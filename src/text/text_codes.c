/* text_codes.c: what a line of text is made of: a Korean (Johab) syllable split into the glyph rows of its three
   parts, and the printable width of a chat line with its colour and format codes left out. */
#include "../game.h"

#define SC(a) ((int)GAME_VAR(signed char, a))

/* 0x4017d0: the two bytes of a Johab syllable (hi, lo; the original rebuilds the word over its first argument): its
   lead consonant, vowel and tail consonant (5 bits each) mapped to glyph indices, and each part's glyph set picked
   by the others (with or without a tail, by the vowel's shape). Returns the tail's glyph */
int (hangul_glyphs)(u32 hi, u32 lo)
{
	u32 v = (hi & 0xffff0000u) | (hi & 0xff) << 8 | (lo & 0xff);
	int vowel = SC(OBJ(g_hangulVowelIndex) + ((v >> 5) & 31)), tail = SC(OBJ(g_hangulTailIndex) + (v & 31)), lead = SC(OBJ(g_hangulLeadIndex) + ((v >> 10) & 31));
	int tailSet = SC(OBJ(g_hangulTailSet) + vowel), leadSet, vowelSet;
	if (!tail) {
		leadSet = SC(OBJ(g_hangulLeadSetPlain) + lead);
		vowelSet = SC(OBJ(g_hangulVowelSetPlain) + vowel);
	} else {
		leadSet = SC(OBJ(g_hangulLeadSetTail) + lead);
		vowelSet = SC(OBJ(g_hangulVowelSetTail) + vowel);
	}
	g_hangulLeadGlyph = lead + vowelSet * 20;
	g_hangulVowelGlyph = vowel + leadSet * 22;
	return g_hangulTailGlyph = tail + tailSet * 28;
}

/* 0x402590: the printable characters of a line of text (spaces not counted): outside a match "|x" is a code ("||" a
   '|'), "$[c]" before a character colours it, and in a match or the lobby (screens 9999 / 400) "$#c" too; a
   double-byte character is not counted (its second byte skipped). Used to centre box text (text_drawBox16 / 32) */
int (text_printableLength)(const char *s)
{
	int n = 0, state = g_menuState;
	char c = *s;
	if (!c)
		return 0;
	const char *p = s;
	do {
		p++;
		if (state != 9999 && c == '|') {
			if (*p != '|') {
				p++;
				goto next;
			}
			c = '|';
			p++;
		} else if (c == '$' && p[0] == '[' && p[2] == ']' && p[4]) {
			c = p[4];
			p += 5;
		}
		if ((state == 9999 || state == 400) && c == '$' && p[0] == '#' && p[2]) {
			c = p[2];
			p += 3;
		}
		if (c & 0x80) {
			p++;
			goto next;
		}
		if (c != ' ')
			n++;
	next:
		c = *p;
	} while (c);
	return n;
}

/* 0x403060: text drawn with the 5-pixel font as quads from (x, y), 6 pixels a letter: "|" a new line 10 pixels down
   ("||" a "|"; unless g_screen is 9999), "$[n]?c" letter c in colour n of the table at g_codeColours, otherwise the
   default colour (g_textColour); a byte with the top bit set and the next one are skipped (16 pixels). Returns
   glEnd's eax */
u32 (text_ascii5Pass)(int x, int y, const u8 *s)
{
	int left = x;
	glBegin(7);   /* GL_QUADS */
	for (u8 c = *s; c; c = *s) {
		glColor4f_stored((const u32 *)OBJ(g_textColour));
		s++;
		if (g_menuState != 9999 && c == '|') {
			if (*s != '|') {
				y += 10;
				x = left;
				continue;
			}
			s++;
		} else if (c == '$' && s[0] == '[' && s[2] == ']' && s[4]) {
			const u32 *colour = (const u32 *)(OBJ(g_codeColours) + ((signed char)s[1] - '0') * 16);
			c = s[4];
			s += 5;
			glColor4f_stored(colour);
		}
		if (c & 0x80) {
			s++;
			x += 16;
		} else {
			text_quad5(x, y, c);   /* text_quad5 */
			x += 6;
		}
	}
	return IMPORT(0x4a9220, u32, void)();   /* glEnd */
}

