/* batch 104 */
/* the scene (BUF) with billboard_setup's billboard object (also BUF) at +0x9ccff8 and vv_setup's view volume and
   test object (the item types' shape, or none); 0..8 items of types 0..40 (34 forced 3D), near the camera or not,
   taken or not, faded or not; 3D mode on or off */
static void mapitems_setup(void)
{
	billboard_setup();
	vv_setup();
	char *sc = BUF;
	G32(sc + 0x9ccff8) = (int)BUF;
	for (int k = 0; k < 3; k++) SF(sc + 0x20f3970, k * 4) = (float)irnd(-1000, 1000);
	SF(sc, 0xa08) = (float)irnd(50, 500);
	for (int t = 0; t <= 40; t++) S32(sc + 0x20f3ae0 + t * 0x90, 0x8c) = irnd(0, 3) ? (int)(BUF + 0x120000) : 0;
	int n = irnd(0, 8);
	S32(sc, 0x20fcd38) = n;
	for (int i = 0; i < n; i++) {
		char *e = sc + 0x20fadf8 + i * 0x28;
		fill(e, 0x28);
		S32(e, 0) = irnd(0, 9) ? (irnd(0, 5) ? irnd(0, 40) : 34) : -1;
		for (int k = 0; k < 3; k++) SF(e, 0xc + k * 4) = SF(sc + 0x20f3970, k * 4) + (float)irnd(-600, 600);
		SF(e, 0x1c) = (float)irnd(0, 3600);
		S32(e, 0x20) = irnd(0, 4) ? 0 : 1;
		SF(e, 0x24) = irnd(0, 1) ? 1.0f : (float)irnd(0, 100) / 100.0f;
	}
	G32(0x83a9c8) = irnd(0, 1); fill((void *)0xa1f23c, 4);
	g_a[0] = (int)(BUF + 0x100000);
}
ST(hud_48f970, mapitems_setup();, (TC(void, 0x48f970, char *, char *)(BUF, (char *)g_a[0]), 0), (hud_48f970(BUF, (DWORD)g_a[0]), 0))
