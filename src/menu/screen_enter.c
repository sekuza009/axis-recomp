/* screen_enter.c: the front end's screens set up as they are entered: the main menu (state 300), the arena lobby
   (400), the setup screen (600) and the game room (800). Each lays out its panels (origins in menu units, then the
   screen's rectangle builders), sets its colours (RGBA floats), points the menu camera's target and look-at points
   at the screen (all at the camera's height) with the camera's current place as home, and clears its state. */
#include "../game.h"
#include <string.h>

#define I(a) GAME_VAR(int, a)
#define U(a) GAME_VAR(u32, a)
#define ONE 0x3f800000u

typedef struct { u32 address, value; } Store;

static void store_all(const Store *s, int n)
{
	for (int i = 0; i < n; i++)
		U(s[i].address) = s[i].value;
}
static void clear_all(const u32 *a, int n)
{
	for (int i = 0; i < n; i++)
		I(a[i]) = 0;
}
#define STORE_ALL(table) store_all(table, sizeof table / sizeof table[0])
#define CLEAR_ALL(table) clear_all(table, sizeof table / sizeof table[0])

/* the camera's target points 0 .. n-1 (16 bytes apart from 0x4df870, look-at points from 0x76d388) at its height,
   and the current position as home (0x9db090) */
static void camera_heights(int n)
{
	int z = I(0x680380);
	for (int i = 0; i < n; i++) {
		I(0x4df878 + i * 0x10) = z;
		I(0x76d390 + i * 0x10) = z;
	}
	I(0x9db090) = I(0x4df024);
	I(0x9db094) = I(0x4df028);
	I(0x9db098) = I(0x4df02c);
}

/* the four target and look-at points of the lobby and setup screens: (+-35, 0) looking at (-+70, +-35) */
static const Store camera4[] = {
	{ 0x4df870, 0x420c0000 }, { 0x4df874, 0 }, { 0x76d388, 0xc28c0000 }, { 0x76d38c, 0x420c0000 },
	{ 0x4df880, 0x420c0000 }, { 0x4df884, 0 }, { 0x76d398, 0xc28c0000 }, { 0x76d39c, 0xc20c0000 },
	{ 0x4df890, 0xc20c0000 }, { 0x4df894, 0 }, { 0x76d3a8, 0x428c0000 }, { 0x76d3ac, 0x420c0000 },
	{ 0x4df8a0, 0xc20c0000 }, { 0x4df8a4, 0 }, { 0x76d3b8, 0x428c0000 }, { 0x76d3bc, 0xc20c0000 } };

/* 0x440bb0: the main menu: its camera (-300), its limits, colours, fade */
void (menuState300_enter)(void)
{
	U(0x9eea90) = 0xc3960000;   /* -300 */
	I(0x9eeab0) = 0;
	U(0x4b0704) = 0x41200000;   /* 10 */
	U(0x4b0708) = 0x42400000;   /* 48 */
	U(0x4b070c) = 0x3e4ccccd;   /* 0.2 */
	U(0x4b0710) = 0xbe4ccccd;   /* -0.2 */
	I(0x4dda44) = 0;
	I(0x9dda80) = 0;
	U(0x9dd948) = 0x3d4ccccd;   /* 0.05 */
	I(0x9eea8c) = 0;
	I(0x9eeab4) = 0;
	I(0x9eea98) = 0;
	U(0x9eea9c) = ONE;
	U(0x9eeaa0) = ONE;
	U(0x9eeaa4) = ONE;
	U(0x9dda70) = 0x3e99999a;   /* (0.3, 0.7, 0.7, 1) */
	U(0x9dda74) = 0x3f333333;
	U(0x9dda78) = 0x3f333333;
	U(0x9dda7c) = ONE;
	I(0x5ae9c4) = 0;
}

