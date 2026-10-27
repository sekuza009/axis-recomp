/* batch 184 (lifted/grp135.c, grp136.c: menuState800_gameRoom on its own so its call to room_43e290 goes through
   the native address, where the test stubs it): the menu state dispatchers lobby_onStateChange, menuState400_frame,
   menu_onStateChange, menuState800_gameRoom, the room screen room_43e290, arena_launchFromFile (a match started
   from a launch file), with their callees stubbed (tools/gentests.py) */
#include "lifted/grp135.c"
#include "lifted/grp136.c"
LIFT_PLAIN(lobby_onStateChange, 4076c0)
LIFT_PLAIN(menuState400_frame, 40d450)
LIFT_PLAIN(menu_onStateChange, 445e40)
LIFT_PLAIN(room_43e290, 43e290)
LIFT_PLAIN(arena_launchFromFile, 410b50)
LIFT_PLAIN(menuState800_gameRoom, 43ef70)
