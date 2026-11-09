/* glrec.c: the game's drawing recorded as a command stream, and the stream proved complete (PORTING.md: the
   rendering seam, step 2). A platform without OpenGL (Godot) will draw the game from such a stream; this checks
   that the stream holds everything the game draws.

   AXIS_GLREC=1: a layer in front of the game's GL import slots. Every GL / GLU call still goes to the driver as
   before, and is appended to a stream - with the data its pointers point at copied in (matrices, vectors, the
   vertex arrays a draw reads, texture pixels), so the stream stands alone. At each SwapBuffers the stream since the
   last one is replayed into a second, hidden GL context drawing into an offscreen framebuffer of the window's size;
   every AXIS_GLREC_EVERY-th frame (default 30) the game's back buffer and the replay's image are read back and
   compared pixel for pixel. glrec.log (game folder): frames compared, identical, differing (the first few differing
   pairs saved as glrec_<n>_game.ppm / _replay.ppm). Queries (glGet*) are answered by the driver and not recorded;
   texture names are the game's own (bound by name in the replay).

   Calls are recorded by a small thunk per function (the stack words copied, then a jump to the driver's function),
   the ones with pointers, draws and textures by their own wrappers. Compiled into the portable loader. */
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned u32;
#define S __stdcall

/* ---- the stream ---- */
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
static void put_bytes(const void *p, size_t n)   /* n bytes, padded to words */
{
	const unsigned char *b = p;
	for (size_t i = 0; i < n; i += 4) {
		u32 w = 0;
		memcpy(&w, b + i, n - i < 4 ? n - i : 4);
		put(w);
	}
}

/* ---- the plain calls: words only. op index, name, words of arguments ---- */
#define PLAIN(X) \
	X(0, glBegin, 1) X(1, glBindTexture, 2) X(2, glBlendFunc, 2) X(3, glClear, 1) X(4, glClearColor, 4) \
	X(5, glClearDepth, 2) X(6, glColor3ub, 3) X(7, glColor4f, 4) X(8, glColor4ub, 4) X(9, glCullFace, 1) \
	X(10, glDepthFunc, 1) X(11, glDisable, 1) X(12, glDisableClientState, 1) X(13, glEnable, 1) \
	X(14, glEnableClientState, 1) X(15, glEnd, 0) X(16, glFogf, 2) X(17, glFogi, 2) X(18, glFrontFace, 1) \
	X(19, glHint, 2) X(20, glLoadIdentity, 0) X(21, glMatrixMode, 1) X(22, glPolygonMode, 2) \
	X(23, glPolygonOffset, 2) X(24, glPopMatrix, 0) X(25, glPushMatrix, 0) X(26, glRotatef, 4) X(27, glScalef, 3) \
	X(28, glTexCoord2d, 4) X(29, glTexCoord2f, 2) X(30, glTexCoord2i, 2) X(31, glTexEnvf, 3) \
	X(32, glTexParameterf, 3) X(33, glTranslatef, 3) X(34, glVertex2i, 2) X(35, glVertex3f, 3) X(36, glViewport, 4) \
	X(37, gluLookAt, 18) X(38, gluOrtho2D, 8) X(39, gluPerspective, 8)
#define NPLAIN 40
static const struct { const char *name; int words; } k_plain[NPLAIN] = {
#define ROW_(i, n, w) { #n, w },
	PLAIN(ROW_)
#undef ROW_
};
void *g_glrecReal[NPLAIN];   /* the driver's functions, by op (the thunks jump through it) */
static int g_recording = 1;

/* the thunks: eax = op; the common part records the words above the return address, then jumps to the driver's
   function with the stack untouched (stdcall: it pops its own arguments) */
void glrec_record(int op, const u32 *args)
{
	if (!g_recording)
		return;
	put((u32)op | (u32)k_plain[op].words << 16);
	for (int i = 0; i < k_plain[op].words; i++)
		put(args[i]);
}
__asm__(".text\n_glrec_common:\n\tpush %eax\n\tlea 8(%esp), %ecx\n\tpush %ecx\n\tpush %eax\n\tcall _glrec_record\n"
        "\tadd $8, %esp\n\tpop %eax\n\tjmp *_g_glrecReal(,%eax,4)\n");
