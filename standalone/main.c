/* main.c: AxisRC.exe, the rebuilt game as a program of its own (PRIVATE; never ship).

   AxisRC.exe holds every rebuilt function (src/, compiled with AXIS_DIRECT: they call each other directly), the patch
   DLL's fixes (axisnet_recomp.c, compiled in with AXIS_STANDALONE), the game's data as C (src/data/) and the few
   bytes of AxisGL.exe it still reads (build/gamedata.bin: the header and some code bytes, tools/mkgamedata.py). It
   runs from the game folder (for the game's Data, Map, Sound... files) without reading or changing AxisGL.exe:

   1. the game's image (what the original kept at 0x400000 .. 0xb6b000) is built in g_image, an array of this exe:
      the header and code bytes from gamedata.bin, the data from src/data. The rebuilt code reaches it through
      IMG() / RELOC() (src/axis.h), so nothing needs the original addresses: that range is reserved (g_space; the
      exe is linked at 0x10000 with ASLR off, see build.sh) and left inaccessible, and an access to it stops the
      game with the address logged (guard_hit);
   2. the game's imports are looked up and written into its import table, which the rebuilt code calls through;
   3. the patch DLL's start-up runs (axisnet_attach: it hooks the game's DirectPlay/ping/OpenGL imports and makes the
      changes the rebuilds follow);
   4. every rebuilt function's original entry gets a jump to it, for what still reaches an entry through the image
      (the patch DLL's retargeted call sites; AXISRC_POISON=2 shows how little);
   5. the game's C runtime is replaced (crt.c: msvcrt.dll, and src/crt/ where VC6's results differ);
   6. the x87 control word Windows gives the game is set, and crt.c's start-up runs the game: its static
      constructors, the rebuilt WinMain, exit.

   AXISRC_POISON=1 makes every byte of the game's code in the image int3 (any of it reached stops the game, logged;
   =2 the rebuilt functions' entries too), AXISRC_DATACHECK=1 compares the image with AxisGL.exe, RECOMP_SKIP=name,...
   leaves those functions' entries without their jump. standalone.log lists what happened. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "standalone.h"
#include "../fnsizes.h"

BOOL WINAPI axisnet_attach(HINSTANCE inst, DWORD reason, LPVOID reserved);   /* axisnet_recomp.c */
int wide_present(void);    /* src/wide.c: the patch layer handed over its widescreen state */
int wide_carries(unsigned addr);   /* the rebuild carries the patch layer's change to that function */

/* g_space: AxisRC.exe's .bss from below GAME_BASE (the exe is linked at 0x10000, see build.sh) to past the
   original's range: that range stays reserved (kept inaccessible, see 1. above) and the game's image, g_image,
   lies in it right after (at the fixed address 0xb6b000 = GAME_BASE + GAME_SIZE: a link-time symbol, as src/data's
   IMG() words need; the exe has no ASLR anyway) */
static BYTE g_space[GAME_BASE + 2 * GAME_SIZE - 0x10000] __attribute__((aligned(4096)));
__asm__(".globl _g_image\n\t.set _g_image, 0xb6b000");
static FILE *g_log;
static char g_logPath[MAX_PATH];
extern const BYTE g_gamedata[];   /* the header and code bytes (build/gamedata.bin, tools/mkgamedata.py), linked in by build.sh */
static BYTE *g_before;            /* the game's image as built, before the patch layer changes anything */

static void fail(const char *fmt, const char *arg)
{
	char msg[512];
	snprintf(msg, sizeof msg, fmt, arg);
	if (g_log) { fprintf(g_log, "%s\n", msg); fclose(g_log); }
	MessageBoxA(NULL, msg, "AxisRC", MB_ICONERROR);
	ExitProcess(1);
}

static IMAGE_NT_HEADERS32 *nt_of(const BYTE *image) { return (IMAGE_NT_HEADERS32 *)(image + ((IMAGE_DOS_HEADER *)image)->e_lfanew); }

