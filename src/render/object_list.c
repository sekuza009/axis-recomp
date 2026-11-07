/* object_list.c: an object list: shapes placed by their own matrices, each with a buffer of shading colours, lit by
   light factors (shape_shadingColours, through the inverse of the shape's matrix) and a tint colour (shape_addColour),
   and handed to the view volume. */
#include "../game.h"
#include <string.h>


/* an entry's colours: with neither tint nor factors cleared; factors first (they set the colours), the tint colour
   then added on top, or alone (setting them). The inverse is taken again before the tint, as the original
   does, though they do not use it; a singular matrix leaves inverse as it was */
static void relight(ListedObject *e, const LightFactors *factors, const void *tint)
{
	float inverse[16];
	if (tint == NULL) {
		if (factors != NULL) {
			Mat4_invert(inverse, e->matrix);
			shape_shadingColours(e->colours, 1, e->shape, factors, inverse);
		} else {
			for (u32 k = 0; k < (u32)e->shape->colourCount; k++)
				e->colours[k] = 0;
		}
	} else if (factors != NULL) {
		Mat4_invert(inverse, e->matrix);
		shape_shadingColours(e->colours, 1, e->shape, factors, inverse);
		Mat4_invert(inverse, e->matrix);
		shape_addColour(e->colours, 0, e->shape, tint);
	} else {
		Mat4_invert(inverse, e->matrix);
		shape_addColour(e->colours, 1, e->shape, tint);
	}
}

/* 0x46f7a0 (ObjectList_relight): every entry that has a shape recoloured: shaded by the light factors
   (shape_shadingColours through the inverse of its matrix), then the colour tint added on top (or alone set) by
   shape_addColour (part_addColour: RGB added and clamped, alpha the minimum); neither gives black */
void THISCALL (ObjectList_relight)(ObjectList *list, const LightFactors *factors, const void *tint)
{
	for (int i = 0; i < list->count; i++) {
		ListedObject *e = &list->entries[i];
		if (e->shape != NULL)
			relight(e, factors, tint);
	}
}

/* 0x46fd20: the list into the view volume, when it has frames and the current one is set (returns 1; else 0 and
   nothing done). A pre-lit list (preLit == 1) is recoloured here (relight: factors and the tint; skipped only when
   there is no tint, factors are given and factors->enabled is not 1) and queued with its own colours; any other list
   hands the factors and the tint colour on (ViewVolume_queueModel's colour). cull, material and the extra matrix
   go to ViewVolume_queueModel. */
int THISCALL (ObjectList_queue)(ObjectList *list, void *view, const LightFactors *factors, const void *tint, int cull,
                          int material, int extraMatrix)
{
	if (list->skelCount <= 0 || list->count <= 0 || list->skeletons[list->skel] == 0)
		return 0;
	for (int i = 0; i < list->count; i++) {
		ListedObject *e = &list->entries[i];
		if (e->shape == NULL)
			continue;
		if (list->preLit == 1) {
			if (tint != NULL || factors == NULL || factors->enabled == 1)
				relight(e, factors, tint);
			ViewVolume_queueModel(view, e->shape, (u32)e->colours, e->matrix, 0, NULL, cull, material, extraMatrix);
		} else {
			ViewVolume_queueModel(view, e->shape, 0, e->matrix, (int)factors, tint, cull, material, extraMatrix);
		}
	}
	return 1;
}

/* 0x497a90 (thiscall on the stage): the ground's two models set up from its layers (0x20c bytes each from
   groundLayers): for layer i a part of layerModel (the grid: (rows + 1) x (cols + 1) points, colours, uv, its strips)
   and a part of waterModel (12 points, waterColours, waterUv, four fans of five of its twelve points; drawn only for
   a water layer: primCount 4, ground_buildDrawLists makes the points); both parts' flags by the layer's kind (0: 0,
   1: 8, 2: 6) and its texture; the models' colourCount summed from the vertex counts (triangleCount 0) */
void THISCALL (ground_buildLayerModels)(u8 *stage)
{
	Stage *st = (Stage *)stage;
	int n = st->groundLayerCount;
	st->layerModel.partCount = n;
	st->layerModel.colourCount = 0;
	st->layerModel.triangleCount = 0;
	st->waterModel.partCount = st->groundLayerCount;
	st->waterModel.colourCount = 0;
	st->waterModel.triangleCount = 0;
	static const int sides[4][5] = { { 4, 5, 0, 3, 0xb }, { 6, 7, 1, 0, 5 }, { 8, 9, 2, 1, 7 }, { 0xa, 0xb, 3, 2, 9 } };
	for (int i = 0; i < st->groundLayerCount; i++) {
		GroundLayer *gl = &st->groundLayers[i];
		ShapePart *A = (ShapePart *)st->waterModel.parts + i, *B = (ShapePart *)st->layerModel.parts + i;
		switch (gl->kind) {
		case 0:
			B->flags = 0;
			A->flags = 0;
			break;
		case 1:
			B->flags = 8;
			A->flags = 8;
			break;
		case 2:
			B->flags = 6;
			A->flags = 6;
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
		A->colourBase = st->waterModel.colourCount;
		A->vertices = (u8 *)gl->waterPoints;
		A->colours = (u8 *)gl->waterColours;
		A->vertexCount = 0xc;
		A->texCoords = &gl->waterUv[0][0];
		A->primCount = gl->water == 1 ? 4 : 0;
		A->prims = (u8 *)gl->waterPrims;
		for (int f = 0; f < 4; f++) {
			gl->waterPrims[f].kind = 6;   /* (a fan) */
			gl->waterPrims[f].indexCount = 5;
			gl->waterPrims[f].indices = (u8 *)gl->waterIndices[f];
			memcpy(gl->waterIndices[f], sides[f], sizeof sides[f]);
		}
		st->layerModel.colourCount += B->vertexCount;
		st->waterModel.colourCount += A->vertexCount;
	}
}

/* 0x46fed0: the textures of every shape in an object list bound (count count, 100-byte entries from *(entries), the
   shape first) */
void THISCALL (ObjectList_bindTextures)(ObjectList *list)
{
	for (int i = 0; i < list->count; i++) {
		void *shape = list->entries[i].shape;
		if (shape)
			shape_bindPartTextures(shape);
	}
}

/* 0x466650: the textures of a shape's parts (their texture id at texture, none when negative) bound in turn, with
   texturing on during it */
void THISCALL (shape_bindPartTextures)(u8 *shape)
{
	Shape *md = (Shape *)shape;
	glEnable(GL_TEXTURE_2D);
	for (int i = 0; i < md->partCount; i++) {
		int id = ((ShapePart *)(md)->parts + i)->texture;
		if (id >= 0)
			tex_bind(g_textures->banks[id / 512], id % 512);
	}
	glDisable(GL_TEXTURE_2D);
}
