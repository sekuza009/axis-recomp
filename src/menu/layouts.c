/* layouts.c: the screens' button layouts: each screen fills its table of button rectangles (left, top, right, bottom in menu units; see hit_tests.c) from its panel's position, usually as rows or columns of equal buttons. */
#include "../game.h"

#define GAME_I32(a) GAME_VAR(int, a)
#define GAME_U32(a) GAME_VAR(u32, a)
#define GAME_F32(a) GAME_VAR(float, a)
#define FIELD_I32(p, o) GAME_VAR(int, (u8 *)RELOC(p) + (o))

/* one rectangle: each corner value = global + constant */
static void rect1(u32 rec, u32 g0, int c0, u32 g1, int c1, u32 g2, int c2, u32 g3, int c3)
{
	set4ints(GAME_I32(g0) + c0, GAME_I32(g1) + c1, GAME_I32(g2) + c2, GAME_I32(g3) + c3, (int *)RELOC(rec));
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
		set4ints(v[0], v[1], v[2], v[3], (int *)RELOC(rec));
	}
}

/* a column of buttons 0x78 wide at y 0x104 .. 0x124, 0xa0 apart from x */
static void rects_column(u32 rec, u32 end, int x)
{
	for (; rec < end; rec += 16, x += 0xa0)
		set4ints(x, 0x104, x + 0x78, 0x124, (int *)RELOC(rec));
}

/* a row of buttons relative to a movable origin (x at ox, y at oy): stride dx, corners at x0 / y0 and x1 / y1 */
static void rects_row(u32 rec, u32 end, u32 ox, u32 oy, int x0, int x1, int y0, int y1, int dx)
{
	for (int d = 0; rec < end; rec += 16, d += dx) {
		int x = GAME_I32(ox), y = GAME_I32(oy);
		set4ints(d + x + x0, y + y0, d + x + x1, y + y1, (int *)RELOC(rec));
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
#define AX IMG(0x4dcc90)
#define AY IMG(0x4dcc94)
#define AX2 IMG(0x4dcc98)
#define AY2 IMG(0x4dcc9c)
static void armc_tabs(u32 rec)
{
	static const RArg a[4] = { RA(AX, 0x10, 1), RA(AY, -8, 0), RA(AX, 0x70, 1), RA(AY, 0x18, 0) };
	static const RArg b[4] = { RA(AX, 0x10, 1), RA(AY2, -0x20, 0), RA(AX, 0x70, 1), RA(AY2, 0, 0) };
	rect_spec(rec, rec + 0x30, 0x64, a);
	rect_spec(rec + 0x30, rec + 0x50, 0x64, b);
}

void (arenaCreate_layout)(void) { rects_column(IMG(0x4dbb80), IMG(0x4dbba0), 0xb4); }

void (leaveDialog_layout)(void) { rects_column(IMG(0x9dd390), IMG(0x9dd3b0), 0xb4); }

void (deleteDialog_layout)(void) { rects_row(IMG(0x9f6808), IMG(0x9f6828), IMG(0x9f8f1c), IMG(0x9f8f0c), 0x6e, 0xce, 0x3c, 0x5c, 0x78); }

void (secondDialog_layout)(void) { rects_row(IMG(0x9f8ee8), IMG(0x9f8f08), IMG(0x9f6834), IMG(0x9f683c), 0x6e, 0xce, 0x3c, 0x5c, 0x78); }

void (newNameDialog_layout)(void) { rects_row(IMG(0x9f9020), IMG(0x9f9040), IMG(0x9f8eac), IMG(0x9f8ea8), 0xa0, 0x100, 0x5a, 0x7a, 0x78); }

void (popup_layout)(void) { rects_row(IMG(0x9dd3b8), IMG(0x9dd3d8), IMG(0x9dd1a0), IMG(0x9dd1ac), 0x64, 0xdc, -0x40, -0x20, 0xb4); }

void (lobbyTop_layout)(void) { rects_row(IMG(0x4dbb40), IMG(0x4dbb60), IMG(0x4dba70), IMG(0x4dba74), 0x32, 0xe6, 0x64, 0x94, 0xc8); }

void (setupOptions_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4dddd0), 0xa, 0), RA(IMG(0x4dddd4), 0x3c, 1), RA(IMG(0x4dddd0), 0x186, 0), RA(IMG(0x4dddd4), 0x5c, 1) };
	static const RArg b[4] = { RA(IMG(0x4dddd0), 0x64, 1), RA(IMG(0x4ddddc), -0x40, 0), RA(IMG(0x4dddd0), 0xdc, 1), RA(IMG(0x4ddddc), -0x20, 0) };
	rect_spec(IMG(0x4ddde0), IMG(0x4dde50), 0x28, a); rect_spec(IMG(0x4dde50), IMG(0x4dde70), 0x8c, b);
}

