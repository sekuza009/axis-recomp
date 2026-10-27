/* batch 105 */
/* 1..4 tunnel rings (0x4000 apart from BUF + 0x980000, linked both ways (+0x3534 next, +0x3530 back); every float field of 0.1..100, spins some past 360, 0..120
   vertices), menutex_setup's texture as the tunnel texture, untextured now and then, modes 0..3, the pulse */
static void tunnel_setup(void)
{
	int t0 = menutex_setup(), k = t0 - t0 % 512;
	G32(0x4e186c) = t0;
	for (int j = 0; j <= 6; j++) {                     /* the inner layer's textures (0x9da470 - ring * 4): GL slot owners */
		char *sl = (char *)S32(BUF, 0xcd134);
		for (int m = irnd(0, 5); m; m--) sl = (char *)S32(sl, 0xc);
		G32(0x9da470 - j * 4) = k + S32(sl, 4);
	}
	int n = irnd(1, 4);
	for (int r = 0; r < n; r++) {
		char *g = BUF + 0x980000 + r * 0x4000;
		for (int o = 0; o < 0x3540; o += 4) SF(g, o) = (float)irnd(-1000, 1000) / 10.0f;
		SF(g, 0x1930) = (float)irnd(0, 3700) / 10.0f; SF(g, 0x3264) = (float)irnd(0, 3700) / 10.0f;
		S32(g, 0x3528) = irnd(0, 9) ? irnd(5, 120) : irnd(0, 4);   /* more overflows the 4096-call log */
		S32(g, 0x3520) = irnd(0, 300); S32(g, 0x3530) = r ? (int)(g - 0x4000) : 0;   /* back-link (the drawing walks back from the last ring) */
		S32(g, 0x3534) = r + 1 < n ? (int)(g + 0x4000) : 0;
	}
	G32(0x9da494) = irnd(0, 4) ? 0 : 1; G32(0x680370) = irnd(0, 3); G32(0x76d36c) = G32(0x9da470 - 4 * irnd(0, 6));   /* the last pass's texture */
	GF(0x4b06fc) = (float)irnd(0, 100) / 100.0f;
	g_a[0] = (int)(BUF + 0x980000);
}
ST(menu_drawBackground3D, tunnel_setup();, (CD(void, 0x429d70, char *)((char *)g_a[0]), 0), (menu_drawBackground3D(0, 0, 0, (DWORD)g_a[0], 0, 0, 0), 0))
