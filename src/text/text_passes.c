/* text_passes.c: drawing a string in one of the four bitmap fonts. A string is drawn in up to three passes, one per
   font texture: the Hangul initial consonants, the Hangul vowels and finals, and ASCII; each pass draws only its
   own characters. Colour codes "$[c]" inside a string take no room. The ASCII pass is a call the patch DLL wraps
   (nearest-texel sampling), so it is made through the original call site (PATCHED_CALL). */
#include "../game.h"
#include <string.h>

/* the pass functions: (x, y, text) */
#define text_hanCho(x, y, s) GAME_CDECL(0x401870, void, int, int, const char *)(x, y, s)
#define text_hanJungJong(x, y, s) GAME_CDECL(0x401aa0, void, int, int, const char *)(x, y, s)
#define text_hanCho32(x, y, s) GAME_CDECL(0x401ce0, void, int, int, const char *)(x, y, s)
#define text_hanJungJong32(x, y, s) GAME_CDECL(0x401e70, void, int, int, const char *)(x, y, s)

/* every pass: the character width set, the 2D projection, texturing on, the current text colour */
static void text_begin(int charWidth)
{
	g_textCharWidth = charWidth;
	gfx_setProjection2D3D(2);
	glEnable(GL_TEXTURE_2D);
	glColor4f_stored(g_textColour);
}
/* a font texture by its id: manager id / 512 of the texture set, slot id % 512 */
static void text_bindFont(int id)
{
	tex_bind(g_textures->managers[id / 512], id % 512);
}
/* the room a string takes, in characters: its length less five for each colour code */
static int text_visibleLength(const char *text)
{
	int length = (int)strlen(text), codes = 0;
	for (int i = 0; i < length; i++)
		if (text[i] == '$' && text[i + 1] == '[' && text[i + 3] == ']' && text[i + 5] != 0)
			codes++;
	return length - codes * 5;
}

/* the 8-unit font's three passes (also text_draw8b's) */
static void text_passes8(int x, int y, const char *text, u32 asciiCallSite)
{
	text_bindFont(g_fontHanCho);
	text_hanCho(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hanJungJong(x, y, text);
	text_bindFont(g_fontAscii);
	PATCHED_CALL(asciiCallSite, void, int, int, const char *)(x, y, text);   /* text_ascii8Pass */
}

/* 0x403170: text in the 5-unit font (ASCII only), 6 units per character */
void (text_draw5)(int x, int y, const char *text)
{
	text_begin(6);
	text_bindFont(g_fontAscii);
	PATCHED_CALL(0x4031f1, void, int, int, const char *)(x, y, text);   /* text_ascii5Pass */
	glDisable(GL_TEXTURE_2D);
}

/* 0x402620: text in the 8-unit font */
void (text_draw8)(int x, int y, const char *text)
{
	text_begin(8);
	text_passes8(x, y, text, 0x402720);
	glDisable(GL_TEXTURE_2D);
}

/* 0x4028b0: text in the 16-unit font, 13 units per character */
void (text_draw16)(int x, int y, const char *text)
{
	text_begin(13);
	text_bindFont(g_fontHanCho);
	text_hanCho(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hanJungJong(x, y, text);
	text_bindFont(g_fontAsciiLarge);
	PATCHED_CALL(0x4029b0, void, int, int, const char *)(x, y, text);   /* text_ascii16Pass */
	glDisable(GL_TEXTURE_2D);
}

/* 0x402c90: text in the 32-unit font, 26 units per character */
void (text_draw32)(int x, int y, const char *text)
{
	text_begin(26);
	text_bindFont(g_fontHanCho);
	text_hanCho32(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hanJungJong32(x, y, text);
	text_bindFont(g_fontAsciiLarge);
	PATCHED_CALL(0x402d90, void, int, int, const char *)(x, y, text);   /* text_ascii32Pass */
	glDisable(GL_TEXTURE_2D);
}

/* 0x402740: text in the 8-unit font centred between x0 and x1 (8 units per character) */
void (text_draw8b)(int x0, int y, int x1, const char *text)
{
	int x = x0 + (x1 - x0) / 2 - text_visibleLength(text) * 4;
	text_begin(8);
	text_passes8(x, y, text, 0x40288c);
	glDisable(GL_TEXTURE_2D);
}

/* 0x403210 (hud_403210): text in the 5-unit font centred between x0 and x1 (6 units per character) */
void (hud_403210)(int x0, int y, int x1, const char *text)
{
	int x = x0 + (x1 - x0) / 2 - text_visibleLength(text) * 3;
	text_begin(6);
	text_bindFont(g_fontAscii);
	PATCHED_CALL(0x4032e6, void, int, int, const char *)(x, y, text);   /* text_ascii5Pass */
	glDisable(GL_TEXTURE_2D);
}
