/* main_loop.c: one frame of the game. WinMain's message loop calls app_frame whenever no window message is
   waiting; it runs either a match frame or the front end's menus. */
#include "../game.h"
#include <string.h>

/* 0x4202d0 (app_frame): the frame: the music, the menus' key guard counted down, then main_loop */
void (app_frame)(void)
{
	music_loopIfEnded();
	if (g_menuKeyGuard > 0.0f)
		g_menuKeyGuard = g_menuKeyGuard - g_frameTime;
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
	if (!g_textFieldOpen) {
		input_updateMouse();
		input_reacquireKeyboard();
	}
	if (match_frameByState(g_scene) == 0)
		game_postMatch();
}

/* 0x462050 (match_frameByState): the match's frame by its state; each state's handler answers the next state. The
   playing, free-camera and replay states present the frame (playing only while matchDrawing is 1). */
int THISCALL (match_frameByState)(Scene *scene)
{
	switch (scene->matchState) {
	case 1:
		return scene->matchState = game_processLoadingMode(scene);
	case 2:
		scene->matchState = match_playFrame(scene);
		if (scene->matchDrawing == 1)
			gfx_swapBuffers();
		break;
	case 3:
		scene->matchState = match_freeCamFrame(scene);
		gfx_swapBuffers();
		break;
	case 4:
		scene->matchState = replay_frame(scene);
		gfx_swapBuffers();
		break;
	}
	return scene->matchState;
}

/* x rounded to a double, as the original's fst qword does (for a value read again) */
static inline double f64(long double x)
{
	volatile double r = (double)x;
	return r;
}


/* 0x41fa40: the menus' frame: the cursor blink clock (100 past 1e6), the screen's set-up when it changed, its keys
   (unless 0x9da49c is 0x68 / 0x69); a direct start from the main menu zooms in (aspect down to 0.01, the camera
   back) and starts the match after 100; the screen's frame, the message box, the input line (menu_drawInputLine) while a text field is open, the cursor
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
		menu_processMouse();
		menu_processKeys();
	}
	if (g_screen == 300 && g_replayZoomIn && !g_dialogPending) {
		g_viewAspect = f32(fsubr_m(fmul_m(fld_m(&g_frameTime), k_0_05f), &g_viewAspect));   /* 0.05 a frame */
		g_armcCamDistance = fadd_m(fld_m((const float *)ADDR(g_armcCamDistance)), (const float *)ADDR(k_10f));                       /* the camera 10 back */
		long double zoom = fadd_m(fld_m(&g_introZoom), &g_frameTime);
		g_introZoom = zoom;
		if (!(g_viewAspect >= k_0_01f))
			g_viewAspect = 0.01f;
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
	case 200: menuState200_title(); break;
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
	if (g_textFieldOpen)
		menu_drawInputLine(g_chatCaretX, g_chatCaretY);
	glLoadIdentity();
	if (g_screen != 9999 && !g_profileIntro)
		PATCHED_CALL(0x41fc28, void, void)();   /* menu_drawCursor; the patch DLL draws its own cursor here */
	glDisable(0xbe2);   /* GL_BLEND */
	glFinish();
	SwapBuffers(g_windowDC);
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
   (+0x233cc28 0: match_startRound); scene_averageFrameTime (its answer dropped); the frame's time (+0x44) added to the
   second's fraction (+0x233cc34) and to the FPS window (+0x2340c90); three countdowns (msgFade, readyTimer,
   keyGuard). Past a whole second the seconds (+0x233cc30) take it, and the frame and packet counts of the window
   (+0x2340c80 / +0x2340c84) become rates (+0x2340c88 / +0x2340c8c; 0 for an empty window), the window cleared. Then
   the input, the game mode and, in state 2, the HUD pass (through the call site the patch DLL retargets). A quit (+0x23432cf 1) stops the music and answers 0; else
   the state (+0x233cc20) */
int THISCALL (match_playFrame)(u8 *s)
{
#define SC ((Scene *)s)
	const float *dt = &SC->frameTime;
	if (SC->modeStarted == 0)
		match_startRound(s);
	(void)scene_averageFrameTime(s);
	long double second = fadd_m(fld_m(dt), &SC->secondFraction);
	SC->secondFraction = f32(second);
	float window = f32(fadd_m(fld_m(&SC->windowTime), dt));
	SC->windowTime = window;
	count_down(s, offsetof(Scene, msgFade), dt);
	count_down(s, offsetof(Scene, noticeTimer), dt);
	count_down(s, offsetof(Scene, keyGuard), dt);
	if (second > k_1f) {
		int whole = ftol(second);
		SC->wholeSeconds += whole;
		SC->secondFraction = f32(second - whole);
		if (window > k_0f) {
			SC->sendRate = f32((long double)SC->windowSent / window);
			SC->receiveRate = f32((long double)SC->windowReceived / window);
		} else
			(*(int *)&SC->sendRate) = (*(int *)&SC->receiveRate) = 0;
		(*(int *)&SC->windowTime) = SC->windowSent = SC->windowReceived = 0;
	}
	match_combatInput(s);
	match_frame(s);
	if (SC->matchState == 2)
		PATCHED_THISCALL(0x48b386, void, void *)(s);   /* hud_pass; the patch DLL calls its hud_pass_wrap here */
	if (SC->quitAsked == 1) {
		music_shutdown();
		return 0;
	}
	return SC->matchState;
#undef SC
}

#define S(type, offset) GAME_VAR(type, s + (offset))
#define SC ((Scene *)s)   /* the same scene by its fields (src/scene.fields) */
#define KEY(at) GAME_VAR(int, at)

/* either key of a binding (its two key globals) pressed this frame / held */
static int pressed2(u32 a, u32 b) { return input_justPressed(KEY(a)) || input_justPressed(KEY(b)); }
static int held2(u32 a, u32 b) { return input_isDown(KEY(a)) || input_isDown(KEY(b)); }

/* the mouse's offset from the screen centre (+0x2343293 vertical, inverted by the setting 0x4df000; +0x2343297
   horizontal, negated when steer is set) scaled by the sensitivity (0x4df008: ((s 0.02)^2 + 1) / 2), and the
   pointer put back in the centre (0x4ded68 / 0x4ded6c) */
static void mouse_offset(u8 *s, int steer)
{
	SC->mouseX = g_mouseX;
	SC->mouseY = g_mouseY;
	long double dy = (long double)(SC->mouseY - gfx_getHeight() / 2);
	SC->mouseDy = f32(g_mouseInvert ? -dy : dy);
	long double dx = (long double)(SC->mouseX - gfx_getWidth() / 2);
	if (steer)
		dx = -dx;
	SC->mouseDx = f32(dx);
	long double k = fmul_m((long double)g_mouseSensitivity, k_0_02f);
	long double f = fmul_m(fadd_m(k * k, (const float *)ADDR(k_1f)), (const float *)ADDR(k_0_5f));
	SC->mouseDy = f32(fmul_m(f, &SC->mouseDy));
	SC->mouseDx = f32(steer ? fmul_m(f, &SC->mouseDx) : dx * f);
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
}

/* the spectator's camera preset keys: numpad 1 .. 9, 0 (into cameraSlot), each also a manual pick and an action */
static const u32 k_spectatePresetKeys[10][2] = { { ADDR(g_dikNumpad1), 1 }, { ADDR(g_dikNumpad2), 2 }, { ADDR(g_dikNumpad3), 3 }, { ADDR(g_dikNumpad4), 4 }, { ADDR(g_dikNumpad5), 5 },
                                       { ADDR(g_dikNumpad6), 6 }, { ADDR(g_dikNumpad7), 7 }, { ADDR(g_dikNumpad8), 8 }, { ADDR(g_dikNumpad9), 9 }, { ADDR(g_dikNumpad0), 0 } };
/* the follow keys, 1 .. 9, 0 (into followKey, one less than the player; the first six 10 more with left shift) */
static const u32 k_followKeys[10] = { ADDR(g_dik1), ADDR(g_dik2), ADDR(g_dik3), ADDR(g_dik4), ADDR(g_dik5), ADDR(g_dik6), ADDR(g_dik7), ADDR(g_dik8), ADDR(g_dik9), ADDR(g_dik0) };
/* the held controls: the binding's two keys and the flag they set */
static const u32 k_heldKeys[10][2] = { { (OBJ(g_controls) + 0x30), offsetof(Scene, holdAltitude) }, { ADDR(g_keyStepLeft), offsetof(Scene, holdStepLeft) }, { ADDR(g_keyStepRight), offsetof(Scene, holdStepRight) },
                                       { ADDR(g_keyForward), offsetof(Scene, holdForward) }, { ADDR(g_keyBackward), offsetof(Scene, holdBackward) }, { (OBJ(g_controls) + 0x40), offsetof(Scene, holdUp) },
                                       { (OBJ(g_controls) + 0x48), offsetof(Scene, holdDown) }, { (OBJ(g_controls) + 0x98), offsetof(Scene, holdZoom) }, { (OBJ(g_controls) + 0xe0), offsetof(Scene, rankingKey) },
                                       { (OBJ(g_controls) + 0x38), offsetof(Scene, holdBooster) } };
/* the weapon slot keys: HAND WEAPON 1 .. 4, R / L SHOULDER (bindings 15 .. 18, 13, 14): the slot of the last held into weaponKey, else -1 */
static const u32 k_weaponKeys[6] = { (OBJ(g_controls) + 0x78), (OBJ(g_controls) + 0x80), (OBJ(g_controls) + 0x88), (OBJ(g_controls) + 0x90), (OBJ(g_controls) + 0x68), (OBJ(g_controls) + 0x70) };

/* 0x49d290 (thiscall on the game object): the match's input for this frame (match_resetInputState first; nothing
   more before the match is drawn, matchDrawing). With no chat line or menu open: spectating (playing 0) and out
   of the match (localAlive 0, or a solo game without a mech in play) the fire keys leave it; spectating otherwise
   a click follows the next player, a right click the next preset, the numpad picks the preset (cameraSlot) and the number
   keys the player to follow (followKey); playing, the fire keys held / pressed; then every held control, the weapon keys,
   the mouse look (above 0.2 s of frame time it is still), the game menu (its keys once keyGuard is
   over), the chat keys, the camera mode cycle (respawnCameraMode), the scoreboard keys, the message log toggle cycle
   (+0x2340ce8 / ce4 with their notices). In the in-match menu (+0x2340cf4 1) the mouse moves the selection (the
   original's +-50 step, or the patch DLL's menu_nav where it replaced that block), and its keys choose. A network
   end (net_hostGone) quits. Its caller ignores the eax it leaves */
void THISCALL (match_combatInput)(u8 *s)
{
	match_resetInputState(s);
	if (!SC->matchDrawing)
		return;
	if (SC->chatMode == 0 && SC->escMenuOpen == 0) {
		if (SC->playing == 0) {
			if (SC->localAlive == 0 || (SC->sessionMode == 0 && SC->players[SC->localPlayer].inPlay == 0)) {
				if (pressed2((OBJ(g_controls) + 0x50), (OBJ(g_controls) + 0x54)))
					SC->quitAsked = 1;
			} else {
				if (g_mouseClick) {
					SC->followNextAsked = 1;
					SC->manualPick[0] = 1;
				}
				if (SC->cameraSlot >= 0 && g_rightClick) {
					SC->presetNextAsked = 1;
					SC->manualPick[1] = 1;
					SC->actionKey = 1;
				}
				for (int k = 0; k < 10; k++)
					if (input_justPressed(KEY(k_spectatePresetKeys[k][0]))) {
						SC->cameraSlot = k_spectatePresetKeys[k][1];
						SC->manualPick[1] = 1;
						SC->actionKey = 1;
					}
				SC->followKey = 0;
				for (int k = 0; k < 10; k++)
					if (input_justPressed(KEY(k_followKeys[k])))
						SC->followKey = k < 6 ? (input_justPressed(g_dikLShift) ? 10 : 0) + k + 1 : k + 1;
				SC->followKey--;
			}
		} else {
			if (held2((OBJ(g_controls) + 0x50), (OBJ(g_controls) + 0x54)))
				SC->holdFire = 1;
			if (pressed2((OBJ(g_controls) + 0x50), (OBJ(g_controls) + 0x54)))
				SC->firePressed = 1;
		}
		for (int k = 0; k < 10; k++)
			if (held2(k_heldKeys[k][0], k_heldKeys[k][0] + 4))
				S(int, k_heldKeys[k][1]) = 1;
		SC->weaponKey = -1;
		for (int k = 0; k < 6; k++)
			if (held2(k_weaponKeys[k], k_weaponKeys[k] + 4))
				SC->weaponKey = k;
		if (!(SC->frameTime >= k_0_2f)) {
			SC->mouseX = g_mouseX;
			SC->mouseY = g_mouseY;
			mouse_offset(s, 1);
		} else {
			SC->mouseX = g_mouseX;
			SC->mouseY = g_mouseY;
			(*(int *)&SC->mouseDy) = (*(int *)&SC->mouseDx) = 0;
			long double k = fmul_m((long double)g_mouseSensitivity, k_0_02f);
			long double f = fmul_m(fadd_m(k * k, (const float *)ADDR(k_1f)), (const float *)ADDR(k_0_5f));
			SC->mouseDy = f32(fmul_m(f, &SC->mouseDy));
			SC->mouseDx = f32(fmul_m(f, &SC->mouseDx));
			g_mouseX = gfx_getWidth() / 2;
			g_mouseY = gfx_getHeight() / 2;
		}
		if (pressed2(ADDR(g_keyGameMenu), ADDR(g_keyGameMenu2)) && !(SC->keyGuard > 0))
			SC->quitAsked = 1;
		if (pressed2((OBJ(g_controls) + 0x58), (OBJ(g_controls) + 0x5c)))
			SC->prevWeaponPressed = 1;
		if (pressed2((OBJ(g_controls) + 0x60), (OBJ(g_controls) + 0x64)))
			SC->nextWeaponPressed = 1;
		if (pressed2((OBJ(g_controls) + 0xf0), (OBJ(g_controls) + 0xf4)))
			SC->respawnCameraMode = SC->cameraMode == 1 ? 2 : SC->cameraMode == 2 ? 3 : 1;
		if (pressed2(ADDR(g_keyChat), (OBJ(g_controls) + 0xac)) && !(SC->keyGuard > 0))
			SC->talkPressed = 1;
		else if (pressed2((OBJ(g_controls) + 0xb0), (OBJ(g_controls) + 0xb4)) && !(SC->keyGuard > 0))
			SC->teamTalkPressed = 1;
		if (pressed2((OBJ(g_controls) + 0xf8), (OBJ(g_controls) + 0xfc)))
			SC->helpPressed = 1;
		if (input_justPressed(g_dikF11)) {
			if (SC->messagesHidden == 0) {
				SC->messagesHidden = 1;
				notice_printCentre((Scene *)s, (const char *)STR(0x4c7d00, "HIDDEN MESSAGE BOX MODE"));
			} else if (SC->hudHidden == 0) {
				SC->hudHidden = 1;
				notice_printCentre((Scene *)s, (const char *)STR(0x4c7cf0, "SCREENSHOT MODE"));
			} else {
				SC->messagesHidden = SC->hudHidden = 0;
				notice_printCentre((Scene *)s, (const char *)STR(0x4c7ce4, "NORMAL MODE"));
			}
		}
	} else if (SC->escMenuOpen == 1) {
		mouse_offset(s, 0);
		if (PATCHED_BLOCK(0x49ddcc, 0x49ddcb, "56 e8 ?? ?? ?? ?? 59 e9"))
			PATCHED_CALL(0x49ddcc, void, void *)(s);   /* the patch DLL's menu_nav; its block then jumps on to 0x49de23 */
		else {
			const float *down = (const float *)ADDR(k_m50f), *up = (const float *)ADDR(k_50f);
			if (!(SC->mouseDy >= *down) || !(SC->mouseDx >= *down))
				SC->menuKeys[0] = 1;
			if (SC->mouseDy > *up || SC->mouseDx > *up)
				SC->menuKeys[1] = 1;
		}
		if (pressed2((OBJ(g_controls) + 0x50), (OBJ(g_controls) + 0x54)))
			SC->menuKeys[2] = 1;
		(*(int *)&SC->mouseDy) = (*(int *)&SC->mouseDx) = 0;
		if (input_justPressed(g_dikLeft) || input_justPressed(g_dikUp))
			SC->menuKeys[0] = 1;
		if (input_justPressed(g_dikRight) || input_justPressed(g_dikDown))
			SC->menuKeys[1] = 1;
		if (input_justPressed(g_dikEnter) || input_justPressed(g_dikSpace))
			SC->menuKeys[2] = 1;
		if (input_justPressed(g_dikEscape))
			SC->menuKeys[3] = 1;
	}
	if (net_hostGone())
		SC->quitAsked = 1;
}
#undef S
#undef SC
#undef KEY

