/* batch 135 (lifted/grp81.c): the room's ranking table */
#include "lifted/grp81.c"
/* 0x43d060 room_43d060(): the ranking window (0x9dced8..): frame, title 0x75aba4; the page arrows (the hovered one,
   room_4323c0, lit) and "first - last" of page 0x9dd6ac (also stored: 0x9dd83c, 0x9dd7dc); the sort label 0x75ac24
   and the sort column (0x9dd1d0: 0..3, one of 0x75ae24 / 0x75af24 / 0x75b024 / 0x75aea4); two lines and the column
   heads (0x75aca4..0x75b024, the sorted one bright); with a list (0x9dd3b0) up to ten 0x44-byte rows (name at
   0x9dcef4, its rank at -4) until an empty name (which stores the page in 0x9dd4b8): rank, name, rank icon
   (+0x32, cell of the font texture 0x76d448), "%8.1f" (+0x36), "%3.2f" (+0x2e) and three counts (+0x26, +0x2a,
   +0x1e), the sorted column in yellow; a line, three buttons (0x75b0a4; the middle one dead while 0x9dd6b8 is
   clear); while loading (0x9dd6b8) the blinking 0x75b1a4 (alpha from 0x4dba80 * k % 10); the border */
LIFT_PLAIN(room_43d060, 43d060)
