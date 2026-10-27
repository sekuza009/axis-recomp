/* batch 96 (lifted/grp42.c) */
#include "lifted/grp42.c"
/* 0x46b950 pen_init(name): the HUD pixel font. A second call (0xa106a8 == 1) gives a message and 0; otherwise the
   font texture by name from the global texture set (0xa106ac), the glyph widths (8) and the texture coordinates of
   the 8-pixel and 14-pixel glyph grids (21 per row) are filled in */
LIFT_PLAIN(pen_init, 46b950)
