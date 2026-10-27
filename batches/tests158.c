/* batch 157 */
static LONG dp_err(void)   /* a success, or one of the DirectPlay results the callers tell apart */
{
	static const DWORD e[] = { 0, 0, 0, 0x80004005, 0x887700dc, 0x887700f0, 0x88770078, 0x80070057, 0x88770028,
		0x8877003c, 0x887700aa, 0x88770168, 0x8877001e, 0x887700ff };
	return (LONG)e[irnd(0, sizeof e / sizeof e[0] - 1)];
}
/* dplay_setup's state with the DirectPlay object always there (unless none): CreatePlayer giving a player id,
   Open and EnumConnections results, the description passed to Open hashed, GetPlayerName answering size queries;
   the host's address (host_setup, ipstr_setup; lookups succeed), free or full player slots, a player name at BUF + 0x1c0 */
static void dplayconn_setup(void)
{
	slot_flags(); host_setup(); ipstr_setup();
	g_mockHostNameFail = g_mockHostFail = 0;   /* a failed lookup leaves the address empty: arena_4542a0 then reads strtok's NULL (in the original too) */
	dplay_setup();
	FakeCom *d = (FakeCom *)fakecom_new(1, 1, g_nargsDplay, 0);
	G32(0xa0b404) = irnd(0, 7) ? (int)d : 0;
	d->ret[6] = dp_err(); d->outarg[6] = 1; d->val[6] = (DWORD)irnd(1, 0x7fffffff);
	d->ret[24] = dp_err(); d->harg[24] = 1; d->hlen[24] = 0x50;
	d->ret[35] = dp_err();
	d->fn[21] = fc_getPlayerName; d->val[21] = irnd(0, 5) ? (DWORD)irnd(8, 64) : 0;
	d->ret0[21] = irnd(0, 4) ? (LONG)0x8877001e : dp_err(); d->ret[21] = irnd(0, 3) ? 0 : dp_err();
	g_mockMallocFail = !irnd(0, 7);
	fill_str(BUF + 0x1c0, 20, 'a', 'z');
	for (int i = 0; i < 8; i++) g_a[i] = irnd(0, 3) ? irnd(0, 64) : irnd(-1000, 100000);
}
/* dplay_create: the lobby from CoCreateInstance or none, its connection settings (size query and fill, flags 0..3),
   SetConnectionSettings and ConnectEx (giving the DirectPlay object) succeeding or not; the plain DirectPlay
   object from CoCreateInstance or none */
static void dplaycreate_setup(void)
{
	dplayconn_setup();
	G32(0xa0b398) = 0; G32(0xa0b404) = 0; G32(0xa0baf4) = 0;
	FakeCom *l = (FakeCom *)fakecom_new(0, 2, g_nargsLobby, 0);
	l->fn[8] = fc_getConnSettings; l->val[8] = (DWORD)irnd(0, 3);
	l->ret0[8] = irnd(0, 5) ? (LONG)0x8877001e : dp_err(); l->ret[8] = irnd(0, 5) ? 0 : dp_err();
	l->ret[12] = irnd(0, 5) ? 0 : dp_err();
	l->ret[15] = irnd(0, 5) ? 0 : dp_err(); l->outarg[15] = 3; l->val[15] = (DWORD)&g_fakeCom[1];
	g_mockCoClsid[0] = 0x4a9648; g_mockCoObj[0] = irnd(0, 3) ? (DWORD)l : 0;
	g_mockCoClsid[1] = 0x4a9668; g_mockCoObj[1] = irnd(0, 4) ? (DWORD)&g_fakeCom[1] : 0;
}
static DWORD g_dpname;
ST(dplay_getPlayerName, dplayconn_setup(); G32(0xa0b404) = (int)&g_fakeCom[1];,
   CALL_PLAIN(0x454190, 0, g_a[0], &g_dpname, 0, 0), dplay_getPlayerName(0, 0, 0, g_a[0], (DWORD)&g_dpname, 0, 0))
T_PLAIN(dplay_create, 0x453790, dplaycreate_setup();, 0, 0, 0, 0, 0)
ST(dplay_hostSession, dplayconn_setup();,
   ((DWORD (__cdecl *)(int, char *, int, int, int, int, int, int))0x453cf0)(g_a[0], BUF + 0x1c0, g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   dplay_hostSession(0, 0, 0, g_a[0], (DWORD)(BUF + 0x1c0), g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]))
T_PLAIN(dplay_joinSession, 0x453e60, dplayconn_setup();, 0, BUF + 0x40, BUF + 0x1c0, g_a[2], 0)
