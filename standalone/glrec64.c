/* glrec64.c: the game's drawing recorded for the host in the 64-bit build (PORTING.md, stage 6) - standalone/glrec.c's
   live mode with no driver (config.nogl), written in plain C: every GL / GLU call the game makes is appended to a
   stream in glrec.c's format (the same ops, each argument as the 32-bit build's stack words: an int or enum one word,
   a float its bits, a double two words), the data its pointers point at copied in; at SwapBuffers the frame's words go
   to the host (AxisHostConfig.frame) with the frame's size. Nothing is drawn here. What a driver would answer comes
   from here too (texture names, the strings, contexts, pixel formats, the texture filters the fixes save and
   restore); glstate.c (mode 3), layered in front, answers the matrix, viewport and fog queries. */
#if defined(__x86_64__) || defined(__aarch64__)
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef uint32_t u32;
typedef uint8_t u8;
extern unsigned char *g_arena;

/* ---- the stream */
static u32 *g_buf;
static size_t g_len, g_cap;
static void put(u32 w)
{
	if (g_len == g_cap) {
		g_cap = g_cap ? g_cap * 2 : 1 << 20;
		g_buf = realloc(g_buf, g_cap * 4);
	}
	g_buf[g_len++] = w;
}
static void put_bytes(const void *p, size_t n)
{
	const u8 *b = p;
	for (size_t i = 0; i < n; i += 4) {
		u32 w = 0;
		memcpy(&w, b + i, n - i < 4 ? n - i : 4);
		put(w);
	}
}
static void put_f(float f) { u32 w; memcpy(&w, &f, 4); put(w); }
static void put_d(double d) { u32 w[2]; memcpy(w, &d, 8); put(w[0]); put(w[1]); }
static void put_op(int op, int words) { put((u32)op | (u32)words << 16); }

/* ---- the plain calls (glrec.c's table: the op, the name, the words) */
#define NPLAIN 40
static const struct { const char *name; int words; } k_plain[NPLAIN] = {
	{ "glBegin", 1 }, { "glBindTexture", 2 }, { "glBlendFunc", 2 }, { "glClear", 1 }, { "glClearColor", 4 },
	{ "glClearDepth", 2 }, { "glColor3ub", 3 }, { "glColor4f", 4 }, { "glColor4ub", 4 }, { "glCullFace", 1 },
	{ "glDepthFunc", 1 }, { "glDisable", 1 }, { "glDisableClientState", 1 }, { "glEnable", 1 },
	{ "glEnableClientState", 1 }, { "glEnd", 0 }, { "glFogf", 2 }, { "glFogi", 2 }, { "glFrontFace", 1 },
	{ "glHint", 2 }, { "glLoadIdentity", 0 }, { "glMatrixMode", 1 }, { "glPolygonMode", 2 },
	{ "glPolygonOffset", 2 }, { "glPopMatrix", 0 }, { "glPushMatrix", 0 }, { "glRotatef", 4 }, { "glScalef", 3 },
	{ "glTexCoord2d", 4 }, { "glTexCoord2f", 2 }, { "glTexCoord2i", 2 }, { "glTexEnvf", 3 },
	{ "glTexParameterf", 3 }, { "glTranslatef", 3 }, { "glVertex2i", 2 }, { "glVertex3f", 3 }, { "glViewport", 4 },
	{ "gluLookAt", 18 }, { "gluOrtho2D", 8 }, { "gluPerspective", 8 },
};
static u32 g_bound;
static int g_minF[4096], g_magF[4096];   /* (each texture's filters, by name: 0 GL's defaults) */
static void track_param(u32 pname, int v)
{
	if (g_bound >= 4096)
		return;
	if (pname == 0x2801)
		g_minF[g_bound] = v;
	else if (pname == 0x2800)
		g_magF[g_bound] = v;
}

/* the client arrays as the game set them (the data copied at each draw) */
typedef struct { int size; u32 type; int stride; const void *ptr; int on; } Array;
static Array g_arr[3];   /* vertex, colour, texture coordinates */
static int array_of(u32 cap) { return cap == 0x8074 ? 0 : cap == 0x8076 ? 1 : cap == 0x8078 ? 2 : -1; }

