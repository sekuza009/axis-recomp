/* batch 116 */
/* the text passes' globals as textpass_setup sets them (game state, screen size), a random text at BUF + 0x400, the
   language English / Korean */
static void menutext_setup(void)
{
	textpass_setup();
	G32(0x9dae74) = irnd(0, 2);
	fill((void *)0x76d438, 16); fill((void *)0x9da480, 16);
}
T_PLAIN(armc_4125c0, 0x4125c0, menutext_setup();, 0, g_a[0], g_a[1], BUF + 0x400, 0)
T_PLAIN(armc_drawStatLabel, 0x4125f0, menutext_setup();, 0, g_a[0], g_a[1], BUF + 0x400, 0)
/* the two message lines (up to 80 characters) */
static void msgbox_setup(void)
{
	menutext_setup();
	fill_str((char *)0x4df81c, 70, 32, 126); fill_str(GSTR(0x74de24), 70, 32, 126);
}
T_PLAIN(menu_4290d0, 0x4290d0, msgbox_setup();, 0, 0, 0, 0, 0)
/* the field: a dialog open now and then, a cursor position, the text (up to 28 characters: the mask buffer holds
   30), password or not; the cursor's blink globals as menu_428890's test sets them */
static void field_setup(void)
{
	menutext_setup();
	G32(0x90d1c4) = irnd(0, 5) ? 0 : 1; G32(0x9dbf10) = irnd(0, 28); G32(0x4e1868) = irnd(0, 1);
	fill_str((char *)0x9dc92c, 28, 32, 126);
	G32(0x9da908) = irnd(0, 45); GF(0x4de1f0) = csu_fr(-10, 100);
}
T_PLAIN(menu_428940, 0x428940, field_setup();, 0, g_a[0], g_a[1], 0, 0)
/* the profile list: 0..20 names, a first visible one and a selection somewhere around it, focused or not */
static void proflist_setup(void)
{
	menutext_setup();
	int n = irnd(0, 20); G32(0x9f9008) = n; G32(0x9f8c4c) = irnd(0, 7); G32(0x9f8d74) = irnd(-1, 20);
	G32(0x9f8f10) = irnd(0, 2); G32(0x9f8e48) = irnd(-50, 500); G32(0x9f8e4c) = irnd(-50, 400);
	for (int k = 0; k < 28; k++) fill_str((char *)0x9f684c + k * 0x48, 40, 32, 126);
}
T_PLAIN(profile_44ce90, 0x44ce90, proflist_setup();, 0, 0, 0, 0, 0)
/* the map list: 0..14 names (flags +0x40 set or not), a first visible one */
static void maplist_setup(void)
{
	menutext_setup();
	G32(0x9dd928) = irnd(0, 14); G32(0x9dd92c) = irnd(0, 4);
	G32(0x9dd908) = irnd(-50, 400); G32(0x9dd90c) = irnd(-50, 300); G32(0x9dd910) = irnd(0, 640);
	for (int k = 0; k < 20; k++) { char *r = (char *)0x9dda88 + k * 0x44; fill_str(r, 40, 32, 126); S32(r, 0x40) = irnd(0, 2) ? 0 : irnd(1, 3); }
}
T_PLAIN(mainmenu_442d10, 0x442d10, maplist_setup();, 0, 0, 0, 0, 0)
