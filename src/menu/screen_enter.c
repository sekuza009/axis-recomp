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
		I(ADDR(g_camPoint0Z) + i * 0x10) = z;
		I(ADDR(g_camAim0Z) + i * 0x10) = z;
	}
	g_menuCameraX = (*(int *)&g_menuCameraPos);
	g_menuCameraY = (*(int *)&g_armcCamHeight);
	g_menuCameraZ = (*(int *)&g_armcCamDistance);
}

/* the four target and look-at points of the lobby and setup screens: (+-35, 0) looking at (-+70, +-35) */
static const Store camera4[] = {
	{ ADDR(g_camPoint0X), 0x420c0000 }, { ADDR(g_camPoint0Y), 0 }, { ADDR(g_camAim0X), 0xc28c0000 }, { ADDR(g_camAim0Y), 0x420c0000 },
	{ ADDR(g_camPoint1X), 0x420c0000 }, { (OBJ(g_camPoints) + 0x14), 0 }, { ADDR(g_camAim1X), 0xc28c0000 }, { ADDR(g_camAim1Y), 0xc20c0000 },
	{ ADDR(g_camPoint2X), 0xc20c0000 }, { ADDR(g_camPoint2Y), 0 }, { ADDR(g_camAim2X), 0x428c0000 }, { ADDR(g_camAim2Y), 0x420c0000 },
	{ (OBJ(g_camPoints) + 0x30), 0xc20c0000 }, { (OBJ(g_camPoints) + 0x34), 0 }, { (OBJ(g_camAims) + 0x30), 0x428c0000 }, { (OBJ(g_camAims) + 0x34), 0xc20c0000 } };

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
	g_replaySelectLitR = 0;
	g_replaySelectLitG = ONE;
	g_replaySelectLitB = ONE;
	g_replaySelectLitA = ONE;
	g_replaySelectDimR = 0x3e99999a;   /* (0.3, 0.7, 0.7, 1) */
	g_replaySelectDimG = 0x3f333333;
	g_replaySelectDimB = 0x3f333333;
	g_replaySelectDimA = ONE;
	g_matchMode = 0;
}

/* 0x404640: the arena lobby */
void (menuState400_enter)(void)
{
	static const Store layout[] = {
		{ OBJ(g_lobbyTopEase), 0 }, { ADDR(g_lobbySubState), 5 }, { OBJ(g_lobbyTopRect), 0x50 }, { (OBJ(g_lobbyTopRect) + 0x4), 0x96 }, { (OBJ(g_lobbyTopRect) + 0x8), 0x230 }, { (OBJ(g_lobbyTopRect) + 0xc), 0x15e },
		{ ADDR(g_arenaNameDialogRight), 0x21c }, { ADDR(g_arenaNameDialogBottom), 0x190 }, { ADDR(g_arenaGameListRight), 0x262 }, { ADDR(g_newArenaFormLeft), 0x28 }, { ADDR(g_newArenaFormTop), 0x1e },
		{ ADDR(g_newArenaFormRight), 0x258 } };
	static const u32 cleared1[] = { ADDR(g_typingArenaName), ADDR(g_editingNewArenaName), ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword), ADDR(g_lanSearch), ADDR(g_lobbySearching), ADDR(g_arenaHaveList),
	                                ADDR(g_arenaListFull), ADDR(g_gameCount), ADDR(g_lobbyBlinkClock) };
	static const u32 cleared2[] = { ADDR(g_localPlayer), ADDR(g_gameListTop), ADDR(g_lobbyListRow), ADDR(g_arenaSearchStarted), ADDR(g_serverSearching), OBJ(g_arenaBright), ADDR(g_arenaUpdateNotice), ADDR(g_arenaLobbyState) };
	static const Store state[] = {
		{ ADDR(g_arenaCameraMode), 2 }, { ADDR(g_lastPanel), 999 }, { (OBJ(g_arenaBright) + 0x4), ONE }, { (OBJ(g_arenaBright) + 0x8), ONE }, { (OBJ(g_arenaBright) + 0xc), ONE },
		{ OBJ(g_arenaDim), 0x3e99999a }, { (OBJ(g_arenaDim) + 0x4), 0x3f333333 }, { (OBJ(g_arenaDim) + 0x8), 0x3f333333 }, { (OBJ(g_arenaDim) + 0xc), ONE }, { ADDR(g_unusedArenaWord), 0xf },
		{ ADDR(g_armcFrom), 1 } };
	g_matchMode = 1;
	arena_clearSessionEntry();
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
   text block at MSG(431, "16BIT COLOR")) */
