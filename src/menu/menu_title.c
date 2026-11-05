/* menu_title.c: the title screen's emblem: a picture cut into four screen quarters (with a second, pulsing layer
   over it) that spread apart as the title goes on, and the logo fading in over them. */
#include "../game.h"

static void bind(int texture)
{
	tex_bind(g_textures->banks[texture / 512], texture % 512);
}

/* a whole texture on the rectangle (x0, y0) - (x1, y1) in menu units */
static void picture(int texture, int x0, int y0, int x1, int y1)
{
	bind(texture);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	menu_vertex(x0, y0);
	glTexCoord2d(1.0, 0.0);
	menu_vertex(x1, y0);
	glTexCoord2d(1.0, 1.0);
	menu_vertex(x1, y1);
	glTexCoord2d(0.0, 1.0);
	menu_vertex(x0, y1);
	glEnd();
}

/* the four quarters of a picture (textures[0..3]: top left, top right, bottom left, bottom right), each pushed
   out from the centre by spread; overlap widens each quarter by that much towards the centre */
static void quarters(const int textures[4], int spread, int overlap)
{
	int d = spread, o = overlap;
	picture(textures[0], -d, -d, 320 + o - d, 240 + o - d);
	picture(textures[1], d + 320 - o, -d, d + 640, 240 + o - d);
	picture(textures[2], -d, d + 240 - o, 320 + o - d, d + 480);
	picture(textures[3], d + 320 - o, d + 240 - o, d + 640, d + 480);
}

/* 0x429170: drawn every frame of the front end while the title is up (the patch DLL wraps the call to it).
   g_titleShown: the title is closing, and both layers fade out over 50 frames as they spread (g_titleSpread by
   g_titleFrames); otherwise the base layer stands at 0.6 and the top layer pulses between 0.2 and 0.9. The logo
   fades in over ten time units (g_frameTime, taken as 1 when a frame took more than 3) and is drawn until opaque. */
void (menu_titleEmblemTransition)(void)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	if (g_frameTime > 3.0f)
		g_frameTime = 1.0f;
	glEnable(GL_TEXTURE_2D);

	glColor4f(1.0f, 1.0f, 1.0f, g_titleShown ? (float)(1.0f - (long double)g_titleFrames * 0.02f) : 0.6f);
	quarters(&g_titleTextures[0], g_titleSpread[g_titleFrames], 0);

	float alpha;
	if (g_titleShown) {
		alpha = (float)(1.0f - (long double)g_titleFrames * 0.02f);
	} else {
		if (g_emblemAlpha > 1.0f)
			g_emblemAlpha = 1.0f;
		else if (!(g_emblemAlpha >= 0.0f))                  /* NaN too */
			g_emblemAlpha = 0.0f;
		alpha = g_emblemAlpha;
	}
	glColor4f(1.0f, 1.0f, 1.0f, alpha);
	quarters(&g_titleTextures[4], g_titleSpread[g_titleFrames], 1);

	/* the pulse: the sum before rounding is what the limits are tested against */
	long double a = (long double)g_emblemPulse * g_frameTime + g_emblemAlpha;
	g_emblemAlpha = f32(a);
	if (a > 0.9) {
		g_emblemAlpha = 0.9f;
		g_emblemPulse = -0.018f;
	}
	if (!(g_emblemAlpha >= 0.2)) {
		g_emblemPulse = 0.018f;
		g_emblemAlpha = 0.2f;
	}

	long double f = (long double)g_frameTime * 0.1f + g_logoFade;
	g_logoFade = f32(f);
	if (f >= 1.0)
		g_logoFade = 1.0f;
	if (g_logoFade >= 0.2) {
		/* a second fade running twice as fast from 0.2: g_unusedLogoFade, never read */
		long double late = (long double)g_logoFade + g_logoFade - 0.2f;
		g_unusedLogoFade = f32(late);
		if (late > 1.0f)
			g_unusedLogoFade = 1.0f;
	}
	if (!(g_logoFade >= 1.0f)) {
		glColor4f(1.0f, 1.0f, 1.0f, (float)(1.0f - (long double)g_logoFade));
		picture(g_logoTexture, 0xa0, 0x3c, 0x1e0, 0x13c);
	}
	glDisable(GL_TEXTURE_2D);
}
