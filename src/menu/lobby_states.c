/* lobby_states.c: the arena lobby's and the game room's screens set up as they are entered: the camera's target point
   for the screen (and its look-at point), the screen's state cleared, the panel brightness (0x3f333333 = 0.7), the
   message box hidden (g_arenaTunnelDepth / g_roomPanelBrightness), and for the lists the map list or the ranking reset. The lobby's
   three sub-screens are 0 (the player's own record), 1 (the arena list) and 2 (creating an arena). */
#include "../game.h"
#include <string.h>


static void clear_all(const u32 *addresses, int n)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(int, addresses[k]) = 0;
}

/* 0x404ac0: sub-screen 0, the player's record: the camera to (35, 0) looking at (-70, 35), the record from axis.cfg
   (arena_loadPlayerSettings) */
void (lobby_enterPlayerScreen)(void)
{
	int z = g_menuCameraHeight;
	(*(u32 *)&g_camPoint0X) = 0x420c0000;   /* 35.0 */
	g_camPoint0Y = 0;
	g_camPoint0Z = z;
	(*(u32 *)&g_camAim0X) = 0xc28c0000;   /* -70.0 */
	(*(u32 *)&g_camAim0Y) = 0x420c0000;   /* 35.0 */
	g_camAim0Z = z;
	arena_loadPlayerSettings();
	g_arenaCameraMode = 1;
	g_lobbySubState = 0;
	g_arenaPanelBrightness = 0x3f333333;
	g_armcFrom = 0;
	g_lobbyPanelsOff = 0;
	g_arenaTunnelDepth = 0xc4ce4000;   /* -1650.0 */
}

/* 0x404b30: sub-screen 1, the arena list: its 24 state words cleared, 999 (no selection), 30 seconds */
void (lobby_enterArenaList)(void)
{
	static const u32 cleared[] = { (OBJ(g_camPoints) + 0x14), ADDR(g_serverConnected), ADDR(g_lobbyRefreshing), ADDR(g_arenaSearchStarted), ADDR(g_serverSearching), ADDR(g_lobbyJoinStarted), ADDR(g_lobbyJoinRequest), ADDR(g_lanSearch),
	                               ADDR(g_lobbySearching), ADDR(g_arenaHaveList), ADDR(g_arenaListFull), ADDR(g_gameCount), ADDR(g_lobbyBlinkClock), ADDR(g_pickedGame), ADDR(g_gameListTop), ADDR(g_lobbyListRow),
	                               ADDR(g_arenaListClickArmed), ADDR(g_arenaSearchClock), ADDR(g_lobbyPanelsOff), ADDR(g_arenaConfirming), ADDR(g_lobbyConnectionOpen), ADDR(g_arenaUpdateNotice), ADDR(g_arenaListRefreshTimer), ADDR(g_typingArenaAddress) };
	int z = g_menuCameraHeight;
	g_camPoint1X = 0x420c0000;   /* 35.0 */
	g_camPoint1Z = z;
	g_camAim1Z = z;
	g_camAim1X = 0xc28c0000;   /* -70.0 */
	g_camAim1Y = 0xc20c0000;   /* -35.0 */
	g_lobbySubState = 1;
	g_arenaCameraMode = 1;
	g_arenaPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_lastPanel = 999;
	g_lobbyPending = 1;
	g_arenaTunnelDepth = 0xc4ce4000;
	g_listRefreshPeriod = 30;
}

/* 0x404980: the arena settings record (g_playerName: title, map, options) loaded into the new arena's form (g_newArenaName). Maps 22 .. 24
   can't be chosen (back to 0); a title still the default one becomes "<player name><suffix>" */
void (lobby_loadArenaSettings)(void)
{
	signed char map = g_arenaMap;
	if (map >= 0x16 && map <= 0x18)
		g_arenaMap = map = 0;
	if (!strcmp(g_playerName, (const char *)STR(0x4ad4a4, "AXIS ARENA"))) {
		memset((void *)OBJ(g_playerName), 0, 32);
		strcpy(g_playerName, g_cfgPlayerName);
		strcat(g_playerName, (const char *)STR(0x4ad49c, " room"));
		map = g_arenaMap;
	}
	memset((void *)OBJ(g_newArenaName), 0, 32);
	strcpy(g_newArenaName, g_playerName);
	u8 b1 = g_arenaPlayers, b2 = g_arenaRotation, b3 = g_arenaGameType, b4 = g_arenaFragLimit,
	   b5 = g_arenaTimeLimit;
	g_newArenaMap = map;
	g_newArenaMode = b3;
	g_newArenaPlayers = b1;
	g_newArenaRotation = b2;
	g_newArenaPassword = 0;
	g_arenaFragLimitTyped = b4;
	g_arenaTimeLimitTyped = b5;
	g_newArenaPassword4 = 0;
}

/* 0x403420: the map on/off list (8-byte entries from g_mapChoiceKeptTable): the first time all off, then the first n maps
   (g_arenaMapCount) on; maps 22 .. 24 turned off (the last ones; the list's open flag cleared too) and the list laid out */
