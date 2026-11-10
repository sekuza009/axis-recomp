/* shapes_skeletons.c: shapes and skeletons: their files read (binary, 3ds Max ASE, Wavefront OBJ), their managers
   (items loaded by name into one block, a name tree), a bone's matrix at a time, and object lists loaded and posed. A
   record's data is one block (allocated, or the caller's memory when it is big enough, else a fatal message). */
#include "../game.h"
#include "../fixes/fixes.h"
#include <string.h>

#define AT(type, p, offset) GAME_VAR(type, AP(u8, RELOC(p)) + (offset))

/* the block (BlockOwner: block, its size blockSize): allocated (owned: ownsBlock 1) without memory given, else the
   memory given (owned 0 when own_flag; the caller's size checked) */
static void take_block(u8 *self, void *mem, int size, char *out, u32 no_memory, u32 too_small, int own_flag)
{
	BlockOwner *bo = (BlockOwner *)self;
	if (!mem) {
		bo->block = AREF(operator_new(bo->blockSize));
		if (!bo->block)
			sys_fatalError(out, AP(const char, RELOC(no_memory)), bo->blockSize);
		bo->ownsBlock = 1;
	} else {
		if (size < bo->blockSize)
			sys_fatalErrorN(out, AP(const char, RELOC(too_small)), bo->blockSize, size);
		bo->block = AREF(mem);
		if (own_flag)
			bo->ownsBlock = 0;
	}
}

/* 0x46aa10 (thiscall on a skeleton): read from f: the 0x24-byte header, the block (+8, its size +4), then the bones
   (0x70 bytes each, boneCount of them, at the block's start: bones) and after them each bone's two tables (posKeyCount keys of
   0x20 bytes at posKeys, rotKeyCount keys of 0x28 bytes at rotKeys). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFromFile)(u8 *self, void *f, void *mem, int size)
{
	Skeleton *sko = (Skeleton *)self;
	Skeleton_release(self);
	crt_fread(self, 0x24, 1, f);
	take_block(self, mem, size, AP(char, OBJ(g_logSkeleton)), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *bones = AP(u8, sko->bones = sko->block);
	crt_fread(bones, 0x70, ((u32)sko->boneCount), f);
	int at = sko->boneCount * 0x70;
	for (int i = 0; i < sko->boneCount; i++) {
		u8 *bone = AP(u8, sko->bones + i * 0x70);
		Bone *bn = (Bone *)bone;
		bn->posKeys = sko->block + at;
		u32 keys = ((u32)bn->posKeyCount);
		at += keys * 0x20;
		bn->rotKeys = sko->block + at;
		at += bn->rotKeyCount * 0x28;
		crt_fread(AGET(void, bn->posKeys), 0x20, keys, f);
		crt_fread(AGET(void, bn->rotKeys), 0x28, ((u32)bn->rotKeyCount), f);
	}
}

/* 0x46aeb0 (thiscall on a skeleton set): set up for n skeletons from the directory dir (dir; none: 0x4b1304), the
   source (where the skeletons load from: 0 / 1 loose files, 2 Skeleton.dat) at source, n at capacity, extra bytes (dataSize) after them: the block (+8, its size n x 0x70 + extra at +4) holds the
   skeletons' 0x4c-byte records (nodes), then their 0x24-byte skeletons (items, each created and released), then the
   rest (data). Its callers ignore the eax it leaves */
void THISCALL (SkeletonManager_initBy)(u8 *self, const char *dir, int n, u32 source, int extra, void *mem, int size)
{
	ShapeManager *mg = (ShapeManager *)self;
	SkeletonManager_release(self);
	strcpy(mg->dir, dir ? dir : AP(const char, STR(0x4b1304, ".")));
	mg->source = source;
	mg->capacity = n;
	mg->dataSize = extra;
	mg->blockSize = n * 0x70 + extra;
	take_block(self, mem, size, AP(char, OBJ(g_logSkeletonManager)), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 0);
	n = mg->capacity;
	mg->nodes = mg->block;
	mg->items = mg->block + n * 0x4c;
	for (int i = 0; i < mg->capacity; i++) {
		Skeleton_clear(AP(void, mg->items + i * 0x24));
		Skeleton_release(AP(void, mg->items + i * 0x24));
	}
	mg->data = mg->block + n * 0x70;
}

/* 0x466a60 (thiscall on a shape set): set up for n shapes from the directory dir (dir, upper-cased; none or
   0x4b1304: empty), the source (where the items load from: 0 / 1 loose files, 2 the packed file) at source, n at capacity, extra bytes (dataSize) after them: the block (+8, its size n x 0x98 +
   extra at +4) holds the shapes' 0x4c-byte records (nodes), then their 0x4c-byte shapes (items, each created and
   released), then the rest (data); the texture-name suffix (textureSuffix) and the bind flags with the tint (bindFlags ..) cleared. Its callers
   ignore the eax it leaves */
void THISCALL (ShapeManager_initBy)(u8 *self, const char *dir, int n, u32 source, int extra, void *mem, int size)
{
	ShapeManager *mg = (ShapeManager *)self;
	ShapeManager_release(self);
	if (dir && strcmp(dir, AP(const char, STR(0x4b1304, "."))) != 0)
		strcpy(mg->dir, dir);
	else
		mg->dir[0] = 0;
	path_normalize(mg->dir);
	mg->source = source;
	mg->capacity = n;
	mg->dataSize = extra;
	mg->blockSize = n * 0x98 + extra;
	take_block(self, mem, size, AP(char, OBJ(g_logShapeManager)), STR(0x4c4cec, "insufficient memory for dataMemory(%d..."), STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -..."), 0);
	n = mg->capacity;
	mg->nodes = mg->block;
	mg->items = mg->block + n * 0x4c;
	for (int i = 0; i < mg->capacity; i++) {
		Shape_clear(AP(void, mg->items + i * 0x4c));
		Shape_release(AP(void, mg->items + i * 0x4c));
	}
	mg->textureSuffix[0] = 0;
	mg->data = mg->block + n * 0x98;
	for (int k = 0; k < 7; k++)
		AT(int, self, offsetof(ShapeManager, bindFlags) + k * 4) = 0;   /* bindFlags, tint */
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
   "shp" the binary format (shape_read), "obj" Wavefront text (shape_readObj), anything else a fatal
   message; the file closed. Its callers ignore the eax it leaves */
void THISCALL (shape_loadFrom)(u8 *shape, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, AP(const char, STR(0x4ad170, "rb")));
	if (!f)
		sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4ae4, "can not read file %s-loadFrom()")), (int)AV(path));
	switch (file_format(path, "shp", "obj")) {
	case 0:
		shape_read(shape, f, mem, size);
		break;
	case 1:
		shape_readObj(shape, f, mem, size);
		break;
	default:
		sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4aa4, "can't figure out what the format of t...")), (int)AV(path));
	}
	fclose(f);
}

