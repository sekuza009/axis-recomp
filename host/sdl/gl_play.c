/* gl_play.c: the game's recorded drawing played on a real OpenGL context (gl_play.h). The stream (standalone/glrec64.c,
   glrec.c's format) holds the game's GL / GLU calls in order: the plain ones as their argument words (the op numbers
   given by the stream's header), the ones with pointers with their data copied in, draws (glDrawElements) with the
   arrays' contents. Each is made again here, as the game made it; only these are the host's:
   - texture names: the game's (its glGenTextures was answered by the recorder) mapped to the context's own;
   - the viewport scaled and moved when the game's size is not the drawable's (DESKTOP is 1:1), with black around it;
   - GLU: the system's own when there is one (Windows' glu32, as the original used), else the same calls here. */
#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "gl_play.h"

#ifdef _WIN32
#define GLAPI __stdcall
#else
#define GLAPI
#endif
typedef uint32_t u32;
typedef uint8_t u8;

/* ---- the GL / GLU functions */
#define GL_FUNCS(X) \
	X(void, glBegin, (u32)) X(void, glBindTexture, (u32, u32)) X(void, glBlendFunc, (u32, u32)) X(void, glClear, (u32)) \
	X(void, glClearColor, (float, float, float, float)) X(void, glClearDepth, (double)) X(void, glColor3ub, (u8, u8, u8)) \
	X(void, glColor4f, (float, float, float, float)) X(void, glColor4ub, (u8, u8, u8, u8)) X(void, glCullFace, (u32)) \
	X(void, glDepthFunc, (u32)) X(void, glDisable, (u32)) X(void, glDisableClientState, (u32)) X(void, glEnable, (u32)) \
	X(void, glEnableClientState, (u32)) X(void, glEnd, (void)) X(void, glFogf, (u32, float)) X(void, glFogi, (u32, int)) \
	X(void, glFrontFace, (u32)) X(void, glHint, (u32, u32)) X(void, glLoadIdentity, (void)) X(void, glMatrixMode, (u32)) \
	X(void, glPolygonMode, (u32, u32)) X(void, glPolygonOffset, (float, float)) X(void, glPopMatrix, (void)) \
	X(void, glPushMatrix, (void)) X(void, glRotatef, (float, float, float, float)) X(void, glScalef, (float, float, float)) \
	X(void, glTexCoord2d, (double, double)) X(void, glTexCoord2f, (float, float)) X(void, glTexCoord2i, (int, int)) \
	X(void, glTexEnvf, (u32, u32, float)) X(void, glTexParameterf, (u32, u32, float)) X(void, glTranslatef, (float, float, float)) \
	X(void, glVertex2i, (int, int)) X(void, glVertex3f, (float, float, float)) X(void, glViewport, (int, int, int, int)) \
	X(void, glColor4ubv, (const u8 *)) X(void, glFogfv, (u32, const float *)) X(void, glLoadMatrixf, (const float *)) \
	X(void, glMultMatrixf, (const float *)) X(void, glMultMatrixd, (const double *)) X(void, glTexCoord2fv, (const float *)) \
	X(void, glVertex3fv, (const float *)) X(void, glVertex4fv, (const float *)) X(void, glPixelStorei, (u32, int)) \
	X(void, glVertexPointer, (int, u32, int, const void *)) X(void, glColorPointer, (int, u32, int, const void *)) \
	X(void, glTexCoordPointer, (int, u32, int, const void *)) X(void, glDrawElements, (u32, int, u32, const void *)) \
	X(void, glTexImage2D, (u32, int, int, int, int, int, u32, u32, const void *)) X(void, glTexParameteri, (u32, u32, int)) \
	X(void, glGenTextures, (int, u32 *)) X(void, glOrtho, (double, double, double, double, double, double)) \
	X(void, glTranslated, (double, double, double)) X(void, glScissor, (int, int, int, int))
#define DECL(ret, name, args) static ret (GLAPI *p_##name) args;
GL_FUNCS(DECL)
static void (GLAPI *u_gluLookAt)(double, double, double, double, double, double, double, double, double);
static void (GLAPI *u_gluOrtho2D)(double, double, double, double);
static void (GLAPI *u_gluPerspective)(double, double, double, double);
static int (GLAPI *u_gluBuild2DMipmaps)(u32, int, int, int, u32, u32, const void *);

