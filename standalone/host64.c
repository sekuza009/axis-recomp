/* host64.c: the 64-bit build's loader (PORTING.md, stage 6) - the game as a library for a host (Godot), on Windows x64,
   Linux and macOS alike. What standalone/portable.c is for the 32-bit Windows build, without Windows under it:

   - the arena (standalone/arena.c) made and the game's data put in it at the original addresses;
   - the game's C runtime (standalone/crt64.c), its static constructors run;
   - the system calls the game makes (src/import_list.h: plat_<name>, src/axis.h IMPORT_FN) are thunks through a table
     of slots here (build/plat_thunks64.s, tools/mkthunks64.py), as the 32-bit build's go through the import slots:
     each starts at a stub that logs the first call ("not on this platform") and answers 0; what a platform defines
     itself (src/plat/posix: plat_<name> functions) takes the place of the thunk; the host layers sit in the slots - the
     drawing recorded for the host (standalone/glrec64.c), the GL state in software (standalone/glstate.c), the window
     stood in (standalone/hostwin64.c), the input and focus from the host (here);
   - the API (src/axis_api.h): axis_init / axis_frame / axis_shutdown ... run the game's own (src/app/win32.c,
     renamed game_axis_* in this build) on the arena's stack, the input and the host's configuration kept here.

   Handles the game keeps (a window, a device context, an instance) are addresses in the arena too: a number from the
   top of the arena (never mapped) made into a pointer, so the game's AV / AP pass them through unchanged. */
#if defined(__x86_64__) || defined(__aarch64__)
#define _GNU_SOURCE
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#define chdir _chdir
#else
#include <unistd.h>
#endif
#define AXIS_DLL 1
#include "../src/axis_api.h"

typedef uint32_t u32;
typedef uint8_t u8;
typedef uint16_t u16;

/* standalone/arena.c */
extern unsigned char *g_arena;
int arena_init(void);
typedef struct { u32 address; const void *bytes; u32 size; } DataPiece;
void arena_placeData(const DataPiece *pieces);
void arena_call(void (*fn)(void *), void *arg);
void *arena_malloc(size_t n);
void arena_free(void *p);
void *fn_ptr(u32 address);
void arena_setLog(FILE *f);
void arena_stats(size_t *inUse, size_t *peak, u32 *top);
/* standalone/crt64.c */
int crt64_install(void);
void crt64_runExitList(void);
int crt64_vsprintf(char *out, const char *fmt, va_list ap);
/* src/data */
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[];

#define AP_(v) ((void *)((v) ? g_arena + (u32)(v) : NULL))
#define AV_(p) ((p) ? (u32)((const u8 *)(p) - g_arena) : 0u)
/* a handle: an arena address above everything mapped (never looked into) */
static u32 g_nextHandle = 0xfe000000u;
void *host64_handle(void) { g_nextHandle += 16; return g_arena + g_nextHandle; }
#define INSTANCE ((void *)(g_arena + 0x400000))   /* (the module's handle: the original's image base, as Windows has it) */

/* ---- the log: standalone64.log in the game folder */
static FILE *g_log;
static char g_dir[1024];
void hlog(const char *fmt, ...)
{
	va_list a;
	va_start(a, fmt);
	vfprintf(g_log ? g_log : stderr, fmt, a);
	va_end(a);
	fflush(g_log ? g_log : stderr);
}

/* ---- the slots */
#include "../src/import_list.h"
enum {
#define IX_(n, d) IMPIX_##n,
	IMPORT_LIST(IX_)
#undef IX_
	IMP_COUNT
};
void *g_platSlots[IMP_COUNT];
static const char *const k_impNames[IMP_COUNT] = {
#define NAME_(n, d) #n,
	IMPORT_LIST(NAME_)
#undef NAME_
};
static unsigned g_missCount[IMP_COUNT];
static uintptr_t missing(int i)
{
	if (!g_missCount[i]++)
		hlog("import %s called: not on this platform (0 answered)\n", k_impNames[i]);
	return 0;
}
#define MISS_(n, d) static uintptr_t miss_##n(void) { return missing(IMPIX_##n); }
IMPORT_LIST(MISS_)
#undef MISS_
static void *const k_miss[IMP_COUNT] = {
#define MISSP_(n, d) (void *)miss_##n,
	IMPORT_LIST(MISSP_)
#undef MISSP_
};
void **host64_slot(const char *name)
{
	for (int i = 0; i < IMP_COUNT; i++)
		if (!strcmp(k_impNames[i], name))
			return &g_platSlots[i];
	return NULL;
}
#define SET(name, f) (*host64_slot(#name) = (void *)(f))

