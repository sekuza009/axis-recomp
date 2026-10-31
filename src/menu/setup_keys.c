/* setup_keys.c: the setup screen's top level: its tabs (sound, graphics, controls, and the top page), their keys,
   and the pages drawn over the screen's background. */
#include "../game.h"
#include <string.h>

#define TAB_SOUND 0
#define TAB_GRAPHIC 1
#define TAB_CONTROL 2
#define TAB_TOP 0x29a

#define g_setupPage GAME_VAR(int, 0x4ddcec)           /* (by use) the open page's state: 0 and 1 closed */
#define g_soundEdited ((const int *)0x4dde98)         /* the sound tab's values being edited (the menu sounds' volume first) */
#define g_soundSettings ((int *)0x4e0c90)             /* the sound settings in use */
#define g_graphicEdited ((const u32 *)0x4ddba0)       /* the graphics tab's seven values being edited */
#define g_graphicSettings ((u32 *)0x83a9c0)           /* the graphics settings in use (g_items3D is the third) */

/* 0x422b30: the tab's page (nothing while a dialog is up) */
void (setup_drawTab)(void)
{
	if (g_dialogOpen != 0)
		return;
	switch (g_setupTab) {
	case TAB_CONTROL: setup_drawControlTab(); break;
	case TAB_SOUND: setup_drawSoundTab(); break;
	case TAB_GRAPHIC: setup_drawGraphicTab(); break;
	case TAB_TOP: setup_drawTopPage(); break;
	}
}

/* 0x4230a0: the tab's keys */
void (setup_processTabKeys)(void)
{
	if (g_dialogOpen != 0)
		return;
	switch (g_setupTab) {
	case TAB_CONTROL: setup_controlTabKeys(); break;
	case TAB_SOUND: setup_soundTabKeys(); break;
	case TAB_GRAPHIC: setup_graphicTabKeys(); break;
	case TAB_TOP: setup_topPageKeys(); break;
	}
}

/* back to the main menu */
static void leave(void)
{
	set_680370_441250(4);
	g_nextScreen = 300;
	g_cursorBlink = 0.0f;
	nullsub_48b420(NULL);
}

/* 0x422b70: the top page: a tab key opens its tab; the back key (when 0x9dae10 allows) or the leave key goes
   back to the main menu */
void (setup_topPageKeys)(void)
{
	if (input_justPressed(g_keyCancel2) && GAME_VAR(int, 0x9dae10) > 0) {
		leave();
	} else if (input_justPressed(GAME_VAR(int, 0x4e1524)) == 1) {
		sound_playMenu(0);
		setup_selectSoundTab();
	} else if (input_justPressed(GAME_VAR(int, 0x4e14ec)) == 1) {
		sound_playMenu(0);
		setup_selectGraphicTab();
	} else if (input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		setup_selectControlTab();
	} else if (input_justPressed(GAME_VAR(int, 0x4e153c)) == 1) {
		sound_playMenu(0);
		leave();
	}
}

/* the sound tab's OK: the edited values taken (the menu sounds' volume worked out), the page closed and the menu
   music restarted */
static void sound_ok(void)
{
	int volume = g_soundEdited[0];
	g_soundSettings[2] = g_soundEdited[2];
	g_soundSettings[1] = g_soundEdited[1];
	g_soundSettings[0] = volume;
	g_soundSettings[3] = g_soundEdited[3];
	g_menuVolume = (volume * 5 - 500) * 4;
	sound_playMenu(0);
	cfg_loadAxisCfg();
	g_setupPage = 0;
	music_shutdown();
	music_play((const char *)0x4b01cc);                  /* "music/Netsphere.mp3" */
}

/* 0x422c60: the sound tab: OK (sound_ok); back or cancel closes the page */
void (setup_soundTabKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)))
		sound_ok();
	else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupPage = 0;
	}
}

/* the graphics tab's OK: the edited values taken and axis.cfg written; if the four that need a restart changed
   (all but the third and the last two), the front end is told (message 1) instead of closing the page. Returns the
   last call's eax */
