/* classes.c: the game's small C++ classes as the compiler built them: constructors (set the vtable, clear the
   members), destructors (the vtable set back, an owned buffer freed), the "deleting" destructors, and the helpers
   that clear a block of members. Most return what the original leaves in eax (usually 0 or the object). */
#include "../game.h"
#include <string.h>

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

/* ---- arrays of members released ---- */
/* the array at +0x11c (count +0x120) of stride-byte entries, each released, the count 0; +0x12c set to 0 if it
   was positive; returns its old value */
typedef int (THISCALL *Release)(void *entry);
static int release_all(u8 *self, int stride, Release release)
{
	if (*(int *)(self + 0x120) > 0) {
		for (int i = 0; i < *(int *)(self + 0x120); i++)
			release(*(u8 **)(self + 0x11c) + i * stride);
		*(int *)(self + 0x120) = 0;
	}
	int r = *(int *)(self + 0x12c);
	if (r > 0)
		*(int *)(self + 0x12c) = 0;
	return r;
}
static int THISCALL release_model(void *e) { return FUN_00464bc0(e); }
static int THISCALL release_skeleton(void *e) { return FUN_004699a0(e); }
/* 0x467520: a shape manager's models (0x4c bytes) */
int THISCALL (FUN_00467520)(u8 *self) { return release_all(self, 0x4c, release_model); }
/* 0x46b7f0: a skeleton manager's skeletons (0x24 bytes) */
int THISCALL (FUN_0046b7f0)(u8 *self) { return release_all(self, 0x24, release_skeleton); }

/* 0x45ff30: an object's eight member lists destroyed (match_46f470, the last member first: +0x701c .. +0x554).
   Returns the last call's eax */
u32 THISCALL (FUN_0045ff30)(u8 *self)
{
	static const u32 members[8] = { 0x701c, 0x587c, 0x40dc, 0x34f4, 0x2524, 0x1554, 0xd54, 0x554 };
	u32 r = 0;
	for (int k = 0; k < 8; k++)
		r = GAME_THISCALL(0x46f470, u32, void *)(self + members[k]);
	return r;
}

/* 0x463960: a resource set destroyed: its five skeleton managers, then its five shape managers, the last member first
   (as ResourceSet_ctor_463850 built them). Returns the last destructor's eax */
u32 THISCALL (ResourceSet_dtor_463960)(u8 *self)
{
	static const u32 skeletons[5] = { 0x468d4, 0x45804, 0x44734, 0x43e34, 0x43534 };
	static const u32 shapes[5] = { 0x2fa68, 0x1fe1c, 0x101d0, 0x8284, 0x338 };
	u32 r = 0;
	for (int k = 0; k < 5; k++)
		GAME_THISCALL(0x46ae60, u32, void *)(self + skeletons[k]);   /* SkeletonManager_dtor */
	for (int k = 0; k < 5; k++)
		r = GAME_THISCALL(0x466a10, u32, void *)(self + shapes[k]);  /* ShapeManager_dtor */
	return r;
}

#define eh_vector_destructor(array, size, count, dtor) \
	((void (STDCALL *)(void *, u32, int, u32))0x49fc4f)(array, size, count, dtor)   /* `eh vector destructor iterator' (stdcall) */

/* 0x46ff70: the stage destroyed, its members last first: 0x48b410 (+0x2148ed8), the 100 actors (+0x1cd93a8,
   0x8888 bytes each, 0x45ff30), the skeleton and shape managers, the 16 resource sets (+0x1561b68, 0x47fd2 bytes
   each, ResourceSet_dtor_463960), two more managers, two 0x464ba0 tables, the three factor pools and +0xa10.
   Returns the last destructor's eax */
