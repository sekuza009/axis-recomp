/* function trace (test only): src/ compiled with -finstrument-functions; every rebuilt function's entry counted, with
   the screens / match states it ran in and the functions that called it. Every 3 s written to Axis\ftrace_<pid>.tsv,
   names from the PDB (dbghelp): fn  calls  contexts  callers (name xN, ...).
   Contexts: s0 before any screen, s100 .. s900 the front end's screens (g_screen), m0..m4 in a match by its
   matchState (0 over, 1 loading, 2 playing, 3 free camera, 4 replay), s? any other screen value. */
#include <windows.h>
#include <dbghelp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NI __attribute__((no_instrument_function))
#define NSLOT 16384
#define NCALLER 12
typedef struct {
	void *fn;
	unsigned calls, ctx;
	void *caller[NCALLER];
	unsigned ccount[NCALLER];
	unsigned overflow;
} Ent;
static Ent g_e[NSLOT];

extern unsigned char g_screen_v[4];
extern unsigned char g_data[];
static const int k_screens[] = { 0, 100, 200, 210, 300, 400, 500, 600, 700, 800, 900 };

static NI unsigned context(void)
{
	int s = *(volatile int *)g_screen_v;
	if (s == 9999) {
		unsigned char *scene = *(unsigned char *volatile *)(g_data + (0x9087b4 - 0x4ad000));
		int m = scene ? *(volatile int *)(scene + 0x233cc20) : -1;
		return m >= 0 && m <= 4 ? 1u << (16 + m) : 1u << 21;
	}
	for (int i = 0; i < (int)(sizeof k_screens / sizeof *k_screens); i++)
		if (k_screens[i] == s) return 1u << i;
	return 1u << 15;
}

static DWORD WINAPI dump_thread(void *unused);
static NI void exit_dump(void);
int g_testMissions;
extern unsigned char g_rdata[];
static NI HWND WINAPI find_window(LPCSTR cls, LPCSTR name)
{
	if ((ULONG_PTR)cls > 0xffff && !strcmp(cls, "AXIS"))
		return NULL;
	return FindWindowA(cls, name);
}
NI void trace_start(void)
{
	g_testMissions = GetEnvironmentVariableA("AXISRC_MISSIONS", NULL, 0) != 0;
	if (GetEnvironmentVariableA("AXISRC_MULTI", NULL, 0)) {
		DWORD old;
		void **slot = (void **)(g_rdata + (0x4a92cc - 0x4a9000));
		VirtualProtect(slot, 4, PAGE_READWRITE, &old);
		*slot = (void *)find_window;
		VirtualProtect(slot, 4, old, &old);
	}
	CreateThread(NULL, 0, dump_thread, NULL, 0, NULL);
	{   /* msvcrt's own atexit (the game's exit() is msvcrt's): registered before the game's, it runs after its destructors */
		int (__cdecl *ms_atexit)(void (__cdecl *)(void)) = (int (__cdecl *)(void (__cdecl *)(void)))GetProcAddress(LoadLibraryA("msvcrt.dll"), "atexit");
		if (ms_atexit)
			ms_atexit(exit_dump);
	}
}

NI void __cyg_profile_func_enter(void *fn, void *site)
{
	unsigned h = ((unsigned)fn * 2654435761u) >> 18;
	Ent *e;
	for (;; h = (h + 1) & (NSLOT - 1)) {
		e = &g_e[h];
		if (e->fn == fn) break;
		if (!e->fn) {
			if (InterlockedCompareExchangePointer(&e->fn, fn, NULL) == NULL || e->fn == fn) break;
		}
	}
	e->calls++;
	e->ctx |= context();
	for (int i = 0; i < NCALLER; i++) {
		if (e->caller[i] == site) { e->ccount[i]++; return; }
		if (!e->caller[i]) { e->caller[i] = site; e->ccount[i] = 1; return; }
	}
	e->overflow++;
}
NI void __cyg_profile_func_exit(void *fn, void *site) {}

static NI const char *name_of(void *a, char *out, int n)
{
	char buf[sizeof(SYMBOL_INFO) + 256];
	SYMBOL_INFO *s = (SYMBOL_INFO *)buf;
	s->SizeOfStruct = sizeof(SYMBOL_INFO); s->MaxNameLen = 255;
	DWORD64 d = 0;
	if (SymFromAddr(GetCurrentProcess(), (DWORD64)(ULONG_PTR)a, &d, s))
		snprintf(out, n, d ? "%s+%x" : "%s", s->Name, (unsigned)d);
	else
		snprintf(out, n, "?%p", a);
	return out;
}

static NI void ctx_text(unsigned c, char *out)
{
	out[0] = 0;
	for (int i = 0; i < 11; i++) if (c >> i & 1) out += sprintf(out, "s%d,", k_screens[i]);
	if (c >> 15 & 1) out += sprintf(out, "s?,");
	for (int i = 0; i < 5; i++) if (c >> (16 + i) & 1) out += sprintf(out, "m%d,", i);
	if (c >> 21 & 1) out += sprintf(out, "m?,");
}

static char g_path[MAX_PATH], g_tmp[MAX_PATH], *g_names[NSLOT];
static volatile LONG g_symReady;
static NI void dump(void)
{
	char nm[300], cn[300], cx[200];
	FILE *f = fopen(g_tmp, "w");
	if (!f) return;
	for (int i = 0; i < NSLOT; i++) {
		Ent *e = &g_e[i];
		if (!e->fn) continue;
		if (!g_names[i]) g_names[i] = _strdup(name_of(e->fn, nm, sizeof nm));
		ctx_text(e->ctx, cx);
		fprintf(f, "%s\t%u\t%s\t", g_names[i], e->calls, cx);
		for (int k = 0; k < NCALLER && e->caller[k]; k++)
			fprintf(f, "%s x%u,", name_of(e->caller[k], cn, sizeof cn), e->ccount[k]);
		fprintf(f, e->overflow ? "+%u more\n" : "\n", e->overflow);
	}
	fclose(f);
	MoveFileExA(g_tmp, g_path, MOVEFILE_REPLACE_EXISTING);
}

static NI DWORD WINAPI dump_thread(void *unused)
{
	SymSetOptions(SYMOPT_DEFERRED_LOADS);
	SymInitialize(GetCurrentProcess(), "C:/Users/Alexander/Desktop/Axis/recomp/build", TRUE);
	snprintf(g_path, sizeof g_path, "C:/Users/Alexander/Desktop/Axis/ftrace_%lu.tsv", GetCurrentProcessId());
	snprintf(g_tmp, sizeof g_tmp, "%s.tmp", g_path);
	g_symReady = 1;
	for (;;) {
		Sleep(3000);
		dump();
	}
	return 0;
}

/* the game's exit(): one last dump, run after the game's own atexit destructors (registered before them) */
static NI void exit_dump(void) { if (g_symReady) dump(); }

/* the game's own exit (ExitProcess): one last dump, so the shut-down path (destructors, app_shutdown) is counted
   (the other threads are gone by then) */
static NI void WINAPI on_tls(PVOID h, DWORD reason, PVOID r)
{
	if (reason == DLL_PROCESS_DETACH && g_symReady)
		dump();
}
__attribute__((section(".CRT$XLB"), used)) PIMAGE_TLS_CALLBACK g_ftraceTls = on_tls;
