/* actor_frame.c: an actor's frame: its weapon and parts, a bot's mind (target, path, aim, keys), the movement and
   collisions, the body's pose and matrices, firing, the lock-on warnings, stamina, footsteps and effects, death and
   its score, and the timers. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

#define K(address) ((const float *)RELOC(address))
#define AC ((Player *)a)   /* the same by its fields (src/scene.fields) */
#define AF(offset) GAME_VAR(float, a + (offset))
#define AU(offset) GAME_VAR(u32, a + (offset))
/* point k of path r: trigger r's way point k */
#define PATH_POINT(r, k) (((const WayPoint *)ST->triggers[r].wayPoints)[k].pos)



static u32 rand_below(u32 n)
{
	u32 r = (*(u32 *)&g_randTable[g_randPos & 0xfff]) % n;
	g_randPos++;
	return r;
}

/* the view (botLookPitch pitch, botLookYaw heading, tenths of a degree) at point p */
static void aim_at(u8 *a, const float *p)
{
	float d[3];
	for (int c = 0; c < 3; c++)
		d[c] = f32(FSUB(p[c], AC->pos[c]));
	long double x = fld_m(&d[0]), z = fld_m(&d[2]);
	AC->botLookPitch = f32(fmul_m(x87_fpatan(-fld_m(&d[1]), x87_fsqrt(x * x + z * z)), &k_572_9578f));
	AC->botLookYaw = f32(fmul_m(x87_fpatan(fld_m(&d[0]), fld_m(&d[2])), &k_572_9578f));
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
static const float *part_matrix(u8 *base, const int *joints, int pose)
{
	return (const float *)(uintptr_t)(GAME_VAR(u32, base) + joints[pose] * 100 + 0xc);
}

/* the local player's weapon at its grip (negated), drawn back by 600 while it comes up (or out, for the sixth) */
static void hold(float *grip, const u8 *at, int out, const float *raise)
{
	const float *o = (const float *)RELOC(at);
	float x = f32(-fld_m(&o[0])), y = f32(-fld_m(&o[1])), z = f32(-fld_m(&o[2]));
	long double d = fmul_m(fsub_m(fld_m(&k_1f), raise), k_600f);
	grip[0] = f32(out ? fadd_m(d, &x) : fsubr_m(d, &x));
	grip[1] = y;
	grip[2] = z;
	glTranslatef_bits(BITS(grip[0]), BITS(y), BITS(z));
}

/* the legs' or booster's emitters: a puff at each joint (flagged 1 in joint[1]: only while running, run > 0) */
static void emit(u8 *s, u8 *a, const int (*joint)[0x20], const int *count, const u8 *mx, const BoosterType *booster, const float *scratch, u32 *fx)
{
	for (int k = 0; k < *count; k++) {
		if (joint[1][k] == 1 && !(AC->run > 0))
			continue;
		u32 r = (*(u32 *)&g_randTable[g_randPos & 0xfff]) & 7;
		g_randPos++;
		const ListedObject *m = (const ListedObject *)(uintptr_t)GAME_VAR(u32, mx) + joint[0][k];
		fx[0] = booster->thrustType + 5;
		fx[1] = r;
		memcpy(fx + 2, m->centre, 12);
		memcpy(fx + 5, scratch, 12);   /* scale, alpha, and whatever the third word last held */
		fx[8] = (u32)(uintptr_t)m->matrix;
		fx[9] = fx[10] = fx[11] = fx[12] = 0;
		particle_spawn(s, fx);
	}
}

#define stage_print(...) GAME_FN(stage_printText, 0x473450, int, void *, const char *, ...)(__VA_ARGS__)
#define FRAG_POINTS(level) GAME_VAR(int, OBJ(g_fragPoints) + (level) * 4)   /* a kill's points by the victim's level */

/* the killer's points and level (the level shown for the local team only) */
static void award(u8 *s, int k, int frags, int points)
{
	ST->actors[k].kills += frags;
	ST->actors[k].score += points;
	if (ST->actors[k].controlledBy == ST->playerActor)
		ST->actors[k].grade = actor_levelFromValue(ST->actors[k].score);
}

/* armour gone: the burst, the debris, the score */
static void actor_dies(u8 *s, u8 *a, int i, u32 *fx, float *scratch)
{
	memset(fx, 0, 13 * 4);
	fx[0] = 3;
	memcpy(AC->deathPos, AC->pos, 12);
	memcpy(fx + 2, AC->pos, 12);
	memcpy(fx + 5, AC->nextPos, 12);
	particle_spawn(s, fx);
	for (int n = 0; n < 20; n++) {
		scratch[0] = scratch[1] = 0;
		BITS(scratch[2]) = 0x459c4000;   /* 5000 */
		Vec3_rotateAxis(scratch, 1, (int)rand_below(3600));
		Vec3_rotateAxis(scratch, 2, (int)rand_below(3600));
		fx[1] = ((u32)AC->player);
		fx[0] = 9;
		memcpy(fx + 2, AC->pos, 12);
		fx[8] = fx[9] = 0;
		memcpy(fx + 5, scratch, 12);
		fx[10] = fx[11] = fx[12] = 0;
		particle_spawn(s, fx);
	}
	int local = ST->playerActor;
	if (i == local && AC->lastAttacker != i)
		sound_playVolume(0xd, 0x64);
	AC->state = 2;
	AC->stateTime = 0.0f;
	ST->rankingDirty = 1;
	int k = AC->lastAttacker;
	if (ST->kingOfTheHill == 1) {   /* every one for themselves */
		if (k != i) {
			int frags, points;
			if (AC->isKing == 1) {   /* the marked one: five times */
				frags = 5;
				points = ST->suddenDeath == 1 ? FRAG_POINTS(AC->grade) * 5 / 2 : FRAG_POINTS(AC->grade) * 5;
			} else {
				frags = 1;
				points = FRAG_POINTS(AC->grade);
			}
			award(s, k, frags, points);
			if (AC->lastAttacker == ST->playerActor) {
				if (AC->isKing == 1) {
					if (ST->showExp == 1)
						stage_print(s, (const char *)STR(0x4b44f8, "YOU FRAGED KING %s, +1(x%d) FRAGS +%d..."), 5, AC->name, points, 5);
					else
						stage_print(s, (const char *)STR(0x4b44d4, "YOU FRAGED KING %s, +1(x%d) FRAGS"), AC->name, 5);
					ST->kingActor = -1;
				} else if (ST->showExp == 1)
					stage_print(s, (const char *)STR(0x4b44c4, "+1 FRAG +%d EXP"), points);
				else
					stage_print(s, (const char *)STR(0x4b44bc, "+1 FRAG"));
			}
		} else {
			AC->kills--;
			stage_print(s, (const char *)STR(0x4b44b4, "-1 FRAG"));
		}
	} else if (ST->platoon == 1) {   /* teams, the leader down: each of the other team gets the team's worth */
		if (AC->isCommander == 1) {
			int n = 0, sum = 0, count = ST->actorCount;
			for (int j = 0; j < count; j++)
				if (ST->actors[j].team == AC->team) {
					n++;
					sum += FRAG_POINTS(ST->actors[j].grade);
				}
			for (int j = 0; j < ST->actorCount; j++)
				if (ST->actors[j].team >= 0 && ST->actors[j].team != AC->team)
					award(s, j, n, sum);
			int lt = ST->actors[ST->playerActor].team;
			if (lt >= 0 && lt != AC->team) {
				if (ST->showExp == 1)
					stage_print(s, (const char *)STR(0x4b447c, "YOU FRAGED COMMANDER %s, +1(x%d) FRAG..."), AC->name, n, sum);
				else
					stage_print(s, (const char *)STR(0x4b4450, "YOU FRAGED COMMANDER %s, +1(x%d) FRAG(S)"), AC->name, n);
			} else if (lt == AC->team)
				stage_print(s, (const char *)STR(0x4b442c, "YOUR COMMANDER %s HAS BEEN KILLED!"), AC->name);
			if (AC->team == 0)
				ST->frags[1] += n;
			else
				ST->frags[0] += n;
			ST->teamCommanders[AC->team] = -1;
		}
	} else if (k != i) {   /* teams */
		int lv = AC->grade;
		int points = ST->suddenDeath == 1 ? FRAG_POINTS(lv) / 2 : FRAG_POINTS(lv);
		if (ST->actors[k].grade > lv + 3)   /* half for a much weaker one */
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
		if (ST->teamGame == 1)
			ST->frags[AC->team]--;
	}
	if (AC->lastAttacker != i)
		AC->deaths++;
	(*(int *)&ST->lockHeld[i]) = 0;
	AC->killPending = 1;
	ST->lastDeath = i;
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
	float scratch[3], dir[3], slide[3], hit[3], hit_t[3], mv_pos[3], mv_dist[3], mv_plane[4], moveLeft, grip[3];
	float ungrip[16], grip_shift[16], muzzle_m[16], inv_ungrip[16], muzzle_inv[16], shot_at[3], shot_dir[3];
	u32 fx[13];
	u8 *a = (u8 *)&ST->actors[i];
	u8 *player = (u8 *)&ST->playerRecords[AC->player];
	PlayerRecord *pr = (PlayerRecord *)player;
	if (AC->spawnAge > AC->dropAge) {   /* not run or heard from for 10 s, or dead: dropped */
		actor_deactivate((Stage *)s, i);
		if (ST->cockpitActor == i)
			ST->cockpitActor = -1;
		return;
	}
	if (AC->controlledBy != ST->playerActor || AC->bot != 0)
		actor_clearInput(s, i);
	const ChestType *chest = &ST->chestTypes[pr->parts[1]];
	const ArmType *arms = &ST->armTypes[pr->parts[2]];
	const LegType *legs = &ST->legTypes[pr->parts[3]];
	const BoosterType *booster = &ST->boosterTypes[pr->parts[4]];
	if (AC->lowDetail != AC->lowDetailLoaded) {
		actor_loadHead(s, i);
		actor_loadBody(s, i);
		actor_loadArms(s, i);
		actor_loadLegs(s, i);
		actor_loadBooster(s, i);
		AC->lowDetailLoaded = AC->lowDetail;
	}
	int item = pr->items[AC->slot];
	ActorItem *weapon = (ActorItem *)(item >= 0 ? (u8 *)&ST->actorItems[item] : NULL);
	if (AC->controlledBy == ST->playerActor && weapon && AC->ammo[weapon->ammoType] < weapon->ammoPerShot
	    && !(AC->weaponRaise < 1.0f)) {   /* out of ammunition: the next weapon */
		actor_nextWeapon(s, i);
		weapon = &ST->actorItems[pr->items[AC->slot]];
	}
	if (AC->inWeaponSlot >= 0)
		actor_selectWeapon((Stage *)s, i, AC->inWeaponSlot);
	if (AC->inPrevWeapon == 1)
		actor_prevWeapon(s, i);
	if (AC->inNextWeapon == 1)
		actor_nextWeapon(s, i);
	if (i == ST->cockpitActor) {
		if (AC->variantLoaded != 0) {
			AC->variantLoaded = 0;
			actor_loadWeapon(s, i, AC->slot, 0);
		}
	} else if (AC->variantLoaded != AC->lowDetail + 1) {
		AC->variantLoaded = AC->lowDetail + 1;
		actor_loadWeapon(s, i, AC->lastWeaponSlot, AC->variantLoaded);
		actor_loadWeapon(s, i, 4, AC->variantLoaded);
		actor_loadWeapon(s, i, 5, AC->variantLoaded);
	}
	if (AC->controlledBy != ST->playerActor && AC->weaponLowering == 0 && AC->switchSlot != AC->slot) {
		AC->switchSlot = AC->slot;
		actor_loadWeapon(s, i, AC->slot, AC->variantLoaded);
	}
	ObjectList *model = (ObjectList *)(AC->slot == 4 ? (u8 *)&AC->weaponModel4 : AC->slot == 5 ? (u8 *)&AC->weaponModel5 : (u8 *)&AC->weaponModel);
	memcpy(AC->pos, a + (AC->state == 1 ? 0x180 : 0x4e0), 12);
	memcpy(a + offsetof(Player, pitch), a + offsetof(Player, nextPitch), 32);   /* pitch .. : the next motion state taken */
	if (AC->controlledBy == ST->playerActor) {   /* (to chunk N: the local team's actors) */
		if (ST->kingOfTheHill == 1) {
			if (AC->isKing == 1)
				BITS(AC->timers[0]) = BITS(AC->timers[2]) = 0x447a0000;   /* 1000 */
			else {
				if (AC->timers[0] > *k_30f)
					AC->timers[0] = 0.0f;
				if (AC->timers[2] > *k_30f)
					AC->timers[2] = 0.0f;
			}
		}
		AC->botNeeds = 0;
		if (AC->bot != 0) {
			if (AC->armor < ftol(fmul_m((long double)AC->armorMax, k_0_3f)))   /* under 0.3 of its armour */
				AC->botNeeds = 1;
			ActorItem *w0 = &ST->actorItems[pr->items[0]];
			if (AC->ammo[w0->ammoType] < w0->ammoPerShot && pr->items[4] >= 0) {
				ActorItem *w1 = &ST->actorItems[pr->items[4]];
				if (AC->ammo[w1->ammoType] < w1->ammoPerShot)
					(*(u8 *)&AC->botNeeds) |= 2;   /* both weapons empty */
			}
		}
		/* a bullet of another team aimed at it */
		int aimed = 0;
		for (int k = 0; k < ST->bulletSlotsUsed; k++) {
			Bullet *b = &ST->bullets[k];
			if (b->homingTarget != i || ST->actors[b->owner].controlledBy == ST->playerActor)
				continue;
			aimed = 1;
			if (AC->homedOn == 0 && AC->bot != 0 && AC->botTarget < 0) {
				int t = ST->bullets[k].owner;
				if (ST->actors[t].team != AC->team && ST->actors[t].state == 1 && (!(ST->actors[t].stateFlags & 0x200) || ST->actors[t].hackingLevel < AC->hackingLevel)) {
					AC->botTarget = t;
					AC->botTargetTime = 10.5f;   /* 10.5 */
					actor_pickRandomWeapon(s, i);
				}
			}
			break;
		}
		AC->homedOn = aimed;
		if (i == ST->playerActor) {   /* the warning beep */
			if (aimed == 1) {
				long double v = fsub_m(fld_m(&AC->beepTimer), dt);
				AC->beepTimer = (float)v;
				if (!(v >= 0)) {
					sound_playVolume(0x11, 100);
					AC->beepTimer = 0.5f;
				}
			} else
				AC->beepTimer = 0.0f;
		}
		if (AC->botTarget >= 0 && ST->actors[AC->botTarget].state != 1) {
			AC->botTarget = -1;
			AC->botTargetTime = 0.0f;
		}
		if (AC->bot != 0) {   /* a bot: its target */
			long double v = fsub_m(fld_m(&AC->scanTime), dt);
			AC->scanTime = (float)v;
			int k = AC->lastAttacker;
			if (AC->hitFlash > 0 && k != i && ST->actors[k].team != AC->team && ST->actors[k].state == 1 && AC->botTarget != k
			    && (!(ST->actors[k].stateFlags & 0x200) || ST->actors[k].hackingLevel < AC->hackingLevel)) {   /* the one who hit it */
				AC->botTarget = k;
				AC->botTargetTime = 10.5f;
				actor_pickRandomWeapon(s, i);
			} else if (!(v > 0) && !((*(u8 *)&AC->botNeeds) & 2)) {
				if (AC->botTarget < 0) {   /* the first other team's actor in sight within its range (+0) */
					for (int j = 0; j < ST->actorCount; j++) {
						if (j == i || ST->actors[j].state != 1 || ST->actors[j].team == AC->team || ((ST->actors[j].stateFlags & 0x200) && ST->actors[j].hackingLevel >= AC->hackingLevel))
							continue;
						float d[3];
						const float *at = &ST->actors[j].pos[0];
						for (int c = 0; c < 3; c++)
							d[c] = f32(FSUB(at[c], AC->pos[c]));
						memcpy(scratch, d, 12);
						long double dist = FMUL(d[0], d[0]) + FMUL(d[2], d[2]);
						dist = dist + FMUL(d[1], d[1]);
						if (!(dist > AC->detectionRangeSq) && collision_rayTrace(s, &AC->pos[0], at, scratch) == 0) {
							AC->botTarget = j;
							break;
						}
					}
					if (AC->botTarget >= 0)
						actor_pickRandomWeapon(s, i);
				} else {
					int t = AC->botTarget;
					if (collision_rayTrace(s, &AC->pos[0], &ST->actors[t].pos[0], scratch) != 0
					    || ((ST->actors[AC->botTarget].stateFlags & 0x200) && ST->actors[AC->botTarget].hackingLevel >= AC->hackingLevel)) {   /* lost from sight */
						if (!(AC->botTargetTime > 0))
							AC->botTarget = -1;
						else
							for (int j = 0; j < ST->actorCount; j++) {
								if (j == i || ST->actors[j].state != 1 || ST->actors[j].team == AC->team
								    || ((ST->actors[j].stateFlags & 0x200) && ST->actors[j].hackingLevel >= AC->hackingLevel))
									continue;
								if (collision_rayTrace(s, &AC->pos[0], &ST->actors[j].pos[0], scratch) == 0) {
									AC->botTarget = j;
									actor_pickRandomWeapon(s, i);
									break;
								}
							}
					}
				}
				AC->scanTime = 0.5f;   /* 0.5 */
			}
			if (AC->botTarget >= 0 && ST->botsHoldFire == 0) {   /* fire in bursts */
				v = fsub_m(fld_m(&AC->burstPause), dt);
				AC->burstPause = (float)v;
				if (!(v > 0)) {
					if (AC->burstFire > 0) {
						AC->inFire = 1;
						AC->burstFire = f32(fsub_m(fld_m(&AC->burstFire), dt));
					} else {
						BITS(AC->burstPause) = BITS(AC->botTimes[3]);
						BITS(AC->burstFire) = BITS(AC->botTimes[4]);
					}
				}
			}
		}
		/* the path: stuck (moved under 500 in a second) */
		AC->stuckTime = f32(fsub_m(fld_m(&AC->stuckTime), dt));
		for (int c = 0; c < 3; c++)
			AC->stuckMove[c] = f32(FADD(AC->move[c], AC->stuckMove[c]));
		if (!(AC->stuckTime > 0)) {
			if (AC->path >= 0) {
				long double x = fld_m(&AC->stuckMove[0]), y = fld_m(&AC->stuckMove[1]), z = fld_m(&AC->stuckMove[2]);
				if (!((x * x + y * y) + z * z >= *&k_250000f)) {
					AC->stuckPath = AC->path;
					AC->path = -1;
				}
			}
			AC->stuckTime = 1.0f;
			memcpy(AC->stuckMove, (const void *)ADDR(g_vecZero), 12);
		}
		if (AC->bot == 1 && AC->path < 0 && (AC->botTarget < 0 || ((*(u8 *)&AC->botNeeds) & 3))) {
			actor_pickPathPoint(s, i);
			if ((*(u8 *)&AC->botNeeds) & 2)
				AC->botTarget = -1;
		}
		if (AC->lookActor >= 0 && ST->actors[AC->lookActor].state != 1)
			AC->lookActor = -1;
		if (AC->followTarget >= 0 && ST->actors[AC->followTarget].state != 1)
			AC->followTarget = -1;
		if (AC->path >= 0) {   /* the scripted path (path, its point pathPoint): its command when within 1000 */
			const float *pt = PATH_POINT(AC->path, AC->pathPoint);
			float d[3];
			for (int c = 0; c < 3; c++)
				d[c] = f32(FSUB(pt[c], AC->pos[c]));
			memcpy(scratch, d, 12);
			long double dist = FMUL(d[0], d[0]) + FMUL(d[2], d[2]);
			if (!(dist + FMUL(d[1], d[1]) >= *&k_1000000f)) {
				script_processCommandBy(s, i, AC->path, AC->pathPoint);
				int at = AC->pathPoint;
				if (AC->pathReverse == 0) {   /* forwards, or backwards */
					if (at < ST->triggers[AC->path].wayPointCount - 1)
						AC->pathPoint = at + 1;
					else
						AC->path = AC->pathPoint = -1;
				} else if (AC->pathPoint > 0)
					AC->pathPoint = AC->pathPoint - 1;
				else
					AC->path = AC->pathPoint = -1;
			}
		}
		if (AC->bot == 1 && AC->path >= 0 && AC->botTarget >= 0 && !((*(u8 *)&AC->botNeeds) & 1))
			AC->path = -1;
		if (AC->botWait > 0)
			AC->botWait = f32(fsub_m(fld_m(&AC->botWait), dt));
		if (AC->botWaitTrigger >= 0 && ST->triggerFired[AC->botWaitTrigger] == 1)
			AC->botWaitTrigger = -1;
		if (AC->bot != 0 && !(AC->botWait > 0) && AC->botWaitTrigger < 0) {   /* a bot: where it goes (botGoal) and looks */
			if (AC->followTarget >= 0) {   /* the one it follows: towards it while over 3000 away */
				const float *at = &ST->actors[AC->followTarget].pos[0];
				float d[3];
				for (int c = 0; c < 3; c++)
					d[c] = f32(FSUB(at[c], AC->pos[c]));
				memcpy(scratch, d, 12);
				long double dist = FMUL(d[0], d[0]) + FMUL(d[2], d[2]);
				memcpy(AC->botGoal, dist + FMUL(d[1], d[1]) > *&k_9000000f ? (const void *)RELOC(at) : (const void *)AC->pos, 12);
			} else if (AC->path >= 0) {   /* its path's point while over 1000 away */
				const float *pt = PATH_POINT(AC->path, AC->pathPoint);
				float d[3];
				for (int c = 0; c < 3; c++)
					d[c] = f32(FSUB(pt[c], AC->pos[c]));
				memcpy(scratch, d, 12);
				long double dist = FMUL(d[2], d[2]) + FMUL(d[1], d[1]);
				memcpy(AC->botGoal, dist + FMUL(d[0], d[0]) > *&k_1000000f ? (const void *)PATH_POINT(AC->path, AC->pathPoint) : (const void *)AC->pos, 12);
			} else if (AC->botTarget >= 0) {   /* about its target: sideways by a random amount, now and then */
				long double v = fsub_m(fld_m(&AC->dodgeTime), dt);
				AC->dodgeTime = (float)v;
				if (!(v > 0)) {
					int t = AC->botTarget;
					float d[3], tmp[3];
					for (int c = 0; c < 3; c++)
						tmp[c] = f32(FSUB(AC->pos[c], ST->actors[t].pos[c]));
					memcpy(d, tmp, 12);
					Vec3_normalize(d);
					d[0] = f32(FMUL(d[0], AC->botTimes[2]));
					d[1] = 0;
					long double z = FMUL(d[2], AC->botTimes[2]);
					d[2] = (float)z;
					scratch[0] = f32(-fmul_m(z, &g_vecUnitY[1]));   /* (d x the unit Y vector) */
					scratch[1] = f32(FMUL(d[2], g_vecUnitY[0]) - FMUL(d[0], g_vecUnitY[2]));
					scratch[2] = f32(FMUL(d[0], g_vecUnitY[1]));
					Vec3_normalize(scratch);
					int n = ftol(fld_m(&AC->dodgeSpread)) * 2;
					int r = n > 0 ? (int)rand_below(n) : 0;
					long double o = fsub_m((long double)r, &AC->dodgeSpread);
					scratch[0] = f32(fmul_m(o, &scratch[0]));
					scratch[2] = f32(fmul_m(o, &scratch[2]));
					AC->botGoal[0] = f32(fadd_m(FADD(scratch[0], ST->actors[AC->botTarget].pos[0]), &d[0]));
					BITS(AC->dodgeTime) = BITS(AC->botTimes[0]);
					AC->botGoal[2] = f32(fadd_m(FADD(scratch[2], ST->actors[AC->botTarget].pos[2]), &d[2]));
				}
				v = fsub_m(fld_m(&AC->heightTime), dt);
				AC->heightTime = (float)v;
				if (!(v > 0)) {   /* and up or down */
					int n = ftol(fld_m(&AC->climbSpread)) * 2;
					int r = n > 0 ? (int)rand_below(n) : 0;
					BITS(AC->heightTime) = BITS(AC->botTimes[1]);
					AC->botGoal[1] = f32(fsub_m(fadd_m((long double)r, &AC->pos[1]), &AC->climbSpread));
				}
			}
			/* the view (botLookPitch, botLookYaw): at what it attends to, or a random look every 2 s */
			if (AC->lookActor >= 0)
				aim_at(a, &ST->actors[AC->lookActor].pos[0]);
			else if (AC->lookPath >= 0)
				aim_at(a, PATH_POINT(AC->lookPath, AC->lookPoint));
			else if (AC->followTarget >= 0)
				aim_at(a, &ST->actors[AC->followTarget].pos[0]);
			else if (AC->botTarget >= 0)
				aim_at(a, &ST->actors[AC->botTarget].pos[0]);
			else if (AC->path >= 0)
				aim_at(a, PATH_POINT(AC->path, AC->pathPoint));
			else {
				long double v = fsub_m(fld_m(&AC->lookTime), dt);
				AC->lookTime = (float)v;
				if (!(v > 0)) {
					AC->botLookPitch = (float)(int)(rand_below(900) - 450);
					AC->lookTime = 2.0f;   /* 2 */
					AC->botLookYaw = (float)(int)rand_below(3600);
				}
			}
			/* the movement keys towards the goal, in the actor's own frame: forward / back / right / left (inForward ..),
			   or up / down (inAltitude with forward or back) when that is the larger way, beyond 500 */
			for (int c = 0; c < 3; c++)
				scratch[c] = f32(FSUB(AC->botGoal[c], AC->pos[c]));
			Vec3_rotateAxis(scratch, 2, -ftol(fld_m(&AC->yaw)));
			Vec3_rotateAxis(scratch, 1, -ftol(fld_m(&AC->pitch)));
			long double len = x87_fsqrt((FMUL(scratch[0], scratch[0]) + FMUL(scratch[2], scratch[2])) + FMUL(scratch[1], scratch[1]));
			if (len > 500.0f) {
				long double G = fld_m(&scratch[0]), Y = fld_m(&scratch[1]), Z = fld_m(&scratch[2]);
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
			/* the turns towards the view, at most the turn rate (turnRate) a second */
			float rate = f32(fmul_m(fld_m(dt), &AC->turnRate));
			for (int c = 0; c < 2; c++) {
				long double r = angle_turn(AU(offsetof(Player, pitch) + c * 4), AU(offsetof(Player, botLookPitch) + c * 4));
				float rr = (float)r;
				AF(offsetof(Player, inPitch) + c * 4) = rr;
				if (r > rate)
					AU(offsetof(Player, inPitch) + c * 4) = BITS(rate);
				else if (!(rr >= -fld_m(&rate)))
					AF(offsetof(Player, inPitch) + c * 4) = (float)-fld_m(&rate);
			}
		}
		if (AC->bot == 1)
			AC->inBooster = 1;
	}
	switch (AC->cheat) {   /* a cheat code to apply */
	case 0:
		AC->armor = ((u32)AC->armorMax);
		AC->shield = ((u32)AC->shieldMax);
		break;
	case 1:
		memcpy(AC->ammo, AC->ammoMax, 16);
		break;
	case 2:
		AC->bigHead = 1;
		break;
	case 3:
		AC->bigHead = 0;
		break;
	case 4:
		AC->deaths++;
		actor_takeDamage(s, i, i, 1, AC->armor, 0, -1);
		break;
	}
	AC->cheat = -1;
	float speed = f32(fmul_m(fld_m(dt), &AC->mobility));
	if (AC->inBooster == 1)
		speed = f32(fld_m(&speed) + fld_m(&speed));
	float accel = f32(fmul_m(fld_m(dt), &AC->moveAccel));
	float want[3];   /* the wanted velocity from the keys, turned to the actor's facing */
	want[2] = 0;
	want[0] = f32(FMUL(AC->strafe, AC->speed));
	want[1] = f32(FMUL(AC->forward, AC->speed));
	Vec3_rotateAxis(want, 1, ftol(FSUB(k_1f, AC->climb) * FADD(AC->pitch, k_900f)));
	Vec3_rotateAxis(want, 2, ftol(fld_m(&AC->yaw)));
	float neg = f32(-fld_m(&accel));
	for (int c = 0; c < 3; c++) {   /* the velocity towards it by at most accel */
		long double v = FSUB(AC->velocity[c], want[c]);
		if (!(v >= neg))
			AC->velocity[c] = f32(FADD(accel, AC->velocity[c]));
		else if (v > accel)
			AC->velocity[c] = f32(FSUB(AC->velocity[c], accel));
		else
			BITS(AC->velocity[c]) = BITS(want[c]);
	}
	float step = !(*dt >= 0.05f) ? *dt : 0.05f;   /* at most 0.05 s */
	for (int c = 0; c < 3; c++)   /* the move this frame */
		AC->move[c] = f32(FMUL(step, AC->velocity[c]));
	if (AC->controlledBy == ST->playerActor && AC->state == 1 && AC->hitFlash > 0) {   /* a push, fading with hitFlash squared */
		long double px = FMUL(step, AC->push[0]);
		float py = f32(FMUL(step, AC->push[1]));
		float pz = f32(FMUL(step, AC->push[2]));
		long double f = fld_m(&AC->hitFlash);
		float sq = f32(f * f);
		px = fmul_m(px, &sq);
		py = f32(FMUL(py, sq));
		pz = f32(FMUL(pz, sq));
		AC->move[0] = f32(fadd_m(px, &AC->move[0]));
		AC->move[1] = f32(FADD(py, AC->move[1]));
		AC->move[2] = f32(FADD(pz, AC->move[2]));
	}
	if (AC->overheat == 1)
		AC->inBooster = 0;
	if (AC->controlledBy == ST->playerActor && AC->state == 1) {   /* (to 45a5d1) the local team's live actors move */
		AC->nextPos[0] = f32(FADD(AC->pos[0], AC->move[0]));
		AC->nextPos[1] = f32(FADD(AC->move[1], AC->pos[1]));
		AC->nextPos[2] = f32(FADD(AC->move[2], AC->pos[2]));
		memcpy(dir, AC->move, 12);
		moveLeft = f32(Vec3_normalize(dir));
		for (int j = 0; j < ST->actorCount; j++) {   /* slide around the other live actors */
			if (ST->actors[j].state != 1 || j == i || ST->actors[j].outOfPlay != 0)
				continue;
			float r = f32(fmul_m(FADD(ST->actors[j].radius, AC->radius), &k_0_75f));
			if (math_segmentSphere(AC->pos, AC->nextPos, dir, &ST->actors[j].pos[0], r, hit, hit_t) != 1)
				continue;
			memcpy(AC->nextPos, hit, 12);
			for (int c = 0; c < 3; c++)
				AC->move[c] = f32(FSUB(AC->nextPos[c], AC->pos[c]));
			long double X = fld_m(&AC->move[0]), Y = fld_m(&AC->move[1]), Z = fld_m(&AC->move[2]);
			moveLeft = f32(fsubr_m(x87_fsqrt((X * X + Y * Y) + Z * Z), &moveLeft));
			const float *o = &ST->actors[j].pos[0];
			long double d0 = FSUB(hit[0], o[0]), d1 = FSUB(hit[1], o[1]), d2 = FSUB(hit[2], o[2]);
			float c0 = f32(fmul_m(d2, &dir[1]) - fmul_m(d1, &dir[2]));
			float c1 = f32(fmul_m(d0, &dir[2]) - fmul_m(d2, &dir[0]));
			long double c2 = fmul_m(d1, &dir[0]) - fmul_m(d0, &dir[1]);
			/* along the sphere: (d x dir) x d (slide doubles as the move's velocity out) */
			slide[0] = f32(c2 * d1 - fmul_m(d2, &c1));
			slide[1] = f32(fmul_m(d2, &c0) - c2 * d0);
			slide[2] = f32(fmul_m(d0, &c1) - fmul_m(d1, &c0));
			Vec3_normalize(slide);
			for (int c = 0; c < 3; c++)
				slide[c] = f32(FMUL(slide[c], moveLeft));
			for (int c = 0; c < 3; c++)
				AC->nextPos[c] = f32(FADD(slide[c], AC->nextPos[c]));
			for (int c = 0; c < 3; c++)
				dir[c] = AC->move[c] = f32(FSUB(AC->nextPos[c], AC->pos[c]));
			moveLeft = f32(Vec3_normalize(dir));
		}
		float r = AC->radius;
		int moved = collision_moveActor(s, r, AC->pos, AC->move, BITS(r), 0, mv_pos, slide, mv_dist, mv_plane, 0);
		memcpy(AC->nextPos, mv_pos, 12);
		if (moved == 1)
			for (int c = 0; c < 3; c++)
				AC->nextPos[c] = f32(FADD(slide[c], AC->nextPos[c]));
		for (int c = 0; c < 3; c++) {   /* inside the world box */
			const float *lo = &ST->levelLow[c], *hi = &ST->levelHigh[c];
			if (!(AC->nextPos[c] >= *lo))
				BITS(AC->nextPos[c]) = BITS(*lo);
			else if (AC->nextPos[c] > *hi)
				BITS(AC->nextPos[c]) = BITS(*hi);
		}
		long double v = FADD(AC->inPitch, AC->pitch);   /* the pitch, within +-89 degrees */
		AC->nextPitch = (float)v;
		if (v > *&k_890f)
			AC->nextPitch = 890.0f;   /* 890 */
		if (!(AC->nextPitch >= *&k_m890f))
			AC->nextPitch = -890.0f;
		AC->nextYaw = f32(FADD(AC->inYaw, AC->yaw));
		float fwd, back, left, right;   /* the top speeds: 1 / -1 walking, runTop running (stepping left goes to +) */
		if (AC->inBooster == 0) {
			fwd = 1.0f;
			back = -1.0f;
			left = 1.0f;
			right = -1.0f;
		} else {
			fwd = AC->runTop[0];
			back = AC->runTop[1];
			left = AC->runTop[2];
			right = AC->runTop[3];
		}
		key_axis(&AC->nextForward, AC->inForward, AC->inBackward, fwd, back, speed);
		key_axis(&AC->nextStrafe, AC->inStepLeft, AC->inStepRight, left, right, speed);
		key_ramp(&AC->nextClimb, AC->inAltitude == 1, speed);
		key_ramp(&AC->nextRun, AC->inBooster == 1, speed);
		/* the body's lean (nextLean) from the forward speed and the pitch */
		long double m, w;
		if (!(AC->nextForward >= 0)) {
			m = AC->nextForward > -1.0f ? fld_m(&AC->nextForward) : -1.0L;
			w = fmul_m(fmul_m(fsub_m(900.0L, &AC->nextPitch), &k_0_0005555556f) * m, &k_150f);
			AC->nextLean = (float)w;
		} else if (!(AC->nextPitch >= 0)) {
			m = !(AC->nextForward >= 1.0f) ? fld_m(&AC->nextForward) : 1.0L;
			w = fmul_m(fmul_m(FADD(AC->nextPitch, k_900f), &k_0_001111111f) * m, &k_450f);
			AC->nextLean = (float)w;
		} else {
			m = !(AC->nextForward >= 1.0f) ? fld_m(&AC->nextForward) : 1.0L;
			w = fmul_m(m, &k_450f);
			AC->nextLean = (float)w;
			if (AC->nextForward > 1.0f)
				AC->nextLean = (float)(fmul_m(FSUB(AC->nextForward, k_1f), &AC->nextPitch) / FSUB(AC->runTop[0], k_1f) + w);
		}
		AC->nextLean = f32(fmul_m(fmul_m(FADD(AC->nextRun, k_1f), &k_0_5f) * FSUB(k_1f, AC->climb), &AC->nextLean));
	} else {   /* the others: towards their sent state at 6.66 a second */
		long double f = fmul_m(fld_m(dt), &k_6_66f);
		float k = (float)f;
		if (f > 1.0L)
			k = 1.0f;
		long double x = FSUB(AC->netPos[0], AC->pos[0]);
		float y = f32(FSUB(AC->netPos[1], AC->pos[1]));
		float z = f32(FSUB(AC->netPos[2], AC->pos[2]));
		x = fmul_m(x, &k);
		y = f32(FMUL(k, y));
		z = f32(FMUL(k, z));
		AC->nextPos[0] = f32(fadd_m(x, &AC->pos[0]));
		AC->nextPos[1] = f32(FADD(y, AC->pos[1]));
		AC->nextPos[2] = f32(FADD(z, AC->pos[2]));
		AC->nextPitch = f32(fadd_m(fmul_m(FSUB(AC->netPitch, AC->pitch), &k), &AC->pitch));
		AC->nextYaw = f32(angle_stepTowards(BITS(AC->nextYaw), BITS(AC->netYaw), BITS(k)));
		for (int c = 0; c < 5; c++)   /* nextForward..nextRun */
			AF(offsetof(Player, nextForward) + c * 4) = f32(fadd_m(fmul_m(FSUB(AC->netMotion[c], AF(offsetof(Player, forward) + c * 4)), &k), &AF(offsetof(Player, forward) + c * 4)));
	}
	if (AC->fireAnim > 0 && weapon) {   /* the firing cycle, wrapping at 1 */
		long double v = fadd_m(fdiv_m(fld_m(dt), &weapon->cycleTime), &AC->fireCycle);
		AC->fireCycle = (float)v;
		if (v >= 1.0L)
			AC->fireCycle = 0;
	}
	if (AC->outOfPlay != 0)
		goto tail;   /* 45cdb1 */
	if (AC->weaponLowering == 1) {   /* the weapon going down (weaponRaise from 1 to 0) */
		if (AC->weaponRaise > 0) {
			if (BITS(AC->weaponRaise) == 0x3f800000 && i == ST->playerActor)
				sound_playVolume(0x14, 0x64);
			AC->weaponRaise = f32(fsubr_m(fmul_m(fld_m(dt), &k_3f), &AC->weaponRaise));
		}
		if (!(AC->weaponRaise > 0))
			AC->weaponLowering = (*(int *)&AC->weaponRaise) = 0;
	} else if (AC->weaponLowering == 0) {   /* the next one coming up */
		if (!(AC->weaponRaise > 0)) {
			actor_setWeaponSlot((Stage *)s, i, AC->switchSlot);
			actor_loadWeapon(s, i, AC->switchSlot, AC->variantLoaded);
			weapon = &ST->actorItems[pr->items[AC->slot]];
			model = (ObjectList *)(AC->slot == 4 ? (u8 *)&AC->weaponModel4 : AC->slot == 5 ? (u8 *)&AC->weaponModel5 : (u8 *)&AC->weaponModel);
			AC->ammoKind = ((u32)weapon->ammoType);
		}
		if (!(AC->weaponRaise >= 1.0f)) {
			int kind = pr->items[AC->slot];
			AC->weaponRaise = f32(fadd_m(fmul_m(fld_m(dt), K(kind == 11 ? ADDR(k_1_95f) : kind == 3 ? ADDR(k_2_25f) : ADDR(k_3f))), &AC->weaponRaise));
			if (AC->weaponRaise >= 1.0f)
				AC->weaponRaise = 1.0f;
		}
	}
	/* the body's pose: the swing, lean and head turn, and its animation frames */
	clamp450(&AC->pose[0], FMUL(AC->strafe, k_m200f));
	AC->pose[1] = f32(fmul_m(fmul_m(FSUB(k_1f, AC->climb) * FADD(AC->pitch, k_900f), &AC->boosterTilt), &k_0_0005555556f));
	clamp450(&AC->pose[2], FMUL(AC->strafe, k_200f));
	AC->pose[3] = f32(fmul_m(fadd_m(FSUB(AC->pitch, AC->lean), &k_900f), &k_0_0005555556f));
	long double side = !(AC->forward >= -1.0f) ? -1.0L : AC->forward > 1.0f ? 1.0L : fld_m(&AC->forward);
	AC->pose[4] = f32(fmul_m(fsubr_m(fmul_m(FADD(AC->run, k_1f), &k_0_5f) * FSUB(k_1f, AC->climb) * side, &k_1f), &k_0_5f));
	BITS(AC->pose[5]) = BITS(AC->run);
	anim_setSkeleton((u8 *)&AC->headModel, 0, BITS(AC->pose[3]));
	anim_setSkeleton((u8 *)&AC->chestModel, 0, BITS(AC->pose[3]));
	anim_setSkeleton((u8 *)&AC->armsModel, 0, BITS(AC->pose[3]));
	anim_setSkeleton((u8 *)&AC->legsModel, 0, BITS(AC->pose[4]));
	anim_setSkeleton((u8 *)&AC->boosterModel, 0, BITS(AC->pose[5]));
	anim_setSkeleton((u8 *)model, 0, BITS(AC->fireAnim));
	/* the matrices: the body at the actor, turned and leant, the head on its neck, the arms */
	glPushMatrix();
	glTranslatef_bits(BITS(AC->pos[0]), BITS(AC->pos[1]), BITS(AC->pos[2]));
	glRotatef(f32(FMUL(AC->yaw, k_tenthsToDegrees)), 0, 1, 0);
	glRotatef(f32(FMUL(AC->lean, k_tenthsToDegrees)), 1, 0, 0);
	glGetFloatv(0xba6, AC->bodyMatrix);
	skel_poseBones((u8 *)&AC->chestModel, AC->bodyMatrix);
	glLoadMatrixf((const float *)(uintptr_t)((u32)AC->chestModel.entries + chest->legsJoint[AC->lowDetail] * 100 + 0xc));
	glRotatef(f32(FMUL(AC->pose[2], k_tenthsToDegrees)), 0, 1, 0);
	skel_poseBones((u8 *)&AC->legsModel, 0);
	glLoadMatrixf(part_matrix((u8 *)&AC->chestModel.entries, chest->armsJoint, AC->lowDetail));
	skel_poseBones((u8 *)&AC->armsModel, 0);
	glLoadMatrixf(part_matrix((u8 *)&AC->chestModel.entries, chest->headJoint, AC->lowDetail));
	if (((u32)AC->stateFlags) & 0x1000)
		glScalef_bits(0x40a00000, 0x40a00000, 0x40a00000);   /* 5 */
	skel_poseBones((u8 *)&AC->headModel, 0);
	glLoadMatrixf(part_matrix((u8 *)&AC->chestModel.entries, chest->boosterJoint, AC->lowDetail));
	glRotatef(f32(fmul_m(fld_m(&AC->pose[0]), k_0_05f)), 0, 0, 1);
	glRotatef(f32(FMUL(AC->pose[1], k_tenthsToDegrees)), 1, 0, 0);
	skel_poseBones((u8 *)&AC->boosterModel, 0);
	memcpy(grip, &g_vecZero, 12);   /* where the weapon is held, for the local player's view */
	glLoadMatrixf(part_matrix((u8 *)&AC->armsModel.entries, arms->weaponJoints[0], AC->lowDetail));
	if (i == ST->cockpitActor && weapon && AC->slot <= 3)
		hold(grip, (const u8 *)weapon->sets[0].grip[AC->variantLoaded], 0, &AC->weaponRaise);
	skel_poseBones((u8 *)&AC->weaponModel, 0);
	glLoadMatrixf(part_matrix((u8 *)&AC->armsModel.entries, arms->weaponJoints[1], AC->lowDetail));
	if (i == ST->cockpitActor && weapon && AC->slot == 4)
		hold(grip, (const u8 *)weapon->sets[0].grip[AC->variantLoaded], 0, &AC->weaponRaise);
	skel_poseBones((u8 *)&AC->weaponModel4, 0);
	glLoadMatrixf(part_matrix((u8 *)&AC->armsModel.entries, arms->weaponJoints[2], AC->lowDetail));
	if (i == ST->cockpitActor && weapon && AC->slot == 5)
		hold(grip, (const u8 *)weapon->sets[1].grip[AC->variantLoaded], 1, &AC->weaponRaise);
	skel_poseBones((u8 *)&AC->weaponModel5, 0);
	glPopMatrix();
	if (i == ST->playerActor) {   /* the local player's locks (lockHeld per actor), sorted longest first (lockTimes / lockIds) */
		float *lock = ST->lockHeld;
		int *count = &ST->lockCount;
		if (weapon && weapon->targetingTime > 0) {
			for (int j = 0; j < ST->actorCount; j++) {
				float *seen = &ST->actors[j].lockAnim;
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
				if (!(FMUL(AC->lockOnTime, weapon->targetingTime) >= ST->actors[j].aimTime) && AC->team != ST->actors[j].team) {
					if (!(lock[j] > 0)) {
						sound_playVolume(0x12, 0x64);
						*seen = 0.25f;
					}
					BITS(lock[j]) = BITS(AC->targetKeepTime);
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
					BITS(ST->lockTimes[*count]) = BITS(lock[j]);
					ST->lockIds[*count] = j;
					++*count;
				}
			float *t = ST->lockTimes;
			if (*count > 0)
				for (int k = 1; k - 1 < *count; k++)
					for (int m = k; m < *count; m++)
						if (!(t[k - 1] >= t[m])) {
							long double was = fld_m(&t[k - 1]);
							BITS(t[k - 1]) = BITS(t[m]);
							t[m] = (float)was;
							int *id = ST->lockIds;
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
	AC->firing = 0;   /* firing this frame */
	AC->sendNow = 0;
	if (AC->controlledBy == ST->playerActor) {
		if (weapon && AC->state == 1) {
			if (AC->inFire == 1 && AC->spawnAge > 3.0f && AC->slot >= 0 && !(AC->fireAnim > 0) && AC->weaponRaise >= 1.0f && AC->weaponLowering == 0
			    && AC->armor > 0)
				AC->firing = 1;
			int shots = 0;   /* this frame's rounds: whole cycles times the burst, and a burst's rounds left (burstLeft, burstTime) */
			const float *cycle = &weapon->cycleTime, *gap = &weapon->burstGap;
			int burst = weapon->burst;
			if (AC->firing == 1) {
				int n = ftol(fdiv_m(fld_m(dt), cycle));
				shots = burst * (n + 1) + AC->burstLeft;
				if (*gap > 0) {
					long double r = fsubr_m(fmul_m((long double)n, cycle), dt);
					int m = ftol(fdiv_m(r, gap)) + 1;
					if (burst > m) {
						AC->burstTime = f32(r - fmul_m((long double)(m - 1), gap));
						AC->burstLeft = burst - m;
						shots -= AC->burstLeft;
					} else
						AC->burstLeft = 0;
				} else
					AC->burstLeft = 0;
			} else if (AC->burstLeft > 0) {
				long double v = fadd_m(fld_m(dt), &AC->burstTime);
				AC->burstTime = (float)v;
				if (v >= *gap) {
					int m = ftol(fdiv_m(v, gap));
					if (m >= AC->burstLeft) {
						shots = AC->burstLeft;
						AC->burstLeft = 0;
						AC->burstTime = 0.0f;
					} else {
						AC->burstLeft -= m;
						shots = m;
						AC->burstTime = f32(fsubr_m(fmul_m((long double)m, gap), &AC->burstTime));
					}
				}
			}
			int quit = 0;
			for (int n = 0; n < shots && !quit; n++) {
				int k = 0;
				while (k < 5 && AC->shotBullets[k] >= 0)
					k++;
				if (k == 5)
					break;
				int w = weapon->ammoType;
				if (AC->ammo[w] < weapon->ammoPerShot && AC->bot != 2) {   /* out of ammunition */
					if (i == ST->playerActor) {
						if (AC->firePrev != 0)
							break;
						strcpy(AC->message, (const char *)STR(0x4b4528, "OUT OF AMMO!"));
						BITS(AC->messageTime) = BITS(*dt);
						sound_playVolume(0xa5, 0x64);
					}
					if (AC->firePrev == 0)
						actor_nextWeapon(s, i);
					break;
				}
				if (w >= 0) {
					const int *muzzle = (const int *)(((u8 *)weapon) + (AC->slot == 5 ? 0x2ca4 : 0x15e8) + AC->variantLoaded * 64);
					skel_applyPose(*(void **)model->skeletons, muzzle_m, muzzle[0], 0);
					Mat4_invert(muzzle_inv, muzzle_m);
					memset(ungrip, 0, 64);   /* the grip undone: grip_shift = muzzle_inv x ungrip x muzzle_m */
					BITS(ungrip[0]) = BITS(ungrip[5]) = BITS(ungrip[10]) = BITS(ungrip[15]) = 0x3f800000;
					ungrip[12] = f32(-fld_m(&grip[0]));
					ungrip[13] = f32(-fld_m(&grip[1]));
					ungrip[14] = f32(-fld_m(&grip[2]));
					Mat4_multiply(inv_ungrip, muzzle_inv, ungrip);
					Mat4_multiply(grip_shift, inv_ungrip, muzzle_m);
					long double r = (long double)(n % burst);   /* this round's offset along the burst (in scratch) */
					scratch[0] = f32(fmul_m(r, &weapon->burstStep[0]));
					scratch[1] = f32(fmul_m(r, &weapon->burstStep[1]));
					scratch[2] = f32(fmul_m(r, &weapon->burstStep[2]));
					long double x = ((FMUL(grip_shift[8], scratch[2]) + FMUL(grip_shift[4], scratch[1])) + FMUL(grip_shift[0], scratch[0])) + grip_shift[12];
					long double y = ((FMUL(grip_shift[9], scratch[2]) + FMUL(grip_shift[5], scratch[1])) + FMUL(grip_shift[1], scratch[0])) + grip_shift[13];
					long double z = ((FMUL(grip_shift[10], scratch[2]) + FMUL(grip_shift[6], scratch[1])) + FMUL(grip_shift[2], scratch[0])) + grip_shift[14];
					const float *q = (const float *)(uintptr_t)((u32)model->entries + muzzle[0] * 100 + 0xc);
					shot_at[0] = f32(((fmul_m(z, &q[8]) + fmul_m(y, &q[4])) + fmul_m(x, &q[0])) + q[12]);
					shot_at[1] = f32(((fmul_m(x, &q[1]) + fmul_m(z, &q[9])) + fmul_m(y, &q[5])) + q[13]);
					shot_at[2] = f32(((fmul_m(x, &q[2]) + fmul_m(z, &q[10])) + fmul_m(y, &q[6])) + q[14]);
					memcpy(shot_dir, &g_vecUnitZ, 12);
					if (AC->bot == 0) {
						Vec3_rotateAxis(shot_dir, 1, ftol(fld_m(&AC->pitch)));
						Vec3_rotateAxis(shot_dir, 2, ftol(fld_m(&AC->yaw)));
					} else {   /* a bot's aim wanders by +-(aimError) */
						u32 sp = (u32)(AC->aimError * 2);
						int r1 = (int)sp > 0 ? (int)rand_below(sp) : 0;
						Vec3_rotateAxis(shot_dir, 1, ftol(fld_m(&AC->pitch)) - AC->aimError + r1);
						int r2 = (int)(u32)(AC->aimError * 2) > 0 ? (int)rand_below((u32)(AC->aimError * 2)) : 0;
						Vec3_rotateAxis(shot_dir, 2, ftol(fld_m(&AC->yaw)) - AC->aimError + r2);
					}
					if (collision_rayTrace(s, AC->pos, shot_at, scratch) != 0) {   /* the muzzle inside a wall */
						if (i == ST->playerActor && AC->firePrev == 0)
							sound_playVolume(0xa5, 0x64);
						break;
					}
					if (AC->bot != 0) {   /* a bot holds fire without a clear line, and swaps weapons when too close */
						const float *tp = &ST->actors[AC->botTarget].pos[0];
						if (collision_rayTrace(s, shot_at, tp, scratch) != 0)
							continue;
						float d[3];
						for (int c = 0; c < 3; c++)
							d[c] = f32(FSUB(tp[c], AC->pos[c]));
						memcpy(scratch, d, 12);
						long double R = fld_m(&weapon->splashRadius);
						long double dd = (FMUL(d[2], d[2]) + FMUL(d[1], d[1])) + FMUL(d[0], d[0]);
						if (R * R > dd) {
							if (AC->slot == 0 && pr->items[4] >= 0)
								actor_selectWeapon((Stage *)s, i, 4);
							else if (AC->slot == 4)
								actor_selectWeapon((Stage *)s, i, 0);
							continue;
						}
					}
					FiredRound *rec = &AC->rounds[k];
					rec->received = 0;
					rec->weapon = pr->items[AC->slot];
					memcpy(rec->from, shot_at, 12);
					rec->hitPlane = -1;
					memcpy(rec->dir, shot_dir, 12);
					rec->muzzle = (u32)(uintptr_t)q;
					int target;
					if (i == ST->playerActor) {
						int c = ST->lockCount;
						target = c > 0 ? ST->lockIds[n % c] : -1;
					} else
						target = AC->botTarget;
					AC->shotBullets[k] = bullet_spawn(s, -1, i, target, rec, n);
					AC->shots[k].isNew = 1;
					if (AC->bot != 2)
						AC->ammo[weapon->ammoType] -= weapon->ammoPerShot;
				}
				AC->fireAnim = 0.0001f;   /* 0.0001: the firing cycle restarts */
				long double v = fdiv_m(fld_m(dt), cycle);
				AC->fireCycle = (float)v;
				if (v >= 1.0L)
					AC->fireCycle = 0;
			}
			AC->firePrev = AC->inFire;
		}
	} else if (weapon && AC->netFired == 1) {   /* the others' rounds, as sent */
		for (int k = 0; k < 5; k++) {   /* per slot (shots[k]): in use, a new round (its kind, owner, flag, direction) */
			int *item = &AC->shotBullets[k];
			u32 *f = (u32 *)&AC->shots[k].isNew;
			if (f[-1] != 1)
				continue;
			if (f[0] == 1) {
				if (*item >= 0)
					bullet_free(s, *item);
				const int *muzzle = (const int *)(((u8 *)weapon) + (AC->slot == 5 ? 0x2ca4 : 0x15e8) + AC->variantLoaded * 64);
				skel_applyPose(*(void **)model->skeletons, muzzle_m, muzzle[0], 0);
				Mat4_invert(muzzle_inv, muzzle_m);
				memset(ungrip, 0, 64);
				BITS(ungrip[0]) = BITS(ungrip[5]) = BITS(ungrip[10]) = BITS(ungrip[15]) = 0x3f800000;
				ungrip[12] = f32(-fld_m(&grip[0]));
				ungrip[13] = f32(-fld_m(&grip[1]));
				ungrip[14] = f32(-fld_m(&grip[2]));
				Mat4_multiply(inv_ungrip, muzzle_inv, ungrip);
				Mat4_multiply(grip_shift, inv_ungrip, muzzle_m);
				const float *o = &g_vecOrigin;
				long double x = ((FMUL(grip_shift[8], o[2]) + FMUL(grip_shift[4], o[1])) + FMUL(grip_shift[0], o[0])) + grip_shift[12];
				long double y = ((FMUL(grip_shift[9], o[2]) + FMUL(grip_shift[5], o[1])) + FMUL(grip_shift[1], o[0])) + grip_shift[13];
				long double z = ((FMUL(grip_shift[10], o[2]) + FMUL(grip_shift[6], o[1])) + FMUL(grip_shift[2], o[0])) + grip_shift[14];
				const float *q = (const float *)(uintptr_t)((u32)model->entries + muzzle[0] * 100 + 0xc);
				shot_at[0] = f32(((fmul_m(z, &q[8]) + fmul_m(y, &q[4])) + fmul_m(x, &q[0])) + q[12]);
				shot_at[1] = f32(((fmul_m(x, &q[1]) + fmul_m(z, &q[9])) + fmul_m(y, &q[5])) + q[13]);
				shot_at[2] = f32(((fmul_m(x, &q[2]) + fmul_m(z, &q[10])) + fmul_m(y, &q[6])) + q[14]);
				FiredRound *rec = &AC->rounds[k];
				rec->received = 1;
				rec->weapon = pr->items[AC->slot];
				memcpy(rec->from, shot_at, 12);
				rec->hitPlane = f[2];
				memcpy(rec->dir, f + 4, 12);
				rec->muzzle = (u32)(uintptr_t)q;
				*item = bullet_spawn(s, -1, i, -1, rec, 0);
				AC->fireAnim = 0.0001f;
				long double v = fadd_m(fdiv_m(fld_m(dt), &weapon->cycleTime), &AC->fireCycle);
				AC->fireCycle = (float)v;
				if (v >= 1.0L)
					AC->fireCycle = 0;
				f[0] = 0;
			}
			Bullet *b = &ST->bullets[*item];   /* the round's record, brought up to date */
			if (b->active != 1)
				continue;
			b->hitActor = f[1];
			b->hit = (struct CollisionPlane *)array_recordAt(f[2], (*(int *)&ST->space.planes.records), 0xac);
			if (f[3] == 1)
				b->life = f32(fsub_m(fld_m(&b->age), dt));
			memcpy(b->netPoint, f + 4, 12);
			memcpy(b->impact, f + 4, 12);
			b->moved = 1;
		}
	}
	/* the booster energy (energy, what is left): spent running, back after a rest (staminaRest the rest) */
	if (!(((u32)AC->stateFlags) & 0x400) && AC->inBooster == 1 && (AC->inForward == 1 || AC->inBackward == 1 || AC->inStepLeft == 1 || AC->inStepRight == 1)) {
		long double v = fsubr_m(fdiv_m(fld_m(dt), &AC->boostTime), &AC->energy);
		AC->energy = (float)v;
		if (!(v >= 0)) {
			AC->energy = 0.0f;
			AC->overheat = 1;
		}
		AC->staminaRest = 0.0f;
	} else if (!(AC->staminaRest >= 1.0f)) {
		long double v = fadd_m(fdiv_m(fld_m(dt), &AC->restTime), &AC->staminaRest);
		AC->staminaRest = (float)v;
		if (v > 1.0L)
			AC->staminaRest = 1.0f;
	} else if (!(AC->energy >= 1.0f)) {
		long double v = fadd_m(fdiv_m(fld_m(dt), &AC->rechargeTime), &AC->energy);
		AC->energy = (float)v;
		if (v > 1.0L)
			AC->energy = 1.0f;
	}
	AC->warned = AC->energy > *&k_0_2f ? 0 : 1;
	if (AC->overheat == 1 && AC->energy >= 0.5f)
		AC->overheat = 0;
	if (AC->state == 1) {
		/* the effects' scale by the speed: 0.5 .. 3 */
		if (!(AC->nextForward > 0.5f))
			AC->effectScale = 0.5f;
		else if (!(AC->nextForward >= 3.0f))
			BITS(AC->effectScale) = BITS(AC->nextForward);
		else
			AC->effectScale = 3.0f;
		if (i != ST->cockpitActor && AC->viewMarked == 0) {   /* the legs' and booster's emitters, faint when cloaked or hurt */
			BITS(scratch[0]) = BITS(AC->effectScale);
			if ((((u32)AC->stateFlags) & 0x200) && AC->hackingLevel >= ST->actors[ST->playerActor].hackingLevel)
				scratch[1] = 0.0627451f;   /* 1/255 */
			else if (AC->spawnAge > 3.0f)
				scratch[1] = 1.0f;
			else
				scratch[1] = f32(fmul_m(fld_m(&AC->spawnAge), k_0_333333f));
			if (i == ST->playerActor)
				scratch[1] = f32(FMUL(scratch[1], k_0_5f));
			emit(s, a, legs->emitters, &legs->emitterCount, (u8 *)&AC->legsModel.entries, booster, scratch, fx);
			emit(s, a, booster->emitters, &booster->emitterCount, (u8 *)&AC->boosterModel.entries, booster, scratch, fx);
		}
		long double v = fadd_m(fld_m(dt), &AC->footstepTime);   /* footsteps every third of a second */
		AC->footstepTime = (float)v;
		if (v > *&k_0_333f) {
			if (i == ST->playerActor && (AC->warned == 1 || AC->overheat == 1) && !(AC->timers[2] > 0))
				sound_playVolume(0x10, 0x64);   /* out of breath */
			if (i != ST->silentActor) {
				int step = booster->thrustType;
				if (i == ST->playerActor)
					sound_playVolume(AC->inBooster == 0 ? step : step + 3, AC->inBooster == 0 ? 0x28 : 0x50);
				else
					sound_play3D(AC->nextRun > 0 ? step + 3 : step, ST->cameraPos, AC->nextPos, ST->viewDir, 0x47435000);
			}
			AC->footstepTime = 0.0f;
		}
	}
	if (AC->state == 1) {
		if (AC->armor <= 0)
			actor_dies(s, a, i, fx, scratch);
		else if (AC->controlledBy == ST->playerActor || AC->bot != 0)   /* the drop age kept 10 s ahead */
			AC->dropAge = f32(fadd_m(fadd_m(fld_m(dt), &AC->spawnAge), &k_10f));
	} else if (AC->state == 2) {   /* dying: out after 2 s */
		if (AC->stateTime > 2.0f) {
			AC->state = 3;
			AC->stateTime = 0.0f;
			if (i == ST->playerActor)   /* the patch DLL's cat_wrap */
				PATCHED_THISCALL(0x45c638, void, void *, u32)(s, (*(u32 *)&g_componentDatPath));
		}
	} else if (AC->state == 3)
		BITS(AC->spawnAge) = BITS(AC->dropAge);
	AC->glow = 0.0f;   /* the glow: a fresh shot's flash, and speed unless cloaked */
	if (AC->fireAnim > 0 && !(AC->fireAnim >= 0.5f)) {
		long double g = FSUB(k_0_5f, AC->fireAnim);
		AC->glow = (float)(g + g);
	}
	if ((((u32)AC->stateFlags) & 0x200) && AC->hackingLevel >= ST->actors[ST->playerActor].hackingLevel) {
		if (AC->effectScale > 1.0f)
			AC->glow = f32(fadd_m(fmul_m(FSUB(AC->effectScale, k_1f), &k_0_2f), &AC->glow));
	} else
		AC->glow = f32(fadd_m(FMUL(AC->effectScale, k_0_2f), &AC->glow));
	goto timers;
tail:   /* 45cdb1: held by the script */
	AC->dropAge = f32(fadd_m(fadd_m(fld_m(dt), &AC->spawnAge), &k_10f));
timers:
	AC->spawnAge = f32(fadd_m(fld_m(dt), &AC->spawnAge));
	AC->stateTime = f32(fadd_m(fld_m(dt), &AC->stateTime));
	long double sec = fadd_m(fld_m(dt), &AC->timeFraction);   /* whole seconds into timePlayed */
	AC->timeFraction = (float)sec;
	if (sec > 1.0L) {
		AC->timePlayed += ftol(sec);
		AC->timeFraction = f32(fsubr_m((long double)ftol(fld_m(&AC->timeFraction)), &AC->timeFraction));
	}
	countdown(&AC->labelFade, dt);
	countdown(&AC->hitFlash, dt);
	countdown(&AC->botTargetTime, dt);
	countdown(&AC->slotIconTime, dt);
	AC->messageTime = f32(fsub_m(fld_m(&AC->messageTime), dt));
	countdown(&AC->warpWait, dt);
	if (AC->shield < AC->shieldMax && AC->shieldRegen > 0) {   /* the shield back by shieldRegen a second up to shieldMax */
		long double v = fadd_m(fld_m(dt), &AC->shieldRegenTime);
		AC->shieldRegenTime = (float)v;
		if (v >= 1.0L) {
			int e = ftol(v) * AC->shieldRegen + AC->shield;
			if (e >= AC->shieldMax) {
				AC->shield = AC->shieldMax;
				AC->shieldRegenTime = 0.0f;
			} else {
				AC->shield = e;
				AC->shieldRegenTime = f32(fsubr_m((long double)ftol(fld_m(&AC->shieldRegenTime)), &AC->shieldRegenTime));
			}
		}
	} else
		AC->shieldRegenTime = 0.0f;
	countdown(&AC->whiteFlash, dt);
	countdown(&AC->timers[0], dt);
	countdown(&AC->timers[1], dt);
	countdown(&AC->timers[2], dt);
	countdown(&AC->timers[3], dt);
	for (int c = 0; c < 3; c++)   /* this frame's move */
		AC->move[c] = f32(FSUB(AC->nextPos[c], AC->pos[c]));
	AC->netFired = 0;
	if (AC->controlledBy == ST->playerActor) {   /* the state bits sent with the actor */
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
		if (AC->bigHead == 1)
			f |= 0x1000;
		if (AC->shield <= 0)
			f |= 0x2000;
		if (AC->id % 2 == 1)
			f |= 0x4000;
		AC->stateFlags = f;
	}
	static const u16 parts[7] = { offsetof(Player, headModel), offsetof(Player, chestModel), offsetof(Player, armsModel), offsetof(Player, legsModel), offsetof(Player, boosterModel), offsetof(Player, weaponModel4), offsetof(Player, weaponModel5) };
	if (AC->breakUp < 7) {   /* the parts' break-up, one a frame */
		if (AC->breakUp >= 0)
			partList_bindTextures(a + parts[AC->breakUp]);
		AC->breakUp++;
	}
}
