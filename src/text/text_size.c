/* text_size.c: text by font size. The game has four bitmap fonts (5, 8, 16 and 32 units high), each with a plain
   pass and a pass that centres the text in a box; these pick the pass from a size. */
#include "../game.h"

/* 0x44ad60: draw text at (x, y) in the font of the given size; other sizes draw nothing */
void (text_drawSized)(int x, int y, const char *text, int size)
{
	switch (size) {
	case 5: text_draw5(x, y, text); break;
	case 8: text_draw8(x, y, text); break;
	case 16: text_draw16(x, y, text); break;
	case 32: text_draw32(x, y, text); break;
	}
}

/* 0x44ae10 (text_drawCentred): draw text centred between x0 and x1 at y in the font of the given size */
void (text_drawCentred)(int x0, int y, int x1, const char *text, int size)
{
	switch (size) {
	case 5: text_drawCentred5(x0, y, x1, text); break;
	case 8: text_draw8b(x0, y, x1, text); break;
	case 16: text_drawBox16(x0, y, x1, text); break;
	case 32: text_drawCentred32(x0, y, x1, text); break;
	}
}
