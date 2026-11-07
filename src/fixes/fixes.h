/* fixes.h: the native build's fixes (AXIS_NATIVE): what the patch DLL (axisnet) did to the game from outside,
   written as the game's own code and called from the functions they change. The settings come from axisnet.ini
   (settings.h); the Windows plumbing is in standalone/platform.c. */
#ifndef FIXES_H
#define FIXES_H
#ifdef AXIS_NATIVE
#include "settings.h"

/* input.c */
int fix_mousePressed(int key);              /* input_justPressed for the mouse buttons (0xfa .. 0xfc): they latch like keys */
int fix_readMouse(void);                    /* input_readMouse, then buttons after alt-tab, the menu pointer's speed */
void fix_cursorClamp(void);                 /* the menu pointer over the whole width of a wide screen */
void fix_menuNav(Scene *scene);             /* the Esc menu's steps by mouse travel */
int fix_labelHalfWidth(const char *name);   /* half a name label's text width (its icon's place) */

/* screen.c */
typedef struct { int x, y, w, h; } FixView;
extern FixView g_fixView;                   /* the viewport set last (fix_glViewport) */
extern int g_fixInHud, g_fixHudArea;        /* the in-match 2D pass is running (nests); which part of it draws (FIX_AREA_*) */
extern int g_fixCursorOn, g_fixCursorX, g_fixCursorW;   /* the menu pointer is drawn over the whole screen, placed as in
                                                           the viewport (left edge, width) it would be in */
enum { FIX_AREA_NONE, FIX_AREA_MARKERS, FIX_AREA_MAIN, FIX_AREA_FPS, FIX_AREA_RANKING, FIX_AREA_LOCKON,
       FIX_AREA_OVERLAY_LEFT, FIX_AREA_OVERLAY_RIGHT, FIX_AREA_OVERLAY_CENTRE };
void fix_glViewport(int x, int y, int w, int h);   /* glViewport, kept */
void fix_fullScreen(int on);                /* 1: the whole screen until the matching 0, then the menus' box again */
void fix_titleEmblemTransition(void);       /* menu_titleEmblemTransition over the whole screen */
void fix_drawCursor(void);                  /* menu_drawCursor over the whole screen */
void fix_cursorVertex(int x, int y);        /* the pointer sprite's right-hand corners, its proportions kept */
void fix_asciiPass(void *pass, int x, int y, const char *text);   /* a font's ASCII pass, pixel-sharp */
const float *fix_digitHeight(void);         /* the HUD digits' height factor */
void STDCALL fix_digitTexCoord(u32 s, u32 t);   /* their texture corners, half a texel inside each cell */

#endif
#endif
