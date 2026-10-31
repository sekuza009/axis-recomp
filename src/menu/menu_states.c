/* menu_states.c: small pieces of the front end's screens: the main menu's frame, the 3D background behind the
   menus, the skirmish and mission settings pages' dispatch, and the mission select keys. */
#include "../game.h"
#include "key_repeat.h"

#define g_tunnel GAME_VAR(TunnelRing *, 0x67fb3c)      /* the background tunnel's first ring */
#define g_settingsPage GAME_VAR(int, 0x9ef1f8)        /* (by use) 10 the skirmish settings, 20 the mission settings */
#define g_settingsState GAME_VAR(int, 0x9ef1f0)       /* (by use) 0 and 1: the page is not up */
#define g_missionState GAME_VAR(int, 0x9f62f8)        /* (by use) the mission select: 0 and 1 not up */
#define g_missionBusy GAME_VAR(int, 0x9f6300)
#define g_missionBriefing GAME_VAR(int, 0x9f62e0)     /* (by use) a mission's briefing is shown */
#define g_mission GAME_VAR(int, 0x9f63b4)             /* the mission chosen, 0 .. 14 */
#define g_quitAsked GAME_VAR(int, 0x67ef14)           /* (by use) 1: the quit question is up */

/* ---- the start-up screen: the logo (texture 0x76d3f0, on a quad 320 x 256 at (160, 60)) over the clear colour
   0x76d350, blended ---- */
