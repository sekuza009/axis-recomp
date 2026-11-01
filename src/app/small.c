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
void *THISCALL (ResourceSet_trivialCtor)(void *self) { return self; }
int THISCALL (recorder_setPathStub)(void *self, int a) { (void)self; (void)a; return 0; }
void THISCALL (recorder_openStub)(void *self, int a0, int a1) { (void)self; (void)a0; (void)a1; }
void THISCALL (recorder_noteStub)(void *self, int a0, int a1, int a2, int a3) { (void)self; (void)a0; (void)a1; (void)a2; (void)a3; }
/* 0x43f770: the start mode from the registry - always 1 in this build */
u32 (reg_readStartMode)(void) { return 1; }

/* ---- setters of single globals (they return the value) ---- */
int (text_setWrapX)(int v) { g_textWrapX = v; return v; }
int (text_setBottom)(int v) { g_textBottom = v; return v; }
int (view_setAngle)(int v) { (*(int *)&g_viewFov) = v; return v; }

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
/* 0x463670, 0x463690, 0x4636b0: one of three requests raised (and the "something requested" flag) */
void THISCALL (event_raise3)(Scene *scene) { FIELD(int, scene, 0x2343237) = 1; FIELD(int, scene, 0x2343106) = 1; }
void THISCALL (event_raise4)(Scene *scene) { FIELD(int, scene, 0x234323b) = 1; FIELD(int, scene, 0x2343106) = 1; }
void THISCALL (event_raise5)(Scene *scene) { FIELD(int, scene, 0x234323f) = 1; FIELD(int, scene, 0x2343106) = 1; }
/* 0x463780: team slot i's id */
int THISCALL (scene_teamSlot)(Scene *scene, int i) { return scene->teamIds[i]; }
/* 0x474390: player record p marked used; 0x4743b0: marked free, its colour grid cleared */
void THISCALL (playerRecord_markUsed)(Stage *stage, int p) { FIELD(int, stage, 0x1561b68 + p * 0x47fd2) = 1; }
void THISCALL (playerRecord_markFree)(Stage *stage, int p)
{
	FIELD(int, stage, 0x1561b68 + p * 0x47fd2) = 0;
	playerRecord_resetColourGrid(stage, p);
}
/* 0x45df90: the stage's 100 actor references cleared */
void THISCALL (stage_clearActorRefs)(Stage *stage) { clear((u8 *)stage + 0x202e8f0, 100); }
/* 0x45e1c0: every actor in use switched off */
void THISCALL (stage_deactivateActors)(Stage *stage)
{
	for (int i = 0; i < stage->actorCount; i++)
		actor_deactivate(stage, i);
}
/* 0x4723e0: the stage's lights reset */
int THISCALL (stage_resetLights)(Stage *stage)
{
	FIELD(int, stage, 0x9d800c) = 0;
	return Light_clearCounts((u8 *)stage + 0x9d8010);
}

/* ---- small objects ---- */
/* 0x480440: an empty slot: -1 and four zeros */
void THISCALL (spaceSlot_clear)(int *self) { self[1] = self[2] = self[3] = self[4] = 0; self[0] = -1; }
/* 0x469980, 0x46f480: members cleared (0x46f480 keeps the sixth) */
void THISCALL (Skeleton_clear)(int *self) { for (int i = 1; i <= 7; i++) self[i] = 0; }
void THISCALL (partList_clear)(int *self) { for (int i = 1; i <= 11; i++) if (i != 6) self[i] = 0; }
/* 0x4699a0, 0x46f4b0: the owned buffer (+8 while +0xc is 1) freed, then the members cleared */
static void free_owned(void *self)
{
	if (FIELD(int, self, 0xc) == 1) {
		operator_delete(FIELD(void *, self, 8));
		FIELD(void *, self, 8) = NULL;
		FIELD(int, self, 0xc) = 0;
	}
}
int THISCALL (Skeleton_release)(void *self) { free_owned(self); Skeleton_clear(self); return 0; }
int THISCALL (partList_release)(void *self) { free_owned(self); partList_clear(self); return 0; }
/* 0x46f470: UnitPoseInfo's destructor (vtable 0x4a9754) */
int THISCALL (UnitPoseInfo_dtor)(u32 *self) { self[0] = IMG(0x4a9754); return partList_release(self); }
/* 0x46ce50: the object's file closed (fclose's result, 0 for none) */
u32 THISCALL (BMPRGBFile_close)(u32 *self) { return self[1] ? fclose((void *)RELOC(self[1])) : 0; }
/* 0x467d60: p freed (operator delete's eax; 0 for none) */
u32 (mem_free)(void *p) { return p ? GAME_CDECL(0x49ef24, u32, void *)(p) : 0; }

/* ---- network tables cleared ---- */
void (net_clearServerList)(void) { clear((void *)IMG(0xa05748), 0x16c0); }
void (net_clearRoomList)(void) { clear((void *)IMG(0x9fd960), 0x1e40); }
void (net_clearPlayerList)(void) { clear((void *)IMG(0xa05330), 0x9b); }
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

