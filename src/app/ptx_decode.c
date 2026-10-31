/* ptx_decode.c: the PTX video decoder (the intro films), JPEG-style: a bit stream read most significant bit first,
   Huffman-coded DC differences and AC run / size symbols for each 8 x 8 block of coefficients in zigzag order, then
   the decoded planes (Y, Cb, Cr and alpha, 0x10000 bytes apart) turned into RGB(A) through the tables of
   ptx_tables.c, and the 8 x 8 blocks laid out as image rows. */
#include <stdarg.h>
#include "../game.h"
#include <string.h>

#define g_bitPos GAME_VAR(int, 0xa21704)          /* the stream position, in bits */
#define g_bitStream GAME_VAR(const u8 *, 0xa61708)
#define g_table GAME_VAR(int, 0xaa2e94)           /* the Huffman table set in use */
#define g_lastDc GAME_VAR(int, 0xaa268c)          /* the block's DC is a difference from the one before */
#define g_zigzag ((const int *)0x4c59ec)
#define g_clamp GAME_VAR(const u8 *, 0xa1f300)

/* 0x46f230: *out = the next n bits; returns the new position */
int (ptx_readBits)(int *out, int n)
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
	ptx_readBits(out, n);
	if (!(*out & (1 << (n - 1))))
		*out = *out - (1 << n) + 1;
}

/* 0x46f190: a DC difference: 16 bits looked at, matched against the table's 16 codes (length, code), only the code's
   bits used, then the value of that many bits */
void (ptx_readDcDiff)(int *out)
{
	int v, len = 0, k;
	ptx_readBits(&v, 16);
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
void (ptx_readAcSymbol)(int *out, int *run)
{
	int v, len = 0, k;
	ptx_readBits(&v, 16);
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
int (ptx_readBlock)(int *block)
{
	int dc, value, run, k = 1;
	memset(block, 0, 64 * 4);
	ptx_readDcDiff(&dc);
	block[0] = g_lastDc + dc;
	g_lastDc += dc;
	do {
		ptx_readAcSymbol(&value, &run);
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
void (ptx_toRgb)(const u8 *y, u8 *dst, unsigned n)
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
void (ptx_toRgba)(const u8 *y, u8 *dst, unsigned n)
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
void (ptx_layoutBlocks)(const u8 *src, u8 *dst, int w, int h, int bpp)
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

/* 0x46e1e0: a video decoder error: "<name of the current stage (0xaef35c)>" and the message (when there is one) to
   stderr; a non-zero code exits with it. Returns the code */
int (ptx_crtlError)(int code, const char *format, ...)
{
	void *err = (void *)0x4d0878;   /* stderr */
	((int (CDECL *)(void *, const char *, ...))0x49f135)(err, (const char *)0x4b182c);
	((int (CDECL *)(void *, const char *, ...))0x49f135)(err, (const char *)0x4c6fc0, GAME_VAR(u32, 0x4d0780 + GAME_VAR(int, 0xaef35c) * 4));
	if (format && strlen(format)) {
		((int (CDECL *)(void *, const char *, ...))0x49f135)(err, (const char *)0x4c6fb0);
		va_list args;
		va_start(args, format);
		GAME_CDECL(0x49fec7, int, void *, const char *, va_list)(err, format, args);   /* vfprintf */
		va_end(args);
	}
	if (code)
		GAME_CDECL(0x49edac, void, int)(code);   /* exit */
	return code;
}

/* 0x46e260: a video error: "<header>" and the message to stderr; a non-zero code exits with it. Returns the code */
int (ptx_error)(int code, const char *format, ...)
{
	void *err = (void *)0x4d0878;   /* stderr */
	((int (CDECL *)(void *, const char *, ...))0x49f135)(err, (const char *)0x4b182c);
	((int (CDECL *)(void *, const char *, ...))0x49f135)(err, (const char *)0x4c6fd0);
	va_list args;
	va_start(args, format);
	GAME_CDECL(0x49fec7, int, void *, const char *, va_list)(err, format, args);   /* vfprintf */
	va_end(args);
	if (code)
		GAME_CDECL(0x49edac, void, int)(code);   /* exit */
	return code;
}

/* ---- a PTX image: a 16-byte header ("PTX\0", version 0x100, width / 8, height / 8, type 0x81 = YCbCr (3 planes,
   fmt 2) or 0x82 = YCbCrA (4 planes, fmt 3), quality), then up to 64 KB of Huffman-coded 8 x 8 DCT blocks, each plane
   byte-aligned (planes 1 and 2 use the second table pair, 0xaa2e94); the planes decoded into 0xa6228c (64 KB
   each), converted to RGB(A) at 0xa21708 and laid out as rows in out. A bad header is fatal (ptx_error) ---- */
#define ptx_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

static int ptx_read(void *f, u8 *out, int *fmt, int *width, int *height, int close)
{
	struct { char magic[4]; u16 version; short w, h, type, quality; u8 pad[6]; } head;
	ptx_fread(&head, 1, 0x10, f);
	if (head.magic[0] != 'P' || head.magic[1] != 'T' || head.magic[2] != 'X' || head.magic[3] != 0)
		ptx_error(-1, (const char *)0x4c6fec);
	if (head.version != 0x100)
		ptx_error(-1, (const char *)0x4c6fec);
	int w = head.w * 8, h = head.h * 8, planes;
	if (head.type == 0x81)
		planes = 3;
	else if (head.type == 0x82)
		planes = 4;
	else {
		ptx_error(-1, (const char *)0x4c6fd8);
		planes = -1;
	}
	ptx_initQuantTables(head.quality);
	u8 *data = (u8 *)0xaa2e98;
	ptx_fread(data, 1, 0x10000, f);
	int pos = 0, bits = 0;
	for (int p = 0; p < planes; p++) {
		if (p <= 3)
			GAME_VAR(int, 0xaa2e94) = p == 1 || p == 2;
		u8 *plane = (u8 *)0xa6228c + (p << 16);
		set_a61708_46f090(data + pos);
		if (w * h > 0)
			for (unsigned n = (unsigned)(w * h + 0x3f) >> 6; n; n--) {
				int block[64];
				bits = ptx_readBlock(block);
				ptx_decodeBlock_46e380(block, plane);
				plane += 0x40;
			}
		pos += (bits + 7) / 8;
	}
	if (close)
		fclose(f);
	if (head.type == 0x81)
		ptx_toRgb((const u8 *)0xa6228c, (u8 *)0xa21708, w * h);
	else if (head.type == 0x82)
		ptx_toRgba((const u8 *)0xa6228c, (u8 *)0xa21708, w * h);
	ptx_layoutBlocks((const u8 *)0xa21708, out, w, h, planes);
	*width = w;
	*height = h;
	if (head.type == 0x81) {
		*fmt = 2;
		return 0;
	}
	if (head.type == 0x82) {
		*fmt = 3;
		return 0;
	}
	return head.type - 0x82;
}

/* 0x46eb00: the image read from the file at path (a failed open is fatal: ptx_crtlError), which is closed before
   the conversion. Returns 0, or the type less 0x82 for an unknown type */
int (ptx_open)(const char *path, u8 *out, int *fmt, int *width, int *height)
{
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		ptx_crtlError(-1, (const char *)0x4b3fd8, path);
	return ptx_read(f, out, fmt, width, height, 1);
}

/* 0x46ed80: the image read from the open file f (left open) */
int (ptx_decode)(void *f, u8 *out, int *fmt, int *width, int *height)
{
	return ptx_read(f, out, fmt, width, height, 0);
}
