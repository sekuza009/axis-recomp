/* posix_net_test.c: plat/posix/net.c checked on Linux (run in WSL by tools/plat_tests/run_posix.sh), called as the
   game calls them ("_plat_<name>", stdcall on 32-bit, Windows' layouts). */
#define AXIS_PORTABLE 1
#include "../../src/plat/posix/net.c"
#include <stdio.h>

static int fails;
static void check(int ok, const char *what)
{
	printf("%s  %s\n", ok ? "PASS" : "FAIL", what);
	if (!ok)
		fails++;
}

extern int WINAPI g_socket(int, int, int) __asm__("_plat_socket");
extern int WINAPI g_connect(int, const void *, int) __asm__("_plat_connect");
extern int WINAPI g_send(uint32_t, const void *, int, int) __asm__("_plat_send");
extern int WINAPI g_recv(uint32_t, void *, int, int) __asm__("_plat_recv");
extern int WINAPI g_closesocket(uint32_t) __asm__("_plat_closesocket");
extern int WINAPI g_shutdown(uint32_t, int) __asm__("_plat_shutdown");
extern uint32_t WINAPI g_inet_addr(const char *) __asm__("_plat_inet_addr");
extern const char *WINAPI g_inet_ntoa(uint32_t) __asm__("_plat_inet_ntoa");
extern uint16_t WINAPI g_htons(uint32_t) __asm__("_plat_htons");
extern void *WINAPI g_gethostbyname(const char *) __asm__("_plat_gethostbyname");
extern int WINAPI g_WSAStartup(uint32_t, void *) __asm__("_plat_WSAStartup");
extern void *WINAPI g_CreateEventA(void *, int, int, const char *) __asm__("_plat_CreateEventA");
extern int WINAPI g_SetEvent(void *) __asm__("_plat_SetEvent");
extern uint32_t WINAPI g_Wait(uint32_t, void *const *, int, uint32_t) __asm__("_plat_WaitForMultipleObjects");
extern void *WINAPI g_CreateThread(void *, size_t, uint32_t (WINAPI *)(void *), void *, uint32_t, uint32_t *) __asm__("_plat_CreateThread");
extern int WINAPI g_CloseHandle(void *) __asm__("_plat_CloseHandle");
extern void *WINAPI g_GlobalAlloc(uint32_t, size_t) __asm__("_plat_GlobalAlloc");
extern void *WINAPI g_GlobalLock(void *) __asm__("_plat_GlobalLock");
extern int WINAPI g_GlobalUnlock(void *) __asm__("_plat_GlobalUnlock");
extern void *WINAPI g_GlobalHandle(const void *) __asm__("_plat_GlobalHandle");
extern void *WINAPI g_GlobalFree(void *) __asm__("_plat_GlobalFree");
extern void *WINAPI g_IcmpCreateFile(void) __asm__("_plat_IcmpCreateFile");
extern uint32_t WINAPI g_IcmpSendEcho(void *, uint32_t, const void *, uint16_t, void *, void *, uint32_t, uint32_t) __asm__("_plat_IcmpSendEcho");

static void *g_events[2];
static uint32_t WINAPI setter(void *p)   /* (the ping thread's shape: stdcall, one argument) */
{
	usleep(100000);
	g_SetEvent(g_events[(intptr_t)p]);
	return 7;
}
static int g_listener;
static void *echo_server(void *unused)   /* (a native server: the game only ever connects out) */
{
	(void)unused;
	int c = accept(g_listener, NULL, NULL);
	char b[64];
	ssize_t n = recv(c, b, sizeof b, 0);
	if (n > 0) send(c, b, (size_t)n, 0);
	close(c);
	return NULL;
}

