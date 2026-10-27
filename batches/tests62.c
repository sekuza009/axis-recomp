/* batch 61 */
/* pool sizes small; memory either allocated (mock heap) or given (scratch, sometimes too small: fatal) */
static void spaceinit_setup(void)
{
	fill(BUF + 0x100, 0x100);
	for (int i = 0; i < 5; i++) g_a[i] = irnd(0, 3) ? irnd(0, 24) : irnd(0, 2);   /* negative counts make the original fill ~2^31 entries */
	g_a[5] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[6] = irnd(0, 4) ? 0x40000 : irnd(0, 0x800);
	g_mockMallocFail = !irnd(0, 8);
}
ST(space_initBy, spaceinit_setup();,
   (TC(void, 0x4813e0, char *, int, int, int, int, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6]), 0),
   (space_initBy(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6]), 0))
/* a space object made by the original space_initBy (reserved memory, so the mock heap is not used before the run) */
static void space_make(char *sp)
{
	fill(sp, 0x100);
	((void (THISCALL *)(char *, int, int, int, int, int, int, int))0x4813e0)(sp, irnd(1, 16), irnd(1, 16), irnd(1, 16), irnd(1, 16), irnd(1, 64),
	                                                                        (int)(BUF + 0x400000), 0x40000);
}
static void spaceset_setup(void)
{
	space_make(BUF + 0x100);
	for (int i = 0; i < 6; i++) SF(BUF + 0x80, i * 4) = csu_fr(-100000, 100000);
	g_a[0] = irnd(0, 9) ? irnd(1, 4) : irnd(-1, 0); g_a[1] = irnd(1, 4); g_a[2] = irnd(1, 4);
	g_a[3] = irnd(0, 9) ? irnd(0, 8) : irnd(9, 12);
}
ST(space_setBy, spaceset_setup();,
   (TC(void, 0x4819b0, char *, char *, char *, int, int, int, int, int, int)(BUF + 0x100, BUF + 0x80, BUF + 0x8c, g_a[0], g_a[1], g_a[2], 7, 9, g_a[3]), 0),
   (space_setBy(BUF + 0x100, (DWORD)(BUF + 0x80), (DWORD)(BUF + 0x8c), (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], 7, 9, (DWORD)g_a[3]), 0))
/* the scene at the scratch area: its level grid (+0xa10) a fresh space object, bounds at +0x9ef904 / +0x9ef910 */
static void levelgrid_setup(void)
{
	space_make(BUF + 0xa10);
	for (int i = 0; i < 6; i++) SF(BUF + 0x9ef904, i * 4) = csu_fr(-100000, 100000);
}
ST(load_471010, levelgrid_setup();, (TC(void, 0x471010, char *)(BUF), 0), (load_471010(BUF), 0))
/* a view volume's pool part (BUF + 0x100000) with small pool sizes */
static void factorinit_setup(void)
{
	fill(BUF + 0x100000, 0x9100); S32(BUF + 0x100000, 0xc) = irnd(0, 1); S32(BUF + 0x100000, 8) = (int)(BUF + 0x3000);
	for (int i = 0; i < 6; i++) g_a[i] = irnd(0, 3) ? irnd(0, 40) : irnd(0, 2);
	g_a[6] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[7] = irnd(0, 4) ? 0x40000 : irnd(0, 0x400);
	g_mockGlExt = (DWORD)irnd(0, 2); g_mockMallocFail = !irnd(0, 8);
}
ST(factor_initBy, factorinit_setup();,
   (TC(void, 0x484050, char *, int, int, int, int, int, int, int, int)(BUF + 0x100000, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]), 0),
   (factor_initBy(BUF + 0x100000, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7]), 0))
/* six texture objects (only their size fields at +0xc0118 matter), mostly the expected sizes, sometimes absent or wrong */
static void texsmall_setup(void)
{
	static const int w[6] = { 64, 128, 256, 128, 256, 256 }, h[6] = { 64, 64, 64, 128, 128, 256 };
	fill(BUF + 0x100, 0x40);
	for (int k = 0; k < 6; k++) {
		char *t = BUF + 0x13fee8 + k * 0x100;
		S32(t, 0xc0118) = irnd(0, 9) ? w[k] : irnd(0, 300); S32(t, 0xc011c) = irnd(0, 9) ? h[k] : irnd(0, 300);
		g_a[k] = irnd(0, 5) ? (int)t : 0;
	}
}
ST(texSmall_initBy, texsmall_setup();,
   (TC(void, 0x4569d0, char *, int, int, int, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5]), 0),
   (texSmall_initBy(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5]), 0))
/* an animation file: header (size +4 = what the tracks and keys need, count +0x10), tracks with their key counts */
static void anim_setup(void)
{
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = 0x24, cnt = irnd(0, 5), size = 0;
	fill(d, 0x24);
	int keys[5][2];
	for (int t = 0; t < cnt; t++) { keys[t][0] = irnd(0, 4); keys[t][1] = irnd(0, 4); size += 0x70 + keys[t][0] * 0x20 + keys[t][1] * 0x28; }
	*(int *)(d + 4) = irnd(0, 9) ? size : size + irnd(-0x40, 0x40); *(int *)(d + 0x10) = cnt;
	for (int t = 0; t < cnt; t++) { fill(d + n, 0x70); *(int *)(d + n + 0x60) = keys[t][0]; *(int *)(d + n + 0x68) = keys[t][1]; n += 0x70; }
	for (int t = 0; t < cnt; t++) { int k = keys[t][0] * 0x20 + keys[t][1] * 0x28; fill(d + n, k); n += k; }
	g_vfsData = d; g_vfsSize = (DWORD)n; g_vfsOpenFail = 0;
	fill(BUF + 0x100, 0x40); S32(BUF + 0x100, 0xc) = 0;
	g_a[0] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[1] = irnd(0, 4) ? 0x40000 : irnd(0, 0x100);
	g_mockMallocFail = !irnd(0, 8);
}
ST(skel_loadFrom_46aa10, anim_setup();, (TC(void, 0x46aa10, char *, int, int, int)(BUF + 0x100, (int)VFS_FILE(0), g_a[0], g_a[1]), 0),
   (skel_loadFrom_46aa10(BUF + 0x100, VFS_FILE(0), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
