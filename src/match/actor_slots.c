/* actor_slots.c: the stage's actor slots: selecting one, the camera's target, an actor's input record, and the
   stage's pools of map objects, particles and bullets emptied. */
#include "../game.h"
#include <string.h>
#define STS ((Stage *)scene)   /* the stage (named scene in these functions) by its fields */

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* an actor's input record: twelve ints (the moves and buttons the actor acts on this frame); the ninth is the
   one cleared to -1 */
static const int input_fields[12] = { offsetof(Player, inForward), offsetof(Player, inBackward), offsetof(Player, inStepLeft), offsetof(Player, inStepRight), offsetof(Player, inPitch), offsetof(Player, inYaw), offsetof(Player, inFire), offsetof(Player, inAltitude), offsetof(Player, inBooster), offsetof(Player, inWeaponSlot), offsetof(Player, inPrevWeapon), offsetof(Player, inNextWeapon) };

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

/* 0x45dff0: the camera follows actor i in mode with value (kept in the actor, cameraValue); the actor followed before
   loses its value. A negative i follows none; an actor not in use is not followed */
void THISCALL (camera_setTarget)(Stage *stage, int i, int mode, int value)
{
	int *target = &stage->cameraTarget;
	if (*target > -1)
		stage->actors[*target].cameraValue = 0;
	if (i < 0 || stage->actors[i].state == 1) {
		*target = i;
		stage->cameraTargetMode = mode;
		stage->actors[i].cameraValue = value;
	}
}

/* ---- the pools emptied (each slot's "in use" cleared, the counters zeroed) ---- */
/* 0x490d10: the 1000 map objects */
void THISCALL (stage_clearMapObjects)(Stage *stage)
{
	stage->objectColourCount = 0;
	stage->objectCount = 0;
	stage->objectFreeHint = 0;
	stage->objectSerial = 0;
	for (int i = 0; i < 1000; i++)
		stage->objects[i].active = 0;
}

/* 0x479a60: the 1000 particles */
void THISCALL (stage_clearParticles)(Stage *stage)
{
	stage->particleCount = 0;
	stage->particleFreeHint = 0;
	stage->particleSerial = 0;
	for (int i = 0; i < 1000; i++)
		stage->particles[i].active = 0;
}

/* 0x4799f0: particle slot i freed: the first-free hint (particleFreeHint) moved down to it, and when it was the last
   in use the used range (particleCount) shrinks past every free slot at its end */
void THISCALL (stage_freeParticle)(Stage *stage, int i)
{
	if (!stage->particles[i].active)
		return;
	stage->particles[i].active = 0;
	if (i < stage->particleFreeHint)
		stage->particleFreeHint = i;
	if (i != stage->particleCount - 1 || stage->particleCount <= 0)
		return;
	do {
		if (stage->particles[stage->particleCount - 1].active)
			return;
	} while (--stage->particleCount > 0);
}

/* 0x47cfd0: the 400 bullets (0x4e8-byte records from 0x202ef34) */
void THISCALL (stage_clearBullets)(Stage *stage)
{
	stage->bulletSlotsUsed = 0;
	stage->bulletFreeHint = 0;
	stage->bulletSerial = 0;
	for (int i = 0; i < 400; i++)
		stage->bullets[i].active = 0;
}

/* 0x4743e0: actor slot i emptied: no name, no player (-1), no team (-1), its counters and marks cleared */
void THISCALL (actor_resetSlot)(Stage *stage, int i)
{
	Player *a = &stage->actors[i];
	a->name[0] = '\0';
	a->player = -1;
	a->character = 0;
	a->team = -1;
	for (int k = 0; k < 11; k++)
		FIELD(int, a, offsetof(Player, inPlay) + k * 4) = 0;   /* inPlay .. (11 words) */
	a->state = 0;
	a->bigHead = 0;
	a->viewMarked = 0;
	a->isKing = 0;
	a->isCommander = 0;
}

/* 0x47d060: every bullet in use drawn (its trail, bullet_drawTrail) */
void THISCALL (stage_drawBullets)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->bulletSlotsUsed; i++)
		if (stage->bullets[i].active == 1)
			bullet_drawTrail(stage, i, view);
}

/* 0x48fde0: while the script runs (scriptMode), its object (scenePath) told (recorder_noteStub); returns b */
int THISCALL (script_notifyObject)(Stage *stage, int a, int b, int c, int d)
{
	if (!stage->scriptMode)
		return 0;
	recorder_noteStub((u8 *)&stage->scenePath, a, b, c, d);
	return b;
}

/* 0x470a70: every actor slot emptied: the six slot numbers from playerActor on (-1), teamsChanged 1, the scores, the
   16 player records and the stage's own reset, then the 100 slots */
void THISCALL (scene_resetActors)(Stage *stage)
{
	for (int k = 0; k < 6; k++)
		FIELD(int, stage, offsetof(Stage, playerActor) + k * 4) = -1;   /* playerActor .. cameraTargetMode */
	stage->teamsChanged = 1;
	stage_clearFrags(stage);
	stage_resetPlayerRecords(stage);
	stage_clearActorSlots(stage);
	for (int i = 0; i < 100; i++)
		actor_resetSlot(stage, i);
}

/* 0x45e070: the 100 actor slots emptied (none in use, each free with no player), with the counts */
void THISCALL (stage_clearActorSlots)(Stage *stage)
{
	stage->actorCount = 0;
	stage->actorFreeHint = 0;
	stage->actorSerial = 0;
	for (int i = 0; i < 100; i++) {
		Player *ac = &stage->actors[i];
		ac->active = 0;
		ac->player = -1;
		ac->state = 0;
		(*(int *)&stage->lockHeld[i]) = 0;
	}
}

/* 0x47cf10: bullet b is gone: its shooter's five target references to it dropped, its slot freed (the lowest free
   slot and the used count kept up to date) */
void THISCALL (bullet_free)(Stage *stage, int b)
{
	Bullet *bu = &stage->bullets[b];
	for (int k = 0; k < 5; k++) {
		int *ref = &stage->actors[bu->owner].shotBullets[k];
		if (*ref == b)
			*ref = -1;
	}
	if (!bu->active)
		return;
	bu->active = 0;
	if (b < stage->bulletFreeHint)
		stage->bulletFreeHint = b;
	int n = stage->bulletSlotsUsed;
	if (b != n - 1 || n <= 0)
		return;
	do {
		n = stage->bulletSlotsUsed;
		if (stage->bullets[n - 1].active)
			return;
		stage->bulletSlotsUsed = --n;
	} while (n > 0);
}

