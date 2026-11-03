/* actor_slots.c: the stage's actor slots: selecting one, the camera's target, an actor's input record, and the
   stage's pools of map objects, projectiles and bullets emptied. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* an actor's input record: twelve ints (the moves and buttons the actor acts on this frame); the ninth is the
   one cleared to -1 */
static const int input_fields[12] = { 0x44c, 0x450, 0x454, 0x458, 0x464, 0x468, 0x46c, 0x470, 0x474, 0x478, 0x47c,
                                      0x480 };

/* 0x45eab0: actor i's input cleared */
void THISCALL (actor_clearInput)(Stage *stage, int i)
{
	Player *a = &stage->actors[i];
	for (int k = 0; k < 12; k++)
		FIELD(int, a, input_fields[k]) = k == 9 ? -1 : 0;
}

/* 0x45eb20: actor i's input set */
void THISCALL (actor_setInput)(Stage *stage, int i, int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
                             int v8, int v9, int v10, int v11)
{
	Player *a = &stage->actors[i];
	const int v[12] = { v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11 };
	for (int k = 0; k < 12; k++)
		FIELD(int, a, input_fields[k]) = v[k];
}

/* 0x45dff0: the camera follows actor i in mode with value (kept in the actor, +0x884c); the actor followed before
   loses its value. A negative i follows none; an actor not in use is not followed */
void THISCALL (camera_setTarget)(Stage *stage, int i, int mode, int value)
{
	int *target = &FIELD(int, stage, 0x202e8e0);
	if (*target > -1)
		FIELD(int, &stage->actors[*target], 0x884c) = 0;
	if (i < 0 || stage->actors[i].state == 1) {
		*target = i;
		FIELD(int, stage, 0x202e8e4) = mode;
		FIELD(int, &stage->actors[i], 0x884c) = value;
	}
}

/* ---- the pools emptied (each slot's "in use" cleared, the counters zeroed) ---- */
/* 0x490d10: the 1000 map objects */
void THISCALL (stage_clearMapObjects)(Stage *stage)
{
	FIELD(int, stage, 0x13016c8) = 0;
	stage->objectCount = 0;
	FIELD(int, stage, 0x13c9b28) = 0;
	FIELD(int, stage, 0x13c9b2c) = 0;
	for (int i = 0; i < 1000; i++)
		stage->objects[i].active = 0;
}

/* 0x479a60: the 1000 projectiles */
void THISCALL (stage_clearProjectiles)(Stage *stage)
{
	stage->projectileCount = 0;
	FIELD(int, stage, 0x20f2da4) = 0;
	FIELD(int, stage, 0x20f2da8) = 0;
	for (int i = 0; i < 1000; i++)
		stage->projectiles[i].active = 0;
}

/* 0x4799f0: projectile slot i freed: the first-free hint (+0x20f2da4) moved down to it, and when it was the last
   in use the used range (projectileCount) shrinks past every free slot at its end */
void THISCALL (stage_freeProjectile)(Stage *stage, int i)
{
	if (!stage->projectiles[i].active)
		return;
	stage->projectiles[i].active = 0;
	if (i < FIELD(int, stage, 0x20f2da4))
		FIELD(int, stage, 0x20f2da4) = i;
	if (i != stage->projectileCount - 1 || stage->projectileCount <= 0)
		return;
	do {
		if (stage->projectiles[stage->projectileCount - 1].active)
			return;
	} while (--stage->projectileCount > 0);
}

/* 0x47cfd0: the 400 bullets (0x4e8-byte records from 0x202ef34) */
void THISCALL (stage_clearBullets)(Stage *stage)
{
	FIELD(int, stage, 0x20a99b4) = 0;
	FIELD(int, stage, 0x20a99b8) = 0;
	FIELD(int, stage, 0x20a99bc) = 0;
	for (int i = 0; i < 400; i++)
		FIELD(int, stage, 0x202ef38 + i * 0x4e8) = 0;
}

/* 0x4743e0: actor slot i emptied: no name, no player (-1), no team (-1), its counters and marks cleared */
void THISCALL (actor_resetSlot)(Stage *stage, int i)
{
	Player *a = &stage->actors[i];
	a->name[0] = '\0';
	a->player = -1;
	FIELD(int, a, 0x114) = 0;
	a->team = -1;
	for (int k = 0; k < 11; k++)
		FIELD(int, a, 0xd8 + k * 4) = 0;
	a->state = 0;
	FIELD(int, a, 0x4d4) = 0;
	a->viewMarked = 0;
	a->markSolo = 0;
	a->markTeam = 0;
}

/* 0x47d060: every bullet in use drawn (its trail, bullet_drawTrail) */
void THISCALL (stage_drawBullets)(Stage *stage, void *view)
{
	for (int i = 0; i < FIELD(int, stage, 0x20a99b4); i++)
		if (FIELD(int, stage, 0x202ef38 + i * 0x4e8) == 1)
			bullet_drawTrail(stage, i, view);
}

/* 0x48fde0: while the script runs (+0x2149308), its object (+0x2148ed8) told (recorder_noteStub); returns b */
int THISCALL (script_notifyObject)(Stage *stage, int a, int b, int c, int d)
{
	if (!FIELD(int, stage, 0x2149308))
		return 0;
	recorder_noteStub((u8 *)stage + 0x2148ed8, a, b, c, d);
	return b;
}

/* 0x470a70: every actor slot emptied: the six slot numbers from playerActor on (-1), +0x202e8ec 1, the scores, the
   16 player records and the stage's own reset, then the 100 slots */
void THISCALL (scene_resetActors)(Stage *stage)
{
	for (int k = 0; k < 6; k++)
		FIELD(int, stage, 0x202e8d4 + k * 4) = -1;
	FIELD(int, stage, 0x202e8ec) = 1;
	stage_clearActorRefs(stage);
	stage_resetPlayerRecords(stage);
	stage_clearActorSlots(stage);
	for (int i = 0; i < 100; i++)
		actor_resetSlot(stage, i);
}

/* 0x45e070: the 100 actor slots emptied (none in use, each free with no player), with the counts */
void THISCALL (stage_clearActorSlots)(Stage *stage)
{
	FIELD(int, stage, 0x202e8c8) = 0;
	FIELD(int, stage, 0x202e8cc) = 0;
	FIELD(int, stage, 0x202e8d0) = 0;
	for (int i = 0; i < 100; i++) {
		u8 *a = (u8 *)stage + i * 0x8888;
		FIELD(int, a, 0x1cd94b0) = 0;
		FIELD(int, a, 0x1cd94b4) = -1;
		FIELD(int, a, 0x1cd94f4) = 0;
		FIELD(int, stage, 0x202ea80 + i * 4) = 0;
	}
}

/* 0x47cf10: bullet b is gone: its shooter's five target references to it dropped, its slot freed (the lowest free
   slot and the used count kept up to date) */
