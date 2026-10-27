/* batch 156 (lifted/grp102.c): DirectPlay release and session enumeration, the arena's four connection slots */
#include "lifted/grp102.c"
/* 0x453920 dplay_release(): releases the lobby (0xa0b398) and the DirectPlay object (0xa0b404: destroys the local
   player 0xa0b424, Close, Release), frees the session list 0xa0baf0, unlocks and frees the global blocks 0xa0bab0 /
   0xa0baf4 and calls CoUninitialize; returns 0 */
LIFT_PLAIN(dplay_release, 453920)
/* 0x453fd0 dplay_enumSessions(): a 0x50-byte session description (the application GUID *0xa0bad8, the game's
   GUID 0x4a96e8), EnumSessions with the callback 0x453560 for connection kinds 0 and 1 (0xa0b418); 0 if there
   is no DirectPlay object or the call fails, else 1 */
LIFT_PLAIN(dplay_enumSessions, 453fd0)
/* the arena's connection slots 0xa0d7a4 .. 0xa0d7b0: release (clearing the slot) or enumerate when it is open */
LIFT_PLAIN(arena_4549a0, 4549a0)
LIFT_PLAIN(arena_4549c0, 4549c0)
LIFT_PLAIN(arena_454ac0, 454ac0)
LIFT_PLAIN(arena_454ae0, 454ae0)
LIFT_PLAIN(arena_454bd0, 454bd0)
LIFT_PLAIN(arena_454bf0, 454bf0)
LIFT_PLAIN(arena_454ce0, 454ce0)
LIFT_PLAIN(arena_454d00, 454d00)
/* 0x453260 arena_453260(): enumerates through the slot of the connection kind 0xa0b418 (0..3), else 0 */
LIFT_PLAIN(arena_453260, 453260)