/* 0x451530: every one of the 16 network slots (0x410 bytes from 0x9f9840: +4 the owner) owned by id emptied, its
   flag (0x9f93d8) too; slot 0 freed sets 0x9fd94c. Leaves 0xff in AL */
u8 (net_freeSlotsOf)(int id)
{
	for (int s = 0; s < 16; s++) {
		u32 r = IMG(0x9f9840) + s * 0x410;
		if (GAME_VAR(int, r + 4) != id)
			continue;
		GAME_VAR(int, r) = GAME_VAR(int, r + 4) = GAME_VAR(int, r + 8) = GAME_VAR(int, r + 0xc) = 0;
		GAME_VAR(int, 0x9f93d8 + s * 4) = 0;
		if (s == 0)
			g_netHostGone = 1;
	}
	return 0xff;
}

/* 0x430bd0: the 16 entries of 0x410 bytes from 0x9f9840 marked empty */
void (net_clearSlots)(void) { for (u32 p = IMG(0x9f9840); p < IMG(0x9fd940); p += 0x410) GAME_VAR(int, p) = 0; }

/* ---- front end ---- */
/* 0x453a30: 1 if connection kind i (0 .. 3) is available */
int (net_connectionAvailable)(u32 i) { return i < 4 && GAME_VAR(int, 0xa0bae0 + i * 4) ? 1 : 0; }
/* 0x4417c0: map i of the map-select dialog in or out; 0x4417f0: all in (0x44-byte entries from 0x9ddac8) */
void (mapSelect_toggle)(int i) { int *f = (int *)(IMG(0x9ddac8) + i * 0x44); *f = 1 - *f; }
void (mapSelect_allIn)(void) { for (int i = 0; i < g_mapSelectCount; i++) GAME_VAR(int, 0x9ddac8 + i * 0x44) = 1; }
/* 0x447af0: a click closes the mission briefing */
void (briefing_clickClose)(void) { if (g_dialogOpen == 0 && g_mouseClick != 0) g_missionStarted = 0; }
/* 0x4411e0: the background tunnel's rings made again (tunnel_appendRing) */
u32 (tunnel_rebuild)(void) { g_tunnelRings = 0; return tunnel_appendRing((void *)IMG(0x67fb3c)); }
/* 0x44ad30: the text colour */
void (text_setColor)(u32 r, u32 g, u32 b, u32 a) { set_colour_bits((Colour *)IMG(0x76d438), r, g, b, a); }
/* 0x404120, 0x431db0, 0x44b080: a dialog's box rectangle */
void (arenaDialogBox_layout)(void) { set4ints(0x104, 0x118, 0x17c, 0x138, (int *)IMG(0x4dbad0)); }
void (gameListStop_layout)(void) { set4ints(0x104, 0x118, 0x17c, 0x138, (int *)IMG(0x9dd308)); }
void (profileDialogBox_layout)(void) { set4ints(0x1d7, 0xf6, 0x226, 0x114, (int *)IMG(0x9f9010)); }
/* 0x45dfb0: actor i selected when it is in use (any negative i: none selected) */
void THISCALL (stage_selectActor)(Stage *stage, int i)
{
	if (i < 0 || FIELD(int, stage, 0x1cd94f4 + i * 0x8888) == 1)
		FIELD(int, stage, 0x202e8d8) = i;
}
/* 0x456820: material m (0x68-byte records at +0xc016c) marked changed, its flags kept to the bits 0x11111113 (the
   original's guard, flags | 2, is always true) */
void THISCALL (tex_markMaterialChanged)(void *self, int m)
{
	u8 *r = (u8 *)self + m * 0x68;
	u32 f = FIELD(u32, r, 0xc016c);
	if ((f | 2) != 0) {
		FIELD(u32, r, 0xc016c) = f & 0x11111113;
		FIELD(int, r, 0xc018c) = 1;
	}
}
/* 0x456b50: three fields cleared in each of the six objects the object points to (+4 .. +0x18) */
void THISCALL (tex_clearSetCounters)(void *self)
{
	for (int k = 1; k <= 6; k++) {
		u8 *o = FIELD(u8 *, self, k * 4);
		FIELD(int, o, 0xcd138) = 0;
		FIELD(int, o, 0xcd13c) = 0;
		FIELD(int, o, 0xcd140) = 0;
	}
}
/* 0x473470: player record p's 16 x 24 colour grid filled with the colour at 0xa1f220, its three counters reset */
void THISCALL (playerRecord_resetColourGrid)(Stage *stage, int p)
{
	u8 *rec = (u8 *)stage + 0x1561b68 + p * 0x47fd2;
	int colour = g_defaultColour;
	for (int k = 0; k < 16 * 24; k++)
		FIELD(int, rec, 0x479c2 + k * 4) = colour;
	FIELD(int, rec, 0x47fc6) = 0;
	FIELD(int, rec, 0x47fca) = 0;
	FIELD(int, rec, 0x47fce) = 0x180;
}
/* 0x48fc40: an event (a, b, c, d, d) put in the stage's script ring of 32 (20 bytes each); when full the oldest is
   dropped */
