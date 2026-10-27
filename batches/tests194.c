/* batch 193 */
/* the objects' frame loop: 0..40 objects in use or not, paused or not, dt; the per-object frame stubbed (thiscall,
   ret 8) */
static const DWORD g_stubObjLoop[] = { 0x490440, 2 | CS_POP | CS_THIS, 0 };
static void objloop_setup(void)
{
	callee_stubs(g_stubObjLoop, 0);
	int n = irnd(-1, 40);
	S32(BUF, 0x13c9b24) = n;
	for (int i = 0; i < n; i++) S32(BUF, 0x131ae48 + i * 0x2cc) = irnd(0, 2);
	S32(BUF, 0x2149308) = irnd(0, 1); S32(BUF, 0x214930c) = irnd(0, 2);
	GF(&g_a[0]) = (float)irnd(1, 100) / 1000.0f;
}
ST(match_490d40, objloop_setup();, (TC(void, 0x490d40, char *, int)(BUF, g_a[0]), 0), (match_490d40(BUF, (DWORD)g_a[0]), 0))
/* the followed player's name: -1 (none) or a player 0..15 with a short name; the text drawn for real */
static void followname_setup(void)
{
	int i = irnd(-1, 15);
	S32(BUF, 0x2340c64) = i;
	for (int k = 0; k < 16; k++) fill_str(BUF + 0x1eccb08 + k * 0x888, 12, 'A', 'z');
}
ST(replay_drawFollowedName, followname_setup();, (TC(void, 0x496b80, char *)(BUF), 0), (replay_drawFollowedName(BUF), 0))
/* the sound table file: sound on or off, a volume, a file of 0..6 entries (index 0..40, a short name, the rest of
   the 0x100 bytes random) ended by a negative index, stored scrambled as the reader descrambles it (byte = rol(x ^
   0x59, 1)); the loader, the table free, the volume and the error message stubbed */
static const DWORD g_stubSndTab[] = { 0x456cd0, 0, 0x456de0, 1, 0x467b90, 1, 0x46c710, 3, 0 };
static void sndtab_setup(void)
{
	callee_stubs(g_stubSndTab, 0x5000);
	G32(0xa0e80c) = irnd(0, 4) ? 1 : 0;
	for (int k = 0; k < 0x80; k++) G32(0xa0e02c + 4 * k) = irnd(0, 1000);
	BYTE *d = (BYTE *)BUF + 0x10000;
	int n = irnd(0, 6), p = 0;
	for (int i = 0; i < n; i++) {
		S32(d, p) = irnd(0, 40); p += 4;
		for (int k = 0; k < 0x100; k++) d[p + k] = (BYTE)irnd(0, 255);
		fill_str((char *)d + p, 16, 'a', 'z'); p += 0x100;
	}
	S32(d, p) = -irnd(1, 5); p += 4;
	for (int k = 0; k < p; k++) { BYTE x = d[k]; d[k] = (BYTE)((x >> 1 | x << 7) ^ 0x59); }
	g_vfsData = d; g_vfsSize = (DWORD)p;
	fill_str(BUF + 0x100, 20, 'a', 'z');
	g_a[0] = (int)(BUF + 0x100); g_a[1] = irnd(-10, 120);
}
T_PLAIN(sound_initSoundTable, 0x456d10, sndtab_setup();, 0, g_a[0], g_a[1], 0, 0)
