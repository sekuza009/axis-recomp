/* layouts.c: the screens' button layouts: each screen fills its table of button rectangles (left, top, right, bottom in menu units; see hit_tests.c) from its panel's position, usually as rows or columns of equal buttons. */
#include "../game.h"

#define GAME_I32(a) GAME_VAR(int, a)

/* one rectangle: each corner value = global + constant */
static void rect1(u32 rec, u32 g0, int c0, u32 g1, int c1, u32 g2, int c2, u32 g3, int c3)
{
	rect_set(GAME_I32(g0) + c0, GAME_I32(g1) + c1, GAME_I32(g2) + c2, GAME_I32(g3) + c3, (int *)RELOC(rec));
}

/* a row or column of rectangles, 16 bytes apart from rec up to end: each corner value = global (or 0) + constant,
   plus the running offset d (growing by step) where marked */
typedef struct { u32 g; int c, d; } RArg;
#define RA(g, c, d) { g, c, d }
static void rect_spec(u32 rec, u32 end, int step, const RArg *a)
{
	for (int d = 0; rec < end; rec += 16, d += step) {
		int v[4];
		for (int k = 0; k < 4; k++)
			v[k] = (a[k].g ? GAME_I32(a[k].g) : 0) + a[k].c + (a[k].d ? d : 0);
		rect_set(v[0], v[1], v[2], v[3], (int *)RELOC(rec));
	}
}

/* a column of buttons 0x78 wide at y 0x104 .. 0x124, 0xa0 apart from x */
static void rects_column(u32 rec, u32 end, int x)
{
	for (; rec < end; rec += 16, x += 0xa0)
		rect_set(x, 0x104, x + 0x78, 0x124, (int *)RELOC(rec));
}

/* a row of buttons relative to a movable origin (x at ox, y at oy): stride dx, corners at x0 / y0 and x1 / y1 */
static void rects_row(u32 rec, u32 end, u32 ox, u32 oy, int x0, int x1, int y0, int y1, int dx)
{
	for (int d = 0; rec < end; rec += 16, d += dx) {
		int x = GAME_I32(ox), y = GAME_I32(oy);
		rect_set(d + x + x0, y + y0, d + x + x1, y + y1, (int *)RELOC(rec));
	}
}

/* the arena options panel: eight rows of fields (at rec) and four controls on the right (at rec2), from the panel's
   x (gx), y (gy) and right edge (gx2) */
static void options_panel(u32 rec, u32 rec2, u32 gx, u32 gy, u32 gx2)
{
	static const short r[8][4] = { { 0x40, 0x2f, 0x1a7, 0x45 }, { 0x40, 0x51, 0xef, 0x67 }, { 0x40, 0x6d, 0x18f, 0x91 },
	                               { 0x40, 0x95, 0xef, 0xab }, { 0x40, 0xb7, 0xef, 0xcd }, { 0x40, 0xd9, 0x14f, 0xef },
	                               { 0x40, 0xfb, 0xef, 0x111 }, { 0x40, 0x11d, 0xef, 0x133 } };
	static const short q[4][4] = { { -0x96, 0x50, -0x16, 0xd0 }, { -0x8c, 0xd7, -0x5c, 0xef }, { -0x50, 0xd7, -0x20, 0xef },
	                               { -0x96, 0xf5, -0x16, 0x111 } };
	if (rec)
		for (int k = 0; k < 8; k++)
			rect1(rec + k * 16, gx, r[k][0], gy, r[k][1], gx, r[k][2], gy, r[k][3]);
	if (rec2)
		for (int k = 0; k < 4; k++)
			rect1(rec2 + k * 16, gx2, q[k][0], gy, q[k][1], gx2, q[k][2], gy, q[k][3]);
}