/* a player record's per-match state cleared (e = the record + 0x44, its character): its name kept or not by the caller;
   the five part names and parts, the six item names and items, the 5 x 2 colour grid's three layers */
static void player_clear(u8 *e)
{
	PlayerRecord *pr = (PlayerRecord *)(e - 0x44);
	for (int k = 0; k < 5; k++)
		pr->partNames[k][0] = 0;
	for (int k = 0; k < 5; k++)
		pr->parts[k] = -1;
	for (int k = 0; k < 6; k++) {
		pr->itemNames[k][0] = 0;
		pr->items[k] = -1;
	}
	for (int r = 0; r < 5; r++)
		for (int c = 0; c < 2; c++) {
			pr->partHue[r][c] = 0;
			pr->partSaturation[r][c] = 0;
			pr->partValue[r][c] = 0;
		}
}

/* 0x474480: the 16 player records reset (unused, no name, no actor) with their colour grids; none seen */
void THISCALL (stage_resetPlayerRecords)(Stage *stage)
{
	for (int p = 0; p < 16; p++) {
		PlayerRecord *pr = &stage->playerRecords[p];
		u8 *e = (u8 *)&pr->character;
		pr->used = 0;
		pr->name[0] = 0;
		pr->character = 0;
		pr->team = -1;
		player_clear(e);
		playerRecord_resetColourGrid(stage, p);
	}
	stage->playerRecordCount = 0;
}

/* 0x470cb0: a new round: the actor slot numbers (-1), the scores, the 16 player records (their names kept), the
   actor slots, then each actor's round state */
void THISCALL (stage_newRound)(Stage *stage)
{
	for (int k = 0; k < 6; k++)
		FIELD(int, stage, offsetof(Stage, playerActor) + k * 4) = -1;   /* playerActor .. cameraTargetMode */
	stage->teamsChanged = 1;
	stage_clearFrags(stage);
	for (int p = 0; p < 16; p++) {
		PlayerRecord *pr = &stage->playerRecords[p];
		u8 *e = (u8 *)&pr->character;
		pr->used = 0;
		pr->team = -1;
		player_clear(e);
	}
	stage->playerRecordCount = 0;
	stage_clearActorSlots(stage);
	static const short cleared[] = { offsetof(Player, inPlay), offsetof(Player, kills), offsetof(Player, deaths), offsetof(Player, killsCounted),
	                                 offsetof(Player, deathsCounted), offsetof(Player, timePlayed), offsetof(Player, timeExtra), offsetof(Player, state),
	                                 offsetof(Player, bigHead), offsetof(Player, isKing), offsetof(Player, isCommander) };
	for (int i = 0; i < 100; i++) {
		Player *ac = &stage->actors[i];
		ac->team = -1;
		for (unsigned k = 0; k < sizeof cleared / sizeof cleared[0]; k++)
			FIELD(int, ac, cleared[k]) = 0;
	}
}

/* 0x45dca0: actor i taken out (if active): its state, the leader marks pointing at it, its slot freed (the lowest
   free slot and the used count kept up to date); the teams changed */
void THISCALL (actor_deactivate)(Stage *stage, int i)
{
	Player *ac = &stage->actors[i];
	if (!ac->active)
		return;
	ac->active = 0;
	ac->state = 0;
	ac->onScreen = 0;
	(*(int *)&ac->aimTime) = 0;
	(*(int *)&ac->labelFade) = 0;
	if (stage->kingActor == i)
		stage->kingActor = -1;
	int team = ac->team;
	if (team > -1 && stage->teamCommanders[team] == i)
		stage->teamCommanders[team] = -1;
	(*(int *)&stage->lockHeld[i]) = 0;
	if (i < stage->actorFreeHint)
		stage->actorFreeHint = i;
	int n = stage->actorCount;
	if (i == n - 1)
		while (n > 0 && stage->actors[stage->actorCount - 1].active == 0) {
			n = stage->actorCount - 1;
			stage->actorCount = n;
		}
	stage->teamsChanged = 1;
}

/* 0x45dc00 (thiscall on the scene): actor slot i (at most 99) set up from its parts (actor_setupFromParts): the
   slots up to it are added first (each new one marked free, active), and the first free slot (searched up to and
   including the count, as the original does) kept as the next free (actorFreeHint). Returns i, or -1 */
int THISCALL (stage_setupActorSlot)(Stage *scene, int i, u32 id, u32 controlledBy, u32 parts)
{
#define COUNT STS->actorCount
#define USED(k) STS->actors[k].active
	if (i >= 100)
		return -1;
	if (COUNT <= i) {
		for (int k = COUNT; k <= i; k++)
			USED(k) = 0;
		COUNT = i + 1;
	}
	for (int k = 0; k <= COUNT; k++)
		if (USED(k) == 0) {
			scene->actorFreeHint = k;
			break;
		}
	actor_setupFromParts((u8 *)scene, i, id, controlledBy, parts);
	return i;
#undef COUNT
#undef USED
}

/* 0x474fd0: a player's part coloured from the network: six signed bytes, scaled (the first and fourth by k_1_40625f,
   the others by k_0_0078125f), given to actor_setPartColor. Its caller ignores the eax it leaves */
void THISCALL (actor_applyRemoteColours)(void *scene, int p, int part, int h1, int s1, int v1, int h2, int s2, int v2)
{
	long double k1 = k_1_40625f, k2 = k_0_0078125f;
	actor_setPartColor(scene, p, part, (float)((signed char)h1 * k1), (float)((signed char)s1 * k2), (float)((signed char)v1 * k2),
	                   (float)((signed char)h2 * k1), (float)((signed char)s2 * k2), (float)((signed char)v2 * k2));
}

/* The five parts' models loaded (0x45e1f0 .. 0x45e530): where each part's model and its own fields are. An actor's part
   type (its type record at playerRecords, 0x47fd2 bytes each, by the actor's player) names the part's model (by +model_at
   in that record); the actor's detail level (lowDetail) picks the model's set of shapes */
