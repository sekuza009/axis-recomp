/* game_lists.c: the lists of games to join, the game room's (window 0x9dd4a8 .. 0x9dd4b4) and the arena lobby's
   (0x4db8c8 .. 0x4db8d4): the games (0x4a-byte records from 0x9087c4) from row 0x680bb0, the page, and their boxes */
#include "../game.h"
#include <string.h>

#define crt_strncpy(to, from, n) GAME_CDECL(0x49ea80, char *, char *, const char *, int)(to, from, n)
#define g_gameCount GAME_VAR(int, 0x67ef30)
#define g_listTop GAME_VAR(int, 0x680bb0)
#define g_confirming GAME_VAR(int, 0x4db8b4)     /* the join confirmation */
#define g_leaving GAME_VAR(int, 0x907b2c)        /* the "leave?" box */
#define g_full GAME_VAR(int, 0x4db714)           /* the "arena full" box */
#define g_joining GAME_VAR(int, 0x4db8bc)        /* the "joining" box */
#define g_searching (GAME_VAR(int, 0x4dba90) || GAME_VAR(int, 0x4db858))

static const u32 *const bright = (const u32 *)0x4dba98, *const dim = (const u32 *)0x4db8a0;
#define TEXT(c) set_colour_bits((Colour *)0x76d438, (c)[0], (c)[1], (c)[2], (c)[3])
#define RECT(r, g, b, a) set_colour_bits(g_rectColour, r, g, b, a)

static void bind_buttons(void)
{
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
}

/* a button's quad (x0, y0 .. x1, y1), lit or dimmed, and the text colour to match */
static void button(int lit, int x0, int y0, int x1, int y1, float dim_alpha)
{
	glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : dim_alpha);
	menu_drawTexQuad_4282f0(x0, y0, x1, y1, 1);
	if (lit)
		TEXT(bright);
	else
		TEXT(dim);
}

/* nine rows of games from g_listTop at x0, from y (to end) below y0: a lock (+0x43; when locks), the name (+0, 32
   characters), the map (+0x21, 13 characters; 0x75c1a4 when +0x20), the game type (+0x28, a string of kinds, step
   apart), "players / most" (+0x23 / +0x22) and the ping (+0x24; when pings); the game under the cursor (0x76d41c) in
   white, the others cyan */
static void game_rows(int x0, int y0, int y, int end, int locks, u32 kinds, int step, int pings)
{
	char text[50], other[12];
	for (int i = 0; i < g_gameCount && y < end; i++, y += 0x18) {
		const u8 *game = (const u8 *)0x9087c4 + (g_listTop + i) * 0x4a;
		if (locks && game[0x43]) {
			glEnable(GL_TEXTURE_2D);
			int texture = GAME_VAR(int, 0x76d448);
			tex_bind(g_textures->managers[texture / 512], texture % 512);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.8125f);
			menu_vertex(x0 + 0xc, y0 + y - 1);
			glTexCoord2f(0.0625f, 0.8125f);
			menu_vertex(x0 + 0x1c, y0 + y - 1);
			glTexCoord2f(0.0625f, 0.875f);
			menu_vertex(x0 + 0x1c, y0 + y + 0xf);
			glTexCoord2f(0.0f, 0.875f);
			menu_vertex(x0 + 0xc, y0 + y + 0xf);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		set_colour_bits((Colour *)0x76d438, 0, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000);   /* 0, 0.8, 0.8, 1 */
		if (GAME_VAR(int, 0x76d41c) == g_listTop + i)
			set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		memset(text, 0, sizeof text);
		crt_strncpy(text, (const char *)game, 0x20);
		text_draw8(x0 + 0x20, y0 + y, text);
		if (game[0x20])
			text_draw8(x0 + 0x114, y0 + y, (const char *)0x75c1a4);
		else {
			memset(text, 0, sizeof text);
			crt_strncpy(text, (const char *)(0x907b30 + (signed char)game[0x21] * 0x20), 0xd);
			text_draw8(x0 + 0x114, y0 + y, text);
		}
		text_draw8(x0 + 0x182, y0 + y, (const char *)(kinds + (signed char)game[0x28] * step));
		memset(text, 0, sizeof text);
		itoa((signed char)game[0x23], text, 10);
		itoa((signed char)game[0x22], other, 10);
		strcat(text, (const char *)0x4ad568);   /* " / " */
		strcat(text, other);
		text_draw8(x0 + 0x1bc, y0 + y, text);
		if (pings) {
			itoa(*(const int *)(game + 0x24), text, 10);
			text_draw8(x0 + 0x200, y0 + y, text);
		}
	}
}

