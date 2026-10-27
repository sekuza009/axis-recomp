/* batch 136 (lifted/grp82.c): the room's game list */
#include "lifted/grp82.c"
/* 0x43adc0 room_43adc0(): the game list (window 0x9dd4a8..): frame, title 0x759ca4, five column heads
   (0x759d24..0x759f24), lines; with a list (0x9dd330) of 0x67ef30 games, nine rows from 0x680bb0 of the 0x4a-byte
   game records (0x9087c4): a lock icon (+0x43) from the font texture, the selected game (0x76d41c) highlighted, the
   name (+0, at most 32), the map (+0x21, a 0x907b30 name, at most 13) or, set (+0x20), 0x75c1a4; the mode (+0x28,
   a 0x7673a4 string), "players / max" (+0x23, +0x22) and +0x24; the page "current / pages" (0x680bb8, 0xa0b358);
   four buttons (0x759fa4; the hovered one, room_432300, bright, the first dead without games, all dim while
   joining 0x9dd6b4); the scroll arrows; the blinking 0x75a1a4 while 0x9dd6a0 / 0x9dd3fc (alpha from 0x4dba80); the
   joining box (0x74f124 and the room name 0x9dcee8); the confirmation (0x4db8b4: 0x752aa4 / 0x752b24, its button
   0x751824 by room_432340); the border */
LIFT_PLAIN(room_43adc0, 43adc0)
