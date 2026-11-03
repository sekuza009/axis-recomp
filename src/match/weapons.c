/* weapons.c: switching an actor's weapon. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* the next usable weapon slot of actor i, going step slots round the six (1 forward, 5 = one back): a slot is
   usable when its player record holds a weapon there, of a known type, and the actor has at least that weapon's
   ammunition cost left */
static void weapon_cycle(Stage *stage, int i, int step)
{
	u8 *actor = (u8 *)(u8 *)&((Stage *)stage)->actors[i];
	Player *ac = (Player *)actor;
	u8 *player = (u8 *)stage + 0x1561b68 + ac->player * 0x47fd2;
	int slot = (ac->slot + step) % 6;
	for (int k = 0; k < 6; k++, slot = (slot + step) % 6) {
		int weapon = FIELD(int, player, 0x320 + slot * 4);
		if (weapon < 0)
			continue;
		int type = stage->actorInfo[weapon].ammoSlot;
		if (FIELD(int, actor, 0x130 + type * 4) < stage->actorInfo[weapon].ammoPerShot || type < 0)
			continue;
		actor_selectWeapon(stage, i, slot);
		return;
	}
}

/* 0x45e9e0, 0x45e910: actor i's next and previous weapon */
void THISCALL (actor_nextWeapon)(Stage *stage, int i) { weapon_cycle(stage, i, 1); }
void THISCALL (actor_prevWeapon)(Stage *stage, int i) { weapon_cycle(stage, i, 5); }

/* 0x45e810: actor i's weapon slot changed to slot (slots 0 .. 3 also remembered as the last ordinary one), with the
   weapon its player record holds there */
void THISCALL (actor_setWeaponSlot)(Stage *stage, int i, int slot)
{
	u8 *actor = (u8 *)(u8 *)&((Stage *)stage)->actors[i];
	Player *ac = (Player *)actor;
	int player = ac->player;
	if (ac->slot != slot) {
		ac->slot = slot;
		if (slot < 4)
			FIELD(int, actor, 0x144) = slot;
		ac->actorType = FIELD(int, stage, 0x1561b68 + player * 0x47fd2 + 0x320 + slot * 4);
	}
}

/* 0x45e880: actor i starts switching to weapon slot (2 seconds) unless it is the slot in use, when its player record
   holds a weapon there of a known type */
void THISCALL (actor_selectWeapon)(Stage *stage, int i, int slot)
{
	Player *actor = (Player *)((u8 *)(u8 *)&((Stage *)stage)->actors[i]);
	if (actor->slot == slot)
		return;
	int weapon = FIELD(int, stage, 0x1561b68 + actor->player * 0x47fd2 + 0x320 + slot * 4);
	if (weapon > -1 && stage->actorInfo[weapon].ammoSlot > -1) {
		actor->weaponLowering = 1;
		actor->slotLoaded = slot;
		BITS(actor->gauge) = 0x40000000;   /* 2.0 */
	}
}

/* 0x45edb0: actor i (when +0x14c is 1) picks slot 0 four times in five, else slot 4, from the game's random table
   (0xa106f8, 4096 values, position 0xa1efb8), and its aim is set back to its own point */
void THISCALL (actor_pickRandomWeapon)(Stage *stage, int i)
{
	Player *actor = (Player *)((u8 *)(u8 *)&((Stage *)stage)->actors[i]);
	if (actor->state != 1)
		return;
	u32 r = g_randPos;
	u32 v = GAME_VAR(u32, OBJ(g_randTable) + (r & 0xfff) * 4);
	g_randPos = r + 1;
	actor_selectWeapon(stage, i, v % 100 < 80 ? 0 : 4);
	(*(int *)&actor->dodgeTime) = 0;
	(*(int *)&actor->heightTime) = 0;
	(*(int *)&actor->burstPause) = (*(int *)&actor->botTimes[3]);
	(*(int *)&actor->burstFire) = (*(int *)&actor->botTimes[4]);
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
#define ACTOR(i) ((u8 *)&((Stage *)scene)->actors[i])
	static const u8 group[10] = { 0, 0, 4, 4, 4, 8, 8, 4, 12, 12 };
	u8 *t = ACTOR(target), *a = ACTOR(attacker);
	Player *ac = (Player *)t;
	if (ac->state != 1 || FIELD(int, t, 0x880c) == 1)
		return;
	int player = ((Player *)a)->active == 1 ? ((Player *)a)->level : -1;
	if ((unsigned)kind <= 9) {
		int level = GAME_VAR(int, OBJ(g_profileRecords) + 0x28 + player * 0x4c + group[kind]) + 100;
		damage = ftol(fadd_m(fmul_m((long double)level * damage, (const float *)ADDR(k_0_01f)), (const float *)ADDR(k_0_5f)));
	}
	if (((u32)((Player *)a)->timerFlags) & 0x100)
		damage *= 2;
	if (((u32)ac->timerFlags) & 0x800)
		damage /= 2;
	if (ac->team != ((Player *)a)->team || target == attacker) {
		if (mode == 0) {
			if ((ac->shield -= damage) < 0) {
				ac->armor += ac->shield;
				ac->shield = 0;
			}
		} else if (mode == 1) {
			int shield = ac->shield;
			if (shield >= damage) {
				ac->shield = shield - damage;
				ac->armor -= ftol(fadd_m(fmul_m((long double)damage, (const float *)STR(0x4a9758, "333?\300\373\273\366")), (const float *)ADDR(k_0_5f)));
			} else {
				int lost = ftol(fadd_m(fmul_m((long double)shield, (const float *)STR(0x4a9758, "333?\300\373\273\366")), (const float *)ADDR(k_0_5f)));
				ac->armor += shield - lost - damage;
				ac->shield = 0;
			}
		}
		if (ac->armor < 0)
			ac->armor = 0;
		if (ac->shield < 0)
			ac->shield = 0;
		FIELD(int, t, 0x4bc) = mode;
		ac->lastAttacker = attacker;
		ac->mechType = value;
		FIELD(int, t, 0x8850) = 1;
	}
	BITS(ac->hitFlash) = 0x3f000000;   /* 0.5 */
	if (target == FIELD(int, scene, 0x202e8d4))
		sound_playVolume(0xc, 100);
#undef ACTOR
}

