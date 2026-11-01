/* main_loop.c: one frame of the game. WinMain's message loop calls app_frame whenever no window message is
   waiting; it runs either a match frame or the front end's menus. */
#include "../game.h"
#include <string.h>

/* 0x4202d0 (app_frame): the frame: the music, the menus' fade-in counted down, then main_loop */
void (app_frame)(void)
{
	music_loopIfEnded();
	if (g_menuFade > 0.0f)
		g_menuFade = g_menuFade - g_frameTime;
	main_loop();
}

/* 0x420280: in a match the input and the match's frame (match_frameByState); a frame that answers 0 ends the match;
   outside a match the menus' frame */
void (main_loop)(void)
{
	if (g_screen != 9999) {
		menu_frame();
		return;
	}
	if (g_lastScreen != 9999)
		menu_enterState();
	if (!g_paused) {
		input_updateMenuCursor();
		input_reacquireKeyboard();
	}
	if (match_frameByState(g_scene) == 0)
		game_postMatch();
}

/* 0x462050 (match_frameByState): the match's frame by its state; each state's handler answers the next state. The
   playing, free-camera and replay states present the frame (playing only while frameFlag is 1). */
int THISCALL (match_frameByState)(Scene *scene)
{
	switch (scene->inputState) {
	case 1:
		return scene->inputState = game_processLoadingMode(scene);
	case 2:
		scene->inputState = match_inputState2(scene);
		if (scene->frameFlag == 1)
			gfx_swapBuffers();
		break;
	case 3:
		scene->inputState = match_inputState3(scene);
		gfx_swapBuffers();
		break;
	case 4:
		scene->inputState = replay_frame(scene);
		gfx_swapBuffers();
		break;
	}
	return scene->inputState;
}

/* x rounded to a double, as the original's fst qword does (for a value read again) */
static inline double f64(long double x)
{
	volatile double r = (double)x;
	return r;
}

#define F(addr) GAME_VAR(float, addr)
#define D(addr) GAME_VAR(double, addr)

/* 0x41fa40: the menus' frame: the cursor blink clock (100 past 1e6), the screen's set-up when it changed, its keys
   (unless 0x9da49c is 0x68 / 0x69); a direct start from the main menu zooms in (aspect down to 0.01, the camera
   back) and starts the match after 100; the screen's frame, the message box, 0x428940 while paused, the cursor
   (not over a match or the profile intro), the buffers swapped; the view angle stepped; then the time: the FPS
   counter (frames over each second, 0x4dd980) and the frame time (60 / the frame rate, 1 past 20). The original
   leaves eax to callers that ignore it */
void (menu_frame)(void)
{
	long double blink = fadd_m(fld_m(&g_frameTime), &g_cursorBlink);
	g_cursorBlink = blink;
	if (blink > k_1000000f)
		g_cursorBlink = 100.0f;
	if (g_screen != g_lastScreen)
		menu_enterState();
	if (g_lobbyReply != 0x69 && g_lobbyReply != 0x68) {
		menu_onStateChange();
		menu_processKeys();
	}
	if (g_screen == 300 && g_mainMenuFadingIn && !g_dialogPending) {
		g_viewAspect = f32(fsubr_m(fmul_m(fld_m(&g_frameTime), (const float *)IMG(0x4a9468)), &g_viewAspect));   /* 0.05 a frame */
		g_armcCamDistance = fadd_m(fld_m((const float *)ADDR(g_armcCamDistance)), (const float *)ADDR(k_10f));                       /* the camera 10 back */
		long double zoom = fadd_m(fld_m(&g_introZoom), &g_frameTime);
		g_introZoom = zoom;
		if (!(g_viewAspect >= k_0_01f))
			BITS(g_viewAspect) = 0x3c23d70a;   /* 0.01 */
		if (zoom >= k_100f) {
			g_screen = 9999;
			g_nextScreen = 9999;
			g_replayRunning = 1;
			BITS(g_cursorBlink) = 0;
		}
	}
	menu_frameBegin();
	switch (g_screen) {
	case 100: menuState100_intro(); break;
	case 200: menu_drawVersion(); break;
	case 210: menuState210_frame(); break;
	case 300: menuState300_frame(); break;
	case 400: menuState400_frame(); break;
	case 500: menuState500_missionSelect(); break;
	case 600: menuState600_setup(); break;
	case 700: menuState700_armCenter(); break;
	case 800: menuState800_gameRoom(); break;
	case 900: menuState900_skirmishSetup(); break;
	}
	if (g_dialogPending)
		menu_drawMessageBox();
	if (g_paused)
		menu_drawInputLine(g_chatCaretX, g_chatCaretY);
	glLoadIdentity();
	if (g_screen != 9999 && !g_profileIntro)
		PATCHED_CALL(0x41fc28, void, void)();   /* menu_drawCursor; the patch DLL draws its own cursor here */
	glDisable(0xbe2);   /* GL_BLEND */
	glFinish();
	SwapBuffers(g_desktopDC);
	switch (g_fovKeys) {
	case 1:
		if (g_viewAngle > k_5f)
			g_viewAngle = fsub_m(fld_m(&g_viewAngle), (const float *)ADDR(k_5f));
		break;
	case 2:
		if (!(g_viewAngle >= k_45f))
			g_viewAngle = fadd_m(fld_m(&g_viewAngle), (const float *)ADDR(k_5f));
		break;
	}
	long double now = timer_now();
	g_clockNow = now;
	if (g_showFps) {
		g_fpsFrameClock = now;
		int frames = ++g_menuFrameCount;
		long double second = now - g_fpsSecondStart;
		double secondStored = f64(second);
		g_fpsSecondSoFar = secondStored;
		if (second >= k_1) {
			g_menuFrameCount = 0;
			g_fps = (long double)frames / secondStored;
			g_fpsSecondStart = now;
		}
	}
	long double rate = k_1 / (now - g_lastFrameClock);
	g_frameRate = rate;
	long double frame = fdivr_m(rate, (const float *)ADDR(k_60f));   /* 60 / rate */
	g_frameTime = frame;
	if (frame > k_20f)
		g_frameTime = 1.0f;
	g_lastFrameClock = now;
}
#undef F
#undef D

/* a countdown (a float in the scene) taken down by the frame's time while above 0, stopping at 0 */
static void count_down(u8 *s, u32 offset, const float *dt)
{
	float *t = (float *)(s + offset);
	const float *zero = (const float *)ADDR(k_0f);
	if (*t > *zero) {
		long double left = fsub_m(fld_m(t), dt);
		*t = f32(left);
		if (!(left >= *zero))
			*(u32 *)RELOC(t) = 0;
	}
}

/* 0x48b200 (thiscall on the scene): the playing state's frame. The match set up first when it is not yet
   (+0x233cc28 0: game_processGameModeInit); frameTimer_average (its answer dropped); the frame's time (+0x44) added to the
   second's fraction (+0x233cc34) and to the FPS window (+0x2340c90); three countdowns (+0x233cc40, +0x2342f02,
   +0x2340d39). Past a whole second the seconds (+0x233cc30) take it, and the frame and packet counts of the window
   (+0x2340c80 / +0x2340c84) become rates (+0x2340c88 / +0x2340c8c; 0 for an empty window), the window cleared. Then
   the input, the game mode and, in state 2, the HUD pass (through the call site the patch DLL retargets). A quit (+0x23432cf 1) stops the music and answers 0; else
   the state (+0x233cc20) */
int THISCALL (match_inputState2)(u8 *s)
{
#define FIELD(type, offset) GAME_VAR(type, s + (offset))
	const float *dt = (const float *)(s + 0x44);
	if (FIELD(int, 0x233cc28) == 0)
		game_processGameModeInit(s);
	(void)frameTimer_average(s);
	long double second = fadd_m(fld_m(dt), (const float *)(s + 0x233cc34));
	FIELD(float, 0x233cc34) = f32(second);
	float window = f32(fadd_m(fld_m((const float *)(s + 0x2340c90)), dt));
	FIELD(float, 0x2340c90) = window;
	count_down(s, 0x233cc40, dt);
	count_down(s, 0x2342f02, dt);
	count_down(s, 0x2340d39, dt);
	if (second > k_1f) {
		int whole = ftol(second);
		FIELD(int, 0x233cc30) += whole;
		FIELD(float, 0x233cc34) = f32(second - whole);
		if (window > k_0f) {
			FIELD(float, 0x2340c88) = f32((long double)FIELD(int, 0x2340c80) / window);
			FIELD(float, 0x2340c8c) = f32((long double)FIELD(int, 0x2340c84) / window);
		} else
			FIELD(int, 0x2340c88) = FIELD(int, 0x2340c8c) = 0;
		FIELD(int, 0x2340c90) = FIELD(int, 0x2340c80) = FIELD(int, 0x2340c84) = 0;
	}
	match_combatInput(s);
	game_processGameMode(s);
	if (FIELD(int, 0x233cc20) == 2)
		PATCHED_THISCALL(0x48b386, void, void *)(s);   /* hud_pass; the patch DLL calls its hud_pass_wrap here */
	if (FIELD(int, 0x23432cf) == 1) {
		music_shutdown();
		return 0;
	}
	return FIELD(int, 0x233cc20);
#undef FIELD
}

#define S(type, offset) GAME_VAR(type, s + (offset))
#define KEY(at) GAME_VAR(int, at)

/* either key of a binding (its two key globals) pressed this frame / held */
static int pressed2(u32 a, u32 b) { return input_justPressed(KEY(a)) || input_justPressed(KEY(b)); }
static int held2(u32 a, u32 b) { return input_isDown(KEY(a)) || input_isDown(KEY(b)); }

/* the mouse's offset from the screen centre (+0x2343293 vertical, inverted by the setting 0x4df000; +0x2343297
   horizontal, negated when steer is set) scaled by the sensitivity (0x4df008: ((s 0.02)^2 + 1) / 2), and the
   pointer put back in the centre (0x4ded68 / 0x4ded6c) */
static void mouse_offset(u8 *s, int steer)
{
	S(int, 0x2343257) = g_mouseX;
	S(int, 0x234325b) = g_mouseY;
	long double dy = (long double)(S(int, 0x234325b) - gfx_getHeight() / 2);
	S(float, 0x2343293) = f32(g_mouseInvert ? -dy : dy);
	long double dx = (long double)(S(int, 0x2343257) - gfx_getWidth() / 2);
	if (steer)
		dx = -dx;
	S(float, 0x2343297) = f32(dx);
	long double k = fmul_m((long double)g_mouseSensitivity, (const float *)IMG(0x4aa480));
	long double f = fmul_m(fadd_m(k * k, (const float *)ADDR(k_1f)), (const float *)ADDR(k_0_5f));
	S(float, 0x2343293) = f32(fmul_m(f, (const float *)(s + 0x2343293)));
	S(float, 0x2343297) = f32(steer ? fmul_m(f, (const float *)(s + 0x2343297)) : dx * f);
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
}

/* the weapon slot keys: slot 1 .. 9, 0 (+0x23424f2), each also asking for the switch (+0x2340c6c, +0x23432cb) */
static const u32 k_slotKeys[10][2] = { { IMG(0x4dec90), 1 }, { IMG(0x4dec8c), 2 }, { IMG(0x4deb5c), 3 }, { IMG(0x4deb58), 4 }, { IMG(0x4deb64), 5 },
                                       { IMG(0x4deb60), 6 }, { IMG(0x4deb6c), 7 }, { IMG(0x4deb68), 8 }, { IMG(0x4deb70), 9 }, { IMG(0x4deb78), 0 } };
/* the radio message keys (+0x2343307 one less than the message; the first six 10 more with the modifier 0x67ef24) */
static const u32 k_radioKeys[10] = { ADDR(g_dik1), ADDR(g_dik2), ADDR(g_dik3), ADDR(g_dik4), IMG(0x4e0c78), IMG(0x4e0c7c), IMG(0x4e0c80), IMG(0x4e0c84), IMG(0x4e0c88), IMG(0x4e0460) };
/* the held controls: the binding's two keys and the flag they set */
static const u32 k_heldKeys[10][2] = { { IMG(0x4def30), 0x234325f }, { ADDR(g_keyFreeCam2), 0x234326b }, { ADDR(g_keyFreeCam3), 0x234326f },
                                       { ADDR(g_keyFreeCam0), 0x2343263 }, { ADDR(g_keyFreeCam1), 0x2343267 }, { IMG(0x4def40), 0x2343273 },
                                       { IMG(0x4def48), 0x2343277 }, { IMG(0x4def98), 0x234328b }, { IMG(0x4defe0), 0x234328f },
                                       { IMG(0x4def38), 0x2343283 } };
/* the view keys (+0x2343287: the last held wins, else -1) */
static const u32 k_viewKeys[6] = { IMG(0x4def78), IMG(0x4def80), IMG(0x4def88), IMG(0x4def90), IMG(0x4def68), IMG(0x4def70) };

/* 0x49d290 (thiscall on the game object): the match's input for this frame (match_resetInputState first; nothing
   more before the match runs, +0x233c9e8). In play (no menu +0x2340d35 / +0x2340cf4): with the own view (+0x233c9fc
   0) and alive (+0x2340cf0, or a network game, or the local player's +0x1eccb48), the weapon slot and radio keys,
   else the fire keys only; a spectator's view the fire keys held / pressed; then every held control, the view keys,
   the mouse look (above 0.2 s of frame time it is still), quitting (Esc keys when the death timer +0x2340d39 is
   over), the chat keys, the camera mode cycle (+0x233cc10), the scoreboard keys, the message log toggle cycle
   (+0x2340ce8 / ce4 with their notices). In the in-match menu (+0x2340cf4 1) the mouse moves the selection (the
   original's +-50 step, or the patch DLL's menu_nav where it replaced that block), and its keys choose. A network
   end (net_matchOver) quits. Its caller ignores the eax it leaves */