/* 0x404640: the arena lobby */
void (menuState400_enter)(void)
{
	static const Store layout[] = {
		{ 0x4dbb60, 0 }, { 0x4db51c, 5 }, { 0x4dba70, 0x50 }, { 0x4dba74, 0x96 }, { 0x4dba78, 0x230 }, { 0x4dba7c, 0x15e },
		{ 0x4dbb70, 0x21c }, { 0x4dbb74, 0x190 }, { 0x4db8d0, 0x262 }, { 0x4dbb00, 0x28 }, { 0x4dbb04, 0x1e },
		{ 0x4dbb08, 0x258 } };
	static const u32 cleared1[] = { 0x4dbbd0, 0x4dbab0, 0x4db850, 0x4db518, 0x4dbacc, 0x4dba90, 0x4db858, 0x4dbac8,
	                                0x4dbaa8, 0x67ef30, 0x4dba80 };
	static const u32 cleared2[] = { 0x76d41c, 0x680bb0, 0x4df818, 0x4dba84, 0x4db854, 0x4dba98, 0x907b2c, 0x4dbbf4 };
	static const Store state[] = {
		{ 0x4dbb3c, 2 }, { 0x907b24, 999 }, { 0x4dba9c, ONE }, { 0x4dbaa0, ONE }, { 0x4dbaa4, ONE },
		{ 0x4db8a0, 0x3e99999a }, { 0x4db8a4, 0x3f333333 }, { 0x4db8a8, 0x3f333333 }, { 0x4db8ac, ONE }, { 0x9fd958, 0xf },
		{ 0x4dc24c, 1 } };
	I(0x5ae9c4) = 1;
	arena_4045e0();
	I(0x4dbb68) = 0x64;
	I(0x4dbb6c) = 0x64;
	I(0x4dda44) = 0;
	I(0x4db8c8) = 0x14;
	I(0x4db8cc) = 0x14;
	U(0x4dba68) = 0xc4af0000;   /* -1400 */
	I(0x4db8d4) = 0x1c2;
	I(0x4dbb0c) = 0x1c2;
	I(0x4db85c) = 1;
	camera_heights(4);
	int lx = I(0x680378), ly = I(0x68037c), lz = I(0x680380);
	STORE_ALL(layout);
	STORE_ALL(camera4);
	I(0x76d3f8) = lx;
	I(0x76d3fc) = ly;
	I(0x76d400) = lz;
	CLEAR_ALL(cleared1);
	arena_403f30();
	arena_403f80();
	arena_404010();
	arena_404120();
	arena_404190();
	arena_404150();
	CLEAR_ALL(cleared2);
	STORE_ALL(state);
}

/* 0x420770: the setup screen: its layout, camera, colours, and the two option columns' texts (0x80 apart in the
   text block at 0x75b5a4) */
void (menuState600_enterSetup)(void)
{
	static const Store layout[] = {
		{ 0x4ddac8, 0x29a }, { 0x4ddd90, 0xc4af0000 }, { 0x4dda60, 1 }, { 0x4de03c, 0 }, { 0x4ddcec, 2 },
		{ 0x4ddad0, 0x32 }, { 0x4ddad4, 0x3c }, { 0x4ddadc, 0x1a4 }, { 0x4dddd0, 0x64 }, { 0x4dddd8, 0x21c },
		{ 0x4ddddc, 0x1c2 }, { 0x4dde80, 0x28 }, { 0x4dde8c, 0x1b8 } };
	static const Store colours[] = {
		{ 0x4de048, 0 }, { 0x4de04c, ONE }, { 0x4de050, ONE }, { 0x4de054, ONE }, { 0x4ddae0, 0 },
		{ 0x4ddae4, 0x3f19999a }, { 0x4ddae8, 0x3f19999a }, { 0x4ddaec, ONE }, { 0x4e14fc, 0 }, { 0x4deda8, ONE },
		{ 0x9db978, 0 }, { 0x4df010, ONE } };
	I(0x4dddd4) = 0x1e;
	I(0x4dde84) = 0x1e;
	I(0x4ddad8) = 0x24e;
	I(0x4dde88) = 0x24e;
	camera_heights(4);
	int lx = I(0x680378), ly = I(0x68037c), lz = I(0x680380);
	STORE_ALL(layout);
	STORE_ALL(camera4);
	I(0x76d3f8) = lx;
	I(0x76d3fc) = ly;
	I(0x76d400) = lz;
	setup_420300();
	setup_420480();
	setup_420510();
	STORE_ALL(colours);
	for (int k = 0; k < 2; k++) {
		const char *text = (const char *)(0x75b7a4 + k * 0x80);
		int o = k * 0x32;
		strcpy((char *)(0x4ddbbc + o), text - 0x200);
		strcpy((char *)(0x4dda64 + o), text - 0x100);
		strcpy((char *)(0x4ddc84 + o), text);
		strcpy((char *)(0x4de058 + o), text);
		strcpy((char *)(0x4ddc20 + o), text);
		strcpy((char *)(0x4ddaf0 + o), text);
	}
}

