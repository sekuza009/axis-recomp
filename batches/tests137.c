/* batch 136 */
/* the game list: dlgwin_setup's window at 0x9dd4a8 (the lock icons from its set too), a list or none, 0..30 games
   from a first visible one 0..20, short names, maps 0..15 (the record's map is a signed byte index), modes 0..4,
   player counts, the selection, pages, the joining / blinking / confirmation states, short texts */
static void gamelist_setup(void)
{
	dlgwin_setup(0x9dd4a8);
	G32(0x76d448) = G32(0x9db0a4);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	for (DWORD s = 0x759ca4; s <= 0x75a1a4; s += 0x80) fill_str((char *)s, 8, 32, 126);
	fill_str((char *)0x75c1a4, 6, 32, 126); fill_str(GSTR(0x74f124), 12, 32, 126); fill_str((char *)0x9dcee8, 10, 32, 126);
	fill_str((char *)0x752aa4, 12, 32, 126); fill_str((char *)0x752b24, 12, 32, 126); fill_str((char *)0x751824, 8, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x7673a4 + k * 0x80, 6, 32, 126);
	for (int k = 0; k < 16; k++) fill_str((char *)0x907b30 + k * 0x20, 10, 'A', 'z');
	G32(0x9dd330) = irnd(0, 4) ? 1 : 0; G32(0x67ef30) = irnd(0, 30); G32(0x680bb0) = irnd(0, 20);
	for (int g = 0; g < 50; g++) {
		char *r = (char *)0x9087c4 + g * 0x4a;
		fill(r, 0x4a);
		fill_str(r, 10, 32, 126);
		r[0x20] = (char)(irnd(0, 3) ? 0 : 1); r[0x21] = (char)irnd(0, 15);
		r[0x22] = (char)irnd(0, 16); r[0x23] = (char)irnd(-1, 16);
		int v = irnd(-99999, 99999); memcpy(r + 0x24, &v, 4);
		r[0x28] = (char)irnd(0, 4); r[0x43] = (char)(irnd(0, 2) ? 0 : 1);
	}
	G32(0x76d41c) = irnd(-1, 40); G32(0x680bb8) = irnd(0, 999); G32(0xa0b358) = irnd(0, 999);
	G32(0x9dd6a0) = irnd(0, 3) ? 0 : 1; G32(0x9dd3fc) = irnd(0, 3) ? 0 : 1; G32(0x9dd6b4) = irnd(0, 4) ? 0 : 1;
	G32(0x4db8b4) = irnd(0, 4) ? 0 : 1; GF(0x4dba80) = (float)irnd(0, 100000) / 100.0f;
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9dd4a8) + irnd(0x20, 0x240); G32(0x4ded6c) = G32(0x9dd4b4) - irnd(0x12, 0x32); }
}
T_PLAIN(room_43adc0, 0x43adc0, gamelist_setup();, 0, 0, 0, 0, 0)
