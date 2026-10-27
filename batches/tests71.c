/* batch 70 */
/* a shape (BUF + 0x100) of up to 3 parts, each with up to 12 vertices (positions, normals sometimes zero or NaN, base
   colours), a box around them (sometimes far away), flags 0 / 2; a factor pool (BUF + 0x10000) of up to 4 factors of
   types 0..3 (rarely 4: fatal) with colours, positions, directions and radii; a matrix or none */
static float shade_f(int lo, int hi) { return irnd(0, 59) ? (float)irnd(lo, hi) / 100.0f : irnd(0, 1) ? 0.0f : 0.0f / 0.0f; }
static void shade_setup(void)
{
	char *sh = BUF + 0x100; int np = irnd(1, 3);
	fill(sh, 0x20); S32(sh, 0x10) = np; S32(sh, 0x14) = (int)(BUF + 0x200);
	for (int p = 0; p < 3; p++) {
		char *pt = BUF + 0x200 + p * 0x80, *d = BUF + 0x1000 + p * 0x1000; int nv = irnd(0, 9) ? irnd(1, 12) : 0;
		fill(pt, 0x80);
		S32(pt, 0) = irnd(0, 4) ? 0 : 2; S32(pt, 0x48) = p * 12; S32(pt, 0x4c) = nv;
		S32(pt, 0x50) = (int)d; S32(pt, 0x54) = (int)(d + 0x100); S32(pt, 0x58) = (int)(d + 0x200);
		for (int i = 0; i < nv * 3; i++) { SF(d, 4 * i) = (float)irnd(-500, 500) / 100.0f; SF(d + 0x100, 4 * i) = shade_f(-100, 100); }
		fill(d + 0x200, 0x40);
		int away = !irnd(0, 4);
		for (int k = 0; k < 3; k++) { SF(pt, 0x68 + 4 * k) = away ? 900.0f : -5.0f - (float)irnd(0, 100) / 100.0f; SF(pt, 0x74 + 4 * k) = away ? 1000.0f : 5.0f + (float)irnd(0, 100) / 100.0f; }
	}
	char *f = BUF + 0x10000; int nf = irnd(0, 9) ? irnd(1, 4) : 0;
	S32(f, 0xb004) = nf;
	for (int k = 0; k < 4; k++) {
		char *r = f + 4 + k * 0x2c; fill(r, 0x2c);
		S32(r, 8) = irnd(0, 40) ? irnd(0, 3) : 4;
		for (int i = 0x10; i < 0x28; i += 4) SF(r, i) = shade_f(-800, 800);
		SF(r, 0x28) = irnd(0, 9) ? (float)irnd(0, 1200) / 100.0f : shade_f(-100, 100);
	}
	float *m = (float *)(BUF + 0x20000);
	for (int i = 0; i < 16; i++) m[i] = (i % 5 == 0) ? 1.0f : (float)irnd(-30, 30) / 100.0f;
	for (int i = 12; i < 15; i++) m[i] = (float)irnd(-300, 300) / 100.0f;
	g_a[0] = irnd(0, 1); g_a[1] = irnd(0, 2) ? 0 : (int)m; g_a[2] = irnd(0, 2);
	fill(BUF + 0x30000, 0x100);
	G32(0xae2ec8) = 0; G32(0xa1efe8) = 0; vfs_content(0, 0);   /* the fatal path (type 4): no log / error hooks, as in sys_errorTerminate's test */
}
ST(shape_getShadingColorBufferBy, shade_setup();,
   (((void (__cdecl *)(char *, int, char *, char *, int))0x463b80)(BUF + 0x30000, g_a[0], BUF + 0x200 + g_a[2] * 0x80, BUF + 0x10000, g_a[1]), 0),
   (shape_getShadingColorBufferBy(0, 0, 0, (DWORD)(BUF + 0x30000), (DWORD)g_a[0], (DWORD)(BUF + 0x200 + g_a[2] * 0x80), (DWORD)(BUF + 0x10000), (DWORD)g_a[1], 0, 0, 0), 0))
ST(FUN_00466910, shade_setup();,
   (((void (__cdecl *)(char *, int, char *, char *, int))0x466910)(BUF + 0x30000, g_a[0], BUF + 0x100, BUF + 0x10000, g_a[1]), 0),
   (FUN_00466910(0, 0, 0, (DWORD)(BUF + 0x30000), (DWORD)g_a[0], (DWORD)(BUF + 0x100), (DWORD)(BUF + 0x10000), (DWORD)g_a[1], 0, 0, 0), 0))
