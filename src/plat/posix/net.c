/* plat/posix/net.c: the network calls the game makes itself, for Linux, macOS and the like (portable build only; not
   built on Windows). Winsock is BSD sockets with Windows' shapes, so each import is answered under its own name
   ("_plat_<name>", as src/axis.h calls it), stdcall on 32-bit, keeping the Windows shapes the game reads:
   - sockets: socket / connect / bind / send / recv / shutdown / closesocket, the addresses as Windows lays them out
     (sockaddr_in with a 16-bit family: macOS's has a length byte first; hostent with 16-bit type and length),
     WSAStartup / WSACleanup (nothing to start), gethostbyname, gethostname, inet_addr, inet_ntoa, htons;
   - the ping thread's pieces (net_servers.c): CreateThread / ExitThread, events (CreateEventA, SetEvent, ResetEvent,
     auto- or manual-reset), WaitForMultipleObjects (any of them, or a timeout), CloseHandle of those;
   - the ICMP ping (IcmpCreateFile / IcmpSendEcho / IcmpCloseHandle): an echo over an unprivileged ICMP socket
     where the system allows it (macOS; Linux within net.ipv4.ping_group_range), else a raw one (root), else none;
   - the GlobalAlloc family that carries DirectPlay's messages: moveable blocks, zeroed when asked, locked to a pointer
     and found again from it (GlobalHandle).
   (DirectPlay itself - the sessions, the NET_ operations of plat.h - is a separate piece, PORTING.md.) */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <poll.h>
#include <pthread.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#if defined(__i386__)
#define WINAPI __attribute__((stdcall))
#else
#define WINAPI
#endif
#define PLAT(ret, name, ...) ret WINAPI plat_##name(__VA_ARGS__) __asm__("_plat_" #name); ret WINAPI plat_##name(__VA_ARGS__)

#ifdef MSG_NOSIGNAL
#define MSG_NOSIGNAL_ MSG_NOSIGNAL
#else
#define MSG_NOSIGNAL_ 0   /* (macOS: SO_NOSIGPIPE on the socket instead) */
#endif

/* ---- sockets ---- */
typedef struct { uint16_t family, port; uint32_t addr; uint8_t zero[8]; } WinSockaddrIn;   /* Windows' sockaddr_in */

/* the game's address (Windows' layout) as this system's (plat/posix/directplay.c uses it too) */
socklen_t net_native_addr(const void *win, int len, struct sockaddr_in *out);
socklen_t net_native_addr(const void *win, int len, struct sockaddr_in *out)
{
	WinSockaddrIn w;
	memset(&w, 0, sizeof w);
	memcpy(&w, win, len < (int)sizeof w ? (size_t)len : sizeof w);
	memset(out, 0, sizeof *out);
	out->sin_family = (sa_family_t)w.family;   /* (AF_INET is 2 everywhere) */
	out->sin_port = w.port;
	out->sin_addr.s_addr = w.addr;
	return sizeof *out;
}

PLAT(int, WSAStartup, uint32_t version, void *data)
{
	if (data) {   /* WSADATA: the version asked and the highest, a description */
		memset(data, 0, 400);
		((uint16_t *)data)[0] = (uint16_t)version;
		((uint16_t *)data)[1] = 0x0202;
	}
	return 0;
}
PLAT(int, WSACleanup, void) { return 0; }
static int g_wsaError;
PLAT(void, WSASetLastError, int e) { g_wsaError = e; }

PLAT(int, socket, int af, int type, int protocol)
{
	int s = socket(af, type, protocol);
#ifdef SO_NOSIGPIPE
	if (s >= 0) {
		int one = 1;
		setsockopt(s, SOL_SOCKET, SO_NOSIGPIPE, &one, sizeof one);
	}
#endif
	return s;
}
/* (the game's connect is axisnet's - plat/posix/directplay.c, as on Windows; this is the plain one under it) */
int net_connect_win(int s, const void *addr, int len);
int net_connect_win(int s, const void *addr, int len)
{
	struct sockaddr_in a;
	socklen_t n = net_native_addr(addr, len, &a);
	return connect(s, (struct sockaddr *)&a, n);
}
PLAT(int, bind, int s, const void *addr, int len)
{
	struct sockaddr_in a;
	socklen_t n = net_native_addr(addr, len, &a);
	return bind(s, (struct sockaddr *)&a, n);
}
PLAT(int, send, uint32_t s, const void *buf, int len, int flags)
{
	return (int)send((int)s, buf, (size_t)len, flags | MSG_NOSIGNAL_);   /* (a closed peer: an error, not SIGPIPE) */
}
PLAT(int, recv, uint32_t s, void *buf, int len, int flags) { return (int)recv((int)s, buf, (size_t)len, flags); }
PLAT(int, shutdown, uint32_t s, int how) { return shutdown((int)s, how); }   /* (SD_RECEIVE / SD_SEND / SD_BOTH: 0 / 1 / 2, as SHUT_*) */
PLAT(int, closesocket, uint32_t s) { return close((int)s); }
PLAT(uint32_t, inet_addr, const char *text) { return inet_addr(text); }
PLAT(const char *, inet_ntoa, uint32_t addr)
{
	struct in_addr a;
	a.s_addr = addr;
	return inet_ntoa(a);
}
PLAT(uint16_t, htons, uint32_t v) { return htons((uint16_t)v); }
PLAT(int, gethostname, char *name, int len) { return gethostname(name, (size_t)len); }