typedef struct {
	int model_at;      /* the part's type in the player record (parts[k]) */
	u32 models;        /* the types' table in the stage, */
	int model_size;    /* and each one's size */
	int shapes_n, names, name_size, skels_n, knames;   /* in the type: per pose (shapeCount, shapeNames, skelCount, skelNames) */
	int data, skels;   /* the player record's shape and skeleton caches handed over */
	int self;          /* the actor's ObjectList for this part (its memory right after it) */
	u32 limit;
} PartModel;

static void part_load(u8 *scene, int a, const PartModel *m)
{
	u8 *actor = (u8 *)&STS->actors[a];
	Player *act = (Player *)actor;
	if (!act->active)
		return;
	u8 *type = (u8 *)&STS->playerRecords[act->player];
	u8 *model = scene + m->models + GAME_VAR(int, type + m->model_at) * m->model_size;
	int pose = act->lowDetail;
	ObjectList_load(actor + m->self, type + m->data, type + m->skels, GAME_VAR(u32, model + m->shapes_n + pose * 4),
	                     model + m->names + pose * m->name_size, GAME_VAR(u32, model + m->skels_n + pose * 4),
	                     model + m->knames + pose * 0x80, 0, 0, 0, actor + m->self + sizeof(ObjectList), m->limit);
}

static const PartModel g_parts[5] = {
#define PART(k, T, part, model) { offsetof(PlayerRecord, parts[k]), offsetof(Stage, part##Types), sizeof(T), offsetof(T, shapeCount), offsetof(T, shapeNames), \
	sizeof ((T *)0)->shapeNames[0], offsetof(T, skelCount), offsetof(T, skelNames), offsetof(PlayerRecord, part##Shapes), offsetof(PlayerRecord, part##Skels), \
	offsetof(Player, model), sizeof ((Player *)0)->model##Mem }
	PART(0, HeadType, head, headModel), PART(1, ChestType, chest, chestModel), PART(2, ArmType, arm, armsModel),
	PART(3, LegType, leg, legsModel), PART(4, BoosterType, booster, boosterModel),
#undef PART
};

/* (thiscall on the scene; their callers ignore the eax they leave) */
void THISCALL (actor_loadHead)(u8 *scene, int a) { part_load(scene, a, &g_parts[0]); }
void THISCALL (actor_loadBody)(u8 *scene, int a) { part_load(scene, a, &g_parts[1]); }
void THISCALL (actor_loadArms)(u8 *scene, int a) { part_load(scene, a, &g_parts[2]); }
void THISCALL (actor_loadLegs)(u8 *scene, int a) { part_load(scene, a, &g_parts[3]); }
void THISCALL (actor_loadBooster)(u8 *scene, int a) { part_load(scene, a, &g_parts[4]); }

/* 0x45de20 (thiscall on the scene): actor a spawned from a map record for the player (playerActor; none: a fatal
   message): set up from its parts (stage_setupActorSlot, with the record's position, angle and parts picked out), then given
   the record's settings: team and two values (kept twice), ranges and speeds scaled, its radius squared (scaled), a
   count from a scaled value, and the rest copied; no targets (target1, target2 -1). Its callers ignore the eax it
   leaves */
void THISCALL (actor_applySpawnRecord)(u8 *scene, int a, const u8 *rec)
{
#define SR ((SpawnRecord *)rec)   /* the same by its fields (src/scene.fields) */
	int player = STS->playerActor;
	if (player < 0)
		sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4b4538, "invalid player actor slot(%d) - spawn..."), player);
	u32 spawn[7] = { SR->player, SR->bot, BITS(SR->pos[0]), BITS(SR->pos[1]), BITS(SR->pos[2]) };
	((float *)RELOC(spawn))[5] = f32(fld_m(&SR->pitch));
	((float *)RELOC(spawn))[6] = f32(fld_m(&SR->yaw));
	stage_setupActorSlot((Stage *)scene, a, -1, STS->playerActor, spawn);
	if (a < 0)
		return;
	u8 *actor = (u8 *)&STS->actors[a];
	Player *act = (Player *)actor;
#define AC act   /* the same by its fields (src/scene.fields) */
	AC->unused1c = SR->unused1c;
	AC->armorMax = SR->armor;
	AC->shieldMax = SR->shield;
	AC->armor = SR->armor;
	AC->shield = SR->shield;
	AC->topSpeed = AC->speed = (float)(SR->speed * (long double)k_27_7778f);
	AC->turnRate = (float)(SR->turnRate * (long double)k_10f);
	long double radius = SR->range;
	AC->radiusSq = (float)(radius * radius * k_10000f);
	AC->unused34 = SR->unused34;
	AC->aimError = ftol(SR->aimError * (long double)k_10f);
	AC->scriptFlag = SR->scriptFlag;
	AC->dodgeSpread = (float)(SR->dodgeSpread * (long double)k_100f);
	AC->climbSpread = (float)(SR->climbSpread * (long double)k_100f);
	for (int k = 0; k < 5; k++)
		BITS(AC->botTimes[k]) = BITS(SR->botTimes[k]);
	AC->target1 = -1;
	AC->target2 = -1;
#undef SR
#undef AC
}

/* 0x45ebc0 (thiscall on the scene): player p's starting values when the slot is in use (active 1). Game types 2 ..
   11 (gameType) by pairs: the energy (armorMax, shieldMax, armor) 10 then 150, shield 0, the four weapon slots
   (ammo ..) empty but one (the pair's: 10 the first, else 50, its ammoMax .. 100; the last pair none). Otherwise
   armor / shield from armorMax / shieldMax and each slot half its ammoMax ... Its caller ignores the eax it leaves */
