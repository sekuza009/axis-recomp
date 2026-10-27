/* batch 141 */
/* the create-arena screen: gamesettings_setup's approach for the arena (texture set and preview first, through
   mappreview_setup for custom rules, the window at 0x4dbb00 after), the fields in range (map 0..15, kind 0..4,
   mode 0..4, the password at most 9 characters: its '*' buffer holds 10), the editing and box flags, short texts */
static void createarena_setup(void)
{
	textpass_setup();
	if (!irnd(0, 3)) { mappreview_setup(0x4db548); G32(0x680cd0) = 1; *(char *)0x4db54a = (char)irnd(1, 2); }
	else { menutex_setup(); G32(0x680cd0) = 0; *(char *)0x4db54a = irnd(0, 1) ? 0 : (char)irnd(1, 4); *(char *)0x4db548 = (char)irnd(0, 15); }
	menutex_fonts(0);
	int id = G32(0x9dae1c);
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id;
	if (!G32(0x680cd0)) G32(0x9da324) = id;
	G32(0x4dbb00) = irnd(-30, 100); G32(0x4dbb04) = irnd(-30, 80);
	G32(0x4dbb08) = G32(0x4dbb00) + irnd(300, 560); G32(0x4dbb0c) = G32(0x4dbb04) + irnd(300, 420);
	fill((void *)0x4dba98, 16); fill((void *)0x4db8a0, 16);
	fill_str((char *)0x752c24, 12, 32, 126);
	for (int k = 0; k < 8; k++) fill_str((char *)0x752ca4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 4; k++) fill_str((char *)0x7530a4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x753224, 12, 32, 126); fill_str((char *)0x7532a4, 12, 32, 126); fill_str((char *)0x75d8a4, 8, 32, 126);
	fill_str(GSTR(0x74dfa4), 12, 32, 126); fill_str(GSTR(0x74e024), 12, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 5; k++) { fill_str((char *)0x4dbba4 + k * 5, 4, 32, 126); fill_str((char *)0x75c9a4 + k * 0x80, 8, 32, 126); }
	for (int k = 0; k < 16; k++) fill_str((char *)0x5ae9d0 + k * 0x50, 12, 32, 126);
	fill_str((char *)0x4db528, 16, 32, 126); fill_str((char *)0x4db54e, 9, 32, 126);
	*(char *)0x4db549 = (char)irnd(-8, 16); *(char *)0x4db54b = (char)irnd(0, 4);
	*(BYTE *)0x4db54c = (BYTE)irnd(0, 255); *(BYTE *)0x4db54d = (BYTE)irnd(0, 255);
	G32(0x4dbab0) = irnd(0, 1); G32(0x4dbacc) = irnd(0, 1); G32(0x4db850) = irnd(0, 1); G32(0x4db518) = irnd(0, 1);
	G32(0x68039c) = irnd(0, 3) ? 0 : 1; G32(0x4db55c) = irnd(0, 4) ? 0 : 1; G32(0x907b2c) = irnd(0, 4) ? 0 : 1;
	G32(0x4db508) = irnd(0, 4) ? 0 : 1;
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4dbb00) + irnd(0x9f, 0x1a7); G32(0x4ded6c) = G32(0x4dbb04) + irnd(0x2f, 0x133); }
}
T_PLAIN(arena_createDraw, 0x40b750, createarena_setup();, 0, 0, 0, 0, 0)
