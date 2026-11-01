/* frame_loops.c: the scene's per-frame passes over its slots: each slot in use (its first dword 1) updated, unless
   the game is paused (+0x2149308 set with +0x214930c 1). The count is read again after each slot. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

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
void THISCALL (stage_updateEffects)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < FIELD(int, s, 0x20f2da0); i++)
		if (FIELD(int, s, 0x20a99c4 + i * 0x12c) == 1)
			particle_update(s, i, dt);
}

/* 0x490d40: the objects (0x2cc-byte slots from +0x131ae48, +0x13c9b24 of them) */
void THISCALL (stage_updateObjects)(void *s, int dt)
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
	if (t > k_1f) {   /* 1 */
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
		sys_errorMessage((char *)IMG(0xae2eb8), (const char *)IMG(0x4c8398), NEXT + 1, 1000);
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

/* 0x49d150 (thiscall on the scene): the camera's actor (+0x234240d, none when negative): how far it moved since the
   last frame (its position +0x1eccb54 .., the last one +0x1eccb60 ..) added to the listener's position (0x4de72e,
   0x4de732, 0x4de722), and the last position brought up to date; outside the menus' text mode (+0x23423a1 0) the
   room's text kept (room_keepText); the view distance (+0x233cc50) 300. Its callers ignore the eax it leaves */
void THISCALL (sound_updateListener)(u8 *s)
{
#define ACTOR FIELD(int, s, 0x234240d)
#define NOW(k) FIELD(int, s, 0x1eccb54 + ACTOR * 0x8888 + (k) * 4)
#define LAST(k) FIELD(int, s, 0x1eccb60 + ACTOR * 0x8888 + (k) * 4)
	if (ACTOR >= 0) {
		g_titleWins += NOW(0) - LAST(0);
		g_titleLosses += NOW(1) - LAST(1);
		g_titlePoints += NOW(2) - LAST(2);
		for (int k = 0; k < 3; k++)
			LAST(k) = NOW(k);
	}
	if (!FIELD(int, s, 0x23423a1))
		room_keepText();
	FIELD(u32, s, 0x233cc50) = 0x43960000;   /* 300.0f */
#undef ACTOR
#undef NOW
#undef LAST
}

/* 0x48ec20 (thiscall on the scene): the effects' shapes looked up in the shape cache (+0x19e188c): three sets of eight
   numbered ones (+0x20f2dac, +0x20f2dcc, +0x20f2dec; named by 0x4c8170, 0x4c815c, 0x4c8144) and eight single ones
   (+0x20f2e74 ..); +0x20f2f3c cleared first. Its caller ignores the eax it leaves */
void THISCALL (effect_initTextures)(u8 *s)
{
	static const u32 sets[3][2] = { { IMG(0x4c8170), 0x20f2dac }, { IMG(0x4c815c), 0x20f2dcc }, { IMG(0x4c8144), 0x20f2dec } };
	static const u32 singles[8] = { IMG(0x4c8130), IMG(0x4c811c), IMG(0x4c8108), IMG(0x4c80f4), IMG(0x4c80e0), IMG(0x4c80c8), IMG(0x4c80b0), IMG(0x4c8098) };
	FIELD(int, s, 0x20f2f3c) = 0;
	char name[0x100];
	for (int set = 0; set < 3; set++)
		for (int k = 0; k < 8; k++) {
			sprintf(name, (const char *)RELOC(sets[set][0]), k);
			FIELD(u32, s, sets[set][1] + k * 4) = shape_getByName(s + 0x19e188c, name, 1);
		}
	for (int k = 0; k < 8; k++)
		FIELD(u32, s, 0x20f2e74 + k * 4) = shape_getByName(s + 0x19e188c, (const char *)RELOC(singles[k]), 1);
}

/* 0x483770 (thiscall on the scene): entry `entry` of trigger trig's script (the triggers' 0x1c-byte records from
   +0xe3b03c, +0 their entry list; an entry 0x14 bytes: +0xc its command count, +0x10 the 0x30-byte commands) run for
   actor a (none when negative; actors are 0x8888 bytes from +0x1cd93a8). Each command by its type: triggers on / off
   (+4) and armed (+0x14); the actor's orders, targets, speed and flags; actors spawned, reset or deactivated; the
   camera's target; events; .scp files, animations and sounds by formatted names; objects (de)activated. Its callers
   ignore the eax it leaves */
void THISCALL (script_processCommandBy)(u8 *s, int a, int trig, int entry)
{
#define TRIGGER(i, offset) FIELD(int, s, 0xe3b03c + (i) * 0x1c + (offset))
#define ACTOR(i, type, offset) FIELD(type, s, 0x1cd93a8 + (i) * 0x8888 + (offset))
	u8 *actor = a >= 0 ? s + 0x1cd93a8 + a * 0x8888 : NULL;
	u8 *e = FIELD(u8 *, s, 0xe3b03c + trig * 0x1c) + entry * 0x14;
	char name[0x100];
	for (int i = 0; i < FIELD(int, e, 0xc); i++) {
		u32 *c = (u32 *)(FIELD(u8 *, e, 0x10) + i * 0x30);
		switch (c[0]) {
		case 0: TRIGGER(c[1], 4) = 1; break;
		case 1: TRIGGER(c[1], 4) = 0; break;
		case 2: TRIGGER(c[1], 0x14) = 1; break;
		case 3: stage_triggerActionNone(s, c[1]); break;
		case 4: if (actor) FIELD(u32, actor, 0x8804) = c[1]; break;
		case 5: if (actor) FIELD(u32, actor, 0x8808) = c[1]; break;
		case 7:
			if (actor) {
				FIELD(u32, actor, 0x87f8) = c[1];
				FIELD(u32, actor, 0x87fc) = c[2];
			}
			break;
		case 8:
			if (actor && FIELD(int, actor, 0x8820) >= 0)
				TRIGGER(c[1], 0x14) = 1;
			break;
		case 9:
			if (actor && FIELD(int, actor, 0x8820) >= 0)
				stage_triggerActionNone(s, c[1]);
			break;
		case 10: if (actor) FIELD(int, actor, 0x78) = 0; break;
		case 11: if (actor) FIELD(int, actor, 0x78) = 1; break;
		case 12:
			if (actor) {
				FIELD(int, actor, 0x8804) = 0;
				FIELD(int, actor, 0x8808) = -1;
				FIELD(u32, actor, 0x50) = FIELD(u32, actor, 0x68);
				FIELD(int, actor, 0x880c) = 0;
				FIELD(int, actor, 0x8810) = FIELD(int, actor, 0x8814) = FIELD(int, actor, 0x8818) = FIELD(int, actor, 0x881c) = -1;
			}
			break;
		case 13:
			if (actor)
				FIELD(float, actor, 0x50) = f32(fmul_m(fld_m((const float *)&c[1]), (const float *)IMG(0x4a9750)));
			break;
		case 14: if (actor) FIELD(int, actor, 0x880c) = 1; break;
		case 15: actor_applySpawnRecord(s, c[1], s + 0x1cd6fb4 + c[1] * 0x5c); break;
		case 16: ACTOR(c[1], int, 0x128) = 0; break;
		case 17: actor_deactivate((Stage *)s, c[1]); break;
		case 18: if (actor) FIELD(u32, actor, 0x8810) = c[1]; break;
		case 19:
			if (actor) {
				FIELD(u32, actor, 0x8814) = c[1];
				FIELD(u32, actor, 0x8818) = c[2];
			}
			break;
		case 20:   /* the actor's weapon holding item c[1] selected */
			if (actor) {
				for (int k = 0; k < 6; k++)
					if (FIELD(u32, s, 0x1561e88 + FIELD(int, actor, 0x10c) * 0x47fd2 + k * 4) == c[1])
						actor_selectWeapon((Stage *)s, a, k);
				FIELD(int, actor, 0x46c) = 1;
			}
			break;
		case 21: if (actor) FIELD(u32, actor, 0x881c) = c[1]; break;
		case 22:
			ACTOR(c[1], int, 0x87f8) = -1;
			ACTOR(c[1], int, 0x87fc) = -1;
			break;
		case 23:
			ACTOR(c[1], u32, 0x87f8) = c[2];
			ACTOR(c[1], u32, 0x87fc) = c[3];
			break;
		case 24: camera_setTarget(s, c[1], c[2], c[3]); break;
		case 25: camera_setTarget(s, -1, -1, 0); break;
		case 26:
			if (FIELD(int, s, 0x2104fe8 + c[1] * 0x88) == 0)
				sys_fatalError((char *)IMG(0xae2eb8), (const char *)IMG(0x4c7a8c), c[1]);
			if (FIELD(int, s, 0x210850c + c[2] * 0x108) == 0)
				sys_fatalError((char *)IMG(0xae2eb8), (const char *)IMG(0x4c7a48), c[2]);
			script_pushEvent(s, c[1], c[2], c[3], c[4]);
			break;
		case 27:
			sprintf(name, (const char *)IMG(0x4c7a3c), s + 0x808, (const char *)&c[1]);
			script_runScpFile(s, name, c[9]);
			break;
		case 28:
			sprintf(name, (const char *)IMG(0x4c7a30), s + 8, s + 0x908, (const char *)&c[2]);
			object_setAnimation(s, c[1], name, c[10], c[11]);
			break;
		case 29:
			sprintf(name, (const char *)IMG(0x4c7a20), s + 0x908, (const char *)&c[1]);
			sound_playFile(name, 100);
			break;
		case 30: object_activate(s, c[1]); break;
		case 31: object_deactivate(s, c[1]); break;
		}
	}
#undef TRIGGER
#undef ACTOR
}

/* a 4 x 4 identity matrix (as float bits) */
static void identity4(u32 *m)
{
	for (int k = 0; k < 16; k++)
		m[k] = k % 5 == 0 ? 0x3f800000 : 0;
}

/* 0x48fee0 (thiscall on the scene): map object i (0x2cc bytes from +0x131ae44) set up from its type record: the
   type's name found among the object names (0x40 bytes from +0x130b440, +0x131ae40 of them) or added (at most 1000,
   else a fatal message); the next serial (+0x13c9b2c), in use, the name's index, three values (+0x40 ..), the
   animation path ("dir\sub\name" by 0x4c7a30 when the type names one, +0x4c), the position (+0x8c) and rotation
   (+0x98, a quaternion); its matrix (+0x74: translation x rotation) and inverse (+0xb4), a copy (+0xf4) and its
   inverse (+0x134), two identities (+0x174, +0x1b4), the copy times the inverse (+0x1f4) and its inverse (+0x234).
   Its shape (shape_getByName, bound) and two ranges of its element count from the shading pool (+0xf30dc8, used
   +0x13016c8; past 1000000 a fatal message), two values (+0xa8), the counters cleared, the shape's centre through
   the matrix (+0x2bc; no shape: the position), and its shading worked out unless the map has it (+0x13016cc). Its
   callers ignore the eax it leaves */
void THISCALL (object_initObjectBy)(u8 *s, int i, const u8 *type)
{
	u8 *obj = s + 0x131ae44 + i * 0x2cc;
	int idx = 0;
	for (; idx < FIELD(int, s, 0x131ae40); idx++)
		if (!strcmp((const char *)RELOC(type), (const char *)s + 0x130b440 + idx * 0x40))
			break;
	if (idx == FIELD(int, s, 0x131ae40)) {
		if (idx >= 1000)
			sys_fatalError((char *)IMG(0xae2eb8), (const char *)IMG(0x4c8364), 1000);
		idx = FIELD(int, s, 0x131ae40)++;
		strcpy((char *)s + 0x130b440 + idx * 0x40, (const char *)RELOC(type));
	}
	FIELD(int, obj, 0) = FIELD(int, s, 0x13c9b2c)++;
	FIELD(int, obj, 4) = 1;
	FIELD(int, obj, 8) = idx;
	memcpy(obj + 0xc, type + 0x40, 12);
	if (type[0x4c])
		sprintf((char *)obj + 0x18, (const char *)IMG(0x4c7a30), s + 8, s + 0x908, type + 0x4c);
	else
		obj[0x18] = 0;
	memcpy(obj + 0x58, type + 0x8c, 12);
	u32 move[16];
	identity4(move);
	for (int c = 0; c < 3; c++)
		((float *)RELOC(move))[12 + c] = f32(fld_m((const float *)(obj + 0x58) + c));
	memcpy(obj + 0x64, type + 0x98, 16);
	float turn[16];
	Mat4_fromQuat(turn, (const float *)(obj + 0x64));
	float *m = (float *)(obj + 0xf4);
	Mat4_multiply((float *)(obj + 0x74), (const float *)RELOC(move), turn);
	Mat4_invert((float *)(obj + 0xb4), (const float *)(obj + 0x74));
	Mat4_copy(m, obj + 0x74);
	Mat4_invert((float *)(obj + 0x134), m);
	identity4((u32 *)(obj + 0x174));
	identity4((u32 *)(obj + 0x1b4));
	Mat4_multiply((float *)(obj + 0x1f4), m, (const float *)(obj + 0xb4));
	Mat4_invert((float *)(obj + 0x234), (const float *)(obj + 0x1f4));
	u8 *shape = (u8 *)shape_getByName(s + 0xe3c93c, (const char *)RELOC(type), 1);
	FIELD(u8 *, obj, 0x27c) = shape;
	for (int r = 0; r < 2; r++) {
		int need = FIELD(int, s, 0x13016c8) + FIELD(int, shape, 0x18);
		if (need > 1000000)
			sys_fatalErrorN((char *)IMG(0xae2eb8), (const char *)IMG(0x4c8314), i, need, 1000000);
		FIELD(u8 *, obj, 0x280 + r * 4) = s + 0xf30dc8 + FIELD(int, s, 0x13016c8) * 4;
		FIELD(int, s, 0x13016c8) += FIELD(int, FIELD(u8 *, obj, 0x27c), 0x18);
	}
	FIELD(int, obj, 0x288) = 1;
	FIELD(u32, obj, 0x274) = FIELD(u32, type, 0xa8);
	FIELD(u32, obj, 0x278) = FIELD(u32, type, 0xac);
	memset(obj + 0x28c, 0, 7 * 4);
	if (shape) {
		const float *c = (const float *)(shape + 0x20);
		float *out = (float *)(obj + 0x2bc);
		out[0] = f32(fadd_m(fmul_m(fld_m(&m[8]), &c[2]) + fmul_m(fld_m(&m[4]), &c[1]) + fmul_m(fld_m(&m[0]), &c[0]), &m[12]));
		for (int r = 1; r < 3; r++)
			out[r] = f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &c[2]) + fmul_m(fld_m(&m[r]), &c[0]) + fmul_m(fld_m(&m[4 + r]), &c[1]), &m[12 + r]));
	} else
		memcpy(obj + 0x2bc, obj + 0x58, 12);
	FIELD(int, obj, 0x2a8) = 0;
	FIELD(int, obj, 0x2c8) = 0;
	if (FIELD(int, s, 0x13016cc) == 0)
		shape_shadeParts(FIELD(u32 *, obj, 0x280), 1, (Model *)FIELD(u8 *, obj, 0x27c), (const LightFactors *)(s + 0x9ccffc),
		                 (const float *)(obj + 0x134));
}

