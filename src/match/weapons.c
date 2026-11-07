/* weapons.c: an actor's weapons (switching, picking), the damage a hit does, and the bullets (fired, flying, hitting). */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */


/* the next usable weapon slot of actor i, going step slots round the six (1 forward, 5 = one back): a slot is
   usable when its player record holds a weapon there, of a known type, and the actor has at least that weapon's
   ammunition cost left */
static void weapon_cycle(Stage *stage, int i, int step)
{
	u8 *actor = (u8 *)(u8 *)&((Stage *)stage)->actors[i];
	Player *ac = (Player *)actor;
	const PlayerRecord *player = &stage->playerRecords[ac->player];
	int slot = (ac->slot + step) % 6;
	for (int k = 0; k < 6; k++, slot = (slot + step) % 6) {
		int weapon = player->items[slot];
		if (weapon < 0)
			continue;
		int type = stage->actorItems[weapon].ammoType;
		if (ac->ammo[type] < stage->actorItems[weapon].ammoPerShot || type < 0)
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
	u8 *actor = (u8 *)(u8 *)&stage->actors[i];
	Player *ac = (Player *)actor;
	int player = ac->player;
	if (ac->slot != slot) {
		ac->slot = slot;
		if (slot < 4)
			ac->lastWeaponSlot = slot;
		ac->heldItem = stage->playerRecords[player].items[slot];
	}
}

/* 0x45e880: actor i starts switching to weapon slot (weaponLowering 1, switchSlot; its icon shown 2 s, slotIconTime)
   unless it is the slot in use, when its player record holds a weapon there of a known type */
void THISCALL (actor_selectWeapon)(Stage *stage, int i, int slot)
{
	Player *actor = (&stage->actors[i]);
	if (actor->slot == slot)
		return;
	int weapon = stage->playerRecords[actor->player].items[slot];
	if (weapon > -1 && stage->actorItems[weapon].ammoType > -1) {
		actor->weaponLowering = 1;
		actor->switchSlot = slot;
		actor->slotIconTime = 2.0f;
	}
}

/* 0x45edb0: actor i (when state is 1) switches to slot 0 four times in five, else slot 4 (actor_selectWeapon), by the
   game's random table (g_randTable, 4096 values, position g_randPos); its bot timers restarted: dodgeTime and
   heightTime 0, burstPause and burstFire from botParams[3] / botParams[4] */
void THISCALL (actor_pickRandomWeapon)(Stage *stage, int i)
{
	Player *actor = (&stage->actors[i]);
	if (actor->state != 1)
		return;
	u32 r = g_randPos;
	u32 v = (*(u32 *)&g_randTable[r & 0xfff]);
	g_randPos = r + 1;
	actor_selectWeapon(stage, i, v % 100 < 80 ? 0 : 4);
	(*(int *)&actor->dodgeTime) = 0;
	(*(int *)&actor->heightTime) = 0;
	(*(int *)&actor->burstPause) = (*(int *)&actor->botParams[3]);
	(*(int *)&actor->burstFire) = (*(int *)&actor->botParams[4]);
}

/* 0x460000 (thiscall on the scene): actor target hit by actor attacker for damage, when it is in play (state 1) and
   not invulnerable. For shot modes 0 .. 9 (the weapon's shotMode) the damage is scaled by the attacker's pilot character's stat for the mode's group
   (g_characterProfiles[character].stats[0 .. 3] + 100, per cent, rounded); doubled by the attacker's timer flag 0x100 and
   halved by the target's 0x800. Unless both are on one team (and not the same actor) it comes off: mode 0 the shield
   first, the rest off the armour; mode 1 the shield, the armour losing 0.7 of it as well, and once the shield is
   gone the rest off the armour; neither below 0; the hit recorded (lastHitMode, lastAttacker, lastHitWeapon the
   weapon, hitPending). The hit flash 0.5 either way, and a sound when the target is the local player. Its callers ignore
   the eax it leaves */
void THISCALL (actor_takeDamage)(u8 *scene, int attacker, int target, int mode, int damage, int shotMode, u32 weapon)
{
	Stage *st = (Stage *)scene;
#define ACTOR(i) ((u8 *)&st->actors[i])
	static const u8 group[10] = { 0, 0, 1, 1, 1, 2, 2, 1, 3, 3 };   /* (the stat by shot mode) */
	Player *ac = (Player *)ACTOR(target), *atk = (Player *)ACTOR(attacker);
	if (ac->state != 1 || ac->invulnerable == 1)
		return;
	int character = atk->active == 1 ? atk->character : -1;
	if ((unsigned)shotMode <= 9) {
		int percent = ((CharacterProfile *)g_characterProfiles)[character].stats[group[shotMode]] + 100;
		damage = ftol(fadd_m(fmul_m((long double)percent * damage, (const float *)ADDR(k_0_01f)), (const float *)ADDR(k_0_5f)));
	}
	if (((u32)atk->stateFlags) & 0x100)
		damage *= 2;
	if (((u32)ac->stateFlags) & 0x800)
		damage /= 2;
	if (ac->team != atk->team || target == attacker) {
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
		ac->lastHitMode = mode;
		ac->lastAttacker = attacker;
		ac->lastHitWeapon = weapon;
		ac->hitPending = 1;
	}
	ac->hitFlash = 0.5f;
	if (target == st->playerActor)
		sound_playVolume(0xc, 100);
#undef ACTOR
}

/* the next value of the game's table of rand() values (g_randTable, 4096 of them; the position g_randPos moves on) */
static u32 table_rand(void)
{
	u32 at = g_randPos;
	g_randPos = at + 1;
	return (*(u32 *)&g_randTable[at & 0xfff]);
}

/* is |p - from| within range (as fcom has it: a NaN is) */
static int within(const float *p, const float *from, const float *range)
{
	long double d = fsub_m(fld_m(p), from);
	if (!(d >= k_0f))
		d = -d;
	return !(d > *range);
}

/* 0x460270 (thiscall on the scene): a new target for actor p (0x8888-byte actors from actors): the points (0x14
   bytes) of every point list (0x1c-byte records from triggers: a count, the points; triggerCount lists) but the one
   it follows (stuckPath) within its range (pathRange) on each axis of it (pos) are candidates. The first five are
   kept, marked whether the line to them is clear (collision_rayTrace); after that a clear one takes the place of a
   random one that is not clear (two tries), and that list is left. One of the candidates picked at random: the
   target (path list, pathPoint point, pathReverse a random side), stuckPath none, the range 1500. With none the range
   grows (x k_1_5f). Its caller ignores the eax it leaves */
void THISCALL (actor_pickPathPoint)(u8 *scene, int p)
{
	Stage *st = (Stage *)scene;
	u8 *a = (u8 *)&st->actors[p];
	Player *ac = (Player *)a;
	const float *from = ac->pos, *range = &ac->pathRange;
	int lists[5], points[5], clear[5], n = 0;
	u8 out[12];
	for (int i = 0; i < st->triggerCount; i++) {
		if (i == ac->stuckPath)
			continue;
		const Trigger *list = &st->triggers[i];
		for (int j = 0; j < list->wayPointCount; j++) {
			const float *pt = ((const WayPoint *)list->wayPoints)[j].pos;
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
		ac->path = lists[k];
		ac->pathPoint = points[k];
		ac->pathReverse = table_rand() & 1;
		ac->stuckPath = -1;
		BITS(ac->pathRange) = 0x44bb8000;   /* 1500.0 */
	} else
		ac->pathRange = f32(fmul_m(fld_m(range), k_1_5f));
}

#define K(address) ((const float *)RELOC(address))
#define BU ((Bullet *)b)   /* the same by its fields (src/scene.fields) */


/* the next of the game's random numbers (its table g_randTable by the counter g_randPos) below n */
static u32 next_rand(u32 n)
{
	u32 at = g_randPos;
	u32 r = (*(u32 *)&g_randTable[at & 0xfff]) % n;
	g_randPos = at + 1;
	return r;
}

/* 0x479b40 (thiscall on the scene): bullet slot (0x4e8 bytes from bullets) fired by owner from the shot (+0 a
   target given, +4 the weapon: its record 0x2e18 bytes from actorItems, +8 the origin, hitPlane the target's record,
   dir the direction or the target, muzzle kept at colour). Its id (or the next serial, bulletSerial). Aimed shots
   spread with the weapon's spread less the owner's steadiness (accuracy) and are renormalised; mode 3 (shotMode) fires
   into a random cone about the direction (through gluLookAt's inverse); the whole shooting range (the weapon's range) is
   traced (collision_rayTrace; the hit record hit, its end impact) and the round's life is the distance to that end over
   its velocity (0 unless 0 .. 10 seconds). Then its
   velocity (velocity times the direction, or the step), colour, the homing target (homingTarget: a guided round's; the local player's own guided round follows the aim point), and, unless
   quiet, the muzzle flash (particle kind shotMode + 10) and the firing sound (sound: at full volume for the local
   player playerActor, else placed). Its callers ignore the eax it leaves */
void THISCALL (bullet_init)(u8 *s, int slot, int id, int owner, int homingTarget, const u8 *shot, int quiet)
{
	u8 *b = (u8 *)&ST->bullets[slot];
	const FiredRound *rd = (const FiredRound *)shot;
	ActorItem *w = (ActorItem *)((u8 *)&ST->actorItems[rd->weapon]);
	const float *o = rd->from, *aim = rd->dir;
	if (id >= 0)
		BU->id = id;
	else
		BU->id = ST->bulletSerial++;
	BU->active = 1;
	BU->weapon = rd->weapon;
	BU->owner = owner;
	BU->muzzle = rd->muzzle;
	memcpy(BU->from, o, 12);
	float dir[3];
	const float *w2de8 = &w->velocity;
	if (rd->received == 0) {
		memcpy(dir, aim, 12);
		if (w->spread > 0) {
			long double spread = fmul_m(fld_m(&w->spread) -
			                            fmul_m((long double)ST->actors[owner].accuracy, &k_10f), K(0x4aa448));
			if (!(spread >= 0))
				spread = 0;
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fadd_m((long double)((int)next_rand(100) - 50) * spread, &dir[k]));
			Vec3_normalize(dir);
		}
		if (w->shotMode == 3) {
			glPushMatrix();
			glLoadIdentity();
			for (int k = 0; k < 3; k++)
				dir[k] = f32(FADD(dir[k], o[k]));
			gluLookAt(o[0], o[1], o[2], dir[0], dir[1], dir[2], 0.0, 1.0, 0.0);
			float m[16], inv[16];
			glGetFloatv(0xba6, m);
			Mat4_invert(inv, m);
			glPopMatrix();
			u32 cone[3] = { 0, 0x3e10d068, 0x3f7d6d5d };   /* 0, 0.141, 0.990: 8.1 degrees off the axis */
			float *v = (float *)RELOC(cone);
			Vec3_rotateAxis(v, 0, (int)next_rand(3600));
			for (int r = 0; r < 3; r++)
				dir[r] = f32(FMUL(v[2], inv[8 + r]) + FMUL(v[1], inv[4 + r]) + FMUL(inv[r], v[0]));
		}
		const float *range = &w->range, *from = BU->from;
		float *end = BU->impact;
		float sx = f32(fmul_m(fld_m(range), &dir[0])), sy = f32(fmul_m(fld_m(range), &dir[1]));
		long double sz = fmul_m(fld_m(range), &dir[2]);
		end[0] = f32(FADD(sx, from[0]));
		end[1] = f32(FADD(sy, from[1]));
		end[2] = f32(fadd_m(sz, &from[2]));
		float hit[3];
		BU->hit = (struct CollisionPlane *)collision_rayTrace(s, from, end, hit);
		if (BU->hit) {
			memcpy(end, hit, 12);
			if (*w2de8 > 0) {
				float dx = f32(FSUB(hit[0], from[0]));
				long double dy = FSUB(hit[1], from[1]), dz = FSUB(hit[2], from[2]);
				BU->life = f32(fdiv_m(x87_fsqrt((FMUL(dx, dx) + dz * dz) + dy * dy), w2de8));
			} else
				BU->life = 0.0f;
		} else if (*w2de8 > 0)
			BU->life = f32(fdiv_m(fld_m(range), w2de8));
		else
			BU->life = 0.0f;
		if (!(BU->life >= 0) || BU->life > *&k_10f)
			BU->life = 0.0f;
	} else {
		for (int k = 0; k < 3; k++)
			dir[k] = f32(FSUB(aim[k], o[k]));
		Vec3_normalize(dir);
		int target = rd->hitPlane;
		BITS(BU->hit) = target >= 0 ? (u32)ST->space.planes.records + target * 0xac : 0;
		memcpy(BU->impact, aim, 12);
		BU->life = 10.0f;   /* 10 */
	}
	BU->age = 0.0f;
	memcpy(BU->prev, o, 12);
	memcpy(BU->pos, o, 12);
	BU->moved = 0;
	float *vel = BU->vel;
	for (int k = 0; k < 3; k++)
		vel[k] = *w2de8 > 0 ? f32(fmul_m(fld_m(w2de8), &dir[k])) : f32(fsub_m(fld_m(BU->impact + k), BU->from + k));
	memcpy(BU->step, (const void *)ADDR(g_vecZero), 12);
	BU->hitActor = -1;
	BU->homeTimer = 0.0f;
	BU->homingTarget = homingTarget;
	if (w->guidance > 0 && homingTarget < 0 && BU->owner == ST->playerActor) {
		const float *at = BU->prev;
		float *point = BU->homingPoint;
		long double tx = FMUL(aim[0], k_200000f);
		float ty = f32(FMUL(aim[1], k_200000f)), tz = f32(FMUL(aim[2], k_200000f));
		point[0] = f32(fadd_m(tx, &at[0]));
		point[1] = f32(FADD(ty, at[1]));
		point[2] = f32(FADD(tz, at[2]));
	}
	BU->struck = 0;
	BU->trailCount = 0;
	if (quiet)
		return;
	u32 rec[13] = { ((u32)w->shotMode) + 10, ((u32)BU->owner) };
	memcpy(&rec[2], BU->prev, 12);
	memcpy(&rec[5], (const void *)OBJ(g_vecZero2), 12);
	rec[8] = BU->muzzle;   /* its matrixFrom */
	float size = f32(fld_m(&w->hitRange));
	memcpy(&rec[11], &size, 4);
	particle_spawn(s, rec);
	int sound = w->sound;
	if (sound < 0)
		return;
	if (BU->owner == ST->playerActor)
		sound_playVolume(sound, 100);
	else
		sound_play3D(sound, ST->cameraPos,
		                                                                                BU->prev, ST->viewDir, 0x47435000);
}
#undef K
#undef BU

/* ---- bullet_update: a bullet's frame ---- */

#define BU ((Bullet *)b)   /* the same by its fields (src/scene.fields) */
#define WI ((ActorItem *)w)   /* the same by its fields (src/scene.fields) */

/* an effect (particle_spawn's record r, 31 words, a ParticleDesc: kind, owner, a point, a direction (target), three
   words, the size, one more; the rest as the last effect left them) */
static void effect(u8 *s, u32 *r, u32 kind, u32 owner, const void *at, const void *dir, u32 x0, u32 x1, u32 x2, u32 size, u32 x3)
{
	r[0] = kind;
	r[1] = owner;
	memcpy(r + 2, at, 12);
	memcpy(r + 5, dir, 12);
	r[8] = x0;
	r[9] = x1;
	r[10] = x2;
	r[11] = size;
	r[12] = x3;
	particle_spawn(s, r);
}

/* the weapon's hit range (hitRange: the impact effect's size), as the original passes it through the FPU */
static u32 effect_size(const u8 *w)
{
	float v = (float)fld_m(&WI->hitRange);
	return BITS(v);
}

/* the inverse of the view gluLookAt makes from the bullet's last point (prev) to its point (pos) */
static void look_inverse(u8 *b, float *inv, int x_up)
{
	float *prev = BU->prev, *cur = BU->pos, mv[16];
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
		out[k] = f32(FADD(off[k], p[k]));
}

/* a beam (kind 7): its four long sides (trail.., the last point's corners, trail[1].. the point's) half the size off
   the line along the view's y (+-) and x (+-), each drawn as a textured strip (kind -1) with the bullet id's
   quarter of the texture (+0); the length kept (trailAge). The flying copy sums the length's squares in another order */
static void beam(u8 *s, u8 *b, const u8 *w, u32 *r, int flying)
{
	float *prev = BU->prev, *cur = BU->pos, inv[16], a[3];
	look_inverse(b, inv, 0);
	float half = f32(fld_m(&WI->hitRange)), minus;
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fadd_m(FMUL(half, inv[4 + k]), &k_0f), &k_0f));
	offset_point(BU->trail[0][0], a, prev);
	offset_point(BU->trail[1][0], a, cur);
	minus = f32(-fld_m(&WI->hitRange));
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fadd_m(FMUL(minus, inv[4 + k]), &k_0f), &k_0f));
	offset_point(BU->trail[0][1], a, prev);
	offset_point(BU->trail[1][1], a, cur);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(FMUL(half, inv[k]), &k_0f));
	offset_point(BU->trail[0][2], a, prev);
	offset_point(BU->trail[1][2], a, cur);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(FMUL(minus, inv[k]), &k_0f));
	offset_point(BU->trail[0][3], a, prev);
	offset_point(BU->trail[1][3], a, cur);
	long double dx = FSUB(cur[0], prev[0]), dy = FSUB(cur[1], prev[1]), dz = FSUB(cur[2], prev[2]);
	long double len = flying ? x87_fsqrt((dx * dx + dz * dz) + dy * dy) : x87_fsqrt((dz * dz + dy * dy) + dx * dx);
	BU->trailAge[0] = (float)len;
	float scale = f32(fmul_m(len, &k_0_00125f));   /* / 800 */
	u32 colour = (u32)ST->effectTextures[4];
	for (int k = 0; k < 4; k++) {
		int quarter = BU->id % 4;
		float v0, u;
		if (k & 1) {
			long double t = fmul_m((long double)(quarter << 5), &k_0_00390625f);   /* / 256 */
			v0 = f32(fadd_m(t, k_0_0625f));
			u = f32(fadd_m(t, &k_0_01f));
		} else {
			long double t = fmul_m((long double)((quarter + 1) << 5), &k_0_00390625f);
			v0 = f32(fsub_m(t, k_0_0625f));
			u = f32(fsub_m(t, &k_0_01f));
		}
		const u8 *side = (const u8 *)BU->trail + k * 0xc;   /* (corner k % 4 of section k / 4: the ring as one run) */
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
		memcpy(r + 25, side + sizeof BU->trail[0], 12);   /* (the next section's same corner) */
		memcpy(r + 28, side, 12);
		particle_spawn(s, r);
	}
}

