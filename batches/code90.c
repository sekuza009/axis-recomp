/* batch 89 (lifted/grp35.c) */
#include "lifted/grp35.c"
/* (thiscall on the scene) FUN_0045e1f0 / actor_updateBody / FUN_0045e390 / FUN_0045e460 / FUN_0045e530(actor):
   for an active actor (0x8888 bytes at +0x1cd93a8, +0x108), its player's (+0x10c; 0x47fd2 at +0x1561b68) head /
   chest / arm / leg / booster type (player +0x30c..+0x31c) in that part's type table, variant actor +0x484: load
   the part's object list (data_loadFrom_46f4e0) with the player's own shape and skeleton caches, the variant's
   shape names and skeleton names, into the actor's memory (2000 / 2000 / 4000 / 4000 / 3000 bytes) */
static THISCALL DWORD FUN_0045e1f0(char *sc, DWORD a) { DWORD v[1] = { a }; return run_lifted(lift_45e1f0, (DWORD)sc, 1, v); }
static THISCALL DWORD actor_updateBody(char *sc, DWORD a) { DWORD v[1] = { a }; return run_lifted(lift_45e2c0, (DWORD)sc, 1, v); }
static THISCALL DWORD FUN_0045e390(char *sc, DWORD a) { DWORD v[1] = { a }; return run_lifted(lift_45e390, (DWORD)sc, 1, v); }
static THISCALL DWORD FUN_0045e460(char *sc, DWORD a) { DWORD v[1] = { a }; return run_lifted(lift_45e460, (DWORD)sc, 1, v); }
static THISCALL DWORD FUN_0045e530(char *sc, DWORD a) { DWORD v[1] = { a }; return run_lifted(lift_45e530, (DWORD)sc, 1, v); }
/* 0x45e600 (thiscall) actor_updatePart(actor, slot, variant): the item in the player's slot (+0x320 + slot * 4;
   0x2e18-byte items at +0x14d1ab4, < 0 none) with the scene's caches (+0x19e188c / +0x1cbe198): slot 4 and 5 their
   own lists (memory +0x58ac / +0x704c), the actor's current slot (+0x140) the weapon list (+0x410c) and its kind
   (item +0x2dc0 -> actor +0x4cc, -1 without an item); no item releases the list */
static THISCALL DWORD actor_updatePart(char *sc, DWORD a, DWORD slot, DWORD var)
{
	DWORD v[3] = { a, slot, var };
	return run_lifted(lift_45e600, (DWORD)sc, 3, v);
}
