/* batch 118 */
/* a dialog: menutex_setup's set (fonts bindable), its texture as frame, button and border, a window rectangle at
   (xo, yo) .. (xe, ye), the cursor sometimes over a button, colours, titles and the two button labels; the new
   profile name empty now and then */
static void profdlg_setup(DWORD xo, DWORD yo, DWORD xe, DWORD ye)
{
	textpass_setup();
	int id = menutex_fonts(menutex_setup());
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id;
	G32(xo) = irnd(-50, 300); G32(yo) = irnd(-50, 250);
	G32(xe) = G32(xo) + irnd(0, 400); G32(ye) = G32(yo) + irnd(0, 300);
	int b = irnd(0, 2);
	G32(0x4ded68) = irnd(0, 2) ? G32(xo) + 0x6e + b * 0x78 + irnd(0, 0x60) : irnd(-50, 700);
	G32(0x4ded6c) = irnd(0, 2) ? G32(yo) + 0x3c + irnd(0, 0x40) : irnd(-50, 500);
	fill((void *)0x9f8eb0, 16); fill((void *)0x9f8d58, 16);
	for (DWORD s = 0x751ca4; s <= 0x751e24; s += 0x80) fill_str((char *)s, 50, 32, 126);
	fill_str((char *)0x7517a4, 30, 32, 126); fill_str((char *)0x751824, 30, 32, 126);
	if (irnd(0, 2)) fill_str((char *)0x9dc92c, 20, 32, 126); else *(char *)0x9dc92c = 0;
}
T_PLAIN(profile_44e180, 0x44e180, profdlg_setup(0x9f8f1c, 0x9f8f0c, 0x9f8f2c, 0x9f8f28);, 0, 0, 0, 0, 0)
T_PLAIN(profile_44e3e0, 0x44e3e0, profdlg_setup(0x9f6834, 0x9f683c, 0x9f93bc, 0x9f93c0);, 0, 0, 0, 0, 0)
T_PLAIN(profile_44de00, 0x44de00, profdlg_setup(0x9f8eac, 0x9f8ea8, 0x9f8f20, 0x9f8f24);, 0, 0, 0, 0, 0)
/* the weight line: ten part weights and a limit (whole and fractional, below a million: "%.0f" goes into 20
   bytes), the language, the label */
static void weight_setup(void)
{
	textpass_setup();
	static const DWORD w[] = { 0x4dc14c, 0x4dc0cc, 0x4dc04c, 0x4dbfcc, 0x4dbf4c, 0x4dbecc, 0x4dcea0, 0x4dc240, 0x4dc2a4, 0x4dcf0c };
	for (int k = 0; k < 10; k++) GF(w[k]) = (float)irnd(0, 50000) / (irnd(0, 1) ? 1.0f : 10.0f);
	GF(0x4dcb0c) = (float)irnd(0, 300000) / (irnd(0, 1) ? 1.0f : 7.0f);
	G32(0x9dae74) = irnd(0, 2); G32(0x4dcc94) = irnd(-50, 400);
	fill_str((char *)0x7573a4, 30, 32, 126);
}
T_PLAIN(armc_41dab0, 0x41dab0, weight_setup();, 0, 0, 0, 0, 0)
