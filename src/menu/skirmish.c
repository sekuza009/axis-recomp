/* skirmish.c: the skirmish screen: its list's keys and the briefing typed out one character at a time. */
#include "../game.h"
#include <string.h>
#include "key_repeat.h"

static void list_up(void) { skirmish_cursorUp(); }
static void list_down(void) { skirmish_cursorDown(); }

/* 0x443f20: the skirmish list's keys: 0x4e0cd4 or fire reads the chosen mission's block (mission_saveAxisMis), back
   or cancel leaves, up / down move the cursor with a key repeat (the original leaves eax to callers that ignore it) */
void (skirmish_processKeys)(void)
{
	if (input_justPressed(g_dikA) == 1 || input_justPressed(g_keyClick) == 1) {
		mission_saveAxisMis(g_missionPicked);
		return;
	}
	if (input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel2) == 1) {
		skirmishSettings_leave();
		return;
	}
	if (!key_repeat(g_keyUp, &g_repeatUp, list_up))
		key_repeat(g_keyDown, &g_repeatDown, list_down);
}

/* ---- the briefing: the text block 0x9ef1ec (read by mission_saveAxisMis), from offset 0x9eeba4 up to 0x9ef200;
   0x9ef1f4 characters of it shown so far, copied to 0x9f1064 ---- */
#define g_briefingText ((char *)IMG(0x9f1064))

/* 0x445520: the briefing typed out: while not done or skipped, every 1.4 of the clock (frame times added) shows one
   more character (a CR LF or a double-byte character at once); drawn in the briefing window (wrapping at 0x23e,
   bottom 0x76), with a cursor bar (half bright on its left) at its end while still typing */
void (briefing_typeOut)(void)
{
	u8 *text = g_briefingSource;
	if (!text)
		return;
	if (!g_briefingDone && !g_briefingSkipped) {
		long double clock = fadd_m(fld_m(&g_frameTime), &g_briefingClock);
		g_briefingClock = clock;
		if (clock > k_1_4) {
			int n = ++g_briefingShown;
			int start = g_briefingStart;
			if (text[start + n] == '\r' && text[start + n + 1] == '\n')
				g_briefingShown = ++n;
			if (text[start + n] & 0x80)
				g_briefingShown = ++n;
			g_briefingClock = 0;
			memcpy(g_briefingText, text + start, n + 1);
			if (start + n >= g_briefingEnd)
				g_briefingDone = 1;
		}
	}
	text_setWrapX(0x23e);
	text_setBottom(0x76);
	text_draw8(g_briefingX + 0x20, g_briefingY + 0x40, g_briefingText);
	if (!g_briefingDone && !g_briefingSkipped) {
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(g_textEndX, g_textEndY - 1, g_textEndX + 8, g_textEndY + 0x11, 1);
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f000000);
		menu_drawRect(g_textEndX - 8, g_textEndY - 1, g_textEndX, g_textEndY + 0x11, 1);
	}
	text_setWrapX(0x280);
	text_setBottom(0x1e0);
}

/* ---- the briefing window (0x9f16a8 .. 0x9f16b4) ---- */
#define BX0 GAME_VAR(int, 0x9f16a8)
#define BY0 GAME_VAR(int, 0x9f16ac)
#define BX1 g_briefingRight
#define BY1 g_briefingBottom
#define g_panelColour ((const u32 *)IMG(0x9ef208))
#define g_dimColour ((const u32 *)IMG(0x9eeac8))

/* one of the window's buttons (x0 .. x1 along its bottom): the textured quad, lit when lit, then its label in
   colour (none: grey, the button greyed) */
