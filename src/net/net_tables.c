/* net_tables.c: the network code's fixed tables: the 200 sessions found (g_sessionTable at 0xa0b470: SessionSlot;
   the last index in 0xa0b41c) and the sixteen player slot records (0x410 bytes from 0x9f9840). */
#include "../game.h"
#include "winsock.h"
#include <string.h>

/* 0x454110: the first free session record, -1 when all 200 are used */
int (net_findFreeSession)(void)
{
	int i = 0;
	for (const SessionSlot *p = g_sessionTable; p < g_sessionTable + 200; p++, i++)
		if (p->used == 0)
			return i;
	return -1;
}

/* 0x4532b0: session i's value, 0 when out of range or unused */
int (net_sessionValue)(int i)
{
	if (i > -1 && i <= g_dplaySessionCount && g_sessionTable[i].used)
		return (int)g_sessionTable[i].desc;
	return 0;
}

/* 0x4514a0: player slot (its low byte) taken by player id: the first ten shorts of its packet reset (two of them
   -1), the one at +0x22 the current value of 0xa0b428 */
void (net_takePlayerSlot)(u32 slot, int id)
{
	static const short init[10] = { 0, 0, 0, 0, 0, -1, 0, 0, -1, 0 };
	NetSlot *r = &g_netSlots[slot & 0xff];
	r->used = 1;
	r->id = id;
	memcpy(r->packet, init, sizeof init);
	memcpy(&r->packet[0x22], &g_localPlayerData, 2);
}

/* 0x4515a0: all slots freed (and the 0x40 bytes at 0x9f93d8 cleared) */
void (net_freeAllSlots)(void)
{
	memset((void *)OBJ(g_playerSlotFlags), 0, 0x40);
	for (NetSlot *r = g_netSlots; r < g_netSlots + 16; r++)
		memset(r, 0, offsetof(NetSlot, packet));
}

/* 0x451450: a free player slot claimed (its flag in the sixteen at 0x9f93d8 set); 0xff when none is free */
u8 (net_claimPlayerSlot)(void)
{
	for (u8 i = 0; i < 0x10; i++)
		if (GAME_VAR(int, OBJ(g_playerSlotFlags) + i * 4) == 0) {
			GAME_VAR(int, OBJ(g_playerSlotFlags) + i * 4) = 1;
			return i;
		}
	return 0xff;
}

/* 0x451410: a slot claimed for the local player (id 0xa0b424) when the session is up; 1 when done */
int (net_claimLocalSlot)(void)
{
	if (!g_isHost)
		return 0;
	u8 slot = net_claimPlayerSlot();
	net_takePlayerSlot(slot, (*(int *)&g_localPlayerId));
	g_watchedSlot = slot;
	g_slotTakenFlag = 1;
	return 1;
}

/* 0x454130: with a session list (0xa0b384), every used session slot (g_sessionTable)
   freed and the list emptied (count 0xa0b41c). Returns the count, or 0 without a list */
u32 (net_freeSessionList)(void)
{
	if (!g_dplaySessionList)
		return 0;
	for (int i = 0; i < g_dplaySessionCount; i++) {
		SessionSlot *rec = &g_sessionTable[i];
		if (rec->used != 1)
			continue;
		rec->used = 0;
		if (rec->desc)
			crt_free(RELOC(rec->desc));
		rec->used = 0;
		rec->desc = 0;
	}
	u32 r = (*(u32 *)&g_dplaySessionCount);
	g_dplaySessionCount = 0;
	return r;
}

/* 0x4542a0: the address typed as "a.b.c.d" (0xa0b43c, cut up in place by strtok) as (a << 24) | b << 16 | c << 8 | d
   (a not masked). Each part goes into a 4-byte slot of a zeroed 20-byte buffer (a longer part runs into the next
   slot); more than four parts would overrun the original's stack, and a string with none makes it copy from NULL */
int (net_parseAddress)(void)
{
	char buf[20];
	memset(buf, 0, sizeof buf);
	char *part = crt_strtok(g_localAddress, (const char *)STR(0x4b1304, "."));
	strcpy(buf, part);
	if (part)
		for (char *slot = buf + 4; (part = crt_strtok(NULL, (const char *)STR(0x4b3e68, ".\n"))) != NULL; slot += 4)
			strcpy(slot, part);
	int a = crt_atoi(buf), b = crt_atoi(buf + 4), c = crt_atoi(buf + 8), d = crt_atoi(buf + 12);
	return ((((a << 8) | (b & 0xff)) << 8 | (c & 0xff)) << 8) | (d & 0xff);
}

/* 0x454390: the address as "a.b.c.d" (bytes high to low) into 0xa0b460; returns its length + 1 */
int (dplay_formatSessionEntry)(u32 address)
{
	char text[16], part[4];
	itoa((int)(address >> 24), part, 10);
	strcpy(text, part);
	for (int shift = 16; shift >= 0; shift -= 8) {
		strcat(text, (const char *)STR(0x4b1304, "."));
		itoa((int)((address >> shift) & 0xff), part, 10);
		strcat(text, part);
	}
	strcpy(g_dottedAddress, text);
	return (int)strlen(text) + 1;
}

/* 0x4540b0: a session found (by value): unless its instance GUID is GUID_NULL (k_GUID_NULL, 0x4aae70), a copy
   (malloc'd) kept in the first free slot of the table at 0xa0b470, the count up. Returns the copy, 0 for a session
   without a GUID, or -1 when the table is full */
u32 (net_addSession)(SessionDesc d)
{
	if (!memcmp(d.instance, (const void *)OBJ(k_GUID_NULL), 16))
		return 0;
	int i = net_findFreeSession();
	if (i < 0)
		return (u32)i;
	SessionDesc *copy = crt_malloc(sizeof(SessionDesc));
	g_sessionTable[i].desc = copy;
	g_sessionTable[i].used = 1;
	memcpy(g_sessionTable[i].desc, &d, sizeof d);
	g_dplaySessionCount += 1;
	return (u32)copy;
}

/* 0x453560 (stdcall; DirectPlay's session enumeration callback): a found session (desc: its GUID at +8, name at
   +0x30 ..) put into the list (net_addSession, by value) unless its GUID is GUID_NULL (1) or already listed (0, which
   ends the enumeration). With no description (the enumeration timed out) it stops in modes 0 and 1. The copy's
   first word is a GlobalAlloc'd block holding the GUID; in mode 0 (+0x74) the session's address as text. 1 */
int STDCALL (dplay_enumSessionsCallback)(const u8 *desc, void *timeout, u32 flags, void *context)
{
	int mode = g_connectionKind;
	if ((mode == 1 || mode == 0) && !desc)
		return 0;
	const DPSessionDesc2 *dd = (const DPSessionDesc2 *)desc;
	SessionDesc d;
	memset(&d, 0, sizeof d);
	const u8 *guid = dd->instance;
	if (!memcmp(guid, (const void *)OBJ(k_GUID_NULL), 16))
		return 1;
	for (int k = 0; k < g_dplaySessionCount; k++)
		if (!memcmp(guid, g_sessionTable[k].desc->instance, 16))
			return 0;
	u8 *block = GlobalLock(GlobalAlloc(0x42, 0x10));   /* GlobalLock(GlobalAlloc(GHND)) */
	d.guid = (u32)block;
	crt_strncpy(d.name, dd->name, 0x46);
	memcpy(&d.players, &dd->players, 4);
	memcpy(block, guid, 16);
	memcpy(d.instance, guid, 16);
	memcpy(d.application, dd->application, 16);
	d.gameMode = (signed char)dd->user2;
	d.maxPlayers = (u8)dd->maxPlayers;
	memcpy(&d.map, &dd->user1, 2);                                    /* map, rotation */
	d.fragLimit = (u8)(dd->user3 >> 8);
	d.timeLimit = (u8)dd->user3;
	if (g_connectionKind == 0) {
		dplay_formatSessionEntry(dd->user4);   /* dplay_formatSessionEntry */
		crt_strncpy(d.address, g_dottedAddress, 0x10);
	}
	net_addSession(d);
	return 1;
}

/* 0x4547c0: inet_addr of the text (Winsock, through the game's jump to its import) */
u32 (net_inetAddr)(const char *text) { return ws_inet_addr(text); }

/* 0x451270: a message sent from the local player (0xa0b424) to to: types 2 and 6 guaranteed (flag 1) with 8 bytes,
   type 7 with size bytes, any other with none. Returns the send's result */
int (net_sendMessage)(const int *message, u32 to, u32 size)
{
	u32 flags = 0, length = 0;
	switch (message[0]) {
	case 2:
	case 6:
		flags = 1;
		length = 8;
		break;
	case 7:
		length = size;
		break;
	}
	return dplay_send(g_localPlayerId, to, flags, message, length);
}

/* 0x452170: socket 100 (message 0x40a) or 101 (0x40c) set to tell the window wnd about reads and closes
   (WSAAsyncSelect, 0x21); 0 when that fails, else 1 (also without the socket) */
int (net_asyncSelect)(void *wnd, int which)
{
	u32 sock, message;
	if (which == 100) {
		sock = g_lobbySocket;
		message = 0x40a;
	} else if (which == 101) {
		sock = (*(u32 *)&g_gameServerSocket);
		message = 0x40c;
	} else
		return 1;
	if (!sock)
		return 1;
	if (WSAAsyncSelect(sock, wnd, message, 0x21) == -1)
		return 0;
	return 1;
}

/* 0x453720: DirectPlay's start: its state and the session table cleared, COM started, the DirectPlay objects made
   (dplay_check); on a failure everything released again and the error returned, else 0 */
int (dplay_coInit)(void)
{
	g_unusedDplayWord1 = 0;
	g_unusedDplayWord2 = 0;
	g_unusedDplayWord3 = 0;
	memset((void *)OBJ(g_sessionTable), 0, 0x190 * 4);
	g_unusedDplayWord4 = 0;
	int hr = CoInitialize(NULL);   /* CoInitialize */
	if (hr >= 0) {
		hr = dplay_check();      /* dplay_check */
		if (hr >= 0)
			return 0;
	}
	dplay_release();
	return hr;
}

/* 0x454760: the network thread's three handles closed (0xa0d788, 0xa0bf1c, 0xa0bb10) and the running flag cleared.
   Returns what the original leaves in eax (the last close's answer, or 0) */
u32 (net_closeThreadHandles)(void)
{
	static const u32 handles[3] = { ADDR(g_pingThread), ADDR(g_pingStopEvent), ADDR(g_pingDataEvent) };
	u32 r = 0;
	for (int k = 0; k < 3; k++) {
		r = GAME_VAR(u32, handles[k]);
		if (r) {
			r = CloseHandle(r);   /* CloseHandle */
			GAME_VAR(u32, handles[k]) = 0;
		}
	}
	if (g_pingThreadId)
		g_pingThreadId = 0;
	return r;
}

/* 0x452d70: the server's 62-byte reply received into 0xa052e8 (recv on 0xa05630 until 62 bytes have come or 3 s
   have passed; each call reads to the start of the buffer), then by its kind (+0x1e): 0 accepted (net_addPlayerRecord), 1
   refused (0xa0b350 set, 0xa0b300 cleared) */
void (net_receiveServerReply)(void)
{
	u8 *reply = g_serverReply;
	u32 start = GetTickCount();
	u32 got = 0;
	do {
		int n = ws_recv((*(u32 *)&g_gameServerSocket), reply, 0x3e, 0);   /* recv */
		if (n > 0)
			got += n;
	} while (GetTickCount() - start <= 3000 && got < 0x3e);
	switch (g_serverReplyKind) {
	case 0:
		net_addPlayerRecord(reply);
		break;
	case 1:
		g_playerListRefused = 1;
		g_netLastRequest = 0;
		break;
	}
}

/* 0x4520e0: both sockets (0xa055f8, 0xa05630) closed: a blocking call cancelled, sending shut down, the socket closed,
   the connection's state reset (arena_freeBuffers); then the connection flags cleared. Returns what the original leaves
   in eax */
u32 (net_closeSockets)(void)
{
	static const u32 sockets[2] = { ADDR(g_lobbySocket), ADDR(g_gameServerSocket) };
	u32 r = g_lobbySocket;
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(u32, sockets[k]))
			continue;
		g_netHostGone = 1;
		WSACleanup();                                     /* WSACleanup */
		IMPORT(WS_SHUTDOWN, int, u32, int)(GAME_VAR(u32, sockets[k]), 1);   /* shutdown(SD_SEND) */
		IMPORT(WS_CLOSESOCKET, int, u32)(GAME_VAR(u32, sockets[k]));           /* closesocket */
		GAME_VAR(u32, sockets[k]) = 0;
		r = arena_freeBuffers();
	}
	g_netLastRequest = 0;
	g_lobbyConnectStatus = 0;
	return r;
}

/* a block of n bytes from malloc, cleared */
static void *alloc_clear(u32 n)
{
	void *p = crt_malloc(n);
	memset(p, 0, n);
	return p;
}

/* 0x451600: the connection to `kind` (100 the lobby, 101 the game server) started afresh: the server table cleared,
   both sockets closed (a blocking call cancelled, sending shut down; arena_freeBuffers after each), the server's address
   taken (its host name, or what net_resolveHost made of it, into 0xa055e4) with its port (0xa05326); then every
   network table cleared and the packet buffers allocated anew, cleared. The caller ignores the eax it leaves */
