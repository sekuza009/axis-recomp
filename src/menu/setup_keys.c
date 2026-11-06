/* setup_keys.c: the setup screen's top level: its tabs (sound, graphics, controls, and the top page), their keys,
   and the pages drawn over the screen's background. */
#include "../game.h"
#include <string.h>

#define TAB_SOUND 0
#define TAB_GRAPHIC 1
#define TAB_CONTROL 2
#define TAB_TOP 0x29a

#define g_graphicInUse ((u32 *)g_graphicSettings)               /* the graphics settings in use (g_highDetail is the third) */

/* 0x422b30: the open tab's clicks (nothing while a dialog is up): controls, sound, graphics or the top page */
void (setup_tabClicks)(void)
{
	if (g_frameOpening != 0)
		return;
	switch (g_setupTab) {
	case TAB_CONTROL: setup_controlTabClicks(); break;
	case TAB_SOUND: setup_soundTabClicks(); break;
	case TAB_GRAPHIC: setup_graphicTabClicks(); break;
	case TAB_TOP: setup_topPageClicks(); break;
	}
}

/* 0x4230a0: the tab's keys */
void (setup_processTabKeys)(void)
{
	if (g_frameOpening != 0)
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
	menuCamera_setMove(4);
	g_nextScreen = 300;
	g_menuRepeatClock = 0.0f;
	shared_emptyFunction(NULL);
}

/* 0x422b70: the top page: a tab key opens its tab; the back key (when a tunnel ring is behind: g_tunnelRings > 0) or the leave key goes
   back to the main menu */
void (setup_topPageKeys)(void)
{
	if (input_justPressed(g_keyCancel2) && g_tunnelRings > 0) {
		leave();
	} else if (input_justPressed(g_dikS) == 1) {
		sound_playMenu(0);
		setup_selectSoundTab();
	} else if (input_justPressed(g_dikG) == 1) {
		sound_playMenu(0);
		setup_selectGraphicTab();
	} else if (input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		setup_selectControlTab();
	} else if (input_justPressed(g_dikX) == 1) {
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
	cfg_writeAxisCfg();
	g_setupCameraMode = 0;
	music_stop();
	music_play((const char *)STR(0x4b01cc, "music/Netsphere.mp3"));
}

/* 0x422c60: the sound tab: OK (sound_ok); back or cancel closes the page */
void (setup_soundTabKeys)(void)
{
	if (input_justPressed(g_dikA))
		sound_ok();
	else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupCameraMode = 0;
	}
}

/* the graphics tab's OK: the edited values taken and axis.cfg written; if the four that need a restart changed
   (all but the third and the last two), the front end is told (message 1) instead of closing the page. Returns the
   last call's eax */
static u32 graphics_apply(void)
{
	int same = g_graphicInUse[1] == g_graphicEdited[1] && g_graphicInUse[0] == g_graphicEdited[0]
	           && g_graphicInUse[3] == g_graphicEdited[3] && g_graphicInUse[4] == g_graphicEdited[4];
	sound_playMenu(0);
	for (int i = 0; i < 7; i++)
		g_graphicInUse[i] = g_graphicEdited[i];
	u32 r = cfg_writeAxisCfg();   /* cfg_writeAxisCfg */
	if (!same)
		return ((u32)app_closeWindow(1));   /* app_closeWindow */
	g_setupCameraMode = 0;
	return r;
}

/* 0x422d20: the graphics tab's keys: OK (g_dikA) as graphics_apply, back / cancel close the page */
void (setup_graphicTabKeys)(void)
{
	if (input_justPressed(g_dikA))
		graphics_apply();
	else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupCameraMode = 0;
	}
}

/* the setup screen with an open page over it: the page, or just its frame while a dialog is up */
static void with_page(void (*draw)(void), const int frame[4])
{
	setup_drawTunnel();
	if (g_setupCameraMode == 1 || g_setupCameraMode == 0 || g_setupTab == TAB_TOP)
		return;
	if (g_frameOpening == 0)
		draw();
	else
		menu_drawFrame(frame[0], frame[1], frame[2], frame[3]);
}

static void page_sound(void) { setup_drawSoundPage(); }
static void page_graphic(void) { setup_drawGraphicPage(); }
static void page_controls(void) { setup_drawControlsPage(); }

