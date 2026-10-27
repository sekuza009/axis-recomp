/* batch 127 */
/* the info panel: dlgwin_setup's window at 0x9dd368, short labels, the password fields at most 11 characters (the
   '*' buffer, also used for the numbers, holds 20), ratios below a million ("%.2f" goes into it too), counts and
   levels of up to six digits, a clan or none, waiting now and then */
static void roominfo_setup(void)
{
	dlgwin_setup(0x9dd368);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	G32(0x9dd6d4) = irnd(0, 5) ? 0 : 1;
	fill_str((char *)0x75b1a4, 20, 32, 126); fill_str(GSTR(0x74f724), 20, 32, 126);
	fill_str((char *)0x7592a4, 12, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x759324 + k * 0x80, 8, 32, 126);
	for (int k = 0; k < 7; k++) fill_str((char *)0x7595a4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x759924, 8, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7517a4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x9dd1d8, 16, 32, 126); fill_str((char *)0x9dd6d8, 11, 32, 126);
	fill_str((char *)0x9dd1f6, 11, 32, 126); fill_str((char *)0x9dd202, 11, 32, 126); fill_str((char *)0x9dd20e, 16, 32, 126);
	G32(0x9dd69c) = irnd(0, 1); G32(0x9dd37c) = irnd(0, 1); G32(0x9dd378) = irnd(0, 1); G32(0x9dd304) = irnd(0, 1);
	G32(0x9dd5d8) = irnd(0, 3) ? irnd(1, 60) : irnd(-999999, 999999);
	G32(0x9dd248) = irnd(0, 2) ? 0 : irnd(-999999, 999999);
	GF(0x9dd5e4) = (float)irnd(-99999999, 99999999) / 100.0f; GF(0x9dd5f4) = (float)irnd(-99999999, 99999999) / 100.0f;
	G32(0x9dd5ec) = irnd(-999999, 999999); G32(0x9dd5f0) = irnd(-999999, 999999); G32(0x9dd5dc) = irnd(-999999, 999999);
	G32(0x76d448) = G32(0x9db0a4);
}
T_PLAIN(room_43a420, 0x43a420, roominfo_setup();, 0, 0, 0, 0, 0)
