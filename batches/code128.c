/* batch 127 (lifted/grp73.c): the room's player-info panel */
#include "lifted/grp73.c"
/* 0x43a420 room_43a420(): while waiting (0x9dd6d4 == 1) only a box with two lines (0x75b1a4, 0x74f724); else the
   panel (window 0x9dd368..): line, title 0x7592a4, labels (0x759324 five, 0x7595a4 seven, 0x80 apart), four field
   boxes, the name 0x9dd1d8, three password fields as '*' (0x9dd6d8 / 0x9dd1f6 / 0x9dd202, each hidden while
   edited: 0x9dd69c / 0x9dd37c / 0x9dd378) and 0x9dd20e (0x9dd304), the level 0x9dd5d8 with its rank icon (cell
   (level - 1) % 10, / 10 of the font texture 0x76d448), the clan 0x9dd248 (or 0x759924 when none), two ratios
   ("%.2f": 0x9dd5e4, 0x9dd5f4) and three counts (0x9dd5ec, 0x9dd5f0, 0x9dd5dc); three buttons, a line, the border */
LIFT_PLAIN(room_43a420, 43a420)
