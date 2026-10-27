/* batch 138 */
/* the colour editor: menutex_setup's set (fonts and the slider texture), panel positions, slots 0..5, every slot's
   colours (hues -360..720 degrees, the rest -1..2 so the caps at 99 and the 180 wrap both show), the part names on
   or off, short labels */
static void colour_setup(void)
{
	textpass_setup();
	G32(0x9db0a4) = menutex_fonts(menutex_setup());
	G32(0x4dcc98) = irnd(200, 640); G32(0x4dcc94) = irnd(-30, 100); G32(0x4dcc90) = irnd(-30, 300); G32(0x4dcc9c) = irnd(-30, 300);
	fill((void *)0x4dbc58, 16); fill((void *)0x4dc1d0, 16);
	G32(0x4dc4b0) = irnd(0, 5); G32(0x4dbc68) = irnd(0, 1); G32(0x4dceac) = irnd(-1, 6);
	for (int k = 0; k < 6; k++) {
		GF(0x4dc4b8 + k * 0x18) = (float)irnd(-3600, 7200) / 10.0f; GF(0x4dc4c4 + k * 0x18) = (float)irnd(-3600, 7200) / 10.0f;
		GF(0x4dc4bc + k * 0x18) = (float)irnd(-100, 200) / 100.0f; GF(0x4dc4c0 + k * 0x18) = (float)irnd(-100, 200) / 100.0f;
		GF(0x4dc4c8 + k * 0x18) = (float)irnd(-200, 100) / 100.0f; GF(0x4dc4cc + k * 0x18) = (float)irnd(-200, 100) / 100.0f;
	}
	fill_str((char *)0x75d3a4, 10, 32, 126); fill_str((char *)0x75d424, 10, 32, 126);
	for (int k = 0; k < 3; k++) fill_str((char *)0x75d4a4 + k * 0x20, 8, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x756aa4 + k * 0x80, 8, 32, 126);
	fill_str((char *)0x756d24, 8, 32, 126);
	static const DWORD nm[] = { 0x4dceb8, 0x4dbc08, 0x4dc250, 0x4dc1e8, 0x4dce40 };
	for (int k = 0; k < 5; k++) fill_str((char *)nm[k], 10, 32, 126);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
}
T_PLAIN(armc_41a280, 0x41a280, colour_setup();, 0, 0, 0, 0, 0)
