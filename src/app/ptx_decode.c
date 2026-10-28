/* ptx_decode.c: the PTX video decoder (the intro films), JPEG-style: a bit stream read most significant bit first,
   Huffman-coded DC differences and AC run / size symbols for each 8 x 8 block of coefficients in zigzag order, then
   the decoded planes (Y, Cb, Cr and alpha, 0x10000 bytes apart) turned into RGB(A) through the tables of
   ptx_tables.c, and the 8 x 8 blocks laid out as image rows. */
#include "../game.h"
#include <string.h>

#define g_bitPos GAME_VAR(int, 0xa21704)          /* the stream position, in bits */
#define g_bitStream GAME_VAR(const u8 *, 0xa61708)
#define g_table GAME_VAR(int, 0xaa2e94)           /* the Huffman table set in use */
#define g_lastDc GAME_VAR(int, 0xaa268c)          /* the block's DC is a difference from the one before */
#define g_zigzag ((const int *)0x4c59ec)
#define g_clamp GAME_VAR(const u8 *, 0xa1f300)

/* 0x46f230: *out = the next n bits; returns the new position */
int (ptx_46f230)(int *out, int n)
{
	*out = 0;
	if (n <= 0)
		return n;
	for (int k = n - 1; n > 0; n--, k--) {
		int pos = g_bitPos;
		if (g_bitStream[pos >> 3] & (u8)(1 << (7 - (pos & 7))))
			*out |= 1u << (k & 31);
		g_bitPos = pos + 1;
	}
	return g_bitPos;
}

/* a value of n bits: the top bit clear means negative (out - 2^n + 1) */
static void huff_value(int *out, int n)
{
	if (n <= 0) {
		*out = 0;
		return;
	}
	ptx_46f230(out, n);
	if (!(*out & (1 << (n - 1))))
		*out = *out - (1 << n) + 1;
}

/* 0x46f190: a DC difference: 16 bits looked at, matched against the table's 16 codes (length, code), only the code's
   bits used, then the value of that many bits */
void (ptx_internal_46f190)(int *out)
{
	int v, len = 0, k;
	ptx_46f230(&v, 16);
	const int *code = (const int *)(0x4c5af0 + g_table * 96);
	for (k = 0; k < 16; k++, code += 2) {
		len = code[0];
		if (v >> ((16 - len) & 31) == code[1])
			break;
	}
	g_bitPos += len - 16;
	huff_value(out, k);
}

/* 0x46f2a0: an AC symbol (256 codes, empty ones skipped): the zeros before it (run) and the value's size */
void (ptx_internal_46f2a0)(int *out, int *run)
{
	int v, len = 0, k;
	ptx_46f230(&v, 16);
	const int *code = (const int *)(0x4c5bb0 + (g_table << 11));
	for (k = 0; k < 256; k++, code += 2) {
		len = code[0];
		if (len && v >> ((16 - len) & 31) == code[1])
			break;
	}
	*run = k >> 4;
	g_bitPos += len - 16;
	huff_value(out, k & 15);
}

/* 0x46f0b0: one block's 64 coefficients, in zigzag order up to the end-of-block symbol; returns the position */
int (ptx_internal_46f0b0)(int *block)
{
	int dc, value, run, k = 1;
	memset(block, 0, 64 * 4);
	ptx_internal_46f190(&dc);
	block[0] = g_lastDc + dc;
	g_lastDc += dc;
	do {
		ptx_internal_46f2a0(&value, &run);
		if (!run && !value) {
			for (; k < 64; k++)
				block[g_zigzag[k]] = 0;
			break;
		}
		while (run-- > 0)
			block[g_zigzag[k++]] = 0;
		block[g_zigzag[k++]] = value;   /* (a run past 64 reads past the table, as in the original) */
	} while (k < 64);
	return g_bitPos;
}

/* the RGB of a pixel from its Y, Cb and Cr (16.16 tables for green) */
#define RED(Y, Cr) g_clamp[GAME_VAR(int, 0xaa228c + (Cr) * 4) + (Y)]
#define GREEN(Y, Cb, Cr) g_clamp[((GAME_VAR(int, 0xa6170c + (Cb) * 4) + GAME_VAR(int, 0xaa2690 + (Cr) * 4)) >> 16) + (Y)]
#define BLUE(Y, Cb) g_clamp[GAME_VAR(int, 0xa1f304 + (Cb) * 4) + (Y)]

/* 0x46e830: n pixels to RGB */
void (ptx_internal_46e830)(const u8 *y, u8 *dst, unsigned n)
{
	const u8 *cb = y + 0x10000, *cr = y + 0x20000;
	for (; n; n--) {
		int Y = *y++, Cb = *cb++, Cr = *cr++;
		*dst++ = RED(Y, Cr);
		*dst++ = GREEN(Y, Cb, Cr);
		*dst++ = BLUE(Y, Cb);
	}
}

