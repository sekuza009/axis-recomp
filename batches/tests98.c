/* batch 97 */
/* menutex_setup's texture set with the five panels' texture ids (GL slot owners; panel 1 also texture i), the panels' corners,
   offsets, angles (some past +-360) and speeds, the height and depth */
static void panels_setup(void)
{
	int k0 = menutex_setup(), k = k0 - k0 % 512;          /* panel 1: menutex_setup's pick; the others GL slot owners */
	for (int j = 2; j <= 5; j++) {
		char *sl = (char *)S32(BUF, 0xcd134);
		for (int n = irnd(0, 5); n; n--) sl = (char *)S32(sl, 0xc);
		G32(0x9da470 - j * 4) = k + S32(sl, 4);
	}
	G32(0x9da470 - 4) = k0;
	for (int j = 1; j <= 5; j++) {
		float *p = (float *)(0x4dc550 + j * 0x58);
		for (int c = 0; c < 22; c++) p[c] = (float)irnd(-2000, 2000) / 10.0f;
		p[20] = (float)irnd(-4000, 4000) / 10.0f;            /* the angle (+0x50) */
		p[21] = (float)irnd(-100, 100) / 10.0f;              /* its speed (+0x54) */
	}
	GF(0x4dcfc4) = (float)irnd(-500, 500) / 10.0f; GF(0x4dcfc8) = (float)irnd(-500, 500) / 10.0f;
}
ST(armc_41b400, panels_setup();, (CD(void, 0x41b400, void)(), 0), (armc_41b400(0, 0, 0, 0, 0, 0, 0), 0))