/* an address of the relocated image as the original's (for the log), else as it is */
static DWORD original(DWORD a)
{
	if (a - (DWORD)g_rdata < 0x4000) return a - (DWORD)g_rdata + 0x4a9000;
	if (a - (DWORD)g_data < 0x666000) return a - (DWORD)g_data + 0x4ad000;
	return a - (DWORD)g_image < GAME_SIZE ? a - (DWORD)g_image + GAME_BASE : a;
}
/* the return-address-like values on a stack: in AxisRC.exe's own code, or in the image's (as original addresses) */
static void log_stack(FILE *f, const DWORD *sp, int words)
{
	for (int i = 0; i < words; i++)
		if ((sp[i] >= 0x10000 && sp[i] < GAME_BASE) || (sp[i] >= (DWORD)AT(0x401000) && sp[i] < (DWORD)AT(0x4a9000)))
			fprintf(f, " [%d]%08lx", i, original(sp[i]));
}

/* the guard: an access to the original range (where nothing is now) - an address the rebuilt code or the patch layer
   still uses as it was, missed by IMG / RELOC. Logged with where it happened, and the game stopped */
static LONG CALLBACK guard_hit(EXCEPTION_POINTERS *e)
{
	DWORD code = e->ExceptionRecord->ExceptionCode, at = (DWORD)e->ExceptionRecord->ExceptionAddress;
	DWORD data = code == EXCEPTION_ACCESS_VIOLATION ? (DWORD)e->ExceptionRecord->ExceptionInformation[1] : 0;
	int moved = data - (DWORD)(g_image + 0xa9000) < 0x66a000;   /* (g_image's data part, now g_rdata / g_data) */
	if (data - GAME_BASE >= GAME_SIZE && at - GAME_BASE >= GAME_SIZE && !moved)
		return EXCEPTION_CONTINUE_SEARCH;
	if (g_log)
		fflush(g_log);
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		fprintf(f, "ORIGINAL ADDRESS USED: %s %08lx at %08lx (esp %08lx); on the stack:",
		        data - GAME_BASE < GAME_SIZE ? (e->ExceptionRecord->ExceptionInformation[0] ? "writing" : "reading") : "executing",
		        data - GAME_BASE < GAME_SIZE ? data : at, original(at), e->ContextRecord->Esp);
		log_stack(f, (const DWORD *)e->ContextRecord->Esp, 64);
		fprintf(f, "\n");
		fclose(f);
	}
	TerminateProcess(GetCurrentProcess(), 4);
	return EXCEPTION_CONTINUE_SEARCH;
}

/* a line appended to standalone.log after start-up (crt.c's start-up logs its steps) */
void sa_log(const char *fmt, int arg)
{
	FILE *f = fopen(g_logPath, "a");
	if (f) { fprintf(f, fmt, arg); fprintf(f, "\n"); fclose(f); }
}

/* AXISRC_WATCH=<original address> (a check): every write to that word of the image logged with where it came from
   (a hardware breakpoint, debug register 0, on the main thread) */
static int g_watchHits;
static LONG CALLBACK watch_hit(EXCEPTION_POINTERS *e)
{
	if (e->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP || !(e->ContextRecord->Dr6 & 1))
		return EXCEPTION_CONTINUE_SEARCH;
	e->ContextRecord->Dr6 = 0;
	if (g_watchHits++ < 12) {
		FILE *f = fopen(g_logPath, "a");
		if (f) {
			fprintf(f, "WATCH: %08lx written (now %08lx) by the code before %08lx; on the stack:", original(e->ContextRecord->Dr0),
			        *(DWORD *)e->ContextRecord->Dr0, original((DWORD)e->ExceptionRecord->ExceptionAddress));
			log_stack(f, (const DWORD *)e->ContextRecord->Esp, 48);
			fprintf(f, "\n");
			fclose(f);
		}
	}
	return EXCEPTION_CONTINUE_EXECUTION;
}
static void watch(DWORD original_addr)
{
	CONTEXT c;
	memset(&c, 0, sizeof c);
	c.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	GetThreadContext(GetCurrentThread(), &c);
	c.Dr0 = (DWORD)AT(original_addr);
	c.Dr7 = (c.Dr7 & ~0xf0003u) | 1 | (1u << 16) | (3u << 18);   /* L0, write, 4 bytes */
	c.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	AddVectoredExceptionHandler(1, watch_hit);
	fprintf(g_log, "AXISRC_WATCH: writes to %08lx watched (%s)\n", original_addr,
	        SetThreadContext(GetCurrentThread(), &c) ? "set" : "FAILED");
}

