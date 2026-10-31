/* glyph_cells.c: the font atlases' cell tables: for each glyph its texture coordinates, a row's top and bottom
   (the same across the row) and a column's left and right. Every value is a texel number times the constant at
   0x4a957c (1/256). */
#include "../game.h"
#include "../wide.h"
#include <stdarg.h>

typedef struct {
	int r0, rstep, rend;   /* the rows' first texel, the step between rows, the end */
	int rLo, rHi;          /* a row's low and high edge from its texel */
	int cols, cstep;       /* glyphs a row, texels between columns */
	int cLo, cHi;          /* a column's low and high edge */
	u32 rowHi, rowLo, colLo, colHi;   /* the four tables (floats, one per glyph) */
} Grid;

static void glyph_grid(const Grid *g)
{
	typedef long double X;
	const float texel = GAME_VAR(float, 0x4a957c);
	int idx = 0;
	for (int r = g->r0; r < g->rend; r += g->rstep) {
		float lo = (float)((X)(r + g->rLo) * texel), hi = (float)((X)(r + g->rHi) * texel);
		for (int c = 0; c < g->cols; c++)
			GAME_VAR(float, g->rowHi + (idx + c) * 4) = hi;
		for (int c = 0; c < g->cols; c++)
			GAME_VAR(float, g->rowLo + (idx + c) * 4) = lo;
		for (int c = 0; c < g->cols; c++, idx++) {
			GAME_VAR(float, g->colLo + idx * 4) = (float)((X)(c * g->cstep + g->cLo) * texel);
			GAME_VAR(float, g->colHi + idx * 4) = (float)((X)(c * g->cstep + g->cHi) * texel);
		}
	}
}

/* 0x42f940: the menu fonts' (16 x 8 of 16 texels, 32 x 16 of 8, and four extra rows) */
void (font_initMenuGrids)(void)
{
	static const Grid grids[3] = {
		{ 0, 16, 0x80, 0, 15, 16, 16, 0, 15, 0x9db0b0, 0x9da4a8, 0x9da90c, 0x9db510 },
		{ 0, 16, 0x80, 0, 15, 32, 8, 1, 8, 0x67ff64, 0x6803ac, 0x6807ac, 0x67fb64 },
		{ 0x87, 8, 0xa7, -7, 0, 32, 8, 1, 8, 0x4e0ce4, 0x5b1114, 0x5b1514, 0x4e10e8 } };
	for (int k = 0; k < 3; k++)
		glyph_grid(&grids[k]);
}

/* 0x42fb40: the HUD fonts' */
void (font_initHudGrids)(void)
{
	static const Grid grids[3] = {
		{ 0, 16, 0x100, 0, 15, 16, 16, 0, 15, 0x4e0474, 0x5b0910, 0x5b0d10, 0x4e0878 },
		{ 0, 16, 0x60, 0, 15, 16, 16, 0, 15, 0x5b1b64, 0x4e16d8, 0x4e1548, 0x5b199c },
		{ 0x6f, 16, 0xdf, -15, 0, 16, 16, 0, 15, 0x83a7e0, 0x4df638, 0x4df458, 0x83a600 } };
	for (int k = 0; k < 3; k++)
		glyph_grid(&grids[k]);
}

/* the pen font's glyph g as four corner tables of (s, t) pairs, 8 bytes a glyph: top left, top right, bottom
   right, bottom left */
static void pen_cell(const u32 corner[4], int g, int x0, int x1, int y0, int y1)
{
	const float *texel = (const float *)0x4a957c;
	float left = f32(fmul_m((long double)x0, texel)), right = f32(fmul_m((long double)x1, texel));
	float top = f32(fmul_m((long double)y0, texel)), bottom = f32(fmul_m((long double)y1, texel));
	const float st[4][2] = { { left, top }, { right, top }, { right, bottom }, { left, bottom } };
	for (int k = 0; k < 4; k++) {
		GAME_VAR(float, corner[k] + g * 8) = st[k][0];
		GAME_VAR(float, corner[k] + g * 8 + 4) = st[k][1];
	}
}

