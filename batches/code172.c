/* batch 171 (lifted/grp121.c): small menu, room and connection functions */
#include "lifted/grp121.c"
/* 0x453770 arena_453770(): DirectPlay up again: arena_4509e0, dplay_create, dplay_release when it worked; 0 */
LIFT_PLAIN(arena_453770, 453770)
/* 0x4014c0 wnd_4014c0(): keyboard and mouse released, then DirectInput 0x4d1e98 */
LIFT_PLAIN(wnd_4014c0, 4014c0)
/* the arena's connection slots 0xa0d7a4 / 0xa0d7a8: host (dplay_hostSession, 8 arguments: 0x4549e0 / 0x454b00) or
   join (dplay_joinSession: 0x454a20 / 0x454b40; 0x1f4 when the slot is closed) through them */
LIFT_PLAIN8(arena_4549e0, 4549e0)
LIFT_PLAIN(arena_454a20, 454a20)
LIFT_PLAIN8(arena_454b00, 454b00)
LIFT_PLAIN(arena_454b40, 454b40)
/* 0x403530 room_403530() / 0x4034e0 room_4034e0(): menu sound 0, the room's 0x67ef00 entries (8 bytes from
   0x4d7358) cleared / all set */
LIFT_PLAIN(room_403530, 403530)
LIFT_PLAIN(room_4034e0, 4034e0)
/* key pages: cancel (0x4e0cdc) or OK (0x4e1510, sound 2) closes the page: 0x407970 lobbyJoin_keys (0x907b2c),
   0x436940 menu_436940 (0x9dd850), 0x4080c0 lobby_keysBack (0x907b2c, not with a dialog), 0x4370e0 menu_4370e0
   (0x9dd6c4) */
LIFT_PLAIN(lobbyJoin_keys, 407970)
LIFT_PLAIN(menu_436940, 436940)
LIFT_PLAIN(lobby_keysBack, 4080c0)
LIFT_PLAIN(menu_4370e0, 4370e0)
/* 0x44ac90 match_44ac90(x, y, len): start typing (keyboard released, input cleared, the edit box at x / y) */
LIFT_PLAIN(match_44ac90, 44ac90)
/* 0x44ace0 match_44ace0(): stop typing: the typed line 0x9dc92c kept in 0x9f63e4 (flag 0x9f67e8), the input buffer
   reset, the keyboard back */
LIFT_PLAIN(match_44ace0, 44ace0)
/* 0x441770 mainmenu_441770(): the first of the 0x9dd928 entries (0x44 bytes from 0x9ddac8) marked 1 opens its page */
LIFT_PLAIN(mainmenu_441770, 441770)
/* 0x435ce0 room_435ce0(): a click on the room's close button (room_432280) closes the popup 0x9dd6c4 */
LIFT_PLAIN(room_435ce0, 435ce0)
