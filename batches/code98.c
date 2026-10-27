/* batch 97 (lifted/grp43.c) */
#include "lifted/grp43.c"
/* 0x41b400 armc_41b400(): the arm-customise screen's five spinning part panels: for k = 1..5, under the menu camera
   (gfx_setMenuCamera) scaled 0.8, texture 0x9da470 - k * 4 bound, panel k's quad (corners 0x4dc550 + k * 0x58, x
   offset +0x40, its spin angle +0x50 about y; panels 2 and 3 resized from 0x4b0708 / 0x4b0704 first) drawn at height
   k * 5 + 0x4dcfc4 + 1 - 105, depth 0x4dcfc8; the angle then advances by its speed (+0x54) times 0x4b071c and wraps
   at +-360 */
LIFT_PLAIN(armc_41b400, 41b400)