/* the ARM CENTER's layout origin (x, y, right, bottom) and its tab rows (3 tabs 0x64 apart, two rows) */
#define AX ADDR(g_armcPageLeft)
#define AY ADDR(g_armcPageTop)
#define AX2 ADDR(g_armcPageRight)
#define AY2 ADDR(g_armcPageBottom)
static void armc_tabs(u32 rec)
{
	static const RArg a[4] = { RA(AX, 0x10, 1), RA(AY, -8, 0), RA(AX, 0x70, 1), RA(AY, 0x18, 0) };
	static const RArg b[4] = { RA(AX, 0x10, 1), RA(AY2, -0x20, 0), RA(AX, 0x70, 1), RA(AY2, 0, 0) };
	rect_spec(rec, rec + 3 * 16, 0x64, a);              /* three tabs (16-byte rects) .. */
	rect_spec(rec + 3 * 16, rec + 5 * 16, 0x64, b);     /* .. then two */
}

void (arenaUpdateNotice_layout)(void) { rects_column(OBJ(g_arenaCreateRects), OBJ(g_arenaCreateRects) + 2 * 16, 0xb4); }

void (updateNotice_layout)(void) { rects_column(OBJ(g_updateNoticeRects), OBJ(g_updateNoticeRects) + 2 * 16, 0xb4); }

void (deleteDialog_layout)(void) { rects_row(OBJ(g_deleteDialogRects), OBJ(g_deleteDialogRects) + 2 * 16, ADDR(g_profileDialogX), ADDR(g_profileDialogY), 0x6e, 0xce, 0x3c, 0x5c, 0x78); }

void (logOutDialog_layout)(void) { rects_row(OBJ(g_logOutDialogRects), OBJ(g_logOutDialogRects) + 2 * 16, ADDR(g_logOutDialogX), ADDR(g_logOutDialogY), 0x6e, 0xce, 0x3c, 0x5c, 0x78); }

void (newNameDialog_layout)(void) { rects_row(OBJ(g_newNameDialogRects), OBJ(g_newNameDialogRects) + 2 * 16, ADDR(g_newNameDialogLeft), ADDR(g_newNameDialogTop), 0xa0, 0x100, 0x5a, 0x7a, 0x78); }

void (newIdConfirm_layout)(void) { rects_row(OBJ(g_newIdConfirmRects), OBJ(g_newIdConfirmRects) + 2 * 16, OBJ(g_newIdConfirmBox), (OBJ(g_newIdConfirmBox) + 0xc), 0x64, 0xdc, -0x40, -0x20, 0xb4); }

void (lobbyTop_layout)(void) { rects_row(OBJ(g_lobbyTopRects), OBJ(g_lobbyTopRects) + 2 * 16, OBJ(g_lobbyTopRect), (OBJ(g_lobbyTopRect) + 0x4), 0x32, 0xe6, 0x64, 0x94, 0xc8); }

void (setupGraphic_layout)(void)
{
	static const RArg a[4] = { RA(OBJ(g_setupGraphicRect), 0xa, 0), RA(ADDR(g_setupGraphicTop), 0x3c, 1), RA(OBJ(g_setupGraphicRect), 0x186, 0), RA(ADDR(g_setupGraphicTop), 0x5c, 1) };
	static const RArg b[4] = { RA(OBJ(g_setupGraphicRect), 0x64, 1), RA((OBJ(g_setupGraphicRect) + 0xc), -0x40, 0), RA(OBJ(g_setupGraphicRect), 0xdc, 1), RA((OBJ(g_setupGraphicRect) + 0xc), -0x20, 0) };
	rect_spec(OBJ(g_setupGraphicRects), (OBJ(g_setupGraphicRects) + 0x70), 0x28, a); rect_spec((OBJ(g_setupGraphicRects) + 0x70), OBJ(g_setupGraphicRects) + 9 * 16, 0x8c, b);
}

void (newIdForm_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_newIdFormLeft), 0x30, 0), RA(ADDR(g_newIdFormTop), 0x30, 1), RA(ADDR(g_newIdFormLeft), 0x210, 0), RA(ADDR(g_newIdFormTop), 0x58, 1) };
	static const RArg b[4] = { RA(ADDR(g_newIdFormLeft), 0x5a, 1), RA(ADDR(g_newIdFormBottom), -0x40, 0), RA(ADDR(g_newIdFormLeft), 0xfa, 1), RA(ADDR(g_newIdFormBottom), -0x20, 0) };
	rect_spec(OBJ(g_newIdFormRects), (OBJ(g_newIdFormRects) + 0x40), 0x30, a); rect_spec((OBJ(g_newIdFormRects) + 0x40), (OBJ(g_newIdFormRects) + 0x60), 0xc8, b);
}

