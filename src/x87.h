/* x87.h: the x87 instructions the original computes with where C has no exact equivalent: the C library's sin, cos,
   sqrt ... may round differently or not use the FPU at all. Each is the one instruction on the top of the FPU stack,
   at 80 bits (src/axis.h: this tree is built with -mno-sse). */
#ifndef X87_H
#define X87_H

#if !defined(__i386__) && !defined(__x86_64__)
/* (no x87 - arm64, Apple Silicon: the C library's, in long double - there the 64-bit double, which is the precision
   the game sets the x87 to anyway: 53 bits, src/app/win32.c axis_frame) */
#include <math.h>
static inline long double x87_fsin(long double x) { return sinl(x); }
static inline long double x87_fcos(long double x) { return cosl(x); }
static inline long double x87_fsqrt(long double x) { return sqrtl(x); }
static inline long double x87_fabs(long double x) { return fabsl(x); }
static inline long double x87_fchs(long double x) { return copysignl(x, -copysignl(1.0L, x)); }
static inline long double x87_fptan(long double x) { return tanl(x); }
static inline long double x87_fpatan(long double y, long double x) { return atan2l(y, x); }
#else
static inline long double x87_fsin(long double x) { __asm__("fsin" : "+t"(x)); return x; }
static inline long double x87_fcos(long double x) { __asm__("fcos" : "+t"(x)); return x; }
static inline long double x87_fsqrt(long double x) { __asm__("fsqrt" : "+t"(x)); return x; }
static inline long double x87_fabs(long double x) { __asm__("fabs" : "+t"(x)); return x; }
/* the sign flipped: also a NaN's (a C negation may be folded into a product, which leaves a new NaN's sign the other
   way) */
static inline long double x87_fchs(long double x) { __asm__("fchs" : "+t"(x)); return x; }
/* tan x (fptan, the 1 it pushes dropped) */
static inline long double x87_fptan(long double x) { __asm__("fptan\n\tfstp %%st(0)" : "+t"(x)); return x; }
/* atan2(y, x) (fpatan) */
static inline long double x87_fpatan(long double y, long double x)
{
	long double r;
	__asm__("fpatan" : "=t"(r) : "0"(x), "u"(y) : "st(1)");
	return r;
}
#endif

#endif