/* a particle of kind at p (particle_spawn's record: the kind, 0, the point, the world's colour 0xa0e7e8, zeros) */
static void spawn_at(u8 *s, u32 kind, const float *p)
{
	u32 rec[13] = { kind, 0 };
	memcpy(&rec[2], p, 12);
	memcpy(&rec[5], (const void *)IMG(0xa0e7e8), 12);
	particle_spawn(s, rec);
}

/* a falling spark (kind 9) moved by its velocity (+0x1c) over dt and dropped 2000 dt further: what it meets on the
   way (collision_rayTrace) stops it there, ends it and leaves a kind 2 particle; its orientation (+0x2c) turned by
   its age; every tenth of a second a trail particle (kind 2 one time in ten, which also ends it, else kind 0) */
static void spark(u8 *s, u8 *p, float dt)
{
	float *pos = (float *)(p + 0x10);
	const float *v = (const float *)(p + 0x1c), *k = (const float *)IMG(0x4a9554);
	float dy = f32(fmul_m(fld_m(&dt), &v[1])), dz = f32(fmul_m(fld_m(&dt), &v[2]));
	float hit[3], below[3];
	hit[0] = f32(fadd_m(fmul_m(fld_m(&dt), &v[0]), &pos[0]));
	hit[1] = f32(fadd_m(fld_m(&dy), &pos[1]));
	hit[2] = f32(fadd_m(fld_m(&dz), &pos[2]));
	below[0] = hit[0];
	below[1] = f32(fld_m(&hit[1]) - fmul_m(fld_m(&dt), k));
	below[2] = hit[2];
	if (collision_rayTrace(s, pos, below, hit)) {
		memcpy(pos, hit, 12);
		GAME_VAR(u32, p + 0x70) = GAME_VAR(u32, p + 0x6c);
		spawn_at(s, 2, hit);
	} else
		memcpy(pos, below, 12);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef_stored(pos);
	glRotatef(f32(fmul_m(fld_m((const float *)(p + 0x6c)), (const float *)IMG(0x4a94c8))), 0.0f, 1.0f, 0.0f);
	glRotatef(f32(fmul_m(fld_m((const float *)(p + 0x6c)), (const float *)IMG(0x4a94c8))), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, (float *)(p + 0x2c));
	glPopMatrix();
	long double wait = fsub_m(fld_m((const float *)(p + 0x84)), &dt);
	GAME_VAR(float, p + 0x84) = f32(wait);
	if (wait > 0)
		return;
	u32 at = g_randPos;
	u32 r = GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4) % 10;
	g_randPos = at + 1;
	spawn_at(s, r ? 0 : 2, pos);
	GAME_VAR(u32, p + 0x84) = 0x3dcccccd;
	if (!r)
		GAME_VAR(u32, p + 0x70) = GAME_VAR(u32, p + 0x6c);
}

