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
	GAME_VAR(int, 0x4dbb3c) = 1;
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
	GAME_VAR(int, 0x4dbb3c) = 1;
	GAME_VAR(u32, 0x4dbba0) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	GAME_VAR(int, 0x907b24) = 999;
	GAME_VAR(int, 0xa0b360) = 1;
	GAME_VAR(u32, 0x4dba68) = 0xc4ce4000;
	GAME_VAR(int, 0x5b1914) = 30;
}

/* 0x404980: the arena settings record (0x4ded20: title, map, options) copied to the lobby's (0x4db528). Maps 22 .. 24
   can't be chosen (back to 0); a title still the default one becomes "<player name><suffix>" */
void (lobby_drawArenaTitle)(void)
{
	signed char map = GAME_VAR(signed char, 0x4ded40);
	if (map >= 0x16 && map <= 0x18)
		GAME_VAR(signed char, 0x4ded40) = map = 0;
	if (!strcmp((char *)0x4ded20, (const char *)0x4ad4a4)) {
		memset((void *)0x4ded20, 0, 32);
		strcpy((char *)0x4ded20, (const char *)0x4dedb0);
		strcat((char *)0x4ded20, (const char *)0x4ad49c);
		map = GAME_VAR(signed char, 0x4ded40);
	}
	memset((void *)0x4db528, 0, 32);
	strcpy((char *)0x4db528, (const char *)0x4ded20);
	u8 b1 = GAME_VAR(u8, 0x4ded41), b2 = GAME_VAR(u8, 0x4ded42), b3 = GAME_VAR(u8, 0x4ded43), b4 = GAME_VAR(u8, 0x4ded44),
	   b5 = GAME_VAR(u8, 0x4ded45);
	GAME_VAR(signed char, 0x4db548) = map;
	GAME_VAR(u8, 0x4db54b) = b3;
	GAME_VAR(u8, 0x4db549) = b1;
	GAME_VAR(u8, 0x4db54a) = b2;
	GAME_VAR(int, 0x4db54e) = 0;
	GAME_VAR(u8, 0x4db54c) = b4;
	GAME_VAR(u8, 0x4db54d) = b5;
	GAME_VAR(int, 0x4db552) = 0;
}

/* 0x403420: the map on/off list (8-byte entries from 0x4d9508): the first time all off, then the first n maps
   (0x67ef00) on; four entries' second words cleared and the list laid out */
void (room_403420)(void)
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
	room_403300();
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
	GAME_VAR(int, 0x4dbb3c) = 1;
	GAME_VAR(u32, 0x4dbba0) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	GAME_VAR(u32, 0x4dba68) = 0xc4ce4000;
	GAME_VAR(int, 0x680cd0) = 1;
	room_403420();
}

/* 0x433700: the room settings record (0x5b1b30: a name and six bytes) copied to the room's (0x4df9c8); map types
   22 .. 24 become 0 */
void (room_433700)(void)
{
	if (GAME_VAR(signed char, 0x5b1b50) > 0x15 && GAME_VAR(signed char, 0x5b1b50) < 0x19)
		GAME_VAR(u8, 0x5b1b50) = 0;
	GAME_VAR(u8, 0x4df9e8) = GAME_VAR(u8, 0x5b1b50);
	memset((void *)0x4df9c8, 0, 32);
	GAME_VAR(u8, 0x4df9eb) = GAME_VAR(u8, 0x5b1b53);   /* stored before the name is copied, as in the original */
	strcpy((char *)0x4df9c8, (const char *)0x5b1b30);
	GAME_VAR(u8, 0x4df9e9) = GAME_VAR(u8, 0x5b1b51);
	GAME_VAR(u8, 0x4df9ea) = GAME_VAR(u8, 0x5b1b52);
	GAME_VAR(u8, 0x4df9ec) = GAME_VAR(u8, 0x5b1b54);
	GAME_VAR(u8, 0x4df9ed) = GAME_VAR(u8, 0x5b1b55);
}

/* 0x433790: the game room's list (state 2) entered: the room's settings, its state cleared, the map list */
void (room_433790)(void)
{
	static const u32 cleared[] = { 0x4dbbf4, 0x4dba88, 0xa0b360, 0x4ded54, 0x907b2c, 0x9dd380, 0x9dd388, 0x9dd568,
	                               0x9dd6a8 };
	room_433700();
	GAME_VAR(int, 0x9dd834) = 2;
	GAME_VAR(int, 0x9dce48) = 1;
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	GAME_VAR(int, 0x680cd0) = 1;
	GAME_VAR(char, 0x4df9ea) = 0;
	room_403420();
}

