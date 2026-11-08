/* menu_states.c: the front end's screens' frames and dispatch: the intro, the main menu with its replay selection
   dialog, the profile, setup and game-room frames, the 3D background, the mission list's and skirmish screen's pages
   and keys, the panels sliding in, and the way back to the menus after a match or a lost server. */
#include "../game.h"
#include "key_repeat.h"

/* ---- the start-up screen: the logo (texture g_logoTexture, on a quad 320 x 256 at (160, 60)) over the clear colour
   g_clearColour, blended. first sets alpha 0.6, but the white (1, 1, 1, 1) set before the quad overrides it (in the
   original too): the logo is never dimmed ---- */
static void draw_logo(int first)
{
	const u32 *clear = (const u32 *)OBJ(g_clearColour);
	glClearColor_bits(clear[0], clear[1], clear[2], clear[3]);   /* glClearColor */
	glClear(0x4100);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(0xbe2);   /* GL_BLEND */
	if (first)
		glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
	glBlendFunc(0x302, 0x303);   /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int texture = g_logoTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	menu_vertex(0xa0, 0x3c);
	glTexCoord2d(1.0, 0.0);
	menu_vertex(0x1e0, 0x3c);
	glTexCoord2d(1.0, 1.0);
	menu_vertex(0x1e0, 0x13c);
	glTexCoord2d(0.0, 1.0);
	menu_vertex(0xa0, 0x13c);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

/* v kept within 0 .. 1 (a NaN becomes 0) */
static float unit(float v)
{
	if (!(v >= *&k_0f))
		v = 0;
	if (v > *&k_1f)
		v = 1;
	return v;
}

/* one pixel column of the progress bar at x in the colour (r, g, b) */
static void bar_column(int x, float r, float g, float b)
{
	set_colour_bits(g_rectColour, BITS(r), BITS(g), BITS(b), 0x3f800000);
	menu_drawRect(x, 0x1da, x + 1, 0x1de, 1);
}

/* 0x41f100: the start-up screen at progress g_loadStep (16 pixels a step): the logo, then a bar of that many columns
   below it, red to blue over the first 200, blue to green over the next 200, green to yellow after that. Returns
   SwapBuffers' answer */
int (frontEnd_drawProgress)(void)
{
	draw_logo(0);
	int n = g_loadStep * 16;
	for (int i = 0; i < n && i < 200; i++) {
		long double f = (long double)i;
		float r = f32(fsubr_m(fmul_m(f, k_0_005f), &k_1f));   /* 1 - i * 0.005 */
		float b = f32(fmul_m(f, &k_0_0051f));                         /* i * 0.0051 */
		bar_column(i + 0x14, unit(r), 0.0f, unit(b));
	}
	if (n > 200)
		for (int i = 0; i + 200 < 400 && i + 200 < n; i++) {
			long double t = fmul_m((long double)i, k_0_005f);
			float g = f32(t), b = f32(1.0L - t);
			bar_column(i + 0xdc, 0.0f, unit(g), unit(b));
		}
	if (n > 400) {
		int i = 0;
		do {
			long double t = fmul_m((long double)i, &k_0_01f);      /* i * 0.01 */
			float r = f32(t), g = f32(fadd_m(t, &k_1f));
			bar_column(i + 0x1a4, unit(r), unit(g), 0.0f);
			i++;
		} while (i + 400 < n);
	}
	glFinish();
	return SwapBuffers(g_windowDC);
}

/* 0x41f540: the intro: the start-up logo shown once (draw_logo's dimming has no effect), then the loading picture stepped four times (g_loadStep) around the start-up loads, with
   waits of 5 and 2 (1/60 s); then the title screen (200) with the front end's state reset, the pointer at
   (310, 230), the Netsphere music and the frame clocks cleared */
void (menuState100_intro)(void)
{
	g_titleClosing = 0;
	g_titleCloseFrames = 0;
	g_loadStep = 0;
	draw_logo(1);
	glFinish();
	SwapBuffers(g_windowDC);
	set_colour_bits(g_textColour, 0x3f800000, 0, 0, 0x3f800000);   /* red text */
	g_loadStep++;
	frontEnd_drawProgress();
	timer_waitFrames(5.0);
	tunnel_restart();
	g_loadStep++;
	frontEnd_drawProgress();
	timer_waitFrames(2.0);
	menu_loadTextures();
	frontEnd_startUp();
	g_loadStep++;
	frontEnd_drawProgress();
	shared_emptyFunction(NULL);   /* (an empty function) */
	g_loadStep++;
	frontEnd_drawProgress();
	g_screen = 200;
	g_lastScreen = 200;
	static const u32 cleared[] = { ADDR(g_titleClosing), ADDR(g_titleCloseFrames), ADDR(g_menuCameraMove), ADDR(g_unusedMenuReturnWord), ADDR(g_cursorFrame), ADDR(g_cursorFrameTime), ADDR(g_tunnelStripeScroll), ADDR(g_tunnelPulse), ADDR(g_replayZoomTime) };
	for (unsigned i = 0; i < sizeof cleared / sizeof cleared[0]; i++)
		GAME_VAR(u32, cleared[i]) = 0;
	(*(u32 *)&g_menuTunnelSpeed) = 0x3f800000;   /* 1.0 */
	(*(u32 *)&g_tunnelPulseStep) = 0x3f800000;
	g_mouseX = 0x136;
	g_mouseY = 0xe6;
	music_play((const char *)STR(0x4b01cc, "music/Netsphere.mp3"));
	static const u32 clocks[] = { ADDR(g_unusedClock1), ADDR(g_unusedClock2), ADDR(g_unusedClock3), ADDR(g_lastFrameClock) };   /* four doubles */
	for (int i = 0; i < 4; i++) {
		GAME_VAR(u32, clocks[i]) = 0;
		GAME_VAR(u32, clocks[i] + 4) = 0;
	}
}

/* 0x441740: the 3D background behind the menus: the tunnel's rings moved on (menuTunnel_advance) and drawn */
void (menu_drawBackground)(void)
{
	menuTunnel_advance(g_menuTunnel);
	gfx_setProjection2D3D(1);
	menu_drawBackground3D(g_menuTunnel);
}

/* 0x442e10: the replay selection dialog (0x9dd908 .. 0x9dd914): the window, its title MSG(21, "SELECT RECORDED GAME"), the list's frame with
   its scroll arrows (0 / 1 under the pointer, by replaySelect_hitTest), two tick boxes (g_replayWrap: MSG(22, "AUTO REPEAT"), g_replayRandomOrder:
   MSG(23, "RANDOM PLAY")), two rows of two buttons (MSG(24, "$[0] ALL FILES") lit from 4, MSG(26, "$[0] O K") from 6), the list row under the pointer
   (8 .. 0x11) highlighted, the list (replaySelect_drawNames) and the border. The original leaves eax to callers that
   ignore it */
void (replaySelect_drawDialog)(void)
{
#define X0 g_replaySelectLeft
#define Y0 g_replaySelectTop
#define X1 g_replaySelectRight
#define Y1 g_replaySelectBottom
	const u32 *bright = (const u32 *)ADDR(g_replaySelectLitR), *dim = (const u32 *)ADDR(g_replaySelectDimR);
	int hovered = replaySelect_hitTest(g_mouseX, g_mouseY);
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)MSG(21, "SELECT RECORDED GAME"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(X0 + 0x10, Y0 + 0x28, X1 - 0x40, Y0 + 0xf5, 0);
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawUpArrow(X1 - 0x32, Y0 + 0x48, X1 - 0x12, Y0 + 0x88, hovered == 0);
	menu_drawDownArrow(X1 - 0x32, Y0 + 0xac, X1 - 0x12, Y0 + 0xec, hovered != 0 && hovered == 1);
	glDisable(GL_TEXTURE_2D);
	const int *ticked[2] = { (const int *)ADDR(g_replayWrap), (const int *)ADDR(g_replayRandomOrder) };
	for (int k = 0; k < 2; k++) {
		int y = Y0 + 0xfe + k * 0x1e;
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(X0 + 0x10, y, X0 + 0x20, y + 0x10, 0);
		if (*ticked[k]) {
			set_colour_bits(g_rectColour, 0x3f800000, 0, 0, 0x3f800000);
			menu_drawRect(X0 + 0x12, y + 2, X0 + 0x1d, y + 0xd, 1);
		}
		set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
		text_draw16(X0 + 0x28, k ? y : y + 2, (const char *)(MSG(22, "AUTO REPEAT") + k * 0x80));   /* (the second label 2 higher) */
	}
	for (int row = 0; row < 2; row++)
		for (int k = 0; k < 2; k++) {
			glEnable(GL_TEXTURE_2D);
			texture = g_buttonTexture;
			tex_bind(g_textures->banks[texture / 512], texture % 512);
			int lit = hovered == 4 + row * 2 + k;
			glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
			int x = X0 + k * 0xa0, y = Y1 - 0x5c + row * 0x28;
			menu_drawWideButton(x + 0x64, y, x + 0xdc, y + 0x20, 1);
			const u32 *colour = lit ? bright : dim;
			set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
			text_drawCentredLines16(x + 0x64, y + 8, x + 0xdc, (const char *)(MSG(24, "$[0] ALL FILES") + row * 0x100 + k * 0x80));
		}
	if (hovered > 7 && hovered < 0x12) {
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e99999a, 0x3f800000, 0x3e99999a);   /* 0.1, 0.3, 1, 0.3 */
		menu_drawRect(X0 + 0x20, Y0 + hovered * 20 - 0x75, X1 - 0x50, Y0 + hovered * 20 - 0x63, 1);
	}
	replaySelect_drawNames();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x4434f0: the replay selection dialog of the main menu (only its frame while a dialog is up) */
void (mainmenu_drawReplaySelect)(void)
{
	if (g_frameOpening != 0)
		menu_drawFrameOpening(g_replaySelectLeft, g_replaySelectTop, g_replaySelectRight, g_replaySelectBottom);
	else
		replaySelect_drawDialog();
}

/* 0x443530: the main menu's frame: background, menu (mainmenu_drawMenu), the replay selection dialog when open; while the
   menus are being left for a match (g_leavingForMatch 1) the camera's move 1 (in), the next screen 9999 and the white
   fade (menu_drawWhiteFade) */
void (menuState300_frame)(void)
{
	menu_drawBackground();
	mainmenu_drawMenu();
	if (g_replaySelectOpen != 0)
		mainmenu_drawReplaySelect();
	if (g_leavingForMatch == 1) {
		menuCamera_setMove(1);
		g_nextScreen = 9999;
		menu_drawWhiteFade();
	}
}

/* 0x443ef0: the mission list's clicks (screen 900; none while a dialog is up): page 10 the list (missions_listClicks), 20 the
   briefing (missions_briefingClicks) */
void (missions_pageClicks)(void)
{
	if (g_frameOpening != 0)
		return;
	if (g_missionsPage == 10)
		missions_listClicks();
	else if (g_missionsPage == 20)
		missions_briefingClicks();
}

/* 0x4440f0: the mission list's keys (screen 900), by page (10 the list, 20 the briefing) */
void (missions_pageKeys)(void)
{
	if (g_missionsState == 1 || g_missionsState == 0 || g_frameOpening != 0)
		return;
	if (g_missionsPage == 10)
		missions_listKeys();
	else if (g_missionsPage == 20)
		missions_briefingKeys();
}

/* 0x4479b0: round chosen (g_skirmishChosen), its map preview to be loaded, sound 2 */
void (skirmish_roundChosen)(int round)
{
	g_skirmishChosen = round;
	g_skirmishPreviewDue = 1;
	sound_playMenu(2);
}

/* 0x447b10: the skirmish screen's clicks (none while a dialog is up or it is busy): the new-parts notice's close, else the list's (skirmish_clicks) */
void (skirmish_screenClicks)(void)
{
	if (g_frameOpening != 0 || g_skirmishLeft != 0)
		return;
	if (g_skirmishNewPartsNotice != 0)
		newPartsNotice_clickClose();
	else
		skirmish_clicks();
}

/* 0x447c30: the new-parts notice's keys: Esc or Enter closes it */
void (newPartsNotice_keys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1 || input_justPressed(g_keyClick) == 1)
		g_skirmishNewPartsNotice = 0;
}