/* "page / pages" (0x680bb8) in white, right-aligned (13 a character) 0x3c in from x1 at y */
static void game_page(int x1, int y, int pages_count)
{
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	char page[50] = { 0 }, pages[10] = { 0 };
	itoa(GAME_VAR(int, 0x680bb8), page, 10);
	strcat(page, (const char *)0x4ad564);   /* "/" */
	itoa(pages_count, pages, 10);
	strcat(page, pages);
	text_draw16(x1 - (int)strlen(page) * 13 - 0x3c, y, page);
}

/* ---- the arena lobby's ---- */
#define X0 GAME_VAR(int, 0x4db8c8)
#define Y0 GAME_VAR(int, 0x4db8cc)
#define X1 GAME_VAR(int, 0x4db8d0)
#define Y1 GAME_VAR(int, 0x4db8d4)

/* a box over the list with a line (0x74f124 joining / 0x74f624 full) and a dark field (with the arena's name, 0x4db520,
   when joining) */
static void info_box(u32 line, int named)
{
	RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
	menu_drawRect(X0 + 0x64, Y0 + 0x96, X1 - 0x64, Y0 + 0x116, 1);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(X0 + 0x64, Y0 + 0xa6, X1 - 0x64, (const char *)line);
	RECT(0, 0, 0, 0x3f000000);
	menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 1);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f000000);
	menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 0);
	if (named)
		text_draw16(X0 + 0xd8, Y0 + 0xd0, (const char *)0x4db520);
}

/* 0x40a070: the arena's game list: the window, its title 0x7524a4, three tabs (0x752524; the one under the pointer,
   by arena_4044a0, lit unless a box is up), five column heads; the rows and page when there is a list (0x4dbac8,
   or the full one 0x4dbaa8); three buttons (0x7528a4: join needs a game, and while searching only the second
   lights; all dimmed under the full / joining boxes); the scroll arrows (15 / 16); the blinking 0x752a24 while
   searching or 0x4db8b8; the joining and full boxes, the join confirmation (0x752aa4 / 0x752b24, its button
   0x751824 by arena_4044e0) and the "leave?" box (the original asks arena_4045a0 but lights its buttons by the
   list's own pointer test); the border. The original leaves eax to callers that ignore it */
