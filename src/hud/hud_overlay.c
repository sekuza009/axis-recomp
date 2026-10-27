/* hud_overlay.c: small overlays of the in-match HUD. The HUD is laid out in 640 x 480 units and scaled to the
   screen. */
#include "../game.h"

/* x in 640-unit HUD space to screen pixels, as the original computes it: x as a float, divided by the units per
   pixel (640 / width) */
static int hud_toScreenX(int x)
{
	float fx = (float)x;
	return ftol(fx / ((long double)640.0f / gfx_getWidth()));
}
/* y in 480-unit HUD space to screen pixels */
static int hud_toScreenY(int y)
{
	float fy = (float)y;
	return ftol(fy / ((long double)480.0f / gfx_getHeight()));
}

/* 0x4950a0 (hud_4950a0): a filled rectangle given in HUD units, in the current colour. The corners are converted
   bottom right first, as the original does (each conversion asks for the screen size again). */
void (hud_4950a0)(int x0, int y0, int x1, int y1)
{
	int sy1 = hud_toScreenY(y1);
	int sx1 = hud_toScreenX(x1);
	int sy0 = hud_toScreenY(y0);
	int sx0 = hud_toScreenX(x0);
	gfx_fillRect(sx0, sy0, sx1, sy1);
}

/* 0x495510: the frames-per-second counter, top right: its icon and the rate with one decimal */
void THISCALL (hud_drawFps)(Scene *scene)
{
	char text[256];
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	replay_drawIcon(scene, 0x1d9, 8, 3);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	sprintf(text, "%4.1f", (double)scene->fps);
	text_drawSized(0x1f1, 8, text, 16);
}

/* 0x4953d0 (hud_4953d0): the chat line while typing: a half-transparent box and the line, with a "_" cursor
   during the first half of each blink */
void THISCALL (hud_4953d0)(Scene *scene)
{
	char text[256];
	if (scene->chatMode != 1 && scene->chatMode != 2)
		return;
	glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
	hud_4950a0(0x50, 0x158, 0x230, 0x188);
	text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
	if (scene->chatBlink >= 0.5f) {
		sprintf(text, "%s_", g_chatLine);
		text_drawSized(0x60, 0x168, text, 8);
	} else {
		text_drawSized(0x60, 0x168, g_chatLine, 8);
	}
}
