/* standalone.h: shared by AxisRC.exe's loader (main.c) and its generated hook table (build/standalone_hooks.c). */
#ifndef STANDALONE_H
#define STANDALONE_H

/* the game's image (header, code bytes, data), relocated: g_image in main.c holds what the original kept at
   0x400000 .. 0xb6b000; AT(a) is the original address a there. The original range itself is left inaccessible */
extern unsigned char g_image[];
#define GAME_BASE 0x400000u
#define GAME_SIZE 0x76b000u
/* (the read-only data 0x4a9000 .. 0x4ad000 and writable data 0x4ad000 .. 0xb13000 are g_rdata and g_data,
   src/data/layout.h; header and code bytes stay in g_image) */
extern unsigned char g_rdata[], g_data[];
#define AT(a) ((unsigned)(a) - 0x4a9000u < 0x4000u ? g_rdata + ((unsigned)(a) - 0x4a9000u) :                (unsigned)(a) - 0x4ad000u < 0x666000u ? g_data + ((unsigned)(a) - 0x4ad000u) : g_image + ((unsigned)(a) - GAME_BASE))

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
