/* small.c: one-line pieces from all over the game that need nothing of their own: clears, flags, getters and
   setters, list toggles, string lengths. Grouped by where they are used. */
#include "../game.h"
#include <stdarg.h>
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

static void clear(void *p, int dwords)
{
	u32 *q = p;
	for (int i = 0; i < dwords; i++)
		q[i] = 0;
}

/* ---- empty methods (their arguments unused) and trivial returns ---- */
/* 0x45fff0: the empty constructor (mov eax, ecx; ret: returns this) that every class without a constructor body
   shares (the compiler folded them into one). It is crt_arrayConstruct's element constructor for 18 of Console_ctor's
   arrays (the lights' Factors, sky / layer / side / floor vertices, ground layers, way points, object colours,
   objects, actor items, map actors, bullets, particles, points, starts, items, the flag atlas). It is also called
   directly for the stack actor's five rounds (actor_checkDataLoss) and armc_drawPreview3D's Light's 0x400 entries */
void *THISCALL (class_emptyCtor)(void *self) { return self; }
/* 0x48b440: ScenePath's per-frame step (an empty method: xor eax, eax; ret 4). It answers 0, so
   stage_advanceScenePath clears scriptMode on the first frame. Its argument is the frame's time (dt) */
int THISCALL (scenePath_advanceStub)(void *self, int a) { (void)self; (void)a; return 0; }
/* 0x48b430: an empty two-argument method (ret 8). It is called as ScenePath's open (stage_advanceScenePath:
   scriptName, "Scene"). Because the compiler folded identical empty bodies, match_frame also calls it on the scene
   after a cheat code (scene, localPlayer, code; app_frameByScreen.c:1582) */
void THISCALL (scenePath_openStub)(void *self, int a0, int a1) { (void)self; (void)a0; (void)a1; }
/* 0x48b450: ScenePath's notify method (empty: ret 0x10). Only script_notifyObject calls it, with its four arguments */
void THISCALL (scenePath_notifyStub)(void *self, int a0, int a1, int a2, int a3) { (void)self; (void)a0; (void)a1; (void)a2; (void)a3; }
/* 0x43f770: the start mode from the registry - always 1 in this build */
u32 (reg_readStartMode)(void) { return 1; }

/* ---- setters of single globals (they return the value) ---- */
int (text_setWrapX)(int v) { g_textWrapX = v; return v; }
int (text_setBottom)(int v) { g_textBottom = v; return v; }
/* 0x4686e0: the view's vertical field of view in degrees (g_viewFov, gluPerspective's fovy; a float's bits) set and
   returned */
int (view_setFov)(int v) { (*(int *)&g_viewFov) = v; return v; }

/* ---- index <-> pointer in an array of records ---- */
/* 0x46cbc0: record i (base + i * stride), 0 for a negative index */
int (array_recordAt)(int i, int base, int stride) { return i < 0 ? 0 : i * stride + base; }
/* 0x46cba0: the index of record p, -1 for none */
int (array_indexOf)(int p, int base, int stride) { return p == 0 ? -1 : (p - base) / stride; }

/* ---- strings ---- */
/* 0x44ac50: the length of s */
int (str_length)(const char *s)
{
	int n = 0;
	while (*s++)
		n++;
	return n;
}
/* 0x44ac70: s without its last character (its old length) */
int (str_dropLast)(char *s)
{
	int n = str_length(s);
	s[n - 1] = '\0';
	return n;
}

/* ---- the scene's and stage's flags and lists ---- */
/* 0x463670, 0x463690, 0x4636b0: an end notice queued for the other players (endEvents: the server ends the game,
   the frag limit, the time limit; packet kinds 3 .. 5) and the "something to send" flag */
void THISCALL (net_announceServerEnd)(Scene *scene) { scene->endEvents[0] = 1; scene->announcePending = 1; }
void THISCALL (net_announceFragLimit)(Scene *scene) { scene->endEvents[1] = 1; scene->announcePending = 1; }
void THISCALL (net_announceTimeLimit)(Scene *scene) { scene->endEvents[2] = 1; scene->announcePending = 1; }
/* 0x463780: team slot i's id */
int THISCALL (scene_teamIdAt)(Scene *scene, int i) { return scene->teamIds[i]; }
/* 0x474390: player record p marked used; playerRecord_markFree: marked free, its flag cleared */
void THISCALL (playerRecord_markUsed)(Stage *stage, int p) { stage->playerRecords[p].used = 1; }
void THISCALL (playerRecord_markFree)(Stage *stage, int p)
{
	stage->playerRecords[p].used = 0;
	playerRecord_resetFlag(stage, p);
}
/* 0x45df90: the stage's frag counts cleared (frags[100]) */
void THISCALL (stage_clearFrags)(Stage *stage) { clear((u8 *)stage->frags, 100); }
/* 0x45e1c0: every actor in use switched off */
void THISCALL (stage_deactivateActors)(Stage *stage)
{
	for (int i = 0; i < stage->actorCount; i++)
		actor_deactivate(stage, i);
}
/* 0x4723e0: the stage's lights reset */
int THISCALL (stage_resetLights)(Stage *stage)
{
	stage->dynamicLightsSet = 0;
	return Light_clearCounts((u8 *)&stage->dynamicLights);
}

/* ---- small objects ---- */
/* 0x480440: an empty slot: -1 and four zeros */
void THISCALL (spaceSlot_clear)(int *self) { self[1] = self[2] = self[3] = self[4] = 0; self[0] = -1; }
/* 0x469980, 0x46f480: members cleared (partList_clear keeps the sixth) */
void THISCALL (Skeleton_clear)(int *self) { for (int i = 1; i <= 7; i++) self[i] = 0; }
void THISCALL (partList_clear)(int *self) { for (int i = 1; i <= 11; i++) if (i != 6) self[i] = 0; }
/* 0x4699a0, 0x46f4b0: the owned block (BlockOwner) freed, then the members cleared */
static void free_owned(void *self)
{
	BlockOwner *bo = (BlockOwner *)self;
	if (bo->ownsBlock == 1) {
		operator_delete(bo->block);
		bo->block = NULL;
		bo->ownsBlock = 0;
	}
}
int THISCALL (Skeleton_release)(void *self) { free_owned(self); Skeleton_clear(self); return 0; }
int THISCALL (partList_release)(void *self) { free_owned(self); partList_clear(self); return 0; }
/* 0x46f470: UnitPoseInfo's destructor (vtable 0x4a9754) */
int THISCALL (UnitPoseInfo_dtor)(u32 *self) { self[0] = VT(UnitPoseInfo, 0x4a9754); return partList_release(self); }
/* 0x45ff10: its deleting destructor (the vtable's slot 0; compiler-made, which the decompile had not listed): the
   destructor, then the object freed when flags bit 0 is set; returns this */