u32 THISCALL (Stage_dtor)(u8 *self)
{
	*(u32 *)self = 0x4aa23c;   /* the vtable */
	GAME_THISCALL(0x48b410, void, void *)(self + 0x2148ed8);
	eh_vector_destructor(self + 0x1cd93a8, 0x8888, 100, 0x45ff30);
	GAME_THISCALL(0x46ae60, void, void *)(self + 0x1cbe198);   /* SkeletonManager_dtor */
	GAME_THISCALL(0x466a10, void, void *)(self + 0x19e188c);   /* ShapeManager_dtor */
	eh_vector_destructor(self + 0x1561b68, 0x47fd2, 16, 0x463960);
	GAME_THISCALL(0x46ae60, void, void *)(self + 0x13016d0);
	GAME_THISCALL(0x466a10, void, void *)(self + 0xe3c93c);
	GAME_THISCALL(0x464ba0, void, void *)(self + 0xdc0cc4);
	GAME_THISCALL(0x464ba0, void, void *)(self + 0xdc0a78);
	GAME_THISCALL(0x483d50, void, void *)(self + 0x9e3020);
	GAME_THISCALL(0x483d50, void, void *)(self + 0x9d8010);
	GAME_THISCALL(0x483d50, void, void *)(self + 0x9ccffc);
	return GAME_THISCALL(0x481390, u32, void *)(self + 0xa10);
}

/* 0x46cd00 (thiscall on an image): a 24-bit BMP opened (the last one closed first): its file header (14 bytes, +8)
   and info header (0x28 bytes, +0x16) read, each missing a fatal message, and anything but 24 bits uncompressed one
   too; its width and height kept (+0x3e, +0x42). Returns the file, or 0 when it can't be opened */
void *THISCALL (image_initBy)(u8 *image, const char *path)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define fatal(text) GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa1f0f0, (const char *)(text))
	if (GAME_VAR(void *, image + 4))
		fclose(GAME_VAR(void *, image + 4));
	void *f = GAME_VAR(void *, image + 4) = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		return 0;
	if (crt_fread(image + 8, 0xe, 1, f) < 1)
		fatal(0x4c5948);
	if (crt_fread(image + 0x16, 0x28, 1, GAME_VAR(void *, image + 4)) < 1)
		fatal(0x4c592c);
	if (GAME_VAR(u16, image + 0x24) != 24 || GAME_VAR(u32, image + 0x26) != 0)
		fatal(0x4c5908);
	GAME_VAR(u32, image + 0x3e) = GAME_VAR(u32, image + 0x1a);
	GAME_VAR(u32, image + 0x42) = GAME_VAR(u32, image + 0x1e);
	return GAME_VAR(void *, image + 4);
#undef crt_fread
#undef fatal
}

/* 0x4734d0 (named gfx_saveScreenshot; by use a part type's emblem loaded): the BMP named after type p (its record at
   +0x1561b68, 0x47fd2 bytes each; the name from +4 by 0x4c74e8) read into a local image; at least 23 x 15 of it: its
   24 x 16 corner copied as RGBA into the record (+0x479c2), black pixels made clear and the rest opaque, and 1
   returned; else 0 */
int THISCALL (gfx_saveScreenshot)(u8 *scene, int p)
{
	u8 *type = scene + 0x1561b68 + p * 0x47fd2;
	u8 image[0x48];
	GAME_VAR(u32, image) = 0x4a96f8;   /* (its vtable) */
	GAME_VAR(u32, image + 4) = 0;      /* (no file yet) */
	char path[0x100];
	sprintf(path, (const char *)0x4c74e8, type + 4);
	int ok = 0;
	if (match_46cdc0(image, path)) {
		if (GAME_VAR(int, image + 0x3e) >= 23 && GAME_VAR(int, image + 0x42) >= 15) {
			u8 *pixel = type + 0x479c2;
			image_copyTo(image, pixel, 24, 16, 4, 0, 0, 0, 0, 24, 16, 0);
			for (int k = 0; k < 24 * 16; k++, pixel += 4)
				pixel[3] = pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0 ? 0 : 0xff;
			ok = 1;
		}
		FUN_0046ce50(image);
	}
	BMPRGBFile_ctor(image);   /* (by use its destructor) */
	return ok;
}

/* 0x473610 (thiscall on the scene): the sixteen part types' emblems (24 x 16 RGBA each, +0x479c2 in a type's record)
   that changed (+0x608 1) copied into the emblem atlas (+0x20fcfe4, 128 x 64, four to a row) and marked done; when one
   of them was new (+0x604 0, now 1) the atlas is uploaded to its GL texture (+0x20fcfe0). Its callers ignore the eax
   it leaves */
