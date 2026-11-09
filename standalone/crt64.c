/* crt64.c: the game's C runtime in the 64-bit build (PORTING.md, stage 6) - the entries the rebuilt code calls
   (src/crt_addrs.h CRT_ENTRIES, through g_crtFn), as Visual C++ 6's runtime behaves, on this system's C library:

   - the heap is the arena's (malloc, operator new ...: standalone/arena.c), so every block has a 32-bit address;
   - a FILE the game keeps is a small record in the arena holding this system's FILE (the game stores the pointer in its
     records); its own stdin / stdout / stderr (its _iob at 0x4d0838) are this system's; text mode as VC6's on every
     system (CR LF in the file, LF in the program);
   - printf formatting as VC6's: 'l' is 32 bits, "%e" has three exponent digits, -0.0 prints without its sign and a NaN
     or infinity as "1.#QNAN0" / "1.#INF00" (src/crt/crt_format.c's view of the doubles);
   - rand, atoi, itoa, strupr, strnicmp, tolower, strtok as VC6's (the C locale); atof the rebuild's (src/crt/crt_atof.c);
   - _findfirst / _findnext with VC6's _finddata_t and handles that fit 32 bits; _chdir / _mkdir on the game's paths.
   The entries are filled in by crt64_install (standalone/host64.c calls it). */
#if defined(__x86_64__) || defined(__aarch64__)
#define _GNU_SOURCE
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#include <direct.h>
#include <io.h>
#else
#include <sys/stat.h>
#include <unistd.h>
#endif

typedef uint32_t u32;
typedef uint8_t u8;
extern unsigned char *g_arena;
void *arena_malloc(size_t n);
void arena_free(void *p);
void *fn_ptr(u32 address);
void hlog(const char *fmt, ...);   /* host64.c */

#define AV_(p) ((p) ? (u32)((const u8 *)(p) - g_arena) : 0u)

/* ---- files */
#define FILE_MAGIC 0x46584147u   /* "GAXF" */
typedef struct { u32 magic; u32 text; FILE *f; } GFile;
#define IOB 0x4d0838u   /* the game's own _iob: stdin, stdout, stderr (0x20 bytes each) */

static FILE *host_file(void *h, int *text)
{
	*text = 0;
	if (!h)
		return NULL;
	u32 a = AV_(h);
	if (a - IOB < 0x60 && a % 0x20 == 0)
		return a == IOB ? stdin : a == IOB + 0x20 ? stdout : stderr;
	GFile *g = h;
	if (g->magic != FILE_MAGIC) {
		hlog("crt: a FILE the runtime did not open (%p)\n", h);
		return NULL;
	}
	*text = (int)g->text;
	return g->f;
}

#ifndef _WIN32
int plat_path(const char *in, char *out, size_t room);   /* plat/posix/files.c: the game's path on this system */
FILE *plat_fopen(const char *path, const char *mode);
int plat_mkdir(const char *path);
int plat_chdir(const char *path);
intptr_t plat_findfirst(const char *pattern, void *data);
int plat_findnext(intptr_t handle, void *data);
int plat_findclose(intptr_t handle);
#endif

