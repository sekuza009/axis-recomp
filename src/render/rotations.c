/* rotations.c: a rotation given as an angle (radians) about an axis, as a quaternion and as a matrix; a 2D turn by
   the game's tables; an angle wrapped; a vector negated or scaled. The sine and cosine are the FPU's own (fsin /
   fcos), as the original's. */
#include "../game.h"
#include <string.h>

typedef long double X;

static X fsin(X x) { __asm__("fsin" : "+t"(x)); return x; }
static X fcos(X x) { __asm__("fcos" : "+t"(x)); return x; }

#define MINUS_HALF GAME_VAR(float, 0x4a94f4)   /* -0.5 */
#define HALF GAME_VAR(float, 0x4a942c)         /* 0.5 */
#define ONE GAME_VAR(float, 0x4a9424)

/* 0x47d0b0: q = the quaternion of {angle, axis x, y, z}: sin(-angle / 2) times the axis, then cos(angle / 2) (the
   angle read again for it) */
void THISCALL (quat_fromAxisAngle)(float *q, const float *rotation)
{
	X s = fsin((X)rotation[0] * MINUS_HALF);
	q[0] = (float)(s * rotation[1]);
	q[1] = (float)(s * rotation[2]);
	q[2] = (float)(s * rotation[3]);
	q[3] = (float)fcos((X)rotation[0] * HALF);
}

/* 0x47d9a0: m = the matrix of {angle, axis x, y, z}, through its quaternion */
void (Mat4_fromAxisAngle)(float *m, const float *rotation)
{
	float q[4];
	quat_fromAxisAngle(q, rotation);
	Mat4_fromQuat(m, q);
}

/* 0x480230: v = -v (each component loaded and stored again: a signalling NaN comes out quiet) */
void THISCALL (collision_480230)(float *v)
{
	for (int i = 0; i < 3; i++) {
		volatile X t = v[i];
		v[i] = (float)-t;
	}
}

/* 0x467700: (x, y) turned by angle tenths of a degree, from the game's cosine and sine tables */
#define g_cos ((const float *)0xa17f38)
#define g_sin ((const float *)0xa1b778)
void THISCALL (hud_467700)(float *v, int angle)
{
	int i = (angle % 3600 + 3600) % 3600;
	X c = g_cos[i], s = g_sin[i];
	X x = c * v[0] + s * v[1], y = c * v[1] - s * v[0];
	v[1] = (float)y;
	v[0] = (float)x;
}

/* 0x4803c0: v scaled by s, and copied to out */
void THISCALL (collision_4803c0)(float *v, float *out, float s)
{
	volatile X k = s;   /* x87 fmul: of two NaNs it keeps the larger payload */
	for (int i = 0; i < 3; i++)
		v[i] = (float)(k * v[i]);
	memcpy(out, v, 12);
}

/* 0x46c100: an angle in tenths of a degree wrapped into 0 .. 3600 (a - whole turns, plus a turn when that is
   negative or NaN); returned unrounded */
#define TURN ((const float *)0x4a94c8)        /* 3600 */
#define PER_TURN ((const float *)0x4aa284)    /* 1 / 3600 */
#define ZERO GAME_VAR(float, 0x4a93e8)
long double (angle_wrap)(float a)
{
	int turns = ftol(fmul_m(fld_m(&a), PER_TURN));
	X r = fsubr_m(fmul_m((X)turns, TURN), &a);
	if (!(r >= ZERO))
		r = fadd_m(r, TURN);
	return r;
}

/* 0x46c140: the turn from angle a to angle b (tenths of a degree, as bits), both wrapped first (rounded to floats):
   the shorter way, -1800 .. 1800; returned unrounded */
#define HALF_TURN GAME_VAR(float, 0x4aa288)   /* 1800 */
long double (angle_turn)(u32 a, u32 b)
{
	float B = (float)FUN_0046c100_bits(b), A = (float)FUN_0046c100_bits(a);
	if (B > A) {
		X d = fsub_m(fld_m(&B), &A);
		if (d > HALF_TURN)
			return fsubr_m(fadd_m(fld_m(&A), TURN), &B);
		return d;
	}
	X b2 = fld_m(&B);
	if (fsub_m(fld_m(&A), &B) > HALF_TURN)
		b2 = fadd_m(b2, TURN);
	return fsub_m(b2, &A);
}