#define S(type, offset) GAME_VAR(type, s + (offset))
#define SC ((Scene *)s)   /* the same scene by its fields (src/scene.fields) */

/* (0, 10000, 0) turned about x by pitch, then about z by yaw (tenths of a degree) */
static void far_point(float *v, int pitch, int yaw)
{
	v[0] = 0;
	GAME_VAR(u32, &v[1]) = 0x461c4000;
	v[2] = 0;
	Vec3_rotateAxis(v, 1, pitch);
	Vec3_rotateAxis(v, 2, yaw);
}

/* the point v about the actor's position */
static void about(float *out, const float *v, const u8 *actor)
{
	for (int k = 0; k < 3; k++)
		out[k] = f32(fadd_m(fld_m(&v[k]), &((const Player *)actor)->pos[k]));
}

/* the free-camera part steps: the flag (F1 .. F5 held), the player's part field, the setter, the table size */
static const u32 k_partSteps[5][4] = {   /* the F key, the part in the player record, its setter, the types' count */
	{ offsetof(Scene, fKeys[0]), offsetof(PlayerRecord, parts[0]), FN_ADDR(actor_setActorTypeHeadInfoBy, 0x473b10), offsetof(Scene, headCount) },
	{ offsetof(Scene, fKeys[1]), offsetof(PlayerRecord, parts[1]), FN_ADDR(actor_setActorTypeChestInfoBy, 0x473c20), offsetof(Scene, chestCount) },
	{ offsetof(Scene, fKeys[2]), offsetof(PlayerRecord, parts[2]), FN_ADDR(actor_setActorTypeArmInfoBy, 0x473d30), offsetof(Scene, armCount) },
	{ offsetof(Scene, fKeys[3]), offsetof(PlayerRecord, parts[3]), FN_ADDR(actor_setActorTypeLegInfoBy, 0x473e40), offsetof(Scene, legCount) },
	{ offsetof(Scene, fKeys[4]), offsetof(PlayerRecord, parts[4]), FN_ADDR(actor_setActorTypeBoosterInfoBy, 0x473f50), offsetof(Scene, boosterCount) } };
/* the held keys and their flags: right button, A, D, W, S, Q, E, left button, shift */
static const u32 k_freeKeys[9][2] = { { 2, offsetof(Scene, holdAltitude) }, { 0x41, offsetof(Scene, holdStepLeft) }, { 0x44, offsetof(Scene, holdStepRight) }, { 0x57, offsetof(Scene, holdForward) }, { 0x53, offsetof(Scene, holdBackward) },
                                      { 0x51, offsetof(Scene, holdUp) }, { 0x45, offsetof(Scene, holdDown) }, { 1, offsetof(Scene, holdFire) }, { 0x10, offsetof(Scene, holdBooster) } };

/* 0x48a370 (thiscall on the game object): the free camera / test mode's frame. On its first frame the camera
   presets (+0x233ca30, ten of six fields) copied to the working set (+0x233cb20), the game clock read and the
   cursor centred. The keys (Windows virtual keys) set the input flags; ctrl with up / down zooms, else up / down /
   left / right turn the camera (+0x233ca28 pitch within +-890, +0x233ca2c heading wrapped at 3600); space resets it;
   Z / X (or shift with them) step the local player's (+0x234240d) parts held by F1 .. F6 down / up through their
   tables (the weapon slot by its item, selected again); the camera is placed behind the actor (camera_setupView);
   unless scenePaused (never set) the actors, bullets and particles move and the actor's ammunition is halved; the
   scene is drawn, with a 100 x 150 grid of lines about the actor when +0x2340cd0. Returns 0 once Esc was pressed,
   else 3 (this mode again) */
u32 THISCALL (match_freeCamFrame)(u8 *s)
{
	u8 *stage = (u8 *)SCENE_STAGE(s);
	if (SC->modeStarted == 0) {
		SC->localPlayer = 0;
		(*(int *)&SC->cameraAngle[0]) = (*(int *)&SC->cameraAngle[1]) = 0;
		for (SC->cameraMode = 0; SC->cameraMode < 10; SC->cameraMode++)
			for (int f = 0; f < 6; f++)
				SC->cameraSettings[f][SC->cameraMode] = SC->cameraPresets[f][SC->cameraMode];
		SC->cameraMode = 0;
		TimeSync_frameTime((u8 *)&SC->timer);
		int y = gfx_getHeight() / 2;
		input_setCursorPos(gfx_getWidth() / 2, y);
	}
	u8 *actor = (u8 *)&SC->players[SC->localPlayer];
	Player *act = (Player *)actor;
	u8 *player = (u8 *)&SC->playerRecords[act->player];
	for (int k = 0; k < 9; k++)
		S(int, k_freeKeys[k][1]) = input_asyncKeyDown(k_freeKeys[k][0]) ? 1 : 0;
	SC->weaponKey = -1;
	for (int k = 0; k < 6; k++)
		if (input_asyncKeyDown('1' + k))
			SC->weaponKey = k;
	if (input_asyncKeyDown(0x11)) {
		SC->zoomInHeld = input_asyncKeyDown(0x26) ? 1 : 0;
		SC->zoomOutHeld = input_asyncKeyDown(0x28) ? 1 : 0;
		SC->pitchUpHeld = 0;
		SC->pitchDownHeld = 0;
	} else {
		SC->zoomInHeld = SC->zoomOutHeld = 0;
		SC->pitchUpHeld = input_asyncKeyDown(0x26) ? 1 : 0;
		SC->pitchDownHeld = input_asyncKeyDown(0x28) ? 1 : 0;
	}
	SC->turnLeftHeld = input_asyncKeyDown(0x25) ? 1 : 0;
	SC->turnRightHeld = input_asyncKeyDown(0x27) ? 1 : 0;
	const int *cursor = input_getCursorPos();
	SC->mouseX = cursor[0];
	SC->mouseY = cursor[1];
	SC->mouseDy = f32((long double)(SC->mouseY - gfx_getHeight() / 2));
	SC->mouseDx = f32(-(long double)(SC->mouseX - gfx_getWidth() / 2));
	int y = gfx_getHeight() / 2;
	input_setCursorPos(gfx_getWidth() / 2, y);
	SC->actionKey = input_asyncKeyPressed(0x20) ? 1 : 0;
	SC->quitAsked = input_asyncKeyPressed(0x1b) ? 1 : 0;
	for (int k = 0; k < 6; k++)
		SC->fKeys[k] = input_asyncKeyDown(0x70 + k) ? 1 : 0;
	SC->partStepDownPressed = input_asyncKeyPressed('Z') || (input_asyncKeyDown(0x10) && input_asyncKeyDown('Z'));
	SC->partStepUpPressed = input_asyncKeyPressed('X') || (input_asyncKeyDown(0x10) && input_asyncKeyDown('X'));
	scene_averageFrameTime(s);
	float slow = f32(fld_m((const float *)ADDR(k_1f)) - fmul_m(fld_m(&SC->frameTime), k_0_6f));
	float turn = f32(fmul_m(fld_m(&SC->frameTime), k_750f));
	long double look = fmul_m(fld_m(&SC->frameTime), (const float *)ADDR(k_100f));
	float yaw = f32(look * SC->mouseDx), pitch = f32(look * SC->mouseDy);
	actor_setInput(stage, 0, (*(u32 *)&SC->holdForward), (*(u32 *)&SC->holdBackward), (*(u32 *)&SC->holdStepLeft), (*(u32 *)&SC->holdStepRight), *(u32 *)&pitch, *(u32 *)&yaw,
	             (*(u32 *)&SC->holdFire), (*(u32 *)&SC->holdAltitude), (*(u32 *)&SC->holdBooster), (*(u32 *)&SC->weaponKey), 0, 0);
	if (SC->pitchUpHeld) {
		long double v = fsub_m(fld_m(SC->cameraAngle), &turn);
		SC->cameraAngle[0] = f32(v);
		if (!(v >= k_m890f))
			SC->cameraAngle[0] = -890.0f;   /* -890 */
	}
	if (SC->pitchDownHeld) {
		long double v = fadd_m(fld_m(&turn), SC->cameraAngle);
		SC->cameraAngle[0] = f32(v);
		if (v > k_890f)
			SC->cameraAngle[0] = 890.0f;   /* 890 */
	}
	if (SC->turnLeftHeld) {
		long double v = fsub_m(fld_m(&SC->cameraAngle[1]), &turn);
		SC->cameraAngle[1] = f32(v);
		if (!(v >= 0))
			SC->cameraAngle[1] = f32(fadd_m(v, (const float *)ADDR(k_3600f)));
	}
	if (SC->turnRightHeld) {
		long double v = fadd_m(fld_m(&turn), &SC->cameraAngle[1]);
		SC->cameraAngle[1] = f32(v);
		if (v >= k_3600f)
			SC->cameraAngle[1] = f32(fsub_m(v, (const float *)ADDR(k_3600f)));
	}
	float *zoom = (float *)&SC->cameraSettings[2][SC->cameraMode];
	if (SC->zoomInHeld) {
		*zoom = f32(fmul_m(fld_m(&slow), zoom));
		if (!(*zoom >= k_500f))
			GAME_VAR(u32, zoom) = 0x43fa0000;   /* 500 */
	}
	zoom = (float *)&SC->cameraSettings[2][SC->cameraMode];
	if (SC->zoomOutHeld) {
		*zoom = f32(fdiv_m(fld_m(zoom), &slow));
		if (*zoom > k_10000f)
			GAME_VAR(u32, zoom) = 0x461c4000;   /* 10000 */
	}
	if (SC->actionKey) {
		SC->cameraSettings[2][SC->cameraMode] = 0x44fa0000;   /* 2000 (the zoom, a float's bits) */
		(*(int *)&SC->cameraAngle[0]) = (*(int *)&SC->cameraAngle[1]) = 0;
		(*(int *)&act->pitch) = (*(int *)&act->yaw) = 0;
		(*(int *)&act->nextPitch) = (*(int *)&act->nextYaw) = 0;
	}
	int item = -1;
	if (SC->partStepDownPressed == 1) {
		for (int k = 0; k < 5; k++)
			if (S(int, k_partSteps[k][0]) == 1 && GAME_VAR(int, player + k_partSteps[k][1]) > 0)
				GAME_THISCALL(k_partSteps[k][2], int, void *, int, int)(stage, act->player, GAME_VAR(int, player + k_partSteps[k][1]) - 1);
		if (SC->fKeys[5] == 1) {
			int it = ((PlayerRecord *)player)->items[act->slot];
			if (it > 0)
				item = it - 1;
		}
	} else if (SC->partStepUpPressed == 1) {
		for (int k = 0; k < 5; k++)
			if (S(int, k_partSteps[k][0]) == 1 && GAME_VAR(int, player + k_partSteps[k][1]) < S(int, k_partSteps[k][3]) - 1)
				GAME_THISCALL(k_partSteps[k][2], int, void *, int, int)(stage, act->player, GAME_VAR(int, player + k_partSteps[k][1]) + 1);
		if (SC->fKeys[5] == 1) {
			int it = ((PlayerRecord *)player)->items[act->slot];
			if (it < SC->actorInfoCount - 1)
				item = it + 1;
		}
	}
	if (item >= 0) {
		int slot = SC->actorInfo[item].slotType ? 4 : 0;
		actor_setActorTypeItemInfoBy((Stage *)stage, 0, slot, item);
		actor_selectWeapon((Stage *)stage, 0, slot);
	}
	float *cam = (float *)SC->cameraPos, *dir = SC->cameraDir, *up = SC->cameraUp;
	cam[0] = cam[1] = 0;
	cam[2] = f32(fld_m((const float *)&SC->cameraSettings[2][SC->cameraMode]));
	Vec3_rotateAxis(cam, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(cam, 2, ftol(fld_m(&SC->cameraAngle[1])));
	for (int k = 0; k < 3; k++)
		cam[k] = f32(fadd_m(fld_m(&act->nextPos[k]), &cam[k]));
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m(&act->nextPos[k]), &cam[k]));
	up[0] = 0;
	GAME_VAR(u32, &up[1]) = 0x3f800000;
	up[2] = 0;
	Vec3_rotateAxis(up, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(up, 2, ftol(fld_m(&SC->cameraAngle[1])));
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = view_angle();
	camera_setupView(stage, cam, dir, up, *(u32 *)&fov, w, h,
	                                                                                             *(u32 *)&near, *(u32 *)&far, BITS(SC->frameTime));   /* camera_setupView */
	if (SC->scenePaused == 0) {
		actor_updateAll(stage, BITS(SC->frameTime));
		bullet_updateAll(stage, BITS(SC->frameTime));
		stage_updateEffects(stage, BITS(SC->frameTime));
		for (int k = 0; k < 4; k++) {
			Player *me = &SC->players[SC->localPlayer];
			me->ammo[k] = me->ammoMax[k] / 2;
		}
	}
	SC->modeStarted++;
	glClearColor_stored(((const u32[]){ 0x3dcccccd, 0x3f000000, 0x3f800000 }));
	glClearDepth(1.0);
	glClear(0x4100);
	gfx_setProjectionHud(1, 1.0f);
	ViewVolume_captureMatrices(SC->view, 0, SC->modelview);
	ViewVolume_reset(SC->view);
	if (SC->debugGrid == 1)
		for (int pitch = 0; pitch < 0x708; pitch += 100)
			for (int yaw = 0; yaw < 0xe10; yaw += 150) {
				float a[3], b[3], pa[3], pb[3];
				far_point(a, pitch, yaw);
				far_point(b, pitch + 100, yaw);
				about(pb, b, actor);
				about(pa, a, actor);
				ViewVolume_addSegment(SC->view, (const void *)ADDR(g_colourMaskRed), pa, pb, 1);
				far_point(a, pitch, yaw);
				far_point(b, pitch, yaw + 150);
				about(pb, b, actor);
				about(pa, a, actor);
				ViewVolume_addSegment(SC->view, (const void *)ADDR(g_colourMaskRed), pa, pb, 1);
			}
	stage_drawActors((Stage *)stage, SC->view, -1);
	stage_drawBullets(stage, SC->view);
	stage_drawParticles((Stage *)stage, SC->view);
	ViewVolume_draw(SC->view, SC->renderMode, 0.0f);
	gfx_setProjectionHud(0, 1.0f);
	return SC->quitAsked == 1 ? 0 : 3;
}
#undef S
#undef SC

