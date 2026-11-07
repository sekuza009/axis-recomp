/* trails.c: a shape's bounds, and the bullet trails drawn into the view volume. */
#include "../game.h"
#include <string.h>


typedef long double X;

#define ONE k_1f
#define HALF k_0_5f

static float as_float(u32 bits) { float f; memcpy(&f, &bits, 4); return f; }

/* 0x4666d0: a shape's bounds: each part's box (min box, max box[3]) from its vertices, the box of all of them (which
   always holds the origin), its centre (centre) and the radius around it (radius) holding every vertex. Bounds are
   copied as raw bits. With no parts, centre and radius are 0 */
void THISCALL (shape_computeBounds)(u8 *shape)
{
	Shape *md = (Shape *)shape;
	if (!md->partCount) {
		(*(int *)&md->centre[0]) = 0;
		(*(int *)&md->centre[1]) = 0;
		(*(int *)&md->centre[2]) = 0;
		(*(int *)&md->radius) = 0;
		return;
	}
	u32 min[3] = { 0, 0, (*(u32 *)&k_0f) }, max[3] = { 0, 0, 0 };
	for (int i = 0; i < md->partCount; i++) {
		ShapePart *part = (ShapePart *)(md->parts + i * 0x80);
		for (int k = 0; k < 6; k++)
			(*(int *)&part->box[k]) = 0;
		const u32 *v = ((const u32 *)(part)->vertices);
		for (int n = part->vertexCount; n > 0; n--, v += 3)
			for (int a = 0; a < 3; a++) {
				if (!(part->box[3 + a] >= as_float(v[a])))
					BITS(part->box[3 + a]) = v[a];
				if (part->box[a] > as_float(v[a]))
					BITS(part->box[a]) = v[a];
			}
		for (int a = 0; a < 3; a++) {   /* (the original's order: x max, x min, y max, ...) */
			if (!(as_float(max[a]) >= part->box[3 + a]))
				max[a] = BITS(part->box[3 + a]);
			if (as_float(min[a]) > part->box[a])
				min[a] = BITS(part->box[a]);
		}
	}
	X half = HALF;
	float centre[3];
	for (int a = 0; a < 3; a++)
		md->centre[a] = centre[a] = f32(((X)as_float(min[a]) + as_float(max[a])) * half);
	float r2 = 0;
	for (int i = 0; i < md->partCount; i++) {
		ShapePart *part = (ShapePart *)(md->parts + i * 0x80);
		const float *v = ((const float *)(part)->vertices);
		for (int n = part->vertexCount; n > 0; n--, v += 3) {
			X dz = (X)v[2] - centre[2], dy = (X)v[1] - centre[1], dx = (X)v[0] - centre[0];
			X d2 = dx * dx + dy * dy + dz * dz;
			if (d2 > r2)
				r2 = f32(d2);
		}
	}
	md->radius = (float)x87_fsqrt(r2);
	md->version = 0x71110300;
}

/* 0x47ca70: bullet b's trail: a ring of 20 slots (four points each, 0x30 bytes from the bullet's trail) with each
   slot's time at trailAge. Newest first, each live slot adds four quads joining it to the slot before; the first
   expired one (or one 18 behind) adds an end cap fanning to the previous slot's centre, and the trail ends. Only for
   bullets of weapon type 3 whose box (+0x78) is within the view's distance (cullMargin) of the camera (cameraPos) */
void THISCALL (bullet_drawTrail)(Stage *stage, int b, void *view)
{
	u8 *bullet = (u8 *)(u8 *)&stage->bullets[b];
	Bullet *bu = (Bullet *)bullet;
	X r = stage->cullMargin;
	for (int a = 0; a < 3; a++)
		if ((X)stage->cameraPos[a] - r > bu->prev[a])
			return;
	for (int a = 0; a < 3; a++)
		if (!(r + stage->cameraPos[a] >= bu->prev[a]))
			return;
	if (stage->actorItems[bu->weapon].shotMode != 3)
		return;
	int texture = stage->effectTextures[1];
	u32 uv0[2] = { 0x3e840000, 0x3e840000 }, uv1[2] = { 0x3efc0000, 0x3ebc0000 };   /* (0.258, 0.258), (0.492, 0.367) */
	int n = bu->trailCount;
	if (n <= 0)
		return;
	const float *ring = &bu->trail[0][0][0];
	for (int i = n, j = n + 0x13; ; ) {
		int prev = j % 20, cur = i % 20;
		u32 colour = 0xffffffff;
		float pts[12];
		X age = (X)bu->age - ONE;
		if (age > bu->trailAge[cur] || i <= bu->trailCount - 0x12) {
			const float *p = ring + prev * 12;
			X sx = (X)p[3] + p[0];
			float sy = f32((X)p[4] + p[1]), sz = f32((X)p[5] + p[2]);
			float centre[3] = { (float)(sx * HALF), (float)((X)sy * HALF), (float)((X)sz * HALF) };
			for (int k = 1; k <= 4; k++) {
				memcpy(pts, centre, 12);
				memcpy(pts + 9, centre, 12);
				memcpy(pts + 3, ring + (cur * 4 + k - 1) * 3, 12);
				memcpy(pts + 6, ring + (cur * 4 + k % 4) * 3, 12);
				ViewVolume_addQuad(view, texture, uv0, uv1, &colour, pts, 2, 1);
			}
			return;
		}
		for (int k = 1; k <= 4; k++) {
			memcpy(pts, ring + (prev * 4 + k - 1) * 3, 12);
			memcpy(pts + 3, ring + (cur * 4 + k - 1) * 3, 12);
			memcpy(pts + 6, ring + (cur * 4 + k % 4) * 3, 12);
			memcpy(pts + 9, ring + (prev * 4 + k % 4) * 3, 12);
			ViewVolume_addQuad(view, texture, uv0, uv1, &colour, pts, 2, 1);
		}
		if (--i <= 0)
			return;
		j--;
	}
}
