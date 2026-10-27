/* batch 60 */
static void hits_setup(void)
{
	int p = irnd(-1, 7);
	S32(SCENE, 0x234240d) = p; S32(SCENE, 0x23423a1) = irnd(0, 1);
	for (int i = 0; i < 8; i++) for (int k = 0; k < 6; k++) S32(SCENE + i * 0x8888, 0x1eccb54 + k * 4) = irnd(0, 500);
	netstate_setup();
}
ST(match_49d150, hits_setup();, (TC(void, 0x49d150, char *)(SCENE), 0), (match_49d150(SCENE), 0))
T_PLAIN(chat_createEdit, 0x43f460, G32(0x9dae74) = irnd(0, 2);, 0, 0x10010, 0, 0, 0)
T_PLAIN(reg_readCharacterSettings, 0x42bee0, g_mockRegFail = !irnd(0, 4); g_paintStacks = 1;, 0, 0, 0, 0, 0)
/* player p's record: name at +4; the emblem BMP (header sizes varied around the 23 x 15 minimum) from the VFS */
static void emblem_setup(void)
{
	g_a[0] = irnd(0, 7);
	char *r = SCENE + 0x1561b68 + g_a[0] * 0x47fd2;
	fill_str(r + 4, 12, 'a', 'z'); fill(r + 0x479c0, 0x620);
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = 54 + 24 * 16 * 3 + irnd(0, 64);
	fill(d, n); d[0] = 'B'; d[1] = 'M'; *(DWORD *)(d + 10) = 54;
	*(int *)(d + 18) = irnd(0, 4) ? irnd(23, 40) : irnd(0, 30); *(int *)(d + 22) = irnd(0, 4) ? irnd(15, 30) : irnd(0, 20);
	*(WORD *)(d + 28) = 24; *(DWORD *)(d + 30) = 0;
	g_vfsData = d; g_vfsSize = (DWORD)n; g_vfsOpenFail = !irnd(0, 5);
	g_paintStacks = 1;
}
ST(gfx_saveScreenshot, emblem_setup();, TC(DWORD, 0x4734d0, char *, int)(SCENE, g_a[0]), gfx_saveScreenshot(SCENE, (DWORD)g_a[0]))
/* the catalogue: version word (plain), then six sections, each a count (0..3) and its records, scrambled like
   every file the descrambling reader reads (stored byte = ror1(b) ^ 0x59) */
static void catalogue_setup(void)
{
	static const int rec[6] = { 0xaa8, 0xabc, 0x1300, 0x13f4, 0x1820, 0x2e18 };
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = 0;
	*(DWORD *)d = irnd(0, 9) ? 0x1204 : 0x1203; n = 4;
	for (int k = 0; k < 6; k++) {
		int c = irnd(0, 3);
		BYTE plain[4]; *(int *)plain = c;
		for (int i = 0; i < 4; i++) { BYTE b = plain[i]; d[n++] = (BYTE)(((b >> 1) | (b << 7)) ^ 0x59); }
		fill(d + n, c * rec[k]); n += c * rec[k];
	}
	g_vfsData = d; g_vfsSize = (DWORD)n; g_vfsOpenFail = !irnd(0, 9);   /* never truncated: a short read leaves a count that the reader then descrambles into a huge one (the original crashes too) */
	strcpy(BUF + 0x300, "Data\\catalogue.dat");
	/* a truncated file leaves a count as it was (fread reads nothing, the reader descrambles the old value):
	   small values there, as in the game, where they are the previous catalogue's */
	static const DWORD cnt[6] = { 0x13eb000, 0x140c8bc, 0x1447ec0, 0x148646c, 0x14d1ab0, 0x1561b64 };
	for (int k = 0; k < 6; k++) S32(SCENE, cnt[k]) = irnd(0, 3);
}
ST(catalogue_loadComponents, catalogue_setup();, TC(DWORD, 0x473780, char *, char *)(SCENE, BUF + 0x300), catalogue_loadComponents(SCENE, (DWORD)(BUF + 0x300)))
