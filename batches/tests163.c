/* batch 162 */
/* the settings screens: the skirmish lists (sk_setup), keyboard (keys_setup) and menu sounds (menusnd_setup), the
   save file, the undo history; dialog open or not, clicks; the skirmish and mission button tables with the cursor
   often on a button; key bindings among a few keys or the wheel (never the mouse buttons 0xfa..0xfc: the patch DLL's
   latch for them in 0x401600 lives in the DLL and would differ between the runs), their latches; the repeat
   delays, mission and unlocked count, pages, unlock screen; the player's typing flag; the chat positions */
static void menudisp_setup(void)
{
	sk_setup(); keys_setup(); menusnd_setup(); vfs_content(0, 0x8000); undo_setup();
	g_menuDialogOpen = !irnd(0, 4); g_mouseClick1 = irnd(0, 1); g_mouseClick2 = !irnd(0, 3);
	rect_table(0x9ef228, 0x9ef2c8); rect_table(0x9f6338, 0x9f6378);
	if (irnd(0, 1)) point_in_table(0x9ef228, 0x9ef2c8); else point_in_table(0x9f6338, 0x9f6378);
	G32(0x4ded68) = g_a[0]; G32(0x4ded6c) = g_a[1];
	static const DWORD binds[] = { 0x4e0cd4, 0x4e0cdc, 0x76d48c, 0x4e150c, 0x4e1514, 0x9dae70, 0x9db0a0, 0x76d330 };
	static const int keys[] = { 0x01, 0x1c, 0xc8, 0xd0, 0x39, 0x0e, 0xfd, 0xfe };
	for (int i = 0; i < 8; i++) {
		int k = keys[irnd(0, 7)];
		G32(binds[i]) = k;
		if (k < 0xfa) G32(0x4d1a98 + 4 * k) = irnd(0, 2) ? 0 : 1;
	}
	GF(0x76d37c) = (float)irnd(-1, 5); GF(0x680bb4) = (float)irnd(-1, 5); G32(0x4dda44) = irnd(0, 1);
	G32(0x9f63b4) = irnd(0, 14); G32(0x9f181c) = irnd(0, 15); G32(0x9f6300) = !irnd(0, 3); G32(0x9f62e0) = irnd(0, 1);
	G32(0x9ef1f0) = irnd(0, 3); G32(0x9ef1f8) = irnd(0, 2) ? 10 : irnd(0, 1) ? 0x14 : irnd(0, 30);
	fill((void *)0x907b30, 16 * 32); fill((void *)0x9db9e4, 15 * 0x5c);
	G32(0x76d41c) = irnd(0, 15);
	for (int i = 0; i < 16; i++) *(BYTE *)(0x908807 + 0x4a * i) = (BYTE)irnd(0, 1);
	G32(0x9dd4a8) = irnd(0, 600); G32(0x9dd4ac) = irnd(0, 400); G32(0x4db8c8) = irnd(0, 600); G32(0x4db8cc) = irnd(0, 400);
	G32(0x9dae74) = irnd(0, 2);
	fill((void *)0x9dc92c, 0x400);
}
T_PLAIN(skirmish_saveSettings, 0x443e20, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(mission_447a50, 0x447a50, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(mission_4479d0, 0x4479d0, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_444070, 0x444070, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(skirmish_processKeys, 0x443f20, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(room_434320, 0x434320, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_editTextField_405010, 0x405010, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_443ef0, 0x443ef0, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_4440f0, 0x4440f0, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(mission_unlockCheat, 0x447b10, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(FUN_00405200, 0x405200, menudisp_setup();, 0, 0, 0, 0, 0)
T_PLAIN(room_434da0, 0x434da0, menudisp_setup();, 0, 0, 0, 0, 0)
