/* batch 64 */
/* every part scene_reset touches, as each callee's own test sets it up; the level grid a fresh space object */
static void scenereset_setup(void)
{
	fill(BUF + 0x9d8000, 0x20); fill(BUF + 0x9e3010, 0x10);
	for (int i = 0; i < 1000; i++) S32(BUF, 0x20a99c4 + i * 0x12c) = irnd(-3, 3);
	for (int i = 0; i < 400; i++) S32(BUF, 0x202ef38 + i * 0x4e8) = irnd(-3, 3);
	for (int i = 0; i < 1000; i++) S32(BUF, 0x131ae48 + i * 0x2cc) = irnd(-3, 3);
	fill(BUF + 0x20f2fc0, 0x9b0); fill((void *)0xa0e7a8, 12); fill((void *)0xa1f220, 4);
	fill(BUF + 0x2148ecc, 0x10); fill(BUF + 0x2149300, 0x30);
	levelgrid_setup();
}
ST(scene_reset, scenereset_setup();, (TC(void, 0x470ad0, char *)(BUF), 0), (scene_reset(BUF), 0))
/* a shape file: header (size = what the parts need, sometimes more; version mostly current), part records (vertex
   count +0x4c, polygon count +0x60, bounds +0x68), then each part's arrays (floats) and polygons (index count +4,
   small indices) */
static void shaperead_setup(void)
{
	BYTE *f = (BYTE *)(BUF + 0x200000); int cur = irnd(0, 4) != 0, rs = cur ? 0x80 : 0x68, n = irnd(0, 4), len = 0x34;
	int nv[4], np[4], need = n * 0x80;
	fill(f, 0x34); for (int k = 0; k < 4; k++) SF(f, 0x20 + 4 * k) = csu_fr(-10000, 10000);
	*(DWORD *)(f + 0x30) = cur ? 0x71110300 : 0x71110200; *(int *)(f + 0x10) = n;
	for (int i = 0; i < n; i++) {
		BYTE *r = f + len; fill(r, rs); nv[i] = irnd(0, 6); np[i] = irnd(0, 1);   /* the data memory keeps 12 bytes for the polygon headers: more than one is overwritten by the index lists (game files have one) */
		*(int *)(r + 0x4c) = nv[i]; *(int *)(r + 0x60) = np[i];
		if (cur) for (int k = 0; k < 6; k++) SF(r, 0x68 + 4 * k) = csu_fr(-10000, 10000);
		len += rs;
	}
	for (int i = 0; i < n; i++) {
		for (int k = 0; k < nv[i] * 9; k++) { SF(f + len, 0) = csu_fr(-10000, 10000); len += 4; }
		int pl = len; len += np[i] * 12; need += nv[i] * 36 + 12;
		for (int p = 0; p < np[i]; p++) {
			int c = irnd(0, 5); fill(f + pl + p * 12, 12); *(int *)(f + pl + p * 12 + 4) = c; need += c * 4 + 12;
			for (int k = 0; k < c; k++) { *(int *)(f + len) = irnd(0, 5); len += 4; }
		}
	}
	*(int *)(f + 4) = need + (irnd(0, 3) ? 0 : irnd(0, 0x100));
	g_vfsData = f; g_vfsSize = (DWORD)len;
	fill(BUF + 0x100, 0x80); S32(BUF + 0x100, 0xc) = 0;
	g_a[0] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[1] = irnd(0, 5) ? 0x40000 : irnd(0, 0x200);
	fill(BUF + 0x400000, 0x2000);
}
ST(shape_read, shaperead_setup();, (TC(void, 0x466120, char *, int, int, int)(BUF + 0x100, (int)VFS_FILE(0), g_a[0], g_a[1]), 0),
   (shape_read(BUF + 0x100, VFS_FILE(0), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