void (net_closeAll)(int kind)
{
	net_clearServers();
	static const u32 sockets[2] = { ADDR(g_lobbySocket), ADDR(g_gameServerSocket) };
	for (int k = 0; k < 2; k++) {
		if (!GAME_VAR(u32, sockets[k]))
			continue;
		WSACleanup();                                     /* WSACleanup */
		IMPORT(WS_SHUTDOWN, int, u32, int)(GAME_VAR(u32, sockets[k]), 1);   /* shutdown(SD_SEND) */
		IMPORT(WS_CLOSESOCKET, int, u32)(GAME_VAR(u32, sockets[k]));           /* closesocket */
		GAME_VAR(u32, sockets[k]) = 0;
		arena_freeBuffers();
	}
	if (kind == 100 || kind == 101) {
		const char *host = (const char *)(RELOC(kind) == 100 ? OBJ(g_tcpDns) : OBJ(g_ladderDns));
		strcpy(g_lobbyHost, net_resolveHost(host) ? g_serverAddress : host);
		g_serverPort = GAME_VAR(u16, kind == 100 ? ADDR(g_lobbyTcpPort) : ADDR(g_ladderPort));
	}
	memset((void *)OBJ(g_roomList), 0, 0x1e40 * 4);
	memset((void *)OBJ(g_serverList), 0, 0x16c0 * 4);
	memset((void *)OBJ(g_netPlayerList), 0, 0x2aa);
	static const struct { u32 at, size; } buffers[] = {
		{ ADDR(g_roomPacket), 0x5b }, { ADDR(g_netInfoPacket), 0x5b }, { ADDR(g_lobbyLeavePacket), 0x5b }, { ADDR(g_netLobbyMessage), 4 }, { ADDR(g_netSendName), 0x10 }, { ADDR(g_accountPacket), 0x10b },
		{ ADDR(g_netRankingBuffer), 8 }, { ADDR(g_arenaPacket), 0x79 }, { ADDR(g_arenaInfoPacket), 0x79 }, { ADDR(g_roomRecordPacket), 0x79 }, { ADDR(g_netRequestWord), 4 }, { ADDR(g_netKindWord), 4 },
		{ ADDR(g_netSendBuffer), 0x10 }, { ADDR(g_netSelectionPacket), 0xb9 }, { ADDR(g_netAccountBuffer), 0x5c }, { ADDR(g_netPlayerRecordPacket), 0x36 }, { ADDR(g_netOneByte), 1 }, { ADDR(g_netJoinMessage), 0x1e } };
	for (unsigned k = 0; k < sizeof buffers / sizeof *buffers; k++)
		GAME_VAR(void *, buffers[k].at) = alloc_clear(buffers[k].size);
	memset((void *)ADDR(g_netNotice), 0, 0x22);
	(*(void **)&g_netLeaveBuffer) = alloc_clear(0x1e);
	memset((void *)OBJ(g_lobbyReplyRecord), 0, 0x5b);
	memset((void *)OBJ(g_gameServerReply), 0, 0x79);
	g_unusedNetCloseWord = 0;
	memset((void *)OBJ(g_serverReply), 0, 0x3e);
	memset((void *)ADDR(g_netRecvBuffer), 0, 0x10b);
}

/* a GlobalAlloc'd block unlocked and freed (through its handle) */
static void global_free(void *p)
{
	GlobalUnlock(GlobalHandle(p));   /* GlobalUnlock(GlobalHandle(p)) */
	GlobalFree(GlobalHandle(p));   /* GlobalFree(GlobalHandle(p)) */
}

/* 0x453920: DirectPlay shut down: the lobby object released, the local player destroyed and the session closed and
   released, the session buffers freed (0xa0bab0 is freed but not cleared), COM ended. Returns 0 */
int (dplay_release)(void)
{
	void *lobby = g_dplayLobby;
	if (lobby) {
		COM(lobby, COM_RELEASE, u32)(lobby);
		g_dplayLobby = 0;
	}
	void *play = g_dplay;
	if (play) {
		if (g_localPlayerId) {
			COM(play, 0x24, u32, u32)(play, g_localPlayerId);   /* DestroyPlayer */
			play = g_dplay;
			g_localPlayerId = 0;
		}
		COM(play, 0x10, u32)(play);   /* Close */
		play = g_dplay;
		COM(play, COM_RELEASE, u32)(play);
		g_dplay = 0;
	}
	if (g_hostAddressBlock) {
		crt_free(g_hostAddressBlock);
		g_hostAddressBlock = 0;
	}
	if (g_connectionCopy)
		global_free(g_connectionCopy);
	if (g_lobbyConnectionBlock) {
		global_free(g_lobbyConnectionBlock);
		g_lobbyConnectionBlock = 0;
	}
	CoUninitialize();   /* CoUninitialize */
	return 0;
}

/* 0x4547d0: host (a name or dotted address) resolved: Winsock started, a raw ICMP socket opened (for the pings),
   the host looked up and its first address as text in 0xa0d320; the socket closed again. 1 when there is an
   address; 0 if Winsock, the socket or the lookup failed (the socket is left open then, as in the original) */
int (net_resolveHost)(const char *host)
{
	u8 wsa[0x190];
	memset((void *)OBJ(g_serverAddress), 0, 0x64);
	if (WSAStartup(0x202, wsa))             /* WSAStartup */
		return 0;
	int sock = ws_socket(2, 3, 1);        /* ws_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) */
	if (sock == -1)
		return 0;
	u8 *entry = ws_gethostbyname(host);           /* gethostbyname */
	if (!entry)
		return 0;
	u32 address = ***(u32 ***)(entry + 0xc);                                 /* h_addr_list[0] */
	strcpy(g_serverAddress, ws_inet_ntoa(address));   /* inet_ntoa */
	if (!strlen(g_serverAddress))
		return 0;
	if (sock) {
		WSACleanup();      /* WSACleanup */
		IMPORT(WS_CLOSESOCKET, int, int)(sock);   /* closesocket */
	}
	return 1;
}

/* 0x453fd0: the sessions asked for (DirectPlay EnumSessions, async with the callback 0x453560, flags 0x12): of the
   game's application (GUID at 0x4a96e8), on the instance at *0xa0bad8; once more while 0xa0b418 is 1. 1 on success,
   0 without DirectPlay or on a failure */
int (dplay_enumSessions)(void)
{
	void *play = g_dplay;
	if (!play)
		return 0;
	DPSessionDesc2 desc;
	memset(&desc, 0, sizeof desc);
	desc.size = sizeof desc;
	memcpy(desc.instance, g_instanceGuid, 16);
	memcpy(desc.application, (const void *)OBJ(k_axisAppGuid), 16);
	if (!g_connectionKind) {
		if (COM(play, 0x34, int, void *, u32, void *, void *, u32)(play, &desc, 0, (void *)FN_ADDR(dplay_enumSessionsCallback, 0x453560), NULL, 0x12) < 0)
			return 0;
		play = g_dplay;
	}
	if (g_connectionKind == 1 &&
	    COM(play, 0x34, int, void *, u32, void *, void *, u32)(play, &desc, 0, (void *)FN_ADDR(dplay_enumSessionsCallback, 0x453560), NULL, 0x12) < 0)
		return 0;
	return 1;
}

#define lstrcpyA(dst, src) IMPORT(0x4a911c, char *, char *, const char *)(dst, src)

/* ---- a received record appended to a list: its strings (each also as the list's name, 20 bytes a slot at
   0xa0bf20) and single bytes copied into the next slot, the count advanced. Returns the slot's offset in the list
   (the original's eax) ---- */
static int list_append(u32 count, u32 base, int size, const u8 *rec, const u8 *strings, int nstrings, int name,
                       const u8 *bytes, int nbytes)
{
	for (int k = 0; k < nstrings; k++)
		lstrcpyA((char *)(RELOC(base) + GAME_VAR(int, count) * size + strings[k]), (const char *)RELOC(rec) + strings[k]);
	lstrcpyA((char *)(OBJ(g_serverNames) + GAME_VAR(int, count) * 20), (const char *)RELOC(rec) + name);
	int i = GAME_VAR(int, count);
	u8 *slot = (u8 *)(RELOC(base) + i * size);
	for (int k = 0; k < nbytes; k++)
		slot[bytes[k]] = rec[bytes[k]];
	GAME_VAR(int, count) = i + 1;
	return i * size;
}
/* 0x452af0: a ServerRecord into the list at 0xa05748 (count 0xa0b368) */
int (net_addServerRecord)(const u8 *rec)
{
	static const u8 strings[3] = { offsetof(ServerRecord, address), offsetof(ServerRecord, name), offsetof(ServerRecord, password) };
	static const u8 bytes[9] = { offsetof(ServerRecord, kind), offsetof(ServerRecord, rotation), offsetof(ServerRecord, fragLimit), offsetof(ServerRecord, timeLimit), offsetof(ServerRecord, gameMode), offsetof(ServerRecord, players), offsetof(ServerRecord, map), offsetof(ServerRecord, maxPlayers), offsetof(ServerRecord, locked) };
	return list_append(ADDR(g_serverListCount), OBJ(g_serverList), sizeof(ServerRecord), rec, strings, 3, offsetof(ServerRecord, address), bytes, 9);
}
/* 0x452c80: a RoomRecord into the list at 0x9fd960 (count 0xa0b358) */
int (net_addRoomRecord)(const u8 *rec)
{
	static const u8 strings[4] = { offsetof(RoomRecord, hostName), offsetof(RoomRecord, address), offsetof(RoomRecord, name), offsetof(RoomRecord, password) };
	static const u8 bytes[9] = { offsetof(RoomRecord, kind), offsetof(RoomRecord, rotation), offsetof(RoomRecord, fragLimit), offsetof(RoomRecord, gameMode), offsetof(RoomRecord, players), offsetof(RoomRecord, map), offsetof(RoomRecord, maxPlayers), offsetof(RoomRecord, timeLimit), offsetof(RoomRecord, locked) };
	return list_append(ADDR(g_roomListCount), OBJ(g_roomList), sizeof(RoomRecord), rec, strings, 4, offsetof(RoomRecord, address), bytes, 9);
}

#define lstrlenA(s) IMPORT(0x4a9188, int, const char *)(s)
/* 0x451350: a chat line for the log: "<name>: <text>" (format 0x4b3e30; the sender's short name from DirectPlay
   through 0x454190, "?" when it has none) in a new global block, stored in *out. Returns the name lookup's result,
   or 0x8007000e (E_OUTOFMEMORY) when the block cannot be had */
int (net_logMessage)(u32 from, const char *text, char **out)
{
	u8 *name = NULL;
	int r = dplay_getPlayerName(from, &name);
	if (r >= 0) {
		const char *shortName = *(const char **)(RELOC(name) + 8);
		if (!shortName)
			shortName = (const char *)STR(0x4b3e38, "unknown");
		int length = lstrlenA(shortName) + lstrlenA(text) + lstrlenA((const char *)STR(0x4b3e30, "%s > %s")) + 1;
		char *line = IMPORT(0x4a9198, char *, void *)(GlobalAlloc(0x42, length));   /* GlobalLock(GlobalAlloc(GHND)) */
		if (!line)
			r = 0x8007000e;
		else {
			((int (CDECL *)(char *, const char *, ...))g_imp_wsprintfA)(line, (const char *)STR(0x4b3e30, "%s > %s"), shortName, text);   /* wsprintfA */
			*out = line;
		}
	}
	if (name)
		global_free(name);
	return r;
}

/* 0x454d90: the first place in text where word appears (strncmp at each position where the first letters match, or
   _strnicmp, ignoring case, when exact is 0); NULL when it does not */
const char *(text_findWord)(const char *text, const char *word, int exact)
{
	int length = strlen(word);
	int positions = strlen(text) - length + 1;
	char first = word[0];
	for (int i = 0; i < positions; i++) {
		if (exact) {
			if (text[i] == first && !crt_strncmp(text + i, word, length))   /* strncmp */
				return text + i;
		} else if (!crt_strnicmp(text + i, word, length))   /* _strnicmp */
			return text + i;
	}
	return NULL;
}

/* 0x4546d0: the network worker started: two events (0xa0bb10, 0xa0bf1c) and the thread running 0x454560 (handle
   0xa0d788, id 0xa0d784), then the first event set. 1, or 0 when any of them cannot be made */
int (net_startThread)(void)
{
	if (!(g_pingDataEvent = CreateEventA(NULL, 0, 0, NULL)))   /* CreateEventA */
		return 0;
	if (!(g_pingStopEvent = CreateEventA(NULL, 0, 0, NULL)))
		return 0;
	g_pingThread = CreateThread(NULL, 0, (void *)FN_ADDR(net_pingThreadProc, 0x454560), NULL, 0, (u32 *)ADDR(g_pingThreadId));   /* CreateThread */
	if (!g_pingThread)
		return 0;
	SetEvent(g_pingDataEvent);
	return 1;
}

/* 0x452de0: a player record appended to the list at 0xa05330 (count 0xa0b35c): its name and the seven values after
   its kind. Returns the slot's offset (the original's eax) */
int (net_addPlayerRecord)(const u8 *rec)
{
	const RankedPlayer *from = (const RankedPlayer *)RELOC(rec);
	lstrcpyA(g_netPlayerList[g_playerListCount].name, from->name);
	int i = g_playerListCount;
	RankedPlayer *slot = &g_netPlayerList[i];
	slot->deaths = from->deaths;
	slot->kills = from->kills;
	slot->value22 = from->value22;
	slot->exp = from->exp;
	BITS(slot->power) = BITS(from->power);
	BITS(slot->rate) = BITS(from->rate);
	slot->level = from->level;
	g_playerListCount = i + 1;
	return i * 62;
}

/* 0x454220: this machine's address as text in 0xa0b43c (16 bytes, cleared first): its host name looked up and the
   first address taken. -1 when the name cannot be had, otherwise 0 */
int (net_getLocalAddress)(void)
{
	char name[0xc8];
	memset((void *)OBJ(g_localAddress), 0, 16);
	if (ws_gethostname(name, 0xc8) == -1)   /* gethostname */
		return -1;
	u8 *entry = ws_gethostbyname(name);     /* gethostbyname */
	if (entry)
		strcpy(g_localAddress, ws_inet_ntoa(***(u32 ***)(entry + 0xc)));   /* inet_ntoa */
	return 0;
}

/* 0x4512c0: a chat line sent: logged for this player (net_logMessage into 0x9fd944), then a message (type 1, from
   the player 0xa0b424, the text at +0xc) in a new global block sent to everyone (0x450bf0). 1 when sent */
