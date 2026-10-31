/* resets.c: input and screen state put back to its start: the key tables, the chat line's mode, the network
   buffers, the map-select list, the message box. */
#include "../game.h"
#include <string.h>

/* 0x431590: no key down (the 256 key states at 0x4d1a98), the key repeat delay 5, no input line */
void (input_resetKeys)(void)
{
	memset((void *)0x4d1a98, 0, 0x100 * 4);
	(*(u32 *)&g_menuFade) = 0x40a00000;   /* 5.0 */
	g_typedLength = 0;
	g_chatLength = 0;
}

/* 0x401780: the second key table (0x4d1fc4) and its state cleared */
void (input_clearKeyTable2)(void)
{
	g_unusedKeyTable2Flags = 0x8000;
	memset((void *)0x4d1fc4, 0, 0x100 * 4);
	g_unusedKeyTable2Word1 = 0;
	g_unusedKeyTable2Word0 = 0;
	g_unusedKeyTable2Word2 = 0;
}

/* 0x4515d0: the two 50-byte network buffers and their lengths cleared */
void (net_clearBuffers)(void)
{
	memset((void *)0xa0b24c, 0, 0xc * 4 + 2);
	memset((void *)0xa055fc, 0, 0xc * 4 + 2);
	g_lobbyTcpPort = 0;
	g_ladderPort = 0;
}

/* 0x440df0: every map of the map-select list out (0x44-byte entries from 0x9ddac8) */
void (mapSelect_allOut)(void)
{
	for (u32 p = 0x9ddac8; p < 0x9eeac8; p += 0x44)
		GAME_VAR(int, p) = 0;
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

/* 0x433610: the room screen's selection from the joined session (none unless its byte 0xa052c1 is 1) */
void (room_selectJoinedSession)(void)
{
	int v = g_joinedSessionFlag != 1 ? g_receivedClan : 0;
	g_pilotClan = v;
	g_accountClan = v;
	g_netNoticeIn = 0;
	g_accountNotice = 0;
	g_roomAwaitingServer = 0;
}
