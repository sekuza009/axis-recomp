/* batch 169 (lifted/grp115.c, grp116.c, grp117.c: split so that the calls between these go through their native
   addresses, where the tests stub them): the armour centre's part selection */
#include "lifted/grp115.c"
#include "lifted/grp116.c"
#include "lifted/grp117.c"
/* the armour centre: the part kind being chosen 0x4dbe48 (0..3 armour parts from the list 0x4dc79c (count
   0x4dc244), 4 / 5 the others from 0x4dcca4 (count 0x4dc778), -1 none), the list position 0x4dc77c, the chosen
   parts 0x4dcb20 / 24 / 28 / 2c (armour) and 0x4dcb18 / 0x4dcb1c.
   0x40f950 armc_40f950(): the position wrapped into its list, that part previewed (armc_41cca0), the snapshot 6
   (armc_snapshot), the lobby player's part re-applied (armc_461540 on the game 0x9087b4), then armc_41c510 */
LIFT_PLAIN(armc_40f950, 40f950)
/* 0x40f870 armc_40f870(kind): switch to part kind: the position of the kind's chosen part in its list; for the
   armour kinds the weapon / part shown on the scene's actor (actor_selectWeapon), then armc_40f950 */
LIFT_PLAIN(armc_40f870, 40f870)
/* 0x40f9e0 armc_40f9e0(): take the part under the position as the kind's choice, the slot redrawn (armc_41ca50),
   its snapshot, all six choices sent to the lobby player (armc_461250, 14 arguments), back to no kind */
LIFT_PLAIN(armc_40f9e0, 40f9e0)
/* 0x40f220 armc_drawPartScreen(): enter the part screen (page 2): the six slots drawn (armc_41ca50), the armour
   choice previewed, the seven snapshots, no kind, the panel (armc_41b300) */
LIFT_PLAIN(armc_drawPartScreen, 40f220)
/* 0x40f0f0 armc_exit(save): leave the armour centre by how it was entered (0x4dc24c: 1 / 3 with armc_40e670, 2 back
   to the lobby page 0): with save the selection kept (armc_saveSelection) or sent (armc_sendSelectionToNet); the
   camera and light back, menu sound 4, the menu music, the main menu page 0x66 -> 0x67 when 0x76d410 */
LIFT_PLAIN(armc_exit, 40f0f0)