/* the next value of the game's table of rand() values (0xa106f8, 4096 of them; the position 0xa1efb8 moves on) */
static u32 table_rand(void)
{
	u32 at = g_randPos;
	g_randPos = at + 1;
	return GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4);
}

/* is |p - from| within range (as fcom has it: a NaN is) */
static int within(const float *p, const float *from, const float *range)
{
	long double d = fsub_m(fld_m(p), from);
	if (!(d >= k_0f))
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
	u8 *a = (u8 *)&((Stage *)scene)->actors[p];
	Player *ac = (Player *)a;
	const float *from = (const float *)(RELOC(a) + 0x154), *range = (const float *)(RELOC(a) + 0x8848);
	int lists[5], points[5], clear[5], n = 0;
	u8 out[12];
	for (int i = 0; i < FIELD(int, scene, 0xe3c938); i++) {
		if (i == ac->stuckPath)
			continue;
		u8 *list = (u8 *)&((Stage *)scene)->triggers[i];
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
		ac->target1 = lists[k];
		ac->target2 = points[k];
		ac->pathReverse = table_rand() & 1;
		ac->stuckPath = -1;
		FIELD(u32, a, 0x8848) = 0x44bb8000;   /* 1500.0 */
	} else
		FIELD(float, a, 0x8848) = f32(fmul_m(fld_m(range), k_1_5f));
}

#define K(address) ((const float *)RELOC(address))
#define B(type, offset) GAME_VAR(type, b + (offset))
#define BU ((Bullet *)b)   /* the same by its fields (src/scene.fields) */


