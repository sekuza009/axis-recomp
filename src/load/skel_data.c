/* skel_data.c: a skeleton's data block: its header read or set, then one block (allocated, or the caller's memory
   when it is big enough, else a fatal message: the record out and the two messages given) laid out as the bones' records followed by their tables. */
#include "../game.h"
#include <string.h>

#define AT(type, p, offset) GAME_VAR(type, (u8 *)RELOC(p) + (offset))
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

/* the block (+8; +4 its size): allocated (owned, +0xc 1) without memory given, else the memory given (owned 0 when
   own_flag; the caller's size checked) */
static void take_block(u8 *self, void *mem, int size, char *out, u32 no_memory, u32 too_small, int own_flag)
{
	if (!mem) {
		AT(void *, self, 8) = operator_new(AT(u32, self, 4));
		if (!AT(void *, self, 8))
			sys_fatalError(out, (const char *)RELOC(no_memory), AT(int, self, 4));
		AT(int, self, 0xc) = 1;
	} else {
		if (size < AT(int, self, 4))
			sys_fatalErrorN(out, (const char *)RELOC(too_small), AT(int, self, 4), size);
		AT(void *, self, 8) = mem;
		if (own_flag)
			AT(int, self, 0xc) = 0;
	}
}

/* 0x46aa10 (thiscall on a skeleton): read from f: the 0x24-byte header, the block (+8, its size +4), then the bones
   (0x70 bytes each, +0x10 of them, at the block's start: +0x14) and after them each bone's two tables (+0x60 keys of
   0x20 bytes at +0x64, +0x68 frames of 0x28 bytes at +0x6c). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFromFile)(u8 *self, void *f, void *mem, int size)
{
	Skeleton_release(self);
	crt_fread(self, 0x24, 1, f);
	take_block(self, mem, size, (char *)IMG(0xa0eaa8), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *bones = AT(u8 *, self, 0x14) = AT(u8 *, self, 8);
	crt_fread(bones, 0x70, AT(u32, self, 0x10), f);
	int at = AT(int, self, 0x10) * 0x70;
	for (int i = 0; i < AT(int, self, 0x10); i++) {
		u8 *bone = AT(u8 *, self, 0x14) + i * 0x70;
		AT(u8 *, bone, 0x64) = AT(u8 *, self, 8) + at;
		u32 keys = AT(u32, bone, 0x60);
		at += keys * 0x20;
		AT(u8 *, bone, 0x6c) = AT(u8 *, self, 8) + at;
		at += AT(int, bone, 0x68) * 0x28;
		crt_fread(AT(void *, bone, 0x64), 0x20, keys, f);
		crt_fread(AT(void *, bone, 0x6c), 0x28, AT(u32, bone, 0x68), f);
	}
}

/* 0x46aeb0 (thiscall on a skeleton set): set up for n skeletons from the directory dir (+0x10; none: 0x4b1304), a at
   +0x110, n at +0x114, extra bytes (+0x124) after them: the block (+8, its size n x 0x70 + extra at +4) holds the
   skeletons' 0x4c-byte records (+0x118), then their 0x24-byte skeletons (+0x11c, each created and released), then the
   rest (+0x128). Its callers ignore the eax it leaves */
void THISCALL (skelSet_setup)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	SkeletonManager_release(self);
	strcpy((char *)self + 0x10, dir ? dir : (const char *)STR(0x4b1304, "."));
	AT(u32, self, 0x110) = a;
	AT(int, self, 0x114) = n;
	AT(int, self, 0x124) = extra;
	AT(int, self, 4) = n * 0x70 + extra;
	take_block(self, mem, size, (char *)IMG(0xa0eaa0), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 0);
	n = AT(int, self, 0x114);
	AT(u8 *, self, 0x118) = AT(u8 *, self, 8);
	AT(u8 *, self, 0x11c) = AT(u8 *, self, 8) + n * 0x4c;
	for (int i = 0; i < AT(int, self, 0x114); i++) {
		Skeleton_clear(AT(u8 *, self, 0x11c) + i * 0x24);
		Skeleton_release(AT(u8 *, self, 0x11c) + i * 0x24);
	}
	AT(u8 *, self, 0x128) = AT(u8 *, self, 8) + n * 0x70;
}

/* 0x466a60 (thiscall on a shape set): set up for n shapes from the directory dir (+0x10, upper-cased; none or
   0x4b1304: empty), a at +0x110, n at +0x114, extra bytes (+0x124) after them: the block (+8, its size n x 0x98 +
   extra at +4) holds the shapes' 0x4c-byte records (+0x118), then their 0x4c-byte shapes (+0x11c, each created and
   released), then the rest (+0x128); the name (+0x130) and seven counts (+0x230 ..) cleared. Its callers ignore the
   eax it leaves */
void THISCALL (shape_initBy)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	ShapeManager_release(self);
	if (dir && strcmp(dir, (const char *)STR(0x4b1304, ".")) != 0)
		strcpy((char *)self + 0x10, dir);
	else
		self[0x10] = 0;
	path_normalize((char *)self + 0x10);
	AT(u32, self, 0x110) = a;
	AT(int, self, 0x114) = n;
	AT(int, self, 0x124) = extra;
	AT(int, self, 4) = n * 0x98 + extra;
	take_block(self, mem, size, (char *)IMG(0xa0e788), STR(0x4c4cec, "insufficient memory for dataMemory(%d..."), STR(0x4c4cbc, "reserved dataMemory overflow(%d/%d) -..."), 0);
	n = AT(int, self, 0x114);
	AT(u8 *, self, 0x118) = AT(u8 *, self, 8);
	AT(u8 *, self, 0x11c) = AT(u8 *, self, 8) + n * 0x4c;
	for (int i = 0; i < AT(int, self, 0x114); i++) {
		Model_clear(AT(u8 *, self, 0x11c) + i * 0x4c);
		Model_release(AT(u8 *, self, 0x11c) + i * 0x4c);
	}
	self[0x130] = 0;
	AT(u8 *, self, 0x128) = AT(u8 *, self, 8) + n * 0x98;
	for (int k = 0; k < 7; k++)
		AT(int, self, 0x230 + k * 4) = 0;
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
		sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4ae4, "can not read file %s-loadFrom()"), (int)path);
	switch (file_format(path, "shp", "obj")) {
	case 0:
		shape_read(shape, f, mem, size);
		break;
	case 1:
		model_loadObjFormatFrom(shape, f, mem, size);
		break;
	default:
		sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4aa4, "can't figure out what the format of t..."), (int)path);
	}
	fclose(f);
}

