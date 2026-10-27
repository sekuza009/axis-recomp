/* batch 124 */
/* the tunnel: menutex_setup's set with every texture it binds bindable (0x4e0cd0, 0x5b197c, 0x5b1978), modes 0..3,
   the animation values anywhere in (and now and then at the edges of) their ranges, the step 0x4b071c */
static void setuptunnel_setup(void)
{
	textpass_setup();
	int id = menutex_fonts(menutex_setup());
	G32(0x4e0cd0) = id; G32(0x5b197c) = id; G32(0x5b1978) = id; G32(0x5b1980) = id; G32(0x5b1984) = id;
	G32(0x4ddcec) = irnd(0, 3);
	GF(0x4de038) = (float)irnd(0, 100) / 100.0f; GF(0x4ddd90) = (float)irnd(-1000, 0) / 10.0f;
	GF(0x9db978) = irnd(0, 5) ? (float)irnd(0, 1000) / 10.0f : (float)irnd(-5, 105);
	GF(0x4df010) = irnd(0, 1) ? 1.0f : -1.0f;
	GF(0x4e14fc) = irnd(0, 5) ? (float)irnd(0, 1990) / 10.0f : (float)irnd(195, 205);
	GF(0x4deda8) = (float)irnd(0, 50) / 10.0f; GF(0x4b071c) = (float)irnd(1, 30) / 10.0f;
}
T_PLAIN(setup_423e50, 0x423e50, setuptunnel_setup();, 0, 0, 0, 0, 0)
/* the setup menu: the tunnel as above, four panel quads, the cursor often at a panel's centre, the hovered
   panel unchanged or not, its glow anywhere in 0..40, a message open now and then, the captions */
static void setupmenu_setup(void)
{
	setuptunnel_setup();
	G32(0x4dda60) = irnd(0, 5) ? 0 : 1; G32(0x680370) = irnd(0, 3) ? 0 : 1;
	G32(0x907b24) = irnd(-1, 3); GF(0x680ccc) = (float)irnd(0, 400) / 10.0f; GF(0x4df454) = irnd(0, 1) ? 1.0f : -1.0f;
	for (int k = 0; k < 4; k++) fill_str((char *)0x7506a4 + k * 0x80, 20, 32, 126);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	/* the panels (run-time data: 0x4df918, 11 dwords each: corner count 4, five xs, five ys): four quads */
	for (int k = 0; k < 4; k++) {
		DWORD *p = (DWORD *)0x4df918 + k * 11; int x = irnd(0, 500), y = irnd(0, 380), w = irnd(20, 140), h = irnd(20, 100);
		p[0] = 4; p[1] = x; p[2] = x + w; p[3] = x + w; p[4] = x; p[5] = 0;
		p[6] = y; p[7] = y; p[8] = y + h; p[9] = y + h; p[10] = 0;
		if (!irnd(0, 3)) { G32(0x4ded68) = x + w / 2; G32(0x4ded6c) = y + h / 2; }
	}
}
T_PLAIN(setup_423330, 0x423330, setupmenu_setup();, 0, 0, 0, 0, 0)