void THISCALL (script_pushEvent)(Stage *stage, int a, int b, int c, int d)
{
	int *e = (int *)((u8 *)stage + 0x2148c50 + (FIELD(int, stage, 0x2148ed0) & 0x1f) * 20);
	e[0] = a;
	e[1] = b;
	e[2] = c;
	e[3] = d;
	e[4] = d;
	int head = ++FIELD(int, stage, 0x2148ed0);
	if (((FIELD(int, stage, 0x2148ed4) ^ head) & 0x1f) == 0)
		FIELD(int, stage, 0x2148ed4)++;
}
/* 0x48fca0: the script's six counters cleared */
int THISCALL (script_reset)(Stage *stage)
{
	debug_traceStripped((Scene *)stage);   /* an empty method of the stage */
	for (int i = 0; i < 6; i++)
		FIELD(int, stage, 0x2149308 + i * 4) = 0;
	return 0;
}
/* player p counted among the players seen so far (the highest + 1) */
static void player_seen(Stage *stage, int p)
{
	u32 *seen = &FIELD(u32, stage, 0x19e1888);
	if (p > (int)(*seen - 1))
		*seen = p + 1;
}
#define PLAYER_RECORD(stage, p) ((u8 *)RELOC(stage) + 0x1561b68 + (p) * 0x47fd2)

/* 0x473a10: player record p's value +0x44 set, and that of every actor of player p (+0x114) */
void THISCALL (player_setValue)(Stage *stage, int p, int v)
{
	player_seen(stage, p);
	FIELD(int, stage, 0x1561b68 + p * 0x47fd2 + 0x44) = v;
	for (int i = 0; i < stage->actorCount; i++)
		if (FIELD(int, &stage->actors[i], 0x10c) == p)
			FIELD(int, &stage->actors[i], 0x114) = v;
}
/* 0x48fe10: the stage's identity matrix, 200 points at the origin (0xa0e7a8), the colour at 0xa1f220 */
void THISCALL (stage_resetMatrixAndPoints)(Stage *stage)
{
	for (int k = 0; k < 16; k++)
		FIELD(u32, stage, 0x20f2fc8 + k * 4) = k % 5 ? 0 : 0x3f800000;
	for (int k = 0; k < 200; k++)
		for (int j = 0; j < 3; j++)
			FIELD(int, stage, 0x20f300c + k * 12 + j * 4) = GAME_VAR(int, 0xa0e7a8 + j * 4);
	FIELD(int, stage, 0x20f3008) = 0;
	FIELD(int, stage, 0x20f396c) = g_defaultColour;
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
/* 0x463a40: a resource set's eight lists, each a UnitPoseInfo (vtable 0x4a9754) with its members cleared */
void *THISCALL (ResourceSet_initLists)(u8 *self)
{
	static const int lists[8] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };
	for (int k = 0; k < 8; k++) {
		FIELD(u32, self, lists[k]) = IMG(0x4a9754);
		partList_clear(self + lists[k]);
	}
	return self;
}
/* 0x484260: the view volume emptied: its two 0xc01-dword tables and its counters */
void THISCALL (ViewVolume_reset)(u8 *self)
{
	static const int cleared[] = { 0x9038, 0x9044, 0x905c, 0x9070, 0x908c, 0x9090, 0x9094, 0x9098, 0x909c, 0x90a0 };
	FIELD(int, self, 0x3024) = 0;
	memset(self + 0x3028, 0, 0xc01 * 4);
	memset(self + 0x602c, 0, 0xc01 * 4);
	for (int k = 0; k < 10; k++)
		FIELD(int, self, cleared[k]) = 0;
}
/* 0x481760: the collision space's units: count at +0x30, the 0x14-byte units at +0x34, each emptied (spaceSlot_clear) and
   chained (prev at +0xc, next at +0x10) */
