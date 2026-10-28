/* hud_escmenu.c: the in-match menu (Esc) and its boxes: its pages, each a grey title box and white item boxes (hud_495ed0),
   fading in over its first quarter second. The item under the cursor (scene->escCursor) is drawn bright. */
#include "../game.h"
#include <string.h>
#include "hud.h"

/* an item's text colour: bright yellow-white under the cursor, else grey */
static void esc_itemColour(int selected, float alpha)
{
	if (selected)
		text_setColor(1.0f, 1.0f, 0.5f, alpha);
	else
		text_setColor(0.5f, 0.5f, 0.5f, alpha);
}

/* a box from x 0xe0 to 0x1a0, 16 high at y, in the given grey and alpha */
static void esc_box(Scene *scene, float grey, float alpha, int y)
{
	glColor4f(grey, grey, grey, alpha);
	hud_495ed0(scene, 0xe0, y, 0x1a0, y + 0x10);
}

/* a page's title: a box (grey, at boxAlpha) and the title in white, centred */
static void esc_title(Scene *scene, float boxAlpha, float alpha, int y, const char *title)
{
	char text[256];
	esc_box(scene, 0.5f, boxAlpha, y);
	sprintf(text, title);
	text_setColor(1.0f, 1.0f, 1.0f, alpha);
	hud_44ae10(0x140, y, 0x140, text, 16);
}

/* one item of the main page at y: a white box and the label, bright when the cursor is on item number item */
static void esc_item(Scene *scene, float alpha, int y, const char *label, int item)
{
	char text[256];
	esc_box(scene, 1.0f, alpha, y);
	sprintf(text, label);
	esc_itemColour(scene->escCursor == item, alpha);
	hud_44ae10(0x140, y, 0x140, text, 16);
}

/* the YES / NO pair under a question */
static void esc_yesNo(Scene *scene, float alpha)
{
	char text[256];
	esc_box(scene, 1.0f, alpha, 0xf0);
	sprintf(text, "YES");
	esc_itemColour(scene->escCursor == 0, alpha);
	hud_44ae10(0x110, 0xf0, 0x110, text, 16);
	sprintf(text, "NO");
	esc_itemColour(scene->escCursor == 1, alpha);
	hud_44ae10(0x170, 0xf0, 0x170, text, 16);
}

/* 0x495610: the menu's page scene->escPage:
   0 the main page: MENU, then START / JOIN / SPECTATOR (not for a player in a single-player game), TEAM (team
     games, multiplayer, while playing), RECORD / STOP RECORDING (multiplayer), HELP, QUIT; the column is placed
     higher the more items it has
   1 the team choice: RED / BLUE
   2 the replay's file name being typed (g_chatLine)
   3 RETRY? ("MISSION FAILED, RETRY" when a mission ends on the stage reached) / 4 QUIT?, with YES / NO */
