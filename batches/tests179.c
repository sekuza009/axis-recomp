/* batch 178: game_postMatch generated (tools/gentests.py), dplay_initConnection by hand */
static const DWORD g_gs_420100[] = { 0x41e7a0, 0, 0x41e8b0, 0, 0x41e9d0, 0, 0x41eb00, 0, 0x41ec50, 0, 0x41ee40, 1, 0x41f880, 0, 0x447010, 0, 0x44aee0, 0, 0x451270, 3, 0x4521c0, 2, 0x457150, 1, 0x457310, 0, 0 };
static const DWORD g_gi_420100[] = { 0x4de6f8, 0x5ae9c4, 0x5b1dac, 0x76d3e8, 0x76d410, 0x9db990, 0x9f181c, 0x9f941c, 0xa05630, 0xa0b328, 0xa0b330, 0xa0baf8, 0xa0ea94, 0 };
static const DWORD g_gb_420100[] = { 0x9f9418, 0 };
T_PLAIN(game_postMatch, 0x420100, gen_setup(g_gs_420100, g_gi_420100, g_gb_420100); netstate_setup(); /* 0xa0b328 / 0xa0b330 are packet buffers (lstrcpyA between them) */, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* dplay_initConnection(kind, address): the old DirectPlay object closed (dplay_closeSession, real: a fake object or
   none), the connection by kind (0 TCP/IP: a compound address for the host name built by the fake lobby, size
   query then fill; 1..3 the stored connections 0xa0bae4 .. 0xa0baec, some empty; others), a new DirectPlay object
   (arena_4539f0, real: CoCreateInstance giving a fake or failing), InitializeConnection and GetCaps succeeding or
   not; a host name or none */
static void dpinit_setup(void)
{
	FakeCom *old = (FakeCom *)fakecom_new(0, 1, g_nargsDplay, 0), *d = (FakeCom *)fakecom_new(1, 7, g_nargsDplay, 0);
	FakeCom *l = (FakeCom *)fakecom_new(2, 2, g_nargsLobby, 0);
	G32(0xa0b404) = irnd(0, 2) ? (int)old : 0;
	G32(0xa0b398) = (int)l;
	l->fn[14] = fc_compoundAddr; l->val[14] = (DWORD)irnd(8, 0x40);
	l->ret0[14] = irnd(0, 4) ? (LONG)0x8877001e : (LONG)0x80004005; l->ret[14] = irnd(0, 4) ? 0 : (LONG)0x80004005;
	d->ret[38] = irnd(0, 3) ? 0 : (LONG)0x80004005;
	d->fn[14] = fc_getCaps; d->val[14] = (DWORD)irnd(0, 1000); d->ret[14] = irnd(0, 4) ? 0 : (LONG)0x80004005;
	g_mockCoClsid[0] = 0x4a9668; g_mockCoObj[0] = irnd(0, 5) ? (DWORD)d : 0;
	for (int k = 0; k < 4; k++) G32(0xa0bae0 + 4 * k) = irnd(0, 3) ? (int)(BUF + 0x400 + 0x40 * k) : 0;
	fill(BUF + 0x400, 0x100); fill_str((char *)0xa0bb0c, 20, 'a', 'z'); fill_str(BUF + 0x300, 30, '0', '9');
	G32(0xa0baf0) = 0;
	g_a[0] = irnd(0, 9) ? irnd(0, 3) : irnd(-1, 6); g_a[1] = irnd(0, 3) ? (int)(BUF + 0x300) : 0;
}
T_PLAIN(dplay_initConnection, 0x453a90, dpinit_setup();, 0, g_a[0], g_a[1], 0, 0)
