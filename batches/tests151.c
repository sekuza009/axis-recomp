/* batch 150 */
/* the receive thread: net_4545b0's state as ping_setup sets it, the two event handles, 0..5 data events (now and
   then a timeout or failure value in between) before the stop event; the mocked ExitThread ends the run */
static void netthread_setup(void)
{
	ping_setup();
	G32(0xa0bb10) = 0x5550 + irnd(0, 9); G32(0xa0bf1c) = 0x6660 + irnd(0, 9);
	g_mockNWaits = (DWORD)irnd(0, 5);
	for (DWORD k = 0; k < g_mockNWaits; k++) g_mockWaits[k] = irnd(0, 5) ? 0 : (irnd(0, 1) ? 0x102 : 0xffffffff);
}
T_PLAIN(net_454560, 0x454560, netthread_setup();, 0, 0, 0, 0, 0)