void (loginDialog_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd6e8), 0x30, 0), RA(IMG(0x9dd6ec), 0x30, 1), RA(IMG(0x9dd6e8), 0x210, 0), RA(IMG(0x9dd6ec), 0x58, 1) };
	static const RArg b[4] = { RA(IMG(0x9dd6e8), 0x5a, 1), RA(IMG(0x9dd6f4), -0x40, 0), RA(IMG(0x9dd6e8), 0xfa, 1), RA(IMG(0x9dd6f4), -0x20, 0) };
	rect_spec(IMG(0x9dce50), IMG(0x9dce90), 0x30, a); rect_spec(IMG(0x9dce90), IMG(0x9dceb0), 0xc8, b);
}

void (arenaNameDialog_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4dbb68), 0x30, 0), RA(IMG(0x4dbb6c), 0x60, 1), RA(IMG(0x4dbb68), 0x188, 0), RA(IMG(0x4dbb6c), 0x78, 1) };
	static const RArg b[4] = { RA(IMG(0x4dbb68), 0x32, 1), RA(IMG(0x4dbb6c), 0xdc, 0), RA(IMG(0x4dbb68), 0x96, 1), RA(IMG(0x4dbb6c), 0xfc, 0) };
	rect_spec(IMG(0x4db588), IMG(0x4db5b8), 0x19, a); rect_spec(IMG(0x4db5b8), IMG(0x4db5e8), 0x78, b);
}

void (roomLogin_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd358), 0xb8, 0), RA(IMG(0x9dd35c), 0x50, 1), RA(IMG(0x9dd358), 0x1a8, 0), RA(IMG(0x9dd35c), 0x70, 1) };
	static const RArg b[4] = { RA(IMG(0x9dd358), 0x30, 1), RA(IMG(0x9dd364), -0x40, 0), RA(IMG(0x9dd358), 0xa8, 1), RA(IMG(0x9dd364), -0x18, 0) };
	rect_spec(IMG(0x9dd7e0), IMG(0x9dd800), 0x30, a); rect_spec(IMG(0x9dd800), IMG(0x9dd830), 0xa0, b);
}

void (skirmish_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9f16a8), 0x10, 0), RA(IMG(0x9f16ac), 0x44, 1), RA(IMG(0x9f16a8), 0x25d, 0), RA(IMG(0x9f16ac), 0x5c, 1) };
	static const RArg b[4] = { RA(IMG(0x9f16b0), -0x12c, 1), RA(IMG(0x9f16b4), -0x40, 0), RA(IMG(0x9f16b0), -0xb4, 1), RA(IMG(0x9f16b4), -0x20, 0) };
	rect_spec(IMG(0x9ef220), IMG(0x9ef2a0), 0x1a, a); rect_spec(IMG(0x9ef2a0), IMG(0x9ef2c0), 0x8c, b);
}

void (account_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd368), 0x84, 0), RA(IMG(0x9dd36c), 0x52, 1), RA(IMG(0x9dd370), -0x30, 0), RA(IMG(0x9dd36c), 0x68, 1) };
	static const RArg b[4] = { RA(IMG(0x9dd368), 0x7d, 1), RA(IMG(0x9dd374), -0x30, 0), RA(IMG(0x9dd368), 0xf5, 1), RA(IMG(0x9dd374), -0x10, 0) };
	rect_spec(IMG(0x9dd400), IMG(0x9dd440), 0x1c, a); rect_spec(IMG(0x9dd440), IMG(0x9dd460), 0xa0, b);
}

