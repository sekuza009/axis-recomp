/* weapons.c: switching an actor's weapon. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* the next usable weapon slot of actor i, going step slots round the six (1 forward, 5 = one back): a slot is
   usable when its player record holds a weapon there, of a known type, and the actor has at least that weapon's
   ammunition cost left */
static void weapon_cycle(Stage *stage, int i, int step)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	u8 *player = (u8 *)stage + 0x1561b68 + FIELD(int, actor, 0x10c) * 0x47fd2;
	int slot = (FIELD(int, actor, 0x140) + step) % 6;
	for (int k = 0; k < 6; k++, slot = (slot + step) % 6) {
		int weapon = FIELD(int, player, 0x320 + slot * 4);
		if (weapon < 0)
			continue;
		int type = FIELD(int, stage, 0x14d4874 + weapon * 0x2e18);
		if (FIELD(int, actor, 0x130 + type * 4) < FIELD(int, stage, 0x14d4878 + weapon * 0x2e18) || type < 0)
			continue;
		actor_selectWeapon(stage, i, slot);
		return;
	}
}

/* 0x45e9e0, 0x45e910: actor i's next and previous weapon */
void THISCALL (actor_45e9e0)(Stage *stage, int i) { weapon_cycle(stage, i, 1); }
void THISCALL (actor_45e910)(Stage *stage, int i) { weapon_cycle(stage, i, 5); }

/* 0x45e810: actor i's weapon slot changed to slot (slots 0 .. 3 also remembered as the last ordinary one), with the
   weapon its player record holds there */
void THISCALL (FUN_0045e810)(Stage *stage, int i, int slot)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	int player = FIELD(int, actor, 0x10c);
	if (FIELD(int, actor, 0x140) != slot) {
		FIELD(int, actor, 0x140) = slot;
		if (slot < 4)
			FIELD(int, actor, 0x144) = slot;
		FIELD(int, actor, 0x148) = FIELD(int, stage, 0x1561b68 + player * 0x47fd2 + 0x320 + slot * 4);
	}
}

/* 0x45e880: actor i starts switching to weapon slot (2 seconds) unless it is the slot in use, when its player record
   holds a weapon there of a known type */
void THISCALL (actor_selectWeapon)(Stage *stage, int i, int slot)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	if (FIELD(int, actor, 0x140) == slot)
		return;
	int weapon = FIELD(int, stage, 0x1561b68 + FIELD(int, actor, 0x10c) * 0x47fd2 + 0x320 + slot * 4);
	if (weapon > -1 && FIELD(int, stage, 0x14d4874 + weapon * 0x2e18) > -1) {
		FIELD(int, actor, 0x48c) = 1;
		FIELD(int, actor, 0x498) = slot;
		FIELD(u32, actor, 0x494) = 0x40000000;   /* 2.0 */
	}
}

/* 0x45edb0: actor i (when +0x14c is 1) picks slot 0 four times in five, else slot 4, from the game's random table
   (0xa106f8, 4096 values, position 0xa1efb8), and its aim is set back to its own point */
void THISCALL (actor_45edb0)(Stage *stage, int i)
{
	u8 *actor = (u8 *)stage + 0x1cd93a8 + i * 0x8888;
	if (FIELD(int, actor, 0x14c) != 1)
		return;
	u32 r = GAME_VAR(u32, 0xa1efb8);
	u32 v = GAME_VAR(u32, 0xa106f8 + (r & 0xfff) * 4);
	GAME_VAR(u32, 0xa1efb8) = r + 1;
	actor_selectWeapon(stage, i, v % 100 < 80 ? 0 : 4);
	FIELD(int, actor, 0x8830) = 0;
	FIELD(int, actor, 0x8834) = 0;
	FIELD(int, actor, 0x8828) = FIELD(int, actor, 0x90);
	FIELD(int, actor, 0x882c) = FIELD(int, actor, 0x94);
}

