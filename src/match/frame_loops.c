/* frame_loops.c: the scene's per-frame passes over its slots (bullets, particles, objects, actors and triggers; each
   slot in use updated unless a script holds the actors) and what they run: particles spawned, set up and updated,
   bullets spawned, map objects added, the triggers' way-point commands, the items' frame; also the effects' shapes
   and the Ladder scores added. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

#define FIELD(type, obj, offset) GAME_VAR(type, AP(u8, RELOC(obj)) + (offset))

static int paused(void *s) { return ST->scriptMode && ST->scriptHoldsPlay == 1; }   /* (a script holds the actors) */

/* 0x47d000 (thiscall on the scene): the bullets (0x4e8-byte slots from bullets[].active, bulletSlotsUsed of them). Its callers
   ignore the eax it leaves */
void THISCALL (bullet_updateAll)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->bulletSlotsUsed; i++)
		if (ST->bullets[i].active == 1)
			bullet_update(s, i, dt);
}

/* 0x479a90: the effects (0x12c-byte slots from particles[].active, particleCount of them) */
void THISCALL (stage_updateParticles)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->particleCount; i++)
		if (ST->particles[i].active == 1)
			particle_update(s, i, dt);
}

/* 0x490d40: the objects (0x2cc-byte slots from objects[].active, objectCount of them) */
void THISCALL (stage_updateObjects)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->objectCount; i++)
		if (ST->objects[i].active == 1)
			mapObject_frame(s, i, dt);
}

/* 0x479950 (thiscall on the scene): an effect started in the next free slot (particleFreeHint; at most 999): a slot added
   when that is the count (particleCount, the new one marked free), the next free one after it found (none: it stays),
   then the effect set up (particle_init). Returns its slot, or -1 */
int THISCALL (particle_spawn)(u8 *s, u32 desc)
{
#define COUNT ST->particleCount
#define NEXT ST->particleFreeHint
	if (NEXT >= 1000)
		return -1;
	if (NEXT == COUNT) {
		COUNT++;
		ST->particles[COUNT].active = 0;
	}
	int slot = NEXT;
	for (int k = slot + 1; k <= COUNT; k++)
		if (ST->particles[k].active == 0) {
			NEXT = k;
			break;
		}
	particle_init(s, slot, desc);
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x45e0c0 (thiscall on the scene): the actors (0x8888-byte slots from actors[].active, actorCount of them) moved on by
   dt, the triggers run (all of it skipped while paused); dt added to the clock's fraction (clockFraction), whole units over 1 moved into
   the clock (clockSeconds). Its callers ignore the eax it leaves */
void THISCALL (stage_updateActorsAndTriggers)(u8 *s, float dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->actorCount; i++)
		if (ST->actors[i].active == 1)
			actor_processFrame(s, i, dt);
	script_processTriggers(s);
	long double t = (long double)dt + ST->clockFraction;
	ST->clockFraction = (float)t;
	if (t > k_1f) {   /* 1 */
		int whole = ftol(t);
		ST->clockSeconds += whole;
		ST->clockFraction = (float)(t - whole);
	}
}

/* 0x47ce50 (thiscall on the scene): a bullet fired (shot the FiredRound: none when its weapon is negative) into the next free slot
   (bulletFreeHint; at most 399; a slot added when that is the count, bulletSlotsUsed), the next free one after it found, then
   the bullet set up (bullet_init). Returns its slot, or -1 */
int THISCALL (bullet_spawn)(u8 *s, u32 id, u32 owner, u32 homingTarget, const u8 *shot, u32 quiet)
{
#define COUNT ST->bulletSlotsUsed
#define NEXT ST->bulletFreeHint
	if ((AP(const FiredRound, RELOC(shot)))->weapon < 0 || NEXT >= 400)
		return -1;
	if (NEXT == COUNT) {
		COUNT++;
		ST->bullets[COUNT].active = 0;
	}
	int slot = NEXT;
	for (int k = slot + 1; k <= COUNT; k++)
		if (ST->bullets[k].active == 0) {
			NEXT = k;
			break;
		}
	bullet_init(s, slot, id, owner, homingTarget, AV(shot), quiet);
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x490c50: an object added into the next free slot (objectFreeHint; at most 999, else a message and -1; a slot added
   when that is the count, objectCount), set up (object_initObjectBy), then the next free one after it found. Returns
   its slot */
int THISCALL (object_addObjectBy)(u8 *s, u32 type)
{
#define COUNT ST->objectCount
#define NEXT ST->objectFreeHint
	if (NEXT >= 1000) {
		sys_errorMessage(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c8398, "objectPool overflow(%d/%d)-addObjectBy()")), NEXT + 1, 1000);
		return -1;
	}
	if (NEXT == COUNT) {
		COUNT++;
		ST->objects[COUNT].active = 0;
	}
	int slot = NEXT;
	object_initObjectBy(s, slot, type);
	for (int k = NEXT + 1; k <= COUNT; k++)
		if (ST->objects[k].active == 0) {
			NEXT = k;
			break;
		}
	return slot;
#undef COUNT
#undef NEXT
}

/* 0x483640 (thiscall on the scene): the map's triggers (0x1c-byte records from triggers, triggerCount of them): each
   armed one (+8 1) fires (fired) on its time (flag 1: the clock, clockSeconds + clockFraction, reaching time) or on the
   player (flag 2: the player's actor, playerActor, within the squared radius radiusSq of its way point, +4; a NaN distance
   counts as within). Then each fired one runs its command (script_processCommandBy), is disarmed, and noted in the
   fired list (triggerFired, one dword each, the others 0) */
