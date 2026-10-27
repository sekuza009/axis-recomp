/* batch 156 */
/* DirectPlay: a fake lobby and DirectPlay object or none (EnumSessions failing or not, its description hashed),
   the local player, the session list and the global blocks or none, connection kinds -1..4, the four slots */
static void dplay_setup(void)
{
	fill(BUF, 0x200);
	G32(0xa0b398) = irnd(0, 2) ? fakecom_new(0, 2, g_nargsDplay, 0) : 0;
	G32(0xa0b404) = irnd(0, 3) ? fakecom_new(1, 1, g_nargsDplay, 0) : 0;
	if (G32(0xa0b404)) { g_fakeCom[1].ret[13] = irnd(0, 2) ? 0 : (LONG)0x80004005; g_fakeCom[1].harg[13] = 1; g_fakeCom[1].hlen[13] = 0x50; }
	G32(0xa0b424) = irnd(0, 1) ? irnd(1, 0x7fffffff) : 0;
	G32(0xa0baf0) = irnd(0, 1) ? (int)(BUF + 0x100) : 0;
	G32(0xa0bab0) = irnd(0, 1) ? (int)(BUF + 0x140) : 0;
	G32(0xa0baf4) = irnd(0, 1) ? (int)(BUF + 0x180) : 0;
	G32(0xa0bad8) = (int)(BUF + 0x40);
	G32(0xa0b418) = irnd(0, 9) ? irnd(0, 3) : irnd(0, 1) ? -1 : 4;
	for (int k = 0; k < 4; k++) G32(0xa0d7a4 + 4 * k) = irnd(0, 1);
}
T_PLAIN(dplay_release, 0x453920, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(dplay_enumSessions, 0x453fd0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_4549a0, 0x4549a0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_4549c0, 0x4549c0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454ac0, 0x454ac0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454ae0, 0x454ae0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454bd0, 0x454bd0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454bf0, 0x454bf0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454ce0, 0x454ce0, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_454d00, 0x454d00, dplay_setup();, 0, 0, 0, 0, 0)
T_PLAIN(arena_453260, 0x453260, dplay_setup();, 0, 0, 0, 0, 0)