/* any other crash: logged with where it happened (the process then ends as Windows ends it) */
static LONG WINAPI crash_hit(EXCEPTION_POINTERS *e)
{
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		fprintf(f, "CRASH: exception %08lx at %08lx (data %08lx, esp %08lx); on the stack:", e->ExceptionRecord->ExceptionCode,
		        original((DWORD)e->ExceptionRecord->ExceptionAddress), (DWORD)e->ExceptionRecord->ExceptionInformation[1],
		        e->ContextRecord->Esp);
		log_stack(f, (const DWORD *)e->ContextRecord->Esp, 64);
		fprintf(f, "\n  (eax %08lx ecx %08lx edx %08lx esi %08lx edi %08lx; DirectInput %08lx keyboard %08lx mouse %08lx)\n",
		        e->ContextRecord->Eax, e->ContextRecord->Ecx, e->ContextRecord->Edx, e->ContextRecord->Esi, e->ContextRecord->Edi,
		        *(DWORD *)AT(0x4d1e98), *(DWORD *)AT(0x4d1fa0), *(DWORD *)AT(0x4d1fa4));
		fclose(f);
	}
	return EXCEPTION_CONTINUE_SEARCH;
}

/* a piece of the game's data as C (src/data/data.h; tools/mkdatasrc.py) */
typedef struct { DWORD address; const void *bytes; DWORD size; } DataPiece;
extern const DataPiece g_rdataPieces[], g_dataPieces[], g_text_dataPieces[];

/* AXISRC_DATACHECK=1 (a check): the image as built compared with the exe file (path) over .rdata, .data and src/data's
   pieces in .text, before the patch layer changes anything. A word may only differ where the file has a rebuilt
   function's address (or a jump stub's to one) and the image that function's own, or where the file has an address
   of the image and the image the same address relocated (src/data's IMG words) */
static void data_check(const char *path)
{
	HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if (h == INVALID_HANDLE_VALUE) { fprintf(g_log, "AXISRC_DATACHECK: cannot open %s\n", path); return; }
	DWORD size = GetFileSize(h, NULL), got = 0;
	BYTE *file = VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	ReadFile(h, file, size, &got, NULL);
	CloseHandle(h);
	IMAGE_NT_HEADERS32 *nt = nt_of(file);
	IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
	DWORD same = 0, functions = 0, relocated = 0, bad = 0;
	for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
		DWORD va = GAME_BASE + s[i].VirtualAddress, n = s[i].SizeOfRawData < s[i].Misc.VirtualSize ? s[i].SizeOfRawData : s[i].Misc.VirtualSize;
		const BYTE *in = file + s[i].PointerToRawData;
		if (!memcmp(s[i].Name, ".text", 6)) {   /* (of .text only src/data's pieces: words in them may be relocated) */
			for (const DataPiece *p = g_text_dataPieces; p->address; p++)
				for (DWORD a = p->address; a < p->address + p->size && p->address >= va && p->address < va + n;) {
					DWORD want = 0, have = 0;
					if (a + 4 <= p->address + p->size) {
						want = *(const DWORD *)(in + (a - va)); have = *(const DWORD *)AT(a);
						if (want - 0x401000 < 0xb6b000 - 0x401000 && have == (DWORD)AT(want)) { relocated++; a += 4; continue; }
					}
					if (*AT(a) == in[a - va]) { same++; a++; continue; }
					if (bad++ < 20)
						fprintf(g_log, "AXISRC_DATACHECK: %08lx (.text) is %02x, the exe has %02x\n", a, *AT(a), in[a - va]);
					a++;
				}
			continue;
		}
		if (memcmp(s[i].Name, ".rdata", 7) && memcmp(s[i].Name, ".data", 6))
			continue;
		for (DWORD a = va; a < va + n; a += 4) {
			DWORD want = *(const DWORD *)(in + (a - va)), have = *(const DWORD *)AT(a);
			if (have == want) { same++; continue; }
			int ok = 0;
			for (int k = 0; k < g_saNhooks && !ok; k++)
				ok = g_saHooks[k].addr == want && (DWORD)g_saHooks[k].fn == have;
			if (ok) { functions++; continue; }
			if (want - 0x401000 < 0xb6b000 - 0x401000 && have == (DWORD)AT(want)) { relocated++; continue; }
			if (bad++ < 20)
				fprintf(g_log, "AXISRC_DATACHECK: %08lx is %08lx, the exe has %08lx\n", a, have, want);
		}
	}
	fprintf(g_log, "AXISRC_DATACHECK: %lu words the same, %lu a rebuilt function's own address, %lu addresses relocated, "
	        "%lu different\n", same, functions, relocated, bad);
	VirtualFree(file, 0, MEM_RELEASE);
}