#define S(type, offset) GAME_VAR(type, s + (offset))
#define SC ((Scene *)s)   /* the same scene by its fields (src/scene.fields) */

/* the camera back at the map's start view (+0x22ee228: position, pitch, heading) */
static void start_view(u8 *s)
{
	memcpy(SC->cameraPos, SC->cameraSaved, 12);
	BITS(SC->cameraAngle[0]) = SC->cameraSaved[3];
	BITS(SC->cameraAngle[1]) = SC->cameraSaved[4];
}

/* the current camera preset (cameraMode) back from its stored one: six fields of ten */
static void preset_reset(u8 *s)
{
	for (int f = 0; f < 6; f++)
		SC->cameraSettings[f][SC->cameraMode] = SC->cameraPresets[f][SC->cameraMode];
}

/* following no one: the free camera from the start view */
static void unfollow(u8 *s)
{
	SC->watchedPlayer = -1;
	SC->playing = 0;
	SC->manualPick[2] = 1;
	start_view(s);
}

/* the game's next random number below n (its table 0xa106f8 by the counter 0xa1efb8) */
static u32 rand_below(u32 n)
{
	u32 r = (*(u32 *)&g_randTable[g_randPos & 0xfff]) % n;
	g_randPos++;
	return r;
}

/* the view angle by step (narrower with +0x234328b), kept within 10 .. 60 */
static void zoom_view(u8 *s, const float *step)
{
	if (SC->holdZoom) {
		float a = f32(fsub_m((long double)view_angle(), step));
		view_setAngle(BITS(a));
		if (!(view_angle() >= 10.0f))
			view_setAngle(0x41200000);   /* 10 */
	} else {
		float a = f32(fadd_m((long double)view_angle(), step));
		view_setAngle(BITS(a));
		if (view_angle() > 60.0f)
			view_setAngle(0x42700000);   /* 60 */
	}
}

/* the end of the replay file (or the skip key): the next replay (a random one with +0x9eeac0, else the next in
   order, the list wrapping round with +0x4b2a7c) with the scene reset; 0 when the list is done (the viewer quits) */
static int replay_next(u8 *s)
{
	u8 *stage = (u8 *)SCENE_STAGE(s);
	if (g_replayRandomOrder == 1) {
		scene_resetActors(stage);
		scene_reset(stage);
		SC->replayIndex = SC->replayCount > 0 ? rand_below(((u32)SC->replayCount)) : 0;
	} else {
		if (++SC->replayIndex >= SC->replayCount) {
			if (g_replayWrap != 1) {
				SC->quitAsked = 1;
				return 0;
			}
			SC->replayIndex = 0;
		}
		scene_resetActors(stage);
		scene_reset(stage);
	}
	SC->matchState = 1;
	SC->modeStarted = 0;
	return 1;
}

/* the player followed: a number key (f, 0 ..), the next live player (+0x234331b), or a random one now and then
   (none yet, gone, or followed 14 s); then the camera preset: the next one (+0x234331f) or a random one after 7 s */
static void choose_followed(u8 *s, int f)
{
	int n = SC->playerCount;
	if (n <= 0) {
		SC->watchedPlayer = -1;
		return;
	}
	if (f >= 0) {
		if (SC->players[f].team >= 0) {
			SC->watchedPlayer = f;
			SC->manualPick[2] = 0;
			SC->manualPick[0] = 1;
		}
	} else if (SC->followNextAsked == 1) {
		int cur = SC->watchedPlayer, next = cur + 1;
		if (next == n)
			unfollow(s);
		else
			for (;;) {
				if (SC->players[next].inPlay == 1) {
					SC->watchedPlayer = next;
					SC->manualPick[2] = 0;
					break;
				}
				if (++next >= n) {
					unfollow(s);
					break;
				}
				if (next == cur)
					break;
			}
	} else if ((SC->manualPick[2] == 0 && SC->watchedPlayer < 0) || SC->watchedPlayer >= n || SC->followTime > 14.0f) {
		u32 r = rand_below(n);
		SC->watchedPlayer = r;
		if (SC->players[r].active == 1)
			SC->followTime = 0.0f;
		else
			SC->watchedPlayer = -1;
	}
	if (SC->presetNextAsked == 1)
		SC->cameraMode = (SC->cameraMode + 1) % 10;
	else if (SC->presetTime > 7.0f) {
		u32 r = rand_below(100);
		SC->cameraMode = r < 5 ? 0 : r < 35 ? 1 : r < 45 ? 2 : r < 50 ? 3 : r < 55 ? 4 : r < 60 ? 5 : r < 65 ? 6 : r < 70 ? 7 : 8 + (r >= 75);
		SC->presetTime = 0.0f;
	}
}

/* the free camera's move (mv, from the keys) through the world, kept in the map's box (+0xbe2fcc .. +0xbe2fd8);
   facing (0, 0, -1) */
/* the move's results (collision_moveActor's: where it ends, the slide, the distance, the plane) */
typedef struct { float out[3], delta[3], dist, plane[4]; } Move;

static void free_camera(u8 *s, const float *mv, u32 filter, Move *m)
{
	float *cam = (float *)SC->cameraPos, *out = m->out, *delta = m->delta;
	int hit = collision_moveActor((u8 *)SCENE_STAGE(s), 500.0f, cam, mv, 0x43fa0000, 0, out, delta, &m->dist, m->plane, filter);
	memcpy(cam, out, 12);
	if (hit == 1) {
		cam[0] = f32(fadd_m(fld_m(&delta[0]), &cam[0]));
		cam[2] = f32(fadd_m(fld_m(&delta[2]), &cam[2]));
		cam[1] = f32(fadd_m(fld_m(&delta[1]), &cam[1]));
	}
	for (int k = 0; k < 3; k++) {
		if (!(cam[k] >= SCENE_STAGE(s)->levelLow[k]))
			BITS(cam[k]) = BITS(SCENE_STAGE(s)->levelLow[k]);
		else if (cam[k] > SCENE_STAGE(s)->levelHigh[k])
			BITS(cam[k]) = BITS(SCENE_STAGE(s)->levelHigh[k]);
	}
	float *dir = SC->cameraDir;
	dir[0] = dir[1] = 0;
	dir[2] = -1.0f;
}

/* the preset's pitch (+0x233ca28) and heading (+0x233ca2c) from its table (index at +preset), the actor's own
   (+0x160 / +0x164) added unless the preset fixes them; the pitch within +-890 */
static void preset_angles(u8 *s, const u8 *t, u32 preset)
{
	int i = S(int, preset);
	SC->cameraAngle[0] = (float)fld_m((const float *)&SC->cameraSettings[0][i]);
	if (SC->cameraSettings[4][S(int, preset)] == 0)
		SC->cameraAngle[0] = f32(fadd_m(fld_m((const float *)&SC->cameraSettings[0][i]), &((const Player *)t)->pitch));
	if (SC->cameraAngle[0] > 890.0f)
		SC->cameraAngle[0] = 890.0f;
	if (!(SC->cameraAngle[0] >= -890.0f))
		SC->cameraAngle[0] = -890.0f;
	i = S(int, preset);
	SC->cameraAngle[1] = (float)fld_m((const float *)&SC->cameraSettings[1][i]);
	if (SC->cameraSettings[5][S(int, preset)] == 0)
		SC->cameraAngle[1] = f32(fadd_m(fld_m((const float *)&SC->cameraSettings[1][i]), &((const Player *)t)->yaw));
}

/* the camera pulled back by the preset's zoom (+0x233cb70) from 0.85 of the actor t's height (its position with
   eye 0), short of what is in the way, at most 300 off; facing (0, 0, 1) */
static void orbit_from(u8 *s, const u8 *t, u32 preset, int eye)
{
	float *cam = (float *)SC->cameraPos, a[3] = { 0, 0, 0 }, b[3], to[3], d[3];
	if (eye) {
		a[1] = f32(fmul_m(fld_m(&((const Player *)t)->radius), &k_0_85f));   /* 0.85 */
		Vec3_rotateAxis(a, 1, ftol(fld_m(SC->cameraAngle)));
		Vec3_rotateAxis(a, 2, ftol(fld_m(&SC->cameraAngle[1])));
	}
	b[0] = b[1] = 0;
	b[2] = f32(fsub_m(-fld_m((const float *)&SC->cameraSettings[2][S(int, preset)]), &k_300f));   /* - zoom - 300 */
	Vec3_rotateAxis(b, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(b, 2, ftol(fld_m(&SC->cameraAngle[1])));
	for (int k = 0; k < 3; k++)
		a[k] = f32(fadd_m(fld_m(&a[k]), &((const Player *)t)->pos[k]));
	to[0] = f32(fadd_m(fld_m(&b[0]), &a[0]));
	to[1] = f32(fadd_m(fld_m(&a[1]), &b[1]));
	to[2] = f32(fadd_m(fld_m(&a[2]), &b[2]));
	if (collision_rayTrace((u8 *)SCENE_STAGE(s), a, to, cam) == 0)
		memcpy(cam, to, 12);
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(&cam[k]), &a[k]));
	if (Vec3_normalize(d) > 300.0f) {
		long double dx = fmul_m(fld_m(&d[0]), &k_300f);
		float dy = f32(fmul_m(fld_m(&d[1]), &k_300f)), dz = f32(fmul_m(fld_m(&d[2]), &k_300f));
		cam[0] = f32(fld_m(&cam[0]) - dx);
		cam[1] = f32(fsub_m(fld_m(&cam[1]), &dy));
		cam[2] = f32(fsub_m(fld_m(&cam[2]), &dz));
	}
	float *dir = SC->cameraDir;
	dir[0] = dir[1] = 0;
	dir[2] = 1.0f;
}

/* an actor's record (0x8888 bytes from +0x1ecca70) */
#define ACTOR_AT(i) ((u8 *)&SC->players[i])

/* preset orbiting the followed player (the preset index: cameraMode) */
static void orbit_camera(u8 *s, int i)
{
	(void)i;
	preset_angles(s, ACTOR_AT(SC->watchedPlayer), offsetof(Scene, cameraMode));
	orbit_from(s, ACTOR_AT(SC->watchedPlayer), offsetof(Scene, cameraMode), 1);
}

/* preset 1: the followed player and the nearest other live one, the camera on the line through both beyond the
   followed one (the angle by their distance); alone, a point 5 heights ahead. Looks at their middle (+0x233cc14) */
static void pair_camera(u8 *s)
{
	int me = SC->watchedPlayer, best = -1, n = SC->playerCount;
	float *mid = SC->cameraTarget, *cam = (float *)SC->cameraPos, *dir = SC->cameraDir, d[3], t[3];
	float nearest;
	BITS(nearest) = 0x7f7fffff;
	for (int j = 0; j < n; j++)
		if (SC->players[j].active == 1 && j != me) {
			for (int k = 0; k < 3; k++)
				d[k] = f32(fsub_m(fld_m(&SC->players[me].pos[k]), &SC->players[j].pos[k]));
			long double dist = fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1]);
			dist = dist + fmul_m(fld_m(&d[0]), &d[0]);
			if (!(dist >= nearest)) {
				nearest = (float)dist;
				best = j;
			}
		}
	if (best >= 0) {
		long double x = fadd_m(fld_m(&SC->players[best].pos[0]), &SC->players[me].pos[0]);
		float y = f32(fadd_m(fld_m(&SC->players[best].pos[1]), &SC->players[me].pos[1])), z = f32(fadd_m(fld_m(&SC->players[best].pos[2]), &SC->players[me].pos[2]));
		mid[0] = f32(fmul_m(x, &k_0_5f));
		mid[1] = f32(fmul_m(fld_m(&y), &k_0_5f));
		mid[2] = f32(fmul_m(fld_m(&z), &k_0_5f));
	} else {
		float e[3] = { 0, 0, f32(fmul_m(fld_m(&SC->players[me].radius), &k_5f)) };   /* 5 heights */
		Vec3_rotateAxis(e, 2, 100 - ftol(fld_m(&SC->players[me].yaw)));
		me = SC->watchedPlayer;
		for (int k = 0; k < 3; k++)
			mid[k] = f32(fadd_m(fld_m(&e[k]), &SC->players[me].pos[k]));
	}
	for (int k = 0; k < 3; k++)
		t[k] = dir[k] = f32(fsub_m(fld_m(&SC->players[me].pos[k]), &mid[k]));
	long double len = Vec3_normalize(dir);
	long double three = fmul_m(fld_m(&SC->players[SC->watchedPlayer].radius), &k_3f);
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fmul_m(three, &dir[k]));
	for (int k = 0; k < 3; k++)
		t[k] = f32(fadd_m(fld_m(&t[k]), &dir[k]));
	Vec3_rotateAxis(t, 2, ftol(fmul_m(fsub_m(len, &k_30000f), &k_m0_002f)));   /* (len - 30000) * -0.002 */
	for (int k = 0; k < 3; k++)
		cam[k] = f32(fadd_m(fld_m(&t[k]), &mid[k]));
}

