/* batch 122 */
/* the room login dialog: dlgwin_setup's window at 0x9dd358, short texts, the editing / connecting / confirmation
   flags */
static void roomlogin_setup(void)
{
	dlgwin_setup(0x9dd358);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	fill_str((char *)0x7583a4, 20, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x758424 + k * 0x80, 12, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x758524 + k * 0x80, 12, 32, 126);
	fill_str((char *)0x9dd1d8, 20, 32, 126); fill_str((char *)0x9dd1f6, 11, 32, 126);
	fill_str(GSTR(0x74f6a4), 30, 32, 126); fill_str(GSTR(0x74f724), 30, 32, 126);
	fill_str(GSTR(0x74dfa4), 30, 32, 126); fill_str(GSTR(0x74e024), 30, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 12, 32, 126);
	G32(0x9dd830) = irnd(0, 1); G32(0x9dd38c) = irnd(0, 1);
	G32(0x9dd838) = irnd(0, 3) ? 0 : 1; G32(0x9dd850) = irnd(0, 3) ? 0 : 1;
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9dd358) + irnd(0x30, 0x1e8); G32(0x4ded6c) = G32(0x9dd364) - irnd(0x20, 0x40); }
}
T_PLAIN(room_4392c0, 0x4392c0, roomlogin_setup();, 0, 0, 0, 0, 0)
/* the pilot panel: menutex_setup's set as portrait and bar textures, 0..6 profiles (the selected one's pilot
   0..8: the portrait atlas is 3 x 3), nine pilots with short names and titles, classes 0..4, stats with one to
   four digits and a sign now and then, the bars' current and target values, focused or not */
static void pilotpanel_setup(void)
{
	textpass_setup();
	int id = menutex_fonts(menutex_setup());
	G32(0x9db0a4) = id; G32(0x4dfa00) = id;
	G32(0x9f9008) = irnd(0, 4) ? irnd(1, 6) : 0; G32(0x9f8d74) = irnd(0, 5); G32(0x9f8f10) = irnd(0, 2);
	G32(0x9f8e48) = irnd(-50, 200); G32(0x9f8e4c) = irnd(-50, 200);
	fill((void *)0x9f8eb0, 16);
	for (int k = 0; k < 8; k++) S32((char *)0x9f684c + k * 0x48, 0x40) = irnd(0, 8);
	for (int k = 0; k < 13; k++) fill_str((char *)0x75e824 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x75eea4 + k * 0x80, 8, 32, 126);
	for (int p = 0; p < 9; p++) {
		char *r = (char *)0x9f9040 + p * 0x4c;
		fill(r, 0x4c);
		fill_str(r, 12, 32, 126); fill_str(r + 0x10, 12, 32, 126);
		S32(r, 0x20) = irnd(0, 4); S32(r, 0x24) = irnd(0, 99);
		for (int s = 0; s < 9; s++) S32(r, 0x28 + s * 4) = irnd(0, 3) ? irnd(0, 999) : irnd(-99, 9999);
	}
	for (int s = 0; s < 9; s++) { GF(0x9f8d34 + s * 4) = (float)irnd(0, 1000) / 10.0f; GF(0x9f8ec0 + s * 4) = (float)irnd(0, 1000) / 10.0f; }
}
T_PLAIN(profile_44cf70, 0x44cf70, pilotpanel_setup();, 0, 0, 0, 0, 0)