/* the next of the game's random numbers (its table 0xa106f8 by the counter 0xa1efb8) below n */
static u32 next_rand(u32 n)
{
	u32 at = g_randPos;
	u32 r = GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4) % n;
	g_randPos = at + 1;
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
	u8 *b = (u8 *)&ST->bullets[slot];
	u8 *w = s + 0x14d1ab4 + GAME_VAR(int, shot + 4) * 0x2e18;
	const float *o = (const float *)(shot + 8), *aim = (const float *)(shot + 0x18);
	if (id >= 0)
		BU->id = id;
	else
		BU->id = ST->bulletSerial++;
	BU->active = 1;
	BU->weapon = GAME_VAR(int, shot + 4);
	BU->owner = owner;
	BU->colour = GAME_VAR(u32, shot + 0x24);
	memcpy(BU->from, o, 12);
	float dir[3];
	const float *w2de8 = (const float *)(w + 0x2de8);
	if (GAME_VAR(int, shot) == 0) {
		memcpy(dir, aim, 12);
		if (((ActorInfo *)w)->spread > 0) {
			long double spread = fmul_m(fld_m((const float *)(w + 0x2dec)) -
			                            fmul_m((long double)GAME_VAR(int, s + 0x1cd93cc + owner * 0x8888), K(0x4a9418)), K(0x4aa448));
			if (!(spread >= 0))
				spread = 0;
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fadd_m((long double)((int)next_rand(100) - 50) * spread, &dir[k]));
			Vec3_normalize(dir);
		}
		if (((ActorInfo *)w)->shotMode == 3) {
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
			float *v = (float *)RELOC(cone);
			Vec3_rotateAxis(v, 0, (int)next_rand(3600));
			for (int r = 0; r < 3; r++)
				dir[r] = f32(fmul_m(fld_m(&v[2]), &inv[8 + r]) + fmul_m(fld_m(&v[1]), &inv[4 + r]) + fmul_m(fld_m(&inv[r]), &v[0]));
		}
		const float *speed = (const float *)(w + 0x2de4), *from = (const float *)(RELOC(b) + 0x54);
		float *end = (float *)(RELOC(b) + 0x60);
		float sx = f32(fmul_m(fld_m(speed), &dir[0])), sy = f32(fmul_m(fld_m(speed), &dir[1]));
		long double sz = fmul_m(fld_m(speed), &dir[2]);
		end[0] = f32(fadd_m(fld_m(&sx), &from[0]));
		end[1] = f32(fadd_m(fld_m(&sy), &from[1]));
		end[2] = f32(fadd_m(sz, &from[2]));
		float hit[3];
		BU->hit = collision_rayTrace(s, from, end, hit);
		if (BU->hit) {
			memcpy(end, hit, 12);
			if (*w2de8 > 0) {
				float dx = f32(fsub_m(fld_m(&hit[0]), &from[0]));
				long double dy = fsub_m(fld_m(&hit[1]), &from[1]), dz = fsub_m(fld_m(&hit[2]), &from[2]);
				BU->life = f32(fdiv_m(x87_fsqrt((fmul_m(fld_m(&dx), &dx) + dz * dz) + dy * dy), w2de8));
			} else
				BU->life = 0.0f;
		} else if (*w2de8 > 0)
			BU->life = f32(fdiv_m(fld_m(speed), w2de8));
		else
			BU->life = 0.0f;
		if (!(BU->life >= 0) || BU->life > *K(0x4a9418))
			BU->life = 0.0f;
	} else {
		for (int k = 0; k < 3; k++)
			dir[k] = f32(fsub_m(fld_m(&aim[k]), &o[k]));
		Vec3_normalize(dir);
		int target = GAME_VAR(int, shot + 0x14);
		BITS(BU->hit) = target >= 0 ? GAME_VAR(u32, s + 0xa24) + target * 0xac : 0;
		memcpy(BU->end, aim, 12);
		BU->life = 10.0f;   /* 10 */
	}
	BU->age = 0.0f;
	memcpy(BU->prev, o, 12);
	memcpy(BU->pos, o, 12);
	BU->moved = 0;
	float *vel = (float *)(RELOC(b) + 0xa0);
	for (int k = 0; k < 3; k++)
		vel[k] = *w2de8 > 0 ? f32(fmul_m(fld_m(w2de8), &dir[k])) : f32(fsub_m(fld_m((const float *)(RELOC(b) + 0x60) + k), (const float *)(RELOC(b) + 0x54) + k));
	memcpy(BU->step, (const void *)ADDR(g_vecZero), 12);
	BU->hitActor = -1;
	B(int, 0xc0) = 0;
	BU->link = a4;
	if (((ActorInfo *)w)->tracer > 0 && a4 < 0 && BU->owner == ST->playerActor) {
		const float *at = (const float *)(RELOC(b) + 0x78);
		float *tip = (float *)(RELOC(b) + 0xc4);
		long double tx = fmul_m(fld_m(&aim[0]), K(0x4aa444));
		float ty = f32(fmul_m(fld_m(&aim[1]), K(0x4aa444))), tz = f32(fmul_m(fld_m(&aim[2]), K(0x4aa444)));
		tip[0] = f32(fadd_m(tx, &at[0]));
		tip[1] = f32(fadd_m(fld_m(&ty), &at[1]));
		tip[2] = f32(fadd_m(fld_m(&tz), &at[2]));
	}
	B(int, 0xd0) = 0;
	BU->trailCount = 0;
	if (quiet)
		return;
	u32 rec[13] = { ((u32)((ActorInfo *)w)->shotMode) + 10, ((u32)BU->owner) };
	memcpy(&rec[2], BU->prev, 12);
	memcpy(&rec[5], (const void *)OBJ(g_vecZero2), 12);
	rec[8] = BU->colour;
	float size = f32(fld_m((const float *)(w + 0x2df0)));
	memcpy(&rec[11], &size, 4);
	particle_spawn(s, rec);
	int sound = ((ActorInfo *)w)->sound;
	if (sound < 0)
		return;
	if (BU->owner == ST->playerActor)
		sound_playVolume(sound, 100);
	else
		sound_play3D(sound, ST->cameraPos,
		                                                                                (const float *)(RELOC(b) + 0x78), ST->viewDir, 0x47435000);
}
#undef K
#undef B
#undef BU

/* ---- 0x47a2d0: a bullet's frame ---- */

#define K(address) ((const float *)RELOC(address))
#define B(type, offset) GAME_VAR(type, b + (offset))
#define BU ((Bullet *)b)   /* the same by its fields (src/scene.fields) */
#define W(type, offset) GAME_VAR(type, w + (offset))
#define WI ((ActorInfo *)w)   /* the same by its fields (src/scene.fields) */
#define AF(i, offset) GAME_VAR(float, s + (offset) + (i) * 0x8888)   /* an actor's field */
#define AI(i, offset) GAME_VAR(int, s + (offset) + (i) * 0x8888)

/* an effect (particle_spawn's record r, 31 words: kind, flag, a point, a direction, three words, the size, one
   more; the rest as the last effect left them) */
static void effect(u8 *s, u32 *r, u32 kind, u32 flag, const void *at, const void *dir, u32 x0, u32 x1, u32 x2, u32 size, u32 x3)
{
	r[0] = kind;
	r[1] = flag;
	memcpy(r + 2, at, 12);
	memcpy(r + 5, dir, 12);
	r[8] = x0;
	r[9] = x1;
	r[10] = x2;
	r[11] = size;
	r[12] = x3;
	particle_spawn(s, r);
}

/* the weapon's effect size (+0x2df0), as the original passes it through the FPU */
static u32 effect_size(const u8 *w)
{
	float v = (float)fld_m(&WI->flashSize);
	return BITS(v);
}

/* the inverse of the view gluLookAt makes from the bullet's last point (+0x78) to its point (+0x84) */
static void look_inverse(u8 *b, float *inv, int x_up)
{
	float *prev = (float *)(RELOC(b) + 0x78), *cur = (float *)(RELOC(b) + 0x84), mv[16];
	glPushMatrix();
	glLoadIdentity();
	if (x_up)
		gluLookAt(prev[0], prev[1], prev[2], cur[0], cur[1], cur[2], 1.0, 0.0, 0.0);
	else
		gluLookAt(prev[0], prev[1], prev[2], cur[0], cur[1], cur[2], 0.0, 1.0, 0.0);
	glGetFloatv(0xba6, mv);
	Mat4_invert(inv, mv);
	glPopMatrix();
}