static void *c_fopen(const char *name, const char *mode)
{
	char m[8];
	int n = 0, text = 1;
	for (const char *p = mode; *p && n < 6; p++) {
		if (*p == 'b') text = 0;
		if (*p == 't') continue;
		m[n++] = *p;
	}
	if (text)
		m[n++] = 'b';   /* (opened binary: text mode is done here, as VC6's) */
	m[n] = 0;
#ifdef _WIN32
	FILE *f = fopen(name, m);
#else
	FILE *f = plat_fopen(name, m);
#endif
	if (!f) {
		static int logged;
		if (logged++ < 40)
			hlog("crt: fopen(\"%s\", \"%s\") failed\n", name, mode);
		return NULL;
	}
	GFile *g = arena_malloc(sizeof *g);
	if (!g) {
		fclose(f);
		return NULL;
	}
	g->magic = FILE_MAGIC;
	g->text = (u32)text;
	g->f = f;
	return g;
}
static int c_fclose(void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	if (!f)
		return -1;
	if (f == stdin || f == stdout || f == stderr)
		return 0;
	int r = fclose(f);
	((GFile *)h)->magic = 0;
	arena_free(h);
	return r;
}
static u32 c_fread(void *p, u32 size, u32 count, void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	if (!f || !size)
		return 0;
	if (!text)
		return (u32)fread(p, size, count, f);
	/* text: CR LF read as LF, a lone CR kept, ^Z the end (VC6's _read) */
	u8 *o = p;
	size_t want = (size_t)size * count, got = 0;
	while (got < want) {
		int c = fgetc(f);
		if (c == EOF || c == 0x1a)
			break;
		if (c == '\r') {
			int d = fgetc(f);
			if (d == '\n')
				c = '\n';
			else if (d != EOF)
				ungetc(d, f);
		}
		o[got++] = (u8)c;
	}
	return (u32)(got / size);
}
static size_t put_text(const void *p, size_t n, FILE *f)
{
	const u8 *b = p;
	size_t done = 0;
	for (; done < n; done++) {
		if (b[done] == '\n' && fputc('\r', f) == EOF)
			break;
		if (fputc(b[done], f) == EOF)
			break;
	}
	return done;
}
static u32 c_fwrite(const void *p, u32 size, u32 count, void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	if (!f || !size)
		return 0;
	if (!text)
		return (u32)fwrite(p, size, count, f);
	return (u32)(put_text(p, (size_t)size * count, f) / size);
}
static int c_fseek(void *h, int offset, int origin)
{
	int text;
	FILE *f = host_file(h, &text);
	return f ? fseek(f, offset, origin) : -1;
}
static int c_ftell(void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	return f ? (int)ftell(f) : -1;
}
static char *c_fgets(char *s, int n, void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	if (!f || n <= 0)
		return NULL;
	int i = 0;
	while (i < n - 1) {
		int c = fgetc(f);
		if (c == EOF || (text && c == 0x1a))
			break;
		if (text && c == '\r') {
			int d = fgetc(f);
			if (d == '\n')
				c = '\n';
			else if (d != EOF)
				ungetc(d, f);
		}
		s[i++] = (char)c;
		if (c == '\n')
			break;
	}
	if (!i)
		return NULL;
	s[i] = 0;
	return s;
}
static int c_fputs(const char *s, void *h)
{
	int text;
	FILE *f = host_file(h, &text);
	if (!f)
		return -1;
	size_t n = strlen(s);
	return (text ? put_text(s, n, f) : fwrite(s, 1, n, f)) == n ? 0 : -1;
}

