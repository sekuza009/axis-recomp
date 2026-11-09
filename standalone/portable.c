/* portable.c: the loader of the portable branch's builds (PORTABLE=1 / PORTABLE=2 in build.sh, see PORTING.md), in
   place of main.c. Nothing of AxisGL.exe is built in: no header or code bytes (gamedata.bin), no jumps at the
   original functions' entries, no jumps for the C runtime. The rebuilt code calls itself directly, the runtime
   through g_crtFn (crt.c) and the system through the import slots in g_rdata, which are filled here by name
   (src/import_list.h).

   1. the game's data (src/data) is put in place: g_rdata, g_data, the split variables' initial values, and the few
      tables the original kept among its code (text_data: DirectInput's object formats) in g_image, whose other
      pages - code, header, the data part now in g_rdata / g_data - stay inaccessible: any use of them is logged;
   2. the imports are looked up by name;
   3. the fixes' settings are read and the network layer starts (axisnet_recomp.c, which hooks some import slots);
   4. the C runtime's table is filled (crt.c: msvcrt.dll and src/crt/);
   5. the x87 control word the original ran with is set and crt.c's start-up runs the game.

   PORTABLE=1 still links the exe at 0x10000 with the original's range reserved and inaccessible (an original
   address used at run time stops the game, logged); PORTABLE=2 (AXIS_RELOCATABLE) is linked with ASLR and keeps
   nothing at fixed addresses. standalone.log lists what happened. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "standalone.h"
#include "../src/imports.h"
#include "../src/import_list.h"
#include "../src/axis_api.h"

BOOL WINAPI axisnet_attach(HINSTANCE inst, DWORD reason, LPVOID reserved);   /* axisnet_recomp.c */
void platform_loadSettings(void);                                            /* platform.c */
unsigned crt_missing(void);                                                  /* crt.c */

#ifdef AXIS_RELOCATABLE
BYTE g_image[GAME_SIZE] __attribute__((aligned(4096)));
#else
/* (PORTABLE=1: from below the original's range to past it, as main.c's g_space; g_image right after the range) */
static BYTE g_space[GAME_BASE + 2 * GAME_SIZE - 0x10000] __attribute__((aligned(4096)));
__asm__(".globl _g_image\n\t.set _g_image, 0xb6b000");
#endif
static FILE *g_log;
static char g_logPath[MAX_PATH];

typedef struct { DWORD address; const void *bytes; DWORD size; } DataPiece;
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[], g_splitObjects[];

static void fail(const char *fmt, const char *arg)
{
	char msg[512];
	snprintf(msg, sizeof msg, fmt, arg);
	if (g_log) { fprintf(g_log, "%s\n", msg); fclose(g_log); g_log = NULL; }
	MessageBoxA(NULL, msg, "AxisRC", MB_ICONERROR);
	ExitProcess(1);
}

/* a line appended to standalone.log after start-up (crt.c's start-up logs its steps) */
void sa_log(const char *fmt, int arg)
{
	FILE *f = fopen(g_logPath, "a");
	if (f) { fprintf(f, fmt, arg); fprintf(f, "\n"); fclose(f); }
}

/* an address in the logs: in g_rdata / g_data / g_image as the original's, else as it is */
static DWORD original(DWORD a)
{
	if (a - (DWORD)g_rdata < 0x4000) return a - (DWORD)g_rdata + 0x4a9000;
	if (a - (DWORD)g_data < 0x666000) return a - (DWORD)g_data + 0x4ad000;
	return a - (DWORD)g_image < GAME_SIZE ? a - (DWORD)g_image + GAME_BASE : a;
}

/* a .data address (0x4ad000 .. 0xb13000) for code that names the game's data by number (axisnet_recomp.c's IMG):
   inside a split object, its place in that object's variable, else its place in g_data (g_splitObjects is in
   address order) */
DWORD axis_dataAt(DWORD a)
{
	static int n = -1;
	if (n < 0)
		for (n = 0; g_splitObjects[n].address; n++)
			;
	int lo = 0, hi = n - 1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		const DataPiece *s = &g_splitObjects[mid];
		if (a < s->address)
			hi = mid - 1;
		else if (a - s->address >= s->size)
			lo = mid + 1;
		else
			return (DWORD)s->bytes + (a - s->address);
	}
	return (DWORD)g_data + (a - 0x4ad000);
}

