/* batch 164 (lifted/grp110.c): mission settings keys, three jump stubs */
#include "lifted/grp110.c"
/* 0x447c30 menu_447c30(): on the unlock screen, cancel (0x76d48c) or back (0x9dae70) closes it (0x9f62e0 = 0) */
LIFT_PLAIN(menu_447c30, 447c30)
/* 0x447b40 menu_447b40(): the mission settings keys: cancel / 0x4e0cdc leave (FUN_00447960), 0x4e1510 start
   (mission_4479d0), 0x9dae14 / 0x9db974 the mission down / up within the unlocked count 0x9f181c and 0..14
   (mission_4479b0); holding 0x6803a8 and 0x4df9fc and pressing 0x4df90c unlocks all 16 (the cheat) */
LIFT_PLAIN(menu_447b40, 447b40)
/* 0x447c70 menu_447c70(): in the mission settings (0x9f62f8 past 1), no dialog, not busy (0x9f6300): the unlock
   screen's keys (0x9f62e0) or the settings keys */
LIFT_PLAIN(menu_447c70, 447c70)
/* jump stubs: 0x44aa30 missionsel_44aa30 -> missionsel_drawScreen, 0x445bd0 skirmish_445bd0 ->
   skirmish_drawScreenB, 0x4532e0 jmp_net_getLocalAddress_4532e0 -> net_getLocalAddress */
LIFT_PLAIN(missionsel_44aa30, 44aa30)
LIFT_PLAIN(skirmish_445bd0, 445bd0)
LIFT_PLAIN(jmp_net_getLocalAddress_4532e0, 4532e0)
