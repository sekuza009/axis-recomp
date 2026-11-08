/* screen_enter.c: the front end's screens set up as they are entered (the main menu, the arena lobby, the setup
   screen, the game room, the mission list, the skirmish screen, the pilot screen, the match): each lays out its
   panels, sets its colours, points the menu camera at the screen with its current place as home, and clears its
   state; also the menus' mouse dispatch (menu_processMouse). */
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

/* the camera's target points 0 .. n-1 (16 bytes apart from g_camPoint0X, look-at points from g_camAim0X) given
   the look-at's current z (g_menuCameraLookZ: the depth along the tunnel), and the current eye as home (g_menuEyeHomeX) */
static void camera_pointsAtLookZ(int n)
{
	int z = (*(int *)&g_menuCameraLookZ);
	for (int i = 0; i < n; i++) {
		I(ADDR(g_camPoint0Z) + i * 0x10) = z;
		I(ADDR(g_camAim0Z) + i * 0x10) = z;
	}
	(*(int *)&g_menuEyeHomeX) = (*(int *)&g_menuEyeX);
	(*(int *)&g_menuEyeHomeY) = (*(int *)&g_menuEyeY);
	(*(int *)&g_menuEyeHomeZ) = (*(int *)&g_menuEyeZ);
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
	(*(u32 *)&g_mainMenuDepth) = 0xc3960000;   /* -300 */
	g_mainMenuFrames = 0;
	(*(u32 *)&g_flareSizeB) = 0x41200000;   /* 10 */
	(*(u32 *)&g_flareSizeA) = 0x42400000;   /* 48 */
	(*(u32 *)&g_flareStepB) = 0x3e4ccccd;   /* 0.2 */
	(*(u32 *)&g_flareStepA) = 0xbe4ccccd;   /* -0.2 */
	(*(int *)&g_menuRepeatClock) = 0;
	(*(int *)&g_menuIdleTime) = 0;
	(*(u32 *)&g_menuHintStep) = 0x3d4ccccd;   /* 0.05 */
	(*(int *)&g_menuHintFade) = 0;
	g_replaySelectOpen = 0;
	(*(int *)&g_replaySelectLitR) = 0;
	(*(u32 *)&g_replaySelectLitG) = ONE;
	(*(u32 *)&g_replaySelectLitB) = ONE;
	(*(u32 *)&g_replaySelectLitA) = ONE;
	(*(u32 *)&g_replaySelectDimR) = 0x3e99999a;   /* (0.3, 0.7, 0.7, 1) */
	(*(u32 *)&g_replaySelectDimG) = 0x3f333333;
	(*(u32 *)&g_replaySelectDimB) = 0x3f333333;
	(*(u32 *)&g_replaySelectDimA) = ONE;
	g_matchMode = 0;
}

