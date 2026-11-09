/* win64.c: the Windows platform of the 64-bit build (PORTING.md, stage 6) - what src/plat/posix is for Linux and macOS,
   on Windows x64: plat.h's time, files and settings (the registry, its keys as 32-bit handles), and the system calls
   the game makes, each with the game's prototype (src/game.h) - put in the slots by win64_install (standalone/host64.c).
   Under a host: no window of the game's own (hostwin64.c), no OpenGL (glrec64.c); message boxes and program launches
   go to the host, the screen size is the host's, handles the game keeps are arena addresses (host64_handle), the
   GlobalAlloc family's blocks are in the arena. The network (sockets, DirectPlay) is not in this build yet. */
#if defined(_WIN32) && (defined(__x86_64__) || defined(__aarch64__))
#include <winsock2.h>
#include <windows.h>
#include <mmsystem.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;
extern unsigned char *g_arena;
void *arena_malloc(size_t n);
void arena_free(void *p);
size_t arena_msize(const void *p);
void *host64_handle(void);
void hlog(const char *fmt, ...);
#define AV_(p) ((p) ? (u32)((const u8 *)(p) - g_arena) : 0u)

/* set by the loader from the host's configuration (as src/plat/posix/system.c's) */
void *g_platHostUser;
int (*g_platHostMessage)(void *user, const char *title, const char *text);
int (*g_platHostLaunch)(void *user, const char *program, const char *arguments);
int g_platScreenW = 1920, g_platScreenH = 1080;

/* ---- time (plat.h TIME_) */
int plat_timeCounter(void *count) { return QueryPerformanceCounter((LARGE_INTEGER *)count); }
int plat_timeFrequency(void *frequency) { return QueryPerformanceFrequency((LARGE_INTEGER *)frequency); }
u32 plat_timeMs(void) { return timeGetTime(); }
u32 plat_timeTicks(void) { return GetTickCount(); }
void plat_sleep(u32 ms) { Sleep(ms); }
void plat_timeLocal(void *st) { GetLocalTime((SYSTEMTIME *)st); }
void plat_timeUTC(void *st) { GetSystemTime((SYSTEMTIME *)st); }

/* ---- files (plat.h FILE_): the handle the game keeps in a local (never stored) */
void *plat_fileOpenRead(const char *path)
{
	return CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}
int plat_fileRead(void *file, void *out, u32 size, u32 *done)
{
	DWORD n = 0;
	BOOL ok = ReadFile((HANDLE)file, out, size, &n, NULL);
	*done = n;
	return ok;
}
int plat_fileClose(void *file) { return CloseHandle((HANDLE)file); }
u32 plat_fileDelete(const char *path) { return DeleteFileA(path); }
u32 plat_currentDirectory(u32 size, char *out) { return GetCurrentDirectoryA(size, out); }

/* ---- the registry (plat.h REG_): the game keeps a key as a 32-bit handle - 1 .. 64 here */
static HKEY g_keys[64];
static HKEY root_of(u32 root) { return root == 0x80000001u ? HKEY_CURRENT_USER : root == 0x80000002u ? HKEY_LOCAL_MACHINE : NULL; }
static u32 keep_key(HKEY k)
{
	for (int i = 0; i < 64; i++)
		if (!g_keys[i]) {
			g_keys[i] = k;
			return (u32)i + 1;
		}
	RegCloseKey(k);
	return 0;
}
static HKEY key_of(u32 h) { return h >= 1 && h <= 64 ? g_keys[h - 1] : NULL; }
int plat_regOpen(u32 root, const char *path, u32 *key)
{
	HKEY k;
	LONG r = RegOpenKeyExA(root_of(root), path, 0, KEY_ALL_ACCESS, &k);
	if (r == ERROR_SUCCESS)
		*key = keep_key(k);
	return (int)r;
}
int plat_regCreate(u32 root, const char *path, u32 *key, u32 *disposition)
{
	HKEY k;
	DWORD d = 0;
	LONG r = RegCreateKeyExA(root_of(root), path, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &k, &d);
	if (r == ERROR_SUCCESS) {
		*key = keep_key(k);
		if (disposition)
			*disposition = d;
	}
	return (int)r;
}
int plat_regQuery(u32 key, const char *name, u32 *type, void *data, u32 *size)
{
	DWORD t = 0, s = size ? *size : 0;
	LONG r = RegQueryValueExA(key_of(key), name, NULL, &t, data, size ? &s : NULL);
	if (type)
		*type = t;
	if (size)
		*size = s;
	return (int)r;
}
int plat_regSet(u32 key, const char *name, u32 type, const void *data, u32 size)
{
	return (int)RegSetValueExA(key_of(key), name, 0, type, data, size);
}
u32 plat_regClose(u32 key)
{
	HKEY k = key_of(key);
	if (!k)
		return ERROR_INVALID_HANDLE;
	g_keys[key - 1] = NULL;
	return (u32)RegCloseKey(k);
}