/* ---- the host */
static AxisHostConfig g_host;
static int g_hostSet;
extern unsigned char g_platKeys[256];   /* src/plat/host/devices.c */
extern int g_platMouse[3];
extern unsigned g_platButtons;
extern int g_platHostInput;
extern const AxisSound *g_platSound;
extern void *g_platSoundUser;
extern void *g_platHostUser;   /* src/plat/posix/system.c (message boxes, launches, the screen) */
extern int (*g_platHostMessage)(void *user, const char *title, const char *text);
extern int (*g_platHostLaunch)(void *user, const char *program, const char *arguments);
extern int g_platScreenW, g_platScreenH;
void (*g_platLoadLog)(const void *timeSync, int mode);   /* (src/plat/plat.h PLAT_LOADLOG: none here) */
static int g_hostX, g_hostY, g_hostFocus;
static int host_focus(void) { return g_hostFocus; }
int (*host64_focus)(void) = host_focus;   /* (platform64.c: the fixes' "is the game in front") */

AXIS_API void axis_host(const AxisHostConfig *config)
{
	g_host = *config;
	g_hostSet = 1;
}
unsigned glrec64_header(unsigned char *out, unsigned room);
AXIS_API unsigned axis_stream_header(unsigned char *out, unsigned room) { return glrec64_header(out, room); }
AXIS_API void axis_input(const unsigned char keys[256], int dx, int dy, int wheel, unsigned buttons, int x, int y, int focused)
{
	memcpy(g_platKeys, keys, 256);
	g_platMouse[0] += dx;
	g_platMouse[1] += dy;
	g_platMouse[2] += wheel;
	g_platButtons = buttons;
	g_hostX = x;
	g_hostY = y;
	g_hostFocus = focused != 0;
}

