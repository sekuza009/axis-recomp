/* batch 132 */
/* the main menu: tunnels_setup's tunnel and textures, six panel quads (run-time data at 0x4deb80) with the cursor
   often at a panel's centre, flying in or not (depth near or at -550), locked now and then, the idle time below and
   above the hint's threshold, the hint fade anywhere in 0..1 with either direction, the captions */
static void mainmenu_setup(void)
{
	tunnels_setup();
	G32(0x9eeaa8) = irnd(0, 3) ? 0 : 1; G32(0x9eeab0) = irnd(0, 100); G32(0x9eeab4) = irnd(0, 4) ? 0 : 1;
	GF(0x9eea90) = irnd(0, 2) ? -550.0f : (float)irnd(-5500, 0) / 10.0f;
	GF(0x9dda80) = (float)irnd(0, 4000) / 10.0f; GF(0x9eea8c) = (float)irnd(-5, 105) / 100.0f;
	GF(0x9dd948) = irnd(0, 1) ? 0.05f : -0.05f; G32(0x680370) = irnd(0, 3) ? 0 : 1;
	G32(0x907b24) = irnd(-1, 6); GF(0x680ccc) = (float)irnd(0, 400) / 10.0f; GF(0x4df454) = irnd(0, 1) ? 1.0f : -1.0f;
	for (int k = 0; k < 6; k++) fill_str((char *)0x7501a4 + k * 0x80, 20, 32, 126);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	for (int k = 0; k < 6; k++) {
		DWORD *p = (DWORD *)0x4deb80 + k * 11; int x = irnd(0, 500), y = irnd(0, 380), w = irnd(20, 140), h = irnd(20, 100);
		p[0] = 4; p[1] = x; p[2] = x + w; p[3] = x + w; p[4] = x; p[5] = 0;
		p[6] = y; p[7] = y; p[8] = y + h; p[9] = y + h; p[10] = 0;
		if (!irnd(0, 5)) { G32(0x4ded68) = x + w / 2; G32(0x4ded6c) = y + h / 2; }
	}
}
T_PLAIN(menu_mainMenu, 0x442050, mainmenu_setup();, 0, 0, 0, 0, 0)
