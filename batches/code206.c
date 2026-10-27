/* batch 205 (lifted/grp164.c .. grp166.c): the mission-select state, the main loop's frame, two HUD panels */
#include "lifted/grp164.c"
/* 0x44aa40 menuState500_missionSelect(): the mission-select screen's frame (119 bytes; functions.csv said 4099):
   0x441740 while 0x9f63b8, 0x448140 unless page 0x9f62f8 is 2, the draw (0x447cb0); on pages other than 0 / 1 a
   dialog (0x90d1c4) draws its box (0x428c30 with 0x9f6308 .. 0x9f6314), else unless 0x9f6300 the input
   (0x44aa30 with 0x9f62e0, else 0x44aa20) by tail call */
LIFT_PLAIN(menuState500_missionSelect, 44aa40)
#include "lifted/grp165.c"
/* 0x420280 main_loop(): one frame: in a match (screen 0x76d3e8 == 9999) 0x41f970 unless 0x67ef0c is 9999 too,
   the input (0x445c60, 0x4012c0) unless 0x68039c, the match frame (main_462050 on the scene 0x9087b4); its 0 ends
   the match (game_postMatch by tail call); outside a match the menus' frame (menu_frame by tail call) */
LIFT_PLAIN(main_loop, 420280)
#include "lifted/grp166.c"
/* 0x494930 hud_drawRanking() (thiscall on the scene): the ranking panel: the mode's name ("%s RANKING" from the
   64-byte table 0x4c7030 by +0x22e7180); in team games (+0x22e7184 == 1) both teams in score order (0x463780,
   scores +0x2221fb8), each team's ranked players (+0x23428f6, +0x2342976 of them, by 0x463740 on their team)
   with name, emblem (0x4922c0 when +0x233c9f0), flag (0x4924d0 by the player's +0x179d1f6), "KILL/DEATH" and
   "TIME mm:ss" and the leader icon (0x496820); else the ranked players the same way; then the players in use
   (FUN_004a8700) without a team (+0x80 < 0). The local player (+0x234240d) is highlighted */
static THISCALL DWORD hud_drawRanking(char *s) { return run_lifted(lift_494930, (DWORD)s, 0, NULL); }
/* 0x496240 hud_496240() (thiscall on the scene): the team score box: both teams' bars (0x46bd60) and scores ("%d"
   by 0x463780), the local player's team marked (0x463740 -> 0x46bd00), then three counters (+0x234297e,
   +0x2342982, +0x2342986), all scaled from the screen size (0x4685b0 / 0x4685c0) */
static THISCALL DWORD hud_496240(char *s) { return run_lifted(lift_496240, (DWORD)s, 0, NULL); }