/* Windows' hostent: the address type and length are 16-bit */
typedef struct { char *name; char **aliases; int16_t addrtype, length; char **addrs; } WinHostent;
PLAT(void *, gethostbyname, const char *name)
{
	static WinHostent h;
	static char hostName[256], addrBytes[8][4];
	static char *addrList[9], *aliasList[1];
	struct addrinfo hints, *res = NULL;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	if (getaddrinfo(name, NULL, &hints, &res) != 0 || !res)
		return NULL;
	int n = 0;
	for (struct addrinfo *a = res; a && n < 8; a = a->ai_next) {
		uint32_t ip = ((struct sockaddr_in *)a->ai_addr)->sin_addr.s_addr;
		int dup = 0;
		for (int i = 0; i < n; i++)
			dup |= !memcmp(addrBytes[i], &ip, 4);
		if (!dup)
			memcpy(addrBytes[n++], &ip, 4);
	}
	freeaddrinfo(res);
	for (int i = 0; i < n; i++)
		addrList[i] = addrBytes[i];
	addrList[n] = NULL;
	aliasList[0] = NULL;
	strncpy(hostName, name, sizeof hostName - 1);
	h.name = hostName;
	h.aliases = aliasList;
	h.addrtype = AF_INET;
	h.length = 4;
	h.addrs = addrList;
	return &h;
}

/* (the 64-bit build: the records the game keeps a pointer to - threads, events, GlobalAlloc blocks - in its arena, and
   its threads on stacks there; the loader sets these, standalone/net64.c) */
void *(*g_platAlloc)(size_t size);
void (*g_platFree)(void *p);
void (*g_platRunThread)(uint32_t (WINAPI *proc)(void *), void *param);
static void *net_calloc(size_t n)
{
	if (!g_platAlloc)
		return calloc(1, n);
	void *p = g_platAlloc(n);
	if (p)
		memset(p, 0, n);
	return p;
}
static void net_free(void *p) { if (g_platFree) g_platFree(p); else free(p); }

/* ---- handles: threads and events (CloseHandle of either) ---- */
#define KIND_THREAD 0x54485244u
#define KIND_EVENT 0x45564e54u
typedef struct { uint32_t kind; } Handle;
typedef struct { Handle h; pthread_t t; uint32_t (WINAPI *proc)(void *); void *param; } Thread;
typedef struct { Handle h; int manual, signaled; } Event;
static pthread_mutex_t g_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_changed = PTHREAD_COND_INITIALIZER;   /* (any event set: the waiters look again) */

static void *thread_start(void *p)
{
	Thread *t = p;
	if (g_platRunThread) {
		g_platRunThread(t->proc, t->param);
		return NULL;
	}
	uint32_t r = t->proc(t->param);
	return (void *)(uintptr_t)r;
}
PLAT(void *, CreateThread, void *security, size_t stack, uint32_t (WINAPI *proc)(void *), void *param, uint32_t flags, uint32_t *id)
{
	(void)security; (void)flags;
	Thread *t = net_calloc(sizeof *t);
	if (!t)
		return NULL;
	t->h.kind = KIND_THREAD;
	t->proc = proc;
	t->param = param;
	pthread_attr_t a;
	pthread_attr_init(&a);
	if (stack)
		pthread_attr_setstacksize(&a, stack < 65536 ? 65536 : stack);
	pthread_attr_setdetachstate(&a, PTHREAD_CREATE_DETACHED);
	int e = pthread_create(&t->t, &a, thread_start, t);
	pthread_attr_destroy(&a);
	if (e) {
		net_free(t);
		return NULL;
	}
	if (id)
		*id = (uint32_t)(uintptr_t)t;
	return t;
}
PLAT(void, ExitThread, uint32_t code) { pthread_exit((void *)(uintptr_t)code); }

