/* menu_cameras.c: the front end's camera moving between its home and a screen's menu point. The camera is a
   position (0x4df024) and a point it looks at (0x680378), three floats each; the menu points are 16 bytes apart
   from OBJ(g_camPoints) (positions) and OBJ(g_camAims) (look-at points), the home at 0x9db090 / 0x76d3f8. Each frame the camera
   eases a share of the way (the frame's time times a rate) and snaps once close enough. The arithmetic is kept in
   the original's order and at x87 precision (long double). */
#include "../game.h"
#include <string.h>

typedef long double X;

#define F(a) GAME_VAR(float, a)
#define I(a) GAME_VAR(int, a)
/* g_viewAspect (game.h): the 3D view's aspect ratio, eased to the screen's while the camera moves */
#define SCREEN_ASPECT ((X)I(ADDR(g_screenW)) / I(ADDR(g_screenH)))
#define RATE F(0x4a93ec)                   /* the share eased per second */

static const u32 cam[6] = { ADDR(g_menuCameraPos), ADDR(g_armcCamHeight), ADDR(g_armcCamDistance), ADDR(g_menuCameraLook), ADDR(g_menuCameraLookY), ADDR(g_menuCameraHeight) };
static const u32 home[6] = { ADDR(g_menuCameraX), ADDR(g_menuCameraY), ADDR(g_menuCameraZ), ADDR(g_menuLookAtX), ADDR(g_menuLookAtY), ADDR(g_menuLookAtZ) };

