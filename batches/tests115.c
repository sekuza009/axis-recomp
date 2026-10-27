/* batch 114 */
/* the profile checks skipped or passing (a failing one exits), the window set up fresh or already (message), a
   direct start or not, the round's console file present or not (console_loadFile's content), start modes 0..4,
   the selections at their limits now and then; the game object at BUF as app_requireCd's test sets it up */
static void consoleinit_setup(void)
{
	session_setup(); clock_setup(); rects3_setup();
	G32(0x9087b4) = (int)BUF;
	G32(0x67fb3c) = 0; G32(0x76d410) = irnd(0, 1);
	G32(0x4e045c) = irnd(320, 1920); G32(0x5b1998) = irnd(200, 1200); G32(0x83a9c4) = irnd(0, 1) ? 16 : 32;
	G32(0x76d480) = irnd(0, 3) ? 0 : 1; G32(0x4ded18) = irnd(0, 2) ? 0 : 0x5678;
	G32(0xa0e930) = irnd(0, 9) ? 0 : 1; fill((void *)0xa0e81c, 0x40); g_mockPixelFormat = 7;
	G32(0x9db990) = irnd(0, 4) ? 0 : 1;
	G32(0x9dad94) = irnd(0, 7); G32(0x5ae9c4) = irnd(0, 4);
	static const DWORD sel[] = { 0x4dc878, 0x4dc87c, 0x4dc880, 0x4dc884, 0x4dc888 };
	static const int lim[] = { 0x13, 0xd, 0x11, 0x13, 0xf };
	for (int k = 0; k < 5; k++) G32(sel[k]) = irnd(0, 1) ? lim[k] : irnd(0, lim[k]);
	for (int k = 0; k < 8; k++) fill_str((char *)0x907b30 + k * 0x20, irnd(0, 30), 32, 126);
	fill((void *)0x4dedb0, 0x48); fill_str((char *)0x4dedb0, irnd(0, 30), 32, 126);
	fill((void *)0x4df81c, 0x50);
	for (int k = 0; k <= 10; k++) fill_str(GSTR(0x74de24 + k * 0x80), 60, 32, 126);
	vfs_content(irnd(0, 1) ? 90 : 0, 0x2000);
	/* a failed open in the profile checks would exit: files fail only when they are skipped, or after them */
	g_vfsFailMask = irnd(0, 2) ? 0 : 1u << irnd(G32(0x76d410) ? 0 : 5, 8);
	g_paintStacks = 1;
}
ST(console_init, consoleinit_setup();, (CD(void, 0x41fd40, void)(), 0), (console_init(0, 0, 0, 0, 0, 0, 0), 0))