/* 0x447b40: the skirmish screen's round keys: Esc or back leaves (skirmish_leave), O starts the round shown
   (skirmish_startRound), left / right step the round shown (g_skirmishRoundShown, 0 .. 14) through those unlocked so
   far (g_progress), and Left Ctrl + Right Alt + Page Up unlocks them all (g_progress 16) */
void (skirmish_roundKeys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		skirmish_leave();
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		skirmish_startRound();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		skirmish_leave();
		return;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_skirmishRoundShown > 0)
		skirmish_roundChosen(--g_skirmishRoundShown);
	if (input_justPressed(g_keyRight) == 1 && g_skirmishRoundShown < g_progress) {
		if (g_skirmishRoundShown >= 14)
			return;
		skirmish_roundChosen(++g_skirmishRoundShown);
	}
	if (input_isDown(g_keyLeftCtrl) && input_isDown(g_dikRAlt) && input_justPressed(g_dikPageUp))
		g_progress = 16;
}

/* 0x447c70: the skirmish screen's keys (not while a dialog is up) */
void (skirmish_keys)(void)
{
	if (g_skirmishState == 1 || g_skirmishState == 0 || g_frameOpening != 0 || g_skirmishLeft != 0)
		return;
	if (g_skirmishNewPartsNotice != 0)
		newPartsNotice_keys();
	else
		skirmish_roundKeys();
}

