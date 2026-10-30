/* match_start.c: a match's rounds started: the first round sets up the mode, the map rotation and the local
   player; each later round picks new starting points and resets the round's state. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

#define g_mapIndex GAME_VAR(int, 0x9dad94)

static void set_round(Round *r, int map, int mode, int score, int time)
{
	r->map = map;
	r->mode = mode;
	r->scoreLimit = score;
	r->timeLimit = time;
}

/* the first round's map rotation: solo, the 15 stages (0x5c-byte records from 0x9db9e4: the mode, the time and the
   score limits) from the stage chosen (0x9dad94); a network host, the arena maps in rotation (0x67ef00 of them, 8
   bytes each from 0x4d9508: in rotation, the map's own mode, used when the chosen mode 0x76d368 is 14 or more) or,
   without rotation (0x9da3e0), the chosen map only, from the first; a machine that joined, none */
static void make_rotation(Scene *s)
{
	if (s->network == 0) {
		s->rotationCount = 0;
		int k;
		for (k = 0; k < 15; k++) {
			u32 stage = 0x9db9e4 + k * 0x5c;
			set_round(&s->rotation[s->rotationCount++], k, GAME_VAR(int, stage), GAME_VAR(int, stage + 8), GAME_VAR(int, stage + 4));
		}
		s->rotationAt = g_mapIndex;
		s->nextMap = k + 1;   /* (beyond the 15, as the original has it) */
		s->nextMode = GAME_VAR(int, 0x9db9e4 + (k + 1) * 0x5c);
		s->rotationOff = 0;
		return;
	}
	if (s->network != 1 || s->client) {
		s->rotationCount = 0;
		s->rotationAt = 0;
		s->rotationOff = 1;
		return;
	}
	if (GAME_VAR(int, 0x9da3e0) == 1) {
		s->rotationCount = 0;
		for (int k = 0; k < GAME_VAR(int, 0x67ef00); k++) {
			u32 entry = 0x4d9508 + k * 8;
			if (GAME_VAR(int, entry) != 1)
				continue;
			int mode = GAME_VAR(int, 0x76d368);
			if (mode >= 14)
				mode = GAME_VAR(int, entry + 4);
			set_round(&s->rotation[s->rotationCount++], k, mode, GAME_VAR(int, 0x4df8e8), GAME_VAR(int, 0x76d408));
		}
	} else {
		s->rotationCount = 1;
		set_round(&s->rotation[0], g_mapIndex, GAME_VAR(int, 0x76d368), GAME_VAR(int, 0x4df8e8), GAME_VAR(int, 0x76d408));
	}
	s->rotationAt = 0;
	g_mapIndex = s->rotation[0].map;
	int next = (s->rotationAt + 1) % s->rotationCount;   /* (none in rotation divides by zero, as in the original) */
	s->nextMap = s->rotation[next].map;
	s->nextMode = s->rotation[next].mode;
	s->rotationOff = 0;
}

/* the first round: emblems in the ranking for a room game (0x5ae9c4 2: 300 seconds of them, a game counted at
   0x4de72a), the rotation, the limits, the mech (its name 0x4dedd8, value, parts, items and the five colour sets),
   the room's level (from its points 0x4de722; outside 1 .. 20 fatal); then a network host makes its player 0, a
   machine that joined has none yet, and a solo game makes player 0 with rotation on (0x9da3e0) */
