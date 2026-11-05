/* menu_states.c: small pieces of the front end's screens: the main menu's frame, the 3D background behind the
   menus, the skirmish and mission settings pages' dispatch, and the mission select keys. */
#include "../game.h"
#include "key_repeat.h"

#define g_missionState g_missionPage   /* (by use) the mission select: 0 and 1 not up */
#define g_missionBriefing g_missionStarted   /* (by use) a mission's briefing is shown */

/* ---- the start-up screen: the logo (texture 0x76d3f0, on a quad 320 x 256 at (160, 60)) over the clear colour
   0x76d350, blended ---- */
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

/* 0x41f100: the start-up screen at progress 0x4dda34 (16 pixels a step): the logo, then a bar of that many columns
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
	return SwapBuffers(g_desktopDC);
}

/* 0x41f540: the intro: the start-up logo shown once (dimmed), then the loading picture stepped four times (0x4dda34) around the start-up loads, with
   waits of 5 and 2 (1/60 s); then the title screen (200) with the front end's state reset, the pointer at
   (310, 230), the Netsphere music and the frame clocks cleared */
void (menuState100_intro)(void)
{
	g_titleShown = 0;
	g_titleFrames = 0;
	g_loadStep = 0;
	draw_logo(1);
	glFinish();
	SwapBuffers(g_desktopDC);
	set_colour_bits(g_textColour, 0x3f800000, 0, 0, 0x3f800000);   /* red text */
	g_loadStep++;
	frontEnd_drawProgress();
	timer_waitFrames(5.0);
	tunnel_rebuild();
	g_loadStep++;
	frontEnd_drawProgress();
	timer_waitFrames(2.0);
	menu_loadTextures();
	frontEnd_startUp();
	g_loadStep++;
	frontEnd_drawProgress();
	debug_traceStripped(NULL);   /* (an empty function) */
	g_loadStep++;
	frontEnd_drawProgress();
	g_screen = 200;
	g_lastScreen = 200;
	static const u32 cleared[] = { ADDR(g_titleShown), ADDR(g_titleFrames), ADDR(g_menuCameraMove), ADDR(g_unusedMenuReturnWord), ADDR(g_cursorFrame), ADDR(g_cursorFrameTime), ADDR(g_scroll), ADDR(g_tunnelPulse), ADDR(g_introZoom) };
	for (unsigned i = 0; i < sizeof cleared / sizeof cleared[0]; i++)
		GAME_VAR(u32, cleared[i]) = 0;
	g_menuTunnelSpeed = 0x3f800000;   /* 1.0 */
	g_tunnelPulseStep = 0x3f800000;
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

/* 0x442e10: the replay selection dialog (0x9dd908 .. 0x9dd914): the window, its title 0x74e8a4, the list's frame with
   its scroll arrows (0 / 1 under the pointer, by FUN_00440b70), two tick boxes (0x4b2a7c: MSG(22, "AUTO REPEAT"), 0x9eeac0:
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
	menu_drawSmallButton3(X1 - 0x32, Y0 + 0x48, X1 - 0x12, Y0 + 0x88, hovered == 0);
	menu_drawSmallButton4(X1 - 0x32, Y0 + 0xac, X1 - 0x12, Y0 + 0xec, hovered != 0 && hovered == 1);
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
			text_drawBox16(x + 0x64, y + 8, x + 0xdc, (const char *)(MSG(24, "$[0] ALL FILES") + row * 0x100 + k * 0x80));
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
	if (g_dialogOpen != 0)
		menu_drawFrame(g_replaySelectLeft, g_replaySelectTop, g_replaySelectRight, g_replaySelectBottom);
	else
		replaySelect_drawDialog();
}

/* 0x443530: the main menu's frame: background, menu, the replay selection dialog when open, and while the quit question
   is up the keys are held (state 1), the next screen set to 9999 and the screen dimmed */
void (menuState300_frame)(void)
{
	menu_drawBackground();
	menu_mainMenu();
	if (g_mainMenuPicked != 0)
		mainmenu_drawReplaySelect();
	if (g_quitAsked == 1) {
		menuCamera_setMove(1);
		g_nextScreen = 9999;
		menu_drawDimOverlay();
	}
}

/* 0x443ef0: the skirmish settings page's clicks (none while a dialog is up): page 10 the settings (skirmish_clicks), 20 their arrows */
void (skirmishSettings_clicks)(void)
{
	if (g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_clicks();
	else if (g_settingsPage == 20)
		skirmish_settingsArrowClick();
}

/* 0x4440f0: the settings page's keys */
void (settingsPage_keys)(void)
{
	if (g_settingsState == 1 || g_settingsState == 0 || g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_processKeys();
	else if (g_settingsPage == 20)
		skirmish_settingsKeys();
}

/* 0x4479b0: mission chosen (sound 2) */
void (mission_chosen)(int mission)
{
	g_missionChosen = mission;
	g_missionPreviewDue = 1;
	sound_playMenu(2);
}

/* 0x447b10: the mission select's clicks (none while a dialog is up or it is busy): the briefing's close, else the list's (missionsel_clicks) */
void (missionSelect_clicks)(void)
{
	if (g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		briefing_clickClose();
	else
		missionsel_clicks();
}

/* 0x447c30: the briefing's keys: Esc or Enter closes it */
void (briefing_keys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1 || input_justPressed(g_keyClick) == 1)
		g_missionBriefing = 0;
}

/* 0x447b40: the list's keys: Esc or back leaves, O starts the mission, left / right step through the missions
   unlocked so far (g_progress), and Left Ctrl + Right Alt + Page Up unlocks them all */
void (missionList_keys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		missionSettings_leave();
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		mission_choose();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		missionSettings_leave();
		return;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_missionShown > 0)
		mission_chosen(--g_missionShown);
	if (input_justPressed(g_keyRight) == 1 && g_missionShown < g_progress) {
		if (g_missionShown >= 14)
			return;
		mission_chosen(++g_missionShown);
	}
	if (input_isDown(g_keyLeftCtrl) && input_isDown(g_dikRAlt) && input_justPressed(g_dikPageUp))
		g_progress = 16;
}

/* 0x447c70: the mission select's keys (not while a dialog is up) */
void (missionsel_keys)(void)
{
	if (g_missionState == 1 || g_missionState == 0 || g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		briefing_keys();
	else
		missionList_keys();
}

/* 0x41edc0 (menu_returnToMain): back to the main menu: the background tunnel freed ring by ring (last first), the menus
   entered again, state 300 */
void (menu_returnToMain)(void)
{
	while (g_menuTunnel != NULL)
		armc_freeRing(&g_menuTunnel);
	game_returnToScreen400();
	g_screen = 300;
}

/* 0x41ed70: back to the main menu from the game room: the background tunnel freed, the menus entered again, the
   room's state cleared, state 300 */
void (menu_returnToMainFromRoom)(void)
{
	while (g_menuTunnel != NULL)
		armc_freeRing(&g_menuTunnel);
	game_returnToMainMenu();
	g_roomRequestOut = 0;
	g_roomAnswerAwaited = 0;
	g_unusedRoomWord = 0;
	g_roomAwaitingServer = 0;
	g_screen = 300;
}

/* 0x441770: the replay selection dialog's OK: if a replay is chosen (0x44-byte entries from 0x9ddac8), the dialog closes and
   the choice is kept */
void (replaySelect_ok)(void)
{
	int count = g_replayFileCount;
	for (int i = 0; i < count; i++)
		if (g_replayList[i].flag == 1) {
			sound_playMenu(0);
			g_replayListCount = g_replayFileCount;
			g_replayZoomIn = 1;
			g_mainMenuPicked = 0;
			return;
		}
}

/* ---- the replay selection dialog's list: 10 rows shown from replay 0x9dd92c of the 0x9dd928 ---- */
static void maps_up(void)
{
	if (g_replaySelectFirst > 0) {
		g_replaySelectFirst--;
		sound_playMenu(2);
	}
}
static void maps_down(void)
{
	if (g_replaySelectFirst + 10 < g_replayFileCount) {
		g_replaySelectFirst++;
		sound_playMenu(2);
	}
}

/* 0x441c00: the replay selection dialog's keys: cancel or back closes it (0x9eeab4), OK takes the choice (replaySelect_ok),
   0x4e151c toggles 0x9eeac0, 0x4e0ce0 / 0x4e0cd4 take every replay out / in, up / down scroll the list with a key
   repeat (the original leaves eax to callers that ignore it) */
void (replaySelect_keys)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		sound_playMenu(0);
		g_mainMenuPicked = 0;
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		replaySelect_ok();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		g_mainMenuPicked = 0;
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
	if (!key_repeat(g_keyUp, &g_repeatUp, maps_up))
		key_repeat(g_keyDown, &g_repeatDown, maps_down);
}

/* 0x441810: the replay selection dialog's mouse: a click (the blink clock restarted) on the arrows (0 / 1), the two
   toggles (0x4b2a7c, 0x9eeac0), every replay in or out, OK, cancel (7), or a row's replay (8 .. 17); holding an arrow
   scrolls once the clock reaches 5 (0x4a93d0), restarting it. The original leaves eax to callers that ignore it */
void (replaySelect_mouse)(void)
{
	const float *repeat = (const float *)ADDR(k_5f);
	if (g_mouseClick) {
		g_cursorBlink = 0.0f;
		int on = replaySelect_hitTest(g_mouseX, g_mouseY);
		if (on == 0)
			maps_up();
		else if (on == 1)
			maps_down();
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
			g_mainMenuPicked = 0;
		else if (on >= 8 && on < 18) {
			sound_playMenu(2);
			replaySelect_toggle(g_replaySelectFirst + on - 8);
		}
	}
	if (!g_mouseHeld)
		return;
	int on = replaySelect_hitTest(g_mouseX, g_mouseY);
	if ((on == 0 || on == 1) && g_cursorBlink >= *repeat) {
		if (on == 0)
			maps_up();
		else
			maps_down();
		g_cursorBlink = 0.0f;
	}
}

/* 0x44f860: the profile screen's frame: while its intro (0x9f6838) runs, quit (app_quitGame); else the background and, once the zoom (0x4dda48)
   is not above 0, the pilot list reloaded for every value of the nine 0x4c-byte pilot stat records (from 0x9f9068)
   that is out of range (above 30, the eighth above 50), then the page (0x9f8f10, 1 .. 6). The original leaves eax
   to callers that ignore it */
void (menuState210_frame)(void)
{
	if (g_profileIntro) {
		app_quitGame();
		return;
	}
	menu_drawBackground();
	if (g_introZoom > k_0f)
		return;
	static const signed char stats[9] = { 0, 2, 3, 1, 5, 4, 6, 8, 7 };   /* in the order checked */
	for (int p = 0; p < 9; p++)   /* (the first nine profiles: any value past its limit reloads them all) */
		for (int f = 0; f < 9; f++)
			if (g_profileRecords[p].stats[stats[f]] > (stats[f] == 7 ? 50 : 30))
				data_loadPilotProfiles();
	static const u32 pages[6] = { FN_ADDR(profile_frame, 0x44f410), FN_ADDR(profile_nameEntryStep, 0x44f4b0), FN_ADDR(profile_pilotPanelPage, 0x44f5f0), FN_ADDR(profile_logIn, 0x44f6c0), FN_ADDR(profile_secondPanelPage, 0x44f740), FN_ADDR(profile_drawScreen, 0x44f810) };
	u32 page = (*(u32 *)&g_profilePage) - 1;
	if (page <= 5)
		GAME_CDECL(pages[page], void, void)();   /* profile_frame .. profile_drawScreen */
}

/* 0x427920: the setup screen's frame: the background, then by tab the screen with its page, or the top page */
void (menuState600_setup)(void)
{
	menu_drawBackground();
	switch (g_setupTab) {
	case 2: setup_camera(); setup_frameControlsPage(); break;
	case 0: setup_camera(); setup_frameSoundPage(); break;
	case 1: setup_camera(); setup_frameOptionsPage(); break;
	case 0x29a: setup_easePanel(); setup_drawMenu(); break;
	}
}

/* 0x44aee0: the room's text (0x9dd570) copied to 0x4de700, and profile_checkAndSendRecord when it is not empty */
void (room_keepText)(void)
{
	const char *from = g_joinedTitleName;
	char *to = g_titleName;
	int i = 0;
	do
		to[i] = from[i];
	while (from[i++] != '\0');
	if (to[0] != '\0')
		profile_checkAndSendRecord();
}

/* a panel sliding in: while flag is set, eased moves a tenth of the way to the constant at 0x4a9448 per time unit
   and slid moves back by the same step, until slid is no longer above the double at 0x4a9440 (then the flag drops
   and slid is set to -1650). Afterwards, while the quit question is up, the keys are held and the next screen set
   to 9999 (returns 1) */
static int menu_slide(u32 flag, u32 eased, u32 slid)
{
	if (GAME_VAR(int, flag)) {
		volatile long double d = (long double)k_setupPanelTarget - GAME_VAR(float, eased);
		d = d * g_frameTime;
		d = d * k_tenthsToDegrees;
		volatile long double e = (long double)GAME_VAR(float, eased) + d;
		GAME_VAR(float, eased) = (float)e;
		long double s = GAME_VAR(float, slid);
		if (s > k_setupPanelEnd) {
			volatile long double t = s - d;
			GAME_VAR(float, slid) = (float)t;
		} else {
			GAME_VAR(int, flag) = 0;
			GAME_VAR(u32, slid) = 0xc4ce4000;   /* -1650.0 */
		}
	}
	if (!g_quitAsked)
		return 0;
	menuCamera_setMove(1);
	g_nextScreen = 9999;
	return 1;
}

/* 0x40cef0 (lobbyTop_draw), 0x43e720: the lobby's and the room's panels */
int (lobbyTop_draw)(void) { return menu_slide(ADDR(g_lobbyPanelsOff), OBJ(g_lobbyTopEase), ADDR(g_arenaTunnelDepth)); }
int (room_slideMenu)(void) { return menu_slide(ADDR(g_roomDialogOpen), ADDR(g_roomPanelEase), ADDR(g_roomTunnelDepth)); }

/* ---- back to the menus after a game: the arena session left (0x452fe0) and, unless kept, the connection closed;
   the player slots (0x410 bytes from 0x9f9840) emptied ---- */
static void leave_game(u32 lobby, int disconnect)
{
	g_quitAsked = 0;
	(*(u32 *)&g_matchMode) = lobby;
	arena_leaveSession();
	if (disconnect)
		net_disconnect();   /* net_disconnect */
	g_arenaLobbyState = 0;
	for (NetSlot *p = g_netSlots; p < g_netSlots + 16; p++) {
		p->used = 0;
		p->id = 0;
	}
}
/* the menu cameras placed (both at (0, 0, z), the far one at farZ, the near one at nearZ: float bits), the keys
   blocked as given, 0x4deb48 set (and 0x4e1868 cleared when asked), the menu state cleared and the keyboard taken back if it was let go. Returns
   what the original leaves in eax: input_initKeyboard's, or 0x68039c's value */
static u32 reset_menus(u32 farZ, u32 nearZ, int blocked, int entering, int clear_chat_field)
{
	u32 typing = (*(u32 *)&g_textFieldOpen);
	(*(u32 *)&g_armcCamHeight) = 0;
	g_menuCameraPos = 0;
	(*(u32 *)&g_armcCamDistance) = farZ;
	g_menuCameraLook = 0;
	g_menuCameraLookY = 0;
	(*(u32 *)&g_menuCameraHeight) = nearZ;
	g_menuCameraMove = blocked;
	g_unusedMenuReturnWord = 0;
	g_roomSlideFarX = 0;
	g_roomSlideFarY = 0;
	g_roomSlideFarZ = farZ;
	g_roomSlideNearX = 0;
	g_roomSlideNearY = 0;
	g_roomSlideNearZ = nearZ;
	g_enteringMenus = entering;
	g_replayRunning = 0;
	(*(int *)&g_cursorBlink) = 0;
	(*(int *)&g_introZoom) = 0;
	if (clear_chat_field)
		g_inputLineHidden = 0;
	if (typing != 1)
		return typing;
	g_textFieldOpen = 0;
	input_resetKeys();
	return ((u32)input_initKeyboard(g_mainWindow));   /* input_initKeyboard */
}
#define FAR_BACK 0xc3e10000u    /* -450 */
#define NEAR_BACK 0xc4098000u   /* -550 */

/* 0x41ec50: to screen 500 */
u32 (game_returnToScreen500)(void)
{
	leave_game(0, 1);
	g_menuState = 500;
	g_nextScreen = 500;
	tunnel_rebuild();
	tunnel_addRing();
	return reset_menus(FAR_BACK, NEAR_BACK, 0, 0, 0);
}

/* 0x41e8b0: to the main menu (300), the cameras in front (500, 400), 0x4deb48 set and 0x4e1868 cleared. Returns 1
   when the keyboard was not let go */
u32 (game_returnToMainMenu)(void)
{
	leave_game(0, 1);
	g_menuState = 300;
	g_nextScreen = 300;
	tunnel_rebuild();
	u32 typing = (*(u32 *)&g_textFieldOpen);
	u32 r = reset_menus(0x43fa0000, 0x43c80000, 2, 1, 1);
	return typing == 1 ? r : 1;
}

/* 0x41e9d0: to screen 400, the previous screen 300 */
u32 (game_returnToScreen400)(void)
{
	leave_game(0, 1);
	g_nextScreen = 400;
	g_menuState = 300;
	g_lastScreen = 300;
	tunnel_rebuild();
	tunnel_addRing();
	return reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
}

/* 0x41eb00: back to the game room (800; lobby state 2, the connection kept): the room's state cleared too */
u32 (game_returnToGameRoom)(void)
{
	leave_game(2, 0);
	g_roomState = 0x63;
	g_menuState = 800;
	g_nextScreen = 800;
	g_lastScreen = 800;
	tunnel_rebuild();
	tunnel_addRing();
	u32 r = reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
	g_retypePassword = 0;
	g_arenaGameSetUp = 0;
	g_roomLoginDue = 0;
	g_rankingRequestPending = 0;
	return r;
}

/* 0x43ef70: the game room's frame. While the dialog highlight is shown the mouse glides a quarter of the way to it
   and the highlight shrinks by the step 0x4b071c (gone below 0). Then the room's page (0x9dd834): 0 .. 4 the room's own pages over the
   background and the room's camera (0x437a10), 66 / 77 / 88 / 99 dialogs drawn before the background (99 shows the
   quit question while it waits on the network). Returns the last call's eax, or the page */
u32 (menuState800_gameRoom)(void)
{
	if (g_highlightShown) {
		int *mouse = (int *)ADDR(g_mouseX);
		mouse[0] += ftol(fmul_m(fmul_m((long double)(g_highlightX - mouse[0]), (const float *)ADDR(g_frameTime)), (const float *)ADDR(k_0_25f)));
		mouse[1] += ftol(fmul_m(fmul_m((long double)(g_highlightY - mouse[1]), (const float *)ADDR(g_frameTime)), (const float *)ADDR(k_0_25f)));
		long double size = fsub_m(fld_m((const float *)ADDR(g_highlightSize)), (const float *)ADDR(g_frameTime));
		g_highlightSize = f32(size);
		if (!(size >= 0))   /* below 0, or not a number */
			g_highlightShown = 0;
	}
	u32 page = (*(u32 *)&g_roomState);
	switch (page) {
	case 0: case 1: case 2: case 4:
		menu_drawBackground();
		room_camera();   /* the room's camera */
		switch (page) {
		case 0: return account_page();
		case 1: return gameList_drawPage();
		case 2: return room_draw();
		default: return ranking_page();
		}
	case 66:
		createDialog_draw();
		menu_drawBackground();
		return roomLogin_draw();
	case 77:
		loginForm_update();
		menu_drawBackground();
		return loginDialog_draw();
	case 88:
		room_networkEvents();
		menu_drawBackground();
		return serverDialog_draw();
	case 99:
		room_slideMenu();
		menu_drawBackground();
		if (g_quitAsked == 1 && g_roomMode == 2)
			return room_drawWhiteFade();
		return room_drawMenu();
	}
	return page;
}

#define lstrcpyA(dst, src) IMPORT(0x4a911c, char *, char *, const char *)(dst, src)

/* the match's result sent to the others (the host only): message 0x9f9418 with its flag word 0x9f941c raised
   while it goes out (net_sendMessage) */
static void send_result(void)
{
	if (!g_isHost)
		return;
	g_hostResultFlag = 1;
	GAME_FN(net_sendMessage, 0x451270, int, void *, u32, u32)((void *)ADDR(g_resultMessage), 0, 0);
	g_hostResultFlag = 0;
}

/* 0x420100: after a match. Started from outside (0x76d410 = 1): the game quits (code 0) and the text mode is reset.
   Otherwise by the match's mode 0x5ae9c4 (0 after a replay, 0x9db990): 1 the arena (the result sent; screen 400),
   2 a network game (the result sent, the two players' names 0x43 / 0x33 into a game record, net_send 0x16; back to
   the room when 0xa05630, else the menus), 3 the campaign (the end mode set by the mission 0x9f181c and the
   progress saved; after the last mission, 15, the game quits with code 0x63 instead), any other the menus. Then
   the menu music, and message 6 when 0xa0ea94 asks for it. Returns what the original leaves in eax */
u32 (game_postMatch)(void)
{
	g_unusedPostMatchFlag = 1;
	g_matchRunning = 0;
	if (g_startedFromLobby == 1) {
		u32 r = ((u32)app_closeWindow(0));   /* app_closeWindow: quit */
		g_menuState = -1;
		return r;
	}
	if (g_replayRunning)
		g_matchMode = 0;
	u32 r;
	int mission;
	switch (g_matchMode) {
	case 1:
		send_result();
		game_returnToScreen400();
		break;
	case 2:
		if (g_isHost) {
			send_result();
			char *to = (*(char **)&g_roomRecordPacket), *from = (*(char **)&g_arenaPacket);
			lstrcpyA(((RoomRecord *)to)->hostName, ((const RoomRecord *)from)->hostName);
			lstrcpyA(((RoomRecord *)to)->address, ((const RoomRecord *)from)->address);
			net_send(0x16, 0x65);   /* net_send */
		}
		if (g_gameServerSocket) {
			room_keepText();   /* the room's text kept */
			game_returnToGameRoom();   /* game_returnToGameRoom: the room */
		} else
			game_returnToMainMenu();
		break;
	case 3:
		mission = g_progress;
		if (mission == 15) {
			g_progress = 16;
			profile_saveProgress();
			reg_writeEndMode(1);      /* reg_writeEndMode */
			music_shutdown();
			r = ((u32)app_closeWindow(0x63));
			goto message;
		}
		reg_writeEndMode(mission < 15 ? 0 : 1);
		profile_saveProgress();
		game_returnToScreen500();         /* game_returnToScreen500 */
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