void (playerSetup_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_playerSetupLeft), 0x30, 0), RA(ADDR(g_playerSetupTop), 0x60, 1), RA(ADDR(g_playerSetupLeft), 0x188, 0), RA(ADDR(g_playerSetupTop), 0x78, 1) };
	static const RArg b[4] = { RA(ADDR(g_playerSetupLeft), 0x32, 1), RA(ADDR(g_playerSetupTop), 0xdc, 0), RA(ADDR(g_playerSetupLeft), 0x96, 1), RA(ADDR(g_playerSetupTop), 0xfc, 0) };
	rect_spec(OBJ(g_playerSetupRects), (OBJ(g_playerSetupRects) + 0x30), 0x19, a); rect_spec((OBJ(g_playerSetupRects) + 0x30), OBJ(g_playerSetupRects) + 6 * 16, 0x78, b);
}

void (roomLogin_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_roomLoginLeft), 0xb8, 0), RA(ADDR(g_roomLoginTop), 0x50, 1), RA(ADDR(g_roomLoginLeft), 0x1a8, 0), RA(ADDR(g_roomLoginTop), 0x70, 1) };
	static const RArg b[4] = { RA(ADDR(g_roomLoginLeft), 0x30, 1), RA(ADDR(g_roomLoginBottom), -0x40, 0), RA(ADDR(g_roomLoginLeft), 0xa8, 1), RA(ADDR(g_roomLoginBottom), -0x18, 0) };
	rect_spec(OBJ(g_roomLoginRects), (OBJ(g_roomLoginRects) + 0x20), 0x30, a); rect_spec((OBJ(g_roomLoginRects) + 0x20), (OBJ(g_roomLoginRects) + 0x20) + 3 * 16, 0xa0, b);
}

void (missionList_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_missionsWindowLeft), 0x10, 0), RA(ADDR(g_missionsWindowTop), 0x44, 1), RA(ADDR(g_missionsWindowLeft), 0x25d, 0), RA(ADDR(g_missionsWindowTop), 0x5c, 1) };
	static const RArg b[4] = { RA(ADDR(g_missionsWindowRight), -0x12c, 1), RA(ADDR(g_missionsWindowBottom), -0x40, 0), RA(ADDR(g_missionsWindowRight), -0xb4, 1), RA(ADDR(g_missionsWindowBottom), -0x20, 0) };
	rect_spec(OBJ(g_missionListRects), (OBJ(g_missionListRects) + 0x80), 0x1a, a); rect_spec((OBJ(g_missionListRects) + 0x80), (OBJ(g_missionListRects) + 0x80) + 2 * 16, 0x8c, b);
}

void (account_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_accountPanelLeft), 0x84, 0), RA(ADDR(g_accountPanelTop), 0x52, 1), RA(ADDR(g_accountPanelRight), -0x30, 0), RA(ADDR(g_accountPanelTop), 0x68, 1) };
	static const RArg b[4] = { RA(ADDR(g_accountPanelLeft), 0x7d, 1), RA(ADDR(g_accountPanelBottom), -0x30, 0), RA(ADDR(g_accountPanelLeft), 0xf5, 1), RA(ADDR(g_accountPanelBottom), -0x10, 0) };
	rect_spec(OBJ(g_accountRects), (OBJ(g_accountRects) + 0x40), 0x1c, a); rect_spec((OBJ(g_accountRects) + 0x40), OBJ(g_accountRects) + 6 * 16, 0xa0, b);
}

void (briefing_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_missionsWindowRight), -0x12c, 1), RA(ADDR(g_missionsWindowBottom), -0x30, 0), RA(ADDR(g_missionsWindowRight), -0xb4, 1), RA(ADDR(g_missionsWindowBottom), -0x10, 0) };
	static const RArg b[4] = { RA(ADDR(g_missionsWindowLeft), 0x40, 1), RA(ADDR(g_missionsWindowBottom), -0x30, 0), RA(ADDR(g_missionsWindowLeft), 0xb8, 1), RA(ADDR(g_missionsWindowBottom), -0x10, 0) };
	rect_spec(OBJ(g_briefingRects), (OBJ(g_briefingRects) + 0x20), 0x8c, a); rect_spec((OBJ(g_briefingRects) + 0x20), OBJ(g_briefingRects) + 4 * 16, 0x8c, b);
}

