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

/* 0x407270: the create screen's quit dialog clicks, only with none of its other panels (and no dialog) open: as
   lobby_406bd0. Returns what the original leaves in eax */
u32 (lobby_407270)(void)
{
	static const u32 panels[5] = { 0x4dbab0, 0x4db850, 0x4db518, 0x4dbacc, 0x90d1c4 };
	for (int k = 0; k < 5; k++)
		if (GAME_VAR(int, panels[k]))
			return GAME_VAR(u32, panels[k]);
	if (GAME_VAR(int, 0x4ded8c))
		GAME_VAR(int, 0x907b2c) = 0;
	if (!g_mouseClick)
		return 0;
	int button = GAME_CDECL(0x4045a0, int, int, int)(g_mouseX, g_mouseY);
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
u32 (lobby_405140)(void) { return settings_store((u8 *)0x4db528, (u8 *)0x4ded20, 0x42d730); }
/* 0x433640: the room's settings kept (0x5b1b30) and written to the registry (reg_writeCharacterSettings) */
u32 (room_433640)(void) { return settings_store((u8 *)0x4df9c8, (u8 *)0x5b1b30, 0x432400); }

/* 0x40d390: the create-arena screen drawn: the tunnel, then (modes other than 0 and 1, not on sub-screen 5) the
   dialog's frame if one is open, else the settings kept in range (players 0 .. 16 else 8, the two limits at most 250
   else 30, the map 0 .. 14 else 0), the screen, the map list when open, the options panel when shown. Returns what
   the original leaves in eax */
u32 (lobbyCreate_draw)(void)
{
	CALL(0x4091b0);   /* arena_4091b0: the tunnel */
	int mode = GAME_VAR(int, 0x4dbb3c);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x4db51c) == 5)
		return (u32)mode;
	if (g_dialogOpen)
		return GAME_CDECL(0x428c30, u32, int, int, int, int)(GAME_VAR(int, 0x4dbb00), GAME_VAR(int, 0x4dbb04),
		                                                     GAME_VAR(int, 0x4dbb08), GAME_VAR(int, 0x4dbb0c));   /* menu_drawFrame */
	signed char players = GAME_VAR(signed char, 0x4ded41);
	if (players < 0 || players > 0x10)
		GAME_VAR(u8, 0x4ded41) = 8;
	if (GAME_VAR(u8, 0x4ded44) > 0xfa)
		GAME_VAR(u8, 0x4ded44) = 0x1e;
	if (GAME_VAR(u8, 0x4ded45) > 0xfa)
		GAME_VAR(u8, 0x4ded45) = 0x1e;
	signed char map = GAME_VAR(signed char, 0x4ded43);
	if (map < 0 || map > 0xe)
		GAME_VAR(u8, 0x4ded43) = 0;
	CALL(0x40b750);   /* arena_createDraw */
	if (GAME_VAR(int, 0x4db508) == 1)
		CALL(0x4038e0);   /* arena_4038e0: the map list */
	if (!GAME_VAR(int, 0x4dba88))
		return 0;
	return CALL(0x405b80);   /* arena_405b80 */
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
	GAME_VAR(int, 0x9da3e0) = GAME_VAR(signed char, 0x4ded42);
	GAME_VAR(int, 0x9dad94) = GAME_VAR(signed char, 0x4ded40);
	memcpy((void *)0x67fb44, (const void *)0x4ded20, 32);
	GAME_VAR(int, 0x76d368) = GAME_VAR(signed char, 0x4ded43);
	GAME_VAR(u32, 0x4df8e8) = limits & 0xff;
	GAME_VAR(u32, 0x76d408) = (limits >> 8) & 0xff;
	GAME_VAR(int, 0x4dbb3c) = 0;
	GAME_VAR(int, 0x4dbbf4) = 1;
	GAME_VAR(int, 0x4db55c) = 0;
	return limits;
}

/* 0x406a60: the lobby player screen's clicks (mode 2, no dialog or list open): a right click goes back; buttons: 0 the
   name field, 2 the ARM CENTER, 3 the profile's record kept, 4 back, 5 the default name. Returns what the original
   leaves in eax */
