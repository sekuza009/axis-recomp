/* actor_frame.c: an actor's frame: its weapon and parts, a bot's mind (target, path, aim, keys), the movement and
   collisions, the body's pose and matrices, firing, the lock-on warnings, stamina, footsteps and effects, death and
   its score, and the timers. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

#define K(address) ((const float *)RELOC(address))
#define AI(offset) GAME_VAR(int, a + (offset))   /* the actor's fields */
#define AC ((Player *)a)   /* the same by its fields (src/scene.fields) */
#define AF(offset) GAME_VAR(float, a + (offset))
#define AC ((Player *)a)   /* the same by its fields (src/scene.fields) */
#define AU(offset) GAME_VAR(u32, a + (offset))
#define AC ((Player *)a)   /* the same by its fields (src/scene.fields) */
#define AU8(offset) GAME_VAR(u8, a + (offset))
#define AC ((Player *)a)   /* the same by its fields (src/scene.fields) */
#define OI(j, offset) GAME_VAR(int, s + (offset) + (j) * 0x8888)   /* actor j's, by their stage offsets */
#define OF(j, offset) GAME_VAR(float, s + (offset) + (j) * 0x8888)
/* point k (20 bytes) of path r: the paths' records (28 bytes at +0xe3b03c) start with their points' address */
#define PATH_POINT(r, k) ((const float *)(uintptr_t)(GAME_VAR(u32, s + ((r) + 0x821b9) * 0x1c) + (k) * 20))



static u32 rand_below(u32 n)
{
	u32 r = GAME_VAR(u32, OBJ(g_randTable) + (g_randPos & 0xfff) * 4) % n;
	g_randPos++;
	return r;
}

/* the view (+0x1e0 pitch, +0x1e4 heading, tenths of a degree) at point p */
static void aim_at(u8 *a, const float *p)
{
	float d[3];
	for (int c = 0; c < 3; c++)
		d[c] = f32(fsub_m(fld_m(&p[c]), &AC->pos[c]));
	long double x = fld_m(&d[0]), z = fld_m(&d[2]);
	AF(0x1e0) = f32(fmul_m(x87_fpatan(-fld_m(&d[1]), x87_fsqrt(x * x + z * z)), K(0x4a9738)));
	AF(0x1e4) = f32(fmul_m(x87_fpatan(fld_m(&d[0]), fld_m(&d[2])), K(0x4a9738)));
}

/* a key-driven speed towards top (key pos) or bottom (key neg) by at most step, else back to 0 */
static void key_axis(float *v, int pos, int neg, float top, float bottom, float step)
{
	if (pos == 1) {
		long double d = fsub_m(fld_m(v), &top);
		if (!(d >= -fld_m(&step)))
			*v = f32(fadd_m(fld_m(&step), v));
		else if (d > step)
			*v = f32(fsub_m(fld_m(v), &step));
		else
			*v = top;
	}
	if (neg == 1) {
		long double d = fsub_m(fld_m(v), &bottom);
		if (!(d >= -fld_m(&step)))
			*v = f32(fadd_m(fld_m(&step), v));
		else if (d > step)
			*v = f32(fsub_m(fld_m(v), &step));
		else
			*v = bottom;
	}
	if (pos == 0 && neg == 0) {
		if (-fld_m(&step) > *v)
			*v = f32(fadd_m(fld_m(&step), v));
		else if (*v > step)
			*v = f32(fsub_m(fld_m(v), &step));
		else
			*v = 0;
	}
}

/* up to 1 while on, down to 0 while off */
static void key_ramp(float *v, int on, float step)
{
	if (on) {
		long double x = fadd_m(fld_m(&step), v);
		*v = (float)x;
		if (x > 1.0L)
			*v = 1.0f;
	} else {
		long double x = fsub_m(fld_m(v), &step);
		*v = (float)x;
		if (!(x >= 0))
			*v = 0;
	}
}

/* v rounded, held within -450..450 (tenths of a degree) */
static void clamp450(float *out, long double v)
{
	*out = (float)v;
	if (!(v >= -450.0L))
		BITS(*out) = 0xc3e10000;
	else if (v > 450.0L)
		BITS(*out) = 0x43e10000;
}

/* a part's joint matrix: the model's matrix block (*base) at the joint index for this pose */
static const float *part_matrix(u8 *base, u8 *joints, int pose)
{
	return (const float *)(uintptr_t)(GAME_VAR(u32, base) + GAME_VAR(int, joints + pose * 4) * 100 + 0xc);
}

/* the local player's weapon at its grip (negated), drawn back by 600 while it comes up (or out, for the sixth) */
static void hold(float *grip, const u8 *at, int out, const float *raise)
{
	const float *o = (const float *)RELOC(at);
	float x = f32(-fld_m(&o[0])), y = f32(-fld_m(&o[1])), z = f32(-fld_m(&o[2]));
	long double d = fmul_m(fsub_m(fld_m(K(0x4a9424)), raise), K(0x4a94ac));
	grip[0] = f32(out ? fadd_m(d, &x) : fsubr_m(d, &x));
	grip[1] = y;
	grip[2] = z;
	glTranslatef_bits(BITS(grip[0]), BITS(y), BITS(z));
}

/* the arms' or legs' emitters: a puff at each joint (+0x80 set: only while leaning, +0x178 > 0) */
static void emit(u8 *s, u8 *a, const int *joint, const int *count, const u8 *mx, const u8 *legs, const float *v28, u32 *fx)
{
	for (int k = 0; k < *count; k++) {
		if (joint[k + 0x20] == 1 && !(AF(0x178) > 0))
			continue;
		u32 r = GAME_VAR(u32, OBJ(g_randTable) + (g_randPos & 0xfff) * 4) & 7;
		g_randPos++;
		u8 *m = (u8 *)(uintptr_t)GAME_VAR(u32, mx) + joint[k] * 100;
		fx[0] = GAME_VAR(u32, legs + 0x17fc) + 5;
		fx[1] = r;
		memcpy(fx + 2, m + 0x58, 12);
		memcpy(fx + 5, v28, 12);   /* scale, alpha, and whatever the third word last held */
		fx[8] = (u32)(uintptr_t)(m + 0xc);
		fx[9] = fx[10] = fx[11] = fx[12] = 0;
		particle_spawn(s, fx);
	}
}

#define stage_print(...) GAME_FN(stage_printText, 0x473450, int, void *, const char *, ...)(__VA_ARGS__)
#define FRAG_POINTS(level) GAME_VAR(int, 0x4b4314 + (level) * 4)   /* a kill's points by the victim's level */

/* the killer's points and level (the level shown for the local team only) */
static void award(u8 *s, int k, int frags, int points)
{
	ST->actors[k].kills += frags;
	ST->actors[k].score += points;
	if (ST->actors[k].pilot == ST->playerActor)
		ST->actors[k].emblem = actor_levelFromValue(ST->actors[k].score);
}