/* ---- printf as VC6's: each conversion's argument fetched by its own type, formatted here or by snprintf */
typedef struct { char *buf; size_t len, cap; } Out;
static void out_put(Out *o, const char *s, size_t n)
{
	if (o->len + n + 1 > o->cap) {
		size_t c = o->cap ? o->cap * 2 : 256;
		while (c < o->len + n + 1)
			c *= 2;
		o->buf = realloc(o->buf, c);
		o->cap = c;
	}
	memcpy(o->buf + o->len, s, n);
	o->len += n;
	o->buf[o->len] = 0;
}
/* "e+00" -> "e+000" (VC6 writes three exponent digits) */
static void three_digit_exponent(char *s, size_t room)
{
	char *e = strpbrk(s, "eE");
	if (!e || (e[1] != '+' && e[1] != '-'))
		return;
	char *d = e + 2;
	size_t digits = strspn(d, "0123456789");
	if (digits >= 3 || strlen(s) + 1 + (3 - digits) > room)
		return;
	memmove(d + (3 - digits), d, strlen(d) + 1);
	memset(d, '0', 3 - digits);
}
static void special_double(char *out, size_t room, double v, int prec, int upper)
{
	(void)upper;
	const char *body = isinf(v) ? "1.#INF" : (signbit(v) ? "1.#IND" : "1.#QNAN");
	char tmp[64];
	snprintf(tmp, sizeof tmp, "%s%s", signbit(v) && isinf(v) ? "-" : (isnan(v) && signbit(v) ? "-" : ""), body);
	/* (padded with zeros to the precision after the point, as VC6 shows "1.#QNAN0" for %f) */
	const char *dot = strchr(tmp, '.');
	int have = (int)strlen(dot + 1);
	if (prec < 0)
		prec = 6;
	size_t n = strlen(tmp);
	for (int i = have; i < prec && n + 1 < sizeof tmp; i++)
		tmp[n++] = '0';
	tmp[n] = 0;
	snprintf(out, room, "%s", tmp);
}
static int vc6_format(Out *o, const char *fmt, va_list ap)
{
	for (const char *p = fmt; *p;) {
		if (*p != '%') {
			const char *q = strchr(p, '%');
			size_t n = q ? (size_t)(q - p) : strlen(p);
			out_put(o, p, n);
			p += n;
			continue;
		}
		const char *start = p++;
		if (*p == '%') {
			out_put(o, "%", 1);
			p++;
			continue;
		}
		char flags[8];
		int nf = 0;
		while (strchr("-+ #0", *p) && *p && nf < 7)
			flags[nf++] = *p++;
		flags[nf] = 0;
		int width = -1, prec = -1;
		if (*p == '*') {
			width = va_arg(ap, int);
			p++;
		} else if (isdigit((u8)*p)) {
			width = (int)strtol(p, (char **)&p, 10);
		}
		if (*p == '.') {
			p++;
			if (*p == '*') {
				prec = va_arg(ap, int);
				p++;
			} else
				prec = (int)strtol(p, (char **)&p, 10);
		}
		int i64 = 0, half = 0;
		for (;;) {
			if (*p == 'h') { half = 1; p++; }
			else if (*p == 'l' || *p == 'L' || *p == 'F' || *p == 'N' || *p == 'w') p++;
			else if (p[0] == 'I' && p[1] == '6' && p[2] == '4') { i64 = 1; p += 3; }
			else if (p[0] == 'I' && p[1] == '3' && p[2] == '2') p += 3;
			else break;
		}
		char conv = *p;
		if (!conv)
			break;
		p++;
		/* the spec for snprintf: flags, width, precision as given, the size as this C library wants it */
		char spec[48];
		int n = snprintf(spec, sizeof spec, "%%%s", flags);
		if (width >= 0) n += snprintf(spec + n, sizeof spec - n, "%d", width);
		if (prec >= 0) n += snprintf(spec + n, sizeof spec - n, ".%d", prec);
		char piece[512];
		piece[0] = 0;
		switch (conv) {
		case 'd': case 'i': case 'o': case 'u': case 'x': case 'X':
			if (i64) {
				snprintf(spec + n, sizeof spec - n, "ll%c", conv);
				long long v = va_arg(ap, long long);
				snprintf(piece, sizeof piece, spec, v);
			} else {
				snprintf(spec + n, sizeof spec - n, "%c", conv);
				int v = va_arg(ap, int);
				if (half)
					v = conv == 'd' || conv == 'i' ? (short)v : (unsigned short)v;
				snprintf(piece, sizeof piece, spec, v);
			}
			break;
		case 'c': case 'C':
			snprintf(spec + n, sizeof spec - n, "c");
			snprintf(piece, sizeof piece, spec, va_arg(ap, int));
			break;
		case 's': case 'S': {
			const char *s = va_arg(ap, const char *);
			snprintf(spec + n, sizeof spec - n, "s");
			/* (a long string: formatted straight into the output) */
			char *big = NULL;
			int len = snprintf(NULL, 0, spec, s ? s : "(null)");
			if (len >= (int)sizeof piece) {
				big = malloc((size_t)len + 1);
				snprintf(big, (size_t)len + 1, spec, s ? s : "(null)");
				out_put(o, big, (size_t)len);
				free(big);
				continue;
			}
			snprintf(piece, sizeof piece, spec, s ? s : "(null)");
			break;
		}
		case 'p': {
			const void *v = va_arg(ap, const void *);
			snprintf(piece, sizeof piece, "%08X", AV_(v));   /* (VC6: eight hex digits; the game's address) */
			break;
		}
		case 'n': {
			int *v = va_arg(ap, int *);
			if (v)
				*v = (int)o->len;
			break;
		}
		case 'e': case 'E': case 'f': case 'g': case 'G': {
			double v = va_arg(ap, double);
			if (v == 0 && signbit(v))
				v = 0;   /* (VC6 prints -0.0 without its sign) */
			if (isnan(v) || isinf(v)) {
				char sp[64];
				special_double(sp, sizeof sp, v, prec, conv == 'E' || conv == 'G');
				char s2[16];
				snprintf(s2, sizeof s2, "%%%s%s*s", flags, strchr(flags, '-') ? "" : "");
				snprintf(piece, sizeof piece, width >= 0 ? (strchr(flags, '-') ? "%-*s" : "%*s") : "%.0s%s", width >= 0 ? width : 0, sp);
				break;
			}
			snprintf(spec + n, sizeof spec - n, "%c", conv);
			snprintf(piece, sizeof piece, spec, v);
			if (conv != 'f')
				three_digit_exponent(piece, sizeof piece);
			break;
		}
		default:   /* (an unknown conversion: printed as it stands, as VC6 does) */
			out_put(o, start, (size_t)(p - start));
			continue;
		}
		out_put(o, piece, strlen(piece));
	}
	return (int)o->len;
}
int crt64_vsprintf(char *out, const char *fmt, va_list ap)
{
	Out o = { 0 };
	va_list a;
	va_copy(a, ap);
	vc6_format(&o, fmt, a);
	va_end(a);
	if (o.buf)
		memcpy(out, o.buf, o.len + 1);
	else
		out[0] = 0;
	free(o.buf);
	return (int)o.len;
}
static int c_sprintf(char *out, const char *fmt, ...)
{
	va_list a;
	va_start(a, fmt);
	int n = crt64_vsprintf(out, fmt, a);
	va_end(a);
	return n;
}
static int c_vfprintf(void *h, const char *fmt, va_list ap)
{
	int text;
	FILE *f = host_file(h, &text);
	Out o = { 0 };
	va_list a;
	va_copy(a, ap);
	vc6_format(&o, fmt, a);
	va_end(a);
	int n = (int)o.len;
	if (f && o.buf)
		text ? put_text(o.buf, o.len, f) : fwrite(o.buf, 1, o.len, f);
	free(o.buf);
	return f ? n : -1;
}
static int c_fprintf(void *h, const char *fmt, ...)
{
	va_list a;
	va_start(a, fmt);
	int n = c_vfprintf(h, fmt, a);
	va_end(a);
	return n;
}