/* the input imports, from the host (the game's prototypes: src/game.h) */
void *hostwin_main(void);              /* hostwin64.c */
void hostwin_origin(int *x, int *y);
static void *h_GetForegroundWindow(void) { return g_hostFocus ? hostwin_main() : NULL; }
static void *h_GetActiveWindow(void) { return hostwin_main(); }
static u32 h_GetCursorPos(int *p)
{
	int x, y;
	hostwin_origin(&x, &y);
	p[0] = g_hostX + x;
	p[1] = g_hostY + y;
	return 1;
}
static u32 h_SetCursorPos(int x, int y) { (void)x; (void)y; return 1; }
/* a Windows virtual key's state from the host's keyboard (DirectInput codes) */
static const u8 k_vkToDik[256] = {
	[0x08] = 0x0e, [0x09] = 0x0f, [0x0d] = 0x1c, [0x10] = 0x2a, [0x11] = 0x1d, [0x12] = 0x38, [0x13] = 0xc5, [0x14] = 0x3a,
	[0x1b] = 0x01, [0x20] = 0x39, [0x21] = 0xc9, [0x22] = 0xd1, [0x23] = 0xcf, [0x24] = 0xc7, [0x25] = 0xcb, [0x26] = 0xc8,
	[0x27] = 0xcd, [0x28] = 0xd0, [0x2d] = 0xd2, [0x2e] = 0xd3,
	['0'] = 0x0b, ['1'] = 0x02, ['2'] = 0x03, ['3'] = 0x04, ['4'] = 0x05, ['5'] = 0x06, ['6'] = 0x07, ['7'] = 0x08,
	['8'] = 0x09, ['9'] = 0x0a,
	['A'] = 0x1e, ['B'] = 0x30, ['C'] = 0x2e, ['D'] = 0x20, ['E'] = 0x12, ['F'] = 0x21, ['G'] = 0x22, ['H'] = 0x23,
	['I'] = 0x17, ['J'] = 0x24, ['K'] = 0x25, ['L'] = 0x26, ['M'] = 0x32, ['N'] = 0x31, ['O'] = 0x18, ['P'] = 0x19,
	['Q'] = 0x10, ['R'] = 0x13, ['S'] = 0x1f, ['T'] = 0x14, ['U'] = 0x16, ['V'] = 0x2f, ['W'] = 0x11, ['X'] = 0x2d,
	['Y'] = 0x15, ['Z'] = 0x2c,
	[0x60] = 0x52, [0x61] = 0x4f, [0x62] = 0x50, [0x63] = 0x51, [0x64] = 0x4b, [0x65] = 0x4c, [0x66] = 0x4d, [0x67] = 0x47,
	[0x68] = 0x48, [0x69] = 0x49, [0x6a] = 0x37, [0x6b] = 0x4e, [0x6d] = 0x4a, [0x6e] = 0x53, [0x6f] = 0xb5,
	[0x70] = 0x3b, [0x71] = 0x3c, [0x72] = 0x3d, [0x73] = 0x3e, [0x74] = 0x3f, [0x75] = 0x40, [0x76] = 0x41, [0x77] = 0x42,
	[0x78] = 0x43, [0x79] = 0x44, [0x7a] = 0x57, [0x7b] = 0x58, [0x90] = 0x45, [0x91] = 0x46,
	[0xa0] = 0x2a, [0xa1] = 0x36, [0xa2] = 0x1d, [0xa3] = 0x9d, [0xa4] = 0x38, [0xa5] = 0xb8,
	[0xba] = 0x27, [0xbb] = 0x0d, [0xbc] = 0x33, [0xbd] = 0x0c, [0xbe] = 0x34, [0xbf] = 0x35, [0xc0] = 0x29,
	[0xdb] = 0x1a, [0xdc] = 0x2b, [0xdd] = 0x1b, [0xde] = 0x28,
};
static short key_state(int vk)
{
	if (vk == 0x01) return g_platButtons & 1 ? (short)0x8000 : 0;
	if (vk == 0x02) return g_platButtons & 2 ? (short)0x8000 : 0;
	if (vk == 0x04) return g_platButtons & 4 ? (short)0x8000 : 0;
	if (vk == 0x10) return (g_platKeys[0x2a] | g_platKeys[0x36]) & 0x80 ? (short)0x8000 : 0;
	if (vk == 0x11) return (g_platKeys[0x1d] | g_platKeys[0x9d]) & 0x80 ? (short)0x8000 : 0;
	if (vk == 0x12) return (g_platKeys[0x38] | g_platKeys[0xb8]) & 0x80 ? (short)0x8000 : 0;
	u8 dik = vk >= 0 && vk < 256 ? k_vkToDik[vk] : 0;
	return dik && g_platKeys[dik] & 0x80 ? (short)0x8000 : 0;
}
static u32 h_GetAsyncKeyState(int vk) { return g_hostFocus ? (u16)key_state(vk) : 0; }
static short h_GetKeyState(int vk) { return key_state(vk); }
static void *h_SetFocus(void *w) { (void)w; return hostwin_main(); }

extern void *(*g_platNewHandle)(void);   /* src/plat/posix/system.c */
static void host_install(void)
{
#ifndef _WIN32
	g_platNewHandle = host64_handle;
#endif
	g_platHostUser = g_host.user;
	g_platHostMessage = g_host.message;
	g_platHostLaunch = g_host.launch;
	if (g_host.screen_w > 0 && g_host.screen_h > 0) {
		g_platScreenW = g_host.screen_w;
		g_platScreenH = g_host.screen_h;
	}
	if (g_host.sound) {
		g_platSound = g_host.sound;
		g_platSoundUser = g_host.user;
		hlog("host: the sounds and music played by the host\n");
	}
	int glrec64_install(void **(*slot)(const char *), void (*frame)(void *, const unsigned *, unsigned, int, int), void *user);
	int glstate_install(void **(*slot)(const char *name), int mode, const char *dir);
	hlog("host: each frame's drawing to the host, no OpenGL (%d calls recorded, %d answered by the software GL state)\n",
	     glrec64_install(host64_slot, g_host.frame, g_host.user), glstate_install(host64_slot, 3, g_dir));
	int hostwin_install(void **(*slot)(const char *name));
	hlog("host: no window - its messages, timers and socket events delivered each frame (%d calls answered)\n",
	     hostwin_install(host64_slot));
	g_platHostInput = 1;
	SET(GetForegroundWindow, h_GetForegroundWindow); SET(GetActiveWindow, h_GetActiveWindow);
	SET(GetCursorPos, h_GetCursorPos); SET(SetCursorPos, h_SetCursorPos); SET(GetAsyncKeyState, h_GetAsyncKeyState);
	SET(GetKeyState, h_GetKeyState); SET(SetFocus, h_SetFocus);
	hlog("host: the input from the host\n");
}