/* 0x404640: the arena lobby */
void (menuState400_enter)(void)
{
	static const Store layout[] = {
		{ OBJ(g_lobbySlideEase), 0 }, { ADDR(g_lobbySubState), 5 }, { OBJ(g_lobbyTopRect), 0x50 }, { (OBJ(g_lobbyTopRect) + 0x4), 0x96 }, { (OBJ(g_lobbyTopRect) + 0x8), 0x230 }, { (OBJ(g_lobbyTopRect) + 0xc), 0x15e },
		{ ADDR(g_playerSetupRight), 0x21c }, { ADDR(g_playerSetupBottom), 0x190 }, { ADDR(g_arenaGameListRight), 0x262 }, { ADDR(g_newArenaFormLeft), 0x28 }, { ADDR(g_newArenaFormTop), 0x1e },
		{ ADDR(g_newArenaFormRight), 0x258 } };
	static const u32 cleared1[] = { ADDR(g_typingArenaPlayerName), ADDR(g_editingNewArenaName), ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword), ADDR(g_lanSearch), ADDR(g_lobbySearching), ADDR(g_arenaLanListBuilt),
	                                ADDR(g_arenaServerList), ADDR(g_gameCount), ADDR(g_listBlinkClock) };
	static const u32 cleared2[] = { ADDR(g_pickedGame), ADDR(g_gameListTop), ADDR(g_gameListRow), ADDR(g_lanSearchStarted), ADDR(g_serverSearching), OBJ(g_arenaBright), ADDR(g_arenaUpdateNotice), ADDR(g_hostingState) };
	static const Store state[] = {
		{ ADDR(g_arenaCameraMode), 2 }, { ADDR(g_lastPanel), 999 }, { (OBJ(g_arenaBright) + 0x4), ONE }, { (OBJ(g_arenaBright) + 0x8), ONE }, { (OBJ(g_arenaBright) + 0xc), ONE },
		{ OBJ(g_arenaDim), 0x3e99999a }, { (OBJ(g_arenaDim) + 0x4), 0x3f333333 }, { (OBJ(g_arenaDim) + 0x8), 0x3f333333 }, { (OBJ(g_arenaDim) + 0xc), ONE }, { ADDR(g_unusedArenaWord), 0xf },
		{ ADDR(g_armcFrom), 1 } };
	g_matchMode = 1;
	arena_clearSessionEntry();
	g_playerSetupLeft = 0x64;
	g_playerSetupTop = 0x64;
	(*(int *)&g_menuRepeatClock) = 0;
	g_arenaGameListLeft = 0x14;
	g_arenaGameListTop = 0x14;
	(*(u32 *)&g_arenaTunnelDepth) = 0xc4af0000;   /* -1400 */
	g_arenaGameListBottom = 0x1c2;
	g_newArenaFormBottom = 0x1c2;
	g_lobbyPanelsSliding = 1;
	camera_pointsAtLookZ(4);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = (*(int *)&g_menuCameraLookZ);
	STORE_ALL(layout);
	STORE_ALL(camera4);
	(*(int *)&g_menuLookHomeX) = lx;
	(*(int *)&g_menuLookHomeY) = ly;
	(*(int *)&g_menuLookHomeZ) = lz;
	CLEAR_ALL(cleared1);
	lobbyTop_layout();
	playerSetup_layout();
	arenaGameList_layout();
	arenaDialogBox_layout();
	createArena_layout();
	arenaUpdateNotice_layout();
	CLEAR_ALL(cleared2);
	STORE_ALL(state);
}

/* 0x420770: the setup screen: its layout, camera, colours, and the two option columns' texts (0x80 apart in the
   text block at MSG(431, "16BIT COLOR")) */
void (menuState600_enterSetup)(void)
{
	static const Store layout[] = {
		{ ADDR(g_setupTab), 0x29a }, { ADDR(g_setupTunnelDepth), 0xc4af0000 }, { ADDR(g_setupPanelMoving), 1 }, { ADDR(g_setupPanelPos), 0 }, { ADDR(g_setupCameraMode), 2 },
		{ ADDR(g_setupSoundLeft), 0x32 }, { (OBJ(g_setupSoundRect) + 0x4), 0x3c }, { (OBJ(g_setupSoundRect) + 0xc), 0x1a4 }, { OBJ(g_setupGraphicRect), 0x64 }, { (OBJ(g_setupGraphicRect) + 0x8), 0x21c },
		{ (OBJ(g_setupGraphicRect) + 0xc), 0x1c2 }, { ADDR(g_setupControlLeft), 0x28 }, { (OBJ(g_setupControlRect) + 0xc), 0x1b8 } };
	static const Store colours_tunnel[] = {
		{ OBJ(g_setupColourLit), 0 }, { (OBJ(g_setupColourLit) + 0x4), ONE }, { (OBJ(g_setupColourLit) + 0x8), ONE }, { (OBJ(g_setupColourLit) + 0xc), ONE }, { OBJ(g_setupColourDim), 0 },
		{ (OBJ(g_setupColourDim) + 0x4), 0x3f19999a }, { (OBJ(g_setupColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_setupColourDim) + 0xc), ONE }, { ADDR(g_tunnelStripeScroll), 0 }, { ADDR(g_menuTunnelSpeed), ONE },
		{ ADDR(g_tunnelPulse), 0 }, { ADDR(g_tunnelPulseStep), ONE } };
	g_setupGraphicTop = 0x1e;
	g_setupControlTop = 0x1e;
	g_setupSoundRight = 0x24e;
	g_setupControlRight = 0x24e;
	camera_pointsAtLookZ(4);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = (*(int *)&g_menuCameraLookZ);
	STORE_ALL(layout);
	STORE_ALL(camera4);
	(*(int *)&g_menuLookHomeX) = lx;
	(*(int *)&g_menuLookHomeY) = ly;
	(*(int *)&g_menuLookHomeZ) = lz;
	setupSound_layout();
	setupGraphic_layout();
	setupControl_layout();
	STORE_ALL(colours_tunnel);
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
   (-+70, +-55)), the room's record and state cleared, the ranking's last page
   999 (g_rankingLastPage) */