/* 0x460000 (thiscall on the scene): actor target (0x8888-byte actors from +0x1cd93a8) hit by actor attacker, when
   it is in play (+0x14c 1) and not invulnerable (+0x880c 1). The damage: for weapon kinds 0 .. 9 scaled by the
   attacker's player's level in the kind's group (the 0x4c-byte levels at 0x9f9068: +0, 4, 8, 12; (level + 100) x
   damage x 0x4a9420, rounded by 0x4a942c; no player: -1), doubled by the attacker's flag 0x100 (+0x3f0) and halved
   by the target's 0x800. Unless both are on the same team (+0x118) and not the same actor, it comes off (mode 0)
   the armour (+0x12c), what is left off the energy (+0x128), or (mode 1) the shield, the energy losing 0x4a9758 of
   it, and once the shield is gone the rest; neither below 0; the hit recorded (+0x4bc mode, +0x4c0 attacker, +0x4c4
   value, +0x8850 1). The hit flash (+0x8854) 0.5 either way, and a sound when the target is the local player. Its
   callers ignore the eax it leaves */
void THISCALL (bullet_playImpactSound)(u8 *scene, int attacker, int target, int mode, int damage, int kind, u32 value)
{
#define ACTOR(i) (scene + 0x1cd93a8 + (i) * 0x8888)
	static const u8 group[10] = { 0, 0, 4, 4, 4, 8, 8, 4, 12, 12 };
	u8 *t = ACTOR(target), *a = ACTOR(attacker);
	if (FIELD(int, t, 0x14c) != 1 || FIELD(int, t, 0x880c) == 1)
		return;
	int player = FIELD(int, a, 0x108) == 1 ? FIELD(int, a, 0x114) : -1;
	if ((unsigned)kind <= 9) {
		int level = GAME_VAR(int, 0x9f9068 + player * 0x4c + group[kind]) + 100;
		damage = ftol(fadd_m(fmul_m((long double)level * damage, (const float *)0x4a9420), (const float *)0x4a942c));
	}
	if (FIELD(u32, a, 0x3f0) & 0x100)
		damage *= 2;
	if (FIELD(u32, t, 0x3f0) & 0x800)
		damage /= 2;
	if (FIELD(int, t, 0x118) != FIELD(int, a, 0x118) || target == attacker) {
		if (mode == 0) {
			if ((FIELD(int, t, 0x12c) -= damage) < 0) {
				FIELD(int, t, 0x128) += FIELD(int, t, 0x12c);
				FIELD(int, t, 0x12c) = 0;
			}
		} else if (mode == 1) {
			int shield = FIELD(int, t, 0x12c);
			if (shield >= damage) {
				FIELD(int, t, 0x12c) = shield - damage;
				FIELD(int, t, 0x128) -= ftol(fadd_m(fmul_m((long double)damage, (const float *)0x4a9758), (const float *)0x4a942c));
			} else {
				int lost = ftol(fadd_m(fmul_m((long double)shield, (const float *)0x4a9758), (const float *)0x4a942c));
				FIELD(int, t, 0x128) += shield - lost - damage;
				FIELD(int, t, 0x12c) = 0;
			}
		}
		if (FIELD(int, t, 0x128) < 0)
			FIELD(int, t, 0x128) = 0;
		if (FIELD(int, t, 0x12c) < 0)
			FIELD(int, t, 0x12c) = 0;
		FIELD(int, t, 0x4bc) = mode;
		FIELD(int, t, 0x4c0) = attacker;
		FIELD(u32, t, 0x4c4) = value;
		FIELD(int, t, 0x8850) = 1;
	}
	FIELD(u32, t, 0x8854) = 0x3f000000;   /* 0.5 */
	if (target == FIELD(int, scene, 0x202e8d4))
		sound_playVolume(0xc, 100);
#undef ACTOR
}

