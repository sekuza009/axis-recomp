/* math_tables.c: MATHFUNC.TBL, the game's lookup tables: sine, cosine and tangent in 0.1 degree steps (3600 each),
   4096 rand() values, and the tangents of -85..85 degrees in 10 degree steps. Made with the x87's own fsin / fcos /
   fptan, so the tables are exactly the game's. */
#include "../game.h"

#define SIN_TABLE ((float *)0xa1b778)
#define COS_TABLE ((float *)0xa17f38)
#define TAN_TABLE ((float *)0xa146f8)
#define RAND_TABLE ((int *)0xa106f8)
#define TAN10_TABLE ((float *)0xa106b0)
#define TABLE_FILE ((const char *)0x4c575c)   /* "MATHFUNC.TBL" */

#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define crt_rand() GAME_CDECL(0x49f92c, int, void)()
#define sys_errorTerminate(message) GAME_CDECL(0x46c950, void, const char *)(message)

static inline long double x87_fsin(long double x) { __asm__("fsin" : "+t"(x)); return x; }
static inline long double x87_fcos(long double x) { __asm__("fcos" : "+t"(x)); return x; }
static inline long double x87_fptan(long double x) { __asm__("fptan\n\tfstp %%st(0)" : "+t"(x)); return x; }

/* 0x46c340: the tables computed and written to the file (missing it is fatal). The tangent is the sine as stored
   (a float) over the cosine before it is rounded. Returns fclose's eax */
u32 (math_makeMathFunctionTableFile)(void)
{
	for (int i = 0; i < 3600; i++) {
		long double angle = (long double)i * GAME_VAR(double, 0x4aa298);   /* 0.1 degree in radians */
		float s = f32(x87_fsin(angle));
		SIN_TABLE[i] = s;
		long double c = x87_fcos(angle);
		COS_TABLE[i] = (float)c;
		TAN_TABLE[i] = (float)((long double)s / c);
	}
	for (int i = 0; i < 4096; i++)
		RAND_TABLE[i] = crt_rand();
	void *f = crt_fopen(TABLE_FILE, (const char *)0x4b2ab0);
	if (!f)
		sys_errorTerminate((const char *)0x4c576c);
	crt_fwrite(SIN_TABLE, 4, 3600, f);
	crt_fwrite(COS_TABLE, 4, 3600, f);
	crt_fwrite(TAN_TABLE, 4, 3600, f);
	crt_fwrite(RAND_TABLE, 4, 4096, f);
	return fclose(f);
}

/* 0x46c270: the tables read from the file (made first when it is missing; still missing is fatal), then the
   tangents of 85, 75 .. -85 degrees. Returns what the original leaves in eax (the loop counter, -95) */
int (math_initMathFunction)(void)
{
	void *f = crt_fopen(TABLE_FILE, (const char *)0x4ad170);
	if (!f)
		GAME_CDECL(0x46c340, u32, void)();   /* math_makeMathFunctionTableFile */
	f = crt_fopen(TABLE_FILE, (const char *)0x4ad170);
	if (!f)
		sys_errorTerminate((const char *)0x4c5728);
	crt_fread(SIN_TABLE, 4, 3600, f);
	crt_fread(COS_TABLE, 4, 3600, f);
	crt_fread(TAN_TABLE, 4, 3600, f);
	crt_fread(RAND_TABLE, 4, 4096, f);
	fclose(f);
	int degrees = 85;
	float *out = TAN10_TABLE;
	do {
		*out++ = (float)x87_fptan((long double)degrees * GAME_VAR(double, 0x4aa290));   /* degrees in radians */
		degrees -= 10;
	} while (degrees > -95);
	return degrees;
}
