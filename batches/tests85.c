/* batch 84 */
/* the shape cache (self; its tree and shapes at BUF + 0x701000...) over tex_bind's texture set (0xa0e010; 21 records sharing the cache's flags and
   colours, sometimes not one of them): a tree of 0..9 pool names whose shapes have parts with GL-slot textures, the
   input a pool name, a tree one, empty / ".x" or random. A miss loads shape_read's test file (formats 0 and 2,
   part texture names patched to textures that own a GL slot, now and then another record's or an unknown one) or
   obj_setup's (format 1: its material names are no textures, so binding ends in the fatal "can't find") */
static void shapecache_setup(char *self)
{
	static const char *pool[] = { "MECH", "mech_a", "Rock/B", "TREE", "tree2", "Gun", "BASE2", "a", "zz", "Arm\\L", "Z9", "_x" };
	enum { NP = 12 };
	texset_setup();
	char *tm = BUF, *set = BUF + 0x400000, *nodes = BUF + 0x701000, *shp = BUF + 0x702000, up[NP][0x40];
	G32(0xa0e010) = (int)set;
	int k = 0; while (S32(set, 4 + k * 4) != (int)tm) k++;
	/* the textures: 21 records, the GL slot owners' names */
	int own[6], no = 0;
	{ char *sl = (char *)S32(tm, 0xcd134), *s0 = sl; do { own[no++] = S32(sl, 4); sl = (char *)S32(sl, 0xc); } while (sl != s0 && no < 6); }
	S32(tm, 0xcd128) = 21;
	fill(self, 0x250);
	S32(self, 0x230) = irnd(0, 3);
	for (int j = 0; j < 6; j++) GF(self + 0x234 + j * 4) = (float)irnd(-500, 500) / 100.0f;
	for (int t = 0; t <= 20; t++) {
		char *r = tm + t * 0x68;
		tex_token(r + 0xc0128); S32(r, 0xc018c) = 0;
		S32(r, 0xc016c) = S32(self, 0x230); memcpy(r + 0xc0170, self + 0x234, 24);
	}
	if (!irnd(0, 4)) GF(self + 0x234 + irnd(0, 5) * 4) += 1.0f;   /* a hit with new colours: recoloured, reloaded */
	/* the file */
	for (int i = 0; i < NP; i++) {
		strcpy(up[i], pool[i]);
		for (char *c = up[i]; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
	}
	int fmt = irnd(0, 2);
	char keep[0x80]; memcpy(keep, tm + 0x100, 0x80);         /* the file setups write BUF + 0x100 and BUF + 0x400000 */
	if (fmt == 1) obj_setup();
	else {
		shaperead_setup();
		BYTE *f = (BYTE *)g_vfsData; int n = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
		for (int p = 0; p < n; p++) {
			char *nm = (char *)f + 0x34 + p * rs + 4; int c = irnd(0, 19);
			if (c < 16) strcpy(nm, tm + 0xc0128 + own[irnd(0, no - 1)] * 0x68);
			else if (c < 19) strcpy(nm, tm + 0xc0128 + irnd(0, 20) * 0x68);
			else strcpy(nm, "NOPE");
		}
	}
	memcpy(tm + 0x100, keep, 0x80);
	for (int j = 0; j < 6; j++) S32(set, 4 + j * 4) = j == k ? (int)tm : 0;
	g_vfsOpenFail = 0; g_vfsFailMask = !irnd(0, 29);
	g_mockMallocFail = 0;
	if (irnd(0, 1)) strcpy(self + 0x10, "Data\\Shape"); else self[0x10] = 0;
	if (irnd(0, 4)) self[0x130] = 0; else strcpy(self + 0x130, "S");
	/* the tree and its shapes (0..3 parts each, textures of the slot owners) */
	int cnt = irnd(0, 9), used[NP] = { 0 }, n = 0;
	fill(nodes, 12 * 0x4c); fill(shp, 12 * 0x4c);
	for (int s = 0; s < 12; s++) {
		char *sh = shp + s * 0x4c, *parts = BUF + 0x710000 + s * 0x200; int np = irnd(0, 3);
		S32(sh, 0xc) = 0; S32(sh, 0x10) = np; S32(sh, 0x14) = (int)parts; S32(sh, 0x18) = np * 12;
		for (int j = 0; j < 3; j++) SF(sh, 0x20 + j * 4) = (float)irnd(-500, 500) / 100.0f;
		for (int p = 0; p < np; p++) {
			char *pt = parts + p * 0x80, *d = BUF + 0x730000 + (s * 3 + p) * 0x300; int nv = irnd(1, 4);
			fill(pt, 0x80); S32(pt, 0x44) = irnd(0, 5) ? k * 512 + own[irnd(0, no - 1)] : -1;
			S32(pt, 0) = irnd(0, 4) ? 0 : 2; S32(pt, 0x48) = p * 12; S32(pt, 0x4c) = nv;   /* shade_setup's part */
			S32(pt, 0x50) = (int)d; S32(pt, 0x54) = (int)(d + 0x100); S32(pt, 0x58) = (int)(d + 0x200);
			for (int v = 0; v < nv * 3; v++) { SF(d, 4 * v) = (float)irnd(-500, 500) / 100.0f; SF(d + 0x100, 4 * v) = shade_f(-100, 100); }
			fill(d + 0x200, 0x40);
			for (int j = 0; j < 3; j++) { SF(pt, 0x68 + 4 * j) = -5.0f - (float)irnd(0, 100) / 100.0f; SF(pt, 0x74 + 4 * j) = 5.0f + (float)irnd(0, 100) / 100.0f; }
		}
	}
	for (int i = 0; i < cnt; i++) {
		int j = irnd(0, NP - 1);
		if (used[j]) continue;
		used[j] = 1;
		char *e = nodes + n * 0x4c;
		strcpy(e, up[j]); S32(e, 0x40) = n; S32(e, 0x44) = 0; S32(e, 0x48) = 0;
		for (char *p = nodes; n; ) {
			int r = strcmp(e, p), off = r < 0 ? 0x44 : 0x48;
			if (!S32(p, off)) { S32(p, off) = (int)e; break; }
			p = (char *)S32(p, off);
		}
		n++;
	}
	S32(self, 0x110) = fmt; S32(self, 0x118) = (int)nodes; S32(self, 0x11c) = (int)shp; S32(self, 0x120) = n;
	S32(self, 0x114) = irnd(0, 19) ? (irnd(0, 9) ? n + irnd(1, 3) : n) : 0;
	if (irnd(0, 1)) { S32(self, 0x128) = (int)(BUF + 0x600000); S32(self, 0x124) = 0x40000; S32(self, 0x12c) = irnd(0, 3) * 0x100; }
	else S32(self, 0x128) = 0;
	fill(BUF + 0x600000, 0x1000);
	/* the shape dat index: the pool names sorted, one sometimes left out, items at offset 0 of the VFS file */
	char *t = BUF + 0x720000; int m = 0, skip = irnd(0, 1) ? irnd(0, NP - 1) : -1;
	char srt[NP][0x40]; memcpy(srt, up, sizeof srt);
	for (int a = 0; a < NP; a++) for (int b = a + 1; b < NP; b++)
		if (strcmp(srt[b], srt[a]) < 0) { char x[0x40]; strcpy(x, srt[a]); strcpy(srt[a], srt[b]); strcpy(srt[b], x); }
	for (int a = 0; a < NP; a++) {
		if (skip >= 0 && !strcmp(srt[a], up[skip])) continue;
		strcpy(t + m * 0x44, srt[a]); S32(t + m * 0x44, 0x40) = 0; m++;
	}
	strcpy(t + m * 0x44, "\x7f\x7f"); S32(t + m * 0x44, 0x40) = 0;
	G32(0xa0e79c) = m; G32(0xa0e7a0) = (int)t; G32(0xa0e7a4) = (int)VFS_FILE(0);
	/* the name */
	char *nm = self + 0x400; int c = irnd(0, 9);
	if (c < 6) strcpy(nm, pool[irnd(0, NP - 1)]);
	else if (c < 8 && n) strcpy(nm, nodes + irnd(0, n - 1) * 0x4c);
	else if (c == 8) strcpy(nm, irnd(0, 1) ? "" : ".shp");
	else fill_str(nm, 20, 33, 126);
	g_a[0] = (int)nm; g_a[1] = irnd(0, 2);
}
static int g_shapeLoads;
static DWORD shapecache_orig(void)   /* counts the misses the original loaded and bound to the end */
{
	int before = S32(BUF + 0x700000, 0x120);
	DWORD r = (DWORD)TC(int, 0x466dc0, char *, char *, int)(BUF + 0x700000, (char *)g_a[0], g_a[1]);
	g_shapeLoads += S32(BUF + 0x700000, 0x120) > before;
	return r;
}
ST(shape_getByName, shapecache_setup(BUF + 0x700000);, shapecache_orig(),
   shape_getByName(BUF + 0x700000, (DWORD)g_a[0], (DWORD)g_a[1]))
