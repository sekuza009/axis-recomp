/* crt_atof.c: atof as the game's runtime does it (Visual C++ 6's _fltin: 0x49fe7a atof, 0x4a65b5 __strgtold12,
   0x4a6d9f __mtold12, 0x4a7508 __multtenpow12, 0x4a72e8 __ld12mul, 0x4a51e1 _ld12cvt). msvcrt.dll's atof rounds
   correctly; VC6's is one unit off now and then (for long numbers, or with an exponent), so it is rebuilt: the text
   read into at most 24 decimal digits, those made an 80-bit binary mantissa, scaled by powers of ten from the
   runtime's tables (0x4d12f8 up, 0x4d1458 down) with a 96-bit product, and narrowed to a double. All integer
   arithmetic; the narrowing rounds up only when a bit beyond the one after the round bit is set (VC6's rule).

   A 12-byte value ("ld12") is: +0 16 more mantissa bits, +2 and +6 the 64-bit mantissa (top bit explicit), +0xa the
   sign and the biased exponent (0x3fff). */
#include "crt.h"
#include <string.h>

#define W16(p, o) (*(u16 *)((u8 *)RELOC(p) + (o)))
#define W32(p, o) (*(u32 *)((u8 *)RELOC(p) + (o)))

/* 0x4a6cc5: *sum = x + y; 1 on a carry */
static int addl(u32 x, u32 y, u32 *sum)
{
	u32 s = x + y;
	*sum = s;
	return s < x || s < y;
}

/* 0x4a6ce6, 0x4a6d44, 0x4a6d72: 96-bit add, shift left, shift right (by one) */
static void add12(u32 *x, const u32 *y)
{
	if (addl(x[0], y[0], &x[0]) && addl(x[1], 1, &x[1]))
		x[2]++;
	if (addl(x[1], y[1], &x[1]))
		x[2]++;
	addl(x[2], y[2], &x[2]);
}
static void shl12(u32 *x)
{
	u32 a = x[0], b = x[1];
	x[0] = a << 1;
	x[1] = b << 1 | a >> 31;
	x[2] = x[2] << 1 | b >> 31;
}
static void shr12(u32 *x)
{
	u32 c = x[2], b = x[1];
	x[1] = b >> 1 | c << 31;
	x[0] = x[0] >> 1 | b << 31;
	x[2] = c >> 1;
}

/* 0x4a6d9f: n decimal digits made a binary value, normalised (top bit at bit 79), its exponent in +0xa */
static void mtold12(const char *digit, unsigned n, u32 *x)
{
	u32 expn = 0x404e;
	x[0] = x[1] = x[2] = 0;
	for (; n > 0; n--, digit++) {
		u32 t[3] = { x[0], x[1], x[2] };
		shl12(x);
		shl12(x);
		add12(x, t);
		shl12(x);
		t[0] = (u32)(int)(signed char)*digit;
		t[1] = t[2] = 0;
		add12(x, t);
	}
	while (x[2] == 0) {
		x[2] = x[1] >> 16;
		x[1] = x[1] << 16 | x[0] >> 16;
		x[0] <<= 16;
		expn += 0xfff0;
	}
	while (!(x[2] & 0x8000)) {
		shl12(x);
		expn += 0xffff;
	}
	W16(x, 0xa) = (u16)expn;
}

