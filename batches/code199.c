/* batch 198 (lifted/grp153.c): the help screen, the loading screen's cylinder */
#include "lifted/grp153.c"
/* 0x4955a0 hud_4955a0() (thiscall on the scene; with "help_draw" at 0x4955c0, which functions.csv listed apart: the
   head runs straight into it): a half-transparent black quad over the screen (0x46bd60), then the 30 help lines
   (0x40 bytes each from +0x234334b) in white at x 0xc0, y 0, 0x10 ... 0x1d0 (0x44ad60) */
static THISCALL DWORD hud_4955a0(char *s) { return run_lifted(lift_4955a0, (DWORD)s, 0, NULL); }
/* 0x469730 loading_drawCylinder(mode, unused, text): the loading screen (0x469320, at the progress 0xa0ea88) with
   its text (copied to 0xa0e988). Mode -1: the progress reset, the backdrop texture looked up, then a fade from
   black over one second of game time (timer 0xa0e948, a full-screen quad 0x46bd60 each frame, swapped by 0x4685d0);
   -2: the progress advanced, then a fade to black; any other: the progress advanced (the text kept unless 1), one
   frame drawn */
LIFT_PLAIN(loading_drawCylinder, 469730)
