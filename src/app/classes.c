/* classes.c: the game's small C++ classes as the compiler built them: constructors (set the vtable, clear the
   members), destructors (the vtable set back, an owned buffer freed), the "deleting" destructors, and the helpers
   that clear a block of members. Most return what the original leaves in eax (usually 0 or the object). */
#include "../game.h"
#include <string.h>
#define GS ((Scene *)g)   /* the scene (g in each function) by its fields (src/scene.fields) */

/* n dwords of an object cleared */
static int clear(void *p, int dwords)
{
	u32 *q = p;
	for (int i = 0; i < dwords; i++)
		q[i] = 0;
	return 0;
}

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

/* ---- member blocks cleared, each the size of its class ---- */
int THISCALL (TextureManager_clear)(void *self) { return clear(self, 0x8); }       /* TextureManager */
int THISCALL (Model_clear)(void *self) { return clear(self, 0x13); }      /* Model */
int THISCALL (ShapeManager_clear)(void *self) { return clear(self, 0x93); }       /* ShapeManager */
int THISCALL (SkeletonManager_clear)(void *self) { return clear(self, 0x4c); }       /* SkeletonManager */
int THISCALL (collisionPlane_clear)(void *self) { return clear(self, 0x2b); }
int THISCALL (spaceBlock_clear)(void *self) { return clear(self, 0x14); }
int THISCALL (CollisionVolume_clear)(void *self) { return clear(self, 0x3d); }       /* CollisionVolume */
int THISCALL (ViewVolume_clear)(void *self) { return clear(self, 0x245c); }
int THISCALL (TimeSync_clear)(void *self) { return clear(self, 0xe); }        /* TimeSync */
int THISCALL (spaceNode_clear)(void *self) { return clear(self, 0x4); }

/* 0x483d60: Light's two counters cleared */
int THISCALL (Light_clearCounts)(void *self)
{
	((LightFactors *)self)->count = 0;
	((LightFactors *)self)->nextFree = 0;
	return 0;
}

/* 0x48fc30: the stage's script event ring emptied (its head and tail) */
int THISCALL (stage_clearScriptEvents)(void *self)
{
	((Stage *)self)->eventHead = 0;
	((Stage *)self)->eventTail = 0;
	return 0;
}

/* 0x4841d0: a view volume's three draw counters cleared */
void THISCALL (ViewVolume_clearDrawCounts)(void *view)
{
	((ViewVolume *)view)->trianglesDrawn = 0;
	((ViewVolume *)view)->meshesDrawn = 0;
	((ViewVolume *)view)->textureBinds = 0;
}

/* 0x480210: three ints set */
void THISCALL (ints_set3)(int *p, int a, int b, int c)
{
	p[0] = a;
	p[1] = b;
	p[2] = c;
}

/* 0x4569b0: the texture sets' members cleared (TextureManager_clear: the six managers), and its count (the class at
   0x83a5e0 is TextureSets, not a TextureManager) */
int THISCALL (TextureManager_reset)(void *self)
{
	TextureManager_clear(self);
	((TextureSets *)RELOC(self))->count = 0;
	return 0;
}

/* an object's owned block (BlockOwner: block, owned while ownsBlock is 1) freed */
static void free_owned(void *self)
{
	BlockOwner *bo = (BlockOwner *)self;
	if (bo->ownsBlock == 1) {
		operator_delete(bo->block);
		bo->block = NULL;
		bo->ownsBlock = 0;
	}
}

/* 0x464bc0, 0x466a30, 0x46ae80, 0x4813b0: the buffer freed, then the members cleared */
int THISCALL (Model_release)(void *self) { free_owned(self); Model_clear(self); return 0; }
int THISCALL (ShapeManager_release)(void *self) { free_owned(self); ShapeManager_clear(self); return 0; }
int THISCALL (SkeletonManager_release)(void *self) { free_owned(self); SkeletonManager_clear(self); return 0; }
int THISCALL (CollisionVolume_release)(void *self) { free_owned(self); CollisionVolume_clear(self); return 0; }

/* ---- getters ---- */
int (net_sessionCount)(void) { return g_dplaySessionCount; }
int (gfx_getWidth)(void) { return g_glWidth; }
int (gfx_getHeight)(void) { return g_glHeight; }
float (view_angle)(void) { return g_viewFov; }
float (view_nearPlane)(void) { return g_viewNear; }
float (view_farPlane)(void) { return g_viewFar; }

/* ---- setters ---- */
void (armc_showPartsPage)(void) { g_armcMode = 1; g_armcUnusedFlag = 0; }   /* the ARM CENTER's parts page */
void (armc_showColourPage)(void) { g_armcMode = 3; g_armcColourSlot = 5; }        /* its colour page */
void (ptx_startBitReader)(int v) { (*(int *)&g_bitStream) = v; g_ptxBitPos = 0; g_ptxLastDc = 0; }
int (input_setKeysBlocked)(int v) { g_keysBlocked = v; return v; }
int (music_setVolumeSetting)(int v) { g_musicVolumeSetting = v; return v; }