/* 0x4699d0 (thiscall on a skeleton): the same for skeletons: "ske" the binary format (skel_loadFromFile), "ase"
   ASCII scene export (skel_loadAseFrom). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom)(u8 *sk, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, AP(const char, STR(0x4ad170, "rb")));
	if (!f)
		sys_fatalError(AP(char, OBJ(g_logSkeleton)), AP(const char, STR(0x4c4ae4, "can not read file %s-loadFrom()")), (int)AV(path));
	switch (file_format(path, "ske", "ase")) {
	case 0:
		skel_loadFromFile(sk, f, mem, size);
		break;
	case 1:
		skel_loadAseFrom(sk, f, mem, size);
		break;
	default:
		sys_fatalError(AP(char, OBJ(g_logSkeleton)), AP(const char, STR(0x4c4aa4, "can't figure out what the format of t...")), (int)AV(path));
	}
	fclose(f);
}

/* 0x46f4e0 (thiscall on an object list): emptied (ObjectList_release), then ns shapes (by the names 0x44 apart, each with
   its bone's translation scale (a float) at +0x40; looked up in the shape cache, the first 64 once, any later ones again when the entries are
   filled) with their element counts summed (colourCount), and nk skeletons (by the names 0x40 apart). Its block (+8, size
   +4: 100 bytes a shape, 4 a skeleton, lit == 1 a colour per element too): allocated (owned, ownsBlock 1; none a fatal
   message) without memory given, else that memory (too small: a fatal message). The entries (entries: shape, int,
   colours when lit and found), the skeletons after them (frames), and lit, the colours worked out (ObjectList_relight). Its
   callers ignore the eax it leaves */
