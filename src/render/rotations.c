/* rotations.c: a rotation given as an angle (radians) about an axis, as a quaternion and as a matrix; a vector
   negated. The sine and cosine are the FPU's own (fsin / fcos), as the original's. */
#include "../game.h"

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
