/* menu_cameras.c: the front end's camera moving between its home and a screen's menu point. The camera is a
   position (0x4df024) and a point it looks at (0x680378), three floats each; the menu points are 16 bytes apart
   from 0x4df870 (positions) and 0x76d388 (look-at points), the home at 0x9db090 / 0x76d3f8. Each frame the camera
   eases a share of the way (the frame's time times a rate) and snaps once close enough. The arithmetic is kept in
   the original's order and at x87 precision (long double). */
#include "../game.h"

typedef long double X;

#define F(a) GAME_VAR(float, a)
#define I(a) GAME_VAR(int, a)
/* g_viewAspect (game.h): the 3D view's aspect ratio, eased to the screen's while the camera moves */
#define SCREEN_ASPECT ((X)I(0x5b1998) / I(0x4e045c))
#define RATE F(0x4a93ec)                   /* the share eased per second */

static const u32 cam[6] = { 0x4df024, 0x4df028, 0x4df02c, 0x680378, 0x68037c, 0x680380 };
static const u32 home[6] = { 0x9db090, 0x9db094, 0x9db098, 0x76d3f8, 0x76d3fc, 0x76d400 };

/* the frame time limited to 1 second (above the constant at limit) */
static void limit_frame_time(u32 limit)
{
	if (g_frameTime > F(limit))
		BITS(g_frameTime) = 0x3f800000;
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
	limit_frame_time(0x4a93d0);
	int mode = I(m->mode);
	if (mode == 1) {
		int i = I(m->idx) * 16;
		X k = g_frameTime, c = RATE;
		F(0x4df024) = (float)(((X)F(i + 0x4df870) - F(0x4df024)) * k * c + F(0x4df024));
		if (!m->arena)
			F(0x4df028) = (float)(((X)F(i + 0x4df874) - F(0x4df028)) * k * c + F(0x4df028));
		F(0x4df02c) = (float)(((X)F(i + 0x4df878) - F(0x4df02c)) * k * c + F(0x4df02c));
		X look = ((X)F(i + 0x76d388) - F(0x680378)) * k * c + F(0x680378);
		F(0x680378) = (float)look;
		F(0x68037c) = (float)(((X)F(i + 0x76d38c) - F(0x68037c)) * k * c + F(0x68037c));
		if (!(look >= F(0x4a93e8)))
			look = -look;
		if (!(look > GAME_VAR(double, 0x4a93e0)))
			return;
		/* there: snapped to the point */
		if (!m->arena) {
			I(m->mode) = 2;
			I(0x4df024) = I(i + 0x4df870);
			I(0x4df028) = I(i + 0x4df874);
			I(0x4df02c) = I(i + 0x4df878);
			I(0x680378) = I(i + 0x76d388);
			I(0x68037c) = I(i + 0x76d38c);
			I(0x680380) = I(i + 0x76d390);
			g_dialogOpen = 1;
		} else {
			g_dialogOpen = 1;
			I(0x4df028) = I(i + 0x4df874);
			I(0x4df02c) = I(i + 0x4df878);
			volatile X x = F(i + 0x4df870);   /* fld / fst / fstp */
			I(0x4db844) = I(0x4df028);
			F(0x4df024) = (float)x;
			I(0x680378) = I(i + 0x76d388);
			I(0x68037c) = I(i + 0x76d38c);
			F(0x4db840) = (float)x;
			I(0x680380) = I(i + 0x76d390);
			I(0x4db848) = I(0x4df02c);
			I(m->mode) = 2;
			I(0x4dbab8) = I(0x680378);
			I(0x4dbabc) = I(0x68037c);
			I(0x4dbac0) = I(0x680380);
		}
		return;
	}
	if (mode != 0)
		return;
	X look = F(0x680378);
	if (!(look >= F(0x4a93e8)))
		look = -look;
	if (!(look >= GAME_VAR(double, 0x4a93d8))) {   /* close enough: snapped home */
		I(0x680378) = I(0x76d3f8);
		I(0x68037c) = I(0x76d3fc);
		I(0x680380) = I(0x76d400);
		I(m->mode) = 2;
		I(0x4df024) = I(0x9db090);
		I(0x4df028) = I(0x9db094);
		I(0x4df02c) = I(0x9db098);
		I(m->idx) = m->idxHome;
		if (I(0x67ef14) == 1)
			I(0x4deb74) = 0;
		else
			g_viewAspect = (float)((long double)I(0x5b1998) / I(0x4e045c));
		return;
	}
	if (I(0x67ef14) == 1) {
		limit_frame_time(0x4a93d0);
		GAME_VAR(u32, m->v150) = 0x43160000;   /* 150.0 */
	}
	for (int k = 0; k < 6; k++)
		ease_from(cam[k], home[k]);
}

