/* names.c: looking resources up by name in the managers' sorted name tables (0x44-byte entries), and file names. */
#include "../game.h"

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))
#include <string.h>

/* binary search of name in the table at *table (count at *count; the search starts with hi = count); -1 when not
   found */
static int name_search(u32 count, u32 table, const char *name)
{
	int lo = 0, hi = GAME_VAR(int, count);
	if (hi <= 0)
		return -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int r = str_order(name, (const char *)(GAME_VAR(u32, table) + mid * 0x44));
		if (r == 0)
			return mid;
		if (r < 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

/* 0x466ce0: a shape by name; 0x46b0c0: a skeleton data file by name */
int (shape_findByName)(const char *name) { return name_search(0xa0e79c, 0xa0e7a0, name); }
int (skelDat_46b0c0)(const char *name) { return name_search(0xa0eab4, 0xa0eab8, name); }

/* 0x46cad0: src without its extension (from the last '.') copied to dst */
void (path_stripExtension)(const char *src, char *dst)
{
	char buf[256];
	strcpy(buf, src);
	for (int i = (int)strlen(buf) - 1; i >= 0; i--)
		if (buf[i] == '.') {
			buf[i] = '\0';
			break;
		}
	strcpy(dst, buf);
}

/* 0x4554c0: a texture manager's name, by binary search of its sorted 0x44-byte records (+0x10c, count +0x108): the
   index or -1. The upper bound starts at the count, not count - 1, as in the original */
int THISCALL (tex_findByName)(u8 *self, const u8 *name)
{
	int hi = FIELD(int, self, 0x108), lo = 0;
	if (hi <= 0)
		return -1;
	const u8 *records = FIELD(const u8 *, self, 0x10c);
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		const u8 *a = name, *b = records + mid * 0x44;
		while (*a == *b && *a)
			a++, b++;
		int c = *a == *b ? 0 : *a < *b ? -1 : 1;
		if (c == 0)
			return mid;
		if (c < 0)
			hi = mid - 1;
		else
			lo = mid + 1;
	}
	return -1;
}

/* 0x455550 (thiscall on a texture manager): the item named, its file (+0x110) moved to where the item starts (its
   0x44-byte record at +0x10c, +0x40); returns the file, or 0 after a fatal message when there is no such item */
void *THISCALL (tex_getItemFileBy)(u8 *manager, const char *name)
{
	int i = tex_findByName(manager, name);
	if (i < 0) {
		sys_fatalError((char *)0xa0dff8, (const char *)0x4b3f80, (int)name);
		return 0;
	}
	crt_fseek(GAME_VAR(void *, manager + 0x110), GAME_VAR(long, GAME_VAR(u8 *, manager + 0x10c) + i * 0x44 + 0x40), 0);
	return GAME_VAR(void *, manager + 0x110);
}

/* 0x456be0 (thiscall on the texture sets): a texture's id by name: each of the six managers (+4 ..) asked in turn
   (tex_allocIdBy, with the rest of the arguments); the first answer k x 512 + its index. None: a fatal message, -1 */
int THISCALL (tex_getIdByName)(u8 *sets, const char *name, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g)
{
	for (int k = 0; k < 6; k++) {
		void *manager = GAME_VAR(void *, sets + 4 + k * 4);
		if (!manager)
			continue;
		int i = tex_allocIdBy(manager, (u32)name, a, b, c, d, e, f, g);
		if (i >= 0)
			return k * 512 + i;
	}
	sys_fatalError((char *)0xa0e000, (const char *)0x4b42b0, (int)name);
	return -1;
}

/* 0x466430 (thiscall on a shape): each of its parts (0x80 bytes from +0x14, +0x10 of them) given its texture (+0x44:
   tex_getIdByName on the game's texture sets, 0xa0e010, by the part's name at +4, the rest of the arguments passed on);
   with a suffix the name gets 0x4b12f4 and the suffix appended first (too long for the 0x40 bytes: a fatal message
   first). Its callers ignore the eax it leaves */
void THISCALL (shape_bindTextureBy)(u8 *shape, const char *suffix, int flags, int a, int b, int c, int d, int e, int f)
{
	for (int i = 0; i < GAME_VAR(int, shape + 0x10); i++) {
		u8 *part = GAME_VAR(u8 *, shape + 0x14) + i * 0x80;
		char *name = (char *)part + 4;
		if (*suffix) {
			if (strlen(name) + strlen(suffix) > 0x3f)
				sys_fatalErrorN((char *)0xa0e790, (const char *)0x4c4c6c, name, suffix);
			strcat(name, (const char *)0x4b12f4);
			strcat(name, suffix);
		}
		GAME_VAR(int, part + 0x44) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, flags, a, b, c, d, e, f);
	}
}

