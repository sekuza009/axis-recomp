/* crt_format.c: printf formatting as the game's runtime does it (0x49e9dd sprintf, 0x49ed2e vsprintf, and its file
   versions), on msvcrt.dll's. The two print the same for every value but two kinds of double: VC6 prints -0.0
   without its sign ("0.00", "+0.0") and a signalling NaN as a quiet one ("1.#QNAN"), where msvcrt keeps the sign and
   prints "1.#SNAN". So the arguments are copied with those doubles changed (to +0.0, and the NaN quieted), the copy
   handed to msvcrt. The format is read as VC6's _output reads it, to find the doubles among the arguments. */
#include "crt.h"
#include "../game.h"

const CrtLib *g_crtLib;
void crt_setLib(const CrtLib *lib) { g_crtLib = lib; }

/* the dwords of the arguments format takes, with each double's place marked (1 at its low dword) */
static int scan(const char *format, u8 *isDouble, int room)
{
	int n = 0;
	for (const char *p = format; *p; p++) {
		if (*p != '%')
			continue;
		p++;
		while (*p == '-' || *p == '+' || *p == ' ' || *p == '#' || *p == '0')
			p++;
		if (*p == '*') {
			n++;
			p++;
		} else {
			while (*p >= '0' && *p <= '9')
				p++;
		}
		if (*p == '.') {
			p++;
			if (*p == '*') {
				n++;
				p++;
			} else {
				while (*p >= '0' && *p <= '9')
					p++;
			}
		}
		int isInt64 = 0;
		for (;;) {
			if (*p == 'h' || *p == 'l' || *p == 'L' || *p == 'F' || *p == 'N' || *p == 'w')
				p++;
			else if (p[0] == 'I' && p[1] == '6' && p[2] == '4')
				p += 3, isInt64 = 1;
			else
				break;
		}
		if (!*p)
			break;
		switch (*p) {
		case 'e': case 'E': case 'f': case 'g': case 'G':
			if (n + 1 < room)
				isDouble[n] = 1;
			n += 2;
			break;
		case 'd': case 'i': case 'o': case 'u': case 'x': case 'X':
			n += isInt64 ? 2 : 1;
			break;
		case 'c': case 'C': case 's': case 'S': case 'Z': case 'p': case 'n':
			n++;
			break;
		}
	}
	return n < room ? n : room;
}

void crt_fixArgs(const char *format, const u32 *args, u32 *out, int room)
{
	u8 isDouble[64] = { 0 };
	int n = scan(format, isDouble, room < 64 ? room : 64);
	for (int i = 0; i < n; i++)
		out[i] = args[i];
	for (int i = 0; i + 1 < n; i++) {
		if (!isDouble[i])
			continue;
		u32 lo = out[i], hi = out[i + 1];
		if (lo == 0 && hi == 0x80000000u)   /* -0.0 */
			out[i + 1] = 0;
		else if ((hi & 0x7ff00000u) == 0x7ff00000u && ((hi & 0xfffff) | lo) && !(hi & 0x80000))   /* a signalling NaN */
			out[i + 1] = hi | 0x80000;
	}
}

/* 0x49ed2e: vsprintf as VC6's */
int (crt_vsprintf)(char *out, const char *format, va_list args)
{
#ifdef AXIS_64   /* (the 64-bit build: the arguments are this system's; crt64.c's runtime formats them as VC6's) */
	return g_crtLib->vsprintf_(out, format, args);
#else
	u32 copy[64];
	crt_fixArgs(format, (const u32 *)args, copy, 64);
	return g_crtLib->vsprintf_(out, format, (va_list)copy);
#endif
}

/* 0x49e9dd: sprintf as VC6's */
int (crt_sprintf)(char *out, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int n = vsprintf(out, format, args);   /* (0x49ed2e: crt_vsprintf in the standalone build) */
	va_end(args);
	return n;
}
