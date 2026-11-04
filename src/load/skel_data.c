/* skel_data.c: a skeleton's data block: its header read or set, then one block (allocated, or the caller's memory
   when it is big enough, else a fatal message: the record out and the two messages given) laid out as the bones' records followed by their tables. */
#include "../game.h"
#include <string.h>

#define AT(type, p, offset) GAME_VAR(type, (u8 *)RELOC(p) + (offset))

/* the block (BlockOwner: block, its size blockSize): allocated (owned: ownsBlock 1) without memory given, else the
   memory given (owned 0 when own_flag; the caller's size checked) */
static void take_block(u8 *self, void *mem, int size, char *out, u32 no_memory, u32 too_small, int own_flag)
{
	BlockOwner *bo = (BlockOwner *)self;
	if (!mem) {
		bo->block = operator_new(bo->blockSize);
		if (!bo->block)
			sys_fatalError(out, (const char *)RELOC(no_memory), bo->blockSize);
		bo->ownsBlock = 1;
	} else {
		if (size < bo->blockSize)
			sys_fatalErrorN(out, (const char *)RELOC(too_small), bo->blockSize, size);
		bo->block = mem;
		if (own_flag)
			bo->ownsBlock = 0;
	}
}

/* 0x46aa10 (thiscall on a skeleton): read from f: the 0x24-byte header, the block (+8, its size +4), then the bones
   (0x70 bytes each, +0x10 of them, at the block's start: +0x14) and after them each bone's two tables (+0x60 keys of
   0x20 bytes at +0x64, +0x68 frames of 0x28 bytes at +0x6c). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFromFile)(u8 *self, void *f, void *mem, int size)
{
	Skeleton *sko = (Skeleton *)self;
	Skeleton_release(self);
	crt_fread(self, 0x24, 1, f);
	take_block(self, mem, size, (char *)OBJ(g_logSkeleton), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *bones = sko->bones = sko->block;
	crt_fread(bones, 0x70, ((u32)sko->boneCount), f);
	int at = sko->boneCount * 0x70;
	for (int i = 0; i < sko->boneCount; i++) {
		u8 *bone = sko->bones + i * 0x70;
		Bone *bn = (Bone *)bone;
		((Bone *)bone)->posKeys = sko->block + at;
		u32 keys = ((u32)bn->posKeyCount);
		at += keys * 0x20;
		((Bone *)bone)->rotKeys = sko->block + at;
		at += bn->rotKeyCount * 0x28;
		crt_fread((*(void * *)&((Bone *)bone)->posKeys), 0x20, keys, f);
		crt_fread((*(void * *)&((Bone *)bone)->rotKeys), 0x28, ((u32)bn->rotKeyCount), f);
	}
}

/* 0x46aeb0 (thiscall on a skeleton set): set up for n skeletons from the directory dir (+0x10; none: 0x4b1304), a at
   +0x110, n at +0x114, extra bytes (+0x124) after them: the block (+8, its size n x 0x70 + extra at +4) holds the
   skeletons' 0x4c-byte records (+0x118), then their 0x24-byte skeletons (+0x11c, each created and released), then the
   rest (+0x128). Its callers ignore the eax it leaves */
void THISCALL (skelSet_setup)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	Manager *mg = (Manager *)self;
	SkeletonManager_release(self);
	strcpy(mg->dir, dir ? dir : (const char *)STR(0x4b1304, "."));
	mg->setupArg = a;
	mg->capacity = n;
	mg->dataSize = extra;
	mg->blockSize = n * 0x70 + extra;
	take_block(self, mem, size, (char *)OBJ(g_logSkeletonManager), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 0);
	n = mg->capacity;
	mg->nodes = mg->block;
	mg->items = mg->block + n * 0x4c;
	for (int i = 0; i < mg->capacity; i++) {
		Skeleton_clear(mg->items + i * 0x24);
		Skeleton_release(mg->items + i * 0x24);
	}
	mg->data = mg->block + n * 0x70;
}

/* 0x466a60 (thiscall on a shape set): set up for n shapes from the directory dir (+0x10, upper-cased; none or
   0x4b1304: empty), a at +0x110, n at +0x114, extra bytes (+0x124) after them: the block (+8, its size n x 0x98 +
   extra at +4) holds the shapes' 0x4c-byte records (+0x118), then their 0x4c-byte shapes (+0x11c, each created and
   released), then the rest (+0x128); the name (+0x130) and seven counts (+0x230 ..) cleared. Its callers ignore the
   eax it leaves */
void THISCALL (shape_initBy)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	Manager *mg = (Manager *)self;
	ShapeManager_release(self);
	if (dir && strcmp(dir, (const char *)STR(0x4b1304, ".")) != 0)
		strcpy(mg->dir, dir);
	else
		mg->dir[0] = 0;
	path_normalize(mg->dir);
	mg->setupArg = a;
	mg->capacity = n;
	mg->dataSize = extra;
	mg->blockSize = n * 0x98 + extra;
	take_block(self, mem, size, (char *)OBJ(g_logShapeManager), STR(0x4c4cec, "insufficient memory for dataMemory(%d..."), STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -..."), 0);
	n = mg->capacity;
	mg->nodes = mg->block;
	mg->items = mg->block + n * 0x4c;
	for (int i = 0; i < mg->capacity; i++) {
		Model_clear(mg->items + i * 0x4c);
		Model_release(mg->items + i * 0x4c);
	}
	mg->textureDir[0] = 0;
	mg->data = mg->block + n * 0x98;
	for (int k = 0; k < 7; k++)
		AT(int, self, offsetof(Manager, bindFlags) + k * 4) = 0;   /* bindFlags, tint */
}

/* a file's format by its extension (after the last '.', none past a '\' or '/'; its first three letters compared
   without case): 0 the first name given, 1 the second, -1 neither */
static int file_format(const char *path, const char *first, const char *second)
{
	int i = (int)strlen(path) - 1;
	for (; i >= 0 && path[i] != '.'; i--)
		if (path[i] == '\\' || path[i] == '/')
			return -1;
	if (i < 0)
		return -1;
	char ext[0x100];
	strcpy(ext, path + i + 1);
	for (int k = 0; k < 2; k++) {
		const char *name = k ? second : first;
		if (crt_tolower(ext[0]) == name[0] && crt_tolower(ext[1]) == name[1] && crt_tolower(ext[2]) == name[2])
			return k;
	}
	return -1;
}

/* 0x464bf0 (thiscall on a shape): loaded from the file path (a failed open is a fatal message) by its extension:
   "shp" the binary format (shape_read), "obj" Wavefront text (model_loadObjFormatFrom), anything else a fatal
   message; the file closed. Its callers ignore the eax it leaves */
void THISCALL (model_loadFrom)(u8 *shape, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4ae4, "can not read file %s-loadFrom()"), (int)path);
	switch (file_format(path, "shp", "obj")) {
	case 0:
		shape_read(shape, f, mem, size);
		break;
	case 1:
		model_loadObjFormatFrom(shape, f, mem, size);
		break;
	default:
		sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4aa4, "can't figure out what the format of t..."), (int)path);
	}
	fclose(f);
}

