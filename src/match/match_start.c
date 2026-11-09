/* match_start.c: a match's rounds started: the first round sets up the mode, the map rotation and the local
   player; each later round picks new starting points and resets the round's state. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, AP(u8, RELOC(obj)) + (offset))


static void set_round(Round *r, int map, int mode, int score, int time)
{
	r->map = map;
	r->mode = mode;
	r->fragLimit = score;
	r->timeLimit = time;
}

/* the first round's map rotation: solo, the 15 stages (0x5c-byte records of g_skirmishInfo from gameMode: the mode, the time and the
   score limits) from the stage chosen (g_mapIndex); a network host, the arena maps in rotation (g_mapCount of them, 8
   bytes each from g_mapChoiceKeptTable: in rotation, the map's own mode, used when the chosen mode g_chosenGameMode is 14 or more) or,
   without rotation (g_mapRotation), the chosen map only, from the first; a machine that joined, none */
static void make_rotation(Scene *s)
{
	if (s->sessionMode == 0) {
		s->rotationCount = 0;
		int k;
		for (k = 0; k < 15; k++) {
			const SkirmishInfo *si = AP(const SkirmishInfo, OBJ(g_skirmishInfo)) + k;
			set_round(&s->rotation[s->rotationCount++], k, si->gameMode, si->fragLimit, si->timeLimit);
		}
		s->rotationAt = g_mapIndex;
		s->nextMap = k + 1;   /* (beyond the 15, as the original has it) */
		s->nextMode = g_skirmishInfo16Mode;   /* (past the 15 records, as the original reads it) */
		s->awaitingHostRound = 0;
		return;
	}
	if (s->sessionMode != 1 || s->client) {
		s->rotationCount = 0;
		s->rotationAt = 0;
		s->awaitingHostRound = 1;
		return;
	}
	if (g_mapRotation == 1) {
		s->rotationCount = 0;
		for (int k = 0; k < g_mapCount; k++) {
			const MapChoice *entry = &g_mapChoiceKeptTable[k];
			if (entry->chosen != 1)
				continue;
			int mode = g_chosenGameMode;
			if (mode >= 14)
				mode = entry->type;
			set_round(&s->rotation[s->rotationCount++], k, mode, g_fragLimit, g_timeLimit);
		}
	} else {
		s->rotationCount = 1;
		set_round(&s->rotation[0], g_mapIndex, g_chosenGameMode, g_fragLimit, g_timeLimit);
	}
	s->rotationAt = 0;
	g_mapIndex = s->rotation[0].map;
	int next = (s->rotationAt + 1) % s->rotationCount;   /* (none in rotation divides by zero, as in the original) */
	s->nextMap = s->rotation[next].map;
	s->nextMode = s->rotation[next].mode;
	s->awaitingHostRound = 0;
}

/* the match set up, before any map is loaded: a Ladder game (the game room's: g_matchMode 2; the scores committed every 300 s, a game counted at
   g_ladderGames), the rotation, the limits, the mech (its name g_matchPlayerName, value, parts, items and the five colour sets),
   the room's level (from its points g_ladderExp; outside 1 .. 20 fatal); then a network host makes its player 0, a
   machine that joined has none yet, and a solo game makes player 0 with rotation on (g_mapRotation) */