void (mapList_init)(void)
{
	if (!g_mapListMade) {
		for (MapChoice *p = g_mapChoiceKeptTable; p < g_mapChoiceKeptTable + 1024; p++) {
			p->chosen = 0;
			p->type = 0;
		}
		for (int k = 0; k < g_arenaMapCount; k++) {
			g_mapChoiceKeptTable[k].chosen = 1;
			g_mapChoiceKeptTable[k].type = 0;
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
void (lobby_enterCreate)(void)
{
	static const u32 cleared[] = { ADDR(g_arenaLobbyState), ADDR(g_connectionAwaited), ADDR(g_lobbyPending), ADDR(g_hostErrorBox), ADDR(g_arenaGameSetUp), ADDR(g_lobbyPanelsOff), ADDR(g_arenaUpdateNotice), ADDR(g_editingNewArenaName),
	                               ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword) };
	int z = g_menuCameraHeight;
	g_camPoint2X = 0xc20c0000;   /* -35.0 */
	g_camPoint2Y = 0;
	g_camPoint2Z = z;
	g_camAim2X = 0x428c0000;   /* 70.0 */
	g_camAim2Y = 0x420c0000;   /* 35.0 */
	g_camAim2Z = z;
	lobby_loadArenaSettings();
	g_lobbySubState = 2;
	g_arenaCameraMode = 1;
	g_arenaPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_arenaTunnelDepth = 0xc4ce4000;
	g_mapPreviewChanged = 1;
	mapList_init();
}

/* 0x433700: the room settings record (g_roomRecName: a name and six bytes) copied to the room's (g_roomSettingsName); map types
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
	g_roomRotation = g_roomRecRotation;
	g_roomFragLimit = g_roomRecFragLimit;
	g_roomTimeLimit = g_roomRecTimeLimit;
}

/* 0x433790: the create-game page (state 2) entered: the room's settings record, its state cleared, the map list */
void (room_enterCreatePage)(void)
{
	static const u32 cleared[] = { ADDR(g_arenaLobbyState), ADDR(g_connectionAwaited), ADDR(g_lobbyPending), ADDR(g_arenaGameSetUp), ADDR(g_arenaUpdateNotice), ADDR(g_editingRoomName), ADDR(g_editingFragLimit), ADDR(g_editingTimeLimit),
	                               ADDR(g_editingRoomPassword) };
	room_loadSettingsRecord();
	g_roomState = 2;
	g_roomCameraMode = 1;
	g_roomPanelBrightness = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_mapPreviewChanged = 1;
	(*(char *)&g_roomRotation) = 0;
	mapList_init();
}

/* 0x433800: the ranking page (state 4) entered: its ten 0x44-byte rows cleared (each marked empty), the paging and
   selection cleared, the distance limit 10,000,000, 999 rooms */
void (ranking_enter)(void)
{
	static const u32 cleared[] = { ADDR(g_rankingPage), ADDR(g_rankingRequestPending), ADDR(g_rankingListIn), ADDR(g_rankingWaiting), ADDR(g_rankingHaveList), ADDR(g_playerListDone), ADDR(g_playerListCount), ADDR(g_rankingPrevPage),
	                               ADDR(g_rankingSort), ADDR(g_rankingPrevSort), ADDR(g_rankingPrevRank) };
	for (RankRow *row = g_rankingRows; row < g_rankingRows + 10; row++) {
		memset(&row->rank, 0, offsetof(RankRow, level) - offsetof(RankRow, rank));
		row->level = 1;
	}
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_roomCameraMode = 1;
	g_rankingFirst = 1;
	g_roomState = 4;
	g_roomPanelBrightness = 0x3f333333;
	g_rankingLast = 10;
	g_roomListDistanceLimit = 0x4b189680;   /* 10000000.0 */
	g_roomListPages = 999;
}

/* 0x432620: the Ladder room's default game settings: the name "Axis Ladder Game", 8 players, mode 0, map 0, limits 10
   and 10, no map rotation, in both the room's form and its record (the Ladder ID copied); the mech unpacked */
void (room_setLadderDefaults)(void)
{
	strcpy(g_roomSettingsName, (const char *)STR(0x4b17bc, "Axis Ladder Game"));
	(*(char *)&g_roomPlayers) = 8;
	(*(char *)&g_roomGameMode) = 0;
	strcpy(g_ladderIdCopy, g_ladderId);
	(*(char *)&g_roomMap) = 0;
	(*(char *)&g_roomFragLimit) = 10;
	(*(char *)&g_roomTimeLimit) = 10;
	(*(char *)&g_roomRotation) = 0;
	strcpy(g_roomRecName, g_roomSettingsName);
	(*(char *)&g_roomRecPlayers) = 8;
	(*(char *)&g_roomRecGameMode) = 0;
	(*(char *)&g_roomRecMap) = 0;
	(*(char *)&g_roomRecFragLimit) = 10;
	(*(char *)&g_roomRecTimeLimit) = 10;
	(*(char *)&g_roomRecRotation) = 0;
	mech_unpackFromRecord();
}

/* 0x432be0: the joined game's settings (g_ladderId: its name, its host's, the room record g_roomRecName, the mech and the
   window rectangles) copied into the room screen's */
void (room_copyJoinedSettings)(void)
{
	strcpy(g_accountName, g_ladderId);
	strcpy(g_accountEmail, g_ladderEmail);
	u8 map = g_roomRecPlayers;
	strcpy(g_roomSettingsName, g_roomRecName);
	g_roomPlayers = map;
	g_roomMap = (*(u8 *)&g_roomRecMap);
	g_roomRotation = g_roomRecRotation;
	g_roomGameMode = g_roomRecGameMode;
	g_roomFragLimit = g_roomRecFragLimit;
	g_roomTimeLimit = g_roomRecTimeLimit;
	memcpy((void *)OBJ(g_roomMechKept), (void *)OBJ(g_roomMech), 11);
	memcpy((void *)OBJ(g_roomColoursKept), (void *)OBJ(g_roomColours), 0x90);
	static const u32 copy[6][2] = { { ADDR(g_pilotLevelKept), ADDR(g_pilotLevel) }, { ADDR(g_pilotExpKept), ADDR(g_pilotExp) }, { (OBJ(g_pilotStatsKept) + 0x1c), ADDR(g_pilotKillRate) },
	                                { ADDR(g_pilotKillsKept), ADDR(g_pilotKills) }, { ADDR(g_pilotDeathsKept), ADDR(g_pilotDeaths) }, { ADDR(g_pilotGamesKept), ADDR(g_pilotGames) } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, copy[k][0]) = GAME_VAR(int, copy[k][1]);
}

/* a PilotStats record's seven fields copied (all but rank, in the original's order) */
static void stats_copy(u32 dst, u32 src)
{
	PilotStats *d = (PilotStats *)RELOC(dst);
	const PilotStats *s = (const PilotStats *)RELOC(src);
	d->level = s->level;
	BITS(d->power) = BITS(s->power);
	BITS(d->killRate) = BITS(s->killRate);
	d->deaths = s->deaths;
	d->exp = s->exp;
	d->kills = s->kills;
	d->games = s->games;
}

/* 0x41e390 (the pilot's record): the two copies of the pilot's record (the server's,
   g_pilotLevel 0x9dd5d8, and the kept one, g_pilotLevelKept 0x9dd240: level, exp, ., power, ., kills, deaths) made
   the same when one's kills or exp are past the other's, then each limited by the Ladder record's (g_ladderLevel) */
void (pilotRecord_syncCopies)(void)
{
	int c5, a1, b1;   /* the values the original holds in registers where the branches meet */
	if (g_pilotKills > g_pilotKillsKept || g_pilotExp > g_pilotExpKept) {
		stats_copy(ADDR(g_pilotLevel), ADDR(g_pilotLevelKept));
		c5 = g_pilotKillsKept;
		a1 = b1 = g_pilotExpKept;
	} else {
		c5 = g_pilotKills;
		a1 = g_pilotExp;
		b1 = g_pilotExpKept;
		if (g_pilotKillsKept > c5 || b1 > a1) {
			stats_copy(ADDR(g_pilotLevelKept), ADDR(g_pilotLevel));
			b1 = a1;
		}
	}
	int e0 = g_ladderLevel, e1 = g_ladderExp, e3 = g_ladderPower,
	    e4 = g_ladderGames, e5 = g_ladderKills, e6 = g_ladderDeaths;
	if (c5 > e5 || a1 > e1) {
		g_pilotLevel = e0;
		g_pilotExp = e1;
		g_pilotPower = e3;
		g_pilotKills = e5;
		g_pilotDeaths = e6;
		g_pilotGames = e4;
	}
	if (g_pilotKillsKept > e5 || b1 > e1) {
		g_pilotExpKept = e1;
		g_pilotLevelKept = e0;
		g_pilotPowerKept = e3;
		g_pilotKillsKept = e5;
		g_pilotDeathsKept = e6;
		g_pilotGamesKept = e4;
	}
}

/* 0x432db0: the login accepted (answer 0x21): the account record the server sent (g_netRecvRecord) taken: the ID and
   e-mail, the 11 mech bytes, the six colour pairs (a negative or NaN saturation or value becomes 0), the pilot's
   stats; then the room's settings, the Ladder record (g_ladderName ..) and the mech */
void (login_takeAccountRecord)(void)
{
	strcpy(g_ladderId, (const char *)(OBJ(g_netRecvRecord) + 0x4));
	strcpy(g_ladderEmail, (const char *)(OBJ(g_netRecvRecord) + 0x22));
	memcpy((void *)OBJ(g_roomMech), (void *)(OBJ(g_netRecvRecord) + 0x54), 11);
	for (int k = 0; k < 6; k++) {
		memcpy((void *)(OBJ(g_roomColours) + k * 0x18), (void *)((OBJ(g_netRecvRecord) + 0x5f) + k * 0x18), 0x18);
		if (!(GAME_VAR(float, OBJ(g_roomColours) + 0x4 + k * 0x18) >= k_0f))
			GAME_VAR(int, OBJ(g_roomColours) + 0x4 + k * 0x18) = 0;
		if (!(GAME_VAR(float, OBJ(g_roomColours) + 0x8 + k * 0x18) >= k_0f))
			GAME_VAR(int, OBJ(g_roomColours) + 0x8 + k * 0x18) = 0;
	}
	static const u32 rect[7][2] = { { ADDR(g_pilotLevel), (OBJ(g_netRecvRecord) + 0xef) }, { ADDR(g_pilotExp), (OBJ(g_netRecvRecord) + 0xff) }, { ADDR(g_pilotPower), (OBJ(g_netRecvRecord) + 0x103) },
	                                { ADDR(g_pilotKillRate), (OBJ(g_netRecvRecord) + 0x107) }, { ADDR(g_pilotKills), (OBJ(g_netRecvRecord) + 0xf7) }, { ADDR(g_pilotDeaths), (OBJ(g_netRecvRecord) + 0xfb) },
	                                { ADDR(g_pilotGames), (OBJ(g_netRecvRecord) + 0xf3) } };
	for (int k = 0; k < 7; k++)
		GAME_VAR(int, rect[k][0]) = GAME_VAR(int, rect[k][1]);
	room_copyJoinedSettings();
	memset((void *)OBJ(g_ladderName), 0, 7 * 4 + 2);
	strcpy(g_ladderName, g_ladderId);
	static const u32 title[6][2] = { { ADDR(g_ladderLevel), ADDR(g_pilotLevel) }, { ADDR(g_ladderExp), ADDR(g_pilotExp) }, { ADDR(g_ladderKills), ADDR(g_pilotKills) },
	                                 { ADDR(g_ladderDeaths), ADDR(g_pilotDeaths) }, { ADDR(g_ladderGames), ADDR(g_pilotGames) }, { ADDR(g_ladderPower), ADDR(g_pilotPower) } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, title[k][0]) = GAME_VAR(int, title[k][1]);
	mech_unpackFromRecord();
	g_bestLevelNet = g_pilotLevel;
	g_roomConnected = 1;
}

/* the default mech settings (11 bytes) and six colour pairs (hue 0, saturation 1, value 0.6) at mech, colours */
static void default_mech(u8 *mech, u8 *colours)
{
	static const u8 bytes[11] = { 0, 0, 0, 0, 0, 0xff, 0x11, 0, 2, 8, 0xff };
	static const u32 pair[6] = { 0, 0x3f800000, 0x3f19999a, 0, 0x3f800000, 0x3f19999a };
	memcpy(mech, bytes, sizeof bytes);
	for (int k = 0; k < 6; k++)
		memcpy(colours + k * 0x18, pair, sizeof pair);
}

/* 0x434820: the new ID registered (its confirmation's OK): the form's ID and e-mail kept as the Ladder login's, the
   default mech and colours in both copies, the pilot's stats reset (level 1) and the Ladder record (g_ladderName ..)
   set from them; the account record (g_accountPacket: kind 0x18, the ID, password and e-mail, the defaults) sent to the
   server (net_send 0xf, 0x65). Returns net_send's
   eax */
u32 (newId_register)(void)
{
	strcpy(g_ladderId, g_accountName);
	strcpy(g_ladderEmail, g_accountEmail);
	default_mech(g_roomMechKept, g_roomColoursKept);
	default_mech(g_roomMech, (u8 *)OBJ(g_roomColours));
	g_pilotLevelKept = 1;
	g_pilotLevel = 1;
	memset((void *)OBJ(g_ladderName), 0, 7 * 4 + 2);
	static const u32 zero[] = { ADDR(g_pilotExp), ADDR(g_pilotKills), ADDR(g_pilotDeaths), ADDR(g_pilotGames), ADDR(g_pilotKillRate), ADDR(g_pilotExpKept), ADDR(g_pilotKillsKept), ADDR(g_pilotDeathsKept),
	                            ADDR(g_pilotGamesKept), (OBJ(g_pilotStatsKept) + 0x1c) };
	for (unsigned k = 0; k < sizeof zero / sizeof zero[0]; k++)
		GAME_VAR(int, zero[k]) = 0;
	strcpy(g_ladderName, g_ladderId);
	g_ladderPower = g_pilotPower;
	g_ladderLevel = 1;
	static const u32 zero2[] = { ADDR(g_ladderExp), ADDR(g_ladderKills), ADDR(g_ladderDeaths), ADDR(g_ladderGames) };
	for (int k = 0; k < 4; k++)
		GAME_VAR(int, zero2[k]) = 0;
	AccountPacket *record = (*(AccountPacket **)&g_accountPacket);
	strcpy(record->name, g_accountName);
	strcpy(record->password, g_accountPassword);
	strcpy(record->email, g_accountEmail);
	default_mech(record->mech, (u8 *)record->colours[0]);
	g_bestLevelNet = g_pilotLevel;
	*(int *)record = 0x18;
	u32 r = net_send(0xf, 0x65);
	g_roomAnswerAwaited = 1;
	return r;
}

/* 0x4080c0: the lobby's back keys (unless a dialog is open): the first closes the list (g_arenaUpdateNotice), the second leaves
   the game (quit code 2). Returns what the original leaves in eax */
u32 (lobby_keysBack)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	u32 r = input_justPressed(g_dikC);
	if (r) {
		g_arenaUpdateNotice = 0;
		return r;
	}
	r = input_justPressed(g_dikO);
	if (!r)
		return 0;
	g_arenaUpdateNotice = 0;
	return app_closeWindow(2);
}

/* 0x40cf80: the lobby's player screen: the arena tunnel, then in modes other than 0 and 1 (g_arenaCameraMode) and not on
   sub-screen 5, the player panel (lobby_drawPlayerSetup), or with a dialog open just its frame. Returns what the original
   leaves in eax */
u32 (lobbyPlayer_draw)(void)
{
	arena_drawTunnel();   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaCameraMode;
	if (mode == 1 || mode == 0 || g_lobbySubState == 5)
		return mode;
	if (!g_dialogOpen)
		return lobby_drawPlayerSetup();   /* lobby_drawPlayerSetup */
	return menu_drawFrame(g_playerSetupLeft, g_playerSetupTop,
	                                                     g_playerSetupRight, g_playerSetupBottom);   /* menu_drawFrame */
}

/* 0x4081f0: the lobby's keys, by sub-screen (g_lobbySubState): 0 the player's record, 1 the arena list (or its chat line
   while open), 2 creating an arena (the back keys while the list is open, the map list, the quit dialog, else the
   connect), 5 the top; 3 and 4 have none. Returns what the handler leaves in eax (else the sub-screen) */
u32 (lobby_processKeys)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 0:
		return lobbyPlayer_keys();   /* lobbyPlayer_keys */
	case 1:
		if (g_arenaUpdateNotice)
			return arenaUpdateNotice_keys();   /* arenaUpdateNotice_keys */
		return arenaGames_keys();       /* arenaGames_keys */
	case 2:
		if (g_arenaUpdateNotice)
			return lobby_keysBack();   /* lobby_keysBack */
		if (g_mapListOpen)
			return mapList_keys();   /* the map list */
		if (g_hostErrorBox)
			return hostError_keys();   /* hostError_keys */
		return arena_createAfterTyping();       /* arena_createAfterTyping */
	case 5:
		return lobbyTop_keys();       /* lobbyTop_keys */
	}
	return screen;
}