PLAT(void *, CreateEventA, void *security, int manualReset, int initial, const char *name)
{
	(void)security; (void)name;
	Event *e = net_calloc(sizeof *e);
	if (!e)
		return NULL;
	e->h.kind = KIND_EVENT;
	e->manual = manualReset != 0;
	e->signaled = initial != 0;
	return e;
}
PLAT(int, SetEvent, void *h)
{
	Event *e = h;
	if (!e || e->h.kind != KIND_EVENT)
		return 0;
	pthread_mutex_lock(&g_lock);
	e->signaled = 1;
	pthread_cond_broadcast(&g_changed);
	pthread_mutex_unlock(&g_lock);
	return 1;
}
PLAT(int, ResetEvent, void *h)
{
	Event *e = h;
	if (!e || e->h.kind != KIND_EVENT)
		return 0;
	pthread_mutex_lock(&g_lock);
	e->signaled = 0;
	pthread_mutex_unlock(&g_lock);
	return 1;
}
/* any one of the events (the first set, in order; an auto-reset one cleared), or 0x102 (WAIT_TIMEOUT) after ms
   (0xffffffff: none); waiting for all of them is not something the game does */
PLAT(uint32_t, WaitForMultipleObjects, uint32_t count, void *const *handles, int all, uint32_t ms)
{
	(void)all;
	struct timespec until;
	if (ms != 0xffffffffu) {
		clock_gettime(CLOCK_REALTIME, &until);
		until.tv_sec += ms / 1000;
		until.tv_nsec += (long)(ms % 1000) * 1000000L;
		if (until.tv_nsec >= 1000000000L) {
			until.tv_sec++;
			until.tv_nsec -= 1000000000L;
		}
	}
	pthread_mutex_lock(&g_lock);
	for (;;) {
		for (uint32_t i = 0; i < count; i++) {
			Event *e = handles[i];
			if (e && e->h.kind == KIND_EVENT && e->signaled) {
				if (!e->manual)
					e->signaled = 0;
				pthread_mutex_unlock(&g_lock);
				return i;   /* WAIT_OBJECT_0 + i */
			}
		}
		if (ms == 0xffffffffu)
			pthread_cond_wait(&g_changed, &g_lock);
		else if (pthread_cond_timedwait(&g_changed, &g_lock, &until) == ETIMEDOUT) {
			pthread_mutex_unlock(&g_lock);
			return 0x102;
		}
	}
}
PLAT(int, CloseHandle, void *h)
{
	Handle *x = h;
	if (!x)
		return 0;
	if (x->kind == KIND_EVENT) {
		x->kind = 0;
		net_free(x);
		return 1;
	}
	if (x->kind == KIND_THREAD) {
		x->kind = 0;   /* (the thread runs on detached; its record is kept for it) */
		return 1;
	}
	return 0;
}

/* ---- the ICMP ping ---- */
typedef struct { uint32_t address, status, rtt; uint16_t size, reserved; void *data; uint8_t options[8]; } WinEchoReply;
static uint16_t checksum(const void *p, size_t n)
{
	const uint8_t *b = p;
	uint32_t s = 0;
	for (size_t i = 0; i + 1 < n; i += 2)
		s += (uint32_t)(b[i] << 8 | b[i + 1]);
	if (n & 1)
		s += (uint32_t)b[n - 1] << 8;
	while (s >> 16)
		s = (s & 0xffff) + (s >> 16);
	return htons((uint16_t)~s);
}
PLAT(void *, IcmpCreateFile, void) { return (void *)(uintptr_t)0x49434d50; }
PLAT(int, IcmpCloseHandle, void *h) { (void)h; return 1; }
/* (the game's IcmpSendEcho is axisnet's, which times a TCP connection to the game's host as on Windows; this real
   ICMP echo is kept for a host or a later use) */