/* 0x4699d0 (thiscall on a skeleton): the same for skeletons: "ske" the binary format (skel_loadFromFile), "ase"
   ASCII scene export (skel_loadAseFrom). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom)(u8 *sk, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_fatalError((char *)OBJ(g_logSkeleton), (const char *)STR(0x4c4ae4, "can not read file %s-loadFrom()"), (int)path);
	switch (file_format(path, "ske", "ase")) {
	case 0:
		skel_loadFromFile(sk, f, mem, size);
		break;
	case 1:
		skel_loadAseFrom(sk, f, mem, size);
		break;
	default:
		sys_fatalError((char *)OBJ(g_logSkeleton), (const char *)STR(0x4c4aa4, "can't figure out what the format of t..."), (int)path);
	}
	fclose(f);
}

/* 0x46f4e0 (thiscall on an object list): emptied (partList_release), then ns shapes (by the names 0x44 apart, each with
   an int at +0x40; looked up in the shape cache, the first 64 once, any later ones again when the entries are
   filled) with their element counts summed (+0x18), and nk skeletons (by the names 0x40 apart). Its block (+8, size
   +4: 100 bytes a shape, 4 a skeleton, lit == 1 a colour per element too): allocated (owned, +0xc 1; none a fatal
   message) without memory given, else that memory (too small: a fatal message). The entries (+0x14: shape, int,
   colours when lit and found), the skeletons after them (+0x20), and lit, the colours worked out (ObjectList_relight). Its
   callers ignore the eax it leaves */
void THISCALL (ObjectList_load)(u8 *list, void *shapes, void *skels, int ns, const u8 *names, int nk, const u8 *knames,
                                     int lit, u32 factors, u32 lights, void *mem, int size)
{
	ObjectList *ol = (ObjectList *)list;
	partList_release(list);
	ol->count = ns;
	ol->frameCount = nk;
	ol->preLit = lit;
	ol->colourCount = 0;
	/* 65, and the entries walked by pointer: the frame is then as deep as the original's (0x11c with the saved
	   registers), so the callees' frames lie where they did there. The skeleton loading reads stack it never wrote
	   (the earlier callees' leftovers); a frame 4 bytes deeper gave those reads other values now and then */
	u32 found[65];
	for (int i = 0; i < ol->count; i++) {
		u32 shape = shape_getByName(shapes, (const char *)names + i * 0x44, 0);
		if (i < 64)
			found[i] = shape;
		if (shape)
			ol->colourCount += ((Model *)shape)->colourCount;
	}
	ol->blockSize = (ol->count * 25 + ol->frameCount) * 4;
	if (ol->preLit == 1)
		ol->blockSize += ol->colourCount * 4;
	if (!mem) {
		ol->block = operator_new(((u32)ol->blockSize));
		if (!ol->block)
			sys_fatalError((char *)OBJ(g_logUnit), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), ol->blockSize);
		ol->ownsBlock = 1;
	} else {
		if (size < ol->blockSize)
			sys_fatalErrorN((char *)OBJ(g_logUnit), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), ol->blockSize, size);
		ol->block = mem;
	}
	ol->entries = (ListedObject *)ol->block;
	int colours = ol->count * 100;
	u32 *entry = (u32 *)ol->entries;
	for (int i = 0; i < ol->count; i++, entry += 25) {
		entry[0] = i < 64 ? found[i] : shape_getByName(shapes, (const char *)names + i * 0x44, 0);
		entry[1] = AT(u32, names, i * 0x44 + 0x40);
		if (ol->preLit == 1 && entry[0]) {
			entry[2] = (u32)(ol->block + colours);
			colours += ((const Model *)RELOC(entry[0]))->colourCount * 4;
		} else
			entry[2] = 0;
	}
	ol->frames = (i32 *)(ol->block + colours);
	for (int j = 0; j < ol->frameCount; j++)
		AT(void *, ol->frames, j * 4) = skel_getSkeletonPtrBy(skels, (u32)(knames + j * 0x40));
	if (ol->preLit == 1)
		ObjectList_relight(list, factors, lights);
}

/* the key for frame among a bone's n keys (size bytes each, their first dword the frame they start at): the last one
   starting at or before it (a binary search); a frame before the first key is moved up to it */
static u8 *key_at(u8 *keys, int n, int size, int *frame)
{
#define KEY_FRAME(p) (((const PosKey *)RELOC(p))->frame)   /* (PosKey and RotKey both start with it) */
	int lo = 0;
	if (*frame < KEY_FRAME(keys))
		*frame = KEY_FRAME(keys);
	else
		for (int hi = n - 1; lo < hi;) {
			int mid = (hi + lo + 1) / 2;
			if (*frame < KEY_FRAME(keys + mid * size))
				hi = mid - 1;
			else
				lo = mid;
		}
	return keys + lo * size;
#undef KEY_FRAME
}

/* does the FPU compare v with 0 as equal (as fcomp's C3 says: also for a NaN)? */
static int zero_or_nan(float v)
{
	return !(v < 0) && !(v > 0);
}

/* glRotatef by angle (rounded to a float) about axis (its x through the FPU, y and z as their bits), unless the
   axis is all zero (or NaN) */
static void rotate(long double angle, const float *axis)
{
	if (zero_or_nan(axis[0]) && zero_or_nan(axis[1]) && zero_or_nan(axis[2]))
		return;
	float a = f32(angle), x = f32(fld_m(&axis[0]));
	u32 abits, xbits;
	memcpy(&abits, &a, 4);
	memcpy(&xbits, &x, 4);
	glRotatef_bits(abits, xbits, ((const u32 *)axis)[1], ((const u32 *)axis)[2]);
}

/* 0x46ab30 (thiscall on a skeleton): bone's matrix at time t (0 .. 1 of the +0x20 frames) into out, worked out on
   the GL modelview matrix (saved, then put back): the identity, then the position (the bone's +0x44, or its keys
   from +0x64, +0x60 of them, 0x20 bytes: base +8 and delta +0x14 over the key's length +4), then the rotation (the
   angle +0x50 in 0x4aa270 units about +0x54; or its keys from +0x6c, +0x68 of them, 0x28 bytes: a base rotation
   +8 about +0xc and a delta +0x18 about +0x1c). A bone past the count (+0x10) gets the identity. Its callers ignore
   the eax it leaves */
