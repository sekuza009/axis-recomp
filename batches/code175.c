/* batch 174 (lifted/grp124.c): returning from a match to the menus (four variants: state, camera, DirectPlay
   left or kept, keyboard back), the room's settings page mouse room_4036c0, the skirmish / mission state entries, room_434490 (a room request
   sent), with their callees stubbed (tools/gentests.py); the in-match player messages (thiscall on the game),
   music_playMatch, dplay_closeSession */
#include "lifted/grp124.c"
LIFT_PLAIN(game_returnToMenus_41ec50, 41ec50)
LIFT_PLAIN(game_returnToMenus_41e8b0, 41e8b0)
LIFT_PLAIN(game_returnToMenus_41e9d0, 41e9d0)
LIFT_PLAIN(game_returnToMenus_41eb00, 41eb00)
LIFT_PLAIN(room_4036c0, 4036c0)
LIFT_PLAIN(menuState900_enterSkirmish, 443950)
LIFT_PLAIN(room_434490, 434490)
LIFT_PLAIN(menuState500_enter, 447750)
/* 0x462b50 msg_playerConnected(game, player) / 0x462c30 msg_chatLine(game, player, text, from): the message
   by mode 0x9dae74 (a chat line only from someone else, 0x234243e) and a sound */
static THISCALL DWORD msg_playerConnected(char *game, DWORD p) { DWORD v[1] = { p }; return run_lifted(lift_462b50, (DWORD)game, 1, v); }
static THISCALL DWORD msg_chatLine(char *game, DWORD p, DWORD t, DWORD f) { DWORD v[3] = { p, t, f }; return run_lifted(lift_462c30, (DWORD)game, 3, v); }
/* 0x462850 music_playMatch() (thiscall on the game): the match music by the map's kind */
LIFT_PLAIN(music_playMatch, 462850)
/* 0x453a10 dplay_closeSession(obj): Close and Release a DirectPlay object (0 without one) */
LIFT_PLAIN(dplay_closeSession, 453a10)
