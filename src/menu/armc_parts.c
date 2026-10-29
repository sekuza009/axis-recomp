/* armc_parts.c: the ARM CENTER's part-info records (0x80 bytes): what the screen shows of an actor type picked as
   a part or a weapon: its folder's last name, six values copied from its ActorInfo, eight scaled. */
#include "../game.h"
#include <string.h>

#define FIELD(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* ActorInfo offsets copied as they are (record offset, ActorInfo offset) */
static const short copied[6][2] = { { 0x40, 0x2dbc }, { 0x44, 0x2dc0 }, { 0x48, 0x2dc4 }, { 0x4c, 0x2dc8 },
                                    { 0x50, 0x2ddc }, { 0x54, 0x2de0 } };

/* and those scaled by a constant of the game (record offset, ActorInfo offset, constant's address) */
static const struct { short dst, src; u32 scale; } scaled[8] = {
	{ 0x58, 0x2de4, 0x4a9420 }, { 0x5c, 0x2de8, 0x4a9420 }, { 0x60, 0x2dec, 0x4a93ec }, { 0x64, 0x2df0, 0x4a9420 },
	{ 0x68, 0x2df4, 0x4a9420 }, { 0x70, 0x2e08, 0x4a94bc }, { 0x74, 0x2e0c, 0x4a93ec }, { 0x78, 0x2e10, 0x4a94bc } };

/* record rec for actor type idx; idx -1: the record emptied (its +0x40 -1) */
static void part_info(u8 *rec, int idx)
{
	if (idx == -1) {
		memset(rec, 0, 64);
		FIELD(int, rec, 0x40) = -1;
		memset(rec + 0x44, 0, 0x3c);
		return;
	}
	ActorInfo *info = &g_scene->actorInfo[idx];

	/* the name: the folder path's part after its last slash */
	char path[128] = { 0 };
	strcpy(path, info->name);
	int n = (int)strlen(path), i = n - 1;
	while (i >= 0 && path[i] != '\\' && path[i] != '/')
		i--;
	memset(rec, 0, 64);
	if (i + 1 < n)
		memcpy(rec, path + i + 1, n - (i + 1));

	for (int k = 0; k < 6; k++)
		FIELD(int, rec, copied[k][0]) = FIELD(int, info, copied[k][1]);
	for (int k = 0; k < 8; k++) {
		if (k == 5)
			FIELD(int, rec, 0x6c) = FIELD(int, info, 0x2df8);
		FIELD(float, rec, scaled[k].dst) =
			(float)((long double)FIELD(float, info, scaled[k].src) * GAME_VAR(float, scaled[k].scale));
	}
	FIELD(int, rec, 0x7c) = FIELD(int, info, 0x2db8);
}

/* 0x41ca50: the record of weapon slot slot (0x4dbe50, 0x80 apart) */
void (armc_41ca50)(int slot, int idx) { part_info((u8 *)0x4dbe50 + slot * 0x80, idx); }

/* 0x41cca0: the record of the part being looked at (0x4dc150); the first type picked is kept in 0x4dc198 */
void (armc_41cca0)(int idx)
{
	part_info((u8 *)0x4dc150, idx);
	if (idx != -1 && GAME_VAR(int, 0x4dc194) == -1)
		GAME_VAR(int, 0x4dc198) = idx;
}

/* ---- 0x41c510: the ARM CENTER's stats panel from the local player's actor in the scene (*0x9087b4): a speed (the
   root of +0x0 times a constant), the actor's values times the game's scale constants, its part's and weapon's
   records' values; every product extended precision, rounded once on store, the second factor from memory as in
   the original. Returns the scene ---- */
typedef long double X;
static void mulf(u32 dst, const float *a, const float *b) { GAME_VAR(float, dst) = (float)fmul_m(fld_m(a), b); }
static void copyf(u32 dst, const float *src) { GAME_VAR(float, dst) = (float)fld_m(src); }   /* (an SNaN quieted) */

