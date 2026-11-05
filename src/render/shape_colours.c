/* shape_colours.c: a model's tint: each of its shapes' parts names a material (set m / 512, entry m % 512 of the
   material sets at g_textures) that is recoloured, or marked changed when the tint is taken off. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* a shape (Model): its parts (ShapePart, each with its material: texture) */
#define PART_COUNT(shape) (((Model *)(shape))->partCount)
#define PART(shape, i) ((ShapePart *)((Model *)(shape))->parts + (i))
#define MATERIAL_SET(m) FIELD(void *, (*(u8 **)&g_textures), ((m) / 512) * 4 + 4)

/* a model (a shape Manager): its shapes (items, 0x4c bytes each, count of them); its tint (tint[6]), on while bit 1 of
   bindFlags is set */
#define SHAPE_COUNT(model) (((Manager *)(model))->count)
#define SHAPE(model, i) (((Manager *)(model))->items + (i) * 0x4c)

/* 0x466560: each part's material marked changed */
void THISCALL (shape_markMaterialsChanged)(void *shape)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		int m = PART(shape, i)->texture;
		if (m < 0)
			continue;
		tex_markMaterialChanged(MATERIAL_SET(m), m % 512);
	}
}

/* 0x4665c0: each part's material recoloured (two hue, saturation, value triples) */
void THISCALL (shape_recolourMaterials)(void *shape, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		int m = PART(shape, i)->texture;
		if (m < 0)
			continue;
		tex_recolourMaterial(MATERIAL_SET(m), m % 512, h1, s1, v1, h2, s2, v2);
	}
}

/* 0x467660: the model tinted, every shape with it */
void THISCALL (shape_setTint)(Manager *model, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	model->tint[0] = h1;
	model->bindFlags |= 2;
	model->tint[3] = h2;
	model->tint[1] = s1;
	model->tint[2] = v1;
	model->tint[4] = s2;
	model->tint[5] = v2;
	for (int i = 0; i < SHAPE_COUNT((u8 *)model); i++)
		shape_recolourMaterials(SHAPE((u8 *)model, i), h1, s1, v1, h2, s2, v2);
}

/* 0x4675f0: the tint taken off */
void THISCALL (model_clearTint)(Manager *model)
{
	model->bindFlags &= ~2;
	for (int k = 0; k < 6; k++)
		model->tint[k] = 0;
	for (int i = 0; i < SHAPE_COUNT((u8 *)model); i++)
		shape_markMaterialsChanged(SHAPE((u8 *)model, i));
}

/* 0x466960: every part's pixels coloured (image_addColour on the part's place in px) */
void (shape_colourPixels)(u8 *px, int mode, const void *shape, const u8 *colour)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		const u32 *part = (const u32 *)PART(shape, i);
		image_addColour(px + part[0x12] * 4, mode, part, colour);
	}
}

/* 0x467580: a model's texture folder (textureDir) and flags (bindFlags) set; with flag 2 its tint (two HSV colours), else
   its shapes' own colours */
void THISCALL (shape_setTextureDir)(Manager *model, const char *folder, int flags, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2,
                                    u32 v2)
{
	strcpy(model->textureDir, folder);
	model->bindFlags = flags;
	if (flags & 2)
		shape_setTint((u8 *)model, h1, s1, v1, h2, s2, v2);
	else
		model_clearTint((u8 *)model);
}

/* 0x46de20: an RGBA byte colour tinted: to floats (/ 255), tex_tintHsv, back to bytes (* 255, all four channels,
   alpha too). Returns the last conversion */
int THISCALL (tex_tintRgba)(u8 *rgba, u32 dh, u32 ds, u32 dv)
{
	float c[4];
	for (int i = 0; i < 4; i++)
		c[i] = (float)fmul_m((long double)(int)rgba[i], k_0_00392157f);   /* 1 / 255 */
	tex_tintHsv(c, dh, ds, dv);
	int r = 0;
	for (int i = 0; i < 4; i++) {
		r = ftol(fmul_m(fld_m(&c[i]), k_255f));   /* 255 */
		rgba[i] = (u8)r;
	}
	return r;
}

/* 0x466910: every part's shading colours (shape_getShadingColorBufferBy) into out at the part's index (colourBase),
   with the factors and the matrix. Returns the part count */
int (shape_shadingColours)(float *out, int first, u8 *shape, void *factors, int matrix)
{
	Model *md = (Model *)shape;
	for (int i = 0; i < md->partCount; i++) {
		ShapePart *part = (ShapePart *)(md->parts + i * 0x80);
		GAME_FN(shape_getShadingColorBufferBy, 0x463b80, void, float *, int, void *, void *, int)(out + part->colourBase, first, (u8 *)part, factors,
		                                                                matrix);   /* shape_getShadingColorBufferBy */
	}
	return md->partCount;
}
