/* batch 178 (lifted/grp128.c): game_postMatch (after a match: by mode back to the room, arena, lobby or menus,
   the result sent, the music) and dplay_initConnection */
#include "lifted/grp128.c"
LIFT_PLAIN(game_postMatch, 420100)
/* 0x453a90 dplay_initConnection(kind, address): a fresh DirectPlay object for connection kind 0..3 (TCP/IP: the
   host address as a compound address from the lobby; the others stored), InitializeConnection, the caps' three
   values into 0xa0bb00; 1, or 0 on a failure */
LIFT_PLAIN(dplay_initConnection, 453a90)
