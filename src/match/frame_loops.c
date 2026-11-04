/* frame_loops.c: the scene's per-frame passes over its slots: each slot in use (its first dword 1) updated, unless
   a script holds the actors (scriptMode set with scriptRunning 1). The count is read again after each slot. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

static int paused(void *s) { return ST->scriptMode && ST->scriptRunning == 1; }   /* (a script holds the actors) */

/* 0x47d000 (thiscall on the scene): the bullets (0x4e8-byte slots from +0x202ef38, +0x20a99b4 of them). Its callers
   ignore the eax it leaves */
void THISCALL (bullet_updateAll)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->bulletSlotsUsed; i++)
		if (ST->bullets[i].active == 1)
			bullet_update(s, i, dt);
}

/* 0x479a90: the effects (0x12c-byte slots from +0x20a99c4, +0x20f2da0 of them) */
void THISCALL (stage_updateEffects)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->projectileCount; i++)
		if (ST->projectiles[i].active == 1)
			particle_update(s, i, dt);
}

/* 0x490d40: the objects (0x2cc-byte slots from +0x131ae48, +0x13c9b24 of them) */
void THISCALL (stage_updateObjects)(void *s, int dt)
{
	if (paused(s))
		return;
	for (int i = 0; i < ST->objectCount; i++)
		if (ST->objects[i].active == 1)
			actor_render(s, i, dt);
}

/* 0x479950 (thiscall on the scene): an effect started in the next free slot (+0x20f2da4; at most 999): a slot added
   when that is the count (+0x20f2da0, the new one marked free), the next free one after it found (none: it stays),
   then the effect set up (particle_init). Returns its slot, or -1 */
