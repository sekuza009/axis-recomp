/* batch 140 */
/* the arena's game list: dlgwin_setup's window at 0x4db8c8 (lock icons from its set), the game records as
   gamelist_setup's (maps 0..15, modes 0..4 as kind strings), the list kinds, the box / searching flags, short texts */
static void arenalist_setup(void)
{
	gamelist_setup();
	dlgwin_setup(0x4db8c8);
	G32(0x76d448) = G32(0x9db0a4);
	fill((void *)0x4dba98, 16); fill((void *)0x4db8a0, 16);
	for (DWORD s = 0x7524a4; s <= 0x752ba4; s += 0x80) fill_str((char *)s, 8, 32, 126);
	for (int k = 0; k < 5; k++) fill_str((char *)0x4db8d8 + k * 5, 4, 32, 126);
	fill_str(GSTR(0x74f624), 12, 32, 126); fill_str((char *)0x4db520, 10, 32, 126);
	G32(0x4dbac8) = irnd(0, 2) ? 1 : 0; G32(0x4dbaa8) = irnd(0, 1); G32(0xa0b368) = irnd(0, 999);
	G32(0x4dba90) = irnd(0, 3) ? 0 : 1; G32(0x4db858) = irnd(0, 3) ? 0 : 1; G32(0x4db8b8) = irnd(0, 3) ? 0 : 1;
	G32(0x4db8bc) = irnd(0, 4) ? 0 : 1; G32(0x4db714) = irnd(0, 4) ? 0 : 1; G32(0x4db8b4) = irnd(0, 4) ? 0 : 1;
	G32(0x907b2c) = irnd(0, 4) ? 0 : 1;
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4db8c8) + irnd(0x23, 0x23e); G32(0x4ded6c) = G32(0x4db8cc) + irnd(0x30, 0x50); }
}
T_PLAIN(arena_40a070, 0x40a070, arenalist_setup();, 0, 0, 0, 0, 0)
