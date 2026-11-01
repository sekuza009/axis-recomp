/* screen_enter.c: the front end's screens set up as they are entered: the main menu (state 300), the arena lobby
   (400), the setup screen (600) and the game room (800). Each lays out its panels (origins in menu units, then the
   screen's rectangle builders), sets its colours (RGBA floats), points the menu camera's target and look-at points
   at the screen (all at the camera's height) with the camera's current place as home, and clears its state. */
#include "../game.h"
#include <string.h>

#define I(a) GAME_VAR(int, a)
#define U(a) GAME_VAR(u32, a)
#define ONE 0x3f800000u

typedef struct { u32 address, value; } Store;

static void store_all(const Store *s, int n)
{
	for (int i = 0; i < n; i++)
		U(s[i].address) = s[i].value;
}
static void clear_all(const u32 *a, int n)
{
	for (int i = 0; i < n; i++)
		I(a[i]) = 0;
}
#define STORE_ALL(table) store_all(table, sizeof table / sizeof table[0])
#define CLEAR_ALL(table) clear_all(table, sizeof table / sizeof table[0])

/* the camera's target points 0 .. n-1 (16 bytes apart from 0x4df870, look-at points from 0x76d388) at its height,
   and the current position as home (0x9db090) */
static void camera_heights(int n)
{
	int z = g_menuCameraHeight;
	for (int i = 0; i < n; i++) {
		I(IMG(0x4df878) + i * 0x10) = z;
		I(IMG(0x76d390) + i * 0x10) = z;
	}
	g_menuCameraX = (*(int *)&g_menuCameraPos);
	g_menuCameraY = (*(int *)&g_armcCamHeight);
	g_menuCameraZ = (*(int *)&g_armcCamDistance);
}

/* the four target and look-at points of the lobby and setup screens: (+-35, 0) looking at (-+70, +-35) */
static const Store camera4[] = {
	{ IMG(0x4df870), 0x420c0000 }, { IMG(0x4df874), 0 }, { IMG(0x76d388), 0xc28c0000 }, { IMG(0x76d38c), 0x420c0000 },
	{ IMG(0x4df880), 0x420c0000 }, { IMG(0x4df884), 0 }, { IMG(0x76d398), 0xc28c0000 }, { IMG(0x76d39c), 0xc20c0000 },
	{ IMG(0x4df890), 0xc20c0000 }, { IMG(0x4df894), 0 }, { IMG(0x76d3a8), 0x428c0000 }, { IMG(0x76d3ac), 0x420c0000 },
	{ IMG(0x4df8a0), 0xc20c0000 }, { IMG(0x4df8a4), 0 }, { IMG(0x76d3b8), 0x428c0000 }, { IMG(0x76d3bc), 0xc20c0000 } };

/* 0x440bb0: the main menu: its camera (-300), its limits, colours, fade */
void (menuState300_enter)(void)
{
	g_mainMenuDepth = 0xc3960000;   /* -300 */
	g_mainMenuFrames = 0;
	(*(u32 *)&g_flareSizeB) = 0x41200000;   /* 10 */
	(*(u32 *)&g_flareSizeA) = 0x42400000;   /* 48 */
	(*(u32 *)&g_flareStepB) = 0x3e4ccccd;   /* 0.2 */
	(*(u32 *)&g_flareStepA) = 0xbe4ccccd;   /* -0.2 */
	(*(int *)&g_cursorBlink) = 0;
	g_menuIdleTime = 0;
	g_menuHintStep = 0x3d4ccccd;   /* 0.05 */
	g_menuHintClock = 0;
	g_mainMenuPicked = 0;
	g_mapSelectLitR = 0;
	g_mapSelectLitG = ONE;
	g_mapSelectLitB = ONE;
	g_mapSelectLitA = ONE;
	g_mapSelectDimR = 0x3e99999a;   /* (0.3, 0.7, 0.7, 1) */
	g_mapSelectDimG = 0x3f333333;
	g_mapSelectDimB = 0x3f333333;
	g_mapSelectDimA = ONE;
	g_matchMode = 0;
}