void THISCALL (actor_startingValues)(u8 *scene, int p)
{
	Player *a = &STS->actors[p];
	if (a->active != 1)
		return;
	unsigned mode = STS->gameType - 2;
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

/* 0x45e600 (thiscall on the scene): actor a's weapon model: its item in slot (its player type record's items + slot x 4; negative:
   none) loaded, in the given variant, into the slot's loader: slots 4 and 5 their own (weaponModel4; weaponModel5, from the
   item's second set of tables), any other only when it is the selected one (slot: weaponModel, and weapon the item's
   ammoSlot, -1 without). Without an item the loader is emptied (partList_release). Its callers ignore the eax it leaves */
void THISCALL (actor_loadWeapon)(u8 *scene, int a, int slot, int variant)
{
	u8 *actor = (u8 *)&STS->actors[a];
	Player *pl = (Player *)actor;
	if (!pl->active)
		return;
	PlayerRecord *type = (PlayerRecord *)((u8 *)&STS->playerRecords[pl->player]);
	int item = type->items[slot];
	u8 *it = item >= 0 ? (u8 *)&STS->actorInfo[item] : NULL;
	ActorInfo *info = (ActorInfo *)it;
	int self, set = 0;
	if (slot == 4)
		self = offsetof(Player, weaponModel4);
	else if (slot == 5) {
		self = offsetof(Player, weaponModel5);
		set = 1;
	} else if (slot == pl->slot)
		self = offsetof(Player, weaponModel);
	else
		return;
	if (it)
		ObjectList_load(actor + self, (u8 *)&STS->partShapes, (u8 *)&STS->partSkeletons, info->sets[set].models[variant],
		                     info->sets[set].bones[variant], info->sets[set].counts[variant], info->sets[set].frames[variant],
		                     0, 0, 0, actor + self + sizeof(ObjectList), 0x1770);   /* (its memory right after it) */
	else
		partList_release(actor + self);
	if (self == offsetof(Player, weaponModel))
		pl->weapon = it ? info->ammoSlot : -1;
}


/* a hue as the colour code keeps it: wrapped (angle_wrap of it x k_10f, then x k_tenthsToDegrees), brought down by
   k_360f when over k_180f (*h updated); its byte ((h - k_m180f) x k_0_7083333f - k_128f) */
static u8 hue_byte(float *h)
{
	long double v = fmul_m(angle_wrap(f32(fmul_m(fld_m(h), &k_10f))), &k_tenthsToDegrees);
	*h = f32(v);
	if (v > *&k_180f)
		*h = f32(fsub_m(fld_m(h), &k_360f));
	return (u8)ftol(fsub_m(fmul_m(fsub_m(fld_m(h), &k_m180f), &k_0_7083333f), &k_128f));
}

/* a saturation or value kept to -1 .. 0.999 (a NaN -1; *v updated); its byte (v x k_128f) */
static u8 level_byte(float *v)
{
	if (!(*v >= *&k_m1f))
		*(u32 *)RELOC(v) = 0xbf800000;   /* -1.0 */
	else if (!(*v < *&k_1f))
		*(u32 *)RELOC(v) = 0x3f7fbe77;   /* 0.999 */
	return (u8)ftol(fmul_m(fld_m(v), &k_128f));
}

/* 0x474b50 (thiscall on the scene): player p's part (0 .. 4) coloured: two hue / saturation / value sets kept as
   bytes in the part type record's colour table (partHue + part x 2: hue, partSaturation saturation, partValue value; the second
   set one byte on), then the part's shape cache (headShapes ..) given textures from the player's
   directory (by 0x4c77f8) tinted with them (shape_setTextureDir). Its callers ignore the eax it leaves */
void THISCALL (actor_setPartColor)(Stage *scene, int p, int part, float h1, float s1, float v1, float h2, float s2, float v2)
{
	static const u32 shapes[5] = { offsetof(PlayerRecord, headShapes), offsetof(PlayerRecord, chestShapes), offsetof(PlayerRecord, armShapes), offsetof(PlayerRecord, legShapes), offsetof(PlayerRecord, boosterShapes) };
	PlayerRecord *pr = &scene->playerRecords[p];
	pr->partHue[part][0] = hue_byte(&h1);
	pr->partSaturation[part][0] = level_byte(&s1);
	pr->partValue[part][0] = level_byte(&v1);
	pr->partHue[part][1] = hue_byte(&h2);
	pr->partSaturation[part][1] = level_byte(&s2);
	pr->partValue[part][1] = level_byte(&v2);
	char dir[0x100];
	sprintf(dir, (const char *)STR(0x4c77f8, "_T%d"), p);
	if ((unsigned)part <= 4)
		shape_setTextureDir((u8 *)pr + shapes[part], dir, 2, *(u32 *)&h1, *(u32 *)&s1, *(u32 *)&v1,
		                    *(u32 *)&h2, *(u32 *)&s2, *(u32 *)&v2);
}

#define K(address) ((const float *)RELOC(address))
#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */

/* the actor's eight object lists (the body, the parts, the weapons) */
static const u32 k_partLists[8] = { offsetof(Player, headModel), offsetof(Player, chestModel), offsetof(Player, armsModel), offsetof(Player, legsModel),
                                     offsetof(Player, boosterModel), offsetof(Player, weaponModel4), offsetof(Player, weaponModel5), offsetof(Player, weaponModel) };

/* the overlay texture the actor's flags ask for (Stage.itemTextures; 0x100: the damage map, 0x800: the shield, else the
   booster) */
static u32 flag_texture(u8 *s, u32 f)
{
	return ((Stage *)s)->itemTextures[f & 0x100 ? 0 : f & 0x800 ? 2 : 1];
}

/* the list of the weapon in hand (slot: 4, 5, else the last) */
static u8 *weapon_list(u8 *ac)
{
	return ac + (AC->slot == 4 ? 0x587c : AC->slot == 5 ? 0x701c : 0x40dc);
}

/* 0x45d3e0 (thiscall on the scene): actor a drawn into the view volume vv when in play and within the view range
   (cullMargin plus its radius radius) of the camera (cameraPos..) on every axis. Its tint (tint): a cloaked actor
   (flag 0x200) at the local player's rank or above white and faint (0x40 to itself, 0x10 to others); else for its
   first 3 s (spawnAge) a white flash fading in then out, or a shot's flash (glow, white) and a hit's (hitFlash, red-orange); a
   faint tint lights it with lightMatrix. The viewing actor (selectedActor), when draw is set, shows only the weapon in
   hand; others, when draw is not 1, all their lists up to the count breakUp (the fifth unless viewMarked; flags 0xd00 skip
   them without flares 0x83a9c8 or when too small on screen; faint ones only with flares); flags 0x100 / 0xc00 add a
   lit pass. A list that would not draw has them all reloaded (actor_loadHead / actor_loadBody / actor_loadArms /
   actor_loadLegs / actor_loadBooster / actor_loadWeapon). Its caller ignores the eax it leaves */
void THISCALL (actor_drawIntoView)(u8 *s, int a, void *vv, int draw)
{
	Stage *st = (Stage *)s;
	u8 *ac = (u8 *)&st->actors[a];
	if (AC->state != 1 || AC->cameraValue == 1)
		return;
	float r = f32(FADD(st->cullMargin, AC->radius));
	const float *cam = (const float *)st->cameraPos, *at = AC->pos;
	for (int k = 0; k < 3; k++)
		if (FSUB(cam[k], r) > at[k])
			return;
	for (int k = 0; k < 3; k++)
		if (!(FADD(r, cam[k]) >= at[k]))
			return;
	u8 *tint = AC->tint;
	int local = st->playerActor;
	if ((((u32)AC->timerFlags) & 0x200) && AC->hackingLevel >= st->actors[local].hackingLevel) {
		tint[0] = tint[1] = tint[2] = 0xff;
		tint[3] = a == local ? 0x40 : 0x10;
	} else if (!(AC->spawnAge > *&k_3f)) {
		if (!(AC->spawnAge >= *k_1_5f))
			tint[0] = tint[1] = tint[2] = tint[3] = (u8)ftol(FMUL(AC->spawnAge, k_170f));
		else {
			tint[0] = tint[1] = tint[2] = (u8)(0xff - ftol(fmul_m(fsub_m(fld_m(&AC->spawnAge), k_1_5f), &k_170f)));
			tint[3] = 0xff;
		}
	} else if (AC->glow > 0 || AC->hitFlash > 0) {
		int c[3] = { 0, 0, 0 };
		if (AC->glow > 0)
			c[0] = c[1] = c[2] = ftol(fmul_m(fld_m(&AC->glow), k_255f));
		if (AC->hitFlash > 0) {
			int red = ftol(fmul_m(fld_m(&AC->hitFlash), k_255f));
			c[0] += red;
			c[1] += red / 2;
			c[2] += red / 2;
		}
		for (int k = 0; k < 3; k++)
			tint[k] = (u8)(c[k] > 0xff ? 0xff : c[k]);
		tint[3] = 0xff;
	} else
		tint = NULL;
	u32 light = tint && tint[3] <= 0x10 ? (u32)st->lightMatrix : 0;
	u8 *lights = (u8 *)&st->actorLights;
	int ok = 1;
	u32 f;
	if (a == st->selectedActor) {
		if (draw) {
			ok = partList_queue(weapon_list(ac), vv, lights, tint, 1, (u32)-1, light) & 1;
			f = ((u32)AC->timerFlags);
			if ((f & 0x100) || (f & 0xc00))
				ok &= partList_queue(weapon_list(ac), vv, lights, tint, 1, flag_texture(s, f), (u32)st->litMatrix);
		}
	} else if (draw != 1) {
		f = ((u32)AC->timerFlags);
		int lists = 1;
		if (f & 0xd00) {
			if (g_highDetail == 0)
				lists = 0;
			else {
				float size = f32(FSUB(AC->tagBottomRight[0], AC->tagTopLeft[0]));
				if (fmul_m(fld_m(&k_640f) / (long double)gfx_getWidth(), k_40f) > size)
					lists = 0;
			}
		}
		if (lists && g_highDetail != 1 && tint && tint[3] <= 0x10)
			lists = 0;
		if (lists) {
			int n = AC->breakUp;
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
			u32 lt = flag_texture(s, f);
			for (int k = 0; k < 8; k++)
				if (k != 4 || !AC->viewMarked)
					ok &= partList_queue(ac + k_partLists[k], vv, lights, tint, 1, lt, (u32)st->litMatrix);
		}
	}
	AC->viewMarked = 0;
	if (ok)
		return;
	actor_loadHead(s, a);
	actor_loadBody(s, a);
	actor_loadArms(s, a);
	actor_loadLegs(s, a);
	actor_loadBooster(s, a);
	for (int k = 0; k < 6; k++)
		actor_loadWeapon(s, a, k, ((u32)AC->variantLoaded));
}
#undef K
#undef A
#undef AC

#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */

/* n dwords from at in the actor set to v */
static void fill_dwords(u8 *at, int n, u32 v)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(u32, at + k * 4) = v;
}

