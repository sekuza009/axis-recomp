/* map_objects.c: map objects switched on and off, with the collision units of their shapes (each unit's parts a
   linked list, bit 0 of a part's flags: left out of collisions). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* a collision unit's planes (from its last, lastPlane, back through listPrev) flagged or not (flag 1: off) */
static void unit_parts_flag(void *unit, int set)
{
	for (u32 *p = (u32 *)((SpaceUnit *)unit)->lastPlane; p; p = (u32 *)((CollisionPlane *)p)->listPrev)
		if (set)
			*p |= 1;
		else
			*p &= ~1u;
}

/* 0x480460, 0x480480: every part of a unit out of / back into the collisions */
void THISCALL (space_disableUnit)(void *unit) { unit_parts_flag(unit, 1); }
void THISCALL (space_enableUnit)(void *unit) { unit_parts_flag(unit, 0); }

/* an object's collision unit (+0x28c), used while +0x290 is 1 */
#define OBJECT_UNIT(o) FIELD(void *, o, 0x28c)
#define OBJECT_HAS_UNIT(o) FIELD(int, o, 0x290)

/* 0x490ee0, 0x490f30: map object i switched on / off (when it was not already), its unit with it */
void THISCALL (object_activate)(Stage *stage, int i)
{
	MapObject *o = &stage->objects[i];
	if (o->active)
		return;
	o->active = 1;
	if (OBJECT_HAS_UNIT(o) == 1 && OBJECT_UNIT(o))
		space_enableUnit(OBJECT_UNIT(o));
}

void THISCALL (object_deactivate)(Stage *stage, int i)
{
	MapObject *o = &stage->objects[i];
	if (o->active != 1)
		return;
	o->active = 0;
	if (OBJECT_HAS_UNIT(o) == 1 && OBJECT_UNIT(o))
		space_disableUnit(OBJECT_UNIT(o));
}

/* 0x490df0: script command 0x1c: object i's animation: none (no name, or mode 0) stops it; otherwise its skeleton
   from the stage's cache (+0x13016d0), its collision unit out of the collisions, the rate 1 / period (+-1 for a
   period within 1e-8 of 0, -1 also for a NaN) */
void THISCALL (object_setAnimation)(Stage *stage, int i, u32 name, float period, int mode)
{
	MapObject *o = &stage->objects[i];
	if (!name || !mode) {
		BITS(o->animRate) = 0;
		return;
	}
	o->skeleton = skel_getSkeletonPtrBy((u8 *)&stage->objectSkeletons, name);
	if (o->unit)
		space_disableUnit(o->unit);
	o->animated = 1;
	o->animMode = mode;
	long double p = period;
	if ((p < 0 ? -p : p) > 1e-8f)
		o->animRate = (float)(1.0L / p);
	else
		o->animRate = period >= 0.0f ? 1.0f : -1.0f;
}
