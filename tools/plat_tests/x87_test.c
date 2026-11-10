/* x87_test.c: src/x87.h and src/axis.h's float helpers checked where there is no x87 (arm64: their plain-C forms) against
   the x87's own results (tools/plat_tests/x87_expected.txt, made on x86-64 with -DMAKE_EXPECTED: the x87 instructions
   themselves). The results are compared as doubles, within a relative 1e-12 - the x87 computes at 80 bits, arm64 at 64,
   which is the precision the game sets the x87 to (53 bits) anyway. */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../src/x87.h"
#if !defined(__i386__) && !defined(__x86_64__)
static inline long double fld_m(const float *m) { return *m; }
static inline long double fmul_m(long double x, const float *m) { return x * *m; }
static inline long double fadd_m(long double x, const float *m) { return x + *m; }
static inline long double fsub_m(long double x, const float *m) { return x - *m; }
static inline long double fdiv_m(long double x, const float *m) { return x / *m; }
#else
static inline long double fld_m(const float *m) { long double x; __asm__("flds %1" : "=t"(x) : "m"(*m)); return x; }
static inline long double fmul_m(long double x, const float *m) { __asm__("fmuls %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fadd_m(long double x, const float *m) { __asm__("fadds %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fsub_m(long double x, const float *m) { __asm__("fsubs %1" : "+t"(x) : "m"(*m)); return x; }
static inline long double fdiv_m(long double x, const float *m) { __asm__("fdivs %1" : "+t"(x) : "m"(*m)); return x; }
#endif

int main(int argc, char **argv)
{
	static const double in[] = { 0.0, 0.1, 0.5, 1.0, 1.5707963267948966, 2.0, 3.0, -0.75, 10.0, 123.456, -42.0, 0.001 };
	int n = (int)(sizeof in / sizeof in[0]);
	double got[512];
	int k = 0;
	for (int i = 0; i < n; i++) {
		long double x = in[i];
		got[k++] = (double)x87_fsin(x);
		got[k++] = (double)x87_fcos(x);
		got[k++] = (double)x87_fsqrt(fabsl(x));
		got[k++] = (double)x87_fabs(x);
		got[k++] = (double)x87_fchs(x);
		got[k++] = (double)x87_fptan(x * 0.5L);
		got[k++] = (double)x87_fpatan(x, 1.25L);
		got[k++] = (double)x87_fpatan(-1.0L, x);
		float f = (float)in[i], g = 1.75f;
		got[k++] = (double)fmul_m(fld_m(&f), &g);
		got[k++] = (double)fadd_m(fld_m(&f), &g);
		got[k++] = (double)fsub_m(fld_m(&f), &g);
		got[k++] = (double)fdiv_m(fld_m(&f), &g);
	}
	if (argc > 1 && !strcmp(argv[1], "--make")) {
		for (int i = 0; i < k; i++)
			printf("%.17g\n", got[i]);
		return 0;
	}
	const char *path = argc > 1 ? argv[1] : "x87_expected.txt";
	FILE *e = fopen(path, "r");
	if (!e) {
		printf("FAIL  no %s\n", path);
		return 1;
	}
	int fails = 0;
	for (int i = 0; i < k; i++) {
		double want;
		if (fscanf(e, "%lf", &want) != 1) {
			printf("FAIL  %s ends at %d\n", path, i);
			return 1;
		}
		double tol = 1e-12 * (fabs(want) > 1 ? fabs(want) : 1);
		if (!(fabs(got[i] - want) <= tol) && !(isnan(want) && isnan(got[i]))) {
			printf("FAIL  case %d (input %g, operation %d): got %.17g, x87 %.17g\n", i, in[i / 12], i % 12, got[i], want);
			fails++;
		}
	}
	fclose(e);
	printf("%s: %d of %d values differ from the x87's\n", fails ? "FAILED" : "ALL PASSED", fails, k);
	return fails != 0;
}