/* the plain calls, by name: the stream's header says which op each is */
enum { P_BEGIN, P_BINDTEXTURE, P_BLENDFUNC, P_CLEAR, P_CLEARCOLOR, P_CLEARDEPTH, P_COLOR3UB, P_COLOR4F, P_COLOR4UB, P_CULLFACE,
       P_DEPTHFUNC, P_DISABLE, P_DISABLECLIENTSTATE, P_ENABLE, P_ENABLECLIENTSTATE, P_END, P_FOGF, P_FOGI, P_FRONTFACE, P_HINT,
       P_LOADIDENTITY, P_MATRIXMODE, P_POLYGONMODE, P_POLYGONOFFSET, P_POPMATRIX, P_PUSHMATRIX, P_ROTATEF, P_SCALEF,
       P_TEXCOORD2D, P_TEXCOORD2F, P_TEXCOORD2I, P_TEXENVF, P_TEXPARAMETERF, P_TRANSLATEF, P_VERTEX2I, P_VERTEX3F, P_VIEWPORT,
       P_GLULOOKAT, P_GLUORTHO2D, P_GLUPERSPECTIVE, P_COUNT };
static const char *const k_names[P_COUNT] = {
	"glBegin", "glBindTexture", "glBlendFunc", "glClear", "glClearColor", "glClearDepth", "glColor3ub", "glColor4f", "glColor4ub",
	"glCullFace", "glDepthFunc", "glDisable", "glDisableClientState", "glEnable", "glEnableClientState", "glEnd", "glFogf",
	"glFogi", "glFrontFace", "glHint", "glLoadIdentity", "glMatrixMode", "glPolygonMode", "glPolygonOffset", "glPopMatrix",
	"glPushMatrix", "glRotatef", "glScalef", "glTexCoord2d", "glTexCoord2f", "glTexCoord2i", "glTexEnvf", "glTexParameterf",
	"glTranslatef", "glVertex2i", "glVertex3f", "glViewport", "gluLookAt", "gluOrtho2D", "gluPerspective" };
static int g_kind[64];   /* op -> P_*, -1 unknown */
static int g_plainOps;
enum { OP_COLOR4UBV = 64, OP_FOGFV, OP_LOADMATRIX, OP_MULTMATRIX, OP_TEXCOORD2FV, OP_VERTEX3FV, OP_VERTEX4FV, OP_PIXELSTORE,
       OP_DRAW, OP_TEXIMAGE, OP_MIPMAPS, OP_TEXPARAMI, OP_TAG, OP_CAMERA };   /* (tags, camera: the Godot remaster's notes) */

