/* menu_cameras.c: the front end's camera moving between its home and a screen's menu point, and the free (watching)
   camera of screen 9999. The menu camera is a position (g_menuEyeX) and a point it looks at (g_menuCameraLook), three
   floats each; the menu points are 16 bytes apart from OBJ(g_camPoints) (positions) and OBJ(g_camAims) (look-at
   points), the home at g_menuEyeHomeX / g_menuLookHomeX. Each frame the camera eases a share of the way (the frame's
   time times a rate) and snaps once close enough. The arithmetic is kept in the original's order and at x87 precision
   (long double). */
#include "../game.h"
#include <string.h>

typedef long double X;

#define F(a) GAME_VAR(float, a)
#define I(a) GAME_VAR(int, a)
/* g_viewAspect (game.h): the 3D view's aspect ratio, eased to the screen's while the camera moves */
#define SCREEN_ASPECT ((X)I(ADDR(g_screenW)) / I(ADDR(g_screenH)))
#define RATE F(0x4a93ec)                   /* the share eased per second */

static const u32 cam[6] = { ADDR(g_menuEyeX), ADDR(g_menuEyeY), ADDR(g_menuEyeZ), ADDR(g_menuCameraLook), ADDR(g_menuCameraLookY), ADDR(g_menuCameraLookZ) };
static const u32 home[6] = { ADDR(g_menuEyeHomeX), ADDR(g_menuEyeHomeY), ADDR(g_menuEyeHomeZ), ADDR(g_menuLookHomeX), ADDR(g_menuLookHomeY), ADDR(g_menuLookHomeZ) };

/* a frame time above the constant at limit (k_5f / k_10f) taken as 1 */
static void limit_frame_time(u32 limit)
{
	if (g_frameTime > F(limit))
		g_frameTime = 1.0f;
}

/* a -= (a - target) * frame time * rate (fsub, fmul, fmul, fsubr) */
static void ease_from(u32 a, u32 target)
{
	F(a) = (float)((X)F(a) - ((X)F(a) - F(target)) * g_frameTime * RATE);
}

/* ---- the room's and the arena's camera: state mode (1 going to menu point idx, 0 going home, 2 there) ---- */
typedef struct {
	u32 mode, idx, v150;
	int idxHome;   /* the point index once home */
	int arena;     /* the arena: no height eased, the point it snapped to recorded */
} MenuCam;

