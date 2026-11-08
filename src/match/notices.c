/* notices.c: the scene's name table, the announcements queued for the other players (each with its own pending
   flag, all with the common announcePending; net_sendMatchEvent sends them), the centred notice and the event
   list. */
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

/* 0x4629c0: the event list emptied, new lines to stay shown timeBits seconds (a float's bits, into eventTime; every caller passes 60.0); the
   message box (msgFade) and the centred notice (noticeTimer) faded out */
void THISCALL (events_clear)(Scene *scene, u32 timeBits)
{
	scene->eventCount = 0;
	scene->eventFirst = 0;
	BITS(scene->eventTime) = timeBits;   /* (a float, taken as its bits: the original only copies it) */
	BITS(scene->msgFade) = 0;
	BITS(scene->noticeTimer) = 0;
}

/* 0x463480: every queued send dropped: the per-player send flags (sendFlags[16][4]) and the announcements' pending
   flags (announcePending, connect, quit, chat, join, change, the three endEvents, cheatPending; restartPending is
   left, never set anyway) */
void THISCALL (net_clearAnnouncements)(Scene *scene)
{
	memset(scene->sendFlags, 0, sizeof scene->sendFlags);
	scene->announcePending = 0;
	scene->connectPending = 0;
	scene->quitPending = 0;
	scene->chatPending = 0;
	scene->joinPending = 0;
	scene->changePending = 0;
	scene->endEvents[0] = scene->endEvents[1] = scene->endEvents[2] = 0;
	scene->cheatPending = 0;
}

/* 0x4634e0, 0x463530, 0x463550, 0x4635b0, 0x463610: an announcement queued for the other players (net_sendMatchEvent
   sends it: packet kinds 8 connected, 9 quit, 7 a chat line, 10 joined a team, 11 changed team), with its values */
void THISCALL (net_announcePlayerConnected)(Scene *scene, int player, const char *text)
{
	scene->connectPlayer = player;
	scene->connectPending = 1;
	strcpy(scene->connectName, text);
	scene->announcePending = 1;
}

void THISCALL (net_announcePlayerQuit)(Scene *scene, int player)
{
	scene->quitPending = 1;
	scene->quitPlayer = player;
	scene->announcePending = 1;
}

void THISCALL (net_announceChatLine)(Scene *scene, int player, const char *text, int team)
{
	scene->chatPlayer = player;
	scene->chatPending = 1;
	strcpy(scene->chatLine, text);
	scene->chatTeam = team;
	scene->announcePending = 1;
}

void THISCALL (net_announceJoinedTeam)(Scene *scene, int player, int team, const char *text)
{
	scene->joinPlayer = player;
	scene->joinTeam = team;
	scene->joinPending = 1;
	strcpy(scene->joinName, text);
	scene->announcePending = 1;
}

void THISCALL (net_announceChangedTeam)(Scene *scene, int player, int team, const char *text)
{
	scene->changePlayer = player;
	scene->changeTeam = team;
	scene->changePending = 1;
	strcpy(scene->changeName, text);
	scene->announcePending = 1;
}

/* 0x463450: the centre-screen notice printed (shown for 2 seconds); vsprintf's count */
int (notice_printCentre)(Scene *scene, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(scene->noticeText, format, args);
	va_end(args);
	scene->noticeTimer = 2.0f;
	return n;
}

/* 0x473450: printed into the stage's text buffer (printText) */
int (stage_printText)(Stage *stage, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(stage->printText, format, args);
	va_end(args);
	return n;
}

/* 0x462ac0: the event lines shown age by dt; the oldest is dropped once its time has run out (<= 0 or NaN) */
void THISCALL (events_age)(Scene *scene, float dt)
{
	for (u32 u = scene->eventFirst; u < scene->eventCount; u++) {
		float *t = (float *)&scene->events[u % 5].timeLeft;
		*t = (float)((long double)*t - dt);
	}
	u32 first = scene->eventFirst;
	if (first < scene->eventCount && !(GAME_VAR(float, &scene->events[first % 5].timeLeft) > 0.0f))
		scene->eventFirst = first + 1;
}