static void log_stack(FILE *f, const DWORD *sp, int words)
{
	HMODULE exe = GetModuleHandleA(NULL);
	DWORD lo = (DWORD)exe, hi = lo + ((IMAGE_NT_HEADERS32 *)((BYTE *)exe + ((IMAGE_DOS_HEADER *)exe)->e_lfanew))->OptionalHeader.SizeOfImage;
	for (int i = 0; i < words; i++)
		if (sp[i] - lo < hi - lo)
			fprintf(f, " [%d]%08lx", i, sp[i] - lo);   /* (AxisRC.exe's code: as an offset from its base) */
}

/* the guards: g_image's inaccessible pages (the original's code, header and moved data), the original's range
   (PORTABLE=1) and the split variables' old places in g_data - anything reaching them is logged, the game stopped */
static LONG CALLBACK guard_hit(EXCEPTION_POINTERS *e)
{
	if (e->ExceptionRecord->ExceptionCode != EXCEPTION_ACCESS_VIOLATION)
		return EXCEPTION_CONTINUE_SEARCH;
	DWORD at = (DWORD)e->ExceptionRecord->ExceptionAddress, data = (DWORD)e->ExceptionRecord->ExceptionInformation[1];
	int ours = data - (DWORD)g_image < GAME_SIZE || data - (DWORD)g_data < 0x666000 || at - (DWORD)g_image < GAME_SIZE;
#ifndef AXIS_RELOCATABLE
	ours |= data - GAME_BASE < GAME_SIZE || at - GAME_BASE < GAME_SIZE;
#endif
	if (!ours)
		return EXCEPTION_CONTINUE_SEARCH;
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		fprintf(f, "ORIGINAL ADDRESS USED: %s %08lx (%s) at %08lx (exe+%lx, esp %08lx); on the stack:",
		        at == data ? "executing" : e->ExceptionRecord->ExceptionInformation[0] ? "writing" : "reading",
		        original(data), data - GAME_BASE < GAME_SIZE ? "the original's range" : "the image's guarded part",
		        at, at - (DWORD)GetModuleHandleA(NULL), e->ContextRecord->Esp);
		log_stack(f, (const DWORD *)e->ContextRecord->Esp, 64);
		fprintf(f, "\n");
		fclose(f);
	}
	TerminateProcess(GetCurrentProcess(), 4);
	return EXCEPTION_CONTINUE_SEARCH;
}

/* any other crash: logged with where it happened */
static LONG WINAPI crash_hit(EXCEPTION_POINTERS *e)
{
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		DWORD at = (DWORD)e->ExceptionRecord->ExceptionAddress;
		fprintf(f, "CRASH: exception %08lx at %08lx (exe+%lx; data %08lx, esp %08lx); on the stack:",
		        e->ExceptionRecord->ExceptionCode, at, at - (DWORD)GetModuleHandleA(NULL),
		        (DWORD)e->ExceptionRecord->ExceptionInformation[1], e->ContextRecord->Esp);
		log_stack(f, (const DWORD *)e->ContextRecord->Esp, 64);
		fprintf(f, "\n");
		fclose(f);
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

/* 1. the game's data in place */
static void place_data(void)
{
	const DataPiece *tables[3] = { g_rdataPieces, g_dataPieces, g_text_dataPieces };
	DWORD total = 0, pieces = 0;
	static BYTE used[GAME_SIZE >> 12];   /* g_image's pages that hold text_data */
	for (int t = 0; t < 3; t++)
		for (const DataPiece *p = tables[t]; p->address; p++, pieces++) {
			if (p->address - GAME_BASE >= GAME_SIZE || p->address + p->size - GAME_BASE > GAME_SIZE)
				fail("src/data has a piece outside the image (%s)", "tools/mkdatasrc.py");
			memcpy(AT(p->address), p->bytes, p->size);
			total += p->size;
			if (t == 2)
				for (DWORD a = p->address & ~0xfffu; a < p->address + p->size; a += 0x1000)
					used[(a - GAME_BASE) >> 12] = 1;
		}
	fprintf(g_log, "the game's data from src/data: %lu bytes in %lu pieces\n", total, pieces);
	/* g_image: only text_data's pages stay accessible */
	DWORD old, guarded = 0;
	for (DWORD o = 0; o < 0xb13000 - GAME_BASE; o += 0x1000)
		if (!used[o >> 12] && VirtualProtect(g_image + o, 0x1000, PAGE_NOACCESS, &old))
			guarded++;
	/* the split variables: their initial values (from g_data, just placed), their old pages in g_data guarded */
	DWORD objects = 0, pages = 0;
	for (const DataPiece *s = g_splitObjects; s->address; s++, objects++) {
		memcpy((void *)s->bytes, AT(s->address), s->size);
		memset(AT(s->address), 0xa5, s->size);
		DWORD lo = ((DWORD)AT(s->address) + 0xfff) & ~0xfffu, hi = (DWORD)AT(s->address + s->size) & ~0xfffu;
		if (hi > lo && VirtualProtect((void *)lo, hi - lo, PAGE_NOACCESS, &old))
			pages += (hi - lo) >> 12;
	}
	fprintf(g_log, "%lu of g_image's pages left inaccessible (all but text_data's); %lu objects split out of g_data, "
	        "%lu of their old pages guarded\n", guarded, objects, pages);
}

/* an import's slot by name (glstate.c's layer) */
static void **slot_by_name(const char *name)
{
#define IMPORT_SLOT_(n, d) { #n, IMP_##n },
	static const struct { const char *name; DWORD slot; } k[] = { IMPORT_LIST(IMPORT_SLOT_) };
#undef IMPORT_SLOT_
	for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++)
		if (!strcmp(k[i].name, name))
			return (void **)AT(k[i].slot);
	return NULL;
}

