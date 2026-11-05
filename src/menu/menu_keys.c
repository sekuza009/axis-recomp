/* menu_keys.c: key handling of the front end: each screen has its own handler; these pick it. */
#include "../game.h"

/* 0x4319d0: the menus' keys, once per frame: none while the input is off, the keys are blocked or the screen is
   still fading in; a message box takes them first; else the current screen's handler */
void (menu_processKeys)(void)
{
	if (g_textFieldOpen)
		return;
	input_reacquireKeyboard();
	if (g_menuCameraMove)
		return;
	if (g_menuKeyGuard > 0.0f)
		return;
	if (g_dialogPending) {
		messageBox_keyClose();
		return;
	}
	switch (g_screen) {
	case 200: menu_keyStartFade(); break;              /* title */
	case 210: profile_screenKeys(); break;              /* profiles */
	case 300: mainmenu_processKeys(); break;
	case 400: lobby_processKeys(); break;
	case 500: missionsel_keys(); break;              /* missions */
	case 600: setup_processTabKeys(); break;
	case 700: armc_processInput(); break;        /* armour */
	case 800: room_keysByState(); break;       /* game room */
	case 900: skirmish_pageKeys(); break;              /* skirmish */
	case 9999: freeCam_keys(); break;
	}
}

/* 0x44cdd0 (profile_screenKeys): the profile screen's keys: none with a dialog open; during the intro animation the cancel
   key or a click skips it to its end; else the current page's handler */
void (profile_screenKeys)(void)
{
	if (g_dialogOpen)
		return;
	if (g_profileIntro && g_profileIntroState != 5) {
		if (input_justPressed(g_keyCancel) == 1 || input_justPressed(g_keyClick) == 1) {
			g_profileIntroState = 5;
			g_profileIntroTime = 0;
			g_profileIntroZoom = 100.0f;
			g_profileIntroSpeed = 0.05f;
		}
		return;
	}
	switch (g_profilePage) {
	case 1: profileList_keys(); break;             /* the profile list */
	case 2: profile_messageKeys(); break;
	case 3: profile_deleteKeys(); break;
	case 5: profile_logOutKeys(); break;
	case 6: pilotSelect_keys(); break;             /* CHARACTER SELECT's grid */
	}
}
