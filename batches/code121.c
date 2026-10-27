/* batch 120 (lifted/grp66.c): the room's server dialog and the two skirmish briefing screens */
#include "lifted/grp66.c"
/* 0x439e00 room_439e00(): the room's server dialog (only its frame while a message is open): title 0x758da4, an
   underline, the server name 0x9dd1d8 in a green-framed box, a note 0x758e24, two buttons (0x758f24, the one under
   the cursor bright); with the confirmation open (0x9dd850) a dimmed screen, a box with two lines (0x74dfa4,
   0x74e024) and its two buttons (0x7517a4); the border */
LIFT_PLAIN(room_439e00, 439e00)
/* 0x4456b0 skirmish_drawScreenB(): the mission briefing: a translucent window (0x9f16a8..), title 0x75e024, a cyan
   frame and line, the typewriter text (skirmish_445520), two buttons (0x75e2a4) and the back / start buttons
   (0x75e3a4): back greyed until the briefing is done (0x4d7348), start greyed without a mission (0x9f1060) */
LIFT_PLAIN(skirmish_drawScreenB, 4456b0)
/* 0x444f40 skirmish_drawScreenA(): the mission list: window, title 0x75dda4, column heads (0x75de24..0x75dfa4) on
   blue bars, up to 8 rows of the 0xfc-byte mission records (0x9ef2d4, count 0x9ef2c0, from 0x9f16bc): name,
   +0x40 text, +0xe0 number (_itoa), +0xe8 kind (a 0x75dda4 string), the selected one (0x9f16a4) highlighted and
   its description (+0x60) below; two buttons (0x75e0a4) */
LIFT_PLAIN(skirmish_drawScreenA, 444f40)
