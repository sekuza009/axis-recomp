/* fixes/hud.c (native build, AXIS_NATIVE): the proportional HUD. The in-match HUD is laid out in 640 x 480 units and
   drawn with x scaled by width/640 and y by height/480, so wider than 4:3 its panels and digits were stretched
   sideways. Every 2D vertex of the game goes through glVertex2i (game.h sends it here); those the HUD draws have x
   remapped so each element is scaled like y (as on 4:3) and anchored to the left edge, the right edge or the centre
   of the HUD area (the screen, at most [hud] maxaspect wide: 16:9 by default). [hud] proportional=0 turns it off.
   Ported from the patch layer (axisnet_recomp.c: hook_glVertex2i, marker_begin/end, ov_begin/end, pu_text,
   label_text and the wrappers around the HUD's calls), which told the HUD's parts apart by the return addresses of
   its OpenGL calls; here the HUD's own code says which part is drawing:
   - the in-match 2D pass counts itself (g_fixInHud, main_loop.c) and each of its parts sets g_fixHudArea through
     the functions below; the main HUD says which of its parts draws next (g_fixHudPart, HUD_* of wide.h);
   - the player markers and the lock-on square are placed at screen pixels (the players' projected positions), so
     they are sized for 4:3 (the render width reads 4H/3 while they draw) and their x is mapped 1:1 to the screen,
     with the full-screen viewport (a centred 16:9 one would clip them on an ultrawide screen);
   - the replay's overlay (camera and clock icons, their numbers, the message box, the watched player's name, the
     ranking) is drawn outside the pass: it is counted as HUD drawing and given the HUD's viewport while it draws. */
#ifdef AXIS_NATIVE
#include "../game.h"
#include "../wide.h"
#include "fixes.h"
#include <string.h>

#define real_glVertex2i(x, y) IMPORT(0x4a91f4, void, int, int)(x, y)
#define real_glViewport(x, y, w, h) IMPORT(0x4a91d4, void, int, int, int, int)(x, y, w, h)

int g_fixHudPart;              /* the main HUD's part drawing (HUD_*: hud_main.c) */
int g_fixPenSharp;             /* font_penDraw samples pixel-sharp (the power-up countdown) */
int g_fixPenDraw;              /* font_penDraw is drawing (glyph_cells.c) */

enum { ANCHOR_NONE, ANCHOR_LEFT, ANCHOR_CENTRE, ANCHOR_RIGHT };

/* ---- the player markers and the lock-on square: sized for 4:3, the full screen to draw in ---- */
static int g_markerW;                       /* the real render width while they draw (0: not drawing) */
static FixView g_markerView;                /* the viewport they found */

static void markers_begin(void)
{
	int w = g_glWidth, h = g_glHeight;
	g_markerW = w;
	if (w > 0 && h > 0 && w * 3 > h * 4)
		g_glWidth = (h * 4 + 1) / 3;   /* sizes in width/640 units come out 4:3; positions are screen pixels anyway */
	g_markerView = g_fixView;
	if (w > 0 && h > 0 && g_fixView.w < w)
		fix_glViewport(0, 0, w, h);
}

static void markers_end(void)
{
	g_glWidth = g_markerW;
	if (g_markerW > 0 && g_markerView.w > 1 && g_markerView.w < g_markerW)
		fix_glViewport(g_markerView.x, 0, g_markerView.w, g_glHeight);
}

void fix_drawPlayerMarkers(Scene *scene)
{
	int was = g_fixHudArea;
	g_fixHudArea = FIX_AREA_MARKERS;
	markers_begin();
	((void (THISCALL *)(Scene *))(void *)FN_hud_drawPlayerMarkers)(scene);
	markers_end();
	g_fixHudArea = was;
}

void fix_drawLockOn(Scene *scene)
{
	int was = g_fixHudArea;
	g_fixHudArea = FIX_AREA_LOCKON;
	markers_begin();
	((void (THISCALL *)(Scene *))(void *)FN_hud_drawLockOn)(scene);
	markers_end();
	g_fixHudArea = was;
}

/* the pass's other parts that are told apart: the main HUD, the FPS counter, the ranking */
static void in_area(int area, void *fn, Scene *scene)
{
	int was = g_fixHudArea;
	g_fixHudArea = area;
	((void (THISCALL *)(Scene *))fn)(scene);
	g_fixHudArea = was;
}

