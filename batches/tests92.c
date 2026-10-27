/* batch 91 */
/* the arm-customise part choices: settype_setup's engine (BUF) with all four type records of the table ready and a
   count of 1..4 (0 would divide by zero), any index -20..20, the edited player or none */
static void armcindex_setup(int k)
{
	const PartType *t = &g_partTypes[k];
	settype_setup(k);
	S32(BUF, t->countOff) = irnd(1, 4);
	for (int ty = 0; ty < 4; ty++) part_record(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->maxNames);
	S32(SCENE, 0x234240d) = irnd(0, 4) ? g_a[0] : -1;
	g_a[1] = irnd(-20, 20);
}
ST(armc_setHeadIndex, armcindex_setup(0);, (TC(void, 0x4613d0, char *, int)(SCENE, g_a[1]), 0), (armc_setHeadIndex(SCENE, (DWORD)g_a[1]), 0))
ST(armc_setChestIndex, armcindex_setup(1);, (TC(void, 0x461410, char *, int)(SCENE, g_a[1]), 0), (armc_setChestIndex(SCENE, (DWORD)g_a[1]), 0))
ST(armc_setArmIndex, armcindex_setup(2);, (TC(void, 0x461450, char *, int)(SCENE, g_a[1]), 0), (armc_setArmIndex(SCENE, (DWORD)g_a[1]), 0))
ST(armc_setLegIndex, armcindex_setup(3);, (TC(void, 0x461490, char *, int)(SCENE, g_a[1]), 0), (armc_setLegIndex(SCENE, (DWORD)g_a[1]), 0))
ST(armc_setBoosterIndex, armcindex_setup(4);, (TC(void, 0x4614d0, char *, int)(SCENE, g_a[1]), 0), (armc_setBoosterIndex(SCENE, (DWORD)g_a[1]), 0))
static void armcitem_setup(void)
{
	setitem_setup();
	S32(SCENE, 0x234240d) = irnd(0, 4) ? g_a[0] : -1;
}
ST(armc_461510, armcitem_setup();, (TC(void, 0x461510, char *, int, int)(SCENE, g_a[1], g_a[2]), 0), (armc_461510(SCENE, (DWORD)g_a[1], (DWORD)g_a[2]), 0))
/* an object list of 0..4 entries whose shapes are shapetex_setup's shape (textures with GL slots or texture i) or none */
static void listbind_setup(void)
{
	shapetex_setup();
	char *list = BUF + 0x8f0000; int n = irnd(0, 4);
	fill(list, 0x20); S32(list, 0x10) = n; S32(list, 0x14) = (int)(BUF + 0x8f0100);
	for (int i = 0; i < n; i++) { fill(BUF + 0x8f0100 + i * 100, 100); S32(BUF + 0x8f0100 + i * 100, 0) = irnd(0, 3) ? (int)(BUF + 0x500000) : 0; }
}
ST(actor_46fed0, listbind_setup();, (TC(void, 0x46fed0, char *)(BUF + 0x8f0000), 0), (actor_46fed0(BUF + 0x8f0000), 0))
/* a whole player: every part table with count 4 and records 0..3, the item records (setitem_setup), a name, value
   and team; part types -1..4 (4 is fatal now and then), items -1..3 */
static DWORD g_pl[15];
static void wholeplayer_setup(void)
{
	setitem_setup();
	int p = g_a[0];
	S32(BUF, 0x20f3ab8) = irnd(0, 3) ? 0 : irnd(0, 13);
	for (int k = 0; k < 5; k++) {
		const PartType *t = &g_partTypes[k];
		S32(BUF, t->countOff) = irnd(0, 19) ? 4 : 3;
		for (int ty = 0; ty < 4; ty++) part_record(BUF + t->base + ty * t->stride, t->stride, 0x40, t->kcOff, t->maxNames);
		S32(BUF + 0x1561b68 + p * 0x47fd2, t->typeOff) = irnd(-1, 3);
	}
	char *nm = BUF + 0x940000; fill_str(nm, 20, 'A', 'Z');
	g_pl[0] = p; g_pl[1] = (DWORD)nm; g_pl[2] = irnd(0, 9); g_pl[3] = irnd(-1, 3);
	for (int k = 4; k < 9; k++) g_pl[k] = irnd(0, 9) ? irnd(-1, 3) : 4;
	for (int k = 9; k < 15; k++) g_pl[k] = irnd(-1, 3);
	char *r = BUF + 0x941000;                    /* load_4742f0's record */
	fill(r, 0x60); strcpy(r + 8, nm);
	S32(r, 4) = g_pl[2]; S32(r, 0x28) = g_pl[3];
	for (int k = 0; k < 5; k++) S32(r, 0x2c + k * 4) = g_pl[4 + k];
	for (int k = 0; k < 6; k++) S32(r, 0x40 + k * 4) = g_pl[9 + k];
}
ST(match_474210, wholeplayer_setup();,
   (TC(void, 0x474210, char *, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)(BUF,
     g_pl[0], g_pl[1], g_pl[2], g_pl[3], g_pl[4], g_pl[5], g_pl[6], g_pl[7], g_pl[8], g_pl[9], g_pl[10], g_pl[11], g_pl[12], g_pl[13], g_pl[14]), 0),
   (match_474210(BUF, g_pl[0], g_pl[1], g_pl[2], g_pl[3], g_pl[4], g_pl[5], g_pl[6], g_pl[7], g_pl[8], g_pl[9], g_pl[10], g_pl[11],
     g_pl[12], g_pl[13], g_pl[14]), 0))
ST(load_4742f0, wholeplayer_setup();, (TC(void, 0x4742f0, char *, int, char *)(BUF, g_pl[0], BUF + 0x941000), 0),
   (load_4742f0(BUF, g_pl[0], (DWORD)(BUF + 0x941000)), 0))