/* armour gone: the burst, the debris, the score */
static void actor_dies(u8 *s, u8 *a, int i, u32 *fx, float *v28)
{
	memset(fx, 0, 13 * 4);
	fx[0] = 3;
	memcpy(a + 0x4e0, a + 0x154, 12);
	memcpy(fx + 2, a + 0x154, 12);
	memcpy(fx + 5, a + 0x180, 12);
	particle_spawn(s, fx);
	for (int n = 0; n < 20; n++) {
		v28[0] = v28[1] = 0;
		BITS(v28[2]) = 0x459c4000;   /* 5000 */
		Vec3_rotateAxis(v28, 1, (int)rand_below(3600));
		Vec3_rotateAxis(v28, 2, (int)rand_below(3600));
		fx[1] = ((u32)AC->player);
		fx[0] = 9;
		memcpy(fx + 2, a + 0x154, 12);
		fx[8] = fx[9] = 0;
		memcpy(fx + 5, v28, 12);
		fx[10] = fx[11] = fx[12] = 0;
		particle_spawn(s, fx);
	}
	int local = ST->playerActor;
	if (i == local && AC->lastAttacker != i)
		sound_playVolume(0xd, 0x64);
	AC->state = 2;
	AI(0x150) = 0;
	GAME_VAR(int, s + 0x202e8ec) = 1;
	int k = AC->lastAttacker;
	if (ST->freeForAll == 1) {   /* every one for themselves */
		if (k != i) {
			int frags, points;
			if (AC->markSolo == 1) {   /* the marked one: five times */
				frags = 5;
				points = ST->halfPoints == 1 ? FRAG_POINTS(AC->emblem) * 5 / 2 : FRAG_POINTS(AC->emblem) * 5;
			} else {
				frags = 1;
				points = FRAG_POINTS(AC->emblem);
			}
			award(s, k, frags, points);
			if (AC->lastAttacker == ST->playerActor) {
				if (AC->markSolo == 1) {
					if (ST->showExp == 1)
						stage_print(s, (const char *)STR(0x4b44f8, "YOU FRAGED KING %s, +1(x%d) FRAGS +%d..."), 5, a + 0x98, points, 5);
					else
						stage_print(s, (const char *)STR(0x4b44d4, "YOU FRAGED KING %s, +1(x%d) FRAGS"), a + 0x98, 5);
					GAME_VAR(int, s + 0x20fce4c) = -1;
				} else if (ST->showExp == 1)
					stage_print(s, (const char *)STR(0x4b44c4, "+1 FRAG +%d EXP"), points);
				else
					stage_print(s, (const char *)STR(0x4b44bc, "+1 FRAG"));
			}
		} else {
			AC->kills--;
			stage_print(s, (const char *)STR(0x4b44b4, "-1 FRAG"));
		}
	} else if (GAME_VAR(int, s + 0x20f3ad8) == 1) {   /* teams, the leader down: each of the other team gets the team's worth */
		if (AC->markTeam == 1) {
			int n = 0, sum = 0, count = ST->actorCount;
			for (int j = 0; j < count; j++)
				if (ST->actors[j].team == AC->team) {
					n++;
					sum += FRAG_POINTS(ST->actors[j].emblem);
				}
			for (int j = 0; j < ST->actorCount; j++)
				if (ST->actors[j].team >= 0 && ST->actors[j].team != AC->team)
					award(s, j, n, sum);
			int lt = ST->actors[ST->playerActor].team;
			if (lt >= 0 && lt != AC->team) {
				if (ST->showExp == 1)
					stage_print(s, (const char *)STR(0x4b447c, "YOU FRAGED COMMANDER %s, +1(x%d) FRAG..."), a + 0x98, n, sum);
				else
					stage_print(s, (const char *)STR(0x4b4450, "YOU FRAGED COMMANDER %s, +1(x%d) FRAG(S)"), a + 0x98, n);
			} else if (lt == AC->team)
				stage_print(s, (const char *)STR(0x4b442c, "YOUR COMMANDER %s HAS BEEN KILLED!"), a + 0x98);
			if (AC->team == 0)
				ST->frags[1] += n;
			else
				ST->frags[0] += n;
			GAME_VAR(int, s + 0x20fce50 + AC->team * 4) = -1;
		}
	} else if (k != i) {   /* teams */
		int lv = AC->emblem;
		int points = ST->halfPoints == 1 ? FRAG_POINTS(lv) / 2 : FRAG_POINTS(lv);
		if (ST->actors[k].emblem > lv + 3)   /* half for a much weaker one */
			points /= 2;
		award(s, k, 1, points);
		if (AC->lastAttacker == ST->playerActor) {
			if (ST->showExp == 1)
				stage_print(s, (const char *)STR(0x4b44c4, "+1 FRAG +%d EXP"), points);
			else
				stage_print(s, (const char *)STR(0x4b44bc, "+1 FRAG"));
		}
		int t = ST->actors[AC->lastAttacker].team;
		if (t >= 0)
			ST->frags[t]++;
	} else {
		AC->kills--;
		if (AC->lastAttacker == ST->playerActor)
			stage_print(s, (const char *)STR(0x4b44b4, "-1 FRAG"));
		if (GAME_VAR(int, s + 0x20f3abc) == 1)
			ST->frags[AC->team]--;
	}
	if (AC->lastAttacker != i)
		AC->deaths++;
	GAME_VAR(int, s + 0x202ea80 + i * 4) = 0;
	AI(0x8868) = 1;
	GAME_VAR(int, s + 0x202e8e8) = i;
}

/* a timer down to 0 */
static void countdown(float *t, const float *dt)
{
	if (*t > 0) {
		long double v = fsub_m(fld_m(t), dt);
		*t = (float)v;
		if (!(v >= 0))
			*t = 0;
	}
}