/* the frame time limited to 1 second (above the constant at limit) */
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
		(*(float *)&g_menuCameraPos) = (float)(((X)F(i + OBJ(g_camPoints)) - (*(float *)&g_menuCameraPos)) * k * c + (*(float *)&g_menuCameraPos));
		if (!m->arena)
			g_armcCamHeight = (float)(((X)F(i + (OBJ(g_camPoints) + 0x4)) - g_armcCamHeight) * k * c + g_armcCamHeight);
		g_armcCamDistance = (float)(((X)F(i + (OBJ(g_camPoints) + 0x8)) - g_armcCamDistance) * k * c + g_armcCamDistance);
		X look = ((X)F(i + OBJ(g_camAims)) - (*(float *)&g_menuCameraLook)) * k * c + (*(float *)&g_menuCameraLook);
		(*(float *)&g_menuCameraLook) = (float)look;
		(*(float *)&g_menuCameraLookY) = (float)(((X)F(i + (OBJ(g_camAims) + 0x4)) - (*(float *)&g_menuCameraLookY)) * k * c + (*(float *)&g_menuCameraLookY));
		if (!(look >= k_0f))
			look = -look;
		if (!(look > k_69_9))
			return;
		/* there: snapped to the point */
		if (!m->arena) {
			I(m->mode) = 2;
			(*(int *)&g_menuCameraPos) = I(i + OBJ(g_camPoints));
			(*(int *)&g_armcCamHeight) = I(i + (OBJ(g_camPoints) + 0x4));
			(*(int *)&g_armcCamDistance) = I(i + (OBJ(g_camPoints) + 0x8));
			(*(int *)&g_menuCameraLook) = I(i + OBJ(g_camAims));
			(*(int *)&g_menuCameraLookY) = I(i + (OBJ(g_camAims) + 0x4));
			g_menuCameraHeight = I(i + (OBJ(g_camAims) + 0x8));
			g_dialogOpen = 1;
		} else {
			g_dialogOpen = 1;
			(*(int *)&g_armcCamHeight) = I(i + (OBJ(g_camPoints) + 0x4));
			(*(int *)&g_armcCamDistance) = I(i + (OBJ(g_camPoints) + 0x8));
			volatile X x = F(i + OBJ(g_camPoints));   /* fld / fst / fstp */
			g_arenaKeptCamY = (*(int *)&g_armcCamHeight);
			(*(float *)&g_menuCameraPos) = (float)x;
			(*(int *)&g_menuCameraLook) = I(i + OBJ(g_camAims));
			(*(int *)&g_menuCameraLookY) = I(i + (OBJ(g_camAims) + 0x4));
			g_arenaKeptCamX = (float)x;
			g_menuCameraHeight = I(i + (OBJ(g_camAims) + 0x8));
			g_arenaKeptCamZ = (*(int *)&g_armcCamDistance);
			I(m->mode) = 2;
			g_arenaKeptLookX = (*(int *)&g_menuCameraLook);
			g_arenaKeptLookY = (*(int *)&g_menuCameraLookY);
			g_arenaKeptLookZ = g_menuCameraHeight;
		}
		return;
	}
	if (mode != 0)
		return;
	X look = (*(float *)&g_menuCameraLook);
	if (!(look >= k_0f))
		look = -look;
	if (!(look >= k_cameraSnapDistance)) {   /* close enough: snapped home */
		(*(int *)&g_menuCameraLook) = g_menuLookAtX;
		(*(int *)&g_menuCameraLookY) = g_menuLookAtY;
		g_menuCameraHeight = g_menuLookAtZ;
		I(m->mode) = 2;
		(*(int *)&g_menuCameraPos) = g_menuCameraX;
		(*(int *)&g_armcCamHeight) = g_menuCameraY;
		(*(int *)&g_armcCamDistance) = g_menuCameraZ;
		I(m->idx) = m->idxHome;
		if (g_quitAsked == 1)
			(*(int *)&g_roomFade) = 0;
		else
			g_viewAspect = (float)((long double)g_screenW / g_screenH);
		return;
	}
	if (g_quitAsked == 1) {
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

/* ---- the skirmish and mission-select camera: to the first menu point and on to (0, -200, 1500), or home and
   back to the main menu (state 300) ---- */
typedef struct {
	u32 mode, flag, minus1;
	int mission;   /* the mission select: its state set before the rest */
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
		(*(int *)&g_menuCameraPos) = 0;
		(*(u32 *)&g_armcCamHeight) = 0xc3480000;   /* -200 */
		(*(u32 *)&g_armcCamDistance) = 0x44bb8000;   /* 1500 */
		(*(int *)&g_menuCameraLook) = 0;
		g_menuCameraLookY = 0xc3480000;
		g_menuCameraHeight = 0;
		I(m->mode) = 2;
		I(m->flag) = 0;
		g_dialogOpen = 1;
		g_viewAspect = (float)full;
		return;
	}
	if (mode != 0)
		return;
	int fast = (*(float *)&g_menuCameraHeight) > k_m549f;
	X c = fast ? k_tenthsToDegrees : k_0_5f;
	I(m->flag) = 1;
	for (int i = 0; i < 6; i++)
		F(cam[i]) = (float)((X)F(cam[i]) - ((X)F(cam[i]) - F(home[i])) * g_frameTime * c);
	X full = SCREEN_ASPECT;
	if (!(g_viewAspect >= full))
		g_viewAspect = (float)((X)g_frameTime * F(fast ? OBJ(k_0_05f) : ADDR(k_0_01f)) + g_viewAspect);
	if ((*(float *)&g_menuCameraHeight) > k_m549_99f)
		return;
	/* home */
	(*(int *)&g_menuCameraLook) = g_menuLookAtX;
	(*(int *)&g_menuCameraLookY) = g_menuLookAtY;
	g_menuCameraHeight = g_menuLookAtZ;
	if (m->mission)
		I(m->mode) = 2;
	(*(int *)&g_menuCameraPos) = g_menuCameraX;
	(*(int *)&g_armcCamHeight) = g_menuCameraY;
	(*(int *)&g_armcCamDistance) = g_menuCameraZ;
	if (m->mission && g_quitAsked == 1)
		(*(int *)&g_roomFade) = 0;
	g_viewAspect = (float)full;
	if (!m->mission)
		I(m->mode) = 2;
	I(m->minus1) = -1;
	g_menuState = 300;
	g_lastScreen = 300;
	g_nextScreen = 300;
	(*(int *)&g_cursorBlink) = 0;
}

