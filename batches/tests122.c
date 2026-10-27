/* batch 121 */
/* the slot list: menutex_setup's set as the button texture, 0..30 slots from a first visible one (0..20, so the
   skipped slots 22..24 show up now and then), taken or not, kinds 0..4 with short names (10 rows of 4 strings stay
   inside the call log); the cursor sometimes on a row or button */
static void slotlist_setup(void)
{
	textpass_setup();
	G32(0x9db0a4) = menutex_fonts(menutex_setup());
	G32(0x67ef00) = irnd(0, 30); G32(0x4d7350) = irnd(0, 20);
	for (int k = 0; k < 40; k++) { G32(0x4d7358 + k * 8) = irnd(0, 2) ? 0 : 1; G32(0x4d735c + k * 8) = irnd(0, 4); }
	for (int k = 0; k < 40; k++) fill_str((char *)0x907b30 + k * 0x20, 6, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x4db8d8 + k * 5, 4, 32, 126);
	fill_str((char *)0x75d924, 10, 32, 126); fill_str((char *)0x75d9a4, 10, 32, 126);
	for (int k = 0; k < 4; k++) fill_str((char *)0x75da24 + k * 0x80, 10, 32, 126);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
}
T_PLAIN(arena_4038e0, 0x4038e0, slotlist_setup();, 0, 0, 0, 0, 0)
/* the map-select dialog: maplist_setup's list (positions overwritten by the window), dlgwin_setup's window at
   0x9dd908 with its textures and cursor, the two checkboxes, titles, short button labels */
static void mapselect_setup(void)
{
	maplist_setup();
	dlgwin_setup(0x9dd908);
	fill((void *)0x9eea98, 16); fill((void *)0x9dda70, 16);
	G32(0x4b2a7c) = irnd(0, 1); G32(0x9eeac0) = irnd(0, 1);
	fill_str(GSTR(0x74e8a4), 20, 32, 126); fill_str(GSTR(0x74e924), 16, 32, 126); fill_str(GSTR(0x74e9a4), 16, 32, 126);
	for (int k = 0; k < 4; k++) fill_str(GSTR(0x74ea24 + k * 0x80), 10, 32, 126);
	for (int k = 0; k < 14; k++) { char *r = (char *)0x9dda88 + k * 0x44; r[irnd(0, 12)] = 0; }   /* the list's names short */
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9dd908) + irnd(0x20, 0x200); G32(0x4ded6c) = G32(0x9dd90c) + irnd(0x28, 0xf5); }
}
T_PLAIN(mainmenu_442e10, 0x442e10, mapselect_setup();, 0, 0, 0, 0, 0)
