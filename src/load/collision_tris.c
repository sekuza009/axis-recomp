/* collision_tris.c: the collision space's triangles. A triangle record (0xa0 bytes) holds its id, its three corners
   (+4), its three edges normalised (+0x28), its face plane (normal +0x4c, distance +0x58), three edge planes (+0x5c,
   16 bytes each: the normal pointing inwards, the distance) and five values of the map's (+0x8c). The arithmetic is
   the original's: extended precision, rounded where it stores a float, and float operands taken straight from
   memory (fld_m / fmul_m, so a signalling NaN behaves as there). */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

typedef long double X;

static X fsqrt(X x) { __asm__("fsqrt" : "+t"(x)); return x; }

/* a * *m, the product not folded into anything around it */
static X mul(X a, const float *m) { return fmul_m(a, m); }
/* *src copied through the FPU (a signalling NaN comes out quiet) */
static void copy_through_fpu(float *dst, const float *src) { *dst = (float)fld_m(src); }

/* 0x47db60: triangle (v0, v1, v2) set up in the record, with its id and the map's five values; returns d */
int THISCALL (load_47db60)(u8 *self, int id, const float *v0, const float *v1, const float *v2, int a, int b, int c, int d,
                           int e)
{
	float *f = (float *)self;
	load_47db50(self);
	FIELD(int, self, 0) = id;
	memcpy(f + 1, v0, 12);
	memcpy(f + 4, v1, 12);
	memcpy(f + 7, v2, 12);
	for (int i = 0; i < 3; i++) {   /* edge i: corner i + 1 - corner i */
		int j = (i + 1) % 3;
		float *edge = f + 10 + i * 3;
		for (int k = 0; k < 3; k++)
			edge[k] = (float)fsub_m(fld_m(&f[1 + j * 3 + k]), &f[1 + i * 3 + k]);
		Vec3_normalize(edge);
	}
	/* the face normal: (-edge 0) x edge 1 */
	X nx = -fld_m(&f[10]), ny = -fld_m(&f[11]), nz = -fld_m(&f[12]);
	float n[3];
	n[0] = (float)(mul(nz, &f[14]) - mul(ny, &f[15]));
	n[1] = (float)(mul(nx, &f[15]) - mul(nz, &f[13]));
	n[2] = (float)(mul(ny, &f[13]) - mul(nx, &f[14]));
	Vec3_normalize(n);
	X dist = mul(fld_m(&n[1]), &f[2]) + mul(fld_m(&n[0]), &f[1]);
	dist = dist + mul(fld_m(&n[2]), &f[3]);
	copy_through_fpu(f + 0x13, &n[0]);
	copy_through_fpu(f + 0x14, &n[1]);
	copy_through_fpu(f + 0x15, &n[2]);
	f[0x16] = (float)dist;
	for (int k = 0; k < 3; k++) {   /* edge plane k: normal x edge k, through corner k */
		const float *edge = f + 10 + k * 3, *corner = f + 1 + k * 3;
		float p[3];
		p[0] = (float)(mul(fld_m(&n[2]), &edge[1]) - mul(fld_m(&n[1]), &edge[2]));
		p[1] = (float)(mul(fld_m(&n[0]), &edge[2]) - mul(fld_m(&n[2]), &edge[0]));
		p[2] = (float)(mul(fld_m(&n[1]), &edge[0]) - mul(fld_m(&n[0]), &edge[1]));
		Vec3_normalize(p);
		X pd = mul(fld_m(&p[2]), &corner[2]) + mul(fld_m(&p[1]), &corner[1]);
		pd = pd + mul(fld_m(&p[0]), &corner[0]);
		float *plane = f + 0x17 + k * 4;
		copy_through_fpu(plane, &p[0]);
		copy_through_fpu(plane + 1, &p[1]);
		copy_through_fpu(plane + 2, &p[2]);
		plane[3] = (float)pd;
	}
	FIELD(int, self, 0x8c) = a;
	FIELD(int, self, 0x90) = b;
	FIELD(int, self, 0x94) = c;
	FIELD(int, self, 0x98) = d;
	FIELD(int, self, 0x9c) = e;
	return d;
}

