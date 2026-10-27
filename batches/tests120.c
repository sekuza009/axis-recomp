/* batch 119 */
/* the loading screen: menutex_setup's set with a bindable picture, a clear colour, progress 0..28 (16 columns
   each, the three ramps start at 200 and 400 columns; more would overflow the 4096-call log) */
static void loading_setup(void)
{
	textpass_setup();
	G32(0x76d3f0) = menutex_fonts(menutex_setup());
	fill((void *)0x76d350, 16);
	G32(0x4dda34) = irnd(0, 3) ? irnd(0, 28) : irnd(-3, 2);
	G32(0x76d480) = irnd(0, 1) ? 0xdc0 : 0;
}
T_PLAIN(intro_41f100, 0x41f100, loading_setup();, 0, 0, 0, 0, 0)
/* a dialog window (x0, y0, x1, y1 at a), menutex_setup's set as frame / button / border textures, the cursor
   sometimes over a button, the editing flags and colours */
static void dlgwin_setup(DWORD a)
{
	textpass_setup();
	int id = menutex_fonts(menutex_setup());
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id;
	G32(a) = irnd(-50, 300); G32(a + 4) = irnd(-50, 250);
	G32(a + 8) = G32(a) + irnd(0, 450); G32(a + 12) = G32(a + 4) + irnd(0, 330);
	G32(0x4ded68) = irnd(-50, 700); G32(0x4ded6c) = irnd(-50, 500);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(a) + irnd(0x5a, 0x300); G32(0x4ded6c) = G32(a + 12) - irnd(0x20, 0x40); }
	G32(0x68039c) = irnd(0, 1); G32(0x90d1c4) = irnd(0, 5) ? 0 : 1;
}
/* the login dialog: its title, four labels, the field values in their real sizes (the name 30 bytes, the two
   password fields 12 each: the '*' mask buffer holds 30), which fields are being edited */
static void login_setup(void)
{
	dlgwin_setup(0x9dd6e8);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	fill_str((char *)0x7588a4, 40, 32, 126);
	for (int k = 0; k < 4; k++) fill_str((char *)0x758924 + k * 0x80, 30, 32, 126);
	fill_str((char *)0x9dd1d8, 29, 32, 126); fill_str((char *)0x9dd1f6, 11, 32, 126);
	fill_str((char *)0x9dd202, 11, 32, 126); fill_str((char *)0x9dd20e, 20, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 30, 32, 126);
	G32(0x9dd348) = irnd(0, 1); G32(0x9dd3f8) = irnd(0, 1); G32(0x9dd564) = irnd(0, 1); G32(0x9dd6cc) = irnd(0, 1);
}
T_PLAIN(room_4399c0, 0x4399c0, login_setup();, 0, 0, 0, 0, 0)
/* the arena name dialog: title, labels, the name, three buttons, a message open now and then */
static void arenaname_setup(void)
{
	dlgwin_setup(0x4dbb68);
	fill((void *)0x4dba98, 16); fill((void *)0x4db8a0, 16);
	fill_str((char *)0x751fa4, 40, 32, 126); fill_str((char *)0x752024, 30, 32, 126); fill_str((char *)0x752124, 30, 32, 126);
	fill_str((char *)0x4db560, 20, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7521a4 + k * 0x80, 30, 32, 126);
	G32(0x4dbbd0) = irnd(0, 3) ? 0 : 1;
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4dbb68) + irnd(0x40, 0x120); G32(0x4ded6c) = G32(0x4dbb6c) + irnd(0x60, 0xa0); }
}
T_PLAIN(arena_409bc0, 0x409bc0, arenaname_setup();, 0, 0, 0, 0, 0)