int (net_sendChat)(const char *text)
{
	if (net_logMessage(g_localPlayerId, text, (char **)ADDR(g_sentChatBlock)) < 0)   /* net_logMessage */
		return 0;
	int size = lstrlenA(text) + 0x10;
	u8 *message = GlobalLock(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!message)
		return 0;
	*(u32 *)RELOC(message) = 1;
	*(u32 *)(RELOC(message) + 8) = g_localPlayerId;
	lstrcpyA((char *)RELOC(message) + 0xc, text);
	return GAME_FN(dplay_send, 0x450bf0, int, u32, u32, u32, void *, int)(g_localPlayerId, 0, 0, message, size) >= 0;
}

/* 0x4548b0: host ip pinged (ICMP echo, waiting up to timeout ms). Returns the round trip time, kept in 0xa0d798:
   0 when the echo failed with no time, 1 when it came back in no time */
/* (the game calls the three through its jump thunks 0x454e4c / 0x454e46 / 0x454e40; AxisRC.exe carries no game code,
   so there they are called through the import slots the thunks jump through) */
#ifdef AXIS_DIRECT
#define ICMP_CREATE IMPORT(0x4a9058, void *, void)
#define ICMP_SEND IMPORT(0x4a905c, u32, void *, u32, void *, u16, void *, void *, u32, u32)
#define ICMP_CLOSE IMPORT(0x4a9060, int, void *)
#else
#define ICMP_CREATE ((void *(STDCALL *)(void))IMG(0x454e4c))
#define ICMP_SEND ((u32 (STDCALL *)(void *, u32, void *, u16, void *, void *, u32, u32))IMG(0x454e46))
#define ICMP_CLOSE ((int (STDCALL *)(void *))IMG(0x454e40))
#endif
u32 (net_ping)(u32 ip, u32 timeout)
{
	u32 reply[9];   /* ICMP_ECHO_REPLY; [2] the round trip time */
	g_pingTime = 0;
	void *icmp = ICMP_CREATE();   /* IcmpCreateFile */
	memset(reply, 0, sizeof reply);
	reply[2] = 0xffffffff;
	u32 sent = ICMP_SEND(icmp, ip, NULL, 0, NULL, reply, 0x24, timeout);   /* IcmpSendEcho */
	u32 rtt = reply[2];
	if (!sent) {
		g_pingTime = rtt;
		ICMP_CLOSE(icmp);   /* IcmpCloseHandle */
		return rtt ? g_pingTime : 0;
	}
	g_pingTime = rtt ? rtt : 1;
	ICMP_CLOSE(icmp);
	return g_pingTime;
}

/* 0x454190: player id's name (a DPNAME) fetched into a new global block (*out): its size asked first (GetPlayerName
   with no buffer). 0, or the error (0x8007000e when the block cannot be had; the block is freed again on a failure) */
int (dplay_getPlayerName)(u32 id, void **out)
{
	void *play = g_dplay;
	u32 size;
	int r = COM(play, 0x54, int, u32, void *, u32 *)(play, id, NULL, &size);
	if (r != (int)0x8877001e)   /* DPERR_BUFFERTOOSMALL */
		return r;
	void *name = IMPORT(0x4a9198, void *, void *)(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!name)
		return 0x8007000e;
	play = g_dplay;
	r = COM(play, 0x54, int, u32, void *, u32 *)(play, id, name, &size);
	if (r >= 0) {
		*out = name;
		return 0;
	}
	global_free(name);
	return r;
}

/* 0x4545b0: every server in the list pinged (net_pingServer by name, 20 bytes a slot at 0xa0bf20) until done
   (0xa0d7a0): its time in 0xa0d384 (above 1000 ms less 400; 0 when it did not answer) and marked pinged (0xa0bb14);
   then done, and the events reset (0x454740, whose eax it returns) */
u32 (net_pingAllServers)(void)
{
	(*(int *)&g_pingTime) = 0;
	if (g_serverPingCount > 0) {
		for (int i = 0; i < g_serverPingCount && g_netListDone != 1; i++) {
			const char *name = (const char *)(OBJ(g_serverNames) + i * 20);
			if ((int)strlen(name) <= 0)
				continue;
			if (net_pingServer(name, i)) {   /* net_pingServer */
				int time = (*(int *)&g_pingTime);
				if (time > 1000)
					(*(int *)&g_pingTime) = time -= 400;
				GAME_VAR(int, OBJ(g_serverPing) + i * 4) = time;
			} else
				GAME_VAR(int, OBJ(g_serverPing) + i * 4) = 0;
			GAME_VAR(int, OBJ(g_serverUsed) + i * 4) = 1;
		}
	}
	g_netListDone = 1;
	return net_wakePingThread();   /* net_wakePingThread */
}

/* ---- a reply of size bytes read from socket into buf, waiting up to 3 s. Each recv lands at buf's start (as in the
   original); the bytes are only counted ---- */
static void reply_read(u32 socket, void *buf, u32 size)
{
	u32 start = GetTickCount();   /* GetTickCount */
	u32 got = 0;
	do {
		int n = ws_recv(GAME_VAR(u32, socket), buf, size, 0);   /* recv */
		if (n > 0)
			got += n;
	} while (GetTickCount() - start <= 3000 && got < size);
}

/* 0x452a30: a lobby reply (0x5b bytes into 0xa05260, socket 0xa055f8), by its type (0xa052aa): 0 a server for the
   list (net_addServerRecord), 1 the list is complete (its count to 0xa0d79c, the ping thread started), 2 / 3 the connection
   state 0xa0b36c set (0xcb / 0x29); 1..3 also end the wait (0xa0b300) */
void (net_receiveLobbyReply)(void)
{
	reply_read(ADDR(g_lobbySocket), (void *)OBJ(g_lobbyReplyRecord), 0x5b);
	switch (g_lobbyReplyKind) {
	case 0:
		net_addServerRecord((void *)OBJ(g_lobbyReplyRecord));   /* net_addServerRecord */
		break;
	case 1:
		g_serverPingCount = g_serverListCount;
		net_startThread();   /* net_startThread */
		g_serverConnectionState = 0xca;
		g_netLastRequest = 0;
		break;
	case 2:
		g_serverConnectionState = 0xcb;
		g_netLastRequest = 0;
		break;
	case 3:
		g_serverConnectionState = 0x29;
		g_netLastRequest = 0;
		break;
	}
}

/* 0x452bd0: a game server's reply (0x79 bytes into 0xa0b280, socket 0xa05630), by its type (0xa0b2e8): 0 a room for
   the list (net_addRoomRecord), 1 the list is complete (as above, state 0xa0b34c 0xca), 2 / 3 state 0x28 */
void (net_receiveGameServerReply)(void)
{
	reply_read(ADDR(g_gameServerSocket), (void *)OBJ(g_gameServerReply), 0x79);
	switch (g_gameServerReplyKind) {
	case 0:
		net_addRoomRecord((void *)OBJ(g_gameServerReply));   /* net_addRoomRecord */
		break;
	case 1:
		g_serverPingCount = g_roomListCount;
		net_startThread();
		g_gameServerState = 0xca;
		g_netLastRequest = 0;
		break;
	case 2:
	case 3:
		g_gameServerState = 0x28;
		g_netLastRequest = 0;
		break;
	}
}

/* a global block freed; returns GlobalFree's eax */
static u32 global_free_r(void *p)
{
	GlobalUnlock(GlobalHandle(p));          /* GlobalUnlock(GlobalHandle(p)) */
	return GlobalFree(GlobalHandle(p));   /* GlobalFree(GlobalHandle(p)) */
}

/* 0x450a60: every waiting DirectPlay message received (0x450bc0) into a global block of 0x9fd940 bytes, grown when
   too small: system messages (from 0) go to 0x450c20 and the next is read; the first player message goes to
   net_handleMessage (a type 7 one longer than 0x49 bytes is dropped). The block is freed at the end (its size reset).
   Returns what the original leaves in eax */