void (menuState800_enterGameRoom)(void)
{
	static const Store layout[] = {
		{ ADDR(g_roomTunnelDepth), 0xc4af0000 }, { ADDR(g_roomPanelsSliding), 1 }, { ADDR(g_roomSlideEase), 0 }, { ADDR(g_roomCameraMode), 2 }, { ADDR(g_unusedRoomFloat), 0x3f333333 },
		{ ADDR(g_roomState), 0x42 }, { ADDR(g_connectionAwaited), 0 }, { ADDR(g_roomLoginLeft), 0x32 }, { ADDR(g_roomLoginTop), 0x6e }, { ADDR(g_roomLoginRight), 0x24e },
		{ ADDR(g_roomLoginBottom), 0x172 }, { ADDR(g_accountPanelLeft), 0x3c }, { ADDR(g_accountPanelTop), 0x1e }, { ADDR(g_accountPanelRight), 0x244 }, { ADDR(g_accountPanelBottom), 0x1c2 },
		{ ADDR(g_roomGameListLeft), 0x14 }, { ADDR(g_roomGameListTop), 0x28 }, { ADDR(g_roomGameListRight), 0x26c }, { ADDR(g_roomGameListBottom), 0x1b8 }, { ADDR(g_roomFormLeft), 0x28 },
		{ ADDR(g_roomFormTop), 0x1e }, { ADDR(g_roomFormRight), 0x258 }, { ADDR(g_roomFormBottom), 0x1c2 }, { OBJ(g_rankingRect), 0x10 }, { (OBJ(g_rankingRect) + 0x4), 0x1e },
		{ (OBJ(g_rankingRect) + 0x8), 0x268 }, { (OBJ(g_rankingRect) + 0xc), 0x1b8 } };
	static const Store colours_camera[] = {
		{ ADDR(g_hostAnswer), 2 }, { OBJ(g_roomBright), 0 }, { (OBJ(g_roomBright) + 0x4), ONE }, { (OBJ(g_roomBright) + 0x8), ONE }, { (OBJ(g_roomBright) + 0xc), ONE },
		{ OBJ(g_roomDim), 0x3e99999a }, { (OBJ(g_roomDim) + 0x4), 0x3f333333 }, { (OBJ(g_roomDim) + 0x8), 0x3f333333 }, { (OBJ(g_roomDim) + 0xc), ONE },
		{ ADDR(g_camPoint0X), 0x41a00000 }, { ADDR(g_camPoint0Y), 0xc1200000 }, { ADDR(g_camAim0X), 0xc28c0000 }, { ADDR(g_camAim0Y), 0x425c0000 },
		{ ADDR(g_camPoint1X), 0x41a00000 }, { (OBJ(g_camPoints) + 0x14), 0 }, { ADDR(g_camAim1X), 0xc28c0000 }, { ADDR(g_camAim1Y), 0 },
		{ ADDR(g_camPoint2X), 0x41a00000 }, { ADDR(g_camPoint2Y), 0x41200000 }, { ADDR(g_camAim2X), 0xc28c0000 }, { ADDR(g_camAim2Y), 0xc25c0000 },
		{ (OBJ(g_camPoints) + 0x30), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x34), 0xc1200000 }, { (OBJ(g_camAims) + 0x30), 0x428c0000 }, { (OBJ(g_camAims) + 0x34), 0x425c0000 },
		{ (OBJ(g_camPoints) + 0x40), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x44), 0 }, { (OBJ(g_camAims) + 0x40), 0x428c0000 }, { (OBJ(g_camAims) + 0x44), 0 } };
	static const u32 cleared[] = { ADDR(g_roomRequestOut), ADDR(g_newIdAnswerAwaited), ADDR(g_unusedRoomWord), ADDR(g_hostGameSetUp), ADDR(g_roomLoginDue), ADDR(g_rankingRequestPending), ADDR(g_roomConnected), ADDR(g_roomAwaitingServer),
	                               ADDR(g_roomUpdateNotice) };
	g_matchMode = 2;
	arena_clearSessionEntry();
	STORE_ALL(layout);
	roomLogin_layout();
	account_layout();
	gameList_layout();
	gameListJoinBox_layout();
	roomSettings_layout();
	ranking_layout();
	updateNotice_layout();
	STORE_ALL(colours_camera);
	camera_pointsAtLookZ(5);
	(*(int *)&g_menuLookHomeX) = (*(int *)&g_menuCameraLook);
	(*(int *)&g_menuLookHomeY) = (*(int *)&g_menuCameraLookY);
	(*(int *)&g_menuLookHomeZ) = (*(int *)&g_menuCameraLookZ);
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
	room_copyAccountRecord();
	g_retypePassword = 1;
	CLEAR_ALL(cleared);
	g_rankingLastPage = 999;
}