/* 0x46b950: the pen font (the HUD's small text) from texture `name` (into 0xa106ac): 105 glyphs (from 1) in two
   sets of 5 rows of 21, every glyph 8 wide (0xa0fb28): the fixed set, 8 x 8 texels from row 0x48, and the
   proportional set, rows of 14 texels from the top with the widths at 0x4c5558. A second call only complains
   (0xa106a8 set): 0. Otherwise 1 */
int (pen_init)(const char *name)
{
	static const u32 fixed[4] = { 0xa0f490, 0xa10010, 0xa0f148, 0xa0fcc8 };
	static const u32 proportional[4] = { 0xa0eab8, 0xa10358, 0xa0ee00, 0xa0f7d8 };
	if (GAME_VAR(int, 0xa106a8) == 1) {
		GAME_CDECL(0x46c840, void, const char *)((const char *)0x4c56fc);   /* "pen duplicate initialization" */
		return 0;
	}
	GAME_VAR(int, 0xa106ac) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 0x69; i++)
		GAME_VAR(int, 0xa0fb28 + i * 4) = 8;
	int g = 1;
	for (int y = 0x48; g <= 105; y += 8)
		for (int c = 0; c < 21; c++, g++)
			pen_cell(fixed, g, c * 8, c * 8 + 8, y, y + 8);
	const int *width = (const int *)0x4c5558;
	g = 1;
	for (int y = 0; g <= 105; y += 14)
		for (int c = 0, x = 0; c < 21; c++, g++, x += *width++)
			pen_cell(proportional, g, x, x + *width, y, y + 14);
	return 1;
}

/* 0x46bdc0: the number value drawn with the HUD's digits (the armor / shield / ammo counters), right to left in
   count slots ending at x + count * w / 2: each slot w = scale * 28 wide, each digit h = scale * 26 tall (centred
   on y) and widened by pad (scale * the float at 0x4a9534) on both sides. Unless padded, the slots beyond the
   value's own digits are left out. A negative value is drawn by its size with a minus sign to the left, on the slot
   where the next digit would go - over the last digit when all count slots were drawn. The
   cells are 35 x 27 texels of the HUD texture (0xa106ac; digit d at column d % 5, row d / 5 from row 112, the minus
   at 175, 112). Two of the patch DLL's changes are followed as they stand in the code: the height's factor (26, the
   operand of the fmul at 0x46bdda) may be its height-based one, and the texture coordinates' function (loaded at
   0x46be96) may be its half-texel inset. Returns glDisable's eax */
u32 (hud_drawDigits)(int x, int y, float scale, int value, int count, int padded)
{
	const float *texel = (const float *)0x4a957c;                         /* 1/256 */
	const float *heightFactor = *(const float *const *)0x46bddc;          /* (the fmul's operand) */
	void (STDCALL *const *texCoord)(u32, u32) = *(void (STDCALL *const *const *)(u32, u32))0x46be98;   /* (mov ebx, [..]) */
	int w = ftol(fmul_m(fld_m(&scale), (const float *)0x4aa280));       /* 28 */
	int h = ftol(fmul_m(fld_m(&scale), heightFactor));
	int pad = ftol(fmul_m(fld_m(&scale), (const float *)0x4a9534));
	x += (int)((u32)w * (u32)count) / 2;
	int top = y - h / 2, negative = 0;
	if (value < 0) {
		value = -value;
		negative = 1;
	}
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[GAME_VAR(int, 0xa106ac) / 512], GAME_VAR(int, 0xa106ac) % 512);
	glBegin(GL_QUADS);
	void (STDCALL *tc)(u32, u32) = *texCoord;
	int place = 10;
	for (int i = 0; i < count; i++) {
		x -= w;
		int unit = place / 10, digit = (value % place) / unit;
		if (!padded && i > 0 && value < unit)
			break;
		int row = digit / 5, col = digit % 5;
		float t0 = f32(fmul_m((long double)(row * 27 + 0x70), texel)), s0 = f32(fmul_m((long double)(col * 35), texel));
		tc(BITS(s0), BITS(t0));
		glVertex2i(x - pad, gfx_getHeight() - top);
		float s1 = f32(fmul_m((long double)((col + 1) * 35), texel));
		tc(BITS(s1), BITS(t0));
		int right = x + pad + w;
		glVertex2i(right, gfx_getHeight() - top);
		float t1 = f32(fmul_m((long double)(row * 27 + 0x8b), texel));
		tc(BITS(s1), BITS(t1));
		glVertex2i(right, gfx_getHeight() - top - h);
		tc(BITS(s0), BITS(t1));
		glVertex2i(x - pad, gfx_getHeight() - top - h);
		place = (int)((u32)place * 10);
	}
	if (negative) {
		int left = x - pad, right = x + pad + w;
		tc(0x3f2f0000, 0x3ee00000);   /* (175, 112) / 256 */
		glVertex2i(left, gfx_getHeight() - top);
		tc(0x3f520000, 0x3ee00000);
		glVertex2i(right, gfx_getHeight() - top);
		tc(0x3f520000, 0x3f0b0000);
		glVertex2i(right, gfx_getHeight() - top - h);
		tc(0x3f2f0000, 0x3f0b0000);
		glVertex2i(left, gfx_getHeight() - top - h);
	}
	glEnd();
	return IMPORT(0x4a922c, u32, u32)(GL_TEXTURE_2D);   /* glDisable */
}

