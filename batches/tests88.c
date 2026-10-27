/* batch 87 */
/* object_initObjectBy's scene and shape cache (shp files mostly, part textures GL slot owners, nothing set up to
   fail in the cache), a skeleton cache of 0..3 entries to release, and the object list as the second VFS content
   ("M1.obj"): version 0x1201 (rarely not), 0..6 objects (now and then 60: two blocks) named after the shape dat
   index's names, scrambled. The shading file (third content) is missing half the time in mode 0 */
static void mapobjects_setup(void)
{
	objinit_setup();
	char *sc = BUF, *self = sc + 0xe3c93c;
	/* the shape cache: as effect_initTextures' clean case */
	self[0x130] = 0; S32(self, 0x114) = 200;
	S32(self, 0x230) = S32(BUF, 0xc016c); memcpy(self + 0x234, BUF + 0xc0170, 24);
	if (S32(self, 0x110) != 1) {
		BYTE *f = (BYTE *)g_vfsData; int np = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
		for (int p = 0; p < np; p++) {
			char *pr = (char *)f + 0x34 + p * rs;
			strcpy(pr + 4, BUF + 0xc0128 + S32((char *)S32(BUF, 0xcd134), 4) * 0x68);
			S32(pr, 0) = irnd(0, 4) ? 0 : 2; S32(pr, 0x48) = p * 12;   /* shading: a known type and a colour offset in the shape's range */
		}
	}
	if (S32(self, 0x128)) { S32(self, 0x128) = (int)(BUF + 0x800000); S32(self, 0x124) = 0x180000; }
	/* the skeleton cache: 0..3 entries to release */
	char *sk = sc + 0x13016d0;
	S32(sk, 0x120) = irnd(0, 3); S32(sk, 0x11c) = (int)(BUF + 0x890000); S32(sk, 0x12c) = irnd(-5, 5);
	fill(BUF + 0x890000, 3 * 0x24);
	/* the object list */
	char *d = BUF + 0x880000, *t = BUF + 0x720000; int m = G32(0xa0e79c), n = irnd(0, 19) ? irnd(0, 6) : 60;
	*(DWORD *)d = irnd(0, 19) ? 0x1201 : 0x1200;
	scrambled_count(d + 4, (DWORD)irnd(0, 9)); scrambled_count(d + 8, (DWORD)n);   /* the second value is the count */
	for (int i = 0; i < n; i++) {
		char *r = d + 12 + i * 0xb0;
		fill(r, 0xb0);
		strcpy(r, m ? t + irnd(0, m - 1) * 0x44 : "MECH");
		if (irnd(0, 1)) r[0x4c] = 0; else strcpy(r + 0x4c, "ROCKS");
		for (int k = 0; k < 3; k++) { SF(r, 0x8c + k * 4) = (float)irnd(-5000, 5000) / 10.0f; SF(r, 0x98 + k * 4) = (float)irnd(-314, 314) / 100.0f; }
		SF(r, 0xa4) = (float)irnd(0, 100) / 10.0f;
		for (int b = 0; b < 0xb0; b++) { BYTE c = (BYTE)r[b]; r[b] = (char)(((c >> 1) | (c << 7)) ^ 0x59); }
	}
	g_vfsAltName = "M1.obj"; g_vfsAltData = (BYTE *)d; g_vfsAltSize = (DWORD)(12 + n * 0xb0);
	/* the shading file: a scrambled count and that many colour dwords (a garbage count would make the original
	   descramble past its buffer: the reader trusts it) */
	char *sf = BUF + 0x8a0000; int ns = irnd(0, 300);
	scrambled_count(sf, (DWORD)ns); fill(sf + 4, ns * 4);
	g_vfsAltName2 = "objectShadingInfo"; g_vfsAltData2 = (BYTE *)sf; g_vfsAltSize2 = (DWORD)(4 + ns * 4 - (irnd(0, 9) ? 0 : irnd(0, ns * 4)));
	/* the scene's dir (+0x108) is left alone: in this layout it is the texture manager's dat count (small: a one-
	   character or empty string) and the next dword its table pointer */
	strcpy(BUF + 0x880000 - 0x100, irnd(0, 9) ? "M1.obj" : "none.obj");
	int mode = irnd(0, 9) ? irnd(0, 1) : 2;
	g_vfsOpenFail = 0;
	g_vfsFailMask = mode == 0 && irnd(0, 1) ? 1 : 0;          /* the shading file is attempt 0 in mode 0 */
	if (S32(self, 0x110) != 1) *(int *)(g_vfsData + 0x18) = irnd(0, 40);   /* the shape's element count: random (even negative) it would send
	                                                                         the pool pointer anywhere, past the check for > 1000000 */
	g_a[0] = (int)(BUF + 0x880000 - 0x100); g_a[1] = mode;
	S32(sc, 0x13016c8) = irnd(0, 1000);             /* not objinit's 999990 now and then: the pool is read and written whole */
}
static int g_mapObjDone;
static DWORD mapobjects_orig(void) { TC(void, 0x48b710, char *, char *, int)(BUF, (char *)g_a[0], g_a[1]); g_mapObjDone++; return 0; }
ST(map_loadObjectInfoFrom, mapobjects_setup();, mapobjects_orig(),
   (map_loadObjectInfoFrom(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