/* ---- the front end's per-frame dispatch ---- */

/* 0x445e40: the menus' mouse, once per frame: the mouse read (input_updateMouse), then, unless the menu camera is moving
   (g_menuCameraMove), the message box's clicks while it is shown, else the current screen's (g_screen): 200 the title, 210 profiles, 300 the main menu, 400 the lobby,
   500 skirmish, 600 setup, 700 the ARM CENTER, 800 the game room, 900 the mission list, 9999 in a match. Returns what the
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
	case 200: return title_clickDismiss();
	case 210: return profile_screenClicks();   /* profile_screenClicks */
	case 300: return mainmenu_clicks();
	case 400: return lobby_clicks();   /* lobby_clicks */
	case 500: return skirmish_screenClicks();
	case 600: return setup_tabClicks();
	case 700: return armc_mouse();   /* armc_mouse */
	case 800: return room_clicksByState();
	case 900: return missions_pageClicks();
	case 9999: return freeCam_mouseLook();  /* freeCam_mouseLook */
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

/* 0x41f970: a screen entered: its set-up by the state (g_screen; the main menu also flags g_enteringMenus), the state kept as
   the one before (g_lastScreen). Returns the state */
u32 (menu_enterState)(void)
{
	switch (g_menuState) {
	case 210: menuState210_enter(); break;   /* menuState210_enter */
	case 300:
		g_enteringMenus = 1;
		menuState300_enter();                 /* menuState300_enter */
		break;
	case 400: menuState400_enter(); break;   /* menuState400_enter */
	case 500: menuState500_enterSkirmish(); break;   /* menuState500_enterSkirmish */
	case 600: menuState600_enterSetup(); break;   /* menuState600_enterSetup */
	case 800: menuState800_enterGameRoom(); break;   /* menuState800_enterGameRoom */
	case 900: menuState900_enterMissions(); break;   /* menuState900_enterMissions */
	case 9999: match_enter(); break;  /* match_enter */
	}
	g_lastScreen = g_menuState;
	return (u32)g_menuState;
}


/* the skirmish and mission screens' camera: the eye at (0, 0, -450) looking at (0, 0, -550), that its home, one target
   point (0, 0, 100) looking at the origin */