/* 0x4699d0 (thiscall on a skeleton): the same for skeletons: "ske" the binary format (skel_loadFromFile), "ase"
   ASCII scene export (skel_loadAseFrom). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom)(u8 *sk, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_fatalError((char *)IMG(0xa0eaa8), (const char *)STR(0x4c4ae4, "can not read file %s-loadFrom()"), (int)path);
	switch (file_format(path, "ske", "ase")) {
	case 0:
		skel_loadFromFile(sk, f, mem, size);
		break;
	case 1:
		skel_loadAseFrom(sk, f, mem, size);
		break;
	default:
		sys_fatalError((char *)IMG(0xa0eaa8), (const char *)STR(0x4c4aa4, "can't figure out what the format of t..."), (int)path);
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
	partList_release(list);
	AT(int, list, 0x10) = ns;
	AT(int, list, 0x1c) = nk;
	AT(int, list, 0x2c) = lit;
	AT(int, list, 0x18) = 0;
	/* 65, and the entries walked by pointer: the frame is then as deep as the original's (0x11c with the saved
	   registers), so the callees' frames lie where they did there. The skeleton loading reads stack it never wrote
	   (the earlier callees' leftovers); a frame 4 bytes deeper gave those reads other values now and then */
	u32 found[65];
	for (int i = 0; i < AT(int, list, 0x10); i++) {
		u32 shape = shape_getByName(shapes, (const char *)names + i * 0x44, 0);
		if (i < 64)
			found[i] = shape;
		if (shape)
			AT(int, list, 0x18) += AT(int, shape, 0x18);
	}
	AT(int, list, 4) = (AT(int, list, 0x10) * 25 + AT(int, list, 0x1c)) * 4;
	if (AT(int, list, 0x2c) == 1)
		AT(int, list, 4) += AT(int, list, 0x18) * 4;
	if (!mem) {
		AT(void *, list, 8) = operator_new(AT(u32, list, 4));
		if (!AT(void *, list, 8))
			sys_fatalError((char *)IMG(0xae2e98), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), AT(int, list, 4));
		AT(int, list, 0xc) = 1;
	} else {
		if (size < AT(int, list, 4))
			sys_fatalErrorN((char *)IMG(0xae2e98), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), AT(int, list, 4), size);
		AT(void *, list, 8) = mem;
	}
	AT(u8 *, list, 0x14) = AT(u8 *, list, 8);
	int colours = AT(int, list, 0x10) * 100;
	u32 *entry = (u32 *)AT(u8 *, list, 0x14);
	for (int i = 0; i < AT(int, list, 0x10); i++, entry += 25) {
		entry[0] = i < 64 ? found[i] : shape_getByName(shapes, (const char *)names + i * 0x44, 0);
		entry[1] = AT(u32, names, i * 0x44 + 0x40);
		if (AT(int, list, 0x2c) == 1 && entry[0]) {
			entry[2] = (u32)(AT(u8 *, list, 8) + colours);
			colours += AT(int, entry[0], 0x18) * 4;
		} else
			entry[2] = 0;
	}
	AT(u8 *, list, 0x20) = AT(u8 *, list, 8) + colours;
	for (int j = 0; j < AT(int, list, 0x1c); j++)
		AT(void *, AT(u8 *, list, 0x20), j * 4) = skel_getSkeletonPtrBy(skels, (u32)(knames + j * 0x40));
	if (AT(int, list, 0x2c) == 1)
		ObjectList_relight(list, factors, lights);
}

/* the key for frame among a bone's n keys (size bytes each, their first dword the frame they start at): the last one
   starting at or before it (a binary search); a frame before the first key is moved up to it */
