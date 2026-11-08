/* menu_init.c: front-end tables put to their start: colours, the camera points, the arena option texts, the mission
   list, the network state, the button outlines, the front end's start-up; also the replay list opened
   (replayList_open). */
#include "../game.h"
#include <string.h>

/* 0x430ab0: seven RGBA colours, each component 1.0 or 0 */
void (menu_initColours)(void)
{
	static const u8 on[28] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1 };
	for (int k = 0; k < 28; k++)
		GAME_VAR(u32, OBJ(g_codeColours) + k * 4) = on[k] ? 0x3f800000 : 0;
}

/* 0x40e510: ARM CENTER's six 16-byte points (g_armcViewPoints) zeroed (x, y, z; the fourth word kept), then the y of
   points 0, 3 and 5 set to 300, -500 and 350. Nothing reads the table (g_armcViewPoints: never read). Caller
   armc_open */
void (armc_initCameraPoints)(void)
{
	for (int *p = (int *)OBJ(g_armcViewPoints); p < (int *)OBJ(g_armcViewPoints) + 6 * 4; p += 4)
		p[0] = p[1] = p[2] = 0;
	(*(u32 *)&g_unusedArmcPoint0Y) = 0x43960000;   /* 300 */
	(*(u32 *)&g_unusedArmcPoint3Y) = 0xc3fa0000;   /* -500 */
	(*(u32 *)&g_unusedArmcPoint5Y) = 0x43af0000;   /* 350 */
}

/* 0x42bc00: the arena option texts (0x80-byte strings of the text table) copied into the menu's 0x14-byte fields */
void (arena_initOptionTexts)(void)
{
	static const u32 copies[7][2] = { { OBJ(g_teamNames), MSG(441, "RED") }, { (OBJ(g_teamNames) + 0x14), MSG(442, "BLUE") }, { (OBJ(g_teamNames) + 0x28), MSG(443, "YELLOW") },
	                                  { OBJ(g_arenaOnOff), MSG(444, "OFF") }, { (OBJ(g_arenaOnOff) + 0x14), MSG(445, "ON") }, { OBJ(g_rotationOnOff), MSG(444, "OFF") },
	                                  { (OBJ(g_rotationOnOff) + 0x14), MSG(445, "ON") } };
	for (int k = 0; k < 7; k++)
		strcpy((char *)RELOC(copies[k][0]), (const char *)RELOC(copies[k][1]));
	for (u32 s = MSG(456, "DM"), d = OBJ(g_gameTypeNames); s < MSG(471, "DEATH MATCH"); s += 0x80, d += 0x14)
		strcpy((char *)RELOC(d), (const char *)RELOC(s));
}

/* 0x443570: the mission list's 30 entries (g_missions) emptied (unusedF0 -1) */
void (missions_clear)(void)
{
	g_missionCount = 0;
	g_misHeader1 = 0;
	g_misHeader2 = 0;
	g_misHeader3 = 0;
	for (Mission *e = g_missions; e < g_missions + 30; e++) {
		memset(e->name, 0, 0x40);
		memset((u8 *)e + offsetof(Mission, title), 0, sizeof e->title + sizeof e->briefing);
		e->unused0 = 0;
		e->number = 0;
		e->unusedE8 = 0;
		e->unusedF0 = -1;
		e->result = 0;
		e->blockSize = 0;
	}
}

/* 0x4509e0: the network state's start (the cleared values then set: 1, 2, 0, 6 and 7) */
void (net_resetState)(void)
{
	g_netChatMessageKind = 0;
	g_netHostLeftMessageKind = 0;
	g_netChatMessageWord1 = 0;
	g_hostGoneMessageFlag = 0;
	g_netChatMessageFrom = 0;
	g_netSlotMessageKind = 0;
	memset((void *)ADDR(g_netPacketMessageKind), 0, 0x103 * 4);
	g_netChatMessageText = 0;
	g_netClaimedSlot = 0;
	g_netChatMessageKind = 1;
	g_netHostLeftMessageKind = 2;
	g_hostGoneMessageFlag = 0;
	g_netHostGone = 0;
	g_netSlotMessageKind = 6;
	g_netPacketMessageKind = 7;
}

/* 0x42f8e0: the setup top page's four button outlines (g_setupTopOutlines) and a second copy (g_outlinesCopy) from
   the lobby top menu's (g_lobbyTopOutlines): each 4 points, then its five x and five y */
void (setupTop_initOutlines)(void)
{
	for (int o = 0; o < 0xb0; o += 0x2c) {   /* four MenuOutline records (0x2c): points = 4, then x[5] (+4) and y[5] (+0x18) copied */
		GAME_VAR(int, OBJ(g_setupTopOutlines) + o) = 4;
		GAME_VAR(int, OBJ(g_outlinesCopy) + o) = 4;
		for (int j = 0; j < 20; j += 4) {
			GAME_VAR(int, OBJ(g_setupTopOutlines) + 4 + o + j) = GAME_VAR(int, OBJ(g_lobbyTopOutlines) + 4 + o + j);
			GAME_VAR(int, OBJ(g_outlinesCopy) + 4 + o + j) = GAME_VAR(int, OBJ(g_lobbyTopOutlines) + 4 + o + j);
			GAME_VAR(int, OBJ(g_setupTopOutlines) + 0x18 + o + j) = GAME_VAR(int, OBJ(g_lobbyTopOutlines) + 0x18 + o + j);
			GAME_VAR(int, OBJ(g_outlinesCopy) + 0x18 + o + j) = GAME_VAR(int, OBJ(g_lobbyTopOutlines) + 0x18 + o + j);
		}
	}
}

