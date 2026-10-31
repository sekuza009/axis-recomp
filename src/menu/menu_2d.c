/* menu_2d.c: the menus' 2D drawing primitives and the switch between the 3D projection and the menus' 2D one,
   with the widescreen fixes they carry (wide.h).

   The menus are laid out in 640 x 480 units. On a screen wider than that the original game's code cave (0x4a8fa4,
   added by the widefix patch) draws them into a centred box, h * 16 / 9 wide, or h * 4 / 3 once the patch DLL has
   rewritten it for [hud] menu43. Two things must still cover the whole screen: full-screen rectangles (fades, the
   white flash before loading, dimming), and the menu cursor, which would otherwise be cut off at the box's edge. */
#include "../game.h"
#include "../wide.h"
#include <string.h>

#define g_menuColour ((const u32 *)0x9da480)     /* RGBA floats */

/* the menu cursor's x (px = x * the scale, pixels) on the full screen, placed as it would be in the viewport it is
   drawn over (wide.h cursorX/cursorW), so it lines up with the menus */
static int cursor_x(float px)
{
	int W = (int)f32(f32((long double)640.0f * g_menuScaleX) + 0.5f);
	if (W <= 0)
		return (int)px;
	return *g_wide->cursorX + (int)f32(f32((long double)px * f32(*g_wide->cursorW)) / f32(W));
}

/* 0x41ef60: a vertex at menu units (x, y), y down from the top. With the patch DLL's menu fix this is the version
   it put in (to place the cursor), which works in single precision, each step rounded to a float, so the menus land
   on exactly the pixels they did with it; the original's products are extended precision, and differ from those
   by a pixel now and then. */
void (menu_vertex)(int x, int y)
{
	if (*g_wide->menuFix) {
		float px = f32((long double)f32(x) * g_menuScaleX);
		int vx = *g_wide->cursorOn ? cursor_x(px) : (int)px;
		glVertex2i(vx, g_screenH - (int)f32((long double)f32(y) * g_menuScaleY));
		return;
	}
	int dy = ftol((long double)y * g_menuScaleY);
	int vy = g_screenH - dy;
	glVertex2i(ftol((long double)x * g_menuScaleX), vy);
}

/* 0x427970: a rectangle in the menu colour, filled or as its outline; one that covers all of 640 x 480 is drawn
   over the full screen while the menus' box is narrower */
void (menu_drawRect)(int x0, int y0, int x1, int y1, int filled)
{
	int full = *g_wide->menuFix && x0 <= 0 && y0 <= 0 && x1 >= 640 && y1 >= 480;
	if (full)
		g_wide->fullScreen(1);
	glColor4f_stored(g_menuColour);
	if (filled) {
		glBegin(GL_QUADS);
		menu_vertex(x0, y0);
		menu_vertex(x1, y0);
		menu_vertex(x1, y1);
		menu_vertex(x0, y1);
	} else {
		glBegin(GL_LINES);
		menu_vertex(x0, y0);
		menu_vertex(x1, y0);
		menu_vertex(x1, y0);
		menu_vertex(x1, y1);
		menu_vertex(x1, y1);
		menu_vertex(x0, y1);
		menu_vertex(x0, y1);
		menu_vertex(x0, y0 - 1);   /* (sic: one past the corner) */
	}
	glEnd();
	if (full)
		g_wide->fullScreen(0);
}

/* the menus' box: centred, h * 16 / 9 wide (h * 4 / 3 when the patch DLL rewrote the cave's "shl eax, 4 / mov ebx, 9"
   for menu43), unless the screen is at most 8 pixels wider than that */
static void menu_box(int *x, int *w)
{
	u32 h = (u32)g_screenH;
	u32 box = code_matches(0x4a8fbb, "c1 e0 02 bb 03 00 00 00") ? (h << 2) / 3 : (h << 4) / 9;
	*x = 0;
	*w = g_screenW;
	if ((int)(box + 8) < g_screenW) {
		*x = (g_screenW - (int)box) >> 1;
		*w = (int)box;
	}
}