void (arena_40a070)(void)
{
	int hovered = GAME_CDECL(0x4044a0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* arena_4044a0 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	TEXT(bright);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)0x7524a4);
	int boxed = g_confirming || g_leaving || g_full || g_joining;
	for (int k = 0; k < 3; k++) {
		bind_buttons();
		int x = X0 + k * 0xb4;
		button(hovered == k && !boxed, x + 0x23, Y0 + 0x30, x + 0xc3, Y0 + 0x50, 0.4f);
		text_drawBox16(x + 0x25, Y0 + 0x38, x + 0xc1, (const char *)(0x752524 + k * 0x80));
	}
	TEXT(bright);
	static const struct { int x; u32 text; } heads[5] = {
		{ 0x10, 0x7526a4 }, { 0x114, 0x752724 }, { 0x164, 0x752ba4 }, { 0x1b4, 0x7527a4 }, { 0x1fc, 0x752824 },
	};
	for (int c = 0; c < 5; c++)
		text_draw8(X0 + heads[c].x, Y0 + 0x5a, (const char *)heads[c].text);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y0 + 0x6e, X1 - 0x10, Y0 + 0x6e);
	FUN_00427a40(X0 + 0x10, Y1 - 0x54, X1 - 0x10, Y1 - 0x54);
	if (GAME_VAR(int, 0x4dbac8) || GAME_VAR(int, 0x4dbaa8)) {
		int full = GAME_VAR(int, 0x4dbaa8);
		game_rows(X0, Y0, 0x78, 0x150, full, 0x4db8d8, 20, full);
		game_page(X1, Y1 - 0x4c, GAME_VAR(int, 0x4dbac8) ? g_gameCount : GAME_VAR(int, 0xa0b368));
	}
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y1 - 0x32, X1 - 0x10, Y1 - 0x32);
	for (int k = 0; k < 3; k++) {
		bind_buttons();
		int x = X0 + k * 0x96 + 0x5a;
		int lit = 0;
		if (hovered == k + 3 && !g_confirming && !g_leaving) {
			if (g_searching)
				lit = k == 1;
			else
				lit = k != 0 || g_gameCount != 0;
		}
		button(lit, x, Y1 - 0x2c, x + 0x78, Y1 - 0xc, 0.4f);
		if (g_full || g_joining)
			button(0, x, Y1 - 0x2c, x + 0x78, Y1 - 0xc, 0.4f);
		text_drawBox16(x, Y1 - 0x24, x + 0x78, (const char *)(0x7528a4 + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexQuad_4286b0(X0 + 0x21e, Y0 + 0xa0, X0 + 0x23e, Y0 + 0xe0, hovered == 0xf);
	menu_drawTexQuad_4287a0(X0 + 0x21e, Y0 + 0xf0, X0 + 0x23e, Y0 + 0x130, hovered != 0xf && hovered == 0x10);
	if (g_searching || GAME_VAR(int, 0x4db8b8)) {   /* blinking in fifteen steps */
		int step = ftol(fmul_m(fld_m((const float *)0x4dba80), (const float *)0x4a9438)) % 15;
		float alpha = f32(fmul_m((long double)step, (const float *)0x4a9434));
		set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y1 - 0x4a, X1, (const char *)0x752a24);
	}
	glDisable(GL_TEXTURE_2D);
	if (g_joining)
		info_box(0x74f124, 1);
	if (g_full)
		info_box(0x74f624, 0);
	if (g_confirming) {
		int on = GAME_CDECL(0x4044e0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* arena_4044e0 */
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)0x752aa4);
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)0x752b24);
		glEnable(GL_TEXTURE_2D);
		texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		button(on == 0, 0x104, 0x118, 0x17c, 0x138, 0.7f);
		text_drawBox16(0x104, 0x120, 0x17c, (const char *)0x751824);
	}
	if (g_leaving) {
		GAME_CDECL(0x4045a0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* arena_4045a0 (unused) */
		RECT(0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3ecccccd);   /* 0.1, 0.1, 0.1, 0.4 */
		menu_drawRect(0, 0, 0x280, 0x1e0, 1);
		RECT(0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f4ccccd);
		menu_drawRect(0x64, 0xb4, 0x21c, 0x140, 1);
		RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(0x68, 0xb8, 0x218, 0x13c, 0);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_drawBox16(0x64, 0xc8, 0x21c, (const char *)0x74dfa4);
		text_drawBox16(0x64, 0xdc, 0x21c, (const char *)0x74e024);
		for (int k = 0; k < 2; k++) {
			bind_buttons();
			int x = 0xb4 + k * 0xa0;
			button(hovered == k, x, 0x104, x + 0x78, 0x124, 0.4f);
			text_drawBox16(x, 0x10c, x + 0x78, (const char *)(0x7517a4 + k * 0x80));
		}
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
}
#undef X0
#undef Y0
#undef X1
#undef Y1

/* ---- the game room's ---- */
#define X0 GAME_VAR(int, 0x9dd4a8)
#define Y0 GAME_VAR(int, 0x9dd4ac)
#define X1 GAME_VAR(int, 0x9dd4b0)
#define Y1 GAME_VAR(int, 0x9dd4b4)

static const u32 *const room_bright = (const u32 *)0x9dcec0, *const room_dim = (const u32 *)0x9dd338;

/* a room button's quad, lit or dimmed, and the text colour to match */
static void room_button(int lit, int x0, int y0, int x1, int y1, float dim_alpha)
{
	glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : dim_alpha);
	menu_drawTexQuad_4282f0(x0, y0, x1, y1, 1);
	if (lit)
		TEXT(room_bright);
	else
		TEXT(room_dim);
}