/* the pilot character's factor k (its profile's stats[4 + k]) as value x 0.01 + 1 */
static long double character_factor(u8 *p, int k)
{
	PlayerRecord *pr = (PlayerRecord *)p;
	return fadd_m(fmul_m((long double)g_characterProfiles[pr->character].stats[4 + k], &k_0_01f), &k_1f);
}

/* the mech's stats for actor ac from player record p's parts (the head, chest, arms, legs and booster records, the
   pilot character's skills, the special items' bonuses at ammoFactor .., the weight against the limit and the overload r slowing the
   legs and booster) and the fixed values, +0 .. +0x94. check: actor_checkDataLoss' copy, which rounds two of them
   differently */
static void mech_stats(u8 *s, u8 *ac, u8 *p, int check)
{
	PlayerRecord *pr = (PlayerRecord *)p;
	Stage *st = (Stage *)s;
	const HeadType *head = &st->headTypes[pr->parts[0]];
	const ChestType *chest = &st->chestTypes[pr->parts[1]];
	const ArmType *arms = &st->armTypes[pr->parts[2]];
	const LegType *legs = &st->legTypes[pr->parts[3]];
	const BoosterType *boost = &st->boosterTypes[pr->parts[4]];
	for (int k = 0; k < 4; k++) {
		AC->ammoFactor[k] = 1.0f;
		AC->ammoBonus[k] = 0;
	}
	AC->rangeBonus = 0.0f;
	BITS(AC->lockOnTimeFactor) = BITS(AC->targetKeepFactor) = 0x3f800000;
	AC->hackingBonus = 0;
	fill_dwords(ac + offsetof(Player, boostTimeFactor), 5, 0x3f800000);   /* boostTimeFactor .. shieldFactor */
	AC->shieldRegen = 0;
	for (int k = 0; k < 6; k++) {
		int it = pr->items[k];
		if (it < 0 || st->actorInfo[it].ammoSlot >= 0)
			continue;
		switch (it) {
		case 0x1b:
			for (int i = 0; i < 4; i++)
				AC->ammoFactor[i] = f32(fadd_m(fld_m(AC->ammoFactor + i), k_0_3f));
			break;
		case 0x1c: AC->ammoBonus[2] += 100; break;
		case 0x1d: AC->ammoBonus[0] += 100; break;
		case 0x1e: AC->ammoBonus[1] += 100; break;
		case 0x1f: AC->ammoBonus[3] += 100; break;
		case 0x20:
			AC->rangeBonus = f32(FADD(AC->rangeBonus, k_10000f));
			AC->lockOnTimeFactor = f32(FSUB(AC->lockOnTimeFactor, k_0_5f));
			AC->targetKeepFactor = f32(FADD(AC->targetKeepFactor, k_1f));
			AC->hackingBonus += 3;
			break;
		case 0x21:
			AC->boostTimeFactor = f32(FADD(AC->boostTimeFactor, k_0_5f));
			AC->rechargeTimeFactor = f32(FSUB(AC->rechargeTimeFactor, k_0_5f));
			AC->restTimeFactor = f32(FSUB(AC->restTimeFactor, k_0_5f));
			break;
		case 0x22:
			AC->loadFactor = f32(FADD(AC->loadFactor, k_0_2f));
			break;
		case 0x23:
			AC->shieldFactor = f32(fadd_m(fld_m(&AC->shieldFactor), k_0_3f));
			AC->shieldRegen += 4;
			break;
		}
	}
	long double hp = fadd_m(fmul_m(character_factor(p, 3), &head->detectionRange), &AC->rangeBonus);
	AC->radiusSq = f32(hp * hp);
	AC->detectionAngle = f32(fmul_m(character_factor(p, 3), &head->detectionAngle));
	AC->hackingLevel = head->hackingLevel + AC->hackingBonus;
	AC->lockOnTime = f32(FMUL(head->lockOnTime, AC->lockOnTimeFactor));
	AC->targetKeepTime = f32(FMUL(head->targetKeepTime, AC->targetKeepFactor));
	AC->loadMax = f32(fmul_m(fmul_m(character_factor(p, 4), &chest->weightLimit), &AC->loadFactor));
	AC->load = f32(fadd_m(fadd_m(FADD(boost->weight, legs->weight),
	                                   &arms->weight), &head->weight));
	int type = st->gameType;
	if (type < 2 || type > 0xb)
		for (int k = 0; k < 6; k++) {
			int it = pr->items[k];
			if (it >= 0)
				AC->load = f32(FADD(st->actorInfo[it].weight, AC->load));
		}
	long double over = AC->load > AC->loadMax
		? fmul_m(fdiv_m(FSUB(AC->load, AC->loadMax), &AC->loadMax), &k_4f)
		: fld_m(&k_0f);
	AC->armorMax = ftol(fadd_m(character_factor(p, 2) * (long double)chest->maxArmor, &k_0_5f));
	AC->shieldMax = ftol(fadd_m(fmul_m(character_factor(p, 2) * (long double)chest->maxShield, &AC->shieldFactor), &k_0_5f));
	AC->accuracy = arms->stats[0];
	for (int k = 0; k < 4; k++)
		AC->ammoMax[k] = ftol(fadd_m(fmul_m((long double)arms->stats[1 + k], AC->ammoFactor + k), &k_0_5f)) +
		                       AC->ammoBonus[k];
	long double left = fld_m(&k_1f) - over;
	long double v = fmul_m(character_factor(p, 0), &legs->agility) * left;
	AC->mobility = f32(v);
	if (!(v >= 0))
		AC->mobility = 0.0f;
	if (st->rocketArena == 1)
		AC->mobility = f32(FMUL(AC->mobility, k_0_333f));
	BITS(AC->leanPitch) = boost->lean;
	AC->boostTime = f32(FMUL(boost->activeTime[0], AC->boostTimeFactor));
	AC->rechargeTime = f32(FMUL(boost->activeTime[1], AC->rechargeTimeFactor));
	AC->restTime = f32(FMUL(boost->activeTime[2], AC->restTimeFactor));
	/* the legs' factors: the level's second value plus the legs' own, plus 1 */
#define LEG(f) fadd_m(fadd_m(fmul_m((long double)g_characterProfiles[pr->character].stats[5], &k_0_01f), &legs->f), &k_1f)
	v = fmul_m(LEG(speedCorrection), &boost->normalSpeed[0]) * left;
	AC->speed = f32(v);
	if (!(v >= *&k_100f))
		AC->speed = 100.0f;   /* 100 */
	v = FMUL(legs->inertia, AC->speed);
	AC->moveAccel = f32(v);
	if (st->rocketArena == 1)   /* (the check scales the stored value) */
		AC->moveAccel = f32(fmul_m(check ? fld_m(&AC->moveAccel) : v, &k_0_333f));
	v = fdiv_m(fmul_m(LEG(forwardBoostCorrection), &boost->normalSpeed[1]), &AC->speed) * left;
	AC->runTop[0] = f32(v);
	if (!(v >= 0))
		AC->runTop[0] = 0.0f;
	v = fmul_m(fdiv_m(fmul_m(LEG(backBoostCorrection), &boost->normalSpeed[2]), &AC->speed) * left, &k_m1f);
	AC->runTop[1] = f32(v);
	if (v > 0)
		AC->runTop[1] = 0.0f;
	v = fdiv_m(fmul_m(LEG(sideBoostCorrection), &boost->normalSpeed[3]), &AC->speed) * left;
	AC->runTop[2] = f32(v);
	if (!((check ? fld_m(&AC->runTop[2]) : v) >= 0))   /* (the check tests the stored value) */
		AC->runTop[2] = 0.0f;
#undef LEG
	AC->runTop[3] = f32(-fld_m(&AC->runTop[2]));
	AC->unused1c = 100;
	BITS(AC->topSpeed) = BITS(AC->speed);
	AC->turnRate = 900.0f;   /* 900 */
	AC->unused34 = 0x40400000;   /* 3 */
	AC->aimError = 10;
	AC->scriptFlag = 0;
	AC->dodgeSpread = 1000.0f;   /* 1000 */
	AC->climbSpread = 500.0f;   /* 500 */
	AC->botTimes[0] = 2.0f;   /* 2 */
	AC->botTimes[1] = 1.0f;
	AC->botTimes[2] = 4000.0f;   /* 4000 */
	AC->botTimes[3] = 5.0f;   /* 5 */
	AC->botTimes[4] = 1.0f;
}

