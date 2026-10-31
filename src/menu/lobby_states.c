/* lobby_states.c: the arena lobby's and the game room's screens set up as they are entered: the camera's target point
   for the screen (and its look-at point), the screen's state cleared, the panel brightness (0x3f333333 = 0.7), the
   message box hidden (0x4dba68 / 0x9dd6bc), and for the lists the map list or the room list reset. The lobby's
   three sub-screens are 0 (the player's own record), 1 (the arena list) and 2 (creating an arena). */
#include "../game.h"
#include <string.h>

#define g_cameraHeight GAME_VAR(int, 0x680380)   /* the menu camera's z, kept for every target point */

static void clear_all(const u32 *addresses, int n)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(int, addresses[k]) = 0;
}

/* 0x404ac0: sub-screen 0: the camera to (35, 0) looking at (-70, 35), the player's record from the profile */
void (lobby_setSubState0)(void)
{
	int z = g_cameraHeight;
	GAME_VAR(u32, 0x4df870) = 0x420c0000;   /* 35.0 */
	GAME_VAR(int, 0x4df874) = 0;
	GAME_VAR(int, 0x4df878) = z;
	GAME_VAR(u32, 0x76d388) = 0xc28c0000;   /* -70.0 */
	GAME_VAR(u32, 0x76d38c) = 0x420c0000;   /* 35.0 */
	GAME_VAR(int, 0x76d390) = z;
	lobby_404930();
	g_arenaLobbyMode = 1;
	GAME_VAR(int, 0x4db51c) = 0;
	GAME_VAR(u32, 0x4dbba0) = 0x3f333333;
	GAME_VAR(int, 0x4dc24c) = 0;
	GAME_VAR(int, 0x4db85c) = 0;
	GAME_VAR(u32, 0x4dba68) = 0xc4ce4000;   /* -1650.0 */
}

/* 0x404b30: sub-screen 1, the arena list: its 24 state words cleared, 999 (no selection), 30 seconds */
void (lobby_setSubState1)(void)
{
	static const u32 cleared[] = { 0x4df884, 0x4dbaac, 0x4db8b8, 0x4dba84, 0x4db854, 0x4dbbec, 0x4dbbf0, 0x4dba90,
	                               0x4db858, 0x4dbac8, 0x4dbaa8, 0x67ef30, 0x4dba80, 0x76d41c, 0x680bb0, 0x4df818,
	                               0x4db71c, 0x4dbaf8, 0x4db85c, 0x4db8b4, 0x4db718, 0x907b2c, 0x4dbaf0, 0x4db714 };
	int z = g_cameraHeight;
	GAME_VAR(u32, 0x4df880) = 0x420c0000;   /* 35.0 */
	GAME_VAR(int, 0x4df888) = z;
	GAME_VAR(int, 0x76d3a0) = z;
	GAME_VAR(u32, 0x76d398) = 0xc28c0000;   /* -70.0 */
	GAME_VAR(u32, 0x76d39c) = 0xc20c0000;   /* -35.0 */
	GAME_VAR(int, 0x4db51c) = 1;
	g_arenaLobbyMode = 1;
	GAME_VAR(u32, 0x4dbba0) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_lastPanel = 999;
	g_lobbyPending = 1;
	GAME_VAR(u32, 0x4dba68) = 0xc4ce4000;
	g_listRefreshPeriod = 30;
}

/* 0x404980: the arena settings record (0x4ded20: title, map, options) copied to the lobby's (0x4db528). Maps 22 .. 24
   can't be chosen (back to 0); a title still the default one becomes "<player name><suffix>" */
void (lobby_drawArenaTitle)(void)
{
	signed char map = g_arenaMap;
	if (map >= 0x16 && map <= 0x18)
		g_arenaMap = map = 0;
	if (!strcmp((char *)0x4ded20, (const char *)0x4ad4a4)) {
		memset((void *)0x4ded20, 0, 32);
		strcpy((char *)0x4ded20, (const char *)0x4dedb0);
		strcat((char *)0x4ded20, (const char *)0x4ad49c);
		map = g_arenaMap;
	}
	memset((void *)0x4db528, 0, 32);
	strcpy((char *)0x4db528, (const char *)0x4ded20);
	u8 b1 = g_arenaPlayers, b2 = g_arenaCustomize, b3 = g_arenaGameType, b4 = g_arenaFragLimit,
	   b5 = g_arenaTimeLimit;
	GAME_VAR(signed char, 0x4db548) = map;
	GAME_VAR(u8, 0x4db54b) = b3;
	GAME_VAR(u8, 0x4db549) = b1;
	GAME_VAR(u8, 0x4db54a) = b2;
	GAME_VAR(int, 0x4db54e) = 0;
	g_arenaFragLimitTyped = b4;
	g_arenaTimeLimitTyped = b5;
	GAME_VAR(int, 0x4db552) = 0;
}

/* 0x403420: the map on/off list (8-byte entries from 0x4d9508): the first time all off, then the first n maps
   (0x67ef00) on; four entries' second words cleared and the list laid out */
void (mapList_init)(void)
{
	if (!GAME_VAR(int, 0x4db510)) {
		for (u32 p = 0x4d950c; p < 0x4db50c; p += 8) {
			GAME_VAR(int, p - 4) = 0;
			GAME_VAR(int, p) = 0;
		}
		for (int k = 0; k < GAME_VAR(int, 0x67ef00); k++) {
			GAME_VAR(int, 0x4d9508 + k * 8) = 1;
			GAME_VAR(int, 0x4d950c + k * 8) = 0;
		}
	}
	GAME_VAR(int, 0x4d95b8) = 0;
	GAME_VAR(int, 0x4d95c0) = 0;
	GAME_VAR(int, 0x4d95c8) = 0;
	GAME_VAR(int, 0x4db508) = 0;
	mapList_layout();
	GAME_VAR(int, 0x4db510) = 1;
}

/* 0x404c20: sub-screen 2, creating an arena: the camera to (-35, 0) looking at (70, 35), the arena's title, the map
   list */
void (lobby_setSubState2)(void)
{
	static const u32 cleared[] = { 0x4dbbf4, 0x4dba88, 0xa0b360, 0x4db55c, 0x4ded54, 0x4db85c, 0x907b2c, 0x4dbab0,
	                               0x4db850, 0x4db518, 0x4dbacc };
	int z = g_cameraHeight;
	GAME_VAR(u32, 0x4df890) = 0xc20c0000;   /* -35.0 */
	GAME_VAR(int, 0x4df894) = 0;
	GAME_VAR(int, 0x4df898) = z;
	GAME_VAR(u32, 0x76d3a8) = 0x428c0000;   /* 70.0 */
	GAME_VAR(u32, 0x76d3ac) = 0x420c0000;   /* 35.0 */
	GAME_VAR(int, 0x76d3b0) = z;
	lobby_drawArenaTitle();
	GAME_VAR(int, 0x4db51c) = 2;
	g_arenaLobbyMode = 1;
	GAME_VAR(u32, 0x4dbba0) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	GAME_VAR(u32, 0x4dba68) = 0xc4ce4000;
	g_mapPreviewChanged = 1;
	mapList_init();
}

/* 0x433700: the room settings record (0x5b1b30: a name and six bytes) copied to the room's (0x4df9c8); map types
   22 .. 24 become 0 */
void (room_loadSettingsRecord)(void)
{
	if (GAME_VAR(signed char, 0x5b1b50) > 0x15 && GAME_VAR(signed char, 0x5b1b50) < 0x19)
		GAME_VAR(u8, 0x5b1b50) = 0;
	g_roomMap = GAME_VAR(u8, 0x5b1b50);
	memset((void *)0x4df9c8, 0, 32);
	GAME_VAR(u8, 0x4df9eb) = GAME_VAR(u8, 0x5b1b53);   /* stored before the name is copied, as in the original */
	strcpy((char *)0x4df9c8, (const char *)0x5b1b30);
	GAME_VAR(u8, 0x4df9e9) = GAME_VAR(u8, 0x5b1b51);
	GAME_VAR(u8, 0x4df9ea) = GAME_VAR(u8, 0x5b1b52);
	g_roomFragLimit = GAME_VAR(u8, 0x5b1b54);
	g_roomTimeLimit = GAME_VAR(u8, 0x5b1b55);
}

