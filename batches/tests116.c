/* batch 115 */
/* the scene at BUF, as scene_reset's and scene_resetActors' tests set it up (item_initTextures lays out the rest).
   Everything else lives in the gap after the scene's last fields (BUF + 0x2150000 ..): a texture manager whose
   records are every texture asked for (the ten numbered ones, the three item textures; flags and colours as
   asked, so each lookup is a plain hit), one sometimes left out (fatal); the nine name arguments; the shape dat
   (index of the 32 effect names, one sometimes left out, every item at offset 0 of shape_read's test file, part
   textures among the records) for the effect cache, which item_initTextures empties first */
static void sceneinit_scrub(void);
static void sceneinit_setup(void)
{
	scenereset_setup(); actors_setup();
	fill(BUF + 0x202e8d0, 0x20); fill(SCENE + 0x20f3ab8, 0x24);
	fill((void *)0xa1f220, 4); fill((void *)0xa1f23c, 4);
	char *M = BUF + 0x2150000;                      /* the manager; its image area (M .. M + 0xc0128) holds the rest */
	char *set = M + 0x200, *args = M + 0x400, *idx = M + 0x1000, *file = M + 0x10000;
	/* the names */
	for (int k = 0; k < 9; k++) fill_str(args + k * 0x40, irnd(1, 30), 'A', 'Z');
	char *base = args + 2 * 0x40;
	if (irnd(0, 1)) strcpy(base, "Texture\\Sky");
	/* the records */
	char want[16][0x40]; int nw = 0, fl[16];
	for (int k = 0; k < 10; k++) { sprintf(want[nw], "%s\\%02d", base, k); fl[nw++] = k > 7; }
	strcpy(want[nw], "Texture\\Item_damagemap_ani0"); fl[nw++] = 0;
	strcpy(want[nw], "Texture\\Item_booster_ani0"); fl[nw++] = 0;
	strcpy(want[nw], "Texture\\Item_shield_ani0"); fl[nw++] = 0;
	int miss = irnd(0, 19) ? -1 : irnd(0, nw - 1), m = 0;
	memset(M + 0xc0100, 0, 0x30); S32(M, 0xc0114) = 0;
	for (int k = 0; k < nw; k++) {
		if (k == miss) continue;
		char *r = M + 0xc0128 + m * 0x68; memset(r, 0, 0x68);
		strcpy(r, want[k]);
		for (char *c = r; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
		S32(r, 0x44) = fl[k];
		m++;
	}
	S32(M, 0xcd128) = m; S32(M, 0xcd130) = 0; S32(M, 0x108) = 0; S32(M, 0x10c) = (int)idx;
	/* tex_bind's GL slot ring (0x14 bytes: slot, owner, GL name, next, prev): every record has its own slot, so a
	   bind only moves it in the ring */
	char *ring = M + 0x30000;
	for (int k = 0; k < m; k++) {
		char *s = ring + k * 0x14;
		S32(s, 0) = k; S32(s, 4) = k; S32(s, 8) = 0x100 + k;
		S32(s, 0xc) = (int)(ring + (k + 1) % m * 0x14); S32(s, 0x10) = (int)(ring + (k + m - 1) % m * 0x14);
		S32(M + 0xc0128 + k * 0x68, 0x40) = k;
	}
	S32(M, 0xcd12c) = (int)ring; S32(M, 0xcd134) = (int)(ring + irnd(0, m - 1) * 0x14); S32(M, 0xcd138) = 0;
	memset(set, 0, 0x20); int slot = irnd(0, 5); S32(set, 4 + slot * 4) = (int)M;
	G32(0xa0e010) = (int)set;
	/* the effect cache's suffix and texture flags / colours (shape_initBy keeps them): none, as the records */
	char *ec = BUF + 0x19e188c; ec[0x130] = 0; memset(ec + 0x230, 0, 0x1c);
	/* the shape dat */
	shaperead_setup();
	BYTE *f = (BYTE *)g_vfsData; int np = *(int *)(f + 0x10), rs = *(DWORD *)(f + 0x30) == 0x71110300 ? 0x80 : 0x68;
	for (int p = 0; p < np; p++) {
		char *nm = (char *)f + 0x34 + p * rs + 4;
		strcpy(nm, M + 0xc0128 + irnd(0, m - 1) * 0x68);
	}
	memcpy(file, g_vfsData, g_vfsSize); g_vfsData = (const BYTE *)file;
	static const char *one[] = { "Effect\\Shell-Fire", "Effect\\Shell-Bullet", "Effect\\Rail-Fire", "Effect\\Blade-Fire",
	                             "Effect\\Rail-Bullet", "Effect\\Lightning-Bullet", "Effect\\Missile-Bullet", "Effect\\Homing-Bullet" };
	char names[32][0x40];
	for (int k = 0; k < 8; k++) {
		sprintf(names[k], "EFFECT\\PLASMATHRUST-%d", k); sprintf(names[8 + k], "EFFECT\\IONTHRUST-%d", k);
		sprintf(names[16 + k], "EFFECT\\GRAVITYTHRUST-%d", k); strcpy(names[24 + k], one[k]);
		for (char *c = names[24 + k]; *c; c++) if (*c >= 'a' && *c <= 'z') *c -= 0x20;
	}
	for (int a = 0; a < 32; a++) for (int b = a + 1; b < 32; b++)
		if (strcmp(names[b], names[a]) < 0) { char x[0x40]; strcpy(x, names[a]); strcpy(names[a], names[b]); strcpy(names[b], x); }
	int skip = irnd(0, 19) ? -1 : irnd(0, 31), n = 0;
	for (int a = 0; a < 32; a++) {
		if (a == skip) continue;
		strcpy(idx + n * 0x44, names[a]); S32(idx + n * 0x44, 0x40) = 0; n++;
	}
	strcpy(idx + n * 0x44, "\x7f\x7f"); S32(idx + n * 0x44, 0x40) = 0;
	G32(0xa0e79c) = n; G32(0xa0e7a0) = (int)idx; G32(0xa0e7a4) = (int)VFS_FILE(0);
	g_vfsOpenFail = 0; g_vfsFailMask = 0; g_mockMallocFail = 0;
	for (int k = 0; k < 8; k++) g_a[k] = (int)(args + k * 0x40);   /* g_a holds 8: the ninth is g_a[7] + 0x40 */
	g_paintStacks = 1; g_postRun = sceneinit_scrub;
}
static int g_sceneInitDone;
/* the light factor records (pool +0x9ccffc and +0x9e3020: 0x2c bytes from +4, count +0xb004) are built on the stack
   with only some fields set (slot, in use, type, colour; type 1 a position at +0x1c, type 2 one at +0x10 and a value
   at +0x28) and copied whole: the rest is leftover stack (return addresses, stack pointers), which no run on another
   stack can match and nothing reads. Both runs clear those fields before the comparison */
static void factor_scrub(char *pool)
{
	int n = S32(pool, 0xb004);
	for (int k = 0; k < n && k < 1024; k++) {
		char *r = pool + 4 + k * 0x2c; int t = S32(r, 8);
		for (int o = 0x10; o < 0x2c; o += 4)
			if (!(t == 1 && o >= 0x1c && o < 0x28) && !(t == 2 && (o < 0x1c || o == 0x28))) S32(r, o) = 0;
	}
}
static void sceneinit_scrub(void) { factor_scrub(BUF + 0x9ccffc); factor_scrub(BUF + 0x9e3020); }
static DWORD sceneinit_orig(void)
{
	TC(void, 0x4700a0, char *, char *, char *, char *, char *, char *, char *, char *, char *, char *)(BUF,
	   (char *)g_a[0], (char *)g_a[1], (char *)g_a[2], (char *)g_a[3], (char *)g_a[4], (char *)g_a[5], (char *)g_a[6], (char *)g_a[7], (char *)(g_a[7] + 0x40));
	g_sceneInitDone++;
	return 0;
}
ST(item_initTextures, sceneinit_setup();, sceneinit_orig(),
   (item_initTextures(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7], (DWORD)(g_a[7] + 0x40)), 0))
