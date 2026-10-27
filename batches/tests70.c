/* batch 69 */
/* collision_rayTrace's scene (level grid and objects around the trace points); the objects also flagged 1 (sometimes)
   with positions near those points and a fade; up to 4 actors near them (state 1 mostly, player index -1..3, radius,
   their outputs random); the camera at a trace point or near it; both GL matrices a 1/32 scaling with noise, so about
   half the points land in view; mode flags random */
static int g_cam[9];
static void camview_setup(void)
{
	raytrace_setup();
	char *sc = BUF; const float *c = (const float *)(BUF + 0x206000);
	fill(sc + 0x20f3970, 0x150);
	S32(sc, 0x2149308) = irnd(0, 1); S32(sc, 0x214930c) = irnd(0, 1);
	for (int k = 0; k < 6; k++) {
		char *o = sc + 0x131ae44 + k * 0x2cc;
		S32(o, 0xc) = irnd(0, 3) ? 1 : irnd(0, 1) * 2;
		for (int i = 0; i < 3; i++) SF(o, 0x58 + 4 * i) = c[i] + (float)irnd(-3000, 3000) / 100.0f;
		SF(o, 0x2a8) = (float)irnd(0, 100) / 100.0f; fill(o + 0x2ac, 0x10);
	}
	int na = irnd(0, 4); S32(sc, 0x202e8c8) = na; S32(sc, 0x202e8d8) = irnd(-1, 3); S32(sc, 0x202e8d4) = irnd(-1, 3);
	for (int i = 0; i < na; i++) {
		char *a = sc + 0x1cd94c0 + i * 0x8888;
		S32(a, 0) = irnd(0, 2); S32(a, 0x30) = irnd(-1, 3); S32(a, 0x34) = irnd(0, 4) ? 1 : irnd(0, 2);
		for (int k = 0; k < 3; k++) SF(a, 0x3c + 4 * k) = c[k] + (float)irnd(-3000, 3000) / 100.0f;
		SF(a, 0x2d0) = (float)irnd(0, 500) / 100.0f; fill(a + 0x86a4, 0x40);
	}
	for (int p = 0; p < 4; p++) SF(sc, 0x14d48c4 + p * 0x2e18) = (float)irnd(-10, 100);
	for (int i = 0; i < 16; i++) { float x = (i % 5 == 0) ? (i == 15 ? 1.0f : 1.0f / 32) : (float)irnd(-20, 20) / 1000.0f; if (i == 11) x = (float)irnd(-1000, 0) / 1000.0f; memcpy(&g_glFloats[i], &x, 4); }
	float *v = (float *)(BUF + 0x1000);
	for (int i = 0; i < 3; i++) v[i] = irnd(0, 1) ? GF(BUF + 0x206200 + 4 * i) : c[i] + (float)irnd(-2000, 2000) / 100.0f;
	for (int i = 3; i < 9; i++) v[i] = (float)irnd(-100, 100) / 100.0f;
	g_cam[0] = (int)v; g_cam[1] = (int)(v + 3); g_cam[2] = (int)(v + 6);
	SF(&g_cam[3], 0) = (float)irnd(30, 90); g_cam[4] = irnd(0, 1) ? 640 : 800; g_cam[5] = irnd(0, 1) ? 480 : 600;
	SF(&g_cam[6], 0) = (float)irnd(1, 10); SF(&g_cam[7], 0) = (float)irnd(1000, 100000); SF(&g_cam[8], 0) = (float)irnd(0, 100) / 1000.0f;
}
static int g_camVis;
static DWORD camview_orig(void)
{
	TC(void, 0x4729b0, char *, int, int, int, int, int, int, int, int, int)(BUF, g_cam[0], g_cam[1], g_cam[2], g_cam[3], g_cam[4], g_cam[5], g_cam[6], g_cam[7], g_cam[8]);
	for (int i = 0; i < S32(BUF, 0x202e8c8); i++) g_camVis += S32(BUF + 0x1cd94c0 + i * 0x8888, 0x40 + 0x21a2 * 4) == 1;
	return 0;
}
ST(camera_setupView, camview_setup();, camview_orig(),
   (camera_setupView(BUF, (DWORD)g_cam[0], (DWORD)g_cam[1], (DWORD)g_cam[2], (DWORD)g_cam[3], (DWORD)g_cam[4], (DWORD)g_cam[5], (DWORD)g_cam[6], (DWORD)g_cam[7], (DWORD)g_cam[8]), 0))