/* three-float vectors at 0xa0e7a8 ..: zero or a unit axis (bits of 1.0) */
static void set3(u32 addr, u32 x, u32 y, u32 z)
{
	u32 *p = (u32 *)RELOC(addr);
	p[0] = x;
	p[1] = y;
	p[2] = z;
}
void (vec_initOrigin)(void) { set3(ADDR(g_vecOrigin), 0, 0, 0); }
void (vec_initZero)(void) { set3(OBJ(g_vecZero2), 0, 0, 0); }
void (vec_initAxisZ)(void) { set3(ADDR(g_vecUnitZ), 0, 0, 0x3f800000u); }
void (vec_initUp)(void) { set3(OBJ(g_vecUnitY), 0, 0x3f800000u, 0); }
void (vec_initRest)(void) { set3(ADDR(g_vecZero), 0, 0, 0); }
void (vec_initAxisX)(void) { set3(OBJ(g_vecUnitX), 0x3f800000u, 0, 0); }

/* ---- class lifecycles ---- */

/* the deleting destructor: the plain one, then the object freed when flags & 1 */
#define DELETING(cls, dtor) \
	void *THISCALL (cls##_deletingDtor)(void *self, int flags) { dtor(self); if (flags & 1) operator_delete(self); return self; }

/* Texture (vtable 0x4a956c): 0x455030 (named Texture_dtor, in fact its destructor) frees the pixel buffer (+0x10c,
   held while +0x108 is not negative) and closes its file (+0x110); the result is what the last call left */
u32 THISCALL (Texture_dtor)(u32 *self)
{
	u32 r = self[0x42];
	self[0] = VT(Texture, 0x4a956c);
	if ((int)r >= 0) {
		r = GAME_CDECL(0x49ef24, u32, void *)((void *)RELOC(self[0x43]));   /* operator delete, its eax kept */
		self[0x42] = 0;
	}
	if (self[0x44] != 0)
		r = fclose((void *)RELOC(self[0x44]));
	return r;
}
DELETING(Texture, Texture_dtor)
/* the six global Texture objects' destructors at exit */
u32 (static_destroyTex64x64)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex64x64)); }
u32 (static_destroyTex128x64)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex128x64)); }
u32 (static_destroyTex256x64)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex256x64)); }
u32 (static_destroyTex128x128)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex128x128)); }
u32 (static_destroyTex256x128)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex256x128)); }
u32 (static_destroyTex256x256)(void) { return Texture_dtor((u32 *)ADDR(g_staticTex256x256)); }

/* TimeSync (vtable 0x4aa46c) */
void *THISCALL (TimeSync_ctor)(u32 *self) { self[0] = VT(TimeSync, 0x4aa46c); TimeSync_clear(self); return self; }
void THISCALL (TimeSync_dtor)(u32 *self) { self[0] = VT(TimeSync, 0x4aa46c); }
DELETING(TimeSync, TimeSync_dtor)
void (static_endTimeSync)(void) { TimeSync_dtor((u32 *)OBJ(g_loadTimer)); }

/* TextureManager (vtable 0x4a9570; the global one at 0x83a5e0) */
int (TextureManager_ctor)(void) { g_textureManager = STR(0x4a9570, "P\263B"); return TextureManager_clear((void *)ADDR(g_textureManager)); }
int THISCALL (TextureManager_dtor)(u32 *self) { self[0] = STR(0x4a9570, "P\263B"); return TextureManager_reset(self); }
DELETING(TextureManager, TextureManager_dtor)
void (static_endTextureManager)(void) { TextureManager_dtor((u32 *)ADDR(g_textureManager)); }

/* Scene (vtable 0x4aa258) */
void *THISCALL (Scene_ctor)(u32 *self) { self[0] = VT(Scene, 0x4aa258); debug_traceStripped(NULL); return self; }
void THISCALL (Scene_dtor)(u32 *self) { self[0] = VT(Scene, 0x4aa258); }
DELETING(Scene, Scene_dtor)

/* Light (vtable 0x4aa248) */
void *THISCALL (Light_ctor)(u32 *self) { self[0] = VT(Light, 0x4aa248); Light_clearCounts(self); return self; }
int THISCALL (Light_dtor)(u32 *self) { self[0] = VT(Light, 0x4aa248); return Light_clearCounts(self); }
DELETING(Light, Light_dtor)