/* 0x404640: the arena lobby */
void (menuState400_enter)(void)
{
	static const Store layout[] = {
		{ IMG(0x4dbb60), 0 }, { IMG(0x4db51c), 5 }, { IMG(0x4dba70), 0x50 }, { IMG(0x4dba74), 0x96 }, { IMG(0x4dba78), 0x230 }, { IMG(0x4dba7c), 0x15e },
		{ IMG(0x4dbb70), 0x21c }, { IMG(0x4dbb74), 0x190 }, { IMG(0x4db8d0), 0x262 }, { IMG(0x4dbb00), 0x28 }, { IMG(0x4dbb04), 0x1e },
		{ IMG(0x4dbb08), 0x258 } };
	static const u32 cleared1[] = { IMG(0x4dbbd0), IMG(0x4dbab0), IMG(0x4db850), IMG(0x4db518), IMG(0x4dbacc), IMG(0x4dba90), IMG(0x4db858), IMG(0x4dbac8),
	                                IMG(0x4dbaa8), IMG(0x67ef30), IMG(0x4dba80) };
	static const u32 cleared2[] = { IMG(0x76d41c), IMG(0x680bb0), IMG(0x4df818), IMG(0x4dba84), IMG(0x4db854), IMG(0x4dba98), IMG(0x907b2c), IMG(0x4dbbf4) };
	static const Store state[] = {
		{ IMG(0x4dbb3c), 2 }, { IMG(0x907b24), 999 }, { IMG(0x4dba9c), ONE }, { IMG(0x4dbaa0), ONE }, { IMG(0x4dbaa4), ONE },
		{ IMG(0x4db8a0), 0x3e99999a }, { IMG(0x4db8a4), 0x3f333333 }, { IMG(0x4db8a8), 0x3f333333 }, { IMG(0x4db8ac), ONE }, { IMG(0x9fd958), 0xf },
		{ IMG(0x4dc24c), 1 } };
	g_matchMode = 1;
	arena_clearChatRecord();
	g_arenaNameDialogLeft = 0x64;
	g_arenaNameDialogTop = 0x64;
	(*(int *)&g_cursorBlink) = 0;
	g_arenaGameListLeft = 0x14;
	g_arenaGameListTop = 0x14;
	g_arenaTunnelDepth = 0xc4af0000;   /* -1400 */
	g_arenaGameListBottom = 0x1c2;
	g_newArenaFormBottom = 0x1c2;
	g_lobbyPanelsOff = 1;
	camera_heights(4);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = g_menuCameraHeight;
	STORE_ALL(layout);
	STORE_ALL(camera4);
	g_menuLookAtX = lx;
	g_menuLookAtY = ly;
	g_menuLookAtZ = lz;
	CLEAR_ALL(cleared1);
	lobbyTop_layout();
	arenaNameDialog_layout();
	arenaGameList_layout();
	arenaDialogBox_layout();
	arenaOptions_layout();
	arenaCreate_layout();
	CLEAR_ALL(cleared2);
	STORE_ALL(state);
}

/* 0x420770: the setup screen: its layout, camera, colours, and the two option columns' texts (0x80 apart in the
   text block at 0x75b5a4) */
void (menuState600_enterSetup)(void)
{
	static const Store layout[] = {
		{ IMG(0x4ddac8), 0x29a }, { IMG(0x4ddd90), 0xc4af0000 }, { IMG(0x4dda60), 1 }, { IMG(0x4de03c), 0 }, { IMG(0x4ddcec), 2 },
		{ IMG(0x4ddad0), 0x32 }, { IMG(0x4ddad4), 0x3c }, { IMG(0x4ddadc), 0x1a4 }, { IMG(0x4dddd0), 0x64 }, { IMG(0x4dddd8), 0x21c },
		{ IMG(0x4ddddc), 0x1c2 }, { IMG(0x4dde80), 0x28 }, { IMG(0x4dde8c), 0x1b8 } };
	static const Store colours[] = {
		{ IMG(0x4de048), 0 }, { IMG(0x4de04c), ONE }, { IMG(0x4de050), ONE }, { IMG(0x4de054), ONE }, { IMG(0x4ddae0), 0 },
		{ IMG(0x4ddae4), 0x3f19999a }, { IMG(0x4ddae8), 0x3f19999a }, { IMG(0x4ddaec), ONE }, { IMG(0x4e14fc), 0 }, { IMG(0x4deda8), ONE },
		{ IMG(0x9db978), 0 }, { IMG(0x4df010), ONE } };
	g_setupOptionsTop = 0x1e;
	g_setupControlTop = 0x1e;
	g_setupSoundRight = 0x24e;
	g_setupControlRight = 0x24e;
	camera_heights(4);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = g_menuCameraHeight;
	STORE_ALL(layout);
	STORE_ALL(camera4);
	g_menuLookAtX = lx;
	g_menuLookAtY = ly;
	g_menuLookAtZ = lz;
	setupSound_layout();
	setupOptions_layout();
	setupControl_layout();
	STORE_ALL(colours);
	for (int k = 0; k < 2; k++) {
		const char *text = (const char *)(IMG(0x75b7a4) + k * 0x80);
		int o = k * 0x32;
		strcpy((char *)(IMG(0x4ddbbc) + o), text - 0x200);
		strcpy((char *)(IMG(0x4dda64) + o), text - 0x100);
		strcpy((char *)(IMG(0x4ddc84) + o), text);
		strcpy((char *)(IMG(0x4de058) + o), text);
		strcpy((char *)(IMG(0x4ddc20) + o), text);
		strcpy((char *)(IMG(0x4ddaf0) + o), text);
	}
}

