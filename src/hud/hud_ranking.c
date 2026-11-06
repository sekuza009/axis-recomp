/* hud_ranking.c: the ranking table (held key / end of a match): the mode's title, then one row per player with
   name, grade badge, flag, kills / deaths and time played; in team games the teams in score order, the leader first;
   players without a team (spectators) last. */
#include "../game.h"
#include <string.h>

/* one row at *y (16 units high, the next row 16 below): the bar in the current colour, the name right-aligned
   at 0xf4 (8 units per character; the original passes the name to sprintf as its format), grade badge and flag
   to the left of the bar, "KILL/DEATH" and "TIME mm:ss". p is the player, flagOwner the player whose flag
   is shown */
static void ranking_row(Scene *scene, int p, int *y)
{
	char name[64], score[32], time[32];
	Player *player = &scene->players[p];
	hud_fillRect(0x70, *y, 0x210, *y + 0x10);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(name, player->name);
	text_drawSized(0xf4 - (int)strlen(name) * 8, *y, name, 8);
	int x = 0x70;
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	if (scene->ladderGame == 1) {
		x = 0x58;
		hud_drawEmblem(scene, player->grade, x, *y);
	}
	int flagOwner = scene->sessionMode ? p : player->player;
	if (scene->playerRecords[flagOwner].flagShown == 1) {
		x -= 0x18;
		hud_drawFlag(scene, flagOwner, x, *y);
	}
	sprintf(score, "KILL/DEATH %3d/%3d", player->kills, player->deaths);
	text_drawSized(0xfc, *y, score, 8);
	sprintf(time, "TIME %02d:%02d", player->timePlayed / 60, player->timePlayed % 60);
	text_drawSized(0x1b0, *y, time, 8);
}

/* 0x494930: the ranking table */
void THISCALL (hud_drawRanking)(Scene *scene)
{
	char title[64];
	int y = 0x8c;
	glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
	hud_fillRect(0x70, 0x70, 0x210, 0x80);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(title, "%s RANKING", g_gameModeNames[scene->gameMode]);
	text_drawCentred(0x140, 0x70, 0x140, title, 16);

	if (scene->teamGame == 1) {
		/* the leading team's side first (side 0 red, side 1 blue), a gap of 12 after a team with rows */
		int other = scene_teamIdAt(scene, 1);
		int lead = scene->teamScores[scene_teamIdAt(scene, 0)] < scene->teamScores[other];
		for (int pass = 0; pass < 2; pass++) {
			int side = pass == 0 ? lead : !lead, drawn = 0;
			float red = side == 0 ? 1.0f : 0.0f, blue = side == 0 ? 0.0f : 1.0f;
			for (int k = 0; k < scene->rankCount; k++) {
				int p = scene->ranking[k];
				if (scene_claimTeamSlot(scene, scene->players[p].team) != side)
					continue;
				glColor4f(red, 0.0f, blue, p == scene->localPlayer ? 0.5f : 0.2f);
				ranking_row(scene, p, &y);
				if (scene->players[p].isCommander == 1) {
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					hud_drawIcon(scene, 0x20c, y, scene->players[p].team + 9);
				}
				y += 0x10;
				drawn = 1;
			}
			if (drawn)
				y += 0xc;
		}
	} else if (scene->rankCount > 0) {
		/* every ranked player, the local one in blue */
		for (int k = 0; k < scene->rankCount; k++) {
			int p = scene->ranking[k];
			if (p == scene->localPlayer)
				glColor4f(0.0f, 0.0f, 1.0f, 0.2f);
			else
				glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
			ranking_row(scene, p, &y);
			if (scene->players[p].isKing == 1) {
				glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				hud_drawIcon(scene, 0x20c, y, 8);
			}
			y += 0x10;
		}
		y += 0xc;
	}

	/* the players in the game without a team, in green */
	for (int i = 0; i < 16; i++) {
		if (net_playerInUse(i) != 1 || scene->players[i].team >= 0)
			continue;
		glColor4f(0.0f, 1.0f, 0.0f, i == scene->localPlayer ? 0.5f : 0.2f);
		ranking_row(scene, i, &y);
		y += 0x10;
	}
}