void (menuState600_enterSetup)(void)
{
	static const Store layout[] = {
		{ ADDR(g_setupTab), 0x29a }, { ADDR(g_setupTunnelDepth), 0xc4af0000 }, { ADDR(g_setupPanelMoving), 1 }, { ADDR(g_setupPanelPos), 0 }, { ADDR(g_setupPage), 2 },
		{ ADDR(g_setupSoundLeft), 0x32 }, { (OBJ(g_setupSoundRect) + 0x4), 0x3c }, { (OBJ(g_setupSoundRect) + 0xc), 0x1a4 }, { OBJ(g_setupGraphicRect), 0x64 }, { (OBJ(g_setupGraphicRect) + 0x8), 0x21c },
		{ (OBJ(g_setupGraphicRect) + 0xc), 0x1c2 }, { ADDR(g_setupControlLeft), 0x28 }, { (OBJ(g_setupControlRect) + 0xc), 0x1b8 } };
	static const Store colours[] = {
		{ OBJ(g_setupColourLit), 0 }, { (OBJ(g_setupColourLit) + 0x4), ONE }, { (OBJ(g_setupColourLit) + 0x8), ONE }, { (OBJ(g_setupColourLit) + 0xc), ONE }, { OBJ(g_setupColourDim), 0 },
		{ (OBJ(g_setupColourDim) + 0x4), 0x3f19999a }, { (OBJ(g_setupColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_setupColourDim) + 0xc), ONE }, { ADDR(g_scroll), 0 }, { ADDR(g_menuTunnelSpeed), ONE },
		{ ADDR(g_tunnelPulse), 0 }, { ADDR(g_tunnelPulseStep), ONE } };
	g_setupGraphicTop = 0x1e;
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
	setupGraphic_layout();
	setupControl_layout();
	STORE_ALL(colours);
	for (int k = 0; k < 2; k++) {
		const char *text = (const char *)(MSG(435, "OFF") + k * 0x80);
		int o = k * 0x32;
		strcpy((char *)(OBJ(g_colourDepthTexts) + o), text - 0x200);
		strcpy((char *)(OBJ(g_fxStatusTexts) + o), text - 0x100);
		strcpy((char *)(OBJ(g_linearFilterTexts) + o), text);
		strcpy((char *)(OBJ(g_mipMapTexts) + o), text);
		strcpy((char *)(OBJ(g_viewFpsTexts) + o), text);
		strcpy((char *)(OBJ(g_simpleMenuTexts) + o), text);
	}
}

/* 0x432ff0: the game room: all its panels laid out, colours, the five camera points ((+-20, +-10) looking at
   (-+70, +-55)), the room's record and state cleared, 999 rooms */