void THISCALL (script_processTriggers)(u8 *s)
{
#define COUNT ST->triggerCount
	for (int i = 0; i < COUNT; i++) {
		Trigger *t = &ST->triggers[i];
		if (t->armed != 1)
			continue;
		u32 flags = t->flags;
		if (flags & 1) {
			long double now = (long double)ST->clockSeconds + ST->clockFraction;
			if (now >= t->time)
				t->fired = 1;
		}
		int localActor = ST->playerActor;
		if (flags & 2 && localActor >= 0) {
			const float *at = ST->actors[localActor].pos;
			const float *point = (AP(const float, t->wayPoints));
			long double dx = (long double)at[0] - point[0], dy = (long double)at[1] - point[1], dz = (long double)at[2] - point[2];
			if (!(dz * dz + dy * dy + dx * dx >= t->radiusSq))
				t->fired = 1;
		}
	}
	for (int i = 0; i < COUNT; i++) {
		Trigger *t = &ST->triggers[i];
		if (t->fired == 1) {
			script_processCommandBy(s, -1, i, 0);
			t->fired = 0;
			t->armed = 0;
			ST->triggerFired[i] = 1;
		} else
			ST->triggerFired[i] = 0;
	}
#undef COUNT

}

/* 0x49d150 (thiscall on the scene): the local player (none when negative): its kills, deaths and score since they
   were last counted (killsCounted, deathsCounted, scoreCounted) added to the Ladder record's kills, deaths and exp
   (g_ladderKills, g_ladderDeaths, g_ladderExp), and counted; while the match is not being left (matchLeaving 0) the
   Ladder record sent (ladder_sendRecord); scoreCommitTimer 300. Its callers ignore the eax it leaves */
void THISCALL (ladder_addMatchScores)(u8 *s)
{
	Scene *sc = (Scene *)s;
	if (sc->localPlayer >= 0) {
		Actor *me = &sc->players[sc->localPlayer];
		g_ladderKills += me->kills - me->killsCounted;
		g_ladderDeaths += me->deaths - me->deathsCounted;
		g_ladderExp += me->score - me->scoreCounted;
		me->killsCounted = me->kills;
		me->deathsCounted = me->deaths;
		me->scoreCounted = me->score;
	}
	if (!sc->matchLeaving)
		ladder_sendRecord();
	BITS(sc->scoreCommitTimer) = 0x43960000;   /* 300.0f */
}

/* 0x48ec20 (thiscall on the scene): the effects' shapes looked up in the shape cache (itemShapes): three sets of eight
   numbered ones (thrustShapes, thrustShapes[8], thrustShapes[16]; named by 0x4c8170, 0x4c815c, 0x4c8144) and eight single ones
   (effectShapes ..); itemTextures cleared first. Its caller ignores the eax it leaves */
void THISCALL (effect_initShapes)(u8 *s)
{
	static const u32 sets[3] = { STR(0x4c8170, "Effect\\PlasmaThrust-%d"), STR(0x4c815c, "Effect\\IonThrust-%d"), STR(0x4c8144, "Effect\\GravityThrust-%d") };
	static const u32 singles[8] = { STR(0x4c8130, "Effect\\Shell-Fire"), STR(0x4c811c, "Effect\\Shell-Bullet"), STR(0x4c8108, "Effect\\Rail-Fire"), STR(0x4c80f4, "Effect\\Blade-Fire"), STR(0x4c80e0, "Effect\\Rail-Bullet"), STR(0x4c80c8, "Effect\\Lightning-Bullet"), STR(0x4c80b0, "Effect\\Missile-Bullet"), STR(0x4c8098, "Effect\\Homing-Bullet") };
	ST->itemTextures[0] = 0;
	char name[0x100];
	for (int set = 0; set < 3; set++)
		for (int k = 0; k < 8; k++) {
			sprintf(name, AP(const char, RELOC(sets[set])), k);
			ST->thrustShapes[set][k] = shape_getByName((u8 *)&ST->itemShapes, name, 1);
		}
	for (int k = 0; k < 8; k++)
		ST->effectShapes[k] = shape_getByName((u8 *)&ST->itemShapes, AP(const char, RELOC(singles[k])), 1);
}

/* 0x483770 (thiscall on the scene): way point `entry` of trigger trig (the triggers' 0x1c-byte records; WayPoint 0x14
   bytes from wayPoints: commandCount commands of 0x30 bytes at commands) run for actor actorIndex (none when
   negative). Each command by its type: triggers armed / disarmed (armed: 0 / 1) or fired (fired: 2),
   stage_triggerActionNone (3, 9); the actor's waits, path, look / follow targets, speed, script flag and
   invulnerability (4 .. 14, 18 .. 23); an actor spawned from its map record (15), its armour zeroed (16) or
   deactivated (17); its weapon holding an item selected and fired (20); an actor held out of play or let go (24 / 25:
   script_holdActor); a message (26); .scp files (27), object animations (28) and sounds (29) by formatted names;
   objects (de)activated (30 / 31). Its callers ignore the eax it leaves */
