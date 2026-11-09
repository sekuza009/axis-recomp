/* glstate.c: the OpenGL state the game reads back, kept in software (PORTING.md: the rendering seam). The game uses
   GL's matrix stack as part of its maths - it reads the modelview matrix back for actor body matrices, collision,
   weapons' aiming (gluLookAt) and the view volume - and asks for the viewport and fog. A platform without OpenGL
   (Godot) has to answer those itself; this is that answer, checked here against the real driver.

   AXIS_GLSTATE=1 (check): a layer in front of the game's GL import slots - each matrix, viewport, enable and fog call
   goes to the driver as before and is applied to the software state too; each query is answered by the driver (so
   the game runs exactly as without the layer) and compared with the software answer: glstate.log, in the game
   folder, counts them by kind (exact, or the largest difference) every few seconds.
   AXIS_GLSTATE=2: the same, but the game gets the software answer (the driver still draws).

   Compiled with SSE float maths (standalone/build.sh), as drivers compute, not the game's x87. The formulas are
   the usual implementations' (Mesa's matrix code; the SGI GLU behind Windows' glu32). */
#include <windows.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define S __stdcall
enum { MV, PROJ, TEX, NSTACK };
static float g_stack[NSTACK][32][16];
static int g_depth[NSTACK], g_mode;
static float g_viewport[4];
static int g_fog;
static float g_fogStart = 0, g_fogEnd = 1;
static int g_answer;   /* 2: the software answer is given */
/* (diagnosis) the modelview calls since its last load, shown with the first differences */
static char g_ops[16][96];
static int g_nops;
static void op(const char *fmt, double a, double b, double c, double d)
{
	if (g_mode != MV)
		return;
	if (g_nops < 16)
		snprintf(g_ops[g_nops], sizeof g_ops[0], fmt, a, b, c, d);
	g_nops++;
}

/* the driver's functions (what was in the slots) */
static void (S *r_glMatrixMode)(unsigned), (S *r_glLoadIdentity)(void), (S *r_glLoadMatrixf)(const float *),
	(S *r_glMultMatrixf)(const float *), (S *r_glPushMatrix)(void), (S *r_glPopMatrix)(void),
	(S *r_glTranslatef)(float, float, float), (S *r_glRotatef)(float, float, float, float), (S *r_glScalef)(float, float, float),
	(S *r_glViewport)(int, int, int, int), (S *r_glEnable)(unsigned), (S *r_glDisable)(unsigned),
	(S *r_glFogf)(unsigned, float), (S *r_glFogi)(unsigned, int), (S *r_glFogfv)(unsigned, const float *),
	(S *r_glGetFloatv)(unsigned, float *), (S *r_glGetBooleanv)(unsigned, unsigned char *),
	(S *r_gluLookAt)(double, double, double, double, double, double, double, double, double),
	(S *r_gluPerspective)(double, double, double, double), (S *r_gluOrtho2D)(double, double, double, double);

static float *top(void) { return g_stack[g_mode][g_depth[g_mode]]; }

static void identity(float *m)
{
	memset(m, 0, 64);
	m[0] = m[5] = m[10] = m[15] = 1;
}

/* m = m * b (column-major; Mesa's matmul4 order) */
static void mult(float *m, const float *b)
{
	float p[16];
	for (int i = 0; i < 4; i++) {
		const float ai0 = m[i], ai1 = m[i + 4], ai2 = m[i + 8], ai3 = m[i + 12];
		p[i] = ai0 * b[0] + ai1 * b[1] + ai2 * b[2] + ai3 * b[3];
		p[i + 4] = ai0 * b[4] + ai1 * b[5] + ai2 * b[6] + ai3 * b[7];
		p[i + 8] = ai0 * b[8] + ai1 * b[9] + ai2 * b[10] + ai3 * b[11];
		p[i + 12] = ai0 * b[12] + ai1 * b[13] + ai2 * b[14] + ai3 * b[15];
	}
	memcpy(m, p, 64);
}

static void translate(float *m, float x, float y, float z)
{
	m[12] = m[0] * x + m[4] * y + m[8] * z + m[12];
	m[13] = m[1] * x + m[5] * y + m[9] * z + m[13];
	m[14] = m[2] * x + m[6] * y + m[10] * z + m[14];
	m[15] = m[3] * x + m[7] * y + m[11] * z + m[15];
}

static void scale(float *m, float x, float y, float z)
{
	for (int i = 0; i < 4; i++) {
		m[i] *= x;
		m[4 + i] *= y;
		m[8 + i] *= z;
	}
}

