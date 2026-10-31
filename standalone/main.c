/* main.c: AxisRC.exe, the rebuilt game as a program of its own (PRIVATE; never ship).

   AxisRC.exe holds every rebuilt function (src/, the same objects recomp.dll is linked from), the patch DLL's fixes
   (axisnet_recomp.c, compiled in with AXIS_STANDALONE) and the game's data (build/gamedata.bin: AxisGL.exe's header,
   .rdata and initialised .data, and the few bytes of its code that anything reads, tools/mkgamedata.py). It runs
   from the game folder (for the game's Data, Map, Sound... files) without reading or changing AxisGL.exe:

   1. the game's image goes to 0x400000, its own address (the game has no relocations). That range is a zeroed
      array in AxisRC.exe's .bss (g_space; the exe is linked at 0x10000 with ASLR off, see build.sh): memory the
      process allocates at start-up (stack, heaps, mapped files) would otherwise sit there;
   2. the game's imports are looked up and written into its import table, which the rebuilt code calls through;
   3. the patch DLL's start-up runs (axisnet_attach: it hooks the game's DirectPlay/ping/OpenGL imports and makes the
      changes the rebuilds follow);
   4. every rebuilt function is switched in at its original's address (a jump), where the game's function tables
      (vtables, callbacks, the constructor table, the window procedure) and the rebuilds' own calls reach it;
   5. the game's C runtime is replaced (crt.c: msvcrt.dll, and src/crt/ where VC6's results differ);
   6. the x87 control word Windows gives the game is set, and crt.c's start-up runs the game: its static
      constructors, the rebuilt WinMain, exit.

   AXISRC_IMAGE=1 maps AxisGL.exe from the folder instead of the built-in data (to compare), AXISRC_GAMECRT=1 keeps
   the game's own runtime, AXISRC_POISON=1 makes every byte of the game's code int3 (any of it reached stops the
   game, logged), RECOMP_SKIP=name,... keeps those functions on the original. standalone.log lists what happened. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "standalone.h"
#include "../fnsizes.h"

#define GAME_BASE 0x400000u

BOOL WINAPI axisnet_attach(HINSTANCE inst, DWORD reason, LPVOID reserved);   /* axisnet_recomp.c */
int wide_present(void);    /* src/wide.c: the patch layer handed over its widescreen state */
int wide_carries(unsigned addr);   /* the rebuild carries the patch layer's change to that function */

static BYTE g_space[0xb80000 - 0x10000] __attribute__((aligned(4096)));   /* covers GAME_BASE.., see 1. above */
static FILE *g_log;
extern const BYTE g_gamedata[];   /* the game's data (build/gamedata.bin, tools/mkgamedata.py), linked in by build.sh */
static BYTE *g_before;            /* the game's image as mapped, before the patch layer changes anything */
static DWORD g_imageSize;

static void fail(const char *fmt, const char *arg)
{
	char msg[512];
	snprintf(msg, sizeof msg, fmt, arg);
	if (g_log) { fprintf(g_log, "%s\n", msg); fclose(g_log); }
	MessageBoxA(NULL, msg, "AxisRC", MB_ICONERROR);
	ExitProcess(1);
}

static IMAGE_NT_HEADERS32 *nt_of(const BYTE *image) { return (IMAGE_NT_HEADERS32 *)(image + ((IMAGE_DOS_HEADER *)image)->e_lfanew); }

/* the game's image at 0x400000: from the data built into AxisRC.exe (its header, .rdata, .data and the few bytes of
   .text anything reads), or with path from that exe file (AXISRC_IMAGE=1: the whole file, to compare) */