/* 0x433790: the game room's list (state 2) entered: the room's settings, its state cleared, the map list */
void (room_enterGameList)(void)
{
	static const u32 cleared[] = { 0x4dbbf4, 0x4dba88, 0xa0b360, 0x4ded54, 0x907b2c, 0x9dd380, 0x9dd388, 0x9dd568,
	                               0x9dd6a8 };
	room_loadSettingsRecord();
	GAME_VAR(int, 0x9dd834) = 2;
	g_roomMode = 1;
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_mapPreviewChanged = 1;
	GAME_VAR(char, 0x4df9ea) = 0;
	mapList_init();
}

/* 0x433800: the room list (state 4) entered: its ten 0x44-byte rows cleared (each marked empty), the paging and
   selection cleared, the distance limit 10,000,000, 999 rooms */
void (room_enterRoomList)(void)
{
	static const u32 cleared[] = { 0x9dd6ac, 0x9dd350, 0x76d40c, 0x9dd6b8, 0x9dd3b0, 0xa0b350, 0xa0b35c, 0x9dd1b4,
	                               0x9dd1d0, 0x9dd300, 0x9dd328 };
	for (u32 e = 0x9dcef4; e < 0x9dd19c; e += 0x44) {
		memset((void *)(e - 4), 0, 0x36);
		GAME_VAR(int, e + 0x32) = 1;
	}
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	g_roomMode = 1;
	g_rankingFirst = 1;
	GAME_VAR(int, 0x9dd834) = 4;
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;
	g_rankingLast = 10;
	GAME_VAR(u32, 0x9dd384) = 0x4b189680;   /* 10000000.0 */
	g_roomListPages = 999;
}

/* 0x432620: the ladder's fixed game: its name (0x4b17bc) and the player's (0x9dd570), map 8, limits 10 and 10, in
   both the room's record and the room settings; the mech unpacked */
void (lobby_ladderGameName)(void)
{
	strcpy((char *)0x4df9c8, (const char *)0x4b17bc);
	GAME_VAR(char, 0x4df9e9) = 8;
	GAME_VAR(char, 0x4df9eb) = 0;
	strcpy((char *)0x76d450, (const char *)0x9dd570);
	GAME_VAR(char, 0x4df9e8) = 0;
	GAME_VAR(char, 0x4df9ec) = 10;
	GAME_VAR(char, 0x4df9ed) = 10;
	GAME_VAR(char, 0x4df9ea) = 0;
	strcpy((char *)0x5b1b30, (const char *)0x4df9c8);
	GAME_VAR(char, 0x5b1b51) = 8;
	GAME_VAR(char, 0x5b1b53) = 0;
	GAME_VAR(char, 0x5b1b50) = 0;
	GAME_VAR(char, 0x5b1b54) = 10;
	GAME_VAR(char, 0x5b1b55) = 10;
	GAME_VAR(char, 0x5b1b52) = 0;
	mech_unpackFromRecord();
}

/* 0x432be0: the joined game's settings (0x9dd570: its name, its host's, the room record 0x5b1b30, the mech and the
   window rectangles) copied into the room screen's */
void (room_copyJoinedSettings)(void)
{
	strcpy((char *)0x9dd1d8, (const char *)0x9dd570);
	strcpy((char *)0x9dd20e, (const char *)0x9dd5a6);
	u8 map = GAME_VAR(u8, 0x5b1b51);
	strcpy((char *)0x4df9c8, (const char *)0x5b1b30);
	GAME_VAR(u8, 0x4df9e9) = map;
	g_roomMap = GAME_VAR(u8, 0x5b1b50);
	GAME_VAR(u8, 0x4df9ea) = GAME_VAR(u8, 0x5b1b52);
	GAME_VAR(u8, 0x4df9eb) = GAME_VAR(u8, 0x5b1b53);
	g_roomFragLimit = GAME_VAR(u8, 0x5b1b54);
	g_roomTimeLimit = GAME_VAR(u8, 0x5b1b55);
	memcpy((void *)0x9dd260, (void *)0x9dd5f8, 11);
	memcpy((void *)0x9dd26b, (void *)0x9dd603, 0x90);
	static const u32 copy[6][2] = { { 0x9dd240, 0x9dd5d8 }, { 0x9dd244, 0x9dd5dc }, { 0x9dd25c, 0x9dd5f4 },
	                                { 0x9dd254, 0x9dd5ec }, { 0x9dd258, 0x9dd5f0 }, { 0x9dd250, 0x9dd5e8 } };
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

/* 0x41e390: the two window rectangles (the joined game's 0x9dd5d8 and the room's 0x9dd240) made the same when one
   reaches past the other, then each limited to the screen's (0x4de71e) */
void (console_41e390)(void)
{
	int c5, a1, b1;   /* the values the original holds in registers where the branches meet */
	if (GAME_VAR(int, 0x9dd5ec) > GAME_VAR(int, 0x9dd254) || GAME_VAR(int, 0x9dd5dc) > GAME_VAR(int, 0x9dd244)) {
		rect_copy(0x9dd5d8, 0x9dd240);
		c5 = GAME_VAR(int, 0x9dd254);
		a1 = b1 = GAME_VAR(int, 0x9dd244);
	} else {
		c5 = GAME_VAR(int, 0x9dd5ec);
		a1 = GAME_VAR(int, 0x9dd5dc);
		b1 = GAME_VAR(int, 0x9dd244);
		if (GAME_VAR(int, 0x9dd254) > c5 || b1 > a1) {
			rect_copy(0x9dd240, 0x9dd5d8);
			b1 = a1;
		}
	}
	int e0 = GAME_VAR(int, 0x4de71e), e1 = GAME_VAR(int, 0x4de722), e3 = GAME_VAR(int, 0x4de726),
	    e4 = GAME_VAR(int, 0x4de72a), e5 = GAME_VAR(int, 0x4de72e), e6 = GAME_VAR(int, 0x4de732);
	if (c5 > e5 || a1 > e1) {
		GAME_VAR(int, 0x9dd5d8) = e0;
		GAME_VAR(int, 0x9dd5dc) = e1;
		GAME_VAR(int, 0x9dd5e4) = e3;
		GAME_VAR(int, 0x9dd5ec) = e5;
		GAME_VAR(int, 0x9dd5f0) = e6;
		GAME_VAR(int, 0x9dd5e8) = e4;
	}
	if (GAME_VAR(int, 0x9dd254) > e5 || b1 > e1) {
		GAME_VAR(int, 0x9dd244) = e1;
		GAME_VAR(int, 0x9dd240) = e0;
		GAME_VAR(int, 0x9dd24c) = e3;
		GAME_VAR(int, 0x9dd254) = e5;
		GAME_VAR(int, 0x9dd258) = e6;
		GAME_VAR(int, 0x9dd250) = e4;
	}
}

/* 0x432db0: a received game's settings (0xa0563c) into the room: its names, the 11 mech bytes, the six colour pairs
   (a negative or NaN chroma or value becomes 0), the window rectangle; then the room screen, the lobby's title
   record and the mech */
void (room_takeReceivedSettings)(void)
{
	strcpy((char *)0x9dd570, (const char *)0xa0563c);
	strcpy((char *)0x9dd5a6, (const char *)0xa0565a);
	memcpy((void *)0x9dd5f8, (void *)0xa0568c, 11);
	for (int k = 0; k < 6; k++) {
		memcpy((void *)(0x9dd603 + k * 0x18), (void *)(0xa05697 + k * 0x18), 0x18);
		if (!(GAME_VAR(float, 0x9dd607 + k * 0x18) >= GAME_VAR(float, 0x4a93e8)))
			GAME_VAR(int, 0x9dd607 + k * 0x18) = 0;
		if (!(GAME_VAR(float, 0x9dd60b + k * 0x18) >= GAME_VAR(float, 0x4a93e8)))
			GAME_VAR(int, 0x9dd60b + k * 0x18) = 0;
	}
	static const u32 rect[7][2] = { { 0x9dd5d8, 0xa05727 }, { 0x9dd5dc, 0xa05737 }, { 0x9dd5e4, 0xa0573b },
	                                { 0x9dd5f4, 0xa0573f }, { 0x9dd5ec, 0xa0572f }, { 0x9dd5f0, 0xa05733 },
	                                { 0x9dd5e8, 0xa0572b } };
	for (int k = 0; k < 7; k++)
		GAME_VAR(int, rect[k][0]) = GAME_VAR(int, rect[k][1]);
	room_copyJoinedSettings();
	memset((void *)0x4de700, 0, 7 * 4 + 2);
	strcpy((char *)0x4de700, (const char *)0x9dd570);
	static const u32 title[6][2] = { { 0x4de71e, 0x9dd5d8 }, { 0x4de722, 0x9dd5dc }, { 0x4de72e, 0x9dd5ec },
	                                 { 0x4de732, 0x9dd5f0 }, { 0x4de72a, 0x9dd5e8 }, { 0x4de726, 0x9dd5e4 } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, title[k][0]) = GAME_VAR(int, title[k][1]);
	mech_unpackFromRecord();
	GAME_VAR(int, 0x4dc4b4) = GAME_VAR(int, 0x9dd5d8);
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
	strcpy((char *)0x9dd570, (const char *)0x9dd1d8);
	strcpy((char *)0x9dd5a6, (const char *)0x9dd20e);
	default_mech((u8 *)0x9dd260, (u8 *)0x9dd26b);
	default_mech((u8 *)0x9dd5f8, (u8 *)0x9dd603);
	GAME_VAR(int, 0x9dd240) = 1;
	GAME_VAR(int, 0x9dd5d8) = 1;
	memset((void *)0x4de700, 0, 7 * 4 + 2);
	static const u32 zero[] = { 0x9dd5dc, 0x9dd5ec, 0x9dd5f0, 0x9dd5e8, 0x9dd5f4, 0x9dd244, 0x9dd254, 0x9dd258,
	                            0x9dd250, 0x9dd25c };
	for (unsigned k = 0; k < sizeof zero / sizeof zero[0]; k++)
		GAME_VAR(int, zero[k]) = 0;
	strcpy((char *)0x4de700, (const char *)0x9dd570);
	GAME_VAR(int, 0x4de726) = GAME_VAR(int, 0x9dd5e4);
	GAME_VAR(int, 0x4de71e) = 1;
	static const u32 zero2[] = { 0x4de722, 0x4de72e, 0x4de732, 0x4de72a };
	for (int k = 0; k < 4; k++)
		GAME_VAR(int, zero2[k]) = 0;
	strcpy(GAME_VAR(char *, 0xa0b320) + 4, (const char *)0x9dd1d8);
	strcpy(GAME_VAR(char *, 0xa0b320) + 0x22, (const char *)0x9dd1f6);
	strcpy(GAME_VAR(char *, 0xa0b320) + 0x2e, (const char *)0x9dd20e);
	u8 *record = GAME_VAR(u8 *, 0xa0b320);
	default_mech(record + 0x70, record + 0x7b);
	GAME_VAR(int, 0x4dc4b4) = GAME_VAR(int, 0x9dd5d8);
	*(int *)record = 0x18;
	u32 r = GAME_CDECL(0x4521c0, u32, int, int)(0xf, 0x65);   /* net_send */
	g_roomAnswerAwaited = 1;
	return r;
}

/* 0x4080c0: the lobby's back keys (unless a dialog is open): the first closes the list (0x907b2c), the second leaves
   the game (quit code 2). Returns what the original leaves in eax */
u32 (lobby_keysBack)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	u32 r = input_justPressed(GAME_VAR(int, 0x4e0cdc));
	if (r) {
		GAME_VAR(int, 0x907b2c) = 0;
		return r;
	}
	r = input_justPressed(GAME_VAR(int, 0x4e1510));
	if (!r)
		return 0;
	GAME_VAR(int, 0x907b2c) = 0;
	return app_closeWindow(2);
}