/* the other presets: the look point (+0x233cc14) moved half way to the followed player; when the view to it is
   blocked, the camera goes behind the player's head (its height back along its own heading and pitch) */
/* the look point (+0x233cc14) moved half way to p */
static void look_toward(u8 *s, const float *p)
{
	float *mid = SC->cameraTarget;
	long double dx = fsub_m(fld_m(&p[0]), &mid[0]);
	float dy = f32(fsub_m(fld_m(&p[1]), &mid[1])), dz = f32(fsub_m(fld_m(&p[2]), &mid[2]));
	long double hx = fmul_m(dx, &k_0_5f);
	float hy = f32(fmul_m(fld_m(&dy), &k_0_5f)), hz = f32(fmul_m(fld_m(&dz), &k_0_5f));
	mid[0] = f32(fadd_m(hx, &mid[0]));
	mid[1] = f32(fadd_m(fld_m(&hy), &mid[1]));
	mid[2] = f32(fadd_m(fld_m(&hz), &mid[2]));
}

static void watch_camera(u8 *s)
{
	int me = SC->watchedPlayer;
	float *mid = SC->cameraTarget, *cam = (float *)SC->cameraPos, hit[3];
	look_toward(s, &SC->players[me].pos[0]);
	if (collision_rayTrace((u8 *)SCENE_STAGE(s), cam, mid, hit)) {
		me = SC->watchedPlayer;
		float e[3] = { 0, 0, f32(-fld_m(&SC->players[me].radius)) };
		Vec3_rotateAxis(e, 1, ftol(fld_m(&SC->players[me].pitch)));
		me = SC->watchedPlayer;
		Vec3_rotateAxis(e, 2, ftol(fld_m(&SC->players[me].yaw)));
		me = SC->watchedPlayer;
		for (int k = 0; k < 3; k++)
			cam[k] = f32(fadd_m(fld_m(&e[k]), &SC->players[me].pos[k]));
	}
}

/* the direction and up vectors turned by the camera's pitch (+0x233ca28) and heading (+0x233ca2c) */
static void turn_view(u8 *s)
{
	float *dir = SC->cameraDir, *up = SC->cameraUp;
	Vec3_rotateAxis(dir, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(dir, 2, ftol(fld_m(&SC->cameraAngle[1])));
	up[0] = 0;
	up[1] = 1.0f;
	up[2] = 0;
	Vec3_rotateAxis(up, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(up, 2, ftol(fld_m(&SC->cameraAngle[1])));
}

/* the free camera's keys: the move (mv) by speed along the view, turned for the held direction keys; up / down,
   three times as fast with +0x2343283; the mouse turns the view (pitch within +-890, heading wrapped at 3600) */
static void free_keys(u8 *s, float *mv, const float *speed, const float *turn)
{
	memcpy(mv, (const void *)ADDR(g_vecZero), 12);
	int bits = SC->holdStepLeft ? 1 : 0;
	if (SC->holdStepRight)
		bits |= 0x10;
	if (SC->holdAltitude == 0) {
		if (SC->holdForward)
			bits |= 0x100;
		if (SC->holdBackward)
			bits |= 0x1000;
	}
	if (bits) {
		mv[2] = f32(-fld_m(speed));
		mv[0] = mv[1] = 0;
		int a = bits == 0x110 ? -450 : bits == 1 ? -2700 : bits == 0x10 ? -900 : bits == 0x101 ? -3150 : bits == 0x1000 ? -1800
		      : bits == 0x1001 ? -2250 : bits == 0x1010 ? -1350 : 0;
		if (a)
			Vec3_rotateAxis(mv, 2, a);
		Vec3_rotateAxis(mv, 1, ftol(fld_m(SC->cameraAngle)));
		Vec3_rotateAxis(mv, 2, ftol(fld_m(&SC->cameraAngle[1])));
	}
	if ((SC->holdAltitude && SC->holdForward) || SC->holdUp)
		mv[1] = f32(fadd_m(fld_m(&mv[1]), speed));
	if ((SC->holdAltitude && SC->holdBackward) || SC->holdDown)
		mv[1] = f32(fsub_m(fld_m(&mv[1]), speed));
	if (SC->holdBooster)
		for (int k = 0; k < 3; k++)
			mv[k] = f32(fmul_m(fld_m(&mv[k]), &k_3f));
	long double v = fsubr_m(fmul_m(fld_m(turn), &SC->mouseDy), SC->cameraAngle);
	SC->cameraAngle[0] = (float)v;
	if (v > 890.0f)
		SC->cameraAngle[0] = 890.0f;
	if (!(SC->cameraAngle[0] >= -890.0f))
		SC->cameraAngle[0] = -890.0f;
	v = fadd_m(fmul_m(fld_m(turn), &SC->mouseDx), &SC->cameraAngle[1]);
	SC->cameraAngle[1] = (float)v;
	if (v >= 3600.0f)
		SC->cameraAngle[1] = f32(fsub_m(v, &k_3600f));
	if (!(SC->cameraAngle[1] >= 0))
		SC->cameraAngle[1] = f32(fadd_m(fld_m(&SC->cameraAngle[1]), &k_3600f));
}

/* a count-down (seconds at +offset) by dt when running; 1 when it ran out this frame */
static int run_down(u8 *s, u32 offset)
{
	if (!(S(float, offset) > 0))
		return 0;
	long double v = fsub_m(fld_m((const float *)(s + offset)), &SC->frameTime);
	S(float, offset) = (float)v;
	return !(v >= 0);
}

/* the free camera / follow keys: held pairs and the flag each sets */
static const u32 k_replayHeld[7][3] = { { (OBJ(g_controls) + 0x30), (OBJ(g_controls) + 0x34), offsetof(Scene, holdAltitude) }, { ADDR(g_keyStepLeft), (OBJ(g_controls) + 0x14), offsetof(Scene, holdStepLeft) }, { ADDR(g_keyStepRight), (OBJ(g_controls) + 0x1c), offsetof(Scene, holdStepRight) },
                                        { ADDR(g_keyForward), (OBJ(g_controls) + 0x4), offsetof(Scene, holdForward) }, { ADDR(g_keyBackward), (OBJ(g_controls) + 0xc), offsetof(Scene, holdBackward) }, { (OBJ(g_controls) + 0x40), (OBJ(g_controls) + 0x44), offsetof(Scene, holdUp) },
                                        { (OBJ(g_controls) + 0x48), (OBJ(g_controls) + 0x4c), offsetof(Scene, holdDown) } };
/* the camera preset keys (presets 1 .. 9, 0) */
static const u32 k_presetKeys[10] = { ADDR(g_dikNumpad1), ADDR(g_dikNumpad2), ADDR(g_dikNumpad3), ADDR(g_dikNumpad4), ADDR(g_dikNumpad5), ADDR(g_dikNumpad6), ADDR(g_dikNumpad7), ADDR(g_dikNumpad8), ADDR(g_dikNumpad9), ADDR(g_dikNumpad0) };
/* the eight lines of a debug marker's star: the far corner's signs */
static const signed char k_star[8][3] = { { 1, 1, 1 }, { -1, -1, -1 }, { 1, -1, 1 }, { -1, 1, -1 }, { -1, 1, 1 }, { 1, -1, -1 }, { -1, -1, 1 }, { 1, 1, -1 } };

/* 0x487f00 (thiscall on the game object): the replay viewer's frame. On its first frame (+0x233cc28 0) the camera
   from the start view and its presets reset, the cursor centred. The keys: the free camera's moves, presets 1 .. 9
   and 0, following a player (the follow keys; the mouse buttons for the next player / preset), slow motion
   (+0x2340d21), skip (+0x2340d25), the ranking, the HUD modes, quit; the mouse turns the view. Unless scenePaused
   (never set) the replay file (+0x2340d08) is read up to the replay's time (+0x2340d2d): records of time, sender,
   length and packet handed to net_processGamePacket; at its end the next replay starts (returns 1) or the viewer
   quits. Then the scene's frame (clocks, objects, actors, bullets, particles, items), kill messages, the camera
   (free, or one of the presets about the followed player), the scene drawn (with debug markers for the map's
   points when +0x2340cd4) and the overlay: icons for the followed player's preset and the replay clock, names,
   the ranking, the start count. Returns 0 when the viewer quits (the file closed, the music stopped), else 4 */
u32 THISCALL (replay_frame)(u8 *s)
{
	u8 *stage = (u8 *)SCENE_STAGE(s);
	Stage *st = (Stage *)stage;
	float mv[3];   /* the free camera's move: set by its keys, which a camera now following no one may not have read
	                  this frame (the original then moves by whatever its stack held) */
	Move move;
	if (SC->modeStarted == 0) {
		start_view(s);
		for (SC->cameraMode = 0; SC->cameraMode < 10; SC->cameraMode++)
			preset_reset(s);
		SC->cameraMode = 1;
		stage_selectActor((Stage *)stage, -1);
		SC->watchedPlayer = -1;
		SC->manualPick[0] = SC->manualPick[1] = SC->manualPick[2] = 0;
		TimeSync_frameTime((u8 *)&SC->timer);
		int y = gfx_getHeight() / 2;
		input_setCursorPos(gfx_getWidth() / 2, y);
		(*(int *)&SC->followTime) = (*(int *)&SC->presetTime) = (*(int *)&SC->flagUploadTimer) = 0;
		SC->wholeSeconds = (*(int *)&SC->secondFraction) = 0;
		(*(int *)&SC->recordTime) = (*(int *)&SC->replayTime) = 0;
		events_clear((Scene *)s, 60.0f);
	}
	scene_averageFrameTime(s);
	/* the replay clock (+0x233cc30 whole seconds, +0x233cc34 the fraction) */
	long double t = fadd_m(fld_m(&SC->secondFraction), &SC->frameTime);
	SC->secondFraction = (float)t;
	if (t > 1.0f) {
		SC->wholeSeconds += ftol(t);
		int whole = ftol(fld_m(&SC->secondFraction));
		SC->secondFraction = f32(fsubr_m((long double)whole, &SC->secondFraction));
	}
	match_resetInputState(s);
	for (int k = 0; k < 7; k++)
		if (held2(k_replayHeld[k][0], k_replayHeld[k][1]))
			S(int, k_replayHeld[k][2]) = 1;
	if (g_mouseClick) {
		SC->followNextAsked = 1;
		SC->manualPick[0] = 1;
	}
	if (g_rightClick) {
		SC->presetNextAsked = 1;
		SC->manualPick[1] = 1;
		SC->actionKey = 1;
	}
	for (int k = 0; k < 10; k++)
		if (input_justPressed(GAME_VAR(int, k_presetKeys[k]))) {
			SC->cameraMode = (k + 1) % 10;
			SC->manualPick[1] = 1;
			SC->actionKey = 1;
		}
	/* the follow keys (all ten read the same key; with 0x67ef24 the players 11 .. 16) */
	int follow = 0;
	for (int k = 1; k <= 10; k++)
		if (input_justPressed(g_dik1))
			follow = k <= 6 && input_justPressed(g_dikLShift) ? k + 10 : k;
	follow--;
	SC->replaySlow = input_isDown(g_dikSpace) ? 1 : 0;
	SC->replaySkip = input_isDown(g_dikEnter) ? 1 : 0;
	if (held2((OBJ(g_controls) + 0xe0), (OBJ(g_controls) + 0xe4)))
		SC->rankingKey = 1;
	if (input_justPressed(g_dikF11)) {
		const char *mode;
		if (SC->messagesHidden == 0) {
			SC->messagesHidden = 1;
			mode = (const char *)STR(0x4c7d00, "HIDDEN MESSAGE BOX MODE");
		} else if (SC->hudHidden == 0) {
			SC->hudHidden = 1;
			mode = (const char *)STR(0x4c7cf0, "SCREENSHOT MODE");
		} else {
			SC->messagesHidden = SC->hudHidden = 0;
			mode = (const char *)STR(0x4c7ce4, "NORMAL MODE");
		}
		notice_printCentre((Scene *)s, mode);
	}
	/* the mouse: its offset from the centre (y inverted with 0x4df000), scaled by the sensitivity, unless slow */
	SC->mouseX = g_mouseX;
	SC->mouseY = g_mouseY;
	if (!(SC->frameTime >= 0.2f)) {
		if (g_mouseInvert == 0)
			SC->mouseDy = f32((long double)(SC->mouseY - gfx_getHeight() / 2));
		else
			SC->mouseDy = f32(-(long double)(SC->mouseY - gfx_getHeight() / 2));
		SC->mouseDx = f32(-(long double)(SC->mouseX - gfx_getWidth() / 2));
	} else
		(*(int *)&SC->mouseDy) = (*(int *)&SC->mouseDx) = 0;
	long double sens = fmul_m((long double)g_mouseSensitivity, k_0_02f);
	sens = fmul_m(fadd_m(sens * sens, &k_1f), &k_0_5f);
	SC->mouseDy = f32(fmul_m(sens, &SC->mouseDy));
	SC->mouseDx = f32(fmul_m(sens, &SC->mouseDx));
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
	if (pressed2(ADDR(g_keyGameMenu), ADDR(g_keyGameMenu2)) && !(SC->keyGuard > 0)) {
		g_replayZoomIn = 0;
		SC->quitAsked = 1;
	}
	if (run_down(s, offsetof(Scene, msgFade)))
		SC->msgFade = 0.0f;
	if (run_down(s, offsetof(Scene, noticeTimer)))
		SC->noticeTimer = 0.0f;
	if (run_down(s, offsetof(Scene, flagUploadTimer))) {
		flag_uploadAtlas(stage);
		SC->flagUploadTimer = 0.0f;
	}
	long double sp = fmul_m(fld_m(&SC->frameTime), &k_2000f);   /* 2000 a second, at most +0x1f4164 */
	float speed = (float)sp;
	if (sp > SC->spaceMargin)
		BITS(speed) = BITS(SC->spaceMargin);
	float turn = f32(fmul_m(fmul_m(fmul_m((long double)view_angle(), &k_0_01666667f), &SC->frameTime), &k_50f));
	float step = f32(fmul_m(fld_m(&SC->frameTime), &k_180f));
	/* the zoom keys: the preset's distance by (1 - 0.9 dt) */
	if (SC->zoomInHeld == 1) {
		long double m = !(SC->frameTime >= 1.0f) ? fld_m(&SC->frameTime) : fld_m(&k_1f);
		float *z = (float *)&SC->cameraSettings[2][SC->cameraMode];
		*z = f32(fmul_m(fsubr_m(fmul_m(m, &k_0_9f), &k_1f), z));
	}
	if (SC->zoomOutHeld == 1) {
		long double m = !(SC->frameTime >= 1.0f) ? fld_m(&SC->frameTime) : fld_m(&k_1f);
		float *z = (float *)&SC->cameraSettings[2][SC->cameraMode];
		*z = f32(fdivr_m(fsubr_m(fmul_m(m, &k_0_9f), &k_1f), z));
	}
	if (SC->actionKey == 1)
		preset_reset(s);
	if (SC->playing == 0)
		free_keys(s, mv, &speed, &turn);
	else if (SC->playing == 1 && SC->cameraMode != 2) {
		int i = SC->cameraMode;
		*(float *)&SC->cameraSettings[1][i] = f32(fadd_m(fld_m(&SC->mouseDx), (const float *)&SC->cameraSettings[1][i]));
		i = SC->cameraMode;
		*(float *)&SC->cameraSettings[0][i] = f32(fadd_m(fld_m(&SC->mouseDy), (const float *)&SC->cameraSettings[0][i]));
	}
	zoom_view(s, &step);
	float dt;   /* slow motion: a twentieth */
	if (SC->replaySlow == 1)
		dt = f32(fmul_m(fld_m(&SC->frameTime), k_0_05f));
	else
		BITS(dt) = BITS(SC->frameTime);

	if (SC->scenePaused == 0) {
		if (!(SC->recordTime > SC->replayTime))
			do {
				int from, len;
				u8 packet[0x130];
				if (fread_scrambled(&SC->recordTime, 4, 1, SC->replayFile) == 0 || SC->replaySkip == 1) {
					if (replay_next(s))
						return 1;
					break;
				}
				fread_scrambled(&from, 4, 1, SC->replayFile);
				fread_scrambled(&len, 4, 1, SC->replayFile);
				fread_scrambled(packet, 1, len, SC->replayFile);
				net_processGamePacket(s, from, len, packet);
			} while (!(SC->recordTime > SC->replayTime));
		stage_advanceClocks(stage, BITS(dt));
		stage_updateObjects(stage, BITS(dt));
		actor_updateAll(stage, BITS(dt));
		bullet_updateAll(stage, BITS(dt));
		stage_updateEffects(stage, BITS(dt));
		item_update(stage, BITS(dt));
		choose_followed(s, follow);
		if (SC->manualPick[0] == 0)
			SC->followTime = f32(fadd_m(fld_m(&dt), &SC->followTime));
		if (SC->manualPick[1] == 0)
			SC->presetTime = f32(fadd_m(fld_m(&dt), &SC->presetTime));
		SC->replayTime = f32(fadd_m(fld_m(&dt), &SC->replayTime));
	}
	for (int i = 0; i < SC->playerCount; i++)
		if (SC->players[i].killPending == 1) {
			msg_kill(s, i, SC->players[i].lastAttacker);
			SC->players[i].killPending = 0;
		}
	events_age(s, BITS(SC->frameTime));
	if (SC->rankingKey == 1)
		SC->msgFade = 5.0f;   /* the ranking shown 5 s */

	/* the camera */
	SC->playing = SC->watchedPlayer >= 0;
	if (SC->playing == 0) {
		free_camera(s, mv, SC->holdAltitude ? OBJ(g_vecUnitY) : 0, &move);
		turn_view(s);
	} else {
		int i = SC->cameraMode;
		if (SC->cameraSettings[3][i] == 0 && i != 1) {
			orbit_camera(s, i);
			turn_view(s);
		} else {
			if (i == 1)
				pair_camera(s);
			else
				watch_camera(s);
			float *dir = SC->cameraDir, *up = SC->cameraUp;
			for (int k = 0; k < 3; k++)
				dir[k] = f32(fsub_m(fld_m(SC->cameraTarget + k), (const float *)SC->cameraPos + k));
			Vec3_normalize(dir);
			up[1] = 1.0f;
			up[0] = up[2] = 0;
		}
	}
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = view_angle();
	camera_setupView(stage, (float *)SC->cameraPos, SC->cameraDir,
	              SC->cameraUp, BITS(fov), w, h, BITS(near), BITS(far), BITS(SC->frameTime));   /* camera_setupView */
	SC->modeStarted++;

	/* the scene */
	tex_clearSetCounters(g_textures);
	if (SC->clearOn == 1) {
		glClearColor_stored(SC->clearColour);
		glClearDepth(1.0);
		glClear(0x4100);
	} else {
		glClearDepth(1.0);
		glClear(0x100);
	}
	gfx_setProjectionHud(1, 1.0f);
	u8 *view = SC->view;
	ViewVolume_captureMatrices(view, 0, SC->modelview);
	ViewVolume_reset(view);
	if (SC->playing == 1 && SC->cameraMode == 2 && SC->watchedPlayer >= 0)
		SC->players[SC->watchedPlayer].viewMarked = 1;   /* (the followed player seen from inside) */
	sky_draw((Stage *)stage, view_farPlane());
	ground_buildDrawLists(stage, view, view_farPlane());
	stage_drawObjects((Stage *)stage, view);
	stage_drawActors((Stage *)stage, view, -1);
	stage_drawBullets(stage, view);
	stage_drawParticles((Stage *)stage, view);
	stage_drawItems(stage, view);
	if (SC->debugPoints == 1)
		for (int i = 0; i < SCENE_STAGE(s)->mapLights.count; i++) {   /* (the map's lights: each a yellow star at its position) */
			const Factor *r = &SCENE_STAGE(s)->mapLights.records[i];
			if (r->used != 1)
				continue;
			float p[3], q[3];
			memcpy(p, r->pos, 12);
			for (int l = 0; l < 8; l++) {
				for (int k = 0; k < 3; k++)
					q[k] = f32(k_star[l][k] > 0 ? fadd_m(fld_m(&p[k]), &k_100f) : fsub_m(fld_m(&p[k]), &k_100f));
				ViewVolume_addSegment(view, (const void *)OBJ(g_packedYellow), p, q, 1);
			}
		}
	if (SC->fogOn == 1) {
		stage_setFog((Stage *)stage, st->glFogColour, st->glFogStart, st->glFogEnd, st->glFogDensity);
		glEnable(GL_FOG);
	}
	ViewVolume_draw(view, SC->renderMode, SC->clockFraction);
	glDisable(GL_FOG);
	gfx_setProjectionHud(0, 1.0f);

	/* the overlay */
	if (SC->hudHidden == 0) {
		char text[0xf0];
		/* (the patch DLL retargets these calls for wide screens) */
		PATCHED_THISCALL(0x48a19c, void, void *)(s);                                 /* hud_drawPlayerMarkers */
		if (SC->messagesHidden == 0 && SC->msgFade > 0)
			PATCHED_THISCALL(0x48a1c0, void, void *)(s);                             /* replay_drawMessage */
		if (SC->watchedPlayer >= 0) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			PATCHED_THISCALL(0x48a1f7, void, void *, int, int, int)(s, 0x10, 0x10, 6);   /* hud_drawIcon */
			text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
			int n = SC->cameraMode;
			sprintf(text, (const char *)STR(0x4b0320, "%d"), n > 0 ? n : n + 10);
			PATCHED_CALL(0x48a259, void, int, int, const char *, int)(0x28, 0x10, text, 0x10);   /* text_drawSized */
		}
		if (!(SC->secondFraction >= 0.5f)) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			PATCHED_THISCALL(0x48a299, void, void *, int, int, int)(s, 0x20e, 0x10, 5);   /* hud_drawIcon */
			text_setColor(1.0f, 1.0f, 1.0f, 1.0f);
			sprintf(text, (const char *)STR(0x4c7cd8, "%02d:%02d"), SC->wholeSeconds / 60, SC->wholeSeconds % 60);
			PATCHED_CALL(0x48a2ff, void, int, int, const char *, int)(0x226, 0x10, text, 0x10);   /* text_drawSized */
		}
		PATCHED_THISCALL(0x48a309, void, void *)(s);                                 /* hud_drawWatchedName */
		if (SC->rankingKey == 1)
			PATCHED_THISCALL(0x48a318, void, void *)(s);                             /* hud_drawRanking */
	}
	if (SC->noticeTimer > 0)
		hud_drawCentreNotice((Scene *)s);
	if (SC->quitAsked != 1)
		return 4;
	fclose(SC->replayFile);
	music_shutdown();
	return 0;
}