/* 0x427830, 0x427880, 0x4278d0: the screen with the sound page, the graphics page, the controls page */
void (setup_frameSoundPage)(void) { with_page(page_sound, (const int *)ADDR(g_setupSoundLeft)); }
void (setup_frameGraphicPage)(void) { with_page(page_graphic, g_setupGraphicRect); }
void (setup_frameControlsPage)(void) { with_page(page_controls, (const int *)ADDR(g_setupControlLeft)); }

/* a tab opened: the page state, the setup camera's distance (-1650) and its fade (0.7), no item picked */
static void tab_opened(void)
{
	g_setupCameraMode = 1;
	(*(u32 *)&g_setupTunnelAlpha) = 0x3f333333;   /* 0.7 */
	(*(int *)&g_setupPressedClock) = 0;
	g_setupArrowPressed = -1;
	g_setupPanelMoving = 0;
	(*(u32 *)&g_setupTunnelDepth) = 0xc4ce4000;   /* -1650.0 */
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
	memcpy((void *)g_graphicEdited, g_graphicInUse, 7 * 4);
	g_setupTab = TAB_GRAPHIC;
	tab_opened();
}

void (setup_selectControlTab)(void)
{
	memcpy((void *)OBJ(g_controlsEdit), (void *)OBJ(g_controls), 0x44 * 4);   /* the key bindings */
	g_setupTab = TAB_CONTROL;
	g_bindPage = 0;
	g_bindRow = -1;
	g_bindWaiting = 0;
	g_lastCrosshair = -1;
	tab_opened();
}

/* ---- the control bindings: 32 pairs (primary, secondary), "none" being the value at g_dikNone ---- */
static const u32 bindings[32] = { OBJ(g_controlsEdit), (OBJ(g_controlsEdit) + 0x8), (OBJ(g_controlsEdit) + 0x10), (OBJ(g_controlsEdit) + 0x18), (OBJ(g_controlsEdit) + 0x20), (OBJ(g_controlsEdit) + 0x28), (OBJ(g_controlsEdit) + 0x30), (OBJ(g_controlsEdit) + 0x38),
                                  (OBJ(g_controlsEdit) + 0x40), (OBJ(g_controlsEdit) + 0x48), (OBJ(g_controlsEdit) + 0x50), (OBJ(g_controlsEdit) + 0x58), (OBJ(g_controlsEdit) + 0x60), (OBJ(g_controlsEdit) + 0x78), (OBJ(g_controlsEdit) + 0x80), (OBJ(g_controlsEdit) + 0x88),
                                  (OBJ(g_controlsEdit) + 0x90), (OBJ(g_controlsEdit) + 0x68), (OBJ(g_controlsEdit) + 0x70), (OBJ(g_controlsEdit) + 0x98), (OBJ(g_controlsEdit) + 0xa0), (OBJ(g_controlsEdit) + 0xa8), (OBJ(g_controlsEdit) + 0xb0), (OBJ(g_controlsEdit) + 0xb8),
                                  (OBJ(g_controlsEdit) + 0xc0), (OBJ(g_controlsEdit) + 0xc8), (OBJ(g_controlsEdit) + 0xd0), (OBJ(g_controlsEdit) + 0xd8), (OBJ(g_controlsEdit) + 0xe0), (OBJ(g_controlsEdit) + 0xe8), (OBJ(g_controlsEdit) + 0xf0), (OBJ(g_controlsEdit) + 0xf8) };
#define KEY_NONE g_dikNone

/* 0x421350: a pair with no primary key gets its secondary as the primary */
void (controls_fillPrimaryKeys)(void)
{
	int none = KEY_NONE;
	for (int k = 0; k < 32; k++) {
		int *pair = (int *)RELOC(bindings[k]);
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
		int *pair = (int *)RELOC(bindings[i]);
		if (pair[1] == k) {
			pair[1] = pair[0];
			pair[0] = none;
			return;
		}
		if (pair[0] == k)
			pair[0] = none;
	}
}

/* 0x4220c0: the setup screen's top page clicks: a left click on one of its four buttons (outlines at g_setupTopOutlines)
   opens the sound, graphics or controls tab or goes back to the main menu; a right click (when a tunnel ring is behind: g_tunnelRings > 0) goes
   back too. Returns what the original leaves in eax */
