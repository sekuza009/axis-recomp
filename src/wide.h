/* wide.h: the widescreen fixes of the patch DLL (axisnet) that rebuilt functions carry themselves.

   The patch DLL used to apply these fixes from outside: it replaced menu_vertex and menu_drawRect in memory with its
   own versions, and told apart the main HUD's parts and the menus' 2D switch by the return addresses of their
   OpenGL calls, which a rebuilt function cannot reproduce. Now those four rebuilds do the fix's part themselves and
   ask the patch DLL only for the state it keeps across functions (the viewport it is tracking, the HUD pass it
   wraps, the menu cursor it draws). The test build of the patch DLL (axisnet_recomp.c) hands recomp.dll this
   table at start-up (recomp_setWide). Without it, every flag reads 0 and the rebuilds draw as the original game. */
#ifndef WIDE_H
#define WIDE_H
#include "axis.h"

typedef struct {
	int size;                          /* sizeof (Wide): the two sides were built from the same layout */
	const volatile int *menuFix;       /* the menus' full-screen effects are on (menu43 and its hooks installed) */
	const volatile int *menu43;        /* the menus are drawn in a centred 4:3 box ([hud] menu43) */
	const volatile int *inHud;         /* the in-match 2D pass is running (nests) */
	const volatile int *hudArea;       /* which part of it: 1 the player markers, 2 the main HUD, 5 the lock-on square */
	const volatile int *cursorOn;      /* the menu cursor is being drawn over the full screen ... */
	const volatile int *cursorX, *cursorW;   /* ... placed as in this viewport (left edge, width; pixels) */
	volatile int *hudPart;             /* the main HUD's part being drawn (HUD_*), for the patch DLL's vertex hook */
	void (CDECL *fullScreen)(int on);  /* 1: the full-screen viewport until the matching 0, then the menu box again */
	/* the functions the patch DLL patches in memory, rebuilt with its change (wide_carries): */
	u8 *state;                         /* the patch DLL's writable data (the harness restores and compares it) */
	u32 stateSize;
	const volatile int *pressedFix;    /* input_justPressed (0x401600): mouse buttons latch like keys ... */
	int (CDECL *mousePressed)(int key);   /* ... answered by this */
	int *mouseLatch;                   /* (its latches, 3, for the tests) */
	const volatile int *cursorClampFix;   /* input_updateMouse (0x445c60): its clamp (0x445cd8) replaced by ... */
	void (CDECL *cursorClamp)(void);      /* ... this (the pointer over the whole width of a wide screen) */
	const volatile int *rotFix;        /* armc_rotateFromCursor (0x461850): the cursor's turn in 640 x 480 units */
	volatile int *penDraw;             /* set by font_penDraw (0x46bb00) while it draws: the patch DLL recognised the
	                                      original by its glVertex2i calls' return addresses */
	void *(CDECL *callSite)(u32 site);   /* what the game's call at site goes to now (the patch DLL retargets some;
	                                        NULL: a call one of its rewritten blocks adds, not added) */
	/* the patch DLL's rewrites of single instructions, as state (AxisRC.exe carries no game code to rewrite): */
	const volatile int *menuBox43;       /* the menus' box is h * 4 / 3 wide (the cave at 0x4a8fbb: shl 2 / mov 3) */
	const float *const volatile *digitHeight;   /* the HUD digits' height factor (the fmul at 0x46bdda; NULL: 26) */
	void **const volatile *digitTexCoord;       /* the slot their texture coordinates are called through (the mov
	                                               at 0x46be96; NULL: glTexCoord2f's import) */
	void (CDECL *playEnding)(void *owner, const char *file, int w, int h);   /* movie_playEnding (0x46c420), which
	                                               the patch DLL replaces with its own player */
} Wide;

/* the call at the game's call site `site` (PATCHED_CALL in the standalone build): the patch DLL's table, else the
   call instruction's own target */
void *wide_callSite(u32 site);
/* 1 when the patch DLL's rewritten block at `at` (whose call is at `site`) is in; else code_matches(at, pattern) */
int wide_callAdded(u32 site, u32 at, const char *pattern);

/* what the main HUD's vertices are anchored to on a screen wider than 4:3 (hudPart) */
enum {
	HUD_AUTO,      /* not said: the patch DLL recognises the part by its return addresses (the original) */
	HUD_LEFT,      /* the left edge of the HUD area */
	HUD_CENTRE,    /* its centre, 4:3 proportions kept */
	HUD_RIGHT,     /* its right edge */
	HUD_SCREEN,    /* as drawn (full-screen flashes) */
	HUD_PIXELS,    /* screen pixels: drawn round in pixels already (the alert ring) */
	HUD_CORNER     /* fixed 64-pixel marks: sized in HUD units, at the top right corner of the HUD area */
};

extern const Wide *g_wide;

/* 1 when the rebuild at addr carries the patch DLL's in-memory change to that function (so it replaces the
   patched original); both hook installers (recomp.c, standalone/main.c) ask this */
int wide_carries(u32 addr);

#endif