void THISCALL (actor_clearTargetRefs)(Stage *stage, int b)
{
	u8 *bullet = (u8 *)stage + b * 0x4e8;
	for (int k = 0; k < 5; k++) {
		int *ref = &FIELD(int, stage, FIELD(int, bullet, 0x202ef40) * 0x8888 + k * 4 + 0x1cd9708);
		if (*ref == b)
			*ref = -1;
	}
	if (!FIELD(int, bullet, 0x202ef38))
		return;
	FIELD(int, bullet, 0x202ef38) = 0;
	if (b < FIELD(int, stage, 0x20a99b8))
		FIELD(int, stage, 0x20a99b8) = b;
	int n = FIELD(int, stage, 0x20a99b4);
	if (b != n - 1 || n <= 0)
		return;
	do {
		n = FIELD(int, stage, 0x20a99b4);
		if (FIELD(int, stage, 0x202ea50 + n * 0x4e8))
			return;
		FIELD(int, stage, 0x20a99b4) = --n;
	} while (n > 0);
}

/* a player record's per-match state cleared (e = the record + 0x44): its name kept or not by the caller; the
   weapons, the five items and six part names, the 5 x 2 colour grid's three layers */
static void player_clear(u8 *e)
{
	e[8] = 0;
	e[0x48] = 0;
	e[0x88] = 0;
	e[0xc8] = 0;
	e[0x108] = 0;
	for (int k = 0; k < 5; k++)
		FIELD(int, e, 0x2c8 + k * 4) = -1;
	for (int k = 0; k < 6; k++) {
		e[0x148 + k * 0x40] = 0;
		FIELD(int, e, 0x2dc + k * 4) = -1;
	}
	for (int r = 0; r < 5; r++)
		for (int c = 0; c < 2; c++) {
			u8 *q = e + 0x4796a + r * 2 + c;
			q[-0xa] = 0;
			q[0] = 0;
			q[0xa] = 0;
		}
}

/* 0x474480: the 16 player records reset (unused, no name, no actor) with their colour grids; none seen */
void THISCALL (stage_resetPlayerRecords)(Stage *stage)
{
	for (int p = 0; p < 16; p++) {
		u8 *e = (u8 *)stage + 0x1561bac + p * 0x47fd2;
		FIELD(int, e, -0x44) = 0;
		e[-0x40] = 0;
		FIELD(int, e, 0) = 0;
		FIELD(int, e, 4) = -1;
		player_clear(e);
		playerRecord_resetColourGrid(stage, p);
	}
	FIELD(int, stage, 0x19e1888) = 0;
}

/* 0x470cb0: a new round: the actor slot numbers (-1), the scores, the 16 player records (their names kept), the
   actor slots, then each actor's round state */
void THISCALL (stage_newRound)(Stage *stage)
{
	for (int k = 0; k < 6; k++)
		FIELD(int, stage, 0x202e8d4 + k * 4) = -1;
	FIELD(int, stage, 0x202e8ec) = 1;
	stage_clearActorRefs(stage);
	for (int p = 0; p < 16; p++) {
		u8 *e = (u8 *)stage + 0x1561bac + p * 0x47fd2;
		FIELD(int, e, -0x44) = 0;
		FIELD(int, e, 4) = -1;
		player_clear(e);
	}
	FIELD(int, stage, 0x19e1888) = 0;
	stage_clearActorSlots(stage);
	static const short cleared[] = { 0, 0xc, 0x10, 0x18, 0x1c, 0x24, 0x28, 0x74, 0x3fc, 0x400, 0x404 };
	for (int i = 0; i < 100; i++) {
		u8 *a = (u8 *)stage + 0x1cd9480 + i * 0x8888;
		FIELD(int, a, 0x40) = -1;
		for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
			FIELD(int, a, cleared[k]) = 0;
	}
}

/* 0x45dca0: actor i taken out (if active): its state, the leader marks pointing at it, its slot freed (the lowest
   free slot and the used count kept up to date); the teams changed */
void THISCALL (actor_deactivate)(Stage *stage, int i)
{
	u8 *a = (u8 *)stage + i * 0x8888;
	if (!FIELD(int, a, 0x1cd94b0))
		return;
	FIELD(int, a, 0x1cd94b0) = 0;
	FIELD(int, a, 0x1cd94f4) = 0;
	FIELD(int, a, 0x1ce1b88) = 0;
	FIELD(int, a, 0x1ce1b90) = 0;
	FIELD(int, a, 0x1ce1b98) = 0;
	if (FIELD(int, stage, 0x20fce4c) == i)
		FIELD(int, stage, 0x20fce4c) = -1;
	int team = FIELD(int, a, 0x1cd94c0);
	if (team > -1 && FIELD(int, stage, 0x20fce50 + team * 4) == i)
		FIELD(int, stage, 0x20fce50 + team * 4) = -1;
	FIELD(int, stage, 0x202ea80 + i * 4) = 0;
	if (i < FIELD(int, stage, 0x202e8cc))
		FIELD(int, stage, 0x202e8cc) = i;
	int n = FIELD(int, stage, 0x202e8c8);
	if (i == n - 1)
		while (n > 0 && FIELD(int, stage, 0x1cd0c28 + FIELD(int, stage, 0x202e8c8) * 0x8888) == 0) {
			n = FIELD(int, stage, 0x202e8c8) - 1;
			FIELD(int, stage, 0x202e8c8) = n;
		}
	FIELD(int, stage, 0x202e8ec) = 1;
}

/* 0x45dc00 (thiscall on the scene): actor slot i (at most 99) set up from its parts (actor_setupFromParts): the
   slots up to it are added first (each new one marked free, +0x108), and the first free slot (searched up to and
   including the count, as the original does) kept as the next free (+0x202e8cc). Returns i, or -1 */
int THISCALL (stage_setupActorSlot)(u8 *scene, int i, u32 x, u32 y, u32 parts)
{
#define COUNT GAME_VAR(int, scene + 0x202e8c8)
#define USED(k) GAME_VAR(int, scene + 0x1cd94b0 + (k) * 0x8888)
	if (i >= 100)
		return -1;
	if (COUNT <= i) {
		for (int k = COUNT; k <= i; k++)
			USED(k) = 0;
		COUNT = i + 1;
	}
	for (int k = 0; k <= COUNT; k++)
		if (USED(k) == 0) {
			GAME_VAR(int, scene + 0x202e8cc) = k;
			break;
		}
	actor_setupFromParts(scene, i, x, y, parts);
	return i;
#undef COUNT
#undef USED
}

/* 0x474fd0: a player's part coloured from the network: six signed bytes, scaled (the first and fourth by 0x4aa41c,
   the others by 0x4aa420), given to actor_setPartColor. Its caller ignores the eax it leaves */