static void match_setup(Scene *s)
{
	s->ladderGame = g_matchMode == 2;
	if (s->ladderGame == 1) {
		BITS(s->scoreCommitTimer) = 0x43960000;   /* 300 */
		g_ladderGames++;
		s->showExp = 1;
	} else
		s->showExp = 0;
	make_rotation(s);
	if (s->rotationCount > 0)
		game_setGameTypeFlags(STAGE(s), s->rotation[s->rotationAt].mode);
	s->fragLimit = g_fragLimit;
	s->timeLimit = g_timeLimit;
	strcpy(s->localName, g_matchPlayerName);
	s->character = g_selectedCharacter;
	if (s->ladderGame == 1) {
		s->levelPoints = g_ladderExp;
		s->level = level_fromPoints(s->levelPoints);
		if (s->level < 1 || s->level > 20)
			sys_fatalError(AP(char, OBJ(g_logConsole)), AP(const char, STR(0x4d0710, "incorrect level(%d) - processGameMode...")), s->level);
	} else {
		s->levelPoints = 0;
		s->level = 1;
	}
	for (int k = 0; k < 5; k++)
		s->mechParts[k] = g_savedMechPartIds[k];
	static const u32 items[6] = { ADDR(g_savedMechWeaponSlot0), ADDR(g_savedMechWeaponSlot1), ADDR(g_savedMechWeaponSlot2), ADDR(g_savedMechWeaponSlot3), ADDR(g_savedMechItemSlot4), ADDR(g_savedMechItemSlot5) };
	for (int k = 0; k < 6; k++)
		s->mechItems[k] = GAME_VAR(int, items[k]);
	/* the five parts' colour pairs (six dwords each from g_savedColourChoices: hue, saturation, value of the first tint, then
	   of the second) */
	for (int i = 0; i < 5; i++)
		for (int t = 0; t < 3; t++) {
			BITS(s->mechColours[t][i][0]) = BITS(((ColourChoice *)g_savedColourChoices)[(u32)i].first[(u32)t]);
			BITS(s->mechColours[t][i][1]) = BITS(((ColourChoice *)g_savedColourChoices)[(u32)i].second[(u32)t]);
		}
	if (s->sessionMode == 1) {
		if (!s->client) {
			netq_reset(1);
			s->localPlayer = 0;
			actor_resetSlot(STAGE(s), 0);
			player_setName(STAGE(s), s->localPlayer, s->localName);
			strcpy(s->players[s->localPlayer].name, s->localName);
			s->players[s->localPlayer].player = s->localPlayer;
		} else {
			netq_reset(0);
			s->localPlayer = -1;
			g_mapIndex = -1;
			s->nextMap = -1;
			s->nextMode = -1;
		}
		memset(&s->sendTimer, 0, 9 * 4);   /* sendTimer .. packetLossTimer */
		s->rankingShown = 1;
	} else {
		g_netHostGone = 0;
		s->localPlayer = 0;
		player_setName(STAGE(s), 0, s->localName);
		s->playerActor = 0;
		g_mapRotation = 1;
		s->rankingShown = 0;
	}
	(*(int *)&s->lostTime) = 0;
	s->stageCleared = 0;
}

/* a random position below n (from the game's table of rand() values, g_randTable, at g_randPos), 0 when n is none */
static int random_below(u32 n)
{
	if ((int)n <= 0)
		return 0;
	u32 at = g_randPos;
	u32 r = (*(u32 *)&g_randTable[at & 0xfff]);
	g_randPos = at + 1;
	return (int)(r % n);
}

/* a round started on the loaded map (the first one too): a random position in each of the six type tables (the five part types', actorItems) (their counts at headCount .., rows of
   0x2aa .. 0xb86 dwords), the restart point, the round's tables copied (cameraMode counting through them, as in the
   original), the camera back to mode 1, nobody watched, the pointer centred, the volumes (g_soundVolume, g_musicVolume) set
   again, the local player's inPlay cleared, the teams (scene_setLocalTeam), the camera and its slot, a typed line kept
   (match_endTyping) and the round's flags cleared */