/* ---- 0x4988e0: the match's frame ---- */


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
	static const char *const k_teams[3] = { (const char *)STR(0x4b21b8, "RED"), (const char *)STR(0x4b21b0, "BLUE"), (const char *)STR(0x4d06ec, "NOTEAM") };   /* NOTEAM */
	void *f = crt_fopen((const char *)STR(0x4d06e0, "axiswl.log"), (const char *)STR(0x4b21a4, "wt"));
	crt_fprintf(f, format, g_mapTitle, g_missionStage, g_fragLimit, g_timeLimit, g_matchPlayerName);
	for (int k = 0; k < SC->rankCount; k++) {
		int e = SC->ranking[k];
		int team = team_game() ? SC->players[e].team : 2;
		char name[64];
		memset(name, 0, sizeof name);
		strcpy(name, ((Player *)ACTOR_AT(e))->name);
		crt_fprintf(f, (const char *)STR(0x4d062c, "ID:%s Team:%s PlayTime:%d Kill:%d Dea..."), name, k_teams[team], own_time ? SC->players[e].timePlayed : stack_time,
		            SC->players[e].kills, SC->players[e].deaths);
	}
	fclose(f);
}

/* a free spawn point (+0x22ee23c, 0x14 bytes each, +0x22ee4bc of them) from a random one on: the first no live
   actor stands within reach of (the reach: its height times 5, or twice it); NULL when there are none */
static const u8 *spawn_point(u8 *s, int doubled)
{
	int n = SC->spawnPointCount;
	if (n <= 0)
		return NULL;
	u32 r = rand_below(n);
	int left = SC->spawnPointCount - 1;
	for (;;) {
		int taken = 0;
		for (int j = 0; j < SC->playerCount; j++) {
			if (SC->players[j].state != 1)
				continue;
			const float *pos = ((Player *)ACTOR_AT(j))->pos, *at = SC->spawnPoints[r].pos;
			float d[3];
			for (int k = 0; k < 3; k++)
				d[k] = f32(fsub_m(fld_m(&pos[k]), &at[k]));
			long double reach = doubled ? fld_m(&((Player *)ACTOR_AT(j))->radius) * 2 : fmul_m(fld_m(&((Player *)ACTOR_AT(j))->radius), &k_5f);
			long double dist = fmul_m(fld_m(&d[2]), &d[2]) + fmul_m(fld_m(&d[1]), &d[1]);
			dist = dist + fmul_m(fld_m(&d[0]), &d[0]);
			if (reach * reach > dist) {
				taken = 1;
				break;
			}
		}
		if (!taken)
			break;
		r = (int)(r + 1) % SC->spawnPointCount;
		if (left-- < 0)
			break;
	}
	return (u8 *)&SC->spawnPoints[r];
}

/* the five parts of actor p in team colours (by its team's side) */
static void team_colours(u8 *s, int p, int team)
{
	int side = scene_teamSide((Scene *)s, team);
	for (int part = 0; part < 5; part++)
		actor_setPartColor_bits((u8 *)SCENE_STAGE(s), p, part, GAME_VAR(u32, 0x4a97fc + side * 4), GAME_VAR(u32, 0x4a9810 + side * 4),
		                        GAME_VAR(u32, 0x4a9824 + side * 4), 0, 0xbf800000, 0x3f7fbe77);
}

/* the local player (+0x234240d) into the match: its record (+0x2342429 ..), colours, a spawn point, the notice */
static void local_spawn(u8 *s)
{
	if (SC->localRecordSet == 0) {
		playerRecord_set((u8 *)SCENE_STAGE(s), SC->localPlayer, (const char *)SC->mechName, (*(u32 *)&SC->pilotLevel), (*(u32 *)&SC->localTeam), (*(u32 *)&SC->mechParts[0]),
		             (*(u32 *)&SC->mechParts[1]), (*(u32 *)&SC->mechParts[2]), (*(u32 *)&SC->mechParts[3]), (*(u32 *)&SC->mechParts[4]), (*(u32 *)&SC->mechItems[0]), (*(u32 *)&SC->mechItems[1]),
		             (*(u32 *)&SC->mechItems[2]), (*(u32 *)&SC->mechItems[3]), (*(u32 *)&SC->mechItems[4]), (*(u32 *)&SC->mechItems[5]));
		SC->localRecordSet = 1;
	}
	if (SC->teamGame == 1)
		team_colours(s, SC->localPlayer, SC->localTeam);
	else if (SC->players[SC->localPlayer].inPlay == 0)
		for (int part = 0; part < 5; part++) {
			float (*c)[5][2] = SC->mechColours;
			actor_setPartColor_bits((u8 *)SCENE_STAGE(s), SC->localPlayer, part, BITS(c[0][part][0]), BITS(c[1][part][0]), BITS(c[2][part][0]),
			                        BITS(c[0][part][1]), BITS(c[1][part][1]), BITS(c[2][part][1]));
		}
	u32 rec[7];   /* the actor, 0, the position, the pitch and heading */
	const u8 *at = spawn_point(s, 0);
	rec[0] = (*(u32 *)&SC->localPlayer);
	rec[1] = 0;
	if (at) {
		memcpy(rec + 2, at, 12);
		float pitch = (float)fld_m(&((const StartPoint *)at)->angle[0]), heading = (float)fld_m(&((const StartPoint *)at)->angle[1]);
		rec[5] = BITS(pitch);
		rec[6] = BITS(heading);
	} else {
		memcpy(rec + 2, SC->cameraSaved, 12);
		float pitch = (float)fld_m((const float *)&SC->cameraSaved[3]), heading = (float)fld_m((const float *)&SC->cameraSaved[4]);
		rec[5] = BITS(pitch);
		rec[6] = BITS(heading);
	}
	stage_claimPlayerActor(SCENE_STAGE(s), rec[0], -1, rec[0], rec);
	if (SC->recording == 1)
		SC->sendFlags[SC->localPlayer][1] = 1;
	SC->playing = 1;
	notice_printCentre((Scene *)s, (const char *)STR(0x4d0618, "PREPARE THE BATTLE"));
	SC->startCount = 3.0f;   /* 3 */
	SC->startCountShown = -1;
	scene_updateRanking((Scene *)s);
	SC->actionKey = 1;
	SC->spawnPending = 0;
}