int gl_play_init(void *(*getProc)(const char *name), void *(*getGlu)(const char *name), const unsigned char *header,
                 unsigned headerBytes, char *error, int room)
{
#define LOAD(ret, name, args) \
	if (!(*(void **)&p_##name = getProc(#name))) { if (error) snprintf_(error, room, "no OpenGL function " #name); return 0; }
#define snprintf_(e, r, s) do { strncpy(e, s, (size_t)(r) - 1); (e)[(r) - 1] = 0; } while (0)
	GL_FUNCS(LOAD)
	if (getGlu) {
		*(void **)&u_gluLookAt = getGlu("gluLookAt");
		*(void **)&u_gluOrtho2D = getGlu("gluOrtho2D");
		*(void **)&u_gluPerspective = getGlu("gluPerspective");
		*(void **)&u_gluBuild2DMipmaps = getGlu("gluBuild2DMipmaps");
	}
	if (headerBytes < 12 || memcmp(header, "AXGLREC1", 8)) {
		snprintf_(error, room, "the stream's header is not AXGLREC1");
		return 0;
	}
	u32 n;
	memcpy(&n, header + 8, 4);
	unsigned o = 12;
	g_plainOps = (int)n;
	for (u32 i = 0; i < n && i < 64; i++) {
		u32 w, l;
		memcpy(&w, header + o, 4);
		memcpy(&l, header + o + 4, 4);
		g_kind[i] = -1;
		for (int k = 0; k < P_COUNT; k++)
			if (strlen(k_names[k]) == l && !memcmp(header + o + 8, k_names[k], l))
				g_kind[i] = k;
		o += 8 + l;
	}
	return 1;
}

/* ---- texture names: the game's -> the context's */
static u32 *g_tex;
static u32 g_texRoom;
static u32 tex_of(u32 name)
{
	if (!name)
		return 0;
	if (name >= g_texRoom) {
		u32 room = g_texRoom ? g_texRoom : 1024;
		while (room <= name)
			room *= 2;
		u32 *more = realloc(g_tex, room * sizeof *more);
		if (!more)
			return 0;
		memset(more + g_texRoom, 0, (room - g_texRoom) * sizeof *more);
		g_tex = more;
		g_texRoom = room;
	}
	if (!g_tex[name])
		p_glGenTextures(1, &g_tex[name]);
	return g_tex[name];
}

/* ---- the frame's place in the drawable: scale and offset (1 and 0 at DESKTOP) */
static double g_s = 1;
static int g_ox, g_oy, g_fit;   /* fit: the game's size differs from the drawable's */
static int g_vp[4];             /* the game's own viewport */
static float g_clear[4];        /* the game's clear colour */
static void viewport(void)
{
	p_glViewport(g_ox + (int)lround(g_vp[0] * g_s), g_oy + (int)lround(g_vp[1] * g_s), (int)lround(g_vp[2] * g_s),
	             (int)lround(g_vp[3] * g_s));
}

/* ---- GLU, when the system has none: the same as GLU's */
static void glu_ortho2d(double l, double r, double b, double t)
{
	if (u_gluOrtho2D) u_gluOrtho2D(l, r, b, t);
	else p_glOrtho(l, r, b, t, -1, 1);
}
static void glu_perspective(double fovy, double aspect, double zn, double zf)
{
	if (u_gluPerspective) {
		u_gluPerspective(fovy, aspect, zn, zf);
		return;
	}
	double a = fovy / 2 * 3.14159265358979323846 / 180, dz = zf - zn, s = sin(a);
	if (dz == 0 || s == 0 || aspect == 0)
		return;
	double c = cos(a) / s, m[16] = { 0 };
	m[0] = c / aspect;
	m[5] = c;
	m[10] = -(zf + zn) / dz;
	m[11] = -1;
	m[14] = -2 * zn * zf / dz;
	p_glMultMatrixd(m);
}
static void glu_lookat(double ex, double ey, double ez, double cx, double cy, double cz, double ux, double uy, double uz)
{
	if (u_gluLookAt) {
		u_gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz);
		return;
	}
	double f[3] = { cx - ex, cy - ey, cz - ez }, up[3] = { ux, uy, uz }, s[3], u[3];
	double n = sqrt(f[0] * f[0] + f[1] * f[1] + f[2] * f[2]);
	if (n > 0) { f[0] /= n; f[1] /= n; f[2] /= n; }
	s[0] = f[1] * up[2] - f[2] * up[1]; s[1] = f[2] * up[0] - f[0] * up[2]; s[2] = f[0] * up[1] - f[1] * up[0];
	n = sqrt(s[0] * s[0] + s[1] * s[1] + s[2] * s[2]);
	if (n > 0) { s[0] /= n; s[1] /= n; s[2] /= n; }
	u[0] = s[1] * f[2] - s[2] * f[1]; u[1] = s[2] * f[0] - s[0] * f[2]; u[2] = s[0] * f[1] - s[1] * f[0];
	double m[16] = { s[0], u[0], -f[0], 0, s[1], u[1], -f[1], 0, s[2], u[2], -f[2], 0, 0, 0, 0, 1 };
	p_glMultMatrixd(m);
	p_glTranslated(-ex, -ey, -ez);
}
/* gluBuild2DMipmaps without GLU: the image as RGBA, box-scaled to the power of two at or below its size, then halved
   level by level to 1 x 1 (as godot/extension's gl_emu.cpp - the original's glu32 scales likewise) */
static int g_unpack = 4;
static void glu_mipmaps(u32 target, int comps, int w, int h, u32 fmt, u32 type, const u8 *src)
{
	if (u_gluBuild2DMipmaps) {
		u_gluBuild2DMipmaps(target, comps, w, h, fmt, type, src);
		return;
	}
	if (w <= 0 || h <= 0 || !src || type != 0x1401)
		return;
	int cn = fmt == 0x1907 || fmt == 0x80e0 ? 3 : fmt == 0x1908 || fmt == 0x80e1 ? 4 : fmt == 0x190a ? 2 : 1;
	size_t row = (size_t)w * cn, a = g_unpack > 0 ? (size_t)g_unpack : 1, stride = (row + a - 1) / a * a;
	u8 *rgba = malloc((size_t)w * h * 4);
	if (!rgba)
		return;
	for (int y = 0; y < h; y++)
		for (int x = 0; x < w; x++) {
			const u8 *s = src + (size_t)y * stride + (size_t)x * cn;
			u8 *d = rgba + ((size_t)y * w + x) * 4;
			switch (fmt) {
			case 0x1907: d[0] = s[0]; d[1] = s[1]; d[2] = s[2]; d[3] = 255; break;
			case 0x1908: memcpy(d, s, 4); break;
			case 0x80e0: d[0] = s[2]; d[1] = s[1]; d[2] = s[0]; d[3] = 255; break;
			case 0x80e1: d[0] = s[2]; d[1] = s[1]; d[2] = s[0]; d[3] = s[3]; break;
			case 0x190a: d[0] = d[1] = d[2] = s[0]; d[3] = s[1]; break;
			case 0x1906: d[0] = d[1] = d[2] = 255; d[3] = s[0]; break;
			default: d[0] = d[1] = d[2] = s[0]; d[3] = 255; break;
			}
		}
	int pw = 1, ph = 1;
	while (pw * 2 <= w) pw *= 2;
	while (ph * 2 <= h) ph *= 2;
	u8 *lv = malloc((size_t)pw * ph * 4);
	if (!lv) {
		free(rgba);
		return;
	}
	for (int y = 0; y < ph; y++)
		for (int x = 0; x < pw; x++) {
			int x0 = x * w / pw, x1 = ((x + 1) * w + pw - 1) / pw, y0 = y * h / ph, y1 = ((y + 1) * h + ph - 1) / ph;
			for (int c = 0; c < 4; c++) {
				unsigned sum = 0, cnt = 0;
				for (int yy = y0; yy < y1; yy++)
					for (int xx = x0; xx < x1; xx++) { sum += rgba[((size_t)yy * w + xx) * 4 + c]; cnt++; }
				lv[((size_t)y * pw + x) * 4 + c] = (u8)(cnt ? (sum + cnt / 2) / cnt : 0);
			}
		}
	free(rgba);
	p_glPixelStorei(0x0cf5, 1);
	for (int level = 0;; level++) {
		p_glTexImage2D(target, level, comps, pw, ph, 0, 0x1908, 0x1401, lv);
		if (pw == 1 && ph == 1)
			break;
		int nw = pw > 1 ? pw / 2 : 1, nh = ph > 1 ? ph / 2 : 1;
		for (int y = 0; y < nh; y++)
			for (int x = 0; x < nw; x++)
				for (int c = 0; c < 4; c++) {
					int xa = x * pw / nw, xb = pw > 1 ? xa + 1 : xa, ya = y * ph / nh, yb = ph > 1 ? ya + 1 : ya;
					unsigned v = lv[((size_t)ya * pw + xa) * 4 + c] + lv[((size_t)ya * pw + xb) * 4 + c] +
					             lv[((size_t)yb * pw + xa) * 4 + c] + lv[((size_t)yb * pw + xb) * 4 + c];
					lv[((size_t)y * nw + x) * 4 + c] = (u8)((v + 2) / 4);
				}
		pw = nw;
		ph = nh;
	}
	p_glPixelStorei(0x0cf5, g_unpack);
	free(lv);
}

/* ---- the frame */
static float F(u32 w) { float f; memcpy(&f, &w, 4); return f; }
static double D(const u32 *w) { double d; memcpy(&d, w, 8); return d; }
static int type_size(u32 t) { return t == 0x1401 || t == 0x1400 ? 1 : t == 0x1402 || t == 0x1403 ? 2 : t == 0x140a ? 8 : 4; }

static void plain(int kind, const u32 *a)
{
	switch (kind) {
	case P_BEGIN: p_glBegin(a[0]); break;
	case P_BINDTEXTURE: p_glBindTexture(a[0], tex_of(a[1])); break;
	case P_BLENDFUNC: p_glBlendFunc(a[0], a[1]); break;
	case P_CLEAR: p_glClear(a[0]); break;
	case P_CLEARCOLOR: g_clear[0] = F(a[0]); g_clear[1] = F(a[1]); g_clear[2] = F(a[2]); g_clear[3] = F(a[3]);
		p_glClearColor(g_clear[0], g_clear[1], g_clear[2], g_clear[3]); break;
	case P_CLEARDEPTH: p_glClearDepth(D(a)); break;
	case P_COLOR3UB: p_glColor3ub((u8)a[0], (u8)a[1], (u8)a[2]); break;
	case P_COLOR4F: p_glColor4f(F(a[0]), F(a[1]), F(a[2]), F(a[3])); break;
	case P_COLOR4UB: p_glColor4ub((u8)a[0], (u8)a[1], (u8)a[2], (u8)a[3]); break;
	case P_CULLFACE: p_glCullFace(a[0]); break;
	case P_DEPTHFUNC: p_glDepthFunc(a[0]); break;
	case P_DISABLE: if (a[0] != 0x0c11) p_glDisable(a[0]); break;   /* (the scissor test is the host's: the frame's place) */
	case P_DISABLECLIENTSTATE: p_glDisableClientState(a[0]); break;
	case P_ENABLE: if (a[0] != 0x0c11) p_glEnable(a[0]); break;
	case P_ENABLECLIENTSTATE: p_glEnableClientState(a[0]); break;
	case P_END: p_glEnd(); break;
	case P_FOGF: p_glFogf(a[0], F(a[1])); break;
	case P_FOGI: p_glFogi(a[0], (int)a[1]); break;
	case P_FRONTFACE: p_glFrontFace(a[0]); break;
	case P_HINT: p_glHint(a[0], a[1]); break;
	case P_LOADIDENTITY: p_glLoadIdentity(); break;
	case P_MATRIXMODE: p_glMatrixMode(a[0]); break;
	case P_POLYGONMODE: p_glPolygonMode(a[0], a[1]); break;
	case P_POLYGONOFFSET: p_glPolygonOffset(F(a[0]), F(a[1])); break;
	case P_POPMATRIX: p_glPopMatrix(); break;
	case P_PUSHMATRIX: p_glPushMatrix(); break;
	case P_ROTATEF: p_glRotatef(F(a[0]), F(a[1]), F(a[2]), F(a[3])); break;
	case P_SCALEF: p_glScalef(F(a[0]), F(a[1]), F(a[2])); break;
	case P_TEXCOORD2D: p_glTexCoord2d(D(a), D(a + 2)); break;
	case P_TEXCOORD2F: p_glTexCoord2f(F(a[0]), F(a[1])); break;
	case P_TEXCOORD2I: p_glTexCoord2i((int)a[0], (int)a[1]); break;
	case P_TEXENVF: p_glTexEnvf(a[0], a[1], F(a[2])); break;
	case P_TEXPARAMETERF: p_glTexParameterf(a[0], a[1], F(a[2])); break;
	case P_TRANSLATEF: p_glTranslatef(F(a[0]), F(a[1]), F(a[2])); break;
	case P_VERTEX2I: p_glVertex2i((int)a[0], (int)a[1]); break;
	case P_VERTEX3F: p_glVertex3f(F(a[0]), F(a[1]), F(a[2])); break;
	case P_VIEWPORT:
		g_vp[0] = (int)a[0]; g_vp[1] = (int)a[1]; g_vp[2] = (int)a[2]; g_vp[3] = (int)a[3];
		viewport();
		break;
	case P_GLULOOKAT: glu_lookat(D(a), D(a + 2), D(a + 4), D(a + 6), D(a + 8), D(a + 10), D(a + 12), D(a + 14), D(a + 16)); break;
	case P_GLUORTHO2D: glu_ortho2d(D(a), D(a + 2), D(a + 4), D(a + 6)); break;
	case P_GLUPERSPECTIVE: glu_perspective(D(a), D(a + 2), D(a + 4), D(a + 6)); break;
	}
}

void gl_play_frame(const unsigned *words, unsigned count, int width, int height, int drawW, int drawH)
{
	if (width <= 0 || height <= 0) {
		width = drawW;
		height = drawH;
	}
	if (!g_vp[2]) {   /* (a new context's viewport: the game's whole frame) */
		g_vp[2] = width;
		g_vp[3] = height;
	}
	g_fit = width != drawW || height != drawH;
	if (g_fit) {   /* (the game's frame scaled into the drawable, black around it; drawn only inside it) */
		g_s = (double)drawW / width < (double)drawH / height ? (double)drawW / width : (double)drawH / height;
		int w = (int)lround(width * g_s), h = (int)lround(height * g_s);
		g_ox = (drawW - w) / 2;
		g_oy = (drawH - h) / 2;
		p_glDisable(0x0c11);
		p_glViewport(0, 0, drawW, drawH);
		p_glClearColor(0, 0, 0, 1);
		p_glClear(0x4000);
		p_glClearColor(g_clear[0], g_clear[1], g_clear[2], g_clear[3]);
		p_glScissor(g_ox, g_oy, w, h);
		p_glEnable(0x0c11);
	} else {
		g_s = 1;
		g_ox = g_oy = 0;
		p_glDisable(0x0c11);
	}
	viewport();
	const u32 *p = words, *end = words + count;
	while (p < end) {
		u32 h = *p++, op = h & 0xffff, n = h >> 16;
		if ((int)op < g_plainOps && op < 64) {
			if (g_kind[op] >= 0)
				plain(g_kind[op], p);
			p += n;
			continue;
		}
		switch (op) {
		case OP_COLOR4UBV: p_glColor4ubv((const u8 *)p); p += 1; break;
		case OP_FOGFV: { float v[4] = { F(p[1]), F(p[2]), F(p[3]), F(p[4]) }; p_glFogfv(p[0], v); p += 5; break; }
		case OP_LOADMATRIX: p_glLoadMatrixf((const float *)p); p += 16; break;
		case OP_MULTMATRIX: p_glMultMatrixf((const float *)p); p += 16; break;
		case OP_TEXCOORD2FV: p_glTexCoord2fv((const float *)p); p += 2; break;
		case OP_VERTEX3FV: p_glVertex3fv((const float *)p); p += 3; break;
		case OP_VERTEX4FV: p_glVertex4fv((const float *)p); p += 4; break;
		case OP_PIXELSTORE: if (p[0] == 0x0cf5) g_unpack = (int)p[1]; p_glPixelStorei(p[0], (int)p[1]); p += 2; break;
		case OP_TEXPARAMI: p_glTexParameteri(p[0], p[1], (int)p[2]); p += 3; break;
		case OP_TAG: p += 1; break;       /* (what the drawing is: nothing to draw here) */
		case OP_CAMERA: p += 32; break;
		case OP_DRAW: {   /* the arrays' contents as recorded (tightly packed), then the indices drawn */
			u32 mode = p[0], cnt = p[1], itype = p[2], nv = p[3];
			p += 4;
			const void *idx = p;
			p += ((size_t)cnt * type_size(itype) + 3) / 4;
			for (int arr = 0; arr < 3; arr++) {
				if (!*p++)
					continue;
				int size = (int)p[0];
				u32 type = p[1];
				p += 2;
				if (arr == 0) p_glVertexPointer(size, type, 0, p);
				else if (arr == 1) p_glColorPointer(size, type, 0, p);
				else p_glTexCoordPointer(size, type, 0, p);
				p += ((size_t)nv * size * type_size(type) + 3) / 4;
			}
			p_glDrawElements(mode, (int)cnt, itype, idx);
			break;
		}
		case OP_TEXIMAGE: {
			u32 nb = p[8];
			p_glTexImage2D(p[0], (int)p[1], (int)p[2], (int)p[3], (int)p[4], (int)p[5], p[6], p[7], nb ? (const void *)(p + 9) : NULL);
			p += 9 + (nb + 3) / 4;
			break;
		}
		case OP_MIPMAPS: {
			u32 nb = p[6];
			glu_mipmaps(p[0], (int)p[1], (int)p[2], (int)p[3], p[4], p[5], nb ? (const u8 *)(p + 7) : NULL);
			p += 7 + (nb + 3) / 4;
			break;
		}
		default: {   /* (an op this player does not know: the rest of the frame cannot be read) */
			static int told;
			if (!told++)
				fprintf(stderr, "gl_play: unknown op %u (word %u of %u) - the rest of the frame skipped\n", op,
				        (unsigned)(p - words - 1), count);
			return;
		}
		}
	}
}