u8 *(armc_41c510)(void)
{
	u8 *g = GAME_VAR(u8 *, 0x9087b4);
	u8 *A = g + FIELD(int, g, 0x234240d) * 0x8888;
	X s = fld_m(&FIELD(float, A, 0x1ecca70));
	__asm__("fsqrt" : "+t"(s));
	s = s * GAME_VAR(double, 0x4a94c0);
	GAME_VAR(float, 0x4dcaa0) = (float)s;
	mulf(0x4dcaa4, &FIELD(float, A, 0x1ecca74), (const float *)0x4a93ec);
	GAME_VAR(int, 0x4dcaa8) = FIELD(int, A, 0x1ecca78);
	mulf(0x4dcaac, &FIELD(float, A, 0x1ecca7c), (const float *)0x4a93f4);
	mulf(0x4dcab0, &FIELD(float, A, 0x1ecca80), (const float *)0x4a94bc);
	for (int i = 0; i < 7; i++)
		GAME_VAR(int, 0x4dcab4 + i * 4) = FIELD(int, A, 0x1ecca8c + i * 4);
	copyf(0x4dcad0, &FIELD(float, A, 0x1eccaa8));
	u8 *player = g + FIELD(int, A, 0x1eccb7c) * 0x47fd2;
	u8 *part = g + FIELD(int, player, 0x1755548) * 0x13f4;
	copyf(0x4dcad4, &FIELD(float, part, 0x163c96c));
	mulf(0x4dcad8, &FIELD(float, part, 0x163c970), (const float *)0x4a93f4);
	mulf(0x4dcadc, &FIELD(float, part, 0x163c974), (const float *)0x4a93f4);
	mulf(0x4dcae0, &FIELD(float, part, 0x163c97c), (const float *)0x4a93f4);
	mulf(0x4dcae4, &FIELD(float, part, 0x163c978), (const float *)0x4a93f4);
	GAME_VAR(int, 0x4dcae8) = FIELD(int, g + FIELD(int, player, 0x175554c) * 0x1820, 0x167b334);
	mulf(0x4dcaec, &FIELD(float, A, 0x1eccab4), (const float *)0x4a94bc);
	mulf(0x4dcaf0, &FIELD(float, A, 0x1eccab8), (const float *)0x4a94bc);
	mulf(0x4dcaf4, &FIELD(float, A, 0x1eccabc), (const float *)0x4a94bc);
	mulf(0x4dcaf8, &FIELD(float, A, 0x1eccac0), (const float *)0x4a94b8);
	mulf(0x4dcafc, (const float *)0x4dcaf8, &FIELD(float, A, 0x1eccac4));
	GAME_VAR(float, 0x4dcb00) = (float)-fmul_m(fld_m((const float *)0x4dcaf8), &FIELD(float, A, 0x1eccac8));
	mulf(0x4dcb04, (const float *)0x4dcaf8, &FIELD(float, A, 0x1eccacc));
	copyf(0x4dcb0c, &FIELD(float, A, 0x1ecca84));
	copyf(0x4dcb08, &FIELD(float, A, 0x1ecca88));
	return g;
}

/* a part's name for the panel: its folder path with '\' and '/' turned into '-', in a zeroed 64-byte field (through
   a zeroed 128-byte buffer; the terminator is not copied) */
static void panel_name(u32 dst, const char *name)
{
	char buf[128];
	memset(buf, 0, sizeof buf);
	strcpy(buf, name);
	int len = (int)strlen(buf);
	for (int i = len - 1; i >= 0; i--) {
		if (buf[i] == '\\')
			buf[i] = '-';
		if (buf[i] == '/')
			buf[i] = '-';
	}
	memset((void *)dst, 0, 64);
	if (len > 0)
		memcpy((void *)dst, buf, len);
}

/* 0x41b750: the ARM CENTER's part panels for the local player's mech: for its head, chest, arm, leg and weapon (the
   player record's indices +0x175553c ..) the part's name and stats, some scaled by the game's constants. Returns the
   weapon's index */
