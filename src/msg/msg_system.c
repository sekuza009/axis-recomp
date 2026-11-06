/* msg_system.c: the match's system messages: a line in the message box (colour 4) in the game's language (1 Korean,
   2 English; none otherwise), with a sound. The texts are the game's own strings; the English ones are quoted. */
#include "../game.h"

#define KOREAN 1
#define ENGLISH 2

static void say(Scene *scene, u32 korean, u32 english, int sound)
{
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)RELOC(korean));
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)RELOC(english));
	sound_playVolume(sound, 100);
}

/* the same with one number in the text */
static void say_number(Scene *scene, u32 korean, u32 english, int n, int sound)
{
	if (g_language == KOREAN)
		msg_print(scene, 4, (const char *)RELOC(korean), n);
	else if (g_language == ENGLISH)
		msg_print(scene, 4, (const char *)RELOC(english), n);
	sound_playVolume(sound, 100);
}

/* 0x462f30: "The server ends the game." */
void THISCALL (msg_serverEndsGame)(Scene *scene) { say(scene, STR(0x4c47ac, "\274\255\271\366\260\241 \260\324\300\323\300\273 \301\276\267\341\307\325\264\317\264\331."), STR(0x4c47c8, "The server ends the game."), 0x16); }
/* 0x462f60: "The user ends the game." */
void THISCALL (msg_userEndsGame)(Scene *scene) { say(scene, STR(0x4c47e4, "\273\347\277\353\300\332\260\241 \260\324\300\323\300\273 \301\276\267\341\307\325\264\317\264\331."), STR(0x4c4800, "The user ends the game."), 0x16); }
/* 0x463390: "The network connection lost. The game ends." */
void THISCALL (msg_connectionLost)(Scene *scene) { say(scene, STR(0x4c4938, "\263\327\306\256\277\366\305\251\301\242\274\323\300\314 \262\367\276\356\301\256\274\255 \260\324\300\323\300\273 \301\276\267\341\307\325..."), STR(0x4c4964, "The network connection lost. The game..."), 0x15); }
/* 0x4633c0: "The network state is not stable. The game ends." */
void THISCALL (msg_networkUnstable)(Scene *scene) { say(scene, STR(0x4c4990, "\263\327\306\256\277\366\305\251\273\363\305\302\260\241 \301\301\301\366 \276\312\276\306\274\255 \260\324\300\323\300\273 \301\276\267..."), STR(0x4c49c0, "The network state is not stable. The ..."), 0x15); }
/* 0x462f90: "Frag limit(%d) reached." */
void THISCALL (msg_fragLimitReached)(Scene *scene) { say_number(scene, STR(0x4c4818, "\270\361\307\245\306\304\261\253\274\366 %d\277\241 \264\331\264\336\276\322\275\300\264\317\264\331."), STR(0x4c4838, "Frag limit(%d) reached."), scene->fragLimit, 0x15); }
/* 0x462fd0: "Time limit(%d minutes) reached." */
void THISCALL (msg_timeLimitReached)(Scene *scene) { say_number(scene, STR(0x4c4850, "\270\361\307\245\260\324\300\323\275\303\260\243 %d\272\320\277\241 \264\331\264\336\276\322\275\300\264\317\264\331."), STR(0x4c4874, "Time limit(%d minutes) reached."), scene->timeLimit, 0x15); }
/* 0x4633f0: "Game end caused by data loss(code %d)." */
void THISCALL (msg_dataLoss)(Scene *scene) { say_number(scene, STR(0x4c49f0, "\265\245\300\314\305\270\274\325\275\307\267\316 \260\324\300\323\300\273 \301\276\267\341\307\325\264\317\264\331(\273\363\310\262%d)."), STR(0x4c4a18, "Game end caused by data loss(code %d)."), scene->dataLossCode, 0x15); }