/* 0x46c1c0: angle a moved part t of the shorter way to b (b wrapped and rounded, a wrapped and kept unrounded),
   wrapped back into 0 .. 3600; returned unrounded */
long double (angle_stepTowards)(u32 a, u32 b, float t)
{
	float B = (float)FUN_0046c100_bits(b);
	X A = FUN_0046c100_bits(a);
	if (B > A) {
		X d = fld_m(&B) - A;
		if (!(d > HALF_TURN))
			return fmul_m(d, &t) + A;
		X v = fmul_m(fsub_m(fld_m(&B), TURN) - A, &t) + A;
		if (!(v >= ZERO))
			v = fadd_m(v, TURN);
		return v;
	}
	if (!(A - fld_m(&B) > HALF_TURN))
		return fmul_m(fld_m(&B) - A, &t) + A;
	X v = fmul_m(fadd_m(fld_m(&B), TURN) - A, &t) + A;
	if (v >= *TURN)
		v = fsub_m(v, TURN);
	return v;
}

/* 0x482a40: out = the point p transformed by the matrix m (columns, the translation at 12 .. 14), each row summed in
   the original's order */
void (space_transformPoint)(float *out, const float *m, const float *p)
{
	out[0] = (float)((X)m[8] * p[2] + (X)m[4] * p[1] + (X)m[0] * p[0] + m[12]);
	out[1] = (float)((X)m[9] * p[2] + (X)m[1] * p[0] + (X)m[5] * p[1] + m[13]);
	out[2] = (float)((X)m[10] * p[2] + (X)m[2] * p[0] + (X)m[6] * p[1] + m[14]);
}

/* 0x4679a0: out = the unit normal of the triangle p0, p1, p2 ((p1 - p0) x (p2 - p0)); of p1 - p0, x and y are
   rounded to floats and z is not */
void (math_triangleNormal)(float *out, const float *p1, const float *p0, const float *p2)
{
	X ux = (X)p2[0] - p0[0], uy = (X)p2[1] - p0[1], uz = (X)p2[2] - p0[2];
	float vx = f32((X)p1[0] - p0[0]), vy = f32((X)p1[1] - p0[1]);
	X vz = (X)p1[2] - p0[2];
	float n[3];
	n[0] = (float)(vz * uy - vy * uz);
	n[1] = (float)(vx * uz - vz * ux);
	n[2] = (float)(vy * ux - vx * uy);
	Vec3_normalize(n);
	out[0] = n[0];
	out[1] = n[1];
	out[2] = n[2];
}

/* 0x47d8a0: m = the rotation matrix (columns) of the quaternion q = (x, y, z, w). xx, xy and w * z stay unrounded;
   the other products are rounded to floats first, as the original keeps them */
void (Mat4_fromQuat)(float *m, const float *q)
{
	X x = q[0], y = q[1], z = q[2], w = q[3], one = ONE;
	X xx = x * x, xy = y * x;
	float xz = f32(z * x), nwx = f32(-(w * x)), yy = f32(y * y), yz = f32(z * y), nwy = f32(-(w * y));
	float zz = f32(z * z);
	X nwz = -(w * z);
	float r[16];
	r[0] = (float)(one - ((X)zz + yy) * 2);
	r[4] = (float)((xy - nwz) * 2);
	r[8] = (float)(((X)nwy + xz) * 2);
	r[1] = (float)((nwz + xy) * 2);
	r[5] = (float)(one - ((X)zz + xx) * 2);
	r[9] = (float)(((X)yz - nwx) * 2);
	r[2] = (float)(((X)xz - nwy) * 2);
	r[6] = (float)(((X)yz + nwx) * 2);
	r[10] = (float)(one - ((X)yy + xx) * 2);
	r[3] = r[7] = r[11] = r[12] = r[13] = r[14] = 0;
	r[15] = 1.0f;
	memcpy(m, r, sizeof r);   /* all of q is read before the first store, as in the original */
}

static X fsqrt(X x) { __asm__("fsqrt" : "+t"(x)); return x; }

/* 0x47d0f0: q = the quaternion (x, y, z, w) of the rotation in m's upper 3 x 3 (columns): from the trace when it is
   positive, else from the largest diagonal element */
