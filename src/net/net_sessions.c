/* net_sessions.c: the network games received from the game's own TCP servers (the lobby's arena records,
   g_serverList, and the game server's rooms, g_roomList, each with its ping) merged into the session list the
   arena lobby and the game room show: g_sessionList's SessionEntrys, their count in g_gameCount. */
#include "../game.h"
#include <string.h>

/* one screen's received games: listCount the address of its listed count (nonzero: entries to merge); records of stride bytes from base (s = a record's key
   byte, its rotation flag: its map, most players, players, game mode, frag and time limits the six bytes before, its
   lock after 9 and password after 10; its name at s + nameOff, its address at s + addressOff); total sums the entries'
   player counts; the three words of clear are cleared when nothing more is coming (g_netListDone 0) */
typedef struct {
	u32 listCount, base;
	int stride, nameOff, addressOff;
	u32 total;
	u32 clear[3];
} Received;

static void merge(const Received *g)
{
	if (GAME_VAR(int, g->listCount)) {
		for (int i = 0; i < g_serverPingCount; i++) {
			if ((*(int *)&((u32 *)g_serverPinged)[i]) != 1)   /* not new */
				continue;
			const u8 *s = (const u8 *)(RELOC(g->base) + i * g->stride);
			int ping = g_serverPing[i];
			if (ping > 0) {
				int k = g_gameCount;
				SessionEntry *e = &g_sessionList[k];
				memset(e->name, 0, 32);
				strcpy(e->name, (const char *)s + g->nameOff);
				u8 map = s[-6];
				e->rotation = s[0];
				e->map = map;
				e->gameMode = s[-3];
				e->maxPlayers = s[-5];
				e->players = s[-4];
				e->fragLimit = s[-2];
				e->timeLimit = s[-1];
				e->ping = ping;
				e->locked = s[9];
				memset(e->password, 0, 8);
				strcpy(e->password, (const char *)s + 0xa);
				memset(e->address, 0, 16);
				strcpy(e->address, (const char *)s + g->addressOff);
				GAME_VAR(int, g->total) += e->players;
				g_gameCount = k + 1;
				sessionList_sort();   /* the list sorted again */
			}
			(*(int *)&((u32 *)g_serverPinged)[i]) = 0;
			g_listAnswered++;
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
	static const Received room = { ADDR(g_roomListCount), (OBJ(g_roomList) + offsetof(RoomRecord, rotation)), sizeof(RoomRecord), (int)offsetof(RoomRecord, name) - (int)offsetof(RoomRecord, rotation), (int)offsetof(RoomRecord, address) - (int)offsetof(RoomRecord, rotation), ADDR(g_roomListPlayers), { ADDR(g_roomSearching), ADDR(g_roomSearchAnswerIn), ADDR(g_roomRefreshing) } };
	merge(&room);
}

/* 0x406640: the arena lobby's (0x5b-byte records) */
void (arena_mergeReceivedSessions)(void)
{
	static const Received arena = { ADDR(g_serverListCount), (OBJ(g_serverList) + offsetof(ArenaRecord, rotation)), sizeof(ArenaRecord), (int)offsetof(ArenaRecord, name) - (int)offsetof(ArenaRecord, rotation), (int)offsetof(ArenaRecord, address) - (int)offsetof(ArenaRecord, rotation), ADDR(g_arenaListPlayers), { ADDR(g_lobbySearching), ADDR(g_serverAnswerIn), ADDR(g_lobbyRefreshing) } };
	merge(&arena);
}

/* 0x4065e0: the session list sorted by ping (bubble sort, whole entries swapped) */
void (sessionList_sort)(void)
{
	for (int pass = 0; g_gameCount - 1 > 0; ) {
		int swapped = 0;
		for (int j = 0; j < g_gameCount - 1; j++) {
			SessionEntry *e = &g_sessionList[j];
			if (e[0].ping > e[1].ping) {
				sessionList_swap(&e[0], &e[1]);
				swapped = 1;
			}
		}
		if (!swapped || ++pass >= g_gameCount - 1)
			break;
	}
}

/* 0x406810: the arena list rebuilt from the sessions DirectPlay found (net_getSession), then sorted */
void (arenaList_rebuild)(void)
{
	int n = net_sessionCount();
	g_gameCount = n;
	g_listAnswered = n;
	for (int i = 0; i < g_gameCount; i++) {
		const SessionDesc *s = (const SessionDesc *)net_getSession(i);
		SessionEntry *e = &g_sessionList[i];
		memset(e->name, 0, 32);
		strcpy(e->name, s->name);
		e->guid = s->guid;
		e->rotation = s->rotation;
		e->map = s->map;
		e->gameMode = s->gameMode;
		e->maxPlayers = s->maxPlayers;
		e->players = (signed char)s->players;
		e->fragLimit = s->fragLimit;
		e->timeLimit = s->timeLimit;
		e->ping = 0;
	}
	g_arenaLanListBuilt = 1;
	g_pickedGame = 0;
	g_arenaServerList = 0;
	sessionList_sort();
}