/* 2. the imports, by name, into their slots in g_rdata */
static void resolve_imports(void)
{
#define IMPORT_ROW_(n, d) { #n, d, IMP_##n },
	static const struct { const char *name, *dll; DWORD slot; } k[] = { IMPORT_LIST(IMPORT_ROW_) };
#undef IMPORT_ROW_
	for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++) {
		HMODULE m = LoadLibraryA(k[i].dll);
		if (!m)
			fail("cannot load %s (a library the game imports)", k[i].dll);
		FARPROC f = GetProcAddress(m, k[i].name);
		if (!f)
			fail("cannot find %s (imported by the game)", k[i].name);
		*(FARPROC *)AT(k[i].slot) = f;
	}
	fprintf(g_log, "%u imports resolved by name\n", (unsigned)(sizeof k / sizeof k[0]));
}

#ifndef AXIS_DLL
/* AXISRC_MULTI=1 (a test, as the trace builds have it): the game's FindWindowA does not see another copy's "AXIS"
   window, so two copies run on one PC (the two-copy sessions) */
static HWND WINAPI find_window(LPCSTR cls, LPCSTR name)
{
	if ((ULONG_PTR)cls > 0xffff && !strcmp(cls, "AXIS"))
		return NULL;
	return FindWindowA(cls, name);
}

/* the Windows host (PORTING.md stage 4): the game started, then its frames run - each after the window's messages,
   as the original's loop did - until it stops. (crt.c's start-up calls this after the static constructors) */
int host_run(void *instance, const char *cmd, int show)
{
	if (!axis_init(instance, NULL, cmd, show))
		return 0;
	sa_log("axis_init done; the host's loop runs the frames (%d)", 0);
	MSG msg;
	while (axis_running()) {
		while (PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE) == 1)
			if (GetMessageA(&msg, NULL, 0, 0)) {
				if (axis_textInput())
					TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		axis_frame();
	}
	return 1;
}

#else
static HWND WINAPI find_window(LPCSTR cls, LPCSTR name)   /* (AXISRC_MULTI, as above) */
{
	if ((ULONG_PTR)cls > 0xffff && !strcmp(cls, "AXIS"))
		return NULL;
	return FindWindowA(cls, name);
}
void crt_construct(void);
#endif

void crt_finish(int r);
int axis_hasEnded(unsigned *code);   /* src/app/win32.c */
/* the end: when the game quit itself (its window destroyed), its code, back to the host (the original ended the
   process there, its exit list not run); otherwise - axis_init failed, or the host stopped - the game's exit list
   and the process ended, as the original's WinMain returning did */
static char g_importLogPath[MAX_PATH];   /* (AXIS_IMPORTLOG, below) */
static void import_log_write(void);
AXIS_API int axis_exit(int code)
{
	unsigned c;
	if (g_importLogPath[0])
		import_log_write();
	if (axis_hasEnded(&c)) {
		sa_log("the game quit (code %d): back to the host", (int)c);
		return (int)c;
	}
	crt_finish(code);
	return code;
}


/* AXIS_MOUSELOG=<file> (a check): the game's mouse reads - each second, how many and the movement they carried, as
   the game got it (DirectInput's, or a host's) */
