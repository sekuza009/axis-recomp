/* batch 65 */
/* a layer (BUF + 0x100) of up to 9 x 9 vertices with normals (sometimes NaN), its light map and colours; light
   factors of types 0..2 (rarely an unknown type: fatal) with colours and directions; a row/column window that may
   be empty */
static void layerlight_setup(void)
{
	char *l = BUF + 0x100; int rows = irnd(0, 8), cols = irnd(0, 8), nv = (rows + 1) * (cols + 1);
	fill(l, 0x140);
	S32(l, 0) = irnd(0, 4) ? irnd(0, 1) : 2; S32(l, 0x1c) = rows; S32(l, 0x20) = cols; S32(l, 0x30) = irnd(0, 1);
	S32(l, 0x44) = (int)(BUF + 0x10000); S32(l, 0x48) = (int)(BUF + 0x20000);
	for (int i = 0; i < nv * 3; i++) SF(BUF + 0x10000, i * 4) = irnd(0, 40) ? csu_fr(-150, 150) : 0.0f / 0.0f;
	fill(BUF + 0x20000, nv * 4 + 16); fill(BUF + 0x30000, nv * 4);
	int nf = irnd(0, 4); S32(BUF, 0x9d8000) = nf;
	for (int k = 0; k < nf; k++) {
		char *f = BUF + 0x9cd008 + k * 0x2c; fill(f, 0x2c);
		S32(f, 0) = irnd(0, 30) ? irnd(0, 2) : 3;
		for (int a = 0; a < 3; a++) SF(f, 0x14 + 4 * a) = csu_fr(-120, 120);
	}
	g_a[0] = irnd(0, 1); g_a[1] = irnd(0, rows); g_a[2] = irnd(0, cols);
	g_a[3] = irnd(0, 6) ? irnd(g_a[1], rows) : irnd(0, rows); g_a[4] = irnd(0, 6) ? irnd(g_a[2], cols) : irnd(0, cols);
}
ST(light_computeLayerLightBy, layerlight_setup();,
   (TC(void, 0x472400, char *, char *, char *, int, int, int, int, int)(BUF, BUF + 0x100, BUF + 0x30000, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4]), 0),
   (light_computeLayerLightBy(BUF, (DWORD)(BUF + 0x100), (DWORD)(BUF + 0x30000), (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4]), 0))
/* the view volume and meshes of ViewVolume_projectObject's test; two terrain objects in the scene using those meshes
   (0x121000, a copy at 0x123000); up to 4 layers of up to 8 x 8 cells near the camera, with bitmaps, index heaps
   and primitive buffers sized for the worst case but capacities sometimes small (fatal, writing on) */
static void renderproc_setup(void)
{
	vv_setup();
	memcpy(BUF + 0x123000, BUF + 0x121000, 16 * 0x80);
	int n = irnd(0, 4);
	S32(BUF, 0xdc0a78 + 0x10) = irnd(0, 4) ? n : irnd(0, 4); S32(BUF, 0xdc0a78 + 0x14) = (int)(BUF + 0x121000);
	S32(BUF, 0xdc0cc4 + 0x10) = irnd(0, 4) ? n : irnd(0, 4); S32(BUF, 0xdc0cc4 + 0x14) = (int)(BUF + 0x123000);
	SF(BUF, 0x20f3970) = csu_fr(-200000, 200000); SF(BUF, 0x20f3978) = csu_fr(-200000, 200000); SF(BUF, 0xa08) = csu_fr(0, 300000);
	for (int i = 0; i < 4; i++) {
		char *L = BUF + 0xdc0248 + i * 0x20c; int rows = irnd(0, 8), cols = irnd(0, 8), cap = 2 * rows * (cols + 1) + 4;
		fill(L, 0x20c);
		SF(L, 0) = SF(BUF, 0x20f3970) + csu_fr(-300000, 100000); SF(L, 4) = csu_fr(-1000, 1000);
		SF(L, 8) = SF(BUF, 0x20f3978) + csu_fr(-300000, 100000);
		S32(L, 0x18) = rows; S32(L, 0x1c) = cols; SF(L, 0x20) = csu_fr(100, 50000); SF(L, 0x28) = csu_fr(100, 5000);
		S32(L, 0x2c) = irnd(0, 1); S32(L, 0x38) = (int)(BUF + 0x130000 + i * 0x1000);
		for (int k = 0; k < 64; k++) BUF[0x130000 + i * 0x1000 + k] = (char)irnd(0, 3);
		S32(L, 0x50) = irnd(0, 4) ? cap : irnd(0, cap); S32(L, 0x54) = (int)(BUF + 0x140000 + i * 0x1000);
		S32(L, 0x5c) = irnd(0, 4) ? 64 : irnd(0, 8); S32(L, 0x60) = (int)(BUF + 0x150000 + i * 0x1000);
		fill(BUF + 0x140000 + i * 0x1000, 0x400); fill(BUF + 0x150000 + i * 0x1000, 0x400);
		S32(BUF + 0x123000 + i * 0x80, 0x50) = (int)(BUF + 0x160000 + i * 0x100); S32(BUF + 0x123000 + i * 0x80, 0x5c) = (int)(BUF + 0x168000 + i * 0x100);
	}
	S32(BUF, 0xdc0a74) = n;                 /* the 4th layer's last dword is the layer count: set after the layers */
	SF(&g_a[4], 0) = csu_fr(-1000, 1000);
}
ST(render_processRenderingBy, renderproc_setup();,
   (TC(void, 0x497d20, char *, char *, float)(BUF, BUF + 0x100000, SF(&g_a[4], 0)), 0),
   (render_processRenderingBy(BUF, (DWORD)(BUF + 0x100000), (DWORD)g_a[4]), 0))