/* 0x433360: the game room's five menu camera target points (g_camPoints) and look-at points (g_camAims) set: x / y from a table
   ((20, -10), (20, 0), (20, 10), (-20, -10), (-20, 0); look-at x -70 / 70, y 55, 0, -55 ..), their z all the current
   look-at's z (g_menuCameraLookZ); the home eye and look-at (g_menuEyeHome*, g_menuLookHome*) from where the camera
   is now; g_roomAwaitingServer cleared. Only caller armc_cameraStep, on the way back to the game room (800) */
void (room_initCameraPoints)(void)
{
	static const u32 point[][2] = {
		{ ADDR(g_camPoint0X), 0x41a00000 }, { ADDR(g_camPoint0Y), 0xc1200000 }, { ADDR(g_camAim0X), 0xc28c0000 }, { ADDR(g_camAim0Y), 0x425c0000 },
		{ ADDR(g_camPoint1X), 0x41a00000 }, { (u32)&g_camPoints[5], 0 }, { ADDR(g_camAim1X), 0xc28c0000 }, { ADDR(g_camAim1Y), 0 },
		{ ADDR(g_camPoint2X), 0x41a00000 }, { ADDR(g_camPoint2Y), 0x41200000 }, { ADDR(g_camAim2X), 0xc28c0000 }, { ADDR(g_camAim2Y), 0xc25c0000 },
		{ (u32)&g_camPoints[12], 0xc1a00000 }, { (u32)&g_camPoints[13], 0xc1200000 }, { (u32)&g_camAims[12], 0x428c0000 }, { (u32)&g_camAims[13], 0x425c0000 },
		{ (u32)&g_camPoints[16], 0xc1a00000 }, { (u32)&g_camPoints[17], 0 }, { (u32)&g_camAims[16], 0x428c0000 }, { (u32)&g_camAims[17], 0 } };   /* (+-20, +-10), (-+70, +-55) */
	int z = (*(int *)&g_menuCameraLookZ);
	for (int i = 0; i < 5; i++) {
		GAME_VAR(int, ((u32)&g_camPoints[2]) + i * 0x10) = z;
		GAME_VAR(int, ((u32)&g_camAims[2]) + i * 0x10) = z;
	}
	(*(int *)&g_menuEyeHomeX) = (*(int *)&g_menuEyeX);
	(*(int *)&g_menuEyeHomeY) = (*(int *)&g_menuEyeY);
	(*(int *)&g_menuEyeHomeZ) = (*(int *)&g_menuEyeZ);
	int lx = (*(int *)&g_menuCameraLook), ly = (*(int *)&g_menuCameraLookY), lz = (*(int *)&g_menuCameraLookZ);
	for (unsigned i = 0; i < sizeof point / sizeof point[0]; i++)
		GAME_VAR(u32, point[i][0]) = point[i][1];
	(*(int *)&g_menuLookHomeX) = lx;
	(*(int *)&g_menuLookHomeY) = ly;
	(*(int *)&g_menuLookHomeZ) = lz;
	g_roomAwaitingServer = 0;
}

/* 0x440d70: the main menu's replay list opened: its state, a dialog open, its frame, the 1024 records (0x44 bytes
   from g_replayList) cleared, the layout and the replay files listed. Returns the listing's eax */
u32 (replayList_open)(void)
{
	g_replayFileCount = 0;
	g_replaySelectFirst = 0;
	g_unusedReplayListWord1 = 0;
	g_unusedReplayListWord2 = 0;
	g_frameOpening = 1;
	g_replaySelectLeft = 0x50;
	g_replaySelectTop = 0x28;
	g_replaySelectRight = 0x230;
	g_replaySelectBottom = 0x1b8;
	for (FileEntry *r = g_replayList; r < g_replayList + 1024; r++)
		memset(r, 0, sizeof *r);
	replaySelect_layout();          /* replaySelect_layout: the layout */
	return autoplay_listFiles();    /* autoplay_listFiles */
}

/* 0x430bf0: the front end's start-up: the input history cleared and the colours set (menu_initColours), then six
   progress steps (g_loadStep counted, frontEnd_drawProgress), each of the first five followed by a 2-frame wait
   (timer_waitFrames: 1/60 s frames) and one of menu_initMainOutlines, lobbyTop_initOutlines, room_initOutlines,
   setupTop_initOutlines, net_clearSlots. Only caller menuState100_intro. Returns the last progress drawing's eax */
u32 (frontEnd_startUp)(void)
{
	static const u32 steps[5] = { FN(menu_initMainOutlines), FN(lobbyTop_initOutlines), FN(room_initOutlines), FN(setupTop_initOutlines), FN(net_clearSlots) };
	memset((void *)OBJ(g_inputHistory), 0, 0x300 * 4);
	menu_initColours();   /* menu_initColours: the colours */
	u32 r = 0;
	for (int k = 0; ; k++) {
		g_loadStep++;
		r = frontEnd_drawProgress();   /* frontEnd_drawProgress: the progress drawn */
		if (k == 5)
			break;
		timer_waitFrames(2.0);   /* timer_waitFrames: wait */
		GAME_CDECL(steps[k], void, void)();
	}
	return r;
}
