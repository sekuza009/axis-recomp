/* armc_mech.c: the ARM CENTER's mech being edited: its name, team, five parts and six items, kept in the scene
   and handed on to the local player's record on the stage (when there is a local player). Part indices wrap
   around the number of parts of that kind. */
#include "../game.h"

/* 0x461320: the name (copied with its terminator) */
void THISCALL (mech_setName)(Scene *scene, const char *name)
{
	int i = 0;
	do
		scene->mechName[i] = name[i];
	while (name[i++] != '\0');
	if (scene->localPlayer >= 0)
		player_setName(STAGE(scene), scene->localPlayer, scene->mechName);
}

/* 0x461370: the local pilot's character set: the scene's and, with a local player, its record's and actors' */
void THISCALL (mech_setCharacter)(Scene *scene, int character)
{
	scene->character = character;
	if (scene->localPlayer >= 0)
		player_setCharacter(STAGE(scene), scene->localPlayer, character);
}

/* 0x4613a0: the team */
void THISCALL (scene_setLocalTeam)(Scene *scene, int team)
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
void THISCALL (mech_setItem)(Scene *scene, int slot, int item)
{
	scene->mechItems[slot] = item;
	if (scene->localPlayer >= 0)
		actor_setActorTypeItemInfoBy(STAGE(scene), scene->localPlayer, slot, item);
}

/* 0x461250: the whole mech at once; the player's record then marked used */
void THISCALL (mech_setAll)(Scene *scene, const char *name, int character, int team, int head, int chest, int arm, int leg,
                            int booster, int item0, int item1, int item2, int item3, int item4, int item5)
{
	mech_setName(scene, name);
	mech_setCharacter(scene, character);
	scene_setLocalTeam(scene, team);
	armc_setHeadIndex(scene, head);
	armc_setChestIndex(scene, chest);
	armc_setArmIndex(scene, arm);
	armc_setLegIndex(scene, leg);
	armc_setBoosterIndex(scene, booster);
	mech_setItem(scene, 0, item0);
	mech_setItem(scene, 1, item1);
	mech_setItem(scene, 2, item2);
	mech_setItem(scene, 3, item3);
	mech_setItem(scene, 4, item4);
	mech_setItem(scene, 5, item5);
	if (scene->localPlayer >= 0)
		player_markUsed(STAGE(scene), scene->localPlayer);
}

/* 0x461540 (thiscall on the game): the shown actor (localPlayer; none when negative) given a weapon slot (none given,
   negative: its current one, players[].slot) through the stage's refresh (stage_remakePlayerActor), its position and two angles kept
   across that; its players[].variantLoaded set unless it is the stage's own (selectedActor). A slot over 3 first selects and updates
   its players[].lastWeaponSlot one. Its callers ignore the eax it leaves */
void THISCALL (armc_giveShownActorWeapon)(u8 *game, int slot)
{
	Scene *sc = (Scene *)game;
#define I (sc->localPlayer)
#define ACTOR (sc->players[I])   /* the shown actor */
	if (I < 0)
		return;
	u32 at[3] = { BITS(ACTOR.nextPos[0]), BITS(ACTOR.nextPos[1]), BITS(ACTOR.nextPos[2]) };
	u32 angle0 = BITS(ACTOR.nextPitch), angle1 = BITS(ACTOR.nextYaw);   /* (copied as dwords, put back through the FPU) */
	int other = ACTOR.lastWeaponSlot;
	int chosen = slot >= 0 ? slot : ACTOR.slot;
	ACTOR.variantLoaded = I != sc->selectedActor;
	Stage *stage = SCENE_STAGE(game);
	stage_remakePlayerActor(stage);
	for (int k = 0; k < 3; k++)
		BITS(ACTOR.nextPos[k]) = at[k];
	ACTOR.nextPitch = f32(fld_m((const float *)&angle0));
	ACTOR.nextYaw = f32(fld_m((const float *)&angle1));
	if (slot > 3) {
		actor_setWeaponSlot(stage, I, other);
		actor_loadWeapon(stage, I, other, ACTOR.variantLoaded);
	}
	actor_setWeaponSlot(stage, I, chosen);
	actor_loadWeapon(stage, I, chosen, ACTOR.variantLoaded);
#undef I
#undef ACTOR
}