/* 0x47fb80: the segment p0 -> p1 against the triangle: crossing its face plane at a point inside its three edge
   planes. On a hit: the point in *hit, its distance to p1 in *dist, returns 1 */
int THISCALL (space_tracePlanes_47fb80)(const u8 *self, const float *p0, const float *p1, float *hit, float *dist)
{
	const float *n = (const float *)(self + 0x4c);
	X zero = GAME_VAR(float, 0x4a93e8);
	X d0 = (X)n[1] * p0[1] + (X)p0[2] * n[2] + (X)n[0] * p0[0] - n[3];
	X d1 = (X)p1[2] * n[2] + (X)n[0] * p1[0] + (X)n[1] * p1[1] - n[3];
	if (d1 * d0 >= zero)   /* both on one side (or touching): no crossing */
		return 0;
	X dx = (X)p1[0] - p0[0];
	float dy = f32((X)p1[1] - p0[1]), dz = f32((X)p1[2] - p0[2]);
	float t = f32(-(d0 / (dx * n[0] + (X)dy * n[1] + (X)dz * n[2])));
	float ey = f32((X)dy * t), ez = f32((X)dz * t);
	float h[3] = { (float)(dx * t + p0[0]), (float)((X)ey + p0[1]), (float)((X)ez + p0[2]) };
	memcpy(hit, h, 12);
	for (int k = 0; k < 3; k++) {
		const float *e = (const float *)(self + 0x5c + k * 0x10);
		if ((X)e[0] * hit[0] + (X)e[1] * hit[1] + (X)e[2] * hit[2] - e[3] >= zero)
			return 0;
	}
	X a = (X)p1[0] - hit[0], b = (X)p1[1] - hit[1], c = (X)p1[2] - hit[2];
	*dist = (float)fsqrt(c * c + b * b + a * a);
	return 1;
}

/* ---- 0x47fce0: does the triangle touch the box from P - r to S + r? (r, P and S as the collision code passes them).
   1. every corner of the triangle outside one face of the box: no; all inside: yes;
   2. all eight box corners on one side of the face plane: no;
   3. an edge of the triangle crossing a face of the box (its other two coordinates within it): yes;
   4. a box corner inside all three edge planes: yes; else no.
   The compares are the original's (a NaN fails every "greater"), the operands from memory as there ---- */

/* the triangle's edges crossing the box face at coordinate *at of axis a: the crossing's coordinates on axes b
   (unrounded) and c (from the parameter rounded to a float, as the original stores it) within (lob, hib) and
   (loc, hic) */
static int edges_cross(const float *T, const float *at, int a, int b, int c, const float *lob, const float *hib,
                       const float *loc, const float *hic)
{
	for (int i = 0; i < 3; i++) {
		const float *v = T + 1 + i * 3, *e = T + 10 + i * 3;
		X t = fdiv_m(fsub_m(fld_m(at), &v[a]), &e[a]);
		float tf = f32(t);
		X y = fadd_m(fmul_m(t, &e[b]), &v[b]);
		if (!(y > *lob))
			continue;
		if (y >= *hib)
			continue;
		X z = fadd_m(fmul_m(fld_m(&tf), &e[c]), &v[c]);
		if (!(z > *loc))
			continue;
		if (!(z >= *hic))
			return 1;
	}
	return 0;
}