/* 0x4580b0: actor i's frame (dt the frame time's bits) */
void THISCALL (actor_processFrame)(u8 *s, int i, u32 dt_bits)
{
	const float *dt = (const float *)&dt_bits;
	/* the original's stack buffers that outlive their uses, or that a callee may leave unwritten */
	float v28[3], dir[3], slide[3], hit[3], hit_t[3], mv_pos[3], mv_dist[3], mv_plane[4], left, grip[3];
	float m0d0[16], m18c[16], m1e0[16], m230[16], m270[16], shot_at[3], shot_dir[3];
	u32 fx[13];
	u8 *a = s + 0x1cd93a8 + i * 0x8888;
	u8 *player = s + 0x1561b68 + AC->player * 0x47fd2;
	if (AF(0x120) > AF(0x124)) {   /* the armour gone */
		actor_deactivate((Stage *)s, i);
		if (ST->selectedActor == i)
			ST->selectedActor = -1;
		return;
	}
	if (AC->pilot != ST->playerActor || AC->bot != 0)
		actor_clearInput(s, i);
	u8 *head = s + 0x13eb004 + GAME_VAR(int, player + 0x310) * 0xabc;
	u8 *body = s + 0x140c8c0 + GAME_VAR(int, player + 0x314) * 0x1300;
	u8 *arms = s + 0x1447ec4 + GAME_VAR(int, player + 0x318) * 0x13f4;
	u8 *legs = s + 0x1486470 + GAME_VAR(int, player + 0x31c) * 0x1820;
	if (AI(0x484) != AI(0x488)) {
		actor_updateHead(s, i);
		actor_updateBody(s, i);
		actor_updateArms(s, i);
		actor_updateLegs(s, i);
		actor_updateBooster(s, i);
		AI(0x488) = AI(0x484);
	}
	int item = GAME_VAR(int, player + 0x320 + AC->gaugeIcon * 4);
	u8 *weapon = item >= 0 ? s + 0x14d1ab4 + item * 0x2e18 : NULL;
	if (AC->pilot == ST->playerActor && weapon && AC->ammo[((ActorInfo *)weapon)->ammoSlot] < ((ActorInfo *)weapon)->ammoPerShot
	    && !(AF(0x490) < 1.0f)) {   /* out of ammunition: the next weapon */
		actor_nextWeapon(s, i);
		weapon = s + 0x14d1ab4 + GAME_VAR(int, player + 0x320 + AC->gaugeIcon * 4) * 0x2e18;
	}
	if (AC->inView >= 0)
		actor_selectWeapon((Stage *)s, i, AC->inView);
	if (AC->inPrevWeapon == 1)
		actor_prevWeapon(s, i);
	if (AC->inNextWeapon == 1)
		actor_nextWeapon(s, i);
	if (i == ST->selectedActor) {
		if (AI(0x49c) != 0) {
			AI(0x49c) = 0;
			actor_updatePart(s, i, AC->gaugeIcon, 0);
		}
	} else if (AI(0x49c) != AI(0x484) + 1) {
		AI(0x49c) = AI(0x484) + 1;
		actor_updatePart(s, i, AI(0x144), AI(0x49c));
		actor_updatePart(s, i, 4, AI(0x49c));
		actor_updatePart(s, i, 5, AI(0x49c));
	}
	if (AC->pilot != ST->playerActor && AC->weaponLowering == 0 && AI(0x498) != AC->gaugeIcon) {
		AI(0x498) = AC->gaugeIcon;
		actor_updatePart(s, i, AC->gaugeIcon, AI(0x49c));
	}
	u8 *model = AC->gaugeIcon == 4 ? a + 0x587c : AC->gaugeIcon == 5 ? a + 0x701c : a + 0x40dc;
	memcpy(a + 0x154, a + (AC->state == 1 ? 0x180 : 0x4e0), 12);
	memcpy(a + 0x160, a + 0x18c, 32);
	if (AC->pilot == ST->playerActor) {   /* (to chunk N: the local team's actors) */
		if (ST->freeForAll == 1) {
			if (AC->markSolo == 1)
				AU(0x3f4) = AU(0x3fc) = 0x447a0000;   /* 1000 */
			else {
				if (AF(0x3f4) > *K(0x4a940c))
					AI(0x3f4) = 0;
				if (AF(0x3fc) > *K(0x4a940c))
					AI(0x3fc) = 0;
			}
		}
		AI(0x87f4) = 0;
		if (AC->bot != 0) {
			if (AC->armor < ftol(fmul_m((long double)AC->armorMax, K(0x4a94fc))))   /* under 0.3 of its armour */
				AI(0x87f4) = 1;
			ActorInfo *w0 = (ActorInfo *)(s + 0x14d1ab4 + GAME_VAR(int, player + 0x320) * 0x2e18);
			if (AC->ammo[w0->ammoSlot] < w0->ammoPerShot && GAME_VAR(int, player + 0x330) >= 0) {
				u8 *w1 = s + 0x14d1ab4 + GAME_VAR(int, player + 0x330) * 0x2e18;
				if (AC->ammo[((ActorInfo *)w1)->ammoSlot] < ((ActorInfo *)w1)->ammoPerShot)
					AU8(0x87f4) |= 2;   /* both weapons empty */
			}
		}
		/* a bullet of another team aimed at it */
		int aimed = 0;
		for (int k = 0; k < GAME_VAR(int, s + 0x20a99b4); k++) {
			u8 *b = s + 0x202ef34 + k * 0x4e8;
			if (GAME_VAR(int, b + 0xbc) != i || ST->actors[GAME_VAR(int, b + 0xc)].pilot == ST->playerActor)
				continue;
			aimed = 1;
			if (AC->alert == 0 && AC->bot != 0 && AC->botTarget < 0) {
				int t = ST->bullets[k].owner;
				if (ST->actors[t].team != AC->team && ST->actors[t].state == 1 && (!(ST->actors[t].timerFlags & 0x200) || OI(t, 0x1cd93b0) < AI(8))) {
					AC->botTarget = t;
					AU(0x8858) = 0x41280000;   /* 10.5 */
					actor_pickRandomWeapon(s, i);
				}
			}
			break;
		}
		AC->alert = aimed;
		if (i == ST->playerActor) {   /* the warning beep */
			if (aimed == 1) {
				long double v = fsub_m(fld_m(&AF(0x8884)), dt);
				AF(0x8884) = (float)v;
				if (!(v >= 0)) {
					sound_playVolume(0x11, 100);
					AU(0x8884) = 0x3f000000;
				}
			} else
				AI(0x8884) = 0;
		}
		if (AC->botTarget >= 0 && ST->actors[AC->botTarget].state != 1) {
			AC->botTarget = -1;
			AI(0x8858) = 0;
		}
		if (AC->bot != 0) {   /* a bot: its target */
			long double v = fsub_m(fld_m(&AF(0x8824)), dt);
			AF(0x8824) = (float)v;
			int k = AC->lastAttacker;
			if (AC->hitFlash > 0 && k != i && ST->actors[k].team != AC->team && ST->actors[k].state == 1 && AC->botTarget != k
			    && (!(ST->actors[k].timerFlags & 0x200) || OI(k, 0x1cd93b0) < AI(8))) {   /* the one who hit it */
				AC->botTarget = k;
				AU(0x8858) = 0x41280000;
				actor_pickRandomWeapon(s, i);
			} else if (!(v > 0) && !(AU8(0x87f4) & 2)) {
				if (AC->botTarget < 0) {   /* the first other team's actor in sight within its range (+0) */
					for (int j = 0; j < ST->actorCount; j++) {
						if (j == i || ST->actors[j].state != 1 || ST->actors[j].team == AC->team || ((ST->actors[j].timerFlags & 0x200) && OI(j, 0x1cd93b0) >= AI(8)))
							continue;
						float d[3];
						const float *at = &ST->actors[j].pos[0];
						for (int c = 0; c < 3; c++)
							d[c] = f32(fsub_m(fld_m(&at[c]), &AC->pos[c]));
						memcpy(v28, d, 12);
						long double dist = fmul_m(fld_m(&d[0]), &d[0]) + fmul_m(fld_m(&d[2]), &d[2]);
						dist = dist + fmul_m(fld_m(&d[1]), &d[1]);
						if (!(dist > AC->radiusSq) && collision_rayTrace(s, &AF(0x154), at, v28) == 0) {
							AC->botTarget = j;
							break;
						}
					}
					if (AC->botTarget >= 0)
						actor_pickRandomWeapon(s, i);
				} else {
					int t = AC->botTarget;
					if (collision_rayTrace(s, &AF(0x154), &ST->actors[t].pos[0], v28) != 0
					    || ((ST->actors[AC->botTarget].timerFlags & 0x200) && OI(AC->botTarget, 0x1cd93b0) >= AI(8))) {   /* lost from sight */
						if (!(AF(0x8858) > 0))
							AC->botTarget = -1;
						else
							for (int j = 0; j < ST->actorCount; j++) {
								if (j == i || ST->actors[j].state != 1 || ST->actors[j].team == AC->team
								    || ((ST->actors[j].timerFlags & 0x200) && OI(j, 0x1cd93b0) >= AI(8)))
									continue;
								if (collision_rayTrace(s, &AF(0x154), &ST->actors[j].pos[0], v28) == 0) {
									AC->botTarget = j;
									actor_pickRandomWeapon(s, i);
									break;
								}
							}
					}
				}
				AU(0x8824) = 0x3f000000;   /* 0.5 */
			}
			if (AC->botTarget >= 0 && GAME_VAR(int, s + 0x20fcd48) == 0) {   /* fire in bursts */
				v = fsub_m(fld_m(&AF(0x8828)), dt);
				AF(0x8828) = (float)v;
				if (!(v > 0)) {
					if (AF(0x882c) > 0) {
						AC->inFire = 1;
						AF(0x882c) = f32(fsub_m(fld_m(&AF(0x882c)), dt));
					} else {
						AU(0x8828) = AC->spawnTail[3];
						AU(0x882c) = AC->spawnTail[4];
					}
				}
			}
		}
		/* the path: stuck (moved under 500 in a second) */
		AF(0x886c) = f32(fsub_m(fld_m(&AF(0x886c)), dt));
		for (int c = 0; c < 3; c++)
			AF(0x8874 + c * 4) = f32(fadd_m(fld_m(&AF(0x384 + c * 4)), &AF(0x8874 + c * 4)));
		if (!(AF(0x886c) > 0)) {
			if (AC->target1 >= 0) {
				long double x = fld_m(&AF(0x8874)), y = fld_m(&AF(0x8878)), z = fld_m(&AF(0x887c));
				if (!((x * x + y * y) + z * z >= *K(0x4a9740))) {
					AI(0x8870) = AC->target1;
					AC->target1 = -1;
				}
			}
			AU(0x886c) = 0x3f800000;
			memcpy(a + 0x8874, (const void *)ADDR(g_vecZero), 12);
		}
		if (AC->bot == 1 && AC->target1 < 0 && (AC->botTarget < 0 || (AU8(0x87f4) & 3))) {
			actor_checkLineOfSight(s, i);
			if (AU8(0x87f4) & 2)
				AC->botTarget = -1;
		}
		if (AI(0x8810) >= 0 && ST->actors[AI(0x8810)].state != 1)
			AI(0x8810) = -1;
		if (AC->followTarget >= 0 && ST->actors[AC->followTarget].state != 1)
			AC->followTarget = -1;
		if (AC->target1 >= 0) {   /* the scripted path (+0x87f8, point +0x87fc): its command when within 1000 */
			const float *pt = PATH_POINT(AC->target1, AC->target2);
			float d[3];
			for (int c = 0; c < 3; c++)
				d[c] = f32(fsub_m(fld_m(&pt[c]), &AC->pos[c]));
			memcpy(v28, d, 12);
			long double dist = fmul_m(fld_m(&d[0]), &d[0]) + fmul_m(fld_m(&d[2]), &d[2]);
			if (!(dist + fmul_m(fld_m(&d[1]), &d[1]) >= *K(0x4a94ec))) {
				script_processCommandBy(s, i, AC->target1, AC->target2);
				int at = AC->target2;
				if (AI(0x8800) == 0) {   /* forwards, or backwards */
					if (at < GAME_VAR(int, s + 0xe3b038 + AC->target1 * 0x1c) - 1)
						AC->target2 = at + 1;
					else
						AC->target1 = AC->target2 = -1;
				} else if (AC->target2 > 0)
					AC->target2 = AC->target2 - 1;
				else
					AC->target1 = AC->target2 = -1;
			}
		}
		if (AC->bot == 1 && AC->target1 >= 0 && AC->botTarget >= 0 && !(AU8(0x87f4) & 1))
			AC->target1 = -1;
		if (AF(0x8804) > 0)
			AF(0x8804) = f32(fsub_m(fld_m(&AF(0x8804)), dt));
		if (AI(0x8808) >= 0 && GAME_VAR(int, s + 0xe3c618 + AI(0x8808) * 4) == 1)
			AI(0x8808) = -1;
		if (AC->bot != 0 && !(AF(0x8804) > 0) && AI(0x8808) < 0) {   /* a bot: where it goes (+0x1d4) and looks */
			if (AC->followTarget >= 0) {   /* the one it follows: towards it while over 3000 away */
				const float *at = &ST->actors[AC->followTarget].pos[0];
				float d[3];
				for (int c = 0; c < 3; c++)
					d[c] = f32(fsub_m(fld_m(&at[c]), &AC->pos[c]));
				memcpy(v28, d, 12);
				long double dist = fmul_m(fld_m(&d[0]), &d[0]) + fmul_m(fld_m(&d[2]), &d[2]);
				memcpy(a + 0x1d4, dist + fmul_m(fld_m(&d[1]), &d[1]) > *K(0x4a973c) ? (const void *)RELOC(at) : (const void *)(a + 0x154), 12);
			} else if (AC->target1 >= 0) {   /* its path's point while over 1000 away */
				const float *pt = PATH_POINT(AC->target1, AC->target2);
				float d[3];
				for (int c = 0; c < 3; c++)
					d[c] = f32(fsub_m(fld_m(&pt[c]), &AC->pos[c]));
				memcpy(v28, d, 12);
				long double dist = fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1]);
				memcpy(a + 0x1d4, dist + fmul_m(fld_m(&d[0]), &d[0]) > *K(0x4a94ec) ? (const void *)PATH_POINT(AC->target1, AC->target2) : (const void *)(a + 0x154), 12);
			} else if (AC->botTarget >= 0) {   /* about its target: sideways by a random amount, now and then */
				long double v = fsub_m(fld_m(&AF(0x8830)), dt);
				AF(0x8830) = (float)v;
				if (!(v > 0)) {
					int t = AC->botTarget;
					float d[3], tmp[3];
					for (int c = 0; c < 3; c++)
						tmp[c] = f32(fsub_m(fld_m(&AC->pos[c]), &OF(t, 0x1cd94fc + c * 4)));
					memcpy(d, tmp, 12);
					Vec3_normalize(d);
					d[0] = f32(fmul_m(fld_m(&d[0]), &AF(0x8c)));
					d[1] = 0;
					long double z = fmul_m(fld_m(&d[2]), &AF(0x8c));
					d[2] = (float)z;
					v28[0] = f32(-fmul_m(z, &g_vecUnitY[1]));   /* (d x the unit Y vector) */
					v28[1] = f32(fmul_m(fld_m(&d[2]), &g_vecUnitY[0]) - fmul_m(fld_m(&d[0]), &g_vecUnitY[2]));
					v28[2] = f32(fmul_m(fld_m(&d[0]), &g_vecUnitY[1]));
					Vec3_normalize(v28);
					int n = ftol(fld_m(&AC->spawn7c)) * 2;
					int r = n > 0 ? (int)rand_below(n) : 0;
					long double o = fsub_m((long double)r, &AC->spawn7c);
					v28[0] = f32(fmul_m(o, &v28[0]));
					v28[2] = f32(fmul_m(o, &v28[2]));
					AF(0x1d4) = f32(fadd_m(fadd_m(fld_m(&v28[0]), &ST->actors[AC->botTarget].pos[0]), &d[0]));
					AU(0x8830) = AC->spawnTail[0];
					AF(0x1dc) = f32(fadd_m(fadd_m(fld_m(&v28[2]), &ST->actors[AC->botTarget].pos[2]), &d[2]));
				}
				v = fsub_m(fld_m(&AF(0x8834)), dt);
				AF(0x8834) = (float)v;
				if (!(v > 0)) {   /* and up or down */
					int n = ftol(fld_m(&AC->spawn80)) * 2;
					int r = n > 0 ? (int)rand_below(n) : 0;
					AU(0x8834) = AC->spawnTail[1];
					AF(0x1d8) = f32(fsub_m(fadd_m((long double)r, &AF(0x158)), &AC->spawn80));
				}
			}
			/* the view (+0x1e0 pitch, +0x1e4 heading): at what it attends to, or a random look every 2 s */
			if (AI(0x8810) >= 0)
				aim_at(a, &ST->actors[AI(0x8810)].pos[0]);
			else if (AI(0x8814) >= 0)
				aim_at(a, PATH_POINT(AI(0x8814), AI(0x8818)));
			else if (AC->followTarget >= 0)
				aim_at(a, &ST->actors[AC->followTarget].pos[0]);
			else if (AC->botTarget >= 0)
				aim_at(a, &ST->actors[AC->botTarget].pos[0]);
			else if (AC->target1 >= 0)
				aim_at(a, PATH_POINT(AC->target1, AC->target2));
			else {
				long double v = fsub_m(fld_m(&AF(0x8844)), dt);
				AF(0x8844) = (float)v;
				if (!(v > 0)) {
					AF(0x1e0) = (float)(int)(rand_below(900) - 450);
					AU(0x8844) = 0x40000000;   /* 2 */
					AF(0x1e4) = (float)(int)rand_below(3600);
				}
			}
			/* the movement keys towards the goal, in the actor's own frame: forward / back / right / left (+0x44c..),
			   or up / down (+0x470 with forward or back) when that is the larger way, beyond 500 */
			for (int c = 0; c < 3; c++)
				v28[c] = f32(fsub_m(fld_m(&AF(0x1d4 + c * 4)), &AC->pos[c]));
			Vec3_rotateAxis(v28, 2, -ftol(fld_m(&AF(0x164))));
			Vec3_rotateAxis(v28, 1, -ftol(fld_m(&AC->pitch)));
			long double len = x87_fsqrt((fmul_m(fld_m(&v28[0]), &v28[0]) + fmul_m(fld_m(&v28[2]), &v28[2])) + fmul_m(fld_m(&v28[1]), &v28[1]));
			if (len > 500.0f) {
				long double G = fld_m(&v28[0]), Y = fld_m(&v28[1]), Z = fld_m(&v28[2]);
				long double ay = !(Y >= 0) ? -Y : Y;
				int vert = 0;
				if (Z > (!(G >= 0) ? -G : G)) {
					if (Z > ay && Z > 500.0f)
						AC->inForward = 1;
					else
						vert = 1;
				} else if (-Z > (!(G >= 0) ? -G : G)) {
					if (-Z > ay && -Z > 500.0f)
						AC->inBackward = 1;
					else
						vert = 1;
				} else if (G > 0) {
					if (G > ay && G > 500.0f)
						AC->inStepLeft = 1;
					else
						vert = 1;
				} else if (-G > ay && -G > 500.0f)
					AC->inStepRight = 1;
				else
					vert = 1;
				if (vert) {
					if (Y > 500.0f)
						AC->inAltitude = AC->inForward = 1;
					else if (-Y > 500.0f)
						AC->inAltitude = AC->inBackward = 1;
				}
			}
			/* the turns towards the view, at most the turn rate (+0x6c) a second */
			float rate = f32(fmul_m(fld_m(dt), &AC->accel));
			for (int c = 0; c < 2; c++) {
				long double r = angle_turn(AU(0x160 + c * 4), AU(0x1e0 + c * 4));
				float rr = (float)r;
				AF(0x464 + c * 4) = rr;
				if (r > rate)
					AU(0x464 + c * 4) = BITS(rate);
				else if (!(rr >= -fld_m(&rate)))
					AF(0x464 + c * 4) = (float)-fld_m(&rate);
			}
		}
		if (AC->bot == 1)
			AC->inBooster = 1;
	}
	switch (AI(0x4d0)) {   /* a pending order */
	case 0:
		(*(u32 *)&AC->armor) = ((u32)AC->armorMax);
		(*(u32 *)&AC->shield) = ((u32)AC->shieldMax);
		break;
	case 1:
		memcpy(a + 0x130, a + 0x28, 16);
		break;
	case 2:
		AI(0x4d4) = 1;
		break;
	case 3:
		AI(0x4d4) = 0;
		break;
	case 4:
		AC->deaths++;
		bullet_playImpactSound(s, i, i, 1, AC->armor, 0, -1);
		break;
	}
	AI(0x4d0) = -1;
	float speed = f32(fmul_m(fld_m(dt), &AF(0x38)));
	if (AC->inBooster == 1)
		speed = f32(fld_m(&speed) + fld_m(&speed));
	float accel = f32(fmul_m(fld_m(dt), &AF(0x3c)));
	float want[3];   /* the wanted velocity from the keys (+0x168, +0x16c), turned to the actor's facing */
	want[2] = 0;
	want[0] = f32(fmul_m(fld_m(&AF(0x16c)), &AC->speed));
	want[1] = f32(fmul_m(fld_m(&AF(0x168)), &AC->speed));
	Vec3_rotateAxis(want, 1, ftol(fsub_m(fld_m(K(0x4a9424)), &AF(0x170)) * fadd_m(fld_m(&AC->pitch), K(0x4a9734))));
	Vec3_rotateAxis(want, 2, ftol(fld_m(&AF(0x164))));
	float neg = f32(-fld_m(&accel));
	for (int c = 0; c < 3; c++) {   /* the velocity (+0x378) towards it by at most accel */
		long double v = fsub_m(fld_m(&AF(0x378 + c * 4)), &want[c]);
		if (!(v >= neg))
			AF(0x378 + c * 4) = f32(fadd_m(fld_m(&accel), &AF(0x378 + c * 4)));
		else if (v > accel)
			AF(0x378 + c * 4) = f32(fsub_m(fld_m(&AF(0x378 + c * 4)), &accel));
		else
			AU(0x378 + c * 4) = BITS(want[c]);
	}
	float step = !(*dt >= 0.05f) ? *dt : 0.05f;   /* at most 0.05 s */
	for (int c = 0; c < 3; c++)   /* the move this frame (+0x384) */
		AF(0x384 + c * 4) = f32(fmul_m(fld_m(&step), &AF(0x378 + c * 4)));
	if (AC->pilot == ST->playerActor && AC->state == 1 && AC->hitFlash > 0) {   /* a push (+0x885c), fading with +0x8854 squared */
		long double px = fmul_m(fld_m(&step), &AF(0x885c));
		float py = f32(fmul_m(fld_m(&step), &AF(0x8860)));
		float pz = f32(fmul_m(fld_m(&step), &AF(0x8864)));
		long double f = fld_m(&AC->hitFlash);
		float sq = f32(f * f);
		px = fmul_m(px, &sq);
		py = f32(fmul_m(fld_m(&py), &sq));
		pz = f32(fmul_m(fld_m(&pz), &sq));
		AF(0x384) = f32(fadd_m(px, &AF(0x384)));
		AF(0x388) = f32(fadd_m(fld_m(&py), &AF(0x388)));
		AF(0x38c) = f32(fadd_m(fld_m(&pz), &AF(0x38c)));
	}
	if (AC->overheat == 1)
		AC->inBooster = 0;
	if (AC->pilot == ST->playerActor && AC->state == 1) {   /* (to 45a5d1) the local team's live actors move */
		AF(0x180) = f32(fadd_m(fld_m(&AF(0x154)), &AF(0x384)));
		AF(0x184) = f32(fadd_m(fld_m(&AF(0x388)), &AF(0x158)));
		AF(0x188) = f32(fadd_m(fld_m(&AF(0x38c)), &AF(0x15c)));
		memcpy(dir, a + 0x384, 12);
		left = f32(Vec3_normalize(dir));
		for (int j = 0; j < ST->actorCount; j++) {   /* slide around the other live actors */
			if (ST->actors[j].state != 1 || j == i || ST->actors[j].cameraValue != 0)
				continue;
			float r = f32(fmul_m(fadd_m(fld_m(&OF(j, 0x1cd9790)), &AF(0x3e8)), K(0x4a9730)));
			if (math_segmentSphere((float *)(a + 0x154), (float *)(a + 0x180), dir, &ST->actors[j].pos[0], r, hit, hit_t) != 1)
				continue;
			memcpy(a + 0x180, hit, 12);
			for (int c = 0; c < 3; c++)
				AF(0x384 + c * 4) = f32(fsub_m(fld_m(&AF(0x180 + c * 4)), &AC->pos[c]));
			long double X = fld_m(&AF(0x384)), Y = fld_m(&AF(0x388)), Z = fld_m(&AF(0x38c));
			left = f32(fsubr_m(x87_fsqrt((X * X + Y * Y) + Z * Z), &left));
			const float *o = &ST->actors[j].pos[0];
			long double d0 = fsub_m(fld_m(&hit[0]), &o[0]), d1 = fsub_m(fld_m(&hit[1]), &o[1]), d2 = fsub_m(fld_m(&hit[2]), &o[2]);
			float c0 = f32(fmul_m(d2, &dir[1]) - fmul_m(d1, &dir[2]));
			float c1 = f32(fmul_m(d0, &dir[2]) - fmul_m(d2, &dir[0]));
			long double c2 = fmul_m(d1, &dir[0]) - fmul_m(d0, &dir[1]);
			/* along the sphere: (d x dir) x d (slide doubles as the move's velocity out) */
			slide[0] = f32(c2 * d1 - fmul_m(d2, &c1));
			slide[1] = f32(fmul_m(d2, &c0) - c2 * d0);
			slide[2] = f32(fmul_m(d0, &c1) - fmul_m(d1, &c0));
			Vec3_normalize(slide);
			for (int c = 0; c < 3; c++)
				slide[c] = f32(fmul_m(fld_m(&slide[c]), &left));
			for (int c = 0; c < 3; c++)
				AF(0x180 + c * 4) = f32(fadd_m(fld_m(&slide[c]), &AF(0x180 + c * 4)));
			for (int c = 0; c < 3; c++)
				dir[c] = AF(0x384 + c * 4) = f32(fsub_m(fld_m(&AF(0x180 + c * 4)), &AC->pos[c]));
			left = f32(Vec3_normalize(dir));
		}
		float r = AF(0x3e8);
		int moved = collision_moveActor(s, r, (float *)(a + 0x154), (float *)(a + 0x384), BITS(r), 0, mv_pos, slide, mv_dist, mv_plane, 0);
		memcpy(a + 0x180, mv_pos, 12);
		if (moved == 1)
			for (int c = 0; c < 3; c++)
				AF(0x180 + c * 4) = f32(fadd_m(fld_m(&slide[c]), &AF(0x180 + c * 4)));
		for (int c = 0; c < 3; c++) {   /* inside the world box */
			const float *lo = &GAME_VAR(float, s + 0x9ef904 + c * 4), *hi = &GAME_VAR(float, s + 0x9ef910 + c * 4);
			if (!(AF(0x180 + c * 4) >= *lo))
				AU(0x180 + c * 4) = BITS(*lo);
			else if (AF(0x180 + c * 4) > *hi)
				AU(0x180 + c * 4) = BITS(*hi);
		}
		long double v = fadd_m(fld_m(&AC->inPitch), &AC->pitch);   /* the pitch, within +-89 degrees */
		AF(0x18c) = (float)v;
		if (v > *K(0x4a972c))
			AU(0x18c) = 0x445e8000;   /* 890 */
		if (!(AF(0x18c) >= *K(0x4a9728)))
			AU(0x18c) = 0xc45e8000;
		AF(0x190) = f32(fadd_m(fld_m(&AC->inYaw), &AF(0x164)));
		float fwd, back, right, lft;   /* the top speeds: 1 / -1 walking, +0x54.. running */
		if (AC->inBooster == 0) {
			fwd = 1.0f;
			back = -1.0f;
			right = 1.0f;
			lft = -1.0f;
		} else {
			fwd = AF(0x54);
			back = AF(0x58);
			right = AF(0x5c);
			lft = AF(0x60);
		}
		key_axis(&AF(0x194), AC->inForward, AC->inBackward, fwd, back, speed);   /* forward speed (+0x194) */
		key_axis(&AF(0x198), AC->inStepLeft, AC->inStepRight, right, lft, speed);   /* sideways (+0x198) */
		key_ramp(&AF(0x19c), AC->inAltitude == 1, speed);   /* up (+0x19c) */
		key_ramp(&AF(0x1a4), AC->inBooster == 1, speed);   /* running (+0x1a4) */
		/* the walk cycle's rate (+0x1a0) from the forward speed and the pitch */
		long double m, w;
		if (!(AF(0x194) >= 0)) {
			m = AF(0x194) > -1.0f ? fld_m(&AF(0x194)) : -1.0L;
			w = fmul_m(fmul_m(fsub_m(900.0L, &AF(0x18c)), K(0x4a9724)) * m, K(0x4a9720));
			AF(0x1a0) = (float)w;
		} else if (!(AF(0x18c) >= 0)) {
			m = !(AF(0x194) >= 1.0f) ? fld_m(&AF(0x194)) : 1.0L;
			w = fmul_m(fmul_m(fadd_m(fld_m(&AF(0x18c)), K(0x4a9734)), K(0x4a971c)) * m, K(0x4a9718));
			AF(0x1a0) = (float)w;
		} else {
			m = !(AF(0x194) >= 1.0f) ? fld_m(&AF(0x194)) : 1.0L;
			w = fmul_m(m, K(0x4a9718));
			AF(0x1a0) = (float)w;
			if (AF(0x194) > 1.0f)
				AF(0x1a0) = (float)(fmul_m(fsub_m(fld_m(&AF(0x194)), K(0x4a9424)), &AF(0x18c)) / fsub_m(fld_m(&AF(0x54)), K(0x4a9424)) + w);
		}
		AF(0x1a0) = f32(fmul_m(fmul_m(fadd_m(fld_m(&AF(0x1a4)), K(0x4a9424)), K(0x4a942c)) * fsub_m(fld_m(K(0x4a9424)), &AF(0x170)), &AF(0x1a0)));
	} else {   /* the others: towards their sent state (+0x1ac..) at 6.66 a second */
		long double f = fmul_m(fld_m(dt), K(0x4a9714));
		float k = (float)f;
		if (f > 1.0L)
			k = 1.0f;
		long double x = fsub_m(fld_m(&AF(0x1ac)), &AF(0x154));
		float y = f32(fsub_m(fld_m(&AF(0x1b0)), &AF(0x158)));
		float z = f32(fsub_m(fld_m(&AF(0x1b4)), &AF(0x15c)));
		x = fmul_m(x, &k);
		y = f32(fmul_m(fld_m(&k), &y));
		z = f32(fmul_m(fld_m(&k), &z));
		AF(0x180) = f32(fadd_m(x, &AF(0x154)));
		AF(0x184) = f32(fadd_m(fld_m(&y), &AF(0x158)));
		AF(0x188) = f32(fadd_m(fld_m(&z), &AF(0x15c)));
		AF(0x18c) = f32(fadd_m(fmul_m(fsub_m(fld_m(&AF(0x1b8)), &AC->pitch), &k), &AC->pitch));
		AF(0x190) = f32(angle_stepTowards(AU(0x190), AU(0x1bc), BITS(k)));
		for (int c = 0; c < 5; c++)   /* +0x194..+0x1a4 */
			AF(0x194 + c * 4) = f32(fadd_m(fmul_m(fsub_m(fld_m(&AF(0x1c0 + c * 4)), &AF(0x168 + c * 4)), &k), &AF(0x168 + c * 4)));
	}
	if (AF(0x17c) > 0 && weapon) {   /* the firing cycle (+0x1a8), wrapping at 1 */
		long double v = fadd_m(fdiv_m(fld_m(dt), &((ActorInfo *)weapon)->cycleTime), &AC->fireCycle);
		AC->fireCycle = (float)v;
		if (v >= 1.0L)
			AC->fireCycle = 0;
	}
	if (AC->cameraValue != 0)
		goto tail;   /* 45cdb1 */
	if (AC->weaponLowering == 1) {   /* the weapon going down (+0x490 from 1 to 0) */
		if (AF(0x490) > 0) {
			if (AU(0x490) == 0x3f800000 && i == ST->playerActor)
				sound_playVolume(0x14, 0x64);
			AF(0x490) = f32(fsubr_m(fmul_m(fld_m(dt), K(0x4a9534)), &AF(0x490)));
		}
		if (!(AF(0x490) > 0))
			AC->weaponLowering = AI(0x490) = 0;
	} else if (AC->weaponLowering == 0) {   /* the next one coming up */
		if (!(AF(0x490) > 0)) {
			actor_setWeaponSlot((Stage *)s, i, AI(0x498));
			actor_updatePart(s, i, AI(0x498), AI(0x49c));
			weapon = s + 0x14d1ab4 + GAME_VAR(int, player + 0x320 + AC->gaugeIcon * 4) * 0x2e18;
			model = AC->gaugeIcon == 4 ? a + 0x587c : AC->gaugeIcon == 5 ? a + 0x701c : a + 0x40dc;
			(*(u32 *)&AC->weapon) = ((u32)((ActorInfo *)weapon)->ammoSlot);
		}
		if (!(AF(0x490) >= 1.0f)) {
			int kind = GAME_VAR(int, player + 0x320 + AC->gaugeIcon * 4);
			AF(0x490) = f32(fadd_m(fmul_m(fld_m(dt), K(kind == 11 ? ADDR(k_1_95f) : kind == 3 ? ADDR(k_2_25f) : ADDR(k_3f))), &AF(0x490)));
			if (AF(0x490) >= 1.0f)
				AF(0x490) = 1.0f;
		}
	}
	/* the body's pose: the arms' swing and lean (+0x390..+0x3a4) */
	clamp450(&AF(0x390), fmul_m(fld_m(&AF(0x16c)), K(0x4a94a0)));
	AF(0x394) = f32(fmul_m(fmul_m(fsub_m(fld_m(K(0x4a9424)), &AF(0x170)) * fadd_m(fld_m(&AC->pitch), K(0x4a9734)), &AF(0x40)), K(0x4a9724)));
	clamp450(&AF(0x398), fmul_m(fld_m(&AF(0x16c)), K(0x4a93f0)));
	AF(0x39c) = f32(fmul_m(fadd_m(fsub_m(fld_m(&AC->pitch), &AF(0x174)), K(0x4a9734)), K(0x4a9724)));
	long double side = !(AF(0x168) >= -1.0f) ? -1.0L : AF(0x168) > 1.0f ? 1.0L : fld_m(&AF(0x168));
	AF(0x3a0) = f32(fmul_m(fsubr_m(fmul_m(fadd_m(fld_m(&AF(0x178)), K(0x4a9424)), K(0x4a942c)) * fsub_m(fld_m(K(0x4a9424)), &AF(0x170)) * side, K(0x4a9424)), K(0x4a942c)));
	AU(0x3a4) = AU(0x178);
	anim_setFrame(a + 0x554, 0, AU(0x39c));
	anim_setFrame(a + 0xd54, 0, AU(0x39c));
	anim_setFrame(a + 0x1554, 0, AU(0x39c));
	anim_setFrame(a + 0x2524, 0, AU(0x3a0));
	anim_setFrame(a + 0x34f4, 0, AU(0x3a4));
	anim_setFrame(model, 0, AU(0x17c));
	/* the matrices: the body at the actor, turned and leant, the head on its neck, the arms */
	glPushMatrix();
	glTranslatef_bits(AU(0x154), AU(0x158), AU(0x15c));
	glRotatef(f32(fmul_m(fld_m(&AF(0x164)), K(0x4a93ec))), 0, 1, 0);
	glRotatef(f32(fmul_m(fld_m(&AF(0x174)), K(0x4a93ec))), 1, 0, 0);
	glGetFloatv(0xba6, (float *)(a + 0x3a8));
	skel_poseBones(a + 0xd54, a + 0x3a8);
	glLoadMatrixf((const float *)(uintptr_t)(AU(0xd68) + GAME_VAR(int, head + 0xa98 + AI(0x484) * 4) * 100 + 0xc));
	glRotatef(f32(fmul_m(fld_m(&AF(0x398)), K(0x4a93ec))), 0, 1, 0);
	skel_poseBones(a + 0x2524, 0);
	glLoadMatrixf(part_matrix(a + 0xd68, head + 0xa90, AI(0x484)));
	skel_poseBones(a + 0x1554, 0);
	glLoadMatrixf(part_matrix(a + 0xd68, head + 0xaa0, AI(0x484)));
	if (((u32)AC->timerFlags) & 0x1000)
		glScalef_bits(0x40a00000, 0x40a00000, 0x40a00000);   /* 5 */
	skel_poseBones(a + 0x554, 0);
	glLoadMatrixf(part_matrix(a + 0xd68, head + 0xaa8, AI(0x484)));
	glRotatef(f32(fmul_m(fld_m(&AF(0x390)), K(0x4a9468))), 0, 0, 1);
	glRotatef(f32(fmul_m(fld_m(&AF(0x394)), K(0x4a93ec))), 1, 0, 0);
	skel_poseBones(a + 0x34f4, 0);
	memcpy(grip, &g_vecZero, 12);   /* where the weapon is held, for the local player's view */
	glLoadMatrixf(part_matrix(a + 0x1568, body + 0x12d0, AI(0x484)));
	if (i == ST->selectedActor && weapon && AC->gaugeIcon <= 3)
		hold(grip, weapon + 0x16d8 + AI(0x49c) * 12, 0, &AF(0x490));
	skel_poseBones(a + 0x40dc, 0);
	glLoadMatrixf(part_matrix(a + 0x1568, body + 0x12d8, AI(0x484)));
	if (i == ST->selectedActor && weapon && AC->gaugeIcon == 4)
		hold(grip, weapon + 0x16d8 + AI(0x49c) * 12, 0, &AF(0x490));
	skel_poseBones(a + 0x587c, 0);
	glLoadMatrixf(part_matrix(a + 0x1568, body + 0x12e0, AI(0x484)));
	if (i == ST->selectedActor && weapon && AC->gaugeIcon == 5)
		hold(grip, weapon + 0x2d94 + AI(0x49c) * 12, 1, &AF(0x490));
	skel_poseBones(a + 0x701c, 0);
	glPopMatrix();
	if (i == ST->playerActor) {   /* the lock-on warnings (s+0x202ea80 per actor), sorted longest first */
		float *lock = &GAME_VAR(float, s + 0x202ea80);
		int *count = &ST->bulletCount;
		if (weapon && ((ActorInfo *)weapon)->ringRange > 0) {
			for (int j = 0; j < ST->actorCount; j++) {
				float *seen = &ST->actors[j].lockSize;
				if (j == i || ST->actors[j].state != 1) {
					lock[j] = 0;
					continue;
				}
				if (*seen > 0) {
					long double v = fsub_m(fld_m(seen), dt);
					*seen = (float)v;
					if (!(v >= 0))
						*seen = 0;
				}
				if (!(fmul_m(fld_m(&AF(0xc)), &((ActorInfo *)weapon)->ringRange) >= ST->actors[j].lockedOn) && AC->team != ST->actors[j].team) {
					if (!(lock[j] > 0)) {
						sound_playVolume(0x12, 0x64);
						BITS(*seen) = 0x3e800000;   /* 0.25 */
					}
					BITS(lock[j]) = AU(0x10);
				} else {
					long double v = fsub_m(fld_m(&lock[j]), dt);
					lock[j] = (float)v;
					if (!(v >= 0))
						lock[j] = 0;
				}
			}
			*count = 0;
			for (int j = 0; j < ST->actorCount; j++)
				if (lock[j] > 0) {
					BITS(GAME_VAR(float, s + 0x202ec10 + *count * 4)) = BITS(lock[j]);
					GAME_VAR(int, s + 0x202eda0 + *count * 4) = j;
					++*count;
				}
			float *t = &GAME_VAR(float, s + 0x202ec10);
			if (*count > 0)
				for (int k = 1; k - 1 < *count; k++)
					for (int m = k; m < *count; m++)
						if (!(t[k - 1] >= t[m])) {
							long double was = fld_m(&t[k - 1]);
							BITS(t[k - 1]) = BITS(t[m]);
							t[m] = (float)was;
							int *id = &GAME_VAR(int, s + 0x202eda0);
							int w = id[m];
							id[m] = id[k - 1];
							id[k - 1] = w;
						}
		} else {
			for (int j = 0; j < ST->actorCount; j++)
				lock[j] = 0;
			*count = 0;
		}
	}
	AI(0x1ec) = 0;   /* firing this frame */
	AI(0x374) = 0;
	if (AC->pilot == ST->playerActor) {
		if (weapon && AC->state == 1) {
			if (AC->inFire == 1 && AF(0x120) > 3.0f && AC->gaugeIcon >= 0 && !(AF(0x17c) > 0) && AF(0x490) >= 1.0f && AC->weaponLowering == 0
			    && AC->armor > 0)
				AI(0x1ec) = 1;
			int shots = 0;   /* this frame's rounds: whole cycles times the burst, and a burst's rounds left (+0x1f0, +0x1f4) */
			const float *cycle = &((ActorInfo *)weapon)->cycleTime, *gap = &((ActorInfo *)weapon)->burstGap;
			int burst = ((ActorInfo *)weapon)->burst;
			if (AI(0x1ec) == 1) {
				int n = ftol(fdiv_m(fld_m(dt), cycle));
				shots = burst * (n + 1) + AC->burstLeft;
				if (*gap > 0) {
					long double r = fsubr_m(fmul_m((long double)n, cycle), dt);
					int m = ftol(fdiv_m(r, gap)) + 1;
					if (burst > m) {
						AF(0x1f4) = f32(r - fmul_m((long double)(m - 1), gap));
						AC->burstLeft = burst - m;
						shots -= AC->burstLeft;
					} else
						AC->burstLeft = 0;
				} else
					AC->burstLeft = 0;
			} else if (AC->burstLeft > 0) {
				long double v = fadd_m(fld_m(dt), &AF(0x1f4));
				AF(0x1f4) = (float)v;
				if (v >= *gap) {
					int m = ftol(fdiv_m(v, gap));
					if (m >= AC->burstLeft) {
						shots = AC->burstLeft;
						AC->burstLeft = 0;
						AI(0x1f4) = 0;
					} else {
						AC->burstLeft -= m;
						shots = m;
						AF(0x1f4) = f32(fsubr_m(fmul_m((long double)m, gap), &AF(0x1f4)));
					}
				}
			}
			int quit = 0;
			for (int n = 0; n < shots && !quit; n++) {
				int k = 0;
				while (k < 5 && AI(0x360 + k * 4) >= 0)
					k++;
				if (k == 5)
					break;
				int w = ((ActorInfo *)weapon)->ammoSlot;
				if (AC->ammo[w] < ((ActorInfo *)weapon)->ammoPerShot && AC->bot != 2) {   /* out of ammunition */
					if (i == ST->playerActor) {
						if (AI(0x4a0) != 0)
							break;
						strcpy((char *)(a + 0x4f4), (const char *)STR(0x4b4528, "OUT OF AMMO!"));
						AU(0x534) = BITS(*dt);
						sound_playVolume(0xa5, 0x64);
					}
					if (AI(0x4a0) == 0)
						actor_nextWeapon(s, i);
					break;
				}
				if (w >= 0) {
					const int *muzzle = (const int *)(weapon + (AC->gaugeIcon == 5 ? 0x2ca4 : 0x15e8) + AI(0x49c) * 64);
					skel_applyPose(GAME_VAR(void *, GAME_VAR(u8 *, model + 0x20)), m1e0, muzzle[0], 0);
					Mat4_invert(m270, m1e0);
					memset(m0d0, 0, 64);   /* the grip undone */
					BITS(m0d0[0]) = BITS(m0d0[5]) = BITS(m0d0[10]) = BITS(m0d0[15]) = 0x3f800000;
					m0d0[12] = f32(-fld_m(&grip[0]));
					m0d0[13] = f32(-fld_m(&grip[1]));
					m0d0[14] = f32(-fld_m(&grip[2]));
					Mat4_multiply(m230, m270, m0d0);
					Mat4_multiply(m18c, m230, m1e0);
					long double r = (long double)(n % burst);   /* this round's v28 */
					v28[0] = f32(fmul_m(r, &GAME_VAR(float, weapon + 0x2dd0)));
					v28[1] = f32(fmul_m(r, &GAME_VAR(float, weapon + 0x2dd4)));
					v28[2] = f32(fmul_m(r, &GAME_VAR(float, weapon + 0x2dd8)));
					long double x = ((fmul_m(fld_m(&m18c[8]), &v28[2]) + fmul_m(fld_m(&m18c[4]), &v28[1])) + fmul_m(fld_m(&m18c[0]), &v28[0])) + m18c[12];
					long double y = ((fmul_m(fld_m(&m18c[9]), &v28[2]) + fmul_m(fld_m(&m18c[5]), &v28[1])) + fmul_m(fld_m(&m18c[1]), &v28[0])) + m18c[13];
					long double z = ((fmul_m(fld_m(&m18c[10]), &v28[2]) + fmul_m(fld_m(&m18c[6]), &v28[1])) + fmul_m(fld_m(&m18c[2]), &v28[0])) + m18c[14];
					const float *q = (const float *)(uintptr_t)(GAME_VAR(u32, model + 0x14) + muzzle[0] * 100 + 0xc);
					shot_at[0] = f32(((fmul_m(z, &q[8]) + fmul_m(y, &q[4])) + fmul_m(x, &q[0])) + q[12]);
					shot_at[1] = f32(((fmul_m(x, &q[1]) + fmul_m(z, &q[9])) + fmul_m(y, &q[5])) + q[13]);
					shot_at[2] = f32(((fmul_m(x, &q[2]) + fmul_m(z, &q[10])) + fmul_m(y, &q[6])) + q[14]);
					memcpy(shot_dir, &g_vecUnitZ, 12);
					if (AC->bot == 0) {
						Vec3_rotateAxis(shot_dir, 1, ftol(fld_m(&AC->pitch)));
						Vec3_rotateAxis(shot_dir, 2, ftol(fld_m(&AF(0x164))));
					} else {   /* a bot's aim wanders by +-(+0x74) */
						u32 sp = (u32)(AC->spawn74 * 2);
						int r1 = (int)sp > 0 ? (int)rand_below(sp) : 0;
						Vec3_rotateAxis(shot_dir, 1, ftol(fld_m(&AC->pitch)) - AC->spawn74 + r1);
						int r2 = (int)(u32)(AC->spawn74 * 2) > 0 ? (int)rand_below((u32)(AC->spawn74 * 2)) : 0;
						Vec3_rotateAxis(shot_dir, 2, ftol(fld_m(&AF(0x164))) - AC->spawn74 + r2);
					}
					if (collision_rayTrace(s, (float *)(a + 0x154), shot_at, v28) != 0) {   /* the muzzle inside a wall */
						if (i == ST->playerActor && AI(0x4a0) == 0)
							sound_playVolume(0xa5, 0x64);
						break;
					}
					if (AC->bot != 0) {   /* a bot holds fire without a clear line, and swaps weapons when too close */
						const float *tp = &ST->actors[AC->botTarget].pos[0];
						if (collision_rayTrace(s, shot_at, tp, v28) != 0)
							continue;
						float d[3];
						for (int c = 0; c < 3; c++)
							d[c] = f32(fsub_m(fld_m(&tp[c]), &AC->pos[c]));
						memcpy(v28, d, 12);
						long double R = fld_m(&((ActorInfo *)weapon)->splashRadius);
						long double dd = (fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1])) + fmul_m(fld_m(&d[0]), &d[0]);
						if (R * R > dd) {
							if (AC->gaugeIcon == 0 && GAME_VAR(int, player + 0x330) >= 0)
								actor_selectWeapon((Stage *)s, i, 4);
							else if (AC->gaugeIcon == 4)
								actor_selectWeapon((Stage *)s, i, 0);
							continue;
						}
					}
					u32 *rec = (u32 *)(a + 0x298 + k * 40);   /* the round */
					rec[0] = 0;
					rec[1] = GAME_VAR(u32, player + 0x320 + AC->gaugeIcon * 4);
					memcpy(rec + 2, shot_at, 12);
					rec[5] = 0xffffffff;
					memcpy(rec + 6, shot_dir, 12);
					rec[9] = (u32)(uintptr_t)q;
					int target;
					if (i == ST->playerActor) {
						int c = ST->bulletCount;
						target = c > 0 ? GAME_VAR(int, s + 0x202eda0 + (n % c) * 4) : -1;
					} else
						target = AC->botTarget;
					AI(0x360 + k * 4) = bullet_spawn(s, -1, i, target, rec, n);
					AI(0x1fc + k * 32) = 1;
					if (AC->bot != 2)
						AC->ammo[((ActorInfo *)weapon)->ammoSlot] -= ((ActorInfo *)weapon)->ammoPerShot;
				}
				AF(0x17c) = 0.0001f;   /* 0.0001: the firing cycle restarts */
				long double v = fdiv_m(fld_m(dt), cycle);
				AC->fireCycle = (float)v;
				if (v >= 1.0L)
					AC->fireCycle = 0;
			}
			AI(0x4a0) = AC->inFire;
		}
	} else if (weapon && AI(0x1e8) == 1) {   /* the others' rounds, as sent */
		for (int k = 0; k < 5; k++) {   /* per slot: +0x1f8 in use, +0x1fc a new round (+0x200 kind, +0x204 owner, +0x208 flag, +0x20c dir) */
			int *item = &AI(0x360 + k * 4);
			u32 *f = &AU(0x1fc + k * 32);
			if (f[-1] != 1)
				continue;
			if (f[0] == 1) {
				if (*item >= 0)
					actor_clearTargetRefs(s, *item);
				const int *muzzle = (const int *)(weapon + (AC->gaugeIcon == 5 ? 0x2ca4 : 0x15e8) + AI(0x49c) * 64);
				skel_applyPose(GAME_VAR(void *, GAME_VAR(u8 *, model + 0x20)), m1e0, muzzle[0], 0);
				Mat4_invert(m270, m1e0);
				memset(m0d0, 0, 64);
				BITS(m0d0[0]) = BITS(m0d0[5]) = BITS(m0d0[10]) = BITS(m0d0[15]) = 0x3f800000;
				m0d0[12] = f32(-fld_m(&grip[0]));
				m0d0[13] = f32(-fld_m(&grip[1]));
				m0d0[14] = f32(-fld_m(&grip[2]));
				Mat4_multiply(m230, m270, m0d0);
				Mat4_multiply(m18c, m230, m1e0);
				const float *o = &g_vecOrigin;
				long double x = ((fmul_m(fld_m(&m18c[8]), &o[2]) + fmul_m(fld_m(&m18c[4]), &o[1])) + fmul_m(fld_m(&m18c[0]), &o[0])) + m18c[12];
				long double y = ((fmul_m(fld_m(&m18c[9]), &o[2]) + fmul_m(fld_m(&m18c[5]), &o[1])) + fmul_m(fld_m(&m18c[1]), &o[0])) + m18c[13];
				long double z = ((fmul_m(fld_m(&m18c[10]), &o[2]) + fmul_m(fld_m(&m18c[6]), &o[1])) + fmul_m(fld_m(&m18c[2]), &o[0])) + m18c[14];
				const float *q = (const float *)(uintptr_t)(GAME_VAR(u32, model + 0x14) + muzzle[0] * 100 + 0xc);
				shot_at[0] = f32(((fmul_m(z, &q[8]) + fmul_m(y, &q[4])) + fmul_m(x, &q[0])) + q[12]);
				shot_at[1] = f32(((fmul_m(x, &q[1]) + fmul_m(z, &q[9])) + fmul_m(y, &q[5])) + q[13]);
				shot_at[2] = f32(((fmul_m(x, &q[2]) + fmul_m(z, &q[10])) + fmul_m(y, &q[6])) + q[14]);
				u32 *rec = (u32 *)(a + 0x298 + k * 40);
				rec[0] = 1;
				rec[1] = GAME_VAR(u32, player + 0x320 + AC->gaugeIcon * 4);
				memcpy(rec + 2, shot_at, 12);
				rec[5] = f[2];
				memcpy(rec + 6, f + 4, 12);
				rec[9] = (u32)(uintptr_t)q;
				*item = bullet_spawn(s, -1, i, -1, rec, 0);
				AF(0x17c) = 0.0001f;
				long double v = fadd_m(fdiv_m(fld_m(dt), &((ActorInfo *)weapon)->cycleTime), &AC->fireCycle);
				AC->fireCycle = (float)v;
				if (v >= 1.0L)
					AC->fireCycle = 0;
				f[0] = 0;
			}
			u8 *b = s + 0x202ef34 + *item * 0x4e8;   /* the round's record, brought up to date */
			if (GAME_VAR(int, b + 4) != 1)
				continue;
			GAME_VAR(u32, b + 0xb8) = f[1];
			GAME_VAR(int, b + 0x6c) = array_recordAt(f[2], GAME_VAR(u32, s + 0xa24), 0xac);
			if (f[3] == 1)
				GAME_VAR(float, b + 0x74) = f32(fsub_m(fld_m(&GAME_VAR(float, b + 0x70)), dt));
			memcpy(b + 0x90, f + 4, 12);
			memcpy(b + 0x60, f + 4, 12);
			GAME_VAR(int, b + 0x9c) = 1;
		}
	}
	/* stamina (+0x4ac): spent running, back after a rest (+0x4b0 the rest) */
	if (!(((u32)AC->timerFlags) & 0x400) && AC->inBooster == 1 && (AC->inForward == 1 || AC->inBackward == 1 || AC->inStepLeft == 1 || AC->inStepRight == 1)) {
		long double v = fsubr_m(fdiv_m(fld_m(dt), &AF(0x44)), &AF(0x4ac));
		AF(0x4ac) = (float)v;
		if (!(v >= 0)) {
			AI(0x4ac) = 0;
			AC->overheat = 1;
		}
		AI(0x4b0) = 0;
	} else if (!(AF(0x4b0) >= 1.0f)) {
		long double v = fadd_m(fdiv_m(fld_m(dt), &AF(0x4c)), &AF(0x4b0));
		AF(0x4b0) = (float)v;
		if (v > 1.0L)
			AU(0x4b0) = 0x3f800000;
	} else if (!(AF(0x4ac) >= 1.0f)) {
		long double v = fadd_m(fdiv_m(fld_m(dt), &AF(0x48)), &AF(0x4ac));
		AF(0x4ac) = (float)v;
		if (v > 1.0L)
			AF(0x4ac) = 1.0f;
	}
	AC->warned = AF(0x4ac) > *K(0x4a94f8) ? 0 : 1;
	if (AC->overheat == 1 && AF(0x4ac) >= 0.5f)
		AC->overheat = 0;
	if (AC->state == 1) {
		/* the effects' scale by the speed: 0.5 .. 3 */
		if (!(AF(0x194) > 0.5f))
			AU(0x4a4) = 0x3f000000;
		else if (!(AF(0x194) >= 3.0f))
			AU(0x4a4) = AU(0x194);
		else
			AU(0x4a4) = 0x40400000;
		if (i != ST->selectedActor && AC->viewMarked == 0) {   /* the arms' and legs' emitters, faint when cloaked or hurt */
			BITS(v28[0]) = AU(0x4a4);
			if ((((u32)AC->timerFlags) & 0x200) && AI(8) >= OI(ST->playerActor, 0x1cd93b0))
				BITS(v28[1]) = 0x3d808081;   /* 1/255 */
			else if (AF(0x120) > 3.0f)
				BITS(v28[1]) = 0x3f800000;
			else
				v28[1] = f32(fmul_m(fld_m(&AF(0x120)), K(0x4a9438)));
			if (i == ST->playerActor)
				v28[1] = f32(fmul_m(fld_m(&v28[1]), K(0x4a942c)));
			emit(s, a, (const int *)(arms + 0x12d0), (const int *)(arms + 0x13d0), a + 0x2538, legs, v28, fx);
			emit(s, a, (const int *)(legs + 0x16f0), (const int *)(legs + 0x17f0), a + 0x3508, legs, v28, fx);
		}
		long double v = fadd_m(fld_m(dt), &AF(0x4a8));   /* footsteps every third of a second */
		AF(0x4a8) = (float)v;
		if (v > *K(0x4a9704)) {
			if (i == ST->playerActor && (AC->warned == 1 || AC->overheat == 1) && !(AF(0x3fc) > 0))
				sound_playVolume(0x10, 0x64);   /* out of breath */
			if (i != GAME_VAR(int, s + 0x202e8dc)) {
				int step = GAME_VAR(int, legs + 0x17fc);
				if (i == ST->playerActor)
					sound_playVolume(AC->inBooster == 0 ? step : step + 3, AC->inBooster == 0 ? 0x28 : 0x50);
				else
					sound_play3D(AF(0x1a4) > 0 ? step + 3 : step, s + 0x20f3970, a + 0x180, s + 0x20f397c, 0x47435000);
			}
			AI(0x4a8) = 0;
		}
	}
	if (AC->state == 1) {
		if (AC->armor <= 0)
			actor_dies(s, a, i, fx, v28);
		else if (AC->pilot == ST->playerActor || AC->bot != 0)   /* the armour's timer kept 10 s ahead */
			AF(0x124) = f32(fadd_m(fadd_m(fld_m(dt), &AF(0x120)), K(0x4a9418)));
	} else if (AC->state == 2) {   /* dying: out after 2 s */
		if (AF(0x150) > 2.0f) {
			AC->state = 3;
			AI(0x150) = 0;
			if (i == ST->playerActor)   /* the patch DLL's cat_wrap */
				PATCHED_THISCALL(0x45c638, void, void *, u32)(s, g_componentDatPath);
		}
	} else if (AC->state == 3)
		AU(0x120) = AU(0x124);
	AI(0x4ec) = 0;   /* the glow (+0x4ec): a fresh shot's flash, and speed unless cloaked */
	if (AF(0x17c) > 0 && !(AF(0x17c) >= 0.5f)) {
		long double g = fsub_m(fld_m(K(0x4a942c)), &AF(0x17c));
		AF(0x4ec) = (float)(g + g);
	}
	if ((((u32)AC->timerFlags) & 0x200) && AI(8) >= OI(ST->playerActor, 0x1cd93b0)) {
		if (AF(0x4a4) > 1.0f)
			AF(0x4ec) = f32(fadd_m(fmul_m(fsub_m(fld_m(&AF(0x4a4)), K(0x4a9424)), K(0x4a94f8)), &AF(0x4ec)));
	} else
		AF(0x4ec) = f32(fadd_m(fmul_m(fld_m(&AF(0x4a4)), K(0x4a94f8)), &AF(0x4ec)));
	goto timers;
