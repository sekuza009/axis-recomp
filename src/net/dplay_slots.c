/* dplay_slots.c: the four DirectPlay connection slots the arena screen opens (0 and 1 the first two connection
   kinds, 2 and 3 the others), each with its own small set of functions: open on a connection kind, close, list the
   sessions, host and join through it. A slot is 1 while its connection is up. */
#include "../game.h"
#include <string.h>

/* close slot k (close is the slot's own close function, called through the game as the original does) */
static int slot_close(int k)
{
	if (g_dplaySlots[k] == 0)
		return 0;
	g_dplaySlots[k] = 0;
	return dplay_release();
}

/* open slot k on connection kind k with address data: COM up, the kind available (else the slot is closed),
   the connection made; 1 when open */
static int slot_open(int k, int address, int (*close)(void))
{
	if (dplay_coInit() != 0)
		return 0;
	if (!dplay_connectionAvailable(k)) {
		g_dplaySlots[k] = 0;
		close();
		return 0;
	}
	if (!dplay_initConnection(k, address))
		return 0;
	g_dplaySlots[k] = 1;
	return 1;
}

static int slot_enum(int k)
{
	return g_dplaySlots[k] ? dplay_enumSessions() : 0;
}

static int slot_host(int k, int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data)
{
	return g_dplaySlots[k] ? dplay_hostSession(session, player, user1, maxPlayers, user2, hi, lo, data) : 0;
}

/* 0x1f4 when the slot is closed; the game mode is passed on but dplay_joinSession does not read it */
static int slot_join(int k, int guid, int player, int data, int gameMode)
{
	return g_dplaySlots[k] ? dplay_joinSession(guid, player, data, gameMode) : 0x1f4;
}

static int close0(void) { return dplaySlot0_close(); }
static int close1(void) { return dplaySlot1_close(); }
static int close2(void) { return dplaySlot2_close(); }
static int close3(void) { return dplaySlot3_close(); }

/* slots 0 and 1 are opened afresh (closed first if open); slots 2 and 3 stay as they are when already open */
int (dplaySlot0_open)(int address)
{
	if (g_dplaySlots[0] != 0) {
		close0();
		g_dplaySlots[0] = 0;
	}
	return slot_open(0, address, close0);
}

int (dplaySlot1_open)(int address)
{
	if (g_dplaySlots[1] != 0) {
		close1();
		g_dplaySlots[1] = 0;
	}
	return slot_open(1, address, close1);
}

int (dplaySlot2_open)(int address)
{
	if (g_dplaySlots[2] != 0)
		return 1;
	return slot_open(2, address, close2);
}

int (dplaySlot3_open)(int address)
{
	if (g_dplaySlots[3] != 0)
		return 1;
	return slot_open(3, address, close3);
}

/* close: dplaySlot0_close, dplaySlot1_close, dplaySlot2_close, dplaySlot3_close */
int (dplaySlot0_close)(void) { return slot_close(0); }
int (dplaySlot1_close)(void) { return slot_close(1); }
int (dplaySlot2_close)(void) { return slot_close(2); }
int (dplaySlot3_close)(void) { return slot_close(3); }

/* list the sessions: dplaySlot0_enum, dplaySlot1_enum, dplaySlot2_enum, dplaySlot3_enum */
int (dplaySlot0_enum)(void) { return slot_enum(0); }
int (dplaySlot1_enum)(void) { return slot_enum(1); }
int (dplaySlot2_enum)(void) { return slot_enum(2); }
int (dplaySlot3_enum)(void) { return slot_enum(3); }

/* host: 0x4549e0, 0x454b00, 0x454c10, 0x454d20 (dplay_hostSession's eight arguments) */
int (dplaySlot0_host)(int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data) { return slot_host(0, session, player, user1, maxPlayers, user2, hi, lo, data); }
int (dplaySlot1_host)(int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data) { return slot_host(1, session, player, user1, maxPlayers, user2, hi, lo, data); }
int (dplaySlot2_host)(int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data) { return slot_host(2, session, player, user1, maxPlayers, user2, hi, lo, data); }
int (dplaySlot3_host)(int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data) { return slot_host(3, session, player, user1, maxPlayers, user2, hi, lo, data); }

/* join: 0x454a20, 0x454b40, 0x454c50, 0x454d60 */
int (dplaySlot0_join)(int guid, int player, int data, int gameMode) { return slot_join(0, guid, player, data, gameMode); }
int (dplaySlot1_join)(int guid, int player, int data, int gameMode) { return slot_join(1, guid, player, data, gameMode); }
int (dplaySlot2_join)(int guid, int player, int data, int gameMode) { return slot_join(2, guid, player, data, gameMode); }
int (dplaySlot3_join)(int guid, int player, int data, int gameMode) { return slot_join(3, guid, player, data, gameMode); }