static void round_start(Scene *s)
{
	const int *counts[6] = { &s->headCount, &s->chestCount, &s->armCount, &s->legCount, &s->boosterCount, &s->actorItemCount };
	static const u32 row_len[6] = { sizeof(HeadType) / 4, sizeof(ChestType) / 4, sizeof(ArmType) / 4, sizeof(LegType) / 4, sizeof(BoosterType) / 4, sizeof(ActorItem) / 4 };   /* (the records in dwords) */
	s->typeCheckTurn = 0;
	for (int k = 0; k < 6; k++)
		s->typeTablePickUnread[k] = random_below(((u32)*counts[k] * row_len[k] * 4) >> 2);
	s->dataLossPending = 0;
	s->dataLossCode = -1;
	s->wholeSeconds = 0;
	BITS(s->secondFraction) = 0;
	s->gamePacketTimer = 3.0f;
	for (int k = 0; k < 3; k++)
		BITS(s->cameraPos[k]) = BITS(s->mapStart[k]);
	BITS(s->cameraAngle[0]) = BITS(s->mapStart[3]);
	BITS(s->cameraAngle[1]) = BITS(s->mapStart[4]);
	for (s->cameraMode = 0; s->cameraMode < 10; s->cameraMode++)
		for (int t = 0; t < 6; t++)
			s->cameraSettings[t][s->cameraMode] = s->cameraPresets[t][s->cameraMode];
	s->cameraMode = 1;
	stage_setCockpitActor(STAGE(s), -1);
	s->watchedPlayer = -1;
	memset(s->manualPick, 0, sizeof s->manualPick);
	s->playing = 0;
	(void)TimeSync_frameTime((u8 *)&s->timer);
	g_mouseX = gfx_getWidth() / 2;
	g_mouseY = gfx_getHeight() / 2;
	sound_setVolume(g_soundVolume);
	music_setVolumeSetting(g_musicVolume);
	s->localRecordSet = 0;
	s->playAsked = 0;
	if (s->localPlayer >= 0)
		s->players[s->localPlayer].inPlay = 0;
	scene_setLocalTeam(s, -1);
	s->respawnCameraMode = s->cameraMode;
	s->cameraSlot = -1;   /* (the -1 still in a register since dataLossCode) */
	s->localRank = -1;
	scene_resetScores(s);
	events_clear(s, 60.0f);
	s->chatMode = 0;
	if (g_textFieldOpen)
		match_endTyping();
	(*(int *)&s->keyGuard) = 0;
	s->matchOver = 0;
	(*(int *)&s->endTime) = 0;
	s->matchLeaving = 0;
	(*(int *)&s->quitDelay) = 0;
	teams_setup(s);
	BITS(s->msgFade) = 0;
}

/* 0x49df10 (thiscall on the scene): run on the playing state's first frame (match_playFrame, stateFrames 0). Before
   any map is loaded (matchDrawing 0, as scene_startSession leaves it) the match is set up (match_setup: Ladder game,
   rotation, limits, mech, local player); once a map has loaded (loading stage 8 sets matchDrawing 1 and stateFrames 0
   again) the round on it starts (round_start: type table check, camera, volumes, scores, events, teams). Its caller
   ignores the eax it leaves */
void THISCALL (match_setupOrStartRound)(Scene *s)
{
	if (s->matchDrawing)
		round_start(s);
	else
		match_setup(s);
}

/* 0x4732f0 (thiscall on the scene): game type t (gameType) and its rule flags (teamGame .. platoon, cleared
   first): the odd types 1 .. 13 set teamGame; types 2 .. 11 by pairs set one of suddenDeath .. gladiator, 12 sets
   kingOfTheHill and 13 platoon. Its callers ignore the eax it leaves */
void THISCALL (game_setGameTypeFlags)(u8 *scene, int t)
{
#define AT(field) (offsetof(Stage, field) - offsetof(Stage, gameType))
	static const u16 modeFlagOffset[14] = { 0, 0, AT(suddenDeath), AT(suddenDeath), AT(shotgunArena), AT(shotgunArena), AT(ionCannonArena),
		AT(ionCannonArena), AT(rocketArena), AT(rocketArena), AT(gladiator), AT(gladiator), AT(kingOfTheHill), AT(platoon) };
#undef AT
	Stage *st = (Stage *)scene;
	u8 *flags = scene + offsetof(Stage, gameType);
	for (int k = 1; k <= 8; k++)
		FIELD(int, flags, k * 4) = 0;   /* teamGame .. platoon */
	st->gameType = t;
	if (t < 1 || t > 13)
		return;
	if (t % 2)
		st->teamGame = 1;
	if (modeFlagOffset[t])
		FIELD(int, flags, modeFlagOffset[t]) = 1;
}

/* a 4 x 4 identity matrix (floats, as their bits) */
static void identity(u32 *m)
{
	for (int k = 0; k < 16; k++)
		m[k] = k % 5 == 0 ? 0x3f800000 : 0;
}