/* 0x406bd0: the lobby's update notice clicks (unless another dialog is open): a right click closes it; OK (its first
   button) closes the game (code 2), CANCEL the notice. Returns what the original leaves in eax */
u32 (arenaUpdateNotice_clicks)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (g_rightClick)
		g_arenaUpdateNotice = 0;
	if (!g_mouseClick)
		return 0;
	int button = arenaCreate_hitTest(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button == 0) {
		g_arenaUpdateNotice = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		g_arenaUpdateNotice = 0;
		return 0;
	}
	return (u32)(button - 1);
}

/* ---- the lobby's per-frame dispatch by sub-screen (g_lobbySubState): drawing and clicks. Each returns what the handler it
   ends in leaves in eax (or the sub-screen when there is none) ---- */

/* 0x40d450: the lobby drawn: the top (5: its title, or the dim overlay while connecting to a ladder game), else the
   background, the camera and the sub-screen (0 the player, 1 the arena list, 2 creating an arena) */
u32 (menuState400_frame)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 5:
		lobbyTop_draw();   /* lobbyTop_draw */
		menu_drawBackground();
		if (g_quitAsked == 1 && g_arenaCameraMode == 2)
			return menu_drawDimOverlay();   /* menu_drawDimOverlay */
		return lobbyTop_drawMenu();       /* lobbyTop_drawMenu */
	case 0:
		menu_drawBackground();
		arena_camera();              /* arena_camera: the lobby's camera */
		return lobbyPlayer_draw();       /* lobbyPlayer_draw */
	case 1:
		menu_drawBackground();
		arena_camera();
		return arena_drawGamesPage();       /* arena_drawGamesPage */
	case 2:
		menu_drawBackground();
		arena_camera();
		return lobbyCreate_draw();       /* lobbyCreate_draw */
	}
	return screen;
}

/* 0x4076c0: the lobby's clicks: the top (lobby_topPageClicks), the player (lobby_playerScreenClicks), the arena list (its close button
   while closing, the quit dialog while open, else connecting), creating an arena (the list's dialog, the map list,
   else the quit dialog if open, then the screen's clicks) */