void THISCALL (match_combatInput)(u8 *s)
{
	match_resetInputState(s);
	if (!S(int, 0x233c9e8))
		return;
	if (S(int, 0x2340d35) == 0 && S(int, 0x2340cf4) == 0) {
		if (S(int, 0x233c9fc) == 0) {
			if (S(int, 0x2340cf0) == 0 || (S(int, 8) == 0 && S(int, 0x1eccb48 + S(int, 0x234240d) * 0x8888) == 0)) {
				if (pressed2(IMG(0x4def50), IMG(0x4def54)))
					S(int, 0x23432cf) = 1;
			} else {
				if (g_mouseClick) {
					S(int, 0x234331b) = 1;
					S(int, 0x2340c68) = 1;
				}
				if (S(int, 0x23424f2) >= 0 && g_keyEnter) {
					S(int, 0x234331f) = 1;
					S(int, 0x2340c6c) = 1;
					S(int, 0x23432cb) = 1;
				}
				for (int k = 0; k < 10; k++)
					if (input_justPressed(KEY(k_slotKeys[k][0]))) {
						S(int, 0x23424f2) = k_slotKeys[k][1];
						S(int, 0x2340c6c) = 1;
						S(int, 0x23432cb) = 1;
					}
				S(int, 0x2343307) = 0;
				for (int k = 0; k < 10; k++)
					if (input_justPressed(KEY(k_radioKeys[k])))
						S(int, 0x2343307) = k < 6 ? (input_justPressed(g_dikLShift) ? 10 : 0) + k + 1 : k + 1;
				S(int, 0x2343307)--;
			}
		} else {
			if (held2(IMG(0x4def50), IMG(0x4def54)))
				S(int, 0x234327b) = 1;
			if (pressed2(IMG(0x4def50), IMG(0x4def54)))
				S(int, 0x234327f) = 1;
		}
		for (int k = 0; k < 10; k++)
			if (held2(k_heldKeys[k][0], k_heldKeys[k][0] + 4))
				S(int, k_heldKeys[k][1]) = 1;
		S(int, 0x2343287) = -1;
		for (int k = 0; k < 6; k++)
			if (held2(k_viewKeys[k], k_viewKeys[k] + 4))
				S(int, 0x2343287) = k;
		if (!(S(float, 0x44) >= k_0_2f)) {
			S(int, 0x2343257) = g_mouseX;
			S(int, 0x234325b) = g_mouseY;
			mouse_offset(s, 1);
		} else {
			S(int, 0x2343257) = g_mouseX;
			S(int, 0x234325b) = g_mouseY;
			S(int, 0x2343293) = S(int, 0x2343297) = 0;
			long double k = fmul_m((long double)g_mouseSensitivity, (const float *)IMG(0x4aa480));
			long double f = fmul_m(fadd_m(k * k, (const float *)ADDR(k_1f)), (const float *)ADDR(k_0_5f));
			S(float, 0x2343293) = f32(fmul_m(f, (const float *)(s + 0x2343293)));
			S(float, 0x2343297) = f32(fmul_m(f, (const float *)(s + 0x2343297)));
			g_mouseX = gfx_getWidth() / 2;
			g_mouseY = gfx_getHeight() / 2;
		}
		if (pressed2(ADDR(g_keyLoadingSkip), ADDR(g_keyLoadingSkip2)) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432cf) = 1;
		if (pressed2(IMG(0x4def58), IMG(0x4def5c)))
			S(int, 0x23432eb) = 1;
		if (pressed2(IMG(0x4def60), IMG(0x4def64)))
			S(int, 0x23432ef) = 1;
		if (pressed2(IMG(0x4deff0), IMG(0x4deff4)))
			S(int, 0x23424ee) = S(int, 0x233cc10) == 1 ? 2 : S(int, 0x233cc10) == 2 ? 3 : 1;
		if (pressed2(ADDR(g_keyWatchChat), IMG(0x4defac)) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432fb) = 1;
		else if (pressed2(IMG(0x4defb0), IMG(0x4defb4)) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432ff) = 1;
		if (pressed2(IMG(0x4deff8), IMG(0x4deffc)))
			S(int, 0x2343303) = 1;
		if (input_justPressed(g_dikF11)) {
			if (S(int, 0x2340ce8) == 0) {
				S(int, 0x2340ce8) = 1;
				notice_printCentre((Scene *)s, (const char *)IMG(0x4c7d00));
			} else if (S(int, 0x2340ce4) == 0) {
				S(int, 0x2340ce4) = 1;
				notice_printCentre((Scene *)s, (const char *)IMG(0x4c7cf0));
			} else {
				S(int, 0x2340ce8) = S(int, 0x2340ce4) = 0;
				notice_printCentre((Scene *)s, (const char *)IMG(0x4c7ce4));
			}
		}
	} else if (S(int, 0x2340cf4) == 1) {
		mouse_offset(s, 0);
		if (code_matches(0x49ddcb, "56 e8 ?? ?? ?? ?? 59 e9"))
			PATCHED_CALL(0x49ddcc, void, void *)(s);   /* the patch DLL's menu_nav; its block then jumps on to 0x49de23 */
		else {
			const float *down = (const float *)ADDR(k_m50f), *up = (const float *)ADDR(k_50f);
			if (!(S(float, 0x2343293) >= *down) || !(S(float, 0x2343297) >= *down))
				S(int, 0x234330b) = 1;
			if (S(float, 0x2343293) > *up || S(float, 0x2343297) > *up)
				S(int, 0x234330f) = 1;
		}
		if (pressed2(IMG(0x4def50), IMG(0x4def54)))
			S(int, 0x2343313) = 1;
		S(int, 0x2343293) = S(int, 0x2343297) = 0;
		if (input_justPressed(g_dikLeft) || input_justPressed(g_dikUp))
			S(int, 0x234330b) = 1;
		if (input_justPressed(g_dikRight) || input_justPressed(g_dikDown))
			S(int, 0x234330f) = 1;
		if (input_justPressed(g_dikEnter) || input_justPressed(g_dikSpace))
			S(int, 0x2343313) = 1;
		if (input_justPressed(g_dikEscape))
			S(int, 0x2343317) = 1;
	}
	if (net_matchOver())
		S(int, 0x23432cf) = 1;
}
#undef S
#undef KEY

#define S(type, offset) GAME_VAR(type, s + (offset))

/* (0, 10000, 0) turned about x by pitch, then about z by yaw (tenths of a degree) */
static void far_point(float *v, int pitch, int yaw)
{
	v[0] = 0;
	GAME_VAR(u32, &v[1]) = 0x461c4000;
	v[2] = 0;
	Vec3_rotateAxis(v, 1, pitch);
	Vec3_rotateAxis(v, 2, yaw);
}

/* the point v about the actor's position (+0x154) */
static void about(float *out, const float *v, const u8 *actor)
{
	for (int k = 0; k < 3; k++)
		out[k] = f32(fadd_m(fld_m(&v[k]), (const float *)(actor + 0x154) + k));
}

/* the free-camera part steps: the flag (F1 .. F5 held), the player's part field, the setter, the table size */
static const u32 k_partSteps[5][4] = { { 0x23432d3, 0x30c, FN_ADDR(actor_setActorTypeHeadInfoBy, 0x473b10), 0x15de6c8 }, { 0x23432d7, 0x310, FN_ADDR(actor_setActorTypeChestInfoBy, 0x473c20), 0x15fff84 },
                                       { 0x23432db, 0x314, FN_ADDR(actor_setActorTypeArmInfoBy, 0x473d30), 0x163b588 }, { 0x23432df, 0x318, FN_ADDR(actor_setActorTypeLegInfoBy, 0x473e40), 0x1679b34 },
                                       { 0x23432e3, 0x31c, FN_ADDR(actor_setActorTypeBoosterInfoBy, 0x473f50), 0x16c5178 } };
/* the held keys and their flags: right button, A, D, W, S, Q, E, left button, shift */
static const u32 k_freeKeys[9][2] = { { 2, 0x234325f }, { 0x41, 0x234326b }, { 0x44, 0x234326f }, { 0x57, 0x2343263 }, { 0x53, 0x2343267 },
                                      { 0x51, 0x2343273 }, { 0x45, 0x2343277 }, { 1, 0x234327b }, { 0x10, 0x2343283 } };

/* 0x48a370 (thiscall on the game object): the free camera / test mode's frame. On its first frame the camera
   presets (+0x233ca30, ten of six fields) copied to the working set (+0x233cb20), the game clock read and the
   cursor centred. The keys (Windows virtual keys) set the input flags; ctrl with up / down zooms, else up / down /
   left / right turn the camera (+0x233ca28 pitch within +-890, +0x233ca2c heading wrapped at 3600); space resets it;
   Z / X (or shift with them) step the local player's (+0x234240d) parts held by F1 .. F6 down / up through their
   tables (the weapon slot by its item, selected again); the camera is placed behind the actor (camera_setupView);
   unless replaying (+0x2340ce0) the actors, bullets and particles move and the actor's ammunition is halved; the
   scene is drawn, with a 100 x 150 grid of lines about the actor when +0x2340cd0. Returns 0 once Esc was pressed,
   else 3 (this mode again) */