/* the next value of the game's table of rand() values (0xa106f8, 4096 of them; the position 0xa1efb8 moves on) */
static u32 table_rand(void)
{
	u32 at = GAME_VAR(u32, 0xa1efb8);
	GAME_VAR(u32, 0xa1efb8) = at + 1;
	return GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4);
}

/* is |p - from| within range (as fcom has it: a NaN is) */
static int within(const float *p, const float *from, const float *range)
{
	long double d = fsub_m(fld_m(p), from);
	if (!(d >= *(const float *)0x4a93e8))
		d = -d;
	return !(d > *range);
}

/* 0x460270 (thiscall on the scene): a new target for actor p (0x8888-byte actors from +0x1cd93a8): the points (0x14
   bytes) of every point list (0x1c-byte records from +0xe3b038: a count, the points; +0xe3c938 lists) but the one
   it follows (+0x8870) within its range (+0x8848) on each axis of it (+0x154) are candidates. The first five are
   kept, marked whether the line to them is clear (collision_rayTrace); after that a clear one takes the place of a
   random one that is not clear (two tries), and that list is left. One of the candidates picked at random: the
   target (+0x87f8 list, +0x87fc point, +0x8800 a random side), +0x8870 none, the range 1500. With none the range
   grows (x 0x4a974c). Its caller ignores the eax it leaves */
void THISCALL (actor_checkLineOfSight)(u8 *scene, int p)
{
	u8 *a = scene + 0x1cd93a8 + p * 0x8888;
	const float *from = (const float *)(a + 0x154), *range = (const float *)(a + 0x8848);
	int lists[5], points[5], clear[5], n = 0;
	u8 out[12];
	for (int i = 0; i < FIELD(int, scene, 0xe3c938); i++) {
		if (i == FIELD(int, a, 0x8870))
			continue;
		u8 *list = scene + 0xe3b038 + i * 0x1c;
		for (int j = 0; j < FIELD(int, list, 0); j++) {
			const float *pt = (const float *)(FIELD(u8 *, list, 4) + j * 0x14);
			if (!within(&pt[0], &from[0], range) || !within(&pt[1], &from[1], range) || !within(&pt[2], &from[2], range))
				continue;
			if (n < 5) {
				points[n] = j;
				lists[n] = i;
				clear[n] = collision_rayTrace(scene, from, pt, out) == 0;
				n++;
				continue;
			}
			if (collision_rayTrace(scene, from, pt, out) != 0)
				continue;
			int k = table_rand() % n;
			if (clear[k] && clear[k = table_rand() % n])
				continue;
			lists[k] = i;
			points[k] = j;
			clear[k] = 1;
			break;
		}
	}
	if (n > 0) {
		int k = table_rand() % n;
		FIELD(int, a, 0x87f8) = lists[k];
		FIELD(int, a, 0x87fc) = points[k];
		FIELD(int, a, 0x8800) = table_rand() & 1;
		FIELD(int, a, 0x8870) = -1;
		FIELD(u32, a, 0x8848) = 0x44bb8000;   /* 1500.0 */
	} else
		FIELD(float, a, 0x8848) = f32(fmul_m(fld_m(range), (const float *)0x4a974c));
}

#define K(address) ((const float *)(address))
#define B(type, offset) GAME_VAR(type, b + (offset))

static long double root(long double x) { __asm__("fsqrt" : "+t"(x)); return x; }

/* the next of the game's random numbers (its table 0xa106f8 by the counter 0xa1efb8) below n */
static u32 next_rand(u32 n)
{
	u32 at = GAME_VAR(u32, 0xa1efb8);
	u32 r = GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4) % n;
	GAME_VAR(u32, 0xa1efb8) = at + 1;
	return r;
}