/* 0x40cf80: the lobby's player screen: the arena tunnel, then in modes other than 0 and 1 (0x4dbb3c) and not on
   sub-screen 5, the player panel (arena_drawNameDialog), or with a dialog open just its frame. Returns what the original
   leaves in eax */
u32 (lobbyPlayer_draw)(void)
{
	GAME_CDECL(0x4091b0, void, void)();   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaLobbyMode;
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x4db51c) == 5)
		return mode;
	if (!g_dialogOpen)
		return GAME_CDECL(0x409bc0, u32, void)();   /* arena_drawNameDialog */
	return GAME_CDECL(0x428c30, u32, int, int, int, int)(g_arenaNameDialogLeft, GAME_VAR(int, 0x4dbb6c),
	                                                     g_arenaNameDialogRight, g_arenaNameDialogBottom);   /* menu_drawFrame */
}

/* 0x4081f0: the lobby's keys, by sub-screen (0x4db51c): 0 the player's record, 1 the arena list (or its chat line
   while open), 2 creating an arena (the back keys while the list is open, the map list, the quit dialog, else the
   connect), 5 the top; 3 and 4 have none. Returns what the handler leaves in eax (else the sub-screen) */
u32 (lobby_processKeys)(void)
{
	u32 screen = GAME_VAR(u32, 0x4db51c);
	switch (screen) {
	case 0:
		return GAME_CDECL(0x407840, u32, void)();   /* lobbyPlayer_keys */
	case 1:
		if (GAME_VAR(int, 0x907b2c))
			return GAME_CDECL(0x407970, u32, void)();   /* lobbyJoin_keys */
		return GAME_CDECL(0x4079c0, u32, void)();       /* lobbyJoin_keysChat */
	case 2:
		if (GAME_VAR(int, 0x907b2c))
			return GAME_CDECL(0x4080c0, u32, void)();   /* lobby_keysBack */
		if (GAME_VAR(int, 0x4db508))
			return GAME_CDECL(0x403870, u32, void)();   /* the map list */
		if (GAME_VAR(int, 0x4db55c))
			return GAME_CDECL(0x408110, u32, void)();   /* lobby_keysQuit */
		return GAME_CDECL(0x407e40, u32, void)();       /* lobbyTop_connect */
	case 5:
		return GAME_CDECL(0x407750, u32, void)();       /* lobbyTop_keys */
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
		GAME_VAR(int, 0x907b2c) = 0;
	if (!g_mouseClick)
		return 0;
	int button = GAME_CDECL(0x4045a0, int, int, int)(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button == 0) {
		GAME_VAR(int, 0x907b2c) = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		GAME_VAR(int, 0x907b2c) = 0;
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
	u32 screen = GAME_VAR(u32, 0x4db51c);
	switch (screen) {
	case 5:
		CALL(0x40cef0);   /* lobbyTop_draw */
		menu_drawBackground();
		if (GAME_VAR(int, 0x67ef14) == 1 && g_arenaLobbyMode == 2)
			return CALL(0x40ce70);   /* menu_drawDimOverlay */
		return CALL(0x408680);       /* lobbyTop_drawTitle */
	case 0:
		menu_drawBackground();
		CALL(0x408270);              /* arena_camera: the lobby's camera */
		return CALL(0x40cf80);       /* lobbyPlayer_draw */
	case 1:
		menu_drawBackground();
		CALL(0x408270);
		return CALL(0x40cfd0);       /* lobbyJoin_draw */
	case 2:
		menu_drawBackground();
		CALL(0x408270);
		return CALL(0x40d390);       /* lobbyCreate_draw */
	}
	return screen;
}

/* 0x4076c0: the lobby's clicks: the top (lobby_topPageClicks), the player (lobby_playerScreenClicks), the arena list (its close button
   while closing, the quit dialog while open, else connecting), creating an arena (the list's dialog, the map list,
   else the quit dialog if open, then the screen's clicks) */
u32 (lobby_onStateChange)(void)
{
	u32 screen = GAME_VAR(u32, 0x4db51c);
	switch (screen) {
	case 5:
		return CALL(0x406950);
	case 0:
		return CALL(0x406a60);
	case 1:
		if (GAME_VAR(int, 0x4db8b4))
			return CALL(0x406b60);   /* lobby_close */
		if (GAME_VAR(int, 0x907b2c))
			return CALL(0x406bd0);   /* lobby_quitDialogClicks */
		return CALL(0x406c30);       /* lobby_connect */
	case 2:
		if (GAME_VAR(int, 0x907b2c))
			return CALL(0x407270);   /* create_quitDialogClicks */
		if (GAME_VAR(int, 0x4db508))
			return CALL(0x4036c0);   /* mapList_mouse: the map list */
		if (GAME_VAR(int, 0x4db55c))
			CALL(0x407300);          /* lobby_pageClicks */
		return CALL(0x407410);       /* arena_createClick */
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
	GAME_VAR(int, 0x4dda44) = 0;
	u32 hit = GAME_CDECL(0x4044e0, u32, int, int)(g_mouseX, g_mouseY);   /* the close button's hit test */
	if (hit)
		return hit;
	GAME_VAR(int, 0x4dbb10) = 0;
	g_arenaJoinWaiting = 0;
	CALL(0x452fe0);   /* arena_leaveSession */
	GAME_VAR(int, 0x4db8b4) = 0;
	return IMPORT(0x4a9330, u32, void *, u32)(g_hWndMain, 0x378);   /* KillTimer */
}

/* 0x403870: the map list's keys: the first key toggles the map (mapList_ok) - or, read a second time, closes the
   list with a sound -, the others move the cursor up and down */
u32 (room_mapListKeys)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e1510)))
		return CALL(0x403640);   /* mapList_ok */
	if (input_justPressed(GAME_VAR(int, 0x4e1510))) {
		u32 r = GAME_CDECL(0x41e760, u32, int)(0);   /* sound_playMenu */
		GAME_VAR(int, 0x4db508) = 0;
		return r;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)))
		return CALL(0x4034e0);   /* mapList_chooseAll */
	u32 r = input_justPressed(GAME_VAR(int, 0x4e0ce0));
	if (r)
		return CALL(0x403530);   /* mapList_chooseNone */
	return r;
}