static u32 graphics_apply(void)
{
	int same = g_graphicSettings[1] == g_graphicEdited[1] && g_graphicSettings[0] == g_graphicEdited[0]
	           && g_graphicSettings[3] == g_graphicEdited[3] && g_graphicSettings[4] == g_graphicEdited[4];
	sound_playMenu(0);
	for (int i = 0; i < 7; i++)
		g_graphicSettings[i] = g_graphicEdited[i];
	u32 r = GAME_CDECL(0x42d730, u32, void)();   /* cfg_loadAxisCfg */
	if (!same)
		return GAME_CDECL(0x41e7a0, u32, int)(1);   /* app_closeWindow */
	g_setupPage = 0;
	return r;
}

/* 0x422d20: the graphics tab's keys: OK (0x4e0cd4) as graphics_apply, back / cancel close the page */
void (setup_graphicTabKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)))
		graphics_apply();
	else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupPage = 0;
	}
}

/* the setup screen with an open page over it: the page, or just its frame while a dialog is up */
static void with_page(void (*draw)(void), const int frame[4])
{
	setup_drawTunnel();
	if (g_setupPage == 1 || g_setupPage == 0 || g_setupTab == TAB_TOP)
		return;
	if (g_dialogOpen == 0)
		draw();
	else
		menu_drawFrame(frame[0], frame[1], frame[2], frame[3]);
}

static void page_424810(void) { setup_drawSoundPage(); }
static void page_425460(void) { setup_drawOptionsDialog(); }
static void page_crosshair(void) { setup_crosshairScreen(); }

/* 0x427830, 0x427880, 0x4278d0: the screen with the key bindings page, the second page, the crosshair page */
void (setup_427830)(void) { with_page(page_424810, (const int *)0x4ddad0); }
void (setup_427880)(void) { with_page(page_425460, (const int *)0x4dddd0); }
void (setup_4278d0)(void) { with_page(page_crosshair, (const int *)0x4dde80); }

/* a tab opened: the page state, the setup camera's distance (-1650) and its fade (0.7), no item picked */
static void tab_opened(void)
{
	g_setupPage = 1;
	GAME_VAR(u32, 0x4de038) = 0x3f333333;   /* 0.7 */
	GAME_VAR(int, 0x4ddb98) = 0;
	GAME_VAR(int, 0x4dde90) = -1;
	GAME_VAR(int, 0x4dda60) = 0;
	GAME_VAR(u32, 0x4ddd90) = 0xc4ce4000;   /* -1650.0 */
}

/* 0x420ad0, 0x420b40, 0x420ba0: the sound, graphics and controls tabs opened, each on a copy of its settings in
   use */
void (setup_selectSoundTab)(void)
{
	memcpy((void *)g_soundEdited, g_soundSettings, 16);
	g_setupTab = TAB_SOUND;
	tab_opened();
}

void (setup_selectGraphicTab)(void)
{
	memcpy((void *)g_graphicEdited, g_graphicSettings, 7 * 4);
	g_setupTab = TAB_GRAPHIC;
	tab_opened();
}

void (setup_selectControlTab)(void)
{
	memcpy((void *)0x4de0c0, (void *)0x4def00, 0x44 * 4);   /* the key bindings */
	g_setupTab = TAB_CONTROL;
	GAME_VAR(int, 0x4ddce8) = 0;
	GAME_VAR(int, 0x4de040) = -1;
	GAME_VAR(int, 0x4dddc8) = 0;
	GAME_VAR(int, 0x4b04f8) = -1;
	tab_opened();
}

/* ---- the control bindings: 32 pairs (primary, secondary), "none" being the value at 0x4df8e4 ---- */
static const u32 bindings[32] = { 0x4de0c0, 0x4de0c8, 0x4de0d0, 0x4de0d8, 0x4de0e0, 0x4de0e8, 0x4de0f0, 0x4de0f8,
                                  0x4de100, 0x4de108, 0x4de110, 0x4de118, 0x4de120, 0x4de138, 0x4de140, 0x4de148,
                                  0x4de150, 0x4de128, 0x4de130, 0x4de158, 0x4de160, 0x4de168, 0x4de170, 0x4de178,
                                  0x4de180, 0x4de188, 0x4de190, 0x4de198, 0x4de1a0, 0x4de1a8, 0x4de1b0, 0x4de1b8 };
#define KEY_NONE GAME_VAR(int, 0x4df8e4)