static const Store briefing_camera[] = {
	{ ADDR(g_menuEyeX), 0 }, { ADDR(g_menuEyeY), 0 }, { ADDR(g_menuEyeZ), 0xc3e10000 }, { ADDR(g_menuCameraLook), 0 }, { ADDR(g_menuCameraLookY), 0 },
	{ ADDR(g_menuCameraLookZ), 0xc4098000 }, { ADDR(g_camPoint0X), 0 }, { ADDR(g_camPoint0Y), 0 }, { ADDR(g_camPoint0Z), 0x42c80000 }, { ADDR(g_camAim0X), 0 },
	{ ADDR(g_camAim0Y), 0 }, { ADDR(g_camAim0Z), 0 }, { ADDR(g_menuEyeHomeX), 0 }, { ADDR(g_menuEyeHomeY), 0 }, { ADDR(g_menuEyeHomeZ), 0xc3e10000 }, { ADDR(g_menuLookHomeX), 0 },
	{ ADDR(g_menuLookHomeY), 0 }, { ADDR(g_menuLookHomeZ), 0xc4098000 } };

/* 0x443950: the mission list (screen 900, axis.mis; nothing in the menus opens it): the briefing camera, the briefing window and its colours, the page's
   panels (missionList_layout, briefing_layout), the page set to 10 (the mission list) with a sound, the mission list
   loaded (mission_loadAxisMis) and its state cleared. Returns 0 (the original's eax) */
int (menuState900_enterMissions)(void)
{
	static const Store setup[] = {
		{ ADDR(g_missionsWindowLeft), 0xa }, { ADDR(g_missionsWindowTop), 0x14 }, { ADDR(g_missionsWindowRight), 0x276 }, { ADDR(g_missionsWindowBottom), 0x1cc }, { OBJ(g_missionsColourLit), 0 },
		{ (OBJ(g_missionsColourLit) + 0x4), ONE }, { (OBJ(g_missionsColourLit) + 0x8), ONE }, { (OBJ(g_missionsColourLit) + 0xc), ONE }, { OBJ(g_missionsColourDim), 0 }, { (OBJ(g_missionsColourDim) + 0x4), 0x3f19999a },
		{ (OBJ(g_missionsColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_missionsColourDim) + 0xc), ONE }, { ADDR(g_missionsState), 1 }, { ADDR(g_screen), 900 }, { ADDR(g_lastScreen), 900 },
		{ ADDR(g_nextScreen), 900 } };
	static const u32 cleared[] = { ADDR(g_missionTop), ADDR(g_missionRow), ADDR(g_missionPicked), ADDR(g_repeatDown), ADDR(g_repeatUp) };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	missionList_layout();   /* missionList_layout */
	briefing_layout();   /* briefing_layout */
	g_missionsDrawBackground = 1;
	g_missionsPage = 10;
	sound_playMenu(4);
	mission_loadAxisMis();   /* mission_loadAxisMis */
	CLEAR_ALL(cleared);
	return 0;
}

/* 0x447750: the skirmish screen (screen 500; the main menu's SKIRMISH PLAY, rounds from skirmish.dat): the briefing camera, the window and its colours, the screen's panels
   (skirmish_layout), the round shown (g_skirmishRoundShown, g_skirmishChosen) the campaign's next one (0x9f181c, at most 14), a sound;
   a newly reached round (past g_progressSeen) raises it and the new-parts notice g_skirmishNewPartsNotice. Returns the campaign's mission */