void THISCALL (space_resetUnits)(u8 *self)
{
	for (int i = 0; i < FIELD(int, self, 0x30); i++)
		spaceSlot_clear((int *)(FIELD(u8 *, self, 0x34) + i * 0x14));
	for (int i = 1; i < FIELD(int, self, 0x30); i++) {
		u8 *e = FIELD(u8 *, self, 0x34) + i * 0x14;
		FIELD(u8 *, e, 0xc) = e - 0x14;
	}
	for (int i = 0; i < FIELD(int, self, 0x30) - 1; i++) {
		u8 *e = FIELD(u8 *, self, 0x34) + i * 0x14;
		FIELD(u8 *, e, 0x10) = e + 0x14;
	}
	FIELD(int, self, 0x3c) = 0;
	FIELD(u8 *, self, 0x38) = FIELD(u8 *, self, 0x34);
}
/* 0x461f10: the scene's input state cleared (two of its fields -1) */
void THISCALL (match_resetInputState)(Scene *scene)
{
	for (int off = 0x234325f; off < 0x2343323; off += 4)
		FIELD(int, scene, off) = 0;
	FIELD(int, scene, 0x2343287) = -1;
	FIELD(int, scene, 0x2343307) = -1;
	memset((u8 *)scene + 0x2343323, 0, 10 * 4);
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
/* 0x45dfe0: the stage's actor without footstep sounds (+0x202e8dc) set (returned) */
int THISCALL (stage_setSilentActor)(Stage *stage, int v) { FIELD(int, stage, 0x202e8dc) = v; return v; }
/* 0x468720: the time sync object at 0xa0e948 constructed */
void *(static_initTimeSync)(void) { return TimeSync_ctor((void *)IMG(0xa0e948)); }
/* 0x470f80: an object's texture folder (+0x908) set, upper-cased with back slashes (returned) */
char *THISCALL (object_setTextureFolder)(void *self, const char *folder)
{
	strcpy((char *)self + 0x908, folder);
	return path_normalize((char *)self + 0x908);
}
/* 0x461ec0: the scene's texture folder (+0x1f35c8) and its stage's */
void THISCALL (scene_setTextureFolder)(Scene *scene, const char *folder)
{
	strcpy((char *)scene + 0x1f35c8, folder);
	object_setTextureFolder(STAGE(scene), folder);
}

/* 0x48fce0: a script file started: the script state reset, its name and mode kept; modes 0 and 2 clear the running
   flag, 1 sets it. Returns 0 for those modes, else mode - 2 */
int THISCALL (script_runScpFile)(Stage *stage, const char *name, int mode)
{
	script_reset(stage);
	strcpy((char *)stage + 0x2149208, name);
	FIELD(int, stage, 0x2149308) = mode;
	if (mode == 0 || mode == 2) {
		FIELD(int, stage, 0x214930c) = 0;
		return 0;
	}
	if (mode == 1) {
		FIELD(int, stage, 0x214930c) = 1;
		return 0;
	}
	return mode - 2;
}

/* 0x46f770: an animation's frame i chosen (when it has a frame table, +0x20, and i is below the count +0x1c), and its
   length (the frame's int at +0x20) times scale */
void THISCALL (anim_setFrame)(u8 *anim, int i, float scale)
{
	if (!FIELD(int, anim, 0x20) || i >= FIELD(int, anim, 0x1c))
		return;
	FIELD(int, anim, 0x24) = i;
	const int *frame = FIELD(int **, anim, 0x20)[i];
	FIELD(int, anim, 0x28) = ftol(fmul_m((long double)frame[8], &scale));
}

/* 0x4722e0: a view's distance set (+0xa08, the float's bits copied) and its depth -v * a + b from the stage's pair */
void THISCALL (view_setDistance)(u8 *view, u32 vBits)
{
	float v;
	FIELD(u32, view, 0xa08) = vBits;   /* the float's bits copied, never through the FPU (which quiets a signalling NaN) */
	memcpy(&v, &vBits, 4);
	volatile long double n = -(long double)v;   /* negated first, as the original's fchs */
	FIELD(float, view, 0xa0c) = (float)(n * FIELD(float, view, 0x20f3a9c) + FIELD(float, view, 0x20f3aac));
}

/* 0x473940: player p's name set (empty for none), and that of every actor of player p (+0x98) */
void THISCALL (player_setName)(Stage *stage, int p, const char *name)
{
	player_seen(stage, p);
	char *dst = (char *)PLAYER_RECORD(stage, p) + 4;
	if (name)
		strcpy(dst, name);
	else
		*dst = 0;
	for (int i = 0; i < stage->actorCount; i++) {
		u8 *actor = (u8 *)&stage->actors[i];
		if (FIELD(int, actor, 0x10c) != p)
			continue;
		if (name)
			strcpy((char *)actor + 0x98, name);
		else
			actor[0x98] = 0;
	}
}

/* 0x473a80: player p's team set, and that of every actor of player p (one leaving the teams, team < 0, also loses
   +0x14c); the teams changed (+0x202e8ec) */
void THISCALL (player_setTeam)(Stage *stage, int p, int team)
{
	player_seen(stage, p);
	FIELD(int, PLAYER_RECORD(stage, p), 0x48) = team;
	for (int i = 0; i < stage->actorCount; i++) {
		u8 *actor = (u8 *)&stage->actors[i];
		if (FIELD(int, actor, 0x10c) == p) {
			FIELD(int, actor, 0x118) = team;
			if (team < 0)
				FIELD(int, actor, 0x14c) = 0;
		}
	}
	FIELD(int, stage, 0x202e8ec) = 1;
}

/* 0x496e40: the stage's animation clocks advanced by dt (unless a script runs in mode 1): two at dt * the rate at
   0x4a9428, wrapping at 1 and counting the turns; in game mode 2 a third at dt * the rate at 0x4aa498, counting turns
   0 .. 15 */
void THISCALL (stage_advanceClocks)(Stage *stage, float dt)
{
	typedef long double X;
	if (FIELD(int, stage, 0x2149308) && FIELD(int, stage, 0x214930c) == 1)
		return;
	X d = (X)dt * k_clockRate, one = k_1f;
	for (int k = 0; k < 2; k++) {
		X a = d + FIELD(float, stage, 0x9ef0a8 + k * 4);
		FIELD(float, stage, 0x9ef0a8 + k * 4) = (float)a;
		if (a >= one) {
			FIELD(int, stage, 0x9ef0a0 + k * 4)++;
			FIELD(float, stage, 0x9ef0a8 + k * 4) = (float)(a - one);
		}
	}
	if (FIELD(int, stage, 0x9ef30c) != 2)
		return;
	X e = (X)dt * k_clockRate3 + FIELD(float, stage, 0x9ef900);
	FIELD(float, stage, 0x9ef900) = (float)e;
	if (e >= one) {
		FIELD(int, stage, 0x9ef8fc) = (FIELD(int, stage, 0x9ef8fc) + 1) % 16;
		FIELD(float, stage, 0x9ef900) = (float)(e - one);
	}
}

/* 0x470de0: nine names (+8, 0x100 bytes apart), each upper-cased with back slashes */
void THISCALL (object_setNames)(u8 *self, const char *s1, const char *s2, const char *s3, const char *s4, const char *s5,
                            const char *s6, const char *s7, const char *s8, const char *s9)
{
	const char *name[9] = { s1, s2, s3, s4, s5, s6, s7, s8, s9 };
	for (int k = 0; k < 9; k++) {
		strcpy((char *)self + 8 + k * 0x100, name[k]);
		path_normalize((char *)self + 8 + k * 0x100);
	}
}

/* 0x471010: the scene's level grid (+0xa10) set up as one cell over the level's bounds (+0x9ef904 .. +0x9ef910) */
void THISCALL (scene_initLevelGrid)(u8 *scene)
{
	space_setBy(scene + 0xa10, scene + 0x9ef904, scene + 0x9ef910, 1, 1, 1, 0, 0, 0);
}

/* 0x470fc0: a message formatted and handed to the log hook (0xae2ec8) if one is set, with b and c (a unused) */
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
	if (!RegOpenKeyExA(0x80000001, (const char *)IMG(0x4b0458), 0, 0xf003f, &key))
		RegSetValueExA(key, name, 0, 4, &data, 4);
	return RegCloseKey(key);
}
/* 0x432400: the player's name and character: the room's name (0x9dd1d8) and the other name (0x9dd20e) copied into
   the registry's copies (0x9dd570, 0x9dd5a6; the first also into 0x76d450), the character record 0x4df9c8 (a
   32-byte name and six choices) into 0x5b1b30; then under HKCU\<the game's key> (0x4b179c) the two names and the six
   choices as DWORDs (sign-extended but for the fourth and fifth). Returns RegCloseKey's answer (the key is closed
   even when it could not be opened) */