/* 0x421350: a pair with no primary key gets its secondary as the primary */
void (setup_drawKeyBindingRow)(void)
{
	int none = KEY_NONE;
	for (int k = 0; k < 32; k++) {
		int *pair = (int *)bindings[k];
		if (pair[0] == none) {
			pair[0] = pair[1];
			pair[1] = none;
		}
	}
}

/* 0x420e50: key k unbound: the first pair holding it as its secondary keeps only its primary, moved to the secondary
   (and the scan stops); a primary equal to k before that becomes none */
void (setup_unbindKey)(int k)
{
	int none = KEY_NONE;
	for (int i = 0; i < 32; i++) {
		int *pair = (int *)bindings[i];
		if (pair[1] == k) {
			pair[1] = pair[0];
			pair[0] = none;
			return;
		}
		if (pair[0] == k)
			pair[0] = none;
	}
}

/* 0x4220c0: the setup screen's top page clicks: a left click on one of its four buttons (outlines at 0x4df918)
   opens the sound, graphics or controls tab or goes back to the main menu; a right click (when 0x9dae10 allows) goes
   back too. Returns what the original leaves in eax */
u32 (setup_drawTopPage)(void)
{
	if (GAME_VAR(int, 0x4ded88)) {
		const Outline *buttons = (const Outline *)0x4df918;
		for (int i = 0; i < 4; i++) {
			if (point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), buttons[i]) != 1)
				continue;
			switch (i) {
			case 0: sound_playMenu(0); GAME_CDECL(0x420ad0, void, void)(); break;   /* the sound tab */
			case 1: sound_playMenu(0); GAME_CDECL(0x420b40, void, void)(); break;   /* graphics */
			case 2: sound_playMenu(0); GAME_CDECL(0x420ba0, void, void)(); break;   /* controls */
			case 3:
				set_680370_441250(4);
				sound_playMenu(0);
				g_nextScreen = 300;
				GAME_VAR(int, 0x4dda44) = 0;
				GAME_CDECL(0x48b420, void, void)();   /* nullsub_48b420 */
				break;
			}
			break;
		}
	}
	int right = GAME_VAR(int, 0x4ded8c);
	if (!right)
		return 0;
	int allowed = GAME_VAR(int, 0x9dae10);
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	u32 r = GAME_CDECL(0x441250, u32, int)(4);   /* set_680370_441250 */
	g_nextScreen = 300;
	GAME_VAR(int, 0x4dda44) = 0;
	GAME_CDECL(0x48b420, void, void)();
	return r;
}

/* 0x422480: the graphics tab clicked (the page open, no message box; a right click closes it). Buttons
   (setup_4206b0): 0 the video mode on (0 .. 7, then 0), 1 .. 5 the colour depth, polygon detail, linear filtering,
   mipmapping and frame counter switched, 6 the simple menu (with 0x9da494), 7 OK (graphics_apply), 8 close. Each
   with its sound. Returns what the original leaves in eax (for a switch, its old or new value) */
