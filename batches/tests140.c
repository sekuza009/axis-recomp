/* batch 139 */
/* the build screen: menutex_setup's set (every texture it binds from it), positions, the selected slot, slot names
   empty / one character / short, the part box's indexes in range, the stats panel in its three states with values
   below a million ("%.0f" / "%.1f" into 56 bytes, " +%d" into 20), the pilot 0..8, the string-table indexes in range, short texts.
   The snapshot (0x4dcc64) is left off: armc_snapshot's own test covers it */
static void armcbuild_setup(void)
{
	pilotpanel_setup();
	int id = G32(0x9db0a4);
	G32(0x4dcc88) = id; for (int k = 0; k < 6; k++) G32(0x4dcc70 + k * 4) = id;
	G32(0x4dcc64) = 0;
	G32(0x4dcc90) = irnd(-30, 200); G32(0x4dcc94) = irnd(-30, 60); G32(0x4dcc98) = irnd(300, 640); G32(0x4dcc9c) = irnd(300, 480);
	fill((void *)0x4dbc58, 16); fill((void *)0x4dc1d0, 16);
	G32(0x4dbe48) = irnd(-1, 6); G32(0x9dae74) = irnd(0, 2);
	for (int k = 0; k < 6; k++) { char *s = (char *)0x4dbe50 + k * 0x80; int c = irnd(0, 3); if (c == 0) s[0] = 0; else if (c == 1) { s[0] = 'X'; s[1] = 0; } else fill_str(s, 8, 33, 126); }
	fill_str((char *)0x4dc150, 10, 32, 126);
	G32(0x4dc77c) = irnd(0, 5);
	for (int k = 0; k < 6; k++) { G32(0x4dc79c + k * 4) = irnd(0, 4); G32(0x4dcca4 + k * 4) = irnd(0, 4); }
	for (int k = 0; k < 5; k++) fill_str((char *)0x7641a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 6; k++) fill_str((char *)0x756fa4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x757da4, 8, 32, 126); fill_str((char *)0x757e24, 8, 32, 126);
	fill_str((char *)0x765fa4, 8, 32, 126);
	for (int k = 0; k < 16; k++) fill_str((char *)0x7574a4 + k * 0x80, 6, 32, 126);
	for (DWORD s = 0x765624; s <= 0x7657a4; s += 0x80) fill_str((char *)s, 3, 32, 126);
	for (int k = 0; k < 6; k++) fill_str((char *)0x7652a4 + k * 0x80, 8, 32, 126);
	int st = irnd(0, 5);
	/* 0x4dc190 / 0x4dc194 / 0x4dc1a0 index string tables (0x757ea4: 2, 0x757fa4: 4, 0x7581a4: 4 entries) */
	G32(0x4dc190) = st == 0 ? -1 : irnd(0, 1); G32(0x4dc194) = st == 1 ? -1 : irnd(0, 3);
	for (int k = 0; k < 2; k++) fill_str((char *)0x757ea4 + k * 0x80, 6, 32, 126);
	for (int k = 0; k < 4; k++) { fill_str((char *)0x757fa4 + k * 0x80, 6, 32, 126); fill_str((char *)0x7581a4 + k * 0x80, 6, 32, 126); }
	fill_str((char *)0x765824, 3, 32, 126); fill_str((char *)0x765924, 3, 32, 126);
	G32(0x4dc198) = irnd(0, 5); G32(0x9f1818) = irnd(0, 8);
	for (DWORD a = 0x4dc19c; a <= 0x4dc1cc; a += 4) {
		if (a == 0x4dc1a0) G32(a) = irnd(0, 3);
		else if (a == 0x4dc19c || a == 0x4dc1a4 || a == 0x4dc1bc) G32(a) = irnd(-9999, 99999);
		else GF(a) = (float)irnd(-9999999, 9999999) / 10.0f;
	}
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
}
T_PLAIN(armc_419160, 0x419160, armcbuild_setup();, 0, 0, 0, 0, 0)