void THISCALL (skel_ase_47d0f0)(float *q, const float *m)
{
	X one = ONE, half = HALF, quarter = GAME_VAR(float, 0x4a941c);
	X t = (X)m[5] + m[0] + m[10] + one;
	if (t > GAME_VAR(float, 0x4a93e8)) {
		X s = half / fsqrt(t);
		q[3] = (float)(quarter / s);
		q[0] = (float)(((X)m[9] - m[6]) * s);
		q[1] = (float)(((X)m[2] - m[8]) * s);
		q[2] = (float)(((X)m[4] - m[1]) * s);
		return;
	}
	int i = m[0] >= m[5] ? (m[0] >= m[10] ? 0 : 2) : (m[5] >= m[10] ? 1 : 2);
	X s;
	switch (i) {
	case 0:
		s = fsqrt((X)m[0] + one - m[5] - m[10]);
		s += s;
		q[0] = (float)(s * quarter);
		q[3] = (float)(((X)m[9] - m[6]) / s);
		q[1] = (float)(((X)m[4] + m[1]) / s);
		q[2] = (float)(((X)m[8] + m[2]) / s);
		break;
	case 1:
		s = fsqrt((X)m[5] + one - m[10] - m[0]);
		s += s;
		q[1] = (float)(s * quarter);
		q[3] = (float)(((X)m[2] - m[8]) / s);
		q[2] = (float)(((X)m[9] + m[6]) / s);
		q[0] = (float)(((X)m[4] + m[1]) / s);
		break;
	default:
		s = fsqrt((X)m[10] + one - m[0] - m[5]);
		s += s;
		q[2] = (float)(s * quarter);
		q[3] = (float)(((X)m[4] - m[1]) / s);
		q[0] = (float)(((X)m[8] + m[2]) / s);
		q[1] = (float)(((X)m[9] + m[6]) / s);
		break;
	}
}

/* the game's CRT acos (_CIacos: the argument and result on the FPU stack) */
static X crt_acos(X x)
{
	__asm__ volatile("call *%1" : "+t"(x) : "r"(0x49ffc0) : "eax", "ecx", "edx", "memory");
	return x;
}

/* 0x47d260: out = (angle, axis) of the quaternion q = (x, y, z, w): the angle -2 acos(w) (0 for w >= 1, -2 pi for
   w <= -1 or NaN), the axis (x, y, z) / sqrt(1 - w * w), a root below 1e-8 (or NaN) taken as 1 */
void THISCALL (skel_ase_47d260)(float *out, const float *q)
{
	if (q[3] >= ONE)
		out[0] = 0;
	else if (q[3] > GAME_VAR(float, 0x4a9474))
		out[0] = (float)fmul_m(crt_acos(fld_m(&q[3])), (const float *)0x4a94a8);   /* * -2 */
	else
		BITS(out[0]) = 0xc0c90fdb;   /* -2 pi */
	X w = fld_m(&q[3]);
	X s = fsubr_m(w * w, (const float *)0x4a9424), a;
	__asm__("fsqrt" : "+t"(s));
	__asm__("fabs" : "=t"(a) : "0"(s));
	if (!(a >= GAME_VAR(double, 0x4aa458)))
		s = fld_m((const float *)0x4a9424);
	out[1] = (float)(fld_m(&q[0]) / s);
	out[2] = (float)(fld_m(&q[1]) / s);
	out[3] = (float)(fld_m(&q[2]) / s);
}

/* 0x47d320: the two rotations a and b (angle, axis) combined: out = the (angle, axis) of matrix(a) * matrix(b) */
u32 (skel_ase_47d320)(float *out, const float *a, const float *b)
{
	float ma[16], mb[16], m[16];
	Mat4_fromAxisAngle(ma, a);
	Mat4_fromAxisAngle(mb, b);
	GAME_CDECL(0x47d380, void, float *, const float *, const float *)(m, ma, mb);   /* Mat4_multiply */
	return GAME_THISCALL(0x47d2f0, u32, float *, const float *)(out, m);       /* skel_ase_47d2f0: matrix -> (angle, axis) */
}

/* 0x47d2f0: out (a rotation) set from the matrix m by way of its quaternion (skel_ase_47d0f0, then skel_ase_47d260).
   Its callers ignore the eax it leaves */
void THISCALL (skel_ase_47d2f0)(float *out, const float *m)
{
	float q[4];
	skel_ase_47d0f0(q, m);
	skel_ase_47d260(out, q);
}