void *THISCALL (UnitPoseInfo_deletingDtor)(u32 *self, int flags)
{
	UnitPoseInfo_dtor(self);
	if (flags & 1)
		operator_delete(self);
	return self;
}
/* 0x46ce50: the object's file closed (fclose's result, 0 for none) */
u32 THISCALL (BMPRGBFile_close)(u32 *self) { return self[1] ? fclose((void *)RELOC(self[1])) : 0; }
/* 0x467d60: p freed (operator delete's eax; 0 for none) */
u32 (mem_free)(void *p) { return p ? GAME_CDECL(0x49ef24, u32, void *)(p) : 0; }

/* ---- network tables cleared ---- */
void (net_clearServerList)(void) { clear((void *)OBJ(g_serverList), 0x16c0); }
void (net_clearRoomList)(void) { clear((void *)OBJ(g_roomList), 0x1e40); }
void (net_clearPlayerList)(void) { clear((void *)OBJ(g_netPlayerList), 0x9b); }
/* 0x46cb60: a path upper-cased in place, '/' turned into '\\'; returns it (NULL as it is) */
char *(path_normalize)(char *s)
{
	if (s)
		for (char *p = s; *p; p++) {
			if (*p >= 'a' && *p <= 'z')
				*p -= 0x20;
			else if (*p == '/')
				*p = '\\';
		}
	return s;
}

/* 0x451530: every one of the 16 network slots (g_netSlots) owned by id emptied, its flag (g_playerSlotFlags) too; slot 0
   freed sets g_netHostGone. Leaves 0xff in AL */
u8 (net_freeSlotsOf)(int id)
{
	for (int s = 0; s < 16; s++) {
		NetSlot *r = &g_netSlots[s];
		if (r->id != (u32)id)
			continue;
		r->used = r->id = r->waiting = r->size = 0;
		g_playerSlotFlags[s] = 0;
		if (s == 0)
			g_netHostGone = 1;
	}
	return 0xff;
}

/* 0x430bd0: the 16 network slots marked empty */
void (net_clearSlots)(void) { for (NetSlot *p = g_netSlots; p < g_netSlots + 16; p++) p->used = 0; }

/* ---- front end ---- */
/* 0x453a30: 1 if connection kind i (0 .. 3) is available */
int (net_connectionAvailable)(u32 i) { return i < 4 && g_dpConnections[i] ? 1 : 0; }
/* 0x4417c0: replay i of the replay selection dialog in or out; replaySelect_allIn: all in (0x44-byte entries from 0x9ddac8) */
void (replaySelect_toggle)(int i) { int *f = &g_replayList[i].picked; *f = 1 - *f; }
void (replaySelect_allIn)(void) { for (int i = 0; i < g_replayFileCount; i++) g_replayList[i].picked = 1; }
/* 0x447af0: a click closes the mission briefing */
void (briefing_clickClose)(void) { if (g_frameOpening == 0 && g_mouseClick != 0) g_skirmishBriefing = 0; }
/* 0x4411e0: the menu tunnel started from its first ring: the ring count (g_tunnelRings) back to 0 and one ring
   (number 0) appended to g_menuTunnel (tunnel_appendRing). Returns that call's eax. It frees nothing */
u32 (tunnel_restart)(void) { g_tunnelRings = 0; return tunnel_appendRing((void *)ADDR(g_menuTunnel)); }
/* 0x44ad30: the text colour */
void (text_setColor)(u32 r, u32 g, u32 b, u32 a) { set_colour_bits(g_textColour, r, g, b, a); }
/* 0x404120, 0x431db0, 0x44b080: a dialog's box rectangle */
void (arenaDialogBox_layout)(void) { rect_set(0x104, 0x118, 0x17c, 0x138, g_arenaDialogBoxRects); }
void (gameListStop_layout)(void) { rect_set(0x104, 0x118, 0x17c, 0x138, g_gameListStopRects); }
void (profileDialogBox_layout)(void) { rect_set(0x1d7, 0xf6, 0x226, 0x114, g_profileMessageClickBox); }
/* 0x45dfb0: the cockpit actor (cockpitActor: the one the camera sits in) set to i when actor i is in play (state 1).
   A negative i is stored as it is (callers pass -1: none) */
void THISCALL (stage_setCockpitActor)(Stage *stage, int i)
{
	if (i < 0 || stage->actors[i].state == 1)
		stage->cockpitActor = i;
}
/* 0x456820: material m (the manager's record m) marked changed, its flags kept to the bits 0x11111113 (the
   original's guard, flags | 2, is always true) */
void THISCALL (tex_markMaterialChanged)(TextureBank *self, int m)
{
	TexRecord *r = &self->records[m];
	u32 f = r->flags;
	if ((f | 2) != 0) {
		r->flags = f & 0x11111113;
		r->changed = 1;
	}
}
/* 0x456b50: the three counters of each of the six texture banks cleared */
void THISCALL (tex_clearSetCounters)(TextureManager *self)
{
	for (int k = 1; k <= 6; k++) {
		TextureBank *o = (TextureBank *)self->banks[k - 1];
		o->loadCount = 0;
		o->counterB = 0;
		o->counterC = 0;
	}
}
/* 0x473470: player record p's flag image (flag, 16 x 24 pixels) filled with g_defaultColour, and its state reset:
   flagShown 0, flagChanged 0, flagSent 0x180 (all sent) */
void THISCALL (playerRecord_resetFlag)(Stage *stage, int p)
{
	PlayerRecord *pr = &stage->playerRecords[p];
	int colour = g_defaultColour;
	for (int k = 0; k < 16 * 24; k++)
		FIELD(int, pr->flag, k * 4) = colour;   /* (the 16 x 24 grid as one run) */
	pr->flagShown = 0;
	pr->flagChanged = 0;
	pr->flagSent = 0x180;
}
/* 0x48fc40: a map script's message (command 26: speaker a, text b, colour c, d twice) put in the stage's message ring
   of 32 (20 bytes each; Scene.msgRing shows them); when full the oldest is dropped */
void THISCALL (script_pushMessage)(Stage *stage, int a, int b, int c, int d)
{
	int *e = stage->messages[stage->msgWrite & 0x1f];
	e[0] = a;
	e[1] = b;
	e[2] = c;
	e[3] = d;
	e[4] = d;
	int head = ++stage->msgWrite;
	if (((stage->msgRead ^ head) & 0x1f) == 0)
		stage->msgRead++;
}
/* 0x48fca0: the map script's state reset. ScenePath's first method is called (shared_emptyFunction, the shared empty
   function). Then scriptMode, scriptHoldsPlay and the four undeclared dwords after them (Stage +0x2149310 ..
   +0x214931c) are cleared. Returns 0 */