/* 0x479b40 (thiscall on the scene): bullet slot (0x4e8 bytes from +0x202ef34) fired by owner from the shot (+0 a
   target given, +4 the weapon: its record 0x2e18 bytes from +0x14d1ab4, +8 the origin, +0x14 the target's record,
   +0x18 the direction or the target, +0x24 kept at +0x10). Its id (or the next serial, +0x20a99bc). Aimed shots
   spread with the weapon's +0x2dec less the owner's steadiness (+0x24) and are renormalised; mode 3 (+0x2dfc) fires
   into a random cone about the direction (through gluLookAt's inverse); the first step (speed +0x2de4) is traced
   (collision_rayTrace; the hit record +0x6c) and the part of a step used (+0x74) kept from 0 to 10. Then its
   velocity (+0x2de8 times the direction, or the step), colour, the owner's own tracer end (+0x2e0c), and, unless
   quiet, the muzzle flash (particle kind +0x2dfc + 10) and the firing sound (+0x2e00: at full volume for the local
   player +0x202e8d4, else placed). Its callers ignore the eax it leaves */
void THISCALL (bullet_init)(u8 *s, int slot, int id, int owner, int a4, const u8 *shot, int quiet)
{
	u8 *b = s + 0x202ef34 + slot * 0x4e8;
	u8 *w = s + 0x14d1ab4 + GAME_VAR(int, shot + 4) * 0x2e18;
	const float *o = (const float *)(shot + 8), *aim = (const float *)(shot + 0x18);
	if (id >= 0)
		B(int, 0) = id;
	else
		B(int, 0) = GAME_VAR(int, s + 0x20a99bc)++;
	B(int, 4) = 1;
	B(int, 8) = GAME_VAR(int, shot + 4);
	B(int, 0xc) = owner;
	B(u32, 0x10) = GAME_VAR(u32, shot + 0x24);
	memcpy(b + 0x54, o, 12);
	float dir[3];
	const float *w2de8 = (const float *)(w + 0x2de8);
	if (GAME_VAR(int, shot) == 0) {
		memcpy(dir, aim, 12);
		if (GAME_VAR(float, w + 0x2dec) > 0) {
			long double spread = fmul_m(fld_m((const float *)(w + 0x2dec)) -
			                            fmul_m((long double)GAME_VAR(int, s + 0x1cd93cc + owner * 0x8888), K(0x4a9418)), K(0x4aa448));
			if (!(spread >= 0))
				spread = 0;
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fadd_m((long double)((int)next_rand(100) - 50) * spread, &dir[k]));
			Vec3_normalize(dir);
		}
		if (GAME_VAR(int, w + 0x2dfc) == 3) {
			glPushMatrix();
			glLoadIdentity();
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fadd_m(fld_m(&dir[k]), &o[k]));
			gluLookAt(o[0], o[1], o[2], dir[0], dir[1], dir[2], 0.0, 1.0, 0.0);
			float m[16], inv[16];
			glGetFloatv(0xba6, m);
			Mat4_invert(inv, m);
			glPopMatrix();
			u32 cone[3] = { 0, 0x3e10d068, 0x3f7d6d5d };   /* 0, 0.141, 0.990: 8.1 degrees off the axis */
			float *v = (float *)cone;
			Vec3_rotateAxis(v, 0, (int)next_rand(3600));
			for (int r = 0; r < 3; r++)
				dir[r] = f32(fmul_m(fld_m(&v[2]), &inv[8 + r]) + fmul_m(fld_m(&v[1]), &inv[4 + r]) + fmul_m(fld_m(&inv[r]), &v[0]));
		}
		const float *speed = (const float *)(w + 0x2de4), *from = (const float *)(b + 0x54);
		float *end = (float *)(b + 0x60);
		float sx = f32(fmul_m(fld_m(speed), &dir[0])), sy = f32(fmul_m(fld_m(speed), &dir[1]));
		long double sz = fmul_m(fld_m(speed), &dir[2]);
		end[0] = f32(fadd_m(fld_m(&sx), &from[0]));
		end[1] = f32(fadd_m(fld_m(&sy), &from[1]));
		end[2] = f32(fadd_m(sz, &from[2]));
		float hit[3];
		B(int, 0x6c) = collision_rayTrace(s, from, end, hit);
		if (B(int, 0x6c)) {
			memcpy(end, hit, 12);
			if (*w2de8 > 0) {
				float dx = f32(fsub_m(fld_m(&hit[0]), &from[0]));
				long double dy = fsub_m(fld_m(&hit[1]), &from[1]), dz = fsub_m(fld_m(&hit[2]), &from[2]);
				B(float, 0x74) = f32(fdiv_m(root((fmul_m(fld_m(&dx), &dx) + dz * dz) + dy * dy), w2de8));
			} else
				B(int, 0x74) = 0;
		} else if (*w2de8 > 0)
			B(float, 0x74) = f32(fdiv_m(fld_m(speed), w2de8));
		else
			B(int, 0x74) = 0;
		if (!(B(float, 0x74) >= 0) || B(float, 0x74) > *K(0x4a9418))
			B(int, 0x74) = 0;
	} else {
		for (int k = 0; k < 3; k++)
			dir[k] = f32(fsub_m(fld_m(&aim[k]), &o[k]));
		Vec3_normalize(dir);
		int target = GAME_VAR(int, shot + 0x14);
		B(u32, 0x6c) = target >= 0 ? GAME_VAR(u32, s + 0xa24) + target * 0xac : 0;
		memcpy(b + 0x60, aim, 12);
		B(u32, 0x74) = 0x41200000;   /* 10 */
	}
	B(int, 0x70) = 0;
	memcpy(b + 0x78, o, 12);
	memcpy(b + 0x84, o, 12);
	B(int, 0x9c) = 0;
	float *vel = (float *)(b + 0xa0);
	for (int k = 0; k < 3; k++)
		vel[k] = *w2de8 > 0 ? f32(fmul_m(fld_m(w2de8), &dir[k])) : f32(fsub_m(fld_m((const float *)(b + 0x60) + k), (const float *)(b + 0x54) + k));
	memcpy(b + 0xac, (const void *)0xa0e7e8, 12);
	B(int, 0xb8) = -1;
	B(int, 0xc0) = 0;
	B(int, 0xbc) = a4;
	if (GAME_VAR(float, w + 0x2e0c) > 0 && a4 < 0 && B(int, 0xc) == GAME_VAR(int, s + 0x202e8d4)) {
		const float *at = (const float *)(b + 0x78);
		float *tip = (float *)(b + 0xc4);
		long double tx = fmul_m(fld_m(&aim[0]), K(0x4aa444));
		float ty = f32(fmul_m(fld_m(&aim[1]), K(0x4aa444))), tz = f32(fmul_m(fld_m(&aim[2]), K(0x4aa444)));
		tip[0] = f32(fadd_m(tx, &at[0]));
		tip[1] = f32(fadd_m(fld_m(&ty), &at[1]));
		tip[2] = f32(fadd_m(fld_m(&tz), &at[2]));
	}
	B(int, 0xd0) = 0;
	B(int, 0x4e4) = 0;
	if (quiet)
		return;
	u32 rec[13] = { GAME_VAR(u32, w + 0x2dfc) + 10, B(u32, 0xc) };
	memcpy(&rec[2], b + 0x78, 12);
	memcpy(&rec[5], (const void *)0xa0e7b8, 12);
	rec[8] = B(u32, 0x10);
	float size = f32(fld_m((const float *)(w + 0x2df0)));
	memcpy(&rec[11], &size, 4);
	particle_spawn(s, rec);
	int sound = GAME_VAR(int, w + 0x2e00);
	if (sound < 0)
		return;
	if (B(int, 0xc) == GAME_VAR(int, s + 0x202e8d4))
		sound_playVolume(sound, 100);
	else
		GAME_CDECL(0x456ed0, void, int, const float *, const float *, const float *, u32)(sound, (const float *)(s + 0x20f3970),
		                                                                                (const float *)(b + 0x78), (const float *)(s + 0x20f397c), 0x47435000);
}
#undef K
#undef B
