/* hud_overlay.c: small overlays of the in-match HUD, and the HUD's unit conversion (hud.h). */
#include "../game.h"
#include "hud.h"

int hud_scaleX(float units)
{
	return ftol(units / ((long double)640.0f / gfx_getWidth()));
}
int hud_scaleY(float units)
{
	return ftol(units / ((long double)480.0f / gfx_getHeight()));
}

/* 0x4950a0 (hud_fillRect): a filled rectangle given in HUD units, in the current colour. The corners are converted
   bottom right first, as the original does (each conversion asks for the screen size again). */
void (hud_fillRect)(int x0, int y0, int x1, int y1)
{
	int sy1 = hud_toScreenY(y1);
	int sx1 = hud_toScreenX(x1);
	int sy0 = hud_toScreenY(y0);
	int sx0 = hud_toScreenX(x0);
	gfx_fillRect(sx0, sy0, sx1, sy1);
}

/* 0x495510: the frames-per-second counter, top right: its icon and the rate with one decimal */
void THISCALL (hud_drawFps)(Scene *scene)
{
	char text[256];
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	replay_drawIcon(scene, 0x1d9, 8, 3);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%4.1f", (double)scene->timer.fps);
	text_drawSized(0x1f1, 8, text, 16);
}

/* 0x4953d0 (hud_drawChatInput): the chat line while typing: a half-transparent box and the line, with a "_" cursor
   during the first half of each blink */
void THISCALL (hud_drawChatInput)(Scene *scene)
{
	char text[256];
	if (scene->chatMode != 1 && scene->chatMode != 2)
		return;
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	hud_fillRect(0x50, 0x158, 0x230, 0x188);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (scene->secondFraction >= 0.5f) {
		sprintf(text, "%s_", g_chatLine);
		text_drawSized(0x60, 0x168, text, 8);
	} else {
		text_drawSized(0x60, 0x168, g_chatLine, 8);
	}
}

/* 0x496240 (hud_drawTeamScores): the team score box at the top: two boxes of 48 x 20 units side by side (red for the team
   in slot 0, blue for slot 1) with their scores, the local player's team outlined, and under them a band of
   26 x 17 units with three counts in red, green and blue */
void THISCALL (hud_drawTeamScores)(Scene *scene)
{
	char text[256];
	int boxWidth = hud_toScreenX(48), boxHeight = hud_toScreenY(20), top = hud_toScreenY(6);
	int left = gfx_getWidth() / 2 - boxWidth;
	glColor4f(1.0f, 0.0f, 0.0f, 0.5f);
	gfx_fillRect(left + 1, top + 1, boxWidth + left - 1, boxHeight + top - 1);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%d", scene->teamScores[scene_teamSlot(scene, 0)]);
	text_drawCentred(0x128, 9, 0x128, text, 16);
	int right = boxWidth + left + 1;
	glColor4f(0.0f, 0.5f, 1.0f, 0.5f);
	gfx_fillRect(right, top, boxWidth + right, boxHeight + top);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%d", scene->teamScores[scene_teamSlot(scene, 1)]);
	text_drawCentred(0x158, 9, 0x158, text, 16);

	top = hud_toScreenY(6);
	left = gfx_getWidth() / 2 - boxWidth;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int team = scene->players[scene->localPlayer].team;
	if (scene_teamSide(scene, team) == 0) {
		hud_drawRectOutline(left, top, boxWidth + left, boxHeight + top);
	} else if (scene_teamSide(scene, scene->players[scene->localPlayer].team) == 1) {
		int x = left + boxWidth + 1;
		hud_drawRectOutline(x + 1, top + 1, boxWidth + x - 1, boxHeight + top - 1);
	}

	int bandWidth = hud_toScreenX(26), bandHeight = hud_toScreenY(17), bandTop = hud_toScreenY(26);
	int bandLeft = gfx_getWidth() / 2 - bandWidth / 2 - bandWidth;
	glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	gfx_fillRect(bandLeft, bandTop, bandWidth + bandLeft + bandWidth * 2, bandHeight + bandTop - 1);
	text_setColor(1.0f, 0.0f, 0.0f, 1.0f);
	sprintf(text, "%d", scene->counterRed);
	text_drawCentred(0x119, 0x1b, 0x133, text, 16);
	text_setColor(0.0f, 1.0f, 0.0f, 1.0f);
	sprintf(text, "%d", scene->counterGreen);
	text_drawCentred(0x133, 0x1b, 0x14d, text, 16);
	text_setColor(0.0f, 0.0f, 1.0f, 1.0f);
	sprintf(text, "%d", scene->counterBlue);
	text_drawCentred(0x14d, 0x1b, 0x167, text, 16);
}