/* p + off, rounded */
static void offset_point(float *out, const float *off, const float *p)
{
	for (int k = 0; k < 3; k++)
		out[k] = f32(fadd_m(fld_m(&off[k]), &p[k]));
}

/* a beam (kind 7): its four long sides (+0xd4.., the last point's corners, +0x104.. the point's) half the size off
   the line along the view's y (+-) and x (+-), each drawn as a textured strip (kind -1) with the bullet id's
   quarter of the texture (+0); the length kept (+0x494). The flying copy sums the length's squares in another order */
static void beam(u8 *s, u8 *b, const u8 *w, u32 *r, int flying)
{
	float *prev = (float *)(RELOC(b) + 0x78), *cur = (float *)(RELOC(b) + 0x84), inv[16], a[3];
	look_inverse(b, inv, 0);
	float half = f32(fld_m(&WI->flashSize)), minus;
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fadd_m(fmul_m(fld_m(&half), &inv[4 + k]), K(0x4a93e8)), K(0x4a93e8)));
	offset_point((float *)(RELOC(b) + 0xd4), a, prev);
	offset_point((float *)(RELOC(b) + 0x104), a, cur);
	minus = f32(-fld_m(&WI->flashSize));
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fadd_m(fmul_m(fld_m(&minus), &inv[4 + k]), K(0x4a93e8)), K(0x4a93e8)));
	offset_point((float *)(RELOC(b) + 0xe0), a, prev);
	offset_point((float *)(RELOC(b) + 0x110), a, cur);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fmul_m(fld_m(&half), &inv[k]), K(0x4a93e8)));
	offset_point((float *)(RELOC(b) + 0xec), a, prev);
	offset_point((float *)(RELOC(b) + 0x11c), a, cur);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fmul_m(fld_m(&minus), &inv[k]), K(0x4a93e8)));
	offset_point((float *)(RELOC(b) + 0xf8), a, prev);
	offset_point((float *)(RELOC(b) + 0x128), a, cur);
	long double dx = fsub_m(fld_m(&cur[0]), &prev[0]), dy = fsub_m(fld_m(&cur[1]), &prev[1]), dz = fsub_m(fld_m(&cur[2]), &prev[2]);
	long double len = flying ? x87_fsqrt((dx * dx + dz * dz) + dy * dy) : x87_fsqrt((dz * dz + dy * dy) + dx * dx);
	BU->trailAge[0] = (float)len;
	float scale = f32(fmul_m(len, K(0x4aa450)));   /* / 800 */
	u32 colour = GAME_VAR(u32, s + 0x9ccfe4);
	for (int k = 0; k < 4; k++) {
		int quarter = BU->id % 4;
		float v0, u;
		if (k & 1) {
			long double t = fmul_m((long double)(quarter << 5), K(0x4a957c));   /* / 256 */
			v0 = f32(fadd_m(t, K(0x4a958c)));
			u = f32(fadd_m(t, K(0x4a9420)));
		} else {
			long double t = fmul_m((long double)((quarter + 1) << 5), K(0x4a957c));
			v0 = f32(fsub_m(t, K(0x4a958c)));
			u = f32(fsub_m(t, K(0x4a9420)));
		}
		const u8 *side = b + 0xd4 + k * 0xc;
		r[0] = (u32)-1;
		r[12] = 1;
		r[13] = colour;
		r[14] = 0;
		r[15] = BITS(u);
		r[16] = BITS(scale);
		r[17] = BITS(v0);
		r[18] = 0xffffffff;
		memcpy(r + 19, prev, 12);
		memcpy(r + 22, cur, 12);
		memcpy(r + 25, side + 0x30, 12);
		memcpy(r + 28, side, 12);
		particle_spawn(s, r);
	}
}

/* a trail (kind 3): the ring of 20 cross-sections (+0x4e4 counts them; 0x30 bytes each from +0xd4, the age of each
   at +0x494): this one half the size about the last point along the view's y and x (up is x for a vertical
   line), the next one collapsed onto the point. The flying copy keeps one product unrounded */
static void trail(u8 *b, const u8 *w, int flying)
{
	float *prev = (float *)(RELOC(b) + 0x78), *cur = (float *)(RELOC(b) + 0x84), inv[16], a[3];
	look_inverse(b, inv, !(prev[0] < cur[0]) && !(prev[0] > cur[0]) && !(prev[2] < cur[2]) && !(prev[2] > cur[2]));
	int i = BU->trailCount % 20;
	u8 *ring = b + i * 0x30;
	long double half = fld_m(&WI->flashSize);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[4 + k]));
	offset_point((float *)(ring + 0xd4), a, prev);
	half = fld_m(&WI->flashSize);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[k]));
	offset_point((float *)(ring + 0xe0), a, prev);
	half = -fld_m(&WI->flashSize);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[4 + k]));
	offset_point((float *)(ring + 0xec), a, prev);
	half = -fld_m(&WI->flashSize);
	float *last = (float *)(ring + 0xf8);
	for (int k = 0; k < 2; k++)
		a[k] = f32(fmul_m(half, &inv[k]));
	last[0] = f32(fadd_m(fld_m(&a[0]), &prev[0]));
	last[1] = f32(fadd_m(fld_m(&a[1]), &prev[1]));
	if (flying)
		last[2] = f32(fadd_m(fmul_m(half, &inv[2]), &prev[2]));
	else {
		a[2] = f32(fmul_m(half, &inv[2]));
		last[2] = f32(fadd_m(fld_m(&a[2]), &prev[2]));
	}
	BITS(BU->trailAge[i]) = BITS(BU->age);
	i = ++BU->trailCount % 20;
	ring = b + i * 0x30;
	for (int c = 0; c < 4; c++)
		memcpy(ring + 0xd4 + c * 0xc, cur, 12);
	BITS(BU->trailAge[i]) = BITS(BU->age);
}