void THISCALL (actor_applyRemoteColours)(void *scene, int p, int part, int a, int b, int c, int d, int e, int f)
{
	long double k1 = k_1_40625f, k2 = k_0_0078125f;
	actor_setPartColor(scene, p, part, (float)((signed char)a * k1), (float)((signed char)b * k2), (float)((signed char)c * k2),
	                   (float)((signed char)d * k1), (float)((signed char)e * k2), (float)((signed char)f * k2));
}

/* The five parts' animations (0x45e1f0 .. 0x45e530): where each part's model and its own fields are. An actor's part
   type (its type record at +0x1561b68, 0x47fd2 bytes each, by the actor's +0x10c) names the part's model (by +model_at
   in that record); the actor's pose (+0x484) picks the model's frame */
typedef struct {
	int model_at;      /* the model's index in the type record */
	u32 models;        /* the models' table in the scene, */
	int model_size;    /* and each one's size */
	int bones, bone_size, counts, frames;   /* in the model: per pose */
	int data, names;   /* the type record's data handed over */
	int self;          /* the actor's loader for this part */
	u32 limit;
} PartModel;

static void part_load(u8 *scene, int a, const PartModel *m)
{
	u8 *actor = scene + 0x1cd93a8 + a * 0x8888;
	if (!GAME_VAR(int, actor + 0x108))
		return;
	u8 *type = scene + 0x1561b68 + GAME_VAR(int, actor + 0x10c) * 0x47fd2;
	u8 *model = scene + m->models + GAME_VAR(int, type + m->model_at) * m->model_size;
	int pose = GAME_VAR(int, actor + 0x484);
	ObjectList_load(actor + m->self, type + m->data, type + m->names, GAME_VAR(u32, model + 0x40 + pose * 4),
	                     model + m->bones + pose * m->bone_size, GAME_VAR(u32, model + m->counts + pose * 4),
	                     model + m->frames + pose * 0x80, 0, 0, 0, actor + m->self + 0x30, m->limit);
}

static const PartModel g_parts[5] = {
	{ 0x30c, 0x13c9b30, 0xaa8, 0x448, 0x220, 0x888, 0x990, 0x338, 0x43534, 0x554, 0x7d0 },
	{ 0x310, 0x13eb004, 0xabc, 0x448, 0x220, 0x888, 0x990, 0x8284, 0x43e34, 0xd54, 0x7d0 },
	{ 0x314, 0x140c8c0, 0x1300, 0x848, 0x440, 0x10c8, 0x11d0, 0x101d0, 0x44734, 0x1554, 0xfa0 },
	{ 0x318, 0x1447ec4, 0x13f4, 0x848, 0x440, 0x10c8, 0x11d0, 0x1fe1c, 0x45804, 0x2524, 0xfa0 },
	{ 0x31c, 0x1486470, 0x1820, 0xa48, 0x550, 0x14e8, 0x15f0, 0x2fa68, 0x468d4, 0x34f4, 0xbb8 },
};

/* (thiscall on the scene; their callers ignore the eax they leave) */
void THISCALL (actor_updateHead)(u8 *scene, int a) { part_load(scene, a, &g_parts[0]); }
void THISCALL (actor_updateBody)(u8 *scene, int a) { part_load(scene, a, &g_parts[1]); }
void THISCALL (actor_updateArms)(u8 *scene, int a) { part_load(scene, a, &g_parts[2]); }
void THISCALL (actor_updateLegs)(u8 *scene, int a) { part_load(scene, a, &g_parts[3]); }
void THISCALL (actor_updateBooster)(u8 *scene, int a) { part_load(scene, a, &g_parts[4]); }

/* 0x45de20 (thiscall on the scene): actor a spawned from a map record for the player (+0x202e8d4; none: a fatal
   message): set up from its parts (stage_setupActorSlot, with the record's position, angle and parts picked out), then given
   the record's settings: team and two values (kept twice), ranges and speeds scaled, its radius squared (scaled), a
   count from a scaled value, and the rest copied; no targets (+0x87f8, +0x87fc -1). Its callers ignore the eax it
   leaves */
void THISCALL (actor_applySpawnRecord)(u8 *scene, int a, const u8 *rec)
{
#define R(type, offset) GAME_VAR(type, rec + (offset))
	int player = GAME_VAR(int, scene + 0x202e8d4);
	if (player < 0)
		sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4b4538, "invalid player actor slot(%d) - spawn..."), player);
	u32 spawn[7] = { R(u32, 0), R(u32, 0x18), R(u32, 4), R(u32, 8), R(u32, 0xc) };
	((float *)RELOC(spawn))[5] = f32(fld_m(&R(float, 0x10)));
	((float *)RELOC(spawn))[6] = f32(fld_m(&R(float, 0x14)));
	stage_setupActorSlot((Stage *)scene, a, -1, GAME_VAR(int, scene + 0x202e8d4), spawn);
	if (a < 0)
		return;
	u8 *actor = scene + 0x1cd93a8 + a * 0x8888;
#define A(type, offset) GAME_VAR(type, actor + (offset))
#define AC ((Player *)actor)   /* the same by its fields (src/scene.fields) */
	AC->spawn64 = R(u32, 0x1c);
	(*(u32 *)&AC->armorMax) = R(u32, 0x20);
	(*(u32 *)&AC->shieldMax) = R(u32, 0x24);
	(*(u32 *)&AC->armor) = R(u32, 0x20);
	(*(u32 *)&AC->shield) = R(u32, 0x24);
	A(float, 0x68) = A(float, 0x50) = (float)(R(float, 0x28) * (long double)k_27_7778f);
	A(float, 0x6c) = (float)(R(float, 0x2c) * (long double)k_10f);
	long double radius = R(float, 0x30);
	AC->radiusSq = (float)(radius * radius * k_10000f);
	AC->spawn70 = R(u32, 0x34);
	AC->spawn74 = ftol(R(float, 0x38) * (long double)k_10f);
	AC->spawn78 = R(u32, 0x3c);
	A(float, 0x7c) = (float)(R(float, 0x40) * (long double)k_100f);
	A(float, 0x80) = (float)(R(float, 0x44) * (long double)k_100f);
	for (int k = 0; k < 5; k++)
		AC->spawnTail[k] = R(u32, 0x48 + k * 4);
	AC->target1 = -1;
	AC->target2 = -1;
#undef R
#undef A
#undef AC
}

/* 0x45ebc0 (thiscall on the scene): player p's starting values when the slot is in use (+0x108 1). Game types 2 ..
   11 (+0x20f3ab8) by pairs: the energy (+0x1c, +0x20, +0x128) 10 then 150, +0x12c 0, the four weapon slots
   (+0x130 ..) empty but one (the pair's: 10 the first, else 50, its +0x28 .. 100; the last pair none). Otherwise
   +0x128 / +0x12c from +0x1c / +0x20 and each slot half its +0x28 ... Its caller ignores the eax it leaves */
