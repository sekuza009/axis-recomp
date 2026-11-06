/* game_lists.c: the lists of games to join, the game room's (window 0x9dd4a8 .. 0x9dd4b4) and the arena lobby's
   (0x4db8c8 .. 0x4db8d4): the games (g_sessionList) from row g_gameListTop, the page, and their boxes */
#include "../game.h"
#include <string.h>

#define g_listTop g_gameListTop
#define g_searching (g_lanSearch || g_lobbySearching)

static const u32 *const bright = g_arenaBright, *const dim = g_arenaDim;
#define TEXT(c) set_colour_bits(g_textColour, (c)[0], (c)[1], (c)[2], (c)[3])
#define RECT(r, g, b, a) set_colour_bits(g_rectColour, r, g, b, a)

static void bind_buttons(void)
{
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
}

/* a button's quad (x0, y0 .. x1, y1), lit or dimmed, and the text colour to match */
static void button(int lit, int x0, int y0, int x1, int y1, float dim_alpha)
{
	glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : dim_alpha);
	menu_drawWideButton(x0, y0, x1, y1, 1);
	if (lit)
		TEXT(bright);
	else
		TEXT(dim);
}

/* nine rows of games from g_listTop at x0, from y (to end) below y0: a lock (when locks), the name (32 characters),
   the map (13 characters; MSG(455, "ROTATION") with the rotation flag), the game mode (a string of kinds, step
   apart), "players / most" and the ping (when pings); the game under the cursor (g_pickedGame) in
   white, the others cyan */
static void game_rows(int x0, int y0, int y, int end, int locks, u32 kinds, int step, int pings)
{
	char text[50], other[12];
	for (int i = 0; i < g_gameCount && y < end; i++, y += 0x18) {
		const SessionEntry *game = &g_sessionList[g_listTop + i];
		if (locks && game->locked) {
			glEnable(GL_TEXTURE_2D);
			int texture = g_fontAscii;
			tex_bind(g_textures->banks[texture / 512], texture % 512);
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
		set_colour_bits(g_textColour, 0, 0x3f4ccccd, 0x3f4ccccd, 0x3f800000);   /* 0, 0.8, 0.8, 1 */
		if (g_pickedGame == g_listTop + i)
			set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		memset(text, 0, sizeof text);
		crt_strncpy(text, game->name, 0x20);
		text_draw8(x0 + 0x20, y0 + y, text);
		if (game->rotation)
			text_draw8(x0 + 0x114, y0 + y, (const char *)MSG(455, "ROTATION"));
		else {
			memset(text, 0, sizeof text);
			crt_strncpy(text, (const char *)(OBJ(g_mapNames) + game->map * 0x20), 0xd);
			text_draw8(x0 + 0x114, y0 + y, text);
		}
		text_draw8(x0 + 0x182, y0 + y, (const char *)(RELOC(kinds) + game->gameMode * step));
		memset(text, 0, sizeof text);
		itoa(game->players, text, 10);
		itoa(game->maxPlayers, other, 10);
		strcat(text, (const char *)STR(0x4ad568, " / "));
		strcat(text, other);
		text_draw8(x0 + 0x1bc, y0 + y, text);
		if (pings) {
			itoa(game->ping, text, 10);
			text_draw8(x0 + 0x200, y0 + y, text);
		}
	}
}

/* "page / pages" (g_lobbyListPage) in white, right-aligned (13 a character) 0x3c in from x1 at y */
static void game_page(int x1, int y, int pages_count)
{
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	char page[50] = { 0 }, pages[10] = { 0 };
	itoa(g_lobbyListPage, page, 10);
	strcat(page, (const char *)STR(0x4ad564, "/"));
	itoa(pages_count, pages, 10);
	strcat(page, pages);
	text_draw16(x1 - (int)strlen(page) * 13 - 0x3c, y, page);
}

/* ---- the arena lobby's ---- */
#define X0 g_arenaGameListLeft
#define Y0 g_arenaGameListTop
#define X1 g_arenaGameListRight
#define Y1 g_arenaGameListBottom

/* a box over the list with a line (MSG(38, "TYPE GAME PASSWORD") for a locked game / MSG(48, "INPUT IP-ADDRESS") for a game
   joined by address) and a dark field (with the typed password, g_arenaJoinPassword, for the first) */
static void info_box(u32 line, int named)
{
	RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
	menu_drawRect(X0 + 0x64, Y0 + 0x96, X1 - 0x64, Y0 + 0x116, 1);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_drawBox16(X0 + 0x64, Y0 + 0xa6, X1 - 0x64, (const char *)RELOC(line));
	RECT(0, 0, 0, 0x3f000000);
	menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 1);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f000000);
	menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 0);
	if (named)
		text_draw16(X0 + 0xd8, Y0 + 0xd0, (const char *)ADDR(g_arenaJoinPassword));
}

/* 0x40a070: the arena's game list: the window, its title MSG(141, "JOIN ARENA"), three tabs (MSG(142, "SEARCH $[0] IPX"); the one under the pointer,
   by arenaGameList_hitTest, lit unless a box is up), five column heads; the rows and page when there is a list (g_arenaHaveList,
   or the full one g_arenaListFull); three buttons (MSG(149, "$[0] JOIN"): join needs a game, and while searching only the second
   lights; all dimmed under the address / password boxes); the scroll arrows (15 / 16); the blinking MSG(152, "SEARCHING FOR THE GAME SERVER") while
   searching or g_lobbyRefreshing; the password and address boxes, the join confirmation (MSG(153, "CONNECTING TO THE GAME SERVER") / MSG(154, "PLEASE WAIT"), its button
   MSG(116, "$[0] CANCEL") by arenaDialogBox_hitTest) and the "leave?" box (the original asks arenaCreate_hitTest but lights its buttons by the
   list's own pointer test); the border. The original leaves eax to callers that ignore it */
