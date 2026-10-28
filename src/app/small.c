/* small.c: one-line pieces from all over the game that need nothing of their own: clears, flags, getters and
   setters, list toggles, string lengths. Grouped by where they are used. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

static void clear(void *p, int dwords)
{
	u32 *q = p;
	for (int i = 0; i < dwords; i++)
		q[i] = 0;
}

/* ---- empty methods (their arguments unused) and trivial returns ---- */
void *THISCALL (match_45fff0)(void *self) { return self; }
int THISCALL (match_48b440)(void *self, int a) { (void)self; (void)a; return 0; }
void THISCALL (match_48b430)(void *self, int a0, int a1) { (void)self; (void)a0; (void)a1; }
void THISCALL (hud_48b450)(void *self, int a0, int a1, int a2, int a3) { (void)self; (void)a0; (void)a1; (void)a2; (void)a3; }
/* 0x43f770: the start mode from the registry - always 1 in this build */
u32 (reg_readStartMode)(void) { return 1; }

/* ---- setters of single globals (they return the value) ---- */
int (skirmish_4017b0)(int v) { GAME_VAR(int, 0x4ad490) = v; return v; }
int (skirmish_4017c0)(int v) { GAME_VAR(int, 0x4ad494) = v; return v; }
int (match_4686e0)(int v) { GAME_VAR(int, 0x4c4dec) = v; return v; }

/* ---- index <-> pointer in an array of records ---- */
/* 0x46cbc0: record i (base + i * stride), 0 for a negative index */
int (FUN_0046cbc0)(int i, int base, int stride) { return i < 0 ? 0 : i * stride + base; }
/* 0x46cba0: the index of record p, -1 for none */
int (FUN_0046cba0)(int p, int base, int stride) { return p == 0 ? -1 : (p - base) / stride; }

/* ---- strings ---- */
/* 0x44ac50: the length of s */
int (cfg_44ac50)(const char *s)
{
	int n = 0;
	while (*s++)
		n++;
	return n;
}
/* 0x44ac70: s without its last character (its old length) */
int (cfg_44ac70)(char *s)
{
	int n = cfg_44ac50(s);
	s[n - 1] = '\0';
	return n;
}

/* ---- the scene's and stage's flags and lists ---- */
/* 0x463670, 0x463690, 0x4636b0: one of three requests raised (and the "something requested" flag) */
void THISCALL (match_463670)(Scene *scene) { FIELD(int, scene, 0x2343237) = 1; FIELD(int, scene, 0x2343106) = 1; }
void THISCALL (match_463690)(Scene *scene) { FIELD(int, scene, 0x234323b) = 1; FIELD(int, scene, 0x2343106) = 1; }
void THISCALL (match_4636b0)(Scene *scene) { FIELD(int, scene, 0x234323f) = 1; FIELD(int, scene, 0x2343106) = 1; }
/* 0x463780: team slot i's id */
int THISCALL (this_get_0x2342381_463780)(Scene *scene, int i) { return scene->teamIds[i]; }
/* 0x474390: player record p marked used; 0x4743b0: marked free, its colour grid cleared */
void THISCALL (FUN_00474390)(Stage *stage, int p) { FIELD(int, stage, 0x1561b68 + p * 0x47fd2) = 1; }
void THISCALL (net_4743b0)(Stage *stage, int p)
{
	FIELD(int, stage, 0x1561b68 + p * 0x47fd2) = 0;
	FUN_00473470(stage, p);
}
/* 0x45df90: the stage's 100 actor references cleared */
void THISCALL (FUN_0045df90)(Stage *stage) { clear((u8 *)stage + 0x202e8f0, 100); }
/* 0x45e1c0: every actor in use switched off */
void THISCALL (match_45e1c0)(Stage *stage)
{
	for (int i = 0; i < stage->actorCount; i++)
		actor_deactivate(stage, i);
}
/* 0x4723e0: the stage's lights reset */
int THISCALL (load_4723e0)(Stage *stage)
{
	FIELD(int, stage, 0x9d800c) = 0;
	return this_set_483d60((u8 *)stage + 0x9d8010);
}

/* ---- small objects ---- */
/* 0x480440: an empty slot: -1 and four zeros */
void THISCALL (load_480440)(int *self) { self[1] = self[2] = self[3] = self[4] = 0; self[0] = -1; }
/* 0x469980, 0x46f480: members cleared (0x46f480 keeps the sixth) */
void THISCALL (FUN_00469980)(int *self) { for (int i = 1; i <= 7; i++) self[i] = 0; }
void THISCALL (FUN_0046f480)(int *self) { for (int i = 1; i <= 11; i++) if (i != 6) self[i] = 0; }
/* 0x4699a0, 0x46f4b0: the owned buffer (+8 while +0xc is 1) freed, then the members cleared */
static void free_owned(void *self)
{
	if (FIELD(int, self, 0xc) == 1) {
		operator_delete(FIELD(void *, self, 8));
		FIELD(void *, self, 8) = NULL;
		FIELD(int, self, 0xc) = 0;
	}
}
int THISCALL (FUN_004699a0)(void *self) { free_owned(self); FUN_00469980(self); return 0; }
int THISCALL (FUN_0046f4b0)(void *self) { free_owned(self); FUN_0046f480(self); return 0; }
/* 0x46f470: UnitPoseInfo's destructor (vtable 0x4a9754) */
int THISCALL (match_46f470)(u32 *self) { self[0] = 0x4a9754; return FUN_0046f4b0(self); }
/* 0x46ce50: the object's file closed (fclose's result, 0 for none) */
u32 THISCALL (FUN_0046ce50)(u32 *self) { return self[1] ? fclose((void *)self[1]) : 0; }
/* 0x467d60: p freed (operator delete's eax; 0 for none) */
u32 (FUN_00467d60)(void *p) { return p ? GAME_CDECL(0x49ef24, u32, void *)(p) : 0; }