/* 0x435a40: leaving the game room: the room's name sent to the others (message 0x19, 0x65 bytes), a pause of half a
   second, back to the main menu (state 300), the connection closed, the mech reloaded from the profile */
u32 (room_leaveGame)(void)
{
	strcpy(GAME_VAR(char *, 0xa0b33c), (const char *)0x9dd570);
	GAME_CDECL(0x4521c0, int, int, int)(0x19, 0x65);   /* net_send */
	IMPORT(0x4a9110, void, u32)(500);                   /* Sleep */
	GAME_CDECL(0x441250, void, int)(4);                 /* input_setKeysBlocked */
	GAME_VAR(int, 0x67ef20) = 300;
	GAME_CDECL(0x48b420, void, void)();                 /* nullsub_48b420 */
	GAME_CDECL(0x451e60, void, void)();                 /* net_disconnect */
	g_roomConnected = 0;
	return CALL(0x4463a0);                              /* mech_loadFromProfile */
}

/* 0x407270: the create screen's quit dialog clicks, only with none of its other panels (and no dialog) open: as
   lobby_quitDialogClicks. Returns what the original leaves in eax */
u32 (create_quitDialogClicks)(void)
{
	static const u32 panels[5] = { 0x4dbab0, 0x4db850, 0x4db518, 0x4dbacc, 0x90d1c4 };
	for (int k = 0; k < 5; k++)
		if (GAME_VAR(int, panels[k]))
			return GAME_VAR(u32, panels[k]);
	if (g_keyEnter)
		GAME_VAR(int, 0x907b2c) = 0;
	if (!g_mouseClick)
		return 0;
	int button = GAME_CDECL(0x4045a0, int, int, int)(g_mouseX, g_mouseY);
	if (button == 0) {
		GAME_VAR(int, 0x907b2c) = 0;
		return (u32)app_closeWindow(2);
	}
	if (button == 1) {
		GAME_VAR(int, 0x907b2c) = 0;
		return 0;
	}
	return (u32)(button - 1);
}

/* 0x405230: the arena title's edit field opened: the keyboard released for typing, the input line emptied (20
   characters at most), placed at the panel's origin + (0xd8, 0xd0), the fade timer 5, the Windows edit control made.
   Returns what that leaves in eax */
u32 (lobby_editTextField_405230)(void)
{
	GAME_CDECL(0x401460, void, void)();   /* input_releaseKeyboard */
	GAME_VAR(int, 0x68039c) = 1;
	menu_clearInputBuffer(0x14);
	memset((void *)0x9dc92c, 0, 0x400);
	GAME_VAR(int, 0x4dbbd4) = 0;
	GAME_VAR(int, 0x9da3d8) = GAME_VAR(int, 0x4db8c8) + 0xd8;
	GAME_VAR(int, 0x9da3dc) = GAME_VAR(int, 0x4db8cc) + 0xd0;
	GAME_VAR(int, 0x9dbf10) = (int)strlen((const char *)0x9dc92c);
	GAME_VAR(int, 0x4dbbd8) = 0;
	GAME_VAR(u32, 0x9da434) = 0x40a00000;   /* 5 */
	/* chat_createEdit(20); the original also leaves the 20 it gave menu_clearInputBuffer on the stack as a second
	   argument */
	u32 r = GAME_CDECL(0x43f460, u32, int, int)(0x14, 0x14);
	GAME_VAR(int, 0x4db714) = 1;
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
u32 (lobby_keepArenaSettings)(void) { return settings_store((u8 *)0x4db528, (u8 *)0x4ded20, 0x42d730); }
/* 0x433640: the room's settings kept (0x5b1b30) and written to the registry (reg_writeCharacterSettings) */
u32 (room_keepSettings)(void) { return settings_store((u8 *)0x4df9c8, (u8 *)0x5b1b30, 0x432400); }

/* 0x40d390: the create-arena screen drawn: the tunnel, then (modes other than 0 and 1, not on sub-screen 5) the
   dialog's frame if one is open, else the settings kept in range (players 0 .. 16 else 8, the two limits at most 250
   else 30, the map 0 .. 14 else 0), the screen, the map list when open, the options panel when shown. Returns what
   the original leaves in eax */
u32 (lobbyCreate_draw)(void)
{
	CALL(0x4091b0);   /* arena_drawTunnel: the tunnel */
	int mode = g_arenaLobbyMode;
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x4db51c) == 5)
		return (u32)mode;
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x4dbb00), GAME_VAR(int, 0x4dbb04),
		                                                     GAME_VAR(int, 0x4dbb08), GAME_VAR(int, 0x4dbb0c));   /* menu_drawFrame */
	signed char players = GAME_VAR(signed char, 0x4ded41);
	if (players < 0 || players > 0x10)
		g_arenaPlayers = 8;
	if (g_arenaFragLimit > 0xfa)
		g_arenaFragLimit = 0x1e;
	if (g_arenaTimeLimit > 0xfa)
		g_arenaTimeLimit = 0x1e;
	signed char map = GAME_VAR(signed char, 0x4ded43);
	if (map < 0 || map > 0xe)
		g_arenaGameType = 0;
	CALL(0x40b750);   /* arena_createDraw */
	if (GAME_VAR(int, 0x4db508) == 1)
		CALL(0x4038e0);   /* mapList_draw: the map list */
	if (!GAME_VAR(int, 0x4dba88))
		return 0;
	return CALL(0x405b80);   /* arena_connectionOutcome */
}

/* 0x408110: the create screen's quit dialog keys (no other dialog open): one closes it, the other starts the arena:
   multiplayer on, the music stopped, the arena settings (0x4ded20) as the game's (map, players, limits), the lobby
   left. Returns what the original leaves in eax */
u32 (lobby_keysQuit)(void)
{
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	u32 r = input_justPressed(GAME_VAR(int, 0x4e0cdc));
	if (r) {
		GAME_VAR(int, 0x4db55c) = 0;
		return r;
	}
	if (!input_justPressed(GAME_VAR(int, 0x4e1510)))
		return 0;
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 1;
	CALL(0x457310);   /* music_shutdown */
	u32 limits = GAME_VAR(u32, 0x4ded44);
	g_mapRotation = GAME_VAR(signed char, 0x4ded42);
	GAME_VAR(int, 0x9dad94) = g_arenaMap;
	memcpy((void *)0x67fb44, (const void *)0x4ded20, 32);
	g_chosenGameMode = GAME_VAR(signed char, 0x4ded43);
	GAME_VAR(u32, 0x4df8e8) = limits & 0xff;
	GAME_VAR(u32, 0x76d408) = (limits >> 8) & 0xff;
	g_arenaLobbyMode = 0;
	GAME_VAR(int, 0x4dbbf4) = 1;
	GAME_VAR(int, 0x4db55c) = 0;
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
		return GAME_CDECL(0x41e760, u32, int)(0);
	}
	if (!g_mouseClick || mode != 2)
		return (u32)mode;
	u32 button = GAME_CDECL(0x404460, u32, int, int)(g_mouseX, g_mouseY);   /* the screen's hit test */
	u32 r;
	switch (button) {
	case 0:
		return CALL(0x404cd0);   /* arena_editTextField_404cd0 */
	case 2:
		sound_playMenu(0);
		GAME_VAR(int, 0x4dc24c) = 2;
		return CALL(0x40ee20);   /* menu_enterMenus: the ARM CENTER */
	case 3:
		sound_playMenu(0);
		r = CALL(0x4050a0);      /* arena_saveSettings */
		g_arenaLobbyMode = 0;
		return r;
	case 4:
		r = GAME_CDECL(0x41e760, u32, int)(0);
		g_arenaLobbyMode = 0;
		return r;
	case 5:
		sound_playMenu(0);
		return CALL(0x4050f0);   /* cfg_defaultPlayerName */
	}
	return button;
}