u32 THISCALL (match_inputState3)(u8 *s)
{
	u8 *stage = s + 0x1f36c8;
	if (S(int, 0x233cc28) == 0) {
		S(int, 0x234240d) = 0;
		S(int, 0x233ca28) = S(int, 0x233ca2c) = 0;
		for (S(int, 0x233cc10) = 0; S(int, 0x233cc10) < 10; S(int, 0x233cc10)++)
			for (int f = 0; f < 6; f++)
				S(u32, 0x233cb20 + f * 0x28 + S(int, 0x233cc10) * 4) = S(u32, 0x233ca30 + f * 0x28 + S(int, 0x233cc10) * 4);
		S(int, 0x233cc10) = 0;
		timer_getGameTime(s + 0xc);
		int y = gfx_getHeight() / 2;
		input_setCursorPos(gfx_getWidth() / 2, y);
	}
	u8 *actor = s + 0x1ecca70 + S(int, 0x234240d) * 0x8888;
	u8 *player = s + 0x1755230 + GAME_VAR(int, actor + 0x10c) * 0x47fd2;
	for (int k = 0; k < 9; k++)
		S(int, k_freeKeys[k][1]) = input_asyncKeyDown(k_freeKeys[k][0]) ? 1 : 0;
	S(int, 0x2343287) = -1;
	for (int k = 0; k < 6; k++)
		if (input_asyncKeyDown('1' + k))
			S(int, 0x2343287) = k;
	if (input_asyncKeyDown(0x11)) {
		S(int, 0x23432ab) = input_asyncKeyDown(0x26) ? 1 : 0;
		S(int, 0x23432af) = input_asyncKeyDown(0x28) ? 1 : 0;
		S(int, 0x23432bb) = 0;
		S(int, 0x23432bf) = 0;
	} else {
		S(int, 0x23432ab) = S(int, 0x23432af) = 0;
		S(int, 0x23432bb) = input_asyncKeyDown(0x26) ? 1 : 0;
		S(int, 0x23432bf) = input_asyncKeyDown(0x28) ? 1 : 0;
	}
	S(int, 0x23432b3) = input_asyncKeyDown(0x25) ? 1 : 0;
	S(int, 0x23432b7) = input_asyncKeyDown(0x27) ? 1 : 0;
	const int *cursor = input_getCursorPos();
	S(int, 0x2343257) = cursor[0];
	S(int, 0x234325b) = cursor[1];
	S(float, 0x2343293) = f32((long double)(S(int, 0x234325b) - gfx_getHeight() / 2));
	S(float, 0x2343297) = f32(-(long double)(S(int, 0x2343257) - gfx_getWidth() / 2));
	int y = gfx_getHeight() / 2;
	input_setCursorPos(gfx_getWidth() / 2, y);
	S(int, 0x23432cb) = input_asyncKeyPressed(0x20) ? 1 : 0;
	S(int, 0x23432cf) = input_asyncKeyPressed(0x1b) ? 1 : 0;
	for (int k = 0; k < 6; k++)
		S(int, 0x23432d3 + k * 4) = input_asyncKeyDown(0x70 + k) ? 1 : 0;
	S(int, 0x23432f3) = input_asyncKeyPressed('Z') || (input_asyncKeyDown(0x10) && input_asyncKeyDown('Z'));
	S(int, 0x23432f7) = input_asyncKeyPressed('X') || (input_asyncKeyDown(0x10) && input_asyncKeyDown('X'));
	frameTimer_average(s);
	float slow = f32(fld_m((const float *)ADDR(k_1f)) - fmul_m(fld_m((const float *)(s + 0x44)), (const float *)IMG(0x4aa488)));
	float turn = f32(fmul_m(fld_m((const float *)(s + 0x44)), (const float *)IMG(0x4aa484)));
	long double look = fmul_m(fld_m((const float *)(s + 0x44)), (const float *)ADDR(k_100f));
	float yaw = f32(look * S(float, 0x2343297)), pitch = f32(look * S(float, 0x2343293));
	actor_setInput(stage, 0, S(u32, 0x2343263), S(u32, 0x2343267), S(u32, 0x234326b), S(u32, 0x234326f), *(u32 *)&pitch, *(u32 *)&yaw,
	             S(u32, 0x234327b), S(u32, 0x234325f), S(u32, 0x2343283), S(u32, 0x2343287), 0, 0);
	if (S(int, 0x23432bb)) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233ca28)), &turn);
		S(float, 0x233ca28) = f32(v);
		if (!(v >= k_m890f))
			S(u32, 0x233ca28) = 0xc45e8000;   /* -890 */
	}
	if (S(int, 0x23432bf)) {
		long double v = fadd_m(fld_m(&turn), (const float *)(s + 0x233ca28));
		S(float, 0x233ca28) = f32(v);
		if (v > k_890f)
			S(u32, 0x233ca28) = 0x445e8000;   /* 890 */
	}
	if (S(int, 0x23432b3)) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233ca2c)), &turn);
		S(float, 0x233ca2c) = f32(v);
		if (!(v >= 0))
			S(float, 0x233ca2c) = f32(fadd_m(v, (const float *)ADDR(k_3600f)));
	}
	if (S(int, 0x23432b7)) {
		long double v = fadd_m(fld_m(&turn), (const float *)(s + 0x233ca2c));
		S(float, 0x233ca2c) = f32(v);
		if (v >= k_3600f)
			S(float, 0x233ca2c) = f32(fsub_m(v, (const float *)ADDR(k_3600f)));
	}
	float *zoom = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
	if (S(int, 0x23432ab)) {
		*zoom = f32(fmul_m(fld_m(&slow), zoom));
		if (!(*zoom >= k_500f))
			GAME_VAR(u32, zoom) = 0x43fa0000;   /* 500 */
	}
	zoom = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
	if (S(int, 0x23432af)) {
		*zoom = f32(fdiv_m(fld_m(zoom), &slow));
		if (*zoom > k_10000f)
			GAME_VAR(u32, zoom) = 0x461c4000;   /* 10000 */
	}
	if (S(int, 0x23432cb)) {
		S(u32, 0x233cb70 + S(int, 0x233cc10) * 4) = 0x44fa0000;   /* 2000 */
		S(int, 0x233ca28) = S(int, 0x233ca2c) = 0;
		GAME_VAR(int, actor + 0x160) = GAME_VAR(int, actor + 0x164) = 0;
		GAME_VAR(int, actor + 0x18c) = GAME_VAR(int, actor + 0x190) = 0;
	}
	int item = -1;
	if (S(int, 0x23432f3) == 1) {
		for (int k = 0; k < 5; k++)
			if (S(int, k_partSteps[k][0]) == 1 && GAME_VAR(int, player + k_partSteps[k][1]) > 0)
				GAME_THISCALL(k_partSteps[k][2], int, void *, int, int)(stage, GAME_VAR(int, actor + 0x10c), GAME_VAR(int, player + k_partSteps[k][1]) - 1);
		if (S(int, 0x23432e7) == 1) {
			int it = GAME_VAR(int, player + 0x320 + GAME_VAR(int, actor + 0x140) * 4);
			if (it > 0)
				item = it - 1;
		}
	} else if (S(int, 0x23432f7) == 1) {
		for (int k = 0; k < 5; k++)
			if (S(int, k_partSteps[k][0]) == 1 && GAME_VAR(int, player + k_partSteps[k][1]) < S(int, k_partSteps[k][3]) - 1)
				GAME_THISCALL(k_partSteps[k][2], int, void *, int, int)(stage, GAME_VAR(int, actor + 0x10c), GAME_VAR(int, player + k_partSteps[k][1]) + 1);
		if (S(int, 0x23432e7) == 1) {
			int it = GAME_VAR(int, player + 0x320 + GAME_VAR(int, actor + 0x140) * 4);
			if (it < S(int, 0x175522c) - 1)
				item = it + 1;
		}
	}
	if (item >= 0) {
		int slot = S(int, 0x16c7f38 + item * 0x2e18) ? 4 : 0;
		actor_setActorTypeItemInfoBy((Stage *)stage, 0, slot, item);
		actor_selectWeapon((Stage *)stage, 0, slot);
	}
	float *cam = (float *)(s + 0x233ca04), *dir = (float *)(s + 0x233ca10), *up = (float *)(s + 0x233ca1c);
	cam[0] = cam[1] = 0;
	cam[2] = f32(fld_m((const float *)(s + 0x233cb70) + S(int, 0x233cc10)));
	Vec3_rotateAxis(cam, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(cam, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	for (int k = 0; k < 3; k++)
		cam[k] = f32(fadd_m(fld_m((const float *)(actor + 0x180) + k), &cam[k]));
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m((const float *)(actor + 0x180) + k), &cam[k]));
	up[0] = 0;
	GAME_VAR(u32, &up[1]) = 0x3f800000;
	up[2] = 0;
	Vec3_rotateAxis(up, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(up, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = game_clock();
	GAME_THISFN(camera_setupView, 0x4729b0, void, void *, float *, float *, float *, u32, int, int, u32, u32, u32)(stage, cam, dir, up, *(u32 *)&fov, w, h,
	                                                                                             *(u32 *)&near, *(u32 *)&far, S(u32, 0x44));   /* camera_setupView */
	if (S(int, 0x2340ce0) == 0) {
		actor_updateAll(stage, S(u32, 0x44));
		bullet_updateAll(stage, S(u32, 0x44));
		stage_updateEffects(stage, S(u32, 0x44));
		for (int k = 0; k < 4; k++) {
			u8 *me = s + 0x1ecca70 + S(int, 0x234240d) * 0x8888;
			GAME_VAR(int, me + 0x130 + k * 4) = GAME_VAR(int, me + 0x28 + k * 4) / 2;
		}
	}
	S(int, 0x233cc28)++;
	glClearColor_stored(((const u32[]){ 0x3dcccccd, 0x3f000000, 0x3f800000 }));
	glClearDepth(1.0);
	glClear(0x4100);
	gfx_setProjectionHud(1, 1.0f);
	ViewVolume_captureMatrices(s + 0x74, 0, s + 0x22e7068);
	ViewVolume_reset(s + 0x74);
	if (S(int, 0x2340cd0) == 1)
		for (int pitch = 0; pitch < 0x708; pitch += 100)
			for (int yaw = 0; yaw < 0xe10; yaw += 150) {
				float a[3], b[3], pa[3], pb[3];
				far_point(a, pitch, yaw);
				far_point(b, pitch + 100, yaw);
				about(pb, b, actor);
				about(pa, a, actor);
				ViewVolume_addSegment(s + 0x74, (const void *)ADDR(g_colourMaskRed), pa, pb, 1);
				far_point(a, pitch, yaw);
				far_point(b, pitch, yaw + 150);
				about(pb, b, actor);
				about(pa, a, actor);
				ViewVolume_addSegment(s + 0x74, (const void *)ADDR(g_colourMaskRed), pa, pb, 1);
			}
	stage_drawActors((Stage *)stage, s + 0x74, -1);
	stage_drawBullets(stage, s + 0x74);
	stage_drawProjectiles((Stage *)stage, s + 0x74);
	render_drawObjects(s + 0x74, S(int, 0x1f1664), 0.0f);
	gfx_setProjectionHud(0, 1.0f);
	return S(int, 0x23432cf) == 1 ? 0 : 3;
}
#undef S

#define S(type, offset) GAME_VAR(type, s + (offset))
#define K(address) ((const float *)RELOC(address))
#define ACTOR(i, offset) GAME_VAR(float, s + 0x1eccbc4 + (i) * 0x8888 + (offset))   /* an actor's field, from its position */
#define ACTOR_INT(i, offset) GAME_VAR(int, s + (offset) + (i) * 0x8888)

/* the camera back at the map's start view (+0x22ee228: position, pitch, heading) */
static void start_view(u8 *s)
{
	memcpy(s + 0x233ca04, s + 0x22ee228, 12);
	S(u32, 0x233ca28) = S(u32, 0x22ee234);
	S(u32, 0x233ca2c) = S(u32, 0x22ee238);
}

/* the current camera preset (+0x233cc10) back from its stored one: six fields of ten */
static void preset_reset(u8 *s)
{
	for (int f = 0; f < 6; f++)
		S(u32, 0x233cb20 + f * 0x28 + S(int, 0x233cc10) * 4) = S(u32, 0x233ca30 + f * 0x28 + S(int, 0x233cc10) * 4);
}

/* following no one: the free camera from the start view */
static void unfollow(u8 *s)
{
	S(int, 0x2340c64) = -1;
	S(int, 0x233c9fc) = 0;
	S(int, 0x2340c70) = 1;
	start_view(s);
}

/* the game's next random number below n (its table 0xa106f8 by the counter 0xa1efb8) */
static u32 rand_below(u32 n)
{
	u32 r = GAME_VAR(u32, 0xa106f8 + (g_randPos & 0xfff) * 4) % n;
	g_randPos++;
	return r;
}

/* the view angle by step (narrower with +0x234328b), kept within 10 .. 60 */
static void zoom_view(u8 *s, const float *step)
{
	if (S(int, 0x234328b)) {
		float a = f32(fsub_m((long double)game_clock(), step));
		view_setAngle(BITS(a));
		if (!(game_clock() >= 10.0f))
			view_setAngle(0x41200000);   /* 10 */
	} else {
		float a = f32(fadd_m((long double)game_clock(), step));
		view_setAngle(BITS(a));
		if (game_clock() > 60.0f)
			view_setAngle(0x42700000);   /* 60 */
	}
}

/* the end of the replay file (or the skip key): the next replay (a random one with +0x9eeac0, else the next in
   order, the list wrapping round with +0x4b2a7c) with the scene reset; 0 when the list is done (the viewer quits) */
static int replay_next(u8 *s)
{
	u8 *stage = s + 0x1f36c8;
	if (g_replayRandomOrder == 1) {
		scene_resetActors(stage);
		scene_reset(stage);
		S(u32, 0x1f35c0) = S(int, 0x1f35bc) > 0 ? rand_below(S(u32, 0x1f35bc)) : 0;
	} else {
		if (++S(int, 0x1f35c0) >= S(int, 0x1f35bc)) {
			if (g_replayWrap != 1) {
				S(int, 0x23432cf) = 1;
				return 0;
			}
			S(int, 0x1f35c0) = 0;
		}
		scene_resetActors(stage);
		scene_reset(stage);
	}
	S(int, 0x233cc20) = 1;
	S(int, 0x233cc28) = 0;
	return 1;
}

/* the player followed: a number key (f, 0 ..), the next live player (+0x234331b), or a random one now and then
   (none yet, gone, or followed 14 s); then the camera preset: the next one (+0x234331f) or a random one after 7 s */
static void choose_followed(u8 *s, int f)
{
	int n = S(int, 0x2221f90);
	if (n <= 0) {
		S(int, 0x2340c64) = -1;
		return;
	}
	if (f >= 0) {
		if (ACTOR_INT(f, 0x1eccb88) >= 0) {
			S(int, 0x2340c64) = f;
			S(int, 0x2340c70) = 0;
			S(int, 0x2340c68) = 1;
		}
	} else if (S(int, 0x234331b) == 1) {
		int cur = S(int, 0x2340c64), next = cur + 1;
		if (next == n)
			unfollow(s);
		else
			for (;;) {
				if (ACTOR_INT(next, 0x1eccb48) == 1) {
					S(int, 0x2340c64) = next;
					S(int, 0x2340c70) = 0;
					break;
				}
				if (++next >= n) {
					unfollow(s);
					break;
				}
				if (next == cur)
					break;
			}
	} else if ((S(int, 0x2340c70) == 0 && S(int, 0x2340c64) < 0) || S(int, 0x2340c64) >= n || S(float, 0x233cc38) > 14.0f) {
		u32 r = rand_below(n);
		S(u32, 0x2340c64) = r;
		if (ACTOR_INT(r, 0x1eccb78) == 1)
			S(int, 0x233cc38) = 0;
		else
			S(int, 0x2340c64) = -1;
	}
	if (S(int, 0x234331f) == 1)
		S(int, 0x233cc10) = (S(int, 0x233cc10) + 1) % 10;
	else if (S(float, 0x233cc3c) > 7.0f) {
		u32 r = rand_below(100);
		S(int, 0x233cc10) = r < 5 ? 0 : r < 35 ? 1 : r < 45 ? 2 : r < 50 ? 3 : r < 55 ? 4 : r < 60 ? 5 : r < 65 ? 6 : r < 70 ? 7 : 8 + (r >= 75);
		S(int, 0x233cc3c) = 0;
	}
}

/* the free camera's move (mv, from the keys) through the world, kept in the map's box (+0xbe2fcc .. +0xbe2fd8);
   facing (0, 0, -1) */
/* the move's results (collision_moveActor's: where it ends, the slide, the distance, the plane) */
typedef struct { float out[3], delta[3], dist, plane[4]; } Move;

static void free_camera(u8 *s, const float *mv, u32 filter, Move *m)
{
	float *cam = (float *)(s + 0x233ca04), *out = m->out, *delta = m->delta;
	int hit = collision_moveActor(s + 0x1f36c8, 500.0f, cam, mv, 0x43fa0000, 0, out, delta, &m->dist, m->plane, filter);
	memcpy(cam, out, 12);
	if (hit == 1) {
		cam[0] = f32(fadd_m(fld_m(&delta[0]), &cam[0]));
		cam[2] = f32(fadd_m(fld_m(&delta[2]), &cam[2]));
		cam[1] = f32(fadd_m(fld_m(&delta[1]), &cam[1]));
	}
	for (int k = 0; k < 3; k++) {
		if (!(cam[k] >= S(float, 0xbe2fcc + k * 4)))
			BITS(cam[k]) = S(u32, 0xbe2fcc + k * 4);
		else if (cam[k] > S(float, 0xbe2fd8 + k * 4))
			BITS(cam[k]) = S(u32, 0xbe2fd8 + k * 4);
	}
	float *dir = (float *)(s + 0x233ca10);
	dir[0] = dir[1] = 0;
	BITS(dir[2]) = 0xbf800000;
}

/* the preset's pitch (+0x233ca28) and heading (+0x233ca2c) from its table (index at +preset), the actor's own
   (+0x160 / +0x164) added unless the preset fixes them; the pitch within +-890 */
static void preset_angles(u8 *s, const u8 *t, u32 preset)
{
	int i = S(int, preset);
	S(float, 0x233ca28) = (float)fld_m((const float *)(s + 0x233cb20) + i);
	if (S(int, 0x233cbc0 + S(int, preset) * 4) == 0)
		S(float, 0x233ca28) = f32(fadd_m(fld_m((const float *)(s + 0x233cb20) + i), (const float *)(RELOC(t) + 0x160)));
	if (S(float, 0x233ca28) > 890.0f)
		S(u32, 0x233ca28) = 0x445e8000;
	if (!(S(float, 0x233ca28) >= -890.0f))
		S(u32, 0x233ca28) = 0xc45e8000;
	i = S(int, preset);
	S(float, 0x233ca2c) = (float)fld_m((const float *)(s + 0x233cb48) + i);
	if (S(int, 0x233cbe8 + S(int, preset) * 4) == 0)
		S(float, 0x233ca2c) = f32(fadd_m(fld_m((const float *)(s + 0x233cb48) + i), (const float *)(RELOC(t) + 0x164)));
}

/* the camera pulled back by the preset's zoom (+0x233cb70) from 0.85 of the actor t's height (its position with
   eye 0), short of what is in the way, at most 300 off; facing (0, 0, 1) */
static void orbit_from(u8 *s, const u8 *t, u32 preset, int eye)
{
	float *cam = (float *)(s + 0x233ca04), a[3] = { 0, 0, 0 }, b[3], to[3], d[3];
	if (eye) {
		a[1] = f32(fmul_m(fld_m((const float *)(RELOC(t) + 0x3e8)), K(0x4aa478)));   /* 0.85 */
		Vec3_rotateAxis(a, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
		Vec3_rotateAxis(a, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	}
	b[0] = b[1] = 0;
	b[2] = f32(fsub_m(-fld_m((const float *)(s + 0x233cb70) + S(int, preset)), K(0x4aa440)));   /* - zoom - 300 */
	Vec3_rotateAxis(b, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(b, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fld_m(&a[k]), (const float *)(RELOC(t) + 0x154) + k));
	to[0] = f32(fadd_m(fld_m(&b[0]), &a[0]));
	to[1] = f32(fadd_m(fld_m(&a[1]), &b[1]));
	to[2] = f32(fadd_m(fld_m(&a[2]), &b[2]));
	if (collision_rayTrace(s + 0x1f36c8, a, to, cam) == 0)
		memcpy(cam, to, 12);
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(&cam[k]), &a[k]));
	if (Vec3_normalize(d) > 300.0f) {
		long double dx = fmul_m(fld_m(&d[0]), K(0x4aa440));
		float dy = f32(fmul_m(fld_m(&d[1]), K(0x4aa440))), dz = f32(fmul_m(fld_m(&d[2]), K(0x4aa440)));
		cam[0] = f32(fld_m(&cam[0]) - dx);
		cam[1] = f32(fsub_m(fld_m(&cam[1]), &dy));
		cam[2] = f32(fsub_m(fld_m(&cam[2]), &dz));
	}
	float *dir = (float *)(s + 0x233ca10);
	dir[0] = dir[1] = 0;
	BITS(dir[2]) = 0x3f800000;
}

/* an actor's record (0x8888 bytes from +0x1ecca70) */
#define ACTOR_AT(i) (s + 0x1ecca70 + (i) * 0x8888)

/* preset orbiting the followed player (the preset index at +0x233cc10) */
static void orbit_camera(u8 *s, int i)
{
	(void)i;
	preset_angles(s, ACTOR_AT(S(int, 0x2340c64)), 0x233cc10);
	orbit_from(s, ACTOR_AT(S(int, 0x2340c64)), 0x233cc10, 1);
}

/* preset 1: the followed player and the nearest other live one, the camera on the line through both beyond the
   followed one (the angle by their distance); alone, a point 5 heights ahead. Looks at their middle (+0x233cc14) */
static void pair_camera(u8 *s)
{
	int me = S(int, 0x2340c64), best = -1, n = S(int, 0x2221f90);
	float *mid = (float *)(s + 0x233cc14), *cam = (float *)(s + 0x233ca04), *dir = (float *)(s + 0x233ca10), d[3], t[3];
	float nearest;
	BITS(nearest) = 0x7f7fffff;
	for (int j = 0; j < n; j++)
		if (ACTOR_INT(j, 0x1eccb78) == 1 && j != me) {
			for (int k = 0; k < 3; k++)
				d[k] = f32(fsub_m(fld_m(&ACTOR(me, k * 4)), &ACTOR(j, k * 4)));
			long double dist = fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1]);
			dist = dist + fmul_m(fld_m(&d[0]), &d[0]);
			if (!(dist >= nearest)) {
				nearest = (float)dist;
				best = j;
			}
		}
	if (best >= 0) {
		long double x = fadd_m(fld_m(&ACTOR(best, 0)), &ACTOR(me, 0));
		float y = f32(fadd_m(fld_m(&ACTOR(best, 4)), &ACTOR(me, 4))), z = f32(fadd_m(fld_m(&ACTOR(best, 8)), &ACTOR(me, 8)));
		mid[0] = f32(fmul_m(x, K(0x4a942c)));
		mid[1] = f32(fmul_m(fld_m(&y), K(0x4a942c)));
		mid[2] = f32(fmul_m(fld_m(&z), K(0x4a942c)));
	} else {
		float e[3] = { 0, 0, f32(fmul_m(fld_m(&ACTOR(me, 0x294)), K(0x4a93d0))) };   /* 5 heights */
		Vec3_rotateAxis(e, 2, 100 - ftol(fld_m(&ACTOR(me, 0x10))));
		me = S(int, 0x2340c64);
		for (int k = 0; k < 3; k++)
			mid[k] = f32(fadd_m(fld_m(&e[k]), &ACTOR(me, k * 4)));
	}
	for (int k = 0; k < 3; k++)
		t[k] = dir[k] = f32(fsub_m(fld_m(&ACTOR(me, k * 4)), &mid[k]));
	long double len = Vec3_normalize(dir);
	long double three = fmul_m(fld_m(&ACTOR(S(int, 0x2340c64), 0x294)), K(0x4a9534));
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fmul_m(three, &dir[k]));
	for (int k = 0; k < 3; k++)
		t[k] = f32(fadd_m(fld_m(&t[k]), &dir[k]));
	Vec3_rotateAxis(t, 2, ftol(fmul_m(fsub_m(len, K(0x4aa474)), K(0x4aa470))));   /* (len - 30000) * -0.002 */
	for (int k = 0; k < 3; k++)
		cam[k] = f32(fadd_m(fld_m(&t[k]), &mid[k]));
}

