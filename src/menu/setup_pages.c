/* setup_pages.c: the setup screen's pages drawn */
#include "../game.h"
#include <string.h>

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

/* 0x424810: the sound page (0x4ddad0 .. 0x4ddadc): the window, a cyan frame, the title MSG(171, "SETUP SOUND"); the volume slider
   from the button texture (g_buttonTexture): the two arrows, the track and the bar (the volume g_volumeSetting long); while
   g_setupPressedClock runs down (by g_frameTime, then -1 into g_setupPressed) the arrow pressed (g_setupPressed: 0 / 1, or 2 / 3 a row lower)
   lit; the label MSG(172, "EFFECT SOUND") and three switches (MSG(173, "BGM"), 0x80 apart) with their on / off names (MSG(176, "OFF") + 0x80 x:
   the volume on, g_setupSound3D, g_setupStereoReverse), the one under the pointer (5 .. 7, by setupSound_hitTest) yellow with a shadow; two
   buttons (MSG(178, "$[0] ACCEPT"), lit from 8) and the border. The original leaves eax to callers that ignore it */
void (setup_drawSoundPage)(void)
{
#define X0 g_setupSoundLeft
#define Y0 (g_setupSoundRect[1])
#define X1 g_setupSoundRight
#define Y1 (g_setupSoundRect[3])
	const u32 *bright = g_setupColourLit, *dim = g_setupColourDim;
	int hovered = setupSound_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(X0 + 0x20, Y0 + 0x30, X1 - 0x20, Y1 - 0x20, 0);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)MSG(171, "SETUP SOUND"));
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	tex_quad(0.0f, 0.25f, 0.25f, 0.375f, X0 + 0x50, Y0 + 0x50, X0 + 0x90, Y0 + 0x70);      /* the arrows */
	tex_quad(0.25f, 0.25f, 0.5f, 0.375f, X0 + 0x190, Y0 + 0x50, X0 + 0x1d0, Y0 + 0x70);
	tex_quad(0.0f, 0.0f, 1.0f, 0.125f, X0 + 0x90, Y0 + 0x50, X0 + 0x190, Y0 + 0x70);       /* the track */
	long double volume = (long double)g_volumeSetting;
	float s = f32(fmul_m(volume, k_0_01f_4a9504));
	int x = X0 - ftol(fmul_m(volume, k_m2_56f)) + 0x90;
	tex_quad(0.0f, 0.125f, s, 0.25f, X0 + 0x90, Y0 + 0x50, x, Y0 + 0x70);                  /* the bar */
	const float *zero = (const float *)ADDR(k_0f);
	if (g_setupPressedClock > *zero) {
		switch (g_setupPressed) {
		case 0: tex_quad(0.5f, 0.25f, 0.75f, 0.375f, X0 + 0x50, Y0 + 0x50, X0 + 0x90, Y0 + 0x70); break;
		case 1: tex_quad(0.75f, 0.25f, 1.0f, 0.375f, X0 + 0x190, Y0 + 0x50, X0 + 0x1d0, Y0 + 0x70); break;
		case 2: tex_quad(0.5f, 0.25f, 0.75f, 0.375f, X0 + 0x50, Y0 + 0x8c, X0 + 0x90, Y0 + 0xac); break;
		case 3: tex_quad(0.75f, 0.25f, 1.0f, 0.375f, X0 + 0x190, Y0 + 0x8c, X0 + 0x1d0, Y0 + 0xac); break;
		}
		long double left = fsub_m(fld_m(&g_setupPressedClock), (const float *)ADDR(g_frameTime));
		g_setupPressedClock = f32(left);
		if (!(left >= *zero)) {
			g_setupPressedClock = 0;
			g_setupPressed = -1;
		}
	}
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x50, Y0 + 0x3c, (const char *)MSG(172, "EFFECT SOUND"));
	for (int k = 0; k < 3; k++)
		text_draw8(X0 + 0x8c, Y0 + 0x9c + k * 0x28, (const char *)(MSG(173, "BGM") + k * 0x80));
	int on = g_effectsVolume > 0;
	for (int k = 0; k < 3; k++) {
		int value = k == 0 ? on : GAME_VAR(int, k == 1 ? ADDR(g_setupSound3D) : ADDR(g_setupStereoReverse));
		const char *name = (const char *)(MSG(176, "OFF") + value * 0x80);
		int y = Y0 + 0x9c + k * 0x28;
		if (hovered == 5 + k) {
			set_colour_bits(g_textColour, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01: the shadow */
			text_draw8(X0 + 0x12d, y + 2, name);
			set_colour_bits(g_textColour, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);            /* 1, 0.8, 0, 1 */
			text_draw8(X0 + 0x12c, y + 1, name);
		} else {
			set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
			text_draw8(X0 + 0x12c, y, name);
		}
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		int lit = hovered == k + 8;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + k * 0x8c;
		menu_drawWideButton(bx + 0x90, Y0 + 0x113, bx + 0x108, Y0 + 0x133, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(bx + 0x90, Y0 + 0x11b, bx + 0x108, (const char *)(MSG(178, "$[0] ACCEPT") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x425460: the graphics page ("SETUP GRAPHIC"; 0x4dddd0 .. 0x4ddddc): the window, the title MSG(181, "SETUP GRAPHIC"), seven labels (MSG(182, "VIDEO MODE"), 0x80
   apart) and their values: the screen size (the names at g_resolutionNames by g_setupResolution) and six choices, each from its own
   table of 0x32-byte names (by 0x4ddba4 .. 0x4ddbb8); the value under the pointer (0 .. 6, by setupGraphic_hitTest) drawn
   again with a shadow, in yellow; two buttons (MSG(189, "$[0] ACCEPT"), lit from 7) and the border. The caller ignores the eax it
   leaves */
void (setup_drawGraphicPage)(void)
{
#define X0 (g_setupGraphicRect[0])
#define Y0 g_setupGraphicTop
#define X1 (g_setupGraphicRect[2])
#define Y1 (g_setupGraphicRect[3])
	static const u32 names[6] = { OBJ(g_colourDepthTexts), OBJ(g_fxStatusTexts), OBJ(g_linearFilterTexts), OBJ(g_mipMapTexts), OBJ(g_viewFpsTexts), OBJ(g_simpleMenuTexts) };
	const u32 *bright = g_setupColourLit, *dim = g_setupColourDim;
	int hovered = setupGraphic_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)MSG(181, "SETUP GRAPHIC"));
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 7; k++)
		text_draw8(X0 + 0x50, Y0 + 0x44 + k * 0x28, (const char *)(MSG(182, "VIDEO MODE") + k * 0x80));
	/* the values: the screen size's name, then each choice's */
	const char *value[7];
	value[0] = GAME_VAR(const char *, OBJ(g_resolutionNames) + g_setupResolution * 4);
	for (int k = 1; k < 7; k++)
		value[k] = (const char *)(RELOC(names[k - 1]) + (int)g_graphicEdited[k] * 0x32);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	for (int k = 0; k < 7; k++)
		text_draw8(X0 + 0xe6, Y0 + 0x44 + k * 0x28, value[k]);
	if (hovered >= 0 && hovered <= 6) {
		int y = Y0 + 0x44 + hovered * 0x28;
		set_colour_bits(g_textColour, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01: the shadow */
		text_draw8(X0 + 0xe6, y, value[hovered]);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);            /* 1, 0.8, 0, 1 */
		text_draw8(X0 + 0xe5, y - 1, value[hovered]);
	}
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		int lit = hovered == k + 7;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + k * 0x8c;
		menu_drawWideButton(bx + 0x64, Y1 - 0x40, bx + 0xdc, Y1 - 0x20, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(bx + 0x64, Y1 - 0x38, bx + 0xdc, (const char *)(MSG(189, "$[0] ACCEPT") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* ---- the controls page ---- */
#define glTexCoord2i(s, t) IMPORT(0x4a91d8, void, int, int)(s, t)

/* the binding each key row of the first three tabs shows (as setup_bindKey edits them, setup_keys.c);
   rows 4 and 9 of the third tab (bindings 25 and 31) are fixed keys */
static const signed char key_rows[3][11] = {
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1 },
	{ 10, 11, 12, 15, 16, 17, 18, 13, 14, 19, 20 },
	{ 21, 22, 23, 24, 25, 26, 28, 29, 30, 31, -1 },
};

/* a key tab (0 .. 2): its title bright again, its labels, and each row's two keys by name (g_keyNames; the unbound
   value g_dikNone shows nothing). A fixed row is red, its one key in large type in both columns */
static void key_tab(int tab)
{
#define X0 g_setupControlLeft
#define Y0 g_setupControlTop
	static const u32 labels[3] = { MSG(216, "FORWARD"), MSG(231, "FIRE"), MSG(246, "CHAT") };
	static const int rows[3] = { 10, 11, 10 };
	const u32 *bright = g_setupColourLit;
	const char *const *key_name = (const char *const *)OBJ(g_keyNames);
	int none = g_dikNone;
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x46 + tab * 0x78, Y0 + 0x12, (const char *)(MSG(202, "$[0] MOVE") + tab * 0x80));
	for (int r = 0; r < rows[tab]; r++)
		text_draw8(X0 + 0x30, Y0 + 0x5c + r * 0x18, (const char *)(RELOC(labels[tab]) + r * 0x80));
	for (int r = 0; r < rows[tab]; r++) {
		const int *slot = (const int *)(OBJ(g_controlsEdit) + key_rows[tab][r] * 8);
		int y = Y0 + 0x5c + r * 0x18;
		if (tab == 2 && (r == 4 || r == 9)) {
			set_colour_bits(g_textColour, 0x3f800000, 0, 0, 0x3f800000);   /* red */
			if (slot[0] != none) {
				text_draw16(X0 + 0xc8, y, key_name[slot[0]]);
				text_draw16(X0 + 0x14a, y, key_name[slot[0]]);
			}
			if (r == 4)
				set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
			continue;
		}
		for (int k = 0; k < 2; k++)
			if (slot[k] != none)
				text_draw8(X0 + (k ? 0x14a : 0xc8), y, key_name[slot[k]]);
	}
#undef X0
#undef Y0
}

/* the fourth tab: its title, labels (MSG(261, "INVERT MOUSE"), and MSG(264, "CROSSHAIRS") lower), the two switches (0x4de1c0 / 0x4de1c4: on
   MSG(119, "ON"), off MSG(118, "OFF")), the sensitivity slider (g_sensitivitySlider, its arrows lit while g_setupPressedClock runs down: g_setupPressed 0 /
   1) and the crosshair g_crosshair: when it changed (from g_lastCrosshair) its texture looked up again (0 .. 7: the path
   "texture/crosshair/crosshair<n>"; others keep the path in g_crosshairName) into g_crosshairTexture, drawn in a box */
static void settings_tab(void)
{
#define X0 g_setupControlLeft
#define Y0 g_setupControlTop
	const u32 *bright = g_setupColourLit;
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x1ae, Y0 + 0x12, (const char *)MSG(205, "MO$[0] USE"));
	for (int r = 0; r < 3; r++)
		text_draw8(X0 + 0x30, Y0 + 0x5c + r * 0x18, (const char *)(MSG(261, "INVERT MOUSE") + r * 0x80));
	text_draw8(X0 + 0x30, Y0 + 0xb0, (const char *)MSG(264, "CROSSHAIRS"));
	for (int k = 0; k < 2; k++)
		text_draw8(X0 + 0xc8, Y0 + 0x5c + k * 0x18, (const char *)(GAME_VAR(int, OBJ(g_setupToggles) + k * 4) == 1 ? MSG(119, "ON") : MSG(118, "OFF")));
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(X0 + 0xc8, Y0 + 0x88, X0 + 0x108, Y0 + 0xa0, 0);   /* the arrows */
	menu_drawSmallButton2(X0 + 0x1d0, Y0 + 0x88, X0 + 0x210, Y0 + 0xa0, 0);
	tex_quad(0.0f, 0.0f, 1.0f, 0.125f, X0 + 0x108, Y0 + 0x88, X0 + 0x1d0, Y0 + 0xa0);   /* the track */
	long double sensitivity = (long double)g_sensitivitySlider;
	float s = f32(fmul_m(sensitivity, k_0_01f_4a9504));
	int x = X0 - ftol(fmul_m(sensitivity, (const float *)ADDR(k_m2f))) + 0x108;
	tex_quad(0.0f, 0.125f, s, 0.25f, X0 + 0x108, Y0 + 0x88, x, Y0 + 0xa0);           /* the bar */
	const float *zero = (const float *)ADDR(k_0f);
	if (g_setupPressedClock > *zero) {
		if (g_setupPressed == 0)
			menu_drawSmallButton1(X0 + 0xc8, Y0 + 0x88, X0 + 0x108, Y0 + 0xa0, 1);
		else if (g_setupPressed == 1)
			menu_drawSmallButton2(X0 + 0x1d0, Y0 + 0x88, X0 + 0x210, Y0 + 0xa0, 1);
	}
	int crosshair = g_crosshair;
	if (crosshair != g_lastCrosshair) {
		if ((u32)crosshair <= 7)
			strcpy(g_crosshairName, (const char *)(STR(0x4b063c, "texture/crosshair/crosshair0") - crosshair * 0x20));
		g_crosshairTexture = tex_getIdByName(g_textures, g_crosshairName, 0, 0, 0, 0, 0, 0, 0);
		g_lastCrosshair = crosshair;
	}
	glEnable(GL_TEXTURE_2D);
	texture = g_crosshairTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0);
	menu_vertex(X0 + 0xc8, Y0 + 0xa0);
	glTexCoord2i(1, 0);
	menu_vertex(X0 + 0xf8, Y0 + 0xa0);
	glTexCoord2i(1, 1);
	menu_vertex(X0 + 0xf8, Y0 + 0xd0);
	glTexCoord2i(0, 1);
	menu_vertex(X0 + 0xc8, Y0 + 0xd0);
	glEnd();
	long double left = fsub_m(fld_m(&g_setupPressedClock), (const float *)ADDR(g_frameTime));
	g_setupPressedClock = f32(left);
	if (!(left >= *zero)) {
		g_setupPressedClock = 0;
		g_setupPressed = -1;
	}
#undef X0
#undef Y0
}

/* 0x425cd0 (the controls page, 0x4dde80 .. 0x4dde8c): the window, cyan lines,
   the column heads (MSG(206, "KEY FUNCTION") ..), the four tab titles (MSG(202, "$[0] MOVE"), 0x80 apart; dim, the current one, g_bindPage, bright
   again). The row under the pointer (setupControl_hitTest: 7 .. 17, kept in g_bindRow; -1 for rows the tab lacks and its fixed
   ones) lit blue, or the row being edited (g_bindWaiting) magenta. The tab's rows; three buttons (MSG(209, "$[0] ACCEPT"), lit from 4
   unless editing); the help line (MSG(212, "Press ENTER or CLICK to change") over a row, MSG(213, "Press NEW-KEY to set |Press ESC to ca...") while editing) and the border. The caller ignores
   the eax it leaves */
void (setup_drawControlsPage)(void)
{
#define X0 g_setupControlLeft
#define Y0 g_setupControlTop
#define X1 g_setupControlRight
#define Y1 (g_setupControlRect[3])
	const u32 *bright = g_setupColourLit, *dim = g_setupColourDim;
	int hovered = setupControl_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x20, Y0 + 0x30, X1 - 0x20, Y0 + 0x30);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_draw8(X0 + 0x30, Y0 + 0x3c, (const char *)MSG(206, "KEY FUNCTION"));
	text_draw8(X0 + 0xc8, Y0 + 0x3c, (const char *)MSG(207, "PRIMARY-KEY"));
	text_draw8(X0 + 0x14a, Y0 + 0x3c, (const char *)MSG(208, "SECONDARY-KEY"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x20, Y0 + 0x50, X1 - 0x20, Y0 + 0x50);
	menu_drawLine(X0 + 0x20, Y1 - 0x38, X1 - 0x20, Y1 - 0x38);
	set_colour_bits(g_textColour, dim[0], dim[1], dim[2], dim[3]);
	for (int k = 0; k < 4; k++)
		text_draw16(X0 + 0x46 + k * 0x78, Y0 + 0x12, (const char *)(MSG(202, "$[0] MOVE") + k * 0x80));
	int editing = g_bindWaiting, tab = g_bindPage;
	int over_row = hovered > 6 && hovered < 18;
	if (over_row && !editing) {
		g_bindRow = hovered - 7;
		if ((tab == 0 && hovered > 16) || (tab == 2 && (hovered > 15 || hovered == 11)) || (tab == 3 && hovered > 8))
			g_bindRow = -1;
		else {
			set_colour_bits(g_rectColour, 0, 0x3f000000, 0x3f800000, 0x3e99999a);   /* 0, 0.5, 1, 0.3 */
			menu_drawRect(X0 + 0x24, Y0 + 0x58 + g_bindRow * 0x18, X1 - 0x24, Y0 + 0x6e + g_bindRow * 0x18, 1);
		}
	} else if (editing) {
		set_colour_bits(g_rectColour, 0x3f800000, 0, 0x3f800000, 0x3e99999a);   /* 1, 0, 1, 0.3 */
		menu_drawRect(X0 + 0x24, Y0 + 0x58 + g_bindRow * 0x18, X1 - 0x24, Y0 + 0x6e + g_bindRow * 0x18, 1);
	}
	if (tab >= 0 && tab <= 2)
		key_tab(tab);
	else if (tab == 3)
		settings_tab();
	for (int k = 0; k < 3; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		int lit = hovered == k + 4 && !editing;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + 0x50 + k * 0x8c;
		menu_drawWideButton(bx, Y1 - 0x30, bx + 0x78, Y1 - 0x10, 1);
		const u32 *c = lit ? bright : dim;
		set_colour_bits(g_textColour, c[0], c[1], c[2], c[3]);
		text_drawBox16(bx, Y1 - 0x28, bx + 0x78, (const char *)(MSG(209, "$[0] ACCEPT") + k * 0x80));
	}
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	if (over_row && !editing)
		text_drawBox16(0, 0x1bc, 0x280, (const char *)MSG(212, "Press ENTER or CLICK to change"));
	if (editing)
		text_drawBox16(0, 0x1bc, 0x280, (const char *)MSG(213, "Press NEW-KEY to set |Press ESC to ca..."));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}
#undef glTexCoord2i

/* ---- the tunnel behind the setup pages ---- */
#define glVertex3f(x, y, z) IMPORT(0x4a9210, void, float, float, float)(x, y, z)

/* a wall of scrolling stripes at x = -29.9 (or 29.9 on the right), h either side of the floor, two quads either
   side of the moving seam z = 40 - 0.4 scroll */
static void stripes(int right, float h)
{
#define SEAM f32(fsubr_m(fmul_m(fld_m(&g_setupStripeScroll), k_0_4f), k_40f))
#define S_LEFT f32(fsubr_m(fmul_m(fld_m(&g_setupStripeScroll), k_0_005f), (const float *)ADDR(k_1f)))   /* 1 - 0.005 scroll */
#define S_RIGHT f32(fmul_m(fld_m(&g_setupStripeScroll), k_0_005f))                                    /* 0.005 scroll */
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

/* the panels' pulse bounced between 0 and 100 (by g_tunnelPulseStep a frame; turn_only: only turned round, not clamped there)
   and the stripes scrolled on (g_menuTunnelSpeed a frame, back to 0 at 200) */
static void tunnel_advance(int turn_only)
{
	const float *frame = (const float *)ADDR(g_frameTime);
	long double pulse = fadd_m(fmul_m(fld_m(frame), (const float *)&g_tunnelPulseStep), &g_tunnelPulse);
	g_tunnelPulse = f32(pulse);
	if (turn_only) {
		if (!(pulse > k_0f))
			g_tunnelPulseStep = 0x3f800000;
		if (pulse >= k_100f)
			g_tunnelPulseStep = 0xbf800000;
	} else if (!(pulse > k_0f)) {
		g_tunnelPulse = 0;
		g_tunnelPulseStep = 0x3f800000;   /* 1 */
	} else if (g_tunnelPulse >= k_100f) {
		g_tunnelPulse = 100.0f;
		g_tunnelPulseStep = 0xbf800000;   /* -1 */
	}
	long double scroll = fadd_m(fmul_m(fld_m((const float *)ADDR(g_menuTunnelSpeed)), frame), &g_setupStripeScroll);
	g_setupStripeScroll = f32(scroll);
	if (scroll >= k_200f)
		g_setupStripeScroll = 0;
}

/* 0x423e50: the tunnel behind the setup pages (3D projection): its alpha (g_setupTunnelAlpha) eases to 0.3 (mode g_setupPage 1)
   or 0.5 (mode 0); then layers of four walls (each under the menu camera, pushed back by g_setupTunnelDepth and turned by
   -35 / 35, the far two the other way): layer 0 the panels (texture g_menuTunnelTexture, dimmed as the pulse rises), layer 1
   the scrolling stripes (the same texture, in the original's colour 1, 1, 10, 0.4), layer 2 nothing, layer 3 a
   strip of g_ctrlMenuTextures a tenth further out, brighter by 0.2. After, the pulse bounces between 0 and 100 (by g_tunnelPulseStep)
   and the stripes scroll on (g_menuTunnelSpeed a frame, back to 0 at 200). The original leaves eax to callers that ignore
   it */
void (setup_drawTunnel)(void)
{
	const float *frame = (const float *)ADDR(g_frameTime);
	gfx_setProjection2D3D(1);
	glEnable(GL_TEXTURE_2D);
	if (g_setupPage == 1)
		g_setupTunnelAlpha = f32(fsubr_m(fmul_m(fmul_m(fsub_m(fld_m(&g_setupTunnelAlpha), k_0_3f), frame),
		                                   (const float *)ADDR(k_tenthsToDegrees)), &g_setupTunnelAlpha));
	else if (g_setupPage == 0)
		g_setupTunnelAlpha = f32(fadd_m(fmul_m(fmul_m(fsub_m(fld_m((const float *)ADDR(k_0_5f)), &g_setupTunnelAlpha), frame),
		                                  (const float *)ADDR(k_tenthsToDegrees)), &g_setupTunnelAlpha));
	glColor4f(1.0f, 1.0f, 1.0f, g_setupTunnelAlpha);
	for (int layer = 0; layer < 4; layer++) {
		/* the strip of the texture: s from s_near (+ ds) to s_far, t from t0 / t1 on by the wall's parity */
		float s0 = 0, ds = 0.5f, t0 = 0, t1 = 0.25f, s_far = 0.5f;
		if (layer == 3)
			s0 = 0.5f, ds = 0, t0 = 0.5f, t1 = 0.75f, s_far = 1.0f;
		int texture;
		if (layer == 0) {
			glColor4f(1.0f, 1.0f, 1.0f, f32(fsubr_m(fmul_m(fld_m(&g_tunnelPulse), k_0_003f), &g_setupTunnelAlpha)));
			texture = g_menuTunnelTexture;
		} else if (layer == 1) {
			glColor4f(1.0f, 1.0f, 10.0f, 0.4f);
			texture = g_menuTunnelTexture;
		} else if (layer == 3) {
			glColor4f(1.0f, 1.0f, 1.0f, f32(fadd_m(fld_m(&g_setupTunnelAlpha), (const float *)ADDR(k_0_2f))));
			texture = GAME_VAR(int, OBJ(g_ctrlMenuTextures) + 12 - layer * 4);
		} else
			continue;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		for (int wall = 0; wall < 4; wall++) {
			int parity = wall % 2, far = wall >= 2;
			gfx_setMenuCamera();
			glTranslatef_bits(0, 0, (*(u32 *)&g_setupTunnelDepth));
			float turn = (g_setupWallTurns)[parity];
			if (far)
				turn = -turn;
			gl_rotateXYZ(0, 0, BITS(turn));
			if (layer == 1) {
				stripes(far, 12.0f);
				continue;
			}
			float x = f32(fmul_m(fld_m(&s0), (const float *)ADDR(k_10f)));    /* 10 s0 */
			float y = f32(fmul_m(fld_m(&s0), k_12f));    /* 12 s0 */
			float top = f32(fsub_m(fld_m(k_12f), &y));   /* 12 - y */
			float bottom = f32(fsub_m(fld_m(&y), k_12f));
			glBegin(GL_QUADS);
			if (layer == 0 && !far) {
				float z0 = f32(fsub_m(fld_m(k_40f), &x)), z1 = f32(fsub_m(fld_m(&x), k_40f));
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-30.0f, top, z0);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(-30.0f, top, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z0);
			} else if (layer == 0) {
				float z0 = f32(fsub_m(fld_m(k_m40f), &x)), z1 = f32(fadd_m(fld_m(&x), k_40f));
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
				float ta = f32(fmul_m((long double)parity, (const float *)ADDR(k_0_25f)));
				float z0 = f32(fsub_m(fld_m(k_40f), &x)), z1 = f32(fsub_m(fld_m(&x), k_40f));
				float wx = f32(fsub_m(fmul_m((long double)layer, (const float *)ADDR(k_tenthsToDegrees)), k_30f));
				float tb = f32(fmul_m(fadd_m(fld_m(&fp), (const float *)ADDR(k_1f)), (const float *)ADDR(k_0_25f)));
				glTexCoord2f(0.0f, ta);
				glVertex3f(wx, top, z0);
				glTexCoord2f(s_far, ta);
				glVertex3f(wx, top, z1);
				glTexCoord2f(s_far, tb);
				glVertex3f(wx, bottom, z1);
				glTexCoord2f(0.0f, tb);
				glVertex3f(wx, bottom, z0);
			} else {
				long double pk = fmul_m((long double)parity, (const float *)ADDR(k_0_25f));
				float ta = f32(pk);
				float u0 = f32(fadd_m(pk, &t0));
				float z0 = f32(fsub_m(fld_m(k_m40f), &x)), z1 = f32(fadd_m(fld_m(&x), k_40f));
				float wx = f32(fsubr_m(fmul_m((long double)layer, (const float *)ADDR(k_tenthsToDegrees)), k_30f));
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
   pushed back 550 and turned by -40 / 0 / 40, the far three the other way): layer 0 the panels (texture g_menuTunnelTexture,
   10 high, dimmed from 0.5 as the pulse rises), layer 1 the stripes (the same texture, in the colour 1, 1, 10,
   0.4), layer 2 nothing (its texture 0x76d47c bound, the walls' turns still made), layer 3 a strip of g_mainMenuTextures a
   tenth further out (alpha 0.7); then the hovered panel's glow (g_panelHovered: g_panelGlow bouncing between 2 and 38 by
   g_panelGlowStep; clamped there when clamp is set) and the pulse and scroll stepped on. The deep ones (deep): the panels
   purple, the stripes red, layer 2 drawn (fully transparent) */
typedef struct {
	u32 depth;             /* how far the walls are pushed back (float bits) */
	u32 textures;          /* layer 2's and 3's textures from here, 4 down a layer: a menu's texture pair + 12 */
	int deep;              /* purple panels, red stripes */
	int layer2;            /* layer 2 drawn (fully transparent) */
	int clamp;
	int turn_only;         /* the pulse only turned round at its ends */
	int walls;             /* 6: three places a side (turned -40 / 0 / 40), 4: two (-35 / 35) */
	const float *height;   /* the panels' half height (10 at k_10f, 12 at k_12f) */
	const float *step;     /* layer 3's strip a place down the texture (0.15625 at k_0_15625f, 0.25 at k_0_25f) */
	float t0, t1;          /* layer 3's strip's top on the far walls, and its height there */
} Tunnel;

/* the hovered menu panel: on, the wall whose layer 2 panel glows (-1: none), in the colour glow (r, g, b; its alpha
   falling as the glow, g_panelGlow, rises); with layer3, layer 3's panels at 0.6 and the hovered one fading from 1;
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
		int texture = layer < 2 ? g_menuTunnelTexture : GAME_VAR(int, t->textures - layer * 4);
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		for (int wall = 0; wall < t->walls; wall++) {
			int place = wall % places, far = wall >= places;
			gfx_setMenuCamera();
			glTranslatef_bits(0, 0, t->depth);
			float turn = turns[place];
			if (far)
				turn = -turn;
			gl_rotateXYZ(0, 0, BITS(turn));
			if (layer == 0) {
				float a = f32(fsubr_m(fmul_m(fld_m(&g_tunnelPulse), k_0_003f), (const float *)ADDR(k_0_5f)));
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
					glColor4f(h->glow[0], h->glow[1], h->glow[2], f32(fsubr_m(fmul_m(fld_m(&g_panelGlow), (const float *)ADDR(k_clockRate)), (const float *)ADDR(k_1f))));
				else
					glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
			} else if (!h->layer3)
				glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
			else if (wall == hovered)
				glColor4f(1.0f, 1.0f, 1.0f, f32(fsubr_m(fmul_m(fld_m(&g_panelGlow), (const float *)ADDR(k_0_01f)), (const float *)ADDR(k_1f))));
			else
				glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
			float x = f32(fmul_m(fld_m(&s0), (const float *)ADDR(k_10f)));   /* 10 s0 */
			float y = f32(fmul_m(fld_m(&s0), t->height));
			float top = f32(fsub_m(fld_m(t->height), &y));
			float bottom = f32(fsub_m(fld_m(&y), t->height));
			glBegin(GL_QUADS);
			if (layer == 0 && !far) {
				float z0 = f32(fsub_m(fld_m(k_40f), &x)), z1 = f32(fsub_m(fld_m(&x), k_40f));
				glTexCoord2f(0.0f, 0.5f);
				glVertex3f(-30.0f, top, z0);
				glTexCoord2f(1.0f, 0.5f);
				glVertex3f(-30.0f, top, z1);
				glTexCoord2f(1.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z1);
				glTexCoord2f(0.0f, 1.0f);
				glVertex3f(-30.0f, bottom, z0);
			} else if (layer == 0) {
				float z0 = f32(fsub_m(fld_m(k_m40f), &x)), z1 = f32(fadd_m(fld_m(&x), k_40f));
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
				float z0 = f32(fsub_m(fld_m(k_40f), &x)), z1 = f32(fsub_m(fld_m(&x), k_40f));
				float wx = f32(fsub_m(fmul_m((long double)layer, (const float *)ADDR(k_tenthsToDegrees)), k_30f));
				float tb = f32(fmul_m(fadd_m(fld_m(&fp), (const float *)ADDR(k_1f)), t->step));
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
				float z0 = f32(fsub_m(fld_m(k_m40f), &x)), z1 = f32(fadd_m(fld_m(&x), k_40f));
				float wx = f32(fsubr_m(fmul_m((long double)layer, (const float *)ADDR(k_tenthsToDegrees)), k_30f));
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
	if (g_panelHovered) {
		long double glow = fadd_m(fmul_m(fld_m((const float *)ADDR(g_frameTime)), &(*(float *)&g_panelGlowStep)), &g_panelGlow);
		g_panelGlow = f32(glow);
		if (!clamp) {
			if (!(glow > k_2f))
				g_panelGlowStep = 0x3f800000;   /* 1 */
			if (glow >= k_38f)
				g_panelGlowStep = 0xbf800000;   /* -1 */
		} else if (!(glow > k_2f)) {
			(*(u32 *)&g_panelGlow) = 0x40000000;   /* 2 */
			g_panelGlowStep = 0x3f800000;
		} else if (g_panelGlow >= k_38f) {
			(*(u32 *)&g_panelGlow) = 0x42180000;   /* 38 */
			g_panelGlowStep = 0xbf800000;
		}
	}
	tunnel_advance(t->turn_only);
}

/* 0x448140: the mission-select screen's tunnel; skirmish_drawTunnel / armc_drawTunnel: the skirmish and ARM CENTER screens' (the glow
   clamped); armc_drawPreviewTunnel: the ARM CENTER's deep one (1650 back, its pulse only turned round); room_drawTunnel: the game room's
   (as deep as g_roomTunnelDepth). The originals leave eax to callers that ignore it */
static const Highlight none = { -1, NULL, 0, 0, 0 };
static const float white[3] = { 1.0f, 1.0f, 1.0f };
#define SIX_WALLS 6, (const float *)ADDR(k_10f), k_0_15625f, 0.46875f, 0.625f
#define FOUR_WALLS 4, k_12f, (const float *)ADDR(k_0_25f), 0.5f, 0.75f
void (missionsel_drawTunnel)(void) { static const Tunnel t = { 0xc4098000, OBJ(g_mainMenuTextures) + 12, 0, 0, 0, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (skirmish_drawTunnel)(void) { static const Tunnel t = { 0xc4098000, OBJ(g_mainMenuTextures) + 12, 0, 0, 1, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (armc_drawTunnel)(void) { static const Tunnel t = { 0xc4098000, OBJ(g_mainMenuTextures) + 12, 0, 0, 1, 0, SIX_WALLS }; menu_tunnel(&t, &none); }
void (armc_drawPreviewTunnel)(void) { static const Tunnel t = { 0xc4ce4000, OBJ(g_ladderMenuTextures) + 12, 1, 1, 0, 1, SIX_WALLS }; menu_tunnel(&t, &none); }
void (room_drawTunnel)(void)
{
	static const float glow[3] = { 0.5f, 0.1f, 1.0f };   /* (no wall glows: the original compares with -1) */
	static const Highlight h = { -1, glow, 0, 0, 0 };
	Tunnel t = { g_roomTunnelDepth, OBJ(g_ladderMenuTextures) + 12, 1, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
}
/* 0x4091b0: the arena lobby's (as deep as g_arenaTunnelDepth; four walls) */
void (arena_drawTunnel)(void)
{
	static const Highlight h = { -1, white, 0, 0, 0 };
	Tunnel t = { g_arenaTunnelDepth, OBJ(g_arenaMenuTextures) + 12, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
}

/* a menu panel's caption (0x80 apart from captions) in white along the bottom */
static void caption(u32 captions, int on)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(0, 0x1bc, 0x280, (const char *)(RELOC(captions) + on * 0x80));
}

/* the menu panel under the pointer: the first of count outlines (menu_pointInPolygon's, 0x2c bytes apart from outlines)
   holding it, none (-1) while locked; g_panelHovered tells whether there is one, and a new one restarts the glow (g_lastPanel
   the last, g_panelGlow 40, g_panelGlowStep -1) */
static int hovered_panel(u32 outlines, int count, int locked)
{
	int on = -1;
	for (int k = 0; k < count && !locked; k++)
		if (point_in_outline(g_mouseX, g_mouseY, *(const Outline *)(RELOC(outlines) + k * 0x2c)) == 1) {
			on = k;
			break;
		}
	g_panelHovered = on != -1;
	if (on != -1 && g_lastPanel != on) {
		g_lastPanel = on;
		(*(u32 *)&g_panelGlow) = 0x42200000;   /* 40 */
		g_panelGlowStep = 0xbf800000;   /* -1 */
	}
	return on;
}

/* 0x437e00: the game room's menu: the panel under the pointer (six, g_roomOutlines; none while g_roomDialogOpen), the room's
   tunnel with that panel glowing, and with the room camera arrived (g_roomCameraMode 2) its caption (MSG(91, "SETUP ID|Hotkey is $[5] P"), 0x80 apart) at the bottom. The
   original leaves eax to callers that ignore it */
void (room_drawMenu)(void)
{
	static const float glow[3] = { 1.0f, 0.1f, 1.0f };
	Highlight h = { hovered_panel(OBJ(g_roomOutlines), 6, g_roomDialogOpen), glow, 0, 0, 0 };
	Tunnel t = { g_roomTunnelDepth, OBJ(g_ladderMenuTextures) + 12, 1, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && g_roomCameraMode == 2)
		caption(MSG(91, "SETUP ID|Hotkey is $[5] P"), h.on);
}

/* 0x408680: the arena lobby's top menu: the panel under the pointer (four, g_lobbyTopOutlines; none while g_lobbyPanelsOff), the
   arena tunnel (as deep as g_arenaTunnelDepth) with that panel lit, and in mode 2 (g_arenaCameraMode) its caption (MSG(86, "SETUP PLAYER FOR THE MULTIPLAY|Hotkey...")) unless
   g_menuCameraMove. The original leaves eax to callers that ignore it */
void (lobbyTop_drawMenu)(void)
{
	Highlight h = { hovered_panel(OBJ(g_lobbyTopOutlines), 4, g_lobbyPanelsOff), white, 1, 0, 0 };
	Tunnel t = { g_arenaTunnelDepth, OBJ(g_arenaMenuTextures) + 12, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && g_arenaCameraMode == 2 && !g_menuCameraMove)
		caption(MSG(86, "SETUP PLAYER FOR THE MULTIPLAY|Hotkey..."), h.on);
}

/* 0x423330: the setup screen's menu: the same over the setup tunnel's textures (0x5b197c / g_ctrlMenuTextures, as deep as
   g_setupTunnelDepth): four panels (g_setupTopOutlines; none while g_setupPanelMoving), the caption (MSG(81, "SETUP SOUND SYSTEM|Hotkey is $[5] S")) in mode 2 (g_setupPage). The original
   leaves eax to callers that ignore it */
void (setup_drawMenu)(void)
{
	Highlight h = { hovered_panel(OBJ(g_setupTopOutlines), 4, g_setupPanelMoving), white, 1, 0, 0 };
	Tunnel t = { (*(u32 *)&g_setupTunnelDepth), OBJ(g_ctrlMenuTextures) + 12, 0, 1, 1, 0, FOUR_WALLS };
	menu_tunnel(&t, &h);
	if (h.on != -1 && g_setupPage == 2 && !g_menuCameraMove)
		caption(MSG(81, "SETUP SOUND SYSTEM|Hotkey is $[5] S"), h.on);
}
/* 0x442050: the main menu: the panel under the pointer (six, g_mainMenuOutlines; none while the tunnel flies in, g_tunnelFlyingIn, or
   after one is picked, g_mainMenuPicked: then the idle clock g_menuIdleTime and the hint's fade restart); with none the idle
   clock runs on. The tunnel flies in (g_mainMenuDepth from deep to -550, faster the deeper; g_mainMenuFrames counts the frames)
   and is drawn with the panel lit (the stripes plain); then the panel's caption (MSG(71, "SKIRMISH PLAY|Hotkey is $[5] K")), or once idle for 120
   the hint 0x4b2a98 fading in and out (g_menuHintClock by g_menuHintStep), unless g_menuCameraMove. The original leaves eax to callers
   that ignore it */
void (menu_mainMenu)(void)
{
#define g_depth (*(float *)&g_mainMenuDepth)
#define g_idle (*(float *)&g_menuIdleTime)
#define g_hint (*(float *)&g_menuHintClock)
#define g_hintStep g_menuHintStep
	const float *frame = (const float *)ADDR(g_frameTime);
	int on = -1;
	for (int k = 0; k < 6 && !g_tunnelFlyingIn; k++)
		if (point_in_outline(g_mouseX, g_mouseY, *(const Outline *)(OBJ(g_mainMenuOutlines) + k * 0x2c)) == 1) {
			on = k;
			break;
		}
	if (on == -1) {
		g_idle = f32(fadd_m(fld_m(frame), &g_idle));
		g_panelHovered = 0;
	} else {
		g_panelHovered = !g_mainMenuPicked;
		g_idle = 0;
		g_hint = 0;
		g_hintStep = 0x3d4ccccd;   /* 0.05 */
		if (g_mainMenuPicked)
			on = -1;
		else if (g_lastPanel != on) {
			g_lastPanel = on;
			(*(u32 *)&g_panelGlow) = 0x42200000;   /* 40 */
			g_panelGlowStep = 0xbf800000;   /* -1 */
		}
	}
	if (g_tunnelFlyingIn) {   /* (no calls: before the tunnel's projection and texturing as in the original) */
		long double step = fmul_m(fmul_m(fadd_m(fld_m(&g_depth), (const float *)ADDR(k_550f)), frame), (const float *)ADDR(k_tenthsToDegrees));
		g_mainMenuFrames++;
		if (g_depth > k_m549_9f)
			g_depth = f32(fld_m(&g_depth) - step);
		else {
			g_tunnelFlyingIn = 0;
			(*(u32 *)&g_depth) = 0xc4098000;   /* -550 */
		}
	}
	Highlight h = { on, white, 1, 1, 1 };
	Tunnel t = { (*(u32 *)&g_depth), OBJ(g_mainMenuTextures) + 12, 0, 1, 1, 0, SIX_WALLS };
	menu_tunnel(&t, &h);
	if (on != -1) {
		if (!g_menuCameraMove)
			caption(MSG(71, "SKIRMISH PLAY|Hotkey is $[5] K"), on);
	} else if (!g_menuCameraMove && !g_mainMenuPicked && g_idle > k_120f) {
		long double hint = fadd_m(fmul_m(fld_m((const float *)&g_hintStep), frame), &g_hint);
		g_hint = f32(hint);
		if (hint > k_3f) {
			g_hint = 1.0f;
			g_hintStep = 0xbd4ccccd;   /* -0.05 */
		} else if (!(g_hint >= k_0f)) {
			g_hint = 0;
			g_hintStep = 0x3d4ccccd;
			g_idle = 0;
		}
		gfx_setProjection2D3D(2);
		glLoadIdentity();
		float alpha = g_hint > k_1f ? 1.0f : g_hint;
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, BITS(alpha));
		text_drawBox16(0, 0x1d0, 0x280, (const char *)STR(0x4b2a98, "AUTOPLAY-F1"));
	}
	glDisable(GL_TEXTURE_2D);
#undef g_depth
#undef g_idle
#undef g_hint
#undef g_hintStep
}
#undef SIX_WALLS
#undef FOUR_WALLS
#undef g_setupStripeScroll
#undef g_tunnelPulse

/* 0x4277c0: the setup panel eased in (g_setupPanelMoving while it moves): its position (g_setupPanelPos) moves the rest of the
   way to k_setupPanelTarget times g_frameTime x k_tenthsToDegrees; the distance left (g_setupTunnelDepth) runs down by the same step, and once it
   is no longer above the double at k_setupPanelEnd the motion stops and the distance is set to -1650 */
void (setup_easePanel)(void)
{
	typedef long double X;
	if (!g_setupPanelMoving)
		return;
	X d = ((X)k_setupPanelTarget - g_setupPanelPos) * g_frameTime * k_tenthsToDegrees;
	g_setupPanelPos = (float)((X)g_setupPanelPos + d);
	if (!((X)g_setupTunnelDepth > (X)k_setupPanelEnd)) {
		g_setupPanelMoving = 0;
		(*(u32 *)&g_setupTunnelDepth) = 0xc4ce4000;
		return;
	}
	g_setupTunnelDepth = (float)((X)g_setupTunnelDepth - d);
}