#define W(x) put((u32)(x))
static void r_glBegin(u32 m) { put_op(0, 1); W(m); }
static void r_glBindTexture(u32 t, u32 n) { g_bound = n; put_op(1, 2); W(t); W(n); }
static void r_glBlendFunc(u32 a, u32 b) { put_op(2, 2); W(a); W(b); }
static void r_glClear(u32 m) { put_op(3, 1); W(m); }
static void r_glClearColor(float r, float g, float b, float a) { put_op(4, 4); put_f(r); put_f(g); put_f(b); put_f(a); }
static void r_glClearDepth(double d) { put_op(5, 2); put_d(d); }
static void r_glColor3ub(u8 r, u8 g, u8 b) { put_op(6, 3); W(r); W(g); W(b); }
static void r_glColor4f(float r, float g, float b, float a) { put_op(7, 4); put_f(r); put_f(g); put_f(b); put_f(a); }
static void r_glColor4ub(u8 r, u8 g, u8 b, u8 a) { put_op(8, 4); W(r); W(g); W(b); W(a); }
static void r_glCullFace(u32 m) { put_op(9, 1); W(m); }
static void r_glDepthFunc(u32 f) { put_op(10, 1); W(f); }
static void r_glDisable(u32 c) { put_op(11, 1); W(c); }
static void r_glDisableClientState(u32 c) { int a = array_of(c); if (a >= 0) g_arr[a].on = 0; put_op(12, 1); W(c); }
static void r_glEnable(u32 c) { put_op(13, 1); W(c); }
static void r_glEnableClientState(u32 c) { int a = array_of(c); if (a >= 0) g_arr[a].on = 1; put_op(14, 1); W(c); }
static void r_glEnd(void) { put_op(15, 0); }
static void r_glFogf(u32 p, float v) { put_op(16, 2); W(p); put_f(v); }
static void r_glFogi(u32 p, int v) { put_op(17, 2); W(p); W(v); }
static void r_glFrontFace(u32 m) { put_op(18, 1); W(m); }
static void r_glHint(u32 t, u32 m) { put_op(19, 2); W(t); W(m); }
static void r_glLoadIdentity(void) { put_op(20, 0); }
static void r_glMatrixMode(u32 m) { put_op(21, 1); W(m); }
static void r_glPolygonMode(u32 f, u32 m) { put_op(22, 2); W(f); W(m); }
static void r_glPolygonOffset(float f, float u) { put_op(23, 2); put_f(f); put_f(u); }
static void r_glPopMatrix(void) { put_op(24, 0); }
static void r_glPushMatrix(void) { put_op(25, 0); }
static void r_glRotatef(float a, float x, float y, float z) { put_op(26, 4); put_f(a); put_f(x); put_f(y); put_f(z); }
static void r_glScalef(float x, float y, float z) { put_op(27, 3); put_f(x); put_f(y); put_f(z); }
static void r_glTexCoord2d(double s, double t) { put_op(28, 4); put_d(s); put_d(t); }
static void r_glTexCoord2f(float s, float t) { put_op(29, 2); put_f(s); put_f(t); }
static void r_glTexCoord2i(int s, int t) { put_op(30, 2); W(s); W(t); }
static void r_glTexEnvf(u32 t, u32 p, float v) { put_op(31, 3); W(t); W(p); put_f(v); }
static void r_glTexParameterf(u32 t, u32 p, float v) { track_param(p, (int)v); put_op(32, 3); W(t); W(p); put_f(v); }
static void r_glTranslatef(float x, float y, float z) { put_op(33, 3); put_f(x); put_f(y); put_f(z); }
static void r_glVertex2i(int x, int y) { put_op(34, 2); W(x); W(y); }
static void r_glVertex3f(float x, float y, float z) { put_op(35, 3); put_f(x); put_f(y); put_f(z); }
static void r_glViewport(int x, int y, int w, int h) { put_op(36, 4); W(x); W(y); W(w); W(h); }
static void r_gluLookAt(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz)
{
	put_op(37, 18);
	put_d(ex); put_d(ey); put_d(ez); put_d(cx); put_d(cy); put_d(cz); put_d(ux); put_d(uy); put_d(uz);
}
static void r_gluOrtho2D(double l, double r, double b, double t) { put_op(38, 8); put_d(l); put_d(r); put_d(b); put_d(t); }
static void r_gluPerspective(double f, double a, double n, double z) { put_op(39, 8); put_d(f); put_d(a); put_d(n); put_d(z); }