/* ---- strings */
static char *c_strncpy(char *d, const char *s, int n) { return strncpy(d, s, (size_t)(unsigned)n); }
static int c_atoi(const char *s)
{
	while (*s == ' ' || (*s >= 9 && *s <= 13))
		s++;
	int neg = *s == '-';
	if (*s == '-' || *s == '+')
		s++;
	u32 v = 0;
	while (*s >= '0' && *s <= '9')
		v = v * 10 + (u32)(*s++ - '0');
	return (int)(neg ? 0u - v : v);
}
static char *g_strtokNext;
static char *c_strtok(char *s, const char *delims)
{
	if (!s)
		s = g_strtokNext;
	if (!s)
		return NULL;
	s += strspn(s, delims);
	if (!*s) {
		g_strtokNext = NULL;
		return NULL;
	}
	char *e = s + strcspn(s, delims);
	if (*e)
		*e++ = 0;
	g_strtokNext = e;
	return s;
}
static char *c_strupr(char *s)
{
	for (char *p = s; *p; p++)
		if (*p >= 'a' && *p <= 'z')
			*p -= 32;
	return s;
}
static char *c_itoa(int v, char *out, int radix)
{
	char tmp[40];
	int n = 0, neg = radix == 10 && v < 0;
	u32 u = neg ? 0u - (u32)v : (u32)v;
	if (radix < 2 || radix > 36) {
		out[0] = 0;
		return out;
	}
	do {
		u32 d = u % (u32)radix;
		tmp[n++] = (char)(d < 10 ? '0' + d : 'a' + d - 10);
		u /= (u32)radix;
	} while (u);
	char *o = out;
	if (neg)
		*o++ = '-';
	while (n)
		*o++ = tmp[--n];
	*o = 0;
	return out;
}
static int c_strncmp(const char *a, const char *b, u32 n) { return strncmp(a, b, n); }
static int c_tolower(int c) { return c >= 'A' && c <= 'Z' ? c + 32 : c; }
static char *c_strstr(const char *h, const char *n) { return strstr(h, n); }
static int c_strnicmp(const char *a, const char *b, u32 n)
{
	for (; n; n--, a++, b++) {
		int x = c_tolower((u8)*a), y = c_tolower((u8)*b);
		if (x != y)
			return x - y;
		if (!x)
			break;
	}
	return 0;
}

