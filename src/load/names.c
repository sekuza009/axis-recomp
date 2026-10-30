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
