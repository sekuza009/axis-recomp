/* fitc.c: glRotatef candidates in C (with the CPU's own rsqrtss), matched bit for bit against the driver's answers.
   Input (stdin): lines "a x y z m0 .. m15" (the case's floats, then the driver's 16 result words in hex), from
   tools/glprobe/fit.py --dump. Prints, per candidate, how many matrices match whole and per element. */
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <xmmintrin.h>

typedef struct { float a, x, y, z; unsigned d[16]; } Case;
static Case g_c[20000];
static int g_n;

static float rsq(float v) { return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_set_ss(v))); }
static float rsq_nr(float v) { float y = rsq(v); return y * (1.5f - 0.5f * v * y * y); }
static float rsq_nr2(float v) { float y = rsq(v); return 0.5f * y * (3.0f - v * y * y); }
/* the bit trick (magic 0x5f3759df) with n Newton steps */
static float qrsqrt(float v, int n, unsigned magic)
{
	float h = 0.5f * v, y;
	unsigned i;
	memcpy(&i, &v, 4);
	i = magic - (i >> 1);
	memcpy(&y, &i, 4);
	for (int k = 0; k < n; k++)
		y = y * (1.5f - h * y * y);
	return y;
}

static void rot(const Case *k, int norm, int form, float *m)
{
	double rad = (double)k->a * (double)(float)(3.14159265358979323846 / 180.0);
	float s = (float)sin(rad), c = (float)cos(rad), x = k->x, y = k->y, z = k->z;
	float m2 = x * x + y * y + z * z, inv = 1;
	switch (norm) {
	case 0: inv = 1.0f / sqrtf(m2); break;
	case 1: inv = rsq(m2); break;
	case 2: inv = rsq_nr(m2); break;
	case 3: inv = rsq_nr2(m2); break;
	case 4: inv = m2 == 1.0f ? 1.0f : rsq_nr(m2); break;
	case 5: inv = (float)(1.0 / sqrt((double)m2)); break;
	case 7: inv = qrsqrt(m2, 1, 0x5f3759df); break;
	case 8: inv = qrsqrt(m2, 2, 0x5f3759df); break;
	case 9: inv = qrsqrt(m2, 2, 0x5f375a86); break;
	case 10: inv = qrsqrt(m2, 3, 0x5f3759df); break;
	}
	if (norm == 6) { float mag = sqrtf(m2); x /= mag; y /= mag; z /= mag; }
	else { x *= inv; y *= inv; z *= inv; }
	float oc = 1.0f - c;
	memset(m, 0, 64);
	m[15] = 1;
	if (form == 0) {   /* Mesa's grouping */
		float xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x, xs = x * s, ys = y * s, zs = z * s;
		m[0] = oc * xx + c; m[4] = oc * xy - zs; m[8] = oc * zx + ys;
		m[1] = oc * xy + zs; m[5] = oc * yy + c; m[9] = oc * yz - xs;
		m[2] = oc * zx - ys; m[6] = oc * yz + xs; m[10] = oc * zz + c;
	} else {           /* the spec's grouping: x x (1 - c) + c ... with (x * y) * oc */
		m[0] = x * x * oc + c; m[4] = x * y * oc - z * s; m[8] = x * z * oc + y * s;
		m[1] = y * x * oc + z * s; m[5] = y * y * oc + c; m[9] = y * z * oc - x * s;
		m[2] = x * z * oc - y * s; m[6] = y * z * oc + x * s; m[10] = z * z * oc + c;
	}
}

int main(void)
{
	char line[512];
	while (g_n < 20000 && fgets(line, sizeof line, stdin)) {
		Case *k = &g_c[g_n];
		char *p = line;
		k->a = strtof(p, &p); k->x = strtof(p, &p); k->y = strtof(p, &p); k->z = strtof(p, &p);
		for (int i = 0; i < 16; i++)
			k->d[i] = (unsigned)strtoul(p, &p, 16);
		g_n++;
	}
	static const char *nn[] = { "1/sqrtf", "rsqrtss", "rsqrtss+NR", "rsqrtss+NR(b)", "unit?1:rsqrt+NR", "1/sqrt dbl", "divide by sqrtf", "quake 1 step", "quake 2 steps", "quake2 5f375a86", "quake 3 steps" };
	for (int norm = 0; norm < 11; norm++)
		for (int form = 0; form < 2; form++) {
			int whole = 0, el[16] = { 0 };
			for (int i = 0; i < g_n; i++) {
				float m[16];
				rot(&g_c[i], norm, form, m);
				int all = 1;
				for (int j = 0; j < 16; j++) {
					unsigned u;
					memcpy(&u, &m[j], 4);
					if (u == g_c[i].d[j]) el[j]++; else all = 0;
				}
				whole += all;
			}
			printf("%-18s %s: %5d/%d whole;", nn[norm], form ? "spec" : "mesa", whole, g_n);
			for (int j = 0; j < 11; j++)
				if (j != 3 && j != 7) printf(" %d", el[j]);
			printf("\n");
		}
	return 0;
}
