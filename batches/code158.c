/* batch 157 (lifted/grp103.c): DirectPlay create, host, join and player names */
#include "lifted/grp103.c"
/* 0x454190 dplay_getPlayerName(id, out): asks the DPNAME size (GetPlayerName with no buffer), allocates and locks a
   global block of it and fetches the name into it (*out = the block, 0); on a failure frees the block and returns the
   error (0x8007000e when the allocation fails) */
LIFT_PLAIN(dplay_getPlayerName, 454190)
/* 0x453790 dplay_create(): through the lobby (CoCreateInstance into 0xa0b398): the connection settings (size query,
   then into the global block 0xa0baf4; session flags 0x44, max players 16), SetConnectionSettings, ConnectEx into
   0xa0b404, CreatePlayer, host or client by the session flags (0xa0baf8); then (also when the lobby part fails)
   a plain DirectPlay object (arena_4539f0) and EnumConnections with dplay_enumConnections; frees the block */
LIFT_PLAIN(dplay_create, 453790)
/* 0x453cf0 dplay_hostSession(max, name, a3, a4, a5, c6, c7, data): fills the session description 0xa0b3b0 (the
   connection kind 0's address from net_getLocalAddress / arena_4542a0), Open as host, CreatePlayer named name;
   the player id into 0xa0b424, data into 0xa0b428, host flag 0xa0baf8, then claims a player slot (arena_451410).
   0 without a DirectPlay object or on a failure, else 1 */
LIFT_PLAIN8(dplay_hostSession, 453cf0)
/* 0x453e60 dplay_joinSession(guid, name, data): Open the session guid, CreatePlayer; 0x1f4 joined (or another
   CreatePlayer error), 0x1f6 / 0x1f8 / 0x1f9 Open errors, 0x1fa the session full or refused, 0x1fb no DirectPlay */
LIFT_PLAIN(dplay_joinSession, 453e60)