/* 0x410b50 (the arm screen's camera, 0x4dc790: 1 out to the first menu point, 0
   back home, 2 there). Going out it eases there (the view's aspect narrowing) and snaps once its depth passes -1
   (-1101 in network play, 0x4dc24c 3): at (0, -200, 1500; 400 in network play) looking at (0, -200, 0), the dialog
   up. Coming home it eases fast while its depth is past -549 (-1649), else slowly, the aspect widening back, and
   snaps home once within 0.01 of -550 (-1650); then on to where it came from (0x4dc24c): 1 the main menu (300), 2 the
   arena lobby (400; the camera to its saved place, the home moved to (0, 0, -1550) looking at (0, 0, -1650)), 3 the
   game room (800, menuCamera_initPoints); a lobby game with a reply 0x67 (0x9da49c) then leaves (arena_loadAndQuit). The caller
   ignores the eax it leaves */
void (armc_cameraStep)(void)
{
	limit_frame_time(ADDR(k_10f));
	int from = g_armcFrom, network = from == 3;
	float base = network ? -1650.0f : -550.0f;
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
		if (!(last > F(network ? ADDR(k_m1101f) : ADDR(k_m1f))))   /* (the depth before its rounding) */
			return;
		(*(int *)&g_menuCameraPos) = 0;
		(*(u32 *)&g_armcCamHeight) = 0xc3480000;   /* -200 */
		(*(u32 *)&g_armcCamDistance) = network ? 0x43c80000 : 0x44bb8000;   /* 400 / 1500 */
		g_dialogOpen = 1;
		(*(int *)&g_menuCameraLook) = 0;
		g_menuCameraLookY = 0xc3480000;
		g_menuCameraHeight = 0;
		g_armcState = 2;
		g_armcEntered = 0;
		g_viewAspect = (float)SCREEN_ASPECT;
		return;
	}
	if (mode != 0)
		return;
	int fast = !((X)base + k_1f >= (*(float *)&g_menuCameraHeight));
	X c = fast ? k_tenthsToDegrees : k_0_5f;
	g_armcEntered = 1;
	for (int i = 0; i < 6; i++)
		F(cam[i]) = (float)((X)F(cam[i]) - ((X)F(cam[i]) - F(home[i])) * g_frameTime * c);
	X full = SCREEN_ASPECT;
	if (!(g_viewAspect >= full))
		g_viewAspect = (float)((X)g_frameTime * F(fast ? OBJ(k_0_05f) : ADDR(k_0_01f)) + g_viewAspect);
	if (!((X)base + k_0_01f >= (*(float *)&g_menuCameraHeight)))
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
		(*(int *)&g_cursorBlink) = 0;
		break;
	case 2:
		state = 400;
		(*(int *)&g_menuCameraPos) = (*(int *)&g_arenaKeptCamX);
		(*(int *)&g_armcCamHeight) = g_arenaKeptCamY;
		(*(int *)&g_armcCamDistance) = g_arenaKeptCamZ;
		(*(int *)&g_menuCameraLook) = g_arenaKeptLookX;
		(*(int *)&g_menuCameraLookY) = g_arenaKeptLookY;
		g_menuCameraHeight = g_arenaKeptLookZ;
		g_menuCameraX = 0;
		g_menuCameraY = 0;
		(*(u32 *)&g_menuCameraZ) = 0xc4c1c000;   /* -1550 */
		g_menuLookAtX = 0;
		g_menuLookAtY = 0;
		(*(u32 *)&g_menuLookAtZ) = 0xc4ce4000;   /* -1650 */
		break;
	case 3:
		state = 800;
		(*(int *)&g_cursorBlink) = 0;
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
			menuCamera_initPoints();   /* menuCamera_initPoints */
	}
	if (g_startedFromLobby == 1 && g_lobbyReply == 0x67)
		arena_loadAndQuit();   /* arena_loadAndQuit */
}

/* 0x444130: the skirmish screen's camera */
void (skirmish_camera)(void)
{
	static const MenuCam2 skirmish = { ADDR(g_skirmishState), ADDR(g_skirmishDrawBackground), ADDR(g_skirmishPage), 0 };
	menu_camera2(&skirmish);
}

/* 0x447cb0: the mission select's camera */
void (missionsel_camera)(void)
{
	static const MenuCam2 mission = { ADDR(g_missionPage), ADDR(g_missionShowBackground), ADDR(g_missionBusy), 1 };
	menu_camera2(&mission);
}