u32 (net_receiveAll)(void)
{
	u8 *buf = NULL;
	u32 size = g_netBlockSize, r;
	for (;;) {
		u32 from = 0, to = 0;
		r = dplay_receive(&from, &to, 1, buf, &size);
		if (r == 0x887700be || r == 0x887703e8)   /* no more messages */
			break;
		if (r == 0x8877001e) {                     /* the buffer too small: a bigger one */
			if (buf)
				global_free_r(buf);
			buf = GlobalLock(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
			if (!buf)
				return 0;
			g_netBlockSize = size;
			continue;
		}
		if (r != 0 || g_netBlockSize < 4)
			break;
		if (!from) {
			net_sendLocalInfo(buf);   /* a system message */
			continue;
		}
		if (*(u32 *)buf == 7 && g_netBlockSize > 0x49)
			return global_free_r(buf);
		r = net_handleMessage(buf, g_netBlockSize, from);   /* net_handleMessage */
		break;
	}
	if (!buf)
		return r;
	r = global_free_r(buf);
	g_netBlockSize = 0;
	return r;
}

/* the session description shared by hosting and joining (g_sessionDesc at 0xa0b3b0): cleared, its size, the
   session's GUID and the game's application GUID (0x4a96e8) */
static DPSessionDesc2 *session_desc(const void *guid)
{
	DPSessionDesc2 *desc = g_sessionDesc;
	memset(desc, 0, sizeof *desc);
	desc->size = sizeof *desc;
	memcpy(desc->instance, guid, 16);
	memcpy(desc->application, (const void *)OBJ(k_axisAppGuid), 16);
	return desc;
}

/* the local player created (CreatePlayer with the short name `name`, no data); its id into *id */
static int create_player(void *play, u32 *id, const char *name)
{
	u32 dpname[4] = { 0x10, 0, (u32)name, 0 };   /* DPNAME: dwSize, dwFlags, lpszShortNameA, lpszLongNameA */
	return COM(play, 0x18, int, u32 *, void *, void *, void *, u32, u32)(play, id, dpname, NULL, NULL, 0, 0);
}

/* 0x453cf0: a session hosted (Open with DPOPEN_CREATE): flags 0x44, the instance GUID from *0xa0bad8, the session
   name, at most maxPlayers, the user words (user3 = hi << 8 | lo, sign-extended bytes; user4 the local address,
   unless 0xa0b418), then the local player `player`: its id into 0xa0b424, data into 0xa0b428, the host flag
   0xa0baf8 set and a player slot claimed (net_claimLocalSlot). 0 without DirectPlay or on a failure, else 1 */
int (dplay_hostSession)(const char *session, const char *player, u32 user1, u32 maxPlayers, u32 user2,
                        signed char hi, signed char lo, u32 data)
{
	void *play = g_dplay;
	if (!play)
		return 0;
	DPSessionDesc2 *desc = session_desc(g_instanceGuid);
	desc->flags = 0x44;
	desc->name = session;
	desc->maxPlayers = maxPlayers;
	desc->user1 = user1;
	desc->user2 = user2;
	desc->user3 = (u32)((int)hi << 8 | (int)lo);
	if (!g_connectionKind) {
		net_getLocalAddress();                 /* net_getLocalAddress */
		desc->user4 = net_parseAddress();       /* net_parseAddress */
		play = g_dplay;
	}
	if (COM(play, 0x60, int, void *, u32)(play, desc, 2) < 0)   /* Open(DPOPEN_CREATE) */
		return 0;
	u32 id;
	if (create_player(g_dplay, &id, player) < 0)
		return 0;
	g_localPlayerData = data;
	g_localPlayerId = id;
	g_isHost = 1;
	net_claimLocalSlot();   /* net_claimLocalSlot */
	return 1;
}

/* 0x453e60: the session `guid` joined (Open with DPOPEN_JOIN), then the local player `player`: its id into
   0xa0b424, data into 0xa0b428, the host flag 0xa0baf8 cleared. 0x1f4 joined (also for a CreatePlayer error not
   listed), 0x1f9 / 0x1f8 / 0x1f6 Open failing (0x887700dc, 0x887700f0, any other), 0x1fa the session full or
   refusing the player, 0x1fb without DirectPlay */
int (dplay_joinSession)(const void *guid, const char *player, u32 data)
{
	void *play = g_dplay;
	if (!play)
		return 0x1fb;
	int r = COM(play, 0x60, int, void *, u32)(play, session_desc(guid), 1);   /* Open(DPOPEN_JOIN) */
	if (r == (int)0x887700dc)
		return 0x1f9;
	if (r == (int)0x887700f0)
		return 0x1f8;
	if (r)
		return 0x1f6;
	u32 id;
	r = create_player(g_dplay, &id, player);
	switch ((u32)r) {
	case 0x88770078: case 0x80070057: case 0x88770028: case 0x8877003c: case 0x887700aa: case 0x88770168:
		return 0x1fa;
	case 0:
		g_localPlayerData = data;
		g_localPlayerId = id;
		g_isHost = 0;
	}
	return 0x1f4;
}

/* the lobby's part of dplay_create: its connection settings (DPLCONNECTION, into a global block 0xa0baf4) with the
   session flags 0x44 and at most 16 players, connected (ConnectEx into 0xa0b404) and the local player created
   with the lobby's player name record; the host flag 0xa0baf8 by the connection's flags (2 create, 1 join). Stops at the
   first failure */
static void dplay_lobbyConnect(void)
{
	if (CoCreateInstance((const void *)OBJ(k_CLSID_DirectPlayLobby), NULL, 1,
			(const void *)OBJ(k_IID_IDirectPlayLobby3A), (void **)ADDR(g_dplayLobby)) < 0)   /* CoCreateInstance(CLSID_DirectPlayLobby, IID_IDirectPlayLobby3A) */
		return;
	void *lobby = g_dplayLobby;
	u32 size;
	if ((u32)COM(lobby, 0x20, int, u32, void *, u32 *)(lobby, 0, NULL, &size) != 0x8877001e)   /* DPERR_BUFFERTOOSMALL */
		return;
	u8 *conn = IMPORT(0x4a9198, void *, void *)(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc) */
	g_lobbyConnectionBlock = conn;
	if (!conn)
		return;
	lobby = g_dplayLobby;
	if (COM(lobby, 0x20, int, u32, void *, u32 *)(lobby, 0, conn, &size) < 0)   /* GetConnectionSettings */
		return;
	u32 *session = *(u32 **)((*(u8 **)&g_lobbyConnectionBlock) + 8);
	session[1] = 0x44;    /* dwFlags */
	session[10] = 16;     /* dwMaxPlayers */
	lobby = g_dplayLobby;
	if (COM(lobby, 0x30, int, u32, u32, void *)(lobby, 0, 0, g_lobbyConnectionBlock) < 0)   /* SetConnectionSettings */
		return;
	lobby = g_dplayLobby;
	if (COM(lobby, 0x3c, int, u32, const void *, void **, void *)(lobby, 0, (const void *)OBJ(k_IID_IDirectPlay4A), (void **)ADDR(g_dplay), NULL) < 0)
		return;   /* ConnectEx */
	u32 id;
	void *play = g_dplay;   /* CreatePlayer with the lobby's DPNAME (lpPlayerName) */
	if (COM(play, 0x18, int, u32 *, void *, void *, void *, u32, u32)(play, &id, *(void **)((*(u8 **)&g_lobbyConnectionBlock) + 0xc),
			NULL, NULL, 0, 0) < 0)
		return;
	u32 flags = *(u32 *)((*(u8 **)&g_lobbyConnectionBlock) + 4);
	if (flags & 2)
		g_isHost = 1;
	else if (flags & 1)
		g_isHost = 0;
}

/* 0x453790: DirectPlay made: first through a lobby that started the game (dplay_lobbyConnect), then (either way) a plain
   DirectPlay object (dplay_createLobby; its failure returned) and the connections listed (EnumConnections of the game's
   application with dplay_enumConnections). The lobby's settings block is freed (but 0xa0baf4 kept). Returns the
   listing's failure, else 0 */
int (dplay_create)(void)
{
	dplay_lobbyConnect();
	int r = dplay_createLobby((void **)ADDR(g_dplay));   /* dplay_createLobby */
	if (r < 0)
		return r;
	void *play = g_dplay;
	r = COM(play, 0x8c, int, const void *, void *, void *, u32)(play, (const void *)OBJ(k_axisAppGuid), (void *)FN_ADDR(dplay_enumConnections, 0x4532f0), NULL, 0);
	if (r >= 0)
		r = 0;
	if (g_lobbyConnectionBlock)
		global_free(g_lobbyConnectionBlock);
	return r;
}

/* 0x451090: a game message from player `from`, by its type (the first word): 1 a chat line (+0xc) logged into
   0x9fd948 (the old one dropped first; 0x9fd95c raised); 2 the host's id (+4, into 0x9fd94c) with the player slots
   reset (0x454130, then 0x4515a0); 6 our own player slot (byte +4, 0x410 bytes a slot from 0x9f9840) taken, the slot
   noted in 0x9fd954 and 0x9f9838 raised; 7 another player's slot data: the slot taken by `from` if it was free,
   then a 0x40-byte block (size +5, data +9) stored when the size is right. Returns what the original leaves in
   eax */
u32 (net_handleMessage)(const u8 *message, u32 size, u32 from)
{
	(void)size;
	const NetPacketMessage *pm = (const NetPacketMessage *)RELOC(message);   /* (kinds 6 and 7) */
	u32 type = pm->kind;
	u32 slot = pm->slot, length = pm->size;
	NetSlot *player = &g_netSlots[slot];
	int r;
	switch (type) {
	case 1:
		if (g_chatLog)
			g_chatLog = 0;
		r = net_logMessage(from, message + 0xc, (char **)ADDR(g_chatLog));   /* net_logMessage */
		if (r >= 0)
			g_chatLogged = 1;
		return r;
	case 2:
		(*(u32 *)&g_netHostGone) = *(const u32 *)(RELOC(message) + 4);
		net_freeSessionList();
		return net_freeAllSlots();
	case 6:
		net_takePlayerSlot(slot, (*(int *)&g_localPlayerId));
		player->used = 1;
		g_slotTakenFlag = 1;
		g_watchedSlot = (u8)slot;
		return slot;
	case 7:
		if (player->used != 1) {
			net_takePlayerSlot(slot, from);
			player->used = 1;
			player->id = from;
		} else if (length != 0x40)
			return slot * 0x410;
		if (length != 0x40)
			return length;
		player->waiting = 1;
		player->size = length;
		memcpy(player->packet, pm->data, length);
		return length;
	}
	return type - 1;
}

/* 0x453a90: a fresh DirectPlay connection of kind 0 .. 3: the old object closed (dplay_closeSession). The kind picks
   the service provider (0xa0bad8: 0xa0b3a0, 0xa0b450, 0xa0b408, 0xa0bab8) and its stored connection (0xa0badc from
   OBJ(g_dpConnections) + 4 * kind); for TCP/IP (0) a compound address is made instead by the lobby from the provider and the
   host `address` (or 0xa0bb0c), size query then fill, into a new block 0xa0baf0. Then (when there is a connection) a
   new DirectPlay object (dplay_createLobby) initialised with it and its caps kept (timeout, buffer and queue sizes into
   0xa0bb00 .. 0xa0bb08). 0 when that fails, else 1 */
int (dplay_initConnection)(int kind, const char *address)
{
	if (g_dplay) {
		dplay_closeSession(g_dplay);   /* dplay_closeSession */
		g_dplay = NULL;
	}
	static const u32 provider[4] = { OBJ(g_tcpProviderGuid), OBJ(g_ipxProviderGuid), OBJ(g_modemProviderGuid), OBJ(g_serialProviderGuid) };   /* (the GUIDs: TCP, IPX, modem, serial) */
	if ((u32)kind <= 3) {
		(*(u32 *)&g_instanceGuid) = provider[kind];
		(*(u32 *)&g_storedConnection) = GAME_VAR(u32, OBJ(g_dpConnections) + kind * 4);
	}
	if (kind == 0) {
		struct { u32 guid[4], size; const void *data; } element[2];   /* DPCOMPOUNDADDRESSELEMENT */
		char host[0xc0];
		u32 size = 0;
		strcpy(host, address ? address : g_noAddress);
		memcpy(element[0].guid, (const void *)OBJ(k_DPAID_ServiceProvider), 16);   /* DPAID_ServiceProvider */
		element[0].size = 0x10;
		element[0].data = g_instanceGuid;
		memcpy(element[1].guid, (const void *)OBJ(k_DPAID_INet), 16);   /* DPAID_INet */
		element[1].size = strlen(host) + 1;
		element[1].data = host;
		void *lobby = g_dplayLobby;
		COM(lobby, 0x38, int, void *, u32, void *, u32 *)(lobby, element, 2, NULL, &size);   /* CreateCompoundAddress */
		void *block = crt_malloc(size);
		g_hostAddressBlock = block;
		lobby = g_dplayLobby;
		COM(lobby, 0x38, int, void *, u32, void *, u32 *)(lobby, element, 2, block, &size);
		g_storedConnection = g_hostAddressBlock;
	}
	if (!g_storedConnection)
		return 1;
	if (dplay_createLobby((void **)ADDR(g_dplay)) < 0 || !g_dplay)   /* dplay_createLobby */
		return 0;
	void *play = g_dplay;
	if (COM(play, 0x98, int, void *, u32)(play, g_storedConnection, 0) < 0)   /* InitializeConnection */
		return 0;
	u32 caps[10] = { 0x28 };   /* DPCAPS */
	play = g_dplay;
	if (COM(play, 0x38, int, u32 *, u32)(play, caps, 0))   /* GetCaps */
		return 0;
	g_dpTimeout = caps[9];   /* dwTimeout */
	g_dpMaxBufferSize = caps[2];   /* dwMaxBufferSize */
	g_dpMaxQueueSize = caps[3];   /* dwMaxQueueSize */
	return 1;
}

/* a server socket closed: pending Winsock calls cancelled, sends shut down, the socket closed and forgotten, then
   0x4519b0. Returns its eax */
static u32 socket_close(u32 socket)
{
	WSACleanup();                                  /* WSACleanup */
	IMPORT(WS_SHUTDOWN, int, int, int)(GAME_VAR(int, socket), 1);      /* shutdown(SD_SEND) */
	IMPORT(WS_CLOSESOCKET, int, int)(GAME_VAR(int, socket));              /* closesocket */
	GAME_VAR(int, socket) = 0;
	return arena_freeBuffers();
}

/* the leaving player's record (from *from into *to): the leave flag (+0) and the flagged byte, the bytes listed
   copied in order, then three names; sent as message `type` (net_send), then a second's wait */
static int send_leave(u32 from, u32 to, const u8 *bytes, int nbytes, int flagged, const u8 *names, int type, int code)
{
	u8 *dst = GAME_VAR(u8 *, to);
	if (!dst)
		return 0;
	dst[0] = 1;
	for (int i = 0; i < nbytes; i++) {
		if (bytes[i] == flagged)
			GAME_VAR(u8 *, to)[flagged] = 1;
		else
			GAME_VAR(u8 *, to)[bytes[i]] = GAME_VAR(u8 *, from)[bytes[i]];
	}
	for (int i = 0; i < 3; i++)
		lstrcpyA(GAME_VAR(char *, to) + names[i], GAME_VAR(char *, from) + names[i]);
	net_send(type, code);   /* net_send */
	Sleep(1000);                 /* Sleep */
	return 1;
}


/* ---- the info sent to the server when a player comes or goes while hosting over TCP/IP: the room's (0xa0b310 into
   the packet 0xa0b314) or the arena's (0xa0b328 into 0xa0b32c), the player count (0x9fd950) included ---- */

static void room_info(u8 *dst, u8 first, u8 count)
{
	const ServerRecord *src = (*(const ServerRecord **)&g_roomPacket);
	ServerRecord *to = (ServerRecord *)dst;
	to->kind = first;
	to->rotation = src->rotation;
	to->timeLimit = src->timeLimit;
	to->fragLimit = src->fragLimit;
	to->gameMode = src->gameMode;
	to->players = count;
	to->map = src->map;
	to->maxPlayers = src->maxPlayers;
	to->locked = src->locked;
	lstrcpyA(to->password, src->password);
	lstrcpyA(to->address, src->address);
	lstrcpyA(to->name, src->name);
	net_send(0xc, 0x64);
}

static void arena_info(u8 *dst, u8 first, u8 count)
{
	const RoomRecord *src = (*(const RoomRecord **)&g_arenaPacket);
	RoomRecord *to = (RoomRecord *)dst;
	to->kind = first;
	to->rotation = src->rotation;
	to->fragLimit = src->fragLimit;
	to->gameMode = src->gameMode;
	to->players = count;
	to->map = src->map;
	to->maxPlayers = src->maxPlayers;
	to->timeLimit = src->timeLimit;
	to->locked = src->locked;
	lstrcpyA(to->password, src->password);
	lstrcpyA(to->hostName, src->hostName);
	lstrcpyA(to->address, src->address);
	net_send(0x14, 0x65);
}

/* 0x450c20 (DirectPlay system message): 5, a player created: its slot taken by the host (net_freeSlotsOf, unless
   0x9fd94c), then the info sent with the count less one; 3, a player gone: a slot freed (net_claimPlayerSlot into
   0x9f9424, net_sendMessage), the message's count kept and the info sent (an arena's then starts with 1). Only while
   hosting (0xa0baf8) over TCP/IP (0xa0b418 = 0) with the right socket open (200: the room on the lobby's, 201: the
   arena on the game server's) and nothing pending (0xa0b360 / 0xa0b364). The original leaves eax to callers that
   ignore it */
void (net_sendLocalInfo)(const u32 *msg)
{
	int gone;
	if (msg[0] == 5) {
		if (!g_netHostGone)
			net_freeSlotsOf(msg[2]);   /* net_freeSlotsOf */
		gone = 0;
	} else if (msg[0] == 3) {
		if (!g_isHost)
			return;
		(*(u8 *)&g_netClaimedSlot) = net_claimPlayerSlot();
		net_sendMessage((void *)ADDR(g_netSlotMessageKind), msg[2], 0);
		gone = 1;
	} else
		return;
	if (!g_isHost || g_connectionKind)
		return;
	switch (g_lobbyConnectStatus) {
	case 201:
		if (g_gameServerPending || !g_gameServerSocket)
			return;
		if (gone)
			g_playerCount = msg[3];
		if (!g_arenaInfoPacket)
			return;
		if (gone)
			arena_info(g_arenaInfoPacket, 1, (u8)g_playerCount);
		else
			arena_info(g_arenaInfoPacket, (*(const u8 **)&g_arenaPacket)[0], (u8)(g_playerCount - 1));
		break;
	case 200:
		if (g_lobbyPending || !(*(int *)&g_lobbySocket))
			return;
		if (gone)
			g_playerCount = msg[3];
		if (!g_netInfoPacket)
			return;
		room_info(g_netInfoPacket, (*(const u8 **)&g_roomPacket)[0], (u8)(g_playerCount - !gone));
		break;
	}
}

/* a TCP socket into *sock connected to the host 0xa055e4 (a dotted address, else looked up by name) at port
   0xa05326, after Winsock 2.2 starts and the socket is bound to any address; connected: 0xa0b380 = status, 1. A
   refusal (connect's result compared with 10061, as the original does) 2, any failure 0 (Winsock cleaned up and
   the network left where the original does so) */
static int connect_socket(int *sock, int status)
{
	const char *host = g_lobbyHost;
	u8 wsa[0x190];
	if (WSAStartup(0x202, wsa))                /* WSAStartup */
		return 0;
	if (wsa[0] != 2 || wsa[1] != wsa[0]) {
		WSACleanup();
		return 0;
	}
	*sock = ws_socket(2, 1, 0);           /* ws_socket(AF_INET, SOCK_STREAM, 0) */
	if (*sock == -1) {
		WSACleanup();
		net_disconnect();
		return 0;
	}
	struct { u16 family, port; u32 address; u8 zero[8]; } where;          /* sockaddr_in */
	memset(&where, 0, sizeof where);
	where.family = 2;
	if (ws_bind(*sock, &where, 16) == -1)   /* bind */
		return 0;
	where.family = 2;
	where.address = ws_inet_addr(host);      /* inet_addr */
	where.port = ws_htons(g_serverPort); /* htons */
	if (where.address == 0xffffffff) {
		u8 *entry = ws_gethostbyname(host);       /* gethostbyname */
		if (!entry) {
			WSASetLastError(0x2726);                     /* WSASetLastError(WSAEINVAL) */
			return 0;
		}
		where.address = ***(u32 ***)(entry + 0xc);                          /* h_addr_list[0] */
	}
	int r = ws_connect(*sock, &where, 16);   /* connect */
	if (r == 10061 || r == -1) {
		WSACleanup();
		net_disconnect();
		*sock = 0;
		return r == 10061 ? 2 : 0;
	}
	g_lobbyConnectStatus = status;
	return 1;
}

/* 0x451b80: connecting (everything closed first): 100 the lobby's socket (0xa055f8, status 200), 0x65 the game
   server's (0xa05630, status 201); any other mode just 1 */
int (net_connect)(int mode)
{
	net_closeAll(mode);
	g_netConnected = 1;
	if (mode == 100)
		return connect_socket((int *)ADDR(g_lobbySocket), 200);
	if (mode == 0x65)
		return connect_socket((int *)ADDR(g_gameServerSocket), 201);
	return 1;
}

/* 0x451e60: leaving the network (while connected, 0xa0b2fc = 1): on the lobby's socket (0xa055f8) the player's
   leave record (0xa0b310 into 0xa0b318, message 0xb) unless 0xa0b360, on the room's (0xa05630) the room record
   (0xa0b328 into 0xa0b330, message 0x16) unless 0xa0b364; each socket closed. Without a send buffer it stops there
   (0). Then the connection flags cleared. Returns what the original leaves in eax */
u32 (net_disconnect)(void)
{
	static const u8 lobbyBytes[9] = { offsetof(ServerRecord, rotation), offsetof(ServerRecord, fragLimit), offsetof(ServerRecord, timeLimit), offsetof(ServerRecord, gameMode), offsetof(ServerRecord, players), offsetof(ServerRecord, map), offsetof(ServerRecord, maxPlayers), offsetof(ServerRecord, locked) }, lobbyNames[3] = { offsetof(ServerRecord, password), offsetof(ServerRecord, address), offsetof(ServerRecord, name) };
	static const u8 roomBytes[9] = { offsetof(RoomRecord, rotation), offsetof(RoomRecord, fragLimit), offsetof(RoomRecord, gameMode), offsetof(RoomRecord, players), offsetof(RoomRecord, map), offsetof(RoomRecord, maxPlayers), offsetof(RoomRecord, timeLimit), offsetof(RoomRecord, locked) }, roomNames[3] = { offsetof(RoomRecord, password), offsetof(RoomRecord, hostName), offsetof(RoomRecord, address) };
	if (g_netConnected != 1)
		return (*(u32 *)&g_netConnected);
	u32 r = g_lobbySocket;
	if ((*(int *)&g_lobbySocket)) {
		if (!g_lobbyPending && !send_leave(ADDR(g_roomPacket), ADDR(g_lobbyLeavePacket), lobbyBytes, 8, 0x45, lobbyNames, 0xb, 0x64))
			return 0;
		r = socket_close(ADDR(g_lobbySocket));
	}
	if (g_gameServerSocket) {
		if (!g_gameServerPending && !send_leave(ADDR(g_arenaPacket), ADDR(g_roomRecordPacket), roomBytes, 8, 0x63, roomNames, 0x16, 0x65))
			return 0;
		r = socket_close(ADDR(g_gameServerSocket));
	}
	g_netLastRequest = 0;
	g_lobbyConnectStatus = 0;
	g_netConnected = 0;
	return r;
}

/* 0x450bb0, 0x4532e0: jumps to net_receiveAll and net_getLocalAddress (their eax passed on) */
u32 (jmp_net_receiveAll)(void) { return net_receiveAll(); }
int (jmp_net_getLocalAddress)(void) { return net_getLocalAddress(); }

/* ---- packets to the lobby (socket 0xa055f8) and the game server (0xa05630): a kind word, then the kind's buffer ---- */

/* the buffer at the pointer kept at `buffer` sent whole (size bytes) over the socket kept at `socket`, if both are
   there */
static void send_buffer(u32 socket, u32 buffer, int size)
{
	void *data = GAME_VAR(void *, buffer);
	if (data && GAME_VAR(u32, socket))
		ws_send(GAME_VAR(u32, socket), data, size, 0);   /* send */
}

/* 0x4521c0: packet `kind` sent to `to` (100 the lobby, 101 the game server; another value sends only the packet
   itself): its kind word (in 0xa0b30c; none: nothing at all), then the kind's buffer: 10 .. 12 to the lobby (0x5b
   bytes), 13 the hello (the game list cleared), 23 the name (0x10), 14 / 15 the address request (this machine's
   address at +0x60), 17 .. 22 and 24 .. 29 to the game server (19 and 21 / 26 after clearing the server or player
   tables, 22 with its first byte set). Most kinds are kept as the last request (0xa0b300). The callers ignore the
   eax it leaves */
void (net_send)(int kind, int to)
{
	u32 *word = g_netKindWord;
	if (to == 100 || to == 101) {
		if (!word)
			return;
		*word = (u32)kind;
		u32 socket = to == 100 ? ADDR(g_lobbySocket) : ADDR(g_gameServerSocket);
		if (GAME_VAR(u32, socket))
			ws_send(GAME_VAR(u32, socket), (*(void **)&g_netKindWord), 4, 0);
	}
	static const struct { u32 buffer; int size, lobby; } plain[30] = {
		[10] = { ADDR(g_roomPacket), 0x5b, 1 }, [11] = { ADDR(g_lobbyLeavePacket), 0x5b, 1 }, [12] = { ADDR(g_netInfoPacket), 0x5b, 1 },
		[17] = { ADDR(g_netPlayerRecordPacket), 0x36, 0 }, [18] = { ADDR(g_arenaPacket), 0x79, 0 }, [20] = { ADDR(g_arenaInfoPacket), 0x79, 0 },
		[25] = { ADDR(g_netLeaveBuffer), 0x1e, 0 }, [27] = { ADDR(g_netSelectionPacket), 0xb9, 0 }, [28] = { ADDR(g_netAccountBuffer), 0x5c, 0 }, [29] = { ADDR(g_netJoinMessage), 0x1e, 0 } };
	switch (kind) {
	case 10: case 11: case 12: case 17: case 18: case 20: case 27: case 28: case 29:
		g_netLastRequest = kind;
		/* fall through */
	case 25:
		send_buffer(plain[kind].lobby ? ADDR(g_lobbySocket) : ADDR(g_gameServerSocket), plain[kind].buffer, plain[kind].size);
		return;
	case 13:
		net_clearServerList();
		g_netLastRequest = 13;
		send_buffer(ADDR(g_lobbySocket), ADDR(g_netLobbyMessage), 4);
		return;
	case 23: {
		char *name = g_netSendName;
		const char *from = (*(const char **)&g_roomPacket);
		if (!name || !from)
			return;
		strcpy(name, ((const ServerRecord *)from)->address);
		send_buffer(ADDR(g_lobbySocket), ADDR(g_netSendName), 0x10);
		return;
	}
	case 14: case 15:
		g_netLastRequest = kind;
		if (!(*(void **)&g_accountPacket))
			return;
		jmp_net_getLocalAddress();
		lstrcpyA((*(AccountPacket **)&g_accountPacket)->address, g_localAddress);
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_accountPacket), 0x10b);
		return;
	case 19:
		net_clearServers();
		net_clearRoomList();
		g_netLastRequest = 0x13;
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_netRequestWord), 4);
		return;
	case 21:
	case 26:
		net_clearPlayerList();
		if (kind == 21)
			g_netLastRequest = 0x15;
		send_buffer(ADDR(g_gameServerSocket), kind == 21 ? ADDR(g_netRankingBuffer) : ADDR(g_netOneByte), kind == 21 ? 8 : 1);
		return;
	case 22:
		g_netLastRequest = 0x16;
		if (!g_roomRecordPacket)
			return;
		*g_roomRecordPacket = 1;
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_roomRecordPacket), 0x79);
		return;
	case 24:
		jmp_net_getLocalAddress();
		if (!g_netSendBuffer)
			return;
		lstrcpyA(g_netSendBuffer, g_localAddress);
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_netSendBuffer), 0x10);
		return;
	}
}