int THISCALL (particle_spawn)(u8 *s, u32 desc)
{
#define COUNT ST->projectileCount
#define NEXT ST->projectileFreeHint
	if (NEXT >= 1000)
		return -1;
	if (NEXT == COUNT) {
		COUNT++;
		ST->projectiles[COUNT].active = 0;
	}
	int slot = NEXT;
	for (int k = slot + 1; k <= COUNT; k++)
		if (ST->projectiles[k].active == 0) {
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

/* 0x47ce50 (thiscall on the scene): a bullet fired (a4 its weapon: none with a4 +4 negative) into the next free slot
   (+0x20a99b8; at most 399; a slot added when that is the count, +0x20a99b4), the next free one after it found, then
   the bullet set up (bullet_init). Returns its slot, or -1 */
int THISCALL (bullet_spawn)(u8 *s, u32 a1, u32 a2, u32 a3, const u8 *a4, u32 a5)
{
#define COUNT ST->bulletSlotsUsed
#define NEXT ST->bulletFreeHint
	if (GAME_VAR(int, a4 + 4) < 0 || NEXT >= 400)
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
#define COUNT ST->objectCount
#define NEXT ST->objectFreeHint
	if (NEXT >= 1000) {
		sys_errorMessage((char *)OBJ(g_logStage), (const char *)STR(0x4c8398, "objectPool overflow(%d/%d)-addObjectBy()"), NEXT + 1, 1000);
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

/* 0x483640 (thiscall on the scene): the map's triggers (0x1c-byte records from +0xe3b038, +0xe3c938 of them): each
   armed one (+8 1) fires (+0x18) on its time (flag 1: the clock, +0x20fcd40 + +0x20fcd44, reaching +0x10) or on the
   player (flag 2: the player's actor, +0x202e8d4, within the squared radius +0x14 of its way point, +4; a NaN distance
   counts as within). Then each fired one runs its command (script_processCommandBy), is disarmed, and noted in the
   fired list (+0xe3c618, one dword each, the others 0) */
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
		int player = ST->playerActor;
		if (flags & 2 && player >= 0) {
			const float *at = ST->actors[player].pos;
			const float *point = ((const float *)t->wayPoints);
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
	if (!((Scene *)s)->roundOver)
		room_keepText();
	BITS(((Scene *)s)->emblemTime) = 0x43960000;   /* 300.0f */
#undef ACTOR
#undef NOW
#undef LAST
}

/* 0x48ec20 (thiscall on the scene): the effects' shapes looked up in the shape cache (+0x19e188c): three sets of eight
   numbered ones (+0x20f2dac, +0x20f2dcc, +0x20f2dec; named by 0x4c8170, 0x4c815c, 0x4c8144) and eight single ones
   (+0x20f2e74 ..); +0x20f2f3c cleared first. Its caller ignores the eax it leaves */
void THISCALL (effect_initTextures)(u8 *s)
{
	static const u32 sets[3] = { STR(0x4c8170, "Effect\\PlasmaThrust-%d"), STR(0x4c815c, "Effect\\IonThrust-%d"), STR(0x4c8144, "Effect\\GravityThrust-%d") };
	static const u32 singles[8] = { STR(0x4c8130, "Effect\\Shell-Fire"), STR(0x4c811c, "Effect\\Shell-Bullet"), STR(0x4c8108, "Effect\\Rail-Fire"), STR(0x4c80f4, "Effect\\Blade-Fire"), STR(0x4c80e0, "Effect\\Rail-Bullet"), STR(0x4c80c8, "Effect\\Lightning-Bullet"), STR(0x4c80b0, "Effect\\Missile-Bullet"), STR(0x4c8098, "Effect\\Homing-Bullet") };
	ST->itemTextures[0] = 0;
	char name[0x100];
	for (int set = 0; set < 3; set++)
		for (int k = 0; k < 8; k++) {
			sprintf(name, (const char *)RELOC(sets[set]), k);
			ST->thrustShapes[set][k] = shape_getByName((u8 *)&ST->partShapes, name, 1);
		}
	for (int k = 0; k < 8; k++)
		ST->effectShapes[k] = shape_getByName((u8 *)&ST->partShapes, (const char *)RELOC(singles[k]), 1);
}

/* 0x483770 (thiscall on the scene): entry `entry` of trigger trig's script (the triggers' 0x1c-byte records from
   +0xe3b03c, +0 their entry list; an entry 0x14 bytes: +0xc its command count, +0x10 the 0x30-byte commands) run for
   actor a (none when negative; actors are 0x8888 bytes from +0x1cd93a8). Each command by its type: triggers on / off
   (+4) and armed (+0x14); the actor's orders, targets, speed and flags; actors spawned, reset or deactivated; the
   camera's target; events; .scp files, animations and sounds by formatted names; objects (de)activated. Its callers
   ignore the eax it leaves */
void THISCALL (script_processCommandBy)(u8 *s, int a, int trig, int entry)
{
#define ACTOR(i, type, offset) FIELD(type, s, 0x1cd93a8 + (i) * 0x8888 + (offset))
	u8 *actor = a >= 0 ? (u8 *)&ST->actors[a] : NULL;
	Player *ac = (Player *)actor;
	WayPoint *e = (WayPoint *)(ST->triggers[trig].wayPoints + entry * 0x14);
	char name[0x100];
	for (int i = 0; i < e->commandCount; i++) {
		u32 *c = (u32 *)(e->commands + i * 0x30);
		switch (c[0]) {
		case 0: ST->triggers[c[1]].armed = 1; break;
		case 1: ST->triggers[c[1]].armed = 0; break;
		case 2: ST->triggers[c[1]].fired = 1; break;
		case 3: stage_triggerActionNone(s, c[1]); break;
		case 4: if (actor) BITS(ac->botWait) = c[1]; break;
		case 5: if (actor) (*(u32 *)&ac->botWaitTrigger) = c[1]; break;
		case 7:
			if (actor) {
				ac->target1 = c[1];
				ac->target2 = c[2];
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
		case 10: if (actor) (*(int *)&ac->spawn78) = 0; break;
		case 11: if (actor) (*(int *)&ac->spawn78) = 1; break;
		case 12:
			if (actor) {
				(*(int *)&ac->botWait) = 0;
				ac->botWaitTrigger = -1;
				BITS(ac->speed) = BITS(ac->topSpeed);
				ac->invulnerable = 0;
				ac->lookActor = ac->lookPath = ac->lookPoint = ac->followTarget = -1;
			}
			break;
		case 13:
			if (actor)
				ac->speed = f32(fmul_m(fld_m((const float *)&c[1]), (const float *)ADDR(k_27_7778f)));
			break;
		case 14: if (actor) ac->invulnerable = 1; break;
		case 15: actor_applySpawnRecord(s, c[1], (u8 *)&ST->mapActors[c[1]]); break;
		case 16: ACTOR(c[1], int, 0x128) = 0; break;
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
						actor_selectWeapon((Stage *)s, a, k);
				ac->inFire = 1;
			}
			break;
		case 21: if (actor) (*(u32 *)&ac->followTarget) = c[1]; break;
		case 22:
			ACTOR(c[1], int, 0x87f8) = -1;
			ACTOR(c[1], int, 0x87fc) = -1;
			break;
		case 23:
			ST->actors[c[1]].target1 = c[2];
			ST->actors[c[1]].target2 = c[3];
			break;
		case 24: camera_setTarget(s, c[1], c[2], c[3]); break;
		case 25: camera_setTarget(s, -1, -1, 0); break;
		case 26:
			if (FIELD(int, s, 0x2104fe8 + c[1] * 0x88) == 0)
				sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c7a8c, "invalid speaker (%d) in command MESSA..."), c[1]);
			if (FIELD(int, s, 0x210850c + c[2] * 0x108) == 0)
				sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c7a48, "invalid text (%d) in command MESSAGE ..."), c[2]);
			script_pushEvent(s, c[1], c[2], c[3], c[4]);
			break;
		case 27:
			sprintf(name, (const char *)STR(0x4c7a3c, "%s/%s.scp"), ST->sceneDir, (const char *)&c[1]);
			script_runScpFile(s, name, c[9]);
			break;
		case 28:
			sprintf(name, (const char *)STR(0x4c7a30, "%s/%s/%s"), s + 8, ST->stageName, (const char *)&c[2]);
			object_setAnimation(s, c[1], name, c[10], c[11]);
			break;
		case 29:
			sprintf(name, (const char *)STR(0x4c7a20, "%s/Sound/%s.wav"), ST->stageName, (const char *)&c[1]);
			sound_playFile(name, 100);
			break;
		case 30: object_activate(s, c[1]); break;
		case 31: object_deactivate(s, c[1]); break;
		}
	}
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
	u8 *obj = (u8 *)&ST->objects[i];
	MapObject *mo = (MapObject *)obj;
	int idx = 0;
	for (; idx < ST->objectNameCount; idx++)
		if (!strcmp((const char *)RELOC(type), ST->objectNames[idx]))
			break;
	if (idx == ST->objectNameCount) {
		if (idx >= 1000)
			sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c8364, "object type buffer overflow (%d) - in..."), 1000);
		idx = ST->objectNameCount++;
		strcpy(ST->objectNames[idx], (const char *)RELOC(type));
	}
	mo->id = ST->objectSerial++;
	mo->active = 1;
	mo->nameIndex = idx;
	memcpy(obj + offsetof(MapObject, flags), type + offsetof(ObjectType, flags), 12);   /* flags, trigger, animSpeed */
	if (type[0x4c])
		sprintf(mo->animPath, (const char *)STR(0x4c7a30, "%s/%s/%s"), ST->stageDir, ST->stageName, ((const ObjectType *)type)->animName);
	else
		obj[0x18] = 0;
	memcpy(mo->place, ((const ObjectType *)type)->place, 12);
	u32 move[16];
	identity4(move);
	for (int c = 0; c < 3; c++)
		((float *)RELOC(move))[12 + c] = f32(fld_m(mo->place + c));
	memcpy(mo->rotation, ((const ObjectType *)type)->rotation, 16);
	float turn[16];
	Mat4_fromQuat(turn, mo->rotation);
	float *m = mo->matrix;
	Mat4_multiply(mo->placeMatrix, (const float *)RELOC(move), turn);
	Mat4_invert(mo->placeInverse, mo->placeMatrix);
	Mat4_copy(m, mo->placeMatrix);
	Mat4_invert(mo->matrixInverse, m);
	identity4((u32 *)mo->animMatrix);
	identity4((u32 *)mo->animInverse);
	Mat4_multiply(mo->relMatrix, m, mo->placeInverse);
	Mat4_invert(mo->relInverse, mo->relMatrix);
	u8 *shape = (u8 *)shape_getByName((u8 *)&ST->objectShapes, (const char *)RELOC(type), 1);
	mo->model = (Model *)shape;
	for (int r = 0; r < 2; r++) {
		int need = ST->objectColourCount + FIELD(int, shape, 0x18);
		if (need > 1000000)
			sys_fatalErrorN((char *)OBJ(g_logStage), (const char *)STR(0x4c8314, "object(%d) objectShapeElementShadingC..."), i, need, 1000000);
		mo->colours[r] = (u32)&ST->objectColours[ST->objectColourCount];
		ST->objectColourCount += FIELD(int, ((u8 *)mo->model), 0x18);
	}
	mo->colourSide = 1;
	mo->typeValue1 = ((const ObjectType *)type)->value1;
	mo->typeValue2 = ((const ObjectType *)type)->value2;
	memset(obj + offsetof(MapObject, unit), 0, 7 * 4);   /* unit .. poseStale */
	if (shape) {
		const float *c = ((const Model *)shape)->centre;
		float *out = mo->pos;
		out[0] = f32(fadd_m(fmul_m(fld_m(&m[8]), &c[2]) + fmul_m(fld_m(&m[4]), &c[1]) + fmul_m(fld_m(&m[0]), &c[0]), &m[12]));
		for (int r = 1; r < 3; r++)
			out[r] = f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &c[2]) + fmul_m(fld_m(&m[r]), &c[0]) + fmul_m(fld_m(&m[4 + r]), &c[1]), &m[12 + r]));
	} else
		memcpy(mo->pos, mo->place, 12);
	BITS(mo->glow) = 0;
	BITS(mo->waitTime) = 0;
	if (ST->mapShaded == 0)
		shape_shadeParts((*(u32 * *)&mo->colours[0]), 1, (Model *)((u8 *)mo->model), (const LightFactors *)&((Stage *)s)->mapLights,
		                 mo->matrixInverse);
}

