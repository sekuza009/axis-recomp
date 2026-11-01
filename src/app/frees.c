/* frees.c: buffers given back: the arena screen's allocations and the loaded sound buffers. Each returns what the
   original leaves in eax: the last free's result. */
#include "../game.h"

/* 0x4519b0: the arena's 19 buffers freed (in the original's order) and their pointers cleared */
u32 (arena_freeBuffers)(void)
{
	static const u32 buffers[19] = { IMG(0xa0b310), IMG(0xa0b314), IMG(0xa0b318), IMG(0xa0b30c), IMG(0xa0b31c), IMG(0xa0b304), IMG(0xa0b320), IMG(0xa0b328),
	                                 IMG(0xa0b32c), IMG(0xa0b330), IMG(0xa0b334), IMG(0xa0b324), IMG(0xa0b308), IMG(0xa0b340), IMG(0xa0b344), IMG(0xa0b338),
	                                 IMG(0xa052e4), IMG(0xa0b33c), IMG(0xa055e0) };
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
	for (u32 p = IMG(0xa0e02c); p < IMG(0xa0e66c); p += 4) {
		r = GAME_VAR(u32, p);
		if (r) {
			r = mem_free((void *)RELOC(r));
			GAME_VAR(u32, p) = 0;
		}
	}
	return r;
}
