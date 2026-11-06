/* profile_dialogs.c: the profile screen's dialogs: typing a new pilot's name, and the two yes / no questions. */
#include "../game.h"
#include <string.h>
#include "portrait.h"

#define g_questionX g_highlightX   /* where the two-button question is drawn */
#define g_questionY g_highlightY

/* 0x44b600: the new pilot's name (16 characters), typed into the panel at g_newNameDialogTop */
void (profile_typeNewName)(void)
{
	input_releaseKeyboard();
	g_textFieldOpen = 1;
	menu_clearInputBuffer(0x10);
	g_chatCaretX = g_newNameDialogLeft + 0x24;
	g_chatCaretY = g_newNameDialogTop + 0x38;
	g_menuKeyGuard = 5.0f;
	g_profilePage = 2;
	g_dialogOpen = 1;
	g_profileMessage = 0;
	chat_createEdit(0x10);
}

/* a two-button question (dialog kind) placed over the panel whose corner is (x, y) */
static void ask(int kind, int x, int y)
{
	sound_playMenu(0);
	g_dialogOpen = 1;
	g_highlightShown = 1;
	g_profilePage = kind;
	g_cursorBlink = 0.0f;
	g_dialogChoice = 0;
	g_highlightSize = 20.0f;
	g_highlightAlpha = 0.2f;
	g_questionX = x + 0x9c;
	g_questionY = y + 0x4a;
}

/* 0x44b670, 0x44b6e0: question 3 over the pilot panel, question 5 (log out) over its own panel */
void (profile_askDelete)(void) { ask(3, g_profileDialogX, g_profileDialogY); }
void (profile_askLogOut)(void) { ask(5, g_logOutDialogX, g_logOutDialogY); }

/* 0x44f810: the profile screen: only its frame while a dialog is up, else the pilot preview (when shown) and the
   screen */
void (profile_drawScreen)(void)
{
	if (g_dialogOpen != 0) {
		menu_drawFrame(g_pilotSelectLeft, g_pilotSelectTop, g_pilotSelectRight, g_pilotSelectBottom);
		return;
	}
	if (g_statBarsStale != 0)
		pilotSelect_loadStats();
	profile_drawPilotSelect();
}

/* 0x44dc60: the profile message window (the panel g_newNameDialogLeft, 0x9f8ea8 .. 0x9f8f20, g_newNameDialogBottom): its frame (texture
   g_dialogFrameTexture), the message MSG(126, "NAME ALREADY REGISTRED") across the top in the panel's colour (g_profileColour), the OK button (texture
   g_buttonTexture, 0x60 wide, centred) with its label MSG(115, "$[0] O K"), and the border. Returns the border call's eax */