/* 0x43adc0: the game room's list of games: the window, its title 0x759ca4, five column heads (0x759d24, 0x80
   apart), rules; with a list (0x9dd330) of games, the rows and "page / pages" (0xa0b358); four buttons (0x759fa4;
   the one under the pointer, by room_432300, lit: the first only with games, and while searching (0x9dd6a0) only
   the third; all dimmed while joining, 0x9dd6b4); the scroll arrows (13 / 14); the blinking 0x75a1a4 while
   searching or 0x9dd3fc; the joining box (0x74f124 and the room's name 0x9dcee8); the join confirmation (0x752aa4 /
   0x752b24, its button 0x751824 by room_432340); the border. The original leaves eax to callers that ignore it */
void (room_43adc0)(void)
{
	int hovered = GAME_CDECL(0x432300, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* room_432300 */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	TEXT(room_bright);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)0x759ca4);
	static const int heads[5] = { 0x10, 0x114, 0x164, 0x1b4, 0x1fc };
	for (int c = 0; c < 5; c++)
		text_draw8(X0 + heads[c], Y0 + 0x38, (const char *)(0x759d24 + c * 0x80));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y0 + 0x50, X1 - 0x10, Y0 + 0x50);
	FUN_00427a40(X0 + 0x10, Y1 - 0x5e, X1 - 0x10, Y1 - 0x5e);
	if (GAME_VAR(int, 0x9dd330) && g_gameCount) {
		game_rows(X0, Y0, 0x60, 0x138, 1, 0x7673a4, 0x80, 1);
		game_page(X1, Y1 - 0x58, GAME_VAR(int, 0xa0b358));
	}
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	FUN_00427a40(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	for (int k = 0; k < 4; k++) {
		bind_buttons();
		int x = X0 + k * 0x8c + 0x20;
		int lit = 0;
		if (hovered == k) {
			if (GAME_VAR(int, 0x9dd6a0))
				lit = k == 2;
			else
				lit = k != 0 || g_gameCount != 0;
		}
		room_button(lit, x, Y1 - 0x32, x + 0x78, Y1 - 0x12, 0.4f);
		if (GAME_VAR(int, 0x9dd6b4))
			room_button(0, x, Y1 - 0x32, x + 0x78, Y1 - 0x12, 0.4f);
		text_drawBox16(x, Y1 - 0x2a, x + 0x78, (const char *)(0x759fa4 + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexQuad_4286b0(X0 + 0x226, Y0 + 0x6e, X0 + 0x246, Y0 + 0xae, hovered == 0xd);
	menu_drawTexQuad_4287a0(X0 + 0x226, Y0 + 0xbe, X0 + 0x246, Y0 + 0xfe, hovered != 0xd && hovered == 0xe);
	glDisable(GL_TEXTURE_2D);
	if (GAME_VAR(int, 0x9dd6a0) || GAME_VAR(int, 0x9dd3fc)) {   /* blinking in fifteen steps */
		int step = ftol(fmul_m(fld_m((const float *)0x4dba80), (const float *)0x4a9438)) % 15;
		float alpha = f32(fmul_m((long double)step, (const float *)0x4a9434));
		set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y1 - 0x57, X1, (const char *)0x75a1a4);
	}
	if (GAME_VAR(int, 0x9dd6b4)) {
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(X0 + 0x64, Y0 + 0x96, X1 - 0x64, Y0 + 0x116, 1);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_drawBox16(X0 + 0x64, Y0 + 0xa6, X1 - 0x64, (const char *)0x74f124);
		RECT(0, 0, 0, 0x3f000000);
		menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 1);
		RECT(0, 0x3f800000, 0x3f800000, 0x3f000000);
		menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 0);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_draw16(X0 + 0xd8, Y0 + 0xd0, (const char *)0x9dcee8);
	}
	if (g_confirming) {
		glDisable(GL_TEXTURE_2D);
		int on = GAME_CDECL(0x432340, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* room_432340 */
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)0x752aa4);
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)0x752b24);
		glEnable(GL_TEXTURE_2D);
		texture = GAME_VAR(int, 0x9db0a4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		room_button(on == 0, 0x104, 0x118, 0x17c, 0x138, 0.7f);
		glDisable(GL_TEXTURE_2D);
		text_drawBox16(0x104, 0x120, 0x17c, (const char *)0x751824);
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
}
#undef X0
#undef Y0
#undef X1
#undef Y1

