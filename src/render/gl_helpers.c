/* gl_helpers.c: small OpenGL helpers. */
#include "../game.h"

/* 0x41ef20 (FUN_0041ef20): turned by x degrees about x, then y about y, then z about z (floats as bits) */
void (FUN_0041ef20)(u32 x, u32 y, u32 z)
{
	glRotatef_bits(x, 0x3f800000u, 0, 0);
	glRotatef_bits(y, 0, 0x3f800000u, 0);
	glRotatef_bits(z, 0, 0, 0x3f800000u);
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
u32 (glWindow_4684c0)(void)
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