/* a particle of kind at p (particle_spawn's record: the kind, 0, the point, the world's colour 0xa0e7e8, zeros) */
static void spawn_at(u8 *s, u32 kind, const float *p)
{
	u32 rec[13] = { kind, 0 };
	memcpy(&rec[2], p, 12);
	memcpy(&rec[5], (const void *)ADDR(g_vecZero), 12);
	particle_spawn(s, rec);
}

/* a falling spark (kind 9) moved by its velocity (+0x1c) over dt and dropped 2000 dt further: what it meets on the
   way (collision_rayTrace) stops it there, ends it and leaves a kind 2 particle; its orientation (+0x2c) turned by
   its age; every tenth of a second a trail particle (kind 2 one time in ten, which also ends it, else kind 0) */
static void spark(u8 *s, u8 *p, float dt)
{
	float *pos = ((Projectile *)p)->pos;
	const float *v = ((Projectile *)p)->target, *k = (const float *)ADDR(k_2000f);
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
		BITS(((Projectile *)p)->life) = BITS(((Projectile *)p)->drawAge);
		spawn_at(s, 2, hit);
	} else
		memcpy(pos, below, 12);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef_stored(pos);
	glRotatef(f32(fmul_m(fld_m(&((Projectile *)p)->drawAge), (const float *)ADDR(k_3600f))), 0.0f, 1.0f, 0.0f);
	glRotatef(f32(fmul_m(fld_m(&((Projectile *)p)->drawAge), (const float *)ADDR(k_3600f))), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, ((Projectile *)p)->matrix);
	glPopMatrix();
	long double wait = fsub_m(fld_m(&((Projectile *)p)->fade), &dt);
	((Projectile *)p)->fade = f32(wait);
	if (wait > 0)
		return;
	u32 at = g_randPos;
	u32 r = GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4) % 10;
	g_randPos = at + 1;
	spawn_at(s, r ? 0 : 2, pos);
	BITS(((Projectile *)p)->fade) = 0x3dcccccd;
	if (!r)
		BITS(((Projectile *)p)->life) = BITS(((Projectile *)p)->drawAge);
}

