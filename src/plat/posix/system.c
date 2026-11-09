/* plat/posix/system.c: the rest of the system calls the game makes, for Linux, macOS and the like (portable build
   only; not built on Windows). In the portable build every import is a call to plat_<name> (src/axis.h IMPORT_FN);
   time, files, settings, sound and input have their own interfaces (plat.h), the window, the drawing and the input
   are the host's (as standalone/host_window.c, glrec.c and the host hooks do on Windows). These are the small ones
   left, each answered as the game needs it (PORTING.md stage 3, the "other" group):
   - message boxes and program launches go to the host (AxisHostConfig.message / launch: the loader sets
     g_platHost* from it); the screen size is the host's (screen_w / screen_h);
   - the system language from LANG / LC_ALL / LC_MESSAGES ("ko..." Korean, 0x412 - the game's other texts - else
     English, 0x409);
   - the rest: Windows' version as a program sees it, handles that are never looked into, success.
   The imports the game never calls (those of the original's own C runtime) need no function here. */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(__i386__)
#define WINAPI __attribute__((stdcall))
#else
#define WINAPI
#endif
/* the symbol the game's calls name (src/axis.h: plat_<name> is "_plat_<name>") */
#define PLAT(ret, name, ...) ret WINAPI plat_##name(__VA_ARGS__) __asm__("_plat_" #name); ret WINAPI plat_##name(__VA_ARGS__)

/* set by the loader from the host's AxisHostConfig */
void *g_platHostUser;
int (*g_platHostMessage)(void *user, const char *title, const char *text);
int (*g_platHostLaunch)(void *user, const char *program, const char *arguments);
int g_platScreenW = 1920, g_platScreenH = 1080;

static uint32_t g_handles = 0x100;   /* (handles the game keeps but never looks into) */
static uintptr_t new_handle(void) { return g_handles += 4; }

PLAT(int, MessageBoxA, void *owner, const char *text, const char *title, uint32_t type)
{
	(void)owner;
	(void)type;
	if (g_platHostMessage)
		return g_platHostMessage(g_platHostUser, title ? title : "", text ? text : "");
	fprintf(stderr, "[%s] %s\n", title ? title : "", text ? text : "");
	return 1;   /* IDOK */
}
PLAT(void *, ShellExecuteA, void *w, const char *verb, const char *file, const char *args, const char *dir, int show)
{
	(void)w; (void)verb; (void)dir; (void)show;
	int ok = g_platHostLaunch && g_platHostLaunch(g_platHostUser, file ? file : "", args ? args : "");
	return (void *)(uintptr_t)(ok ? 42 : 2);
}

PLAT(int, GetSystemMetrics, int index)
{
	return index == 0 ? g_platScreenW : index == 1 ? g_platScreenH : 0;   /* SM_CXSCREEN, SM_CYSCREEN */
}
PLAT(int, GetDeviceCaps, void *dc, int index)
{
	(void)dc;
	switch (index) {
	case 8: return g_platScreenW;    /* HORZRES */
	case 10: return g_platScreenH;   /* VERTRES */
	case 12: return 32;              /* BITSPIXEL */
	default: return 0;
	}
}
PLAT(int32_t, ChangeDisplaySettingsA, void *mode, uint32_t flags) { (void)mode; (void)flags; return 0; }   /* (the desktop's mode: nothing to change) */
PLAT(void *, GetActiveWindow, void) { return NULL; }
PLAT(void *, FindWindowA, const char *cls, const char *title) { (void)cls; (void)title; return NULL; }   /* (no launcher, no other copy) */

/* what Windows 10 / 11 gives a program without a manifest: 6.2, build 9200 (major in the low byte); the game only asks
   whether it is NT (below 0x80000000: its RegisterClassA path, as on Windows) */
PLAT(uint32_t, GetVersion, void) { return 0x23f00206; }
static int korean(const char *v) { return v && (v[0] == 'k' || v[0] == 'K') && (v[1] == 'o' || v[1] == 'O'); }
PLAT(uint16_t, GetSystemDefaultLangID, void)
{
	const char *v = getenv("LC_ALL");
	if (!v || !*v) v = getenv("LC_MESSAGES");
	if (!v || !*v) v = getenv("LANG");
	return korean(v) ? 0x412 : 0x409;
}
PLAT(void *, GetModuleHandleA, const char *name) { (void)name; return (void *)new_handle(); }
PLAT(void *, GetProcAddress, void *module, const char *name) { (void)module; (void)name; return NULL; }   /* (SetProcessDPIAware: none) */

PLAT(void *, LoadIconA, void *instance, const char *name) { (void)instance; (void)name; return (void *)new_handle(); }
PLAT(void *, LoadCursorA, void *instance, const char *name) { (void)instance; (void)name; return (void *)new_handle(); }
PLAT(void *, SetCursor, void *cursor) { (void)cursor; return NULL; }
static int g_cursorCount;
PLAT(int, ShowCursor, int show) { return show ? ++g_cursorCount : --g_cursorCount; }   /* (the host shows its own pointer) */
PLAT(int, SystemParametersInfoA, uint32_t action, uint32_t param, void *data, uint32_t winIni)
{
	(void)action; (void)param; (void)data; (void)winIni;
	return 1;
}
PLAT(void *, GetStockObject, int index) { (void)index; return (void *)new_handle(); }
PLAT(void *, CreateFontIndirectA, const void *font) { (void)font; return (void *)new_handle(); }

/* the music file's name made wide for DirectShow (sound_basic.c; the host's music takes the narrow one) */
PLAT(int, MultiByteToWideChar, uint32_t codePage, uint32_t flags, const char *in, int inLength, uint16_t *out, int room)
{
	(void)codePage; (void)flags;
	int n = inLength < 0 ? (int)strlen(in) + 1 : inLength;
	if (!room)
		return n;
	if (n > room)
		return 0;
	for (int i = 0; i < n; i++)
		out[i] = (unsigned char)in[i];
	return n;
}
PLAT(char *, lstrcpyA, char *to, const char *from) { return strcpy(to, from); }
PLAT(int, lstrlenA, const char *s) { return s ? (int)strlen(s) : 0; }

PLAT(int32_t, CoInitialize, void *reserved) { (void)reserved; return 0; }
PLAT(void, CoUninitialize, void) {}
PLAT(uint32_t, mciSendCommandA, uint32_t device, uint32_t message, uintptr_t flags, uintptr_t params)
{
	(void)device; (void)message; (void)flags; (void)params;
	return 263;   /* MCIERR_INVALID_DEVICE_NAME (the ending movie is the host's) */
}
PLAT(void, ExitProcess, uint32_t code) { exit((int)code); }

/* the original's own message loop and painting (not reached with a host: it runs the frames, host_window the messages) */
PLAT(int, PeekMessageA, void *msg, void *w, uint32_t from, uint32_t to, uint32_t remove) { (void)msg; (void)w; (void)from; (void)to; (void)remove; return 0; }
PLAT(int, GetMessageA, void *msg, void *w, uint32_t from, uint32_t to) { (void)msg; (void)w; (void)from; (void)to; return 0; }
PLAT(int, TranslateMessage, const void *msg) { (void)msg; return 0; }
PLAT(intptr_t, DispatchMessageA, const void *msg) { (void)msg; return 0; }
PLAT(void *, BeginPaint, void *w, void *paint) { (void)w; (void)paint; return NULL; }
PLAT(int, EndPaint, void *w, const void *paint) { (void)w; (void)paint; return 1; }
#endif