/* 0x4a72e8: *x *= *y (12-byte values; the product rounded to even, overflow to infinity) */
static void ld12mul(u8 *x, const u8 *y)
{
	u16 ex = W16(x, 0xa), ey = W16(y, 0xa);
	u32 sign = (ex ^ ey) & 0x8000;
	u32 ax = ex & 0x7fff, cx = ey & 0x7fff, e = ax + cx;
	u32 r[3] = { 0, 0, 0 };
	int sticky = 0;
	if (ax >= 0x7fff || cx >= 0x7fff || (u16)e > 0xbffd)
		goto infinite;
	if ((u16)e <= 0x3fbf) {
		W32(x, 8) = W32(x, 4) = W32(x, 0) = 0;
		return;
	}
	if (ax == 0) {
		e++;
		if (!(W32(x, 8) & 0x7fffffff) && W32(x, 4) == 0 && W32(x, 0) == 0) {
			W16(x, 0xa) = 0;
			return;
		}
	}
	if (cx == 0) {
		e++;
		if (!(W32(y, 8) & 0x7fffffff) && W32(y, 4) == 0 && W32(y, 0) == 0) {
			W32(x, 8) = W32(x, 4) = W32(x, 0) = 0;
			return;
		}
	}
	for (int i = 0, count = 5; count > 0; i++, count--)
		for (int j = 0; j < count; j++) {
			u32 *at = (u32 *)((u8 *)RELOC(r) + 2 * i);
			if (addl(*at, (u32)W16(x, 2 * (i + j)) * W16(y, 8 - 2 * j), at))
				W16(r, 2 * i + 4)++;
		}
	e += 0xc002;
	if ((short)e > 0) {
		while (!(((u8 *)RELOC(r))[11] & 0x80)) {
			shl12(r);
			e += 0xffff;
			if ((short)e <= 0)
				break;
		}
	}
	if ((short)e <= 0) {
		e += 0xffff;
		if ((short)e < 0) {
			int n = -(short)e;
			e += n;
			for (; n > 0; n--) {
				if (((u8 *)RELOC(r))[0] & 1)
					sticky++;
				shr12(r);
			}
			if (sticky)
				((u8 *)RELOC(r))[0] |= 1;
		}
	}
	if (W16(r, 0) > 0x8000 || (W32(r, 0) & 0x1ffff) == 0x18000) {
		if (W32(r, 2) == 0xffffffff) {
			W32(r, 2) = 0;
			if (W32(r, 6) == 0xffffffff) {
				W32(r, 6) = 0;
				if (W16(r, 0xa) == 0xffff) {
					e++;
					W16(r, 0xa) = 0x8000;
				} else {
					W16(r, 0xa)++;
				}
			} else {
				W32(r, 6)++;
			}
		} else {
			W32(r, 2)++;
		}
	}
	if ((u16)e >= 0x7fff)
		goto infinite;
	W16(x, 0) = W16(r, 2);
	W32(x, 2) = W32(r, 4);
	W32(x, 6) = W32(r, 8);
	W16(x, 0xa) = (u16)(e | sign);
	return;
infinite:
	W32(x, 4) = 0;
	W32(x, 0) = 0;
	W32(x, 8) = (sign ? 0x80000000u : 0) + 0x7fff8000u;
}

/* 0x4a7508: *x *= 10^power, 3 bits of the power at a time from the runtime's tables (7 powers a step; an entry
   whose extension word is 0x8000 or more is used one unit lower in its mantissa); mult12 0: the extension cleared */
static void multtenpow12(u8 *x, int power, int mult12)
{
	u32 table = IMG(0x4d12f8);
	if (power == 0)
		return;
	if (power < 0) {
		power = -power;
		table = IMG(0x4d1458);
	}
	if (mult12 == 0)
		W16(x, 0) = 0;
	while (power != 0) {
		table += 0x54;
		int k = power & 7;
		power >>= 3;
		if (k == 0)
			continue;
		const u8 *entry = (const u8 *)(RELOC(table) + k * 12);
		u8 lower[12];
		if (W16(entry, 0) >= 0x8000) {
			memcpy(lower, entry, 12);
			W32(lower, 2)--;
			entry = lower;
		}
		ld12mul(x, entry);
	}
}

/* 0x4a65b5: the text at s read as a number into *x (at most 24 significant digits; a 25th and more only count in the
   exponent, rounding the 24th as VC6 does); *end at the first character not used. Flags: 4 no digits, 2 overflow,
   1 underflow */
