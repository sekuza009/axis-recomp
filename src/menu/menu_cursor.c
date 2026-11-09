/* menu_cursor.c: the front end's mouse pointer, an animated sprite of 15 frames in a 4 x 4 sheet. */
#include "../game.h"
#include "../fixes/fixes.h"

/* 0x429bc0: the pointer at (g_mouseX, g_mouseY): a 47-unit quad with its tip at the top left, textured with the
   current frame's cell (a quarter of the sheet each way); then the animation clock: every 5 units of frame time the
   next frame. Its right-hand corners go through two call sites the patch DLL retargets (cursor_vtx keeps the
   sprite's proportions on wide screens) */
void (menu_drawCursor)(void)
{
	int x = g_mouseX, y = g_mouseY;
	int column = g_cursorFrame % 4, row = g_cursorFrame / 4;
	gfx_setProjection2D3D(2);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_bind(AP(TextureManager, g_textures)->banks[g_cursorTexture / 512], g_cursorTexture % 512);
#ifdef AXIS_NATIVE   /* (pixel-sharp: the linear filter blended in the next frame's cell, a thin line at its edge) */
	int sharp[2], sharpOn = g_settings.sharpText && platform_texNearest(sharp);
#endif
	glBegin(GL_QUADS);
	float left = (float)column, top = (float)row;
	float s0 = left * 0.25f, t0 = top * 0.25f;
	glTexCoord2f(s0, t0);
	menu_vertex(x, y);
	float s1 = (left + 1.0f) * 0.25f;
	glTexCoord2f(s1, t0);
#ifdef AXIS_NATIVE
	fix_cursorVertex(x + 0x2f, y);   /* (its proportions kept: fixes/screen.c) */
#else
	SITE_CALL(0x429cc3, menu_vertex, void, int, int)(x + 0x2f, y);                /* menu_vertex */
#endif
	float t1 = (top + 1.0f) * 0.25f;
	glTexCoord2f(s1, t1);
#ifdef AXIS_NATIVE
	fix_cursorVertex(x + 0x2f, y + 0x2f);
#else
	SITE_CALL(0x429cf0, menu_vertex, void, int, int)(x + 0x2f, y + 0x2f);         /* menu_vertex */
#endif
	glTexCoord2f(s0, t1);
	menu_vertex(x, y + 0x2f);
	glEnd();
#ifdef AXIS_NATIVE
	if (sharpOn)
		platform_texRestore(sharp);
#endif
	glDisable(GL_TEXTURE_2D);

	g_cursorFrameTime = g_frameTime + g_cursorFrameTime;
	if (g_cursorFrameTime >= 5.0f) {
		g_cursorFrameTime = 0.0f;
		if (++g_cursorFrame >= 15)
			g_cursorFrame = 0;
	}
}