/* 0x4566c0 (thiscall on a texture manager): texture i bound, through the cache of GL textures (0x14-byte slots from
   +0xcd12c: their index, the texture in them, the GL id, next and previous in a ring, +0xcd134 the oldest). Not in the
   cache (its slot, +0xc0168 in its 0x68-byte record, negative): the oldest slot taken and the texture loaded into it
   (tinted when its flags, +0xc016c, have 2; mipmapped unless they have 1; +0xcd138 counts the loads); in it but changed
   (+0xc018c 1): loaded again; else just bound. The slot then becomes the newest: when it was the oldest the next one is
   (and that one's texture loses its slot), else it moves to just before the oldest. Its callers ignore the eax it leaves */
void THISCALL (tex_bind)(u8 *tm, int i)
{
#define AT(type, p, offset) GAME_VAR(type, (u8 *)(p) + (offset))
#define OLDEST AT(u8 *, tm, 0xcd134)
	u8 *texture = tm + i * 0x68;
	u8 *slot;
	if (AT(int, texture, 0xc0168) < 0) {
		slot = OLDEST;
		AT(int, slot, 4) = i;
		tex_loadColorMask(tm, i);
		if (AT(u8, texture, 0xc016c) & 2)
			tex_applyTintMask(tm, i);
		tex_upload(tm, AT(u32, slot, 8), AT(u8, texture, 0xc016c) & 1 ? 0 : 1);
		AT(int, tm, 0xcd138)++;
	} else {
		slot = AT(u8 *, tm, 0xcd12c) + AT(int, texture, 0xc0168) * 0x14;
		if (AT(int, texture, 0xc018c) == 1) {
			tex_loadColorMask(tm, i);
			if (AT(u8, texture, 0xc016c) & 2)
				tex_applyTintMask(tm, i);
			tex_upload(tm, AT(u32, slot, 8), AT(u8, texture, 0xc016c) & 1 ? 0 : 1);
			AT(int, tm, 0xcd138)++;
			AT(int, texture, 0xc018c) = 0;
		} else
			glBindTexture(0xde1, AT(u32, slot, 8));   /* GL_TEXTURE_2D */
	}
	if (slot == OLDEST) {
		OLDEST = AT(u8 *, slot, 0xc);
		AT(int, tm + AT(int, OLDEST, 4) * 0x68, 0xc0168) = -1;
	} else {
		AT(u8 *, AT(u8 *, slot, 0xc), 0x10) = AT(u8 *, slot, 0x10);
		AT(u8 *, AT(u8 *, slot, 0x10), 0xc) = AT(u8 *, slot, 0xc);
		u8 *oldest = OLDEST;
		AT(u8 *, slot, 0xc) = oldest;
		AT(u8 *, slot, 0x10) = AT(u8 *, OLDEST, 0x10);
		AT(u8 *, oldest, 0x10) = slot;
		AT(u8 *, AT(u8 *, slot, 0x10), 0xc) = slot;
	}
	AT(int, slot, 4) = i;
	AT(int, texture, 0xc0168) = AT(int, slot, 0);
#undef AT
#undef OLDEST
}

