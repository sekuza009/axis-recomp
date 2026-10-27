/* batch 90 */
/* 0..6 actors of random players (variants 0..3), the player count 0..8; a type record (the new type, cleared:
   empty shape / skeleton names, see part_counts) with a name of up to 30 characters, every variant's counts set */
static void part_actors(int p)
{
	int n = irnd(0, 6);
	S32(BUF, 0x202e8c8) = n; S32(BUF, 0x19e1888) = irnd(0, 8);
	for (int a = 0; a < n; a++) {
		char *ac = BUF + 0x1cd93a8 + a * 0x8888;
		S32(ac, 0x108) = irnd(0, 9) ? 1 : 0; S32(ac, 0x10c) = irnd(0, 2) ? p : irnd(0, 7);
		S32(ac, 0x484) = irnd(0, 3); S32(ac, 0x49c) = irnd(0, 3); S32(ac, 0x140) = irnd(0, 5);
		fill(ac + 0x554, 0x30); S32(ac + 0x554, 0xc) = irnd(0, 2);
		fill(ac + 0x40dc, 0x30); fill(ac + 0x587c, 0x30); fill(ac + 0x701c, 0x30);
		S32(ac + 0x40dc, 0xc) = 0; S32(ac + 0x587c, 0xc) = 0; S32(ac + 0x701c, 0xc) = 0;
	}
}
static void part_record(char *rec, int size, int cOff, int kcOff, int maxNames)
{
	memset(rec, 0, (size_t)size);
	fill_str(rec, 30, 'A', 'Z');
	for (int v = 0; v < 4; v++) part_counts(rec, v, cOff, kcOff, maxNames);
}
static void settype_setup(int k)
{
	const PartType *t = &g_partTypes[k];
	int p = irnd(0, 7), cur = irnd(0, 3), c = irnd(0, 9), ty = c == 0 ? -1 : c == 1 ? cur : irnd(0, 3);
	char *pl = BUF + 0x1561b68 + p * 0x47fd2;
	part_actors(p);
	fill(pl + 0x4c, 0x40); S32(pl, t->typeOff) = cur;
	S32(BUF, t->countOff) = irnd(0, 19) ? 4 : irnd(0, 3);
	if (ty >= 0) part_record(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->maxNames);
	g_a[0] = p; g_a[1] = ty;
}
ST(actor_setActorTypeHeadInfoBy, settype_setup(0);, TC(int, 0x473b10, char *, int, int)(BUF, g_a[0], g_a[1]), actor_setActorTypeHeadInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]))
ST(actor_setActorTypeChestInfoBy, settype_setup(1);, TC(int, 0x473c20, char *, int, int)(BUF, g_a[0], g_a[1]), actor_setActorTypeChestInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]))
ST(actor_setActorTypeArmInfoBy, settype_setup(2);, TC(int, 0x473d30, char *, int, int)(BUF, g_a[0], g_a[1]), actor_setActorTypeArmInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]))
ST(actor_setActorTypeLegInfoBy, settype_setup(3);, TC(int, 0x473e40, char *, int, int)(BUF, g_a[0], g_a[1]), actor_setActorTypeLegInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]))
ST(actor_setActorTypeBoosterInfoBy, settype_setup(4);, TC(int, 0x473f50, char *, int, int)(BUF, g_a[0], g_a[1]), actor_setActorTypeBoosterInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1]))
/* the item setter: game mode 0..13, slot 0..5, item -1..3; the item records it can pick (0..3 and the modes' fixed
   ones) cleared with names and counts; the item count mostly 40 */
static void setitem_setup(void)
{
	static const int fixed[] = { 3, 5, 0x16, 0x17, 0x19, 0x24 };
	int p = irnd(0, 7), slot = irnd(0, 5), it = irnd(0, 5) ? irnd(0, 3) : -1;
	char *pl = BUF + 0x1561b68 + p * 0x47fd2;
	part_actors(p);
	S32(BUF, 0x20f3ab8) = irnd(0, 13);
	S32(BUF, 0x1561b64) = irnd(0, 19) ? 40 : irnd(0, 30);
	fill(pl + 0x18c, 6 * 0x40); fill(pl + 0x320, 6 * 4);
	for (int i = 0; i < 4; i++) part_record(BUF + 0x14d1ab4 + i * 0x2e18, 0x2e18, 0x40, 0x12dc, 15);
	for (int i = 0; i < 6; i++) part_record(BUF + 0x14d1ab4 + fixed[i] * 0x2e18, 0x2e18, 0x40, 0x12dc, 15);
	for (int i = 0; i < 10; i++) for (int v = 0; v < 4; v++)              /* slot 5's list */
		part_counts(BUF + 0x14d1ab4 + (i < 4 ? i : fixed[i - 4]) * 0x2e18, v, 0x16fc, 0x2998, 15);
	g_a[0] = p; g_a[1] = slot; g_a[2] = it;
}
ST(actor_setActorTypeItemInfoBy, setitem_setup();, (TC(void, 0x474060, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
   (actor_setActorTypeItemInfoBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