void THISCALL (actor_startingValues)(u8 *scene, int p)
{
	Player *a = (Player *)(scene + 0x1cd93a8 + p * 0x8888);
	if (a->active != 1)
		return;
	unsigned mode = FIELD(int, scene, 0x20f3ab8) - 2;
	if (mode <= 9) {
		int pair = mode / 2;
		int energy = pair == 0 ? 10 : 150;
		a->armorMax = a->shieldMax = a->armor = energy;
		a->shield = 0;
		for (int k = 0; k < 4; k++)
			if (k == pair) {
				a->ammoMax[k] = 100;
				a->ammo[k] = pair == 0 ? 10 : 50;
			} else
				a->ammo[k] = 0;
	} else {
		a->shield = a->shieldMax;
		a->armor = a->armorMax;
		for (int k = 0; k < 4; k++)
			a->ammo[k] = a->ammoMax[k] / 2;
	}
}

/* 0x45e600 (thiscall on the scene): actor a's item in slot (its player type record's +0x320 + slot x 4; negative:
   none) loaded, in the given variant, into the slot's loader: slots 4 and 5 their own (+0x587c; +0x701c, from the
   item's second set of tables), any other only when it is the selected one (+0x140: +0x40dc, and +0x4cc the item's
   +0x2dc0, -1 without). Without an item the loader is emptied (partList_release). Its callers ignore the eax it leaves */
void THISCALL (actor_updatePart)(u8 *scene, int a, int slot, int variant)
{
	u8 *actor = scene + 0x1cd93a8 + a * 0x8888;
	if (!FIELD(int, actor, 0x108))
		return;
	u8 *type = scene + 0x1561b68 + FIELD(int, actor, 0x10c) * 0x47fd2;
	int item = FIELD(int, type, 0x320 + slot * 4);
	u8 *it = item >= 0 ? scene + 0x14d1ab4 + item * 0x2e18 : NULL;
	int self, models = 0x40, bones = 0x94c, counts = 0x12dc, frames = 0x1468;
	if (slot == 4)
		self = 0x587c;
	else if (slot == 5) {
		self = 0x701c;
		models = 0x16fc, bones = 0x2008, counts = 0x2998, frames = 0x2b24;
	} else if (slot == FIELD(int, actor, 0x140))
		self = 0x40dc;
	else
		return;
	if (it)
		ObjectList_load(actor + self, scene + 0x19e188c, scene + 0x1cbe198, FIELD(u32, it, models + variant * 4),
		                     it + bones + variant * 0x330, FIELD(u32, it, counts + variant * 4), it + frames + variant * 0x80,
		                     0, 0, 0, actor + self + 0x30, 0x1770);
	else
		partList_release(actor + self);
	if (self == 0x40dc)
		FIELD(int, actor, 0x4cc) = it ? FIELD(int, it, 0x2dc0) : -1;
}

#define K(address) ((const float *)RELOC(address))

/* a hue as the colour code keeps it: wrapped (angle_wrap of it x 0x4a9418, then x 0x4a93ec), brought down by
   0x4a9460 when over 0x4a945c (*h updated); its byte ((h - 0x4aa418) x 0x4aa414 - 0x4aa264) */
static u8 hue_byte(float *h)
{
	long double v = fmul_m(angle_wrap(f32(fmul_m(fld_m(h), K(0x4a9418)))), K(0x4a93ec));
	*h = f32(v);
	if (v > *K(0x4a945c))
		*h = f32(fsub_m(fld_m(h), K(0x4a9460)));
	return (u8)ftol(fsub_m(fmul_m(fsub_m(fld_m(h), K(0x4aa418)), K(0x4aa414)), K(0x4aa264)));
}

/* a saturation or value kept to -1 .. 0.999 (a NaN -1; *v updated); its byte (v x 0x4aa264) */
static u8 level_byte(float *v)
{
	if (!(*v >= *K(0x4a9474)))
		*(u32 *)RELOC(v) = 0xbf800000;   /* -1.0 */
	else if (!(*v < *K(0x4a9424)))
		*(u32 *)RELOC(v) = 0x3f7fbe77;   /* 0.999 */
	return (u8)ftol(fmul_m(fld_m(v), K(0x4aa264)));
}

/* 0x474b50 (thiscall on the scene): player p's part (0 .. 4) coloured: two hue / saturation / value sets kept as
   bytes in the part type record's colour table (+0x479a4 + part x 2: hue, +0xa saturation, +0x14 value; the second
   set one byte on), then the part's shape (+0x338 .., 0x7f4c apart but the last) given textures from the player's
   directory (by 0x4c77f8) tinted with them (shape_setTextureDir). Its callers ignore the eax it leaves */
void THISCALL (actor_setPartColor)(u8 *scene, int p, int part, float h1, float s1, float v1, float h2, float s2, float v2)
{
	static const u32 shapes[5] = { 0x1561ea0, 0x1569dec, 0x1571d38, 0x1581984, 0x15915d0 };
	u8 *colours = scene + 0x15a950c + p * 0x47fd2 + part * 2;
	colours[0] = hue_byte(&h1);
	colours[0xa] = level_byte(&s1);
	colours[0x14] = level_byte(&v1);
	colours[1] = hue_byte(&h2);
	colours[0xb] = level_byte(&s2);
	colours[0x15] = level_byte(&v2);
	char dir[0x100];
	sprintf(dir, (const char *)STR(0x4c77f8, "_T%d"), p);
	if ((unsigned)part <= 4)
		shape_setTextureDir(scene + shapes[part] + p * 0x47fd2, dir, 2, *(u32 *)&h1, *(u32 *)&s1, *(u32 *)&v1,
		                    *(u32 *)&h2, *(u32 *)&s2, *(u32 *)&v2);
}
#undef K

#define K(address) ((const float *)RELOC(address))
#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */

/* the actor's eight object lists (the body, the parts, the weapons) */
static const u32 k_partLists[8] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x587c, 0x701c, 0x40dc };

/* the light the actor's flags ask for (0x100: +0x20f2f3c, 0x800: +0x20f2f44, else +0x20f2f40) */
static u32 flag_light(u8 *s, u32 f)
{
	return GAME_VAR(u32, s + (f & 0x100 ? 0x20f2f3c : f & 0x800 ? 0x20f2f44 : 0x20f2f40));
}

/* the list of the weapon in hand (+0x140: 4, 5, else the last) */
static u8 *weapon_list(u8 *ac)
{
	return ac + (AC->gaugeIcon == 4 ? 0x587c : AC->gaugeIcon == 5 ? 0x701c : 0x40dc);
}