/* a trail (kind 3): the ring of 20 cross-sections (trail: four corners each; trailCount counts them, trailAge their
   ages): this one half the size about the last point along the view's y and x (up is x for a vertical
   line), the next one collapsed onto the point. The flying copy keeps one product unrounded */
static void trail(u8 *b, const u8 *w, int flying)
{
	float *prev = BU->prev, *cur = BU->pos, inv[16], a[3];
	look_inverse(b, inv, !(prev[0] < cur[0]) && !(prev[0] > cur[0]) && !(prev[2] < cur[2]) && !(prev[2] > cur[2]));
	int i = BU->trailCount % 20;
	float (*ring)[3] = BU->trail[i];
	long double half = fld_m(&WI->hitRange);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[4 + k]));
	offset_point(ring[0], a, prev);
	half = fld_m(&WI->hitRange);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[k]));
	offset_point(ring[1], a, prev);
	half = -fld_m(&WI->hitRange);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fmul_m(half, &inv[4 + k]));
	offset_point(ring[2], a, prev);
	half = -fld_m(&WI->hitRange);
	float *last = ring[3];
	for (int k = 0; k < 2; k++)
		a[k] = f32(fmul_m(half, &inv[k]));
	last[0] = f32(FADD(a[0], prev[0]));
	last[1] = f32(FADD(a[1], prev[1]));
	if (flying)
		last[2] = f32(fadd_m(fmul_m(half, &inv[2]), &prev[2]));
	else {
		a[2] = f32(fmul_m(half, &inv[2]));
		last[2] = f32(FADD(a[2], prev[2]));
	}
	BITS(BU->trailAge[i]) = BITS(BU->age);
	i = ++BU->trailCount % 20;
	ring = BU->trail[i];
	for (int c = 0; c < 4; c++)
		memcpy(ring[c], cur, 12);
	BITS(BU->trailAge[i]) = BITS(BU->age);
}

