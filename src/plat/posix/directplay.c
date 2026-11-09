/* plat/posix/directplay.c: DirectPlay for Linux, macOS and the like (portable build only; not built on Windows) -
   axisnet's own replacement (axisnet_dp.c: the DirectPlay and DirectPlayLobby objects, the session hub, LAN
   discovery, the built-in game list, the ping) built on POSIX with the few Windows pieces it uses answered here,
   so the game plays the same sessions with the same protocol as on Windows (Windows players and the DServer relay
   included). The game reaches it as on Windows: CoCreateInstance(CLSID_DirectPlay / DirectPlayLobby) gives the
   objects and plat.h's NET_ operations call through their tables. axisnet.ini is read from the game's folder (the
   current directory). Not here: UPnP (the router's port opened for a host; Windows' COM service) and the host
   address copied to the clipboard - a host can do both. */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE
#include "win32_compat.h"

#define AXIS_NATIVE 1      /* (axisnet's native build: no patch layer) */
#define AXISNET_POSIX 1    /* (axisnet_dp.c: no UPnP, no clipboard) */
#include "../../../axisnet_dp.c"

socklen_t net_native_addr(const void *win, int len, struct sockaddr_in *out);   /* plat/posix/net.c */
static HRESULT WINAPI no_class(REFCLSID c, void *o, DWORD x, REFIID i, void **p) { (void)c; (void)o; (void)x; (void)i; if (p) *p = NULL; return REGDB_E_CLASSNOTREG; }
static int WSAAPI connect_native(SOCKET s, const struct sockaddr *a, int len) { return connect(s, a, (socklen_t)len); }

/* the start (axisnet_attach's network part): its locks, the hub's sockets unset, the settings read */
static int g_started;
static void axisnet_start(void)
{
	if (g_started)
		return;
	g_started = 1;
	InitializeCriticalSection(&g_logcs);
	InitializeCriticalSection(&g_pingcs);
	InitializeCriticalSection(&g_reccs);
	InitializeCriticalSection(&g_vmcs);
	InitializeCriticalSection(&hub.cs);
	hub.ls = hub.us = INVALID_SOCKET;
	load_config();
	real_connect = connect_native;
	real_CoCreateInstance = no_class;   /* (anything but DirectPlay: not here) */
	logf("axisnet (POSIX): %s mode, hub port %d, game-list port %d", g_local ? "local" : "server", g_hubport, g_mainport);
}

#define PLAT(ret, name, ...) ret WINAPI plat_##name(__VA_ARGS__) __asm__("_plat_" #name); ret WINAPI plat_##name(__VA_ARGS__)
/* the game's CoCreateInstance: DirectPlay and its lobby (anything else: none) */
PLAT(HRESULT, CoCreateInstance, REFCLSID clsid, void *outer, DWORD ctx, REFIID iid, void **out)
{
	axisnet_start();
	return hook_CoCreateInstance(clsid, outer, ctx, iid, out);
}
/* the game's connect: its address made this system's, then axisnet's (local mode: the game-list server is the
   built-in list), then the plain one */
PLAT(int, connect, SOCKET s, const void *name, int len)
{
	axisnet_start();
	struct sockaddr_in a;
	socklen_t n = net_native_addr(name, len, &a);
	return hook_connect(s, (const struct sockaddr *)&a, (int)n);
}
/* its ping: axisnet's (the round trip of a TCP connection to the game's host, as the game list shows it) */
PLAT(DWORD, IcmpSendEcho, HANDLE h, DWORD dest, void *req, WORD reqsize, void *opt, void *reply, DWORD replysize, DWORD timeout)
{
	axisnet_start();
	return hook_IcmpSendEcho(h, dest, req, reqsize, opt, reply, replysize, timeout);
}
#endif
