/* batch 72 (lifted/grp19.c) */
#include "lifted/grp19.c"
/* 0x45ee40 (thiscall) armc_computeTotals(actor): the "data loss" check game_processGameMode runs every 20 s on the
   local player's actor (0x8888 apart from +0x1cd93a8): an actor not in state 1 (+0x14c) passes; else its mech's stats
   are recomputed from the player record (+0x1561b68, 0x47fd2 apart: pilot +0x44 into the table at 0x9f9078, the
   parts +0x30c..+0x31c into their tables, six items +0x320 with their bonuses) and the game mode (+0x20f3ab8,
   +0x20f3acc), and every field of the actor's stat block must agree within 0.1 (some exactly), its limits must hold
   and its heat values stay <= 30. Returns 1 if all agree, else 0. 0x88a0-byte frame (_chkstk), eight stack objects
   with an SEH frame for their destructors */
static THISCALL DWORD armc_computeTotals(char *scene, DWORD actor) { DWORD v[1] = { actor }; return run_lifted(lift_45ee40, (DWORD)scene, 1, v); }
