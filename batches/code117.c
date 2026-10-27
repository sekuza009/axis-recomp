/* batch 116 (lifted/grp62.c): menu text callers; text_draw8/5/drawBox16, gfx_setProjection2D3D and menu_drawRect
   run natively (the patch DLL rewrites them in memory, so they stay the originals) */
#include "lifted/grp62.c"
/* 0x4125c0 armc_4125c0(x, y, s): text in the language's small font (Korean 2: text_draw5, else text_draw8) */
LIFT_PLAIN(armc_4125c0, 4125c0)
/* 0x4125f0 armc_drawStatLabel(x, y, s): the same, right-aligned at x (8 / 6 units a character) */
LIFT_PLAIN(armc_drawStatLabel, 4125f0)
/* 0x4290d0 menu_4290d0(): the message box: 2D projection, a translucent panel and two lines (0x4df81c, 0x74de24) */
LIFT_PLAIN(menu_4290d0, 4290d0)
/* 0x428940 menu_428940(x, y): an input field (no dialog open): the blinking cursor after the cursor position
   (0x9dbf10) and the text 0x9dc92c, masked with '*' for a password field (0x4e1868) */
LIFT_PLAIN(menu_428940, 428940)
/* 0x44ce90 profile_44ce90(): the profile list's visible names (count 0x9f9008 from 0x9f8c4c, 0x48 bytes each from
   0x9f684c, at most 13, 20 apart), the selected one (0x9f8d74) brighter, all brighter when focused (0x9f8f10) */
LIFT_PLAIN(profile_44ce90, 44ce90)
/* 0x442d10 mainmenu_442d10(): the map list's visible names (count 0x9dd928 from 0x9dd92c, 0x44 bytes each from
   0x9dda88, at most 10, 20 apart), flagged ones (+0x40) on a red bar */
LIFT_PLAIN(mainmenu_442d10, 442d10)