void (skirmishButtons_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9f16b0), -0x12c, 1), RA(IMG(0x9f16b4), -0x30, 0), RA(IMG(0x9f16b0), -0xb4, 1), RA(IMG(0x9f16b4), -0x10, 0) };
	static const RArg b[4] = { RA(IMG(0x9f16a8), 0x40, 1), RA(IMG(0x9f16b4), -0x30, 0), RA(IMG(0x9f16a8), 0xb8, 1), RA(IMG(0x9f16b4), -0x10, 0) };
	rect_spec(IMG(0x9f16c0), IMG(0x9f16e0), 0x8c, a); rect_spec(IMG(0x9f16e0), IMG(0x9f1700), 0x8c, b);
}

void (missionsel_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9f6308), 0x96, 1), RA(IMG(0x9f6314), -0x30, 0), RA(IMG(0x9f6308), 0x10e, 1), RA(IMG(0x9f6314), -0x10, 0) };
	rect_spec(IMG(0x9f6330), IMG(0x9f6350), 0x8c, a);
	set4ints(g_missionSelectLeft + 0x98, g_missionSelectTop + 0x4c, g_missionSelectLeft + 0xd0, g_missionSelectTop + 0x74, (int *)IMG(0x9f6350));
	set4ints(g_missionSelectLeft + 0x160, g_missionSelectTop + 0x4c, g_missionSelectLeft + 0x198, g_missionSelectTop + 0x74, (int *)IMG(0x9f6360));
}

void (pilotSelect_layout)(void)        /* 3 x 3 grid, then a row of two */
{
	u32 rec = IMG(0x9f8f38);
	for (int i = 0; rec < IMG(0x9f8fc8); i++, rec += 16) {
		int y = g_pilotSelectTop + (i / 3) * 86, x = g_pilotSelectLeft + (i % 3) * 86;
		set4ints(x + 0x20, y + 0x4c, x + 0x74, y + 0xa0, (int *)RELOC(rec));
	}
	static const RArg b[4] = { RA(IMG(0x9f8c54), 0xaa, 1), RA(IMG(0x9f682c), -0x40, 0), RA(IMG(0x9f8c54), 0x122, 1), RA(IMG(0x9f682c), -0x20, 0) };
	rect_spec(IMG(0x9f8fc8), IMG(0x9f8fe8), 0xa0, b);
}

void (gameList_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd4a8), 0x20, 1), RA(IMG(0x9dd4b4), -0x32, 0), RA(IMG(0x9dd4a8), 0x98, 1), RA(IMG(0x9dd4b4), -0x12, 0) };
	static const RArg b[4] = { RA(IMG(0x9dd4a8), 0x10, 0), RA(IMG(0x9dd4ac), 0x5e, 1), RA(IMG(0x9dd4a8), 0x204, 0), RA(IMG(0x9dd4ac), 0x74, 1) };
	static const RArg c[4] = { RA(IMG(0x9dd4a8), 0x226, 0), RA(IMG(0x9dd4ac), 0x6e, 1), RA(IMG(0x9dd4a8), 0x246, 0), RA(IMG(0x9dd4ac), 0xae, 1) };
	rect_spec(IMG(0x9dcd48), IMG(0x9dcd88), 0x8c, a); rect_spec(IMG(0x9dcd88), IMG(0x9dce18), 0x18, b); rect_spec(IMG(0x9dce18), IMG(0x9dce38), 0x50, c);
}

void (arenaGameList_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4db8c8), 0x23, 1), RA(IMG(0x4db8cc), 0x30, 0), RA(IMG(0x4db8c8), 0xc3, 1), RA(IMG(0x4db8cc), 0x48, 0) };
	static const RArg b[4] = { RA(IMG(0x4db8c8), 0x5a, 1), RA(IMG(0x4db8d4), -0x2c, 0), RA(IMG(0x4db8c8), 0xd2, 1), RA(IMG(0x4db8d4), -0xc, 0) };
	static const RArg c[4] = { RA(IMG(0x4db8c8), 0x10, 0), RA(IMG(0x4db8cc), 0x76, 1), RA(IMG(0x4db8c8), 0x204, 0), RA(IMG(0x4db8cc), 0x8c, 1) };
	static const RArg d[4] = { RA(IMG(0x4db8c8), 0x21e, 0), RA(IMG(0x4db8cc), 0xa0, 1), RA(IMG(0x4db8c8), 0x23e, 0), RA(IMG(0x4db8cc), 0xe0, 1) };
	rect_spec(IMG(0x4db720), IMG(0x4db750), 0xb4, a); rect_spec(IMG(0x4db750), IMG(0x4db780), 0x96, b);
	rect_spec(IMG(0x4db780), IMG(0x4db810), 0x18, c); rect_spec(IMG(0x4db810), IMG(0x4db830), 0x50, d);
}

