/* tex_colours.c: colouring textures. A texture manager keeps per slot (0x68-byte records from +0xc0108) two HSV
   tints and their flags; a texture's pixels (RGBA at image) are tinted where its colour mask (colourMask) is strong
   in red (the first tint) or green (the second). A tint replaces the hue and offsets saturation and value.
   Also: a colour added to RGBA pixels, RGB -> HSV, and a texture record set up from its name. */
#include "../game.h"
#include <string.h>


typedef long double X;

#define ZERO k_0f
#define ONE k_1f
#define TURN k_360f       /* 360 degrees */
#define TINY k_1em8f       /* 1e-8 */

/* 0x464a70: a colour c added to the image's pixels (count img[0x13]), each channel at most 255 and the alpha at most
   c's; mode 1, or an image with flag 2, fills them with c instead */
void (image_addColour)(u8 *px, int mode, const u32 *img, const u8 *c)
{
	if (mode == 1 || (img[0] & 2)) {
		for (int i = 0; i < (int)img[0x13]; i++)
			((u32 *)px)[i] = *(const u32 *)c;
		return;
	}
	int r = c[0], g = c[1], b = c[2];
	for (int i = 0; i < (int)img[0x13]; i++, px += 4) {
		int x = px[0] + r, y = px[1] + g, z = px[2] + b;
		px[0] = (u8)(x > 255 ? 255 : x);
		px[1] = (u8)(y > 255 ? 255 : y);
		px[2] = (u8)(z > 255 ? 255 : z);
		if (px[3] > c[3])
			px[3] = c[3];
	}
}

/* equal or unordered (fcomp; test ah, 0x40) */
#define EQ_OR_NAN(a, b) (!((a) < (b)) && !((a) > (b)))

/* 0x46def0: r, g, b -> hue (degrees; FLT_MAX without saturation), saturation, value */
void (tex_rgbToHsv)(float r, float g, float b, float *h, float *s, float *v)
{
	X max = r > g ? (r > b ? r : b) : (g > b ? g : b);
	X min = !(r >= g) ? (!(r >= b) ? r : b) : (!(g >= b) ? g : b);
	{
		volatile X t = max;
		*v = (float)t;
	}
	X sat = max > TINY ? (max - min) / max : (X)ZERO;
	*s = (float)sat;
	if (!(sat >= TINY)) {
		BITS(*h) = 0x7f7fffff;
		return;
	}
	float delta = f32(max - min);
	if (EQ_OR_NAN((X)r, max))
		*h = f32(((X)g - b) / delta);
	else if (EQ_OR_NAN((X)g, max))
		*h = f32(((X)b - r) / delta + k_2f);   /* + 2 */
	else if (EQ_OR_NAN((X)b, max))
		*h = f32(((X)r - g) / delta + k_4f);   /* + 4 */
	X d = (X)*h * k_60f;                         /* * 60 */
	*h = (float)d;
	if (!(d >= ZERO))
		*h = (float)(d + TURN);
}

/* 0x46d950: rgb re-coloured in place: the hue becomes dh (wrapped into 0 .. 360 once; the colour's own hue is worked
   out but not used), saturation and value offset by ds and dv, clamped to 0 .. 1 */
void THISCALL (tex_tintHsv)(float *rgb, float dh, float ds, float dv)
{
	float h, s, v;
	tex_rgbToHsv(BITS(rgb[0]), BITS(rgb[1]), BITS(rgb[2]), &h, &s, &v);
	X d = dh;
	if (!(d >= ZERO))
		h = f32(d + TURN);
	else if (!(d < TURN))
		h = f32(d - TURN);
	else
		BITS(h) = *(volatile u32 *)&dh;
	X t = (X)s + ds;
	s = f32(t);
	if (!(t >= ZERO))
		s = 0;
	else if (s > ONE)
		s = 1.0f;
	t = (X)v + dv;
	v = f32(t);
	if (!(t >= ZERO))
		v = 0;
	else if (v > ONE)
		v = 1.0f;
	color_hsvToRgb(BITS(h), BITS(s), BITS(v), &rgb[0], &rgb[1], &rgb[2]);
}

