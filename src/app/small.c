/* small.c: one-line pieces from all over the game that need nothing of their own: clears, flags, getters and
   setters, list toggles, string lengths. Grouped by where they are used. */
#include "../game.h"

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