/* 0x43ea10: the game room's page of games: the "searching" message's clock (0x9dcd40, while 0x9dd34c; done above 0x4a944c),
   the tunnel; in room modes other than 0 / 1, and not page 99: a message box (0x90d1c4) alone, else the search's
   end (0x9dd6a0 searching, 0x9da498 the answer in, 0x76d484 its result: -1 .. 4) and the blinking clock (0x4dba80
   falling, back to 1000 below 0x4a9418); while the list refreshes (0x9dd3fc) its timer (0x9dd6c0 against 0x5b1914:
   the list asked for again, the next in 5) and a stop (0xa0d7a0); then the list, and with a game joined (0x9dd56c)
   the join sent (0x9dd6b4 clear) or, once a password is typed (0x9dd6c8), it checked against the game's (+0x3b)
   (message 0x27 when wrong) */
void (room_43ea10)(void)
{
	const float *step = (const float *)0x4ad498, *blinkFloor = (const float *)0x4a9418;
	if (GAME_VAR(int, 0x9dd34c)) {
		long double t = fadd_m(fld_m(&g_frameTime), &GAME_VAR(float, 0x9dcd40));
		GAME_VAR(float, 0x9dcd40) = f32(t);
		if (t > *(const float *)0x4a944c) {
			GAME_VAR(int, 0x9dd34c) = 0;
			GAME_VAR(int, 0x9dcd40) = 0;
		}
	}
	room_4388e0();
	int mode = GAME_VAR(int, 0x9dce48);
	if (mode == 1 || mode == 0 || GAME_VAR(int, 0x9dd834) == 99)
		return;
	if (GAME_VAR(int, 0x90d1c4)) {
		menu_drawFrame(GAME_VAR(int, 0x9dd4a8), GAME_VAR(int, 0x9dd4ac), GAME_VAR(int, 0x9dd4b0), GAME_VAR(int, 0x9dd4b4));
		return;
	}
	if (GAME_VAR(int, 0x9dd6a0)) {
		if (GAME_VAR(int, 0x9da498) == 1) {
			int result = GAME_VAR(int, 0x76d484);
			if (result != 2 && (u32)(result + 1) <= 5) {
				GAME_VAR(int, 0x4db858) = 0;
				GAME_VAR(int, 0x4df018) = 0;
				GAME_VAR(int, 0x4db8b8) = result == 1;
				if (result == 3)
					GAME_VAR(int, 0x907b2c) = 1;
				else if (result == 0)
					FUN_0041ee40(0x40);
				else if (result == 4)
					FUN_0041ee40(0x2a);
			}
			GAME_VAR(int, 0x9dd6a0) = 0;
			GAME_VAR(int, 0x9da498) = 0;
			GAME_VAR(int, 0x9dd3fc) = 1;
		}
		long double blink = fsubr_m(fmul_m(fld_m(step), &g_frameTime), &GAME_VAR(float, 0x4dba80));
		GAME_VAR(float, 0x4dba80) = f32(blink);
		if (!(blink >= *blinkFloor))
			GAME_VAR(u32, 0x4dba80) = 0x447a0000;   /* 1000 */
	}
	if (GAME_VAR(int, 0x9dd3fc)) {
		long double t = fadd_m(fld_m(&GAME_VAR(float, 0x9dd6c0)), &g_frameTime);
		GAME_VAR(float, 0x9dd6c0) = f32(t);
		if (t > (long double)GAME_VAR(int, 0x5b1914)) {
			room_434ff0();
			GAME_VAR(int, 0x9dd6c0) = 0;
			GAME_VAR(int, 0x5b1914) = 5;
		}
		long double blink = fsubr_m(fmul_m(fld_m(step), &g_frameTime), &GAME_VAR(float, 0x4dba80));
		GAME_VAR(float, 0x4dba80) = f32(blink);
		if (!(blink >= *blinkFloor))
			GAME_VAR(u32, 0x4dba80) = 0x447a0000;
		if (GAME_VAR(int, 0xa0d7a0)) {
			room_434ff0();
			GAME_VAR(int, 0x9dd6a0) = 0;
			GAME_VAR(int, 0x9da498) = 0;
			GAME_VAR(int, 0x9dd3fc) = 0;
		}
	}
	room_43adc0();
	if (!GAME_VAR(int, 0x9dd56c))
		return;
	if (!GAME_VAR(int, 0x9dd6b4)) {
		room_434dd0(g_localPlayer);
		return;
	}
	if (!GAME_VAR(int, 0x9dd6c8) || g_paused)
		return;
	GAME_VAR(int, 0x9dd6c8) = 0;
	memset((void *)0x9dcee8, 0, 8);
	strcpy((char *)0x9dcee8, g_chatLine);
	if (strcmp((const char *)(0x9087c4 + g_localPlayer * 0x4a + 0x3b), (const char *)0x9dcee8) != 0) {
		FUN_0041ee40(0x27);
		GAME_VAR(int, 0x9dd56c) = 0;
	}
	GAME_VAR(int, 0x9dd6b4) = 0;
}