/* ---- the system calls (the game's prototypes) */
static int s_MessageBoxA(void *owner, const char *text, const char *title, u32 type)
{
	(void)owner; (void)type;
	if (g_platHostMessage)
		return g_platHostMessage(g_platHostUser, title ? title : "", text ? text : "");
	return MessageBoxA(NULL, text, title, MB_OK);
}
static void *s_ShellExecuteA(void *w, const char *verb, const char *file, const char *args, const char *dir, int show)
{
	(void)w; (void)verb; (void)dir; (void)show;
	int ok = g_platHostLaunch && g_platHostLaunch(g_platHostUser, file ? file : "", args ? args : "");
	return (void *)(uintptr_t)(ok ? 42 : 2);
}
static int s_GetSystemMetrics(int index) { return index == 0 ? g_platScreenW : index == 1 ? g_platScreenH : GetSystemMetrics(index); }
static int s_GetDeviceCaps(void *dc, int index)
{
	(void)dc;
	return index == 8 ? g_platScreenW : index == 10 ? g_platScreenH : index == 12 ? 32 : 0;
}
static int s_ChangeDisplaySettingsA(void *mode, u32 flags) { (void)mode; (void)flags; return 0; }
static void *s_FindWindowA(const char *cls, const char *title) { (void)cls; (void)title; return NULL; }
static u32 s_GetVersion(void) { return 0x23f00206; }
static u16 s_GetSystemDefaultLangID(void) { return GetSystemDefaultLangID(); }
static void *s_GetProcAddress(void *module, const char *name) { (void)module; (void)name; return NULL; }
static void *s_handle(void *a, const char *b) { (void)a; (void)b; return host64_handle(); }
static void *s_GetStockObject(int index) { (void)index; return host64_handle(); }
static void *s_CreateFontIndirectA(const void *f) { (void)f; return host64_handle(); }
static void *s_SetCursor(void *c) { (void)c; return NULL; }
static int g_cursorCount;
static int s_ShowCursor(int show) { return show ? ++g_cursorCount : --g_cursorCount; }
static int s_SystemParametersInfoA(u32 action, u32 param, void *data, u32 winIni) { (void)action; (void)param; (void)data; (void)winIni; return 1; }
static int s_MultiByteToWideChar(u32 cp, u32 flags, const char *in, int n, u16 *out, int room)
{
	return MultiByteToWideChar(cp, flags, in, n, (wchar_t *)out, room);
}
static char *s_lstrcpyA(char *to, const char *from) { return strcpy(to, from); }
static int s_lstrlenA(const char *s) { return s ? (int)strlen(s) : 0; }
static int s_CoInitialize(void *r) { (void)r; return 0; }
static void s_CoUninitialize(void) {}
static long s_CoCreateInstance(const void *clsid, void *outer, u32 ctx, const void *iid, u32 *out)
{
	(void)clsid; (void)outer; (void)ctx; (void)iid;
	if (out)
		*out = 0;
	return (long)(int32_t)0x80040154;   /* REGDB_E_CLASSNOTREG (DirectPlay: not in this build yet) */
}
static u32 s_mciSendCommandA(u32 id, u32 msg, uintptr_t flags, uintptr_t param) { (void)id; (void)msg; (void)flags; (void)param; return 1; }
static int s_PeekMessageA(void *msg, void *w, u32 a, u32 b, u32 remove) { (void)msg; (void)w; (void)a; (void)b; (void)remove; return 0; }
static int s_GetMessageA(void *msg, void *w, u32 a, u32 b) { (void)msg; (void)w; (void)a; (void)b; return 0; }
static int s_TranslateMessage(const void *msg) { (void)msg; return 0; }
static long s_DispatchMessageA(const void *msg) { (void)msg; return 0; }
static void *s_BeginPaint(void *w, void *ps) { (void)w; (void)ps; return host64_handle(); }
static int s_EndPaint(void *w, const void *ps) { (void)w; (void)ps; return 1; }
static void s_ExitProcess(u32 code) { ExitProcess(code); }
static u32 s_GetTickCount(void) { return GetTickCount(); }
static u32 s_timeGetTime(void) { return timeGetTime(); }
static int s_QueryPerformanceCounter(void *c) { return QueryPerformanceCounter((LARGE_INTEGER *)c); }
static int s_QueryPerformanceFrequency(void *f) { return QueryPerformanceFrequency((LARGE_INTEGER *)f); }
static void s_Sleep(u32 ms) { Sleep(ms); }
static void s_GetLocalTime(void *st) { GetLocalTime((SYSTEMTIME *)st); }
static void s_GetSystemTime(void *st) { GetSystemTime((SYSTEMTIME *)st); }
static u32 s_GetCurrentDirectoryA(u32 n, char *out) { return GetCurrentDirectoryA(n, out); }
static int s_DeleteFileA(const char *p) { return DeleteFileA(p); }