u32 (lobby_clicks)(void)
{
	u32 screen = (*(u32 *)&g_lobbySubState);
	switch (screen) {
	case 5:
		return lobby_topPageClicks();
	case 0:
		return lobby_playerScreenClicks();
	case 1:
		if (g_arenaConfirming)
			return lobby_close();   /* lobby_close */
		if (g_arenaUpdateNotice)
			return arenaUpdateNotice_clicks();   /* arenaUpdateNotice_clicks */
		return arenaGames_mouse();       /* arenaGames_mouse */
	case 2:
		if (g_arenaUpdateNotice)
			return createUpdateNotice_clicks();   /* createUpdateNotice_clicks */
		if (g_mapListOpen)
			return mapList_mouse();   /* mapList_mouse: the map list */
		if (g_hostErrorBox)
			hostError_clicks();          /* hostError_clicks */
		return arena_createClick();       /* arena_createClick */
	}
	return screen;
}

/* 0x406b60: a click on the arena list's close button (mode 2, no dialog open): the list closed, the session search
   stopped (arena_leaveSession) and its timer (0x378) killed. Returns what the original leaves in eax */
u32 (lobby_close)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (!g_mouseClick || g_arenaCameraMode != 2)
		return g_mouseClick;
	(*(int *)&g_cursorBlink) = 0;
	u32 hit = ((u32)arenaDialogBox_hitTest(g_mouseX, g_mouseY));   /* the close button's hit test */
	if (hit)
		return hit;
	g_arenaSearchTicks = 0;
	g_arenaJoinWaiting = 0;
	arena_leaveSession();   /* arena_leaveSession */
	g_arenaConfirming = 0;
	return ((u32)KillTimer(g_hWndMain, 0x378));   /* KillTimer */
}

/* 0x403870: the map list's keys: the first key toggles the map (mapList_ok) - or, read a second time, closes the
   list with a sound -, the others move the cursor up and down */
u32 (mapList_keys)(void)
{
	if (input_justPressed(g_dikO))
		return mapList_ok();   /* mapList_ok */
	if (input_justPressed(g_dikO)) {
		u32 r = sound_playMenu(0);   /* sound_playMenu */
		g_mapListOpen = 0;
		return r;
	}
	if (input_justPressed(g_dikA))
		return mapList_chooseAll();   /* mapList_chooseAll */
	u32 r = input_justPressed(g_dikD);
	if (r)
		return mapList_chooseNone();   /* mapList_chooseNone */
	return r;
}

/* 0x435a40: leaving the game room: the Ladder ID sent to the game server (packet 0x19: logging out), a pause of half a
   second, back to the main menu (state 300), the connection closed, the mech reloaded from the profile */
u32 (room_leaveGame)(void)
{
	strcpy(g_netLeaveBuffer, g_ladderId);
	net_send(0x19, 0x65);   /* net_send */
	Sleep(500);                   /* Sleep */
	menuCamera_setMove(4);
	g_nextScreen = 300;
	GAME_FN(debug_traceStripped, 0x48b420, void, void)();                 /* debug_traceStripped */
	net_disconnect();                 /* net_disconnect */
	g_roomConnected = 0;
	return mech_loadFromProfile();
}

/* 0x407270: the create screen's update notice clicks, only with none of its other panels (and no dialog) open: as
   arenaUpdateNotice_clicks. Returns what the original leaves in eax */
u32 (createUpdateNotice_clicks)(void)
{
	static const u32 panels[5] = { ADDR(g_editingNewArenaName), ADDR(g_editingNewArenaFragLimit), ADDR(g_editingNewArenaTimeLimit), ADDR(g_typingArenaPassword), ADDR(g_dialogOpen) };
	for (int k = 0; k < 5; k++)
		if (GAME_VAR(int, panels[k]))
			return GAME_VAR(u32, panels[k]);
	if (g_rightClick)
		g_arenaUpdateNotice = 0;
	if (!g_mouseClick)
		return 0;
	int button = arenaCreate_hitTest(g_mouseX, g_mouseY);
	if (button == 0) {
		g_arenaUpdateNotice = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		g_arenaUpdateNotice = 0;
		return 0;
	}
	return (u32)(button - 1);
}

/* 0x405230: the IP address field opened (a game joined by its address, arena_joinListed(99999)): the keyboard released for typing, the input line emptied (20
   characters at most), placed at the panel's origin + (0xd8, 0xd0), the fade timer 5, the Windows edit control made.
   Returns what that leaves in eax */
u32 (arena_editAddress)(void)
{
	input_releaseKeyboard();
	g_textFieldOpen = 1;
	menu_clearInputBuffer(0x14);
	memset((void *)OBJ(g_chatLine), 0, 0x400);
	(*(int *)&g_typedArenaAddress) = 0;
	g_chatCaretX = g_arenaGameListLeft + 0xd8;
	g_chatCaretY = g_arenaGameListTop + 0xd0;
	g_chatLength = (int)strlen(g_chatLine);
	g_typedArenaAddress4 = 0;
	(*(u32 *)&g_menuKeyGuard) = 0x40a00000;   /* 5 */
	/* chat_createEdit(20); the original also leaves the 20 it gave menu_clearInputBuffer on the stack as a second
	   argument */
	u32 r = GAME_FN(chat_createEdit, 0x43f460, u32, int, int)(0x14, 0x14);
	g_typingArenaAddress = 1;
	return r;
}

/* a settings record (GameSettings: the name, the six choices, the password) stored into another: the locked flag
   (the password is not empty) set in both. Then the store's follow-up; returns what it leaves in eax */
/* (the copies are plain loops, as the original's inline string instructions: no calls before the follow-up, whose
   stack the original leaves untouched) */
static void copy_string(u8 *to, const u8 *from)
{
	do
		*to++ = *from;
	while (*from++);
}
static u32 settings_store(GameSettings *from, GameSettings *to, u32 then)
{
	u8 locked = from->password[0] != 0;
	from->locked = locked;
	copy_string((u8 *)to->name, (const u8 *)from->name);
	to->maxPlayers = from->maxPlayers;
	to->map = from->map;
	to->mode = from->mode;
	to->rotation = from->rotation;
	to->limit[1] = from->limit[1];
	to->limit[0] = from->limit[0];
	copy_string((u8 *)to->password, (const u8 *)from->password);
	to->locked = locked;
	return GAME_CDECL(then, u32, void)();
}
/* 0x405140: the arena being created kept as the arena settings (g_playerName), then axis.cfg loaded again */
u32 (lobby_keepArenaSettings)(void) { return settings_store((GameSettings *)OBJ(g_newArenaName), (GameSettings *)OBJ(g_playerName), FN_ADDR(cfg_writeAxisCfg, 0x42d730)); }
/* 0x433640: the room's settings kept (g_roomRecName) and written to the registry (reg_writeLadderSettings) */
u32 (room_keepSettings)(void) { return settings_store((GameSettings *)OBJ(g_roomSettingsName), (GameSettings *)OBJ(g_roomRecName), FN_ADDR(reg_writeLadderSettings, 0x432400)); }

/* 0x40d390: the create-arena screen drawn: the tunnel, then (modes other than 0 and 1, not on sub-screen 5) the
   dialog's frame if one is open, else the settings kept in range (players 0 .. 16 else 8, the two limits at most 250
   else 30, the map 0 .. 14 else 0), the screen, the map list when open, the options panel when shown. Returns what
   the original leaves in eax */