void (skirmish_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_skirmishRectLeft), 0x96, 1), RA((OBJ(g_skirmishRect) + 0xc), -0x30, 0), RA(ADDR(g_skirmishRectLeft), 0x10e, 1), RA((OBJ(g_skirmishRect) + 0xc), -0x10, 0) };
	rect_spec(OBJ(g_skirmishRects), (OBJ(g_skirmishRects) + 0x20), 0x8c, a);
	rect_set(g_skirmishRectLeft + 0x98, g_skirmishRectTop + 0x4c, g_skirmishRectLeft + 0xd0, g_skirmishRectTop + 0x74, (int *)(OBJ(g_skirmishRects) + 0x20));
	rect_set(g_skirmishRectLeft + 0x160, g_skirmishRectTop + 0x4c, g_skirmishRectLeft + 0x198, g_skirmishRectTop + 0x74, (int *)(OBJ(g_skirmishRects) + 0x30));
}

void (pilotSelect_layout)(void)        /* 3 x 3 grid, then a row of two */
{
	u32 rec = OBJ(g_pilotSelectRects);
	for (int i = 0; rec < (OBJ(g_pilotSelectRects) + 0x90); i++, rec += 16) {
		int y = g_pilotSelectTop + (i / 3) * 86, x = g_pilotSelectLeft + (i % 3) * 86;
		rect_set(x + 0x20, y + 0x4c, x + 0x74, y + 0xa0, (int *)RELOC(rec));
	}
	static const RArg b[4] = { RA(ADDR(g_pilotSelectLeft), 0xaa, 1), RA(ADDR(g_pilotSelectBottom), -0x40, 0), RA(ADDR(g_pilotSelectLeft), 0x122, 1), RA(ADDR(g_pilotSelectBottom), -0x20, 0) };
	rect_spec((OBJ(g_pilotSelectRects) + 0x90), OBJ(g_pilotSelectRects) + 11 * 16, 0xa0, b);
}

void (gameList_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_roomGameListLeft), 0x20, 1), RA(ADDR(g_roomGameListBottom), -0x32, 0), RA(ADDR(g_roomGameListLeft), 0x98, 1), RA(ADDR(g_roomGameListBottom), -0x12, 0) };
	static const RArg b[4] = { RA(ADDR(g_roomGameListLeft), 0x10, 0), RA(ADDR(g_roomGameListTop), 0x5e, 1), RA(ADDR(g_roomGameListLeft), 0x204, 0), RA(ADDR(g_roomGameListTop), 0x74, 1) };
	static const RArg c[4] = { RA(ADDR(g_roomGameListLeft), 0x226, 0), RA(ADDR(g_roomGameListTop), 0x6e, 1), RA(ADDR(g_roomGameListLeft), 0x246, 0), RA(ADDR(g_roomGameListTop), 0xae, 1) };
	rect_spec(OBJ(g_gameListRects), (OBJ(g_gameListRects) + 0x40), 0x8c, a); rect_spec((OBJ(g_gameListRects) + 0x40), (OBJ(g_gameListRects) + 0xd0), 0x18, b); rect_spec((OBJ(g_gameListRects) + 0xd0), OBJ(g_gameListRects) + 15 * 16, 0x50, c);
}