/* ---- the arena's name dialog (its window at 0x4dbb68 .. 0x4dbb74) ---- */

/* text with a near-black shadow one down and right, then in yellow */
static void shadowed(int x, int y, const char *text)
{
	set_colour_bits((Colour *)0x76d438, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01 */
	text_draw8(x + 1, y + 1, text);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);           /* 1, 0.8, 0 */
	text_draw8(x, y, text);
}

/* 0x409bc0: the arena's name dialog: the window, a cyan frame, the title 0x751fa4, two labels (0x752024, 0x752124)
   and the name 0x4db560 (hidden while it is typed in, g_paused); without a message (0x4dbbd0) the name or the
   second label under the pointer (arena_404460's 0 / 2) shadowed in yellow; three buttons (0x7521a4, 0x80 apart;
   3 .. 5, lit under the pointer), the border. The original leaves eax to callers that ignore it */
void (arena_409bc0)(void)
{
	int x0 = GAME_VAR(int, 0x4dbb68), y0 = GAME_VAR(int, 0x4dbb6c);
	int hovered = arena_404460(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(x0, y0, GAME_VAR(int, 0x4dbb70), GAME_VAR(int, 0x4dbb74), GAME_VAR(int, 0x4deb50));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(x0 + 0x20, y0 + 0x30, GAME_VAR(int, 0x4dbb70) - 0x20, GAME_VAR(int, 0x4dbb74) - 0x20, 0);
	TEXT(bright);
	text_draw16(x0 + 0x50, y0 + 0x10, (const char *)0x751fa4);
	bind_buttons();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	text_draw8(x0 + 0x40, y0 + 0x64, (const char *)0x752024);
	text_draw8(x0 + 0x40, y0 + 0x96, (const char *)0x752124);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	if (!g_paused)
		text_draw8(x0 + 0xc2, y0 + 0x64, (const char *)0x4db560);
	if (!GAME_VAR(int, 0x4dbbd0)) {
		if (hovered == 0 && !g_paused)
			shadowed(x0 + 0xc1, y0 + 0x63, (const char *)0x4db560);
		else if (hovered == 2)
			shadowed(x0 + 0x3f, y0 + 0x95, (const char *)0x752124);
	}
	for (int k = 0; k < 3; k++) {
		int x = GAME_VAR(int, 0x4dbb68) + k * 0x78, y = GAME_VAR(int, 0x4dbb6c);
		bind_buttons();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		button(hovered == k + 3 && !GAME_VAR(int, 0x4dbbd0), x + 0x32, y + 0xdc, x + 0x96, y + 0xfc, 0.4f);
		text_drawBox16(x + 0x32, GAME_VAR(int, 0x4dbb6c) + 0xe4, x + 0x96, (const char *)(0x7521a4 + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(GAME_VAR(int, 0x4dbb68), GAME_VAR(int, 0x4dbb6c), GAME_VAR(int, 0x4dbb70), GAME_VAR(int, 0x4dbb74));
}
