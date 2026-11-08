/* network.c: the game's network code: the TCP connections to the lobby and game servers (connect, send a request,
   read its reply, the lists received), DirectPlay (started, sessions hosted, joined and enumerated, messages sent and
   handled), the session table (200 SessionSlots at g_sessionTable) and the sixteen player slots (g_netSlots), the
   ping thread, this machine's address, and the match's game packets taken in (net_processGamePacket). */
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

/* 0x4532b0: session i's SessionDesc copy (g_sessionTable[i].desc), 0 when i is out of range (0 ..
   g_dplaySessionCount, a count, yet taken inclusive) or the slot unused */
int (net_getSession)(int i)
{
	if (i > -1 && i <= g_dplaySessionCount && g_sessionTable[i].used)
		return (int)g_sessionTable[i].desc;
	return 0;
}

/* 0x4514a0: player slot (its low byte) taken by player id: the first ten shorts of its packet reset (two of them
   -1), the one at +0x22 the current value of g_localPlayerData */
void (net_takePlayerSlot)(u32 slot, int id)
{
	static const short init[10] = { 0, 0, 0, 0, 0, -1, 0, 0, -1, 0 };
	NetSlot *r = &g_netSlots[slot & 0xff];
	r->used = 1;
	r->id = id;
	memcpy(r->packet, init, sizeof init);
	memcpy(&r->packet[0x22], &g_localPlayerData, 2);
}

/* 0x4515a0: all slots freed (and the 0x40 bytes at g_playerSlotFlags cleared) */
void (net_freeAllSlots)(void)
{
	memset((void *)OBJ(g_playerSlotFlags), 0, 0x40);
	for (NetSlot *r = g_netSlots; r < g_netSlots + 16; r++)
		memset(r, 0, offsetof(NetSlot, packet));
}

/* 0x451450: a free player slot claimed (its flag in the sixteen at g_playerSlotFlags set); 0xff when none is free */
u8 (net_claimPlayerSlot)(void)
{
	for (u8 i = 0; i < 0x10; i++)
		if (g_playerSlotFlags[i] == 0) {
			g_playerSlotFlags[i] = 1;
			return i;
		}
	return 0xff;
}

/* 0x451410: on the host only (g_isHost; else 0): a free player slot claimed for the local player (id
   g_localPlayerId), noted in g_localSlot, g_slotTakenFlag raised; 1 */
int (net_claimLocalSlot)(void)
{
	if (!g_isHost)
		return 0;
	u8 slot = net_claimPlayerSlot();
	net_takePlayerSlot(slot, (*(int *)&g_localPlayerId));
	g_localSlot = slot;
	g_slotTakenFlag = 1;
	return 1;
}

/* 0x454130: with a session list (g_sessionListOpen), every used session slot (g_sessionTable)
   freed and the list emptied (count g_dplaySessionCount). Returns the count, or 0 without a list */
u32 (net_freeSessionList)(void)
{
	if (!g_sessionListOpen)
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

/* 0x4542a0: this machine's address "a.b.c.d" (g_localAddress, from net_getLocalAddress; cut up in place by strtok) as (a << 24) | b << 16 | c << 8 | d
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

/* 0x454390: the address as "a.b.c.d" (bytes high to low) into g_dottedAddress; returns its length + 1 */
int (net_formatAddress)(u32 address)
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
   (malloc'd) kept in the first free slot of the table at g_sessionTable, the count up. Returns the copy, 0 for a session
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
   name ..) put into the list (net_addSession, by value) unless its GUID is GUID_NULL (1) or already listed (0, which
   ends the enumeration). With no description (the enumeration timed out) it stops in modes 0 and 1. The copy's
   first word is a GlobalAlloc'd block holding the GUID; in mode 0 (address) the session's address as text. 1 */
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
		net_formatAddress(dd->user4);   /* net_formatAddress */
		crt_strncpy(d.address, g_dottedAddress, 0x10);
	}
	net_addSession(d);
	return 1;
}

/* 0x4547c0: inet_addr of the text (Winsock, through the game's jump to its import) */
u32 (net_inetAddr)(const char *text) { return ws_inet_addr(text); }

/* 0x451270: a message sent from the local player (g_localPlayerId) to to: types 2 and 6 guaranteed (flag 1) with 8 bytes,
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

/* 0x453720: DirectPlay's start: the unused words and the session table (g_sessionTable) cleared, COM started
   (CoInitialize), then net_resetState + DirectPlay made (dplay_resetAndCreate). Only CoInitialize's failure
   reaches the error path (dplay_release, its HRESULT returned): dplay_resetAndCreate always returns 0. 0 otherwise */
int (dplay_init)(void)
{
	g_unusedDplayWord1 = 0;
	g_unusedDplayWord2 = 0;
	g_unusedDplayWord3 = 0;
	memset((void *)OBJ(g_sessionTable), 0, 0x190 * 4);
	g_unusedDplayWord4 = 0;
	int hr = CoInitialize(NULL);   /* CoInitialize */
	if (hr >= 0) {
		hr = dplay_resetAndCreate();      /* dplay_resetAndCreate */
		if (hr >= 0)
			return 0;
	}
	dplay_release();
	return hr;
}

/* 0x454760: the network thread's three handles closed (g_pingThread, g_pingStopEvent, g_pingStartEvent) and the running flag cleared.
   Returns what the original leaves in eax (the last close's answer, or 0) */
u32 (net_closeThreadHandles)(void)
{
	static const u32 handles[3] = { ADDR(g_pingThread), ADDR(g_pingStopEvent), ADDR(g_pingStartEvent) };
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

/* 0x452d70: the server's 62-byte reply received into g_playerListReply (recv on g_gameServerSocket until 62 bytes have come or 3 s
   have passed; each call reads to the start of the buffer), then by its kind (+0x1e): 0 a player for the list
   (net_addPlayerRecord), 1 the list's end (g_playerListDone set: WndProc then raises g_rankingListIn; g_netLastRequest
   cleared) */
void (net_receivePlayerListReply)(void)
{
	u8 *reply = g_playerListReply;
	u32 start = GetTickCount();
	u32 got = 0;
	do {
		int n = ws_recv((*(u32 *)&g_gameServerSocket), reply, 0x3e, 0);   /* recv */
		if (n > 0)
			got += n;
	} while (GetTickCount() - start <= 3000 && got < 0x3e);
	switch (g_playerListReplyKind) {
	case 0:
		net_addPlayerRecord(reply);
		break;
	case 1:
		g_playerListDone = 1;
		g_netLastRequest = 0;
		break;
	}
}

/* 0x4520e0: both sockets (g_lobbySocket, g_gameServerSocket) closed: Winsock cleaned up (WSACleanup), sending shut down, the socket closed,
   the connection's state reset (net_freeBuffers); then the connection flags cleared. Returns what the original leaves
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
		r = net_freeBuffers();
	}
	g_netLastRequest = 0;
	g_connectedServer = 0;
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
   both sockets closed (Winsock cleaned up (WSACleanup), sending shut down; net_freeBuffers after each), the server's address
   taken (its host name, or what net_resolveHost made of it, into g_serverHost) with its port (g_serverPort); then every
   network table cleared and the packet buffers allocated anew, cleared. The caller ignores the eax it leaves */
void (net_resetConnection)(int kind)
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
		net_freeBuffers();
	}
	if (kind == 100 || kind == 101) {
		const char *host = (const char *)(RELOC(kind) == 100 ? OBJ(g_tcpDns) : OBJ(g_ladderDns));
		strcpy(g_serverHost, net_resolveHost(host) ? g_resolvedAddress : host);
		g_serverPort = GAME_VAR(u16, kind == 100 ? ADDR(g_lobbyTcpPort) : ADDR(g_ladderPort));
	}
	memset((void *)OBJ(g_roomList), 0, 0x1e40 * 4);
	memset((void *)OBJ(g_serverList), 0, 0x16c0 * 4);
	memset((void *)OBJ(g_netPlayerList), 0, 0x2aa);
	static const struct { u32 at, size; } buffers[] = {
		{ ADDR(g_arenaPacket), 0x5b }, { ADDR(g_arenaInfoPacket), 0x5b }, { ADDR(g_lobbyLeavePacket), 0x5b }, { ADDR(g_arenaListRequest), 4 }, { ADDR(g_lobbyKeepAlive), 0x10 }, { ADDR(g_accountPacket), 0x10b },
		{ ADDR(g_netRankingBuffer), 8 }, { ADDR(g_roomPacket), 0x79 }, { ADDR(g_roomInfoPacket), 0x79 }, { ADDR(g_roomLeavePacket), 0x79 }, { ADDR(g_roomListRequest), 4 }, { ADDR(g_netKindBuffer), 4 },
		{ ADDR(g_gameServerKeepAlive), 0x10 }, { ADDR(g_netSelectionPacket), 0xb9 }, { ADDR(g_netAccountBuffer), 0x5c }, { ADDR(g_netPlayerRecordPacket), 0x36 }, { ADDR(g_netByteBuffer), 1 }, { ADDR(g_netAccountRequest), 0x1e } };
	for (unsigned k = 0; k < sizeof buffers / sizeof *buffers; k++)
		GAME_VAR(void *, buffers[k].at) = alloc_clear(buffers[k].size);
	memset((void *)ADDR(g_rankReplyCode), 0, 0x22);
	(*(void **)&g_netLeaveBuffer) = alloc_clear(0x1e);
	memset((void *)OBJ(g_lobbyReplyRecord), 0, 0x5b);
	memset((void *)OBJ(g_gameServerReply), 0, 0x79);
	g_unusedNetResetWord = 0;
	memset((void *)OBJ(g_playerListReply), 0, 0x3e);
	memset((void *)ADDR(g_profileReplyResult), 0, 0x10b);
}