/* 0x46e8e0: n pixels to RGBA (the alpha plane copied) */
void (ptx_internal_46e8e0)(const u8 *y, u8 *dst, unsigned n)
{
	const u8 *cb = y + 0x10000, *cr = y + 0x20000, *alpha = y + 0x30000;
	for (; n; n--) {
		int Y = *y++, Cb = *cb++, Cr = *cr++, A = *alpha++;
		*dst++ = RED(Y, Cr);
		*dst++ = GREEN(Y, Cb, Cr);
		*dst++ = BLUE(Y, Cb);
		*dst++ = (u8)A;
	}
}

/* 0x46ea30: the 8 x 8 blocks (one after another, bpp bytes a pixel) laid out as w x h image rows */
void (ptx_internal_46ea30)(const u8 *src, u8 *dst, int w, int h, int bpp)
{
	if (h <= 0)
		return;
	int row = w * bpp, blockRow = bpp * 8;
	for (unsigned by = ((unsigned)h + 7) >> 3; by; by--, dst += row * 8) {
		if (w <= 0)
			continue;
		u8 *bd = dst;
		for (unsigned bx = ((unsigned)w + 7) >> 3; bx; bx--, bd += blockRow) {
			u8 *o = bd;
			for (int r = 0; r < 8; r++, o += row, src += blockRow)
				memcpy(o, src, blockRow);
		}
	}
}

/* ---- 0x46e380: one 8 x 8 block of coefficients to 8 x 8 bytes: libjpeg's jpeg_idct_ifast (AAN, 8-bit fixed point
   multiplies as (x * c) >> 8 in wrapping 32-bit ints, no rounding), with the quantisation table at 0xaa2c94 and the
   range limit table at the clamp table + 0x80 ---- */
static int idct_mul(int x, int c) { return (int)((u32)x * (u32)c) >> 8; }
#define Q(i) ((u32)(i))

void (ptx_decodeBlock_46e380)(const int *in, u8 *out)
{
	const int *quant = (const int *)0xaa2c94;
	const u8 *limit = g_clamp + 0x80;
	int ws[64];
	for (int c = 0; c < 8; c++) {   /* pass 1: the columns, dequantised */
		const int *i = in + c, *q = quant + c;
		int *w = ws + c;
		if (!i[8] && !i[16] && !i[24] && !i[32] && !i[40] && !i[48] && !i[56]) {
			int dc = (int)(Q(i[0]) * Q(q[0]));
			for (int r = 0; r < 8; r++)
				w[r * 8] = dc;
			continue;
		}
		int t0 = (int)(Q(i[0]) * q[0]), t1 = (int)(Q(i[16]) * q[16]);
		int t2 = (int)(Q(i[32]) * q[32]), t3 = (int)(Q(i[48]) * q[48]);
		int t10 = t0 + t2, t11 = t0 - t2, t13 = t1 + t3, t12 = idct_mul(t1 - t3, 362) - t13;
		t0 = t10 + t13;
		t3 = t10 - t13;
		t1 = t11 + t12;
		t2 = t11 - t12;
		int t4 = (int)(Q(i[8]) * q[8]), t5 = (int)(Q(i[24]) * q[24]);
		int t6 = (int)(Q(i[40]) * q[40]), t7 = (int)(Q(i[56]) * q[56]);
		int z13 = t6 + t5, z10 = t6 - t5, z11 = t4 + t7, z12 = t4 - t7;
		t7 = z11 + z13;
		int z5 = idct_mul(z10 + z12, 473);
		t6 = idct_mul(z10, -669) - t7 + z5;
		t5 = idct_mul(z11 - z13, 362) - t6;
		t4 = idct_mul(z12, 277) - z5 + t5;
		w[0] = t0 + t7;
		w[56] = t0 - t7;
		w[8] = t1 + t6;
		w[48] = t1 - t6;
		w[16] = t2 + t5;
		w[40] = t2 - t5;
		w[32] = t3 + t4;
		w[24] = t3 - t4;
	}
	for (int r = 0; r < 8; r++, out += 8) {   /* pass 2: the rows, descaled (>> 5) and range limited */
		const int *w = ws + r * 8;
		int t10 = w[0] + w[4], t11 = w[0] - w[4], t13 = w[2] + w[6], t12 = idct_mul(w[2] - w[6], 362) - t13;
		int t0 = t10 + t13, t3 = t10 - t13, t1 = t11 + t12, t2 = t11 - t12;
		int z13 = w[5] + w[3], z10 = w[5] - w[3], z11 = w[1] + w[7], z12 = w[1] - w[7];
		int t7 = z11 + z13, z5 = idct_mul(z10 + z12, 473);
		int t6 = idct_mul(z10, -669) - t7 + z5, t5 = idct_mul(z11 - z13, 362) - t6, t4 = idct_mul(z12, 277) - z5 + t5;
#define LIMIT(x) limit[((x) >> 5) & 0x3ff]
		out[0] = LIMIT(t0 + t7);
		out[7] = LIMIT(t0 - t7);
		out[1] = LIMIT(t1 + t6);
		out[6] = LIMIT(t1 - t6);
		out[2] = LIMIT(t2 + t5);
		out[5] = LIMIT(t2 - t5);
		out[4] = LIMIT(t3 + t4);
		out[3] = LIMIT(t3 - t4);
#undef LIMIT
	}
}