#define THUNK_(i, n, w) __asm__(".text\n_glrec_t" #i ":\n\tmov $" #i ", %eax\n\tjmp _glrec_common\n"); void glrec_t##i(void);
PLAIN(THUNK_)
#undef THUNK_
static void (*const k_thunk[NPLAIN])(void) = {
#define T_(i, n, w) glrec_t##i,
	PLAIN(T_)
#undef T_
};

/* the replay of a plain call: the words pushed again (each stdcall argument is whole words on the stack) */
typedef u32 W;
static void call_words(void *f, const W *a, int n)
{
	switch (n) {
	case 0: ((void (S *)(void))f)(); break;
	case 1: ((void (S *)(W))f)(a[0]); break;
	case 2: ((void (S *)(W, W))f)(a[0], a[1]); break;
	case 3: ((void (S *)(W, W, W))f)(a[0], a[1], a[2]); break;
	case 4: ((void (S *)(W, W, W, W))f)(a[0], a[1], a[2], a[3]); break;
	case 8: ((void (S *)(W, W, W, W, W, W, W, W))f)(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]); break;
	case 18: ((void (S *)(W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W))f)(a[0], a[1], a[2], a[3], a[4], a[5],
	         a[6], a[7], a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15], a[16], a[17]); break;
	}
}

/* ---- the calls with pointers, draws, textures: their own wrappers (ops from 64) ---- */
enum { OP_COLOR4UBV = 64, OP_FOGFV, OP_LOADMATRIX, OP_MULTMATRIX, OP_TEXCOORD2FV, OP_VERTEX3FV, OP_VERTEX4FV,
       OP_PIXELSTORE, OP_DRAW, OP_TEXIMAGE, OP_MIPMAPS, OP_TEXPARAMI };
/* the fixes' pixel-sharp text (standalone/platform.c) sets texture filters with glTexParameteri, which the game does
   not import: its pointers, set here before its first use */
extern void (S *g_texParameteri)(u32, u32, int);
extern void (S *g_getTexParameteriv)(u32, u32, int *);
static void (S *r_glTexParameteri)(u32, u32, int);
static void S w_glTexParameteri(u32 t, u32 p, int v) { r_glTexParameteri(t, p, v); put((u32)OP_TEXPARAMI | 3u << 16); put(t); put(p); put((u32)v); }
static void (S *r_glColor4ubv)(const void *), (S *r_glFogfv)(u32, const float *), (S *r_glLoadMatrixf)(const float *),
	(S *r_glMultMatrixf)(const float *), (S *r_glTexCoord2fv)(const float *), (S *r_glVertex3fv)(const float *),
	(S *r_glVertex4fv)(const float *), (S *r_glPixelStorei)(u32, int),
	(S *r_glVertexPointer)(int, u32, int, const void *), (S *r_glColorPointer)(int, u32, int, const void *),
	(S *r_glTexCoordPointer)(int, u32, int, const void *), (S *r_glDrawElements)(u32, int, u32, const void *),
	(S *r_glTexImage2D)(u32, int, int, int, int, int, u32, u32, const void *),
	(S *r_glEnableClientState)(u32), (S *r_glDisableClientState)(u32);
static int (S *r_gluBuild2DMipmaps)(u32, int, int, int, u32, u32, const void *);
static void *(S *r_wglGetProcAddress)(const char *);
static int (S *r_wglMakeCurrent)(HDC, HGLRC);
static BOOL (S *r_SwapBuffers)(HDC);

