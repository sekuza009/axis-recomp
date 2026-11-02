/* lobby_states.c: the arena lobby's and the game room's screens set up as they are entered: the camera's target point
   for the screen (and its look-at point), the screen's state cleared, the panel brightness (0x3f333333 = 0.7), the
   message box hidden (0x4dba68 / 0x9dd6bc), and for the lists the map list or the room list reset. The lobby's
   three sub-screens are 0 (the player's own record), 1 (the arena list) and 2 (creating an arena). */
#include "../game.h"
#include <string.h>


static void clear_all(const u32 *addresses, int n)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(int, addresses[k]) = 0;
}

/* 0x404ac0: sub-screen 0: the camera to (35, 0) looking at (-70, 35), the player's record from the profile */
void (lobby_setSubState0)(void)
{
	int z = g_menuCameraHeight;
	(*(u32 *)&g_camPoint0X) = 0x420c0000;   /* 35.0 */
	g_camPoint0Y = 0;
	g_camPoint0Z = z;
	(*(u32 *)&g_camAim0X) = 0xc28c0000;   /* -70.0 */
	(*(u32 *)&g_camAim0Y) = 0x420c0000;   /* 35.0 */
	g_camAim0Z = z;
	arena_copyProfile();
	g_arenaLobbyMode = 1;
	g_lobbySubState = 0;
	g_arenaPanelBrightness = 0x3f333333;
	g_armcFrom = 0;
	g_lobbyPanelsOff = 0;
	g_arenaTunnelDepth = 0xc4ce4000;   /* -1650.0 */
}

/* 0x404b30: sub-screen 1, the arena list: its 24 state words cleared, 999 (no selection), 30 seconds */
void (lobby_setSubState1)(void)
{
	static const u32 cleared[] = { (OBJ(g_camPoints) + 0x14), ADDR(g_serverConnected), ADDR(g_lobbyRefreshing), ADDR(g_arenaSearchStarted), ADDR(g_serverSearching), ADDR(g_lobbyJoinStarted), ADDR(g_lobbyJoinRequest), ADDR(g_lanSearch),
	                               ADDR(g_lobbySearching), ADDR(g_arenaHaveList), ADDR(g_arenaListFull), ADDR(g_gameCount), ADDR(g_lobbyBlinkClock), ADDR(g_localPlayer), ADDR(g_gameListTop), ADDR(g_lobbyListRow),
	                               ADDR(g_arenaListClickArmed), ADDR(g_arenaSearchClock), ADDR(g_lobbyPanelsOff), ADDR(g_arenaConfirming), ADDR(g_lobbyConnectionOpen), ADDR(g_arenaLeaving), ADDR(g_arenaListRefreshTimer), ADDR(g_arenaFull) };
	int z = g_menuCameraHeight;
	g_camPoint1X = 0x420c0000;   /* 35.0 */
	g_camPoint1Z = z;
	g_camAim1Z = z;
	g_camAim1X = 0xc28c0000;   /* -70.0 */
	g_camAim1Y = 0xc20c0000;   /* -35.0 */
	g_lobbySubState = 1;
	g_arenaLobbyMode = 1;
	g_arenaPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_lastPanel = 999;
	g_lobbyPending = 1;
	g_arenaTunnelDepth = 0xc4ce4000;
	g_listRefreshPeriod = 30;
}

/* 0x404980: the arena settings record (0x4ded20: title, map, options) copied to the lobby's (0x4db528). Maps 22 .. 24
   can't be chosen (back to 0); a title still the default one becomes "<player name><suffix>" */
void (lobby_drawArenaTitle)(void)
{
	signed char map = g_arenaMap;
	if (map >= 0x16 && map <= 0x18)
		g_arenaMap = map = 0;
	if (!strcmp(g_playerName, (const char *)STR(0x4ad4a4, "AXIS ARENA"))) {
		memset((void *)OBJ(g_playerName), 0, 32);
		strcpy(g_playerName, g_cfgPlayerName);
		strcat(g_playerName, (const char *)IMG(0x4ad49c));
		map = g_arenaMap;
	}
	memset((void *)OBJ(g_newArenaName), 0, 32);
	strcpy(g_newArenaName, g_playerName);
	u8 b1 = g_arenaPlayers, b2 = g_arenaCustomize, b3 = g_arenaGameType, b4 = g_arenaFragLimit,
	   b5 = g_arenaTimeLimit;
	g_newArenaMap = map;
	g_newArenaMode = b3;
	g_newArenaPlayers = b1;
	g_newArenaKind = b2;
	g_newArenaPassword = 0;
	g_arenaFragLimitTyped = b4;
	g_arenaTimeLimitTyped = b5;
	g_newArenaPassword4 = 0;
}

/* 0x403420: the map on/off list (8-byte entries from 0x4d9508): the first time all off, then the first n maps
   (0x67ef00) on; maps 22 .. 24 turned off (the last ones; the list's open flag cleared too) and the list laid out */
void (mapList_init)(void)
{
	if (!g_mapListMade) {
		for (u32 p = OBJ(g_mapChoiceKeptTable) + 4; p < OBJ(g_mapChoiceKeptTable) + 4 + 1024 * 8; p += 8) {
			GAME_VAR(int, p - 4) = 0;
			GAME_VAR(int, p) = 0;
		}
		for (int k = 0; k < g_arenaMapCount; k++) {
			GAME_VAR(int, OBJ(g_mapChoiceKeptTable) + k * 8) = 1;
			GAME_VAR(int, OBJ(g_mapChoiceKeptTable) + 4 + k * 8) = 0;
		}
	}
	g_mapEntry22On = 0;
	g_mapEntry23On = 0;
	g_mapEntry24On = 0;
	g_mapListOpen = 0;
	mapList_layout();
	g_mapListMade = 1;
}

/* 0x404c20: sub-screen 2, creating an arena: the camera to (-35, 0) looking at (70, 35), the arena's title, the map
   list */
void (lobby_setSubState2)(void)
{
	static const u32 cleared[] = { ADDR(g_arenaLobbyState), ADDR(g_connectionAwaited), ADDR(g_lobbyPending), ADDR(g_createQuitDialog), ADDR(g_arenaGameSetUp), ADDR(g_lobbyPanelsOff), ADDR(g_arenaLeaving), ADDR(g_editingNewArenaName),
	                               ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword) };
	int z = g_menuCameraHeight;
	g_camPoint2X = 0xc20c0000;   /* -35.0 */
	g_camPoint2Y = 0;
	g_camPoint2Z = z;
	g_camAim2X = 0x428c0000;   /* 70.0 */
	g_camAim2Y = 0x420c0000;   /* 35.0 */
	g_camAim2Z = z;
	lobby_drawArenaTitle();
	g_lobbySubState = 2;
	g_arenaLobbyMode = 1;
	g_arenaPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_arenaTunnelDepth = 0xc4ce4000;
	g_mapPreviewChanged = 1;
	mapList_init();
}

/* 0x433700: the room settings record (0x5b1b30: a name and six bytes) copied to the room's (0x4df9c8); map types
   22 .. 24 become 0 */
void (room_loadSettingsRecord)(void)
{
	if (g_roomRecMap > 0x15 && g_roomRecMap < 0x19)
		(*(u8 *)&g_roomRecMap) = 0;
	g_roomMap = (*(u8 *)&g_roomRecMap);
	memset((void *)OBJ(g_roomSettingsName), 0, 32);
	g_roomGameMode = g_roomRecGameMode;   /* stored before the name is copied, as in the original */
	strcpy(g_roomSettingsName, g_roomRecName);
	g_roomPlayers = g_roomRecPlayers;
	g_roomCustom = g_roomRecCustom;
	g_roomFragLimit = g_roomRecFragLimit;
	g_roomTimeLimit = g_roomRecTimeLimit;
}

/* 0x433790: the game room's list (state 2) entered: the room's settings, its state cleared, the map list */
void (room_enterGameList)(void)
{
	static const u32 cleared[] = { ADDR(g_arenaLobbyState), ADDR(g_connectionAwaited), ADDR(g_lobbyPending), ADDR(g_arenaGameSetUp), ADDR(g_arenaLeaving), ADDR(g_editingRoomName), IMG(0x9dd388), IMG(0x9dd568),
	                               ADDR(g_editingRoomPassword) };
	room_loadSettingsRecord();
	g_roomState = 2;
	g_roomMode = 1;
	g_roomPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_mapPreviewChanged = 1;
	(*(char *)&g_roomCustom) = 0;
	mapList_init();
}

/* 0x433800: the room list (state 4) entered: its ten 0x44-byte rows cleared (each marked empty), the paging and
   selection cleared, the distance limit 10,000,000, 999 rooms */
void (room_enterRoomList)(void)
{
	static const u32 cleared[] = { ADDR(g_roomListPage), ADDR(g_rankingRequestPending), ADDR(g_roomListWaiting), ADDR(g_rankingWaiting), ADDR(g_rankingHaveList), ADDR(g_playerListRefused), ADDR(g_playerListCount), ADDR(g_roomListPrevPage),
	                               ADDR(g_rankingSort), ADDR(g_roomListPrev), ADDR(g_roomListPrevRank) };
	for (u32 e = IMG(0x9dcef4); e < IMG(0x9dd19c); e += 0x44) {
		memset((void *)(RELOC(e) - 4), 0, 0x36);
		GAME_VAR(int, e + 0x32) = 1;
	}
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_roomMode = 1;
	g_rankingFirst = 1;
	g_roomState = 4;
	g_roomPanelBrightness = 0x3f333333;
	g_rankingLast = 10;
	g_roomListDistanceLimit = 0x4b189680;   /* 10000000.0 */
	g_roomListPages = 999;
}

/* 0x432620: the ladder's fixed game: its name (0x4b17bc) and the player's (0x9dd570), map 8, limits 10 and 10, in
   both the room's record and the room settings; the mech unpacked */
