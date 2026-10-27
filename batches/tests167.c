/* batch 166 */
/* the profile screen's input: profilepage_setup's state, the profile list (profiles_setup), all six button tables
   and the name page's OK rectangle with the cursor often on a button, key bindings among a few keys or the wheel
   (never the mouse buttons: batch 162), their latches, a fake DirectInput for input_initKeyboard (else it would
   reach the game's real one), the intro animation, page, dialog, repeat delays, pop-in and message state */
static void profileinput_setup(void)
{
	profilepage_setup();
	profiles_setup();
	G32(0x9f8d74) = irnd(0, 15);
	rect_table(0x9f9028, 0x9f9048); rect_table(0x9f8c68, 0x9f8cf8); rect_table(0x9f8d80, 0x9f8e50);
	{ int l = irnd(0, 500), t = irnd(0, 400); G32(0x9f9010) = l; G32(0x9f9014) = t; G32(0x9f9018) = l + irnd(0, 140); G32(0x9f901c) = t + irnd(0, 80); }
	static const DWORD tb[][2] = { { 0x9f6810, 0x9f6830 }, { 0x9f8ef0, 0x9f8f10 }, { 0x9f8f40, 0x9f8ff0 },
		{ 0x9f9028, 0x9f9048 }, { 0x9f8c68, 0x9f8cf8 }, { 0x9f8d80, 0x9f8e50 } };
	int k = irnd(0, 6);
	if (k < 6) point_in_table(tb[k][0], tb[k][1]);
	else { g_a[0] = G32(0x9f9010) + irnd(-5, 150); g_a[1] = G32(0x9f9014) + irnd(-5, 90); }
	G32(0x4ded68) = g_a[0]; G32(0x4ded6c) = g_a[1];
	static const DWORD binds[] = { 0x9db0a0, 0x76d330, 0x4e1510, 0x9dae70, 0x4e0cdc, 0x9db974, 0x9dae14, 0x76d48c, 0x4e0cd4 };
	static const int keys[] = { 0x01, 0x1c, 0xc8, 0xd0, 0xcb, 0xcd, 0x0e, 0xfd, 0xfe };
	for (int i = 0; i < 9; i++) {
		int key = keys[irnd(0, 8)];
		G32(binds[i]) = key;
		if (key < 0xfa) G32(0x4d1a98 + 4 * key) = irnd(0, 2) ? 0 : 1;
	}
	FakeCom *di = (FakeCom *)fakecom_new(13, 0x30, g_nargsDinput, irnd(0, 2) ? 0 : (LONG)0x80004005);
	di->outarg[3] = 2; di->val[3] = (DWORD)fakecom_new(14, 0x31, g_nargsDidev, 0);
	G32(0x4d1e98) = (int)di;
	G32(0x9f6838) = !irnd(0, 4); G32(0x9f8e54) = irnd(0, 6); G32(0x9f8f10) = irnd(-1, 7);
	g_menuDialogOpen = !irnd(0, 4);
	GF(0x76d37c) = (float)irnd(-1, 5); GF(0x680bb4) = (float)irnd(-1, 5);
	G32(0x74de1c) = irnd(0, 2); G32(0x76d42c) = irnd(0, 2); G32(0x9f8f34) = irnd(0, 2); G32(0x9f8c5c) = irnd(-1, 3);
}
T_PLAIN(profile_44be00, 0x44be00, profileinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c190, 0x44c190, profileinput_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_processInput, 0x44c560, profileinput_setup();, 0, 0, 0, 0, 0)