/* ---- the calls with pointers, draws, textures (glrec.c's ops from 64) */
enum { OP_COLOR4UBV = 64, OP_FOGFV, OP_LOADMATRIX, OP_MULTMATRIX, OP_TEXCOORD2FV, OP_VERTEX3FV, OP_VERTEX4FV,
       OP_PIXELSTORE, OP_DRAW, OP_TEXIMAGE, OP_MIPMAPS, OP_TEXPARAMI };
static void r_glColor4ubv(const void *v) { put_op(OP_COLOR4UBV, 1); put_bytes(v, 4); }
static void r_glFogfv(u32 p, const float *v) { put_op(OP_FOGFV, 5); W(p); put_bytes(v, 16); }
static void r_glLoadMatrixf(const float *m) { put_op(OP_LOADMATRIX, 16); put_bytes(m, 64); }
static void r_glMultMatrixf(const float *m) { put_op(OP_MULTMATRIX, 16); put_bytes(m, 64); }
static void r_glTexCoord2fv(const float *v) { put_op(OP_TEXCOORD2FV, 2); put_bytes(v, 8); }
static void r_glVertex3fv(const float *v) { put_op(OP_VERTEX3FV, 3); put_bytes(v, 12); }
static void r_glVertex4fv(const float *v) { put_op(OP_VERTEX4FV, 4); put_bytes(v, 16); }
static int g_unpackAlign = 4;
static void r_glPixelStorei(u32 p, int v)
{
	if (p == 0x0cf5)
		g_unpackAlign = v;
	put_op(OP_PIXELSTORE, 2); W(p); W(v);
}
static void glTexParameteri_(u32 t, u32 p, int v) { track_param(p, v); put_op(OP_TEXPARAMI, 3); W(t); W(p); W(v); }