void (lobby_ladderGameName)(void)
{
	strcpy(g_roomSettingsName, (const char *)STR(0x4b17bc, "Axis Ladder Game"));
	(*(char *)&g_roomPlayers) = 8;
	(*(char *)&g_roomGameMode) = 0;
	strcpy((char *)IMG(0x76d450), g_joinedTitleName);
	(*(char *)&g_roomMap) = 0;
	(*(char *)&g_roomFragLimit) = 10;
	(*(char *)&g_roomTimeLimit) = 10;
	(*(char *)&g_roomCustom) = 0;
	strcpy(g_roomRecName, g_roomSettingsName);
	(*(char *)&g_roomRecPlayers) = 8;
	(*(char *)&g_roomRecGameMode) = 0;
	(*(char *)&g_roomRecMap) = 0;
	(*(char *)&g_roomRecFragLimit) = 10;
	(*(char *)&g_roomRecTimeLimit) = 10;
	(*(char *)&g_roomRecCustom) = 0;
	mech_unpackFromRecord();
}

/* 0x432be0: the joined game's settings (0x9dd570: its name, its host's, the room record 0x5b1b30, the mech and the
   window rectangles) copied into the room screen's */
void (room_copyJoinedSettings)(void)
{
	strcpy(g_accountName, g_joinedTitleName);
	strcpy(g_accountEmail, (const char *)IMG(0x9dd5a6));
	u8 map = g_roomRecPlayers;
	strcpy(g_roomSettingsName, g_roomRecName);
	g_roomPlayers = map;
	g_roomMap = (*(u8 *)&g_roomRecMap);
	g_roomCustom = g_roomRecCustom;
	g_roomGameMode = g_roomRecGameMode;
	g_roomFragLimit = g_roomRecFragLimit;
	g_roomTimeLimit = g_roomRecTimeLimit;
	memcpy((void *)IMG(0x9dd260), (void *)OBJ(g_roomMech), 11);
	memcpy((void *)IMG(0x9dd26b), (void *)OBJ(g_roomColours), 0x90);
	static const u32 copy[6][2] = { { ADDR(g_pilotLevelKept), ADDR(g_pilotLevel) }, { ADDR(g_pilotPointsKept), ADDR(g_pilotPoints) }, { (OBJ(g_pilotStatsKept) + 0x1c), ADDR(g_pilotWinRate) },
	                                { ADDR(g_pilotWinsKept), ADDR(g_pilotWins) }, { ADDR(g_pilotLossesKept), ADDR(g_pilotLosses) }, { ADDR(g_pilotScoreKept), ADDR(g_pilotScore) } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, copy[k][0]) = GAME_VAR(int, copy[k][1]);
}

/* a window rectangle record's seven fields copied (in the original's order) */
static void rect_copy(u32 dst, u32 src)
{
	static const int field[] = { 0, 0xc, 0x1c, 0x18, 4, 0x14, 0x10 };
	for (int k = 0; k < 7; k++)
		GAME_VAR(int, dst + field[k]) = GAME_VAR(int, src + field[k]);
}

/* 0x41e390 (named room_fitWindowRects; by use the pilot's record): the two copies of the pilot's record (the server's,
   g_pilotLevel 0x9dd5d8, and the kept one, g_pilotLevelKept 0x9dd240: level, points, ., rating, ., wins, losses) made
   the same when one's wins or points are past the other's, then each limited by the title record's (0x4de71e) */
void (room_fitWindowRects)(void)
{
	int c5, a1, b1;   /* the values the original holds in registers where the branches meet */
	if (g_pilotWins > g_pilotWinsKept || g_pilotPoints > g_pilotPointsKept) {
		rect_copy(ADDR(g_pilotLevel), ADDR(g_pilotLevelKept));
		c5 = g_pilotWinsKept;
		a1 = b1 = g_pilotPointsKept;
	} else {
		c5 = g_pilotWins;
		a1 = g_pilotPoints;
		b1 = g_pilotPointsKept;
		if (g_pilotWinsKept > c5 || b1 > a1) {
			rect_copy(ADDR(g_pilotLevelKept), ADDR(g_pilotLevel));
			b1 = a1;
		}
	}
	int e0 = g_titleLevel, e1 = g_titlePoints, e3 = g_titleRating,
	    e4 = g_titleScore, e5 = g_titleWins, e6 = g_titleLosses;
	if (c5 > e5 || a1 > e1) {
		g_pilotLevel = e0;
		g_pilotPoints = e1;
		g_pilotRating = e3;
		g_pilotWins = e5;
		g_pilotLosses = e6;
		g_pilotScore = e4;
	}
	if (g_pilotWinsKept > e5 || b1 > e1) {
		g_pilotPointsKept = e1;
		g_pilotLevelKept = e0;
		g_pilotRatingKept = e3;
		g_pilotWinsKept = e5;
		g_pilotLossesKept = e6;
		g_pilotScoreKept = e4;
	}
}

/* 0x432db0: a received game's settings (0xa0563c) into the room: its names, the 11 mech bytes, the six colour pairs
   (a negative or NaN chroma or value becomes 0), the window rectangle; then the room screen, the lobby's title
   record and the mech */
void (room_takeReceivedSettings)(void)
{
	strcpy(g_joinedTitleName, (const char *)(OBJ(g_netRecvRecord) + 0x4));
	strcpy((char *)IMG(0x9dd5a6), (const char *)(OBJ(g_netRecvRecord) + 0x22));
	memcpy((void *)OBJ(g_roomMech), (void *)(OBJ(g_netRecvRecord) + 0x54), 11);
	for (int k = 0; k < 6; k++) {
		memcpy((void *)(OBJ(g_roomColours) + k * 0x18), (void *)((OBJ(g_netRecvRecord) + 0x5f) + k * 0x18), 0x18);
		if (!(GAME_VAR(float, OBJ(g_roomColours) + 0x4 + k * 0x18) >= k_0f))
			GAME_VAR(int, OBJ(g_roomColours) + 0x4 + k * 0x18) = 0;
		if (!(GAME_VAR(float, OBJ(g_roomColours) + 0x8 + k * 0x18) >= k_0f))
			GAME_VAR(int, OBJ(g_roomColours) + 0x8 + k * 0x18) = 0;
	}
	static const u32 rect[7][2] = { { ADDR(g_pilotLevel), (OBJ(g_netRecvRecord) + 0xef) }, { ADDR(g_pilotPoints), (OBJ(g_netRecvRecord) + 0xff) }, { ADDR(g_pilotRating), (OBJ(g_netRecvRecord) + 0x103) },
	                                { ADDR(g_pilotWinRate), (OBJ(g_netRecvRecord) + 0x107) }, { ADDR(g_pilotWins), (OBJ(g_netRecvRecord) + 0xf7) }, { ADDR(g_pilotLosses), (OBJ(g_netRecvRecord) + 0xfb) },
	                                { ADDR(g_pilotScore), (OBJ(g_netRecvRecord) + 0xf3) } };
	for (int k = 0; k < 7; k++)
		GAME_VAR(int, rect[k][0]) = GAME_VAR(int, rect[k][1]);
	room_copyJoinedSettings();
	memset((void *)OBJ(g_titleName), 0, 7 * 4 + 2);
	strcpy(g_titleName, g_joinedTitleName);
	static const u32 title[6][2] = { { ADDR(g_titleLevel), ADDR(g_pilotLevel) }, { ADDR(g_titlePoints), ADDR(g_pilotPoints) }, { ADDR(g_titleWins), ADDR(g_pilotWins) },
	                                 { ADDR(g_titleLosses), ADDR(g_pilotLosses) }, { ADDR(g_titleScore), ADDR(g_pilotScore) }, { ADDR(g_titleRating), ADDR(g_pilotRating) } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, title[k][0]) = GAME_VAR(int, title[k][1]);
	mech_unpackFromRecord();
	g_bestLevelNet = g_pilotLevel;
	g_roomConnected = 1;
}

/* the default mech settings (11 bytes) and six colour pairs (hue 0, chroma 1, value 0.6) at mech, colours */
static void default_mech(u8 *mech, u8 *colours)
{
	static const u8 bytes[11] = { 0, 0, 0, 0, 0, 0xff, 0x11, 0, 2, 8, 0xff };
	static const u32 pair[6] = { 0, 0x3f800000, 0x3f19999a, 0, 0x3f800000, 0x3f19999a };
	memcpy(mech, bytes, sizeof bytes);
	for (int k = 0; k < 6; k++)
		memcpy(colours + k * 0x18, pair, sizeof pair);
}

/* 0x434820: a new room hosted: the room's names copied as the joined game's, the default mech and colours in both,
   the window rectangle reset (to 1, 0, ...) in both and the title record (0x4de700) set from it; the room record
   (0xa0b320: kind 0x18, the three names, the defaults) sent to the server (net_send 0xf, 0x65). Returns net_send's
   eax */
u32 (room_host)(void)
{
	strcpy(g_joinedTitleName, g_accountName);
	strcpy((char *)IMG(0x9dd5a6), g_accountEmail);
	default_mech((u8 *)IMG(0x9dd260), (u8 *)IMG(0x9dd26b));
	default_mech(g_roomMech, (u8 *)OBJ(g_roomColours));
	g_pilotLevelKept = 1;
	g_pilotLevel = 1;
	memset((void *)OBJ(g_titleName), 0, 7 * 4 + 2);
	static const u32 zero[] = { ADDR(g_pilotPoints), ADDR(g_pilotWins), ADDR(g_pilotLosses), ADDR(g_pilotScore), ADDR(g_pilotWinRate), ADDR(g_pilotPointsKept), ADDR(g_pilotWinsKept), ADDR(g_pilotLossesKept),
	                            ADDR(g_pilotScoreKept), (OBJ(g_pilotStatsKept) + 0x1c) };
	for (unsigned k = 0; k < sizeof zero / sizeof zero[0]; k++)
		GAME_VAR(int, zero[k]) = 0;
	strcpy(g_titleName, g_joinedTitleName);
	g_titleRating = g_pilotRating;
	g_titleLevel = 1;
	static const u32 zero2[] = { ADDR(g_titlePoints), ADDR(g_titleWins), ADDR(g_titleLosses), ADDR(g_titleScore) };
	for (int k = 0; k < 4; k++)
		GAME_VAR(int, zero2[k]) = 0;
	strcpy(g_accountPacket + 4, g_accountName);
	strcpy(g_accountPacket + 0x22, g_accountPassword);
	strcpy(g_accountPacket + 0x2e, g_accountEmail);
	u8 *record = (*(u8 **)&g_accountPacket);
	default_mech(record + 0x70, record + 0x7b);
	g_bestLevelNet = g_pilotLevel;
	*(int *)record = 0x18;
	u32 r = net_send(0xf, 0x65);
	g_roomAnswerAwaited = 1;
	return r;
}