/* a joined session's settings taken from its record (0x4a bytes): the music stopped, the 32-byte rules (+4), +0x24,
   +0x25, +0x2c and the colours (+0x2d, +0x2e); the lobby left (0x4dbb3c 0) for the game (0x67ef14 1, 0x67ef04 2) */
static void take_session(const u8 *rec)
{
	music_shutdown();
	GAME_VAR(int, 0x9dad94) = (signed char)rec[0x25];
	memcpy((void *)0x67fb44, rec + 4, 32);
	g_mapRotation = (signed char)rec[0x24];
	g_arenaLobbyMode = 0;
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 2;
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
	const u8 *rec = (const u8 *)(0x9087c0 + session * 0x4a);
	GAME_VAR(int, 0x4dbbec) = 0;
	g_lobbyJoinRequest = 0;
	g_arenaTimeLimit = g_arenaTimeLimitTyped = rec[0x2e];
	g_arenaFragLimit = g_arenaFragLimitTyped = rec[0x2d];
	int r = GAME_CDECL(0x453180, int, int, u32, const char *, int)(session, *(const u32 *)rec, (const char *)0x4dedb0,
	                                                               g_playerCorporation);   /* dplay_join: join */
	if (r != 0x1f4)
		return GAME_CDECL(0x41ee40, u32, int)(r == 0x1f5 ? 0x36 : 0x35);   /* the message */
	take_session(rec);
	GAME_VAR(int, 0x4db8b4) = 0;
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
		GAME_VAR(int, 0x4dbb10) = 0;
		g_arenaJoinWaiting = 0;
		arena_leaveSession();
		menu_showMessage(0x44);
		GAME_VAR(int, 0x4db8b4) = 0;
		return;
	}
	int pick = g_arenaJoinRow;
	u8 *rec;
	if (pick == 99999) {
		g_arenaJoinRow = 0;
		if (!GAME_VAR(int, 0x4db708))
			return;
		const u8 *in = GAME_VAR(const u8 *, 0x4dbbf8);
		rec = (u8 *)0x9dae20;
		*(u32 *)rec = *(const u32 *)in;
		rec[0x2d] = in[0x28];
		rec[0x2e] = in[0x29];
		rec[0x2c] = in[0x27];
		rec[0x25] = in[0x24];
		rec[0x24] = in[0x25];
		strcpy((char *)rec + 4, (const char *)in + 0x2e);
	} else {
		if (!GAME_VAR(int, 0x4db708))
			return;
		rec = (u8 *)(0x9087c0 + pick * 0x4a);
		*(u32 *)rec = *GAME_VAR(const u32 *, 0x4dbbf8);
		g_arenaFragLimit = rec[0x2d];
		g_arenaTimeLimit = rec[0x2e];
	}
	int r = dplay_join(0, *(const u32 *)rec, (const char *)0x4dedb0, g_playerCorporation);
	if (r == 0x1f4) {
		take_session(rec);
		net_disconnect();
	} else {
		static const u8 message[5] = { 0x43, 0x42, 0x42, 0x44, 0x45 };   /* 501 .. 505 */
		if ((u32)(r - 0x1f5) <= 4)
			menu_showMessage(message[r - 0x1f5]);
		arena_leaveSession();
	}
	GAME_VAR(int, 0x4dbb10) = 0;
	GAME_VAR(int, 0x4db708) = 0;
	GAME_VAR(int, 0x4db8b4) = 0;
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
	u32 r = GAME_CDECL(0x441250, u32, int)(4);   /* input_setKeysBlocked: keys blocked */
	g_nextScreen = 300;
	GAME_CDECL(0x48b420, void, void)();          /* nullsub_48b420 */
	return r;
}

/* 0x407750: the lobby's top page keys (no dialog open, not while 0x67ef14 is 1): back (when 0x9dae10 allows) or
   leave goes to the main menu; the other three pick the lobby's sub-pages 2, 0 and 1. Returns the action's eax */
u32 (lobbyTop_keys)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (GAME_VAR(int, 0x67ef14) == 1)
		return 0;
	if (input_justPressed(g_keyCancel2) && GAME_VAR(int, 0x9dae10) > 0) {
		sound_playMenu(0);
		return to_main_menu();
	}
	if (key_hit(0x4e0cdc))
		return GAME_CDECL(0x404c20, u32, void)();   /* lobby_setSubState2 */
	if (key_hit(0x4e1514))
		return GAME_CDECL(0x404ac0, u32, void)();   /* lobby_setSubState0 */
	if (key_hit(0x4e14f8))
		return GAME_CDECL(0x404b30, u32, void)();   /* lobby_setSubState1 */
	if (key_hit(0x4e153c))
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
	if (GAME_VAR(int, 0x67ef14) == 1)
		return 0;
	if (GAME_VAR(int, 0x4ded88)) {
		const Outline *buttons = (const Outline *)0x5b1cf8;
		for (int i = 0; i < 4; i++) {
			if (point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), buttons[i]) != 1)
				continue;
			sound_playMenu(0);
			switch (i) {
			case 0: GAME_CDECL(0x404ac0, void, void)(); break;   /* lobby_setSubState0 */
			case 1: GAME_CDECL(0x404b30, void, void)(); break;   /* lobby_setSubState1 */
			case 2: GAME_CDECL(0x404c20, void, void)(); break;   /* lobby_setSubState2 */
			case 3: to_main_menu(); break;
			}
			break;
		}
	}
	int right = g_keyEnter;
	if (!right)
		return 0;
	int allowed = GAME_VAR(int, 0x9dae10);
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
	u32 page = GAME_VAR(u32, 0x4dbb3c);
	if (page == 1 || page == 0 || g_dialogOpen)
		return page;
	if (g_typingArenaName) {
		if (GAME_VAR(int, 0x68039c))
			return page;
		const char *typed = (const char *)0x9dc92c;
		u32 length = strlen(typed);
		g_typingArenaName = 0;
		if (!length)
			return 0;
		memset((void *)0x4db560, 0, 32);
		strcpy((char *)0x4db560, typed);
		return length + 1;
	}
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_arenaLobbyMode = 0;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1510))) {
		sound_playMenu(0);
		GAME_CDECL(0x4050a0, void, void)();
		g_arenaLobbyMode = 0;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0ce0))) {
		sound_playMenu(0);
		return GAME_CDECL(0x4050f0, u32, void)();   /* cfg_defaultPlayerName */
	}
	if (!input_justPressed(g_keyBack))
		return 0;
	u32 r = GAME_CDECL(0x41e760, u32, int)(0);      /* sound_playMenu */
	g_arenaLobbyMode = 0;
	return r;
}

/* 0x4060f0: the lobby server connection opened (unless open, 0x4db718): the old one closed, net_connect(100) (0: no
   server, message 0x3d; 2: message 0x46) and the socket's messages sent to the main window (failing: 0x3e). Then
   the lobby screen's state reset and the hello sent (0x180001, net_send(0xd, 100)). 1, or 0 on a failure */
