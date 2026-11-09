/* net64.c: the network of the 64-bit build (PORTING.md, stage 6), on Windows x64 and on Linux / macOS:

   - axisnet's DirectPlay (axisnet_dp.c: the sessions, the hub, LAN discovery, the built-in game list, the ping) built
     in, as src/plat/posix/directplay.c builds it for the 32-bit POSIX tests - the same protocol, so a 64-bit copy plays
     with 32-bit Windows players and the DServer relay (its wire records hold only fixed-size fields);
   - plat.h's NET_ operations for the game, translating DirectPlay's records between the game's 32-bit layout (built in
     its memory: a pointer is an address in g_arena) and axisnet's own: the session description (hosting, joining, the
     session list's callback), the player name (creating, asking), the connection list's names. What the game reads of
     the system messages (the first four words) has no pointer before it, and the compound address's elements have the
     same layout on 64-bit, so those pass as they are. The DirectPlay objects the game keeps are numbers here;
   - on Windows, the game's own socket, thread, event and ping calls (the lobby and game server connections, the ping
     thread) with the game's prototypes: threads run on arena stacks, the handles the game keeps are arena records. On
     Linux / macOS src/plat/posix/net.c answers those (its records in the arena: the hooks set here). */
#if defined(__x86_64__) || defined(__aarch64__)
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <objbase.h>
#include <oleauto.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#define RELOC(a) (a)
#else
#define _POSIX_C_SOURCE 200809L
#define _DEFAULT_SOURCE
#define _DARWIN_C_SOURCE
#define AXIS_PORTABLE 1
#include "../src/plat/posix/win32_compat.h"
#define AXISNET_POSIX 1
#endif
#define AXIS_NATIVE 1
#include "../axisnet_dp.c"

typedef uint32_t u32;
typedef uint8_t u8;
#define DPERR_INVALIDPARAMS_ E_INVALIDARG
#ifndef E_OUTOFMEMORY
#define E_OUTOFMEMORY ((HRESULT)0x8007000eu)
#endif
extern unsigned char *g_arena;
void *arena_malloc(size_t n);
void arena_free(void *p);
void arena_callOnNewStack(void (*fn)(void *), void *arg, u32 size);
void hlog(const char *fmt, ...);
#define AP_(v) ((void *)((v) ? g_arena + (u32)(v) : NULL))
#define AV_(p) ((p) ? (u32)((const u8 *)(p) - g_arena) : 0u)

/* ---- the start (axisnet_attach's network part) */
static int g_started;
#ifndef _WIN32
static HRESULT WINAPI no_class(REFCLSID c, void *o, DWORD x, REFIID i, void **p) { (void)c; (void)o; (void)x; (void)i; if (p) *p = NULL; return REGDB_E_CLASSNOTREG; }
static int WSAAPI connect_native(SOCKET s, const struct sockaddr *a, int len) { return connect(s, a, (socklen_t)len); }
#endif
static void net_start(void)
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
#ifdef _WIN32
	real_connect = connect;
	wsa_init();
#else
	real_connect = connect_native;
	real_CoCreateInstance = no_class;
#endif
	logf("axisnet (64-bit build): %s mode, hub port %d, game-list port %d", g_local ? "local" : "server", g_hubport, g_mainport);
}

/* ---- the objects the game keeps: numbers (arena addresses above everything mapped) for axisnet's DP / Lobby */
#define OBJ_BASE 0xfe500000u
#define OBJ_MAX 64
static void *g_objs[OBJ_MAX];
static u32 keep_obj(void *o)
{
	for (int i = 0; i < OBJ_MAX; i++)
		if (!g_objs[i]) {
			g_objs[i] = o;
			return OBJ_BASE + (u32)i * 16;
		}
	return 0;
}
static void *obj_of(const void *p)
{
	u32 a = AV_(p) - OBJ_BASE, i = a / 16;
	return a % 16 == 0 && i < OBJ_MAX ? g_objs[i] : NULL;
}
static void drop_obj(const void *p)
{
	u32 a = AV_(p) - OBJ_BASE, i = a / 16;
	if (a % 16 == 0 && i < OBJ_MAX)
		g_objs[i] = NULL;
}
#define DPOBJ(p) ((DP *)obj_of(p))
#define LBOBJ(p) ((Lobby *)obj_of(p))

