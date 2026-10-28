/* classes.c: the game's small C++ classes as the compiler built them: constructors (set the vtable, clear the
   members), destructors (the vtable set back, an owned buffer freed), the "deleting" destructors, and the helpers
   that clear a block of members. Most return what the original leaves in eax (usually 0 or the object). */
#include "../game.h"

/* n dwords of an object cleared */
static int clear(void *p, int dwords)
{
	u32 *q = p;
	for (int i = 0; i < dwords; i++)
		q[i] = 0;
	return 0;
}

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* ---- member blocks cleared, each the size of its class ---- */
int THISCALL (FUN_004569a0)(void *self) { return clear(self, 0x8); }       /* TextureManager */
int THISCALL (FUN_00464bb0)(void *self) { return clear(self, 0x13); }      /* Model */
int THISCALL (load_466a20)(void *self) { return clear(self, 0x93); }       /* ShapeManager */
int THISCALL (load_46ae70)(void *self) { return clear(self, 0x4c); }       /* SkeletonManager */
int THISCALL (load_47db50)(void *self) { return clear(self, 0x2b); }
int THISCALL (load_4804a0)(void *self) { return clear(self, 0x14); }
int THISCALL (load_4813a0)(void *self) { return clear(self, 0x3d); }       /* CollisionVolume */
int THISCALL (load_483fc0)(void *self) { return clear(self, 0x245c); }
int THISCALL (load_487480)(void *self) { return clear(self, 0xe); }        /* TimeSync */
int THISCALL (load_480430)(void *self) { return clear(self, 0x4); }

/* 0x483d60: Light's two counters cleared */
int THISCALL (this_set_483d60)(void *self)
{
	FIELD(int, self, 0xb004) = 0;
	FIELD(int, self, 0xb008) = 0;
	return 0;
}

/* 0x48fc30: two counters of the stage's map items cleared */
int THISCALL (load_48fc30)(void *self)
{
	FIELD(int, self, 0x2148ed0) = 0;
	FIELD(int, self, 0x2148ed4) = 0;
	return 0;
}

/* 0x4841d0: a view volume's three draw counters cleared */
void THISCALL (this_set_4841d0)(void *view)
{
	FIELD(int, view, 0x90a4) = 0;
	FIELD(int, view, 0x90a8) = 0;
	FIELD(int, view, 0x90ac) = 0;
}

/* 0x480210: three ints set */
void THISCALL (this_set_480210)(int *p, int a, int b, int c)
{
	p[0] = a;
	p[1] = b;
	p[2] = c;
}

/* 0x4569b0: TextureManager's members cleared, and its count */
int THISCALL (FUN_004569b0)(void *self)
{
	FUN_004569a0(self);
	FIELD(int, self, 0x1c) = 0;
	return 0;
}

/* an object's owned buffer (+8, owned while +0xc is 1) freed */
static void free_owned(void *self)
{
	if (FIELD(int, self, 0xc) == 1) {
		operator_delete(FIELD(void *, self, 8));
		FIELD(void *, self, 8) = NULL;
		FIELD(int, self, 0xc) = 0;
	}
}

/* 0x464bc0, 0x466a30, 0x46ae80, 0x4813b0: the buffer freed, then the members cleared */
int THISCALL (FUN_00464bc0)(void *self) { free_owned(self); FUN_00464bb0(self); return 0; }
int THISCALL (load_466a30)(void *self) { free_owned(self); load_466a20(self); return 0; }
int THISCALL (load_46ae80)(void *self) { free_owned(self); load_46ae70(self); return 0; }
int THISCALL (load_4813b0)(void *self) { free_owned(self); load_4813a0(self); return 0; }

/* ---- getters ---- */
int (arena_4532a0)(void) { return GAME_VAR(int, 0xa0b41c); }
int (gfx_getWidth)(void) { return GAME_VAR(int, 0xa0e810); }
int (gfx_getHeight)(void) { return GAME_VAR(int, 0xa0e928); }
float (FUN_004686d0)(void) { return GAME_VAR(float, 0x4c4dec); }
float (match_4686f0)(void) { return GAME_VAR(float, 0x4c4df0); }
float (FUN_00468700)(void) { return GAME_VAR(float, 0x4c4df4); }