/* ---- the system calls this file answers itself (the rest: src/plat/posix, the layers above) */
static void *h_GetModuleHandleA(const char *name) { (void)name; return INSTANCE; }
static u32 h_GetModuleFileNameA(void *m, char *out, u32 size)
{
	(void)m;
	int n = snprintf(out, size, "%sAxisGL.exe", g_dir);
	return n < 0 ? 0 : (u32)n;
}
static const char *h_GetCommandLineA(void) { return "AxisGL.exe"; }

/* ---- a crash: where (the instruction, the address it read, the call chain by frame pointers), into the log */
#if !defined(_WIN32) && defined(__x86_64__)
#include <signal.h>
#include <ucontext.h>
static void crashed(int sig, siginfo_t *si, void *ctx)
{
	ucontext_t *uc = ctx;
	uintptr_t ip = (uintptr_t)uc->uc_mcontext.gregs[REG_RIP], bp = (uintptr_t)uc->uc_mcontext.gregs[REG_RBP];
	uintptr_t a = (uintptr_t)si->si_addr;
	hlog("CRASH: signal %d at ip %p, address %p (arena offset %08lx%s)\n", sig, (void *)ip, (void *)a,
	     (unsigned long)(a - (uintptr_t)g_arena), a - (uintptr_t)g_arena < 0x100000000ull ? "" : ", outside");
	hlog("  rsp %p rbp %p; calls:", (void *)(uintptr_t)uc->uc_mcontext.gregs[REG_RSP], (void *)bp);
	for (int i = 0; i < 24 && bp && !(bp & 7); i++) {
		uintptr_t *f = (uintptr_t *)bp;
		hlog(" %p", (void *)f[1]);
		if (f[0] <= bp)
			break;
		bp = f[0];
	}
	hlog("\n");
	signal(sig, SIG_DFL);
	raise(sig);
}
static void crash_handler(void)
{
	struct sigaction sa;
	memset(&sa, 0, sizeof sa);
	sa.sa_sigaction = crashed;
	sa.sa_flags = SA_SIGINFO | SA_ONSTACK;
	sigaction(SIGSEGV, &sa, NULL);
	sigaction(SIGBUS, &sa, NULL);
	sigaction(SIGILL, &sa, NULL);
	sigaction(SIGFPE, &sa, NULL);
	static char alt[65536];
	stack_t st = { .ss_sp = alt, .ss_size = sizeof alt };
	sigaltstack(&st, NULL);
}
#elif defined(_WIN32)
static LONG WINAPI crashed(EXCEPTION_POINTERS *e)
{
	CONTEXT *c = e->ContextRecord;
	uintptr_t a = e->ExceptionRecord->NumberParameters > 1 ? (uintptr_t)e->ExceptionRecord->ExceptionInformation[1] : 0;
	HMODULE m = NULL;
	GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT, (LPCSTR)crashed, &m);
	hlog("CRASH: exception %08lx at ip %p (module offset %llx), address %p (arena offset %llx)\n",
	     (unsigned long)e->ExceptionRecord->ExceptionCode, (void *)c->Rip, (unsigned long long)(c->Rip - (uintptr_t)m),
	     (void *)a, (unsigned long long)(a - (uintptr_t)g_arena));
	hlog("  calls (module offsets):");
	uintptr_t bp = c->Rbp;
	for (int i = 0; i < 24 && bp && !(bp & 7); i++) {
		uintptr_t *f = (uintptr_t *)bp;
		hlog(" %llx", (unsigned long long)(f[1] - (uintptr_t)m));
		if (f[0] <= bp)
			break;
		bp = f[0];
	}
	hlog("\n");
	return EXCEPTION_CONTINUE_SEARCH;
}
static void crash_handler(void) { SetUnhandledExceptionFilter(crashed); }
#else
static void crash_handler(void) {}
#endif

/* ---- start-up */
typedef struct { const u32 *table; int n; } Ctors;
static void run_ctors(void *a)
{
	(void)a;
	int n = 0;
	for (u32 at = 0x4ad000; at < 0x4ad0fc; at += 4) {
		u32 f = *(u32 *)(g_arena + at);
		if (f) {
			((void (*)(void))fn_ptr(f))();
			n++;
		}
	}
	hlog("the game's static constructors run (%d)\n", n);
}

void crt_setLib(const void *lib);   /* src/crt/crt_format.c */
static struct { int (*vsprintf_)(char *, const char *, va_list); } g_crtLib = { crt64_vsprintf };

