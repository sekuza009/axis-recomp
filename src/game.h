/* game.h: the parts of AxisGL.exe the rebuilt code uses by their original address: functions (called through their
   address, see axis.h), globals and imports. Grows as rebuilds need more; a name defined here can still have a
   rebuild of its own elsewhere in src (that file defines it as "void (name)(...)"). */
#ifndef GAME_H
#define GAME_H
#include "axis.h"
#include "scene.h"

/* ---- OpenGL, through the import table ---- */
#define glColor4f(r, g, b, a) IMPORT(0x4a9228, void, float, float, float, float)(r, g, b, a)

/* ---- C runtime of the game ---- */
#define sprintf(...) GAME_CDECL(0x49e9dd, int, char *, const char *, ...)(__VA_ARGS__)

/* ---- screen ---- */
#define gfx_getWidth() GAME_CDECL(0x4685b0, int, void)()
#define gfx_getHeight() GAME_CDECL(0x4685c0, int, void)()
#define gfx_fillRect(x0, y0, x1, y1) GAME_CDECL(0x46bd60, void, int, int, int, int)(x0, y0, x1, y1)

/* ---- text ---- */
#define text_setColor(r, g, b, a) GAME_CDECL(0x44ad30, void, float, float, float, float)(r, g, b, a)
#define text_draw5(x, y, s) GAME_CDECL(0x403170, void, int, int, const char *)(x, y, s)
#define text_draw8(x, y, s) GAME_CDECL(0x402620, void, int, int, const char *)(x, y, s)
#define text_draw16(x, y, s) GAME_CDECL(0x4028b0, void, int, int, const char *)(x, y, s)
#define text_draw32(x, y, s) GAME_CDECL(0x402c90, void, int, int, const char *)(x, y, s)
/* the box passes: text centred between x0 and x1 */
#define hud_403210(x0, y, x1, s) GAME_CDECL(0x403210, void, int, int, int, const char *)(x0, y, x1, s)
#define text_draw8b(x0, y, x1, s) GAME_CDECL(0x402740, void, int, int, int, const char *)(x0, y, x1, s)
#define text_drawBox16(x0, y, x1, s) GAME_CDECL(0x4029d0, void, int, int, int, const char *)(x0, y, x1, s)
#define hud_402db0(x0, y, x1, s) GAME_CDECL(0x402db0, void, int, int, int, const char *)(x0, y, x1, s)
#define text_drawSized(x, y, s, size) GAME_CDECL(0x44ad60, void, int, int, const char *, int)(x, y, s, size)

/* ---- HUD ---- */
#define hud_4950a0(x0, y0, x1, y1) GAME_CDECL(0x4950a0, void, int, int, int, int)(x0, y0, x1, y1)
#define replay_drawIcon(scene, x, y, icon) GAME_THISCALL(0x496820, void, Scene *, int, int, int)(scene, x, y, icon)

/* ---- globals ---- */
typedef struct { float r, g, b, a; } Colour;
#define g_textColours ((Colour *)0xa1f100)          /* the 16 message colours */
#define g_chatLine ((char *)0x9dc92c)               /* the chat line being typed */

#endif
