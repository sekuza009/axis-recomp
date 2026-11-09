/* hud_icons.c: the HUD's small icons from atlases: the HUD's icons (hud_drawIcon: a 32-texel cell of the icon atlas,
   drawn 32 x 32 units at (x, y - 8)), and a player's grade badge and flag (the ranking table's: one 24 x 16-texel
   cell each, drawn 24 x 16 HUD units with its top left at (x, y)). */
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

/* 0x4922c0: the badge of grade `grade` (1 up; 0 or less draws nothing) from the HUD's icon atlas (scene->iconTexture,
   256 texels wide): ten cells per row, the rows starting 224 texels down */
void THISCALL (hud_drawGradeBadge)(Scene *scene, int grade, int x, int y)
{
	if (grade <= 0)
		return;
	int cell = grade - 1;
	int sx = hud_toScreenX(x), sy = hud_toScreenY(y);
	int w = hud_scaleX(24.0f), h = hud_scaleY(16.0f);
	glEnable(GL_TEXTURE_2D);
	tex_bind(AP(TextureManager, g_textures)->banks[scene->iconTexture / 512], scene->iconTexture % 512);
	int row = cell / 10, col = cell % 10;
	icon_quad(sx, sy, w, h, texel(col * 24, 1.0f / 256), texel((row + 14) * 16, 1.0f / 256),
	          texel(col * 24 + 24, 1.0f / 256), texel((row + 15) * 16, 1.0f / 256));
}

/* 0x4924d0: player's flag: four cells per row (128 x 64 texels): in a solo game (sessionMode 0) from the map's flag
   texture (scene->flagTexture), else from the players' own flags' atlas (scene->flagGlTexture) */
void THISCALL (hud_drawFlag)(Scene *scene, int player, int x, int y)
{
	int sx = hud_toScreenX(x), sy = hud_toScreenY(y);
	int w = hud_scaleX(24.0f), h = hud_scaleY(16.0f);
	glEnable(GL_TEXTURE_2D);
	if (scene->sessionMode == 0)
		tex_bind(AP(TextureManager, g_textures)->banks[scene->flagTexture / 512], scene->flagTexture % 512);
	else
		glBindTexture(GL_TEXTURE_2D, scene->flagGlTexture);
	int row = player / 4, col = player % 4;
	icon_quad(sx, sy, w, h, texel(col * 24, 1.0f / 128), texel(row * 16, 1.0f / 64),
	          texel(col * 24 + 24, 1.0f / 128), texel((row + 1) * 16, 1.0f / 64));
}

/* 0x496820: icon number icon from the HUD's icon atlas (scene->iconTexture, 256 texels wide): eight 32-texel cells
   per row, the rows starting 96 texels down; drawn 32 x 32 HUD units, white, with its top left at (x, y - 8) */
void THISCALL (hud_drawIcon)(Scene *scene, int x, int y, int icon)
{
	float s0 = texel(icon % 8 * 32, 1.0f / 256), t0 = texel((icon / 8 + 3) * 32, 1.0f / 256);
	int sy = hud_toScreenY(y - 8), sx = hud_toScreenX(x);
	int w = hud_scaleX(32.0f), h = hud_scaleY(32.0f);
	glEnable(GL_TEXTURE_2D);
	tex_bind(AP(TextureManager, g_textures)->banks[scene->iconTexture / 512], scene->iconTexture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	float s1 = s0 + 0.125f, t1 = t0 + 0.125f;
	icon_quad(sx, sy, w, h, s0, t0, s1, t1);
}