/* the shot drawn by its kind (+0x2dfc): a trail, a beam, or a particle of kind + 0x14 from the last point to the
   point (flagged for the camera's own first 0.03 s, +0x202e8d8) */
static void draw_shot(u8 *s, u8 *b, const u8 *w, u32 *r, int flying)
{
	int kind = WI->shotMode;
	if (kind == 3)
		trail(b, w, flying);
	else if (kind == 7)
		beam(s, b, w, r, flying);
	else {
		u32 flag = BU->owner == ST->selectedActor && !(BU->age >= *K(0x4a9568)) ? 1 : 0;
		effect(s, r, kind + 0x14, flag, b + 0x78, b + 0x84, 0, 0, 0, effect_size(w), 0);
	}
}

/* the bullet hit actor +0xb8: the damage when the actor is the local player's and alive (+0x1cd94f4), sparks and a
   flash (kind 8, the actor's 0x2000 flag) facing away from it, the hit sound, the local owner's hit beep, and the
   push (+0x1ce1c04: 10 times the weapon's +0x2e14 towards the actor) */
static void hit_actor(u8 *s, u8 *b, const u8 *w, u32 *r, int weapon)
{
	int t = BU->hitActor;
	if (ST->actors[t].pilot == ST->playerActor && ST->actors[t].state == 1)
		bullet_playImpactSound(s, BU->owner, t, WI->damageMode, WI->damage, WI->shotMode, weapon);
	t = BU->hitActor;
	float dir[3];
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m((const float *)(RELOC(b) + 0x84) + k), &AF(t, 0x1cd9528 + k * 4)));
	Vec3_normalize(dir);
	effect(s, r, WI->shotMode + 0x1e, 0, b + 0x60, dir, 0, 0, 0, effect_size(w), 0);
	effect(s, r, 8, ST->actors[BU->hitActor].timerFlags & 0x2000, b + 0x60, dir, 0, 0, 0, 0, 0);
	if (WI->hitSound >= 0)
		sound_play3D(WI->hitSound, s + 0x20f3970, b + 0x84, s + 0x20f397c, 0x47435000);
	if (BU->owner == ST->playerActor)
		sound_playVolume(0xb, 100);
	if (WI->push > 0) {
		long double k = -fld_m(&WI->push);
		float x = f32(fmul_m(k, &dir[0])), y = f32(fmul_m(k, &dir[1]));
		long double z = fmul_m(k, &dir[2]);
		float *push = &AF(BU->hitActor, 0x1ce1c04);
		push[0] = f32(fmul_m(fld_m(&x), K(0x4a9418)));
		push[1] = f32(fmul_m(fld_m(&y), K(0x4a9418)));
		push[2] = f32(fmul_m(z, K(0x4a9418)));
	}
	B(int, 0xd0) = 1;
}

/* ((M[a] * p[ia] + M[b] * p[ib]) + M[c] * p[ic]) + M[t], each product a matrix entry times a point's */
static float through(const float *M, const float *p, int a, int ia, int b, int ib, int c, int ic, int t)
{
	long double v = fmul_m(fld_m(&M[a]), &p[ia]) + fmul_m(fld_m(&M[b]), &p[ib]);
	return f32(fadd_m(v + fmul_m(fld_m(&M[c]), &p[ic]), &M[t]));
}

/* the mark on the hit surface (kind + 0x28): its plane's axes from the triangle's first corner and the normal,
   the other two corners' coordinates in them (uv: the axes' lengths, 0, then two pairs) */
static void decal(u8 *s, u8 *b, const u8 *w, u32 *r, const u8 *h, const float *N, const float *P)
{
	const float *imp = (const float *)(RELOC(b) + 0x60);
	float e[3], uv[6], c2, le;
	for (int k = 0; k < 3; k++)
		e[k] = f32(fsub_m(fld_m(&P[k]), &imp[k]));
	long double c0 = fmul_m(fld_m(&e[1]), &N[2]) - fmul_m(fld_m(&e[2]), &N[1]);
	long double c1 = fmul_m(fld_m(&N[0]), &e[2]) - fmul_m(fld_m(&N[2]), &e[0]);
	c2 = f32(fmul_m(fld_m(&N[1]), &e[0]) - fmul_m(fld_m(&N[0]), &e[1]));
	le = f32(x87_fsqrt((fmul_m(fld_m(&e[2]), &e[2]) + fmul_m(fld_m(&e[1]), &e[1])) + fmul_m(fld_m(&e[0]), &e[0])));
	long double lc = x87_fsqrt((fmul_m(fld_m(&c2), &c2) + c1 * c1) + c0 * c0);
	if (!(le < 0) && !(le > 0))
		BITS(le) = 0x3f800000;
	if (!(lc < 0) && !(lc > 0))
		lc = fld_m(K(0x4a9424));
	uv[0] = le;
	uv[1] = 0;
	for (int q = 1; q < 3; q++) {
		long double f0 = fsub_m(fld_m(&P[q * 3]), &imp[0]), f1 = fsub_m(fld_m(&P[q * 3 + 1]), &imp[1]), f2 = fsub_m(fld_m(&P[q * 3 + 2]), &imp[2]);
		uv[q * 2] = f32(fdiv_m((fmul_m(f2, &e[2]) + fmul_m(f1, &e[1])) + fmul_m(f0, &e[0]), &le));
		uv[q * 2 + 1] = f32(((fmul_m(f2, &c2) + f1 * c1) + f0 * c0) / lc);
	}
	const int *obj = GAME_VAR(const int *, h + 0x8c);
	if (obj) {
		u8 *part = GAME_VAR(u8 *, GAME_VAR(u8 *, s + 0x131b0c0 + *obj * 0x2cc) + 0x14) + GAME_VAR(int, h + 0x90) * 0x80;
		float tri[9];
		for (int k = 0; k < 3; k++)
			memcpy(tri + k * 3, GAME_VAR(float *, part + 0x50) + GAME_VAR(int, h + 0x94 + k * 4) * 3, 12);
		effect(s, r, WI->shotMode + 0x28, 0, imp, N, (u32)(s + 0x131af38 + *GAME_VAR(const int *, h + 0x8c) * 0x2cc), (u32)tri, (u32)uv, 0, 0);
	} else
		effect(s, r, WI->shotMode + 0x28, 0, imp, N, 0, (u32)P, (u32)uv, effect_size(w), 0);
}

