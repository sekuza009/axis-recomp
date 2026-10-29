/* text_codes.c: what a line of text is made of: a Korean (Johab) syllable split into the glyph rows of its three
   parts, and the printable width of a chat line with its colour and format codes left out. */
#include "../game.h"

#define SC(a) ((int)GAME_VAR(signed char, a))

/* 0x4017d0: the two bytes of a Johab syllable (hi, lo; the original rebuilds the word over its first argument): its
   lead consonant, vowel and tail consonant (5 bits each) mapped to glyph indices, and each part's glyph set picked
   by the others (with or without a tail, by the vowel's shape). Returns the tail's glyph */
int (hud_4017d0)(u32 hi, u32 lo)
{
	u32 v = (hi & 0xffff0000u) | (hi & 0xff) << 8 | (lo & 0xff);
	int vowel = SC(0x4ad3e4 + ((v >> 5) & 31)), tail = SC(0x4ad404 + (v & 31)), lead = SC(0x4ad3c4 + ((v >> 10) & 31));
	int tailSet = SC(0x4ad478 + vowel), leadSet, vowelSet;
	if (!tail) {
		leadSet = SC(0x4ad450 + lead);
		vowelSet = SC(0x4ad424 + vowel);
	} else {
		leadSet = SC(0x4ad464 + lead);
		vowelSet = SC(0x4ad43a + vowel);
	}
	GAME_VAR(int, 0x4d60e0) = lead + vowelSet * 20;
	GAME_VAR(int, 0x4d23d4) = vowel + leadSet * 22;
	return GAME_VAR(int, 0x4d23dc) = tail + tailSet * 28;
}

/* 0x402590: the printable characters of a chat line (spaces not counted): outside a match "|x" is a code ("||" a
   '|'), "$[c]" before a character colours it, and in a match or the game room "$#c" too; a double-byte character's
   second byte is skipped */
int (FUN_00402590)(const char *s)
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
   ("||" a "|"; unless 0x76d3e8 is 9999), "$[n]?c" letter c in colour n of the table at 0x9dada0, otherwise the
   default colour (0x76d438); a byte with the top bit set and the next one are skipped (16 pixels). Returns
   glEnd's eax */
u32 (text_ascii5Pass)(int x, int y, const u8 *s)
{
	int left = x;
	glBegin(7);   /* GL_QUADS */
	for (u8 c = *s; c; c = *s) {
		glColor4f_stored((const u32 *)0x76d438);
		s++;
		if (GAME_VAR(int, 0x76d3e8) != 9999 && c == '|') {
			if (*s != '|') {
				y += 10;
				x = left;
				continue;
			}
			s++;
		} else if (c == '$' && s[0] == '[' && s[2] == ']' && s[4]) {
			const u32 *colour = (const u32 *)(0x9dada0 + ((signed char)s[1] - '0') * 16);
			c = s[4];
			s += 5;
			glColor4f_stored(colour);
		}
		if (c & 0x80) {
			s++;
			x += 16;
		} else {
			GAME_CDECL(0x428240, void, int, int, int)(x, y, c);   /* text_quad5 */
			x += 6;
		}
	}
	return IMPORT(0x4a9220, u32, void)();   /* glEnd */
}
