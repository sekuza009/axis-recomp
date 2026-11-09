/* plat/posix/win32_compat.h: the Windows types and calls axisnet's network part (axisnet_dp.c) uses, on POSIX:
   Winsock's names for BSD sockets, critical sections and threads on pthreads, the tick count, axisnet.ini read as
   GetPrivateProfileString reads it. Only what that code needs - not a general Windows layer. */
#pragma once
#include <arpa/inet.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#if defined(__i386__)
#define WINAPI __attribute__((stdcall))
#else
#define WINAPI
#endif
#define WSAAPI WINAPI
#define CALLBACK WINAPI
#define __cdecl

typedef uint32_t DWORD, ULONG, UINT;
typedef int32_t LONG, BOOL, HRESULT;
typedef uint16_t WORD, USHORT;
typedef uint8_t BYTE, UCHAR;
typedef void *HANDLE, *HMODULE, *HINSTANCE, *LPVOID, *HWND;
typedef char CHAR;
typedef int SOCKET;
typedef uintptr_t UINT_PTR, ULONG_PTR, DWORD_PTR;
typedef union { struct { DWORD LowPart; LONG HighPart; }; int64_t QuadPart; } LARGE_INTEGER;
typedef struct { uint32_t Data1; uint16_t Data2, Data3; uint8_t Data4[8]; } GUID;
typedef const GUID *REFIID, *REFCLSID, *REFGUID;
#define TRUE 1
#define FALSE 0
#define MAX_PATH 260
#define S_OK 0
#define E_NOTIMPL ((HRESULT)0x80004001u)
#define E_NOINTERFACE ((HRESULT)0x80004002u)
#define E_FAIL ((HRESULT)0x80004005u)
#define E_INVALIDARG ((HRESULT)0x80070057u)
#define REGDB_E_CLASSNOTREG ((HRESULT)0x80040154u)
#define CLASS_E_NOAGGREGATION ((HRESULT)0x80040110u)
#define INVALID_SOCKET (-1)
#define SOCKET_ERROR (-1)
#define INFINITE 0xffffffffu
#define MAKEWORD(a, b) ((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define LOWORD(l) ((WORD)((DWORD)(l) & 0xffff))
#define HIWORD(l) ((WORD)((DWORD)(l) >> 16))
#define IsEqualGUID(a, b) (!memcmp((a), (b), sizeof(GUID)))
#define closesocket close
#define _stricmp strcasecmp
#define _strnicmp strncasecmp
#define stricmp strcasecmp
#define strnicmp strncasecmp
#define lstrcpynA(d, s, n) (strncpy((d), (s), (n) - 1), (d)[(n) - 1] = 0, (d))
#define wsprintfA sprintf
#define _snprintf snprintf
#define ZeroMemory(p, n) memset((p), 0, (n))
#define WSAEWOULDBLOCK EWOULDBLOCK
#define WSAEINPROGRESS EINPROGRESS
#define WSAECONNRESET ECONNRESET
#define SD_BOTH SHUT_RDWR
#define SD_SEND SHUT_WR
#ifndef MSG_NOSIGNAL
#define MSG_NOSIGNAL 0
#endif

typedef struct { WORD wVersion, wHighVersion; char szDescription[257], szSystemStatus[129]; } WSADATA;
static inline int WSAStartup(WORD v, WSADATA *d) { if (d) { memset(d, 0, sizeof *d); d->wVersion = v; } return 0; }
static inline int WSACleanup(void) { return 0; }
static inline int WSAGetLastError(void) { return errno; }
static inline int ioctlsocket(SOCKET s, long cmd, unsigned long *arg)
{
	(void)cmd;   /* (FIONBIO only) */
	int f = fcntl(s, F_GETFL, 0);
	return fcntl(s, F_SETFL, *arg ? f | O_NONBLOCK : f & ~O_NONBLOCK);
}
#define FIONBIO_ 0x8004667e
/* select as Winsock's: the first argument (the highest socket + 1 on POSIX) is ignored there - axisnet passes 0 */
static inline int compat_select_(int n, fd_set *r, fd_set *w, fd_set *e, struct timeval *t)
{
	(void)n;
	return select(FD_SETSIZE, r, w, e, t);
}
#define select compat_select_