void THISCALL (script_processCommandBy)(u8 *s, int actorIndex, int trig, int entry)
{
	u8 *actor = actorIndex >= 0 ? (u8 *)&ST->actors[actorIndex] : NULL;
	Actor *ac = (Actor *)actor;
	WayPoint *e = AP(WayPoint, (ST->triggers[trig].wayPoints + entry * 0x14));
	char name[0x100];
	for (int i = 0; i < e->commandCount; i++) {
		u32 *c = AP(u32, (e->commands + i * 0x30));
		switch (c[0]) {
		case 0: ST->triggers[c[1]].armed = 1; break;
		case 1: ST->triggers[c[1]].armed = 0; break;
		case 2: ST->triggers[c[1]].fired = 1; break;
		case 3: stage_triggerActionNone(s, c[1]); break;
		case 4: if (actor) BITS(ac->botWait) = c[1]; break;
		case 5: if (actor) (*(u32 *)&ac->botWaitTrigger) = c[1]; break;
		case 7:
			if (actor) {
				ac->path = c[1];
				ac->pathPoint = c[2];
			}
			break;
		case 8:
			if (actor && ac->botTarget >= 0)
				ST->triggers[c[1]].fired = 1;
			break;
		case 9:
			if (actor && ac->botTarget >= 0)
				stage_triggerActionNone(s, c[1]);
			break;
		case 10: if (actor) (*(int *)&ac->scriptFlag) = 0; break;
		case 11: if (actor) (*(int *)&ac->scriptFlag) = 1; break;
		case 12:
			if (actor) {
				(*(int *)&ac->botWait) = 0;
				ac->botWaitTrigger = -1;
				BITS(ac->speed) = BITS(ac->baseSpeed);
				ac->invulnerable = 0;
				ac->lookActor = ac->lookPath = ac->lookPoint = ac->followTarget = -1;
			}
			break;
		case 13:
			if (actor)
				ac->speed = f32(fmul_m(fld_m((const float *)&c[1]), AP(const float, ADDR(k_27_7778f))));
			break;
		case 14: if (actor) ac->invulnerable = 1; break;
		case 15: actor_applySpawnRecord(s, c[1], (u8 *)&ST->mapActors[c[1]]); break;
		case 16: ST->actors[c[1]].armor = 0; break;
		case 17: actor_deactivate((Stage *)s, c[1]); break;
		case 18: if (actor) (*(u32 *)&ac->lookActor) = c[1]; break;
		case 19:
			if (actor) {
				ac->lookPath = c[1];
				ac->lookPoint = c[2];
			}
			break;
		case 20:   /* the actor's weapon holding item c[1] selected */
			if (actor) {
				for (int k = 0; k < 6; k++)
					if ((u32)ST->playerRecords[ac->player].items[k] == c[1])
						actor_selectWeapon((Stage *)s, actorIndex, k);
				ac->inFire = 1;
			}
			break;
		case 21: if (actor) (*(u32 *)&ac->followTarget) = c[1]; break;
		case 22:
			ST->actors[c[1]].path = -1;
			ST->actors[c[1]].pathPoint = -1;
			break;
		case 23:
			ST->actors[c[1]].path = c[2];
			ST->actors[c[1]].pathPoint = c[3];
			break;
		case 24: script_holdActor(s, c[1], c[2], c[3]); break;
		case 25: script_holdActor(s, -1, -1, 0); break;
		case 26:   /* MESSAGE (nothing fills Stage.speakers / texts, so with the game's data this stops the game with the message below) */
			if (*(const int *)ST->speakers[c[1]] == 0)
				sys_fatalError(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c7a8c, "invalid speaker (%d) in command MESSA...")), c[1]);
			if (*(const int *)ST->texts[c[2]] == 0)
				sys_fatalError(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c7a48, "invalid text (%d) in command MESSAGE ...")), c[2]);
			script_pushMessage(s, c[1], c[2], c[3], c[4]);
			break;
		case 27:
			sprintf(name, AP(const char, STR(0x4c7a3c, "%s/%s.scp")), ST->sceneDir, (const char *)&c[1]);
			script_startScenePath(s, name, c[9]);
			break;
		case 28:
			sprintf(name, AP(const char, STR(0x4c7a30, "%s/%s/%s")), s + 8, ST->stageName, (const char *)&c[2]);
			object_setAnimation(s, c[1], name, c[10], c[11]);
			break;
		case 29:
			sprintf(name, AP(const char, STR(0x4c7a20, "%s/Sound/%s.wav")), ST->stageName, (const char *)&c[1]);
			sound_playFile(name, 100);
			break;
		case 30: object_activate(s, c[1]); break;
		case 31: object_deactivate(s, c[1]); break;
		}
	}
}

/* a 4 x 4 identity matrix (as float bits) */
static void identity4(u32 *m)
{
	for (int k = 0; k < 16; k++)
		m[k] = k % 5 == 0 ? 0x3f800000 : 0;
}

/* 0x48fee0 (thiscall on the scene): map object i (0x2cc bytes from objects) set up from its type record: the
   type's name found among the object names (0x40 bytes from objectNames, objectNameCount of them) or added (at most 1000,
   else a fatal message); the next serial (objectSerial), in use, the name's index, three values (flags ..), the
   animation path ("dir\sub\name" by 0x4c7a30 when the type names one, animName), the position (place) and rotation
   (rotation, a quaternion); its matrix (placeMatrix: translation x rotation) and inverse (placeInverse), a copy (matrix) and its
   inverse (matrixInverse), two identities (animMatrix, animInverse), the copy times the inverse (relMatrix) and its inverse (relInverse).
   Its shape (shape_getByName, bound) and two ranges of its element count from the shading pool (objectColours, used
   objectColourCount; past 1000000 a fatal message), the record's glow (glowSize, glowColour), the counters cleared, the shape's centre
   through the matrix (pos; no shape: the position), and its shading worked out unless the map has it (mapShaded). Its
   callers ignore the eax it leaves */