void THISCALL (skel_applyPose)(u8 *sk, u32 *out, int bone, float t)
{
	Skeleton *sko = (Skeleton *)sk;
	if (bone >= sko->boneCount) {
		for (int k = 0; k < 16; k++)
			out[k] = k % 5 == 0 ? 0x3f800000 : 0;   /* 1.0 on the diagonal */
		return;
	}
	const float *unit = k_57_2958f;
	float saved[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	int frames = sko->frames;
	int frame = ftol(fmul_m(frames, &t));
	if (frame < 0)
		frame = 0;
	else if (frame >= frames)
		frame = frames;
	glLoadIdentity();
	u8 *b = sko->bones + bone * 0x70;
	Bone *bn = (Bone *)b;
	if (bn->posKeyCount > 0) {
		float *key = (float *)key_at(bn->posKeys, bn->posKeyCount, 0x20, &frame);
		int length = ((int *)key)[1];
		long double f = length > 0 ? (long double)(frame - ((int *)key)[0]) / length : fld_m((const float *)ADDR(k_0f));
		glTranslatef(fadd_m(fmul_m(f, &key[5]), &key[2]), fadd_m(fmul_m(f, &key[6]), &key[3]), fadd_m(fmul_m(f, &key[7]), &key[4]));
	} else
		glTranslatef_bits(BITS(((Bone *)b)->pos[0]), BITS(((Bone *)b)->pos[1]), BITS(((Bone *)b)->pos[2]));
	if (bn->rotKeyCount > 0) {
		RotKey *key = (RotKey *)key_at(bn->rotKeys, bn->rotKeyCount, 0x28, &frame);
		int length = key->length;
		float f = length > 0 ? f32((long double)(frame - key->frame) / length) : 0;
		rotate(fmul_m(fld_m(&key->rotation[0]), unit), &key->rotation[1]);
		rotate(fmul_m(fmul_m(fld_m(&f), &key->step[0]), unit), &key->step[1]);
	} else
		rotate(fmul_m(fld_m(&bn->rotation[0]), unit), &bn->rotation[1]);
	glGetFloatv(0xba6, (float *)out);
	glLoadMatrixf(saved);
}

/* A cache's name tree: 0x4c-byte nodes from +0x118 (the name, its item's index +0x40, left +0x44 and right +0x48 by
   strcmp), +0x120 of them (at most +0x114: none, or full, a fatal message out / no_room, full). The index of key's
   node; a missing one is added (index the count, *added set; the caller loads the item and counts it) */
static int tree_lookup(u8 *cache, const char *key, char *out, u32 no_room, u32 full, int *added)
{
	Manager *mg = (Manager *)cache;
	*added = 0;
	if (mg->capacity == 0)
		sys_fatalErrorN(out, (const char *)RELOC(no_room));
	u8 *nodes = mg->nodes, *node = nodes;
	u8 **link = NULL;
	if (mg->count != 0)
		for (;;) {
			int c = strcmp(key, (const char *)node);
			if (c == 0)
				return ((TreeNode *)node)->index;
			link = (u8 **)(node + (c < 0 ? 0x44 : 0x48));
			if (!*link)
				break;
			node = *link;
		}
	int i = mg->count;
	if (link) {
		if (i >= mg->capacity)
			sys_fatalError(out, (const char *)RELOC(full), i);
		i = mg->count;
		*link = node = mg->nodes + i * 0x4c;
	}
	strcpy((char *)node, key);
	((TreeNode *)node)->index = link ? i : 0;
	((TreeNode *)node)->left = ((TreeNode *)node)->right = 0;
	*added = 1;
	return i;
}

/* an item's file path: "dir\name.ext" with the cache's directory (+0x10), or "name.ext"; the extension by the cache's
   format (+0x110: 0 or 1, another a fatal message) */
static void item_path(char *path, u8 *cache, const char *name, u32 ext0, u32 ext1, char *out, u32 bad)
{
	Manager *mg = (Manager *)cache;
	char ext[4];
	int format = ((int)mg->setupArg);
	if (format == 0 || format == 1)
		strcpy(ext, (const char *)(RELOC(format) ? ext1 : ext0));
	else
		sys_fatalError(out, (const char *)RELOC(bad), format);
	if (mg->dir[0])
		sprintf(path, (const char *)STR(0x4c4d5c, "%s\\%s.%s"), mg->dir, name, ext);
	else
		sprintf(path, (const char *)STR(0x4c4d54, "%s.%s"), name, ext);
}

/* 0x46b1a0 (thiscall on a skeleton cache): the skeleton named name (upper-cased; empty or starting with '.': none,
   0), found in the cache's name tree or added to it (tree_lookup) and loaded into skeleton i (0x24 bytes each from
   +0x11c): from the skeleton dat (format +0x110 2: its item's file, skel_loadFromFile) or a "ske" / "ase" file
   (skel_loadFrom), into the cache's data memory when it has one (+0x128, its size +0x124, +0x12c used: the
   skeleton's size added) */
u8 *THISCALL (skel_getSkeletonPtrBy)(u8 *cache, const char *name)
{
	Manager *mg = (Manager *)cache;
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, (char *)OBJ(g_logSkeletonManager), STR(0x4c5528, "sizeOfSkeletonBuffer is zero-getSkele..."), STR(0x4c54c8, "skeleton overflow(%d)-getSkeletonPtrBy()"), &added);
	u8 *sk = mg->items + i * 0x24;
	if (!added)
		return sk;
	const char *own = (const char *)mg->nodes + i * 0x4c;
	u8 *mem = mg->data;
	void *at = mem ? mem + mg->dataUsed : NULL;
	int room = mem ? mg->dataSize - mg->dataUsed : 0;
	if (((int)mg->setupArg) == 2)
		skel_loadFromFile(sk, skelDat_getItemFileBy(key), at, room);
	else {
		char path[0x100];
		item_path(path, cache, own, STR(0x4c54f4, "ske"), STR(0x4c54f8, "ase"), (char *)OBJ(g_logSkeletonManager), STR(0x4c54fc, "invalid file format(%s)-getSkeletonPt..."));
		skel_loadFrom(sk, path, at, room);
	}
	if (mem)
		mg->dataUsed += ((Skeleton *)sk)->blockSize;
	mg->count++;
	return sk;
}

/* 0x466dc0 (thiscall on a shape cache): the shape named name, as skel_getSkeletonPtrBy does it for skeletons: shape
   i (0x4c bytes each from +0x11c) loaded from the shape dat (shape_findDatEntry, shape_read) or a "shp" / "obj" file
   (model_loadFrom), its textures looked up (shape_bindTextureBy with the cache's texture sets +0x130 and seven values
   +0x230 ..); bound (shape_bindPartTextures) when bind is 1, found or added */
u8 *THISCALL (shape_getByName)(u8 *cache, const char *name, int bind)
{
	Manager *mg = (Manager *)cache;
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, (char *)OBJ(g_logShapeManager), STR(0x4c4d98, "sizeOfShapeBuffer is zero-getShapePtr..."), STR(0x4c4d30, "shape overflow(%d)-getShapePtrBy()"), &added);
	u8 *shape = mg->items + i * 0x4c;
	Model *md = (Model *)shape;
	if (added) {
		const char *own = (const char *)mg->nodes + i * 0x4c;
		u8 *mem = mg->data;
		void *at = mem ? mem + mg->dataUsed : NULL;
		int room = mem ? mg->dataSize - mg->dataUsed : 0;
		if (((int)mg->setupArg) == 2)
			/* (the original's first of its four copies of this pair: the patch DLL retargets all four, for the KYRIE models) */
			PATCHED_THISCALL(0x466eb8, void, void *, void *, void *, int)(shape, PATCHED_CALL(0x466ea9, void *, const char *)(key), at, room);   /* shape_read (shape_findDatEntry) */
		else {
			char path[0x100];
			item_path(path, cache, own, STR(0x4c4d68, "shp"), STR(0x4c4d6c, "obj"), (char *)OBJ(g_logShapeManager), STR(0x4c4d70, "invalid file format(%s)-getShapePtrBy()"));
			model_loadFrom(shape, path, at, room);
		}
		if (mem)
			mg->dataUsed += md->blockSize;
		shape_bindTextureBy(shape, mg->textureDir, mg->bindFlags, mg->tint[0], mg->tint[1],
		                    mg->tint[2], mg->tint[3], mg->tint[4], mg->tint[5]);
		mg->count++;
	}
	if (bind == 1)
		shape_bindPartTextures(shape);
	return shape;
}