u32 (setup_topPageClicks)(void)
{
	if (g_mouseClick) {
		const Outline *buttons = (const Outline *)OBJ(g_setupTopOutlines);
		for (int i = 0; i < 4; i++) {
			if (point_in_outline(g_mouseX, g_mouseY, buttons[i]) != 1)
				continue;
			switch (i) {
			case 0: sound_playMenu(0); setup_selectSoundTab(); break;   /* the sound tab */
			case 1: sound_playMenu(0); setup_selectGraphicTab(); break;   /* graphics */
			case 2: sound_playMenu(0); setup_selectControlTab(); break;   /* controls */
			case 3:
				menuCamera_setMove(4);
				sound_playMenu(0);
				g_nextScreen = 300;
				(*(int *)&g_menuRepeatClock) = 0;
				GAME_FN(shared_emptyFunction, 0x48b420, void, void)();   /* shared_emptyFunction */
				break;
			}
			break;
		}
	}
	int right = g_rightClick;
	if (!right)
		return 0;
	int allowed = g_tunnelRings;
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	u32 r = menuCamera_setMove(4);   /* menuCamera_setMove */
	g_nextScreen = 300;
	(*(int *)&g_menuRepeatClock) = 0;
	GAME_FN(shared_emptyFunction, 0x48b420, void, void)();
	return r;
}

/* 0x422480: the graphics tab clicked (the page open, no message box; a right click closes it). Buttons
   (setupGraphic_hitTest): 0 the video mode on (0 .. 7, then 0), 1 .. 5 the colour depth, polygon detail, linear filtering,
   mipmapping and frame counter switched, 6 the simple menu (with g_simpleMenu), 7 OK (graphics_apply), 8 close. Each
   with its sound. Returns what the original leaves in eax (for a switch, its old or new value) */
u32 (setup_graphicTabClicks)(void)
{
	u32 page = (*(u32 *)&g_setupCameraMode);
	if (page == 1 || page == 0 || g_frameOpening)
		return page;
	if (g_rightClick)
		g_setupCameraMode = 0;
	if (!g_mouseClick)
		return page;
	u32 button = ((u32)setupGraphic_hitTest(g_mouseX, g_mouseY));   /* setupGraphic_hitTest */
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
		old = (*(u32 *)&g_simpleMenu);
		edited[6] = 1 - edited[6];
		(*(u32 *)&g_simpleMenu) = 1 - old;
		return old;
	case 7:
		return graphics_apply();
	case 8:
		old = sound_playMenu(0);
		g_setupCameraMode = 0;
		return old;
	}
	return button;
}

/* ---- the sound tab's mouse: the volume (g_soundEdited[0], 0 .. 100; g_setupArrowPressed the arrow last used (0 down, 1 up), g_setupPressedClock its
   glow) ---- */

static void volume_down(void)
{
	if (g_setupEffectVolume > 0) {
		g_setupArrowPressed = 0;
		g_setupEffectVolume--;
		(*(u32 *)&g_setupPressedClock) = 0x40a00000;   /* 5 */
	}
}

static void volume_up(void)
{
	if (g_setupEffectVolume < 100) {
		g_setupArrowPressed = 1;
		g_setupEffectVolume++;
		(*(u32 *)&g_setupPressedClock) = 0x40a00000;
	}
}

/* the slider set where the pointer is (its track 0x90 in from the page, g_setupSoundLeft) */
static void volume_at_pointer(void)
{
	g_setupEffectVolume = 1 - ftol(fmul_m((long double)(g_mouseX - g_setupSoundLeft - 0x90), k_m0_390625f));
}

/* 0x4221d0: the sound tab's mouse (an open page, no message box; a right click closes it but goes on): a click (the
   blink clock restarted) on the volume's arrows (0 / 1) or slider (2), the sound toggles (5: g_setupMusicVolume 0 / 100; 6, 7:
   g_setupSound3D, g_setupStereoReverse), OK (8) or close (9); holding the arrows or the slider repeats once the clock passes 1 (and
   restarts it). The original leaves eax to callers that ignore it */
void (setup_soundTabClicks)(void)
{
	if (g_setupCameraMode == 1 || g_setupCameraMode == 0 || g_frameOpening)
		return;
	if (g_rightClick)
		g_setupCameraMode = 0;
	if (g_mouseClick) {
		g_menuRepeatClock = 0.0f;
		switch (setupSound_hitTest(g_mouseX, g_mouseY)) {
		case 0: volume_down(); break;
		case 1: volume_up(); break;
		case 2: volume_at_pointer(); break;
		case 5: g_setupMusicVolume = g_setupMusicVolume >= 50 ? 0 : 100; break;
		case 6:
			sound_playMenu(2);
			g_setupSound3D = 1 - g_setupSound3D;
			break;
		case 7:
			sound_playMenu(2);
			g_setupStereoReverse = 1 - g_setupStereoReverse;
			break;
		case 8: sound_ok(); break;
		case 9:
			sound_playMenu(0);
			g_setupCameraMode = 0;
			break;
		}
	}
	if (!g_mouseHeld || !(g_menuRepeatClock > k_1f))
		return;
	g_menuRepeatClock = 0.0f;
	switch (setupSound_hitTest(g_mouseX, g_mouseY)) {
	case 0: volume_down(); break;
	case 1: volume_up(); break;
	case 2: volume_at_pointer(); break;
	}
}

