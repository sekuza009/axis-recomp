/* crt.c: the game's C runtime replaced (AxisRC.exe only). AxisGL.exe carries Microsoft's C runtime of Visual C++ 6
   (0x49e000 ..), linked in. The rebuilt functions call its entry points at their addresses; here each one the
   rebuilds use becomes a jump to the same function of Windows' msvcrt.dll, the shared runtime of the same lineage
   (its formatting, rand and file functions behave as VC6's: the harness checks the ones whose results the game
   sees, recomp.c "C runtime" tests), except printf's view of two kinds of double and atof's rounding, which
   src/crt/ does as VC6's. The game's runtime then holds no state: msvcrt keeps the heap, the files, rand's
   seed and the exit list, as one runtime instance for the whole game (AxisRC.exe's own code uses the UCRT, apart).
   crt_start does the start-up work of the runtime's entry (0x49f976): the game's C++ static constructors (its table
   at 0x4ad000), then WinMain with the command line after the program's name, then exit with its result. */
#include <windows.h>
#include <string.h>
#include "standalone.h"
#undef CDECL   /* (windows.h's; axis.h has its own) */
#include "../src/crt/crt.h"

/* the runtime functions the rebuilds call, by their msvcrt.dll export */
static const struct { unsigned addr; const char *name; } k_msvcrt[] = {
	{ 0x49e7e0, "fclose" }, { 0x49e836, "fread" }, { 0x49e91e, "fseek" }, { 0x49e9ca, "fopen" },
	{ 0x49ea80, "strncpy" }, { 0x49ec09, "atoi" }, { 0x49ec14, "_ftol" }, { 0x49ec3b, "strtok" }, { 0x49ecd7, "fgets" },
	{ 0x49edac, "exit" }, { 0x49ee81, "free" }, { 0x49eeb0, "malloc" },
	{ 0x49ef24, "??3@YAXPAX@Z" },   /* operator delete */
	{ 0x49ef9c, "atexit" }, { 0x49efdd, "ftell" }, { 0x49f1aa, "??2@YAPAXI@Z" },   /* operator new */
	{ 0x49f58a, "fwrite" }, { 0x49f694, "_findfirst" }, { 0x49f75e, "_findnext" }, { 0x49f823, "_findclose" },
	{ 0x49f8a6, "_chdir" }, { 0x49f92c, "rand" }, { 0x49f94a, "_mkdir" }, { 0x49fab5, "_strupr" }, { 0x49fb53, "_itoa" },
	{ 0x49fbe0, "strncmp" }, { 0x49fdaf, "tolower" }, { 0x49ffc0, "_CIacos" }, { 0x4a0090, "strstr" },
	{ 0x4a8740, "_strnicmp" },
};

typedef struct _iobuf FILE_;
static FILE_ *(__cdecl *msvcrt_iob)(unsigned);   /* __iob_func: msvcrt's stdin, stdout, stderr (0x20 bytes each) */
static int (__cdecl *msvcrt_vfprintf)(void *, const char *, va_list);
static int (__cdecl *msvcrt_fputs)(const char *, void *);

/* the game's own standard streams (its _iob at 0x4d0838: stdin, stdout, stderr) as msvcrt's */
static void *stream(void *f)
{
	unsigned a = (unsigned)f;
	if (a >= 0x4d0838 && a < 0x4d0898 && (a - 0x4d0838) % 0x20 == 0)
		return (char *)msvcrt_iob(0) + (a - 0x4d0838);
	return f;
}
/* (the file versions of the formatting, with the arguments as VC6 sees them: src/crt/crt_format.c) */
static int __cdecl crt_vfprintf(void *f, const char *format, va_list args)
{
	u32 copy[64];
	crt_fixArgs(format, (const u32 *)args, copy, 64);
	return msvcrt_vfprintf(stream(f), format, (va_list)copy);
}
static int __cdecl crt_fprintf(void *f, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = crt_vfprintf(f, format, args);
	va_end(args);
	return n;
}
int crt_vsprintf(char *out, const char *format, va_list args);
int crt_sprintf(char *out, const char *format, ...);
double crt_atof(const char *s);
static int __cdecl crt_fputs(const char *s, void *f) { return msvcrt_fputs(s, stream(f)); }