/* 0x4080c0: the lobby's back keys (unless a dialog is open): the first closes the list (0x907b2c), the second leaves
   the game (quit code 2). Returns what the original leaves in eax */
u32 (lobby_keysBack)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	u32 r = input_justPressed(g_dikC);
	if (r) {
		g_arenaLeaving = 0;
		return r;
	}
	r = input_justPressed(g_dikO);
	if (!r)
		return 0;
	g_arenaLeaving = 0;
	return app_closeWindow(2);
}

/* 0x40cf80: the lobby's player screen: the arena tunnel, then in modes other than 0 and 1 (0x4dbb3c) and not on
   sub-screen 5, the player panel (arena_drawNameDialog), or with a dialog open just its frame. Returns what the original
   leaves in eax */
u32 (lobbyPlayer_draw)(void)
{
	arena_drawTunnel();   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaLobbyMode;
	if (mode == 1 || mode == 0 || g_lobbySubState == 5)
		return mode;
	if (!g_dialogOpen)
		return GAME_FN(arena_drawNameDialog, 0x409bc0, u32, void)();   /* arena_drawNameDialog */
	return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(g_arenaNameDialogLeft, g_arenaNameDialogTop,
	                                                     g_arenaNameDialogRight, g_arenaNameDialogBottom);   /* menu_drawFrame */
}

/* 0x4081f0: the lobby's keys, by sub-screen (0x4db51c): 0 the player's record, 1 the arena list (or its chat line
   while open), 2 creating an arena (the back keys while the list is open, the map list, the quit dialog, else the
   connect), 5 the top; 3 and 4 have none. Returns what the handler leaves in eax (else the sub-screen) */
u32 (lobby_processKeys)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 0:
		return GAME_FN(lobbyPlayer_keys, 0x407840, u32, void)();   /* lobbyPlayer_keys */
	case 1:
		if (g_arenaLeaving)
			return GAME_FN(lobbyJoin_keys, 0x407970, u32, void)();   /* lobbyJoin_keys */
		return GAME_FN(lobbyJoin_keysChat, 0x4079c0, u32, void)();       /* lobbyJoin_keysChat */
	case 2:
		if (g_arenaLeaving)
			return GAME_FN(lobby_keysBack, 0x4080c0, u32, void)();   /* lobby_keysBack */
		if (g_mapListOpen)
			return GAME_FN(room_mapListKeys, 0x403870, u32, void)();   /* the map list */
		if (g_createQuitDialog)
			return GAME_FN(lobby_keysQuit, 0x408110, u32, void)();   /* lobby_keysQuit */
		return GAME_FN(lobbyTop_connect, 0x407e40, u32, void)();       /* lobbyTop_connect */
	case 5:
		return GAME_FN(lobbyTop_keys, 0x407750, u32, void)();       /* lobbyTop_keys */
	}
	return screen;
}

/* 0x406bd0: the lobby's quit dialog's clicks (unless another dialog is open): a right click closes it; on its first
   button the game quits (code 2), on its second the dialog closes. Returns what the original leaves in eax */
u32 (lobby_quitDialogClicks)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_keyEnter)
		g_arenaLeaving = 0;
	if (!g_mouseClick)
		return 0;
	int button = arenaCreate_hitTest(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button == 0) {
		g_arenaLeaving = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		g_arenaLeaving = 0;
		return 0;
	}
	return (u32)(button - 1);
}

/* ---- the lobby's per-frame dispatch by sub-screen (0x4db51c): drawing and clicks. Each returns what the handler it
   ends in leaves in eax (or the sub-screen when there is none) ---- */
#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x40d450: the lobby drawn: the top (5: its title, or the dim overlay while connecting to a ladder game), else the
   background, the camera and the sub-screen (0 the player, 1 the arena list, 2 creating an arena) */
u32 (menuState400_frame)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 5:
		GAME_FN(lobbyTop_draw, 0x40cef0, u32, void)();   /* lobbyTop_draw */
		menu_drawBackground();
		if (g_quitAsked == 1 && g_arenaLobbyMode == 2)
			return GAME_FN(menu_drawDimOverlay, 0x40ce70, u32, void)();   /* menu_drawDimOverlay */
		return GAME_FN(lobbyTop_drawTitle, 0x408680, u32, void)();       /* lobbyTop_drawTitle */
	case 0:
		menu_drawBackground();
		GAME_FN(arena_camera, 0x408270, u32, void)();              /* arena_camera: the lobby's camera */
		return GAME_FN(lobbyPlayer_draw, 0x40cf80, u32, void)();       /* lobbyPlayer_draw */
	case 1:
		menu_drawBackground();
		GAME_FN(arena_camera, 0x408270, u32, void)();
		return GAME_FN(lobbyJoin_draw, 0x40cfd0, u32, void)();       /* lobbyJoin_draw */
	case 2:
		menu_drawBackground();
		GAME_FN(arena_camera, 0x408270, u32, void)();
		return GAME_FN(lobbyCreate_draw, 0x40d390, u32, void)();       /* lobbyCreate_draw */
	}
	return screen;
}

/* 0x4076c0: the lobby's clicks: the top (lobby_topPageClicks), the player (lobby_playerScreenClicks), the arena list (its close button
   while closing, the quit dialog while open, else connecting), creating an arena (the list's dialog, the map list,
   else the quit dialog if open, then the screen's clicks) */
u32 (lobby_onStateChange)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 5:
		return GAME_FN(lobby_topPageClicks, 0x406950, u32, void)();
	case 0:
		return GAME_FN(lobby_playerScreenClicks, 0x406a60, u32, void)();
	case 1:
		if (g_arenaConfirming)
			return GAME_FN(lobby_close, 0x406b60, u32, void)();   /* lobby_close */
		if (g_arenaLeaving)
			return GAME_FN(lobby_quitDialogClicks, 0x406bd0, u32, void)();   /* lobby_quitDialogClicks */
		return GAME_FN(lobby_connect, 0x406c30, u32, void)();       /* lobby_connect */
	case 2:
		if (g_arenaLeaving)
			return GAME_FN(create_quitDialogClicks, 0x407270, u32, void)();   /* create_quitDialogClicks */
		if (g_mapListOpen)
			return GAME_FN(mapList_mouse, 0x4036c0, u32, void)();   /* mapList_mouse: the map list */
		if (g_createQuitDialog)
			GAME_FN(lobby_pageClicks, 0x407300, u32, void)();          /* lobby_pageClicks */
		return GAME_FN(arena_createClick, 0x407410, u32, void)();       /* arena_createClick */
	}
	return screen;
}

/* 0x406b60: a click on the arena list's close button (mode 2, no dialog open): the list closed, the session search
   stopped (arena_leaveSession) and its timer (0x378) killed. Returns what the original leaves in eax */
u32 (lobby_close)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (!g_mouseClick || g_arenaLobbyMode != 2)
		return g_mouseClick;
	(*(int *)&g_cursorBlink) = 0;
	u32 hit = GAME_FN(arenaDialogBox_hitTest, 0x4044e0, u32, int, int)(g_mouseX, g_mouseY);   /* the close button's hit test */
	if (hit)
		return hit;
	g_arenaSearchTicks = 0;
	g_arenaJoinWaiting = 0;
	GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();   /* arena_leaveSession */
	g_arenaConfirming = 0;
	return IMPORT(0x4a9330, u32, void *, u32)(g_hWndMain, 0x378);   /* KillTimer */
}

/* 0x403870: the map list's keys: the first key toggles the map (mapList_ok) - or, read a second time, closes the
   list with a sound -, the others move the cursor up and down */
u32 (room_mapListKeys)(void)
{
	if (input_justPressed(g_dikO))
		return GAME_FN(mapList_ok, 0x403640, u32, void)();   /* mapList_ok */
	if (input_justPressed(g_dikO)) {
		u32 r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);   /* sound_playMenu */
		g_mapListOpen = 0;
		return r;
	}
	if (input_justPressed(g_dikA))
		return GAME_FN(mapList_chooseAll, 0x4034e0, u32, void)();   /* mapList_chooseAll */
	u32 r = input_justPressed(g_dikD);
	if (r)
		return GAME_FN(mapList_chooseNone, 0x403530, u32, void)();   /* mapList_chooseNone */
	return r;
}

/* 0x435a40: leaving the game room: the room's name sent to the others (message 0x19, 0x65 bytes), a pause of half a
   second, back to the main menu (state 300), the connection closed, the mech reloaded from the profile */
u32 (room_leaveGame)(void)
{
	strcpy(g_netLeaveBuffer, g_joinedTitleName);
	GAME_FN(net_send, 0x4521c0, int, int, int)(0x19, 0x65);   /* net_send */
	IMPORT(0x4a9110, void, u32)(500);                   /* Sleep */
	input_setKeysBlocked(4);
	g_nextScreen = 300;
	GAME_FN(debug_traceStripped, 0x48b420, void, void)();                 /* debug_traceStripped */
	GAME_FN(net_disconnect, 0x451e60, void, void)();                 /* net_disconnect */
	g_roomConnected = 0;
	return mech_loadFromProfile();
}

/* 0x407270: the create screen's quit dialog clicks, only with none of its other panels (and no dialog) open: as
   lobby_quitDialogClicks. Returns what the original leaves in eax */
