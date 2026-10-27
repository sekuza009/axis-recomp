/* batch 105 (lifted/grp51.c) */
#include "lifted/grp51.c"
/* 0x429d70 menu_drawBackground3D(ring): the menu's 3D tunnel. The ring chain (+0x3534 next, +0x3530 back) is walked to its last
   ring, which is drawn first (at most two passes): under the menu camera at depth +8, turned by +0x1930, a quad
   strip through its +0x3528 vertices (from +0x10) in a pulsing blue (0x4b06fc), textured (0x4e186c) unless
   0x9da494; its spin advances by +0x1934 times the frame step (five times faster in modes 1 and 3, 0x680370) and
   wraps at 360. The second part draws the rings' inner layer (+0x1940.., spin +0x3264 / +0x3268) the same way in
   red; the pulse then moves on and turns at 0.05 / 0.95 */
LIFT_PLAIN(menu_drawBackground3D, 429d70)
