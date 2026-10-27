/* batch 88 */
/* an object list (BUF + 0x8f0000) over shape_getByName's test cache (BUF + 0x700000; shp parts patched for
   binding and shading, element counts small) and skel_getSkeletonPtrBy's (BUF + 0x1000; its .ske / .ase file as
   the second VFS content, files only). 0..8 shape names (now and then 70: past the 64 kept), from the shape dat
   index, empty or unknown; 0..4 skeleton names from the skeleton dat index; lit 0 / 1 with shade_setup's factors */
static DWORD g_dl[11];
static void datalist_setup(void)
{
	char *sc = BUF + 0x700000, *kc = BUF + 0x1000, *tm = BUF, keep[0x80], set[0x20];
	shapecache_setup(sc);
	BYTE *shp = (BYTE *)(BUF + 0x9d0000); DWORD shpSize = g_vfsSize;   /* the skeleton setups write BUF + 0x200000 too */
	memcpy(shp, g_vfsData, shpSize);
	memcpy(keep, tm + 0x100, 0x80); memcpy(set, BUF + 0x400000, 0x20);
	skelcache_setup(kc);                                   /* writes BUF + 0x100 and BUF + 0x400000: put back below */
	if (S32(kc, 0x110) == 2) S32(kc, 0x110) = irnd(0, 1) ? 0 : 1;   /* files only (format 2 would read the shape dat's handle) */
	int ase = S32(kc, 0x110) == 1;
	if (ase) ase_setup(); else anim_setup();
	memcpy(BUF + 0x8c0000, g_vfsData, g_vfsSize);
	g_vfsAltName = ase ? ".ase" : ".ske"; g_vfsAltData = (BYTE *)(BUF + 0x8c0000); g_vfsAltSize = g_vfsSize;
	g_vfsData = shp; g_vfsSize = shpSize; g_vfsOpenFail = 0; g_vfsFailMask = 0; g_mockMallocFail = 0;
	memcpy(tm + 0x100, keep, 0x80); memcpy(BUF + 0x400000, set, 0x20);
	if (S32(kc, 0x128)) S32(kc, 0x128) = (int)(BUF + 0x980000);
	/* the shape file: parts that bind and shade */
	if (S32(sc, 0x110) != 1) {
		BYTE *f = (BYTE *)g_vfsData; int np = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
		*(int *)(f + 0x18) = np * 12;
		for (int p = 0; p < np; p++) {
			char *pr = (char *)f + 0x34 + p * rs;
			strcpy(pr + 4, BUF + 0xc0128 + S32((char *)S32(BUF, 0xcd134), 4) * 0x68);
			S32(pr, 0) = irnd(0, 4) ? 0 : 2; S32(pr, 0x48) = p * 12;
		}
	}
	sc[0x130] = 0; S32(sc, 0x114) = 200;
	S32(sc, 0x230) = S32(BUF, 0xc016c); memcpy(sc + 0x234, BUF + 0xc0170, 24);
	if (S32(sc, 0x128)) { S32(sc, 0x128) = (int)(BUF + 0x800000); S32(sc, 0x124) = 0x180000; }
	/* the names */
	char *sn = BUF + 0x900000, *kn = BUF + 0x910000, *st = BUF + 0x720000, *kt = BUF + 0x10000;
	int ns = irnd(0, 19) ? irnd(0, 8) : 70, nk = irnd(0, 4), ms = G32(0xa0e79c), mk = G32(0xa0eab4);
	for (int i = 0; i < ns; i++) {
		char *e = sn + i * 0x44; int c = irnd(0, 9);
		fill(e, 0x44);
		if (c < 8 && ms) strcpy(e, st + irnd(0, ms - 1) * 0x44); else if (c == 8) e[0] = 0; else strcpy(e, "NOPE");
	}
	for (int i = 0; i < nk; i++) { char *e = kn + i * 0x40; fill(e, 0x40); strcpy(e, mk ? kt + irnd(0, mk - 1) * 0x44 : "RUN"); }
	/* factors (shade_setup's) */
	char *f = BUF + 0x920000; int nf = irnd(0, 9) ? irnd(1, 4) : 0;
	S32(f, 0xb004) = nf;
	for (int k = 0; k < 4; k++) {
		char *r = f + 4 + k * 0x2c; fill(r, 0x2c);
		S32(r, 8) = irnd(0, 3);
		for (int j = 0x10; j < 0x28; j += 4) SF(r, j) = shade_f(-800, 800);
		SF(r, 0x28) = (float)irnd(0, 1200) / 100.0f;
	}
	char *list = BUF + 0x8f0000;
	fill(list, 0x40); S32(list, 0xc) = irnd(0, 2);
	int lit = irnd(0, 2) ? irnd(0, 1) : 2, need = (ns * 25 + nk) * 4 + (lit == 1 ? ns * 40 * 4 : 0);
	g_dl[0] = (int)sc; g_dl[1] = (int)kc; g_dl[2] = ns; g_dl[3] = (int)sn; g_dl[4] = nk; g_dl[5] = (int)kn;
	g_dl[6] = lit; g_dl[7] = irnd(0, 3) ? (int)f : 0; g_dl[8] = 0;
	g_dl[9] = irnd(0, 1) || lit == 1 ? (int)(BUF + 0x930000) : 0; g_dl[10] = irnd(0, 9) ? 0x20000 : irnd(0, need);
	/* the entries' matrices (+0xc, 16 floats; set by the caller in the game, not here): lit lists need invertible
	   ones, since Mat4_invert leaves a singular matrix's inverse unwritten and the shading then reads leftover stack,
	   which differs between the original's and the lifted run's call depths. So lit lists use this memory, which
	   holds rotations and translations; fresh allocations (zero) only for unlit ones */
	fill(BUF + 0x930000, 0x2000);
	for (int i = 0; i < 70; i++) {
		float *m = (float *)(BUF + 0x930000 + i * 100 + 0xc), a = (float)irnd(-314, 314) / 100.0f;
		memset(m, 0, 64); m[0] = m[5] = cosf(a); m[1] = sinf(a); m[4] = -m[1]; m[10] = m[15] = 1.0f;
		for (int k = 12; k < 15; k++) m[k] = (float)irnd(-500, 500) / 10.0f;
	}
	g_paintStacks = 1;
}
ST(data_loadFrom_46f4e0, datalist_setup();,
   (TC(void, 0x46f4e0, char *, int, int, int, int, int, int, int, int, int, int, int)(BUF + 0x8f0000, g_dl[0], g_dl[1], g_dl[2], g_dl[3],
     g_dl[4], g_dl[5], g_dl[6], g_dl[7], g_dl[8], g_dl[9], g_dl[10]), 0),
   (data_loadFrom_46f4e0(BUF + 0x8f0000, g_dl[0], g_dl[1], g_dl[2], g_dl[3], g_dl[4], g_dl[5], g_dl[6], g_dl[7], g_dl[8], g_dl[9], g_dl[10]), 0))
