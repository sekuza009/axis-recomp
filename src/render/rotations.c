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