/* ---- network tables cleared ---- */
void (net_452e60)(void) { clear((void *)0xa05748, 0x16c0); }
void (net_452e80)(void) { clear((void *)0x9fd960, 0x1e40); }
void (net_452ea0)(void) { clear((void *)0xa05330, 0x9b); }
/* 0x430bd0: the 16 entries of 0x410 bytes from 0x9f9840 marked empty */
void (intro_430bd0)(void) { for (u32 p = 0x9f9840; p < 0x9fd940; p += 0x410) GAME_VAR(int, p) = 0; }

/* ---- front end ---- */
/* 0x453a30: 1 if connection kind i (0 .. 3) is available */
int (arena_453a30)(u32 i) { return i < 4 && GAME_VAR(int, 0xa0bae0 + i * 4) ? 1 : 0; }
/* 0x4417c0: map i of the map-select dialog in or out; 0x4417f0: all in (0x44-byte entries from 0x9ddac8) */
void (mainmenu_4417c0)(int i) { int *f = (int *)(0x9ddac8 + i * 0x44); *f = 1 - *f; }
void (mainmenu_4417f0)(void) { for (int i = 0; i < GAME_VAR(int, 0x9dd928); i++) GAME_VAR(int, 0x9ddac8 + i * 0x44) = 1; }
/* 0x447af0: a click closes the mission briefing */
void (mission_447af0)(void) { if (g_dialogOpen == 0 && g_mouseClick != 0) GAME_VAR(int, 0x9f62e0) = 0; }
/* 0x4411e0: the background tunnel's rings made again (FUN_00441120) */
u32 (intro_4411e0)(void) { GAME_VAR(int, 0x9dae10) = 0; return FUN_00441120((void *)0x67fb3c); }
/* 0x44ad30: the text colour */
void (text_setColor)(u32 r, u32 g, u32 b, u32 a) { set_colour_bits((Colour *)0x76d438, r, g, b, a); }
/* 0x404120, 0x431db0, 0x44b080: a dialog's box rectangle */
void (arena_404120)(void) { set4ints(0x104, 0x118, 0x17c, 0x138, (int *)0x4dbad0); }
void (room_431db0)(void) { set4ints(0x104, 0x118, 0x17c, 0x138, (int *)0x9dd308); }
void (profile_44b080)(void) { set4ints(0x1d7, 0xf6, 0x226, 0x114, (int *)0x9f9010); }
/* 0x45dfb0: actor i selected when it is in use (any negative i: none selected) */
void THISCALL (FUN_0045dfb0)(Stage *stage, int i)
{
	if (i < 0 || FIELD(int, stage, 0x1cd94f4 + i * 0x8888) == 1)
		FIELD(int, stage, 0x202e8d8) = i;
}
/* 0x456820: material m (0x68-byte records at +0xc016c) marked changed, its flags kept to the bits 0x11111113 (the
   original's guard, flags | 2, is always true) */
