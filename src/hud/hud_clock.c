/* hud_clock.c: the HUD's match counters (points still needed, time left), the match result and the replay
   recording mark. */
#include "../game.h"
#include <string.h>

/* the counters' colour: white, or when nearly out red, blinking off in the second half of each second */
static void clock_setColour(int low, Scene *scene)
{
	if (!low)
		text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	else
		text_setColor(1.0f, 0.0f, 0.0f, scene->clockFraction > 0.5f ? 0.0f : 1.0f);
}

/* 0x496610: top centre: the points the leader still needs for the score limit (icon 1, right-aligned to 13 units
   per character), and the time left as mm:ss (icon 2); red when one point / ten seconds are left */
void THISCALL (hud_drawClock)(Scene *scene)
{
	char text[256];
	if (scene->scoreLimit > 0) {
		int best;
		if (scene->teamGame == 1)
			best = scene->teamScores[0] < scene->teamScores[1] ? scene->teamScores[1] : scene->teamScores[0];
		else if (scene->rankCount > 0)
			best = scene->players[scene->ranking[0]].kills;
		else
			best = 0;
		clock_setColour(scene->scoreLimit - best <= 1, scene);
		sprintf(text, "%d", scene->scoreLimit - best);
		text_drawSized((0x15 - (int)strlen(text)) * 13, 8, text, 16);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		hud_drawIcon(scene, 0xf9 - (int)strlen(text) * 13, 8, 1);
	}
	if (scene->timeLimit > 0) {
		int left = scene->timeLimit * 60;
		if (left > scene->elapsed)
			left -= scene->elapsed;
		clock_setColour(left <= 10, scene);
		sprintf(text, "%02d:%02d", left / 60, left % 60);
		text_drawSized(0x187, 8, text, 16);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		hud_drawIcon(scene, 0x16f, 8, 2);
	}
}

/* 0x496a30: the match's result: in team games a grey band and the winning side ("RED TEAM WIN!" in red, "BLUE TEAM
   WIN!" in blue, else "DRAW GAME!" in green); otherwise "Top Player: name" while the top player is in play */
void THISCALL (hud_drawMatchResult)(Scene *scene)
{
	char text[256];
	if (scene->teamGame == 1) {
		glColor4f(0.6f, 0.6f, 0.6f, 0.5f);
		hud_fillRect(0, 0x15e, 0x280, 0x192);
		switch (scene_teamSide(scene, scene->winnerTeam)) {
		case 0:
			sprintf(text, "RED TEAM WIN!");
			text_setColor(1.0f, 0.0f, 0.0f, 1.0f);
			break;
		case 1:
			sprintf(text, "BLUE TEAM WIN!");
			text_setColor(0.0f, 0.0f, 1.0f, 1.0f);
			break;
		default:
			sprintf(text, "DRAW GAME!");
			text_setColor(0.0f, 1.0f, 0.0f, 1.0f);
			break;
		}
		text_drawCentred(0, 0x168, 0x280, text, 32);
	} else if (scene_topPlayer(scene)->state == 1) {
		text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
		sprintf(text, "Top Player: %s", scene_topPlayer(scene)->name);
		text_drawCentred(0, 0x192, 0x280, text, 16);
	}
}

/* 0x496d10: while recording, in the first half of each second: the record icon, the time recorded (mm:ss) and the
   replay's file name */
void THISCALL (hud_drawRecordIndicator)(Scene *scene)
{
	char text[256];
	int whole = ftol(scene->recordTime);
	if (!((long double)scene->recordTime - whole >= 0.5f)) {        /* also taken for NaN, as the original */
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		hud_drawIcon(scene, 0x10a, 0x140, 4);
		text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
		int seconds = ftol(scene->recordTime);
		sprintf(text, "%02d:%02d", seconds / 60, seconds % 60);
		text_drawSized(0x122, 0x140, text, 16);
		text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
		sprintf(text, "\"AutoPlay\\%s\"", scene->recordName);
		text_drawCentred(0x140, 0x128, 0x140, text, 16);
	}
}