/* ---- the controls tab: four pages of bindings (g_bindPage), a row selected on the page (g_bindRow, -1 none) ---- */
#define g_bindToggle (g_mouseSwitchesEdit[0])          /* row 10's setting (on / off) */

/* 0x422e10: the controls tab's keys. F1 (g_dikF1) only gives a sound. While a row waits: cancel stops waiting, any
   other key (codes 2 .. 0xdd) is bound to it. Otherwise: fire selects (row 10 toggles), up / down move along the
   page's rows, four keys pick the page, OK takes the bindings (the copy at g_controlsEdit into g_keyForward, axis.cfg read)
   and closes, back or cancel closes, g_dikD puts the defaults back (the original leaves eax to callers that
   ignore it) */
void (setup_controlTabKeys)(void)
{
	if (input_justPressed(g_dikF1)) {
		sound_playMenu(6);
		return;
	}
	if (g_bindWaiting) {
		if (input_justPressed(g_dikF1)) {
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
				setup_bindKey(key);
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
		if (g_bindRow < ((int *)g_bindRows)[g_bindPage] - 1)
			g_bindRow++;
		return;
	}
	static const u32 page_keys[4] = { ADDR(g_dikM), ADDR(g_dikS), ADDR(g_dikI), ADDR(g_dikU) };
	for (int page = 0; page < 4; page++)
		if (input_justPressed(GAME_VAR(int, page_keys[page])) == 1) {
			sound_playMenu(2);
			g_bindPage = page;
			return;
		}
	if (input_justPressed(g_dikA) == 1) {
		sound_playMenu(0);
		memcpy((void *)OBJ(g_controls), (const void *)OBJ(g_controlsEdit), 0x44 * 4);
		cfg_writeAxisCfg();
		g_setupCameraMode = 0;
		return;
	}
	if (input_justPressed(g_keyBack) != 1) {
		if (input_justPressed(g_dikD) == 1) {
			sound_playMenu(0);
			setup_defaultBindings();
			return;
		}
		if (!input_justPressed(g_keyCancel2))
			return;
	}
	sound_playMenu(0);
	g_setupCameraMode = 0;
}

/* 0x422830: the controls tab's mouse (an open page, no message box). While a row waits for its key, a right click,
   the wheel (up g_dikWheelUp, down g_dikWheelDown) or a click binds that button to it; otherwise a right click closes the page
   (and goes on). A click picks a page (0 .. 3), OK (the bindings at g_controlsEdit kept in g_keyForward, axis.cfg read; the
   page closed), close, the defaults; on page 3 rows 7 / 8 toggle their setting (0x4de1c0 / 0x4de1c4), 9 drags the
   slider and 10 / 11 step g_crosshairEdit (0 .. 7); any other row control with a row selected makes it wait for a key.
   Holding the button on page 3's slider (once the blink clock passes 1) drags it. The original leaves eax to
   callers that ignore it */
void (setup_controlTabClicks)(void)
{
	if (g_setupCameraMode == 1 || g_setupCameraMode == 0 || g_frameOpening)
		return;
	int waiting = g_bindWaiting;
	if (g_rightClick) {
		if (waiting) {
			setup_bindKey(g_dikMouse2);
			g_bindWaiting = 0;
			return;
		}
		g_setupCameraMode = 0;
	}
	if (g_mouseWheelTurned && waiting) {
		int wheel = g_mouseWheel;
		if (wheel < 0)
			setup_bindKey(g_dikWheelUp);
		else if (wheel > 0)
			setup_bindKey(g_dikWheelDown);
		g_bindWaiting = 0;
		return;
	}
	if (g_mouseClick) {
		if (waiting) {
			setup_bindKey(g_dikMouse1);
			g_bindWaiting = 0;
			return;
		}
		int on = setupControl_hitTest(g_mouseX, g_mouseY), row = g_bindRow, page = g_bindPage;
		if ((u32)on <= 3) {
			sound_playMenu(2);
			g_bindPage = on;
		} else if (on == 4) {
			sound_playMenu(0);
			memcpy((void *)OBJ(g_controls), (const void *)OBJ(g_controlsEdit), 0x110);
			cfg_writeAxisCfg();
			g_setupCameraMode = 0;
		} else if (on == 5) {
			sound_playMenu(0);
			g_setupCameraMode = 0;
		} else if (on == 6) {
			sound_playMenu(0);
			setup_defaultBindings();
		} else if ((on == 7 || on == 8) && row >= 0 && page == 3) {
			int *setting = &GAME_VAR(int, on == 7 ? OBJ(g_mouseSwitchesEdit) : (OBJ(g_mouseSwitchesEdit) + 0x4));
			*setting = 1 - *setting;
			sound_playMenu(0);
			return;
		} else if ((on == 9 || ((on == 7 || on == 8) && row < 0)) && page == 3) {
			setup_sliderClicks();
			return;
		} else if ((on == 10 || on == 11) && g_bindPage == 3) {
			if (++g_crosshairEdit > 7)
				g_crosshairEdit = 0;
			sound_playMenu(0);
			return;
		} else if (on >= 7 && on <= 17 && row >= 0) {
			g_bindWaiting = 1;
			sound_playMenu(0);
		}
	}
	if (g_mouseHeld && g_menuRepeatClock > k_1f && setupControl_hitTest(g_mouseX, g_mouseY) == 9 && g_bindPage == 3)
		setup_sliderClicks();
}

/* the binding (two key slots, eight bytes from g_controlsEdit) each row of the three key pages edits; -1: none */
static const signed char page_bindings[3][11] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1 },
	{ 10, 11, 12, 15, 16, 17, 18, 13, 14, 19, 20 },
	{ 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, -1 },
};