void THISCALL (object_initObjectBy)(Stage *s, int i, const ObjectInfo *info)
{
	u8 *obj = (u8 *)&ST->objects[i];
	MapObject *mo = (MapObject *)obj;
	int idx = 0;
	for (; idx < ST->objectNameCount; idx++)
		if (!strcmp(info->name, ST->objectNames[idx]))
			break;
	if (idx == ST->objectNameCount) {
		if (idx >= 1000)
			sys_fatalError(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c8364, "object type buffer overflow (%d) - in...")), 1000);
		idx = ST->objectNameCount++;
		strcpy(ST->objectNames[idx], info->name);
	}
	mo->id = ST->objectSerial++;
	mo->active = 1;
	mo->nameIndex = idx;
	memcpy(obj + offsetof(MapObject, flags), &info->flags, 12);   /* flags, trigger, animPeriod */
	if (info->animName[0])
		sprintf(mo->animPath, AP(const char, STR(0x4c7a30, "%s/%s/%s")), ST->stageDir, ST->stageName, info->animName);
	else
		obj[0x18] = 0;
	memcpy(mo->place, info->place, 12);
	u32 move[16];
	identity4(move);
	for (int c = 0; c < 3; c++)
		(AP(float, RELOC(move)))[12 + c] = f32(fld_m(mo->place + c));
	memcpy(mo->rotation, info->rotation, 16);
	float turn[16];
	Mat4_fromQuat(turn, mo->rotation);
	float *m = mo->matrix;
	Mat4_multiply(mo->placeMatrix, AP(const float, RELOC(move)), turn);
	Mat4_invert(mo->placeInverse, mo->placeMatrix);
	Mat4_copy(m, mo->placeMatrix);
	Mat4_invert(mo->matrixInverse, m);
	identity4((u32 *)mo->animMatrix);
	identity4((u32 *)mo->animInverse);
	Mat4_multiply(mo->relMatrix, m, mo->placeInverse);
	Mat4_invert(mo->relInverse, mo->relMatrix);
	Shape *shape = (Shape *)(AP(u8, shape_getByName((u8 *)&ST->objectShapes, info->name, 1)));
	mo->model = AREF((Shape *)((u8 *)shape));
	for (int r = 0; r < 2; r++) {
		int need = ST->objectColourCount + shape->colourCount;
		if (need > 1000000)
			sys_fatalErrorN(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c8314, "object(%d) objectShapeElementShadingC...")), i, need, 1000000);
		mo->colourRuns[r] = AV(&ST->objectColours[ST->objectColourCount]);
		ST->objectColourCount += mo->model->colourCount;
	}
	mo->colourSide = 1;
	BITS(mo->glowSize) = BITS(info->glowSize);
	mo->glowColour = info->glowColour;
	memset(obj + offsetof(MapObject, unit), 0, 7 * 4);   /* unit .. poseStale */
	if (shape) {
		const float *c = shape->centre;
		float *out = mo->pos;
		out[0] = f32(fadd_m(FMUL(m[8], c[2]) + FMUL(m[4], c[1]) + FMUL(m[0], c[0]), &m[12]));
		for (int r = 1; r < 3; r++)
			out[r] = f32(fadd_m(FMUL(m[8 + r], c[2]) + FMUL(m[r], c[0]) + FMUL(m[4 + r], c[1]), &m[12 + r]));
	} else
		memcpy(mo->pos, mo->place, 12);
	BITS(mo->glow) = 0;
	BITS(mo->waitTime) = 0;
	if (ST->shadingCached == 0)
		shape_shadingColours((*(u32 * *)&mo->colourRuns[0]), 1, AP(Shape, mo->model), (const LightFactors *)&s->mapLights,
		                 mo->matrixInverse);
}

/* a particle of kind at p (particle_spawn's record: the kind, 0, the point, the world's colour g_vecZero, zeros) */
static void spawn_at(u8 *s, u32 kind, const float *p)
{
	u32 rec[13] = { kind, 0 };
	memcpy(&rec[2], p, 12);
	memcpy(&rec[5], AP(const void, ADDR(g_vecZero)), 12);
	particle_spawn(s, rec);
}

/* a piece of debris (kind 9: a dead actor's part, actor_dies) moved by its velocity (target) over dt and dropped 2000 dt further: what it meets on the
   way (collision_rayTrace) stops it there, ends it and leaves a kind 2 particle; its orientation (matrix) turned by
   its age; every tenth of a second a trail particle (kind 2 one time in ten, which also ends it, else kind 0) */
static void debris(u8 *s, u8 *p, float dt)
{
	Particle *pr = (Particle *)p;
	float *pos = pr->pos;
	const float *v = pr->target, *k = AP(const float, ADDR(k_2000f));
	float dy = f32(FMUL(dt, v[1])), dz = f32(FMUL(dt, v[2]));
	float hit[3], below[3];
	hit[0] = f32(fadd_m(FMUL(dt, v[0]), &pos[0]));
	hit[1] = f32(FADD(dy, pos[1]));
	hit[2] = f32(FADD(dz, pos[2]));
	below[0] = hit[0];
	below[1] = f32(fld_m(&hit[1]) - fmul_m(fld_m(&dt), k));
	below[2] = hit[2];
	if (collision_rayTrace(s, pos, below, hit)) {
		memcpy(pos, hit, 12);
		BITS(pr->life) = BITS(pr->drawAge);
		spawn_at(s, 2, hit);
	} else
		memcpy(pos, below, 12);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef_stored(pos);
	glRotatef(f32(fmul_m(fld_m(&pr->drawAge), AP(const float, ADDR(k_3600f)))), 0.0f, 1.0f, 0.0f);
	glRotatef(f32(fmul_m(fld_m(&pr->drawAge), AP(const float, ADDR(k_3600f)))), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, pr->matrix);
	glPopMatrix();
	long double wait = FSUB(pr->puffWait, dt);
	pr->puffWait = f32(wait);
	if (wait > 0)
		return;
	u32 at = g_randPos;
	u32 r = (*(u32 *)&g_randTable[at & 0xfff]) % 10;
	g_randPos = at + 1;
	spawn_at(s, r ? 0 : 2, pos);
	pr->puffWait = 0.1f;
	if (!r)
		BITS(pr->life) = BITS(pr->drawAge);
}

