/* tex_colours.c: colouring textures. A texture manager keeps per slot (0x68-byte records from +0xc0108) two HSV
   tints and their flags; a texture's pixels (RGBA at +0x114) are tinted where its colour mask (+0x80114) is strong
   in red (the first tint) or green (the second). A tint replaces the hue and offsets saturation and value.
   Also: a colour added to RGBA pixels, RGB -> HSV, and a texture record set up from its name. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

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
		BITS(s) = 0x3f800000;
	t = (X)v + dv;
	v = f32(t);
	if (!(t >= ZERO))
		v = 0;
	else if (v > ONE)
		BITS(v) = 0x3f800000;
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

/* 0x456860: slot m's tints (first h, c, v, then the second's; copied as raw bits) set, the slot marked tinted (flag
   2) and changed (+0x84) when any value differs */
void THISCALL (tex_recolourMaterial)(u8 *self, int m, u32 h1, u32 c1, u32 v1, u32 h2, u32 c2, u32 v2)
{
	u8 *rec = self + m * 0x68;
	u32 flags = FIELD(u32, rec, 0xc016c) | 2;
	if (flags == 0 || !same(FIELD(u32, rec, 0xc0170), h1) || !same(FIELD(u32, rec, 0xc0174), c1) ||
	    !same(FIELD(u32, rec, 0xc0178), v1) || !same(FIELD(u32, rec, 0xc017c), h2) ||
	    !same(FIELD(u32, rec, 0xc0180), c2) || !same(FIELD(u32, rec, 0xc0184), v2)) {
		FIELD(u32, rec, 0xc016c) = flags;
		FIELD(u32, rec, 0xc0170) = h1;
		FIELD(u32, rec, 0xc0174) = c1;
		FIELD(u32, rec, 0xc0178) = v1;
		FIELD(u32, rec, 0xc017c) = h2;
		FIELD(u32, rec, 0xc0180) = c2;
		FIELD(u32, rec, 0xc0184) = v2;
		FIELD(int, rec, 0xc018c) = 1;
	}
}

/* 0x456470: texture slot i's tints applied where its mask asks (red >= 200: the first, else green >= 200: the second),
   if the slot is tinted. Returns what the original leaves in eax */
int THISCALL (tex_applyTintMask)(u8 *tex, int i)
{
	u8 *rec = tex + i * 0x68;
	u8 flags = FIELD(u8, rec, 0xc016c);
	if (!(flags & 2))
		return (int)(((u32)i & 0xffffff00u) | flags);
	for (int y = 0; y < FIELD(int, tex, 0xc011c); y++)
		for (int x = 0; x < FIELD(int, tex, 0xc0118); x++) {
			int k = FIELD(int, tex, 0xc0118) * y + x;
			u8 *px = tex + k * 4 + 0x114, *mask = tex + k * 4 + 0x80114;
			if (mask[0] >= 200)
				tex_tintRgba(px, FIELD(u32, rec, 0xc0170), FIELD(u32, rec, 0xc0174), FIELD(u32, rec, 0xc0178));
			else if (mask[1] >= 200)
				tex_tintRgba(px, FIELD(u32, rec, 0xc017c), FIELD(u32, rec, 0xc0180), FIELD(u32, rec, 0xc0184));
		}
	return FIELD(int, tex, 0xc011c);
}

/* 0x454e60: a texture record: its name, eight parameters, and its animation from the name's suffix: "_ANI" 1,
   "_ANI0" .. "_ANI3" 1 .. 4 (another digit leaves +0x60 as it was), anything else 0. (The original also makes an
   upper-cased copy of the name it never uses; the suffix test is case-sensitive.) */
void THISCALL (texRecord_init)(u8 *self, const char *name, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9)
{
	strcpy((char *)self, name);
	FIELD(int, self, 0x44) = a3;
	FIELD(int, self, 0x40) = a2;
	FIELD(int, self, 0x48) = a4;
	FIELD(int, self, 0x4c) = a5;
	FIELD(int, self, 0x50) = a6;
	FIELD(int, self, 0x54) = a7;
	FIELD(int, self, 0x58) = a8;
	FIELD(int, self, 0x5c) = a9;
	int n = (int)strlen((char *)self);
	if (n > 4 && !memcmp(self + n - 4, "_ANI", 4)) {
		FIELD(int, self, 0x60) = 1;
		FIELD(int, self, 0x64) = 0;
		return;
	}
	if (n > 5 && !memcmp(self + n - 5, "_ANI", 4)) {
		char c = (char)self[n - 1];
		if (c >= '0' && c <= '3')
			FIELD(int, self, 0x60) = c - '0' + 1;
		FIELD(int, self, 0x64) = 0;
		return;
	}
	FIELD(int, self, 0x60) = 0;
	FIELD(int, self, 0x64) = 0;
}