void (menuState800_enterGameRoom)(void)
{
	static const Store layout[] = {
		{ ADDR(g_roomTunnelDepth), 0xc4af0000 }, { ADDR(g_roomDialogOpen), 1 }, { ADDR(g_roomPanelEase), 0 }, { ADDR(g_roomCameraMode), 2 }, { ADDR(g_roomPanelBrightness), 0x3f333333 },
		{ ADDR(g_roomState), 0x42 }, { ADDR(g_connectionAwaited), 0 }, { ADDR(g_roomLoginLeft), 0x32 }, { ADDR(g_roomLoginTop), 0x6e }, { ADDR(g_roomLoginRight), 0x24e },
		{ ADDR(g_roomLoginBottom), 0x172 }, { ADDR(g_accountPanelLeft), 0x3c }, { ADDR(g_accountPanelTop), 0x1e }, { ADDR(g_accountPanelRight), 0x244 }, { ADDR(g_accountPanelBottom), 0x1c2 },
		{ ADDR(g_roomGameListLeft), 0x14 }, { ADDR(g_roomGameListTop), 0x28 }, { ADDR(g_roomGameListRight), 0x26c }, { ADDR(g_roomGameListBottom), 0x1b8 }, { ADDR(g_roomFormLeft), 0x28 },
		{ ADDR(g_roomFormTop), 0x1e }, { ADDR(g_roomFormRight), 0x258 }, { ADDR(g_roomFormBottom), 0x1c2 }, { OBJ(g_roomMessageRect), 0x10 }, { (OBJ(g_roomMessageRect) + 0x4), 0x1e },
		{ (OBJ(g_roomMessageRect) + 0x8), 0x268 }, { (OBJ(g_roomMessageRect) + 0xc), 0x1b8 } };
	static const Store colours_camera[] = {
		{ ADDR(g_connectStep), 2 }, { OBJ(g_roomBright), 0 }, { (OBJ(g_roomBright) + 0x4), ONE }, { (OBJ(g_roomBright) + 0x8), ONE }, { (OBJ(g_roomBright) + 0xc), ONE },
		{ OBJ(g_roomDim), 0x3e99999a }, { (OBJ(g_roomDim) + 0x4), 0x3f333333 }, { (OBJ(g_roomDim) + 0x8), 0x3f333333 }, { (OBJ(g_roomDim) + 0xc), ONE },
		{ ADDR(g_camPoint0X), 0x41a00000 }, { ADDR(g_camPoint0Y), 0xc1200000 }, { ADDR(g_camAim0X), 0xc28c0000 }, { ADDR(g_camAim0Y), 0x425c0000 },
		{ ADDR(g_camPoint1X), 0x41a00000 }, { (OBJ(g_camPoints) + 0x14), 0 }, { ADDR(g_camAim1X), 0xc28c0000 }, { ADDR(g_camAim1Y), 0 },
		{ ADDR(g_camPoint2X), 0x41a00000 }, { ADDR(g_camPoint2Y), 0x41200000 }, { ADDR(g_camAim2X), 0xc28c0000 }, { ADDR(g_camAim2Y), 0xc25c0000 },
		{ (OBJ(g_camPoints) + 0x30), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x34), 0xc1200000 }, { (OBJ(g_camAims) + 0x30), 0x428c0000 }, { (OBJ(g_camAims) + 0x34), 0x425c0000 },
		{ (OBJ(g_camPoints) + 0x40), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x44), 0 }, { (OBJ(g_camAims) + 0x40), 0x428c0000 }, { (OBJ(g_camAims) + 0x44), 0 } };
	static const u32 cleared[] = { ADDR(g_roomRequestOut), ADDR(g_roomAnswerAwaited), ADDR(g_unusedRoomWord), ADDR(g_arenaGameSetUp), ADDR(g_roomLoginDue), ADDR(g_rankingRequestPending), ADDR(g_roomConnected), ADDR(g_roomAwaitingServer),
	                               ADDR(g_roomUpdateNotice) };
	g_matchMode = 2;
	arena_clearSessionEntry();
	STORE_ALL(layout);
	roomLogin_layout();
	account_layout();
	gameList_layout();
	gameListStop_layout();
	roomSettings_layout();
	ranking_layout();
	updateNotice_layout();
	STORE_ALL(colours_camera);
	camera_heights(5);
	g_menuLookAtX = (*(int *)&g_menuCameraLook);
	g_menuLookAtY = (*(int *)&g_menuCameraLookY);
	g_menuLookAtZ = g_menuCameraHeight;
	memset((void *)OBJ(g_ladderEmail), 0, 7 * 4 + 2);
	g_ladderPassword = 0;
	g_ladderPassword4 = 0;
	g_ladderPassword8 = 0;
	g_typingLoginId = 0;
	g_typingLoginPassword = 1;
	memset((void *)OBJ(g_roomMech), 0, 5);
	g_lineToLoginPassword = 1;
	g_lineToLoginId = 0;
	g_loginToSend = 0;
	room_copyJoinedSettings();
	g_retypePassword = 1;
	CLEAR_ALL(cleared);
	g_roomListPages = 999;
}

/* ---- the front end's per-frame dispatch ---- */

/* 0x445e40: the menus' mouse, once per frame: the mouse read (input_updateMouse), then, unless the menu camera is moving
   (g_menuCameraMove), the message box's clicks while it is shown, else the current screen's (0x76d3e8): 200 the title, 210 profiles, 300 the main menu, 400 the lobby,
   500 missions, 600 setup, 700 the ARM CENTER, 800 the game room, 900 skirmish, 9999 in a match. Returns what the
   handler leaves in eax (or the original's leftover of its compares) */