/* ---- the heap, exit, rand */
static void *c_malloc(u32 n) { return arena_malloc(n); }
static u32 c_free(void *p) { arena_free(p); return 0; }
static void c_delete(void *p) { arena_free(p); }
static void *c_new(u32 n) { return arena_malloc(n ? n : 1); }
#define MAX_ATEXIT 64
static void (*g_atexit[MAX_ATEXIT])(void);
static int g_natexit;
static int c_atexit(void (*f)(void))
{
	if (g_natexit == MAX_ATEXIT)
		return -1;
	g_atexit[g_natexit++] = f;
	return 0;
}
/* the game's exit list, last first (its static destructors) */
void crt64_runExitList(void)
{
	while (g_natexit > 0)
		g_atexit[--g_natexit]();
}
static void c_exit(int code)
{
	hlog("exit(%d)\n", code);
	crt64_runExitList();
	exit(code);
}
static u32 g_holdrand = 1;
static int c_rand(void)
{
	g_holdrand = g_holdrand * 214013u + 2531011u;
	return (int)(g_holdrand >> 16 & 0x7fff);
}
static int c_ftol(double x) { return (int)(long long)x; }

/* ---- the compiler's array helpers: the constructor / destructor as functions the game holds (FN numbers) */
static void c_vectorConstruct(u8 *first, int size, int count, u32 ctor, u32 dtor)
{
	(void)dtor;
	void (*f)(void *) = (void (*)(void *))fn_ptr(ctor);
	for (int i = 0; i < count; i++, first += size)
		f(first);
}
static void c_vectorDestruct(u8 *first, int size, int count, u32 dtor)
{
	void (*f)(void *) = (void (*)(void *))fn_ptr(dtor);
	for (u8 *p = first + size * count; count-- > 0;) {
		p -= size;
		f(p);
	}
}