/* ---- replies to the last request (0xa0b300) ---- */

/* size bytes read from the socket kept at `socket` into buf, again and again until that many have come (1) or 3
   seconds since start have passed (0) */
static int recv_all(u32 socket, void *buf, int size, u32 start)
{
	u32 got = 0;
	for (;;) {
		int n = ws_recv(GAME_VAR(u32, socket), buf, size, 0);   /* recv */
		if (n > 0)
			got += n;
		if (GetTickCount() - start > 3000)
			return 0;
		if (got >= (u32)size)
			return 1;
	}
}

/* a status reply (four bytes into reply): 1 the connection closed, 0 refused, 3 the timeout's code; each ends the
   request and leaves its code in status */
static void status_reply(u32 socket, u32 reply, u32 status, u32 timeout, u32 start)
{
	if (!recv_all(socket, (void *)RELOC(reply), 4, start)) {
		GAME_VAR(int, status) = timeout;
		g_netLastRequest = 0;
	}
	switch (GAME_VAR(int, reply)) {
	case 1:
		GAME_VAR(int, status) = 0x67;
		net_disconnect();
		g_netLastRequest = 0;
		break;
	case 0:
		g_netLastRequest = 0;
		GAME_VAR(int, status) = 0x66;
		break;
	case 3:
		g_netLastRequest = 0;
		GAME_VAR(int, status) = timeout;
		break;
	}
}

/* an answer (0x10b bytes into 0xa05638) from the game server: its code kept in `answer` when it is one of `codes`
   (that ends the request); a timeout leaves 0x28 */
static void answer_reply(u32 answer, const u8 *codes, int count, u32 start)
{
	if (!recv_all(ADDR(g_gameServerSocket), (void *)ADDR(g_netRecvBuffer), 0x10b, start)) {
		GAME_VAR(int, answer) = 0x28;
		g_netLastRequest = 0;
	}
	int code = g_netRecvBuffer;
	for (int k = 0; k < count; k++)
		if (code == codes[k]) {
			g_netLastRequest = 0;
			GAME_VAR(int, answer) = code;
			return;
		}
}

/* 0x452620: the reply to the last request (0xa0b300) read: 10 the lobby's status (0xa055dc into 0xa0b370), 13 the
   list of games, 14 / 15 the game server's answers (kept in 0xa0b378 / 0xa0b37c), 18 its status (0xa0b248 into
   0xa0b374), 19 the server list, 21 the player list, 26 the player list cleared (0xa0b350), 29 a 0x22-byte notice
   (0xa052c0; 0xa0b354 when it is not empty). The callers ignore the eax it leaves */
void (net_recv)(void)
{
	u32 start = GetTickCount();
	static const u8 answers14[6] = { 0x1f, 0x20, 0x21, 0x22, 0x28, 0x2a }, answers15[4] = { 0x1e, 0x21, 0x28, 0x2a };
	switch (g_netLastRequest) {
	case 10:
		status_reply(ADDR(g_lobbySocket), OBJ(g_lobbyReplyCode), ADDR(g_lobbyStatus), 0x29, start);
		break;
	case 13:
		net_receiveLobbyReply();
		break;
	case 14:
		answer_reply(ADDR(g_gameServerAnswer), answers14, 6, start);
		break;
	case 15:
		answer_reply(ADDR(g_gameServerAnswer15), answers15, 4, start);
		break;
	case 18:
		status_reply(ADDR(g_gameServerSocket), OBJ(g_gameServerReplyCode), ADDR(g_gameServerStatus), 0x28, start);
		break;
	case 19:
		net_receiveGameServerReply();
		break;
	case 21:
		net_receiveServerReply();
		break;
	case 26:
		net_clearPlayerList();
		g_playerListRefused = 1;
		g_netLastRequest = 0;
		break;
	case 29:
		recv_all(ADDR(g_gameServerSocket), (void *)ADDR(g_netNotice), 0x22, start);
		if (g_netNotice) {
			g_netNoticeIn = 1;
			g_netLastRequest = 0;
		}
		break;
	}
}

/* The six match packets are built where the original builds them: in the 0x40 bytes straight below the return
   address, which its "sub esp, 0x40" (0x44, 0x48) reserves without writing, so the bytes a packet does not set go
   out as the stack had them. A C local cannot sit there (the saved registers come first), so each sender is an
   entry stub that reserves those bytes the same way and hands them to the C body (thiscall: ecx kept, the
   function's own argument passed on, the packet last). The body's eax is passed back. */