u32 (lobbyCreate_draw)(void)
{
	arena_drawTunnel();   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaCameraMode;
	if (mode == 1 || mode == 0 || g_lobbySubState == 5)
		return (u32)mode;
	if (g_dialogOpen)
		return menu_drawFrame(g_newArenaFormLeft, g_newArenaFormTop,
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
	arena_createDraw();   /* arena_createDraw */
	if (g_mapListOpen == 1)
		mapList_draw();   /* mapList_draw: the map list */
	if (!g_connectionAwaited)
		return 0;
	return arena_connectionOutcome();   /* arena_connectionOutcome */
}

/* 0x408110: the "NETWORK INITIALIZE ERROR" box's keys (hosting failed; no other dialog open): C closes it, O starts the arena anyway:
   multiplayer on, the music stopped, the arena settings (g_playerName) as the game's (map, players, limits), the lobby
   left. Returns what the original leaves in eax */
u32 (hostError_keys)(void)
{
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	u32 r = input_justPressed(g_dikC);
	if (r) {
		g_hostErrorBox = 0;
		return r;
	}
	if (!input_justPressed(g_dikO))
		return 0;
	g_quitAsked = 1;
	g_netRole = 1;
	music_shutdown();   /* music_shutdown */
	u32 limits = (*(u32 *)&g_arenaFragLimit);
	g_mapRotation = (*(signed char *)&g_arenaRotation);
	g_mapIndex = g_arenaMap;
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_chosenGameMode = (*(signed char *)&g_arenaGameType);
	(*(u32 *)&g_fragLimit) = limits & 0xff;
	(*(u32 *)&g_timeLimit) = (limits >> 8) & 0xff;
	g_arenaCameraMode = 0;
	g_arenaLobbyState = 1;
	g_hostErrorBox = 0;
	return limits;
}

/* 0x406a60: the lobby player screen's clicks (mode 2, no dialog or list open): a right click goes back; buttons: 0 the
   name field, 2 the ARM CENTER, 3 the profile's record kept, 4 back, 5 the default name. Returns what the original
   leaves in eax */
u32 (lobby_playerScreenClicks)(void)
{
	int mode = g_arenaCameraMode;
	if (mode == 1 || mode == 0 || g_dialogOpen || g_typingArenaName)
		return (u32)mode;
	if (g_rightClick) {
		g_arenaCameraMode = 0;
		return sound_playMenu(0);
	}
	if (!g_mouseClick || mode != 2)
		return (u32)mode;
	u32 button = ((u32)playerSetup_hitTest(g_mouseX, g_mouseY));   /* the screen's hit test */
	u32 r;
	switch (button) {
	case 0:
		return arena_editName();   /* arena_editName */
	case 2:
		sound_playMenu(0);
		g_armcFrom = 2;
		return armc_enterParts();   /* armc_enterParts: the ARM CENTER */
	case 3:
		sound_playMenu(0);
		r = arena_savePlayerSettings();      /* arena_savePlayerSettings */
		g_arenaCameraMode = 0;
		return r;
	case 4:
		r = sound_playMenu(0);
		g_arenaCameraMode = 0;
		return r;
	case 5:
		sound_playMenu(0);
		return arena_defaultPlayer();   /* arena_defaultPlayer */
	}
	return button;
}

/* a joined session's settings taken from its list entry: the music stopped, its name as the map title, the map,
   rotation, game mode, frag and time limits; the lobby left (g_arenaCameraMode 0) for the game (g_quitAsked 1, g_netRole 2) */
static void take_session(const SessionEntry *rec)
{
	music_shutdown();
	g_mapIndex = rec->map;
	memcpy((void *)OBJ(g_mapTitle), rec->name, 32);
	g_mapRotation = rec->rotation;
	g_arenaCameraMode = 0;
	g_quitAsked = 1;
	g_netRole = 2;
	g_chosenGameMode = rec->gameMode;
	g_fragLimit = rec->fragLimit;
	g_timeLimit = rec->timeLimit;
}

/* 0x405690: arena session `session` joined: its list entry gives the frag and time limits shown and the join's
   argument (its guid); a refused join shows message 0x36 (full) or 0x35. Joined, the music stops and the session's
   settings are taken (take_session). Returns the message's eax, or the time limit */
u32 (arena_joinSession)(int session)
{
	const SessionEntry *rec = &g_sessionList[session];
	g_lobbyJoinStarted = 0;
	g_lobbyJoinRequest = 0;
	g_arenaTimeLimit = g_arenaTimeLimitTyped = rec->timeLimit;
	g_arenaFragLimit = g_arenaFragLimitTyped = rec->fragLimit;
	int r = dplay_join(session, rec->guid, g_cfgPlayerName,
	                                                               g_playerCorporation);   /* dplay_join: join */
	if (r != 0x1f4)
		return menu_showMessage(r == 0x1f5 ? 0x36 : 0x35);   /* the message */
	take_session(rec);
	g_arenaConfirming = 0;
	return rec->timeLimit;
}

/* 0x4062b0 (the arena join's answer, from WndProc): with the join dialog up (g_arenaJoinWaiting)
   message 0x44 and the connection closed; else a pending join (g_arenaJoinPending) of the game picked (g_arenaJoinRow: 99999 for
   the one received at g_receivedSession, copied into a session record at g_joinedSessionRec, otherwise its row of the list, which
   takes the received id) is answered (dplay_join): joined, the session's settings are taken and the lobby
   connection closed; refused, messages 0x43 (501), 0x42 (502, 503), 0x44 (504), 0x45 (505) and the connection
   closed. The caller ignores the eax it leaves */
void (arena_joinAnswer)(void)
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
	SessionEntry *rec;
	if (pick == 99999) {
		g_arenaJoinRow = 0;
		if (!g_arenaJoinPending)
			return;
		const SessionDesc *in = (const SessionDesc *)g_receivedSession;
		rec = g_joinedSessionRec;
		rec->guid = in->guid;
		rec->fragLimit = in->fragLimit;
		rec->timeLimit = in->timeLimit;
		rec->gameMode = in->gameMode;
		rec->map = in->map;
		rec->rotation = in->rotation;
		strcpy(rec->name, in->name);
	} else {
		if (!g_arenaJoinPending)
			return;
		rec = &g_sessionList[pick];
		rec->guid = ((const SessionDesc *)g_receivedSession)->guid;
		g_arenaFragLimit = rec->fragLimit;
		g_arenaTimeLimit = rec->timeLimit;
	}
	int r = dplay_join(0, rec->guid, g_cfgPlayerName, g_playerCorporation);
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
/* back to the main menu; returns menuCamera_setMove's eax (4) */
static u32 to_main_menu(void)
{
	u32 r = menuCamera_setMove(4);   /* menuCamera_setMove: keys blocked */
	g_nextScreen = 300;
	GAME_FN(debug_traceStripped, 0x48b420, void, void)();          /* debug_traceStripped */
	return r;
}

/* 0x407750: the lobby's top page keys (no dialog open, not while g_quitAsked is 1): back (when a tunnel ring is behind: g_tunnelRings > 0) or
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
		return lobby_enterCreate();   /* lobby_enterCreate */
	if (key_hit(ADDR(g_dikP)))
		return lobby_enterPlayerScreen();   /* lobby_enterPlayerScreen */
	if (key_hit(ADDR(g_dikJ)))
		return lobby_enterArenaList();   /* lobby_enterArenaList */
	if (key_hit(ADDR(g_dikX)))
		return to_main_menu();
	return 0;
}

/* 0x406950: the lobby's top page clicks (no dialog open, not while g_quitAsked is 1): a left click on one of its four
   buttons (outlines at g_lobbyTopOutlines) picks sub-page 0, 1 or 2 or goes back to the main menu; a right click (when a tunnel ring
   is behind: g_tunnelRings > 0) goes back too. Returns what the original leaves in eax */
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
			case 0: lobby_enterPlayerScreen(); break;   /* lobby_enterPlayerScreen */
			case 1: lobby_enterArenaList(); break;   /* lobby_enterArenaList */
			case 2: lobby_enterCreate(); break;   /* lobby_enterCreate */
			case 3: to_main_menu(); break;
			}
			break;
		}
	}
	int right = g_rightClick;
	if (!right)
		return 0;
	int allowed = g_tunnelRings;
	if (allowed <= 0)
		return allowed;
	sound_playMenu(0);
	return to_main_menu();
}

/* 0x407840: the lobby's player page keys (page open, g_arenaCameraMode not 0 or 1; no dialog): while the name is being typed
   (g_typingArenaName), the typed line (g_chatLine) becomes the player's name (g_arenaPlayerName, 32 bytes) once the keyboard is back
   (g_textFieldOpen clear) and typing ends; otherwise back closes the page, g_dikO applies (arena_savePlayerSettings) and closes it,
   g_dikD resets the name to the default, g_dikC closes it. Returns what the original leaves in eax */
