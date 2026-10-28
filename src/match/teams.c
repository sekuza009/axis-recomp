/* teams.c: the match's teams: up to five team ids, each in a slot of Scene.teamIds (a free slot is negative); a
   team's slot picks its name, colour and score. */
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
