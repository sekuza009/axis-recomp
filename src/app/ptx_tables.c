/* ptx_tables.c: the lookup tables of the PTX image decoder (the compressed textures): the clamp table, the colour space
   conversions (16.16 fixed point) and the quantisation tables for a quality. */
#include "../game.h"
#include <string.h>

#define I32(a) GAME_VAR(int, a)
#define F32(a) GAME_VAR(float, a)
#define g_ptxQuality I32(STR(0x4c59e8, "\377\377\377\377"))           /* meant as the quality the tables are made for, but never written: always -1, so both builders always rebuild */

/* 0x46e320: the clamp table: 0 below, the identity, 255 above */
void (ptx_initClampTable)(void)
{
	memset(AP(void, OBJ(g_ptxClampTable)), 0, 0x100);
	g_ptxClamp = AREF(AP(u8, (OBJ(g_ptxClampTable) + 0x100)));
	for (int i = 0; i < 256; i++)
		g_ptxClampTable[0x100 + i] = (u8)i;
	memset(AP(void, (OBJ(g_ptxClampTable) + 0x200)), 0xff, 0x180);
	memset(AP(void, (OBJ(g_ptxClampTable) + 0x380)), 0, 0x180);
	memcpy(AP(void, (OBJ(g_ptxClampTable) + 0x500)), AP(const void, g_ptxClamp), 0x80);
}

/* 0x46e7c0: YCbCr -> RGB, the four per-component tables (Cr to red, Cb and Cr to green, Cb to blue) */
void (ptx_initColourTables)(void)
{
	int c = 0x2c8d00, d = (int)0xff4d0b80, s = (int)0xff1daf00, e = 0x5b6900;
	for (int k = 0; ; k += 4) {
		I32(OBJ(g_ptxCbGreen) + k) = c;
		I32(OBJ(g_ptxCrRed) + k) = d >> 16;
		I32(OBJ(g_ptxCbBlue) + k) = s >> 16;
		I32(OBJ(g_ptxCrGreen) + k) = e;
		c -= 0x581a;
		d += 0x166e9;
		s += 0x1c5a2;
		e -= 0xb6d2;
		if (c < (int)0xffd4cb1a)
			break;
	}
}

/* 0x46efd0: RGB -> YCbCr, eight tables of 256 (each component's share of Y, Cb and Cr) */
void (ptx_initYCbCrTables)(void)
{
	int rY = 0, gY = 0, bY = 0x8000, rCb = 0, gCb = 0, bCb = 0x807fff, gCr = 0, bCr = 0;
	for (u32 p = OBJ(g_ptxYCbCrTables) + 0x800; p <= OBJ(g_ptxYCbCrTables) + 0xbfc; p += 4) {   /* (the third table; the others around it) */
		I32(p - 0x800) = rY;
		I32(p - 0x400) = gY;
		I32(p) = bY;
		I32(p + 0x400) = rCb;
		I32(p + 0x800) = gCb;
		I32(p + 0xc00) = bCb;
		I32(p + 0x1000) = gCr;
		I32(p + 0x1400) = bCr;
		bCb += 0x8000;
		gCr -= 0x6b2f;
		rY += 0x4c8b;
		gY += 0x9646;
		bY += 0x1d2f;
		rCb -= 0x2b33;
		gCb -= 0x54cd;
		bCr -= 0x14d1;
	}
}

/* 0x46e9b0: the decoder's dequantisation multipliers for quality q (g_ptxDequant, luma then chroma):
   base (g_ptxQuantBase) x AAN scale (k_ptxQuantScales) x 100 / q >> 12, libjpeg's ifast IDCT multiplier table;
   ptx_inverseDct multiplies the coefficients by them */
void (ptx_initDequantTables)(int q)
{
	if (g_ptxQuality == q)
		return;
	for (int j = 0; j < 128; j++) {
		int t = (int)((u32)I32(OBJ(g_ptxQuantBase) + j * 4) * (u32)I32(OBJ(k_ptxQuantScales) + (j & 63) * 4) * 100u);
		I32(OBJ(g_ptxDequant) + j * 4) = (t / q) >> 12;
	}
}

/* 0x46e2b0: the forward DCT's divisors for quality q (g_ptxFdctDivisors: 1 / (g_ptxFdctBase x 100 / q
   x aan[row] x aan[col] x 8), libjpeg jcdctmgr's float fdtbl) - an encoder's table, never read by the decoder */
void (ptx_initFdctDivisors)(int q)
{
	typedef long double X;
	if (g_ptxQuality == q)
		return;
	X qf = q;
	const double *f = k_aanScales;
	for (int j = 0; j < 128; j++) {
		X v = (X)F32(OBJ(g_ptxFdctBase) + j * 4) * k_100;
		v = v / qf * f[(j >> 3) & 7] * f[j & 7] * k_8;
		F32(OBJ(g_ptxFdctDivisors) + j * 4) = (float)((X)k_1 / v);
	}
}

/* 0x46ea00: every table, for quality 100 */
void (ptx_initTables)(void)
{
	g_ptxHuffSet = 0;
	ptx_initClampTable();
	ptx_initYCbCrTables();
	ptx_initFdctDivisors(100);
	ptx_initColourTables();
	ptx_initDequantTables(100);
}
