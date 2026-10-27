/* batch 145 (lifted/grp91.c): re-equipping the current player's armour part */
#include "lifted/grp91.c"
/* 0x461540 (thiscall on the game) armc_461540(slot): for the player in lobby slot +0x234240d (none when negative):
   keep the actor's part slot fields (+0x1eccbf0..+0x1eccc00 of its 0x8888-byte record at +0x1eccbb0; a negative
   slot means the actor's current one, +0x1eccbb0), mark whether it is the local player (+0x1eccf0c against
   +0x2221fa0), rebuild the actor's lists (armc_45ddc0 on the scene +0x1f36c8), put the kept fields back, and for
   slots above 3 first re-apply the stored slot +0x1eccbb4, then the slot (FUN_0045e810, actor_updatePart) */
static THISCALL DWORD armc_461540(char *game, DWORD slot) { DWORD v[1] = { slot }; return run_lifted(lift_461540, (DWORD)game, 1, v); }