static void menu_camera(const MenuCam *m)
{
	limit_frame_time(ADDR(k_5f));
	int mode = I(m->mode);
	if (mode == 1) {
		int i = I(m->idx) * 16;
		X k = g_frameTime, c = RATE;
		g_menuEyeX = (float)(((X)F(i + OBJ(g_camPoints)) - g_menuEyeX) * k * c + g_menuEyeX);
		if (!m->arena)
			g_menuEyeY = (float)(((X)F(i + (OBJ(g_camPoints) + 0x4)) - g_menuEyeY) * k * c + g_menuEyeY);
		g_menuEyeZ = (float)(((X)F(i + (OBJ(g_camPoints) + 0x8)) - g_menuEyeZ) * k * c + g_menuEyeZ);
		X look = ((X)F(i + OBJ(g_camAims)) - g_menuCameraLook) * k * c + g_menuCameraLook;
		g_menuCameraLook = (float)look;
		g_menuCameraLookY = (float)(((X)F(i + (OBJ(g_camAims) + 0x4)) - g_menuCameraLookY) * k * c + g_menuCameraLookY);
		if (!(look >= k_0f))
			look = -look;
		if (!(look > k_69_9))
			return;
		/* there: snapped to the point */
		if (!m->arena) {
			I(m->mode) = 2;
			(*(int *)&g_menuEyeX) = I(i + OBJ(g_camPoints));
			(*(int *)&g_menuEyeY) = I(i + (OBJ(g_camPoints) + 0x4));
			(*(int *)&g_menuEyeZ) = I(i + (OBJ(g_camPoints) + 0x8));
			(*(int *)&g_menuCameraLook) = I(i + OBJ(g_camAims));
			(*(int *)&g_menuCameraLookY) = I(i + (OBJ(g_camAims) + 0x4));
			(*(int *)&g_menuCameraLookZ) = I(i + (OBJ(g_camAims) + 0x8));
			g_frameOpening = 1;
		} else {
			g_frameOpening = 1;
			(*(int *)&g_menuEyeY) = I(i + (OBJ(g_camPoints) + 0x4));
			(*(int *)&g_menuEyeZ) = I(i + (OBJ(g_camPoints) + 0x8));
			volatile X x = F(i + OBJ(g_camPoints));   /* fld / fst / fstp */
			(*(int *)&g_arenaKeptCamY) = (*(int *)&g_menuEyeY);
			g_menuEyeX = (float)x;
			(*(int *)&g_menuCameraLook) = I(i + OBJ(g_camAims));
			(*(int *)&g_menuCameraLookY) = I(i + (OBJ(g_camAims) + 0x4));
			g_arenaKeptCamX = (float)x;
			(*(int *)&g_menuCameraLookZ) = I(i + (OBJ(g_camAims) + 0x8));
			(*(int *)&g_arenaKeptCamZ) = (*(int *)&g_menuEyeZ);
			I(m->mode) = 2;
			(*(int *)&g_arenaKeptLookX) = (*(int *)&g_menuCameraLook);
			(*(int *)&g_arenaKeptLookY) = (*(int *)&g_menuCameraLookY);
			(*(int *)&g_arenaKeptLookZ) = (*(int *)&g_menuCameraLookZ);
		}
		return;
	}
	if (mode != 0)
		return;
	X look = g_menuCameraLook;
	if (!(look >= k_0f))
		look = -look;
	if (!(look >= k_cameraSnapDistance)) {   /* close enough: snapped home */
		(*(int *)&g_menuCameraLook) = (*(int *)&g_menuLookHomeX);
		(*(int *)&g_menuCameraLookY) = (*(int *)&g_menuLookHomeY);
		(*(int *)&g_menuCameraLookZ) = (*(int *)&g_menuLookHomeZ);
		I(m->mode) = 2;
		(*(int *)&g_menuEyeX) = (*(int *)&g_menuEyeHomeX);
		(*(int *)&g_menuEyeY) = (*(int *)&g_menuEyeHomeY);
		(*(int *)&g_menuEyeZ) = (*(int *)&g_menuEyeHomeZ);
		I(m->idx) = m->idxHome;
		if (g_leavingForMatch == 1)
			(*(int *)&g_whiteFade) = 0;
		else
			g_viewAspect = (float)((long double)g_screenW / g_screenH);
		return;
	}
	if (g_leavingForMatch == 1) {
		limit_frame_time(ADDR(k_5f));
		GAME_VAR(u32, m->v150) = 0x43160000;   /* 150.0 */
	}
	for (int k = 0; k < 6; k++)
		ease_from(cam[k], home[k]);
}

/* 0x437a10: the game room's camera */
void (room_camera)(void)
{
	static const MenuCam room = { ADDR(g_roomCameraMode), ADDR(g_roomState), ADDR(g_unusedRoomCamWord), 0x63, 0 };
	menu_camera(&room);
}

/* 0x408270: the arena lobby's camera */
void (arena_camera)(void)
{
	static const MenuCam arena = { ADDR(g_arenaCameraMode), ADDR(g_lobbySubState), ADDR(g_unusedArenaCamWord), 5, 1 };
	menu_camera(&arena);
}

/* ---- the mission list's and skirmish screen's camera: to the first menu point and on to (0, -200, 1500), or home and
   back to the main menu (state 300) ---- */
typedef struct {
	u32 mode, flag, minus1;
	int skirmish;   /* the skirmish screen: its state set before the rest */
} MenuCam2;

static const u32 point0[6] = { ADDR(g_camPoint0X), ADDR(g_camPoint0Y), ADDR(g_camPoint0Z), ADDR(g_camAim0X), ADDR(g_camAim0Y), ADDR(g_camAim0Z) };