/* 0x466120 (thiscall on a shape): read from f. Its old data released (Model_release), the 0x34-byte header (block size
   +4, part count +0x10, a point +0x20, the version +0x30: 0x71110300 the current format; an older file has a 0x30-byte
   header and 0x68-byte parts, its block grown by 0x18 a part, the position put back as it was), the block (+8, as
   take_block). The 0x80-byte parts (+0x14) at the block's start, then each part's tables after them: vertices,
   normals (12 bytes each), colours (4), texture coordinates (8) for its +0x4c vertices, and its +0x60 primitives
   (12 bytes; one slot more is left past them), each with its index list (+4 of them). An old file is relocated
   (shape_relocate). The shape's box (+0x34 low, +0x40 high) from the point +0x20 and every part's box (+0x68 ..). Its
   callers ignore the eax it leaves */
void THISCALL (shape_read)(u8 *shape, void *f, void *mem, int size)
{
	Model *md = (Model *)shape;
	Model_release(shape);
	crt_fread(shape, 0x34, 1, f);
	int current = md->version == 0x71110300;
	if (!current) {
		long at = crt_ftell(f);
		crt_fseek(f, -4, 1);   /* SEEK_CUR */
		md->blockSize += md->partCount * 0x18;
		crt_fseek(f, at, 0);   /* SEEK_SET */
	}
	take_block(shape, mem, size, (char *)OBJ(g_logShape), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *parts = md->parts = md->block;
	if (current)
		crt_fread(parts, 0x80, ((u32)md->partCount), f);
	else
		for (int i = 0; i < md->partCount; i++)
			crt_fread(md->parts + i * 0x80, 0x68, 1, f);
	int at = md->partCount * 0x80;
	for (int i = 0; i < md->partCount; i++) {
		u8 *p = md->parts + i * 0x80;
		ShapePart *sp = (ShapePart *)p;
		sp->texture = -1;
		int n = sp->vertexCount;
		static const u8 sizes[4] = { 12, 12, 4, 8 };   /* vertices, normals, colours, texture coordinates */
		u8 **arrays[4] = { &sp->vertices, &sp->normals, &sp->colours, (u8 **)&sp->texCoords };
		for (int t = 0; t < 4; t++) {
			*arrays[t] = md->block + at;
			at += n * sizes[t];
		}
		for (int t = 0; t < 4; t++)
			crt_fread(*arrays[t], sizes[t], ((u32)sp->vertexCount), f);
		sp->prims = md->block + at;
		crt_fread(sp->prims, 0xc, ((u32)sp->primCount), f);
		at += 0xc;
		for (int k = 0; k < sp->primCount; k++) {
			ShapePrim *prim = (ShapePrim *)(sp->prims + k * 0xc);
			prim->indices = md->block + at;
			crt_fread(prim->indices, 4, ((u32)prim->indexCount), f);
			at += prim->indexCount * 4;
		}
	}
	if (!current)
		shape_relocate(shape);
	memcpy(md->low, md->centre, 12);
	memcpy(md->high, md->centre, 12);
	float *low = md->low, *high = md->high;
	for (int i = 0; i < md->partCount; i++) {
		const float *box = (const float *)(md->parts + i * 0x80 + 0x68);
		for (int c = 0; c < 3; c++)
			if (low[c] > box[c])
				((u32 *)low)[c] = ((const u32 *)box)[c];
		for (int c = 0; c < 3; c++)
			if (!(high[c] >= box[3 + c]))
				((u32 *)high)[c] = ((const u32 *)box)[3 + c];
	}
}

/* point p (x, y, z; at stride step) through the 4 x 4 matrix m (column-major), each row summed as the original does:
   z and y terms first, then x, then the translation */
static void transform(float *out, const float *m, const float *px, const float *py, const float *pz)
{
	for (int r = 0; r < 3; r++)
		out[r] = f32(fadd_m(fmul_m(fld_m(pz), &m[8 + r]) + fmul_m(fld_m(py), &m[4 + r]) + fmul_m(fld_m(px), &m[r]), &m[12 + r]));
}

/* 0x46f8c0 (thiscall on an object's skeleton pose): its skeleton (the pointer at +0x20, entry +0x24; none: nothing)
   posed at frame +0x28 (modulo the skeleton's frames +0x20 + 1) for each of its bones (0x70 bytes from its +0x14;
   at most the object's +0x10): on the GL modelview matrix (saved and put back) the parent bone's matrix is loaded
   (its record +0xc; none: base, or the matrix there was), the position translated (the bone's +0x44, or its keys as
   in skel_applyPose; times the bone record's scale +4), the rotation as in skel_applyPose; the result read back
   into the bone's 0x64-byte record (+0xc), with two points carried through it: 0xa0e7a8 (to +0x4c) and the record's
   own point (+0, its +0x20 ..; none: the first again, to +0x58). Its callers ignore the eax it leaves */
void THISCALL (skel_poseBones)(u8 *pose, const float *base)
{
	ObjectList *ol = (ObjectList *)pose;
	if (ol->frameCount <= 0)
		return;
	float saved[16], root[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	Mat4_copy(root, base ? base : saved);
	u8 **entry = ((u8 **)ol->frames) + ol->frame;
	if (!*entry)
		return;
	const float *unit = k_57_2958f, *point = (const float *)ADDR(g_vecOrigin);
	for (int i = 0; i < ol->count; i++) {
		Skeleton *sk = (Skeleton *)(*entry);
		ListedObject *out = (ListedObject *)(((u8 *)ol->entries) + i * 0x64);
		u8 *b = sk->bones + i * 0x70;
		Bone *bn = (Bone *)b;
		int frame = ol->animTick % (sk->frames + 1);
		if (i >= sk->boneCount)
			break;
		int parent = bn->parent;
		glLoadMatrixf(parent < 0 ? root : (const float *)(((u8 *)ol->entries) + parent * 0x64 + 0xc));
		const float *scale = &out->scale;
		if (bn->posKeyCount > 0) {
			int at = frame;
			PosKey *key = (PosKey *)key_at(bn->posKeys, bn->posKeyCount, 0x20, &at);
			int length = key->length;
			long double f = length > 0 ? (long double)(at - key->frame) / length : fld_m((const float *)ADDR(k_0f));
			glTranslatef(fmul_m(fadd_m(fmul_m(f, &key->delta[0]), &key->pos[0]), scale), fmul_m(fadd_m(fmul_m(f, &key->delta[1]), &key->pos[1]), scale),
			             fmul_m(fadd_m(fmul_m(f, &key->delta[2]), &key->pos[2]), scale));
		} else
			glTranslatef(fmul_m(fld_m(&bn->pos[0]), scale), fmul_m(fld_m(&bn->pos[1]), scale),
			             fmul_m(fld_m(&bn->pos[2]), scale));
		if (bn->rotKeyCount > 0) {
			int at = frame;
			RotKey *key = (RotKey *)key_at(bn->rotKeys, bn->rotKeyCount, 0x28, &at);
			int length = key->length;
			float f = length > 0 ? f32((long double)(at - key->frame) / length) : 0;
			rotate(fmul_m(fld_m(&key->rotation[0]), unit), &key->rotation[1]);
			rotate(fmul_m(fmul_m(fld_m(&f), &key->step[0]), unit), &key->step[1]);
		} else
			rotate(fmul_m(fld_m(&bn->rotation[0]), unit), &bn->rotation[1]);
		float *m = out->matrix;
		glGetFloatv(0xba6, m);
		transform(out->pos, m, &point[0], &point[1], &point[2]);
		const Model *own = out->shape;
		if (own) {
			for (int r = 0; r < 3; r++)   /* (here the z, x, y terms in that order for the y and z rows) */
				out->centre[r] = r == 0
					? f32(fadd_m(fmul_m(fld_m(&m[8]), &own->centre[2]) + fmul_m(fld_m(&m[4]), &own->centre[1]) + fmul_m(fld_m(&m[0]), &own->centre[0]), &m[12]))
					: f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &own->centre[2]) + fmul_m(fld_m(&m[r]), &own->centre[0]) + fmul_m(fld_m(&m[4 + r]), &own->centre[1]), &m[12 + r]));
		} else
			memcpy(out->centre, out->pos, 12);
	}
	glLoadMatrixf(saved);
}

