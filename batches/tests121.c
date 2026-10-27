/* batch 120 */
/* the server dialog: dlgwin_setup's window at 0x9dd1a0, its texts, the confirmation open now and then (the cursor
   then sometimes over one of its buttons) */
static void srvdlg_setup(void)
{
	dlgwin_setup(0x9dd1a0);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	fill_str((char *)0x758da4, 40, 32, 126); fill_str((char *)0x758e24, 40, 32, 126); fill_str((char *)0x9dd1d8, 29, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x758f24 + k * 0x80, 30, 32, 126);
	fill_str(GSTR(0x74dfa4), 40, 32, 126); fill_str(GSTR(0x74e024), 40, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 30, 32, 126);
	G32(0x9dd850) = irnd(0, 2) ? 0 : 1;
	if (G32(0x9dd850) && irnd(0, 1)) { G32(0x4ded68) = 0xb4 + irnd(0, 1) * 0xa0 + irnd(0, 0x78); G32(0x4ded6c) = 0x104 + irnd(0, 0x20); }
}
T_PLAIN(room_439e00, 0x439e00, srvdlg_setup();, 0, 0, 0, 0, 0)
/* a skirmish window (0x9f16a8..0x9f16b4) with menutex_setup's set, colours, the cursor sometimes on a button */
static void skwin_setup(void)
{
	int id = menutex_fonts(menutex_setup());
	G32(0x9db0a4) = id;
	G32(0x9f16a8) = irnd(-30, 100); G32(0x9f16ac) = irnd(-30, 100);
	G32(0x9f16b0) = G32(0x9f16a8) + irnd(300, 640); G32(0x9f16b4) = G32(0x9f16ac) + irnd(200, 480);
	fill((void *)0x9ef208, 16); fill((void *)0x9eeac8, 16);
	G32(0x4ded68) = irnd(-50, 700); G32(0x4ded6c) = irnd(-50, 500);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9f16a8) + irnd(0, 640); G32(0x4ded6c) = G32(0x9f16b4) - irnd(0x10, 0x40); }
}
/* the briefing: typewriter_setup's text (positions overwritten by the window), titles and buttons, the briefing
   done or not, a mission or not */
static void briefing_setup(void)
{
	typewriter_setup();
	G32(0x9ef1f4) = irnd(0, 60); memset((void *)0x9f1064, 0, 0x200); fill_str((char *)0x9f1064, 60, 32, 126);   /* the rest of the screen's text needs room in the call log */
	skwin_setup();
	fill_str((char *)0x75e024, 40, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x75e2a4 + k * 0x80, 20, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x75e3a4 + k * 0x80, 20, 32, 126);
	G32(0x9f1060) = irnd(-1, 3);
}
T_PLAIN(skirmish_drawScreenB, 0x4456b0, briefing_setup();, 0, 0, 0, 0, 0)
/* the mission list: 0..14 records with short texts (eight rows of four columns stay inside the call log), the
   first visible one and the selection, kinds 0..4 */
static void missionlist_setup(void)
{
	textpass_setup();
	skwin_setup();
	fill_str((char *)0x75dda4, 12, 32, 126);
	for (int k = 1; k < 6; k++) fill_str((char *)0x75dda4 + k * 0x80, 6, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x75e0a4 + k * 0x80, 16, 32, 126);
	int n = irnd(0, 14); G32(0x9ef2c0) = n; G32(0x9f16bc) = irnd(0, 4); G32(0x9f16a4) = irnd(0, 15);
	for (int k = 0; k < 20; k++) {
		char *r = (char *)0x9ef2d4 + k * 0xfc;
		fill(r, 0xfc);
		fill_str(r, 6, 32, 126); fill_str(r + 0x40, 6, 32, 126); fill_str(r + 0x60, 20, 32, 126);
		S32(r, 0xe0) = irnd(-9999, 9999); S32(r, 0xe8) = irnd(0, 4);
	}
}
T_PLAIN(skirmish_drawScreenA, 0x444f40, missionlist_setup();, 0, 0, 0, 0, 0)