/* CollisionVolume (vtable 0x4aa254) */
void *THISCALL (CollisionVolume_ctor)(u32 *self) { self[0] = STR(0x4aa254, "\2607F"); CollisionVolume_clear(self); return self; }
int THISCALL (CollisionVolume_dtor)(u32 *self) { self[0] = STR(0x4aa254, "\2607F"); return CollisionVolume_release(self); }
DELETING(CollisionVolume, CollisionVolume_dtor)

/* Model (vtable 0x4aa250) */
void *THISCALL (Model_ctor)(u32 *self) { self[0] = VT(Model, 0x4aa250); Model_clear(self); return self; }
int THISCALL (Model_dtor)(u32 *self) { self[0] = VT(Model, 0x4aa250); return Model_release(self); }
DELETING(Model, Model_dtor)

/* ShapeManager (vtable 0x4aa244), SkeletonManager (vtable 0x4aa240) */
int THISCALL (ShapeManager_dtor)(u32 *self) { self[0] = VT(ShapeManager, 0x4aa244); return ShapeManager_release(self); }
DELETING(ShapeManager, ShapeManager_dtor)
int THISCALL (SkeletonManager_dtor)(u32 *self) { self[0] = STR(0x4aa240, "\3207F"); return SkeletonManager_release(self); }
DELETING(SkeletonManager, SkeletonManager_dtor)

/* BMPRGBFile (vtable 0x4a96f8): 0x46ce60 (named BMPRGBFile_ctor, in fact its destructor) closes its file */
void THISCALL (BMPRGBFile_ctor)(u32 *self) { self[0] = VT(BMPRGBFile, 0x4a96f8); if (self[1]) fclose((void *)RELOC(self[1])); }
DELETING(BMPRGBFile, BMPRGBFile_ctor)

/* ErrorLog (vtable 0x4aa2a0): the class-name records */
void THISCALL (ErrorLog_dtor)(u32 *self) { self[0] = VT(ErrorLog, 0x4aa2a0); }
DELETING(ErrorLog, ErrorLog_dtor)
void (static_endSoundRtti)(void) { ErrorLog_dtor(g_logSound); }
void *THISCALL (ErrorLog_ctor)(u32 *self, const char *name, int b)
{
	self[0] = VT(ErrorLog, 0x4aa2a0);
	self[1] = (u32)name;
	g_errorCleanupHook = b;
	return self;
}

/* 0x463850: a resource set (a PlayerRecord's part caches): five shape managers (vtable 0x4aa244) and five skeleton managers (0x4aa240) built in
   place (the original's exception frame only matters if a constructor throws, and these cannot) */
void *THISCALL (ResourceSet_ctor)(u8 *self)
{
	static const u32 shapes[5] = { offsetof(PlayerRecord, headShapes), offsetof(PlayerRecord, chestShapes), offsetof(PlayerRecord, armShapes), offsetof(PlayerRecord, legShapes), offsetof(PlayerRecord, boosterShapes) };
	static const u32 skels[5] = { offsetof(PlayerRecord, headSkels), offsetof(PlayerRecord, chestSkels), offsetof(PlayerRecord, armSkels), offsetof(PlayerRecord, legSkels), offsetof(PlayerRecord, boosterSkels) };
	for (int i = 0; i < 5; i++) {
		*(u32 *)(self + shapes[i]) = VT(ShapeManager, 0x4aa244);
		ShapeManager_clear(self + shapes[i]);
	}
	for (int i = 0; i < 5; i++) {
		*(u32 *)(self + skels[i]) = STR(0x4aa240, "\3207F");
		SkeletonManager_clear(self + skels[i]);
	}
	return self;
}

/* ---- arrays of members released ---- */
/* a manager's items (count of them, stride bytes each) each released, the count 0; dataUsed set to 0 if it was
   positive; returns its old value */
typedef int (THISCALL *Release)(void *entry);
static int release_all(u8 *self, int stride, Release release)
{
	Manager *mg = (Manager *)self;
	if (mg->count > 0) {
		for (int i = 0; i < mg->count; i++)
			release(mg->items + i * stride);
		mg->count = 0;
	}
	int r = mg->dataUsed;
	if (r > 0)
		mg->dataUsed = 0;
	return r;
}
static int THISCALL release_model(void *e) { return Model_release(e); }
static int THISCALL release_skeleton(void *e) { return Skeleton_release(e); }
/* 0x467520: a shape manager's models (0x4c bytes) */
int THISCALL (ShapeManager_releaseModels)(u8 *self) { return release_all(self, 0x4c, release_model); }
/* 0x46b7f0: a skeleton manager's skeletons (0x24 bytes) */
int THISCALL (SkeletonManager_releaseSkeletons)(u8 *self) { return release_all(self, 0x24, release_skeleton); }

/* 0x45ff30: an object's eight member lists destroyed (UnitPoseInfo_dtor, the last member first: +0x701c .. +0x554).
   Returns the last call's eax */
