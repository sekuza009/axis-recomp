/* batch 153 (lifted/grp99.c): HUD messages */
#include "lifted/grp99.c"
/* 0x495140 hud_drawPressFire(): "Press fire button to start" centred low (hud_44ae10, patched: native) */
LIFT_PLAIN(hud_drawPressFire, 495140)
/* 0x496c20 (thiscall on the game) hud_drawReadyStart(): the countdown (+0x233cc4c): "READY %d" in yellow, below 1
   "START!" in red, large; at 0 or below the game's message +0x2342f06 */
static THISCALL DWORD hud_drawReadyStart(char *game) { return run_lifted(lift_496c20, (DWORD)game, 0, NULL); }
/* 0x496d10 (thiscall on the game) hud_drawRecordIndicator(): while recording, blinking by the time +0x2340d29: the
   record icon (replay_drawIcon 4), the time as "%02d:%02d" and "[AutoPlay %s]" with the file name +0x2340d0c */
static THISCALL DWORD hud_drawRecordIndicator(char *game) { return run_lifted(lift_496d10, (DWORD)game, 0, NULL); }
/* 0x496a30 (thiscall on the game) hud_drawMatchResult(): team games (+0x22e7184 == 1): a band and "RED TEAM WIN!" /
   "BLUE TEAM WIN!" / "DRAW GAME!" by the winning team (FUN_00463740 of +0x23423bd); else, if the top player
   (FUN_004625a0) has +0x14c set, "Top Player : %s" with its name +0x98 */
static THISCALL DWORD hud_drawMatchResult(char *game) { return run_lifted(lift_496a30, (DWORD)game, 0, NULL); }