/* the game's image in g_image: the header and code bytes built into AxisRC.exe, then src/data's pieces */
static void map_game(void)
{
	if ((BYTE *)g_space > (BYTE *)GAME_BASE || (BYTE *)g_space + sizeof g_space < g_image + GAME_SIZE || g_image != (BYTE *)(GAME_BASE + GAME_SIZE))
		fail("AxisRC.exe was linked so that g_space does not hold the original's range and g_image (%s)", "see build.sh");
	IMAGE_NT_HEADERS32 *nt = nt_of(g_gamedata + 8);   /* (the first piece: the header) */
	if (nt->Signature != IMAGE_NT_SIGNATURE || nt->OptionalHeader.ImageBase != GAME_BASE || nt->OptionalHeader.SizeOfImage != GAME_SIZE)
		fail("the built-in data is not the expected AxisGL.exe's (%s)", "an image of 0x76b000 bytes at 0x400000");
	DWORD old;
	VirtualProtect(g_image, GAME_SIZE, PAGE_EXECUTE_READWRITE, &old);   /* (the entry jumps run there) */
	DWORD total = 0, pieces = 0;
	for (const BYTE *c = g_gamedata; *(const DWORD *)c; c += 8 + ((const DWORD *)c)[1], pieces++) {
		DWORD at = ((const DWORD *)c)[0], n = ((const DWORD *)c)[1];
		if (at - GAME_BASE >= GAME_SIZE || at + n - GAME_BASE > GAME_SIZE) fail("the built-in game data is damaged (%s)", "a piece outside the image");
		memcpy(AT(at), c + 8, n);
		total += n;
	}
	fprintf(g_log, "the game's image at %p (0x%x in the original): header and code bytes, %lu bytes in %lu pieces "
	        "(AxisGL.exe not read)\n", (void *)g_image, GAME_BASE, total, pieces);
	/* the game's data, as C (src/data/, tools/mkdatasrc.py): .rdata, .data, the data kept in .text */
	const DataPiece *tables[3] = { g_rdataPieces, g_dataPieces, g_text_dataPieces };
	total = pieces = 0;
	for (int t = 0; t < 3; t++)
		for (const DataPiece *p = tables[t]; p->address; p++, pieces++) {
			if (p->address - GAME_BASE >= GAME_SIZE || p->address + p->size - GAME_BASE > GAME_SIZE)
				fail("src/data has a piece outside the image (%s)", "tools/mkdatasrc.py");
			memcpy(AT(p->address), p->bytes, p->size);
			total += p->size;
		}
	fprintf(g_log, "the game's data from src/data: %lu bytes in %lu pieces\n", total, pieces);
	g_before = VirtualAlloc(NULL, GAME_SIZE, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!g_before) fail("out of memory (%s)", "the image's copy");
	for (DWORD o = 0; o < GAME_SIZE; o += 0x1000)   /* (in the original's layout: from g_image, g_rdata, g_data) */
		memcpy(g_before + o, AT(GAME_BASE + o), 0x1000);
}