/* 0x476410 (thiscall on the scene): particle slot's frame (0x12c bytes from particles). Its age (age, kept at
   drawAge) past its life (life) frees it (stage_freeParticle); otherwise debris moves (debris, kind 9), and flashes
   and impacts (kinds 2, 3, 25, 26, 30 .. 38) cast a light that shrinks with age: lightRadius = (1 - age / life)^2 x
   the kind's radius (3000 / 5000 / 2000 / 1000 / 1500); the age moves on by dt. Its caller ignores the eax it leaves */
void THISCALL (particle_update)(u8 *s, int slot, float dt)
{
	u8 *p = (u8 *)&ST->particles[slot];
	Particle *pr = (Particle *)p;
	float age = pr->age;
	pr->drawAge = age;
	if (age > pr->life) {
		stage_freeParticle(s, slot);
		return;
	}
	float t = pr->life > 0 ? f32(FDIV(age, pr->life)) : 0.0f;
	int k = pr->kind;
	u32 radius = 0;   /* where the radius constant is */
	switch (k / 5) {
	case 0:
		radius = k == 2 ? ADDR(k_3000f) : k == 3 ? ADDR(k_5000f) : 0;
		break;
	case 1:
		if (k == 9)
			debris(s, p, dt);
		break;
	case 5:
		radius = k == 25 || k == 26 ? ADDR(k_2000f) : 0;
		break;
	case 6:
		radius = k <= 31 ? OBJ(k_1000f) : ADDR(k_1500f);
		break;
	case 7:
		radius = k == 35 ? ADDR(k_5000f) : k == 36 ? ADDR(k_3000f) : k <= 38 ? ADDR(k_1500f) : 0;
		break;
	}
	if (radius) {
		long double u = fsub_m(fld_m(AP(const float, ADDR(k_1f))), &t);
		pr->lightRadius = f32(fmul_m(u * u, AP(const float, RELOC(radius))));
	}
	pr->age = f32(FADD(dt, pr->age));
}

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Actor *)ac)   /* the same by its fields (src/scene.fields) */

/* the cells, armour and shield items (kinds 0 .. 5, 10 .. 19): the actor's flag (stateFlags) that refuses them, the
   count raised, its limit (and how far an extended one may go past it), the message; an extended one is noted as the
   last big pickup (lastPickup) */
static const struct { u8 flag; u16 count, limit; u8 add, over; u32 text; } k_supplies[16] = {
	{ 0x10, offsetof(Actor, ammo[0]), offsetof(Actor, ammoMax[0]), 1, 0, STR(0x4c82f4, "+1 30MM CELL") }, { 0x10, offsetof(Actor, ammo[0]), offsetof(Actor, ammoMax[0]), 40, 0, STR(0x4c82e4, "+40 30MM CELLS") }, { 0x20, offsetof(Actor, ammo[1]), offsetof(Actor, ammoMax[1]), 40, 0, STR(0x4c82d4, "+40 60MM CELLS") },
	{ 0x40, offsetof(Actor, ammo[2]), offsetof(Actor, ammoMax[2]), 40, 0, STR(0x4c82c0, "+40 E-PACK CELLS") }, { 0x80, offsetof(Actor, ammo[3]), offsetof(Actor, ammoMax[3]), 15, 0, STR(0x4c82ac, "+15 MISSILE CELLS") }, { 0x80, offsetof(Actor, ammo[3]), offsetof(Actor, ammoMax[3]), 5, 0, STR(0x4c8298, "+5 MISSILE CELLS") },
	{ 1, offsetof(Actor, armor), offsetof(Actor, armorMax), 10, 0, STR(0x4c828c, "+10 ARMOR") }, { 1, offsetof(Actor, armor), offsetof(Actor, armorMax), 25, 0, STR(0x4c8280, "+25 ARMOR") }, { 1, offsetof(Actor, armor), offsetof(Actor, armorMax), 50, 0, STR(0x4c8274, "+50 ARMOR") },
	{ 1, offsetof(Actor, armor), offsetof(Actor, armorMax), 100, 0, STR(0x4c8268, "+100 ARMOR") }, { 2, offsetof(Actor, armor), offsetof(Actor, armorMax), 100, 100, STR(0x4c8254, "+100 EXTENDED ARMOR") }, { 4, offsetof(Actor, shield), offsetof(Actor, shieldMax), 10, 0, STR(0x4c8248, "+10 SHIELD") },
	{ 4, offsetof(Actor, shield), offsetof(Actor, shieldMax), 25, 0, STR(0x4c823c, "+25 SHIELD") }, { 4, offsetof(Actor, shield), offsetof(Actor, shieldMax), 50, 0, STR(0x4c8230, "+50 SHIELD") }, { 4, offsetof(Actor, shield), offsetof(Actor, shieldMax), 100, 0, STR(0x4c8224, "+100 SHIELD") },
	{ 8, offsetof(Actor, shield), offsetof(Actor, shieldMax), 100, 100, STR(0x4c820c, "+100 EXTENDED SHIELD") } };

/* the item's sound (its type's respawnSound or pickSound) at its position, heard from the camera */
static void item_sound(u8 *s, int sound, u8 *it)
{
	sound_play3D(sound, ST->cameraPos,
	                                                                                ((const MapItem *)it)->pos, ST->viewDir, 0x47c35000);   /* (heard to 100000) */
}