/* 0x49fd2d, 0x49fc4f: the compiler's array helpers (stdcall): count objects of size bytes from first constructed in
   order, or destroyed last first (thiscall constructor / destructor). (Their SEH frames, for unwinding a throwing
   constructor, are not reproduced: the game's constructors do not throw) */
static void __stdcall vector_construct(char *first, int size, int count, void (__thiscall *ctor)(void *), void *dtor)
{
	(void)dtor;
	for (int i = 0; i < count; i++, first += size)
		ctor(first);
}
static void __stdcall vector_destruct(char *first, int size, int count, void (__thiscall *dtor)(void *))
{
	for (char *p = first + size * count; count-- > 0;) {
		p -= size;
		dtor(p);
	}
}

unsigned g_crtEntries[64];   /* the runtime entries pointed elsewhere (AXISRC_POISON keeps their jumps) */
int g_ncrtEntries;
static void jump(unsigned at, const void *to)
{
	BYTE *p = (BYTE *)at;
	g_crtEntries[g_ncrtEntries++] = at;
	p[0] = 0xE9;
	*(DWORD *)(p + 1) = (DWORD)to - (at + 5);
}

/* every runtime entry the rebuilds use pointed at its replacement; 0 and the missing export's name on a failure */
const char *crt_install(int *count)
{
	HMODULE m = LoadLibraryA("msvcrt.dll");
	if (!m)
		return "msvcrt.dll";
	*count = 0;
	for (unsigned i = 0; i < sizeof k_msvcrt / sizeof k_msvcrt[0]; i++) {
		FARPROC f = GetProcAddress(m, k_msvcrt[i].name);
		if (!f)
			return k_msvcrt[i].name;
		jump(k_msvcrt[i].addr, (const void *)f);
		++*count;
	}
	msvcrt_iob = (FILE_ *(__cdecl *)(unsigned))GetProcAddress(m, "__iob_func");
	msvcrt_vfprintf = (int (__cdecl *)(void *, const char *, va_list))GetProcAddress(m, "vfprintf");
	msvcrt_fputs = (int (__cdecl *)(const char *, void *))GetProcAddress(m, "fputs");
	if (!msvcrt_iob || !msvcrt_vfprintf || !msvcrt_fputs)
		return "__iob_func / vfprintf / fputs";
	static CrtLib lib;
	lib.vsprintf_ = (int (__cdecl *)(char *, const char *, va_list))GetProcAddress(m, "vsprintf");
	if (!lib.vsprintf_)
		return "vsprintf";
	crt_setLib(&lib);
	jump(0x49ed2e, crt_vsprintf);
	jump(0x49e9dd, crt_sprintf);
	jump(0x49fe7a, crt_atof);
	jump(0x49fec7, crt_vfprintf);
	jump(0x49f135, crt_fprintf);
	jump(0x49f167, crt_fputs);
	jump(0x49fd2d, vector_construct);
	jump(0x49fc4f, vector_destruct);
	*count += 8;
	return NULL;
}

/* the runtime's start-up, for the game: its static constructors in table order (some through the compiler's jump
   stubs), WinMain(the exe, NULL, the command line after the program's name, how the window is to be shown), exit */
void crt_start(void)
{
	for (const unsigned *f = (const unsigned *)0x4ad000; f < (const unsigned *)0x4ad0fc; f++)
		if (*f)
			((void (__cdecl *)(void))*f)();
	char *cmd = GetCommandLineA();
	if (*cmd == '"') {
		for (cmd++; *cmd && *cmd != '"'; cmd++)
			;
		if (*cmd == '"')
			cmd++;
	} else {
		while ((unsigned char)*cmd > ' ')
			cmd++;
	}
	while (*cmd && (unsigned char)*cmd <= ' ')
		cmd++;
	STARTUPINFOA si;
	si.dwFlags = 0;
	GetStartupInfoA(&si);
	int show = si.dwFlags & STARTF_USESHOWWINDOW ? si.wShowWindow : SW_SHOWDEFAULT;
	int r = ((int (__stdcall *)(HINSTANCE, HINSTANCE, char *, int))0x43f9d0)(GetModuleHandleA(NULL), NULL, cmd, show);   /* game_WinMain */
	((void (__cdecl *)(int))0x49edac)(r);   /* exit (msvcrt's) */
}