/* 0x457330 (thiscall on the scene): actor a built from player *pp's mech (the player record 0x47fd2 bytes from
   playerRecords; its parts parts head, chest, arms, legs, booster; pp: the player, controlledBy copied, the position +8
   and the heading +0x14). The special items in its six slots (items; kinds 0x1b .. 0x23 with a negative ammoSlot)
   bend the defaults (ammoFactor ..: armour, shields, power, cooling, mobility); then the stats: health and energy (the
   head with the level), the weight against the limit (any items' weight unless the game type is 2 .. 11) giving an
   overload r that slows the legs and booster (speed, turn, jump, gravity, fall), the arms' ammunition, and the
   fixed values; its id (id, or the next serial when negative), the player's details, the weapon slot (actor_setWeaponSlot),
   the starting values (actor_startingValues), the position history, timers and flags reset, its lists loaded and parts
   placed (actor_loadHead .. actor_loadBooster, actor_loadWeapon; viewed by another than itself variantLoaded), and the scene told
   an actor joined (teamsChanged). Its caller ignores the eax it leaves */
void THISCALL (actor_setupFromParts)(u8 *s, int a, int id, u32 controlledBy, const u32 *pp)
{
	Stage *st = (Stage *)s;
	u8 *ac = (u8 *)&st->actors[a];
	u8 *p = (u8 *)&st->playerRecords[pp[0]];
	PlayerRecord *pr = (PlayerRecord *)p;
	mech_stats(s, ac, p, 0);
	AC->inPlay = 1;
	strcpy(AC->name, (const char *)RELOC(p) + 4);
	AC->id = id >= 0 ? id : st->actorSerial++;
	AC->active = 1;
	AC->player = pp[0];
	AC->controlledBy = controlledBy;
	int character = pr->character;
	AC->character = character >= 0 && character < 9 ? character : 0;
	AC->team = ((u32)pr->team);
	AC->bot = pp[1];
	AC->spawnAge = 0.0f;
	AC->armorDeadline = 1.0f;
	AC->armor = ((u32)AC->armorMax);
	AC->shield = ((u32)AC->shieldMax);
	fill_dwords(ac + offsetof(Player, ammo), 4, 0);   /* ammo */
	AC->slot = -1;
	AC->lastWeaponSlot = 0;
	actor_setWeaponSlot((Stage *)s, a, 0);
	actor_startingValues(s, a);   /* actor_startingValues */
	AC->state = 1;
	AC->stateTime = 0.0f;
	memcpy(AC->pos, pp + 2, 12);
	BITS(AC->pitch) = pp[5];
	BITS(AC->yaw) = pp[6];
	fill_dwords(ac + offsetof(Player, forward), 6, 0);   /* forward .. fireAnim */
	/* the next, sent and bot-goal states start at the place and the heading */
	memcpy(AC->nextPos, AC->pos, 12);
	BITS(AC->nextPitch) = BITS(AC->pitch);
	BITS(AC->nextYaw) = BITS(AC->yaw);
	memcpy(AC->netPos, AC->pos, 12);
	BITS(AC->netPitch) = BITS(AC->pitch);
	BITS(AC->netYaw) = BITS(AC->yaw);
	memcpy(AC->botGoal, AC->pos, 12);
	BITS(AC->botLookPitch) = BITS(AC->pitch);
	BITS(AC->botLookYaw) = BITS(AC->yaw);
	fill_dwords(ac + offsetof(Player, nextForward), 6, 0);   /* nextForward .. fireCycle */
	fill_dwords(ac + offsetof(Player, netMotion), 5, 0);   /* netMotion */
	fill_dwords(ac + offsetof(Player, netFired), 3, 0);   /* netFired .. burstLeft */
	AC->burstTime = 0.0f;
	for (int k = 0; k < 5; k++) {
		AC->shots[k].inUse = 0;
		AC->shots[k].isNew = 0;
		AC->shotBullets[k] = -1;
	}
	AC->sendNow = 0;
	memcpy(AC->velocity, (const void *)ADDR(g_vecZero), 12);
	memcpy(AC->move, (const void *)ADDR(g_vecZero), 12);
	AC->radius = 500.0f;   /* 500 */
	AC->chatIcon = 0;
	AC->timerFlags = AC->id % 2 == 1 ? 0x4000 : 0;
	fill_dwords(ac + offsetof(Player, timers), 4, 0);   /* timers */
	fill_dwords(ac + offsetof(Player, inForward), 11, 0);   /* inForward .. inBooster */
	AC->inWeaponSlot = -1;
	fill_dwords(ac + offsetof(Player, inPrevWeapon), 5, 0);   /* inPrevWeapon .. weaponLowering */
	AC->weaponLower = 1.0f;
	(*(int *)&AC->gauge) = AC->slotLoaded = 0;
	AC->variantLoaded = a == st->selectedActor ? 0 : 1;
	fill_dwords(ac + offsetof(Player, firePrev), 3, 0);   /* firePrev .. footstepTime */
	BITS(AC->energyUsed) = BITS(AC->staminaRest) = 0x3f800000;
	AC->overheat = AC->warned = 0;
	fill_dwords(ac + offsetof(Player, lastHitMode), 3, (u32)-1);   /* lastHitMode .. lastHitWeapon */
	AC->cheat = -1;
	memcpy(AC->deathPos, AC->pos, 12);
	AC->glow = 0.0f;
	(*(u8 *)&AC->message[0]) = 0;
	AC->messageTime = -10000.0f;   /* -10000 */
	AC->lastWarp = -1;
	fill_dwords(ac + offsetof(Player, onWarp), 3, 0);   /* onWarp .. shieldRegenTime */
	AC->damageFlash = 1.0f;
	AC->breakUp = 0;
	actor_loadHead(s, a);
	actor_loadBody(s, a);
	actor_loadArms(s, a);
	actor_loadLegs(s, a);
	actor_loadBooster(s, a);
	for (int k = 5; k >= 0; k--)
		actor_loadWeapon(s, a, k, ((u32)AC->variantLoaded));
	fill_dwords(ac + offsetof(Player, screenPos), 10, 0);   /* screenPos .. tagBottomRight, onScreen */
	fill_dwords(ac + offsetof(Player, aimTime), 4, 0);   /* aimTime .. botNeeds */
	AC->target1 = AC->target2 = -1;
	AC->pathReverse = (*(int *)&AC->botWait) = 0;
	AC->botWaitTrigger = -1;
	AC->invulnerable = 0;
	fill_dwords(ac + offsetof(Player, lookActor), 5, (u32)-1);   /* lookActor .. botTarget */
	fill_dwords(ac + offsetof(Player, scanTime), 5, 0);   /* scanTime .. heightTime */
	memcpy(AC->cleared8838, (const void *)ADDR(g_vecZero), 12);
	AC->lookTime = 0.0f;
	BITS(AC->pathRange) = 0x44bb8000;   /* 1500 */
	fill_dwords(ac + offsetof(Player, cameraValue), 3, 0);   /* cameraValue .. hitFlash */
	memcpy(AC->push, (const void *)ADDR(g_vecZero), 12);
	AC->botTargetTime = 0.0f;
	AC->killPending = 0;
	AC->stuckTime = 1.0f;
	AC->stuckPath = -1;
	memcpy(AC->stuckMove, (const void *)ADDR(g_vecZero), 12);
	AC->homedOn = (*(int *)&AC->beepTimer) = 0;
	(*(int *)&st->lockHeld[a]) = 0;
	st->teamsChanged = 1;
}
#undef AC