/* ---- the free menu camera moved along its heading (the turn at 0x90d1cc, plus a quarter turn, wrapped, in radians)
   by the frame time times its speed ---- */

static X heading(void)
{
	X v = (X)g_armcLookYaw + k_90f;
	if (v > k_360f)
		v -= k_360f;
	return v * (X)k_pi * (X)k_oneOver180;
}
#define SPEED F(0x4a9534)

/* 0x42aa30: forward (the camera's position 0x4de344 / 0x4de34c and the menu camera's) */
void (menuCamera_forward)(void)
{
	X a = heading();
	float s = (float)x87_fsin(a);
	X c = x87_fcos(a);
	X t = (X)g_frameTime * s * SPEED;
	float tf = (float)t;
	(*(float *)&g_menuCamX) = (float)(t + (*(float *)&g_menuCamX));   /* the unrounded step here ... */
	X u = c * g_frameTime * SPEED;
	(*(float *)&g_menuCamZ) = (float)(u + (*(float *)&g_menuCamZ));
	(*(float *)&g_menuCameraPos) = (float)((X)tf + (*(float *)&g_menuCameraPos));   /* ... the rounded one here */
	g_armcCamDistance = (float)(u + g_armcCamDistance);
}

/* 0x42aad0: back (here every use of the sideways step is rounded) */
void (menuCamera_back)(void)
{
	X a = heading();
	float s = (float)x87_fsin(a);
	X c = x87_fcos(a);
	float tf = (float)((X)g_frameTime * s * SPEED);
	(*(float *)&g_menuCamX) = (float)((X)(*(float *)&g_menuCamX) - tf);
	X u = c * g_frameTime * SPEED;
	(*(float *)&g_menuCamZ) = (float)((X)(*(float *)&g_menuCamZ) - u);
	(*(float *)&g_menuCameraPos) = (float)((X)(*(float *)&g_menuCameraPos) - tf);
	g_armcCamDistance = (float)((X)g_armcCamDistance - u);
}

/* the ARM CENTER's turn (0x90d1cc, degrees) as its sine and cosine, and kept in the slot's record (g_slotCams) */
static void turn_update(int slot)
{
	X a = (X)g_armcLookYaw * k_pi * k_oneOver180;
	g_armcLookSin = (float)x87_fsin(a);
	g_armcLookCos = (float)x87_fcos(a);
	volatile X t = g_armcLookYaw;
	F(OBJ(g_slotCams) + 0x28 + slot * 88) = (float)t;
}

/* 0x42ab70: the ARM CENTER's mouse look (unless locked, 0x4de6fc): the pointer's distance from the centre turns
   the view (wrapping 0 .. 360) and tilts it (0x4de6c4, within its limits); a click starts the camera's move to the
   slot's point */
void (armc_mouseLook)(void)
{
	if (g_watchChatOpen)
		return;
	int dx = 0x140 - g_mouseX, dy = 0xf0 - g_mouseY;
	int slot = g_watchedSlot;
	if (dx > 0) {
		X a = (X)dx * k_0_28125f * g_frameTime + g_armcLookYaw;
		g_armcLookYaw = (float)a;
		if (a > k_360f)
			(*(int *)&g_armcLookYaw) = 0;
		turn_update(slot);
	}
	if (dx < 0) {
		X a = (X)g_armcLookYaw - (X)(-dx) * k_0_28125f * g_frameTime;
		g_armcLookYaw = (float)a;
		if (!(a >= k_0f))
			(*(u32 *)&g_armcLookYaw) = 0x43b40000;   /* 360 */
		turn_update(slot);
	}
	if (dy > 0 && !(g_armcLookTilt >= k_50f))
		g_armcLookTilt = (float)((X)dy * k_tenth * g_frameTime + g_armcLookTilt);
	if (dy < 0 && g_armcLookTilt > k_m50f)
		g_armcLookTilt = (float)((X)dy * k_tenth * g_frameTime + g_armcLookTilt);
	if (g_mouseClick && !g_armcMoveStarted) {
		u32 r = OBJ(g_slotCams) + slot * 88;
		g_armcMoveStarted = 1;
		g_unusedArmcMoveWord = 0x41f00000;   /* 30 */
		g_armcMoveTargetX = I(r);
		g_armcMoveTargetY = I(r + 4);
		g_armcMoveTargetZ = I(r + 8);
		g_armcMoveEyeX = (float)((X)g_armcLookSin * k_2000f + F(r));
		g_armcMoveEyeY = I(r + 4);
		g_armcMoveEyeZ = (float)((X)g_armcLookCos * k_2000f + F(r + 8));
	}
}