/* 0x476410 (thiscall on the scene): particle slot's frame (0x12c bytes from +0x20a99c0). Its age (+0x74, kept at +0x6c)
   past its life (+0x70) frees it (0x4799f0); otherwise sparks move (spark), and puffs and flashes (kinds 2, 3, 25,
   26, 30 .. 38) shrink with age, (1 - age / life)^2 times their size (+0x7c); the age moves on by dt. Its caller
   ignores the eax it leaves */
void THISCALL (particle_update)(u8 *s, int slot, float dt)
{
	u8 *p = (u8 *)&ST->projectiles[slot];
	float age = ((Projectile *)p)->age;
	((Projectile *)p)->drawAge = age;
	if (age > ((Projectile *)p)->life) {
		stage_freeProjectile(s, slot);
		return;
	}
	float t = ((Projectile *)p)->life > 0 ? f32(fdiv_m(fld_m(&age), &((Projectile *)p)->life)) : 0.0f;
	int k = ((Projectile *)p)->kind;
	u32 size = 0;   /* where the size constant is */
	switch (k / 5) {
	case 0:
		size = k == 2 ? ADDR(k_3000f) : k == 3 ? ADDR(k_5000f) : 0;
		break;
	case 1:
		if (k == 9)
			spark(s, p, dt);
		break;
	case 5:
		size = k == 25 || k == 26 ? ADDR(k_2000f) : 0;
		break;
	case 6:
		size = k <= 31 ? OBJ(k_1000f) : ADDR(k_1500f);
		break;
	case 7:
		size = k == 35 ? ADDR(k_5000f) : k == 36 ? ADDR(k_3000f) : k <= 38 ? ADDR(k_1500f) : 0;
		break;
	}
	if (size) {
		long double u = fsub_m(fld_m((const float *)ADDR(k_1f)), &t);
		((Projectile *)p)->size = f32(fmul_m(u * u, (const float *)RELOC(size)));
	}
	((Projectile *)p)->age = f32(fadd_m(fld_m(&dt), &((Projectile *)p)->age));
}

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */
#define I(type, offset) GAME_VAR(type, it + (offset))