#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */

/* the actor's eight part lists (constructed on the stack copy as the original does) */
static const u16 k_listAt[8] = { offsetof(Player, headModel), offsetof(Player, chestModel), offsetof(Player, armsModel), offsetof(Player, legsModel), offsetof(Player, boosterModel), offsetof(Player, weaponModel), offsetof(Player, weaponModel4), offsetof(Player, weaponModel5) };

/* |a - b| (an x87 abs: a NaN stays) within 0.1 */
static int close_enough(const float *a, const float *b)
{
	long double d = fsub_m(fld_m(a), b);
	if (!(d >= 0))
		d = -d;
	return !(d > *&k_tenthsToDegrees);
}

/* whether actor ac's stats agree with mine, worked out again from its player's record (mech_stats in check mode,
   then the game type's fixed energy and weapons), and its limits hold */
static int totals_agree(u8 *s, u8 *ac, u8 *me)
{
	Stage *st = (Stage *)s;
	Player *act = (Player *)me;
	u8 *p = (u8 *)&st->playerRecords[AC->player];
	mech_stats(s, me, p, 1);
	unsigned mode = st->gameType - 2;
	if (mode <= 9) {
		int pair = mode / 2;
		act->armorMax = act->shieldMax = pair == 0 ? 10 : 150;
		if (pair < 4)
			act->ammoMax[pair] = 100;
	}
	static const u8 floats1[] = { offsetof(Player, radiusSq), offsetof(Player, detectionAngle) }, ints[] = { offsetof(Player, armorMax), offsetof(Player, shieldMax), offsetof(Player, accuracy), offsetof(Player, ammoMax[0]), offsetof(Player, ammoMax[1]), offsetof(Player, ammoMax[2]), offsetof(Player, ammoMax[3]) };
	static const u8 floats2[] = { offsetof(Player, lockOnTime), offsetof(Player, targetKeepTime), offsetof(Player, loadMax), offsetof(Player, load) }, floats3[] = { offsetof(Player, mobility), offsetof(Player, boostTime), offsetof(Player, rechargeTime), offsetof(Player, restTime), offsetof(Player, speed), offsetof(Player, moveAccel), offsetof(Player, runTop[0]), offsetof(Player, runTop[1]), offsetof(Player, runTop[2]), offsetof(Player, runTop[3]) };
	for (int k = 0; k < 2; k++)
		if (!close_enough((const float *)(ac + floats1[k]), (const float *)(me + floats1[k])))
			return 0;
	if (AC->hackingLevel != act->hackingLevel)
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
	if (!close_enough(&AC->topSpeed, &act->speed))
		return 0;
	int d = AC->shieldRegen - act->shieldRegen;
	if ((long double)(d < 0 ? -d : d) > *&k_tenthsToDegrees)
		return 0;
	if (AC->armor > AC->armorMax + 100 || AC->shield > AC->shieldMax + 100 || AC->ammo[0] > AC->ammoMax[0] ||
	    AC->ammo[1] > AC->ammoMax[1] || AC->ammo[2] > AC->ammoMax[2] || AC->ammo[3] > AC->ammoMax[3] || AC->shieldRegen > 8)
		return 0;
	const float *heat = k_30f;
	if ((AC->isKing == 0 && AC->timers[0] > *heat) || AC->timers[1] > *heat || (AC->isKing == 0 && AC->timers[2] > *heat) ||
	    AC->timers[3] > *heat)
		return 0;
	return 1;
}

