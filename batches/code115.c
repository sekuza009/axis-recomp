/* batch 114 (lifted/grp60.c) */
#include "lifted/grp60.c"
/* 0x41fd40 console_init: the console's start: pending node list freed (0x67fb3c, FUN_00441190), the five profile
   files checked unless skipped (0x76d410; a missing one: "Run AxisPlay.exe" and exit), the aspect ratio, the clock
   check, the window ("Axis Console", glWindow_init, parent 0x4ded18); a direct start (0x9db990) starts mode 3
   (app_requireCd on the game 0x9087b4); else the round's console file (console_loadFile, round 0x9dad94): none
   sends the menu to 400 / 800 by start mode 0x5ae9c4; with it, mode 1 clamps the selections 0x4dc878.. and loads
   the pilot profiles, modes 1 / 3 start a session, and the round's name (0x907b30) goes to FUN_00461ec0 */
LIFT_PLAIN(console_init, 41fd40)