void (arenaGameList_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_arenaGameListLeft), 0x23, 1), RA(ADDR(g_arenaGameListTop), 0x30, 0), RA(ADDR(g_arenaGameListLeft), 0xc3, 1), RA(ADDR(g_arenaGameListTop), 0x48, 0) };
	static const RArg b[4] = { RA(ADDR(g_arenaGameListLeft), 0x5a, 1), RA(ADDR(g_arenaGameListBottom), -0x2c, 0), RA(ADDR(g_arenaGameListLeft), 0xd2, 1), RA(ADDR(g_arenaGameListBottom), -0xc, 0) };
	static const RArg c[4] = { RA(ADDR(g_arenaGameListLeft), 0x10, 0), RA(ADDR(g_arenaGameListTop), 0x76, 1), RA(ADDR(g_arenaGameListLeft), 0x204, 0), RA(ADDR(g_arenaGameListTop), 0x8c, 1) };
	static const RArg d[4] = { RA(ADDR(g_arenaGameListLeft), 0x21e, 0), RA(ADDR(g_arenaGameListTop), 0xa0, 1), RA(ADDR(g_arenaGameListLeft), 0x23e, 0), RA(ADDR(g_arenaGameListTop), 0xe0, 1) };
	rect_spec(OBJ(g_arenaGameListRects), (OBJ(g_arenaGameListRects) + 0x30), 0xb4, a); rect_spec((OBJ(g_arenaGameListRects) + 0x30), (OBJ(g_arenaGameListRects) + 0x60), 0x96, b);
	rect_spec((OBJ(g_arenaGameListRects) + 0x60), (OBJ(g_arenaGameListRects) + 0xf0), 0x18, c); rect_spec((OBJ(g_arenaGameListRects) + 0xf0), (OBJ(g_arenaGameListRects) + 0x110), 0x50, d);
}

void (profilePage_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_profilePageLeft), 0x28, 1), RA(ADDR(g_profilePageBottom), -0x30, 0), RA(ADDR(g_profilePageLeft), 0x88, 1), RA(ADDR(g_profilePageBottom), -0x10, 0) };
	static const short r[4][4] = { { 0x20, 0x23, 0xd4, 0x126 }, { 0xe0, 0x50, 0xf8, 0x80 }, { 0xe0, 0xb4, 0xf8, 0xe4 },
	                               { 0x1a4, 0x24, 0x1e4, 0x64 } };
	rect_spec(OBJ(g_profilePageRects), (OBJ(g_profilePageRects) + 0x40), 0x72, a);
	for (int k = 0; k < 4; k++)
		rect_set(g_profilePageLeft + r[k][0], g_profilePageTop + r[k][1], g_profilePageLeft + r[k][2], g_profilePageTop + r[k][3],
		         (int *)((OBJ(g_profilePageRects) + 0x40) + k * 16));
}