/* 0x437a10: the game room's camera */
void (room_437a10)(void)
{
	static const MenuCam room = { 0x9dce48, 0x9dd834, 0x9dd848, 0x63, 0 };
	menu_camera(&room);
}

/* 0x408270: the arena lobby's camera */
void (arena_408270)(void)
{
	static const MenuCam arena = { 0x4dbb3c, 0x4db51c, 0x4dbaf4, 5, 1 };
	menu_camera(&arena);
}

/* ---- the skirmish and mission-select camera: to the first menu point and on to (0, -200, 1500), or home and
   back to the main menu (state 300) ---- */
typedef struct {
	u32 mode, flag, minus1;
	int mission;   /* the mission select: its state set before the rest */
} MenuCam2;

static const u32 point0[6] = { 0x4df870, 0x4df874, 0x4df878, 0x76d388, 0x76d38c, 0x76d390 };

static void menu_camera2(const MenuCam2 *m)
{
	limit_frame_time(0x4a9418);
	int mode = I(m->mode);
	if (mode == 1) {
		X k = g_frameTime, c = RATE;
		X last = 0;
		for (int i = 0; i < 6; i++) {
			last = ((X)F(point0[i]) - F(cam[i])) * k * c + F(cam[i]);
			F(cam[i]) = (float)last;
		}
		if (g_viewAspect > F(0x4a93e8))
			g_viewAspect = (float)((X)g_viewAspect - (X)g_frameTime * F(0x4a946c));
		if (!(last > F(0x4a9474)))
			return;
		X full = SCREEN_ASPECT;
		I(0x4df024) = 0;
		GAME_VAR(u32, 0x4df028) = 0xc3480000;   /* -200 */
		GAME_VAR(u32, 0x4df02c) = 0x44bb8000;   /* 1500 */
		I(0x680378) = 0;
		GAME_VAR(u32, 0x68037c) = 0xc3480000;
		I(0x680380) = 0;
		I(m->mode) = 2;
		I(m->flag) = 0;
		g_dialogOpen = 1;
		g_viewAspect = (float)full;
		return;
	}
	if (mode != 0)
		return;
	int fast = F(0x680380) > F(0x4a95d8);
	X c = fast ? F(0x4a93ec) : F(0x4a942c);
	I(m->flag) = 1;
	for (int i = 0; i < 6; i++)
		F(cam[i]) = (float)((X)F(cam[i]) - ((X)F(cam[i]) - F(home[i])) * g_frameTime * c);
	X full = SCREEN_ASPECT;
	if (!(g_viewAspect >= full))
		g_viewAspect = (float)((X)g_frameTime * F(fast ? 0x4a9468 : 0x4a9420) + g_viewAspect);
	if (F(0x680380) > F(0x4a95d4))
		return;
	/* home */
	I(0x680378) = I(0x76d3f8);
	I(0x68037c) = I(0x76d3fc);
	I(0x680380) = I(0x76d400);
	if (m->mission)
		I(m->mode) = 2;
	I(0x4df024) = I(0x9db090);
	I(0x4df028) = I(0x9db094);
	I(0x4df02c) = I(0x9db098);
	if (m->mission && I(0x67ef14) == 1)
		I(0x4deb74) = 0;
	g_viewAspect = (float)full;
	if (!m->mission)
		I(m->mode) = 2;
	I(m->minus1) = -1;
	g_menuState = 300;
	I(0x67ef0c) = 300;
	g_nextScreen = 300;
	I(0x4dda44) = 0;
}