#define PACKET_ENTRY(name, nargs) \
	__asm__(".text\n.globl _" #name "\n_" #name ":\n" \
	        "\tsubl $0x40, %esp\n"                      /* the packet: [entry - 0x40, entry), left as it was */ \
	        "\tpushl %esp\n"                            /* (the value before the push: the packet) */ \
	        ".if " #nargs "\n\tpushl 0x48(%esp)\n.endif\n"   /* the argument, from above the packet */ \
	        "\tcalll _" #name "_body\n" \
	        "\taddl $0x40, %esp\n" \
	        "\tretl $(" #nargs " * 4)\n")

/* a match packet (0x40 bytes) sent and counted (+0x2340c78); while recording (+0x2340d1d 1) the frame (+0x2340d29),
   the camera's actor (+0x234240d), the packet's size and the packet written to the recording (+0x2340d08) */
static void send_packet(u8 *s, u8 *packet)
{
	net_sendPacketData(0x40, packet);
	((Scene *)s)->packetsSent++;
	if (((Scene *)s)->recording == 1) {
		int size = 0x40;
		file_writeScrambled(&((Scene *)s)->recordTime, 4, 1, ((Scene *)s)->replayFile);
		file_writeScrambled(&((Scene *)s)->localPlayer, 4, 1, ((Scene *)s)->replayFile);
		file_writeScrambled(&size, 4, 1, ((Scene *)s)->replayFile);
		file_writeScrambled(packet, 1, size, ((Scene *)s)->replayFile);
	}
}

/* 0x48ead0 (thiscall on the scene): the players' levels sent (a 0x40-byte packet, kind 0xe in its second byte): one
   nibble each for up to 124 players (+0x22ee4c0, 0x28 bytes each, +0x22f0400 of them; two to a byte from the third,
   the even one low), a player in the game (+0 not negative, +0x20 1) its level (+0x24) / 10 + 1, at most 15 (each
   byte cleared at its even player). The frame count (+0x2340c78) goes up; while recording (+0x2340d1d 1) the frame
   (+0x2340d29), the camera's actor (+0x234240d), the packet's size and the packet written to the recording
   (+0x2340d08). Its caller ignores the eax it leaves */
#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))
static void THISCALL __attribute__((used)) net_sendPlayerLevels_body(u8 *s, u8 *packet)
{
	packet[1] = 0xe;
	for (int i = 0; i < SCENE_STAGE(s)->itemCount && i < 0x7c; i++) {
		const MapItem *player = &SCENE_STAGE(s)->items[i];   /* (an item, its level sent) */
		if (i % 2 == 0)
			packet[2 + i / 2] = 0;
		if (player->type < 0 || player->taken != 1)
			continue;
		int level = ftol(player->fade) / 10 + 1;
		if (level > 15)
			level = 15;
		packet[2 + i / 2] |= (u8)(i % 2 ? level << 4 : level);
	}
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendPlayerLevels, 0);
#undef FIELD

/* 0x48e0f0 (thiscall on the scene): player p's info sent once when flagged (+0x234300a + p x 0x10, cleared): packet
   2 (64 bytes, its first byte left as it was): from its PlayerRecord the name, then +0x13 its level, +0x14 its
   team, its actor's emblem, p, the five parts and six items (each + 1), the 30 colour bytes (hue, saturation, value). Sent by send_packet. Its caller ignores the eax it
   leaves */
static void THISCALL __attribute__((used)) net_sendPlayerInfo_body(u8 *s, int p, u8 *packet)
{
	int *flag = &((Scene *)s)->sendFlags[p][1];
	if (!*flag)
		return;
	PlayerRecord *r = &((Scene *)s)->playerRecords[p];
	packet[1] = 2;
	strcpy((char *)packet + 2, r->name);
	packet[0x14] = (u8)r->team;
	packet[0x13] = (u8)r->level;
	packet[0x16] = (u8)p;
	packet[0x15] = (u8)((Scene *)s)->players[p].emblem;
	for (int k = 0; k < 5; k++)
		packet[0x17 + k] = (u8)(r->parts[k] + 1);
	for (int k = 0; k < 6; k++)
		packet[0x1c + k] = (u8)(r->items[k] + 1);
	memcpy(packet + 0x22, (u8 *)r + offsetof(PlayerRecord, partHue), 30);   /* partHue, partSaturation, partValue */
	*flag = 0;
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendPlayerInfo, 1);

/* 0x4532f0: DirectPlay's EnumConnections callback: the service provider's short name kept upper-cased (the 0x80-byte
   slot of the count 0xa0bac8, which counts up to 9), and by its kind (the name containing "TCP", "IPX", "MODEM" or
   its Korean name, "SERIAL" or its Korean name) its GUID (0xa0b3a0, 0xa0b450, 0xa0b408, 0xa0bab8) and a copy of its
   connection data (GlobalAlloc'ed, 0xa0bab0; 0xa0bae0 .. 0xa0baec). Returns 1 (go on) */
u32 STDCALL (dplay_enumConnections)(const u32 *guid, const void *connection, u32 size, const u32 *name, u32 flags, void *context)
{
	static const struct { u32 words[2], guid, data; } kinds[4] = {
		{ { STR(0x4b3e64, "TCP") }, OBJ(g_tcpProviderGuid), OBJ(g_dpConnections) }, { { STR(0x4b3e60, "IPX") }, OBJ(g_ipxProviderGuid), OBJ(g_dpConnections) + 4 },
		{ { STR(0x4b3e58, "MODEM"), STR(0x4b3e50, "\270\360\265\251") }, OBJ(g_modemProviderGuid), OBJ(g_dpConnections) + 8 }, { { STR(0x4b3e48, "SERIAL"), STR(0x4b3e40, "\301\367\267\304") }, OBJ(g_serialProviderGuid), OBJ(g_dpConnections) + 12 } };
	char names[10][0x80];
	char *own = names[g_serviceProviderCount];
	strcpy(own, (const char *)RELOC(name[2]));   /* lpszShortNameA */
	crt_strupr(own);
	u32 *id = operator_new(0x10);
	if (!id)
		return 1;
	memcpy(id, guid, 0x10);
	void *data = g_connectionCopy = IMPORT(0x4a9198, void *, void *)(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!data)
		return 1;
	memcpy(data, connection, size);
	for (int k = 0; k < 4; k++)
		if (text_findWord(own, (const char *)kinds[k].words[0], 1) ||
		    (kinds[k].words[1] && text_findWord(own, (const char *)kinds[k].words[1], 1))) {
			memcpy((void *)RELOC(kinds[k].guid), id, 0x10);
			GAME_VAR(void *, kinds[k].data) = g_connectionCopy;
			break;
		}
	operator_delete(id);
	if (g_serviceProviderCount < 9)
		g_serviceProviderCount++;
	return 1;
}

/* 0x48e680 (thiscall on the scene): the first pending match event (flags at 1, each cleared when taken) sent as its
   packet (kind in the second byte; 0x6b where it carries nothing): 3, 4, 5 (+0x2343237, +0x234323b, +0x234323f); 6 two
   bytes (+0x234324f: +0x2343247, +0x234324b); 7 a byte and a line (+0x234319b: +0x234315a, +0x234315e; and byte
   0x3e from +0x2343197); 8 the same (+0x234314e: +0x234310a, +0x234310e); 9 a byte (+0x2343156: +0x2343152); 10 two
   bytes and a line (+0x23431e7: +0x234319f, +0x23431a3, +0x23431a7); 11 the camera's actor, a byte and a line
   (+0x2343233: +0x23431ef, +0x23431f3); 13 (+0x2343243). With none pending any more the events are done
   (+0x2343106 0). Sent by send_packet (even with nothing pending). Its callers ignore the eax it leaves */
static void THISCALL __attribute__((used)) net_sendMatchEvent_body(u8 *s, u8 *packet)
{
#define SC ((Scene *)s)
#define FLAG(offset) GAME_VAR(int, s + (offset))
#define TAKE(f) ((f) == 1 && ((f) = 0, 1))   /* a pending event taken */
	static const u32 flags[10] = { offsetof(Scene, chatPending), offsetof(Scene, connectPending), offsetof(Scene, quitPending), offsetof(Scene, joinPending), offsetof(Scene, changePending), offsetof(Scene, endEvents[0]), offsetof(Scene, endEvents[1]), offsetof(Scene, endEvents[2]), offsetof(Scene, event6Pending), offsetof(Scene, event13Pending) };
	if (TAKE(SC->endEvents[0]))
		packet[1] = 3, packet[2] = 0x6b;
	else if (TAKE(SC->endEvents[1]))
		packet[1] = 4, packet[2] = 0x6b;
	else if (TAKE(SC->endEvents[2]))
		packet[1] = 5, packet[2] = 0x6b;
	else if (TAKE(SC->event6Pending))
		packet[1] = 6, packet[2] = (u8)SC->event6A, packet[3] = (u8)SC->event6B;
	else if (SC->chatPending == 1) {
		packet[1] = 7;
		packet[2] = (u8)SC->chatPlayer;
		strcpy((char *)packet + 3, (const char *)SC->chatLine);
		SC->chatPending = 0;
		packet[0x3c] = (u8)SC->chatTeam;
	} else if (SC->connectPending == 1) {
		packet[1] = 8;
		packet[2] = (u8)SC->connectPlayer;
		strcpy((char *)packet + 3, (const char *)SC->connectName);
		SC->connectPending = 0;
	} else if (TAKE(SC->quitPending))
		packet[1] = 9, packet[2] = (u8)SC->quitPlayer;
	else if (SC->joinPending == 1) {
		packet[1] = 10;
		packet[2] = (u8)SC->joinPlayer;
		packet[3] = (u8)SC->joinTeam;
		strcpy((char *)packet + 4, (const char *)SC->joinName);
		SC->joinPending = 0;
	} else if (SC->changePending == 1) {
		packet[1] = 11;
		packet[2] = (u8)SC->localPlayer;
		packet[3] = (u8)SC->changeTeam;
		strcpy((char *)packet + 4, (const char *)SC->changeName);
		SC->changePending = 0;
	} else if (TAKE(SC->event13Pending))
		packet[1] = 13, packet[2] = 0x6b;
	int pending = 0;
	for (int k = 0; k < 10; k++)
		pending |= FLAG(flags[k]) != 0;
	if (!pending)
		SC->noticeChanged = 0;
	send_packet(s, packet);
#undef FLAG
#undef TAKE
#undef SC
}
PACKET_ENTRY(net_sendMatchEvent, 0);

/* 0x48e990 (thiscall on the scene): player p's emblem sent in pieces (packet 0xc, p): when it is in the atlas or
   changed (its record's flagShown, emblemChanged) the position reached (emblemSent, as a short) and the 16 pixels from
   there (their RGB, 3 bytes each), the position then 16 on; else 0xffff and the position back to 0x180 (all sent).
   Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendColourRing_body(u8 *s, int p, u8 *packet)
{
	PlayerRecord *pr = &((Scene *)s)->playerRecords[p];
	packet[1] = 0xc;
	packet[2] = (u8)p;
	if (pr->flagShown == 1 || pr->emblemChanged == 1) {
		int at = pr->emblemSent;
		memcpy(packet + 3, &at, 2);
		for (int k = 0; k < 16; k++)
			memcpy(packet + 5 + k * 3, (u8 *)pr->emblem + (at + k) * 4, 3);
		pr->emblemSent = at + 16;
	} else {
		packet[3] = packet[4] = 0xff;
		pr->emblemSent = 0x180;
	}
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendColourRing, 1);

/* a float in memory times a constant, truncated (the original's __ftol) */
static int scaled(const void *v, u32 k)
{
	return ftol(fmul_m(fld_m((const float *)RELOC(v)), (const float *)RELOC(k)));
}

/* an angle wrapped into a turn (angle_wrap, given the float's bits) times 0x4aa49c, truncated */
static int angle_byte(const void *v)
{
	return ftol(fmul_m(FUN_0046c100_bits(*(const u32 *)RELOC(v)), k_0_0711111f));
}

/* 0x48e2c0 (thiscall on the game): player p's state sent (packet 0; the actor at +0x1ecca70 + p x 0x8888): its
   flags word (+0x3f0), a byte of p and its mode (+0x3ec: 0 with +0x140, 1, 2; bit 0 in play +0x14c), the position
   (+0x180, x 0x4a93ec, words), two angles (+0x18c, +0x190) and two tilts (+0x194, +0x198), two nibbles (+0x19c,
   +0x1a4), a third angle (+0x1a0); a pending hit (+0x8850: cleared) as 0x80 alive / 0xc0 dead with the attacker
   (+0x4c0) and value (+0x4c4); then its five shot slots (+0x360, nine bytes each): a slot whose shot (0x4e8 bytes
   from +0x22225fc) is gone is cleared (-1); else flags (1, 3 for a new one: +0x1fc + slot x 0x20 cleared; 4 aimed
   at an actor, 8 still flying), the target (+0xb8, or the object's index + 1, or 0) and the position (+0x60 while
   it flies at an object, else +0x84). Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendPlayerState_body(u8 *g, int p, u8 *packet)
{
	u8 *a = (u8 *)&((Scene *)g)->players[p];
	Player *pl = (Player *)a;
	u16 w;
	packet[1] = 0;
	memcpy(packet + 2, &pl->timerFlags, 2);
	switch (pl->statusIcon) {
	case 0: packet[4] = (u8)((((u8)p << 3) | (u8)pl->slot) << 1); break;
	case 1: packet[4] = (u8)(p << 4 | 0xc); break;
	case 2: packet[4] = (u8)(p << 4 | 0xe); break;
	}
	if (pl->state == 1)
		packet[4] |= 1;
	for (int c = 0; c < 3; c++) {
		w = (u16)scaled(&pl->nextPos[c], ADDR(k_tenthsToDegrees));
		memcpy(packet + 5 + c * 2, &w, 2);
	}
	packet[0xb] = (u8)angle_byte(&pl->nextPitch);
	packet[0xc] = (u8)angle_byte(&pl->nextYaw);
	packet[0xd] = (u8)scaled(&pl->nextForward, ADDR(k_10f));
	packet[0xe] = (u8)scaled(&pl->nextStrafe, ADDR(k_10f));
	packet[0xf] = (u8)(scaled(&pl->nextClimb, ADDR(k_clockRate3)) << 4) | (u8)scaled(&pl->nextRun, ADDR(k_clockRate3));
	packet[0x10] = (u8)angle_byte(&pl->nextLean);
	packet[0x11] = 0;
	if (pl->hitPending == 1) {
		u8 state = pl->armor > 0 ? 0x80 : 0xc0;
		pl->hitPending = 0;
		packet[0x11] = state | (u8)pl->lastAttacker;
		packet[0x12] = (u8)pl->lastHitWeapon;
	}
	for (int k = 0; k < 5; k++)
		packet[0x13 + k * 9] = 0;
	for (int k = 0; k < 5; k++) {
		int *slot = &((Player *)a)->shotBullets[k], *fresh = &((Player *)a)->shots[k].isNew;
		u8 *o = packet + 0x13 + k * 9;
		if (*slot < 0)
			continue;
		u8 *shot = (u8 *)&SCENE_STAGE(g)->bullets[*slot];
		if (((Bullet *)shot)->active != 1) {
			*slot = -1;
			continue;
		}
		if (*fresh == 1) {
			o[0] |= 3;
			*fresh = 0;
		} else
			o[0] |= 1;
		if (((Bullet *)shot)->hitActor >= 0) {
			o[0] |= 4;
			w = (u16)((Bullet *)shot)->hitActor;
		} else if ((*(void * *)&((Bullet *)shot)->hit))
			w = (u16)(array_indexOf((*(void * *)&((Bullet *)shot)->hit), (int)SCENE_STAGE(g)->space.planes.records, 0xac) + 1);
		else
			w = 0;
		memcpy(o + 1, &w, 2);
		int flying = ((Bullet *)shot)->age > ((Bullet *)shot)->life;
		if (flying)
			o[0] |= 8;
		u8 *at = (u8 *)(flying && (*(void * *)&((Bullet *)shot)->hit) ? ((Bullet *)shot)->end : ((Bullet *)shot)->pos);
		for (int c = 0; c < 3; c++) {
			w = (u16)scaled(at + c * 4, ADDR(k_tenthsToDegrees));
			memcpy(o + 3 + c * 2, &w, 2);
		}
	}
	send_packet(g, packet);
}
PACKET_ENTRY(net_sendPlayerState, 1);

/* the next value of the game's table of rand() values (0xa106f8, 4096 of them; the position 0xa1efb8 moves on) */
static u32 table_rand(void)
{
	u32 at = g_randPos;
	g_randPos = at + 1;
	return GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4);
}

