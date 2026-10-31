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
		int y = net != 0 || scene->localTeam < 0 ? 0xb4 : 0xc8;
		if (net == 1 && scene->teamGame == 1 && scene->localTeam >= 0)
			y -= 0x14;
		if (net == 1)
			y -= 0x14;
		esc_title(scene, alpha, alpha, y, "MENU");
		y += 0x28;
		if (scene->network != 0 || scene->localTeam < 0) {
			const char *label = scene->localTeam >= 0 ? "SPECTATOR" : scene->network == 0 ? "START" : "JOIN";
			esc_item(scene, alpha, y, label, 0);
			y += 0x28;
		}
		if (scene->network == 1) {
			if (scene->teamGame == 1 && scene->localTeam >= 0) {
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

/* 0x49ca20: the in-match menu opened on page with item under the cursor (a spectator's page 4 first, overwritten:
   the original stores both) */
void THISCALL (escMenu_open)(Scene *scene, int page, int item)
{
	if (scene->localPlayer < 0) {
		scene->escPage = 4;
		scene->escCursor = 0;
	}
	scene->escMenuOpen = 1;
	scene->escPage = page;
	scene->escCursor = item;
	BITS(scene->escTimer) = 0;
}

/* ---- the menu's keys (scene->menuKeys: up, down, enter, escape; 1 pressed) ---- */
enum { KEY_UP, KEY_DOWN, KEY_ENTER, KEY_ESC };

/* the main page's cursor moved: items 0 START / JOIN / SPECTATOR, 1 TEAM, 2 RECORD, 3 HELP, 4 QUIT. A single-player
   game has 0 (only without a team), 3 and 4; TEAM needs a team game and a team. Anything else goes to QUIT */
static void esc_mainCursor(Scene *scene, int down)
{
	int sel = scene->escCursor, teamItem = scene->teamGame == 1 && scene->localTeam >= 0;
	if (!scene->network) {
		static const int up[5] = { 4, 4, 4, -1, 3 }, dn[5] = { 3, 4, 4, 4, -1 };
		int to = (u32)sel <= 4 ? (down ? dn : up)[sel] : 4;
		if (to < 0)   /* past the hidden item 0 */
			to = scene->localTeam >= 0 ? (down ? 3 : 4) : 0;
		scene->escCursor = to;
	} else if ((u32)sel > 4)
		scene->escCursor = 4;
	else if (down)
		scene->escCursor = sel == 0 ? (teamItem ? 1 : 2) : sel == 4 ? 0 : sel + 1;
	else
		scene->escCursor = sel == 0 ? 4 : sel == 2 ? (teamItem ? 1 : 0) : sel - 1;
}

/* the two-item pages' cursor: up 0, down 1 */
static void esc_pairCursor(Scene *scene)
{
	if (scene->menuKeys[KEY_UP] == 1)
		scene->escCursor = 0;
	else if (scene->menuKeys[KEY_DOWN] == 1)
		scene->escCursor = 1;
}

/* the local player's ranking record reset for a team change (the emblems redrawn first) */
static void esc_resetScore(Scene *scene)
{
	if (scene->showEmblems == 1)
		sound_updateListener(scene);
	scene->players[scene->localPlayer].statF0 = 0;
	scene->players[scene->localPlayer].kills = 0;
	scene->players[scene->localPlayer].deaths++;
}

/* the main page. Returns 1 when the menu closes */
static int esc_main(Scene *scene)
{
	const int *keys = scene->menuKeys;
	if (keys[KEY_UP] == 1)
		esc_mainCursor(scene, 0);
	else if (keys[KEY_DOWN] == 1)
		esc_mainCursor(scene, 1);
	if (keys[KEY_ENTER] != 1)
		return keys[KEY_ESC] == 1;
	switch (scene->escCursor) {
	case 0:
		if (scene->localTeam >= 0) {   /* SPECTATOR: the actor taken out, watching from now on */
			actor_deactivate(STAGE(scene), scene->localPlayer);
			if (scene->network)
				scene->localTeam = -1;
			scene->playing = 0;
			if (scene->network == 1) {
				match_4613a0(scene, -1);
				scene->players[scene->localPlayer].team = -1;
				esc_resetScore(scene);
				msg_playerChangedTeam(scene, scene->localPlayer, -1);
				match_463610(scene, scene->localPlayer, -1, scene->mechName);
				msg_newKing(scene);
				scene->watchedPlayer = -1;
			}
			vsprintf_wrap_463450(scene, (const char *)0x4d06f4);
			return 1;
		}
		if (scene->teamGame != 1) {   /* START */
			scene->teamAsked = 1;
			return 1;
		}
		if (scene->chosenTeam >= 0 && scene->network)   /* JOIN: the team page, on the team asked for before */
			escMenu_open(scene, 1, scene_teamSide(scene, scene->chosenTeam) != 0);
		else
			escMenu_open(scene, 1, scene->counterRed > scene->counterBlue);
		return 0;
	case 1:
		escMenu_open(scene, 1, scene->counterRed > scene->counterBlue);
		return 0;
	case 2:
		if (scene->recording) {
			replay_closeRecording(scene);
			return 1;
		}
		escMenu_open(scene, 2, 0);   /* the replay's name typed */
		chat_textField(0, 0, 16);
		return 0;
	case 3:
		scene->consoleOpen = 1;
		return 1;
	case 4:
		escMenu_open(scene, 4, 0);
		return 0;
	}
	return 0;
}

/* page 1, the team: RED (0) / BLUE (1); single player games take team slot 0 and ask to play. A changed team is
   announced (joined, or changed from another) and the score reset */
static int esc_team(Scene *scene)
{
	const int *keys = scene->menuKeys;
	esc_pairCursor(scene);
	if (keys[KEY_ENTER] != 1)
		return keys[KEY_ESC] == 1;
	if (!scene->network) {
		scene->localTeam = 0;
		scene->teamAsked = 1;
		scene->chosenTeam = 0;
		scene->teamIds[scene->escCursor == 0 ? 0 : 1] = 0;
	} else {
		scene->localTeam = scene->teamIds[scene->escCursor == 0 ? 0 : 1];
		scene->chosenTeam = scene->localTeam;
	}
#define TEAM_NOW GAME_VAR(int, (u8 *)STAGE(scene) + 0x1561b68 + scene->localPlayer * 0x47fd2 + 0x48)   /* the player's resource set */
	if (TEAM_NOW == scene->localTeam)
		return 1;
	if (TEAM_NOW >= 0) {
		esc_resetScore(scene);
		msg_newKing(scene);
	}
	if (TEAM_NOW < 0) {
		msg_playerJoinedTeam(scene, scene->localPlayer, scene->localTeam);
		match_4635b0(scene, scene->localPlayer, scene->localTeam, scene->mechName);
	} else if (TEAM_NOW != scene->localTeam) {
		msg_playerChangedTeam(scene, scene->localPlayer, scene->localTeam);
		match_463610(scene, scene->localPlayer, scene->localTeam, scene->mechName);
	}
#undef TEAM_NOW
	match_4613a0(scene, scene->localTeam);
	scene->teamChanged = 1;
	return 1;
}

/* page 2, the replay's name: once typing has ended, recording starts under it (if one was typed) */
static int esc_name(Scene *scene)
{
	if (g_paused)
		return scene->menuKeys[KEY_ESC] == 1;
	chat_keepLastLine();
	if (*(const char *)0x9f63e4)
		autoplay_startRecording(scene, (const char *)0x9f63e4);
	return 1;
}

/* page 3, RETRY?: YES restarts the match (the clock and the restart values), NO leaves it. Escape does nothing */
static int esc_retry(Scene *scene)
{
	esc_pairCursor(scene);
	if (scene->menuKeys[KEY_ENTER] != 1)
		return 0;
	if (scene->escCursor != 0) {
		scene->quitAsked = 1;
		return 1;
	}
	scene->clockExtra = 0;
	scene->elapsed = 0;
	scene->timeFraction = 0.0f;
	memcpy(scene->restartA, scene->restartFrom, sizeof scene->restartA);
	memcpy(scene->restartB, scene->restartFrom + 3, sizeof scene->restartB);
	music_playMatch(scene);
	return 1;
}

/* page 4, QUIT?: YES leaves the match */
static int esc_quit(Scene *scene)
{
	esc_pairCursor(scene);
	if (scene->menuKeys[KEY_ENTER] != 1)
		return scene->menuKeys[KEY_ESC] == 1;
	if (scene->escCursor == 0)
		scene->quitAsked = 1;
	return 1;
}

/* 0x49ca70: the in-match menu's keys, once it has faded in (a quarter second): its page's (the main page, the team,
   the replay's name, RETRY?, QUIT?), the menu closed when the page says so, a sound for any key; the open time
   (escTimer) runs on by the frame's */
void THISCALL (match_escMenu)(Scene *scene)
{
	static int (*const page[5])(Scene *) = { esc_main, esc_team, esc_name, esc_retry, esc_quit };
	if (scene->escTimer >= *(const float *)0x4a941c) {
		if ((u32)scene->escPage <= 4 && page[scene->escPage](scene))
			scene->escMenuOpen = 0;
		const int *keys = scene->menuKeys;
		if (keys[KEY_UP] | keys[KEY_DOWN] | keys[KEY_ENTER] | keys[KEY_ESC])
			sound_playVolume(9, 100);
	}
	scene->escTimer = f32(fadd_m(fld_m(&scene->frameTime), &scene->escTimer));
}