static void menu_camera2(const MenuCam2 *m)
{
	limit_frame_time(ADDR(k_10f));
	int mode = I(m->mode);
	if (mode == 1) {
		X k = g_frameTime, c = RATE;
		X last = 0;
		for (int i = 0; i < 6; i++) {
			last = ((X)F(point0[i]) - F(cam[i])) * k * c + F(cam[i]);
			F(cam[i]) = (float)last;
		}
		if (g_viewAspect > k_0f)
			g_viewAspect = (float)((X)g_viewAspect - (X)g_frameTime * k_0_07f);
		if (!(last > k_m1f))
			return;
		X full = SCREEN_ASPECT;
		(*(int *)&g_menuEyeX) = 0;
		(*(u32 *)&g_menuEyeY) = 0xc3480000;   /* -200 */
		(*(u32 *)&g_menuEyeZ) = 0x44bb8000;   /* 1500 */
		(*(int *)&g_menuCameraLook) = 0;
		(*(u32 *)&g_menuCameraLookY) = 0xc3480000;
		(*(int *)&g_menuCameraLookZ) = 0;
		I(m->mode) = 2;
		I(m->flag) = 0;
		g_frameOpening = 1;
		g_viewAspect = (float)full;
		return;
	}
	if (mode != 0)
		return;
	int fast = g_menuCameraLookZ > k_m549f;
	X c = fast ? k_0_1f : k_0_5f;
	I(m->flag) = 1;
	for (int i = 0; i < 6; i++)
		F(cam[i]) = (float)((X)F(cam[i]) - ((X)F(cam[i]) - F(home[i])) * g_frameTime * c);
	X full = SCREEN_ASPECT;
	if (!(g_viewAspect >= full))
		g_viewAspect = (float)((X)g_frameTime * F(fast ? OBJ(k_0_05f) : ADDR(k_0_01f)) + g_viewAspect);
	if (g_menuCameraLookZ > k_m549_99f)
		return;
	/* home */
	(*(int *)&g_menuCameraLook) = (*(int *)&g_menuLookHomeX);
	(*(int *)&g_menuCameraLookY) = (*(int *)&g_menuLookHomeY);
	(*(int *)&g_menuCameraLookZ) = (*(int *)&g_menuLookHomeZ);
	if (m->skirmish)
		I(m->mode) = 2;
	(*(int *)&g_menuEyeX) = (*(int *)&g_menuEyeHomeX);
	(*(int *)&g_menuEyeY) = (*(int *)&g_menuEyeHomeY);
	(*(int *)&g_menuEyeZ) = (*(int *)&g_menuEyeHomeZ);
	if (m->skirmish && g_leavingForMatch == 1)
		(*(int *)&g_whiteFade) = 0;
	g_viewAspect = (float)full;
	if (!m->skirmish)
		I(m->mode) = 2;
	I(m->minus1) = -1;
	g_menuState = 300;
	g_lastScreen = 300;
	g_nextScreen = 300;
	(*(int *)&g_menuRepeatClock) = 0;
}

/* 0x410b50 (the arm screen's camera, g_armcState: 1 out to the first menu point, 0
   back home, 2 there). Going out it eases there (the view's aspect narrowing) and snaps once its depth passes -1
   (-1101 from the Ladder game room, g_armcFrom 3): at (0, -200, 1500; 400 from the game room) looking at (0, -200, 0), the dialog
   up. Coming home it eases fast while its depth is past -549 (-1649), else slowly, the aspect widening back, and
   snaps home once within 0.01 of -550 (-1650); then on to where it came from (g_armcFrom): 1 the main menu (300), 2 the
   arena lobby (400; the camera to its saved place, the home moved to (0, 0, -1550) looking at (0, 0, -1650)), 3 the
   game room (800, room_initCameraPoints); a launcher-started game (reply 0x67, g_launchStartStep) then starts (arena_startFromLauncher). The caller
   ignores the eax it leaves */