/* 0x470ad0 (thiscall on the stage): the stage's subsystems reset (stage_resetDynamicLights; the 100 dwords at lockHeld and
   lockCount cleared; the object list, stage_clearBullets, stage_clearParticles, stage_resetMatrixAndPoints), the camera at the origin looking down
   -z (cameraPos .. lastCameraPos[2]) with identity matrices (modelview, lastModelview), the start and item points none, the
   team commanders (teamCommanders) and snapshot textures (snapshotTex) all -1, then the scripts (stage_clearMessages, script_reset) and stage_initSpaceOneCell. Its
   callers ignore the eax it leaves */
void THISCALL (stage_reset)(u8 *s)
{
	Stage *st = (Stage *)s;
	stage_resetDynamicLights(s);
	memset(st->lockHeld, 0, 0x64 * 4);
	st->lockCount = 0;
	stage_clearMapObjects(s);
	stage_clearBullets(s);
	stage_clearParticles(s);
	stage_resetMatrixAndPoints(s);
	static const u32 camera[9] = { 0, 0, 0, 0, 0, 0xbf800000, 0, 0x3f800000, 0 };   /* position, forward -z, up y */
	memcpy(st->cameraPos, camera, sizeof camera);
	memcpy(st->lastCameraPos, st->cameraPos, 12);
	identity((u32 *)st->modelview);
	identity((u32 *)st->lastModelview);
	st->itemTypeCount = 0;
	st->startCount = 0;
	st->itemCount = 0;
	st->lastPickup = -1;
	st->clockSeconds = (*(int *)&st->clockFraction) = st->botsHoldFire = 0;
	st->printText[0] = 0;   /* the kill report emptied */
	st->kingActor = -1;
	memset(st->teamCommanders, 0xff, 0x64 * 4);
	stage_clearMessages(s);
	script_reset(st);
	stage_initSpaceOneCell(s);
	memset(st->snapshotTex, 0xff, 0x32 * 4);
}


/* a player record's part (or the stage's) shape set and skeleton set sized into their blocks */
static void model_sets(u8 *shapes, const char *dir, int n, int extra, int size, u8 *skels, const char *skel_dir, int sn,
                       int sextra, u8 *smem, int ssize)
{
	ShapeManager_initBy(shapes, dir, n, 2, extra, shapes + sizeof(ShapeManager), size);   /* (its block right after it) */
	SkeletonManager_initBy(skels, skel_dir, sn, 2, sextra, smem, ssize);
}

/* 0x4700a0 (thiscall on the stage): the stage built (its names passed on to stage_setFolders): the collision space (in its
   block spaceData), the ten effect textures (effectTextures and mapItemTexture, by 0x4c7410 from the third name; the last two flagged), the light factors and
   the default light (grey, from (-1, -1, -1)). The sky box (skySphere: six faces of 7 x 7 points, a cube of side
   1 / sqrt(k_27) turned to each face), the dome (layer: 7 x 7 points of the up vector turned by two angles),
   six 4-point rings top and bottom (sides), an 11 x 11 ground grid (floor); the world box (+-100000), the
   layer lists cleared; the shape and skeleton sets of the stage, of each of the 16 player records (five parts each) and
   of the map; the effects and three textures (0x4c73f4 ..), an identity and a 1.1 scale matrix, the flag atlas
   (a texture, filled with g_defaultColour); the game type 0, the actors and the stage reset (stage_resetActors, stage_reset); built (+4 1). Its caller
   ignores the eax it leaves */