/* ---- setters ---- */
void (set_4dc798_40f200)(void) { g_armcMode = 1; GAME_VAR(int, 0x4dc788) = 0; }   /* the ARM CENTER's parts page */
void (set_4dc798_40f320)(void) { g_armcMode = 3; g_armcColourSlot = 5; }        /* its colour page */
void (set_a61708_46f090)(int v) { GAME_VAR(int, 0xa61708) = v; GAME_VAR(int, 0xa21704) = 0; GAME_VAR(int, 0xaa268c) = 0; }
int (set_680370_441250)(int v) { g_keysBlocked = v; return v; }
int (set_4b42dc_457140)(int v) { GAME_VAR(int, 0x4b42dc) = v; return v; }

/* three-float vectors at 0xa0e7a8 ..: zero or a unit axis (bits of 1.0) */
static void set3(u32 addr, u32 x, u32 y, u32 z)
{
	u32 *p = (u32 *)addr;
	p[0] = x;
	p[1] = y;
	p[2] = z;
}
void (set_a0e7a8_4678f0)(void) { set3(0xa0e7a8, 0, 0, 0); }
void (set_a0e7b8_467890)(void) { set3(0xa0e7b8, 0, 0, 0); }
void (set_a0e7c8_467980)(void) { set3(0xa0e7c8, 0, 0, 0x3f800000u); }
void (set_a0e7d8_467950)(void) { set3(0xa0e7d8, 0, 0x3f800000u, 0); }
void (set_a0e7e8_4678c0)(void) { set3(0xa0e7e8, 0, 0, 0); }
void (set_a0e7f8_467920)(void) { set3(0xa0e7f8, 0x3f800000u, 0, 0); }

/* ---- class lifecycles ---- */

