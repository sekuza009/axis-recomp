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

#endif
#endif
