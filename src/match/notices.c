/* notices.c: the scene's name table and its HUD notices: the requests the match code raises for the HUD (each
   with its own "shown" flag, all with the common "something changed" flag noticeChanged), and the event list
   reset. */
#include "../game.h"
#include <string.h>
#include <stdarg.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* the player records (stride 0x47fd2 from 0x1755230) keep a name at +4 */
#define RECORD_NAME(scene, k) ((char *)(scene) + 0x1755234 + (k) * 0x47fd2)

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
	static const int flags[] = { 0x2343106, 0x234314e, 0x2343156, 0x234319b, 0x23431e7, 0x2343233, 0x2343237,
	                             0x234323b, 0x234323f, 0x234324f };
	memset((u8 *)scene + 0x2343006, 0, 0x100);
	for (int k = 0; k < 10; k++)
		FIELD(int, scene, flags[k]) = 0;
}

/* 0x4634e0, 0x463530, 0x463550, 0x4635b0, 0x463610: one notice raised, with its values and text */
void THISCALL (match_4634e0)(Scene *scene, int a, const char *text)
{
	FIELD(int, scene, 0x234310a) = a;
	FIELD(int, scene, 0x234314e) = 1;
	strcpy((char *)scene + 0x234310e, text);
	scene->noticeChanged = 1;
}

void THISCALL (match_463530)(Scene *scene, int a)
{
	FIELD(int, scene, 0x2343156) = 1;
	FIELD(int, scene, 0x2343152) = a;
	scene->noticeChanged = 1;
}

void THISCALL (match_463550)(Scene *scene, int a, const char *text, int b)
{
	FIELD(int, scene, 0x234315a) = a;
	FIELD(int, scene, 0x234319b) = 1;
	strcpy((char *)scene + 0x234315e, text);
	FIELD(int, scene, 0x2343197) = b;
	scene->noticeChanged = 1;
}

void THISCALL (match_4635b0)(Scene *scene, int a, int b, const char *text)
{
	FIELD(int, scene, 0x234319f) = a;
	FIELD(int, scene, 0x23431a3) = b;
	FIELD(int, scene, 0x23431e7) = 1;
	strcpy((char *)scene + 0x23431a7, text);
	scene->noticeChanged = 1;
}

void THISCALL (match_463610)(Scene *scene, int a, int b, const char *text)
{
	FIELD(int, scene, 0x23431eb) = a;
	FIELD(int, scene, 0x23431ef) = b;
	FIELD(int, scene, 0x2343233) = 1;
	strcpy((char *)scene + 0x23431f3, text);
	scene->noticeChanged = 1;
}

/* 0x463450: the centre-screen notice printed (shown for 2 seconds); vsprintf's count */
int (vsprintf_wrap_463450)(Scene *scene, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(scene->readyText, format, args);
	va_end(args);
	BITS(scene->readyTimer) = 0x40000000;   /* 2.0 */
	return n;
}

/* 0x473450: printed into the stage's text buffer (+0x20fcd4c) */
int (vsprintf_wrap_473450)(u8 *obj, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf((char *)obj + 0x20fcd4c, format, args);
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