u32 (menu_processMouse)(void)
{
	input_updateMouse();
	if (g_menuCameraMove)
		return (*(u32 *)&g_menuCameraMove);
	if (g_dialogPending)
		return messageBox_clickClose();   /* the message box */
	int state = g_menuState;
	switch (state) {
	case 200: return menu_clickStartFade();
	case 210: return profile_processInput();   /* profile_processInput */
	case 300: return mainmenu_clicks();
	case 400: return lobby_clicks();   /* lobby_clicks */
	case 500: return missionSelect_clicks();
	case 600: return setup_tabClicks();
	case 700: return armc_mouse();   /* armc_mouse */
	case 800: return room_clicksByState();
	case 900: return skirmish_pageClicks();
	case 9999: return armc_mouseLook();  /* armc_mouseLook */
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
	case 210: menuState210_enter(); break;   /* menuState210_enter */
	case 300:
		g_enteringMenus = 1;
		menuState300_enter();                 /* menuState300_enter */
		break;
	case 400: menuState400_enter(); break;   /* menuState400_enter */
	case 500: menuState500_enter(); break;   /* menuState500_enter */
	case 600: menuState600_enterSetup(); break;   /* menuState600_enterSetup */
	case 800: menuState800_enterGameRoom(); break;   /* menuState800_enterGameRoom */
	case 900: menuState900_enterSkirmish(); break;   /* menuState900_enterSkirmish */
	case 9999: match_enter(); break;  /* match_enter */
	}
	g_lastScreen = g_menuState;
	return (u32)g_menuState;
}


/* the skirmish and mission screens' camera: at (0, 0, -450) moving to (0, 0, -550), that place its home, one target
   point (0, 0, 100) looking at the origin */
static const Store briefing_camera[] = {
	{ ADDR(g_menuCameraPos), 0 }, { ADDR(g_armcCamHeight), 0 }, { ADDR(g_armcCamDistance), 0xc3e10000 }, { ADDR(g_menuCameraLook), 0 }, { ADDR(g_menuCameraLookY), 0 },
	{ ADDR(g_menuCameraHeight), 0xc4098000 }, { ADDR(g_camPoint0X), 0 }, { ADDR(g_camPoint0Y), 0 }, { ADDR(g_camPoint0Z), 0x42c80000 }, { ADDR(g_camAim0X), 0 },
	{ ADDR(g_camAim0Y), 0 }, { ADDR(g_camAim0Z), 0 }, { ADDR(g_menuCameraX), 0 }, { ADDR(g_menuCameraY), 0 }, { ADDR(g_menuCameraZ), 0xc3e10000 }, { ADDR(g_menuLookAtX), 0 },
	{ ADDR(g_menuLookAtY), 0 }, { ADDR(g_menuLookAtZ), 0xc4098000 } };

/* 0x443950: the skirmish setup (screen 900): the briefing camera, the briefing window and its colours, the page's
   panels (skirmishList_layout, briefing_layout), the page set to 10 (the mission list) with a sound, the mission list
   loaded (mission_loadAxisMis) and its state cleared. Returns 0 (the original's eax) */
int (menuState900_enterSkirmish)(void)
{
	static const Store setup[] = {
		{ ADDR(g_briefingX), 0xa }, { ADDR(g_briefingY), 0x14 }, { ADDR(g_briefingRight), 0x276 }, { ADDR(g_briefingBottom), 0x1cc }, { OBJ(g_skirmishColourLit), 0 },
		{ (OBJ(g_skirmishColourLit) + 0x4), ONE }, { (OBJ(g_skirmishColourLit) + 0x8), ONE }, { (OBJ(g_skirmishColourLit) + 0xc), ONE }, { OBJ(g_skirmishColourDim), 0 }, { (OBJ(g_skirmishColourDim) + 0x4), 0x3f19999a },
		{ (OBJ(g_skirmishColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_skirmishColourDim) + 0xc), ONE }, { ADDR(g_skirmishState), 1 }, { ADDR(g_screen), 900 }, { ADDR(g_lastScreen), 900 },
		{ ADDR(g_nextScreen), 900 } };
	static const u32 cleared[] = { ADDR(g_missionTop), ADDR(g_skirmishRow), ADDR(g_missionPicked), ADDR(g_repeatDown), ADDR(g_repeatUp) };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	skirmishList_layout();   /* skirmishList_layout */
	briefing_layout();   /* briefing_layout */
	g_skirmishDrawBackground = 1;
	g_skirmishPage = 10;
	sound_playMenu(4);
	mission_loadAxisMis();   /* mission_loadAxisMis */
	CLEAR_ALL(cleared);
	return 0;
}

