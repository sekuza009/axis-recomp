/* batch 63 */
/* a map file: the version (plain), then descrambled data: a section to skip (size, bytes), a second size, and the
   test's own records; built in plain form, then scrambled after the version */
static BYTE g_mapf[0x4000];
static int map_head(int skips)
{
	BYTE *f = g_mapf; int n = 4;
	*(DWORD *)f = irnd(0, 15) ? 0x1201 : 0x1200;
	for (int k = 0; k < skips; k++) { int s = irnd(0, 40); *(int *)(f + n) = s; n += 4; fill(f + n, s); n += s; }
	*(int *)(f + n) = irnd(0, 100); n += 4;
	return n;
}
static void map_file(int n)
{
	BYTE *d = (BYTE *)(BUF + 0x200000);
	memcpy(d, g_mapf, 4);
	for (int i = 4; i < n; i++) { BYTE b = g_mapf[i]; d[i] = (BYTE)(((b >> 1) | (b << 7)) ^ 0x59); }
	g_vfsData = d; g_vfsSize = (DWORD)n; g_vfsOpenFail = 0;   /* a file that does not open leaves the counts as the stack had them */
	fill_str(BUF + 0x108, 20, 'A', 'Z'); strcpy(BUF + 0x300, "MAP.PLY");
}
/* play records: starts (type 0), multiplayer starts (1, kept within 32), item points (2), other types; the
   game options that remap item kinds */
static void playinfo_setup(void)
{
	int n = map_head(1), cnt = irnd(0, 60), c1 = 0;
	*(int *)(g_mapf + n) = cnt; n += 4;
	for (int i = 0; i < cnt; i++) {
		BYTE *r = g_mapf + n; int t = irnd(0, 9) ? irnd(0, 2) : irnd(3, 5);
		if (t == 1 && c1++ >= 32) t = 0;
		*(int *)r = t; *(int *)(r + 4) = irnd(0, 3) ? irnd(0, 40) : irnd(-15, 60); fill(r + 8, 8);
		for (int k = 0; k < 5; k++) *(float *)(r + 0x10 + 4 * k) = csu_fr(-100000, 100000);
		n += 0x24;
	}
	map_file(n);
	fill(BUF + 0x20fab60, 0x20); for (int k = 0; k < 5; k++) S32(BUF, 0x20f3ac0 + 4 * k) = irnd(0, 2) ? 0 : 1;
	S32(BUF, 0x20fadf4) = irnd(0, 5); S32(BUF, 0x20fcd38) = irnd(0, 5);
}
ST(map_loadPlayInfoFrom, playinfo_setup();, (TC(void, 0x4876b0, char *, char *)(BUF, BUF + 0x300), 0), (map_loadPlayInfoFrom(BUF, (DWORD)(BUF + 0x300)), 0))
/* mission: actions (count, 0x30 each), waypoint lists (count, 0x14 headers with their action counts at +0xc),
   triggers (count, 0x1c records: waypoint count, radius at +0x14); the totals mostly agree */
static void mission_setup(void)
{
	int n = map_head(2), a = irnd(0, 30), w = irnd(0, 6), t = irnd(0, 6), left;
	*(int *)(g_mapf + n) = a; n += 4; fill(g_mapf + n, a * 0x30); n += a * 0x30;
	*(int *)(g_mapf + n) = w; n += 4; left = a;
	for (int i = 0; i < w; i++) {
		BYTE *r = g_mapf + n; fill(r, 0x14);
		int c = i == w - 1 && irnd(0, 4) ? left : irnd(0, left > 0 ? left : 0);
		*(int *)(r + 0xc) = c; left -= c; n += 0x14;
	}
	*(int *)(g_mapf + n) = t; n += 4; left = w;
	for (int i = 0; i < t; i++) {
		BYTE *r = g_mapf + n; fill(r, 0x1c);
		int c = i == t - 1 && irnd(0, 4) ? left : irnd(0, left > 0 ? left : 0);
		*(int *)r = c; left -= c; *(float *)(r + 0x14) = csu_fr(0, 50000); n += 0x1c;
	}
	map_file(n);
	fill(BUF + 0xe36200, 0x20); S32(BUF, 0xe3b034) = irnd(0, 5); S32(BUF, 0xe3c938) = irnd(0, 5);
}
ST(map_loadMissionInfoFrom, mission_setup();, (TC(void, 0x48b5c0, char *, char *)(BUF, BUF + 0x300), 0), (map_loadMissionInfoFrom(BUF, (DWORD)(BUF + 0x300)), 0))