/* Mesa's _math_matrix_rotate: the axis-aligned cases built directly, else the general rotation */
static void rotate(float *m, float angle, float x, float y, float z)
{
	float r[16];
	/* (the driver's sine and cosine, measured against it - glstate_diff.log: the angle times pi / 180 held as a
	   float, multiplied in double; sin and cos in double, rounded to float) */
	const double rad = (double)angle * (double)(float)(3.14159265358979323846 / 180.0);
	const float s = (float)sin(rad), c = (float)cos(rad);
	identity(r);
	int optimized = 0;
	if (x == 0.0f) {
		if (y == 0.0f) {
			if (z != 0.0f) {
				optimized = 1;
				r[0] = c;
				r[5] = c;
				if (z < 0.0f) { r[1] = -s; r[4] = s; } else { r[1] = s; r[4] = -s; }
			}
		} else if (z == 0.0f) {
			optimized = 1;
			r[0] = c;
			r[10] = c;
			if (y < 0.0f) { r[2] = s; r[8] = -s; } else { r[2] = -s; r[8] = s; }
		}
	} else if (y == 0.0f && z == 0.0f) {
		optimized = 1;
		r[5] = c;
		r[10] = c;
		if (x < 0.0f) { r[6] = -s; r[9] = s; } else { r[6] = s; r[9] = -s; }
	}
	if (!optimized) {
		const float mag = sqrtf(x * x + y * y + z * z);
		if (mag <= 1.0e-4f)
			return;
		x /= mag;
		y /= mag;
		z /= mag;
		const float xx = x * x, yy = y * y, zz = z * z, xy = x * y, yz = y * z, zx = z * x;
		const float xs = x * s, ys = y * s, zs = z * s, one_c = 1.0f - c;
		r[0] = (one_c * xx) + c;
		r[4] = (one_c * xy) - zs;
		r[8] = (one_c * zx) + ys;
		r[1] = (one_c * xy) + zs;
		r[5] = (one_c * yy) + c;
		r[9] = (one_c * yz) - xs;
		r[2] = (one_c * zx) - ys;
		r[6] = (one_c * yz) + xs;
		r[10] = (one_c * zz) + c;
	}
	mult(m, r);
}

/* glMultMatrixd / glTranslated as drivers take them: to floats first */
static void mult_d(float *m, const double *d)
{
	float f[16];
	for (int i = 0; i < 16; i++)
		f[i] = (float)d[i];
	mult(m, f);
}

/* ---- the layer: the driver called, the software state kept alongside ---- */
static void S l_glMatrixMode(unsigned mode)
{
	r_glMatrixMode(mode);
	if (mode - 0x1700u < 3)
		g_mode = (int)(mode - 0x1700u);
}
static void S l_glLoadIdentity(void) { r_glLoadIdentity(); identity(top()); if (g_mode == MV) g_nops = 0; op("LoadIdentity", 0, 0, 0, 0); }
static void S l_glLoadMatrixf(const float *m) { r_glLoadMatrixf(m); memcpy(top(), m, 64); if (g_mode == MV) g_nops = 0; op("LoadMatrix", 0, 0, 0, 0); }
static void S l_glMultMatrixf(const float *m) { r_glMultMatrixf(m); mult(top(), m); op("MultMatrix %.9g %.9g %.9g %.9g..", m[0], m[1], m[2], m[4]); }
static void S l_glPushMatrix(void)
{
	r_glPushMatrix();
	if (g_depth[g_mode] < 31) {
		memcpy(g_stack[g_mode][g_depth[g_mode] + 1], top(), 64);
		g_depth[g_mode]++;
	}
}
static void S l_glPopMatrix(void)
{
	r_glPopMatrix();
	if (g_depth[g_mode] > 0)
		g_depth[g_mode]--;
}
static void S l_glTranslatef(float x, float y, float z) { r_glTranslatef(x, y, z); translate(top(), x, y, z); op("Translate %.9g %.9g %.9g", x, y, z, 0); }
static void S l_glRotatef(float a, float x, float y, float z) { r_glRotatef(a, x, y, z); rotate(top(), a, x, y, z); op("Rotate %.9g about %.9g %.9g %.9g", a, x, y, z); }
static void S l_glScalef(float x, float y, float z) { r_glScalef(x, y, z); scale(top(), x, y, z); op("Scale %.9g %.9g %.9g", x, y, z, 0); }
static void S l_glViewport(int x, int y, int w, int h)
{
	r_glViewport(x, y, w, h);
	g_viewport[0] = (float)x;
	g_viewport[1] = (float)y;
	g_viewport[2] = (float)w;
	g_viewport[3] = (float)h;
}
static void S l_glEnable(unsigned cap) { r_glEnable(cap); if (cap == 0x0b60) g_fog = 1; }
static void S l_glDisable(unsigned cap) { r_glDisable(cap); if (cap == 0x0b60) g_fog = 0; }
static void fog_value(unsigned pname, float v)
{
	if (pname == 0x0b63) g_fogStart = v;   /* GL_FOG_START */
	if (pname == 0x0b64) g_fogEnd = v;     /* GL_FOG_END */
}
static void S l_glFogf(unsigned pname, float v) { r_glFogf(pname, v); fog_value(pname, v); }
static void S l_glFogi(unsigned pname, int v) { r_glFogi(pname, v); fog_value(pname, (float)v); }
static void S l_glFogfv(unsigned pname, const float *v) { r_glFogfv(pname, v); fog_value(pname, v[0]); }

