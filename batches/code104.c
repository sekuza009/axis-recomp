/* batch 103 (lifted/grp49.c) */
#include "lifted/grp49.c"
/* 0x457330 (thiscall on the scene) actor_setupFromParts(actor, a, b, &player): build actor's mech from its player's
   (*player) parts: stat defaults, item bonuses for the special items (0x1b..: armour, energy ...) of item
   records with a negative kind (+0x2dc0), the stats summed / scaled from the head, chest, arm, leg and booster
   records, the part object lists loaded (FUN_0045e1f0 .. FUN_0045e530, actor_updatePart), the player's starting
   values (actor_45ebc0) and the weapon slot (FUN_0045e810) */
static THISCALL DWORD actor_setupFromParts(char *sc, DWORD a, DWORD x, DWORD y, DWORD pp)
{
	DWORD v[4] = { a, x, y, pp };
	return run_lifted(lift_457330, (DWORD)sc, 4, v);
}