/* the game's DPSESSIONDESC2 (32-bit: the names are addresses) */
typedef struct { u32 size, flags; u8 instance[16], application[16]; u32 maxPlayers, players, name, password, reserved1,
                 reserved2, user1, user2, user3, user4; } SD32;
static void sd_from32(DPSD2 *d, const SD32 *s)
{
	memset(d, 0, sizeof *d);
	d->dwSize = sizeof *d;
	d->dwFlags = s->flags;
	memcpy(&d->guidInstance, s->instance, 16);
	memcpy(&d->guidApplication, s->application, 16);
	d->dwMaxPlayers = s->maxPlayers;
	d->dwCurrentPlayers = s->players;
	d->lpszSessionNameA = AP_(s->name);
	d->lpszPasswordA = AP_(s->password);
	d->dwUser1 = s->user1; d->dwUser2 = s->user2; d->dwUser3 = s->user3; d->dwUser4 = s->user4;
}

long plat_netCreate(u32 *out)
{
	net_start();
	*out = keep_obj(new_dp());
	return *out ? DP_OK : E_OUTOFMEMORY;
}
long plat_netLobbyCreate(u32 *out)
{
	net_start();
	Lobby *l = calloc(1, sizeof *l);
	l->vtbl = lobby_vtbl;
	l->ref = 1;
	*out = keep_obj(l);
	return *out ? DP_OK : E_OUTOFMEMORY;
}
long plat_netRelease(void *o)
{
	void *x = obj_of(o);
	if (!x)
		return 0;
	drop_obj(o);
	return (long)((ULONG (WINAPI *)(void *))(*(const void *const **)x)[2])(x);   /* (Release: DP_Release / LB_Release) */
}
long plat_netClose(void *p) { DP *dp = DPOBJ(p); return dp ? (long)DP_Close(dp) : (long)DPERR_INVALIDPARAMS_; }
u32 plat_netDestroyPlayer(void *p, u32 id) { DP *dp = DPOBJ(p); return dp ? (u32)DP_DestroyPlayer(dp, id) : 0; }

/* the session list: each session handed to the game's callback in its layout, the name in the arena (the game copies
   it) */
typedef int (WINAPI *GameSessCb)(const void *desc, void *timeout, u32 flags, void *ctx);
static GameSessCb g_sessCb;
static SD32 *g_sd32;
static char *g_sdName;
static BOOL WINAPI sess_cb(const DPSD2 *sd, DWORD *timeout, DWORD flags, void *ctx)
{
	if (!g_sd32) {
		g_sd32 = arena_malloc(sizeof *g_sd32);
		g_sdName = arena_malloc(NAMELEN + 1);
	}
	if (!sd)
		return g_sessCb(NULL, timeout, flags, ctx);
	SD32 *s = g_sd32;
	memset(s, 0, sizeof *s);
	s->size = sizeof *s;
	s->flags = sd->dwFlags;
	memcpy(s->instance, &sd->guidInstance, 16);
	memcpy(s->application, &sd->guidApplication, 16);
	s->maxPlayers = sd->dwMaxPlayers;
	s->players = sd->dwCurrentPlayers;
	snprintf(g_sdName, NAMELEN + 1, "%s", sd->lpszSessionNameA ? sd->lpszSessionNameA : "");
	s->name = AV_(g_sdName);
	s->user1 = sd->dwUser1; s->user2 = sd->dwUser2; s->user3 = sd->dwUser3; s->user4 = sd->dwUser4;
	return g_sessCb(s, timeout, flags, ctx);
}
int plat_netEnumSessions(void *p, void *desc, void *callback)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (int)DPERR_INVALIDPARAMS_;
	DPSD2 sd;
	sd_from32(&sd, desc);
	g_sessCb = (GameSessCb)callback;
	return (int)DP_EnumSessions(dp, &sd, 0, sess_cb, NULL, 0x12);   /* (the game's: no time-out, async, all) */
}
int plat_netOpen(void *p, void *desc, u32 flags)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (int)DPERR_INVALIDPARAMS_;
	DPSD2 sd;
	sd_from32(&sd, desc);
	return (int)DP_Open(dp, &sd, flags);
}

