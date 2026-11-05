/* skirmish.c: the skirmish screen: its list's keys and the briefing typed out one character at a time. */
#include "../game.h"
#include <string.h>
#include "key_repeat.h"

static void list_up(void) { skirmish_cursorUp(); }
static void list_down(void) { skirmish_cursorDown(); }

/* 0x443f20: the skirmish list's keys: 0x4e0cd4 or fire reads the chosen mission's block (mission_loadBriefing), back
   or cancel leaves, up / down move the cursor with a key repeat (the original leaves eax to callers that ignore it) */
void (skirmish_listKeys)(void)
{
	if (input_justPressed(g_dikA) == 1 || input_justPressed(g_keyClick) == 1) {
		mission_loadBriefing(g_missionPicked);
		return;
	}
	if (input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel2) == 1) {
		skirmish_leave();
		return;
	}
	if (!key_repeat(g_keyUp, &g_repeatUp, list_up))
		key_repeat(g_keyDown, &g_repeatDown, list_down);
}

/* ---- the briefing: the text block 0x9ef1ec (read by mission_loadBriefing), from offset 0x9eeba4 up to 0x9ef200;
   0x9ef1f4 characters of it shown so far, copied to 0x9f1064 ---- */

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
#define BX0 g_briefingX
#define BY0 g_briefingY
#define BX1 g_briefingRight
#define BY1 g_briefingBottom
#define g_panelColour (g_skirmishColourLit)
#define g_dimColour (g_skirmishColourDim)

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
	set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(x0, BY1 - 0x28, x1, label);
}

static void bind_button_texture(void)
{
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/* ---- the mission list: g_missions (count 0x9ef2c0) ---- */

/* the columns' left (and right) x from the window's left */
static const int column_x0[4] = { 0x10, 0x159, 0x1b3, 0x20d }, column_x1[4] = { 0x154, 0x1ae, 0x208, 0x25d };

/* 0x444f40: the mission list: the window and its title 0x75dda4, a cyan frame and rule, the column heads (0x75de24,
   0x80 apart) on blue bars, up to 8 rows from g_missionTop (the picked one bright), the picked one's description
   (wrapped at the window's right less 0x38) and two buttons (MSG(517, "RESERVED"); 8 / 9 under the pointer by skirmishList_hitTest,
   lit). The original leaves eax to callers that ignore it */
void (missionList_draw)(void)
{
	int hovered = skirmishList_hitTest(g_mouseX, g_mouseY);   /* skirmishList_hitTest */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(BX0, BY0, BX1, BY1, 1);
	set_colour_bits(g_textColour, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw16(BX0 + 0x10, BY0 + 0xa, (const char *)MSG(511, "DON'T"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(BX0 + 8, BY0 + 0x20, BX1 - 8, BY1 - 8, 0);
	menu_drawLine(BX0 + 0x18, BY1 - 0xa0, BX1 - 0x18, BY1 - 0xa0);
	set_colour_bits(g_rectColour, 0, 0x3e4ccccd, 0x3f19999a, 0x3f4ccccd);   /* 0, 0.2, 0.6, 0.8 */
	for (int c = 0; c < 4; c++)
		menu_drawRect(BX0 + column_x0[c], BY0 + 0x24, BX0 + column_x1[c], BY0 + 0x3c, 1);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_draw8(BX0 + 0x18, BY0 + 0x28, (const char *)MSG(512, "SUCCEED"));
	for (int c = 1; c < 4; c++)
		text_draw8b(BX0 + column_x0[c], BY0 + 0x28, BX0 + column_x1[c], (const char *)(MSG(512, "SUCCEED") + c * 0x80));
	text_draw8(BX0 + 0xf0, BY1 - 0x9e, (const char *)MSG(516, "MISSION BRIEFING"));
	char number[12];
	for (int i = 0; i < g_missionCount && i < 8; i++) {
		const u32 *colour = g_missionPicked == g_missionTop + i ? g_panelColour : g_dimColour;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		int y = BY0 + i * 0x1a + 0x48;
		const Mission *m = &g_missions[g_missionTop + i];
		text_draw8(BX0 + 0x18, y, m->name);
		text_draw8b(BX0 + column_x0[1], y, BX0 + column_x1[1], m->title);
		itoa(m->number, number, 10);
		text_draw8b(BX0 + column_x0[2], y, BX0 + column_x1[2], number);
		text_draw8b(BX0 + column_x0[3], y, BX0 + column_x1[3],
		            (const char *)(MSG(511, "DON'T") + m->result * 0x80));
	}
	text_setWrapX(BX1 - 0x38);
	set_colour_bits(g_textColour, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw8(BX0 + 0xf0, BY1 - 0x8c, g_missions[g_missionPicked].briefing);
	text_setWrapX(0x280);
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x0 = BX1 + k * 0x8c - 0x12c, x1 = BX1 + k * 0x8c - 0xb4;
		int lit = hovered == k + 8;
		menu_drawWideButton(x0, BY1 - 0x40, x1, BY1 - 0x20, lit);
		const u32 *colour = lit ? g_panelColour : g_dimColour;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x0, BY1 - 0x38, x1, (const char *)(MSG(517, "RESERVED") + k * 0x80));
	}
}
#undef mission

/* 0x4456b0: the mission briefing: a translucent blue window, its title 0x75e024, a cyan frame and rule, the text
   typed out (briefing_typeOut), two buttons at the right (MSG(521, "$[0] ACCEPT"), 0x80 apart; lit under the pointer: 0 / 1 by
   briefing_hitTest) and two at the left (MSG(523, "$[0] NEXT"): 2 only once the text is out (0x4d7348), 3 only past the first
   page (g_briefingPage); greyed otherwise). The original leaves eax to callers that ignore it */
void (missionBriefing_draw)(void)
{
	int hovered = briefing_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(BX0, BY0, BX1, BY1, 1);
	set_colour_bits(g_textColour, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw16(BX0 + 0x10, BY0 + 0xa, (const char *)MSG(516, "MISSION BRIEFING"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(BX0 + 8, BY0 + 0x20, BX1 - 8, BY1 - 8, 0);
	menu_drawLine(BX0 + 0x18, BY1 - 0x40, BX1 - 0x18, BY1 - 0x40);
	set_colour_bits(g_textColour, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
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
		int usable = k == 0 ? g_briefingSkipped != 0 : g_briefingPage > 0;
		int lit = usable && hovered == k + 2;
		briefing_button(x + 0x30, x + 0xa8, lit, usable ? (lit ? g_panelColour : g_dimColour) : NULL,
		                (const char *)(MSG(523, "$[0] NEXT") + k * 0x80));
	}
}

/* 0x445bc0, 0x445bd0: jumps to missionList_draw and missionBriefing_draw (the skirmish setup's states'
   frames; their callers ignore eax) */
void (skirmish_frameList)(void) { missionList_draw(); }
void (skirmish_frameBriefing)(void) { missionBriefing_draw(); }
