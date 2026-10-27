/* batch 89 */
/* an actor (0..15, active mostly) of a player (0..7) whose part type (0..3) record is cleared (empty names: the
   cache lookups give 0 at once, so no cache is set up) with random counts for its variant (0..3): mostly within
   the names the record holds, now and then past the memory (fatal) */
typedef struct { int typeOff, base, stride, nameOff, nameStride, kcOff, knOff, maxNames, countOff; } PartType;
static const PartType g_partTypes[5] = {   /* countOff: the table's count (after the table, not before it) */
	{ 0x30c, 0x13c9b30, 0xaa8, 0x448, 0x220, 0x888, 0x990, 8, 0x13eb000 },  { 0x310, 0x13eb004, 0xabc, 0x448, 0x220, 0x888, 0x990, 8, 0x140c8bc },
	{ 0x314, 0x140c8c0, 0x1300, 0x848, 0x440, 0x10c8, 0x11d0, 16, 0x1447ec0 }, { 0x318, 0x1447ec4, 0x13f4, 0x848, 0x440, 0x10c8, 0x11d0, 16, 0x148646c },
	{ 0x31c, 0x1486470, 0x1820, 0xa48, 0x550, 0x14e8, 0x15f0, 20, 0x14d1ab0 } };
static char *part_actor(void)
{
	char *sc = BUF; int a = irnd(0, 15), p = irnd(0, 7);
	char *ac = sc + 0x1cd93a8 + a * 0x8888;
	S32(ac, 0x108) = irnd(0, 9) ? 1 : 0; S32(ac, 0x10c) = p; S32(ac, 0x484) = irnd(0, 3);
	fill(ac + 0x554, 0x30); S32(ac + 0x554, 0xc) = irnd(0, 2);
	g_a[0] = a;
	return ac;
}
static void part_counts(char *rec, int v, int cOff, int kcOff, int maxNames)
{
	S32(rec, cOff + v * 4) = irnd(0, 9) ? irnd(0, maxNames) : irnd(0, 200);
	S32(rec, kcOff + v * 4) = irnd(0, 4) ? irnd(0, 2) : irnd(0, 20);
}
static void parttype_setup(int k)
{
	const PartType *t = &g_partTypes[k];
	char *ac = part_actor(), *pl = BUF + 0x1561b68 + S32(ac, 0x10c) * 0x47fd2;
	int idx = irnd(0, 3);
	S32(pl, t->typeOff) = idx;
	char *rec = BUF + t->base + idx * t->stride;
	memset(rec, 0, (size_t)t->stride);
	part_counts(rec, S32(ac, 0x484), 0x40, t->kcOff, t->maxNames);
}
ST(FUN_0045e1f0, parttype_setup(0);, (TC(void, 0x45e1f0, char *, int)(BUF, g_a[0]), 0), (FUN_0045e1f0(BUF, (DWORD)g_a[0]), 0))
ST(actor_updateBody, parttype_setup(1);, (TC(void, 0x45e2c0, char *, int)(BUF, g_a[0]), 0), (actor_updateBody(BUF, (DWORD)g_a[0]), 0))
ST(FUN_0045e390, parttype_setup(2);, (TC(void, 0x45e390, char *, int)(BUF, g_a[0]), 0), (FUN_0045e390(BUF, (DWORD)g_a[0]), 0))
ST(FUN_0045e460, parttype_setup(3);, (TC(void, 0x45e460, char *, int)(BUF, g_a[0]), 0), (FUN_0045e460(BUF, (DWORD)g_a[0]), 0))
ST(FUN_0045e530, parttype_setup(4);, (TC(void, 0x45e530, char *, int)(BUF, g_a[0]), 0), (FUN_0045e530(BUF, (DWORD)g_a[0]), 0))
/* actor_updatePart: slot 0..5 (the actor's current slot sometimes), the player's item there (-1..3), its cleared
   record with counts for both lists of the variant (0..3) */
static void itempart_setup(void)
{
	char *ac = part_actor(), *pl = BUF + 0x1561b68 + S32(ac, 0x10c) * 0x47fd2;
	int slot = irnd(0, 5), var = irnd(0, 3), it = irnd(0, 5) ? irnd(0, 3) : -1;
	S32(ac, 0x140) = irnd(0, 1) ? slot : irnd(0, 5);
	fill(ac + 0x4cc, 4);
	S32(pl, 0x320 + slot * 4) = it;
	if (it >= 0) {
		char *rec = BUF + 0x14d1ab4 + it * 0x2e18;
		memset(rec, 0, 0x2e18);
		part_counts(rec, var, 0x40, 0x12dc, 15);
		part_counts(rec, var, 0x16fc, 0x2998, 15);
		S32(rec, 0x2dc0) = irnd(-1, 9);
	}
	fill(ac + 0x587c, 0x30); fill(ac + 0x701c, 0x30); fill(ac + 0x40dc, 0x30);
	g_a[1] = slot; g_a[2] = var;
}
ST(actor_updatePart, itempart_setup();, (TC(void, 0x45e600, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
   (actor_updatePart(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