/* 0x41ef90: the 3D projection (mode 1) or the menus' 2D one (any other), unless it is the one set already */
void (gfx_setProjection2D3D)(int mode)
{
	if (mode == g_projMode)
		return;
	int x = 0, w = g_screenW, h = g_screenH;
	if (mode != 1)
		menu_box(&x, &w);
	/* during the in-match 2D pass (which draws through this switch: the player name labels, the HUD's text) the
	   menus' 4:3 box would clip the HUD: it gets the old 16:9 box back, or the full screen when that is narrower
	   or while the player markers draw (they are placed at screen pixels) */
	if (*g_wide->menu43 && *g_wide->inHud && h > 0) {
		int sw = 2 * x + w, w16 = h * 16 / 9, area = *g_wide->hudArea;
		if (w16 + 8 >= sw || area == 1 || area == 5) {
			x = 0;
			w = sw;
		} else {
			x = (sw - w16) / 2;
			w = w16;
		}
	}
	glViewport(x, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	if (mode == 1) {
		glLoadIdentity();
		gluPerspective(g_viewAngle, g_viewAspect, 1.0, 20000.0);
		glEnable(GL_DEPTH_TEST);
		g_projMode = mode;
		glMatrixMode(GL_MODELVIEW);
		return;
	}
	glLoadIdentity();
	gluOrtho2D(0.0, g_screenW, 0.0, g_screenH);
	glDisable(GL_DEPTH_TEST);
	g_projMode = mode;
	glMatrixMode(GL_MODELVIEW);
}

/* 0x427a40: a line in the menu colour from (x0, y0) to (x1, y1). Returns glEnd's eax */
u32 (menu_drawLine)(int x0, int y0, int x1, int y1)
{
	glColor4f_stored(g_menuColour);
	glBegin(GL_LINES);
	menu_vertex(x0, y0);
	menu_vertex(x1, y1);
	return IMPORT(0x4a9220, u32, void)();   /* glEnd */
}

/* 0x42f0f0: the 3D view over w x h pixels (from the corner): the projection from the view's angle and aspect.
   Returns the last glMatrixMode's eax */
u32 (gfx_setup3DView)(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_viewAngle, g_viewAspect, 1.0, 20000.0);
	return IMPORT(0x4a91fc, u32, u32)(GL_MODELVIEW);
}

/* 0x41f820: a menu frame begun: the screen cleared to black (colour and depth), white, blending by alpha. Returns
   glBlendFunc's eax */
u32 (menu_frameBegin)(void)
{
	IMPORT(0x4a91e0, void, float, float, float, float)(0, 0, 0, 0);   /* glClearColor */
	glClearDepth(1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(0x0be2);   /* GL_BLEND */
	return IMPORT(0x4a91ec, u32, u32, u32)(0x302, 0x303);   /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) */
}

/* 0x40ce70: the screen dimmed by a black overlay fading in (0x4deb74 grows by the frame time times a rate; its alpha
   at most 1). Returns menu_drawRect's eax */
u32 (menu_drawDimOverlay)(void)
{
	long double a = fadd_m(fmul_m(fld_m(&g_frameTime), (const float *)0x4a943c), (const float *)0x4deb74);
	g_roomFade = (float)a;
	float alpha = (float)a;
	if (a > k_1f)
		BITS(alpha) = 0x3f800000;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x9da480, 0x3f800000, 0x3f800000, 0x3f800000, BITS(alpha));   /* the menu colour (1, 1, 1, alpha) */
	return GAME_CDECL(0x427970, u32, int, int, int, int, int)(0, 0, 640, 480, 1);   /* menu_drawRect, filled */
}

/* 0x41f050: the menu camera: the scene moved by minus the camera's position (0x4df024), then the view from it towards
   the look-at point (0x680378), y up. Returns gluLookAt's eax */