static void map_game(const char *path)
{
	BYTE *file = NULL;
	DWORD fileSize = 0;
	const BYTE *header = g_gamedata + 8;   /* (the first piece: the header) */
	if (path) {
		HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		DWORD got = 0;
		if (h == INVALID_HANDLE_VALUE) fail("cannot open %s", path);
		fileSize = GetFileSize(h, NULL);
		file = VirtualAlloc(NULL, fileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		if (!file || !ReadFile(h, file, fileSize, &got, NULL) || got != fileSize) fail("cannot read %s", path);
		CloseHandle(h);
		header = file;
	}
	IMAGE_NT_HEADERS32 *nt = nt_of(header);
	if (nt->Signature != IMAGE_NT_SIGNATURE || nt->OptionalHeader.ImageBase != GAME_BASE)
		fail("%s is not the expected AxisGL.exe (an image based at 0x400000)", path ? path : "the built-in data");
	BYTE *base = (BYTE *)GAME_BASE;
	DWORD size = g_imageSize = nt->OptionalHeader.SizeOfImage;
	if (g_space > base || g_space + sizeof g_space < base + size)
		fail("AxisRC.exe was linked so that its .bss does not cover the game's address range (%s)", "see build.sh");
	DWORD old;
	VirtualProtect(base, size, PAGE_EXECUTE_READWRITE, &old);
	if (path) {
		memcpy(base, file, nt->OptionalHeader.SizeOfHeaders);
		IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
		for (int i = 0; i < nt->FileHeader.NumberOfSections; i++)
			if (s[i].PointerToRawData + s[i].SizeOfRawData <= fileSize)
				memcpy(base + s[i].VirtualAddress, file + s[i].PointerToRawData, s[i].SizeOfRawData);
		fprintf(g_log, "mapped %s at %#x (%#lx bytes)\n", path, GAME_BASE, size);
	} else {
		DWORD total = 0, pieces = 0;
		for (const BYTE *c = g_gamedata; *(const DWORD *)c; c += 8 + ((const DWORD *)c)[1], pieces++) {
			DWORD at = ((const DWORD *)c)[0], n = ((const DWORD *)c)[1];
			if (at < GAME_BASE || at + n > GAME_BASE + size) fail("the built-in game data is damaged (%s)", "a piece outside the image");
			memcpy((void *)at, c + 8, n);
			total += n;
		}
		fprintf(g_log, "mapped the game's data built into AxisRC.exe at %#x (%lu bytes in %lu pieces; AxisGL.exe not read)\n",
		        GAME_BASE, total, pieces);
	}
	g_before = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!g_before) fail("out of memory (%s)", "the image's copy");
	memcpy(g_before, base, size);
}

static void resolve_imports(void)
{
	IMAGE_NT_HEADERS32 *nt = (IMAGE_NT_HEADERS32 *)(GAME_BASE + ((IMAGE_DOS_HEADER *)GAME_BASE)->e_lfanew);
	IMAGE_DATA_DIRECTORY *d = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	int n = 0;
	for (IMAGE_IMPORT_DESCRIPTOR *imp = (IMAGE_IMPORT_DESCRIPTOR *)(GAME_BASE + d->VirtualAddress); imp->Name; imp++) {
		const char *dll = (const char *)(GAME_BASE + imp->Name);
		HMODULE m = LoadLibraryA(dll);
		if (!m) fail("cannot load %s (a library the game imports)", dll);
		DWORD *names = (DWORD *)(GAME_BASE + (imp->OriginalFirstThunk ? imp->OriginalFirstThunk : imp->FirstThunk));
		DWORD *slots = (DWORD *)(GAME_BASE + imp->FirstThunk);
		for (; *names; names++, slots++, n++) {
			char what[128];
			FARPROC f;
			if (*names & IMAGE_ORDINAL_FLAG32) {
				f = GetProcAddress(m, (LPCSTR)(*names & 0xffff));
				snprintf(what, sizeof what, "%s ordinal %lu", dll, *names & 0xffff);
			} else {
				const char *name = (const char *)((IMAGE_IMPORT_BY_NAME *)(GAME_BASE + *names))->Name;
				f = GetProcAddress(m, name);
				snprintf(what, sizeof what, "%s %s", dll, name);
			}
			if (!f) fail("cannot find %s (imported by the game)", what);
			*slots = (DWORD)f;
		}
	}
	fprintf(g_log, "%d imports resolved\n", n);
}