/* 0x4230e0: the setup screen's camera: to the setup tab's menu point (mode 1; its height not eased), or home (mode
   0), then snapped and settled (mode 2) once close enough */
void (setup_camera)(void)
{
	if (g_frameTime > k_10f)
		g_frameTime = 1.0f;
	int mode = g_setupPage;
	X k = g_frameTime, c = RATE;
	if (mode == 1) {
		int i = g_setupTab * 16;
		(*(float *)&g_menuCameraPos) = (float)(((X)F(i + OBJ(g_camPoints)) - (*(float *)&g_menuCameraPos)) * k * c + (*(float *)&g_menuCameraPos));
		g_armcCamDistance = (float)(((X)F(i + (OBJ(g_camPoints) + 0x8)) - g_armcCamDistance) * k * c + g_armcCamDistance);
		X look = ((X)F(i + OBJ(g_camAims)) - (*(float *)&g_menuCameraLook)) * k * c + (*(float *)&g_menuCameraLook);
		(*(float *)&g_menuCameraLook) = (float)look;
		(*(float *)&g_menuCameraLookY) = (float)(((X)F(i + (OBJ(g_camAims) + 0x4)) - (*(float *)&g_menuCameraLookY)) * k * c + (*(float *)&g_menuCameraLookY));
		if (!(look >= k_0f))
			look = -look;
		if (!(look > k_69_9))
			return;
		for (int a = 0; a < 3; a++) {
			I(ADDR(g_menuCameraPos) + a * 4) = I(i + OBJ(g_camPoints) + a * 4);
		}
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuCameraLook) + a * 4) = I(i + OBJ(g_camAims) + a * 4);
		g_setupPage = 2;
		g_dialogOpen = 1;
	} else if (mode == 0) {
		(*(float *)&g_menuCameraPos) = (float)((X)(*(float *)&g_menuCameraPos) - ((X)(*(float *)&g_menuCameraPos) - (*(float *)&g_menuCameraX)) * k * c);
		g_armcCamDistance = (float)((X)g_armcCamDistance - ((X)g_armcCamDistance - (*(float *)&g_menuCameraZ)) * k * c);
		X look = (X)(*(float *)&g_menuCameraLook) - ((X)(*(float *)&g_menuCameraLook) - (*(float *)&g_menuLookAtX)) * k * c;
		(*(float *)&g_menuCameraLook) = (float)look;
		(*(float *)&g_menuCameraLookY) = (float)((X)(*(float *)&g_menuCameraLookY) - ((X)(*(float *)&g_menuCameraLookY) - (*(float *)&g_menuLookAtY)) * k * c);
		if (!(look >= k_0f))
			look = -look;
		if (look >= k_cameraSnapDistance)
			return;
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuCameraLook) + a * 4) = I(ADDR(g_menuLookAtX) + a * 4);
		g_setupPage = 2;
		for (int a = 0; a < 3; a++)
			I(ADDR(g_menuCameraPos) + a * 4) = I(ADDR(g_menuCameraX) + a * 4);
		g_setupTab = 0x29a;
	}
}

/* 0x42ada0: the free camera's keys (while watching): typing a chat line (0x4de6fc) until it is closed (0x68039c
   clear): then sent (net_sendChat, 0x9fd95c / 0x9fd948) unless empty and the keyboard taken back; 0x4defa8 opens the
   chat line (50 characters); the second cancel key leaves (a hosted game, 0xa0baf8, told first); the turn keys
   (0x4def00 / 0x4def08) slide the camera and the menu camera sideways (0x4de6c0, 0x4de6c8 at 0x4a9534 a frame),
   the move keys step it (menuCamera_forward / menuCamera_back); then the menu camera follows (0x680378 .. 0x680380 and the
   look-at 0x4df024 ..) and the camera's position is kept in the watched slot (0x4dfa1c, 0x58 bytes, by 0x9fd954);
   0x680388 toggles 0x4e0464 between 1 and 2, and four keys step 0x4de6e0 by 1 / 10 (not below 1). The original
   leaves eax to callers that ignore it */
