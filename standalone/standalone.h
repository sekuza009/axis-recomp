/* standalone.h: shared by AxisRC.exe's loader (main.c) and its generated hook table (build/standalone_hooks.c). */
#ifndef STANDALONE_H
#define STANDALONE_H

/* a rebuilt function and the original's address, where the game's own remaining code and its tables reach it */
typedef struct { unsigned addr; void *fn; const char *name; } SaHook;
extern const SaHook g_saHooks[];
extern const int g_saNhooks;
/* bytes inside rebuilt functions that the patch DLL may retarget (call rel32s) without the rebuild losing track:
   the rebuild reads the live target (PATCHED_CALL), so such a change does not keep the original */
extern const unsigned g_saPatchOk[][2];
extern const int g_saNpatchOk;
/* the game's code bytes the rebuilds read (AXISRC_POISON keeps them) */
extern const unsigned g_saKeep[][2];
extern const int g_saNkeep;
/* crt.c: the game's C runtime replaced by msvcrt.dll's */
const char *crt_install(int *count);
void crt_start(void);
extern unsigned g_crtEntries[];
extern int g_ncrtEntries;

#endif