/* 0x41edc0: the lobby server's socket closed (WndProc 0x40a FD_CLOSE on g_lobbySocket, not in a match): the background tunnel freed
   ring by ring, then game_returnToArenaLobby (screen 300 for now, next screen 400, the camera's move 2 into it),
   g_screen 300 */
void (menu_returnToArenaLobbyViaMain)(void)
{
	while (g_menuTunnel != NULL)
		armc_freeRing(&g_menuTunnel);
	game_returnToArenaLobby();
	g_screen = 300;
}

/* 0x41ed70: the game server's socket closed (WndProc 0x40c FD_CLOSE on g_gameServerSocket, not in a match): back to
   the main menu from the game room: the background tunnel freed, the menus entered again, the
   room's state cleared, state 300 */
void (menu_returnToMainFromRoom)(void)
{
	while (g_menuTunnel != NULL)
		armc_freeRing(&g_menuTunnel);
	game_returnToMainMenu();
	g_roomRequestOut = 0;
	g_newIdAnswerAwaited = 0;
	g_unusedRoomWord = 0;
	g_accountRankAwaited = 0;
	g_screen = 300;
}

/* 0x441770: the replay selection dialog's OK: if any replay is picked (g_replayList), the menu sound,
   g_replayListCount = g_replayFileCount, the dialog closed and the show of the picked replays started (g_replayShowOn
   1) */