/* 0x432ff0: the game room: all its panels laid out, colours, the five camera points ((+-20, +-10) looking at
   (-+70, +-55)), the room's record and state cleared, 999 rooms */
void (menuState800_enterGameRoom)(void)
{
	static const Store layout[] = {
		{ IMG(0x9dd698), 0xc4af0000 }, { IMG(0x9dd7d8), 1 }, { IMG(0x9dd560), 0 }, { IMG(0x9dce48), 2 }, { IMG(0x9dd6bc), 0x3f333333 },
		{ IMG(0x9dd834), 0x42 }, { IMG(0x4dba88), 0 }, { IMG(0x9dd358), 0x32 }, { IMG(0x9dd35c), 0x6e }, { IMG(0x9dd360), 0x24e },
		{ IMG(0x9dd364), 0x172 }, { IMG(0x9dd368), 0x3c }, { IMG(0x9dd36c), 0x1e }, { IMG(0x9dd370), 0x244 }, { IMG(0x9dd374), 0x1c2 },
		{ IMG(0x9dd4a8), 0x14 }, { IMG(0x9dd4ac), 0x28 }, { IMG(0x9dd4b0), 0x26c }, { IMG(0x9dd4b4), 0x1b8 }, { IMG(0x9dd1b8), 0x28 },
		{ IMG(0x9dd1bc), 0x1e }, { IMG(0x9dd1c0), 0x258 }, { IMG(0x9dd1c4), 0x1c2 }, { IMG(0x9dced8), 0x10 }, { IMG(0x9dcedc), 0x1e },
		{ IMG(0x9dcee0), 0x268 }, { IMG(0x9dcee4), 0x1b8 } };
	static const Store colours_camera[] = {
		{ IMG(0x4ded60), 2 }, { IMG(0x9dcec0), 0 }, { IMG(0x9dcec4), ONE }, { IMG(0x9dcec8), ONE }, { IMG(0x9dcecc), ONE },
		{ IMG(0x9dd338), 0x3e99999a }, { IMG(0x9dd33c), 0x3f333333 }, { IMG(0x9dd340), 0x3f333333 }, { IMG(0x9dd344), ONE },
		{ IMG(0x4df870), 0x41a00000 }, { IMG(0x4df874), 0xc1200000 }, { IMG(0x76d388), 0xc28c0000 }, { IMG(0x76d38c), 0x425c0000 },
		{ IMG(0x4df880), 0x41a00000 }, { IMG(0x4df884), 0 }, { IMG(0x76d398), 0xc28c0000 }, { IMG(0x76d39c), 0 },
		{ IMG(0x4df890), 0x41a00000 }, { IMG(0x4df894), 0x41200000 }, { IMG(0x76d3a8), 0xc28c0000 }, { IMG(0x76d3ac), 0xc25c0000 },
		{ IMG(0x4df8a0), 0xc1a00000 }, { IMG(0x4df8a4), 0xc1200000 }, { IMG(0x76d3b8), 0x428c0000 }, { IMG(0x76d3bc), 0x425c0000 },
		{ IMG(0x4df8b0), 0xc1a00000 }, { IMG(0x4df8b4), 0 }, { IMG(0x76d3c8), 0x428c0000 }, { IMG(0x76d3cc), 0 } };
	static const u32 cleared[] = { IMG(0x9dd838), IMG(0x9dd6a4), IMG(0x9dd1b0), IMG(0x4ded54), IMG(0x9dd1c8), IMG(0x9dd350), IMG(0x9dd84c), IMG(0x9dd6d4),
	                               IMG(0x9dd850) };
	g_matchMode = 2;
	arena_clearChatRecord();
	STORE_ALL(layout);
	roomLogin_layout();
	account_layout();
	gameList_layout();
	gameListStop_layout();
	roomSettings_layout();
	ranking_layout();
	leaveDialog_layout();
	STORE_ALL(colours_camera);
	camera_heights(5);
	g_menuLookAtX = (*(int *)&g_menuCameraLook);
	g_menuLookAtY = (*(int *)&g_menuCameraLookY);
	g_menuLookAtZ = g_menuCameraHeight;
	memset((void *)IMG(0x9dd5a6), 0, 7 * 4 + 2);
	g_joinedTitleLevel = 0;
	g_joinedTitlePoints = 0;
	g_joinedTitleRating = 0;
	g_typingGameName = 0;
	g_typingGamePassword = 1;
	memset((void *)IMG(0x9dd5f8), 0, 5);
	g_typingRoomPassword = 1;
	g_typingRoomName = 0;
	g_loginToSend = 0;
	room_copyJoinedSettings();
	g_retypePassword = 1;
	CLEAR_ALL(cleared);
	g_roomListPages = 999;
}