u32 (profile_drawMessageWindow)(void)
{
#define X0 g_newNameDialogLeft
#define Y0 g_newNameDialogTop
#define X1 g_newNameDialogRight
#define Y1 g_newNameDialogBottom
	const u32 *colour = g_profileColour;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTextureFlipped(X0, Y0, X1, Y1, g_dialogFrameTexture);
	int button = X0 + (X1 - X0) / 2 - 0x32;
	set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(X0, Y0 + 0x20, X1, (const char *)MSG(126, "NAME ALREADY REGISTRED"));
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawWideButton(button, Y0 + 0x50, button + 0x60, Y0 + 0x70, 1);
	set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(button, Y0 + 0x58, button + 0x60, (const char *)MSG(115, "$[0] O K"));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawTopRightOrnament, 0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* ---- a two-button profile dialog: the window (x0, y0, x1, y1 kept in four globals) with its frame (texture
   g_dialogFrameTexture), the question across the top in the panel colour (g_profileColour), two buttons 0x78 apart (texture g_buttonTexture,
   labels 0x80 bytes apart from MSG(115, "$[0] O K")), the hovered one (by hit) bright in the panel colour, the other dim in
   g_profileDim, and the border. Returns the border call's eax ---- */
typedef struct { u32 x0, y0, x1, y1, hit, question; } TwoButtons;

static u32 two_buttons(const TwoButtons *d)
{
#define X0 GAME_VAR(int, d->x0)
#define Y0 GAME_VAR(int, d->y0)
#define X1 GAME_VAR(int, d->x1)
#define Y1 GAME_VAR(int, d->y1)
	const u32 *panel = g_profileColour, *dim = g_profileDim;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	int hovered = GAME_CDECL(d->hit, int, int, int)(g_mouseX, g_mouseY);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTextureFlipped(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, panel[0], panel[1], panel[2], panel[3]);
	text_drawBox16(X0, Y0 + 0x10, X1, (const char *)d->question);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		const u32 *colour = k == hovered ? panel : dim;
		glColor4f(1.0f, 1.0f, 1.0f, k == hovered ? 1.0f : 0.4f);
		menu_drawWideButton(X0 + k * 0x78 + 0x6e, Y0 + 0x3c, X0 + k * 0x78 + 0xce, Y0 + 0x5c, 1);
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(X0 + k * 0x78 + 0x6e, Y0 + 0x44, X0 + k * 0x78 + 0xce, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawTopRightOrnament, 0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x44e180: the delete question (deleteDialog_hitTest, question MSG(127, "ARE YOU SURE?")); profile_drawLogOutQuestion: the log-out question (logOutDialog_hitTest,
   question MSG(128, "ARE YOU SURE?")) */
u32 (profile_drawDeleteQuestion)(void)
{
	static const TwoButtons d = { ADDR(g_profileDialogX), ADDR(g_profileDialogY), ADDR(g_profileDialogRight), ADDR(g_profileDialogBottom), FN_ADDR(deleteDialog_hitTest, 0x44b320), MSG(127, "ARE YOU SURE?") };
	return two_buttons(&d);
}
u32 (profile_drawLogOutQuestion)(void)
{
	static const TwoButtons d = { ADDR(g_logOutDialogX), ADDR(g_logOutDialogY), ADDR(g_logOutDialogRight), ADDR(g_logOutDialogBottom), FN_ADDR(logOutDialog_hitTest, 0x44b360), MSG(128, "ARE YOU SURE?") };
	return two_buttons(&d);
}

/* 0x44de00: the new-profile dialog (g_newNameDialogLeft, 0x9f8ea8 .. 0x9f8f20, g_newNameDialogBottom): the frame, the title MSG(125, "REGISTRY PROFILE"), the
   name field, the two buttons side by side (the hovered one, by newNameDialog_hitTest, bright; OK dimmed while no name has
   been typed, g_chatLine) and the border. Returns the border call's eax */
u32 (profile_drawNewDialog)(void)
{
#define X0 g_newNameDialogLeft
#define Y0 g_newNameDialogTop
#define X1 g_newNameDialogRight
#define Y1 g_newNameDialogBottom
	const u32 *panel = g_profileColour, *dim = g_profileDim;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	int hovered = newNameDialog_hitTest(g_mouseX, g_mouseY);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTextureFlipped(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_rectColour, 0x3f4ccccd, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000);
	set_colour_bits(g_textColour, panel[0], panel[1], panel[2], panel[3]);
	text_draw16(X0 + 0x14, Y0 + 0x10, (const char *)MSG(125, "REGISTRY PROFILE"));
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	profile_drawButton(X0 + 0x14, Y0 + 0x30, X1 - 0x14, Y0 + 0x50, 1);
	for (int k = 0; k < 2; k++) {
		int x = X0 + k * 0x78;
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		const u32 *colour = k == hovered ? panel : dim;
		glColor4f(1.0f, 1.0f, 1.0f, k == hovered ? 1.0f : 0.4f);
		menu_drawWideButton(x + 0xa0, Y0 + 0x5a, x + 0x100, Y0 + 0x7a, 1);
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		if (strlen(g_chatLine) == 0 && k == 0) {
			glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
			menu_drawWideButton(X0 + 0xa0, Y0 + 0x5a, X0 + 0x100, Y0 + 0x7a, 1);
			set_colour_bits(g_textColour, dim[0], dim[1], dim[2], dim[3]);
		}
		text_drawBox16(x + 0xa0, Y0 + 0x62, x + 0x100, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_FN(menu_drawTopRightOrnament, 0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x44d720: the profile management window (0x9f8e48 .. 0x9f8ea4): the window (brighter while the pilot list has the focus,
   page g_profilePage = 1), the list's and the details' frames, the title MSG(120, "PROFILE MANAGEMENT"), four buttons (MSG(121, "$[0] NEW"), 0x80 apart:
   on the list page the one under the pointer, by profilePage_hitTest, lit; on page k + 2 button k lit, in the panel
   colour less 0.2 in green and blue), the pilot list (profileList_drawNames), its scroll arrows (5 / 6 under the
   pointer), the details (profile_drawChosenPilot), the border and the version string 0x4b0384 right-aligned at the bottom.
   The original leaves eax to callers that ignore it */
void (profile_drawManagementWindow)(void)
{
#define X0 g_profilePageLeft
#define Y0 g_profilePageTop
#define X1 g_profilePageRight
#define Y1 g_profilePageBottom
#define PAGE g_profilePage
	float *panel = (float *)OBJ(g_profileColour);
	const u32 *bright = g_profileColour, *dim = g_profileDim;
	int hovered = profilePage_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	if (PAGE == 1) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0, 0x3f000000, 0x3f800000);   /* 0.2, 0, 0.5, 1 */
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	} else {
		set_colour_bits(g_rectColour, 0x3dcccccd, 0, 0x3e99999a, 0x3f000000);   /* 0.1, 0, 0.3, 0.5 */
		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	}
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	if (PAGE == 1)
		set_colour_bits(g_rectColour, 0x3f4ccccd, 0x3f4ccccd, 0x3f4ccccd, 0x3f4ccccd);
	else
		set_colour_bits(g_rectColour, 0x3f000000, 0x3f000000, 0x3f000000, 0x3f000000);
	menu_drawRect(X0 + 0x20, Y0 + 0x20, X0 + 0x100, Y1 - 0x40, 0);
	menu_drawRect(X0 + 0x108, Y0 + 0x20, X1 - 0x20, Y1 - 0x40, 0);
	const u32 *title = PAGE == 1 ? bright : dim;
	set_colour_bits(g_textColour, title[0], title[1], title[2], title[3]);
	text_draw16(X0 + 0x20, Y0 + 0xa, (const char *)MSG(120, "PROFILE MANAGEMENT"));
	for (int k = 0; k < 4; k++) {
		int x = X0 + k * 0x72;
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		if (PAGE == 1) {
			if (k == hovered) {
				glColor4f(1.0f, 0.8f, 1.0f, 1.0f);
				set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
			} else {
				glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
				set_colour_bits(g_textColour, dim[0], dim[1], dim[2], dim[3]);
			}
		} else if (PAGE == k + 2) {
			glColor4f(0.8f, 0.8f, 0.8f, 1.0f);
			float b = f32(fsub_m(fld_m(&panel[2]), (const float *)ADDR(k_0_2f)));
			float g = f32(fsub_m(fld_m(&panel[1]), (const float *)ADDR(k_0_2f)));
			set_colour_bits(g_textColour, bright[0], BITS(g), BITS(b), bright[3]);
		} else {
			glColor4f(0.8f, 0.8f, 0.8f, 0.3f);
			set_colour_bits(g_textColour, dim[0], dim[1], dim[2], dim[3]);
		}
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		menu_drawWideButton(x + 0x28, Y1 - 0x30, x + 0x88, Y1 - 0x10, 1);
		text_drawBox16(x + 0x28, Y1 - 0x28, x + 0x88, (const char *)(MSG(121, "$[0] NEW") + k * 0x80));
	}
	profileList_drawNames();   /* the pilot list */
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton3(X0 + 0xe0, Y0 + 0x50, X0 + 0xf8, Y0 + 0x80, hovered == 5);
	menu_drawSmallButton4(X0 + 0xe0, Y0 + 0xb4, X0 + 0xf8, Y0 + 0xe4, hovered != 5 && hovered == 6);
	glDisable(GL_TEXTURE_2D);
	profile_drawChosenPilot();   /* the details */
	if (PAGE == 1)
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	else
		glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
	const char *version = (const char *)STR(0x4b0384, "Axis v1.03");
	text_draw5((0x69 - (int)strlen(version)) * 6, 0x1d6, version);
#undef X0
#undef Y0
#undef X1
#undef Y1
#undef PAGE
}

/* ---- a pilot's details (g_characterProfiles: name, corporation, sex, age, nine stats) ---- */
#define PILOT(n) (&g_characterProfiles[n])

/* the nine stats, right-aligned (by their digits and sign) from x, step apart from y, each with 0x4b3e2c */
static void pilot_stats(int pilot, int x, int y, int step)
{
	char text[20];
	for (int k = 0; k < 9; k++) {
		itoa(PILOT(pilot)->stats[k], text, 10);
		int pad;
		if (text[0] != '-')
			pad = strlen(text) < 2 ? 0x10 : 8;
		else
			pad = strlen(text) < 3 ? 8 : 0;
		strcat(text, (const char *)STR(0x4b3e2c, "%"));
		text_draw8(x + pad, y + k * step, text);
	}
}

/* the nine stat bars (g_statBars, easing a tenth a frame to g_statBarTargets) from x, 5 high and step apart from y, as long as
   the bar by scale (negative: to the right), in grey; each the button texture's strip 0.05 .. 0.95 (by length) */
static void stat_bars(int x, int y, int step, const float *scale, float grey)
{
	const float *frame = (const float *)ADDR(g_frameTime);
	float *bar = g_statBars;
	const float *target = g_statBarTargets;
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 9; k++) {
		glBegin(GL_QUADS);
		glColor4f(grey, grey, grey, 1.0f);
		long double eased = fadd_m(fmul_m(fmul_m(FSUB(target[k], bar[k]), frame), (const float *)ADDR(k_tenthsToDegrees)), &bar[k]);
		bar[k] = f32(eased);
		long double end = fadd_m(fmul_m(eased, (const float *)ADDR(k_0_01f)), k_0_05f);
		float s = f32(end);
		if (end > k_0_95f)
			s = 0.95f;
		glTexCoord2f(0.05f, 0.1875f);
		menu_vertex(x, y + k * step);
		glTexCoord2f(s, 0.1875f);
		menu_vertex(x - ftol(fmul_m(fld_m(&bar[k]), scale)), y + k * step);
		glTexCoord2f(s, 0.1875f);
		menu_vertex(x - ftol(fmul_m(fld_m(&bar[k]), scale)), y + k * step + 5);
		glTexCoord2f(0.05f, 0.1875f);
		menu_vertex(x, y + k * step + 5);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
}

/* 0x44e640: the pilot-select dialog (g_pilotSelectLeft, 0x9f8c50 .. 0x9f6830, g_pilotSelectBottom): the window, its title MSG(531, "CHARACTER SELECT") and
   rule; the portraits (texture g_characterTexture) and over them the chosen pilot's (g_pilotSelectCursor: cell % 3, / 3 of 86 texels)
   growing by 2 a reveal step (g_profileReveal, up to 8, one a 1.0 of g_profileRevealClock) under a pulsing frame (g_fontAsciiLarge; its alpha
   by g_profileFrameAlpha, which bounces between 2 and 38 at g_profileFrameStep a frame); the details: 13 labels (MSG(532, "NAME :")), the pilot's
   name, corporation, sex (MSG(545, "RESERVED") + it: MALE / FEMALE), age and nine stats (right-aligned, with 0x4b3e2c) beside their bars (g_statBars,
   easing to g_statBarTargets); two buttons (MSG(115, "$[0] O K"); 9 / 10 under the pointer by pilotSelect_hitTest, bright) and the border.
   The original leaves eax to callers that ignore it */
void (profile_drawPilotSelect)(void)
{
#define X0 g_pilotSelectLeft
#define Y0 g_pilotSelectTop
#define X1 g_pilotSelectRight
#define Y1 g_pilotSelectBottom
#define K(addr) ((const float *)RELOC(addr))
#define g_pilot g_pilotSelectCursor
#define g_revealClock (*(float *)&g_profileRevealClock)
	const u32 *panel = g_profileColour, *dim = g_profileDim;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	int hovered = pilotSelect_hitTest(g_mouseX, g_mouseY);   /* pilotSelect_hitTest */
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, panel[0], panel[1], panel[2], panel[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(531, "CHARACTER SELECT"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	/* the portraits */
	glEnable(GL_TEXTURE_2D);
	int texture = g_characterTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	menu_vertex(X0 + 0x20, Y0 + 0x4c);
	glTexCoord2d(1.0, 0.0);
	menu_vertex(X0 + 0x120, Y0 + 0x4c);
	glTexCoord2d(1.0, 1.0);
	menu_vertex(X0 + 0x120, Y0 + 0x14c);
	glTexCoord2d(0.0, 1.0);
	menu_vertex(X0 + 0x20, Y0 + 0x14c);
	glEnd();
	/* the chosen one's cell, grown by the reveal: corners at (x, y) less the reveal and 2 x reveal + 85 further */
	float col = (float)(g_pilot % 3), row = (float)(g_pilot / 3);
	long double reveal = (long double)g_profileReveal;
	float x = f32(fmul_m(col, k_86f) - reveal), y = f32(fmul_m(row, k_86f) - reveal);
	glBegin(GL_QUADS);
	long double rt = fmul_m(row, k_86f), ct = fmul_m(col, k_86f);
	float row_t = f32(rt), col_t = f32(ct);
	float t0 = f32(fmul_m(rt, &k_0_00390625f)), s0 = f32(fmul_m(ct, &k_0_00390625f));
	glTexCoord2f(s0, t0);
	int y0 = ftol(fadd_m((long double)(Y0 + 0x4c), &y));
	menu_vertex(ftol(fadd_m((long double)(X0 + 0x20), &x)), y0);
	float s1 = f32(fmul_m(fadd_m(col_t, k_85f), &k_0_00390625f));
	glTexCoord2f(s1, t0);
	y0 = ftol(fadd_m((long double)(Y0 + 0x4c), &y));
	menu_vertex(ftol(fadd_m(fadd_m((long double)(g_profileReveal * 2) + (long double)(X0 + 0x20), &x), k_85f)), y0);
	float t1 = f32(fmul_m(fadd_m(row_t, k_85f), &k_0_00390625f));
	glTexCoord2f(s1, t1);
	int y1 = ftol(fadd_m(fadd_m((long double)(Y0 + 0x4c) + (long double)(g_profileReveal * 2), &y), k_85f));
	menu_vertex(ftol(fadd_m(fadd_m((long double)(X0 + 0x20) + (long double)(g_profileReveal * 2), &x), k_85f)), y1);
	glTexCoord2f(s0, t1);
	y1 = ftol(fadd_m(fadd_m((long double)(g_profileReveal * 2) + (long double)(Y0 + 0x4c), &y), k_85f));
	menu_vertex(ftol(fadd_m((long double)(X0 + 0x20), &x)), y1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	/* its pulsing frame: 5 outside the cell's corner, 90 beyond it */
	glEnable(GL_TEXTURE_2D);
	texture = g_fontAsciiLarge;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, f32(fsubr_m(FMUL(g_profileFrameAlpha, k_clockRate), &k_1f)));
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.5f);
	y0 = ftol(fsub_m(fadd_m((long double)(Y0 + 0x4c), &y), &k_5f));
	menu_vertex(ftol(fsub_m(fadd_m((long double)(X0 + 0x20), &x), &k_5f)), y0);
	glTexCoord2f(0.5f, 0.5f);
	y0 = ftol(fsub_m(fadd_m((long double)(Y0 + 0x4c), &y), &k_5f));
	menu_vertex(ftol(fadd_m(fadd_m((long double)(g_profileReveal * 2) + (long double)(X0 + 0x20), &x), &k_90f)), y0);
	glTexCoord2f(0.5f, 1.0f);
	y1 = ftol(fadd_m(fadd_m((long double)(Y0 + 0x4c) + (long double)(g_profileReveal * 2), &y), &k_90f));
	menu_vertex(ftol(fadd_m(fadd_m((long double)(X0 + 0x20) + (long double)(g_profileReveal * 2), &x), &k_90f)), y1);
	glTexCoord2f(0.0f, 1.0f);
	y1 = ftol(fadd_m(fadd_m((long double)(g_profileReveal * 2) + (long double)(Y0 + 0x4c), &y), &k_90f));
	menu_vertex(ftol(fsub_m(fadd_m((long double)(X0 + 0x20), &x), &k_5f)), y1);
	glEnd();
	long double pulse = fadd_m(fmul_m(fld_m((&g_frameTime)), (const float *)&g_profileFrameStep), &g_profileFrameAlpha);
	g_profileFrameAlpha = f32(pulse);
	if (!(pulse > *&k_2f))
		g_profileFrameStep = 0x3f800000;   /* 1 */
	if (pulse >= *&k_38f)
		g_profileFrameStep = 0xbf800000;   /* -1 */
	if (g_profileReveal < 8) {
		long double clock = fadd_m(fld_m(&g_revealClock), (&g_frameTime));
		g_revealClock = f32(clock);
		if (clock > *&k_1f) {
			g_revealClock = 0;
			g_profileReveal++;
		}
	}
	/* the details */
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(X0 + 0x130, Y0 + 0x40, X0 + 0x22a, Y0 + 0x158, 0);
	for (int k = 0; k < 13; k++)
		text_draw8(X0 + 0x138, Y0 + k * 0x15 + 0x48, (const char *)(MSG(532, "NAME :") + k * 0x80));
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
text_draw8(X0 + 0x184, Y0 + 0x48, PILOT(g_pilot)->name);
	text_draw8(X0 + 0x184, Y0 + 0x5d, PILOT(g_pilot)->corporation);
	text_draw8(X0 + 0x184, Y0 + 0x72, (const char *)(MSG(545, "RESERVED") + PILOT(g_pilot)->sex * 0x80));
	char text[20];
	itoa(PILOT(g_pilot)->age, text, 10);
	text_draw8(X0 + 0x184, Y0 + 0x87, text);
	pilot_stats(g_pilot, X0 + 0x192, Y0 + 0x9c, 0x15);
	stat_bars(X0 + 0x1bc, Y0 + 0x9f, 0x15, &k_m1f_4a95f4, 1.0f);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		int lit = hovered == k + 9;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int bx = X0 + k * 0xa0;
		menu_drawWideButton(bx + 0xaa, Y1 - 0x40, bx + 0x122, Y1 - 0x20, 1);
		const u32 *colour = lit ? panel : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(bx + 0xaa, Y1 - 0x38, bx + 0x122, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef g_revealClock
#undef g_pilot
#undef K
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x44cf70: the chosen profile's pilot (0x9f688c, 0x48 bytes a profile, of g_pilotChosen, into g_chosenPilot) beside the
   profile list, when there are profiles (g_profileCount): 13 labels (MSG(532, "NAME :")), the portrait in a yellow frame, the name,
   corporation and sex (the original places these two by the panel's x, g_profilePageLeft, not its y), the age, the nine
   stats and their bars; all at half brightness while the list does not have the focus (g_profilePage) */
void (profile_drawChosenPilot)(void)
{
#define X0 g_profilePageLeft
#define Y0 g_profilePageTop
	if (g_profileCount <= 0)
		return;
	int pilot = *(const int *)((OBJ(g_profileList) + 0x40) + g_pilotChosen * 0x48);
	g_chosenPilot = pilot;
	int focus = g_profilePage == 1;
	float *panel = (float *)OBJ(g_profileColour);
	if (focus)
		set_colour_bits(g_textColour, BITS(panel[0]), BITS(panel[1]), BITS(panel[2]), BITS(panel[3]));
	else {
		const float *half = (const float *)ADDR(k_0_5f);
		float b = f32(fmul_m(fld_m(&panel[2]), half)), g = f32(fmul_m(fld_m(&panel[1]), half));
		float r = f32(fmul_m(fld_m(&panel[0]), half));
		set_colour_bits(g_textColour, BITS(r), BITS(g), BITS(b), BITS(panel[3]));
	}
	for (int k = 0; k < 13; k++)
		text_draw8(X0 + 0x10c, Y0 + k * 0x14 + 0x24, (const char *)(MSG(532, "NAME :") + k * 0x80));
	glEnable(GL_TEXTURE_2D);
	int texture = g_characterTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	float grey = focus ? 1.0f : 0.5f;
	glColor4f(grey, grey, grey, 1.0f);
	portrait(g_chosenPilot, X0 + 0x1a4, Y0 + 0x24, 0x40);
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3e99999a);   /* 1, 1, 0, 0.3 */
	menu_drawRect(X0 + 0x1a4, Y0 + 0x24, X0 + 0x1e4, Y0 + 0x64, 0);
	u32 text_grey = focus ? 0x3f800000 : 0x3f000000;
	set_colour_bits(g_textColour, text_grey, text_grey, text_grey, 0x3f800000);
	text_draw8(X0 + 0x14e, Y0 + 0x24, PILOT(g_chosenPilot)->name);
	text_draw8(X0 + 0x14e, X0 + 0x38, PILOT(g_chosenPilot)->corporation);
	text_draw8(X0 + 0x14e, X0 + 0x4c, (const char *)(MSG(545, "RESERVED") + PILOT(g_chosenPilot)->sex * 0x80));
	char text[20];
	itoa(PILOT(g_chosenPilot)->age, text, 10);
	text_draw8(X0 + 0x14e, Y0 + 0x60, text);
	pilot_stats(g_chosenPilot, X0 + 0x166, Y0 + 0x74, 0x14);
	stat_bars(X0 + 0x18a, Y0 + 0x78, 0x14, k_m0_9f, grey);
#undef X0
#undef Y0
}