/* 0x45ee40 (thiscall on the scene): the "data loss" check match_frame runs every 20 s on the local
   player's actor a: one not in play (state) passes; else totals_agree. The original's stack actor (its five
   resource sets and eight part lists constructed and destroyed again) is kept; its SEH frame is not reproduced.
   Returns 1 if all agree, else 0 */
u32 THISCALL (actor_checkDataLoss)(u8 *s, int a)
{
	Stage *st = (Stage *)s;
	u8 me[0x8888];   /* the stack actor (only the fields it computes are read) */
	for (int k = 0; k < 5; k++)
		ResourceSet_trivialCtor((u8 *)&((Player *)me)->rounds[k]);   /* ResourceSet_trivialCtor: a resource set */
	for (int k = 0; k < 8; k++) {
		GAME_VAR(u32, me + k_listAt[k]) = VT(UnitPoseInfo, 0x4a9754);
		partList_clear(me + k_listAt[k]);
	}
	u8 *ac = (u8 *)&st->actors[a];
	int ok = AC->state != 1 || totals_agree(s, ac, me);
	for (int k = 7; k >= 0; k--)
		UnitPoseInfo_dtor(me + k_listAt[k]);   /* UnitPoseInfo_dtor: a part list released */
	return ok;
}
#undef A
#undef AC