int THISCALL (script_reset)(Stage *stage)
{
	shared_emptyFunction((Scene *)&stage->scenePath);   /* ScenePath's first method: the shared empty function */
	for (int i = 0; i < 6; i++)
		FIELD(int, stage, offsetof(Stage, scriptMode) + i * 4) = 0;   /* scriptMode, scriptHoldsPlay and four more */
	return 0;
}
/* player p counted among the players seen so far (the highest + 1) */
static void player_seen(Stage *stage, int p)
{
	u32 *seen = &(*(u32 *)&stage->playerRecordCount);
	if (p > (int)(*seen - 1))
		*seen = p + 1;
}

/* 0x473a10: player record p's pilot character set, and that of every actor of player p */
void THISCALL (player_setCharacter)(Stage *stage, int p, int v)
{
	player_seen(stage, p);
	stage->playerRecords[p].character = v;
	for (int i = 0; i < stage->actorCount; i++)
		if (stage->actors[i].player == p)
			stage->actors[i].character = v;
}
/* 0x48fe10: the stage's base matrix (baseMatrix) made the identity, its 200 points (points) put at the origin
   (g_vecOrigin), pointCount set to 0 and defaultColour to g_defaultColour */
void THISCALL (stage_resetMatrixAndPoints)(Stage *stage)
{
	for (int k = 0; k < 16; k++)
		BITS(stage->baseMatrix[k]) = k % 5 ? 0 : 0x3f800000;
	for (int k = 0; k < 200; k++)
		for (int j = 0; j < 3; j++)
			(*(int *)&stage->points[k][j]) = (*(int *)&g_vecOriginXyz[j]);
	stage->pointCount = 0;
	stage->defaultColour = g_defaultColour;
}

/* ---- matrices (16 dwords) ---- */
/* 0x47d5a0: copied (column by column) */
void (Mat4_copy)(u32 *d, const u32 *s)
{
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			d[r * 4 + c] = s[r * 4 + c];
}
/* 0x47d830: copied transposed */
void (Mat4_transpose)(u32 *d, const u32 *s)
{
	for (int k = 0; k < 16; k++)
		d[(k & 3) * 4 + (k >> 2)] = s[k];
}

/* ---- objects put to their start ---- */
/* 0x463a40: an actor's eight part lists (head .. the hand-held and shoulder weapons), each a UnitPoseInfo (vtable
   0x4a9754) with its members cleared (the element constructor of the stage's actors) */
void *THISCALL (actor_initPartLists)(u8 *self)
{
	static const int lists[8] = { offsetof(Player, headModel), offsetof(Player, chestModel), offsetof(Player, armsModel), offsetof(Player, legsModel), offsetof(Player, boosterModel), offsetof(Player, weaponModel), offsetof(Player, weaponModel4), offsetof(Player, weaponModel5) };
	for (int k = 0; k < 8; k++) {
		FIELD(u32, self, lists[k]) = VT(UnitPoseInfo, 0x4a9754);
		partList_clear(self + lists[k]);
	}
	return self;
}
/* 0x484260: the view volume emptied: its two 0xc01-dword tables and its counters */
void THISCALL (ViewVolume_reset)(u8 *self)
{
	ViewVolume *vw = (ViewVolume *)self;
	static const int cleared[] = { offsetof(ViewVolume, entryCount), offsetof(ViewVolume, matrixCount), offsetof(ViewVolume, triangleCount), offsetof(ViewVolume, quadCount), offsetof(ViewVolume, segmentCount), offsetof(ViewVolume, entriesFull), offsetof(ViewVolume, matricesFull), offsetof(ViewVolume, trianglesFull), offsetof(ViewVolume, quadsFull), offsetof(ViewVolume, segmentsFull) };
	vw->materialCount = 0;
	memset(vw->materialHeads, 0, 0xc01 * 4);
	memset(vw->materialTails, 0, 0xc01 * 4);
	for (int k = 0; k < 10; k++)
		FIELD(int, self, cleared[k]) = 0;
}
/* 0x481760: the collision space's units (its units pool), each emptied (spaceSlot_clear) and chained (poolPrev /
   poolNext) */
void THISCALL (space_resetUnits)(u8 *self)
{
	Space *sp = (Space *)self;
	for (int i = 0; i < sp->units.count; i++)
		spaceSlot_clear((int *)(sp->units.records + i * sizeof(SpaceUnit)));
	for (int i = 1; i < sp->units.count; i++) {
		u8 *e = sp->units.records + i * sizeof(SpaceUnit);
		((SpaceUnit *)e)->poolPrev = e - sizeof(SpaceUnit);
	}
	for (int i = 0; i < sp->units.count - 1; i++) {
		u8 *e = sp->units.records + i * sizeof(SpaceUnit);
		((SpaceUnit *)e)->poolNext = e + sizeof(SpaceUnit);
	}
	sp->units.used = 0;
	sp->units.freeHead = sp->units.records;
}
/* 0x461f10: the scene's input state cleared (two of its fields -1) */
void THISCALL (match_resetInputState)(Scene *scene)
{
	for (int *p = &scene->holdAltitude; p < scene->cleared2343323; p++)   /* holdAltitude .. presetNextAsked */
		*p = 0;
	scene->weaponKey = -1;
	scene->followKey = -1;
	memset(scene->cleared2343323, 0, sizeof scene->cleared2343323);
}

/* ---- the no-CD build (patched to return at once; the original checks are still behind the ret) ---- */
/* 0x401000: the CD drive found */
u32 (cd_findDrive)(void) { return 1; }
/* 0x41e550, 0x41e5b0, 0x41e610, 0x41e670, 0x41e6d0: the data files on the CD (Korean profile, skirmish, game,
   game data, English profile) found */
u32 (app_checkFile_profkor)(void) { return 1; }
u32 (app_checkFile_skirmish)(void) { return 1; }
u32 (app_checkFile_axisgame)(void) { return 1; }
u32 (app_checkFile_game)(void) { return 1; }
u32 (app_checkFile_profeng)(void) { return 1; }
/* 0x40d990: the retail game reset the edited and saved mech's SERAPHIM parts (head 19, chest 13, arm 17, booster
   15, leg 19) to 0; unlockfix.py turns all ten checks into jumps (the parts stay equipped), leaving nothing */
void (armc_resetSeraphimParts)(void) {}