void (profilePage_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9f8e48), 0x28, 1), RA(IMG(0x9f8ea4), -0x30, 0), RA(IMG(0x9f8e48), 0x88, 1), RA(IMG(0x9f8ea4), -0x10, 0) };
	static const short r[4][4] = { { 0x20, 0x23, 0xd4, 0x126 }, { 0xe0, 0x50, 0xf8, 0x80 }, { 0xe0, 0xb4, 0xf8, 0xe4 },
	                               { 0x1a4, 0x24, 0x1e4, 0x64 } };
	rect_spec(IMG(0x9f8c60), IMG(0x9f8ca0), 0x72, a);
	for (int k = 0; k < 4; k++)
		set4ints(g_profilePageLeft + r[k][0], g_profilePageTop + r[k][1], g_profilePageLeft + r[k][2], g_profilePageTop + r[k][3],
		         (int *)(IMG(0x9f8ca0) + k * 16));
}

void (armcParts_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x28, 1), RA(AX, 0xa0, 0), RA(AY, 0x54, 1) };
	armc_tabs(IMG(0x4dbc88));
	rect_spec(0x4dbce8, 0x4dbd48, 0x3f, c);
	rect1(0x4dbd48, AX2, -0xea, AY, 0x162, AX2, -0xc2, AY, 0x182);
	rect1(0x4dbd58, AX2, -0x22, AY, 0x162, AX2, 6, AY, 0x182);
	rect1(0x4dbd68, AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (armcColour_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x40, 1), RA(AX, 0xb0, 0), RA(AY, 0x6c, 1) };
	static const RArg d[4] = { RA(AX2, -0xb8, 0), RA(AY, 0x58, 1), RA(AX2, -0x18, 0), RA(AY, 0x6c, 1) };
	static const RArg e[4] = { RA(AX2, -0xb8, 0), RA(AY, 0x108, 1), RA(AX2, -0x18, 0), RA(AY, 0x11c, 1) };
	armc_tabs(IMG(0x4dcb38));
	rect_spec(0x4dcb88, 0x4dcbe8, 0x30, c);
	rect_spec(0x4dcbe8, 0x4dcc18, 0x30, d); rect_spec(0x4dcc18, 0x4dcc48, 0x30, e);
	rect1(0x4dcc48, AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (armcMain_layout)(void)
{
	static const RArg c[4] = { RA(AX, 0x10, 0), RA(AY, 0x40, 1), RA(AX, 0xb0, 0), RA(AY, 0x6c, 1) };
	armc_tabs(IMG(0x4dc2a8));
	rect_spec(0x4dc308, 0x4dc368, 0x30, c);
	rect1(0x4dc378, AX, 0x114, AY2, -0x20, AX, 0x174, AY2, 0);
	rect1(0x4dc388, AX, 0xe4, AY2, -0x1c, AX, 0x114, AY2, -4);
	rect1(0x4dc398, AX, 0x174, AY2, -0x1c, AX, 0x1a4, AY2, -4);
	rect1(0x4dc3a8, AX2, -0xa0, AY2, -0x20, AX2, 0, AY2, 0);
}

void (mapSelect_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd910), -0x32, 0), RA(IMG(0x9dd90c), 0x48, 1), RA(IMG(0x9dd910), -0x12, 0), RA(IMG(0x9dd90c), 0x88, 1) };
	static const RArg b[4] = { RA(IMG(0x9dd908), 0x10, 0), RA(IMG(0x9dd90c), 0xfe, 1), RA(IMG(0x9dd908), 0xd8, 0), RA(IMG(0x9dd90c), 0x10e, 1) };
	static const RArg c[4] = { RA(IMG(0x9dd908), 0x64, 1), RA(IMG(0x9dd914), -0x5c, 0), RA(IMG(0x9dd908), 0xdc, 1), RA(IMG(0x9dd914), -0x3c, 0) };
	static const RArg d[4] = { RA(IMG(0x9dd908), 0x64, 1), RA(IMG(0x9dd914), -0x34, 0), RA(IMG(0x9dd908), 0xdc, 1), RA(IMG(0x9dd914), -0x14, 0) };
	static const RArg e[4] = { RA(IMG(0x9dd908), 0x28, 0), RA(IMG(0x9dd90c), 0x2c, 1), RA(IMG(0x9dd910), -0x50, 0), RA(IMG(0x9dd90c), 0x3c, 1) };
	rect_spec(IMG(0x9dd950), IMG(0x9dd970), 0x64, a); rect_spec(IMG(0x9dd970), IMG(0x9dd990), 0x1e, b); rect_spec(IMG(0x9dd990), IMG(0x9dd9b0), 0xa0, c);
	rect_spec(IMG(0x9dd9b0), IMG(0x9dd9d0), 0xa0, d); rect_spec(IMG(0x9dd9d0), IMG(0x9dda70), 0x14, e);
}

