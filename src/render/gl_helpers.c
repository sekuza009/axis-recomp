/* gl_helpers.c: small OpenGL helpers. */
#include "../game.h"

/* 0x41ef20 (gl_rotateXYZ): turned by x degrees about x, then y about y, then z about z (floats as bits) */
void (gl_rotateXYZ)(u32 x, u32 y, u32 z)
{
	glRotatef_bits(x, 0x3f800000u, 0, 0);
	glRotatef_bits(y, 0, 0x3f800000u, 0);
	glRotatef_bits(z, 0, 0, 0x3f800000u);
}

/* 0x4685f0: the in-match projection switch (the HUD's): the model view reset, then, unless mode is the one set
   already (0x4c4de8), the 3D projection (1: the view's angle, an aspect of width * scale / height, the near and far
   planes) or the HUD's 2D one (0: width * scale x height units). As the installed exe has it (hudfix.py: code in
   the .axnet section's tail, entered at 0x468671 and 0x4686af), the 3D projection takes the full screen and the 2D
   one the centred 16:9 box, unless the screen is at most 8 pixels wider; both make the menus' switch (g_projMode)
   set its viewport again next time */
void (gfx_setProjectionHud)(int mode, float scale)
{
	glLoadIdentity();
	if (mode == g_glCachedState)
		return;
	g_glCachedState = mode;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (g_glCachedState == 1) {
		gluPerspective(g_viewFov, (double)(fmul_m((long double)g_glWidth, &scale) / g_glHeight),
		               g_viewNear, g_viewFar);
		glViewport(0, 0, g_glWidth, g_glHeight);
		g_projMode = -1;
		glEnable(GL_DEPTH_TEST);
	} else if (g_glCachedState == 0) {
		gluOrtho2D(0.0, (double)fmul_m((long double)g_glWidth, &scale), 0.0, (double)g_glHeight);
		int h = g_glHeight, w = g_glWidth, x = 0;
		u32 box = ((u32)h << 4) / 9;
		if ((int)(box + 8) < w) {
			x = (w - (int)box) >> 1;
			w = (int)box;
		}
		glViewport(x, 0, w, h);
		g_projMode = -1;
		glDisable(GL_DEPTH_TEST);
	}
	glMatrixMode(GL_MODELVIEW);
}

/* 0x46bd60: the rectangle from (x0, y0) to (x1, y1) (inclusive, y down) filled in the current colour. As the installed
   exe has it (hudfix.py: its entry jumps to code in the .axnet section's tail), the whole screen (0, 0, width, height),
   a flash or fade, is filled over the full window, the viewport (the HUD's 16:9 box) put back after. Returns the eax
   the last GL call leaves */
static u32 fill_rect(int x0, int y0, int x1, int y1)
{
	glBegin(GL_QUADS);
	glVertex2i(x0, gfx_getHeight() - y0);
	glVertex2i(x1 + 1, gfx_getHeight() - y0);
	glVertex2i(x1 + 1, gfx_getHeight() - y1 - 1);
	glVertex2i(x0, gfx_getHeight() - y1 - 1);
	return IMPORT(0x4a9220, u32, void)();   /* glEnd */
}
u32 (gfx_fillRect)(int x0, int y0, int x1, int y1)
{
	if ((x0 | y0) != 0 || x1 != g_glWidth || y1 != g_glHeight)
		return fill_rect(x0, y0, x1, y1);
	float vp[4];
	glGetFloatv(0x0ba2, vp);   /* GL_VIEWPORT */
	glViewport(0, 0, g_glWidth, g_glHeight);
	fill_rect(x0, y0, x1, y1);
	return IMPORT(0x4a91d4, u32, int, int, int, int)((int)vp[0], (int)vp[1], (int)vp[2], (int)vp[3]);   /* glViewport */
}

/* 0x4685d0: the frame finished and shown (SwapBuffers' result) */
int (gfx_swapBuffers)(void)
{
	glFinish();
	return SwapBuffers(g_hdc);
}

/* 0x4684c0: the default GL state: nicest hints, textures modulated, alpha blending (src alpha, 1 - src alpha), the
   depth test (<=) on, texturing, smoothing, lighting, fog and face culling off, filled polygons with counter-clockwise
   fronts (back faces the ones to cull). The original also calls glEnable(0x1d01), GL_SMOOTH, which is not a
   capability; kept. Returns the last glDisable's eax */
static u32 default_gl_state(void)
{
	glHint(0xc50, 0x1102);                                      /* GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST */
	IMPORT(0x4a91c8, void, u32, u32, u32)(0x2300, 0x2200, 0x46040000);   /* glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE) */
	IMPORT(0x4a91ec, void, u32, u32)(0x302, 0x303);            /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) */
	glHint(0xc51, 0x1102);                                      /* points */
	glHint(0xc52, 0x1102);                                      /* lines */
	IMPORT(0x4a91cc, void, u32)(0x203);                         /* glDepthFunc(GL_LEQUAL) */
	glHint(0xc54, 0x1102);                                      /* fog */
	glEnable(0x1d01);
	glDisable(0xde1);                                           /* GL_TEXTURE_2D */
	glEnable(0xbe2);                                            /* GL_BLEND */
	glDisable(0xb10);                                           /* GL_POINT_SMOOTH */
	glDisable(0xb20);                                           /* GL_LINE_SMOOTH */
	glDisable(0xb41);                                           /* GL_POLYGON_SMOOTH */
	glEnable(0xb71);                                            /* GL_DEPTH_TEST */
	glDisable(0xb50);                                           /* GL_LIGHTING */
	glDisable(0x4000);                                          /* GL_LIGHT0 */
	glDisable(0xb60);                                           /* GL_FOG */
	IMPORT(0x4a91c4, void, u32, u32)(0x408, 0x1b02);           /* glPolygonMode(GL_FRONT_AND_BACK, GL_FILL) */
	IMPORT(0x4a91c0, void, u32)(0x901);                         /* glFrontFace(GL_CCW) */
	IMPORT(0x4a91d0, void, u32)(0x405);                         /* glCullFace(GL_BACK) */
	return IMPORT(0x4a922c, u32, u32)(0xb44);                   /* glDisable(GL_CULL_FACE) */
}
u32 (gfx_resetState)(void) { return default_gl_state(); }

/* 0x42f150: a new window's GL state: the defaults, then the projection (field of view 0x68038c, the aspect
   width / height kept in 0x4e1870, depth 1 .. 20000) and the window's size (0x42f0f0); 0x5ae9bc set. Returns
   0x42f0f0's eax */
u32 (gfx_initGLState)(int width, int height)
{
	default_gl_state();
	IMPORT(0x4a91fc, void, u32)(0x1701);   /* glMatrixMode(GL_PROJECTION) */
	g_viewAspect = f32((long double)width / (long double)height);
	((void (STDCALL *)(double, double, double, double))*(const u32 *)STR(0x4a9048, "j\300\n"))((double)fld_m((const float *)IMG(0x68038c)),
		(double)fld_m((const float *)IMG(0x4e1870)), 1.0, 20000.0);   /* gluPerspective */
	IMPORT(0x4a91fc, void, u32)(0x1700);   /* glMatrixMode(GL_MODELVIEW) */
	u32 r = GAME_FN(gfx_setup3DView, 0x42f0f0, u32, int, int)(width, height);
	g_projMode = 1;
	return r;
}