/* 0x447750: the mission select (screen 500; the main menu's SKIRMISH PLAY): the briefing camera, the window and its colours, the screen's panels
   (missionsel_layout), the mission shown (0x9f63b4, 0x9f6328) the campaign's next one (0x9f181c, at most 14), a sound;
   a newly reached mission (past 0x9f62fc) raises it and the briefing flag 0x9f62e0. Returns the campaign's mission */
int (menuState500_enter)(void)
{
	static const Store setup[] = {
		{ ADDR(g_missionSelectLeft), 0x28 }, { ADDR(g_missionSelectTop), 0xa }, { (OBJ(g_missionSelectRect) + 0x8), 0x258 }, { (OBJ(g_missionSelectRect) + 0xc), 0x1cc }, { OBJ(g_missionColourLit), 0 },
		{ (OBJ(g_missionColourLit) + 0x4), ONE }, { (OBJ(g_missionColourLit) + 0x8), ONE }, { (OBJ(g_missionColourLit) + 0xc), ONE }, { OBJ(g_missionColourDim), 0 }, { (OBJ(g_missionColourDim) + 0x4), 0x3f19999a },
		{ (OBJ(g_missionColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_missionColourDim) + 0xc), ONE }, { ADDR(g_missionPage), 1 }, { ADDR(g_screen), 500 }, { ADDR(g_lastScreen), 500 },
		{ ADDR(g_nextScreen), 500 } };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	missionsel_layout();   /* missionsel_layout */
	g_missionShowBackground = 1;
	g_missionBusy = 0;
	int mission = g_progress < 15 ? g_progress : 14;
	g_missionShown = mission;
	g_missionChosen = mission;
	g_missionPreviewDue = 1;
	sound_playMenu(4);
	g_missionBriefing = 0;
	if (g_progress > g_profileProgressSaved) {
		g_missionBriefing = 1;
		g_profileProgressSaved = g_progress;
	}
	return g_progress;
}

/* 0x44b420: the pilot screen (state 210): its panels laid out, the profiles' header read back (profile_readHeader) with
   the current one selected and scrolled into the 13 visible rows, the new-pilot dialog up when there are none, the
   message box and the screen's rectangles (profilePage_layout, 44b030 .. 44b1a0), its colours, then the list shown
   (profile_resetPreview). Returns that call's eax */
u32 (menuState210_enter)(void)
{
	static const Store layout[] = {
		{ ADDR(g_profilePageLeft), 0x3c }, { ADDR(g_profilePageTop), 0x3c }, { ADDR(g_profileDialogBottom), 0x10e }, { ADDR(g_logOutDialogBottom), 0x10e }, { ADDR(g_profilePageRight), 0x244 },
		{ ADDR(g_profilePageBottom), 0x1a4 }, { ADDR(g_newNameDialogLeft), 0x78 }, { ADDR(g_newNameDialogTop), 0x96 }, { ADDR(g_newNameDialogRight), 0x208 }, { ADDR(g_newNameDialogBottom), 0x118 },
		{ ADDR(g_profileDialogX), 0x78 }, { ADDR(g_profileDialogY), 0x96 }, { ADDR(g_profileDialogRight), 0x208 }, { ADDR(g_logOutDialogX), 0x78 }, { ADDR(g_logOutDialogY), 0x96 },
		{ ADDR(g_logOutDialogRight), 0x208 }, { ADDR(g_pilotSelectLeft), 0x1e }, { ADDR(g_pilotSelectTop), 0x14 }, { ADDR(g_pilotSelectRight), 0x262 }, { ADDR(g_pilotSelectBottom), 0x1c2 } };
	static const u32 cleared[] = { ADDR(g_profileScreenReady), ADDR(g_profileDialogOpen), ADDR(g_profileListTop), ADDR(g_profileListRow), ADDR(g_pilotChosen), ADDR(g_currentProfile), ADDR(g_repeatDown), ADDR(g_repeatUp),
	                               ADDR(g_highlightShown) };
	static const Store colours[] = {
		{ OBJ(g_profileColour), 0 }, { (OBJ(g_profileColour) + 0x4), ONE }, { (OBJ(g_profileColour) + 0x8), ONE }, { (OBJ(g_profileColour) + 0xc), ONE }, { OBJ(g_profileDim), 0 },
		{ (OBJ(g_profileDim) + 0x4), 0x3f19999a }, { (OBJ(g_profileDim) + 0x8), 0x3f19999a }, { (OBJ(g_profileDim) + 0xc), ONE }, { ADDR(g_cursorBlink), 0 }, { ADDR(g_introZoom), 0 },
		{ ADDR(g_profileIntro), 0 }, { ADDR(g_profileRowClicked), 0 }, { ADDR(g_profileMessageTime), 0 } };
	static const u32 rects[7] = { FN_ADDR(profilePage_layout, 0x44af30), FN_ADDR(newNameDialog_layout, 0x44b030), FN_ADDR(profileDialogBox_layout, 0x44b080), FN_ADDR(deleteDialog_layout, 0x44b0b0), FN_ADDR(logOutDialog_layout, 0x44b100), FN_ADDR(profileList_layout, 0x44b150), FN_ADDR(pilotSelect_layout, 0x44b1a0) };
	STORE_ALL(layout);
	CLEAR_ALL(cleared);
	profile_readHeader();   /* profile_readHeader: the header read back */
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
	return profile_resetPreview();   /* profile_resetPreview */
}

