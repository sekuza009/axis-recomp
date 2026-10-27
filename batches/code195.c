/* batch 194 (lifted/grp150.c): the in-match network packets */
#include "lifted/grp150.c"
/* 0x48c830 net_processGamePacket(from, type, packet) (thiscall on the scene, ret 0xc): only type 0x40; recorded to
   the replay file first when recording (+0x2340d1d, 0x46cc30); while waiting for the start (+0x233cc20) only kind
   1. By the kind (byte 1): 0 a player's state (position, aim, weapon, the five weapon slots), 1 the game state (time,
   map, scores, the checksums of the map tables, the item states), 2 a player joining (name, team, settings,
   weapons), 3..5 pause / resume, 6..11 player events (name, team changes, leaving), 12 a player's record, 13 a
   timer, 14 the items' states; other kinds go to 0x48b420 (a no-op). The scene's handlers are stubbed */
static THISCALL DWORD net_processGamePacket(char *s, DWORD from, DWORD type, DWORD pkt) { DWORD v[3] = { from, type, pkt }; return run_lifted(lift_48c830, (DWORD)s, 3, v); }
