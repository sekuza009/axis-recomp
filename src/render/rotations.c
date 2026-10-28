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
void THISCALL (FUN_0047d0b0)(float *q, const float *rotation)
{
	X s = fsin((X)rotation[0] * MINUS_HALF);
	q[0] = (float)(s * rotation[1]);
	q[1] = (float)(s * rotation[2]);
	q[2] = (float)(s * rotation[3]);
	q[3] = (float)fcos((X)rotation[0] * HALF);
}

/* 0x47d9a0: m = the matrix of {angle, axis x, y, z}, through its quaternion */
void (FUN_0047d9a0)(float *m, const float *rotation)
{
	float q[4];
	FUN_0047d0b0(q, rotation);
	FUN_0047d8a0(m, q);
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
long double (FUN_0046c100)(float a)
{
	int turns = ftol(fmul_m(fld_m(&a), PER_TURN));
	X r = fsubr_m(fmul_m((X)turns, TURN), &a);
	if (!(r >= ZERO))
		r = fadd_m(r, TURN);
	return r;
}

/* 0x482a40: out = the point p transformed by the matrix m (columns, the translation at 12 .. 14), each row summed in
   the original's order */
void (load_482a40)(float *out, const float *m, const float *p)
{
	out[0] = (float)((X)m[8] * p[2] + (X)m[4] * p[1] + (X)m[0] * p[0] + m[12]);
	out[1] = (float)((X)m[9] * p[2] + (X)m[1] * p[0] + (X)m[5] * p[1] + m[13]);
	out[2] = (float)((X)m[10] * p[2] + (X)m[2] * p[0] + (X)m[6] * p[1] + m[14]);
}

/* 0x4679a0: out = the unit normal of the triangle p0, p1, p2 ((p1 - p0) x (p2 - p0)); of p1 - p0, x and y are
   rounded to floats and z is not */
void (FUN_004679a0)(float *out, const float *p1, const float *p0, const float *p2)
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
void (FUN_0047d8a0)(float *m, const float *q)
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
