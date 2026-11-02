/* shape_colours.c: a model's tint: each of its shapes' parts names a material (set m / 512, entry m % 512 of the
   material sets at 0xa0e010) that is recoloured, or marked changed when the tint is taken off. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* a shape: its part count at +0x10, its 0x80-byte parts at +0x14 (each with its material at +0x44) */
#define PART_COUNT(shape) FIELD(int, shape, 0x10)
#define PART(shape, i) (FIELD(u8 *, shape, 0x14) + (i) * 0x80)
#define MATERIAL_SET(m) FIELD(void *, (*(u8 **)&g_textures), ((m) / 512) * 4 + 4)

/* a model: its shapes (0x4c bytes each) at +0x11c, their count at +0x120; its tint at +0x234 .. +0x248, on while
   bit 1 of +0x230 is set */
#define SHAPE_COUNT(model) FIELD(int, model, 0x120)
#define SHAPE(model, i) (FIELD(u8 *, model, 0x11c) + (i) * 0x4c)

/* 0x466560: each part's material marked changed */
void THISCALL (shape_markMaterialsChanged)(void *shape)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		int m = FIELD(int, PART(shape, i), 0x44);
		if (m < 0)
			continue;
		tex_markMaterialChanged(MATERIAL_SET(m), m % 512);
	}
}

/* 0x4665c0: each part's material recoloured (two hue, chroma, value triples) */
void THISCALL (shape_recolourMaterials)(void *shape, u32 h1, u32 c1, u32 v1, u32 h2, u32 c2, u32 v2)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		int m = FIELD(int, PART(shape, i), 0x44);
		if (m < 0)
			continue;
		tex_recolourMaterial(MATERIAL_SET(m), m % 512, h1, c1, v1, h2, c2, v2);
	}
}

/* 0x467660: the model tinted, every shape with it */
void THISCALL (shape_setTint)(void *model, u32 h1, u32 c1, u32 v1, u32 h2, u32 c2, u32 v2)
{
	FIELD(u32, model, 0x234) = h1;
	FIELD(u32, model, 0x230) |= 2;
	FIELD(u32, model, 0x240) = h2;
	FIELD(u32, model, 0x238) = c1;
	FIELD(u32, model, 0x23c) = v1;
	FIELD(u32, model, 0x244) = c2;
	FIELD(u32, model, 0x248) = v2;
	for (int i = 0; i < SHAPE_COUNT(model); i++)
		shape_recolourMaterials(SHAPE(model, i), h1, c1, v1, h2, c2, v2);
}

/* 0x4675f0: the tint taken off */
void THISCALL (model_clearTint)(void *model)
{
	FIELD(u32, model, 0x230) &= ~2;
	for (int k = 0; k < 6; k++)
		FIELD(u32, model, 0x234 + k * 4) = 0;
	for (int i = 0; i < SHAPE_COUNT(model); i++)
		shape_markMaterialsChanged(SHAPE(model, i));
}

/* 0x466960: every part's pixels coloured (image_addColour on the part's place in px) */
void (shape_colourPixels)(u8 *px, int mode, const void *shape, const u8 *colour)
{
	for (int i = 0; i < PART_COUNT(shape); i++) {
		const u32 *part = (const u32 *)PART(shape, i);
		image_addColour(px + part[0x12] * 4, mode, part, colour);
	}
}

/* 0x467580: a model's texture folder (+0x130) and flags (+0x230) set; with flag 2 its tint (two HSV colours), else
   its shapes' own colours */
void THISCALL (shape_setTextureDir)(void *model, const char *folder, int flags, u32 h1, u32 c1, u32 v1, u32 h2, u32 c2,
                                    u32 v2)
{
	strcpy((char *)model + 0x130, folder);
	FIELD(int, model, 0x230) = flags;
	if (flags & 2)
		shape_setTint(model, h1, c1, v1, h2, c2, v2);
	else
		model_clearTint(model);
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

/* 0x466910: every part's shading colours (shape_getShadingColorBufferBy) into out at the part's index (+0x48),
   with the factors and the matrix. Returns the part count */
int (shape_shadingColours)(float *out, int first, u8 *shape, void *factors, int matrix)
{
	for (int i = 0; i < FIELD(int, shape, 0x10); i++) {
		u8 *part = FIELD(u8 *, shape, 0x14) + i * 0x80;
		GAME_FN(shape_getShadingColorBufferBy, 0x463b80, void, float *, int, void *, void *, int)(out + FIELD(int, part, 0x48), first, part, factors,
		                                                                matrix);   /* shape_getShadingColorBufferBy */
	}
	return FIELD(int, shape, 0x10);
}