/* ---- more small methods ---- */
void THISCALL (stage_triggerActionNone)(void *self, int a) { (void)self; (void)a; }
/* 0x45dfe0: the stage's actor without footstep sounds (silentActor) set (returned) */
int THISCALL (stage_setSilentActor)(Stage *stage, int v) { stage->silentActor = v; return v; }
/* 0x468720: the time sync object at g_loadTimer constructed */
void *(static_initTimeSync)(void) { return TimeSync_ctor((void *)OBJ(g_loadTimer)); }
/* 0x470f80: the stage's name (stageName: the map's name, the folder of Stage\<name>\Clan, its sounds and animations)
   set, upper-cased with back slashes (returned) */
char *THISCALL (stage_setName)(Stage *self, const char *folder)
{
	strcpy(self->stageName, folder);
	return path_normalize(self->stageName);
}
/* 0x461ec0: the scene's map name (mapName: loading reads <mapName>.bfd) and its stage's name (stage_setName) set */
void THISCALL (scene_setMapName)(Scene *scene, const char *folder)
{
	strcpy(scene->mapName, folder);
	stage_setName(STAGE(scene), folder);
}

/* 0x48fce0: script command 27. The script state is reset (script_reset), and the .scp path (scriptName) and the mode
   (scriptMode) are kept. Modes 0 and 2 clear scriptHoldsPlay, 1 sets it. Nothing reads the file:
   stage_advanceScenePath only hands the name to ScenePath's empty open, and clears scriptMode on the first frame.
   Returns 0 for those modes, else mode - 2 */
int THISCALL (script_startScenePath)(Stage *stage, const char *name, int mode)
{
	script_reset(stage);
	strcpy(stage->scriptName, name);
	stage->scriptMode = mode;
	if (mode == 0 || mode == 2) {
		stage->scriptHoldsPlay = 0;
		return 0;
	}
	if (mode == 1) {
		stage->scriptHoldsPlay = 1;
		return 0;
	}
	return mode - 2;
}

/* 0x46f770 (thiscall on a part list, ObjectList): when it has skeletons and i < skelCount, animation (skeleton) i is
   chosen (skel) and animTick is set to its duration (ms, Skeleton +0x20) times t, a 0 .. 1 fraction of the animation.
   Nothing happens otherwise */
void THISCALL (anim_setTime)(u8 *anim, int i, float scale)
{
	ObjectList *ol = (ObjectList *)anim;
	if (!ol->skeletons || i >= ol->skelCount)
		return;
	ol->skel = i;
	const int *frame = ((int **)ol->skeletons)[i];
	ol->animTick = ftol(fmul_m((long double)frame[8], &scale));
}

/* 0x4722e0: the stage's cull margin (cullMargin, the float's bits copied) set, and viewDepth = -v x
   viewProjection[10] + viewProjection[14] (written, never read). Its one caller (match_frame) passes cullMargin
   itself, so only viewDepth changes */
void THISCALL (stage_setCullMargin)(u8 *stage, u32 vBits)
{
	float v;
	Stage *st = (Stage *)stage;
	BITS(st->cullMargin) = vBits;   /* the float's bits copied, never through the FPU (which quiets a signalling NaN) */
	memcpy(&v, &vBits, 4);
	volatile long double n = -(long double)v;   /* negated first, as the original's fchs */
	st->viewDepth = (float)(n * st->viewProjection[10] + st->viewProjection[14]);
}

/* 0x473940: player p's name set (empty for none), and that of every actor of player p (name) */
void THISCALL (player_setName)(Stage *stage, int p, const char *name)
{
	player_seen(stage, p);
	char *dst = stage->playerRecords[p].name;
	if (name)
		strcpy(dst, name);
	else
		*dst = 0;
	for (int i = 0; i < stage->actorCount; i++) {
		Player *actor = &stage->actors[i];
		if (actor->player != p)
			continue;
		if (name)
			strcpy(actor->name, name);
		else
			actor->name[0] = 0;
	}
}

/* 0x473a80: player p's team set, and that of every actor of player p (one leaving the teams, team < 0, also loses
   state); the teams changed (rankingDirty) */
void THISCALL (player_setTeam)(Stage *stage, int p, int team)
{
	player_seen(stage, p);
	stage->playerRecords[p].team = team;
	for (int i = 0; i < stage->actorCount; i++) {
		Player *actor = &stage->actors[i];
		if (actor->player == p) {
			actor->team = team;
			if (team < 0)
				actor->state = 0;
		}
	}
	stage->rankingDirty = 1;
}

/* 0x496e40: unless a script holds play (scriptMode with scriptHoldsPlay 1), the sky layers' texture scroll
   (layerScroll u, v) advanced by dt x k_clockRate, wrapping at 1 and counting the turns (layerTurns). With floorMode
   2 (the animated floor), its clock (floorClock) is advanced by dt x k_clockRate3, stepping floorFrame 0 .. 15 at
   each 1 */
void THISCALL (stage_advanceClocks)(Stage *stage, float dt)
{
	typedef long double X;
	if (stage->scriptMode && stage->scriptHoldsPlay == 1)
		return;
	X d = (X)dt * k_clockRate, one = k_1f;
	for (int k = 0; k < 2; k++) {
		X a = d + stage->layerScroll[k];
		stage->layerScroll[k] = (float)a;
		if (a >= one) {
			stage->layerTurns[k]++;
			stage->layerScroll[k] = (float)(a - one);
		}
	}
	if (stage->floorMode != 2)
		return;
	X e = (X)dt * k_clockRate3 + stage->floorClock;
	stage->floorClock = (float)e;
	if (e >= one) {
		stage->floorFrame = (stage->floorFrame + 1) % 16;
		stage->floorClock = (float)(e - one);
	}
}

/* 0x470de0: the stage's nine folder names (+8, 0x100 bytes apart: stage, map, texture, shape, skeleton, actor,
   bullet, effect, scene), each upper-cased with back slashes */
void THISCALL (stage_setFolders)(u8 *self, const char *stageDir, const char *mapDir, const char *textureDir, const char *shapeDir, const char *skeletonDir,
                            const char *actorDir, const char *bulletDir, const char *effectDir, const char *sceneDir)
{
	const char *name[9] = { stageDir, mapDir, textureDir, shapeDir, skeletonDir, actorDir, bulletDir, effectDir, sceneDir };
	for (int k = 0; k < 9; k++) {
		strcpy((char *)self + 8 + k * 0x100, name[k]);
		path_normalize((char *)self + 8 + k * 0x100);
	}
}

/* 0x471010: the stage's collision space (space) set up as one cell over the level's bounds (levelLow .. levelHigh) */
void THISCALL (stage_initSpaceOneCell)(u8 *stage)
{
	Stage *st = (Stage *)stage;
	space_setBy((u8 *)&st->space, st->levelLow, st->levelHigh, 1, 1, 1, 0, 0, 0);
}

