/* teams.c: the match's teams: up to five team ids, each in a slot of Scene.teamIds (a free slot is negative); a
   team's slot picks its name, colour and score. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* 0x463710: the slot holding team id, or -1 (also for a negative id) */
int THISCALL (scene_findTeam)(Scene *scene, int id)
{
	if (id < 0)
		return -1;
	for (int i = 0; i < 5; i++)
		if (scene->teamIds[i] == id)
			return i;
	return -1;
}

/* 0x463740: the slot of team id, given the first free slot if it has none yet; -1 when there is no room (or for a
   negative id) */
int THISCALL (scene_teamSide)(Scene *scene, int id)
{
	if (id < 0)
		return -1;
	int slot = scene_findTeam(scene, id);
	if (slot >= 0)
		return slot;
	for (int i = 0; i < 5; i++)
		if (scene->teamIds[i] < 0) {
			scene->teamIds[i] = id;
			return i;
		}
	return -1;
}

/* 0x4636d0: the team slots at the start of a match: all free in a local team game, else teams 0 .. 4 */
void THISCALL (teams_setup)(Scene *scene)
{
	if (scene->network == 0 && scene->teamGame == 1)
		for (int k = 0; k < 5; k++)
			scene->teamIds[k] = -1;
	else
		for (int k = 0; k < 5; k++)
			scene->teamIds[k] = k;
}

/* 0x4625a0: the actor the camera follows: in a team match (+0x22e7184) the first listed actor of the team that is
   behind (else the local player's), otherwise the first listed one */
void *THISCALL (scene_followedActor)(Scene *scene)
{
	int i;
	if (scene->teamGame == 1) {
		int behind = scene->teamScores[0] < scene->teamScores[1];
		for (int k = 0; k < scene->rankCount; k++) {
			int a = scene->ranking[k];
			if (scene->players[a].team == behind)
				return (u8 *)&scene->players[a];
		}
		i = scene->localPlayer;
	} else
		i = scene->ranking[0];
	return (u8 *)&scene->players[i];
}

/* 0x472310: the factor pool (+0x9d8010) refilled: flagged (+0x9d800c), emptied (0x483d60), then a factor (kind
   0xa1f23c) for each active actor, of (its +0x4ec + 0x4a9424) * 0x4aa410 at its +0x154, and for each active
   projectile whose +0x7c is above 0x4a93e8, of that at its +0x10 */
void THISCALL (stage_refillFactors)(Stage *stage)
{
	u8 *pool = (u8 *)&((Stage *)stage)->dynamicLights;
	GAME_VAR(int, (u8 *)stage + 0x9d800c) = 1;
	Light_clearCounts(pool);
	for (int i = 0; i < stage->actorCount; i++) {
		u8 *a = (u8 *)&stage->actors[i];
		if (stage->actors[i].active == 1) {
			float value = f32(fmul_m(fadd_m(fld_m((const float *)(RELOC(a) + 0x4ec)), (const float *)ADDR(k_1f)), k_2500f));
			GAME_THISFN(factors_addDirected, 0x483f00, int, void *, u32, float, void *)(pool, OBJ(g_packedWhite), value, a + 0x154);   /* factors_addDirected */
		}
	}
	for (int i = 0; i < stage->projectileCount; i++) {
		u8 *p = (u8 *)&stage->projectiles[i];
		if (stage->projectiles[i].active == 1 && *(const float *)(p + 0x7c) > k_0f)
			GAME_THISFN(factors_addDirected, 0x483f00, int, void *, u32, u32, void *)(pool, OBJ(g_packedWhite), GAME_VAR(u32, p + 0x7c), p + 0x10);
	}
}
