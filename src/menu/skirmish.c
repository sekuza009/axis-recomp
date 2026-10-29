/* skirmish.c: the skirmish screen: its list's keys and the briefing typed out one character at a time. */
#include "../game.h"
#include <string.h>
#include "key_repeat.h"

static void list_up(void) { skirmish_443cd0(); }
static void list_down(void) { skirmish_443d10(); }

/* 0x443f20: the skirmish list's keys: 0x4e0cd4 or fire reads the chosen mission's block (mission_saveAxisMis), back
   or cancel leaves, up / down move the cursor with a key repeat (the original leaves eax to callers that ignore it) */
void (skirmish_processKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)) == 1 || input_justPressed(g_keyClick) == 1) {
		mission_saveAxisMis(GAME_VAR(int, 0x9f16a4));
		return;
	}
	if (input_justPressed(g_keyBack) == 1 || input_justPressed(g_keyCancel2) == 1) {
		skirmish_443c80();
		return;
	}
	if (!key_repeat(g_keyUp, &g_repeatUp, list_up))
		key_repeat(g_keyDown, &g_repeatDown, list_down);
}

/* ---- the briefing: the text block 0x9ef1ec (read by mission_saveAxisMis), from offset 0x9eeba4 up to 0x9ef200;
   0x9ef1f4 characters of it shown so far, copied to 0x9f1064 ---- */
#define g_briefing GAME_VAR(u8 *, 0x9ef1ec)
#define g_briefingStart GAME_VAR(int, 0x9eeba4)
#define g_briefingShown GAME_VAR(int, 0x9ef1f4)
#define g_briefingEnd GAME_VAR(int, 0x9ef200)
#define g_briefingDone GAME_VAR(int, 0x9f105c)      /* the whole text is out */
#define g_briefingSkipped GAME_VAR(int, 0x4d7348)
#define g_briefingClock GAME_VAR(float, 0x9f16b8)
#define g_briefingText ((char *)0x9f1064)
#define g_briefingX GAME_VAR(int, 0x9f16a8)         /* the briefing window */
#define g_briefingY GAME_VAR(int, 0x9f16ac)
#define g_textEndX GAME_VAR(int, 0x4d23c8)          /* where the last text pass ended */
#define g_textEndY GAME_VAR(int, 0x4d23cc)

/* 0x445520: the briefing typed out: while not done or skipped, every 1.4 of the clock (frame times added) shows one
   more character (a CR LF or a double-byte character at once); drawn in the briefing window (wrapping at 0x23e,
   bottom 0x76), with a cursor bar (half bright on its left) at its end while still typing */
void (skirmish_445520)(void)
{
	u8 *text = g_briefing;
	if (!text)
		return;
	if (!g_briefingDone && !g_briefingSkipped) {
		long double clock = fadd_m(fld_m(&g_frameTime), &g_briefingClock);
		g_briefingClock = clock;
		if (clock > GAME_VAR(double, 0x4a95e0)) {
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
	skirmish_4017b0(0x23e);
	skirmish_4017c0(0x76);
	text_draw8(g_briefingX + 0x20, g_briefingY + 0x40, g_briefingText);
	if (!g_briefingDone && !g_briefingSkipped) {
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(g_textEndX, g_textEndY - 1, g_textEndX + 8, g_textEndY + 0x11, 1);
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f000000);
		menu_drawRect(g_textEndX - 8, g_textEndY - 1, g_textEndX, g_textEndY + 0x11, 1);
	}
	skirmish_4017b0(0x280);
	skirmish_4017c0(0x1e0);
}

/* ---- the briefing window (0x9f16a8 .. 0x9f16b4) ---- */
#define BX0 GAME_VAR(int, 0x9f16a8)
#define BY0 GAME_VAR(int, 0x9f16ac)
#define BX1 GAME_VAR(int, 0x9f16b0)
#define BY1 GAME_VAR(int, 0x9f16b4)
#define g_panelColour ((const u32 *)0x9ef208)
#define g_dimColour ((const u32 *)0x9eeac8)

/* one of the window's buttons (x0 .. x1 along its bottom): the textured quad, lit when lit, then its label in
   colour (none: grey, the button greyed) */
static void briefing_button(int x0, int x1, int lit, const u32 *colour, const char *label)
{
	static const u32 grey[4] = { 0x3f19999a, 0x3f19999a, 0x3f19999a, 0x3f800000 };   /* 0.6, 0.6, 0.6, 1 */
	if (!colour)
		glColor4f(0.6f, 0.6f, 0.6f, 1.0f);
	menu_drawTexQuad_4282f0(x0, BY1 - 0x30, x1, BY1 - 0x10, lit);
	if (!colour)
		colour = grey;
	set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(x0, BY1 - 0x28, x1, label);
}

static void bind_button_texture(void)
{
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

/* 0x4456b0: the mission briefing: a translucent blue window, its title 0x75e024, a cyan frame and rule, the text
   typed out (skirmish_445520), two buttons at the right (0x75e2a4, 0x80 apart; lit under the pointer: 0 / 1 by
   skirmish_443910) and two at the left (0x75e3a4: 2 only once the text is out (0x4d7348), 3 only with something to
   undo (0x9f1060); greyed otherwise). The original leaves eax to callers that ignore it */
void (skirmish_drawScreenB)(void)
{
	int hovered = skirmish_443910(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
	menu_drawRect(BX0, BY0, BX1, BY1, 1);
	set_colour_bits((Colour *)0x76d438, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	text_draw16(BX0 + 0x10, BY0 + 0xa, (const char *)0x75e024);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(BX0 + 8, BY0 + 0x20, BX1 - 8, BY1 - 8, 0);
	FUN_00427a40(BX0 + 0x18, BY1 - 0x40, BX1 - 0x18, BY1 - 0x40);
	set_colour_bits((Colour *)0x76d438, g_panelColour[0], g_panelColour[1], g_panelColour[2], g_panelColour[3]);
	skirmish_445520();
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x = BX1 + k * 0x8c;
		int lit = hovered == k;
		briefing_button(x - 0x12c, x - 0xb4, lit, lit ? g_panelColour : g_dimColour, (const char *)(0x75e2a4 + k * 0x80));
	}
	for (int k = 0; k < 2; k++) {
		bind_button_texture();
		int x = BX0 + k * 0x8c;
		int usable = k == 0 ? GAME_VAR(int, 0x4d7348) != 0 : GAME_VAR(int, 0x9f1060) > 0;
		int lit = usable && hovered == k + 2;
		briefing_button(x + 0x30, x + 0xa8, lit, usable ? (lit ? g_panelColour : g_dimColour) : NULL,
		                (const char *)(0x75e3a4 + k * 0x80));
	}
}
