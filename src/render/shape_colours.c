/* shape_colours.c: a model's tint: each of its shapes' parts names a material (set m / 512, entry m % 512 of the
   material sets at g_textures) that is recoloured, or marked changed when the tint is taken off. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, AP(u8, RELOC(obj)) + (offset))

/* a shape (Shape): its parts (ShapePart, each with its material: texture) */
#define PART_COUNT(shape) (((Shape *)(shape))->partCount)
#define PART(shape, i) ((ShapePart *)((Shape *)(shape))->parts + (i))
#define MATERIAL_SET(m) FIELD(void *, (*(u8 **)&g_textures), ((m) / 512) * 4 + 4)

/* a shape manager (ShapeManager): its shapes (items, 0x4c bytes each, count of them); its tint (tint[6]), on while bit 1 of
   bindFlags is set */
#define SHAPE_COUNT(model) (((ShapeManager *)(model))->count)
#define SHAPE(model, i) (((ShapeManager *)(model))->items + (i) * 0x4c)

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

/* 0x4665c0: each part's material (texture >= 0) given the two hue / saturation / value tints (tex_setMaterialTint);
   the pixels are recoloured later, when tex_bind reloads it */
void THISCALL (shape_setMaterialTints)(void *shape, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		int m = PART(shape, i)->texture;
		if (m < 0)
			continue;
		tex_setMaterialTint(MATERIAL_SET(m), m % 512, h1, s1, v1, h2, s2, v2);
	}
}

/* 0x467660: the model tinted, every shape with it */
void THISCALL (shape_setTint)(ShapeManager *model, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	BITS(model->tint[0]) = h1;
	model->bindFlags |= 2;
	BITS(model->tint[3]) = h2;
	BITS(model->tint[1]) = s1;
	BITS(model->tint[2]) = v1;
	BITS(model->tint[4]) = s2;
	BITS(model->tint[5]) = v2;
	for (int i = 0; i < SHAPE_COUNT((u8 *)model); i++)
		shape_setMaterialTints(AP(void, SHAPE((u8 *)model, i)), h1, s1, v1, h2, s2, v2);
}

/* 0x4675f0: the shape manager's tint record cleared (bindFlags bit 1 off, tint[0..5] 0) and each shape's part
   materials marked changed (shape_markMaterialsChanged). The materials keep flag 2 and their tints
   (tex_markMaterialChanged keeps bits 0x11111113), so a reload still tints them. Only reached from
   shape_setTextureSuffix without flag 2, and its one caller (playerRecord_setPartColour) always passes 2 */
void THISCALL (shape_clearTint)(ShapeManager *model)
{
	model->bindFlags &= ~2;
	for (int k = 0; k < 6; k++)
		model->tint[k] = 0;
	for (int i = 0; i < SHAPE_COUNT((u8 *)model); i++)
		shape_markMaterialsChanged(AP(void, SHAPE((u8 *)model, i)));
}

/* 0x466960: one RGBA colour added to (mode 0) or set on (mode 1) every part's vertex colours, which are the part's
   slice of the shape's colour buffer px from colourBase (part_addColour) */
void (shape_addColour)(u8 *px, int mode, const void *shape, const u8 *colour)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		const u32 *part = (const u32 *)PART(shape, i);
		part_addColour(px + part[0x12] * 4, mode, part, colour);
	}
}

/* 0x467580: a shape manager's texture-name suffix (textureSuffix, e.g. "_T<player>") and bindFlags set; with flag 2
   its tint (two HSV colours, shape_setTint), else shape_clearTint */
void THISCALL (shape_setTextureSuffix)(ShapeManager *model, const char *suffix, int flags, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2,
                                    u32 v2)
{
	strcpy(model->textureSuffix, suffix);
	model->bindFlags = flags;
	if (flags & 2)
		shape_setTint((u8 *)model, h1, s1, v1, h2, s2, v2);
	else
		shape_clearTint((u8 *)model);
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
int (shape_shadingColours)(u32 *out, int first, u8 *shape, void *factors, const float *matrix)
{
	Shape *md = (Shape *)shape;
	for (int i = 0; i < md->partCount; i++) {
		ShapePart *part = AP(ShapePart, (md->parts + i * 0x80));
		shape_getShadingColorBufferBy(out + part->colourBase, first, (u8 *)part, factors,
		                                                                matrix);   /* shape_getShadingColorBufferBy */
	}
	return md->partCount;
}