void (armc_cameraStep)(void)
{
	limit_frame_time(ADDR(k_10f));
	int from = g_armcFrom, fromRoom = from == 3;
	float base = fromRoom ? -1650.0f : -550.0f;
	int mode = g_armcState;
	if (mode == 1) {
		X k = g_frameTime, c = RATE;
		X last = 0;
		for (int i = 0; i < 6; i++) {
			last = ((X)F(point0[i]) - F(cam[i])) * k * c + F(cam[i]);
			F(cam[i]) = (float)last;
		}
		if (g_viewAspect > k_0f)
			g_viewAspect = (float)((X)g_viewAspect - (X)g_frameTime * k_0_07f);
		if (!(last > F(fromRoom ? ADDR(k_m1101f) : ADDR(k_m1f))))   /* (the depth before its rounding) */
			return;
		(*(int *)&g_menuEyeX) = 0;
		(*(u32 *)&g_menuEyeY) = 0xc3480000;   /* -200 */
		(*(u32 *)&g_menuEyeZ) = fromRoom ? 0x43c80000 : 0x44bb8000;   /* 400 / 1500 */
		g_frameOpening = 1;
		(*(int *)&g_menuCameraLook) = 0;
		(*(u32 *)&g_menuCameraLookY) = 0xc3480000;
		(*(int *)&g_menuCameraLookZ) = 0;
		g_armcState = 2;
		g_armcCameraTravelling = 0;
		g_viewAspect = (float)SCREEN_ASPECT;
		return;
	}
	if (mode != 0)
		return;
	int fast = !((X)base + k_1f >= g_menuCameraLookZ);
	X c = fast ? k_0_1f : k_0_5f;
	g_armcCameraTravelling = 1;
	for (int i = 0; i < 6; i++)
		F(cam[i]) = (float)((X)F(cam[i]) - ((X)F(cam[i]) - F(home[i])) * g_frameTime * c);
	X full = SCREEN_ASPECT;
	if (!(g_viewAspect >= full))
		g_viewAspect = (float)((X)g_frameTime * F(fast ? OBJ(k_0_05f) : ADDR(k_0_01f)) + g_viewAspect);
	if (!((X)base + k_0_01f >= g_menuCameraLookZ))
		return;
	/* home */
	g_armcState = 2;
	for (int i = 0; i < 6; i++)
		I(cam[i]) = I(home[i]);
	g_armcMode = 0;
	int state;
	switch (from) {
	case 1:
		state = 300;
		(*(int *)&g_menuRepeatClock) = 0;
		break;
	case 2:
		state = 400;
		(*(int *)&g_menuEyeX) = (*(int *)&g_arenaKeptCamX);
		(*(int *)&g_menuEyeY) = (*(int *)&g_arenaKeptCamY);
		(*(int *)&g_menuEyeZ) = (*(int *)&g_arenaKeptCamZ);
		(*(int *)&g_menuCameraLook) = (*(int *)&g_arenaKeptLookX);
		(*(int *)&g_menuCameraLookY) = (*(int *)&g_arenaKeptLookY);
		(*(int *)&g_menuCameraLookZ) = (*(int *)&g_arenaKeptLookZ);
		(*(int *)&g_menuEyeHomeX) = 0;
		(*(int *)&g_menuEyeHomeY) = 0;
		(*(u32 *)&g_menuEyeHomeZ) = 0xc4c1c000;   /* -1550 */
		(*(int *)&g_menuLookHomeX) = 0;
		(*(int *)&g_menuLookHomeY) = 0;
		(*(u32 *)&g_menuLookHomeZ) = 0xc4ce4000;   /* -1650 */
		break;
	case 3:
		state = 800;
		(*(int *)&g_menuRepeatClock) = 0;
		break;
	default:
		state = 0;
		break;
	}
	if (state) {
		g_viewAspect = (float)full;
		g_menuState = state;
		g_lastScreen = state;
		g_nextScreen = state;
		g_armcFrom = 0;
		if (state == 800)
			room_initCameraPoints();   /* room_initCameraPoints */
	}
	if (g_launchedForNetGame == 1 && g_launchStartStep == 0x67)
		arena_startFromLauncher();
}

/* 0x444130: the mission list's camera (screen 900) */
void (missions_camera)(void)
{
	static const MenuCam2 missions = { ADDR(g_missionsState), ADDR(g_missionsDrawBackground), ADDR(g_missionsPage), 0 };
	menu_camera2(&missions);
}

/* 0x447cb0: the skirmish screen's camera (screen 500) */
void (skirmish_camera)(void)
{
	static const MenuCam2 skirmish = { ADDR(g_skirmishState), ADDR(g_skirmishShowBackground), ADDR(g_skirmishLeft), 1 };
	menu_camera2(&skirmish);
}

/* ---- the free menu camera moved along its heading (the turn at g_freeCamYaw, plus a quarter turn, wrapped, in radians)
   by the frame time times its speed ---- */

static X side_angle(void)
{
	X v = (X)g_freeCamYaw + k_90f;
	if (v > k_360f)
		v -= k_360f;
	return v * (X)k_pi * (X)k_oneOver180;
}
#define SPEED F(0x4a9534)

/* 0x42aa30: the free (watching) camera stepped left: along its heading plus a quarter turn (g_freeCamYaw + 90
   degrees) by the frame time x its speed, both the free camera's point (g_freeCamLookX / g_freeCamLookZ) and the menu
   camera's eye (g_menuCameraPos, g_menuEyeZ). Only caller freeCam_keys, on g_keyStepLeft (A) */