u32 THISCALL (actor_destroyPartLists)(u8 *self)
{
	static const u32 members[8] = { offsetof(Player, weaponModel5), offsetof(Player, weaponModel4), offsetof(Player, weaponModel), offsetof(Player, boosterModel), offsetof(Player, legsModel), offsetof(Player, armsModel), offsetof(Player, chestModel), offsetof(Player, headModel) };
	u32 r = 0;
	for (int k = 0; k < 8; k++)
		r = UnitPoseInfo_dtor(self + members[k]);
	return r;
}

/* 0x463960: a resource set destroyed: its five skeleton managers, then its five shape managers, the last member first
   (as ResourceSet_ctor built them). Returns the last destructor's eax */
u32 THISCALL (ResourceSet_dtor)(u8 *self)
{
	static const u32 skeletons[5] = { offsetof(PlayerRecord, boosterSkels), offsetof(PlayerRecord, legSkels), offsetof(PlayerRecord, armSkels), offsetof(PlayerRecord, chestSkels), offsetof(PlayerRecord, headSkels) };
	static const u32 shapes[5] = { offsetof(PlayerRecord, boosterShapes), offsetof(PlayerRecord, legShapes), offsetof(PlayerRecord, armShapes), offsetof(PlayerRecord, chestShapes), offsetof(PlayerRecord, headShapes) };
	u32 r = 0;
	for (int k = 0; k < 5; k++)
		GAME_THISFN(SkeletonManager_dtor, 0x46ae60, u32, void *)(self + skeletons[k]);   /* SkeletonManager_dtor */
	for (int k = 0; k < 5; k++)
		r = GAME_THISFN(ShapeManager_dtor, 0x466a10, u32, void *)(self + shapes[k]);  /* ShapeManager_dtor */
	return r;
}

#define eh_vector_destructor(array, size, count, dtor) \
	((void (STDCALL *)(void *, u32, int, u32))IMG(0x49fc4f))(array, size, count, dtor)   /* `eh vector destructor iterator' (stdcall) */

/* 0x46ff70: the stage destroyed, its members last first: 0x48b410 (+0x2148ed8), the 100 actors (+0x1cd93a8,
   0x8888 bytes each, 0x45ff30), the skeleton and shape managers, the 16 resource sets (+0x1561b68, 0x47fd2 bytes
   each, ResourceSet_dtor), two more managers, two 0x464ba0 tables, the three factor pools and +0xa10.
   Returns the last destructor's eax */
u32 THISCALL (Stage_dtor)(u8 *self)
{
	Stage *stage = (Stage *)self;
	*(u32 *)self = STR(0x4aa23c, "08F");   /* the vtable */
	Scene_dtor((u8 *)&stage->scenePath);
	eh_vector_destructor((u8 *)stage->actors, 0x8888, 100, FN_ADDR(actor_destroyPartLists, 0x45ff30));
	SkeletonManager_dtor((u8 *)&stage->partSkeletons);   /* SkeletonManager_dtor */
	GAME_THISFN(ShapeManager_dtor, 0x466a10, void, void *)((u8 *)&stage->partShapes);   /* ShapeManager_dtor */
	eh_vector_destructor((u8 *)stage->playerRecords, 0x47fd2, 16, FN_ADDR(ResourceSet_dtor, 0x463960));
	SkeletonManager_dtor((u8 *)&stage->objectSkeletons);
	ShapeManager_dtor((u8 *)&stage->objectShapes);
	Model_dtor((u8 *)&stage->layerBoxModel);
	Model_dtor((u8 *)&stage->layerModel);
	Light_dtor((u8 *)&((Stage *)self)->actorLights);
	Light_dtor((u8 *)&((Stage *)self)->dynamicLights);
	Light_dtor((u8 *)&((Stage *)self)->mapLights);
	return GAME_THISFN(CollisionVolume_dtor, 0x481390, u32, void *)((u8 *)&stage->space);
}

/* 0x46cd00 (thiscall on an image): a 24-bit BMP opened (the last one closed first): its file header (14 bytes, +8)
   and info header (0x28 bytes, +0x16) read, each missing a fatal message, and anything but 24 bits uncompressed one
   too; its width and height kept (+0x3e, +0x42). Returns the file, or 0 when it can't be opened */
void *THISCALL (image_initBy)(u8 *image, const char *path)
{
	BmpFile *bmp = (BmpFile *)image;
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define fatal(text) sys_fatalErrorN((char *)OBJ(g_logBMPRGBFile), (const char *)RELOC(text))
	if (bmp->file)
		fclose(bmp->file);
	void *f = bmp->file = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		return 0;
	if (crt_fread(&bmp->type, 0xe, 1, f) < 1)   /* (the BITMAPFILEHEADER) */
		fatal(STR(0x4c5948, "can't read header-initBy()"));
	if (crt_fread(&bmp->infoSize, 0x28, 1, bmp->file) < 1)   /* (the BITMAPINFOHEADER) */
		fatal(STR(0x4c592c, "can't read info-initBy()"));
	if (bmp->bitCount != 24 || bmp->compression != 0)
		fatal(STR(0x4c5908, "non-RGB format BMP file-initBy()"));
	bmp->width = ((u32)bmp->bmpWidth);
	bmp->height = ((u32)bmp->bmpHeight);
	return bmp->file;
#undef crt_fread
#undef fatal
}