/* 0x444130: the skirmish screen's camera */
void (skirmish_444130)(void)
{
	static const MenuCam2 skirmish = { 0x9ef1f0, 0x9eeba8, 0x9ef1f8, 0 };
	menu_camera2(&skirmish);
}

/* 0x447cb0: the mission select's camera */
void (missionsel_447cb0)(void)
{
	static const MenuCam2 mission = { 0x9f62f8, 0x9f63b8, 0x9f6300, 1 };
	menu_camera2(&mission);
}

/* ---- the free menu camera moved along its heading (the turn at 0x90d1cc, plus a quarter turn, wrapped, in radians)
   by the frame time times its speed ---- */
static X fsin(X x) { __asm__("fsin" : "+t"(x)); return x; }
static X fcos(X x) { __asm__("fcos" : "+t"(x)); return x; }

static X heading(void)
{
	X v = (X)F(0x90d1cc) + F(0x4a9550);
	if (v > F(0x4a9460))
		v -= F(0x4a9460);
	return v * (X)GAME_VAR(double, 0x4a9548) * (X)GAME_VAR(double, 0x4a9540);
}
#define SPEED F(0x4a9534)

/* 0x42aa30: forward (the camera's position 0x4de344 / 0x4de34c and the menu camera's) */
void (match_42aa30)(void)
{
	X a = heading();
	float s = (float)fsin(a);
	X c = fcos(a);
	X t = (X)g_frameTime * s * SPEED;
	float tf = (float)t;
	F(0x4de344) = (float)(t + F(0x4de344));   /* the unrounded step here ... */
	X u = c * g_frameTime * SPEED;
	F(0x4de34c) = (float)(u + F(0x4de34c));
	F(0x4df024) = (float)((X)tf + F(0x4df024));   /* ... the rounded one here */
	F(0x4df02c) = (float)(u + F(0x4df02c));
}

/* 0x42aad0: back (here every use of the sideways step is rounded) */
void (match_42aad0)(void)
{
	X a = heading();
	float s = (float)fsin(a);
	X c = fcos(a);
	float tf = (float)((X)g_frameTime * s * SPEED);
	F(0x4de344) = (float)((X)F(0x4de344) - tf);
	X u = c * g_frameTime * SPEED;
	F(0x4de34c) = (float)((X)F(0x4de34c) - u);
	F(0x4df024) = (float)((X)F(0x4df024) - tf);
	F(0x4df02c) = (float)((X)F(0x4df02c) - u);
}

/* the ARM CENTER's turn (0x90d1cc, degrees) as its sine and cosine, and kept in the slot's record (88 bytes from
   0x4dfa1c) */
static void turn_update(int slot)
{
	X a = (X)F(0x90d1cc) * GAME_VAR(double, 0x4a9548) * GAME_VAR(double, 0x4a9540);
	F(0x4de6c0) = (float)fsin(a);
	F(0x4de6c8) = (float)fcos(a);
	volatile X t = F(0x90d1cc);
	F(0x4dfa44 + slot * 88) = (float)t;
}

/* 0x42ab70: the ARM CENTER's mouse look (unless locked, 0x4de6fc): the pointer's distance from the centre turns
   the view (wrapping 0 .. 360) and tilts it (0x4de6c4, within its limits); a click starts the camera's move to the
   slot's point */
