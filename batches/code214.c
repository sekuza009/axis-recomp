/* batch 213 (lifted/grp178.c .. grp180.c): functions that jump into code caves of the installed exe (0x4a8e20.. at
   the end of .text): lift.py "&lo-hi" lifts each cave as part of the function that reaches it */
#include "lifted/grp178.c"
/* 0x41ef90 gfx_setProjection2D3D(mode): unless already in it (0x5ae9bc), the viewport (the cave 0x4a8fa4: in 2D a
   centred box of h * 16 / 9, or with the patch DLL's menu43 rewrite of the cave (%0x4a8fbb) h * 4 / 3, when the
   screen is wider), the projection (mode 1: gluPerspective from 0x68038c / 0x4e1870, depth on; else gluOrtho2D,
   depth off) */
LIFT_PLAIN(gfx_setProjection2D3D, 41ef90)
#include "lifted/grp179.c"
/* 0x42eed0 FUN_0042eed0(w, h, bpp, hz): the display mode: the cave 0x4a8e54 keeps the desktop mode (0x67eefc /
   0x76d430) as is (leaving a changed one, flag 0xb12a80, by ChangeDisplaySettingsA(0)) and remembers any other
   (0xb12a84 / 0xb12a88, flag set) before the original sets it with a DEVMODE (32 bits) */
LIFT_PLAIN(FUN_0042eed0, 42eed0)
#include "lifted/grp180.c"
/* 0x43fcc0 app_init(inst, show): the checks (0x41e6d0 .. unless 0x76d410), the 640 x 480 default, paths and
   settings (0x43f580, 0x43f5a0, 0x42b3e0), in the cave 0x4a8e20 SetProcessDPIAware when user32 has it; the desktop's
   DC, size and depth (0x67eefc, 0x76d430, 0x76d3ec), 0x42fd40 / 0x42eca0 / 0x43f640, the display mode
   (FUN_0042eed0) and 0x42ef30; the checks again; the window class (WndProc, icon, cursor, brush; 0x43f840 on old
   Windows, else RegisterClassA), the window (the cave 0x4a8f50: the size from 0x5b1998 / 0x4e045c), three timers,
   shown; app_checkCdAndLoad (failure: the mode back, 0); screen 100, the cursor hidden, 0x43f300. Returns 1 */
LIFT_PLAIN(app_init, 43fcc0)
