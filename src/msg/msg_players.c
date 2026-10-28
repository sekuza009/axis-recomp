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