extern void (*g_platMouseLog)(long dx, long dy);
static FILE *g_mouseLog;
static DWORD g_mouseT;
static long g_mReads, g_mDx, g_mDy, g_mMax, g_mMoving;
static long g_testEnding = -1, g_testEndingCode = 99;
static char g_testMessage[256];   /* (AXIS_TEST_MESSAGE=<text>: a message box on the first frame, through the game's slot) */

/* AXIS_IMPORTLOG=<file> (a check, PORTING.md stage 3): which of the game's imports it really calls, and how often -
   a counting stub in front of every import slot (after the host's and the GL layers' own), the counts written every
   five seconds (only the ones called) */
#define IMPORT_NAME_(n, d) #n,
static const char *const k_importNames[] = { IMPORT_LIST(IMPORT_NAME_) };
#undef IMPORT_NAME_
#define N_IMPORTS (sizeof k_importNames / sizeof k_importNames[0])
static volatile LONG g_importCount[N_IMPORTS];
static void *g_importTarget[N_IMPORTS];
static char g_importLogPath[MAX_PATH];
static DWORD g_importLogT;
static void import_log_write(void)
{
	FILE *f = fopen(g_importLogPath, "w");
	if (!f)
		return;
	for (unsigned i = 0; i < N_IMPORTS; i++)
		if (g_importCount[i])
			fprintf(f, "%s %ld\n", k_importNames[i], g_importCount[i]);
	fclose(f);
}
static void import_log_install(void)
{
	unsigned char *code = VirtualAlloc(NULL, N_IMPORTS * 12, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!code)
		return;
	for (unsigned i = 0; i < N_IMPORTS; i++) {
		void **slot = slot_by_name(k_importNames[i]);
		if (!slot)
			continue;
		unsigned char *s = code + i * 12;
		g_importTarget[i] = *slot;
		s[0] = 0xff; s[1] = 0x05;   /* inc dword ptr [count] */
		*(void **)(s + 2) = (void *)&g_importCount[i];
		s[6] = 0xff; s[7] = 0x25;   /* jmp dword ptr [target] */
		*(void **)(s + 8) = (void *)&g_importTarget[i];
		*slot = s;
	}
	FlushInstructionCache(GetCurrentProcess(), code, N_IMPORTS * 12);
	g_importLogT = GetTickCount();
}

static void mouse_log(long dx, long dy)
{
	if (g_importLogPath[0] && GetTickCount() - g_importLogT >= 5000) {
		g_importLogT = GetTickCount();
		import_log_write();
	}
	if (g_testMessage[0]) {
		char t[256];
		strcpy(t, g_testMessage);
		g_testMessage[0] = 0;
		((int (WINAPI *)(HWND, LPCSTR, LPCSTR, UINT))*slot_by_name("MessageBoxA"))(NULL, t, "Axis (a test message)", 0);
	}
	if (g_testEnding > 0 && --g_testEnding == 0) {
		extern unsigned char g_exitCode_v[], g_mainWindow_v[];
		*(int *)g_exitCode_v = g_testEndingCode;   /* (99: app_closeWindow(0x63), game_postMatch after mission 15; 1: a graphics change) */
		/* (through the game's own slot, as app_closeWindow posts it: a host's stand-in window gets it too) */
		((BOOL (WINAPI *)(HWND, UINT, WPARAM, LPARAM))*slot_by_name("PostMessageA"))(*(HWND *)g_mainWindow_v, WM_CLOSE, 0, 0);
	}
	if (!g_mouseLog)
		return;
	g_mReads++;
	g_mDx += dx;
	g_mDy += dy;
	if (dx || dy) g_mMoving++;
	long a = dx < 0 ? -dx : dx;
	if (a > g_mMax) g_mMax = a;
	DWORD now = GetTickCount();
	if (now - g_mouseT >= 1000) {
		fprintf(g_mouseLog, "%lu ms: %ld reads (%ld with movement), dx %ld dy %ld, largest |dx| in a read %ld\n",
		        now - g_mouseT, g_mReads, g_mMoving, g_mDx, g_mDy, g_mMax);
		fflush(g_mouseLog);
		g_mouseT = now;
		g_mReads = g_mDx = g_mDy = g_mMax = g_mMoving = 0;
	}
}

/* AXIS_LOADLOG=<file> (a check): each loading-screen frame (loading_drawScreen): the time, the frame's real length
   and the length the animation advanced by (TimeSync_frameTime: at most 1/15 s) */