void (armcWeaponsPage_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x28, 1), RA(AX, 0xa0, 0), RA(AY, 0x54, 1) };
	armc_tabs(OBJ(g_armcWeaponsPageRects));
	rect_spec((OBJ(g_armcWeaponsPageRects) + 0x60), (OBJ(g_armcWeaponsPageRects) + 0xc0), 0x3f, c);
	rect1((OBJ(g_armcWeaponsPageRects) + 0xc0), AX2, -0xea, AY, 0x162, AX2, -0xc2, AY, 0x182);
	rect1((OBJ(g_armcWeaponsPageRects) + 0xd0), AX2, -0x22, AY, 0x162, AX2, 6, AY, 0x182);
	rect1((OBJ(g_armcWeaponsPageRects) + 0xe0), AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (armcColour_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x40, 1), RA(AX, 0xb0, 0), RA(AY, 0x6c, 1) };
	static const RArg d[4] = { RA(AX2, -0xb8, 0), RA(AY, 0x58, 1), RA(AX2, -0x18, 0), RA(AY, 0x6c, 1) };
	static const RArg e[4] = { RA(AX2, -0xb8, 0), RA(AY, 0x108, 1), RA(AX2, -0x18, 0), RA(AY, 0x11c, 1) };
	armc_tabs(OBJ(g_armcColourRects));
	rect_spec((OBJ(g_armcColourRects) + 0x50), (OBJ(g_armcColourRects) + 0xb0), 0x30, c);
	rect_spec((OBJ(g_armcColourRects) + 0xb0), (OBJ(g_armcColourRects) + 0xe0), 0x30, d); rect_spec((OBJ(g_armcColourRects) + 0xe0), (OBJ(g_armcColourRects) + 0x110), 0x30, e);
	rect1((OBJ(g_armcColourRects) + 0x110), AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (armcPartsPage_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x40, 1), RA(AX, 0xb0, 0), RA(AY, 0x6c, 1) };
	armc_tabs(OBJ(g_armcPartsPageRects));
	rect_spec((OBJ(g_armcPartsPageRects) + 0x60), (OBJ(g_armcPartsPageRects) + 0xc0), 0x30, c);
	rect1((OBJ(g_armcPartsPageRects) + 0xd0), AX, 0x114, AY2, -0x20, AX, 0x174, AY2, 0);
	rect1((OBJ(g_armcPartsPageRects) + 0xe0), AX, 0xe4, AY2, -0x1c, AX, 0x114, AY2, -4);
	rect1((OBJ(g_armcPartsPageRects) + 0xf0), AX, 0x174, AY2, -0x1c, AX, 0x1a4, AY2, -4);
	rect1((OBJ(g_armcPartsPageRects) + 0x100), AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (replaySelect_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_replaySelectRight), -0x32, 0), RA(ADDR(g_replaySelectTop), 0x48, 1), RA(ADDR(g_replaySelectRight), -0x12, 0), RA(ADDR(g_replaySelectTop), 0x88, 1) };
	static const RArg b[4] = { RA(ADDR(g_replaySelectLeft), 0x10, 0), RA(ADDR(g_replaySelectTop), 0xfe, 1), RA(ADDR(g_replaySelectLeft), 0xd8, 0), RA(ADDR(g_replaySelectTop), 0x10e, 1) };
	static const RArg c[4] = { RA(ADDR(g_replaySelectLeft), 0x64, 1), RA(ADDR(g_replaySelectBottom), -0x5c, 0), RA(ADDR(g_replaySelectLeft), 0xdc, 1), RA(ADDR(g_replaySelectBottom), -0x3c, 0) };
	static const RArg d[4] = { RA(ADDR(g_replaySelectLeft), 0x64, 1), RA(ADDR(g_replaySelectBottom), -0x34, 0), RA(ADDR(g_replaySelectLeft), 0xdc, 1), RA(ADDR(g_replaySelectBottom), -0x14, 0) };
	static const RArg e[4] = { RA(ADDR(g_replaySelectLeft), 0x28, 0), RA(ADDR(g_replaySelectTop), 0x2c, 1), RA(ADDR(g_replaySelectRight), -0x50, 0), RA(ADDR(g_replaySelectTop), 0x3c, 1) };
	rect_spec(OBJ(g_replaySelectRects), (OBJ(g_replaySelectRects) + 0x20), 0x64, a); rect_spec((OBJ(g_replaySelectRects) + 0x20), (OBJ(g_replaySelectRects) + 0x40), 0x1e, b); rect_spec((OBJ(g_replaySelectRects) + 0x40), (OBJ(g_replaySelectRects) + 0x60), 0xa0, c);
	rect_spec((OBJ(g_replaySelectRects) + 0x60), (OBJ(g_replaySelectRects) + 0x80), 0xa0, d); rect_spec((OBJ(g_replaySelectRects) + 0x80), (OBJ(g_replaySelectRects) + 0x80) + 10 * 16, 0x14, e);
}

void (setupControl_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_setupControlLeft), 0x46, 1), RA(ADDR(g_setupControlTop), 0x10, 0), RA(ADDR(g_setupControlLeft), 0xaa, 1), RA(ADDR(g_setupControlTop), 0x24, 0) };
	static const RArg b[4] = { RA(ADDR(g_setupControlLeft), 0x50, 1), RA((OBJ(g_setupControlRect) + 0xc), -0x30, 0), RA(ADDR(g_setupControlLeft), 0xc8, 1), RA((OBJ(g_setupControlRect) + 0xc), -0x10, 0) };
	static const RArg c[4] = { RA(ADDR(g_setupControlLeft), 0x30, 0), RA(ADDR(g_setupControlTop), 0x59, 1), RA(ADDR(g_setupControlRight), -0x18, 0), RA(ADDR(g_setupControlTop), 0x70, 1) };
	rect_spec(OBJ(g_setupControlRects), (OBJ(g_setupControlRects) + 0x40), 0x78, a); rect_spec((OBJ(g_setupControlRects) + 0x40), (OBJ(g_setupControlRects) + 0x70), 0x8c, b); rect_spec((OBJ(g_setupControlRects) + 0x70), OBJ(g_setupControlRects) + 18 * 16, 0x18, c);
	rect1(OBJ(g_setupSliderRects), ADDR(g_setupControlLeft), 0xc8, ADDR(g_setupControlTop), 0x88, ADDR(g_setupControlLeft), 0x108, ADDR(g_setupControlTop), 0xa0);
	rect1((OBJ(g_setupSliderRects) + 0x10), ADDR(g_setupControlLeft), 0x1d0, ADDR(g_setupControlTop), 0x88, ADDR(g_setupControlLeft), 0x210, ADDR(g_setupControlTop), 0xa0);
	rect1((OBJ(g_setupSliderRects) + 0x20), ADDR(g_setupControlLeft), 0x108, ADDR(g_setupControlTop), 0x88, ADDR(g_setupControlLeft), 0x1d0, ADDR(g_setupControlTop), 0xa0);
}