u32 (gfx_setMenuCamera)(void)
{
	float z = (float)-fld_m((const float *)0x4df02c), y = (float)-fld_m((const float *)0x4df028),
	      x = (float)-fld_m((const float *)0x4df024);
	IMPORT(0x4a9214, void, float, float, float)(x, y, z);   /* glTranslatef */
	glLoadIdentity();
	const float *eye = (const float *)0x4df024, *at = (const float *)0x680378;
	return ((u32 (STDCALL *)(double, double, double, double, double, double, double, double, double))*(const u32 *)0x4a904c)(
		eye[0], eye[1], eye[2], at[0], at[1], at[2], 0.0, 1.0, 0.0);   /* gluLookAt */
}

/* ---- a dialog frame opening on (x0, y0) .. (x1, y1) (phase 0x4de740, frame counter 0x76d428) ---- */
#define g_framePhase g_menuFramePhase
#define g_frameCount g_menuFrameCounter

/* the counter's progress: frames x the frame time x scale (unrounded) */
static long double frame_progress(const float *scale)
{
	return fmul_m(fmul_m((long double)g_frameCount, &g_frameTime), scale);
}

/* a progress, or the limit once it has gone past it */
static int up_to(long double progress, int limit)
{
	return progress > (long double)limit ? limit : ftol(progress);
}

/* the fading lines' alpha: 1 - frames x the frame time / 10, 0 once below */
static float fading(void)
{
	long double a = frame_progress((const float *)0x4a93ec);
	return a > k_1f ? 0.0f : f32(fsubr_m(a, (const float *)0x4a9424));   /* 1 - a */
}

static void line(int xa, int ya, int xb, int yb)
{
	glBegin(GL_LINES);
	menu_vertex(xa, ya);
	menu_vertex(xb, yb);
	glEnd();
}

/* the next phase once the counter x 64 x the frame time passes 640 */
static int phase_done(int next)
{
	g_frameCount++;
	if (fmul_m((long double)(g_frameCount << 6), &g_frameTime) > k_640f) {
		g_framePhase = next;
		g_frameCount = 0;
		return 1;
	}
	return 0;
}

/* 0x428c30: the dialog frame opening, one step a frame, in three phases: 1 two cyan lines grow from the left edge
   along y0 and from the bottom up x0 (64 and 48 units a frame); 2 those fade out as full-screen lines while two
   more grow in from the right along y1 and down x1; 3 the green lines along y1 and x1 fade while a dark blue panel
   (0, 0, 0.5, 0.3) grows from (x0, y0) by a tenth of the frame a frame, and once it is as wide as the frame the
   phase goes back to 1 and the message box flag (0x90d1c4) is cleared. Other phases draw nothing. The callers pass
   on the eax it leaves to menu_frame, which ignores it */
void (menu_drawFrame)(int x0, int y0, int x1, int y1)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	if (g_framePhase == 1) {
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		line(0, y0, up_to(frame_progress((const float *)0x4a9518), x1), y0);
		glBegin(GL_LINES);
		menu_vertex(x0, g_screenH);
		long double down = frame_progress((const float *)0x4a9514);
		menu_vertex(x0, down > (long double)y1 ? g_screenH - y1 : g_screenH - ftol(down));
		glEnd();
		if (phase_done(2))
			return;
	}
	if (g_framePhase == 2) {
		glColor4f(0.0f, 1.0f, 1.0f, fading());
		line(0, y0, g_screenW, y0);
		line(x0, g_screenH, x0, 0);
		glColor4f(0.0f, 1.0f, 1.0f, 1.0f);
		long double across = frame_progress((const float *)0x4a9518);
		line(across > (long double)x1 ? g_screenW - x1 : g_screenW - ftol(across), y1, g_screenW, y1);
		line(x1, up_to(frame_progress((const float *)0x4a9514), y1), x1, 0);
		if (phase_done(3))
			return;
	}
	if (g_framePhase != 3)
		return;
	glColor4f(0.0f, 1.0f, 0.0f, fading());
	line(0, y1, g_screenW, y1);
	line(x1, g_screenH, x1, 0);
	set_colour_bits(g_rectColour, 0, 0, 0x3f000000, 0x3e99999a);   /* 0.5, 0.3 */
	int dx = (x1 - x0) / 10, dy = (y1 - y0) / 10, n = g_frameCount;
	long double grown = fmul_m((long double)(dy * n), &g_frameTime);
	long double bottom = (long double)y0 + grown;
	int right = ftol(fmul_m((long double)(dx * n), &g_frameTime));
	if ((long double)y1 < bottom || __builtin_isnan(bottom))
		menu_drawRect(x0, y0, right + x0, y1, 1);
	else
		menu_drawRect(x0, y0, right + x0, ftol(grown) + y0, 1);
	n = ++g_frameCount;
	long double width = fmul_m((long double)(dx * n), &g_frameTime) + (long double)x0;
	if (!((long double)x1 > width)) {
		g_framePhase = 1;
		g_frameCount = 0;
		g_dialogOpen = 0;
	}
}
#undef g_framePhase
#undef g_frameCount