/* 0x476410 (thiscall on the scene): particle slot's frame (0x12c bytes from +0x20a99c0). Its age (+0x74, kept at +0x6c)
   past its life (+0x70) frees it (0x4799f0); otherwise sparks move (spark), and puffs and flashes (kinds 2, 3, 25,
   26, 30 .. 38) shrink with age, (1 - age / life)^2 times their size (+0x7c); the age moves on by dt. Its caller
   ignores the eax it leaves */
void THISCALL (particle_update)(u8 *s, int slot, float dt)
{
	u8 *p = s + 0x20a99c0 + slot * 0x12c;
	float age = GAME_VAR(float, p + 0x74);
	GAME_VAR(float, p + 0x6c) = age;
	if (age > GAME_VAR(float, p + 0x70)) {
		GAME_THISFN(stage_freeProjectile, 0x4799f0, void, void *, int)(s, slot);
		return;
	}
	float t = GAME_VAR(float, p + 0x70) > 0 ? f32(fdiv_m(fld_m(&age), (const float *)(p + 0x70))) : 0.0f;
	int k = GAME_VAR(int, p + 8);
	u32 size = 0;   /* where the size constant is */
	switch (k / 5) {
	case 0:
		size = k == 2 ? IMG(0x4aa42c) : k == 3 ? IMG(0x4aa430) : 0;
		break;
	case 1:
		if (k == 9)
			spark(s, p, dt);
		break;
	case 5:
		size = k == 25 || k == 26 ? IMG(0x4a9554) : 0;
		break;
	case 6:
		size = k <= 31 ? IMG(0x4a94bc) : IMG(0x4a949c);
		break;
	case 7:
		size = k == 35 ? IMG(0x4aa430) : k == 36 ? IMG(0x4aa42c) : k <= 38 ? IMG(0x4a949c) : 0;
		break;
	}
	if (size) {
		long double u = fsub_m(fld_m((const float *)IMG(0x4a9424)), &t);
		GAME_VAR(float, p + 0x7c) = f32(fmul_m(u * u, (const float *)RELOC(size)));
	}
	GAME_VAR(float, p + 0x74) = f32(fadd_m(fld_m(&dt), (const float *)(p + 0x74)));
}

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define I(type, offset) GAME_VAR(type, it + (offset))