void THISCALL (tex_upload2)(u8 *scene)
{
	int uploaded = 0;
	for (int p = 0; p < 16; p++) {
		u8 *emblem = scene + 0x1561b68 + p * 0x47fd2 + 0x479c2;
		if (GAME_VAR(int, emblem + 0x608) != 1)
			continue;
		u32 *atlas = (u32 *)(scene + 0x20fcfe4) + (p / 4) * 16 * 128 + (p % 4) * 24;
		const u32 *pixel = (const u32 *)emblem;
		for (int y = 0; y < 16; y++, atlas += 128)
			for (int x = 0; x < 24; x++)
				atlas[x] = *pixel++;
		GAME_VAR(int, emblem + 0x608) = 0;
		if (!GAME_VAR(int, emblem + 0x604)) {
			GAME_VAR(int, emblem + 0x604) = 1;
			uploaded = 1;
		}
	}
	if (uploaded != 1)
		return;
	glPixelStorei(0xcf5, 1);   /* GL_UNPACK_ALIGNMENT */
	glBindTexture(0xde1, GAME_VAR(u32, scene + 0x20fcfe0));
	glTexParameterf_bits(0xde1, 0x2802, 0x46240000);   /* wrap S: GL_CLAMP */
	glTexParameterf_bits(0xde1, 0x2803, 0x46240000);   /* wrap T */
	glTexParameterf_bits(0xde1, 0x2800, 0x46180400);   /* mag filter: GL_LINEAR */
	glTexParameterf_bits(0xde1, 0x2801, 0x46180400);   /* min filter */
	glTexImage2D(0xde1, 0, 4, 0x80, 0x40, 0, 0x1908, 0x1401, scene + 0x20fcfe4);   /* RGBA, unsigned bytes */
}

/* 0x46ce80 (thiscall on an image): a w x h block of the open 24-bit BMP (its file +4, pixel data at +0x12, size +0x3e
   x +0x42, rows stored bottom-up) from (sx, sy) copied into the dw x dh buffer dst at (dx, dy), both clipped (nothing
   left: nothing; wider than 0x400 a fatal message): BGR to RGB (depth 3) or RGBA with alpha 0xff (depth 4; another
   depth a fatal message per row), the rows placed top-down when topDown, else bottom-up. Its callers ignore the eax
   it leaves */
void THISCALL (image_copyTo)(u8 *image, u8 *dst, int dw, int dh, int depth, int sx, int sy, int dx, int dy, int w, int h,
                             int topDown)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	void *f = GAME_VAR(void *, image + 4);
	int iw = GAME_VAR(int, image + 0x3e), ih = GAME_VAR(int, image + 0x42);
	if (sx < 0) {
		dx -= sx;
		w += sx;
		sx = 0;
	}
	if (sy < 0) {
		dy -= sy;
		h += sy;
		sy = 0;
	}
	if (sx >= iw || sy >= ih)
		return;
	if (sx + w > iw)
		w = iw - sx;
	if (sy + h > ih)
		h = ih - sy;
	if (dx < 0) {
		sx -= dx;
		w += dx;
		dx = 0;
	}
	if (dy < 0) {
		sy -= dy;
		h += dy;
		dy = 0;
	}
	if (dx >= dw || dy >= dh)
		return;
	if (dx + w > dw)
		w = dw - dx;
	if (h + dy > dh)
		h = dh - dy;
	if (w <= 0 || h <= 0)
		return;
	if (w > 0x400)
		GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa1f0f0, (const char *)0x4c5984);
	crt_fseek(f, GAME_VAR(int, image + 0x12) + ((GAME_VAR(int, image + 0x42) - sy - h) * GAME_VAR(int, image + 0x3e) + sx) * 3, 0);
	u8 row[0xc00];
	int first = topDown ? dy : h - 1 + dy, step = topDown ? dw : -dw;
	u8 *p3 = dst + (first * dw + dx) * 3, *p4 = dst + (first * dw + dx) * 4;
	for (int r = 0; r < h; r++) {
		crt_fread(row, w * 3, 1, f);
		if (depth == 3)
			for (int k = 0; k < w; k++) {
				p3[k * 3] = row[k * 3 + 2];
				p3[k * 3 + 1] = row[k * 3 + 1];
				p3[k * 3 + 2] = row[k * 3];
			}
		else if (depth == 4)
			for (int k = 0; k < w; k++) {
				p4[k * 4] = row[k * 3 + 2];
				p4[k * 4 + 1] = row[k * 3 + 1];
				p4[k * 4 + 2] = row[k * 3];
				p4[k * 4 + 3] = 0xff;
			}
		else
			GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa1f0f0, (const char *)0x4c5964);
		crt_fseek(f, (GAME_VAR(int, image + 0x3e) - w) * 3, 1);
		p3 += step * 3;
		p4 += step * 4;
	}