void (replaySelect_ok)(void)
{
	int count = g_replayFileCount;
	for (int i = 0; i < count; i++)
		if (g_replayList[i].picked == 1) {
			sound_playMenu(0);
			g_replayListCount = g_replayFileCount;
			g_replayShowOn = 1;
			g_replaySelectOpen = 0;
			return;
		}
}

/* ---- the replay selection dialog's list: 10 rows shown from replay g_replaySelectFirst of the g_replayFileCount ---- */
static void replaySelect_scrollUp(void)
{
	if (g_replaySelectFirst > 0) {
		g_replaySelectFirst--;
		sound_playMenu(2);
	}
}
static void replaySelect_scrollDown(void)
{
	if (g_replaySelectFirst + 10 < g_replayFileCount) {
		g_replaySelectFirst++;
		sound_playMenu(2);
	}
}

/* 0x441c00: the replay selection dialog's keys: cancel or back closes it (g_replaySelectOpen), OK takes the choice (replaySelect_ok),
   g_dikR toggles g_replayRandomOrder, g_dikD / g_dikA take every replay out / in, up / down scroll the list with a key
   repeat (the original leaves eax to callers that ignore it) */
void (replaySelect_keys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		sound_playMenu(0);
		g_replaySelectOpen = 0;
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		replaySelect_ok();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		g_replaySelectOpen = 0;
		return;
	}
	if (input_justPressed(g_dikR) == 1) {
		sound_playMenu(0);
		g_replayRandomOrder = 1 - g_replayRandomOrder;
		return;
	}
	if (input_justPressed(g_dikD) == 1) {
		sound_playMenu(0);
		replaySelect_allOut();
		return;
	}
	if (input_justPressed(g_dikA) == 1) {
		sound_playMenu(0);
		replaySelect_allIn();
		return;
	}
	if (!key_repeat(g_keyUp, &g_repeatUp, replaySelect_scrollUp))
		key_repeat(g_keyDown, &g_repeatDown, replaySelect_scrollDown);
}