/* the shot drawn by its kind (shotMode): a trail, a beam, or a particle of kind + 0x14 from the last point to the
   point (flagged for the camera's own first 0.03 s, cockpitActor) */
static void draw_shot(u8 *s, u8 *b, const u8 *w, u32 *r, int flying)
{
	int kind = WI->shotMode;
	if (kind == 3)
		trail(b, w, flying);
	else if (kind == 7)
		beam(s, b, w, r, flying);
	else {
		u32 flag = BU->owner == ST->cockpitActor && !(BU->age >= *&k_0_03f) ? 1 : 0;
		effect(s, r, kind + 0x14, flag, (u8 *)BU->prev, (u8 *)BU->pos, 0, 0, 0, effect_size(w), 0);
	}
}

/* the bullet hit actor hitActor: the damage when the actor is the local player's and alive (actors[].state), sparks and a
   flash (kind 8, the actor's 0x2000 flag) facing away from it, the hit sound, the local owner's hit beep, and the
   push (actors[].push: 10 times the weapon's push towards the actor) */
static void hit_actor(u8 *s, u8 *b, const u8 *w, u32 *r, int weapon)
{
	int t = BU->hitActor;
	if (ST->actors[t].controlledBy == ST->playerActor && ST->actors[t].state == 1)
		actor_takeDamage(s, BU->owner, t, WI->damageType, WI->damage, WI->shotMode, weapon);
	t = BU->hitActor;
	float dir[3];
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m(BU->pos + k), &ST->actors[t].nextPos[k]));
	Vec3_normalize(dir);
	effect(s, r, WI->shotMode + 0x1e, 0, (u8 *)BU->impact, dir, 0, 0, 0, effect_size(w), 0);
	effect(s, r, 8, ST->actors[BU->hitActor].stateFlags & 0x2000, (u8 *)BU->impact, dir, 0, 0, 0, 0, 0);
	if (WI->hitSound >= 0)
		sound_play3D(WI->hitSound, ST->cameraPos, (u8 *)BU->pos, ST->viewDir, 0x47435000);
	if (BU->owner == ST->playerActor)
		sound_playVolume(0xb, 100);
	if (WI->push > 0) {
		long double k = -fld_m(&WI->push);
		float x = f32(fmul_m(k, &dir[0])), y = f32(fmul_m(k, &dir[1]));
		long double z = fmul_m(k, &dir[2]);
		float *push = ST->actors[BU->hitActor].push;
		push[0] = f32(FMUL(x, k_10f));
		push[1] = f32(FMUL(y, k_10f));
		push[2] = f32(fmul_m(z, &k_10f));
	}
	BU->struck = 1;
}