static void put_op(int op, int words) { put((u32)op | (u32)words << 16); }
static void S w_glColor4ubv(const void *v) { r_glColor4ubv(v); put_op(OP_COLOR4UBV, 1); put_bytes(v, 4); }
static void S w_glFogfv(u32 p, const float *v) { r_glFogfv(p, v); put_op(OP_FOGFV, 5); put(p); put_bytes(v, 16); }
static void S w_glLoadMatrixf(const float *m) { r_glLoadMatrixf(m); put_op(OP_LOADMATRIX, 16); put_bytes(m, 64); }
static void S w_glMultMatrixf(const float *m) { r_glMultMatrixf(m); put_op(OP_MULTMATRIX, 16); put_bytes(m, 64); }
static void S w_glTexCoord2fv(const float *v) { r_glTexCoord2fv(v); put_op(OP_TEXCOORD2FV, 2); put_bytes(v, 8); }
static void S w_glVertex3fv(const float *v) { r_glVertex3fv(v); put_op(OP_VERTEX3FV, 3); put_bytes(v, 12); }
static void S w_glVertex4fv(const float *v) { r_glVertex4fv(v); put_op(OP_VERTEX4FV, 4); put_bytes(v, 16); }
static int g_unpackAlign = 4;
static void S w_glPixelStorei(u32 p, int v)
{
	r_glPixelStorei(p, v);
	if (p == 0x0cf5)   /* GL_UNPACK_ALIGNMENT */
		g_unpackAlign = v;
	put_op(OP_PIXELSTORE, 2); put(p); put((u32)v);
}

/* the client arrays as the game set them (the data copied at each draw) */
typedef struct { int size; u32 type; int stride; const void *ptr; int on; } Array;
static Array g_arr[3];   /* vertex, colour, texture coordinates */
static int type_size(u32 t)
{
	switch (t) {
	case 0x1400: case 0x1401: return 1;   /* GL_BYTE, GL_UNSIGNED_BYTE */
	case 0x1402: case 0x1403: return 2;   /* GL_SHORT, GL_UNSIGNED_SHORT */
	case 0x140a: return 8;                /* GL_DOUBLE */
	default: return 4;                    /* GL_INT, GL_UNSIGNED_INT, GL_FLOAT */
	}
}
static int array_of(u32 cap) { return cap == 0x8074 ? 0 : cap == 0x8076 ? 1 : cap == 0x8078 ? 2 : -1; }
static void S w_glEnableClientState(u32 cap)
{
	r_glEnableClientState(cap);
	int a = array_of(cap);
	if (a >= 0) g_arr[a].on = 1;   /* (recorded by the thunk this calls) */
}
static void S w_glDisableClientState(u32 cap)
{
	r_glDisableClientState(cap);
	int a = array_of(cap);
	if (a >= 0) g_arr[a].on = 0;
}
static void set_array(int a, int size, u32 type, int stride, const void *p)
{
	g_arr[a].size = size; g_arr[a].type = type; g_arr[a].stride = stride; g_arr[a].ptr = p;
}
static void S w_glVertexPointer(int s, u32 t, int st, const void *p) { r_glVertexPointer(s, t, st, p); set_array(0, s, t, st, p); }
static void S w_glColorPointer(int s, u32 t, int st, const void *p) { r_glColorPointer(s, t, st, p); set_array(1, s, t, st, p); }
static void S w_glTexCoordPointer(int s, u32 t, int st, const void *p) { r_glTexCoordPointer(s, t, st, p); set_array(2, s, t, st, p); }
/* the EXT_vertex_array forms the game looks up (an extra count argument) */
static void (S *r_glVertexPointerEXT)(int, u32, int, int, const void *), (S *r_glColorPointerEXT)(int, u32, int, int, const void *),
	(S *r_glTexCoordPointerEXT)(int, u32, int, int, const void *);
static void S w_glVertexPointerEXT(int s, u32 t, int st, int n, const void *p) { r_glVertexPointerEXT(s, t, st, n, p); set_array(0, s, t, st, p); }
static void S w_glColorPointerEXT(int s, u32 t, int st, int n, const void *p) { r_glColorPointerEXT(s, t, st, n, p); set_array(1, s, t, st, p); }
static void S w_glTexCoordPointerEXT(int s, u32 t, int st, int n, const void *p) { r_glTexCoordPointerEXT(s, t, st, n, p); set_array(2, s, t, st, p); }
static void *S w_wglGetProcAddress(const char *name)
{
	void *f = r_wglGetProcAddress(name);
	if (!f)
		return f;
	if (!strcmp(name, "glVertexPointerEXT")) { *(void **)&r_glVertexPointerEXT = f; return (void *)w_glVertexPointerEXT; }
	if (!strcmp(name, "glColorPointerEXT")) { *(void **)&r_glColorPointerEXT = f; return (void *)w_glColorPointerEXT; }
	if (!strcmp(name, "glTexCoordPointerEXT")) { *(void **)&r_glTexCoordPointerEXT = f; return (void *)w_glTexCoordPointerEXT; }
	return f;
}

