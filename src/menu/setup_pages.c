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

/* ---- the tunnel behind the setup pages ---- */
#define glVertex3f(x, y, z) IMPORT(0x4a9210, void, float, float, float)(x, y, z)
#define g_tunnelAlpha GAME_VAR(float, 0x4de038)
#define g_tunnelPulse GAME_VAR(float, 0x9db978)       /* bounces 0 .. 100 */
#define g_tunnelPulseStep GAME_VAR(u32, 0x4df010)
#define g_scroll GAME_VAR(float, 0x4e14fc)      /* runs 0 .. 200 */

/* a wall of scrolling stripes at x = -29.9 (or 29.9 on the right), h either side of the floor, two quads either
   side of the moving seam z = 40 - 0.4 scroll */
static void stripes(int right, float h)
{
#define SEAM f32(fsubr_m(fmul_m(fld_m(&g_scroll), (const float *)0x4a9408), (const float *)0x4a9414))
#define S_LEFT f32(fsubr_m(fmul_m(fld_m(&g_scroll), (const float *)0x4a9404), (const float *)0x4a9424))   /* 1 - 0.005 scroll */
#define S_RIGHT f32(fmul_m(fld_m(&g_scroll), (const float *)0x4a9404))                                    /* 0.005 scroll */
	if (!right) {
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-29.9f, h, SEAM);
		glTexCoord2f(S_LEFT, 0.0f);
		glVertex3f(-29.9f, h, -40.0f);
		glTexCoord2f(S_LEFT, 0.5f);
		glVertex3f(-29.9f, -h, -40.0f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(-29.9f, -h, SEAM);
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(S_LEFT, 0.0f);
		glVertex3f(-29.9f, h, 40.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-29.9f, h, SEAM);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(-29.9f, -h, SEAM);
		glTexCoord2f(S_LEFT, 0.5f);
		glVertex3f(-29.9f, -h, 40.0f);
		glEnd();
	} else {
		glBegin(GL_QUADS);
		glTexCoord2f(S_RIGHT, 0.0f);
		glVertex3f(29.9f, h, -40.0f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(29.9f, h, SEAM);
		glTexCoord2f(1.0f, 0.5f);
		glVertex3f(29.9f, -h, SEAM);
		glTexCoord2f(S_RIGHT, 0.5f);
		glVertex3f(29.9f, -h, -40.0f);
		glEnd();
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(29.9f, h, SEAM);
		glTexCoord2f(S_RIGHT, 0.0f);
		glVertex3f(29.9f, h, 40.0f);
		glTexCoord2f(S_RIGHT, 0.5f);
		glVertex3f(29.9f, -h, 40.0f);
		glTexCoord2f(0.0f, 0.5f);
		glVertex3f(29.9f, -h, SEAM);
		glEnd();
	}
#undef SEAM
#undef S_LEFT
#undef S_RIGHT
}

/* the panels' pulse bounced between 0 and 100 (by 0x4df010 a frame; turn_only: only turned round, not clamped there)
   and the stripes scrolled on (0x4deda8 a frame, back to 0 at 200) */
static void tunnel_advance(int turn_only)
{
	const float *frame = (const float *)0x4b071c;
	long double pulse = fadd_m(fmul_m(fld_m(frame), (const float *)&g_tunnelPulseStep), &g_tunnelPulse);
	g_tunnelPulse = f32(pulse);
	if (turn_only) {
		if (!(pulse > *(const float *)0x4a93e8))
			g_tunnelPulseStep = 0x3f800000;
		if (pulse >= *(const float *)0x4a93f4)
			g_tunnelPulseStep = 0xbf800000;
	} else if (!(pulse > *(const float *)0x4a93e8)) {
		g_tunnelPulse = 0;
		g_tunnelPulseStep = 0x3f800000;   /* 1 */
	} else if (g_tunnelPulse >= *(const float *)0x4a93f4) {
		g_tunnelPulse = 100.0f;
		g_tunnelPulseStep = 0xbf800000;   /* -1 */
	}
	long double scroll = fadd_m(fmul_m(fld_m((const float *)0x4deda8), frame), &g_scroll);
	g_scroll = f32(scroll);
	if (scroll >= *(const float *)0x4a93f0)
		g_scroll = 0;
}

/* 0x423e50: the tunnel behind the setup pages (3D projection): its alpha (0x4de038) eases to 0.3 (mode 0x4ddcec 1)
   or 0.5 (mode 0); then layers of four walls (each under the menu camera, pushed back by 0x4ddd90 and turned by
   -35 / 35, the far two the other way): layer 0 the panels (texture 0x4e0cd0, dimmed as the pulse rises), layer 1
   the scrolling stripes (the same texture, in the original's colour 1, 1, 10, 0.4), layer 2 nothing, layer 3 a
   strip of 0x5b1978 a tenth further out, brighter by 0.2. After, the pulse bounces between 0 and 100 (by 0x4df010)
   and the stripes scroll on (0x4deda8 a frame, back to 0 at 200). The original leaves eax to callers that ignore
   it */
void (setup_423e50)(void)
{
	const float *frame = (const float *)0x4b071c;
	gfx_setProjection2D3D(1);
	glEnable(GL_TEXTURE_2D);
	if (GAME_VAR(int, 0x4ddcec) == 1)
		g_tunnelAlpha = f32(fsubr_m(fmul_m(fmul_m(fsub_m(fld_m(&g_tunnelAlpha), (const float *)0x4a94fc), frame),
		                                   (const float *)0x4a93ec), &g_tunnelAlpha));
	else if (GAME_VAR(int, 0x4ddcec) == 0)
		g_tunnelAlpha = f32(fadd_m(fmul_m(fmul_m(fsub_m(fld_m((const float *)0x4a942c), &g_tunnelAlpha), frame),
		                                  (const float *)0x4a93ec), &g_tunnelAlpha));
	glColor4f(1.0f, 1.0f, 1.0f, g_tunnelAlpha);
	for (int layer = 0; layer < 4; layer++) {
		/* the strip of the texture: s from s_near (+ ds) to s_far, t from t0 / t1 on by the wall's parity */
		float s0 = 0, ds = 0.5f, t0 = 0, t1 = 0.25f, s_far = 0.5f;
		if (layer == 3)
			s0 = 0.5f, ds = 0, t0 = 0.5f, t1 = 0.75f, s_far = 1.0f;
		int texture;
		if (layer == 0) {
			glColor4f(1.0f, 1.0f, 1.0f, f32(fsubr_m(fmul_m(fld_m(&g_tunnelPulse), (const float *)0x4a9430), &g_tunnelAlpha)));
			texture = GAME_VAR(int, 0x4e0cd0);
		} else if (layer == 1) {
			glColor4f(1.0f, 1.0f, 10.0f, 0.4f);
			texture = GAME_VAR(int, 0x4e0cd0);
		} else if (layer == 3) {
			glColor4f(1.0f, 1.0f, 1.0f, f32(fadd_m(fld_m(&g_tunnelAlpha), (const float *)0x4a94f8)));
			texture = GAME_VAR(int, 0x5b1984 - layer * 4);
		} else
			continue;
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		for (int wall = 0; wall < 4; wall++) {
			int parity = wall % 2, far = wall >= 2;
			gfx_setMenuCamera();
			glTranslatef_bits(0, 0, GAME_VAR(u32, 0x4ddd90));
			float turn = ((const float *)0x4b04c4)[parity];
			if (far)
				turn = -turn;
			FUN_0041ef20(0, 0, BITS(turn));
			if (layer == 1) {
				stripes(far, 12.0f);
				continue;
			}
			float x = f32(fmul_m(fld_m(&s0), (const float *)0x4a9418));    /* 10 s0 */
			float y = f32(fmul_m(fld_m(&s0), (const float *)0x4a9410));    /* 12 s0 */
			float top = f32(fsub_m(fld_m((const float *)0x4a9410), &y));   /* 12 - y */
			float bottom = f32(fsub_m(fld_m(&y), (const float *)0x4a9410));
			glBegin(GL_QUADS);
			if (layer == 0 && !far) {
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9414), &x)), z1 = f32(fsub_m(fld_m(&x), (const float *)0x4a9414));
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-30.0f, top, z0);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(-30.0f, top, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z0);
			} else if (layer == 0) {
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9400), &x)), z1 = f32(fadd_m(fld_m(&x), (const float *)0x4a9414));
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(30.0f, top, z0);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(30.0f, top, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(30.0f, bottom, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(30.0f, bottom, z0);
			} else if (!far) {
				float fp = (float)parity;
				float ta = f32(fmul_m((long double)parity, (const float *)0x4a941c));
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9414), &x)), z1 = f32(fsub_m(fld_m(&x), (const float *)0x4a9414));
				float wx = f32(fsub_m(fmul_m((long double)layer, (const float *)0x4a93ec), (const float *)0x4a940c));
				float tb = f32(fmul_m(fadd_m(fld_m(&fp), (const float *)0x4a9424), (const float *)0x4a941c));
				glTexCoord2f(0.0f, ta);
				glVertex3f(wx, top, z0);
				glTexCoord2f(s_far, ta);
				glVertex3f(wx, top, z1);
				glTexCoord2f(s_far, tb);
				glVertex3f(wx, bottom, z1);
				glTexCoord2f(0.0f, tb);
				glVertex3f(wx, bottom, z0);
			} else {
				long double pk = fmul_m((long double)parity, (const float *)0x4a941c);
				float ta = f32(pk);
				float u0 = f32(fadd_m(pk, &t0));
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9400), &x)), z1 = f32(fadd_m(fld_m(&x), (const float *)0x4a9414));
				float wx = f32(fsubr_m(fmul_m((long double)layer, (const float *)0x4a93ec), (const float *)0x4a940c));
				float s1 = f32(fadd_m(fld_m(&s_far), &ds));
				float u1 = f32(fadd_m(fld_m(&ta), &t1));
				glTexCoord2f(ds, u0);
				glVertex3f(wx, top, z0);
				glTexCoord2f(s1, u0);
				glVertex3f(wx, top, z1);
				glTexCoord2f(s1, u1);
				glVertex3f(wx, bottom, z1);
				glTexCoord2f(ds, u1);
				glVertex3f(wx, bottom, z0);
			}
			glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);
	tunnel_advance(0);
}
/* the menus' tunnel (mission select, skirmish, ARM CENTER): four layers of six walls (each under the menu camera,
   pushed back 550 and turned by -40 / 0 / 40, the far three the other way): layer 0 the panels (texture 0x4e0cd0,
   10 high, dimmed from 0.5 as the pulse rises), layer 1 the stripes (the same texture, in the colour 1, 1, 10,
   0.4), layer 2 nothing (its texture 0x76d47c bound, the walls' turns still made), layer 3 a strip of 0x76d478 a
   tenth further out (alpha 0.7); then the hovered panel's glow (0x680398: 0x680ccc bouncing between 2 and 38 by
   0x4df454; clamped there when clamp is set) and the pulse and scroll stepped on. The deep ones (deep): the panels
   purple, the stripes red, layer 2 drawn (fully transparent) */