void (freeCam_stepLeft)(void)
{
	X a = side_angle();
	float s = (float)x87_fsin(a);
	X c = x87_fcos(a);
	X t = (X)g_frameTime * s * SPEED;
	float tf = (float)t;
	g_freeCamLookX = (float)(t + g_freeCamLookX);   /* the unrounded step here ... */
	X u = c * g_frameTime * SPEED;
	g_freeCamLookZ = (float)(u + g_freeCamLookZ);
	g_menuEyeX = (float)((X)tf + g_menuEyeX);   /* ... the rounded one here */
	g_menuEyeZ = (float)(u + g_menuEyeZ);
}

/* 0x42aad0: the free camera stepped right (freeCam_stepLeft's opposite; here every use of the sideways step is
   rounded). Only caller freeCam_keys, on g_keyStepRight (D) */
void (freeCam_stepRight)(void)
{
	X a = side_angle();
	float s = (float)x87_fsin(a);
	X c = x87_fcos(a);
	float tf = (float)((X)g_frameTime * s * SPEED);
	g_freeCamLookX = (float)((X)g_freeCamLookX - tf);
	X u = c * g_frameTime * SPEED;
	g_freeCamLookZ = (float)((X)g_freeCamLookZ - u);
	g_menuEyeX = (float)((X)g_menuEyeX - tf);
	g_menuEyeZ = (float)((X)g_menuEyeZ - u);
}

/* the free (watching) camera's turn (g_freeCamYaw, degrees) as its sine and cosine, and kept in the slot's record (g_slotCams) */
static void turn_update(int slot)
{
	X a = (X)g_freeCamYaw * k_pi * k_oneOver180;
	g_freeCamTurnSin = (float)x87_fsin(a);
	g_freeCamTurnCos = (float)x87_fcos(a);
	volatile X t = g_freeCamYaw;
	F(OBJ(g_slotCams) + 0x28 + slot * 88) = (float)t;
}

/* 0x42ab70: the free (watching) camera's mouse look, screen 9999 (not while the chat line is open, g_watchChatOpen):
   the pointer's distance from (320, 240) turns the view (g_freeCamYaw, wrapping 0 .. 360; turn_update keeps its sine
   / cosine and puts it in the local slot's g_slotCams record) and tilts it (g_freeCamTilt, -50 .. 50); the first
   click (g_freeCamMoveStarted) sets g_freeCamMoveTarget / g_freeCamMoveEye from the slot's record */
void (freeCam_mouseLook)(void)
{
	if (g_watchChatOpen)
		return;
	int dx = 0x140 - g_mouseX, dy = 0xf0 - g_mouseY;
	int slot = g_localSlot;
	if (dx > 0) {
		X a = (X)dx * k_0_28125f * g_frameTime + g_freeCamYaw;
		g_freeCamYaw = (float)a;
		if (a > k_360f)
			(*(int *)&g_freeCamYaw) = 0;
		turn_update(slot);
	}
	if (dx < 0) {
		X a = (X)g_freeCamYaw - (X)(-dx) * k_0_28125f * g_frameTime;
		g_freeCamYaw = (float)a;
		if (!(a >= k_0f))
			(*(u32 *)&g_freeCamYaw) = 0x43b40000;   /* 360 */
		turn_update(slot);
	}
	if (dy > 0 && !(g_freeCamTilt >= k_50f))
		g_freeCamTilt = (float)((X)dy * k_tenth * g_frameTime + g_freeCamTilt);
	if (dy < 0 && g_freeCamTilt > k_m50f)
		g_freeCamTilt = (float)((X)dy * k_tenth * g_frameTime + g_freeCamTilt);
	if (g_mouseClick && !g_freeCamMoveStarted) {
		u32 r = OBJ(g_slotCams) + slot * 88;
		g_freeCamMoveStarted = 1;
		g_unusedFreeCamMoveWord = 0x41f00000;   /* 30 */
		(*(int *)&g_freeCamMoveTargetX) = I(r);
		(*(int *)&g_freeCamMoveTargetY) = I(r + 4);
		(*(int *)&g_freeCamMoveTargetZ) = I(r + 8);
		g_freeCamMoveEyeX = (float)((X)g_freeCamTurnSin * k_2000f + F(r));
		(*(int *)&g_freeCamMoveEyeY) = I(r + 4);
		g_freeCamMoveEyeZ = (float)((X)g_freeCamTurnCos * k_2000f + F(r + 8));
	}
}

