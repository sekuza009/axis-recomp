/* batch 128 */
/* the room menu: tunnels_setup's tunnel and textures, six panel quads (run-time data at 0x9daf88) with the cursor
   often at a panel's centre, the hover state and glow, modes 0..3, the captions */
static void roommenu_setup(void)
{
	tunnels_setup();
	G32(0x9dd7d8) = irnd(0, 5) ? 0 : 1; G32(0x9dce48) = irnd(0, 3);
	G32(0x907b24) = irnd(-1, 5); GF(0x680ccc) = (float)irnd(0, 400) / 10.0f; GF(0x4df454) = irnd(0, 1) ? 1.0f : -1.0f;
	for (int k = 0; k < 6; k++) fill_str((char *)0x750ba4 + k * 0x80, 20, 32, 126);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	for (int k = 0; k < 6; k++) {
		DWORD *p = (DWORD *)0x9daf88 + k * 11; int x = irnd(0, 500), y = irnd(0, 380), w = irnd(20, 140), h = irnd(20, 100);
		p[0] = 4; p[1] = x; p[2] = x + w; p[3] = x + w; p[4] = x; p[5] = 0;
		p[6] = y; p[7] = y; p[8] = y + h; p[9] = y + h; p[10] = 0;
		if (!irnd(0, 5)) { G32(0x4ded68) = x + w / 2; G32(0x4ded6c) = y + h / 2; }
	}
}
T_PLAIN(room_437e00, 0x437e00, roommenu_setup();, 0, 0, 0, 0, 0)