/* 0x4569d0 (thiscall on the texture sets): the six managers kept (+4 .. +0x18), each (when given) checked for its
   size: 64 x 64, 128 x 64, 256 x 64, 128 x 128, 256 x 128, 256 x 256 (its +0xc0118 / +0xc011c), a fatal message
   with the size found otherwise. Its caller ignores the eax it leaves */
void THISCALL (texSmall_initBy)(u8 *sets, u8 *a, u8 *b, u8 *c, u8 *d, u8 *e, u8 *f)
{
	static const u32 sizes[6][3] = { { 64, 64, 0x4b4278 }, { 128, 64, 0x4b423c }, { 256, 64, 0x4b4200 },
	                                 { 128, 128, 0x4b41c4 }, { 256, 128, 0x4b4188 }, { 256, 256, 0x4b414c } };
	u8 *managers[6] = { a, b, c, d, e, f };
	TextureManager_reset(sets);
	for (int k = 0; k < 6; k++) {
		u8 *m = managers[k];
		if (m && (GAME_VAR(u32, m + 0xc0118) != sizes[k][0] || GAME_VAR(u32, m + 0xc011c) != sizes[k][1]))
			sys_fatalErrorN((char *)0xa0e000, (const char *)sizes[k][2], GAME_VAR(int, m + 0xc0118), GAME_VAR(int, m + 0xc011c));
	}
	for (int k = 0; k < 6; k++)
		GAME_VAR(u8 *, sets + 4 + k * 4) = managers[k];
}

/* 0x456520 (thiscall on a texture manager): its pixels (+0x114, +0xc0118 x +0xc011c) uploaded to GL texture id: wrapped
   (mode 1: repeat, else clamp), filtered linearly or not (+0xc0124 1), with mipmaps (+0xc0120 1: built by
   gluBuild2DMipmaps after the first level) or without. Its callers ignore the eax it leaves */
void THISCALL (tex_upload)(u8 *tm, u32 id, int mode)
{
	glPixelStorei(0xcf5, 1);   /* GL_UNPACK_ALIGNMENT */
	glBindTexture(0xde1, id);
	u32 wrap = mode == 1 ? 0x46240400 : 0x46240000;   /* GL_REPEAT : GL_CLAMP */
	glTexParameterf_bits(0xde1, 0x2802, wrap);
	glTexParameterf_bits(0xde1, 0x2803, wrap);
	int linear = GAME_VAR(int, tm + 0xc0124) == 1;
	int mipmaps = GAME_VAR(int, tm + 0xc0120) == 1;
	glTexParameterf_bits(0xde1, 0x2800, linear ? 0x46180400 : 0x46180000);   /* mag: GL_LINEAR : GL_NEAREST */
	glTexParameterf_bits(0xde1, 0x2801, mipmaps ? (linear ? 0x461c0c00 : 0x461c0000) : (linear ? 0x46180400 : 0x46180000));
	glTexImage2D(0xde1, 0, 4, GAME_VAR(int, tm + 0xc0118), GAME_VAR(int, tm + 0xc011c), 0, 0x1908, 0x1401, tm + 0x114);
	if (mipmaps)
		gluBuild2DMipmaps(0xde1, 4, GAME_VAR(int, tm + 0xc0118), GAME_VAR(int, tm + 0xc011c), 0x1908, 0x1401, tm + 0x114);
}

/* 0x4557e0 (thiscall on a texture manager): is the texture name (up to a '*') there in the manager's format (+0xc0114,
   under its directory +8 when it has one) at its size (+0xc0118 x +0xc011c)? 0: in the dat index (tex_findByName); 1: a
   BMP of that size; 2: a RAW whose header (at 6, two shorts in 8-pixel units) gives it; else a fatal message. 1 or
   0, the local image (a BMPRGBFile) closed either way */