/* the cells, armour and shield items (kinds 0 .. 5, 10 .. 19): the actor's flag (+0x3f0) that refuses them, the
   count raised, its limit (and how far an extended one may go past it), the message; an extended one is noted as the
   last big pickup (+0x20fcd3c) */
static const struct { u8 flag; u16 count, limit; u8 add, over; u32 text; } k_supplies[16] = {
	{ 0x10, 0x130, 0x28, 1, 0, IMG(0x4c82f4) }, { 0x10, 0x130, 0x28, 40, 0, IMG(0x4c82e4) }, { 0x20, 0x134, 0x2c, 40, 0, IMG(0x4c82d4) },
	{ 0x40, 0x138, 0x30, 40, 0, IMG(0x4c82c0) }, { 0x80, 0x13c, 0x34, 15, 0, IMG(0x4c82ac) }, { 0x80, 0x13c, 0x34, 5, 0, IMG(0x4c8298) },
	{ 1, 0x128, 0x1c, 10, 0, IMG(0x4c828c) }, { 1, 0x128, 0x1c, 25, 0, IMG(0x4c8280) }, { 1, 0x128, 0x1c, 50, 0, IMG(0x4c8274) },
	{ 1, 0x128, 0x1c, 100, 0, IMG(0x4c8268) }, { 2, 0x128, 0x1c, 100, 100, IMG(0x4c8254) }, { 4, 0x12c, 0x20, 10, 0, IMG(0x4c8248) },
	{ 4, 0x12c, 0x20, 25, 0, IMG(0x4c823c) }, { 4, 0x12c, 0x20, 50, 0, IMG(0x4c8230) }, { 4, 0x12c, 0x20, 100, 0, IMG(0x4c8224) },
	{ 8, 0x12c, 0x20, 100, 100, IMG(0x4c820c) } };

