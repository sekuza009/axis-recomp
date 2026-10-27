/* batch 86 */
/* object_initObjectBy's test with the slot bookkeeping: the free slot is the object being set up (now and then
   1000: the pool is full), the highest used slot at or a little past it, the objects after it used or not */
static void objadd_setup(void)
{
	objinit_setup();
	char *sc = BUF; int i = g_a[0], hi = i + irnd(0, 4);
	if (hi > 999) hi = 999;
	if (!irnd(0, 3)) hi = i;
	S32(sc, 0x13c9b28) = irnd(0, 29) ? i : 1000; S32(sc, 0x13c9b24) = hi;
	for (int j = i + 1; j <= hi + 1 && j <= 1000; j++) S32(sc, 0x131ae48 + j * 0x2cc) = irnd(0, 2) ? 1 : 0;
	g_a[0] = g_a[1];
}
ST(object_addObjectBy, objadd_setup();, TC(int, 0x490c50, char *, char *)(BUF, (char *)g_a[0]), object_addObjectBy(BUF, (DWORD)g_a[0]))
/* the effect shapes: shape_getByName's test cache at +0x19e188c with its tree rebuilt from a random part of the 32
   effect names (and the dat index from all of them, one sometimes left out); the cache has room for every miss
   now and then not */
static void effshapes_setup(void)
{
	char *self = BUF + 0x19e188c, *nodes = BUF + 0x701000, names[32][0x40];
	shapecache_setup(self);
	static const char *one[] = { "Effect\\Shell-Fire", "Effect\\Shell-Bullet", "Effect\\Rail-Fire", "Effect\\Blade-Fire",
	                             "Effect\\Rail-Bullet", "Effect\\Lightning-Bullet", "Effect\\Missile-Bullet", "Effect\\Homing-Bullet" };
	for (int k = 0; k < 8; k++) {
		sprintf(names[k], "Effect\\PlasmaThrust-%d", k); sprintf(names[8 + k], "Effect\\IonThrust-%d", k);
		sprintf(names[16 + k], "Effect\\GravityThrust-%d", k); strcpy(names[24 + k], one[k]);
	}
	for (int k = 0; k < 32; k++) for (char *c = names[k]; *c; c++) if (*c >= 'a' && *c <= 'z') *c -= 0x20;
	int n = 0, used[32] = { 0 }, want = irnd(0, 1) ? irnd(0, 32) : irnd(0, 12);
	for (int t = 0; t < 200 && n < want; t++) {
		int j = irnd(0, 31);
		if (used[j]) continue;
		used[j] = 1;
		char *e = nodes + n * 0x4c;
		strcpy(e, names[j]); S32(e, 0x40) = n % 12; S32(e, 0x44) = 0; S32(e, 0x48) = 0;   /* the 12 prebuilt shapes, reused */
		for (char *p = nodes; n; ) {
			int r = strcmp(e, p), off = r < 0 ? 0x44 : 0x48;
			if (!S32(p, off)) { S32(p, off) = (int)e; break; }
			p = (char *)S32(p, off);
		}
		n++;
	}
	S32(self, 0x120) = n;
	S32(self, 0x114) = irnd(0, 3) ? n + 32 : n + irnd(0, 8);
	int clean = irnd(0, 3) != 0;                  /* three in four: nothing set up to fail */
	char *t = BUF + 0x720000; int m = 0, skip = clean || irnd(0, 2) ? -1 : irnd(0, 31);
	char srt[32][0x40]; memcpy(srt, names, sizeof srt);
	for (int a = 0; a < 32; a++) for (int b = a + 1; b < 32; b++)
		if (strcmp(srt[b], srt[a]) < 0) { char x[0x40]; strcpy(x, srt[a]); strcpy(srt[a], srt[b]); strcpy(srt[b], x); }
	for (int a = 0; a < 32; a++) {
		if (skip >= 0 && !strcmp(srt[a], names[skip])) continue;
		strcpy(t + m * 0x44, srt[a]); S32(t + m * 0x44, 0x40) = 0; m++;
	}
	strcpy(t + m * 0x44, "\x7f\x7f"); S32(t + m * 0x44, 0x40) = 0;
	G32(0xa0e79c) = m;
	fill(BUF + 0x20f2dac, 0x200);
	if (S32(self, 0x128)) { S32(self, 0x128) = (int)(BUF + 0x800000); S32(self, 0x124) = 0x180000; fill(BUF + 0x800000, 0x1000); }   /* room for 32 loads, clear of the tree */
	memset(BUF + 0x702000 + 12 * 0x4c, 0, 52 * 0x4c);          /* the shapes the misses load into */
	/* mostly the path through all 32: no suffix (suffixed names are no textures), and shp files mostly from the dat
	   (format 2 opens no file; the mock VFS has 14 opens per run, fewer than the misses) */
	if (irnd(0, 9)) self[0x130] = 0;
	if (S32(self, 0x110) == 0 && irnd(0, 3)) S32(self, 0x110) = 2;
	if (clean) {
		self[0x130] = 0; S32(self, 0x114) = n + 32;
		S32(self, 0x230) = S32(BUF, 0xc016c); memcpy(self + 0x234, BUF + 0xc0170, 24);   /* the records' own colours */
		if (S32(self, 0x110) != 1) {                /* shp part textures: GL slot owners only */
			BYTE *f = (BYTE *)g_vfsData; int np = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
			for (int p = 0; p < np; p++) strcpy((char *)f + 0x34 + p * rs + 4, BUF + 0xc0128 + S32((char *)S32(BUF, 0xcd134), 4) * 0x68);
		}
	}
}
static int g_effDone;
static DWORD effshapes_orig(void) { TC(void, 0x48ec20, char *)(BUF); g_effDone++; return 0; }   /* counts runs that got through all 32 */
ST(effect_initTextures, effshapes_setup();, effshapes_orig(), (effect_initTextures(BUF), 0))
