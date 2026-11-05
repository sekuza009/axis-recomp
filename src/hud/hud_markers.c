/* hud_markers.c: the marks over the other players in view, placed in screen pixels around each player's projected
   point (Player.screenPos[0], Player.tagTopLeft[1]; OpenGL's y runs up, hence height - y). */
#include "../game.h"
#include <string.h>
#include "hud.h"

/* one textured quad, w x h pixels with its top left at (x, y) (y down), from texture id texture (manager * 512 +
   slot), its cell from (s0, t0) to (s1, t1), in white at alpha; the screen height asked for at each corner */
static void marker_quad(int texture, float alpha, int x, int y, int w, int h, float s0, float t0, float s1, float t1)
{
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	glBegin(GL_QUADS);
	glTexCoord2f(s0, t0);
	glVertex2i(x, gfx_getHeight() - y);
	glTexCoord2f(s1, t0);
	glVertex2i(w + x, gfx_getHeight() - y);
	glTexCoord2f(s1, t1);
	glVertex2i(w + x, gfx_getHeight() - y - h);
	glTexCoord2f(s0, t1);
	glVertex2i(x, gfx_getHeight() - y - h);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* a texel count of a 256-texel texture to a texture coordinate, rounded to a float as the original stores it */
static float texel256(int n)
{
	return (float)((long double)n * (1.0f / 256));
}

/* a screen position to HUD units (640 x 480) */
static int marker_hudX(float px)
{
	return ftol(640.0f / (long double)gfx_getWidth() * px);
}
static int marker_hudY(float py)
{
	return ftol(480.0f / (long double)gfx_getHeight() * py);
}

/* a 64-unit mark standing on the player's point, centred */
static void marker_big(Scene *scene, Player *player, int texture, float alpha, float s0, float t0, float s1, float t1)
{
	(void)scene;
	int w = hud_scaleX(64.0f), h = hud_scaleY(64.0f);
	int x = ftol(player->screenPos[0]) - w / 2;
	int y = ftol(player->tagTopLeft[1]) - h;
	marker_quad(texture, alpha, x, y, w, h, s0, t0, s1, t1);
}

/* 0x4913a0: for every other player in play and on screen:
   - the king mark (isKing) and the platoon leader mark in the player's team's cell (isPlatoonLeader), from the marker texture;
   - the rest only while the name label is up (labelFade > 0), or always for a spectator (playing == 0) or in
     network mode 3, its alpha labelFade / 3 while playing (1 otherwise):
     an arrow over team mates (unless kingOfTheHill), the leader mark (rank 1, with the player's kills > 0),
     the name label in the team's colour with emblem and flag (not for the player a spectator follows), and the
     player's chat icon (chatIcon 1 or 2, always opaque) */
void THISCALL (hud_drawPlayerMarkers)(Scene *scene)
{
	char name[256];
	for (int i = 0; i < 16; i++) {
		Player *player = &scene->players[i];
		if (i == scene->localPlayer || player->state != 1 || player->onScreen != 1)
			continue;
		if (player->isKing == 1)
			marker_big(scene, player, scene->markerTexture, 1.0f, 0.0f, 0.75f, 0.25f, 1.0f);
		if (player->isCommander == 1)
			marker_big(scene, player, scene->markerTexture, 1.0f, texel256((player->team + 1) * 64), 0.75f,
			           texel256((player->team + 2) * 64), 1.0f);

		float alpha;
		if (!(player->labelFade > 0.0f) && scene->playing != 0 && scene->sessionMode != 3)
			goto status;
		if (scene->playing == 0 || scene->sessionMode == 3)
			alpha = 1.0f;
		else
			alpha = player->labelFade * (1.0f / 3);

		if (player->team == scene->players[scene->localPlayer].team && scene->sessionMode != 3 && scene->kingOfTheHill == 0) {
			/* the team mate arrow: 32 units, standing 16 units above the point */
			int w = hud_scaleX(32.0f), h = hud_scaleY(32.0f), lift = hud_scaleY(16.0f);
			int y = ftol(player->tagTopLeft[1]) - lift - h;
			int x = ftol(player->screenPos[0]) - w / 2;
			marker_quad(scene->hudTexture, alpha, x, y, w, h, 0.125f, 0.625f, 0.25f, 0.75f);
		}
		if (scene->rank[i] == 1 && scene->kingOfTheHill == 0 && scene->platoon == 0 && player->kills > 0)
			marker_big(scene, player, scene->hudTexture, alpha, 0.0f, 0.75f, 0.25f, 1.0f);

		if ((scene->playing == 0 && scene->cameraSlot >= 0 && i == scene->watchedPlayer)
		    || (scene->sessionMode == 3 && i == scene->watchedPlayer))
			goto status;
		if (scene->teamGame == 0)
			text_setColor(1.0f, 1.0f, 1.0f, alpha);
		else
			switch (scene_teamSide(scene, player->team)) {
			case 0: text_setColor(1.0f, 0.0f, 0.0f, alpha); break;
			case 1: text_setColor(0.0f, 0.0f, 1.0f, alpha); break;
			default: text_setColor(1.0f, 1.0f, 1.0f, alpha); break;
			}
		strcpy(name, player->name);
		{
			/* the name centred 16 units above the point, then emblem and flag to the left of where it starts */
			int right = marker_hudX(player->screenPos[0]);
			int y = marker_hudY(player->tagTopLeft[1]) - 0x10;
			int left = marker_hudX(player->screenPos[0]);
			/* through the original call site: the patch DLL retargets it (label_text) to centre the name on the player
			   and keep its letters 4:3 on wide screens */
			PATCHED_CALL(0x491c2d, void, int, int, int, const char *, int)(left, y, right, name, 8);   /* text_drawCentred */
			int centre = marker_hudX(player->screenPos[0]), half;
			if (PATCHED_BLOCK(0x491c58, 0x491c52, "52 8d 44 24 3c 50 e8 ?? ?? ?? ?? 59 5a 2b d0 90 90 90 90 90 90"))
				half = PATCHED_CALL(0x491c58, int, const char *, int)(name, centre);   /* the patch DLL measures the name */
			else
				half = (int)(strlen(name) >> 1) * 8;                                  /* 8 units per character */
			int x = centre - half;
			glColor4f(1.0f, 1.0f, 1.0f, alpha);
			if (scene->ladderGame == 1) {
				x -= 0x18;
				hud_drawEmblem(scene, player->grade, x, marker_hudY(player->tagTopLeft[1]) - 0x10);
			}
			int flagOwner = scene->sessionMode == 0 ? player->player : i;
			if (scene->playerRecords[flagOwner].flagShown == 1)
				hud_drawFlag(scene, flagOwner, x - 0x18, marker_hudY(player->tagTopLeft[1]) - 0x10);
		}

	status:
		if (player->chatIcon != 0) {
			/* 64 units, standing 16 units above the point; texture rows 128 (status 1) or 160 */
			int w = hud_scaleX(64.0f), h = hud_scaleY(64.0f), lift = hud_scaleY(16.0f);
			int y = ftol(player->tagTopLeft[1]) - lift - h;
			int x = ftol(player->screenPos[0]) - w / 2;
			int row = player->chatIcon == 1 ? 0x80 : 0xa0;
			marker_quad(scene->hudTexture, 1.0f, x, y, w, h, 0.0f, texel256(row), 0.125f, texel256(row + 0x20));
		}
	}
}