/* 0x45d3e0 (thiscall on the scene): actor a drawn into the view volume vv when in play and within the view range
   (+0xa08 plus its radius +0x3e8) of the camera (+0x20f3970..) on every axis. Its tint (+0x4f0): a cloaked actor
   (flag 0x200) at the local player's rank or above white and faint (0x40 to itself, 0x10 to others); else a hit
   flash (+0x120 up to K 0x4a9534) fading in then out, or the damage glow (+0x4ec white, +0x8854 red-orange); a
   faint tint lights it with +0x20f2f48. The viewing actor (+0x202e8d8), when draw is set, shows only the weapon in
   hand; others, when draw is not 1, all their lists up to the count +0x54c (the fifth unless +0x550; flags 0xd00 skip
   them without flares 0x83a9c8 or when too small on screen; faint ones only with flares); flags 0x100 / 0xc00 add a
   lit pass. A list that would not draw has them all reloaded (actor_updateHead / actor_updateBody / actor_updateArms /
   actor_updateLegs / actor_updateBooster / actor_updatePart). Its caller ignores the eax it leaves */
void THISCALL (actor_updateAllParts)(u8 *s, int a, void *vv, int draw)
{
	u8 *ac = s + 0x1cd93a8 + a * 0x8888;
	if (AC->state != 1 || AC->cameraValue == 1)
		return;
	float r = f32(fadd_m(fld_m((const float *)(s + 0xa08)), (const float *)(ac + 0x3e8)));
	const float *cam = (const float *)(s + 0x20f3970), *at = (const float *)(ac + 0x154);
	for (int k = 0; k < 3; k++)
		if (fsub_m(fld_m(&cam[k]), &r) > at[k])
			return;
	for (int k = 0; k < 3; k++)
		if (!(fadd_m(fld_m(&r), &cam[k]) >= at[k]))
			return;
	u8 *tint = ac + 0x4f0;
	int local = GAME_VAR(int, s + 0x202e8d4);
	if ((((u32)AC->timerFlags) & 0x200) && A(int, 8) >= GAME_VAR(int, s + 0x1cd93b0 + local * 0x8888)) {
		tint[0] = tint[1] = tint[2] = 0xff;
		tint[3] = a == local ? 0x40 : 0x10;
	} else if (!(A(float, 0x120) > *K(0x4a9534))) {
		if (!(A(float, 0x120) >= *K(0x4a974c)))
			tint[0] = tint[1] = tint[2] = tint[3] = (u8)ftol(fmul_m(fld_m((const float *)(ac + 0x120)), K(0x4a9748)));
		else {
			tint[0] = tint[1] = tint[2] = (u8)(0xff - ftol(fmul_m(fsub_m(fld_m((const float *)(ac + 0x120)), K(0x4a974c)), K(0x4a9748))));
			tint[3] = 0xff;
		}
	} else if (A(float, 0x4ec) > 0 || AC->hitFlash > 0) {
		int c[3] = { 0, 0, 0 };
		if (A(float, 0x4ec) > 0)
			c[0] = c[1] = c[2] = ftol(fmul_m(fld_m((const float *)(ac + 0x4ec)), K(0x4a9744)));
		if (AC->hitFlash > 0) {
			int red = ftol(fmul_m(fld_m((const float *)(ac + 0x8854)), K(0x4a9744)));
			c[0] += red;
			c[1] += red / 2;
			c[2] += red / 2;
		}
		for (int k = 0; k < 3; k++)
			tint[k] = (u8)(c[k] > 0xff ? 0xff : c[k]);
		tint[3] = 0xff;
	} else
		tint = NULL;
	u32 light = tint && tint[3] <= 0x10 ? (u32)(s + 0x20f2f48) : 0;
	u8 *lights = s + 0x9e3020;
	int ok = 1;
	u32 f;
	if (a == GAME_VAR(int, s + 0x202e8d8)) {
		if (draw) {
			ok = partList_queue(weapon_list(ac), vv, lights, tint, 1, (u32)-1, light) & 1;
			f = ((u32)AC->timerFlags);
			if ((f & 0x100) || (f & 0xc00))
				ok &= partList_queue(weapon_list(ac), vv, lights, tint, 1, flag_light(s, f), (u32)(s + 0x20f2f88));
		}
	} else if (draw != 1) {
		f = ((u32)AC->timerFlags);
		int lists = 1;
		if (f & 0xd00) {
			if (g_items3D == 0)
				lists = 0;
			else {
				float size = f32(fsub_m(fld_m((const float *)(ac + 0x87d4)), (const float *)(ac + 0x87c8)));
				if (fmul_m(fld_m(K(0x4a9510)) / (long double)gfx_getWidth(), K(0x4a9414)) > size)
					lists = 0;
			}
		}
		if (lists && g_items3D != 1 && tint && tint[3] <= 0x10)
			lists = 0;
		if (lists) {
			int n = A(int, 0x54c);
			if (n < 0)
				return;
			for (int k = 0; k < 8; k++) {
				if (k > 0 && n < k)
					return;
				if (k == 4 && AC->viewMarked)
					continue;
				int r = partList_queue(ac + k_partLists[k], vv, lights, tint, 1, (u32)-1, light);
				ok = k ? ok & r : r & 1;
			}
		}
		f = ((u32)AC->timerFlags);
		if ((f & 0x100) || (f & 0xc00)) {
			u32 lt = flag_light(s, f);
			for (int k = 0; k < 8; k++)
				if (k != 4 || !AC->viewMarked)
					ok &= partList_queue(ac + k_partLists[k], vv, lights, tint, 1, lt, (u32)(s + 0x20f2f88));
		}
	}
	AC->viewMarked = 0;
	if (ok)
		return;
	actor_updateHead(s, a);
	actor_updateBody(s, a);
	actor_updateArms(s, a);
	actor_updateLegs(s, a);
	actor_updateBooster(s, a);
	for (int k = 0; k < 6; k++)
		actor_updatePart(s, a, k, A(u32, 0x49c));
}
#undef K
#undef A
#undef AC

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */
#define K(address) ((const float *)RELOC(address))

/* n dwords from at in the actor set to v */
static void fill_dwords(u8 *at, int n, u32 v)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(u32, at + k * 4) = v;
}

/* the pilot level's factor k (the level table 0x9f9078, 0x4c bytes a level, by the player's +0x44) as
   level value x 0.01 + 1 */
static long double level_factor(u8 *p, int k)
{
	return fadd_m(fmul_m((long double)GAME_VAR(int, OBJ(g_profileRecords) + 0x38 + GAME_VAR(int, p + 0x44) * 0x4c + k * 4), K(0x4a9420)), K(0x4a9424));
}

/* the mech's stats for actor ac from player record p's parts (the head, chest, arms, legs and booster records, the
   pilot level, the special items' bonuses at +0x404 .., the weight against the limit and the overload r slowing the
   legs and booster) and the fixed values, +0 .. +0x94. check: armc_computeTotals' copy, which rounds two of them
   differently */
