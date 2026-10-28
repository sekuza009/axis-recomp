/* actor_slots.c: the stage's actor slots: selecting one, the camera's target, an actor's input record, and the
   stage's pools of map objects, projectiles and bullets emptied. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* an actor's input record: twelve ints (the moves and buttons the actor acts on this frame); the ninth is the
   one cleared to -1 */
static const int input_fields[12] = { 0x44c, 0x450, 0x454, 0x458, 0x464, 0x468, 0x46c, 0x470, 0x474, 0x478, 0x47c,
                                      0x480 };

/* 0x45eab0: actor i's input cleared */
void THISCALL (actor_45eab0)(Stage *stage, int i)
{
	Player *a = &stage->actors[i];
	for (int k = 0; k < 12; k++)
		FIELD(int, a, input_fields[k]) = k == 9 ? -1 : 0;
}

/* 0x45eb20: actor i's input set */
void THISCALL (match_45eb20)(Stage *stage, int i, int v0, int v1, int v2, int v3, int v4, int v5, int v6, int v7,
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
void THISCALL (load_490d10)(Stage *stage)
{
	FIELD(int, stage, 0x13016c8) = 0;
	stage->objectCount = 0;
	FIELD(int, stage, 0x13c9b28) = 0;
	FIELD(int, stage, 0x13c9b2c) = 0;
	for (int i = 0; i < 1000; i++)
		stage->objects[i].active = 0;
}

/* 0x479a60: the 1000 projectiles */
void THISCALL (load_479a60)(Stage *stage)
{
	stage->projectileCount = 0;
	FIELD(int, stage, 0x20f2da4) = 0;
	FIELD(int, stage, 0x20f2da8) = 0;
	for (int i = 0; i < 1000; i++)
		stage->projectiles[i].active = 0;
}

/* 0x47cfd0: the 400 bullets (0x4e8-byte records from 0x202ef34) */
void THISCALL (FUN_0047cfd0)(Stage *stage)
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
	FIELD(int, a, 0x10c) = -1;
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

/* 0x47d060: every bullet in use drawn (its trail, hud_47ca70) */
void THISCALL (hud_47d060)(Stage *stage, void *view)
{
	for (int i = 0; i < FIELD(int, stage, 0x20a99b4); i++)
		if (FIELD(int, stage, 0x202ef38 + i * 0x4e8) == 1)
			hud_47ca70(stage, i, view);
}

/* 0x48fde0: while the script runs (+0x2149308), its object (+0x2148ed8) told (hud_48b450); returns b */
int THISCALL (hud_48fde0)(Stage *stage, int a, int b, int c, int d)
{
	if (!FIELD(int, stage, 0x2149308))
		return 0;
	hud_48b450((u8 *)stage + 0x2148ed8, a, b, c, d);
	return b;
}

/* 0x470a70: every actor slot emptied: the six slot numbers from playerActor on (-1), +0x202e8ec 1, the scores, the
   16 player records and the stage's own reset, then the 100 slots */
void THISCALL (scene_resetActors)(Stage *stage)
{
	for (int k = 0; k < 6; k++)
		FIELD(int, stage, 0x202e8d4 + k * 4) = -1;
	FIELD(int, stage, 0x202e8ec) = 1;
	FUN_0045df90(stage);
	load_474480(stage);
	FUN_0045e070(stage);
	for (int i = 0; i < 100; i++)
		actor_resetSlot(stage, i);
}

/* 0x45e070: the 100 actor slots emptied (none in use, each free with no player), with the counts */
void THISCALL (FUN_0045e070)(Stage *stage)
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
