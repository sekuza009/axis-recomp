/* net_servers.c: the server list of the game's own TCP network code: pings, and the threads' events. */
#include "../game.h"

#define g_serverUsed ((u32 *)0xa0bb14)                /* per server slot (256) */
#define g_serverPing ((int *)0xa0d384)                /* per server slot: the ping time (0 none) */
#define g_serverNames ((u32 *)0xa0bf20)               /* 256 names of 0x14 bytes */

/* 0x454650: ping the server named address (dotted) and keep its time in slot; 1 when it answered within a second */
int (net_pingServer)(const char *address, int slot)
{
	GAME_VAR(int, 0xa0bf14) = 0;
	GAME_VAR(int, 0xa0bf18) = 0;
	GAME_VAR(int, 0xa0d798) = 0;
	g_serverPing[slot] = 0;
	return net_ping(inet_addr_wrap_4547c0(address), 1000) != 0;
}

/* 0x454690: the server table cleared and the threads' handles closed */
void (net_clearServers)(void)
{
	for (int i = 0; i < 0x100; i++)
		g_serverUsed[i] = 0;
	for (int i = 0; i < 0x100; i++)
		g_serverPing[i] = 0;
	for (int i = 0; i < 0x500; i++)
		g_serverNames[i] = 0;
	g_serverPingCount = 0;
	g_netListDone = 0;
	net_closeThreadHandles();
}

/* 0x454560: the receive thread's procedure: wait on the two events (0xa0bb10 data, 0xa0bf1c stop): data pings the
   listed servers and waits again, stop ends the thread, anything else waits again */
void (net_pingThreadProc)(void)
{
	void *events[2] = { g_pingDataEvent, g_pingStopEvent };
	for (;;) {
		u32 r = WaitForMultipleObjects(2, events, 0, 0xffffffff);
		if (r == 0)
			net_pingAllServers();
		else if (r == 1)
			ExitThread(0);
	}
}

/* 0x454740: the network thread told to go on (one event reset, the other set; SetEvent's result) */
int (net_wakePingThread)(void)
{
	ResetEvent(g_pingDataEvent);
	return SetEvent(g_pingStopEvent);
}