/* a GlobalAlloc'd block unlocked and freed (through its handle) */
static void global_free(void *p)
{
	GlobalUnlock(GlobalHandle(p));   /* GlobalUnlock(GlobalHandle(p)) */
	GlobalFree(GlobalHandle(p));   /* GlobalFree(GlobalHandle(p)) */
}

/* 0x453920: DirectPlay shut down: the lobby object released, the local player destroyed and the session closed and
   released, the session buffers freed (g_connectionCopy is freed but not cleared), COM ended. Returns 0 */
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
   the host looked up and its first address as text in g_resolvedAddress; the socket closed again. 1 when there is an
   address; 0 if Winsock, the socket or the lookup failed (the socket is left open then, as in the original) */
int (net_resolveHost)(const char *host)
{
	u8 wsa[0x190];
	memset((void *)OBJ(g_resolvedAddress), 0, 0x64);
	if (WSAStartup(0x202, wsa))             /* WSAStartup */
		return 0;
	int sock = ws_socket(2, 3, 1);        /* ws_socket(AF_INET, SOCK_RAW, IPPROTO_ICMP) */
	if (sock == -1)
		return 0;
	u8 *entry = ws_gethostbyname(host);           /* gethostbyname */
	if (!entry)
		return 0;
	u32 address = ***(u32 ***)(entry + 0xc);                                 /* h_addr_list[0] */
	strcpy(g_resolvedAddress, ws_inet_ntoa(address));   /* inet_ntoa */
	if (!strlen(g_resolvedAddress))
		return 0;
	if (sock) {
		WSACleanup();      /* WSACleanup */
		IMPORT(WS_CLOSESOCKET, int, int)(sock);   /* closesocket */
	}
	return 1;
}

/* 0x453fd0: the sessions asked for (DirectPlay EnumSessions, async with the callback dplay_enumSessionsCallback, flags 0x12): of the
   game's application (GUID at k_axisAppGuid), on the instance at *g_providerGuid; asked once, and only for connection kinds 0 and 1 (2 and 3 ask
   nothing and return 1). 1 on success,
   0 without DirectPlay or on a failure */
