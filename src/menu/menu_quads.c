/* menu_quads.c: the front end's textured quads: buttons cut from the menu's button sheet, panel backgrounds and
   the panel corner ornaments. Corners are in the menus' 640 x 480 units (menu_vertex), always in the order top left,
   top right, bottom right, bottom left. */
#include "../game.h"

/* a quad from (x0, y0) to (x1, y1) showing the texture from (s0, t0) to (s1, t1) */
static void textured_quad(int x0, int y0, int x1, int y1, float s0, float t0, float s1, float t1)
{
	glTexCoord2f(s0, t0);
	menu_vertex(x0, y0);
	glTexCoord2f(s1, t0);
	menu_vertex(x1, y0);
	glTexCoord2f(s1, t1);
	menu_vertex(x1, y1);
	glTexCoord2f(s0, t1);
	menu_vertex(x0, y1);
}

/* ---- buttons: one cell of the bound sheet; lit == 1 picks the lit cell, anything else the plain one ---- */

static void button(int x0, int y0, int x1, int y1, int lit, const float plainCell[4], const float litCell[4])
{
	const float *c = lit == 1 ? litCell : plainCell;
	glBegin(GL_QUADS);
	textured_quad(x0, y0, x1, y1, c[0], c[1], c[2], c[3]);
	glEnd();
}

/* 0x4282f0: the wide button (the screens' text buttons; 87 call sites in 28 functions) */
void (menu_drawWideButton)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.005f, 0.375f, 0.375f, 0.5f }, lit_[4] = { 0.38f, 0.375f, 0.75f, 0.5f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

/* 0x4283e0: the large button cell (0.625 x 0.156 of the sheet), lit or plain; every caller passes lit 1 (a label /
   field background): profile_drawNewDialog, newIdForm_draw (room_dialogs.c), armc_drawColourEditor (armc_screens.c),
   armc_drawPartsScreen (armc_parts_screen.c) */
void (menu_drawLargeButton)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.0f, 0.5f, 0.625f, 0.65625f }, lit_[4] = { 0.0f, 0.65625f, 0.625f, 0.8125f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

/* 0x4284d0, 0x4285c0, 0x4286b0, 0x4287a0: the arrow buttons (left, right, up, down), two cells each */
void (menu_drawLeftArrow)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.0f, 0.25f, 0.25f, 0.375f }, lit_[4] = { 0.5f, 0.25f, 0.75f, 0.375f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

void (menu_drawRightArrow)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.25f, 0.25f, 0.5f, 0.375f }, lit_[4] = { 0.75f, 0.25f, 1.0f, 0.375f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

void (menu_drawUpArrow)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.75f, 0.375f, 0.875f, 0.625f }, lit_[4] = { 0.875f, 0.375f, 1.0f, 0.625f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

void (menu_drawDownArrow)(int x0, int y0, int x1, int y1, int lit)
{
	static const float plain[4] = { 0.75f, 0.625f, 0.875f, 0.875f }, lit_[4] = { 0.875f, 0.625f, 1.0f, 0.875f };
	button(x0, y0, x1, y1, lit, plain, lit_);
}

/* ---- whole textures and the panel ornaments: these bind their texture and switch texturing on and off ---- */

static void bind(int texture)
{
	glEnable(GL_TEXTURE_2D);
	tex_bind(AP(void, AP(TextureManager, g_textures)->banks[texture / 512]), texture % 512);
}

/* 0x427a90: all of texture on the rectangle (a panel's background) */
void (menu_drawTexture)(int x0, int y0, int x1, int y1, int texture)
{
	bind(texture);
	glBegin(GL_QUADS);
	textured_quad(x0, y0, x1, y1, 0.0f, 0.0f, 1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* 0x427b60: the same, upside down */
void (menu_drawTextureFlipped)(int x0, int y0, int x1, int y1, int texture)
{
	bind(texture);
	glBegin(GL_QUADS);
	textured_quad(x0, y0, x1, y1, 0.0f, 1.0f, 1.0f, 0.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* 0x428a00: the ornaments on a panel's top left and bottom right corners (128-unit quarters of
   g_menuOrnamentTexture), placed around (x0, y0) and (x1, y1) */
void (menu_drawCornerOrnaments)(int x0, int y0, int x1, int y1)
{
	bind(g_menuOrnamentTexture);
	glBegin(GL_QUADS);
	textured_quad(x0 - 30, y0 - 18, x0 + 98, y0 + 110, 0.0f, 0.0f, 0.5f, 0.5f);
	glEnd();
	glBegin(GL_QUADS);
	textured_quad(x1 - 102, y1 - 100, x1 + 26, y1 + 28, 0.5f, 0.0f, 1.0f, 0.5f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* 0x428b50: the ornament on a panel's top right corner (the texture's lower right quarter, s and t 0.5 .. 1); the
   first argument is unused */
void (menu_drawTopRightOrnament)(int x0, int y0, int x1)
{
	(void)x0;
	bind(g_menuOrnamentTexture);
	glBegin(GL_QUADS);
	textured_quad(x1 - 114, y0 - 18, x1 + 14, y0 + 110, 0.5f, 0.5f, 1.0f, 1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}