int (menuState500_enterSkirmish)(void)
{
	static const Store setup[] = {
		{ ADDR(g_skirmishRectLeft), 0x28 }, { ADDR(g_skirmishRectTop), 0xa }, { (OBJ(g_skirmishRect) + 0x8), 0x258 }, { (OBJ(g_skirmishRect) + 0xc), 0x1cc }, { OBJ(g_skirmishColourLit), 0 },
		{ (OBJ(g_skirmishColourLit) + 0x4), ONE }, { (OBJ(g_skirmishColourLit) + 0x8), ONE }, { (OBJ(g_skirmishColourLit) + 0xc), ONE }, { OBJ(g_skirmishColourDim), 0 }, { (OBJ(g_skirmishColourDim) + 0x4), 0x3f19999a },
		{ (OBJ(g_skirmishColourDim) + 0x8), 0x3f19999a }, { (OBJ(g_skirmishColourDim) + 0xc), ONE }, { ADDR(g_skirmishState), 1 }, { ADDR(g_screen), 500 }, { ADDR(g_lastScreen), 500 },
		{ ADDR(g_nextScreen), 500 } };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	skirmish_layout();   /* skirmish_layout */
	g_skirmishShowBackground = 1;
	g_skirmishLeft = 0;
	int roundShown = g_progress < 15 ? g_progress : 14;
	g_skirmishRoundShown = roundShown;
	g_skirmishChosen = roundShown;
	g_skirmishPreviewDue = 1;
	sound_playMenu(4);
	g_skirmishNewPartsNotice = 0;
	if (g_progress > g_progressSeen) {
		g_skirmishNewPartsNotice = 1;
		g_progressSeen = g_progress;
	}
	return g_progress;
}

/* 0x44b420: the pilot screen (state 210): its panels laid out, the profiles' header read back (profile_readHeader) with
   the current one selected and scrolled into the 13 visible rows, the new-pilot dialog up when there are none, the
   message box and the screen's rectangles (profilePage_layout, 44b030 .. 44b1a0), its colours, then the list shown
   (profile_resetStatBars). Returns that call's eax */
