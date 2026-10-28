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