/* the bots (the map's actors that are bots, mapActorCount records) waiting to spawn: placed on a free point */
static void bot_spawns(u8 *s)
{
	for (int j = 0; j < SC->mapActorCount; j++) {
		const SpawnRecord *rec = &SCENE_STAGE(s)->mapActors[j];
		int state = SC->players[j].active;
		if (rec->bot != 1 || !(state == 0 || (state == 1 && SC->players[j].state == 3)))
			continue;
		PlayerRecord *player = &SC->playerRecords[rec->player];
		if (SC->teamGame == 1)
			team_colours(s, rec->player, player->team);
		u32 copy[0x17];
		memcpy(copy, rec, 0x5c);
		const u8 *at = spawn_point(s, 1);
		memcpy(copy + 1, at ? at : (const u8 *)SC->cameraSaved, 12);
		actor_applySpawnRecord((u8 *)SCENE_STAGE(s), j, copy);
		if (SC->players[j].inPlay == 0)
			msg_playerJoinedTeam((Scene *)s, GAME_VAR(int, rec), player->team);
	}
}

/* the camera looking back at the actor t's killer (+0x4c0) from 2 heights behind its head (+0x4e0) */
static void killer_view(u8 *s, const u8 *t)
{
	Player *act = (Player *)t;
	float *cam = (float *)SC->cameraPos, *head = (float *)((const Player *)t)->deathPos, d[3], p[3];
	int k = act->lastAttacker;
	for (int j = 0; j < 3; j++)
		d[j] = f32(fsub_m(fld_m(&((Player *)ACTOR_AT(k))->pos[j]), &head[j]));
	Vec3_normalize(d);
	long double r = fmul_m(fld_m(&((const Player *)t)->radius), &k_m2f);   /* -2 heights */
	for (int j = 0; j < 3; j++)
		p[j] = f32(fmul_m(r, &d[j]));
	for (int j = 0; j < 3; j++)
		p[j] = f32(fadd_m(fld_m(&p[j]), &head[j]));
	if (collision_rayTrace((u8 *)SCENE_STAGE(s), head, p, cam) == 0)
		memcpy(cam, p, 12);
	for (int j = 0; j < 3; j++)
		d[j] = f32(fsub_m(fld_m(&cam[j]), &head[j]));
	if (Vec3_normalize(d) > 300.0f) {
		long double dx = fmul_m(fld_m(&d[0]), &k_300f);
		float dy = f32(fmul_m(fld_m(&d[1]), &k_300f)), dz = f32(fmul_m(fld_m(&d[2]), &k_300f));
		cam[0] = f32(fld_m(&cam[0]) - dx);
		cam[1] = f32(fsub_m(fld_m(&cam[1]), &dy));
		cam[2] = f32(fsub_m(fld_m(&cam[2]), &dz));
	}
	look_toward(s, ((Player *)ACTOR_AT(act->lastAttacker))->pos);
	for (int j = 0; j < 3; j++)
		SC->cameraDir[j] = f32(fsub_m(fld_m(SC->cameraTarget + j), &cam[j]));
}

/* the camera looking at the look point, which moves half way to p */
static void look_at(u8 *s, const float *p)
{
	float *dir = SC->cameraDir, *up = SC->cameraUp;
	look_toward(s, p);
	for (int k = 0; k < 3; k++)
		dir[k] = f32(fsub_m(fld_m(SC->cameraTarget + k), (const float *)SC->cameraPos + k));
	Vec3_normalize(dir);
	up[0] = 0;
	up[1] = 1.0f;
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
	Player *act = (Player *)t;
	const PlayerRecord *pr = &SC->playerRecords[act->player];
	int slot = act->slot;
	const ArmType *arms = &SCENE_STAGE(s)->armTypes[pr->parts[2]];
	ActorInfo *item = (ActorInfo *)((u8 *)&SCENE_STAGE(s)->actorInfo[pr->items[slot]]);
	float P[3], E[3] = { 0, 0, 0 };
	const float *v, *m;
	int bone;
	if (slot == 4) {
		v = item->sets[0].muzzle[act->variantLoaded];
		bone = arms->weaponJoints[1][act->lowDetail];
	} else if (slot == 5) {
		v = item->sets[1].muzzle[act->variantLoaded];
		bone = arms->weaponJoints[2][act->lowDetail];
	} else {
		v = item->sets[0].muzzle[act->variantLoaded];
		bone = arms->weaponJoints[0][act->lowDetail];
	}
	m = (const float *)((u8 *)act->armsModel.entries + bone * 100 + 0xc);
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
	E[1] = f32(fmul_m(fld_m(&act->radius), k_0_3f));   /* 0.3 */
	Vec3_rotateAxis(E, 1, ftol(fld_m(SC->cameraAngle)));
	Vec3_rotateAxis(E, 2, ftol(fld_m(&SC->cameraAngle[1])));
	for (int k = 0; k < 3; k++)
		E[k] = f32(fadd_m(fld_m(&E[k]), &act->pos[k]));
	float f;
	BITS(f) = BITS(act->weaponLower);
	long double dx = fsub_m(fld_m(&P[0]), &E[0]);
	float dy = f32(fsub_m(fld_m(&P[1]), &E[1])), dz = f32(fsub_m(fld_m(&P[2]), &E[2]));
	long double hx = fmul_m(dx, &f);
	float hy = f32(fmul_m(fld_m(&dy), &f)), hz = f32(fmul_m(fld_m(&dz), &f));
	float *cam = (float *)SC->cameraPos, *dir = SC->cameraDir;
	cam[0] = f32(fadd_m(hx, &E[0]));
	cam[1] = f32(fadd_m(fld_m(&hy), &E[1]));
	cam[2] = f32(fadd_m(fld_m(&hz), &E[2]));
	dir[0] = dir[1] = 0;
	dir[2] = 1.0f;
}

/* the round's slow motion: the last two seconds of a won round's end (+0x2342399) when the last to die (lastDeath) is
   down (state 2), unless the time ran out */
static int slow_end(u8 *s)
{
	if (SC->matchOver != 1)
		return 0;
	if (SC->timeLimit > 0 && SC->elapsed >= SC->timeLimit * 60)
		return 0;
	if (!(fsub_m(fld_m(&k_10f), &SC->endTime) < 2.0f))
		return 0;
	return SC->lastDeath >= 0 && SC->players[SC->lastDeath].state == 2;
}

/* the winning team (+0x23423bd): the side whose team slot has more (team scores +0x2221fb8), -1 for a draw */
static void winning_team(u8 *s)
{
	int a = scene_teamIdAt((Scene *)s, 1), b = scene_teamIdAt((Scene *)s, 0);
	if (SC->teamScores[b] > SC->teamScores[a]) {
		SC->winnerTeam = scene_teamIdAt((Scene *)s, 0);
		return;
	}
	a = scene_teamIdAt((Scene *)s, 1);
	b = scene_teamIdAt((Scene *)s, 0);
	if (SC->teamScores[b] < SC->teamScores[a])
		SC->winnerTeam = scene_teamIdAt((Scene *)s, 1);
	else
		SC->winnerTeam = -1;
}

/* the round over (10 s of end, +0x234239d): the notice (frag or time limit), the log written later */
static void round_over(u8 *s, int time_limit)
{
	SC->botsHoldFire = 1;
	SC->matchOver = 1;
	SC->endTime = 10.0f;   /* 10 */
	SC->playing = 1;
	music_shutdown();
	if (time_limit)
		msg_timeLimitReached(s);
	else
		msg_fragLimitReached(s);
	SC->endedByTime = time_limit;
	SC->endNoticeTime = 0.0f;
	g_writeMatchLog = 1;
}

/* the local player's camera chat keys: T (all, +0x23432fb) / Y (team, +0x23432ff) open the line, its end sends it
   (a cheat code, a macro or the text) */
static void chat_keys(u8 *s)
{
	char line[0x100];
	int me = SC->localPlayer, mode = SC->chatMode;
	if (mode == 0) {
		if (SC->talkPressed == 1) {
			SC->chatMode = 1;
			chat_textField(0, 0, 0x38);
			SC->players[SC->localPlayer].chatIcon = 1;
		} else if (SC->teamTalkPressed == 1) {
			SC->chatMode = 2;
			chat_textField(0, 0, 0x38);
			SC->players[SC->localPlayer].chatIcon = 2;
		}
		return;
	}
	if ((mode != 1 && mode != 2) || g_textFieldOpen != 0)
		return;
	SC->chatMode = 0;
	chat_keepLastLine();
	const char *typed = (const char *)ADDR(g_keptChatLine);
	(void)me;
	if (strlen(typed) != 0) {
		int code = mode == 1 ? chat_matchCheatCode(s, SC->localPlayer, typed) : -1;
		if (code >= 0) {
			msg_cheatUsed(s, SC->localPlayer, code);
			recorder_openStub(s, (void *)SC->localPlayer, (const void *)RELOC(code));
		} else {
			int r = chat_macro(s, typed, line);
			if (r == 0)
				strcpy(line, typed);
			if (r == 0 || r == 1) {
				int team = mode == 1 ? -1 : SC->localTeam;
				msg_chatLine(s, SC->localPlayer, line, team);
				team = mode == 1 ? -1 : SC->localTeam;
				net_announceChatLine(s, SC->localPlayer, line, team);
			}
		}
	}
	SC->players[SC->localPlayer].chatIcon = 0;
}

/* 0x4988e0 (thiscall on the game object): the match's frame. The log of the last match written when asked
   (0x9f67ec); nothing more until the match runs (+0x233c9e8). Then: the Esc menu and quitting, the local player
   joining (the network's slot, its name and record), its team or spawn, the bots' spawns, the free camera's keys
   or the player's own (actor_setInput), the view angle, the network's packets, the scene's frame (slowed at a round's
   end), the followed player when spectating, kill messages, the notices and countdowns, the network's per-player
   updates, the round's end (frag or time limit) and the next round or map, the camera (spectating: free, one of
   the presets about the followed player or its killer; playing: the presets, the muzzle or the killer), the chat
   keys, the connection checks and the match's end (the log, back to the menu) */
