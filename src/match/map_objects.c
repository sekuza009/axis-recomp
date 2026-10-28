/* map_objects.c: map objects switched on and off, with the collision units of their shapes (each unit's parts a
   linked list, bit 0 of a part's flags: left out of collisions). */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* a part of a collision unit: flags first, the next part at +0xa4; the unit keeps its first part at +4 */
static void unit_parts_flag(void *unit, int set)
{
	for (u32 *p = FIELD(u32 *, unit, 4); p; p = FIELD(u32 *, p, 0xa4))
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
