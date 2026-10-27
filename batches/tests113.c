/* batch 112 */
/* window messages: create, destroy, size, paint, close and others (passed on), with a context and DC or none; the
   pixel format found or not */
static void wndproc_setup(void)
{
	static const DWORD msgs[] = { 1, 2, 5, 0xf, 0x10, 0x100, 0x200, 0x0006, 0x0014 };
	g_a[0] = 0x1234 + irnd(0, 3); g_a[1] = (int)msgs[irnd(0, 8)]; g_a[2] = irnd(0, 0xffff);
	g_a[3] = irnd(1, 2000) | irnd(1, 1500) << 16;
	G32(0xa0e938) = irnd(0, 3) ? 0xdc0 : 0; G32(0xa0e93c) = irnd(0, 3) ? 0x6c0 : 0;
	g_mockPixelFormat = irnd(0, 4) ? 7 : 0; g_mockGlrc = irnd(0, 4) ? 0x6c0 : 0;
	fill((void *)0xa0e930, 4);
}
ST(glWindow_wndProc, wndproc_setup();, ((DWORD (WINAPI *)(DWORD, DWORD, DWORD, DWORD))0x4680d0)(g_a[0], g_a[1], g_a[2], g_a[3]),
   glWindow_wndProc(g_a[0], g_a[1], g_a[2], g_a[3]))
/* the window: a title, sizes, depth, full screen or not, a parent or none; initialised already now and then;
   RegisterClassA failing now and then */
static void glwinit_setup(void)
{
	char *t = BUF + 0x300; fill_str(t, 20, 'A', 'z');
	G32(0xa0e930) = irnd(0, 9) ? 0 : 1; g_mockAtom = irnd(0, 9) ? 0xc001 : 0;
	g_a[0] = (int)t; g_a[1] = irnd(320, 1920); g_a[2] = irnd(200, 1200); g_a[3] = irnd(0, 2) ? 32 : 16;
	g_a[4] = irnd(0, 3); g_a[5] = irnd(0, 1); g_a[6] = irnd(0, 2) ? 0 : 0x5678; g_a[7] = irnd(0, 3) ? 0 : 1;
	fill((void *)0xa0e81c, 0x40); fill((void *)0xa0e918, 0x14);
	g_mockPixelFormat = irnd(0, 4) ? 7 : 0;
}
ST(glWindow_init, glwinit_setup();, CD(DWORD, 0x468250, char *, int, int, int, int, int, int, int)((char *)g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   glWindow_init(0, 0, 0, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7]))