u32 (create_quitDialogClicks)(void)
{
	static const u32 panels[5] = { ADDR(g_editingNewArenaName), ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword), ADDR(g_dialogOpen) };
	for (int k = 0; k < 5; k++)
		if (GAME_VAR(int, panels[k]))
			return GAME_VAR(u32, panels[k]);
	if (g_keyEnter)
		g_arenaLeaving = 0;
	if (!g_mouseClick)
		return 0;
	int button = arenaCreate_hitTest(g_mouseX, g_mouseY);
	if (button == 0) {
		g_arenaLeaving = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		g_arenaLeaving = 0;
		return 0;
	}
	return (u32)(button - 1);
}

/* 0x405230: the arena title's edit field opened: the keyboard released for typing, the input line emptied (20
   characters at most), placed at the panel's origin + (0xd8, 0xd0), the fade timer 5, the Windows edit control made.
   Returns what that leaves in eax */
u32 (arena_editTitle)(void)
{
	input_releaseKeyboard();
	g_paused = 1;
	menu_clearInputBuffer(0x14);
	memset((void *)OBJ(g_chatLine), 0, 0x400);
	(*(int *)&g_typedArenaName) = 0;
	g_chatCaretX = g_arenaGameListLeft + 0xd8;
	g_chatCaretY = g_arenaGameListTop + 0xd0;
	g_chatLength = (int)strlen(g_chatLine);
	g_typedArenaName4 = 0;
	(*(u32 *)&g_menuFade) = 0x40a00000;   /* 5 */
	/* chat_createEdit(20); the original also leaves the 20 it gave menu_clearInputBuffer on the stack as a second
	   argument */
	u32 r = GAME_FN(chat_createEdit, 0x43f460, u32, int, int)(0x14, 0x14);
	g_arenaFull = 1;
	return r;
}

/* a settings record (name, six bytes from +0x20, a password from +0x26) stored into another: the password flag
   (+0x2e: the password is not empty) set in both. Then the store's follow-up; returns what it leaves in eax */
/* (the copies are plain loops, as the original's inline string instructions: no calls before the follow-up, whose
   stack the original leaves untouched) */
static void copy_string(u8 *to, const u8 *from)
{
	do
		*to++ = *from;
	while (*from++);
}
static u32 settings_store(u8 *from, u8 *to, u32 then)
{
	u8 locked = from[0x26] != 0;
	from[0x2e] = locked;
	copy_string(to, from);
	static const u8 order[6] = { 0x21, 0x20, 0x23, 0x22, 0x25, 0x24 };
	for (int k = 0; k < 6; k++)
		to[order[k]] = from[order[k]];
	copy_string(to + 0x26, from + 0x26);
	to[0x2e] = locked;
	return GAME_CDECL(then, u32, void)();
}
/* 0x405140: the arena being created kept as the arena settings (0x4ded20), then axis.cfg loaded again */
u32 (lobby_keepArenaSettings)(void) { return settings_store((u8 *)OBJ(g_newArenaName), (u8 *)OBJ(g_playerName), FN_ADDR(cfg_loadAxisCfg, 0x42d730)); }
/* 0x433640: the room's settings kept (0x5b1b30) and written to the registry (reg_writeCharacterSettings) */
u32 (room_keepSettings)(void) { return settings_store((u8 *)OBJ(g_roomSettingsName), (u8 *)OBJ(g_roomRecName), FN_ADDR(reg_writeCharacterSettings, 0x432400)); }

/* 0x40d390: the create-arena screen drawn: the tunnel, then (modes other than 0 and 1, not on sub-screen 5) the
   dialog's frame if one is open, else the settings kept in range (players 0 .. 16 else 8, the two limits at most 250
   else 30, the map 0 .. 14 else 0), the screen, the map list when open, the options panel when shown. Returns what
   the original leaves in eax */
u32 (lobbyCreate_draw)(void)
{
	GAME_FN(arena_drawTunnel, 0x4091b0, u32, void)();   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaLobbyMode;
	if (mode == 1 || mode == 0 || g_lobbySubState == 5)
		return (u32)mode;
	if (g_dialogOpen)
		return GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(g_newArenaFormLeft, g_newArenaFormTop,
		                                                     g_newArenaFormRight, g_newArenaFormBottom);   /* menu_drawFrame */
	signed char players = (*(signed char *)&g_arenaPlayers);
	if (players < 0 || players > 0x10)
		g_arenaPlayers = 8;
	if (g_arenaFragLimit > 0xfa)
		g_arenaFragLimit = 0x1e;
	if (g_arenaTimeLimit > 0xfa)
		g_arenaTimeLimit = 0x1e;
	signed char map = (*(signed char *)&g_arenaGameType);
	if (map < 0 || map > 0xe)
		g_arenaGameType = 0;
	GAME_FN(arena_createDraw, 0x40b750, u32, void)();   /* arena_createDraw */
	if (g_mapListOpen == 1)
		GAME_FN(mapList_draw, 0x4038e0, u32, void)();   /* mapList_draw: the map list */
	if (!g_connectionAwaited)
		return 0;
	return GAME_FN(arena_connectionOutcome, 0x405b80, u32, void)();   /* arena_connectionOutcome */
}

/* 0x408110: the create screen's quit dialog keys (no other dialog open): one closes it, the other starts the arena:
   multiplayer on, the music stopped, the arena settings (0x4ded20) as the game's (map, players, limits), the lobby
   left. Returns what the original leaves in eax */
u32 (lobby_keysQuit)(void)
{
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	u32 r = input_justPressed(g_dikC);
	if (r) {
		g_createQuitDialog = 0;
		return r;
	}
	if (!input_justPressed(g_dikO))
		return 0;
	g_quitAsked = 1;
	g_netRole = 1;
	GAME_FN(music_shutdown, 0x457310, u32, void)();   /* music_shutdown */
	u32 limits = (*(u32 *)&g_arenaFragLimit);
	g_mapRotation = (*(signed char *)&g_arenaCustomize);
	g_missionStage = g_arenaMap;
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_chosenGameMode = (*(signed char *)&g_arenaGameType);
	(*(u32 *)&g_fragLimit) = limits & 0xff;
	(*(u32 *)&g_timeLimit) = (limits >> 8) & 0xff;
	g_arenaLobbyMode = 0;
	g_arenaLobbyState = 1;
	g_createQuitDialog = 0;
	return limits;
}

/* 0x406a60: the lobby player screen's clicks (mode 2, no dialog or list open): a right click goes back; buttons: 0 the
   name field, 2 the ARM CENTER, 3 the profile's record kept, 4 back, 5 the default name. Returns what the original
   leaves in eax */
u32 (lobby_playerScreenClicks)(void)
{
	int mode = g_arenaLobbyMode;
	if (mode == 1 || mode == 0 || g_dialogOpen || g_typingArenaName)
		return (u32)mode;
	if (g_keyEnter) {
		g_arenaLobbyMode = 0;
		return GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);
	}
	if (!g_mouseClick || mode != 2)
		return (u32)mode;
	u32 button = GAME_FN(arenaNameDialog_hitTest, 0x404460, u32, int, int)(g_mouseX, g_mouseY);   /* the screen's hit test */
	u32 r;
	switch (button) {
	case 0:
		return GAME_FN(arena_editName, 0x404cd0, u32, void)();   /* arena_editName */
	case 2:
		sound_playMenu(0);
		g_armcFrom = 2;
		return menu_enterMenus();   /* menu_enterMenus: the ARM CENTER */
	case 3:
		sound_playMenu(0);
		r = GAME_FN(arena_saveSettings, 0x4050a0, u32, void)();      /* arena_saveSettings */
		g_arenaLobbyMode = 0;
		return r;
	case 4:
		r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);
		g_arenaLobbyMode = 0;
		return r;
	case 5:
		sound_playMenu(0);
		return GAME_FN(cfg_defaultPlayerName, 0x4050f0, u32, void)();   /* cfg_defaultPlayerName */
	}
	return button;
}

/* a joined session's settings taken from its record (0x4a bytes): the music stopped, the 32-byte rules (+4), +0x24,
   +0x25, +0x2c and the colours (+0x2d, +0x2e); the lobby left (0x4dbb3c 0) for the game (0x67ef14 1, 0x67ef04 2) */
static void take_session(const u8 *rec)
{
	music_shutdown();
	g_missionStage = (signed char)rec[0x25];
	memcpy((void *)OBJ(g_mapTitle), rec + 4, 32);
	g_mapRotation = (signed char)rec[0x24];
	g_arenaLobbyMode = 0;
	g_quitAsked = 1;
	g_netRole = 2;
	g_chosenGameMode = (signed char)rec[0x2c];
	g_fragLimit = rec[0x2d];
	g_timeLimit = rec[0x2e];
}

/* 0x405690: arena session `session` joined: its record (0x4a bytes from 0x9087c0) gives the colours shown
   (+0x2d, +0x2e) and the join's argument (+0); a refused join shows message 0x36 (full) or 0x35. Joined, the music
   stops and the session's settings are taken: the 32-byte rules (+4), +0x24, +0x25, +0x2c, the colours. Returns the
   message's eax, or the colour +0x2e */
u32 (arena_joinSession)(int session)
{
	const u8 *rec = (const u8 *)(IMG(0x9087c0) + session * 0x4a);
	g_lobbyJoinStarted = 0;
	g_lobbyJoinRequest = 0;
	g_arenaTimeLimit = g_arenaTimeLimitTyped = rec[0x2e];
	g_arenaFragLimit = g_arenaFragLimitTyped = rec[0x2d];
	int r = dplay_join(session, *(const u32 *)rec, g_cfgPlayerName,
	                                                               g_playerCorporation);   /* dplay_join: join */
	if (r != 0x1f4)
		return GAME_FN(menu_showMessage, 0x41ee40, u32, int)(r == 0x1f5 ? 0x36 : 0x35);   /* the message */
	take_session(rec);
	g_arenaConfirming = 0;
	return rec[0x2e];
}