void THISCALL (FUN_00456820)(void *self, int m)
{
	u8 *r = (u8 *)self + m * 0x68;
	u32 f = FIELD(u32, r, 0xc016c);
	if ((f | 2) != 0) {
		FIELD(u32, r, 0xc016c) = f & 0x11111113;
		FIELD(int, r, 0xc018c) = 1;
	}
}
/* 0x456b50: three fields cleared in each of the six objects the object points to (+4 .. +0x18) */
void THISCALL (hud_456b50)(void *self)
{
	for (int k = 1; k <= 6; k++) {
		u8 *o = FIELD(u8 *, self, k * 4);
		FIELD(int, o, 0xcd138) = 0;
		FIELD(int, o, 0xcd13c) = 0;
		FIELD(int, o, 0xcd140) = 0;
	}
}
/* 0x473470: player record p's 16 x 24 colour grid filled with the colour at 0xa1f220, its three counters reset */
void THISCALL (FUN_00473470)(Stage *stage, int p)
{
	u8 *rec = (u8 *)stage + 0x1561b68 + p * 0x47fd2;
	int colour = GAME_VAR(int, 0xa1f220);
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
	nullsub_48b420((Scene *)stage);   /* an empty method of the stage */
	for (int i = 0; i < 6; i++)
		FIELD(int, stage, 0x2149308 + i * 4) = 0;
	return 0;
}
/* 0x473a10: player record p's value +0x44 set, and that of every actor of player p (+0x114) */
void THISCALL (FUN_00473a10)(Stage *stage, int p, int v)
{
	u32 *seen = &FIELD(u32, stage, 0x19e1888);   /* players seen so far (the highest + 1) */
	if (p > (int)(*seen - 1))
		*seen = p + 1;
	FIELD(int, stage, 0x1561b68 + p * 0x47fd2 + 0x44) = v;
	for (int i = 0; i < stage->actorCount; i++)
		if (FIELD(int, &stage->actors[i], 0x10c) == p)
			FIELD(int, &stage->actors[i], 0x114) = v;
}
/* 0x48fe10: the stage's identity matrix, 200 points at the origin (0xa0e7a8), the colour at 0xa1f220 */
void THISCALL (load_48fe10)(Stage *stage)
{
	for (int k = 0; k < 16; k++)
		FIELD(u32, stage, 0x20f2fc8 + k * 4) = k % 5 ? 0 : 0x3f800000;
	for (int k = 0; k < 200; k++)
		for (int j = 0; j < 3; j++)
			FIELD(int, stage, 0x20f300c + k * 12 + j * 4) = GAME_VAR(int, 0xa0e7a8 + j * 4);
	FIELD(int, stage, 0x20f3008) = 0;
	FIELD(int, stage, 0x20f396c) = GAME_VAR(int, 0xa1f220);
}

/* ---- matrices (16 dwords) ---- */
/* 0x47d5a0: copied (column by column) */
void (FUN_0047d5a0)(u32 *d, const u32 *s)
{
	for (int c = 0; c < 4; c++)
		for (int r = 0; r < 4; r++)
			d[r * 4 + c] = s[r * 4 + c];
}
/* 0x47d830: copied transposed */
void (skel_47d830)(u32 *d, const u32 *s)
{
	for (int k = 0; k < 16; k++)
		d[(k & 3) * 4 + (k >> 2)] = s[k];
}

/* ---- objects put to their start ---- */
/* 0x463a40: a resource set's eight lists, each a UnitPoseInfo (vtable 0x4a9754) with its members cleared */
void *THISCALL (ResourceSet_init_463a40)(u8 *self)
{
	static const int lists[8] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };
	for (int k = 0; k < 8; k++) {
		FIELD(u32, self, lists[k]) = 0x4a9754;
		FUN_0046f480(self + lists[k]);
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
/* 0x481760: the collision space's units: count at +0x30, the 0x14-byte units at +0x34, each emptied (load_480440) and
   chained (prev at +0xc, next at +0x10) */
void THISCALL (space_resetUnits)(u8 *self)
{
	for (int i = 0; i < FIELD(int, self, 0x30); i++)
		load_480440((int *)(FIELD(u8 *, self, 0x34) + i * 0x14));
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
void (armc_40d990)(void) {}

/* ---- more small methods ---- */
void THISCALL (nullsub_483ce0)(void *self, int a) { (void)self; (void)a; }
/* 0x45dfe0: the stage's +0x202e8dc set (returned) */
int THISCALL (armc_45dfe0)(Stage *stage, int v) { FIELD(int, stage, 0x202e8dc) = v; return v; }
/* 0x468720: the time sync object at 0xa0e948 constructed */
void *(load_487430_wrap_468720)(void) { return TimeSync_ctor((void *)0xa0e948); }
/* 0x470f80: an object's texture folder (+0x908) set, upper-cased with back slashes (returned) */
char *THISCALL (FUN_00470f80)(void *self, const char *folder)
{
	strcpy((char *)self + 0x908, folder);
	return FUN_0046cb60((char *)self + 0x908);
}
/* 0x461ec0: the scene's texture folder (+0x1f35c8) and its stage's */
void THISCALL (FUN_00461ec0)(Scene *scene, const char *folder)
{
	strcpy((char *)scene + 0x1f35c8, folder);
	FUN_00470f80(STAGE(scene), folder);
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
void THISCALL (actor_46f770)(u8 *anim, int i, float scale)
{
	if (!FIELD(int, anim, 0x20) || i >= FIELD(int, anim, 0x1c))
		return;
	FIELD(int, anim, 0x24) = i;
	const int *frame = FIELD(int **, anim, 0x20)[i];
	FIELD(int, anim, 0x28) = ftol(fmul_m((long double)frame[8], &scale));
}

/* 0x4722e0: a view's distance set (+0xa08, the float's bits copied) and its depth -v * a + b from the stage's pair */
void THISCALL (match_4722e0)(u8 *view, float v)
{
	BITS(FIELD(float, view, 0xa08)) = BITS(v);
	volatile long double n = -(long double)v;   /* negated first, as the original's fchs */
	FIELD(float, view, 0xa0c) = (float)(n * FIELD(float, view, 0x20f3a9c) + FIELD(float, view, 0x20f3aac));
}