AXIS_API int axis_load(void)
{
	const char *dir = getenv("AXIS_GAME_DIR");
	if (dir && *dir) {
		snprintf(g_dir, sizeof g_dir, "%s", dir);
		size_t n = strlen(g_dir);
		if (g_dir[n - 1] != '/' && g_dir[n - 1] != '\\')
			strcat(g_dir, "/");
		if (chdir(g_dir) != 0)
			fprintf(stderr, "axis: cannot enter %s\n", g_dir);
	} else
		strcpy(g_dir, "./");
	char path[1100];
	snprintf(path, sizeof path, "%sstandalone64.log", g_dir);
	g_log = fopen(path, "w");
	arena_setLog(g_log);
	crash_handler();
	if (!arena_init())
		return 0;
	hlog("64-bit build: the arena at %p\n", (void *)g_arena);
	arena_placeData(g_rdataPieces);
	arena_placeData(g_dataPieces);
	arena_placeData(g_text_dataPieces);
	int n = crt64_install();
	if (n < 0) {
		hlog("the C runtime: %d entries without a function\n", -n);
		return 0;
	}
	crt_setLib(&g_crtLib);
	hlog("the game's data in place; its C runtime: %d entries\n", n);
	for (int i = 0; i < IMP_COUNT; i++)
		g_platSlots[i] = k_miss[i];
#ifdef _WIN32
	int win64_install(void **(*slot)(const char *name));   /* win64.c */
	hlog("the Windows platform: %d system calls\n", win64_install(host64_slot));
#endif
	SET(GetModuleHandleA, h_GetModuleHandleA); SET(GetModuleFileNameA, h_GetModuleFileNameA);
	SET(GetCommandLineA, h_GetCommandLineA);
	if (g_hostSet)
		host_install();
	arena_call(run_ctors, NULL);
	return 1;
}

/* ---- the game's API calls, on the arena's stack (its own: src/app/win32.c, game_axis_* here) */
unsigned game_axis_init(void *instance, void *previous, const char *commandLine, int show);
unsigned game_axis_frame(void);
int game_axis_running(void);
int game_axis_textInput(void);
void game_axis_shutdown(void);
void game_axis_key(unsigned vk, int down);
void game_axis_char(unsigned ch);
int axis_hasEnded(unsigned *code);   /* src/app/win32.c */

typedef struct { const char *cmd; int show; unsigned r; } InitCall;
static void do_init(void *a)
{
	InitCall *c = a;
	c->r = game_axis_init(INSTANCE, NULL, c->cmd, c->show);
}
AXIS_API unsigned axis_init(void *instance, void *previous, const char *commandLine, int show)
{
	(void)instance;
	(void)previous;
	/* (the command line in the arena: the game keeps pointers into it) */
	size_t n = strlen(commandLine ? commandLine : "");
	char *cmd = arena_malloc(n + 1);
	memcpy(cmd, commandLine ? commandLine : "", n + 1);
	InitCall c = { cmd, show, 0 };
	arena_call(do_init, &c);
	return c.r;
}
static void do_frame(void *a) { *(unsigned *)a = game_axis_frame(); }
AXIS_API unsigned axis_frame(void)
{
	unsigned r = 0;
	arena_call(do_frame, &r);
	return r;
}
AXIS_API int axis_running(void) { return game_axis_running(); }
AXIS_API int axis_textInput(void) { return game_axis_textInput(); }
static void do_shutdown(void *a) { (void)a; game_axis_shutdown(); }
AXIS_API void axis_shutdown(void) { arena_call(do_shutdown, NULL); }
typedef struct { unsigned a; int b; } KeyCall;
static void do_key(void *a) { KeyCall *k = a; game_axis_key(k->a, k->b); }
AXIS_API void axis_key(unsigned vk, int down)
{
	KeyCall k = { vk, down };
	arena_call(do_key, &k);
}
static void do_char(void *a) { game_axis_char(*(unsigned *)a); }
AXIS_API void axis_char(unsigned ch) { arena_call(do_char, &ch); }
static void do_exitlist(void *a) { (void)a; crt64_runExitList(); }
AXIS_API int axis_exit(int code)
{
	unsigned ended;
	size_t inUse, peak;
	u32 top;
	arena_stats(&inUse, &peak, &top);
	hlog("heap: %zu bytes in use, %zu at most (top %08x)\n", inUse, peak, top);
	if (axis_hasEnded(&ended))
		return (int)ended;
	arena_call(do_exitlist, NULL);
	return code;
}
#endif
