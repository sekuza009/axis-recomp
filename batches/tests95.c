/* batch 94 */
/* shape_getByName's test cache at +0x19e188c with nothing set up to fail (as effect_initTextures' clean case), and
   the item file as the second VFS content ("Items.dat"): version 0x1201 (rarely not), 0..12 records (the count
   matches them: the reader trusts it), names empty now and then, shape names from the shape dat index or unknown */
static void itemfile_setup(void)
{
	char *self = BUF + 0x19e188c;
	shapecache_setup(self);
	self[0x130] = 0; S32(self, 0x114) = 200;
	S32(self, 0x230) = S32(BUF, 0xc016c); memcpy(self + 0x234, BUF + 0xc0170, 24);
	if (S32(self, 0x110) != 1) {
		BYTE *f = (BYTE *)g_vfsData; int np = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
		for (int p = 0; p < np; p++) strcpy((char *)f + 0x34 + p * rs + 4, BUF + 0xc0128 + S32((char *)S32(BUF, 0xcd134), 4) * 0x68);
	}
	if (S32(self, 0x128)) { S32(self, 0x128) = (int)(BUF + 0x800000); S32(self, 0x124) = 0x180000; }
	char *d = BUF + 0x880000, *t = BUF + 0x720000; int m = G32(0xa0e79c), n = irnd(0, 12);
	*(DWORD *)d = irnd(0, 19) ? 0x1201 : 0x1200;
	scrambled_count(d + 4, (DWORD)n);
	for (int i = 0; i < n; i++) {
		char *r = d + 8 + i * 0x90;
		fill(r, 0x90);
		if (irnd(0, 5)) fill_str(r, 20, 'A', 'Z'); else r[0] = 0;
		strcpy(r + 0x4c, m && irnd(0, 9) ? t + irnd(0, m - 1) * 0x44 : "NOPE");
		for (int b = 0; b < 0x90; b++) { BYTE c = (BYTE)r[b]; r[b] = (char)(((c >> 1) | (c << 7)) ^ 0x59); }
	}
	g_vfsAltName = "Items.dat"; g_vfsAltData = (BYTE *)d; g_vfsAltSize = (DWORD)(8 + n * 0x90);
	g_vfsOpenFail = 0; g_vfsFailMask = !irnd(0, 29);
	strcpy(BUF + 0x87ff00, "Map\\Items.dat");
	fill(BUF + 0x20f3adc, 4 + 12 * 0x90);
	g_a[0] = (int)(BUF + 0x87ff00);
}
ST(map_loadItemInfoFrom, itemfile_setup();, TC(int, 0x4875d0, char *, char *)(BUF, (char *)g_a[0]), map_loadItemInfoFrom(BUF, (DWORD)g_a[0]))