/* 0x46cdc0 (thiscall on an image): as image_initBy, without the fatal messages: the file, or 0 when it can't be
   opened, a header is short, or it isn't 24 bits uncompressed (the file then stays open at +4) */
void *THISCALL (image_tryOpen)(u8 *image, const char *path)
{
	BmpFile *bmp = (BmpFile *)image;
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	if (bmp->file)
		fclose(bmp->file);
	void *f = bmp->file = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f || crt_fread(&bmp->type, 0xe, 1, f) < 1 || crt_fread(&bmp->infoSize, 0x28, 1, bmp->file) < 1
	    || bmp->bitCount != 24 || bmp->compression != 0)
		return 0;
	bmp->width = ((u32)bmp->bmpWidth);
	bmp->height = ((u32)bmp->bmpHeight);
	return bmp->file;
#undef crt_fread
}

/* 0x4734d0 (named gfx_saveScreenshot; by use a part type's emblem loaded): the BMP named after type p (its record at
   +0x1561b68, 0x47fd2 bytes each; the name from +4 by 0x4c74e8) read into a local image; at least 23 x 15 of it: its
   24 x 16 corner copied as RGBA into the record (+0x479c2), black pixels made clear and the rest opaque, and 1
   returned; else 0 */
int THISCALL (gfx_saveScreenshot)(u8 *scene, int p)
{
	u8 *type = (u8 *)&((Stage *)scene)->playerRecords[p];
	u8 image[0x48];
	GAME_VAR(u32, image) = VT(BMPRGBFile, 0x4a96f8);   /* (its vtable) */
	BITS(((BmpFile *)image)->file) = 0;      /* (no file yet) */
	char path[0x100];
	sprintf(path, (const char *)STR(0x4c74e8, "Save\\%s.BMP"), type + 4);
	int ok = 0;
	if (image_tryOpen(image, path)) {
		if (((BmpFile *)image)->width >= 23 && ((BmpFile *)image)->height >= 15) {
			u8 *pixel = (u8 *)((PlayerRecord *)type)->emblem;
			image_copyTo(image, pixel, 24, 16, 4, 0, 0, 0, 0, 24, 16, 0);
			for (int k = 0; k < 24 * 16; k++, pixel += 4)
				pixel[3] = pixel[0] == 0 && pixel[1] == 0 && pixel[2] == 0 ? 0 : 0xff;
			ok = 1;
		}
		BMPRGBFile_close(image);
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
		PlayerRecord *pr = &((Stage *)scene)->playerRecords[p];
		if (pr->emblemChanged != 1)
			continue;
		u32 *atlas = &((Stage *)scene)->emblemAtlas[(p / 4) * 16][(p % 4) * 24];
		const u32 *pixel = &pr->emblem[0][0];
		for (int y = 0; y < 16; y++, atlas += 128)
			for (int x = 0; x < 24; x++)
				atlas[x] = *pixel++;
		pr->emblemChanged = 0;
		if (!pr->flagShown) {
			pr->flagShown = 1;
			uploaded = 1;
		}
	}
	if (uploaded != 1)
		return;
	glPixelStorei(0xcf5, 1);   /* GL_UNPACK_ALIGNMENT */
	glBindTexture(0xde1, ((Stage *)scene)->emblemTexture);
	glTexParameterf_bits(0xde1, 0x2802, 0x46240000);   /* wrap S: GL_CLAMP */
	glTexParameterf_bits(0xde1, 0x2803, 0x46240000);   /* wrap T */
	glTexParameterf_bits(0xde1, 0x2800, 0x46180400);   /* mag filter: GL_LINEAR */
	glTexParameterf_bits(0xde1, 0x2801, 0x46180400);   /* min filter */
	glTexImage2D(0xde1, 0, 4, 0x80, 0x40, 0, 0x1908, 0x1401, (u8 *)((Stage *)scene)->emblemAtlas);   /* RGBA, unsigned bytes */
}

/* 0x46ce80 (thiscall on an image): a w x h block of the open 24-bit BMP (its file +4, pixel data at +0x12, size +0x3e
   x +0x42, rows stored bottom-up) from (sx, sy) copied into the dw x dh buffer dst at (dx, dy), both clipped (nothing
   left: nothing; wider than 0x400 a fatal message): BGR to RGB (depth 3) or RGBA with alpha 0xff (depth 4; another
   depth a fatal message per row), the rows placed top-down when topDown, else bottom-up. Its callers ignore the eax
   it leaves */