/* players: the game's DPNAME (dwSize, dwFlags, the two names' addresses) */
int plat_netCreatePlayer(void *p, u32 *id, void *name)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (int)DPERR_INVALIDPARAMS_;
	const u32 *n = name;
	DPNAME_ dn = { sizeof dn, 0, n ? AP_(n[2]) : NULL, n ? AP_(n[3]) : NULL };
	DWORD got = 0;
	HRESULT r = DP_CreatePlayer(dp, &got, n ? &dn : NULL, NULL, NULL, 0, 0);
	*id = got;
	return (int)r;
}
int plat_netGetPlayerName(void *p, u32 id, void *name, u32 *size)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (int)DPERR_INVALIDPARAMS_;
	BYTE tmp[sizeof(DPNAME_) + 2 * NAMELEN + 2];
	DWORD n = sizeof tmp;
	HRESULT r = DP_GetPlayerName(dp, id, tmp, &n);
	if (r != DP_OK)
		return (int)r;
	const DPNAME_ *dn = (const DPNAME_ *)tmp;
	const char *s = dn->lpszShortNameA ? dn->lpszShortNameA : "", *l = dn->lpszLongNameA ? dn->lpszLongNameA : "";
	u32 need = 16 + (u32)strlen(s) + 1 + (u32)strlen(l) + 1;
	if (!name || *size < need) {
		*size = need;
		return (int)DPERR_BUFFERTOOSMALL;
	}
	u32 *o = name;
	char *q = (char *)name + 16;
	o[0] = 16;
	o[1] = 0;
	strcpy(q, s);
	o[2] = AV_(q);
	q += strlen(s) + 1;
	strcpy(q, l);
	o[3] = dn->lpszLongNameA ? AV_(q) : 0;
	*size = need;
	return DP_OK;
}

/* the connections (TCP/IP, IPX): each given to the game's callback with its name in the game's layout */
typedef u32 (WINAPI *GameConnCb)(const void *guid, const void *conn, u32 size, const u32 *name, u32 flags, void *ctx);
static GameConnCb g_connCb;
static BOOL WINAPI conn_cb(const GUID *guid, void *conn, DWORD size, const DPNAME_ *name, DWORD flags, void *ctx)
{
	static u32 *n32;
	static char *names;
	if (!n32) {
		n32 = arena_malloc(16);
		names = arena_malloc(2 * 128);
	}
	snprintf(names, 128, "%s", name && name->lpszShortNameA ? name->lpszShortNameA : "");
	snprintf(names + 128, 128, "%s", name && name->lpszLongNameA ? name->lpszLongNameA : "");
	n32[0] = 16;
	n32[1] = 0;
	n32[2] = AV_(names);
	n32[3] = name && name->lpszLongNameA ? AV_(names + 128) : 0;
	return g_connCb(guid, conn, size, n32, flags, ctx) != 0;
}
int plat_netEnumConnections(void *p, void *callback)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (int)DPERR_INVALIDPARAMS_;
	g_connCb = (GameConnCb)callback;
	return (int)DP_EnumConnections(dp, NULL, conn_cb, NULL, 0);
}