/* the GlobalAlloc family: a block in the arena; its handle is its address (GMEM_MOVEABLE blocks never move here) */
static void *s_GlobalAlloc(u32 flags, size_t size)
{
	void *p = arena_malloc(size ? size : 1);
	if (p && flags & 0x40)   /* GMEM_ZEROINIT */
		memset(p, 0, size);
	return p;
}
static void *s_GlobalLock(void *h) { return h; }
static int s_GlobalUnlock(void *h) { (void)h; return 0; }
static void *s_GlobalHandle(const void *p) { return (void *)p; }
static void *s_GlobalFree(void *h) { arena_free(h); return NULL; }

/* the network's sockets and threads: not yet (every call fails, as with no network) */
static int s_WSAStartup(u32 version, void *data)
{
	(void)version;
	if (data)
		memset(data, 0, 0x190);   /* (the 32-bit WSADATA the game made room for) */
	return 0;
}
static int s_WSACleanup(void) { return 0; }
static void s_WSASetLastError(int e) { WSASetLastError(e); }
static u32 s_socket(int af, int type, int protocol) { (void)af; (void)type; (void)protocol; return 0xffffffffu; }
static int s_fail(void) { return -1; }
static void *s_null(void) { return NULL; }

int win64_install(void **(*slot)(const char *name))
{
	int n = 0;
#define SET(name, f) do { void **p = slot(#name); if (p) { *p = (void *)(f); n++; } } while (0)
	SET(MessageBoxA, s_MessageBoxA); SET(ShellExecuteA, s_ShellExecuteA); SET(GetSystemMetrics, s_GetSystemMetrics);
	SET(GetDeviceCaps, s_GetDeviceCaps); SET(ChangeDisplaySettingsA, s_ChangeDisplaySettingsA); SET(FindWindowA, s_FindWindowA);
	SET(GetVersion, s_GetVersion); SET(GetSystemDefaultLangID, s_GetSystemDefaultLangID); SET(GetProcAddress, s_GetProcAddress);
	SET(LoadIconA, s_handle); SET(LoadCursorA, s_handle); SET(GetStockObject, s_GetStockObject);
	SET(CreateFontIndirectA, s_CreateFontIndirectA); SET(SetCursor, s_SetCursor); SET(ShowCursor, s_ShowCursor);
	SET(SystemParametersInfoA, s_SystemParametersInfoA); SET(MultiByteToWideChar, s_MultiByteToWideChar);
	SET(lstrcpyA, s_lstrcpyA); SET(lstrlenA, s_lstrlenA); SET(CoInitialize, s_CoInitialize); SET(CoUninitialize, s_CoUninitialize);
	SET(CoCreateInstance, s_CoCreateInstance); SET(mciSendCommandA, s_mciSendCommandA); SET(PeekMessageA, s_PeekMessageA);
	SET(GetMessageA, s_GetMessageA); SET(TranslateMessage, s_TranslateMessage); SET(DispatchMessageA, s_DispatchMessageA);
	SET(BeginPaint, s_BeginPaint); SET(EndPaint, s_EndPaint); SET(ExitProcess, s_ExitProcess);
	SET(GetTickCount, s_GetTickCount); SET(timeGetTime, s_timeGetTime); SET(QueryPerformanceCounter, s_QueryPerformanceCounter);
	SET(QueryPerformanceFrequency, s_QueryPerformanceFrequency); SET(Sleep, s_Sleep); SET(GetLocalTime, s_GetLocalTime);
	SET(GetSystemTime, s_GetSystemTime); SET(GetCurrentDirectoryA, s_GetCurrentDirectoryA); SET(DeleteFileA, s_DeleteFileA);
	SET(GlobalAlloc, s_GlobalAlloc); SET(GlobalLock, s_GlobalLock); SET(GlobalUnlock, s_GlobalUnlock);
	SET(GlobalHandle, s_GlobalHandle); SET(GlobalFree, s_GlobalFree);
	SET(WSAStartup, s_WSAStartup); SET(WSACleanup, s_WSACleanup); SET(WSASetLastError, s_WSASetLastError);
	SET(socket, s_socket); SET(connect, s_fail); SET(bind, s_fail); SET(send, s_fail); SET(recv, s_fail);
	SET(gethostbyname, s_null); SET(IcmpCreateFile, s_null); SET(CreateThread, s_null); SET(CreateEventA, s_null);
#undef SET
	return n;
}
#endif
