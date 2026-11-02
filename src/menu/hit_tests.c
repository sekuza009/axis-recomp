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

int (mapList_hitTest)(int x, int y) { return hit(x, y, g_mapListRects, 26); }   /* 0x4033e0 */
int (arenaNameDialog_hitTest)(int x, int y) { return hit(x, y, g_arenaNameDialogRects, 6); }   /* 0x404460 */
int (arenaGameList_hitTest)(int x, int y) { return hit(x, y, g_arenaGameListRects, 18); }   /* 0x4044a0 */
int (arenaDialogBox_hitTest)(int x, int y) { return hit(x, y, g_arenaDialogBoxRects, 1); }   /* 0x4044e0 */
int (arenaCreate_hitTest)(int x, int y) { return hit(x, y, g_arenaCreateRects, 2); }   /* 0x4045a0 */
int (armcMain_hitTest)(int x, int y) { return hit(x, y, g_armcMainRects, 17); }   /* 0x40e450 */
int (armcParts_hitTest)(int x, int y) { return hit(x, y, g_armcPartsRects, 15); }   /* 0x40e490 */
int (armcColour_hitTest)(int x, int y) { return hit(x, y, g_armcColourRects, 18); }   /* 0x40e4d0 */
int (setupSound_hitTest)(int x, int y) { return hit(x, y, g_setupSoundRects, 10); }   /* 0x420670 */
int (setupOptions_hitTest)(int x, int y) { return hit(x, y, g_setupOptionsRects, 9); }   /* 0x4206b0 */
int (setupControl_hitTest)(int x, int y) { return hit(x, y, g_setupControlRects, 18); }   /* 0x4206f0 */
int (setupSlider_hitTest)(int x, int y) { return hit(x, y, g_setupSliderRects, 3); }   /* 0x420730 */
int (leaveDialog_hitTest)(int x, int y) { return hit(x, y, g_leaveDialogRects, 2); }   /* 0x4321c0 */
int (createDialog_hitTest)(int x, int y) { return hit(x, y, g_createDialogRects, 5); }   /* 0x432200 */
int (loginForm_hitTest)(int x, int y) { return hit(x, y, g_loginFormRects, 7); }   /* 0x432240 */
int (popup_hitTest)(int x, int y) { return hit(x, y, g_popupRects, 2); }   /* 0x432280 */
int (account_hitTest)(int x, int y) { return hit(x, y, g_accountRects, 6); }   /* 0x4322c0 */
int (gameList_hitTest)(int x, int y) { return hit(x, y, g_gameListRects, 15); }   /* 0x432300 */
int (gameListStop_hitTest)(int x, int y) { return hit(x, y, g_gameListStopRects, 1); }   /* 0x432340 */
int (roomSettings_hitTest)(int x, int y) { return hit(x, y, g_roomSettingsRects, 14); }   /* 0x432380 */
int (ranking_hitTest)(int x, int y) { return hit(x, y, g_rankingRects, 9); }   /* 0x4323c0 */
int (mapSelect_hitTest)(int x, int y) { return hit(x, y, g_mapSelectRects, 18); }   /* 0x440b70 */
int (skirmishSettings_hitTest)(int x, int y) { return hit(x, y, g_skirmishSettingsRects, 10); }   /* 0x4438d0 */
int (briefing_hitTest)(int x, int y) { return hit(x, y, g_briefingRects, 4); }   /* 0x443910 */
int (missionsel_hitTest)(int x, int y) { return hit(x, y, g_missionselRects, 4); }   /* 0x447710 */
int (profilePage_hitTest)(int x, int y) { return hit(x, y, g_profilePageRects, 9); }   /* 0x44b260 */
int (newNameDialog_hitTest)(int x, int y) { return hit(x, y, g_newNameDialogRects, 2); }   /* 0x44b2a0 */
int (deleteDialog_hitTest)(int x, int y) { return hit(x, y, g_deleteDialogRects, 2); }   /* 0x44b320 */
int (secondDialog_hitTest)(int x, int y) { return hit(x, y, g_secondDialogRects, 2); }   /* 0x44b360 */
int (profileList_hitTest)(int x, int y) { return hit(x, y, g_profileListRects, 13); }   /* 0x44b3a0 */
int (pilotSelect_hitTest)(int x, int y) { return hit(x, y, g_pilotSelectRects, 11); }   /* 0x44b3e0 */

/* 0x404520: the create-arena screen: its second set of buttons (numbered from 16) while 0x4db55c is set */
int (createArena_hitTest)(int x, int y)
{
	if (g_createQuitDialog != 0) {
		int i = hit(x, y, g_createArena2Rects, 2);
		return i < 0 ? -1 : i + 16;
	}
	return hit(x, y, g_createArenaRects, 16);
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