/* the item's sound (its type's +0x40 or +0x44) at its position, heard from the camera */
static void item_sound(u8 *s, int sound, u8 *it)
{
	GAME_FN(sound_play3D, 0x456ed0, void, int, const float *, const float *, const float *, u32)(sound, (const float *)(s + 0x20f3970),
	                                                                                (const float *)(it + 0xc), (const float *)(s + 0x20f397c), 0x47c35000);   /* (heard to 100000) */
}

/* actor ac touching item i (of kind type, its type record t): what it gives. Supplies the actor can use are taken;
   power-ups (damage amp, cloak, booster, gravity armour: 30 s each) are taken; a warp zone (kind 24 / 34) sends the
   local player, when not already warping and not just arrived from it, to the linked item's (+4) place and heading
   without being taken; other kinds are an error message (0 .. 9: fatal) */
static void item_pickup(u8 *s, u8 *ac, u8 *it, int i, u8 *t, int type)
{
	u32 text, *timer = NULL;
	int last = 0;
	switch (type / 10) {
	case 0:
	case 1: {
		if (type < 10 && type > 5) {
			sys_fatalError((char *)IMG(0xae2eb8), (const char *)IMG(0x4c81d0), type);
			return;
		}
		int k = type < 10 ? type : 6 + type % 10;
		if (A(u8, 0x3f0) & k_supplies[k].flag)
			return;
		int limit = A(int, k_supplies[k].limit) + k_supplies[k].over;
		A(int, k_supplies[k].count) += k_supplies[k].add;
		if (A(int, k_supplies[k].count) > limit)
			A(int, k_supplies[k].count) = limit;
		text = k_supplies[k].text;
		last = k_supplies[k].over != 0;
		break;
	}
	case 2:
	case 3:
		switch (type % 10) {
		case 0: timer = &A(u32, 0x3f4); text = IMG(0x4c81c4); break;   /* DAMAGE AMP */
		case 1: timer = &A(u32, 0x3f8); text = IMG(0x4c81b4); break;   /* CLOAKING FIELD */
		case 3: timer = &A(u32, 0x3fc); text = IMG(0x4c81a4); break;   /* OVERED BOOSTER */
		case 7: timer = &A(u32, 0x400); text = IMG(0x4c8188); break;   /* GRAVITY ARMOR */
		case 4: {
			int warped = 0;
			if (A(int, 0x110) == GAME_VAR(int, s + 0x202e8d4) && !(A(float, 0x540) > 0) && A(int, 0x538) != i) {
				u8 *to = s + 0x20fadf8 + I(int, 4) * 0x28;
				memcpy(ac + 0x180, to + 0xc, 12);
				A(float, 0x18c) = f32(fmul_m((long double)GAME_VAR(int, to + 8), (const float *)IMG(0x4a9418)));
				A(u32, 0x190) = GAME_VAR(u32, to + 0x1c);
				A(int, 0x538) = I(int, 4);
				strcpy((char *)ac + 0x4f4, (const char *)IMG(0x4c8198));   /* WARP ZONE */
				A(int, 0x534) = 0;
				A(u32, 0x548) = 0x3f800000;
				A(u32, 0x540) = 0x40000000;
				A(int, 0x104) = GAME_VAR(int, s + 0x202e8d0)++;
				warped = 1;
			}
			A(int, 0x53c) = 1;
			if (warped)
				item_sound(s, GAME_VAR(int, t + 0x44), it);
			return;
		}
		default:
			return;
		}
		*timer = 0x41f00000;   /* 30 */
		last = 1;
		break;
	default:
		GAME_FN(sys_errorMessage, 0x46c5f0, void, char *, const char *, int)((char *)IMG(0xae2eb8), (const char *)IMG(0x4c81d0), type);
		return;
	}
	strcpy((char *)ac + 0x4f4, (const char *)RELOC(text));
	A(int, 0x534) = 0;
	if (last)
		GAME_VAR(int, s + 0x20fcd3c) = i;
	item_sound(s, GAME_VAR(int, t + 0x44), it);
	I(int, 0x20) = 1;
	I(int, 0x24) = 0;
}