#define crt_fgets(line, n, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, n, f)
#define TOKEN(delims) crt_strtok(NULL, (const char *)RELOC(delims))
#define SPACE STR(0x4ad5dc, " \t")
#define LINE_END STR(0x4b4310, " \t\n")

/* the next number of the line as a float (atof's double rounded), negated or not */
static float ase_float(u32 delims, int negate)
{
	long double v = crt_atof(TOKEN(delims));
	return f32(negate ? -v : v);
}

/* a key's time: its tick over the ticks per frame, times the milliseconds per frame */
static int ase_time(int ticks, int ms)
{
	return crt_atoi(TOKEN(SPACE)) / ticks * ms;
}

/* a 4 x 4 translation by p (its floats loaded and stored as the original does) */
static void translation(float *m, const float *p)
{
	memset(m, 0, 64);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
	for (int k = 0; k < 3; k++)
		m[12 + k] = f32(fld_m(&p[k]));
}

/* 0x469b90 (thiscall on a skeleton): a skeleton from a 3ds Max ASE text file. The old one released
   (Skeleton_release); pass 1 counts GEOMOBJECTs (bones, 0x70 bytes), TCB / Bezier position keys (0x20) and TCB rotation
   keys (0x28) and takes the data memory (allocated, +0xc 1; or given: too small is fatal); pass 2 (from the top)
   reads SCENE_LASTFRAME / FRAMESPEED (+0x20 the length in ms) / TICKSPERFRAME, and per bone (cameras skipped) its
   NODE_NAME, NODE_PARENT (among the earlier bones; missing is fatal), TM_POS / TM_ROTAXIS / TM_ROTANGLE (y and z
   swapped, z and the angle negated) and its key lists (each rotation key composed onto the previous one). Then the
   bones become relative to their parents (last first) and the keys get their spans and deltas. Its caller ignores
   the eax it leaves */
