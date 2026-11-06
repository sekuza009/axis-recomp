/* net_servers.c: the server list of the game's own TCP network code: pings, and the threads' events. */
#include "../game.h"


/* 0x454650: ping the server named address (dotted, inet_addr) with a 1 s timeout (net_ping), its slot's g_serverPing
   cleared first; 1 when net_ping returns a non-zero time: a server that answers (its time, at least 1), not one that
   does not (IcmpSendEcho writes the reply on a timeout too: status 11010, time 0, so net_ping gives 0; tested) */
int (net_pingServer)(const char *address, int slot)
{
	g_unusedPingWord1 = 0;
	g_unusedPingWord2 = 0;
	(*(int *)&g_pingTime) = 0;
	g_serverPing[slot] = 0;
	return net_ping(net_inetAddr(address), 1000) != 0;
}

/* 0x454690: the server table cleared and the threads' handles closed */
void (net_clearServers)(void)
{
	for (int i = 0; i < 0x100; i++)
		((u32 *)g_serverPinged)[i] = 0;
	for (int i = 0; i < 0x100; i++)
		g_serverPing[i] = 0;
	for (int i = 0; i < 0x500; i++)
		((u32 *)g_pingAddresses)[i] = 0;
	g_serverPingCount = 0;
	g_netListDone = 0;
	net_closeThreadHandles();
}

/* 0x454560: the ping thread's procedure (started by net_startPingThread): wait on g_pingStartEvent (0: ping every listed
   server, net_pingAllServers) and g_pingStopEvent (1: ExitThread); anything else waits again */
void (net_pingThreadProc)(void)
{
	void *events[2] = { g_pingStartEvent, g_pingStopEvent };
	for (;;) {
		u32 r = WaitForMultipleObjects(2, events, 0, 0xffffffff);
		if (r == 0)
			net_pingAllServers();
		else if (r == 1)
			ExitThread(0);
	}
}

/* 0x454740: the ping thread told to end: g_pingStartEvent reset, g_pingStopEvent set (its wait then returns 1:
   ExitThread). SetEvent's result */
int (net_stopPingThread)(void)
{
	ResetEvent(g_pingStartEvent);
	return SetEvent(g_pingStopEvent);
}
