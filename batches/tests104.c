/* batch 103 */
/* a player's mech: every part and item record filled with floats of 0.1..100 (stats), their shape / skeleton name
   lists emptied and their counts set (part_counts), the player's part types 0..3 and items -1..3 or the special ones
   (0x1b..0x24), an actor of that player; a and b floats; a pointer to the player index */
static void statrec(char *rec, int size, int cOff, int kcOff, int nOff, int nStride, int knOff, int maxNames)
{
	for (int o = 0; o + 4 <= size; o += 4) SF(rec, o) = (float)irnd(1, 1000) / 10.0f;
	for (int v = 0; v < 4; v++) { memset(rec + nOff + v * nStride, 0, (size_t)nStride); memset(rec + knOff + v * 0x80, 0, 0x80); }
	memset(rec, 0, 0x40);
	for (int v = 0; v < 4; v++) part_counts(rec, v, cOff, kcOff, maxNames);
}
static int g_spf;                       /* the player index (an int; the decompiler typed it float) */
static void mechsetup_setup(void)
{
	int p = irnd(0, 7), a = irnd(0, 5);
	part_actors(p);
	char *pl = BUF + 0x1561b68 + p * 0x47fd2;
	for (int k = 0; k < 5; k++) {
		const PartType *t = &g_partTypes[k];
		for (int ty = 0; ty < 4; ty++) statrec(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->nameOff, t->nameStride, t->knOff, t->maxNames);
		S32(pl, t->typeOff) = irnd(0, 3);
	}
	static const int items[] = { 0, 1, 2, 3, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x21, 0x22, 0x23, 0x24 };
	for (int i = 0; i < 14; i++) {
		char *r = BUF + 0x14d1ab4 + items[i] * 0x2e18;
		statrec(r, 0x2e18, 0x40, 0x12dc, 0x94c, 0x330, 0x1468, 15);
		for (int v = 0; v < 4; v++) { memset(r + 0x2008 + v * 0x330, 0, 0x330); memset(r + 0x2b24 + v * 0x80, 0, 0x80); part_counts(r, v, 0x16fc, 0x2998, 15); }
		S32(r, 0x2dc0) = irnd(0, 2) ? -1 : irnd(0, 9);
	}
	for (int s = 0; s < 6; s++) S32(pl, 0x320 + s * 4) = irnd(0, 2) ? items[irnd(0, 13)] : -1;
	char *ac = BUF + 0x1cd93a8 + a * 0x8888;
	ResourceSet_init_463a40(ac);
	S32(ac, 0x108) = 1; S32(ac, 0x10c) = p; S32(ac, 0x484) = irnd(0, 3); S32(ac, 0x49c) = irnd(0, 3); S32(ac, 0x140) = irnd(0, 5);
	fill(ac + 0x3f0, 0x100);
	S32(BUF, 0x20f3ab8) = irnd(0, 13); S32(BUF, 0x1561b64) = 40;
	g_spf = p;
	float x = (float)irnd(-1000, 1000) / 10.0f, y = (float)irnd(-1000, 1000) / 10.0f;
	g_a[0] = a; memcpy(&g_a[1], &x, 4); memcpy(&g_a[2], &y, 4); g_a[3] = (int)&g_spf;
}
ST(actor_setupFromParts, mechsetup_setup();, (TC(void, 0x457330, char *, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3]), 0),
   (actor_setupFromParts(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3]), 0))