/* the surface the bullet hit (+0x6c, a collision triangle record: corners +4, normal +0x4c, its object +0x8c):
   the corners and normal taken into the world through the object's matrix (+0x1f4), the impact (kind + 0x1e), a
   mark unless the surface takes none (flag 0x10) or marks are off (0x83a9c8), the hit sound */
static void hit_surface(u8 *s, u8 *b, const u8 *w, u32 *r)
{
	const u8 *h = (*(const u8 * *)&BU->hit);
	if (!h)
		return;
	float N[3], P[9];
	const float *n = (const float *)(h + 0x4c), *p = (const float *)(h + 4);
	const int *obj = GAME_VAR(const int *, h + 0x8c);
	if (obj) {
		const float *M = (const float *)(s + 0x131ae44 + *obj * 0x2cc + 0x1f4);
		N[0] = f32((fmul_m(fld_m(&n[2]), &M[8]) + fmul_m(fld_m(&n[1]), &M[4])) + fmul_m(fld_m(&n[0]), &M[0]));
		N[1] = f32((fmul_m(fld_m(&n[0]), &M[1]) + fmul_m(fld_m(&n[2]), &M[9])) + fmul_m(fld_m(&n[1]), &M[5]));
		N[2] = f32((fmul_m(fld_m(&n[0]), &M[2]) + fmul_m(fld_m(&n[2]), &M[10])) + fmul_m(fld_m(&n[1]), &M[6]));
		P[0] = through(M, p, 4, 1, 8, 2, 0, 0, 12);
		P[1] = through(M, p, 5, 1, 1, 0, 9, 2, 13);
		P[2] = through(M, p, 6, 1, 2, 0, 10, 2, 14);
		P[3] = through(M, p + 3, 4, 1, 8, 2, 0, 0, 12);
		P[4] = through(M, p + 3, 1, 0, 5, 1, 9, 2, 13);
		P[5] = through(M, p + 3, 2, 0, 6, 1, 10, 2, 14);
		P[6] = through(M, p + 6, 8, 2, 4, 1, 0, 0, 12);
		P[7] = through(M, p + 6, 9, 2, 1, 0, 5, 1, 13);
		P[8] = through(M, p + 6, 10, 2, 2, 0, 6, 1, 14);
	} else {
		for (int k = 0; k < 3; k++)
			N[k] = (float)fld_m(&n[k]);
		memcpy(P, p, 36);
	}
	effect(s, r, WI->shotMode + 0x1e, 0, b + 0x60, N, 0, 0, 0, effect_size(w), 0);
	if (!(*(*(const u8 * *)&BU->hit) & 0x10) && g_items3D == 1)
		decal(s, b, w, r, (*(const u8 * *)&BU->hit), N, P);
	if (WI->hitSound >= 0)
		sound_play3D(WI->hitSound, s + 0x20f3970, b + 0x60, s + 0x20f397c, 0x47435000);
	B(int, 0xd0) = 1;
}

/* splash damage once the bullet hit (+0xd0): every other live actor of the local player's (+0x1cd94b8) with health
   over 3 within the weapon's radius (+0x2df4) of the point is hurt by up to the weapon's damage (by distance) and
   pushed (+0x1ce1c04) */