static u8 *key_at(u8 *keys, int n, int size, int *frame)
{
	int lo = 0;
	if (*frame < AT(int, keys, 0))
		*frame = AT(int, keys, 0);
	else
		for (int hi = n - 1; lo < hi;) {
			int mid = (hi + lo + 1) / 2;
			if (*frame < AT(int, keys, mid * size))
				hi = mid - 1;
			else
				lo = mid;
		}
	return keys + lo * size;
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
	if (bone >= AT(int, sk, 0x10)) {
		for (int k = 0; k < 16; k++)
			out[k] = k % 5 == 0 ? 0x3f800000 : 0;   /* 1.0 on the diagonal */
		return;
	}
	const float *unit = (const float *)IMG(0x4aa270);
	float saved[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	int frames = AT(int, sk, 0x20);
	int frame = ftol(fmul_m(frames, &t));
	if (frame < 0)
		frame = 0;
	else if (frame >= frames)
		frame = frames;
	glLoadIdentity();
	u8 *b = AT(u8 *, sk, 0x14) + bone * 0x70;
	if (AT(int, b, 0x60) > 0) {
		float *key = (float *)key_at(AT(u8 *, b, 0x64), AT(int, b, 0x60), 0x20, &frame);
		int length = ((int *)key)[1];
		long double f = length > 0 ? (long double)(frame - ((int *)key)[0]) / length : fld_m((const float *)ADDR(k_0f));
		glTranslatef(fadd_m(fmul_m(f, &key[5]), &key[2]), fadd_m(fmul_m(f, &key[6]), &key[3]), fadd_m(fmul_m(f, &key[7]), &key[4]));
	} else
		glTranslatef_bits(AT(u32, b, 0x44), AT(u32, b, 0x48), AT(u32, b, 0x4c));
	if (AT(int, b, 0x68) > 0) {
		float *key = (float *)key_at(AT(u8 *, b, 0x6c), AT(int, b, 0x68), 0x28, &frame);
		int length = ((int *)key)[1];
		float f = length > 0 ? f32((long double)(frame - ((int *)key)[0]) / length) : 0;
		rotate(fmul_m(fld_m(&key[2]), unit), &key[3]);
		rotate(fmul_m(fmul_m(fld_m(&f), &key[6]), unit), &key[7]);
	} else
		rotate(fmul_m(fld_m((const float *)(RELOC(b) + 0x50)), unit), (const float *)(RELOC(b) + 0x54));
	glGetFloatv(0xba6, (float *)out);
	glLoadMatrixf(saved);
}

/* A cache's name tree: 0x4c-byte nodes from +0x118 (the name, its item's index +0x40, left +0x44 and right +0x48 by
   strcmp), +0x120 of them (at most +0x114: none, or full, a fatal message out / no_room, full). The index of key's
   node; a missing one is added (index the count, *added set; the caller loads the item and counts it) */
static int tree_lookup(u8 *cache, const char *key, char *out, u32 no_room, u32 full, int *added)
{
	*added = 0;
	if (AT(int, cache, 0x114) == 0)
		GAME_FN(sys_fatalError, 0x46c710, void, char *, const char *)(out, (const char *)RELOC(no_room));
	u8 *nodes = AT(u8 *, cache, 0x118), *node = nodes;
	u8 **link = NULL;
	if (AT(int, cache, 0x120) != 0)
		for (;;) {
			int c = strcmp(key, (const char *)node);
			if (c == 0)
				return AT(int, node, 0x40);
			link = (u8 **)(node + (c < 0 ? 0x44 : 0x48));
			if (!*link)
				break;
			node = *link;
		}
	int i = AT(int, cache, 0x120);
	if (link) {
		if (i >= AT(int, cache, 0x114))
			sys_fatalError(out, (const char *)RELOC(full), i);
		i = AT(int, cache, 0x120);
		*link = node = AT(u8 *, cache, 0x118) + i * 0x4c;
	}
	strcpy((char *)node, key);
	AT(int, node, 0x40) = link ? i : 0;
	AT(int, node, 0x44) = AT(int, node, 0x48) = 0;
	*added = 1;
	return i;
}

/* an item's file path: "dir\name.ext" with the cache's directory (+0x10), or "name.ext"; the extension by the cache's
   format (+0x110: 0 or 1, another a fatal message) */
static void item_path(char *path, u8 *cache, const char *name, u32 ext0, u32 ext1, char *out, u32 bad)
{
	char ext[4];
	int format = AT(int, cache, 0x110);
	if (format == 0 || format == 1)
		strcpy(ext, (const char *)(RELOC(format) ? ext1 : ext0));
	else
		sys_fatalError(out, (const char *)RELOC(bad), format);
	if (cache[0x10])
		sprintf(path, (const char *)STR(0x4c4d5c, "%s\\%s.%s"), cache + 0x10, name, ext);
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
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, (char *)IMG(0xa0eaa0), STR(0x4c5528, "sizeOfSkeletonBuffer is zero-getSkele..."), STR(0x4c54c8, "skeleton overflow(%d)-getSkeletonPtrBy()"), &added);
	u8 *sk = AT(u8 *, cache, 0x11c) + i * 0x24;
	if (!added)
		return sk;
	const char *own = (const char *)AT(u8 *, cache, 0x118) + i * 0x4c;
	u8 *mem = AT(u8 *, cache, 0x128);
	void *at = mem ? mem + AT(int, cache, 0x12c) : NULL;
	int room = mem ? AT(int, cache, 0x124) - AT(int, cache, 0x12c) : 0;
	if (AT(int, cache, 0x110) == 2)
		skel_loadFromFile(sk, skelDat_getItemFileBy(key), at, room);
	else {
		char path[0x100];
		item_path(path, cache, own, STR(0x4c54f4, "ske"), STR(0x4c54f8, "ase"), (char *)IMG(0xa0eaa0), STR(0x4c54fc, "invalid file format(%s)-getSkeletonPt..."));
		skel_loadFrom(sk, path, at, room);
	}
	if (mem)
		AT(int, cache, 0x12c) += AT(int, sk, 4);
	AT(int, cache, 0x120)++;
	return sk;
}

/* 0x466dc0 (thiscall on a shape cache): the shape named name, as skel_getSkeletonPtrBy does it for skeletons: shape
   i (0x4c bytes each from +0x11c) loaded from the shape dat (shape_findDatEntry, shape_read) or a "shp" / "obj" file
   (model_loadFrom), its textures looked up (shape_bindTextureBy with the cache's texture sets +0x130 and seven values
   +0x230 ..); bound (shape_bindPartTextures) when bind is 1, found or added */
