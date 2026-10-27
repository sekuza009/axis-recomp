/* menu_keys.c: key handling of the front end: each screen has its own handler; these pick it. */
#include "../game.h"

/* 0x4319d0: the menus' keys, once per frame: none while the input is off, the keys are blocked or the screen is
   still fading in; a message box takes them first; else the current screen's handler */
void (menu_processKeys)(void)
{
	if (g_paused)
		return;
	input_reacquireKeyboard();
	if (g_keysBlocked)
		return;
	if (g_menuFade > 0.0f)
		return;
	if (g_dialogPending) {
		menu_431950();
		return;
	}
	switch (g_screen) {
	case 200: menu_4318b0(); break;              /* title */
	case 210: menu_44cdd0(); break;              /* profiles */
	case 300: mainmenu_processKeys(); break;
	case 400: lobby_processKeys(); break;
	case 500: menu_447c70(); break;              /* missions */
	case 600: setup_processTabKeys(); break;
	case 700: armc_processInput(); break;        /* armour */
	case 800: menu_4378e0(); break;              /* game room */
	case 900: menu_4440f0(); break;              /* skirmish */
	case 9999: match_debugHandler(); break;
	}
}

/* 0x44cdd0 (menu_44cdd0): the profile screen's keys: none with a dialog open; during the intro animation Enter
   skips it to its end; else the current page's handler */
void (menu_44cdd0)(void)
{
	if (g_dialogOpen)
		return;
	if (g_profileIntro && g_profileIntroState != 5) {
		if (input_justPressed(g_keyEnter2) == 1 || input_justPressed(g_keyEnter) == 1) {
			g_profileIntroState = 5;
			g_profileIntroTime = 0;
			g_profileIntroZoom = 100.0f;
			g_profileIntroSpeed = 0.05f;
		}
		return;
	}
	switch (g_profilePage) {
	case 1: profile_44c600(); break;             /* the profile list */
	case 2: profile_44c850(); break;
	case 3: profile_44c8c0(); break;
	case 5: profile_44ca90(); break;
	case 6: profile_44cc60(); break;             /* the emblem grid */
	}
}