void (arena_drawGameList)(void)
{
	int hovered = arenaGameList_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 0.8f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	TEXT(bright);
	text_draw16(X0 + 0x50, Y0 + 0x10, (const char *)MSG(141, "JOIN ARENA"));
	int boxed = g_arenaConfirming || g_arenaUpdateNotice || g_typingArenaAddress || g_arenaJoinNeedsPassword;
	for (int k = 0; k < 3; k++) {
		bind_buttons();
		int x = X0 + k * 0xb4;
		button(hovered == k && !boxed, x + 0x23, Y0 + 0x30, x + 0xc3, Y0 + 0x50, 0.4f);
		text_drawBox16(x + 0x25, Y0 + 0x38, x + 0xc1, (const char *)(MSG(142, "SEARCH $[0] IPX") + k * 0x80));
	}
	TEXT(bright);
	static const struct { int x; u32 text; } heads[5] = {
		{ 0x10, MSG(145, "ROOM NAME") }, { 0x114, MSG(146, "MAP NAME") }, { 0x164, MSG(155, "TYPE") }, { 0x1b4, MSG(147, "PLAYER") }, { 0x1fc, MSG(148, "PING") },
	};
	for (int c = 0; c < 5; c++)
		text_draw8(X0 + heads[c].x, Y0 + 0x5a, (const char *)RELOC(heads[c].text));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x6e, X1 - 0x10, Y0 + 0x6e);
	menu_drawLine(X0 + 0x10, Y1 - 0x54, X1 - 0x10, Y1 - 0x54);
	if (g_arenaHaveList || g_arenaListFull) {
		int full = g_arenaListFull;
		game_rows(X0, Y0, 0x78, 0x150, full, OBJ(g_gameTypeNames), 20, full);
		game_page(X1, Y1 - 0x4c, g_arenaHaveList ? g_gameCount : g_serverListCount);
	}
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x32, X1 - 0x10, Y1 - 0x32);
	for (int k = 0; k < 3; k++) {
		bind_buttons();
		int x = X0 + k * 0x96 + 0x5a;
		int lit = 0;
		if (hovered == k + 3 && !g_arenaConfirming && !g_arenaUpdateNotice) {
			if (g_searching)
				lit = k == 1;
			else
				lit = k != 0 || g_gameCount != 0;
		}
		button(lit, x, Y1 - 0x2c, x + 0x78, Y1 - 0xc, 0.4f);
		if (g_typingArenaAddress || g_arenaJoinNeedsPassword)
			button(0, x, Y1 - 0x2c, x + 0x78, Y1 - 0xc, 0.4f);
		text_drawBox16(x, Y1 - 0x24, x + 0x78, (const char *)(MSG(149, "$[0] JOIN") + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton3(X0 + 0x21e, Y0 + 0xa0, X0 + 0x23e, Y0 + 0xe0, hovered == 0xf);
	menu_drawSmallButton4(X0 + 0x21e, Y0 + 0xf0, X0 + 0x23e, Y0 + 0x130, hovered != 0xf && hovered == 0x10);
	if (g_searching || g_lobbyRefreshing) {   /* blinking in fifteen steps */
		int step = ftol(fmul_m(fld_m((const float *)ADDR(g_lobbyBlinkClock)), k_0_333333f)) % 15;
		float alpha = f32(fmul_m((long double)step, k_0_0667f));
		set_colour_bits(g_textColour, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y1 - 0x4a, X1, (const char *)MSG(152, "SEARCHING FOR THE GAME SERVER"));
	}
	glDisable(GL_TEXTURE_2D);
	if (g_arenaJoinNeedsPassword)
		info_box(MSG(38, "TYPE GAME PASSWORD"), 1);
	if (g_typingArenaAddress)
		info_box(MSG(48, "INPUT IP-ADDRESS"), 0);
	if (g_arenaConfirming) {
		int on = arenaDialogBox_hitTest(g_mouseX, g_mouseY);   /* arenaDialogBox_hitTest */
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)MSG(153, "CONNECTING TO THE GAME SERVER"));
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)MSG(154, "PLEASE WAIT"));
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		button(on == 0, 0x104, 0x118, 0x17c, 0x138, 0.7f);
		text_drawBox16(0x104, 0x120, 0x17c, (const char *)MSG(116, "$[0] CANCEL"));
	}
	if (g_arenaUpdateNotice) {
		arenaCreate_hitTest(g_mouseX, g_mouseY);   /* arenaCreate_hitTest (unused) */
		RECT(0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3ecccccd);   /* 0.1, 0.1, 0.1, 0.4 */
		menu_drawRect(0, 0, 0x280, 0x1e0, 1);
		RECT(0x3dcccccd, 0x3dcccccd, 0x3dcccccd, 0x3f4ccccd);
		menu_drawRect(0x64, 0xb4, 0x21c, 0x140, 1);
		RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(0x68, 0xb8, 0x218, 0x13c, 0);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_drawBox16(0x64, 0xc8, 0x21c, (const char *)MSG(3, "THIS PROGRAM HAS BEEN UPDATED"));
		text_drawBox16(0x64, 0xdc, 0x21c, (const char *)MSG(4, "DO DOWNLOAD A NEW VERSION"));
		for (int k = 0; k < 2; k++) {
			bind_buttons();
			int x = 0xb4 + k * 0xa0;
			button(hovered == k, x, 0x104, x + 0x78, 0x124, 0.4f);
			text_drawBox16(x, 0x10c, x + 0x78, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
		}
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
}
#undef X0
#undef Y0
#undef X1
#undef Y1

/* ---- the game room's ---- */
#define X0 g_roomGameListLeft
#define Y0 g_roomGameListTop
#define X1 g_roomGameListRight
#define Y1 g_roomGameListBottom

static const u32 *const room_bright = g_roomBright, *const room_dim = g_roomDim;

/* a room button's quad, lit or dimmed, and the text colour to match */
static void room_button(int lit, int x0, int y0, int x1, int y1, float dim_alpha)
{
	glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : dim_alpha);
	menu_drawWideButton(x0, y0, x1, y1, 1);
	if (lit)
		TEXT(room_bright);
	else
		TEXT(room_dim);
}

