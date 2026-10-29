/* arena_list.c: the arena's game list (the join screen of the arena lobby): its window at 0x4db8c8 .. 0x4db8d4, the
   list of games (0x4a-byte records from 0x9087c4) from row 0x680bb0, and its boxes */
#include "../game.h"
#include <string.h>

#define X0 GAME_VAR(int, 0x4db8c8)
#define Y0 GAME_VAR(int, 0x4db8cc)
#define X1 GAME_VAR(int, 0x4db8d0)
#define Y1 GAME_VAR(int, 0x4db8d4)
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

/* the list's rows (up to nine from g_listTop): a lock when the list shows them (0x4dbaa8) and the game has one
   (+0x43), the name (+0, 32 characters), the map (+0x21, 13 characters; 0x75c1a4 when +0x20), the game type (+0x28,
   a 0x4db8d8 string), "players / most" (+0x23 / +0x22) and with the full list the ping (+0x24); the game under the
   cursor (0x76d41c) in white, the others cyan; then "page / pages" */
static void rows(void)
{
	char text[50], other[12];
	for (int i = 0, y = 0x78; i < g_gameCount && y < 0x150; i++, y += 0x18) {
		const u8 *game = (const u8 *)0x9087c4 + (g_listTop + i) * 0x4a;
		if (GAME_VAR(int, 0x4dbaa8) && game[0x43]) {
			glEnable(GL_TEXTURE_2D);
			int texture = GAME_VAR(int, 0x76d448);
			tex_bind(g_textures->managers[texture / 512], texture % 512);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.8125f);
			menu_vertex(X0 + 0xc, Y0 + y - 1);
			glTexCoord2f(0.0625f, 0.8125f);
			menu_vertex(X0 + 0x1c, Y0 + y - 1);
			glTexCoord2f(0.0625f, 0.875f);
			menu_vertex(X0 + 0x1c, Y0 + y + 0xf);
			glTexCoord2f(0.0f, 0.875f);
			menu_vertex(X0 + 0xc, Y0 + y + 0xf);
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		set_colour_bits((Colour *)0x76d438, 0, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000);   /* 0, 0.8, 0.8, 1 */
		if (GAME_VAR(int, 0x76d41c) == g_listTop + i)
			set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		memset(text, 0, sizeof text);
		crt_strncpy(text, (const char *)game, 0x20);
		text_draw8(X0 + 0x20, Y0 + y, text);
		if (game[0x20])
			text_draw8(X0 + 0x114, Y0 + y, (const char *)0x75c1a4);
		else {
			memset(text, 0, sizeof text);
			crt_strncpy(text, (const char *)(0x907b30 + (signed char)game[0x21] * 0x20), 0xd);
			text_draw8(X0 + 0x114, Y0 + y, text);
		}
		text_draw8(X0 + 0x182, Y0 + y, (const char *)(0x4db8d8 + (signed char)game[0x28] * 20));
		memset(text, 0, sizeof text);
		itoa((signed char)game[0x23], text, 10);
		itoa((signed char)game[0x22], other, 10);
		strcat(text, (const char *)0x4ad568);   /* " / " */
		strcat(text, other);
		text_draw8(X0 + 0x1bc, Y0 + y, text);
		if (GAME_VAR(int, 0x4dbaa8)) {
			itoa(*(const int *)(game + 0x24), text, 10);
			text_draw8(X0 + 0x200, Y0 + y, text);
		}
	}
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	char page[50] = { 0 }, pages[10] = { 0 };
	itoa(GAME_VAR(int, 0x680bb8), page, 10);
	strcat(page, (const char *)0x4ad564);   /* "/" */
	itoa(GAME_VAR(int, 0x4dbac8) ? g_gameCount : GAME_VAR(int, 0xa0b368), pages, 10);
	strcat(page, pages);
	text_draw16(X1 - (int)strlen(page) * 13 - 0x3c, Y1 - 0x4c, page);
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
	if (GAME_VAR(int, 0x4dbac8) || GAME_VAR(int, 0x4dbaa8))
		rows();
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
