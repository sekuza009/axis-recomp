/* teams.c: the match's teams: up to five team ids, each in a slot of Scene.teamIds (a free slot is negative); a
   team's slot picks its name, colour and score. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

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
void THISCALL (match_4636d0)(Scene *scene)
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
void *THISCALL (FUN_004625a0)(Scene *scene)
{
	u8 *s = (u8 *)scene;
	int i;
	if (FIELD(int, s, 0x22e7184) == 1) {
		int behind = FIELD(int, s, 0x2221fb8) < FIELD(int, s, 0x2221fbc);
		for (int k = 0; k < FIELD(int, s, 0x2342976); k++) {
			int a = FIELD(int, s, 0x23428f6 + k * 4);
			if (FIELD(int, s, 0x1eccb88 + a * 0x8888) == behind)
				return s + 0x1ecca70 + a * 0x8888;
		}
		i = FIELD(int, s, 0x234240d);
	} else
		i = FIELD(int, s, 0x23428f6);
	return s + 0x1ecca70 + i * 0x8888;
}
