/* frees.c: buffers given back: the arena screen's allocations and the loaded sound buffers. Each returns what the
   original leaves in eax: the last free's result. */
#include "../game.h"

/* 0x4519b0: the arena's 19 buffers freed (in the original's order) and their pointers cleared */
u32 (arena_freeBuffers)(void)
{
	static const u32 buffers[19] = { ADDR(g_roomPacket), ADDR(g_netInfoPacket), IMG(0xa0b318), ADDR(g_netKindWord), ADDR(g_netLobbyMessage), ADDR(g_netSendName), ADDR(g_accountPacket), ADDR(g_arenaPacket),
	                                 ADDR(g_arenaInfoPacket), ADDR(g_roomRecordPacket), ADDR(g_netRequestWord), ADDR(g_netRankingBuffer), ADDR(g_netSendBuffer), ADDR(g_netSelectionPacket), ADDR(g_netAccountBuffer), ADDR(g_netPlayerRecordPacket),
	                                 IMG(0xa052e4), ADDR(g_netLeaveBuffer), ADDR(g_netJoinMessage) };
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
	for (u32 p = IMG(0xa0e02c); p < ADDR(g_soundBaseVolume); p += 4) {
		r = GAME_VAR(u32, p);
		if (r) {
			r = mem_free((void *)RELOC(r));
			GAME_VAR(u32, p) = 0;
		}
	}
	return r;
}