/* the lobby: axisnet's is never lobbied (the launcher's "-net" start has no settings to give) */
int plat_netLobbyGetConnection(void *l, void *buffer, u32 *size)
{
	Lobby *lb = LBOBJ(l);
	DWORD n = size ? *size : 0;
	HRESULT r = lb ? LB_GetConnectionSettings(lb, 0, buffer, &n) : DPERR_NOTLOBBIED;
	if (size)
		*size = n;
	return (int)r;
}
int plat_netLobbySetConnection(void *l, void *connection) { (void)l; (void)connection; return (int)DPERR_UNSUPPORTED; }
int plat_netLobbyConnect(void *l, u32 *out) { (void)l; *out = 0; return (int)DPERR_UNSUPPORTED; }
int plat_netLobbyAddress(void *l, void *elements, u32 n, void *block, u32 *size)
{
	Lobby *lb = LBOBJ(l);
	if (!lb)
		return (int)DPERR_INVALIDPARAMS_;
	DWORD s = *size;
	HRESULT r = LB_CreateCompoundAddress(lb, elements, n, block, &s);   /* (the elements: the same layout on 64-bit) */
	*size = s;
	return (int)r;
}
int plat_netInitConnection(void *p, void *connection) { DP *dp = DPOBJ(p); return dp ? (int)DP_InitializeConnection(dp, connection, 0) : (int)DPERR_INVALIDPARAMS_; }
int plat_netGetCaps(void *p, u32 *caps) { DP *dp = DPOBJ(p); return dp ? (int)DP_GetCaps(dp, (DPCAPS_ *)caps, 0) : (int)DPERR_INVALIDPARAMS_; }
long plat_netReceive(void *p, u32 *from, u32 *to, u32 flags, void *data, u32 *size)
{
	DP *dp = DPOBJ(p);
	if (!dp)
		return (long)DPERR_INVALIDPARAMS_;
	DWORD f = from ? *from : 0, t = to ? *to : 0, s = size ? *size : 0;
	HRESULT r = DP_Receive(dp, &f, &t, flags, data, &s);
	if (from) *from = f;
	if (to) *to = t;
	if (size) *size = s;
	return (long)r;
}
long plat_netSend(void *p, u32 from, u32 to, u32 flags, const void *data, u32 size)
{
	DP *dp = DPOBJ(p);
	return dp ? (long)DP_Send(dp, from, to, flags, (void *)data, size) : (long)DPERR_INVALIDPARAMS_;
}

/* ---- the ping (the game's IcmpSendEcho): axisnet's round trip, the reply in the game's 32-bit ICMP_ECHO_REPLY layout
   (Address, Status, RoundTripTime, DataSize / Reserved, Data's address, Ttl .. OptionsSize, OptionsData) */
static u32 game_ping(u32 dest, void *req, uint16_t reqsize, void *reply, u32 replysize)
{
	net_start();
	DWORD rtt = 0;
	if (!reply || replysize < 28u + reqsize || !ping_cached(dest, &rtt))
		return 0;
	u32 *r = reply;
	memset(r, 0, 28);
	r[0] = dest;
	r[2] = rtt ? rtt : 1;
	r[3] = reqsize;
	r[4] = AV_((u8 *)reply + 28);
	((u8 *)reply)[20] = 128;   /* Ttl */
	if (reqsize && req)
		memcpy((u8 *)reply + 28, req, reqsize);
	return 1;
}