/* 0x470fc0: a message formatted and handed to the log hook (g_logHook) if one is set, with b and c (a unused) */
void (log_message)(int a, int b, int c, const char *format, ...)
{
	char text[0x400];
	(void)a;
	void (CDECL *hook)(int, int, const char *) = g_logHook;
	if (!hook)
		return;
	va_list args;
	va_start(args, format);
	vsprintf(text, format, args);
	va_end(args);
	hook(b, c, text);
}

/* ---- the registry: a DWORD value under HKCU\<the game's key> (0x4b0458) ---- */
#define RegOpenKeyExA(root, key, options, access, out) IMPORT(0x4a9004, int, u32, const char *, u32, u32, u32 *)(root, key, options, access, out)
#define RegSetValueExA(key, name, reserved, type, data, size) IMPORT(0x4a9000, int, u32, const char *, u32, u32, const void *, u32)(key, name, reserved, type, data, size)
#define RegCloseKey(key) IMPORT(0x4a900c, u32, u32)(key)

/* value written as name (a REG_DWORD); returns RegCloseKey's answer. The key's handle goes into the argument's own
   slot, so when the key can't be opened the original closes whatever RegOpenKeyExA left there */
static u32 reg_write(u32 value, const char *name)
{
	u32 key = value, data = value;
	if (!RegOpenKeyExA(0x80000001, (const char *)STR(0x4b0458, "SOFTWARE\\AxisArena\\Launcher"), 0, 0xf003f, &key))
		RegSetValueExA(key, name, 0, 4, &data, 4);
	return RegCloseKey(key);
}
/* 0x432400: the Ladder settings (kept under the registry key "Character"): the room's name (g_accountForm) and the other name (g_accountEmail) copied into
   the registry's copies (g_ladderId, g_ladderEmail; the first also into g_ladderIdCopy), the room settings record g_roomSettingsName (a
   32-byte name and six choices) into g_roomRecName; then under HKCU\<the game's key> (0x4b179c) the two names and the six
   choices as DWORDs (sign-extended but for the fourth and fifth). Returns RegCloseKey's answer (the key is closed
   even when it could not be opened) */
u32 (reg_writeLadderSettings)(void)
{
	strcpy(g_ladderId, g_accountName);
	strcpy(g_ladderEmail, g_accountEmail);
	strcpy(g_ladderIdCopy, g_ladderId);
	strcpy(g_roomRecName, g_roomSettingsName);
	memcpy((void *)ADDR(g_roomRecMap), (const void *)ADDR(g_roomMap), 6);
	u32 key;
	__asm__("" : "=m"(key));   /* left as the stack has it: a failed open leaves it so, and the original closes it anyway */
	if (!RegOpenKeyExA(0x80000001, (const char *)STR(0x4b179c, "SOFTWARE\\AxisArena\\Character"), 0, 0xf003f, &key)) {
		RegSetValueExA(key, (const char *)STR(0x4b1794, "Name"), 0, 1, (const void *)OBJ(g_ladderId), 0x1e);   /* REG_SZ */
		RegSetValueExA(key, (const char *)STR(0x4b1788, "GameName"), 0, 1, (const void *)OBJ(g_roomRecName), 0x20);
		const signed char *choice = (const signed char *)ADDR(g_roomRecMap);
		static const u32 names[6] = { STR(0x4b1784, "Map"), STR(0x4b1778, "PlayerNum"), STR(0x4b176c, "GameType"), STR(0x4b1760, "FlagLimit"), STR(0x4b1754, "TimeLimit"), STR(0x4b1748, "Customize") };
		static const u8 order[6] = { 0, 1, 3, 4, 5, 2 };
		for (int i = 0; i < 6; i++) {
			int k = order[i];
			u32 data = (k == 4 || k == 5) ? (u8)choice[k] : (u32)(int)choice[k];
			RegSetValueExA(key, (const char *)RELOC(names[i]), 0, 4, &data, 4);
		}
	}
	return RegCloseKey(key);
}

/* 0x41f880, 0x43f7f0: the end mode and the start mode */
u32 (reg_writeEndMode)(u32 value) { return reg_write(value, (const char *)STR(0x4b0450, "EndMode")); }
u32 (reg_writeStartMode)(u32 value) { return reg_write(value, (const char *)STR(0x4b29dc, "StartMode")); }

/* 0x44ace0: the chat line's typing ended. g_keptChat (0x400 bytes) is cleared and, when the typed line (g_chatLine)
   is not empty, the whole buffer is copied into it and g_chatTyping cleared. The text field is closed
   (g_textFieldOpen 0), the key state reset (input_resetKeys) and the keyboard taken again (input_initKeyboard).
   Returns that call's eax */
u32 (chat_endTyping)(void)
{
	memset((void *)ADDR(g_keptChatLine), 0, 0x400);
	if (strlen(g_chatLine)) {
		memcpy((void *)ADDR(g_keptChatLine), (const void *)OBJ(g_chatLine), 0x400);
		g_chatTyping = 0;
	}
	g_textFieldOpen = 0;
	input_resetKeys();   /* input_resetKeys: the key state */
	return (u32)input_initKeyboard(g_hWndMain);
}

/* 0x42ef30: a display mode change's problem reported (ChangeDisplaySettings' answer): codes 1 and -1 .. -5 each show their message (MSG(103, "SYSTEM MODE CHANGE RESTART") ..) in a box titled
   MSG(100, "USERMESSAGE") over the main window; returns the box's answer, or the code itself when it has no message */
int (app_reportDisplayModeError)(int code)
{
	u32 text;
	switch (code) {
	case 1: text = MSG(103, "SYSTEM MODE CHANGE RESTART"); break;
	case -4: text = MSG(104, "SYSTEM MODE CHANGE INVALID FLAGS"); break;
	case -5: text = MSG(105, "SYSTEM MODE CHANGE INVALID PARAMETER"); break;
	case -1: text = MSG(106, "SYSTEM MODE CHANGE FAILED"); break;
	case -2: text = MSG(107, "SYSTEM MODE CHANGE INVALID MODE"); break;
	case -3: text = MSG(108, "SYSTEM MODE CHANGE NOTUPDATED"); break;
	default: return code;
	}
	return MessageBoxA(g_mainWindow, (const char *)RELOC(text), (const char *)MSG(100, "USERMESSAGE"), 0);
}


#define RegQueryValueExA(key, name, reserved, type, data, size) IMPORT(0x4a9008, int, u32, const char *, u32, u32 *, void *, u32 *)(key, name, reserved, type, data, size)

/* the six choices (0x5b1b50 ..) in the order the registry keeps them, with their value names; the fourth and fifth
   (the flag and time limits) are unsigned */