static unsigned strgtold12(u8 *x, const char **end, const char *s, int mult12, int scale, int decpt, int implicitE)
{
	char buf[0x18 + 4], *man = buf;
	u32 manSign = 0;
	int expSign = 1, manlen = 0, foundDigit = 0, foundPoint = 0, foundExp = 0, overflow = 0, underflow = 0;
	int exp = 0, expAdj = 0;
	unsigned flags = 0;
	int state = 0;
	const unsigned char *p = (const unsigned char *)RELOC(s), *saved = p;   /* (the restart point: before the spaces) */
	unsigned char c;
	while (*p == ' ' || *p == '\t' || *p == '\n' || *p == '\r')
		p++;
#define DIGIT(c) ((c) >= '0' && (c) <= '9')
#define NZDIGIT(c) ((c) >= '1' && (c) <= '9')
	for (;;) {
		c = *p++;
		switch (state) {
		case 0:   /* the start */
			if (NZDIGIT(c)) { state = 3; p--; }
			else if (c == '.') state = 5;
			else if (c == '+') { state = 2; manSign = 0; }
			else if (c == '-') { state = 2; manSign = 0x8000; }
			else if (c == '0') state = 1;
			else { p--; goto done; }
			continue;
		case 1:   /* leading zeros */
			foundDigit = 1;
			if (NZDIGIT(c)) { state = 3; p--; }
			else if (c == '.') state = 4;
			else if (c == '+' || c == '-') { p--; state = 11; }
			else if (c == '0') state = 1;
			else if (c == 'D' || c == 'E' || c == 'd' || c == 'e') state = 6;
			else { p--; goto done; }
			continue;
		case 2:   /* after the sign */
			if (NZDIGIT(c)) { state = 3; p--; }
			else if (c == '.') state = 5;
			else if (c == '0') state = 1;
			else { p = saved; goto done; }
			continue;
		case 3:   /* the digits before the point */
			foundDigit = 1;
			while (DIGIT(c)) {
				if (manlen < 0x19) { manlen++; *man++ = (char)(c - '0'); }
				else expAdj++;
				c = *p++;
			}
			if (c == '.') { state = 4; continue; }
			goto after_digits;
		case 4:   /* the digits after the point */
			foundDigit = 1;
			foundPoint = 1;
			if (manlen == 0)
				while (c == '0') { expAdj--; c = *p++; }
			while (DIGIT(c)) {
				if (manlen < 0x19) { manlen++; *man++ = (char)(c - '0'); expAdj--; }
				c = *p++;
			}
		after_digits:
			if (c == '+' || c == '-') { p--; state = 11; }
			else if (c == 'D' || c == 'E' || c == 'd' || c == 'e') state = 6;
			else { p--; goto done; }
			continue;
		case 5:   /* a point first */
			foundPoint = 1;
			if (DIGIT(c)) { state = 4; p--; }
			else { p = saved; goto done; }
			continue;
		case 6:   /* after the E */
			saved = p - 2;
			if (NZDIGIT(c)) { state = 9; p--; }
			else if (c == '+') state = 7;
			else if (c == '-') { expSign = -1; state = 7; }
			else if (c == '0') state = 8;
			else { p = saved; goto done; }
			continue;
		case 7:   /* the exponent's sign */
			if (NZDIGIT(c)) { state = 9; p--; }
			else if (c == '0') state = 8;
			else { p = saved; goto done; }
			continue;
		case 8:   /* the exponent's leading zeros */
			foundExp = 1;
			while (c == '0')
				c = *p++;
			if (NZDIGIT(c)) { state = 9; p--; }
			else { p--; goto done; }
			continue;
		case 9:   /* the exponent's digits */
			foundExp = 1;
			exp = 0;
			while (DIGIT(c)) {
				exp = exp * 10 + (signed char)c - '0';
				if (exp > 0x1450) { exp = 0x1451; break; }
				c = *p++;
			}
			while (DIGIT(c))
				c = *p++;
			p--;
			goto done;
		case 11:   /* a sign after the digits: an exponent only when implicit */
			if (implicitE == 0) { p--; goto done; }
			saved = p - 1;
			if (c == '+') state = 7;
			else if (c == '-') { expSign = -1; state = 7; }
			else { p = saved; goto done; }
			continue;
		}
	}
#undef DIGIT
#undef NZDIGIT
done:
	*end = (const char *)p;
	u32 lo = 0, hi = 0, w0 = 0, ew = 0;
	if (!foundDigit) {
		flags = 4;
	} else {
		if (manlen > 0x18) {
			if (buf[0x17] >= 5)
				buf[0x17]++;
			manlen = 0x18;
			man--;
			expAdj++;
		}
		while (manlen > 0 && man[-1] == 0) {
			man--;
			manlen--;
			expAdj++;
		}
		if (manlen > 0) {
			u8 v[12];
			mtold12(buf, (unsigned)manlen, (u32 *)v);
			if (expSign < 0)
				exp = -exp;
			exp += expAdj;
			if (!foundExp)
				exp += scale;
			if (!foundPoint)
				exp -= decpt;
			if (exp > 0x1450)
				overflow = 1;
			else if (exp < -0x1450)
				underflow = 1;
			else {
				multtenpow12(v, exp, mult12);
				w0 = W16(v, 0);
				lo = W32(v, 2);
				hi = W32(v, 6);
				ew = W16(v, 0xa);
			}
			if (overflow) {
				lo = 0; ew = 0x7fff; hi = 0x80000000u; w0 = 0;
				flags = 2;
			} else if (underflow) {
				lo = hi = w0 = ew = 0;
				flags = 1;
			}
		}
	}
	W32(x, 6) = hi;
	W32(x, 2) = lo;
	W16(x, 0xa) = (u16)(ew | manSign);
	W16(x, 0) = (u16)w0;
	return flags;
}

