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

/* 0x44aee0: the room's text (0x9dd570) copied to 0x4de700, and match_4327f0 when it is not empty */
void (match_44aee0)(void)
{
	const char *from = (const char *)0x9dd570;
	char *to = (char *)0x4de700;
	int i = 0;
	do
		to[i] = from[i];
	while (from[i++] != '\0');
	if (to[0] != '\0')
		match_4327f0();
}

/* a panel sliding in: while flag is set, eased moves a tenth of the way to the constant at 0x4a9448 per time unit
   and slid moves back by the same step, until slid is no longer above the double at 0x4a9440 (then the flag drops
   and slid is set to -1650). Afterwards, while the quit question is up, the keys are held and the next screen set
   to 9999 (returns 1) */
static int menu_slide(u32 flag, u32 eased, u32 slid)
{
	if (GAME_VAR(int, flag)) {
		volatile long double d = (long double)GAME_VAR(float, 0x4a9448) - GAME_VAR(float, eased);
		d = d * g_frameTime;
		d = d * GAME_VAR(float, 0x4a93ec);
		volatile long double e = (long double)GAME_VAR(float, eased) + d;
		GAME_VAR(float, eased) = (float)e;
		long double s = GAME_VAR(float, slid);
		if (s > GAME_VAR(double, 0x4a9440)) {
			volatile long double t = s - d;
			GAME_VAR(float, slid) = (float)t;
		} else {
			GAME_VAR(int, flag) = 0;
			GAME_VAR(u32, slid) = 0xc4ce4000;   /* -1650.0 */
		}
	}
	if (!g_quitAsked)
		return 0;
	set_680370_441250(1);
	g_nextScreen = 9999;
	return 1;
}

/* 0x40cef0 (lobbyTop_draw), 0x43e720: the lobby's and the room's panels */
int (lobbyTop_draw)(void) { return menu_slide(0x4db85c, 0x4dbb60, 0x4dba68); }
int (room_43e720)(void) { return menu_slide(0x9dd7d8, 0x9dd560, 0x9dd698); }

/* ---- back to the menus after a game: the arena session left (0x452fe0) and, unless kept, the connection closed;
   the player slots (0x410 bytes from 0x9f9840) emptied ---- */
static void leave_game(u32 lobby, int disconnect)
{
	GAME_VAR(int, 0x67ef14) = 0;
	GAME_VAR(u32, 0x5ae9c4) = lobby;
	GAME_CDECL(0x452fe0, void, void)();       /* arena_452fe0 */
	if (disconnect)
		GAME_CDECL(0x451e60, void, void)();   /* net_disconnect */
	GAME_VAR(int, 0x4dbbf4) = 0;
	for (u32 p = 0x9f9844; p < 0x9fd944; p += 0x410) {
		GAME_VAR(int, p - 4) = 0;
		GAME_VAR(int, p) = 0;
	}
}
/* the menu cameras placed (both at (0, 0, z), the far one at farZ, the near one at nearZ: float bits), the keys
   blocked as given, 0x4deb48 set (and 0x4e1868 cleared when asked), the menu state cleared and the keyboard taken back if it was let go. Returns
   what the original leaves in eax: input_initKeyboard's, or 0x68039c's value */
static u32 reset_menus(u32 farZ, u32 nearZ, int blocked, int deb48, int clear_4e1868)
{
	u32 typing = GAME_VAR(u32, 0x68039c);
	GAME_VAR(u32, 0x4df028) = 0;
	GAME_VAR(u32, 0x4df024) = 0;
	GAME_VAR(u32, 0x4df02c) = farZ;
	GAME_VAR(u32, 0x680378) = 0;
	GAME_VAR(u32, 0x68037c) = 0;
	GAME_VAR(u32, 0x680380) = nearZ;
	GAME_VAR(int, 0x680370) = blocked;
	GAME_VAR(int, 0x4df8e0) = 0;
	GAME_VAR(u32, 0x9dd930) = 0;
	GAME_VAR(u32, 0x9dd934) = 0;
	GAME_VAR(u32, 0x9dd938) = farZ;
	GAME_VAR(u32, 0x9dd918) = 0;
	GAME_VAR(u32, 0x9dd91c) = 0;
	GAME_VAR(u32, 0x9dd920) = nearZ;
	GAME_VAR(int, 0x4deb48) = deb48;
	GAME_VAR(int, 0x9db990) = 0;
	GAME_VAR(int, 0x4dda44) = 0;
	GAME_VAR(int, 0x4dda48) = 0;
	if (clear_4e1868)
		GAME_VAR(int, 0x4e1868) = 0;
	if (typing != 1)
		return typing;
	GAME_VAR(int, 0x68039c) = 0;
	GAME_CDECL(0x431590, void, void)();   /* match_431590 */
	return GAME_CDECL(0x401310, u32, void *)(GAME_VAR(void *, 0x4ded18));   /* input_initKeyboard */
}
#define FAR_BACK 0xc3e10000u    /* -450 */
#define NEAR_BACK 0xc4098000u   /* -550 */

/* 0x41ec50: to screen 500 */
u32 (game_returnToMenus_41ec50)(void)
{
	leave_game(0, 1);
	GAME_VAR(int, 0x76d3e8) = 500;
	g_nextScreen = 500;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	return reset_menus(FAR_BACK, NEAR_BACK, 0, 0, 0);
}

/* 0x41e8b0: to the main menu (300), the cameras in front (500, 400), 0x4deb48 set and 0x4e1868 cleared. Returns 1
   when the keyboard was not let go */
u32 (game_returnToMenus_41e8b0)(void)
{
	leave_game(0, 1);
	GAME_VAR(int, 0x76d3e8) = 300;
	g_nextScreen = 300;
	GAME_CDECL(0x4411e0, void, void)();
	u32 typing = GAME_VAR(u32, 0x68039c);
	u32 r = reset_menus(0x43fa0000, 0x43c80000, 2, 1, 1);
	return typing == 1 ? r : 1;
}

/* 0x41e9d0: to screen 400, the previous screen 300 */
u32 (game_returnToMenus_41e9d0)(void)
{
	leave_game(0, 1);
	g_nextScreen = 400;
	GAME_VAR(int, 0x76d3e8) = 300;
	GAME_VAR(int, 0x67ef0c) = 300;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	return reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
}

/* 0x41eb00: back to the game room (800; lobby state 2, the connection kept): the room's state cleared too */
u32 (game_returnToMenus_41eb00)(void)
{
	leave_game(2, 0);
	GAME_VAR(int, 0x9dd834) = 0x63;
	GAME_VAR(int, 0x76d3e8) = 800;
	g_nextScreen = 800;
	GAME_VAR(int, 0x67ef0c) = 800;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	u32 r = reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
	GAME_VAR(int, 0x9dced0) = 0;
	GAME_VAR(int, 0x4ded54) = 0;
	GAME_VAR(int, 0x9dd1c8) = 0;
	GAME_VAR(int, 0x9dd350) = 0;
	return r;
}