u32 (lobbyPlayer_keys)(void)
{
	u32 page = (*(u32 *)&g_arenaCameraMode);
	if (page == 1 || page == 0 || g_dialogOpen)
		return page;
	if (g_typingArenaName) {
		if (g_textFieldOpen)
			return page;
		const char *typed = g_chatLine;
		u32 length = strlen(typed);
		g_typingArenaName = 0;
		if (!length)
			return 0;
		memset((void *)OBJ(g_arenaPlayerName), 0, 32);
		strcpy(g_arenaPlayerName, typed);
		return length + 1;
	}
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_arenaCameraMode = 0;
	}
	if (input_justPressed(g_dikO)) {
		sound_playMenu(0);
		arena_savePlayerSettings();
		g_arenaCameraMode = 0;
	}
	if (input_justPressed(g_dikD)) {
		sound_playMenu(0);
		return arena_defaultPlayer();   /* arena_defaultPlayer */
	}
	if (!input_justPressed(g_keyBack))
		return 0;
	u32 r = sound_playMenu(0);      /* sound_playMenu */
	g_arenaCameraMode = 0;
	return r;
}

/* 0x4060f0: the lobby server connection opened (unless open, g_lobbyConnectionOpen): the old one closed, net_connect(100) (0: no
   server, message 0x3d; 2: message 0x46) and the socket's messages sent to the main window (failing: 0x3e). Then
   the lobby screen's state reset and the hello sent (0x180001, net_send(0xd, 100)). 1, or 0 on a failure */
int (lobby_openConnection)(void)
{
	if (!g_lobbyConnectionOpen) {
		net_disconnect();                   /* net_disconnect */
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
	g_pickedGame = 0;
	(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000.0f */
	g_gameListTop = 0;
	g_lobbyListRow = 0;
	*g_netLobbyMessage = 0x180001;   /* the message to send */
	net_send(0xd, 100);   /* net_send */
	g_arenaConfirming = 0;
	g_listRefreshPeriod = 30;
	return 1;
}

/* 0x40d840: a launcher-started arena game. As its host (g_startedByLauncher 1): the arena's settings from axiswl.dat
   (arena_loadSettings; none: quit) as the arena record (the name g_arenaGameName into g_playerName, the optional password
   g_arenaFilePassword, the limits, game type, map and players), then the lobby's arena list and the arena hosted
   (lobby_hostArena; reply 0x68). Otherwise the lobby's arena list and the server address given (g_serverAddressArg,
   into g_typedArenaAddress) joined (arena_joinListed(99999); reply 0x69).
   Returns the last call's eax */
u32 (arena_startFromLauncher)(void)
{
	if (g_startedByLauncher != 1) {
		menuState400_enter();   /* menuState400_enter */
		lobby_enterArenaList();   /* lobby_enterArenaList */
		memset((void *)ADDR(g_typedArenaAddress), 0, 24);
		strcpy((char *)ADDR(g_typedArenaAddress), g_serverAddressArg);
		u32 r = arena_joinListed(99999);   /* arena_joinListed */
		g_lobbyReply = 0x69;
		return r;
	}
	if (!arena_loadSettings((const char *)STR(0x4ad5e4, "axiswl.dat")))
		return PostQuitMessage(0);                               /* PostQuitMessage */
	memset((void *)OBJ(g_playerName), 0, 32);
	strcpy(g_playerName, g_arenaGameName);
	u8 secret = (*(u8 *)&g_arenaFileSecret);   /* (1: a password game) */
	g_arenaPassword = 0;
	g_arenaLocked = secret;
	g_arenaPassword4 = 0;
	if (secret == 1)
		strcpy((char *)ADDR(g_arenaPassword), (const char *)ADDR(g_arenaFilePassword));
	g_arenaFragLimit = g_arenaFileFragLimit;
	g_arenaGameType = g_arenaFileGameType;
	g_arenaRotation = 0;
	(*(u8 *)&g_arenaMap) = g_arenaFileMap;
	g_arenaPlayers = g_arenaFilePlayers;
	g_arenaTimeLimit = (*(u8 *)&g_cmdTimeLimit);
	menuState400_enter();
	lobby_enterArenaList();
	u32 r = lobby_hostArena();   /* lobby_hostArena */
	g_lobbyReply = 0x68;
	return r;
}

/* 0x407300: the "NETWORK INITIALIZE ERROR" box's clicks (nothing else open: g_editingNewArenaName, g_editingNewArenaFragLimit, g_editingNewArenaTimeLimit, g_typingArenaPassword, no
   dialog): a right click or button 0x11 closes it (g_hostErrorBox); button 0x10 starts the game anyway with the player's settings (the
   32-byte record g_playerName and its colour / corporation bytes), the music stopped. Returns what the original
   leaves in eax */
u32 (hostError_clicks)(void)
{
	u32 busy = (*(u32 *)&g_editingNewArenaName);
	if (busy || g_editingNewArenaFragLimit || g_editingNewArenaTimeLimit || g_typingArenaPassword || g_dialogOpen)
		return busy;
	if (g_rightClick) {
		g_hostErrorBox = 0;
		return 0;
	}
	if (!g_mouseClick)
		return 0;
	int button = createArena_hitTest(g_mouseX, g_mouseY);
	if (button == 0x11) {
		g_hostErrorBox = 0;
		return 0;
	}
	if (button != 0x10)
		return button - 0x11;
	g_quitAsked = 1;
	g_netRole = 1;
	music_shutdown();
	g_mapRotation = (signed char)g_arenaRotation;
	g_mapIndex = (signed char)(*(u8 *)&g_arenaMap);
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_chosenGameMode = (signed char)g_arenaGameType;
	g_fragLimit = g_arenaFragLimit;
	g_timeLimit = g_arenaTimeLimit;
	g_arenaCameraMode = 0;
	g_arenaLobbyState = 1;
	g_hostErrorBox = 0;
	return (*(u32 *)&g_arenaFragLimit);
}

/* 0x405b80: the arena connection's outcome (g_connectStep; 2 nothing to do). 1 connected: the music stopped, the player
   slot opened (arena_openSession), the arena hosted with the player's record (g_playerName: name, g_cfgPlayerName, colours,
   corporation; g_playerCorporation) and its settings taken for the game, g_arenaGameSetUp set; then (as the state stands after) 0
   closed, 3 closed for a ladder game (g_arenaUpdateNotice), 4 refused (message 0x46): the connection closed (net_disconnect) and
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
		g_arenaCameraMode = 0;
		GAME_FN(arena_openSession, 0x452ec0, void, int, int)(0, 0);   /* arena_openSession */
		dplay_host(me, (const void *)OBJ(g_cfgPlayerName),
			(int)(signed char)me[0x22] << 8 | (int)(signed char)me[0x20], (signed char)me[0x21], (signed char)me[0x23],
			me[0x24], me[0x25], (*(u32 *)&g_playerCorporation));   /* dplay_host: host */
		g_mapIndex = (signed char)me[0x20];
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
	u32 r = net_disconnect();   /* net_disconnect: the connection closed */
	g_connectStep = 2;
	if (state == 3)
		g_arenaUpdateNotice = 1;
	g_connectionAwaited = 0;
	g_arenaGameSetUp = 0;
	if (state == 4)
		r = menu_showMessage(0x46);   /* the message */
	return r;
}

/* 0x407e40: the "create arena" page after typing (not while typing or with a message box): a typed field is taken
   (the arena's name into g_newArenaName unless blank (sound 6); the password into g_newArenaPassword; the two limits as numbers,
   0 .. 250 (else 250), into the bytes g_arenaFragLimitTyped / g_arenaTimeLimitTyped; an empty line changes nothing), else the keys: create
   (g_dikI; lobby_hostArenaLan) and join (g_dikT; lobby_announceArena) unless connecting, and the two close
   keys (the arena left). Returns what the original leaves in eax */
u32 (arena_createAfterTyping)(void)
{
	u32 mode = (*(u32 *)&g_arenaCameraMode);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	const char *line = g_chatLine;
	if (g_editingNewArenaName) {   /* the arena's name */
		if (g_textFieldOpen)
			return mode;
		if (!strlen(line) || name_isBlank(line) == 1) {   /* name_isBlank: blank */
			u32 r = strlen(line) ? sound_playMenu(6) : 0;
			g_editingNewArenaName = 0;
			return r;
		}
		g_editingNewArenaName = 0;
		memset((void *)OBJ(g_newArenaName), 0, 32);
		strcpy(g_newArenaName, line);
		return strlen(line) + 1;
	}
	if (g_typingArenaPassword) {   /* the password */
		if (g_textFieldOpen)
			return mode;
		memset((void *)ADDR(g_newArenaPassword), 0, 8);
		g_typingArenaPassword = 0;
		g_inputLineHidden = 0;
		strcpy((char *)ADDR(g_newArenaPassword), line);
		return 0;
	}
	static const u32 limit[2][2] = { { ADDR(g_editingNewArenaFragLimit), ADDR(g_arenaFragLimitTyped) }, { ADDR(g_editingNewArenaTimeLimit), ADDR(g_arenaTimeLimitTyped) } };
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(int, limit[k][0]))
			continue;
		if (g_textFieldOpen)
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
		return lobby_hostArenaLan();   /* lobby_hostArenaLan: create */
	}
	if (input_justPressed(g_dikT) && !g_arenaGameSetUp) {
		sound_playMenu(0);
		u32 r = lobby_announceArena();
		return r ? r : lobby_hostArena();   /* lobby_hostArena */
	}
	u32 r = 0;
	static const u32 close[2] = { ADDR(g_dikC), ADDR(g_dikEscape_2) };
	for (int k = 0; k < 2; k++) {
		r = (u32)input_justPressed(GAME_VAR(int, close[k]));
		if (r) {
			arena_leaveSession();   /* arena_leaveSession: the arena left */
			g_arenaCameraMode = 0;
			r = sound_playMenu(0);
		}
	}
	return r;
}

