/* setup_pages.c: the setup screen's pages drawn */
#include "../game.h"

/* a textured quad, (s0, t0) .. (s1, t1) of the bound texture on (x0, y0) .. (x1, y1) */
static void tex_quad(float s0, float t0, float s1, float t1, int x0, int y0, int x1, int y1)
{
	glBegin(GL_QUADS);
	glTexCoord2f(s0, t0);
	menu_vertex(x0, y0);
	glTexCoord2f(s1, t0);
	menu_vertex(x1, y0);
	glTexCoord2f(s1, t1);
	menu_vertex(x1, y1);
	glTexCoord2f(s0, t1);
	menu_vertex(x0, y1);
	glEnd();
}

/* 0x424810: the sound page (0x4ddad0 .. 0x4ddadc): the window, a cyan frame, the title 0x7533a4; the volume slider
   from the button texture (0x9db0a4): the two arrows, the track and the bar (the volume 0x4dde98 long); while
   0x4ddb98 runs down (by 0x4b071c, then -1 into 0x4dde90) the arrow pressed (0x4dde90: 0 / 1, or 2 / 3 a row lower)
   lit; the label 0x753424 and three switches (0x7534a4, 0x80 apart) with their on / off names (0x753624 + 0x80 x:
   the volume on, 0x4ddea0, 0x4ddea4), the one under the pointer (5 .. 7, by setup_420670) yellow with a shadow; two
   buttons (0x753724, lit from 8) and the border. The original leaves eax to callers that ignore it */
void (setup_424810)(void)
{
#define X0 GAME_VAR(int, 0x4ddad0)
#define Y0 GAME_VAR(int, 0x4ddad4)
#define X1 GAME_VAR(int, 0x4ddad8)
#define Y1 GAME_VAR(int, 0x4ddadc)
#define g_pressedClock GAME_VAR(float, 0x4ddb98)
#define g_pressed GAME_VAR(int, 0x4dde90)
	const u32 *bright = (const u32 *)0x4de048, *dim = (const u32 *)0x4ddae0;
	int hovered = GAME_CDECL(0x420670, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* setup_420670 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(X0 + 0x20, Y0 + 0x30, X1 - 0x20, Y1 - 0x20, 0);
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)0x7533a4);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_quad(0.0f, 0.25f, 0.25f, 0.375f, X0 + 0x50, Y0 + 0x50, X0 + 0x90, Y0 + 0x70);      /* the arrows */
	tex_quad(0.25f, 0.25f, 0.5f, 0.375f, X0 + 0x190, Y0 + 0x50, X0 + 0x1d0, Y0 + 0x70);
	tex_quad(0.0f, 0.0f, 1.0f, 0.125f, X0 + 0x90, Y0 + 0x50, X0 + 0x190, Y0 + 0x70);       /* the track */
	long double volume = (long double)GAME_VAR(int, 0x4dde98);
	float s = f32(fmul_m(volume, (const float *)0x4a9504));
	int x = X0 - ftol(fmul_m(volume, (const float *)0x4a9500)) + 0x90;
	tex_quad(0.0f, 0.125f, s, 0.25f, X0 + 0x90, Y0 + 0x50, x, Y0 + 0x70);                  /* the bar */
	const float *zero = (const float *)0x4a93e8;
	if (g_pressedClock > *zero) {
		switch (g_pressed) {
		case 0: tex_quad(0.5f, 0.25f, 0.75f, 0.375f, X0 + 0x50, Y0 + 0x50, X0 + 0x90, Y0 + 0x70); break;
		case 1: tex_quad(0.75f, 0.25f, 1.0f, 0.375f, X0 + 0x190, Y0 + 0x50, X0 + 0x1d0, Y0 + 0x70); break;
		case 2: tex_quad(0.5f, 0.25f, 0.75f, 0.375f, X0 + 0x50, Y0 + 0x8c, X0 + 0x90, Y0 + 0xac); break;
		case 3: tex_quad(0.75f, 0.25f, 1.0f, 0.375f, X0 + 0x190, Y0 + 0x8c, X0 + 0x1d0, Y0 + 0xac); break;
		}
		long double left = fsub_m(fld_m(&g_pressedClock), (const float *)0x4b071c);
		g_pressedClock = f32(left);
		if (!(left >= *zero)) {
			g_pressedClock = 0;
			g_pressed = -1;
		}
	}
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x50, Y0 + 0x3c, (const char *)0x753424);
	for (int k = 0; k < 3; k++)
		text_draw8(X0 + 0x8c, Y0 + 0x9c + k * 0x28, (const char *)(0x7534a4 + k * 0x80));
	int on = GAME_VAR(int, 0x4dde9c) > 0;
	for (int k = 0; k < 3; k++) {
		int value = k == 0 ? on : GAME_VAR(int, k == 1 ? 0x4ddea0 : 0x4ddea4);
		const char *name = (const char *)(0x753624 + value * 0x80);
		int y = Y0 + 0x9c + k * 0x28;
		if (hovered == 5 + k) {
			set_colour_bits((Colour *)0x76d438, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01: the shadow */
			text_draw8(X0 + 0x12d, y + 2, name);
			set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);            /* 1, 0.8, 0, 1 */
			text_draw8(X0 + 0x12c, y + 1, name);
		} else {
			set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
			text_draw8(X0 + 0x12c, y, name);
		}
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		int lit = hovered == k + 8;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + k * 0x8c;
		menu_drawTexQuad_4282f0(bx + 0x90, Y0 + 0x113, bx + 0x108, Y0 + 0x133, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(bx + 0x90, Y0 + 0x11b, bx + 0x108, (const char *)(0x753724 + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
#undef g_pressed
#undef g_pressedClock
#undef X0
#undef Y0
#undef X1
#undef Y1
}
