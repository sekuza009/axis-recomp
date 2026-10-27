/* batch 154 */
/* the loading screen: the game at BUF, hudtext_setup's set (fonts and the cylinder texture bindable), modes 0..4,
   receiving or not, play types 0..7 (the eight mode names), rounds 0..15 with map names, limits, the title and
   status line, the scroll anywhere */
static void loadingscr_setup(void)
{
	hudtext_setup();
	G32(0xa0ea8c) = (int)BUF; G32(0xa0e980) = G32(0x9dae1c);
	S32(BUF, 8) = irnd(0, 4); S32(BUF, 0x1f1cb0) = irnd(0, 3) ? 0 : 1; S32(BUF, 0x22e7180) = irnd(0, 7);
	G32(0x9dad94) = irnd(0, 15);
	for (int k = 0; k < 16; k++) fill_str((char *)0x907b30 + k * 0x20, 12, 33, 126);
	G32(0x4df8e8) = irnd(-5, 999); G32(0x76d408) = irnd(-5, 999);
	fill_str((char *)0x67fb44, 24, 32, 126); fill_str((char *)0xa0e988, 40, 32, 126);
	GF(&g_a[0]) = (float)irnd(-1000, 1000) / 100.0f;
}
T_PLAIN(loading_draw, 0x469320, loadingscr_setup();, 0, g_a[0], 0, 0, 0)
