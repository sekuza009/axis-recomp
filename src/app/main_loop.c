/* main_loop.c: one frame of the game. WinMain's message loop calls FUN_004202d0 whenever no window message is
   waiting; it runs either a match frame or the front end's menus. */
#include "../game.h"

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