static void draw_logo(int first)
{
	const u32 *clear = (const u32 *)0x76d350;
	IMPORT(0x4a91e0, void, u32, u32, u32, u32)(clear[0], clear[1], clear[2], clear[3]);   /* glClearColor */
	glClear(0x4100);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(0xbe2);   /* GL_BLEND */
	if (first)
		glColor4f(1.0f, 1.0f, 1.0f, 0.6f);
	IMPORT(0x4a91ec, void, u32, u32)(0x302, 0x303);   /* glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) */
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int texture = GAME_VAR(int, 0x76d3f0);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
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

#define K(addr) ((const float *)(addr))
/* v kept within 0 .. 1 (a NaN becomes 0) */
static float unit(float v)
{
	if (!(v >= *K(0x4a93e8)))
		v = 0;
	if (v > *K(0x4a9424))
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
int (intro_41f100)(void)
{
	draw_logo(0);
	int n = GAME_VAR(int, 0x4dda34) * 16;
	for (int i = 0; i < n && i < 200; i++) {
		long double f = (long double)i;
		float r = f32(fsubr_m(fmul_m(f, K(0x4a9404)), K(0x4a9424)));   /* 1 - i * 0.005 */
		float b = f32(fmul_m(f, K(0x4a94d8)));                         /* i * 0.0051 */
		bar_column(i + 0x14, unit(r), 0.0f, unit(b));
	}
	if (n > 200)
		for (int i = 0; i + 200 < 400 && i + 200 < n; i++) {
			long double t = fmul_m((long double)i, K(0x4a9404));
			float g = f32(t), b = f32(1.0L - t);
			bar_column(i + 0xdc, 0.0f, unit(g), unit(b));
		}
	if (n > 400) {
		int i = 0;
		do {
			long double t = fmul_m((long double)i, K(0x4a9420));      /* i * 0.01 */
			float r = f32(t), g = f32(fadd_m(t, K(0x4a9424)));
			bar_column(i + 0x1a4, unit(r), unit(g), 0.0f);
			i++;
		} while (i + 400 < n);
	}
	glFinish();
	return SwapBuffers(GAME_VAR(void *, 0x76d480));
}
#undef K

/* 0x41f540: the intro: the start-up logo shown once (dimmed), then the loading picture stepped four times (0x4dda34) around the start-up loads, with
   waits of 5 and 2 (1/60 s); then the title screen (200) with the front end's state reset, the pointer at
   (310, 230), the Netsphere music and the frame clocks cleared */
void (menuState100_intro)(void)
{
	GAME_VAR(int, 0x4df01c) = 0;
	GAME_VAR(int, 0x4e0458) = 0;
	GAME_VAR(int, 0x4dda34) = 0;
	draw_logo(1);
	glFinish();
	SwapBuffers(GAME_VAR(void *, 0x76d480));
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0, 0, 0x3f800000);   /* red text */
	GAME_VAR(int, 0x4dda34)++;
	intro_41f100();
	intro_41e730(5.0);
	intro_4411e0();
	GAME_VAR(int, 0x4dda34)++;
	intro_41f100();
	intro_41e730(2.0);
	menu_loadIntroTextures();
	intro_430bf0();
	GAME_VAR(int, 0x4dda34)++;
	intro_41f100();
	nullsub_48b420(NULL);   /* (an empty function) */
	GAME_VAR(int, 0x4dda34)++;
	intro_41f100();
	g_screen = 200;
	g_lastScreen = 200;
	static const u32 cleared[] = { 0x4df01c, 0x4e0458, 0x680370, 0x4df8e0, 0x4df03c, 0x4df910, 0x4e14fc, 0x9db978, 0x4dda48 };
	for (unsigned i = 0; i < sizeof cleared / sizeof cleared[0]; i++)
		GAME_VAR(u32, cleared[i]) = 0;
	GAME_VAR(u32, 0x4deda8) = 0x3f800000;   /* 1.0 */
	GAME_VAR(u32, 0x4df010) = 0x3f800000;
	GAME_VAR(int, 0x4ded68) = 0x136;
	GAME_VAR(int, 0x4ded6c) = 0xe6;
	music_play((const char *)0x4b01cc);   /* "music/Netsphere.mp3" */
	static const u32 clocks[] = { 0x4dd560, 0x4dd0a8, 0x4dd080, 0x4dd0c8 };   /* four doubles */
	for (int i = 0; i < 4; i++) {
		GAME_VAR(u32, clocks[i]) = 0;
		GAME_VAR(u32, clocks[i] + 4) = 0;
	}
}

/* 0x441740: the 3D background behind the menus: the tunnel's rings moved on (armc_enter) and drawn */
void (menu_drawBackground)(void)
{
	armc_enter(g_tunnel);
	gfx_setProjection2D3D(1);
	menu_drawBackground3D(g_tunnel);
}

/* 0x442e10: the map-select dialog (0x9dd908 .. 0x9dd914): the window, its title 0x74e8a4, the list's frame with
   its scroll arrows (0 / 1 under the pointer, by FUN_00440b70), two tick boxes (0x4b2a7c: 0x74e924, 0x9eeac0:
   0x74e9a4), two rows of two buttons (0x74ea24 lit from 4, 0x74eb24 from 6), the list row under the pointer
   (8 .. 0x11) highlighted, the list (mainmenu_442d10) and the border. The original leaves eax to callers that
   ignore it */
void (mainmenu_442e10)(void)
{
#define X0 GAME_VAR(int, 0x9dd908)
#define Y0 GAME_VAR(int, 0x9dd90c)
#define X1 GAME_VAR(int, 0x9dd910)
#define Y1 GAME_VAR(int, 0x9dd914)
	const u32 *bright = (const u32 *)0x9eea98, *dim = (const u32 *)0x9dda70;
	int hovered = GAME_CDECL(0x440b70, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_427a90(X0, Y0, X1, Y1, GAME_VAR(int, 0x4deb50));
	set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
	text_draw16(X0 + 0x20, Y0 + 0x10, (const char *)0x74e8a4);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(X0 + 0x10, Y0 + 0x28, X1 - 0x40, Y0 + 0xf5, 0);
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexQuad_4286b0(X1 - 0x32, Y0 + 0x48, X1 - 0x12, Y0 + 0x88, hovered == 0);
	menu_drawTexQuad_4287a0(X1 - 0x32, Y0 + 0xac, X1 - 0x12, Y0 + 0xec, hovered != 0 && hovered == 1);
	glDisable(GL_TEXTURE_2D);
	const int *ticked[2] = { (const int *)0x4b2a7c, (const int *)0x9eeac0 };
	for (int k = 0; k < 2; k++) {
		int y = Y0 + 0xfe + k * 0x1e;
		set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
		menu_drawRect(X0 + 0x10, y, X0 + 0x20, y + 0x10, 0);
		if (*ticked[k]) {
			set_colour_bits(g_rectColour, 0x3f800000, 0, 0, 0x3f800000);
			menu_drawRect(X0 + 0x12, y + 2, X0 + 0x1d, y + 0xd, 1);
		}
		set_colour_bits((Colour *)0x76d438, bright[0], bright[1], bright[2], bright[3]);
		text_draw16(X0 + 0x28, k ? y : y + 2, (const char *)(0x74e924 + k * 0x80));   /* (the second label 2 higher) */
	}
	for (int row = 0; row < 2; row++)
		for (int k = 0; k < 2; k++) {
			glEnable(GL_TEXTURE_2D);
			texture = GAME_VAR(int, 0x9db0a4);
			tex_bind(g_textures->managers[texture / 512], texture % 512);
			int lit = hovered == 4 + row * 2 + k;
			glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
			int x = X0 + k * 0xa0, y = Y1 - 0x5c + row * 0x28;
			menu_drawTexQuad_4282f0(x + 0x64, y, x + 0xdc, y + 0x20, 1);
			const u32 *colour = lit ? bright : dim;
			set_colour_bits((Colour *)0x76d438, colour[0], colour[1], colour[2], colour[3]);
			text_drawBox16(x + 0x64, y + 8, x + 0xdc, (const char *)(0x74ea24 + row * 0x100 + k * 0x80));
		}
	if (hovered > 7 && hovered < 0x12) {
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e99999a, 0x3f800000, 0x3e99999a);   /* 0.1, 0.3, 1, 0.3 */
		menu_drawRect(X0 + 0x20, Y0 + hovered * 20 - 0x75, X1 - 0x50, Y0 + hovered * 20 - 0x63, 1);
	}
	mainmenu_442d10();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexturedRect_428a00(X0, Y0, X1, Y1);
#undef X0
#undef Y0
#undef X1
#undef Y1
}

/* 0x4434f0: the map-select dialog of the main menu (only its frame while a dialog is up) */
void (mainmenu_4434f0)(void)
{
	if (g_dialogOpen != 0)
		menu_drawFrame(GAME_VAR(int, 0x9dd908), GAME_VAR(int, 0x9dd90c), GAME_VAR(int, 0x9dd910), GAME_VAR(int, 0x9dd914));
	else
		mainmenu_442e10();
}

/* 0x443530: the main menu's frame: background, menu, the map-select dialog when open, and while the quit question
   is up the keys are held (state 1), the next screen set to 9999 and the screen dimmed */
void (menuState300_frame)(void)
{
	menu_drawBackground();
	menu_mainMenu();
	if (GAME_VAR(int, 0x9eeab4) != 0)
		mainmenu_4434f0();
	if (g_quitAsked == 1) {
		set_680370_441250(1);
		g_nextScreen = 9999;
		menu_drawDimOverlay();
	}
}

/* 0x443ef0: the settings page's draw pass (none while a dialog is up) */
void (menu_443ef0)(void)
{
	if (g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_saveSettings();
	else if (g_settingsPage == 20)
		menu_443ea0();
}

/* 0x4440f0: the settings page's keys */
void (menu_4440f0)(void)
{
	if (g_settingsState == 1 || g_settingsState == 0 || g_dialogOpen != 0)
		return;
	if (g_settingsPage == 10)
		skirmish_processKeys();
	else if (g_settingsPage == 20)
		menu_444070();
}

/* 0x4479b0: mission chosen (sound 2) */
void (mission_4479b0)(int mission)
{
	GAME_VAR(int, 0x9f6328) = mission;
	GAME_VAR(int, 0x9f63b0) = 1;
	sound_playMenu(2);
}

/* 0x447b10: the mission select's draw pass: the briefing or the list */
void (mission_unlockCheat)(void)
{
	if (g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		mission_447af0();
	else
		mission_447a50();
}

/* 0x447c30: the briefing's keys: Esc or Enter closes it */
void (menu_447c30)(void)
{
	if (input_justPressed(g_keyCancel2) == 1 || input_justPressed(g_keyClick) == 1)
		g_missionBriefing = 0;
}

/* 0x447b40: the list's keys: Esc or back leaves, O starts the mission, left / right step through the missions
   unlocked so far (g_progress), and Left Ctrl + Right Alt + Page Up unlocks them all */
void (menu_447b40)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		FUN_00447960();
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		mission_4479d0();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		FUN_00447960();
		return;
	}
	if (input_justPressed(g_keyLeft) == 1 && g_mission > 0)
		mission_4479b0(--g_mission);
	if (input_justPressed(g_keyRight) == 1 && g_mission < g_progress) {
		if (g_mission >= 14)
			return;
		mission_4479b0(++g_mission);
	}
	if (input_isDown(g_keyLeftCtrl) && input_isDown(GAME_VAR(int, 0x4df9fc)) && input_justPressed(GAME_VAR(int, 0x4df90c)))
		g_progress = 16;
}

/* 0x447c70: the mission select's keys (not while a dialog is up) */
void (menu_447c70)(void)
{
	if (g_missionState == 1 || g_missionState == 0 || g_dialogOpen != 0 || g_missionBusy != 0)
		return;
	if (g_missionBriefing != 0)
		menu_447c30();
	else
		menu_447b40();
}

/* 0x41edc0 (menu_returnToMain): back to the main menu: the background tunnel freed ring by ring (last first), the menus
   entered again, state 300 */
void (menu_returnToMain)(void)
{
	while (g_tunnel != NULL)
		armc_freeRing(&GAME_VAR(TunnelRing *, 0x67fb3c));
	game_returnToMenus_41e9d0();
	g_screen = 300;
}

/* 0x41ed70: back to the main menu from the game room: the background tunnel freed, the menus entered again, the
   room's state cleared, state 300 */
void (menu_returnToMainFromRoom)(void)
{
	while (g_tunnel != NULL)
		armc_freeRing(&GAME_VAR(TunnelRing *, 0x67fb3c));
	game_returnToMenus_41e8b0();
	GAME_VAR(int, 0x9dd838) = 0;
	GAME_VAR(int, 0x9dd6a4) = 0;
	GAME_VAR(int, 0x9dd1b0) = 0;
	GAME_VAR(int, 0x9dd6d4) = 0;
	g_screen = 300;
}

/* 0x441770: the map-select dialog's OK: if a map is chosen (0x44-byte entries from 0x9ddac8), the dialog closes and
   the choice is kept */
void (mainmenu_441770)(void)
{
	int count = GAME_VAR(int, 0x9dd928);
	for (int i = 0; i < count; i++)
		if (GAME_VAR(int, 0x9ddac8 + i * 0x44) == 1) {
			sound_playMenu(0);
			GAME_VAR(int, 0x9eeab8) = GAME_VAR(int, 0x9dd928);
			GAME_VAR(int, 0x9db994) = 1;
			GAME_VAR(int, 0x9eeab4) = 0;
			return;
		}
}

/* ---- the map-select dialog's list: 10 rows shown from map 0x9dd92c of the 0x9dd928 ---- */
#define g_mapFirst GAME_VAR(int, 0x9dd92c)
static void maps_up(void)
{
	if (g_mapFirst > 0) {
		g_mapFirst--;
		sound_playMenu(2);
	}
}
static void maps_down(void)
{
	if (g_mapFirst + 10 < GAME_VAR(int, 0x9dd928)) {
		g_mapFirst++;
		sound_playMenu(2);
	}
}

/* 0x441c00: the map-select dialog's keys: cancel or back closes it (0x9eeab4), OK takes the choice (mainmenu_441770),
   0x4e151c toggles 0x9eeac0, 0x4e0ce0 / 0x4e0cd4 take every map out / in, up / down scroll the list with a key
   repeat (the original leaves eax to callers that ignore it) */
void (mainmenu_441c00)(void)
{
	if (input_justPressed(g_keyCancel2) == 1) {
		sound_playMenu(0);
		GAME_VAR(int, 0x9eeab4) = 0;
		return;
	}
	if (input_justPressed(g_keyOk) == 1) {
		mainmenu_441770();
		return;
	}
	if (input_justPressed(g_keyBack) == 1) {
		sound_playMenu(0);
		GAME_VAR(int, 0x9eeab4) = 0;
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e151c)) == 1) {
		sound_playMenu(0);
		GAME_VAR(int, 0x9eeac0) = 1 - GAME_VAR(int, 0x9eeac0);
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0ce0)) == 1) {
		sound_playMenu(0);
		mainmenu_440df0();
		return;
	}
	if (input_justPressed(GAME_VAR(int, 0x4e0cd4)) == 1) {
		sound_playMenu(0);
		mainmenu_4417f0();
		return;
	}
	if (!key_repeat(g_keyUp, &g_repeatUp, maps_up))
		key_repeat(g_keyDown, &g_repeatDown, maps_down);
}