int (lobby_openConnection)(void)
{
	if (!g_lobbyConnectionOpen) {
		GAME_CDECL(0x451e60, void, void)();                   /* net_disconnect */
		int r = net_connect(100);
		if (r == 0 || r == 2) {
			GAME_CDECL(0x41ee40, void, int)(r == 0 ? 0x3d : 0x46);   /* the message */
			return 0;
		}
		if (!GAME_CDECL(0x452170, int, void *, int)(GAME_VAR(void *, 0x4ded18), 100)) {   /* net_asyncSelect */
			GAME_CDECL(0x41ee40, void, int)(0x3e);
			return 0;
		}
	}
	g_lobbyConnectionOpen = 1;
	g_serverConnected = 1;
	GAME_VAR(int, 0x4dba88) = 1;
	g_connectStep = 2;
	g_serverAnswerIn = 0;
	g_lobbyRefreshing = 0;
	g_lobbySearching = 1;
	g_searchResult = 0;
	GAME_VAR(int, 0x680bb8) = 0;
	GAME_VAR(int, 0x4dba8c) = 0;
	g_serverConnectionState = 0;
	GAME_VAR(int, 0x9087b0) = 0;
	GAME_VAR(int, 0x67ef30) = 0;
	g_arenaListFull = 1;
	g_arenaHaveList = 0;
	GAME_VAR(int, 0x76d41c) = 0;
	GAME_VAR(u32, 0x4dba80) = 0x447a0000;   /* 1000.0f */
	GAME_VAR(int, 0x680bb0) = 0;
	GAME_VAR(int, 0x4df818) = 0;
	*GAME_VAR(u32 *, 0xa0b31c) = 0x180001;   /* the message to send */
	GAME_CDECL(0x4521c0, int, int, int)(0xd, 100);   /* net_send */
	GAME_VAR(int, 0x4db8b4) = 0;
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
		GAME_CDECL(0x404640, void, void)();   /* menuState400_enter */
		GAME_CDECL(0x404b30, void, void)();   /* lobby_setSubState1 */
		memset((void *)0x4dbbd4, 0, 24);
		strcpy((char *)0x4dbbd4, (const char *)0x4de748);
		u32 r = GAME_CDECL(0x406200, u32, int)(99999);   /* arena_joinListed */
		g_lobbyReply = 0x69;
		return r;
	}
	if (!arena_loadSettings((const char *)0x4ad5e4))   /* "axiswl.dat" */
		return IMPORT(0x4a932c, u32, int)(0);                               /* PostQuitMessage */
	memset((void *)0x4ded20, 0, 32);
	strcpy((char *)0x4ded20, (const char *)0x5b191c);
	u8 clan = GAME_VAR(u8, 0x5b1958);
	GAME_VAR(u32, 0x4ded46) = 0;
	GAME_VAR(u8, 0x4ded4e) = clan;
	GAME_VAR(u32, 0x4ded4a) = 0;
	if (clan == 1)
		strcpy((char *)0x4ded46, (const char *)0x5b193c);
	g_arenaFragLimit = GAME_VAR(u8, 0x5b1950);
	g_arenaGameType = GAME_VAR(u8, 0x5b194c);
	g_arenaCustomize = 0;
	GAME_VAR(u8, 0x4ded40) = GAME_VAR(u8, 0x5b1944);
	g_arenaPlayers = GAME_VAR(u8, 0x5b1948);
	g_arenaTimeLimit = GAME_VAR(u8, 0x5b1954);
	GAME_CDECL(0x404640, void, void)();
	GAME_CDECL(0x404b30, void, void)();
	u32 r = GAME_CDECL(0x4057a0, u32, void)();   /* lobby_checkReservedName */
	g_lobbyReply = 0x68;
	return r;
}

/* 0x407300: the lobby page's clicks (nothing else open: 0x4dbab0, 0x4db850, 0x4db518, 0x4dbacc, no dialog): a right
   click or button 0x11 closes the page (0x4db55c); button 0x10 starts the game with the player's settings (the
   32-byte record 0x4ded20 and its colour / corporation bytes), the music stopped. Returns what the original
   leaves in eax */
