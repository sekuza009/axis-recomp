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
   kept (chat_keepLastLine) and the round's flags cleared */
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
	stage_selectActor(STAGE(s), -1);
	s->watchedPlayer = -1;
	memset(s->watchClear, 0, sizeof s->watchClear);
	s->playing = 0;
	(void)timer_getGameTime((u8 *)s + 0xc);
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
	sound_setVolume(GAME_VAR(int, 0x4e0c90));
	set_4b42dc_457140(GAME_VAR(int, 0x4e0c94));
	s->roundClear4 = 0;
	s->teamAsked = 0;
	if (s->localPlayer >= 0)
		s->players[s->localPlayer].statD8 = 0;
	match_4613a0(s, -1);
	s->startCameraMode = s->cameraMode;
	s->cameraSlot = -1;   /* (the -1 still in a register since dataLossCode) */
	s->rankShown = -1;
	scene_resetScores(s);
	events_clear(s, 60.0f);
	s->chatMode = 0;
	if (GAME_VAR(int, 0x68039c))
		chat_keepLastLine();
	s->roundClear5 = 0;
	s->matchOver = 0;
	s->roundClear6 = 0;
	s->roundOver = 0;
	s->roundClear7 = 0;
	teams_setup(s);
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

/* 0x470ad0 (thiscall on the scene): the scene's subsystems reset (stage_resetLights; the 100 dwords at +0x202ea80 and
   +0x202ef30 cleared; the object list, stage_clearBullets, stage_clearProjectiles, stage_resetMatrixAndPoints), the camera at the origin looking down
   -z (+0x20f3970 .. +0x20f399c) with identity matrices (+0x20f39a0, +0x20f39e0), the start and item points none, the
   id tables (+0x20fce50, +0x1cd6968) all -1, then the scripts (stage_clearMapItemCounts, script_reset) and scene_initLevelGrid. Its
   callers ignore the eax it leaves */
void THISCALL (scene_reset)(u8 *s)
{
	stage_resetLights(s);
	memset(s + 0x202ea80, 0, 0x64 * 4);
	FIELD(int, s, 0x202ef30) = 0;
	stage_clearMapObjects(s);
	stage_clearBullets(s);
	stage_clearProjectiles(s);
	stage_resetMatrixAndPoints(s);
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
	stage_clearMapItemCounts(s);
	script_reset((Stage *)s);
	scene_initLevelGrid(s);
	memset(s + 0x1cd6968, 0xff, 0x32 * 4);
}

#define K(address) ((const float *)(address))

/* a part type's (or the stage's) shape set and skeleton set sized into their blocks */
static void model_sets(u8 *shapes, const char *dir, int n, int extra, int size, u8 *skels, const char *skel_dir, int sn,
                       int sextra, u8 *smem, int ssize)
{
	shape_initBy(shapes, dir, n, 2, extra, shapes + 0x24c, size);
	skelSet_setup(skels, skel_dir, sn, 2, sextra, smem, ssize);
}

/* 0x4700a0 (thiscall on the stage): the stage built (its names passed on to object_setNames): the collision space (in its
   block +0xb04), the ten sky textures (by 0x4c7410 from the third name; the last two flagged), the light factors and
   the default light (grey, from (-1, -1, -1)). The sky box (+0x9ee080: six faces of 7 x 7 points, a cube of side
   1 / sqrt(0x4aa408) turned to each face), the dome (+0x9eee54: 7 x 7 points of the up vector turned by two angles),
   six 4-point rings top and bottom (+0x9ef0cc), an 11 x 11 ground grid (+0x9ef350); the world box (+-100000), the
   layer lists cleared; the shape and skeleton sets of the stage, of each of the 16 part types (five parts each) and
   of the map; the effects and three textures (0x4c73f4 ..), an identity and a 1.1 scale matrix, the emblem atlas
   (a texture, filled with 0xa1f220); the game type 0, the actors and the scene reset; built (+4 1). Its caller
   ignores the eax it leaves */
