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

/* 0x479950 (thiscall on the scene): an effect started in the next free slot (+0x20f2da4; at most 999): a slot added
   when that is the count (+0x20f2da0, the new one marked free), the next free one after it found (none: it stays),
   then the effect set up (particle_init). Returns its slot, or -1 */
int THISCALL (particle_spawn)(u8 *s, u32 desc)
{
#define COUNT FIELD(int, s, 0x20f2da0)
#define NEXT FIELD(int, s, 0x20f2da4)
	if (NEXT >= 1000)
		return -1;
	if (NEXT == COUNT) {
		COUNT++;
		FIELD(int, s, 0x20a99c4 + COUNT * 0x12c) = 0;
	}
	int slot = NEXT;
	for (int k = slot + 1; k <= COUNT; k++)
		if (FIELD(int, s, 0x20a99c4 + k * 0x12c) == 0) {
			NEXT = k;
			break;
		}
	particle_init(s, slot, desc);
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x45e0c0 (thiscall on the scene): the actors (0x8888-byte slots from +0x1cd94b0, +0x202e8c8 of them) moved on by
   dt, the triggers run (all of it skipped while paused); dt added to the clock's fraction (+0x20fcd44), whole units over 1 moved into
   the clock (+0x20fcd40). Its callers ignore the eax it leaves */
void THISCALL (actor_updateAll)(u8 *s, float dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < FIELD(int, s, 0x202e8c8); i++)
		if (FIELD(int, s, 0x1cd94b0 + i * 0x8888) == 1)
			actor_processFrame(s, i, dt);
	script_processTriggers(s);
	long double t = (long double)dt + FIELD(float, s, 0x20fcd44);
	FIELD(float, s, 0x20fcd44) = (float)t;
	if (t > GAME_VAR(float, 0x4a9424)) {   /* 1 */
		int whole = ftol(t);
		FIELD(int, s, 0x20fcd40) += whole;
		FIELD(float, s, 0x20fcd44) = (float)(t - whole);
	}
}

/* 0x47ce50 (thiscall on the scene): a bullet fired (a4 its weapon: none with a4 +4 negative) into the next free slot
   (+0x20a99b8; at most 399; a slot added when that is the count, +0x20a99b4), the next free one after it found, then
   the bullet set up (bullet_init). Returns its slot, or -1 */
int THISCALL (bullet_spawn)(u8 *s, u32 a1, u32 a2, u32 a3, const u8 *a4, u32 a5)
{
#define COUNT FIELD(int, s, 0x20a99b4)
#define NEXT FIELD(int, s, 0x20a99b8)
	if (GAME_VAR(int, a4 + 4) < 0 || NEXT >= 400)
		return -1;
	if (NEXT == COUNT) {
		COUNT++;
		FIELD(int, s, 0x202ef38 + COUNT * 0x4e8) = 0;
	}
	int slot = NEXT;
	for (int k = slot + 1; k <= COUNT; k++)
		if (FIELD(int, s, 0x202ef38 + k * 0x4e8) == 0) {
			NEXT = k;
			break;
		}
	bullet_init(s, slot, a1, a2, a3, (u32)a4, a5);
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x490c50: an object added into the next free slot (+0x13c9b28; at most 999, else a message and -1; a slot added
   when that is the count, +0x13c9b24), set up (object_initObjectBy), then the next free one after it found. Returns
   its slot */
int THISCALL (object_addObjectBy)(u8 *s, u32 type)
{
#define COUNT FIELD(int, s, 0x13c9b24)
#define NEXT FIELD(int, s, 0x13c9b28)
	if (NEXT >= 1000) {
		sys_errorMessage((char *)0xae2eb8, (const char *)0x4c8398, NEXT + 1, 1000);
		return -1;
	}
	if (NEXT == COUNT) {
		COUNT++;
		FIELD(int, s, 0x131ae48 + COUNT * 0x2cc) = 0;
	}
	int slot = NEXT;
	object_initObjectBy(s, slot, type);
	for (int k = NEXT + 1; k <= COUNT; k++)
		if (FIELD(int, s, 0x131ae48 + k * 0x2cc) == 0) {
			NEXT = k;
			break;
		}
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x483640 (thiscall on the scene): the map's triggers (0x1c-byte records from +0xe3b038, +0xe3c938 of them): each
   armed one (+8 1) fires (+0x18) on its time (flag 1: the clock, +0x20fcd40 + +0x20fcd44, reaching +0x10) or on the
   player (flag 2: the player's actor, +0x202e8d4, within the squared radius +0x14 of its way point, +4; a NaN distance
   counts as within). Then each fired one runs its command (script_processCommandBy), is disarmed, and noted in the
   fired list (+0xe3c618, one dword each, the others 0) */
void THISCALL (script_processTriggers)(u8 *s)
{
#define COUNT FIELD(int, s, 0xe3c938)
#define TRIGGER(i) (s + 0xe3b038 + (i) * 0x1c)
	for (int i = 0; i < COUNT; i++) {
		u8 *t = TRIGGER(i);
		if (FIELD(int, t, 8) != 1)
			continue;
		u32 flags = FIELD(u32, t, 0xc);
		if (flags & 1) {
			long double now = (long double)FIELD(int, s, 0x20fcd40) + FIELD(float, s, 0x20fcd44);
			if (now >= FIELD(float, t, 0x10))
				FIELD(int, t, 0x18) = 1;
		}
		int player = FIELD(int, s, 0x202e8d4);
		if (flags & 2 && player >= 0) {
			const float *at = (const float *)(s + 0x1cd94fc + player * 0x8888);
			const float *point = FIELD(const float *, t, 4);
			long double dx = (long double)at[0] - point[0], dy = (long double)at[1] - point[1], dz = (long double)at[2] - point[2];
			if (!(dz * dz + dy * dy + dx * dx >= FIELD(float, t, 0x14)))
				FIELD(int, t, 0x18) = 1;
		}
	}
	for (int i = 0; i < COUNT; i++) {
		u8 *t = TRIGGER(i);
		if (FIELD(int, t, 0x18) == 1) {
			script_processCommandBy(s, -1, i, 0);
			FIELD(int, t, 0x18) = 0;
			FIELD(int, t, 8) = 0;
			FIELD(int, s, 0xe3c618 + i * 4) = 1;
		} else
			FIELD(int, s, 0xe3c618 + i * 4) = 0;
	}
#undef COUNT
#undef TRIGGER
}