void THISCALL (stage_build)(u8 *s, u32 stageDir, u32 mapDir, const char *textureDir, u32 shapeDir, const char *skeletonDir, u32 actorDir,
                                  u32 bulletDir, u32 effectDir, u32 sceneDir)
{
	Stage *st = (Stage *)s;
	stage_setFolders(s, stageDir, mapDir, AV(textureDir), shapeDir, AV(skeletonDir), actorDir, bulletDir, effectDir, sceneDir);
	space_initBy((u8 *)&st->space, 0x9c40, 0x27100, 0x3e8, 0x2710, 0x3e8, st->spaceData, sizeof st->spaceData);
	char name[0x100];
	for (int i = 0; i < 10; i++) {
		sprintf(name, AP(const char, STR(0x4c7410, "%s\\%02d")), textureDir, i);
		st->effectTextures[i] = tex_getIdByName((*(void **)&g_textures), name, i > 7, 0, 0, 0, 0, 0, 0);
	}
	Light_clearCounts((u8 *)&st->mapLights);
	factors_addAmbient((u8 *)&st->mapLights, AP(const void, OBJ(g_packedWhite)));
	stage_resetDynamicLights(s);
	Light_clearCounts((u8 *)&st->actorLights);
	u8 grey[4] = { 0x40, 0x40, 0x40, 0xff };
	factors_addAmbient((u8 *)&st->actorLights, grey);
	u32 down[3] = { 0xbf800000, 0xbf800000, 0xbf800000 };
	factors_addDirectional((u8 *)&st->actorLights, AP(const void, OBJ(g_packedWhite)), down);
	long double root = 1;
	root = x87_fsqrt(k_27);
	memset((u8 *)s + offsetof(Stage, clearOn), 0, 14 * 4);   /* clearOn and the next 13 dwords */
	long double inv = fld_m(&k_1f) / root;
	float r = f32(inv), out = f32(fmul_m(inv, &k_3f));
	for (int face = 0; face < 6; face++) {
		st->skyTextures[face] = -1;
		float *dst = &st->skySphere[face][0][0][0];
		for (int row = 3; row >= -3; row--) {
			float fr = f32(row);
			for (int c = 0; c <= 6; c++, dst += 3) {
				float v[3];
				v[0] = out;
				float fc = f32(c - 3);
				v[1] = f32(fld_m(&r) * fld_m(&fr));
				v[2] = f32(FMUL(r, fc));
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
	st->layerMode = 0;
	st->skyLayerTextures[0] = st->skyLayerTextures[1] = -1;
	float *dome = &st->layer[0][0][0];
	for (int i = 0; i <= 6; i++) {
		int ai = ftol(fmul_m(fsub_m((long double)i, &k_3f), &k_200f));
		for (int j = 0; j <= 6; j++, dome += 3) {
			u32 v[3] = { 0, 0x3f800000, 0 };
			Vec3_rotateAxis(AP(float, RELOC(v)), 1, ai);
			Vec3_rotateAxis(AP(float, RELOC(v)), 0, ftol(fmul_m(fsub_m((long double)j, &k_3f), &k_200f)));
			(AP(float, RELOC(v)))[1] = f32(fsub_m(fld_m((float *)&v[1]), &k_0_5f));
			memcpy(dome, v, 12);
		}
	}
	memset((u8 *)st + offsetof(Stage, layerTurns), 0, 5 * 4);   /* layerTurns, layerScroll, sideMode */
	for (int o = 0, angle = 0; angle < 3600; o++, angle += 600) {
		st->sideTextures[o] = -1;
		for (int k = 0; k < 4; k++) {
			u32 v[3] = { 0, 0x3f800000, 0x3f800000 };
			Vec3_rotateAxis(AP(float, RELOC(v)), 2, angle + k * 200);
			memcpy(st->sides[o][k], v, 12);
			float *low = st->sides[o][4 + k];
			low[0] = f32(fld_m((float *)&v[0]));
			BITS(low[1]) = 0;
			low[2] = f32(fld_m((float *)&v[2]));
		}
	}
	st->floorMode = 0;
	memset(st->floorTextures, 0xff, 16 * 4);
	float *grid = &st->floor[0][0][0];
	for (int i = 0; i <= 10; i++) {
		float x = f32(fmul_m(fsub_m((long double)i, &k_5f), &k_0_2f_4aa400));
		for (int j = 0; j <= 10; j++, grid += 3) {
			grid[0] = f32(fmul_m(fsub_m((long double)j, &k_5f), &k_0_2f_4aa400));
			BITS(grid[1]) = 0;
			grid[2] = x;
		}
	}
	st->floorFrame = (*(int *)&st->floorClock) = 0;
	for (int c = 0; c < 3; c++) {
		BITS(st->levelLow[c]) = 0xc7c35000;   /* -100000 */
		BITS(st->levelHigh[c]) = 0x47c35000;   /* 100000 */
	}
	memcpy(st->worldLow, st->levelLow, 12);
	st->unused9ef934 = 1.0f;
	st->layerPoolUsed = 0;
	memcpy(st->worldHigh, st->levelHigh, 12);
	st->groundLayerCount = 0;
	st->layerModel.parts = AREF(st->layerParts);
	st->waterModel.parts = AREF((u8 *)st->waterParts);
	const char *dir = st->shapeDir;
	ShapeManager_initBy((u8 *)&st->objectShapes, dir, 0x190, 2, 0xe54c0, st->objectShapeData, sizeof st->objectShapeData);
	st->objectColourCount = 0;
	SkeletonManager_initBy((u8 *)&st->objectSkeletons, st->skeletonDir, 0x64, 2, 0x7080, st->objectSkeletonData, sizeof st->objectSkeletonData);
	static const u32 zero[10] = { offsetof(Stage, objectNameCount), offsetof(Stage, objectCount), offsetof(Stage, objectFreeHint), offsetof(Stage, objectSerial), offsetof(Stage, headTypeCount), offsetof(Stage, chestTypeCount), offsetof(Stage, armTypeCount), offsetof(Stage, legTypeCount),
	                              offsetof(Stage, boosterTypeCount), offsetof(Stage, playerRecordCount) };
	for (int k = 0; k < 10; k++)
		FIELD(int, s, zero[k]) = 0;
	/* each player record's five shape and skeleton caches */
#define PART(p, n, extra, sextra) { offsetof(PlayerRecord, p##Shapes), n, extra, sizeof ((PlayerRecord *)0)->p##ShapeData, offsetof(PlayerRecord, p##Skels), sextra, \
	offsetof(PlayerRecord, p##SkelData), sizeof ((PlayerRecord *)0)->p##SkelData }
	static const struct { u32 shapes; int n, extra, size; u32 skels; int sextra; u32 smem; int ssize; } parts[5] = {
		PART(head, 8, 0x7840, 0x6f0), PART(chest, 8, 0x7840, 0x6f0), PART(arm, 0x10, 0xf080, 0xec0), PART(leg, 0x10, 0xf080, 0xec0),
		PART(booster, 0x14, 0x12ca0, 0xec0) };
#undef PART
	for (int t = 0; t < 16; t++) {
		u8 *record = (u8 *)&st->playerRecords[t];
		for (int k = 0; k < 5; k++)
			model_sets(record + parts[k].shapes, dir, parts[k].n, parts[k].extra, parts[k].size, record + parts[k].skels, skeletonDir, 2,
			           parts[k].sextra, record + parts[k].smem, parts[k].ssize);
	}
	ShapeManager_initBy((u8 *)&st->itemShapes, dir, 0x258, 2, 0x2c6280, st->itemShapeData, sizeof st->itemShapeData);
	SkeletonManager_initBy((u8 *)&st->itemSkeletons, skeletonDir, 0x64, 2, 0x15ae0, st->itemSkeletonData, sizeof st->itemSkeletonData);
	shared_emptyFunction((Scene *)s);
	effect_initShapes(s);
	static const u32 names[3] = { STR(0x4c73f4, "Texture\\Item_damagemap_ani0"), STR(0x4c73d8, "Texture\\Item_booster_ani0"), STR(0x4c73bc, "Texture\\Item_shield_ani0") };
	for (int k = 0; k < 3; k++) {
		sprintf(name, AP(const char, RELOC(names[k])));
		st->itemTextures[k] = tex_getIdByName((*(void **)&g_textures), name, 0, 0, 0, 0, 0, 0, 0);
	}
	for (int k = 0; k < 16; k++) {
		BITS(st->faintActorMatrix[k]) = k % 5 == 0 ? 0x3f800000 : 0;
		BITS(st->overlayMatrix[k]) = k == 15 ? 0x3f800000 : k % 5 == 0 ? 0x3f8ccccd : 0;   /* 1.1 */
	}
	glGenTextures(1, &st->flagGlTexture);   /* glGenTextures */
	for (int k = 0; k < 0x2000; k++)
		st->flagAtlas[k / 128][k % 128] = (*(u32 *)&g_defaultColour);
	st->showExp = 0;
	game_setGameTypeFlags((Stage *)s, 0);
	stage_resetActors(s);
	stage_reset(s);
	st->built = 1;
}