/* 0x48ed90 (thiscall on the scene): the items' frame. Live actors' touch flags (+0x53c) cleared; every item (0x28
   bytes from +0x20fadf8, +0x20fcd38 of them; its kind +0 into the 0x90-byte types at +0x20f3ae0, state +0x20, timer
   +0x24, position +0xc): a taken one comes back after its type's time (+0x48, with its sound +0x40); a present one
   spins (+0x1c, 600 a second, but kind 0x22) and the first live actor within 1.5 of its radius (+0x3e8) on every
   axis touches it (item_pickup). An actor touching no warp zone forgets the last one (+0x538 -1). Its callers ignore
   the eax it leaves */
void THISCALL (item_update)(u8 *s, float dt)
{
	for (int k = 0; k < GAME_VAR(int, s + 0x202e8c8); k++) {
		u8 *ac = s + 0x1cd93a8 + k * 0x8888;
		if (A(int, 0x14c) == 1)
			A(int, 0x53c) = 0;
	}
	for (int i = 0; i < GAME_VAR(int, s + 0x20fcd38); i++) {
		u8 *it = s + 0x20fadf8 + i * 0x28;
		int type = I(int, 0);
		if (type < 0)
			continue;
		u8 *t = s + 0x20f3ae0 + type * 0x90;
		if (I(int, 0x20) == 1) {
			if (I(float, 0x24) > GAME_VAR(float, t + 0x48)) {
				item_sound(s, GAME_VAR(int, t + 0x40), it);
				I(int, 0x20) = 0;
				I(int, 0x24) = 0;
			}
		} else if (I(int, 0x20) == 0) {
			if (type != 0x22)
				I(float, 0x1c) = f32(fadd_m(fmul_m(fld_m(&dt), (const float *)IMG(0x4a94ac)), (const float *)(it + 0x1c)));
			int n = GAME_VAR(int, s + 0x202e8c8);
			for (int k = 0; k < n; k++) {
				u8 *ac = s + 0x1cd93a8 + k * 0x8888;
				if (A(int, 0x14c) != 1)
					continue;
				float reach = 0;
				int near = 1;
				for (int a = 0; a < 3 && near; a++) {
					long double d = fsub_m(fld_m((const float *)(ac + 0x154) + a), (const float *)(it + 0xc) + a);
					if (!(d >= 0))
						d = -d;
					if (a == 0)
						reach = f32(fmul_m(fld_m((const float *)(ac + 0x3e8)), (const float *)IMG(0x4a974c)));
					near = !(d >= reach);
				}
				if (near) {
					item_pickup(s, ac, it, i, t, type);
					break;
				}
			}
		}
		I(float, 0x24) = f32(fadd_m(fld_m(&dt), (const float *)(it + 0x24)));
	}
	for (int k = 0; k < GAME_VAR(int, s + 0x202e8c8); k++) {
		u8 *ac = s + 0x1cd93a8 + k * 0x8888;
		if (A(int, 0x53c) == 0)
			A(int, 0x538) = -1;
	}
}
#undef A
#undef I

#define P(type, offset) GAME_VAR(type, p + (offset))
#define K(address) ((const float *)RELOC(address))

/* the next of the game's random numbers (its table 0xa106f8 by the counter 0xa1efb8) below n */
static u32 table_rand_below(u32 n)
{
	u32 at = g_randPos;
	u32 r = GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4) % n;
	g_randPos = at + 1;
	return r;
}

/* the particle's direction (+0x10, from 0xa0e7a8 through its matrix +0x2c) */
static void particle_heading(u8 *p)
{
	const float *m = (const float *)(p + 0x2c), *v = (const float *)IMG(0xa0e7a8);
	for (int r = 0; r < 3; r++)
		P(float, 0x10 + r * 4) = f32(fadd_m(fmul_m(fld_m(&v[2]), &m[8 + r]) + fmul_m(fld_m(&v[1]), &m[4 + r]) + fmul_m(fld_m(&v[0]), &m[r]),
		                                    &m[12 + r]));
}

/* a matrix from the particle's own (+0x28) turned by a random whole degree about z (its +0x2c), and the direction */
static void particle_spin(u8 *p)
{
	glPushMatrix();
	glLoadIdentity();
	glLoadMatrixf(P(const float *, 0x28));
	glRotatef((float)table_rand_below(360), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, (float *)(p + 0x2c));
	glPopMatrix();
	particle_heading(p);
}

/* the particle's +0x2c the inverse of a look from its position (+0x10) to its target (+0x1c), stretched by their
   distance (z) and xy (1, or by size +0x80) */