void THISCALL (skel_loadAseFrom)(u8 *sk, void *f, u8 *mem, int memSize)
{
	Skeleton *sko = (Skeleton *)sk;
	char line[0x100], parent[0x40];
	Skeleton_release(sk);
	sko->boneCount = ((Skeleton *)sk)->rotKeyTotal = ((Skeleton *)sk)->posKeyTotal = 0;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, (const char *)STR(0x4c5498, "* \t"));
		if (!strcmp(t, (const char *)STR(0x4c548c, "GEOMOBJECT")))
			sko->boneCount++;
		else if (!strcmp(t, (const char *)STR(0x4c5478, "CONTROL_TCB_POS_KEY")) || !strcmp(t, (const char *)STR(0x4c5460, "CONTROL_BEZIER_POS_KEY")))
			((Skeleton *)sk)->posKeyTotal++;
		else if (!strcmp(t, (const char *)STR(0x4c544c, "CONTROL_TCB_ROT_KEY")))
			((Skeleton *)sk)->rotKeyTotal++;
	}
	int bones = sko->boneCount;
	if (bones <= 0)
		return;
	int size = sko->blockSize = bones * 0x70 + ((Skeleton *)sk)->rotKeyTotal * 0x28 + ((Skeleton *)sk)->posKeyTotal * 0x20;
	if (!mem) {
		(*(void * *)&((Skeleton *)sk)->block) = operator_new(size);
		if (!(*(void * *)&((Skeleton *)sk)->block))
			sys_fatalError((char *)OBJ(g_logSkeleton), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), sko->blockSize);
		sko->ownsBlock = 1;
	} else {
		if (memSize < size)
			sys_fatalErrorN((char *)OBJ(g_logSkeleton), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), size, memSize);
		((Skeleton *)sk)->block = mem;
		sko->ownsBlock = 0;
	}
	sko->bones = ((Skeleton *)sk)->block;
	int keys = sko->boneCount * 0x70;   /* where the next key list goes, after the bones */
	crt_fseek(f, 0, 0);
	int frames = 0, ms = 0x21, ticks = 0xa0, skip = -1, index = -1, at = -0x70;
	u8 *b = NULL;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, (const char *)STR(0x4c5498, "* \t"));
		if (!strcmp(t, (const char *)STR(0x4c543c, "SCENE_LASTFRAME")))   /* SCENE_LASTFRAME */
			frames = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, (const char *)STR(0x4c541c, "SCENE_FRAMESPEED"))) {   /* SCENE_FRAMESPEED */
			ms = 1000 / crt_atoi(TOKEN(LINE_END));
			sko->frames = ms * frames;
		} else if (!strcmp(t, (const char *)STR(0x4c5408, "SCENE_TICKSPERFRAME")))   /* SCENE_TICKSPERFRAME */
			ticks = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, (const char *)STR(0x4c548c, "GEOMOBJECT"))) {   /* GEOMOBJECT */
			index++;
			skip = 0;
			at += 0x70;
			b = sko->bones + at;
			((Bone *)b)->parent = -1;
			((Bone *)b)->posKeyCount = (*(int *)&((Bone *)b)->posKeys) = ((Bone *)b)->rotKeyCount = (*(int *)&((Bone *)b)->rotKeys) = 0;
		} else if (!strcmp(t, (const char *)STR(0x4c53f8, "CAMERAOBJECT"))) {   /* CAMERAOBJECT */
			skip = 1;
			continue;
		}
		if (skip)
			continue;
		if (!strcmp(t, (const char *)STR(0x4c5430, "NODE_NAME")))   /* NODE_NAME */
			strcpy((char *)RELOC(b), TOKEN(STR(0x4c53f4, "\"")));
		else if (!strcmp(t, (const char *)STR(0x4c53e8, "NODE_PARENT"))) {   /* NODE_PARENT */
			strcpy(parent, TOKEN(STR(0x4c53f4, "\"")));
			if (at > 0)
				for (int j = 0; j < index; j++)
					if (!strcmp((const char *)sko->bones + j * 0x70, parent)) {
						((Bone *)b)->parent = j;
						break;
					}
			if (((Bone *)b)->parent < 0)
				sys_fatalError((char *)OBJ(g_logSkeleton), (const char *)STR(0x4c53b8, "can't find parent part(%s)-loadAseFor..."), (int)parent);
		} else if (!strcmp(t, (const char *)STR(0x4c53b0, "TM_POS"))) {   /* TM_POS */
			((Bone *)b)->pos[0] = ase_float(SPACE, 0);
			((Bone *)b)->pos[2] = ase_float(SPACE, 1);
			((Bone *)b)->pos[1] = ase_float(LINE_END, 0);
		} else if (!strcmp(t, (const char *)STR(0x4c53a4, "TM_ROTAXIS"))) {   /* TM_ROTAXIS */
			((Bone *)b)->rotation[1] = ase_float(SPACE, 0);
			((Bone *)b)->rotation[3] = ase_float(SPACE, 1);
			((Bone *)b)->rotation[2] = ase_float(LINE_END, 0);
		} else if (!strcmp(t, (const char *)STR(0x4c5398, "TM_ROTANGLE")))   /* TM_ROTANGLE */
			((Bone *)b)->rotation[0] = ase_float(LINE_END, 1);
		else if (!strcmp(t, (const char *)STR(0x4c5388, "CONTROL_POS_TCB")) || !strcmp(t, (const char *)STR(0x4c5374, "CONTROL_POS_BEZIER"))) {   /* CONTROL_POS_TCB / _BEZIER */
			((Bone *)b)->posKeys = ((Skeleton *)sk)->block + keys;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, (const char *)STR(0x4c535c, "* \t\n"));
				if (!strcmp(t, (const char *)STR(0x4c5478, "CONTROL_TCB_POS_KEY")) || !strcmp(t, (const char *)STR(0x4c5460, "CONTROL_BEZIER_POS_KEY"))) {
					PosKey *k = (PosKey *)(((Bone *)b)->posKeys + ((Bone *)b)->posKeyCount * 0x20);
					k->frame = ase_time(ticks, ms);
					k->pos[0] = ase_float(SPACE, 0);
					k->pos[2] = ase_float(SPACE, 1);
					k->pos[1] = ase_float(SPACE, 0);
					((Bone *)b)->posKeyCount++;
				} else if (t && t[0] == '}')
					break;
			}
			keys += ((Bone *)b)->posKeyCount * 0x20;
		} else if (!strcmp(t, (const char *)STR(0x4c5364, "CONTROL_ROT_TCB"))) {   /* CONTROL_ROT_TCB */
			((Bone *)b)->rotKeys = ((Skeleton *)sk)->block + keys;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, (const char *)STR(0x4c535c, "* \t\n"));
				if (!strcmp(t, (const char *)STR(0x4c544c, "CONTROL_TCB_ROT_KEY"))) {
					u8 *k = ((Bone *)b)->rotKeys + ((Bone *)b)->rotKeyCount * 0x28;
					((RotKey *)k)->frame = ase_time(ticks, ms);
					((RotKey *)k)->rotation[1] = ase_float(SPACE, 0);
					((RotKey *)k)->rotation[3] = ase_float(SPACE, 1);
					((RotKey *)k)->rotation[2] = ase_float(SPACE, 0);
					((RotKey *)k)->rotation[0] = ase_float(SPACE, 1);
					if (((Bone *)b)->rotKeyCount > 0) {
						float r[4];
						axisAngle_combine(r, (const float *)(RELOC(k) + 8), (const float *)(RELOC(k) + 8 - 0x28));
						memcpy(k + 8, r, 16);
					}
					((Bone *)b)->rotKeyCount++;
				} else if (t && t[0] == '}')
					break;
			}
			keys += ((Bone *)b)->rotKeyCount * 0x28;
		}
	}
	u8 *all = ((Skeleton *)sk)->bones;
	for (int i = ((Skeleton *)sk)->boneCount - 1; i >= 0; i--) {
		u8 *bone = all + i * 0x70;
		if (((Bone *)bone)->parent < 0)
			continue;
		u8 *up = all + ((Bone *)bone)->parent * 0x70;
		float t[16], r[16], m[16], inv[16], local[16], rel[16];
		translation(t, ((Bone *)up)->pos);
		Mat4_fromAxisAngle(r, ((Bone *)up)->rotation);
		Mat4_multiply(m, t, r);
		Mat4_invert(inv, m);
		translation(t, ((Bone *)bone)->pos);
		Mat4_fromAxisAngle(r, ((Bone *)bone)->rotation);
		Mat4_multiply(local, t, r);
		Mat4_multiply(rel, inv, local);
		for (int k = 0; k < 3; k++)
			((Bone *)bone)->pos[k] = f32(fld_m(&rel[12 + k]));
		rel[12] = rel[13] = rel[14] = 0;
		axisAngle_fromMatrix(((Bone *)bone)->rotation, rel);
	}
	for (int i = 0; i < ((Skeleton *)sk)->boneCount; i++) {
		u8 *bone = ((Skeleton *)sk)->bones + i * 0x70;
		for (int k = 0; k < ((Bone *)bone)->posKeyCount - 1; k++) {
			u8 *key = ((Bone *)bone)->posKeys + k * 0x20;
			((PosKey *)key)->length = ((PosKey *)key)[1].frame - ((PosKey *)key)->frame;
			for (int c = 0; c < 3; c++)
				((PosKey *)key)->delta[c] = f32(fsub_m(fld_m(&((PosKey *)key)[1].pos[c]), &((PosKey *)key)->pos[c]));
		}
		if (((Bone *)bone)->posKeyCount > 0) {
			u8 *last = ((Bone *)bone)->posKeys + (((Bone *)bone)->posKeyCount - 1) * 0x20;
			((PosKey *)last)->length = 0;
			BITS(((PosKey *)last)->delta[0]) = BITS(((PosKey *)last)->delta[1]) = BITS(((PosKey *)last)->delta[2]) = 0;
		}
		for (int k = 0; k < ((Bone *)bone)->rotKeyCount - 1; k++) {
			u8 *key = ((Bone *)bone)->rotKeys + k * 0x28;
			((RotKey *)key)->length = ((RotKey *)key)[1].frame - ((RotKey *)key)->frame;
			float r[16], back[16], next[16], step[16];
			Mat4_fromAxisAngle(r, ((RotKey *)key)->rotation);
			Mat4_transpose(back, r);
			Mat4_fromAxisAngle(next, ((RotKey *)key)[1].rotation);
			Mat4_multiply(step, back, next);
			axisAngle_fromMatrix(((RotKey *)key)->step, step);
		}
		if (((Bone *)bone)->rotKeyCount > 0) {
			u8 *last = ((Bone *)bone)->rotKeys + (((Bone *)bone)->rotKeyCount - 1) * 0x28;
			((RotKey *)last)->length = 0;
			BITS(((RotKey *)last)->step[0]) = BITS(((RotKey *)last)->step[1]) = BITS(((RotKey *)last)->step[2]) = BITS(((RotKey *)last)->step[3]) = 0;
		}
	}
}
#undef crt_fgets
#undef TOKEN
#undef SPACE
#undef LINE_END

