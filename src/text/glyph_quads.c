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
void (glyph_drawHud13)(int x, int y, int i) { glyph_quad(x, y, 0xd, 0xd, i, 0x5b0d10, 0x5b0910, 0x4e0878, 0x4e0474); }
void (glyph_drawHud31)(int x, int y, int i) { glyph_quad(x, y, 0x1f, 0x1f, i, 0x5b0d10, 0x5b0910, 0x4e0878, 0x4e0474); }
/* 0x428030, 0x4280e0, 0x428190, 0x428240: character c (1-based) of the 8, 16, 32 and 5-pixel fonts */
void (text_quad8)(int x, int y, int c) { glyph_quad(x, y, 7, 0xf, c - 1, 0x6807ac, 0x6803ac, 0x67fb64, 0x67ff64); }
void (text_quad16)(int x, int y, int c) { glyph_quad(x, y, 0xf, 0xf, c - 1, 0x9da90c, 0x9da4a8, 0x9db510, 0x9db0b0); }
void (text_quad32)(int x, int y, int c) { glyph_quad(x, y, 0x17, 0x1f, c - 1, 0x9da90c, 0x9da4a8, 0x9db510, 0x9db0b0); }
void (text_quad5)(int x, int y, int c) { glyph_quad(x, y, 7, 7, c - 1, 0x5b1514, 0x5b1114, 0x4e10e8, 0x4e0ce4); }
/* 0x427ce0, 0x427ee0: two layers at once (glyph i from one set, j from another), 13 and 31 units */
void (glyph_drawHud13Layered)(int x, int y, int i, int j)
{
	glyph_quad(x, y, 0xd, 0xd, i, 0x4e1548, 0x4e16d8, 0x5b199c, 0x5b1b64);
	glyph_quad(x, y, 0xd, 0xd, j, 0x4df458, 0x4df638, 0x83a600, 0x83a7e0);
}
void (glyph_drawHud31Layered)(int x, int y, int i, int j)
{
	glyph_quad(x, y, 0x1f, 0x1f, i, 0x4e1548, 0x4e16d8, 0x5b199c, 0x5b1b64);
	glyph_quad(x, y, 0x1f, 0x1f, j, 0x4df458, 0x4df638, 0x83a600, 0x83a7e0);
}