/* the other presets: the look point (+0x233cc14) moved half way to the followed player; when the view to it is
   blocked, the camera goes behind the player's head (its height back along its own heading and pitch) */
/* the look point (+0x233cc14) moved half way to p */
static void look_toward(u8 *s, const float *p)
{
	float *mid = (float *)(s + 0x233cc14);
	long double dx = fsub_m(fld_m(&p[0]), &mid[0]);
	float dy = f32(fsub_m(fld_m(&p[1]), &mid[1])), dz = f32(fsub_m(fld_m(&p[2]), &mid[2]));
	long double hx = fmul_m(dx, K(0x4a942c));
	float hy = f32(fmul_m(fld_m(&dy), K(0x4a942c))), hz = f32(fmul_m(fld_m(&dz), K(0x4a942c)));
	mid[0] = f32(fadd_m(hx, &mid[0]));
	mid[1] = f32(fadd_m(fld_m(&hy), &mid[1]));
	mid[2] = f32(fadd_m(fld_m(&hz), &mid[2]));
}

static void watch_camera(u8 *s)
{
	int me = S(int, 0x2340c64);
	float *mid = (float *)(s + 0x233cc14), *cam = (float *)(s + 0x233ca04), hit[3];
	look_toward(s, &ACTOR(me, 0));
	if (collision_rayTrace(s + 0x1f36c8, cam, mid, hit)) {
		me = S(int, 0x2340c64);
		float e[3] = { 0, 0, f32(-fld_m(&ACTOR(me, 0x294))) };
		Vec3_rotateAxis(e, 1, ftol(fld_m(&ACTOR(me, 0xc))));
		me = S(int, 0x2340c64);
		Vec3_rotateAxis(e, 2, ftol(fld_m(&ACTOR(me, 0x10))));
		me = S(int, 0x2340c64);
		for (int k = 0; k < 3; k++)
			cam[k] = f32(fadd_m(fld_m(&e[k]), &ACTOR(me, k * 4)));
	}
}

/* the direction and up vectors turned by the camera's pitch (+0x233ca28) and heading (+0x233ca2c) */
static void turn_view(u8 *s)
{
	float *dir = (float *)(s + 0x233ca10), *up = (float *)(s + 0x233ca1c);
	Vec3_rotateAxis(dir, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(dir, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	up[0] = 0;
	BITS(up[1]) = 0x3f800000;
	up[2] = 0;
	Vec3_rotateAxis(up, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(up, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
}

/* the free camera's keys: the move (mv) by speed along the view, turned for the held direction keys; up / down,
   three times as fast with +0x2343283; the mouse turns the view (pitch within +-890, heading wrapped at 3600) */
static void free_keys(u8 *s, float *mv, const float *speed, const float *turn)
{
	memcpy(mv, (const void *)ADDR(g_vecZero), 12);
	int bits = S(int, 0x234326b) ? 1 : 0;
	if (S(int, 0x234326f))
		bits |= 0x10;
	if (S(int, 0x234325f) == 0) {
		if (S(int, 0x2343263))
			bits |= 0x100;
		if (S(int, 0x2343267))
			bits |= 0x1000;
	}
	if (bits) {
		mv[2] = f32(-fld_m(speed));
		mv[0] = mv[1] = 0;
		int a = bits == 0x110 ? -450 : bits == 1 ? -2700 : bits == 0x10 ? -900 : bits == 0x101 ? -3150 : bits == 0x1000 ? -1800
		      : bits == 0x1001 ? -2250 : bits == 0x1010 ? -1350 : 0;
		if (a)
			Vec3_rotateAxis(mv, 2, a);
		Vec3_rotateAxis(mv, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
		Vec3_rotateAxis(mv, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	}
	if ((S(int, 0x234325f) && S(int, 0x2343263)) || S(int, 0x2343273))
		mv[1] = f32(fadd_m(fld_m(&mv[1]), speed));
	if ((S(int, 0x234325f) && S(int, 0x2343267)) || S(int, 0x2343277))
		mv[1] = f32(fsub_m(fld_m(&mv[1]), speed));
	if (S(int, 0x2343283))
		for (int k = 0; k < 3; k++)
			mv[k] = f32(fmul_m(fld_m(&mv[k]), K(0x4a9534)));
	long double v = fsubr_m(fmul_m(fld_m(turn), (const float *)(s + 0x2343293)), (const float *)(s + 0x233ca28));
	S(float, 0x233ca28) = (float)v;
	if (v > 890.0f)
		S(u32, 0x233ca28) = 0x445e8000;
	if (!(S(float, 0x233ca28) >= -890.0f))
		S(u32, 0x233ca28) = 0xc45e8000;
	v = fadd_m(fmul_m(fld_m(turn), (const float *)(s + 0x2343297)), (const float *)(s + 0x233ca2c));
	S(float, 0x233ca2c) = (float)v;
	if (v >= 3600.0f)
		S(float, 0x233ca2c) = f32(fsub_m(v, K(0x4a94c8)));
	if (!(S(float, 0x233ca2c) >= 0))
		S(float, 0x233ca2c) = f32(fadd_m(fld_m((const float *)(s + 0x233ca2c)), K(0x4a94c8)));
}

/* a count-down (seconds at +offset) by dt when running; 1 when it ran out this frame */
static int run_down(u8 *s, u32 offset)
{
	if (!(S(float, offset) > 0))
		return 0;
	long double v = fsub_m(fld_m((const float *)(s + offset)), (const float *)(s + 0x44));
	S(float, offset) = (float)v;
	return !(v >= 0);
}

/* the free camera / follow keys: held pairs and the flag each sets */
static const u32 k_replayHeld[7][3] = { { IMG(0x4def30), IMG(0x4def34), 0x234325f }, { ADDR(g_keyFreeCam2), IMG(0x4def14), 0x234326b }, { ADDR(g_keyFreeCam3), IMG(0x4def1c), 0x234326f },
                                        { ADDR(g_keyFreeCam0), IMG(0x4def04), 0x2343263 }, { ADDR(g_keyFreeCam1), IMG(0x4def0c), 0x2343267 }, { IMG(0x4def40), IMG(0x4def44), 0x2343273 },
                                        { IMG(0x4def48), IMG(0x4def4c), 0x2343277 } };
/* the camera preset keys (presets 1 .. 9, 0) */
static const u32 k_presetKeys[10] = { IMG(0x4dec90), IMG(0x4dec8c), IMG(0x4deb5c), IMG(0x4deb58), IMG(0x4deb64), IMG(0x4deb60), IMG(0x4deb6c), IMG(0x4deb68), IMG(0x4deb70), IMG(0x4deb78) };
/* the eight lines of a debug marker's star: the far corner's signs */
static const signed char k_star[8][3] = { { 1, 1, 1 }, { -1, -1, -1 }, { 1, -1, 1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, -1, -1 }, { -1, -1, 1 }, { 1, 1, -1 } };

/* 0x487f00 (thiscall on the game object): the replay viewer's frame. On its first frame (+0x233cc28 0) the camera
   from the start view and its presets reset, the cursor centred. The keys: the free camera's moves, presets 1 .. 9
   and 0, following a player (the follow keys; the mouse buttons for the next player / preset), slow motion
   (+0x2340d21), skip (+0x2340d25), the ranking, the HUD modes, quit; the mouse turns the view. Unless paused
   (+0x2340ce0) the replay file (+0x2340d08) is read up to the replay's time (+0x2340d2d): records of time, sender,
   length and packet handed to net_processGamePacket; at its end the next replay starts (returns 1) or the viewer
   quits. Then the scene's frame (clocks, objects, actors, bullets, particles, items), kill messages, the camera
   (free, or one of the presets about the followed player), the scene drawn (with debug markers for the map's
   points when +0x2340cd4) and the overlay: icons for the followed player's preset and the replay clock, names,
   the ranking, the start count. Returns 0 when the viewer quits (the file closed, the music stopped), else 4 */
u32 THISCALL (replay_frame)(u8 *s)
{
	u8 *stage = s + 0x1f36c8;
	float mv[3];   /* the free camera's move: set by its keys, which a camera now following no one may not have read
	                  this frame (the original then moves by whatever its stack held) */
	Move move;
	if (S(int, 0x233cc28) == 0) {
		start_view(s);
		for (S(int, 0x233cc10) = 0; S(int, 0x233cc10) < 10; S(int, 0x233cc10)++)
			preset_reset(s);
		S(int, 0x233cc10) = 1;
		stage_selectActor((Stage *)stage, -1);
		S(int, 0x2340c64) = -1;
		S(int, 0x2340c68) = S(int, 0x2340c6c) = S(int, 0x2340c70) = 0;
		timer_getGameTime(s + 0xc);
		int y = gfx_getHeight() / 2;
		input_setCursorPos(gfx_getWidth() / 2, y);
		S(int, 0x233cc38) = S(int, 0x233cc3c) = S(int, 0x2342425) = 0;
		S(int, 0x233cc30) = S(int, 0x233cc34) = 0;
		S(int, 0x2340d29) = S(int, 0x2340d2d) = 0;
		events_clear((Scene *)s, 60.0f);
	}
	frameTimer_average(s);
	/* the replay clock (+0x233cc30 whole seconds, +0x233cc34 the fraction) */
	long double t = fadd_m(fld_m((const float *)(s + 0x233cc34)), (const float *)(s + 0x44));
	S(float, 0x233cc34) = (float)t;
	if (t > 1.0f) {
		S(int, 0x233cc30) += ftol(t);
		int whole = ftol(fld_m((const float *)(s + 0x233cc34)));
		S(float, 0x233cc34) = f32(fsubr_m((long double)whole, (const float *)(s + 0x233cc34)));
	}
	match_resetInputState(s);
	for (int k = 0; k < 7; k++)
		if (held2(k_replayHeld[k][0], k_replayHeld[k][1]))
			S(int, k_replayHeld[k][2]) = 1;
	if (g_mouseClick) {
		S(int, 0x234331b) = 1;
		S(int, 0x2340c68) = 1;
	}
	if (g_keyEnter) {
		S(int, 0x234331f) = 1;
		S(int, 0x2340c6c) = 1;
		S(int, 0x23432cb) = 1;
	}
	for (int k = 0; k < 10; k++)
		if (input_justPressed(GAME_VAR(int, k_presetKeys[k]))) {
			S(int, 0x233cc10) = (k + 1) % 10;
			S(int, 0x2340c6c) = 1;
			S(int, 0x23432cb) = 1;
		}
	/* the follow keys (all ten read the same key; with 0x67ef24 the players 11 .. 16) */
	int follow = 0;
	for (int k = 1; k <= 10; k++)
		if (input_justPressed(g_dik1))
			follow = k <= 6 && input_justPressed(g_dikLShift) ? k + 10 : k;
	follow--;
	S(int, 0x2340d21) = input_isDown(g_dikSpace) ? 1 : 0;
	S(int, 0x2340d25) = input_isDown(g_dikEnter) ? 1 : 0;
	if (held2(IMG(0x4defe0), IMG(0x4defe4)))
		S(int, 0x234328f) = 1;
	if (input_justPressed(g_dikF11)) {
		const char *mode;
		if (S(int, 0x2340ce8) == 0) {
			S(int, 0x2340ce8) = 1;
			mode = (const char *)IMG(0x4c7d00);   /* "HIDDEN MESSAGE BOX MODE" */
		} else if (S(int, 0x2340ce4) == 0) {
			S(int, 0x2340ce4) = 1;
			mode = (const char *)IMG(0x4c7cf0);   /* "SCREENSHOT MODE" */
		} else {
			S(int, 0x2340ce8) = S(int, 0x2340ce4) = 0;
			mode = (const char *)IMG(0x4c7ce4);   /* "NORMAL MODE" */
		}
		notice_printCentre((Scene *)s, mode);
	}
	/* the mouse: its offset from the centre (y inverted with 0x4df000), scaled by the sensitivity, unless slow */
	S(int, 0x2343257) = g_mouseX;
	S(int, 0x234325b) = g_mouseY;
	if (!(S(float, 0x44) >= 0.2f)) {
		if (g_mouseInvert == 0)
			S(float, 0x2343293) = f32((long double)(S(int, 0x234325b) - gfx_getHeight() / 2));
		else
			S(float, 0x2343293) = f32(-(long double)(S(int, 0x234325b) - gfx_getHeight() / 2));
		S(float, 0x2343297) = f32(-(long double)(S(int, 0x2343257) - gfx_getWidth() / 2));
	} else
		S(int, 0x2343293) = S(int, 0x2343297) = 0;
	long double sens = fmul_m((long double)g_mouseSensitivity, K(0x4aa480));
	sens = fmul_m(fadd_m(sens * sens, K(0x4a9424)), K(0x4a942c));
	S(float, 0x2343293) = f32(fmul_m(sens, (const float *)(s + 0x2343293)));
	S(float, 0x2343297) = f32(fmul_m(sens, (const float *)(s + 0x2343297)));
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
	if (pressed2(ADDR(g_keyLoadingSkip), ADDR(g_keyLoadingSkip2)) && !(S(float, 0x2340d39) > 0)) {
		g_mainMenuFadingIn = 0;
		S(int, 0x23432cf) = 1;
	}
	if (run_down(s, 0x233cc40))
		S(int, 0x233cc40) = 0;
	if (run_down(s, 0x2342f02))
		S(int, 0x2342f02) = 0;
	if (run_down(s, 0x2342425)) {
		tex_upload2(stage);
		S(int, 0x2342425) = 0;
	}
	long double sp = fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a9554));   /* 2000 a second, at most +0x1f4164 */
	float speed = (float)sp;
	if (sp > S(float, 0x1f4164))
		BITS(speed) = S(u32, 0x1f4164);
	float turn = f32(fmul_m(fmul_m(fmul_m((long double)game_clock(), K(0x4aa2a8)), (const float *)(s + 0x44)), K(0x4a9560)));
	float step = f32(fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a945c)));
	/* the zoom keys: the preset's distance by (1 - 0.9 dt) */
	if (S(int, 0x23432ab) == 1) {
		long double m = !(S(float, 0x44) >= 1.0f) ? fld_m((const float *)(s + 0x44)) : fld_m(K(0x4a9424));
		float *z = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
		*z = f32(fmul_m(fsubr_m(fmul_m(m, K(0x4a9508)), K(0x4a9424)), z));
	}
	if (S(int, 0x23432af) == 1) {
		long double m = !(S(float, 0x44) >= 1.0f) ? fld_m((const float *)(s + 0x44)) : fld_m(K(0x4a9424));
		float *z = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
		*z = f32(fdivr_m(fsubr_m(fmul_m(m, K(0x4a9508)), K(0x4a9424)), z));
	}
	if (S(int, 0x23432cb) == 1)
		preset_reset(s);
	if (S(int, 0x233c9fc) == 0)
		free_keys(s, mv, &speed, &turn);
	else if (S(int, 0x233c9fc) == 1 && S(int, 0x233cc10) != 2) {
		int i = S(int, 0x233cc10);
		S(float, 0x233cb48 + i * 4) = f32(fadd_m(fld_m((const float *)(s + 0x2343297)), (const float *)(s + 0x233cb48) + i));
		i = S(int, 0x233cc10);
		S(float, 0x233cb20 + i * 4) = f32(fadd_m(fld_m((const float *)(s + 0x2343293)), (const float *)(s + 0x233cb20) + i));
	}
	zoom_view(s, &step);
	float dt;   /* slow motion: a twentieth */
	if (S(int, 0x2340d21) == 1)
		dt = f32(fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a9468)));
	else
		BITS(dt) = S(u32, 0x44);

	if (S(int, 0x2340ce0) == 0) {
		if (!(S(float, 0x2340d29) > S(float, 0x2340d2d)))
			do {
				int from, len;
				u8 packet[0x130];
				if (fread_scrambled(s + 0x2340d29, 4, 1, S(void *, 0x2340d08)) == 0 || S(int, 0x2340d25) == 1) {
					if (replay_next(s))
						return 1;
					break;
				}
				fread_scrambled(&from, 4, 1, S(void *, 0x2340d08));
				fread_scrambled(&len, 4, 1, S(void *, 0x2340d08));
				fread_scrambled(packet, 1, len, S(void *, 0x2340d08));
				net_processGamePacket(s, from, len, packet);
			} while (!(S(float, 0x2340d29) > S(float, 0x2340d2d)));
		stage_advanceClocks(stage, BITS(dt));
		stage_updateObjects(stage, BITS(dt));
		actor_updateAll(stage, BITS(dt));
		bullet_updateAll(stage, BITS(dt));
		stage_updateEffects(stage, BITS(dt));
		item_update(stage, BITS(dt));
		choose_followed(s, follow);
		if (S(int, 0x2340c68) == 0)
			S(float, 0x233cc38) = f32(fadd_m(fld_m(&dt), (const float *)(s + 0x233cc38)));
		if (S(int, 0x2340c6c) == 0)
			S(float, 0x233cc3c) = f32(fadd_m(fld_m(&dt), (const float *)(s + 0x233cc3c)));
		S(float, 0x2340d2d) = f32(fadd_m(fld_m(&dt), (const float *)(s + 0x2340d2d)));
	}
	for (int i = 0; i < S(int, 0x2221f90); i++)
		if (ACTOR_INT(i, 0x1ed52d8) == 1) {
			msg_kill(s, i, ACTOR_INT(i, 0x1ed52d8 - 0x83a8));
			ACTOR_INT(i, 0x1ed52d8) = 0;
		}
	events_age(s, S(u32, 0x44));
	if (S(int, 0x234328f) == 1)
		S(u32, 0x233cc40) = 0x40a00000;   /* the ranking shown 5 s */

	/* the camera */
	S(int, 0x233c9fc) = S(int, 0x2340c64) >= 0;
	if (S(int, 0x233c9fc) == 0) {
		free_camera(s, mv, S(int, 0x234325f) ? IMG(0xa0e7d8) : 0, &move);
		turn_view(s);
	} else {
		int i = S(int, 0x233cc10);
		if (S(int, 0x233cb98 + i * 4) == 0 && i != 1) {
			orbit_camera(s, i);
			turn_view(s);
		} else {
			if (i == 1)
				pair_camera(s);
			else
				watch_camera(s);
			float *dir = (float *)(s + 0x233ca10), *up = (float *)(s + 0x233ca1c);
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fsub_m(fld_m((const float *)(s + 0x233cc14) + k), (const float *)(s + 0x233ca04) + k));
			Vec3_normalize(dir);
			BITS(up[1]) = 0x3f800000;
			up[0] = up[2] = 0;
		}
	}
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = game_clock();
	GAME_THISFN(camera_setupView, 0x4729b0, void, void *, float *, float *, float *, u32, int, int, u32, u32, u32)(stage, (float *)(s + 0x233ca04), (float *)(s + 0x233ca10),
	              (float *)(s + 0x233ca1c), BITS(fov), w, h, BITS(near), BITS(far), S(u32, 0x44));   /* camera_setupView */
	S(int, 0x233cc28)++;

	/* the scene */
	tex_clearSetCounters(g_textures);
	if (S(int, 0xbe16f8) == 1) {
		glClearColor_stored((const u32 *)(s + 0xbe16fc));
		glClearDepth(1.0);
		glClear(0x4100);
	} else {
		glClearDepth(1.0);
		glClear(0x100);
	}
	gfx_setProjectionHud(1, 1.0f);
	u8 *view = s + 0x74;
	ViewVolume_captureMatrices(view, 0, s + 0x22e7068);
	ViewVolume_reset(view);
	if (S(int, 0x233c9fc) == 1 && S(int, 0x233cc10) == 2 && S(int, 0x2340c64) >= 0)
		ACTOR_INT(S(int, 0x2340c64), 0x1eccfc0) = 1;   /* (the followed player seen from inside) */
	sky_draw((Stage *)stage, view_farPlane());
	render_processRenderingBy(stage, view, view_farPlane());
	stage_drawObjects((Stage *)stage, view);
	stage_drawActors((Stage *)stage, view, -1);
	stage_drawBullets(stage, view);
	stage_drawProjectiles((Stage *)stage, view);
	stage_drawItems(stage, view);
	if (S(int, 0x2340cd4) == 1)
		for (int i = 0; i < S(int, 0xbcb6c8); i++) {
			const u8 *r = s + 0xbc06cc + i * 0x2c;
			if (GAME_VAR(int, r) != 1)
				continue;
			float p[3], q[3];
			memcpy(p, r + 0xc, 12);
			for (int l = 0; l < 8; l++) {
				for (int k = 0; k < 3; k++)
					q[k] = f32(k_star[l][k] > 0 ? fadd_m(fld_m(&p[k]), K(0x4a93f4)) : fsub_m(fld_m(&p[k]), K(0x4a93f4)));
				ViewVolume_addSegment(view, (const void *)IMG(0xa1f208), p, q, 1);
			}
		}
	if (S(int, 0xbe170c) == 1) {
		stage_setFog((Stage *)stage, stage + 0x9ee048, GAME_VAR(u32, stage + 0x9ee058), GAME_VAR(u32, stage + 0x9ee05c), GAME_VAR(u32, stage + 0x9ee060));
		glEnable(GL_FOG);
	}
	render_drawObjects(view, S(int, 0x1f1664), S(float, 0x22f040c));
	glDisable(GL_FOG);
	gfx_setProjectionHud(0, 1.0f);

	/* the overlay */
	if (S(int, 0x2340ce4) == 0) {
		char text[0xf0];
		/* (the patch DLL retargets these calls for wide screens) */
		PATCHED_THISCALL(0x48a19c, void, void *)(s);                                 /* hud_drawPlayerMarkers */
		if (S(int, 0x2340ce8) == 0 && S(float, 0x233cc40) > 0)
			PATCHED_THISCALL(0x48a1c0, void, void *)(s);                             /* replay_drawMessage */
		if (S(int, 0x2340c64) >= 0) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			PATCHED_THISCALL(0x48a1f7, void, void *, int, int, int)(s, 0x10, 0x10, 6);   /* replay_drawIcon */
			text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
			int n = S(int, 0x233cc10);
			sprintf(text, (const char *)IMG(0x4b0320), n > 0 ? n : n + 10);   /* "%d" */
			PATCHED_CALL(0x48a259, void, int, int, const char *, int)(0x28, 0x10, text, 0x10);   /* text_drawSized */
		}
		if (!(S(float, 0x233cc34) >= 0.5f)) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			PATCHED_THISCALL(0x48a299, void, void *, int, int, int)(s, 0x20e, 0x10, 5);   /* replay_drawIcon */
			text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
			sprintf(text, (const char *)IMG(0x4c7cd8), S(int, 0x233cc30) / 60, S(int, 0x233cc30) % 60);   /* "%02d:%02d" */
			PATCHED_CALL(0x48a2ff, void, int, int, const char *, int)(0x226, 0x10, text, 0x10);   /* text_drawSized */
		}
		PATCHED_THISCALL(0x48a309, void, void *)(s);                                 /* replay_drawFollowedName */
		if (S(int, 0x234328f) == 1)
			PATCHED_THISCALL(0x48a318, void, void *)(s);                             /* hud_drawRanking */
	}
	if (S(float, 0x2342f02) > 0)
		hud_drawReadyStart((Scene *)s);
	if (S(int, 0x23432cf) != 1)
		return 4;
	fclose(S(void *, 0x2340d08));
	music_shutdown();
	return 0;
}