void (*g_platLoadLog)(const void *timeSync, int mode);
static FILE *g_loadLog;
static void load_log(const void *t, int mode)
{
	/* (TimeSync, src/scene.h: the frequency at +0xc, the rise at +0x1c, the frame time at +0x30) */
	const char *ts = (const char *)t;
	unsigned long long freq;
	long long rise;
	float ft;
	memcpy(&freq, ts + 0xc, 8);
	memcpy(&rise, ts + 0x1c, 8);
	memcpy(&ft, ts + 0x30, 4);
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);
	fprintf(g_loadLog, "%.1f ms mode %d: frame %.2f ms, advanced %.2f ms\n", now.QuadPart * 1000.0 / (double)freq, mode,
	        rise * 1000.0 / (double)freq, ft * 1000.0);
	fflush(g_loadLog);
}

/* ---- a host (axis_api.h axis_host): its drawing callback, its input, the game's window kept hidden ---- */
static AxisHostConfig g_host;
static int g_hostSet;
extern int g_platHostInput, g_platformHostFocus;   /* src/plat/win32/devices.c, platform.c */
extern unsigned char g_platKeys[256];
extern int g_platMouse[3];
extern unsigned g_platButtons;
extern void *g_platHostWindow;
static HWND g_gameWnd;           /* the game's own window (class "AXIS"), hidden */
static int g_hostX, g_hostY, g_hostFocus;
static HWND (WINAPI *r_CreateWindowExA)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
static BOOL (WINAPI *r_ShowWindow)(HWND, int);
static HWND (WINAPI *r_GetForegroundWindow)(void);

AXIS_API void axis_host(const AxisHostConfig *config)
{
	g_host = *config;
	g_hostSet = 1;
}

unsigned glrec_header(unsigned char *out, unsigned room);   /* glrec.c */
AXIS_API unsigned axis_stream_header(unsigned char *out, unsigned room) { return glrec_header(out, room); }

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
	g_platformHostFocus = g_hostFocus;
}

static HWND WINAPI h_CreateWindowExA(DWORD ex, LPCSTR cls, LPCSTR title, DWORD style, int x, int y, int w, int h, HWND parent,
                                     HMENU menu, HINSTANCE inst, LPVOID param)
{
	HWND r = r_CreateWindowExA(ex, cls, title, style & ~WS_VISIBLE, x, y, w, h, parent, menu, inst, param);
	if (!parent && !g_gameWnd)   /* (the game's own window: hidden, the host shows the game) */
		g_gameWnd = r;
	return r;
}
static BOOL WINAPI h_ShowWindow(HWND w, int cmd) { return r_ShowWindow(w, w == g_gameWnd ? SW_HIDE : cmd); }
HWND hostwin_main(void);
void hostwin_origin(int *x, int *y);
static HWND game_window(void) { return g_gameWnd ? g_gameWnd : hostwin_main(); }   /* (the hidden one, or the stand-in) */
static HWND WINAPI h_GetForegroundWindow(void) { return g_hostFocus ? game_window() : r_GetForegroundWindow(); }
static BOOL WINAPI h_GetCursorPos(POINT *p)   /* the host's pointer, as a screen point over the game's window */
{
	p->x = g_hostX;
	p->y = g_hostY;
	if (g_gameWnd)
		ClientToScreen(g_gameWnd, p);
	else {
		int x, y;
		hostwin_origin(&x, &y);
		p->x += x;
		p->y += y;
	}
	return TRUE;
}
static BOOL WINAPI h_SetCursorPos(int x, int y) { (void)x; (void)y; return TRUE; }   /* (the host's pointer is its own) */
static short key_state(int vk)
{
	if (vk == VK_LBUTTON) return g_platButtons & 1 ? (short)0x8000 : 0;
	if (vk == VK_RBUTTON) return g_platButtons & 2 ? (short)0x8000 : 0;
	if (vk == VK_MBUTTON) return g_platButtons & 4 ? (short)0x8000 : 0;
	UINT sc = MapVirtualKeyA((UINT)vk, MAPVK_VK_TO_VSC);
	if (vk == VK_LEFT || vk == VK_RIGHT || vk == VK_UP || vk == VK_DOWN || vk == VK_INSERT || vk == VK_DELETE ||
	    vk == VK_HOME || vk == VK_END || vk == VK_PRIOR || vk == VK_NEXT || vk == VK_RCONTROL || vk == VK_RMENU)
		sc |= 0x80;   /* (the extended keys' DirectInput codes) */
	if (vk == VK_SHIFT) return (g_platKeys[0x2a] | g_platKeys[0x36]) & 0x80 ? (short)0x8000 : 0;
	if (vk == VK_CONTROL) return (g_platKeys[0x1d] | g_platKeys[0x9d]) & 0x80 ? (short)0x8000 : 0;
	if (vk == VK_MENU) return (g_platKeys[0x38] | g_platKeys[0xb8]) & 0x80 ? (short)0x8000 : 0;
	return sc < 256 && g_platKeys[sc] & 0x80 ? (short)0x8000 : 0;
}
static SHORT WINAPI h_GetAsyncKeyState(int vk) { return g_hostFocus ? key_state(vk) : 0; }
static SHORT WINAPI h_GetKeyState(int vk) { return key_state(vk); }
/* the game moves the keyboard focus to its text field's hidden EDIT control and back to its window: with a host that
   took the focus from the host's window (its keys stopped, it left the foreground). The host's keys reach the field
   directly (axis_key / axis_char), so the focus stays where it is */
