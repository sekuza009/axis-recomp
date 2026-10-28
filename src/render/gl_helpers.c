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