u32 (lobby_406a60)(void)
{
	int mode = GAME_VAR(int, 0x4dbb3c);
	if (mode == 1 || mode == 0 || g_dialogOpen || GAME_VAR(int, 0x4dbbd0))
		return (u32)mode;
	if (GAME_VAR(int, 0x4ded8c)) {
		GAME_VAR(int, 0x4dbb3c) = 0;
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
		r = CALL(0x4050a0);      /* FUN_004050a0 */
		GAME_VAR(int, 0x4dbb3c) = 0;
		return r;
	case 4:
		r = GAME_CDECL(0x41e760, u32, int)(0);
		GAME_VAR(int, 0x4dbb3c) = 0;
		return r;
	case 5:
		sound_playMenu(0);
		return CALL(0x4050f0);   /* cfg_defaultPlayerName */
	}
	return button;
}

/* 0x405690: arena session `session` joined: its record (0x4a bytes from 0x9087c0) gives the colours shown
   (+0x2d, +0x2e) and the join's argument (+0); a refused join shows message 0x36 (full) or 0x35. Joined, the music
   stops and the session's settings are taken: the 32-byte rules (+4), +0x24, +0x25, +0x2c, the colours. Returns the
   message's eax, or the colour +0x2e */
u32 (arena_405690)(int session)
{
	const u8 *rec = (const u8 *)(0x9087c0 + session * 0x4a);
	GAME_VAR(int, 0x4dbbec) = 0;
	GAME_VAR(int, 0x4dbbf0) = 0;
	GAME_VAR(u8, 0x4ded45) = GAME_VAR(u8, 0x4db54d) = rec[0x2e];
	GAME_VAR(u8, 0x4ded44) = GAME_VAR(u8, 0x4db54c) = rec[0x2d];
	int r = GAME_CDECL(0x453180, int, int, u32, const char *, int)(session, *(const u32 *)rec, (const char *)0x4dedb0,
	                                                               GAME_VAR(int, 0x4dedd0));   /* arena_453180: join */
	if (r != 0x1f4)
		return GAME_CDECL(0x41ee40, u32, int)(r == 0x1f5 ? 0x36 : 0x35);   /* the message */
	music_shutdown();
	GAME_VAR(int, 0x9dad94) = (signed char)rec[0x25];
	memcpy((void *)0x67fb44, rec + 4, 32);
	GAME_VAR(int, 0x9da3e0) = (signed char)rec[0x24];
	GAME_VAR(int, 0x4dbb3c) = 0;
	GAME_VAR(int, 0x4db8b4) = 0;
	GAME_VAR(int, 0x67ef14) = 1;
	GAME_VAR(int, 0x67ef04) = 2;
	GAME_VAR(int, 0x76d368) = (signed char)rec[0x2c];
	GAME_VAR(int, 0x4df8e8) = rec[0x2d];
	return GAME_VAR(int, 0x76d408) = rec[0x2e];
}

/* ---- a menu key: the key bound at `binding` was just pressed (the confirm sound played then) ---- */
static int key_hit(u32 binding)
{
	if (!input_justPressed(GAME_VAR(int, binding)))
		return 0;
	sound_playMenu(0);
	return 1;
}
/* back to the main menu; returns set_680370_441250's eax (4) */
static u32 to_main_menu(void)
{
	u32 r = GAME_CDECL(0x441250, u32, int)(4);   /* set_680370_441250: keys blocked */
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
u32 (lobby_406950)(void)
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
	int right = GAME_VAR(int, 0x4ded8c);
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
	if (GAME_VAR(int, 0x4dbbd0)) {
		if (GAME_VAR(int, 0x68039c))
			return page;
		const char *typed = (const char *)0x9dc92c;
		u32 length = strlen(typed);
		GAME_VAR(int, 0x4dbbd0) = 0;
		if (!length)
			return 0;
		memset((void *)0x4db560, 0, 32);
		strcpy((char *)0x4db560, typed);
		return length + 1;
	}
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		GAME_VAR(int, 0x4dbb3c) = 0;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e1510))) {
		sound_playMenu(0);
		GAME_CDECL(0x4050a0, void, void)();
		GAME_VAR(int, 0x4dbb3c) = 0;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0ce0))) {
		sound_playMenu(0);
		return GAME_CDECL(0x4050f0, u32, void)();   /* cfg_defaultPlayerName */
	}
	if (!input_justPressed(g_keyBack))
		return 0;
	u32 r = GAME_CDECL(0x41e760, u32, int)(0);      /* sound_playMenu */
	GAME_VAR(int, 0x4dbb3c) = 0;
	return r;
}
