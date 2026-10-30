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
