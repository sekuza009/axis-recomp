/* msg_players.c: messages about players, in the game's language (1 Korean, 2 English; none otherwise). The texts are
   the game's own strings; the English ones are quoted. */
#include "../game.h"

#define KOREAN 1
#define ENGLISH 2

/* 0x462bc0: "%s has left the game." (colour 0) */
void THISCALL (msg_playerLeft)(Scene *scene, int actor)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 0, (const char *)0x4c468c, name);
	else if (g_language == ENGLISH)
		msg_print(scene, 0, (const char *)0x4c46a8, name);
}

/* 0x463030: "%s has used cheat code(%s)." (colour 4); the cheat's name from the language's table of 256-byte names */
void THISCALL (msg_cheatUsed)(Scene *scene, int actor, int cheat)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)0x4c4894, name, (const char *)(0x4a9838 + cheat * 256));
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)0x4c48b8, name, (const char *)(0x4a9d38 + cheat * 256));
}

/* 0x462b50: "%s has been connected." (colour 0), with sound 10 */
void THISCALL (msg_playerConnected)(Scene *scene, int actor)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 0, (const char *)0x4c465c, name);
	else if (g_language == ENGLISH)
		msg_print(scene, 0, (const char *)0x4c4674, name);
	sound_playVolume(10, 100);
}

/* 0x4630c0: a kill: "%s killed himself." when victim == killer, else "%s has crushed %s(%s)." (the killer, the victim,
   the victim's mech); colour 4 when the local player is one of them, else 0. Nothing for a negative index */
void THISCALL (msg_kill)(Scene *scene, int victim, int killer)
{
	if (victim < 0 || killer < 0)
		return;
	if (g_language != KOREAN && g_language != ENGLISH)
		return;
	int english = g_language == ENGLISH;
	Player *v = &scene->players[victim];
	if (victim == killer) {
		int colour = victim == scene->localPlayer ? 4 : 0;
		msg_print(scene, colour, (const char *)(english ? 0x4c4924 : 0x4c48f4), v->name);
	} else {
		int colour = victim == scene->localPlayer || killer == scene->localPlayer ? 4 : 0;
		const char *mech = scene->actorInfo[v->mechType].name + 5;
		msg_print(scene, colour, (const char *)(english ? 0x4c490c : 0x4c48d4), scene->players[killer].name, v->name, mech);
	}
}