u32 (lobby_pageClicks)(void)
{
	u32 busy = GAME_VAR(u32, 0x4dbab0);
	if (busy || GAME_VAR(int, 0x4db850) || GAME_VAR(int, 0x4db518) || g_typingArenaPassword || g_dialogOpen)
		return busy;
	if (g_keyEnter) {
		GAME_VAR(int, 0x4db55c) = 0;
		return 0;
	}
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	int button = GAME_CDECL(0x404520, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* createArena_hitTest */
	if (button == 0x11) {
		GAME_VAR(int, 0x4db55c) = 0;
		return 0;
	}
	if (button != 0x10)
		return button - 0x11;
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 1;
	music_shutdown();
	g_mapRotation = (signed char)g_arenaCustomize;
	GAME_VAR(int, 0x9dad94) = (signed char)GAME_VAR(u8, 0x4ded40);
	memcpy((void *)0x67fb44, (const void *)0x4ded20, 32);
	g_chosenGameMode = (signed char)g_arenaGameType;
	g_fragLimit = g_arenaFragLimit;
	g_timeLimit = g_arenaTimeLimit;
	g_arenaLobbyMode = 0;
	GAME_VAR(int, 0x4dbbf4) = 1;
	GAME_VAR(int, 0x4db55c) = 0;
	return GAME_VAR(u32, 0x4ded44);
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
	const u8 *me = (const u8 *)0x4ded20;
	if (state == 1) {
		GAME_VAR(int, 0x4dba88) = 0;
		GAME_VAR(int, 0x67ef14) = 1;
		GAME_VAR(int, 0x67ef04) = 1;
		music_shutdown();
		g_arenaLobbyMode = 0;
		GAME_CDECL(0x452ec0, void, int, int)(0, 0);   /* arena_openSession */
		GAME_CDECL(0x453090, void, const void *, const void *, int, int, int, int, int, u32)(me, (const void *)0x4dedb0,
			(int)(signed char)me[0x22] << 8 | (int)(signed char)me[0x20], (signed char)me[0x21], (signed char)me[0x23],
			me[0x24], me[0x25], GAME_VAR(u32, 0x4dedd0));   /* dplay_host: host */
		GAME_VAR(int, 0x9dad94) = (signed char)me[0x20];
		memcpy((void *)0x67fb44, me, 32);
		g_mapRotation = (signed char)me[0x22];
		g_chosenGameMode = (signed char)me[0x23];
		g_fragLimit = me[0x24];
		g_timeLimit = me[0x25];
		state = g_connectStep;
		GAME_VAR(int, 0x4ded54) = 1;
	}
	if (state != 0 && state != 3 && state != 4)
		return state;
	u32 r = GAME_CDECL(0x451e60, u32, void)();   /* net_451e60: the connection closed */
	g_connectStep = 2;
	if (state == 3)
		GAME_VAR(int, 0x907b2c) = 1;
	GAME_VAR(int, 0x4dba88) = 0;
	GAME_VAR(int, 0x4ded54) = 0;
	if (state == 4)
		r = GAME_CDECL(0x41ee40, u32, int)(0x46);   /* the message */
	return r;
}

/* 0x407e40: the "create arena" page after typing (not while typing or with a message box): a typed field is taken
   (the arena's name into 0x4db528 unless blank (sound 6); the password into 0x4db54e; the two limits as numbers,
   0 .. 250 (else 250), into the bytes 0x4db54c / 0x4db54d; an empty line changes nothing), else the keys: create
   (0x4e14f4; lobby_4052c0) and join (0x4e1528; 0x405cf0, then the name check) unless connecting, and the two close
   keys (the arena left). Returns what the original leaves in eax */
u32 (lobbyTop_connect)(void)
{
	u32 mode = GAME_VAR(u32, 0x4dbb3c);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	const char *line = (const char *)0x9dc92c;
	if (GAME_VAR(int, 0x4dbab0)) {   /* the arena's name */
		if (g_paused)
			return mode;
		if (!strlen(line) || GAME_CDECL(0x4343b0, int, const char *)(line) == 1) {   /* name_isBlank: blank */
			u32 r = strlen(line) ? GAME_CDECL(0x41e760, u32, int)(6) : 0;
			GAME_VAR(int, 0x4dbab0) = 0;
			return r;
		}
		GAME_VAR(int, 0x4dbab0) = 0;
		memset((void *)0x4db528, 0, 32);
		strcpy((char *)0x4db528, line);
		return strlen(line) + 1;
	}
	if (g_typingArenaPassword) {   /* the password */
		if (g_paused)
			return mode;
		memset((void *)0x4db54e, 0, 8);
		g_typingArenaPassword = 0;
		GAME_VAR(int, 0x4e1868) = 0;
		strcpy((char *)0x4db54e, line);
		return 0;
	}
	static const u32 limit[2][2] = { { 0x4db850, 0x4db54c }, { 0x4db518, 0x4db54d } };
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
	if (input_justPressed(GAME_VAR(int, 0x4e14f4)) && !GAME_VAR(int, 0x4ded54)) {
		sound_playMenu(0);
		return GAME_CDECL(0x4052c0, u32, void)();   /* lobby_4052c0: create */
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1528)) && !GAME_VAR(int, 0x4ded54)) {
		sound_playMenu(0);
		u32 r = GAME_CDECL(0x405cf0, u32, void)();
		return r ? r : GAME_CDECL(0x4057a0, u32, void)();   /* lobby_checkReservedName */
	}
	u32 r = 0;
	static const u32 close[2] = { 0x4e0cdc, 0x76d48c };
	for (int k = 0; k < 2; k++) {
		r = (u32)input_justPressed(GAME_VAR(int, close[k]));
		if (r) {
			GAME_CDECL(0x452fe0, void, void)();   /* arena_leaveSession: the arena left */
			g_arenaLobbyMode = 0;
			r = GAME_CDECL(0x41e760, u32, int)(0);
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
	if (GAME_VAR(int, 0x4dbab0))
		return GAME_VAR(u32, 0x4dbab0);
	if (GAME_VAR(int, 0x4db850) || GAME_VAR(int, 0x4db518) || g_typingArenaPassword)
		return 0;
	u32 mode = GAME_VAR(u32, 0x4dbb3c);
	if (mode == 1 || mode == 0 || g_dialogOpen)
		return mode;
	if (g_keyEnter) {
		sound_playMenu(0);
		u32 r = GAME_CDECL(0x452fe0, u32, void)();   /* arena_leaveSession: the arena left */
		g_arenaLobbyMode = 0;
		return r;
	}
	if (!GAME_VAR(int, 0x4ded88) || mode != 2)
		return mode;
	u32 button = GAME_CDECL(0x404520, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* createArena_hitTest */
	u8 *players = (u8 *)0x4db549, *custom = (u8 *)0x4db54a, *type = (u8 *)0x4db54b;
	u32 r;
	u8 old;
	switch (button) {
	case 0: return GAME_CDECL(0x404d70, u32, void)();
	case 1: return GAME_CDECL(0x404f90, u32, void)();
	case 6: return GAME_CDECL(0x404e10, u32, void)();
	case 7: return GAME_CDECL(0x404ed0, u32, void)();
	case 2:
		sound_playMenu(2);
		/* fall through */
	case 12: case 14:
		return GAME_CDECL(0x4068d0, u32, int)(1);   /* lobby_4068d0: the next map */
	case 13:
		return GAME_CDECL(0x4068d0, u32, int)(0);
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
		r = (u32)input_isDown(GAME_VAR(int, 0x67ef24));
		if (!r) r = (u32)input_isDown(GAME_VAR(int, 0x9db0ac));
		if (!r) r = (u32)input_isDown(GAME_VAR(int, 0x6803a8));
		if (!r) r = (u32)input_isDown(GAME_VAR(int, 0x9dad8c));
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
		if (GAME_VAR(int, 0x4ded54))
			return 8;
		sound_playMenu(0);
		return GAME_CDECL(0x4052c0, u32, void)();   /* lobby_4052c0: create */
	case 9:
		if (GAME_VAR(int, 0x4ded54))
			return 9;
		sound_playMenu(0);
		r = GAME_CDECL(0x405cf0, u32, void)();
		return r ? r : GAME_CDECL(0x4057a0, u32, void)();   /* lobby_checkReservedName */
	case 11:
		GAME_CDECL(0x452fe0, void, void)();
		g_arenaLobbyMode = 0;
		return GAME_CDECL(0x41e760, u32, int)(0);
	case 15:
		if (*custom != 1)
			return 15;
		sound_playMenu(2);
		return GAME_CDECL(0x403490, u32, int)(1);   /* mapList_startEdit: the map list (the original pushes a 1 it ignores) */
	}
	return button;
}

/* 0x4079c0: the arena lobby's join screen keys (none while the "full" or "joining" box, a message box, or in modes
   0 / 1 (0x4dbb3c)). With the join confirmation up only back answers it (the timer 0x378 killed). Up / down held
   move along the list of games (once the blink clock reaches 5, restarting it; nine rows shown from g_listTop, the
   selection in 0x76d41c); while no search runs (0x4dba90, 0x4db858, the result box 0x4db8b8) the click key or fire
   joins the selected game (0x4dbbec; the chat line opened when connected, 0x4dbaac) or asks its password
   (0x4dbbf0); cancel2 and back leave (to mode 0), 0x4e1524 cancels the search; 0x4e14f4 searches the local network
   (a slot opened, 0x4dba80 150), 0x4e1528 the lobby server; 0x4e1514 edits the arena's title */
void (lobbyJoin_keysChat)(void)
{
#define g_listTop GAME_VAR(int, 0x680bb0)
#define g_listRow GAME_VAR(int, 0x4df818)
#define g_gameCount GAME_VAR(int, 0x67ef30)
#define busy (g_lanSearch || g_lobbySearching || g_lobbyRefreshing)
	int mode = g_arenaLobbyMode;
	if (GAME_VAR(int, 0x4db714) || mode == 1 || mode == 0 || GAME_VAR(int, 0x4db8bc) || GAME_VAR(int, 0x90d1c4))
		return;
	if (GAME_VAR(int, 0x4db8b4)) {
		if (input_justPressed(g_keyBack)) {
			GAME_VAR(int, 0x4dbb10) = 0;
			g_arenaJoinWaiting = 0;
			arena_leaveSession();
			GAME_VAR(int, 0x4db8b4) = 0;
			KillTimer(g_hWndMain, 0x378);
		}
		return;
	}
	if (input_isDown(g_keyUp)) {
		if (!(g_cursorBlink >= *(const float *)0x4a93d0))
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
		if (!(g_cursorBlink >= *(const float *)0x4a93d0))
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
	if (input_justPressed(GAME_VAR(int, 0x4e14f8)) || input_justPressed(g_keyClick)) {
		if (busy || g_gameCount <= 0)
			return;
		if (g_serverConnected) {
			GAME_VAR(int, 0x4dbbec) = 1;
			g_lobbyJoinRequest = 0;
			arena_chatLine();
		} else {
			g_lobbyJoinRequest = 1;
			GAME_VAR(int, 0x4dbbec) = 0;
		}
		return;
	}
	if (input_justPressed(g_keyCancel2)) {
		g_serverConnectionState = 0;
		arena_leaveSession();
		net_disconnect();
		g_serverAnswerIn = 1;
		g_arenaLobbyMode = 0;
		GAME_VAR(u32, 0x4dba80) = 0x3f800000;   /* 1 */
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1524))) {
		g_serverConnectionState = 0;
		GAME_VAR(u32, 0x4dba80) = 0x3f800000;
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
		GAME_VAR(u32, 0x4dba80) = 0x3f800000;
		g_serverAnswerIn = 1;
		arena_leaveSession();
		net_disconnect();
		g_arenaLobbyMode = 0;
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e14f4))) {
		if (busy)
			return;
		if (GAME_VAR(int, 0x4db854)) {
			g_lobbyConnectionOpen = 0;
			net_disconnect();
		}
		if (GAME_VAR(int, 0x4dba84))
			arena_leaveSession();
		g_serverListCount = 0;
		arena_openSession(1, NULL);
		g_lanSearch = 1;
		GAME_VAR(int, 0x4dba84) = 1;
		GAME_VAR(int, 0x680bb8) = 0;
		g_gameCount = 0;
		g_serverConnected = 0;
		GAME_VAR(int, 0x4db854) = 0;
		GAME_VAR(u32, 0x4dba80) = 0x43160000;   /* 150 */
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1528))) {
		if (busy)
			return;
		g_lobbyConnectionOpen = 0;
		net_disconnect();
		arena_leaveSession();
		g_serverListCount = 0;
		if (lobby_openConnection() == 1) {
			g_serverConnected = 1;
			g_lobbySearching = 1;
			GAME_VAR(int, 0x4db854) = 1;
			g_lobbyConnectionOpen = 1;
			GAME_VAR(int, 0x4dba84) = 0;
		}
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1514)) && !GAME_VAR(int, 0x4db714)) {
		sound_playMenu(0);
		lobby_editTextField_405230();
	}
#undef g_listTop
#undef g_listRow
#undef g_gameCount
#undef busy
}

/* ---- the player's record (from 0x4de700: the name, +0x1e the level, +0x22 points, +0x26 rating, +0x2a 0x4de72a,
   +0x2e wins, +0x32 losses) and its two kept copies (0x9dd5d8 and 0x9dd240: +0 level, +4 points, +0xc rating,
   +0x10 0x4de72a's value, +0x14 wins, +0x18 losses, +0x1c the win rate) ---- */
#define R_POINTS GAME_VAR(int, 0x4de722)
#define R_RATING GAME_VAR(float, 0x4de726)
#define R_OTHER GAME_VAR(int, 0x4de72a)
#define R_WINS GAME_VAR(int, 0x4de72e)
#define R_LOSSES GAME_VAR(int, 0x4de732)

