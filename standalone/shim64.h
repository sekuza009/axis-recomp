/* shim64.h: the few Windows names standalone/glstate.c uses, for the 64-bit build off Windows (its mode 3 - answers
   only - needs no thread and no log; a lock is a mutex) */
#pragma once
#include <pthread.h>
#include <unistd.h>
#define WINAPI
#define __stdcall
#define MAX_PATH 260
typedef unsigned long DWORD;
typedef void *HANDLE;
typedef pthread_mutex_t CRITICAL_SECTION;
static inline void InitializeCriticalSection(CRITICAL_SECTION *c) { pthread_mutex_init(c, NULL); }
static inline void EnterCriticalSection(CRITICAL_SECTION *c) { pthread_mutex_lock(c); }
static inline void LeaveCriticalSection(CRITICAL_SECTION *c) { pthread_mutex_unlock(c); }
static inline void Sleep(DWORD ms) { usleep((useconds_t)ms * 1000); }
static inline HANDLE CreateThread(void *a, size_t s, DWORD (*f)(void *), void *p, DWORD fl, DWORD *id)
{
	(void)a; (void)s; (void)f; (void)p; (void)fl; (void)id;
	return NULL;   /* (mode 3 starts no report thread) */
}
static inline int CloseHandle(HANDLE h) { (void)h; return 1; }