#ifdef _WIN32
/* ---- Windows: the game's own network calls (its prototypes) */
static int w_WSAStartup(u32 version, void *data)
{
	WSADATA w;
	int r = WSAStartup((WORD)version, &w);
	if (data) {   /* (the game's 32-bit WSADATA: versions, then the two texts) */
		memset(data, 0, 0x190);
		memcpy(data, &w, 4);
		memcpy((u8 *)data + 4, w.szDescription, 257);
		memcpy((u8 *)data + 4 + 257, w.szSystemStatus, 129);
	}
	return r;
}
static int w_WSACleanup(void) { return WSACleanup(); }
static void w_WSASetLastError(int e) { WSASetLastError(e); }
static int w_socket(int af, int type, int protocol)
{
	SOCKET s = socket(af, type, protocol);
	return s == INVALID_SOCKET ? -1 : (int)s;   /* (Windows' socket numbers are small: they fit the game's 32 bits) */
}
static int w_bind(int s, void *addr, int len) { return bind((SOCKET)(u32)s, addr, len); }
static int w_connect(int s, void *addr, int len) { net_start(); return hook_connect((SOCKET)(u32)s, addr, len); }
static int w_send(u32 s, const void *b, int n, int f) { return send((SOCKET)s, b, n, f); }
static int w_recv(u32 s, void *b, int n, int f) { return recv((SOCKET)s, b, n, f); }
static int w_shutdown(u32 s, int how) { return shutdown((SOCKET)s, how); }
static int w_closesocket(u32 s) { return closesocket((SOCKET)s); }
static u32 w_inet_addr(const char *t) { return inet_addr(t); }
static const char *w_inet_ntoa(u32 a) { struct in_addr i; i.s_addr = a; return inet_ntoa(i); }
static uint16_t w_htons(u32 v) { return htons((u_short)v); }
static int w_gethostname(char *n, int len) { return gethostname(n, len); }
static void *w_gethostbyname(const char *n) { return gethostbyname(n); }   /* (read in place: the game's HostEnt is this system's) */

/* threads and events: records in the arena (the game keeps their addresses), the system's handle inside */
#define REC_THREAD 0x54485244u
#define REC_EVENT 0x45564e54u
typedef struct { u32 kind, pad; HANDLE h; DWORD (WINAPI *proc)(void *); void *param; } Rec;
static Rec *rec_of(void *p)
{
	if ((uintptr_t)p >> 32 == 0)   /* (a handle passed as its 32-bit number) */
		p = AP_((u32)(uintptr_t)p);
	Rec *r = p;
	return r && AV_(r) < 0xfe000000u && (r->kind == REC_THREAD || r->kind == REC_EVENT) ? r : NULL;
}
static void run_proc(void *a) { Rec *r = a; r->proc(r->param); }
static DWORD WINAPI thread_entry(void *a)
{
	arena_callOnNewStack(run_proc, a, 0x100000);   /* (the game's locals' addresses go into its records) */
	return 0;
}
static void *w_CreateThread(void *sec, u32 stack, void *proc, void *param, u32 flags, u32 *id)
{
	(void)sec; (void)stack;
	Rec *r = arena_malloc(sizeof *r);
	if (!r)
		return NULL;
	memset(r, 0, sizeof *r);
	r->kind = REC_THREAD;
	r->proc = (DWORD (WINAPI *)(void *))proc;
	r->param = param;
	DWORD tid = 0;
	r->h = CreateThread(NULL, 0, thread_entry, r, flags, &tid);
	if (!r->h) {
		arena_free(r);
		return NULL;
	}
	if (id)
		*id = tid;
	return r;
}
static void w_ExitThread(u32 code) { ExitThread(code); }
static void *w_CreateEventA(void *sec, int manual, int initial, void *name)
{
	(void)sec; (void)name;
	Rec *r = arena_malloc(sizeof *r);
	if (!r)
		return NULL;
	memset(r, 0, sizeof *r);
	r->kind = REC_EVENT;
	r->h = CreateEventA(NULL, manual, initial, NULL);
	return r;
}
static int w_SetEvent(void *e) { Rec *r = rec_of(e); return r ? SetEvent(r->h) : 0; }
static int w_ResetEvent(void *e) { Rec *r = rec_of(e); return r ? ResetEvent(r->h) : 0; }
static u32 w_WaitForMultipleObjects(u32 n, void *const *handles, int all, u32 ms)
{
	HANDLE h[16];
	if (n > 16)
		n = 16;
	for (u32 i = 0; i < n; i++) {
		Rec *r = rec_of(handles[i]);
		h[i] = r ? r->h : NULL;
	}
	return WaitForMultipleObjects(n, h, all, ms);
}
static int w_CloseHandle(void *x)
{
	Rec *r = rec_of(x);
	if (!r)
		return 0;
	CloseHandle(r->h);
	int event = r->kind == REC_EVENT;
	r->kind = 0;
	if (event)
		arena_free(r);   /* (a thread's record stays: its thread may still run on it) */
	return 1;
}
static void *w_IcmpCreateFile(void) { return AP_(0xfe4f0000u); }
static int w_IcmpCloseHandle(void *h) { (void)h; return 1; }
static u32 w_IcmpSendEcho(void *h, u32 dest, void *req, uint16_t reqsize, void *opt, void *reply, u32 replysize, u32 timeout)
{
	(void)h; (void)opt; (void)timeout;
	return game_ping(dest, req, reqsize, reply, replysize);
}

