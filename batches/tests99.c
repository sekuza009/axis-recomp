/* batch 98 */
/* the network mocks: events and threads that fail now and then, recv returning 0..0x80 bytes or an error, Winsock
   versions 2.2 or other, sockets, bind and connect that fail or are refused, a host name that is no dotted address */
static void netmock_setup(void)
{
	g_mockEventFail = !irnd(0, 9); g_mockThreadFail = !irnd(0, 9);
	g_mockRecvRet = irnd(0, 4) ? (DWORD)irnd(0, 0x80) : (DWORD)-1;
	g_mockWsaFail = !irnd(0, 9); g_mockWsaVer = irnd(0, 9) ? 0x202 : 0x101;
	g_mockSocket = irnd(0, 9) ? 0x1234 : 0xffffffff; g_mockBindFail = !irnd(0, 9);
	g_mockConnectRet = irnd(0, 2) ? 0 : irnd(0, 1) ? 0xffffffff : 0x274d;
	g_mockInetNone = !irnd(0, 3); g_mockHostFail = !irnd(0, 3);
	fill_str((char *)0xa055e4, 15, '0', '9'); fill((void *)0xa05326, 2);
	fill((void *)0xa055f8, 4); fill((void *)0xa05630, 4); fill((void *)0xa0b2fc, 4); fill((void *)0xa0b380, 4);
	fill((void *)0xa0bb10, 4); fill((void *)0xa0bf1c, 4); fill((void *)0xa0d784, 8);
}
ST(net_startThread, netmock_setup();, CD(int, 0x4546d0, void)(), net_startThread(0, 0, 0, 0, 0, 0, 0))
/* a reply of the given type in the buffer (recv may overwrite it) */
static void netreply_setup(DWORD buf, int len, DWORD typep)
{
	netmock_setup();
	fill((void *)buf, len); G32(typep) = irnd(0, 9) ? irnd(0, 3) : irnd(4, 9);
	for (int k = 15; k < len; k += 16) ((BYTE *)buf)[k] = 0;   /* the record's strings end (net_452af0 / c80 copy them) */
	g_mockRecvRet = irnd(0, 4) ? (DWORD)irnd(0, 0x30) : (DWORD)-1;   /* recv's pattern has no 0 byte: keep it off the strings */
	fill((void *)0xa0d79c, 4); G32(0xa0b368) = irnd(0, 9); G32(0xa0b358) = irnd(0, 9);   /* list slots, as netrec_setup's */
	fill((void *)0xa0b36c, 4); fill((void *)0xa0b34c, 4); fill((void *)0xa0b300, 4);
}
ST(net_452a30, netreply_setup(0xa05260, 0x5b, 0xa052aa);, (CD(void, 0x452a30, void)(), 0), (net_452a30(0, 0, 0, 0, 0, 0, 0), 0))
ST(net_452bd0, netreply_setup(0xa0b280, 0x79, 0xa0b2e8);, (CD(void, 0x452bd0, void)(), 0), (net_452bd0(0, 0, 0, 0, 0, 0, 0), 0))
ST(net_connect, netmock_setup(); g_a[0] = irnd(0, 9) ? 100 + irnd(0, 1) : irnd(0, 200);,
   CD(int, 0x451b80, int)(g_a[0]), net_connect(0, 0, 0, (DWORD)g_a[0], 0, 0, 0))
/* the lobby: connected already or not, with the lobby screen's state variables random */
static void lobbyopen_setup(void)
{
	static const DWORD vars[] = { 0x4db718, 0x4db858, 0x4db8b4, 0x4db8b8, 0x4dba80, 0x4dba88, 0x4dba8c, 0x4dbaa8, 0x4dbaac,
	                              0x4dbac8, 0x4ded18, 0x4ded60, 0x4df018, 0x4df818, 0x5b1914, 0x67ef30, 0x680bb0, 0x680bb8,
	                              0x76d41c, 0x76d484, 0x9087b0, 0xa0b31c, 0xa0b36c };
	netmock_setup();
	for (unsigned k = 0; k < sizeof vars / sizeof vars[0]; k++) fill((void *)vars[k], 4);
	G32(0x4db718) = irnd(0, 3) ? 0 : 1;
	G32(0xa0b31c) = (int)(BUF + 0x960000); fill(BUF + 0x960000, 0x100);   /* the send buffer pointer */
}
ST(lobby_openConnection, lobbyopen_setup();, CD(int, 0x4060f0, void)(), lobby_openConnection(0, 0, 0, 0, 0, 0, 0))
