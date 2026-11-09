/* teams.c: the match's teams (team slots in Scene.teamIds: a slot picks its name, colour and score; the top player);
   also the stage's dynamic lights refilled (stage_refillLights). */
#include "../game.h"


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
int THISCALL (scene_claimTeamSlot)(Scene *scene, int id)
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
	if (scene->sessionMode == 0 && scene->teamGame == 1)
		for (int k = 0; k < 5; k++)
			scene->teamIds[k] = -1;
	else
		for (int k = 0; k < 5; k++)
			scene->teamIds[k] = k;
}

/* 0x4625a0: the match's top player: in a team match (teamGame) the best-ranked player of the leading team (team 1
   when its frags, teamScores[1], are higher, else team 0; none ranked there: the local player), otherwise the first
   in the ranking. hud_drawMatchResult prints it as "Top Player", and the end-of-match camera follows it while alive */
void *THISCALL (scene_topPlayer)(Scene *scene)
{
	int i;
	if (scene->teamGame == 1) {
		int leading = scene->teamScores[0] < scene->teamScores[1];
		for (int k = 0; k < scene->rankCount; k++) {
			int a = scene->ranking[k];
			if (scene->players[a].team == leading)
				return (u8 *)&scene->players[a];
		}
		i = scene->localPlayer;
	} else
		i = scene->ranking[0];
	return (u8 *)&scene->players[i];
}

/* 0x472310: the dynamic lights refilled: flagged (dynamicLightsSet), emptied (Light_clearCounts), then a white light for
   each active actor, of (its glow + 1) * 2500 at its position, and for each active particle whose light radius
   (lightRadius) is above 0, of that radius at its position */
void THISCALL (stage_refillLights)(Stage *stage)
{
	u8 *pool = (u8 *)&stage->dynamicLights;
	stage->dynamicLightsSet = 1;
	Light_clearCounts(pool);
	for (int i = 0; i < stage->actorCount; i++) {
		Actor *a = (Actor *)((u8 *)&stage->actors[i]);
		if (stage->actors[i].active == 1) {
			float radius = f32(fmul_m(fadd_m(fld_m(&a->glow), AP(const float, ADDR(k_1f))), k_2500f));
			factors_addPointLight(pool, OBJ(g_packedWhite), radius, a->pos);   /* factors_addPointLight */
		}
	}
	for (int i = 0; i < stage->particleCount; i++) {
		Particle *p = &stage->particles[i];
		if (p->active == 1 && p->lightRadius > k_0f)
			factors_addPointLight_bits(pool, OBJ(g_packedWhite), BITS(p->lightRadius), p->pos);
	}
}
