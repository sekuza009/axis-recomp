/* batch 109 */
/* every actor (0..6) with fresh empty object lists, active or not, positions near the camera; then as
   updateparts_setup (part tables, items, one actor's state) */
static void allparts_setup(void)
{
	updateparts_setup();
	for (int a = 0; a < 7; a++) {
		char *ac = BUF + 0x1cd93a8 + a * 0x8888;
		if (a != g_a[0]) { ResourceSet_init_463a40(ac); S32(ac, 0x10c) = irnd(0, 7); S32(ac, 0x14c) = irnd(0, 1); S32(ac, 0x884c) = 0;
		                   for (int k = 0; k < 3; k++) SF(ac, 0x154 + k * 4) = SF(BUF + 0x20f3970, k * 4) + (float)irnd(-300, 300); }
		S32(ac, 0x108) = irnd(0, 3) ? 1 : 0;
	}
	S32(BUF, 0x202e8c8) = irnd(0, 7);
	g_a[0] = g_a[1]; g_a[1] = g_a[2];
}
ST(hud_45e170, allparts_setup();, (TC(void, 0x45e170, char *, int, int)(BUF, g_a[0], g_a[1]), 0), (hud_45e170(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
/* mechsetup_setup's player and actor (slot 0..5, now and then 100+), the actor count 0..8 */
static void slot_setup(void)
{
	mechsetup_setup();
	S32(BUF, 0x202e8c8) = irnd(0, 8);
	if (!irnd(0, 15)) g_a[0] = irnd(100, 120);
	for (int a = 0; a < 9; a++) fill(BUF + 0x1cd94b0 + a * 0x8888, 4);
	fill(BUF + 0x202e8cc, 12);
}
ST(FUN_0045dc00, slot_setup();, TC(int, 0x45dc00, char *, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3]),
   FUN_0045dc00(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3]))
ST(match_45dd80, slot_setup();, (TC(void, 0x45dd80, char *, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3]), 0),
   (match_45dd80(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3]), 0))
/* the player's actor is the player's own index (armc_45ddc0 passes it as both): that actor's lists constructed */
static void ownslot_setup(void)
{
	slot_setup();
	S32(BUF, 0x202e8d4) = g_spf;
	char *ac = BUF + 0x1cd93a8 + g_spf * 0x8888;
	ResourceSet_init_463a40(ac); S32(ac, 0x10c) = g_spf; S32(ac, 0x484) = irnd(0, 3); S32(ac, 0x49c) = irnd(0, 3); S32(ac, 0x140) = irnd(0, 5);
	fill((void *)0xa0e7a8, 12);
}
ST(armc_45ddc0, ownslot_setup();, (TC(void, 0x45ddc0, char *)(BUF), 0), (armc_45ddc0(BUF), 0))
/* a spawn record: the player (mechsetup_setup's), then ints for the stats; the player's actor slot, now and then -1 */
static void spawnrec_setup(void)
{
	slot_setup();
	S32(BUF, 0x202e8d4) = irnd(0, 19) ? irnd(0, 6) : -1;
	int *r = (int *)(BUF + 0x9e0000);
	r[0] = g_spf;
	for (int i = 1; i < 0x17; i++) r[i] = irnd(-1000, 1000);
	g_a[1] = (int)r;
	g_paintStacks = 1;
}
ST(actor_applySpawnRecord, spawnrec_setup();, (TC(void, 0x45de20, char *, int, int *)(BUF, g_a[0], (int *)g_a[1]), 0),
   (actor_applySpawnRecord(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
