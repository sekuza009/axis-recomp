/* math_tables.c: MATHFUNC.TBL, the game's lookup tables: sine, cosine and tangent in 0.1 degree steps (3600 each),
   4096 rand() values, and the tangents of -85..85 degrees in 10 degree steps. Made with the x87's own fsin / fcos /
   fptan, so the tables are exactly the game's. */
#include "../game.h"

#define SIN_TABLE ((float *)IMG(0xa1b778))
#define COS_TABLE ((float *)IMG(0xa17f38))
#define TAN_TABLE ((float *)IMG(0xa146f8))
#define RAND_TABLE ((int *)IMG(0xa106f8))
#define TAN10_TABLE ((float *)IMG(0xa106b0))
#define TABLE_FILE ((const char *)STR(0x4c575c, "MATHFUNC.TBL"))

#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

static inline long double x87_fsin(long double x) { __asm__("fsin" : "+t"(x)); return x; }
static inline long double x87_fcos(long double x) { __asm__("fcos" : "+t"(x)); return x; }
static inline long double x87_fptan(long double x) { __asm__("fptan\n\tfstp %%st(0)" : "+t"(x)); return x; }

/* 0x46c340: the tables computed and written to the file (missing it is fatal). The tangent is the sine as stored
   (a float) over the cosine before it is rounded. Returns fclose's eax */
u32 (math_makeMathFunctionTableFile)(void)
{
	for (int i = 0; i < 3600; i++) {
		long double angle = (long double)i * k_tenthDegreeRad;   /* 0.1 degree in radians */
		float s = f32(x87_fsin(angle));
		SIN_TABLE[i] = s;
		long double c = x87_fcos(angle);
		COS_TABLE[i] = (float)c;
		TAN_TABLE[i] = (float)((long double)s / c);
	}
	for (int i = 0; i < 4096; i++)
		RAND_TABLE[i] = crt_rand();
	void *f = crt_fopen(TABLE_FILE, (const char *)STR(0x4b2ab0, "wb"));
	if (!f)
		sys_errorTerminate((const char *)STR(0x4c576c, "can't open file MATHFFUNC.TBL in make..."));
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
	void *f = crt_fopen(TABLE_FILE, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		GAME_FN(math_makeMathFunctionTableFile, 0x46c340, u32, void)();   /* math_makeMathFunctionTableFile */
	f = crt_fopen(TABLE_FILE, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_errorTerminate((const char *)STR(0x4c5728, "can't open file MATHFUNC.TBL in initM..."));
	crt_fread(SIN_TABLE, 4, 3600, f);
	crt_fread(COS_TABLE, 4, 3600, f);
	crt_fread(TAN_TABLE, 4, 3600, f);
	crt_fread(RAND_TABLE, 4, 4096, f);
	fclose(f);
	int degrees = 85;
	float *out = TAN10_TABLE;
	do {
		*out++ = (float)x87_fptan((long double)degrees * k_degToRad);   /* degrees in radians */
		degrees -= 10;
	} while (degrees > -95);
	return degrees;
}