static void splash(u8 *s, u8 *b, const u8 *w)
{
	if (B(int, 0xd0) != 1 || !(WI->splashRadius > 0))
		return;
	for (int j = 0; j < ST->actorCount; j++) {
		if (ST->actors[j].state != 1 || !(ST->actors[j].blinkTime > 3.0f) || ST->actors[j].pilot != ST->playerActor || BU->hitActor == j
		    || ST->actors[j].cameraValue == 1)
			continue;
		float d[3];
		for (int k = 0; k < 3; k++)
			d[k] = f32(fsub_m(fld_m(&AF(j, 0x1cd9528 + k * 4)), (const float *)(RELOC(b) + 0x84) + k));
		long double len = Vec3_normalize(d);
		if (len >= WI->splashRadius)
			continue;
		float f = f32(fsubr_m(fmul_m(fdiv_m(len, &WI->splashRadius), K(0x4a942c)), K(0x4a9424)));   /* 1 - len / r / 2 */
		int damage = ftol(fmul_m((long double)WI->damage, &f));
		bullet_playImpactSound(s, BU->owner, j, WI->damageMode, damage, WI->shotMode, BU->weapon);
		if (WI->push > 0) {
			long double k = fld_m(&WI->push);
			float x = f32(fmul_m(k, &d[0])), y = f32(fmul_m(k, &d[1]));
			long double z = fmul_m(k, &d[2]);
			float x10 = f32(fmul_m(fld_m(&x), K(0x4a9418))), y10 = f32(fmul_m(fld_m(&y), K(0x4a9418)));
			long double z10 = fmul_m(z, K(0x4a9418));
			float *push = &AF(j, 0x1ce1c04);
			push[0] = f32(fmul_m(fld_m(&f), &x10));
			push[1] = f32(fmul_m(fld_m(&y10), &f));
			push[2] = f32(fmul_m(z10, &f));
		}
	}
}

/* homing: the velocity (+0xa0) turned towards the target (actor +0xbc, else the point +0xc4) by at most the turn
   rate (+0x2e0c, degrees: the cosine table 0xa17f38) about their cross product, at the weapon's speed (+0x2de8;
   for kind 3 both by the bullet's age); again in 1/15 s (+0xc0) */
static void home(u8 *s, u8 *b, const u8 *w)
{
	float *prev = (float *)(RELOC(b) + 0x78), *vel = (float *)(RELOC(b) + 0xa0), spd, rate, T[3];
	if (WI->shotMode != 3) {
		BITS(spd) = BITS(WI->velocity);
		BITS(rate) = BITS(WI->tracer);
	} else {
		long double x = fsub_m(fmul_m(fld_m(&BU->age), K(0x4a947c)), K(0x4a9424));   /* 4 age - 1 */
		spd = f32(fmul_m(fadd_m(((x * x) * x) * x, K(0x4a93ec)), &WI->velocity));
		long double y = fadd_m(fld_m(&BU->age), K(0x4a9424));
		rate = f32(fdivr_m((y * y) * y, &WI->tracer));
	}
	int tg = BU->link;
	for (int k = 0; k < 3; k++)
		T[k] = f32(fsub_m(fld_m(tg >= 0 ? &AF(tg, 0x1cd9528 + k * 4) : (const float *)(RELOC(b) + 0xc4) + k), &prev[k]));
	Vec3_normalize(T);
	Vec3_normalize(vel);
	long double dot = (fmul_m(fld_m(&T[2]), &vel[2]) + fmul_m(fld_m(&T[1]), &vel[1])) + fmul_m(fld_m(&T[0]), &vel[0]);
	int deg = ftol(fld_m(&rate));
	if (fld_m(g_cosTable + deg) > dot) {
		float axis[3], rot[4], m[16];
		axis[0] = f32(fmul_m(fld_m(&T[2]), &vel[1]) - fmul_m(fld_m(&T[1]), &vel[2]));
		axis[1] = f32(fmul_m(fld_m(&T[0]), &vel[2]) - fmul_m(fld_m(&T[2]), &vel[0]));
		axis[2] = f32(fmul_m(fld_m(&T[1]), &vel[0]) - fmul_m(fld_m(&T[0]), &vel[1]));
		Vec3_normalize(axis);
		rot[0] = f32(fmul_m(fld_m(&rate), K(0x4aa44c)));   /* in radians */
		for (int k = 0; k < 3; k++)
			rot[1 + k] = (float)fld_m(&axis[k]);
		Mat4_fromAxisAngle(m, rot);
		T[0] = f32((fmul_m(fld_m(&m[8]), &vel[2]) + fmul_m(fld_m(&m[4]), &vel[1])) + fmul_m(fld_m(&m[0]), &vel[0]));
		T[1] = f32((fmul_m(fld_m(&m[1]), &vel[0]) + fmul_m(fld_m(&m[9]), &vel[2])) + fmul_m(fld_m(&m[5]), &vel[1]));
		T[2] = f32((fmul_m(fld_m(&m[2]), &vel[0]) + fmul_m(fld_m(&m[10]), &vel[2])) + fmul_m(fld_m(&m[6]), &vel[1]));
	}
	B(u32, 0xc0) = 0x3d888889;   /* 1/15 */
	vel[0] = f32(fmul_m(fld_m(&spd), &T[0]));
	vel[1] = f32(fmul_m(fld_m(&T[1]), &spd));
	vel[2] = f32(fmul_m(fld_m(&T[2]), &spd));
}

/* a local player's bullet in flight: homing, the step by its velocity (none for a weapon of no speed: it ends at
   its point +0x60 at once, as does one whose life ends this frame unless it homes), the nearest actor the step
   passes within its radius plus the weapon's size (math_segmentSphere; the bullet then stops there), else for a
   homing weapon the world in the way (collision_rayTrace: the hit record +0x6c and the life cut to it) */
