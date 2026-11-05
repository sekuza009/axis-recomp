/* object_list.c: an object list: shapes placed by their own matrices, each with a buffer of shading colours, lit by
   light factors (shape_shadeParts, through the inverse of the shape's matrix) and point lights (shape_lightParts),
   and handed to the view volume. */
#include "../game.h"
#include <string.h>


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
   material and the extra matrix go to ViewVolume_projectObject. */
int THISCALL (partList_queue)(ObjectList *list, void *view, const LightFactors *factors, const void *lights, int cull,
                          int material, int extraMatrix)
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
			ViewVolume_projectObject(view, e->shape, (u32)e->colours, e->matrix, 0, NULL, cull, material, extraMatrix);
		} else {
			ViewVolume_projectObject(view, e->shape, 0, e->matrix, (int)factors, lights, cull, material, extraMatrix);
		}
	}
	return 1;
}

/* 0x497a90: the draw records of the stage's meshes (0x20c bytes each from +0xdc0278): for mesh i a vertex record B
   (at *(+0xdc0a8c) + i * 0x80) and a box record A (*(+0xdc0cd8) + i * 0x80), the vertex and index counts summed, and
   each mesh's box sides written into it: four fans of five of its twelve points */
void THISCALL (stage_buildMeshDrawRecords)(u8 *stage)
{
	Stage *st = (Stage *)stage;
	int n = st->groundLayerCount;
	st->layerModel.partCount = n;
	st->layerModel.colourCount = 0;
	st->layerModel.triangleCount = 0;
	st->layerBoxModel.partCount = st->groundLayerCount;
	st->layerBoxModel.colourCount = 0;
	st->layerBoxModel.triangleCount = 0;
	static const int sides[4][5] = { { 4, 5, 0, 3, 0xb }, { 6, 7, 1, 0, 5 }, { 8, 9, 2, 1, 7 }, { 0xa, 0xb, 3, 2, 9 } };
	for (int i = 0; i < st->groundLayerCount; i++) {
		GroundLayer *gl = &st->groundLayers[i];
		ShapePart *A = (ShapePart *)st->layerBoxModel.parts + i, *B = (ShapePart *)st->layerModel.parts + i;
		switch (gl->kind) {
		case 0:
			*(int *)B->name = 0;
			*(int *)A->name = 0;
			break;
		case 1:
			*(int *)B->name = 8;
			*(int *)A->name = 8;
			break;
		case 2:
			*(int *)B->name = 6;
			*(int *)A->name = 6;
			break;
		}
		B->texture = gl->texture;
		A->texture = gl->texture;
		B->colourBase = st->layerModel.colourCount;
		B->vertexCount = (int)((u32)(gl->rows + 1) * (u32)(gl->cols + 1));
		B->vertices = (u8 *)gl->points;
		B->colours = (u8 *)gl->colours;
		B->texCoords = gl->uv;
		B->primCount = 0;
		B->prims = gl->strips;
		A->colourBase = st->layerBoxModel.colourCount;
		A->vertices = (u8 *)gl->boxPoints;
		A->colours = (u8 *)gl->boxColours;
		A->vertexCount = 0xc;
		A->texCoords = &gl->boxUv[0][0];
		A->primCount = gl->lit == 1 ? 4 : 0;
		A->prims = (u8 *)gl->boxPrims;
		for (int f = 0; f < 4; f++) {
			gl->boxPrims[f].kind = 6;   /* (a fan) */
			gl->boxPrims[f].indexCount = 5;
			gl->boxPrims[f].indices = (u8 *)gl->boxIndices[f];
			memcpy(gl->boxIndices[f], sides[f], sizeof sides[f]);
		}
		st->layerModel.colourCount += B->vertexCount;
		st->layerBoxModel.colourCount += A->vertexCount;
	}
}

/* 0x46fed0: the textures of every shape in an object list bound (count +0x10, 100-byte entries from *(+0x14), the
   shape first) */
void THISCALL (partList_bindTextures)(u8 *list)
{
	for (int i = 0; i < ((ObjectList *)list)->count; i++) {
		void *shape = ((ObjectList *)list)->entries[i].shape;
		if (shape)
			shape_bindPartTextures(shape);
	}
}

/* 0x466650: the textures of a shape's parts (their texture id at +0x44, none when negative) bound in turn, with
   texturing on during it */
void THISCALL (shape_bindPartTextures)(u8 *shape)
{
	Model *md = (Model *)shape;
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < md->partCount; i++) {
		int id = ((ShapePart *)(md)->parts + i)->texture;
		if (id >= 0)
			tex_bind(g_textures->banks[id / 512], id % 512);
	}
	glDisable(GL_TEXTURE_2D);
}