/* ((M[a] * p[ia] + M[b] * p[ib]) + M[c] * p[ic]) + M[t], each product a matrix entry times a point's */
static float through(const float *M, const float *p, int a, int ia, int b, int ib, int c, int ic, int t)
{
	long double v = FMUL(M[a], p[ia]) + FMUL(M[b], p[ib]);
	return f32(fadd_m(v + FMUL(M[c], p[ic]), &M[t]));
}

/* the mark on the hit surface (kind + 0x28): its plane's axes from the triangle's first corner and the normal,
   the other two corners' coordinates in them (uv: the axes' lengths, 0, then two pairs) */
static void decal(u8 *s, u8 *b, const u8 *w, u32 *r, const u8 *h, const float *N, const float *P)
{
	const float *imp = BU->impact;
	float e[3], uv[6], c2, le;
	for (int k = 0; k < 3; k++)
		e[k] = f32(FSUB(P[k], imp[k]));
	long double c0 = FMUL(e[1], N[2]) - FMUL(e[2], N[1]);
	long double c1 = FMUL(N[0], e[2]) - FMUL(N[2], e[0]);
	c2 = f32(FMUL(N[1], e[0]) - FMUL(N[0], e[1]));
	le = f32(x87_fsqrt((FMUL(e[2], e[2]) + FMUL(e[1], e[1])) + FMUL(e[0], e[0])));
	long double lc = x87_fsqrt((FMUL(c2, c2) + c1 * c1) + c0 * c0);
	if (!(le < 0) && !(le > 0))
		le = 1.0f;
	if (!(lc < 0) && !(lc > 0))
		lc = fld_m(&k_1f);
	uv[0] = le;
	uv[1] = 0;
	for (int q = 1; q < 3; q++) {
		long double f0 = FSUB(P[q * 3], imp[0]), f1 = FSUB(P[q * 3 + 1], imp[1]), f2 = FSUB(P[q * 3 + 2], imp[2]);
		uv[q * 2] = f32(fdiv_m((fmul_m(f2, &e[2]) + fmul_m(f1, &e[1])) + fmul_m(f0, &e[0]), &le));
		uv[q * 2 + 1] = f32(((fmul_m(f2, &c2) + f1 * c1) + f0 * c0) / lc);
	}
	const int *obj = &((const CollisionPlane *)h)->unit->index;   /* (its unit's map object number) */
	if (obj) {
		const ShapePart *part = (const ShapePart *)ST->objects[*obj].model->parts + ((const CollisionPlane *)h)->part;
		float tri[9];
		for (int k = 0; k < 3; k++)
			memcpy(tri + k * 3, (const float *)part->vertices + ((const CollisionPlane *)h)->cornerIndices[k] * 3, 12);
		effect(s, r, WI->shotMode + 0x28, 0, imp, N, (u32)ST->objects[((const CollisionPlane *)h)->unit->index].matrix, (u32)tri, (u32)uv, 0, 0);
	} else
		effect(s, r, WI->shotMode + 0x28, 0, imp, N, 0, (u32)P, (u32)uv, effect_size(w), 0);
}

