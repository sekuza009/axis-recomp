/* menu_init.c: front-end tables put to their start: colours, the camera points, the arena option texts, the
   skirmish player rows, the network state. */
#include "../game.h"
#include <string.h>

/* 0x430ab0: seven RGBA colours, each component 1.0 or 0 */
void (menu_initColours)(void)
{
	static const u8 on[28] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1 };
	for (int k = 0; k < 28; k++)
		GAME_VAR(u32, 0x9dada0 + k * 4) = on[k] ? 0x3f800000 : 0;
}

/* 0x40e510: three camera points (0, 300, 0), (0, -500, 0), (0, 350, 0) (16 bytes apart, the fourth word kept) */
void (armc_initCameraPoints)(void)
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
void (arena_initOptionTexts)(void)
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
void (skirmish_clearPlayerRows)(void)
{
	g_missionCount = 0;
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
void (net_resetState)(void)
{
	GAME_VAR(int, 0x9f93c8) = 0;
	g_resultMessage = 0;
	GAME_VAR(int, 0x9f93cc) = 0;
	g_hostResultFlag = 0;
	GAME_VAR(int, 0x9f93d0) = 0;
	GAME_VAR(int, 0x9f9420) = 0;
	memset((void *)0x9f9428, 0, 0x103 * 4);
	GAME_VAR(int, 0x9f93d4) = 0;
	g_netClaimedSlot = 0;
	GAME_VAR(int, 0x9f93c8) = 1;
	g_resultMessage = 2;
	g_hostResultFlag = 0;
	g_netHostGone = 0;
	GAME_VAR(int, 0x9f9420) = 6;
	GAME_VAR(int, 0x9f9428) = 7;
}

/* 0x42f8e0: the key repeat records (four of 0x2c bytes, at 0x4df918 and again at 0x9da328): delay 4, then two rows of
   five values from the defaults at 0x5b1cfc */
void (menu_initKeyRepeat)(void)
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

/* 0x433360: the menu camera's five target points and look-at points (all at the camera's height), the home point
   from where the camera is now */
void (menuCamera_initPoints)(void)
{
	static const u32 point[][2] = {
		{ 0x4df870, 0x41a00000 }, { 0x4df874, 0xc1200000 }, { 0x76d388, 0xc28c0000 }, { 0x76d38c, 0x425c0000 },
		{ 0x4df880, 0x41a00000 }, { 0x4df884, 0 }, { 0x76d398, 0xc28c0000 }, { 0x76d39c, 0 },
		{ 0x4df890, 0x41a00000 }, { 0x4df894, 0x41200000 }, { 0x76d3a8, 0xc28c0000 }, { 0x76d3ac, 0xc25c0000 },
		{ 0x4df8a0, 0xc1a00000 }, { 0x4df8a4, 0xc1200000 }, { 0x76d3b8, 0x428c0000 }, { 0x76d3bc, 0x425c0000 },
		{ 0x4df8b0, 0xc1a00000 }, { 0x4df8b4, 0 }, { 0x76d3c8, 0x428c0000 }, { 0x76d3cc, 0 } };   /* (+-20, +-10), (-+70, +-55) */
	int z = g_menuCameraHeight;
	for (int i = 0; i < 5; i++) {
		GAME_VAR(int, 0x4df878 + i * 0x10) = z;
		GAME_VAR(int, 0x76d390 + i * 0x10) = z;
	}
	g_menuCameraX = (*(int *)&g_menuCameraPos);
	g_menuCameraY = (*(int *)&g_armcCamHeight);
	g_menuCameraZ = (*(int *)&g_armcCamDistance);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = g_menuCameraHeight;
	for (unsigned i = 0; i < sizeof point / sizeof point[0]; i++)
		GAME_VAR(u32, point[i][0]) = point[i][1];
	g_menuLookAtX = lx;
	g_menuLookAtY = ly;
	g_menuLookAtZ = lz;
	g_roomAwaitingServer = 0;
}

/* 0x440d70: the main menu's replay list opened: its state, a dialog open, its frame, the 1024 records (0x44 bytes
   from 0x9dda88) cleared, the layout and the replay files listed. Returns the listing's eax */
u32 (replayList_open)(void)
{
	g_mapSelectCount = 0;
	g_mapSelectFirst = 0;
	GAME_VAR(int, 0x9dd944) = 0;
	GAME_VAR(int, 0x9eea88) = 0;
	g_dialogOpen = 1;
	GAME_VAR(int, 0x9dd908) = 0x50;
	GAME_VAR(int, 0x9dd90c) = 0x28;
	GAME_VAR(int, 0x9dd910) = 0x230;
	GAME_VAR(int, 0x9dd914) = 0x1b8;
	for (u32 r = 0x9ddac8; r < 0x9eeac8; r += 0x44)
		memset((void *)(r - 0x40), 0, 0x44);
	GAME_CDECL(0x440a20, void, void)();          /* mapSelect_layout: the layout */
	return GAME_CDECL(0x440c60, u32, void)();    /* autoplay_listFiles */
}

/* 0x430bf0: the front end's start-up: the chat history cleared, then six steps (colours; three table builders, the key
   repeat records, the menu's records), each counted on the progress bar (0x4dda34), drawn, and followed by a 2-second
   wait. Returns the last progress drawing's eax */
u32 (frontEnd_startUp)(void)
{
	static const u32 steps[5] = { 0x42f2b0, 0x42f500, 0x42f690, 0x42f8e0, 0x430bd0 };
	memset((void *)0x67ef38, 0, 0x300 * 4);
	GAME_CDECL(0x430ab0, void, void)();   /* menu_initColours: the colours */
	u32 r = 0;
	for (int k = 0; ; k++) {
		g_loadStep++;
		r = GAME_CDECL(0x41f100, u32, void)();   /* frontEnd_drawProgress: the progress drawn */
		if (k == 5)
			break;
		GAME_CDECL(0x41e730, void, double)(2.0);   /* timer_waitFrames: wait */
		GAME_CDECL(steps[k], void, void)();
	}
	return r;
}