/* 0x421680 (the key, mouse button or wheel code pressed for the binding being edited, the page g_bindPage's
   row g_bindRow): unless it is F1 (g_dikF1, never bound), the key is taken off the other bindings (setup_unbindKey) and
   set in the row's binding: with its second slot set, the key in the first and the second cleared (g_dikNone: none);
   else into an empty first slot; else, unless the first is this key, into the second. Then every pair left with no
   primary key gets its secondary as the primary (controls_fillPrimaryKeys). The callers ignore the eax it leaves */
void (setup_bindKey)(int key)
{
	if (key == g_dikF1)
		return;
	setup_unbindKey(key);
	int page = g_bindPage, row = g_bindRow;
	int binding = page >= 0 && page <= 2 && (u32)row < 11 ? page_bindings[page][row] : -1;
	if (binding >= 0) {
		int *slot = (int *)(OBJ(g_controlsEdit) + binding * 8), none = g_dikNone;
		if (slot[1] != none) {
			slot[0] = key;
			slot[1] = none;
		} else if (slot[0] == none)
			slot[0] = key;
		else if (slot[0] != key)
			slot[1] = key;
	}
	controls_fillPrimaryKeys();
}

/* the mouse-sensitivity slider's part under the cursor acted on: the minus / plus buttons step the value (g_sensitivitySlider)
   within 0..100 (g_setupArrowPressed which way) and start the 5.0 highlight timer (g_setupPressedClock); the bar sets it from the cursor x */
static void slider_press(void)
{
#define VALUE g_sensitivitySlider
	switch (setupSlider_hitTest(g_mouseX, g_mouseY)) {
	case 0:
		if (VALUE > 0) {
			g_setupArrowPressed = 0;
			VALUE--;
			(*(u32 *)&g_setupPressedClock) = 0x40a00000;   /* 5.0f */
		}
		break;
	case 1:
		if (VALUE < 100) {
			g_setupArrowPressed = 1;
			VALUE++;
			(*(u32 *)&g_setupPressedClock) = 0x40a00000;
		}
		break;
	case 2:
		VALUE = 1 - ftol((g_mouseX - g_setupControlLeft - 0x108) * (long double)k_m0_5f);
		break;
	}
#undef VALUE
}

/* 0x4226b0: the slider on the control setup page: a click (g_mouseClicked), or the button held (g_mouseButtonsHeld) for over a
   second (its timer g_menuRepeatClock past k_1f), presses the part under the cursor, the timer starting again. Nothing
   uses the eax it leaves */
void (setup_sliderClicks)(void)
{
#define TIMER g_menuRepeatClock
	if (g_mouseClick) {
		TIMER = 0;
		slider_press();
	}
	if (g_mouseHeld && TIMER > k_1f) {
		TIMER = 0;
		slider_press();
	}
#undef TIMER
}