/* 0x441810: the map-select dialog's mouse: a click (the blink clock restarted) on the arrows (0 / 1), the two
   toggles (0x4b2a7c, 0x9eeac0), every map in or out, OK, cancel (7), or a row's map (8 .. 17); holding an arrow
   scrolls once the clock reaches 5 (0x4a93d0), restarting it. The original leaves eax to callers that ignore it */
void (mainmenu_441810)(void)
{
	const float *repeat = (const float *)0x4a93d0;
	if (g_mouseClick) {
		g_cursorBlink = 0.0f;
		int on = mainmenu_440b70(g_mouseX, g_mouseY);
		if (on == 0)
			maps_up();
		else if (on == 1)
			maps_down();
		else if (on == 2)
			GAME_VAR(int, 0x4b2a7c) = 1 - GAME_VAR(int, 0x4b2a7c);
		else if (on == 3)
			GAME_VAR(int, 0x9eeac0) = 1 - GAME_VAR(int, 0x9eeac0);
		else if (on == 4)
			mainmenu_4417f0();
		else if (on == 5)
			mainmenu_440df0();
		else if (on == 6)
			mainmenu_441770();
		else if (on == 7)
			GAME_VAR(int, 0x9eeab4) = 0;
		else if (on >= 8 && on < 18) {
			sound_playMenu(2);
			mainmenu_4417c0(g_mapFirst + on - 8);
		}
	}
	if (!g_mouseHeld)
		return;
	int on = mainmenu_440b70(g_mouseX, g_mouseY);
	if ((on == 0 || on == 1) && g_cursorBlink >= *repeat) {
		if (on == 0)
			maps_up();
		else
			maps_down();
		g_cursorBlink = 0.0f;
	}
}

