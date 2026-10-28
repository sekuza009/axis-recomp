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

/* 0x45e880: actor i starts switching to weapon slot (2 seconds) unless it is the slot in use, when its player record
   holds a weapon there of a known type */
void THISCALL (actor_selectWeapon)(Stage *stage, int i, int slot)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	if (FIELD(int, actor, 0x140) == slot)
		return;
	int weapon = FIELD(int, stage, 0x1561b68 + FIELD(int, actor, 0x10c) * 0x47fd2 + 0x320 + slot * 4);
	if (weapon > -1 && FIELD(int, stage, 0x14d4874 + weapon * 0x2e18) > -1) {
		FIELD(int, actor, 0x48c) = 1;
		FIELD(int, actor, 0x498) = slot;
		FIELD(u32, actor, 0x494) = 0x40000000;   /* 2.0 */
	}
}

/* 0x45edb0: actor i (when +0x14c is 1) picks slot 0 four times in five, else slot 4, from the game's random table
   (0xa106f8, 4096 values, position 0xa1efb8), and its aim is set back to its own point */
void THISCALL (actor_45edb0)(Stage *stage, int i)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	if (FIELD(int, actor, 0x14c) != 1)
		return;
	u32 r = GAME_VAR(u32, 0xa1efb8);
	u32 v = GAME_VAR(u32, 0xa106f8 + (r & 0xfff) * 4);
	GAME_VAR(u32, 0xa1efb8) = r + 1;
	actor_selectWeapon(stage, i, v % 100 < 80 ? 0 : 4);
	FIELD(int, actor, 0x8830) = 0;
	FIELD(int, actor, 0x8834) = 0;
	FIELD(int, actor, 0x8828) = FIELD(int, actor, 0x90);
	FIELD(int, actor, 0x882c) = FIELD(int, actor, 0x94);
}
