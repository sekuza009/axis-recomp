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
static const u32 k_partSteps[5][4] = { { 0x23432d3, 0x30c, 0x473b10, 0x15de6c8 }, { 0x23432d7, 0x310, 0x473c20, 0x15fff84 },
                                       { 0x23432db, 0x314, 0x473d30, 0x163b588 }, { 0x23432df, 0x318, 0x473e40, 0x1679b34 },
                                       { 0x23432e3, 0x31c, 0x473f50, 0x16c5178 } };
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
	armc_461210(s);
	float slow = f32(fld_m((const float *)0x4a9424) - fmul_m(fld_m((const float *)(s + 0x44)), (const float *)0x4aa488));
	float turn = f32(fmul_m(fld_m((const float *)(s + 0x44)), (const float *)0x4aa484));
	long double look = fmul_m(fld_m((const float *)(s + 0x44)), (const float *)0x4a93f4);
	float yaw = f32(look * S(float, 0x2343297)), pitch = f32(look * S(float, 0x2343293));
	match_45eb20(stage, 0, S(u32, 0x2343263), S(u32, 0x2343267), S(u32, 0x234326b), S(u32, 0x234326f), *(u32 *)&pitch, *(u32 *)&yaw,
	             S(u32, 0x234327b), S(u32, 0x234325f), S(u32, 0x2343283), S(u32, 0x2343287), 0, 0);
	if (S(int, 0x23432bb)) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233ca28)), &turn);
		S(float, 0x233ca28) = f32(v);
		if (!(v >= *(const float *)0x4a9728))
			S(u32, 0x233ca28) = 0xc45e8000;   /* -890 */
	}
	if (S(int, 0x23432bf)) {
		long double v = fadd_m(fld_m(&turn), (const float *)(s + 0x233ca28));
		S(float, 0x233ca28) = f32(v);
		if (v > *(const float *)0x4a972c)
			S(u32, 0x233ca28) = 0x445e8000;   /* 890 */
	}
	if (S(int, 0x23432b3)) {
		long double v = fsub_m(fld_m((const float *)(s + 0x233ca2c)), &turn);
		S(float, 0x233ca2c) = f32(v);
		if (!(v >= 0))
			S(float, 0x233ca2c) = f32(fadd_m(v, (const float *)0x4a94c8));
	}
	if (S(int, 0x23432b7)) {
		long double v = fadd_m(fld_m(&turn), (const float *)(s + 0x233ca2c));
		S(float, 0x233ca2c) = f32(v);
		if (v >= *(const float *)0x4a94c8)
			S(float, 0x233ca2c) = f32(fsub_m(v, (const float *)0x4a94c8));
	}
	float *zoom = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
	if (S(int, 0x23432ab)) {
		*zoom = f32(fmul_m(fld_m(&slow), zoom));
		if (!(*zoom >= *(const float *)0x4a9450))
			GAME_VAR(u32, zoom) = 0x43fa0000;   /* 500 */
	}
	zoom = (float *)(s + 0x233cb70) + S(int, 0x233cc10);
	if (S(int, 0x23432af)) {
		*zoom = f32(fdiv_m(fld_m(zoom), &slow));
		if (*zoom > *(const float *)0x4a9708)
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
	float far = hud_scale(), near = match_4686f0();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = game_clock();
	GAME_THISCALL(0x4729b0, void, void *, float *, float *, float *, u32, int, int, u32, u32, u32)(stage, cam, dir, up, *(u32 *)&fov, w, h,
	                                                                                             *(u32 *)&near, *(u32 *)&far, S(u32, 0x44));   /* camera_setupView */
	if (S(int, 0x2340ce0) == 0) {
		actor_updateAll(stage, S(u32, 0x44));
		bullet_updateAll(stage, S(u32, 0x44));
		match_479a90(stage, S(u32, 0x44));
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
				ViewVolume_add_485120(s + 0x74, (const void *)0xa1f238, pa, pb, 1);
				far_point(a, pitch, yaw);
				far_point(b, pitch, yaw + 150);
				about(pb, b, actor);
				about(pa, a, actor);
				ViewVolume_add_485120(s + 0x74, (const void *)0xa1f238, pa, pb, 1);
			}
	hud_45e170((Stage *)stage, s + 0x74, -1);
	hud_47d060(stage, s + 0x74);
	hud_479af0((Stage *)stage, s + 0x74);
	render_drawObjects(s + 0x74, S(int, 0x1f1664), 0.0f);
	gfx_setProjectionHud(0, 1.0f);
	return S(int, 0x23432cf) == 1 ? 0 : 3;
}
#undef S