static int type_size(u32 t)
{
	switch (t) {
	case 0x1400: case 0x1401: return 1;
	case 0x1402: case 0x1403: return 2;
	case 0x140a: return 8;
	default: return 4;
	}
}
static void set_array(int a, int size, u32 type, int stride, const void *p)
{
	g_arr[a].size = size; g_arr[a].type = type; g_arr[a].stride = stride; g_arr[a].ptr = p;
}
static void r_glVertexPointer(int s, u32 t, int st, const void *p) { set_array(0, s, t, st, p); }
static void r_glColorPointer(int s, u32 t, int st, const void *p) { set_array(1, s, t, st, p); }
static void r_glTexCoordPointer(int s, u32 t, int st, const void *p) { set_array(2, s, t, st, p); }
static void r_glDrawElements(u32 mode, int count, u32 itype, const void *idx)
{
	u32 top = 0;
	for (int i = 0; i < count; i++) {
		u32 v = itype == 0x1401 ? ((const u8 *)idx)[i] : itype == 0x1403 ? ((const uint16_t *)idx)[i] : ((const u32 *)idx)[i];
		if (v > top)
			top = v;
	}
	u32 n = count ? top + 1 : 0;
	size_t words = 4 + (size_t)(count * type_size(itype) + 3) / 4;
	for (int a = 0; a < 3; a++)
		if (g_arr[a].on)
			words += 3 + (n * g_arr[a].size * type_size(g_arr[a].type) + 3) / 4;
	put_op(OP_DRAW, (int)(words > 0xffff ? 0xffff : words));
	W(mode); W(count); W(itype); W(n);
	put_bytes(idx, (size_t)count * type_size(itype));
	for (int a = 0; a < 3; a++) {
		W(g_arr[a].on);
		if (!g_arr[a].on)
			continue;
		int el = g_arr[a].size * type_size(g_arr[a].type), st = g_arr[a].stride ? g_arr[a].stride : el;
		W(g_arr[a].size); W(g_arr[a].type);
		u32 w = 0;
		int fill = 0;
		for (u32 i = 0; i < n; i++)
			for (int b = 0; b < el; b++) {
				w |= (u32)((const u8 *)g_arr[a].ptr)[(size_t)i * st + b] << (8 * fill);
				if (++fill == 4) { put(w); w = 0; fill = 0; }
			}
		if (fill)
			put(w);
	}
}
static size_t image_bytes(int w, int h, u32 format, u32 type)
{
	int comps = format == 0x1907 ? 3 : format == 0x1908 ? 4 : format == 0x190a ? 2 : format == 0x80e0 ? 3 : format == 0x80e1 ? 4 : 1;
	int px = type == 0x1401 || type == 0x1400 ? comps : (type == 0x8033 || type == 0x8034 || type == 0x8363) ? 2 : comps * type_size(type);
	size_t row = (size_t)w * px, a = g_unpackAlign > 0 ? (size_t)g_unpackAlign : 1;
	size_t stride = (row + a - 1) / a * a;
	return h > 0 ? stride * (h - 1) + row : 0;
}
static void r_glTexImage2D(u32 target, int level, int ifmt, int w, int h, int border, u32 fmt, u32 type, const void *p)
{
	size_t n = p ? image_bytes(w, h, fmt, type) : 0;
	put_op(OP_TEXIMAGE, 0xffff);
	W(target); W(level); W(ifmt); W(w); W(h); W(border); W(fmt); W(type); W(n);
	put_bytes(p, n);
}
static int r_gluBuild2DMipmaps(u32 target, int comps, int w, int h, u32 fmt, u32 type, const void *p)
{
	size_t n = p ? image_bytes(w, h, fmt, type) : 0;
	put_op(OP_MIPMAPS, 0xffff);
	W(target); W(comps); W(w); W(h); W(fmt); W(type); W(n);
	put_bytes(p, n);
	return 0;
}

/* ---- what a driver would answer */
static u32 g_nextName = 1;
static void f_glGenTextures(int n, u32 *names) { for (int i = 0; i < n; i++) names[i] = g_nextName++; }
static const char *f_glGetString(u32 name)
{
	/* (in the arena: the game may keep the address) */
	static char *s;
	if (!s) {
		void *arena_malloc(size_t);
		s = arena_malloc(64);
		strcpy(s, "AxisRC (no driver: the host draws)");
	}
	return name == 0x1f03 ? s + strlen(s) : s;   /* (GL_EXTENSIONS: none) */
}
static void f_glGetFloatv(u32 p, float *out) { (void)p; out[0] = 0; }
static void f_glGetBooleanv(u32 p, u8 *out) { (void)p; out[0] = 0; }
static void f_glFinish(void) {}
void *host64_handle(void);   /* host64.c */
static void *f_wglCreateContext(void *dc) { (void)dc; return host64_handle(); }
static int f_wglDeleteContext(void *rc) { (void)rc; return 1; }
static int f_wglMakeCurrent(void *dc, void *rc) { (void)dc; (void)rc; return 1; }
static void *f_wglGetProcAddress(const char *n) { (void)n; return NULL; }
static int f_ChoosePixelFormat(void *dc, const void *pfd) { (void)dc; (void)pfd; return 1; }
static int f_SetPixelFormat(void *dc, int f, const void *pfd) { (void)dc; (void)f; (void)pfd; return 1; }
/* the fixes' pixel-sharp text (src/fixes, platform_texNearest / platform_texRestore): the bound texture's filters */
int glrec64_texNearest(int saved[2])
{
	saved[0] = g_bound < 4096 && g_magF[g_bound] ? g_magF[g_bound] : 0x2601;   /* GL_LINEAR */
	saved[1] = g_bound < 4096 && g_minF[g_bound] ? g_minF[g_bound] : 0x2702;   /* GL_NEAREST_MIPMAP_LINEAR */
	glTexParameteri_(0x0de1, 0x2800, 0x2600);
	glTexParameteri_(0x0de1, 0x2801, 0x2600);
	return 1;
}
void glrec64_texRestore(const int saved[2])
{
	glTexParameteri_(0x0de1, 0x2800, saved[0]);
	glTexParameteri_(0x0de1, 0x2801, saved[1]);
}