/* 0x432ff0: the game room: all its panels laid out, colours, the five camera points ((+-20, +-10) looking at
   (-+70, +-55)), the room's record and state cleared, 999 rooms */
void (menuState800_enterGameRoom)(void)
{
	static const Store layout[] = {
		{ 0x9dd698, 0xc4af0000 }, { 0x9dd7d8, 1 }, { 0x9dd560, 0 }, { 0x9dce48, 2 }, { 0x9dd6bc, 0x3f333333 },
		{ 0x9dd834, 0x42 }, { 0x4dba88, 0 }, { 0x9dd358, 0x32 }, { 0x9dd35c, 0x6e }, { 0x9dd360, 0x24e },
		{ 0x9dd364, 0x172 }, { 0x9dd368, 0x3c }, { 0x9dd36c, 0x1e }, { 0x9dd370, 0x244 }, { 0x9dd374, 0x1c2 },
		{ 0x9dd4a8, 0x14 }, { 0x9dd4ac, 0x28 }, { 0x9dd4b0, 0x26c }, { 0x9dd4b4, 0x1b8 }, { 0x9dd1b8, 0x28 },
		{ 0x9dd1bc, 0x1e }, { 0x9dd1c0, 0x258 }, { 0x9dd1c4, 0x1c2 }, { 0x9dced8, 0x10 }, { 0x9dcedc, 0x1e },
		{ 0x9dcee0, 0x268 }, { 0x9dcee4, 0x1b8 } };
	static const Store colours_camera[] = {
		{ 0x4ded60, 2 }, { 0x9dcec0, 0 }, { 0x9dcec4, ONE }, { 0x9dcec8, ONE }, { 0x9dcecc, ONE },
		{ 0x9dd338, 0x3e99999a }, { 0x9dd33c, 0x3f333333 }, { 0x9dd340, 0x3f333333 }, { 0x9dd344, ONE },
		{ 0x4df870, 0x41a00000 }, { 0x4df874, 0xc1200000 }, { 0x76d388, 0xc28c0000 }, { 0x76d38c, 0x425c0000 },
		{ 0x4df880, 0x41a00000 }, { 0x4df884, 0 }, { 0x76d398, 0xc28c0000 }, { 0x76d39c, 0 },
		{ 0x4df890, 0x41a00000 }, { 0x4df894, 0x41200000 }, { 0x76d3a8, 0xc28c0000 }, { 0x76d3ac, 0xc25c0000 },
		{ 0x4df8a0, 0xc1a00000 }, { 0x4df8a4, 0xc1200000 }, { 0x76d3b8, 0x428c0000 }, { 0x76d3bc, 0x425c0000 },
		{ 0x4df8b0, 0xc1a00000 }, { 0x4df8b4, 0 }, { 0x76d3c8, 0x428c0000 }, { 0x76d3cc, 0 } };
	static const u32 cleared[] = { 0x9dd838, 0x9dd6a4, 0x9dd1b0, 0x4ded54, 0x9dd1c8, 0x9dd350, 0x9dd84c, 0x9dd6d4,
	                               0x9dd850 };
	I(0x5ae9c4) = 2;
	arena_4045e0();
	STORE_ALL(layout);
	room_431ae0();
	room_431c50();
	room_431ce0();
	room_431db0();
	room_431de0();
	room_432040();
	room_431aa0();
	STORE_ALL(colours_camera);
	camera_heights(5);
	I(0x76d3f8) = I(0x680378);
	I(0x76d3fc) = I(0x68037c);
	I(0x76d400) = I(0x680380);
	memset((void *)0x9dd5a6, 0, 7 * 4 + 2);
	I(0x9dd58e) = 0;
	I(0x9dd592) = 0;
	I(0x9dd596) = 0;
	I(0x9dd830) = 0;
	I(0x9dd38c) = 1;
	memset((void *)0x9dd5f8, 0, 5);
	I(0x9dd6b0) = 1;
	I(0x9dd1cc) = 0;
	I(0x9dd198) = 0;
	room_432be0();
	I(0x9dced0) = 1;
	CLEAR_ALL(cleared);
	I(0x9dd4b8) = 999;
}

