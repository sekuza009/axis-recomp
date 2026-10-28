/* menu_states.c: small pieces of the front end's screens: the main menu's frame, the 3D background behind the
   menus, the skirmish and mission settings pages' dispatch, and the mission select keys. */
#include "../game.h"

#define g_tunnel GAME_VAR(TunnelRing *, 0x67fb3c)      /* the background tunnel's first ring */
#define g_settingsPage GAME_VAR(int, 0x9ef1f8)        /* (by use) 10 the skirmish settings, 20 the mission settings */
#define g_settingsState GAME_VAR(int, 0x9ef1f0)       /* (by use) 0 and 1: the page is not up */
#define g_missionState GAME_VAR(int, 0x9f62f8)        /* (by use) the mission select: 0 and 1 not up */
#define g_missionBusy GAME_VAR(int, 0x9f6300)
#define g_missionBriefing GAME_VAR(int, 0x9f62e0)     /* (by use) a mission's briefing is shown */
#define g_mission GAME_VAR(int, 0x9f63b4)             /* the mission chosen, 0 .. 14 */
#define g_quitAsked GAME_VAR(int, 0x67ef14)           /* (by use) 1: the quit question is up */

/* 0x441740: the 3D background behind the menus: the tunnel's rings moved on (armc_enter) and drawn */
void (menu_drawBackground)(void)
{
	armc_enter(g_tunnel);
	gfx_setProjection2D3D(1);
	menu_drawBackground3D(g_tunnel);
}

/* 0x4434f0: the map-select dialog of the main menu (only its frame while a dialog is up) */
void (mainmenu_4434f0)(void)
{
	if (g_dialogOpen != 0)
		menu_drawFrame(GAME_VAR(int, 0x9dd908), GAME_VAR(int, 0x9dd90c), GAME_VAR(int, 0x9dd910), GAME_VAR(int, 0x9dd914));
	else
		mainmenu_442e10();
}

/* 0x443530: the main menu's frame: background, menu, the map-select dialog when open, and while the quit question
   is up the keys are held (state 1), the next screen set to 9999 and the screen dimmed */
void (menuState300_frame)(void)
{
	menu_drawBackground();
	menu_mainMenu();
	if (GAME_VAR(int, 0x9eeab4) != 0)
		mainmenu_4434f0();
	if (g_quitAsked == 1) {
		set_680370_441250(1);
		g_nextScreen = 9999;
		menu_drawDimOverlay();
	}
}

/* 0x443ef0: the settings page's draw pass (none while a dialog is up) */
void (menu_443ef0)(void)
{
	if (g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_saveSettings();
	else if (g_settingsPage == 20)
		menu_443ea0();
}

/* 0x4440f0: the settings page's keys */
void (menu_4440f0)(void)
{
	if (g_settingsState == 1 || g_settingsState == 0 || g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_processKeys();
	else if (g_settingsPage == 20)
		menu_444070();
}

/* 0x4479b0: mission chosen (sound 2) */
void (mission_4479b0)(int mission)
{
	GAME_VAR(int, 0x9f6328) = mission;
	GAME_VAR(int, 0x9f63b0) = 1;
	sound_playMenu(2);
}

/* 0x447b10: the mission select's draw pass: the briefing or the list */
void (mission_unlockCheat)(void)
{
	if (g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		mission_447af0();
	else
		mission_447a50();
}

/* 0x447c30: the briefing's keys: Esc or Enter closes it */
void (menu_447c30)(void)
{
	if (input_justPressed(g_keyCancel2) == 1 || input_justPressed(g_keyClick) == 1)
		g_missionBriefing = 0;
}

/* 0x447b40: the list's keys: Esc or back leaves, O starts the mission, left / right step through the missions
   unlocked so far (g_progress), and Left Ctrl + Right Alt + Page Up unlocks them all */
void (menu_447b40)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		FUN_00447960();
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		mission_4479d0();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		FUN_00447960();
		return;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_mission > 0)
		mission_4479b0(--g_mission);
	if (input_justPressed(g_keyRight) == 1 && g_mission < g_progress) {
		if (g_mission >= 14)
			return;
		mission_4479b0(++g_mission);
	}
	if (input_isDown(g_keyLeftCtrl) && input_isDown(GAME_VAR(int, 0x4df9fc)) && input_justPressed(GAME_VAR(int, 0x4df90c)))
		g_progress = 16;
}

/* 0x447c70: the mission select's keys (not while a dialog is up) */
void (menu_447c70)(void)
{
	if (g_missionState == 1 || g_missionState == 0 || g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		menu_447c30();
	else
		menu_447b40();
}

/* 0x41edc0 (FUN_0041edc0): back to the main menu: the background tunnel freed ring by ring (last first), the menus
   entered again, state 300 */
void (FUN_0041edc0)(void)
{
	while (g_tunnel != NULL)
		armc_freeRing(&GAME_VAR(TunnelRing *, 0x67fb3c));
	game_returnToMenus_41e9d0();
	g_screen = 300;
}

/* 0x41ed70: back to the main menu from the game room: the background tunnel freed, the menus entered again, the
   room's state cleared, state 300 */
void (FUN_0041ed70)(void)
{
	while (g_tunnel != NULL)
		armc_freeRing(&GAME_VAR(TunnelRing *, 0x67fb3c));
	game_returnToMenus_41e8b0();
	GAME_VAR(int, 0x9dd838) = 0;
	GAME_VAR(int, 0x9dd6a4) = 0;
	GAME_VAR(int, 0x9dd1b0) = 0;
	GAME_VAR(int, 0x9dd6d4) = 0;
	g_screen = 300;
}

/* 0x441770: the map-select dialog's OK: if a map is chosen (0x44-byte entries from 0x9ddac8), the dialog closes and
   the choice is kept */
void (mainmenu_441770)(void)
{
	int count = GAME_VAR(int, 0x9dd928);
	for (int i = 0; i < count; i++)
		if (GAME_VAR(int, 0x9ddac8 + i * 0x44) == 1) {
			sound_playMenu(0);
			GAME_VAR(int, 0x9eeab8) = GAME_VAR(int, 0x9dd928);
			GAME_VAR(int, 0x9db994) = 1;
			GAME_VAR(int, 0x9eeab4) = 0;
			return;
		}
}

/* 0x427920: the setup screen's frame: the background, then by tab the screen with its page, or the top page */
void (menuState600_setup)(void)
{
	menu_drawBackground();
	switch (g_setupTab) {
	case 2: setup_4230e0(); setup_4278d0(); break;
	case 0: setup_4230e0(); setup_427830(); break;
	case 1: setup_4230e0(); setup_427880(); break;
	case 0x29a: setup_4277c0(); setup_423330(); break;
	}
}
