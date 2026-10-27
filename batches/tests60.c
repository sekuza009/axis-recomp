/* batch 59 */
T_PLAIN(armc_41b710, 0x41b710, lookat_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_drawDimOverlay, 0x40ce70, GF(0x4deb74) = csu_fr(-50, 120);, 0, 0, 0, 0, 0)
T_PLAIN(room_43df00, 0x43df00, GF(0x4deb74) = csu_fr(-50, 120);, 0, 0, 0, 0, 0)
T_PLAIN(menu_428890, 0x428890, G32(0x9da908) = irnd(0, 45); GF(0x4de1f0) = csu_fr(-10, 100); g_a[0] = irnd(-50, 700); g_a[1] = irnd(-50, 500);, 0, g_a[0], g_a[1], 0, 0)
T_PLAIN(menu_drawFrame, 0x428c30, G32(0x4de740) = irnd(0, 2); for (int i = 0; i < 4; i++) g_a[i] = irnd(-50, 700);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static void dispmode_setup(void)
{
	g_mockDispRet = irnd(0, 2) ? 0 : (DWORD)irnd(-2, 1); g_mockCaps = (DWORD)irnd(0, 64); g_mockPixelFormat = irnd(0, 9);
	G32(0xa0e920) = irnd(0, 1); G32(0xa0e810) = irnd(320, 2560); G32(0xa0e928) = irnd(200, 1600);
	g_a[0] = irnd(320, 2560); g_a[1] = irnd(200, 1600); g_a[2] = irnd(0, 3) ? 32 : irnd(0, 32);
	g_paintStacks = 1;   /* DEVMODE / PIXELFORMATDESCRIPTOR are filled only in part and passed whole */
}
T_PLAIN(glWindow_restoreDisplayMode, 0x468050, dispmode_setup();, 0, 0, 0, 0, 0)
T_PLAIN(glWindow_setDisplayModeBy, 0x467f20, dispmode_setup();, 0, g_a[0], g_a[1], g_a[2], 0)
T_PLAIN(glWindow_setupPixelFormat, 0x467e60, dispmode_setup();, 0, 0xdc0, 0, 0, 0)
T_PLAIN(glWindow_resize, 0x468450, dispmode_setup();, 0, g_a[0], g_a[1], 0, 0)
/* a BMP file: 14-byte file header + 40-byte info header, mostly 24-bit uncompressed; the image object may still
   hold an open file */
static void bmp_setup(void)
{
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = irnd(0, 9) ? 54 + irnd(0, 64) : irnd(0, 54);
	fill(d, 54 + 64); d[0] = 'B'; d[1] = 'M';
	*(WORD *)(d + 28) = irnd(0, 5) ? 24 : (WORD)irnd(0, 32); *(DWORD *)(d + 30) = irnd(0, 5) ? 0 : (DWORD)irnd(1, 3);
	g_vfsData = d; g_vfsSize = (DWORD)n; g_vfsOpenFail = !irnd(0, 6);
	fill(BUF + 0x100, 0x50); S32(BUF + 0x100, 4) = irnd(0, 1) ? (int)VFS_FILE(1) : 0;
	strcpy(BUF + 0x300, "Data\\test.bmp");
}
ST(image_initBy, bmp_setup();, TC(DWORD, 0x46cd00, char *, char *)(BUF + 0x100, BUF + 0x300), image_initBy(BUF + 0x100, (DWORD)(BUF + 0x300)))
/* a dat index file: count (small) and 0x44-byte entries; the index may already be loaded */
static void datinit_setup(DWORD countp, DWORD filep)
{
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = irnd(0, 20);
	*(int *)d = n; fill(d + 4, n * 0x44);
	g_vfsData = d; g_vfsSize = (DWORD)(4 + (irnd(0, 4) ? n * 0x44 : irnd(0, n * 0x44))); g_vfsOpenFail = !irnd(0, 6);
	G32(countp) = irnd(0, 3) ? 0 : irnd(-1, 3); G32(filep) = irnd(0, 3) ? 0 : (int)VFS_FILE(1);
	g_mockMallocFail = !irnd(0, 8);
}
T_PLAIN(shapeDat_initBy, 0x466c00, datinit_setup(0xa0e79c, 0xa0e7a4);, 0, 0, 0, 0, 0)
T_PLAIN(skelDat_initBy, 0x46afe0, datinit_setup(0xa0eab4, 0xa0eabc);, 0, 0, 0, 0, 0)
/* a timer object: initialised or not, counters, a frame-time ring of 10 floats at +0x48 (index +0x70) */
static void gametimer_setup(void)
{
	char *t = BUF + 0x100;
	fill(t, 0x80);
	S32(t, 4) = irnd(0, 1); S32(t, 0x70) = irnd(0, 9);
	for (int i = 0; i < 10; i++) SF(t, 0x48 + i * 4) = csu_fr(0, 100);
	SF(t, 0x34) = irnd(0, 2) ? csu_fr(1, 10) : csu_fr(-5, 0);
	S32(t, 0x10) = irnd(0, 1); S32(t, 0x18) = irnd(0, 1); S32(t, 0x28) = irnd(0, 1);
	qpf_setup(); g_mockQpc = (DWORD)irnd(0, 0x7fffffff);
}
ST(timer_getGameTime, gametimer_setup();, ld_hash(((long double (THISCALL *)(char *))0x487490)(BUF + 0x100)), ld_hash(timer_getGameTime(BUF + 0x100)))
ST(armc_461210, gametimer_setup();, (TC(void, 0x461210, char *)(BUF + 0x100), 0), (armc_461210(BUF + 0x100), 0))
/* the stored time (0x9dd880..) and the mocked system time with small random fields */
static void clock_setup(void)
{
	for (int i = 0; i < 0x34; i++) *(WORD *)(0x9dd880 + i * 2) = (WORD)irnd(0, 59);
	for (int i = 0; i < 8; i++) g_mockTime[i] = (WORD)(i == 0 ? 2026 : irnd(0, 59));
	g_mockTimeMs = (DWORD)irnd(0, 0x7fffffff);
}
T_PLAIN(sys_checkClockTampering, 0x43f300, clock_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_deleteFiles, 0x44ba60, selectload_setup(); g_mockDeleteOk = irnd(0, 1);, 0, 0, 0, 0, 0)
static void charset_setup(void) { netstate_setup(); fill_str((char *)0x9dd1d8, 20, 32, 126); g_mockRegFail = !irnd(0, 4); G32(0x9dd6c4) = irnd(0, 3); fill_str((char *)0x4df9ee, 12, 32, 126); }
T_PLAIN(reg_writeCharacterSettings, 0x432400, charset_setup();, 0, 0, 0, 0, 0)
T_PLAIN(room_433640, 0x433640, charset_setup();, 0, 0, 0, 0, 0)
T_PLAIN(room_43e610, 0x43e610, charset_setup();, 0, 0, 0, 0, 0)
T_PLAIN(gfx_initGLState, 0x42f150, g_a[0] = irnd(0, 2000); g_a[1] = irnd(0, 1500); GF(0x68038c) = csu_fr(100, 12000); GF(0x4e1870) = csu_fr(50, 300);, 0, g_a[0], g_a[1], 0, 0)
/* a texture object (RGBA image at +0x114, size at +0xc0118, mipmap/filter flags) */
static void texobj_setup(void)
{
	char *t = BUF + 0x100000;
	int w = irnd(1, 64), h = irnd(1, 64);
	S32(t, 0xc0118) = w; S32(t, 0xc011c) = h; S32(t, 0xc0120) = irnd(0, 1); S32(t, 0xc0124) = irnd(0, 1);
	fill(t + 0x114, w * h * 4);
	g_a[0] = irnd(1, 500); g_a[1] = irnd(0, 2);
}
ST(tex_upload, texobj_setup();, (TC(void, 0x456520, char *, int, int)(BUF + 0x100000, g_a[0], g_a[1]), 0), (tex_upload(BUF + 0x100000, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
/* eight players' 16 x 24 colour blocks with their changed / uploaded flags */
static void colourblocks_setup(void)
{
	for (int p = 0; p < 8; p++) {
		char *b = SCENE + 0x15a952a + p * 0x47fd2;
		fill(b, 0x600); S32(b, 0x604) = irnd(0, 1); S32(b, 0x608) = irnd(0, 1);
	}
}
ST(tex_upload2, colourblocks_setup();, (TC(void, 0x473610, char *)(SCENE), 0), (tex_upload2(SCENE), 0))