u32 (setup_drawGraphicTab)(void)
{
	u32 page = GAME_VAR(u32, 0x4ddcec);
	if (page == 1 || page == 0 || GAME_VAR(int, 0x90d1c4))
		return page;
	if (GAME_VAR(int, 0x4ded8c))
		g_setupPage = 0;
	if (!GAME_VAR(int, 0x4ded88))
		return page;
	u32 button = GAME_CDECL(0x4206b0, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* setup_4206b0 */
	u32 *edited = (u32 *)g_graphicEdited, old, mode;
	switch (button) {
	case 0:
		sound_playMenu(2);
		mode = ++edited[0];
		if ((int)mode > 7)
			edited[0] = 0;
		return mode;
	case 1: case 2: case 3: case 4: case 5:
		sound_playMenu(2);
		old = edited[button];
		edited[button] = 1 - old;
		return button == 2 || button == 5 ? 1 - old : old;   /* the original's eax held one or the other */
	case 6:
		sound_playMenu(2);
		old = GAME_VAR(u32, 0x9da494);
		edited[6] = 1 - edited[6];
		GAME_VAR(u32, 0x9da494) = 1 - old;
		return old;
	case 7:
		return graphics_apply();
	case 8:
		old = GAME_CDECL(0x41e760, u32, int)(0);
		g_setupPage = 0;
		return old;
	}
	return button;
}

/* ---- the sound tab's mouse: the volume (g_soundEdited[0], 0 .. 100; 0x4dde90 the arrow last used, 0x4ddb98 its
   glow) ---- */
#define g_volume GAME_VAR(int, 0x4dde98)

static void volume_down(void)
{
	if (g_volume > 0) {
		GAME_VAR(int, 0x4dde90) = 0;
		g_volume--;
		GAME_VAR(u32, 0x4ddb98) = 0x40a00000;   /* 5 */
	}
}

static void volume_up(void)
{
	if (g_volume < 100) {
		GAME_VAR(int, 0x4dde90) = 1;
		g_volume++;
		GAME_VAR(u32, 0x4ddb98) = 0x40a00000;
	}
}

/* the slider set where the pointer is (its track 0x90 in from the page, 0x4ddad0) */
static void volume_at_pointer(void)
{
	g_volume = 1 - ftol(fmul_m((long double)(g_mouseX - GAME_VAR(int, 0x4ddad0) - 0x90), (const float *)0x4a94f0));
}

/* 0x4221d0: the sound tab's mouse (an open page, no message box; a right click closes it but goes on): a click (the
   blink clock restarted) on the volume's arrows (0 / 1) or slider (2), the sound toggles (5: 0x4dde9c 0 / 100; 6, 7:
   0x4ddea0, 0x4ddea4), OK (8) or close (9); holding the arrows or the slider repeats once the clock passes 1 (and
   restarts it). The original leaves eax to callers that ignore it */
void (setup_drawSoundTab)(void)
{
	if (g_setupPage == 1 || g_setupPage == 0 || GAME_VAR(int, 0x90d1c4))
		return;
	if (GAME_VAR(int, 0x4ded8c))
		g_setupPage = 0;
	if (g_mouseClick) {
		g_cursorBlink = 0.0f;
		switch (setup_420670(g_mouseX, g_mouseY)) {
		case 0: volume_down(); break;
		case 1: volume_up(); break;
		case 2: volume_at_pointer(); break;
		case 5: GAME_VAR(int, 0x4dde9c) = GAME_VAR(int, 0x4dde9c) >= 50 ? 0 : 100; break;
		case 6:
			sound_playMenu(2);
			GAME_VAR(int, 0x4ddea0) = 1 - GAME_VAR(int, 0x4ddea0);
			break;
		case 7:
			sound_playMenu(2);
			GAME_VAR(int, 0x4ddea4) = 1 - GAME_VAR(int, 0x4ddea4);
			break;
		case 8: sound_ok(); break;
		case 9:
			sound_playMenu(0);
			g_setupPage = 0;
			break;
		}
	}
	if (!g_mouseHeld || !(g_cursorBlink > *(const float *)0x4a9424))
		return;
	g_cursorBlink = 0.0f;
	switch (setup_420670(g_mouseX, g_mouseY)) {
	case 0: volume_down(); break;
	case 1: volume_up(); break;
	case 2: volume_at_pointer(); break;
	}
}
#undef g_volume

/* ---- the controls tab: four pages of bindings (0x4ddce8), a row selected on the page (0x4de040, -1 none) ---- */
#define g_bindWaiting GAME_VAR(int, 0x4dddc8)         /* the selected row waits for its new key */
#define g_bindRow GAME_VAR(int, 0x4de040)
#define g_bindPage GAME_VAR(int, 0x4ddce8)
#define g_bindRows ((const int *)0x4b04ec)            /* rows per page */
#define g_bindToggle GAME_VAR(int, 0x4de1c0)          /* row 10's setting (on / off) */

/* 0x422e10: the controls tab's keys. 0x9da440 only gives a sound. While a row waits: cancel stops waiting, any
   other key (codes 2 .. 0xdd) is bound to it. Otherwise: fire selects (row 10 toggles), up / down move along the
   page's rows, four keys pick the page, OK takes the bindings (the copy at 0x4de0c0 into 0x4def00, axis.cfg read)
   and closes, back or cancel closes, 0x4e0ce0 puts the defaults back (the original leaves eax to callers that
   ignore it) */
void (setup_controlTabKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x9da440))) {
		sound_playMenu(6);
		return;
	}
	if (g_bindWaiting) {
		if (input_justPressed(GAME_VAR(int, 0x9da440))) {
			sound_playMenu(6);
			return;
		}
		if (input_justPressed(g_keyCancel2)) {
			sound_playMenu(1);
			g_bindWaiting = 0;
			return;
		}
		for (int key = 2; key < 0xde; key++)
			if (input_justPressed(key)) {
				sound_playMenu(2);
				setup_drawKeyBindingRows(key);
				g_bindWaiting = 0;
				return;
			}
		return;
	}
	if (input_justPressed(g_keyClick) == 1) {
		if (g_bindRow < 0)
			return;
		sound_playMenu(2);
		if (g_bindRow == 10)
			g_bindToggle = 1 - g_bindToggle;
		else
			g_bindWaiting = 1;
		return;
	}
	if (input_justPressed(g_keyUp) == 1) {
		if (g_bindRow >= 0)
			g_bindRow--;
		return;
	}
	if (input_justPressed(g_keyDown) == 1) {
		if (g_bindRow < g_bindRows[g_bindPage] - 1)
			g_bindRow++;
		return;
	}
	static const u32 page_keys[4] = { 0x4e1508, 0x4e1524, 0x4e14f4, 0x4e1530 };
	for (int page = 0; page < 4; page++)
		if (input_justPressed(GAME_VAR(int, page_keys[page])) == 1) {
			sound_playMenu(2);
			g_bindPage = page;
			return;
		}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)) == 1) {
		sound_playMenu(0);
		memcpy((void *)0x4def00, (const void *)0x4de0c0, 0x44 * 4);
		cfg_loadAxisCfg();
		g_setupPage = 0;
		return;
	}
	if (input_justPressed(g_keyBack) != 1) {
		if (input_justPressed(GAME_VAR(int, 0x4e0ce0)) == 1) {
			sound_playMenu(0);
			setup_controlTabHelper_420c10();
			return;
		}
		if (!input_justPressed(g_keyCancel2))
			return;
	}
	sound_playMenu(0);
	g_setupPage = 0;
}