static void particle_aim(u8 *p, int by_size)
{
	float d[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m((const float *)(p + 0x1c) + k), (const float *)(p + 0x10) + k));
	float len = f32(Vec3_normalize(d));
	glPushMatrix();
	glLoadIdentity();
	float xy = by_size ? f32(fld_m(K(0x4a9424)) / fadd_m(fmul_m(fld_m((const float *)(p + 0x80)), K(0x4a9504)), K(0x4a9424))) : 1.0f;
	float z = f32(fld_m(K(0x4a9424)) / fmul_m(fld_m(&len), K(0x4a9504)));
	glScalef_bits(*(u32 *)&xy, *(u32 *)&xy, *(u32 *)&z);
	gluLookAt(P(float, 0x10), P(float, 0x14), P(float, 0x18), P(float, 0x1c), P(float, 0x20), P(float, 0x24), 0.0, 1.0, 0.0);
	float m[16];
	glGetFloatv(0xba6, m);
	Mat4_invert((float *)(p + 0x2c), m);
	glPopMatrix();
}

/* a beam (kinds 25 / 26, its colour): its matrix looking back from the target (+0x1c) away from the position, and
   unless it is a remote one (+0xc 1) small particles (kind 0, of its size) along it, one per 200 units */
static void particle_beam(u8 *s, u8 *p, u32 colour)
{
	P(int, 0x70) = 0;
	P(u32, 0x78) = colour;
	glPushMatrix();
	glLoadIdentity();
	const float *at = (const float *)(p + 0x1c), *from = (const float *)(p + 0x10);
	gluLookAt(at[0], at[1], at[2], (double)(fld_m(&at[0]) * 2 - fld_m(&from[0])), (double)(fld_m(&at[1]) * 2 - fld_m(&from[1])),
	          (double)(fld_m(&at[2]) * 2 - fld_m(&from[2])), 0.0, 1.0, 0.0);
	float m[16];
	glGetFloatv(0xba6, m);
	Mat4_invert((float *)(p + 0x2c), m);
	glPopMatrix();
	if (P(int, 0xc) == 1)
		return;
	float d[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(&from[k]), &at[k]));
	long double len = Vec3_normalize(d);
	float step = f32(len);
	if (!(len > 0))
		return;
	int n = ftol(fmul_m(fld_m(&step), K(0x4aa428)));
	u32 rec[13];
	if (n <= 1) {
		memset(rec, 0, sizeof rec);
		memcpy(&rec[2], at, 12);
		memcpy(&rec[5], (const void *)IMG(0xa0e7b8), 12);
		float size = f32(fld_m((const float *)(p + 0x80)));
		memcpy(&rec[11], &size, 4);
		particle_spawn(s, rec);
		return;
	}
	step = f32(fld_m(&step) / (long double)n);
	for (int k = 0; k < n; k++) {
		long double sx = fmul_m(fld_m(&d[0]), &step);
		float sy = f32(fmul_m(fld_m(&d[1]), &step)), sz = f32(fmul_m(fld_m(&d[2]), &step));
		float kf = f32((long double)k);
		float y = f32(fmul_m(fld_m(&sy), &kf)), z = f32(fmul_m(fld_m(&sz), &kf));
		float pos[3] = { f32(fadd_m(fmul_m(sx, &kf), &at[0])), f32(fadd_m(fld_m(&y), &at[1])), f32(fadd_m(fld_m(&z), &at[2])) };
		rec[0] = rec[1] = 0;
		memcpy(&rec[2], pos, 12);
		memcpy(&rec[5], (const void *)IMG(0xa0e7b8), 12);
		rec[8] = rec[9] = rec[10] = 0;
		float size = f32(fld_m((const float *)(p + 0x80)));
		memcpy(&rec[11], &size, 4);
		rec[12] = 0;
		particle_spawn(s, rec);
	}
}

/* a trail particle (kinds 40 .. 49): its three points (from the descriptor's +0x24), and its two ends' widths and
   lengths (+0xb4 ..) from the descriptor's +0x28 sizes, either as size x 0.005 + 0.5 or (by d, the particle's size
   plus a margin) as (size / d + 1) / 2; its colours the shared one (0xa1f23c) */
static void particle_trail(u8 *p, const u8 *desc, u32 margin)
{
	P(u32, 0x70) = 0x40000000;   /* 2 s */
	memcpy(p + 0x84, GAME_VAR(const u8 *, desc + 0x24), 12);
	memcpy(p + 0x90, GAME_VAR(const u8 *, desc + 0x24) + 0xc, 12);
	memcpy(p + 0x9c, GAME_VAR(const u8 *, desc + 0x24) + 0x18, 12);
	const float *q = GAME_VAR(const float *, desc + 0x28);
	static const u8 from[5] = { 0, 2, 3, 4, 5 }, to[5] = { 0xb4, 0xbc, 0xc0, 0xc4, 0xc8 };
	if (!margin) {
		for (int k = 0; k < 5; k++) {
			P(float, to[k]) = f32(fadd_m(fmul_m(fld_m(&q[from[k]]), K(0x4aa428)), K(0x4a942c)));
			if (k == 0)
				P(u32, 0xb8) = 0x3f000000;
		}
	} else {
		long double d = fadd_m(fld_m((const float *)(p + 0x80)), K(margin));
		for (int k = 0; k < 5; k++) {
			P(float, to[k]) = f32(fmul_m(fadd_m(fld_m(&q[from[k]]) / d, K(0x4a9424)), K(0x4a942c)));
			if (k == 0)
				P(u32, 0xb8) = 0x3f000000;
		}
	}
	P(u32, 0xd4) = P(u32, 0xd8) = P(u32, 0xdc) = g_white;
}