/* the cells, armour and shield items (kinds 0 .. 5, 10 .. 19): the actor's flag (+0x3f0) that refuses them, the
   count raised, its limit (and how far an extended one may go past it), the message; an extended one is noted as the
   last big pickup (+0x20fcd3c) */
static const struct { u8 flag; u16 count, limit; u8 add, over; u32 text; } k_supplies[16] = {
	{ 0x10, 0x130, 0x28, 1, 0, STR(0x4c82f4, "+1 30MM CELL") }, { 0x10, 0x130, 0x28, 40, 0, STR(0x4c82e4, "+40 30MM CELLS") }, { 0x20, 0x134, 0x2c, 40, 0, STR(0x4c82d4, "+40 60MM CELLS") },
	{ 0x40, 0x138, 0x30, 40, 0, STR(0x4c82c0, "+40 E-PACK CELLS") }, { 0x80, 0x13c, 0x34, 15, 0, STR(0x4c82ac, "+15 MISSILE CELLS") }, { 0x80, 0x13c, 0x34, 5, 0, STR(0x4c8298, "+5 MISSILE CELLS") },
	{ 1, 0x128, 0x1c, 10, 0, STR(0x4c828c, "+10 ARMOR") }, { 1, 0x128, 0x1c, 25, 0, STR(0x4c8280, "+25 ARMOR") }, { 1, 0x128, 0x1c, 50, 0, STR(0x4c8274, "+50 ARMOR") },
	{ 1, 0x128, 0x1c, 100, 0, STR(0x4c8268, "+100 ARMOR") }, { 2, 0x128, 0x1c, 100, 100, STR(0x4c8254, "+100 EXTENDED ARMOR") }, { 4, 0x12c, 0x20, 10, 0, STR(0x4c8248, "+10 SHIELD") },
	{ 4, 0x12c, 0x20, 25, 0, STR(0x4c823c, "+25 SHIELD") }, { 4, 0x12c, 0x20, 50, 0, STR(0x4c8230, "+50 SHIELD") }, { 4, 0x12c, 0x20, 100, 0, STR(0x4c8224, "+100 SHIELD") },
	{ 8, 0x12c, 0x20, 100, 100, STR(0x4c820c, "+100 EXTENDED SHIELD") } };