static HWND WINAPI h_SetFocus(HWND w) { (void)w; return GetFocus(); }

/* AXIS_MSGLOG=<file> (a check, PORTING.md stage 3): every message the game's window procedures get from Windows,
   in order - the game's own window class's procedure wrapped (RegisterClassA / RegisterClassExA) */
static FILE *g_msgLog;
static WNDPROC g_msgLogProc;
static LRESULT CALLBACK msg_log_proc(HWND w, UINT m, WPARAM wp, LPARAM lp)
{
	fprintf(g_msgLog, "%lu msg %04x w %08lx l %08lx\n", GetTickCount(), m, (unsigned long)wp, (unsigned long)lp);
	fflush(g_msgLog);
	LRESULT r = CallWindowProcA(g_msgLogProc, w, m, wp, lp);
	return r;
}
static ATOM (WINAPI *r_RegisterClassA)(const WNDCLASSA *);
static ATOM WINAPI h_RegisterClassA(const WNDCLASSA *c)
{
	WNDCLASSA w = *c;
	g_msgLogProc = w.lpfnWndProc;
	w.lpfnWndProc = msg_log_proc;
	return r_RegisterClassA(&w);
}
static ATOM (WINAPI *r_RegisterClassExA)(const WNDCLASSEXA *);
static ATOM WINAPI h_RegisterClassExA(const WNDCLASSEXA *c)
{
	WNDCLASSEXA w = *c;
	g_msgLogProc = w.lpfnWndProc;
	w.lpfnWndProc = msg_log_proc;
	return r_RegisterClassExA(&w);
}

/* the host's message box and program launches (AxisHostConfig.message / launch) in place of Windows' */
static int WINAPI h_MessageBoxA(HWND owner, LPCSTR text, LPCSTR title, UINT type)
{
	(void)owner;
	(void)type;
	return g_host.message(g_host.user, title ? title : "", text ? text : "");
}
static HINSTANCE WINAPI h_ShellExecuteA(HWND w, LPCSTR verb, LPCSTR file, LPCSTR args, LPCSTR dir, INT show)
{
	(void)w; (void)verb; (void)dir; (void)show;
	int ok = g_host.launch(g_host.user, file ? file : "", args ? args : "");
	return (HINSTANCE)(ULONG_PTR)(ok ? 42 : 2);   /* (ShellExecute: above 32 done, else an error) */
}