/* 0x46bb00: text in the pen font (the HUD's small text: the power-up countdown, the ranking...), printf-style, at
   (x, y) (y down from the top): font 1 the proportional set (14 tall, widths from 0x4c5558), else the fixed one (8 x
   8). A newline goes back to x one line lower, a tab moves 64 right, other characters outside ' ' .. '~' are left
   out. Each glyph's four corners take their texture coordinates from the font's four cell tables (glyph 1 = ' ').
   While it draws, the patch DLL is told (wide.h: penDraw): its vertex hook scales the power-up countdown's glyphs
   about their start, which it used to recognise by return addresses in here. Returns glDisable's eax */
u32 (font_penDraw)(int x, int y, int font, const char *format, ...)
{
	char text[0x400];
	va_list args;
	va_start(args, format);
	vsprintf(text, format, args);
	va_end(args);
	const u8 *topLeft, *bottomLeft, *bottomRight, *topRight;   /* (the tables, from glyph 1) */
	const int *widths;
	int height;
	if (font) {
		topLeft = (const u8 *)0xa0eac0; topRight = (const u8 *)0xa10360; bottomRight = (const u8 *)0xa0ee08;
		bottomLeft = (const u8 *)0xa0f7e0; widths = (const int *)0x4c5558; height = 14;
	} else {
		topLeft = (const u8 *)0xa0f498; topRight = (const u8 *)0xa10018; bottomRight = (const u8 *)0xa0f150;
		bottomLeft = (const u8 *)0xa0fcd0; widths = (const int *)0xa0fb28; height = 8;
	}
	int left = x;
	glEnable(GL_TEXTURE_2D);
	tex_bind(g_textures->managers[GAME_VAR(int, 0xa106ac) / 512], GAME_VAR(int, 0xa106ac) % 512);
	glBegin(GL_QUADS);
	*g_wide->penDraw = 1;
	for (const char *p = text; *p; p++) {
		int c = (signed char)*p;
		if (c == '\n') {
			x = left;
			y += height;
		} else if (c == '\t') {
			x += 0x40;
		} else if (c >= 0x20 && c <= 0x7e) {
			int g = c - 0x20;
			glTexCoord2fv(topLeft + g * 8);
			glVertex2i(x, gfx_getHeight() - y);
			glTexCoord2fv(bottomLeft + g * 8);
			glVertex2i(x, gfx_getHeight() - y - height);
			glTexCoord2fv(bottomRight + g * 8);
			glVertex2i(widths[g] + x, gfx_getHeight() - y - height);
			glTexCoord2fv(topRight + g * 8);
			glVertex2i(widths[g] + x, gfx_getHeight() - y);
			x += widths[g];
		}
	}
	*g_wide->penDraw = 0;
	glEnd();
	return IMPORT(0x4a922c, u32, u32)(GL_TEXTURE_2D);   /* glDisable */
}
