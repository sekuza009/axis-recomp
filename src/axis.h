/* axis.h: conventions for the readable rebuild of AxisGL.exe (PRIVATE; never ship).

   Every function here is a rebuild of one function of the game, checked bit-exact against the original by the
   recomp harness (recomp.c: the same random tests the lifted versions passed). Its comment names the original
   address. Rules that keep the code readable and exact at once:

   - Game data lives where the game keeps it: the scene object (scene.h, passed in like the original's "this") and
     named globals at fixed addresses (game.h).
   - A call to another game function is written as an ordinary call, text_drawSized(x, y, s, 8): game.h makes the
     name a call through the function's original address. So whichever version is installed (the original or a
     rebuild) runs, and the harness can put a stub there while it tests the caller. A rebuild is therefore defined
     with its name in parentheses, void (hud_drawFps)(Scene *s), which stops the call macro from expanding there.
   - Floating point is x87 (this tree is built with -mno-sse): float values are rounded where the original stores
     them; comparisons are written so NaN goes the way the original's fcomp / fnstsw test sends it; float-to-int
     conversions use ftol(), the original's __ftol (truncation, low 32 bits of the 64-bit result).
   - Imports (OpenGL, Win32) are called through the game's import table, as the original calls them. */
#ifndef AXIS_H
#define AXIS_H
#include <stdint.h>
#include <stddef.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef int32_t i32;

#define CDECL __attribute__((cdecl))
#define STDCALL __attribute__((stdcall))
#define THISCALL __attribute__((thiscall))

/* the game's __ftol: ST0 truncated to 64 bits, EDX:EAX; callers keep the low 32 bits */
static inline int ftol(long double x)
{
	long long r;
	__asm__ volatile("call *%1" : "=A"(r) : "r"(0x49ec14), "t"(x) : "ecx", "st", "memory");
	return (int)r;
}

/* a game function at its original address, as a callable expression */
#define GAME_CDECL(addr, ret, ...) ((ret (CDECL *)(__VA_ARGS__))(addr))
#define GAME_THISCALL(addr, ret, ...) ((ret (THISCALL *)(__VA_ARGS__))(addr))
/* an import, through the game's import table slot */
#define IMPORT(slot, ret, ...) ((ret (STDCALL *)(__VA_ARGS__))*(const u32 *)(slot))
/* a global of the game at its address */
#define GAME_VAR(type, addr) (*(type *)(addr))

#endif
