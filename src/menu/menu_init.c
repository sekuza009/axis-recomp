/* menu_init.c: front-end tables put to their start: colours, the camera points, the arena option texts, the
   skirmish player rows, the network state. */
#include "../game.h"
#include <string.h>

/* 0x430ab0: seven RGBA colours, each component 1.0 or 0 */
void (intro_430ab0)(void)
{
	static const u8 on[28] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1 };
	for (int k = 0; k < 28; k++)
		GAME_VAR(u32, 0x9dada0 + k * 4) = on[k] ? 0x3f800000 : 0;
}

/* 0x40e510: three camera points (0, 300, 0), (0, -500, 0), (0, 350, 0) (16 bytes apart, the fourth word kept) */
void (menu_40e510)(void)
{
	for (u32 p = 0x4dca30; p < 0x4dca90; p += 0x10) {
		GAME_VAR(int, p) = 0;
		GAME_VAR(int, p + 4) = 0;
		GAME_VAR(int, p + 8) = 0;
	}
	GAME_VAR(u32, 0x4dca34) = 0x43960000;   /* 300 */
	GAME_VAR(u32, 0x4dca64) = 0xc3fa0000;   /* -500 */
	GAME_VAR(u32, 0x4dca84) = 0x43af0000;   /* 350 */
}

/* 0x42bc00: the arena option texts (0x80-byte strings of the text table) copied into the menu's 0x14-byte fields */
void (arena_42bc00)(void)
{
	static const u32 copies[7][2] = { { 0x4db860, 0x75baa4 }, { 0x4db874, 0x75bb24 }, { 0x4db888, 0x75bba4 },
	                                  { 0x4dbb14, 0x75bc24 }, { 0x4dbb28, 0x75bca4 }, { 0x4dbba4, 0x75bc24 },
	                                  { 0x4dbbb8, 0x75bca4 } };
	for (int k = 0; k < 7; k++)
		strcpy((char *)copies[k][0], (const char *)copies[k][1]);
	for (u32 s = 0x75c224, d = 0x4db8d8; s < 0x75c9a4; s += 0x80, d += 0x14)
		strcpy((char *)d, (const char *)s);
}

/* 0x443570: the skirmish list's 32 player rows (0xfc bytes: a 0x40-byte name, 0xa0 bytes of settings, the team
   -1) emptied */
void (skirmish_443570)(void)
{
	GAME_VAR(int, 0x9ef2c0) = 0;
	GAME_VAR(int, 0x9ef2c4) = 0;
	GAME_VAR(int, 0x9ef2c8) = 0;
	GAME_VAR(int, 0x9ef2cc) = 0;
	for (u32 e = 0x9ef314; e < 0x9f109c; e += 0xfc) {
		memset((void *)(e - 0x40), 0, 0x40);
		memset((void *)e, 0, 0xa0);
		GAME_VAR(int, e - 0x44) = 0;
		GAME_VAR(int, e + 0xa0) = 0;
		GAME_VAR(int, e + 0xa4) = 0;
		GAME_VAR(int, e + 0xac) = -1;
		GAME_VAR(int, e + 0xa8) = 0;
		GAME_VAR(int, e + 0xb0) = 0;
	}
}

/* 0x4509e0: the network state's start (the cleared values then set: 1, 2, 0, 6 and 7) */
void (arena_4509e0)(void)
{
	GAME_VAR(int, 0x9f93c8) = 0;
	GAME_VAR(int, 0x9f9418) = 0;
	GAME_VAR(int, 0x9f93cc) = 0;
	GAME_VAR(int, 0x9f941c) = 0;
	GAME_VAR(int, 0x9f93d0) = 0;
	GAME_VAR(int, 0x9f9420) = 0;
	memset((void *)0x9f9428, 0, 0x103 * 4);
	GAME_VAR(int, 0x9f93d4) = 0;
	GAME_VAR(int, 0x9f9424) = 0;
	GAME_VAR(int, 0x9f93c8) = 1;
	GAME_VAR(int, 0x9f9418) = 2;
	GAME_VAR(int, 0x9f941c) = 0;
	GAME_VAR(int, 0x9fd94c) = 0;
	GAME_VAR(int, 0x9f9420) = 6;
	GAME_VAR(int, 0x9f9428) = 7;
}

/* 0x42f8e0: the key repeat records (four of 0x2c bytes, at 0x4df918 and again at 0x9da328): delay 4, then two rows of
   five values from the defaults at 0x5b1cfc */
void (intro_42f8e0)(void)
{
	for (int o = 0; o < 0xb0; o += 0x2c) {
		GAME_VAR(int, 0x4df918 + o) = 4;
		GAME_VAR(int, 0x9da328 + o) = 4;
		for (int j = 0; j < 20; j += 4) {
			GAME_VAR(int, 0x4df91c + o + j) = GAME_VAR(int, 0x5b1cfc + o + j);
			GAME_VAR(int, 0x9da32c + o + j) = GAME_VAR(int, 0x5b1cfc + o + j);
			GAME_VAR(int, 0x4df930 + o + j) = GAME_VAR(int, 0x5b1d10 + o + j);
			GAME_VAR(int, 0x9da340 + o + j) = GAME_VAR(int, 0x5b1d10 + o + j);
		}
	}
}
