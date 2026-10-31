/* ptx_tables.c: the lookup tables of the PTX video decoder (the intro films): the clamp table, the colour space
   conversions (16.16 fixed point) and the quantisation tables for a quality. */
#include "../game.h"
#include <string.h>

#define I32(a) GAME_VAR(int, a)
#define F32(a) GAME_VAR(float, a)
#define F64(a) GAME_VAR(double, a)
#define g_ptxQuality I32(0x4c59e8)           /* the quality the tables are made for */
#define g_ptxClamp GAME_VAR(u8 *, 0xa1f300)   /* clamp[v]: v limited to 0 .. 255 (v from -0x100) */

/* 0x46e320: the clamp table: 0 below, the identity, 255 above */
void (ptx_initClampTable)(void)
{
	memset((void *)0xa61b0c, 0, 0x100);
	g_ptxClamp = (u8 *)0xa61c0c;
	for (int i = 0; i < 256; i++)
		GAME_VAR(u8, 0xa61c0c + i) = (u8)i;
	memset((void *)0xa61d0c, 0xff, 0x180);
	memset((void *)0xa61e8c, 0, 0x180);
	memcpy((void *)0xa6200c, g_ptxClamp, 0x80);
}

/* 0x46e7c0: YCbCr -> RGB, the four per-component tables (Cr to red, Cb and Cr to green, Cb to blue) */
void (ptx_initColourTables)(void)
{
	int c = 0x2c8d00, d = (int)0xff4d0b80, s = (int)0xff1daf00, e = 0x5b6900;
	for (int k = 0; ; k += 4) {
		I32(0xa6170c + k) = c;
		I32(0xaa228c + k) = d >> 16;
		I32(0xa1f304 + k) = s >> 16;
		I32(0xaa2690 + k) = e;
		c -= 0x581a;
		d += 0x166e9;
		s += 0x1c5a2;
		e -= 0xb6d2;
		if (c < (int)0xffd4cb1a)
			break;
	}
}

/* 0x46efd0: RGB -> YCbCr, eight tables of 256 (each component's share of Y, Cb and Cr) */
void (ptx_initTable_46efd0)(void)
{
	int c = 0, d = 0, s = 0x8000, e = 0, b = 0, l10 = 0x807fff, l14 = 0, l18 = 0;
	for (u32 p = 0xa1ff04; p <= 0xa20300; p += 4) {
		I32(p - 0x800) = c;
		I32(p - 0x400) = d;
		I32(p) = s;
		I32(p + 0x400) = e;
		I32(p + 0x800) = b;
		I32(p + 0xc00) = l10;
		I32(p + 0x1000) = l14;
		I32(p + 0x1400) = l18;
		l10 += 0x8000;
		l14 -= 0x6b2f;
		c += 0x4c8b;
		d += 0x9646;
		s += 0x1d2f;
		e -= 0x2b33;
		b -= 0x54cd;
		l18 -= 0x14d1;
	}
}

/* 0x46e9b0: the two 64-entry quantisation tables (luma, chroma) scaled for quality q */
void (ptx_initQuantTables)(int q)
{
	if (g_ptxQuality == q)
		return;
	for (int j = 0; j < 128; j++) {
		int t = (int)((u32)I32(0x4c6db0 + j * 4) * (u32)I32(0x4aa2f0 + (j & 63) * 4) * 100u);
		I32(0xaa2c94 + j * 4) = (t / q) >> 12;
	}
}

/* 0x46e2b0: the dequantisation tables for quality q, with the AAN inverse DCT's scale factors (eight doubles at
   0x4aa2b0) folded in */
void (ptx_initDequantTables)(int q)
{
	typedef long double X;
	if (g_ptxQuality == q)
		return;
	X qf = q;
	const double *f = (const double *)0x4aa2b0;
	for (int j = 0; j < 128; j++) {
		X v = (X)F32(0x4c6bb0 + j * 4) * F64(0x4aa3f8);
		v = v / qf * f[(j >> 3) & 7] * f[j & 7] * F64(0x4aa3f0);
		F32(0xaa2a90 + j * 4) = (float)((X)F64(0x4a94e0) / v);
	}
}

/* 0x46ea00: every table, for quality 100 */
void (ptx_initTables)(void)
{
	I32(0xaa2e94) = 0;
	ptx_initClampTable();
	ptx_initTable_46efd0();
	ptx_initDequantTables(100);
	ptx_initColourTables();
	ptx_initQuantTables(100);
}