void fix_drawMainHud(Scene *scene) { in_area(FIX_AREA_MAIN, (void *)FN_hud_drawMain, scene); }
void fix_drawFps(Scene *scene) { in_area(FIX_AREA_FPS, (void *)FN_hud_drawFps, scene); }
void fix_drawRanking(Scene *scene) { in_area(FIX_AREA_RANKING, (void *)FN_hud_drawRanking, scene); }

/* ---- the replay's overlay: counted as HUD drawing, in the HUD's viewport (a centred 16:9 box, or the full screen
   when that is narrower). It can start while the viewport is still the menus' 4:3 box, which clipped its left and
   right elements; the viewport found is put back after. ---- */
static FixView g_overlayView;
static int g_overlaySet;

int fix_overlayBegin(int area)
{
	int was = g_fixHudArea;
	g_fixHudArea = area;
	g_fixInHud++;
	g_overlaySet = 0;
	int W = g_fixView.x * 2 + g_fixView.w, h = g_fixView.h, w16 = h * 16 / 9, x, w;
	if (g_fixView.w <= 1 || h <= 0)
		return was;
	if (w16 + 8 >= W) {
		x = 0;
		w = W;
	} else {
		x = (W - w16) / 2;
		w = w16;
	}
	if (x == g_fixView.x && w == g_fixView.w)
		return was;
	g_overlayView = g_fixView;
	g_overlaySet = 1;
	fix_glViewport(x, g_fixView.y, w, h);
	return was;
}

void fix_overlayEnd(int was)
{
	if (g_overlaySet) {
		g_overlaySet = 0;
		fix_glViewport(g_overlayView.x, g_overlayView.y, g_overlayView.w, g_overlayView.h);
	}
	g_fixInHud--;
	g_fixHudArea = was;
}

/* ---- the power-up countdown (font_penDraw: a fixed-pixel font, 14-pixel glyphs at any resolution). Its glyphs are
   scaled about the text's top left like the rest of the HUD, and the text is centred on its 32-unit icon by its
   real width (the game assumed 22 pixels; the font is proportional and now scaled). ---- */
static int g_penText, g_penX, g_penY;

void fix_powerUpText(int x, int y, int font, const char *format, int value)
{
	if (font == 1 && g_settings.hudProportional) {
		char s[32];
		int lead = 0, shown = 0, spaces = 0, w = g_glWidth, h = g_glHeight;   /* ("%2d" pads with a space) */
		sprintf(s, format, value);   /* (a number: "%2d") */
		for (const char *c = s; *c; c++) {
			if (*c < 0x20 || *c > 0x7e)
				continue;
			int cw = g_penPropWidths[*c - 0x20];
			if (*c == ' ') {
				if (shown)
					spaces += cw;
				else
					lead += cw;
			} else {
				shown += spaces + cw;
				spaces = 0;
			}
		}
		double scale = w > 0 && h > 480 ? w / 640.0 : 1.0;   /* the glyphs' scale (fix_hudVertex) */
		if (shown)
			x += 11 - (int)((lead + shown / 2.0) * scale + 0.5);
	}
	g_penX = x;
	g_penY = y;
	g_penText = g_settings.hudProportional;
	g_fixPenSharp = 1;   /* (sampled pixel-sharp like the menu text: the next glyph's column showed as a thin line) */
	((void (CDECL *)(int, int, int, const char *, int))(void *)FN_font_penDraw)(x, y, font, format, value);
	g_fixPenSharp = 0;
	g_penText = 0;
}

/* ---- the name labels over the mechs: centred on the player, letters 4:3. The label's x comes in units of the 4:3
   marker width; the text is drawn with the real width, and never wraps (past 640 units, near the right edge of a
   wide screen, a name was drawn one letter per line). ---- */
static int g_label, g_labelX;
static double g_labelPx;

void fix_labelText(int x1, int y, int x2, const char *name, int size)
{
	g_labelX = (x1 + x2) / 2;
	g_labelPx = g_labelX * (double)g_glWidth / 640.0;   /* the player's screen pixel */
	g_label = g_settings.hudProportional;
	int markerW = g_glWidth, wrapX = g_textWrapX, bottom = g_textBottom;
	if (g_markerW > 0)
		g_glWidth = g_markerW;
	g_textWrapX = 0x7fffffff;
	g_textBottom = 0x7fffffff;
	text_drawCentred(x1, y, x2, name, size);
	g_textWrapX = wrapX;
	g_textBottom = bottom;
	g_glWidth = markerW;
	g_label = 0;
}