/* 0x422830: the controls tab's mouse (an open page, no message box). While a row waits for its key, a right click,
   the wheel (down 0x9da490, up 0x76d490) or a click binds that button to it; otherwise a right click closes the page
   (and goes on). A click picks a page (0 .. 3), OK (the bindings at 0x4de0c0 kept in 0x4def00, axis.cfg read; the
   page closed), close, the defaults; on page 3 rows 7 / 8 toggle their setting (0x4de1c0 / 0x4de1c4), 9 drags the
   slider and 10 / 11 step 0x4de1cc (0 .. 7); any other row control with a row selected makes it wait for a key.
   Holding the button on page 3's slider (once the blink clock passes 1) drags it. The original leaves eax to
   callers that ignore it */
void (setup_drawControlTab)(void)
{
	if (g_setupPage == 1 || g_setupPage == 0 || GAME_VAR(int, 0x90d1c4))
		return;
	int waiting = g_bindWaiting;
	if (GAME_VAR(int, 0x4ded8c)) {
		if (waiting) {
			setup_drawKeyBindingRows(GAME_VAR(int, 0x76d424));
			g_bindWaiting = 0;
			return;
		}
		g_setupPage = 0;
	}
	if (GAME_VAR(int, 0x4ded70) && waiting) {
		int wheel = GAME_VAR(int, 0x4ded7c);
		if (wheel < 0)
			setup_drawKeyBindingRows(GAME_VAR(int, 0x9da490));
		else if (wheel > 0)
			setup_drawKeyBindingRows(GAME_VAR(int, 0x76d490));
		g_bindWaiting = 0;
		return;
	}
	if (g_mouseClick) {
		if (waiting) {
			setup_drawKeyBindingRows(GAME_VAR(int, 0x4de73c));
			g_bindWaiting = 0;
			return;
		}
		int on = setup_4206f0(g_mouseX, g_mouseY), row = g_bindRow, page = g_bindPage;
		if ((u32)on <= 3) {
			sound_playMenu(2);
			g_bindPage = on;
		} else if (on == 4) {
			sound_playMenu(0);
			memcpy((void *)0x4def00, (const void *)0x4de0c0, 0x110);
			cfg_loadAxisCfg();
			g_setupPage = 0;
		} else if (on == 5) {
			sound_playMenu(0);
			g_setupPage = 0;
		} else if (on == 6) {
			sound_playMenu(0);
			setup_controlTabHelper_420c10();
		} else if ((on == 7 || on == 8) && row >= 0 && page == 3) {
			int *setting = &GAME_VAR(int, on == 7 ? 0x4de1c0 : 0x4de1c4);
			*setting = 1 - *setting;
			sound_playMenu(0);
			return;
		} else if ((on == 9 || ((on == 7 || on == 8) && row < 0)) && page == 3) {
			setup_drawControlSlider();
			return;
		} else if ((on == 10 || on == 11) && g_bindPage == 3) {
			if (++GAME_VAR(int, 0x4de1cc) > 7)
				GAME_VAR(int, 0x4de1cc) = 0;
			sound_playMenu(0);
			return;
		} else if (on >= 7 && on <= 17 && row >= 0) {
			g_bindWaiting = 1;
			sound_playMenu(0);
		}
	}
	if (g_mouseHeld && g_cursorBlink > *(const float *)0x4a9424 && setup_4206f0(g_mouseX, g_mouseY) == 9 && g_bindPage == 3)
		setup_drawControlSlider();
}

