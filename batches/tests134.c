/* batch 133 */
/* the mission-select screen: missions 0..15; the preview looked up now and then (mappreview_setup's indexed map
   name, sometimes left out: fatal) or already bindable; every texture of the set (menutex_fonts after the set is
   built); the records' counts 0..8 with portraits in range for the allies (no check there) and sometimes out of
   range for the enemies; kinds 0..4; values zero now and then; short texts (the title goes into 128 bytes, the
   preview path into 64) */
static void missionscreen_setup(void)
{
	textpass_setup();
	int m = irnd(0, 15);
	G32(0x9f63b0) = irnd(0, 3) ? 0 : 1;
	if (G32(0x9f63b0)) { G32(0x9f63b4) = 0; mappreview_setup(0x9f63b4); m = G32(0x9f63b4); }
	else menutex_setup();
	menutex_fonts(0);
	int id = G32(0x9dae1c);
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id; G32(0x4dfa00) = id;
	if (!G32(0x9f63b0)) { G32(0x9da324) = id; for (int k = 0; k < 16; k++) fill_str((char *)0x907b30 + k * 0x20, 10, 'A', 'z'); }
	G32(0x9f63b4) = m;
	G32(0x9f6308) = irnd(-30, 100); G32(0x9f630c) = irnd(-30, 80);
	G32(0x9f6310) = G32(0x9f6308) + irnd(300, 560); G32(0x9f6314) = G32(0x9f630c) + irnd(300, 420);
	fill((void *)0x9f6318, 16); fill((void *)0x9f62e8, 16);
	fill_str((char *)0x75f1a4, 20, 32, 126);
	fill_str((char *)0x75f2a4, 8, 32, 126); fill_str((char *)0x75f324, 8, 32, 126); fill_str((char *)0x75f3a4, 8, 32, 126);
	fill_str((char *)0x75f524, 10, 32, 126); fill_str((char *)0x75f5a4, 10, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x75f6a4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x75f7a4, 20, 32, 126); fill_str(GSTR(0x74de24), 20, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x75c9a4 + k * 0x80, 8, 32, 126);
	for (DWORD s = 0x75bfa4; s <= 0x75c124; s += 0x80) fill_str((char *)s, 8, 32, 126);
	for (int k = 0; k < 16; k++) {
		char *r = (char *)0x9db99c + k * 0x5c;
		fill(r, 0x5c);
		S32(r, 0) = irnd(0, 8); S32(r, 0x24) = irnd(0, 8);
		for (int i = 0; i < 8; i++) { S32(r, 4 + i * 4) = irnd(0, 9) ? irnd(0, 8) : irnd(-3, 12); S32(r, 0x28 + i * 4) = irnd(0, 8); }
		S32(r, 0x48) = irnd(0, 4); S32(r, 0x4c) = irnd(0, 3) ? irnd(1, 99999) : 0; S32(r, 0x50) = irnd(0, 3) ? irnd(1, 99999) : 0;
	}
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	g_paintStacks = 1;
}
T_PLAIN(missionsel_drawScreen, 0x449a50, missionscreen_setup();, 0, 0, 0, 0, 0)