int THISCALL (load_47fce0)(const float *T, const float *P, const float *S, float r)
{
	float lo[3];
	for (int a = 0; a < 3; a++)
		lo[a] = f32(fsub_m(fld_m(&P[a]), &r));
	unsigned all = 0x111111, any = 0;
	for (int i = 0; i < 3; i++) {
		const float *v = T + 1 + i * 3;
		unsigned code = 0;
		for (int a = 0; a < 3; a++) {
			if (!(v[a] > lo[a]))
				code |= 1u << (a * 8);
			else if (!(fadd_m(fld_m(&r), &S[a]) > v[a]))
				code |= 0x10u << (a * 8);
		}
		all &= code;
		any |= code;
	}
	if (all & 0x111111)
		return 0;
	if (!any)
		return 1;
	float hi[3];
	for (int a = 0; a < 3; a++)
		hi[a] = f32(fadd_m(fld_m(&r), &S[a]));
	const float corner[8][3] = { { lo[0], lo[1], lo[2] }, { hi[0], lo[1], lo[2] }, { lo[0], lo[1], hi[2] },
	                             { hi[0], lo[1], hi[2] }, { lo[0], hi[1], lo[2] }, { hi[0], hi[1], lo[2] },
	                             { lo[0], hi[1], hi[2] }, { hi[0], hi[1], hi[2] } };
	X zero = GAME_VAR(float, 0x4a93e8);
	int side = -1;
	for (int k = 0; ; k++) {   /* the corners against the face plane */
		X d = fmul_m(fld_m(&corner[k][2]), &T[0x15]) + fmul_m(fld_m(&corner[k][0]), &T[0x13]);
		d = d + fmul_m(fld_m(&corner[k][1]), &T[0x14]);
		d = fsub_m(d, &T[0x16]);
		if (d > zero) {
			if (side == 1)
				break;
			if (side < 0)
				side = 0;
		} else {
			if (side == 0)
				break;
			if (side < 0)
				side = 1;
		}
		if (k >= 7)
			return 0;
	}
	if (edges_cross(T, &lo[0], 0, 1, 2, &lo[1], &hi[1], &lo[2], &hi[2]) ||
	    edges_cross(T, &hi[0], 0, 1, 2, &lo[1], &hi[1], &lo[2], &hi[2]) ||
	    edges_cross(T, &lo[1], 1, 2, 0, &lo[2], &hi[2], &lo[0], &hi[0]) ||
	    edges_cross(T, &hi[1], 1, 2, 0, &lo[2], &hi[2], &lo[0], &hi[0]) ||
	    edges_cross(T, &lo[2], 2, 0, 1, &lo[0], &hi[0], &lo[1], &hi[1]) ||
	    edges_cross(T, &hi[2], 2, 0, 1, &lo[0], &hi[0], &lo[1], &hi[1]))
		return 1;
	for (int k = 0; k < 8; k++) {   /* a corner inside the three edge planes */
		const float *c = corner[k];
		X d = fmul_m(fld_m(&T[0x19]), &c[2]) + fmul_m(fld_m(&c[1]), &T[0x18]);
		d = d + fmul_m(fld_m(&T[0x17]), &c[0]);
		d = fsub_m(d, &T[0x1a]);
		if (d > zero)
			continue;
		d = fmul_m(fld_m(&T[0x1c]), &c[1]) + fmul_m(fld_m(&T[0x1d]), &c[2]);
		d = d + fmul_m(fld_m(&T[0x1b]), &c[0]);
		d = fsub_m(d, &T[0x1e]);
		if (d > zero)
			continue;
		d = fmul_m(fld_m(&T[0x20]), &c[1]) + fmul_m(fld_m(&T[0x21]), &c[2]);
		d = d + fmul_m(fld_m(&T[0x1f]), &c[0]);
		d = fsub_m(d, &T[0x22]);
		if (!(d > zero))
			return 1;
	}
	return 0;
}

/* the world box's clamp of one coordinate of the moved position (a NaN goes to the low side, as fcom has it): 1 when
   it was moved */
static int clamp_to(float *v, const float *low, const float *high)
{
	if (!(*v >= *low)) {
		*(u32 *)v = *(const u32 *)low;
		return 1;
	}
	if (*v > *high) {
		*(u32 *)v = *(const u32 *)high;
		return 1;
	}
	return 0;
}