void THISCALL (item_initTextures)(u8 *s, u32 a1, u32 a2, const char *sky, u32 a4, const char *skel_dir, u32 a6, u32 a7, u32 a8,
                                  u32 a9)
{
	object_setNames(s, a1, a2, (u32)sky, a4, (u32)skel_dir, a6, a7, a8, a9);
	space_initBy(s + 0xa10, 0x9c40, 0x27100, 0x3e8, 0x2710, 0x3e8, s + 0xb04, 0x9c95f0);
	char name[0x100];
	for (int i = 0; i < 10; i++) {
		sprintf(name, (const char *)0x4c7410, sky, i);
		FIELD(int, s, 0x9ccfd4 + i * 4) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, i > 7, 0, 0, 0, 0, 0, 0);
	}
	this_set_483d60(s + 0x9ccffc);
	factors_addConstant(s + 0x9ccffc, (const void *)0xa1f23c);
	stage_resetLights(s);
	this_set_483d60(s + 0x9e3020);
	u8 grey[4] = { 0x40, 0x40, 0x40, 0xff };
	factors_addConstant(s + 0x9e3020, grey);
	u32 down[3] = { 0xbf800000, 0xbf800000, 0xbf800000 };
	factors_addPoint(s + 0x9e3020, (const void *)0xa1f23c, down);
	long double root = 1;
	__asm__("fldl %1\n\tfsqrt" : "=t"(root) : "m"(*(const double *)0x4aa408));
	memset(s + 0x9ee030, 0, 14 * 4);
	long double inv = fld_m(K(0x4a9424)) / root;
	float r = f32(inv), out = f32(fmul_m(inv, K(0x4a9534)));
	for (int face = 0; face < 6; face++) {
		FIELD(int, s, 0x9ee068 + face * 4) = -1;
		float *dst = (float *)(s + 0x9ee080 + face * 49 * 12);
		for (int row = 3; row >= -3; row--) {
			float fr = f32(row);
			for (int c = 0; c <= 6; c++, dst += 3) {
				float v[3];
				v[0] = out;
				float fc = f32(c - 3);
				v[1] = f32(fld_m(&r) * fld_m(&fr));
				v[2] = f32(fmul_m(fld_m(&r), &fc));
				if (face == 0)
					Vec3_rotateAxis(v, 0, 900);
				else if (face <= 4)
					Vec3_rotateAxis(v, 2, 900 - face * 900);
				else
					Vec3_rotateAxis(v, 0, -900);
				memcpy(dst, v, 12);
			}
		}
	}
	FIELD(int, s, 0x9eee48) = 0;
	FIELD(int, s, 0x9eee4c) = FIELD(int, s, 0x9eee50) = -1;
	float *dome = (float *)(s + 0x9eee54);
	for (int i = 0; i <= 6; i++) {
		int ai = ftol(fmul_m(fsub_m((long double)i, K(0x4a9534)), K(0x4a93f0)));
		for (int j = 0; j <= 6; j++, dome += 3) {
			u32 v[3] = { 0, 0x3f800000, 0 };
			Vec3_rotateAxis((float *)v, 1, ai);
			Vec3_rotateAxis((float *)v, 0, ftol(fmul_m(fsub_m((long double)j, K(0x4a9534)), K(0x4a93f0))));
			((float *)v)[1] = f32(fsub_m(fld_m((float *)&v[1]), K(0x4a942c)));
			memcpy(dome, v, 12);
		}
	}
	memset(s + 0x9ef0a0, 0, 5 * 4);
	for (int o = 0, angle = 0; angle < 3600; o++, angle += 600) {
		FIELD(int, s, 0x9ef0b4 + o * 4) = -1;
		for (int k = 0; k < 4; k++) {
			u32 v[3] = { 0, 0x3f800000, 0x3f800000 };
			Vec3_rotateAxis((float *)v, 2, angle + k * 200);
			memcpy(s + 0x9ef0cc + o * 0x60 + k * 0xc, v, 12);
			float *low = (float *)(s + 0x9ef0fc + o * 0x60 + k * 0xc);
			low[0] = f32(fld_m((float *)&v[0]));
			FIELD(int, low, 4) = 0;
			low[2] = f32(fld_m((float *)&v[2]));
		}
	}
	FIELD(int, s, 0x9ef30c) = 0;
	memset(s + 0x9ef310, 0xff, 16 * 4);
	float *grid = (float *)(s + 0x9ef350);
	for (int i = 0; i <= 10; i++) {
		float x = f32(fmul_m(fsub_m((long double)i, K(0x4a93d0)), K(0x4aa400)));
		for (int j = 0; j <= 10; j++, grid += 3) {
			grid[0] = f32(fmul_m(fsub_m((long double)j, K(0x4a93d0)), K(0x4aa400)));
			FIELD(int, grid, 4) = 0;
			grid[2] = x;
		}
	}
	FIELD(int, s, 0x9ef8fc) = FIELD(int, s, 0x9ef900) = 0;
	for (int c = 0; c < 3; c++) {
		FIELD(u32, s, 0x9ef904 + c * 4) = 0xc7c35000;   /* -100000 */
		FIELD(u32, s, 0x9ef910 + c * 4) = 0x47c35000;   /* 100000 */
	}
	memcpy(s + 0x9ef91c, s + 0x9ef904, 12);
	FIELD(u32, s, 0x9ef934) = 0x3f800000;
	FIELD(int, s, 0xdc0240) = 0;
	memcpy(s + 0x9ef928, s + 0x9ef910, 12);
	FIELD(int, s, 0xdc0a74) = 0;
	FIELD(u8 *, s, 0xdc0a8c) = s + 0xdc0ac4;
	FIELD(u8 *, s, 0xdc0cd8) = s + 0xdc0d10;
	const char *dir = (const char *)s + 0x308;
	shape_initBy(s + 0xe3c93c, dir, 0x190, 2, 0xe54c0, s + 0xe3cb88, 1000000);
	FIELD(int, s, 0x13016c8) = 0;
	skelSet_setup(s + 0x13016d0, (const char *)s + 0x408, 0x64, 2, 0x7080, s + 0x1301800, 0x9c40);
	static const u32 zero[10] = { 0x131ae40, 0x13c9b24, 0x13c9b28, 0x13c9b2c, 0x13eb000, 0x140c8bc, 0x1447ec0, 0x148646c,
	                              0x14d1ab0, 0x19e1888 };
	for (int k = 0; k < 10; k++)
		FIELD(int, s, zero[k]) = 0;
	static const struct { u32 shapes; int n, extra, size; u32 skels; int sextra; u32 smem; int ssize; } parts[5] = {
		{ 0, 8, 0x7840, 0x7d00, 0x431fc, 0x6f0, 0x4332c, 0x7d0 }, { 0x7f4c, 8, 0x7840, 0x7d00, 0x43afc, 0x6f0, 0x43c2c, 0x7d0 },
		{ 0xfe98, 0x10, 0xf080, 0xfa00, 0x443fc, 0xec0, 0x4452c, 0xfa0 }, { 0x1fae4, 0x10, 0xf080, 0xfa00, 0x454cc, 0xec0, 0x455fc, 0xfa0 },
		{ 0x2f730, 0x14, 0x12ca0, 0x13880, 0x4659c, 0xec0, 0x466cc, 0xfa0 } };
	for (int t = 0; t < 16; t++) {
		u8 *type = s + 0x1561ea0 + t * 0x47fd2;
		for (int k = 0; k < 5; k++)
			model_sets(type + parts[k].shapes, dir, parts[k].n, parts[k].extra, parts[k].size, type + parts[k].skels, skel_dir, 2,
			           parts[k].sextra, type + parts[k].smem, parts[k].ssize);
	}
	shape_initBy(s + 0x19e188c, dir, 0x258, 2, 0x2c6280, s + 0x19e1ad8, 0x2dc6c0);
	skelSet_setup(s + 0x1cbe198, skel_dir, 0x64, 2, 0x15ae0, s + 0x1cbe2c8, 0x186a0);
	nullsub_48b420((Scene *)s);
	effect_initTextures(s);
	static const u32 names[3] = { 0x4c73f4, 0x4c73d8, 0x4c73bc };
	for (int k = 0; k < 3; k++) {
		sprintf(name, (const char *)names[k]);
		FIELD(int, s, 0x20f2f3c + k * 4) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, 0, 0, 0, 0, 0, 0, 0);
	}
	for (int k = 0; k < 16; k++) {
		FIELD(u32, s, 0x20f2f48 + k * 4) = k % 5 == 0 ? 0x3f800000 : 0;
		FIELD(u32, s, 0x20f2f88 + k * 4) = k == 15 ? 0x3f800000 : k % 5 == 0 ? 0x3f8ccccd : 0;   /* 1.1 */
	}
	IMPORT(0x4a925c, void, int, void *)(1, s + 0x20fcfe0);   /* glGenTextures */
	for (int k = 0; k < 0x2000; k++)
		FIELD(u32, s, 0x20fcfe4 + k * 4) = GAME_VAR(u32, 0xa1f220);
	FIELD(int, s, 0x20f3ab4) = 0;
	game_setGameTypeFlags((Stage *)s, 0);
	scene_resetActors(s);
	scene_reset(s);
	FIELD(int, s, 4) = 1;
}
#undef K