/* 0x475070 (thiscall on the scene): particle slot (0x12c bytes from +0x20a99c0) set up from its descriptor: a
   serial id, in use. A descriptor flagged +0x30 is a kind 50 effect (its 0x48 bytes from +0x34). Otherwise the
   kind (+0), owner, position, target, a matrix to copy, the size (+0x2c); then by kind its life (+0x70) and: 2 / 3
   a sound at the position; 4 its colour from +0x20; 9 a fade; 10 / 11 / 18 a random spin; 12 .. 17 the heading
   through its matrix; 20 / 21 / 24 aimed at the target; 25 / 26 beams; 40 .. 49 trails */
void THISCALL (particle_init)(u8 *s, int slot, const u8 *desc)
{
	u8 *p = s + 0x20a99c0 + slot * 0x12c;
	P(int, 0) = GAME_VAR(int, s + 0x20f2da8)++;
	P(int, 4) = 1;
	if (GAME_VAR(int, desc + 0x30) == 1) {
		P(int, 8) = 0x32;
		memcpy(p + 0xe4, desc + 0x34, 0x18);
		memcpy(p + 0xfc, desc + 0x4c, 12);
		memcpy(p + 0x108, desc + 0x58, 12);
		memcpy(p + 0x114, desc + 0x64, 12);
		memcpy(p + 0x120, desc + 0x70, 12);
		P(u32, 0x70) = 0x3c23d70a;   /* 0.01 */
		P(int, 0x6c) = P(int, 0x74) = 0;
		return;
	}
	P(u32, 8) = GAME_VAR(u32, desc);
	P(u32, 0xc) = GAME_VAR(u32, desc + 4);
	memcpy(p + 0x10, desc + 8, 12);
	memcpy(p + 0x1c, desc + 0x14, 12);
	P(u32, 0x28) = GAME_VAR(u32, desc + 0x20);
	if (P(u32, 0x28))
		Mat4_copy(p + 0x2c, P(const void *, 0x28));
	P(int, 0x6c) = 0;
	P(u32, 0x70) = 0x3f800000;
	P(int, 0x74) = 0;
	P(u32, 0x78) = g_white;
	P(int, 0x7c) = 0;
	P(u32, 0x80) = GAME_VAR(u32, desc + 0x2c);
	int kind = P(int, 8);
	switch (kind) {
	case 0: case 1: case 8: P(u32, 0x70) = 0x3f000000; break;   /* 0.5 s */
	case 2:
	case 3:
		GAME_FN(sound_play3D, 0x456ed0, void, int, const float *, const float *, const float *, u32)(kind == 2 ? 0x2a : 0x28, (const float *)(s + 0x20f3970),
		                                                                                (const float *)(p + 0x10), (const float *)(s + 0x20f397c),
		                                                                                kind == 2 ? 0x47435000 : 0x47c35000);
		break;
	case 4:
		P(int, 0x70) = 0;
		P(u32, 0x78) = P(u32, 0x20);
		break;
	case 5: case 6: case 7: P(int, 0x70) = 0; break;
	case 9:
		P(u32, 0x70) = 0x40000000;
		P(u32, 0x84) = 0x3dcccccd;
		break;
	case 10: case 11: case 18:
		P(u32, 0x70) = 0x3c23d70a;
		particle_spin(p);
		break;
	case 12: case 13: case 17:
		P(u32, 0x70) = 0x3c23d70a;
		particle_heading(p);
		break;
	case 14: case 15: case 16:
		P(u32, 0x70) = 0x3f000000;
		particle_heading(p);
		break;
	case 20: case 21:
		P(u32, 0x70) = 0x3c23d70a;
		particle_aim(p, 0);
		break;
	case 22: P(u32, 0x70) = 0x3c23d70a; break;
	case 24:
		P(u32, 0x70) = 0x3f000000;
		particle_aim(p, 1);
		break;
	case 25: particle_beam(s, p, 0xffc4c4ff); break;   /* bytes ff c4 c4 ff */
	case 26: particle_beam(s, p, 0xffffc4c4); break;   /* bytes c4 c4 ff ff */
	case 30: case 31: case 32: case 33: case 34: case 35: case 36: case 37: case 38:
		P(u32, 0x70) = 0x3f800000;
		break;
	case 40: case 41: case 49: particle_trail(p, desc, 0); break;
	case 42: case 43: case 44: case 46: case 47: case 48: particle_trail(p, desc, IMG(0x4a93f0)); break;
	case 45: particle_trail(p, desc, IMG(0x4aa424)); break;
	}
}
#undef P
#undef K