/* ---- 0x4988e0: the match's frame ---- */

#define A_INT(i, offset) GAME_VAR(int, s + (offset) + (i) * 0x8888)    /* an actor's field */
#define P_INT(i, offset) GAME_VAR(int, s + (offset) + (i) * 0x47fd2)   /* a player's */

/* the team games (odd modes up to 11) */
static int team_game(void)
{
	int m = g_chosenGameMode;
	return m == 1 || m == 3 || m == 5 || m == 7 || m == 9 || m == 11;
}

/* axiswl.log: the game title, map, limits and date, then the ranking (+0x23428f6, +0x2342976 of them): name, team
   (none outside team games), play time, kills and deaths. The opening log passes its own stack word as the play
   time (the original's: the same slot the network packets are read into later) */
static void write_log(u8 *s, const char *format, int own_time, int stack_time)
{
	static const char *const k_teams[3] = { (const char *)IMG(0x4b21b8), (const char *)IMG(0x4b21b0), (const char *)IMG(0x4d06ec) };   /* NOTEAM */
	void *f = crt_fopen((const char *)IMG(0x4d06e0), (const char *)IMG(0x4b21a4));   /* "axiswl.log" */
	crt_fprintf(f, format, (const char *)IMG(0x67fb44), g_missionStage, g_fragLimit, g_timeLimit, (const char *)IMG(0x4dedd8));
	for (int k = 0; k < S(int, 0x2342976); k++) {
		int e = S(int, 0x23428f6 + k * 4);
		int team = team_game() ? A_INT(e, 0x1eccb88) : 2;
		char name[64];
		memset(name, 0, sizeof name);
		strcpy(name, (const char *)ACTOR_AT(e) + 0x98);
		crt_fprintf(f, (const char *)IMG(0x4d062c), name, k_teams[team], own_time ? A_INT(e, 0x1eccb6c) : stack_time,
		            A_INT(e, 0x1eccb54), A_INT(e, 0x1eccb58));
	}
	fclose(f);
}

/* a free spawn point (+0x22ee23c, 0x14 bytes each, +0x22ee4bc of them) from a random one on: the first no live
   actor stands within reach of (the reach: its height times 5, or twice it); NULL when there are none */
static const u8 *spawn_point(u8 *s, int doubled)
{
	int n = S(int, 0x22ee4bc);
	if (n <= 0)
		return NULL;
	u32 r = rand_below(n);
	int left = S(int, 0x22ee4bc) - 1;
	for (;;) {
		int taken = 0;
		for (int j = 0; j < S(int, 0x2221f90); j++) {
			if (A_INT(j, 0x1eccbbc) != 1)
				continue;
			const float *pos = (const float *)(ACTOR_AT(j) + 0x154), *at = (const float *)(s + 0x22ee23c + r * 0x14);
			float d[3];
			for (int k = 0; k < 3; k++)
				d[k] = f32(fsub_m(fld_m(&pos[k]), &at[k]));
			long double reach = doubled ? fld_m((const float *)(ACTOR_AT(j) + 0x3e8)) * 2 : fmul_m(fld_m((const float *)(ACTOR_AT(j) + 0x3e8)), K(0x4a93d0));
			long double dist = fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1]);
			dist = dist + fmul_m(fld_m(&d[0]), &d[0]);
			if (reach * reach > dist) {
				taken = 1;
				break;
			}
		}
		if (!taken)
			break;
		r = (int)(r + 1) % S(int, 0x22ee4bc);
		if (left-- < 0)
			break;
	}
	return s + 0x22ee23c + r * 0x14;
}

/* the five parts of actor p in team colours (by its team's side) */
static void team_colours(u8 *s, int p, int team)
{
	int side = scene_teamSide((Scene *)s, team);
	for (int part = 0; part < 5; part++)
		actor_setPartColor_bits(s + 0x1f36c8, p, part, GAME_VAR(u32, 0x4a97fc + side * 4), GAME_VAR(u32, 0x4a9810 + side * 4),
		                        GAME_VAR(u32, 0x4a9824 + side * 4), 0, 0xbf800000, 0x3f7fbe77);
}

/* the local player (+0x234240d) into the match: its record (+0x2342429 ..), colours, a spawn point, the notice */
static void local_spawn(u8 *s)
{
	if (S(int, 0x2342411) == 0) {
		playerRecord_set(s + 0x1f36c8, S(int, 0x234240d), (const char *)(s + 0x2342429), S(u32, 0x234243a), S(u32, 0x234243e), S(u32, 0x234244a),
		             S(u32, 0x234244e), S(u32, 0x2342452), S(u32, 0x2342456), S(u32, 0x234245a), S(u32, 0x234245e), S(u32, 0x2342462),
		             S(u32, 0x2342466), S(u32, 0x234246a), S(u32, 0x234246e), S(u32, 0x2342472));
		S(int, 0x2342411) = 1;
	}
	if (S(int, 0x22e7184) == 1)
		team_colours(s, S(int, 0x234240d), S(int, 0x234243e));
	else if (A_INT(S(int, 0x234240d), 0x1eccb48) == 0)
		for (int part = 0; part < 5; part++) {
			const u32 *c = (const u32 *)(s + 0x23424a2) + part * 2;
			actor_setPartColor_bits(s + 0x1f36c8, S(int, 0x234240d), part, c[-11], c[-1], c[9], c[-10], c[0], c[10]);
		}
	u32 rec[7];   /* the actor, 0, the position, the pitch and heading */
	const u8 *at = spawn_point(s, 0);
	rec[0] = S(u32, 0x234240d);
	rec[1] = 0;
	if (at) {
		memcpy(rec + 2, at, 12);
		float pitch = (float)fld_m((const float *)(at + 0xc)), heading = (float)fld_m((const float *)(at + 0x10));
		rec[5] = BITS(pitch);
		rec[6] = BITS(heading);
	} else {
		memcpy(rec + 2, s + 0x22ee228, 12);
		float pitch = (float)fld_m((const float *)(s + 0x22ee234)), heading = (float)fld_m((const float *)(s + 0x22ee238));
		rec[5] = BITS(pitch);
		rec[6] = BITS(heading);
	}
	stage_claimPlayerActor((Stage *)(s + 0x1f36c8), rec[0], -1, rec[0], rec);
	if (S(int, 0x2340d1d) == 1)
		S(int, 0x234300a + S(int, 0x234240d) * 16) = 1;
	S(int, 0x233c9fc) = 1;
	notice_printCentre((Scene *)s, (const char *)IMG(0x4d0618));
	S(u32, 0x23423c1) = 0x40400000;   /* 3 */
	S(int, 0x23423c5) = -1;
	msg_newKing((Scene *)s);
	S(int, 0x23432cb) = 1;
	S(int, 0x2340d00) = 0;
}

/* the bots (+0x1eca67c, 0x5c-byte records, +0x1ecca6c of them) waiting to spawn: placed on a free point */
static void bot_spawns(u8 *s)
{
	for (int j = 0; j < S(int, 0x1ecca6c); j++) {
		u8 *rec = s + 0x1eca67c + j * 0x5c;
		int state = A_INT(j, 0x1eccb78);
		if (GAME_VAR(int, rec + 0x18) != 1 || !(state == 0 || (state == 1 && A_INT(j, 0x1eccbbc) == 3)))
			continue;
		u8 *player = s + 0x1755230 + GAME_VAR(int, rec) * 0x47fd2;
		if (S(int, 0x22e7184) == 1)
			team_colours(s, GAME_VAR(int, rec), GAME_VAR(int, player + 0x48));
		u32 copy[0x17];
		memcpy(copy, rec, 0x5c);
		const u8 *at = spawn_point(s, 1);
		memcpy(copy + 1, at ? at : s + 0x22ee228, 12);
		actor_applySpawnRecord(s + 0x1f36c8, j, copy);
		if (A_INT(j, 0x1eccb48) == 0)
			msg_playerJoinedTeam((Scene *)s, GAME_VAR(int, rec), GAME_VAR(int, player + 0x48));
	}
}

