/* msg_players.c: messages about players, in the game's language (1 Korean, 2 English; none otherwise). The texts are
   the game's own strings; the English ones are quoted. */
#include "../game.h"
#include <string.h>

#define KOREAN 1
#define ENGLISH 2

/* 0x462bc0: "%s has left the game." (colour 0) */
void THISCALL (msg_playerLeft)(Scene *scene, int actor)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 0, (const char *)STR(0x4c468c, "%s\264\324\300\314 \260\324\300\323\300\273 \301\276\267\341\307\337\275\300\264\317\264\331."), name);
	else if (g_language == ENGLISH)
		msg_print(scene, 0, (const char *)STR(0x4c46a8, "%s has left the game."), name);
}

/* 0x463030: "%s has used cheat code(%s)." (colour 4); the cheat's name from the language's table of 256-byte names */
void THISCALL (msg_cheatUsed)(Scene *scene, int actor, int cheat)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)STR(0x4c4894, "%s\264\324\300\314 \304\241\306\256\304\332\265\345(%s)\270\246 \273\347\277\353\307\337\275\300\264\317\264\331."), name, (const char *)(STR(0x4a9838, "fancer") + cheat * 256));
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)STR(0x4c48b8, "%s has used cheat code(%s)."), name, (const char *)(STR(0x4a9d38, "fancer") + cheat * 256));
}

/* 0x462b50: "%s has been connected." (colour 0), with sound 10 */
void THISCALL (msg_playerConnected)(Scene *scene, int actor)
{
	const char *name = scene->players[actor].name;
	if (g_language == KOREAN)
		msg_print(scene, 0, (const char *)STR(0x4c465c, "%s\264\324\300\314 \301\242\274\323\307\337\275\300\264\317\264\331."), name);
	else if (g_language == ENGLISH)
		msg_print(scene, 0, (const char *)STR(0x4c4674, "%s has been connected."), name);
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
		msg_print(scene, colour, (const char *)(RELOC(english) ? STR(0x4c4924, "%s killed himself.") : STR(0x4c48f4, "%s\264\324\300\314 \300\332\306\370\307\337\275\300\264\317\264\331.")), v->name);
	} else {
		int colour = victim == scene->localPlayer || killer == scene->localPlayer ? 4 : 0;
		const char *mech = scene->actorInfo[v->lastHitWeapon].name + 5;
		msg_print(scene, colour, (const char *)(RELOC(english) ? STR(0x4c490c, "%s has crushed %s(%s).") : STR(0x4c48d4, "%s\264\324\300\314 %s\264\324\300\273 \306\304\261\253\307\337\275\300\264\317\264\331(%s).")), scene->players[killer].name, v->name, mech);
	}
}

/* the players' records (stride 0x47fd2 from Scene + 0x1755230; scene.fields does not hold them yet): the name at +4,
   empty when the player is not there */
#define PLAYER_NAME(scene, p) ((const char *)RELOC(scene) + 0x1755234 + (p) * 0x47fd2)

/* 0x462c30: a chat line "[%s]%s" (name, text) said to team: shown in colour 3 or 2 to the first two teams' own
   players, in colour 1 to everyone when said to all (a team without a slot); sound 9 */
void THISCALL (msg_chatLine)(Scene *scene, int actor, const char *text, int team)
{
	const char *name = scene->players[actor].name;
	switch (scene_findTeam(scene, team)) {
	case 0:
		if (scene->localTeam == team)
			msg_print(scene, 3, (const char *)STR(0x4c46c0, "[%s]%s"), name, text);
		break;
	case 1:
		if (scene->localTeam == team)
			msg_print(scene, 2, (const char *)STR(0x4c46c0, "[%s]%s"), name, text);
		break;
	default:
		msg_print(scene, 1, (const char *)STR(0x4c46c0, "[%s]%s"), name, text);
		break;
	}
	sound_playVolume(9, 100);
}

/* 0x462d30: "%s has joined %s team." in team games, else "%s has joined the battle." (colour 0; the team's name, 16
   bytes a slot, passed either way); nothing for a player whose record is empty */
void THISCALL (msg_playerJoinedTeam)(Scene *scene, int player, int team)
{
	const char *name = PLAYER_NAME(scene, player);
	if (name[0] == '\0')
		return;
	if (g_language == KOREAN) {
		const char *format = (const char *)(scene->teamGame == 1 ? STR(0x4c46e4, "%s\264\324\300\314 %s\306\300\277\241 \307\325\267\371\307\337\275\300\264\317\264\331.") : STR(0x4c46c8, "%s\264\324\300\314 \300\374\305\365\277\241 \302\374\277\251\307\337\275\300\264\317\264\331."));
		msg_print(scene, 0, format, name, (const char *)(OBJ(k_teamNamesKorean) + scene_teamSide(scene, team) * 16));
	} else if (g_language == ENGLISH) {
		const char *format = (const char *)(scene->teamGame == 1 ? STR(0x4c471c, "%s has joined %s team.") : STR(0x4c4700, "%s has joined the battle."));
		msg_print(scene, 0, format, name, (const char *)(STR(0x4a97ac, "red") + scene_teamSide(scene, team) * 16));
	}
}

/* 0x462650: is text one of the cheat codes (entries 2 .. 4 of the language's table of 256-byte codes; empty ones
   skipped)? The actor's cheat (+0x4d0) set to it and returned, else -1 */
int THISCALL (chat_matchCheatCode)(Scene *scene, int actor, const char *text)
{
	int language = g_language;
	for (int k = 0; k < 3; k++) {
		const char *code = language == 1 ? (const char *)(STR(0x4a9a38, "\270\323\270\256\305\253\276\306\300\314") + k * 0x100)
		                 : language == 2 ? (const char *)(STR(0x4a9f38, "give me a big head") + k * 0x100) : NULL;
		if (code && code[0] && !strcmp(code, text)) {
			GAME_VAR(int, (u8 *)scene + 0x1eccf40 + actor * 0x8888) = k + 2;
			return k + 2;
		}
	}
	return -1;
}

/* 0x462e30: "%s has changed team to %s." with the team's name (16 bytes a slot, by scene_teamSide), or without a
   team (negative) "%s becomes a spectator" (colour 0), in the game's language. Its callers ignore the eax it leaves */
void THISCALL (msg_playerChangedTeam)(Scene *scene, int player, int team)
{
	const char *name = PLAYER_NAME(scene, player);
	if (g_language == KOREAN) {
		if (team >= 0)
			msg_print(scene, 0, (const char *)STR(0x4c4754, "%s\264\324\300\314 \306\300\300\273 %s\306\300\300\270\267\316 \271\331\262\345\275\300\264\317\264\331."), name, (const char *)(OBJ(k_teamNamesKorean) + scene_teamSide(scene, team) * 16));
		else
			msg_print(scene, 0, (const char *)STR(0x4c4734, "%s\264\324\300\314 \260\324\300\323\300\273 \261\270\260\346\270\270 \307\325\264\317\264\331."), name);
	} else if (g_language == ENGLISH) {
		if (team >= 0)
			msg_print(scene, 0, (const char *)STR(0x4c4790, "%s has changed team to %s."), name, (const char *)(STR(0x4a97ac, "red") + scene_teamSide(scene, team) * 16));
		else
			msg_print(scene, 0, (const char *)STR(0x4c4778, "%s becomes a spectator"), name);
	}
}