/* 0x4230e0: the setup screen's camera: to the setup tab's menu point (mode 1; its height not eased), or home (mode
   0), then snapped and settled (mode 2) once close enough */
void (setup_camera)(void)
{
	if (g_frameTime > k_10f)
		g_frameTime = 1.0f;
	int mode = g_setupCameraMode;
	X k = g_frameTime, c = RATE;
	if (mode == 1) {
		int i = g_setupTab * 16;
		g_menuEyeX = (float)(((X)F(i + OBJ(g_camPoints)) - g_menuEyeX) * k * c + g_menuEyeX);
		g_menuEyeZ = (float)(((X)F(i + (OBJ(g_camPoints) + 0x8)) - g_menuEyeZ) * k * c + g_menuEyeZ);
		X look = ((X)F(i + OBJ(g_camAims)) - g_menuCameraLook) * k * c + g_menuCameraLook;
		g_menuCameraLook = (float)look;
		g_menuCameraLookY = (float)(((X)F(i + (OBJ(g_camAims) + 0x4)) - g_menuCameraLookY) * k * c + g_menuCameraLookY);
		if (!(look >= k_0f))
			look = -look;
		if (!(look > k_69_9))
			return;
		for (int a = 0; a < 3; a++) {
			I(ADDR(g_menuEyeX) + a * 4) = I(i + OBJ(g_camPoints) + a * 4);
		}
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuCameraLook) + a * 4) = I(i + OBJ(g_camAims) + a * 4);
		g_setupCameraMode = 2;
		g_frameOpening = 1;
	} else if (mode == 0) {
		g_menuEyeX = (float)((X)g_menuEyeX - ((X)g_menuEyeX - g_menuEyeHomeX) * k * c);
		g_menuEyeZ = (float)((X)g_menuEyeZ - ((X)g_menuEyeZ - g_menuEyeHomeZ) * k * c);
		X look = (X)g_menuCameraLook - ((X)g_menuCameraLook - g_menuLookHomeX) * k * c;
		g_menuCameraLook = (float)look;
		g_menuCameraLookY = (float)((X)g_menuCameraLookY - ((X)g_menuCameraLookY - g_menuLookHomeY) * k * c);
		if (!(look >= k_0f))
			look = -look;
		if (look >= k_cameraSnapDistance)
			return;
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuCameraLook) + a * 4) = I(ADDR(g_menuLookHomeX) + a * 4);
		g_setupCameraMode = 2;
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuEyeX) + a * 4) = I(ADDR(g_menuEyeHomeX) + a * 4);
		g_setupTab = 0x29a;
	}
}

/* 0x42ada0: the free camera's keys (screen 9999, watching): while the chat line is open (g_watchChatOpen) wait until
   it is closed (g_textFieldOpen clear), then send it (net_sendChat; g_lastChatLineSet / g_lastChatLine) unless empty
   and take the keyboard back; g_keyChat opens the chat line (50 characters); g_keyCancel2 leaves (a host tells the
   others first: g_netHostLeftMessageKind) through game_returnToMainMenu; g_keyForward / g_keyBackward (W / S) move
   the camera along its heading (g_freeCamTurnSin / g_freeCamTurnCos x k_3f x the frame time), g_keyStepLeft /
   g_keyStepRight (A / D) step it sideways (freeCam_stepLeft / freeCam_stepRight); then the menu camera follows:
   look-at (g_freeCamLookX, g_menuCameraLookY = height + tilt, g_freeCamLookZ), eye 50 units behind along the heading at
   height + 10; the point is kept in the local slot's g_slotCams record (0x58 bytes, g_localSlot); g_dikZ_2 toggles
   g_freeCamZoom 1 / 2, and 1 / 2 / 3 / 4 step g_debugValue by +1 / +10 / -1 / -10 (not below 1). The original leaves
   eax to callers that ignore it */