/* 0x44f860: the profile screen's frame: while its intro (0x9f6838) runs, quit (profile_44f850); else the background and, once the zoom (0x4dda48)
   is not above 0, the pilot list reloaded for every value of the nine 0x4c-byte pilot stat records (from 0x9f9068)
   that is out of range (above 30, the eighth above 50), then the page (0x9f8f10, 1 .. 6). The original leaves eax
   to callers that ignore it */
void (menuState210_frame)(void)
{
	if (g_profileIntro) {
		profile_44f850();
		return;
	}
	menu_drawBackground();
	if (GAME_VAR(float, 0x4dda48) > GAME_VAR(float, 0x4a93e8))
		return;
	static const signed char fields[9] = { -8, 0, 4, -4, 12, 8, 16, 24, 20 };   /* in the order checked */
	for (u32 rec = 0x9f9070; rec < 0x9f931c; rec += 0x4c)
		for (int f = 0; f < 9; f++)
			if (GAME_VAR(int, rec + fields[f]) > (fields[f] == 20 ? 50 : 30))
				data_loadPilotProfiles();
	static const u32 pages[6] = { 0x44f410, 0x44f4b0, 0x44f5f0, 0x44f6c0, 0x44f740, 0x44f810 };
	u32 page = GAME_VAR(u32, 0x9f8f10) - 1;
	if (page <= 5)
		GAME_CDECL(pages[page], void, void)();   /* profile_44f410 .. profile_44f810 */
}

