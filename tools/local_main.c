/* local_main.c: standalone harness for pure functions (no game state, no imports). Maps the patched game image
   (installed.exe) at 0x400000 in this process (inside the harness's own .bss, see g_space), so the originals can be
   called at their own addresses next to the rebuilt C versions. Build: bash tools/local_build.sh <test.c> <out.exe>
   <test.c> starts with #include "local_main.c" and defines local_test(). Never part of recomp.dll. */
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define THISCALL __attribute__((thiscall))
#define G32(a) (*(int *)(a))
#define GF(a) (*(float *)(a))
#define S32(self, off) (*(int *)((char *)(self) + (off)))
#define SF(self, off) (*(float *)((char *)(self) + (off)))
#define TC(ret, addr, ...) ((ret (THISCALL *)(__VA_ARGS__))(addr))
#define CD(ret, addr, ...) ((ret (__cdecl *)(__VA_ARGS__))(addr))

static unsigned g_seed = 12345;
static int irnd(int lo, int hi) { g_seed = g_seed * 1103515245u + 12345u; return lo + (int)((g_seed >> 8) % (unsigned)(hi - lo + 1)); }
static void fill(void *p, int n) { for (int i = 0; i < n; i++) ((BYTE *)p)[i] = (BYTE)irnd(0, 255); }

/* The harness exe is linked at a fixed base of 0x10000 (ASLR flag cleared by local_build.sh); this zeroed array in its
   own .bss then covers 0x400000.. (checked below), and the game's sections are copied into it. Memory the process
   allocates at start-up (stack, heaps, mapped files) would otherwise sit in that range. */
static BYTE g_space[0xc00000] __attribute__((aligned(4096)));
static int map_image(const char *path)
{
	FILE *f = fopen(path, "rb");
	if (!f) return 0;
	BYTE *g_file = malloc(4 << 20);                 /* on the heap, so that g_space is the only large .bss item */
	size_t n = fread(g_file, 1, 4 << 20, f); fclose(f);
	IMAGE_NT_HEADERS32 *nt = (IMAGE_NT_HEADERS32 *)(g_file + ((IMAGE_DOS_HEADER *)g_file)->e_lfanew);
	DWORD size = nt->OptionalHeader.SizeOfImage;
	BYTE *base = (BYTE *)0x400000;
	if (g_space > base || g_space + sizeof g_space < base + size) {
		printf("g_space %p..%p does not cover 0x400000..%p\n", (void *)g_space, (void *)(g_space + sizeof g_space), (void *)(base + size));
		return 0;
	}
	DWORD old;
	VirtualProtect(base, size, PAGE_EXECUTE_READWRITE, &old);
	memcpy(base, g_file, nt->OptionalHeader.SizeOfHeaders);
	IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
	for (int i = 0; i < nt->FileHeader.NumberOfSections; i++)
		if (s[i].PointerToRawData + s[i].SizeOfRawData <= n)
			memcpy(base + s[i].VirtualAddress, g_file + s[i].PointerToRawData, s[i].SizeOfRawData);
	return 1;
}

void local_test(void);
int main(void)
{
	if (!map_image("C:/Users/Alexander/Desktop/Axis/recomp/installed.exe")) {
		printf("could not map the image at 0x400000 (exe at %p, error %lu)\n", (void *)GetModuleHandleA(NULL), GetLastError());
		return 1;
	}
	local_test();
	return 0;
}
