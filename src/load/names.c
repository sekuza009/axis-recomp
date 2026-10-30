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
int (shape_466ce0)(const char *name) { return name_search(0xa0e79c, 0xa0e7a0, name); }
int (skelDat_46b0c0)(const char *name) { return name_search(0xa0eab4, 0xa0eab8, name); }

/* 0x46cad0: src without its extension (from the last '.') copied to dst */
void (load_46cad0)(const char *src, char *dst)
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
int THISCALL (tex_4554c0)(u8 *self, const u8 *name)
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
	int i = tex_4554c0(manager, name);
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
	FUN_004569b0(sets);
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
