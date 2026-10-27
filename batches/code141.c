/* batch 140 (lifted/grp86.c): the arena's game list */
#include "lifted/grp86.c"
/* 0x40a070 arena_40a070(): room_43adc0's game list for the arena (window 0x4db8c8..): frame, a line, title 0x7524a4;
   three tabs (0x752524; the hovered one, arena_4044a0, bright unless a box is open: 0x4db8b4, 0x907b2c, 0x4db714,
   0x4db8bc); five column heads; with a list (0x4dbac8, or 0x4dbaa8 which also shows locks and the last column)
   nine rows of the 0x4a-byte game records from 0x680bb0 (the mode as a 0x4db8d8 kind string), the page
   "current / pages" (0x680bb8, 0xa0b368 or the game count 0x67ef30); three buttons (0x7528a4; the second dead
   without games, the third while searching 0x4dba90 / 0x4db858); scroll arrows; the blinking 0x752a24 while
   searching or 0x4db8b8 (alpha from 0x4dba80); the joining box (0x4db8bc: 0x74f124 and the arena name 0x4db520),
   the full box (0x4db714: 0x74f624), the confirmation (0x4db8b4: 0x752aa4 / 0x752b24, its button 0x751824 by
   arena_4044e0); the border */
LIFT_PLAIN(arena_40a070, 40a070)
