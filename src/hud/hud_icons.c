/* hud_icons.c: the ranking table's small icons: a player's emblem and a player's flag, each one cell of 24 x 16
   texels from an atlas, drawn 24 x 16 HUD units with its top left at (x, y). */
#include "../game.h"
#include "hud.h"

/* the cell's quad: corners in screen pixels (y down, flipped for OpenGL; the screen height asked for at each
   corner), texture coordinates from (s0, t0) to (s1, t1) */
static void icon_quad(int x, int y, int w, int h, float s0, float t0, float s1, float t1)
{
	glBegin(GL_QUADS);
	glTexCoord2f(s0, t0);
	glVertex2i(x, gfx_getHeight() - y);
	glTexCoord2f(s1, t0);
	glVertex2i(w + x, gfx_getHeight() - y);
	glTexCoord2f(s1, t1);
	glVertex2i(w + x, gfx_getHeight() - h - y);
	glTexCoord2f(s0, t1);
	glVertex2i(x, gfx_getHeight() - h - y);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* a texel count to a texture coordinate, rounded to a float as the original stores it */
static float texel(int n, float perTexel)
{
	return (float)((long double)n * perTexel);
}

/* 0x4922c0: emblem number emblem (1 up; 0 or less draws nothing) from the emblem texture (scene->emblemTexture,
   256 texels wide): ten cells per row, the rows starting 224 texels down */
void THISCALL (hud_drawNameIcon)(Scene *scene, int emblem, int x, int y)
{
	if (emblem <= 0)
		return;
	int cell = emblem - 1;
	int sx = hud_toScreenX(x), sy = hud_toScreenY(y);
	int w = hud_scaleX(24.0f), h = hud_scaleY(16.0f);
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[scene->emblemTexture / 512], scene->emblemTexture % 512);
	int row = cell / 10, col = cell % 10;
	icon_quad(sx, sy, w, h, texel(col * 24, 1.0f / 256), texel((row + 14) * 16, 1.0f / 256),
	          texel(col * 24 + 24, 1.0f / 256), texel((row + 15) * 16, 1.0f / 256));
}

/* 0x4924d0: player's flag: four cells per row from the flag texture (128 x 64 texels); in the mode
   scene->flagOwnerIsSelf, from the GL texture scene->flagGlTexture instead of the texture manager */
void THISCALL (hud_drawLeaderIcon)(Scene *scene, int player, int x, int y)
{
	int sx = hud_toScreenX(x), sy = hud_toScreenY(y);
	int w = hud_scaleX(24.0f), h = hud_scaleY(16.0f);
	glEnable(GL_TEXTURE_2D);
	if (scene->flagOwnerIsSelf == 0)
		tex_bind(g_textures->managers[scene->flagTexture / 512], scene->flagTexture % 512);
	else
		glBindTexture(GL_TEXTURE_2D, scene->flagGlTexture);
	int row = player / 4, col = player % 4;
	icon_quad(sx, sy, w, h, texel(col * 24, 1.0f / 128), texel(row * 16, 1.0f / 64),
	          texel(col * 24 + 24, 1.0f / 128), texel((row + 1) * 16, 1.0f / 64));
}