static void resolve_imports(void)
{
	IMAGE_NT_HEADERS32 *nt = nt_of(g_image);
	IMAGE_DATA_DIRECTORY *d = &nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	int n = 0;
	for (IMAGE_IMPORT_DESCRIPTOR *imp = (IMAGE_IMPORT_DESCRIPTOR *)AT(GAME_BASE + d->VirtualAddress); imp->Name; imp++) {
		const char *dll = (const char *)AT(GAME_BASE + imp->Name);
		HMODULE m = LoadLibraryA(dll);
		if (!m) fail("cannot load %s (a library the game imports)", dll);
		DWORD *names = (DWORD *)AT(GAME_BASE + (imp->OriginalFirstThunk ? imp->OriginalFirstThunk : imp->FirstThunk));
		DWORD *slots = (DWORD *)AT(GAME_BASE + imp->FirstThunk);
		for (; *names; names++, slots++, n++) {
			char what[128];
			FARPROC f;
			if (*names & IMAGE_ORDINAL_FLAG32) {
				f = GetProcAddress(m, (LPCSTR)(*names & 0xffff));
				snprintf(what, sizeof what, "%s ordinal %lu", dll, *names & 0xffff);
			} else {
				const char *name = (const char *)((IMAGE_IMPORT_BY_NAME *)AT(GAME_BASE + *names))->Name;
				f = GetProcAddress(m, name);
				snprintf(what, sizeof what, "%s %s", dll, name);
			}
			if (!f) fail("cannot find %s (imported by the game)", what);
			*slots = (DWORD)f;
		}
	}
	fprintf(g_log, "%d imports resolved\n", n);
}

/* 1 when the code at addr (the whole function, by fnsizes.h) differs from the image as built other than where the
   patch DLL may retarget a call the rebuild follows (g_saPatchOk): the patch DLL changed that function in memory,
   so it keeps running (as recomp.c's hook() decides in play) */
static int patched_in_memory(DWORD addr)
{
	int lo = 0, hi = (int)(sizeof g_fnSizes / sizeof g_fnSizes[0]) - 1, k = -1;
	while (lo <= hi) { int mid = (lo + hi) / 2; if (g_fnSizes[mid][0] == addr) { k = mid; break; } if (g_fnSizes[mid][0] < addr) lo = mid + 1; else hi = mid - 1; }
	DWORD size = k >= 0 ? g_fnSizes[k][1] : 5;
	if (addr - GAME_BASE >= GAME_SIZE || addr + size - GAME_BASE > GAME_SIZE)
		return 1;
	const BYTE *before = g_before + (addr - GAME_BASE);
	for (DWORD j = 0; j < size; j++) {
		if (AT(addr)[j] == before[j]) continue;
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
		BYTE *p = AT(h->addr);
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
		*(DWORD *)(p + 1) = (DWORD)h->fn - ((DWORD)p + 5);
		fprintf(g_log, "  rebuilt  %06x %s%s\n", h->addr, h->name, folded ? " (carries the patch layer's fix)" : "");
		n++;
	}
	FlushInstructionCache(GetCurrentProcess(), g_image, GAME_SIZE);
	return n;
}

/* AXISRC_POISON=1 (a check): every byte of the game's own code in the image (its functions from 0x401000 to the MSVC
   runtime at 0x49e000 and its packet layer at 0x4a8300 .. 0x4a8740, by fnsizes.h, and the installed exe's patch code
   at 0x4a8e20 ..) becomes int3, except the jumps at the rebuilt functions' entries (and the patch layer's at
   movie_playEnding's), and the bytes the rebuilds read (g_saKeep). Any original game code still reached then stops
   the game at once, at its address. */
