/* notices.c: the scene's name table and its HUD notices: the requests the match code raises for the HUD (each
   with its own "shown" flag, all with the common "something changed" flag noticeChanged), and the event list
   reset. */
#include "../game.h"
#include <string.h>
#include <stdarg.h>


/* the player records (stride 0x47fd2 from 0x1755230) keep a name at +4 */
#define RECORD_NAME(scene, k) (((Scene *)RELOC(scene))->playerRecords[k].name)

/* 0x4616e0: the 16 players' names saved into the name table */
void THISCALL (scene_saveNames)(Scene *scene)
{
	for (int k = 0; k < 16; k++)
		strcpy(scene->playerNames[k], scene->players[k].name);
}

/* 0x461730: the names put back from the table, into the player records and the players */
void THISCALL (scene_restoreNames)(Scene *scene)
{
	for (int k = 0; k < 16; k++) {
		strcpy(RECORD_NAME(scene, k), scene->playerNames[k]);
		strcpy(scene->players[k].name, scene->playerNames[k]);
	}
}

/* 0x4629c0: the event list emptied, new lines stamped with time; the message box and "ready" faded out */
void THISCALL (events_clear)(Scene *scene, u32 time)
{
	scene->eventCount = 0;
	scene->eventFirst = 0;
	scene->eventTime = time;
	BITS(scene->msgFade) = 0;
	BITS(scene->readyTimer) = 0;
}

/* 0x463480: every notice cleared */
void THISCALL (notices_clearAll)(Scene *scene)
{
	memset(scene->sendFlags, 0, sizeof scene->sendFlags);
	scene->noticeChanged = 0;
	scene->connectPending = 0;
	scene->quitPending = 0;
	scene->chatPending = 0;
	scene->joinPending = 0;
	scene->changePending = 0;
	scene->endEvents[0] = scene->endEvents[1] = scene->endEvents[2] = 0;
	scene->cheatPending = 0;
}

/* 0x4634e0, 0x463530, 0x463550, 0x4635b0, 0x463610: one notice raised, with its values and text */
void THISCALL (notice_playerConnected)(Scene *scene, int a, const char *text)
{
	scene->connectPlayer = a;
	scene->connectPending = 1;
	strcpy(scene->connectName, text);
	scene->noticeChanged = 1;
}

void THISCALL (notice_playerQuit)(Scene *scene, int a)
{
	scene->quitPending = 1;
	scene->quitPlayer = a;
	scene->noticeChanged = 1;
}

void THISCALL (notice_chatLine)(Scene *scene, int a, const char *text, int b)
{
	scene->chatPlayer = a;
	scene->chatPending = 1;
	strcpy(scene->chatLine, text);
	scene->chatTeam = b;
	scene->noticeChanged = 1;
}

void THISCALL (notice_joinedTeam)(Scene *scene, int a, int b, const char *text)
{
	scene->joinPlayer = a;
	scene->joinTeam = b;
	scene->joinPending = 1;
	strcpy(scene->joinName, text);
	scene->noticeChanged = 1;
}

void THISCALL (notice_changedTeam)(Scene *scene, int a, int b, const char *text)
{
	scene->changePlayer = a;
	scene->changeTeam = b;
	scene->changePending = 1;
	strcpy(scene->changeName, text);
	scene->noticeChanged = 1;
}

/* 0x463450: the centre-screen notice printed (shown for 2 seconds); vsprintf's count */
int (notice_printCentre)(Scene *scene, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(scene->readyText, format, args);
	va_end(args);
	scene->readyTimer = 2.0f;
	return n;
}

/* 0x473450: printed into the stage's text buffer (+0x20fcd4c) */
int (stage_printText)(u8 *obj, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(((Stage *)obj)->printText, format, args);
	va_end(args);
	return n;
}

/* 0x462ac0: the event lines shown age by dt; the oldest is dropped once its time has run out (<= 0 or NaN) */
void THISCALL (events_age)(Scene *scene, float dt)
{
	for (u32 u = scene->eventFirst; u < scene->eventCount; u++) {
		float *t = (float *)&scene->events[u % 5].time;
		*t = (float)((long double)*t - dt);
	}
	u32 first = scene->eventFirst;
	if (first < scene->eventCount && !(GAME_VAR(float, &scene->events[first % 5].time) > 0.0f))
		scene->eventFirst = first + 1;
}
