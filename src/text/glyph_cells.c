/* glyph_cells.c: the font atlases' cell tables: for each glyph its texture coordinates, a row's top and bottom
   (the same across the row) and a column's left and right. Every value is a texel number times the constant at
   0x4a957c (1/256). */
#include "../game.h"

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