/* ---- the front end's per-frame dispatch ---- */
#define CALL(addr) GAME_CDECL(addr, u32, void)()

/* 0x445e40: the frame's input (0x445c60), then, unless the game is leaving (0x680370), the message box's keys while
   it is shown, else the current screen's (0x76d3e8): 200 the title, 210 profiles, 300 the main menu, 400 the lobby,
   500 missions, 600 setup, 700 the ARM CENTER, 800 the game room, 900 skirmish, 9999 in a match. Returns what the
   handler leaves in eax (or the original's leftover of its compares) */
u32 (menu_onStateChange)(void)
{
	CALL(0x445c60);
	if (GAME_VAR(int, 0x680370))
		return GAME_VAR(u32, 0x680370);
	if (GAME_VAR(int, 0x4df900))
		return CALL(0x445e10);   /* the message box */
	int state = g_menuState;
	switch (state) {
	case 200: return CALL(0x445de0);
	case 210: return CALL(0x44c560);   /* profile_processInput */
	case 300: return CALL(0x4419d0);
	case 400: return CALL(0x4076c0);   /* lobby_onStateChange */
	case 500: return CALL(0x447b10);
	case 600: return CALL(0x422b30);
	case 700: return CALL(0x410190);   /* armc_onStateEnter */
	case 800: return CALL(0x436800);   /* room_processKeys */
	case 900: return CALL(0x443ef0);
	case 9999: return CALL(0x42ab70);  /* menu_42ab70 */
	}
	/* the original's subtraction chain leaves these */
	if (state > 900)
		return (u32)state;
	if (state > 600)
		return (u32)(state - 800);
	if (state > 300)
		return (u32)(state - 500);
	return (u32)(state - 210);
}

/* 0x41f970: a screen entered: its set-up by the state (0x76d3e8; the main menu also flags 0x4deb48), the state kept as
   the one before (0x67ef0c). Returns the state */
u32 (menu_enterState)(void)
{
	switch (g_menuState) {
	case 210: CALL(0x44b420); break;   /* menuState210_enter */
	case 300:
		GAME_VAR(int, 0x4deb48) = 1;
		CALL(0x440bb0);                 /* menuState300_enter */
		break;
	case 400: CALL(0x404640); break;   /* menuState400_enter */
	case 500: CALL(0x447750); break;   /* menuState500_enter */
	case 600: CALL(0x420770); break;   /* menuState600_enterSetup */
	case 800: CALL(0x432ff0); break;   /* menuState800_enterGameRoom */
	case 900: CALL(0x443950); break;   /* menuState900_enterSkirmish */
	case 9999: CALL(0x41fd40); break;  /* console_init */
	}
	GAME_VAR(int, 0x67ef0c) = g_menuState;
	return (u32)g_menuState;
}


/* the skirmish and mission screens' camera: at (0, 0, -450) moving to (0, 0, -550), that place its home, one target
   point (0, 0, 100) looking at the origin */