void (menu_42ab70)(void)
{
	if (I(0x4de6fc))
		return;
	int dx = 0x140 - g_mouseX, dy = 0xf0 - g_mouseY;
	int slot = GAME_VAR(u8, 0x9fd954);
	if (dx > 0) {
		X a = (X)dx * F(0x4a9564) * g_frameTime + F(0x90d1cc);
		F(0x90d1cc) = (float)a;
		if (a > F(0x4a9460))
			I(0x90d1cc) = 0;
		turn_update(slot);
	}
	if (dx < 0) {
		X a = (X)F(0x90d1cc) - (X)(-dx) * F(0x4a9564) * g_frameTime;
		F(0x90d1cc) = (float)a;
		if (!(a >= F(0x4a93e8)))
			GAME_VAR(u32, 0x90d1cc) = 0x43b40000;   /* 360 */
		turn_update(slot);
	}
	if (dy > 0 && !(F(0x4de6c4) >= F(0x4a9560)))
		F(0x4de6c4) = (float)((X)dy * F(0x4a955c) * g_frameTime + F(0x4de6c4));
	if (dy < 0 && F(0x4de6c4) > F(0x4a9558))
		F(0x4de6c4) = (float)((X)dy * F(0x4a955c) * g_frameTime + F(0x4de6c4));
	if (g_mouseClick && !I(0x4de340)) {
		u32 r = 0x4dfa1c + slot * 88;
		I(0x4de340) = 1;
		GAME_VAR(u32, 0x4de6f0) = 0x41f00000;   /* 30 */
		I(0x4de6d0) = I(r);
		I(0x4de6d4) = I(r + 4);
		I(0x4de6d8) = I(r + 8);
		F(0x4de350) = (float)((X)F(0x4de6c0) * F(0x4a9554) + F(r));
		I(0x4de354) = I(r + 4);
		F(0x4de358) = (float)((X)F(0x4de6c8) * F(0x4a9554) + F(r + 8));
	}
}

/* 0x4230e0: the setup screen's camera: to the setup tab's menu point (mode 1; its height not eased), or home (mode
   0), then snapped and settled (mode 2) once close enough */
void (setup_4230e0)(void)
{
	if (g_frameTime > F(0x4a9418))
		BITS(g_frameTime) = 0x3f800000;
	int mode = I(0x4ddcec);
	X k = g_frameTime, c = RATE;
	if (mode == 1) {
		int i = I(0x4ddac8) * 16;
		F(0x4df024) = (float)(((X)F(i + 0x4df870) - F(0x4df024)) * k * c + F(0x4df024));
		F(0x4df02c) = (float)(((X)F(i + 0x4df878) - F(0x4df02c)) * k * c + F(0x4df02c));
		X look = ((X)F(i + 0x76d388) - F(0x680378)) * k * c + F(0x680378);
		F(0x680378) = (float)look;
		F(0x68037c) = (float)(((X)F(i + 0x76d38c) - F(0x68037c)) * k * c + F(0x68037c));
		if (!(look >= F(0x4a93e8)))
			look = -look;
		if (!(look > GAME_VAR(double, 0x4a93e0)))
			return;
		for (int a = 0; a < 3; a++) {
			I(0x4df024 + a * 4) = I(i + 0x4df870 + a * 4);
		}
		for (int a = 0; a < 3; a++)
			I(0x680378 + a * 4) = I(i + 0x76d388 + a * 4);
		I(0x4ddcec) = 2;
		g_dialogOpen = 1;
	} else if (mode == 0) {
		F(0x4df024) = (float)((X)F(0x4df024) - ((X)F(0x4df024) - F(0x9db090)) * k * c);
		F(0x4df02c) = (float)((X)F(0x4df02c) - ((X)F(0x4df02c) - F(0x9db098)) * k * c);
		X look = (X)F(0x680378) - ((X)F(0x680378) - F(0x76d3f8)) * k * c;
		F(0x680378) = (float)look;
		F(0x68037c) = (float)((X)F(0x68037c) - ((X)F(0x68037c) - F(0x76d3fc)) * k * c);
		if (!(look >= F(0x4a93e8)))
			look = -look;
		if (look >= GAME_VAR(double, 0x4a93d8))
			return;
		for (int a = 0; a < 3; a++)
			I(0x680378 + a * 4) = I(0x76d3f8 + a * 4);
		I(0x4ddcec) = 2;
		for (int a = 0; a < 3; a++)
			I(0x4df024 + a * 4) = I(0x9db090 + a * 4);
		I(0x4ddac8) = 0x29a;
	}
}
