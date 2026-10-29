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

/* 0x422c60: the sound tab: OK takes the edited values (the menu sounds' volume worked out, the menu music restarted); back or cancel
   closes the page */
void (setup_soundTabKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4))) {
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
	} else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupPage = 0;
	}
}

/* 0x422d20: the graphics tab: OK takes the edited values; if the four that need a restart changed (all but the
   third and the last two), the front end is told (message 1) instead of closing the page */
void (setup_graphicTabKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4))) {
		int same = g_graphicSettings[1] == g_graphicEdited[1] && g_graphicSettings[0] == g_graphicEdited[0]
		           && g_graphicSettings[3] == g_graphicEdited[3] && g_graphicSettings[4] == g_graphicEdited[4];
		sound_playMenu(0);
		for (int i = 0; i < 7; i++)
			g_graphicSettings[i] = g_graphicEdited[i];
		cfg_loadAxisCfg();
		if (same)
			g_setupPage = 0;
		else
			profile_41e7a0(1);
	} else if (input_justPressed(g_keyBack) || input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_setupPage = 0;
	}
}

/* the setup screen with an open page over it: the page, or just its frame while a dialog is up */
static void with_page(void (*draw)(void), const int frame[4])
{
	setup_423e50();
	if (g_setupPage == 1 || g_setupPage == 0 || g_setupTab == TAB_TOP)
		return;
	if (g_dialogOpen == 0)
		draw();
	else
		menu_drawFrame(frame[0], frame[1], frame[2], frame[3]);
}

static void page_424810(void) { setup_424810(); }
static void page_425460(void) { setup_425460(); }
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
void (setup_420e50)(int k)
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