static void mech_stats(u8 *s, u8 *ac, u8 *p, int check)
{
	u8 *head = s + 0x13c9b30 + GAME_VAR(int, p + 0x30c) * 0xaa8, *chest = s + 0x13eb004 + GAME_VAR(int, p + 0x310) * 0xabc;
	u8 *arms = s + 0x140c8c0 + GAME_VAR(int, p + 0x314) * 0x1300, *legs = s + 0x1447ec4 + GAME_VAR(int, p + 0x318) * 0x13f4;
	u8 *boost = s + 0x1486470 + GAME_VAR(int, p + 0x31c) * 0x1820;
	for (int k = 0; k < 4; k++) {
		A(u32, 0x404 + k * 4) = 0x3f800000;
		A(int, 0x414 + k * 4) = 0;
	}
	A(int, 0x424) = 0;
	A(u32, 0x428) = A(u32, 0x42c) = 0x3f800000;
	A(int, 0x430) = 0;
	fill_dwords(ac + 0x434, 5, 0x3f800000);
	A(int, 0x448) = 0;
	for (int k = 0; k < 6; k++) {
		int it = GAME_VAR(int, p + 0x320 + k * 4);
		if (it < 0 || GAME_VAR(int, s + 0x14d1ab4 + it * 0x2e18 + 0x2dc0) >= 0)
			continue;
		switch (it) {
		case 0x1b:
			for (int i = 0; i < 4; i++)
				A(float, 0x404 + i * 4) = f32(fadd_m(fld_m((const float *)(ac + 0x404) + i), K(0x4a94fc)));
			break;
		case 0x1c: A(int, 0x41c) += 100; break;
		case 0x1d: A(int, 0x414) += 100; break;
		case 0x1e: A(int, 0x418) += 100; break;
		case 0x1f: A(int, 0x420) += 100; break;
		case 0x20:
			A(float, 0x424) = f32(fadd_m(fld_m((const float *)(ac + 0x424)), K(0x4a9708)));
			A(float, 0x428) = f32(fsub_m(fld_m((const float *)(ac + 0x428)), K(0x4a942c)));
			A(float, 0x42c) = f32(fadd_m(fld_m((const float *)(ac + 0x42c)), K(0x4a9424)));
			A(int, 0x430) += 3;
			break;
		case 0x21:
			A(float, 0x434) = f32(fadd_m(fld_m((const float *)(ac + 0x434)), K(0x4a942c)));
			A(float, 0x438) = f32(fsub_m(fld_m((const float *)(ac + 0x438)), K(0x4a942c)));
			A(float, 0x43c) = f32(fsub_m(fld_m((const float *)(ac + 0x43c)), K(0x4a942c)));
			break;
		case 0x22:
			A(float, 0x440) = f32(fadd_m(fld_m((const float *)(ac + 0x440)), K(0x4a94f8)));
			break;
		case 0x23:
			A(float, 0x444) = f32(fadd_m(fld_m((const float *)(ac + 0x444)), K(0x4a94fc)));
			A(int, 0x448) += 4;
			break;
		}
	}
	long double hp = fadd_m(fmul_m(level_factor(p, 3), (const float *)(head + 0xa94)), (const float *)(ac + 0x424));
	AC->radiusSq = f32(hp * hp);
	AC->heading = f32(fmul_m(level_factor(p, 3), (const float *)(head + 0xa98)));
	A(int, 8) = GAME_VAR(int, head + 0xa9c) + A(int, 0x430);
	A(float, 0xc) = f32(fmul_m(fld_m((const float *)(head + 0xaa0)), (const float *)(ac + 0x428)));
	A(float, 0x10) = f32(fmul_m(fld_m((const float *)(head + 0xaa4)), (const float *)(ac + 0x42c)));
	A(float, 0x14) = f32(fmul_m(fmul_m(level_factor(p, 4), (const float *)(chest + 0xab0)), (const float *)(ac + 0x440)));
	A(float, 0x18) = f32(fadd_m(fadd_m(fadd_m(fld_m((const float *)(boost + 0x17f8)), (const float *)(legs + 0x13d8)),
	                                   (const float *)(arms + 0x12e8)), (const float *)(head + 0xa90)));
	int type = GAME_VAR(int, s + 0x20f3ab8);
	if (type < 2 || type > 0xb)
		for (int k = 0; k < 6; k++) {
			int it = GAME_VAR(int, p + 0x320 + k * 4);
			if (it >= 0)
				A(float, 0x18) = f32(fadd_m(fld_m((const float *)(s + 0x14d1ab4 + it * 0x2e18 + 0x2db8)), (const float *)(ac + 0x18)));
		}
	long double over = A(float, 0x18) > A(float, 0x14)
		? fmul_m(fdiv_m(fsub_m(fld_m((const float *)(ac + 0x18)), (const float *)(ac + 0x14)), (const float *)(ac + 0x14)), K(0x4a947c))
		: fld_m(K(0x4a93e8));
	AC->armorMax = ftol(fadd_m(level_factor(p, 2) * (long double)GAME_VAR(int, chest + 0xab4), K(0x4a942c)));
	AC->shieldMax = ftol(fadd_m(fmul_m(level_factor(p, 2) * (long double)GAME_VAR(int, chest + 0xab8), (const float *)(ac + 0x444)), K(0x4a942c)));
	A(u32, 0x24) = GAME_VAR(u32, arms + 0x12ec);
	for (int k = 0; k < 4; k++)
		AC->ammoMax[k] = ftol(fadd_m(fmul_m((long double)GAME_VAR(int, arms + 0x12f0 + k * 4), (const float *)(ac + 0x404) + k), K(0x4a942c))) +
		                       A(int, 0x414 + k * 4);
	long double left = fld_m(K(0x4a9424)) - over;
	long double v = fmul_m(level_factor(p, 0), (const float *)(legs + 0x13dc)) * left;
	A(float, 0x38) = f32(v);
	if (!(v >= 0))
		A(int, 0x38) = 0;
	if (GAME_VAR(int, s + 0x20f3acc) == 1)
		A(float, 0x38) = f32(fmul_m(fld_m((const float *)(ac + 0x38)), K(0x4a9704)));
	A(u32, 0x40) = GAME_VAR(u32, boost + 0x1800);
	A(float, 0x44) = f32(fmul_m(fld_m((const float *)(boost + 0x1804)), (const float *)(ac + 0x434)));
	A(float, 0x48) = f32(fmul_m(fld_m((const float *)(boost + 0x1808)), (const float *)(ac + 0x438)));
	A(float, 0x4c) = f32(fmul_m(fld_m((const float *)(boost + 0x180c)), (const float *)(ac + 0x43c)));
	/* the legs' factors: the level's second value plus the legs' own, plus 1 */
#define LEG(o) fadd_m(fadd_m(fmul_m((long double)GAME_VAR(int, OBJ(g_profileRecords) + 0x3c + GAME_VAR(int, p + 0x44) * 0x4c), K(0x4a9420)), (const float *)(legs + (o))), K(0x4a9424))
	v = fmul_m(LEG(0x13e4), (const float *)(boost + 0x1810)) * left;
	A(float, 0x50) = f32(v);
	if (!(v >= *K(0x4a93f4)))
		A(u32, 0x50) = 0x42c80000;   /* 100 */
	v = fmul_m(fld_m((const float *)(legs + 0x13e0)), (const float *)(ac + 0x50));
	A(float, 0x3c) = f32(v);
	if (GAME_VAR(int, s + 0x20f3acc) == 1)   /* (the check scales the stored value) */
		A(float, 0x3c) = f32(fmul_m(check ? fld_m((const float *)(ac + 0x3c)) : v, K(0x4a9704)));
	v = fdiv_m(fmul_m(LEG(0x13e8), (const float *)(boost + 0x1814)), (const float *)(ac + 0x50)) * left;
	A(float, 0x54) = f32(v);
	if (!(v >= 0))
		A(int, 0x54) = 0;
	v = fmul_m(fdiv_m(fmul_m(LEG(0x13ec), (const float *)(boost + 0x1818)), (const float *)(ac + 0x50)) * left, K(0x4a9474));
	A(float, 0x58) = f32(v);
	if (v > 0)
		A(int, 0x58) = 0;
	v = fdiv_m(fmul_m(LEG(0x13f0), (const float *)(boost + 0x181c)), (const float *)(ac + 0x50)) * left;
	A(float, 0x5c) = f32(v);
	if (!((check ? fld_m((const float *)(ac + 0x5c)) : v) >= 0))   /* (the check tests the stored value) */
		A(int, 0x5c) = 0;
#undef LEG
	A(float, 0x60) = f32(-fld_m((const float *)(ac + 0x5c)));
	(*(int *)&AC->spawn64) = 100;
	A(u32, 0x68) = A(u32, 0x50);
	A(u32, 0x6c) = 0x44610000;   /* 900 */
	AC->spawn70 = 0x40400000;   /* 3 */
	AC->spawn74 = 10;
	(*(int *)&AC->spawn78) = 0;
	A(u32, 0x7c) = 0x447a0000;   /* 1000 */
	A(u32, 0x80) = 0x43fa0000;   /* 500 */
	AC->spawnTail[0] = 0x40000000;   /* 2 */
	AC->spawnTail[1] = 0x3f800000;
	AC->spawnTail[2] = 0x457a0000;   /* 4000 */
	AC->spawnTail[3] = 0x40a00000;   /* 5 */
	AC->spawnTail[4] = 0x3f800000;
}