static void briefing_button(int x0, int x1, int lit, const u32 *colour, const char *label)
{
	static const u32 grey[4] = { 0x3f19999a, 0x3f19999a, 0x3f19999a, 0x3f800000 };   /* 0.6, 0.6, 0.6, 1 */
	if (!colour)
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	menu_drawWideButton(x0, BY1 - 0x30, x1, BY1 - 0x10, lit);
	if (!colour)
		colour = grey;
	set_colour_bits((Colour *)IMG(0x76d438), colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(x0, BY1 - 0x28, x1, label);
}

static void bind_button_texture(void)
{
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/* ---- the mission list: 0xfc-byte records from 0x9ef2d4 (count 0x9ef2c0): the name, +0x40 a text, +0x60 the
   description, +0xe0 a number, +0xe8 the kind (a 0x75dda4 string) ---- */
#define mission(i) ((const u8 *)IMG(0x9ef2d4) + (i) * 0xfc)
#define g_missionTop GAME_VAR(int, 0x9f16bc)      /* the first row shown */

/* the columns' left (and right) x from the window's left */
static const int column_x0[4] = { 0x10, 0x159, 0x1b3, 0x20d }, column_x1[4] = { 0x154, 0x1ae, 0x208, 0x25d };

/* 0x444f40: the mission list: the window and its title 0x75dda4, a cyan frame and rule, the column heads (0x75de24,
   0x80 apart) on blue bars, up to 8 rows from g_missionTop (the picked one bright), the picked one's description
   (wrapped at the window's right less 0x38) and two buttons (0x75e0a4; 8 / 9 under the pointer by skirmishSettings_hitTest,
   lit). The original leaves eax to callers that ignore it */
void (skirmish_drawScreenA)(void)
{
	int hovered = GAME_FN(skirmishSettings_hitTest, 0x4438d0, int, int, int)(g_mouseX, g_mouseY);   /* skirmishSettings_hitTest */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(BX0, BY0, BX1, BY1, 1);
	set_colour_bits((Colour *)IMG(0x76d438), g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw16(BX0 + 0x10, BY0 + 0xa, (const char *)MSG(511, "DON'T"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(BX0 + 8, BY0 + 0x20, BX1 - 8, BY1 - 8, 0);
	menu_drawLine(BX0 + 0x18, BY1 - 0xa0, BX1 - 0x18, BY1 - 0xa0);
	set_colour_bits(g_rectColour, 0, 0x3e4ccccd, 0x3f19999a, 0x3f4ccccd);   /* 0, 0.2, 0.6, 0.8 */
	for (int c = 0; c < 4; c++)
		menu_drawRect(BX0 + column_x0[c], BY0 + 0x24, BX0 + column_x1[c], BY0 + 0x3c, 1);
	set_colour_bits((Colour *)IMG(0x76d438), 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_draw8(BX0 + 0x18, BY0 + 0x28, (const char *)MSG(512, "SUCCEED"));
	for (int c = 1; c < 4; c++)
		text_draw8b(BX0 + column_x0[c], BY0 + 0x28, BX0 + column_x1[c], (const char *)(MSG(512, "SUCCEED") + c * 0x80));
	text_draw8(BX0 + 0xf0, BY1 - 0x9e, (const char *)MSG(516, "MISSION BRIEFING"));
	char number[12];
	for (int i = 0; i < g_missionCount && i < 8; i++) {
		const u32 *colour = g_missionPicked == g_missionTop + i ? g_panelColour : g_dimColour;
		set_colour_bits((Colour *)IMG(0x76d438), colour[0], colour[1], colour[2], colour[3]);
		int y = BY0 + i * 0x1a + 0x48;
		text_draw8(BX0 + 0x18, y, (const char *)mission(g_missionTop + i));
		text_draw8b(BX0 + column_x0[1], y, BX0 + column_x1[1], (const char *)mission(g_missionTop + i) + 0x40);
		itoa(*(const int *)(mission(g_missionTop + i) + 0xe0), number, 10);
		text_draw8b(BX0 + column_x0[2], y, BX0 + column_x1[2], number);
		text_draw8b(BX0 + column_x0[3], y, BX0 + column_x1[3],
		            (const char *)(MSG(511, "DON'T") + *(const int *)(mission(g_missionTop + i) + 0xe8) * 0x80));
	}
	text_setWrapX(BX1 - 0x38);
	set_colour_bits((Colour *)IMG(0x76d438), g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw8(BX0 + 0xf0, BY1 - 0x8c, (const char *)mission(g_missionPicked) + 0x60);
	text_setWrapX(0x280);
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x0 = BX1 + k * 0x8c - 0x12c, x1 = BX1 + k * 0x8c - 0xb4;
		int lit = hovered == k + 8;
		menu_drawWideButton(x0, BY1 - 0x40, x1, BY1 - 0x20, lit);
		const u32 *colour = lit ? g_panelColour : g_dimColour;
		set_colour_bits((Colour *)IMG(0x76d438), colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x0, BY1 - 0x38, x1, (const char *)(MSG(517, "RESERVED") + k * 0x80));
	}
}
#undef mission

/* 0x4456b0: the mission briefing: a translucent blue window, its title 0x75e024, a cyan frame and rule, the text
   typed out (briefing_typeOut), two buttons at the right (0x75e2a4, 0x80 apart; lit under the pointer: 0 / 1 by
   briefing_hitTest) and two at the left (0x75e3a4: 2 only once the text is out (0x4d7348), 3 only with something to
   undo (0x9f1060); greyed otherwise). The original leaves eax to callers that ignore it */
void (skirmish_drawScreenB)(void)
{
	int hovered = briefing_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(BX0, BY0, BX1, BY1, 1);
	set_colour_bits((Colour *)IMG(0x76d438), g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw16(BX0 + 0x10, BY0 + 0xa, (const char *)MSG(516, "MISSION BRIEFING"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(BX0 + 8, BY0 + 0x20, BX1 - 8, BY1 - 8, 0);
	menu_drawLine(BX0 + 0x18, BY1 - 0x40, BX1 - 0x18, BY1 - 0x40);
	set_colour_bits((Colour *)IMG(0x76d438), g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	briefing_typeOut();
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x = BX1 + k * 0x8c;
		int lit = hovered == k;
		briefing_button(x - 0x12c, x - 0xb4, lit, lit ? g_panelColour : g_dimColour, (const char *)(MSG(521, "$[0] ACCEPT") + k * 0x80));
	}
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x = BX0 + k * 0x8c;
		int usable = k == 0 ? g_briefingSkipped != 0 : g_undoDepth > 0;
		int lit = usable && hovered == k + 2;
		briefing_button(x + 0x30, x + 0xa8, lit, usable ? (lit ? g_panelColour : g_dimColour) : NULL,
		                (const char *)(MSG(523, "$[0] NEXT") + k * 0x80));
	}
}

/* 0x445bc0, 0x445bd0: jumps to skirmish_drawScreenA and skirmish_drawScreenB (the skirmish setup's states'
   frames; their callers ignore eax) */
void (skirmish_frameScreenA)(void) { skirmish_drawScreenA(); }
void (skirmish_frameScreenB)(void) { skirmish_drawScreenB(); }
