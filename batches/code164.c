/* batch 163 (lifted/grp109.c): screen dispatchers (setup tabs, lobby / room / profile keys and
   draws) */
#include "lifted/grp109.c"
/* 0x422b30 setup_drawTab() / 0x4230a0 setup_processTabKeys(): no dialog open: the setup tab 0x4ddac8 (0..2, 0x29a)
   drawn / its keys */
LIFT_PLAIN(setup_drawTab, 422b30)
LIFT_PLAIN(setup_processTabKeys, 4230a0)
/* 0x4081f0 lobby_processKeys(): by lobby page 0x4db51c (0..5), typing (0x907b2c), the dialog flags 0x4db508 /
   0x4db55c */
LIFT_PLAIN(lobby_processKeys, 4081f0)
/* 0x4378e0 menu_4378e0() / 0x436800 room_processKeys(): the room's mouse / keys by page 0x9dd834 (0..0x63, byte
   table), its sub-mode 0x9dd850, popup 0x9dd7d8 and dialogs 0x4db508 / 0x4db8b4 */
LIFT_PLAIN(menu_4378e0, 4378e0)
LIFT_PLAIN(room_processKeys, 436800)
/* 0x44f410 profile_44f410(): the profile screen: a message timer (0x9f900c, 0x9f8f18 up to 0x4a944c), with a dialog
   its box (0x428c30) and maybe 0x44b600, else 0x44bd20 when 0x9f8d68 and the profile frame 0x44d720 */
LIFT_PLAIN(profile_44f410, 44f410)
/* 0x43ed20 room_43ed20() / 0x40d390 lobbyCreate_draw(): the room / create-game screen: its draw, then (entered, not
   leaving) the dialog box or: the settings bytes kept in range (players 0..16, limits, map), the panel, the dialog,
   the chat */
LIFT_PLAIN(room_43ed20, 43ed20)
LIFT_PLAIN(lobbyCreate_draw, 40d390)