/* 0x441810: the replay selection dialog's mouse: a click (the repeat clock g_menuRepeatClock restarted) on the arrows
   (0 / 1), the two toggles (g_replayWrap, g_replayRandomOrder), every replay in or out, OK, cancel (7), or a row's
   replay (8 .. 17); holding an arrow scrolls once the clock reaches 5 (k_5f), restarting it. The original leaves eax
   to callers that ignore it */
void (replaySelect_mouse)(void)
{
	const float *repeat = (const float *)ADDR(k_5f);
	if (g_mouseClick) {
		g_menuRepeatClock = 0.0f;
		int on = replaySelect_hitTest(g_mouseX, g_mouseY);
		if (on == 0)
			replaySelect_scrollUp();
		else if (on == 1)
			replaySelect_scrollDown();
		else if (on == 2)
			g_replayWrap = 1 - g_replayWrap;
		else if (on == 3)
			g_replayRandomOrder = 1 - g_replayRandomOrder;
		else if (on == 4)
			replaySelect_allIn();
		else if (on == 5)
			replaySelect_allOut();
		else if (on == 6)
			replaySelect_ok();
		else if (on == 7)
			g_replaySelectOpen = 0;
		else if (on >= 8 && on < 18) {
			sound_playMenu(2);
			replaySelect_toggle(g_replaySelectFirst + on - 8);
		}
	}
	if (!g_mouseHeld)
		return;
	int on = replaySelect_hitTest(g_mouseX, g_mouseY);
	if ((on == 0 || on == 1) && g_menuRepeatClock >= *repeat) {
		if (on == 0)
			replaySelect_scrollUp();
		else
			replaySelect_scrollDown();
		g_menuRepeatClock = 0.0f;
	}
}

/* 0x44f860: the profile screen's frame: once the log-out was confirmed (g_profileQuitting) the game quits
   (app_quitGame); else the background and, once the zoom (g_replayZoomTime) is not above 0, the pilot table reloaded
   (data_loadCharacterProfiles) for every stat of the first nine pilots that is out of range (above 30, stat 7 above
   50), then the page (g_profilePage 1 .. 6: profile_listPage, profile_newNamePage, profile_deletePage, profile_logIn,
   profile_logOutPage, pilotSelect_page = the pilot select) */
void (menuState210_frame)(void)
{
	if (g_profileQuitting) {
		app_quitGame();
		return;
	}
	menu_drawBackground();
	if (g_replayZoomTime > k_0f)
		return;
	static const signed char stats[9] = { 0, 2, 3, 1, 5, 4, 6, 8, 7 };   /* in the order checked */
	for (int p = 0; p < 9; p++)   /* (the first nine profiles: any value past its limit reloads them all) */
		for (int f = 0; f < 9; f++)
			if (((CharacterProfile *)g_characterProfiles)[p].stats[stats[f]] > (stats[f] == 7 ? 50 : 30))
				data_loadCharacterProfiles();
	static const u32 pages[6] = { FN(profile_listPage), FN(profile_newNamePage), FN(profile_deletePage), FN(profile_logIn), FN(profile_logOutPage), FN(pilotSelect_page) };
	u32 page = (*(u32 *)&g_profilePage) - 1;
	if (page <= 5)
		GAME_CDECL(pages[page], void, void)();   /* profile_listPage .. pilotSelect_page */
}

/* 0x427920: the setup screen's frame: the background, then by tab the screen with its page, or the top page */
void (menuState600_setup)(void)
{
	menu_drawBackground();
	switch (g_setupTab) {
	case 2: setup_camera(); setup_frameControlsPage(); break;
	case 0: setup_camera(); setup_frameSoundPage(); break;
	case 1: setup_camera(); setup_frameGraphicPage(); break;
	case 0x29a: setup_easePanel(); setup_drawMenu(); break;
	}
}