/* 1 when the code at addr (the whole function, by fnsizes.h) differs from the image as mapped other than where the
   patch DLL may retarget a call the rebuild follows (g_saPatchOk): the patch DLL changed that function in memory,
   so it keeps running (as recomp.c's hook() decides in play) */
static int patched_in_memory(DWORD addr)
{
	int lo = 0, hi = (int)(sizeof g_fnSizes / sizeof g_fnSizes[0]) - 1, k = -1;
	while (lo <= hi) { int mid = (lo + hi) / 2; if (g_fnSizes[mid][0] == addr) { k = mid; break; } if (g_fnSizes[mid][0] < addr) lo = mid + 1; else hi = mid - 1; }
	DWORD size = k >= 0 ? g_fnSizes[k][1] : 5;
	if (addr < GAME_BASE || addr + size > GAME_BASE + g_imageSize)
		return 1;
	const BYTE *before = g_before + (addr - GAME_BASE);
	for (DWORD j = 0; j < size; j++) {
		if (((const BYTE *)addr)[j] == before[j]) continue;
		int ok = 0;
		for (int q = 0; q < g_saNpatchOk && !ok; q++)
			ok = addr + j >= g_saPatchOk[q][0] && addr + j < g_saPatchOk[q][0] + g_saPatchOk[q][1];
		if (!ok) return 1;
	}
	return 0;
}

static int install_hooks(void)
{
	char skip[4096] = ",";
	int n = 0;
	if (!GetEnvironmentVariableA("RECOMP_SKIP", skip + 1, sizeof skip - 2)) skip[1] = 0;
	strcat(skip, ",");
	for (int i = 0; i < g_saNhooks; i++) {
		const SaHook *h = &g_saHooks[i];
		BYTE *p = (BYTE *)h->addr;
		char key[128];
		snprintf(key, sizeof key, ",%s,", h->name);
		/* the same rules as recomp.c's hook() */
		if ((h->addr == 0x41ef90 || h->addr == 0x4926f0) && !wide_present()) {
			fprintf(g_log, "  original %06x %s (the patch layer checks its return address)\n", h->addr, h->name);
			continue;
		}
		int folded = wide_carries(h->addr);
		if (!folded && patched_in_memory(h->addr)) {
			fprintf(g_log, "  original %06x %s (changed in memory by the patch layer)\n", h->addr, h->name);
			continue;
		}
		if (skip[1] && strstr(skip, key)) {
			fprintf(g_log, "  original %06x %s (RECOMP_SKIP)\n", h->addr, h->name);
			continue;
		}
		p[0] = 0xE9;
		*(DWORD *)(p + 1) = (DWORD)h->fn - (h->addr + 5);
		fprintf(g_log, "  rebuilt  %06x %s%s\n", h->addr, h->name, folded ? " (carries the patch layer's fix)" : "");
		n++;
	}
	FlushInstructionCache(GetCurrentProcess(), (void *)GAME_BASE, g_imageSize);
	return n;
}

/* AXISRC_POISON=1 (a check): every byte of the game's own code (its functions from 0x401000 to the MSVC runtime at
   0x49e000 and its packet layer at 0x4a8300 .. 0x4a8740, by fnsizes.h, and the installed exe's patch code at
   0x4a8e20 ..) becomes int3, except the jumps at the rebuilt functions' entries (and
   the patch layer's at movie_playEnding's), and the bytes the rebuilds read (g_saKeep). Any original game code still
   reached then stops the game at once, at its address. */
