/* batch 211 (lifted/grp175.c, grp176.c): native until now; their only in-memory change is a call the patch DLL
   retargets (lift.py "@site", g_patchOk), or none */
#include "lifted/grp175.c"
/* 0x403170 text_draw5 / 0x402620 text_draw8 / 0x4028b0 text_draw16 / 0x402c90 text_draw32 / 0x402740 text_draw8b /
   0x4029d0 text_drawBox16 / 0x403210 hud_403210 / 0x402db0 hud_402db0 (x, y, text[, w]): the text passes: the 2D
   projection (0x41ef90), the colour 0x76d438.., per font texture (ids 0x9dae1c, 0x76d360, 0x76d448, set 0xa0e010)
   its glyph pass; the last pass of each (@0x4031f1, 0x402720, 0x4029b0, 0x402d90, 0x40288c, 0x402be8, 0x4032e6,
   0x402fbd) goes through the patch DLL's text_e5 / e8 / e16 / e32 (nearest-texel sampling) */
LIFT_PLAIN(text_draw5, 403170)
LIFT_PLAIN(text_draw8, 402620)
LIFT_PLAIN(text_draw16, 4028b0)
LIFT_PLAIN(text_draw32, 402c90)
LIFT_PLAIN(text_draw8b, 402740)
LIFT_PLAIN(text_drawBox16, 4029d0)
LIFT_PLAIN(hud_403210, 403210)
LIFT_PLAIN(hud_402db0, 402db0)
/* 0x429bc0 menu_drawCursor(): the menu pointer at 0x4ded68 / 0x4ded6c (blinking by 0x4df910, the click flash
   0x4df03c), a 47-unit sprite through menu_vertex; its right-hand corners (@0x429cc3, @0x429cf0) go through the
   patch DLL's cursor_vtx */
LIFT_PLAIN(menu_drawCursor, 429bc0)
#include "lifted/grp176.c"
/* 0x44ad60 text_drawSized(x, y, text, size): text_draw5 / 8 / 16 / 32 by the size */
LIFT_PLAIN(text_drawSized, 44ad60)
/* 0x44ae10 hud_44ae10(x1, y, x2, text, size): text_draw8b / text_drawBox16 / hud_402db0 / hud_403210 by the size */
LIFT_PLAIN8(hud_44ae10, 44ae10)
/* 0x4950a0 hud_4950a0(x1, y1, x2, y2): a filled box (gfx_fillRect) scaled from 640 x 480 to the screen */
LIFT_PLAIN(hud_4950a0, 4950a0)
/* 0x41f8d0 menu_drawVersion(): the title screen's end (0x4df01c counting 0x4e0458 to 19, then screen 210), the
   menu background (0x441740), the emblem transition (@0x41f903: 0x429170, the patch DLL's trans_wrap), the version
   texts (text_draw5) */
LIFT_PLAIN(menu_drawVersion, 41f8d0)
