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

/* hud.c */
extern int g_fixHudPart;                    /* the main HUD's part drawing (HUD_* of wide.h) */
extern int g_fixPenSharp;                   /* font_penDraw samples pixel-sharp ([hud] sharptext) */
extern int g_fixPenDraw;                    /* font_penDraw is drawing */
void fix_hudVertex(int x, int y);           /* glVertex2i, the HUD's vertices remapped */
void fix_drawPlayerMarkers(Scene *scene);   /* hud_drawPlayerMarkers, sized for 4:3 over the whole screen */
void fix_drawLockOn(Scene *scene);          /* hud_drawLockOn, the same */
void fix_drawMainHud(Scene *scene);         /* hud_drawMain, fix_drawFps, fix_drawRanking: their area told */
void fix_drawFps(Scene *scene);
void fix_drawRanking(Scene *scene);
int fix_overlayBegin(int area);             /* the replay's overlay: one of its parts drawing (returns what to end with) */
void fix_overlayEnd(int was);
#define OVERLAY(area, call) do { int was_ = fix_overlayBegin(area); call; fix_overlayEnd(was_); } while (0)
void fix_powerUpText(int x, int y, int font, const char *format, int value);   /* font_penDraw for the power-up countdown */
void fix_labelText(int x1, int y, int x2, const char *name, int size);       /* text_drawCentred for a name label */

/* kyrie.c */
int fix_catalogueLoad(void *stage, const char *path);   /* catalogue_loadComponents, then the KYRIE parts */
void *fix_shapeFind(const char *name);                  /* shapeDat_getItemFileBy, the MARKED\ prefix dropped */
void fix_shapeRead(void *shape, void *file, void *at, int room);   /* shape_read, a marked model's textures moved */
int fix_maskFind(void *manager, char *name);            /* tex_findByName, a marked mask falling back to the original's */

#endif
#endif