static void host_install(void)
{
	if (g_host.window)
		g_platHostWindow = g_host.window;
	if (g_host.sound) {   /* (the host's sound: no DirectSound / DirectShow) */
		extern const AxisSound *g_platSound;
		extern void *g_platSoundUser;
		g_platSound = g_host.sound;
		g_platSoundUser = g_host.user;
		fprintf(g_log, "host: the sounds and music played by the host\n");
	}
	if (g_host.frame) {
		int glrec_install_live(void **(*slot)(const char *), const char *, void (*)(void *, const unsigned *, unsigned, int, int), void *);
		char dir[MAX_PATH];
		strcpy(dir, g_logPath);
		*(strrchr(dir, '\\') + 1) = 0;
		fprintf(g_log, "host: each frame's drawing to the host (%d GL calls recorded)\n", glrec_install_live(slot_by_name, dir, g_host.frame, g_host.user));
		if (g_host.nogl) {   /* (no OpenGL: recorded only; the queries from glstate.c, mode 3 - in front of the record) */
			int glrec_nogl(void **(*slot)(const char *));
			int glstate_install(void **(*slot)(const char *name), int mode, const char *dir);
			int faked = glrec_nogl(slot_by_name);
			fprintf(g_log, "host: no OpenGL (%d driver calls answered here, %d by the software GL state)\n", faked,
			        glstate_install(slot_by_name, 3, dir));
		}
	}
	if (g_host.input) {
		g_platHostInput = 1;
		g_platformHostFocus = 0;
#define SWAP(name) do { void **p = slot_by_name(#name); *(void **)&r_##name = *p; *p = (void *)h_##name; } while (0)
#define SET(name) do { *slot_by_name(#name) = (void *)h_##name; } while (0)
		{
			char rw[4];
			if (GetEnvironmentVariableA("AXIS_REALWINDOW", rw, sizeof rw)) {   /* (the old way: a real window, hidden) */
				SWAP(CreateWindowExA); SWAP(ShowWindow);
			} else {
				extern void (*g_platPump)(void);
				int hostwin_install(void **(*slot)(const char *name));
				void hostwin_pump(void);
				fprintf(g_log, "host: no window - its messages, timers and socket events delivered each frame (%d calls answered)\n",
				        hostwin_install(slot_by_name));
				g_platPump = hostwin_pump;
				extern void (*g_glrecFrameSize)(int *, int *);
				void hostwin_size(int *w, int *h);
				g_glrecFrameSize = hostwin_size;   /* (the recorder's frame size: the window's, without a window) */
			}
		}
		SWAP(GetForegroundWindow);
		SET(GetCursorPos); SET(SetCursorPos); SET(GetAsyncKeyState); SET(GetKeyState); SET(SetFocus);
#undef SWAP
#undef SET
		fprintf(g_log, "host: the input from the host, the game's window hidden\n");
	}
	if (g_host.message) {
		*slot_by_name("MessageBoxA") = (void *)h_MessageBoxA;
		fprintf(g_log, "host: the game's message boxes shown by the host\n");
	}
	if (g_host.launch) {
		*slot_by_name("ShellExecuteA") = (void *)h_ShellExecuteA;
		fprintf(g_log, "host: the programs the game starts (itself again, the patcher, DServer) started by the host\n");
	}
	{
		char p[MAX_PATH];
		if (GetEnvironmentVariableA("AXIS_MSGLOG", p, sizeof p) && (g_msgLog = fopen(p, "w"))) {
			void **s = slot_by_name("RegisterClassA");
			*(void **)&r_RegisterClassA = *s;
			*s = (void *)h_RegisterClassA;
			s = slot_by_name("RegisterClassExA");
			*(void **)&r_RegisterClassExA = *s;
			*s = (void *)h_RegisterClassExA;
		}
	}
}

