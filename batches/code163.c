/* batch 162 (lifted/grp108.c): skirmish / mission settings input, the room and arena text fields */
#include "lifted/grp108.c"
/* 0x443e20 skirmish_saveSettings(): no dialog open: a right click leaves (skirmish_443c80); a left click on the
   settings screen's buttons (skirmish_4438d0, 0x9ef228): rows 0..7 skirmish_443d50(row), 8 save (mission_saveAxisMis
   with the selection 0x9f16a4), 9 leave */
LIFT_PLAIN(skirmish_saveSettings, 443e20)
/* 0x447a50 mission_447a50(): the mission settings the same way (missionsel_447710, 0x9f6338): 0 start
   (mission_4479d0), 1 leave, 2 / 3 the mission 0x9f63b4 down / up within the unlocked 0x9f181c and 0..14 */
LIFT_PLAIN(mission_447a50, 447a50)
/* 0x4479d0 mission_4479d0(): mission 0x9f63b4 as the stage (0x9dad94), its map name (0x907b30) as the title
   0x67fb44, its limits (0x9db9e4 + 0x5c * m: 0x76d368, 0x4df8e8 frag, 0x76d408 time), leave the settings, state 3 */
LIFT_PLAIN(mission_4479d0, 4479d0)
/* 0x444070 menu_444070(): keys on the skirmish undo screen: back (0x4e0cd4) nothing, cancel (0x4e0cdc / 0x76d48c)
   to page 10, undo / redo (0x4e150c / 0x4e1514: FUN_00443d80 / FUN_00443de0) */
LIFT_PLAIN(menu_444070, 444070)
/* 0x443f20 skirmish_processKeys(): back / enter save (mission_saveAxisMis), cancel leaves, up / down held
   (0x9db0a0 / 0x76d330) repeat after a delay (0x76d37c / 0x680bb4: 4 frames, then the key repeat 0x4b071c) moving
   the selection (skirmish_443cd0 / 443d10) */
LIFT_PLAIN(skirmish_processKeys, 443f20)
/* 0x434320 room_434320() / 0x405010 arena_editTextField_405010(): start typing in the chat line: keyboard
   released, the input buffer cleared, an empty line at 0x9dc92c, the edit box placed by the room / arena chat
   position (0x9dd4a8 / 0x4db8c8 + 0xd8, + 0xd0), typing on (0x9dd6c8 / 0x4db70c) and the edit window created */
LIFT_PLAIN(room_434320, 434320)
LIFT_PLAIN(arena_editTextField_405010, 405010)
/* 0x443ef0 menu_443ef0() / 0x4440f0 menu_4440f0(): no dialog open: the skirmish settings (page 0x9ef1f8 10) or undo
   screen (0x14) mouse / keys (0x4440f0 only while 0x9ef1f0 is past 1) */
LIFT_PLAIN(menu_443ef0, 443ef0)
LIFT_PLAIN(menu_4440f0, 4440f0)
/* 0x447b10 mission_unlockCheat(): no dialog, not busy (0x9f6300): the unlock screen 0x9f62e0 (mission_447af0) or
   the mission settings mouse (mission_447a50) */
LIFT_PLAIN(mission_unlockCheat, 447b10)
/* 0x405200 FUN_00405200() / 0x434da0 room_434da0(): typing allowed (0x908807 + 0x4a * the player 0x76d41c): start
   the arena / room chat line (flag 0x4db8bc / 0x9dd6b4) */
LIFT_PLAIN(FUN_00405200, 405200)
LIFT_PLAIN(room_434da0, 434da0)