/* 0x4062b0 (named app_shutdown; by use the arena join's answer, from WndProc): with the join dialog up (0x4dbb78)
   message 0x44 and the connection closed; else a pending join (0x4db708) of the game picked (0x4db710: 99999 for
   the one received at 0x4dbbf8, copied into a session record at 0x9dae20, otherwise its row of the list, which
   takes the received id) is answered (dplay_join): joined, the session's settings are taken and the lobby
   connection closed; refused, messages 0x43 (501), 0x42 (502, 503), 0x44 (504), 0x45 (505) and the connection
   closed. The caller ignores the eax it leaves */
void (app_shutdown)(void)
{
	if (g_arenaJoinWaiting) {
		g_arenaSearchTicks = 0;
		g_arenaJoinWaiting = 0;
		arena_leaveSession();
		menu_showMessage(0x44);
		g_arenaConfirming = 0;
		return;
	}
	int pick = g_arenaJoinRow;
	u8 *rec;
	if (pick == 99999) {
		g_arenaJoinRow = 0;
		if (!g_arenaJoinPending)
			return;
		const u8 *in = g_receivedSession;
		rec = (u8 *)IMG(0x9dae20);
		*(u32 *)rec = *(const u32 *)in;
		rec[0x2d] = in[0x28];
		rec[0x2e] = in[0x29];
		rec[0x2c] = in[0x27];
		rec[0x25] = in[0x24];
		rec[0x24] = in[0x25];
		strcpy((char *)rec + 4, (const char *)in + 0x2e);
	} else {
		if (!g_arenaJoinPending)
			return;
		rec = (u8 *)(IMG(0x9087c0) + pick * 0x4a);
		*(u32 *)rec = *(*(const u32 **)&g_receivedSession);
		g_arenaFragLimit = rec[0x2d];
		g_arenaTimeLimit = rec[0x2e];
	}
	int r = dplay_join(0, *(const u32 *)rec, g_cfgPlayerName, g_playerCorporation);
	if (r == 0x1f4) {
		take_session(rec);
		net_disconnect();
	} else {
		static const u8 message[5] = { 0x43, 0x42, 0x42, 0x44, 0x45 };   /* 501 .. 505 */
		if ((u32)(r - 0x1f5) <= 4)
			menu_showMessage(message[r - 0x1f5]);
		arena_leaveSession();
	}
	g_arenaSearchTicks = 0;
	g_arenaJoinPending = 0;
	g_arenaConfirming = 0;
}

/* ---- a menu key: the key bound at `binding` was just pressed (the confirm sound played then) ---- */
static int key_hit(u32 binding)
{
	if (!input_justPressed(GAME_VAR(int, binding)))
		return 0;
	sound_playMenu(0);
	return 1;
}
/* back to the main menu; returns input_setKeysBlocked's eax (4) */
static u32 to_main_menu(void)
{
	u32 r = GAME_FN(input_setKeysBlocked, 0x441250, u32, int)(4);   /* input_setKeysBlocked: keys blocked */
	g_nextScreen = 300;
	GAME_FN(debug_traceStripped, 0x48b420, void, void)();          /* debug_traceStripped */
	return r;
}

/* 0x407750: the lobby's top page keys (no dialog open, not while 0x67ef14 is 1): back (when 0x9dae10 allows) or
   leave goes to the main menu; the other three pick the lobby's sub-pages 2, 0 and 1. Returns the action's eax */
u32 (lobbyTop_keys)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_quitAsked == 1)
		return 0;
	if (input_justPressed(g_keyCancel2) && g_tunnelRings > 0) {
		sound_playMenu(0);
		return to_main_menu();
	}
	if (key_hit(ADDR(g_dikC)))
		return GAME_FN(lobby_setSubState2, 0x404c20, u32, void)();   /* lobby_setSubState2 */
	if (key_hit(ADDR(g_dikP)))
		return GAME_FN(lobby_setSubState0, 0x404ac0, u32, void)();   /* lobby_setSubState0 */
	if (key_hit(ADDR(g_dikJ)))
		return GAME_FN(lobby_setSubState1, 0x404b30, u32, void)();   /* lobby_setSubState1 */
	if (key_hit(ADDR(g_dikX)))
		return to_main_menu();
	return 0;
}

/* 0x406950: the lobby's top page clicks (no dialog open, not while 0x67ef14 is 1): a left click on one of its four
   buttons (outlines at 0x5b1cf8) picks sub-page 0, 1 or 2 or goes back to the main menu; a right click (when
   0x9dae10 allows) goes back too. Returns what the original leaves in eax */
u32 (lobby_topPageClicks)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_quitAsked == 1)
		return 0;
	if (g_mouseClick) {
		const Outline *buttons = (const Outline *)OBJ(g_lobbyTopOutlines);
		for (int i = 0; i < 4; i++) {
			if (point_in_outline(g_mouseX, g_mouseY, buttons[i]) != 1)
				continue;
			sound_playMenu(0);
			switch (i) {
			case 0: GAME_FN(lobby_setSubState0, 0x404ac0, void, void)(); break;   /* lobby_setSubState0 */
			case 1: GAME_FN(lobby_setSubState1, 0x404b30, void, void)(); break;   /* lobby_setSubState1 */
			case 2: GAME_FN(lobby_setSubState2, 0x404c20, void, void)(); break;   /* lobby_setSubState2 */
			case 3: to_main_menu(); break;
			}
			break;
		}
	}
	int right = g_keyEnter;
	if (!right)
		return 0;
	int allowed = g_tunnelRings;
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	return to_main_menu();
}

/* 0x407840: the lobby's player page keys (page open, 0x4dbb3c not 0 or 1; no dialog): while the name is being typed
   (0x4dbbd0), the typed line (0x9dc92c) becomes the player's name (0x4db560, 32 bytes) once the keyboard is back
   (0x68039c clear) and typing ends; otherwise back closes the page, 0x4e1510 applies (0x4050a0) and closes it,
   0x4e0ce0 resets the name to the default, 0x4e0cdc closes it. Returns what the original leaves in eax */
u32 (lobbyPlayer_keys)(void)
{
	u32 page = (*(u32 *)&g_arenaLobbyMode);
	if (page == 1 || page == 0 || g_dialogOpen)
		return page;
	if (g_typingArenaName) {
		if (g_paused)
			return page;
		const char *typed = g_chatLine;
		u32 length = strlen(typed);
		g_typingArenaName = 0;
		if (!length)
			return 0;
		memset((void *)OBJ(g_arenaName), 0, 32);
		strcpy(g_arenaName, typed);
		return length + 1;
	}
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_arenaLobbyMode = 0;
	}
	if (input_justPressed(g_dikO)) {
		sound_playMenu(0);
		GAME_FN(arena_saveSettings, 0x4050a0, void, void)();
		g_arenaLobbyMode = 0;
	}
	if (input_justPressed(g_dikD)) {
		sound_playMenu(0);
		return GAME_FN(cfg_defaultPlayerName, 0x4050f0, u32, void)();   /* cfg_defaultPlayerName */
	}
	if (!input_justPressed(g_keyBack))
		return 0;
	u32 r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);      /* sound_playMenu */
	g_arenaLobbyMode = 0;
	return r;
}

/* 0x4060f0: the lobby server connection opened (unless open, 0x4db718): the old one closed, net_connect(100) (0: no
   server, message 0x3d; 2: message 0x46) and the socket's messages sent to the main window (failing: 0x3e). Then
   the lobby screen's state reset and the hello sent (0x180001, net_send(0xd, 100)). 1, or 0 on a failure */
