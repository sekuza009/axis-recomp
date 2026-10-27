/* batch 198 */
/* the help screen: 30 short lines; the quad and the text drawing stubbed (the screen size getters real) */
static const DWORD g_stubHelp[] = { 0x46bd60, 3, 0x44ad30, 4, 0x44ad60, 4, 0 };
static void help_setup(void)
{
	callee_stubs(g_stubHelp, 0);
	for (int i = 0; i < 30; i++) fill_str(BUF + 0x234334b + i * 0x40, 20, ' ', 'z');
}
ST(hud_4955a0, help_setup();, (TC(void, 0x4955a0, char *)(BUF), 0), (hud_4955a0(BUF), 0))
/* the loading cylinder: mode -2, -1, 1 or another, a short text, the progress so far; the timer real (the
   performance counter mock moves on each call, so the fades end), the screen, quad, swap and texture lookup stubbed */
static const DWORD g_stubCyl[] = { 0x469320, 1, 0x4685d0, 0, 0x46bd60, 4, 0x456be0, 8 | CS_POP | CS_THIS, 0 };
static void cyl_setup(void)
{
	callee_stubs(g_stubCyl, 0);
	callee_ret(0x456be0, (DWORD)irnd(0, 1000));
	static const int modes[] = { -2, -1, 0, 1, 2, 7 };
	g_a[0] = modes[irnd(0, 5)]; g_a[1] = irnd(0, 100);
	fill_str(BUF + 0x100, 40, ' ', 'z'); g_a[2] = (int)(BUF + 0x100);
	GF(0xa0ea88) = (float)irnd(0, 100) / 100.0f;
}
T_PLAIN(loading_drawCylinder, 0x469730, cyl_setup();, 0, g_a[0], g_a[1], g_a[2], 0)