/* ---- the larger text passes, one quad per character (colour g_textColour): "|" breaks the line outside the console
   (screen 9999; "||" is a '|'), as does "\r\n"; "$[c]" colours the next character with colour c (16 bytes a slot
   at g_codeColours); the 13-unit passes also take "$#c" in a match or the game room (screens 9999 / 400): colour c
   kept for the rest of the text, a later "$[c]" changing it. Lines are `line` apart, wrap at x g_textWrapX and stop
   at y g_textBottom. The ASCII passes draw the single-byte characters (a double-byte one is skipped, `wide` across),
   then keep where they ended (g_textEndX / g_textEndY; g_textHitBottom set when stopped). The Korean passes draw only the
   double-byte syllables, each split by hangul_glyphs (after the conversion text_hangulConvert when g_convertHangul is 1): the lead
   glyph alone (g_hangulLeadGlyph) or the vowel and tail glyphs as two layers (g_hangulVowelGlyph / g_hangulTailGlyph); other characters move
   `space` for a space, else g_textCharWidth. Returns glEnd's eax, or glDisable's for the passes that end texturing ---- */
typedef struct {
	int line, wide;
	int sticky;                  /* "$#c" understood */
	u32 glyph;                   /* the quad: (x, y, c), or (x, y, i[, j]) for Korean */
	int korean, layered;
	int space, narrow, other;    /* the ASCII advance for ' ', for 'I' / 'i', for the rest (Korean: space only) */
	int untexture;               /* glDisable(GL_TEXTURE_2D) after */
} TextPass;

static u32 text_pass(int x, int y, const u8 *s, const TextPass *pass)
{
	int left = x, kept = 0, colour = 0;
	glBegin(7);   /* GL_QUADS */
	for (u8 c = *s; c; c = *s) {
		int screen = g_menuState, special = pass->sticky && (screen == 9999 || screen == 400);
		s++;
		if (special && c == '$' && s[0] == '#' && s[2]) {
			colour = (signed char)s[1] - '0';
			kept = 1;
			c = s[2];
			s += 3;
		}
		glColor4f_stored(special && kept ? (const u32 *)(OBJ(g_codeColours) + colour * 16) : (const u32 *)OBJ(g_textColour));
		if (g_menuState != 9999 && c == '|') {
			if (*s != '|') {
				y += pass->line;
				x = left;
				continue;
			}
			s++;
		} else if (c == '$' && s[0] == '[' && s[2] == ']' && s[4]) {
			int code = (signed char)s[1] - '0';
			if (pass->sticky)
				colour = code;
			c = s[4];
			s += 5;
			glColor4f_stored((const u32 *)(OBJ(g_codeColours) + code * 16));
		}
		if (c == '\r' && *s == '\n') {
			s++;
			y += pass->line;
			x = left;
			continue;
		}
		if (x >= g_textWrapX) {
			x = left;
			y += pass->line;
		}
		if (y >= g_textBottom) {
			if (!pass->korean)
				g_textHitBottom = 1;
			break;
		}
		if (!pass->korean) {
			if (c & 0x80) {
				s++;
				x += pass->wide;
				continue;
			}
			GAME_CDECL(pass->glyph, void, int, int, int)(x, y, c);
			x += c == ' ' ? pass->space : c == 'I' || c == 'i' ? pass->narrow : pass->other;
			continue;
		}
		if (!(c & 0x80)) {
			x += c == ' ' ? pass->space : g_textCharWidth;
			continue;
		}
		u8 hi = c, lo = *s++;
		if (g_convertHangul == 1) {
			u32 code = text_hangulConvert((u32)hi << 8 | lo);
			hi = (u8)(code >> 8);
			lo = (u8)code;
		}
		hangul_glyphs(hi, lo);   /* hangul_glyphs */
		if (pass->layered)
			GAME_CDECL(pass->glyph, void, int, int, int, int)(x, y, g_hangulVowelGlyph, g_hangulTailGlyph);
		else
			GAME_CDECL(pass->glyph, void, int, int, int)(x, y, g_hangulLeadGlyph);
		x += pass->wide;
	}
	if (!pass->korean) {
		g_textEndX = x;
		g_textEndY = y;
	}
	u32 r = IMPORT(0x4a9220, u32, void)();   /* glEnd */
	return pass->untexture ? IMPORT(0x4a922c, u32, u32)(0xde1) : r;   /* glDisable(GL_TEXTURE_2D) */
}