/* critical sections (recursive, as Windows') */
typedef pthread_mutex_t CRITICAL_SECTION;
static inline void InitializeCriticalSection(CRITICAL_SECTION *c)
{
	pthread_mutexattr_t a;
	pthread_mutexattr_init(&a);
	pthread_mutexattr_settype(&a, PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(c, &a);
	pthread_mutexattr_destroy(&a);
}
#define EnterCriticalSection pthread_mutex_lock
#define LeaveCriticalSection pthread_mutex_unlock
#define DeleteCriticalSection pthread_mutex_destroy
static inline LONG InterlockedIncrement(volatile LONG *p) { return __atomic_add_fetch(p, 1, __ATOMIC_SEQ_CST); }
static inline LONG InterlockedDecrement(volatile LONG *p) { return __atomic_sub_fetch(p, 1, __ATOMIC_SEQ_CST); }
static inline LONG InterlockedExchange(volatile LONG *p, LONG v) { return __atomic_exchange_n(p, v, __ATOMIC_SEQ_CST); }

/* threads: a Windows thread procedure on a pthread; its handle can be waited for (WaitForSingleObject, with a
   timeout) and closed in either order (the record goes when both the thread and the handle are done with it) */
typedef DWORD (WINAPI *LPTHREAD_START_ROUTINE)(void *);
#define COMPAT_THREAD_MAGIC_ 0x43544852u
typedef struct {
	uint32_t magic;   /* (first: CloseHandle tells a thread from an event) */
	LPTHREAD_START_ROUTINE f;
	void *a;
	pthread_mutex_t m;
	pthread_cond_t c;
	int done, refs;
} CompatThread_;
static void compat_release_(CompatThread_ *t)
{
	pthread_mutex_lock(&t->m);
	int last = --t->refs == 0;
	pthread_mutex_unlock(&t->m);
	if (last) {
		pthread_mutex_destroy(&t->m);
		pthread_cond_destroy(&t->c);
		free(t);
	}
}
static void *compat_thread_(void *p)
{
	CompatThread_ *t = p;
	t->f(t->a);
	pthread_mutex_lock(&t->m);
	t->done = 1;
	pthread_cond_broadcast(&t->c);
	pthread_mutex_unlock(&t->m);
	compat_release_(t);
	return NULL;
}
static inline HANDLE CreateThread(void *sec, size_t stack, LPTHREAD_START_ROUTINE f, void *arg, DWORD flags, DWORD *id)
{
	(void)sec; (void)stack; (void)flags;
	CompatThread_ *t = calloc(1, sizeof *t);
	if (!t) return NULL;
	t->f = f;
	t->a = arg;
	t->magic = COMPAT_THREAD_MAGIC_;
	t->refs = 2;   /* (the thread's and the handle's) */
	pthread_mutex_init(&t->m, NULL);
	pthread_cond_init(&t->c, NULL);
	pthread_t th;
	pthread_attr_t a;
	pthread_attr_init(&a);
	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
	int e = pthread_create(&th, &a, compat_thread_, t);
	pthread_attr_destroy(&a);
	if (e) { pthread_mutex_destroy(&t->m); pthread_cond_destroy(&t->c); free(t); return NULL; }
	if (id) *id = 1;
	return t;
}
#define WAIT_OBJECT_0 0
#define WAIT_TIMEOUT 0x102u
DWORD WINAPI plat_WaitForMultipleObjects_(DWORD n, void *const *h, int all, DWORD ms) __asm__("_plat_WaitForMultipleObjects");
static inline DWORD WaitForSingleObject(HANDLE h, DWORD ms)
{
	CompatThread_ *t = h;
	if (!t) return 0xffffffffu;
	if (t->magic != COMPAT_THREAD_MAGIC_)   /* (an event: the game's kind, plat/posix/net.c) */
		return plat_WaitForMultipleObjects_(1, &h, 0, ms);
	struct timespec until;
	clock_gettime(CLOCK_REALTIME, &until);
	until.tv_sec += ms / 1000;
	until.tv_nsec += (long)(ms % 1000) * 1000000L;
	if (until.tv_nsec >= 1000000000L) { until.tv_sec++; until.tv_nsec -= 1000000000L; }
	pthread_mutex_lock(&t->m);
	int r = 0;
	while (!t->done && r != ETIMEDOUT)
		r = ms == INFINITE ? pthread_cond_wait(&t->c, &t->m) : pthread_cond_timedwait(&t->c, &t->m, &until);
	int done = t->done;
	pthread_mutex_unlock(&t->m);
	return done ? WAIT_OBJECT_0 : WAIT_TIMEOUT;
}
/* events are the game's own kind (plat/posix/net.c: the game may hand axisnet one of its events, DirectPlay's
   "a message arrived"), so they go through those */
void *WINAPI plat_CreateEventA_(void *sec, int manual, int initial, const char *name) __asm__("_plat_CreateEventA");
int WINAPI plat_SetEvent_(void *h) __asm__("_plat_SetEvent");
int WINAPI plat_ResetEvent_(void *h) __asm__("_plat_ResetEvent");
int WINAPI plat_CloseHandle_(void *h) __asm__("_plat_CloseHandle");
#define CreateEventA(sec, manual, initial, name) plat_CreateEventA_((sec), (manual), (initial), (name))
#define SetEvent(h) plat_SetEvent_(h)
#define ResetEvent(h) plat_ResetEvent_(h)
static inline BOOL CloseHandle(HANDLE h)
{
	if (!h) return FALSE;
	if (((CompatThread_ *)h)->magic == COMPAT_THREAD_MAGIC_) { compat_release_((CompatThread_ *)h); return TRUE; }
	return plat_CloseHandle_(h);
}
static inline void Sleep(DWORD ms) { struct timespec t = { (time_t)(ms / 1000), (long)(ms % 1000) * 1000000L }; while (nanosleep(&t, &t)) ; }
static inline DWORD GetTickCount(void)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (DWORD)((uint64_t)t.tv_sec * 1000u + (uint64_t)t.tv_nsec / 1000000u);
}
static inline DWORD GetCurrentProcessId(void) { return (DWORD)getpid(); }