/* a draw: the mode, the indices, and the enabled arrays' elements up to the largest index, packed */
static void S w_glDrawElements(u32 mode, int count, u32 itype, const void *idx)
{
	r_glDrawElements(mode, count, itype, idx);
	u32 top = 0;
	for (int i = 0; i < count; i++) {
		u32 v = itype == 0x1401 ? ((const unsigned char *)idx)[i] : itype == 0x1403 ? ((const unsigned short *)idx)[i] : ((const u32 *)idx)[i];
		if (v > top) top = v;
	}
	u32 n = count ? top + 1 : 0;
	size_t words = 4 + (size_t)(count * type_size(itype) + 3) / 4;
	for (int a = 0; a < 3; a++)
		if (g_arr[a].on)
			words += 3 + (n * g_arr[a].size * type_size(g_arr[a].type) + 3) / 4;
	put_op(OP_DRAW, (int)(words > 0xffff ? 0xffff : words));   /* (the length is read from the contents) */
	put(mode); put((u32)count); put(itype); put(n);
	put_bytes(idx, (size_t)count * type_size(itype));
	for (int a = 0; a < 3; a++) {
		put((u32)g_arr[a].on);
		if (!g_arr[a].on)
			continue;
		int el = g_arr[a].size * type_size(g_arr[a].type), st = g_arr[a].stride ? g_arr[a].stride : el;
		put((u32)g_arr[a].size); put(g_arr[a].type);
		u32 w = 0;
		int fill = 0;
		for (u32 i = 0; i < n; i++)   /* (packed: element after element, words padded at the end) */
			for (int b = 0; b < el; b++) {
				w |= (u32)((const unsigned char *)g_arr[a].ptr)[(size_t)i * st + b] << (8 * fill);
				if (++fill == 4) { put(w); w = 0; fill = 0; }
			}
		if (fill)
			put(w);
	}
}

/* a texture image's bytes as the driver reads them (rows aligned to the unpack alignment) */
static size_t image_bytes(int w, int h, u32 format, u32 type)
{
	int comps = format == 0x1907 ? 3 : format == 0x1908 ? 4 : format == 0x190a ? 2 : format == 0x80e0 ? 3 : format == 0x80e1 ? 4 : 1;
	int px = type == 0x1401 || type == 0x1400 ? comps : (type == 0x8033 || type == 0x8034 || type == 0x8363) ? 2 : comps * type_size(type);
	size_t row = (size_t)w * px, a = g_unpackAlign > 0 ? (size_t)g_unpackAlign : 1;
	size_t stride = (row + a - 1) / a * a;
	return h > 0 ? stride * (h - 1) + row : 0;
}
static void S w_glTexImage2D(u32 target, int level, int ifmt, int w, int h, int border, u32 fmt, u32 type, const void *p)
{
	r_glTexImage2D(target, level, ifmt, w, h, border, fmt, type, p);
	size_t n = p ? image_bytes(w, h, fmt, type) : 0;
	put_op(OP_TEXIMAGE, 0xffff);
	put(target); put((u32)level); put((u32)ifmt); put((u32)w); put((u32)h); put((u32)border); put(fmt); put(type);
	put((u32)n);
	put_bytes(p, n);
}
static int S w_gluBuild2DMipmaps(u32 target, int comps, int w, int h, u32 fmt, u32 type, const void *p)
{
	int r = r_gluBuild2DMipmaps(target, comps, w, h, fmt, type, p);
	size_t n = p ? image_bytes(w, h, fmt, type) : 0;
	put_op(OP_MIPMAPS, 0xffff);
	put(target); put((u32)comps); put((u32)w); put((u32)h); put(fmt); put(type); put((u32)n);
	put_bytes(p, n);
	return r;
}