/* the camera looking back at the actor t's killer (+0x4c0) from 2 heights behind its head (+0x4e0) */
static void killer_view(u8 *s, const u8 *t)
{
	float *cam = (float *)(s + 0x233ca04), *head = (float *)(RELOC(t) + 0x4e0), d[3], p[3];
	int k = GAME_VAR(int, t + 0x4c0);
	for (int j = 0; j < 3; j++)
		d[j] = f32(fsub_m(fld_m((const float *)(ACTOR_AT(k) + 0x154) + j), &head[j]));
	Vec3_normalize(d);
	long double r = fmul_m(fld_m((const float *)(RELOC(t) + 0x3e8)), K(0x4a94a8));   /* -2 heights */
	for (int j = 0; j < 3; j++)
		p[j] = f32(fmul_m(r, &d[j]));
	for (int j = 0; j < 3; j++)
		p[j] = f32(fadd_m(fld_m(&p[j]), &head[j]));
	if (collision_rayTrace(s + 0x1f36c8, head, p, cam) == 0)
		memcpy(cam, p, 12);
	for (int j = 0; j < 3; j++)
		d[j] = f32(fsub_m(fld_m(&cam[j]), &head[j]));
	if (Vec3_normalize(d) > 300.0f) {
		long double dx = fmul_m(fld_m(&d[0]), K(0x4aa440));
		float dy = f32(fmul_m(fld_m(&d[1]), K(0x4aa440))), dz = f32(fmul_m(fld_m(&d[2]), K(0x4aa440)));
		cam[0] = f32(fld_m(&cam[0]) - dx);
		cam[1] = f32(fsub_m(fld_m(&cam[1]), &dy));
		cam[2] = f32(fsub_m(fld_m(&cam[2]), &dz));
	}
	look_toward(s, (const float *)(ACTOR_AT(GAME_VAR(int, t + 0x4c0)) + 0x154));
	for (int j = 0; j < 3; j++)
		((float *)(s + 0x233ca10))[j] = f32(fsub_m(fld_m((const float *)(s + 0x233cc14) + j), &cam[j]));
}

/* the camera looking at the look point, which moves half way to p */
static void look_at(u8 *s, const float *p)
{
	float *dir = (float *)(s + 0x233ca10), *up = (float *)(s + 0x233ca1c);
	look_toward(s, p);
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m((const float *)(s + 0x233cc14) + k), (const float *)(s + 0x233ca04) + k));
	Vec3_normalize(dir);
	up[0] = 0;
	BITS(up[1]) = 0x3f800000;
	up[2] = 0;
}

/* ((m[a] * v[ia] + m[b] * v[ib]) + m[c] * v[ic]) + m[t], rounded */
static float mrow(const float *m, const float *v, int a, int ia, int b, int ib, int c, int ic, int t)
{
	long double x = fmul_m(fld_m(&m[a]), &v[ia]) + fmul_m(fld_m(&m[b]), &v[ib]);
	return f32(fadd_m(x + fmul_m(fld_m(&m[c]), &v[ic]), &m[t]));
}

/* preset 1 of the local player's camera: at the selected weapon's muzzle (its part's bone matrix, +0x1568), a
   fraction (+0x490) of the way from the eye (0.3 heights up, turned with the view) */