/* 0x433800: the room list (state 4) entered: its ten 0x44-byte rows cleared (each marked empty), the paging and
   selection cleared, the distance limit 10,000,000, 999 rooms */
void (room_433800)(void)
{
	static const u32 cleared[] = { 0x9dd6ac, 0x9dd350, 0x76d40c, 0x9dd6b8, 0x9dd3b0, 0xa0b350, 0xa0b35c, 0x9dd1b4,
	                               0x9dd1d0, 0x9dd300, 0x9dd328 };
	for (u32 e = 0x9dcef4; e < 0x9dd19c; e += 0x44) {
		memset((void *)(e - 4), 0, 0x36);
		GAME_VAR(int, e + 0x32) = 1;
	}
	clear_all(cleared, sizeof cleared / sizeof cleared[0]);
	GAME_VAR(int, 0x9dce48) = 1;
	GAME_VAR(int, 0x9dd83c) = 1;
	GAME_VAR(int, 0x9dd834) = 4;
	GAME_VAR(u32, 0x9dd6bc) = 0x3f333333;
	GAME_VAR(int, 0x9dd7dc) = 10;
	GAME_VAR(u32, 0x9dd384) = 0x4b189680;   /* 10000000.0 */
	GAME_VAR(int, 0x9dd4b8) = 999;
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
	FUN_0040ddb0();
}

/* 0x432be0: the joined game's settings (0x9dd570: its name, its host's, the room record 0x5b1b30, the mech and the
   window rectangles) copied into the room screen's */
void (room_432be0)(void)
{
	strcpy((char *)0x9dd1d8, (const char *)0x9dd570);
	strcpy((char *)0x9dd20e, (const char *)0x9dd5a6);
	u8 map = GAME_VAR(u8, 0x5b1b51);
	strcpy((char *)0x4df9c8, (const char *)0x5b1b30);
	GAME_VAR(u8, 0x4df9e9) = map;
	GAME_VAR(u8, 0x4df9e8) = GAME_VAR(u8, 0x5b1b50);
	GAME_VAR(u8, 0x4df9ea) = GAME_VAR(u8, 0x5b1b52);
	GAME_VAR(u8, 0x4df9eb) = GAME_VAR(u8, 0x5b1b53);
	GAME_VAR(u8, 0x4df9ec) = GAME_VAR(u8, 0x5b1b54);
	GAME_VAR(u8, 0x4df9ed) = GAME_VAR(u8, 0x5b1b55);
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
void (room_432db0)(void)
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
	room_432be0();
	memset((void *)0x4de700, 0, 7 * 4 + 2);
	strcpy((char *)0x4de700, (const char *)0x9dd570);
	static const u32 title[6][2] = { { 0x4de71e, 0x9dd5d8 }, { 0x4de722, 0x9dd5dc }, { 0x4de72e, 0x9dd5ec },
	                                 { 0x4de732, 0x9dd5f0 }, { 0x4de72a, 0x9dd5e8 }, { 0x4de726, 0x9dd5e4 } };
	for (int k = 0; k < 6; k++)
		GAME_VAR(int, title[k][0]) = GAME_VAR(int, title[k][1]);
	FUN_0040ddb0();
	GAME_VAR(int, 0x4dc4b4) = GAME_VAR(int, 0x9dd5d8);
	GAME_VAR(int, 0x9dd84c) = 1;
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
	return profile_41e7a0(2);
}

/* 0x40cf80: the lobby's player screen: the arena tunnel, then in modes other than 0 and 1 (0x4dbb3c) and not on
   sub-screen 5, the player panel (arena_409bc0), or with a dialog open just its frame. Returns what the original
   leaves in eax */