/* 0x44aee0: the Ladder ID (g_ladderId) put into the Ladder record (g_ladderName), and the record checked and sent
   (ladder_checkAndSendRecord) when it is not empty */
void (ladder_sendRecord)(void)
{
	const char *from = g_ladderId;
	char *to = g_ladderName;
	int i = 0;
	do
		to[i] = from[i];
	while (from[i++] != '\0');
	if (to[0] != '\0')
		ladder_checkAndSendRecord();
}

/* a panel sliding in: while flag is set, eased moves a tenth of the way to the constant at k_panelSlideTarget per time unit
   and slid moves back by the same step, until slid is no longer above the double at k_panelSlideEnd (then the flag drops
   and slid is set to -1650). Afterwards, while leaving for a match (g_leavingForMatch), the camera's move 1 (menuCamera_setMove) and the next
   screen 9999 (returns 1) */
static int menu_slide(u32 flag, u32 eased, u32 slid)
{
	if (GAME_VAR(int, flag)) {
		volatile long double d = (long double)k_panelSlideTarget - GAME_VAR(float, eased);
		d = d * g_frameTime;
		d = d * k_0_1f;
		volatile long double e = (long double)GAME_VAR(float, eased) + d;
		GAME_VAR(float, eased) = (float)e;
		long double s = GAME_VAR(float, slid);
		if (s > k_panelSlideEnd) {
			volatile long double t = s - d;
			GAME_VAR(float, slid) = (float)t;
		} else {
			GAME_VAR(int, flag) = 0;
			GAME_VAR(u32, slid) = 0xc4ce4000;   /* -1650.0 */
		}
	}
	if (!g_leavingForMatch)
		return 0;
	menuCamera_setMove(1);
	g_nextScreen = 9999;
	return 1;
}

/* 0x40cef0: the arena lobby's panels sliding in (menu_slide on g_lobbyPanelsSliding / g_lobbySlideEase /
   g_arenaTunnelDepth); while leaving for a match (g_leavingForMatch) the camera's move 1 and next screen 9999
   (returns 1). Caller menuState400_frame */
int (lobby_slidePanels)(void) { return menu_slide(ADDR(g_lobbyPanelsSliding), OBJ(g_lobbySlideEase), ADDR(g_arenaTunnelDepth)); }
int (room_slideMenu)(void) { return menu_slide(ADDR(g_roomPanelsSliding), ADDR(g_roomSlideEase), ADDR(g_roomTunnelDepth)); }

/* ---- back to the menus after a game: the arena session left (dplay_leaveSession) and, unless kept, the connection closed;
   the player slots (0x410 bytes from g_netSlots) emptied ---- */
static void leave_game(u32 matchMode, int disconnect)
{
	g_leavingForMatch = 0;
	(*(u32 *)&g_matchMode) = matchMode;
	dplay_leaveSession();
	if (disconnect)
		net_disconnect();   /* net_disconnect */
	g_hostingState = 0;
	for (NetSlot *p = g_netSlots; p < g_netSlots + 16; p++) {
		p->used = 0;
		p->id = 0;
	}
}
/* the menu camera placed: its eye at (0, 0, eyeZ) looking at (0, 0, lookZ) (float bits; the kept place too), its move
   state g_menuCameraMove = cameraMove (which also holds off the menus' keys and mouse), g_enteringMenus set, and
   g_inputLineHidden cleared when showInputLine; the menu state cleared and the keyboard taken back if it was let go.
   Returns what the original leaves in eax: input_initKeyboard's, or g_textFieldOpen's value */
