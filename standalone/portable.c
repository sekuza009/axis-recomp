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

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	char path[MAX_PATH];
	(void)prev; (void)cmd; (void)show;
	GetModuleFileNameA(NULL, path, sizeof path);
	strcpy(strrchr(path, '\\') + 1, "standalone.log");
	strcpy(g_logPath, path);
	g_log = fopen(path, "w");
	if (!g_log)
		fail("cannot write %s", path);
	fprintf(g_log, "portable build: AxisRC.exe at %p, the image's remains (text_data) at %p\n",
	        (void *)GetModuleHandleA(NULL), (void *)g_image);
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
	crt_start();
	return 0;
}