void (freeCam_keys)(void)
{
	const float *frame = (const float *)ADDR(g_frameTime), *speed = (const float *)ADDR(k_3f);
	if (g_watchChatOpen) {
		if (g_textFieldOpen)
			return;
		if (strlen(g_chatLine)) {
			net_sendChat(g_chatLine);
			g_watchChatOpen = 0;
			g_chatLogged = 1;
			(*(u32 *)&g_chatLog) = OBJ(g_chatLine);
		} else {
			g_watchChatOpen = 0;
			g_chatLogged = 0;
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
		g_chatCaretX = 0x32;
		g_chatCaretY = 0x1cc;
		return;
	}
	if (input_justPressed(g_keyCancel2)) {
		if (g_isHost) {
			g_hostResultFlag = 1;
			net_sendMessage((void *)ADDR(g_resultMessage), 0, 0);
			g_hostResultFlag = 0;
		}
		g_unusedPostMatchFlag = 1;
		game_returnToMainMenu();
		return;
	}
	if (input_isDown(g_keyForward) == 1) {
		long double a = fmul_m(fmul_m(fld_m(frame), &g_armcLookSin), speed);
		(*(float *)&g_menuCamX) = f32(fadd_m(a, &(*(float *)&g_menuCamX)));
		long double b = fmul_m(fmul_m(fld_m(&g_armcLookCos), frame), speed);
		float bf = f32(b);
		(*(float *)&g_menuCamZ) = f32(fadd_m(b, &(*(float *)&g_menuCamZ)));
		(*(float *)&g_menuCameraPos) = f32(fadd_m(a, &(*(float *)&g_menuCameraPos)));
		g_armcCamDistance = f32(fadd_m(fld_m(&bf), &g_armcCamDistance));
	}
	if (input_isDown(g_keyBackward) == 1) {
		long double a = fmul_m(fmul_m(fld_m(frame), &g_armcLookSin), speed);
		(*(float *)&g_menuCamX) = f32(fld_m(&(*(float *)&g_menuCamX)) - a);
		float bf = f32(fmul_m(fmul_m(fld_m(&g_armcLookCos), frame), speed));
		(*(float *)&g_menuCamZ) = f32(fsub_m(fld_m(&(*(float *)&g_menuCamZ)), &bf));
		(*(float *)&g_menuCameraPos) = f32(fld_m(&(*(float *)&g_menuCameraPos)) - a);
		g_armcCamDistance = f32(fsub_m(fld_m(&g_armcCamDistance), &bf));
	}
	if (input_isDown(g_keyStepLeft) == 1)
		menuCamera_forward();
	if (input_isDown(g_keyStepRight) == 1)
		menuCamera_back();
	g_menuCameraLook = g_menuCamX;
	(*(u32 *)&g_menuCameraHeight) = g_menuCamZ;
	(*(float *)&g_menuCameraPos) = f32(fsubr_m(fmul_m(fld_m(&g_armcLookSin), (const float *)ADDR(k_50f)), &(*(float *)&g_menuCamX)));
	g_armcCamHeight = f32(fadd_m(fld_m(&g_freeCamHeight), (const float *)ADDR(k_10f)));
	u32 *slot = (u32 *)(OBJ(g_slotCams) + g_watchedSlot * 0x58);
	slot[0] = g_menuCamX;
	slot[1] = (*(u32 *)&g_freeCamHeight);
	slot[2] = g_menuCamZ;
	g_armcCamDistance = f32(fsubr_m(fmul_m(fld_m(&g_armcLookCos), (const float *)ADDR(k_50f)), &(*(float *)&g_menuCamZ)));
	(*(float *)&g_menuCameraLookY) = f32(fadd_m(fld_m(&g_armcLookTilt), &g_freeCamHeight));
	if (input_justPressed(g_dikZ_2) == 1)
		g_fovKeys = g_fovKeys == 1 ? 2 : 1;
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
