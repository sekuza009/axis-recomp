/* settings_form.c: the game settings form, as the game room shows it (and, for a new arena, the arena screen):
   the window, a title and a line, the labels down the left and each value in its box, the value under the pointer
   drawn again with a shadow in yellow, the buttons, the map preview with its arrows and the custom rules button. */
#include "../game.h"
#include <string.h>

/* a value's box at (x0, y0) .. (x1, y1): black at 0.4, a cyan border at 0.5 */
static void field_box(int x0, int y0, int x1, int y1)
{
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3ecccccd);
	menu_drawRect(x0, y0, x1, y1, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f000000);
	menu_drawRect(x0, y0, x1, y1, 0);
}

/* the hovered value drawn again: its shadow at (x, y), then in yellow one up and left */
static void hover_text(int x, int y, const char *text)
{
	set_colour_bits((Colour *)0x76d438, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01 */
	text_draw8(x, y, text);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);            /* 1, 0.8, 0, 1 */
	text_draw8(x - 1, y - 1, text);
}

/* a password shown as stars (20 bytes, cleared first) */
static void stars(char *out, const char *password)
{
	memset(out, 0, 20);
	int n = (int)strlen(password);
	if (n > 0)
		memset(out, '*', n);
}

static void white(void)
{
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
}

static void bind_buttons(void)
{
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
}

/* 0x43bfe0: the game room's settings form (0x9dd1b8 .. 0x9dd1c4): the title 0x75a424, a cyan line, the labels
   (0x75a4a4, 0x80 apart) and the values in their boxes: the game's name (0x4df9c8) and its password as stars
   (0x4df9ee; each hidden while it is edited, 0x9dd380 / 0x9dd6a8), the map (0x4df9e8, its name from 0x5ae9d0, 0x50
   apart; CUSTOM, set lower, with custom rules 0x4df9ea), the players (0x4df9e9), the text 0x74e6a4, the mode
   (0x4df9eb, a name from 0x7669a4) and the two limits (the bytes 0x4df9ec / 0x4df9ed, hidden while edited: 0x9dd388
   / 0x9dd568). Unless a field is being edited (0x68039c) or the "leave?" box is up (0x907b2c), the value under the
   pointer (room_432380: 0 .. 7; not the custom map) drawn again in yellow. Two buttons (0x75a8a4, lit from 8 unless
   editing), the map preview (room_drawCustomOption), its arrows (11 / 12) and the custom rules button (0x75d8a4,
   13, not while the map list is up, 0x4db508); the border. The caller ignores the eax it leaves */