void (setupControl_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4dde80), 0x46, 1), RA(IMG(0x4dde84), 0x10, 0), RA(IMG(0x4dde80), 0xaa, 1), RA(IMG(0x4dde84), 0x24, 0) };
	static const RArg b[4] = { RA(IMG(0x4dde80), 0x50, 1), RA(IMG(0x4dde8c), -0x30, 0), RA(IMG(0x4dde80), 0xc8, 1), RA(IMG(0x4dde8c), -0x10, 0) };
	static const RArg c[4] = { RA(IMG(0x4dde80), 0x30, 0), RA(IMG(0x4dde84), 0x59, 1), RA(IMG(0x4dde88), -0x18, 0), RA(IMG(0x4dde84), 0x70, 1) };
	rect_spec(IMG(0x4ddea8), IMG(0x4ddee8), 0x78, a); rect_spec(IMG(0x4ddee8), IMG(0x4ddf18), 0x8c, b); rect_spec(IMG(0x4ddf18), IMG(0x4ddfc8), 0x18, c);
	rect1(IMG(0x4ddd98), IMG(0x4dde80), 0xc8, IMG(0x4dde84), 0x88, IMG(0x4dde80), 0x108, IMG(0x4dde84), 0xa0);
	rect1(IMG(0x4ddda8), IMG(0x4dde80), 0x1d0, IMG(0x4dde84), 0x88, IMG(0x4dde80), 0x210, IMG(0x4dde84), 0xa0);
	rect1(IMG(0x4dddb8), IMG(0x4dde80), 0x108, IMG(0x4dde84), 0x88, IMG(0x4dde80), 0x1d0, IMG(0x4dde84), 0xa0);
}

void (setupSound_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4ddad0), 0x74, 0), RA(IMG(0x4ddad4), 0x94, 1), RA(IMG(0x4ddad0), 0x1ae, 0), RA(IMG(0x4ddad4), 0xb4, 1) };
	static const RArg b[4] = { RA(IMG(0x4ddad0), 0x90, 1), RA(IMG(0x4ddad4), 0x113, 0), RA(IMG(0x4ddad0), 0x108, 1), RA(IMG(0x4ddad4), 0x133, 0) };
	static const short r[5][4] = { { 0x50, 0x50, 0x8f, 0x70 }, { 0x191, 0x50, 0x1d0, 0x70 }, { 0x90, 0x50, 0x190, 0x70 },
	                               { 0x50, 0x8c, 0x8f, 0xac }, { 0x191, 0x8c, 0x1d0, 0xac } };
	for (int k = 0; k < 5; k++) rect1(IMG(0x4ddcf0) + k * 16, IMG(0x4ddad0), r[k][0], IMG(0x4ddad4), r[k][1], IMG(0x4ddad0), r[k][2], IMG(0x4ddad4), r[k][3]);
	rect_spec(IMG(0x4ddd40), IMG(0x4ddd70), 0x28, a); rect_spec(IMG(0x4ddd70), IMG(0x4ddd90), 0x8c, b);
}