/* 0x457330 (thiscall on the scene): actor a built from player *pp's mech (the player record 0x47fd2 bytes from
   +0x1561b68; its parts +0x30c head, chest, arms, legs, booster; pp: the player, a2, a3 copied, the position +8
   and the heading +0x14). The special items in its six slots (+0x320; kinds 0x1b .. 0x23 with a negative +0x2dc0)
   bend the defaults (+0x404 ..: armour, shields, power, cooling, mobility); then the stats: health and energy (the
   head with the level), the weight against the limit (any items' weight unless the game type is 2 .. 11) giving an
   overload r that slows the legs and booster (speed, turn, jump, gravity, fall), the arms' ammunition, and the
   fixed values; its id (a2, or the next serial +0x202e8d0), the player's details, the weapon slot (actor_setWeaponSlot),
   the starting values (actor_startingValues), the position history, timers and flags reset, its lists loaded and parts
   placed (actor_updateHead .. actor_updateBooster, actor_updatePart; viewed by another than itself +0x49c), and the scene told
   an actor joined (+0x202e8ec). Its caller ignores the eax it leaves */
void THISCALL (actor_setupFromParts)(u8 *s, int a, int id, u32 a3, const u32 *pp)
{
	u8 *ac = s + 0x1cd93a8 + a * 0x8888;
	u8 *p = s + 0x1561b68 + pp[0] * 0x47fd2;
	mech_stats(s, ac, p, 0);
	AC->statD8 = 1;
	strcpy((char *)ac + 0x98, (const char *)RELOC(p) + 4);
	A(int, 0x104) = id >= 0 ? id : GAME_VAR(int, s + 0x202e8d0)++;
	AC->active = 1;
	(*(u32 *)&AC->player) = pp[0];
	(*(u32 *)&AC->pilot) = a3;
	int level = GAME_VAR(int, p + 0x44);
	A(int, 0x114) = level >= 0 && level < 9 ? level : 0;
	(*(u32 *)&AC->team) = GAME_VAR(u32, p + 0x48);
	(*(u32 *)&AC->bot) = pp[1];
	A(int, 0x120) = 0;
	A(u32, 0x124) = 0x3f800000;
	(*(u32 *)&AC->armor) = ((u32)AC->armorMax);
	(*(u32 *)&AC->shield) = ((u32)AC->shieldMax);
	fill_dwords(ac + 0x130, 4, 0);
	AC->gaugeIcon = -1;
	A(int, 0x144) = 0;
	actor_setWeaponSlot((Stage *)s, a, 0);
	actor_startingValues(s, a);   /* actor_startingValues */
	AC->state = 1;
	A(int, 0x150) = 0;
	memcpy(ac + 0x154, pp + 2, 12);
	A(u32, 0x160) = pp[5];
	A(u32, 0x164) = pp[6];
	fill_dwords(ac + 0x168, 6, 0);
	static const u16 past[3] = { 0x180, 0x1ac, 0x1d4 };   /* three past positions: the place and the heading */
	for (int k = 0; k < 3; k++) {
		u8 *h = ac + past[k];
		memcpy(h, ac + 0x154, 12);
		GAME_VAR(u32, h + 0xc) = A(u32, 0x160);
		GAME_VAR(u32, h + 0x10) = A(u32, 0x164);
	}
	fill_dwords(ac + 0x194, 6, 0);
	fill_dwords(ac + 0x1c0, 5, 0);
	fill_dwords(ac + 0x1e8, 3, 0);
	A(int, 0x1f4) = 0;
	for (int k = 0; k < 5; k++) {
		A(int, 0x1f8 + k * 0x20) = 0;
		A(int, 0x1fc + k * 0x20) = 0;
		A(int, 0x360 + k * 4) = -1;
	}
	A(int, 0x374) = 0;
	memcpy(ac + 0x378, (const void *)ADDR(g_vecZero), 12);
	memcpy(ac + 0x384, (const void *)ADDR(g_vecZero), 12);
	A(u32, 0x3e8) = 0x43fa0000;   /* 500 */
	AC->statusIcon = 0;
	AC->timerFlags = A(int, 0x104) % 2 == 1 ? 0x4000 : 0;
	fill_dwords(ac + 0x3f4, 4, 0);
	fill_dwords(ac + 0x44c, 11, 0);
	AC->inView = -1;
	fill_dwords(ac + 0x47c, 5, 0);
	A(u32, 0x490) = 0x3f800000;
	A(int, 0x494) = A(int, 0x498) = 0;
	A(int, 0x49c) = a == GAME_VAR(int, s + 0x202e8d8) ? 0 : 1;
	fill_dwords(ac + 0x4a0, 3, 0);
	A(u32, 0x4ac) = A(u32, 0x4b0) = 0x3f800000;
	AC->overheat = AC->warned = 0;
	fill_dwords(ac + 0x4bc, 3, (u32)-1);
	A(int, 0x4d0) = -1;
	memcpy(ac + 0x4e0, ac + 0x154, 12);
	A(int, 0x4ec) = 0;
	A(u8, 0x4f4) = 0;
	A(u32, 0x534) = 0xc61c4000;   /* -10000 */
	A(int, 0x538) = -1;
	fill_dwords(ac + 0x53c, 3, 0);
	A(u32, 0x548) = 0x3f800000;
	A(int, 0x54c) = 0;
	actor_updateHead(s, a);
	actor_updateBody(s, a);
	actor_updateArms(s, a);
	actor_updateLegs(s, a);
	actor_updateBooster(s, a);
	for (int k = 5; k >= 0; k--)
		actor_updatePart(s, a, k, A(u32, 0x49c));
	fill_dwords(ac + 0x87bc, 10, 0);
	fill_dwords(ac + 0x87e8, 4, 0);
	AC->target1 = AC->target2 = -1;
	A(int, 0x8800) = A(int, 0x8804) = 0;
	A(int, 0x8808) = -1;
	A(int, 0x880c) = 0;
	fill_dwords(ac + 0x8810, 5, (u32)-1);
	fill_dwords(ac + 0x8824, 5, 0);
	memcpy(ac + 0x8838, (const void *)ADDR(g_vecZero), 12);
	A(int, 0x8844) = 0;
	A(u32, 0x8848) = 0x44bb8000;   /* 1500 */
	fill_dwords(ac + 0x884c, 3, 0);
	memcpy(ac + 0x885c, (const void *)ADDR(g_vecZero), 12);
	A(int, 0x8858) = 0;
	A(int, 0x8868) = 0;
	A(u32, 0x886c) = 0x3f800000;
	A(int, 0x8870) = -1;
	memcpy(ac + 0x8874, (const void *)ADDR(g_vecZero), 12);
	AC->alert = A(int, 0x8884) = 0;
	GAME_VAR(int, s + 0x202ea80 + a * 4) = 0;
	GAME_VAR(int, s + 0x202e8ec) = 1;
}
#undef A
#undef AC
#undef K

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */
#define K(address) ((const float *)RELOC(address))

