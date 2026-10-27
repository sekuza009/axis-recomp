/* batch 100 */
/* the whole mech: wholeplayer_setup's player as the edited one (or none), the name, value, team and part / item
   indices any value (the pickers wrap them) */
static DWORD g_am[14];
static void armcmech_setup(void)
{
	wholeplayer_setup();
	S32(SCENE, 0x234240d) = irnd(0, 4) ? (int)g_pl[0] : -1;
	g_am[0] = g_pl[1]; g_am[1] = g_pl[2]; g_am[2] = g_pl[3];
	for (int k = 3; k < 8; k++) g_am[k] = irnd(-6, 6);
	for (int k = 8; k < 14; k++) g_am[k] = irnd(-1, 3);
}
ST(armc_461250, armcmech_setup();,
   (TC(void, 0x461250, char *, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD, DWORD)(SCENE,
     g_am[0], g_am[1], g_am[2], g_am[3], g_am[4], g_am[5], g_am[6], g_am[7], g_am[8], g_am[9], g_am[10], g_am[11], g_am[12], g_am[13]), 0),
   (armc_461250(SCENE, g_am[0], g_am[1], g_am[2], g_am[3], g_am[4], g_am[5], g_am[6], g_am[7], g_am[8], g_am[9], g_am[10], g_am[11],
     g_am[12], g_am[13]), 0))
/* the name: one of the reserved names (as stored, so a byte-exact match) or a random one; the mech bytes, the
   version strings and the address strings the packet takes; the send buffer; the network mocks */
static void reserved_name(char *dst)
{
	static const DWORD res[] = { 0x4ad4b8, 0x4ad4c8, 0x4ad4d8, 0x4ad4e8, 0x4ad4f4, 0x4ad504, 0x4ad514, 0x4ad524, 0x4ad530, 0x4ad53c, 0x4ad548, 0x4ad554 };
	if (irnd(0, 2)) fill_str(dst, 15, 'A', 'z'); else strcpy(dst, (const char *)res[irnd(0, 11)]);
}
static void lobbylogin_setup(DWORD name, DWORD bytes, DWORD bufp)
{
	charset_setup();                             /* room_433640 (Name3) draws with the font tables */
	netmock_setup();
	reserved_name((char *)name);
	fill((void *)bytes, 0x20);
	G32(bufp) = (int)(BUF + 0x960000); fill(BUF + 0x960000, 0x200);
	fill_str((char *)0xa0b43c, 15, 32, 126); fill_str((char *)0x9dd570, 15, 32, 126); fill_str((char *)0x4dbbf4, 15, 32, 126);
	fill((void *)0x4dba88, 4); fill((void *)0x4ded60, 4); fill((void *)0x4ded18, 4); fill((void *)0xa0b43c + 0x10, 4);
}
ST(lobby_checkReservedName3, lobbylogin_setup(0x5b1b30, 0x5b1b50, 0xa0b328);, (CD(void, 0x4351c0, void)(), 0),
   (lobby_checkReservedName3(0, 0, 0, 0, 0, 0, 0), 0))
ST(lobby_checkReservedName2, lobbylogin_setup(0x4ded20, 0x4ded40, 0xa0b310);, (CD(void, 0x405cf0, void)(), 0),
   (lobby_checkReservedName2(0, 0, 0, 0, 0, 0, 0), 0))