static void muzzle_camera(u8 *s, const u8 *t)
{
	u8 *player = s + GAME_VAR(int, t + 0x10c) * 0x47fd2;
	int slot = GAME_VAR(int, t + 0x140);
	u8 *parts = s + 0x15fff88 + GAME_VAR(int, player + 0x1755544) * 0x1300;
	u8 *item = s + 0x16c517c + GAME_VAR(int, player + 0x1755550 + slot * 4) * 0x2e18;
	float P[3], E[3] = { 0, 0, 0 };
	const float *v, *m;
	int bone;
	if (slot == 4) {
		v = (const float *)(RELOC(item) + 0x16b4 + GAME_VAR(int, t + 0x49c) * 0xc);
		bone = GAME_VAR(int, parts + GAME_VAR(int, t + 0x484) * 4 + 0x12d8);
	} else if (slot == 5) {
		v = (const float *)(RELOC(item) + 0x2d70 + GAME_VAR(int, t + 0x49c) * 0xc);
		bone = GAME_VAR(int, parts + GAME_VAR(int, t + 0x484) * 4 + 0x12e0);
	} else {
		v = (const float *)(RELOC(item) + 0x16b4 + GAME_VAR(int, t + 0x49c) * 0xc);
		bone = GAME_VAR(int, parts + GAME_VAR(int, t + 0x484) * 4 + 0x12d0);
	}
	m = (const float *)(GAME_VAR(u8 *, t + 0x1568) + bone * 100 + 0xc);
	if (slot == 4) {
		P[0] = mrow(m, v, 4, 1, 8, 2, 0, 0, 12);
		P[1] = mrow(m, v, 5, 1, 1, 0, 9, 2, 13);
		P[2] = mrow(m, v, 6, 1, 2, 0, 10, 2, 14);
	} else if (slot == 5) {
		P[0] = mrow(m, v, 8, 2, 4, 1, 0, 0, 12);
		P[1] = mrow(m, v, 9, 2, 1, 0, 5, 1, 13);
		P[2] = mrow(m, v, 10, 2, 2, 0, 6, 1, 14);
	} else {
		P[0] = mrow(m, v, 4, 1, 8, 2, 0, 0, 12);
		P[1] = mrow(m, v, 1, 0, 5, 1, 9, 2, 13);
		P[2] = mrow(m, v, 2, 0, 6, 1, 10, 2, 14);
	}
	E[1] = f32(fmul_m(fld_m((const float *)(RELOC(t) + 0x3e8)), K(0x4a94fc)));   /* 0.3 */
	Vec3_rotateAxis(E, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(E, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	for (int k = 0; k < 3; k++)
		E[k] = f32(fadd_m(fld_m(&E[k]), (const float *)(RELOC(t) + 0x154) + k));
	float f;
	BITS(f) = GAME_VAR(u32, t + 0x490);
	long double dx = fsub_m(fld_m(&P[0]), &E[0]);
	float dy = f32(fsub_m(fld_m(&P[1]), &E[1])), dz = f32(fsub_m(fld_m(&P[2]), &E[2]));
	long double hx = fmul_m(dx, &f);
	float hy = f32(fmul_m(fld_m(&dy), &f)), hz = f32(fmul_m(fld_m(&dz), &f));
	float *cam = (float *)(s + 0x233ca04), *dir = (float *)(s + 0x233ca10);
	cam[0] = f32(fadd_m(hx, &E[0]));
	cam[1] = f32(fadd_m(fld_m(&hy), &E[1]));
	cam[2] = f32(fadd_m(fld_m(&hz), &E[2]));
	dir[0] = dir[1] = 0;
	BITS(dir[2]) = 0x3f800000;
}

/* the round's slow motion: the last two seconds of a won round's end (+0x2342399) when the winner (+0x2221fb0) is
   down (state 2), unless the time ran out */
static int slow_end(u8 *s)
{
	if (S(int, 0x2342399) != 1)
		return 0;
	if (S(int, 0x23423b1) > 0 && S(int, 0x22f0408) >= S(int, 0x23423b1) * 60)
		return 0;
	if (!(fsub_m(fld_m(K(0x4a9418)), (const float *)(s + 0x234239d)) < 2.0f))
		return 0;
	return S(int, 0x2221fb0) >= 0 && A_INT(S(int, 0x2221fb0), 0x1eccbbc) == 2;
}

/* the winning team (+0x23423bd): the side whose team slot has more (team scores +0x2221fb8), -1 for a draw */
static void winning_team(u8 *s)
{
	int a = scene_teamSlot((Scene *)s, 1), b = scene_teamSlot((Scene *)s, 0);
	if (S(int, 0x2221fb8 + b * 4) > S(int, 0x2221fb8 + a * 4)) {
		S(int, 0x23423bd) = scene_teamSlot((Scene *)s, 0);
		return;
	}
	a = scene_teamSlot((Scene *)s, 1);
	b = scene_teamSlot((Scene *)s, 0);
	if (S(int, 0x2221fb8 + b * 4) < S(int, 0x2221fb8 + a * 4))
		S(int, 0x23423bd) = scene_teamSlot((Scene *)s, 1);
	else
		S(int, 0x23423bd) = -1;
}

/* the round over (10 s of end, +0x234239d): the notice (frag or time limit), the log written later */
static void round_over(u8 *s, int time_limit)
{
	S(int, 0x22f0410) = 1;
	S(int, 0x2342399) = 1;
	S(u32, 0x234239d) = 0x41200000;   /* 10 */
	S(int, 0x233c9fc) = 1;
	music_shutdown();
	if (time_limit)
		msg_timeLimitReached(s);
	else
		msg_fragLimitReached(s);
	S(int, 0x23423b5) = time_limit;
	S(int, 0x23423b9) = 0;
	g_writeMatchLog = 1;
}

/* the local player's camera chat keys: T (all, +0x23432fb) / Y (team, +0x23432ff) open the line, its end sends it
   (a cheat code, a macro or the text) */
static void chat_keys(u8 *s)
{
	char line[0x100];
	int me = S(int, 0x234240d), mode = S(int, 0x2340d35);
	if (mode == 0) {
		if (S(int, 0x23432fb) == 1) {
			S(int, 0x2340d35) = 1;
			chat_textField(0, 0, 0x38);
			A_INT(S(int, 0x234240d), 0x1ecce5c) = 1;
		} else if (S(int, 0x23432ff) == 1) {
			S(int, 0x2340d35) = 2;
			chat_textField(0, 0, 0x38);
			A_INT(S(int, 0x234240d), 0x1ecce5c) = 2;
		}
		return;
	}
	if ((mode != 1 && mode != 2) || g_paused != 0)
		return;
	S(int, 0x2340d35) = 0;
	chat_keepLastLine();
	const char *typed = (const char *)ADDR(g_keptChatLine);
	(void)me;
	if (strlen(typed) != 0) {
		int code = mode == 1 ? chat_matchCheatCode(s, S(int, 0x234240d), typed) : -1;
		if (code >= 0) {
			msg_cheatUsed(s, S(int, 0x234240d), code);
			recorder_openStub(s, (void *)S(int, 0x234240d), (const void *)RELOC(code));
		} else {
			int r = chat_macro(s, typed, line);
			if (r == 0)
				strcpy(line, typed);
			if (r == 0 || r == 1) {
				int team = mode == 1 ? -1 : S(int, 0x234243e);
				msg_chatLine(s, S(int, 0x234240d), line, team);
				team = mode == 1 ? -1 : S(int, 0x234243e);
				notice_raise3(s, S(int, 0x234240d), line, team);
			}
		}
	}
	A_INT(S(int, 0x234240d), 0x1ecce5c) = 0;
}

/* 0x4988e0 (thiscall on the game object): the match's frame. The log of the last match written when asked
   (0x9f67ec); nothing more until the match runs (+0x233c9e8). Then: the Esc menu and quitting, the local player
   joining (the network's slot, its name and record), its team or spawn, the bots' spawns, the free camera's keys
   or the player's own (actor_setInput), the view angle, the network's packets, the scene's frame (slowed at a round's
   end), the followed player when spectating, kill messages, the notices and countdowns, the network's per-player
   updates, the round's end (frag or time limit) and the next round or map, the camera (spectating: free, one of
   the presets about the followed player or its killer; playing: the presets, the muzzle or the killer), the chat
   keys, the connection checks and the match's end (the log, back to the menu) */
void THISCALL (game_processGameMode)(u8 *s)
{
	u8 *stage = s + 0x1f36c8;
	float mv[3];        /* the free camera's move (its keys may not have run: the original's stack then) */
	Move move;          /* (the stubbed move may leave these as the stack had them) */
	int from, size;     /* the network packet's sender and size, as the reader leaves them; the opening log's play
	                       time reads the sender's slot before it is ever written, as the original does */
	u8 packet[0x130];
	if (g_writeMatchLog != 0 && g_startedFromLobby != 0) {
		write_log(s, (const char *)(S(int, 0x2342976) > 1 ? IMG(0x4d0658) : IMG(0x4d069c)), 0, *(volatile int *)&from);
		g_writeMatchLog = 0;
		g_matchLogWritten = 1;
	}
	if (S(int, 0x233c9e8) == 0) {
		S(int, 0x233cc20) = 1;
		S(int, 0x233cc28) = 0;
		return;
	}
	if (S(int, 0x2343303) == 1)
		S(int, 0x2340cec) ^= 1;
	if (S(int, 0x23432cf) == 1) {
		if (S(int, 0x2340cec) == 1)
			S(int, 0x2340cec) = S(int, 0x23432cf) = 0;
	} else if (S(int, 0x2340cec) == 1 && S(int, 0x234327f) == 1)
		S(int, 0x2340cec) = 0;
	/* the Esc menu, quitting */
	int quit_check = 1;
	if (S(int, 0x2340cf4) == 1)
		match_escMenu(s);
	else if (S(int, 0x23432cf) == 1) {
		if (S(int, 0x23423a1) == 0) {
			sound_playVolume(9, 100);
			if (S(int, 0x2340cf0) == 0 || (S(int, 8) == 0 && S(int, 0x2342415) == 1 && A_INT(S(int, 0x234240d), 0x1eccb48) == 0)) {
				S(int, 0x2340d04) = 0;
				S(int, 0x2340cf0) = 1;
			}
			escMenu_open((Scene *)s, 0, A_INT(S(int, 0x234240d), 0x1eccb48) == 0 ? 0 : 4);
			S(int, 0x23432cf) = 0;
		}
	} else
		quit_check = 0;
	if (quit_check && S(int, 0x23432cf) == 1) {
		if (S(int, 4) == 0) {
			if (S(int, 0x23423a1) == 0) {
				S(int, 0x23423a1) = 1;
				S(u32, 0x23423a5) = 0x40400000;
				music_shutdown();
				if (S(int, 8) == 0) {
					msg_userEndsGame(s);
					g_matchEndedByUser = 1;
				} else {
					msg_serverEndsGame(s);
					event_raise3(s);
					S(int, 0x23423b5) = 2;
					S(int, 0x23423b9) = 0;
					g_matchEndedByUser = 1;
				}
			}
		} else {
			S(int, 0x23423a1) = 1;
			S(int, 0x23423a5) = 0;
			music_shutdown();
			if (S(int, 0x234240d) >= 0)
				notice_raise2(s, S(int, 0x234240d));
			g_matchEndedByUser = 0;
		}
		S(int, 0x23432cf) = 0;
	}
	/* the local player's starting kills and deaths, its screenshot */
	if (S(int, 0x234240d) >= 0 && S(int, 0x2342419) == 0) {
		A_INT(S(int, 0x234240d), 0x1eccb4c) = S(int, 0x2342442);
		A_INT(S(int, 0x234240d), 0x1eccb50) = S(int, 0x2342442);
		A_INT(S(int, 0x234240d), 0x1eccb5c) = S(int, 0x2342446);
		A_INT(S(int, 0x234240d), 0x1eccb68) = S(int, 0x2342446);
		S(int, 0x2342419) = 1;
	}
	if (S(int, 0x2342421) == 0 && S(int, 0x234240d) >= 0 && S(int, 8) == 1) {
		int shot = gfx_saveScreenshot(stage, S(int, 0x234240d));
		P_INT(S(int, 0x234240d), 0x179d1fa) = shot;
		P_INT(S(int, 0x234240d), 0x179d1fe) = 0;
		S(u32, 0x2342425) = 0x40a00000;   /* 5 */
		S(int, 0x2342421) = 1;
	} else if (run_down(s, 0x2342425)) {
		tex_upload2(stage);
		S(int, 0x2342425) = 0;
	}
	/* joining: the network's slot for the local player */
	if (S(int, 0x234240d) < 0 && net_isClient()) {
		PATCHED_THISCALL(0x498dd8, u32, void *, const char *)(stage, g_catalogueFile);   /* catalogue_loadComponents */
		S(int, 0x234240d) = net_localSlot();
		actor_resetSlot((Stage *)stage, S(int, 0x234240d));
		player_setName((Stage *)stage, S(int, 0x234240d), (const char *)(s + 0x2342429));
		strcpy((char *)ACTOR_AT(S(int, 0x234240d)) + 0x98, (const char *)(s + 0x2342429));
		A_INT(S(int, 0x234240d), 0x1eccb7c) = S(int, 0x234240d);
		msg_playerConnected(s, S(int, 0x234240d));
		notice_raise1(s, S(int, 0x234240d), s + 0x1755234 + S(int, 0x234240d) * 0x47fd2);
		net_sendMatchEvent(s);
	}
	/* a team chosen (or a menu for it), then the spawn */
	int me = S(int, 0x234240d);
	if (me >= 0 && A_INT(me, 0x1eccb78) == 0 && S(int, 0x2342399) == 0 && P_INT(me, 0x179d1fe) == 0x180
	    && (S(int, 0x234327f) == 1 || S(int, 0x2342415) == 1)) {
		if (S(int, 0x22e7184) == 1 && (S(int, 0x234243e) < 0 || scene_findTeam((Scene *)s, S(int, 0x234243e)) < 0)) {
			if (S(int, 0x234241d) >= 0 && S(int, 8) != 0)
				escMenu_open((Scene *)s, 1, scene_teamSide((Scene *)s, S(int, 0x234241d)) == 0 ? 0 : 1);
			else
				escMenu_open((Scene *)s, 1, S(int, 0x234297e) > S(int, 0x2342982) ? 1 : 0);
		} else {
			if (S(int, 0x234243e) < 0) {
				scene_setLocalTeam((Scene *)s, S(int, 0x234240d));
				msg_playerJoinedTeam((Scene *)s, S(int, 0x234240d), S(int, 0x234243e));
				notice_raise4((Scene *)s, S(int, 0x234240d), S(int, 0x234243e), (const char *)(s + 0x2342429));
			}
			S(int, 0x2340d00) = 1;
		}
		S(int, 0x2342415) = 0;
	}
	me = S(int, 0x234240d);
	if (me >= 0 && S(int, 0x234243e) >= 0 && A_INT(me, 0x1eccb78) == 0 && S(int, 0x2340d35) == 0 && S(int, 0x2342399) == 0
	    && S(int, 0x23423a1) == 0) {
		long double v = fadd_m(fld_m((const float *)(s + 0x44)), (const float *)(s + 0x233cc48));
		S(float, 0x233cc48) = (float)v;
		if (!(v < 10.0f)) {   /* respawn after 10 s */
			S(int, 0x233cc48) = 0;
			S(int, 0x2340d00) = 1;
		}
	} else
		S(int, 0x233cc48) = 0;
	if (S(int, 0x2340d00) == 1
	    || (S(int, 0x22e71a0) == 1 && A_INT(S(int, 0x234240d), 0x1eccbbc) == 3 && A_INT(S(int, 0x234240d), 0x1eccf4c) == 1))
		local_spawn(s);
	if (S(int, 8) == 0 && S(int, 0x234240d) >= 0 && A_INT(S(int, 0x234240d), 0x1eccb48) == 1 && S(int, 0x2342399) == 0)
		bot_spawns(s);
	stage_selectActor((Stage *)stage, S(int, 0x233c9fc) == 1 && S(int, 0x233cc10) == 1 ? S(int, 0x234240d) : -1);
	/* the keys' rates */
	long double sp = fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a9554));
	float speed = (float)sp;
	if (sp > S(float, 0x1f4164))
		BITS(speed) = S(u32, 0x1f4164);
	float turn = f32(fmul_m(fmul_m(fmul_m((long double)game_clock(), K(0x4aa2a8)), (const float *)(s + 0x44)), K(0x4aa504)));
	float step = f32(fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a945c)));
	if (S(int, 0x23432cb) == 1)
		for (int k = 0; k < 10; k++)
			for (int f = 0; f < 6; f++)
				S(u32, 0x233cb20 + f * 0x28 + k * 4) = S(u32, 0x233ca30 + f * 0x28 + k * 4);
	if (S(int, 0x233c9fc) == 0) {
		if (S(int, 0x23424f2) >= 0 && S(int, 0x2340c64) >= 0) {
			int i = S(int, 0x23424f2);
			if (i != 2) {
				S(float, 0x233cb48 + i * 4) = f32(fadd_m(fld_m((const float *)(s + 0x2343297)), (const float *)(s + 0x233cb48) + i));
				i = S(int, 0x23424f2);
				S(float, 0x233cb20 + i * 4) = f32(fadd_m(fld_m((const float *)(s + 0x2343293)), (const float *)(s + 0x233cb20) + i));
			}
		} else
			free_keys(s, mv, &speed, &turn);
	} else if (S(int, 0x233c9fc) == 1 && (S(int, 8) == 0 || net_isClient())) {
		if (S(int, 0x2342399) == 1 || S(int, 0x23423a1) == 1) {
			if (S(int, 0x2342399) == 1 && S(int, 0x23428f6) != S(int, 0x234240d)) {   /* the round's end: the camera turns */
				float *v = (float *)(s + 0x233cb20) + S(int, 0x233cc10);
				*v = f32(fsubr_m(fmul_m(fld_m(&turn), (const float *)(s + 0x2343293)), v));
				v = (float *)(s + 0x233cb48) + S(int, 0x233cc10);
				*v = f32(fsubr_m(fmul_m(fld_m(&turn), (const float *)(s + 0x2343297)), v));
			}
			S(int, 0x234327b) = 0;
			S(int, 0x2343287) = -1;
			S(int, 0x23432eb) = 0;
			S(int, 0x23432ef) = 0;
		}
		if (S(int, 0x2343273) == 1) {
			S(int, 0x234325f) = S(int, 0x2343263) = 1;
			S(int, 0x2343267) = 0;
		}
		if (S(int, 0x2343277) == 1) {
			S(int, 0x234325f) = S(int, 0x2343267) = 1;
			S(int, 0x2343263) = 0;
		}
		float pitch = f32(fmul_m(fld_m(&turn), (const float *)(s + 0x2343293))), yaw = f32(fmul_m(fld_m(&turn), (const float *)(s + 0x2343297)));
		actor_setInput(stage, S(u32, 0x234240d), S(u32, 0x2343263), S(u32, 0x2343267), S(u32, 0x234326b), S(u32, 0x234326f), BITS(pitch),
		             BITS(yaw), S(u32, 0x234327b), S(u32, 0x234325f), S(u32, 0x2343283), S(u32, 0x2343287), S(u32, 0x23432eb), S(u32, 0x23432ef));
	}
	zoom_view(s, &step);
	/* the network's packets */
	S(int, 0x2340c80) += S(int, 0x2340c78);
	S(int, 0x2340c84) += S(int, 0x2340c7c);
	S(int, 0x2340c78) = S(int, 0x2340c7c) = 0;
	if (S(int, 0x23423a1) == 0) {
		netq_poll();
		for (int r = netq_receive(&from, &size, packet); r != 0; r = netq_receive(&from, &size, packet)) {
			if (r == 1)
				net_processGamePacket(s, from, size, packet);
			S(int, 0x2340c7c)++;
			netq_poll();
		}
	}
	if (S(int, 0x233cc20) == 1)
		return;
	/* the scene's frame */
	float dt;
	if (slow_end(s))
		dt = f32(fmul_m(fld_m((const float *)(s + 0x44)), K(0x4a9468)));
	else
		BITS(dt) = S(u32, 0x44);
	if (S(int, 0x2340ce0) == 0 && !(S(int, 0x2340cf4) == 1 && S(int, 8) == 0)) {
		if (S(int, 0x233c9fc) == 0 && S(int, 0x23424f2) == 2 && S(int, 0x2340c64) >= 0)
			A_INT(S(int, 0x2340c64), 0x1eccfc0) = 1;
		else if (S(int, 0x233c9fc) == 1 && S(int, 0x233cc10) == 2 && S(int, 0x234240d) >= 0)
			A_INT(S(int, 0x234240d), 0x1eccfc0) = 1;
		stage_advanceClocks(stage, BITS(dt));
		actor_updateAll(stage, BITS(dt));
		if (S(int, 0x2342399) == 1 || S(int, 0x23423a1) == 1)
			stage_clearBullets(stage);
		bullet_updateAll(stage, BITS(dt));
		stage_updateEffects(stage, BITS(dt));
		item_update(stage, BITS(dt));
		stage_refillFactors(stage);
		stage_updateObjects(stage, BITS(dt));
		scene_loadPath(stage, BITS(dt));
		if (S(int, 8) == 1) {   /* the server checks the local player's parts every 20 s */
			long double v = fsub_m(fld_m((const float *)(s + 0x2342405)), (const float *)(s + 0x44));
			S(float, 0x2342405) = (float)v;
			if (!(v >= 0) && S(int, 0x234240d) >= 0 && A_INT(S(int, 0x234240d), 0x1eccbbc) == 1) {
				if (armc_computeTotals(stage, S(int, 0x234240d)) == 0) {
					S(int, 0x23423fd) = 1;
					S(int, 0x2342401) = 0;
				}
				S(u32, 0x2342405) = 0x41a00000;   /* 20 */
			}
			if (S(int, 0x23423fd) == 1) {
				msg_dataLoss(s);
				S(int, 0x23423a1) = 1;
				S(u32, 0x23423a5) = 0x40400000;
				music_shutdown();
				S(int, 0x23423fd) = 0;
			}
		}
		if (S(int, 0x233c9fc) == 0) {   /* spectating: the followed player */
			if (S(int, 0x2340c64) >= 0 && A_INT(S(int, 0x2340c64), 0x1eccb88) < 0)
				S(int, 0x2340c64) = -1;
			int f = S(int, 0x2343307), n = S(int, 0x2221f90);
			if (f >= 0) {
				if (A_INT(f, 0x1eccb88) >= 0) {
					if (S(int, 0x23424f2) < 0)
						S(int, 0x23424f2) = 1;
					S(int, 0x2340c64) = f;
					S(int, 0x233cc38) = 0;
					S(int, 0x2340c68) = 1;
				}
			} else if (n > 0 && (S(int, 0x234331b) == 1 || S(float, 0x233cc38) > 14.0f)) {
				int cur = S(int, 0x2340c64), next = cur + 1;
				if (next == n) {
					S(int, 0x2340c64) = -1;
					start_view(s);
				} else
					for (;;) {
						if (A_INT(next, 0x1eccb88) >= 0) {
							if (S(int, 0x23424f2) < 0)
								S(int, 0x23424f2) = 1;
							S(int, 0x2340c64) = next;
							S(int, 0x233cc38) = 0;
							break;
						}
						if (++next >= n) {
							S(int, 0x2340c64) = -1;
							start_view(s);
							break;
						}
						if (next == cur)
							break;
					}
			}
			if (S(int, 0x2340c64) >= 0) {
				if (S(int, 0x234331f) == 1)
					S(int, 0x23424f2) = (S(int, 0x23424f2) + 1) % 10;
				else if (S(float, 0x233cc3c) > 7.0f) {
					u32 r = rand_below(100);
					S(int, 0x23424f2) = r < 5 ? 0 : r < 35 ? 1 : r < 45 ? 2 : r < 50 ? 3 : r < 55 ? 4 : r < 60 ? 5 : r < 65 ? 6 : r < 70 ? 7 : 8 + (r >= 75);
					S(int, 0x233cc3c) = 0;
				}
			}
			if (S(int, 0x2340c68) == 0)
				S(float, 0x233cc38) = f32(fadd_m(fld_m((const float *)(s + 0x233cc38)), (const float *)(s + 0x44)));
			if (S(int, 0x2340c6c) == 0)
				S(float, 0x233cc3c) = f32(fadd_m(fld_m((const float *)(s + 0x44)), (const float *)(s + 0x233cc3c)));
		}
	}
	for (int i = 0; i < S(int, 0x2221f90); i++)
		if (A_INT(i, 0x1ed52d8) == 1) {
			msg_kill(s, i, A_INT(i, 0x1ed52d8 - 0x83a8));
			A_INT(i, 0x1ed52d8) = 0;
		}
	events_age(s, S(u32, 0x44));
	if (S(int, 0x234328f) == 1)
		S(u32, 0x233cc40) = 0x40a00000;
	me = S(int, 0x234240d);
	if (me >= 0 && A_INT(me, 0x1eccbbc) == 1 && !(GAME_VAR(float, ACTOR_AT(me) + 0x534) < 0) && !(GAME_VAR(float, ACTOR_AT(me) + 0x534) > 0))
		notice_printCentre((Scene *)s, (const char *)(ACTOR_AT(me) + 0x4f4));   /* (its own text as the format) */
	/* the start count (3, 2, 1, go) */
	if (S(float, 0x23423c1) > 0) {
		long double v = fsub_m(fld_m((const float *)(s + 0x23423c1)), (const float *)(s + 0x44));
		S(float, 0x23423c1) = (float)v;
		if (!(v >= 0)) {
			S(int, 0x23423c1) = 0;
			notice_printCentre((Scene *)s, (const char *)IMG(0x4d0610));
			sound_playVolume(0x17, 100);
		} else {
			int n = ftol(v);
			if (S(int, 0x23423c5) != n) {
				S(int, 0x23423c5) = n;
				if (n == 0)
					notice_printCentre((Scene *)s, (const char *)IMG(0x4d05f8));
				else if (n == 1)
					notice_printCentre((Scene *)s, (const char *)IMG(0x4d0600));
				else if (n == 2)
					notice_printCentre((Scene *)s, (const char *)IMG(0x4d0608));
				sound_playVolume(9, 100);
			}
		}
	}
	if (S(int, 0x233c9f0) == 1 && S(int, 0x234240d) >= 0) {
		me = S(int, 0x234240d);
		int a = A_INT(me, 0x1eccb4c);
		if (a != A_INT(me, 0x1eccb50)) {
			A_INT(me, 0x1eccb50) = a;
			notice_printCentre((Scene *)s, (const char *)IMG(0x4d05ec));
			sound_playVolume(0x18, 100);
		}
	}
	if (S(u8, 0x22f0414)) {
		notice_printCentre((Scene *)s, (const char *)(s + 0x22f0414));
		S(u8, 0x22f0414) = 0;
	}
	if (S(int, 0x2221fb4) == 1 || !(S(float, 0x233cc58) > 0)) {
		msg_newKing((Scene *)s);
		if (net_playerInUse(S(int, 0x234240d)) == 1 && S(int, 0x2342936 + S(int, 0x234240d) * 4) == 1
		    && (S(int, 0x234297a) > 1 || (S(int, 0x22e719c) == 1 && S(int, 0x234297a) != 1)))
			sound_playVolume(0xf, 100);
		S(int, 0x2221fb4) = 0;
		S(u32, 0x233cc58) = 0x40a00000;
	}
	if (S(int, 0x2340d1d) == 1)
		S(float, 0x2340d29) = f32(fadd_m(fld_m((const float *)(s + 0x44)), (const float *)(s + 0x2340d29)));
	/* the network's per-player updates */
	if (S(int, 0x234240d) >= 0) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233cc54)), (const float *)(s + 0x44));
		S(float, 0x233cc54) = (float)v;
		if (!(v > 0)) {
			S(int, 0x2343006 + S(int, 0x234240d) * 16) = 1;
			S(u32, 0x233cc54) = 0x40400000;
		}
		if (A_INT(S(int, 0x234240d), 0x1eccb88) >= 0) {
			v = fsub_m(fld_m((const float *)(s + 0x233cc5c)), (const float *)(s + 0x44));
			S(float, 0x233cc5c) = (float)v;
			if (!(v > 0)) {
				S(int, 0x234300a + S(int, 0x234240d) * 16) = 1;
				S(u32, 0x233cc5c) = 0x41700000;   /* 15 */
			}
		}
		if (S(int, 0x2343106) == 1)
			do
				net_sendMatchEvent(s);
			while (S(int, 0x2343106) == 1);
		for (int i = 0; i < 16; i++) {
			if (S(int, 0x2343006 + i * 16) == 1)
				net_sendGamePacket(s, i);
			if (S(int, 0x234300a + i * 16) == 1)
				net_sendPlayerInfo(s, i);
			if (net_playerInUse(i) == 1 && S(float, 0x2340c74) > 0.05f && P_INT(S(int, 0x234240d), 0x179d1fe) < 0x180) {
				net_sendColourRing(s, S(int, 0x234240d));
				S(float, 0x2340c74) = (float)-fld_m((const float *)(s + 0x44));
			}
			if (net_playerInUse(i) == 1 && A_INT(i, 0x1eccb78) == 1 && A_INT(i, 0x1eccb80) == S(int, 0x234240d)
			    && (S(float, 0x2340c74) > 0.05f || A_INT(i, 0x1eccc5c) == 1
			        || (!(GAME_VAR(float, s + 0x1eccfa4 + i * 0x8888) < 0) && !(GAME_VAR(float, s + 0x1eccfa4 + i * 0x8888) > 0))
			        || A_INT(i, 0x1eccde4) == 1)) {
				net_sendPlayerState(s, i);
				S(float, 0x2340c74) = (float)-fld_m((const float *)(s + 0x44));
			}
		}
		S(float, 0x2340c74) = f32(fadd_m(fld_m((const float *)(s + 0x2340c74)), (const float *)(s + 0x44)));
	}
	/* the round's end */
	if (S(float, 0x234239d) > 0) {
		PATCHED_THISCALL(0x49a54f, u32, void *, const char *)(stage, g_catalogueFile);   /* catalogue_loadComponents */
		if (S(int, 8) == 1 && S(int, 4) == 0) {   /* the server's end notices, every half second */
			if (S(float, 0x23423b9) > 0.5f) {
				S(int, 0x23423b9) = 0;
				int k = S(int, 0x23423b5);
				if (k == 0)
					event_raise4(s);
				else if (k == 1)
					event_raise5(s);
				else if (k == 2)
					event_raise3(s);
			} else
				S(float, 0x23423b9) = f32(fadd_m(fld_m((const float *)(s + 0x44)), (const float *)(s + 0x23423b9)));
		}
		long double v = fsub_m(fld_m((const float *)(s + 0x234239d)), (const float *)(s + 0x44));
		S(float, 0x234239d) = (float)v;
		if (!(v >= 0)) {
			if (g_startedFromLobby != 0) {
				S(int, 0x23432cf) = 1;
				S(int, 0x2340cf4) = 0;
			}
			S(int, 0x2342399) = 0;
			S(int, 0x23423b5) = -1;
			S(int, 0x233c9fc) = 0;
			S(int, 0x2340cf4) = 0;
			S(int, 0x2340cf0) = 0;
			S(int, 0x234239d) = 0;
			S(int, 0x23424f2) = -1;
			replay_closeRecording((Scene *)s);
			stage_deactivateActors(stage);
			S(int, 0x233cb20 + S(int, 0x233cc10) * 4) = 0;
			S(int, 0x233cb48 + S(int, 0x233cc10) * 4) = 0;
			if (S(int, 8) == 0 && S(int, 0x23423a9) == 1 && g_missionStage == 14) {
				S(int, 0x233c9ec) = 1;   /* the last mission won */
				S(int, 0x23423a1) = 1;
				S(int, 0x23423a5) = 0;
			} else {
				/* the next round */
				if (S(int, 0x233c9f0) == 1) {
					g_titleScore++;
					sound_updateListener((Scene *)s);
				}
				scene_resetScores((Scene *)s);
				S(int, 0x234297a) = -1;
				events_clear((Scene *)s, 60.0f);
				notices_clearAll(s);
				if (S(int, 8) == 0) {
					teams_setup((Scene *)s);
					scene_setLocalTeam((Scene *)s, -1);
					if (S(int, 0x23423a9) == 0)
						escMenu_open((Scene *)s, 3, 0);
					else
						S(int, 0x23432cf) = 1;
					S(int, 0x23423a9) = 0;
					return;
				}
				if (g_mapRotation == 0) {
					S(int, 0x22f0408) = S(int, 0x22f040c) = 0;
					start_view(s);
					music_playMatch((Scene *)s);
				} else {
					if (S(int, 0x1f1ca8) > 0) {   /* the server's map rotation (+0x1f1668: map, mode) */
						S(int, 0x1f1cac) = (S(int, 0x1f1cac) + 1) % S(int, 0x1f1ca8);
						g_missionStage = S(int, 0x1f1668 + S(int, 0x1f1cac) * 16);
						S(int, 0x1f1cb4) = S(int, 0x1f1668 + (S(int, 0x1f1cac) + 1) % S(int, 0x1f1ca8) * 16);
						S(int, 0x1f1cb8) = S(int, 0x1f166c + (S(int, 0x1f1cac) + 1) % S(int, 0x1f1ca8) * 16);
						game_setGameTypeFlags((Stage *)stage, S(int, 0x1f166c + S(int, 0x1f1cac) * 16));
					} else {
						g_missionStage = S(int, 0x1f1cb4);
						S(int, 0x1f1cb4) = -1;
						game_setGameTypeFlags((Stage *)stage, S(int, 0x1f1cb8));
						S(int, 0x1f1cb8) = -1;
					}
					S(int, 0x233cc20) = 1;
					S(int, 0x233cc28) = 0;
				}
				scene_saveNames(s);
				stage_newRound(stage);
				scene_restoreNames(s);
				S(int, 0x2342411) = 0;
				S(int, 0x234243e) = -1;
				if (S(int, 0x22e7184) == 0) {
					S(int, 0x2342415) = 0;
					if (S(int, 0x234240d) >= 0)
						A_INT(S(int, 0x234240d), 0x1eccb48) = 0;
					scene_setLocalTeam((Scene *)s, -1);
				}
				A_INT(S(int, 0x234240d), 0x1eccb60) = 0;
				A_INT(S(int, 0x234240d), 0x1eccb54) = 0;
				A_INT(S(int, 0x234240d), 0x1eccb64) = 0;
				A_INT(S(int, 0x234240d), 0x1eccb58) = 0;
				S(int, 0x2340d04) = 1;
				S(int, 0x23423a9) = 0;
				return;
			}
		}
	}
	/* the frag and time limits */
	if (S(int, 4) == 0 && S(int, 0x2342399) == 0) {
		int limit = S(int, 0x23423ad);
		if (limit > 0) {
			if (S(int, 0x22e7184) == 1) {
				if (S(int, 0x2221fb8 + scene_teamSlot((Scene *)s, 0) * 4) >= S(int, 0x23423ad)
				    || S(int, 0x2221fb8 + scene_teamSlot((Scene *)s, 1) * 4) >= S(int, 0x23423ad)) {
					winning_team(s);
					round_over(s, 0);
					if (S(int, 8) == 0 && S(int, 0x2221fb8 + S(int, 0x234243e) * 4) >= S(int, 0x23423ad)
					    && g_missionStage == g_progress)
						S(int, 0x23423a9) = 1;
				}
			} else if (S(int, 0x2342976) > 0 && A_INT(S(int, 0x23428f6), 0x1eccb54) >= limit) {
				round_over(s, 0);
				if (S(int, 8) == 0 && A_INT(S(int, 0x234240d), 0x1eccb54) >= S(int, 0x23423ad)
				    && g_missionStage == g_progress)
					S(int, 0x23423a9) = 1;
			}
		}
		if (S(int, 0x23423b1) > 0 && S(int, 0x22f0408) >= S(int, 0x23423b1) * 60) {
			if (S(int, 0x22e7184) == 1)
				winning_team(s);
			round_over(s, 1);
		}
	}
	if (S(int, 0x23423a9) == 1 && g_missionStage == g_progress) {   /* the campaign's progress */
		g_progress++;
		profile_saveProgress();
	}
	/* the camera */
	if (S(int, 0x233c9fc) == 0) {
		if (S(int, 0x23424f2) >= 0 && S(int, 0x2340c64) >= 0) {
			int c = S(int, 0x2340c64);
			if (A_INT(c, 0x1eccbbc) != 1 && A_INT(c, 0x1eccf30) >= 0)
				killer_view(s, ACTOR_AT(c));
			else {
				int i = S(int, 0x23424f2);
				if (S(int, 0x233cb98 + i * 4) == 0 && i != 1) {
					preset_angles(s, ACTOR_AT(S(int, 0x2340c64)), 0x23424f2);
					orbit_from(s, ACTOR_AT(S(int, 0x2340c64)), 0x23424f2, 1);
					turn_view(s);
				} else {
					if (i == 1)
						pair_camera(s);
					else
						watch_camera(s);
					float *dir = (float *)(s + 0x233ca10), *up = (float *)(s + 0x233ca1c);
					for (int k = 0; k < 3; k++)
						dir[k] = f32(fsub_m(fld_m((const float *)(s + 0x233cc14) + k), (const float *)(s + 0x233ca04) + k));
					Vec3_normalize(dir);
					BITS(up[1]) = 0x3f800000;
					up[0] = up[2] = 0;
				}
			}
		} else {
			free_camera(s, mv, 0, &move);
			turn_view(s);
		}
	} else if (S(int, 0x233c9fc) == 1) {
		const u8 *t;
		if (S(int, 0x2342399) == 1) {   /* the round's end: the winner, the top player or oneself */
			S(int, 0x233cc10) = 9;
			if (slow_end(s))
				t = ACTOR_AT(S(int, 0x2221fb0));
			else if (GAME_VAR(int, (u8 *)scene_topPlayer((Scene *)s) + 0x14c) == 1)
				t = (const u8 *)scene_topPlayer((Scene *)s);
			else
				t = ACTOR_AT(S(int, 0x234240d));
		} else {
			S(int, 0x233cc10) = S(int, 0x23424ee);
			t = ACTOR_AT(S(int, 0x234240d));
		}
		if (GAME_VAR(int, t + 0x14c) != 1 && GAME_VAR(int, t + 0x4c0) >= 0)
			killer_view(s, t);
		else if (S(int, 0x233cb98 + S(int, 0x233cc10) * 4) != 0)
			look_at(s, (const float *)(RELOC(t) + 0x154));
		else {
			preset_angles(s, t, 0x233cc10);
			if (S(int, 0x233cc10) == 1)
				muzzle_camera(s, t);
			else
				orbit_from(s, t, 0x233cc10, S(int, 0x233cc10) != 9);
			turn_view(s);
		}
	}
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = game_clock();
	GAME_THISFN(camera_setupView, 0x4729b0, void, void *, float *, float *, float *, u32, int, int, u32, u32, u32)(stage, (float *)(s + 0x233ca04), (float *)(s + 0x233ca10),
	              (float *)(s + 0x233ca1c), BITS(fov), w, h, BITS(near), BITS(far), S(u32, 0x44));   /* camera_setupView */
	view_setDistance(stage, GAME_VAR(u32, stage + 0xa08));
	if (S(int, 0x234240d) >= 0)
		chat_keys(s);
	if (S(int, 0x2340d35) != 0)
		S(u32, 0x2340d39) = 0x3dcccccd;   /* 0.1 */
	if (S(int, 0x233c9f0) == 1) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233cc50)), (const float *)(s + 0x44));
		S(float, 0x233cc50) = (float)v;
		if (!(v >= 0))
			sound_updateListener((Scene *)s);
	}
	/* the connection (a client's) */
	if (S(int, 8) == 1) {
		if (S(int, 0x23423a1) == 0) {
			if (net_isClient() == 0) {
				if (S(float, 0x2342395) > 5.0f) {
					msg_connectionLost(s);
					S(int, 0x23423a1) = 1;
					S(u32, 0x23423a5) = 0x40400000;
					music_shutdown();
				} else
					S(float, 0x2342395) = f32(fadd_m(fld_m((const float *)(s + 0x2342395)), (const float *)(s + 0x44)));
			}
			if (S(int, 0x23423a1) == 0 && netq_resends() >= 0x80) {
				netq_clearResends();
				msg_networkUnstable(s);
				S(int, 0x23423a1) = 1;
				S(u32, 0x23423a5) = 0x40400000;
				music_shutdown();
			}
		}
		if (netq_resends() > 0) {
			netq_clearResends();
			S(u32, 0x2340c94) = 0x3f800000;
		} else if (run_down(s, 0x2340c94))
			S(int, 0x2340c94) = 0;
	}
	/* the match restart count */
	if (S(float, 0x233cc4c) > 0) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233cc4c)), (const float *)(s + 0x44));
		S(float, 0x233cc4c) = (float)v;
		if (v > 0) {
			if (ftol(fadd_m(v, (const float *)(s + 0x44))) != ftol(v))
				sound_playVolume(9, 100);
		} else {
			if (S(int, 0x234240d) >= 0 && A_INT(S(int, 0x234240d), 0x1eccb88) >= 0)
				S(int, 0x2340d00) = 1;
			S(int, 0x234239d) = 0;
			S(int, 0x2342399) = 0;
			replay_closeRecording((Scene *)s);
			if (S(int, 0x233c9f0) == 1) {
				g_titleScore++;
				sound_updateListener((Scene *)s);
			}
			for (int i = 0; i < S(int, 0x22f0400); i++)
				S(int, 0x22ee4e0 + i * 0x28) = S(int, 0x22ee4e4 + i * 0x28) = 0;
			for (int i = 0; i < 16; i++) {
				A_INT(i, 0x1eccb54) = A_INT(i, 0x1eccb58) = A_INT(i, 0x1eccb60) = 0;
				A_INT(i, 0x1eccb64) = A_INT(i, 0x1eccb6c) = A_INT(i, 0x1eccb70) = 0;
			}
			stage_clearActorRefs((Stage *)stage);
			msg_newKing((Scene *)s);
			S(int, 0x234297a) = -1;
			events_clear((Scene *)s, 60.0f);
			notices_clearAll(s);
			S(int, 0x22f0408) = S(int, 0x22f040c) = 0;
			A_INT(S(int, 0x234240d), 0x1eccb60) = 0;
			A_INT(S(int, 0x234240d), 0x1eccb54) = 0;
			A_INT(S(int, 0x234240d), 0x1eccb64) = 0;
			A_INT(S(int, 0x234240d), 0x1eccb58) = 0;
			S(int, 0x233cc4c) = 0;
			sound_playVolume(0x18, 100);
		}
	}
	/* the match's end: the log, back to the menu */
	if (S(int, 0x23423a1) == 1) {
		long double v = fsub_m(fld_m((const float *)(s + 0x23423a5)), (const float *)(s + 0x44));
		S(float, 0x23423a5) = (float)v;
		if (!(v > 0)) {
			if (g_matchLogWritten == 0 && g_startedFromLobby != 0)
				write_log(s, (const char *)(g_matchEndedByServer == 1 || (g_matchEndedByUser == 1 && S(int, 0x2342976) <= 1) ? IMG(0x4d069c) : IMG(0x4d05a8)),
				          1, 0);
			replay_closeRecording((Scene *)s);
			music_shutdown();
			if (S(int, 0x2340d35) != 0 && g_paused == 0) {
				S(int, 0x2340d35) = 0;
				chat_keepLastLine();
			}
			if (S(int, 0x233c9f0) == 1)
				sound_updateListener((Scene *)s);
			S(int, 0x23432cf) = 1;
		}
	}
	S(int, 0x233cc28)++;
}
#undef A_INT
#undef P_INT
#undef S
#undef K
#undef ACTOR
#undef ACTOR_INT
#undef ACTOR_AT