static u32 reset_menus(u32 eyeZ, u32 lookZ, int cameraMove, int entering, int showInputLine)
{
	u32 typing = (*(u32 *)&g_textFieldOpen);
	(*(u32 *)&g_menuEyeY) = 0;
	(*(u32 *)&g_menuEyeX) = 0;
	(*(u32 *)&g_menuEyeZ) = eyeZ;
	(*(u32 *)&g_menuCameraLook) = 0;
	(*(u32 *)&g_menuCameraLookY) = 0;
	(*(u32 *)&g_menuCameraLookZ) = lookZ;
	g_menuCameraMove = cameraMove;
	g_unusedMenuReturnWord = 0;
	(*(u32 *)&g_menuEyeKeptX) = 0;
	(*(u32 *)&g_menuEyeKeptY) = 0;
	(*(u32 *)&g_menuEyeKeptZ) = eyeZ;
	(*(u32 *)&g_menuLookKeptX) = 0;
	(*(u32 *)&g_menuLookKeptY) = 0;
	(*(u32 *)&g_menuLookKeptZ) = lookZ;
	g_enteringMenus = entering;
	g_replayRunning = 0;
	(*(int *)&g_menuRepeatClock) = 0;
	(*(int *)&g_replayZoomTime) = 0;
	if (showInputLine)
		g_inputLineHidden = 0;
	if (typing != 1)
		return typing;
	g_textFieldOpen = 0;
	input_resetKeys();
	return ((u32)input_initKeyboard(g_mainWindow));   /* input_initKeyboard */
}
#define FAR_BACK 0xc3e10000u    /* -450: the eye's z */
#define NEAR_BACK 0xc4098000u   /* -550: the look-at's z */

/* 0x41ec50: back to the skirmish screen (screen 500) */
u32 (game_returnToSkirmish)(void)
{
	leave_game(0, 1);
	g_menuState = 500;
	g_nextScreen = 500;
	tunnel_restart();
	tunnel_addRing();
	return reset_menus(FAR_BACK, NEAR_BACK, 0, 0, 0);
}

/* 0x41e8b0: to the main menu (300), the cameras in front (500, 400), g_enteringMenus set and g_inputLineHidden cleared. Returns 1
   when the keyboard was not let go */
u32 (game_returnToMainMenu)(void)
{
	leave_game(0, 1);
	g_menuState = 300;
	g_nextScreen = 300;
	tunnel_restart();
	u32 typing = (*(u32 *)&g_textFieldOpen);
	u32 r = reset_menus(0x43fa0000, 0x43c80000, 2, 1, 1);
	return typing == 1 ? r : 1;
}

/* 0x41e9d0: to the arena lobby (screen 400), the previous screen the main menu (300) */
u32 (game_returnToArenaLobby)(void)
{
	leave_game(0, 1);
	g_nextScreen = 400;
	g_menuState = 300;
	g_lastScreen = 300;
	tunnel_restart();
	tunnel_addRing();
	return reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
}

/* 0x41eb00: back to the game room (800; g_matchMode left at 2, the connection kept): g_roomState 99 (the room's
   menu), the room's flags cleared too */
u32 (game_returnToGameRoom)(void)
{
	leave_game(2, 0);
	g_roomState = 0x63;
	g_menuState = 800;
	g_nextScreen = 800;
	g_lastScreen = 800;
	tunnel_restart();
	tunnel_addRing();
	u32 r = reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
	g_retypePassword = 0;
	g_hostGameSetUp = 0;
	g_roomLoginDue = 0;
	g_rankingRequestPending = 0;
	return r;
}

/* 0x43ef70: the game room's frame. While the pointer glides (g_pointerGliding) it moves a quarter of the way to
   g_pointerGlideX / Y per time unit until g_pointerGlideTime runs out. Then by g_roomState: 0 account, 1 game list, 2
   the create-game page (CREATE LADDER GAME), 4 ranking -- over the background with the room's camera; 66 login, 77 new-ID form, 88 new-ID
   confirmation: updated, background, drawn; 99 the room's menu: panels slid (room_slideMenu), background, then the
   white fade (room_drawWhiteFade) while leaving for a match with the camera arrived, else room_drawMenu. Returns the
   last call's eax, or the page */