int (lobby_openConnection)(void)
{
	if (!g_lobbyConnectionOpen) {
		GAME_FN(net_disconnect, 0x451e60, void, void)();                   /* net_disconnect */
		int r = net_connect(100);
		if (r == 0 || r == 2) {
			menu_showMessage(r == 0 ? 0x3d : 0x46);   /* the message */
			return 0;
		}
		if (!net_asyncSelect(g_mainWindow, 100)) {   /* net_asyncSelect */
			menu_showMessage(0x3e);
			return 0;
		}
	}
	g_lobbyConnectionOpen = 1;
	g_serverConnected = 1;
	g_connectionAwaited = 1;
	g_connectStep = 2;
	g_serverAnswerIn = 0;
	g_lobbyRefreshing = 0;
	g_lobbySearching = 1;
	g_searchResult = 0;
	g_lobbyListPage = 0;
	g_arenaNameSum = 0;
	g_serverConnectionState = 0;
	g_unusedRoomListWord = 0;
	g_gameCount = 0;
	g_arenaListFull = 1;
	g_arenaHaveList = 0;
	g_localPlayer = 0;
	(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000.0f */
	g_gameListTop = 0;
	g_lobbyListRow = 0;
	*g_netLobbyMessage = 0x180001;   /* the message to send */
	GAME_FN(net_send, 0x4521c0, int, int, int)(0xd, 100);   /* net_send */
	g_arenaConfirming = 0;
	g_listRefreshPeriod = 30;
	return 1;
}

/* 0x40d840: the arena screen entered. Started by the launcher (0x76d364 = 1): its settings (axiswl.dat,
   arena_loadSettings; none: quit) give the player (name 0x5b191c into 0x4ded20, the optional clan 0x5b193c, the
   colours and corporation bytes 0x4ded40..45), then the lobby's sub-page 1 and the name check (screen 0x68).
   Otherwise the lobby page with the server name (0x4de748 into 0x4dbbd4) and 0x406200(99999) (screen 0x69).
   Returns the last call's eax */
u32 (arena_loadAndQuit)(void)
{
	if (g_startedByLauncher != 1) {
		GAME_FN(menuState400_enter, 0x404640, void, void)();   /* menuState400_enter */
		GAME_FN(lobby_setSubState1, 0x404b30, void, void)();   /* lobby_setSubState1 */
		memset((void *)ADDR(g_typedArenaName), 0, 24);
		strcpy((char *)ADDR(g_typedArenaName), (const char *)IMG(0x4de748));
		u32 r = GAME_FN(arena_joinListed, 0x406200, u32, int)(99999);   /* arena_joinListed */
		g_lobbyReply = 0x69;
		return r;
	}
	if (!arena_loadSettings((const char *)STR(0x4ad5e4, "axiswl.dat")))
		return IMPORT(0x4a932c, u32, int)(0);                               /* PostQuitMessage */
	memset((void *)OBJ(g_playerName), 0, 32);
	strcpy(g_playerName, (const char *)IMG(0x5b191c));
	u8 clan = (*(u8 *)&g_cmdSecret);
	g_unusedPlayerRecord26 = 0;
	g_playerHasClan = clan;
	g_unusedPlayerRecord2a = 0;
	if (clan == 1)
		strcpy((char *)ADDR(g_unusedPlayerRecord26), (const char *)ADDR(g_arenaFileClan));
	g_arenaFragLimit = g_arenaFileFragLimit;
	g_arenaGameType = g_arenaFileGameType;
	g_arenaCustomize = 0;
	(*(u8 *)&g_arenaMap) = g_arenaFileMap;
	g_arenaPlayers = g_arenaFilePlayers;
	g_arenaTimeLimit = (*(u8 *)&g_cmdTimeLimit);
	GAME_FN(menuState400_enter, 0x404640, void, void)();
	GAME_FN(lobby_setSubState1, 0x404b30, void, void)();
	u32 r = GAME_FN(lobby_checkReservedName, 0x4057a0, u32, void)();   /* lobby_checkReservedName */
	g_lobbyReply = 0x68;
	return r;
}

/* 0x407300: the lobby page's clicks (nothing else open: 0x4dbab0, 0x4db850, 0x4db518, 0x4dbacc, no dialog): a right
   click or button 0x11 closes the page (0x4db55c); button 0x10 starts the game with the player's settings (the
   32-byte record 0x4ded20 and its colour / corporation bytes), the music stopped. Returns what the original
   leaves in eax */
u32 (lobby_pageClicks)(void)
{
	u32 busy = (*(u32 *)&g_editingNewArenaName);
	if (busy || g_editingNewArenaFragLimit || g_editingNewArenaTimeLimit || g_typingArenaPassword || g_dialogOpen)
		return busy;
	if (g_keyEnter) {
		g_createQuitDialog = 0;
		return 0;
	}
	if (!g_mouseClick)
		return 0;
	int button = createArena_hitTest(g_mouseX, g_mouseY);
	if (button == 0x11) {
		g_createQuitDialog = 0;
		return 0;
	}
	if (button != 0x10)
		return button - 0x11;
	g_quitAsked = 1;
	g_netRole = 1;
	music_shutdown();
	g_mapRotation = (signed char)g_arenaCustomize;
	g_missionStage = (signed char)(*(u8 *)&g_arenaMap);
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_chosenGameMode = (signed char)g_arenaGameType;
	g_fragLimit = g_arenaFragLimit;
	g_timeLimit = g_arenaTimeLimit;
	g_arenaLobbyMode = 0;
	g_arenaLobbyState = 1;
	g_createQuitDialog = 0;
	return (*(u32 *)&g_arenaFragLimit);
}

/* 0x405b80: the arena connection's outcome (0x4ded60; 2 nothing to do). 1 connected: the music stopped, the player
   slot opened (arena_openSession), the arena hosted with the player's record (0x4ded20: name, 0x4dedb0, colours,
   corporation; 0x4dedd0) and its settings taken for the game, 0x4ded54 set; then (as the state stands after) 0
   closed, 3 closed for a ladder game (0x907b2c), 4 refused (message 0x46): the connection closed (net_451e60) and
   the state back to 2. Returns what the original leaves in eax */
u32 (arena_connectionOutcome)(void)
{
	int state = g_connectStep;
	if (state == 2)
		return 2;
	const u8 *me = (const u8 *)OBJ(g_playerName);
	if (state == 1) {
		g_connectionAwaited = 0;
		g_quitAsked = 1;
		g_netRole = 1;
		music_shutdown();
		g_arenaLobbyMode = 0;
		GAME_FN(arena_openSession, 0x452ec0, void, int, int)(0, 0);   /* arena_openSession */
		GAME_FN(dplay_host, 0x453090, void, const void *, const void *, int, int, int, int, int, u32)(me, (const void *)OBJ(g_cfgPlayerName),
			(int)(signed char)me[0x22] << 8 | (int)(signed char)me[0x20], (signed char)me[0x21], (signed char)me[0x23],
			me[0x24], me[0x25], (*(u32 *)&g_playerCorporation));   /* dplay_host: host */
		g_missionStage = (signed char)me[0x20];
		memcpy((void *)OBJ(g_mapTitle), me, 32);
		g_mapRotation = (signed char)me[0x22];
		g_chosenGameMode = (signed char)me[0x23];
		g_fragLimit = me[0x24];
		g_timeLimit = me[0x25];
		state = g_connectStep;
		g_arenaGameSetUp = 1;
	}
	if (state != 0 && state != 3 && state != 4)
		return state;
	u32 r = net_disconnect();   /* net_451e60: the connection closed */
	g_connectStep = 2;
	if (state == 3)
		g_arenaLeaving = 1;
	g_connectionAwaited = 0;
	g_arenaGameSetUp = 0;
	if (state == 4)
		r = GAME_FN(menu_showMessage, 0x41ee40, u32, int)(0x46);   /* the message */
	return r;
}

/* 0x407e40: the "create arena" page after typing (not while typing or with a message box): a typed field is taken
   (the arena's name into 0x4db528 unless blank (sound 6); the password into 0x4db54e; the two limits as numbers,
   0 .. 250 (else 250), into the bytes 0x4db54c / 0x4db54d; an empty line changes nothing), else the keys: create
   (0x4e14f4; lobby_4052c0) and join (0x4e1528; 0x405cf0, then the name check) unless connecting, and the two close
   keys (the arena left). Returns what the original leaves in eax */
u32 (lobbyTop_connect)(void)
{
	u32 mode = (*(u32 *)&g_arenaLobbyMode);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	const char *line = g_chatLine;
	if (g_editingNewArenaName) {   /* the arena's name */
		if (g_paused)
			return mode;
		if (!strlen(line) || GAME_FN(name_isBlank, 0x4343b0, int, const char *)(line) == 1) {   /* name_isBlank: blank */
			u32 r = strlen(line) ? GAME_FN(sound_playMenu, 0x41e760, u32, int)(6) : 0;
			g_editingNewArenaName = 0;
			return r;
		}
		g_editingNewArenaName = 0;
		memset((void *)OBJ(g_newArenaName), 0, 32);
		strcpy(g_newArenaName, line);
		return strlen(line) + 1;
	}
	if (g_typingArenaPassword) {   /* the password */
		if (g_paused)
			return mode;
		memset((void *)ADDR(g_newArenaPassword), 0, 8);
		g_typingArenaPassword = 0;
		g_chatFieldFlag = 0;
		strcpy((char *)ADDR(g_newArenaPassword), line);
		return 0;
	}
	static const u32 limit[2][2] = { { ADDR(g_editingNewArenaFragLimit), ADDR(g_arenaFragLimitTyped) }, { ADDR(g_editingNewArenaTimeLimit), ADDR(g_arenaTimeLimitTyped) } };
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(int, limit[k][0]))
			continue;
		if (g_paused)
			return mode;
		if (!strlen(line)) {
			GAME_VAR(int, limit[k][0]) = 0;
			return 0;
		}
		int v = crt_atoi(line);
		if (v > 250 || v < 0)
			v = 250;
		GAME_VAR(int, limit[k][0]) = 0;
		GAME_VAR(u8, limit[k][1]) = (u8)v;
		return (u32)v;
	}
	if (input_justPressed(g_dikI) && !g_arenaGameSetUp) {
		sound_playMenu(0);
		return GAME_FN(lobby_roomNameCheck, 0x4052c0, u32, void)();   /* lobby_4052c0: create */
	}
	if (input_justPressed(g_dikT) && !g_arenaGameSetUp) {
		sound_playMenu(0);
		u32 r = GAME_FN(lobby_checkReservedName2, 0x405cf0, u32, void)();
		return r ? r : GAME_FN(lobby_checkReservedName, 0x4057a0, u32, void)();   /* lobby_checkReservedName */
	}
	u32 r = 0;
	static const u32 close[2] = { ADDR(g_dikC), ADDR(g_dikEscape_2) };
	for (int k = 0; k < 2; k++) {
		r = (u32)input_justPressed(GAME_VAR(int, close[k]));
		if (r) {
			arena_leaveSession();   /* arena_leaveSession: the arena left */
			g_arenaLobbyMode = 0;
			r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);
		}
	}
	return r;
}

/* 0x407410: the "create arena" page clicked (no field being typed, page state 2, no message box; a right click leaves
   the arena). Buttons (createArena_hitTest): 0 / 1 / 6 / 7 type a field (0x404d70, 0x404f90, 0x404e10, 0x404ed0), 2 / 12 /
   14 the map on and 13 back (lobby_4068d0), 3 the players +2 (to 16, then 2), 4 custom on / off (0x4db54a; the game
   type kept in range), 5 the game type on (with a turn key held back) through 0 .. 13 (0 .. 14 when custom), 8
   create and 9 join (unless connecting), 11 leave, 15 the custom map list (when custom; mapList_startEdit). Returns what
   the original leaves in eax (for the byte settings, its low byte the new value) */