#ifdef AXIS_DLL
AXIS_API int axis_load(void)
{
	HINSTANCE inst = GetModuleHandleA(NULL);
#else
int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	(void)prev; (void)cmd; (void)show;
#endif
	char path[MAX_PATH];
	if (GetEnvironmentVariableA("AXIS_GAME_DIR", path, MAX_PATH - 20)) {   /* (a host's game folder: the game's files, settings, logs) */
		size_t n = strlen(path);
		if (n && path[n - 1] != '\\') strcat(path, "\\");
		SetCurrentDirectoryA(path);
		strcat(path, "standalone.log");
	} else {
		GetModuleFileNameA(NULL, path, sizeof path);
		strcpy(strrchr(path, '\\') + 1, "standalone.log");
	}
	strcpy(g_logPath, path);
	g_log = fopen(path, "w");
	if (!g_log)
		fail("cannot write %s", path);
#ifdef AXIS_DLL
	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((void *)axis_load, &mbi, sizeof mbi);
	fprintf(g_log, "axis.dll at %p (host %p), the image's remains (text_data) at %p\n", mbi.AllocationBase,
	        (void *)GetModuleHandleA(NULL), (void *)g_image);
#else
	fprintf(g_log, "portable build: AxisRC.exe at %p, the image's remains (text_data) at %p\n",
	        (void *)GetModuleHandleA(NULL), (void *)g_image);
#endif
#ifndef AXIS_RELOCATABLE
	DWORD old;
	if ((BYTE *)g_space > (BYTE *)GAME_BASE || (BYTE *)g_space + sizeof g_space < g_image + GAME_SIZE)
		fail("AxisRC.exe was linked so that g_space does not hold the original's range (%s)", "see build.sh");
	if (!VirtualProtect((void *)GAME_BASE, GAME_SIZE, PAGE_NOACCESS, &old))
		fail("cannot protect the original's range (%s)", "VirtualProtect");
	fprintf(g_log, "the original's range 0x%x .. 0x%x left inaccessible\n", GAME_BASE, GAME_BASE + GAME_SIZE);
#endif
	AddVectoredExceptionHandler(1, guard_hit);
	SetUnhandledExceptionFilter(crash_hit);
	place_data();
	resolve_imports();
	if (GetEnvironmentVariableA("AXISRC_MULTI", NULL, 0)) {   /* (a test: a second copy, as the trace builds allow) */
		*(FARPROC *)AT(IMP_FindWindowA) = (FARPROC)find_window;
		fprintf(g_log, "AXISRC_MULTI: the game's \"already running\" check skipped\n");
	}
	platform_loadSettings();
	axisnet_attach(inst, DLL_PROCESS_ATTACH, NULL);
	fprintf(g_log, "network layer started\n");
	if (g_hostSet)
		host_install();
	{
		char p[MAX_PATH];
		if (GetEnvironmentVariableA("AXIS_IMPORTLOG", g_importLogPath, sizeof g_importLogPath))
			g_platMouseLog = mouse_log;   /* (written from the per-frame mouse read) */
		else
			g_importLogPath[0] = 0;
		if (GetEnvironmentVariableA("AXIS_TEST_MESSAGE", g_testMessage, sizeof g_testMessage)) {
			SetEnvironmentVariableA("AXIS_TEST_MESSAGE", NULL);
			g_platMouseLog = mouse_log;
		} else
			g_testMessage[0] = 0;
		if (GetEnvironmentVariableA("AXIS_TEST_ENDING", p, sizeof p) && atoi(p) > 0) {   /* <reads>[,<exit code>] */
			g_testEnding = atoi(p);
			g_testEndingCode = strchr(p, ',') ? atoi(strchr(p, ',') + 1) : 99;
			SetEnvironmentVariableA("AXIS_TEST_ENDING", NULL);   /* (a copy the game starts does not inherit it) */
			g_platMouseLog = mouse_log;
		}
		if (GetEnvironmentVariableA("AXIS_LOADLOG", p, sizeof p) && (g_loadLog = fopen(p, "w")))
			g_platLoadLog = load_log;
		if (GetEnvironmentVariableA("AXIS_MOUSELOG", p, sizeof p) && (g_mouseLog = fopen(p, "w"))) {
			g_mouseT = GetTickCount();
			g_platMouseLog = mouse_log;
		}
	}
	if (GetEnvironmentVariableA("AXIS_GLREC", NULL, 0)) {   /* (a check: the drawing recorded and replayed, glrec.c) */
		int glrec_install(void **(*slot)(const char *name), const char *dir);
		char dir[MAX_PATH];
		strcpy(dir, g_logPath);
		*(strrchr(dir, '\\') + 1) = 0;
		fprintf(g_log, "AXIS_GLREC: %d GL calls recorded (glrec.log)\n", glrec_install(slot_by_name, dir));
	}
	{	/* AXIS_GLSTATE=1 / 2 (a check): the software GL state in front of the GL slots, glstate.c */
		char v[8];
		if (GetEnvironmentVariableA("AXIS_GLSTATE", v, sizeof v)) {
			int glstate_install(void **(*slot)(const char *name), int mode, const char *dir);
			char dir[MAX_PATH];
			strcpy(dir, g_logPath);
			*(strrchr(dir, '\\') + 1) = 0;
			fprintf(g_log, "AXIS_GLSTATE=%s: %d GL calls layered (glstate.log)\n", v, glstate_install(slot_by_name, v[0] - '0', dir));
		}
	}
	if (g_importLogPath[0])
		import_log_install();   /* (last: after every other layer in front of the slots) */
	int n = 0;
	const char *missing = crt_install(&n);
	if (missing)
		fail("msvcrt.dll has no %s (needed for the game's C runtime)", missing);
	if (crt_missing()) {
		char a[16];
		snprintf(a, sizeof a, "%x", crt_missing());
		fail("the C runtime entry %s has no function (standalone/crt.c)", a);
	}
	fprintf(g_log, "the game's C runtime: %d entries (msvcrt.dll, src/crt)\n", n);
	{	/* the x87 control word the original ran with (main.c) */
		unsigned short cw = 0x027f;
		__asm__ volatile("fldcw %0" : : "m"(cw));
	}
	fclose(g_log);
	g_log = NULL;
#ifdef AXIS_DLL
	crt_construct();
	return 1;
#else
	crt_start();
	return 0;
#endif
}
