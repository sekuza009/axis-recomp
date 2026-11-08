/* menu_keys.c: key handling of the front end: each screen has its own handler; these pick it. */
#include "../game.h"

/* 0x4319d0: the menus' keys, once per frame: none while a text field has them (g_textFieldOpen), the menu camera
   moves (g_menuCameraMove) or the key guard runs (g_menuKeyGuard above 0; the keyboard reacquired before these two);
   a message box (g_dialogPending) takes them first; else the current screen's handler (g_screen) */
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
	case 200: title_keyDismiss(); break;              /* title */
	case 210: profile_screenKeys(); break;              /* profiles */
	case 300: mainmenu_processKeys(); break;
	case 400: lobby_processKeys(); break;
	case 500: skirmish_keys(); break;              /* skirmish */
	case 600: setup_processTabKeys(); break;
	case 700: armc_processInput(); break;        /* armour */
	case 800: room_keysByState(); break;       /* game room */
	case 900: missions_pageKeys(); break;              /* the mission list */
	case 9999: freeCam_keys(); break;
	}
}

/* 0x44cdd0: the profile screen's keys: none while a dialog frame opens (g_frameOpening); once the log-out was
   answered yes (g_profileQuitting, the game about to quit) the cancel key or a click only sets g_profileQuitSkip 5
   and the unused camera words; else the current page's handler (g_profilePage: 1 list, 2 message, 3 delete, 5 log
   out, 6 pilot select) */
void (profile_screenKeys)(void)
{
	if (g_frameOpening)
		return;
	if (g_profileQuitting && g_profileQuitSkip != 5) {
		if (input_justPressed(g_keyCancel) == 1 || input_justPressed(g_keyClick) == 1) {
			g_profileQuitSkip = 5;
			g_unusedProfileCameraTime = 0;
			g_unusedProfileCameraZoom = 100.0f;
			g_unusedProfileCameraSpeed = 0.05f;
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