/* actor ac touching item i (of kind type, its type record t): what it gives. Supplies (kinds 0 .. 5 and 10 .. 19)
   the actor can use are taken; power-ups (2x / 3x: damage amp, cloak, booster, gravity armour: 30 s each) are taken;
   a warp zone (kind 24 / 34) sends the local player, when not already warping and not just arrived from it, to the
   linked item's (warpTo) place and heading without being taken; other 2x / 3x kinds are ignored; kinds 6 .. 9 are a
   fatal message, kinds from 40 up an error message */
static void item_pickup(u8 *s, u8 *ac, u8 *it, int i, u8 *t, int type)
{
	MapItem *mi = (MapItem *)it;
	u32 text, *timer = NULL;
	int bigPickup = 0;
	switch (type / 10) {
	case 0:
	case 1: {
		if (type < 10 && type > 5) {
			sys_fatalError(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c81d0, "can't figure out the item type (%d) -...")), type);
			return;
		}
		int k = type < 10 ? type : 6 + type % 10;
		if (*(const u8 *)&AC->stateFlags & k_supplies[k].flag)
			return;
		int limit = A(int, k_supplies[k].limit) + k_supplies[k].over;
		A(int, k_supplies[k].count) += k_supplies[k].add;
		if (A(int, k_supplies[k].count) > limit)
			A(int, k_supplies[k].count) = limit;
		text = k_supplies[k].text;
		bigPickup = k_supplies[k].over != 0;
		break;
	}
	case 2:
	case 3:
		switch (type % 10) {
		case 0: timer = &BITS(AC->timers[0]); text = STR(0x4c81c4, "DAMAGE AMP"); break;   /* DAMAGE AMP */
		case 1: timer = &BITS(AC->timers[1]); text = STR(0x4c81b4, "CLOAKING FIELD"); break;   /* CLOAKING FIELD */
		case 3: timer = &BITS(AC->timers[2]); text = STR(0x4c81a4, "OVERED BOOSTER"); break;   /* OVERED BOOSTER */
		case 7: timer = &BITS(AC->timers[3]); text = STR(0x4c8188, "GRAVITY ARMOR"); break;   /* GRAVITY ARMOR */
		case 4: {
			int warped = 0;
			if (AC->controlledBy == ST->playerActor && !(AC->warpWait > 0) && AC->lastWarp != i) {
				MapItem *to = &ST->items[mi->warpTo];
				memcpy(AC->nextPos, to->pos, 12);
				AC->nextPitch = f32(fmul_m((long double)to->warpPitch, AP(const float, ADDR(k_10f))));
				BITS(AC->nextYaw) = BITS(to->angle);
				AC->lastWarp = mi->warpTo;
				strcpy(AC->message, AP(const char, STR(0x4c8198, "WARP ZONE")));   /* WARP ZONE */
				AC->messageTime = 0.0f;
				AC->whiteFlash = 1.0f;
				AC->warpWait = 2.0f;
				AC->id = ST->actorSerial++;
				warped = 1;
			}
			AC->onWarp = 1;
			if (warped)
				item_sound(s, ((ItemType *)t)->pickSound, it);
			return;
		}
		default:
			return;
		}
		*timer = 0x41f00000;   /* 30 */
		bigPickup = 1;
		break;
	default:
		CALL_FN(sys_errorMessage, void, char *, const char *, int)(AP(char, OBJ(g_logStage)), AP(const char, STR(0x4c81d0, "can't figure out the item type (%d) -...")), type);
		return;
	}
	strcpy(AC->message, AP(const char, RELOC(text)));
	AC->messageTime = 0.0f;
	if (bigPickup)
		ST->lastPickup = i;
	item_sound(s, ((ItemType *)t)->pickSound, it);
	mi->taken = 1;
	mi->timer = 0.0f;
}

/* 0x48ed90 (thiscall on the scene): the items' frame. Live actors' touch flags (onWarp) cleared; every item (0x28
   bytes from items, itemCount of them; its kind +0 into the 0x90-byte types at itemTypes, state taken, timer
   timer, position pos): a taken one comes back after its type's time (respawnTime, with its sound respawnSound); a present one
   spins (angle, 600 a second, but kind 0x22) and the first live actor within 1.5 of its radius (radius) on every
   axis touches it (item_pickup). An actor touching no warp zone forgets the last one (lastWarp -1). Its callers ignore
   the eax it leaves */
void THISCALL (item_update)(u8 *s, float dt)
{
	for (int k = 0; k < ST->actorCount; k++) {
		u8 *ac = (u8 *)&ST->actors[k];
		if (AC->state == 1)
			AC->onWarp = 0;
	}
	for (int i = 0; i < ST->itemCount; i++) {
		u8 *it = (u8 *)&ST->items[i];
		MapItem *mi = (MapItem *)it;
		int type = mi->type;
		if (type < 0)
			continue;
		ItemType *t = &ST->itemTypes[type];
		if (mi->taken == 1) {
			if (mi->timer > t->respawnTime) {
				item_sound(s, t->respawnSound, it);
				mi->taken = 0;
				mi->timer = 0.0f;
			}
		} else if (mi->taken == 0) {
			if (type != 0x22)
				mi->angle = f32(fadd_m(fmul_m(fld_m(&dt), k_600f), &mi->angle));
			int n = ST->actorCount;
			for (int k = 0; k < n; k++) {
				u8 *ac = (u8 *)&ST->actors[k];
				if (AC->state != 1)
					continue;
				float reach = 0;
				int near = 1;
				for (int a = 0; a < 3 && near; a++) {
					long double d = fsub_m(fld_m(AC->pos + a), &mi->pos[a]);
					if (!(d >= 0))
						d = -d;
					if (a == 0)
						reach = f32(fmul_m(fld_m(&AC->radius), k_1_5f));
					near = !(d >= reach);
				}
				if (near) {
					item_pickup(s, ac, it, i, (u8 *)t, type);
					break;
				}
			}
		}
		mi->timer = f32(FADD(dt, mi->timer));
	}
	for (int k = 0; k < ST->actorCount; k++) {
		u8 *ac = (u8 *)&ST->actors[k];
		if (AC->onWarp == 0)
			AC->lastWarp = -1;
	}
}
#undef A