u32 (arena_createClick)(void)
{
	if (g_editingNewArenaName)
		return (*(u32 *)&g_editingNewArenaName);
	if (g_editingNewArenaFragLimit || g_editingNewArenaTimeLimit || g_typingArenaPassword)
		return 0;
	u32 mode = (*(u32 *)&g_arenaLobbyMode);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	if (g_keyEnter) {
		sound_playMenu(0);
		u32 r = GAME_FN(arena_leaveSession, 0x452fe0, u32, void)();   /* arena_leaveSession: the arena left */
		g_arenaLobbyMode = 0;
		return r;
	}
	if (!g_mouseClick || mode != 2)
		return mode;
	u32 button = GAME_FN(createArena_hitTest, 0x404520, u32, int, int)(g_mouseX, g_mouseY);   /* createArena_hitTest */
	u8 *players = (u8 *)ADDR(g_newArenaPlayers), *custom = (u8 *)ADDR(g_newArenaKind), *type = (u8 *)ADDR(g_newArenaMode);
	u32 r;
	u8 old;
	switch (button) {
	case 0: return GAME_FN(arena_editComment, 0x404d70, u32, void)();
	case 1: return GAME_FN(arena_editPassword, 0x404f90, u32, void)();
	case 6: return GAME_FN(arena_editFragLimit, 0x404e10, u32, void)();
	case 7: return GAME_FN(arena_editTimeLimit, 0x404ed0, u32, void)();
	case 2:
		sound_playMenu(2);
		/* fall through */
	case 12: case 14:
		return GAME_FN(arena_stepMap, 0x4068d0, u32, int)(1);   /* lobby_4068d0: the next map */
	case 13:
		return GAME_FN(arena_stepMap, 0x4068d0, u32, int)(0);
	case 3:
		*players += 2;
		r = *players;
		if ((signed char)*players > 16)
			*players = 2;
		return r;
	case 4:
		old = *custom;
		*custom = 1 - old;
		if (*custom)
			*type = 0xe;
		else if ((signed char)*type > 0xd)
			*type = 0;
		return old;
	case 5:
		r = (u32)input_isDown(g_dikLShift);
		if (!r) r = (u32)input_isDown(g_dikRShift);
		if (!r) r = (u32)input_isDown(g_dikLCtrl);
		if (!r) r = (u32)input_isDown(g_dikRCtrl);
		if (r) {   /* back */
			*type -= 1;
			r = (r & ~0xffu) | *type;
			if ((signed char)*type < 0)
				*type = *custom ? 0xe : 0xd;
		} else {
			*type += 1;
			r = *type;
			if ((signed char)*type > (*custom ? 0xe : 0xd))
				*type = 0;
		}
		return r;
	case 8:
		if (g_arenaGameSetUp)
			return 8;
		sound_playMenu(0);
		return GAME_FN(lobby_roomNameCheck, 0x4052c0, u32, void)();   /* lobby_4052c0: create */
	case 9:
		if (g_arenaGameSetUp)
			return 9;
		sound_playMenu(0);
		r = GAME_FN(lobby_checkReservedName2, 0x405cf0, u32, void)();
		return r ? r : GAME_FN(lobby_checkReservedName, 0x4057a0, u32, void)();   /* lobby_checkReservedName */
	case 11:
		arena_leaveSession();
		g_arenaLobbyMode = 0;
		return GAME_FN(sound_playMenu, 0x41e760, u32, int)(0);
	case 15:
		if (*custom != 1)
			return 15;
		sound_playMenu(2);
		return GAME_FN(mapList_startEdit, 0x403490, u32, int)(1);   /* mapList_startEdit: the map list (the original pushes a 1 it ignores) */
	}
	return button;
}

/* 0x4079c0: the arena lobby's join screen keys (none while the "full" or "joining" box, a message box, or in modes
   0 / 1 (0x4dbb3c)). With the join confirmation up only back answers it (the timer 0x378 killed). Up / down held
   move along the list of games (once the blink clock reaches 5, restarting it; nine rows shown from g_gameListTop, the
   selection in 0x76d41c); while no search runs (0x4dba90, 0x4db858, the result box 0x4db8b8) the click key or fire
   joins the selected game (0x4dbbec; the chat line opened when connected, 0x4dbaac) or asks its password
   (0x4dbbf0); cancel2 and back leave (to mode 0), 0x4e1524 cancels the search; 0x4e14f4 searches the local network
   (a slot opened, 0x4dba80 150), 0x4e1528 the lobby server; 0x4e1514 edits the arena's title */
void (lobbyJoin_keysChat)(void)
{
#define g_listTop g_gameListTop
#define g_listRow g_lobbyListRow
#define busy (g_lanSearch || g_lobbySearching || g_lobbyRefreshing)
	int mode = g_arenaLobbyMode;
	if (g_arenaFull || mode == 1 || mode == 0 || g_arenaJoining || g_dialogOpen)
		return;
	if (g_arenaConfirming) {
		if (input_justPressed(g_keyBack)) {
			g_arenaSearchTicks = 0;
			g_arenaJoinWaiting = 0;
			arena_leaveSession();
			g_arenaConfirming = 0;
			KillTimer(g_hWndMain, 0x378);
		}
		return;
	}
	if (input_isDown(g_keyUp)) {
		if (!(g_cursorBlink >= k_5f))
			return;
		int row = g_listRow;
		g_cursorBlink = 0.0f;
		if (row > 0)
			g_listRow = --row;
		else if (g_listTop > 0)
			g_listTop--;
		g_localPlayer = g_listTop + row;
		return;
	}
	if (input_isDown(g_keyDown)) {
		if (!(g_cursorBlink >= k_5f))
			return;
		g_cursorBlink = 0.0f;
		if (g_listTop + g_listRow >= g_gameCount - 1)
			return;
		if (g_listRow < 8)
			g_listRow++;
		else
			g_listTop++;
		g_localPlayer = g_listTop + g_listRow;
		return;
	}
	if (input_justPressed(g_dikJ) || input_justPressed(g_keyClick)) {
		if (busy || g_gameCount <= 0)
			return;
		if (g_serverConnected) {
			g_lobbyJoinStarted = 1;
			g_lobbyJoinRequest = 0;
			arena_chatLine();
		} else {
			g_lobbyJoinRequest = 1;
			g_lobbyJoinStarted = 0;
		}
		return;
	}
	if (input_justPressed(g_keyCancel2)) {
		g_serverConnectionState = 0;
		arena_leaveSession();
		net_disconnect();
		g_serverAnswerIn = 1;
		g_arenaLobbyMode = 0;
		(*(u32 *)&g_lobbyBlinkClock) = 0x3f800000;   /* 1 */
		return;
	}
	if (input_justPressed(g_dikS)) {
		g_serverConnectionState = 0;
		(*(u32 *)&g_lobbyBlinkClock) = 0x3f800000;
		g_serverAnswerIn = 1;
		g_searchResult = -1;
		g_lobbyConnectionOpen = 0;
		arena_leaveSession();
		net_disconnect();
		if (g_lobbyRefreshing == 1) {
			g_lobbyRefreshing = 0;
			g_lobbySearching = 0;
			g_serverAnswerIn = 0;
		}
		g_netListDone = 1;
		return;
	}
	if (input_justPressed(g_keyBack)) {
		if (busy)
			return;
		g_serverConnectionState = 0;
		(*(u32 *)&g_lobbyBlinkClock) = 0x3f800000;
		g_serverAnswerIn = 1;
		arena_leaveSession();
		net_disconnect();
		g_arenaLobbyMode = 0;
		return;
	}
	if (input_justPressed(g_dikI)) {
		if (busy)
			return;
		if (g_serverSearching) {
			g_lobbyConnectionOpen = 0;
			net_disconnect();
		}
		if (g_arenaSearchStarted)
			arena_leaveSession();
		g_serverListCount = 0;
		arena_openSession(1, NULL);
		g_lanSearch = 1;
		g_arenaSearchStarted = 1;
		g_lobbyListPage = 0;
		g_gameCount = 0;
		g_serverConnected = 0;
		g_serverSearching = 0;
		(*(u32 *)&g_lobbyBlinkClock) = 0x43160000;   /* 150 */
		return;
	}
	if (input_justPressed(g_dikT)) {
		if (busy)
			return;
		g_lobbyConnectionOpen = 0;
		net_disconnect();
		arena_leaveSession();
		g_serverListCount = 0;
		if (lobby_openConnection() == 1) {
			g_serverConnected = 1;
			g_lobbySearching = 1;
			g_serverSearching = 1;
			g_lobbyConnectionOpen = 1;
			g_arenaSearchStarted = 0;
		}
		return;
	}
	if (input_justPressed(g_dikP) && !g_arenaFull) {
		sound_playMenu(0);
		arena_editTitle();
	}
#undef g_listTop
#undef g_listRow
#undef busy
}

/* ---- the player's record (from 0x4de700: the name, +0x1e the level, +0x22 points, +0x26 rating, +0x2a 0x4de72a,
   +0x2e wins, +0x32 losses) and its two kept copies (0x9dd5d8 and 0x9dd240: +0 level, +4 points, +0xc rating,
   +0x10 0x4de72a's value, +0x14 wins, +0x18 losses, +0x1c the win rate) ---- */
#define R_POINTS g_titlePoints
#define R_RATING (*(float *)&g_titleRating)
#define R_OTHER g_titleScore
#define R_WINS g_titleWins
#define R_LOSSES g_titleLosses

/* the win rate in percent (as its float bits): 0 without games (and, when checked, with a total not above 0) */
static u32 win_rate(int wins, int losses, int checked)
{
	if (!wins && !losses)
		return 0;
	int total = wins + losses;
	if (checked && total <= 0)
		return 0;
	float rate = f32(fmul_m((long double)wins, (const float *)ADDR(k_100f)) / (long double)total);   /* x 100 / total */
	return BITS(rate);
}

/* the rating: the rate x 0.01 x the points */
static void rate_points(u32 rate)
{
	float r;
	BITS(r) = rate;
	R_RATING = f32(fmul_m(fld_m(&r), (const float *)ADDR(k_0_01f)) * (long double)R_POINTS);
}

/* a kept copy taken back as the record, when the record's wins are more than 300 above it */
static u32 take_back(u32 kept, u32 rate)
{
	if (R_WINS <= GAME_VAR(int, kept + 0x14) + 300)
		return rate;
	R_POINTS = GAME_VAR(int, kept + 4);
	R_LOSSES = GAME_VAR(int, kept + 0x18);
	R_OTHER = GAME_VAR(int, kept + 0x10);
	R_WINS = GAME_VAR(int, kept + 0x14);
	rate = win_rate(R_WINS, R_LOSSES, 0);
	rate_points(rate);
	return rate;
}