/* 0x4290d0: the message box: a dark blue-grey panel (0.2, 0.2, 0.7, alpha 0.7) and its two lines (0x4df81c, then the
   message 0x74de24) in yellow. Returns the text call's eax */
u32 (menu_drawMessageBox)(void)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x9da480, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
	menu_drawRect(0x50, 0xc8, 0x230, 0x118, 1);
	GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	GAME_CDECL(0x4029d0, u32, int, int, int, const char *)(0x69, 0xdc, 0x217, (const char *)0x4df81c);
	return GAME_CDECL(0x4029d0, u32, int, int, int, const char *)(0x69, 0xf4, 0x217, (const char *)0x74de24);
}

/* 0x428890: the text cursor at (x, y), a green bar 7 x 15 menu units, its alpha 1 - a timer (0x4de1f0: grows by the
   frame time, back to 0 past 0x4a9508; a frame counter 0x9da908 wraps past 40). Returns glEnd's eax */
u32 (menu_drawTextCursor)(int x, int y)
{
	long double t = fmul_m(fld_m(&g_frameTime), (const float *)0x4a950c);
	int frames = g_frameCounter40 + 1;
	t = fadd_m(t, (const float *)0x4de1f0);
	g_frameCounter40 = frames;
	g_cursorBlinkTimer = (float)t;
	if (frames > 0x28)
		g_frameCounter40 = 0;
	if (t > k_0_9f)
		(*(int *)&g_cursorBlinkTimer) = 0;
	gfx_setProjection2D3D(2);
	float alpha = (float)fsub_m(fld_m((const float *)0x4a9424), (const float *)0x4de1f0);
	glColor4f_bits(0, 0x3f800000, 0, BITS(alpha));
	glBegin(GL_QUADS);
	menu_vertex(x, y);
	menu_vertex(x + 7, y);
	menu_vertex(x + 7, y + 15);
	menu_vertex(x, y + 15);
	return IMPORT(0x4a9220, u32, void)();   /* glEnd */
}

/* 0x428940: the input line at (x, y) in green with its cursor after the typed characters (8 units each); a password
   (0x4e1868) shows as stars. Returns the text call's eax (or the dialog's state while one is open) */
u32 (menu_drawInputLine)(int x, int y)
{
	if (g_dialogOpen)
		return (u32)g_dialogOpen;
	GAME_CDECL(0x41f0e0, void, void *, u32, u32, u32, u32)((void *)0x76d438, 0, 0x3f800000, 0, 0x3f800000);
	GAME_CDECL(0x428890, u32, int, int)(x + g_chatLength * 8, y);   /* menu_drawTextCursor: the cursor */
	if (!g_chatFieldFlag)
		return GAME_CDECL(0x402620, u32, int, int, const char *)(x, y, (const char *)0x9dc92c);   /* text_draw8 */
	char stars[0x30];   /* the original zeroes 30 bytes of its frame here: a longer password (the fields take 20) would run over */
	int n = (int)strlen((const char *)0x9dc92c);
	memset(stars, 0, 30);
	if (n > 0)
		memset(stars, '*', n);
	return GAME_CDECL(0x402620, u32, int, int, const char *)(x, y, stars);
}
