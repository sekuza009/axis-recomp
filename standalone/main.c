/* main.c: AxisRC.exe, the rebuilt game as a program of its own (PRIVATE; never ship).

   AxisRC.exe holds every rebuilt function (src/, the same objects recomp.dll is linked from) and the patch DLL's
   fixes (axisnet_recomp.c, compiled in with AXIS_STANDALONE). It does not change or inject into the installed game:
   it reads AxisGL.exe from its own folder as data, and does there what Windows' loader would do for it:

   1. the game's sections go to 0x400000, their own address (the game has no relocations). That range is a zeroed
      array in AxisRC.exe's .bss (g_space; the exe is linked at 0x10000 with ASLR off, see build.sh): memory the
      process allocates at start-up (stack, heaps, mapped files) would otherwise sit there;
   2. the game's imports are looked up and written into its import table, which the rebuilt code calls through;
   3. the patch DLL's start-up runs (axisnet_attach: it hooks the game's DirectPlay/ping/OpenGL imports and patches
      the code it fixes);
   4. every rebuilt function is switched in at its original's address (a jump, as recomp.dll does in play), so the
      game's remaining original code (the MSVC runtime and the few functions the patch DLL rewrites) and its
      function tables reach the rebuilds;
   5. the game's entry point (the MSVC runtime's start-up) runs, which calls the rebuilt WinMain.

   What runs from the game file is then its data and the code that is not rebuilt; standalone.log next to the exe
   lists every function and where it runs from. RECOMP_SKIP=name,name,... keeps those on the original. */
#include <windows.h>
#include <stdio.h>
#include <string.h>
#include "standalone.h"
#include "../fnsizes.h"

#define GAME_BASE 0x400000u

BOOL WINAPI axisnet_attach(HINSTANCE inst, DWORD reason, LPVOID reserved);   /* axisnet_recomp.c */
int wide_present(void);    /* src/wide.c: the patch layer handed over its widescreen state */
int wide_menuFix(void);

static BYTE g_space[0xb80000 - 0x10000] __attribute__((aligned(4096)));   /* covers GAME_BASE.., see 1. above */
static BYTE *g_file;       /* AxisGL.exe as read */
static DWORD g_fileSize;
static FILE *g_log;

static void fail(const char *fmt, const char *arg)
{
	char msg[512];
	snprintf(msg, sizeof msg, fmt, arg);
	if (g_log) { fprintf(g_log, "%s\n", msg); fclose(g_log); }
	MessageBoxA(NULL, msg, "AxisRC", MB_ICONERROR);
	ExitProcess(1);
}

static IMAGE_NT_HEADERS32 *file_nt(void) { return (IMAGE_NT_HEADERS32 *)(g_file + ((IMAGE_DOS_HEADER *)g_file)->e_lfanew); }

static void map_game(const char *path)
{
	HANDLE h = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	DWORD got = 0;
	if (h == INVALID_HANDLE_VALUE) fail("cannot open %s", path);
	g_fileSize = GetFileSize(h, NULL);
	g_file = VirtualAlloc(NULL, g_fileSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (!g_file || !ReadFile(h, g_file, g_fileSize, &got, NULL) || got != g_fileSize) fail("cannot read %s", path);
	CloseHandle(h);
	IMAGE_NT_HEADERS32 *nt = file_nt();
	if (nt->Signature != IMAGE_NT_SIGNATURE || nt->OptionalHeader.ImageBase != GAME_BASE)
		fail("%s is not the expected AxisGL.exe (an image based at 0x400000)", path);
	BYTE *base = (BYTE *)GAME_BASE;
	DWORD size = nt->OptionalHeader.SizeOfImage;
	if (g_space > base || g_space + sizeof g_space < base + size)
		fail("AxisRC.exe was linked so that its .bss does not cover the game's address range (%s)", "see build.sh");
	DWORD old;
	VirtualProtect(base, size, PAGE_EXECUTE_READWRITE, &old);
	memcpy(base, g_file, nt->OptionalHeader.SizeOfHeaders);
	IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
	for (int i = 0; i < nt->FileHeader.NumberOfSections; i++)
		if (s[i].PointerToRawData + s[i].SizeOfRawData <= g_fileSize)
			memcpy(base + s[i].VirtualAddress, g_file + s[i].PointerToRawData, s[i].SizeOfRawData);
	fprintf(g_log, "mapped %s at %#x (%#lx bytes)\n", path, GAME_BASE, size);
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

/* 1 when the code at addr (the whole function, by fnsizes.h) differs from the game file other than where the
   patch DLL may retarget a call the rebuild follows (g_saPatchOk): the patch DLL changed that function in memory,
   so it keeps running (as recomp.c's hook() decides in play) */
static int patched_in_memory(DWORD addr)
{
	int lo = 0, hi = (int)(sizeof g_fnSizes / sizeof g_fnSizes[0]) - 1, k = -1;
	while (lo <= hi) { int mid = (lo + hi) / 2; if (g_fnSizes[mid][0] == addr) { k = mid; break; } if (g_fnSizes[mid][0] < addr) lo = mid + 1; else hi = mid - 1; }
	DWORD size = k >= 0 ? g_fnSizes[k][1] : 5;
	IMAGE_NT_HEADERS32 *nt = file_nt();
	IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
	DWORD rva = addr - GAME_BASE;
	for (int i = 0; i < nt->FileHeader.NumberOfSections; i++, s++)
		if (rva >= s->VirtualAddress && rva + size <= s->VirtualAddress + s->SizeOfRawData) {
			const BYTE *file = g_file + s->PointerToRawData + (rva - s->VirtualAddress);
			for (DWORD j = 0; j < size; j++) {
				if (((const BYTE *)addr)[j] == file[j]) continue;
				int ok = 0;
				for (int q = 0; q < g_saNpatchOk && !ok; q++)
					ok = addr + j >= g_saPatchOk[q][0] && addr + j < g_saPatchOk[q][0] + g_saPatchOk[q][1];
				if (!ok) return 1;
			}
			return 0;
		}
	return 1;
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
		int folded = (h->addr == 0x41ef60 || h->addr == 0x427970) && wide_menuFix() && p[0] == 0xE9;
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
	FlushInstructionCache(GetCurrentProcess(), (void *)GAME_BASE, file_nt()->OptionalHeader.SizeOfImage);
	return n;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR cmd, int show)
{
	char dir[MAX_PATH], path[MAX_PATH];
	(void)prev; (void)cmd; (void)show;
	GetModuleFileNameA(NULL, dir, sizeof dir);
	*(strrchr(dir, '\\') + 1) = 0;
	snprintf(path, sizeof path, "%sstandalone.log", dir);
	g_log = fopen(path, "w");
	if (!g_log) fail("cannot write %s", path);
	snprintf(path, sizeof path, "%sAxisGL.exe", dir);
	map_game(path);
	resolve_imports();
	axisnet_attach(inst, DLL_PROCESS_ATTACH, NULL);
	fprintf(g_log, "patch layer started (widescreen state %s)\n", wide_present() ? "handed over" : "MISSING");
	int n = install_hooks();
	fprintf(g_log, "%d of %d rebuilt functions switched in; starting the game\n", n, g_saNhooks);
	fclose(g_log);
	g_log = NULL;
	((void (*)(void))(GAME_BASE + file_nt()->OptionalHeader.AddressOfEntryPoint))();
	return 0;   /* (the game's runtime ends the process itself) */
}