int net64_install(void **(*slot)(const char *name))
{
	int n = 0;
#define SET(name, f) do { void **p = slot(#name); if (p) { *p = (void *)(f); n++; } } while (0)
	SET(WSAStartup, w_WSAStartup); SET(WSACleanup, w_WSACleanup); SET(WSASetLastError, w_WSASetLastError);
	SET(socket, w_socket); SET(bind, w_bind); SET(connect, w_connect); SET(send, w_send); SET(recv, w_recv);
	SET(shutdown, w_shutdown); SET(closesocket, w_closesocket); SET(inet_addr, w_inet_addr); SET(inet_ntoa, w_inet_ntoa);
	SET(htons, w_htons); SET(gethostname, w_gethostname); SET(gethostbyname, w_gethostbyname);
	SET(CreateThread, w_CreateThread); SET(ExitThread, w_ExitThread); SET(CreateEventA, w_CreateEventA);
	SET(SetEvent, w_SetEvent); SET(ResetEvent, w_ResetEvent); SET(WaitForMultipleObjects, w_WaitForMultipleObjects);
	SET(CloseHandle, w_CloseHandle); SET(IcmpCreateFile, w_IcmpCreateFile); SET(IcmpCloseHandle, w_IcmpCloseHandle);
	SET(IcmpSendEcho, w_IcmpSendEcho);
#undef SET
	return n;
}
#else
/* ---- Linux / macOS: the game's connect and ping (the rest: src/plat/posix/net.c, its records in the arena) */
socklen_t net_native_addr(const void *win, int len, struct sockaddr_in *out);   /* plat/posix/net.c */
#define PLAT(ret, name, ...) ret plat_##name(__VA_ARGS__) __asm__("_plat_" #name); ret plat_##name(__VA_ARGS__)
PLAT(int, connect, SOCKET s, const void *name, int len)
{
	net_start();
	struct sockaddr_in a;
	socklen_t n = net_native_addr(name, len, &a);
	return hook_connect(s, (const struct sockaddr *)&a, (int)n);
}
PLAT(DWORD, IcmpSendEcho, HANDLE h, DWORD dest, void *req, WORD reqsize, void *opt, void *reply, DWORD replysize, DWORD timeout)
{
	(void)h; (void)opt; (void)timeout;
	return game_ping(dest, req, reqsize, reply, replysize);
}
extern void *(*g_platAlloc)(size_t);
extern void (*g_platFree)(void *);
extern void (*g_platRunThread)(uint32_t (*proc)(void *), void *param);
typedef struct { uint32_t (*proc)(void *); void *param; } ThreadCall;
static void run_proc(void *a) { ThreadCall *c = a; c->proc(c->param); }
static void run_thread(uint32_t (*proc)(void *), void *param)
{
	ThreadCall c = { proc, param };
	arena_callOnNewStack(run_proc, &c, 0x100000);
}
int net64_install(void **(*slot)(const char *name))
{
	(void)slot;
	g_platAlloc = arena_malloc;
	g_platFree = arena_free;
	g_platRunThread = run_thread;
	return 0;
}
#endif
#endif