#define PR ((Particle *)p)   /* the same by its fields (src/scene.fields) */
#define K(address) (AP(const float, RELOC(address)))

/* the next of the game's random numbers (its table g_randTable by the counter g_randPos) below n */
static u32 table_rand_below(u32 n)
{
	u32 at = g_randPos;
	u32 r = (*(u32 *)&g_randTable[at & 0xfff]) % n;
	g_randPos = at + 1;
	return r;
}

/* the particle placed at its matrix's origin (pos: the origin g_vecOrigin through its matrix) */
static void particle_placeAtMatrix(u8 *p)
{
	const float *m = PR->matrix, *v = AP(const float, ADDR(g_vecOrigin));
	for (int r = 0; r < 3; r++)
		PR->pos[r] = f32(fadd_m(FMUL(v[2], m[8 + r]) + FMUL(v[1], m[4 + r]) + FMUL(v[0], m[r]),
		                                    &m[12 + r]));
}

/* a matrix from the particle's own (matrixFrom) turned by a random whole degree about z (its matrix), and its position from it */
static void particle_spin(u8 *p)
{
	glPushMatrix();
	glLoadIdentity();
	glLoadMatrixf((*(const float * *)&PR->matrixFrom));
	glRotatef((float)table_rand_below(360), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, PR->matrix);
	glPopMatrix();
	particle_placeAtMatrix(p);
}

/* the particle's matrix the inverse of a look from its position (pos) to its target (target), stretched by their
   distance (z) and xy (1, or by size baseSize) */
static void particle_aim(u8 *p, int by_size)
{
	float d[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(PR->target + k), PR->pos + k));
	float len = f32(Vec3_normalize(d));
	glPushMatrix();
	glLoadIdentity();
	float xy = by_size ? f32(fld_m(&k_1f) / fadd_m(fmul_m(fld_m(&PR->baseSize), k_0_01f_4a9504), &k_1f)) : 1.0f;
	float z = f32(fld_m(&k_1f) / fmul_m(fld_m(&len), k_0_01f_4a9504));
	glScalef_bits(*(u32 *)&xy, *(u32 *)&xy, *(u32 *)&z);
	gluLookAt(PR->pos[0], PR->pos[1], PR->pos[2], PR->target[0], PR->target[1], PR->target[2], 0.0, 1.0, 0.0);
	float m[16];
	glGetFloatv(0xba6, m);
	Mat4_invert(PR->matrix, m);
	glPopMatrix();
}

/* a beam (kinds 25 / 26, its colour): its matrix looking back from the target (target) away from the position, and
   unless it is a remote one (+0xc 1) small particles (kind 0, of its size) along it, one per 200 units */