/* 0x453770: DirectPlay checked once more: net_resetState, then a DirectPlay object made and released again */
int (dplay_check)(void)
{
	net_resetState();
	if (dplay_create() != 0)
		dplay_release();
	return 0;
}

/* 0x453090: a session hosted through the slot of connection kind g_connectionKind (dplay_hostSession's eight arguments passed on); 0 for an
   unknown kind */
int (dplay_host)(int session, int player, int user1, int maxPlayers, int user2, int hi, int lo, int data)
{
	u32 kind = (*(u32 *)&g_connectionKind);
	if (kind > 3)
		return 0;
	return dplay_slotHost(kind, session, player, user1, maxPlayers, user2, hi, lo, data);
}

/* 0x453180: session `session` joined through the slot of connection kind g_connectionKind (with its game mode); 0x1f7 when
   there is no such session, 0x1f5 when it is full (players == maxPlayers), 0 for an unknown kind */
int (dplay_join)(int session, int guid, int player, int data)
{
	const SessionDesc *rec = (const SessionDesc *)net_sessionValue(session);
	if (!rec)
		return 0x1f7;
	if (rec->players == rec->maxPlayers)
		return 0x1f5;
	u32 kind = (*(u32 *)&g_connectionKind);
	if (kind > 3)
		return 0;
	return dplay_slotJoin(kind, guid, player, data, (u8)rec->gameMode);
}

/* 0x452fe0: the arena session left (when one is open, g_arenaSessionOpen and g_sessionListOpen): the host tells everyone first
   (message g_netHostLeftMessageKind, flag g_hostGoneMessageFlag), the slot of the connection kind closed (the kind becomes 4), the session list
   freed (net_freeSessionList, whose eax it returns) and the session state cleared. 1 when there is no session */
u32 (arena_leaveSession)(void)
{
	static const u32 close[4] = { FN_ADDR(dplaySlot0_close, 0x4549a0), FN_ADDR(dplaySlot1_close, 0x454ac0), FN_ADDR(dplaySlot2_close, 0x454bd0), FN_ADDR(dplaySlot3_close, 0x454ce0) };
	if (g_arenaSessionOpen != 1 || !g_sessionListOpen)
		return 1;
	if (g_isHost) {
		g_hostGoneMessageFlag = 1;
		GAME_FN(net_sendMessage, 0x451270, int, void *, u32, u32)((void *)ADDR(g_netHostLeftMessageKind), 0, 0);   /* net_sendMessage: send */
	}
	u32 kind = (*(u32 *)&g_connectionKind);
	(*(u32 *)&g_connectionKind) = 4;
	if (kind <= 3)
		GAME_CDECL(close[kind], int, void)();
	u32 r = net_freeSessionList();   /* net_freeSessionList */
	g_sessionListOpen = 0;
	g_netQueueOnline = 0;
	g_arenaSessionOpen = 0;
	return r;
}

/* 0x452ec0: an arena session opened with connection kind (0 TCP/IP to host, which is resolved first; 1..3 the
   others): the old session left, the session state reset and the slot opened (dplaySlot0_open with the address, or
   dplaySlot1_open / dplaySlot2_open / dplaySlot3_open). The slot's answer (and the session marked open), or 0 */
int (arena_openSession)(u32 kind, const char *host)
{
	static const u32 open[4] = { FN_ADDR(dplaySlot0_open, 0x454940), FN_ADDR(dplaySlot1_open, 0x454a50), FN_ADDR(dplaySlot2_open, 0x454b70), FN_ADDR(dplaySlot3_open, 0x454c80) };
	char address[16] = { 0 };
	net_freeAllSlots();
	g_arenaSessionOpen = 1;
	if (host) {
		if (!net_resolveHost(host))   /* net_resolveHost */
			return 0;
		strcpy(address, g_resolvedAddress);
	}
	if (g_sessionListOpen) {
		if ((*(u32 *)&g_connectionKind) == kind) {
			arena_leaveSession();
			g_sessionListOpen = 0;
		} else
			arena_leaveSession();
	}
	(*(u32 *)&g_connectionKind) = kind;
	g_dplaySessionCount = 0;
	g_unusedSessionWord = 0;
	(*(int *)&g_localPlayerId) = 0;
	(*(int *)&g_localPlayerData) = 0;
	if (kind > 3)
		return 0;
	int r = kind == 0 ? GAME_CDECL(open[0], int, const char *)(address) : GAME_CDECL(open[kind], int, int)(0);
	if (!r)
		return 0;
	g_sessionListOpen = 1;
	g_netQueueOnline = 1;
	return r;
}
