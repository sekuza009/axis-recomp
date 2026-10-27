/* batch 165 */
/* the profile screen: its variables (PROFILE_VARS), saves to load and delete (selectload_setup), the keyboard and
   menu sounds, the chat edit's state; the three button tables with the cursor often on a button, clicks */
static void profilepage_setup(void)
{
	PROFILE_VARS
	selectload_setup(); g_mockDeleteOk = irnd(0, 1);
	keys_setup(); menusnd_setup();
	G32(0x9dae74) = irnd(0, 2);
	rect_table(0x9f6810, 0x9f6830); rect_table(0x9f8ef0, 0x9f8f10); rect_table(0x9f8f40, 0x9f8ff0);
	int t = irnd(0, 2);
	if (t == 0) point_in_table(0x9f6810, 0x9f6830); else if (t == 1) point_in_table(0x9f8ef0, 0x9f8f10); else point_in_table(0x9f8f40, 0x9f8ff0);
	G32(0x4ded68) = g_a[0]; G32(0x4ded6c) = g_a[1];
	g_mouseClick1 = irnd(0, 2) ? 1 : 0; g_mouseClick2 = !irnd(0, 3);
	G32(0x9f8d30) = irnd(-1, 12);
	G32(0x9f8d74) = irnd(0, 15);   /* the selected profile: an index into the table at 0x9f684c (PROFILE_VARS fills it) */
}
T_PLAIN(profile_44b600, 0x44b600, profilepage_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44b670, 0x44b670, profilepage_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44b6e0, 0x44b6e0, profilepage_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c390, 0x44c390, profilepage_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c400, 0x44c400, profilepage_setup();, 0, 0, 0, 0, 0)
T_PLAIN(profile_44c480, 0x44c480, profilepage_setup();, 0, 0, 0, 0, 0)
