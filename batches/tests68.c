/* batch 67 */
/* a space object whose pools cannot run out (64 planes, 4000 nodes, 8 units, 600 blocks) over a grid of 1..3 cells
   per axis around the origin (bounds sometimes off-centre, margin sometimes > 0, split threshold 0..3, depth 0..1, 2
   for a single cell), with up to 4 triangles already in it (the original); 8 triangles' corners at BUF + 0x3000 */
static void spacegrid_setup(void)
{
	char *sp = BUF + 0x100; int nx = irnd(1, 3), ny = irnd(1, 3), nz = irnd(1, 3), one = nx * ny * nz == 1;
	fill(sp, 0x100);
	TC(void, 0x4813e0, char *, int, int, int, int, int, int, int)(sp, 64, 4000, 8, 600, 27, (int)(BUF + 0x400000), 0x100000);
	for (int i = 0; i < 3; i++) { SF(BUF + 0x80, 4 * i) = (float)irnd(-1500, -500) / 100.0f; SF(BUF + 0x8c, 4 * i) = (float)irnd(500, 1500) / 100.0f; }
	float mg = irnd(0, 3) ? 0.0f : (float)irnd(0, 200) / 100.0f;
	TC(void, 0x4819b0, char *, char *, char *, int, int, int, float, int, int)(sp, BUF + 0x80, BUF + 0x8c, nx, ny, nz, mg, irnd(0, 3), irnd(0, one ? 2 : 1));
	for (int k = 0; k < 8; k++) {
		float *v = (float *)(BUF + 0x3000 + k * 0x40);
		for (int i = 0; i < 3; i++) v[i] = (float)irnd(-1800, 1800) / 100.0f;
		for (int i = 3; i < 9; i++) v[i] = irnd(0, 2) ? v[i % 3] + (float)irnd(-400, 400) / 100.0f : (float)irnd(-1800, 1800) / 100.0f;
		if (!irnd(0, 19)) memcpy(v + 3, v, 12);                                           /* degenerate */
	}
	for (int n = irnd(0, 4); n > 0; n--) {
		float *v = (float *)(BUF + 0x3000 + irnd(0, 7) * 0x40);
		TC(int, 0x481eb0, char *, int, float *, float *, float *, int, int, int, int, int)(sp, irnd(0, 0x10), v, v + 3, v + 6, 1, 2, 3, 4, 5);
	}
}
static int g_pa[9];                    /* 9 arguments: g_a holds 8 */
static void planes_setup(void)
{
	spacegrid_setup();
	float *v = (float *)(BUF + 0x3000 + irnd(0, 7) * 0x40);
	g_pa[0] = irnd(0, 0x10); g_pa[1] = (int)v; g_pa[2] = (int)(v + 3); g_pa[3] = (int)(v + 6);
	for (int i = 4; i < 9; i++) g_pa[i] = irnd(-5, 5);
}
ST(space_buildPlanes, planes_setup();,
   TC(DWORD, 0x481eb0, char *, int, int, int, int, int, int, int, int, int)(BUF + 0x100, g_pa[0], g_pa[1], g_pa[2], g_pa[3], g_pa[4], g_pa[5], g_pa[6], g_pa[7], g_pa[8]),
   space_buildPlanes(BUF + 0x100, (DWORD)g_pa[0], (DWORD)g_pa[1], (DWORD)g_pa[2], (DWORD)g_pa[3], (DWORD)g_pa[4], (DWORD)g_pa[5], (DWORD)g_pa[6], (DWORD)g_pa[7], (DWORD)g_pa[8]))