/* the surface the bullet hit (Bullet.hit, a CollisionPlane: its corners, normal, object):
   the corners and normal taken into the world through the object's matrix (relMatrix), the impact (kind + 0x1e), a
   mark unless the surface takes none (flag 0x10) or marks are off (0x83a9c8), the hit sound */
static void hit_surface(u8 *s, u8 *b, const u8 *w, u32 *r)
{
	const u8 *h = (*(const u8 * *)&BU->hit);
	if (!h)
		return;
	float N[3], P[9];
	const float *n = ((const CollisionPlane *)h)->normal, *p = &((const CollisionPlane *)h)->cornerPoints[0][0];
	const int *obj = &((const CollisionPlane *)h)->unit->index;   /* (its unit's map object number) */
	if (obj) {
		const float *M = ST->objects[*obj].relMatrix;
		N[0] = f32((FMUL(n[2], M[8]) + FMUL(n[1], M[4])) + FMUL(n[0], M[0]));
		N[1] = f32((FMUL(n[0], M[1]) + FMUL(n[2], M[9])) + FMUL(n[1], M[5]));
		N[2] = f32((FMUL(n[0], M[2]) + FMUL(n[2], M[10])) + FMUL(n[1], M[6]));
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
	effect(s, r, WI->shotMode + 0x1e, 0, (u8 *)BU->impact, N, 0, 0, 0, effect_size(w), 0);
	if (!(*(*(const u8 * *)&BU->hit) & 0x10) && g_highDetail == 1)
		decal(s, b, w, r, (*(const u8 * *)&BU->hit), N, P);
	if (WI->hitSound >= 0)
		sound_play3D(WI->hitSound, ST->cameraPos, (u8 *)BU->impact, ST->viewDir, 0x47435000);
	BU->struck = 1;
}

/* splash damage once the bullet hit (struck): every other live actor of the local player's (actors[].controlledBy) with health
   over 3 within the weapon's radius (splashRadius) of the point is hurt by up to the weapon's damage (by distance) and
   pushed (actors[].push) */
static void splash(u8 *s, u8 *b, const u8 *w)
{
	if (BU->struck != 1 || !(WI->splashRadius > 0))
		return;
	for (int j = 0; j < ST->actorCount; j++) {
		if (ST->actors[j].state != 1 || !(ST->actors[j].spawnAge > 3.0f) || ST->actors[j].controlledBy != ST->playerActor || BU->hitActor == j
		    || ST->actors[j].outOfPlay == 1)
			continue;
		float d[3];
		for (int k = 0; k < 3; k++)
			d[k] = f32(fsub_m(fld_m(&ST->actors[j].nextPos[k]), BU->pos + k));
		long double len = Vec3_normalize(d);
		if (len >= WI->splashRadius)
			continue;
		float f = f32(fsubr_m(fmul_m(fdiv_m(len, &WI->splashRadius), &k_0_5f), &k_1f));   /* 1 - len / r / 2 */
		int damage = ftol(fmul_m((long double)WI->damage, &f));
		actor_takeDamage(s, BU->owner, j, WI->damageType, damage, WI->shotMode, BU->weapon);
		if (WI->push > 0) {
			long double k = fld_m(&WI->push);
			float x = f32(fmul_m(k, &d[0])), y = f32(fmul_m(k, &d[1]));
			long double z = fmul_m(k, &d[2]);
			float x10 = f32(FMUL(x, k_10f)), y10 = f32(FMUL(y, k_10f));
			long double z10 = fmul_m(z, &k_10f);
			float *push = ST->actors[j].push;
			push[0] = f32(FMUL(f, x10));
			push[1] = f32(FMUL(y10, f));
			push[2] = f32(fmul_m(z10, &f));
		}
	}
}

/* homing: the velocity (vel) turned towards the target (actor homingTarget, else the point homingPoint) by at most the turn
   rate (guidance, tenths of a degree: the cosine table g_cosTable's index; x pi / 1800 in radians) about their cross product, at the weapon's speed (velocity;
   for kind 3 both by the bullet's age); again in 1/15 s (homeTimer) */
static void home(u8 *s, u8 *b, const u8 *w)
{
	float *prev = BU->prev, *vel = BU->vel, spd, rate, T[3];
	if (WI->shotMode != 3) {
		BITS(spd) = BITS(WI->velocity);
		BITS(rate) = BITS(WI->guidance);
	} else {
		long double x = fsub_m(FMUL(BU->age, k_4f), &k_1f);   /* 4 age - 1 */
		spd = f32(fmul_m(fadd_m(((x * x) * x) * x, &k_tenthsToDegrees), &WI->velocity));
		long double y = FADD(BU->age, k_1f);
		rate = f32(fdivr_m((y * y) * y, &WI->guidance));
	}
	int tg = BU->homingTarget;
	for (int k = 0; k < 3; k++)
		T[k] = f32(fsub_m(fld_m(tg >= 0 ? &ST->actors[tg].nextPos[k] : BU->homingPoint + k), &prev[k]));
	Vec3_normalize(T);
	Vec3_normalize(vel);
	long double dot = (FMUL(T[2], vel[2]) + FMUL(T[1], vel[1])) + FMUL(T[0], vel[0]);
	int deg = ftol(fld_m(&rate));
	if (fld_m(g_cosTable + deg) > dot) {
		float axis[3], rot[4], m[16];
		axis[0] = f32(FMUL(T[2], vel[1]) - FMUL(T[1], vel[2]));
		axis[1] = f32(FMUL(T[0], vel[2]) - FMUL(T[2], vel[0]));
		axis[2] = f32(FMUL(T[1], vel[0]) - FMUL(T[0], vel[1]));
		Vec3_normalize(axis);
		rot[0] = f32(FMUL(rate, k_0_001745329f));   /* in radians */
		for (int k = 0; k < 3; k++)
			rot[1 + k] = (float)fld_m(&axis[k]);
		Mat4_fromAxisAngle(m, rot);
		T[0] = f32((FMUL(m[8], vel[2]) + FMUL(m[4], vel[1])) + FMUL(m[0], vel[0]));
		T[1] = f32((FMUL(m[1], vel[0]) + FMUL(m[9], vel[2])) + FMUL(m[5], vel[1]));
		T[2] = f32((FMUL(m[2], vel[0]) + FMUL(m[10], vel[2])) + FMUL(m[6], vel[1]));
	}
	BU->homeTimer = 0.06666667f;   /* 1/15 */
	vel[0] = f32(FMUL(spd, T[0]));
	vel[1] = f32(FMUL(T[1], spd));
	vel[2] = f32(FMUL(T[2], spd));
}

/* a local player's bullet in flight: homing, the step by its velocity (none for a weapon of no speed: it ends at
   its point end at once, as does one whose life ends this frame unless it homes), the nearest actor the step
   passes within its radius plus the weapon's size (math_segmentSphere; the bullet then stops there), else for a
   homing weapon the world in the way (collision_rayTrace: the hit record hit and the life cut to it) */
static void fly_local(u8 *s, u8 *b, const u8 *w, const float *dt)
{
	float *prev = BU->prev, *cur = BU->pos, *vel = BU->vel, *step = BU->step;
	if (WI->guidance > 0 && WI->velocity > 0) {
		long double v = fsub_m(fld_m(&BU->homeTimer), dt);
		BU->homeTimer = (float)v;
		if (!(v > 0))
			home(s, b, w);
	}
	if (WI->velocity > 0) {
		for (int k = 0; k < 3; k++)
			step[k] = f32(fmul_m(fld_m(dt), &vel[k]));
		if (!(fadd_m(fld_m(dt), &BU->age) > BU->life) || WI->guidance > 0) {
			cur[0] = f32(FADD(step[0], prev[0]));
			cur[1] = f32(FADD(prev[1], step[1]));
			cur[2] = f32(FADD(prev[2], step[2]));
		} else
			memcpy(cur, BU->impact, 12);
	} else {
		memcpy(step, vel, 12);
		memcpy(cur, BU->impact, 12);
	}
	float dir[3], best, hit[3], t;
	memcpy(dir, step, 12);
	Vec3_normalize(dir);
	BITS(best) = 0x7f7fffff;
	for (int j = 0; j < ST->actorCount; j++) {
		if (ST->actors[j].state != 1 || !(ST->actors[j].spawnAge > 3.0f) || j == BU->owner || ST->actors[j].outOfPlay != 0)
			continue;
		float radius = f32(FADD(ST->actors[j].radius, WI->hitRange));
		if (math_segmentSphere(prev, cur, dir, ST->actors[j].nextPos, radius, hit, &t) == 1 && !(t >= best)) {
			BU->hitActor = j;
			memcpy(cur, hit, 12);
			memcpy(BU->impact, hit, 12);
			BITS(best) = BITS(t);
		}
	}
	if (BU->hitActor >= 0) {
		BU->hit = 0;
		BITS(BU->life) = BITS(BU->age);
	}
	if (WI->guidance > 0 && BU->hitActor < 0) {
		float h[3];
		int r = collision_rayTrace(s, prev, cur, h);
		BU->hit = (struct CollisionPlane *)r;
		if (r) {
			memcpy(BU->impact, h, 12);
			h[0] = f32(FSUB(h[0], prev[0]));
			long double dy = FSUB(h[1], prev[1]);
			h[1] = (float)dy;
			long double dz = FSUB(h[2], prev[2]);
			h[2] = (float)dz;
			long double len = x87_fsqrt((FMUL(h[0], h[0]) + dz * dz) + dy * dy);
			long double spd = x87_fsqrt((FMUL(vel[0], vel[0]) + FMUL(vel[1], vel[1])) + FMUL(vel[2], vel[2]));
			BU->life = f32(fadd_m(len / spd, &BU->age));
		}
	}
	BU->moved = 1;
}

/* 0x47a2d0 (thiscall on the scene): bullet slot's frame (0x4e8 bytes from bullets; its weapon's record 0x2e18
   bytes from actorItems). An actor it hit (hitActor) takes it first. In flight (age age up to its life life): the
   local player's (playerActor) bullets move and find their hits (fly_local), other players' follow the network's
   points (netPoint, or the last step again); it is drawn when it moved (moved), aged, and its owner told when it ends
   (actors[].sendNow). Afterwards: another player's bullet is drawn at its last point, then the surface it hit, the
   splash, and the slot freed (bullet_free) */
void THISCALL (bullet_update)(u8 *s, int slot, u32 dt_bits)
{
	const float *dt = (const float *)&dt_bits;   /* (only ever read from memory, as the original does) */
	u8 *b = (u8 *)&ST->bullets[slot];
	int weapon = BU->weapon;
	u8 *w = (u8 *)&ST->actorItems[weapon];
	u32 r[31];   /* particle_spawn's record, reused */
	float *prev = BU->prev, *cur = BU->pos, *step = BU->step;
	if (BU->hitActor >= 0)
		hit_actor(s, b, w, r, weapon);
	if (!(BU->age > BU->life)) {
		memcpy(prev, cur, 12);
		if (ST->actors[BU->owner].controlledBy == ST->playerActor)
			fly_local(s, b, w, dt);
		else if (BU->moved == 1) {
			memcpy(cur, BU->netPoint, 12);
			for (int k = 0; k < 3; k++)
				step[k] = f32(FSUB(cur[k], prev[k]));
			Vec3_normalize(step);
		} else
			for (int k = 0; k < 3; k++)
				cur[k] = f32(FADD(step[k], prev[k]));
		if (BU->moved == 1)
			draw_shot(s, b, w, r, 1);
		long double age = fadd_m(fld_m(dt), &BU->age);
		BU->age = (float)age;
		if (age > BU->life)
			ST->actors[BU->owner].sendNow = 1;
		BU->moved = 0;
		return;
	}
	if (ST->actors[BU->owner].controlledBy != ST->playerActor) {
		memcpy(cur, BU->netPoint, 12);
		for (int k = 0; k < 3; k++)
			step[k] = f32(FSUB(cur[k], prev[k]));
		draw_shot(s, b, w, r, 0);
	}
	hit_surface(s, b, w, r);
	splash(s, b, w);
	bullet_free(s, slot);
}
#undef BU
#undef WI