static LONG CALLBACK poison_hit(EXCEPTION_POINTERS *e)
{
	DWORD at = (DWORD)e->ExceptionRecord->ExceptionAddress, code = e->ExceptionRecord->ExceptionCode;
	int hit = code == EXCEPTION_BREAKPOINT && at >= (DWORD)AT(0x401000) && at < (DWORD)AT(0x4a9000);
	if (!hit && code != EXCEPTION_ACCESS_VIOLATION && code != EXCEPTION_ILLEGAL_INSTRUCTION && code != EXCEPTION_PRIV_INSTRUCTION)
		return EXCEPTION_CONTINUE_SEARCH;
	FILE *f = fopen(g_logPath, "a");
	if (f) {
		const DWORD *sp = (const DWORD *)e->ContextRecord->Esp;
		if (hit)
			fprintf(f, "POISONED CODE REACHED at %06lx (esp %08lx); on the stack:", original(at), (DWORD)sp);
		else
			fprintf(f, "EXCEPTION %08lx at %08lx (data %08lx, esp %08lx); on the stack:", code, original(at),
			        (DWORD)e->ExceptionRecord->ExceptionInformation[1], (DWORD)sp);
		log_stack(f, sp, 64);
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
		fprintf(f, "ExitProcess(%u); on the stack:", code);
		log_stack(f, (const DWORD *)&code - 1, 400);
		fprintf(f, "\n");
		fclose(f);
	}
	g_realExit(code);
}

