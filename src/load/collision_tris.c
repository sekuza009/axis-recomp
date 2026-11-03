/* collision_tris.c: the collision space's triangles. A triangle record (0xa0 bytes) holds its id, its three corners
   (+4), its three edges normalised (+0x28), its face plane (normal +0x4c, distance +0x58), three edge planes (+0x5c,
   16 bytes each: the normal pointing inwards, the distance) and five values of the map's (+0x8c). The arithmetic is
   the original's: extended precision, rounded where it stores a float, and float operands taken straight from
   memory (fld_m / fmul_m, so a signalling NaN behaves as there). */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

typedef long double X;


/* a * *m, the product not folded into anything around it */
static X mul(X a, const float *m) { return fmul_m(a, m); }
/* *src copied through the FPU (a signalling NaN comes out quiet) */
static void copy_through_fpu(float *dst, const float *src) { *dst = (float)fld_m(src); }

/* 0x47db60: triangle (v0, v1, v2) set up in the record, with its id and the map's five values; returns d */
int THISCALL (collisionTri_setup)(u8 *self, int id, const float *v0, const float *v1, const float *v2, int a, int b, int c, int d,
                           int e)
{
	float *f = (float *)self;
	collisionPlane_clear(self);
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
int THISCALL (collisionTri_traceSegment)(const u8 *self, const float *p0, const float *p1, float *hit, float *dist)
{
	const float *n = (const float *)(self + 0x4c);
	X zero = k_0f;
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
	*dist = (float)x87_fsqrt(c * c + b * b + a * a);
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

int THISCALL (space_itemMeetsBox)(const float *T, const float *P, const float *S, float r)
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
	X zero = k_0f;
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
	Stage *st = (Stage *)stage;
	float to[3], d[3];
	to[0] = f32(fadd_m(fld_m(&pos[0]), &vel[0]));
	to[1] = f32(fadd_m(fld_m(&vel[1]), &pos[1]));
	to[2] = f32(fadd_m(fld_m(&vel[2]), &pos[2]));
	memcpy(outPos, to, sizeof to);
	const float *low = ((Stage *)stage)->worldLow, *high = ((Stage *)stage)->worldHigh;
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
	for (int i = 0; i < st->objectCount; i++) {
		if (i == 0) {
			X y = fld_m(&d[1]), z = fld_m(&d[2]);
			reach = fadd_m(x87_fsqrt(z * z + y * y + mul(fld_m(&d[0]), &d[0])), &r);
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

/* ---- 0x47dd90: a moving sphere against one triangle ---- */
#define TINY ((const float *)ADDR(k_1em8f))    /* 1e-8 */
#define ONE ((const float *)ADDR(k_1f))
#define MINUS_ONE ((const float *)ADDR(k_m1f))
#define REST ((const float *)ADDR(g_vecZero))    /* the axis a response falls back to */

static void vset(float *o, float x, float y, float z) { o[0] = x; o[1] = y; o[2] = z; }
/* a x b, each component's products in the original's order */
static void cross3(float *o, const float *a, const float *b)
{
	vset(o, f32(mul(fld_m(&a[1]), &b[2]) - mul(fld_m(&a[2]), &b[1])), f32(mul(fld_m(&a[2]), &b[0]) - mul(fld_m(&a[0]), &b[2])),
	     f32(mul(fld_m(&a[0]), &b[1]) - mul(fld_m(&a[1]), &b[0])));
}
/* Vec3_dot (0x4802b0): summed z, y, x; and summed x, y, z */
static X dot_zyx(const float *a, const float *b) { return mul(fld_m(&b[2]), &a[2]) + mul(fld_m(&b[1]), &a[1]) + mul(fld_m(&b[0]), &a[0]); }
static X dot_xyz(const float *a, const float *b) { return mul(fld_m(&a[0]), &b[0]) + mul(fld_m(&a[1]), &b[1]) + mul(fld_m(&a[2]), &b[2]); }
static X absx(X x) { return !(x >= 0) ? -x : x; }
/* |v| under 1e-8 (or NaN), its sign taken from x and its size from the float f */
static int small(X x, float f) { return !((!(x >= 0) ? -fld_m(&f) : fld_m(&f)) >= *TINY); }
/* a - b rounded, componentwise */
static void vsub(float *o, const float *a, const float *b)
{
	vset(o, f32(fsub_m(fld_m(&a[0]), &b[0])), f32(fsub_m(fld_m(&a[1]), &b[1])), f32(fsub_m(fld_m(&a[2]), &b[2])));
}
static X len2(const float *u) { return mul(fld_m(&u[0]), &u[0]) + mul(fld_m(&u[1]), &u[1]) + mul(fld_m(&u[2]), &u[2]); }

/* of the two roots the one nearer 0 (the rounded t1 when the magnitudes tie or are NaN), held to -1 .. 1 */
static X nearer_root(float t1, X t2)
{
	X t = !(absx(fld_m(&t1)) >= absx(t2)) ? fld_m(&t1) : t2;
	if (t > *ONE)
		return fld_m(ONE);
	if (!(t >= *MINUS_ONE))
		return fld_m(MINUS_ONE);
	return t;
}

/* the sphere's centre at the contact: pos + vel x t */
static void contact_centre(float *c, const float *p, const float *v, X t)
{
	float s[3];
	vset(s, f32(fmul_m(t, &v[0])), f32(fmul_m(t, &v[1])), f32(fmul_m(t, &v[2])));
	vset(c, f32(fadd_m(fld_m(&s[0]), &p[0])), f32(fadd_m(fld_m(&p[1]), &s[1])), f32(fadd_m(fld_m(&p[2]), &s[2])));
}

/* the response along y (normalised by the game's Vec3_normalize; 0 when that is too short): y scaled by its dot
   with the contact vector d, then outVel = y + (y - d) x k. Some of the original's copies keep y.z x dot unrounded
   for the subtraction (keep_z) */
static int slide_inline(float *outVel, float *y, const float *d, float k, int keep_z)
{
	if (!(Vec3_normalize(y) >= *TINY))
		return 0;
	X dd = mul(fld_m(&y[0]), &d[0]) + mul(fld_m(&d[2]), &y[2]) + mul(fld_m(&d[1]), &y[1]);
	y[0] = f32(fmul_m(dd, &y[0]));
	y[1] = f32(fmul_m(dd, &y[1]));
	X z = fmul_m(dd, &y[2]);
	y[2] = (float)z;
	float zv[3], q[3];
	vset(zv, f32(fsub_m(fld_m(&y[0]), &d[0])), f32(fsub_m(fld_m(&y[1]), &d[1])),
	     f32(keep_z ? fsub_m(z, &d[2]) : fsub_m(fld_m(&y[2]), &d[2])));
	vset(q, f32(fmul_m(fld_m(&zv[0]), &k)), f32(fmul_m(fld_m(&zv[1]), &k)), f32(fmul_m(fld_m(&zv[2]), &k)));
	vset(outVel, f32(fadd_m(fld_m(&q[0]), &y[0])), f32(fadd_m(fld_m(&q[1]), &y[1])), f32(fadd_m(fld_m(&q[2]), &y[2])));
	return 1;
}

/* the same through the vector helpers (the face's copy): the dot rounded to a float first */
static int slide_helpers(float *outVel, float *y, const float *d, float k)
{
	if (!(Vec3_normalize(y) >= *TINY))
		return 0;
	float s = (float)dot_zyx(d, y), zv[3], q[3];
	for (int i = 0; i < 3; i++)
		y[i] = f32(fmul_m(fld_m(&s), &y[i]));
	vsub(zv, y, d);
	for (int i = 0; i < 3; i++)
		q[i] = f32(fmul_m(fld_m(&k), &zv[i]));
	vset(outVel, f32(fadd_m(fld_m(&q[0]), &y[0])), f32(fadd_m(fld_m(&q[1]), &y[1])), f32(fadd_m(fld_m(&q[2]), &y[2])));
	return 1;
}

/* the response and plane of a corner or edge contact, w the contact normal (the centre less the feature). Without an
   axis the response is along (v x w) x w and the plane's normal is w; with one, along w x axis, the normal w x that.
   The edge's copy with an axis rounds y.z x dot (keep_z 0) and writes the plane through the helpers (no FPU) */
static void respond(float *w, const float *v, const float *d, float k, const float *axis, float *outVel, float *plane,
                    const float *o, int corner)
{
	float x[3], y[3];
	if (!axis) {
		cross3(x, v, w);
		cross3(y, x, w);
		if (!slide_inline(outVel, y, d, k, 1))
			memcpy(outVel, REST, 12);
	} else {
		cross3(y, w, axis);
		if (!slide_inline(outVel, y, d, k, corner))
			memcpy(outVel, REST, 12);
		cross3(w, w, y);
		if (!corner) {
			float dn = (float)dot_zyx(w, o);
			memcpy(plane, w, 12);
			plane[3] = dn;
			return;
		}
	}
	X dn = mul(fld_m(&w[0]), &o[0]) + mul(fld_m(&w[1]), &o[1]) + mul(fld_m(&w[2]), &o[2]);
	for (int i = 0; i < 3; i++)
		plane[i] = (float)fld_m(&w[i]);
	plane[3] = (float)dn;
}

/* 0x47dd90 (thiscall on a triangle record, see the top of the file): the sphere of radius r moving from pos by vel
   against the triangle. Misses (0): moving away from the face (vel . n > 1e-8), or pos + vel (outPos) r or more from
   the face's plane or outside an edge plane by r. With no motion it is pushed back along -n by r. Then by where
   pos + vel lies: outside an edge plane (the first), the nearest of that edge's start corner, its end corner or the
   edge itself; else the face. Each solves for the fraction t (-1 .. 1) of the move that brings the sphere into
   touch, puts the centre there (outPos), its distance from pos + vel (outDist), the response (outVel: the remaining
   move slid along the contact, scaled by k, about axis when there is one) and the contact plane (normal and
   distance). Returns 1 on a contact */
int THISCALL (collision_sphereVsUnit)(u8 *tri, float r, const float *pos, const float *vel, float k, float *outPos,
                                      float *outVel, float *outDist, float *plane, const float *axis)
{
	const float *n = (const float *)(tri + 0x4c), *dist = (const float *)(tri + 0x58);
	float *o = outPos, edge[3], p[3], v[3], c[3], d[3], w[3], u[3], pv[3], r2, a;
	for (int i = 0; i < 3; i++)
		o[i] = f32(fadd_m(fld_m(&pos[i]), &vel[i]));
	if (mul(fld_m(&vel[2]), &n[2]) + mul(fld_m(&vel[1]), &n[1]) + mul(fld_m(&n[0]), &vel[0]) > *TINY)
		return 0;
	if (absx(fsub_m(mul(fld_m(&o[2]), &n[2]) + mul(fld_m(&o[1]), &n[1]) + mul(fld_m(&o[0]), &n[0]), dist)) >= r)
		return 0;
	for (int i = 0; i < 3; i++) {
		const float *e = (const float *)(tri + 0x5c + i * 16);
		X s = fsub_m(mul(fld_m(&e[0]), &o[0]) + mul(fld_m(&e[1]), &o[1]) + mul(fld_m(&e[2]), &o[2]), &e[3]);
		edge[i] = (float)s;
		if (s >= r)
			return 0;
	}
	memcpy(p, pos, 12);
	memcpy(v, vel, 12);
	if (small(fld_m(&v[0]), v[0]) && small(fld_m(&v[1]), v[1]) && small(fld_m(&v[2]), v[2])) {   /* no motion */
		X nx = -fld_m(&n[0]);
		v[1] = f32(-fld_m(&n[1]));
		v[2] = f32(-fld_m(&n[2]));
		vset(o, f32(fadd_m(nx, &pos[0])), f32(fadd_m(fld_m(&v[1]), &pos[1])), f32(fadd_m(fld_m(&v[2]), &pos[2])));
		v[0] = f32(fmul_m(nx, &r));
		v[1] = f32(fmul_m(fld_m(&v[1]), &r));
		v[2] = f32(fmul_m(fld_m(&v[2]), &r));
	}
	int i = 0;
	while (i < 3 && !(edge[i] > 0))
		i++;
	if (i == 3) {   /* the face: the plane's equation solved along the move */
		float nn[3], y[3], x[3], t;
		memcpy(nn, n, 12);
		a = f32(fsub_m(dot_zyx(nn, p), dist));
		X dv = dot_zyx(nn, v);
		float dvf = (float)dv;
		if (small(dv, dvf))
			return 0;
		X t1 = -(fadd_m(fld_m(&a), &r) / fld_m(&dvf));
		t = f32(-(fsub_m(fld_m(&a), &r) / fld_m(&dvf)));
		if (!(absx(t1) >= absx(fld_m(&t))))
			t = (float)t1;
		if (t > *ONE)
			FIELD(u32, &t, 0) = 0x3f800000;
		else if (!(t >= *MINUS_ONE))
			FIELD(u32, &t, 0) = 0xbf800000;
		for (int j = 0; j < 3; j++)
			u[j] = f32(fmul_m(fld_m(&t), &v[j]));
		vset(c, f32(fadd_m(fld_m(&u[0]), &p[0])), f32(fadd_m(fld_m(&u[1]), &p[1])), f32(fadd_m(fld_m(&u[2]), &p[2])));
		vsub(d, o, c);
		*outDist = (float)x87_fsqrt(len2(d));
		memcpy(o, c, 12);
		if (!(fsub_m(dot_zyx(nn, o), dist) >= 0))
			for (int j = 0; j < 3; j++)
				nn[j] = (float)-fld_m(&nn[j]);
		if (!axis) {
			cross3(x, v, nn);
			cross3(y, x, nn);
			if (!slide_helpers(outVel, y, d, k))
				memcpy(outVel, REST, 12);
		} else {
			cross3(y, nn, axis);
			if (!slide_helpers(outVel, y, d, k))
				memcpy(outVel, REST, 12);
			cross3(nn, nn, y);
		}
		float dn = (float)dot_zyx(nn, o);
		memcpy(plane, nn, 12);
		plane[3] = dn;
		return 1;
	}
	int j = (i + 1) % 3, corner = 1;
	const float *vi = (const float *)(tri + 4 + i * 12), *vj = (const float *)(tri + 4 + j * 12);
	const float *e = (const float *)(tri + 0x28 + i * 12);
	vsub(u, o, vi);
	if (!(dot_zyx(e, u) >= 0)) {   /* before the edge's start: that corner */
		r2 = f32(fmul_m(fld_m(&r), &r));
		vsub(u, o, vi);
		if (!(len2(u) < r2))
			return 0;
		vsub(pv, p, vi);
		X aa = len2(v);
		a = (float)aa;
		if (small(aa, a))
			return 0;
		X b = dot_xyz(pv, v);
		X disc = b * b - fmul_m(fsub_m(len2(pv), &r2), &a);
		if (!(disc >= *TINY))
			return 0;
		X s = x87_fsqrt(disc);
		contact_centre(c, p, v, nearer_root(f32(fdiv_m(s - b, &a)), fdiv_m(-b - s, &a)));
		vsub(d, o, c);
	} else {
		r2 = f32(fmul_m(fld_m(&r), &r));
		vsub(u, o, vj);
		if (dot_zyx(e, u) > 0) {   /* past the edge's end: the next corner */
			vsub(u, o, vj);
			if (!(len2(u) < r2))
				return 0;
			vsub(pv, p, vj);
			X aa = len2(v), b = dot_xyz(pv, v);
			X disc = b * b - fsub_m(len2(pv), &r2) * aa;
			if (!(disc >= *TINY))
				return 0;
			X s = x87_fsqrt(disc);
			contact_centre(c, p, v, nearer_root((float)((s - b) / aa), (-b - s) / aa));
			vi = vj;
		} else {   /* along the edge: the sphere against the edge's line */
			vsub(u, o, vi);
			X de = dot_zyx(e, u);
			if (!(len2(u) - de * de < r2))
				return 0;
			vsub(pv, p, vi);
			X ve = mul(fld_m(&v[1]), &e[1]) + mul(fld_m(&v[2]), &e[2]) + mul(fld_m(&v[0]), &e[0]);
			float pe = (float)dot_zyx(e, pv);
			X aa = len2(v) - ve * ve;
			a = (float)aa;
			if (small(aa, a))
				return 0;
			X b = dot_xyz(pv, v) - fmul_m(ve, &pe);
			X disc = b * b - fmul_m(fsub_m(len2(pv) - mul(fld_m(&pe), &pe), &r2), &a);
			if (!(disc >= *TINY))
				return 0;
			X s = x87_fsqrt(disc);
			contact_centre(c, p, v, nearer_root(f32(fdiv_m(s - b, &a)), fdiv_m(-b - s, &a)));
			corner = 0;
		}
		vsub(d, o, c);
		if (!(dot_xyz(d, v) > 0))   /* the contact behind the move: the rest axis */
			memcpy(d, REST, 12);
	}
	*outDist = (float)x87_fsqrt(mul(fld_m(&d[1]), &d[1]) + mul(fld_m(&d[2]), &d[2]) + mul(fld_m(&d[0]), &d[0]));
	memcpy(o, c, 12);
	vsub(w, o, vi);
	if (!corner) {   /* the normal from the edge's line: e x ((centre - start) x e) */
		float t[3];
		cross3(t, w, e);
		cross3(w, e, t);
	}
	respond(w, v, d, k, axis, outVel, plane, o, corner);
	return 1;
}

/* an affine point (with the translation) or a direction through a 4x4 matrix (columns), each row summed z, y, x */
static float row_point(const float *m, const float *p, int i)
{
	return f32(fadd_m(mul(fld_m(&p[2]), &m[8 + i]) + mul(fld_m(&p[1]), &m[4 + i]) + mul(fld_m(&p[0]), &m[i]), &m[12 + i]));
}
static float row_dir(const float *m, const float *p, int i)
{
	return f32(mul(fld_m(&p[2]), &m[8 + i]) + mul(fld_m(&p[1]), &m[4 + i]) + mul(fld_m(&p[0]), &m[i]));
}

/* 0x4804b0 (thiscall on a space object): the sphere of radius r moving from pos by vel against the triangles of the
   object's list (+0x18: nodes {record, ., ., next +0xc}; records whose first byte has bit 0 set are skipped there)
   and of nsubs sub-models (subs: {list, model-to-world matrix, world-to-model matrix}; pos and vel are taken into
   the model, the contact back out; an empty sub-model list crashes the original, as it would here). The farthest
   contact along the move wins (collision_sphereVsUnit's outDist), the record that gave it is skipped next time;
   then the move slides on: up to 6 passes, ending when a pass's distance is under r / 10, or (contact, outVel the
   0xa0e7e8 axis, outDist 0) when the response turns back against vel. outPos starts as pos + vel. Returns 1 when
   anything was hit */
int THISCALL (space_collideUnit)(u8 *self, float r, const float *pos, const float *vel, u32 k, float *outPos,
                                 float *outVel, float *outDist, float *outPlane, u32 axis, const u32 *subs, int nsubs)
{
	float at[3], move[3], from[3], step[3], hitPos[3], hitVel[3], plane[4], dist, best;
	for (int c = 0; c < 3; c++)
		outPos[c] = f32(fadd_m(fld_m(&pos[c]), &vel[c]));
	memcpy(step, vel, 12);
	memcpy(from, pos, 12);
	int result = 0;
	u8 *last = 0;
	for (int pass = 0;; pass++) {
		memcpy(at, from, 12);
		u8 *node = FIELD(u8 *, self, 0x18);
		int sub = -1, hit = 0;
		FIELD(u32, &best, 0) = 0xff7fffff;   /* -FLT_MAX */
		memcpy(move, step, 12);
		for (;;) {
			if (!node) {
				if (++sub >= nsubs)
					break;
				const float *in = (const float *)RELOC(subs[sub * 3 + 2]);
				node = (u8 *)RELOC(subs[sub * 3]);
				for (int i = 0; i < 3; i++)
					at[i] = row_point(in, from, i);
				for (int i = 0; i < 3; i++)
					move[i] = row_dir(in, step, i);
			}
			if (node != last && (sub >= 0 || !(*FIELD(u8 *, node, 0) & 1))
			    && collision_sphereVsUnit(FIELD(void *, node, 0), r, at, move, k, hitPos, hitVel, &dist, plane, axis) == 1) {
				hit = 1;
				if (dist > best) {
					if (sub < 0) {
						memcpy(outPos, hitPos, 12);
						memcpy(outVel, hitVel, 12);
						memcpy(outPlane, plane, 16);
					} else {
						const float *out = (const float *)RELOC(subs[sub * 3 + 1]);
						for (int i = 0; i < 3; i++)
							outPos[i] = row_point(out, hitPos, i);
						for (int i = 0; i < 3; i++)
							outVel[i] = row_dir(out, hitVel, i);
						for (int i = 0; i < 4; i++)
							outPlane[i] = f32(mul(fld_m(&plane[3]), &out[12 + i]) + mul(fld_m(&plane[2]), &out[8 + i])
							                  + mul(fld_m(&plane[1]), &out[4 + i]) + mul(fld_m(&plane[0]), &out[i]));
					}
					last = node;
					FIELD(u32, &best, 0) = FIELD(u32, &dist, 0);
				}
			}
			node = FIELD(u8 *, node, 0xc);
		}
		const float *tiny = (const float *)ADDR(k_1em8f);   /* 1e-8 */
		if (!(hit == 1 && best > *tiny))
			return result;
		if (!(mul(fld_m(&outVel[2]), &vel[2]) + mul(fld_m(&outVel[1]), &vel[1]) + mul(fld_m(&outVel[0]), &vel[0]) > *tiny)) {
			memcpy(outVel, (const void *)ADDR(g_vecZero), 12);
			FIELD(u32, outDist, 0) = 0;
			return 1;
		}
		result = 1;
		memcpy(from, outPos, 12);
		memcpy(step, outVel, 12);
		FIELD(u32, outDist, 0) = FIELD(u32, &best, 0);
		if (pass != 0 && mul(fld_m(&r), (const float *)ADDR(k_tenthsToDegrees)) > best)
			return result;
		if (pass + 1 > 5)
			return result;
	}
}

/* a triangle of the stage's ground or bounds put into the collision space (no unit, part or indices) */
static void ground_triangle(u8 *grid, u32 id, const void *a, const void *b, const void *c)
{
	space_buildPlanes(grid, id, (u32)a, (u32)b, (u32)c, 0, -1, -1, -1, -1);
}

/* 0x471040 (thiscall on the stage): its collision space (+0xa10) set up over the world box (+0x9ef904 low, +0x9ef910
   high) in cells of the given sizes (z, x, y: the counts of whole cells), with a, b and the depth. Then, with
   +0x9ef30c, the floor (the box's lower face, two triangles, id 0x10); each ground layer (+0xdc0a74 of them, 0x20c
   bytes from +0xdc0244: kind 0 or 1, rows +0x1c, columns +0x20, the (columns + 1) x (rows + 1) points +0x40) as two
   triangles a cell, split one way for kind 0 and the other for kind 1, each row logged; and every object in use
   (+4) that is not flagged 4 (+0xc) as a unit (space_buildUnits with its shape +0x27c and matrix +0xf4: +0x28c),
   every second one logged. Its caller ignores the eax it leaves */
void THISCALL (collision_initVolume)(u8 *stage, float size_z, float size_x, float size_y, u32 a, u32 b, u32 depth)
{
	Stage *st = (Stage *)stage;
	u8 *grid = stage + 0xa10;
	const float *low = ((Stage *)stage)->levelLow, *high = ((Stage *)stage)->levelHigh;
	log_message((int)stage, 0, 0, (const char *)STR(0x4c7490, "init. collision volume"));
	int ny = ftol(fdiv_m(fsub_m(fld_m(&high[1]), &low[1]), &size_y));
	int nx = ftol(fdiv_m(fsub_m(fld_m(&high[0]), &low[0]), &size_x));
	int nz = ftol(fdiv_m(fsub_m(fld_m(&high[2]), &low[2]), &size_z));
	space_setBy(grid, (void *)low, (void *)high, nz, nx, ny, a, b, depth);
	log_message((int)stage, 0, 0, (const char *)STR(0x4c747c, "add floor planes"));
	if (st->floorOn) {
#define F(v) f32(fld_m(&(v)))
		float va[3] = { F(high[0]), F(low[1]), F(low[2]) }, vb[3] = { F(low[0]), F(low[1]), F(high[2]) };
		float vd[3] = { F(high[0]), F(low[1]), F(high[2]) };
#undef F
		u32 vc[3];
		memcpy(vc, low, sizeof vc);
		ground_triangle(grid, 0x10, vc, vb, va);
		ground_triangle(grid, 0x10, va, vb, vd);
	}
	for (int l = 0; l < st->groundLayerCount; l++) {
		u8 *layer = (u8 *)&((Stage *)stage)->groundLayers[l];
		int kind = FIELD(int, layer, 0);
		if (kind != 0 && kind != 1)
			continue;
		for (int r = 0; r < FIELD(int, layer, 0x1c); r++) {
			log_message((int)stage, 0, r, (const char *)(RELOC(kind) ? STR(0x4c7430, "add layer ceiling type planes row %d") : STR(0x4c7458, "add layer floor type planes row %d")), r);
			for (int c = 0; c < FIELD(int, layer, 0x20); c++) {
				int w = FIELD(int, layer, 0x20) + 1;
				const float *v = FIELD(const float *, layer, 0x40);
				const float *p00 = v + (w * r + c) * 3, *p01 = p00 + 3, *p10 = v + (w * (r + 1) + c) * 3, *p11 = p10 + 3;
				if (kind == 0) {
					ground_triangle(grid, 0, p00, p10, p01);
					ground_triangle(grid, 0, p01, p10, p11);
				} else {
					ground_triangle(grid, 0, p00, p01, p10);
					ground_triangle(grid, 0, p01, p11, p10);
				}
			}
		}
	}
	for (int i = 0; i < st->objectCount; i++) {
		u8 *obj = (u8 *)&((Stage *)stage)->objects[i];
		if (FIELD(int, obj, 4) != 1 || (obj[0xc] & 4))
			continue;
		if (i % 2 == 0)
			log_message((int)stage, 0, i, (const char *)STR(0x4c7418, "add object %d planes"), i);
		FIELD(u32, obj, 0x28c) = space_buildUnits(grid, i, FIELD(void *, obj, 0x27c), (const float *)(obj + 0xf4));
	}
}
