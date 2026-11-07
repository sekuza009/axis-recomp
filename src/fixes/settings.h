/* settings.h: the native build's (AXIS_NATIVE) settings and the platform services its fixes use. Shared by the
   game's code (src/fixes/) and the Windows side (standalone/platform.c, which fills g_settings from axisnet.ini at
   start-up and provides the services); plain C types only, no game headers. */
#ifndef FIXES_SETTINGS_H
#define FIXES_SETTINGS_H

typedef struct {
	int menu43;            /* [hud] menu43: the menus in a centred 4:3 box (0: a 16:9 box) */
	int hudProportional;   /* [hud] proportional: the in-match HUD keeps its 4:3 proportions on wide screens */
	float hudMaxAspect;    /* [hud] maxaspect: the widest area the HUD spreads over, width / height (0: the screen) */
	int sharpText;         /* [hud] sharptext: menu / chat text sampled pixel-sharp */
	float menuSens;        /* [input] menusens: the menu pointer's speed (1: the Windows pointer's; 0: the original's) */
	float escMenuSens;     /* [input] escmenusens: how little mouse travel moves the in-match (Esc) menu's cursor (1: a
	                          quarter of the screen's height a step at the Windows pointer speed; 2: half that) */
} Settings;

extern Settings g_settings;

/* the Windows side (standalone/platform.c) */
void platform_loadSettings(void);              /* g_settings from axisnet.ini next to the exe (at start-up) */
int platform_isForeground(void *window);       /* the window is the foreground window */
void platform_watchWindow(void *window, void **chatLine, void **mouseDevice);
	/* subclass the game window once (again if it changes): on activation the chat line (*chatLine, an EDIT
	   child) gets the focus back; on deactivation the DirectInput mouse (*mouseDevice) is unacquired and the
	   real mouse buttons are watched so none stays held in Windows */
void platform_mouseButtons(int bits);          /* the buttons down in the last foreground read (bit 0 L, 1 R, 2 M) */
float platform_pointerSpeed(void);             /* the Windows pointer speed (Control Panel slider) as a factor */
unsigned platform_ticks(void);                 /* milliseconds (GetTickCount) */
int platform_texNearest(int saved[2]);          /* the bound 2D texture's filters to GL_NEAREST (the old ones into saved;
                                                  0: not available) */
void platform_texRestore(const int saved[2]);   /* its filters back */
void platform_playMovie(void *owner, const char *file, int w, int h);   /* the ending movie (movie_playEnding) */

#endif
