/* hud_lockon.c: the lock-on marks over the other players. Both are quads from one texture (scene->hudTexture),
   placed in screen pixels around the player's projected position (OpenGL's y runs up, hence height - y). */
#include "../game.h"

/* one textured quad of size x size pixels with its top left at (x, y) in screen pixels (y down), its texture
   cell from (s0, t0) to (s1, t1); the screen height is asked for again at each corner, as the original does */
static void lockon_quad(int x, int y, int size, float s0, float t0, float s1, float t1)
{
	glTexCoord2f(s0, t0);
	glVertex2i(x, gfx_getHeight() - y);
	glTexCoord2f(s1, t0);
	glVertex2i(size + x, gfx_getHeight() - y);
	glTexCoord2f(s1, t1);
	glVertex2i(size + x, gfx_getHeight() - y - size);
	glTexCoord2f(s0, t1);
	glVertex2i(x, gfx_getHeight() - y - size);
}

/* 0x491f50: for every other player in play and on screen: while the local player's lock on it holds
   (scene->lockHeld) a box that closes in as lockAnim runs down from the lock's making, fading as the hold runs out;
   while it is only being aimed at (aimTime > 0) a fixed 64-unit box from the texture's other cell */
void THISCALL (hud_drawLockOn)(Scene *scene)
{
	for (int i = 0; i < 16; i++) {
		Actor *player = &scene->players[i];
		if (i == scene->localPlayer || player->state != 1 || player->onScreen != 1)
			continue;
		if (scene->lockHeld[i] > 0.0f) {
			float grow = player->lockAnim * 4.0f, holdLeft = scene->lockHeld[i] * 4.0f;
			float units = ((long double)grow * 5.0f + 1.0f) * 64.0f;
			int size = ftol(units / ((long double)640.0f / gfx_getWidth())), half = size / 2;
			int x = ftol(player->screenPos[0]) - half, y = ftol(player->screenPos[1]) - half;
			glEnable(GL_TEXTURE_2D);
			tex_bind(g_textures->banks[scene->hudTexture / 512], scene->hudTexture % 512);
			long double fade = 1.0L - grow;                       /* compared before it is rounded to a float */
			glColor4f(1.0f, 1.0f, 1.0f, fade >= holdLeft ? holdLeft : (float)fade);
			glBegin(GL_QUADS);
			lockon_quad(x, y, size, 0.25f, 0.5f, 0.5f, 0.75f);
		} else if (player->aimTime > 0.0f) {
			int size = ftol((long double)64.0f / ((long double)640.0f / gfx_getWidth())), half = size / 2;
			int x = ftol(player->screenPos[0]) - half, y = ftol(player->screenPos[1]) - half;
			glEnable(GL_TEXTURE_2D);
			tex_bind(g_textures->banks[scene->hudTexture / 512], scene->hudTexture % 512);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			lockon_quad(x, y, size, 0.75f, 0.75f, 1.0f, 1.0f);
		} else {
			continue;
		}
		glEnd();
		glDisable(GL_TEXTURE_2D);
	}
}