void THISCALL (match_frame)(u8 *s)
{
	Scene *sc = (Scene *)s;
	u8 *stage = (u8 *)SCENE_STAGE(s);
	Stage *st = (Stage *)stage;
	float mv[3];        /* the free camera's move (its keys may not have run: the original's stack then) */
	Move move;          /* (the stubbed move may leave these as the stack had them) */
	int from, size;     /* the network packet's sender and size, as the reader leaves them; the opening log's play
	                       time reads the sender's slot before it is ever written, as the original does */
	u8 packet[0x130];
	if (g_writeMatchLog != 0 && g_startedFromLobby != 0) {
		write_log(s, (const char *)(SC->rankCount > 1 ? STR(0x4d0658, "GameTitle %s\nMapNo %d\nFragLimit %d\nTi...") : STR(0x4d069c, "GameTitle %s\nMapNo %d\nFragLimit %d\nTi...")), 0, *(volatile int *)&from);
		g_writeMatchLog = 0;
		g_matchLogWritten = 1;
	}
	if (SC->matchDrawing == 0) {
		SC->matchState = 1;
		SC->modeStarted = 0;
		return;
	}
	if (SC->helpPressed == 1)
		SC->helpOpen ^= 1;
	if (SC->quitAsked == 1) {
		if (SC->helpOpen == 1)
			SC->helpOpen = SC->quitAsked = 0;
	} else if (SC->helpOpen == 1 && SC->firePressed == 1)
		SC->helpOpen = 0;
	/* the Esc menu, quitting */
	int quit_check = 1;
	if (SC->escMenuOpen == 1)
		match_escMenu(s);
	else if (SC->quitAsked == 1) {
		if (SC->matchLeaving == 0) {
			sound_playVolume(9, 100);
			if (SC->localAlive == 0 || (SC->sessionMode == 0 && SC->teamAsked == 1 && SC->players[SC->localPlayer].inPlay == 0)) {
				SC->rankingShown = 0;
				SC->localAlive = 1;
			}
			escMenu_open((Scene *)s, 0, SC->players[SC->localPlayer].inPlay == 0 ? 0 : 4);
			SC->quitAsked = 0;
		}
	} else
		quit_check = 0;
	if (quit_check && SC->quitAsked == 1) {
		if (SC->client == 0) {
			if (SC->matchLeaving == 0) {
				SC->matchLeaving = 1;
				SC->quitDelay = 3.0f;
				music_shutdown();
				if (SC->sessionMode == 0) {
					msg_userEndsGame(s);
					g_matchEndedByUser = 1;
				} else {
					msg_serverEndsGame(s);
					net_announceServerEnd(s);
					SC->endedByTime = 2;
					SC->endNoticeTime = 0.0f;
					g_matchEndedByUser = 1;
				}
			}
		} else {
			SC->matchLeaving = 1;
			SC->quitDelay = 0.0f;
			music_shutdown();
			if (SC->localPlayer >= 0)
				net_announcePlayerQuit(s, SC->localPlayer);
			g_matchEndedByUser = 0;
		}
		SC->quitAsked = 0;
	}
	/* the local player's starting grade and score; its flag loaded (network games) */
	if (SC->localPlayer >= 0 && SC->statsTaken == 0) {
		SC->players[SC->localPlayer].grade = SC->level;
		SC->players[SC->localPlayer].levelShown = SC->level;
		SC->players[SC->localPlayer].score = SC->levelPoints;
		SC->players[SC->localPlayer].startPoints = SC->levelPoints;
		SC->statsTaken = 1;
	}
	if (SC->flagLoaded == 0 && SC->localPlayer >= 0 && SC->sessionMode == 1) {
		int loaded = playerRecord_loadFlag(stage, SC->localPlayer);
		SC->playerRecords[SC->localPlayer].flagChanged = loaded;
		SC->playerRecords[SC->localPlayer].flagSent = 0;
		SC->flagUploadTimer = 5.0f;   /* 5 */
		SC->flagLoaded = 1;
	} else if (run_down(s, offsetof(Scene, flagUploadTimer))) {
		flag_uploadAtlas(stage);
		SC->flagUploadTimer = 0.0f;
	}
	/* joining: the network's slot for the local player */
	if (SC->localPlayer < 0 && net_isClient()) {
		PATCHED_THISCALL(0x498dd8, u32, void *, const char *)(stage, g_catalogueFile);   /* catalogue_loadComponents */
		SC->localPlayer = net_localSlot();
		actor_resetSlot((Stage *)stage, SC->localPlayer);
		player_setName((Stage *)stage, SC->localPlayer, (const char *)SC->mechName);
		strcpy(((Player *)ACTOR_AT(SC->localPlayer))->name, (const char *)SC->mechName);
		SC->players[SC->localPlayer].player = SC->localPlayer;
		msg_playerConnected(s, SC->localPlayer);
		net_announcePlayerConnected(s, SC->localPlayer, (u8 *)&SC->playerRecords[SC->localPlayer] + 4);
		net_sendMatchEvent(s);
	}
	/* a team chosen (or a menu for it), then the spawn */
	int me = SC->localPlayer;
	if (me >= 0 && SC->players[me].active == 0 && SC->matchOver == 0 && SC->playerRecords[me].flagSent == 0x180
	    && (SC->firePressed == 1 || SC->teamAsked == 1)) {
		if (SC->teamGame == 1 && (SC->localTeam < 0 || scene_findTeam((Scene *)s, SC->localTeam) < 0)) {
			if (SC->chosenTeam >= 0 && SC->sessionMode != 0)
				escMenu_open((Scene *)s, 1, scene_teamSide((Scene *)s, SC->chosenTeam) == 0 ? 0 : 1);
			else
				escMenu_open((Scene *)s, 1, SC->redTeamCount > SC->blueTeamCount ? 1 : 0);
		} else {
			if (SC->localTeam < 0) {
				scene_setLocalTeam((Scene *)s, SC->localPlayer);
				msg_playerJoinedTeam((Scene *)s, SC->localPlayer, SC->localTeam);
				net_announceJoinedTeam((Scene *)s, SC->localPlayer, SC->localTeam, (const char *)SC->mechName);
			}
			SC->spawnPending = 1;
		}
		SC->teamAsked = 0;
	}
	me = SC->localPlayer;
	if (me >= 0 && SC->localTeam >= 0 && SC->players[me].active == 0 && SC->chatMode == 0 && SC->matchOver == 0
	    && SC->matchLeaving == 0) {
		long double v = fadd_m(fld_m(&SC->frameTime), &SC->respawnTime);
		SC->respawnTime = (float)v;
		if (!(v < 10.0f)) {   /* respawn after 10 s */
			SC->respawnTime = 0.0f;
			SC->spawnPending = 1;
		}
	} else
		SC->respawnTime = 0.0f;
	if (SC->spawnPending == 1
	    || (SC->platoon == 1 && SC->players[SC->localPlayer].state == 3 && SC->players[SC->localPlayer].isCommander == 1))
		local_spawn(s);
	if (SC->sessionMode == 0 && SC->localPlayer >= 0 && SC->players[SC->localPlayer].inPlay == 1 && SC->matchOver == 0)
		bot_spawns(s);
	stage_selectActor((Stage *)stage, SC->playing == 1 && SC->cameraMode == 1 ? SC->localPlayer : -1);
	/* the keys' rates */
	long double sp = fmul_m(fld_m(&SC->frameTime), &k_2000f);
	float speed = (float)sp;
	if (sp > SC->spaceMargin)
		BITS(speed) = BITS(SC->spaceMargin);
	float turn = f32(fmul_m(fmul_m(fmul_m((long double)view_angle(), &k_0_01666667f), &SC->frameTime), &k_75f));
	float step = f32(fmul_m(fld_m(&SC->frameTime), &k_180f));
	if (SC->actionKey == 1)
		for (int k = 0; k < 10; k++)
			for (int f = 0; f < 6; f++)
				SC->cameraSettings[f][k] = SC->cameraPresets[f][k];
	if (SC->playing == 0) {
		if (SC->cameraSlot >= 0 && SC->watchedPlayer >= 0) {
			int i = SC->cameraSlot;
			if (i != 2) {
				*(float *)&SC->cameraSettings[1][i] = f32(fadd_m(fld_m(&SC->mouseDx), (const float *)&SC->cameraSettings[1][i]));
				i = SC->cameraSlot;
				*(float *)&SC->cameraSettings[0][i] = f32(fadd_m(fld_m(&SC->mouseDy), (const float *)&SC->cameraSettings[0][i]));
			}
		} else
			free_keys(s, mv, &speed, &turn);
	} else if (SC->playing == 1 && (SC->sessionMode == 0 || net_isClient())) {
		if (SC->matchOver == 1 || SC->matchLeaving == 1) {
			if (SC->matchOver == 1 && SC->ranking[0] != SC->localPlayer) {   /* the round's end: the camera turns */
				float *v = (float *)&SC->cameraSettings[0][SC->cameraMode];
				*v = f32(fsubr_m(fmul_m(fld_m(&turn), &SC->mouseDy), v));
				v = (float *)&SC->cameraSettings[1][SC->cameraMode];
				*v = f32(fsubr_m(fmul_m(fld_m(&turn), &SC->mouseDx), v));
			}
			SC->holdFire = 0;
			SC->weaponKey = -1;
			SC->prevWeaponPressed = 0;
			SC->nextWeaponPressed = 0;
		}
		if (SC->holdUp == 1) {
			SC->holdAltitude = SC->holdForward = 1;
			SC->holdBackward = 0;
		}
		if (SC->holdDown == 1) {
			SC->holdAltitude = SC->holdBackward = 1;
			SC->holdForward = 0;
		}
		float pitch = f32(fmul_m(fld_m(&turn), &SC->mouseDy)), yaw = f32(fmul_m(fld_m(&turn), &SC->mouseDx));
		actor_setInput(stage, (*(u32 *)&SC->localPlayer), (*(u32 *)&SC->holdForward), (*(u32 *)&SC->holdBackward), (*(u32 *)&SC->holdStepLeft), (*(u32 *)&SC->holdStepRight), BITS(pitch),
		             BITS(yaw), (*(u32 *)&SC->holdFire), (*(u32 *)&SC->holdAltitude), (*(u32 *)&SC->holdBooster), (*(u32 *)&SC->weaponKey), (*(u32 *)&SC->prevWeaponPressed), (*(u32 *)&SC->nextWeaponPressed));
	}
	zoom_view(s, &step);
	/* the network's packets */
	SC->windowSent += SC->packetsSent;
	SC->windowReceived += SC->packetsReceived;
	SC->packetsSent = SC->packetsReceived = 0;
	if (SC->matchLeaving == 0) {
		netq_poll();
		for (int r = netq_receive(&from, &size, packet); r != 0; r = netq_receive(&from, &size, packet)) {
			if (r == 1)
				net_processGamePacket(s, from, size, packet);
			SC->packetsReceived++;
			netq_poll();
		}
	}
	if (SC->matchState == 1)
		return;
	/* the scene's frame */
	float dt;
	if (slow_end(s))
		dt = f32(fmul_m(fld_m(&SC->frameTime), k_0_05f));
	else
		BITS(dt) = BITS(SC->frameTime);
	if (SC->scenePaused == 0 && !(SC->escMenuOpen == 1 && SC->sessionMode == 0)) {
		if (SC->playing == 0 && SC->cameraSlot == 2 && SC->watchedPlayer >= 0)
			SC->players[SC->watchedPlayer].viewMarked = 1;
		else if (SC->playing == 1 && SC->cameraMode == 2 && SC->localPlayer >= 0)
			SC->players[SC->localPlayer].viewMarked = 1;
		stage_advanceClocks(stage, BITS(dt));
		actor_updateAll(stage, BITS(dt));
		if (SC->matchOver == 1 || SC->matchLeaving == 1)
			stage_clearBullets(stage);
		bullet_updateAll(stage, BITS(dt));
		stage_updateEffects(stage, BITS(dt));
		item_update(stage, BITS(dt));
		stage_refillLights(stage);
		stage_updateObjects(stage, BITS(dt));
		stage_advanceScenePath(stage, BITS(dt));
		if (SC->sessionMode == 1) {   /* the server checks the local player's parts every 20 s */
			long double v = fsub_m(fld_m(&SC->partsCheckTime), &SC->frameTime);
			SC->partsCheckTime = (float)v;
			if (!(v >= 0) && SC->localPlayer >= 0 && SC->players[SC->localPlayer].state == 1) {
				if (actor_checkDataLoss(stage, SC->localPlayer) == 0) {
					SC->dataLossPending = 1;
					SC->dataLossCode = 0;
				}
				SC->partsCheckTime = 20.0f;   /* 20 */
			}
			if (SC->dataLossPending == 1) {
				msg_dataLoss(s);
				SC->matchLeaving = 1;
				SC->quitDelay = 3.0f;
				music_shutdown();
				SC->dataLossPending = 0;
			}
		}
		if (SC->playing == 0) {   /* spectating: the followed player */
			if (SC->watchedPlayer >= 0 && SC->players[SC->watchedPlayer].team < 0)
				SC->watchedPlayer = -1;
			int f = SC->followKey, n = SC->playerCount;
			if (f >= 0) {
				if (SC->players[f].team >= 0) {
					if (SC->cameraSlot < 0)
						SC->cameraSlot = 1;
					SC->watchedPlayer = f;
					SC->followTime = 0.0f;
					SC->manualPick[0] = 1;
				}
			} else if (n > 0 && (SC->followNextAsked == 1 || SC->followTime > 14.0f)) {
				int cur = SC->watchedPlayer, next = cur + 1;
				if (next == n) {
					SC->watchedPlayer = -1;
					start_view(s);
				} else
					for (;;) {
						if (SC->players[next].team >= 0) {
							if (SC->cameraSlot < 0)
								SC->cameraSlot = 1;
							SC->watchedPlayer = next;
							SC->followTime = 0.0f;
							break;
						}
						if (++next >= n) {
							SC->watchedPlayer = -1;
							start_view(s);
							break;
						}
						if (next == cur)
							break;
					}
			}
			if (SC->watchedPlayer >= 0) {
				if (SC->presetNextAsked == 1)
					SC->cameraSlot = (SC->cameraSlot + 1) % 10;
				else if (SC->presetTime > 7.0f) {
					u32 r = rand_below(100);
					SC->cameraSlot = r < 5 ? 0 : r < 35 ? 1 : r < 45 ? 2 : r < 50 ? 3 : r < 55 ? 4 : r < 60 ? 5 : r < 65 ? 6 : r < 70 ? 7 : 8 + (r >= 75);
					SC->presetTime = 0.0f;
				}
			}
			if (SC->manualPick[0] == 0)
				SC->followTime = f32(fadd_m(fld_m(&SC->followTime), &SC->frameTime));
			if (SC->manualPick[1] == 0)
				SC->presetTime = f32(fadd_m(fld_m(&SC->frameTime), &SC->presetTime));
		}
	}
	for (int i = 0; i < SC->playerCount; i++)
		if (SC->players[i].killPending == 1) {
			msg_kill(s, i, SC->players[i].lastAttacker);
			SC->players[i].killPending = 0;
		}
	events_age(s, BITS(SC->frameTime));
	if (SC->rankingKey == 1)
		SC->msgFade = 5.0f;
	me = SC->localPlayer;
	if (me >= 0 && SC->players[me].state == 1 && !(((Player *)ACTOR_AT(me))->messageTime < 0) && !(((Player *)ACTOR_AT(me))->messageTime > 0))
		notice_printCentre((Scene *)s, ((Player *)ACTOR_AT(me))->message);   /* (its own text as the format) */
	/* the start count (3, 2, 1, go) */
	if (SC->startCount > 0) {
		long double v = fsub_m(fld_m(&SC->startCount), &SC->frameTime);
		SC->startCount = (float)v;
		if (!(v >= 0)) {
			SC->startCount = 0.0f;
			notice_printCentre((Scene *)s, (const char *)STR(0x4d0610, "FIGHT!"));
			sound_playVolume(0x17, 100);
		} else {
			int n = ftol(v);
			if (SC->startCountShown != n) {
				SC->startCountShown = n;
				if (n == 0)
					notice_printCentre((Scene *)s, (const char *)STR(0x4d05f8, "HANA!"));
				else if (n == 1)
					notice_printCentre((Scene *)s, (const char *)STR(0x4d0600, "DOOL!"));
				else if (n == 2)
					notice_printCentre((Scene *)s, (const char *)STR(0x4d0608, "SET!"));
				sound_playVolume(9, 100);
			}
		}
	}
	if (SC->ladderGame == 1 && SC->localPlayer >= 0) {
		me = SC->localPlayer;
		int a = SC->players[me].grade;
		if (a != SC->players[me].levelShown) {
			SC->players[me].levelShown = a;
			notice_printCentre((Scene *)s, (const char *)STR(0x4d05ec, "LEVEL UP!"));
			sound_playVolume(0x18, 100);
		}
	}
	if ((*(u8 *)&SC->centreNotice[0])) {
		notice_printCentre((Scene *)s, (const char *)SC->centreNotice);
		(*(u8 *)&SC->centreNotice[0]) = 0;
	}
	if (SC->teamsChanged == 1 || !(SC->rankingTimer > 0)) {
		scene_updateRanking(sc);
		if (net_playerInUse(SC->localPlayer) == 1 && SC->rank[SC->localPlayer] == 1
		    && (SC->rankShown > 1 || (SC->kingOfTheHill == 1 && SC->rankShown != 1)))
			sound_playVolume(0xf, 100);
		SC->teamsChanged = 0;
		SC->rankingTimer = 5.0f;
	}
	if (SC->recording == 1)
		SC->recordTime = f32(fadd_m(fld_m(&SC->frameTime), &SC->recordTime));
	/* the network's per-player updates */
	if (SC->localPlayer >= 0) {
		long double v = fsub_m(fld_m(&SC->stateSendTimer), &SC->frameTime);
		SC->stateSendTimer = (float)v;
		if (!(v > 0)) {
			SC->sendFlags[SC->localPlayer][0] = 1;
			SC->stateSendTimer = 3.0f;
		}
		if (SC->players[SC->localPlayer].team >= 0) {
			v = fsub_m(fld_m(&SC->infoSendTimer), &SC->frameTime);
			SC->infoSendTimer = (float)v;
			if (!(v > 0)) {
				SC->sendFlags[SC->localPlayer][1] = 1;
				SC->infoSendTimer = 15.0f;   /* 15 */
			}
		}
		if (SC->announcePending == 1)
			do
				net_sendMatchEvent(s);
			while (SC->announcePending == 1);
		for (int i = 0; i < 16; i++) {
			if (SC->sendFlags[i][0] == 1)
				net_sendGamePacket(s, i);
			if (SC->sendFlags[i][1] == 1)
				net_sendPlayerInfo(s, i);
			if (net_playerInUse(i) == 1 && SC->sendTimer > 0.05f && SC->playerRecords[SC->localPlayer].flagSent < 0x180) {
				net_sendFlagPiece(s, SC->localPlayer);
				SC->sendTimer = (float)-fld_m(&SC->frameTime);
			}
			if (net_playerInUse(i) == 1 && SC->players[i].active == 1 && SC->players[i].controlledBy == SC->localPlayer
			    && (SC->sendTimer > 0.05f || SC->players[i].firing == 1
			        || (!(SC->players[i].messageTime < 0) && !(SC->players[i].messageTime > 0))
			        || SC->players[i].sendNow == 1)) {
				net_sendPlayerState(s, i);
				SC->sendTimer = (float)-fld_m(&SC->frameTime);
			}
		}
		SC->sendTimer = f32(fadd_m(fld_m(&SC->sendTimer), &SC->frameTime));
	}
	/* the round's end */
	if (SC->endTime > 0) {
		PATCHED_THISCALL(0x49a54f, u32, void *, const char *)(stage, g_catalogueFile);   /* catalogue_loadComponents */
		if (SC->sessionMode == 1 && SC->client == 0) {   /* the server's end notices, every half second */
			if (SC->endNoticeTime > 0.5f) {
				SC->endNoticeTime = 0.0f;
				int k = SC->endedByTime;
				if (k == 0)
					net_announceFragLimit(s);
				else if (k == 1)
					net_announceTimeLimit(s);
				else if (k == 2)
					net_announceServerEnd(s);
			} else
				SC->endNoticeTime = f32(fadd_m(fld_m(&SC->frameTime), &SC->endNoticeTime));
		}
		long double v = fsub_m(fld_m(&SC->endTime), &SC->frameTime);
		SC->endTime = (float)v;
		if (!(v >= 0)) {
			if (g_startedFromLobby != 0) {
				SC->quitAsked = 1;
				SC->escMenuOpen = 0;
			}
			SC->matchOver = 0;
			SC->endedByTime = -1;
			SC->playing = 0;
			SC->escMenuOpen = 0;
			SC->localAlive = 0;
			SC->endTime = 0.0f;
			SC->cameraSlot = -1;
			replay_closeRecording(sc);
			stage_deactivateActors(stage);
			SC->cameraSettings[0][SC->cameraMode] = 0;
			SC->cameraSettings[1][SC->cameraMode] = 0;
			if (SC->sessionMode == 0 && SC->stageCleared == 1 && g_missionStage == 14) {
				SC->lastMissionWon = 1;   /* the last mission won */
				SC->matchLeaving = 1;
				SC->quitDelay = 0.0f;
			} else {
				/* the next round */
				if (SC->ladderGame == 1) {
					g_ladderScore++;
					profile_addMatchScores(sc);
				}
				scene_resetScores(sc);
				SC->rankShown = -1;
				events_clear((Scene *)s, 60.0f);
				net_clearAnnouncements(s);
				if (SC->sessionMode == 0) {
					teams_setup(sc);
					scene_setLocalTeam((Scene *)s, -1);
					if (SC->stageCleared == 0)
						escMenu_open((Scene *)s, 3, 0);
					else
						SC->quitAsked = 1;
					SC->stageCleared = 0;
					return;
				}
				if (g_mapRotation == 0) {
					SC->elapsed = (*(int *)&SC->clockFraction) = 0;
					start_view(s);
					music_playMatch(sc);
				} else {
					if (SC->rotationCount > 0) {   /* the server's map rotation (+0x1f1668: map, mode) */
						SC->rotationAt = (SC->rotationAt + 1) % SC->rotationCount;
						g_missionStage = SC->rotation[SC->rotationAt].map;
						SC->nextMap = SC->rotation[(SC->rotationAt + 1) % SC->rotationCount].map;
						SC->nextMode = SC->rotation[(SC->rotationAt + 1) % SC->rotationCount].mode;
						game_setGameTypeFlags((Stage *)stage, SC->rotation[SC->rotationAt].mode);
					} else {
						g_missionStage = SC->nextMap;
						SC->nextMap = -1;
						game_setGameTypeFlags((Stage *)stage, SC->nextMode);
						SC->nextMode = -1;
					}
					SC->matchState = 1;
					SC->modeStarted = 0;
				}
				scene_saveNames(s);
				stage_newRound(stage);
				scene_restoreNames(s);
				SC->localRecordSet = 0;
				SC->localTeam = -1;
				if (SC->teamGame == 0) {
					SC->teamAsked = 0;
					if (SC->localPlayer >= 0)
						SC->players[SC->localPlayer].inPlay = 0;
					scene_setLocalTeam((Scene *)s, -1);
				}
				SC->players[SC->localPlayer].killsCounted = 0;
				SC->players[SC->localPlayer].kills = 0;
				SC->players[SC->localPlayer].deathsCounted = 0;
				SC->players[SC->localPlayer].deaths = 0;
				SC->rankingShown = 1;
				SC->stageCleared = 0;
				return;
			}
		}
	}
	/* the frag and time limits */
	if (SC->client == 0 && SC->matchOver == 0) {
		int limit = SC->scoreLimit;
		if (limit > 0) {
			if (SC->teamGame == 1) {
				if (SC->teamScores[scene_teamIdAt((Scene *)s, 0)] >= SC->scoreLimit
				    || SC->teamScores[scene_teamIdAt((Scene *)s, 1)] >= SC->scoreLimit) {
					winning_team(s);
					round_over(s, 0);
					if (SC->sessionMode == 0 && SC->teamScores[SC->localTeam] >= SC->scoreLimit
					    && g_missionStage == g_progress)
						SC->stageCleared = 1;
				}
			} else if (SC->rankCount > 0 && SC->players[SC->ranking[0]].kills >= limit) {
				round_over(s, 0);
				if (SC->sessionMode == 0 && SC->players[SC->localPlayer].kills >= SC->scoreLimit
				    && g_missionStage == g_progress)
					SC->stageCleared = 1;
			}
		}
		if (SC->timeLimit > 0 && SC->elapsed >= SC->timeLimit * 60) {
			if (SC->teamGame == 1)
				winning_team(s);
			round_over(s, 1);
		}
	}
	if (SC->stageCleared == 1 && g_missionStage == g_progress) {   /* the campaign's progress */
		g_progress++;
		profile_saveProgress();
	}
	/* the camera */
	if (SC->playing == 0) {
		if (SC->cameraSlot >= 0 && SC->watchedPlayer >= 0) {
			int c = SC->watchedPlayer;
			if (SC->players[c].state != 1 && SC->players[c].lastAttacker >= 0)
				killer_view(s, ACTOR_AT(c));
			else {
				int i = SC->cameraSlot;
				if (SC->cameraSettings[3][i] == 0 && i != 1) {
					preset_angles(s, ACTOR_AT(SC->watchedPlayer), 0x23424f2);
					orbit_from(s, ACTOR_AT(SC->watchedPlayer), 0x23424f2, 1);
					turn_view(s);
				} else {
					if (i == 1)
						pair_camera(s);
					else
						watch_camera(s);
					float *dir = SC->cameraDir, *up = SC->cameraUp;
					for (int k = 0; k < 3; k++)
						dir[k] = f32(fsub_m(fld_m(SC->cameraTarget + k), (const float *)SC->cameraPos + k));
					Vec3_normalize(dir);
					up[1] = 1.0f;
					up[0] = up[2] = 0;
				}
			}
		} else {
			free_camera(s, mv, 0, &move);
			turn_view(s);
		}
	} else if (SC->playing == 1) {
		const u8 *t;
		if (SC->matchOver == 1) {   /* the round's end: the winner, the top player or oneself */
			SC->cameraMode = 9;
			if (slow_end(s))
				t = ACTOR_AT(SC->lastDeath);
			else if (((Player *)scene_topPlayer(sc))->state == 1)
				t = (const u8 *)scene_topPlayer(sc);
			else
				t = ACTOR_AT(SC->localPlayer);
		} else {
			SC->cameraMode = SC->respawnCameraMode;
			t = ACTOR_AT(SC->localPlayer);
		}
		if (((Player *)t)->state != 1 && ((Player *)t)->lastAttacker >= 0)
			killer_view(s, t);
		else if (SC->cameraSettings[3][SC->cameraMode] != 0)
			look_at(s, ((const Player *)t)->pos);
		else {
			preset_angles(s, t, offsetof(Scene, cameraMode));
			if (SC->cameraMode == 1)
				muzzle_camera(s, t);
			else
				orbit_from(s, t, offsetof(Scene, cameraMode), SC->cameraMode != 9);
			turn_view(s);
		}
	}
	float far = view_farPlane(), near = view_nearPlane();
	int h = gfx_getHeight(), w = gfx_getWidth();
	float fov = view_angle();
	camera_setupView(stage, (float *)SC->cameraPos, SC->cameraDir,
	              SC->cameraUp, BITS(fov), w, h, BITS(near), BITS(far), BITS(SC->frameTime));   /* camera_setupView */
	stage_setViewDistance(stage, BITS(st->cullMargin));
	if (SC->localPlayer >= 0)
		chat_keys(s);
	if (SC->chatMode != 0)
		SC->keyGuard = 0.1f;   /* 0.1 */
	if (SC->ladderGame == 1) {
		long double v = fsub_m(fld_m(&SC->scoreCommitTimer), &SC->frameTime);
		SC->scoreCommitTimer = (float)v;
		if (!(v >= 0))
			profile_addMatchScores(sc);
	}
	/* the connection (a client's) */
	if (SC->sessionMode == 1) {
		if (SC->matchLeaving == 0) {
			if (net_isClient() == 0) {
				if (SC->lostTime > 5.0f) {
					msg_connectionLost(s);
					SC->matchLeaving = 1;
					SC->quitDelay = 3.0f;
					music_shutdown();
				} else
					SC->lostTime = f32(fadd_m(fld_m(&SC->lostTime), &SC->frameTime));
			}
			if (SC->matchLeaving == 0 && netq_resends() >= 0x80) {
				netq_clearResends();
				msg_networkUnstable(s);
				SC->matchLeaving = 1;
				SC->quitDelay = 3.0f;
				music_shutdown();
			}
		}
		if (netq_resends() > 0) {
			netq_clearResends();
			SC->resendWarning = 1.0f;
		} else if (run_down(s, offsetof(Scene, resendWarning)))
			SC->resendWarning = 0.0f;
	}
	/* the match restart count */
	if (SC->restartTimer > 0) {
		long double v = fsub_m(fld_m(&SC->restartTimer), &SC->frameTime);
		SC->restartTimer = (float)v;
		if (v > 0) {
			if (ftol(fadd_m(v, &SC->frameTime)) != ftol(v))
				sound_playVolume(9, 100);
		} else {
			if (SC->localPlayer >= 0 && SC->players[SC->localPlayer].team >= 0)
				SC->spawnPending = 1;
			SC->endTime = 0.0f;
			SC->matchOver = 0;
			replay_closeRecording(sc);
			if (SC->ladderGame == 1) {
				g_ladderScore++;
				profile_addMatchScores(sc);
			}
			for (int i = 0; i < SCENE_STAGE(s)->itemCount; i++)
				SCENE_STAGE(s)->items[i].taken = BITS(SCENE_STAGE(s)->items[i].fade) = 0;
			for (int i = 0; i < 16; i++) {
				SC->players[i].kills = SC->players[i].deaths = SC->players[i].killsCounted = 0;
				SC->players[i].deathsCounted = SC->players[i].timePlayed = BITS(SC->players[i].timeExtra) = 0;
			}
			stage_clearFrags(st);
			scene_updateRanking(sc);
			SC->rankShown = -1;
			events_clear((Scene *)s, 60.0f);
			net_clearAnnouncements(s);
			SC->elapsed = (*(int *)&SC->clockFraction) = 0;
			SC->players[SC->localPlayer].killsCounted = 0;
			SC->players[SC->localPlayer].kills = 0;
			SC->players[SC->localPlayer].deathsCounted = 0;
			SC->players[SC->localPlayer].deaths = 0;
			SC->restartTimer = 0.0f;
			sound_playVolume(0x18, 100);
		}
	}
	/* the match's end: the log, back to the menu */
	if (SC->matchLeaving == 1) {
		long double v = fsub_m(fld_m(&SC->quitDelay), &SC->frameTime);
		SC->quitDelay = (float)v;
		if (!(v > 0)) {
			if (g_matchLogWritten == 0 && g_startedFromLobby != 0)
				write_log(s, (const char *)(g_matchEndedByServer == 1 || (g_matchEndedByUser == 1 && SC->rankCount <= 1) ? STR(0x4d069c, "GameTitle %s\nMapNo %d\nFragLimit %d\nTi...") : STR(0x4d05a8, "GameTitle %s\nMapNo %d\nFragLimit %d\nTi...")),
				          1, 0);
			replay_closeRecording(sc);
			music_shutdown();
			if (SC->chatMode != 0 && g_textFieldOpen == 0) {
				SC->chatMode = 0;
				chat_keepLastLine();
			}
			if (SC->ladderGame == 1)
				profile_addMatchScores(sc);
			SC->quitAsked = 1;
		}
	}
	SC->modeStarted++;
}
#undef S
#undef SC
#undef ACTOR
#undef ACTOR_AT