/* the profile files checked (the English one, then four times the Korean one): a missing one ends the game with
   the message 0x4b04b0 */
static void check_profiles(void)
{
	for (int k = 0; k < 5; k++)
		if (!(k == 0 ? app_checkFile_profeng() : app_checkFile_profkor())) {
			sys_messageBox((const char *)STR(0x4b04b0, "Run AxisPlay.exe"));
			crt_exit(-1);   /* exit */
		}
}

/* the player's name for the match (0x4dedd8, 32 bytes) */
static void match_name(const char *name)
{
	memset((void *)OBJ(g_matchPlayerName), 0, 32);
	strcpy(g_matchPlayerName, name);
}

/* 0x41fd40 (the match started, state 9999): the menus' tunnel freed; outside the lobby
   (0x76d410) the profile files checked; the display opened (aspect 0x4e1870, glWindow_init); a replay (0x9db990)
   started at once (scene_startSession 0, 3); else the map (0x9dad94) loaded (failing: message 6 and back to state 400 /
   800 for the arena / room). By the kind of match (0x5ae9c4): 1 the arena, 2 the room (the pilots read, the
   player's name taken from the profile / the room, the part lists 0x40d990), 3 a skirmish (the name 0x9f1798),
   started with scene_startSession (a host unless 0x67ef04 is 1; 3: 0, 0); then the map's name announced. The caller
   ignores the eax it leaves */
void (match_enter)(void)
{
	while (g_menuTunnel)   /* the menus' tunnel, ring by ring */
		tunnel_removeLastRing((TunnelRing **)ADDR(g_menuTunnel));
	if (!g_startedFromLobby)
		check_profiles();
	g_matchRunning = 1;
	g_viewAspect = f32((long double)g_screenW / (long double)g_screenH);
	sys_checkClockTampering();
	glWindow_init((const char *)STR(0x4b04a0, "Axis Console"), g_screenW, g_screenH, g_videoDepth, 0x10, 0, g_hWndMain, (*(int *)&g_windowDC));
#define scene g_scene   /* read at each use: loading the map makes the match's scene */
	if (g_replayRunning) {
		g_matchMode = 0;
		scene_startSession(scene, 0, 3);
		return;
	}
	int loaded = map_fileExists(g_missionStage);
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
		match_name(g_cfgPlayerName);
		armc_resetSeraphimParts();
		scene_startSession(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 2:
		pilotRecord_syncCopies();
		if (g_pilotLevel != 0x14)
			armc_resetSeraphimParts();
		data_loadPilotProfiles();
		match_name(g_ladderId);
		scene_startSession(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 3:
		match_name((const char *)(OBJ(g_campaign) + 0x80));
		scene_startSession(scene, 0, 0);
		break;
	}
	scene_setTextureFolder(scene, (const char *)(OBJ(g_mapNames) + g_missionStage * 0x20));   /* (the original also builds "%s" with the name on its stack, unused) */
#undef scene
}