/* ---- directories and file searches: VC6's _finddata_t (no pointers in it); handles 1 .. 64 */
#ifdef _WIN32
#pragma pack(push, 4)
typedef struct { u32 attrib; u32 time_create, time_access, time_write; u32 size; char name[260]; } FindData;
#pragma pack(pop)
static HANDLE g_finds[64];
static void fill_find(FindData *d, const WIN32_FIND_DATAA *w)
{
	memset(d, 0, sizeof *d);
	d->attrib = w->dwFileAttributes;
	d->size = w->nFileSizeLow;
	snprintf(d->name, sizeof d->name, "%s", w->cFileName);
}
static int c_findfirst(const char *pattern, void *data)
{
	WIN32_FIND_DATAA w;
	HANDLE h = FindFirstFileA(pattern, &w);
	if (h == INVALID_HANDLE_VALUE)
		return -1;
	for (int i = 0; i < 64; i++)
		if (!g_finds[i]) {
			g_finds[i] = h;
			fill_find(data, &w);
			return i + 1;
		}
	FindClose(h);
	return -1;
}
static int c_findnext(int handle, void *data)
{
	WIN32_FIND_DATAA w;
	if (handle < 1 || handle > 64 || !g_finds[handle - 1] || !FindNextFileA(g_finds[handle - 1], &w))
		return -1;
	fill_find(data, &w);
	return 0;
}
static int c_findclose(int handle)
{
	if (handle < 1 || handle > 64 || !g_finds[handle - 1])
		return -1;
	FindClose(g_finds[handle - 1]);
	g_finds[handle - 1] = NULL;
	return 0;
}
static int c_chdir(const char *p) { return _chdir(p); }
static int c_mkdir(const char *p) { return _mkdir(p); }
#else
static intptr_t g_finds[64];
static int c_findfirst(const char *pattern, void *data)
{
	intptr_t h = plat_findfirst(pattern, data);
	if (h == -1)
		return -1;
	for (int i = 0; i < 64; i++)
		if (!g_finds[i]) {
			g_finds[i] = h;
			return i + 1;
		}
	plat_findclose(h);
	return -1;
}
static int c_findnext(int handle, void *data)
{
	if (handle < 1 || handle > 64 || !g_finds[handle - 1])
		return -1;
	return plat_findnext(g_finds[handle - 1], data);
}
static int c_findclose(int handle)
{
	if (handle < 1 || handle > 64 || !g_finds[handle - 1])
		return -1;
	int r = plat_findclose(g_finds[handle - 1]);
	g_finds[handle - 1] = 0;
	return r;
}
static int c_chdir(const char *p) { return plat_chdir(p); }
static int c_mkdir(const char *p) { return plat_mkdir(p); }
#endif

/* _CIacos (unused here: src/render/rotations.c computes it itself in the 64-bit build) */
static double c_CIacos(double x) { return acos(x); }

double crt_atof(const char *s);   /* src/crt/crt_atof.c */

/* every entry filled, in src/crt_addrs.h's order; the number filled */
#include "../src/crt_addrs.h"
enum { CRTIX_NONE_ = -1
#define CRT_IX_(n) , CRTIX_##n
CRT_ENTRIES(CRT_IX_)
#undef CRT_IX_
, CRT_COUNT_ };
extern void *g_crtFn[CRT_COUNT_];
void *g_crtFn[CRT_COUNT_];
int crt64_install(void)
{
#define SET(n, f) g_crtFn[CRTIX_##n] = (void *)(f)
	SET(fclose, c_fclose); SET(fread, c_fread); SET(fseek, c_fseek); SET(fopen, c_fopen); SET(sprintf, c_sprintf);
	SET(strncpy, c_strncpy); SET(atoi, c_atoi); SET(ftol, c_ftol); SET(strtok, c_strtok); SET(fgets, c_fgets);
	SET(vsprintf, crt64_vsprintf); SET(exit, c_exit); SET(free, c_free); SET(malloc, c_malloc);
	SET(operator_delete, c_delete); SET(atexit, c_atexit); SET(ftell, c_ftell); SET(fprintf, c_fprintf);
	SET(fputs, c_fputs); SET(operator_new, c_new); SET(fwrite, c_fwrite); SET(findfirst, c_findfirst);
	SET(findnext, c_findnext); SET(findclose, c_findclose); SET(chdir, c_chdir); SET(rand, c_rand); SET(mkdir, c_mkdir);
	SET(strupr, c_strupr); SET(itoa, c_itoa); SET(strncmp, c_strncmp); SET(vectorDestruct, c_vectorDestruct);
	SET(vectorConstruct, c_vectorConstruct); SET(tolower, c_tolower); SET(atof, crt_atof); SET(vfprintf, c_vfprintf);
	SET(CIacos, c_CIacos); SET(strstr, c_strstr); SET(strnicmp, c_strnicmp);
#undef SET
	int n = 0;
	for (int i = 0; i < CRT_COUNT_; i++)
		n += g_crtFn[i] != NULL;
	return n == CRT_COUNT_ ? n : -(CRT_COUNT_ - n);
}
#endif