u32 (menuState800_gameRoom)(void)
{
	if (g_pointerGliding) {
		int *mouse = (int *)ADDR(g_mouseX);
		mouse[0] += ftol(fmul_m(fmul_m((long double)(g_pointerGlideX - mouse[0]), (const float *)ADDR(g_frameTime)), (const float *)ADDR(k_0_25f)));
		mouse[1] += ftol(fmul_m(fmul_m((long double)(g_pointerGlideY - mouse[1]), (const float *)ADDR(g_frameTime)), (const float *)ADDR(k_0_25f)));
		long double timeLeft = fsub_m(fld_m((const float *)ADDR(g_pointerGlideTime)), (const float *)ADDR(g_frameTime));
		g_pointerGlideTime = f32(timeLeft);
		if (!(timeLeft >= 0))   /* below 0, or not a number */
			g_pointerGliding = 0;
	}
	u32 page = (*(u32 *)&g_roomState);
	switch (page) {
	case 0: case 1: case 2: case 4:
		menu_drawBackground();
		room_camera();   /* the room's camera */
		switch (page) {
		case 0: return account_page();
		case 1: return gameList_pageFrame();
		case 2: return roomSettings_page();
		default: return ranking_page();
		}
	case 66:
		roomLogin_update();
		menu_drawBackground();
		return roomLogin_draw();
	case 77:
		newIdForm_update();
		menu_drawBackground();
		return newIdForm_draw();
	case 88:
		newIdConfirm_update();
		menu_drawBackground();
		return newIdConfirm_draw();
	case 99:
		room_slideMenu();
		menu_drawBackground();
		if (g_leavingForMatch == 1 && g_roomCameraMode == 2)
			return room_drawWhiteFade();
		return room_drawMenu();
	}
	return page;
}


/* the host leaving announced to the others (the host only): message g_netHostLeftMessageKind with its flag word g_hostGoneMessageFlag raised
   while it goes out (net_sendMessage) */
static void send_host_leaving(void)
{
	if (!g_isHost)
		return;
	g_hostGoneMessageFlag = 1;
	CALL_FN(net_sendMessage, int, void *, u32, u32)((void *)ADDR(g_netHostLeftMessageKind), 0, 0);
	g_hostGoneMessageFlag = 0;
}

/* 0x420100: after a match. Started from outside (g_launchedForNetGame = 1): the game quits (code 0) and g_screen is set to -1.
   Otherwise by the match's mode g_matchMode (0 after a replay, g_replayRunning): 1 the arena (the host's leaving sent; screen 400),
   2 a network game (the host's leaving sent, the host's name (+0x43) and address (+0x33) copied from g_roomPacket into the leave record (g_roomLeavePacket), net_send 0x16; back to
   the room when g_gameServerSocket, else the menus), 3 the campaign (the end mode set by the mission 0x9f181c and the
   progress saved; after the last mission, 15, the game quits with code 0x63 instead), any other the menus. Then
   the menu music, and message 6 when g_mapMissing asks for it. Returns what the original leaves in eax */
u32 (game_postMatch)(void)
{
	g_unusedPostMatchFlag = 1;
	g_matchRunning = 0;
	if (g_launchedForNetGame == 1) {
		u32 r = ((u32)app_closeWindow(0));   /* app_closeWindow: quit */
		g_menuState = -1;
		return r;
	}
	if (g_replayRunning)
		g_matchMode = 0;
	u32 r;
	int progress;
	switch (g_matchMode) {
	case 1:
		send_host_leaving();
		game_returnToArenaLobby();
		break;
	case 2:
		if (g_isHost) {
			send_host_leaving();
			RoomRecord *to = (*(RoomRecord **)&g_roomLeavePacket), *from = g_roomPacket;
			lstrcpyA(to->hostName, from->hostName);
			lstrcpyA(to->address, from->address);
			net_send(0x16, 0x65);   /* net_send */
		}
		if (g_gameServerSocket) {
			ladder_sendRecord();
			game_returnToGameRoom();   /* game_returnToGameRoom: the room */
		} else
			game_returnToMainMenu();
		break;
	case 3:
		progress = g_progress;
		if (progress == 15) {
			g_progress = 16;
			profile_save();
			reg_writeEndMode(1);      /* reg_writeEndMode */
			music_stop();
			r = ((u32)app_closeWindow(0x63));
			goto message;
		}
		reg_writeEndMode(progress < 15 ? 0 : 1);
		profile_save();
		game_returnToSkirmish();         /* game_returnToSkirmish */
		break;
	default:
		game_returnToMainMenu();
	}
	r = music_play((const char *)STR(0x4b01cc, "music/Netsphere.mp3"));   /* music_play */
message:
	if (g_mapMissing) {
		r = menu_showMessage(6);
		g_mapMissing = 0;
	}
	return r;
}
