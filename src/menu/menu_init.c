/* menu_init.c: front-end tables put to their start: colours, the camera points, the arena option texts, the
   skirmish player rows, the network state. */
#include "../game.h"
#include <string.h>

/* 0x430ab0: seven RGBA colours, each component 1.0 or 0 */
void (menu_initColours)(void)
{
	static const u8 on[28] = { 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1 };
	for (int k = 0; k < 28; k++)
		GAME_VAR(u32, OBJ(g_codeColours) + k * 4) = on[k] ? 0x3f800000 : 0;
}

/* 0x40e510: three camera points (0, 300, 0), (0, -500, 0), (0, 350, 0) (16 bytes apart, the fourth word kept) */
void (armc_initCameraPoints)(void)
{
	for (int *p = (int *)OBJ(g_armcViewPoints); p < (int *)OBJ(g_armcViewPoints) + 6 * 4; p += 4)
		p[0] = p[1] = p[2] = 0;
	g_armcViewPoint0Y = 0x43960000;   /* 300 */
	g_armcViewPoint3Y = 0xc3fa0000;   /* -500 */
	g_armcViewPoint5Y = 0x43af0000;   /* 350 */
}

/* 0x42bc00: the arena option texts (0x80-byte strings of the text table) copied into the menu's 0x14-byte fields */
void (arena_initOptionTexts)(void)
{
	static const u32 copies[7][2] = { { OBJ(g_teamNames), MSG(441, "RED") }, { (OBJ(g_teamNames) + 0x14), MSG(442, "BLUE") }, { (OBJ(g_teamNames) + 0x28), MSG(443, "YELLOW") },
	                                  { OBJ(g_arenaOnOff), MSG(444, "OFF") }, { (OBJ(g_arenaOnOff) + 0x14), MSG(445, "ON") }, { OBJ(g_arenaOnOff2), MSG(444, "OFF") },
	                                  { (OBJ(g_arenaOnOff2) + 0x14), MSG(445, "ON") } };
	for (int k = 0; k < 7; k++)
		strcpy((char *)RELOC(copies[k][0]), (const char *)RELOC(copies[k][1]));
	for (u32 s = MSG(456, "DM"), d = OBJ(g_gameTypeNames); s < MSG(471, "DEATH MATCH"); s += 0x80, d += 0x14)
		strcpy((char *)RELOC(d), (const char *)RELOC(s));
}

/* 0x443570: the mission list's 30 entries (g_missions) emptied (valueF0 -1) */
void (skirmish_clearPlayerRows)(void)
{
	g_missionCount = 0;
	g_misHeader1 = 0;
	g_misHeader2 = 0;
	g_misHeader3 = 0;
	for (Mission *e = g_missions; e < g_missions + 30; e++) {
		memset(e->name, 0, 0x40);
		memset((u8 *)e + offsetof(Mission, title), 0, sizeof e->title + sizeof e->briefing);
		e->id = 0;
		e->number = 0;
		e->valueE8 = 0;
		e->valueF0 = -1;
		e->result = 0;
		e->blockSize = 0;
	}
}

/* 0x4509e0: the network state's start (the cleared values then set: 1, 2, 0, 6 and 7) */
void (net_resetState)(void)
{
	g_netChatMessageKind = 0;
	g_resultMessage = 0;
	g_netChatMessageWord1 = 0;
	g_hostResultFlag = 0;
	g_netChatMessageWord2 = 0;
	g_netSlotMessageKind = 0;
	memset((void *)ADDR(g_netPacketMessageKind), 0, 0x103 * 4);
	g_netChatMessageText = 0;
	g_netClaimedSlot = 0;
	g_netChatMessageKind = 1;
	g_resultMessage = 2;
	g_hostResultFlag = 0;
	g_netHostGone = 0;
	g_netSlotMessageKind = 6;
	g_netPacketMessageKind = 7;
}

/* 0x42f8e0: the setup top page's four button outlines (g_setupTopOutlines) and a second copy (g_outlinesCopy) from
   the lobby top menu's (g_lobbyTopOutlines): each 4 points, then its five x and five y */