static const u8 choice_order[6] = { 0, 1, 3, 4, 5, 2 };
static const u32 choice_names[6] = { STR(0x4b1784, "Map"), STR(0x4b1778, "PlayerNum"), STR(0x4b176c, "GameType"), STR(0x4b1760, "FlagLimit"), STR(0x4b1754, "TimeLimit"), STR(0x4b1748, "Customize") };
static u32 choice_dword(int k)
{
	const signed char *choice = (const signed char *)ADDR(g_roomRecMap);
	return (k == 4 || k == 5) ? (u8)choice[k] : (u32)(int)choice[k];
}

/* a string value read into dest (size bytes, cleared first); a missing one gets dest written as it is */
static void read_string(u32 key, const char *name, char *dest, u32 size, u32 *type, char *buf)
{
	u32 got = size;
	if (!RegQueryValueExA(key, name, 0, type, buf, &got)) {
		memset(dest, 0, size);
		strcpy(dest, buf);
	} else
		RegSetValueExA(key, name, 0, 1, dest, size);   /* REG_SZ */
}

/* 0x42bee0: the Ladder settings read back (reg_writeLadderSettings' mirror). First the defaults: the
   name "AxisPlayer" (g_ladderId), the game "Axis Ladder Game" (g_roomRecName), the choices 0, 8, 0, 0, 10, 10. Under
   HKCU\SOFTWARE\AxisArena\Character, created when missing: a new key gets them all written; an existing one has
   each read, and one it lacks written as the default. Then the limits kept within 5 .. 30, the map within 0 .. 21
   (else 0), the players 0 .. 16 (else 8), the game type 0 .. 11 (else 0), and the key closed. The caller ignores
   the eax it leaves */
void (reg_readLadderSettings)(void)
{
	strcpy(g_ladderId, (const char *)STR(0x4b17d0, "AxisPlayer"));
	strcpy(g_roomRecName, (const char *)STR(0x4b17bc, "Axis Ladder Game"));
	static const u8 defaults[6] = { 0, 8, 0, 0, 10, 10 };
	memcpy((void *)ADDR(g_roomRecMap), defaults, 6);
	u32 key, disposition, type, value;
	char buf[0x400];
	__asm__("" : "=m"(disposition));   /* left as the stack has it when the key can't be created, as in the original */
	IMPORT(0x4a9010, int, u32, const char *, u32, const char *, u32, u32, void *, u32 *, u32 *)
		(0x80000001, (const char *)STR(0x4b179c, "SOFTWARE\\AxisArena\\Character"), 0, NULL, 0, 0xf003f, NULL, &key, &disposition);   /* RegCreateKeyExA */
	signed char *choice = (signed char *)ADDR(g_roomRecMap);
	if (disposition == 1) {   /* REG_CREATED_NEW_KEY */
		RegSetValueExA(key, (const char *)STR(0x4b1794, "Name"), 0, 1, (const void *)OBJ(g_ladderId), 0x1e);
		RegSetValueExA(key, (const char *)STR(0x4b1788, "GameName"), 0, 1, (const void *)OBJ(g_roomRecName), 0x20);
		for (int i = 0; i < 6; i++) {
			value = choice_dword(choice_order[i]);
			RegSetValueExA(key, (const char *)RELOC(choice_names[i]), 0, 4, &value, 4);
		}
	} else if (disposition == 2) {   /* REG_OPENED_EXISTING_KEY */
		read_string(key, (const char *)STR(0x4b1794, "Name"), g_ladderId, 0x1e, &type, buf);
		read_string(key, (const char *)STR(0x4b1788, "GameName"), g_roomRecName, 0x20, &type, buf);
		u32 size = 4;   /* set once: each read leaves the size it found for the next (as in the original) */
		value = 0;
		for (int i = 0; i < 6; i++) {
			int k = choice_order[i];
			if (!RegQueryValueExA(key, (const char *)RELOC(choice_names[i]), 0, &type, &value, &size))
				choice[k] = (signed char)value;
			else {
				value = choice_dword(k);
				RegSetValueExA(key, (const char *)RELOC(choice_names[i]), 0, 4, &value, 4);
			}
		}
	} else
		return;
	u8 *limit = (u8 *)ADDR(g_roomRecFragLimit);
	for (int k = 0; k < 2; k++)
		limit[k] = limit[k] < 5 ? 5 : limit[k] > 30 ? 30 : limit[k];
	if (choice[0] < 0 || choice[0] > 0x15)
		choice[0] = 0;
	if (choice[1] < 0 || choice[1] > 0x10)
		choice[1] = 8;
	if (choice[3] < 0 || choice[3] > 0xb)
		choice[3] = 0;
	RegCloseKey(key);
}

/* 0x42bde0: the server settings read from HKCU\SOFTWARE\AxisArena\SelectServer (AxisPlay.exe's choice): TcpDNS and
   LadderDNS (the game-list and ladder servers, 50 bytes; the second read with the size the first left) and their
   ports (TcpPort, LadderPort). Without the key a
   message (which one by g_language), the key's unset handle closed (as the original does) and the main window closed.
   Returns the last call's eax */
int (reg_readServerSettings)(void)
{
	u32 key, type, size;
	if (RegOpenKeyExA(0x80000001, (const char *)STR(0x4b1728, "SOFTWARE\\AxisArena\\SelectServer"), 0, 0xf003f, &key)) {
		sys_messageBox((const char *)(g_language == 1 ? STR(0x4b16a4, "     \260\324\300\323\274\255\271\366\270\246 \274\261\305\303\307\317\301\366 \276\312\276\322\275\300\264\317\264\331.\n...") : STR(0x4b1660, "     Cannot find Server list.\nSelect ...")));
		RegCloseKey(key);
		return PostMessageA(g_mainWindow, 0x10, 0, 0);   /* WM_CLOSE */
	}
	size = 50;
	RegQueryValueExA(key, (const char *)STR(0x4b1720, "TcpDNS"), 0, &type, (void *)OBJ(g_tcpDns), &size);
	RegQueryValueExA(key, (const char *)STR(0x4b1714, "LadderDNS"), 0, &type, (void *)OBJ(g_ladderDns), &size);
	size = 4;
	RegQueryValueExA(key, (const char *)STR(0x4b170c, "TcpPort"), 0, &type, (void *)ADDR(g_lobbyTcpPort), &size);
	RegQueryValueExA(key, (const char *)STR(0x4b1700, "LadderPort"), 0, &type, (void *)ADDR(g_ladderPort), &size);
	return RegCloseKey(key);
}