u32 (menuState210_enter)(void)
{
	static const Store layout[] = {
		{ ADDR(g_profilePageLeft), 0x3c }, { ADDR(g_profilePageTop), 0x3c }, { ADDR(g_deleteDialogBottom), 0x10e }, { ADDR(g_logOutDialogBottom), 0x10e }, { ADDR(g_profilePageRight), 0x244 },
		{ ADDR(g_profilePageBottom), 0x1a4 }, { ADDR(g_newNameDialogLeft), 0x78 }, { ADDR(g_newNameDialogTop), 0x96 }, { ADDR(g_newNameDialogRight), 0x208 }, { ADDR(g_newNameDialogBottom), 0x118 },
		{ ADDR(g_deleteDialogX), 0x78 }, { ADDR(g_deleteDialogY), 0x96 }, { ADDR(g_deleteDialogRight), 0x208 }, { ADDR(g_logOutDialogX), 0x78 }, { ADDR(g_logOutDialogY), 0x96 },
		{ ADDR(g_logOutDialogRight), 0x208 }, { ADDR(g_pilotSelectLeft), 0x1e }, { ADDR(g_pilotSelectTop), 0x14 }, { ADDR(g_pilotSelectRight), 0x262 }, { ADDR(g_pilotSelectBottom), 0x1c2 } };
	static const u32 cleared[] = { ADDR(g_profileNoneAtEntry), ADDR(g_profileLogInAsked), ADDR(g_profileListTop), ADDR(g_profileListRow), ADDR(g_profileChosen), ADDR(g_currentProfile), ADDR(g_repeatDown), ADDR(g_repeatUp),
	                               ADDR(g_pointerGliding) };
	static const Store colours_clocks[] = {
		{ OBJ(g_profileColour), 0 }, { (OBJ(g_profileColour) + 0x4), ONE }, { (OBJ(g_profileColour) + 0x8), ONE }, { (OBJ(g_profileColour) + 0xc), ONE }, { OBJ(g_profileDim), 0 },
		{ (OBJ(g_profileDim) + 0x4), 0x3f19999a }, { (OBJ(g_profileDim) + 0x8), 0x3f19999a }, { (OBJ(g_profileDim) + 0xc), ONE }, { ADDR(g_menuRepeatClock), 0 }, { ADDR(g_replayZoomTime), 0 },
		{ ADDR(g_profileQuitting), 0 }, { ADDR(g_profileRowClicked), 0 }, { ADDR(g_profileRowClickTime), 0 } };
	static const u32 rects[7] = { FN(profilePage_layout), FN(newNameDialog_layout), FN(profileDialogBox_layout), FN(deleteDialog_layout), FN(logOutDialog_layout), FN(profileList_layout), FN(pilotSelect_layout) };
	STORE_ALL(layout);
	CLEAR_ALL(cleared);
	profile_readHeader();   /* profile_readHeader: the header read back */
	int current = g_currentProfile;
	g_profileChosen = current;
	g_profileListRow = current;
	if (current >= 13) {
		g_profileListRow = 12;
		g_profileListTop = current - 12;
	}
	if (g_profileCount == 0)
		g_profileNoneAtEntry = 1;
	g_menuFramePhase = 1;
	g_menuFrameCounter = 0;
	g_frameOpening = 1;
	g_profilePage = 1;
	for (int k = 0; k < 7; k++)
		GAME_CDECL(rects[k], void, void)();
	STORE_ALL(colours_clocks);
	return profile_resetStatBars();   /* profile_resetStatBars */
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

/* the player's name for the match (g_matchPlayerName, 32 bytes) */
static void match_name(const char *name)
{
	memset((void *)OBJ(g_matchPlayerName), 0, 32);
	strcpy(g_matchPlayerName, name);
}

/* 0x41fd40 (the match started, state 9999): the menus' tunnel freed; outside the lobby
   (g_launchedForNetGame) the profile files checked; the display opened (aspect g_viewAspect, glWindow_init); a replay (g_replayRunning)
   started at once (scene_startSession 0, 3); else the map (g_mapIndex) loaded (failing: message 6 and back to state 400 /
   800 for the arena / room). By the kind of match (g_matchMode): 1 the arena, 2 the room (the pilots read, the
   player's name taken from the profile / the room, the part lists armc_resetSeraphimParts), 3 a skirmish (the name 0x9f1798),
   started with scene_startSession (a client unless g_netRole is 1, the host; 3: 0, 0); then the map's name announced. The caller
   ignores the eax it leaves */
void (match_enter)(void)
{
	while (g_menuTunnel)   /* the menus' tunnel, ring by ring */
		tunnel_removeLastRing((TunnelRing **)ADDR(g_menuTunnel));
	if (!g_launchedForNetGame)
		check_profiles();
	g_matchRunning = 1;
	g_viewAspect = f32((long double)g_screenW / (long double)g_screenH);
	sys_checkClockTampering();
	glWindow_init((const char *)STR(0x4b04a0, "Axis Console"), g_screenW, g_screenH, g_videoDepth, 0x10, 0, g_mainWindow, (*(int *)&g_windowDC));
#define scene g_scene   /* read at each use: loading the map makes the match's scene */
	if (g_replayRunning) {
		g_matchMode = 0;
		scene_startSession(scene, 0, 3);
		return;
	}
	int mapExists = map_fileExists(g_mapIndex);
	int kind = g_matchMode;   /* (after the load, as the original reads it) */
	if (!mapExists) {
		if (kind == 1)
			g_menuState = 400;
		else if (kind == 2)
			g_menuState = 800;
		menu_showMessage(6);
		return;
	}
	switch (kind) {
	case 1:   /* (the selection's range checks are jumped over in the patched game) */
		data_loadCharacterProfiles();
		match_name(g_cfgPlayerName);
		armc_resetSeraphimParts();
		scene_startSession(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 2:
		pilotRecord_syncCopies();
		if (g_pilotLevel != 0x14)
			armc_resetSeraphimParts();
		data_loadCharacterProfiles();
		match_name(g_ladderId);
		scene_startSession(scene, g_netRole == 1 ? 0 : 1, 1);
		break;
	case 3:
		match_name((const char *)(OBJ(g_pilotSave) + 0x80));
		scene_startSession(scene, 0, 0);
		break;
	}
	scene_setMapName(scene, (const char *)(OBJ(g_mapNames) + g_mapIndex * 0x20));   /* (the original also builds "%s" with the name on its stack, unused) */
#undef scene
}