/* the record into the packet (0xa0b338: the name when asked, then the same fields from +0x1e) and both kept
   copies, and sent to the game server (kind 0x11) */
static void record_send(u32 rate, int name)
{
	u8 *packet = g_netPlayerRecordPacket;
	if (name)
		strcpy((char *)packet, g_titleName);
	*(int *)(packet + 0x1e) = R_OTHER;
	*(int *)(packet + 0x22) = R_WINS;
	*(int *)(packet + 0x26) = R_LOSSES;
	*(int *)(packet + 0x2a) = R_POINTS;
	*(float *)(packet + 0x32) = f32(fld_m(&R_RATING));
	*(int *)(packet + 0x2e) = actor_levelFromValue(R_POINTS);
	static const u32 kept[2] = { ADDR(g_pilotLevel), ADDR(g_pilotLevelKept) };
	for (int k = 0; k < 2; k++) {
		GAME_VAR(int, kept[k] + 0x10) = R_OTHER;
		GAME_VAR(int, kept[k] + 0x14) = R_WINS;
		GAME_VAR(int, kept[k] + 0x18) = R_LOSSES;
		GAME_VAR(int, kept[k] + 4) = R_POINTS;
		GAME_VAR(int, kept[k]) = (signed char)actor_levelFromValue(R_POINTS);
		GAME_VAR(u32, kept[k] + 0x1c) = rate;
		GAME_VAR(u32, kept[k] + 0xc) = (*(u32 *)&R_RATING);
	}
	net_send(0x11, 0x65);
}

/* 0x4327f0: the player's record checked and sent: the rating worked out from the win rate; a kept copy (0x9dd5d8,
   then 0x9dd240) taken back when the record's wins are more than 300 above it; the record sent and kept; then, when
   the points are more than 150 a win, they are cut to 2 a win and the record is sent and kept again. The caller
   ignores the eax it leaves */
void (profile_checkAndSendRecord)(void)
{
	u32 rate = win_rate(R_WINS, R_LOSSES, 1);
	rate_points(rate);
	rate = take_back(ADDR(g_pilotLevel), rate);
	rate = take_back(ADDR(g_pilotLevelKept), rate);
	record_send(rate, 1);
	if (R_WINS * 150 >= R_POINTS)
		return;
	R_POINTS = R_WINS * 2;
	rate = win_rate(R_WINS, R_LOSSES, 0);
	rate_points(rate);
	record_send(rate, 0);
}
#undef R_POINTS
#undef R_RATING
#undef R_OTHER
#undef R_WINS
#undef R_LOSSES

/* ---- hosting under a name: the special rooms ---- */
#define lstrcpyA(dst, src) IMPORT(0x4a911c, char *, char *, const char *)(dst, src)

/* a game named like one of the special rooms gets its hidden map (22 .. 24, which the map list never offers):
   JamieSystem 0x18, Operator Room 0x16, Developer Room 0x17 (each in Korean and three spellings) */
static void special_map(const char *name, u8 *map)
{
	static const struct { u8 map; u32 names[4]; } rooms[3] = {
		{ 0x18, { STR(0x4ad554, "\300\347\271\314\275\303\275\272\305\333\260\263\271\337"), STR(0x4ad548, "jamiesystem"), STR(0x4ad53c, "JAMIESYSTEM"), STR(0x4ad530, "JamieSystem") } },
		{ 0x16, { STR(0x4ad524, "\277\356\277\265\300\332\271\346"), STR(0x4ad514, "operator room"), STR(0x4ad504, "OPERATOR ROOM"), STR(0x4ad4f4, "Operator Room") } },
		{ 0x17, { STR(0x4ad4e8, "\260\263\271\337\300\332\271\346"), STR(0x4ad4d8, "developer room"), STR(0x4ad4c8, "DEVELOPER ROOM"), STR(0x4ad4b8, "Developer Room") } } };
	for (int r = 0; r < 3; r++)
		for (int k = 0; k < 4; k++)
			if (!strcmp(name, (const char *)rooms[r].names[k])) {
				*map = rooms[r].map;
				break;
			}
}

#define ARENA(off) GAME_VAR(signed char, OBJ(g_playerName) + (off))   /* the arena's settings: the name, then the map (+0x20) .. */

/* the arena hosted with its settings (dplay_host): 0 when that failed */
static int host_arena(void)
{
	return dplay_host(g_playerName, g_cfgPlayerName, ((int)ARENA(0x22) << 8) | (int)ARENA(0x20),
	                    ARENA(0x21), ARENA(0x23), (u8)ARENA(0x24), (u8)ARENA(0x25), g_playerCorporation);
}

/* the hosted arena's settings taken for the match */
static void take_arena(void)
{
	g_missionStage = ARENA(0x20);
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_mapRotation = ARENA(0x22);
	g_chosenGameMode = ARENA(0x23);
	g_fragLimit = (u8)ARENA(0x24);
	g_timeLimit = (u8)ARENA(0x25);
	g_arenaGameSetUp = 1;
}

/* 0x4052c0: the arena hosted on the local network (a slot opened, kind 1): the settings kept, a special room's map;
   the slot or the hosting failing, the game state put back and the connection closed (0x4db55c set); else the music stopped and the
   settings taken (0x4dbbf4 1, back to lobby mode 0). The callers ignore the eax it leaves */
void (lobby_roomNameCheck)(void)
{
	int was = g_netRole;
	g_quitAsked = 1;
	g_netRole = 1;
	lobby_keepArenaSettings();
	int hosted = arena_openSession(1, NULL);
	if (hosted) {
		special_map(g_playerName, (u8 *)ADDR(g_arenaMap));
		hosted = host_arena();
	}
	if (!hosted) {
		g_createQuitDialog = 1;
		g_quitAsked = 0;
		g_netRole = was;
		arena_leaveSession();
		return;
	}
	music_shutdown();
	g_arenaLobbyState = 1;
	take_arena();
	g_arenaLobbyMode = 0;
}

/* 0x4057a0: the arena hosted through DirectPlay (a slot opened, kind 0): the music stopped first, a special room's
   map, the arena hosted and its settings taken whatever the answer. The callers ignore the eax it leaves */
void (lobby_checkReservedName)(void)
{
	g_arenaLobbyState = 2;
	g_quitAsked = 1;
	g_netRole = 1;
	music_shutdown();
	g_arenaLobbyMode = 0;
	arena_openSession(0, NULL);
	special_map(g_playerName, (u8 *)ADDR(g_arenaMap));
	host_arena();
	take_arena();
}

/* 0x405cf0: the arena announced on the lobby server: the settings kept, connected (messages 0x3d no server, 0x46
   refused, 0x3e no events; 0), a special room's map, the hello packet (0xa0b310: kind 0x18, the settings, the
   arena's name, this machine's address) sent as kind 10. Returns 1 when sent */
int (lobby_checkReservedName2)(void)
{
	lobby_keepArenaSettings();
	int r = net_connect(100);
	if (r == 0) {
		menu_showMessage(0x3d);
		return 0;
	}
	if (r == 2) {
		menu_showMessage(0x46);
		return 0;
	}
	if (!net_asyncSelect(g_hWndMain, 100)) {
		menu_showMessage(0x3e);
		return 0;
	}
	g_arenaGameSetUp = 1;
	special_map(g_playerName, (u8 *)ADDR(g_arenaMap));
	u8 *packet = g_roomPacket;
	packet[0] = 0x18;
	packet[0x49] = ARENA(0x22);
	packet[0x48] = ARENA(0x25);
	packet[0x47] = ARENA(0x24);
	packet[0x46] = ARENA(0x23);
	packet[0x45] = 1;
	packet[0x43] = ARENA(0x20);
	packet[0x44] = ARENA(0x21);
	packet[0x52] = ARENA(0x2e);
	lstrcpyA((char *)packet + 0x53, (const char *)ADDR(g_unusedPlayerRecord26));
	lstrcpyA((char *)g_roomPacket + 1, g_playerName);
	jmp_net_getLocalAddress();
	lstrcpyA((char *)g_roomPacket + 0x33, g_localAddress);
	g_connectionAwaited = 1;
	g_connectStep = 2;
	net_send(0xa, 0x64);
	g_arenaLobbyState = 2;
	return 1;
}
#undef ARENA

/* 0x4351c0: the game room's game announced on the game server: the room's settings kept (0x5b1b30), a special
   room's map, the packet (0xa0b328: kind 0x18, the player's name 0x9dd570 at +0x43, the settings, the game's name,
   this machine's address) sent as kind 0x12. The callers ignore the eax it leaves */
void (lobby_checkReservedName3)(void)
{
	room_keepSettings();
	special_map(g_roomRecName, (u8 *)ADDR(g_roomRecMap));
	u8 *packet = g_arenaPacket;
	GAME_CDECL(0x49ea80, char *, char *, const char *, int)((char *)packet + 0x43, g_joinedTitleName, 0x1e);   /* strncpy */
	packet = g_arenaPacket;
	const u8 *room = (const u8 *)OBJ(g_roomRecName);
	packet[0] = 0x18;
	packet[0x67] = room[0x22];
	packet[0x66] = room[0x25];
	packet[0x65] = room[0x24];
	packet[0x64] = room[0x23];
	packet[0x63] = 1;
	packet[0x61] = room[0x20];
	packet[0x62] = room[0x21];
	packet[0x70] = room[0x2e];
	lstrcpyA((char *)packet + 0x71, g_roomRecName + 0x26);
	lstrcpyA((char *)g_arenaPacket + 1, g_roomRecName);
	jmp_net_getLocalAddress();
	lstrcpyA((char *)g_arenaPacket + 0x33, g_localAddress);
	g_connectionAwaited = 1;
	g_connectStep = 2;
	net_send(0x12, 0x65);
	g_arenaLobbyState = 2;
}
#undef lstrcpyA
