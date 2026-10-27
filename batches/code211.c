/* batch 210 (lifted/grp174.c): the game mode's frame */
#include "lifted/grp174.c"
/* 0x4988e0 game_processGameMode() (thiscall on the scene; 16.7 KB): with a log (0x9f67ec, 0x76d410) the ranking
   is written to a file; then by the mode (0x76d368: deathmatch, team, sudden death, arenas, gladiator ...) the
   round's clock, frags and the ranking tables (+0x23428f6 / +0x2342936), respawns and team changes, the end of
   the round and of the match, the camera and the replay; the scene's parts loaded and updated (@0x498dd8 /
   @0x49a54f: 0x473780, the patch DLL's cat_wrap); messages, sounds and the network packets of each event */
static THISCALL DWORD game_processGameMode(char *s) { return run_lifted(lift_4988e0, (DWORD)s, 0, NULL); }
