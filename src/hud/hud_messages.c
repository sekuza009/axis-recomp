/* hud_messages.c: the HUD's centred texts and the text list overlay. */
#include "../game.h"

/* 0x495140: "Press fire button to start", centred */
void THISCALL (hud_drawPressFire)(Scene *scene)
{
	char text[256];
	(void)scene;
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "Press fire button to start");
	hud_44ae10(0, 0x168, 0x280, text, 16);
}

/* 0x496b80: the name of the player a spectator watches, or "FREE CAMERA" */
void THISCALL (replay_drawFollowedName)(Scene *scene)
{
	char text[256];
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (scene->watchedPlayer >= 0)
		sprintf(text, "%s", scene->players[scene->watchedPlayer].name);
	else
		sprintf(text, "FREE CAMERA");
	hud_44ae10(0, 0x192, 0x280, text, 16);
}

/* 0x496c20: the countdown before a round: "READY n" (yellow) while a second or more is left, then "START!" (red);
   when there is no countdown, the waiting text (scene->readyText) */
void THISCALL (hud_drawReadyStart)(Scene *scene)
{
	char text[256];
	if (scene->startTimer > 0.0f) {
		if (scene->startTimer >= 1.0f) {
			text_setColor(1.0f, 1.0f, 0.0f, 1.0f);
			sprintf(text, "READY %d", ftol(scene->startTimer));
		} else {
			text_setColor(1.0f, 0.0f, 0.0f, 1.0f);
			sprintf(text, "START!");
		}
		hud_44ae10(0, 0xf0, 0x280, text, 32);
	} else {
		text_setColor(1.0f, 1.0f, 0.0f, 1.0f);
		hud_44ae10(0, 0x172, 0x280, scene->readyText, 16);
	}
}

/* 0x4955a0 (hud_4955a0): the text list over the whole screen, darkened: 30 lines of scene->consoleLines */
void THISCALL (hud_4955a0)(Scene *scene)
{
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	int height = gfx_getHeight();
	gfx_fillRect(0, 0, gfx_getWidth(), height);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	for (int line = 0; line < 30; line++)
		text_drawSized(0xc0, line * 0x10, scene->consoleLines[line], 8);
}

/* 0x46bd00 (hud_46bd00): the outline of a rectangle (screen pixels, y down; its right and bottom edges one pixel
   outside x1 / y1) */
void (hud_46bd00)(int x0, int y0, int x1, int y1)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(x0, gfx_getHeight() - y0);
	glVertex2i(x1 + 1, gfx_getHeight() - y0);
	glVertex2i(x1 + 1, gfx_getHeight() - y1 - 1);
	glVertex2i(x0, gfx_getHeight() - y1 - 1);
	glEnd();
}