/* gluLookAt (SGI GLU, as in Windows' glu32): forward, side and up in floats, the rotation multiplied in, then the
   eye translated away */
static void S l_gluLookAt(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz)
{
	r_gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz);
	op("LookAt eye %.9g %.9g %.9g ..", ex, ey, ez, 0);
	op("  centre %.9g %.9g %.9g up-y %.9g", cx, cy, cz, uy);
	float f[3] = { (float)(cx - ex), (float)(cy - ey), (float)(cz - ez) }, up[3] = { (float)ux, (float)uy, (float)uz }, s[3], u[3];
	float r = sqrtf(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
	if (r != 0.0f) { f[0] /= r; f[1] /= r; f[2] /= r; }
	s[0] = f[1] * up[2] - f[2] * up[1];
	s[1] = f[2] * up[0] - f[0] * up[2];
	s[2] = f[0] * up[1] - f[1] * up[0];
	r = sqrtf(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
	if (r != 0.0f) { s[0] /= r; s[1] /= r; s[2] /= r; }
	u[0] = s[1] * f[2] - s[2] * f[1];
	u[1] = s[2] * f[0] - s[0] * f[2];
	u[2] = s[0] * f[1] - s[1] * f[0];
	float m[16];
	identity(m);
	m[0] = s[0]; m[4] = s[1]; m[8] = s[2];
	m[1] = u[0]; m[5] = u[1]; m[9] = u[2];
	m[2] = -f[0]; m[6] = -f[1]; m[10] = -f[2];
	mult(top(), m);
	translate(top(), (float)-ex, (float)-ey, (float)-ez);
}
static void S l_gluPerspective(double fovy, double aspect, double zNear, double zFar)
{
	r_gluPerspective(fovy, aspect, zNear, zFar);
	double radians = fovy / 2 * 3.14159265358979323846 / 180, dz = zFar - zNear, sine = sin(radians);
	if (dz == 0 || sine == 0 || aspect == 0)
		return;
	double cot = cos(radians) / sine, m[16] = { 0 };
	m[0] = cot / aspect;
	m[5] = cot;
	m[10] = -(zFar + zNear) / dz;
	m[11] = -1;
	m[14] = -2 * zNear * zFar / dz;
	mult_d(top(), m);
}
static void S l_gluOrtho2D(double l, double rt, double b, double t)
{
	r_gluOrtho2D(l, rt, b, t);
	float L = (float)l, R = (float)rt, B = (float)b, T = (float)t, n = -1, f = 1, m[16];
	identity(m);
	m[0] = 2.0f / (R - L);
	m[12] = -(R + L) / (R - L);
	m[5] = 2.0f / (T - B);
	m[13] = -(T + B) / (T - B);
	m[10] = -2.0f / (f - n);
	m[14] = -(f + n) / (f - n);
	mult(top(), m);
}

/* ---- the queries: compared, counted ---- */
typedef struct { const char *name; unsigned n, exact; float maxDiff; unsigned shown; } Stat;
static Stat g_stats[6] = { { "modelview" }, { "projection" }, { "viewport" }, { "fog start" }, { "fog end" }, { "fog on" } };
static CRITICAL_SECTION g_cs;
static char g_logPath[MAX_PATH];
static FILE *g_detail;

static void compare(Stat *st, const float *driver, const float *soft, int n)
{
	float d = 0;
	int exact = 1;
	for (int i = 0; i < n; i++) {
		if (memcmp(&driver[i], &soft[i], 4))
			exact = 0;
		float e = fabsf(driver[i] - soft[i]);
		if (e > d)
			d = e;
	}
	st->n++;
	st->exact += exact;
	if (d > st->maxDiff)
		st->maxDiff = d;
	if (!exact && st->shown < 24 && g_detail) {   /* (the first few differences, in full) */
		st->shown++;
		fprintf(g_detail, "%s differs (largest %g):\n  driver  ", st->name, d);
		for (int i = 0; i < n; i++) fprintf(g_detail, " %.9g", driver[i]);
		fprintf(g_detail, "\n  software");
		for (int i = 0; i < n; i++) fprintf(g_detail, " %.9g", soft[i]);
		fprintf(g_detail, "\n");
		if (st == &g_stats[0])
			for (int k = 0; k < g_nops && k < 16; k++)
				fprintf(g_detail, "    %s\n", g_ops[k]);
		fflush(g_detail);
	}
}

static void S l_glGetFloatv(unsigned pname, float *out)
{
	r_glGetFloatv(pname, out);
	const float *soft = NULL;
	Stat *st = NULL;
	int n = 1;
	float one;
	switch (pname) {
	case 0x0ba6: soft = g_stack[MV][g_depth[MV]]; st = &g_stats[0]; n = 16; break;     /* GL_MODELVIEW_MATRIX */
	case 0x0ba7: soft = g_stack[PROJ][g_depth[PROJ]]; st = &g_stats[1]; n = 16; break; /* GL_PROJECTION_MATRIX */
	case 0x0ba2: soft = g_viewport; st = &g_stats[2]; n = 4; break;                    /* GL_VIEWPORT */
	case 0x0b63: one = g_fogStart; soft = &one; st = &g_stats[3]; break;
	case 0x0b64: one = g_fogEnd; soft = &one; st = &g_stats[4]; break;
	}
	if (!st)
		return;
	if (g_answer == 3) {   /* (no driver: the software answer, nothing compared) */
		memcpy(out, soft, n * 4);
		return;
	}
	EnterCriticalSection(&g_cs);
	compare(st, out, soft, n);
	LeaveCriticalSection(&g_cs);
	if (g_answer == 2)
		memcpy(out, soft, n * 4);
}
static void S l_glGetBooleanv(unsigned pname, unsigned char *out)
{
	r_glGetBooleanv(pname, out);
	if (pname != 0x0b60)
		return;
	if (g_answer == 3) {
		*out = (unsigned char)g_fog;
		return;
	}
	float driver = *out, soft = (float)g_fog;
	EnterCriticalSection(&g_cs);
	compare(&g_stats[5], &driver, &soft, 1);
	LeaveCriticalSection(&g_cs);
	if (g_answer == 2)
		*out = (unsigned char)g_fog;
}

static DWORD WINAPI report(void *unused)
{
	(void)unused;
	for (;;) {
		Sleep(5000);
		FILE *f = fopen(g_logPath, "w");
		if (!f)
			continue;
		EnterCriticalSection(&g_cs);
		fprintf(f, "glstate (AXIS_GLSTATE=%d: %s): the game's GL queries, the driver's answer against the software state\n",
		        g_answer, g_answer == 2 ? "the software answer given" : "the driver's answer given");
		for (int i = 0; i < 6; i++)
			fprintf(f, "  %-10s %8u queries, %8u exact, largest difference %g\n", g_stats[i].name, g_stats[i].n,
			        g_stats[i].exact, g_stats[i].maxDiff);
		LeaveCriticalSection(&g_cs);
		fclose(f);
	}
	return 0;
}

/* the layer put in front of the game's GL slots; slot(name) gives a slot's place. Returns the number wrapped */
int glstate_install(void **(*slot)(const char *name), int mode, const char *dir)
{
	g_answer = mode;
	InitializeCriticalSection(&g_cs);
	for (int k = 0; k < NSTACK; k++)
		identity(g_stack[k][0]);
	if (mode != 3) {   /* (mode 3: no driver - nothing to compare, no logs) */
		snprintf(g_logPath, sizeof g_logPath, "%sglstate.log", dir);
		char detail[MAX_PATH];
		snprintf(detail, sizeof detail, "%sglstate_diff.log", dir);
		g_detail = fopen(detail, "w");
	}
	int n = 0;
#define WRAP(name) do { void **p = slot(#name); if (p) { *(void **)&r_##name = *p; *p = (void *)l_##name; n++; } } while (0)
	WRAP(glMatrixMode); WRAP(glLoadIdentity); WRAP(glLoadMatrixf); WRAP(glMultMatrixf); WRAP(glPushMatrix);
	WRAP(glPopMatrix); WRAP(glTranslatef); WRAP(glRotatef); WRAP(glScalef); WRAP(glViewport); WRAP(glEnable);
	WRAP(glDisable); WRAP(glFogf); WRAP(glFogi); WRAP(glFogfv); WRAP(glGetFloatv); WRAP(glGetBooleanv);
	WRAP(gluLookAt); WRAP(gluPerspective); WRAP(gluOrtho2D);
#undef WRAP
	if (mode != 3)
		CloseHandle(CreateThread(NULL, 0, report, NULL, 0, NULL));
	return n;
}