void (freeCam_keys)(void)
{
	const float *frame = (const float *)ADDR(g_frameTime), *speed = (const float *)ADDR(k_3f);
	if (g_watchChatOpen) {
		if (g_textFieldOpen)
			return;
		if (strlen(g_inputLine)) {
			net_sendChat(g_inputLine);
			g_watchChatOpen = 0;
			g_lastChatLineSet = 1;
			(*(u32 *)&g_lastChatLine) = OBJ(g_inputLine);
		} else {
			g_watchChatOpen = 0;
			g_lastChatLineSet = 0;
		}
		g_textFieldOpen = 0;
		input_resetKeys();
		input_initKeyboard(g_mainWindow);
		return;
	}
	if (input_justPressed(g_keyChat)) {
		input_releaseKeyboard();
		g_textFieldOpen = 1;
		menu_clearInputBuffer(0x32);
		g_watchChatOpen = 1;
		(*(u32 *)&g_menuKeyGuard) = 0x41a00000;   /* 20 */
		g_editCaretX = 0x32;
		g_editCaretY = 0x1cc;
		return;
	}
	if (input_justPressed(g_keyCancel2)) {
		if (g_isHost) {
			g_hostGoneMessageFlag = 1;
			net_sendMessage((void *)ADDR(g_netHostLeftMessageKind), 0, 0);
			g_hostGoneMessageFlag = 0;
		}
		g_unusedPostMatchFlag = 1;
		game_returnToMainMenu();
		return;
	}
	if (input_isDown(g_keyForward) == 1) {
		long double a = fmul_m(fmul_m(fld_m(frame), &g_freeCamTurnSin), speed);
		g_freeCamLookX = f32(fadd_m(a, &g_freeCamLookX));
		long double b = fmul_m(fmul_m(fld_m(&g_freeCamTurnCos), frame), speed);
		float bf = f32(b);
		g_freeCamLookZ = f32(fadd_m(b, &g_freeCamLookZ));
		g_menuEyeX = f32(fadd_m(a, &g_menuEyeX));
		g_menuEyeZ = f32(FADD(bf, g_menuEyeZ));
	}
	if (input_isDown(g_keyBackward) == 1) {
		long double a = fmul_m(fmul_m(fld_m(frame), &g_freeCamTurnSin), speed);
		g_freeCamLookX = f32(fld_m(&g_freeCamLookX) - a);
		float bf = f32(fmul_m(fmul_m(fld_m(&g_freeCamTurnCos), frame), speed));
		g_freeCamLookZ = f32(FSUB(g_freeCamLookZ, bf));
		g_menuEyeX = f32(fld_m(&g_menuEyeX) - a);
		g_menuEyeZ = f32(FSUB(g_menuEyeZ, bf));
	}
	if (input_isDown(g_keyStepLeft) == 1)
		freeCam_stepLeft();
	if (input_isDown(g_keyStepRight) == 1)
		freeCam_stepRight();
	(*(u32 *)&g_menuCameraLook) = (*(u32 *)&g_freeCamLookX);
	(*(u32 *)&g_menuCameraLookZ) = (*(u32 *)&g_freeCamLookZ);
	g_menuEyeX = f32(fsubr_m(fmul_m(fld_m(&g_freeCamTurnSin), (const float *)ADDR(k_50f)), &g_freeCamLookX));
	g_menuEyeY = f32(fadd_m(fld_m(&g_freeCamLookY), (const float *)ADDR(k_10f)));
	u32 *slot = (u32 *)(OBJ(g_slotCams) + g_localSlot * 0x58);
	slot[0] = (*(u32 *)&g_freeCamLookX);
	slot[1] = (*(u32 *)&g_freeCamLookY);
	slot[2] = (*(u32 *)&g_freeCamLookZ);
	g_menuEyeZ = f32(fsubr_m(fmul_m(fld_m(&g_freeCamTurnCos), (const float *)ADDR(k_50f)), &g_freeCamLookZ));
	g_menuCameraLookY = f32(FADD(g_freeCamTilt, g_freeCamLookY));
	if (input_justPressed(g_dikZ_2) == 1)
		g_freeCamZoom = g_freeCamZoom == 1 ? 2 : 1;
	if (input_justPressed(g_dik1) == 1)
		g_debugValue++;
	if (input_justPressed(g_dik2) == 1)
		g_debugValue += 10;
	if (input_justPressed(g_dik3) == 1)
		g_debugValue--;
	if (input_justPressed(g_dik4) == 1)
		g_debugValue -= 10;
	if (g_debugValue < 1)
		g_debugValue = 1;
}