/* ---- the replay context: a hidden window of the game window's pixel format, an offscreen framebuffer ---- */
static HDC g_gameDC;
static HGLRC g_gameRC, g_shadowRC;
static HDC g_shadowDC;
static int g_fbW, g_fbH;
static u32 g_fbo, g_rbColor, g_rbDepth;
static void (S *f_genFB)(int, u32 *), (S *f_bindFB)(u32, u32), (S *f_genRB)(int, u32 *), (S *f_bindRB)(u32, u32),
	(S *f_rbStorage)(u32, u32, int, int), (S *f_fbRB)(u32, u32, u32, u32), (S *f_delFB)(int, const u32 *), (S *f_delRB)(int, const u32 *);
static void (S *g_readPixels)(int, int, int, int, u32, u32, void *), (S *g_readBuffer)(u32), (S *g_getIntegerv)(u32, int *);

static int g_useFbo;   /* (AXIS_GLREC_FBO: see shadow_make) */
static char g_dir[MAX_PATH];
static unsigned g_frames, g_compared, g_same, g_differ, g_saved, g_every = 30, g_errors;
static double g_worst;
static FILE *g_logf;

static void report(void)
{
	char p[MAX_PATH];
	snprintf(p, sizeof p, "%sglrec.log", g_dir);
	FILE *f = fopen(p, "w");
	if (!f)
		return;
	fprintf(f, "glrec: the game's drawing recorded and replayed in a second context (%s), compared every %u frames\n"
	        "  frames %u, compared %u, identical %u, differing %u (largest share of pixels differing in one: %.6f)\n"
	        "  stream errors %u (an unknown texture format, a context not made)\n",
	        g_useFbo ? "a framebuffer object" : "a hidden window's back buffer", g_every, g_frames, g_compared, g_same, g_differ, g_worst, g_errors);
	fclose(f);
}

static void save_ppm(const char *what, const unsigned char *px, int w, int h)
{
	char p[MAX_PATH];
	snprintf(p, sizeof p, "%sglrec_%u_%s.ppm", g_dir, g_saved, what);
	FILE *f = fopen(p, "wb");
	if (!f)
		return;
	fprintf(f, "P6\n%d %d\n255\n", w, h);
	for (int y = h - 1; y >= 0; y--)
		for (int x = 0; x < w; x++)
			fwrite(px + ((size_t)y * w + x) * 4, 1, 3, f);
	fclose(f);
}

/* the replay drawn into the hidden window's own back buffer (default), as the game draws into its window's: the
   driver lays a window's buffer out otherwise than a framebuffer object's (rows the other way up), which moves where
   samples fall by a hair - pixel-sharp text and filtered textures then round differently. AXIS_GLREC_FBO=1: into a
   framebuffer object instead */
