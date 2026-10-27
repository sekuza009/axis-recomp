/* batch 101 */
/* an actor (0..6) with empty, freshly constructed object lists (ResourceSet_init_463a40), every part table and item
   record ready (cleared names, see part_record), and its state at random: alive or not, near the camera or not, hit /
   damaged / cloaked, the viewing actor or not, the current weapon slot */
static void updateparts_setup(void)
{
	char *sc = BUF; int a = irnd(0, 6), p = irnd(0, 7);
	part_actors(p);
	for (int k = 0; k < 5; k++) {
		const PartType *t = &g_partTypes[k];
		for (int ty = 0; ty < 4; ty++) part_record(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->maxNames);
		S32(BUF + 0x1561b68 + p * 0x47fd2, t->typeOff) = irnd(0, 3);
	}
	for (int it = 0; it < 4; it++) {
		char *r = BUF + 0x14d1ab4 + it * 0x2e18;
		part_record(r, 0x2e18, 0x40, 0x12dc, 15);
		for (int v = 0; v < 4; v++) part_counts(r, v, 0x16fc, 0x2998, 15);
	}
	for (int s = 0; s < 6; s++) S32(BUF + 0x1561b68 + p * 0x47fd2, 0x320 + s * 4) = irnd(-1, 3);
	char *ac = sc + 0x1cd93a8 + a * 0x8888;
	ResourceSet_init_463a40(ac);
	S32(ac, 0x108) = 1; S32(ac, 0x10c) = p; S32(ac, 8) = irnd(0, 9);
	S32(ac, 0x14c) = irnd(0, 9) ? 1 : 0; S32(ac, 0x884c) = irnd(0, 9) ? 0 : 1;
	for (int k = 0; k < 3; k++) { SF(sc + 0x20f3970, k * 4) = (float)irnd(-1000, 1000); SF(ac, 0x154 + k * 4) = SF(sc + 0x20f3970, k * 4) + (float)irnd(-300, 300); }
	SF(sc, 0xa08) = (float)irnd(50, 400); SF(ac, 0x3e8) = (float)irnd(0, 50);
	SF(ac, 0x120) = irnd(0, 2) ? 0.0f : (float)irnd(0, 50) / 10.0f;
	SF(ac, 0x4ec) = irnd(0, 2) ? 0.0f : (float)irnd(0, 400); SF(ac, 0x8854) = irnd(0, 2) ? 0.0f : (float)irnd(0, 400);
	S32(ac, 0x3f0) = irnd(0, 3) ? 0 : irnd(0, 0xfff);
	S32(ac, 0x140) = irnd(0, 5); S32(ac, 0x484) = irnd(0, 3); S32(ac, 0x49c) = irnd(0, 3);
	fill(ac + 0x4f0, 4); fill(ac + 0x54c, 8); fill(ac + 0x87c8, 0x10);
	S32(sc, 0x202e8d4) = irnd(0, 6); S32(sc, 0x202e8d8) = irnd(0, 1) ? a : irnd(0, 6);
	fill(sc + 0x20f2f3c, 0x10); fill(sc + 0x20f2f88, 0x10);
	g_a[0] = a; g_a[1] = (int)(BUF + 0x980000); g_a[2] = irnd(0, 1);
}
ST(actor_updateAllParts, updateparts_setup();, TC(int, 0x45d3e0, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]),
   actor_updateAllParts(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]))
