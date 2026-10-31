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

static int slot_host(int k, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	return g_dplaySlots[k] ? dplay_hostSession(a1, a2, a3, a4, a5, a6, a7, a8) : 0;
}

/* 0x1f4 when the slot is closed */
static int slot_join(int k, int a1, int a2, int a3, int a4)
{
	return g_dplaySlots[k] ? dplay_joinSession(a1, a2, a3, a4) : 0x1f4;
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

/* close: 0x4549a0, 0x454ac0, 0x454bd0, 0x454ce0 */
int (dplaySlot0_close)(void) { return slot_close(0); }
int (dplaySlot1_close)(void) { return slot_close(1); }
int (dplaySlot2_close)(void) { return slot_close(2); }
int (dplaySlot3_close)(void) { return slot_close(3); }

/* list the sessions: 0x4549c0, 0x454ae0, 0x454bf0, 0x454d00 */
int (dplaySlot0_enum)(void) { return slot_enum(0); }
int (dplaySlot1_enum)(void) { return slot_enum(1); }
int (dplaySlot2_enum)(void) { return slot_enum(2); }
int (dplaySlot3_enum)(void) { return slot_enum(3); }

/* host: 0x4549e0, 0x454b00, 0x454c10, 0x454d20 (dplay_hostSession's eight arguments) */
int (dplaySlot0_host)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return slot_host(0, a1, a2, a3, a4, a5, a6, a7, a8); }
int (dplaySlot1_host)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return slot_host(1, a1, a2, a3, a4, a5, a6, a7, a8); }
int (dplaySlot2_host)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return slot_host(2, a1, a2, a3, a4, a5, a6, a7, a8); }
int (dplaySlot3_host)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8) { return slot_host(3, a1, a2, a3, a4, a5, a6, a7, a8); }

/* join: 0x454a20, 0x454b40, 0x454c50, 0x454d60 */
int (dplaySlot0_join)(int a1, int a2, int a3, int a4) { return slot_join(0, a1, a2, a3, a4); }
int (dplaySlot1_join)(int a1, int a2, int a3, int a4) { return slot_join(1, a1, a2, a3, a4); }
int (dplaySlot2_join)(int a1, int a2, int a3, int a4) { return slot_join(2, a1, a2, a3, a4); }
int (dplaySlot3_join)(int a1, int a2, int a3, int a4) { return slot_join(3, a1, a2, a3, a4); }

/* 0x453770: DirectPlay checked once more: net_resetState, then a DirectPlay object made and released again */
int (dplay_check)(void)
{
	net_resetState();
	if (dplay_create() != 0)
		dplay_release();
	return 0;
}

/* 0x453090: a session hosted through the slot of connection kind 0xa0b418 (its eight arguments passed on); 0 for an
   unknown kind */
int (dplay_host)(int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8)
{
	u32 kind = (*(u32 *)&g_connectionKind);
	if (kind > 3)
		return 0;
	return dplay_slotHost(kind, a1, a2, a3, a4, a5, a6, a7, a8);
}

/* 0x453180: session `session` joined through the slot of connection kind 0xa0b418 (with the session record's byte
   +0x27); 0x1f7 when there is no such session, 0x1f5 when it is full (+0x2a players of +0x26), 0 for an unknown kind */
int (dplay_join)(int session, int a2, int a3, int a4)
{
	const u8 *rec = (const u8 *)net_sessionValue(session);
	if (!rec)
		return 0x1f7;
	if (*(const int *)(rec + 0x2a) == rec[0x26])
		return 0x1f5;
	u32 kind = (*(u32 *)&g_connectionKind);
	if (kind > 3)
		return 0;
	return dplay_slotJoin(kind, a2, a3, a4, rec[0x27]);
}

/* 0x452fe0: the arena session left (when one is open, 0xa0b390 and 0xa0b384): the host tells everyone first
   (message 0x9f9418, flag 0x9f941c), the slot of the connection kind closed (the kind becomes 4), the session list
   freed (0x454130, whose eax it returns) and the session state cleared. 1 when there is no session */
u32 (arena_leaveSession)(void)
{
	static const u32 close[4] = { 0x4549a0, 0x454ac0, 0x454bd0, 0x454ce0 };
	if (g_arenaSessionOpen != 1 || !g_dplaySessionList)
		return 1;
	if (g_isHost) {
		g_hostResultFlag = 1;
		GAME_CDECL(0x451270, int, void *, u32, u32)((void *)0x9f9418, 0, 0);   /* net_sendMessage: send */
	}
	u32 kind = (*(u32 *)&g_connectionKind);
	(*(u32 *)&g_connectionKind) = 4;
	if (kind <= 3)
		GAME_CDECL(close[kind], int, void)();
	u32 r = GAME_CDECL(0x454130, u32, void)();   /* net_freeSessionList */
	g_dplaySessionList = 0;
	g_netQueueOnline = 0;
	g_arenaSessionOpen = 0;
	return r;
}

/* 0x452ec0: an arena session opened with connection kind (0 TCP/IP to host, which is resolved first; 1..3 the
   others): the old session left, the session state reset and the slot opened (0x454940 with the address, or
   0x454a50 / 0x454b70 / 0x454c80). The slot's answer (and the session marked open), or 0 */
int (arena_openSession)(u32 kind, const char *host)
{
	static const u32 open[4] = { 0x454940, 0x454a50, 0x454b70, 0x454c80 };
	char address[16] = { 0 };
	GAME_CDECL(0x4515a0, void, void)();
	g_arenaSessionOpen = 1;
	if (host) {
		if (!GAME_CDECL(0x4547d0, int, const char *)(host))   /* net_resolveHost */
			return 0;
		strcpy(address, (const char *)0xa0d320);
	}
	if (g_dplaySessionList) {
		if ((*(u32 *)&g_connectionKind) == kind) {
			GAME_CDECL(0x452fe0, void, void)();   /* arena_leaveSession */
			g_dplaySessionList = 0;
		} else
			GAME_CDECL(0x452fe0, void, void)();
	}
	(*(u32 *)&g_connectionKind) = kind;
	g_dplaySessionCount = 0;
	GAME_VAR(int, 0xa0b420) = 0;
	(*(int *)&g_localPlayerId) = 0;
	(*(int *)&g_localPlayerData) = 0;
	if (kind > 3)
		return 0;
	int r = kind == 0 ? GAME_CDECL(open[0], int, const char *)(address) : GAME_CDECL(open[kind], int, int)(0);
	if (!r)
		return 0;
	g_dplaySessionList = 1;
	g_netQueueOnline = 1;
	return r;
}