void (setupSound_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_setupSoundLeft), 0x74, 0), RA((OBJ(g_setupSoundRect) + 0x4), 0x94, 1), RA(ADDR(g_setupSoundLeft), 0x1ae, 0), RA((OBJ(g_setupSoundRect) + 0x4), 0xb4, 1) };
	static const RArg b[4] = { RA(ADDR(g_setupSoundLeft), 0x90, 1), RA((OBJ(g_setupSoundRect) + 0x4), 0x113, 0), RA(ADDR(g_setupSoundLeft), 0x108, 1), RA((OBJ(g_setupSoundRect) + 0x4), 0x133, 0) };
	static const short r[5][4] = { { 0x50, 0x50, 0x8f, 0x70 }, { 0x191, 0x50, 0x1d0, 0x70 }, { 0x90, 0x50, 0x190, 0x70 },
	                               { 0x50, 0x8c, 0x8f, 0xac }, { 0x191, 0x8c, 0x1d0, 0xac } };
	for (int k = 0; k < 5; k++) rect1(OBJ(g_setupSoundRects) + k * 16, ADDR(g_setupSoundLeft), r[k][0], (OBJ(g_setupSoundRect) + 0x4), r[k][1], ADDR(g_setupSoundLeft), r[k][2], (OBJ(g_setupSoundRect) + 0x4), r[k][3]);
	rect_spec((OBJ(g_setupSoundRects) + 0x50), (OBJ(g_setupSoundRects) + 0x80), 0x28, a); rect_spec((OBJ(g_setupSoundRects) + 0x80), (OBJ(g_setupSoundRects) + 0x80) + 2 * 16, 0x8c, b);
}

void (ranking_layout)(void)
{
	static const RArg a[4] = { RA(OBJ(g_rankingRect), 0x7d, 1), RA((OBJ(g_rankingRect) + 0xc), -0x30, 0), RA(OBJ(g_rankingRect), 0x11d, 1), RA((OBJ(g_rankingRect) + 0xc), -0x10, 0) };
	static const short r[4][2] = { { 0x112, 0x144 }, { 0x14e, 0x130 }, { 0x18a, 0x1bc }, { 0x20c, 0x23e } };   /* [1] is inverted */
	rect1(OBJ(g_rankingRects), OBJ(g_rankingRect), 0xb2, (OBJ(g_rankingRect) + 0x4), 0x26, OBJ(g_rankingRect), 0xe6, (OBJ(g_rankingRect) + 0x4), 0x3e);
	rect1((OBJ(g_rankingRects) + 0x10), OBJ(g_rankingRect), 0x144, (OBJ(g_rankingRect) + 0x4), 0x26, OBJ(g_rankingRect), 0x178, (OBJ(g_rankingRect) + 0x4), 0x3e);
	rect1((OBJ(g_rankingRects) + 0x20), (OBJ(g_rankingRect) + 0x8), -0x78, (OBJ(g_rankingRect) + 0x4), 0x24, (OBJ(g_rankingRect) + 0x8), -0x14, (OBJ(g_rankingRect) + 0x4), 0x40);
	rect_spec((OBJ(g_rankingRects) + 0x30), (OBJ(g_rankingRects) + 0x50), 0xc8, a);
	for (int k = 0; k < 4; k++) rect1((OBJ(g_rankingRects) + 0x50) + k * 16, OBJ(g_rankingRect), r[k][0], (OBJ(g_rankingRect) + 0x4), 0x50, OBJ(g_rankingRect), r[k][1], (OBJ(g_rankingRect) + 0x4), 0x66);
}