void THISCALL (ObjectList_load)(u8 *list, void *shapes, void *skels, int ns, const u8 *names, int nk, const u8 *knames,
                                     int lit, u32 factors, u32 tint, void *mem, int size)
{
	ObjectList *ol = (ObjectList *)list;
	ObjectList_release(list);
	ol->count = ns;
	ol->skelCount = nk;
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
			ol->colourCount += (AP(Shape, shape))->colourCount;
	}
	ol->blockSize = (ol->count * 25 + ol->skelCount) * 4;
	if (ol->preLit == 1)
		ol->blockSize += ol->colourCount * 4;
	if (!mem) {
		ol->block = AREF(operator_new(((u32)ol->blockSize)));
		if (!ol->block)
			sys_fatalError(AP(char, OBJ(g_logUnit)), AP(const char, STR(0x4c4bec, "insufficient memory for dataMemory(%d...")), ol->blockSize);
		ol->ownsBlock = 1;
	} else {
		if (size < ol->blockSize)
			sys_fatalErrorN(AP(char, OBJ(g_logUnit)), AP(const char, STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l...")), ol->blockSize, size);
		ol->block = AREF(mem);
	}
	ol->entries = AREF(AP(ListedObject, ol->block));
	int colours = ol->count * 100;
	u32 *entry = AP(u32, ol->entries);
	for (int i = 0; i < ol->count; i++, entry += 25) {
		entry[0] = i < 64 ? found[i] : shape_getByName(shapes, (const char *)names + i * 0x44, 0);
		entry[1] = AT(u32, names, i * 0x44 + 0x40);
		if (ol->preLit == 1 && entry[0]) {
			entry[2] = (u32)(ol->block + colours);
			colours += (AP(const Shape, RELOC(entry[0])))->colourCount * 4;
		} else
			entry[2] = 0;
	}
	ol->skeletons = AREF(AP(APTR(struct Skeleton), (ol->block + colours)));
	for (int j = 0; j < ol->skelCount; j++)
		AT(APTR(void), ol->skeletons, j * 4) = AREF(skel_getSkeletonPtrBy(skels, AV((knames + j * 0x40))));
	if (ol->preLit == 1)
		ObjectList_relight(list, factors, tint);
}

/* the key for time (ms) among a bone's n keys (size bytes each, their first dword the time they start at): the last
   one starting at or before it (a binary search); a time before the first key is moved up to it */
static u8 *key_at(u8 *keys, int n, int size, int *time)
{
#define KEY_TIME(p) ((AP(const PosKey, RELOC(p)))->time)   /* (PosKey and RotKey both start with it: ms) */
	int lo = 0;
	if (*time < KEY_TIME(keys))
		*time = KEY_TIME(keys);
	else
		for (int hi = n - 1; lo < hi;) {
			int mid = (hi + lo + 1) / 2;
			if (*time < KEY_TIME(keys + mid * size))
				hi = mid - 1;
			else
				lo = mid;
		}
	return keys + lo * size;
#undef KEY_TIME
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

/* 0x46ab30 (thiscall on a skeleton): bone's matrix at time t (0 .. 1 of the duration) into out, worked out on
   the GL modelview matrix (saved, then put back): the identity, then the position (the bone's pos, or its keys
   from posKeys, posKeyCount of them, 0x20 bytes: base +8 and delta delta over the key's length +4), then the rotation (the
   angle rotation[0] in k_57_2958f units about rotation[1..3]; or its keys from rotKeys, rotKeyCount of them, 0x28 bytes: a base rotation
   +8 about rotation[1..3] and a delta step[0] about step[1..3]). A bone past the count (boneCount) gets the identity. Its callers ignore
   the eax it leaves */
void THISCALL (skel_getBoneMatrix)(u8 *sk, u32 *out, int bone, float t)
{
	Skeleton *sko = (Skeleton *)sk;
	if (bone >= sko->boneCount) {
		for (int k = 0; k < 16; k++)
			out[k] = k % 5 == 0 ? 0x3f800000 : 0;   /* 1.0 on the diagonal */
		return;
	}
	const float *toDegrees = k_57_2958f;
	float saved[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	int duration = sko->duration;
	int animTime = ftol(fmul_m(duration, &t));
	if (animTime < 0)
		animTime = 0;
	else if (animTime >= duration)
		animTime = duration;
	glLoadIdentity();
	u8 *b = AP(u8, sko->bones + bone * 0x70);
	Bone *bn = (Bone *)b;
	if (bn->posKeyCount > 0) {
		float *key = (float *)key_at(AP(u8, bn->posKeys), bn->posKeyCount, 0x20, &animTime);
		int length = ((int *)key)[1];
		long double f = length > 0 ? (long double)(animTime - ((int *)key)[0]) / length : fld_m(AP(const float, ADDR(k_0f)));
		glTranslatef(fadd_m(fmul_m(f, &key[5]), &key[2]), fadd_m(fmul_m(f, &key[6]), &key[3]), fadd_m(fmul_m(f, &key[7]), &key[4]));
	} else
		glTranslatef_bits(BITS(bn->pos[0]), BITS(bn->pos[1]), BITS(bn->pos[2]));
	if (bn->rotKeyCount > 0) {
		RotKey *key = (RotKey *)key_at(AP(u8, bn->rotKeys), bn->rotKeyCount, 0x28, &animTime);
		int length = key->length;
		float f = length > 0 ? f32((long double)(animTime - key->time) / length) : 0;
		rotate(fmul_m(fld_m(&key->rotation[0]), toDegrees), &key->rotation[1]);
		rotate(fmul_m(FMUL(f, key->step[0]), toDegrees), &key->step[1]);
	} else
		rotate(fmul_m(fld_m(&bn->rotation[0]), toDegrees), &bn->rotation[1]);
	glGetFloatv(0xba6, (float *)out);
	glLoadMatrixf(saved);
}

/* A cache's name tree: 0x4c-byte nodes from nodes (the name, its item's index index, left left and right right by
   strcmp), count of them (at most capacity: none, or full, a fatal message out / no_room, full). The index of key's
   node; a missing one is added (index the count, *added set; the caller loads the item and counts it) */
static int tree_lookup(u8 *cache, const char *key, char *out, u32 no_room, u32 full, int *added)
{
	ShapeManager *mg = (ShapeManager *)cache;
	*added = 0;
	if (mg->capacity == 0)
		sys_fatalErrorN(out, AP(const char, RELOC(no_room)));
	u8 *nodes = AP(u8, mg->nodes), *node = nodes;
	APTR(u8) *link = NULL;
	if (mg->count != 0)
		for (;;) {
			int c = strcmp(key, (const char *)node);
			if (c == 0)
				return ((TreeNode *)node)->index;
			link = (APTR(u8) *)(node + (c < 0 ? 0x44 : 0x48));
			if (!*link)
				break;
			node = AP(u8, *link);
		}
	int i = mg->count;
	if (link) {
		if (i >= mg->capacity)
			sys_fatalError(out, AP(const char, RELOC(full)), i);
		i = mg->count;
		node = AP(u8, mg->nodes + i * 0x4c);
		*link = AREF(node);
	}
	strcpy((char *)node, key);
	((TreeNode *)node)->index = link ? i : 0;
	((TreeNode *)node)->left = ((TreeNode *)node)->right = 0;
	*added = 1;
	return i;
}

/* an item's file path: "dir\name.ext" with the cache's directory (dir), or "name.ext"; the extension by the cache's
   format (source: 0 or 1, another a fatal message) */
static void item_path(char *path, u8 *cache, const char *name, u32 ext0, u32 ext1, char *log, u32 bad)
{
	ShapeManager *mg = (ShapeManager *)cache;
	char ext[4];
	int format = ((int)mg->source);
	if (format == 0 || format == 1)
		strcpy(ext, AP(const char, (RELOC(format) ? ext1 : ext0)));
	else
		sys_fatalError(log, AP(const char, RELOC(bad)), format);
	if (mg->dir[0])
		sprintf(path, AP(const char, STR(0x4c4d5c, "%s\\%s.%s")), mg->dir, name, ext);
	else
		sprintf(path, AP(const char, STR(0x4c4d54, "%s.%s")), name, ext);
}

/* 0x46b1a0 (thiscall on a skeleton cache): the skeleton named name (upper-cased; empty or starting with '.': none,
   0), found in the cache's name tree or added to it (tree_lookup) and loaded into skeleton i (0x24 bytes each from
   items): from the skeleton dat (format source 2: its item's file, skel_loadFromFile) or a "ske" / "ase" file
   (skel_loadFrom), into the cache's data memory when it has one (data, its size dataSize, dataUsed used: the
   skeleton's size added) */
u8 *THISCALL (skel_getSkeletonPtrBy)(u8 *cache, const char *name)
{
	ShapeManager *mg = (ShapeManager *)cache;
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, AP(char, OBJ(g_logSkeletonManager)), STR(0x4c5528, "sizeOfSkeletonBuffer is zero-getSkele..."), STR(0x4c54c8, "skeleton overflow(%d)-getSkeletonPtrBy()"), &added);
	Skeleton *sk = AP(Skeleton, (mg->items + i * 0x24));
	if (!added)
		return ((u8 *)sk);
	const char *own = AP(const char, mg->nodes) + i * 0x4c;
	u8 *mem = AP(u8, mg->data);
	void *at = mem ? mem + mg->dataUsed : NULL;
	int room = mem ? mg->dataSize - mg->dataUsed : 0;
	if (((int)mg->source) == 2)
		skel_loadFromFile((u8 *)sk, skelDat_getItemFileBy(key), at, room);
	else {
		char path[0x100];
		item_path(path, cache, own, STR(0x4c54f4, "ske"), STR(0x4c54f8, "ase"), AP(char, OBJ(g_logSkeletonManager)), STR(0x4c54fc, "invalid file format(%s)-getSkeletonPt..."));
		skel_loadFrom((u8 *)sk, path, at, room);
	}
	if (mem)
		mg->dataUsed += sk->blockSize;
	mg->count++;
	return ((u8 *)sk);
}

/* 0x466dc0 (thiscall on a shape cache): the shape named name, as skel_getSkeletonPtrBy does it for skeletons: shape
   i (0x4c bytes each from items) loaded from the shape dat (shapeDat_getItemFileBy, shape_read) or a "shp" / "obj" file
   (shape_loadFrom), its textures looked up (shape_bindTextureBy with the cache's texture-name suffix (textureSuffix) and seven values
   bindFlags ..); bound (shape_bindPartTextures) when bind is 1, found or added */
u8 *THISCALL (shape_getByName)(u8 *cache, const char *name, int bind)
{
	ShapeManager *mg = (ShapeManager *)cache;
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, AP(char, OBJ(g_logShapeManager)), STR(0x4c4d98, "sizeOfShapeBuffer is zero-getShapePtr..."), STR(0x4c4d30, "shape overflow(%d)-getShapePtrBy()"), &added);
	u8 *shape = AP(u8, mg->items + i * 0x4c);
	Shape *md = (Shape *)shape;
	if (added) {
		const char *own = AP(const char, mg->nodes) + i * 0x4c;
		u8 *mem = AP(u8, mg->data);
		void *at = mem ? mem + mg->dataUsed : NULL;
		int room = mem ? mg->dataSize - mg->dataUsed : 0;
		if (((int)mg->source) == 2)
			/* (the original's first of its four copies of this pair: the patch DLL retargets all four, for the KYRIE models) */
#ifdef AXIS_NATIVE
			fix_shapeRead(shape, fix_shapeFind(key), at, room);   /* shape_read (shapeDat_getItemFileBy): the KYRIE models (fixes/kyrie.c) */
#else
			SITE_THISCALL(0x466eb8, shape_read, void, void *, void *, void *, int)(shape, SITE_CALL(0x466ea9, shapeDat_getItemFileBy, void *, const char *)(key), at, room);   /* shape_read (shapeDat_getItemFileBy) */
#endif
		else {
			char path[0x100];
			item_path(path, cache, own, STR(0x4c4d68, "shp"), STR(0x4c4d6c, "obj"), AP(char, OBJ(g_logShapeManager)), STR(0x4c4d70, "invalid file format(%s)-getShapePtrBy()"));
			shape_loadFrom(shape, path, at, room);
		}
		if (mem)
			mg->dataUsed += md->blockSize;
		shape_bindTextureBy(shape, mg->textureSuffix, mg->bindFlags, BITS(mg->tint[0]), BITS(mg->tint[1]),
		                    BITS(mg->tint[2]), BITS(mg->tint[3]), BITS(mg->tint[4]), BITS(mg->tint[5]));
		mg->count++;
	}
	if (bind == 1)
		shape_bindPartTextures(shape);
	return shape;
}

/* 0x466120 (thiscall on a shape): read from f. Its old data released (Shape_release), the 0x34-byte header (block size
   +4, part count partCount, a point centre, the version version: 0x71110300 the current format; an older file has a 0x30-byte
   header and 0x68-byte parts, its block grown by 0x18 a part, the position put back as it was), the block (+8, as
   take_block). The 0x80-byte parts (parts) at the block's start, then each part's tables after them: vertices,
   normals (12 bytes each), colours (4), texture coordinates (8) for its vertexCount vertices, and its primCount primitives
   (12 bytes; one slot more is left past them), each with its index list (+4 of them). An old file is relocated
   (shape_computeBounds). The shape's box (low low, high high) from the point centre and every part's box (box ..). Its
   callers ignore the eax it leaves */
void THISCALL (shape_read)(u8 *shape, void *f, void *mem, int size)
{
	Shape *md = (Shape *)shape;
	Shape_release(shape);
	crt_fread(shape, 0x34, 1, f);
	int current = md->version == 0x71110300;
	if (!current) {
		long at = crt_ftell(f);
		crt_fseek(f, -4, 1);   /* SEEK_CUR */
		md->blockSize += md->partCount * 0x18;
		crt_fseek(f, at, 0);   /* SEEK_SET */
	}
	take_block(shape, mem, size, AP(char, OBJ(g_logShape)), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *parts = AP(u8, md->parts = md->block);
	if (current)
		crt_fread(parts, 0x80, ((u32)md->partCount), f);
	else
		for (int i = 0; i < md->partCount; i++)
			crt_fread(AP(void, md->parts + i * 0x80), 0x68, 1, f);
	int at = md->partCount * 0x80;
	for (int i = 0; i < md->partCount; i++) {
		u8 *p = AP(u8, md->parts + i * 0x80);
		ShapePart *sp = (ShapePart *)p;
		sp->texture = -1;
		int n = sp->vertexCount;
		static const u8 sizes[4] = { 12, 12, 4, 8 };   /* vertices, normals, colours, texture coordinates */
		APTR(u8) *arrays[4] = { &sp->vertices, &sp->normals, &sp->colours, (APTR(u8) *)&sp->texCoords };
		for (int t = 0; t < 4; t++) {
			*arrays[t] = md->block + at;
			at += n * sizes[t];
		}
		for (int t = 0; t < 4; t++)
			crt_fread(AP(u8, *arrays[t]), sizes[t], ((u32)sp->vertexCount), f);
		sp->prims = md->block + at;
		crt_fread(AP(void, sp->prims), 0xc, ((u32)sp->primCount), f);
		at += 0xc;
		for (int k = 0; k < sp->primCount; k++) {
			ShapePrim *prim = AP(ShapePrim, (sp->prims + k * 0xc));
			prim->indices = md->block + at;
			crt_fread(AP(void, prim->indices), 4, ((u32)prim->indexCount), f);
			at += prim->indexCount * 4;
		}
	}
	if (!current)
		shape_computeBounds(shape);
	memcpy(md->low, md->centre, 12);
	memcpy(md->high, md->centre, 12);
	float *low = md->low, *high = md->high;
	for (int i = 0; i < md->partCount; i++) {
		const float *box = AP(const float, (md->parts + i * 0x80 + 0x68));
		for (int c = 0; c < 3; c++)
			if (low[c] > box[c])
				((u32 *)low)[c] = ((const u32 *)box)[c];
		for (int c = 0; c < 3; c++)
			if (!(high[c] >= box[3 + c]))
				((u32 *)high)[c] = ((const u32 *)box)[3 + c];
	}
}

/* the point (*px, *py, *pz) through the 4 x 4 matrix m (column-major) into out (x, y, z), each row summed as the
   original does: z and y terms first, then x, then the translation */
static void transform(float *out, const float *m, const float *px, const float *py, const float *pz)
{
	for (int r = 0; r < 3; r++)
		out[r] = f32(fadd_m(fmul_m(fld_m(pz), &m[8 + r]) + fmul_m(fld_m(py), &m[4 + r]) + fmul_m(fld_m(px), &m[r]), &m[12 + r]));
}

/* 0x46f8c0 (thiscall on an object list): its current skeleton (skeletons[skel]; none: nothing) posed at frame
   animTick (modulo the skeleton's duration + 1) for each of its bones (0x70 bytes from its bones; at most the list's
   count): on the GL modelview matrix (saved and put back) the parent bone's matrix is loaded (its entry's matrix;
   none: base, or the matrix there was), the position translated (the bone's pos, or its keys as in
   skel_getBoneMatrix; times the entry's scale), the rotation as in skel_getBoneMatrix; the result read back into the
   bone's 0x64-byte entry (matrix), with two points carried through it: g_vecOrigin (to pos) and the entry's shape's
   centre (none: pos again, to centre). Its callers ignore the eax it leaves */
void THISCALL (ObjectList_poseBones)(u8 *list, const float *base)
{
	ObjectList *ol = (ObjectList *)list;
	if (ol->skelCount <= 0)
		return;
	float saved[16], root[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	Mat4_copy(root, base ? base : saved);
	APTR(u8) *entry = AP(APTR(u8), ol->skeletons) + ol->skel;
	if (!*entry)
		return;
	const float *toDegrees = k_57_2958f, *point = AP(const float, ADDR(g_vecOrigin));
	for (int i = 0; i < ol->count; i++) {
		Skeleton *sk = AP(Skeleton, *entry);
		ListedObject *out = (ListedObject *)((AP(u8, ol->entries)) + i * 0x64);
		u8 *b = AP(u8, sk->bones + i * 0x70);
		Bone *bn = (Bone *)b;
		int animTime = ol->animTick % (sk->duration + 1);
		if (i >= sk->boneCount)
			break;
		int parent = bn->parent;
		glLoadMatrixf(parent < 0 ? root : (const float *)((AP(u8, ol->entries)) + parent * 0x64 + 0xc));
		const float *scale = &out->scale;
		if (bn->posKeyCount > 0) {
			int at = animTime;
			PosKey *key = (PosKey *)key_at(AP(u8, bn->posKeys), bn->posKeyCount, 0x20, &at);
			int length = key->length;
			long double f = length > 0 ? (long double)(at - key->time) / length : fld_m(AP(const float, ADDR(k_0f)));
			glTranslatef(fmul_m(fadd_m(fmul_m(f, &key->delta[0]), &key->pos[0]), scale), fmul_m(fadd_m(fmul_m(f, &key->delta[1]), &key->pos[1]), scale),
			             fmul_m(fadd_m(fmul_m(f, &key->delta[2]), &key->pos[2]), scale));
		} else
			glTranslatef(fmul_m(fld_m(&bn->pos[0]), scale), fmul_m(fld_m(&bn->pos[1]), scale),
			             fmul_m(fld_m(&bn->pos[2]), scale));
		if (bn->rotKeyCount > 0) {
			int at = animTime;
			RotKey *key = (RotKey *)key_at(AP(u8, bn->rotKeys), bn->rotKeyCount, 0x28, &at);
			int length = key->length;
			float f = length > 0 ? f32((long double)(at - key->time) / length) : 0;
			rotate(fmul_m(fld_m(&key->rotation[0]), toDegrees), &key->rotation[1]);
			rotate(fmul_m(FMUL(f, key->step[0]), toDegrees), &key->step[1]);
		} else
			rotate(fmul_m(fld_m(&bn->rotation[0]), toDegrees), &bn->rotation[1]);
		float *m = out->matrix;
		glGetFloatv(0xba6, m);
		transform(out->pos, m, &point[0], &point[1], &point[2]);
		const Shape *shape = AP(const Shape, out->shape);
		if (shape) {
			for (int r = 0; r < 3; r++)   /* (here the z, x, y terms in that order for the y and z rows) */
				out->centre[r] = r == 0
					? f32(fadd_m(FMUL(m[8], shape->centre[2]) + FMUL(m[4], shape->centre[1]) + FMUL(m[0], shape->centre[0]), &m[12]))
					: f32(fadd_m(FMUL(m[8 + r], shape->centre[2]) + FMUL(m[r], shape->centre[0]) + FMUL(m[4 + r], shape->centre[1]), &m[12 + r]));
		} else
			memcpy(out->centre, out->pos, 12);
	}
	glLoadMatrixf(saved);
}

#define crt_fgets(line, n, f) CRT_CALL(fgets, char *, char *, int, void *)(line, n, f)
#define TOKEN(delims) crt_strtok(NULL, AP(const char, RELOC(delims)))
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
   keys (0x28) and takes the data memory (allocated, ownsBlock 1; or given: too small is fatal); pass 2 (from the top)
   reads SCENE_LASTFRAME / FRAMESPEED (frames the length in ms) / TICKSPERFRAME, and per bone (cameras skipped) its
   NODE_NAME, NODE_PARENT (among the earlier bones; missing is fatal), TM_POS / TM_ROTAXIS / TM_ROTANGLE (y and z
   swapped, z and the angle negated) and its key lists (each rotation key composed onto the previous one). Then the
   bones become relative to their parents (last first) and the keys get their spans and deltas. Its caller ignores
   the eax it leaves */
void THISCALL (skel_loadAseFrom)(u8 *sk, void *f, u8 *mem, int memSize)
{
	Skeleton *sko = (Skeleton *)sk;
	char line[0x100], parent[0x40];
	Skeleton_release(sk);
	sko->boneCount = sko->rotKeyTotal = sko->posKeyTotal = 0;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, AP(const char, STR(0x4c5498, "* \t")));
		if (!strcmp(t, AP(const char, STR(0x4c548c, "GEOMOBJECT"))))
			sko->boneCount++;
		else if (!strcmp(t, AP(const char, STR(0x4c5478, "CONTROL_TCB_POS_KEY"))) || !strcmp(t, AP(const char, STR(0x4c5460, "CONTROL_BEZIER_POS_KEY"))))
			sko->posKeyTotal++;
		else if (!strcmp(t, AP(const char, STR(0x4c544c, "CONTROL_TCB_ROT_KEY"))))
			sko->rotKeyTotal++;
	}
	int bones = sko->boneCount;
	if (bones <= 0)
		return;
	int size = sko->blockSize = bones * 0x70 + sko->rotKeyTotal * 0x28 + sko->posKeyTotal * 0x20;
	if (!mem) {
		ASET(sko->block, operator_new(size));
		if (!AGET(void, sko->block))
			sys_fatalError(AP(char, OBJ(g_logSkeleton)), AP(const char, STR(0x4c4bec, "insufficient memory for dataMemory(%d...")), sko->blockSize);
		sko->ownsBlock = 1;
	} else {
		if (memSize < size)
			sys_fatalErrorN(AP(char, OBJ(g_logSkeleton)), AP(const char, STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l...")), size, memSize);
		sko->block = AREF(mem);
		sko->ownsBlock = 0;
	}
	sko->bones = sko->block;
	int keyAt = sko->boneCount * 0x70;   /* where the next key list goes, after the bones */
	crt_fseek(f, 0, 0);
	int frames = 0, ms = 0x21, ticks = 0xa0, skip = -1, index = -1, at = -0x70;
	Bone *b = NULL;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, AP(const char, STR(0x4c5498, "* \t")));
		if (!strcmp(t, AP(const char, STR(0x4c543c, "SCENE_LASTFRAME"))))   /* SCENE_LASTFRAME */
			frames = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, AP(const char, STR(0x4c541c, "SCENE_FRAMESPEED")))) {   /* SCENE_FRAMESPEED */
			ms = 1000 / crt_atoi(TOKEN(LINE_END));
			sko->duration = ms * frames;
		} else if (!strcmp(t, AP(const char, STR(0x4c5408, "SCENE_TICKSPERFRAME"))))   /* SCENE_TICKSPERFRAME */
			ticks = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, AP(const char, STR(0x4c548c, "GEOMOBJECT")))) {   /* GEOMOBJECT */
			index++;
			skip = 0;
			at += 0x70;
			b = AP(Bone, (sko->bones + at));
			b->parent = -1;
			b->posKeyCount = (*(int *)&b->posKeys) = b->rotKeyCount = (*(int *)&b->rotKeys) = 0;
		} else if (!strcmp(t, AP(const char, STR(0x4c53f8, "CAMERAOBJECT")))) {   /* CAMERAOBJECT */
			skip = 1;
			continue;
		}
		if (skip)
			continue;
		if (!strcmp(t, AP(const char, STR(0x4c5430, "NODE_NAME"))))   /* NODE_NAME */
			strcpy(AP(char, RELOC(b)), TOKEN(STR(0x4c53f4, "\"")));
		else if (!strcmp(t, AP(const char, STR(0x4c53e8, "NODE_PARENT")))) {   /* NODE_PARENT */
			strcpy(parent, TOKEN(STR(0x4c53f4, "\"")));
			if (at > 0)
				for (int j = 0; j < index; j++)
					if (!strcmp(AP(const char, sko->bones) + j * 0x70, parent)) {
						b->parent = j;
						break;
					}
			if (b->parent < 0)
				sys_fatalError(AP(char, OBJ(g_logSkeleton)), AP(const char, STR(0x4c53b8, "can't find parent part(%s)-loadAseFor...")), (int)AV(parent));
		} else if (!strcmp(t, AP(const char, STR(0x4c53b0, "TM_POS")))) {   /* TM_POS */
			b->pos[0] = ase_float(SPACE, 0);
			b->pos[2] = ase_float(SPACE, 1);
			b->pos[1] = ase_float(LINE_END, 0);
		} else if (!strcmp(t, AP(const char, STR(0x4c53a4, "TM_ROTAXIS")))) {   /* TM_ROTAXIS */
			b->rotation[1] = ase_float(SPACE, 0);
			b->rotation[3] = ase_float(SPACE, 1);
			b->rotation[2] = ase_float(LINE_END, 0);
		} else if (!strcmp(t, AP(const char, STR(0x4c5398, "TM_ROTANGLE"))))   /* TM_ROTANGLE */
			b->rotation[0] = ase_float(LINE_END, 1);
		else if (!strcmp(t, AP(const char, STR(0x4c5388, "CONTROL_POS_TCB"))) || !strcmp(t, AP(const char, STR(0x4c5374, "CONTROL_POS_BEZIER")))) {   /* CONTROL_POS_TCB / _BEZIER */
			b->posKeys = sko->block + keyAt;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, AP(const char, STR(0x4c535c, "* \t\n")));
				if (!strcmp(t, AP(const char, STR(0x4c5478, "CONTROL_TCB_POS_KEY"))) || !strcmp(t, AP(const char, STR(0x4c5460, "CONTROL_BEZIER_POS_KEY")))) {
					PosKey *k = AP(PosKey, (b->posKeys + b->posKeyCount * 0x20));
					k->time = ase_time(ticks, ms);
					k->pos[0] = ase_float(SPACE, 0);
					k->pos[2] = ase_float(SPACE, 1);
					k->pos[1] = ase_float(SPACE, 0);
					b->posKeyCount++;
				} else if (t && t[0] == '}')
					break;
			}
			keyAt += b->posKeyCount * 0x20;
		} else if (!strcmp(t, AP(const char, STR(0x4c5364, "CONTROL_ROT_TCB")))) {   /* CONTROL_ROT_TCB */
			b->rotKeys = sko->block + keyAt;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, AP(const char, STR(0x4c535c, "* \t\n")));
				if (!strcmp(t, AP(const char, STR(0x4c544c, "CONTROL_TCB_ROT_KEY")))) {
					RotKey *rk = AP(RotKey, (b->rotKeys + b->rotKeyCount * 0x28));
					rk->time = ase_time(ticks, ms);
					rk->rotation[1] = ase_float(SPACE, 0);
					rk->rotation[3] = ase_float(SPACE, 1);
					rk->rotation[2] = ase_float(SPACE, 0);
					rk->rotation[0] = ase_float(SPACE, 1);
					if (b->rotKeyCount > 0) {
						float r[4];
						axisAngle_combine(r, (const float *)(AP(u8, RELOC(rk)) + 8), (const float *)(AP(u8, RELOC(rk)) + 8 - 0x28));
						memcpy((u8 *)rk + 8, r, 16);
					}
					b->rotKeyCount++;
				} else if (t && t[0] == '}')
					break;
			}
			keyAt += b->rotKeyCount * 0x28;
		}
	}
	u8 *all = AP(u8, ((Skeleton *)sk)->bones);
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
		u8 *bone = AP(u8, ((Skeleton *)sk)->bones + i * 0x70);
		for (int k = 0; k < ((Bone *)bone)->posKeyCount - 1; k++) {
			u8 *key = AP(u8, ((Bone *)bone)->posKeys + k * 0x20);
			((PosKey *)key)->length = ((PosKey *)key)[1].time - ((PosKey *)key)->time;
			for (int c = 0; c < 3; c++)
				((PosKey *)key)->delta[c] = f32(FSUB(((PosKey *)key)[1].pos[c], ((PosKey *)key)->pos[c]));
		}
		if (((Bone *)bone)->posKeyCount > 0) {
			u8 *last = AP(u8, ((Bone *)bone)->posKeys + (((Bone *)bone)->posKeyCount - 1) * 0x20);
			((PosKey *)last)->length = 0;
			BITS(((PosKey *)last)->delta[0]) = BITS(((PosKey *)last)->delta[1]) = BITS(((PosKey *)last)->delta[2]) = 0;
		}
		for (int k = 0; k < ((Bone *)bone)->rotKeyCount - 1; k++) {
			u8 *key = AP(u8, ((Bone *)bone)->rotKeys + k * 0x28);
			((RotKey *)key)->length = ((RotKey *)key)[1].time - ((RotKey *)key)->time;
			float r[16], back[16], next[16], step[16];
			Mat4_fromAxisAngle(r, ((RotKey *)key)->rotation);
			Mat4_transpose(back, r);
			Mat4_fromAxisAngle(next, ((RotKey *)key)[1].rotation);
			Mat4_multiply(step, back, next);
			axisAngle_fromMatrix(((RotKey *)key)->step, step);
		}
		if (((Bone *)bone)->rotKeyCount > 0) {
			u8 *last = AP(u8, ((Bone *)bone)->rotKeys + (((Bone *)bone)->rotKeyCount - 1) * 0x28);
			((RotKey *)last)->length = 0;
			BITS(((RotKey *)last)->step[0]) = BITS(((RotKey *)last)->step[1]) = BITS(((RotKey *)last)->step[2]) = BITS(((RotKey *)last)->step[3]) = 0;
		}
	}
}
#undef crt_fgets
#undef TOKEN
#undef SPACE
#undef LINE_END

