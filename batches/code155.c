/* batch 154 (lifted/grp100.c): the match loading screen */
#include "lifted/grp100.c"
/* 0x469320 loading_draw(scroll): the match loading screen: clear to blue, a textured cylinder (texture 0xa0e980,
   18 segments turned by Vec3_rotateAxis, its texture scrolled by scroll) in the HUD projection
   (gfx_setProjectionHud, patched: native), then in yellow "TITLE : %s" (0x67fb44, game modes 1 / 3 of the game
   0xa0ea8c +8), "ZONE : %s" (the round's map 0x907b30 or "ON RECEIVING" while +0x1f1cb0 == 1), "PLAY TYPE : %s"
   (the mode name 0x4c7030 + 0x40 * +0x22e7180, or "ON RECEIVING"), "FRAG LIMIT : %d" (0x4df8e8), "TIME LIMIT :
   %d" (0x76d408) and in grey the status line 0xa0e988 */
LIFT_PLAIN(loading_draw, 469320)