u32 (lobbyPlayer_draw)(void)
{
	GAME_CDECL(0x4091b0, void, void)();   /* arena_4091b0: the tunnel */
	int mode = GAME_VAR(int, 0x4dbb3c);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x4db51c) == 5)
		return mode;
	if (!g_dialogOpen)
		return GAME_CDECL(0x409bc0, u32, void)();   /* arena_409bc0 */
	return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x4dbb68), GAME_VAR(int, 0x4dbb6c),
	                                                     GAME_VAR(int, 0x4dbb70), GAME_VAR(int, 0x4dbb74));   /* menu_drawFrame */
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
u32 (lobby_406bd0)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (GAME_VAR(int, 0x4ded8c))
		GAME_VAR(int, 0x907b2c) = 0;
	if (!g_mouseClick)
		return 0;
	int button = GAME_CDECL(0x4045a0, int, int, int)(g_mouseX, g_mouseY);   /* the dialog's hit test */
	if (button == 0) {
		GAME_VAR(int, 0x907b2c) = 0;
		return (u32)profile_41e7a0(2);
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
		if (GAME_VAR(int, 0x67ef14) == 1 && GAME_VAR(int, 0x4dbb3c) == 2)
			return CALL(0x40ce70);   /* menu_drawDimOverlay */
		return CALL(0x408680);       /* lobbyTop_drawTitle */
	case 0:
		menu_drawBackground();
		CALL(0x408270);              /* arena_408270: the lobby's camera */
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

/* 0x4076c0: the lobby's clicks: the top (lobby_406950), the player (lobby_406a60), the arena list (its close button
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
			return CALL(0x406bd0);   /* lobby_406bd0 */
		return CALL(0x406c30);       /* lobby_connect */
	case 2:
		if (GAME_VAR(int, 0x907b2c))
			return CALL(0x407270);   /* lobby_407270 */
		if (GAME_VAR(int, 0x4db508))
			return CALL(0x4036c0);   /* room_4036c0: the map list */
		if (GAME_VAR(int, 0x4db55c))
			CALL(0x407300);          /* lobby_407300 */
		return CALL(0x407410);       /* arena_createClick */
	}
	return screen;
}

/* 0x406b60: a click on the arena list's close button (mode 2, no dialog open): the list closed, the session search
   stopped (arena_452fe0) and its timer (0x378) killed. Returns what the original leaves in eax */
u32 (lobby_close)(void)
{
	if (g_dialogOpen)
		return g_dialogOpen;
	if (!g_mouseClick || GAME_VAR(int, 0x4dbb3c) != 2)
		return g_mouseClick;
	GAME_VAR(int, 0x4dda44) = 0;
	u32 hit = GAME_CDECL(0x4044e0, u32, int, int)(g_mouseX, g_mouseY);   /* the close button's hit test */
	if (hit)
		return hit;
	GAME_VAR(int, 0x4dbb10) = 0;
	GAME_VAR(int, 0x4dbb78) = 0;
	CALL(0x452fe0);   /* arena_452fe0 */
	GAME_VAR(int, 0x4db8b4) = 0;
	return IMPORT(0x4a9330, u32, void *, u32)(g_hWndMain, 0x378);   /* KillTimer */
}

/* 0x403870: the map list's keys: the first key toggles the map (room_403640) - or, read a second time, closes the
   list with a sound -, the others move the cursor up and down */
u32 (FUN_00403870)(void)
{
	if (input_justPressed(GAME_VAR(int, 0x4e1510)))
		return CALL(0x403640);   /* room_403640 */
	if (input_justPressed(GAME_VAR(int, 0x4e1510))) {
		u32 r = GAME_CDECL(0x41e760, u32, int)(0);   /* sound_playMenu */
		GAME_VAR(int, 0x4db508) = 0;
		return r;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)))
		return CALL(0x4034e0);   /* room_4034e0 */
	u32 r = input_justPressed(GAME_VAR(int, 0x4e0ce0));
	if (r)
		return CALL(0x403530);   /* room_403530 */
	return r;
}

/* 0x435a40: leaving the game room: the room's name sent to the others (message 0x19, 0x65 bytes), a pause of half a
   second, back to the main menu (state 300), the connection closed, the mech reloaded from the profile */
u32 (room_leaveGame)(void)
{
	strcpy(GAME_VAR(char *, 0xa0b33c), (const char *)0x9dd570);
	GAME_CDECL(0x4521c0, int, int, int)(0x19, 0x65);   /* net_send */
	IMPORT(0x4a9110, void, u32)(500);                   /* Sleep */
	GAME_CDECL(0x441250, void, int)(4);                 /* set_680370_441250 */
	GAME_VAR(int, 0x67ef20) = 300;
	GAME_CDECL(0x48b420, void, void)();                 /* nullsub_48b420 */
	GAME_CDECL(0x451e60, void, void)();                 /* net_disconnect */
	GAME_VAR(int, 0x9dd84c) = 0;
	return CALL(0x4463a0);                              /* FUN_004463a0 */
}