static char g_logPath[MAX_PATH];
/* where poisoned code was reached: its address and the stack's return-address-like values, into standalone.log */
static LONG CALLBACK poison_hit(EXCEPTION_POINTERS *e)
{
	DWORD at = (DWORD)e->ExceptionRecord->ExceptionAddress, code = e->ExceptionRecord->ExceptionCode;
	int hit = code == EXCEPTION_BREAKPOINT && at >= 0x401000 && at < 0x4a9000;
	if (!hit && code != EXCEPTION_ACCESS_VIOLATION && code != EXCEPTION_ILLEGAL_INSTRUCTION && code != EXCEPTION_PRIV_INSTRUCTION)
		return EXCEPTION_CONTINUE_SEARCH;
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		const DWORD *sp = (const DWORD *)e->ContextRecord->Esp;
		if (hit)
			fprintf(f, "POISONED CODE REACHED at %06lx (esp %08lx); on the stack:", at, (DWORD)sp);
		else
			fprintf(f, "EXCEPTION %08lx at %08lx (data %08lx, esp %08lx); on the stack:", code, at,
			        (DWORD)e->ExceptionRecord->ExceptionInformation[1], (DWORD)sp);
		for (int i = 0; i < 64; i++)
			if ((sp[i] >= 0x401000 && sp[i] < 0x4a9000) || (sp[i] >= 0x10000 && sp[i] < 0x400000))
				fprintf(f, " [%d]%08lx", i, sp[i]);
		fprintf(f, "\n");
		fclose(f);
	}
	TerminateProcess(GetCurrentProcess(), 3);
	return EXCEPTION_CONTINUE_SEARCH;
}

/* (poison mode) the game's ExitProcess, logged with the return addresses on the stack */
static void (WINAPI *g_realExit)(UINT);
static void WINAPI poison_exit(UINT code)
{
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		const DWORD *sp = (const DWORD *)&code - 1;
		fprintf(f, "ExitProcess(%u); on the stack:", code);
		for (int i = 0; i < 400; i++)
			if ((sp[i] >= 0x401000 && sp[i] < 0x4a9000) || (sp[i] >= 0x10000 && sp[i] < 0x400000))
				fprintf(f, " [%d]%08lx", i, sp[i]);
		fprintf(f, "\n");
		fclose(f);
	}
	g_realExit(code);
}

