/* batch 129 (lifted/grp75.c): the arena menu's tunnel with hover panels */
#include "lifted/grp75.c"
/* 0x408680 lobbyTop_drawTitle(): the arena menu (misnamed): setup_423330's code for the arena: four panels
   (0x5b1cf8, 11 dwords each; none while 0x4db85c), the hover glow, the arena tunnel (depth 0x4dba68, two walls a
   side at -35 / 35, textures 0x4e0cd0 and 0x4df044 / 0x4df040), and in mode 2 (0x4dbb3c) without a message
   (0x680370) the hovered panel's caption (0x750924, 0x80 apart) */
LIFT_PLAIN(lobbyTop_drawTitle, 408680)
