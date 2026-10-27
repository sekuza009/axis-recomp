/* batch 92 (lifted/grp38.c) */
#include "lifted/grp38.c"
/* menu_drawTexturedRect_427a90 / _427b60(x1, y1, x2, y2, tex): with GL_TEXTURE_2D, bind texture tex (set tex / 512
   of the global texture set 0xa0e010, index tex % 512; tex_bind) and draw the quad x1,y1 - x2,y2 through
   menu_vertex (0x41ef60), _427b60 with the texture flipped vertically; _428a00(x1, y1, x2, y2) / _428b50(-, y, x):
   the menu frame texture (0x4deb4c) as two quads (corner pieces at fixed offsets around the given points) / one */
LIFT_PLAIN8(menu_drawTexturedRect_427a90, 427a90)
LIFT_PLAIN8(menu_drawTexturedRect_427b60, 427b60)
LIFT_PLAIN8(menu_drawTexturedRect_428a00, 428a00)
LIFT_PLAIN8(menu_drawTexturedRect_428b50, 428b50)