void THISCALL (image_copyTo)(u8 *image, u8 *dst, int dw, int dh, int depth, int sx, int sy, int dx, int dy, int w, int h,
                             int topDown)
{
	BmpFile *bmp = (BmpFile *)image;
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	void *f = bmp->file;
	int iw = bmp->width, ih = bmp->height;
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
		sys_fatalErrorN((char *)OBJ(g_logBMPRGBFile), (const char *)STR(0x4c5984, "temporary imageWidthA exceeds _SIZE_O..."));
	crt_fseek(f, bmp->dataOffset + ((bmp->height - sy - h) * bmp->width + sx) * 3, 0);
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
			sys_fatalErrorN((char *)OBJ(g_logBMPRGBFile), (const char *)STR(0x4c5964, "invalid bufferDepthA-copyTo()"));
		crt_fseek(f, (bmp->width - w) * 3, 1);
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
   message); the ten camera presets, the stage's player slots reset (stage_selectActor -1), the geometry check sizes; the
   help text (Help.txt: 30 lines of 63 characters into consoleLines) read, each with its line end cut (an empty one
   cuts the byte before it), and the chat macros loaded (chat_loadMacros). (The original's SEH frame, for
   unwinding a failed construction, is not reproduced.) Returns the object */
u8 *THISCALL (game_loadAllData)(u8 *g)
{
#define CALL(addr, at) GAME_THISCALL(addr, void, void *)(at)
#define VECTOR(at, size, count) ((void (STDCALL *)(void *, int, int, u32))FN_ADDR(crt_arrayConstruct, 0x401290))(at, size, count, FN_ADDR(ResourceSet_trivialCtor, 0x45fff0))   /* (the CRT's iterators are stdcall) */
#define VTABLE(at, vt) (GAME_VAR(u32, at) = (vt))
	u8 *s = (u8 *)SCENE_STAGE(g);
	Stage *st = (Stage *)s;
	TimeSync_ctor((u8 *)&GS->timer);   /* TimeSync_ctor */
	VTABLE((u8 *)GS->view, STR(0x4aa24c, "04F"));
	ViewVolume_clear((u8 *)GS->view);
	CollisionVolume_ctor((u8 *)&st->space);   /* CollisionVolume_ctor */
	VECTOR((u8 *)((Stage *)s)->mapLights.records, sizeof(Factor), 0x400);
	VTABLE((u8 *)&((Stage *)s)->mapLights, VT(Light, 0x4aa248));
	Light_clearCounts((u8 *)&((Stage *)s)->mapLights);
	VECTOR((u8 *)((Stage *)s)->dynamicLights.records, sizeof(Factor), 0x400);
	VTABLE((u8 *)&((Stage *)s)->dynamicLights, VT(Light, 0x4aa248));
	Light_clearCounts((u8 *)&((Stage *)s)->dynamicLights);
	Light_ctor((u8 *)&((Stage *)s)->actorLights);   /* Light_ctor */
	VECTOR((u8 *)st->skySphere, 0xc, 0x126);
	VECTOR((u8 *)st->layer, 0xc, 0x31);
	VECTOR((u8 *)st->sides, 0xc, 0x30);
	VECTOR((u8 *)st->floor, 0xc, 0x79);
	VECTOR((u8 *)st->groundLayers, 0x20c, 4);
	Model_ctor((u8 *)&st->layerModel);   /* Model_ctor */
	Model_ctor((u8 *)&st->layerBoxModel);
	VECTOR((u8 *)st->wayPoints, 0x14, 0x3e8);
	VTABLE((u8 *)&st->objectShapes, VT(ShapeManager, 0x4aa244));
	ShapeManager_clear((u8 *)&st->objectShapes);
	VECTOR((u8 *)st->objectColours, 4, 1000000);
	VTABLE((u8 *)&st->objectSkeletons, STR(0x4aa240, "\3207F"));
	SkeletonManager_clear((u8 *)&st->objectSkeletons);
	VECTOR((u8 *)st->objects, 0x2cc, 0x3e8);
	VECTOR((u8 *)st->actorInfo, 0x2e18, 0x32);
	((void (STDCALL *)(void *, int, int, u32, u32))IMG(0x49fd2d))((u8 *)st->playerRecords, 0x47fd2, 0x10, FN_ADDR(ResourceSet_ctor, 0x463850), FN_ADDR(ResourceSet_dtor, 0x463960));
	VTABLE((u8 *)&st->partShapes, VT(ShapeManager, 0x4aa244));
	ShapeManager_clear((u8 *)&st->partShapes);
	VTABLE((u8 *)&st->partSkeletons, STR(0x4aa240, "\3207F"));
	SkeletonManager_clear((u8 *)&st->partSkeletons);
	VECTOR((u8 *)st->mapActors, 0x5c, 0x64);
	((void (STDCALL *)(void *, int, int, u32, u32))IMG(0x49fd2d))((u8 *)st->actors, 0x8888, 0x64, FN_ADDR(ResourceSet_initLists, 0x463a40), FN_ADDR(actor_destroyPartLists, 0x45ff30));
	VECTOR((u8 *)st->bullets, 0x4e8, 0x190);
	VECTOR((u8 *)st->projectiles, 0x12c, 0x3e8);
	VECTOR((u8 *)st->points, 0xc, 0xc8);
	VECTOR((u8 *)st->starts, 0x14, 0x20);
	VECTOR((u8 *)st->items, 0x28, 0xc8);
	VECTOR((u8 *)st->emblemAtlas, 4, 0x2000);
	Scene_ctor((u8 *)&st->scenePath);   /* Scene_ctor */
	VTABLE(s, STR(0x4aa23c, "08F"));
	((Stage *)s)->built = 0;
	VTABLE(g, VT(Console, 0x4aa238));
	GS->client = GS->network = -1;
	TimeSync_clear((u8 *)&GS->timer);
	for (int k = 0; k < 10; k++)
		BITS(GS->frameTimes[k]) = 0x3d088889;   /* 1/30 */
	GS->frameTimeNext = 0;
	factor_initBy((u8 *)GS->view, 10000, 1000, 20000, 4000, 400, 10000,
	                                                                                GS->viewMemory, sizeof GS->viewMemory);   /* factor_initBy */
	item_initTextures(s, STR(0x4c45a8, "Stage"), STR(0x4b1784, "Map"), STR(0x4c45b0, "Texture"), STR(0x4c45b8, "Shape"),
	                                                                                  STR(0x4c45c0, "Skeleton"), STR(0x4c45cc, "Actor"), STR(0x4c45d4, "Bullet"), STR(0x4c45dc, "Effect"), STR(0x4c45e4, "Scene"));   /* item_initTextures */
	if (!PATCHED_THISCALL(0x460920, int, void *, const char *)(s, (const char *)STR(0x4b4418, "Data/Component.dat")))   /* catalogue_loadComponents (the patch DLL adds the KYRIE parts here) */
		sys_fatalErrorN((char *)OBJ(g_logConsole), (const char *)STR(0x4c4598, "file damaged!"));
	if (!map_loadItemInfoFrom(s, (const char *)STR(0x4c4588, "Data/Item.dat")))   /* map_loadItemInfoFrom */
		sys_fatalErrorN((char *)OBJ(g_logConsole), (const char *)STR(0x4c4598, "file damaged!"));
	memcpy(GS->cameraPresets, k_cameraPresets, sizeof k_cameraPresets);
	GS->cameraMode = 1;
	stage_selectActor((Stage *)s, -1);
	GS->geometryPerRow[0] = 6;
	GS->geometryPerRow[2] = 6;
	GS->watchedPlayer = -1;
	GS->watchClear[0] = GS->watchClear[1] = GS->watchClear[2] = 0;
	GS->geometryPerRow[1] = 3;
	GS->geometryPerRow[3] = 7;
	GS->geometryPerRow[4] = 10;
	GS->geometryPerRow[5] = 0x18;
	for (int k = 0; k < 30; k++)
		GS->consoleLines[k][0] = 0;
	void *f = crt_fopen((const char *)STR(0x4c457c, "Help.txt"), (const char *)STR(0x4ad5e0, "rt"));
	if (f) {
#define crt_fgets(line, n, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, n, f)
		if (crt_fgets(GS->consoleLines[0], 0x3f, f))
			for (int k = 1; k < 30 && crt_fgets(GS->consoleLines[k], 0x3f, f); k++)
				;
#undef crt_fgets
		fclose(f);
	}
	for (int k = 0; k < 30; k++) {
		char *m = GS->consoleLines[k];   /* (the help text's lines, from Help.txt) */
		m[(int)strlen(m) - 1] = 0;
	}
	chat_loadMacros(g);   /* chat_loadMacros */
	return g;
#undef CALL
#undef VECTOR
#undef VTABLE
}

