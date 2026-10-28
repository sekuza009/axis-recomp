/* msg_system.c: the match's system messages: a line in the message box (colour 4) in the game's language (1 Korean,
   2 English; none otherwise), with a sound. The texts are the game's own strings; the English ones are quoted. */
#include "../game.h"

#define KOREAN 1
#define ENGLISH 2

static void say(Scene *scene, u32 korean, u32 english, int sound)
{
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)korean);
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)english);
	sound_playVolume(sound, 100);
}

/* the same with one number in the text */
static void say_number(Scene *scene, u32 korean, u32 english, int n, int sound)
{
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)korean, n);
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)english, n);
	sound_playVolume(sound, 100);
}

/* 0x462f30: "The server ends the game." */
void THISCALL (msg_serverEndsGame)(Scene *scene) { say(scene, 0x4c47ac, 0x4c47c8, 0x16); }
/* 0x462f60: "The user ends the game." */
void THISCALL (msg_userEndsGame)(Scene *scene) { say(scene, 0x4c47e4, 0x4c4800, 0x16); }
/* 0x463390: "The network connection lost. The game ends." */
void THISCALL (msg_connectionLost)(Scene *scene) { say(scene, 0x4c4938, 0x4c4964, 0x15); }
/* 0x4633c0: "The network state is not stable. The game ends." */
void THISCALL (msg_networkUnstable)(Scene *scene) { say(scene, 0x4c4990, 0x4c49c0, 0x15); }
/* 0x462f90: "Frag limit(%d) reached." */
void THISCALL (msg_fragLimitReached)(Scene *scene) { say_number(scene, 0x4c4818, 0x4c4838, scene->scoreLimit, 0x15); }
/* 0x462fd0: "Time limit(%d minutes) reached." */
void THISCALL (msg_timeLimitReached)(Scene *scene) { say_number(scene, 0x4c4850, 0x4c4874, scene->timeLimit, 0x15); }
/* 0x4633f0: "Game end caused by data loss(code %d)." */
void THISCALL (msg_dataLoss)(Scene *scene) { say_number(scene, 0x4c49f0, 0x4c4a18, scene->dataLossCode, 0x15); }
