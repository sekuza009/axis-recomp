/* batch 90 (lifted/grp36.c) */
#include "lifted/grp36.c"
/* (thiscall on the scene) actor_setActorType{Head,Chest,Arm,Leg,Booster}InfoBy(player, type): a negative type
   gives 0; the player count (+0x19e1888) grows to cover the player; the same type as now gives 1; a type past the
   table's count (the dword before each table) is fatal. Otherwise the player's own shape and skeleton caches are
   released, the type's name copied to the player (+0x4c), the type stored (+0x30c..+0x31c), and every actor of the
   player (count +0x202e8c8) reloads that part (FUN_0045e1f0 / actor_updateBody / FUN_0045e390 / FUN_0045e460 /
   FUN_0045e530); 1 */
#define SET_TYPE(name, addr) static THISCALL DWORD name(char *sc, DWORD p, DWORD t) { DWORD v[2] = { p, t }; return run_lifted(lift_##addr, (DWORD)sc, 2, v); }
SET_TYPE(actor_setActorTypeHeadInfoBy, 473b10)
SET_TYPE(actor_setActorTypeChestInfoBy, 473c20)
SET_TYPE(actor_setActorTypeArmInfoBy, 473d30)
SET_TYPE(actor_setActorTypeLegInfoBy, 473e40)
SET_TYPE(actor_setActorTypeBoosterInfoBy, 473f50)
/* 0x474060 (thiscall) actor_setActorTypeItemInfoBy(player, slot, item): the item for a player's slot; the game mode
   (+0x20f3ab8) 2..11 fixes slot 0's item (3, 5, 0x24, 0x19, 0x16; mode 10/11 also slot 1: 0x17) and empties the
   other slots; otherwise a negative item empties the slot. The item's name goes to the player (+0x18c + slot * 0x40,
   empty for none), an item past the count (+0x1561b64) is fatal, the index is stored (+0x320 + slot * 4) and every
   actor of the player reloads that slot (actor_updatePart with its variant +0x49c) */
static THISCALL DWORD actor_setActorTypeItemInfoBy(char *sc, DWORD p, DWORD slot, DWORD item)
{
	DWORD v[3] = { p, slot, item };
	return run_lifted(lift_474060, (DWORD)sc, 3, v);
}
