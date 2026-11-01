/* net_sessions.c: the network games received (DirectPlay's session enumeration) merged into the session list the
   arena lobby and the game room show: 0x4a-byte entries from 0x9087c4, their count in 0x67ef30. */
#include "../game.h"
#include <string.h>

#define SESSION(k) (g_gameList + (k) * 0x4a)

/* one screen's received games: flag says new ones arrived; records of stride bytes from base (s = a record's key
   byte: its name at s + nameOff, its flags around s, a second string at s + str2Off); total sums the entries'
   player counts; the three words of clear are cleared when nothing more is coming (0xa0d7a0 0) */
typedef struct {
	u32 flag, base;
	int stride, nameOff, str2Off;
	u32 total;
	u32 clear[3];
} Received;

static void merge(const Received *g)
{
	if (GAME_VAR(int, g->flag)) {
		for (int i = 0; i < g_serverPingCount; i++) {
			if (GAME_VAR(int, 0xa0bb14 + i * 4) != 1)   /* not new */
				continue;
			const u8 *s = (const u8 *)(RELOC(g->base) + i * g->stride);
			int players = GAME_VAR(int, 0xa0d384 + i * 4);
			if (players > 0) {
				int k = g_gameCount;
				u8 *e = SESSION(k);
				memset(e, 0, 32);
				strcpy((char *)e, (const char *)s + g->nameOff);
				u8 b6 = s[-6];
				e[0x20] = s[0];
				e[0x21] = b6;
				e[0x28] = s[-3];
				e[0x22] = s[-5];
				e[0x23] = s[-4];
				e[0x29] = s[-2];
				e[0x2a] = s[-1];
				GAME_VAR(int, e + 0x24) = players;
				e[0x43] = s[9];
				GAME_VAR(int, e + 0x3b) = 0;
				GAME_VAR(int, e + 0x3f) = 0;
				strcpy((char *)e + 0x3b, (const char *)s + 0xa);
				memset(e + 0x2b, 0, 16);
				strcpy((char *)e + 0x2b, (const char *)s + g->str2Off);
				GAME_VAR(int, g->total) += (signed char)e[0x23];
				g_gameCount = k + 1;
				sessionList_sort();   /* the list sorted again */
			}
			GAME_VAR(int, 0xa0bb14 + i * 4) = 0;
			g_lobbyListPage++;
		}
		if (!g_netListDone)
			return;
	}
	for (int k = 0; k < 3; k++)
		GAME_VAR(int, g->clear[k]) = 0;
}

/* 0x434ff0: the game room's (0x79-byte records) */
void (room_mergeReceivedSessions)(void)
{
	static const Received room = { ADDR(g_roomListCount), IMG(0x9fd9c7), 0x79, -0x66, -0x34, ADDR(g_roomNameSum), { ADDR(g_roomSearching), ADDR(g_roomSearchAnswerIn), ADDR(g_roomRefreshing) } };
	merge(&room);
}

/* 0x406640: the arena lobby's (0x5b-byte records) */
void (arena_mergeReceivedSessions)(void)
{
	static const Received arena = { ADDR(g_serverListCount), IMG(0xa05791), 0x5b, -0x48, -0x16, ADDR(g_arenaNameSum), { ADDR(g_lobbySearching), ADDR(g_serverAnswerIn), ADDR(g_lobbyRefreshing) } };
	merge(&arena);
}

/* 0x4065e0: the session list sorted by player count (+0x24, bubble sort). The original swaps 0x4a-byte blocks that
   start 4 bytes before each record (from 0x9087c0): a record's last 4 bytes travel with the record after it */
void (sessionList_sort)(void)
{
	for (int pass = 0; g_gameCount - 1 > 0; ) {
		int swapped = 0;
		for (int j = 0; j < g_gameCount - 1; j++) {
			u8 *e = SESSION(j);
			if (GAME_VAR(int, e + 0x24) > GAME_VAR(int, e + 0x4a + 0x24)) {
				record_swap(e - 4, e + 0x4a - 4);
				swapped = 1;
			}
		}
		if (!swapped || ++pass >= g_gameCount - 1)
			break;
	}
}

/* 0x406810: the arena list rebuilt from the session list (0x4a-byte records: name, id before it, settings), then
   sorted */
void (arenaList_rebuild)(void)
{
	int n = net_sessionCount();
	g_gameCount = n;
	g_lobbyListPage = n;
	for (int i = 0; i < g_gameCount; i++) {
		const u8 *s = (const u8 *)net_sessionValue(i);
		u8 *e = SESSION(i);
		memset(e, 0, 32);
		strcpy((char *)e, (const char *)s + 0x2e);
		GAME_VAR(int, e - 4) = GAME_VAR(int, s);
		e[0x20] = s[0x25];
		e[0x21] = s[0x24];
		e[0x28] = s[0x27];
		e[0x22] = s[0x26];
		e[0x23] = s[0x2a];
		e[0x29] = s[0x28];
		e[0x2a] = s[0x29];
		GAME_VAR(int, e + 0x24) = 0;
	}
	g_arenaHaveList = 1;
	g_localPlayer = 0;
	g_arenaListFull = 0;
	sessionList_sort();
}