void (room_drawGameSettings)(void)
{
#define X0 GAME_VAR(int, 0x9dd1b8)
#define Y0 GAME_VAR(int, 0x9dd1bc)
#define X1 GAME_VAR(int, 0x9dd1c0)
#define Y1 GAME_VAR(int, 0x9dd1c4)
	const u32 *bright = (const u32 *)0x9dcec0, *dim = (const u32 *)0x9dd338;
	int editing = GAME_VAR(int, 0x68039c), leaving = GAME_VAR(int, 0x907b2c);
	int custom = GAME_VAR(char, 0x4df9ea) != 0;
	const char *map = (const char *)(0x5ae9d0 + GAME_VAR(signed char, 0x4df9e8) * 0x50);
	const char *mode = (const char *)(0x7669a4 + GAME_VAR(signed char, 0x4df9eb) * 0x80);
	char text[20];
	int hovered = room_432380(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)0x75a424);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	for (int k = 0; k < 8; k++)   /* (the original would grey labels past the eighth: there are none) */
		text_draw8(X0 + 0x40, Y0 + 0x32 + k * 0x22, (const char *)(0x75a4a4 + k * 0x80));

	field_box(X0 + 0x9f, Y0 + 0x2f, X0 + 0x1a7, Y0 + 0x45);
	white();
	if (!GAME_VAR(int, 0x9dd380))
		text_draw8(X0 + 0xa4, Y0 + 0x32, (const char *)0x4df9c8);
	field_box(X0 + 0x9f, Y0 + 0x51, X0 + 0xef, Y0 + 0x67);
	if (!GAME_VAR(int, 0x9dd6a8)) {
		stars(text, (const char *)0x4df9ee);
		text_draw8(X0 + 0xa4, Y0 + 0x54, text);
	}
	field_box(X0 + 0x9f, Y0 + 0x6d, X0 + 0x18f, Y0 + 0x91);
	if (custom)
		text_draw8(X0 + 0xa4, Y0 + 0x76, (const char *)0x4ad56c);   /* CUSTOM */
	else
		text_draw8(X0 + 0xa4, Y0 + 0x6f, map);
	field_box(X0 + 0x9f, Y0 + 0x95, X0 + 0xef, Y0 + 0xab);
	itoa(GAME_VAR(signed char, 0x4df9e9), text, 10);
	text_draw8(X0 + 0xa4, Y0 + 0x98, text);
	field_box(X0 + 0x9f, Y0 + 0xb7, X0 + 0xef, Y0 + 0xcd);
	white();
	text_draw8(X0 + 0xa4, Y0 + 0xba, (const char *)0x74e6a4);
	field_box(X0 + 0x9f, Y0 + 0xd9, X0 + 0x18f, Y0 + 0xef);
	white();
	text_draw8(X0 + 0xa4, Y0 + 0xdc, mode);
	field_box(X0 + 0x9f, Y0 + 0xfb, X0 + 0xef, Y0 + 0x111);
	white();
	if (!GAME_VAR(int, 0x9dd388)) {
		itoa(GAME_VAR(u8, 0x4df9ec), text, 10);
		text_draw8(X0 + 0xa4, Y0 + 0xfe, text);
	}
	field_box(X0 + 0x9f, Y0 + 0x11d, X0 + 0xef, Y0 + 0x133);
	if (!GAME_VAR(int, 0x9dd568)) {
		itoa(GAME_VAR(u8, 0x4df9ed), text, 10);
		text_draw8(X0 + 0xa4, Y0 + 0x120, text);
	}

	if (!editing && !leaving)
		switch (hovered) {
		case 0:
			hover_text(X0 + 0xa4, Y0 + 0x32, (const char *)0x4df9c8);
			break;
		case 1:
			stars(text, (const char *)0x4df9ee);
			hover_text(X0 + 0xa4, Y0 + 0x54, text);
			break;
		case 2:
			if (!custom)
				hover_text(X0 + 0xa4, Y0 + 0x6f, map);
			break;
		case 3:
			itoa(GAME_VAR(signed char, 0x4df9e9), text, 10);
			hover_text(X0 + 0xa4, Y0 + 0x98, text);
			break;
		case 5:
			hover_text(X0 + 0xa4, Y0 + 0xdc, mode);
			break;
		case 6:
			itoa(GAME_VAR(u8, 0x4df9ec), text, 10);
			hover_text(X0 + 0xa4, Y0 + 0xfe, text);
			break;
		case 7:
			itoa(GAME_VAR(u8, 0x4df9ed), text, 10);
			hover_text(X0 + 0xa4, Y0 + 0x120, text);
			break;
		}

	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		bind_buttons();
		int lit = hovered == k + 8 && !editing;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + k * 0xc8;
		menu_drawTexQuad_4282f0(bx + 0x64, Y1 - 0x40, bx + 0x104, Y1 - 0x20, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(bx + 0x64, Y1 - 0x38, bx + 0x104, (const char *)(0x75a8a4 + k * 0x80));
	}
	room_drawCustomOption(GAME_VAR(signed char, 0x4df9e8));
	bind_buttons();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int arrows = !editing && !leaving;
	menu_drawTexQuad_4284d0(X1 - 0x8c, Y0 + 0xd7, X1 - 0x5c, Y0 + 0xef, hovered == 11 && arrows);
	menu_drawTexQuad_4285c0(X1 - 0x50, Y0 + 0xd7, X1 - 0x20, Y0 + 0xef, hovered == 12 && arrows);
	glEnable(GL_TEXTURE_2D);
	bind_buttons();
	if (hovered == 13 && !editing && !GAME_VAR(int, 0x4db508)) {
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		white();
	} else {
		glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
		set_colour_bits((Colour *)0x76d438, 0x3e99999a, 0x3f333333, 0x3f333333, 0x3f800000);   /* 0.3, 0.7, 0.7, 1 */
	}
	menu_drawTexQuad_4282f0(X1 - 0x96, Y0 + 0xf5, X1 - 0x16, Y0 + 0x111, 1);
	text_drawBox16(X1 - 0x96, Y0 + 0xfb, X1 - 0x16, (const char *)0x75d8a4);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}
