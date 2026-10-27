/* batch 66 */
/* light_computeLayerLightBy's layers and light factors, the layer's own light map as the colours */
ST(load_4728e0, layerlight_setup();, (TC(void, 0x4728e0, char *, char *)(BUF, BUF + 0x100), 0), (load_4728e0(BUF, (DWORD)(BUF + 0x100)), 0))
/* a space object (pools big enough for depth 2: 120 blocks, 600 nodes) with a root block around the origin and 8
   collision triangles near it; the original inserts up to 6 of them first (random depths), then the test inserts
   one (sometimes again) at depth -1..2; margin +0x8c and the split threshold +0x90 random */
static void octree_setup(void)
{
	char *sp = BUF + 0x100;
	fill(sp, 0x100);
	TC(void, 0x4813e0, char *, int, int, int, int, int, int, int)(sp, 4, 600, 4, 120, 4, (int)(BUF + 0x400000), 0x100000);
	SF(sp, 0x8c) = irnd(0, 3) ? 0.0f : (float)irnd(0, 200) / 100.0f; S32(sp, 0x90) = irnd(0, 3);
	for (int i = 0; i < 3; i++) { SF(BUF + 0x80, 4 * i) = (float)irnd(-1200, -800) / 100.0f; SF(BUF + 0x8c, 4 * i) = (float)irnd(800, 1200) / 100.0f; }
	g_a[0] = (int)TC(DWORD, 0x4818e0, char *, char *, char *)(sp, BUF + 0x80, BUF + 0x8c);
	for (int k = 0; k < 8; k++) {
		float v[9]; char *t = BUF + 0x2000 + k * 0x100;
		for (int i = 0; i < 9; i++) v[i] = (float)irnd(-1300, 1300) / 100.0f;
		if (irnd(0, 2)) for (int i = 3; i < 9; i++) v[i] = v[i % 3] + (float)irnd(-300, 300) / 100.0f;   /* small ones */
		fill(t, 0xd0);
		load_47db60(t, k, v, v + 3, v + 6, 1, 2, 3, 4, 5);
	}
	for (int n = irnd(0, 6); n > 0; n--)
		TC(int, 0x481ae0, char *, int, int, int)(sp, g_a[0], (int)(BUF + 0x2000 + irnd(0, 7) * 0x100), irnd(0, 2));
	g_a[1] = (int)(BUF + 0x2000 + irnd(0, 7) * 0x100); g_a[2] = irnd(-1, 2);
	if (!irnd(0, 9)) g_a[0] = (int)TC(DWORD, 0x4818e0, char *, char *, char *)(sp, BUF + 0x80, BUF + 0x8c);   /* a fresh block */
}
static int g_octSplits;
static DWORD octree_orig(void)
{
	DWORD r = (DWORD)TC(int, 0x481ae0, char *, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2]);
	g_octSplits += r == 1;
	return r;
}
ST(load_481ae0, octree_setup();, octree_orig(),
   load_481ae0(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]))
/* a skeleton (BUF + 0x100) of up to 4 bones (0x70 apart) with position and rotation keys (sorted frames, lengths
   sometimes 0, some zero axes, rarely NaN), frame counts sometimes 0 or negative; bone -1..4; t mostly 0..1; the
   modelview matrix glGetFloatv hands out random */
static float skel_f(void) { int k = irnd(0, 39); return k == 0 ? 0.0f / 0.0f : k < 4 ? 0.0f : csu_fr(-1000, 1000); }
static void pose_setup(void)
{
	char *sk = BUF + 0x100; int nb = irnd(0, 4);
	fill(sk, 0x40);
	S32(sk, 0x10) = nb; S32(sk, 0x14) = (int)(BUF + 0x1000); S32(sk, 0x20) = irnd(0, 9) ? irnd(0, 100) : irnd(-5, 0);
	for (int i = 0; i < nb; i++) {
		char *b = BUF + 0x1000 + i * 0x70; int np = irnd(0, 4) ? irnd(1, 5) : irnd(-1, 0), nr = irnd(0, 4) ? irnd(1, 5) : irnd(-1, 0);
		fill(b, 0x70);
		for (int k = 0x44; k < 0x60; k += 4) SF(b, k) = skel_f();
		S32(b, 0x60) = np; S32(b, 0x64) = (int)(BUF + 0x4000 + i * 0x400);
		S32(b, 0x68) = nr; S32(b, 0x6c) = (int)(BUF + 0x6000 + i * 0x400);
		int f = irnd(-5, 10);
		for (int k = 0; k < 5; k++) {
			char *p = BUF + 0x4000 + i * 0x400 + k * 0x20; S32(p, 0) = f; S32(p, 4) = irnd(0, 4) ? irnd(1, 30) : irnd(-2, 0);
			for (int j = 8; j < 0x20; j += 4) SF(p, j) = skel_f();
			f += irnd(0, 30);
		}
		f = irnd(-5, 10);
		for (int k = 0; k < 5; k++) {
			char *p = BUF + 0x6000 + i * 0x400 + k * 0x28; S32(p, 0) = f; S32(p, 4) = irnd(0, 4) ? irnd(1, 30) : irnd(-2, 0);
			for (int j = 8; j < 0x28; j += 4) SF(p, j) = skel_f();
			f += irnd(0, 30);
		}
	}
	for (int i = 0; i < 16; i++) { float x = csu_fr(-1000, 1000); memcpy(&g_glFloats[i], &x, 4); }
	g_a[0] = irnd(-1, 4); SF(&g_a[1], 0) = irnd(0, 9) ? (float)irnd(0, 1000) / 1000.0f : csu_fr(-200, 300);
	fill(BUF + 0x200, 0x40);
}
ST(skel_applyPose, pose_setup();, (TC(void, 0x46ab30, char *, char *, int, float)(BUF + 0x100, BUF + 0x200, g_a[0], SF(&g_a[1], 0)), 0),
   (skel_applyPose(BUF + 0x100, (DWORD)(BUF + 0x200), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
