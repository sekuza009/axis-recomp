/* names.c: looking resources up by name in the managers' sorted name tables (0x44-byte entries), and file names. */
#include "../game.h"
#include <string.h>

/* strcmp, as -1 / 0 / 1 (bytes compared unsigned) */
static int name_cmp(const char *a, const char *b)
{
	for (;; a++, b++) {
		if (*a != *b)
			return (u8)*a < (u8)*b ? -1 : 1;
		if (*a == '\0')
			return 0;
	}
}

/* binary search of name in the table at *table (count at *count; the search starts with hi = count); -1 when not
   found */
static int name_search(u32 count, u32 table, const char *name)
{
	int lo = 0, hi = GAME_VAR(int, count);
	if (hi <= 0)
		return -1;
	while (lo <= hi) {
		int mid = (lo + hi) / 2;
		int r = name_cmp(name, (const char *)(GAME_VAR(u32, table) + mid * 0x44));
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