/* a random entry of one of the level's geometry tables (rows of row_len dwords from base, rows of them at +rows,
   n per row at +per_row): its random position (a 16-bit word, below 100000 before it was cut) into *at, the entry
   returned */
static u32 sample(u8 *s, u32 per_row, u32 rows, int row_len, u32 base, u8 *at)
{
	u16 r = (u16)(table_rand() % 100000);
	memcpy(at, &r, 2);
	int n = GAME_VAR(int, s + per_row);
	int row = r / n % GAME_VAR(int, s + rows);
	return GAME_VAR(u32, s + base + (row * row_len + r % n) * 4);
}

/* 0x48dbf0 (thiscall on the scene): player p's game packet (1), sent when flagged (+0x2343006 + p x 0x10, cleared):
   the room's game (its map and modes from +0x1f1668 / +0x1f1cb4 ..; 0xff and 0xffff without one, or once the start
   countdown +0x234239d is running), the clock (+0x22f0408, +0x22f040c), the player's two scores (+0x1eccb6c,
   +0x1eccb70 of its actor), which of the players in use (net_playerInUse) were flagged twice (+0x234300e,
   +0x2343012: cleared, one bit each), the actor's two counts (+0x1eccb54 / 58) and the team scores (+0x2221fb8 /
   bc), the kill notice (+0x22f0404, set back to -1), then two random checks of the level: one of the five geometry
   tables in turn (+0x23423c9 counting; its number in byte 0x2b) and the sixth, each a position and the entry there.
   Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendGamePacket_body(u8 *s, int p, u8 *packet)
{
	static const struct { u32 per_row, rows; int row_len; u32 base; } tables[5] = {
		{ 0x23423e5, 0x15de6c8, 682, 0x15bd1f8 }, { 0x23423e9, 0x15fff84, 687, 0x15de6cc },
		{ 0x23423ed, 0x163b588, 0x4c0, 0x15fff88 }, { 0x23423f1, 0x1679b34, 1277, 0x163b58c },
		{ 0x23423f5, 0x16c5178, 1544, 0x1679b38 } };
	int *flag = &((Scene *)s)->sendFlags[p][0];
	if (!*flag)
		return;
	packet[1] = 1;
	packet[2] = (u8)p;
	if (((Scene *)s)->rotationCount > 0 && !(((Scene *)s)->endTime > k_0f)) {
		int k = ((Scene *)s)->rotationAt * 16;
		packet[3] = s[0x1f1668 + k];
		packet[4] = s[0x1f1cb4];
		packet[5] = s[0x1f166c + k];
		packet[6] = s[0x1f1cb8];
		memcpy(packet + 7, &((Scene *)s)->missionNumber, 2);
	} else
		memset(packet + 3, 0xff, 6);
	memcpy(packet + 9, &((Scene *)s)->elapsed, 4);
	float clock = f32(fld_m(&((Scene *)s)->timeFraction));
	memcpy(packet + 0xd, &clock, 4);
	u32 turn = ((u32)((Scene *)s)->geometryCheckTurn);
	packet[0x2b] = (u8)(turn % 5);
	((Scene *)s)->geometryCheckTurn = turn + 1;
	u32 v = sample(s, tables[packet[0x2b]].per_row, tables[packet[0x2b]].rows, tables[packet[0x2b]].row_len, tables[packet[0x2b]].base,
	               packet + 0x2c);
	memcpy(packet + 0x2e, &v, 4);
	v = sample(s, 0x23423f9, 0x175522c, 2950, 0x16c517c, packet + 0x32);
	memcpy(packet + 0x34, &v, 4);
	memcpy(packet + 0x11, &((Scene *)s)->players[p].timePlayed, 4);
	memcpy(packet + 0x15, &((Scene *)s)->players[p].timeExtra, 4);
	u32 twice[2] = { 0, 0 };
	for (int i = 0; i < 16; i++) {
		if (net_playerInUse(i) != 1)
			continue;
		for (int k = 0; k < 2; k++) {
			int *f = &((Scene *)s)->sendFlags[i][2 + k];
			if (*f == 1) {
				*f = 0;
				twice[k] |= 1u << i;
			}
		}
	}
	memcpy(packet + 0x19, twice, 8);
	memcpy(packet + 0x21, &((Scene *)s)->players[p].kills, 2);
	memcpy(packet + 0x23, &((Scene *)s)->players[p].deaths, 2);
	memcpy(packet + 0x25, &((Scene *)s)->teamScores[0], 2);
	memcpy(packet + 0x27, &((Scene *)s)->teamScores[1], 2);
	memcpy(packet + 0x29, &SCENE_STAGE(s)->lastPickup, 2);
	SCENE_STAGE(s)->lastPickup = -1;
	*flag = 0;
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendGamePacket, 1);

#define G(type, offset) GAME_VAR(type, g + (offset))
#define GS ((Scene *)g)   /* the same by its fields (src/scene.fields) */
#define K(address) ((const float *)RELOC(address))
#define STAGE ((u8 *)SCENE_STAGE(g))
#define ACTOR(i) ((u8 *)&((Scene *)g)->players[i])   /* the stage's actors, from the game object */
#define PLAYER(i) ((u8 *)&((Scene *)g)->playerRecords[i])
#define CALL1(addr, a) GAME_THISCALL(addr, void, void *, int)(STAGE, a)

/* thiscall fn(self, a1 .. a8), returning what the callee leaves in ecx (the original pushes registers whose upper
   bytes are the callee's leftovers) */
__attribute__((naked)) static u32 thiscall8_ecx(u32 fn, void *self, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5, u32 a6, u32 a7, u32 a8)
{
	__asm__("push %ebx\n\t"
	        "mov 8(%esp), %ebx\n\t"
	        "mov 12(%esp), %ecx\n\t"
	        "pushl 44(%esp)\n\tpushl 44(%esp)\n\tpushl 44(%esp)\n\tpushl 44(%esp)\n\t"
	        "pushl 44(%esp)\n\tpushl 44(%esp)\n\tpushl 44(%esp)\n\tpushl 44(%esp)\n\t"
	        "call *%ebx\n\t"
	        "mov %ecx, %eax\n\t"
	        "pop %ebx\n\t"
	        "ret");
}

/* x 10 (a packed position) */
static float tens(int v) { return f32(fmul_m((long double)v, K(0x4a9418))); }

/* a table entry's checksum against the packet's: word w into a table of 'per' columns (count, stride) */
static int table_ok(u8 *g, u32 base, u32 per, u32 count, int stride, u16 w, u32 sum)
{
	int n = G(int, per);
	int row = (int)w / n % G(int, count);
	return G(u32, base + (row * stride + (int)w % n) * 4) == sum;
}

/* a player's name copied into its actor (+0x98) and the slot's own index noted (+0x10c) */
static void actor_name(u8 *g, int i, const char *name)
{
	char *to = ((Player *)ACTOR(i))->name;
	if (name)
		strcpy(to, name);
	else
		to[0] = 0;
	((Player *)ACTOR(i))->player = i;
}

/* team change (kinds 10 / 11): the team, team colours when team colours are on, the name, the notice; a player
   leaving the teams (negative) who is alive is taken out and gets a death */
static void team_change(u8 *g, int i, const char *pkt, u32 notice)
{
	player_setTeam(STAGE, i, pkt[3]);   /* player_setTeam */
	if (GS->teamGame == 1) {
		int t = scene_teamSide(g, pkt[3]);
		for (int k = 0; k < 5; k++)
			GAME_THISFN(actor_setPartColor, 0x474b50, void, void *, int, int, u32, u32, u32, u32, u32, u32)(STAGE, i, k, GAME_VAR(u32, 0x4a97fc + t * 4),
			                                                                             GAME_VAR(u32, 0x4a9810 + t * 4),
			                                                                             GAME_VAR(u32, 0x4a9824 + t * 4), 0,
			                                                                             0xbf800000, 0x3f7fbe77);   /* actor_setPartColor */
	}
	player_setName(STAGE, i, pkt + 4);   /* player_setName */
	actor_name(g, i, pkt + 4);
	GAME_THISCALL(notice, void, void *, int, int)(g, i, pkt[3]);
	if (pkt[3] >= 0 || ((Player *)ACTOR(i))->statD8 != 1)
		return;
	actor_deactivate(STAGE, i);   /* actor_deactivate */
	((Player *)ACTOR(i))->deaths++;
}

/* the end of a match's limit (kinds 4 / 5, state 0 frags or 1 time): once, its notice, and the result for team
   play (the red team's score +0x2221fb8 against the blue +0x2221fbc: 0 red ahead, 1 blue, -1 level) */
static void match_limit(u8 *g, int state, u32 notice)
{
	if (GS->elapsed <= 0x1e || GS->endedByTime == state)
		return;
	GS->endedByTime = state;
	GAME_THISCALL(notice, void, void *)(g);
	if (GS->matchOver)
		return;
	if (GS->teamGame == 1) {
		int red = GS->teamScores[0], blue = GS->teamScores[1];
		GS->winnerTeam = red > blue ? 0 : red < blue ? 1 : -1;
	}
	GS->matchOver = 1;
	GS->endTime = 10.0f;   /* 10 s */
}

/* 0x48c830 (thiscall on the game object): a network packet (type 0x40 only) from a player. When recording
   (+0x2340d1d) it goes to the replay file first; while the game is starting (+0x233cc20 1) only kind 1. By the kind
   (byte 1): 0 a player's state (position, aim, weapon, lights, the five weapon slots; a player not yet set up is
   asked for); 1 the game state (round, time, map change, the checksums of the part and item tables, scores, items);
   2 a player joining with his mech; 3 the server ending the game; 4 / 5 the frag / time limit; 6 a cheat notice; 7
   a chat line; 8 a player connecting; 9 one leaving; 10 / 11 team changes; 12 a player's emblem rows; 13 a pause
   timer; 14 the items' states. Anything else goes to 0x48b420 (nothing) */