void (roomSettings_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_roomFormLeft), 0x64, 1), RA(ADDR(g_roomFormBottom), -0x40, 0), RA(ADDR(g_roomFormLeft), 0x104, 1), RA(ADDR(g_roomFormBottom), -0x20, 0) };
	options_panel(OBJ(g_roomSettingsRects), 0, ADDR(g_roomFormLeft), ADDR(g_roomFormTop), ADDR(g_roomFormRight));
	rect_spec((OBJ(g_roomSettingsRects) + 0x80), (OBJ(g_roomSettingsRects) + 0xa0), 0xc8, a);
	options_panel(0, (OBJ(g_roomSettingsRects) + 0xa0), ADDR(g_roomFormLeft), ADDR(g_roomFormTop), ADDR(g_roomFormRight));
}

/* ---- the arena options, the profile list and the map list ---- */
void (createArena_layout)(void)
{
	static const RArg a[4] = { RA(ADDR(g_newArenaFormLeft), 0x3c, 1), RA(ADDR(g_newArenaFormBottom), -0x5a, 0), RA(ADDR(g_newArenaFormLeft), 0x104, 1), RA(ADDR(g_newArenaFormBottom), -0x3a, 0) };
	static const RArg b[4] = { RA(ADDR(g_newArenaFormLeft), 0x3c, 1), RA(ADDR(g_newArenaFormBottom), -0x32, 0), RA(ADDR(g_newArenaFormLeft), 0x104, 1), RA(ADDR(g_newArenaFormBottom), -0x12, 0) };
	options_panel(OBJ(g_createArenaRects), 0, ADDR(g_newArenaFormLeft), ADDR(g_newArenaFormTop), ADDR(g_newArenaFormRight));
	rect_spec((OBJ(g_createArenaRects) + 0x80), (OBJ(g_createArenaRects) + 0xa0), 0xfa, a); rect_spec((OBJ(g_createArenaRects) + 0xa0), (OBJ(g_createArenaRects) + 0xc0), 0xfa, b);
	options_panel(0, (OBJ(g_createArenaRects) + 0xc0), ADDR(g_newArenaFormLeft), ADDR(g_newArenaFormTop), ADDR(g_newArenaFormRight));
	rects_column(OBJ(g_createArena2Rects), OBJ(g_createArena2Rects) + 2 * 16, 0xb4);
}

void (profileList_layout)(void)       /* a column: 13 rows 0x14 apart */
{
	for (u32 rec = OBJ(g_profileListRects), d = 0; rec < OBJ(g_profileListRects) + 13 * 16; rec += 16, d += 0x14) {   /* (13 rectangles) */
		int y = g_profilePageTop, x = g_profilePageLeft;
		rect_set(x + 0x20, d + y + 0x23, x + 0xd4, d + y + 0x36, (int *)RELOC(rec));
	}
}

void (mapList_layout)(void)
{
	int y = 0x57;
	for (u32 rec = (OBJ(g_mapListRects) + 0xa0); rec < (OBJ(g_mapListRects) + 0x140); rec += 16, y += 0x18) {
		rect_set(0x96, y, 0x154, y + 0x14, (int *)(RELOC(rec) - 0xa0));
		rect_set(0x168, y, 0x1a4, y + 0x14, (int *)RELOC(rec));
	}
	rect_set(0x1c2, 0x96, 0x1e0, 0xca, (int *)(OBJ(g_mapListRects) + 0x140));
	rect_set(0x1c2, 0xdc, 0x1e0, 0x110, (int *)(OBJ(g_mapListRects) + 0x150));
	int x = 0xaa;
	for (u32 rec = (OBJ(g_mapListRects) + 0x180); rec < (OBJ(g_mapListRects) + 0x1a0); rec += 16, x += 0xa0) {
		rect_set(x, 0x15e, x + 0x8c, 0x17e, (int *)(RELOC(rec) - 0x20));
		rect_set(x, 0x186, x + 0x8c, 0x1a6, (int *)RELOC(rec));
	}
}
