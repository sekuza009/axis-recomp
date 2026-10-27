/* batch 137 */
/* the settings form: the texture set and the custom option as customopt_setup's (the preview reloaded through
   mappreview_setup for custom rules, else a bindable preview), the window at 0x9dd1b8 after that (the custom option
   draws at the window's own corner), every texture of the set, the fields in range (map 0..15, mode 0..4, the
   password at most 19 characters: its '*' buffer holds 20), the editing / locked flags, the cursor sometimes on a
   value or button */
static void gamesettings_setup(void)
{
	textpass_setup();
	if (!irnd(0, 3)) { mappreview_setup(0x4df9e8); G32(0x680cd0) = 1; *(char *)0x4df9ea = (char)irnd(1, 2); }
	else { menutex_setup(); G32(0x680cd0) = 0; *(char *)0x4df9ea = irnd(0, 1) ? 0 : (char)irnd(1, 2); *(char *)0x4df9e8 = (char)irnd(0, 15); }
	menutex_fonts(0);
	int id = G32(0x9dae1c);
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id;
	if (!G32(0x680cd0)) G32(0x9da324) = id;
	G32(0x9dd1b8) = irnd(-30, 100); G32(0x9dd1bc) = irnd(-30, 80);
	G32(0x9dd1c0) = G32(0x9dd1b8) + irnd(300, 560); G32(0x9dd1c4) = G32(0x9dd1bc) + irnd(300, 420);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	fill_str((char *)0x75a424, 12, 32, 126);
	for (int k = 0; k < 8; k++) fill_str((char *)0x75a4a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x75a8a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x7669a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 16; k++) fill_str((char *)0x5ae9d0 + k * 0x50, 12, 32, 126);
	fill_str(GSTR(0x74e6a4), 8, 32, 126);
	fill_str((char *)0x4df9c8, 16, 32, 126); fill_str((char *)0x4df9ee, 19, 32, 126);
	*(char *)0x4df9e9 = (char)irnd(-8, 16); *(char *)0x4df9eb = (char)irnd(0, 4);
	*(BYTE *)0x4df9ec = (BYTE)irnd(0, 255); *(BYTE *)0x4df9ed = (BYTE)irnd(0, 255);
	G32(0x9dd380) = irnd(0, 1); G32(0x9dd6a8) = irnd(0, 1); G32(0x9dd388) = irnd(0, 1); G32(0x9dd568) = irnd(0, 1);
	G32(0x68039c) = irnd(0, 3) ? 0 : 1; G32(0x907b2c) = irnd(0, 3) ? 0 : 1; G32(0x4db508) = irnd(0, 3) ? 0 : 1;
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9dd1b8) + irnd(0x9f, 0x1a7); G32(0x4ded6c) = G32(0x9dd1bc) + irnd(0x2f, 0x133); }
}
T_PLAIN(room_drawGameSettings, 0x43bfe0, gamesettings_setup();, 0, 0, 0, 0, 0)
