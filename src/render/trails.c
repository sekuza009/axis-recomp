/* trails.c: a shape's bounds, and the bullet trails drawn into the view volume. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

typedef long double X;

#define ONE GAME_VAR(float, 0x4a9424)
#define HALF GAME_VAR(float, 0x4a942c)

static X fsqrt(X x) { __asm__("fsqrt" : "+t"(x)); return x; }
static float as_float(u32 bits) { float f; memcpy(&f, &bits, 4); return f; }

/* 0x4666d0: a shape's bounds: each part's box (min +0x68, max +0x74) from its vertices, the box of all of them (which
   always holds the origin), its centre (+0x20) and the radius around it (+0x2c) holding every vertex. Bounds are
   copied as raw bits. With no parts, centre and radius are 0 */
void THISCALL (shape_relocate)(u8 *shape)
{
	if (!FIELD(int, shape, 0x10)) {
		FIELD(int, shape, 0x20) = 0;
		FIELD(int, shape, 0x24) = 0;
		FIELD(int, shape, 0x28) = 0;
		FIELD(int, shape, 0x2c) = 0;
		return;
	}
	u32 min[3] = { 0, 0, GAME_VAR(u32, 0x4a93e8) }, max[3] = { 0, 0, 0 };
	for (int i = 0; i < FIELD(int, shape, 0x10); i++) {
		u8 *part = FIELD(u8 *, shape, 0x14) + i * 0x80;
		for (int k = 0; k < 6; k++)
			FIELD(int, part, 0x68 + k * 4) = 0;
		const u32 *v = FIELD(const u32 *, part, 0x50);
		for (int n = FIELD(int, part, 0x4c); n > 0; n--, v += 3)
			for (int a = 0; a < 3; a++) {
				if (!(FIELD(float, part, 0x74 + a * 4) >= as_float(v[a])))
					FIELD(u32, part, 0x74 + a * 4) = v[a];
				if (FIELD(float, part, 0x68 + a * 4) > as_float(v[a]))
					FIELD(u32, part, 0x68 + a * 4) = v[a];
			}
		for (int a = 0; a < 3; a++) {   /* (the original's order: x max, x min, y max, ...) */
			if (!(as_float(max[a]) >= FIELD(float, part, 0x74 + a * 4)))
				max[a] = FIELD(u32, part, 0x74 + a * 4);
			if (as_float(min[a]) > FIELD(float, part, 0x68 + a * 4))
				min[a] = FIELD(u32, part, 0x68 + a * 4);
		}
	}
	X half = HALF;
	float centre[3];
	for (int a = 0; a < 3; a++)
		FIELD(float, shape, 0x20 + a * 4) = centre[a] = f32(((X)as_float(min[a]) + as_float(max[a])) * half);
	float r2 = 0;
	for (int i = 0; i < FIELD(int, shape, 0x10); i++) {
		u8 *part = FIELD(u8 *, shape, 0x14) + i * 0x80;
		const float *v = FIELD(const float *, part, 0x50);
		for (int n = FIELD(int, part, 0x4c); n > 0; n--, v += 3) {
			X dz = (X)v[2] - centre[2], dy = (X)v[1] - centre[1], dx = (X)v[0] - centre[0];
			X d2 = dx * dx + dy * dy + dz * dz;
			if (d2 > r2)
				r2 = f32(d2);
		}
	}
	FIELD(float, shape, 0x2c) = (float)fsqrt(r2);
	FIELD(u32, shape, 0x30) = 0x71110300;
}

/* 0x47ca70: bullet b's trail: a ring of 20 slots (four points each, 0x30 bytes from the bullet's +0xd4) with each
   slot's time at +0x494. Newest first, each live slot adds four quads joining it to the slot before; the first
   expired one (or one 18 behind) adds an end cap fanning to the previous slot's centre, and the trail ends. Only for
   bullets of weapon type 3 whose box (+0x78) is within the view's distance (+0xa08) of the camera (+0x20f3970) */
void THISCALL (hud_47ca70)(Stage *stage, int b, void *view)
{
	u8 *bullet = (u8 *)stage + 0x202ef34 + b * 0x4e8;
	X r = FIELD(float, stage, 0xa08);
	for (int a = 0; a < 3; a++)
		if ((X)FIELD(float, stage, 0x20f3970 + a * 4) - r > FIELD(float, bullet, 0x78 + a * 4))
			return;
	for (int a = 0; a < 3; a++)
		if (!(r + FIELD(float, stage, 0x20f3970 + a * 4) >= FIELD(float, bullet, 0x78 + a * 4)))
			return;
	if (FIELD(int, stage, FIELD(int, bullet, 8) * 0x2e18 + 0x14d48b0) != 3)
		return;
	int texture = FIELD(int, stage, 0x9ccfd8);
	u32 uv0[2] = { 0x3e840000, 0x3e840000 }, uv1[2] = { 0x3efc0000, 0x3ebc0000 };   /* (0.258, 0.258), (0.492, 0.367) */
	int n = FIELD(int, bullet, 0x4e4);
	if (n <= 0)
		return;
	const float *ring = (const float *)(bullet + 0xd4);
	for (int i = n, j = n + 0x13; ; ) {
		int prev = j % 20, cur = i % 20;
		u32 colour = 0xffffffff;
		float pts[12];
		X age = (X)FIELD(float, bullet, 0x70) - ONE;
		if (age > FIELD(float, bullet, 0x494 + cur * 4) || i <= FIELD(int, bullet, 0x4e4) - 0x12) {
			const float *p = ring + prev * 12;
			X sx = (X)p[3] + p[0];
			float sy = f32((X)p[4] + p[1]), sz = f32((X)p[5] + p[2]);
			float centre[3] = { (float)(sx * HALF), (float)((X)sy * HALF), (float)((X)sz * HALF) };
			for (int k = 1; k <= 4; k++) {
				memcpy(pts, centre, 12);
				memcpy(pts + 9, centre, 12);
				memcpy(pts + 3, ring + (cur * 4 + k - 1) * 3, 12);
				memcpy(pts + 6, ring + (cur * 4 + k % 4) * 3, 12);
				hud_4848e0(view, texture, uv0, uv1, &colour, pts, 2, 1);
			}
			return;
		}
		for (int k = 1; k <= 4; k++) {
			memcpy(pts, ring + (prev * 4 + k - 1) * 3, 12);
			memcpy(pts + 3, ring + (cur * 4 + k - 1) * 3, 12);
			memcpy(pts + 6, ring + (cur * 4 + k % 4) * 3, 12);
			memcpy(pts + 9, ring + (prev * 4 + k % 4) * 3, 12);
			hud_4848e0(view, texture, uv0, uv1, &colour, pts, 2, 1);
		}
		if (--i <= 0)
			return;
		j--;
	}
}