/* a unit from the pool (its plane and node lists sometimes already holding one entry made the same way) */
static void unittri_setup(void)
{
	spacegrid_setup();
	char *sp = BUF + 0x100;
	int u = (int)TC(DWORD, 0x4817f0, char *)(sp);
	if (irnd(0, 1)) {
		float *v = (float *)(BUF + 0x3000 + irnd(0, 7) * 0x40);
		TC(void, 0x482320, char *, int, int, int, int, int, int, float *, float *, float *)(sp, 0, u, 0, 1, 2, 3, v, v + 3, v + 6);
	}
	float *v = (float *)(BUF + 0x3000 + irnd(0, 7) * 0x40);
	g_pa[0] = irnd(0, 0x10); g_pa[1] = u; g_pa[2] = irnd(0, 3); g_pa[3] = irnd(0, 9); g_pa[4] = irnd(0, 9); g_pa[5] = irnd(0, 9);
	g_pa[6] = (int)v; g_pa[7] = (int)(v + 3); g_pa[8] = (int)(v + 6);
}
ST(load_482320, unittri_setup();,
   (TC(void, 0x482320, char *, int, int, int, int, int, int, int, int, int)(BUF + 0x100, g_pa[0], g_pa[1], g_pa[2], g_pa[3], g_pa[4], g_pa[5], g_pa[6], g_pa[7], g_pa[8]), 0),
   (load_482320(BUF + 0x100, (DWORD)g_pa[0], (DWORD)g_pa[1], (DWORD)g_pa[2], (DWORD)g_pa[3], (DWORD)g_pa[4], (DWORD)g_pa[5], (DWORD)g_pa[6], (DWORD)g_pa[7], (DWORD)g_pa[8]), 0))
/* a shape (BUF + 0x8000) of up to 3 parts (flags 0x20 / 1 sometimes), each with 8 vertices and up to 3 primitives of
   type 4 / 5 / 6 (rarely another) and 0..8 indices (at most 40 triangles in all: the plane pool holds 64); the matrix
   given (rotation-ish, plus translation) or the mocked GL one */
static void shapeunits_setup(void)
{
	spacegrid_setup();
	char *sh = BUF + 0x8000; int np = irnd(0, 3);
	fill(sh, 0x20); S32(sh, 0x10) = np; S32(sh, 0x14) = (int)(BUF + 0x8100);
	for (int p = 0; p < np; p++) {
		char *pt = BUF + 0x8100 + p * 0x80; int nprim = irnd(0, 3);
		fill(pt, 0x80);
		S32(pt, 0) = irnd(0, 5) ? irnd(0, 1) : 0x20 | irnd(0, 1);
		S32(pt, 0x50) = (int)(BUF + 0x9000 + p * 0x100);
		for (int i = 0; i < 24; i++) SF(BUF + 0x9000 + p * 0x100, 4 * i) = (float)irnd(-1000, 1000) / 100.0f;
		S32(pt, 0x60) = nprim; S32(pt, 0x64) = (int)(BUF + 0xa000 + p * 0x100);
		for (int q = 0; q < nprim; q++) {
			char *pr = BUF + 0xa000 + p * 0x100 + q * 12; int n = irnd(0, 8);
			S32(pr, 0) = irnd(0, 19) ? irnd(4, 6) : irnd(0, 7); S32(pr, 4) = n; S32(pr, 8) = (int)(BUF + 0xb000 + p * 0x400 + q * 0x40);
			for (int i = 0; i < 8; i++) S32(BUF + 0xb000 + p * 0x400 + q * 0x40, 4 * i) = irnd(0, 7);
		}
	}
	float *m = (float *)(BUF + 0xc000);
	for (int i = 0; i < 16; i++) m[i] = (float)irnd(-100, 100) / 100.0f;
	for (int i = 12; i < 15; i++) m[i] = (float)irnd(-500, 500) / 100.0f;
	for (int i = 0; i < 16; i++) { float x = (float)irnd(-100, 100) / 100.0f; memcpy(&g_glFloats[i], &x, 4); }
	g_pa[0] = irnd(0, 0x10); g_pa[1] = irnd(0, 3) ? (int)m : 0;
}
ST(space_buildUnits, shapeunits_setup();, TC(DWORD, 0x4823c0, char *, int, char *, int)(BUF + 0x100, g_pa[0], BUF + 0x8000, g_pa[1]),
   space_buildUnits(BUF + 0x100, (DWORD)g_pa[0], (DWORD)(BUF + 0x8000), (DWORD)g_pa[1]))
