/* loading.c: the loading screen between the menus and a match: a progress bar under a text, faded in from black and
   out to black. */
#include "../game.h"
#include <string.h>

#define g_loadTimer ((void *)0xa0e948)                /* its own game-time timer */
#define g_loadProgress GAME_VAR(float, 0xa0ea88)
#define g_loadText ((char *)0xa0e988)
#define g_loadTexture GAME_VAR(int, 0xa0e980)         /* the backdrop's texture id */
#define g_loadFade GAME_VAR(float, 0xa0e984)          /* the fade's time, 0 .. 1 s */
#define ONE GAME_VAR(float, 0x4a9424)

/* one frame of a fade: the screen at its progress, under a black quad (alpha 1 - time fading in, time fading out),
   the fade's time advanced */
static void fade_frame(int in)
{
	loading_draw_bits(BITS(g_loadProgress));
	if (in)
		glColor4f(1.0f, 1.0f, 1.0f, fsub_m(fld_m(&ONE), &g_loadFade));
	else
		glColor4f_bits(0x3f800000, 0x3f800000, 0x3f800000, BITS(g_loadFade));
	int h = gfx_getHeight();
	gfx_fillRect(0, 0, gfx_getWidth(), h);
	g_loadFade = fadd_m(timer_getGameTime(g_loadTimer), &g_loadFade);
	gfx_swapBuffers();
}

/* 0x469730 (mode, unused, text): the loading screen. -1: the progress reset, the text set, the backdrop looked up,
   then a fade from black over one second of game time; -2: the progress advanced by the time since the last call,
   the text set, then a fade to black; any other mode: the progress advanced (the text set when 1) and one frame */
void (loading_drawCylinder)(int mode, int unused, const char *text)
{
	(void)unused;
	long double dt = timer_getGameTime(g_loadTimer);
	if (mode == -2) {
		g_loadProgress = fadd_m(dt, &g_loadProgress);
		strcpy(g_loadText, text);
		BITS(g_loadFade) = 0;
		do
			fade_frame(0);
		while (!(g_loadFade >= ONE));
		return;
	}
	if (mode == -1) {
		BITS(g_loadProgress) = 0;
		strcpy(g_loadText, text);
		g_loadTexture = tex_getIdByName(g_textures, (const char *)0x4c533c, 0, 0, 0, 0, 0, 0, 0);
		BITS(g_loadFade) = 0;
		do
			fade_frame(1);
		while (!(g_loadFade >= ONE));
		return;
	}
	g_loadProgress = fadd_m(dt, &g_loadProgress);
	if (mode == 1)
		strcpy(g_loadText, text);
	loading_draw_bits(BITS(g_loadProgress));
	gfx_swapBuffers();
}