/* 0x427920: the setup screen's frame: the background, then by tab the screen with its page, or the top page */
void (menuState600_setup)(void)
{
	menu_drawBackground();
	switch (g_setupTab) {
	case 2: setup_4230e0(); setup_4278d0(); break;
	case 0: setup_4230e0(); setup_427830(); break;
	case 1: setup_4230e0(); setup_427880(); break;
	case 0x29a: setup_4277c0(); setup_423330(); break;
	}
}

/* 0x44aee0: the room's text (0x9dd570) copied to 0x4de700, and match_4327f0 when it is not empty */
void (match_44aee0)(void)
{
	const char *from = (const char *)0x9dd570;
	char *to = (char *)0x4de700;
	int i = 0;
	do
		to[i] = from[i];
	while (from[i++] != '\0');
	if (to[0] != '\0')
		match_4327f0();
}

/* a panel sliding in: while flag is set, eased moves a tenth of the way to the constant at 0x4a9448 per time unit
   and slid moves back by the same step, until slid is no longer above the double at 0x4a9440 (then the flag drops
   and slid is set to -1650). Afterwards, while the quit question is up, the keys are held and the next screen set
   to 9999 (returns 1) */
static int menu_slide(u32 flag, u32 eased, u32 slid)
{
	if (GAME_VAR(int, flag)) {
		volatile long double d = (long double)GAME_VAR(float, 0x4a9448) - GAME_VAR(float, eased);
		d = d * g_frameTime;
		d = d * GAME_VAR(float, 0x4a93ec);
		volatile long double e = (long double)GAME_VAR(float, eased) + d;
		GAME_VAR(float, eased) = (float)e;
		long double s = GAME_VAR(float, slid);
		if (s > GAME_VAR(double, 0x4a9440)) {
			volatile long double t = s - d;
			GAME_VAR(float, slid) = (float)t;
		} else {
			GAME_VAR(int, flag) = 0;
			GAME_VAR(u32, slid) = 0xc4ce4000;   /* -1650.0 */
		}
	}
	if (!g_quitAsked)
		return 0;
	set_680370_441250(1);
	g_nextScreen = 9999;
	return 1;
}