/* 0x43f640: the screen size (g_screenW x g_screenH) for video mode g_videoMode: 640x480, 1280x720, 1600x900, 1920x1080,
   2560x1440, 3840x2160, 1024x768, or 7 the desktop's (g_desktopWidth x g_desktopHeight); any mode also sets g_simpleMenu from
   g_cfgSimpleMenu, which it returns */
int (app_screenSizeForMode)(void)
{
	static const int sizes[7][2] = { { 640, 480 }, { 1280, 720 }, { 1600, 900 }, { 1920, 1080 }, { 2560, 1440 },
	                                 { 3840, 2160 }, { 1024, 768 } };
	u32 mode = g_videoMode;
	if (mode < 7) {
		g_screenW = sizes[mode][0];
		g_screenH = sizes[mode][1];
	} else if (mode == 7) {
		g_screenW = g_desktopWidth;
		g_screenH = g_desktopHeight;
	}
	return g_simpleMenu = g_cfgSimpleMenu;
}


/* 0x43f300: a clock set back? The seconds passed by the system clock since the last check (g_clockLastTime, minutes and
   seconds; an hour change counts 60 more minutes; into g_clockCheckSeconds) against the seconds passed by timeGetTime (from
   g_startTicks; into g_clockCheckTickSeconds): when the clock's are fewer than 0.7 of them, a message (by the language g_language) and
   either the window closed (g_clockCheckQuits; 1) or 0 with the check restarted. Otherwise the check restarts and 1 */
int (sys_checkClockTampering)(void)
{
	const u16 *now = g_clockNowTime, *last = g_clockLastTime;   /* SYSTEMTIME: [4] hour, [5] minute, [6] second */
	GetSystemTime((void *)OBJ(g_clockNowTime));
	u32 tick = timeGetTime();
	g_clockCheckTick = tick;
	u32 minutes = now[5] + (now[4] > last[4] ? 60 : 0);
	int seconds = minutes > last[5] ? (int)(minutes * 60 - last[5] * 60 - last[6] + now[6]) : (int)(now[6] - last[6]);
	u32 tickSeconds = (tick - g_startTicks) / 1000;
	g_clockCheckSeconds = seconds;
	g_clockCheckTickSeconds = tickSeconds;
	long double ticked = (long double)(uint64_t)tickSeconds;
	if (ticked * k_0_3 + (long double)(uint64_t)(u32)seconds < ticked) {   /* clock + 0.3 * ticks < ticks */
		sys_messageBox((const char *)(g_language == 1 ? STR(0x4b2914, "\300\337\270\370\265\307\260\305\263\252 \300\314\273\363\307\321 \307\301\267\316\261\327\267\245\300\314 \265\277\300\333\307\317\260\355...") : STR(0x4b2888, "Now Unauthorized program is running\n\n...")));
		if (g_clockCheckQuits) {
			PostMessageA(g_mainWindow, 0x10, 0, 0);   /* WM_CLOSE */
			return 1;
		}
		GetSystemTime((void *)OBJ(g_clockLastTime));
		g_startTicks = timeGetTime();
		return 0;
	}
	GetSystemTime((void *)OBJ(g_clockLastTime));
	g_startTicks = timeGetTime();
	return 1;
}

/* 0x48fd50 (thiscall on the stage; match_frame passes the frame's time dt). With a map script running (scriptMode),
   ScenePath is opened when it is not yet (scenePath_openStub with scriptName and "Scene"; opened is never set, so
   every time) and stepped (scenePath_advanceStub, which answers 0, so scriptMode is cleared). With a sound named
   (pathSound, never written), "scenePath\<name>" is played at volume 100. Its caller ignores the eax it leaves */
void THISCALL (stage_advanceScenePath)(u8 *scene, u32 path)
{
	Stage *st = (Stage *)scene;
	if (!st->scriptMode)
		return;
	if (!st->scenePath.opened)
		scenePath_openStub((u8 *)&st->scenePath, st->scriptName, (const void *)STR(0x4c45e4, "Scene"));
	if (!scenePath_advanceStub((u8 *)&st->scenePath, path))
		st->scriptMode = 0;
	const char *name = st->pathSound;
	if (*name) {
		char text[0x100];
		sprintf(text, (const char *)STR(0x4c8304, "scenePath\\%s"), name);
		sound_playFile(text, 100);
	}
}

/* 0x4742f0 (thiscall on the stage): player p set from an actor record: its name (+8), character (+4), team (team), the
   parts (head, chest, arm, leg, booster: parts .. parts[4]), the six items (items ..), then marked in use. Its caller
   ignores the eax it leaves */
void THISCALL (playerRecord_setFromMapPlayer)(Stage *stage, int p, const u8 *rec)
{
	const MapPlayer *mp = (const MapPlayer *)rec;
	player_setName(stage, p, mp->name);
	player_setCharacter(stage, p, mp->character);
	player_setTeam(stage, p, mp->team);
	actor_setActorTypeHeadInfoBy(stage, p, mp->parts[0]);
	actor_setActorTypeChestInfoBy(stage, p, mp->parts[1]);
	actor_setActorTypeArmInfoBy(stage, p, mp->parts[2]);
	actor_setActorTypeLegInfoBy(stage, p, mp->parts[3]);
	actor_setActorTypeBoosterInfoBy(stage, p, mp->parts[4]);
	for (int k = 0; k < 6; k++)
		actor_setActorTypeItemInfoBy(stage, p, k, mp->items[k]);
	player_markUsed(stage, p);
}

/* 0x474210 (thiscall on the stage): player p set from its pieces: name, character, team, the five parts, the six items,
   then marked in use (as playerRecord_setFromMapPlayer does from a record). Its caller ignores the eax it leaves */
void THISCALL (playerRecord_set)(Stage *stage, int p, const char *name, int character, int team, int head, int chest, int arm, int leg,
                             int booster, int i0, int i1, int i2, int i3, int i4, int i5)
{
	player_setName(stage, p, name);
	player_setCharacter(stage, p, character);
	player_setTeam(stage, p, team);
	actor_setActorTypeHeadInfoBy(stage, p, head);
	actor_setActorTypeChestInfoBy(stage, p, chest);
	actor_setActorTypeArmInfoBy(stage, p, arm);
	actor_setActorTypeLegInfoBy(stage, p, leg);
	actor_setActorTypeBoosterInfoBy(stage, p, booster);
	int items[6] = { i0, i1, i2, i3, i4, i5 };
	for (int k = 0; k < 6; k++)
		actor_setActorTypeItemInfoBy(stage, p, k, items[k]);
	player_markUsed(stage, p);
}

/* a part kind as actor_setActorType*InfoBy set it: the player's field, the stage's type count, the fatal message, the
   player's shape and skeleton caches, the types' names (+stride each) and the player's copy, the actors' reload */