#define S(type, offset) GAME_VAR(type, s + (offset))
#define K(address) ((const float *)(address))
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
	u32 r = GAME_VAR(u32, 0xa106f8 + (GAME_VAR(u32, 0xa1efb8) & 0xfff) * 4) % n;
	GAME_VAR(u32, 0xa1efb8)++;
	return r;
}

/* the view angle by step (narrower with +0x234328b), kept within 10 .. 60 */
static void zoom_view(u8 *s, const float *step)
{
	if (S(int, 0x234328b)) {
		float a = f32(fsub_m((long double)game_clock(), step));
		match_4686e0(BITS(a));
		if (!(game_clock() >= 10.0f))
			match_4686e0(0x41200000);   /* 10 */
	} else {
		float a = f32(fadd_m((long double)game_clock(), step));
		match_4686e0(BITS(a));
		if (game_clock() > 60.0f)
			match_4686e0(0x42700000);   /* 60 */
	}
}

/* the end of the replay file (or the skip key): the next replay (a random one with +0x9eeac0, else the next in
   order, the list wrapping round with +0x4b2a7c) with the scene reset; 0 when the list is done (the viewer quits) */
static int replay_next(u8 *s)
{
	u8 *stage = s + 0x1f36c8;
	if (GAME_VAR(int, 0x9eeac0) == 1) {
		scene_resetActors(stage);
		scene_reset(stage);
		S(u32, 0x1f35c0) = S(int, 0x1f35bc) > 0 ? rand_below(S(u32, 0x1f35bc)) : 0;
	} else {
		if (++S(int, 0x1f35c0) >= S(int, 0x1f35bc)) {
			if (GAME_VAR(int, 0x4b2a7c) != 1) {
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
static void free_camera(u8 *s, const float *mv)
{
	float *cam = (float *)(s + 0x233ca04), out[3], delta[3], dist, plane[4];
	int hit = collision_moveActor(s + 0x1f36c8, 500.0f, cam, mv, 0x43fa0000, 0, out, delta, &dist, plane, S(int, 0x234325f) ? 0xa0e7d8 : 0);
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

/* preset orbiting the followed player (i, the preset's angles added to the player's own unless fixed): the camera
   pulled back by the zoom from 0.85 of the player's height, short of what is in the way, at most 300 off; facing
   (0, 0, 1) */
static void orbit_camera(u8 *s, int i)
{
	float *cam = (float *)(s + 0x233ca04), a[3], b[3], to[3], d[3];
	S(float, 0x233ca28) = (float)fld_m((const float *)(s + 0x233cb20) + i);
	if (S(int, 0x233cbc0 + S(int, 0x233cc10) * 4) == 0)
		S(float, 0x233ca28) = f32(fadd_m(fld_m((const float *)(s + 0x233cb20) + i), &ACTOR(S(int, 0x2340c64), 0xc)));
	if (S(float, 0x233ca28) > 890.0f)
		S(u32, 0x233ca28) = 0x445e8000;
	if (!(S(float, 0x233ca28) >= -890.0f))
		S(u32, 0x233ca28) = 0xc45e8000;
	i = S(int, 0x233cc10);
	S(float, 0x233ca2c) = (float)fld_m((const float *)(s + 0x233cb48) + i);
	if (S(int, 0x233cbe8 + S(int, 0x233cc10) * 4) == 0)
		S(float, 0x233ca2c) = f32(fadd_m(fld_m((const float *)(s + 0x233cb48) + i), &ACTOR(S(int, 0x2340c64), 0x10)));
	int me = S(int, 0x2340c64);
	a[0] = a[2] = 0;
	a[1] = f32(fmul_m(fld_m(&ACTOR(me, 0x294)), K(0x4aa478)));   /* 0.85 */
	Vec3_rotateAxis(a, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(a, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	b[0] = b[1] = 0;
	b[2] = f32(fsub_m(-fld_m((const float *)(s + 0x233cb70) + S(int, 0x233cc10)), K(0x4aa440)));   /* - zoom - 300 */
	Vec3_rotateAxis(b, 1, ftol(fld_m((const float *)(s + 0x233ca28))));
	Vec3_rotateAxis(b, 2, ftol(fld_m((const float *)(s + 0x233ca2c))));
	me = S(int, 0x2340c64);
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fld_m(&a[k]), &ACTOR(me, k * 4)));
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
static void watch_camera(u8 *s)
{
	int me = S(int, 0x2340c64);
	float *mid = (float *)(s + 0x233cc14), *cam = (float *)(s + 0x233ca04), hit[3];
	long double dx = fsub_m(fld_m(&ACTOR(me, 0)), &mid[0]);
	float dy = f32(fsub_m(fld_m(&ACTOR(me, 4)), &mid[1])), dz = f32(fsub_m(fld_m(&ACTOR(me, 8)), &mid[2]));
	long double hx = fmul_m(dx, K(0x4a942c));
	float hy = f32(fmul_m(fld_m(&dy), K(0x4a942c))), hz = f32(fmul_m(fld_m(&dz), K(0x4a942c)));
	mid[0] = f32(fadd_m(hx, &mid[0]));
	mid[1] = f32(fadd_m(fld_m(&hy), &mid[1]));
	mid[2] = f32(fadd_m(fld_m(&hz), &mid[2]));
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
	memcpy(mv, (const void *)0xa0e7e8, 12);
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
static const u32 k_replayHeld[7][3] = { { 0x4def30, 0x4def34, 0x234325f }, { 0x4def10, 0x4def14, 0x234326b }, { 0x4def18, 0x4def1c, 0x234326f },
                                        { 0x4def00, 0x4def04, 0x2343263 }, { 0x4def08, 0x4def0c, 0x2343267 }, { 0x4def40, 0x4def44, 0x2343273 },
                                        { 0x4def48, 0x4def4c, 0x2343277 } };
/* the camera preset keys (presets 1 .. 9, 0) */
static const u32 k_presetKeys[10] = { 0x4dec90, 0x4dec8c, 0x4deb5c, 0x4deb58, 0x4deb64, 0x4deb60, 0x4deb6c, 0x4deb68, 0x4deb70, 0x4deb78 };
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
	if (S(int, 0x233cc28) == 0) {
		start_view(s);
		for (S(int, 0x233cc10) = 0; S(int, 0x233cc10) < 10; S(int, 0x233cc10)++)
			preset_reset(s);
		S(int, 0x233cc10) = 1;
		FUN_0045dfb0((Stage *)stage, -1);
		S(int, 0x2340c64) = -1;
		S(int, 0x2340c68) = S(int, 0x2340c6c) = S(int, 0x2340c70) = 0;
		timer_getGameTime(s + 0xc);
		int y = gfx_getHeight() / 2;
		input_setCursorPos(gfx_getWidth() / 2, y);
		S(int, 0x233cc38) = S(int, 0x233cc3c) = S(int, 0x2342425) = 0;
		S(int, 0x233cc30) = S(int, 0x233cc34) = 0;
		S(int, 0x2340d29) = S(int, 0x2340d2d) = 0;
		match_4629c0((Scene *)s, 60.0f);
	}
	armc_461210(s);
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
	if (GAME_VAR(int, 0x4ded88)) {
		S(int, 0x234331b) = 1;
		S(int, 0x2340c68) = 1;
	}
	if (GAME_VAR(int, 0x4ded8c)) {
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
		if (input_justPressed(GAME_VAR(int, 0x4e0468)))
			follow = k <= 6 && input_justPressed(GAME_VAR(int, 0x67ef24)) ? k + 10 : k;
	follow--;
	S(int, 0x2340d21) = input_isDown(GAME_VAR(int, 0x5b1da8)) ? 1 : 0;
	S(int, 0x2340d25) = input_isDown(GAME_VAR(int, 0x9dae70)) ? 1 : 0;
	if (held2(0x4defe0, 0x4defe4))
		S(int, 0x234328f) = 1;
	if (input_justPressed(GAME_VAR(int, 0x4df8d0))) {
		const char *mode;
		if (S(int, 0x2340ce8) == 0) {
			S(int, 0x2340ce8) = 1;
			mode = (const char *)0x4c7d00;   /* "HIDDEN MESSAGE BOX MODE" */
		} else if (S(int, 0x2340ce4) == 0) {
			S(int, 0x2340ce4) = 1;
			mode = (const char *)0x4c7cf0;   /* "SCREENSHOT MODE" */
		} else {
			S(int, 0x2340ce8) = S(int, 0x2340ce4) = 0;
			mode = (const char *)0x4c7ce4;   /* "NORMAL MODE" */
		}
		vsprintf_wrap_463450((Scene *)s, mode);
	}
	/* the mouse: its offset from the centre (y inverted with 0x4df000), scaled by the sensitivity, unless slow */
	S(int, 0x2343257) = GAME_VAR(int, 0x4ded68);
	S(int, 0x234325b) = GAME_VAR(int, 0x4ded6c);
	if (!(S(float, 0x44) >= 0.2f)) {
		if (GAME_VAR(int, 0x4df000) == 0)
			S(float, 0x2343293) = f32((long double)(S(int, 0x234325b) - gfx_getHeight() / 2));
		else
			S(float, 0x2343293) = f32(-(long double)(S(int, 0x234325b) - gfx_getHeight() / 2));
		S(float, 0x2343297) = f32(-(long double)(S(int, 0x2343257) - gfx_getWidth() / 2));
	} else
		S(int, 0x2343293) = S(int, 0x2343297) = 0;
	long double sens = fmul_m((long double)GAME_VAR(int, 0x4df008), K(0x4aa480));
	sens = fmul_m(fadd_m(sens * sens, K(0x4a9424)), K(0x4a942c));
	S(float, 0x2343293) = f32(fmul_m(sens, (const float *)(s + 0x2343293)));
	S(float, 0x2343297) = f32(fmul_m(sens, (const float *)(s + 0x2343297)));
	GAME_VAR(int, 0x4ded68) = gfx_getWidth() / 2;
	GAME_VAR(int, 0x4ded6c) = gfx_getHeight() / 2;
	if (pressed2(0x4defc8, 0x4defcc) && !(S(float, 0x2340d39) > 0)) {
		GAME_VAR(int, 0x9db994) = 0;
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
		match_496e40(stage, BITS(dt));
		match_490d40(stage, BITS(dt));
		actor_updateAll(stage, BITS(dt));
		bullet_updateAll(stage, BITS(dt));
		match_479a90(stage, BITS(dt));
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
	match_462ac0(s, S(u32, 0x44));
	if (S(int, 0x234328f) == 1)
		S(u32, 0x233cc40) = 0x40a00000;   /* the ranking shown 5 s */

	/* the camera */
	S(int, 0x233c9fc) = S(int, 0x2340c64) >= 0;
	if (S(int, 0x233c9fc) == 0) {
		free_camera(s, mv);
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
	float far = hud_scale(), near = match_4686f0();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = game_clock();
	GAME_THISCALL(0x4729b0, void, void *, float *, float *, float *, u32, int, int, u32, u32, u32)(stage, (float *)(s + 0x233ca04), (float *)(s + 0x233ca10),
	              (float *)(s + 0x233ca1c), BITS(fov), w, h, BITS(near), BITS(far), S(u32, 0x44));   /* camera_setupView */
	S(int, 0x233cc28)++;

	/* the scene */
	hud_456b50(g_textures);
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
	hud_496f20((Stage *)stage, hud_scale());
	render_processRenderingBy(stage, view, hud_scale());
	hud_490da0((Stage *)stage, view);
	hud_45e170((Stage *)stage, view, -1);
	hud_47d060(stage, view);
	hud_479af0((Stage *)stage, view);
	hud_48f970(stage, view);
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
				ViewVolume_add_485120(view, (const void *)0xa1f208, p, q, 1);
			}
		}
	if (S(int, 0xbe170c) == 1) {
		hud_472900((Stage *)stage, stage + 0x9ee048, GAME_VAR(u32, stage + 0x9ee058), GAME_VAR(u32, stage + 0x9ee05c), GAME_VAR(u32, stage + 0x9ee060));
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
			sprintf(text, (const char *)0x4b0320, n > 0 ? n : n + 10);   /* "%d" */
			PATCHED_CALL(0x48a259, void, int, int, const char *, int)(0x28, 0x10, text, 0x10);   /* text_drawSized */
		}
		if (!(S(float, 0x233cc34) >= 0.5f)) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			PATCHED_THISCALL(0x48a299, void, void *, int, int, int)(s, 0x20e, 0x10, 5);   /* replay_drawIcon */
			text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
			sprintf(text, (const char *)0x4c7cd8, S(int, 0x233cc30) / 60, S(int, 0x233cc30) % 60);   /* "%02d:%02d" */
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
#undef S
#undef K
#undef ACTOR
#undef ACTOR_INT