static int poison(void)
{
	AddVectoredExceptionHandler(1, poison_hit);
	g_realExit = *(void (WINAPI **)(UINT))0x4a90f8;
	*(void (WINAPI **)(UINT))0x4a90f8 = poison_exit;
	static const unsigned ranges[][2] = { { 0x401000, 0x49e000 }, { 0x4a8e20, 0x4a9000 }, { 0x4a8300, 0x4a8740 },
	                                      { 0x49e000, 0x4a8300 } };   /* (the last: the C runtime, once replaced) */
	int nranges = g_ncrtEntries ? 4 : 3;
	static BYTE keep[0xa8000];   /* (0x401000 .. 0x4a9000) */
	for (int i = 0; i < g_saNhooks; i++)
		memset(keep + g_saHooks[i].addr - 0x401000, 1, 5);
	memset(keep + 0x46c420 - 0x401000, 1, 5);   /* movie_playEnding: the patch layer's jump to its own player */
	for (int i = 0; i < g_ncrtEntries; i++)
		memset(keep + g_crtEntries[i] - 0x401000, 1, 5);   /* the runtime entries' jumps to msvcrt.dll */
	for (int i = 0; i < g_saNkeep; i++)
		memset(keep + g_saKeep[i][0] - 0x401000, 1, g_saKeep[i][1] - g_saKeep[i][0]);
	/* the compiler's jump thunks (the runtime's static-initializer table points at some: 0x467880 jmp 0x467890):
	   a jmp straight to a rebuilt function's entry only hands over, so it stays */
	static BYTE entry[0xa8000];
	for (int i = 0; i < g_saNhooks; i++)
		entry[g_saHooks[i].addr - 0x401000] = 1;
	int thunks = 0;
	for (unsigned a = 0x401000; a + 5 <= (g_ncrtEntries ? 0x4a8300u : 0x49e000u); a++) {
		unsigned to = a + 5 + *(const int *)(a + 1);
		if (*(const BYTE *)a == 0xE9 && !entry[a - 0x401000] && to >= 0x401000 && to < 0x4a9000 && entry[to - 0x401000]) {
			memset(keep + a - 0x401000, 1, 5);
			thunks++;
		}
	}
	fprintf(g_log, "AXISRC_POISON: %d jumps to rebuilt entries kept\n", thunks);
	/* AXISRC_POISON=2: the rebuilt functions' entry jumps poisoned too, but for the entries something of the
	   original still points at: a word of its data (.rdata, .data: vtables, the start-up tables), a call or jump
	   kept for the patch layer (g_saKeep: the call sites it retargets), a compiler thunk. src/ calls the rebuilt
	   functions directly (AXIS_DIRECT), so any call still made through an original address stops the game there */
	{
		char v[8];
		if (GetEnvironmentVariableA("AXISRC_POISON", v, sizeof v) && !strcmp(v, "2")) {
			static BYTE needed[0xa8000];
			for (unsigned a = 0x4a9000; a + 4 <= 0x4d2000; a += 4) {   /* (the data as built in) */
				unsigned w = *(const unsigned *)(g_before + (a - GAME_BASE));
				if (w >= 0x401000 && w < 0x4a9000)
					needed[w - 0x401000] = 1;
			}
			for (int i = 0; i < g_saNkeep; i++)
				for (unsigned a = g_saKeep[i][0]; a + 5 <= g_saKeep[i][1]; a++)
					if (*(const BYTE *)a == 0xE8 || *(const BYTE *)a == 0xE9) {
						unsigned to = a + 5 + *(const int *)(a + 1);
						if (to >= 0x401000 && to < 0x4a9000)
							needed[to - 0x401000] = 1;
					}
			for (unsigned a = 0x401000; a + 5 <= 0x4a8300; a++)
				if (keep[a - 0x401000] && !entry[a - 0x401000] && *(const BYTE *)a == 0xE9) {
					unsigned to = a + 5 + *(const int *)(a + 1);
					if (to >= 0x401000 && to < 0x4a9000)
						needed[to - 0x401000] = 1;
				}
			int dropped = 0;
			for (int i = 0; i < g_saNhooks; i++)
				if (!needed[g_saHooks[i].addr - 0x401000]) {
					memset(keep + g_saHooks[i].addr - 0x401000, 0, 5);
					dropped++;
				}
			fprintf(g_log, "AXISRC_POISON=2: %d rebuilt entries' jumps poisoned too (nothing of the original points there)\n", dropped);
		}
	}
	int n = 0;
	unsigned lo = 0, hi = 0xffffffff;   /* AXISRC_POISON=lo-hi (hex): only that part (for narrowing a problem down) */
	{ char v[64]; if (GetEnvironmentVariableA("AXISRC_POISON", v, sizeof v) && strchr(v, '-')) { lo = strtoul(v, NULL, 16); hi = strtoul(strchr(v, '-') + 1, NULL, 16); } }
	/* only inside the game's functions (fnsizes.h): .text also holds data between them, e.g. the DirectInput
	   object formats at 0x44f950 that dinput reads (its keyboard set-up failed when they were poisoned) */
	static BYTE code[0xa8000];
	for (int i = 0; i < (int)(sizeof g_fnSizes / sizeof g_fnSizes[0]); i++)
		if ((g_fnSizes[i][0] >= ranges[0][0] && g_fnSizes[i][0] + g_fnSizes[i][1] <= ranges[0][1]) ||
		    (g_fnSizes[i][0] >= 0x4a8300 && g_fnSizes[i][0] + g_fnSizes[i][1] <= 0x4a8740) ||   /* (the packet layer, after the runtime) */
		    (g_ncrtEntries && g_fnSizes[i][0] >= 0x49e000 && g_fnSizes[i][0] + g_fnSizes[i][1] <= 0x4a8300))   /* (the runtime) */
			memset(code + g_fnSizes[i][0] - 0x401000, 1, g_fnSizes[i][1]);
	memset(code + ranges[1][0] - 0x401000, 1, ranges[1][1] - ranges[1][0]);
	for (int r = 0; r < nranges; r++)
		for (unsigned a = ranges[r][0]; a < ranges[r][1]; a++)
			if (code[a - 0x401000] && !keep[a - 0x401000] && a >= lo && a < hi) {
				*(BYTE *)a = 0xCC;
				n++;
			}
	FlushInstructionCache(GetCurrentProcess(), (void *)0x401000, 0xa8000);
	return n;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	char dir[MAX_PATH], path[MAX_PATH];
	(void)prev; (void)cmd; (void)show;
	GetModuleFileNameA(NULL, dir, sizeof dir);
	*(strrchr(dir, '\\') + 1) = 0;
	snprintf(path, sizeof path, "%sstandalone.log", dir);
	strcpy(g_logPath, path);
	g_log = fopen(path, "w");
	if (!g_log) fail("cannot write %s", path);
	snprintf(path, sizeof path, "%sAxisGL.exe", dir);
	map_game(GetEnvironmentVariableA("AXISRC_IMAGE", NULL, 0) ? path : NULL);
	resolve_imports();
	axisnet_attach(inst, DLL_PROCESS_ATTACH, NULL);
	{	/* what the patch layer changed in the game's code (to compare the built-in data with the exe file) */
		DWORD n = 0, hash = 2166136261u;
		for (DWORD a = 0x1000; a < 0xa9000; a++)
			if (((BYTE *)GAME_BASE)[a] != g_before[a]) {
				n++;
				hash = (hash ^ a ^ ((BYTE *)GAME_BASE)[a] << 24) * 16777619u;
			}
		int wide_fixes(void);
		fprintf(g_log, "patch layer started (widescreen state %s; fixes %x; %lu code bytes changed, hash %08lx)\n",
		        wide_present() ? "handed over" : "MISSING", wide_fixes(), n, hash);
	}
	int n = install_hooks();
	fprintf(g_log, "%d of %d rebuilt functions switched in; starting the game\n", n, g_saNhooks);
	if (!GetEnvironmentVariableA("AXISRC_GAMECRT", NULL, 0)) {
		int n = 0;
		const char *missing = crt_install(&n);
		if (missing)
			fail("msvcrt.dll has no %s (needed for the game's C runtime)", missing);
		fprintf(g_log, "the game's C runtime replaced by msvcrt.dll's (%d entries)\n", n);
	}
	if (GetEnvironmentVariableA("AXISRC_POISON", NULL, 0))
		fprintf(g_log, "AXISRC_POISON: %d bytes of the game's own code made int3\n", poison());
	{	/* the x87 control word the game runs with: Windows starts every thread at 0x027f (53-bit precision), and the
		   game's runtime never changes it (only __ftol, for a moment); MinGW's start-up code in this exe set 0x037f
		   (64-bit), which would round the game's x87 maths differently from the original */
		unsigned short cw = 0x027f, now;
		__asm__ volatile("fnstcw %0" : "=m"(now));
		__asm__ volatile("fldcw %0" : : "m"(cw));
		fprintf(g_log, "x87 control word %04x for the game (was %04x)\n", cw, now);
	}
	fclose(g_log);
	g_log = NULL;
	if (g_ncrtEntries)
		crt_start();
	else
		((void (*)(void))(GAME_BASE + nt_of((const BYTE *)GAME_BASE)->OptionalHeader.AddressOfEntryPoint))();   /* the game's own runtime start-up */
	return 0;   /* (the game's runtime ends the process itself) */
}