typedef struct {
	u32 depth;             /* how far the walls are pushed back (float bits) */
	u32 textures;          /* layer 2's and 3's textures from here, 4 down a layer */
	int deep;              /* purple panels, red stripes */
	int layer2;            /* layer 2 drawn (fully transparent) */
	int clamp;
	int turn_only;         /* the pulse only turned round at its ends */
	int walls;             /* 6: three places a side (turned -40 / 0 / 40), 4: two (-35 / 35) */
	const float *height;   /* the panels' half height (10 at 0x4a9418, 12 at 0x4a9410) */
	const float *step;     /* layer 3's strip a place down the texture (0.15625 at 0x4a9478, 0.25 at 0x4a941c) */
	float t0, t1;          /* layer 3's strip's top on the far walls, and its height there */
} Tunnel;

/* the hovered menu panel: on, the wall whose layer 2 panel glows (-1: none), in the colour glow (r, g, b; its alpha
   falling as the glow, 0x680ccc, rises); with layer3, layer 3's panels at 0.6 and the hovered one fading from 1;
   white_stripes: the stripes plain (alpha 0.4); keep_texture: texturing left on (the caller turns it off) */
typedef struct { int on; const float *glow; int layer3, white_stripes, keep_texture; } Highlight;

static void menu_tunnel(const Tunnel *t, const Highlight *h)
{
	int hovered = h->on;
	int deep = t->deep, clamp = t->clamp, places = t->walls / 2;
	static const float turns3[3] = { -40.0f, 0.0f, 40.0f }, turns2[2] = { -35.0f, 35.0f };
	const float *turns = places == 3 ? turns3 : turns2;
	gfx_setProjection2D3D(1);
	glEnable(GL_TEXTURE_2D);
	for (int layer = 0; layer < 4; layer++) {
		/* layer 3's texture strip (s from s0 .. s0 + ds to s_far; t from t0 / t1 on by the wall's place) */
		float s0 = 0, ds = 0.5f, t0 = 0, t1 = 0.25f, s_far = 0.5f;
		if (layer > 1)
			s0 = 0.5f, ds = 0, t0 = t->t0, t1 = t->t1, s_far = 1.0f;
		int texture = layer < 2 ? GAME_VAR(int, 0x4e0cd0) : GAME_VAR(int, t->textures - layer * 4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		for (int wall = 0; wall < t->walls; wall++) {
			int place = wall % places, far = wall >= places;
			gfx_setMenuCamera();
			glTranslatef_bits(0, 0, t->depth);
			float turn = turns[place];
			if (far)
				turn = -turn;
			FUN_0041ef20(0, 0, BITS(turn));
			if (layer == 0) {
				float a = f32(fsubr_m(fmul_m(fld_m(&g_tunnelPulse), (const float *)0x4a9430), (const float *)0x4a942c));
				if (deep)
					glColor4f(0.7f, 0.0f, 0.7f, a);
				else
					glColor4f(1.0f, 1.0f, 1.0f, a);
			} else if (layer == 1) {
				if (deep)
					glColor4f(1.0f, 0.1f, 0.1f, 0.7f);
				else if (h->white_stripes)
					glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
				else
					glColor4f(1.0f, 1.0f, 10.0f, 0.4f);
				stripes(far, *t->height);
				continue;
			} else if (layer == 2) {
				if (!t->layer2)
					continue;
				if (wall == hovered)
					glColor4f(h->glow[0], h->glow[1], h->glow[2], f32(fsubr_m(fmul_m(fld_m(&GAME_VAR(float, 0x680ccc)), (const float *)0x4a9428), (const float *)0x4a9424)));
				else
					glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
			} else if (!h->layer3)
				glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
			else if (wall == hovered)
				glColor4f(1.0f, 1.0f, 1.0f, f32(fsubr_m(fmul_m(fld_m(&GAME_VAR(float, 0x680ccc)), (const float *)0x4a9420), (const float *)0x4a9424)));
			else
				glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
			float x = f32(fmul_m(fld_m(&s0), (const float *)0x4a9418));   /* 10 s0 */
			float y = f32(fmul_m(fld_m(&s0), t->height));
			float top = f32(fsub_m(fld_m(t->height), &y));
			float bottom = f32(fsub_m(fld_m(&y), t->height));
			glBegin(GL_QUADS);
			if (layer == 0 && !far) {
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9414), &x)), z1 = f32(fsub_m(fld_m(&x), (const float *)0x4a9414));
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-30.0f, top, z0);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(-30.0f, top, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z0);
			} else if (layer == 0) {
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9400), &x)), z1 = f32(fadd_m(fld_m(&x), (const float *)0x4a9414));
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(30.0f, top, z0);
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(30.0f, top, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(30.0f, bottom, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(30.0f, bottom, z0);
			} else if (!far) {
				float fp = (float)place;
				float ta = f32(fmul_m(fld_m(&fp), t->step));   /* 0.15625 a place */
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9414), &x)), z1 = f32(fsub_m(fld_m(&x), (const float *)0x4a9414));
				float wx = f32(fsub_m(fmul_m((long double)layer, (const float *)0x4a93ec), (const float *)0x4a940c));
				float tb = f32(fmul_m(fadd_m(fld_m(&fp), (const float *)0x4a9424), t->step));
				glTexCoord2f(0.0f, ta);
				glVertex3f(wx, top, z0);
				glTexCoord2f(s_far, ta);
				glVertex3f(wx, top, z1);
				glTexCoord2f(s_far, tb);
				glVertex3f(wx, bottom, z1);
				glTexCoord2f(0.0f, tb);
				glVertex3f(wx, bottom, z0);
			} else {
				long double pk = fmul_m((long double)place, t->step);
				float ta = f32(pk);
				float u0 = f32(fadd_m(pk, &t0));
				float z0 = f32(fsub_m(fld_m((const float *)0x4a9400), &x)), z1 = f32(fadd_m(fld_m(&x), (const float *)0x4a9414));
				float wx = f32(fsubr_m(fmul_m((long double)layer, (const float *)0x4a93ec), (const float *)0x4a940c));
				float s1 = f32(fadd_m(fld_m(&s_far), &ds));
				float u1 = f32(fadd_m(fld_m(&ta), &t1));
				glTexCoord2f(ds, u0);
				glVertex3f(wx, top, z0);
				glTexCoord2f(s1, u0);
				glVertex3f(wx, top, z1);
				glTexCoord2f(s1, u1);
				glVertex3f(wx, bottom, z1);
				glTexCoord2f(ds, u1);
				glVertex3f(wx, bottom, z0);
			}
			glEnd();
		}
	}
	if (!h->keep_texture)
		glDisable(GL_TEXTURE_2D);
	if (GAME_VAR(int, 0x680398)) {
		long double glow = fadd_m(fmul_m(fld_m((const float *)0x4b071c), &GAME_VAR(float, 0x4df454)), &GAME_VAR(float, 0x680ccc));
		GAME_VAR(float, 0x680ccc) = f32(glow);
		if (!clamp) {
			if (!(glow > *(const float *)0x4a93fc))
				GAME_VAR(u32, 0x4df454) = 0x3f800000;   /* 1 */
			if (glow >= *(const float *)0x4a93f8)
				GAME_VAR(u32, 0x4df454) = 0xbf800000;   /* -1 */
		} else if (!(glow > *(const float *)0x4a93fc)) {
			GAME_VAR(u32, 0x680ccc) = 0x40000000;   /* 2 */
			GAME_VAR(u32, 0x4df454) = 0x3f800000;
		} else if (GAME_VAR(float, 0x680ccc) >= *(const float *)0x4a93f8) {
			GAME_VAR(u32, 0x680ccc) = 0x42180000;   /* 38 */
			GAME_VAR(u32, 0x4df454) = 0xbf800000;
		}
	}
	tunnel_advance(t->turn_only);
}