typedef struct {
	u16 field;
	u32 count, message, shapes, skels, names, stride;
	u16 name;
	u32 reload;
} PartKind;
static const PartKind part_kinds[5] = {
	{ offsetof(PlayerRecord, parts[0]), offsetof(Stage, headTypeCount), STR(0x4c75f0, "invalid headIndex(%d) - setActorTypeH..."), offsetof(PlayerRecord, headShapes), offsetof(PlayerRecord, headSkels), offsetof(Stage, headTypes), sizeof(HeadType), offsetof(PlayerRecord, partNames[0]), FN_ADDR(actor_loadHead, 0x45e1f0) },     /* head */
	{ offsetof(PlayerRecord, parts[1]), offsetof(Stage, chestTypeCount), STR(0x4c7624, "invalid chestIndex(%d) - setActorType..."), offsetof(PlayerRecord, chestShapes), offsetof(PlayerRecord, chestSkels), offsetof(Stage, chestTypes), sizeof(ChestType), offsetof(PlayerRecord, partNames[1]), FN_ADDR(actor_loadChest, 0x45e2c0) },    /* chest (actor_loadChest) */
	{ offsetof(PlayerRecord, parts[2]), offsetof(Stage, armTypeCount), STR(0x4c7658, "invalid armIndex(%d) - setActorTypeAr..."), offsetof(PlayerRecord, armShapes), offsetof(PlayerRecord, armSkels), offsetof(Stage, armTypes), sizeof(ArmType), offsetof(PlayerRecord, partNames[2]), FN_ADDR(actor_loadArms, 0x45e390) },  /* arms */
	{ offsetof(PlayerRecord, parts[3]), offsetof(Stage, legTypeCount), STR(0x4c7688, "invalid legIndex(%d) - setActorTypeLe..."), offsetof(PlayerRecord, legShapes), offsetof(PlayerRecord, legSkels), offsetof(Stage, legTypes), sizeof(LegType), offsetof(PlayerRecord, partNames[3]), FN_ADDR(actor_loadLegs, 0x45e460) }, /* legs */
	{ offsetof(PlayerRecord, parts[4]), offsetof(Stage, boosterTypeCount), STR(0x4c76b8, "invalid boosterIndex(%d) - setActorTy..."), offsetof(PlayerRecord, boosterShapes), offsetof(PlayerRecord, boosterSkels), offsetof(Stage, boosterTypes), sizeof(BoosterType), offsetof(PlayerRecord, partNames[4]), FN_ADDR(actor_loadBooster, 0x45e530) }, /* booster */
};

/* player p's part of kind k set to type (its record at playerRecords, 0x47fd2 bytes each): none for a negative type (0);
   the player count (playerRecordCount) grows to cover p; the same type again is 1 at once. A type past the count is a fatal
   message (the game exits); then the player's caches emptied, the type's name copied, the type
   stored, and each of the player's actors reloads the part; 1 */
static int set_part(u8 *scene, int p, int type, const PartKind *k)
{
	Stage *st = (Stage *)scene;
	if (type < 0)
		return 0;
	u8 *pl = (u8 *)&st->playerRecords[p];
	if (p > st->playerRecordCount - 1)
		st->playerRecordCount = p + 1;
	if (GAME_VAR(int, pl + k->field) == type)
		return 1;
	if (type >= GAME_VAR(int, scene + k->count))
		sys_fatalError((char *)OBJ(g_logStage), (const char *)(uintptr_t)k->message, type);
	ShapeManager_releaseModels(pl + k->shapes);
	SkeletonManager_releaseSkeletons(pl + k->skels);
	strcpy((char *)pl + k->name, (const char *)scene + k->names + type * k->stride);
	GAME_VAR(int, pl + k->field) = type;
	for (int i = 0; i < st->actorCount; i++)
		if (st->actors[i].player == p)
			GAME_THISCALL(k->reload, void, void *, int)(scene, i);
	return 1;
}

/* 0x473b10, 0x473c20, 0x473d30, 0x473e40, 0x473f50 (thiscall on the stage): player p's head, chest, arms, legs and
   booster type */
int THISCALL (actor_setActorTypeHeadInfoBy)(Stage *stage, int p, int type) { return set_part((u8 *)stage, p, type, &part_kinds[0]); }
int THISCALL (actor_setActorTypeChestInfoBy)(Stage *stage, int p, int type) { return set_part((u8 *)stage, p, type, &part_kinds[1]); }
int THISCALL (actor_setActorTypeArmInfoBy)(Stage *stage, int p, int type) { return set_part((u8 *)stage, p, type, &part_kinds[2]); }
int THISCALL (actor_setActorTypeLegInfoBy)(Stage *stage, int p, int type) { return set_part((u8 *)stage, p, type, &part_kinds[3]); }
int THISCALL (actor_setActorTypeBoosterInfoBy)(Stage *stage, int p, int type) { return set_part((u8 *)stage, p, type, &part_kinds[4]); }

/* 0x474060 (thiscall on the stage): player p's item in slot set (its player record at playerRecords, 0x47fd2 bytes
   each: the item (items[slot]) and its name (itemNames[slot])). Game types 2 .. 11 (gameType) fix the
   first slot (3, 5, 0x24, 0x19, 0x16 by pairs; 10 / 11 the second too, 0x17) and leave the others empty (-1); else
   the item given (negative: empty). An item past the catalogue (actorItemCount) is a fatal message. Each of the player's
   actors then has the slot updated (actor_loadWeapon, with its variantLoaded). The callers ignore the eax it leaves */
void THISCALL (actor_setActorTypeItemInfoBy)(Stage *stage, int p, int slot, int item)
{
	u8 *scene = (u8 *)stage;
	Stage *st = (Stage *)scene;
	PlayerRecord *type = &st->playerRecords[p];
	static const int fixed[5] = { 3, 5, 0x24, 0x19, 0x16 };
	unsigned mode = st->gameType - 2;
	if (mode <= 9)
		item = slot == 0 ? fixed[mode / 2] : mode >= 8 && slot == 1 ? 0x17 : -1;
	if (item >= 0)
		strcpy(((PlayerRecord *)RELOC(type))->itemNames[slot], (const char *)(u8 *)&st->actorItems[item]);
	else
		type->itemNames[slot][0] = 0;
	if (item >= st->actorItemCount)
		sys_fatalError((char *)OBJ(g_logStage), (const char *)STR(0x4c76f0, "invalid itemIndex(%d) - setActorTypeI..."), item);
	type->items[slot] = item;
	for (int i = 0; i < st->actorCount; i++)
		if (st->actors[i].player == p)
			actor_loadWeapon(scene, i, slot, st->actors[i].variantLoaded);
}