/* the item's sound (its type's +0x40 or +0x44) at its position, heard from the camera */
static void item_sound(u8 *s, int sound, u8 *it)
{
	sound_play3D(sound, ST->cameraPos,
	                                                                                ((const MapItem *)it)->pos, ST->viewDir, 0x47c35000);   /* (heard to 100000) */
}

/* actor ac touching item i (of kind type, its type record t): what it gives. Supplies the actor can use are taken;
   power-ups (damage amp, cloak, booster, gravity armour: 30 s each) are taken; a warp zone (kind 24 / 34) sends the
   local player, when not already warping and not just arrived from it, to the linked item's (+4) place and heading
   without being taken; other kinds are an error message (0 .. 9: fatal) */
static void item_pickup(u8 *s, u8 *ac, u8 *it, int i, u8 *t, int type)
{
	MapItem *mi = (MapItem *)it;
	u32 text, *timer = NULL;
	int last = 0;
	switch (type / 10) {
	case 0:
	case 1: {
		if (type < 10 && type > 5) {
			sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c81d0, "can't figure out the item type (%d) -..."), type);
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
		case 0: timer = &BITS(AC->timers[0]); text = STR(0x4c81c4, "DAMAGE AMP"); break;   /* DAMAGE AMP */
		case 1: timer = &BITS(AC->timers[1]); text = STR(0x4c81b4, "CLOAKING FIELD"); break;   /* CLOAKING FIELD */
		case 3: timer = &BITS(AC->timers[2]); text = STR(0x4c81a4, "OVERED BOOSTER"); break;   /* OVERED BOOSTER */
		case 7: timer = &BITS(AC->timers[3]); text = STR(0x4c8188, "GRAVITY ARMOR"); break;   /* GRAVITY ARMOR */
		case 4: {
			int warped = 0;
			if (AC->pilot == ST->playerActor && !(AC->warpWait > 0) && AC->lastWarp != i) {
				MapItem *to = &ST->items[mi->warpTo];
				memcpy(AC->nextPos, to->pos, 12);
				AC->nextPitch = f32(fmul_m((long double)to->warpPitch, (const float *)ADDR(k_10f)));
				BITS(AC->nextYaw) = BITS(to->angle);
				AC->lastWarp = mi->warpTo;
				strcpy(AC->message, (const char *)STR(0x4c8198, "WARP ZONE"));   /* WARP ZONE */
				AC->messageTime = 0.0f;
				AC->damageFlash = 1.0f;
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
		last = 1;
		break;
	default:
		GAME_FN(sys_errorMessage, 0x46c5f0, void, char *, const char *, int)((char *)OBJ(g_logStage), (const char *)STR(0x4c81d0, "can't figure out the item type (%d) -..."), type);
		return;
	}
	strcpy(AC->message, (const char *)RELOC(text));
	AC->messageTime = 0.0f;
	if (last)
		ST->lastPickup = i;
	item_sound(s, ((ItemType *)t)->pickSound, it);
	mi->taken = 1;
	mi->fade = 0.0f;
}

/* 0x48ed90 (thiscall on the scene): the items' frame. Live actors' touch flags (+0x53c) cleared; every item (0x28
   bytes from +0x20fadf8, +0x20fcd38 of them; its kind +0 into the 0x90-byte types at +0x20f3ae0, state +0x20, timer
   +0x24, position +0xc): a taken one comes back after its type's time (+0x48, with its sound +0x40); a present one
   spins (+0x1c, 600 a second, but kind 0x22) and the first live actor within 1.5 of its radius (+0x3e8) on every
   axis touches it (item_pickup). An actor touching no warp zone forgets the last one (+0x538 -1). Its callers ignore
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
		u8 *t = (u8 *)&ST->itemTypes[type];
		if (mi->taken == 1) {
			if (mi->fade > ((ItemType *)t)->respawnTime) {
				item_sound(s, ((ItemType *)t)->respawnSound, it);
				mi->taken = 0;
				mi->fade = 0.0f;
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
					item_pickup(s, ac, it, i, t, type);
					break;
				}
			}
		}
		mi->fade = f32(fadd_m(fld_m(&dt), &mi->fade));
	}
	for (int k = 0; k < ST->actorCount; k++) {
		u8 *ac = (u8 *)&ST->actors[k];
		if (AC->onWarp == 0)
			AC->lastWarp = -1;
	}
}
#undef A
#undef I

#define P(type, offset) GAME_VAR(type, p + (offset))
#define PR ((Projectile *)p)   /* the same by its fields (src/scene.fields) */
#define K(address) ((const float *)RELOC(address))

/* the next of the game's random numbers (its table 0xa106f8 by the counter 0xa1efb8) below n */
static u32 table_rand_below(u32 n)
{
	u32 at = g_randPos;
	u32 r = GAME_VAR(u32, OBJ(g_randTable) + (at & 0xfff) * 4) % n;
	g_randPos = at + 1;
	return r;
}

/* the particle's direction (+0x10, from 0xa0e7a8 through its matrix +0x2c) */
static void particle_heading(u8 *p)
{
	const float *m = PR->matrix, *v = (const float *)ADDR(g_vecOrigin);
	for (int r = 0; r < 3; r++)
		PR->pos[r] = f32(fadd_m(fmul_m(fld_m(&v[2]), &m[8 + r]) + fmul_m(fld_m(&v[1]), &m[4 + r]) + fmul_m(fld_m(&v[0]), &m[r]),
		                                    &m[12 + r]));
}

/* a matrix from the particle's own (+0x28) turned by a random whole degree about z (its +0x2c), and the direction */
static void particle_spin(u8 *p)
{
	glPushMatrix();
	glLoadIdentity();
	glLoadMatrixf((*(const float * *)&PR->matrixFrom));
	glRotatef((float)table_rand_below(360), 0.0f, 0.0f, 1.0f);
	glGetFloatv(0xba6, PR->matrix);
	glPopMatrix();
	particle_heading(p);
}

/* the particle's +0x2c the inverse of a look from its position (+0x10) to its target (+0x1c), stretched by their
   distance (z) and xy (1, or by size +0x80) */
static void particle_aim(u8 *p, int by_size)
{
	float d[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(PR->target + k), PR->pos + k));
	float len = f32(Vec3_normalize(d));
	glPushMatrix();
	glLoadIdentity();
	float xy = by_size ? f32(fld_m(K(0x4a9424)) / fadd_m(fmul_m(fld_m(&PR->baseSize), K(0x4a9504)), K(0x4a9424))) : 1.0f;
	float z = f32(fld_m(K(0x4a9424)) / fmul_m(fld_m(&len), K(0x4a9504)));
	glScalef_bits(*(u32 *)&xy, *(u32 *)&xy, *(u32 *)&z);
	gluLookAt(PR->pos[0], PR->pos[1], PR->pos[2], PR->target[0], PR->target[1], PR->target[2], 0.0, 1.0, 0.0);
	float m[16];
	glGetFloatv(0xba6, m);
	Mat4_invert(PR->matrix, m);
	glPopMatrix();
}

/* a beam (kinds 25 / 26, its colour): its matrix looking back from the target (+0x1c) away from the position, and
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
		memcpy(&rec[5], (const void *)OBJ(g_vecZero2), 12);
		float size = f32(fld_m(&PR->baseSize));
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
		memcpy(&rec[5], (const void *)OBJ(g_vecZero2), 12);
		rec[8] = rec[9] = rec[10] = 0;
		float size = f32(fld_m(&PR->baseSize));
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
	const ParticleDesc *pd = (const ParticleDesc *)desc;
	PR->life = 2.0f;   /* 2 s */
	memcpy(p + 0x84, pd->trailPoints, 12);
	memcpy(p + 0x90, pd->trailPoints + 3, 12);
	memcpy(p + 0x9c, pd->trailPoints + 6, 12);
	const float *q = pd->trailSizes;
	static const u8 from[5] = { 0, 2, 3, 4, 5 }, to[5] = { 0xb4, 0xbc, 0xc0, 0xc4, 0xc8 };
	if (!margin) {
		for (int k = 0; k < 5; k++) {
			P(float, to[k]) = f32(fadd_m(fmul_m(fld_m(&q[from[k]]), K(0x4aa428)), K(0x4a942c)));
			if (k == 0)
				P(u32, 0xb8) = 0x3f000000;
		}
	} else {
		long double d = fadd_m(fld_m(&PR->baseSize), K(margin));
		for (int k = 0; k < 5; k++) {
			P(float, to[k]) = f32(fmul_m(fadd_m(fld_m(&q[from[k]]) / d, K(0x4a9424)), K(0x4a942c)));
			if (k == 0)
				P(u32, 0xb8) = 0x3f000000;
		}
	}
	PR->cornerColours[0] = PR->cornerColours[1] = PR->cornerColours[2] = g_white;
}