/* 0x40cef0 (lobbyTop_draw), 0x43e720: the lobby's and the room's panels */
int (lobbyTop_draw)(void) { return menu_slide(0x4db85c, 0x4dbb60, 0x4dba68); }
int (room_43e720)(void) { return menu_slide(0x9dd7d8, 0x9dd560, 0x9dd698); }

/* ---- back to the menus after a game: the arena session left (0x452fe0) and, unless kept, the connection closed;
   the player slots (0x410 bytes from 0x9f9840) emptied ---- */
static void leave_game(u32 lobby, int disconnect)
{
	GAME_VAR(int, 0x67ef14) = 0;
	GAME_VAR(u32, 0x5ae9c4) = lobby;
	GAME_CDECL(0x452fe0, void, void)();       /* arena_452fe0 */
	if (disconnect)
		GAME_CDECL(0x451e60, void, void)();   /* net_disconnect */
	GAME_VAR(int, 0x4dbbf4) = 0;
	for (u32 p = 0x9f9844; p < 0x9fd944; p += 0x410) {
		GAME_VAR(int, p - 4) = 0;
		GAME_VAR(int, p) = 0;
	}
}
/* the menu cameras placed (both at (0, 0, z), the far one at farZ, the near one at nearZ: float bits), the keys
   blocked as given, 0x4deb48 set (and 0x4e1868 cleared when asked), the menu state cleared and the keyboard taken back if it was let go. Returns
   what the original leaves in eax: input_initKeyboard's, or 0x68039c's value */
static u32 reset_menus(u32 farZ, u32 nearZ, int blocked, int deb48, int clear_4e1868)
{
	u32 typing = GAME_VAR(u32, 0x68039c);
	GAME_VAR(u32, 0x4df028) = 0;
	GAME_VAR(u32, 0x4df024) = 0;
	GAME_VAR(u32, 0x4df02c) = farZ;
	GAME_VAR(u32, 0x680378) = 0;
	GAME_VAR(u32, 0x68037c) = 0;
	GAME_VAR(u32, 0x680380) = nearZ;
	GAME_VAR(int, 0x680370) = blocked;
	GAME_VAR(int, 0x4df8e0) = 0;
	GAME_VAR(u32, 0x9dd930) = 0;
	GAME_VAR(u32, 0x9dd934) = 0;
	GAME_VAR(u32, 0x9dd938) = farZ;
	GAME_VAR(u32, 0x9dd918) = 0;
	GAME_VAR(u32, 0x9dd91c) = 0;
	GAME_VAR(u32, 0x9dd920) = nearZ;
	GAME_VAR(int, 0x4deb48) = deb48;
	GAME_VAR(int, 0x9db990) = 0;
	GAME_VAR(int, 0x4dda44) = 0;
	GAME_VAR(int, 0x4dda48) = 0;
	if (clear_4e1868)
		GAME_VAR(int, 0x4e1868) = 0;
	if (typing != 1)
		return typing;
	GAME_VAR(int, 0x68039c) = 0;
	GAME_CDECL(0x431590, void, void)();   /* match_431590 */
	return GAME_CDECL(0x401310, u32, void *)(GAME_VAR(void *, 0x4ded18));   /* input_initKeyboard */
}
#define FAR_BACK 0xc3e10000u    /* -450 */
#define NEAR_BACK 0xc4098000u   /* -550 */

