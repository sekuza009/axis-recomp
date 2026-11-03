/* object_list.c: an object list: shapes placed by their own matrices, each with a buffer of shading colours, lit by
   light factors (shape_shadeParts, through the inverse of the shape's matrix) and point lights (shape_lightParts),
   and handed to the view volume. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

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

/* 0x46f7a0 (ObjectList_relight): relight every entry that has a shape */
void THISCALL (ObjectList_relight)(ObjectList *list, const LightFactors *factors, const void *lights)
{
	for (int i = 0; i < list->count; i++) {
		ListedObject *e = &list->entries[i];
		if (e->shape != NULL)
			relight(e, factors, lights);
	}
}

/* 0x46fd20 (partList_queue): the list into the view volume, when it has frames and the current one is set (returns 1;
   else 0 and nothing done). A pre-lit list (preLit == 1) is relit here (factors only while factors->enabled when
   there are no point lights) and drawn with its own colours; any other list hands the factors and lights on. cull,
   material and a8 go to ViewVolume_projectObject. */
int THISCALL (partList_queue)(ObjectList *list, void *view, const LightFactors *factors, const void *lights, int cull,
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

/* 0x497a90: the draw records of the stage's meshes (0x20c bytes each from +0xdc0278): for mesh i a vertex record B
   (at *(+0xdc0a8c) + i * 0x80) and a box record A (*(+0xdc0cd8) + i * 0x80), the vertex and index counts summed, and
   each mesh's fixed six-face index lists written into it (with their pointers) */
void THISCALL (stage_buildMeshDrawRecords)(u8 *stage)
{
	Stage *st = (Stage *)stage;
	int n = st->groundLayerCount;
	FIELD(int, stage, 0xdc0a88) = n;
	FIELD(int, stage, 0xdc0a90) = 0;
	FIELD(int, stage, 0xdc0a94) = 0;
	FIELD(int, stage, 0xdc0cd4) = st->groundLayerCount;
	FIELD(int, stage, 0xdc0cdc) = 0;
	FIELD(int, stage, 0xdc0ce0) = 0;
	static const short faces[][2] = {   /* (offset in the mesh, value), in the original's order of stores */
		{ 0x1b4, 6 }, { 0x1a8, 6 }, { 0x1c0, 6 }, { 0x1cc, 6 }, { 0x1ac, 5 }, { 0x1b8, 5 }, { 0x1c4, 5 }, { 0x1d0, 5 },
		{ 0x158, 4 }, { 0x16c, 6 }, { 0x15c, 5 }, { 0x160, 0 }, { 0x164, 3 }, { 0x168, 0xb }, { 0x170, 7 }, { 0x174, 1 },
		{ 0x178, 0 }, { 0x17c, 5 }, { 0x180, 8 }, { 0x184, 9 }, { 0x188, 2 }, { 0x18c, 1 }, { 0x190, 7 }, { 0x194, 0xa },
		{ 0x198, 0xb }, { 0x19c, 3 }, { 0x1a0, 2 }, { 0x1a4, 9 } };
	for (int i = 0; i < st->groundLayerCount; i++) {
		u8 *m = stage + 0xdc0278 + i * 0x20c;
		u8 *A = FIELD(u8 *, stage, 0xdc0cd8) + i * 0x80, *B = FIELD(u8 *, stage, 0xdc0a8c) + i * 0x80;
		switch (FIELD(int, m, -0x34)) {
		case 0:
			FIELD(int, B, 0) = 0;
			FIELD(int, A, 0) = 0;
			break;
		case 1:
			FIELD(int, B, 0) = 8;
			FIELD(int, A, 0) = 8;
			break;
		case 2:
			FIELD(int, B, 0) = 6;
			FIELD(int, A, 0) = 6;
			break;
		}
		FIELD(int, B, 0x44) = FIELD(int, m, 0);
		FIELD(int, A, 0x44) = FIELD(int, m, 0);
		FIELD(int, B, 0x48) = FIELD(int, stage, 0xdc0a90);
		FIELD(int, B, 0x4c) = (int)((u32)(FIELD(int, m, -0x18) + 1) * (u32)(FIELD(int, m, -0x14) + 1));
		FIELD(int, B, 0x50) = FIELD(int, m, 0xc);
		FIELD(int, B, 0x58) = FIELD(int, m, 0x14);
		FIELD(int, B, 0x5c) = FIELD(int, m, 0x1c);
		FIELD(int, B, 0x60) = 0;
		FIELD(int, B, 0x64) = FIELD(int, m, 0x30);
		FIELD(int, A, 0x48) = FIELD(int, stage, 0xdc0cdc);
		FIELD(u8 *, A, 0x50) = m + 0x38;
		FIELD(u8 *, A, 0x58) = m + 0xc8;
		FIELD(int, A, 0x4c) = 0xc;
		FIELD(u8 *, A, 0x5c) = m + 0xf8;
		FIELD(int, A, 0x60) = FIELD(int, m, -4) == 1 ? 4 : 0;
		FIELD(u8 *, A, 0x64) = m + 0x1a8;
		for (unsigned k = 0; k < sizeof faces / sizeof faces[0]; k++) {
			if (k == 8) {   /* the index lists' pointers, stored among the constants */
				FIELD(u8 *, m, 0x1b0) = m + 0x158;
				FIELD(u8 *, m, 0x1c8) = m + 0x180;
				FIELD(u8 *, m, 0x1bc) = m + 0x16c;
			}
			if (k == 10)
				FIELD(u8 *, m, 0x1d4) = m + 0x194;
			FIELD(int, m, faces[k][0]) = faces[k][1];
		}
		FIELD(int, stage, 0xdc0a90) += FIELD(int, B, 0x4c);
		FIELD(int, stage, 0xdc0cdc) += FIELD(int, A, 0x4c);
	}
}

/* 0x46fed0: the textures of every shape in an object list bound (count +0x10, 100-byte entries from *(+0x14), the
   shape first) */
void THISCALL (partList_bindTextures)(u8 *list)
{
	for (int i = 0; i < FIELD(int, list, 0x10); i++) {
		void *shape = FIELD(void *, FIELD(u8 *, list, 0x14) + i * 0x64, 0);
		if (shape)
			shape_bindPartTextures(shape);
	}
}

/* 0x466650: the textures of a shape's parts (their texture id at +0x44, none when negative) bound in turn, with
   texturing on during it */
void THISCALL (shape_bindPartTextures)(u8 *shape)
{
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < FIELD(int, shape, 0x10); i++) {
		int id = FIELD(int, FIELD(u8 *, shape, 0x14) + i * 0x80, 0x44);
		if (id >= 0)
			tex_bind(g_textures->managers[id / 512], id % 512);
	}
	glDisable(GL_TEXTURE_2D);
}