int (armc_41b750)(void)
{
	u8 *g = GAME_VAR(u8 *, 0x9087b4);
	u8 *player = g + FIELD(int, g + FIELD(int, g, 0x234240d) * 0x8888, 0x1eccb7c) * 0x47fd2;
	u8 *p = g + FIELD(int, player, 0x175553c) * 0xaa8;   /* head */
	panel_name(0x4dceb8, (const char *)p + 0x15bd1f8);
	mulf(0x4dcef8, &FIELD(float, p, 0x15bdc8c), (const float *)0x4a9420);
	mulf(0x4dcefc, &FIELD(float, p, 0x15bdc90), (const float *)0x4a93ec);
	GAME_VAR(int, 0x4dcf00) = FIELD(int, p, 0x15bdc94);
	mulf(0x4dcf04, &FIELD(float, p, 0x15bdc98), (const float *)0x4a93f4);
	mulf(0x4dcf08, &FIELD(float, p, 0x15bdc9c), (const float *)0x4a94bc);
	copyf(0x4dcf0c, &FIELD(float, p, 0x15bdc88));
	p = g + FIELD(int, player, 0x1755540) * 0xabc;   /* chest */
	panel_name(0x4dbc08, (const char *)p + 0x15de6cc);
	copyf(0x4dbc48, &FIELD(float, p, 0x15df17c));
	GAME_VAR(int, 0x4dbc4c) = FIELD(int, p, 0x15df180);
	GAME_VAR(int, 0x4dbc50) = FIELD(int, p, 0x15df184);
	p = g + FIELD(int, player, 0x1755544) * 0x1300;   /* arm */
	panel_name(0x4dc250, (const char *)p + 0x15fff88);
	for (int i = 0; i < 5; i++)
		GAME_VAR(int, 0x4dc290 + i * 4) = FIELD(int, p, 0x1601274 + i * 4);
	copyf(0x4dc2a4, &FIELD(float, p, 0x1601270));
	p = g + FIELD(int, player, 0x1755548) * 0x13f4;   /* leg */
	panel_name(0x4dc1e8, (const char *)p + 0x163b58c);
	copyf(0x4dc228, &FIELD(float, p, 0x163c968));
	copyf(0x4dc22c, &FIELD(float, p, 0x163c96c));
	mulf(0x4dc230, &FIELD(float, p, 0x163c970), (const float *)0x4a93f4);
	mulf(0x4dc234, &FIELD(float, p, 0x163c974), (const float *)0x4a93f4);
	mulf(0x4dc238, &FIELD(float, p, 0x163c97c), (const float *)0x4a93f4);
	mulf(0x4dc23c, &FIELD(float, p, 0x163c978), (const float *)0x4a93f4);
	copyf(0x4dc240, &FIELD(float, p, 0x163c964));
	int weapon = FIELD(int, player, 0x175554c);
	p = g + weapon * 0x1820;
	panel_name(0x4dce40, (const char *)p + 0x1679b38);
	GAME_VAR(int, 0x4dce80) = FIELD(int, p, 0x167b334);
	for (int i = 0; i < 3; i++)
		mulf(0x4dce84 + i * 4, &FIELD(float, p, 0x167b33c + i * 4), (const float *)0x4a94bc);
	for (int i = 0; i < 4; i++)
		mulf(0x4dce90 + i * 4, &FIELD(float, p, 0x167b348 + i * 4), (const float *)0x4a94b8);
	GAME_VAR(u32, 0x4dcfd8) = 0x3f800000;
	copyf(0x4dcea0, &FIELD(float, p, 0x167b330));
	return weapon;
}

/* 0x40f340: mech part `part` (0 .. 4: head, chest, arm, leg, booster) stepped through its list, back (dir 1) or on
   (wrapping at both ends): its cursor, the list's count and entries, the chosen part (0x4dc760 + 4 * part), and
   the mech marked changed (0x4dcc58). Returns what the original leaves in eax: the new part on the even steps back
   and odd steps on, else the cursor (another part: the part number) */
u32 (armc_40f340)(u32 part, int dir)
{
	static const struct { u32 cursor, count, list; } parts[5] = {
		{ 0x4dcc8c, 0x4dc780, 0x4dc3e8 }, { 0x4dcf3c, 0x4dcc60, 0x4dcd6c }, { 0x4dbc7c, 0x4dca90, 0x4dc964 },
		{ 0x4dcea4, 0x4dca94, 0x4dc89c }, { 0x4dcb30, 0x4dc890, 0x4dbd7c } };
	GAME_VAR(int, 0x4dcc58) = 1;
	if (part > 4)
		return part;
	int *cursor = (int *)parts[part].cursor, count = GAME_VAR(int, parts[part].count);
	if (dir == 1) {
		if (--*cursor < 0)
			*cursor = count - 1;
	} else if (++*cursor >= count)
		*cursor = 0;
	u32 chosen = ((const u32 *)parts[part].list)[*cursor];
	GAME_VAR(u32, 0x4dc760 + part * 4) = chosen;
	return (part & 1) == (dir == 1 ? 0u : 1u) ? chosen : (u32)*cursor;
}