int main(void)
{
	unsigned char wsa[400];
	check(g_WSAStartup(0x0101, wsa) == 0 && ((uint16_t *)wsa)[0] == 0x0101, "WSAStartup(1.1): 0");
	check(g_inet_addr("127.0.0.1") == htonl(0x7f000001) && !strcmp(g_inet_ntoa(htonl(0x0a000102)), "10.0.1.2"), "inet_addr / inet_ntoa");
	check(g_htons(2020) == htons(2020), "htons(2020)");

	g_listener = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in a;
	memset(&a, 0, sizeof a);
	a.sin_family = AF_INET;
	a.sin_addr.s_addr = htonl(0x7f000001);
	bind(g_listener, (struct sockaddr *)&a, sizeof a);
	socklen_t al = sizeof a;
	getsockname(g_listener, (struct sockaddr *)&a, &al);
	listen(g_listener, 1);
	pthread_t srv;
	pthread_create(&srv, NULL, echo_server, NULL);

	WinSockaddrIn w = { 2, a.sin_port, htonl(0x7f000001), { 0 } };   /* (as the game fills it: a 16-bit family) */
	int s = g_socket(2, 1, 6);
	check(s >= 0, "socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)");
	check(g_connect(s, &w, sizeof w) == 0, "connect with Windows' sockaddr_in to the local server");
	check(g_send((uint32_t)s, "axis-hello", 10, 0) == 10, "send 10 bytes");
	char back[32] = { 0 };
	int got = 0;
	for (int i = 0; i < 50 && got < 10; i++) {
		int n = g_recv((uint32_t)s, back + got, 10 - got, 0);
		if (n > 0) got += n; else if (n == 0) break;
	}
	check(got == 10 && !memcmp(back, "axis-hello", 10), "recv them back");
	check(g_shutdown((uint32_t)s, 2) == 0 && g_closesocket((uint32_t)s) == 0, "shutdown / closesocket");
	pthread_join(srv, NULL);
	close(g_listener);
	check(g_send((uint32_t)s, "x", 1, 0) < 0, "send on a closed socket: an error, no SIGPIPE");

	WinHostent *h = g_gethostbyname("localhost");
	check(h && h->addrtype == 2 && h->length == 4 && h->addrs[0] && !memcmp(h->addrs[0], "\x7f\x00\x00\x01", 4),
	      "gethostbyname(localhost): Windows' hostent, 127.0.0.1");
	check(g_gethostbyname("no-such-host.invalid") == NULL, "gethostbyname of an unknown name: NULL");

	g_events[0] = g_CreateEventA(NULL, 0, 0, NULL);
	g_events[1] = g_CreateEventA(NULL, 0, 0, NULL);
	check(g_Wait(2, g_events, 0, 50) == 0x102, "WaitForMultipleObjects with neither set: WAIT_TIMEOUT after 50 ms");
	uint32_t id = 0;
	void *t = g_CreateThread(NULL, 0, setter, (void *)(intptr_t)1, 0, &id);
	check(t != NULL && id != 0, "CreateThread (stdcall procedure, an id)");
	check(g_Wait(2, g_events, 0, 0xffffffffu) == 1, "the thread sets the second event: the wait returns 1");
	check(g_Wait(2, g_events, 0, 20) == 0x102, "auto-reset: it is clear again");
	g_SetEvent(g_events[0]);
	g_SetEvent(g_events[1]);
	check(g_Wait(2, g_events, 0, 0) == 0 && g_Wait(2, g_events, 0, 0) == 1, "both set: the first, then the second");
	check(g_CloseHandle(t) && g_CloseHandle(g_events[0]) && g_CloseHandle(g_events[1]), "CloseHandle of the thread and events");

	void *gh = g_GlobalAlloc(0x42, 100);   /* GHND */
	unsigned char *p = g_GlobalLock(gh);
	int zero = 1;
	for (int i = 0; i < 100; i++) zero &= p[i] == 0;
	check(gh && p && zero, "GlobalAlloc(GHND, 100) + GlobalLock: 100 zeroed bytes");
	check(g_GlobalHandle(p) == gh, "GlobalHandle(the pointer): the handle");
	check(g_GlobalUnlock(gh) == 0 && g_GlobalFree(gh) == NULL, "GlobalUnlock: 0 (unlocked); GlobalFree: NULL (freed)");

	unsigned char reply[64];
	uint32_t n = g_IcmpSendEcho(g_IcmpCreateFile(), htonl(0x7f000001), "ping", 4, NULL, reply, sizeof reply, 1000);
	printf("      ping 127.0.0.1: %s", n ? "answered" : "no ICMP socket allowed here (no answer, as an unreachable server)");
	if (n) printf(", %u ms", ((WinEchoReply *)reply)->rtt);
	printf("\n");
	check(n == 0 || ((WinEchoReply *)reply)->address == htonl(0x7f000001), "IcmpSendEcho: a reply from 127.0.0.1, or none");

	printf("%s: %d failed\n", fails ? "FAILED" : "ALL PASSED", fails);
	return fails != 0;
}