void THISCALL (hud_drawEscMenu)(Scene *scene)
{
	char text[256];
	float alpha;
	if (!(scene->escTimer >= 0.25f))                      /* NaN fades as the original does */
		alpha = (float)(1.0L - (0.25L - scene->escTimer) * 4.0L);
	else
		alpha = 1.0f;

	switch (scene->escPage) {
	case 0: {
		int net = scene->network;
		int y = net != 0 || scene->respawnPlayer < 0 ? 0xb4 : 0xc8;
		if (net == 1 && scene->teamGame == 1 && scene->respawnPlayer >= 0)
			y -= 0x14;
		if (net == 1)
			y -= 0x14;
		esc_title(scene, alpha, alpha, y, "MENU");
		y += 0x28;
		if (scene->network != 0 || scene->respawnPlayer < 0) {
			const char *label = scene->respawnPlayer >= 0 ? "SPECTATOR" : scene->network == 0 ? "START" : "JOIN";
			esc_item(scene, alpha, y, label, 0);
			y += 0x28;
		}
		if (scene->network == 1) {
			if (scene->teamGame == 1 && scene->respawnPlayer >= 0) {
				esc_item(scene, alpha, y, "TEAM", 1);
				y += 0x28;
			}
			if (scene->network == 1) {
				esc_item(scene, alpha, y, scene->recording ? "STOP RECORDING" : "RECORD", 2);
				y += 0x28;
			}
		}
		esc_item(scene, alpha, y, "HELP", 3);
		y += 0x28;
		esc_item(scene, alpha, y, "QUIT", 4);
		break;
	}
	case 1:
		esc_title(scene, alpha, alpha, 0xc8, "TEAM");
		esc_box(scene, 1.0f, alpha, 0xf0);
		sprintf(text, "RED");
		if (scene->escCursor == 0)
			text_setColor(1.0f, 0.0f, 0.0f, alpha);
		else
			text_setColor(0.5f, 0.5f, 0.5f, alpha);
		hud_44ae10(0x110, 0xf0, 0x110, text, 16);
		sprintf(text, "BLUE");
		if (scene->escCursor == 1)
			text_setColor(0.0f, 0.0f, 1.0f, alpha);
		else
			text_setColor(0.5f, 0.5f, 0.5f, alpha);
		hud_44ae10(0x170, 0xf0, 0x170, text, 16);
		break;
	case 2:
		esc_title(scene, 0.5f, alpha, 0xdc, "INPUT FILE NAME");
		esc_box(scene, 1.0f, alpha, 0x104);
		strcpy(text, g_chatLine);
		text_setColor(1.0f, 1.0f, 1.0f, alpha);
		hud_44ae10(0x140, 0x104, 0x140, text, 16);
		break;
	case 3:
		esc_title(scene, 0.5f, alpha, 0xc8,
		          scene->stageCleared == 0 && g_missionStage == g_missionProgress ? "MISSION FAILED, RETRY" : "RETRY");
		esc_yesNo(scene, alpha);
		break;
	case 4:
		esc_title(scene, 0.5f, alpha, 0xc8, "QUIT");
		esc_yesNo(scene, alpha);
		break;
	}
}

/* 0x495ed0 (hud_495ed0): a menu box: the rectangle (x0, y0) - (x1, y1) in HUD units with a 32-unit border around
   it, drawn as nine quads (corners, edges, middle) from the 3 x 3 cells of 32 texels at the top left of the menu
   texture (scene->menuBoxTexture) */
void THISCALL (hud_495ed0)(Scene *scene, int x0, int y0, int x1, int y1)
{
	int left[9], top[9], right[9], bottom[9];
	int sx0 = hud_toScreenX(x0), sy0 = hud_toScreenY(y0), sx1 = hud_toScreenX(x1), sy1 = hud_toScreenY(y1);
	for (int k = 0; k < 9; k++) {
		switch (k % 3) {
		case 0: {
			float fx = (float)sx0;
			left[k] = ftol(fx - 32.0f / ((long double)640.0f / gfx_getWidth()));
			right[k] = sx0;
			break;
		}
		case 1: left[k] = sx0; right[k] = sx1; break;
		case 2:
			left[k] = sx1;
			right[k] = ftol(32.0f / ((long double)640.0f / gfx_getWidth()) + sx1);
			break;
		}
		switch (k / 3) {
		case 0: {
			float fy = (float)sy0;
			top[k] = ftol(fy - 32.0f / ((long double)480.0f / gfx_getHeight()));
			bottom[k] = sy0;
			break;
		}
		case 1: top[k] = sy0; bottom[k] = sy1; break;
		case 2:
			top[k] = sy1;
			bottom[k] = ftol(32.0f / ((long double)480.0f / gfx_getHeight()) + sy1);
			break;
		}
	}
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[scene->menuBoxTexture / 512], scene->menuBoxTexture % 512);
	glBegin(GL_QUADS);
	for (int k = 0; k < 9; k++) {
		int row = k / 3, col = k % 3;
		float t0 = (float)((long double)(row * 32) * (1.0f / 256)), s0 = (float)((long double)(col * 32) * (1.0f / 256));
		float s1 = (float)((long double)((col + 1) * 32) * (1.0f / 256)), t1 = (float)((long double)((row + 1) * 32) * (1.0f / 256));
		glTexCoord2f(s0, t0);
		glVertex2i(left[k], gfx_getHeight() - top[k]);
		glTexCoord2f(s1, t0);
		glVertex2i(right[k], gfx_getHeight() - top[k]);
		glTexCoord2f(s1, t1);
		glVertex2i(right[k], gfx_getHeight() - bottom[k]);
		glTexCoord2f(s0, t1);
		glVertex2i(left[k], gfx_getHeight() - bottom[k]);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