/*                              line  wide  sticky glyph     korean layered space narrow other untexture */
static const TextPass ascii8 =  { 0x11, 0x10, 1, FN_ADDR(text_quad8, 0x428030), 0, 0, 8,    8,    8,    0 };
static const TextPass ascii16 = { 0x11, 0x10, 1, FN_ADDR(text_quad16, 0x4280e0), 0, 0, 8,    0xb,  0xd,  1 };
static const TextPass ascii32 = { 0x21, 0x20, 0, FN_ADDR(text_quad32, 0x428190), 0, 0, 0x10, 0x10, 0x16, 1 };
static const TextPass han13 =   { 0x11, 0x10, 1, FN_ADDR(glyph_drawHangulLead13, 0x427c30), 1, 0, 8,    0,    0,    0 };
static const TextPass han13b =  { 0x11, 0x10, 1, FN_ADDR(glyph_drawHangulVowelTail13, 0x427ce0), 1, 1, 8,    0,    0,    0 };
static const TextPass han31 =   { 0x21, 0x20, 0, FN_ADDR(glyph_drawHangulLead31, 0x427e30), 1, 0, 0x10, 0,    0,    0 };
static const TextPass han31b =  { 0x21, 0x20, 0, FN_ADDR(glyph_drawHangulVowelTail31, 0x427ee0), 1, 1, 0x10, 0,    0,    0 };

/* 0x402010, 0x402210, 0x402420: the 8, 16 and 32-pixel fonts (0x402010 also notes where it starts first, which the
   end overwrites) */
u32 (text_ascii8Pass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &ascii8); }
u32 (text_ascii16Pass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &ascii16); }
u32 (text_ascii32Pass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &ascii32); }
/* 0x401870, 0x401aa0: Korean at 13 units, the lead glyphs and the vowel and tail glyphs; text_hangul31Pass, text_hangul31LayeredPass: the
   same at 31 units */
u32 (text_hangul13Pass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &han13); }
u32 (text_hangul13LayeredPass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &han13b); }
u32 (text_hangul31Pass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &han31); }
u32 (text_hangul31LayeredPass)(int x, int y, const u8 *s) { return text_pass(x, y, s, &han31b); }

/* a pair of KS X 1001 rows (first, first + 1, ...) to a Johab lead byte (from base) and trail byte */
static int ks_row(int hi, int lo, int base, int first)
{
	int r = hi - first;
	u8 b = (u8)lo;
	if (!(r % 2)) {
		b = (u8)(lo - 0x70);
		if (b > 0x7e)
			b += 0x12;
	}
	return (r / 2 + base) * 256 + b;
}

/* 0x44aac0: one EUC-KR (KS X 1001) character to Johab, 0 for none: the jamo row (0xa4) by g_ksJamoCodes
   (its codes g_ksJamoJohab; the upper half of EAX is left at 0x004b, and a miss gives 0x4b8761), the symbol rows in
   pairs, the syllables (0xb0 .. 0xc8) by g_ksSyllableJohab, the hanja rows in pairs */
int (text_hangulConvert)(u32 code)
{
	int hi = (code >> 8) & 0xff, lo = code & 0xff;
	if (hi == 0xa4) {
		for (int k = 0; k < 39; k++)
			if ((u16)code == GAME_VAR(u16, OBJ(g_ksJamoCodes) + k * 2))
				return (OBJ(g_unlockTablesNet) + 0x1430) | GAME_VAR(u16, OBJ(g_ksJamoJohab) + k * 2);
		return IMG(0x4b8761);
	}
	int ok = lo >= 0xa1 && lo <= 0xfe;
	if (hi >= 0xa1 && hi <= 0xac)
		return ok ? ks_row(hi, lo, 0xd9, 0xa1) : 0;
	if (hi == 0xad)
		return ok ? (u8)(lo - 0x21) + 0xd400 : 0;
	if (hi == 0xae)
		return lo >= 0xa1 && lo <= 0xc1 ? (u8)(lo + 0x3d) + 0xd400 : 0;
	if (hi >= 0xb0 && hi <= 0xc8)
		return ok ? GAME_VAR(u16, OBJ(g_ksSyllableJohab) - (0xb0 * 94 + 0xa1) * 2 + (lo + hi * 94) * 2) : 0;
	if (hi >= 0xca && hi <= 0xfd)
		return ok ? ks_row(hi, lo, 0xe0, 0xca) : 0;
	return 0;
}