#define crt_fgets(line, n, f) GAME_CDECL(0x49ecd7, char *, char *, int, void *)(line, n, f)
#define TOK(s, delims) crt_strtok(s, (const char *)RELOC(delims))
#define SPACE STR(0x4ad5dc, " \t")
#define LINE_END STR(0x4b4310, " \t\n")
#define SLASH STR(0x4ad564, "/")
#define BAD_OBJ() sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4c20, "invalid obj format string(%s)-loadObj..."), (int)line)

/* a face's first corner token: a lone "\" continues the face on the next line */
static char *face_start(char *line, void *f)
{
	char *t = TOK(NULL, LINE_END);
	if (!strcmp(t, (const char *)STR(0x4b1328, "\\"))) {
		crt_fgets(line, 0x100, f);
		t = TOK(line, LINE_END);
	}
	return t;
}

/* corner "v[/a[/b]]" into part corner i: its position (v), and with a: texture a and normal b, or (no b) no
   texture and normal a. Returns 0 when it is a bare position */
static int obj_corner(u8 *part, int i, char *corner, const float *vs, const float *ns, const float *ts)
{
	ShapePart *sp = (ShapePart *)part;
	memcpy(sp->vertices + i * 12, vs + (crt_atoi(TOK(corner, SLASH)) - 1) * 3, 12);
	char *a = TOK(NULL, SLASH);
	if (!a)
		return 0;
	int ai = crt_atoi(a) - 1;
	char *b = TOK(NULL, SLASH);
	float *uv = sp->texCoords + i * 2;
	if (!b) {
		BITS(uv[0]) = BITS(uv[1]) = 0;
		memcpy(sp->normals + i * 12, ns + ai * 3, 12);
	} else {
		memcpy(uv, ts + ai * 2, 8);
		memcpy(sp->normals + i * 12, ns + (crt_atoi(b) - 1) * 3, 12);
	}
	return 1;
}

/* 0x464db0 (thiscall on a shape): a shape from a Wavefront OBJ text file. The old one released (Model_release);
   pass 1 counts the parts (usemtl), positions (v), normals (vn), texture coordinates (vt) and the corners of the
   faces (+0x18: a face of 3 or 4 corners, 3 or 6; fewer are fatal; +0x1c triangles); the data memory is taken
   (allocated with three temporary arrays, or given: too small is fatal); pass 2 counts each part's corners and lays
   out its arrays and its one triangle list; pass 3 reads the values, names the parts after the last "_" piece of
   the material (its last character cut) and expands the faces into corners (bare positions get a flat normal). A
   "3DS" comment flips y / z (the original's loop over that never moves on: a part with corners hangs it). Then the
   colours, the temporaries freed, the parts' bounds (shape_relocate) and the shape's. As the original, a quad's
   second triangle copies its corners into the temporary arrays rather than the part's. Its caller ignores the eax
   it leaves */
