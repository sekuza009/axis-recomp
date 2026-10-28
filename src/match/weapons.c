/* weapons.c: switching an actor's weapon. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* the next usable weapon slot of actor i, going step slots round the six (1 forward, 5 = one back): a slot is
   usable when its player record holds a weapon there, of a known type, and the actor has at least that weapon's
   ammunition cost left */
static void weapon_cycle(Stage *stage, int i, int step)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	u8 *player = (u8 *)stage + 0x1561b68 + FIELD(int, actor, 0x10c) * 0x47fd2;
	int slot = (FIELD(int, actor, 0x140) + step) % 6;
	for (int k = 0; k < 6; k++, slot = (slot + step) % 6) {
		int weapon = FIELD(int, player, 0x320 + slot * 4);
		if (weapon < 0)
			continue;
		int type = FIELD(int, stage, 0x14d4874 + weapon * 0x2e18);
		if (FIELD(int, actor, 0x130 + type * 4) < FIELD(int, stage, 0x14d4878 + weapon * 0x2e18) || type < 0)
			continue;
		actor_selectWeapon(stage, i, slot);
		return;
	}
}

/* 0x45e9e0, 0x45e910: actor i's next and previous weapon */
void THISCALL (actor_45e9e0)(Stage *stage, int i) { weapon_cycle(stage, i, 1); }
void THISCALL (actor_45e910)(Stage *stage, int i) { weapon_cycle(stage, i, 5); }

/* 0x45e810: actor i's weapon slot changed to slot (slots 0 .. 3 also remembered as the last ordinary one), with the
   weapon its player record holds there */
void THISCALL (FUN_0045e810)(Stage *stage, int i, int slot)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	int player = FIELD(int, actor, 0x10c);
	if (FIELD(int, actor, 0x140) != slot) {
		FIELD(int, actor, 0x140) = slot;
		if (slot < 4)
			FIELD(int, actor, 0x144) = slot;
		FIELD(int, actor, 0x148) = FIELD(int, stage, 0x1561b68 + player * 0x47fd2 + 0x320 + slot * 4);
	}
}