/* the win rate in percent (as its float bits): 0 without games (and, when checked, with a total not above 0) */
static u32 win_rate(int wins, int losses, int checked)
{
	if (!wins && !losses)
		return 0;
	int total = wins + losses;
	if (checked && total <= 0)
		return 0;
	float rate = f32(fmul_m((long double)wins, (const float *)0x4a93f4) / (long double)total);   /* x 100 / total */
	return BITS(rate);
}

/* the rating: the rate x 0.01 x the points */
static void rate_points(u32 rate)
{
	float r;
	BITS(r) = rate;
	R_RATING = f32(fmul_m(fld_m(&r), (const float *)0x4a9420) * (long double)R_POINTS);
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
	u8 *packet = GAME_VAR(u8 *, 0xa0b338);
	if (name)
		strcpy((char *)packet, (const char *)0x4de700);
	*(int *)(packet + 0x1e) = R_OTHER;
	*(int *)(packet + 0x22) = R_WINS;
	*(int *)(packet + 0x26) = R_LOSSES;
	*(int *)(packet + 0x2a) = R_POINTS;
	*(float *)(packet + 0x32) = f32(fld_m(&R_RATING));
	*(int *)(packet + 0x2e) = actor_levelFromValue(R_POINTS);
	static const u32 kept[2] = { 0x9dd5d8, 0x9dd240 };
	for (int k = 0; k < 2; k++) {
		GAME_VAR(int, kept[k] + 0x10) = R_OTHER;
		GAME_VAR(int, kept[k] + 0x14) = R_WINS;
		GAME_VAR(int, kept[k] + 0x18) = R_LOSSES;
		GAME_VAR(int, kept[k] + 4) = R_POINTS;
		GAME_VAR(int, kept[k]) = (signed char)actor_levelFromValue(R_POINTS);
		GAME_VAR(u32, kept[k] + 0x1c) = rate;
		GAME_VAR(u32, kept[k] + 0xc) = GAME_VAR(u32, 0x4de726);
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
	rate = take_back(0x9dd5d8, rate);
	rate = take_back(0x9dd240, rate);
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
		{ 0x18, { 0x4ad554, 0x4ad548, 0x4ad53c, 0x4ad530 } },
		{ 0x16, { 0x4ad524, 0x4ad514, 0x4ad504, 0x4ad4f4 } },
		{ 0x17, { 0x4ad4e8, 0x4ad4d8, 0x4ad4c8, 0x4ad4b8 } } };
	for (int r = 0; r < 3; r++)
		for (int k = 0; k < 4; k++)
			if (!strcmp(name, (const char *)rooms[r].names[k])) {
				*map = rooms[r].map;
				break;
			}
}

#define ARENA(off) GAME_VAR(signed char, 0x4ded20 + (off))   /* the arena's settings: the name, then the map (+0x20) .. */

/* the arena hosted with its settings (dplay_host): 0 when that failed */
static int host_arena(void)
{
	return dplay_host((const char *)0x4ded20, (const char *)0x4dedb0, ((int)ARENA(0x22) << 8) | (int)ARENA(0x20),
	                    ARENA(0x21), ARENA(0x23), (u8)ARENA(0x24), (u8)ARENA(0x25), g_playerCorporation);
}

/* the hosted arena's settings taken for the match */
static void take_arena(void)
{
	GAME_VAR(int, 0x9dad94) = ARENA(0x20);
	memcpy((void *)0x67fb44, (const void *)0x4ded20, 32);
	g_mapRotation = ARENA(0x22);
	g_chosenGameMode = ARENA(0x23);
	g_fragLimit = (u8)ARENA(0x24);
	g_timeLimit = (u8)ARENA(0x25);
	GAME_VAR(int, 0x4ded54) = 1;
}

/* 0x4052c0: the arena hosted on the local network (a slot opened, kind 1): the settings kept, a special room's map;
   the slot or the hosting failing, the game state put back and the connection closed (0x4db55c set); else the music stopped and the
   settings taken (0x4dbbf4 1, back to lobby mode 0). The callers ignore the eax it leaves */
void (lobby_roomNameCheck)(void)
{
	int was = GAME_VAR(int, 0x67ef04);
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 1;
	lobby_keepArenaSettings();
	int hosted = arena_openSession(1, NULL);
	if (hosted) {
		special_map((const char *)0x4ded20, (u8 *)0x4ded40);
		hosted = host_arena();
	}
	if (!hosted) {
		GAME_VAR(int, 0x4db55c) = 1;
		GAME_VAR(int, 0x67ef14) = 0;
		GAME_VAR(int, 0x67ef04) = was;
		arena_leaveSession();
		return;
	}
	music_shutdown();
	GAME_VAR(int, 0x4dbbf4) = 1;
	take_arena();
	g_arenaLobbyMode = 0;
}

/* 0x4057a0: the arena hosted through DirectPlay (a slot opened, kind 0): the music stopped first, a special room's
   map, the arena hosted and its settings taken whatever the answer. The callers ignore the eax it leaves */
void (lobby_checkReservedName)(void)
{
	GAME_VAR(int, 0x4dbbf4) = 2;
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 1;
	music_shutdown();
	g_arenaLobbyMode = 0;
	arena_openSession(0, NULL);
	special_map((const char *)0x4ded20, (u8 *)0x4ded40);
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
	GAME_VAR(int, 0x4ded54) = 1;
	special_map((const char *)0x4ded20, (u8 *)0x4ded40);
	u8 *packet = GAME_VAR(u8 *, 0xa0b310);
	packet[0] = 0x18;
	packet[0x49] = ARENA(0x22);
	packet[0x48] = ARENA(0x25);
	packet[0x47] = ARENA(0x24);
	packet[0x46] = ARENA(0x23);
	packet[0x45] = 1;
	packet[0x43] = ARENA(0x20);
	packet[0x44] = ARENA(0x21);
	packet[0x52] = ARENA(0x2e);
	lstrcpyA((char *)packet + 0x53, (const char *)0x4ded46);
	lstrcpyA((char *)GAME_VAR(u8 *, 0xa0b310) + 1, (const char *)0x4ded20);
	jmp_net_getLocalAddress_4532e0();
	lstrcpyA((char *)GAME_VAR(u8 *, 0xa0b310) + 0x33, (const char *)0xa0b43c);
	GAME_VAR(int, 0x4dba88) = 1;
	g_connectStep = 2;
	net_send(0xa, 0x64);
	GAME_VAR(int, 0x4dbbf4) = 2;
	return 1;
}
#undef ARENA

/* 0x4351c0: the game room's game announced on the game server: the room's settings kept (0x5b1b30), a special
   room's map, the packet (0xa0b328: kind 0x18, the player's name 0x9dd570 at +0x43, the settings, the game's name,
   this machine's address) sent as kind 0x12. The callers ignore the eax it leaves */
void (lobby_checkReservedName3)(void)
{
	room_keepSettings();
	special_map((const char *)0x5b1b30, (u8 *)0x5b1b50);
	u8 *packet = GAME_VAR(u8 *, 0xa0b328);
	GAME_CDECL(0x49ea80, char *, char *, const char *, int)((char *)packet + 0x43, (const char *)0x9dd570, 0x1e);   /* strncpy */
	packet = GAME_VAR(u8 *, 0xa0b328);
	const u8 *room = (const u8 *)0x5b1b30;
	packet[0] = 0x18;
	packet[0x67] = room[0x22];
	packet[0x66] = room[0x25];
	packet[0x65] = room[0x24];
	packet[0x64] = room[0x23];
	packet[0x63] = 1;
	packet[0x61] = room[0x20];
	packet[0x62] = room[0x21];
	packet[0x70] = room[0x2e];
	lstrcpyA((char *)packet + 0x71, (const char *)0x5b1b56);
	lstrcpyA((char *)GAME_VAR(u8 *, 0xa0b328) + 1, (const char *)0x5b1b30);
	jmp_net_getLocalAddress_4532e0();
	lstrcpyA((char *)GAME_VAR(u8 *, 0xa0b328) + 0x33, (const char *)0xa0b43c);
	GAME_VAR(int, 0x4dba88) = 1;
	g_connectStep = 2;
	net_send(0x12, 0x65);
	GAME_VAR(int, 0x4dbbf4) = 2;
}
#undef lstrcpyA