/* 0x41ec50: to screen 500 */
u32 (game_returnToMenus_41ec50)(void)
{
	leave_game(0, 1);
	GAME_VAR(int, 0x76d3e8) = 500;
	g_nextScreen = 500;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	return reset_menus(FAR_BACK, NEAR_BACK, 0, 0, 0);
}

/* 0x41e8b0: to the main menu (300), the cameras in front (500, 400), 0x4deb48 set and 0x4e1868 cleared. Returns 1
   when the keyboard was not let go */
u32 (game_returnToMenus_41e8b0)(void)
{
	leave_game(0, 1);
	GAME_VAR(int, 0x76d3e8) = 300;
	g_nextScreen = 300;
	GAME_CDECL(0x4411e0, void, void)();
	u32 typing = GAME_VAR(u32, 0x68039c);
	u32 r = reset_menus(0x43fa0000, 0x43c80000, 2, 1, 1);
	return typing == 1 ? r : 1;
}

/* 0x41e9d0: to screen 400, the previous screen 300 */
u32 (game_returnToMenus_41e9d0)(void)
{
	leave_game(0, 1);
	g_nextScreen = 400;
	GAME_VAR(int, 0x76d3e8) = 300;
	GAME_VAR(int, 0x67ef0c) = 300;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	return reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
}

/* 0x41eb00: back to the game room (800; lobby state 2, the connection kept): the room's state cleared too */
u32 (game_returnToMenus_41eb00)(void)
{
	leave_game(2, 0);
	GAME_VAR(int, 0x9dd834) = 0x63;
	GAME_VAR(int, 0x76d3e8) = 800;
	g_nextScreen = 800;
	GAME_VAR(int, 0x67ef0c) = 800;
	GAME_CDECL(0x4411e0, void, void)();
	GAME_CDECL(0x441200, void, void)();
	u32 r = reset_menus(FAR_BACK, NEAR_BACK, 2, 0, 0);
	GAME_VAR(int, 0x9dced0) = 0;
	GAME_VAR(int, 0x4ded54) = 0;
	GAME_VAR(int, 0x9dd1c8) = 0;
	GAME_VAR(int, 0x9dd350) = 0;
	return r;
}

/* 0x43ef70: the game room's frame. While the dialog highlight is shown the mouse glides a quarter of the way to it
   and the highlight shrinks by the step 0x4b071c (gone below 0). Then the room's page (0x9dd834): 0 .. 4 the room's own pages over the
   background and the room's camera (0x437a10), 66 / 77 / 88 / 99 dialogs drawn before the background (99 shows the
   quit question while it waits on the network). Returns the last call's eax, or the page */
u32 (menuState800_gameRoom)(void)
{
	if (g_highlightShown) {
		int *mouse = (int *)0x4ded68;
		mouse[0] += ftol(fmul_m(fmul_m((long double)(g_highlightX - mouse[0]), (const float *)0x4b071c), (const float *)0x4a941c));
		mouse[1] += ftol(fmul_m(fmul_m((long double)(g_highlightY - mouse[1]), (const float *)0x4b071c), (const float *)0x4a941c));
		long double size = fsub_m(fld_m((const float *)0x680bc0), (const float *)0x4b071c);
		g_highlightSize = f32(size);
		if (!(size >= 0))   /* below 0, or not a number */
			g_highlightShown = 0;
	}
#define CALL(addr) GAME_CDECL(addr, u32, void)()
	u32 page = GAME_VAR(u32, 0x9dd834);
	switch (page) {
	case 0: case 1: case 2: case 4:
		menu_drawBackground();
		CALL(0x437a10);   /* the room's camera */
		switch (page) {
		case 0: return CALL(0x43e7b0);
		case 1: return CALL(0x43ea10);
		case 2: return CALL(0x43ed20);
		default: return CALL(0x43ede0);
		}
	case 66:
		CALL(0x43df80);
		menu_drawBackground();
		return CALL(0x4392c0);
	case 77:
		CALL(0x43e290);
		menu_drawBackground();
		return CALL(0x4399c0);
	case 88:
		CALL(0x43e610);
		menu_drawBackground();
		return CALL(0x439e00);
	case 99:
		CALL(0x43e720);
		menu_drawBackground();
		if (g_quitAsked == 1 && GAME_VAR(int, 0x9dce48) == 2)
			return CALL(0x43df00);
		return CALL(0x437e00);
	}
#undef CALL
	return page;
}

