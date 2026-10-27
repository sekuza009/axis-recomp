/* batch 106 */
/* the sky: every mode at random, every texture id a GL slot owner of menutex_setup's set, the camera, scroll,
   heights, floor vertices and fog values small floats, a scale of 0.1..10 */
static void sky_setup(void)
{
	int t0 = menutex_setup(), k = t0 - t0 % 512;
	char *sc = BUF;
	for (int o = 0x9ee048; o < 0x9ef900; o += 4) SF(sc, o) = (float)irnd(-1000, 1000) / 10.0f;
	for (int o = 0x20f3970; o < 0x20f3994; o += 4) SF(sc, o) = (float)irnd(-1000, 1000) / 10.0f;
	DWORD ids[] = { 0x9ee068, 0x9ee06c, 0x9ee070, 0x9ee074, 0x9ee078, 0x9ee07c, 0x9eee4c, 0x9eee50,
	                0x9ef0b4, 0x9ef0b8, 0x9ef0bc, 0x9ef0c0, 0x9ef0c4, 0x9ef0c8 };
	for (unsigned j = 0; j < sizeof ids / sizeof ids[0]; j++) {
		char *sl = (char *)S32(BUF, 0xcd134);
		for (int m = irnd(0, 5); m; m--) sl = (char *)S32(sl, 0xc);
		S32(sc, ids[j]) = k + S32(sl, 4);
	}
	for (int j = 0; j < 16; j++) {
		char *sl = (char *)S32(BUF, 0xcd134);
		for (int m = irnd(0, 5); m; m--) sl = (char *)S32(sl, 0xc);
		S32(sc, 0x9ef310 + j * 4) = k + S32(sl, 4);
	}
	S32(sc, 0x9ee064) = irnd(0, 2); S32(sc, 0x9eee48) = irnd(0, 2); S32(sc, 0x9ef0b0) = irnd(0, 3); S32(sc, 0x9ef30c) = irnd(0, 1);
	S32(sc, 0x9ee058) = irnd(0, 0xffffff); S32(sc, 0x9eee5c) = irnd(0, 15); S32(sc, 0x9ef8fc) = irnd(0, 15);
	float s = (float)irnd(1, 100) / 10.0f; memcpy(&g_a[0], &s, 4);
}
ST(hud_496f20, sky_setup();, (TC(void, 0x496f20, char *, int)(BUF, g_a[0]), 0), (hud_496f20(BUF, (DWORD)g_a[0]), 0))
