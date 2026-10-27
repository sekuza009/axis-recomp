/* batch 170 (lifted/grp118.c, grp119.c, grp120.c: split so the calls between these go through their native
   addresses, where the tests stub them): the armour centre's states and input */
#include "lifted/grp118.c"
#include "lifted/grp119.c"
#include "lifted/grp120.c"
/* the armour centre's pages (0x4dc798): 0x40fb20 armc_40fb20(): the mouse on the main page (armc_40e450's buttons:
   parts, colours, the part screen (armc_drawPartScreen), back (armc_exit) ...); 0x4101e0 armc_4101e0(): the main
   page's keys (one binding after another: parts, colours, the rotation toggle 0x4dceac, back); 0x410500
   armc_410500(): the part screen's keys (kinds armc_40f870, positions 0x4dc77c with armc_40f950, take
   armc_40f9e0, back); 0x410810 armc_410810(): the colour page's keys (armc_backupColours, back) */
LIFT_PLAIN(armc_40fb20, 40fb20)
LIFT_PLAIN(armc_4101e0, 4101e0)
LIFT_PLAIN(armc_410500, 410500)
LIFT_PLAIN(armc_410810, 410810)
/* 0x410190 armc_onStateEnter(): in a state past 1 (0x4dc790), no dialog: the mouse of page 0x4dc798 (1..4) */
LIFT_PLAIN(armc_onStateEnter, 410190)
/* 0x410ab0 armc_processInput(): the armour centre's frame input: entering (state 0x4dc790 0 / 1: the menu camera
   and projection set up, the camera eased in), the page's keys (armc_4101e0 / armc_410500 / armc_410810), the
   held rotation keys turning the camera, leaving (state 3: the camera eased out, then armc_433360 or the arena's
   load-and-quit when the main menu page is 0x67) */
LIFT_PLAIN(armc_processInput, 410ab0)
