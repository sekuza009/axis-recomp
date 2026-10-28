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
void (app_42f940)(void)
{
	static const Grid grids[3] = {
		{ 0, 16, 0x80, 0, 15, 16, 16, 0, 15, 0x9db0b0, 0x9da4a8, 0x9da90c, 0x9db510 },
		{ 0, 16, 0x80, 0, 15, 32, 8, 1, 8, 0x67ff64, 0x6803ac, 0x6807ac, 0x67fb64 },
		{ 0x87, 8, 0xa7, -7, 0, 32, 8, 1, 8, 0x4e0ce4, 0x5b1114, 0x5b1514, 0x4e10e8 } };
	for (int k = 0; k < 3; k++)
		glyph_grid(&grids[k]);
}

/* 0x42fb40: the HUD fonts' */
void (hud_42fb40)(void)
{
	static const Grid grids[3] = {
		{ 0, 16, 0x100, 0, 15, 16, 16, 0, 15, 0x4e0474, 0x5b0910, 0x5b0d10, 0x4e0878 },
		{ 0, 16, 0x60, 0, 15, 16, 16, 0, 15, 0x5b1b64, 0x4e16d8, 0x4e1548, 0x5b199c },
		{ 0x6f, 16, 0xdf, -15, 0, 16, 16, 0, 15, 0x83a7e0, 0x4df638, 0x4df458, 0x83a600 } };
	for (int k = 0; k < 3; k++)
		glyph_grid(&grids[k]);
}
