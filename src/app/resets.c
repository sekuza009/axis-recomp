/* resets.c: input and screen state put back to its start: the key tables, the chat line's mode, the network
   buffers, the replay selection list, the message box. */
#include "../game.h"
#include <string.h>

/* 0x431590: the 256 key press latches (g_keySeen) cleared (a key still held then counts as just pressed
   again), the menu keys held off (g_menuKeyGuard 5), the input line emptied (g_lineMaxLength, g_chatLength 0) */
void (input_resetKeys)(void)
{
	memset((void *)OBJ(g_keySeen), 0, 0x100 * 4);
	(*(u32 *)&g_menuKeyGuard) = 0x40a00000;   /* 5.0 */
	g_lineMaxLength = 0;
	g_chatLength = 0;
}

/* 0x401780: the second key table (g_keyTable2) and its state cleared */
void (input_clearKeyTable2)(void)
{
	g_unusedKeyTable2Flags = 0x8000;
	memset((void *)OBJ(g_keyTable2), 0, 0x100 * 4);
	g_unusedKeyTable2Word1 = 0;
	g_unusedKeyTable2Word0 = 0;
	g_unusedKeyTable2Word2 = 0;
}

/* 0x4515d0: the server settings cleared: the game-list and ladder servers' names (50 bytes each) and ports */
void (net_clearServerSettings)(void)
{
	memset((void *)OBJ(g_tcpDns), 0, 0xc * 4 + 2);
	memset((void *)OBJ(g_ladderDns), 0, 0xc * 4 + 2);
	g_lobbyTcpPort = 0;
	g_ladderPort = 0;
}

/* 0x440df0: every replay of the replay selection list out (g_replayList's picked flags, 1024 entries)
   and the show's options back to their defaults (g_replayWrap 1, g_replayRandomOrder 0; g_unusedMainMenuWord 0) */
void (replaySelect_allOut)(void)
{
	for (FileEntry *p = g_replayList; p < g_replayList + 1024; p++)
		p->picked = 0;
	g_replayWrap = 1;
	g_unusedMainMenuWord = 0;
	g_replayRandomOrder = 0;
}

/* 0x445e10: a right or left click closes the message box */
void (messageBox_clickClose)(void)
{
	if (g_rightClick) {
		(*(int *)&g_menuRepeatClock) = 0;
		g_dialogPending = 0;
	}
	if (g_mouseClick) {
		(*(int *)&g_menuRepeatClock) = 0;
		g_dialogPending = 0;
	}
}

/* 0x433610: the rank reply taken (message 29, received at g_rankReplyCode): the rank (+0x16), 0 when out of the first 1000 (byte +1 set), into both copies of the pilot's record; the notice flags cleared */
void (account_takeRank)(void)
{
	int v = g_outOfRank != 1 ? g_receivedRank : 0;
	g_pilotRank = v;
	g_accountRank = v;
	g_rankReplyIn = 0;
	g_accountNotice = 0;
	g_roomAwaitingServer = 0;
}
