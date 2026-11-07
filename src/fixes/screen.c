/* fixes/screen.c (native build, AXIS_NATIVE): the patch layer's screen fixes as the game's own code - the menus'
   centred 4:3 box and what must still cover the whole screen, the menu pointer, pixel-sharp text, the HUD digits.
   Ported from axisnet_recomp.c (hook_glViewport, menu_full, cursor_draw, cursor_vtx, trans_wrap, text_pass,
   digit_texcoord, update_digit_h), which did them by hooking OpenGL and rewriting the game's calls. */
#ifdef AXIS_NATIVE
#include "../game.h"
#include "fixes.h"

#define real_glViewport(x, y, w, h) IMPORT(0x4a91d4, void, int, int, int, int)(x, y, w, h)
#define real_glVertex2i(x, y) IMPORT(0x4a91f4, void, int, int)(x, y)

FixView g_fixView = { 0, 0, 1, 0 };
int g_fixInHud, g_fixHudArea;
int g_fixCursorOn, g_fixCursorX, g_fixCursorW;

/* every glViewport of the game's code (game.h): the viewport is kept, for the box and the pointer below */
void fix_glViewport(int x, int y, int w, int h)
{
	g_fixView.x = x;
	g_fixView.y = y;
	g_fixView.w = w > 0 ? w : 1;
	g_fixView.h = h;
	real_glViewport(x, y, w, h);
}

/* the menus' box as it stands: the viewport kept, else the rule (a centred 4:3 box; 16:9 with menu43=0) */
static void menu_box(int W, int H, int *x, int *w)
{
	if (g_fixView.w > 1 && g_fixView.w <= W) {
		*x = g_fixView.x;
		*w = g_fixView.w;
		return;
	}
	*w = g_settings.menu43 ? (W * 3 > H * 4 ? H * 4 / 3 : W) : (W * 9 > H * 16 ? H * 16 / 9 : W);
	*x = (W - *w) / 2;
}

static int screen_w(void) { return (int)(640.0f * g_menuScaleX + 0.5f); }

/* ---- drawing over the whole screen while the menus' box is narrower: full-screen rectangles (fades, the white
   flash before loading, dimming) and the title's emblem transition. Nests; the box comes back after the last. ---- */
static int g_fullDepth, g_fullBoxX, g_fullBoxW;

void fix_fullScreen(int on)
{
	int H = g_screenH, W = screen_w();
	if (on) {
		if (g_fullDepth++ == 0) {
			menu_box(W, H, &g_fullBoxX, &g_fullBoxW);
			if (g_fullBoxW < W)
				real_glViewport(0, 0, W, H);   /* (not kept: the box is still the menus') */
		}
	} else if (g_fullDepth > 0 && --g_fullDepth == 0) {
		if (g_fullBoxW < W)
			real_glViewport(g_fullBoxX, 0, g_fullBoxW, H);
	}
}

/* the title screen's emblem transition (menuState200_title), over the whole screen */
void fix_titleEmblemTransition(void)
{
	fix_fullScreen(1);
	((void (CDECL *)(void))(void *)FN_menu_titleEmblemTransition)();
	fix_fullScreen(0);
}

/* ---- the menu pointer: drawn over the whole screen (the box cut it off at its edge), placed as it would be in the
   box so that it lines up with the menus; the 2D switch is made first so the one inside menu_drawCursor cannot reset
   the viewport to the box. The viewport found is put back as it was. ---- */
void fix_drawCursor(void)
{
	gfx_setProjection2D3D(2);
	int W = screen_w(), x = g_fixView.x, y = g_fixView.y, w = g_fixView.w, h = g_fixView.h;
	if (w <= 1 || h <= 0 || w >= W) {
		((void (CDECL *)(void))(void *)FN_menu_drawCursor)();
		return;
	}
	g_fixCursorX = x;
	g_fixCursorW = w;
	g_fixCursorOn = 1;
	real_glViewport(0, y, W, h);
	((void (CDECL *)(void))(void *)FN_menu_drawCursor)();
	real_glViewport(x, y, w, h);
	g_fixCursorOn = 0;
}

/* the pointer's x (px: menu units x the scale, pixels) on the full screen, placed as in the box it is drawn over */
static int cursor_x(float px)
{
	int W = screen_w();
	return W > 0 ? g_fixCursorX + (int)(px * g_fixCursorW / W) : (int)px;
}

/* the pointer sprite's two right-hand corners (x + 47): 47 units of the vertical scale wide, so the arrow keeps its
   proportions on a wide screen (it came out stretched sideways); the tip and the click point stay */
void fix_cursorVertex(int x, int y)
{
	float sx = g_menuScaleX, sy = g_menuScaleY;
	int H = g_screenH, W = screen_w(), boxX, boxW;
	menu_box(W, H, &boxX, &boxW);
	float k = boxW > 0 ? (float)W / boxW : 1.0f;
	if (g_fixCursorOn)
		real_glVertex2i(cursor_x((x - 47) * sx) + (int)(47 * sy), H - (int)(y * sy));
	else
		real_glVertex2i((int)((x - 47) * sx + 47 * sy * k), H - (int)(y * sy));
}

/* ---- the bitmap fonts' ASCII passes drawn with nearest-texel sampling ([hud] sharptext): each character's texture
   rectangle runs up to its cell's unused column and row, so with linear filtering the neighbouring texels showed as
   thin lines at high resolutions. The font texture's filters are put back afterwards. ---- */
void fix_asciiPass(void *pass, int x, int y, const char *text)
{
	int saved[2], on = g_settings.sharpText && platform_texNearest(saved);
	((void (CDECL *)(int, int, const char *))pass)(x, y, text);
	if (on)
		platform_texRestore(saved);
}

/* ---- the HUD's digits (hud_drawDigits): their height factor, height-based on a screen wider than 4:3 (it was the
   width's, so the digits came out too tall), and their texture corners half a texel inside each 35 x 27 cell (the
   linear filter blended in the row above: a thin green dash over the shield digits) ---- */
static float g_digitHeight = 26.0f;

const float *fix_digitHeight(void)
{
	int w = g_glWidth, h = g_glHeight;
	g_digitHeight = (g_settings.hudProportional && w > 0 && h > 0 && w * 3 > h * 4) ? (float)(26.0 * 640.0 * h / (480.0 * w)) : 26.0f;
	return &g_digitHeight;
}

static unsigned g_digitCorner;

void STDCALL fix_digitTexCoord(u32 s, u32 t)
{
	const float e = 0.5f / 256;
	unsigned k = g_digitCorner++ & 3;   /* corners: top-left, top-right, bottom-right, bottom-left */
	float fs = *(const float *)&s + ((k == 0 || k == 3) ? e : -e);
	float ft = *(const float *)&t + (k < 2 ? e : -e);
	glTexCoord2f(fs, ft);
}
#endif