/* ---- the front end's per-frame dispatch ---- */
#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x445e40: the frame's input (0x445c60), then, unless the game is leaving (0x680370), the message box's keys while
   it is shown, else the current screen's (0x76d3e8): 200 the title, 210 profiles, 300 the main menu, 400 the lobby,
   500 missions, 600 setup, 700 the ARM CENTER, 800 the game room, 900 skirmish, 9999 in a match. Returns what the
   handler leaves in eax (or the original's leftover of its compares) */
u32 (menu_onStateChange)(void)
{
	GAME_FN(input_updateMenuCursor, 0x445c60, u32, void)();
	if (g_keysBlocked)
		return (*(u32 *)&g_keysBlocked);
	if (g_dialogPending)
		return GAME_FN(messageBox_clickClose, 0x445e10, u32, void)();   /* the message box */
	int state = g_menuState;
	switch (state) {
	case 200: return GAME_FN(menu_clickStartFade, 0x445de0, u32, void)();
	case 210: return GAME_FN(profile_processInput, 0x44c560, u32, void)();   /* profile_processInput */
	case 300: return GAME_FN(mainmenu_startNetGame, 0x4419d0, u32, void)();
	case 400: return GAME_FN(lobby_onStateChange, 0x4076c0, u32, void)();   /* lobby_onStateChange */
	case 500: return GAME_FN(mission_unlockCheat, 0x447b10, u32, void)();
	case 600: return GAME_FN(setup_drawTab, 0x422b30, u32, void)();
	case 700: return GAME_FN(armc_onStateEnter, 0x410190, u32, void)();   /* armc_onStateEnter */
	case 800: return GAME_FN(room_processKeys, 0x436800, u32, void)();   /* room_processKeys */
	case 900: return GAME_FN(settingsPage_draw, 0x443ef0, u32, void)();
	case 9999: return GAME_FN(armc_mouseLook, 0x42ab70, u32, void)();  /* armc_mouseLook */
	}
	/* the original's subtraction chain leaves these */
	if (state > 900)
		return (u32)state;
	if (state > 600)
		return (u32)(state - 800);
	if (state > 300)
		return (u32)(state - 500);
	return (u32)(state - 210);
}

/* 0x41f970: a screen entered: its set-up by the state (0x76d3e8; the main menu also flags 0x4deb48), the state kept as
   the one before (0x67ef0c). Returns the state */
u32 (menu_enterState)(void)
{
	switch (g_menuState) {
	case 210: GAME_FN(menuState210_enter, 0x44b420, u32, void)(); break;   /* menuState210_enter */
	case 300:
		g_enteringMenus = 1;
		GAME_FN(menuState300_enter, 0x440bb0, u32, void)();                 /* menuState300_enter */
		break;
	case 400: GAME_FN(menuState400_enter, 0x404640, u32, void)(); break;   /* menuState400_enter */
	case 500: GAME_FN(menuState500_enter, 0x447750, u32, void)(); break;   /* menuState500_enter */
	case 600: GAME_FN(menuState600_enterSetup, 0x420770, u32, void)(); break;   /* menuState600_enterSetup */
	case 800: GAME_FN(menuState800_enterGameRoom, 0x432ff0, u32, void)(); break;   /* menuState800_enterGameRoom */
	case 900: GAME_FN(menuState900_enterSkirmish, 0x443950, u32, void)(); break;   /* menuState900_enterSkirmish */
	case 9999: GAME_FN(console_init, 0x41fd40, u32, void)(); break;  /* console_init */
	}
	g_lastScreen = g_menuState;
	return (u32)g_menuState;
}


/* the skirmish and mission screens' camera: at (0, 0, -450) moving to (0, 0, -550), that place its home, one target
   point (0, 0, 100) looking at the origin */
static const Store briefing_camera[] = {
	{ IMG(0x4df024), 0 }, { IMG(0x4df028), 0 }, { IMG(0x4df02c), 0xc3e10000 }, { IMG(0x680378), 0 }, { IMG(0x68037c), 0 },
	{ IMG(0x680380), 0xc4098000 }, { IMG(0x4df870), 0 }, { IMG(0x4df874), 0 }, { IMG(0x4df878), 0x42c80000 }, { IMG(0x76d388), 0 },
	{ IMG(0x76d38c), 0 }, { IMG(0x76d390), 0 }, { IMG(0x9db090), 0 }, { IMG(0x9db094), 0 }, { IMG(0x9db098), 0xc3e10000 }, { IMG(0x76d3f8), 0 },
	{ IMG(0x76d3fc), 0 }, { IMG(0x76d400), 0xc4098000 } };

/* 0x443950: the skirmish setup (screen 900): the briefing camera, the briefing window and its colours, the page's
   panels (skirmish_layout, skirmishButtons_layout), the page set to 10 (skirmish settings) with a sound, the mission list
   loaded (mission_loadAxisMis) and its state cleared. Returns 0 (the original's eax) */
int (menuState900_enterSkirmish)(void)
{
	static const Store setup[] = {
		{ IMG(0x9f16a8), 0xa }, { IMG(0x9f16ac), 0x14 }, { IMG(0x9f16b0), 0x276 }, { IMG(0x9f16b4), 0x1cc }, { IMG(0x9ef208), 0 },
		{ IMG(0x9ef20c), ONE }, { IMG(0x9ef210), ONE }, { IMG(0x9ef214), ONE }, { IMG(0x9eeac8), 0 }, { IMG(0x9eeacc), 0x3f19999a },
		{ IMG(0x9eead0), 0x3f19999a }, { IMG(0x9eead4), ONE }, { IMG(0x9ef1f0), 1 }, { IMG(0x76d3e8), 900 }, { IMG(0x67ef0c), 900 },
		{ IMG(0x67ef20), 900 } };
	static const u32 cleared[] = { IMG(0x9f16bc), IMG(0x9f1058), IMG(0x9f16a4), IMG(0x680bb4), IMG(0x76d37c) };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	GAME_FN(skirmish_layout, 0x4437b0, void, void)();   /* skirmish_layout */
	GAME_FN(skirmishButtons_layout, 0x443840, void, void)();   /* skirmishButtons_layout */
	g_skirmishDrawBackground = 1;
	g_settingsPage = 10;
	sound_playMenu(4);
	GAME_FN(mission_loadAxisMis, 0x4435f0, void, void)();   /* mission_loadAxisMis */
	CLEAR_ALL(cleared);
	return 0;
}

/* 0x447750: the mission select (screen 500): the briefing camera, the window and its colours, the screen's panels
   (mission_447660), the mission shown (0x9f63b4, 0x9f6328) the campaign's next one (0x9f181c, at most 14), a sound;
   a newly reached mission (past 0x9f62fc) raises it and the briefing flag 0x9f62e0. Returns the campaign's mission */
int (menuState500_enter)(void)
{
	static const Store setup[] = {
		{ IMG(0x9f6308), 0x28 }, { IMG(0x9f630c), 0xa }, { IMG(0x9f6310), 0x258 }, { IMG(0x9f6314), 0x1cc }, { IMG(0x9f6318), 0 },
		{ IMG(0x9f631c), ONE }, { IMG(0x9f6320), ONE }, { IMG(0x9f6324), ONE }, { IMG(0x9f62e8), 0 }, { IMG(0x9f62ec), 0x3f19999a },
		{ IMG(0x9f62f0), 0x3f19999a }, { IMG(0x9f62f4), ONE }, { IMG(0x9f62f8), 1 }, { IMG(0x76d3e8), 500 }, { IMG(0x67ef0c), 500 },
		{ IMG(0x67ef20), 500 } };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	GAME_FN(missionsel_layout, 0x447660, void, void)();   /* mission_447660 */
	g_missionShowBackground = 1;
	g_missionBusy = 0;
	int mission = g_progress < 15 ? g_progress : 14;
	g_missionShown = mission;
	g_missionChosen = mission;
	g_missionPreviewDue = 1;
	sound_playMenu(4);
	g_missionStarted = 0;
	if (g_progress > g_profileProgressSaved) {
		g_missionStarted = 1;
		g_profileProgressSaved = g_progress;
	}
	return g_progress;
}

/* 0x44b420: the pilot screen (state 210): its panels laid out, the profiles' header read back (profile_create) with
   the current one selected and scrolled into the 13 visible rows, the new-pilot dialog up when there are none, the
   message box and the screen's rectangles (profilePage_layout, 44b030 .. 44b1a0), its colours, then the list shown
   (profile_resetPreview). Returns that call's eax */
u32 (menuState210_enter)(void)
{
	static const Store layout[] = {
		{ IMG(0x9f8e48), 0x3c }, { IMG(0x9f8e4c), 0x3c }, { IMG(0x9f8f28), 0x10e }, { IMG(0x9f93c0), 0x10e }, { IMG(0x9f8ea0), 0x244 },
		{ IMG(0x9f8ea4), 0x1a4 }, { IMG(0x9f8eac), 0x78 }, { IMG(0x9f8ea8), 0x96 }, { IMG(0x9f8f20), 0x208 }, { IMG(0x9f8f24), 0x118 },
		{ IMG(0x9f8f1c), 0x78 }, { IMG(0x9f8f0c), 0x96 }, { IMG(0x9f8f2c), 0x208 }, { IMG(0x9f6834), 0x78 }, { IMG(0x9f683c), 0x96 },
		{ IMG(0x9f93bc), 0x208 }, { IMG(0x9f8c54), 0x1e }, { IMG(0x9f8c50), 0x14 }, { IMG(0x9f6830), 0x262 }, { IMG(0x9f682c), 0x1c2 } };
	static const u32 cleared[] = { IMG(0x9f8d70), IMG(0x9f6840), IMG(0x9f8c4c), IMG(0x9f8c5c), IMG(0x9f8d74), IMG(0x9f8c58), IMG(0x680bb4), IMG(0x76d37c),
	                               IMG(0x76d42c) };
	static const Store colours[] = {
		{ IMG(0x9f8eb0), 0 }, { IMG(0x9f8eb4), ONE }, { IMG(0x9f8eb8), ONE }, { IMG(0x9f8ebc), ONE }, { IMG(0x9f8d58), 0 },
		{ IMG(0x9f8d5c), 0x3f19999a }, { IMG(0x9f8d60), 0x3f19999a }, { IMG(0x9f8d64), ONE }, { IMG(0x4dda44), 0 }, { IMG(0x4dda48), 0 },
		{ IMG(0x9f6838), 0 }, { IMG(0x9f900c), 0 }, { IMG(0x9f8f18), 0 } };
	static const u32 rects[7] = { FN_ADDR(profilePage_layout, 0x44af30), FN_ADDR(newNameDialog_layout, 0x44b030), FN_ADDR(profileDialogBox_layout, 0x44b080), FN_ADDR(deleteDialog_layout, 0x44b0b0), FN_ADDR(secondDialog_layout, 0x44b100), FN_ADDR(profileList_layout, 0x44b150), FN_ADDR(pilotSelect_layout, 0x44b1a0) };
	STORE_ALL(layout);
	CLEAR_ALL(cleared);
	profile_create();   /* profile_create: the header read back */
	int current = g_currentProfile;
	g_pilotChosen = current;
	g_profileListRow = current;
	if (current >= 13) {
		g_profileListRow = 12;
		g_profileListTop = current - 12;
	}
	if (g_profileCount == 0)
		g_profileScreenReady = 1;
	g_menuFramePhase = 1;
	g_menuFrameCounter = 0;
	g_dialogOpen = 1;
	g_profilePage = 1;
	for (int k = 0; k < 7; k++)
		GAME_CDECL(rects[k], void, void)();
	STORE_ALL(colours);
	return GAME_FN(profile_resetPreview, 0x44b7a0, u32, void)();   /* profile_resetPreview */
}

/* the profile files checked (the English one, then four times the Korean one): a missing one ends the game with
   the message 0x4b04b0 */
static void check_profiles(void)
{
	for (int k = 0; k < 5; k++)
		if (!(k == 0 ? app_checkFile_profeng() : app_checkFile_profkor())) {
			sys_messageBox((const char *)IMG(0x4b04b0));
			GAME_CDECL(0x49edac, void, int)(-1);   /* exit */
		}
}

/* the player's name for the match (0x4dedd8, 32 bytes) */
static void match_name(const char *name)
{
	memset((void *)IMG(0x4dedd8), 0, 32);
	strcpy((char *)IMG(0x4dedd8), name);
}

/* 0x41fd40 (named console_init; by use the match started, state 9999): the menus' tunnel freed; outside the lobby
   (0x76d410) the profile files checked; the display opened (aspect 0x4e1870, glWindow_init); a replay (0x9db990)
   started at once (app_requireCd 0, 3); else the map (0x9dad94) loaded (failing: message 6 and back to state 400 /
   800 for the arena / room). By the kind of match (0x5ae9c4): 1 the arena, 2 the room (the pilots read, the
   player's name taken from the profile / the room, the part lists 0x40d990), 3 a skirmish (the name 0x9f1798),
   started with app_requireCd (a host unless 0x67ef04 is 1; 3: 0, 0); then the map's name announced. The caller
   ignores the eax it leaves */
void (console_init)(void)
{
	while (g_menuTunnel)   /* the menus' tunnel, ring by ring */
		tunnel_removeLastRing((TunnelRing **)IMG(0x67fb3c));
	if (!g_startedFromLobby)
		check_profiles();
	g_matchRunning = 1;
	g_viewAspect = f32((long double)g_screenW / (long double)g_screenH);
	sys_checkClockTampering();
	glWindow_init((const char *)IMG(0x4b04a0), g_screenW, g_screenH, g_videoDepth, 0x10, 0, g_hWndMain, (*(int *)&g_desktopDC));
#define scene GAME_VAR(Scene *, 0x9087b4)   /* read at each use: loading the map makes the match's scene */
	if (g_replayRunning) {
		g_matchMode = 0;
		app_requireCd(scene, 0, 3);
		return;
	}
	int loaded = console_loadFile(g_missionStage);
	int kind = g_matchMode;   /* (after the load, as the original reads it) */
	if (!loaded) {
		if (kind == 1)
			g_menuState = 400;
		else if (kind == 2)
			g_menuState = 800;
		menu_showMessage(6);
		return;
	}
	switch (kind) {
	case 1:   /* (the selection's range checks are jumped over in the patched game) */
		data_loadPilotProfiles();
		match_name((const char *)IMG(0x4dedb0));
		armc_resetSeraphimParts();
		app_requireCd(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 2:
		room_fitWindowRects();
		if (g_pilotLevel != 0x14)
			armc_resetSeraphimParts();
		data_loadPilotProfiles();
		match_name((const char *)IMG(0x9dd570));
		app_requireCd(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 3:
		match_name((const char *)IMG(0x9f1798));
		app_requireCd(scene, 0, 0);
		break;
	}
	scene_setTextureFolder(scene, (const char *)(IMG(0x907b30) + g_missionStage * 0x20));   /* (the original also builds "%s" with the name on its stack, unused) */
#undef scene
}
