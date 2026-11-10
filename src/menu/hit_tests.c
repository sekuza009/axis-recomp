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
int (playerSetup_hitTest)(int x, int y) { return hit(x, y, g_playerSetupRects, 6); }   /* 0x404460 */
int (arenaGameList_hitTest)(int x, int y) { return hit(x, y, g_arenaGameListRects, 18); }   /* 0x4044a0 */
int (arenaDialogBox_hitTest)(int x, int y) { return hit(x, y, g_arenaDialogBoxRects, 1); }   /* 0x4044e0 */
int (arenaUpdateNotice_hitTest)(int x, int y) { return hit(x, y, g_arenaUpdateNoticeRects, 2); }   /* 0x4045a0 */
int (armcPartsPage_hitTest)(int x, int y) { return hit(x, y, g_armcPartsPageRects, 17); }   /* 0x40e450 */
int (armcWeaponsPage_hitTest)(int x, int y) { return hit(x, y, g_armcWeaponsPageRects, 15); }   /* 0x40e490 */
int (armcColour_hitTest)(int x, int y) { return hit(x, y, g_armcColourRects, 18); }   /* 0x40e4d0 */
int (setupSound_hitTest)(int x, int y) { return hit(x, y, g_setupSoundRects, 10); }   /* 0x420670 */
int (setupGraphic_hitTest)(int x, int y) { return hit(x, y, g_setupGraphicRects, 9); }   /* 0x4206b0 */
int (setupControl_hitTest)(int x, int y) { return hit(x, y, g_setupControlRects, 18); }   /* 0x4206f0 */
int (setupSlider_hitTest)(int x, int y) { return hit(x, y, g_setupSliderRects, 3); }   /* 0x420730 */
int (updateNotice_hitTest)(int x, int y) { return hit(x, y, g_updateNoticeRects, 2); }   /* 0x4321c0 */
int (roomLogin_hitTest)(int x, int y) { return hit(x, y, g_roomLoginRects, 5); }   /* 0x432200 */
int (newIdForm_hitTest)(int x, int y) { return hit(x, y, g_newIdFormRects, 7); }   /* 0x432240 */
int (newIdConfirm_hitTest)(int x, int y) { return hit(x, y, g_newIdConfirmRects, 2); }   /* 0x432280 */
int (account_hitTest)(int x, int y) { return hit(x, y, g_accountRects, 6); }   /* 0x4322c0 */
int (gameList_hitTest)(int x, int y) { return hit(x, y, g_gameListRects, 15); }   /* 0x432300 */
int (gameListJoinBox_hitTest)(int x, int y) { return hit(x, y, g_gameListJoinBoxRects, 1); }   /* 0x432340 */
int (roomSettings_hitTest)(int x, int y) { return hit(x, y, g_roomSettingsRects, 14); }   /* 0x432380 */
int (ranking_hitTest)(int x, int y) { return hit(x, y, g_rankingRects, 9); }   /* 0x4323c0 */
int (replaySelect_hitTest)(int x, int y) { return hit(x, y, g_replaySelectRects, 18); }   /* 0x440b70 */
int (missionList_hitTest)(int x, int y) { return hit(x, y, g_missionListRects, 10); }   /* 0x4438d0 */
int (briefing_hitTest)(int x, int y) { return hit(x, y, g_briefingRects, 4); }   /* 0x443910 */
int (skirmish_hitTest)(int x, int y) { return hit(x, y, g_skirmishRects, 4); }   /* 0x447710 */
int (profilePage_hitTest)(int x, int y) { return hit(x, y, g_profilePageRects, 9); }   /* 0x44b260 */
int (newNameDialog_hitTest)(int x, int y) { return hit(x, y, g_newNameDialogRects, 2); }   /* 0x44b2a0 */
int (deleteDialog_hitTest)(int x, int y) { return hit(x, y, g_deleteDialogRects, 2); }   /* 0x44b320 */
int (logOutDialog_hitTest)(int x, int y) { return hit(x, y, g_logOutDialogRects, 2); }   /* 0x44b360 */
int (profileList_hitTest)(int x, int y) { return hit(x, y, g_profileListRects, 13); }   /* 0x44b3a0 */
int (pilotSelect_hitTest)(int x, int y) { return hit(x, y, g_pilotSelectRects, 11); }   /* 0x44b3e0 */

/* 0x404520: the create-arena screen: the error box's buttons (numbered from 16) while it is up (g_hostErrorBox) */
int (createArena_hitTest)(int x, int y)
{
	if (g_hostErrorBox != 0) {
		int i = hit(x, y, g_hostErrorBoxRects, 2);
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

#ifdef AXIS_64
/* (the 64-bit build's point_in_outline: menu_pointInPolygon's test on an outline given by address - game.h) */
int menu_outlineHolds(int x, int y, const Outline *o)
{
	const int *px = o->x, *py = o->y;
	int cx = x - 320, cy = 240 - y;
	for (int i = 0; i < o->n; i++)
		if ((int)((u32)(px[i + 1] - px[i]) * (u32)(cy - py[i]) + (u32)(cx - px[i]) * (u32)(py[i] - py[i + 1])) > 0)
			return 0;
	return 1;
}
#endif
