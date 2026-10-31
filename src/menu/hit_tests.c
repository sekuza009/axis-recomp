/* hit_tests.c: the screens' button hit tests. Each screen keeps its buttons as a table of rectangles in menu units
   (left, top, right, bottom; 16 bytes each); a hit test gives the index of the first rectangle holding the point, or
   -1. The game has 31 copies of the same code, one per table. */
#include "../game.h"
#include <stdarg.h>

/* the first of the rectangles from table (count of them) holding (x, y), or -1 */
static int hit(int x, int y, const int *table, int count)
{
	for (int i = 0; i < count; i++) {
		const int *r = table + i * 4;
		if (x >= r[0] && x <= r[2] && y >= r[1] && y <= r[3])
			return i;
	}
	return -1;
}

int (arena_4033e0)(int x, int y) { return hit(x, y, (const int *)0x4d9358, 26); }   /* 0x4033e0 */
int (arena_404460)(int x, int y) { return hit(x, y, (const int *)0x4db588, 6); }   /* 0x404460 */
int (arena_4044a0)(int x, int y) { return hit(x, y, (const int *)0x4db720, 18); }   /* 0x4044a0 */
int (arena_4044e0)(int x, int y) { return hit(x, y, (const int *)0x4dbad0, 1); }   /* 0x4044e0 */
int (arena_4045a0)(int x, int y) { return hit(x, y, (const int *)0x4dbb80, 2); }   /* 0x4045a0 */
int (armc_40e450)(int x, int y) { return hit(x, y, (const int *)0x4dc2a8, 17); }   /* 0x40e450 */
int (armc_40e490)(int x, int y) { return hit(x, y, (const int *)0x4dbc88, 15); }   /* 0x40e490 */
int (armc_40e4d0)(int x, int y) { return hit(x, y, (const int *)0x4dcb38, 18); }   /* 0x40e4d0 */
int (setup_420670)(int x, int y) { return hit(x, y, (const int *)0x4ddcf0, 10); }   /* 0x420670 */
int (setup_4206b0)(int x, int y) { return hit(x, y, (const int *)0x4ddde0, 9); }   /* 0x4206b0 */
int (setup_4206f0)(int x, int y) { return hit(x, y, (const int *)0x4ddea8, 18); }   /* 0x4206f0 */
int (setup_420730)(int x, int y) { return hit(x, y, (const int *)0x4ddd98, 3); }   /* 0x420730 */
int (room_4321c0)(int x, int y) { return hit(x, y, (const int *)0x9dd390, 2); }   /* 0x4321c0 */
int (room_432200)(int x, int y) { return hit(x, y, (const int *)0x9dd7e0, 5); }   /* 0x432200 */
int (room_432240)(int x, int y) { return hit(x, y, (const int *)0x9dce50, 7); }   /* 0x432240 */
int (room_432280)(int x, int y) { return hit(x, y, (const int *)0x9dd3b8, 2); }   /* 0x432280 */
int (room_4322c0)(int x, int y) { return hit(x, y, (const int *)0x9dd400, 6); }   /* 0x4322c0 */
int (room_432300)(int x, int y) { return hit(x, y, (const int *)0x9dcd48, 15); }   /* 0x432300 */
int (room_432340)(int x, int y) { return hit(x, y, (const int *)0x9dd308, 1); }   /* 0x432340 */
int (room_432380)(int x, int y) { return hit(x, y, (const int *)0x9dd6f8, 14); }   /* 0x432380 */
int (room_4323c0)(int x, int y) { return hit(x, y, (const int *)0x9dd4c0, 9); }   /* 0x4323c0 */
int (mainmenu_440b70)(int x, int y) { return hit(x, y, (const int *)0x9dd950, 18); }   /* 0x440b70 */
int (skirmish_4438d0)(int x, int y) { return hit(x, y, (const int *)0x9ef220, 10); }   /* 0x4438d0 */
int (skirmish_443910)(int x, int y) { return hit(x, y, (const int *)0x9f16c0, 4); }   /* 0x443910 */
int (missionsel_447710)(int x, int y) { return hit(x, y, (const int *)0x9f6330, 4); }   /* 0x447710 */
int (profile_44b260)(int x, int y) { return hit(x, y, (const int *)0x9f8c60, 9); }   /* 0x44b260 */
int (profile_44b2a0)(int x, int y) { return hit(x, y, (const int *)0x9f9020, 2); }   /* 0x44b2a0 */
int (profile_44b320)(int x, int y) { return hit(x, y, (const int *)0x9f6808, 2); }   /* 0x44b320 */
int (profile_44b360)(int x, int y) { return hit(x, y, (const int *)0x9f8ee8, 2); }   /* 0x44b360 */
int (profile_44b3a0)(int x, int y) { return hit(x, y, (const int *)0x9f8d78, 13); }   /* 0x44b3a0 */
int (profile_44b3e0)(int x, int y) { return hit(x, y, (const int *)0x9f8f38, 11); }   /* 0x44b3e0 */

/* 0x404520: the create-arena screen: its second set of buttons (numbered from 16) while 0x4db55c is set */
int (createArena_hitTest)(int x, int y)
{
	if (GAME_VAR(int, 0x4db55c) != 0) {
		int i = hit(x, y, (const int *)0x4db6e8, 2);
		return i < 0 ? -1 : i + 16;
	}
	return hit(x, y, (const int *)0x4db5e8, 16);
}

/* 0x41eea0: is the point (x, y) (menu units) inside the convex polygon of n edges whose corners follow on the stack
   (5 xs, then 5 ys, centred: x - 320, 240 - y), every edge turning the same way? */
int (menu_pointInPolygon)(int x, int y, int n, ...)
{
	va_list args;
	va_start(args, n);
	const int *px = (const int *)args, *py = px + 5;
	int cx = x - 320, cy = 240 - y;
	for (int i = 0; i < n; i++)
		if ((int)((u32)(px[i + 1] - px[i]) * (u32)(cy - py[i]) + (u32)(cx - px[i]) * (u32)(py[i] - py[i + 1])) > 0) {
			va_end(args);
			return 0;
		}
	va_end(args);
	return 1;
}
