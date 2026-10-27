/* batch 109 (lifted/grp55.c) */
#include "lifted/grp55.c"
/* 0x45e170 (thiscall on the scene) hud_45e170(vv, draw): actor_updateAllParts for every active actor
   (+0x1cd94b0 == 1, count +0x202e8c8) */
static THISCALL DWORD hud_45e170(char *sc, DWORD vv, DWORD draw) { DWORD v[2] = { vv, draw }; return run_lifted(lift_45e170, (DWORD)sc, 2, v); }
/* 0x45dc00 (thiscall) FUN_0045dc00(actor, a, b, &player): claim actor slot `actor` (100 or more: -1): slots past the
   count are cleared and the count grows to cover it; the first free slot is noted (+0x202e8cc); the mech is built
   (actor_setupFromParts); returns the slot. 0x45dd80 match_45dd80(the same): also makes it the player's actor
   (+0x202e8d4) with weapon slot 0 (FUN_0045e810). 0x45ddc0 armc_45ddc0(): the player's actor again, from its own
   player and the start position (0xa0e7a8..) */
static THISCALL DWORD FUN_0045dc00(char *sc, DWORD a, DWORD x, DWORD y, DWORD pp) { DWORD v[4] = { a, x, y, pp }; return run_lifted(lift_45dc00, (DWORD)sc, 4, v); }
static THISCALL DWORD match_45dd80(char *sc, DWORD a, DWORD x, DWORD y, DWORD pp) { DWORD v[4] = { a, x, y, pp }; return run_lifted(lift_45dd80, (DWORD)sc, 4, v); }
static THISCALL DWORD armc_45ddc0(char *sc) { return run_lifted(lift_45ddc0, (DWORD)sc, 0, NULL); }
/* 0x45de20 (thiscall) actor_applySpawnRecord(actor, rec): build the actor's mech for the player's actor slot
   (+0x202e8d4; negative is fatal) from a spawn record (player, position...), then override its stats from the
   record's ints (+0x1c..: scaled to floats) and reset two fields to -NaN */
static THISCALL DWORD actor_applySpawnRecord(char *sc, DWORD a, DWORD rec) { DWORD v[2] = { a, rec }; return run_lifted(lift_45de20, (DWORD)sc, 2, v); }