void THISCALL (model_loadObjFormatFrom)(u8 *sh, void *f, u8 *mem, int memSize)
{
	Model *md = (Model *)sh;
	char line[0x100], last[0x100], c[4][0x20];
	int nv = 0, nvn = 0, nvt = 0;
	Model_release(sh);
	md->partCount = 0;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, (const char *)STR(0x4c4c64, "usemtl")))
			md->partCount++;
		else if (!strcmp(t, (const char *)STR(0x4c4c60, "v")))
			nv++;
		else if (!strcmp(t, (const char *)STR(0x4c4c5c, "vn")))
			nvn++;
		else if (!strcmp(t, (const char *)STR(0x4c4c58, "vt")))
			nvt++;
		else if (!strcmp(t, (const char *)STR(0x4c4c54, "f"))) {
			if (!face_start(line, f))
				BAD_OBJ();
			for (int k = 0; k < 2; k++)
				if (!TOK(NULL, LINE_END))
					BAD_OBJ();
			if (!TOK(NULL, LINE_END)) {
				md->colourCount += 3;
				md->triangleCount += 1;
			} else {
				md->colourCount += 6;
				md->triangleCount += 2;
			}
		}
	}
	int parts = md->partCount;
	if (parts <= 0)
		return;
	int size = md->blockSize = (md->colourCount * 3 + md->triangleCount) * 0xc + parts * 0x8c;
	float *vs, *ns, *ts;
	int allocated;
	if (!mem) {
		(*(void * *)&md->block) = operator_new(size);
		if (!(*(void * *)&md->block))
			sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), md->blockSize);
		md->ownsBlock = 1;
		if (!(vs = operator_new(nv * 12)))
			sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4bb4, "insufficient memory for vertexCoordAr..."), nv);
		if (!(ns = operator_new(nvn * 12)))
			sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4b78, "insufficient memory for vertexNormalA..."), nvn);
		if (!(ts = operator_new(nvt * 8)))
			sys_fatalError((char *)OBJ(g_logShape), (const char *)STR(0x4c4b38, "insufficient memory for vertexTexture..."), nvt);
		allocated = 1;
	} else {
		int need = nvt * 8 + (nvn + nv) * 0xc + size;
		if (memSize < need)
			sys_fatalErrorN((char *)OBJ(g_logShape), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), need, memSize);
		md->block = mem;
		md->ownsBlock = 0;
		vs = (float *)(mem + md->blockSize);
		ns = (float *)(mem + md->blockSize + nv * 0xc);
		ts = (float *)(mem + md->blockSize + (nvn + nv) * 0xc);
		allocated = 0;
	}
	u8 *all = md->parts = md->block;
	int at = md->partCount << 7;
	for (int k = 0; k < md->partCount; k++) {
		u8 *pt = all + k * 0x80;
		GAME_VAR(int, pt) = 0;
		((ShapePart *)pt)->texture = 0;
		for (int o = 0x4c; o <= 0x64; o += 4)
			GAME_VAR(int, pt + o) = 0;
	}
	crt_fseek(f, 0, 0);
	int off = -0x80;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, (const char *)STR(0x4c4c64, "usemtl"))) {
			off += 0x80;
			GAME_VAR(int, md->parts + 0x60 + off) = 1;
		} else if (!strcmp(t, (const char *)STR(0x4c4c54, "f"))) {
			if (!face_start(line, f))
				BAD_OBJ();
			for (int k = 0; k < 2; k++)
				if (!TOK(NULL, LINE_END))
					BAD_OBJ();
			GAME_VAR(int, md->parts + 0x4c + off) += TOK(NULL, LINE_END) ? 6 : 3;
		}
	}
	int corner = 0;
	for (int k = 0; k < md->partCount; k++) {
		u8 *pt = md->parts + k * 0x80, *data = md->block;
		int n = ((ShapePart *)pt)->vertexCount;
		((ShapePart *)pt)->vertices = data + at;
		at += n * 12;
		((ShapePart *)pt)->normals = data + at;
		at += n * 12;
		((ShapePart *)pt)->colours = data + at;
		at += n * 4;
		((ShapePart *)pt)->colourBase = corner;
		corner += n;
		(*(u8 * *)&((ShapePart *)pt)->texCoords) = data + at;
		at += n * 8;
		((ShapePart *)pt)->primCount = 1;
		u32 *prim = (*(u32 * *)&((ShapePart *)pt)->prims) = (u32 *)(data + at);
		at += 0xc;
		prim[0] = 4;
		prim[1] = ((u32)((ShapePart *)pt)->vertexCount);
		prim[2] = (u32)(md->block + at);
		at += ((ShapePart *)pt)->vertexCount * 4;
	}
	u8 *part = NULL;
	int flip = 0, poff = 0;
	float *vp = vs, *np = ns, *tp = ts;
	crt_fseek(f, 0, 0);
	while (crt_fgets(line, 0x100, f)) {
		int next = corner;
		if (line[0] == '#') {
			const char *q = line + 2, *r;
			do {
				if (!q[-1] || !q[0])
					break;
				if (q[-2] == '3' && q[-1] == 'D' && q[0] == 'S') {
					flip = 1;
					break;
				}
				r = q - 1;
				q++;
			} while (*r);
		} else {
			char *t = TOK(line, SPACE);
			if (!strcmp(t, (const char *)STR(0x4c4c60, "v"))) {
				vp[0] = f32(crt_atof(TOK(NULL, SPACE)));
				vp[1] = f32(crt_atof(TOK(NULL, SPACE)));
				vp[2] = f32(crt_atof(TOK(NULL, LINE_END)));
				vp += 3;
			} else if (!strcmp(t, (const char *)STR(0x4c4c5c, "vn"))) {
				np[0] = f32(crt_atof(TOK(NULL, SPACE)));
				np[1] = f32(crt_atof(TOK(NULL, SPACE)));
				np[2] = f32(crt_atof(TOK(NULL, LINE_END)));
				np += 3;
			} else if (!strcmp(t, (const char *)STR(0x4c4c58, "vt"))) {
				tp[0] = f32(crt_atof(TOK(NULL, SPACE)));
				tp[1] = f32(crt_atof(TOK(NULL, LINE_END)));
				tp += 2;
			} else if (!strcmp(t, (const char *)STR(0x4c4c64, "usemtl"))) {
				part = md->parts + poff;
				poff += 0x80;
				for (char *piece = TOK(NULL, STR(0x4c4b04, "_")); piece; piece = TOK(NULL, STR(0x4c4b04, "_")))
					strcpy(last, piece);
				char *name = TOK(last, LINE_END);
				strcpy((char *)part + 4, name);
				part[(int)strlen(name) + 3] = 0;
				((ShapePart *)part)->texture = -1;
				next = 0;
			} else if (!strcmp(t, (const char *)STR(0x4c4c54, "f"))) {
				strcpy(c[0], face_start(line, f));
				strcpy(c[1], TOK(NULL, LINE_END));
				strcpy(c[2], TOK(NULL, LINE_END));
				char *t4 = TOK(NULL, LINE_END);
				if (t4)
					strcpy(c[3], t4);
				else
					c[3][0] = 0;
				int b = corner;
				float *pv = (*(float * *)&((ShapePart *)part)->vertices), *pn;
				obj_corner(part, b, c[0], vs, ns, ts);
				obj_corner(part, b + 1, c[1], vs, ns, ts);
				if (!obj_corner(part, b + 2, c[2], vs, ns, ts)) {
					float tmp[3];
					pv = (*(float * *)&((ShapePart *)part)->vertices);
					const float *nrm = math_triangleNormal(tmp, pv + b * 3, pv + (b + 1) * 3, pv + (b + 2) * 3);
					pn = (*(float * *)&((ShapePart *)part)->normals);
					memcpy(pn + (b + 2) * 3, nrm, 12);
					memcpy(pn + (b + 1) * 3, pn + (b + 2) * 3, 12);
					memcpy(pn + b * 3, pn + (b + 2) * 3, 12);
				}
				next = b + 3;
				if (c[3][0]) {
					int q = b + 3;
					memcpy(vs + q * 3, vs + (q - 1) * 3, 12);   /* (into the temporaries, as the original) */
					memcpy(ns + q * 3, ns + (q - 1) * 3, 12);
					memcpy(ts + q * 2, ts + (q - 1) * 2, 8);
					memcpy(vs + (b + 5) * 3, vs + b * 3, 12);
					memcpy(ns + (b + 5) * 3, ns + b * 3, 12);
					memcpy(ts + (q + 2) * 2, ts + (q - 3) * 2, 8);
					if (!obj_corner(part, b + 4, c[3], vs, ns, ts)) {
						float tmp[3];
						pv = (*(float * *)&((ShapePart *)part)->vertices);
						const float *nrm = math_triangleNormal(tmp, pv + q * 3, pv + (b + 4) * 3, pv + (b + 5) * 3);
						pn = (*(float * *)&((ShapePart *)part)->normals);
						memcpy(pn + (b + 4) * 3, nrm, 12);
						memcpy(pn + q * 3, pn + (b + 4) * 3, 12);
						memcpy(pn + (b + 5) * 3, pn + (b + 4) * 3, 12);
					}
					next = b + 6;
				}
			}
		}
		corner = next;
	}
	for (int k = 0; k < md->partCount; k++) {
		ShapePart *pt = (ShapePart *)(md->parts + k * 0x80);
		for (int i = 0; i < pt->vertexCount; i++)
			GAME_VAR(u32 *, pt->prims + 8)[i] = i;
	}
	if (flip)
		for (int k = 0; k < md->partCount; k++) {
			ShapePart *pt = (ShapePart *)(md->parts + k * 0x80);
			while (pt->vertexCount > 0) {   /* (never moves on, as the original) */
				k++;
				float *v = (*(float * *)&pt->vertices), *n = (*(float * *)&pt->normals);
				long double y = fld_m(&v[2]);
				v[2] = f32(-fld_m(&v[1]));
				v[1] = f32(y);
				y = fld_m(&n[2]);
				n[2] = f32(-fld_m(&n[1]));
				n[1] = f32(y);
				for (int c3 = 0; c3 < 3; c3++)
					n[c3] = f32(fmul_m(fld_m(&n[c3]), (const float *)ADDR(k_m1f)));
			}
		}
	for (int k = 0; k < md->partCount; k++) {
		ShapePart *pt = (ShapePart *)(md->parts + k * 0x80);
		for (int i = 0; i < pt->vertexCount; i++)
			(*(u32 * *)&pt->colours)[i] = g_white;
	}
	if (allocated == 1) {
		if (nv > 0)
			operator_delete(vs);
		if (nvn > 0)
			operator_delete(ns);
		if (nvt > 0)
			operator_delete(ts);
	}
	shape_relocate(sh);
	memcpy(md->low, md->centre, 12);
	memcpy(md->high, md->centre, 12);
	for (int k = 0; k < md->partCount; k++) {
		ShapePart *pt = (ShapePart *)(md->parts + k * 0x80);
		for (int a = 0; a < 3; a++)   /* (the values copied as bits: a NaN stays as it is) */
			if (fld_m(&md->low[a]) > pt->box[a])
				memcpy(&md->low[a], &pt->box[a], 4);
		for (int a = 0; a < 3; a++)
			if (!(fld_m(&md->high[a]) >= pt->box[3 + a]))
				memcpy(&md->high[a], &pt->box[3 + a], 4);
	}
}
#undef crt_fgets
#undef TOK
#undef SPACE
#undef LINE_END
#undef SLASH
#undef BAD_OBJ