void (ranking_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dced8), 0x7d, 1), RA(IMG(0x9dcee4), -0x30, 0), RA(IMG(0x9dced8), 0x11d, 1), RA(IMG(0x9dcee4), -0x10, 0) };
	static const short r[4][2] = { { 0x112, 0x144 }, { 0x14e, 0x130 }, { 0x18a, 0x1bc }, { 0x20c, 0x23e } };   /* [1] is inverted */
	rect1(IMG(0x9dd4c0), IMG(0x9dced8), 0xb2, IMG(0x9dcedc), 0x26, IMG(0x9dced8), 0xe6, IMG(0x9dcedc), 0x3e);
	rect1(IMG(0x9dd4d0), IMG(0x9dced8), 0x144, IMG(0x9dcedc), 0x26, IMG(0x9dced8), 0x178, IMG(0x9dcedc), 0x3e);
	rect1(IMG(0x9dd4e0), IMG(0x9dcee0), -0x78, IMG(0x9dcedc), 0x24, IMG(0x9dcee0), -0x14, IMG(0x9dcedc), 0x40);
	rect_spec(IMG(0x9dd4f0), IMG(0x9dd510), 0xc8, a);
	for (int k = 0; k < 4; k++) rect1(IMG(0x9dd510) + k * 16, IMG(0x9dced8), r[k][0], IMG(0x9dcedc), 0x50, IMG(0x9dced8), r[k][1], IMG(0x9dcedc), 0x66);
}

void (roomSettings_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x9dd1b8), 0x64, 1), RA(IMG(0x9dd1c4), -0x40, 0), RA(IMG(0x9dd1b8), 0x104, 1), RA(IMG(0x9dd1c4), -0x20, 0) };
	options_panel(IMG(0x9dd6f8), 0, IMG(0x9dd1b8), IMG(0x9dd1bc), IMG(0x9dd1c0));
	rect_spec(IMG(0x9dd778), IMG(0x9dd798), 0xc8, a);
	options_panel(0, IMG(0x9dd798), IMG(0x9dd1b8), IMG(0x9dd1bc), IMG(0x9dd1c0));
}

/* ---- batch 18: arena options layout, entering the setup screen and the game room --------------- */
void (arenaOptions_layout)(void)
{
	static const RArg a[4] = { RA(IMG(0x4dbb00), 0x3c, 1), RA(IMG(0x4dbb0c), -0x5a, 0), RA(IMG(0x4dbb00), 0x104, 1), RA(IMG(0x4dbb0c), -0x3a, 0) };
	static const RArg b[4] = { RA(IMG(0x4dbb00), 0x3c, 1), RA(IMG(0x4dbb0c), -0x32, 0), RA(IMG(0x4dbb00), 0x104, 1), RA(IMG(0x4dbb0c), -0x12, 0) };
	options_panel(IMG(0x4db5e8), 0, IMG(0x4dbb00), IMG(0x4dbb04), IMG(0x4dbb08));
	rect_spec(IMG(0x4db668), IMG(0x4db688), 0xfa, a); rect_spec(IMG(0x4db688), IMG(0x4db6a8), 0xfa, b);
	options_panel(0, IMG(0x4db6a8), IMG(0x4dbb00), IMG(0x4dbb04), IMG(0x4dbb08));
	rects_column(IMG(0x4db6e8), IMG(0x4db708), 0xb4);
}

void (profileList_layout)(void)       /* a column: 13 rows 0x14 apart */
{
	for (u32 rec = IMG(0x9f8d78), d = 0; rec < IMG(0x9f8e48); rec += 16, d += 0x14) {
		int y = g_profilePageTop, x = g_profilePageLeft;
		set4ints(x + 0x20, d + y + 0x23, x + 0xd4, d + y + 0x36, (int *)RELOC(rec));
	}
}

void (mapList_layout)(void)
{
	int y = 0x57;
	for (u32 rec = IMG(0x4d93f8); rec < IMG(0x4d9498); rec += 16, y += 0x18) {
		set4ints(0x96, y, 0x154, y + 0x14, (int *)(RELOC(rec) - 0xa0));
		set4ints(0x168, y, 0x1a4, y + 0x14, (int *)RELOC(rec));
	}
	set4ints(0x1c2, 0x96, 0x1e0, 0xca, (int *)IMG(0x4d9498));
	set4ints(0x1c2, 0xdc, 0x1e0, 0x110, (int *)IMG(0x4d94a8));
	int x = 0xaa;
	for (u32 rec = 0x4d94d8; rec < 0x4d94f8; rec += 16, x += 0xa0) {
		set4ints(x, 0x15e, x + 0x8c, 0x17e, (int *)(RELOC(rec) - 0x20));
		set4ints(x, 0x186, x + 0x8c, 0x1a6, (int *)RELOC(rec));
	}
}