/* GetPrivateProfileString / Int as Windows reads an INI: the section and key without regard to case, the value
   trimmed of spaces; the default when the file, section or key is missing */
static inline DWORD GetPrivateProfileStringA(const char *section, const char *key, const char *def, char *out, DWORD size, const char *file)
{
	snprintf(out, size, "%s", def ? def : "");
	FILE *f = fopen(file, "r");
	if (!f) return (DWORD)strlen(out);
	char line[1024];
	int in = 0;
	while (fgets(line, sizeof line, f)) {
		char *s = line;
		while (isspace((unsigned char)*s)) s++;
		char *e = s + strlen(s);
		while (e > s && isspace((unsigned char)e[-1])) *--e = 0;
		if (*s == '[') {
			char *r = strchr(s, ']');
			if (r) { *r = 0; in = !strcasecmp(s + 1, section); }
			continue;
		}
		if (!in || *s == ';' || *s == '#') continue;
		char *eq = strchr(s, '=');
		if (!eq) continue;
		*eq = 0;
		char *k = s, *v = eq + 1, *ke = eq;
		while (ke > k && isspace((unsigned char)ke[-1])) *--ke = 0;
		while (isspace((unsigned char)*v)) v++;
		if (!strcasecmp(k, key)) { snprintf(out, size, "%s", v); break; }
	}
	fclose(f);
	return (DWORD)strlen(out);
}
static inline UINT GetPrivateProfileIntA(const char *section, const char *key, int def, const char *file)
{
	char d[32], v[64];
	snprintf(d, sizeof d, "%d", def);
	GetPrivateProfileStringA(section, key, d, v, sizeof v, file);
	return (UINT)atoi(v);
}