/* the actor's eight part lists (constructed on the stack copy as the original does) */
static const u16 k_listAt[8] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };

/* |a - b| (an x87 abs: a NaN stays) within 0.1 */
static int close_enough(const float *a, const float *b)
{
	long double d = fsub_m(fld_m(a), b);
	if (!(d >= 0))
		d = -d;
	return !(d > *K(0x4a93ec));
}

/* whether actor ac's stats agree with mine, worked out again from its player's record (mech_stats in check mode,
   then the game type's fixed energy and weapons), and its limits hold */
static int totals_agree(u8 *s, u8 *ac, u8 *me)
{
	u8 *p = s + 0x1561b68 + AC->player * 0x47fd2;
	mech_stats(s, me, p, 1);
	unsigned mode = GAME_VAR(int, s + 0x20f3ab8) - 2;
	if (mode <= 9) {
		int pair = mode / 2;
		GAME_VAR(int, me + 0x1c) = GAME_VAR(int, me + 0x20) = pair == 0 ? 10 : 150;
		if (pair < 4)
			GAME_VAR(int, me + 0x28 + pair * 4) = 100;
	}
	static const u8 floats1[] = { 0, 4 }, ints[] = { 0x1c, 0x20, 0x24, 0x28, 0x2c, 0x30, 0x34 };
	static const u8 floats2[] = { 0xc, 0x10, 0x14, 0x18 }, floats3[] = { 0x38, 0x44, 0x48, 0x4c, 0x50, 0x3c, 0x54, 0x58, 0x5c, 0x60 };
	for (int k = 0; k < 2; k++)
		if (!close_enough((const float *)(ac + floats1[k]), (const float *)(me + floats1[k])))
			return 0;
	if (A(int, 8) != GAME_VAR(int, me + 8))
		return 0;
	for (int k = 0; k < 4; k++)
		if (!close_enough((const float *)(ac + floats2[k]), (const float *)(me + floats2[k])))
			return 0;
	for (int k = 0; k < 7; k++)
		if (A(int, ints[k]) != GAME_VAR(int, me + ints[k]))
			return 0;
	for (int k = 0; k < 10; k++)
		if (!close_enough((const float *)(ac + floats3[k]), (const float *)(me + floats3[k])))
			return 0;
	if (!close_enough((const float *)(ac + 0x68), (const float *)(me + 0x50)))
		return 0;
	int d = A(int, 0x448) - GAME_VAR(int, me + 0x448);
	if ((long double)(d < 0 ? -d : d) > *K(0x4a93ec))
		return 0;
	if (AC->armor > AC->armorMax + 100 || AC->shield > AC->shieldMax + 100 || AC->ammo[0] > AC->ammoMax[0] ||
	    AC->ammo[1] > AC->ammoMax[1] || AC->ammo[2] > AC->ammoMax[2] || AC->ammo[3] > AC->ammoMax[3] || A(int, 0x448) > 8)
		return 0;
	const float *heat = K(0x4a940c);
	if ((AC->markSolo == 0 && AC->timers[0] > *heat) || AC->timers[1] > *heat || (AC->markSolo == 0 && AC->timers[2] > *heat) ||
	    AC->timers[3] > *heat)
		return 0;
	return 1;
}

/* 0x45ee40 (thiscall on the scene): the "data loss" check game_processGameMode runs every 20 s on the local
   player's actor a: one not in play (+0x14c) passes; else totals_agree. The original's stack actor (its five
   resource sets and eight part lists constructed and destroyed again) is kept; its SEH frame is not reproduced.
   Returns 1 if all agree, else 0 */
u32 THISCALL (armc_computeTotals)(u8 *s, int a)
{
	u8 me[0x8888];   /* the stack actor (only the fields it computes are read) */
	for (int k = 0; k < 5; k++)
		ResourceSet_trivialCtor(me + 0x298 + k * 0x28);   /* ResourceSet_trivialCtor: a resource set */
	for (int k = 0; k < 8; k++) {
		GAME_VAR(u32, me + k_listAt[k]) = VT(UnitPoseInfo, 0x4a9754);
		partList_clear(me + k_listAt[k]);
	}
	u8 *ac = s + 0x1cd93a8 + a * 0x8888;
	int ok = AC->state != 1 || totals_agree(s, ac, me);
	for (int k = 7; k >= 0; k--)
		GAME_THISFN(UnitPoseInfo_dtor, 0x46f470, void, void *)(me + k_listAt[k]);   /* UnitPoseInfo_dtor: a part list released */
	return ok;
}
#undef A
#undef AC
#undef K
