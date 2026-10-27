/* batch 161 */
/* the keyboard: a fake device or none (only when not ready), ready or not, GetDeviceState succeeding with random
   key states, losing the input (reacquire) or failing; the mouse buttons and wheel; a key code 0..255 or a mouse
   code 0xfa..0xfe */
static void keys_setup(void)
{
	FakeCom *kb = (FakeCom *)fakecom_new(0, 0x32, g_nargsDidev, 0);
	kb->fn[9] = fc_devState; kb->val[9] = (DWORD)(BUF + 0x3000);
	kb->ret[9] = irnd(0, 4) ? 0 : irnd(0, 1) ? (LONG)0x8007001e : (LONG)0x80004005;
	fill(BUF + 0x3000, 0x100); fill((void *)0x4d1e9c, 0x100);
	G32(0x4d1fa8) = irnd(0, 5) ? 1 : 0;
	G32(0x4d1fa0) = G32(0x4d1fa8) || irnd(0, 1) ? (int)kb : 0;
	G32(0x4ded94) = irnd(0, 1); G32(0x4ded98) = irnd(0, 1); G32(0x4ded9c) = irnd(0, 1); G32(0x4ded7c) = irnd(-2, 2);
	g_a[0] = irnd(0, 3) ? irnd(0, 255) : irnd(0xfa, 0xfe);
}
/* the menu sounds 0..5: dsbuf_setup's sound or none, sound on or off, the volume; the saved camera; a mission */
static void menusnd_setup(void)
{
	dsbuf_setup(0);
	for (int i = 0; i < 6; i++) G32(0x4dd4d4 + 4 * i) = irnd(0, 4) ? g_a[2] : 0;
	G32(0xa0e80c) = irnd(0, 4) ? 1 : irnd(0, 2);
	G32(0x4dd984) = irnd(-10000, 0);
	fill((void *)0x4df870, 12); fill((void *)0x76d388, 12);
	g_a[3] = irnd(-5, 100); g_a[4] = irnd(0, 5);
}
T_PLAIN(load_401540, 0x401540, keys_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(load_4014f0, 0x4014f0, keys_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(input_isDown, 0x401590, keys_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(sound_playMenu, 0x41e760, menusnd_setup();, 0, g_a[4], 0, 0, 0)
T_PLAIN(skirmish_443c80, 0x443c80, menusnd_setup();, 0, 0, 0, 0, 0)
T_PLAIN(FUN_00447960, 0x447960, menusnd_setup();, 0, 0, 0, 0, 0)
T_PLAIN(mission_4479b0, 0x4479b0, menusnd_setup();, 0, g_a[3], 0, 0, 0)
