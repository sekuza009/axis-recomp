/* batch 124 (lifted/grp70.c): the setup screens' 3D tunnel */
#include "lifted/grp70.c"
/* 0x423e50 setup_423e50(): the tunnel behind the setup screens (3D projection): its alpha 0x4de038 eases to 0.3
   (mode 0x4ddcec 1) or 0.5 (mode 0); four layers of walls (camera gfx_setMenuCamera, pushed back 0x4ddd90, turned
   by 0x4b04c4 / FUN_0041ef20), the first two with texture 0x4e0cd0, the others 0x5b197c / 0x5b1978: layer 0 the
   pulsing panels (0x9db978), layer 1 the scrolling stripes (0x4e14fc), layer 3 brighter; then the pulse
   (0x9db978 bouncing 0..100 by 0x4df010) and the scroll (0x4e14fc += 0x4deda8, wrapping at 200) advance */
LIFT_PLAIN(setup_423e50, 423e50)
/* 0x423330 setup_423330(): the tunnel of the setup menu itself: the cursor tested against the four menu panels
   (0x4df918, 11 dwords each, FUN_0041eea0; none while 0x4dda60): the hovered one (0x680398) restarts its glow
   (0x680ccc = 40, 0x4df454 = -1) when it changes (0x907b24); the tunnel layers as setup_423e50's with the hovered
   panel glowing (0x680ccc bouncing 2..38); in mode 2 without a message (0x680370) the hovered panel's caption
   (0x7506a4, 0x80 apart) at the bottom */
LIFT_PLAIN(setup_423330, 423330)
