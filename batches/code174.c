/* batch 173 (lifted/grp123.c): small functions tested with their callees stubbed (tools/gentests.py): the
   in-match messages (connection lost, network unstable, server / user ends the game, data loss, frag / time
   limit: a message by mode 0x9dae74 and a sound), the arena slots 3 / 4 join wrappers, dplay_coInit,
   lobby_close, the room / lobby / setup key and mouse pages, setup_drawTopPage, profile_44f4b0,
   mainmenu_441810 */
#include "lifted/grp123.c"
LIFT_PLAIN(msg_connectionLost, 463390)
LIFT_PLAIN(msg_networkUnstable, 4633c0)
LIFT_PLAIN(msg_serverEndsGame, 462f30)
LIFT_PLAIN(msg_userEndsGame, 462f60)
LIFT_PLAIN(msg_dataLoss, 4633f0)
LIFT_PLAIN(msg_fragLimitReached, 462f90)
LIFT_PLAIN(msg_timeLimitReached, 462fd0)
LIFT_PLAIN(arena_454c50, 454c50)
LIFT_PLAIN(arena_454d60, 454d60)
LIFT_PLAIN(dplay_coInit, 453720)
LIFT_PLAIN(lobby_close, 406b60)
LIFT_PLAIN(FUN_00403870, 403870)
LIFT_PLAIN(room_435f40, 435f40)
LIFT_PLAIN(room_435e70, 435e70)
LIFT_PLAIN(room_433c70, 433c70)
LIFT_PLAIN(lobby_keysQuit, 408110)
LIFT_PLAIN(setup_topPageKeys, 422b70)
LIFT_PLAIN(setup_graphicTabKeys, 422d20)
LIFT_PLAIN(lobbyTop_keys, 407750)
LIFT_PLAIN(setup_drawTopPage, 4220c0)
LIFT_PLAIN(lobby_406950, 406950)
LIFT_PLAIN(lobby_407300, 407300)
LIFT_PLAIN(lobbyPlayer_keys, 407840)
LIFT_PLAIN(room_433d30, 433d30)
LIFT_PLAIN(profile_44f4b0, 44f4b0)
LIFT_PLAIN(mainmenu_441810, 441810)
