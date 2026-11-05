/* frees.c: buffers given back: the network's send buffers and the loaded sound buffers. Each returns what the
   original leaves in eax: the last free's result. */
#include "../game.h"

/* 0x4519b0: the network's 19 send buffers (allocated when connecting) freed, in the original's order, and their
   pointers cleared */
u32 (net_freeBuffers)(void)
{
	static const u32 buffers[19] = { ADDR(g_roomPacket), ADDR(g_netInfoPacket), ADDR(g_lobbyLeavePacket), ADDR(g_netKindBuffer), ADDR(g_netLobbyMessage), ADDR(g_netSendName), ADDR(g_accountPacket), ADDR(g_arenaPacket),
	                                 ADDR(g_arenaInfoPacket), ADDR(g_roomRecordPacket), ADDR(g_netRequestBuffer), ADDR(g_netRankingBuffer), ADDR(g_netSendBuffer), ADDR(g_netSelectionPacket), ADDR(g_netAccountBuffer), ADDR(g_netPlayerRecordPacket),
	                                 ADDR(g_netByteBuffer), ADDR(g_netLeaveBuffer), ADDR(g_netAccountRequest) };
	u32 r = 0;
	for (int i = 0; i < 19; i++) {
		r = GAME_VAR(u32, buffers[i]);
		if (r) {
			r = crt_free((void *)RELOC(r));
			GAME_VAR(u32, buffers[i]) = 0;
		}
	}
	return r;
}

/* 0x456cd0: with sound on (0xa0e80c), every loaded sound buffer (0xa0e02c .. 0xa0e66c) deleted */
u32 (sound_freeAll)(void)
{
	if (!g_soundOn)
		return 0;
	u32 r = 0;
	for (u32 p = OBJ(g_soundTable); p < OBJ(g_soundTable) + 400 * 4; p += 4) {   /* (400 entries) */
		r = GAME_VAR(u32, p);
		if (r) {
			r = mem_free((void *)RELOC(r));
			GAME_VAR(u32, p) = 0;
		}
	}
	return r;
}