u8 *THISCALL (shape_getByName)(u8 *cache, const char *name, int bind)
{
	char key[0x100];
	strcpy(key, name);
	path_normalize(key);
	if (key[0] == 0 || key[0] == '.')
		return NULL;
	int added, i = tree_lookup(cache, key, (char *)IMG(0xa0e788), STR(0x4c4d98, "sizeOfShapeBuffer is zero-getShapePtr..."), STR(0x4c4d30, "shape overflow(%d)-getShapePtrBy()"), &added);
	u8 *shape = AT(u8 *, cache, 0x11c) + i * 0x4c;
	if (added) {
		const char *own = (const char *)AT(u8 *, cache, 0x118) + i * 0x4c;
		u8 *mem = AT(u8 *, cache, 0x128);
		void *at = mem ? mem + AT(int, cache, 0x12c) : NULL;
		int room = mem ? AT(int, cache, 0x124) - AT(int, cache, 0x12c) : 0;
		if (AT(int, cache, 0x110) == 2)
			shape_read(shape, shape_findDatEntry(key), at, room);
		else {
			char path[0x100];
			item_path(path, cache, own, STR(0x4c4d68, "shp"), STR(0x4c4d6c, "obj"), (char *)IMG(0xa0e788), STR(0x4c4d70, "invalid file format(%s)-getShapePtrBy()"));
			model_loadFrom(shape, path, at, room);
		}
		if (mem)
			AT(int, cache, 0x12c) += AT(int, shape, 4);
		shape_bindTextureBy(shape, cache + 0x130, AT(u32, cache, 0x230), AT(u32, cache, 0x234), AT(u32, cache, 0x238),
		                    AT(u32, cache, 0x23c), AT(u32, cache, 0x240), AT(u32, cache, 0x244), AT(u32, cache, 0x248));
		AT(int, cache, 0x120)++;
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
	Model_release(shape);
	crt_fread(shape, 0x34, 1, f);
	int current = AT(u32, shape, 0x30) == 0x71110300;
	if (!current) {
		long at = crt_ftell(f);
		crt_fseek(f, -4, 1);   /* SEEK_CUR */
		AT(int, shape, 4) += AT(int, shape, 0x10) * 0x18;
		crt_fseek(f, at, 0);   /* SEEK_SET */
	}
	take_block(shape, mem, size, (char *)IMG(0xa0e790), STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), 1);
	u8 *parts = AT(u8 *, shape, 0x14) = AT(u8 *, shape, 8);
	if (current)
		crt_fread(parts, 0x80, AT(u32, shape, 0x10), f);
	else
		for (int i = 0; i < AT(int, shape, 0x10); i++)
			crt_fread(AT(u8 *, shape, 0x14) + i * 0x80, 0x68, 1, f);
	int at = AT(int, shape, 0x10) * 0x80;
	for (int i = 0; i < AT(int, shape, 0x10); i++) {
		u8 *p = AT(u8 *, shape, 0x14) + i * 0x80;
		AT(int, p, 0x44) = -1;
		int n = AT(int, p, 0x4c);
		static const u8 sizes[4] = { 12, 12, 4, 8 };   /* vertices, normals, colours, texture coordinates */
		for (int t = 0; t < 4; t++) {
			AT(u8 *, p, 0x50 + t * 4) = AT(u8 *, shape, 8) + at;
			at += n * sizes[t];
		}
		for (int t = 0; t < 4; t++)
			crt_fread(AT(u8 *, p, 0x50 + t * 4), sizes[t], AT(u32, p, 0x4c), f);
		AT(u8 *, p, 0x64) = AT(u8 *, shape, 8) + at;
		crt_fread(AT(u8 *, p, 0x64), 0xc, AT(u32, p, 0x60), f);
		at += 0xc;
		for (int k = 0; k < AT(int, p, 0x60); k++) {
			u8 *prim = AT(u8 *, p, 0x64) + k * 0xc;
			AT(u8 *, prim, 8) = AT(u8 *, shape, 8) + at;
			crt_fread(AT(u8 *, prim, 8), 4, AT(u32, prim, 4), f);
			at += AT(int, prim, 4) * 4;
		}
	}
	if (!current)
		shape_relocate(shape);
	memcpy(shape + 0x34, shape + 0x20, 12);
	memcpy(shape + 0x40, shape + 0x20, 12);
	float *low = (float *)(RELOC(shape) + 0x34), *high = (float *)(RELOC(shape) + 0x40);
	for (int i = 0; i < AT(int, shape, 0x10); i++) {
		const float *box = (const float *)(AT(u8 *, shape, 0x14) + i * 0x80 + 0x68);
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
	if (AT(int, pose, 0x1c) <= 0)
		return;
	float saved[16], root[16];
	glGetFloatv(0xba6, saved);   /* GL_MODELVIEW_MATRIX */
	Mat4_copy(root, base ? base : saved);
	u8 **entry = AT(u8 **, pose, 0x20) + AT(int, pose, 0x24);
	if (!*entry)
		return;
	const float *unit = (const float *)IMG(0x4aa270), *point = (const float *)ADDR(g_vecOrigin);
	for (int i = 0; i < AT(int, pose, 0x10); i++) {
		u8 *sk = *entry;
		u8 *out = AT(u8 *, pose, 0x14) + i * 0x64;
		u8 *b = AT(u8 *, sk, 0x14) + i * 0x70;
		int frame = AT(int, pose, 0x28) % (AT(int, sk, 0x20) + 1);
		if (i >= AT(int, sk, 0x10))
			break;
		int parent = AT(int, b, 0x40);
		glLoadMatrixf(parent < 0 ? root : (const float *)(AT(u8 *, pose, 0x14) + parent * 0x64 + 0xc));
		const float *scale = (const float *)(out + 4);
		if (AT(int, b, 0x60) > 0) {
			int at = frame;
			float *key = (float *)key_at(AT(u8 *, b, 0x64), AT(int, b, 0x60), 0x20, &at);
			int length = ((int *)key)[1];
			long double f = length > 0 ? (long double)(at - ((int *)key)[0]) / length : fld_m((const float *)ADDR(k_0f));
			glTranslatef(fmul_m(fadd_m(fmul_m(f, &key[5]), &key[2]), scale), fmul_m(fadd_m(fmul_m(f, &key[6]), &key[3]), scale),
			             fmul_m(fadd_m(fmul_m(f, &key[7]), &key[4]), scale));
		} else
			glTranslatef(fmul_m(fld_m((const float *)(RELOC(b) + 0x44)), scale), fmul_m(fld_m((const float *)(RELOC(b) + 0x48)), scale),
			             fmul_m(fld_m((const float *)(RELOC(b) + 0x4c)), scale));
		if (AT(int, b, 0x68) > 0) {
			int at = frame;
			float *key = (float *)key_at(AT(u8 *, b, 0x6c), AT(int, b, 0x68), 0x28, &at);
			int length = ((int *)key)[1];
			float f = length > 0 ? f32((long double)(at - ((int *)key)[0]) / length) : 0;
			rotate(fmul_m(fld_m(&key[2]), unit), &key[3]);
			rotate(fmul_m(fmul_m(fld_m(&f), &key[6]), unit), &key[7]);
		} else
			rotate(fmul_m(fld_m((const float *)(RELOC(b) + 0x50)), unit), (const float *)(RELOC(b) + 0x54));
		float *m = (float *)(out + 0xc);
		glGetFloatv(0xba6, m);
		transform((float *)(out + 0x4c), m, &point[0], &point[1], &point[2]);
		const float *own = AT(const float *, out, 0);
		if (own) {
			for (int r = 0; r < 3; r++)   /* (here the z, x, y terms in that order for the y and z rows) */
				((float *)(out + 0x58))[r] = r == 0
					? f32(fadd_m(fmul_m(fld_m(&m[8]), &own[10]) + fmul_m(fld_m(&m[4]), &own[9]) + fmul_m(fld_m(&m[0]), &own[8]), &m[12]))
					: f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &own[10]) + fmul_m(fld_m(&m[r]), &own[8]) + fmul_m(fld_m(&m[4 + r]), &own[9]), &m[12 + r]));
		} else
			memcpy(out + 0x58, out + 0x4c, 12);
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
	char line[0x100], parent[0x40];
	Skeleton_release(sk);
	GAME_VAR(int, sk + 0x10) = GAME_VAR(int, sk + 0x1c) = GAME_VAR(int, sk + 0x18) = 0;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, (const char *)STR(0x4c5498, "* \t"));
		if (!strcmp(t, (const char *)STR(0x4c548c, "GEOMOBJECT")))
			GAME_VAR(int, sk + 0x10)++;
		else if (!strcmp(t, (const char *)STR(0x4c5478, "CONTROL_TCB_POS_KEY")) || !strcmp(t, (const char *)STR(0x4c5460, "CONTROL_BEZIER_POS_KEY")))
			GAME_VAR(int, sk + 0x18)++;
		else if (!strcmp(t, (const char *)STR(0x4c544c, "CONTROL_TCB_ROT_KEY")))
			GAME_VAR(int, sk + 0x1c)++;
	}
	int bones = GAME_VAR(int, sk + 0x10);
	if (bones <= 0)
		return;
	int size = GAME_VAR(int, sk + 4) = bones * 0x70 + GAME_VAR(int, sk + 0x1c) * 0x28 + GAME_VAR(int, sk + 0x18) * 0x20;
	if (!mem) {
		GAME_VAR(void *, sk + 8) = operator_new(size);
		if (!GAME_VAR(void *, sk + 8))
			sys_fatalError((char *)IMG(0xa0eaa8), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), GAME_VAR(int, sk + 4));
		GAME_VAR(int, sk + 0xc) = 1;
	} else {
		if (memSize < size)
			sys_fatalErrorN((char *)IMG(0xa0eaa8), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), size, memSize);
		GAME_VAR(u8 *, sk + 8) = mem;
		GAME_VAR(int, sk + 0xc) = 0;
	}
	GAME_VAR(u8 *, sk + 0x14) = GAME_VAR(u8 *, sk + 8);
	int keys = GAME_VAR(int, sk + 0x10) * 0x70;   /* where the next key list goes, after the bones */
	crt_fseek(f, 0, 0);
	int frames = 0, ms = 0x21, ticks = 0xa0, skip = -1, index = -1, at = -0x70;
	u8 *b = NULL;
	while (crt_fgets(line, 0x100, f)) {
		const char *t = crt_strtok(line, (const char *)STR(0x4c5498, "* \t"));
		if (!strcmp(t, (const char *)STR(0x4c543c, "SCENE_LASTFRAME")))   /* SCENE_LASTFRAME */
			frames = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, (const char *)STR(0x4c541c, "SCENE_FRAMESPEED"))) {   /* SCENE_FRAMESPEED */
			ms = 1000 / crt_atoi(TOKEN(LINE_END));
			GAME_VAR(int, sk + 0x20) = ms * frames;
		} else if (!strcmp(t, (const char *)STR(0x4c5408, "SCENE_TICKSPERFRAME")))   /* SCENE_TICKSPERFRAME */
			ticks = crt_atoi(TOKEN(LINE_END));
		else if (!strcmp(t, (const char *)STR(0x4c548c, "GEOMOBJECT"))) {   /* GEOMOBJECT */
			index++;
			skip = 0;
			at += 0x70;
			b = GAME_VAR(u8 *, sk + 0x14) + at;
			GAME_VAR(int, b + 0x40) = -1;
			GAME_VAR(int, b + 0x60) = GAME_VAR(int, b + 0x64) = GAME_VAR(int, b + 0x68) = GAME_VAR(int, b + 0x6c) = 0;
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
					if (!strcmp((const char *)GAME_VAR(u8 *, sk + 0x14) + j * 0x70, parent)) {
						GAME_VAR(int, b + 0x40) = j;
						break;
					}
			if (GAME_VAR(int, b + 0x40) < 0)
				sys_fatalError((char *)IMG(0xa0eaa8), (const char *)STR(0x4c53b8, "can't find parent part(%s)-loadAseFor..."), (int)parent);
		} else if (!strcmp(t, (const char *)STR(0x4c53b0, "TM_POS"))) {   /* TM_POS */
			GAME_VAR(float, b + 0x44) = ase_float(SPACE, 0);
			GAME_VAR(float, b + 0x4c) = ase_float(SPACE, 1);
			GAME_VAR(float, b + 0x48) = ase_float(LINE_END, 0);
		} else if (!strcmp(t, (const char *)STR(0x4c53a4, "TM_ROTAXIS"))) {   /* TM_ROTAXIS */
			GAME_VAR(float, b + 0x54) = ase_float(SPACE, 0);
			GAME_VAR(float, b + 0x5c) = ase_float(SPACE, 1);
			GAME_VAR(float, b + 0x58) = ase_float(LINE_END, 0);
		} else if (!strcmp(t, (const char *)STR(0x4c5398, "TM_ROTANGLE")))   /* TM_ROTANGLE */
			GAME_VAR(float, b + 0x50) = ase_float(LINE_END, 1);
		else if (!strcmp(t, (const char *)STR(0x4c5388, "CONTROL_POS_TCB")) || !strcmp(t, (const char *)STR(0x4c5374, "CONTROL_POS_BEZIER"))) {   /* CONTROL_POS_TCB / _BEZIER */
			GAME_VAR(u8 *, b + 0x64) = GAME_VAR(u8 *, sk + 8) + keys;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, (const char *)STR(0x4c535c, "* \t\n"));
				if (!strcmp(t, (const char *)STR(0x4c5478, "CONTROL_TCB_POS_KEY")) || !strcmp(t, (const char *)STR(0x4c5460, "CONTROL_BEZIER_POS_KEY"))) {
					u8 *k = GAME_VAR(u8 *, b + 0x64) + GAME_VAR(int, b + 0x60) * 0x20;
					GAME_VAR(int, k) = ase_time(ticks, ms);
					GAME_VAR(float, k + 8) = ase_float(SPACE, 0);
					GAME_VAR(float, k + 0x10) = ase_float(SPACE, 1);
					GAME_VAR(float, k + 0xc) = ase_float(SPACE, 0);
					GAME_VAR(int, b + 0x60)++;
				} else if (t && t[0] == '}')
					break;
			}
			keys += GAME_VAR(int, b + 0x60) * 0x20;
		} else if (!strcmp(t, (const char *)STR(0x4c5364, "CONTROL_ROT_TCB"))) {   /* CONTROL_ROT_TCB */
			GAME_VAR(u8 *, b + 0x6c) = GAME_VAR(u8 *, sk + 8) + keys;
			while (crt_fgets(line, 0x100, f)) {
				t = crt_strtok(line, (const char *)STR(0x4c535c, "* \t\n"));
				if (!strcmp(t, (const char *)STR(0x4c544c, "CONTROL_TCB_ROT_KEY"))) {
					u8 *k = GAME_VAR(u8 *, b + 0x6c) + GAME_VAR(int, b + 0x68) * 0x28;
					GAME_VAR(int, k) = ase_time(ticks, ms);
					GAME_VAR(float, k + 0xc) = ase_float(SPACE, 0);
					GAME_VAR(float, k + 0x14) = ase_float(SPACE, 1);
					GAME_VAR(float, k + 0x10) = ase_float(SPACE, 0);
					GAME_VAR(float, k + 8) = ase_float(SPACE, 1);
					if (GAME_VAR(int, b + 0x68) > 0) {
						float r[4];
						axisAngle_combine(r, (const float *)(RELOC(k) + 8), (const float *)(RELOC(k) + 8 - 0x28));
						memcpy(k + 8, r, 16);
					}
					GAME_VAR(int, b + 0x68)++;
				} else if (t && t[0] == '}')
					break;
			}
			keys += GAME_VAR(int, b + 0x68) * 0x28;
		}
	}
	u8 *all = GAME_VAR(u8 *, sk + 0x14);
	for (int i = GAME_VAR(int, sk + 0x10) - 1; i >= 0; i--) {
		u8 *bone = all + i * 0x70;
		if (GAME_VAR(int, bone + 0x40) < 0)
			continue;
		u8 *up = all + GAME_VAR(int, bone + 0x40) * 0x70;
		float t[16], r[16], m[16], inv[16], local[16], rel[16];
		translation(t, (const float *)(up + 0x44));
		Mat4_fromAxisAngle(r, (const float *)(up + 0x50));
		Mat4_multiply(m, t, r);
		Mat4_invert(inv, m);
		translation(t, (const float *)(RELOC(bone) + 0x44));
		Mat4_fromAxisAngle(r, (const float *)(RELOC(bone) + 0x50));
		Mat4_multiply(local, t, r);
		Mat4_multiply(rel, inv, local);
		for (int k = 0; k < 3; k++)
			GAME_VAR(float, bone + 0x44 + k * 4) = f32(fld_m(&rel[12 + k]));
		rel[12] = rel[13] = rel[14] = 0;
		axisAngle_fromMatrix((float *)(RELOC(bone) + 0x50), rel);
	}
	for (int i = 0; i < GAME_VAR(int, sk + 0x10); i++) {
		u8 *bone = GAME_VAR(u8 *, sk + 0x14) + i * 0x70;
		for (int k = 0; k < GAME_VAR(int, bone + 0x60) - 1; k++) {
			u8 *key = GAME_VAR(u8 *, bone + 0x64) + k * 0x20;
			GAME_VAR(int, key + 4) = GAME_VAR(int, key + 0x20) - GAME_VAR(int, key);
			for (int c = 0; c < 3; c++)
				GAME_VAR(float, key + 0x14 + c * 4) = f32(fsub_m(fld_m((const float *)(key + 0x28) + c), (const float *)(key + 8) + c));
		}
		if (GAME_VAR(int, bone + 0x60) > 0) {
			u8 *last = GAME_VAR(u8 *, bone + 0x64) + (GAME_VAR(int, bone + 0x60) - 1) * 0x20;
			GAME_VAR(int, last + 4) = 0;
			GAME_VAR(int, last + 0x14) = GAME_VAR(int, last + 0x18) = GAME_VAR(int, last + 0x1c) = 0;
		}
		for (int k = 0; k < GAME_VAR(int, bone + 0x68) - 1; k++) {
			u8 *key = GAME_VAR(u8 *, bone + 0x6c) + k * 0x28;
			GAME_VAR(int, key + 4) = GAME_VAR(int, key + 0x28) - GAME_VAR(int, key);
			float r[16], back[16], next[16], step[16];
			Mat4_fromAxisAngle(r, (const float *)(key + 8));
			Mat4_transpose(back, r);
			Mat4_fromAxisAngle(next, (const float *)(GAME_VAR(u8 *, bone + 0x6c) + k * 0x28 + 0x30));
			Mat4_multiply(step, back, next);
			axisAngle_fromMatrix((float *)(GAME_VAR(u8 *, bone + 0x6c) + k * 0x28 + 0x18), step);
		}
		if (GAME_VAR(int, bone + 0x68) > 0) {
			u8 *last = GAME_VAR(u8 *, bone + 0x6c) + (GAME_VAR(int, bone + 0x68) - 1) * 0x28;
			GAME_VAR(int, last + 4) = 0;
			GAME_VAR(int, last + 0x18) = GAME_VAR(int, last + 0x1c) = GAME_VAR(int, last + 0x20) = GAME_VAR(int, last + 0x24) = 0;
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
#define BAD_OBJ() sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4c20, "invalid obj format string(%s)-loadObj..."), (int)line)

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
	memcpy(GAME_VAR(u8 *, part + 0x50) + i * 12, vs + (crt_atoi(TOK(corner, SLASH)) - 1) * 3, 12);
	char *a = TOK(NULL, SLASH);
	if (!a)
		return 0;
	int ai = crt_atoi(a) - 1;
	char *b = TOK(NULL, SLASH);
	float *uv = GAME_VAR(float *, part + 0x5c) + i * 2;
	if (!b) {
		GAME_VAR(int, uv) = GAME_VAR(int, uv + 1) = 0;
		memcpy(GAME_VAR(u8 *, part + 0x54) + i * 12, ns + ai * 3, 12);
	} else {
		memcpy(uv, ts + ai * 2, 8);
		memcpy(GAME_VAR(u8 *, part + 0x54) + i * 12, ns + (crt_atoi(b) - 1) * 3, 12);
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
	char line[0x100], last[0x100], c[4][0x20];
	int nv = 0, nvn = 0, nvt = 0;
	Model_release(sh);
	GAME_VAR(int, sh + 0x10) = 0;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, (const char *)STR(0x4c4c64, "usemtl")))
			GAME_VAR(int, sh + 0x10)++;
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
				GAME_VAR(int, sh + 0x18) += 3;
				GAME_VAR(int, sh + 0x1c) += 1;
			} else {
				GAME_VAR(int, sh + 0x18) += 6;
				GAME_VAR(int, sh + 0x1c) += 2;
			}
		}
	}
	int parts = GAME_VAR(int, sh + 0x10);
	if (parts <= 0)
		return;
	int size = GAME_VAR(int, sh + 4) = (GAME_VAR(int, sh + 0x18) * 3 + GAME_VAR(int, sh + 0x1c)) * 0xc + parts * 0x8c;
	float *vs, *ns, *ts;
	int allocated;
	if (!mem) {
		GAME_VAR(void *, sh + 8) = operator_new(size);
		if (!GAME_VAR(void *, sh + 8))
			sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4bec, "insufficient memory for dataMemory(%d..."), GAME_VAR(int, sh + 4));
		GAME_VAR(int, sh + 0xc) = 1;
		if (!(vs = operator_new(nv * 12)))
			sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4bb4, "insufficient memory for vertexCoordAr..."), nv);
		if (!(ns = operator_new(nvn * 12)))
			sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4b78, "insufficient memory for vertexNormalA..."), nvn);
		if (!(ts = operator_new(nvt * 8)))
			sys_fatalError((char *)IMG(0xa0e790), (const char *)STR(0x4c4b38, "insufficient memory for vertexTexture..."), nvt);
		allocated = 1;
	} else {
		int need = nvt * 8 + (nvn + nv) * 0xc + size;
		if (memSize < need)
			sys_fatalErrorN((char *)IMG(0xa0e790), (const char *)STR(0x4c4b08, "reserved dataMemory overflow(%d/%d)-l..."), need, memSize);
		GAME_VAR(u8 *, sh + 8) = mem;
		GAME_VAR(int, sh + 0xc) = 0;
		vs = (float *)(mem + GAME_VAR(int, sh + 4));
		ns = (float *)(mem + GAME_VAR(int, sh + 4) + nv * 0xc);
		ts = (float *)(mem + GAME_VAR(int, sh + 4) + (nvn + nv) * 0xc);
		allocated = 0;
	}
	u8 *all = GAME_VAR(u8 *, sh + 0x14) = GAME_VAR(u8 *, sh + 8);
	int at = GAME_VAR(int, sh + 0x10) << 7;
	for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
		u8 *pt = all + k * 0x80;
		GAME_VAR(int, pt) = 0;
		GAME_VAR(int, pt + 0x44) = 0;
		for (int o = 0x4c; o <= 0x64; o += 4)
			GAME_VAR(int, pt + o) = 0;
	}
	crt_fseek(f, 0, 0);
	int off = -0x80;
	while (crt_fgets(line, 0x100, f)) {
		char *t = TOK(line, SPACE);
		if (!strcmp(t, (const char *)STR(0x4c4c64, "usemtl"))) {
			off += 0x80;
			GAME_VAR(int, GAME_VAR(u8 *, sh + 0x14) + 0x60 + off) = 1;
		} else if (!strcmp(t, (const char *)STR(0x4c4c54, "f"))) {
			if (!face_start(line, f))
				BAD_OBJ();
			for (int k = 0; k < 2; k++)
				if (!TOK(NULL, LINE_END))
					BAD_OBJ();
			GAME_VAR(int, GAME_VAR(u8 *, sh + 0x14) + 0x4c + off) += TOK(NULL, LINE_END) ? 6 : 3;
		}
	}
	int corner = 0;
	for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
		u8 *pt = GAME_VAR(u8 *, sh + 0x14) + k * 0x80, *data = GAME_VAR(u8 *, sh + 8);
		int n = GAME_VAR(int, pt + 0x4c);
		GAME_VAR(u8 *, pt + 0x50) = data + at;
		at += n * 12;
		GAME_VAR(u8 *, pt + 0x54) = data + at;
		at += n * 12;
		GAME_VAR(u8 *, pt + 0x58) = data + at;
		at += n * 4;
		GAME_VAR(int, pt + 0x48) = corner;
		corner += n;
		GAME_VAR(u8 *, pt + 0x5c) = data + at;
		at += n * 8;
		GAME_VAR(int, pt + 0x60) = 1;
		u32 *prim = GAME_VAR(u32 *, pt + 0x64) = (u32 *)(data + at);
		at += 0xc;
		prim[0] = 4;
		prim[1] = GAME_VAR(u32, pt + 0x4c);
		prim[2] = (u32)(GAME_VAR(u8 *, sh + 8) + at);
		at += GAME_VAR(int, pt + 0x4c) * 4;
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
				part = GAME_VAR(u8 *, sh + 0x14) + poff;
				poff += 0x80;
				for (char *piece = TOK(NULL, STR(0x4c4b04, "_")); piece; piece = TOK(NULL, STR(0x4c4b04, "_")))
					strcpy(last, piece);
				char *name = TOK(last, LINE_END);
				strcpy((char *)part + 4, name);
				part[(int)strlen(name) + 3] = 0;
				GAME_VAR(int, part + 0x44) = -1;
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
				float *pv = GAME_VAR(float *, part + 0x50), *pn;
				obj_corner(part, b, c[0], vs, ns, ts);
				obj_corner(part, b + 1, c[1], vs, ns, ts);
				if (!obj_corner(part, b + 2, c[2], vs, ns, ts)) {
					float tmp[3];
					pv = GAME_VAR(float *, part + 0x50);
					const float *nrm = math_triangleNormal(tmp, pv + b * 3, pv + (b + 1) * 3, pv + (b + 2) * 3);
					pn = GAME_VAR(float *, part + 0x54);
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
						pv = GAME_VAR(float *, part + 0x50);
						const float *nrm = math_triangleNormal(tmp, pv + q * 3, pv + (b + 4) * 3, pv + (b + 5) * 3);
						pn = GAME_VAR(float *, part + 0x54);
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
	for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
		u8 *pt = GAME_VAR(u8 *, sh + 0x14) + k * 0x80;
		for (int i = 0; i < GAME_VAR(int, pt + 0x4c); i++)
			GAME_VAR(u32 *, GAME_VAR(u8 *, pt + 0x64) + 8)[i] = i;
	}
	if (flip)
		for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
			u8 *pt = GAME_VAR(u8 *, sh + 0x14) + k * 0x80;
			while (GAME_VAR(int, pt + 0x4c) > 0) {   /* (never moves on, as the original) */
				k++;
				float *v = GAME_VAR(float *, pt + 0x50), *n = GAME_VAR(float *, pt + 0x54);
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
	for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
		u8 *pt = GAME_VAR(u8 *, sh + 0x14) + k * 0x80;
		for (int i = 0; i < GAME_VAR(int, pt + 0x4c); i++)
			GAME_VAR(u32 *, pt + 0x58)[i] = g_white;
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
	memcpy(sh + 0x34, sh + 0x20, 12);
	memcpy(sh + 0x40, sh + 0x20, 12);
	for (int k = 0; k < GAME_VAR(int, sh + 0x10); k++) {
		u8 *pt = GAME_VAR(u8 *, sh + 0x14) + k * 0x80;
		for (int a = 0; a < 3; a++)   /* (the values copied as bits: a NaN stays as it is) */
			if (fld_m((const float *)(sh + 0x34) + a) > *((const float *)(pt + 0x68) + a))
				memcpy(sh + 0x34 + a * 4, pt + 0x68 + a * 4, 4);
		for (int a = 0; a < 3; a++)
			if (!(fld_m((const float *)(sh + 0x40) + a) >= *((const float *)(pt + 0x74) + a)))
				memcpy(sh + 0x40 + a * 4, pt + 0x74 + a * 4, 4);
	}
}
#undef crt_fgets
#undef TOK
#undef SPACE
#undef LINE_END
#undef SLASH
#undef BAD_OBJ