static void first_round(Scene *s)
{
	s->showEmblems = GAME_VAR(int, 0x5ae9c4) == 2;
	if (s->showEmblems == 1) {
		BITS(s->emblemTime) = 0x43960000;   /* 300 */
		GAME_VAR(int, 0x4de72a)++;
		FIELD(int, s, 0x22e717c) = 1;        /* (in projection's last dword) */
	} else
		FIELD(int, s, 0x22e717c) = 0;
	make_rotation(s);
	if (s->rotationCount > 0)
		game_setGameTypeFlags(STAGE(s), s->rotation[s->rotationAt].mode);
	s->scoreLimit = GAME_VAR(int, 0x4df8e8);
	s->timeLimit = GAME_VAR(int, 0x76d408);
	strcpy(s->mechName, (const char *)0x4dedd8);
	s->mechValue = GAME_VAR(int, 0x9f1818);
	if (s->showEmblems == 1) {
		s->levelPoints = GAME_VAR(int, 0x4de722);
		s->level = actor_levelFromValue(s->levelPoints);
		if (s->level < 1 || s->level > 20)
			sys_fatalError((char *)0xa0e778, (const char *)0x4d0710, s->level);
	} else {
		s->levelPoints = 0;
		s->level = 1;
	}
	for (int k = 0; k < 5; k++)
		s->mechParts[k] = GAME_VAR(int, 0x4dc878 + k * 4);
	static const u32 items[6] = { 0x4dcf20, 0x4dcf24, 0x4dcf28, 0x4dcf2c, 0x4dcf18, 0x4dcf1c };
	for (int k = 0; k < 6; k++)
		s->mechItems[k] = GAME_VAR(int, items[k]);
	/* the five colour sets (six dwords each from 0x4dcfe0) into three tables of pairs (0x2342476, 0x234249e,
	   0x23424c6): set i's dwords 0 / 3, 1 / 4 and 2 / 5 */
	for (int i = 0; i < 5; i++)
		for (int t = 0; t < 3; t++) {
			FIELD(u32, s, 0x2342476 + t * 0x28 + i * 8) = GAME_VAR(u32, 0x4dcfe0 + i * 0x18 + t * 4);
			FIELD(u32, s, 0x234247a + t * 0x28 + i * 8) = GAME_VAR(u32, 0x4dcfec + i * 0x18 + t * 4);
		}
	if (s->network == 1) {
		if (!s->client) {
			FUN_004a8300(1);
			s->localPlayer = 0;
			actor_resetSlot(STAGE(s), 0);
			player_setName(STAGE(s), s->localPlayer, s->mechName);
			strcpy(s->players[s->localPlayer].name, s->mechName);
			s->players[s->localPlayer].flagOwner = s->localPlayer;
		} else {
			FUN_004a8300(0);
			s->localPlayer = -1;
			g_mapIndex = -1;
			s->nextMap = -1;
			s->nextMode = -1;
		}
		memset(s->firstRoundClear, 0, sizeof s->firstRoundClear);
		s->rankingShown = 1;
	} else {
		GAME_VAR(int, 0x9fd94c) = 0;
		s->localPlayer = 0;
		player_setName(STAGE(s), 0, s->mechName);
		s->soloClear = 0;
		GAME_VAR(int, 0x9da3e0) = 1;
		s->rankingShown = 0;
	}
	s->startClear = 0;
	s->stageCleared = 0;
}

/* a random position below n (from the game's table of rand() values, 0xa106f8, at 0xa1efb8), 0 when n is none */
static int random_below(u32 n)
{
	if ((int)n <= 0)
		return 0;
	u32 at = GAME_VAR(u32, 0xa1efb8);
	u32 r = GAME_VAR(u32, 0xa106f8 + (at & 0xfff) * 4);
	GAME_VAR(u32, 0xa1efb8) = at + 1;
	return (int)(r % n);
}

/* a later round: a random position in each of the six geometry tables (their counts at +0x15de6c8 .., rows of
   0x2aa .. 0xb86 dwords), the restart point, the round's tables copied (cameraMode counting through them, as in the
   original), the camera back to mode 1, nobody watched, the pointer centred, the volumes (0x4e0c90, 0x4e0c94) set
   again, the local player's statD8 cleared, the teams (match_4613a0), the camera and its slot, a typed chat line
   kept (match_44ace0) and the round's flags cleared */
static void later_round(Scene *s)
{
	static const u32 counts[6] = { 0x15de6c8, 0x15fff84, 0x163b588, 0x1679b34, 0x16c5178, 0x175522c };
	static const u32 rows[6] = { 0x2aa, 0x2af, 0x4c0, 0x4fd, 0x608, 0xb86 };
	s->roundClear = 0;
	for (int k = 0; k < 6; k++)
		s->geometryPick[k] = random_below(((u32)FIELD(int, s, counts[k]) * rows[k] * 4) >> 2);
	s->roundClear2 = 0;
	s->dataLossCode = -1;
	s->roundClear3 = 0;
	BITS(s->chatBlink) = 0;
	BITS(s->roundTimer) = 0x40400000;   /* 3 */
	for (int k = 0; k < 3; k++)
		s->restartA[k] = s->restartFrom[k];
	s->restartB[0] = s->restartFrom[3];
	s->restartB[1] = s->restartFrom[4];
	for (s->cameraMode = 0; s->cameraMode < 10; s->cameraMode++)
		for (int t = 0; t < 6; t++)
			s->roundArrays[t][s->cameraMode] = s->restartArrays[t][s->cameraMode];
	s->cameraMode = 1;
	FUN_0045dfb0(STAGE(s), -1);
	s->watchedPlayer = -1;
	memset(s->watchClear, 0, sizeof s->watchClear);
	s->playing = 0;
	(void)timer_getGameTime((u8 *)s + 0xc);
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
	FUN_00456de0(GAME_VAR(int, 0x4e0c90));
	set_4b42dc_457140(GAME_VAR(int, 0x4e0c94));
	s->roundClear4 = 0;
	s->teamAsked = 0;
	if (s->localPlayer >= 0)
		s->players[s->localPlayer].statD8 = 0;
	match_4613a0(s, -1);
	s->startCameraMode = s->cameraMode;
	s->cameraSlot = -1;   /* (the -1 still in a register since dataLossCode) */
	s->rankShown = -1;
	match_4620e0(s);
	match_4629c0(s, 60.0f);
	s->chatMode = 0;
	if (GAME_VAR(int, 0x68039c))
		match_44ace0();
	s->roundClear5 = 0;
	s->matchOver = 0;
	s->roundClear6 = 0;
	s->roundOver = 0;
	s->roundClear7 = 0;
	match_4636d0(s);
	BITS(s->msgFade) = 0;
}

