/* batch 110 */
/* vv_setup's view volume (BUF + 0x100000, its test object as every effect shape and part-debris shape) made ready for billboards and
   triangles too (lists, capacities, matrices), the item atlas ids, the camera; 1..6 projectiles of any type 0..75
   (all fields floats of -1000..1000 except frame, active, type, owner; timers 0..10; positions near the camera or
   not), the viewing actor one of their owners now and then */
static void projvv_setup(void)
{
	vv_setup();
	char *vv = BUF + 0x100000, *sc = BUF;
	S32(vv, 0x9068) = irnd(0, 12); S32(vv, 0x906c) = (int)(BUF + 0x1a8000); S32(vv, 0x9070) = 0; fill(vv + 0x909c, 4);
	fill(BUF + 0x1a8000, 12 * 92);
	S32(vv, 0x9054) = irnd(0, 20); S32(vv, 0x9058) = (int)(BUF + 0x198000); S32(vv, 0x905c) = 0;
	for (int k = 0; k < 32; k++) SF(vv, 0x90b0 + k * 4) = unit_rnd() * 2.0f;
	SF(vv, 0x90bc) = 0; SF(vv, 0x90cc) = 0; SF(vv, 0x90dc) = -1.0f; SF(vv, 0x90ec) = unit_rnd();
	for (int k = 0; k < 8; k++) S32(sc, 0x20f2e74 + k * 4) = (int)(BUF + 0x120000);    /* always set in the game */
	for (int k = 0; k < 24; k++) S32(sc, 0x20f2dac + k * 4) = (int)(BUF + 0x120000);
	for (int k = 0; k < 12; k++) S32(sc, 0x9ccfd4 + k * 4) = irnd(-1, 600);
	for (int k = 0; k < 3; k++) SF(sc + 0x20f3970, k * 4) = (float)irnd(-1000, 1000);
	SF(sc, 0xa08) = (float)irnd(100, 2000);
	fill((void *)0xa0e7c8, 12);
	int n = irnd(1, 6);
	S32(sc, 0x20f2da0) = n;
	for (int i = 0; i < n; i++) {
		char *r = sc + 0x20a99c0 + i * 300;
		for (int o = 0; o < 300; o += 4) SF(r, o) = (float)irnd(-1000, 1000) / 10.0f;
		S32(r, 0) = irnd(0, 100); S32(r, 4) = irnd(0, 3) ? 1 : 0; S32(r, 8) = irnd(0, 75); S32(r, 0xc) = irnd(0, 7);
		for (int k = 0; k < 3; k++) SF(r, 0x10 + k * 4) = SF(sc + 0x20f3970, k * 4) + (float)irnd(-2500, 2500);
		SF(r, 0x6c) = (float)irnd(0, 100) / 10.0f; SF(r, 0x70) = (float)irnd(0, 100) / 10.0f;
		S32(r, 0x28) = irnd(0, 1) ? (int)(BUF + 0x1c8000 + irnd(0, 3) * 64) : 0;   /* the trail's matrix (ViewVolume_transformObject) or none */
	}
	for (int m = 0; m < 4; m++) {
		float *mt = (float *)(BUF + 0x1c8000 + m * 64), a = (float)irnd(-314, 314) / 100.0f;
		memset(mt, 0, 64); mt[0] = mt[5] = cosf(a); mt[1] = sinf(a); mt[4] = -mt[1]; mt[10] = mt[15] = 1.0f;
		for (int j = 12; j < 15; j++) mt[j] = (float)irnd(-300, 300) / 10.0f;
	}
	S32(sc, 0x202e8d8) = irnd(0, 7);
	for (int p = 0; p < 8; p++) {                          /* each player's five part shape caches: one shape (debris) */
		static const int cache[5] = { 0x338, 0x8284, 0x101d0, 0x1fe1c, 0x2fa68 };
		for (int c = 0; c < 5; c++) { char *ch = sc + 0x1561b68 + p * 0x47fd2 + cache[c]; S32(ch, 0x11c) = (int)(BUF + 0x120000); S32(ch, 0x120) = 1; }
	}
	g_a[0] = irnd(0, n - 1); g_a[1] = (int)vv;
	g_paintStacks = 1;
}
ST(hud_476890, projvv_setup();, (TC(void, 0x476890, char *, int, char *)(BUF, g_a[0], (char *)g_a[1]), 0),
   (hud_476890(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
ST(hud_479af0, projvv_setup();, (TC(void, 0x479af0, char *, char *)(BUF, (char *)g_a[1]), 0), (hud_479af0(BUF, (DWORD)g_a[1]), 0))