/* 0x43adc0: the game room's list of games: the window, its title MSG(381, "AXIS LADDER GAME"), five column heads (MSG(382, "TITLE"), 0x80
   apart), rules; with a list (g_gameListLoaded) of games, the rows and "page / pages" (g_roomListCount); four buttons (MSG(387, "$[0] JOIN");
   the one under the pointer, by gameList_hitTest, lit: the first only with games, and while searching (g_roomSearching) only
   the third; all dimmed while joining, g_roomJoinNeedsPassword); the scroll arrows (13 / 14); the blinking MSG(391, "SEARCHING FOR THE GAME SERVER") while
   searching or g_roomRefreshing; the joining box (MSG(38, "TYPE GAME PASSWORD") and the room's name g_joinPasswordAndRanking); the join confirmation (MSG(153, "CONNECTING TO THE GAME SERVER") /
   MSG(154, "PLEASE WAIT"), its button MSG(116, "$[0] CANCEL") by gameListStop_hitTest); the border. The original leaves eax to callers that ignore it */
void (gameList_draw)(void)
{
	int hovered = gameList_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x28, X1 - 0x10, Y0 + 0x28);
	TEXT(room_bright);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(381, "AXIS LADDER GAME"));
	static const int heads[5] = { 0x10, 0x114, 0x164, 0x1b4, 0x1fc };
	for (int c = 0; c < 5; c++)
		text_draw8(X0 + heads[c], Y0 + 0x38, (const char *)(MSG(382, "TITLE") + c * 0x80));
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y0 + 0x50, X1 - 0x10, Y0 + 0x50);
	menu_drawLine(X0 + 0x10, Y1 - 0x5e, X1 - 0x10, Y1 - 0x5e);
	if (g_gameListLoaded && g_gameCount) {
		game_rows(X0, Y0, 0x60, 0x138, 1, MSG(811, "DM"), 0x80, 1);
		game_page(X1, Y1 - 0x58, g_roomListCount);
	}
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawLine(X0 + 0x10, Y1 - 0x40, X1 - 0x10, Y1 - 0x40);
	for (int k = 0; k < 4; k++) {
		bind_buttons();
		int x = X0 + k * 0x8c + 0x20;
		int lit = 0;
		if (hovered == k) {
			if (g_roomSearching)
				lit = k == 2;
			else
				lit = k != 0 || g_gameCount != 0;
		}
		room_button(lit, x, Y1 - 0x32, x + 0x78, Y1 - 0x12, 0.4f);
		if (g_roomJoinNeedsPassword)
			room_button(0, x, Y1 - 0x32, x + 0x78, Y1 - 0x12, 0.4f);
		text_drawBox16(x, Y1 - 0x2a, x + 0x78, (const char *)(MSG(387, "$[0] JOIN") + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton3(X0 + 0x226, Y0 + 0x6e, X0 + 0x246, Y0 + 0xae, hovered == 0xd);
	menu_drawSmallButton4(X0 + 0x226, Y0 + 0xbe, X0 + 0x246, Y0 + 0xfe, hovered != 0xd && hovered == 0xe);
	glDisable(GL_TEXTURE_2D);
	if (g_roomSearching || g_roomRefreshing) {   /* blinking in fifteen steps */
		int step = ftol(fmul_m(fld_m((const float *)ADDR(g_lobbyBlinkClock)), k_0_333333f)) % 15;
		float alpha = f32(fmul_m((long double)step, k_0_0667f));
		set_colour_bits(g_textColour, 0, 0x3f800000, 0, BITS(alpha));
		text_drawBox16(X0, Y1 - 0x57, X1, (const char *)MSG(391, "SEARCHING FOR THE GAME SERVER"));
	}
	if (g_roomJoinNeedsPassword) {
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
		menu_drawRect(X0 + 0x64, Y0 + 0x96, X1 - 0x64, Y0 + 0x116, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_drawBox16(X0 + 0x64, Y0 + 0xa6, X1 - 0x64, (const char *)MSG(38, "TYPE GAME PASSWORD"));
		RECT(0, 0, 0, 0x3f000000);
		menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 1);
		RECT(0, 0x3f800000, 0x3f800000, 0x3f000000);
		menu_drawRect(X0 + 0xc8, Y0 + 0xc8, X1 - 0xc8, Y0 + 0xe8, 0);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		text_draw16(X0 + 0xd8, Y0 + 0xd0, (const char *)ADDR(g_roomJoinPassword));
	}
	if (g_arenaConfirming) {
		glDisable(GL_TEXTURE_2D);
		int on = gameListStop_hitTest(g_mouseX, g_mouseY);
		RECT(0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(0x64, 0xc8, 0x21c, 0x140, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
		text_drawBox16(0x69, 0xdc, 0x217, (const char *)MSG(153, "CONNECTING TO THE GAME SERVER"));
		text_drawBox16(0x69, 0xf4, 0x217, (const char *)MSG(154, "PLEASE WAIT"));
		glEnable(GL_TEXTURE_2D);
		texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		room_button(on == 0, 0x104, 0x118, 0x17c, 0x138, 0.7f);
		glDisable(GL_TEXTURE_2D);
		text_drawBox16(0x104, 0x120, 0x17c, (const char *)MSG(116, "$[0] CANCEL"));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
}
#undef X0
#undef Y0
#undef X1
#undef Y1

/* 0x43ea10: the game room's page of games: the "searching" message's clock (g_gameListClickTimer, while g_gameListClickArmed; done above k_20f),
   the tunnel; with the room camera arrived (g_roomCameraMode 2), and not page 99: a message box (g_dialogOpen) alone, else the search's
   end (g_roomSearching searching, g_roomSearchAnswerIn the answer in, g_searchResult its result: -1 .. 4) and the blinking clock (g_lobbyBlinkClock
   falling, back to 1000 below k_10f); while the list refreshes (g_roomRefreshing) its timer (g_roomListRefreshTimer against g_listRefreshPeriod:
   the list asked for again, the next in 5) and a stop (g_netListDone); then the list, and with a game joined (g_roomJoined)
   the join sent (g_roomJoinNeedsPassword clear) or, once a password is typed (g_typingRoomJoinPassword), it checked against the game's (+0x3b)
   (message 0x27 when wrong) */
void (gameList_drawPage)(void)
{
	const float *step = (const float *)ADDR(g_lobbyBlinkRate), *blinkFloor = (const float *)ADDR(k_10f);
	if (g_gameListClickArmed) {
		long double t = FADD(g_frameTime, g_gameListClickTimer);
		g_gameListClickTimer = f32(t);
		if (t > k_20f) {
			g_gameListClickArmed = 0;
			(*(int *)&g_gameListClickTimer) = 0;
		}
	}
	room_drawTunnel();
	int mode = g_roomCameraMode;
	if (mode == 1 || mode == 0 || g_roomState == 99)
		return;
	if (g_dialogOpen) {
		menu_drawFrame(g_roomGameListLeft, g_roomGameListTop, g_roomGameListRight, g_roomGameListBottom);
		return;
	}
	if (g_roomSearching) {
		if (g_roomSearchAnswerIn == 1) {
			int result = g_searchResult;
			if (result != 2 && (u32)(result + 1) <= 5) {
				g_lobbySearching = 0;
				g_serverAnswerIn = 0;
				g_lobbyRefreshing = result == 1;
				if (result == 3)
					g_arenaUpdateNotice = 1;
				else if (result == 0)
					menu_showMessage(0x40);
				else if (result == 4)
					menu_showMessage(0x2a);
			}
			g_roomSearching = 0;
			g_roomSearchAnswerIn = 0;
			g_roomRefreshing = 1;
		}
		long double blink = fsubr_m(fmul_m(fld_m(step), &g_frameTime), &g_lobbyBlinkClock);
		g_lobbyBlinkClock = f32(blink);
		if (!(blink >= *blinkFloor))
			(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000 */
	}
	if (g_roomRefreshing) {
		long double t = FADD(g_roomListRefreshTimer, g_frameTime);
		g_roomListRefreshTimer = f32(t);
		if (t > (long double)g_listRefreshPeriod) {
			room_mergeReceivedSessions();
			(*(int *)&g_roomListRefreshTimer) = 0;
			g_listRefreshPeriod = 5;
		}
		long double blink = fsubr_m(fmul_m(fld_m(step), &g_frameTime), &g_lobbyBlinkClock);
		g_lobbyBlinkClock = f32(blink);
		if (!(blink >= *blinkFloor))
			(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;
		if (g_netListDone) {
			room_mergeReceivedSessions();
			g_roomSearching = 0;
			g_roomSearchAnswerIn = 0;
			g_roomRefreshing = 0;
		}
	}
	gameList_draw();
	if (!g_roomJoined)
		return;
	if (!g_roomJoinNeedsPassword) {
		room_joinSession(g_pickedGame);
		return;
	}
	if (!g_typingRoomJoinPassword || g_textFieldOpen)
		return;
	g_typingRoomJoinPassword = 0;
	memset((void *)ADDR(g_roomJoinPassword), 0, 8);
	strcpy((char *)ADDR(g_roomJoinPassword), g_chatLine);
	if (strcmp(g_sessionList[g_pickedGame].password, (const char *)ADDR(g_roomJoinPassword)) != 0) {
		menu_showMessage(0x27);
		g_roomJoined = 0;
	}
	g_roomJoinNeedsPassword = 0;
}

/* ---- the SETUP PLAYER dialog (the lobby's player record; its window at 0x4dbb68 .. 0x4dbb74) ---- */

/* text with a near-black shadow one down and right, then in yellow */
static void shadowed(int x, int y, const char *text)
{
	set_colour_bits(g_textColour, 0x3c23d70a, 0x3c23d70a, 0x3c23d70a, 0x3f800000);   /* 0.01 */
	text_draw8(x + 1, y + 1, text);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f4ccccd, 0, 0x3f800000);           /* 1, 0.8, 0 */
	text_draw8(x, y, text);
}

/* 0x409bc0: the SETUP PLAYER dialog: the window, a cyan frame, the title MSG(131, "SETUP PLAYER"), two labels (MSG(132, "PLAYER NAME :"), MSG(134, "MOVE TO ARM-CENTER"))
   and the name g_arenaPlayerName (hidden while it is typed in, g_textFieldOpen); without a message (g_typingArenaName) the name or the
   second label under the pointer (playerSetup_hitTest's 0 / 2) shadowed in yellow; three buttons (MSG(135, "$[0] O K"), 0x80 apart;
   3 .. 5, lit under the pointer), the border. The original leaves eax to callers that ignore it */
void (lobby_drawPlayerSetup)(void)
{
	int x0 = g_playerSetupLeft, y0 = g_playerSetupTop;
	int hovered = playerSetup_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(x0, y0, g_playerSetupRight, g_playerSetupBottom, g_dialogFrameTexture);
	RECT(0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(x0 + 0x20, y0 + 0x30, g_playerSetupRight - 0x20, g_playerSetupBottom - 0x20, 0);
	TEXT(bright);
	text_draw16(x0 + 0x50, y0 + 0x10, (const char *)MSG(131, "SETUP PLAYER"));
	bind_buttons();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	text_draw8(x0 + 0x40, y0 + 0x64, (const char *)MSG(132, "PLAYER NAME :"));
	text_draw8(x0 + 0x40, y0 + 0x96, (const char *)MSG(134, "MOVE TO ARM-CENTER"));
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	if (!g_textFieldOpen)
		text_draw8(x0 + 0xc2, y0 + 0x64, g_arenaPlayerName);
	if (!g_typingArenaName) {
		if (hovered == 0 && !g_textFieldOpen)
			shadowed(x0 + 0xc1, y0 + 0x63, g_arenaPlayerName);
		else if (hovered == 2)
			shadowed(x0 + 0x3f, y0 + 0x95, (const char *)MSG(134, "MOVE TO ARM-CENTER"));
	}
	for (int k = 0; k < 3; k++) {
		int x = g_playerSetupLeft + k * 0x78, y = g_playerSetupTop;
		bind_buttons();
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		button(hovered == k + 3 && !g_typingArenaName, x + 0x32, y + 0xdc, x + 0x96, y + 0xfc, 0.4f);
		text_drawBox16(x + 0x32, g_playerSetupTop + 0xe4, x + 0x96, (const char *)(MSG(135, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(g_playerSetupLeft, g_playerSetupTop, g_playerSetupRight, g_playerSetupBottom);
}

/* ---- the game room's list of games: its mouse ---- */

/* the selection one row up (the list scrolls at the top row) */
static void games_up(void)
{
	int row = g_lobbyListRow;
	if (row > 0)
		g_lobbyListRow = --row;
	else if (g_listTop > 0)
		g_listTop--;
	g_pickedGame = g_listTop + row;
}

/* one row down (nine rows shown), unless at the last game: 0 then */
static int games_down(void)
{
	int row = g_lobbyListRow;
	if (g_listTop + row >= g_gameCount - 1)
		return 0;
	if (row < 8)
		g_lobbyListRow = ++row;
	else
		g_listTop++;
	g_pickedGame = g_listTop + row;
	return 1;
}

/* stop: the search or refresh ended (a refresh: both flags cleared and its answer dropped) */
static void games_stop(void)
{
	sound_playMenu(0);
	(*(u32 *)&g_lobbyBlinkClock) = 0x3f800000;   /* 1 */
	g_gameServerState = 0;
	g_roomSearchAnswerIn = 1;
	if (g_roomRefreshing == 1) {
		g_roomRefreshing = 0;
		g_roomSearching = 0;
		g_roomSearchAnswerIn = 0;
	}
	g_netListDone = 1;
}

/* leave the list; 0 (sound 6) while searching or refreshing */
static int games_leave(void)
{
	if (g_roomSearching || g_roomRefreshing) {
		sound_playMenu(6);
		return 0;
	}
	sound_playMenu(0);
	g_gameServerState = 0;
	g_roomCameraMode = 0;
	g_gameServerPending = 0;
	g_netListDone = 1;
	return 1;
}

/* 0x435fc0: the game room's list of games, its mouse (with the room camera arrived, g_roomCameraMode 2; not while joining, g_roomJoinNeedsPassword,
   or with a message box): a right click leaves the list (unless searching, g_roomSearching). A click (gameList_hitTest) on: 0
   join (not while searching or refreshing, g_roomRefreshing, and only with games; else sound 6), 1 search, 2 stop or
   refresh, 3 leave, 13 / 14 one row up / down, or a row (4 .. 12): selects it, or on the selected row again within
   the double-click time (g_gameListClickArmed) joins it. Holding the button on the arrows scrolls once the blink clock reaches
   5. The original leaves eax to callers that ignore it */
void (gameList_mouse)(void)
{
	int mode = g_roomCameraMode;
	if (mode == 1 || mode == 0 || g_roomJoinNeedsPassword || g_dialogOpen)
		return;
	if (g_rightClick) {
		if (g_roomSearching)
			return;
		sound_playMenu(0);
		g_gameServerState = 0;
		g_roomCameraMode = 0;
		g_gameServerPending = 0;
		return;
	}
	if (g_mouseClick) {
		int on = gameList_hitTest(g_mouseX, g_mouseY);
		if (on == 0) {
			if (g_roomJoined)
				return;
			if (g_roomSearching || g_roomRefreshing || g_gameCount <= 0) {
				sound_playMenu(6);
				return;
			}
			sound_playMenu(0);
			room_askJoinPassword();
			g_roomJoined = 1;
		} else if (on == 1) {
			if (g_roomSearching || g_roomRefreshing) {
				sound_playMenu(6);
				return;
			}
			if (g_roomJoined)
				return;
			g_roomListCount = 0;
			g_lobbyListPage = 0;
			if (gameList_open() == 1) {
				sound_playMenu(0);
				g_roomSearching = 1;
				g_gameListJoinClicked = 1;
			}
		} else if (on == 2)
			games_stop();
		else if (on == 3) {
			if (!games_leave())
				return;
		} else if (on == 13)
			games_up();
		else if (on == 14) {
			if (!games_down())
				return;
		} else if (on >= 4 && on <= 12) {
			int row = on - 4;
			if (g_listTop + row >= g_gameCount)
				return;
			if (row == g_lobbyListRow && g_gameListClickArmed) {
				if (g_gameCount <= 0)
					return;
				if (g_roomSearching || g_roomRefreshing) {
					sound_playMenu(6);
					return;
				}
				if (g_roomJoined)
					return;
				sound_playMenu(0);
				g_gameListClickArmed = 0;
				(*(int *)&g_gameListClickTimer) = 0;
				g_roomJoined = 1;
				room_askJoinPassword();
			} else {
				sound_playMenu(0);
				g_gameListClickArmed = 1;
				(*(int *)&g_gameListClickTimer) = 0;
				g_lobbyListRow = row;
				g_pickedGame = g_listTop + row;
			}
		}
	}
	if (!g_mouseHeld)
		return;
	int on = gameList_hitTest(g_mouseX, g_mouseY);
	if ((on != 13 && on != 14) || !(g_cursorBlink >= k_5f))
		return;
	if (on == 13 || games_down()) {
		if (on == 13)
			games_up();
		g_cursorBlink = 0.0f;
	}
}

/* 0x4372f0: the game room's list of games, its keys (not while joining, g_roomJoinNeedsPassword). With the join confirmation up only
   back answers it (the timer 0x378 killed). g_dikJ or fire joins the selected game (not while searching or
   refreshing, and only with games: else sound 6); g_dikR searches; g_dikS stops; back leaves the list; up / down
   held move the selection (once the blink clock reaches 5, restarting it); cancel2 leaves the room's lists. The
   original leaves eax to callers that ignore it */
void (gameList_keys)(void)
{
	if (g_roomJoinNeedsPassword)
		return;
	if (g_arenaConfirming) {
		if (input_justPressed(g_keyBack)) {
			sound_playMenu(0);
			g_arenaSearchTicks = 0;
			g_arenaJoinWaiting = 0;
			arena_leaveSession();
			g_arenaConfirming = 0;
			KillTimer(g_hWndMain, 0x378);
		}
		return;
	}
	if (input_justPressed(g_dikJ) || input_justPressed(g_keyClick)) {
		if (g_roomJoined)
			return;
		if (g_roomSearching || g_roomRefreshing || g_gameCount <= 0) {
			sound_playMenu(6);
			return;
		}
		sound_playMenu(0);
		g_roomJoined = 1;
		room_askJoinPassword();
		return;
	}
	if (input_justPressed(g_dikR)) {
		if (g_roomSearching || g_roomRefreshing) {
			sound_playMenu(6);
			return;
		}
		g_roomListCount = 0;
		g_lobbyListPage = 0;
		if (gameList_open() == 1) {
			g_roomSearching = 1;
			g_gameListJoinClicked = 1;
			sound_playMenu(0);
		}
		return;
	}
	if (input_justPressed(g_dikS)) {
		games_stop();
		return;
	}
	if (input_justPressed(g_keyBack)) {
		games_leave();
		return;
	}
	if (input_isDown(g_keyUp)) {
		if (g_cursorBlink >= k_5f) {
			sound_playMenu(2);
			g_cursorBlink = 0.0f;
			games_up();
		}
		return;
	}
	if (input_isDown(g_keyDown)) {
		if (g_cursorBlink >= k_5f) {
			sound_playMenu(2);
			g_cursorBlink = 0.0f;
			games_down();
		}
		return;
	}
	if (input_justPressed(g_keyCancel2)) {
		sound_playMenu(0);
		g_roomCameraMode = 0;
		g_gameServerState = 0;
	}
}

/* the searching message's blink clock (g_lobbyBlinkClock) run down, back to 1000 once below k_10f */
static void blink_down(void)
{
	long double blink = fsubr_m(fmul_m(fld_m((const float *)ADDR(g_lobbyBlinkRate)), &g_frameTime), &g_lobbyBlinkClock);
	g_lobbyBlinkClock = f32(blink);
	if (!(blink >= k_10f))
		(*(u32 *)&g_lobbyBlinkClock) = 0x447a0000;   /* 1000 */
}

/* 0x40cfd0: the arena lobby's page of games: the "searching" message's clock (g_arenaSearchClock, while g_arenaListClickArmed), the
   arena tunnel; with the arena camera arrived (g_arenaCameraMode 2) and not on sub-screen 5: a message box (g_dialogOpen) alone, else the
   local network search (g_lanSearch: DirectPlay polled ten times, ended once its clock g_lobbyBlinkClock runs out), the server
   search's end (g_lobbySearching searching, g_serverAnswerIn the answer in, g_searchResult its result -1 .. 4: messages 0x40 / 0x46,
   g_lobbyRefreshing the list to fetch, g_arenaUpdateNotice) and blink, the list's refresh (g_lobbyRefreshing: its timer g_arenaListRefreshTimer against g_listRefreshPeriod,
   a stop g_netListDone); then the list; then a join (g_lobbyJoinStarted: once typed, the password, g_arenaJoinPassword, checked against the
   game's, message 0x27 when wrong; or the join sent, g_arenaJoinNeedsPassword clear), a typed game address (g_typingArenaAddress: joined as
   99999 when not empty) or a join confirmed (g_lobbyJoinRequest). The original leaves eax to callers that ignore it */
void (arena_drawGamesPage)(void)
{
	if (g_arenaListClickArmed) {
		long double t = FADD(g_frameTime, g_arenaSearchClock);
		g_arenaSearchClock = f32(t);
		if (t > k_20f) {
			g_arenaListClickArmed = 0;
			(*(int *)&g_arenaSearchClock) = 0;
		}
	}
	arena_drawTunnel();
	int mode = g_arenaCameraMode;
	if (mode == 1 || mode == 0 || g_lobbySubState == 5)
		return;
	if (g_dialogOpen) {
		menu_drawFrame(g_arenaGameListLeft, g_arenaGameListTop, g_arenaGameListRight, g_arenaGameListBottom);
		return;
	}
	if (g_lanSearch) {
		for (int k = 0; k < 10; k++)
			dplay_listSessions();
		long double t = fsubr_m(fmul_m(fld_m((const float *)ADDR(g_lobbyBlinkRate)), &g_frameTime), &g_lobbyBlinkClock);
		g_lobbyBlinkClock = f32(t);
		if (!(t > k_0f)) {
			arenaList_rebuild();
			g_lanSearch = 0;
		}
	}
	if (g_lobbySearching) {
		if (g_serverAnswerIn == 1) {
			int result = g_searchResult;
			if (result != 2 && (u32)(result + 1) <= 5) {
				g_lobbySearching = 0;
				g_serverAnswerIn = 0;
				g_lobbyRefreshing = result == 1;
				if (result == 3)
					g_arenaUpdateNotice = 1;
				else if (result == 0)
					menu_showMessage(0x40);
				else if (result == 4)
					menu_showMessage(0x46);
			}
		}
		blink_down();
	}
	if (g_lobbyRefreshing) {
		long double t = FADD(g_arenaListRefreshTimer, g_frameTime);
		g_arenaListRefreshTimer = f32(t);
		if (t > (long double)g_listRefreshPeriod) {
			arena_mergeReceivedSessions();
			(*(int *)&g_arenaListRefreshTimer) = 0;
			g_listRefreshPeriod = 5;
		}
		blink_down();
		if (g_netListDone) {
			arena_mergeReceivedSessions();
			g_lobbySearching = 0;
			g_serverAnswerIn = 0;
			g_lobbyRefreshing = 0;
		}
	}
	arena_drawGameList();
	if (g_lobbyJoinStarted) {
		if (!g_arenaJoinNeedsPassword) {
			arena_joinListed(g_pickedGame);
			return;
		}
		if (!g_typingArenaJoinPassword || g_textFieldOpen)
			return;
		memset((void *)ADDR(g_arenaJoinPassword), 0, 8);
		g_typingArenaJoinPassword = 0;
		strcpy((char *)ADDR(g_arenaJoinPassword), g_chatLine);
		int wrong = strcmp(g_sessionList[g_pickedGame].password, (const char *)ADDR(g_arenaJoinPassword)) != 0;
		if (wrong)
			g_lobbyJoinStarted = 0;
		g_arenaJoinNeedsPassword = 0;
		if (wrong)
			menu_showMessage(0x27);
		return;
	}
	if (g_typingArenaAddress) {
		if (g_textFieldOpen)
			return;
		g_typingArenaAddress = 0;
		memset((void *)ADDR(g_typedArenaAddress), 0, 6 * 4);
		strcpy((char *)ADDR(g_typedArenaAddress), g_chatLine);
		if (g_typedArenaAddress)
			arena_joinListed(99999);
	}
	if (g_lobbyJoinRequest)
		arena_joinSession(g_pickedGame);
}

/* ---- the arena lobby's list of games: its mouse ---- */

/* the lobby busy: searching, connecting (g_lobbySearching) or refreshing (g_lobbyRefreshing) */
static int lobby_busy(void)
{
	return g_lanSearch || g_lobbySearching || g_lobbyRefreshing;
}

/* the selected game joined: connected to the server (g_serverConnected), its join password asked for when it is locked
   (arena_askJoinPassword; g_lobbyJoinStarted), else the join asked of the lobby (g_lobbyJoinRequest) */
static void lobby_join(void)
{
	sound_playMenu(0);
	if (g_serverConnected) {
		g_lobbyJoinStarted = 1;
		g_lobbyJoinRequest = 0;
		arena_askJoinPassword();
	} else {
		g_lobbyJoinRequest = 1;
		g_lobbyJoinStarted = 0;
	}
}

/* the lobby left for the arena screen's first page (g_lobbyBlinkClock 1; g_serverAnswerIn set) */
static void lobby_leave(void)
{
	g_serverConnectionState = 0;
	sound_playMenu(0);
	(*(u32 *)&g_lobbyBlinkClock) = 0x3f800000;   /* 1 */
	g_serverAnswerIn = 1;
}

/* 0x406c30 (the arena lobby's list of games, its mouse: with the arena camera arrived (g_arenaCameraMode 2), not
   while joining, with the address box or a message box). A right click (not while searching or connecting) drops the
   connection and the mode. A click (arenaGameList_hitTest) on: 0 search the network (DirectPlay, arena_openSession), 1 connect to
   the lobby server (lobby_openConnection), 2 a game's IP address typed (arena_editAddress), 3 join (with games; not while busy), 4 back (a
   refresh in progress ended), 5 leave the lobby (mode 0), 15 / 16 one row up / down, or a row (6 .. 14): selects
   it, or on the selected row again (g_arenaListClickArmed) joins it. A busy lobby answers sound 6. Holding the button on the
   arrows scrolls once the blink clock reaches 5. The caller ignores the eax it leaves */
void (arenaGames_mouse)(void)
{
	int mode = g_arenaCameraMode;
	if (mode == 1 || mode == 0 || g_arenaJoinNeedsPassword || g_typingArenaAddress || g_dialogOpen)
		return;
	if (g_rightClick) {
		if (g_lobbySearching || g_lanSearch)
			return;
		g_serverConnectionState = 0;
		arena_leaveSession();
		net_disconnect();
		sound_playMenu(0);
		g_arenaCameraMode = mode = 0;
	}
	if (g_mouseClick && mode == 2) {
		g_cursorBlink = 0.0f;
		int on = arenaGameList_hitTest(g_mouseX, g_mouseY);
		switch (on) {
		case 0:
		case 1:
			if (lobby_busy()) {
				sound_playMenu(6);
				return;
			}
			if (g_typingArenaAddress)
				return;
			sound_playMenu(0);
			if (on == 0) {
				if (g_serverSearching) {
					g_lobbyConnectionOpen = 0;
					net_disconnect();
				}
				if (g_arenaSearchStarted)
					arena_leaveSession();
				g_serverListCount = 0;
				arena_openSession(1, NULL);
				g_lobbyListPage = 0;
				g_lanSearch = 1;
				(*(u32 *)&g_lobbyBlinkClock) = 0x43160000;   /* 150 */
				g_gameCount = 0;
				g_serverConnected = 0;
				g_arenaSearchStarted = 1;
				g_serverSearching = 0;
			} else {
				g_lobbyConnectionOpen = 0;
				net_disconnect();
				arena_leaveSession();
				g_serverListCount = 0;
				if (lobby_openConnection() == 1) {
					g_serverConnected = 1;
					g_lobbySearching = 1;
					g_serverSearching = 1;
					g_arenaSearchStarted = 0;
					g_lobbyConnectionOpen = 1;
				}
			}
			break;
		case 2:
			if (g_typingArenaAddress)
				return;
			sound_playMenu(0);
			arena_editAddress();
			break;
		case 3:
			if (lobby_busy()) {
				sound_playMenu(6);
				return;
			}
			if (g_typingArenaAddress)
				return;
			if (g_gameCount <= 0) {
				sound_playMenu(6);
				return;
			}
			lobby_join();
			break;
		case 4:
			if (g_typingArenaAddress)
				return;
			lobby_leave();
			g_searchResult = -1;
			g_lobbyConnectionOpen = 0;
			arena_leaveSession();
			net_disconnect();
			if (g_lobbyRefreshing == 1) {
				g_lobbyRefreshing = 0;
				g_lobbySearching = 0;
				g_serverAnswerIn = 0;
			}
			g_netListDone = 1;
			break;
		case 5:
			if (lobby_busy()) {
				sound_playMenu(6);
				return;
			}
			if (g_typingArenaAddress)
				return;
			lobby_leave();
			arena_leaveSession();
			net_disconnect();
			g_arenaCameraMode = 0;
			g_netListDone = 1;
			break;
		case 15:
			if (g_typingArenaAddress)
				return;
			games_up();
			break;
		case 16:
			if (g_typingArenaAddress)
				return;
			if (!games_down())
				return;
			break;
		default:
			if (on < 6 || on > 14)
				break;
			if (g_typingArenaAddress)
				return;
			int row = on - 6;
			if (g_listTop + row >= g_gameCount)
				return;
			if (row == g_lobbyListRow && g_arenaListClickArmed) {
				if (g_gameCount <= 0)
					return;
				if (lobby_busy()) {
					sound_playMenu(6);
					return;
				}
				lobby_join();
				g_arenaListClickArmed = 0;
			} else {
				sound_playMenu(0);
				g_arenaListClickArmed = 1;
				g_lobbyListRow = row;
				g_pickedGame = g_listTop + row;
			}
			(*(int *)&g_arenaSearchClock) = 0;
			break;
		}
	}
	if (!g_mouseHeld || g_arenaCameraMode != 2 || g_typingArenaAddress)
		return;
	int on = arenaGameList_hitTest(g_mouseX, g_mouseY);
	if ((on != 15 && on != 16) || !(g_cursorBlink >= k_5f))
		return;
	if (on == 15 || games_down()) {
		if (on == 15)
			games_up();
		g_cursorBlink = 0.0f;
	}
}
