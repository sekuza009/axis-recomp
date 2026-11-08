/* text_draw.c: drawing a string in one of the four bitmap fonts, plain, centred or centred in lines. A string is
   drawn in up to three passes (text_passes.c), one per font texture: the Hangul initial consonants, the Hangul vowels
   and finals, and ASCII; each pass draws only its own characters. Colour codes "$[c]" inside a string take no room.
   The ASCII pass is a call the patch DLL wraps (nearest-texel sampling), so it is made through the original call site
   (PATCHED_CALL). */
#include "../game.h"
#include <string.h>

/* an ASCII pass through its call site in the game (the patch DLL wraps it there), or in the native build the pass
   itself, pixel-sharp (fixes/screen.c) */
#ifdef AXIS_NATIVE
#include "../fixes/fixes.h"
#define ASCII_PASS(site, fn, x, y, text) fix_asciiPass((void *)FN_##fn, x, y, text)
#else
#define ASCII_PASS(site, fn, x, y, text) SITE_CALL(site, fn, void, int, int, const char *)(x, y, text)
#endif

/* the pass functions: (x, y, text) */

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
	tex_bind(g_textures->banks[id / 512], id % 512);
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

/* the 8-unit font's three passes (also text_drawCentred8's) */
static void text_passes8(int x, int y, const char *text, u32 asciiCallSite)
{
	text_bindFont(g_fontHanCho);
	text_hangul13Pass(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hangul13LayeredPass(x, y, text);
	text_bindFont(g_fontAscii);
	ASCII_PASS(asciiCallSite, text_ascii8Pass, x, y, text);   /* text_ascii8Pass */
}

/* 0x403170: text in the 5-unit font (ASCII only), 6 units per character */
void (text_draw5)(int x, int y, const char *text)
{
	text_begin(6);
	text_bindFont(g_fontAscii);
	ASCII_PASS(0x4031f1, text_ascii5Pass, x, y, text);   /* text_ascii5Pass */
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
	text_hangul13Pass(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hangul13LayeredPass(x, y, text);
	text_bindFont(g_fontAsciiLarge);
	ASCII_PASS(0x4029b0, text_ascii16Pass, x, y, text);   /* text_ascii16Pass */
	glDisable(GL_TEXTURE_2D);
}

/* 0x402c90: text in the 32-unit font, 26 units per character */
void (text_draw32)(int x, int y, const char *text)
{
	text_begin(26);
	text_bindFont(g_fontHanCho);
	text_hangul31Pass(x, y, text);
	text_bindFont(g_fontHanJungJong);
	text_hangul31LayeredPass(x, y, text);
	text_bindFont(g_fontAsciiLarge);
	ASCII_PASS(0x402d90, text_ascii32Pass, x, y, text);   /* text_ascii32Pass */
	glDisable(GL_TEXTURE_2D);
}

/* 0x402740: text in the 8-unit font centred between x0 and x1 (8 units per character) */
void (text_drawCentred8)(int x0, int y, int x1, const char *text)
{
	int x = x0 + (x1 - x0) / 2 - text_visibleLength(text) * 4;
	text_begin(8);
	text_passes8(x, y, text, 0x40288c);
	glDisable(GL_TEXTURE_2D);
}

/* 0x403210 (text_drawCentred5): text in the 5-unit font centred between x0 and x1 (6 units per character) */
void (text_drawCentred5)(int x0, int y, int x1, const char *text)
{
	int x = x0 + (x1 - x0) / 2 - text_visibleLength(text) * 3;
	text_begin(6);
	text_bindFont(g_fontAscii);
	ASCII_PASS(0x4032e6, text_ascii5Pass, x, y, text);   /* text_ascii5Pass */
	glDisable(GL_TEXTURE_2D);
}

/* the printable (non-space) characters of a line (0x402590): with the visible length, the centring correction, in units of 3 */
#define text_printableLength(s) CALL_FN(text_printableLength, int, const char *)(s)

/* text_drawCentredLines16 / text_drawCentredLines32: text centred between x0 and x1, broken into lines at each "|" ("||" is a plain
   "|"; in a match no line breaks), one line under the other */
static void text_drawCentredLines(int x0, int y, int x1, const char *text, int large)
{
	char work[100], line[100], rest[100];
	memset(work, 0, sizeof work);
	strcpy(work, text);
	for (;;) {
		int length = (int)strlen(work), split = 0, i = 0;
		memset(line, 0, sizeof line);
		memset(rest, 0, sizeof rest);
		if (g_screen != 9999) {
			for (i = 0; i < length; i++) {
				if (work[i] != '|')
					continue;
				if (work[i + 1] != '|') {
					split = 1;
					break;
				}
				i++;
			}
		}
		if (split) {
			strncpy(line, work, i);
			strncpy(rest, &work[i + 1], length - i - 1);
			memset(work, 0, sizeof work);
			strcpy(work, rest);
		} else {
			strncpy(line, work, length);
		}
		int centre = x0 + (x1 - x0) / 2;
		int visible = text_visibleLength(line), printable = text_printableLength(line);
		if (!large) {
			text_begin(13);
			int x = centre - visible * 4 - printable * 3;
			text_bindFont(g_fontHanCho);
			text_hangul13Pass(x, y, line);
			text_bindFont(g_fontHanJungJong);
			text_hangul13LayeredPass(x, y, line);
			text_bindFont(g_fontAsciiLarge);
			ASCII_PASS(0x402be8, text_ascii16Pass, x, y, line);   /* text_ascii16Pass */
			y += 0x11;
		} else {
			text_begin(18);
			int x = centre - visible * 8 - printable * 3 + 4;
			text_bindFont(g_fontHanCho);
			text_hangul31Pass(x, y, line);
			text_bindFont(g_fontHanJungJong);
			text_hangul31LayeredPass(x, y, line);
			text_bindFont(g_fontAsciiLarge);
			ASCII_PASS(0x402fbd, text_ascii32Pass, x, y, line);   /* text_ascii32Pass */
			y += 0x21;
		}
		glDisable(GL_TEXTURE_2D);
		if (!split)
			return;
	}
}

/* 0x4029d0: text in the 16-unit font centred between x0 and x1, in lines (13 units per character, 0x11 apart) */
void (text_drawCentredLines16)(int x0, int y, int x1, const char *text)
{
	text_drawCentredLines(x0, y, x1, text, 0);
}

/* 0x402db0: the same in the 32-unit font (18 units per character, 0x21 apart) */
void (text_drawCentredLines32)(int x0, int y, int x1, const char *text)
{
	text_drawCentredLines(x0, y, x1, text, 1);
}