void THISCALL (net_processGamePacket)(u8 *g, u32 from, int type, const char *pkt)
{
	if (type != 0x40)
		return;
	if (GS->recording == 1) {
		void *f = GS->replayFile;
		GAME_FN(file_writeScrambled, 0x46cc30, void, const void *, int, int, void *)((u8 *)&GS->recordTime, 4, 1, f);
		GAME_FN(file_writeScrambled, 0x46cc30, void, const void *, int, int, void *)(&from, 4, 1, f);
		GAME_FN(file_writeScrambled, 0x46cc30, void, const void *, int, int, void *)(&type, 4, 1, f);
		GAME_FN(file_writeScrambled, 0x46cc30, void, const void *, int, int, void *)(pkt, 1, type, f);
	}
	if (GS->inputState == 1 && pkt[1] != 1)
		return;
	const u8 *b = (const u8 *)pkt;
	switch (b[1]) {
	case 0: {
		int weapon = (b[4] >> 1) & 7, i = b[4] >> 4;
		float x = tens(*(const short *)(pkt + 5)), y = tens(*(const short *)(pkt + 7)), z = tens(*(const short *)(pkt + 9));
		long double h = fmul_m((long double)b[0xb], K(0x4aa494));
		float yaw = f32(h);
		if (h > *K(0x4aa288))
			yaw = f32(fsub_m(fld_m(&yaw), K(0x4a94c8)));
		float pitch = f32(fmul_m((long double)b[0xc], K(0x4aa494)));
		if (GAME_VAR(int, PLAYER(i)) == 0) {
			GS->sendFlags[GS->localPlayer][0] = 1;
			GS->sendFlags[i][2] = 1;
			return;
		}
		u8 *ac = ACTOR(i);
		if ((*(const u16 *)&((Player *)ac)->timerFlags ^ *(const u16 *)(pkt + 2)) & 0x4000)
			actor_deactivate(STAGE, i);   /* actor_deactivate */
		if (((Player *)ac)->active == 0 && (b[4] & 1)) {
			u32 rec[7] = { (u32)i, 0 };
			memcpy(&rec[2], &x, 4);
			memcpy(&rec[3], &y, 4);
			memcpy(&rec[4], &z, 4);
			memcpy(&rec[5], &yaw, 4);
			memcpy(&rec[6], &pitch, 4);
			GAME_THISFN(stage_setupActorSlot, 0x45dc00, void, void *, int, int, u32, u32 *)(STAGE, i, -1, from, rec);
			msg_newKing(g);   /* msg_newKing */
		}
		((Player *)ac)->netFired = 1;
		((Player *)ac)->armorDeadline = f32(fadd_m(fld_m(&((Player *)ac)->blinkTime), K(0x4a9418)));
		BITS(((Player *)ac)->timerFlags) = *(const u16 *)(pkt + 2);
		if (weapon == 6)
			((Player *)ac)->statusIcon = 1;
		else if (weapon == 7)
			((Player *)ac)->statusIcon = 2;
		else {
			((Player *)ac)->statusIcon = 0;
			actor_setWeaponSlot(STAGE, i, weapon);   /* actor_setWeaponSlot */
		}
		((Player *)ac)->netPos[0] = x;
		((Player *)ac)->netPos[1] = y;
		((Player *)ac)->netPos[2] = z;
		((Player *)ac)->netPitch = yaw;
		((Player *)ac)->netYaw = pitch;
		((Player *)ac)->netMotion[0] = f32(fmul_m((long double)(signed char)b[0xd], K(0x4a955c)));
		((Player *)ac)->netMotion[1] = f32(fmul_m((long double)(signed char)b[0xe], K(0x4a955c)));
		((Player *)ac)->netMotion[2] = f32(fmul_m((long double)(b[0xf] >> 4), K(0x4aa490)));
		((Player *)ac)->netMotion[4] = f32(fmul_m((long double)(b[0xf] & 0xf), K(0x4aa490)));
		h = fmul_m((long double)b[0x10], K(0x4aa48c));
		((Player *)ac)->netMotion[3] = f32(h);
		if (h > *K(0x4aa288))
			((Player *)ac)->netMotion[3] = f32(fsub_m(h, K(0x4a94c8)));
		int hurt;
		if (b[0x11] & 0x80) {
			((Player *)ac)->lastAttacker = b[0x11] & 0xf;
			((Player *)ac)->lastHitWeapon = b[0x12];
			hurt = 1;
			if ((b[0x11] & 0x40) && ((Player *)ac)->armor > 0)
				((Player *)ac)->armor = 0;
		} else {
			hurt = !(b[4] & 1) && ((Player *)ac)->armor > 0;
			if (hurt)
				((Player *)ac)->armor = 0;
		}
		if (hurt)
			BITS(((Player *)ac)->hitFlash) = 0x3f000000;
		const u8 *w = b + 0x13;
		for (int k = 0; k < 5; k++, w += 9) {
			u32 *slot = (u32 *)&((Player *)ac)->shots[k];
			if (!(w[0] & 1) || ((Player *)ac)->team < 0) {
				slot[0] = 0;
				continue;
			}
			slot[0] = 1;
			slot[1] = (w[0] >> 1) & 1;
			u16 v = *(const u16 *)(w + 1);
			if (w[0] & 4) {
				slot[2] = v;
				slot[3] = (u32)-1;
			} else {
				slot[2] = (u32)-1;
				slot[3] = v - 1;
			}
			slot[4] = w[0] & 8 ? 1 : 0;
			float p[3] = { tens(*(const short *)(w + 3)), tens(*(const short *)(w + 5)), tens(*(const short *)(w + 7)) };
			memcpy(&slot[5], p, 12);
		}
		return;
	}
	case 1: {
		if (b[2] > 0x10 || pkt[3] < -1 || pkt[4] < -1 || pkt[5] < -1 || pkt[6] < -1)
			break;
		if (b[2] == 0) {
			GS->elapsed = *(const u32 *)(pkt + 9);
			BITS(GS->timeFraction) = *(const u32 *)(pkt + 0xd);
			if (pkt[3] >= 0) {
				int round = g_missionStage;
				if (round != pkt[3] && (round < 0 || GS->rotationOff == 1 || GS->elapsed > 0x1e)) {
					g_missionStage = pkt[3];
					GS->nextMap = pkt[4];
					GS->nextMode = pkt[6];
					scene_setTextureFolder((Scene *)g, g_mapNames + g_missionStage * 0x20);
					GS->inputState = 1;
					GS->modeStarted = 0;
					game_setGameTypeFlags((Stage *)STAGE, pkt[5]);
					GS->rotationOff = 0;
					return;
				}
				GS->nextMap = pkt[4];
				GS->nextMode = pkt[6];
				if (g_missionStage == pkt[3] && GS->missionNumber != *(const short *)(pkt + 7)) {
					GS->roundClear2 = 1;
					GS->dataLossCode = 1;
				}
			}
			static const u32 parts[5][4] = {   /* each part kind's type table, its entries a row, its count, its record in dwords */
				{ SCENE_STAGE_AT + offsetof(Stage, headTypes), offsetof(Scene, geometryPerRow[0]), offsetof(Scene, headCount), sizeof(HeadType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, chestTypes), offsetof(Scene, geometryPerRow[1]), offsetof(Scene, chestCount), sizeof(ChestType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, armTypes), offsetof(Scene, geometryPerRow[2]), offsetof(Scene, armCount), sizeof(ArmType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, legTypes), offsetof(Scene, geometryPerRow[3]), offsetof(Scene, legCount), sizeof(LegType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, boosterTypes), offsetof(Scene, geometryPerRow[4]), offsetof(Scene, boosterCount), sizeof(BoosterType) / 4 } };
			u16 w = *(const u16 *)(pkt + 0x2c);
			int part = b[0x2b];
			if (part <= 4 && !table_ok(g, parts[part][0], parts[part][1], parts[part][2], parts[part][3], w, *(const u32 *)(pkt + 0x2e))) {
				GS->roundClear2 = 1;
				GS->dataLossCode = 2;
			}
			if (!table_ok(g, offsetof(Scene, actorInfo), offsetof(Scene, geometryPerRow[5]), offsetof(Scene, actorInfoCount), sizeof(ActorInfo) / 4, *(const u16 *)(pkt + 0x32), *(const u32 *)(pkt + 0x34))) {
				GS->roundClear2 = 1;
				GS->dataLossCode = 3;
			}
		}
		u8 *ac = ACTOR(b[2]);
		((Player *)ac)->timePlayed = *(const u32 *)(pkt + 0x11);
		BITS(((Player *)ac)->timeExtra) = *(const u32 *)(pkt + 0x15);
		int me = GS->localPlayer;
		if (*(const u32 *)(pkt + 0x19) & 1u << (me & 0x1f))
			GS->sendFlags[me][1] = 1;
		if (*(const u32 *)(pkt + 0x1d) & 1u << (me & 0x1f))
			((PlayerRecord *)PLAYER(me))->emblemSent = 0;
		((Player *)ACTOR(b[2]))->kills = *(const short *)(pkt + 0x21);
		((Player *)ACTOR(b[2]))->deaths = *(const short *)(pkt + 0x23);
		if (b[2] == 0) {
			GS->teamScores[0] = *(const short *)(pkt + 0x25);
			GS->teamScores[1] = *(const short *)(pkt + 0x27);
		}
		short item = *(const short *)(pkt + 0x29);
		if ((GS->network != 3 || GS->replayVersion > 0x1201) && item >= 0 && SCENE_STAGE(g)->items[item].taken == 0) {
			SCENE_STAGE(g)->items[item].taken = 1;
			BITS(SCENE_STAGE(g)->items[item].fade) = 0;
		}
		if (GS->network == 3 && GS->replayVersion >= 0x1202)
			msg_newKing(g);   /* msg_newKing */
		return;
	}
	case 2: {
		const char *name = pkt + 2;
		const u8 *m = b + 2;   /* the record after the name's 0x11 bytes */
		int i = m[0x14], lim = GS->actorInfoCount;
		if (strlen(name) >= 0x11 || (signed char)m[0x11] < 0 || (signed char)m[0x11] > 8 || i >= 0x10 || m[0x15] > GS->headCount ||
		    m[0x16] > GS->chestCount || m[0x17] > GS->armCount || m[0x18] > GS->legCount || m[0x19] > GS->boosterCount)
			break;
		int bad = 0;
		for (int k = 0; k < 6; k++)
			bad |= m[0x1a + k] > lim;
		if (bad)
			break;
		((Player *)ACTOR(i))->player = i;
		player_setName(STAGE, i, name);   /* player_setName */
		player_setValue(STAGE, i, (signed char)m[0x11]);
		player_setTeam(STAGE, i, (signed char)m[0x12]);   /* player_setTeam */
		static const u32 setters[5] = { FN_ADDR(actor_setActorTypeHeadInfoBy, 0x473b10), FN_ADDR(actor_setActorTypeChestInfoBy, 0x473c20), FN_ADDR(actor_setActorTypeArmInfoBy, 0x473d30), FN_ADDR(actor_setActorTypeLegInfoBy, 0x473e40), FN_ADDR(actor_setActorTypeBoosterInfoBy, 0x473f50) };   /* head .. booster */
		for (int k = 0; k < 5; k++)
			GAME_THISCALL(setters[k], int, void *, int, int)(STAGE, i, m[0x15 + k] - 1);
		for (int k = 0; k < 6; k++)
			actor_setActorTypeItemInfoBy(STAGE, i, k, m[0x1a + k] - 1);   /* actor_setActorTypeItemInfoBy */
		((Player *)ACTOR(i))->emblem = (signed char)m[0x13];
		char *to = ((Player *)ACTOR(i))->name;
		if (name)
			strcpy(to, name);
		else
			to[0] = 0;
		((Player *)ACTOR(i))->levelShown = ((Player *)ACTOR(i))->emblem;
		const u8 *c = m + 0x2b;
		/* (the original loads each colour byte into al / cl and pushes the whole register: on the first part the
		   rest of eax is left from the actor's address and of ecx from its +0xdc; later eax holds the player and ecx what
		   the call left) */
		u32 hi_a = (u32)(g + i * 0x8888) & ~0xffu, hi_c = *(u32 *)&((Player *)ACTOR(i))->emblem & ~0xffu;
		for (int k = 0; k < 5; k++, c += 2) {
			u32 left = thiscall8_ecx(FN_ADDR(actor_applyRemoteColours, 0x474fd0), STAGE, i, k, hi_c | c[-0xb], hi_a | c[-1], hi_c | c[9], hi_a | c[-0xa], hi_c | c[0],
			                         hi_a | c[0xa]);   /* actor_applyRemoteColours */
			hi_a = 0;
			hi_c = left & ~0xffu;
		}
		if (((PlayerRecord *)PLAYER(i))->team >= 0)
			player_markUsed(STAGE, i);
		return;
	}
	case 3:
		if (pkt[2] != 'k')
			break;
		if (GS->endedByTime == 2)
			return;
		GS->endedByTime = 2;
		msg_serverEndsGame(g);
		if (GS->roundOver)
			return;
		GS->roundOver = 1;
		GS->quitDelay = 3.0f;
		g_matchEndedByServer = 1;
		return;
	case 4:
		if (pkt[2] != 'k')
			break;
		match_limit(g, 0, FN_ADDR(msg_fragLimitReached, 0x462f90));
		return;
	case 5:
		if (pkt[2] != 'k')
			break;
		match_limit(g, 1, FN_ADDR(msg_timeLimitReached, 0x462fd0));
		return;
	case 6:
		if (b[2] > 0x10)
			break;
		msg_cheatUsed(g, b[2], b[3]);
		return;
	case 7:
		if (b[2] > 0x10 || strlen(pkt + 3) >= 0x39)
			break;
		msg_chatLine(g, b[2], pkt + 3, pkt[0x3c]);
		return;
	case 8:
		if (b[2] > 0x10 || strlen(pkt + 3) >= 0x11)
			break;
		playerRecord_markFree(STAGE, b[2]);   /* playerRecord_markFree */
		player_setName(STAGE, b[2], pkt + 3);   /* player_setName */
		actor_resetSlot(STAGE, b[2]);   /* actor_resetSlot */
		actor_name(g, b[2], pkt + 3);
		GS->sendFlags[GS->localPlayer][1] = 1;
		msg_playerConnected(g, b[2]);
		if (GS->client == 0)
			net_sendPlayerLevels(g);   /* net_sendPlayerLevels */
		return;
	case 9:
		if (b[2] > 0x10)
			break;
		msg_playerLeft(g, b[2]);   /* msg_playerLeft */
		playerRecord_markFree(STAGE, b[2]);
		actor_resetSlot(STAGE, b[2]);
		((PlayerRecord *)PLAYER(b[2]))->name[0] = 0;
		((PlayerRecord *)PLAYER(b[2]))->team = -1;
		actor_deactivate(STAGE, b[2]);   /* actor_deactivate */
		return;
	case 10:
		if (b[2] >= 0x10)
			break;
		team_change(g, b[2], pkt, FN_ADDR(msg_playerJoinedTeam, 0x462d30));
		return;
	case 11:
		if (pkt[2] >= 0x10)
			break;
		team_change(g, pkt[2], pkt, FN_ADDR(msg_playerChangedTeam, 0x462e30));
		return;
	case 12: {
		short row = *(const short *)(pkt + 3);
		if (pkt[2] > 0x10 || row > 0x170)
			break;
		PlayerRecord *p = (PlayerRecord *)PLAYER(pkt[2]);
		if (row >= 0) {
			u8 *to = (u8 *)p->emblem + row * 4;   /* (16 pixels from pixel row: the grid as one run) */
			const u8 *from3 = b + 5;
			for (int k = 0; k < 16; k++, from3 += 3, to += 4) {
				to[0] = from3[0];
				to[1] = from3[1];
				to[2] = from3[2];
				to[3] = from3[0] || from3[1] || from3[2] ? 0xff : 0;
			}
		}
		if (p->emblemChanged)
			return;
		PlayerRecord *mine = (PlayerRecord *)PLAYER(GS->localPlayer);
		if (p->flagShown == 0 && (mine->flagShown == 1 || mine->emblemChanged == 1))
			mine->emblemSent = 0;
		GS->screenshotUpload = 5.0f;
		if (*(const short *)(pkt + 3) < 0)
			return;
		p->emblemChanged = 1;
		return;
	}
	case 13:
		if (pkt[2] != 'k')
			break;
		GS->startTimer = 5.0f;
		return;
	case 14:
		if (GS->itemLevelsTaken == 1)
			return;
		for (int k = 0; k < SCENE_STAGE(g)->itemCount && k < 0x7c; k++) {
			MapItem *it = &SCENE_STAGE(g)->items[k];
			if (it->type < 0)
				continue;
			u8 v = b[2 + k / 2];
			int n = (k % 2 == 0 ? v : v >> 4) & 0xf;
			if (n == 0)
				it->taken = BITS(it->fade) = 0;
			else {
				it->taken = 1;
				it->fade = f32(fmul_m((long double)n, K(0x4a9418)));
			}
		}
		GS->itemLevelsTaken = 1;
		return;
	}
	GAME_FN(debug_traceStripped, 0x48b420, void, const char *)(pkt);   /* debug_traceStripped */
}
#undef G
#undef GS
#undef K
#undef STAGE
#undef ACTOR
#undef PLAYER
#undef CALL1