/* 0x471400 (thiscall on the stage): an actor's move (radius r from pos along vel) for this frame. outPos is pos + vel
   kept inside the world box (+0x9ef91c low, +0x9ef928 high); when it had to be, the move is cut to match. The map
   objects (+0x13c9b24 of them, 0x2cc bytes from +0x131ae48: active, solid +0x28c, triangles +0x288's +8, a box
   +0x278, the world-to-model matrix +0x130) with pos inside their box widened by r + the move's length become the
   sub-models (+0x9ca0f4: triangles and the two matrices +0x1f0 / +0x230), and space_testSphere runs on the stage's
   grid (+0xa10) with them. Returns what it finds */
int THISCALL (collision_moveActor)(u8 *stage, float r, const float *pos, const float *vel, u32 step, u32 k, float *outPos,
                                   u32 outVel, u32 outDist, u32 outPlane, u32 axis)
{
	float to[3], d[3];
	to[0] = f32(fadd_m(fld_m(&pos[0]), &vel[0]));
	to[1] = f32(fadd_m(fld_m(&vel[1]), &pos[1]));
	to[2] = f32(fadd_m(fld_m(&vel[2]), &pos[2]));
	memcpy(outPos, to, sizeof to);
	const float *low = (const float *)(stage + 0x9ef91c), *high = (const float *)(stage + 0x9ef928);
	int clamped = clamp_to(&outPos[0], &low[0], &high[0]);
	clamped |= clamp_to(&outPos[1], &low[1], &high[1]);
	clamped |= clamp_to(&outPos[2], &low[2], &high[2]);
	if (clamped)
		for (int c = 0; c < 3; c++)
			d[c] = f32(fsub_m(fld_m(&outPos[c]), &pos[c]));
	else
		memcpy(d, vel, sizeof d);
	int count = 0;
	u32 *sub = (u32 *)(stage + 0x9ca0f4);
	X reach = 0;
	for (int i = 0; i < FIELD(int, stage, 0x13c9b24); i++) {
		if (i == 0) {
			X y = fld_m(&d[1]), z = fld_m(&d[2]);
			reach = fadd_m(fsqrt(z * z + y * y + mul(fld_m(&d[0]), &d[0])), &r);
		}
		u8 *obj = stage + 0x131ae48 + i * 0x2cc;
		if (FIELD(int, obj, 0) != 1 || FIELD(int, obj, 0x28c) != 1)
			continue;
		u32 tris = FIELD(u32, FIELD(u8 *, obj, 0x288), 8);
		if (!tris)
			continue;
		const float *m = (const float *)(obj + 0x130);
		float at[3];
		at[0] = f32(fadd_m(mul(fld_m(&m[8]), &pos[2]) + mul(fld_m(&m[4]), &pos[1]) + mul(fld_m(&m[0]), &pos[0]), &m[12]));
		at[1] = f32(fadd_m(mul(fld_m(&m[1]), &pos[0]) + mul(fld_m(&m[9]), &pos[2]) + mul(fld_m(&m[5]), &pos[1]), &m[13]));
		at[2] = f32(fadd_m(mul(fld_m(&m[2]), &pos[0]) + mul(fld_m(&m[10]), &pos[2]) + mul(fld_m(&m[6]), &pos[1]), &m[14]));
		const float *box = (const float *)(FIELD(u8 *, obj, 0x278) + 0x34);
		int inside = 1;
		for (int c = 0; c < 3 && inside; c++)
			inside = !(fld_m(&box[c]) - reach >= at[c]);
		for (int c = 0; c < 3 && inside; c++)
			inside = fadd_m(reach, &box[3 + c]) > at[c];
		if (!inside)
			continue;
		sub[0] = tris;
		sub[1] = (u32)(obj + 0x1f0);
		sub[2] = (u32)(obj + 0x230);
		sub += 3;
		count++;
	}
	return space_testSphere(stage + 0xa10, *(u32 *)&r, pos, d, step, k, (u32)outPos, outVel, outDist, outPlane, axis,
	                        stage + 0x9ca0f4, count);
}