/* 0x475070 (thiscall on the scene): particle slot (0x12c bytes from +0x20a99c0) set up from its descriptor: a
   serial id, in use. A descriptor flagged +0x30 is a kind 50 effect (its 0x48 bytes from +0x34). Otherwise the
   kind (+0), owner, position, target, a matrix to copy, the size (+0x2c); then by kind its life (+0x70) and: 2 / 3
   a sound at the position; 4 its colour from +0x20; 9 a fade; 10 / 11 / 18 a random spin; 12 .. 17 the heading
   through its matrix; 20 / 21 / 24 aimed at the target; 25 / 26 beams; 40 .. 49 trails */
void THISCALL (particle_init)(u8 *s, int slot, const u8 *desc)
{
	const ParticleDesc *pd = (const ParticleDesc *)desc;
	u8 *p = (u8 *)&ST->projectiles[slot];
	PR->id = ST->projectileSerial++;
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
		Mat4_copy(p + 0x2c, (*(const void * *)&PR->matrixFrom));
	PR->drawAge = 0.0f;
	PR->life = 1.0f;
	PR->age = 0.0f;
	PR->colour = g_white;
	PR->size = 0.0f;
	BITS(PR->baseSize) = pd->size;
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
		PR->fade = 0.1f;
		break;
	case 10: case 11: case 18:
		PR->life = 0.01f;
		particle_spin(p);
		break;
	case 12: case 13: case 17:
		PR->life = 0.01f;
		particle_heading(p);
		break;
	case 14: case 15: case 16:
		PR->life = 0.5f;
		particle_heading(p);
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
	case 40: case 41: case 49: particle_trail(p, desc, 0); break;
	case 42: case 43: case 44: case 46: case 47: case 48: particle_trail(p, desc, ADDR(k_200f)); break;
	case 45: particle_trail(p, desc, ADDR(k_400f)); break;
	}
}
#undef P
#undef K