uint32_t net_icmp_echo(void *h, uint32_t dest, const void *data, uint16_t size, void *options, void *reply, uint32_t replySize, uint32_t timeout);
uint32_t net_icmp_echo(void *h, uint32_t dest, const void *data, uint16_t size, void *options, void *reply, uint32_t replySize, uint32_t timeout)
{
	(void)h; (void)options;
	int raw = 0, s = socket(AF_INET, SOCK_DGRAM, IPPROTO_ICMP);   /* (unprivileged: the system fills the id) */
	if (s < 0) {
		s = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
		raw = 1;
	}
	if (s < 0)
		return 0;
	unsigned char pkt[8 + 512];
	size_t n = size > 512 ? 512 : size;
	memset(pkt, 0, sizeof pkt);
	pkt[0] = 8;   /* echo request */
	uint16_t id = (uint16_t)getpid(), seq = 1;
	pkt[4] = (uint8_t)(id >> 8); pkt[5] = (uint8_t)id; pkt[6] = (uint8_t)(seq >> 8); pkt[7] = (uint8_t)seq;
	if (data && n)
		memcpy(pkt + 8, data, n);
	uint16_t c = checksum(pkt, 8 + n);
	memcpy(pkt + 2, &c, 2);
	struct sockaddr_in to;
	memset(&to, 0, sizeof to);
	to.sin_family = AF_INET;
	to.sin_addr.s_addr = dest;
	struct timeval t0, t1;
	gettimeofday(&t0, NULL);
	if (sendto(s, pkt, 8 + n, 0, (struct sockaddr *)&to, sizeof to) < 0) {
		close(s);
		return 0;
	}
	uint32_t got = 0;
	for (;;) {
		gettimeofday(&t1, NULL);
		long spent = (t1.tv_sec - t0.tv_sec) * 1000L + (t1.tv_usec - t0.tv_usec) / 1000L;
		if (spent >= (long)timeout)
			break;
		struct pollfd p = { s, POLLIN, 0 };
		if (poll(&p, 1, (int)(timeout - spent)) <= 0)
			break;
		unsigned char in[1024];
		struct sockaddr_in from;
		socklen_t fl = sizeof from;
		ssize_t r = recvfrom(s, in, sizeof in, 0, (struct sockaddr *)&from, &fl);
		if (r <= 0)
			continue;
		const unsigned char *icmp = in;
		if (raw) {   /* (a raw socket gives the IP header too) */
			size_t ihl = (size_t)(in[0] & 15) * 4;
			if ((size_t)r < ihl + 8)
				continue;
			icmp = in + ihl;
		}
		if (icmp[0] != 0 || from.sin_addr.s_addr != dest)   /* an echo reply from there */
			continue;
		gettimeofday(&t1, NULL);
		if (reply && replySize >= sizeof(WinEchoReply)) {
			WinEchoReply *e = reply;
			memset(e, 0, sizeof *e);
			e->address = dest;
			e->status = 0;   /* IP_SUCCESS */
			e->rtt = (uint32_t)((t1.tv_sec - t0.tv_sec) * 1000L + (t1.tv_usec - t0.tv_usec) / 1000L);
			e->size = (uint16_t)n;
		}
		got = 1;
		break;
	}
	close(s);
	return got;
}

/* ---- the GlobalAlloc family: a block behind a small header; the handle is the header, Lock gives the bytes ---- */
#define GLOBAL_MAGIC 0x474c4f42u
typedef struct { uint32_t magic, size, locks, pad; } Global;
PLAT(void *, GlobalAlloc, uint32_t flags, size_t size)
{
	Global *g = net_calloc(sizeof(Global) + size);   /* (zeroed whether GMEM_ZEROINIT or not) */
	if (!g)
		return NULL;
	g->magic = GLOBAL_MAGIC;
	g->size = (uint32_t)size;
	g->locks = 0;
	return g;
}
PLAT(void *, GlobalLock, void *h)
{
	Global *g = h;
	if (!g || g->magic != GLOBAL_MAGIC)
		return NULL;
	g->locks++;
	return g + 1;
}
PLAT(int, GlobalUnlock, void *h)
{
	Global *g = h;
	if (!g || g->magic != GLOBAL_MAGIC || !g->locks)
		return 0;
	return --g->locks != 0;   /* (nonzero while still locked) */
}
PLAT(void *, GlobalHandle, const void *p)
{
	if (!p)
		return NULL;
	Global *g = (Global *)p - 1;
	return g->magic == GLOBAL_MAGIC ? g : NULL;
}
PLAT(void *, GlobalFree, void *h)
{
	Global *g = h;
	if (!g || g->magic != GLOBAL_MAGIC)
		return h;   /* (not one of ours: as Windows, the handle back means it failed) */
	g->magic = 0;
	net_free(g);
	return NULL;
}
#endif