/* 0x407410: the "create arena" page clicked (no field being typed, page state 2, no message box; a right click leaves
   the arena). Buttons (createArena_hitTest): 0 / 1 / 6 / 7 type a field (arena_editComment, arena_editPassword, arena_editFragLimit, arena_editTimeLimit), 2 / 12 /
   14 the map on and 13 back (arena_stepMap), 3 the players +2 (to 16, then 2), 4 the map rotation on / off (g_newArenaRotation; the game
   type kept in range), 5 the game type on (with a turn key held back) through 0 .. 13 (0 .. 14 with the rotation on), 8
   create and 9 join (unless connecting), 11 leave, 15 the rotation's map list (with the rotation on; mapList_startEdit). Returns what
   the original leaves in eax (for the byte settings, its low byte the new value) */
u32 (arena_createClick)(void)
{
	if (g_editingNewArenaName)
		return (*(u32 *)&g_editingNewArenaName);
	if (g_editingNewArenaFragLimit || g_editingNewArenaTimeLimit || g_typingArenaPassword)
		return 0;
	u32 mode = (*(u32 *)&g_arenaCameraMode);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	if (g_rightClick) {
		sound_playMenu(0);
		u32 r = arena_leaveSession();   /* arena_leaveSession: the arena left */
		g_arenaCameraMode = 0;
		return r;
	}
	if (!g_mouseClick || mode != 2)
		return mode;
	u32 button = ((u32)createArena_hitTest(g_mouseX, g_mouseY));   /* createArena_hitTest */
	u8 *players = (u8 *)ADDR(g_newArenaPlayers), *rotation = (u8 *)ADDR(g_newArenaRotation), *type = (u8 *)ADDR(g_newArenaMode);
	u32 r;
	u8 old;
	switch (button) {
	case 0: return arena_editComment();
	case 1: return arena_editPassword();
	case 6: return arena_editFragLimit();
	case 7: return arena_editTimeLimit();
	case 2:
		sound_playMenu(2);
		/* fall through */
	case 12: case 14:
		return arena_stepMap(1);   /* arena_stepMap: the next map */
	case 13:
		return arena_stepMap(0);
	case 3:
		*players += 2;
		r = *players;
		if ((signed char)*players > 16)
			*players = 2;
		return r;
	case 4:
		old = *rotation;
		*rotation = 1 - old;
		if (*rotation)
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
				*type = *rotation ? 0xe : 0xd;
		} else {
			*type += 1;
			r = *type;
			if ((signed char)*type > (*rotation ? 0xe : 0xd))
				*type = 0;
		}
		return r;
	case 8:
		if (g_arenaGameSetUp)
			return 8;
		sound_playMenu(0);
		return lobby_hostArenaLan();   /* lobby_hostArenaLan: create */
	case 9:
		if (g_arenaGameSetUp)
			return 9;
		sound_playMenu(0);
		r = lobby_announceArena();
		return r ? r : lobby_hostArena();   /* lobby_hostArena */
	case 11:
		arena_leaveSession();
		g_arenaCameraMode = 0;
		return sound_playMenu(0);
	case 15:
		if (*rotation != 1)
			return 15;
		sound_playMenu(2);
		return mapList_startEdit(1);   /* mapList_startEdit: the map list (the original pushes a 1 it ignores) */
	}
	return button;
}

/* 0x4079c0: the arena lobby's game list keys (none while the address or password box, a message box, or before the
   arena camera has arrived, g_arenaCameraMode 2). With the join confirmation up only back answers it (the timer 0x378 killed). Up / down held
   move along the list of games (once the blink clock reaches 5, restarting it; nine rows shown from g_gameListTop, the
   selection in g_pickedGame); while no search runs (g_lanSearch, g_lobbySearching, the result box g_lobbyRefreshing) the click key or fire
   joins the selected game (g_lobbyJoinStarted; its join password asked for when connected, g_serverConnected) or asks the lobby to
   join (g_lobbyJoinRequest); cancel2 and back leave (to mode 0), g_dikS cancels the search; g_dikI searches the local network
   (a slot opened, g_lobbyBlinkClock 150), g_dikT the lobby server; g_dikP types a game's IP address (arena_editAddress) */