/* two floats given as their bits equal, or either NaN */
static int same(u32 a, u32 b)
{
	float x, y;
	memcpy(&x, &a, 4);
	memcpy(&y, &b, 4);
	return EQ_OR_NAN(x, y);
}

/* 0x456860: slot m's tints (first h, s, v, then the second's; copied as raw bits) set, the slot marked tinted (flag
   2) and changed (+0x84) when any value differs */
void THISCALL (tex_recolourMaterial)(TextureBank *self, int m, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	TexRecord *rec = &self->records[m];
	u32 flags = rec->flags | 2;
	if (flags == 0 || !same(BITS(rec->colours[0]), h1) || !same(BITS(rec->colours[1]), s1) ||
	    !same(BITS(rec->colours[2]), v1) || !same(BITS(rec->colours[3]), h2) ||
	    !same(BITS(rec->colours[4]), s2) || !same(BITS(rec->colours[5]), v2)) {
		rec->flags = flags;
		BITS(rec->colours[0]) = h1;
		BITS(rec->colours[1]) = s1;
		BITS(rec->colours[2]) = v1;
		BITS(rec->colours[3]) = h2;
		BITS(rec->colours[4]) = s2;
		BITS(rec->colours[5]) = v2;
		rec->changed = 1;
	}
}

/* 0x456470: texture slot i's tints applied where its mask asks (red >= 200: the first, else green >= 200: the second),
   if the slot is tinted. Returns what the original leaves in eax */
int THISCALL (tex_applyTintMask)(TextureBank *tex, int i)
{
	TexRecord *rec = &tex->records[i];
	u8 flags = (*(u8 *)&rec->flags);
	if (!(flags & 2))
		return (int)(((u32)i & 0xffffff00u) | flags);
	for (int y = 0; y < tex->height; y++)
		for (int x = 0; x < tex->width; x++) {
			int k = tex->width * y + x;
			u8 *px = (u8 *)tex + k * 4 + 0x114, *mask = (u8 *)tex + k * 4 + 0x80114;
			if (mask[0] >= 200)
				tex_tintRgba(px, BITS(rec->colours[0]), BITS(rec->colours[1]), BITS(rec->colours[2]));
			else if (mask[1] >= 200)
				tex_tintRgba(px, BITS(rec->colours[3]), BITS(rec->colours[4]), BITS(rec->colours[5]));
		}
	return tex->height;
}

/* 0x454e60: a texture record: its name, slot, flags and two colours (h, s, v each), and its animation from the name's suffix: "_ANI" 1,
   "_ANI0" .. "_ANI3" 1 .. 4 (another digit leaves animation as it was), anything else 0. (The original also makes an
   upper-cased copy of the name it never uses; the suffix test is case-sensitive.) */
void THISCALL (texRecord_init)(u8 *self, const char *name, int slot, int flags, int h1, int s1, int v1, int h2, int s2, int v2)
{
	TexRecord *tr = (TexRecord *)self;
	strcpy((char *)self, name);
	tr->flags = flags;
	tr->slot = slot;
	(*(int *)&tr->colours[0]) = h1;
	(*(int *)&tr->colours[1]) = s1;
	(*(int *)&tr->colours[2]) = v1;
	(*(int *)&tr->colours[3]) = h2;
	(*(int *)&tr->colours[4]) = s2;
	(*(int *)&tr->colours[5]) = v2;
	int n = (int)strlen((char *)self);
	if (n > 4 && !memcmp(self + n - 4, "_ANI", 4)) {
		tr->animation = 1;
		tr->changed = 0;
		return;
	}
	if (n > 5 && !memcmp(self + n - 5, "_ANI", 4)) {
		char c = (char)self[n - 1];
		if (c >= '0' && c <= '3')
			tr->animation = c - '0' + 1;
		tr->changed = 0;
		return;
	}
	tr->animation = 0;
	tr->changed = 0;
}
