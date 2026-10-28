/* object_list.c: an object list: shapes placed by their own matrices, each with a buffer of shading colours, lit by
   light factors (shape_shadeParts, through the inverse of the shape's matrix) and point lights (shape_lightParts),
   and handed to the view volume. */
#include "../game.h"

/* an entry's colours: with neither lights nor factors cleared; factors first (they set the colours), point lights
   then added on top, or alone (setting them). The inverse is taken again before the point lights, as the original
   does, though they do not use it; a singular matrix leaves inverse as it was */
static void relight(ListedObject *e, const LightFactors *factors, const void *lights)
{
	float inverse[16];
	if (lights == NULL) {
		if (factors != NULL) {
			Mat4_invert(inverse, e->matrix);
			shape_shadeParts(e->colours, 1, e->shape, factors, inverse);
		} else {
			for (u32 k = 0; k < (u32)e->shape->colourCount; k++)
				e->colours[k] = 0;
		}
	} else if (factors != NULL) {
		Mat4_invert(inverse, e->matrix);
		shape_shadeParts(e->colours, 1, e->shape, factors, inverse);
		Mat4_invert(inverse, e->matrix);
		shape_lightParts(e->colours, 0, e->shape, lights);
	} else {
		Mat4_invert(inverse, e->matrix);
		shape_lightParts(e->colours, 1, e->shape, lights);
	}
}

/* 0x46f7a0 (data_46f7a0): relight every entry that has a shape */
void THISCALL (data_46f7a0)(ObjectList *list, const LightFactors *factors, const void *lights)
{
	for (int i = 0; i < list->count; i++) {
		ListedObject *e = &list->entries[i];
		if (e->shape != NULL)
			relight(e, factors, lights);
	}
}

/* 0x46fd20 (hud_46fd20): the list into the view volume, when it has frames and the current one is set (returns 1;
   else 0 and nothing done). A pre-lit list (preLit == 1) is relit here (factors only while factors->enabled when
   there are no point lights) and drawn with its own colours; any other list hands the factors and lights on. cull,
   material and a8 go to ViewVolume_projectObject. */
int THISCALL (hud_46fd20)(ObjectList *list, void *view, const LightFactors *factors, const void *lights, int cull,
                          int material, int a8)
{
	if (list->frameCount <= 0 || list->count <= 0 || list->frames[list->frame] == 0)
		return 0;
	for (int i = 0; i < list->count; i++) {
		ListedObject *e = &list->entries[i];
		if (e->shape == NULL)
			continue;
		if (list->preLit == 1) {
			if (lights != NULL || factors == NULL || factors->enabled == 1)
				relight(e, factors, lights);
			ViewVolume_projectObject(view, e->shape, (u32)e->colours, e->matrix, 0, NULL, cull, material, a8);
		} else {
			ViewVolume_projectObject(view, e->shape, 0, e->matrix, (int)factors, lights, cull, material, a8);
		}
	}
	return 1;
}