/* the binding (two key slots, eight bytes from 0x4de0c0) each row of the three key pages edits; -1: none */
static const signed char page_bindings[3][11] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1 },
	{ 10, 11, 12, 15, 16, 17, 18, 13, 14, 19, 20 },
	{ 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, -1 },
};

/* 0x421680 (named setup_drawKeyBindingRows; by use the key pressed for the binding being edited, the page 0x4ddce8's
   row 0x4de040): unless it is the excluded key (0x9da440), the key is taken off the other bindings (setup_unbindKey) and
   set in the row's binding: with its second slot set, the key in the first and the second cleared (0x4df8e4: none);
   else into an empty first slot; else, unless the first is this key, into the second. Then the row redrawn. The
   callers ignore the eax it leaves */
void (setup_drawKeyBindingRows)(int key)
{
	if (key == GAME_VAR(int, 0x9da440))
		return;
	setup_unbindKey(key);
	int page = GAME_VAR(int, 0x4ddce8), row = GAME_VAR(int, 0x4de040);
	int binding = page >= 0 && page <= 2 && (u32)row < 11 ? page_bindings[page][row] : -1;
	if (binding >= 0) {
		int *slot = (int *)(0x4de0c0 + binding * 8), none = GAME_VAR(int, 0x4df8e4);
		if (slot[1] != none) {
			slot[0] = key;
			slot[1] = none;
		} else if (slot[0] == none)
			slot[0] = key;
		else if (slot[0] != key)
			slot[1] = key;
	}
	setup_drawKeyBindingRow();
}

/* the mouse-sensitivity slider's part under the cursor acted on: the minus / plus buttons step the value (0x4de1c8)
   within 0..100 (0x4dde90 which way) and start the 5.0 highlight timer (0x4ddb98); the bar sets it from the cursor x */
static void slider_press(void)
{
#define VALUE GAME_VAR(int, 0x4de1c8)
	switch (setup_420730(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c))) {
	case 0:
		if (VALUE > 0) {
			GAME_VAR(int, 0x4dde90) = 0;
			VALUE--;
			GAME_VAR(u32, 0x4ddb98) = 0x40a00000;   /* 5.0f */
		}
		break;
	case 1:
		if (VALUE < 100) {
			GAME_VAR(int, 0x4dde90) = 1;
			VALUE++;
			GAME_VAR(u32, 0x4ddb98) = 0x40a00000;
		}
		break;
	case 2:
		VALUE = 1 - ftol((GAME_VAR(int, 0x4ded68) - GAME_VAR(int, 0x4dde80) - 0x108) * (long double)GAME_VAR(float, 0x4a94f4));
		break;
	}
#undef VALUE
}

/* 0x4226b0: the slider on the control setup page: a click (0x4ded88), or the button held (0x4ded94) for over a
   second (its timer 0x4dda44 past 0x4a9424), presses the part under the cursor, the timer starting again. Nothing
   uses the eax it leaves */
void (setup_drawControlSlider)(void)
{
#define TIMER GAME_VAR(float, 0x4dda44)
	if (GAME_VAR(int, 0x4ded88)) {
		TIMER = 0;
		slider_press();
	}
	if (GAME_VAR(int, 0x4ded94) && TIMER > GAME_VAR(float, 0x4a9424)) {
		TIMER = 0;
		slider_press();
	}
#undef TIMER
}