static void particle_beam(u8 *s, u8 *p, u32 colour)
{
	PR->life = 0.0f;
	PR->colour = colour;
	glPushMatrix();
	glLoadIdentity();
	const float *at = PR->target, *from = PR->pos;
	gluLookAt(at[0], at[1], at[2], (double)(fld_m(&at[0]) * 2 - fld_m(&from[0])), (double)(fld_m(&at[1]) * 2 - fld_m(&from[1])),
	          (double)(fld_m(&at[2]) * 2 - fld_m(&from[2])), 0.0, 1.0, 0.0);
	float m[16];
	glGetFloatv(0xba6, m);
	Mat4_invert(PR->matrix, m);
	glPopMatrix();
	if (PR->owner == 1)
		return;
	float d[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(FSUB(from[k], at[k]));
	long double len = Vec3_normalize(d);
	float step = f32(len);
	if (!(len > 0))
		return;
	int n = ftol(FMUL(step, k_0_005f_4aa428));
	u32 rec[13];
	if (n <= 1) {
		memset(rec, 0, sizeof rec);
		memcpy(&rec[2], at, 12);
		memcpy(&rec[5], AP(const void, OBJ(g_vecZero2)), 12);
		float size = f32(fld_m(&PR->baseSize));
		memcpy(&rec[11], &size, 4);
		particle_spawn(s, rec);
		return;
	}
	step = f32(fld_m(&step) / (long double)n);
	for (int k = 0; k < n; k++) {
		long double sx = FMUL(d[0], step);
		float sy = f32(FMUL(d[1], step)), sz = f32(FMUL(d[2], step));
		float kf = f32((long double)k);
		float y = f32(FMUL(sy, kf)), z = f32(FMUL(sz, kf));
		float pos[3] = { f32(fadd_m(fmul_m(sx, &kf), &at[0])), f32(FADD(y, at[1])), f32(FADD(z, at[2])) };
		rec[0] = rec[1] = 0;
		memcpy(&rec[2], pos, 12);
		memcpy(&rec[5], AP(const void, OBJ(g_vecZero2)), 12);
		rec[8] = rec[9] = rec[10] = 0;
		float size = f32(fld_m(&PR->baseSize));
		memcpy(&rec[11], &size, 4);
		rec[12] = 0;
		particle_spawn(s, rec);
	}
}

/* a hit mark (kinds 40 .. 49, a bullet's mark on the surface it hit: weapons.c decal): its triangle's three points
   (the descriptor's markCorners), and their texture coordinates (the first v 0.5) from the descriptor's markCoords
   (offsets about the impact), either as offset x 0.005 + 0.5 or (by d, the particle's size plus a margin) as
   (offset / d + 1) / 2; its colours the shared one (g_white) */
static void particle_mark(u8 *p, const u8 *desc, u32 margin)
{
	const ParticleDesc *pd = (const ParticleDesc *)desc;
	PR->life = 2.0f;   /* 2 s */
	memcpy(PR->markPoints[0], AP(const void, pd->markCorners), 12);
	memcpy(PR->markPoints[1], AP(const void, pd->markCorners + 3), 12);
	memcpy(PR->markPoints[2], AP(const void, pd->markCorners + 6), 12);
	const float *q = AP(const float, pd->markCoords);
	static const u8 uv[5] = { 0, 2, 3, 4, 5 };   /* (q[k] gives markUv[k]; q[1] is not used) */
	if (!margin) {
		for (int k = 0; k < 5; k++) {
			PR->markUv[uv[k]] = f32(fadd_m(FMUL(q[uv[k]], k_0_005f_4aa428), &k_0_5f));
			if (k == 0)
				PR->markUv[1] = 0.5f;
		}
	} else {
		long double d = fadd_m(fld_m(&PR->baseSize), K(margin));
		for (int k = 0; k < 5; k++) {
			PR->markUv[uv[k]] = f32(fmul_m(fadd_m(fld_m(&q[uv[k]]) / d, &k_1f), &k_0_5f));
			if (k == 0)
				PR->markUv[1] = 0.5f;
		}
	}
	PR->markColours[0] = PR->markColours[1] = PR->markColours[2] = g_white;
}

/* 0x475070 (thiscall on the scene): particle slot (0x12c bytes from particles) set up from its descriptor: a
   serial id, in use. A descriptor flagged isQuad is a kind 50 effect (its 0x48 bytes from quad). Otherwise the
   kind (+0), owner, position, target, a matrix to copy, the size (size); then by kind its life (life) and: 2 / 3
   a sound at the position; 4 its colour from +0x20; 9 (debris) its wait for the first smoke puff (puffWait 0.1); 10 / 11 / 18 a random spin; 12 .. 17 the position
   from its matrix; 20 / 21 / 24 aimed at the target; 25 / 26 beams; 40 .. 49 hit marks */
void THISCALL (particle_init)(u8 *s, int slot, const u8 *desc)
{
	const ParticleDesc *pd = (const ParticleDesc *)desc;
	u8 *p = (u8 *)&ST->particles[slot];
	PR->id = ST->particleSerial++;
	PR->active = 1;
	if (pd->isQuad == 1) {
		PR->kind = 0x32;
		memcpy(&PR->quadTexture, pd->quad, 0x18);
		memcpy(PR->quadPoints[0], pd->quadPoints[0], 12);
		memcpy(PR->quadPoints[1], pd->quadPoints[1], 12);
		memcpy(PR->quadPoints[2], pd->quadPoints[2], 12);
		memcpy(PR->quadPoints[3], pd->quadPoints[3], 12);
		PR->life = 0.01f;   /* 0.01 */
		(*(int *)&PR->drawAge) = (*(int *)&PR->age) = 0;
		return;
	}
	PR->kind = pd->kind;
	PR->owner = pd->owner;
	memcpy(PR->pos, pd->pos, 12);
	memcpy(PR->target, pd->target, 12);
	PR->matrixFrom = pd->matrixFrom;
	if (PR->matrixFrom)
		Mat4_copy(PR->matrix, (*(const void * *)&PR->matrixFrom));
	PR->drawAge = 0.0f;
	PR->life = 1.0f;
	PR->age = 0.0f;
	PR->colour = g_white;
	PR->lightRadius = 0.0f;
	BITS(PR->baseSize) = BITS(pd->size);
	int kind = PR->kind;
	switch (kind) {
	case 0: case 1: case 8: PR->life = 0.5f; break;   /* 0.5 s */
	case 2:
	case 3:
		sound_play3D(kind == 2 ? 0x2a : 0x28, ST->cameraPos,
		                                                                                PR->pos, ST->viewDir,
		                                                                                kind == 2 ? 0x47435000 : 0x47c35000);
		break;
	case 4:
		PR->life = 0.0f;
		PR->colour = BITS(PR->target[1]);
		break;
	case 5: case 6: case 7: (*(int *)&PR->life) = 0; break;
	case 9:
		PR->life = 2.0f;
		PR->puffWait = 0.1f;
		break;
	case 10: case 11: case 18:
		PR->life = 0.01f;
		particle_spin(p);
		break;
	case 12: case 13: case 17:
		PR->life = 0.01f;
		particle_placeAtMatrix(p);
		break;
	case 14: case 15: case 16:
		PR->life = 0.5f;
		particle_placeAtMatrix(p);
		break;
	case 20: case 21:
		PR->life = 0.01f;
		particle_aim(p, 0);
		break;
	case 22: PR->life = 0.01f; break;
	case 24:
		PR->life = 0.5f;
		particle_aim(p, 1);
		break;
	case 25: particle_beam(s, p, 0xffc4c4ff); break;   /* bytes ff c4 c4 ff */
	case 26: particle_beam(s, p, 0xffffc4c4); break;   /* bytes c4 c4 ff ff */
	case 30: case 31: case 32: case 33: case 34: case 35: case 36: case 37: case 38:
		PR->life = 1.0f;
		break;
	case 40: case 41: case 49: particle_mark(p, desc, 0); break;
	case 42: case 43: case 44: case 46: case 47: case 48: particle_mark(p, desc, ADDR(k_200f)); break;
	case 45: particle_mark(p, desc, ADDR(k_400f)); break;
	}
}
#undef K
