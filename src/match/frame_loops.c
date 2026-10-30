/* frame_loops.c: the scene's per-frame passes over its slots: each slot in use (its first dword 1) updated, unless
   the game is paused (+0x2149308 set with +0x214930c 1). The count is read again after each slot. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

static int paused(void *s) { return FIELD(int, s, 0x2149308) && FIELD(int, s, 0x214930c) == 1; }

/* 0x47d000 (thiscall on the scene): the bullets (0x4e8-byte slots from +0x202ef38, +0x20a99b4 of them). Its callers
   ignore the eax it leaves */
void THISCALL (bullet_updateAll)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < FIELD(int, s, 0x20a99b4); i++)
		if (FIELD(int, s, 0x202ef38 + i * 0x4e8) == 1)
			bullet_update(s, i, dt);
}

/* 0x479a90: the effects (0x12c-byte slots from +0x20a99c4, +0x20f2da0 of them) */
void THISCALL (match_479a90)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < FIELD(int, s, 0x20f2da0); i++)
		if (FIELD(int, s, 0x20a99c4 + i * 0x12c) == 1)
			match_476410(s, i, dt);
}

/* 0x490d40: the objects (0x2cc-byte slots from +0x131ae48, +0x13c9b24 of them) */
void THISCALL (match_490d40)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < FIELD(int, s, 0x13c9b24); i++)
		if (FIELD(int, s, 0x131ae48 + i * 0x2cc) == 1)
			actor_render(s, i, dt);
}