int THISCALL (tex_textureFileExist)(u8 *tm, const char *name)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
	static const u32 formats[3][2] = { { 0x4b3fdc, 0x4b3fd8 }, { 0x4b3fec, 0x4b3fe4 }, { 0x4b4000, 0x4b3ff8 } };   /* "%s\%s" "%s", .BMP, .RAW */
	u8 image[0x48];
	FIELD(u32, image, 0) = 0x4a96f8;   /* (its vtable) */
	FIELD(u32, image, 4) = 0;          /* (no file yet) */
	char base[0x100], path[0x100];
	strcpy(base, name);
	crt_strtok(base, (const char *)0x4b12f4);   /* "*" */
	const char *dir = (const char *)tm + 8;
	int format = FIELD(int, tm, 0xc0114), ok = 0;
	if ((unsigned)format > 2)
		sys_fatalError((char *)0xa0dff8, (const char *)0x4b400c, format);
	else {
		if (*dir)
			sprintf(path, (const char *)formats[format][0], dir, base);
		else
			sprintf(path, (const char *)formats[format][1], base);
		if (format == 0)
			ok = tex_findByName(tm, path) >= 0;
		else if (format == 1) {
			if (file_exists_46ca70(path)) {
				image_initBy(image, path);
				int w = FIELD(int, image, 0x3e), h = FIELD(int, image, 0x42);
				BMPRGBFile_close(image);
				ok = w == FIELD(int, tm, 0xc0118) && h == FIELD(int, tm, 0xc011c);
			}
		} else {
			void *f = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
			if (f) {
				short size[2];
				crt_fseek(f, 6, 0);
				crt_fread(&size[0], 2, 1, f);
				crt_fread(&size[1], 2, 1, f);
				fclose(f);
				ok = size[0] * 8 == FIELD(int, tm, 0xc0118) && size[1] * 8 == FIELD(int, tm, 0xc011c);
			}
		}
	}
	BMPRGBFile_ctor(image);   /* (by use its destructor) */
	return ok;
#undef crt_fread
}

/* 0x455080 (thiscall on a texture manager): set up (twice is a fatal message): its directory (+8, upper-cased; none or
   0x4b1304 empty), format, size and filtering (+0xc0114 .. +0xc0124). The dat format (0) opens its image file for
   the size (Data\Image64.dat ..., by 0x4b3f20 for another size; none a fatal message: kept open at +0x110) and reads
   its index (a count +0x108, then that many 0x44-byte entries at +0x10c; no memory a fatal message). Then up to 0x200
   texture slots (+0xcd130 of them, 0x14 bytes at +0xcd12c: its index, id -1, a GL texture name, previous and next in a
   ring), the oldest +0xcd134, the counts +0xcd128 / +0xcd138 .. cleared; set up (+4 1). Its callers ignore the eax
   it leaves */