#undef crt_fread
}

/* the scene's camera presets (+0x233ca30: six tables of ten, as float bits or ints) */
static const u32 k_cameraPresets[6][10] = {
	{ 0, 0, 0, 0, 0, 0, 0x42480000, 0, 0, 0 },
	{ 0, 0, 0, 0, 0x44610000, 0xc4610000, 0x43960000, 0xc2c80000, 0x44e10000, 0 },
	{ 0x44e10000, 0x41200000, 0x43960000, 0x453b8000, 0x44e10000, 0x44e10000, 0x44e10000, 0x453b8000, 0x44e10000, 0x44e10000 },
	{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 1, 1, 0, 0, 1, 1 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 } };

/* 0x460570 (thiscall: the game object's constructor): its clock (TimeSync_ctor at +0xc), view volume (+0x74) and the
   stage (+0x1f36c8) with all its member arrays built (the CRT's vector constructors 0x401290 / 0x49fd2d with their
   element constructors) and vtables set; the factor tables sized (factor_initBy into the block at +0x91e4); the
   parts (item_initTextures with nine names), the component catalogue and the items loaded (failing: a fatal
   message); the ten camera presets, the stage's player slots reset (FUN_0045dfb0 -1), the geometry check sizes; the
   30 chat macros (63 characters each, 0x40 apart from +0x234334b) read from their file, each with its line end cut
   (an empty one cuts the byte before it), and saved back (chat_saveMacros). (The original's SEH frame, for
   unwinding a failed construction, is not reproduced.) Returns the object */
