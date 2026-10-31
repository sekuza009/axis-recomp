/* crt.h: the game's C runtime (Visual C++ 6, linked into the exe at 0x49e000 ..) as the standalone build replaces
   it: Windows' msvcrt.dll does the work (standalone/crt.c points the runtime's entries at it), these files make the
   few results that differ from VC6's come out as VC6's. msvcrt's functions are handed in by the host (crt_setLib):
   AxisRC.exe's loader, or the harness before its tests. */
#ifndef CRT_H
#define CRT_H
#include "../axis.h"
#include <stdarg.h>

typedef struct {
	int (CDECL *vsprintf_)(char *out, const char *format, va_list args);   /* msvcrt's vsprintf */
} CrtLib;
extern const CrtLib *g_crtLib;
void crt_setLib(const CrtLib *lib);

/* format's arguments (args) copied to out (room dwords) with VC6's view of the doubles: the copy to format with */
void crt_fixArgs(const char *format, const u32 *args, u32 *out, int room);

#endif