void THISCALL (tex_initBy)(u8 *tm, const char *dir, int slots, int format, int w, int h, int linear, int mipmaps)
{
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define fatal(text, ...) GAME_CDECL(0x46c710, void, char *, const char *, ...)((char *)0xa0dff8, (const char *)(text), ##__VA_ARGS__)
	static const u32 names[6][3] = { { 64, 64, 0x4b3f54 }, { 128, 64, 0x4b3f4c }, { 128, 128, 0x4b3f3c },
	                                 { 256, 64, 0x4b3f44 }, { 256, 128, 0x4b3f34 }, { 256, 256, 0x4b3f2c } };
	if (FIELD(int, tm, 4) == 1)
		fatal(0x4b3f5c);
	char *own = (char *)tm + 8;
	if (dir && strcmp(dir, (const char *)0x4b1304) != 0)
		strcpy(own, dir);
	else
		own[0] = 0;
	path_normalize(own);
	FIELD(int, tm, 0xc0124) = linear;
	FIELD(int, tm, 0xc0114) = format;
	FIELD(int, tm, 0xc0118) = w;
	FIELD(int, tm, 0xc011c) = h;
	FIELD(int, tm, 0xc0120) = mipmaps;
	if (format == 0) {
		char name[0x100], path[0x100];
		int k = 0;
		while (k < 6 && !(names[k][0] == (u32)w && names[k][1] == (u32)h))
			k++;
		if (k < 6)
			strcpy(name, (const char *)names[k][2]);
		else
			sprintf(name, (const char *)0x4b3f20, w, h);
		if (*own)
			sprintf(path, (const char *)0x4b3f10, own, name);
		else
			sprintf(path, (const char *)0x4b3f04, name);
		FIELD(void *, tm, 0x110) = crt_fopen(path, (const char *)0x4ad170);   /* "rb" */
		if (!FIELD(void *, tm, 0x110))
			fatal(0x4b3ee4, path);
		crt_fread(tm + 0x108, 4, 1, FIELD(void *, tm, 0x110));
		FIELD(void *, tm, 0x10c) = operator_new(FIELD(u32, tm, 0x108) * 0x44);
		if (!FIELD(void *, tm, 0x10c))
			fatal(0x4b3eb4, FIELD(int, tm, 0x108));
		crt_fread(FIELD(void *, tm, 0x10c), 0x44, FIELD(u32, tm, 0x108), FIELD(void *, tm, 0x110));
	} else {
		FIELD(int, tm, 0x108) = 0;
		FIELD(void *, tm, 0x10c) = NULL;
		FIELD(void *, tm, 0x110) = NULL;
	}
	FIELD(int, tm, 0xcd128) = 0;
	FIELD(int, tm, 0xcd130) = slots > 0x200 ? 0x200 : slots;
	FIELD(u8 *, tm, 0xcd12c) = operator_new(FIELD(int, tm, 0xcd130) * 0x14);
	if (!FIELD(u8 *, tm, 0xcd12c))
		fatal(0x4b3e84, FIELD(int, tm, 0xcd130));
	for (int i = 0; i < FIELD(int, tm, 0xcd130); i++) {
		u32 *slot = (u32 *)(FIELD(u8 *, tm, 0xcd12c) + i * 0x14);
		slot[0] = i;
		slot[1] = 0xffffffff;
		IMPORT(0x4a925c, void, int, u32 *)(1, &slot[2]);   /* glGenTextures */
		int n = FIELD(int, tm, 0xcd130);
		slot[3] = (u32)(FIELD(u8 *, tm, 0xcd12c) + (n + i - 1) % n * 0x14);
		slot[4] = (u32)(FIELD(u8 *, tm, 0xcd12c) + (i + 1) % FIELD(int, tm, 0xcd130) * 0x14);
	}
	FIELD(int, tm, 0xcd138) = 0;
	FIELD(int, tm, 0xcd13c) = 0;
	FIELD(int, tm, 0xcd140) = 0;
	FIELD(u8 *, tm, 0xcd134) = FIELD(u8 *, tm, 0xcd12c);
	FIELD(int, tm, 4) = 1;
#undef crt_fread
#undef fatal
}

/* 0x4555b0 (thiscall on a texture manager): the record for texture name (upper-cased; empty: -1) with flags and two
   colours (h1 s1 v1, h2 s2 v2): among the +0xcd128 records (0x68 bytes from +0xc0128: the name, flags +0x44, the
   colours +0x48 ..) a hit keeps it as it is when flags and colours match (a NaN matches anything, as fcom has it),
   else takes them and is recoloured (tex_recolourMaterial). A miss whose file is there (tex_textureFileExist; else
   -1) gets a new record (at most 512: a fatal message), bound at once (tex_bind) while the count is below +0xcd130.
   Returns the record's index */
int THISCALL (tex_allocIdBy)(u8 *tm, const char *name, u32 flags, u32 h1, u32 s1, u32 v1, u32 h2, u32 s2, u32 v2)
{
	/* the two colours (h1 s1 v1, h2 s2 v2) read where the caller put them, through a volatile pointer: clang would
	   otherwise copy them into the frame. The frame then holds only the name and is as deep as the original's (0x50
	   with the saved registers): tex_textureFileExist reads a short file's size words from stack it never wrote,
	   and a deeper frame gave those reads other values now and then */
	const volatile u32 *colour = &h1;
	(void)s1, (void)v1, (void)h2, (void)s2, (void)v2;
	char key[0x40];
	strcpy(key, name);
	path_normalize(key);
	if (!key[0])
		return -1;
	int i = 0;
	for (; i < FIELD(int, tm, 0xcd128); i++) {
		u8 *rec = tm + 0xc0128 + i * 0x68;
		if (strcmp((const char *)rec, key))
			continue;
		const float *c = (const float *)(rec + 0x48);
#define SAME(a, k) (!((a) < fld_m((const float *)&colour[k])) && !((a) > fld_m((const float *)&colour[k])))
		if (FIELD(u32, rec, 0x44) == flags && SAME(c[0], 0) && SAME(c[2], 2) && SAME(c[1], 1) && SAME(c[3], 3) &&
		    SAME(c[5], 5) && SAME(c[4], 4))
			return i;
#undef SAME
		FIELD(u32, rec, 0x44) = flags;
		tex_recolourMaterial(tm, i, colour[0], colour[1], colour[2], colour[3], colour[4], colour[5]);
		return i;
	}
	if (!tex_textureFileExist(tm, key))
		return -1;
	if (FIELD(int, tm, 0xcd128) < 0x200) {
		i = FIELD(int, tm, 0xcd128);
		tex_454e60(tm + 0xc0128 + i * 0x68, key, -1, flags, colour[0], colour[1], colour[2], colour[3], colour[4], colour[5]);
		FIELD(int, tm, 0xcd128)++;
	} else
		sys_fatalErrorN((char *)0xa0dff8, (const char *)0x4b3fa8, FIELD(int, tm, 0xc0118), FIELD(int, tm, 0xc011c), 0x200);
	if (FIELD(int, tm, 0xcd128) < FIELD(int, tm, 0xcd130))
		tex_bind(tm, i);
	return i;
}

#define W(m) GAME_VAR(int, (m) + 0xc0118)
#define H(m) GAME_VAR(int, (m) + 0xc011c)

/* path: the texture name in the given format, under the manager's directory (+8) when it has one */
static void tex_path(u8 *m, char *path, u32 with_dir, u32 plain, const char *name)
{
	if (m[8])
		sprintf(path, (const char *)with_dir, (const char *)m + 8, name);
	else
		sprintf(path, (const char *)plain, name);
}

/* a decoded image of another size than the manager's is fatal */
static void size_check(u8 *m, int w, int h)
{
	if (W(m) != w || H(m) != h)
		GAME_CDECL(0x46c710, void, char *, const char *, int, int, int, int)((char *)0xa0dff8, (const char *)0x4b4104, W(m), H(m), w, h);
}

/* the image's alpha (the 4th bytes from +0x114): the grey of the ALPHA image at +0x40114, or opaque */
static void alpha_from(u8 *m, int have)
{
	for (int y = 0; y < H(m); y++)
		for (int x = 0; x < W(m); x++) {
			u8 *px = m + (y * W(m) + x) * 4;
			px[0x117] = have ? (u8)((px[0x40116] + px[0x40115] + px[0x40114]) / 3) : 0xff;
		}
}

/* no colour mask: every pixel of +0x80114 the colour at 0xa1f238 */
static void colour_fill(u8 *m)
{
	for (int y = 0; y < H(m); y++)
		for (int x = 0; x < W(m); x++)
			GAME_VAR(u32, m + 0x80114 + (y * W(m) + x) * 4) = GAME_VAR(u32, 0xa1f238);
}

/* 0x455aa0 (thiscall on the texture manager): texture i's image (its name +0xc0128 + i * 0x68 cut at '*') loaded at
   +0x114, its alpha (alpha_from) and its colour mask at +0x80114 (or colour_fill), by the manager's format +0xc0114:
   0 items of the texture dat (name, name_ALPHA, name_COLOR: tex_findByName / tex_getItemFileBy, the decoder's tables set
   up on first use, 0xa0e00c), 1 BMP files (name.BMP must open), 2 PTX files (name.RAW, name_ALPHA.RAW,
   name_COLOR.RAW); a PTX of another size than +0xc0118 x +0xc011c is fatal. (The original's SEH frame, for its BMP
   objects, is not reproduced.) Its callers ignore the eax it leaves */
void THISCALL (tex_loadColorMask)(u8 *m, int i)
{
	u32 bmp[3][0x12];   /* BMP reader objects (vtable 0x4a96f8) for the image, the alpha, the mask */
	for (int k = 0; k < 3; k++) {
		bmp[k][0] = 0x4a96f8;
		bmp[k][1] = 0;
	}
	char name[0x100], path[0x190];
	int bpp, w, h;
	strcpy(name, (const char *)m + 0xc0128 + i * 0x68);
	crt_strtok(name, (const char *)0x4b12f4);
	switch (GAME_VAR(int, m + 0xc0114)) {
	case 0:
		if (!g_ptxTablesReady) {
			ptx_initTables();
			g_ptxTablesReady = 1;
		}
		tex_path(m, path, 0x4b3fdc, 0x4b3fd8, name);
		ptx_decode(tex_getItemFileBy(m, path), m + 0x114, &bpp, &w, &h);
		size_check(m, w, h);
		tex_path(m, path, 0x4b405c, 0x4b4050, name);
		if (tex_findByName(m, (const u8 *)path) >= 0) {
			ptx_decode(tex_getItemFileBy(m, path), m + 0x40114, &bpp, &w, &h);
			size_check(m, w, h);
			alpha_from(m, 1);
		} else
			alpha_from(m, 0);
		tex_path(m, path, 0x4b4044, 0x4b4038, name);
		if (tex_findByName(m, (const u8 *)path) >= 0) {
			ptx_decode(tex_getItemFileBy(m, path), m + 0x80114, &bpp, &w, &h);
			size_check(m, w, h);
		} else
			colour_fill(m);
		break;
	case 1:
		tex_path(m, path, 0x4b3fec, 0x4b3fe4, name);
		if (!image_initBy(bmp[0], path))
			sys_fatalError((char *)0xa0dff8, (const char *)0x4b40a8, (int)path);
		image_copyTo(bmp[0], m + 0x114, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
		tex_path(m, path, 0x4b4098, 0x4b4088, name);
		if (image_initBy(bmp[1], path)) {
			image_copyTo(bmp[1], m + 0x40114, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
			alpha_from(m, 1);
			BMPRGBFile_close(bmp[1]);
		} else
			alpha_from(m, 0);
		tex_path(m, path, 0x4b4078, 0x4b4068, name);
		if (image_initBy(bmp[2], path)) {
			image_copyTo(bmp[2], m + 0x80114, W(m), H(m), 4, 0, 0, 0, 0, W(m), H(m), 0);
			BMPRGBFile_close(bmp[2]);
		} else
			colour_fill(m);
		break;
	case 2: {
		if (!g_ptxTablesReady) {
			ptx_initTables();
			g_ptxTablesReady = 1;
		}
		tex_path(m, path, 0x4b4000, 0x4b3ff8, name);
		ptx_open(path, m + 0x114, &bpp, &w, &h);
		size_check(m, w, h);
		tex_path(m, path, 0x4b40f4, 0x4b40e4, name);
		void *f = crt_fopen(path, (const char *)0x4ad170);
		if (f) {
			ptx_decode(f, m + 0x40114, &bpp, &w, &h);
			size_check(m, w, h);
			alpha_from(m, 1);
		} else
			alpha_from(m, 0);
		tex_path(m, path, 0x4b40d4, 0x4b40c4, name);
		f = crt_fopen(path, (const char *)0x4ad170);
		if (f) {
			ptx_decode(f, m + 0x80114, &bpp, &w, &h);
			size_check(m, w, h);
		} else
			colour_fill(m);
		break;
	}
	}
	for (int k = 2; k >= 0; k--)
		BMPRGBFile_ctor(bmp[k]);   /* (the reader's destructor) */
}
#undef W
#undef H