/* ---- every 2D vertex ---- */
static int anchor_of(int area)
{
	switch (area) {
	case FIX_AREA_OVERLAY_LEFT: return ANCHOR_LEFT;
	case FIX_AREA_OVERLAY_RIGHT: return ANCHOR_RIGHT;
	case FIX_AREA_OVERLAY_CENTRE: return ANCHOR_CENTRE;
	case FIX_AREA_FPS: return ANCHOR_RIGHT;
	case FIX_AREA_MAIN:   /* the part the main HUD says (the power-up countdown too) */
		switch (g_fixHudPart) {
		case HUD_LEFT: return ANCHOR_LEFT;
		case HUD_RIGHT: return ANCHOR_RIGHT;
		case HUD_AUTO: case HUD_CENTRE: return ANCHOR_CENTRE;
		default: return ANCHOR_NONE;   /* as drawn */
		}
	default: return ANCHOR_CENTRE;   /* the rest of the pass (ranking, chat, the Esc menu, counters, messages) */
	}
}

void fix_hudVertex(int x, int y)
{
	int w = g_glWidth, h = g_glHeight, area = g_fixHudArea;
	FixView v = g_fixView;
	if (!g_settings.hudProportional || w <= 0 || h <= 0 || v.w <= 1) {
		real_glVertex2i(x, y);
		return;
	}
	/* the power-up countdown's glyphs: scaled about the text's top left (x by width/640, y by height/480) */
	if (g_penText && g_fixPenDraw && h > 480) {
		int top = h - g_penY;
		x = g_penX + (int)((x - g_penX) * (w / 640.0) + 0.5);
		y = top + (int)((y - top) * (h / 480.0) + (y >= top ? 0.5 : -0.5));
	}
	/* the markers: their x is the player's screen pixel, mapped 1:1 to the screen (the HUD's projection spans 0..w
	   over the viewport); a name label's letters centred on the player, 4:3 */
	if (g_markerW > 0 && (area == FIX_AREA_MARKERS || area == FIX_AREA_LOCKON)) {
		double X = x;
		if (g_label) {
			double c = v.x + (double)g_labelX * v.w / 640.0, s = 640.0 * h / 480.0 / v.w;
			X = g_labelPx + (v.x + (double)x * v.w / w - c) * (s < 1 ? s : 1);
		}
		real_glVertex2i((int)((X - v.x) * g_markerW / v.w + (X >= v.x ? 0.5 : -0.5)), y);
		return;
	}
	if (!g_fixInHud) {
		real_glVertex2i(x, y);
		return;
	}
	if (area == FIX_AREA_MAIN && g_fixHudPart == HUD_PIXELS) {   /* drawn round in screen pixels (the alert ring) */
		real_glVertex2i((int)((double)(x - v.x) * w / v.w + (x >= v.x ? 0.5 : -0.5)), y);
		return;
	}
	double screenW = v.x * 2 + v.w, areaW = screenW, k = h / 480.0;   /* the HUD area's width, pixels per unit */
	if (g_settings.hudMaxAspect > 0 && areaW > h * g_settings.hudMaxAspect)
		areaW = h * g_settings.hudMaxAspect;
	if (area == FIX_AREA_MAIN && g_fixHudPart == HUD_CORNER) {   /* 64 fixed pixels at the top right: in HUD units */
		double X = (screenW + areaW) / 2 - (w - x) * k;
		real_glVertex2i((int)((X - v.x) * w / v.w + 0.5), h - (int)((h - y) * k + 0.5));
		return;
	}
	int a = anchor_of(area);
	if (a != ANCHOR_NONE && areaW > 640 * k) {   /* (only when the HUD area is wider than 4:3) */
		double X = v.x + (double)x * v.w / w, bx = (screenW - areaW) / 2, u = (X - v.x) * 640.0 / v.w;
		if (a == ANCHOR_LEFT)
			X = bx + u * k;
		else if (a == ANCHOR_RIGHT)
			X = bx + areaW - (640.0 - u) * k;
		else
			X = screenW / 2.0 + (u - 320.0) * k;
		x = (int)((X - v.x) * w / v.w + (X >= v.x ? 0.5 : -0.5));
	}
	real_glVertex2i(x, y);
}
#endif