u32 (reg_writeCharacterSettings)(void)
{
	strcpy((char *)IMG(0x9dd570), (const char *)IMG(0x9dd1d8));
	strcpy((char *)IMG(0x9dd5a6), (const char *)IMG(0x9dd20e));
	strcpy((char *)IMG(0x76d450), (const char *)IMG(0x9dd570));
	strcpy((char *)IMG(0x5b1b30), (const char *)IMG(0x4df9c8));
	memcpy((void *)IMG(0x5b1b50), (const void *)IMG(0x4df9e8), 6);
	u32 key;
	__asm__("" : "=m"(key));   /* left as the stack has it: a failed open leaves it so, and the original closes it anyway */
	if (!RegOpenKeyExA(0x80000001, (const char *)IMG(0x4b179c), 0, 0xf003f, &key)) {
		RegSetValueExA(key, (const char *)IMG(0x4b1794), 0, 1, (const void *)IMG(0x9dd570), 0x1e);   /* REG_SZ */
		RegSetValueExA(key, (const char *)IMG(0x4b1788), 0, 1, (const void *)IMG(0x5b1b30), 0x20);
		const signed char *choice = (const signed char *)IMG(0x5b1b50);
		static const u32 names[6] = { IMG(0x4b1784), IMG(0x4b1778), IMG(0x4b176c), IMG(0x4b1760), IMG(0x4b1754), IMG(0x4b1748) };
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
u32 (reg_writeEndMode)(u32 value) { return reg_write(value, (const char *)IMG(0x4b0450)); }
u32 (reg_writeStartMode)(u32 value) { return reg_write(value, (const char *)IMG(0x4b29dc)); }

/* 0x44ace0: the typed chat line (0x9dc92c) kept as the match's last line (0x9f63e4, 0x400 bytes; cleared when there
   is none), typing off, the key state reset and the keyboard taken again. Returns that call's eax */
u32 (chat_keepLastLine)(void)
{
	memset((void *)IMG(0x9f63e4), 0, 0x400);
	if (strlen((const char *)IMG(0x9dc92c))) {
		memcpy((void *)IMG(0x9f63e4), (const void *)IMG(0x9dc92c), 0x400);
		g_chatTyping = 0;
	}
	g_paused = 0;
	input_resetKeys();   /* input_resetKeys: the key state */
	return (u32)input_initKeyboard(g_hWndMain);
}

/* 0x42ef30: a start-up problem reported: codes 1 and -1 .. -5 each show their message (0x7511a4 ..) in a box titled
   0x751024 over the main window; returns the box's answer, or the code itself when it has no message */
int (app_reportStartupProblem)(int code)
{
	u32 text;
	switch (code) {
	case 1: text = IMG(0x7511a4); break;
	case -4: text = IMG(0x751224); break;
	case -5: text = IMG(0x7512a4); break;
	case -1: text = IMG(0x751324); break;
	case -2: text = IMG(0x7513a4); break;
	case -3: text = IMG(0x751424); break;
	default: return code;
	}
	return MessageBoxA(g_mainWindow, (const char *)RELOC(text), (const char *)IMG(0x751024), 0);
}


#define RegQueryValueExA(key, name, reserved, type, data, size) IMPORT(0x4a9008, int, u32, const char *, u32, u32 *, void *, u32 *)(key, name, reserved, type, data, size)

/* the six choices (0x5b1b50 ..) in the order the registry keeps them, with their value names; the fourth and fifth
   (the flag and time limits) are unsigned */
static const u8 choice_order[6] = { 0, 1, 3, 4, 5, 2 };
static const u32 choice_names[6] = { IMG(0x4b1784), IMG(0x4b1778), IMG(0x4b176c), IMG(0x4b1760), IMG(0x4b1754), IMG(0x4b1748) };
static u32 choice_dword(int k)
{
	const signed char *choice = (const signed char *)IMG(0x5b1b50);
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

/* 0x42bee0: the player's name and character read back (reg_writeCharacterSettings' mirror). First the defaults: the
   name "AxisPlayer" (0x9dd570), the game "Axis Ladder Game" (0x5b1b30), the choices 0, 8, 0, 0, 10, 10. Under
   HKCU\SOFTWARE\AxisArena\Character, created when missing: a new key gets them all written; an existing one has
   each read, and one it lacks written as the default. Then the limits kept within 5 .. 30, the map within 0 .. 21
   (else 0), the players 0 .. 16 (else 8), the game type 0 .. 11 (else 0), and the key closed. The caller ignores
   the eax it leaves */
void (reg_readCharacterSettings)(void)
{
	strcpy((char *)IMG(0x9dd570), (const char *)IMG(0x4b17d0));
	strcpy((char *)IMG(0x5b1b30), (const char *)IMG(0x4b17bc));
	static const u8 defaults[6] = { 0, 8, 0, 0, 10, 10 };
	memcpy((void *)IMG(0x5b1b50), defaults, 6);
	u32 key, disposition, type, value;
	char buf[0x400];
	__asm__("" : "=m"(disposition));   /* left as the stack has it when the key can't be created, as in the original */
	IMPORT(0x4a9010, int, u32, const char *, u32, const char *, u32, u32, void *, u32 *, u32 *)
		(0x80000001, (const char *)IMG(0x4b179c), 0, NULL, 0, 0xf003f, NULL, &key, &disposition);   /* RegCreateKeyExA */
	signed char *choice = (signed char *)IMG(0x5b1b50);
	if (disposition == 1) {   /* REG_CREATED_NEW_KEY */
		RegSetValueExA(key, (const char *)IMG(0x4b1794), 0, 1, (const void *)IMG(0x9dd570), 0x1e);
		RegSetValueExA(key, (const char *)IMG(0x4b1788), 0, 1, (const void *)IMG(0x5b1b30), 0x20);
		for (int i = 0; i < 6; i++) {
			value = choice_dword(choice_order[i]);
			RegSetValueExA(key, (const char *)RELOC(choice_names[i]), 0, 4, &value, 4);
		}
	} else if (disposition == 2) {   /* REG_OPENED_EXISTING_KEY */
		read_string(key, (const char *)IMG(0x4b1794), (char *)IMG(0x9dd570), 0x1e, &type, buf);
		read_string(key, (const char *)IMG(0x4b1788), (char *)IMG(0x5b1b30), 0x20, &type, buf);
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
	u8 *limit = (u8 *)IMG(0x5b1b54);
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

/* 0x42bde0: the server settings read from HKCU\<0x4b1728>: the server name (0xa0b24c, 50 bytes), two more values
   (0xa055fc, 0xa05634; their size is what the read before left) and the port (0xa055f4, 4 bytes). Without the key a
   message (which one by 0x9dae74), the key's unset handle closed (as the original does) and the main window closed.
   Returns the last call's eax */
int (reg_readServerSettings)(void)
{
	u32 key, type, size;
	if (RegOpenKeyExA(0x80000001, (const char *)IMG(0x4b1728), 0, 0xf003f, &key)) {
		sys_messageBox((const char *)(g_language == 1 ? IMG(0x4b16a4) : IMG(0x4b1660)));
		RegCloseKey(key);
		return PostMessageA(g_mainWindow, 0x10, 0, 0);   /* WM_CLOSE */
	}
	size = 50;
	RegQueryValueExA(key, (const char *)IMG(0x4b1720), 0, &type, (void *)IMG(0xa0b24c), &size);
	RegQueryValueExA(key, (const char *)IMG(0x4b1714), 0, &type, (void *)IMG(0xa055fc), &size);
	size = 4;
	RegQueryValueExA(key, (const char *)IMG(0x4b170c), 0, &type, (void *)IMG(0xa055f4), &size);
	RegQueryValueExA(key, (const char *)IMG(0x4b1700), 0, &type, (void *)IMG(0xa05634), &size);
	return RegCloseKey(key);
}

/* 0x43f640: the screen size (0x5b1998 x 0x4e045c) for video mode 0x83a9c0: 640x480, 1280x720, 1600x900, 1920x1080,
   2560x1440, 3840x2160, 1024x768, or 7 the desktop's (0x67eefc x 0x76d430); any mode also sets 0x9da494 from
   0x83a9d8, which it returns */
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
	return g_texturesOff = g_cfgSimpleMenu;
}

#define GetSystemTime(st) IMPORT(0x4a910c, void, void *)(st)
#define timeGetTime() IMPORT(0x4a9364, u32, void)()

/* 0x43f300: a clock set back? The seconds passed by the system clock since the last check (0x9dd878, minutes and
   seconds; an hour change counts 60 more minutes; into 0x9dd860) against the seconds passed by timeGetTime (from
   0x9dd8e8; into 0x9dd8ec): when the clock's are fewer than 0.7 of them, a message (by the language 0x9dae74) and
   either the window closed (0x9dd904; 1) or 0 with the check restarted. Otherwise the check restarts and 1 */
int (sys_checkClockTampering)(void)
{
	const u16 *now = (const u16 *)IMG(0x9dd8d0), *last = (const u16 *)IMG(0x9dd878);   /* SYSTEMTIME: [4] hour, [5] minute, [6] second */
	GetSystemTime((void *)IMG(0x9dd8d0));
	u32 tick = timeGetTime();
	g_clockCheckTick = tick;
	u32 minutes = now[5] + (now[4] > last[4] ? 60 : 0);
	int seconds = minutes > last[5] ? (int)(minutes * 60 - last[5] * 60 - last[6] + now[6]) : (int)(now[6] - last[6]);
	u32 tickSeconds = (tick - g_startTicks) / 1000;
	g_clockCheckSeconds = seconds;
	g_clockCheckTickSeconds = tickSeconds;
	long double ticked = (long double)(uint64_t)tickSeconds;
	if (ticked * k_0_3 + (long double)(uint64_t)(u32)seconds < ticked) {   /* clock + 0.3 * ticks < ticks */
		sys_messageBox((const char *)(g_language == 1 ? IMG(0x4b2914) : IMG(0x4b2888)));
		if (g_clockCheckClosed) {
			PostMessageA(g_mainWindow, 0x10, 0, 0);   /* WM_CLOSE */
			return 1;
		}
		GetSystemTime((void *)IMG(0x9dd878));
		g_startTicks = timeGetTime();
		return 0;
	}
	GetSystemTime((void *)IMG(0x9dd878));
	g_startTicks = timeGetTime();
	return 1;
}

/* 0x48fd50 (thiscall on the scene): with a recording on (+0x2149308): the recorder (+0x2148ed8) opened when it is not
   yet (+0x2148ee0; recorder_openStub with +0x2149208 and 0x4c45e4) and the path given to it (recorder_setPathStub; failing, the
   recording off); with a name for it (+0x2149108) a sound played (the name formatted by 0x4c8304) at volume 100.
   Its caller ignores the eax it leaves */
void THISCALL (scene_loadPath)(u8 *scene, u32 path)
{
	if (!GAME_VAR(int, scene + 0x2149308))
		return;
	if (!GAME_VAR(int, scene + 0x2148ee0))
		recorder_openStub(scene + 0x2148ed8, scene + 0x2149208, (const void *)IMG(0x4c45e4));
	if (!recorder_setPathStub(scene + 0x2148ed8, path))
		GAME_VAR(int, scene + 0x2149308) = 0;
	const char *name = (const char *)(scene + 0x2149108);
	if (*name) {
		char text[0x100];
		sprintf(text, (const char *)IMG(0x4c8304), name);
		sound_playFile(text, 100);
	}
}

/* 0x4742f0 (thiscall on the stage): player p set from an actor record: its name (+8), value (+4), team (+0x28), the
   parts (head, chest, arm, leg, booster: +0x2c .. +0x3c), the six items (+0x40 ..), then marked in use. Its caller
   ignores the eax it leaves */
void THISCALL (playerRecord_setFromActorRecord)(Stage *stage, int p, const u8 *rec)
{
#define R(offset) GAME_VAR(int, rec + (offset))
	player_setName(stage, p, (const char *)(rec + 8));
	player_setValue(stage, p, R(4));
	player_setTeam(stage, p, R(0x28));
	actor_setActorTypeHeadInfoBy(stage, p, R(0x2c));
	actor_setActorTypeChestInfoBy(stage, p, R(0x30));
	actor_setActorTypeArmInfoBy(stage, p, R(0x34));
	actor_setActorTypeLegInfoBy(stage, p, R(0x38));
	actor_setActorTypeBoosterInfoBy(stage, p, R(0x3c));
	for (int k = 0; k < 6; k++)
		actor_setActorTypeItemInfoBy(stage, p, k, R(0x40 + k * 4));
	player_markUsed(stage, p);
#undef R
}

/* 0x474210 (thiscall on the stage): player p set from its pieces: name, value, team, the five parts, the six items,
   then marked in use (as playerRecord_setFromActorRecord does from a record). Its caller ignores the eax it leaves */
void THISCALL (playerRecord_set)(Stage *stage, int p, const char *name, int v, int team, int head, int chest, int arm, int leg,
                             int booster, int i0, int i1, int i2, int i3, int i4, int i5)
{
	player_setName(stage, p, name);
	player_setValue(stage, p, v);
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
	{ 0x30c, 0x13eb000, IMG(0x4c75f0), 0x338, 0x43534, 0x13c9b30, 0xaa8, 0x4c, FN_ADDR(actor_updateHead, 0x45e1f0) },     /* head */
	{ 0x310, 0x140c8bc, IMG(0x4c7624), 0x8284, 0x43e34, 0x13eb004, 0xabc, 0x8c, FN_ADDR(actor_updateBody, 0x45e2c0) },    /* chest (actor_updateBody) */
	{ 0x314, 0x1447ec0, IMG(0x4c7658), 0x101d0, 0x44734, 0x140c8c0, 0x1300, 0xcc, FN_ADDR(actor_updateArms, 0x45e390) },  /* arms */
	{ 0x318, 0x148646c, IMG(0x4c7688), 0x1fe1c, 0x45804, 0x1447ec4, 0x13f4, 0x10c, FN_ADDR(actor_updateLegs, 0x45e460) }, /* legs */
	{ 0x31c, 0x14d1ab0, IMG(0x4c76b8), 0x2fa68, 0x468d4, 0x1486470, 0x1820, 0x14c, FN_ADDR(actor_updateBooster, 0x45e530) }, /* booster */
};

/* player p's part of kind k set to type (its record at +0x1561b68, 0x47fd2 bytes each): none for a negative type (0);
   the player count (+0x19e1888) grows to cover p; the same type again is 1 at once. A type past the count is a fatal
   message (the game exits); then the player's caches emptied, the type's name copied, the type
   stored, and each of the player's actors reloads the part; 1 */
static int set_part(u8 *scene, int p, int type, const PartKind *k)
{
	if (type < 0)
		return 0;
	u8 *pl = scene + 0x1561b68 + p * 0x47fd2;
	if (p > GAME_VAR(int, scene + 0x19e1888) - 1)
		GAME_VAR(int, scene + 0x19e1888) = p + 1;
	if (GAME_VAR(int, pl + k->field) == type)
		return 1;
	if (type >= GAME_VAR(int, scene + k->count))
		sys_fatalError((char *)IMG(0xae2eb8), (const char *)(uintptr_t)k->message, type);
	ShapeManager_releaseModels(pl + k->shapes);
	SkeletonManager_releaseSkeletons(pl + k->skels);
	strcpy((char *)pl + k->name, (const char *)scene + k->names + type * k->stride);
	GAME_VAR(int, pl + k->field) = type;
	for (int i = 0; i < GAME_VAR(int, scene + 0x202e8c8); i++)
		if (GAME_VAR(int, scene + 0x1cd94b4 + i * 0x8888) == p)
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

/* 0x474060 (thiscall on the stage): player p's item in slot set (its part type record at +0x1561b68, 0x47fd2 bytes
   each: the item at +0x320 + slot x 4, its name at +0x18c + slot x 0x40). Game types 2 .. 11 (+0x20f3ab8) fix the
   first slot (3, 5, 0x24, 0x19, 0x16 by pairs; 10 / 11 the second too, 0x17) and leave the others empty (-1); else
   the item given (negative: empty). An item past the catalogue (+0x1561b64) is a fatal message. Each of the player's
   actors then has the slot updated (actor_updatePart, with its +0x49c). The callers ignore the eax it leaves */
void THISCALL (actor_setActorTypeItemInfoBy)(Stage *stage, int p, int slot, int item)
{
	u8 *scene = (u8 *)stage;
	u8 *type = scene + 0x1561b68 + p * 0x47fd2;
	static const int fixed[5] = { 3, 5, 0x24, 0x19, 0x16 };
	unsigned mode = GAME_VAR(int, scene + 0x20f3ab8) - 2;
	if (mode <= 9)
		item = slot == 0 ? fixed[mode / 2] : mode >= 8 && slot == 1 ? 0x17 : -1;
	if (item >= 0)
		strcpy((char *)RELOC(type) + 0x18c + slot * 0x40, (const char *)scene + 0x14d1ab4 + item * 0x2e18);
	else
		type[0x18c + slot * 0x40] = 0;
	if (item >= GAME_VAR(int, scene + 0x1561b64))
		sys_fatalError((char *)IMG(0xae2eb8), (const char *)IMG(0x4c76f0), item);
	GAME_VAR(int, type + 0x320 + slot * 4) = item;
	for (int i = 0; i < GAME_VAR(int, scene + 0x202e8c8); i++)
		if (GAME_VAR(int, scene + 0x1cd94b4 + i * 0x8888) == p)
			actor_updatePart(scene, i, slot, GAME_VAR(u32, scene + 0x1cd9844 + i * 0x8888));
}