/* 0x4a4fe7: the mantissa's bits after position n (counted from the top) all clear */
static int zero_after(const u32 *man, int n)
{
	int w = n / 32, r = n % 32;
	if (man[w] & ~(0xffffffffu << (31 - r)))
		return 0;
	for (w++; w < 3; w++)
		if (man[w])
			return 0;
	return 1;
}

/* 0x4a5030: one added at position n (from the top); the carry out of the top */
static int inc_man(u32 *man, int n)
{
	int w = n / 32, r = n % 32;
	int carry = addl(man[w], 1u << (31 - r), &man[w]);
	for (w--; w >= 0 && carry; w--)
		carry = addl(man[w], 1, &man[w]);
	return carry;
}

/* 0x4a5086: rounded to precision bits: up when the round bit is set and some bit after the one following it is too;
   the bits below cleared. 1 when the rounding carried out of the top */
static int round_man(u32 *man, int precision)
{
	int keep = precision, w = keep / 32, shift = 31 - keep % 32;
	int carry = 0;
	if (man[w] & (1u << shift)) {
		if (!zero_after(man, keep + 1))
			carry = inc_man(man, precision - 1);
	}
	man[w] &= 0xffffffffu << shift;
	for (w++; w < 3; w++)
		man[w] = 0;
	return carry;
}

/* 0x4a5154: shifted right by n bits */
static void shr_man(u32 *man, int n)
{
	int words = n / 32, r = n % 32;
	u32 mask = ~(0xffffffffu << r), carry = 0;
	for (int k = 0; k < 3; k++) {
		u32 low = man[k] & mask;
		man[k] = man[k] >> r | carry;
		carry = r ? low << (32 - r) : 0;
	}
	for (int k = 2; k >= 0; k--)
		man[k] = k >= words ? man[k - words] : 0;
}

/* 0x4a51e1 (_ld12cvt with the double's format at 0x4d1010: exponents 1024 / -1023, 53 bits, 11 exponent bits,
   bias 1023): *x as a double into d[0] (low) and d[1] (high) */
static void ld12tod(const u8 *x, u32 *d)
{
	enum { MAX_EXP = 1024, MIN_EXP = -1023, PRECISION = 53, EXP_WIDTH = 11, BIAS = 1023 };
	u32 sign = W16(x, 0xa) & 0x8000;
	int exp = (W16(x, 0xa) & 0x7fff) - 0x3fff, bexp;
	u32 man[3] = { W32(x, 6), W32(x, 2), (u32)W16(x, 0) << 16 }, saved[3];
	if (exp == -0x3fff) {
		bexp = 0;
		if (!(man[0] == 0 && man[1] == 0 && man[2] == 0))
			man[0] = man[1] = man[2] = 0;
	} else {
		memcpy(saved, man, sizeof man);
		if (round_man(man, PRECISION))
			exp++;
		if (exp < MIN_EXP - PRECISION) {
			man[0] = man[1] = man[2] = 0;
			bexp = 0;
		} else if (exp <= MIN_EXP) {
			memcpy(man, saved, sizeof man);
			shr_man(man, MIN_EXP - exp);
			round_man(man, PRECISION);
			shr_man(man, EXP_WIDTH + 1);
			bexp = 0;
		} else if (exp >= MAX_EXP) {
			man[0] = man[1] = man[2] = 0;
			man[0] |= 0x80000000u;
			shr_man(man, EXP_WIDTH);
			bexp = MAX_EXP + BIAS;
		} else {
			man[0] &= 0x7fffffff;
			shr_man(man, EXP_WIDTH);
			bexp = exp + BIAS;
		}
	}
	d[1] = (u32)bexp << (31 - EXP_WIDTH) | (sign ? 0x80000000u : 0) | man[0];
	d[0] = man[1];
}

/* 0x49fe7a: atof. Spaces skipped (the C locale's: tab .. carriage return, space), the number read; none: 0 */
double (crt_atof)(const char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	u8 x[12];
	const char *end;
	u32 d[2] = { 0, 0 };
	if (!(strgtold12(x, &end, s, 0, 0, 0, 0) & 4))
		ld12tod(x, d);
	double r;
	memcpy(&r, d, 8);
	return r;
}
