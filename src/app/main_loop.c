/* main_loop.c: one frame of the game. WinMain's message loop calls FUN_004202d0 whenever no window message is
   waiting; it runs either a match frame or the front end's menus. */
#include "../game.h"
#include <string.h>

/* 0x4202d0 (FUN_004202d0): the frame: the music, the menus' fade-in counted down, then main_loop */
void (FUN_004202d0)(void)
{
	music_4572b0();
	if (g_menuFade > 0.0f)
		g_menuFade = g_menuFade - g_frameTime;
	main_loop();
}

/* 0x420280: in a match the input and the match's frame (main_462050); a frame that answers 0 ends the match;
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
	if (main_462050(g_scene) == 0)
		game_postMatch();
}

/* 0x462050 (main_462050): the match's frame by its state; each state's handler answers the next state. The
   playing, free-camera and replay states present the frame (playing only while frameFlag is 1). */
int THISCALL (main_462050)(Scene *scene)
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

#define g_introZoom GAME_VAR(float, 0x4dda48)        /* (by use) the main menu's zoom into a direct start, counted up */
#define g_fovKeys GAME_VAR(int, 0x4e0464)            /* (by use) 1 / 2: the view angle narrows / widens by 5 a frame */
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
	if (blink > F(0x4a94ec))
		g_cursorBlink = 100.0f;
	if (g_screen != g_lastScreen)
		menu_enterState();
	if (GAME_VAR(int, 0x9da49c) != 0x69 && GAME_VAR(int, 0x9da49c) != 0x68) {
		menu_onStateChange();
		menu_processKeys();
	}
	if (g_screen == 300 && GAME_VAR(int, 0x9db994) && !g_dialogPending) {
		g_viewAspect = f32(fsubr_m(fmul_m(fld_m(&g_frameTime), (const float *)0x4a9468), &g_viewAspect));   /* 0.05 a frame */
		F(0x4df02c) = fadd_m(fld_m((const float *)0x4df02c), (const float *)0x4a9418);                       /* the camera 10 back */
		long double zoom = fadd_m(fld_m(&g_introZoom), &g_frameTime);
		g_introZoom = zoom;
		if (!(g_viewAspect >= F(0x4a9420)))
			BITS(g_viewAspect) = 0x3c23d70a;   /* 0.01 */
		if (zoom >= F(0x4a93f4)) {
			g_screen = 9999;
			g_nextScreen = 9999;
			GAME_VAR(int, 0x9db990) = 1;
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
		menu_4290d0();
	if (g_paused)
		menu_428940(GAME_VAR(int, 0x9da3d8), GAME_VAR(int, 0x9da3dc));
	glLoadIdentity();
	if (g_screen != 9999 && !g_profileIntro)
		PATCHED_CALL(0x41fc28, void, void)();   /* menu_drawCursor; the patch DLL draws its own cursor here */
	glDisable(0xbe2);   /* GL_BLEND */
	glFinish();
	SwapBuffers(GAME_VAR(void *, 0x76d480));
	switch (g_fovKeys) {
	case 1:
		if (g_viewAngle > F(0x4a93d0))
			g_viewAngle = fsub_m(fld_m(&g_viewAngle), (const float *)0x4a93d0);
		break;
	case 2:
		if (!(g_viewAngle >= F(0x4a94e8)))
			g_viewAngle = fadd_m(fld_m(&g_viewAngle), (const float *)0x4a93d0);
		break;
	}
	long double now = timer_now();
	D(0x9db980) = now;
	if (g_showFps) {
		D(0x4dd550) = now;
		int frames = ++GAME_VAR(int, 0x4dd0b0);
		long double second = now - D(0x4dd0a0);
		double secondStored = f64(second);
		D(0x4dd978) = secondStored;
		if (second >= D(0x4a94e0)) {
			GAME_VAR(int, 0x4dd0b0) = 0;
			F(0x4dd980) = (long double)frames / secondStored;
			D(0x4dd0a0) = now;
		}
	}
	long double rate = D(0x4a94e0) / (now - D(0x4dd0c8));
	D(0x4dd558) = rate;
	long double frame = fdivr_m(rate, (const float *)0x4a94dc);   /* 60 / rate */
	g_frameTime = frame;
	if (frame > F(0x4a944c))
		g_frameTime = 1.0f;
	D(0x4dd0c8) = now;
}
#undef F
#undef D

/* a countdown (a float in the scene) taken down by the frame's time while above 0, stopping at 0 */
static void count_down(u8 *s, u32 offset, const float *dt)
{
	float *t = (float *)(s + offset);
	const float *zero = (const float *)0x4a93e8;
	if (*t > *zero) {
		long double left = fsub_m(fld_m(t), dt);
		*t = f32(left);
		if (!(left >= *zero))
			*(u32 *)t = 0;
	}
}

/* 0x48b200 (thiscall on the scene): the playing state's frame. The match set up first when it is not yet
   (+0x233cc28 0: game_processGameModeInit); armc_461210 (its answer dropped); the frame's time (+0x44) added to the
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
	(void)armc_461210(s);
	long double second = fadd_m(fld_m(dt), (const float *)(s + 0x233cc34));
	FIELD(float, 0x233cc34) = f32(second);
	float window = f32(fadd_m(fld_m((const float *)(s + 0x2340c90)), dt));
	FIELD(float, 0x2340c90) = window;
	count_down(s, 0x233cc40, dt);
	count_down(s, 0x2342f02, dt);
	count_down(s, 0x2340d39, dt);
	if (second > *(const float *)0x4a9424) {
		int whole = ftol(second);
		FIELD(int, 0x233cc30) += whole;
		FIELD(float, 0x233cc34) = f32(second - whole);
		if (window > *(const float *)0x4a93e8) {
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
	S(int, 0x2343257) = KEY(0x4ded68);
	S(int, 0x234325b) = KEY(0x4ded6c);
	long double dy = (long double)(S(int, 0x234325b) - gfx_getHeight() / 2);
	S(float, 0x2343293) = f32(KEY(0x4df000) ? -dy : dy);
	long double dx = (long double)(S(int, 0x2343257) - gfx_getWidth() / 2);
	if (steer)
		dx = -dx;
	S(float, 0x2343297) = f32(dx);
	long double k = fmul_m((long double)KEY(0x4df008), (const float *)0x4aa480);
	long double f = fmul_m(fadd_m(k * k, (const float *)0x4a9424), (const float *)0x4a942c);
	S(float, 0x2343293) = f32(fmul_m(f, (const float *)(s + 0x2343293)));
	S(float, 0x2343297) = f32(steer ? fmul_m(f, (const float *)(s + 0x2343297)) : dx * f);
	KEY(0x4ded68) = gfx_getWidth() / 2;
	KEY(0x4ded6c) = gfx_getHeight() / 2;
}

/* the weapon slot keys: slot 1 .. 9, 0 (+0x23424f2), each also asking for the switch (+0x2340c6c, +0x23432cb) */
static const u32 k_slotKeys[10][2] = { { 0x4dec90, 1 }, { 0x4dec8c, 2 }, { 0x4deb5c, 3 }, { 0x4deb58, 4 }, { 0x4deb64, 5 },
                                       { 0x4deb60, 6 }, { 0x4deb6c, 7 }, { 0x4deb68, 8 }, { 0x4deb70, 9 }, { 0x4deb78, 0 } };
/* the radio message keys (+0x2343307 one less than the message; the first six 10 more with the modifier 0x67ef24) */
static const u32 k_radioKeys[10] = { 0x4e0468, 0x4e046c, 0x4e0470, 0x4e0874, 0x4e0c78, 0x4e0c7c, 0x4e0c80, 0x4e0c84, 0x4e0c88, 0x4e0460 };
/* the held controls: the binding's two keys and the flag they set */
static const u32 k_heldKeys[10][2] = { { 0x4def30, 0x234325f }, { 0x4def10, 0x234326b }, { 0x4def18, 0x234326f },
                                       { 0x4def00, 0x2343263 }, { 0x4def08, 0x2343267 }, { 0x4def40, 0x2343273 },
                                       { 0x4def48, 0x2343277 }, { 0x4def98, 0x234328b }, { 0x4defe0, 0x234328f },
                                       { 0x4def38, 0x2343283 } };
/* the view keys (+0x2343287: the last held wins, else -1) */
static const u32 k_viewKeys[6] = { 0x4def78, 0x4def80, 0x4def88, 0x4def90, 0x4def68, 0x4def70 };

/* 0x49d290 (thiscall on the game object): the match's input for this frame (match_resetInputState first; nothing
   more before the match runs, +0x233c9e8). In play (no menu +0x2340d35 / +0x2340cf4): with the own view (+0x233c9fc
   0) and alive (+0x2340cf0, or a network game, or the local player's +0x1eccb48), the weapon slot and radio keys,
   else the fire keys only; a spectator's view the fire keys held / pressed; then every held control, the view keys,
   the mouse look (above 0.2 s of frame time it is still), quitting (Esc keys when the death timer +0x2340d39 is
   over), the chat keys, the camera mode cycle (+0x233cc10), the scoreboard keys, the message log toggle cycle
   (+0x2340ce8 / ce4 with their notices). In the in-match menu (+0x2340cf4 1) the mouse moves the selection (the
   original's +-50 step, or the patch DLL's menu_nav where it replaced that block), and its keys choose. A network
   end (FUN_004a86e0) quits. Its caller ignores the eax it leaves */
void THISCALL (match_combatInput)(u8 *s)
{
	match_resetInputState(s);
	if (!S(int, 0x233c9e8))
		return;
	if (S(int, 0x2340d35) == 0 && S(int, 0x2340cf4) == 0) {
		if (S(int, 0x233c9fc) == 0) {
			if (S(int, 0x2340cf0) == 0 || (S(int, 8) == 0 && S(int, 0x1eccb48 + S(int, 0x234240d) * 0x8888) == 0)) {
				if (pressed2(0x4def50, 0x4def54))
					S(int, 0x23432cf) = 1;
			} else {
				if (KEY(0x4ded88)) {
					S(int, 0x234331b) = 1;
					S(int, 0x2340c68) = 1;
				}
				if (S(int, 0x23424f2) >= 0 && KEY(0x4ded8c)) {
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
						S(int, 0x2343307) = k < 6 ? (input_justPressed(KEY(0x67ef24)) ? 10 : 0) + k + 1 : k + 1;
				S(int, 0x2343307)--;
			}
		} else {
			if (held2(0x4def50, 0x4def54))
				S(int, 0x234327b) = 1;
			if (pressed2(0x4def50, 0x4def54))
				S(int, 0x234327f) = 1;
		}
		for (int k = 0; k < 10; k++)
			if (held2(k_heldKeys[k][0], k_heldKeys[k][0] + 4))
				S(int, k_heldKeys[k][1]) = 1;
		S(int, 0x2343287) = -1;
		for (int k = 0; k < 6; k++)
			if (held2(k_viewKeys[k], k_viewKeys[k] + 4))
				S(int, 0x2343287) = k;
		if (!(S(float, 0x44) >= *(const float *)0x4a94f8)) {
			S(int, 0x2343257) = KEY(0x4ded68);
			S(int, 0x234325b) = KEY(0x4ded6c);
			mouse_offset(s, 1);
		} else {
			S(int, 0x2343257) = KEY(0x4ded68);
			S(int, 0x234325b) = KEY(0x4ded6c);
			S(int, 0x2343293) = S(int, 0x2343297) = 0;
			long double k = fmul_m((long double)KEY(0x4df008), (const float *)0x4aa480);
			long double f = fmul_m(fadd_m(k * k, (const float *)0x4a9424), (const float *)0x4a942c);
			S(float, 0x2343293) = f32(fmul_m(f, (const float *)(s + 0x2343293)));
			S(float, 0x2343297) = f32(fmul_m(f, (const float *)(s + 0x2343297)));
			KEY(0x4ded68) = gfx_getWidth() / 2;
			KEY(0x4ded6c) = gfx_getHeight() / 2;
		}
		if (pressed2(0x4defc8, 0x4defcc) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432cf) = 1;
		if (pressed2(0x4def58, 0x4def5c))
			S(int, 0x23432eb) = 1;
		if (pressed2(0x4def60, 0x4def64))
			S(int, 0x23432ef) = 1;
		if (pressed2(0x4deff0, 0x4deff4))
			S(int, 0x23424ee) = S(int, 0x233cc10) == 1 ? 2 : S(int, 0x233cc10) == 2 ? 3 : 1;
		if (pressed2(0x4defa8, 0x4defac) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432fb) = 1;
		else if (pressed2(0x4defb0, 0x4defb4) && !(S(float, 0x2340d39) > 0))
			S(int, 0x23432ff) = 1;
		if (pressed2(0x4deff8, 0x4deffc))
			S(int, 0x2343303) = 1;
		if (input_justPressed(KEY(0x4df8d0))) {
			if (S(int, 0x2340ce8) == 0) {
				S(int, 0x2340ce8) = 1;
				vsprintf_wrap_463450((Scene *)s, (const char *)0x4c7d00);
			} else if (S(int, 0x2340ce4) == 0) {
				S(int, 0x2340ce4) = 1;
				vsprintf_wrap_463450((Scene *)s, (const char *)0x4c7cf0);
			} else {
				S(int, 0x2340ce8) = S(int, 0x2340ce4) = 0;
				vsprintf_wrap_463450((Scene *)s, (const char *)0x4c7ce4);
			}
		}
	} else if (S(int, 0x2340cf4) == 1) {
		mouse_offset(s, 0);
		if (code_matches(0x49ddcb, "56 e8 ?? ?? ?? ?? 59 e9"))
			PATCHED_CALL(0x49ddcc, void, void *)(s);   /* the patch DLL's menu_nav; its block then jumps on to 0x49de23 */
		else {
			const float *down = (const float *)0x4a9558, *up = (const float *)0x4a9560;
			if (!(S(float, 0x2343293) >= *down) || !(S(float, 0x2343297) >= *down))
				S(int, 0x234330b) = 1;
			if (S(float, 0x2343293) > *up || S(float, 0x2343297) > *up)
				S(int, 0x234330f) = 1;
		}
		if (pressed2(0x4def50, 0x4def54))
			S(int, 0x2343313) = 1;
		S(int, 0x2343293) = S(int, 0x2343297) = 0;
		if (input_justPressed(KEY(0x9dae14)) || input_justPressed(KEY(0x9db0a0)))
			S(int, 0x234330b) = 1;
		if (input_justPressed(KEY(0x9db974)) || input_justPressed(KEY(0x76d330)))
			S(int, 0x234330f) = 1;
		if (input_justPressed(KEY(0x9dae70)) || input_justPressed(KEY(0x5b1da8)))
			S(int, 0x2343313) = 1;
		if (input_justPressed(KEY(0x6803a0)))
			S(int, 0x2343317) = 1;
	}
	if (FUN_004a86e0())
		S(int, 0x23432cf) = 1;
}
#undef S
#undef KEY