#define crt_fgets(line, n, f) CRT_CALL(fgets, char *, char *, int, void *)(line, n, f)
#define TOK(s, delims) crt_strtok(s, AP(const char, RELOC(delims)))
#define SPACE STR(0x4ad5dc, " \t")
#define LINE_END STR(0x4b4310, " \t\n")
#define SLASH STR(0x4ad564, "/")
#define BAD_OBJ() sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4c20, "invalid obj format string(%s)-loadObj...")), (int)AV(line))

/* a face's first corner token: a lone "\" continues the face on the next line */
static char *face_start(char *line, void *f)
{
	char *t = TOK(NULL, LINE_END);
	if (!strcmp(t, AP(const char, STR(0x4b1328, "\\")))) {
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
	memcpy(AP(void, sp->vertices + i * 12), vs + (crt_atoi(TOK(corner, SLASH)) - 1) * 3, 12);
	char *a = TOK(NULL, SLASH);
	if (!a)
		return 0;
	int ai = crt_atoi(a) - 1;
	char *b = TOK(NULL, SLASH);
	float *uv = AP(float, sp->texCoords) + i * 2;
	if (!b) {
		BITS(uv[0]) = BITS(uv[1]) = 0;
		memcpy(AP(void, sp->normals + i * 12), ns + ai * 3, 12);
	} else {
		memcpy(uv, ts + ai * 2, 8);
		memcpy(AP(void, sp->normals + i * 12), ns + (crt_atoi(b) - 1) * 3, 12);
	}
	return 1;
}

/* 0x464db0 (thiscall on a shape): a shape from a Wavefront OBJ text file. The old one released (Shape_release);
   pass 1 counts the parts (usemtl), positions (v), normals (vn), texture coordinates (vt) and the corners of the
   faces (colourCount: a face of 3 or 4 corners, 3 or 6; fewer are fatal; triangleCount triangles); the data memory is taken
   (allocated with three temporary arrays, or given: too small is fatal); pass 2 counts each part's corners and lays
   out its arrays and its one triangle list; pass 3 reads the values, names the parts after the last "_" piece of
   the material (its last character cut) and expands the faces into corners (bare positions get a flat normal). A
   "3DS" comment flips y / z (the original's loop over that never moves on: a part with corners hangs it). Then the
   colours, the temporaries freed, the parts' bounds (shape_computeBounds) and the shape's. As the original, a quad's
   second triangle copies its corners into the temporary arrays rather than the part's. Its caller ignores the eax
   it leaves */
void THISCALL (shape_readObj)(u8 *sh, void *f, u8 *mem, int memSize)
{
	Shape *md = (Shape *)sh;
	char line[0x100], last[0x100], c[4][0x20];
	int nv = 0, nvn = 0, nvt = 0;
	Shape_release(sh);
	md->partCount = 0;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, AP(const char, STR(0x4c4c64, "usemtl"))))
			md->partCount++;
		else if (!strcmp(t, AP(const char, STR(0x4c4c60, "v"))))
			nv++;
		else if (!strcmp(t, AP(const char, STR(0x4c4c5c, "vn"))))
			nvn++;
		else if (!strcmp(t, AP(const char, STR(0x4c4c58, "vt"))))
			nvt++;
		else if (!strcmp(t, AP(const char, STR(0x4c4c54, "f")))) {
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
		ASET(md->block, operator_new(size));
		if (!AGET(void, md->block))
			sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4bec, "insufficient memory for dataMemory(%d...")), md->blockSize);
		md->ownsBlock = 1;
		if (!(vs = operator_new(nv * 12)))
			sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4bb4, "insufficient memory for vertexCoordAr...")), nv);
		if (!(ns = operator_new(nvn * 12)))
			sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4b78, "insufficient memory for vertexNormalA...")), nvn);
		if (!(ts = operator_new(nvt * 8)))
			sys_fatalError(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4b38, "insufficient memory for vertexTexture...")), nvt);
		allocated = 1;
	} else {
		int need = nvt * 8 + (nvn + nv) * 0xc + size;
		if (memSize < need)
			sys_fatalErrorN(AP(char, OBJ(g_logShape)), AP(const char, STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l...")), need, memSize);
		md->block = AREF(mem);
		md->ownsBlock = 0;
		vs = (float *)(mem + md->blockSize);
		ns = (float *)(mem + md->blockSize + nv * 0xc);
		ts = (float *)(mem + md->blockSize + (nvn + nv) * 0xc);
		allocated = 0;
	}
	u8 *all = AP(u8, md->parts = md->block);
	int at = md->partCount << 7;
	for (int k = 0; k < md->partCount; k++) {
		u8 *pt = all + k * 0x80;
		((ShapePart *)pt)->flags = 0;
		((ShapePart *)pt)->texture = 0;
		for (int o = offsetof(ShapePart, vertexCount); o <= (int)offsetof(ShapePart, prims); o += 4)   /* vertexCount .. prims */
			GAME_VAR(int, pt + o) = 0;
	}
	crt_fseek(f, 0, 0);
	int off = -0x80;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, AP(const char, STR(0x4c4c64, "usemtl")))) {
			off += 0x80;
			GAME_VAR(int, md->parts + 0x60 + off) = 1;
		} else if (!strcmp(t, AP(const char, STR(0x4c4c54, "f")))) {
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
		ShapePart *pt = AP(ShapePart, (md->parts + k * 0x80));
		u8 *data = AP(u8, md->block);
		int n = pt->vertexCount;
		pt->vertices = AREF(data + at);
		at += n * 12;
		pt->normals = AREF(data + at);
		at += n * 12;
		pt->colours = AREF(data + at);
		at += n * 4;
		pt->colourBase = corner;
		corner += n;
		ASET(pt->texCoords, data + at);
		at += n * 8;
		pt->primCount = 1;
		u32 *prim = (u32 *)(data + at);
		ASET(pt->prims, prim);
		at += 0xc;
		prim[0] = 4;
		prim[1] = ((u32)pt->vertexCount);
		prim[2] = (u32)(md->block + at);
		at += pt->vertexCount * 4;
	}
	ShapePart *part = NULL;
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
			if (!strcmp(t, AP(const char, STR(0x4c4c60, "v")))) {
				vp[0] = f32(crt_atof(TOK(NULL, SPACE)));
				vp[1] = f32(crt_atof(TOK(NULL, SPACE)));
				vp[2] = f32(crt_atof(TOK(NULL, LINE_END)));
				vp += 3;
			} else if (!strcmp(t, AP(const char, STR(0x4c4c5c, "vn")))) {
				np[0] = f32(crt_atof(TOK(NULL, SPACE)));
				np[1] = f32(crt_atof(TOK(NULL, SPACE)));
				np[2] = f32(crt_atof(TOK(NULL, LINE_END)));
				np += 3;
			} else if (!strcmp(t, AP(const char, STR(0x4c4c58, "vt")))) {
				tp[0] = f32(crt_atof(TOK(NULL, SPACE)));
				tp[1] = f32(crt_atof(TOK(NULL, LINE_END)));
				tp += 2;
			} else if (!strcmp(t, AP(const char, STR(0x4c4c64, "usemtl")))) {
				part = AP(ShapePart, (md->parts + poff));
				poff += 0x80;
				for (char *piece = TOK(NULL, STR(0x4c4b04, "_")); piece; piece = TOK(NULL, STR(0x4c4b04, "_")))
					strcpy(last, piece);
				char *name = TOK(last, LINE_END);
				strcpy((char *)((u8 *)part) + 4, name);
				((u8 *)part)[(int)strlen(name) + 3] = 0;
				part->texture = -1;
				next = 0;
			} else if (!strcmp(t, AP(const char, STR(0x4c4c54, "f")))) {
				strcpy(c[0], face_start(line, f));
				strcpy(c[1], TOK(NULL, LINE_END));
				strcpy(c[2], TOK(NULL, LINE_END));
				char *t4 = TOK(NULL, LINE_END);
				if (t4)
					strcpy(c[3], t4);
				else
					c[3][0] = 0;
				int b = corner;
				float *pv = AGET(float, part->vertices), *pn;
				obj_corner((u8 *)part, b, c[0], vs, ns, ts);
				obj_corner((u8 *)part, b + 1, c[1], vs, ns, ts);
				if (!obj_corner((u8 *)part, b + 2, c[2], vs, ns, ts)) {
					float tmp[3];
					pv = AGET(float, part->vertices);
					const float *nrm = math_triangleNormal(tmp, pv + b * 3, pv + (b + 1) * 3, pv + (b + 2) * 3);
					pn = AGET(float, part->normals);
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
					if (!obj_corner((u8 *)part, b + 4, c[3], vs, ns, ts)) {
						float tmp[3];
						pv = AGET(float, part->vertices);
						const float *nrm = math_triangleNormal(tmp, pv + q * 3, pv + (b + 4) * 3, pv + (b + 5) * 3);
						pn = AGET(float, part->normals);
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
		ShapePart *pt = AP(ShapePart, (md->parts + k * 0x80));
		for (int i = 0; i < pt->vertexCount; i++)
			AP(u32, GAME_VAR(APTR(u32), pt->prims + 8))[i] = i;
	}
	if (flip)
		for (int k = 0; k < md->partCount; k++) {
			ShapePart *pt = AP(ShapePart, (md->parts + k * 0x80));
			while (pt->vertexCount > 0) {   /* (never moves on, as the original) */
				k++;
				float *v = AGET(float, pt->vertices), *n = AGET(float, pt->normals);
				long double y = fld_m(&v[2]);
				v[2] = f32(-fld_m(&v[1]));
				v[1] = f32(y);
				y = fld_m(&n[2]);
				n[2] = f32(-fld_m(&n[1]));
				n[1] = f32(y);
				for (int c3 = 0; c3 < 3; c3++)
					n[c3] = f32(fmul_m(fld_m(&n[c3]), AP(const float, ADDR(k_m1f))));
			}
		}
	for (int k = 0; k < md->partCount; k++) {
		ShapePart *pt = AP(ShapePart, (md->parts + k * 0x80));
		for (int i = 0; i < pt->vertexCount; i++)
			AGET(u32, pt->colours)[i] = g_white;
	}
	if (allocated == 1) {
		if (nv > 0)
			operator_delete(vs);
		if (nvn > 0)
			operator_delete(ns);
		if (nvt > 0)
			operator_delete(ts);
	}
	shape_computeBounds(sh);
	memcpy(md->low, md->centre, 12);
	memcpy(md->high, md->centre, 12);
	for (int k = 0; k < md->partCount; k++) {
		ShapePart *pt = AP(ShapePart, (md->parts + k * 0x80));
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