static const Store briefing_camera[] = {
	{ 0x4df024, 0 }, { 0x4df028, 0 }, { 0x4df02c, 0xc3e10000 }, { 0x680378, 0 }, { 0x68037c, 0 },
	{ 0x680380, 0xc4098000 }, { 0x4df870, 0 }, { 0x4df874, 0 }, { 0x4df878, 0x42c80000 }, { 0x76d388, 0 },
	{ 0x76d38c, 0 }, { 0x76d390, 0 }, { 0x9db090, 0 }, { 0x9db094, 0 }, { 0x9db098, 0xc3e10000 }, { 0x76d3f8, 0 },
	{ 0x76d3fc, 0 }, { 0x76d400, 0xc4098000 } };

/* 0x443950: the skirmish setup (screen 900): the briefing camera, the briefing window and its colours, the page's
   panels (skirmish_4437b0, skirmish_443840), the page set to 10 (skirmish settings) with a sound, the mission list
   loaded (mission_loadAxisMis) and its state cleared. Returns 0 (the original's eax) */
int (menuState900_enterSkirmish)(void)
{
	static const Store setup[] = {
		{ 0x9f16a8, 0xa }, { 0x9f16ac, 0x14 }, { 0x9f16b0, 0x276 }, { 0x9f16b4, 0x1cc }, { 0x9ef208, 0 },
		{ 0x9ef20c, ONE }, { 0x9ef210, ONE }, { 0x9ef214, ONE }, { 0x9eeac8, 0 }, { 0x9eeacc, 0x3f19999a },
		{ 0x9eead0, 0x3f19999a }, { 0x9eead4, ONE }, { 0x9ef1f0, 1 }, { 0x76d3e8, 900 }, { 0x67ef0c, 900 },
		{ 0x67ef20, 900 } };
	static const u32 cleared[] = { 0x9f16bc, 0x9f1058, 0x9f16a4, 0x680bb4, 0x76d37c };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	GAME_CDECL(0x4437b0, void, void)();   /* skirmish_4437b0 */
	GAME_CDECL(0x443840, void, void)();   /* skirmish_443840 */
	I(0x9eeba8) = 1;
	I(0x9ef1f8) = 10;
	sound_playMenu(4);
	GAME_CDECL(0x4435f0, void, void)();   /* mission_loadAxisMis */
	CLEAR_ALL(cleared);
	return 0;
}

/* 0x447750: the mission select (screen 500): the briefing camera, the window and its colours, the screen's panels
   (mission_447660), the mission shown (0x9f63b4, 0x9f6328) the campaign's next one (0x9f181c, at most 14), a sound;
   a newly reached mission (past 0x9f62fc) raises it and the briefing flag 0x9f62e0. Returns the campaign's mission */
int (menuState500_enter)(void)
{
	static const Store setup[] = {
		{ 0x9f6308, 0x28 }, { 0x9f630c, 0xa }, { 0x9f6310, 0x258 }, { 0x9f6314, 0x1cc }, { 0x9f6318, 0 },
		{ 0x9f631c, ONE }, { 0x9f6320, ONE }, { 0x9f6324, ONE }, { 0x9f62e8, 0 }, { 0x9f62ec, 0x3f19999a },
		{ 0x9f62f0, 0x3f19999a }, { 0x9f62f4, ONE }, { 0x9f62f8, 1 }, { 0x76d3e8, 500 }, { 0x67ef0c, 500 },
		{ 0x67ef20, 500 } };
	STORE_ALL(briefing_camera);
	STORE_ALL(setup);
	GAME_CDECL(0x447660, void, void)();   /* mission_447660 */
	I(0x9f63b8) = 1;
	I(0x9f6300) = 0;
	int mission = I(0x9f181c) < 15 ? I(0x9f181c) : 14;
	I(0x9f63b4) = mission;
	I(0x9f6328) = mission;
	I(0x9f63b0) = 1;
	sound_playMenu(4);
	I(0x9f62e0) = 0;
	if (I(0x9f181c) > I(0x9f62fc)) {
		I(0x9f62e0) = 1;
		I(0x9f62fc) = I(0x9f181c);
	}
	return I(0x9f181c);
}