int (dplay_enumSessions)(void)
{
	void *play = g_dplay;
	if (!play)
		return 0;
	DPSessionDesc2 desc;
	memset(&desc, 0, sizeof desc);
	desc.size = sizeof desc;
	memcpy(desc.instance, g_providerGuid, 16);
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

/* ---- a received record appended to a list: its strings and single bytes copied into the next slot, and its
   address (the string at pingAddress) also into the ping list (20 bytes a slot at g_pingAddresses); the count
   advanced. Returns the slot's offset in the list (the original's eax) ---- */
static int list_append(u32 count, u32 base, int size, const u8 *rec, const u8 *strings, int nstrings, int pingAddress,
                       const u8 *bytes, int nbytes)
{
	for (int k = 0; k < nstrings; k++)
		lstrcpyA((char *)(RELOC(base) + GAME_VAR(int, count) * size + strings[k]), (const char *)RELOC(rec) + strings[k]);
	lstrcpyA((char *)(OBJ(g_pingAddresses) + GAME_VAR(int, count) * 20), (const char *)RELOC(rec) + pingAddress);
	int i = GAME_VAR(int, count);
	u8 *slot = (u8 *)(RELOC(base) + i * size);
	for (int k = 0; k < nbytes; k++)
		slot[bytes[k]] = rec[bytes[k]];
	GAME_VAR(int, count) = i + 1;
	return i * size;
}
/* 0x452af0: an ArenaRecord into the list at g_serverList (count g_serverListCount) */
int (net_addServerRecord)(const u8 *rec)
{
	static const u8 strings[3] = { offsetof(ArenaRecord, address), offsetof(ArenaRecord, name), offsetof(ArenaRecord, password) };
	static const u8 bytes[9] = { offsetof(ArenaRecord, kind), offsetof(ArenaRecord, rotation), offsetof(ArenaRecord, fragLimit), offsetof(ArenaRecord, timeLimit), offsetof(ArenaRecord, gameMode), offsetof(ArenaRecord, players), offsetof(ArenaRecord, map), offsetof(ArenaRecord, maxPlayers), offsetof(ArenaRecord, locked) };
	return list_append(ADDR(g_serverListCount), OBJ(g_serverList), sizeof(ArenaRecord), rec, strings, 3, offsetof(ArenaRecord, address), bytes, 9);
}
/* 0x452c80: a RoomRecord into the list at g_roomList (count g_roomListCount) */
int (net_addRoomRecord)(const u8 *rec)
{
	static const u8 strings[4] = { offsetof(RoomRecord, hostName), offsetof(RoomRecord, address), offsetof(RoomRecord, name), offsetof(RoomRecord, password) };
	static const u8 bytes[9] = { offsetof(RoomRecord, kind), offsetof(RoomRecord, rotation), offsetof(RoomRecord, fragLimit), offsetof(RoomRecord, gameMode), offsetof(RoomRecord, players), offsetof(RoomRecord, map), offsetof(RoomRecord, maxPlayers), offsetof(RoomRecord, timeLimit), offsetof(RoomRecord, locked) };
	return list_append(ADDR(g_roomListCount), OBJ(g_roomList), sizeof(RoomRecord), rec, strings, 4, offsetof(RoomRecord, address), bytes, 9);
}

#define lstrlenA(s) IMPORT(0x4a9188, int, const char *)(s)
/* 0x451350: a chat line as text: \"<name> > <text>\" (format 0x4b3e30 \"%s > %s\"; the sender's short name from
   DirectPlay through dplay_getPlayerName, \"unknown\" (0x4b3e38) when it has none) in a new global block, stored in
   *out. Returns the name lookup's result, or 0x8007000e (E_OUTOFMEMORY) when the block cannot be had */
int (net_formatChatLine)(u32 from, const char *text, char **out)
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
const char *(text_findSubstring)(const char *text, const char *word, int exact)
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

/* 0x4546d0: the network worker started: two events (g_pingStartEvent, g_pingStopEvent) and the thread running net_pingThreadProc (handle
   g_pingThread, id g_pingThreadId), then the first event set. 1, or 0 when any of them cannot be made */
int (net_startPingThread)(void)
{
	if (!(g_pingStartEvent = CreateEventA(NULL, 0, 0, NULL)))   /* CreateEventA */
		return 0;
	if (!(g_pingStopEvent = CreateEventA(NULL, 0, 0, NULL)))
		return 0;
	g_pingThread = CreateThread(NULL, 0, (void *)FN_ADDR(net_pingThreadProc, 0x454560), NULL, 0, (u32 *)ADDR(g_pingThreadId));   /* CreateThread */
	if (!g_pingThread)
		return 0;
	SetEvent(g_pingStartEvent);
	return 1;
}

/* 0x452de0: a player record appended to the list at g_netPlayerList (count g_playerListCount): its name and the seven values after
   its kind. Returns the slot's offset (the original's eax) */
int (net_addPlayerRecord)(const u8 *rec)
{
	const RankedPlayer *from = (const RankedPlayer *)RELOC(rec);
	lstrcpyA(((RankedPlayer *)g_netPlayerList)[g_playerListCount].name, from->name);
	int i = g_playerListCount;
	RankedPlayer *slot = &((RankedPlayer *)g_netPlayerList)[i];
	slot->deaths = from->deaths;
	slot->kills = from->kills;
	slot->games = from->games;
	slot->exp = from->exp;
	BITS(slot->power) = BITS(from->power);
	BITS(slot->rate) = BITS(from->rate);
	slot->level = from->level;
	g_playerListCount = i + 1;
	return i * 62;
}

/* 0x454220: this machine's address as text in g_localAddress (16 bytes, cleared first): its host name looked up and the
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

/* 0x4512c0: a chat line sent: formatted for this player (net_formatChatLine into g_sentChatBlock), then a message (type 1, from
   the player g_localPlayerId, the text at +0xc) in a new global block sent to everyone (dplay_send). 1 when sent */
int (net_sendChat)(const char *text)
{
	if (net_formatChatLine(g_localPlayerId, text, (char **)ADDR(g_sentChatBlock)) < 0)   /* net_formatChatLine */
		return 0;
	int size = lstrlenA(text) + 0x10;
	u8 *message = GlobalLock(GlobalAlloc(0x42, size));   /* GlobalLock(GlobalAlloc(GHND)) */
	if (!message)
		return 0;
	*(u32 *)RELOC(message) = 1;
	*(u32 *)(RELOC(message) + 8) = g_localPlayerId;
	lstrcpyA((char *)RELOC(message) + 0xc, text);
	return dplay_send(g_localPlayerId, 0, 0, message, size) >= 0;
}

/* 0x4548b0: host ip pinged (ICMP echo, waiting up to timeout ms). Returns the round trip time, kept in g_pingTime:
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

/* 0x4545b0: every server in the list pinged (net_pingServer by name, 20 bytes a slot at g_pingAddresses) until done
   (g_netListDone): its time in g_serverPing (above 1000 ms less 400; 0 when it did not answer) and marked pinged (g_serverPinged);
   then done, and the events reset (net_stopPingThread, whose eax it returns) */
u32 (net_pingAllServers)(void)
{
	(*(int *)&g_pingTime) = 0;
	if (g_serverPingCount > 0) {
		for (int i = 0; i < g_serverPingCount && g_netListDone != 1; i++) {
			const char *address = (const char *)(OBJ(g_pingAddresses) + i * 20);
			if ((int)strlen(address) <= 0)
				continue;
			if (net_pingServer(address, i)) {   /* net_pingServer */
				int time = (*(int *)&g_pingTime);
				if (time > 1000)
					(*(int *)&g_pingTime) = time -= 400;
				g_serverPing[i] = time;
			} else
				g_serverPing[i] = 0;
			(*(int *)&((u32 *)g_serverPinged)[i]) = 1;
		}
	}
	g_netListDone = 1;
	return net_stopPingThread();   /* net_stopPingThread */
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

/* 0x452a30: a lobby reply (0x5b bytes into g_lobbyReplyRecord, socket g_lobbySocket), by its type (g_lobbyReplyKind): 0 a server for the
   list (net_addServerRecord), 1 the list is complete (its count to g_serverPingCount, the ping thread started), 2 / 3 the connection
   state g_lobbyListAnswer set (0xcb / 0x29); 1..3 also end the wait (g_netLastRequest) */
void (net_receiveLobbyReply)(void)
{
	reply_read(ADDR(g_lobbySocket), (void *)OBJ(g_lobbyReplyRecord), 0x5b);
	switch (g_lobbyReplyKind) {
	case 0:
		net_addServerRecord((void *)OBJ(g_lobbyReplyRecord));   /* net_addServerRecord */
		break;
	case 1:
		g_serverPingCount = g_serverListCount;
		net_startPingThread();   /* net_startPingThread */
		g_lobbyListAnswer = 0xca;
		g_netLastRequest = 0;
		break;
	case 2:
		g_lobbyListAnswer = 0xcb;
		g_netLastRequest = 0;
		break;
	case 3:
		g_lobbyListAnswer = 0x29;
		g_netLastRequest = 0;
		break;
	}
}

/* 0x452bd0: a game server's reply (0x79 bytes into g_gameServerReply, socket g_gameServerSocket), by its type (g_gameServerReplyKind): 0 a room for
   the list (net_addRoomRecord), 1 the list is complete (as above, state g_roomListAnswer 0xca), 2 / 3 state 0x28 */
void (net_receiveGameServerReply)(void)
{
	reply_read(ADDR(g_gameServerSocket), (void *)OBJ(g_gameServerReply), 0x79);
	switch (g_gameServerReplyKind) {
	case 0:
		net_addRoomRecord((void *)OBJ(g_gameServerReply));   /* net_addRoomRecord */
		break;
	case 1:
		g_serverPingCount = g_roomListCount;
		net_startPingThread();
		g_roomListAnswer = 0xca;
		g_netLastRequest = 0;
		break;
	case 2:
	case 3:
		g_roomListAnswer = 0x28;
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

/* 0x450a60: every waiting DirectPlay message received (dplay_receive) into a global block of g_netBlockSize bytes, grown when
   too small: system messages (from 0) go to net_handleSystemMessage and the next is read; the first player message goes to
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
			net_handleSystemMessage(buf);
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
   session's GUID and the game's application GUID (k_axisAppGuid) */
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

/* 0x453cf0: a session hosted (Open with DPOPEN_CREATE): flags 0x44, the instance GUID from *g_providerGuid, the session
   name, at most maxPlayers, the user words (user3 = hi << 8 | lo, sign-extended bytes; user4 the local address,
   unless g_connectionKind), then the local player `player`: its id into g_localPlayerId, data into g_localPlayerData, the host flag
   g_isHost set and a player slot claimed (net_claimLocalSlot). 0 without DirectPlay or on a failure, else 1 */
int (dplay_hostSession)(const char *session, const char *player, u32 user1, u32 maxPlayers, u32 user2,
                        signed char hi, signed char lo, u32 data)
{
	void *play = g_dplay;
	if (!play)
		return 0;
	DPSessionDesc2 *desc = session_desc(g_providerGuid);
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
   g_localPlayerId, data into g_localPlayerData, the host flag g_isHost cleared. 0x1f4 joined (also for a CreatePlayer error not
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

/* the lobby's part of dplay_create: its connection settings (DPLCONNECTION, into a global block g_lobbyConnectionBlock) with the
   session flags 0x44 and at most 16 players, connected (ConnectEx into g_dplay) and the local player created
   with the lobby's player name record; the host flag g_isHost by the connection's flags (2 create, 1 join). Stops at the
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
   DirectPlay object (dplay_createObject; its failure returned) and the connections listed (EnumConnections of the game's
   application with dplay_enumConnections). The lobby's settings block is freed (but g_lobbyConnectionBlock kept). Returns the
   listing's failure, else 0 */
int (dplay_create)(void)
{
	dplay_lobbyConnect();
	int r = dplay_createObject((void **)ADDR(g_dplay));   /* dplay_createObject */
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

/* 0x451090: a game message from player `from`, by its type (the first word): 1 a chat line (+0xc) formatted into
   g_lastChatLine (the old pointer only cleared first, its block not freed; g_lastChatLineSet raised); 2 the host's id (+4, into g_netHostGone) with the player slots
   reset (net_freeSessionList, then net_freeAllSlots); 6 our own player slot (byte +4, 0x410 bytes a slot from g_netSlots) taken, the slot
   noted in g_localSlot and g_slotTakenFlag raised; 7 another player's slot data: the slot taken by `from` if it was free,
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
		if ((*(int *)&g_lastChatLine))
			(*(int *)&g_lastChatLine) = 0;
		r = net_formatChatLine(from, message + 0xc, (char **)ADDR(g_lastChatLine));   /* net_formatChatLine */
		if (r >= 0)
			g_lastChatLineSet = 1;
		return r;
	case 2:
		(*(u32 *)&g_netHostGone) = *(const u32 *)(RELOC(message) + 4);
		net_freeSessionList();
		return net_freeAllSlots();
	case 6:
		net_takePlayerSlot(slot, (*(int *)&g_localPlayerId));
		player->used = 1;
		g_slotTakenFlag = 1;
		g_localSlot = (u8)slot;
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
   the service provider (g_providerGuid: g_tcpProviderGuid, g_ipxProviderGuid, g_modemProviderGuid, g_serialProviderGuid) and its stored connection (g_storedConnection from
   OBJ(g_dpConnections) + 4 * kind); for TCP/IP (0) a compound address is made instead by the lobby from the provider and the
   host `address` (or g_noAddress), size query then fill, into a new block g_hostAddressBlock. Then (when there is a connection) a
   new DirectPlay object (dplay_createObject) initialised with it and its caps kept (timeout, buffer and queue sizes into
   0xa0bb00 .. 0xa0bb08). 0 when that fails, else 1 */
int (dplay_initConnection)(int kind, const char *address)
{
	if (g_dplay) {
		dplay_closeSession(g_dplay);   /* dplay_closeSession */
		g_dplay = NULL;
	}
	static const u32 provider[4] = { OBJ(g_tcpProviderGuid), OBJ(g_ipxProviderGuid), OBJ(g_modemProviderGuid), OBJ(g_serialProviderGuid) };   /* (the GUIDs: TCP, IPX, modem, serial) */
	if ((u32)kind <= 3) {
		(*(u32 *)&g_providerGuid) = provider[kind];
		(*(u32 *)&g_storedConnection) = (*(u32 *)&g_dpConnections[kind]);
	}
	if (kind == 0) {
		struct { u32 guid[4], size; const void *data; } element[2];   /* DPCOMPOUNDADDRESSELEMENT */
		char host[0xc0];
		u32 size = 0;
		strcpy(host, address ? address : g_noAddress);
		memcpy(element[0].guid, (const void *)OBJ(k_DPAID_ServiceProvider), 16);   /* DPAID_ServiceProvider */
		element[0].size = 0x10;
		element[0].data = g_providerGuid;
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
	if (dplay_createObject((void **)ADDR(g_dplay)) < 0 || !g_dplay)   /* dplay_createObject */
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
   net_freeBuffers. Returns its eax */
static u32 socket_close(u32 socket)
{
	WSACleanup();                                  /* WSACleanup */
	IMPORT(WS_SHUTDOWN, int, int, int)(GAME_VAR(int, socket), 1);      /* shutdown(SD_SEND) */
	IMPORT(WS_CLOSESOCKET, int, int)(GAME_VAR(int, socket));              /* closesocket */
	GAME_VAR(int, socket) = 0;
	return net_freeBuffers();
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


/* ---- the info sent to the server when a player comes or goes while hosting over TCP/IP: the arena's (g_arenaPacket into
   the packet g_arenaInfoPacket, to the lobby server) or the Ladder room's (g_roomPacket into g_roomInfoPacket, to the game server), the player count (g_playerCount) included ---- */

static void arena_info(u8 *dst, u8 kind, u8 count)
{
	const ArenaRecord *src = g_arenaPacket;
	ArenaRecord *to = (ArenaRecord *)dst;
	to->kind = kind;
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

static void room_info(u8 *dst, u8 kind, u8 count)
{
	const RoomRecord *src = g_roomPacket;
	RoomRecord *to = (RoomRecord *)dst;
	to->kind = kind;
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

/* 0x450c20 (a DirectPlay system message): 5 (DPSYS_DESTROYPLAYERORGROUP), a player gone: its slots freed
   (net_freeSlotsOf, unless the host is gone), then the info sent with the count less one; 3
   (DPSYS_CREATEPLAYERORGROUP), a player joined (the host only): a slot claimed for it (net_claimPlayerSlot into
   g_netClaimedSlot) and sent to it (net_sendMessage), the message's count kept and the info sent (a Ladder room's then
   with kind 1; an arena's keeps its own kind). Only while
   hosting (g_isHost) over TCP/IP (g_connectionKind = 0) with the right socket open (200: the arena on the lobby's, 201: the
   Ladder room on the game server's) and nothing pending (g_lobbyReportsOff / g_gameServerReportsOff). The original leaves eax to callers that
   ignore it */
void (net_handleSystemMessage)(const u32 *msg)
{
	int joined;
	if (msg[0] == 5) {
		if (!g_netHostGone)
			net_freeSlotsOf(msg[2]);   /* net_freeSlotsOf */
		joined = 0;
	} else if (msg[0] == 3) {
		if (!g_isHost)
			return;
		(*(u8 *)&g_netClaimedSlot) = net_claimPlayerSlot();
		net_sendMessage((void *)ADDR(g_netSlotMessageKind), msg[2], 0);
		joined = 1;
	} else
		return;
	if (!g_isHost || g_connectionKind)
		return;
	switch (g_connectedServer) {
	case 201:
		if (g_gameServerReportsOff || !g_gameServerSocket)
			return;
		if (joined)
			g_playerCount = msg[3];
		if (!g_roomInfoPacket)
			return;
		if (joined)
			room_info(g_roomInfoPacket, 1, (u8)g_playerCount);
		else
			room_info(g_roomInfoPacket, g_roomPacket->kind, (u8)(g_playerCount - 1));
		break;
	case 200:
		if (g_lobbyReportsOff || !(*(int *)&g_lobbySocket))
			return;
		if (joined)
			g_playerCount = msg[3];
		if (!g_arenaInfoPacket)
			return;
		arena_info(g_arenaInfoPacket, g_arenaPacket->kind, (u8)(g_playerCount - !joined));
		break;
	}
}

/* a TCP socket into *sock connected to the host g_serverHost (a dotted address, else looked up by name) at port
   g_serverPort, after Winsock 2.2 starts and the socket is bound to any address; connected: g_connectedServer = status, 1. A
   refusal (connect's result compared with 10061, as the original does) 2, any failure 0 (Winsock cleaned up and
   the network left where the original does so) */
static int connect_socket(int *sock, int status)
{
	const char *host = g_serverHost;
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
	g_connectedServer = status;
	return 1;
}

/* 0x451b80: connecting (everything closed first): 100 the lobby's socket (g_lobbySocket, status 200), 0x65 the game
   server's (g_gameServerSocket, status 201); any other mode just 1 */
int (net_connect)(int mode)
{
	net_resetConnection(mode);
	g_netConnected = 1;
	if (mode == 100)
		return connect_socket((int *)ADDR(g_lobbySocket), 200);
	if (mode == 0x65)
		return connect_socket((int *)ADDR(g_gameServerSocket), 201);
	return 1;
}

/* 0x451e60: leaving the network (while connected, g_netConnected = 1): on the lobby's socket (g_lobbySocket) the hosted
   arena's record (g_arenaPacket into g_lobbyLeavePacket, message 0xb) unless g_lobbyReportsOff, on the game server's (g_gameServerSocket) the room record
   (g_roomPacket into g_roomLeavePacket, message 0x16) unless g_gameServerReportsOff; each socket closed. Without a send buffer it stops there
   (0). Then the connection flags cleared. Returns what the original leaves in eax */
u32 (net_disconnect)(void)
{
	static const u8 lobbyBytes[9] = { offsetof(ArenaRecord, rotation), offsetof(ArenaRecord, fragLimit), offsetof(ArenaRecord, timeLimit), offsetof(ArenaRecord, gameMode), offsetof(ArenaRecord, players), offsetof(ArenaRecord, map), offsetof(ArenaRecord, maxPlayers), offsetof(ArenaRecord, locked) }, lobbyNames[3] = { offsetof(ArenaRecord, password), offsetof(ArenaRecord, address), offsetof(ArenaRecord, name) };
	static const u8 roomBytes[9] = { offsetof(RoomRecord, rotation), offsetof(RoomRecord, fragLimit), offsetof(RoomRecord, gameMode), offsetof(RoomRecord, players), offsetof(RoomRecord, map), offsetof(RoomRecord, maxPlayers), offsetof(RoomRecord, timeLimit), offsetof(RoomRecord, locked) }, roomNames[3] = { offsetof(RoomRecord, password), offsetof(RoomRecord, hostName), offsetof(RoomRecord, address) };
	if (g_netConnected != 1)
		return (*(u32 *)&g_netConnected);
	u32 r = g_lobbySocket;
	if ((*(int *)&g_lobbySocket)) {
		if (!g_lobbyReportsOff && !send_leave(ADDR(g_arenaPacket), ADDR(g_lobbyLeavePacket), lobbyBytes, 8, 0x45, lobbyNames, 0xb, 0x64))
			return 0;
		r = socket_close(ADDR(g_lobbySocket));
	}
	if (g_gameServerSocket) {
		if (!g_gameServerReportsOff && !send_leave(ADDR(g_roomPacket), ADDR(g_roomLeavePacket), roomBytes, 8, 0x63, roomNames, 0x16, 0x65))
			return 0;
		r = socket_close(ADDR(g_gameServerSocket));
	}
	g_netLastRequest = 0;
	g_connectedServer = 0;
	g_netConnected = 0;
	return r;
}

/* 0x450bb0, 0x4532e0: jumps to net_receiveAll and net_getLocalAddress (their eax passed on) */
u32 (jmp_net_receiveAll)(void) { return net_receiveAll(); }
int (jmp_net_getLocalAddress)(void) { return net_getLocalAddress(); }

/* ---- packets to the lobby (socket g_lobbySocket) and the game server (g_gameServerSocket): a kind word, then the kind's buffer ---- */

/* the buffer at the pointer kept at `buffer` sent whole (size bytes) over the socket kept at `socket`, if both are
   there */
static void send_buffer(u32 socket, u32 buffer, int size)
{
	void *data = GAME_VAR(void *, buffer);
	if (data && GAME_VAR(u32, socket))
		ws_send(GAME_VAR(u32, socket), data, size, 0);   /* send */
}

/* 0x4521c0: packet `kind` sent to `to` (100 the lobby, 101 the game server; another value sends only the packet
   itself): its kind word (in g_netKindBuffer; none: nothing at all), then the kind's buffer: 10 .. 12 to the lobby (0x5b
   bytes), 13 the arena list request (the server list cleared first), 23 the hosted arena's address (0x10, in
   g_lobbyKeepAlive), 14 / 15 the Ladder login / new-ID registration (the account record g_accountPacket, 0x10b bytes,
   with this machine's address put in), 17 .. 22 and 24 .. 29 to the game server (19 and 21 / 26 after clearing the
   server or player tables, 22 with its first byte set). Most kinds are kept as the last request (g_netLastRequest).
   The callers ignore the eax it leaves */
void (net_send)(int kind, int to)
{
	u32 *word = g_netKindBuffer;
	if (to == 100 || to == 101) {
		if (!word)
			return;
		*word = (u32)kind;
		u32 socket = to == 100 ? ADDR(g_lobbySocket) : ADDR(g_gameServerSocket);
		if (GAME_VAR(u32, socket))
			ws_send(GAME_VAR(u32, socket), (*(void **)&g_netKindBuffer), 4, 0);
	}
	static const struct { u32 buffer; int size, lobby; } plain[30] = {
		[10] = { ADDR(g_arenaPacket), 0x5b, 1 }, [11] = { ADDR(g_lobbyLeavePacket), 0x5b, 1 }, [12] = { ADDR(g_arenaInfoPacket), 0x5b, 1 },
		[17] = { ADDR(g_netPlayerRecordPacket), 0x36, 0 }, [18] = { ADDR(g_roomPacket), 0x79, 0 }, [20] = { ADDR(g_roomInfoPacket), 0x79, 0 },
		[25] = { ADDR(g_netLeaveBuffer), 0x1e, 0 }, [27] = { ADDR(g_netSelectionPacket), 0xb9, 0 }, [28] = { ADDR(g_netAccountBuffer), 0x5c, 0 }, [29] = { ADDR(g_netAccountRequest), 0x1e, 0 } };
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
		send_buffer(ADDR(g_lobbySocket), ADDR(g_arenaListRequest), 4);
		return;
	case 23: {
		char *address = g_lobbyKeepAlive;
		const char *from = (const char *)g_arenaPacket;
		if (!address || !from)
			return;
		strcpy(address, ((const ArenaRecord *)from)->address);
		send_buffer(ADDR(g_lobbySocket), ADDR(g_lobbyKeepAlive), 0x10);
		return;
	}
	case 14: case 15:
		g_netLastRequest = kind;
		if (!g_accountPacket)
			return;
		jmp_net_getLocalAddress();
		lstrcpyA(g_accountPacket->address, g_localAddress);
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_accountPacket), 0x10b);
		return;
	case 19:
		net_clearServers();
		net_clearRoomList();
		g_netLastRequest = 0x13;
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_roomListRequest), 4);
		return;
	case 21:
	case 26:
		net_clearPlayerList();
		if (kind == 21)
			g_netLastRequest = 0x15;
		send_buffer(ADDR(g_gameServerSocket), kind == 21 ? ADDR(g_netRankingBuffer) : ADDR(g_netByteBuffer), kind == 21 ? 8 : 1);
		return;
	case 22:
		g_netLastRequest = 0x16;
		if (!g_roomLeavePacket)
			return;
		*g_roomLeavePacket = 1;
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_roomLeavePacket), 0x79);
		return;
	case 24:
		jmp_net_getLocalAddress();
		if (!g_gameServerKeepAlive)
			return;
		lstrcpyA(g_gameServerKeepAlive, g_localAddress);
		send_buffer(ADDR(g_gameServerSocket), ADDR(g_gameServerKeepAlive), 0x10);
		return;
	}
}

/* ---- replies to the last request (g_netLastRequest) ---- */

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

/* an answer (0x10b bytes into g_profileReplyResult) from the game server: its code kept in `answer` when it is one of `codes`
   (that ends the request); a timeout leaves 0x28 */
static void answer_reply(u32 answer, const u8 *codes, int count, u32 start)
{
	if (!recv_all(ADDR(g_gameServerSocket), (void *)ADDR(g_profileReplyResult), 0x10b, start)) {
		GAME_VAR(int, answer) = 0x28;
		g_netLastRequest = 0;
	}
	int code = g_profileReplyResult;
	for (int k = 0; k < count; k++)
		if (code == codes[k]) {
			g_netLastRequest = 0;
			GAME_VAR(int, answer) = code;
			return;
		}
}

/* 0x452620: the reply to the last request (g_netLastRequest) read: 10 the lobby's status (g_lobbyReplyCode into g_lobbyStatus), 13 the
   server list (the lobby's: net_receiveLobbyReply), 14 / 15 the game server's answers (kept in g_gameServerAnswer / g_newIdAnswer), 18 its status (g_gameServerReplyCode into
   g_gameServerStatus), 19 the room list (net_receiveGameServerReply), 21 the player list, 26 the player list cleared (g_playerListDone), 29 a 0x22-byte notice
   (g_rankReplyCode; g_rankReplyIn when it is not empty). The callers ignore the eax it leaves */
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
		answer_reply(ADDR(g_newIdAnswer), answers15, 4, start);
		break;
	case 18:
		status_reply(ADDR(g_gameServerSocket), OBJ(g_gameServerReplyCode), ADDR(g_gameServerStatus), 0x28, start);
		break;
	case 19:
		net_receiveGameServerReply();
		break;
	case 21:
		net_receivePlayerListReply();
		break;
	case 26:
		net_clearPlayerList();
		g_playerListDone = 1;
		g_netLastRequest = 0;
		break;
	case 29:
		recv_all(ADDR(g_gameServerSocket), (void *)ADDR(g_rankReplyCode), 0x22, start);
		if (g_rankReplyCode) {
			g_rankReplyIn = 1;
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

/* a match packet (0x40 bytes) sent and counted (packetsSent); while recording (recording 1) the frame (recordTime),
   the camera's actor (localPlayer), the packet's size and the packet written to the recording (replayFile) */
static void send_packet(u8 *s, u8 *packet)
{
	Scene *sc = (Scene *)s;
	net_sendPacketData(0x40, packet);
	sc->packetsSent++;
	if (sc->recording == 1) {
		int size = 0x40;
		file_writeScrambled(&sc->recordTime, 4, 1, sc->replayFile);
		file_writeScrambled(&sc->localPlayer, 4, 1, sc->replayFile);
		file_writeScrambled(&size, 4, 1, sc->replayFile);
		file_writeScrambled(packet, 1, size, sc->replayFile);
	}
}

/* 0x48ead0 (thiscall on the scene): the map items' states sent (a 0x40-byte packet, kind 0xe in its second byte): one
   nibble each for up to 124 items (the stage's items, itemCount of them; two to a byte from the third, the even one
   low), an item that is there (type not negative) and taken: its timer / 10 + 1, at most 15 (each byte cleared at its
   even item). Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendItemStates_body(u8 *s, u8 *packet)
{
	packet[1] = 0xe;
	for (int i = 0; i < SCENE_STAGE(s)->itemCount && i < 0x7c; i++) {
		const MapItem *it = &SCENE_STAGE(s)->items[i];
		if (i % 2 == 0)
			packet[2 + i / 2] = 0;
		if (it->type < 0 || it->taken != 1)
			continue;
		int level = ftol(it->timer) / 10 + 1;
		if (level > 15)
			level = 15;
		packet[2 + i / 2] |= (u8)(i % 2 ? level << 4 : level);
	}
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendItemStates, 0);

/* 0x48e0f0 (thiscall on the scene): player p's info sent once when flagged (sendFlags[][1] + p x 0x10, cleared): packet
   2 (64 bytes, its first byte left as it was): from its PlayerRecord the name, then +0x13 its character, +0x14 its
   team, its actor's emblem, p, the five parts and six items (each + 1), the 30 colour bytes (hue, saturation, value). Sent by send_packet. Its caller ignores the eax it
   leaves */
static void THISCALL __attribute__((used)) net_sendPlayerInfo_body(u8 *s, int p, u8 *packet)
{
	Scene *sc = (Scene *)s;
	int *flag = &sc->sendFlags[p][1];
	if (!*flag)
		return;
	PlayerRecord *r = &sc->playerRecords[p];
	packet[1] = 2;
	strcpy((char *)packet + 2, r->name);
	packet[0x14] = (u8)r->team;
	packet[0x13] = (u8)r->character;
	packet[0x16] = (u8)p;
	packet[0x15] = (u8)(sc)->players[p].grade;
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
   slot of the count g_serviceProviderCount, which counts up to 9), and by its kind (the name containing "TCP", "IPX", "MODEM" or
   its Korean name, "SERIAL" or its Korean name) its GUID (g_tcpProviderGuid, g_ipxProviderGuid, g_modemProviderGuid, g_serialProviderGuid) and a copy of its
   connection data (GlobalAlloc'ed, g_connectionCopy; 0xa0bae0 .. 0xa0baec). Returns 1 (go on) */
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
		if (text_findSubstring(own, (const char *)kinds[k].words[0], 1) ||
		    (kinds[k].words[1] && text_findSubstring(own, (const char *)kinds[k].words[1], 1))) {
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
   packet (kind in the second byte; 0x6b where it carries nothing): 3, 4, 5 (endEvents[0], endEvents[1], endEvents[2]); 6 two
   bytes (cheatPending: cheatPlayer, cheatCode); 7 a byte and a line (chatPending: chatPlayer, chatLine; and byte
   0x3c from chatTeam); 8 the same (connectPending: connectPlayer, connectName); 9 a byte (quitPending: quitPlayer); 10 two
   bytes and a line (joinPending: joinPlayer, joinTeam, joinName); 11 the local player (localPlayer), a byte and a line
   (changePending: changeTeam, changeName); 13 (restartPending). With none pending any more the events are done
   (announcePending 0). Sent by send_packet (even with nothing pending). Its callers ignore the eax it leaves */
static void THISCALL __attribute__((used)) net_sendMatchEvent_body(u8 *s, u8 *packet)
{
#define SC ((Scene *)s)
#define FLAG(offset) GAME_VAR(int, s + (offset))
#define TAKE(f) ((f) == 1 && ((f) = 0, 1))   /* a pending event taken */
	static const u32 flags[10] = { offsetof(Scene, chatPending), offsetof(Scene, connectPending), offsetof(Scene, quitPending), offsetof(Scene, joinPending), offsetof(Scene, changePending), offsetof(Scene, endEvents[0]), offsetof(Scene, endEvents[1]), offsetof(Scene, endEvents[2]), offsetof(Scene, cheatPending), offsetof(Scene, restartPending) };
	if (TAKE(SC->endEvents[0]))
		packet[1] = 3, packet[2] = 0x6b;
	else if (TAKE(SC->endEvents[1]))
		packet[1] = 4, packet[2] = 0x6b;
	else if (TAKE(SC->endEvents[2]))
		packet[1] = 5, packet[2] = 0x6b;
	else if (TAKE(SC->cheatPending))
		packet[1] = 6, packet[2] = (u8)SC->cheatPlayer, packet[3] = (u8)SC->cheatCode;
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
	} else if (TAKE(SC->restartPending))
		packet[1] = 13, packet[2] = 0x6b;
	int pending = 0;
	for (int k = 0; k < 10; k++)
		pending |= FLAG(flags[k]) != 0;
	if (!pending)
		SC->announcePending = 0;
	send_packet(s, packet);
#undef FLAG
#undef TAKE
#undef SC
}
PACKET_ENTRY(net_sendMatchEvent, 0);

/* 0x48e990 (thiscall on the scene): player p's flag sent in pieces (packet 0xc, p): when it is in the atlas or
   changed (its record's flagShown, flagChanged) the position reached (flagSent, as a short) and the 16 pixels from
   there (their RGB, 3 bytes each), the position then 16 on; else 0xffff and the position back to 0x180 (all sent).
   Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendFlagPiece_body(u8 *s, int p, u8 *packet)
{
	PlayerRecord *pr = &((Scene *)s)->playerRecords[p];
	packet[1] = 0xc;
	packet[2] = (u8)p;
	if (pr->flagShown == 1 || pr->flagChanged == 1) {
		int at = pr->flagSent;
		memcpy(packet + 3, &at, 2);
		for (int k = 0; k < 16; k++)
			memcpy(packet + 5 + k * 3, (u8 *)pr->flag + (at + k) * 4, 3);
		pr->flagSent = at + 16;
	} else {
		packet[3] = packet[4] = 0xff;
		pr->flagSent = 0x180;
	}
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendFlagPiece, 1);

/* a float in memory times a constant, truncated (the original's __ftol) */
static int scaled(const void *v, u32 k)
{
	return ftol(fmul_m(fld_m((const float *)RELOC(v)), (const float *)RELOC(k)));
}

/* an angle wrapped into a turn (angle_wrap, given the float's bits) times k_0_0711111f, truncated */
static int angle_byte(const void *v)
{
	return ftol(fmul_m(angle_wrap_bits(*(const u32 *)RELOC(v)), k_0_0711111f));
}

/* 0x48e2c0 (thiscall on the game): player p's state sent (packet 0; the actor at players + p x 0x8888): its
   flags word (stateFlags), a byte of p and its mode (chatIcon: 0 with slot, 1, 2; bit 0 in play state), the position
   (nextPos, x k_0_1f, words), two angles (nextPitch, nextYaw) and two tilts (nextForward, nextStrafe), two nibbles (nextClimb,
   nextRun), a third angle (nextLean); a pending hit (hitPending: cleared) as 0x80 alive / 0xc0 dead with the attacker
   (lastAttacker) and value (lastHitWeapon); then its five shot slots (shotBullets, nine bytes each): a slot whose shot (0x4e8 bytes
   from the stage's bullets) is gone is cleared (-1); else flags (1, 3 for a new one: shots[].isNew + slot x 0x20 cleared; 4 aimed
   at an actor, 8 its life run out, age > life: the round has ended), the target (hitActor, or the object's index + 1, or 0)
   and the position (impact once it has ended on an object, else pos). Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendPlayerState_body(u8 *g, int p, u8 *packet)
{
	u8 *a = (u8 *)&((Scene *)g)->players[p];
	Actor *pl = (Actor *)a;
	u16 w;
	packet[1] = 0;
	memcpy(packet + 2, &pl->stateFlags, 2);
	switch (pl->chatIcon) {
	case 0: packet[4] = (u8)((((u8)p << 3) | (u8)pl->slot) << 1); break;
	case 1: packet[4] = (u8)(p << 4 | 0xc); break;
	case 2: packet[4] = (u8)(p << 4 | 0xe); break;
	}
	if (pl->state == 1)
		packet[4] |= 1;
	for (int c = 0; c < 3; c++) {
		w = (u16)scaled(&pl->nextPos[c], ADDR(k_0_1f));
		memcpy(packet + 5 + c * 2, &w, 2);
	}
	packet[0xb] = (u8)angle_byte(&pl->nextPitch);
	packet[0xc] = (u8)angle_byte(&pl->nextYaw);
	packet[0xd] = (u8)scaled(&pl->nextForward, ADDR(k_10f));
	packet[0xe] = (u8)scaled(&pl->nextStrafe, ADDR(k_10f));
	packet[0xf] = (u8)(scaled(&pl->nextClimb, ADDR(k_15f)) << 4) | (u8)scaled(&pl->nextRun, ADDR(k_15f));
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
		int *slot = &pl->shotBullets[k], *fresh = &pl->shots[k].isNew;
		u8 *o = packet + 0x13 + k * 9;
		if (*slot < 0)
			continue;
		Bullet *shot = (Bullet *)((u8 *)&SCENE_STAGE(g)->bullets[*slot]);
		if (shot->active != 1) {
			*slot = -1;
			continue;
		}
		if (*fresh == 1) {
			o[0] |= 3;
			*fresh = 0;
		} else
			o[0] |= 1;
		if (shot->hitActor >= 0) {
			o[0] |= 4;
			w = (u16)shot->hitActor;
		} else if ((*(void * *)&shot->hit))
			w = (u16)(array_indexOf((*(void * *)&shot->hit), (int)SCENE_STAGE(g)->space.planes.records, 0xac) + 1);
		else
			w = 0;
		memcpy(o + 1, &w, 2);
		int ended = shot->age > shot->life;
		if (ended)
			o[0] |= 8;
		u8 *at = (u8 *)(ended && (*(void * *)&shot->hit) ? shot->impact : shot->pos);
		for (int c = 0; c < 3; c++) {
			w = (u16)scaled(at + c * 4, ADDR(k_0_1f));
			memcpy(o + 3 + c * 2, &w, 2);
		}
	}
	send_packet(g, packet);
}
PACKET_ENTRY(net_sendPlayerState, 1);

/* the next value of the game's table of rand() values (g_randTable, 4096 of them; the position g_randPos moves on) */
static u32 table_rand(void)
{
	u32 at = g_randPos;
	g_randPos = at + 1;
	return (*(u32 *)&g_randTable[at & 0xfff]);
}

/* a random entry of one of the type tables (the part types' and actorItems) (rows of row_len dwords from base, rows of them at +rows,
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

/* 0x48dbf0 (thiscall on the scene): player p's game packet (1), sent when flagged (sendFlags + p x 0x10, cleared):
   the room's game (its map and modes from rotation / nextMap ..; 0xff and 0xffff without one, or once the end
   countdown endTime is running), the clock (elapsed, clockFraction), the player's two scores (players[].timePlayed,
   players[].timeFraction of its actor), which of the players in use (net_playerInUse) asked for a resend (resendAsked: sendFlags[][2],
   sendFlags[][3]: cleared, one bit each), the actor's two counts (players[].kills / deaths) and the team scores (teamScores[0] /
   [1]), the last pickup (lastPickup, set back to -1), then two random checks of the data: one of the five part type
   tables in turn (typeCheckTurn counting; its number in byte 0x2b) and the sixth, each a position and the entry there.
   Sent by send_packet. Its caller ignores the eax it leaves */
static void THISCALL __attribute__((used)) net_sendGamePacket_body(u8 *s, int p, u8 *packet)
{
	Scene *sc = (Scene *)s;
	static const struct { u32 per_row, rows; int row_len; u32 base; } tables[5] = {
		{ 0x23423e5, 0x15de6c8, 682, 0x15bd1f8 }, { 0x23423e9, 0x15fff84, 687, 0x15de6cc },
		{ 0x23423ed, 0x163b588, 0x4c0, 0x15fff88 }, { 0x23423f1, 0x1679b34, 1277, 0x163b58c },
		{ 0x23423f5, 0x16c5178, 1544, 0x1679b38 } };
	int *flag = &sc->sendFlags[p][0];
	if (!*flag)
		return;
	packet[1] = 1;
	packet[2] = (u8)p;
	if (sc->rotationCount > 0 && !(sc->endTime > k_0f)) {
		int k = sc->rotationAt * 16;
		packet[3] = s[0x1f1668 + k];
		packet[4] = s[0x1f1cb4];
		packet[5] = s[0x1f166c + k];
		packet[6] = s[0x1f1cb8];
		memcpy(packet + 7, &sc->mapNumber, 2);
	} else
		memset(packet + 3, 0xff, 6);
	memcpy(packet + 9, &sc->elapsed, 4);
	float clock = f32(fld_m(&sc->clockFraction));
	memcpy(packet + 0xd, &clock, 4);
	u32 turn = ((u32)(sc)->typeCheckTurn);
	packet[0x2b] = (u8)(turn % 5);
	sc->typeCheckTurn = turn + 1;
	u32 v = sample(s, tables[packet[0x2b]].per_row, tables[packet[0x2b]].rows, tables[packet[0x2b]].row_len, tables[packet[0x2b]].base,
	               packet + 0x2c);
	memcpy(packet + 0x2e, &v, 4);
	v = sample(s, 0x23423f9, 0x175522c, 2950, 0x16c517c, packet + 0x32);
	memcpy(packet + 0x34, &v, 4);
	memcpy(packet + 0x11, &sc->players[p].timePlayed, 4);
	memcpy(packet + 0x15, &sc->players[p].timeFraction, 4);
	u32 resendAsked[2] = { 0, 0 };
	for (int i = 0; i < 16; i++) {
		if (net_playerInUse(i) != 1)
			continue;
		for (int k = 0; k < 2; k++) {
			int *f = &sc->sendFlags[i][2 + k];
			if (*f == 1) {
				*f = 0;
				resendAsked[k] |= 1u << i;
			}
		}
	}
	memcpy(packet + 0x19, resendAsked, 8);
	memcpy(packet + 0x21, &sc->players[p].kills, 2);
	memcpy(packet + 0x23, &sc->players[p].deaths, 2);
	memcpy(packet + 0x25, &sc->teamScores[0], 2);
	memcpy(packet + 0x27, &sc->teamScores[1], 2);
	memcpy(packet + 0x29, &SCENE_STAGE(s)->lastPickup, 2);
	SCENE_STAGE(s)->lastPickup = -1;
	*flag = 0;
	send_packet(s, packet);
}
PACKET_ENTRY(net_sendGamePacket, 1);

#define G(type, offset) GAME_VAR(type, g + (offset))
#define GS ((Scene *)g)   /* the same by its fields (src/scene.fields) */
#undef STAGE   /* (game.h's takes the scene; here g's stage as a byte pointer) */
#define STAGE ((u8 *)SCENE_STAGE(g))
#define ACTOR(i) ((u8 *)&((Scene *)g)->players[i])   /* the stage's actors, from the game object */
#define PLAYER(i) ((u8 *)&((Scene *)g)->playerRecords[i])

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
static float tens(int v) { return f32(fmul_m((long double)v, &k_10f)); }

/* a table entry's checksum against the packet's: word w into a table of 'per' columns (count, stride) */
static int table_ok(u8 *g, u32 base, u32 per, u32 count, int stride, u16 w, u32 sum)
{
	int n = G(int, per);
	int row = (int)w / n % G(int, count);
	return G(u32, base + (row * stride + (int)w % n) * 4) == sum;
}

/* a player's name copied into its actor (name) and the slot's own index noted (player) */
static void actor_name(u8 *g, int i, const char *name)
{
	char *to = ((Actor *)ACTOR(i))->name;
	if (name)
		strcpy(to, name);
	else
		to[0] = 0;
	((Actor *)ACTOR(i))->player = i;
}

/* team change (kinds 10 / 11): the team, team colours when team colours are on, the name, the notice; a player
   leaving the teams (negative) who is alive is taken out and gets a death */
static void team_change(u8 *g, int i, const char *pkt, u32 notice)
{
	player_setTeam(STAGE, i, pkt[3]);   /* player_setTeam */
	if (GS->teamGame == 1) {
		int t = scene_claimTeamSlot(g, pkt[3]);
		for (int k = 0; k < 5; k++)
			GAME_THISFN(playerRecord_setPartColour, 0x474b50, void, void *, int, int, u32, u32, u32, u32, u32, u32)(STAGE, i, k, GAME_VAR(u32, OBJ(k_teamHue) + t * 4),
			                                                                             GAME_VAR(u32, OBJ(k_teamSaturation) + t * 4),
			                                                                             GAME_VAR(u32, OBJ(k_teamValue) + t * 4), 0,
			                                                                             0xbf800000, 0x3f7fbe77);   /* playerRecord_setPartColour */
	}
	player_setName(STAGE, i, pkt + 4);   /* player_setName */
	actor_name(g, i, pkt + 4);
	GAME_THISCALL(notice, void, void *, int, int)(g, i, pkt[3]);
	if (pkt[3] >= 0 || ((Actor *)ACTOR(i))->inPlay != 1)
		return;
	actor_deactivate(STAGE, i);   /* actor_deactivate */
	((Actor *)ACTOR(i))->deaths++;
}

/* the end of a match's limit (kinds 4 / 5, state 0 frags or 1 time): once, its notice, and the result for team
   play (the red team's score teamScores[0] against the blue teamScores[1]: 0 red ahead, 1 blue, -1 level) */
static void match_limit(u8 *g, int state, u32 notice)
{
	if (GS->elapsed <= 0x1e || GS->endReason == state)
		return;
	GS->endReason = state;
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

/* 0x48c830 (thiscall on the game object): a network packet (of 0x40 bytes only) from a player. When recording
   (recording) it goes to the replay file first; while the game is starting (matchState 1) only kind 1. By the kind
   (byte 1): 0 a player's state (position, aim, weapon, lights, the five weapon slots; a player not yet set up is
   asked for); 1 the game state (round, time, map change, the checksums of the part and item tables, scores, items);
   2 a player joining with his mech; 3 the server ending the game; 4 / 5 the frag / time limit; 6 a cheat notice; 7
   a chat line; 8 a player connecting; 9 one leaving; 10 / 11 team changes; 12 a player's flag rows; 13 a restart
   (restartTimer 5 s; net_sendMatchEvent's restartPending); 14 the items' states. Anything else goes to shared_emptyFunction (nothing) */
void THISCALL (net_processGamePacket)(u8 *g, u32 from, int size, const char *pkt)
{
	if (size != 0x40)
		return;
	if (GS->recording == 1) {
		void *f = GS->replayFile;
		file_writeScrambled((u8 *)&GS->recordTime, 4, 1, f);
		file_writeScrambled(&from, 4, 1, f);
		file_writeScrambled(&size, 4, 1, f);
		file_writeScrambled(pkt, 1, size, f);
	}
	if (GS->matchState == 1 && pkt[1] != 1)
		return;
	const u8 *b = (const u8 *)pkt;
	switch (b[1]) {
	case 0: {
		int itemSlot = (b[4] >> 1) & 7, i = b[4] >> 4;
		float x = tens(*(const short *)(pkt + 5)), y = tens(*(const short *)(pkt + 7)), z = tens(*(const short *)(pkt + 9));
		long double h = fmul_m((long double)b[0xb], &k_14_0625f);
		float pitch = f32(h);   /* b[0xb]: the pitch, b[0xc]: the heading (nextPitch, nextYaw) */
		if (h > *&k_1800f)
			pitch = f32(FSUB(pitch, k_3600f));
		float yaw = f32(fmul_m((long double)b[0xc], &k_14_0625f));
		if (GAME_VAR(int, PLAYER(i)) == 0) {
			GS->sendFlags[GS->localPlayer][0] = 1;
			GS->sendFlags[i][2] = 1;
			return;
		}
		Actor *ac = (Actor *)(ACTOR(i));
		if ((*(const u16 *)&ac->stateFlags ^ *(const u16 *)(pkt + 2)) & 0x4000)
			actor_deactivate(STAGE, i);   /* actor_deactivate */
		if (ac->active == 0 && (b[4] & 1)) {
			u32 rec[7] = { (u32)i, 0 };
			memcpy(&rec[2], &x, 4);
			memcpy(&rec[3], &y, 4);
			memcpy(&rec[4], &z, 4);
			memcpy(&rec[5], &pitch, 4);
			memcpy(&rec[6], &yaw, 4);
			stage_setupActorSlot((Stage *)STAGE, i, -1, from, rec);
			scene_updateRanking(g);   /* scene_updateRanking */
		}
		ac->netFired = 1;
		ac->dropAge = f32(FADD(ac->spawnAge, k_10f));
		BITS(ac->stateFlags) = *(const u16 *)(pkt + 2);
		if (itemSlot == 6)
			ac->chatIcon = 1;
		else if (itemSlot == 7)
			ac->chatIcon = 2;
		else {
			ac->chatIcon = 0;
			actor_setWeaponSlot(STAGE, i, itemSlot);   /* actor_setWeaponSlot */
		}
		ac->netPos[0] = x;
		ac->netPos[1] = y;
		ac->netPos[2] = z;
		ac->netPitch = pitch;
		ac->netYaw = yaw;
		ac->netMotion[0] = f32(fmul_m((long double)(signed char)b[0xd], &k_tenth));
		ac->netMotion[1] = f32(fmul_m((long double)(signed char)b[0xe], &k_tenth));
		ac->netMotion[2] = f32(fmul_m((long double)(b[0xf] >> 4), &k_0_06666667f));
		ac->netMotion[4] = f32(fmul_m((long double)(b[0xf] & 0xf), &k_0_06666667f));
		h = fmul_m((long double)b[0x10], &k_14_11765f);
		ac->netMotion[3] = f32(h);
		if (h > *&k_1800f)
			ac->netMotion[3] = f32(fsub_m(h, &k_3600f));
		int hurt;
		if (b[0x11] & 0x80) {
			ac->lastAttacker = b[0x11] & 0xf;
			ac->lastHitWeapon = b[0x12];
			hurt = 1;
			if ((b[0x11] & 0x40) && ac->armor > 0)
				ac->armor = 0;
		} else {
			hurt = !(b[4] & 1) && ac->armor > 0;
			if (hurt)
				ac->armor = 0;
		}
		if (hurt)
			ac->hitFlash = 0.5f;
		const u8 *w = b + 0x13;
		for (int k = 0; k < 5; k++, w += 9) {
			u32 *slot = (u32 *)&ac->shots[k];
			if (!(w[0] & 1) || ac->team < 0) {
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
			GS->elapsed = ((const GamePacket *)pkt)->elapsed;
			BITS(GS->clockFraction) = BITS(((const GamePacket *)pkt)->clockFraction);
			if (pkt[3] >= 0) {
				int mapIndex = g_mapIndex;
				if (mapIndex != pkt[3] && (mapIndex < 0 || GS->awaitingHostRound == 1 || GS->elapsed > 0x1e)) {
					g_mapIndex = pkt[3];
					GS->nextMap = pkt[4];
					GS->nextMode = pkt[6];
					scene_setMapName((Scene *)g, g_mapNames + g_mapIndex * 0x20);
					GS->matchState = 1;
					GS->stateFrames = 0;
					game_setGameTypeFlags((Stage *)STAGE, pkt[5]);
					GS->awaitingHostRound = 0;
					return;
				}
				GS->nextMap = pkt[4];
				GS->nextMode = pkt[6];
				if (g_mapIndex == pkt[3] && GS->mapNumber != *(const short *)(pkt + 7)) {
					GS->dataLossPending = 1;
					GS->dataLossCode = 1;
				}
			}
			static const u32 parts[5][4] = {   /* each part kind's type table, its typeTablePerRow (dwords sampled a record), its count, its record in dwords */
				{ SCENE_STAGE_AT + offsetof(Stage, headTypes), offsetof(Scene, typeTablePerRow[0]), offsetof(Scene, headCount), sizeof(HeadType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, chestTypes), offsetof(Scene, typeTablePerRow[1]), offsetof(Scene, chestCount), sizeof(ChestType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, armTypes), offsetof(Scene, typeTablePerRow[2]), offsetof(Scene, armCount), sizeof(ArmType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, legTypes), offsetof(Scene, typeTablePerRow[3]), offsetof(Scene, legCount), sizeof(LegType) / 4 },
				{ SCENE_STAGE_AT + offsetof(Stage, boosterTypes), offsetof(Scene, typeTablePerRow[4]), offsetof(Scene, boosterCount), sizeof(BoosterType) / 4 } };
			u16 w = ((const GamePacket *)pkt)->checkIndex;
			int part = b[0x2b];
			if (part <= 4 && !table_ok(g, parts[part][0], parts[part][1], parts[part][2], parts[part][3], w, ((const GamePacket *)pkt)->checkValue)) {
				GS->dataLossPending = 1;
				GS->dataLossCode = 2;
			}
			if (!table_ok(g, offsetof(Scene, actorItems), offsetof(Scene, typeTablePerRow[5]), offsetof(Scene, actorItemCount), sizeof(ActorItem) / 4, ((const GamePacket *)pkt)->checkIndex2, ((const GamePacket *)pkt)->checkValue2)) {
				GS->dataLossPending = 1;
				GS->dataLossCode = 3;
			}
		}
		Actor *ac = (Actor *)(ACTOR(b[2]));
		ac->timePlayed = ((const GamePacket *)pkt)->timePlayed;
		BITS(ac->timeFraction) = BITS(((const GamePacket *)pkt)->timeFraction);
		int me = GS->localPlayer;
		if (((const GamePacket *)pkt)->resendAsked[0] & 1u << (me & 0x1f))
			GS->sendFlags[me][1] = 1;
		if (((const GamePacket *)pkt)->resendAsked[1] & 1u << (me & 0x1f))
			((PlayerRecord *)PLAYER(me))->flagSent = 0;
		((Actor *)ACTOR(b[2]))->kills = ((const GamePacket *)pkt)->kills;
		((Actor *)ACTOR(b[2]))->deaths = ((const GamePacket *)pkt)->deaths;
		if (b[2] == 0) {
			GS->teamScores[0] = ((const GamePacket *)pkt)->teamScores[0];
			GS->teamScores[1] = ((const GamePacket *)pkt)->teamScores[1];
		}
		short item = ((const GamePacket *)pkt)->lastPickup;
		if ((GS->sessionMode != 3 || GS->replayVersion > 0x1201) && item >= 0 && SCENE_STAGE(g)->items[item].taken == 0) {
			SCENE_STAGE(g)->items[item].taken = 1;
			BITS(SCENE_STAGE(g)->items[item].timer) = 0;
		}
		if (GS->sessionMode == 3 && GS->replayVersion >= 0x1202)
			scene_updateRanking(g);   /* scene_updateRanking */
		return;
	}
	case 2: {
		const char *name = pkt + 2;
		const u8 *m = b + 2;   /* the record after the name's 0x11 bytes */
		int i = m[0x14], lim = GS->actorItemCount;
		if (strlen(name) >= 0x11 || (signed char)m[0x11] < 0 || (signed char)m[0x11] > 8 || i >= 0x10 || m[0x15] > GS->headCount ||
		    m[0x16] > GS->chestCount || m[0x17] > GS->armCount || m[0x18] > GS->legCount || m[0x19] > GS->boosterCount)
			break;
		int bad = 0;
		for (int k = 0; k < 6; k++)
			bad |= m[0x1a + k] > lim;
		if (bad)
			break;
		((Actor *)ACTOR(i))->player = i;
		player_setName(STAGE, i, name);   /* player_setName */
		player_setCharacter(STAGE, i, (signed char)m[0x11]);
		player_setTeam(STAGE, i, (signed char)m[0x12]);   /* player_setTeam */
		static const u32 setters[5] = { FN_ADDR(actor_setActorTypeHeadInfoBy, 0x473b10), FN_ADDR(actor_setActorTypeChestInfoBy, 0x473c20), FN_ADDR(actor_setActorTypeArmInfoBy, 0x473d30), FN_ADDR(actor_setActorTypeLegInfoBy, 0x473e40), FN_ADDR(actor_setActorTypeBoosterInfoBy, 0x473f50) };   /* head .. booster */
		for (int k = 0; k < 5; k++)
			GAME_THISCALL(setters[k], int, void *, int, int)(STAGE, i, m[0x15 + k] - 1);
		for (int k = 0; k < 6; k++)
			actor_setActorTypeItemInfoBy(STAGE, i, k, m[0x1a + k] - 1);   /* actor_setActorTypeItemInfoBy */
		((Actor *)ACTOR(i))->grade = (signed char)m[0x13];
		char *to = ((Actor *)ACTOR(i))->name;
		if (name)
			strcpy(to, name);
		else
			to[0] = 0;
		((Actor *)ACTOR(i))->levelShown = ((Actor *)ACTOR(i))->grade;
		const u8 *c = m + 0x2b;
		/* (the original loads each colour byte into al / cl and pushes the whole register: on the first part the
		   rest of eax is left from the actor's address and of ecx from its grade; later eax holds the player and ecx what
		   the call left) */
		u32 hi_a = (u32)(g + i * 0x8888) & ~0xffu, hi_c = *(u32 *)&((Actor *)ACTOR(i))->grade & ~0xffu;
		for (int k = 0; k < 5; k++, c += 2) {
			u32 left = thiscall8_ecx(FN_ADDR(playerRecord_applyNetColours, 0x474fd0), STAGE, i, k, hi_c | c[-0xb], hi_a | c[-1], hi_c | c[9], hi_a | c[-0xa], hi_c | c[0],
			                         hi_a | c[0xa]);   /* playerRecord_applyNetColours */
			hi_a = 0;
			hi_c = left & ~0xffu;
		}
		if (((PlayerRecord *)PLAYER(i))->team >= 0)
			playerRecord_markUsed(STAGE, i);
		return;
	}
	case 3:
		if (pkt[2] != 'k')
			break;
		if (GS->endReason == 2)
			return;
		GS->endReason = 2;
		msg_serverEndsGame(g);
		if (GS->matchLeaving)
			return;
		GS->matchLeaving = 1;
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
			net_sendItemStates(g);   /* net_sendItemStates */
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
		PlayerRecord *p = (PlayerRecord *)PLAYER((signed char)pkt[2]);
		if (row >= 0) {
			u8 *to = (u8 *)p->flag + row * 4;   /* (16 pixels from pixel row: the grid as one run) */
			const u8 *from3 = b + 5;
			for (int k = 0; k < 16; k++, from3 += 3, to += 4) {
				to[0] = from3[0];
				to[1] = from3[1];
				to[2] = from3[2];
				to[3] = from3[0] || from3[1] || from3[2] ? 0xff : 0;
			}
		}
		if (p->flagChanged)
			return;
		PlayerRecord *mine = (PlayerRecord *)PLAYER(GS->localPlayer);
		if (p->flagShown == 0 && (mine->flagShown == 1 || mine->flagChanged == 1))
			mine->flagSent = 0;
		GS->flagUploadTimer = 5.0f;
		if (*(const short *)(pkt + 3) < 0)
			return;
		p->flagChanged = 1;
		return;
	}
	case 13:
		if (pkt[2] != 'k')
			break;
		GS->restartTimer = 5.0f;
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
				it->taken = BITS(it->timer) = 0;
			else {
				it->taken = 1;
				it->timer = f32(fmul_m((long double)n, &k_10f));
			}
		}
		GS->itemLevelsTaken = 1;
		return;
	}
	GAME_FN(shared_emptyFunction, 0x48b420, void, const char *)(pkt);   /* shared_emptyFunction */
}
#undef G
#undef GS
#undef STAGE
#undef ACTOR
#undef PLAYER
