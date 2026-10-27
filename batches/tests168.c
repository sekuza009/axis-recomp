/* batch 167 */
/* a message: a DirectPlay system message (create player 5 / destroy player 3 / another type: its id and a value) or
   a game packet (type 1..7, a player slot 0..15, a payload size of 0x40 or another, data), in buf (0x80 bytes);
   returns its length */
static DWORD rcvmsg_make(BYTE *buf, int sys)
{
	fill(buf, 0x80);
	if (sys) {
		static const int types[] = { 3, 5, 5, 3, 1, 7 };
		*(DWORD *)buf = (DWORD)types[irnd(0, 5)]; *(DWORD *)(buf + 8) = (DWORD)irnd(1, 0x7fff);
		return 0x30;
	}
	*(DWORD *)buf = (DWORD)(irnd(0, 9) ? irnd(1, 7) : irnd(0, 9));
	buf[4] = (BYTE)irnd(0, 15);
	*(DWORD *)(buf + 5) = irnd(0, 2) ? 0x40 : (DWORD)irnd(0, 0x40);
	if (*(DWORD *)buf == 1) { char *t = (char *)buf + 0xc; fill_str(t, 40, 32, 126); }
	return irnd(0, 4) ? (DWORD)irnd(0x10, 0x80) : (DWORD)irnd(0, 0x10);
}
/* the network: dplayconn_setup's DirectPlay object (Send results, player names), netstate_setup's packet buffers,
   free and taken player slots; the receive queue (0..6 messages, some an error), the buffer size so far, hosting
   or not over each connection kind, the room or arena, flags; a message and its sender at BUF + 0x3800 */
static void dpmsg_setup(void)
{
	dplayconn_setup();
	netstate_setup();
	FakeCom *d = &g_fakeCom[1];
	G32(0xa0b404) = (int)d;   /* the callers reach it only while connected (dplay_getPlayerName does not check) */
	d->fn[25] = fc_receive; d->val2[25] = 0;
	d->val[21] = (DWORD)irnd(0x18, 64);   /* real DirectPlay gives a whole DPNAME (net_logMessage reads its name pointer) */
	d->ret0[21] = irnd(0, 4) ? (LONG)0x8877001e : (LONG)0x80004005;   /* and never succeeds on the size query */
	d->ret[26] = irnd(0, 3) ? 0 : (LONG)0x80004005;
	g_nrcv = irnd(0, 6);
	for (int i = 0; i < g_nrcv; i++) {
		int sys = !irnd(0, 2);
		g_rcv[i].from = sys ? 0 : (DWORD)irnd(1, 0x7fff);
		g_rcv[i].len = rcvmsg_make(g_rcv[i].data, sys);
		g_rcv[i].ret = irnd(0, 9) ? 0 : irnd(0, 1) ? (LONG)0x887703e8 : (LONG)0x80004005;
	}
	G32(0x9fd940) = irnd(0, 2) ? 0 : irnd(0, 0x100);
	G32(0xa0baf8) = irnd(0, 1); G32(0xa0b418) = irnd(0, 3) ? 0 : irnd(1, 3);
	G32(0xa0b380) = irnd(0, 2) ? irnd(200, 201) : irnd(0, 300);
	G32(0xa0b360) = irnd(0, 2) ? 0 : 1; G32(0xa0b364) = irnd(0, 2) ? 0 : 1;
	G32(0x9fd94c) = irnd(0, 1); G32(0x9fd948) = 0; G32(0x9fd95c) = 0; G32(0x9fd950) = irnd(0, 16);
	g_a[4] = (int)rcvmsg_make((BYTE *)BUF + 0x3800, irnd(0, 1));
	g_a[5] = irnd(1, 0x7fff);
	fill_str(BUF + 0x3900, 40, 32, 126);
	for (int i = 0; i < 4; i++) g_a[i] = irnd(0, 3) ? irnd(0, 0x7fff) : irnd(-5, 5);
}
static DWORD g_rcvOut[4];
ST(arena_450bc0, dpmsg_setup(); g_rcvOut[2] = (DWORD)irnd(0, 0x100); if (!irnd(0, 7)) G32(0xa0b404) = 0;,
   ((DWORD (__cdecl *)(DWORD *, DWORD *, DWORD, void *, DWORD *))0x450bc0)(&g_rcvOut[0], &g_rcvOut[1], g_a[2], BUF + 0x3a00, &g_rcvOut[2]),
   arena_450bc0(0, 0, 0, (DWORD)&g_rcvOut[0], (DWORD)&g_rcvOut[1], g_a[2], (DWORD)(BUF + 0x3a00), (DWORD)&g_rcvOut[2], 0, 0, 0))
ST(FUN_00450bf0, dpmsg_setup(); if (!irnd(0, 7)) G32(0xa0b404) = 0;,
   ((DWORD (__cdecl *)(DWORD, DWORD, DWORD, void *, DWORD))0x450bf0)(g_a[0], g_a[1], g_a[2], BUF + 0x3800, g_a[4]),
   FUN_00450bf0(0, 0, 0, g_a[0], g_a[1], g_a[2], (DWORD)(BUF + 0x3800), g_a[4], 0, 0, 0))
T_PLAIN(FUN_00451270, 0x451270, dpmsg_setup();, 0, BUF + 0x3800, g_a[0], g_a[4], 0)
T_PLAIN(net_logMessage, 0x451350, dpmsg_setup();, 0, g_a[5], BUF + 0x3900, BUF + 0x3a00, 0)
T_PLAIN(arena_451090, 0x451090, dpmsg_setup();, 0, BUF + 0x3800, g_a[4], g_a[5], 0)
T_PLAIN(net_sendLocalInfo, 0x450c20, dpmsg_setup();, 0, BUF + 0x3800, 0, 0, 0)
T_PLAIN(arena_450a60, 0x450a60, dpmsg_setup();, 0, 0, 0, 0, 0)
T_PLAIN(FUN_00450bb0, 0x450bb0, dpmsg_setup();, 0, 0, 0, 0, 0)
