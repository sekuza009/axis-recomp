/* skirmish.c: the skirmish screen: its list's keys and the briefing typed out one character at a time. */
#include "../game.h"
#include <string.h>

#define g_repeatUp GAME_VAR(float, 0x76d37c)       /* frames until a held up / down key steps again */
#define g_repeatDown GAME_VAR(float, 0x680bb4)
#define g_zero GAME_VAR(float, 0x4a93e8)

/* a held key's repeat: the first press steps at once and waits 4 frames, then it steps whenever the wait runs out.
   1 when the key is held */
static int repeat(int key, float *wait, void (*step)(void))
{
	if (input_isDown(key) == 0)
		BITS(*wait) = 0;
	if (input_isDown(key) != 1)
		return 0;
	g_cursorBlink = 0;
	if (*wait > g_zero) {
		*wait = fsub_m(fld_m(wait), &g_frameTime);
		return 1;
	}
	*wait = 4.0f;
	step();
	return 1;
}

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
	if (!repeat(g_keyUp, &g_repeatUp, list_up))
		repeat(g_keyDown, &g_repeatDown, list_down);
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