/* n dwords from at set to 0 (some of the game object's are unaligned) */
static void zero_dwords(u8 *at, int n)
{
	for (int k = 0; k < n; k++)
		GAME_VAR(u32, at + k * 4) = 0;
}

/* 0x460cb0 (thiscall on the game object): a session started in mode (+4 a, +8 mode). With no CD found a fatal
   message. Its counters cleared; in mode 3 the names of the map list entries flagged +0x40 (0x9dda88, 0x44-byte
   records, 0x9eeab8 of them) copied to +0x1f1cbc (0x40 each, count +0x1f35bc); actors and scene reset; mode 2 also
   clears the armour cache, the view box (+0xbe2fcc: -100000 .. 100000, twice), and sets the game type flags for type
   0; the camera from 0xa0e7a8.. (direction negated), the HUD mode +0x233cc20 (mode 2 -> 3, 3 -> 1, else 2) and its
   defaults, the match state (teams_setup), the notices (notices_clearAll) and the lobby slots (+0x234240d -1 in modes 1
   and 3). Its callers ignore the eax it leaves */
void THISCALL (app_requireCd)(u8 *g, u32 a, int mode)
{
	if (!cd_findDrive())
		sys_fatalErrorN((char *)OBJ(g_logConsole), g_insertCdMessage);
	GS->client = a;
	GS->network = mode;
	GS->objectsMode = 0;
	zero_dwords((u8 *)g + offsetof(Scene, rotationCount), 3);   /* rotationCount .. rotationOff */
	zero_dwords((u8 *)g + offsetof(Scene, frameFlag), 3);   /* frameFlag .. showEmblems */
	GS->replayCount = 0;
	if (GS->network == 3)
		for (int k = 0; k < g_mapListFlaggedCount; k++) {
			const char *e = g_fileList[k].name;
			if (g_fileList[k].flag == 1)
				strcpy(GS->replayFiles[GS->replayCount++], e);
		}
	u8 *s = (u8 *)SCENE_STAGE(g);
	GS->replayIndex = GS->replayVersion = 0;
	scene_resetActors(s);
	scene_reset(s);
	if (GS->network == 2) {
		stage_setSilentActor(s, 0);   /* stage_setSilentActor */
		GS->soloClear = 0;
		for (int k = 0; k < 3; k++) {
			((Stage *)s)->levelLow[k] = -100000.0f;
			((Stage *)s)->levelHigh[k] = 100000.0f;
		}
		memcpy(((Stage *)s)->worldLow, ((Stage *)s)->levelLow, 12);
		memcpy(((Stage *)s)->worldHigh, ((Stage *)s)->levelHigh, 12);
		BITS(GS->unusedBe2ffc) = 0x3f800000;
		game_setGameTypeFlags((Stage *)s, 0);
	}
	GS->playing = GS->unused233ca00 = 0;
	memcpy(GS->cameraPos, (const void *)ADDR(g_vecOrigin), 12);
	for (int k = 0; k < 3; k++)
		GS->cameraDir[k] = f32(-fld_m((const float *)ADDR(g_vecUnitZ) + k));
	memcpy(GS->cameraUp, (const void *)OBJ(g_vecUnitY), 12);
	(*(int *)&GS->cameraAngle[0]) = (*(int *)&GS->cameraAngle[1]) = 0;
	GS->inputState = GS->network == 2 ? 3 : GS->network == 3 ? 1 : 2;
	GS->modeStarted = GS->wholeSeconds = (*(int *)&GS->secondFraction) = 0;
	(*(int *)&GS->msgFade) = GS->unused233cc44 = 0;
	BITS(GS->emblemTime) = 0x43960000;   /* 300, 3, 5, 15 */
	BITS(GS->roundTimer) = 0x40400000;
	BITS(GS->kingTimer) = 0x40a00000;
	BITS(GS->teamSyncTime) = 0x41700000;
	zero_dwords((u8 *)GS->cleared2340ca4, 11);
	GS->debugGrid = 1;
	zero_dwords((u8 *)g + offsetof(Scene, debugPoints), 13);   /* debugPoints .. rankingShown */
	zero_dwords((u8 *)g + offsetof(Scene, recording), 7);   /* recording .. chatMode */
	teams_setup((Scene *)g);
	zero_dwords((u8 *)g + offsetof(Scene, lostTime), 8);   /* lostTime .. timeLimit */
	GS->endedByTime = -1;
	zero_dwords((u8 *)g + offsetof(Scene, geometryCheckTurn), 7);   /* geometryCheckTurn .. geometryPick */
	GS->roundClear2 = (*(int *)&GS->previewTurn) = 0;
	zero_dwords((u8 *)g + offsetof(Scene, holdAltitude), 10);   /* holdAltitude .. holdBooster */
	GS->viewKey = -1;
	zero_dwords((u8 *)g + offsetof(Scene, holdZoom), 31);   /* holdZoom .. helpPressed */
	zero_dwords((u8 *)g + offsetof(Scene, menuKeys), 4);   /* menuKeys */
	notices_clearAll(g);
	GS->localPlayer = GS->network == 1 || GS->network == 3 ? -1 : 0;
	zero_dwords((u8 *)g + offsetof(Scene, roundClear4), 3);   /* roundClear4 .. statsTaken */
	GS->chosenTeam = -1;
	GS->screenshotTaken = 0;
	GS->itemLevelsTaken = 0;
}
