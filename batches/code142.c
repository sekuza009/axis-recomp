/* batch 141 (lifted/grp87.c): the create-arena screen */
#include "lifted/grp87.c"
/* 0x40b750 arena_createDraw(): room_drawGameSettings' form for a new arena (window 0x4dbb00..): title 0x752c24,
   labels 0x752ca4.., the arena name 0x4db528 and the password 0x4db54e as '*' (into a 10-byte buffer; each hidden
   while edited: 0x4dbab0 / 0x4dbacc), the map (0x4db548, a 0x5ae9d0 name; or, custom 0x4db54a, set lower), players
   (0x4db549), the kind (0x4db54a, a 0x4dbba4 string, 5 apart), mode (0x4db54b, a 0x75c9a4 string), two limits (bytes
   0x4db54c / 0x4db54d, hidden while edited: 0x4db850 / 0x4db518); the hovered value highlighted unless something
   is open (0x68039c, 0x4db55c, 0x907b2c, 0x4db508); two button rows (0x7530a4, 0x7531a4); the preview
   (arena_drawCustomOption), its arrows and the custom button (0x75d8a4, bright for custom rules); the confirmation
   box (0x4db55c: 0x753224 / 0x7532a4 and two buttons by arena_4045a0) and the lock box (0x907b2c: 0x74dfa4 /
   0x74e024); the border */
LIFT_PLAIN(arena_createDraw, 40b750)
