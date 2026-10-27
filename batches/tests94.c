/* batch 93 */
/* menutex_setup's texture set; the HUD object is BUF (its texture fields set to the chosen id), screen positions */
static void hudicon_setup(void)
{
	int t = menutex_setup();
	S32(BUF, 0xbc06b0) = t; S32(BUF, 0x22f86ac) = t; S32(BUF, 0x22f06a8) = irnd(1, 500);
	g_a[0] = irnd(-3, 40); g_a[1] = irnd(-50, 700); g_a[2] = irnd(-50, 500);
}
ST(hud_drawNameIcon, hudicon_setup();, (TC(void, 0x4922c0, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
   (hud_drawNameIcon(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
ST(hud_drawLeaderIcon, hudicon_setup();, (TC(void, 0x4924d0, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
   (hud_drawLeaderIcon(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
ST(replay_drawIcon, hudicon_setup();, (TC(void, 0x496820, char *, int, int, int)(BUF, g_a[1], g_a[2], g_a[0]), 0),
   (replay_drawIcon(BUF, (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[0]), 0))