/* the registry: the game's settings store (plat/posix/registry.c) - axisnet reads the server the launcher picked */
typedef uint32_t HKEY;
#define HKEY_CURRENT_USER 0x80000001u
#define KEY_READ 0x20019
#define ERROR_SUCCESS 0
#define REG_DWORD 4
int plat_regOpen(uint32_t root, const char *path, uint32_t *key);
int plat_regQuery(uint32_t key, const char *name, uint32_t *type, void *data, uint32_t *size);
uint32_t plat_regClose(uint32_t key);
static inline LONG RegOpenKeyExA(HKEY root, const char *path, DWORD opt, DWORD access, HKEY *out) { (void)opt; (void)access; return plat_regOpen(root, path, out); }
static inline LONG RegQueryValueExA(HKEY k, const char *name, DWORD *res, DWORD *type, BYTE *data, DWORD *size) { (void)res; return plat_regQuery(k, name, type, data, size); }
static inline LONG RegCloseKey(HKEY k) { return (LONG)plat_regClose(k); }

typedef struct { WORD wYear, wMonth, wDayOfWeek, wDay, wHour, wMinute, wSecond, wMilliseconds; } SYSTEMTIME;
static inline void GetLocalTime(SYSTEMTIME *s)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	struct tm m;
	time_t secs = t.tv_sec;
	localtime_r(&secs, &m);
	s->wYear = (WORD)(m.tm_year + 1900); s->wMonth = (WORD)(m.tm_mon + 1); s->wDayOfWeek = (WORD)m.tm_wday; s->wDay = (WORD)m.tm_mday;
	s->wHour = (WORD)m.tm_hour; s->wMinute = (WORD)m.tm_min; s->wSecond = (WORD)m.tm_sec; s->wMilliseconds = (WORD)(t.tv_nsec / 1000000);
}
static inline DWORD GetEnvironmentVariableA(const char *name, char *out, DWORD size)
{
	const char *v = getenv(name);
	if (!v) return 0;
	snprintf(out, size, "%s", v);
	return (DWORD)strlen(out);
}
static inline DWORD GetModuleFileNameA(HMODULE m, char *out, DWORD size) { (void)m; if (size) out[0] = 0; return 0; }   /* (the current folder: the game's) */

/* a new GUID (the hub's session): random bytes, as a version-4 GUID */
static inline HRESULT CoCreateGuid(GUID *g)
{
	FILE *f = fopen("/dev/urandom", "rb");
	size_t n = f ? fread(g, 1, sizeof *g, f) : 0;
	if (f) fclose(f);
	if (n != sizeof *g) {   /* (no /dev/urandom: the time and the process) */
		struct timespec t;
		clock_gettime(CLOCK_REALTIME, &t);
		uint32_t x = (uint32_t)t.tv_nsec ^ (uint32_t)getpid() << 16;
		for (size_t i = 0; i < sizeof *g; i++) { x = x * 1103515245u + 12345u; ((uint8_t *)g)[i] = (uint8_t)(x >> 16); }
	}
	g->Data3 = (uint16_t)((g->Data3 & 0x0fff) | 0x4000);
	g->Data4[0] = (uint8_t)((g->Data4[0] & 0x3f) | 0x80);
	return S_OK;
}
#define RELOC(a) (a)   /* (axisnet's patch-layer address mapping: nothing to map here) */

static inline BOOL QueryPerformanceFrequency(LARGE_INTEGER *f) { f->QuadPart = 1000000000; return TRUE; }
static inline BOOL QueryPerformanceCounter(LARGE_INTEGER *c)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	c->QuadPart = (int64_t)t.tv_sec * 1000000000 + t.tv_nsec;
	return TRUE;
}
