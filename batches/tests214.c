/* batch 213 */
/* the projection switch: the current and wanted modes 0..2, screen sizes 4:3 .. 21:9, the view's angle and depth;
   GL and GLU mocked (the cave's box rewritten by the patch DLL when menu43 is on) */
static void proj2d_setup(void)
{
	static const int w[] = { 640, 1024, 1280, 1920, 2560, 3440 }, h[] = { 480, 768, 1024, 1080, 1440, 1440 };
	int k = irnd(0, 5);
	G32(0x5b1998) = w[k]; G32(0x4e045c) = h[k]; G32(0x5ae9bc) = irnd(-1, 2);
	GF(0x68038c) = csu_fr(1000, 9000); GF(0x4e1870) = csu_fr(1, 500);
	g_a[0] = irnd(0, 2);
}
T_PLAIN(gfx_setProjection2D3D, 0x41ef90, proj2d_setup();, 0, g_a[0], 0, 0, 0)
/* the display mode: the desktop's size, the one asked for equal or not, the changed-mode flag, the mocked
   ChangeDisplaySettingsA's answer; the DEVMODE's unset bytes painted alike */
static void displaymode_setup(void)
{
	static const int w[] = { 640, 800, 1024, 1920 }, h[] = { 480, 600, 768, 1080 };
	int k = irnd(0, 3), j = irnd(0, 1) ? k : irnd(0, 3);
	G32(0x67eefc) = w[k]; G32(0x76d430) = h[k]; *(BYTE *)0xb12a80 = (BYTE)irnd(0, 1); *(BYTE *)0xb12a81 = (BYTE)irnd(0, 1);
	g_mockDispRet = irnd(0, 2) ? 0 : (DWORD)-1;
	g_a[0] = w[j]; g_a[1] = irnd(0, 3) ? h[j] : h[irnd(0, 3)]; g_a[2] = irnd(0, 1) ? 32 : 16; g_a[3] = irnd(0, 2) * 60;
	g_paintStacks = 1;
}
T_PLAIN(FUN_0042eed0, 0x42eed0, displaymode_setup();, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* the start-up: 0x76d410 either way, the checks and the CD load passing mostly (one time in eight not), the class
   registration's answer, the Windows version (old / new), user32 with or without SetProcessDPIAware, the screen
   size; every callee stubbed, the window calls mocked */
static const DWORD g_stubAppInit[] = { 0x41e550, 0, 0x41e5b0, 0, 0x41e610, 0, 0x41e670, 0, 0x41e6d0, 0, 0x41edf0, 1,
	0x42b3e0, 0, 0x42eca0, 0, 0x42eed0, 4, 0x42ef30, 1, 0x42fd40, 0, 0x430400, 1, 0x43f300, 0, 0x43f580, 0, 0x43f5a0, 0,
	0x43f640, 0, 0x43f840, 1, 0 };
static void appinit_setup(void)
{
	callee_stubs(g_stubAppInit, 0);
	static const DWORD chk[] = { 0x41e550, 0x41e5b0, 0x41e610, 0x41e670, 0x41e6d0, 0x430400, 0x43f840 };
	for (int i = 0; i < 7; i++) callee_ret(chk[i], irnd(0, 7) ? 1 : 0);
	callee_ret(0x42eed0, (DWORD)irnd(0, 2));
	G32(0x76d410) = irnd(0, 1); G32(0x83a9c4) = irnd(0, 3);
	g_mockModFail = !irnd(0, 4); g_mockProcFail = !irnd(0, 4);
	static const DWORD ver[] = { 0x0a280105, 0x80000004, 0x00000a04, 0xc0000a04 };
	g_mockVersion = ver[irnd(0, 3)];
	g_mockAtom = irnd(0, 3) ? 0xc001 : 0;
	g_a[0] = 0x400000; g_a[1] = irnd(0, 10);
}
T_PLAIN(app_init, 0x43fcc0, appinit_setup();, 0, g_a[0], g_a[1], 0, 0)