static HWND g_shadowWnd;
static int shadow_make(int w, int h)
{
	if (!g_shadowRC) {
		WNDCLASSA wc = { 0 };
		wc.lpfnWndProc = DefWindowProcA;
		wc.hInstance = GetModuleHandleA(NULL);
		wc.lpszClassName = "glrec_shadow";
		RegisterClassA(&wc);
		RECT r = { 0, 0, w, h };
		AdjustWindowRect(&r, WS_POPUP, FALSE);
		HWND wnd = CreateWindowA("glrec_shadow", "glrec", WS_POPUP, 0, 0, r.right - r.left, r.bottom - r.top, NULL, NULL, wc.hInstance, NULL);
		g_shadowWnd = wnd;
		g_shadowDC = GetDC(wnd);
		int pf = GetPixelFormat(g_gameDC);
		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(g_gameDC, pf, sizeof pfd, &pfd);
		if (!SetPixelFormat(g_shadowDC, pf, &pfd) || !(g_shadowRC = wglCreateContext(g_shadowDC)))
			return 0;
		r_wglMakeCurrent(g_shadowDC, g_shadowRC);
		*(void **)&f_genFB = r_wglGetProcAddress("glGenFramebuffersEXT");
		*(void **)&f_bindFB = r_wglGetProcAddress("glBindFramebufferEXT");
		*(void **)&f_genRB = r_wglGetProcAddress("glGenRenderbuffersEXT");
		*(void **)&f_bindRB = r_wglGetProcAddress("glBindRenderbufferEXT");
		*(void **)&f_rbStorage = r_wglGetProcAddress("glRenderbufferStorageEXT");
		*(void **)&f_fbRB = r_wglGetProcAddress("glFramebufferRenderbufferEXT");
		*(void **)&f_delFB = r_wglGetProcAddress("glDeleteFramebuffersEXT");
		*(void **)&f_delRB = r_wglGetProcAddress("glDeleteRenderbuffersEXT");
		if (g_useFbo && (!f_genFB || !f_rbStorage))
			return 0;
	} else
		r_wglMakeCurrent(g_shadowDC, g_shadowRC);
	if (!g_useFbo) {
		if (w != g_fbW || h != g_fbH) {
			SetWindowPos(g_shadowWnd, NULL, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
			g_fbW = w;
			g_fbH = h;
		}
		g_readBuffer(0x0405);   /* GL_BACK */
		return 1;
	}
	if (w != g_fbW || h != g_fbH) {   /* the framebuffer at the window's size, its depth as the window's */
		if (g_fbo) { f_delFB(1, &g_fbo); f_delRB(1, &g_rbColor); f_delRB(1, &g_rbDepth); }
		PIXELFORMATDESCRIPTOR pfd;
		DescribePixelFormat(g_gameDC, GetPixelFormat(g_gameDC), sizeof pfd, &pfd);
		u32 depth = pfd.cDepthBits <= 16 ? 0x81a5 : pfd.cStencilBits ? 0x88f0 : 0x81a6;   /* DEPTH_COMPONENT16 / DEPTH24_STENCIL8 / DEPTH_COMPONENT24 */
		f_genFB(1, &g_fbo);
		f_bindFB(0x8d40, g_fbo);
		f_genRB(1, &g_rbColor);
		f_bindRB(0x8d41, g_rbColor);
		f_rbStorage(0x8d41, 0x8058, w, h);   /* RGBA8 */
		f_fbRB(0x8d40, 0x8ce0, 0x8d41, g_rbColor);
		f_genRB(1, &g_rbDepth);
		f_bindRB(0x8d41, g_rbDepth);
		f_rbStorage(0x8d41, depth, w, h);
		f_fbRB(0x8d40, 0x8d00, 0x8d41, g_rbDepth);
		if (depth == 0x88f0)
			f_fbRB(0x8d40, 0x8d20, 0x8d41, g_rbDepth);
		g_fbW = w;
		g_fbH = h;
	}
	f_bindFB(0x8d40, g_fbo);
	return 1;
}

/* the stream replayed in the current (shadow) context */
static void replay(const u32 *p, const u32 *end)
{
	while (p < end) {
		u32 h = *p++, op = h & 0xffff, words = h >> 16;
		if (op < NPLAIN) {
			call_words(g_glrecReal[op], p, (int)words);
			p += words;
			continue;
		}
		switch (op) {
		case OP_COLOR4UBV: r_glColor4ubv(p); p += 1; break;
		case OP_FOGFV: r_glFogfv(p[0], (const float *)(p + 1)); p += 5; break;
		case OP_LOADMATRIX: r_glLoadMatrixf((const float *)p); p += 16; break;
		case OP_MULTMATRIX: r_glMultMatrixf((const float *)p); p += 16; break;
		case OP_TEXCOORD2FV: r_glTexCoord2fv((const float *)p); p += 2; break;
		case OP_VERTEX3FV: r_glVertex3fv((const float *)p); p += 3; break;
		case OP_VERTEX4FV: r_glVertex4fv((const float *)p); p += 4; break;
		case OP_PIXELSTORE: r_glPixelStorei(p[0], (int)p[1]); p += 2; break;
		case OP_TEXPARAMI: r_glTexParameteri(p[0], p[1], (int)p[2]); p += 3; break;
		case OP_DRAW: {
			u32 mode = p[0], count = p[1], itype = p[2], n = p[3];
			p += 4;
			const void *idx = p;
			p += ((size_t)count * type_size(itype) + 3) / 4;
			for (int a = 0; a < 3; a++) {
				if (!*p++)
					continue;
				int size = (int)p[0];
				u32 type = p[1];
				p += 2;
				const void *data = p;
				p += ((size_t)n * size * type_size(type) + 3) / 4;
				if (a == 0) r_glVertexPointer(size, type, 0, data);
				else if (a == 1) r_glColorPointer(size, type, 0, data);
				else r_glTexCoordPointer(size, type, 0, data);
			}
			r_glDrawElements(mode, (int)count, itype, idx);
			break;
		}
		case OP_TEXIMAGE: {
			u32 n = p[8];
			r_glTexImage2D(p[0], (int)p[1], (int)p[2], (int)p[3], (int)p[4], (int)p[5], p[6], p[7], n ? p + 9 : NULL);
			p += 9 + (n + 3) / 4;
			break;
		}
		case OP_MIPMAPS: {
			u32 n = p[6];
			r_gluBuild2DMipmaps(p[0], (int)p[1], (int)p[2], (int)p[3], p[4], p[5], n ? p + 7 : NULL);
			p += 7 + (n + 3) / 4;
			break;
		}
		default:
			g_errors++;
			return;
		}
	}
}

/* AXIS_GLREC_DUMP=<file> (with AXIS_GLREC): the stream written to a file instead of replayed - the first
   AXIS_GLREC_DUMP_FRAMES frames (600), each as its window size and its words - for a replayer elsewhere (the
   Godot branch). The file: "AXGLREC1", the plain calls' table (count, then each: words, name length, name), then
   per frame: width, height, the number of words, the words. The ops from 64 are as in replay() above */
static FILE *g_dump;
static unsigned g_dumpFrames = 600;
static void dump_header(void)
{
	fwrite("AXGLREC1", 1, 8, g_dump);
	u32 n = NPLAIN;
	fwrite(&n, 4, 1, g_dump);
	for (int i = 0; i < NPLAIN; i++) {
		u32 w = (u32)k_plain[i].words, l = (u32)strlen(k_plain[i].name);
		fwrite(&w, 4, 1, g_dump);
		fwrite(&l, 4, 1, g_dump);
		fwrite(k_plain[i].name, 1, l, g_dump);
	}
}

static BOOL S w_SwapBuffers(HDC dc)
{
	g_frames++;
	int check = g_frames % g_every == 0;
	RECT rc;
	HWND wnd = WindowFromDC(dc);
	GetClientRect(wnd, &rc);
	int w = rc.right, h = rc.bottom;
	if (g_dump) {
		if (g_frames <= g_dumpFrames) {
			u32 head[3] = { (u32)w, (u32)h, (u32)g_len };
			fwrite(head, 4, 3, g_dump);
			fwrite(g_buf, 4, g_len, g_dump);
			if (g_frames == g_dumpFrames) {
				fclose(g_dump);
				g_dump = NULL;
				g_recording = 0;   /* (done: the game runs on without the layer's work) */
			}
		}
		g_len = 0;
		if (check)
			report();
		return r_SwapBuffers(dc);
	}
	unsigned char *game = NULL, *mine = NULL;
	if (check && w > 0 && h > 0) {   /* the game's frame, from its back buffer */
		game = malloc((size_t)w * h * 4);
		int was;
		g_getIntegerv(0x0c02, &was);   /* GL_READ_BUFFER */
		g_readBuffer(0x0405);           /* GL_BACK */
		g_readPixels(0, 0, w, h, 0x1908, 0x1401, game);
		g_readBuffer((u32)was);
	}
	g_gameDC = dc;
	HGLRC rcGame = wglGetCurrentContext();
	if (w > 0 && h > 0 && shadow_make(w, h)) {
		g_recording = 0;
		replay(g_buf, g_buf + g_len);
		g_recording = 1;
		if (game) {
			mine = malloc((size_t)w * h * 4);
			g_readPixels(0, 0, w, h, 0x1908, 0x1401, mine);
		}
		r_wglMakeCurrent(dc, rcGame);
	} else
		g_errors++;
	g_len = 0;
	if (game && mine) {
		size_t diff = 0;
		for (size_t i = 0; i < (size_t)w * h; i++)
			if (memcmp(game + i * 4, mine + i * 4, 3))
				diff++;
		g_compared++;
		if (diff) {
			g_differ++;
			double share = (double)diff / ((double)w * h);
			if (share > g_worst) g_worst = share;
			if (g_saved < 3) {
				g_saved++;
				save_ppm("game", game, w, h);
				save_ppm("replay", mine, w, h);
			}
		} else
			g_same++;
	}
	free(game);
	free(mine);
	if (check)
		report();
	return r_SwapBuffers(dc);
}

/* a new game context: the replay starts again with it (the game uploads everything to a new context) */
static int S w_wglMakeCurrent(HDC dc, HGLRC rc)
{
	int r = r_wglMakeCurrent(dc, rc);
	if (rc && rc != g_gameRC) {
		g_gameRC = rc;
		g_len = 0;
		if (g_shadowRC) {
			wglDeleteContext(g_shadowRC);
			g_shadowRC = NULL;
			g_fbW = g_fbH = 0;
			g_fbo = 0;
		}
	}
	return r;
}

/* the layer put in front of the game's GL slots (slot(name): a slot's place). Returns the number wrapped */
int glrec_install(void **(*slot)(const char *name), const char *dir)
{
	strcpy(g_dir, dir);
	char v[16];
	g_useFbo = GetEnvironmentVariableA("AXIS_GLREC_FBO", NULL, 0) != 0;
	{
		char path[MAX_PATH];
		if (GetEnvironmentVariableA("AXIS_GLREC_DUMP", path, sizeof path) && (g_dump = fopen(path, "wb")))
			dump_header();
		if (GetEnvironmentVariableA("AXIS_GLREC_DUMP_FRAMES", v, sizeof v) && atoi(v) > 0)
			g_dumpFrames = (unsigned)atoi(v);
	}
	if (GetEnvironmentVariableA("AXIS_GLREC_EVERY", v, sizeof v) && atoi(v) > 0)
		g_every = (unsigned)atoi(v);
	HMODULE gl = LoadLibraryA("opengl32.dll");
	*(void **)&g_readPixels = (void *)GetProcAddress(gl, "glReadPixels");
	*(void **)&g_readBuffer = (void *)GetProcAddress(gl, "glReadBuffer");
	*(void **)&g_getIntegerv = (void *)GetProcAddress(gl, "glGetIntegerv");
	*(void **)&r_glTexParameteri = (void *)GetProcAddress(gl, "glTexParameteri");
	g_texParameteri = w_glTexParameteri;
	*(void **)&g_getTexParameteriv = (void *)GetProcAddress(gl, "glGetTexParameteriv");
	int n = 0;
	for (int i = 0; i < NPLAIN; i++) {
		void **p = slot(k_plain[i].name);
		if (!p) { g_errors++; continue; }
		g_glrecReal[i] = *p;
		*p = (void *)k_thunk[i];
		n++;
	}
#define WRAP(name) do { void **p = slot(#name); if (p) { *(void **)&r_##name = *p; *p = (void *)w_##name; n++; } else g_errors++; } while (0)
	WRAP(glColor4ubv); WRAP(glFogfv); WRAP(glLoadMatrixf); WRAP(glMultMatrixf); WRAP(glTexCoord2fv); WRAP(glVertex3fv);
	WRAP(glVertex4fv); WRAP(glPixelStorei); WRAP(glVertexPointer); WRAP(glColorPointer); WRAP(glTexCoordPointer);
	WRAP(glDrawElements); WRAP(glTexImage2D); WRAP(gluBuild2DMipmaps); WRAP(wglGetProcAddress); WRAP(wglMakeCurrent);
	WRAP(SwapBuffers);
	WRAP(glEnableClientState); WRAP(glDisableClientState);   /* (in front of their thunks: the arrays' state kept) */
#undef WRAP
	(void)g_logf;
	return n;
}
