/* batch 180 (lifted/grp130.c): menu_drawBackground (the menus' animated background: the list 0x67fb3c's camera,
   the projection, its draw), the arena slots' connect (a fresh DirectPlay for that kind, dplay_initConnection,
   the slot open or released), room_435c20, with their callees stubbed (tools/gentests.py); match_4620e0 and
   arena_453090 by hand */
#include "lifted/grp130.c"
LIFT_PLAIN(menu_drawBackground, 441740)
LIFT_PLAIN(arena_454940, 454940)
LIFT_PLAIN(arena_454a50, 454a50)
LIFT_PLAIN(arena_454b70, 454b70)
LIFT_PLAIN(arena_454c80, 454c80)
LIFT_PLAIN(room_435c20, 435c20)
/* 0x4620e0 match_4620e0() (thiscall on the scene): every player's scores cleared, the actors reset, the ranking */
LIFT_PLAIN(match_4620e0, 4620e0)
/* 0x453090 arena_453090(8 arguments): host through the slot of connection kind 0xa0b418 (0 otherwise) */
LIFT_PLAIN8(arena_453090, 453090)