/* 0x49df10 (thiscall on the scene): the round started, the first (frameFlag clear) or a later one. Its caller
   ignores the eax it leaves */
void THISCALL (game_processGameModeInit)(Scene *s)
{
	if (s->frameFlag)
		later_round(s);
	else
		first_round(s);
}

/* 0x4732f0 (thiscall on the scene): game type t (+0x20f3ab8) and its rule flags (+0x20f3abc .. +0x20f3ad8, cleared
   first): the odd types 1 .. 13 set +0x20f3abc; types 2 .. 11 by pairs set one of +0x20f3ac0 .. +0x20f3ad0, 12 sets
   +0x20f3ad4 and 13 +0x20f3ad8. Its callers ignore the eax it leaves */
void THISCALL (game_setGameTypeFlags)(u8 *scene, int t)
{
	static const u16 second[14] = { 0, 0, 0x20f3ac0 - 0x20f3ab8, 0x20f3ac0 - 0x20f3ab8, 0x20f3ac4 - 0x20f3ab8, 0x20f3ac4 - 0x20f3ab8,
		0x20f3ac8 - 0x20f3ab8, 0x20f3ac8 - 0x20f3ab8, 0x20f3acc - 0x20f3ab8, 0x20f3acc - 0x20f3ab8, 0x20f3ad0 - 0x20f3ab8,
		0x20f3ad0 - 0x20f3ab8, 0x20f3ad4 - 0x20f3ab8, 0x20f3ad8 - 0x20f3ab8 };
	u8 *flags = scene + 0x20f3ab8;
	for (int k = 1; k <= 8; k++)
		FIELD(int, flags, k * 4) = 0;
	FIELD(int, flags, 0) = t;
	if (t < 1 || t > 13)
		return;
	if (t % 2)
		FIELD(int, flags, 4) = 1;
	if (second[t])
		FIELD(int, flags, second[t]) = 1;
}

/* a 4 x 4 identity matrix (floats, as their bits) */
static void identity(u32 *m)
{
	for (int k = 0; k < 16; k++)
		m[k] = k % 5 == 0 ? 0x3f800000 : 0;
}

/* 0x470ad0 (thiscall on the scene): the scene's subsystems reset (load_4723e0; the 100 dwords at +0x202ea80 and
   +0x202ef30 cleared; the object list, FUN_0047cfd0, load_479a60, load_48fe10), the camera at the origin looking down
   -z (+0x20f3970 .. +0x20f399c) with identity matrices (+0x20f39a0, +0x20f39e0), the start and item points none, the
   id tables (+0x20fce50, +0x1cd6968) all -1, then the scripts (load_48fc30, script_reset) and load_471010. Its
   callers ignore the eax it leaves */
void THISCALL (scene_reset)(u8 *s)
{
	load_4723e0(s);
	memset(s + 0x202ea80, 0, 0x64 * 4);
	FIELD(int, s, 0x202ef30) = 0;
	load_490d10(s);
	FUN_0047cfd0(s);
	load_479a60(s);
	load_48fe10(s);
	static const u32 camera[9] = { 0, 0, 0, 0, 0, 0xbf800000, 0, 0x3f800000, 0 };   /* position, forward -z, up y */
	memcpy(s + 0x20f3970, camera, sizeof camera);
	memcpy(s + 0x20f3994, s + 0x20f3970, 12);
	identity((u32 *)(s + 0x20f39a0));
	identity((u32 *)(s + 0x20f39e0));
	FIELD(int, s, 0x20f3adc) = 0;
	FIELD(int, s, 0x20fadf4) = 0;
	FIELD(int, s, 0x20fcd38) = 0;
	FIELD(int, s, 0x20fcd3c) = -1;
	FIELD(int, s, 0x20fcd40) = FIELD(int, s, 0x20fcd44) = FIELD(int, s, 0x20fcd48) = 0;
	s[0x20fcd4c] = 0;
	FIELD(int, s, 0x20fce4c) = -1;
	memset(s + 0x20fce50, 0xff, 0x64 * 4);
	load_48fc30(s);
	script_reset((Stage *)s);
	load_471010(s);
	memset(s + 0x1cd6968, 0xff, 0x32 * 4);
}