void (arenaGames_keys)(void)
{
#define g_listTop g_gameListTop
#define g_listRow g_lobbyListRow
#define busy (g_lanSearch || g_lobbySearching || g_lobbyRefreshing)
	int mode = g_arenaCameraMode;
	if (g_typingArenaAddress || mode == 1 || mode == 0 || g_arenaJoinNeedsPassword || g_dialogOpen)
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
		g_pickedGame = g_listTop + row;
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
		g_pickedGame = g_listTop + g_listRow;
		return;
	}
	if (input_justPressed(g_dikJ) || input_justPressed(g_keyClick)) {
		if (busy || g_gameCount <= 0)
			return;
		if (g_serverConnected) {
			g_lobbyJoinStarted = 1;
			g_lobbyJoinRequest = 0;
			arena_askJoinPassword();
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
		g_arenaCameraMode = 0;
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
		g_arenaCameraMode = 0;
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
	if (input_justPressed(g_dikP) && !g_typingArenaAddress) {
		sound_playMenu(0);
		arena_editAddress();
	}
#undef g_listTop
#undef g_listRow
#undef busy
}

/* ---- the player's record (from g_ladderName: the name, +0x1e the level, +0x22 exp, +0x26 power, +0x2a games played,
   +0x2e kills, +0x32 deaths) and its two kept copies (PilotStats: g_pilotLevel and g_pilotLevelKept) ---- */
#define R_EXP g_ladderExp
#define R_POWER (*(float *)&g_ladderPower)
#define R_GAMES g_ladderGames
#define R_KILLS g_ladderKills
#define R_DEATHS g_ladderDeaths

/* the kill rate in percent (as its float bits): kills over kills + deaths; 0 without either (and, when checked, with a
   total not above 0) */
static u32 kill_rate(int kills, int deaths, int checked)
{
	if (!kills && !deaths)
		return 0;
	int total = kills + deaths;
	if (checked && total <= 0)
		return 0;
	float rate = f32(fmul_m((long double)kills, (const float *)ADDR(k_100f)) / (long double)total);   /* x 100 / total */
	return BITS(rate);
}

/* the power: the kill rate x 0.01 x the exp */
static void power_from_rate(u32 rate)
{
	float r;
	BITS(r) = rate;
	R_POWER = f32(fmul_m(fld_m(&r), (const float *)ADDR(k_0_01f)) * (long double)R_EXP);
}

/* a kept copy taken back as the record, when the record's kills are more than 300 above it */
static u32 take_back(u32 kept, u32 rate)
{
	const PilotStats *k = &GAME_VAR(PilotStats, kept);
	if (R_KILLS <= k->kills + 300)
		return rate;
	R_EXP = k->exp;
	R_DEATHS = k->deaths;
	R_GAMES = k->games;
	R_KILLS = k->kills;
	rate = kill_rate(R_KILLS, R_DEATHS, 0);
	power_from_rate(rate);
	return rate;
}

/* the record into the packet (g_netPlayerRecordPacket, a PlayerRecordPacket: the name when asked) and both kept
   copies, and sent to the game server (kind 0x11) */
static void record_send(u32 rate, int name)
{
	PlayerRecordPacket *packet = (PlayerRecordPacket *)g_netPlayerRecordPacket;
	if (name)
		strcpy(packet->name, g_ladderName);
	packet->games = R_GAMES;
	packet->kills = R_KILLS;
	packet->deaths = R_DEATHS;
	packet->exp = R_EXP;
	packet->power = f32(fld_m(&R_POWER));
	packet->level = actor_levelFromValue(R_EXP);
	static const u32 kept[2] = { ADDR(g_pilotLevel), ADDR(g_pilotLevelKept) };
	for (int k = 0; k < 2; k++) {
		GAME_VAR(int, kept[k] + offsetof(PilotStats, games)) = R_GAMES;
		GAME_VAR(int, kept[k] + offsetof(PilotStats, kills)) = R_KILLS;
		GAME_VAR(int, kept[k] + offsetof(PilotStats, deaths)) = R_DEATHS;
		GAME_VAR(int, kept[k] + offsetof(PilotStats, exp)) = R_EXP;
		GAME_VAR(int, kept[k] + offsetof(PilotStats, level)) = (signed char)actor_levelFromValue(R_EXP);
		GAME_VAR(u32, kept[k] + offsetof(PilotStats, killRate)) = rate;
		GAME_VAR(u32, kept[k] + offsetof(PilotStats, power)) = (*(u32 *)&R_POWER);
	}
	net_send(0x11, 0x65);
}

/* 0x4327f0: the player's Ladder record (g_ladderName ..) checked and sent: the power worked out from the kill rate; a kept copy (g_pilotLevel,
   then g_pilotLevelKept) taken back when the record's kills are more than 300 above it; the record sent and kept; then, when
   the exp is more than 150 a kill, it is cut to 2 a kill and the record is sent and kept again. The caller
   ignores the eax it leaves */
void (ladder_checkAndSendRecord)(void)
{
	u32 rate = kill_rate(R_KILLS, R_DEATHS, 1);
	power_from_rate(rate);
	rate = take_back(ADDR(g_pilotLevel), rate);
	rate = take_back(ADDR(g_pilotLevelKept), rate);
	record_send(rate, 1);
	if (R_KILLS * 150 >= R_EXP)
		return;
	R_EXP = R_KILLS * 2;
	rate = kill_rate(R_KILLS, R_DEATHS, 0);
	power_from_rate(rate);
	record_send(rate, 0);
}
#undef R_EXP
#undef R_POWER
#undef R_GAMES
#undef R_KILLS
#undef R_DEATHS

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


/* the arena hosted with its settings (dplay_host): 0 when that failed */
static int host_arena(void)
{
	return dplay_host(g_playerName, g_cfgPlayerName, ((int)(signed char)g_arenaRotation << 8) | (int)g_arenaMap,
	                    (signed char)g_arenaPlayers, (signed char)g_arenaGameType, g_arenaFragLimit, g_arenaTimeLimit, g_playerCorporation);
}

/* the hosted arena's settings taken for the match */
static void take_arena(void)
{
	g_mapIndex = g_arenaMap;
	memcpy((void *)OBJ(g_mapTitle), (const void *)OBJ(g_playerName), 32);
	g_mapRotation = (signed char)g_arenaRotation;
	g_chosenGameMode = (signed char)g_arenaGameType;
	g_fragLimit = g_arenaFragLimit;
	g_timeLimit = g_arenaTimeLimit;
	g_arenaGameSetUp = 1;
}

/* 0x4052c0: the arena hosted on the local network (a slot opened, kind 1): the settings kept, a special room's map;
   the slot or the hosting failing, the game state put back and the connection closed (the error box up, g_hostErrorBox); else the music stopped and the
   settings taken (g_arenaLobbyState 1, back to lobby mode 0). The callers ignore the eax it leaves */
void (lobby_hostArenaLan)(void)
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
		g_hostErrorBox = 1;
		g_quitAsked = 0;
		g_netRole = was;
		arena_leaveSession();
		return;
	}
	music_shutdown();
	g_arenaLobbyState = 1;
	take_arena();
	g_arenaCameraMode = 0;
}

/* 0x4057a0: the arena hosted through DirectPlay (a slot opened, kind 0): the music stopped first, a special room's
   map, the arena hosted and its settings taken whatever the answer. The callers ignore the eax it leaves */
void (lobby_hostArena)(void)
{
	g_arenaLobbyState = 2;
	g_quitAsked = 1;
	g_netRole = 1;
	music_shutdown();
	g_arenaCameraMode = 0;
	arena_openSession(0, NULL);
	special_map(g_playerName, (u8 *)ADDR(g_arenaMap));
	host_arena();
	take_arena();
}

/* 0x405cf0: the arena announced on the lobby server: the settings kept, connected (messages 0x3d no server, 0x46
   refused, 0x3e no events; 0), a special room's map, the hello packet (g_arenaPacket: kind 0x18, the settings, the
   arena's name, this machine's address) sent as kind 10. Returns 1 when sent */
int (lobby_announceArena)(void)
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
	ServerRecord *packet = (ServerRecord *)g_arenaPacket;
	packet->kind = 0x18;
	packet->rotation = g_arenaRotation;
	packet->timeLimit = g_arenaTimeLimit;
	packet->fragLimit = g_arenaFragLimit;
	packet->gameMode = g_arenaGameType;
	packet->players = 1;
	packet->map = g_arenaMap;
	packet->maxPlayers = g_arenaPlayers;
	packet->locked = g_arenaLocked;
	lstrcpyA(packet->password, (const char *)ADDR(g_arenaPassword));
	lstrcpyA(((ServerRecord *)g_arenaPacket)->name, g_playerName);
	jmp_net_getLocalAddress();
	lstrcpyA(((ServerRecord *)g_arenaPacket)->address, g_localAddress);
	g_connectionAwaited = 1;
	g_connectStep = 2;
	net_send(0xa, 0x64);
	g_arenaLobbyState = 2;
	return 1;
}

/* 0x4351c0: the game room's game announced on the game server: the room's settings kept (g_roomRecName), a special
   room's map, the packet (g_roomPacket: kind 0x18, the player's name g_ladderId at +0x43, the settings, the game's name,
   this machine's address) sent as kind 0x12. The callers ignore the eax it leaves */
void (room_announceGame)(void)
{
	room_keepSettings();
	special_map(g_roomRecName, (u8 *)ADDR(g_roomRecMap));
	RoomRecord *packet = (RoomRecord *)g_roomPacket;
	GAME_CDECL(0x49ea80, char *, char *, const char *, int)(packet->hostName, g_ladderId, 0x1e);   /* strncpy */
	packet = (RoomRecord *)g_roomPacket;
	const GameSettings *room = (const GameSettings *)OBJ(g_roomRecName);
	packet->kind = 0x18;
	packet->rotation = room->rotation;
	packet->timeLimit = room->limit[1];
	packet->fragLimit = room->limit[0];
	packet->gameMode = room->mode;
	packet->players = 1;
	packet->map = room->map;
	packet->maxPlayers = room->maxPlayers;
	packet->locked = room->locked;
	lstrcpyA(packet->password, ((const GameSettings *)OBJ(g_roomRecName))->password);
	lstrcpyA(((RoomRecord *)g_roomPacket)->name, g_roomRecName);
	jmp_net_getLocalAddress();
	lstrcpyA(((RoomRecord *)g_roomPacket)->address, g_localAddress);
	g_connectionAwaited = 1;
	g_connectStep = 2;
	net_send(0x12, 0x65);
	g_arenaLobbyState = 2;
}
#undef lstrcpyA