void (menu_initKeyRepeat)(void)
{
	for (int o = 0; o < 0xb0; o += 0x2c) {
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

/* 0x433360: the menu camera's five target points and look-at points (all at the camera's height), the home point
   from where the camera is now */
void (menuCamera_initPoints)(void)
{
	static const u32 point[][2] = {
		{ ADDR(g_camPoint0X), 0x41a00000 }, { ADDR(g_camPoint0Y), 0xc1200000 }, { ADDR(g_camAim0X), 0xc28c0000 }, { ADDR(g_camAim0Y), 0x425c0000 },
		{ ADDR(g_camPoint1X), 0x41a00000 }, { (OBJ(g_camPoints) + 0x14), 0 }, { ADDR(g_camAim1X), 0xc28c0000 }, { ADDR(g_camAim1Y), 0 },
		{ ADDR(g_camPoint2X), 0x41a00000 }, { ADDR(g_camPoint2Y), 0x41200000 }, { ADDR(g_camAim2X), 0xc28c0000 }, { ADDR(g_camAim2Y), 0xc25c0000 },
		{ (OBJ(g_camPoints) + 0x30), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x34), 0xc1200000 }, { (OBJ(g_camAims) + 0x30), 0x428c0000 }, { (OBJ(g_camAims) + 0x34), 0x425c0000 },
		{ (OBJ(g_camPoints) + 0x40), 0xc1a00000 }, { (OBJ(g_camPoints) + 0x44), 0 }, { (OBJ(g_camAims) + 0x40), 0x428c0000 }, { (OBJ(g_camAims) + 0x44), 0 } };   /* (+-20, +-10), (-+70, +-55) */
	int z = g_menuCameraHeight;
	for (int i = 0; i < 5; i++) {
		GAME_VAR(int, (OBJ(g_camPoints) + 0x8) + i * 0x10) = z;
		GAME_VAR(int, (OBJ(g_camAims) + 0x8) + i * 0x10) = z;
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
	g_unusedReplayListWord1 = 0;
	g_unusedReplayListWord2 = 0;
	g_dialogOpen = 1;
	g_mapSelectLeft = 0x50;
	g_mapSelectTop = 0x28;
	g_mapSelectRight = 0x230;
	g_mapSelectBottom = 0x1b8;
	for (u32 r = OBJ(g_fileList) + 0x40; r < OBJ(g_fileList) + 0x40 + 1024 * 0x44; r += 0x44)
		memset((void *)(RELOC(r) - 0x40), 0, 0x44);
	mapSelect_layout();          /* mapSelect_layout: the layout */
	return autoplay_listFiles();    /* autoplay_listFiles */
}

/* 0x430bf0: the front end's start-up: the chat history cleared, then six steps (colours; three table builders, the key
   repeat records, the menu's records), each counted on the progress bar (0x4dda34), drawn, and followed by a 2-second
   wait. Returns the last progress drawing's eax */
u32 (frontEnd_startUp)(void)
{
	static const u32 steps[5] = { FN_ADDR(menu_initMainButtons, 0x42f2b0), FN_ADDR(menu_initKeyRepeatDefaults, 0x42f500), FN_ADDR(room_initMenuButtons, 0x42f690), FN_ADDR(menu_initKeyRepeat, 0x42f8e0), FN_ADDR(net_clearSlots, 0x430bd0) };
	memset((void *)OBJ(g_chatHistory), 0, 0x300 * 4);
	menu_initColours();   /* menu_initColours: the colours */
	u32 r = 0;
	for (int k = 0; ; k++) {
		g_loadStep++;
		r = GAME_FN(frontEnd_drawProgress, 0x41f100, u32, void)();   /* frontEnd_drawProgress: the progress drawn */
		if (k == 5)
			break;
		timer_waitFrames(2.0);   /* timer_waitFrames: wait */
		GAME_CDECL(steps[k], void, void)();
	}
	return r;
}