/* the deleting destructor: the plain one, then the object freed when flags & 1 */
#define DELETING(cls, dtor) \
	void *THISCALL (cls##_deletingDtor)(void *self, int flags) { dtor(self); if (flags & 1) operator_delete(self); return self; }

/* Texture (vtable 0x4a956c): 0x455030 (named Texture_ctor, in fact its destructor) frees the pixel buffer (+0x10c,
   held while +0x108 is not negative) and closes its file (+0x110); the result is what the last call left */
u32 THISCALL (Texture_ctor)(u32 *self)
{
	u32 r = self[0x42];
	self[0] = 0x4a956c;
	if ((int)r >= 0) {
		r = GAME_CDECL(0x49ef24, u32, void *)((void *)self[0x43]);   /* operator delete, its eax kept */
		self[0x42] = 0;
	}
	if (self[0x44] != 0)
		r = fclose((void *)self[0x44]);
	return r;
}
DELETING(Texture, Texture_ctor)
/* the six global Texture objects' destructors at exit */
u32 (Texture_ctor_wrap_42b180)(void) { return Texture_ctor((u32 *)0x4e1878); }
u32 (Texture_ctor_wrap_42b1d0)(void) { return Texture_ctor((u32 *)0x5b1db8); }
u32 (Texture_ctor_wrap_42b220)(void) { return Texture_ctor((u32 *)0x680cd8); }
u32 (Texture_ctor_wrap_42b270)(void) { return Texture_ctor((u32 *)0x76d498); }
u32 (Texture_ctor_wrap_42b2c0)(void) { return Texture_ctor((u32 *)0x90d1e0); }
u32 (Texture_ctor_wrap_42b310)(void) { return Texture_ctor((u32 *)0x83a9e0); }

/* TimeSync (vtable 0x4aa46c) */
void *THISCALL (TimeSync_ctor)(u32 *self) { self[0] = 0x4aa46c; load_487480(self); return self; }
void THISCALL (TimeSync_dtor)(u32 *self) { self[0] = 0x4aa46c; }
DELETING(TimeSync, TimeSync_dtor)
void (TimeSync_dtor_wrap_468740)(void) { TimeSync_dtor((u32 *)0xa0e948); }

/* TextureManager (vtable 0x4a9570; the global one at 0x83a5e0) */
int (TextureManager_ctor)(void) { GAME_VAR(u32, 0x83a5e0) = 0x4a9570; return FUN_004569a0((void *)0x83a5e0); }
int THISCALL (TextureManager_dtor)(u32 *self) { self[0] = 0x4a9570; return FUN_004569b0(self); }
DELETING(TextureManager, TextureManager_dtor)
void (TextureManager_dtor_wrap_42b380)(void) { TextureManager_dtor((u32 *)0x83a5e0); }

/* Scene (vtable 0x4aa258) */
void *THISCALL (Scene_ctor)(u32 *self) { self[0] = 0x4aa258; nullsub_48b420(NULL); return self; }
void THISCALL (Scene_dtor)(u32 *self) { self[0] = 0x4aa258; }
DELETING(Scene, Scene_dtor)

/* Light (vtable 0x4aa248) */
void *THISCALL (Light_ctor)(u32 *self) { self[0] = 0x4aa248; this_set_483d60(self); return self; }
int THISCALL (Light_dtor)(u32 *self) { self[0] = 0x4aa248; return this_set_483d60(self); }
DELETING(Light, Light_dtor)

/* CollisionVolume (vtable 0x4aa254) */
void *THISCALL (CollisionVolume_ctor)(u32 *self) { self[0] = 0x4aa254; load_4813a0(self); return self; }
int THISCALL (CollisionVolume_dtor)(u32 *self) { self[0] = 0x4aa254; return load_4813b0(self); }
DELETING(CollisionVolume, CollisionVolume_dtor)

/* Model (vtable 0x4aa250) */
void *THISCALL (Model_ctor)(u32 *self) { self[0] = 0x4aa250; FUN_00464bb0(self); return self; }
int THISCALL (Model_dtor)(u32 *self) { self[0] = 0x4aa250; return FUN_00464bc0(self); }
DELETING(Model, Model_dtor)

/* ShapeManager (vtable 0x4aa244), SkeletonManager (vtable 0x4aa240) */
int THISCALL (ShapeManager_dtor)(u32 *self) { self[0] = 0x4aa244; return load_466a30(self); }
DELETING(ShapeManager, ShapeManager_dtor)
int THISCALL (SkeletonManager_dtor)(u32 *self) { self[0] = 0x4aa240; return load_46ae80(self); }
DELETING(SkeletonManager, SkeletonManager_dtor)

/* BMPRGBFile (vtable 0x4a96f8): 0x46ce60 (named BMPRGBFile_ctor, in fact its destructor) closes its file */
void THISCALL (BMPRGBFile_ctor)(u32 *self) { self[0] = 0x4a96f8; if (self[1]) fclose((void *)self[1]); }
DELETING(BMPRGBFile, BMPRGBFile_ctor)

/* ErrorLog (vtable 0x4aa2a0): the class-name records */
void THISCALL (ErrorLog_dtor)(u32 *self) { self[0] = 0x4aa2a0; }
DELETING(ErrorLog, ErrorLog_dtor)
void (ErrorLog_dtor_wrap_456cc0)(void) { ErrorLog_dtor((u32 *)0xa0e020); }
void *THISCALL (ErrorLog_ctor)(u32 *self, const char *name, int b)
{
	self[0] = 0x4aa2a0;
	self[1] = (u32)name;
	GAME_VAR(int, 0xa1efe8) = b;
	return self;
}

/* 0x463850: a resource set: five shape managers (vtable 0x4aa244) and five skeleton managers (0x4aa240) built in
   place (the original's exception frame only matters if a constructor throws, and these cannot) */
void *THISCALL (ResourceSet_ctor_463850)(u8 *self)
{
	static const u32 shapes[5] = { 0x338, 0x8284, 0x101d0, 0x1fe1c, 0x2fa68 };
	static const u32 skels[5] = { 0x43534, 0x43e34, 0x44734, 0x45804, 0x468d4 };
	for (int i = 0; i < 5; i++) {
		*(u32 *)(self + shapes[i]) = 0x4aa244;
		load_466a20(self + shapes[i]);
	}
	for (int i = 0; i < 5; i++) {
		*(u32 *)(self + skels[i]) = 0x4aa240;
		load_46ae70(self + skels[i]);
	}
	return self;
}
