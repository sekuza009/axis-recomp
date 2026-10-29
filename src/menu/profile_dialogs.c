/* profile_dialogs.c: the profile screen's dialogs: typing a new pilot's name, and the two yes / no questions. */
#include "../game.h"

#define g_profileDialog GAME_VAR(int, 0x9f8f10)       /* (by use) the open dialog: 2 the name, 3 and 5 the questions */
#define g_questionX GAME_VAR(int, 0x67ef34)           /* where the two-button question is drawn */
#define g_questionY GAME_VAR(int, 0x67fb38)

/* 0x44b600: the new pilot's name (16 characters), typed into the panel at 0x9f8ea8 */
void (profile_44b600)(void)
{
	input_releaseKeyboard();
	g_paused = 1;
	menu_clearInputBuffer(0x10);
	g_chatCaretX = GAME_VAR(int, 0x9f8eac) + 0x24;
	g_chatCaretY = GAME_VAR(int, 0x9f8ea8) + 0x38;
	g_menuFade = 5.0f;
	g_profileDialog = 2;
	g_dialogOpen = 1;
	GAME_VAR(int, 0x9f8f34) = 0;
	chat_createEdit(0x10);
}

/* a two-button question (dialog kind) placed over the panel whose corner is (x, y) */
static void ask(int kind, int x, int y)
{
	sound_playMenu(0);
	g_dialogOpen = 1;
	g_highlightShown = 1;
	g_profileDialog = kind;
	g_cursorBlink = 0.0f;
	g_dialogChoice = 0;
	GAME_VAR(float, 0x680bc0) = 20.0f;
	GAME_VAR(float, 0x9da4a4) = 0.2f;
	g_questionX = x + 0x9c;
	g_questionY = y + 0x4a;
}

/* 0x44b670, 0x44b6e0: question 3 over the pilot panel, question 5 over the second panel */
void (profile_44b670)(void) { ask(3, GAME_VAR(int, 0x9f8f1c), GAME_VAR(int, 0x9f8f0c)); }
void (profile_44b6e0)(void) { ask(5, GAME_VAR(int, 0x9f6834), GAME_VAR(int, 0x9f683c)); }

/* 0x44f810: the profile screen: only its frame while a dialog is up, else the pilot preview (when shown) and the
   screen */
void (profile_44f810)(void)
{
	if (g_dialogOpen != 0) {
		menu_drawFrame(GAME_VAR(int, 0x9f8c54), GAME_VAR(int, 0x9f8c50), GAME_VAR(int, 0x9f6830), GAME_VAR(int, 0x9f682c));
		return;
	}
	if (GAME_VAR(int, 0x9f8d68) != 0)
		profile_44bc50();
	profile_44e640();
}

/* 0x44dc60: the profile message window (the panel 0x9f8eac, 0x9f8ea8 .. 0x9f8f20, 0x9f8f24): its frame (texture
   0x4deb50), the message 0x751d24 across the top in the panel's colour (0x9f8eb0), the OK button (texture
   0x9db0a4, 0x60 wide, centred) with its label 0x7517a4, and the border. Returns the border call's eax */
u32 (profile_44dc60)(void)
{
#define X0 GAME_VAR(int, 0x9f8eac)
#define Y0 GAME_VAR(int, 0x9f8ea8)
#define X1 GAME_VAR(int, 0x9f8f20)
#define Y1 GAME_VAR(int, 0x9f8f24)
	const u32 *colour = (const u32 *)0x9f8eb0;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427b60(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	int button = X0 + (X1 - X0) / 2 - 0x32;
	set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(X0, Y0 + 0x20, X1, (const char *)0x751d24);
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexQuad_4282f0(button, Y0 + 0x50, button + 0x60, Y0 + 0x70, 1);
	set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
	text_drawBox16(button, Y0 + 0x58, button + 0x60, (const char *)0x7517a4);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* ---- a two-button profile dialog: the window (x0, y0, x1, y1 kept in four globals) with its frame (texture
   0x4deb50), the question across the top in the panel colour (0x9f8eb0), two buttons 0x78 apart (texture 0x9db0a4,
   labels 0x80 bytes apart from 0x7517a4), the hovered one (by hit) bright in the panel colour, the other dim in
   0x9f8d58, and the border. Returns the border call's eax ---- */
typedef struct { u32 x0, y0, x1, y1, hit, question; } TwoButtons;

static u32 two_buttons(const TwoButtons *d)
{
#define X0 GAME_VAR(int, d->x0)
#define Y0 GAME_VAR(int, d->y0)
#define X1 GAME_VAR(int, d->x1)
#define Y1 GAME_VAR(int, d->y1)
	const u32 *panel = (const u32 *)0x9f8eb0, *dim = (const u32 *)0x9f8d58;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	int hovered = GAME_CDECL(d->hit, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427b60(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, panel[0], panel[1], panel[2], panel[3]);
	text_drawBox16(X0, Y0 + 0x10, X1, (const char *)d->question);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		const u32 *colour = k == hovered ? panel : dim;
		glColor4f(1.0f, 1.0f, 1.0f, k == hovered ? 1.0f : 0.4f);
		menu_drawTexQuad_4282f0(X0 + k * 0x78 + 0x6e, Y0 + 0x3c, X0 + k * 0x78 + 0xce, Y0 + 0x5c, 1);
		set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(X0 + k * 0x78 + 0x6e, Y0 + 0x44, X0 + k * 0x78 + 0xce, (const char *)(0x7517a4 + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	return GAME_CDECL(0x428b50, u32, int, int, int, int)(X0, Y0, X1, Y1);   /* the border */
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x44e180: the delete question (profile_44b320, question 0x751da4); 0x44e3e0: the second dialog (profile_44b360,
   question 0x751e24) */
u32 (profile_44e180)(void)
{
	static const TwoButtons d = { 0x9f8f1c, 0x9f8f0c, 0x9f8f2c, 0x9f8f28, 0x44b320, 0x751da4 };
	return two_buttons(&d);
}
u32 (profile_44e3e0)(void)
{
	static const TwoButtons d = { 0x9f6834, 0x9f683c, 0x9f93bc, 0x9f93c0, 0x44b360, 0x751e24 };
	return two_buttons(&d);
}
