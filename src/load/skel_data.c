/* skel_data.c: a skeleton's data block: its header read or set, then one block (allocated, or the caller's memory
   when it is big enough, else a fatal message: the record out and the two messages given) laid out as the bones' records followed by their tables. */
#include "../game.h"
#include <string.h>

#define AT(type, p, offset) GAME_VAR(type, (u8 *)(p) + (offset))
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)

/* the block (+8; +4 its size): allocated (owned, +0xc 1) without memory given, else the memory given (owned 0 when
   own_flag; the caller's size checked) */
static void take_block(u8 *self, void *mem, int size, char *out, u32 no_memory, u32 too_small, int own_flag)
{
	if (!mem) {
		AT(void *, self, 8) = operator_new(AT(u32, self, 4));
		if (!AT(void *, self, 8))
			sys_fatalError(out, (const char *)no_memory, AT(int, self, 4));
		AT(int, self, 0xc) = 1;
	} else {
		if (size < AT(int, self, 4))
			sys_fatalErrorN(out, (const char *)too_small, AT(int, self, 4), size);
		AT(void *, self, 8) = mem;
		if (own_flag)
			AT(int, self, 0xc) = 0;
	}
}

/* 0x46aa10 (thiscall on a skeleton): read from f: the 0x24-byte header, the block (+8, its size +4), then the bones
   (0x70 bytes each, +0x10 of them, at the block's start: +0x14) and after them each bone's two tables (+0x60 keys of
   0x20 bytes at +0x64, +0x68 frames of 0x28 bytes at +0x6c). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom_46aa10)(u8 *self, void *f, void *mem, int size)
{
	FUN_004699a0(self);
	crt_fread(self, 0x24, 1, f);
	take_block(self, mem, size, (char *)0xa0eaa8, 0x4c4bec, 0x4c4b08, 1);
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
void THISCALL (skel_loadFrom_46aeb0)(u8 *self, const char *dir, int n, u32 a, int extra, void *mem, int size)
{
	load_46ae80(self);
	strcpy((char *)self + 0x10, dir ? dir : (const char *)0x4b1304);
	AT(u32, self, 0x110) = a;
	AT(int, self, 0x114) = n;
	AT(int, self, 0x124) = extra;
	AT(int, self, 4) = n * 0x70 + extra;
	take_block(self, mem, size, (char *)0xa0eaa0, 0x4c4bec, 0x4c4b08, 0);
	n = AT(int, self, 0x114);
	AT(u8 *, self, 0x118) = AT(u8 *, self, 8);
	AT(u8 *, self, 0x11c) = AT(u8 *, self, 8) + n * 0x4c;
	for (int i = 0; i < AT(int, self, 0x114); i++) {
		FUN_00469980(AT(u8 *, self, 0x11c) + i * 0x24);
		FUN_004699a0(AT(u8 *, self, 0x11c) + i * 0x24);
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
	load_466a30(self);
	if (dir && strcmp(dir, (const char *)0x4b1304) != 0)
		strcpy((char *)self + 0x10, dir);
	else
		self[0x10] = 0;
	FUN_0046cb60((char *)self + 0x10);
	AT(u32, self, 0x110) = a;
	AT(int, self, 0x114) = n;
	AT(int, self, 0x124) = extra;
	AT(int, self, 4) = n * 0x98 + extra;
	take_block(self, mem, size, (char *)0xa0e788, 0x4c4cec, 0x4c4cbc, 0);
	n = AT(int, self, 0x114);
	AT(u8 *, self, 0x118) = AT(u8 *, self, 8);
	AT(u8 *, self, 0x11c) = AT(u8 *, self, 8) + n * 0x4c;
	for (int i = 0; i < AT(int, self, 0x114); i++) {
		FUN_00464bb0(AT(u8 *, self, 0x11c) + i * 0x4c);
		FUN_00464bc0(AT(u8 *, self, 0x11c) + i * 0x4c);
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
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		sys_fatalError((char *)0xa0e790, (const char *)0x4c4ae4, (int)path);
	switch (file_format(path, "shp", "obj")) {
	case 0:
		shape_read(shape, f, mem, size);
		break;
	case 1:
		model_loadObjFormatFrom(shape, f, mem, size);
		break;
	default:
		sys_fatalError((char *)0xa0e790, (const char *)0x4c4aa4, (int)path);
	}
	fclose(f);
}

/* 0x4699d0 (thiscall on a skeleton): the same for skeletons: "ske" the binary format (skel_loadFrom_46aa10), "ase"
   ASCII scene export (skel_loadAseFrom). Its callers ignore the eax it leaves */
void THISCALL (skel_loadFrom)(u8 *sk, const char *path, void *mem, int size)
{
	void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
	if (!f)
		sys_fatalError((char *)0xa0eaa8, (const char *)0x4c4ae4, (int)path);
	switch (file_format(path, "ske", "ase")) {
	case 0:
		skel_loadFrom_46aa10(sk, f, mem, size);
		break;
	case 1:
		skel_loadAseFrom(sk, f, mem, size);
		break;
	default:
		sys_fatalError((char *)0xa0eaa8, (const char *)0x4c4aa4, (int)path);
	}
	fclose(f);
}

/* 0x46f4e0 (thiscall on an object list): emptied (FUN_0046f4b0), then ns shapes (by the names 0x44 apart, each with
   an int at +0x40; looked up in the shape cache, the first 64 once, any later ones again when the entries are
   filled) with their element counts summed (+0x18), and nk skeletons (by the names 0x40 apart). Its block (+8, size
   +4: 100 bytes a shape, 4 a skeleton, lit == 1 a colour per element too): allocated (owned, +0xc 1; none a fatal
   message) without memory given, else that memory (too small: a fatal message). The entries (+0x14: shape, int,
   colours when lit and found), the skeletons after them (+0x20), and lit, the colours worked out (data_46f7a0). Its
   callers ignore the eax it leaves */
void THISCALL (data_loadFrom_46f4e0)(u8 *list, void *shapes, void *skels, int ns, const u8 *names, int nk, const u8 *knames,
                                     int lit, u32 factors, u32 lights, void *mem, int size)
{
	FUN_0046f4b0(list);
	AT(int, list, 0x10) = ns;
	AT(int, list, 0x1c) = nk;
	AT(int, list, 0x2c) = lit;
	AT(int, list, 0x18) = 0;
	u32 found[64];
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
			sys_fatalError((char *)0xae2e98, (const char *)0x4c4bec, AT(int, list, 4));
		AT(int, list, 0xc) = 1;
	} else {
		if (size < AT(int, list, 4))
			sys_fatalErrorN((char *)0xae2e98, (const char *)0x4c4b08, AT(int, list, 4), size);
		AT(void *, list, 8) = mem;
	}
	AT(u8 *, list, 0x14) = AT(u8 *, list, 8);
	int colours = AT(int, list, 0x10) * 100;
	for (int i = 0; i < AT(int, list, 0x10); i++) {
		u32 *entry = (u32 *)(AT(u8 *, list, 0x14) + i * 100);
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
		data_46f7a0(list, factors, lights);
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
	const float *unit = (const float *)0x4aa270;
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
		long double f = length > 0 ? (long double)(frame - ((int *)key)[0]) / length : fld_m((const float *)0x4a93e8);
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
		rotate(fmul_m(fld_m((const float *)(b + 0x50)), unit), (const float *)(b + 0x54));
	glGetFloatv(0xba6, (float *)out);
	glLoadMatrixf(saved);
}