static int poison(void)
{
	AddVectoredExceptionHandler(1, poison_hit);
	g_realExit = *(void (WINAPI **)(UINT))AT(0x4a90f8);
	*(void (WINAPI **)(UINT))AT(0x4a90f8) = poison_exit;
	static const unsigned ranges[][2] = { { 0x401000, 0x49e000 }, { 0x4a8e20, 0x4a9000 }, { 0x4a8300, 0x4a8740 },
	                                      { 0x49e000, 0x4a8300 } };   /* (the last: the C runtime, replaced) */
	int nranges = 4;
	static BYTE keep[0xa8000];   /* (0x401000 .. 0x4a9000) */
	for (int i = 0; i < g_saNhooks; i++)
		memset(keep + g_saHooks[i].addr - 0x401000, 1, 5);
	memset(keep + 0x46c420 - 0x401000, 1, 5);   /* movie_playEnding: the patch layer's jump to its own player */
	for (int i = 0; i < g_ncrtEntries; i++)
		memset(keep + g_crtEntries[i] - 0x401000, 1, 5);   /* the runtime entries' jumps to msvcrt.dll */
	for (int i = 0; i < g_saNkeep; i++)
		memset(keep + g_saKeep[i][0] - 0x401000, 1, g_saKeep[i][1] - g_saKeep[i][0]);
	/* the compiler's jump thunks (the runtime's static-initializer table points at some: 0x467880 jmp 0x467890):
	   a jmp straight to a rebuilt function's entry only hands over, so it stays (rel32s between two places of the
	   image are the same relocated) */
	static BYTE entry[0xa8000];
	for (int i = 0; i < g_saNhooks; i++)
		entry[g_saHooks[i].addr - 0x401000] = 1;
	int thunks = 0;
	for (unsigned a = 0x401000; a + 5 <= 0x4a8300u; a++) {
		unsigned to = a + 5 + *(const int *)AT(a + 1);
		if (*AT(a) == 0xE9 && !entry[a - 0x401000] && to >= 0x401000 && to < 0x4a9000 && entry[to - 0x401000]) {
			memset(keep + a - 0x401000, 1, 5);
			thunks++;
		}
	}
	fprintf(g_log, "AXISRC_POISON: %d jumps to rebuilt entries kept\n", thunks);
	/* AXISRC_POISON=2: the rebuilt functions' entry jumps poisoned too, but for the entries something of the
	   original still points at: a word of its data as built (an original code address there), a call or jump kept
	   for the patch layer (g_saKeep: the call sites it retargets), a compiler thunk. src/ calls the rebuilt
	   functions directly (AXIS_DIRECT), so any call still made through an original entry stops the game there */
	{
		char v[8];
		if (GetEnvironmentVariableA("AXISRC_POISON", v, sizeof v) && !strcmp(v, "2")) {
			static BYTE needed[0xa8000];
			for (unsigned a = 0x4a9000; a + 4 <= 0x4d2000; a += 4) {
				unsigned w = original(*(const unsigned *)(g_before + (a - GAME_BASE)));
				if (w >= 0x401000 && w < 0x4a9000)
					needed[w - 0x401000] = 1;
			}
			for (int i = 0; i < g_saNkeep; i++)
				for (unsigned a = g_saKeep[i][0]; a + 5 <= g_saKeep[i][1]; a++)
					if (*AT(a) == 0xE8 || *AT(a) == 0xE9) {
						unsigned to = a + 5 + *(const int *)AT(a + 1);
						if (to >= 0x401000 && to < 0x4a9000)
							needed[to - 0x401000] = 1;
					}
			for (unsigned a = 0x401000; a + 5 <= 0x4a8300; a++)
				if (keep[a - 0x401000] && !entry[a - 0x401000] && *AT(a) == 0xE9) {
					unsigned to = a + 5 + *(const int *)AT(a + 1);
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
		    (g_fnSizes[i][0] >= 0x49e000 && g_fnSizes[i][0] + g_fnSizes[i][1] <= 0x4a8300))     /* (the runtime) */
			memset(code + g_fnSizes[i][0] - 0x401000, 1, g_fnSizes[i][1]);
	memset(code + ranges[1][0] - 0x401000, 1, ranges[1][1] - ranges[1][0]);
	for (int r = 0; r < nranges; r++)
		for (unsigned a = ranges[r][0]; a < ranges[r][1]; a++)
			if (code[a - 0x401000] && !keep[a - 0x401000] && a >= lo && a < hi) {
				*AT(a) = 0xCC;
				n++;
			}
	FlushInstructionCache(GetCurrentProcess(), AT(0x401000), 0xa8000);
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
	map_game();
	if (GetEnvironmentVariableA("AXISRC_DATACHECK", NULL, 0))
		data_check(path);
	/* the original's range, kept free by g_space, made inaccessible: nothing of the game may use it now */
	DWORD old;
	if (!VirtualProtect((void *)GAME_BASE, GAME_SIZE, PAGE_NOACCESS, &old))
		fail("cannot protect the original's range (%s)", "VirtualProtect");
	AddVectoredExceptionHandler(1, guard_hit);
	SetUnhandledExceptionFilter(crash_hit);
	/* and g_image's own .rdata / .data part: those are g_rdata / g_data now, so nothing may use the copy's place */
	if (!VirtualProtect(g_image + 0xa9000, 0xb13000 - 0x4a9000, PAGE_NOACCESS, &old))
		fail("cannot protect g_image's data part (%s)", "VirtualProtect");
	fprintf(g_log, "the original's range 0x%x .. 0x%x and g_image's data part left inaccessible (guarded); "
	        "the data in g_rdata %p, g_data %p\n", GAME_BASE, GAME_BASE + GAME_SIZE, (void *)g_rdata, (void *)g_data);
	resolve_imports();
	axisnet_attach(inst, DLL_PROCESS_ATTACH, NULL);
	{	/* what the patch layer changed in the game's code (to compare the built-in data with the exe file) */
		DWORD n = 0, hash = 2166136261u;
		for (DWORD a = 0x1000; a < 0xa9000; a++)
			if (g_image[a] != g_before[a]) {
				n++;
				hash = (hash ^ a ^ g_image[a] << 24) * 16777619u;
			}
		int wide_fixes(void);
		fprintf(g_log, "patch layer started (widescreen state %s; fixes %x; %lu code bytes changed, hash %08lx)\n",
		        wide_present() ? "handed over" : "MISSING", wide_fixes(), n, hash);
	}
	int n = install_hooks();
	fprintf(g_log, "%d of %d rebuilt functions switched in; starting the game\n", n, g_saNhooks);
	{
		int n = 0;
		const char *missing = crt_install(&n);
		if (missing)
			fail("msvcrt.dll has no %s (needed for the game's C runtime)", missing);
		fprintf(g_log, "the game's C runtime replaced by msvcrt.dll's (%d entries)\n", n);
	}
	if (GetEnvironmentVariableA("AXISRC_POISON", NULL, 0))
		fprintf(g_log, "AXISRC_POISON: %d bytes of the game's own code made int3\n", poison());
	{
		char v[16];
		if (GetEnvironmentVariableA("AXISRC_WATCH", v, sizeof v))
			watch(strtoul(v, NULL, 16));
	}
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
	crt_start();
	return 0;   /* (the game's runtime ends the process itself) */
}
