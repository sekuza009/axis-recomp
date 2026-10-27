/* batch 68 */
/* the scene's level grid a space object with pools that cannot run out; level bounds around the origin and cell
   sizes giving 1..3 cells per axis; the bottom face sometimes; up to 2 layers (types 0..2) of up to 3 x 3 cells with
   vertices; up to 3 objects (active or not, flag 4 sometimes) with small shapes (as in space_buildUnits' test) and
   matrices */
static int g_cva[6];
static void colvol_setup(void)
{
	char *sp = BUF + 0xa10;
	fill(sp, 0x100);
	TC(void, 0x4813e0, char *, int, int, int, int, int, int, int)(sp, 200, 8000, 8, 1000, 27, (int)(BUF + 0x400000), 0x100000);
	float *lo = (float *)(BUF + 0x9ef904), *hi = (float *)(BUF + 0x9ef910);
	for (int i = 0; i < 3; i++) { lo[i] = (float)irnd(-1500, -500) / 100.0f; hi[i] = (float)irnd(500, 1500) / 100.0f; }
	static const int ax[3] = { 2, 0, 1 };                                   /* arg 1 sizes z, arg 2 x, arg 3 y */
	for (int k = 0; k < 3; k++) { float e = hi[ax[k]] - lo[ax[k]]; SF(&g_cva[k], 0) = e / ((float)irnd(1, 3) + 0.5f); }
	SF(&g_cva[3], 0) = irnd(0, 3) ? 0.0f : (float)irnd(0, 200) / 100.0f; g_cva[4] = irnd(0, 3); g_cva[5] = irnd(0, 1);
	S32(BUF, 0x9ef30c) = irnd(0, 1);
	int nl = irnd(0, 2); S32(BUF, 0xdc0a74) = nl;
	for (int i = 0; i < nl; i++) {
		char *L = BUF + 0xdc0248 + i * 0x20c; int rows = irnd(0, 3), cols = irnd(0, 3);
		fill(L, 0x60);
		S32(L, 4) = irnd(0, 4) ? irnd(0, 1) : 2; S32(L, 0x18) = rows; S32(L, 0x1c) = cols; S32(L, 0x3c) = (int)(BUF + 0x20000 + i * 0x400);
		for (int k = 0; k < (rows + 1) * (cols + 1) * 3; k++) SF(BUF + 0x20000 + i * 0x400, 4 * k) = (float)irnd(-1600, 1600) / 100.0f;
	}
	int no = irnd(0, 3); S32(BUF, 0x13c9b24) = no;
	for (int o = 0; o < no; o++) {
		char *ob = BUF + 0x131ae48 + o * 0x2cc, *sh = BUF + 0x30000 + o * 0x2000; int np = irnd(0, 2);
		fill(ob, 0x2cc);
		S32(ob, 0) = irnd(0, 3) ? 1 : irnd(0, 2); S32(ob, 8) = irnd(0, 4) ? 0 : 4; S32(ob, 0x278) = (int)sh;
		for (int i = 0; i < 16; i++) SF(ob, 0xf0 + 4 * i) = (float)irnd(-100, 100) / 100.0f;
		for (int i = 12; i < 15; i++) SF(ob, 0xf0 + 4 * i) = (float)irnd(-500, 500) / 100.0f;
		fill(sh, 0x20); S32(sh, 0x10) = np; S32(sh, 0x14) = (int)(sh + 0x100);
		for (int p = 0; p < np; p++) {
			char *pt = sh + 0x100 + p * 0x80; int nprim = irnd(0, 2);
			fill(pt, 0x80);
			S32(pt, 0) = irnd(0, 5) ? irnd(0, 1) : 0x20; S32(pt, 0x50) = (int)(sh + 0x400 + p * 0x100);
			for (int i = 0; i < 24; i++) SF(sh + 0x400 + p * 0x100, 4 * i) = (float)irnd(-1000, 1000) / 100.0f;
			S32(pt, 0x60) = nprim; S32(pt, 0x64) = (int)(sh + 0x600 + p * 0x100);
			for (int q = 0; q < nprim; q++) {
				char *pr = sh + 0x600 + p * 0x100 + q * 12;
				S32(pr, 0) = irnd(4, 6); S32(pr, 4) = irnd(0, 6); S32(pr, 8) = (int)(sh + 0x800 + p * 0x100 + q * 0x40);
				for (int i = 0; i < 8; i++) S32(sh + 0x800 + p * 0x100 + q * 0x40, 4 * i) = irnd(0, 7);
			}
		}
	}
}
ST(collision_initVolume, colvol_setup();,
   (TC(void, 0x471040, char *, int, int, int, int, int, int)(BUF, g_cva[0], g_cva[1], g_cva[2], g_cva[3], g_cva[4], g_cva[5]), 0),
   (collision_initVolume(BUF, (DWORD)g_cva[0], (DWORD)g_cva[1], (DWORD)g_cva[2], (DWORD)g_cva[3], (DWORD)g_cva[4], (DWORD)g_cva[5]), 0))