/* 0x448140: the mission-select screen's tunnel; 0x4445a0 / 0x411110: the skirmish and ARM CENTER screens' (the glow
   clamped); 0x411ab0: the ARM CENTER's deep one (1650 back, its pulse only turned round); 0x4388e0: the game room's
   (as deep as 0x9dd698). The originals leave eax to callers that ignore it */
static const Highlight none = { -1, NULL, 0, 0, 0 };
static const float white[3] = { 1.0f, 1.0f, 1.0f };
#define SIX_WALLS 6, (const float *)0x4a9418, (const float *)0x4a9478, 0.46875f, 0.625f
#define FOUR_WALLS 4, (const float *)0x4a9410, (const float *)0x4a941c, 0.5f, 0.75f
void (missionsel_448140)(void) { static const Tunnel t = { 0xc4098000, 0x76d484, 0, 0, 0, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (skirmish_4445a0)(void) { static const Tunnel t = { 0xc4098000, 0x76d484, 0, 0, 1, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (armc_411110)(void) { static const Tunnel t = { 0xc4098000, 0x76d484, 0, 0, 1, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (armc_411ab0)(void) { static const Tunnel t = { 0xc4ce4000, 0x4df910, 1, 1, 0, 1, SIX_WALLS }; menu_tunnel(&t, &none); }
void (room_4388e0)(void)
{
	static const float glow[3] = { 0.5f, 0.1f, 1.0f };   /* (no wall glows: the original compares with -1) */
	static const Highlight h = { -1, glow, 0, 0, 0 };
	Tunnel t = { GAME_VAR(u32, 0x9dd698), 0x4df910, 1, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
}
/* 0x4091b0: the arena lobby's (as deep as 0x4dba68; four walls) */
void (arena_4091b0)(void)
{
	static const Highlight h = { -1, white, 0, 0, 0 };
	Tunnel t = { GAME_VAR(u32, 0x4dba68), 0x4df04c, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
}

/* a menu panel's caption (0x80 apart from captions) in white along the bottom */
static void caption(u32 captions, int on)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(0, 0x1bc, 0x280, (const char *)(captions + on * 0x80));
}

/* the menu panel under the pointer: the first of count outlines (FUN_0041eea0's, 0x2c bytes apart from outlines)
   holding it, none (-1) while locked; 0x680398 tells whether there is one, and a new one restarts the glow (0x907b24
   the last, 0x680ccc 40, 0x4df454 -1) */
static int hovered_panel(u32 outlines, int count, int locked)
{
	int on = -1;
	for (int k = 0; k < count && !locked; k++)
		if (point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), *(const Outline *)(outlines + k * 0x2c)) == 1) {
			on = k;
			break;
		}
	GAME_VAR(int, 0x680398) = on != -1;
	if (on != -1 && GAME_VAR(int, 0x907b24) != on) {
		GAME_VAR(int, 0x907b24) = on;
		GAME_VAR(u32, 0x680ccc) = 0x42200000;   /* 40 */
		GAME_VAR(u32, 0x4df454) = 0xbf800000;   /* -1 */
	}
	return on;
}

/* 0x437e00: the game room's menu: the panel under the pointer (six, 0x9daf88; none while 0x9dd7d8), the room's
   tunnel with that panel glowing, and in mode 2 (0x9dce48) its caption (0x750ba4, 0x80 apart) at the bottom. The
   original leaves eax to callers that ignore it */
void (room_437e00)(void)
{
	static const float glow[3] = { 1.0f, 0.1f, 1.0f };
	Highlight h = { hovered_panel(0x9daf88, 6, GAME_VAR(int, 0x9dd7d8)), glow, 0, 0, 0 };
	Tunnel t = { GAME_VAR(u32, 0x9dd698), 0x4df910, 1, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && GAME_VAR(int, 0x9dce48) == 2)
		caption(0x750ba4, h.on);
}

/* 0x408680: the arena lobby's top menu: the panel under the pointer (four, 0x5b1cf8; none while 0x4db85c), the
   arena tunnel (as deep as 0x4dba68) with that panel lit, and in mode 2 (0x4dbb3c) its caption (0x750924) unless
   0x680370. The original leaves eax to callers that ignore it */
void (lobbyTop_drawTitle)(void)
{
	Highlight h = { hovered_panel(0x5b1cf8, 4, GAME_VAR(int, 0x4db85c)), white, 1, 0, 0 };
	Tunnel t = { GAME_VAR(u32, 0x4dba68), 0x4df04c, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && GAME_VAR(int, 0x4dbb3c) == 2 && !GAME_VAR(int, 0x680370))
		caption(0x750924, h.on);
}

/* 0x423330: the setup screen's menu: the same over the setup tunnel's textures (0x5b197c / 0x5b1978, as deep as
   0x4ddd90): four panels (0x4df918; none while 0x4dda60), the caption (0x7506a4) in mode 2 (0x4ddcec). The original
   leaves eax to callers that ignore it */
void (setup_423330)(void)
{
	Highlight h = { hovered_panel(0x4df918, 4, GAME_VAR(int, 0x4dda60)), white, 1, 0, 0 };
	Tunnel t = { GAME_VAR(u32, 0x4ddd90), 0x5b1984, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && GAME_VAR(int, 0x4ddcec) == 2 && !GAME_VAR(int, 0x680370))
		caption(0x7506a4, h.on);
}
/* 0x442050: the main menu: the panel under the pointer (six, 0x4deb80; none while the tunnel flies in, 0x9eeaa8, or
   after one is picked, 0x9eeab4: then the idle clock 0x9dda80 and the hint's fade restart); with none the idle
   clock runs on. The tunnel flies in (0x9eea90 from deep to -550, faster the deeper; 0x9eeab0 counts the frames)
   and is drawn with the panel lit (the stripes plain); then the panel's caption (0x7501a4), or once idle for 120
   the hint 0x4b2a98 fading in and out (0x9eea8c by 0x9dd948), unless 0x680370. The original leaves eax to callers
   that ignore it */
void (menu_mainMenu)(void)
{
#define g_depth GAME_VAR(float, 0x9eea90)
#define g_idle GAME_VAR(float, 0x9dda80)
#define g_hint GAME_VAR(float, 0x9eea8c)
#define g_hintStep GAME_VAR(u32, 0x9dd948)
	const float *frame = (const float *)0x4b071c;
	int on = -1;
	for (int k = 0; k < 6 && !GAME_VAR(int, 0x9eeaa8); k++)
		if (point_in_outline(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c), *(const Outline *)(0x4deb80 + k * 0x2c)) == 1) {
			on = k;
			break;
		}
	if (on == -1) {
		g_idle = f32(fadd_m(fld_m(frame), &g_idle));
		GAME_VAR(int, 0x680398) = 0;
	} else {
		GAME_VAR(int, 0x680398) = !GAME_VAR(int, 0x9eeab4);
		g_idle = 0;
		g_hint = 0;
		g_hintStep = 0x3d4ccccd;   /* 0.05 */
		if (GAME_VAR(int, 0x9eeab4))
			on = -1;
		else if (GAME_VAR(int, 0x907b24) != on) {
			GAME_VAR(int, 0x907b24) = on;
			GAME_VAR(u32, 0x680ccc) = 0x42200000;   /* 40 */
			GAME_VAR(u32, 0x4df454) = 0xbf800000;   /* -1 */
		}
	}
	if (GAME_VAR(int, 0x9eeaa8)) {   /* (no calls: before the tunnel's projection and texturing as in the original) */
		long double step = fmul_m(fmul_m(fadd_m(fld_m(&g_depth), (const float *)0x4a9498), frame), (const float *)0x4a93ec);
		GAME_VAR(int, 0x9eeab0)++;
		if (g_depth > *(const float *)0x4a95d0)
			g_depth = f32(fld_m(&g_depth) - step);
		else {
			GAME_VAR(int, 0x9eeaa8) = 0;
			GAME_VAR(u32, 0x9eea90) = 0xc4098000;   /* -550 */
		}
	}
	Highlight h = { on, white, 1, 1, 1 };
	Tunnel t = { GAME_VAR(u32, 0x9eea90), 0x76d484, 0, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
	if (on != -1) {
		if (!GAME_VAR(int, 0x680370))
			caption(0x7501a4, on);
	} else if (!GAME_VAR(int, 0x680370) && !GAME_VAR(int, 0x9eeab4) && g_idle > *(const float *)0x4a95cc) {
		long double hint = fadd_m(fmul_m(fld_m((const float *)&g_hintStep), frame), &g_hint);
		g_hint = f32(hint);
		if (hint > *(const float *)0x4a9534) {
			g_hint = 1.0f;
			g_hintStep = 0xbd4ccccd;   /* -0.05 */
		} else if (!(g_hint >= *(const float *)0x4a93e8)) {
			g_hint = 0;
			g_hintStep = 0x3d4ccccd;
			g_idle = 0;
		}
		gfx_setProjection2D3D(2);
		glLoadIdentity();
		float alpha = g_hint > *(const float *)0x4a9424 ? 1.0f : g_hint;
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, BITS(alpha));
		text_drawBox16(0, 0x1d0, 0x280, (const char *)0x4b2a98);
	}
	glDisable(GL_TEXTURE_2D);
#undef g_depth
#undef g_idle
#undef g_hint
#undef g_hintStep
}
#undef SIX_WALLS
#undef FOUR_WALLS
#undef g_scroll
#undef g_tunnelPulseStep
#undef g_tunnelPulse
#undef g_tunnelAlpha