#define lstrcpyA(dst, src) IMPORT(0x4a911c, char *, char *, const char *)(dst, src)

/* the match's result sent to the others (the host only): message 0x9f9418 with its flag word 0x9f941c raised
   while it goes out (net_sendMessage) */
static void send_result(void)
{
	if (!GAME_VAR(int, 0xa0baf8))
		return;
	GAME_VAR(int, 0x9f941c) = 1;
	GAME_CDECL(0x451270, int, void *, u32, u32)((void *)0x9f9418, 0, 0);
	GAME_VAR(int, 0x9f941c) = 0;
}

/* 0x420100: after a match. Started from outside (0x76d410 = 1): the game quits (code 0) and the text mode is reset.
   Otherwise by the match's mode 0x5ae9c4 (0 after a replay, 0x9db990): 1 the arena (the result sent; screen 400),
   2 a network game (the result sent, the two players' names 0x43 / 0x33 into a game record, net_send 0x16; back to
   the room when 0xa05630, else the menus), 3 the campaign (the end mode set by the mission 0x9f181c and the
   progress saved; after the last mission, 15, the game quits with code 0x63 instead), any other the menus. Then
   the menu music, and message 6 when 0xa0ea94 asks for it. Returns what the original leaves in eax */
u32 (game_postMatch)(void)
{
	GAME_VAR(int, 0x4de6f8) = 1;
	GAME_VAR(int, 0x5b1dac) = 0;
	if (GAME_VAR(int, 0x76d410) == 1) {
		u32 r = GAME_CDECL(0x41e7a0, u32, int)(0);   /* profile_41e7a0: quit */
		GAME_VAR(int, 0x76d3e8) = -1;
		return r;
	}
	if (GAME_VAR(int, 0x9db990))
		GAME_VAR(int, 0x5ae9c4) = 0;
	u32 r;
	int mission;
	switch (GAME_VAR(int, 0x5ae9c4)) {
	case 1:
		send_result();
		game_returnToMenus_41e9d0();
		break;
	case 2:
		if (GAME_VAR(int, 0xa0baf8)) {
			send_result();
			char *to = GAME_VAR(char *, 0xa0b330), *from = GAME_VAR(char *, 0xa0b328);
			lstrcpyA(to + 0x43, from + 0x43);
			lstrcpyA(to + 0x33, from + 0x33);
			GAME_CDECL(0x4521c0, int, int, int)(0x16, 0x65);   /* net_send */
		}
		if (GAME_VAR(int, 0xa05630)) {
			GAME_CDECL(0x44aee0, void, void)();   /* the room's text kept */
			GAME_CDECL(0x41eb00, void, void)();   /* game_returnToMenus_41eb00: the room */
		} else
			game_returnToMenus_41e8b0();
		break;
	case 3:
		mission = GAME_VAR(int, 0x9f181c);
		if (mission == 15) {
			GAME_VAR(int, 0x9f181c) = 16;
			GAME_CDECL(0x447010, void, void)();     /* profile_saveProgress */
			GAME_CDECL(0x41f880, u32, u32)(1);      /* reg_writeEndMode */
			music_shutdown();
			r = GAME_CDECL(0x41e7a0, u32, int)(0x63);
			goto message;
		}
		GAME_CDECL(0x41f880, u32, u32)(mission < 15 ? 0 : 1);
		GAME_CDECL(0x447010, void, void)();
		GAME_CDECL(0x41ec50, void, void)();         /* game_returnToMenus_41ec50 */
		break;
	default:
		game_returnToMenus_41e8b0();
	}
	r = GAME_CDECL(0x457150, u32, const char *)((const char *)0x4b01cc);   /* music_play */
message:
	if (GAME_VAR(int, 0xa0ea94)) {
		r = GAME_CDECL(0x41ee40, u32, int)(6);
		GAME_VAR(int, 0xa0ea94) = 0;
	}
	return r;
}