u8 *THISCALL (game_loadAllData)(u8 *g)
{
#define CALL(addr, at) GAME_THISCALL(addr, void, void *)(at)
#define VECTOR(at, size, count) ((void (STDCALL *)(void *, int, int, u32))0x401290)(at, size, count, 0x45fff0)   /* (the CRT's iterators are stdcall) */
#define VTABLE(at, vt) (GAME_VAR(u32, at) = (vt))
	u8 *s = g + 0x1f36c8;
	CALL(0x487430, g + 0xc);   /* TimeSync_ctor */
	VTABLE(g + 0x74, 0x4aa24c);
	CALL(0x483fc0, g + 0x74);
	CALL(0x463790, s + 0xa10);   /* CollisionVolume_ctor */
	VECTOR(s + 0x9cd000, 0x2c, 0x400);
	VTABLE(s + 0x9ccffc, 0x4aa248);
	CALL(0x483d60, s + 0x9ccffc);
	VECTOR(s + 0x9d8014, 0x2c, 0x400);
	VTABLE(s + 0x9d8010, 0x4aa248);
	CALL(0x483d60, s + 0x9d8010);
	CALL(0x462560, s + 0x9e3020);   /* Light_ctor */
	VECTOR(s + 0x9ee080, 0xc, 0x126);
	VECTOR(s + 0x9eee54, 0xc, 0x31);
	VECTOR(s + 0x9ef0cc, 0xc, 0x30);
	VECTOR(s + 0x9ef350, 0xc, 0x79);
	VECTOR(s + 0xdc0244, 0x20c, 4);
	CALL(0x462cf0, s + 0xdc0a78);   /* Model_ctor */
	CALL(0x462cf0, s + 0xdc0cc4);
	VECTOR(s + 0xe36214, 0x14, 0x3e8);
	VTABLE(s + 0xe3c93c, 0x4aa244);
	CALL(0x466a20, s + 0xe3c93c);
	VECTOR(s + 0xf30dc8, 4, 1000000);
	VTABLE(s + 0x13016d0, 0x4aa240);
	CALL(0x46ae70, s + 0x13016d0);
	VECTOR(s + 0x131ae44, 0x2cc, 0x3e8);
	VECTOR(s + 0x14d1ab4, 0x2e18, 0x32);
	((void (STDCALL *)(void *, int, int, u32, u32))0x49fd2d)(s + 0x1561b68, 0x47fd2, 0x10, 0x463850, 0x463960);
	VTABLE(s + 0x19e188c, 0x4aa244);
	CALL(0x466a20, s + 0x19e188c);
	VTABLE(s + 0x1cbe198, 0x4aa240);
	CALL(0x46ae70, s + 0x1cbe198);
	VECTOR(s + 0x1cd6fb4, 0x5c, 0x64);
	((void (STDCALL *)(void *, int, int, u32, u32))0x49fd2d)(s + 0x1cd93a8, 0x8888, 0x64, 0x463a40, 0x45ff30);
	VECTOR(s + 0x202ef34, 0x4e8, 0x190);
	VECTOR(s + 0x20a99c0, 0x12c, 0x3e8);
	VECTOR(s + 0x20f300c, 0xc, 0xc8);
	VECTOR(s + 0x20fab74, 0x14, 0x20);
	VECTOR(s + 0x20fadf8, 0x28, 0xc8);
	VECTOR(s + 0x20fcfe4, 4, 0x2000);
	CALL(0x4637f0, s + 0x2148ed8);   /* Scene_ctor */
	VTABLE(s, 0x4aa23c);
	GAME_VAR(int, s + 4) = 0;
	VTABLE(g, 0x4aa238);
	GAME_VAR(int, g + 4) = GAME_VAR(int, g + 8) = -1;
	CALL(0x487480, g + 0xc);
	for (int k = 0; k < 10; k++)
		GAME_VAR(u32, g + 0x48 + k * 4) = 0x3d088889;
	GAME_VAR(int, g + 0x70) = 0;
	GAME_THISCALL(0x484050, void, void *, int, int, int, int, int, int, void *, int)(g + 0x74, 10000, 1000, 20000, 4000, 400, 10000,
	                                                                                g + 0x91e4, 2000000);   /* factor_initBy */
	GAME_THISCALL(0x4700a0, void, void *, u32, u32, u32, u32, u32, u32, u32, u32, u32)(s, 0x4c45a8, 0x4b1784, 0x4c45b0, 0x4c45b8,
	                                                                                  0x4c45c0, 0x4c45cc, 0x4c45d4, 0x4c45dc, 0x4c45e4);   /* item_initTextures */
	if (!GAME_THISCALL(0x473780, int, void *, const char *)(s, (const char *)0x4b4418))   /* catalogue_loadComponents */
		GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa0e778, (const char *)0x4c4598);
	if (!GAME_THISCALL(0x4875d0, int, void *, const char *)(s, (const char *)0x4c4588))   /* map_loadItemInfoFrom */
		GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa0e778, (const char *)0x4c4598);
	memcpy(g + 0x233ca30, k_cameraPresets, sizeof k_cameraPresets);
	GAME_VAR(int, g + 0x233cc10) = 1;
	FUN_0045dfb0((Stage *)s, -1);
	GAME_VAR(int, g + 0x23423e5) = 6;
	GAME_VAR(int, g + 0x23423ed) = 6;
	GAME_VAR(int, g + 0x2340c64) = -1;
	GAME_VAR(int, g + 0x2340c68) = GAME_VAR(int, g + 0x2340c6c) = GAME_VAR(int, g + 0x2340c70) = 0;
	GAME_VAR(int, g + 0x23423e9) = 3;
	GAME_VAR(int, g + 0x23423f1) = 7;
	GAME_VAR(int, g + 0x23423f5) = 10;
	GAME_VAR(int, g + 0x23423f9) = 0x18;
	char *macros = (char *)g + 0x234334b;
	for (int k = 0; k < 30; k++)
		macros[k * 0x40] = 0;
	void *f = crt_fopen((const char *)0x4c457c, (const char *)0x4ad5e0);
	if (f) {
#define crt_fgets(line, n, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, n, f)
		if (crt_fgets(macros, 0x3f, f))
			for (int k = 1; k < 30 && crt_fgets(macros + k * 0x40, 0x3f, f); k++)
				;
#undef crt_fgets
		fclose(f);
	}
	for (int k = 0; k < 30; k++) {
		char *m = macros + k * 0x40;
		m[(int)strlen(m) - 1] = 0;
	}
	CALL(0x4617f0, g);   /* chat_saveMacros */
	return g;
#undef CALL
#undef VECTOR
#undef VTABLE
}