static void fly_local(u8 *s, u8 *b, const u8 *w, const float *dt)
{
	float *prev = (float *)(RELOC(b) + 0x78), *cur = (float *)(RELOC(b) + 0x84), *vel = (float *)(RELOC(b) + 0xa0), *step = (float *)(RELOC(b) + 0xac);
	if (WI->tracer > 0 && WI->velocity > 0) {
		long double v = fsub_m(fld_m(&B(float, 0xc0)), dt);
		B(float, 0xc0) = (float)v;
		if (!(v > 0))
			home(s, b, w);
	}
	if (WI->velocity > 0) {
		for (int k = 0; k < 3; k++)
			step[k] = f32(fmul_m(fld_m(dt), &vel[k]));
		if (!(fadd_m(fld_m(dt), &BU->age) > BU->life) || WI->tracer > 0) {
			cur[0] = f32(fadd_m(fld_m(&step[0]), &prev[0]));
			cur[1] = f32(fadd_m(fld_m(&prev[1]), &step[1]));
			cur[2] = f32(fadd_m(fld_m(&prev[2]), &step[2]));
		} else
			memcpy(cur, BU->end, 12);
	} else {
		memcpy(step, vel, 12);
		memcpy(cur, BU->end, 12);
	}
	float dir[3], best, hit[3], t;
	memcpy(dir, step, 12);
	Vec3_normalize(dir);
	BITS(best) = 0x7f7fffff;
	for (int j = 0; j < ST->actorCount; j++) {
		if (ST->actors[j].state != 1 || !(ST->actors[j].blinkTime > 3.0f) || j == BU->owner || ST->actors[j].cameraValue != 0)
			continue;
		float radius = f32(fadd_m(fld_m(&AF(j, 0x1cd9790)), &WI->flashSize));
		if (math_segmentSphere(prev, cur, dir, &AF(j, 0x1cd9528), radius, hit, &t) == 1 && !(t >= best)) {
			BU->hitActor = j;
			memcpy(cur, hit, 12);
			memcpy(BU->end, hit, 12);
			BITS(best) = BITS(t);
		}
	}
	if (BU->hitActor >= 0) {
		BU->hit = 0;
		BITS(BU->life) = BITS(BU->age);
	}
	if (WI->tracer > 0 && BU->hitActor < 0) {
		float h[3];
		int r = collision_rayTrace(s, prev, cur, h);
		BU->hit = r;
		if (r) {
			memcpy(BU->end, h, 12);
			h[0] = f32(fsub_m(fld_m(&h[0]), &prev[0]));
			long double dy = fsub_m(fld_m(&h[1]), &prev[1]);
			h[1] = (float)dy;
			long double dz = fsub_m(fld_m(&h[2]), &prev[2]);
			h[2] = (float)dz;
			long double len = x87_fsqrt((fmul_m(fld_m(&h[0]), &h[0]) + dz * dz) + dy * dy);
			long double spd = x87_fsqrt((fmul_m(fld_m(&vel[0]), &vel[0]) + fmul_m(fld_m(&vel[1]), &vel[1])) + fmul_m(fld_m(&vel[2]), &vel[2]));
			BU->life = f32(fadd_m(len / spd, &BU->age));
		}
	}
	BU->moved = 1;
}

/* 0x47a2d0 (thiscall on the scene): bullet slot's frame (0x4e8 bytes from +0x202ef34; its weapon's record 0x2e18
   bytes from +0x14d1ab4). An actor it hit (+0xb8) takes it first. In flight (age +0x70 up to its life +0x74): the
   local player's (+0x202e8d4) bullets move and find their hits (fly_local), other players' follow the network's
   points (+0x90, or the last step again); it is drawn when it moved (+0x9c), aged, and its owner told when it ends
   (+0x1cd971c). Afterwards: another player's bullet is drawn at its last point, then the surface it hit, the
   splash, and the slot freed (actor_clearTargetRefs) */
void THISCALL (bullet_update)(u8 *s, int slot, u32 dt_bits)
{
	const float *dt = (const float *)&dt_bits;   /* (only ever read from memory, as the original does) */
	u8 *b = (u8 *)&ST->bullets[slot];
	int weapon = BU->weapon;
	u8 *w = (u8 *)&ST->actorInfo[weapon];
	u32 r[31];   /* particle_spawn's record, reused */
	float *prev = (float *)(RELOC(b) + 0x78), *cur = (float *)(RELOC(b) + 0x84), *step = (float *)(RELOC(b) + 0xac);
	if (BU->hitActor >= 0)
		hit_actor(s, b, w, r, weapon);
	if (!(BU->age > BU->life)) {
		memcpy(prev, cur, 12);
		if (ST->actors[BU->owner].pilot == ST->playerActor)
			fly_local(s, b, w, dt);
		else if (BU->moved == 1) {
			memcpy(cur, BU->netPoint, 12);
			for (int k = 0; k < 3; k++)
				step[k] = f32(fsub_m(fld_m(&cur[k]), &prev[k]));
			Vec3_normalize(step);
		} else
			for (int k = 0; k < 3; k++)
				cur[k] = f32(fadd_m(fld_m(&step[k]), &prev[k]));
		if (BU->moved == 1)
			draw_shot(s, b, w, r, 1);
		long double age = fadd_m(fld_m(dt), &BU->age);
		BU->age = (float)age;
		if (age > BU->life)
			AI(BU->owner, 0x1cd971c) = 1;
		BU->moved = 0;
		return;
	}
	if (ST->actors[BU->owner].pilot != ST->playerActor) {
		memcpy(cur, BU->netPoint, 12);
		for (int k = 0; k < 3; k++)
			step[k] = f32(fsub_m(fld_m(&cur[k]), &prev[k]));
		draw_shot(s, b, w, r, 0);
	}
	hit_surface(s, b, w, r);
	splash(s, b, w);
	actor_clearTargetRefs(s, slot);
}
#undef K
#undef B
#undef BU
#undef W
#undef WI
#undef AF
#undef AI
