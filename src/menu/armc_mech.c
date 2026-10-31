/* armc_mech.c: the ARM CENTER's mech being edited: its name, team, five parts and six items, kept in the scene
   and handed on to the local player's record on the stage (when there is a local player). Part indices wrap
   around the number of parts of that kind. */
#include "../game.h"

/* 0x461320: the name (copied with its terminator) */
void THISCALL (armc_461320)(Scene *scene, const char *name)
{
	int i = 0;
	do
		scene->mechName[i] = name[i];
	while (name[i++] != '\0');
	if (scene->localPlayer >= 0)
		player_setName(STAGE(scene), scene->localPlayer, scene->mechName);
}

/* 0x461370: (unclear) a value kept with the player (its record's +0x44 and its actors') */
void THISCALL (armc_461370)(Scene *scene, int v)
{
	scene->mechValue = v;
	if (scene->localPlayer >= 0)
		player_setValue(STAGE(scene), scene->localPlayer, v);
}

/* 0x4613a0: the team */
void THISCALL (match_4613a0)(Scene *scene, int team)
{
	scene->localTeam = team;
	if (scene->localPlayer >= 0)
		player_setTeam(STAGE(scene), scene->localPlayer, team);
}

/* index wrapped into 0 .. count - 1 (negative indices count from the end) */
static int wrap(int index, int count)
{
	return (index % count + count) % count;
}

/* 0x4613d0, 0x461410, 0x461450, 0x461490, 0x4614d0: a part by its index */
void THISCALL (armc_setHeadIndex)(Scene *scene, int index)
{
	scene->mechParts[0] = wrap(index, scene->headCount);
	if (scene->localPlayer >= 0)
		actor_setActorTypeHeadInfoBy(STAGE(scene), scene->localPlayer, scene->mechParts[0]);
}

void THISCALL (armc_setChestIndex)(Scene *scene, int index)
{
	scene->mechParts[1] = wrap(index, scene->chestCount);
	if (scene->localPlayer >= 0)
		actor_setActorTypeChestInfoBy(STAGE(scene), scene->localPlayer, scene->mechParts[1]);
}

void THISCALL (armc_setArmIndex)(Scene *scene, int index)
{
	scene->mechParts[2] = wrap(index, scene->armCount);
	if (scene->localPlayer >= 0)
		actor_setActorTypeArmInfoBy(STAGE(scene), scene->localPlayer, scene->mechParts[2]);
}

void THISCALL (armc_setLegIndex)(Scene *scene, int index)
{
	scene->mechParts[3] = wrap(index, scene->legCount);
	if (scene->localPlayer >= 0)
		actor_setActorTypeLegInfoBy(STAGE(scene), scene->localPlayer, scene->mechParts[3]);
}

void THISCALL (armc_setBoosterIndex)(Scene *scene, int index)
{
	scene->mechParts[4] = wrap(index, scene->boosterCount);
	if (scene->localPlayer >= 0)
		actor_setActorTypeBoosterInfoBy(STAGE(scene), scene->localPlayer, scene->mechParts[4]);
}

/* 0x461510: item slot slot (0 .. 5) */
void THISCALL (armc_461510)(Scene *scene, int slot, int item)
{
	scene->mechItems[slot] = item;
	if (scene->localPlayer >= 0)
		actor_setActorTypeItemInfoBy(STAGE(scene), scene->localPlayer, slot, item);
}

/* 0x461250: the whole mech at once; the player's record then marked used */
void THISCALL (armc_461250)(Scene *scene, const char *name, int v, int team, int head, int chest, int arm, int leg,
                            int booster, int item0, int item1, int item2, int item3, int item4, int item5)
{
	armc_461320(scene, name);
	armc_461370(scene, v);
	match_4613a0(scene, team);
	armc_setHeadIndex(scene, head);
	armc_setChestIndex(scene, chest);
	armc_setArmIndex(scene, arm);
	armc_setLegIndex(scene, leg);
	armc_setBoosterIndex(scene, booster);
	armc_461510(scene, 0, item0);
	armc_461510(scene, 1, item1);
	armc_461510(scene, 2, item2);
	armc_461510(scene, 3, item3);
	armc_461510(scene, 4, item4);
	armc_461510(scene, 5, item5);
	if (scene->localPlayer >= 0)
		player_markUsed(STAGE(scene), scene->localPlayer);
}

/* 0x461540 (thiscall on the game): the shown actor (+0x234240d; none when negative) given a weapon slot (none given,
   negative: its current one, +0x1eccbb0) through the stage's refresh (armc_45ddc0), its position and two angles kept
   across that; its +0x1eccf0c set unless it is the stage's own (+0x2221fa0). A slot over 3 first selects and updates
   its +0x1eccbb4 one. Its callers ignore the eax it leaves */
void THISCALL (armc_461540)(u8 *game, int slot)
{
#define I GAME_VAR(int, game + 0x234240d)
#define ACTOR(type, offset) GAME_VAR(type, game + I * 0x8888 + (offset))
	if (I < 0)
		return;
	u32 at[3] = { ACTOR(u32, 0x1eccbf0), ACTOR(u32, 0x1eccbf4), ACTOR(u32, 0x1eccbf8) };
	u32 angle0 = ACTOR(u32, 0x1eccbfc), angle1 = ACTOR(u32, 0x1eccc00);   /* (copied as dwords, put back through the FPU) */
	int other = ACTOR(int, 0x1eccbb4);
	int chosen = slot >= 0 ? slot : ACTOR(int, 0x1eccbb0);
	ACTOR(int, 0x1eccf0c) = I != GAME_VAR(int, game + 0x2221fa0);
	Stage *stage = (Stage *)(game + 0x1f36c8);
	armc_45ddc0(stage);
	for (int k = 0; k < 3; k++)
		ACTOR(u32, 0x1eccbf0 + k * 4) = at[k];
	ACTOR(float, 0x1eccbfc) = f32(fld_m((const float *)&angle0));
	ACTOR(float, 0x1eccc00) = f32(fld_m((const float *)&angle1));
	if (slot > 3) {
		actor_setWeaponSlot(stage, I, other);
		actor_updatePart(stage, I, other, ACTOR(u32, 0x1eccf0c));
	}
	actor_setWeaponSlot(stage, I, chosen);
	actor_updatePart(stage, I, chosen, ACTOR(u32, 0x1eccf0c));
#undef I
#undef ACTOR
}