tail:   /* 45cdb1: held by the script */
	AF(0x124) = f32(fadd_m(fadd_m(fld_m(dt), &AF(0x120)), K(0x4a9418)));
timers:
	AF(0x120) = f32(fadd_m(fld_m(dt), &AF(0x120)));
	AF(0x150) = f32(fadd_m(fld_m(dt), &AF(0x150)));
	long double sec = fadd_m(fld_m(dt), &AC->timeExtra);   /* whole seconds into +0xfc */
	AC->timeExtra = (float)sec;
	if (sec > 1.0L) {
		AC->timePlayed += ftol(sec);
		AC->timeExtra = f32(fsubr_m((long double)ftol(fld_m(&AC->timeExtra)), &AC->timeExtra));
	}
	countdown(&AC->labelFade, dt);
	countdown(&AC->hitFlash, dt);
	countdown(&AF(0x8858), dt);
	countdown(&AC->gauge, dt);
	AF(0x534) = f32(fsub_m(fld_m(&AF(0x534)), dt));
	countdown(&AF(0x540), dt);
	if (AC->shield < AC->shieldMax && AI(0x448) > 0) {   /* the energy (+0x12c) back by +0x448 a second up to +0x20 */
		long double v = fadd_m(fld_m(dt), &AF(0x544));
		AF(0x544) = (float)v;
		if (v >= 1.0L) {
			int e = ftol(v) * AI(0x448) + AC->shield;
			if (e >= AC->shieldMax) {
				AC->shield = AC->shieldMax;
				AI(0x544) = 0;
			} else {
				AC->shield = e;
				AF(0x544) = f32(fsubr_m((long double)ftol(fld_m(&AF(0x544))), &AF(0x544)));
			}
		}
	} else
		AI(0x544) = 0;
	countdown(&AC->damageFlash, dt);
	countdown(&AF(0x3f4), dt);
	countdown(&AC->timers[1], dt);
	countdown(&AF(0x3fc), dt);
	countdown(&AC->timers[3], dt);
	for (int c = 0; c < 3; c++)   /* this frame's move */
		AF(0x384 + c * 4) = f32(fsub_m(fld_m(&AF(0x180 + c * 4)), &AC->pos[c]));
	AI(0x1e8) = 0;
	if (AC->pilot == ST->playerActor) {   /* the state bits sent with the actor */
		u32 f = 0;
		if (AC->armor >= AC->armorMax)
			f = 1;
		if (AC->armor >= AC->armorMax + 100)
			f |= 2;
		if (AC->shield >= AC->shieldMax)
			f |= 4;
		if (AC->shield >= AC->shieldMax + 100)
			f |= 8;
		for (int c = 0; c < 4; c++)   /* the ammunition kinds full */
			if (AC->ammo[c] >= AC->ammoMax[c])
				f |= 0x10 << c;
		for (int c = 0; c < 4; c++)   /* the power-ups running */
			if (AC->timers[c] > 0)
				f |= 0x100 << c;
		if (AI(0x4d4) == 1)
			f |= 0x1000;
		if (AC->shield <= 0)
			f |= 0x2000;
		if (AI(0x104) % 2 == 1)
			f |= 0x4000;
		(*(u32 *)&AC->timerFlags) = f;
	}
	static const u16 parts[7] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x587c, 0x701c };
	if (AI(0x54c) < 7) {   /* the parts' break-up, one a frame */
		if (AI(0x54c) >= 0)
			partList_bindTextures(a + parts[AI(0x54c)]);
		AI(0x54c)++;
	}
}
