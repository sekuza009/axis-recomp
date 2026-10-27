/* batch 128 (lifted/grp74.c): the room menu's tunnel with hover panels */
#include "lifted/grp74.c"
/* 0x437e00 room_437e00(): the room menu: setup_423330's code for the room: the cursor tested against six panels
   (0x9daf88, 11 dwords each; none while 0x9dd7d8), the hovered one's glow restarted when it changes (0x907b24),
   the room tunnel (depth 0x9dd698, textures 0x4e0cd0 and 0x4df908 / 0x4df904) with the glowing panel, and in mode
   2 (0x9dce48) the hovered panel's caption (0x750ba4, 0x80 apart) */
LIFT_PLAIN(room_437e00, 437e00)