/* ---- the frame */
static void (*g_live)(void *user, const unsigned *words, unsigned count, int width, int height);
static void *g_liveUser;
void hostwin_size(int *w, int *h);   /* hostwin64.c */
static int f_SwapBuffers(void *dc)
{
	(void)dc;
	int w = 0, h = 0;
	hostwin_size(&w, &h);
	if (g_live)
		g_live(g_liveUser, g_buf, (unsigned)g_len, w, h);
	g_len = 0;
	return 1;
}

/* the stream's header ("AXGLREC1", the plain calls' table), as glrec.c's */
unsigned glrec64_header(unsigned char *out, unsigned room)
{
	unsigned n = 12;
	for (int i = 0; i < NPLAIN; i++)
		n += 8 + (unsigned)strlen(k_plain[i].name);
	if (!out || room < n)
		return n;
	memcpy(out, "AXGLREC1", 8);
	u32 c = NPLAIN;
	memcpy(out + 8, &c, 4);
	unsigned o = 12;
	for (int i = 0; i < NPLAIN; i++) {
		u32 w = (u32)k_plain[i].words, l = (u32)strlen(k_plain[i].name);
		memcpy(out + o, &w, 4);
		memcpy(out + o + 4, &l, 4);
		memcpy(out + o + 8, k_plain[i].name, l);
		o += 8 + l;
	}
	return n;
}

int glrec64_install(void **(*slot)(const char *name), void (*frame)(void *, const unsigned *, unsigned, int, int), void *user)
{
	g_live = frame;
	g_liveUser = user;
	int n = 0;
#define SET(name, f) do { void **p = slot(#name); if (p) { *p = (void *)(f); n++; } } while (0)
#define R(name) SET(name, r_##name)
	R(glBegin); R(glBindTexture); R(glBlendFunc); R(glClear); R(glClearColor); R(glClearDepth); R(glColor3ub);
	R(glColor4f); R(glColor4ub); R(glCullFace); R(glDepthFunc); R(glDisable); R(glDisableClientState); R(glEnable);
	R(glEnableClientState); R(glEnd); R(glFogf); R(glFogi); R(glFrontFace); R(glHint); R(glLoadIdentity);
	R(glMatrixMode); R(glPolygonMode); R(glPolygonOffset); R(glPopMatrix); R(glPushMatrix); R(glRotatef); R(glScalef);
	R(glTexCoord2d); R(glTexCoord2f); R(glTexCoord2i); R(glTexEnvf); R(glTexParameterf); R(glTranslatef);
	R(glVertex2i); R(glVertex3f); R(glViewport); R(gluLookAt); R(gluOrtho2D); R(gluPerspective);
	R(glColor4ubv); R(glFogfv); R(glLoadMatrixf); R(glMultMatrixf); R(glTexCoord2fv); R(glVertex3fv); R(glVertex4fv);
	R(glPixelStorei); R(glVertexPointer); R(glColorPointer); R(glTexCoordPointer); R(glDrawElements);
	R(glTexImage2D); R(gluBuild2DMipmaps);
	SET(glGenTextures, f_glGenTextures); SET(glGetString, f_glGetString); SET(glGetFloatv, f_glGetFloatv);
	SET(glGetBooleanv, f_glGetBooleanv); SET(glFinish, f_glFinish); SET(wglCreateContext, f_wglCreateContext);
	SET(wglDeleteContext, f_wglDeleteContext); SET(wglMakeCurrent, f_wglMakeCurrent);
	SET(wglGetProcAddress, f_wglGetProcAddress); SET(ChoosePixelFormat, f_ChoosePixelFormat);
	SET(SetPixelFormat, f_SetPixelFormat); SET(SwapBuffers, f_SwapBuffers);
#undef R
#undef SET
	return n;
}
#endif
