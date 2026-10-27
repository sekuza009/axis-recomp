/* batch 201 */
/* the profile pages' keys: profileinput_setup (the page, bindings among a few keys with their latches, repeat
   delays, dialog state); callees real as for profile_processInput */
T_PLAIN(profile_44c600, 0x44c600, profileinput_setup(); G32(0x9f8d30) = irnd(0, 8);, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c850, 0x44c850, profileinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c8c0, 0x44c8c0, profileinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44ca90, 0x44ca90, profileinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44cc60, 0x44cc60, profileinput_setup(); G32(0x9f8d30) = irnd(0, 8);, 0, 0, 0, 0, 0)
/* the profile screen's key dispatch: profileinput_setup, the dialog flag 0x90d1c4 and Enter's second binding
   0x6803a0 among the same keys; the page handlers stubbed */
static const DWORD g_stubMenuCdd0[] = { 0x44c600, 0, 0x44c850, 0, 0x44c8c0, 0, 0x44ca90, 0, 0x44cc60, 0, 0 };
static void menucdd0_setup(void)
{
	callee_stubs(g_stubMenuCdd0, 0);
	profileinput_setup();
	static const int keys[] = { 0x01, 0x1c, 0xc8, 0xd0, 0xfd };
	int key = keys[irnd(0, 4)];
	G32(0x6803a0) = key; if (key < 0xfa) G32(0x4d1a98 + 4 * key) = irnd(0, 2) ? 0 : 1;
	G32(0x90d1c4) = !irnd(0, 4);
}
T_PLAIN(menu_44cdd0, 0x44cdd0, menucdd0_setup();, 0, 0, 0, 0, 0)
/* the menus' key dispatch: the blocking flags, the fade at, below or above its limit, a pending dialog, the
   screen among its ten values or another; the poll and every handler stubbed */
static const DWORD g_stubMenuKeys[] = { 0x4012c0, 0, 0x4081f0, 0, 0x410ab0, 0, 0x4230a0, 0, 0x42ada0, 0, 0x4318b0, 0,
	0x431950, 0, 0x4378e0, 0, 0x441e00, 0, 0x4440f0, 0, 0x447c70, 0, 0x44cdd0, 0, 0 };
static void menukeys_setup(void)
{
	callee_stubs(g_stubMenuKeys, 0);
	static const int scr[] = { 200, 210, 300, 400, 500, 600, 700, 800, 900, 9999, 0, 250, 1000 };
	G32(0x68039c) = !irnd(0, 5); G32(0x680370) = !irnd(0, 5); G32(0x4df900) = !irnd(0, 4);
	float lim = GF(0x4a93e8); int k = irnd(0, 3);
	GF(0x9da434) = k == 0 ? lim : k == 1 ? lim + 1.0f : lim - (float)irnd(1, 100) / 10.0f;
	G32(0x76d3e8) = scr[irnd(0, 12)];
}
T_PLAIN(menu_processKeys, 0x4319d0, menukeys_setup();, 0, 0, 0, 0, 0)
