/* resets.c: input and screen state put back to its start: the key tables, the chat line's mode, the network
   buffers, the map-select list, the message box. */
#include "../game.h"
#include <string.h>

/* 0x431590: no key down (the 256 key states at 0x4d1a98), the key repeat delay 5, no input line */
void (input_resetKeys)(void)
{
	memset((void *)OBJ(g_keySeen), 0, 0x100 * 4);
	(*(u32 *)&g_menuFade) = 0x40a00000;   /* 5.0 */
	g_typedLength = 0;
	g_chatLength = 0;
}

/* 0x401780: the second key table (0x4d1fc4) and its state cleared */
void (input_clearKeyTable2)(void)
{
	g_unusedKeyTable2Flags = 0x8000;
	memset((void *)OBJ(g_keyTable2), 0, 0x100 * 4);
	g_unusedKeyTable2Word1 = 0;
	g_unusedKeyTable2Word0 = 0;
	g_unusedKeyTable2Word2 = 0;
}

/* 0x4515d0: the two 50-byte network buffers and their lengths cleared */
void (net_clearBuffers)(void)
{
	memset((void *)OBJ(g_tcpDns), 0, 0xc * 4 + 2);
	memset((void *)OBJ(g_ladderDns), 0, 0xc * 4 + 2);
	g_lobbyTcpPort = 0;
	g_ladderPort = 0;
}

/* 0x440df0: every map of the map-select list out (g_fileList's flags) */
void (mapSelect_allOut)(void)
{
	for (FileEntry *p = g_fileList; p < g_fileList + 1024; p++)
		p->flag = 0;
	g_replayWrap = 1;
	g_unusedMainMenuWord = 0;
	g_replayRandomOrder = 0;
}

/* 0x445e10: a click (either button) closes the message box */
void (messageBox_clickClose)(void)
{
	if (g_keyEnter) {
		(*(int *)&g_cursorBlink) = 0;
		g_dialogPending = 0;
	}
	if (g_mouseClick) {
		(*(int *)&g_cursorBlink) = 0;
		g_dialogPending = 0;
	}
}

/* 0x433610: the rank reply taken (message 29, received at 0xa052c0): the rank (+0x16), 0 when out of the first 1000 (byte +1 set), into both copies of the pilot's record; the notice flags cleared */
void (account_takeRank)(void)
{
	int v = g_outOfRank != 1 ? g_receivedRank : 0;
	g_pilotRank = v;
	g_accountRank = v;
	g_netNoticeIn = 0;
	g_accountNotice = 0;
	g_roomAwaitingServer = 0;
}
