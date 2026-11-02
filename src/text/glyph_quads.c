/* glyph_quads.c: one character of a bitmap font as a textured quad in menu units: corners from (x, y), size w x h,
   texture coordinates from the font's four tables (left, top, right, bottom per glyph; floats passed as their bits).
   These sit between the text passes and the patch DLL's vertex hook, which identifies HUD text by its call sites on
   the stack, so they stay small, one level deep. */
#include "../game.h"

#define glTexCoord2f_bits(s, t) IMPORT(0x4a920c, void, u32, u32)(s, t)

static void glyph_quad(int x, int y, int w, int h, int i, u32 u0, u32 v0, u32 u1, u32 v1)
{
	const u32 *L = (const u32 *)RELOC(u0), *T = (const u32 *)RELOC(v0), *R = (const u32 *)RELOC(u1), *B = (const u32 *)RELOC(v1);
	glTexCoord2f_bits(L[i], T[i]);
	menu_vertex(x, y);
	glTexCoord2f_bits(R[i], T[i]);
	menu_vertex(x + w, y);
	glTexCoord2f_bits(R[i], B[i]);
	menu_vertex(x + w, y + h);
	glTexCoord2f_bits(L[i], B[i]);
	menu_vertex(x, y + h);
}

/* 0x427c30, 0x427e30: HUD glyph i, 13 and 31 units */
void (glyph_drawHud13)(int x, int y, int i) { glyph_quad(x, y, 0xd, 0xd, i, OBJ(g_hudFontLeft), OBJ(g_hudFontTop), OBJ(g_hudFontRight), OBJ(g_hudFontBottom)); }
void (glyph_drawHud31)(int x, int y, int i) { glyph_quad(x, y, 0x1f, 0x1f, i, OBJ(g_hudFontLeft), OBJ(g_hudFontTop), OBJ(g_hudFontRight), OBJ(g_hudFontBottom)); }
/* 0x428030, 0x4280e0, 0x428190, 0x428240: character c (1-based) of the 8, 16, 32 and 5-pixel fonts */
void (text_quad8)(int x, int y, int c) { glyph_quad(x, y, 7, 0xf, c - 1, OBJ(g_font8Left), OBJ(g_font8Top), OBJ(g_font8Right), OBJ(g_font8Bottom)); }
void (text_quad16)(int x, int y, int c) { glyph_quad(x, y, 0xf, 0xf, c - 1, OBJ(g_font16Left), OBJ(g_font16Top), OBJ(g_font16Right), OBJ(g_font16Bottom)); }
void (text_quad32)(int x, int y, int c) { glyph_quad(x, y, 0x17, 0x1f, c - 1, OBJ(g_font16Left), OBJ(g_font16Top), OBJ(g_font16Right), OBJ(g_font16Bottom)); }
void (text_quad5)(int x, int y, int c) { glyph_quad(x, y, 7, 7, c - 1, OBJ(g_font5Left), OBJ(g_font5Top), OBJ(g_font5Right), OBJ(g_font5Bottom)); }
/* 0x427ce0, 0x427ee0: two layers at once (glyph i from one set, j from another), 13 and 31 units */
void (glyph_drawHud13Layered)(int x, int y, int i, int j)
{
	glyph_quad(x, y, 0xd, 0xd, i, OBJ(g_hudLayerALeft), OBJ(g_hudLayerATop), OBJ(g_hudLayerARight), OBJ(g_hudLayerABottom));
	glyph_quad(x, y, 0xd, 0xd, j, OBJ(g_hudLayerBLeft), OBJ(g_hudLayerBTop), OBJ(g_hudLayerBRight), OBJ(g_hudLayerBBottom));
}
void (glyph_drawHud31Layered)(int x, int y, int i, int j)
{
	glyph_quad(x, y, 0x1f, 0x1f, i, OBJ(g_hudLayerALeft), OBJ(g_hudLayerATop), OBJ(g_hudLayerARight), OBJ(g_hudLayerABottom));
	glyph_quad(x, y, 0x1f, 0x1f, j, OBJ(g_hudLayerBLeft), OBJ(g_hudLayerBTop), OBJ(g_hudLayerBRight), OBJ(g_hudLayerBBottom));
}
