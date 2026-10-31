/* axisnet - DirectPlay 4 replacement for Axis (Jamie System, 2001).
 *
 * Built into AxisGL.exe (and AxisD3D/AxisSavage): a TLS callback in the exe writes this DLL to
 * %TEMP% and loads it before the game starts. On load it hooks four imports of the game:
 *   CoCreateInstance - CLSID_DirectPlay / CLSID_DirectPlayLobby return the objects below, so the
 *                      Windows DirectPlay feature isn't needed.
 *   IcmpSendEcho     - "ping" in game lists measures the round trip to the game's host.
 *   connect          - (local mode) the game-list server connection goes to a built-in list that
 *                      finds games on the LAN, so SEARCH TCP works without any server.
 * It also replaces the game's movie routine (ending movie after mission 15, found by signature):
 * the original leaves the MCI window style uninitialised, ignores errors and busy-waits without
 * handling messages after the game window is already destroyed, which crashed or hung the game.
 *
 * Modes (axisnet.ini next to the exe, section [net]):
 *   mode=local  (default) the player who hosts runs the session hub inside his own game
 *               (TCP port hubport=2300, opened on the router with UPnP when possible, address
 *               copied to the clipboard). Others join with DIRECT IP, or SEARCH TCP on a LAN.
 *   mode=server all traffic goes through a DServer relay (server=, port=; default: the game-list
 *               server picked in AxisPlay.exe) - nobody needs open ports except the server.
 *
 * Hub/relay protocol (TCP): client sends "AXNR" + u32 version, then frames
 *   u32 length (of type + payload), u8 type, payload.
 * LAN discovery (UDP discport=2301): "AXNQ" -> "AXNB" u16 hubport u16 0, main record[0x5b], session.
 */
#define WIN32_LEAN_AND_MEAN
#define COBJMACROS
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <objbase.h>
#include <oleauto.h>
#include <mmsystem.h>
#include <digitalv.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "iv32/iv32.h"

/* ------------------------------------------------------------------ DirectPlay definitions */
#define DPH(c) ((HRESULT)(0x88770000u + (c)))
#define DP_OK                    S_OK
#define DPERR_ALREADYINITIALIZED DPH(5)
#define DPERR_BUFFERTOOSMALL     DPH(30)
#define DPERR_CANTADDPLAYER      DPH(40)
#define DPERR_CANTCREATESESSION  DPH(70)
#define DPERR_INVALIDPLAYER      DPH(150)
#define DPERR_NOCONNECTION       DPH(170)
#define DPERR_NOMESSAGES         DPH(190)
#define DPERR_NOSESSIONS         DPH(220)
#define DPERR_TIMEOUT            DPH(240)
#define DPERR_INVALIDPASSWORD    DPH(360)
#define DPERR_NOTLOBBIED         DPH(1070)
#define DPERR_UNSUPPORTED        E_NOTIMPL

#define DPID_SYSMSG      0
#define DPID_ALLPLAYERS  0
#define DPOPEN_JOIN      1
#define DPOPEN_CREATE    2
#define DPRECEIVE_TOPLAYER   2
#define DPRECEIVE_FROMPLAYER 4
#define DPRECEIVE_PEEK       8
#define DPENUMSESSIONS_ASYNC     0x10
#define DPENUMSESSIONS_STOPASYNC 0x20
#define DPESC_TIMEDOUT   1
#define DPSYS_CREATEPLAYERORGROUP  3
#define DPSYS_DESTROYPLAYERORGROUP 5
#define DPPLAYERTYPE_PLAYER 1

typedef struct { DWORD dwSize, dwFlags; char *lpszShortNameA, *lpszLongNameA; } DPNAME_;
typedef struct {
    DWORD dwSize, dwFlags; GUID guidInstance, guidApplication; DWORD dwMaxPlayers, dwCurrentPlayers;
    char *lpszSessionNameA, *lpszPasswordA; DWORD dwReserved1, dwReserved2, dwUser1, dwUser2, dwUser3, dwUser4;
} DPSD2;
typedef struct { DWORD dwSize, dwFlags, dwMaxBufferSize, dwMaxQueueSize, dwMaxPlayers, dwHundredBaud,
                 dwLatency, dwMaxLocalPlayers, dwHeaderLength, dwTimeout; } DPCAPS_;
typedef struct { GUID guidDataType; DWORD dwDataSize; void *lpData; } DPCAE;
typedef struct { DWORD dwType, dwPlayerType; DWORD dpId, dwCurrentPlayers; void *lpData; DWORD dwDataSize;
                 DPNAME_ dpnName; DWORD dpIdParent, dwFlags; } MSG_CREATE;
typedef struct { DWORD dwType, dwPlayerType; DWORD dpId; void *lpLocalData; DWORD dwLocalDataSize;
                 void *lpRemoteData; DWORD dwRemoteDataSize; DPNAME_ dpnName; DWORD dpIdParent, dwFlags; } MSG_DESTROY;

typedef BOOL (WINAPI *ENUMCONN_CB)(const GUID *, void *, DWORD, const DPNAME_ *, DWORD, void *);
typedef BOOL (WINAPI *ENUMSESS_CB)(const DPSD2 *, DWORD *, DWORD, void *);
typedef BOOL (WINAPI *ENUMPLAYER_CB)(DWORD, DWORD, const DPNAME_ *, DWORD, void *);

static const GUID CLSID_DirectPlay_      = {0xd1eb6d20,0x8923,0x11d0,{0x9d,0x97,0x00,0xa0,0xc9,0x0a,0x43,0xcb}};
static const GUID CLSID_DirectPlayLobby_ = {0x2fe8f810,0xb2a5,0x11d0,{0xa7,0x87,0x00,0x00,0xf8,0x03,0xab,0xfc}};
static const GUID SP_TCPIP = {0x36e95ee0,0x8577,0x11cf,{0x96,0x0c,0x00,0x80,0xc7,0x53,0x4e,0x82}};
static const GUID SP_IPX   = {0x685bc400,0x9d2c,0x11cf,{0xa9,0xcd,0x00,0xaa,0x00,0x68,0x86,0xe3}};
static const GUID DPAID_INet_ = {0xc4a54da0,0xe0af,0x11cf,{0x9c,0x4e,0x00,0xa0,0xc9,0x05,0x42,0x5e}};
static const GUID CLSID_UPnPNAT_ = {0xae1e00aa,0x3fd5,0x403c,{0x8a,0x27,0x2b,0xbd,0xc3,0x0c,0xd0,0xe1}};
static const GUID IID_IUPnPNAT_  = {0xb171c812,0xcc76,0x485a,{0x94,0xd8,0xb6,0xb3,0xa2,0x79,0x4e,0x99}};

/* ------------------------------------------------------------------ config / logging */
static char g_server[128], g_dir[MAX_PATH];
static int g_port = 2020, g_mainport = 2020, g_log = 0, g_local = 1, g_hubport = 2300, g_discport = 2301, g_upnp = 1;
static CRITICAL_SECTION g_logcs;
static int g_hudtrace, g_fakew, g_fakeh, g_hud43 = 1, g_watch, g_menu43 = 1, g_sharptext = 1;
static double g_hudaspect = 16.0 / 9.0;
static double g_menusens = 1.0;

static void logf(const char *fmt, ...) {
    if (!g_log) return;
    char path[MAX_PATH], line[1024];
    va_list ap; va_start(ap, fmt); vsnprintf(line, sizeof line, fmt, ap); va_end(ap);
    snprintf(path, sizeof path, "%saxisnet.log", g_dir);
    EnterCriticalSection(&g_logcs);
    FILE *f = fopen(path, "a");
    if (f) { SYSTEMTIME t; GetLocalTime(&t);
             fprintf(f, "%02d:%02d:%02d.%03d [%lu] %s\n", t.wHour, t.wMinute, t.wSecond, t.wMilliseconds,
                     GetCurrentProcessId(), line); fclose(f); }
    LeaveCriticalSection(&g_logcs);
}

static void trim(char *s) {
    size_t n = strlen(s);
    while (n && (s[n - 1] == ' ' || s[n - 1] == '\t' || s[n - 1] == '\r' || s[n - 1] == '\n')) s[--n] = 0;
}

static void load_config(void) {
    char ini[MAX_PATH], mode[32];
    GetModuleFileNameA(NULL, g_dir, MAX_PATH);  /* settings and log live next to the game exe */
    char *p = strrchr(g_dir, '\\'); if (p) p[1] = 0; else g_dir[0] = 0;
    snprintf(ini, sizeof ini, "%saxisnet.ini", g_dir);
    GetPrivateProfileStringA("net", "mode", "local", mode, sizeof mode, ini);
    g_local = _stricmp(mode, "server") != 0;
    GetPrivateProfileStringA("net", "server", "", g_server, sizeof g_server, ini);
    g_port = GetPrivateProfileIntA("net", "port", 0, ini);
    g_hubport = GetPrivateProfileIntA("net", "hubport", 2300, ini);
    g_discport = GetPrivateProfileIntA("net", "discport", g_hubport + 1, ini);
    g_upnp = GetPrivateProfileIntA("net", "upnp", 1, ini);
    g_log = GetPrivateProfileIntA("net", "log", 0, ini);
    g_hudtrace = GetPrivateProfileIntA("net", "hudtrace", 0, ini);
    g_watch = GetPrivateProfileIntA("net", "watch", 0, ini);
    g_hud43 = GetPrivateProfileIntA("hud", "proportional", 1, ini);
    g_menu43 = GetPrivateProfileIntA("hud", "menu43", 1, ini);   /* menus in a centred 4:3 box (0 = 16:9 box, as before) */
    g_sharptext = GetPrivateProfileIntA("hud", "sharptext", 1, ini);   /* menu/chat text: nearest-pixel font sampling (0 = smoothed, as before) */
    char sens[32];  /* menu cursor speed: 1 = like the Windows pointer, 2 = twice as fast, 0 = original (1 count = 1 unit of 640) */
    GetPrivateProfileStringA("input", "menusens", "1", sens, sizeof sens, ini);
    g_menusens = atof(sens);
    char asp[32];  /* widest area the HUD spreads over; 0 = the whole screen */
    GetPrivateProfileStringA("hud", "maxaspect", "1.7778", asp, sizeof asp, ini);
    g_hudaspect = atof(asp);
    char fake[32];  /* debug: fakeres=3440x1440 makes DESKTOP mode use that size (to preview other aspect ratios) */
    GetPrivateProfileStringA("net", "fakeres", "", fake, sizeof fake, ini);
    if (sscanf(fake, "%dx%d", &g_fakew, &g_fakeh) != 2 || g_fakew <= 0 || g_fakeh <= 0) g_fakew = g_fakeh = 0;
    HKEY k;
    if (RegOpenKeyExA(HKEY_CURRENT_USER, "SOFTWARE\\AxisArena\\SelectServer", 0, KEY_READ, &k) == ERROR_SUCCESS) {
        DWORD sz = sizeof g_server, port = 0, psz = sizeof port, type;
        if (!g_server[0]) RegQueryValueExA(k, "TcpDNS", NULL, &type, (BYTE *)g_server, &sz);
        if (RegQueryValueExA(k, "TcpPort", NULL, &type, (BYTE *)&port, &psz) == ERROR_SUCCESS && type == REG_DWORD && port)
            g_mainport = (int)port;
        RegCloseKey(k);
    }
    trim(g_server);
    if (!g_port) g_port = g_mainport;
}

/* ------------------------------------------------------------------ sockets */
enum { C_PING = 1, S_PONG = 2, C_ENUM = 3, S_SESSIONS = 4, C_HOST = 5, S_HOSTED = 6, C_JOIN = 7, S_JOINED = 8,
       C_CREATEPLAYER = 9, S_PLAYER = 10, C_DESTROYPLAYER = 11, C_SEND = 12, S_DATA = 13, C_CLOSE = 15,
       S_SYSCREATE = 16, S_SYSDESTROY = 17 };
#define NAMELEN 64
#define SESS_WIRE (16 + 7 * 4 + NAMELEN + 1)
#define MAINREC 0x5b
#define E_NOSESS DPERR_NOSESSIONS

typedef int (WSAAPI *CONNECTFN)(SOCKET, const struct sockaddr *, int);
static CONNECTFN real_connect;
static int g_wsa;
static void wsa_init(void) { if (!g_wsa) { WSADATA w; WSAStartup(MAKEWORD(2, 2), &w); g_wsa = 1; } }

static int send_all(SOCKET s, const void *buf, int len) {
    const char *p = buf;
    while (len > 0) { int n = send(s, p, len, 0); if (n <= 0) return 0; p += n; len -= n; }
    return 1;
}
static int recv_all(SOCKET s, void *buf, int len) {
    char *p = buf;
    while (len > 0) { int n = recv(s, p, len, 0); if (n <= 0) return 0; p += n; len -= n; }
    return 1;
}
static int send_frame(SOCKET s, CRITICAL_SECTION *cs, int type, const void *a, int alen, const void *b, int blen) {
    unsigned char hdr[5]; DWORD len = 1 + alen + blen;
    memcpy(hdr, &len, 4); hdr[4] = (unsigned char)type;
    if (cs) EnterCriticalSection(cs);
    int ok = s != INVALID_SOCKET && send_all(s, hdr, 5) && (!alen || send_all(s, a, alen)) && (!blen || send_all(s, b, blen));
    if (cs) LeaveCriticalSection(cs);
    return ok;
}

/* connect with a timeout; returns a connected socket that has sent the relay hello */
static SOCKET hub_connect(const char *host, int port, DWORD timeout_ms) {
    wsa_init();
    char ps[16]; snprintf(ps, sizeof ps, "%d", port);
    struct addrinfo hints = {0}, *res = NULL;
    hints.ai_family = AF_INET; hints.ai_socktype = SOCK_STREAM;
    if (!host || !host[0] || getaddrinfo(host, ps, &hints, &res) || !res) { logf("cannot resolve '%s'", host ? host : ""); return INVALID_SOCKET; }
    SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    u_long nb = 1; ioctlsocket(s, FIONBIO, &nb);
    connect(s, res->ai_addr, (int)res->ai_addrlen);
    freeaddrinfo(res);
    fd_set w, e; FD_ZERO(&w); FD_ZERO(&e); FD_SET(s, &w); FD_SET(s, &e);
    struct timeval tv = {(long)(timeout_ms / 1000), (long)(timeout_ms % 1000) * 1000};
    int ok = select(0, NULL, &w, &e, &tv) == 1 && FD_ISSET(s, &w);
    nb = 0; ioctlsocket(s, FIONBIO, &nb);
    if (!ok) { closesocket(s); logf("cannot connect to %s:%d", host, port); return INVALID_SOCKET; }
    int one = 1; setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof one);
    unsigned char hello[8] = {'A', 'X', 'N', 'R', 1, 0, 0, 0};
    send_all(s, hello, 8);
    return s;
}

static void local_ips(char *out, int size) {
    char host[256]; out[0] = 0;
    wsa_init();
    if (gethostname(host, sizeof host)) return;
    struct addrinfo hints = {0}, *res = NULL, *r;
    hints.ai_family = AF_INET;
    if (getaddrinfo(host, NULL, &hints, &res)) return;
    for (r = res; r; r = r->ai_next) {
        char *a = inet_ntoa(((struct sockaddr_in *)r->ai_addr)->sin_addr);
        if ((int)(strlen(out) + strlen(a) + 2) < size) { if (out[0]) strcat(out, " "); strcat(out, a); }
    }
    freeaddrinfo(res);
}

typedef struct { GUID inst; DWORD flags, maxp, cur, u1, u2, u3, u4; char name[NAMELEN]; int haspw; char addr[NAMELEN]; } Sess;
static void read_sess(Sess *x, const BYTE *p) {
    memcpy(&x->inst, p, 16); memcpy(&x->flags, p + 16, 28);
    memcpy(x->name, p + 44, NAMELEN); x->name[NAMELEN - 1] = 0; x->haspw = p[44 + NAMELEN]; x->addr[0] = 0;
}

/* ------------------------------------------------------------------ the hub (host side, local mode) */
#define HUB_MAXC 32
#define HUB_MAXP 8
typedef struct {
    SOCKET s; BYTE *buf; DWORD len, cap; int hello; char ip[32];
    int joined, is_host, np; DWORD pid[HUB_MAXP]; char sn[HUB_MAXP][NAMELEN], ln[HUB_MAXP][NAMELEN];
} HubC;
static struct {
    CRITICAL_SECTION cs; volatile LONG running; HANDLE thread; SOCKET ls, us;
    HubC c[HUB_MAXC]; int n;
    int has_sess, open; GUID guid; DWORD flags, maxp, u[4], next_id; char name[NAMELEN], pw[16];
    char external[64];
} hub;
static CRITICAL_SECTION g_reccs;
static BYTE g_myrec[MAINREC]; static int g_have_rec;   /* this game's entry in the (built-in) game list */

static int hub_players(void) { int n = 0; for (int i = 0; i < hub.n; i++) n += hub.c[i].np; return n; }
static void hub_wire(BYTE *p) {
    memcpy(p, &hub.guid, 16);
    DWORD v[7] = {hub.flags, hub.maxp, (DWORD)hub_players(), hub.u[0], hub.u[1], hub.u[2], hub.u[3]};
    memcpy(p + 16, v, 28); memset(p + 44, 0, NAMELEN); lstrcpynA((char *)p + 44, hub.name, NAMELEN);
    p[44 + NAMELEN] = hub.pw[0] != 0;
}
static void hub_send(HubC *c, int type, const void *a, int alen, const void *b, int blen) {
    if (c->s != INVALID_SOCKET && !send_frame(c->s, NULL, type, a, alen, b, blen)) {
        closesocket(c->s); c->s = INVALID_SOCKET;   /* dropped on the next loop */
    }
}
static void hub_notify(HubC *from, int type, DWORD pid, const char *sn, const char *ln) {
    BYTE p[8 + 2 * NAMELEN]; DWORD cur = hub_players();
    memcpy(p, &pid, 4); memcpy(p + 4, &cur, 4);
    memset(p + 8, 0, 2 * NAMELEN); lstrcpynA((char *)p + 8, sn, NAMELEN); lstrcpynA((char *)p + 8 + NAMELEN, ln, NAMELEN);
    for (int i = 0; i < hub.n; i++)
        if (&hub.c[i] != from && hub.c[i].joined) hub_send(&hub.c[i], type, p, sizeof p, NULL, 0);
}
static void hub_leave(HubC *c) {
    if (!c->joined) return;
    while (c->np) { c->np--; hub_notify(c, S_SYSDESTROY, c->pid[c->np], c->sn[c->np], c->ln[c->np]); }
    c->joined = 0;
    if (c->is_host) {
        logf("hub: host left - session '%s' closed", hub.name);
        hub.open = 0; hub.has_sess = 0;
        for (int i = 0; i < hub.n; i++) if (&hub.c[i] != c && hub.c[i].s != INVALID_SOCKET) { closesocket(hub.c[i].s); hub.c[i].s = INVALID_SOCKET; }
        InterlockedExchange(&hub.running, 0);
    }
}

static void hub_frame(HubC *c, int type, const BYTE *p, DWORD plen) {
    switch (type) {
    case C_PING: hub_send(c, S_PONG, p, plen >= 4 ? 4 : 0, NULL, 0); break;
    case C_ENUM: {
        BYTE out[4 + SESS_WIRE]; DWORD n = hub.has_sess && hub.open ? 1 : 0;
        memcpy(out, &n, 4); if (n) hub_wire(out + 4);
        hub_send(c, S_SESSIONS, out, 4 + n * SESS_WIRE, NULL, 0);
        break;
    }
    case C_HOST: {
        BYTE out[20] = {0}; HRESULT hr = DP_OK;
        if (plen < 24 + NAMELEN + 16 || strcmp(c->ip, "127.0.0.1") || hub.has_sess) hr = DPERR_CANTCREATESESSION;
        else {
            memcpy(&hub.flags, p, 4); memcpy(&hub.maxp, p + 4, 4); memcpy(hub.u, p + 8, 16);
            memcpy(hub.name, p + 24, NAMELEN); hub.name[NAMELEN - 1] = 0;
            memcpy(hub.pw, p + 24 + NAMELEN, 16); hub.pw[15] = 0;
            CoCreateGuid(&hub.guid);
            hub.has_sess = hub.open = 1; c->joined = c->is_host = 1;
            logf("hub: hosting '%s' (max %lu) on port %d", hub.name, hub.maxp, g_hubport);
        }
        memcpy(out, &hr, 4); memcpy(out + 4, &hub.guid, 16);
        hub_send(c, S_HOSTED, out, 20, NULL, 0);
        break;
    }
    case C_JOIN: {
        HRESULT hr = DP_OK; char pw[16] = {0};
        if (plen >= 32) memcpy(pw, p + 16, 15);
        if (plen < 32 || !hub.has_sess || !hub.open || memcmp(p, &hub.guid, 16)) hr = DPERR_NOSESSIONS;
        else if (hub.pw[0] && strcmp(pw, hub.pw)) hr = DPERR_INVALIDPASSWORD;
        else if (hub.maxp && hub_players() >= (int)hub.maxp) hr = DPERR_CANTADDPLAYER;
        if (hr != DP_OK) { hub_send(c, S_JOINED, &hr, 4, NULL, 0); break; }
        int np = hub_players();
        DWORD size = 4 + SESS_WIRE + 4 + np * (4 + 2 * NAMELEN);
        BYTE *out = calloc(1, size), *q = out + 8 + SESS_WIRE;
        hub_wire(out + 4); memcpy(out + 4 + SESS_WIRE, &np, 4);
        for (int i = 0; i < hub.n; i++)
            for (int j = 0; j < hub.c[i].np; j++) {
                memcpy(q, &hub.c[i].pid[j], 4); lstrcpynA((char *)q + 4, hub.c[i].sn[j], NAMELEN);
                lstrcpynA((char *)q + 4 + NAMELEN, hub.c[i].ln[j], NAMELEN); q += 4 + 2 * NAMELEN;
            }
        hub_send(c, S_JOINED, out, size, NULL, 0);
        free(out);
        c->joined = 1;
        logf("hub: %s joined", c->ip);
        break;
    }
    case C_CREATEPLAYER: {
        DWORD out[2] = {(DWORD)DP_OK, 0};
        if (!c->joined) out[0] = (DWORD)DPERR_NOCONNECTION;
        else if (c->np >= HUB_MAXP || (hub.maxp && hub_players() >= (int)hub.maxp)) out[0] = (DWORD)DPERR_CANTADDPLAYER;
        else {
            DWORD id = ++hub.next_id;
            c->pid[c->np] = id;
            lstrcpynA(c->sn[c->np], plen >= NAMELEN ? (const char *)p : "", NAMELEN);
            lstrcpynA(c->ln[c->np], plen >= 2 * NAMELEN ? (const char *)p + NAMELEN : "", NAMELEN);
            c->np++; out[1] = id;
            hub_notify(c, S_SYSCREATE, id, c->sn[c->np - 1], c->ln[c->np - 1]);
            logf("hub: player %08lx '%s' from %s (%d players)", id, c->sn[c->np - 1], c->ip, hub_players());
        }
        hub_send(c, S_PLAYER, out, 8, NULL, 0);
        break;
    }
    case C_DESTROYPLAYER: {
        DWORD id; if (plen < 4) break; memcpy(&id, p, 4);
        for (int j = 0; j < c->np; j++) if (c->pid[j] == id) {
            char sn[NAMELEN], ln[NAMELEN]; lstrcpynA(sn, c->sn[j], NAMELEN); lstrcpynA(ln, c->ln[j], NAMELEN);
            c->np--; c->pid[j] = c->pid[c->np]; strcpy(c->sn[j], c->sn[c->np]); strcpy(c->ln[j], c->ln[c->np]);
            hub_notify(c, S_SYSDESTROY, id, sn, ln);
            break;
        }
        break;
    }
    case C_SEND: {
        DWORD from, to; if (!c->joined || plen < 12) break;
        memcpy(&from, p, 4); memcpy(&to, p + 4, 4);
        int mine = 0; for (int j = 0; j < c->np; j++) if (c->pid[j] == from) mine = 1;
        if (c->np && !mine) break;
        BYTE hdr[8]; memcpy(hdr, &from, 4); memcpy(hdr + 4, &to, 4);
        for (int i = 0; i < hub.n; i++) {
            HubC *o = &hub.c[i];
            if (o == c || !o->joined) continue;
            int hit = to == DPID_ALLPLAYERS;
            for (int j = 0; j < o->np && !hit; j++) if (o->pid[j] == to) hit = 1;
            if (hit) hub_send(o, S_DATA, hdr, 8, p + 12, (int)plen - 12);
        }
        break;
    }
    case C_CLOSE: hub_leave(c); break;
    }
}

static void hub_beacon(SOCKET us) {
    char q[16]; struct sockaddr_in from; int fl = sizeof from;
    int n = recvfrom(us, q, sizeof q, 0, (struct sockaddr *)&from, &fl);
    if (n < 4 || memcmp(q, "AXNQ", 4) || !hub.has_sess || !hub.open) return;
    BYTE r[8 + MAINREC + SESS_WIRE] = {'A', 'X', 'N', 'B'};
    WORD port = (WORD)g_hubport; memcpy(r + 4, &port, 2);
    EnterCriticalSection(&g_reccs); if (g_have_rec) memcpy(r + 8, g_myrec, MAINREC); LeaveCriticalSection(&g_reccs);
    hub_wire(r + 8 + MAINREC);
    sendto(us, (char *)r, sizeof r, 0, (struct sockaddr *)&from, fl);
}

static void hub_read(HubC *c) {
    if (c->cap - c->len < 4096) { c->cap = c->cap ? c->cap * 2 : 8192; c->buf = realloc(c->buf, c->cap); }
    int n = recv(c->s, (char *)c->buf + c->len, (int)(c->cap - c->len), 0);
    if (n <= 0) { closesocket(c->s); c->s = INVALID_SOCKET; return; }
    c->len += n;
    DWORD off = 0;
    if (!c->hello) {
        if (c->len < 8) return;
        if (memcmp(c->buf, "AXNR", 4)) { closesocket(c->s); c->s = INVALID_SOCKET; return; }
        c->hello = 1; off = 8;
    }
    while (c->s != INVALID_SOCKET && c->len - off >= 4) {
        DWORD fl; memcpy(&fl, c->buf + off, 4);
        if (fl < 1 || fl > (1 << 20)) { closesocket(c->s); c->s = INVALID_SOCKET; return; }
        if (c->len - off - 4 < fl) break;
        hub_frame(c, c->buf[off + 4], c->buf + off + 5, fl - 1);
        off += 4 + fl;
    }
    memmove(c->buf, c->buf + off, c->len - off); c->len -= off;
}

static DWORD WINAPI upnp_thread(void *arg);

static DWORD WINAPI hub_thread(void *arg) {
    while (hub.running) {
        fd_set r; FD_ZERO(&r); FD_SET(hub.ls, &r); FD_SET(hub.us, &r);
        for (int i = 0; i < hub.n; i++) FD_SET(hub.c[i].s, &r);
        struct timeval tv = {0, 200000};
        if (select(0, &r, NULL, NULL, &tv) < 0) Sleep(10);
        if (FD_ISSET(hub.ls, &r)) {
            struct sockaddr_in a; int al = sizeof a;
            SOCKET s = accept(hub.ls, (struct sockaddr *)&a, &al);
            if (s != INVALID_SOCKET) {
                if (hub.n >= HUB_MAXC) closesocket(s);
                else {
                    int one = 1; DWORD tmo = 3000;
                    setsockopt(s, IPPROTO_TCP, TCP_NODELAY, (char *)&one, sizeof one);
                    setsockopt(s, SOL_SOCKET, SO_SNDTIMEO, (char *)&tmo, sizeof tmo);
                    HubC *c = &hub.c[hub.n++]; memset(c, 0, sizeof *c);
                    c->s = s; lstrcpynA(c->ip, inet_ntoa(a.sin_addr), sizeof c->ip);
                }
            }
        }
        if (FD_ISSET(hub.us, &r)) hub_beacon(hub.us);
        EnterCriticalSection(&hub.cs);
        for (int i = 0; i < hub.n; i++) if (hub.c[i].s != INVALID_SOCKET && FD_ISSET(hub.c[i].s, &r)) hub_read(&hub.c[i]);
        for (int i = 0; i < hub.n;) {
            if (hub.c[i].s == INVALID_SOCKET) {
                hub_leave(&hub.c[i]); free(hub.c[i].buf);
                hub.c[i] = hub.c[--hub.n];
            } else i++;
        }
        LeaveCriticalSection(&hub.cs);
    }
    for (int i = 0; i < hub.n; i++) { if (hub.c[i].s != INVALID_SOCKET) closesocket(hub.c[i].s); free(hub.c[i].buf); }
    hub.n = 0; hub.has_sess = hub.open = 0;
    closesocket(hub.ls); closesocket(hub.us); hub.ls = hub.us = INVALID_SOCKET;
    if (g_upnp) CloseHandle(CreateThread(NULL, 0, upnp_thread, (void *)0, 0, NULL));  /* remove the port mapping */
    logf("hub stopped");
    return 0;
}

static int hub_start(void) {
    if (hub.running) return 1;
    if (hub.thread) { WaitForSingleObject(hub.thread, 3000); CloseHandle(hub.thread); hub.thread = NULL; }
    wsa_init();
    struct sockaddr_in a = {0}; a.sin_family = AF_INET; a.sin_addr.s_addr = INADDR_ANY; a.sin_port = htons((u_short)g_hubport);
    hub.ls = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (bind(hub.ls, (struct sockaddr *)&a, sizeof a) || listen(hub.ls, 16)) {
        logf("hub: cannot listen on TCP %d (%d)", g_hubport, WSAGetLastError());
        closesocket(hub.ls); return 0;
    }
    hub.us = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int one = 1; setsockopt(hub.us, SOL_SOCKET, SO_REUSEADDR, (char *)&one, sizeof one);
    a.sin_port = htons((u_short)g_discport);
    if (bind(hub.us, (struct sockaddr *)&a, sizeof a)) logf("hub: LAN discovery port %d busy", g_discport);
    hub.has_sess = hub.open = 0; hub.n = 0; hub.next_id = 0x41580000 | (GetTickCount() & 0xfff) << 4;
    hub.running = 1;
    hub.thread = CreateThread(NULL, 0, hub_thread, NULL, 0, NULL);
    if (g_upnp) CloseHandle(CreateThread(NULL, 0, upnp_thread, (void *)1, 0, NULL));
    else { char ips[128]; local_ips(ips, sizeof ips); logf("hub: UPnP disabled - forward TCP %d to this PC (%s)", g_hubport, ips); }
    return 1;
}

/* UPnP port mapping through Windows' NATUPnP COM object; also puts the joinable address on the clipboard */
static void copy_to_clipboard(const char *text) {
    if (!OpenClipboard(NULL)) return;
    EmptyClipboard();
    HGLOBAL h = GlobalAlloc(GMEM_MOVEABLE, strlen(text) + 1);
    if (h) { strcpy(GlobalLock(h), text); GlobalUnlock(h); SetClipboardData(CF_TEXT, h); }
    CloseClipboard();
}
static void *vt(void *obj, int i) { return (*(void ***)obj)[i]; }
static DWORD WINAPI upnp_thread(void *arg) {
    int add = arg != NULL;
    char ips[128], first[64] = "";
    local_ips(ips, sizeof ips);
    sscanf(ips, "%63s", first);
    for (char *t = strtok(ips, " "); t; t = strtok(NULL, " "))       /* prefer a private LAN address */
        if (!strncmp(t, "192.168.", 8) || !strncmp(t, "10.", 3) || !strncmp(t, "172.", 4)) { lstrcpynA(first, t, sizeof first); break; }
    CoInitializeEx(NULL, COINIT_MULTITHREADED);
    void *nat = NULL, *coll = NULL, *map = NULL; int ok = 0;
    if (SUCCEEDED(CoCreateInstance(&CLSID_UPnPNAT_, NULL, CLSCTX_INPROC_SERVER, &IID_IUPnPNAT_, &nat)) && nat) {
        ((HRESULT (WINAPI *)(void *, void **))vt(nat, 7))(nat, &coll);  /* get_StaticPortMappingCollection */
        if (coll) {
            BSTR tcp = SysAllocString(L"TCP");
            ((HRESULT (WINAPI *)(void *, long, BSTR))vt(coll, 10))(coll, g_hubport, tcp);   /* Remove old */
            if (add) {
                WCHAR wclient[64], wdesc[] = L"Axis game host";
                MultiByteToWideChar(CP_ACP, 0, first, -1, wclient, 64);
                BSTR client = SysAllocString(wclient), desc = SysAllocString(wdesc);
                HRESULT hr = ((HRESULT (WINAPI *)(void *, long, BSTR, long, BSTR, VARIANT_BOOL, BSTR, void **))vt(coll, 11))
                    (coll, g_hubport, tcp, g_hubport, client, VARIANT_TRUE, desc, &map);
                if (SUCCEEDED(hr) && map) {
                    BSTR ext = NULL;
                    ((HRESULT (WINAPI *)(void *, BSTR *))vt(map, 7))(map, &ext);  /* get_ExternalIPAddress */
                    if (ext) { WideCharToMultiByte(CP_ACP, 0, ext, -1, hub.external, sizeof hub.external, NULL, NULL); SysFreeString(ext); }
                    ((ULONG (WINAPI *)(void *))vt(map, 2))(map);
                    ok = 1;
                } else logf("UPnP: router refused the port mapping (%08lx)", hr);
                SysFreeString(client); SysFreeString(desc);
            }
            SysFreeString(tcp);
            ((ULONG (WINAPI *)(void *))vt(coll, 2))(coll);
        } else if (add) logf("UPnP: no UPnP router found");
        ((ULONG (WINAPI *)(void *))vt(nat, 2))(nat);
    }
    CoUninitialize();
    if (add) {
        char text[96];
        if (ok && hub.external[0]) {
            snprintf(text, sizeof text, "%s", hub.external);
            logf("hosting: router port TCP %d opened by UPnP - friends join with DIRECT IP %s (copied to clipboard)", g_hubport, hub.external);
        } else {
            snprintf(text, sizeof text, "%s", first);
            logf("hosting: LAN address %s copied to clipboard. For internet play forward TCP %d to this PC", first, g_hubport);
        }
        copy_to_clipboard(text);
    }
    return 0;
}

/* ------------------------------------------------------------------ LAN discovery (client side) */
typedef struct { char ip[32]; int port; BYTE rec[MAINREC]; Sess s; } Disc;
static int discover(Disc *out, int max, DWORD timeout_ms) {
    wsa_init();
    SOCKET u = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    int one = 1; setsockopt(u, SOL_SOCKET, SO_BROADCAST, (char *)&one, sizeof one);
    struct sockaddr_in a = {0}; a.sin_family = AF_INET; a.sin_port = htons((u_short)g_discport);
    const char *targets[2] = {"255.255.255.255", "127.0.0.1"};
    for (int i = 0; i < 2; i++) { a.sin_addr.s_addr = inet_addr(targets[i]); sendto(u, "AXNQ", 4, 0, (struct sockaddr *)&a, sizeof a); }
    char ips[128]; local_ips(ips, sizeof ips);
    for (char *t = strtok(ips, " "); t; t = strtok(NULL, " ")) {     /* subnet broadcasts (/24) */
        unsigned long ip = inet_addr(t); if (ip == INADDR_NONE) continue;
        a.sin_addr.s_addr = (ip & htonl(0xffffff00)) | htonl(0xff);
        sendto(u, "AXNQ", 4, 0, (struct sockaddr *)&a, sizeof a);
    }
    int n = 0; DWORD end = GetTickCount() + timeout_ms;
    for (;;) {
        long left = (long)(end - GetTickCount()); if (left <= 0) break;
        fd_set r; FD_ZERO(&r); FD_SET(u, &r);
        struct timeval tv = {left / 1000, (left % 1000) * 1000};
        if (select(0, &r, NULL, NULL, &tv) <= 0) break;
        BYTE b[8 + MAINREC + SESS_WIRE + 16]; struct sockaddr_in from; int fl = sizeof from;
        int got = recvfrom(u, (char *)b, sizeof b, 0, (struct sockaddr *)&from, &fl);
        if (got < 8 + MAINREC + SESS_WIRE || memcmp(b, "AXNB", 4) || n >= max) continue;
        Disc d; memset(&d, 0, sizeof d);
        WORD port; memcpy(&port, b + 4, 2); d.port = port;
        memcpy(d.rec, b + 8, MAINREC); read_sess(&d.s, b + 8 + MAINREC);
        const char *src = inet_ntoa(from.sin_addr);
        if (!strncmp(src, "127.", 4)) { char me[128]; local_ips(me, sizeof me); sscanf(me, "%31s", d.ip); }
        else lstrcpynA(d.ip, src, sizeof d.ip);
        if (!d.ip[0]) lstrcpynA(d.ip, src, sizeof d.ip);
        int dup = 0; for (int i = 0; i < n; i++) if (IsEqualGUID(&out[i].s.inst, &d.s.inst)) dup = 1;
        if (!dup) { lstrcpynA(d.s.addr, d.ip, NAMELEN); out[n++] = d; }
    }
    closesocket(u);
    return n;
}

/* ------------------------------------------------------------------ built-in game list (local mode) */
static int g_vm_port; static SOCKET g_vm_ls = INVALID_SOCKET; static CRITICAL_SECTION g_vmcs;
static DWORD WINAPI vm_client(void *arg) {
    SOCKET s = (SOCKET)(UINT_PTR)arg;
    for (;;) {
        DWORD id; BYTE body[MAINREC];
        if (!recv_all(s, &id, 4)) break;
        int size = id == 10 || id == 11 || id == 12 ? MAINREC : id == 13 ? 4 : id == 23 ? 16 : -1;
        if (size < 0 || !recv_all(s, body, size)) break;
        if (id == 10 || id == 12) {
            EnterCriticalSection(&g_reccs); memcpy(g_myrec, body, MAINREC); g_have_rec = 1; LeaveCriticalSection(&g_reccs);
            if (id == 10) { DWORD ok = 0; send_all(s, &ok, 4); logf("game list: '%s' advertised on the LAN", (char *)body + 1); }
        } else if (id == 11) {
            EnterCriticalSection(&g_reccs); g_have_rec = 0; LeaveCriticalSection(&g_reccs);
        } else if (id == 13) {
            Disc d[32]; int n = discover(d, 32, 700), sent = 0;
            for (int i = 0; i < n; i++) {
                if (!d[i].rec[1]) continue;  /* hosted without a list entry */
                BYTE r[MAINREC]; memcpy(r, d[i].rec, MAINREC);
                memset(r + 0x33, 0, 16); lstrcpynA((char *)r + 0x33, d[i].ip, 16);
                memset(r + 0x4a, 0, 4);
                send_all(s, r, MAINREC); sent++;
            }
            BYTE end[MAINREC] = {0}; end[0x4a] = 1; send_all(s, end, MAINREC);
            logf("game list: SEARCH TCP found %d LAN game(s)", sent);
        }
    }
    closesocket(s);
    return 0;
}
static DWORD WINAPI vm_thread(void *arg) {
    for (;;) {
        SOCKET s = accept(g_vm_ls, NULL, NULL);
        if (s == INVALID_SOCKET) break;
        CloseHandle(CreateThread(NULL, 0, vm_client, (void *)(UINT_PTR)s, 0, NULL));
    }
    return 0;
}
static int vm_start(void) {
    EnterCriticalSection(&g_vmcs);
    if (!g_vm_port) {
        wsa_init();
        struct sockaddr_in a = {0}; int al = sizeof a;
        a.sin_family = AF_INET; a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        g_vm_ls = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (!bind(g_vm_ls, (struct sockaddr *)&a, sizeof a) && !listen(g_vm_ls, 8) && !getsockname(g_vm_ls, (struct sockaddr *)&a, &al)) {
            g_vm_port = ntohs(a.sin_port);
            CloseHandle(CreateThread(NULL, 0, vm_thread, NULL, 0, NULL));
        }
    }
    LeaveCriticalSection(&g_vmcs);
    return g_vm_port;
}
static int WSAAPI hook_connect(SOCKET s, const struct sockaddr *name, int len) {
    if (name && name->sa_family == AF_INET)
        logf("game connect %s:%d", inet_ntoa(((struct sockaddr_in *)name)->sin_addr), ntohs(((struct sockaddr_in *)name)->sin_port));
    if (g_local && name && name->sa_family == AF_INET && ntohs(((struct sockaddr_in *)name)->sin_port) == g_mainport) {
        int port = vm_start();
        if (port) {
            struct sockaddr_in a = {0}; a.sin_family = AF_INET; a.sin_addr.s_addr = htonl(INADDR_LOOPBACK); a.sin_port = htons((u_short)port);
            return real_connect(s, (struct sockaddr *)&a, sizeof a);
        }
    }
    return real_connect(s, name, len);
}

/* ------------------------------------------------------------------ DirectPlay object */
typedef struct Msg {
    struct Msg *next;
    DWORD from, to, sys, size;
    DWORD dpid, cur; char sname[NAMELEN], lname[NAMELEN];
    BYTE data[1];
} Msg;
typedef struct { DWORD id; char sname[NAMELEN], lname[NAMELEN]; int local; } Player;

typedef struct DP {
    const void *vtbl; LONG ref;
    CRITICAL_SECTION cs, sendcs; SOCKET s; HANDLE thread; volatile LONG alive; char conn_to[NAMELEN];
    int initialized; char target[NAMELEN];
    Msg *qhead, *qtail; DWORD qcount; HANDLE hEvent;
    HANDLE reply_ev; volatile int wait_type; BYTE *reply; DWORD reply_len;
    Sess sess[64]; int nsess; DWORD last_enum; int have_enum;
    volatile int in_session; int is_host; DPSD2 sd; char sessname[NAMELEN];
    Player players[64]; int nplayers;
} DP;

static Player *find_player(DP *dp, DWORD id) {
    for (int i = 0; i < dp->nplayers; i++) if (dp->players[i].id == id) return &dp->players[i];
    return NULL;
}
static void add_player(DP *dp, DWORD id, const char *s, const char *l, int local) {
    Player *p = find_player(dp, id);
    if (!p) { if (dp->nplayers >= 64) return; p = &dp->players[dp->nplayers++]; }
    p->id = id; p->local = local;
    lstrcpynA(p->sname, s ? s : "", NAMELEN); lstrcpynA(p->lname, l ? l : "", NAMELEN);
}
static void del_player(DP *dp, DWORD id) {
    for (int i = 0; i < dp->nplayers; i++)
        if (dp->players[i].id == id) { dp->players[i] = dp->players[--dp->nplayers]; return; }
}
static void push_msg(DP *dp, Msg *m) {
    EnterCriticalSection(&dp->cs);
    m->next = NULL;
    if (dp->qtail) dp->qtail->next = m; else dp->qhead = m;
    dp->qtail = m; dp->qcount++;
    LeaveCriticalSection(&dp->cs);
    if (dp->hEvent) SetEvent(dp->hEvent);
}
static void clear_queue(DP *dp) {
    EnterCriticalSection(&dp->cs);
    for (Msg *m = dp->qhead, *n; m; m = n) { n = m->next; free(m); }
    dp->qhead = dp->qtail = NULL; dp->qcount = 0;
    LeaveCriticalSection(&dp->cs);
}
static void push_sys(DP *dp, DWORD sys, DWORD id, const char *sn, const char *ln, DWORD cur) {
    Msg *m = calloc(1, sizeof(Msg));
    m->sys = sys; m->dpid = id; m->cur = cur;
    lstrcpynA(m->sname, sn, NAMELEN); lstrcpynA(m->lname, ln, NAMELEN);
    push_msg(dp, m);
}

static DWORD WINAPI reader_thread(void *arg) {
    DP *dp = arg;
    SOCKET s = dp->s;
    for (;;) {
        DWORD len; BYTE type;
        if (!recv_all(s, &len, 4) || len < 1 || len > 1 << 20 || !recv_all(s, &type, 1)) break;
        DWORD plen = len - 1;
        BYTE *p = malloc(plen + 1);
        if (!p || (plen && !recv_all(s, p, (int)plen))) { free(p); break; }
        if (type == S_DATA && plen >= 8) {
            Msg *m = calloc(1, sizeof(Msg) + plen - 8);
            memcpy(&m->from, p, 4); memcpy(&m->to, p + 4, 4); m->size = plen - 8; memcpy(m->data, p + 8, m->size);
            push_msg(dp, m);
        } else if ((type == S_SYSCREATE || type == S_SYSDESTROY) && plen >= 8 + 2 * NAMELEN) {
            DWORD id, cur; memcpy(&id, p, 4); memcpy(&cur, p + 4, 4);
            char sn[NAMELEN], ln[NAMELEN]; memcpy(sn, p + 8, NAMELEN); memcpy(ln, p + 8 + NAMELEN, NAMELEN);
            sn[NAMELEN - 1] = ln[NAMELEN - 1] = 0;
            EnterCriticalSection(&dp->cs);
            if (type == S_SYSCREATE) add_player(dp, id, sn, ln, 0); else del_player(dp, id);
            LeaveCriticalSection(&dp->cs);
            logf("%s player %08lx '%s'", type == S_SYSCREATE ? "remote" : "lost", id, sn);
            push_sys(dp, type == S_SYSCREATE ? DPSYS_CREATEPLAYERORGROUP : DPSYS_DESTROYPLAYERORGROUP, id, sn, ln, cur);
        } else if (type == S_SESSIONS && plen >= 4) {
            DWORD n; memcpy(&n, p, 4);
            EnterCriticalSection(&dp->cs);
            dp->nsess = 0;
            for (DWORD i = 0; i < n && i < 64 && 4 + (i + 1) * SESS_WIRE <= plen; i++) {
                read_sess(&dp->sess[dp->nsess], p + 4 + i * SESS_WIRE);
                lstrcpynA(dp->sess[dp->nsess].addr, dp->conn_to, NAMELEN);
                dp->nsess++;
            }
            dp->have_enum = 1;
            LeaveCriticalSection(&dp->cs);
            if (dp->wait_type == S_SESSIONS) SetEvent(dp->reply_ev);
        } else if (type == dp->wait_type) {
            free(dp->reply); dp->reply = p; dp->reply_len = plen; p = NULL;
            SetEvent(dp->reply_ev);
        }
        free(p);
    }
    logf("connection to %s closed", dp->conn_to);
    if (InterlockedExchange(&dp->alive, 0) && dp->in_session) {
        /* the host (or the relay) went away: tell the game every remote player left */
        EnterCriticalSection(&dp->cs);
        Player copy[64]; int n = 0;
        for (int i = 0; i < dp->nplayers; i++) if (!dp->players[i].local) copy[n++] = dp->players[i];
        LeaveCriticalSection(&dp->cs);
        for (int i = 0; i < n; i++) push_sys(dp, DPSYS_DESTROYPLAYERORGROUP, copy[i].id, copy[i].sname, copy[i].lname, 0);
    }
    SetEvent(dp->reply_ev);
    return 0;
}

static void disconnect(DP *dp) {
    if (dp->s != INVALID_SOCKET) { shutdown(dp->s, SD_BOTH); closesocket(dp->s); }
    if (dp->thread) { WaitForSingleObject(dp->thread, 3000); CloseHandle(dp->thread); dp->thread = NULL; }
    dp->s = INVALID_SOCKET; dp->alive = 0; dp->conn_to[0] = 0;
}

/* connect to a hub (local mode: "addr", hub port) or the relay (server mode) */
static int connect_to(DP *dp, const char *addr) {
    const char *host = g_local ? addr : g_server;
    int port = g_local ? g_hubport : g_port;
    if (dp->alive && !strcmp(dp->conn_to, host)) return 1;
    disconnect(dp);
    dp->s = hub_connect(host, port, 3000);
    if (dp->s == INVALID_SOCKET) return 0;
    lstrcpynA(dp->conn_to, host, NAMELEN);
    dp->alive = 1;
    dp->thread = CreateThread(NULL, 0, reader_thread, dp, 0, NULL);
    logf("connected to %s:%d", host, port);
    return 1;
}

static int request(DP *dp, int type, const void *a, int alen, int reply_type, DWORD timeout) {
    if (!dp->alive) return 0;
    ResetEvent(dp->reply_ev);
    dp->wait_type = reply_type;
    if (!send_frame(dp->s, &dp->sendcs, type, a, alen, NULL, 0)) { dp->wait_type = 0; return 0; }
    DWORD r = WaitForSingleObject(dp->reply_ev, timeout);
    dp->wait_type = 0;
    return r == WAIT_OBJECT_0 && dp->alive;
}

/* ---- IUnknown */
static HRESULT WINAPI DP_QueryInterface(DP *dp, REFIID riid, void **ppv) { *ppv = dp; InterlockedIncrement(&dp->ref); return S_OK; }
static ULONG WINAPI DP_AddRef(DP *dp) { return InterlockedIncrement(&dp->ref); }
static HRESULT WINAPI DP_Close(DP *dp);
static ULONG WINAPI DP_Release(DP *dp) {
    LONG r = InterlockedDecrement(&dp->ref);
    if (r) return r;
    if (dp->in_session) DP_Close(dp);
    disconnect(dp);
    clear_queue(dp);
    free(dp->reply);
    CloseHandle(dp->reply_ev);
    DeleteCriticalSection(&dp->cs); DeleteCriticalSection(&dp->sendcs);
    free(dp);
    return 0;
}

/* ---- connections */
typedef struct { char magic[4]; DWORD kind; char ip[NAMELEN]; } ConnBlob;

static HRESULT WINAPI DP_EnumConnections(DP *dp, const GUID *app, ENUMCONN_CB cb, void *ctx, DWORD flags) {
    ConnBlob c = {{'A', 'X', 'N', 'A'}, 0, ""};
    DPNAME_ n = {sizeof(DPNAME_), 0, "Internet TCP/IP Connection For DirectPlay", NULL};
    if (!cb(&SP_TCPIP, &c, sizeof c, &n, 0, ctx)) return DP_OK;
    ConnBlob x = {{'A', 'X', 'N', 'A'}, 1, ""};
    DPNAME_ m = {sizeof(DPNAME_), 0, "IPX Connection For DirectPlay (Axis LAN)", NULL};
    cb(&SP_IPX, &x, sizeof x, &m, 0, ctx);
    return DP_OK;
}
static HRESULT WINAPI DP_InitializeConnection(DP *dp, void *conn, DWORD flags) {
    if (dp->initialized) return DPERR_ALREADYINITIALIZED;
    wsa_init();  /* DirectPlay's TCP/IP provider starts Winsock here; the game relies on it (gethostname) */
    ConnBlob *c = conn;
    dp->target[0] = 0;
    if (c && !memcmp(c->magic, "AXNA", 4)) lstrcpynA(dp->target, c->ip, NAMELEN);
    trim(dp->target);
    dp->initialized = 1;
    logf("InitializeConnection target='%s' (%s mode)", dp->target, g_local ? "local" : "server");
    return DP_OK;
}
static HRESULT WINAPI DP_GetCaps(DP *dp, DPCAPS_ *caps, DWORD flags) {
    if (!caps) return E_INVALIDARG;
    DWORD size = caps->dwSize;
    memset(caps, 0, sizeof *caps);
    caps->dwSize = size ? size : sizeof *caps;
    caps->dwFlags = 0x8 | (dp->is_host ? 0x2 : 0);
    caps->dwMaxBufferSize = 65000; caps->dwMaxPlayers = 64; caps->dwLatency = 50;
    caps->dwMaxLocalPlayers = 64; caps->dwHeaderLength = 20; caps->dwTimeout = 5000;
    return DP_OK;
}

/* ---- sessions */
static void fill_sd(DPSD2 *sd, const Sess *x, char *name) {
    memset(sd, 0, sizeof *sd);
    sd->dwSize = sizeof *sd; sd->dwFlags = x->flags; sd->guidInstance = x->inst;
    sd->dwMaxPlayers = x->maxp; sd->dwCurrentPlayers = x->cur;
    lstrcpynA(name, x->name, NAMELEN); sd->lpszSessionNameA = name;
    sd->dwUser1 = x->u1; sd->dwUser2 = x->u2; sd->dwUser3 = x->u3; sd->dwUser4 = x->u4;
    /* the game pings dwUser4 (the host's own LAN address); use the address we reached it at */
    if (g_local && x->addr[0]) { unsigned long a = inet_addr(x->addr); if (a != INADDR_NONE) sd->dwUser4 = a; }
}

static void refresh_sessions(DP *dp) {
    if (g_local && !dp->target[0]) {  /* no address: search the LAN */
        Disc d[32]; int n = discover(d, 32, 500);
        EnterCriticalSection(&dp->cs);
        dp->nsess = 0;
        for (int i = 0; i < n && i < 64; i++) dp->sess[dp->nsess++] = d[i].s;
        dp->have_enum = 1;
        LeaveCriticalSection(&dp->cs);
        return;
    }
    if (!connect_to(dp, dp->target)) { EnterCriticalSection(&dp->cs); dp->nsess = 0; dp->have_enum = 1; LeaveCriticalSection(&dp->cs); return; }
    char ip[NAMELEN] = {0}; lstrcpynA(ip, dp->target, NAMELEN);
    request(dp, C_ENUM, ip, NAMELEN, S_SESSIONS, 2000);
}

static HRESULT WINAPI DP_EnumSessions(DP *dp, DPSD2 *sd, DWORD timeout, ENUMSESS_CB cb, void *ctx, DWORD flags) {
    if (flags & DPENUMSESSIONS_STOPASYNC) return DP_OK;
    if (!dp->initialized) return DPERR_NOCONNECTION;
    DWORD now = GetTickCount();
    if (!(flags & DPENUMSESSIONS_ASYNC) || !dp->have_enum || now - dp->last_enum > 1500) {
        refresh_sessions(dp);
        dp->last_enum = GetTickCount();
    }
    Sess copy[64]; int n;
    EnterCriticalSection(&dp->cs);
    n = dp->nsess; memcpy(copy, dp->sess, sizeof(Sess) * n);
    LeaveCriticalSection(&dp->cs);
    for (int i = 0; i < n; i++) {
        DPSD2 d; char name[NAMELEN]; DWORD to = timeout;
        fill_sd(&d, &copy[i], name);
        if (sd) d.guidApplication = sd->guidApplication;
        if (!cb(&d, &to, 0, ctx)) return DP_OK;
    }
    DWORD to = timeout;
    cb(NULL, &to, DPESC_TIMEDOUT, ctx);
    return DP_OK;
}

static HRESULT WINAPI DP_Open(DP *dp, DPSD2 *sd, DWORD flags) {
    if (!dp->initialized) return DPERR_NOCONNECTION;
    if (flags & DPOPEN_CREATE) {
        if (g_local && !hub_start()) return DPERR_CANTCREATESESSION;
        if (!connect_to(dp, "127.0.0.1")) return DPERR_CANTCREATESESSION;
        struct { DWORD flags, maxp, u1, u2, u3, u4; char name[NAMELEN]; char pw[16]; char ips[128]; } h;
        memset(&h, 0, sizeof h);
        h.flags = sd->dwFlags; h.maxp = sd->dwMaxPlayers;
        h.u1 = sd->dwUser1; h.u2 = sd->dwUser2; h.u3 = sd->dwUser3; h.u4 = sd->dwUser4;
        if (sd->lpszSessionNameA) lstrcpynA(h.name, sd->lpszSessionNameA, NAMELEN);
        if (sd->lpszPasswordA) lstrcpynA(h.pw, sd->lpszPasswordA, 16);
        local_ips(h.ips, sizeof h.ips);
        if (!request(dp, C_HOST, &h, sizeof h, S_HOSTED, 5000) || dp->reply_len < 20) return DPERR_CANTCREATESESSION;
        HRESULT hr; memcpy(&hr, dp->reply, 4);
        if (hr != DP_OK) return hr;
        dp->sd = *sd; memcpy(&dp->sd.guidInstance, dp->reply + 4, 16);
        lstrcpynA(dp->sessname, h.name, NAMELEN); dp->sd.lpszSessionNameA = dp->sessname; dp->sd.lpszPasswordA = NULL;
        dp->in_session = 1; dp->is_host = 1;
        logf("hosting session '%s' (max %lu)", h.name, h.maxp);
        return DP_OK;
    }
    if (flags & DPOPEN_JOIN) {
        char addr[NAMELEN] = "";
        EnterCriticalSection(&dp->cs);
        for (int i = 0; i < dp->nsess; i++) if (IsEqualGUID(&dp->sess[i].inst, &sd->guidInstance)) lstrcpynA(addr, dp->sess[i].addr, NAMELEN);
        LeaveCriticalSection(&dp->cs);
        if (!addr[0]) lstrcpynA(addr, dp->target, NAMELEN);
        if (!connect_to(dp, addr)) return DPERR_NOSESSIONS;
        struct { GUID g; char pw[16]; } j;
        memset(&j, 0, sizeof j); j.g = sd->guidInstance;
        if (sd->lpszPasswordA) lstrcpynA(j.pw, sd->lpszPasswordA, 16);
        if (!request(dp, C_JOIN, &j, sizeof j, S_JOINED, 5000)) return DPERR_TIMEOUT;
        if (dp->reply_len < 4) return DPERR_NOSESSIONS;
        HRESULT hr; memcpy(&hr, dp->reply, 4);
        if (hr != DP_OK) { logf("join refused %08lx", hr); return hr; }
        if (dp->reply_len < 4 + SESS_WIRE + 4) return DPERR_NOSESSIONS;
        Sess x; read_sess(&x, dp->reply + 4);
        fill_sd(&dp->sd, &x, dp->sessname);
        dp->sd.guidApplication = sd->guidApplication;
        DWORD n; memcpy(&n, dp->reply + 4 + SESS_WIRE, 4);
        const BYTE *p = dp->reply + 8 + SESS_WIRE;
        EnterCriticalSection(&dp->cs);
        dp->nplayers = 0;
        for (DWORD i = 0; i < n && p + 4 + 2 * NAMELEN <= dp->reply + dp->reply_len; i++, p += 4 + 2 * NAMELEN) {
            DWORD id; memcpy(&id, p, 4);
            add_player(dp, id, (const char *)p + 4, (const char *)p + 4 + NAMELEN, 0);
        }
        LeaveCriticalSection(&dp->cs);
        dp->in_session = 1; dp->is_host = 0;
        logf("joined '%s' at %s (%lu players)", x.name, addr, n);
        return DP_OK;
    }
    return E_INVALIDARG;
}

static HRESULT WINAPI DP_Close(DP *dp) {
    if (dp->in_session && dp->alive) send_frame(dp->s, &dp->sendcs, C_CLOSE, NULL, 0, NULL, 0);
    dp->in_session = 0; dp->is_host = 0;
    EnterCriticalSection(&dp->cs); dp->nplayers = 0; LeaveCriticalSection(&dp->cs);
    clear_queue(dp);
    logf("Close");
    return DP_OK;
}
static HRESULT WINAPI DP_GetSessionDesc(DP *dp, void *data, DWORD *size) {
    if (!dp->in_session) return DPERR_NOCONNECTION;
    DWORD need = sizeof(DPSD2) + NAMELEN;
    if (!data || *size < need) { *size = need; return DPERR_BUFFERTOOSMALL; }
    DPSD2 *d = data; *d = dp->sd;
    char *name = (char *)data + sizeof(DPSD2); lstrcpynA(name, dp->sessname, NAMELEN);
    d->lpszSessionNameA = name; d->lpszPasswordA = NULL;
    EnterCriticalSection(&dp->cs); d->dwCurrentPlayers = dp->nplayers; LeaveCriticalSection(&dp->cs);
    *size = need;
    return DP_OK;
}
static HRESULT WINAPI DP_SetSessionDesc(DP *dp, DPSD2 *sd, DWORD flags) { return DP_OK; }

/* ---- players */
static HRESULT WINAPI DP_CreatePlayer(DP *dp, DWORD *id, DPNAME_ *name, HANDLE ev, void *data, DWORD size, DWORD flags) {
    if (!dp->in_session) return DPERR_NOCONNECTION;
    struct { char s[NAMELEN]; char l[NAMELEN]; } n;
    memset(&n, 0, sizeof n);
    if (name && name->lpszShortNameA) lstrcpynA(n.s, name->lpszShortNameA, NAMELEN);
    if (name && name->lpszLongNameA) lstrcpynA(n.l, name->lpszLongNameA, NAMELEN);
    if (!request(dp, C_CREATEPLAYER, &n, sizeof n, S_PLAYER, 5000) || dp->reply_len < 8) return DPERR_CANTADDPLAYER;
    HRESULT hr; memcpy(&hr, dp->reply, 4);
    if (hr != DP_OK) return hr;
    memcpy(id, dp->reply + 4, 4);
    if (ev) dp->hEvent = ev;
    EnterCriticalSection(&dp->cs); add_player(dp, *id, n.s, n.l, 1); LeaveCriticalSection(&dp->cs);
    logf("local player %08lx '%s'", *id, n.s);
    return DP_OK;
}
static HRESULT WINAPI DP_DestroyPlayer(DP *dp, DWORD id) {
    if (dp->alive) send_frame(dp->s, &dp->sendcs, C_DESTROYPLAYER, &id, 4, NULL, 0);
    EnterCriticalSection(&dp->cs); del_player(dp, id); LeaveCriticalSection(&dp->cs);
    return DP_OK;
}
static HRESULT WINAPI DP_GetPlayerName(DP *dp, DWORD id, void *data, DWORD *size) {
    char s[NAMELEN], l[NAMELEN];
    EnterCriticalSection(&dp->cs);
    Player *p = find_player(dp, id);
    if (p) { lstrcpynA(s, p->sname, NAMELEN); lstrcpynA(l, p->lname, NAMELEN); }
    LeaveCriticalSection(&dp->cs);
    if (!p) return DPERR_INVALIDPLAYER;
    DWORD need = sizeof(DPNAME_) + (DWORD)strlen(s) + 1 + (DWORD)strlen(l) + 1;
    if (!data || *size < need) { *size = need; return DPERR_BUFFERTOOSMALL; }
    DPNAME_ *n = data; char *q = (char *)data + sizeof(DPNAME_);
    n->dwSize = sizeof(DPNAME_); n->dwFlags = 0;
    strcpy(q, s); n->lpszShortNameA = q; q += strlen(s) + 1;
    strcpy(q, l); n->lpszLongNameA = l[0] ? q : NULL;
    *size = need;
    return DP_OK;
}
static HRESULT WINAPI DP_EnumPlayers(DP *dp, GUID *g, ENUMPLAYER_CB cb, void *ctx, DWORD flags) {
    Player copy[64]; int n;
    EnterCriticalSection(&dp->cs); n = dp->nplayers; memcpy(copy, dp->players, sizeof(Player) * n); LeaveCriticalSection(&dp->cs);
    for (int i = 0; i < n; i++) {
        DPNAME_ nm = {sizeof(DPNAME_), 0, copy[i].sname, copy[i].lname[0] ? copy[i].lname : NULL};
        if (!cb(copy[i].id, DPPLAYERTYPE_PLAYER, &nm, copy[i].local ? 8 : 0, ctx)) break;
    }
    return DP_OK;
}

/* ---- messages */
static HRESULT WINAPI DP_Send(DP *dp, DWORD from, DWORD to, DWORD flags, void *data, DWORD size) {
    if (!dp->in_session) return DPERR_NOCONNECTION;
    EnterCriticalSection(&dp->cs);
    Player *p = find_player(dp, to);
    int local = to != DPID_ALLPLAYERS && p && p->local;
    LeaveCriticalSection(&dp->cs);
    if (local) {
        Msg *m = calloc(1, sizeof(Msg) + size);
        m->from = from; m->to = to; m->size = size; memcpy(m->data, data, size);
        push_msg(dp, m);
        return DP_OK;
    }
    DWORD hdr[3] = {from, to, flags};
    if (!send_frame(dp->s, &dp->sendcs, C_SEND, hdr, sizeof hdr, data, (int)size)) return DPERR_NOCONNECTION;
    return DP_OK;
}
static HRESULT WINAPI DP_SendEx(DP *dp, DWORD from, DWORD to, DWORD flags, void *data, DWORD size,
                                DWORD prio, DWORD timeout, void *ctx, DWORD *msgid) {
    return DP_Send(dp, from, to, flags, data, size);
}
static DWORD msg_size(const Msg *m) {
    DWORD names = (DWORD)strlen(m->sname) + 1 + (DWORD)strlen(m->lname) + 1;
    if (m->sys == DPSYS_CREATEPLAYERORGROUP) return sizeof(MSG_CREATE) + names;
    if (m->sys == DPSYS_DESTROYPLAYERORGROUP) return sizeof(MSG_DESTROY) + names;
    return m->size;
}
static void msg_build(const Msg *m, BYTE *out) {
    if (!m->sys) { memcpy(out, m->data, m->size); return; }
    DPNAME_ *n; char *q;
    if (m->sys == DPSYS_CREATEPLAYERORGROUP) {
        MSG_CREATE *c = (MSG_CREATE *)out; memset(c, 0, sizeof *c);
        c->dwType = DPSYS_CREATEPLAYERORGROUP; c->dwPlayerType = DPPLAYERTYPE_PLAYER;
        c->dpId = m->dpid; c->dwCurrentPlayers = m->cur; n = &c->dpnName; q = (char *)(c + 1);
    } else {
        MSG_DESTROY *d = (MSG_DESTROY *)out; memset(d, 0, sizeof *d);
        d->dwType = DPSYS_DESTROYPLAYERORGROUP; d->dwPlayerType = DPPLAYERTYPE_PLAYER;
        d->dpId = m->dpid; n = &d->dpnName; q = (char *)(d + 1);
    }
    n->dwSize = sizeof(DPNAME_);
    strcpy(q, m->sname); n->lpszShortNameA = q; q += strlen(m->sname) + 1;
    strcpy(q, m->lname); n->lpszLongNameA = m->lname[0] ? q : NULL;
}
static HRESULT WINAPI DP_Receive(DP *dp, DWORD *from, DWORD *to, DWORD flags, void *data, DWORD *size) {
    EnterCriticalSection(&dp->cs);
    Msg *prev = NULL, *m = dp->qhead;
    for (; m; prev = m, m = m->next) {
        if ((flags & DPRECEIVE_TOPLAYER) && to && m->to != *to && m->to != DPID_ALLPLAYERS) continue;
        if ((flags & DPRECEIVE_FROMPLAYER) && from && m->from != *from) continue;
        break;
    }
    if (!m) { LeaveCriticalSection(&dp->cs); return DPERR_NOMESSAGES; }
    DWORD need = msg_size(m);
    if (!data || !size || *size < need) { if (size) *size = need; LeaveCriticalSection(&dp->cs); return DPERR_BUFFERTOOSMALL; }
    msg_build(m, data);
    *size = need;
    if (from) *from = m->sys ? DPID_SYSMSG : m->from;
    if (to) *to = m->to;
    if (!(flags & DPRECEIVE_PEEK)) {
        if (prev) prev->next = m->next; else dp->qhead = m->next;
        if (dp->qtail == m) dp->qtail = prev;
        dp->qcount--;
        free(m);
    }
    LeaveCriticalSection(&dp->cs);
    return DP_OK;
}
static HRESULT WINAPI DP_GetMessageCount(DP *dp, DWORD id, DWORD *count) {
    EnterCriticalSection(&dp->cs); *count = dp->qcount; LeaveCriticalSection(&dp->cs);
    return DP_OK;
}

static HRESULT WINAPI DP_Unsupported(void) { return DPERR_UNSUPPORTED; }
#define U ((void *)DP_Unsupported)
static void *dp_vtbl[] = {
    DP_QueryInterface, DP_AddRef, DP_Release,
    U, DP_Close, U, DP_CreatePlayer, U, U, DP_DestroyPlayer, U, U, DP_EnumPlayers,
    DP_EnumSessions, DP_GetCaps, U, U, DP_GetMessageCount, U, U, U, DP_GetPlayerName, DP_GetSessionDesc,
    U, DP_Open, DP_Receive, DP_Send, U, U, U, U, DP_SetSessionDesc,
    U, U, U, DP_EnumConnections, U, U, DP_InitializeConnection, U, U, U, U, U, U, U, U,
    U, U, DP_SendEx, U, U, U
};
static DP *new_dp(void) {
    DP *dp = calloc(1, sizeof *dp);
    dp->vtbl = dp_vtbl; dp->ref = 1; dp->s = INVALID_SOCKET;
    InitializeCriticalSection(&dp->cs); InitializeCriticalSection(&dp->sendcs);
    dp->reply_ev = CreateEventA(NULL, TRUE, FALSE, NULL);
    return dp;
}

/* ------------------------------------------------------------------ DirectPlayLobby object */
typedef struct { const void *vtbl; LONG ref; } Lobby;
static HRESULT WINAPI LB_QueryInterface(Lobby *l, REFIID riid, void **ppv) { *ppv = l; InterlockedIncrement(&l->ref); return S_OK; }
static ULONG WINAPI LB_AddRef(Lobby *l) { return InterlockedIncrement(&l->ref); }
static ULONG WINAPI LB_Release(Lobby *l) { LONG r = InterlockedDecrement(&l->ref); if (!r) free(l); return r; }
static HRESULT WINAPI LB_GetConnectionSettings(Lobby *l, DWORD app, void *data, DWORD *size) { return DPERR_NOTLOBBIED; }
static HRESULT WINAPI LB_CreateCompoundAddress(Lobby *l, DPCAE *el, DWORD count, void *addr, DWORD *size) {
    if (!size) return E_INVALIDARG;
    if (!addr || *size < sizeof(ConnBlob)) { *size = sizeof(ConnBlob); return DPERR_BUFFERTOOSMALL; }
    ConnBlob *c = addr; memset(c, 0, sizeof *c); memcpy(c->magic, "AXNA", 4);
    for (DWORD i = 0; i < count; i++) {
        if (IsEqualGUID(&el[i].guidDataType, &SP_IPX)) c->kind = 1;
        if (IsEqualGUID(&el[i].guidDataType, &DPAID_INet_) && el[i].lpData)
            lstrcpynA(c->ip, el[i].lpData, el[i].dwDataSize && el[i].dwDataSize < NAMELEN ? el[i].dwDataSize + 1 : NAMELEN);
    }
    *size = sizeof(ConnBlob);
    return DP_OK;
}
static HRESULT WINAPI LB_CreateAddress(Lobby *l, const GUID *sp, const GUID *type, void *data, DWORD dsize, void *addr, DWORD *size) {
    DPCAE el[2] = {{SP_TCPIP, 16, (void *)sp}, {*type, dsize, data}};
    return LB_CreateCompoundAddress(l, el, 2, addr, size);
}
static HRESULT WINAPI LB_Unsupported(void) { return DPERR_UNSUPPORTED; }
#define LU ((void *)LB_Unsupported)
static void *lobby_vtbl[] = {
    LB_QueryInterface, LB_AddRef, LB_Release, LU, LB_CreateAddress, LU, LU, LU,
    LB_GetConnectionSettings, LU, LU, LU, LU, LU, LB_CreateCompoundAddress, LU, LU, LU, LU
};

/* ------------------------------------------------------------------ hooks */
typedef HRESULT (WINAPI *COCREATE)(REFCLSID, void *, DWORD, REFIID, void **);
typedef DWORD (WINAPI *ICMPSEND)(HANDLE, DWORD, void *, WORD, void *, void *, DWORD, DWORD);
static COCREATE real_CoCreateInstance;
static ICMPSEND real_IcmpSendEcho;

static HRESULT WINAPI hook_CoCreateInstance(REFCLSID clsid, void *outer, DWORD ctx, REFIID iid, void **ppv) {
    if (IsEqualGUID(clsid, &CLSID_DirectPlay_)) { *ppv = new_dp(); return S_OK; }
    if (IsEqualGUID(clsid, &CLSID_DirectPlayLobby_)) {
        Lobby *l = calloc(1, sizeof *l); l->vtbl = lobby_vtbl; l->ref = 1; *ppv = l; return S_OK;
    }
    return real_CoCreateInstance(clsid, outer, ctx, iid, ppv);
}

/* ping: round trip to the game's hub (local mode) or the relay (server mode), cached per address */
static CRITICAL_SECTION g_pingcs;
static struct { DWORD ip, rtt, when; int ok; } g_pings[32];
static int measure_rtt(const char *host, int port, DWORD *rtt) {
    SOCKET s = hub_connect(host, port, 1000);
    if (s == INVALID_SOCKET) return 0;
    DWORD tmo = 1500; setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&tmo, sizeof tmo);
    LARGE_INTEGER f, a, b; QueryPerformanceFrequency(&f); QueryPerformanceCounter(&a);
    DWORD tok = a.LowPart, len, got; BYTE type; int ok = 0;
    if (send_frame(s, NULL, C_PING, &tok, 4, NULL, 0) && recv_all(s, &len, 4) && len == 5 &&
        recv_all(s, &type, 1) && recv_all(s, &got, 4) && type == S_PONG && got == tok) {
        QueryPerformanceCounter(&b);
        *rtt = (DWORD)((b.QuadPart - a.QuadPart) * 1000 / f.QuadPart); ok = 1;
    }
    closesocket(s);
    return ok;
}
static int ping_cached(DWORD dest, DWORD *rtt) {
    DWORD key = g_local ? dest : 0, now = GetTickCount();
    EnterCriticalSection(&g_pingcs);
    for (int i = 0; i < 32; i++)
        if (g_pings[i].when && g_pings[i].ip == key && now - g_pings[i].when < 3000) {
            int ok = g_pings[i].ok; *rtt = g_pings[i].rtt; LeaveCriticalSection(&g_pingcs); return ok;
        }
    LeaveCriticalSection(&g_pingcs);
    struct in_addr ia; ia.s_addr = dest;
    char host[32]; lstrcpynA(host, g_local ? inet_ntoa(ia) : g_server, sizeof host);
    int ok = measure_rtt(host, g_local ? g_hubport : g_port, rtt);
    EnterCriticalSection(&g_pingcs);
    int slot = 0; for (int i = 1; i < 32; i++) if (g_pings[i].when < g_pings[slot].when) slot = i;
    g_pings[slot].ip = key; g_pings[slot].rtt = *rtt; g_pings[slot].ok = ok; g_pings[slot].when = GetTickCount() | 1;
    LeaveCriticalSection(&g_pingcs);
    return ok;
}
typedef struct { DWORD Address, Status, RoundTripTime; WORD DataSize, Reserved; void *Data;
                 BYTE Ttl, Tos, Flags, OptionsSize; void *OptionsData; } ECHO_REPLY;
static DWORD WINAPI hook_IcmpSendEcho(HANDLE h, DWORD dest, void *req, WORD reqsize, void *opt, void *reply,
                                      DWORD replysize, DWORD timeout) {
    DWORD rtt = 0;
    if (!reply || replysize < sizeof(ECHO_REPLY) + reqsize || !ping_cached(dest, &rtt)) return 0;
    ECHO_REPLY *r = reply; memset(r, 0, sizeof *r);
    r->Address = dest; r->RoundTripTime = rtt ? rtt : 1; r->DataSize = reqsize; r->Ttl = 128;
    r->Data = (BYTE *)reply + sizeof(ECHO_REPLY);
    if (reqsize && req) memcpy(r->Data, req, reqsize);
    return 1;
}

/* ------------------------------------------------------------------ ending movie */
static LRESULT CALLBACK movie_wndproc(HWND w, UINT m, WPARAM wp, LPARAM lp) {
    if (m == WM_SETCURSOR) { SetCursor(NULL); return TRUE; }
    return DefWindowProcA(w, m, wp, lp);
}

/* same arguments as the game's routine: (owner, file, width, height), cdecl */
static void __cdecl play_movie(HWND owner, const char *file, int gw, int gh) {
    char path[MAX_PATH];
    if (!GetFullPathNameA(file, sizeof path, path, NULL)) lstrcpynA(path, file, sizeof path);
    /* the original movies are Indeo 3, which Windows no longer decodes (iv32\iv32.c) */
    logf("movie: Indeo 3 decoder %s", iv32_install() ? "installed" : "NOT installed");
    /* the game is DPI-unaware: with display scaling it sees a scaled-down screen, but MCIAVI multiplies the
       rectangles it is given by the scale factor (DESKTOPHORZRES / HORZRES, e.g. 1.5 at 150%) */
    HDC sdc = GetDC(NULL);
    int physw = GetDeviceCaps(sdc, DESKTOPHORZRES), logw = GetDeviceCaps(sdc, HORZRES);
    ReleaseDC(NULL, sdc);
    if (physw <= 0 || logw <= 0) physw = logw = 1;
    int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
    WNDCLASSA wc = {0};
    wc.lpfnWndProc = movie_wndproc; wc.hInstance = GetModuleHandleA(NULL);
    wc.hbrBackground = GetStockObject(BLACK_BRUSH); wc.lpszClassName = "AxisMovie";
    RegisterClassA(&wc);
    HWND win = CreateWindowExA(WS_EX_TOPMOST, wc.lpszClassName, "Axis", WS_POPUP | WS_VISIBLE, 0, 0, sw, sh,
                               owner, NULL, wc.hInstance, NULL);
    MCI_DGV_OPEN_PARMSA op = {0};
    op.lpstrDeviceType = "AVIVideo"; op.lpstrElementName = path;
    MCIERROR e = win ? mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&op) : MCIERR_INTERNAL;
    logf("movie %s (%dx%d screen): open %s (mci error %lu)", path, sw, sh, e ? "FAILED" : "ok", e);
    if (e) {
        if (win) DestroyWindow(win);
        UnregisterClassA(wc.lpszClassName, wc.hInstance);
        return;
    }
    MCIDEVICEID dev = op.wDeviceID;
    /* fit to the screen keeping the movie's aspect (MCI rects are x, y, width, height) */
    MCI_DGV_RECT_PARMS src = {0};
    int vw = 4, vh = 3;
    if (!mciSendCommandA(dev, MCI_WHERE, MCI_DGV_WHERE_SOURCE, (DWORD_PTR)&src) && src.rc.right > 0 && src.rc.bottom > 0) {
        vw = src.rc.right; vh = src.rc.bottom;
    }
    int dw = sw, dh = sw * vh / vw;
    if (dh > sh) { dh = sh; dw = sh * vw / vh; }
    /* the movie draws centred into the black full-screen window (MCI rect: x, y, width, height) */
    MCI_DGV_WINDOW_PARMSA wnd = {0};
    wnd.hWnd = win;
    mciSendCommandA(dev, MCI_WINDOW, MCI_DGV_WINDOW_HWND, (DWORD_PTR)&wnd);
    MCI_DGV_PUT_PARMS put = {0};
    put.rc.left = MulDiv((sw - dw) / 2, logw, physw); put.rc.top = MulDiv((sh - dh) / 2, logw, physw);
    put.rc.right = MulDiv(dw, logw, physw); put.rc.bottom = MulDiv(dh, logw, physw);
    mciSendCommandA(dev, MCI_PUT, MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT, (DWORD_PTR)&put);
    logf("movie %dx%d source on %dx%d screen (scale %d/%d), destination %ld,%ld %ldx%ld", vw, vh, sw, sh, physw, logw,
         put.rc.left, put.rc.top, put.rc.right, put.rc.bottom);
    SetForegroundWindow(win);
    MCI_DGV_PLAY_PARMS play = {0};
    e = mciSendCommandA(dev, MCI_PLAY, 0, (DWORD_PTR)&play);
    DWORD start = GetTickCount();
    int quit = 0, played = 0;
    WPARAM quitcode = 0;
    while (!e) {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) { quit = 1; quitcode = msg.wParam; continue; }
            TranslateMessage(&msg); DispatchMessageA(&msg);
        }
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) break;
        MCI_STATUS_PARMS st = {0};
        st.dwItem = MCI_STATUS_MODE;
        if (mciSendCommandA(dev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&st)) break;
        if (st.dwReturn == MCI_MODE_PLAY) played = 1;
        else if (st.dwReturn != MCI_MODE_SEEK && (played || GetTickCount() - start > 3000)) break;
        Sleep(15);
    }
    logf("movie finished (play error %lu, played %d)", e, played);
    mciSendCommandA(dev, MCI_CLOSE, 0, 0);
    DestroyWindow(win);
    UnregisterClassA(wc.lpszClassName, wc.hInstance);
    if (quit) PostQuitMessage((int)quitcode);
}

/* find the game's movie routine in the exe's code and jump to play_movie instead */
static int hook_movie(HMODULE mod) {
    static const BYTE sig[] = {0x83,0xec,0x5c,0x8b,0x44,0x24,0x64,0x53,0x56,0x8b,0x35,0,0,0,0,0x8d,0x4c,0x24,0x48,0x57,0x51,
                               0x68,0x00,0x22,0x01,0x00,0x33,0xff,0x68,0x03,0x08,0x00,0x00};
    BYTE *base = (BYTE *)mod;
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + ((IMAGE_DOS_HEADER *)base)->e_lfanew);
    IMAGE_SECTION_HEADER *s = IMAGE_FIRST_SECTION(nt);
    BYTE *p = base + s->VirtualAddress, *end = p + s->Misc.VirtualSize - sizeof sig;
    for (; p < end; p++) {
        int i = 0;
        while (i < (int)sizeof sig && (p[i] == sig[i] || (i >= 11 && i < 15))) i++;
        if (i < (int)sizeof sig) continue;
        DWORD old;
        VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
        p[0] = 0xe9; *(INT32 *)(p + 1) = (INT32)((BYTE *)play_movie - (p + 5));
        VirtualProtect(p, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), p, 5);
        return 1;
    }
    return 0;
}

/* ------------------------------------------------------------------ proportional HUD (AxisGL)
 * The in-match HUD is laid out in 640x480 units and drawn with x scaled by width/640 and y by height/480,
 * so on anything wider than 4:3 the armor/shield/ammo digits and panels were stretched sideways. Every
 * 2D vertex goes through glVertex2i; for vertices drawn by the HUD code, x is remapped so each element is
 * scaled like y (as on 4:3) and anchored to the left edge, the right edge or the centre of the HUD area
 * (the screen, at most [hud] maxaspect wide - 16:9 by default). Which element a vertex belongs to is
 * known from the code that draws it (return address, or the HUD call site found on the stack).
 * [hud] proportional=0 turns it off. [net] hudtrace=1 logs the x/y range drawn per code site. */
typedef void (WINAPI *GLVERTEX2I)(int, int);
typedef void (WINAPI *GLVIEWPORT)(int, int, int, int);
static GLVERTEX2I real_glVertex2i;
static GLVIEWPORT real_glViewport;
static int g_vpx, g_vpw = 1, g_vpy, g_vph;
enum { A_NONE, A_LEFT, A_CENTER, A_RIGHT };
/* Only vertices drawn during the in-match 2D pass (0x4982f0, called once per frame from 0x48b386) are
   remapped; outside it (loading screens, menus) the stack can hold leftover HUD addresses, which made
   loading text jump between two widths. The call is routed through hud_pass_wrap, which counts depth. */
volatile int g_inhud __asm__("axis_inhud");
volatile DWORD g_scene __asm__("axis_scene");
void *g_hudpass_fn __asm__("axis_hudpass") = (void *)0x4982f0;
/* which part of the HUD pass is drawing: 1 = player markers (0x4913a0), 2 = main HUD (0x4926f0) */
volatile int g_area __asm__("axis_area");
void *g_markers_fn __asm__("axis_markers_fn") = (void *)0x4913a0;
void *g_mainhud_fn __asm__("axis_mainhud_fn") = (void *)0x4926f0;
/* 5 = lock-on overlay (0x491f50, the square that closes in on the target). Both marker routines run between
   marker_begin/marker_end (see there); the scene pointer in ecx is kept across the C call. */
void *g_lockon_fn __asm__("axis_lockon_fn") = (void *)0x491f50;
__attribute__((naked)) static void markers_wrap(void) {
    __asm__ volatile("pushl axis_area\n\tmovl $1, axis_area\n\tpushl %ecx\n\tcall axis_marker_begin\n\tpopl %ecx\n\t"
                     "call *axis_markers_fn\n\tcall axis_marker_end\n\tpopl axis_area\n\tret");
}
__attribute__((naked)) static void lockon_wrap(void) {
    __asm__ volatile("pushl axis_area\n\tmovl $5, axis_area\n\tpushl %ecx\n\tcall axis_marker_begin\n\tpopl %ecx\n\t"
                     "call *axis_lockon_fn\n\tcall axis_marker_end\n\tpopl axis_area\n\tret");
}
__attribute__((naked)) static void mainhud_wrap(void) {
    __asm__ volatile("pushl axis_area\n\tmovl $2, axis_area\n\tcall *axis_mainhud_fn\n\tpopl axis_area\n\tret");
}
/* 3 = FPS counter (0x495510, right edge), 4 = "1/4" counter + ranking table (0x494930) */
void *g_fps_fn __asm__("axis_fps_fn") = (void *)0x495510;
void *g_rank_fn __asm__("axis_rank_fn") = (void *)0x494930;
__attribute__((naked)) static void fps_wrap(void) {
    __asm__ volatile("pushl axis_area\n\tmovl $3, axis_area\n\tcall *axis_fps_fn\n\tpopl axis_area\n\tret");
}
__attribute__((naked)) static void rank_wrap(void) {
    __asm__ volatile("pushl axis_area\n\tmovl $4, axis_area\n\tcall *axis_rank_fn\n\tpopl axis_area\n\tret");
}
__attribute__((naked)) static void hud_pass_wrap(void) {
    __asm__ volatile("movl %ecx, axis_scene\n\tincl axis_inhud\n\tcall *axis_hudpass\n\tdecl axis_inhud\n\tret");
}
/* Auto play (replay) overlay: the replay frame (0x487f00) draws its own 2D after the HUD projection 0x4685f0,
   outside the in-match HUD pass: camera icon + number top-left (0x496820 / 0x44ad60 at 16 and 40 units),
   clock icon + time top-right (526 / 550 units), the fading message (0x495190), the followed player's name
   (0x496b80, bottom centre) and the ranking table (0x494930). Their text switches the projection through
   0x41ef90, which put all of it into the centred 4:3 menu box. Each call goes through an OV_WRAP wrapper:
   counted as HUD drawing (remap) with g_area 6 = left, 7 = right, 8 = centre, 4 = ranking - the same
   anchoring as in a match - between ov_begin/ov_end (HUD viewport, see there). The wrapped routine keeps its
   own stack (cdecl or callee-cleaned) and ecx. */
void *g_ov_ret __asm__("axis_ov_ret") __attribute__((used));
int g_ov_area __asm__("axis_ov_area") __attribute__((used));
#define OV_WRAP(name, area, fn) \
    __attribute__((naked)) static void name(void) { \
        __asm__ volatile("popl axis_ov_ret\n\tmovl axis_area, %eax\n\tmovl %eax, axis_ov_area\n\t" \
                         "movl $" #area ", axis_area\n\tincl axis_inhud\n\tpushl %ecx\n\tcall axis_ov_begin\n\tpopl %ecx\n\t" \
                         "movl $" #fn ", %eax\n\tcall *%eax\n\tpushl %eax\n\tcall axis_ov_end\n\t" \
                         "decl axis_inhud\n\tmovl axis_ov_area, %eax\n\tmovl %eax, axis_area\n\t" \
                         "popl %eax\n\tpushl axis_ov_ret\n\tret"); }
OV_WRAP(ov_icon_left, 6, 0x496820)
OV_WRAP(ov_text_left, 6, 0x44ad60)
OV_WRAP(ov_icon_right, 7, 0x496820)
OV_WRAP(ov_text_right, 7, 0x44ad60)
OV_WRAP(ov_message, 8, 0x495190)
OV_WRAP(ov_name, 8, 0x496b80)
OV_WRAP(ov_rank, 4, 0x494930)
#define AXGL_W (*(volatile int *)0xa0e810)   /* render width / height the HUD scales by */
#define AXGL_H (*(volatile int *)0xa0e928)
/* Markers that follow players (reticles, lock-on square, team/leader icons, name labels) are placed at the
   player's projected screen pixel (0x472ec0, the game's own camera matrices) and sized with the width getter
   (x W/640), so wider than 4:3 they were stretched. While they draw, the render width reads as 4H/3: sizes
   become 4:3-proportional and positions are unaffected. g_mw keeps the real width for the vertex hook. */
/* The HUD pass draws into a centred 16:9 viewport on screens wider than that (hudfix), which clipped markers
   of players standing in the outer strips of an ultrawide screen. Markers are placed at screen pixels anyway
   (vertex hook, area 1/5), so they get the full-screen viewport while they draw. */
static volatile int g_mw, g_mwsaved, g_mvpx, g_mvpw;
static void WINAPI hook_glViewport(int x, int y, int w, int h);
void marker_begin(void) __asm__("axis_marker_begin");
void marker_end(void) __asm__("axis_marker_end");
__attribute__((used)) void marker_begin(void) {
    int w = AXGL_W, h = AXGL_H;
    g_mw = g_mwsaved = w;
    if (w > 0 && h > 0 && w * 3 > h * 4) AXGL_W = (h * 4 + 1) / 3;
    g_mvpx = g_vpx; g_mvpw = g_vpw;
    if (real_glViewport && w > 0 && h > 0 && g_vpw < w) hook_glViewport(0, 0, w, h);
}
__attribute__((used)) void marker_end(void) {
    AXGL_W = g_mwsaved;
    if (real_glViewport && g_mwsaved > 0 && g_mvpw > 1 && g_mvpw < g_mwsaved) hook_glViewport(g_mvpx, 0, g_mvpw, AXGL_H);
}
/* The replay overlay can start while the viewport is still the 4:3 menu box (the 2D projection was already
   current, so 0x41ef90 doesn't switch again and the viewport hook can't correct it); left/right elements were
   then remapped outside that box and clipped. ov_begin gives it the HUD viewport (the centred 16:9 box, or the
   full screen when that is narrower), ov_end puts back exactly the viewport it found. */
static volatile int g_ovx, g_ovy, g_ovw, g_ovh, g_ovset;
void ov_begin(void) __asm__("axis_ov_begin");
void ov_end(void) __asm__("axis_ov_end");
__attribute__((used)) void ov_begin(void) {
    int W = g_vpx * 2 + g_vpw, h = g_vph, w16 = h * 16 / 9, x, w;
    g_ovset = 0;
    if (!real_glViewport || g_vpw <= 1 || h <= 0) return;
    if (w16 + 8 >= W) { x = 0; w = W; } else { x = (W - w16) / 2; w = w16; }
    if (x == g_vpx && w == g_vpw) return;
    g_ovx = g_vpx; g_ovy = g_vpy; g_ovw = g_vpw; g_ovh = g_vph; g_ovset = 1;
    hook_glViewport(x, g_vpy, w, h);
}
__attribute__((used)) void ov_end(void) {
    if (g_ovset) { g_ovset = 0; hook_glViewport(g_ovx, g_ovy, g_ovw, g_ovh); }
}
/* The HUD digit routine 0x46bdc0 gets one size factor (width/640 based) and uses it for the digit width
   (x28) and height (x26), so digits were too tall on anything wider than 4:3. Its "x26" now reads this
   value instead: 26 * (640*H) / (480*W), i.e. a height/480 based height. */
static volatile float g_digit_h = 26.0f;
static void update_digit_h(void) {
    int w = AXGL_W, h = AXGL_H;
    g_digit_h = (g_hud43 && w > 0 && h > 0 && w * 3 > h * 4) ? (float)(26.0 * 640.0 * h / (480.0 * w)) : 26.0f;
}
static int hud_anchor(DWORD ret, DWORD site) {
    if (site == 0x498659) {                       /* drawn directly by the main HUD routine 0x4926f0 */
        if (ret >= 0x492840 && ret < 0x4929d0) return A_NONE;    /* lock-on range circle: already H-based */
        if (ret >= 0x4935b8 && ret < 0x493980) return A_RIGHT;   /* power-up icons (right edge) */
        if (ret >= 0x492a00 && ret < 0x492c00) return A_LEFT;    /* armor/shield panel */
        if (ret >= 0x492f00 && ret < 0x493100) return A_RIGHT;   /* weapon / ammo panels */
        if (ret >= 0x493980 && ret < 0x493d96) return A_RIGHT;   /* weapon picture (V view), one quad */
        if (ret >= 0x493d00 && ret < 0x494440) return A_LEFT;    /* boost gauge */
        return A_CENTER;
    }
    if (site >= 0x492c00 && site < 0x492d00) return A_LEFT;      /* armor/shield digits */
    if (site >= 0x493200 && site < 0x493300) return A_RIGHT;     /* ammo digits */
    if (site == 0x494431) return A_LEFT;                          /* boost gauge outline */
    if (site == 0x493964) return A_RIGHT;                         /* power-up seconds (0x46bb00) */
    if (site >= 0x492780 && site < 0x4927e0) return A_NONE;      /* full-screen flashes */
    if (site >= 0x494900 && site < 0x494930) return A_RIGHT;     /* "1/4" */
    if (site >= 0x495500 && site < 0x4955a0) return A_RIGHT;     /* FPS */
    if (site >= 0x488000 && site < 0x49a000) return A_CENTER;    /* chat, menu, frag counter, messages */
    return A_NONE;
}
/* RECOMP TEST BUILD ONLY: the main HUD rebuilt in recomp.dll (src/hud/hud_main.c) can't be recognised by the return
   addresses above and below; it says which part it is drawing instead (g_hudpart, the values of src/wide.h HUD_*:
   0 not said, 1 left, 2 centre, 3 right, 4 as drawn, 5 screen pixels, 6 the top right corner marks) */
volatile int g_hudpart;
enum { HP_AUTO, HP_LEFT, HP_CENTRE, HP_RIGHT, HP_SCREEN, HP_PIXELS, HP_CORNER };
static int hud_part_is(int area, DWORD ret, DWORD lo, DWORD hi, int part) {
    return area == 2 && g_hudpart ? g_hudpart == part : ret >= lo && ret < hi;
}
static int hud_part_anchor(int area, DWORD ret, DWORD site) {
    if (area != 2 || !g_hudpart) return hud_anchor(ret, site);
    return g_hudpart == HP_LEFT ? A_LEFT : g_hudpart == HP_CENTRE ? A_CENTER : g_hudpart == HP_RIGHT ? A_RIGHT : A_NONE;
}
static void WINAPI hook_glViewport(int x, int y, int w, int h) {
    if (g_hudtrace) {    /* log each distinct viewport with its caller */
        static struct { int x, y, w, h; void *ret; } seen[64];
        void *ret = __builtin_return_address(0);
        int i;
        for (i = 0; i < 64 && seen[i].w && !(seen[i].x == x && seen[i].y == y && seen[i].w == w && seen[i].h == h && seen[i].ret == ret); i++) ;
        if (i < 64 && !seen[i].w) { seen[i].x = x; seen[i].y = y; seen[i].w = w; seen[i].h = h; seen[i].ret = ret;
                                    logf("viewport %d,%d %dx%d from %p (inhud %d)", x, y, w, h, ret, g_inhud); }
    }
    if (g_menu43 && g_inhud && __builtin_return_address(0) == (void *)0x4a8fdd && h > 0) {
        /* menu 2D switch (widefix cave) during the in-match HUD: back to its 16:9 box (see menu43 in DllMain) */
        int W = 2 * x + w, w16 = h * 16 / 9;
        if (w16 + 8 >= W || g_area == 1 || g_area == 5) { x = 0; w = W; }   /* markers: full screen (marker_begin) */
        else { x = (W - w16) / 2; w = w16; }
    }
    g_vpx = x; g_vpw = w > 0 ? w : 1; g_vpy = y; g_vph = h;
    update_digit_h();
    real_glViewport(x, y, w, h);
}
typedef struct { void *ret, *site; int x0, x1, y0, y1; unsigned n; } TraceE;
static TraceE g_tr[256];
static DWORD g_trdump;
static void trace_vertex(void *ret, void *site, int x, int y) {
    int i;
    for (i = 0; i < 256 && g_tr[i].ret && !(g_tr[i].ret == ret && g_tr[i].site == site); i++) ;
    if (i < 256) {
        TraceE *e = &g_tr[i];
        if (!e->ret) { e->ret = ret; e->site = site; e->x0 = e->x1 = x; e->y0 = e->y1 = y; }
        if (x < e->x0) e->x0 = x; if (x > e->x1) e->x1 = x; if (y < e->y0) e->y0 = y; if (y > e->y1) e->y1 = y;
        e->n++;
    }
    DWORD now = GetTickCount();
    if (now - g_trdump > 5000) {
        g_trdump = now;
        for (int j = 0; j < 256 && g_tr[j].ret; j++)
            logf("hudtrace %p site %p x %d..%d y %d..%d n %u", g_tr[j].ret, g_tr[j].site, g_tr[j].x0, g_tr[j].x1, g_tr[j].y0, g_tr[j].y1, g_tr[j].n);
        logf("hudtrace ----");
    }
}
/* The power-up countdown is drawn by 0x46bb00, a fixed-pixel font (14 px glyphs at any resolution, so
   tiny at 4K). Its call at 0x49395f goes through pu_text, which has the glyphs scaled about the text's
   top-left like the rest of the HUD (x by width/640, y by height/480); the remap above then makes them
   proportional. The game centres the text under its 32-unit icon by assuming it is 22 px wide (x = icon
   centre - 11), but the font is proportional (space and "1" 7 px, other digits 12 px) and the glyphs are
   scaled, so the seconds sat right of the icon; pu_text measures the text and centres it on the icon. */
static volatile int g_txt, g_txtx, g_txty;
/* player name labels over mechs (0x491c2d: 0x44ae10(x, y, x, name, 8), centred on x) */
static volatile int g_label, g_labelx;
static volatile double g_labelpx;
typedef void (__cdecl *HUDTEXT)(int, int, int, const char *, int);
static void __cdecl label_text(int x1, int y, int x2, const char *s, int size) {
    /* x came in as 640 units of the (4H/3) marker width: back to the player's screen pixel */
    g_labelx = (x1 + x2) / 2; g_labelpx = g_labelx * (double)AXGL_W / 640.0; g_label = g_hud43;
    int fw = AXGL_W;
    AXGL_W = g_mw;                    /* the text routine and the vertex hook see the real width */
    /* The text routines wrap to a new line once a character's x reaches [0x4ad490] (640) and stop at y
       [0x4ad494] (480). The label x is in units of the 4:3 marker width, so on wider screens a player near
       the right edge is past 640 and the name was drawn one letter per line (vertical). Labels never wrap. */
    int lim_x = *(int *)0x4ad490, lim_y = *(int *)0x4ad494;
    *(int *)0x4ad490 = 0x7fffffff; *(int *)0x4ad494 = 0x7fffffff;
    ((HUDTEXT)0x44ae10)(x1, y, x2, s, size);
    *(int *)0x4ad490 = lim_x; *(int *)0x4ad494 = lim_y;
    AXGL_W = fw;
    g_label = 0;
}
/* Menus in a 4:3 box ([hud] menu43, see DllMain): everything in the menus is drawn in 640x480 units through
   menu_vtx (= 0x41ef60, reimplemented so it can be redirected) inside a centred 4:3 viewport. Two kinds of
   drawing must not be clipped to that box, so they get the full-screen viewport while they draw:
   - 0x429170, the title emblem and the zooming transition between menus (quads that reach past the screen
     edges): stretched over the whole screen as originally (g_menumode 1). The game already corrects the
     emblem's x for the screen aspect itself, so mapping it proportionally (mode 2) made it too thin;
   - any rectangle (0x427970) that covers all of 640x480 - the white flash before loading, fades and dimming:
     stretched over the whole screen (g_menumode 1), as before. */
static volatile int g_menumode;
/* menu cursor (cursor_draw): drawn with the full viewport but placed exactly as in the viewport that was
   current (g_cur_vx/g_cur_vw), so it isn't cut off at the box edge. px = an x in that viewport's pixel
   space (x * [0x680bac], 0..W) -> screen pixels */
static int g_cur_on, g_cur_vx, g_cur_vw;
static int menu_boxx(float px) {
    float sx = *(float *)0x680bac;
    int W = (int)(640.0f * sx + 0.5f);
    return W > 0 ? g_cur_vx + (int)(px * g_cur_vw / W) : (int)px;
}
static void menu_box(int W, int H, int *vx, int *vw) {
    if (g_vpw > 1 && g_vpw <= W) { *vx = g_vpx; *vw = g_vpw; return; }   /* viewport hook (HUD hooks on) */
    *vw = g_menu43 ? (W * 3 > H * 4 ? H * 4 / 3 : W) : (W * 9 > H * 16 ? H * 16 / 9 : W);
    *vx = (W - *vw) / 2;
}
static void __cdecl menu_vtx(int x, int y) {
    float sx = *(float *)0x680bac, sy = *(float *)0x4df014;
    int H = *(int *)0x4e045c, X = (int)(x * sx);
    if (g_menumode == 2) X = (int)(320.0f * sx + (x - 320) * sy);
    if (g_cur_on) X = menu_boxx(x * sx);
    typedef void (WINAPI *V2I)(int, int);
    (*(V2I *)0x4a91f4)(X, H - (int)(y * sy));
}
/* enter/leave full-screen drawing: full viewport while it lasts, then the menu box again */
static int g_menu_vx, g_menu_vw, g_menu_depth;
typedef void (WINAPI *VIEWPORT)(int, int, int, int);
static void __cdecl menu_full(int mode) {
    float sx = *(float *)0x680bac;
    int H = *(int *)0x4e045c, W = (int)(640.0f * sx + 0.5f);
    if (mode) {
        if (g_menu_depth++ == 0) {
            menu_box(W, H, &g_menu_vx, &g_menu_vw);
            if (g_menu_vw < W) (*(VIEWPORT *)0x4a91d4)(0, 0, W, H);
            g_menumode = mode;
        }
    } else if (g_menu_depth > 0 && --g_menu_depth == 0) {
        g_menumode = 0;
        if (g_menu_vw < W) (*(VIEWPORT *)0x4a91d4)(g_menu_vx, 0, g_menu_vw, H);
    }
}
/* 0x429170 (emblem/transition): called from 0x41f903; wrapped. Not re-entrant (one caller). */
void *g_trans_ret __asm__("axis_trans_ret") __attribute__((used));
void *g_trans_fn __asm__("axis_trans_fn") = (void *)0x429170;
__attribute__((naked)) static void trans_wrap(void) {
    __asm__ volatile("popl axis_trans_ret\n\tpushl $1\n\tcall %P0\n\taddl $4, %%esp\n\tcall *axis_trans_fn\n\t"
                     "pushl %%eax\n\tpushl $0\n\tcall %P0\n\taddl $4, %%esp\n\tpopl %%eax\n\tpushl axis_trans_ret\n\tret" :: "i"(menu_full));
}
/* 0x427970(x0, y0, x1, y1, filled): rectangles; a full-screen one is drawn full screen. Its first
   instruction (mov eax,[0x9da48c], 5 bytes) is replayed by rect_tramp. */
void *g_rect_ret __asm__("axis_rect_ret") __attribute__((used));
__attribute__((naked)) static void rect_tramp(void) {
    __asm__ volatile("movl 0x9da48c, %eax\n\tpushl $0x427975\n\tret");
}
static int __cdecl rect_full(int x0, int y0, int x1, int y1) { return x0 <= 0 && y0 <= 0 && x1 >= 640 && y1 >= 480; }
__attribute__((naked)) static void rect_wrap(void) {
    __asm__ volatile("pushl 16(%%esp)\n\tpushl 16(%%esp)\n\tpushl 16(%%esp)\n\tpushl 16(%%esp)\n\tcall %P0\n\taddl $16, %%esp\n\t"
                     "testl %%eax, %%eax\n\tjz 1f\n\t"
                     "popl axis_rect_ret\n\tpushl $1\n\tcall %P2\n\taddl $4, %%esp\n\tcall %P1\n\t"
                     "pushl %%eax\n\tpushl $0\n\tcall %P2\n\taddl $4, %%esp\n\tpopl %%eax\n\tpushl axis_rect_ret\n\tret\n"
                     "1:\n\tjmp %P1" :: "i"(rect_full), "i"(rect_tramp), "i"(menu_full));
}
/* The menu cursor (0x429bc0) is a 47x47-unit sprite with its tip at the top-left corner, drawn through the
   menu vertex helper 0x41ef60(x, y) = glVertex2i(x * [0x680bac], H - y * [0x4df014]). Menus are laid out in
   640x480 units, so on a screen wider than 4:3 the x scale is larger than the y scale and the arrow came out
   stretched sideways (a third wider at 16:9 and on pillarboxed ultrawide). Its two right-hand corners
   (0x429cc3, 0x429cf0, called with x + 47) now go through cursor_vtx, which makes the width 47 units of the
   y scale in screen pixels (allowing for the viewport); at 4:3 the result is unchanged. The tip and click point stay where they were. */
static void __cdecl cursor_vtx(int x, int y) {
    float sx = *(float *)0x680bac, sy = *(float *)0x4df014;
    int H = *(int *)0x4e045c;
    typedef void (WINAPI *V2I)(int, int);
    /* on ultrawide the menus are drawn into a centred 16:9 viewport (widefix): convert the width to that box.
       The viewport hook tracks it; without the HUD hooks, menu_box uses the box rule. */
    int W = (int)(640.0f * sx + 0.5f), vx, vw;
    menu_box(W, H, &vx, &vw);
    float k = vw > 0 ? (float)W / vw : 1.0f;
    if (g_cur_on) (*(V2I *)0x4a91f4)(menu_boxx((x - 47) * sx) + (int)(47 * sy), H - (int)(y * sy));
    else (*(V2I *)0x4a91f4)((int)((x - 47) * sx + 47 * sy * k), H - (int)(y * sy));
}
/* The menu cursor was clipped by the 4:3 box: at the right limit (the original 630) most of the arrow
   vanished at the box edge in the middle of the screen. 0x41fc28 (its only call) -> cursor_draw: same
   position, size and limits, drawn with the full viewport. It is self-contained (not menu_full: the
   cursor can be drawn while a transition already has the full viewport) and puts back exactly the
   viewport it found, which the viewport hook tracks; the hook itself is bypassed so that stays valid.
   0x429bc0 starts with the 2D projection switch 0x41ef90(2), which (only when the mode changes, cached in
   [0x5ae9bc]) resets the viewport to the box - e.g. when the main menu's 3D background was drawn last. It is
   made here first, so the one inside is a no-op and can't clip the cursor again. */
/* The menu cursor was kept to x 0..630 (and y 0..474) of the 640x480 menu units by 0x445cd8, i.e. inside the
   centred 4:3 (or 16:9) menu box. It now reaches the whole screen: x from the screen's left edge to its right
   edge less the same 10 units, in the box's units (so the click point still lines up with the menus). y is
   unchanged; on a 4:3 screen the limits are the original ones. In a match ([0x76d3e8] == 0x270f) the game
   skips the clamp, as before. */
/* Text from the iftex\english8 / english16 fonts (menus, help, chat; sizes 5/8/16/32 via 0x44ad60) showed thin
   vertical lines at higher resolutions. Each character is a quad scaled from an 8x16 (16x16) cell, and its
   texture rectangle runs right up to the cell's unused column/row (english8: u = cell x+1..x+8, so the left edge
   touches the cell's column 0 and the right edge the next cell's column 0). With the textures' linear filtering
   those neighbouring texels were blended into the edges of every scaled-up character; a space (stored next to
   symbols) became a line. The ASCII passes (0x402010 / 0x402210 / 0x402420, and 0x403060 for size 5) now draw
   with nearest-texel sampling, which never leaves the character's own texels: the characters look exactly as at
   640x480, scaled up. The bound font texture's filters are put back afterwards (other code draws from it). */
typedef void (WINAPI *TEXPARAMI)(unsigned, unsigned, int);
typedef void (WINAPI *GETTEXPARAMIV)(unsigned, unsigned, int *);
static TEXPARAMI p_glTexParameteri;
static GETTEXPARAMIV p_glGetTexParameteriv;
static void text_pass(DWORD fn, int a, int b, int c) {
    int mag = 0, min = 0, on = g_sharptext && p_glTexParameteri && p_glGetTexParameteriv;
    if (on) {
        p_glGetTexParameteriv(0x0de1, 0x2800, &mag); p_glGetTexParameteriv(0x0de1, 0x2801, &min);   /* GL_TEXTURE_2D */
        p_glTexParameteri(0x0de1, 0x2800, 0x2600); p_glTexParameteri(0x0de1, 0x2801, 0x2600);       /* GL_NEAREST */
    }
    ((void (__cdecl *)(int, int, int))fn)(a, b, c);
    if (on) { p_glTexParameteri(0x0de1, 0x2800, mag); p_glTexParameteri(0x0de1, 0x2801, min); }
}
static void __cdecl text_e8(int a, int b, int c) { text_pass(0x402010, a, b, c); }
static void __cdecl text_e16(int a, int b, int c) { text_pass(0x402210, a, b, c); }
static void __cdecl text_e32(int a, int b, int c) { text_pass(0x402420, a, b, c); }
static void __cdecl text_e5(int a, int b, int c) { text_pass(0x403060, a, b, c); }
static void hook_sharptext(void) {
    static const struct { DWORD at, from; void *to; } calls[] = {
        {0x402720, 0x402010, text_e8}, {0x40288c, 0x402010, text_e8}, {0x4029b0, 0x402210, text_e16},
        {0x402be8, 0x402210, text_e16}, {0x402d90, 0x402420, text_e32}, {0x402fbd, 0x402420, text_e32},
        {0x4031f1, 0x403060, text_e5}, {0x4032e6, 0x403060, text_e5},
    };
    HMODULE gl = GetModuleHandleA("opengl32.dll");
    p_glTexParameteri = gl ? (TEXPARAMI)GetProcAddress(gl, "glTexParameteri") : NULL;
    p_glGetTexParameteriv = gl ? (GETTEXPARAMIV)GetProcAddress(gl, "glGetTexParameteriv") : NULL;
    int n = sizeof calls / sizeof calls[0];
    for (int i = 0; i < n; i++) {   /* all or nothing */
        BYTE *p = (BYTE *)calls[i].at;
        if (p[0] != 0xe8 || *(INT32 *)(p + 1) != (INT32)(calls[i].from - (calls[i].at + 5)) || !p_glTexParameteri) {
            logf("text: sharp font sampling NOT INSTALLED (unexpected code at %#lx)", calls[i].at);
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        BYTE *p = (BYTE *)calls[i].at;
        DWORD old;
        VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
        *(INT32 *)(p + 1) = (INT32)((BYTE *)calls[i].to - (p + 5));
        VirtualProtect(p, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), p, 5);
    }
    logf("text: menu/chat fonts drawn with nearest-texel sampling (no lines at high resolutions)");
}
/* HUD numbers (0x46bdc0: armor, shield, ammo) are 35x27-texel cells of the HUD texture ([0xa106ac], 256x256;
   digit d at column d%5, row d/5 from y 112, minus sign at 175,112) and their texture rectangles run exactly to
   the cell borders, so when scaled up the linear filter blended in the texels around them - a thin green dash
   along the top of the shield digits (the row above the digits). The routine sets each quad's corners in the
   order top-left, top-right, bottom-right, bottom-left through glTexCoord2f, loaded once into a register
   (0x46be96); it now loads digit_texcoord, which moves each corner half a texel into the cell. */
static unsigned g_dtc;
static void WINAPI digit_texcoord(float s, float t) {
    const float e = 0.5f / 256;
    unsigned k = g_dtc++ & 3;
    s += (k == 0 || k == 3) ? e : -e;
    t += k < 2 ? e : -e;
    (*(void (WINAPI **)(float, float))0x4a920c)(s, t);
}
static void *g_digit_tc = (void *)digit_texcoord;
static void hook_digits(void) {
    static const BYTE sig[] = {0x8b, 0x1d, 0x0c, 0x92, 0x4a, 0x00};   /* 0x46be96: mov ebx, [glTexCoord2f] */
    BYTE *p = (BYTE *)0x46be96;
    if (memcmp(p, sig, sizeof sig)) { logf("HUD digits: edge fix NOT INSTALLED (unexpected code)"); return; }
    DWORD old;
    VirtualProtect(p, 6, PAGE_EXECUTE_READWRITE, &old);
    *(void ***)(p + 2) = &g_digit_tc;
    VirtualProtect(p, 6, old, &old);
    FlushInstructionCache(GetCurrentProcess(), p, 6);
    logf("HUD digits: texture edges kept inside each digit");
}
static void __cdecl cursor_clamp(void) {
    int *cx = (int *)0x4ded68, *cy = (int *)0x4ded6c, lo = 0, hi = 630;
    int W = *(int *)0x5b1998, H = *(int *)0x4e045c;
    if (W > 0 && H > 0) {
        int vw = g_menu43 ? (W * 3 > H * 4 ? H * 4 / 3 : W) : (W * 9 > H * 16 ? H * 16 / 9 : W);
        if (vw > 0 && vw < W) {
            int vx = (W - vw) / 2;
            lo = -(vx * 640 / vw);
            hi = (W - vx) * 640 / vw - 10;
        }
    }
    if (*cx > hi) *cx = hi;
    if (*cy > 474) *cy = 474;
    if (*cx < lo) *cx = lo;
    if (*cy < 0) *cy = 0;
}
__attribute__((naked)) static void cursor_clamp_wrap(void) {   /* replaces 0x445cd8..0x445d12 */
    __asm__ volatile("pushal\n\tcall %P0\n\tpopal\n\tpushl $0x445d12\n\tret" :: "i"(cursor_clamp));
}
static void __cdecl cursor_draw(void) {
    ((void (__cdecl *)(int))0x41ef90)(2);
    float sx = *(float *)0x680bac;
    int W = (int)(640.0f * sx + 0.5f), vx = g_vpx, vw = g_vpw, vy = g_vpy, vh = g_vph;
    if (!real_glViewport || vw <= 1 || vh <= 0 || vw >= W) { ((void (__cdecl *)(void))0x429bc0)(); return; }
    g_cur_vx = vx; g_cur_vw = vw; g_cur_on = 1;
    real_glViewport(0, vy, W, vh);
    ((void (__cdecl *)(void))0x429bc0)();
    real_glViewport(vx, vy, vw, vh);
    g_cur_on = 0;
}
/* Per-frame input read (0x445c60 calls 0x401730, the DInput mouse read that mousefix.py replaced).
   Mouse: since the window stays visible after alt-tab, a click on it brings the game back, and the
   exclusive DInput mouse is acquired while that button is down; its release could be missed and the
   button (fire / mouse 2) stayed held. After the game is back in the foreground each button now counts
   only once it has been seen released.
   Chat: the chat line is an EDIT child of the game window (0x43f460, handle [0x9dd888], destroyed when
   the line is sent/closed). Reactivating the window gave the focus to the window itself, so typing went
   nowhere; the game window is subclassed (from here, on whichever thread runs the loop) and hands the focus
   back to the chat line when it gets activated / focused while the line exists. */
static BYTE g_btnmask;
static HWND g_subwnd;
static WNDPROC g_mainproc;
/* Menu cursor speed: 0x445c60 adds the raw DInput counts to the cursor in 640x480 units, so one count
   was one pixel at 640x480 but box/640 pixels now (4.5 at 4K) - far faster than the Windows pointer.
   In menus ([0x76d3e8] != 0x270f, see the main loop 0x420280) the counts are scaled so one count moves
   about one screen pixel (per axis) times the Windows pointer speed; the fraction is carried to the next frame.
   In a match the cursor is re-centred every frame and its offset is the turn rate, so aim is untouched. */
static float g_mfx, g_mfy;
static float menu_speed(void) {   /* Windows pointer speed (Control Panel slider) * [input] menusens */
    static const float spd[21] = {0, 1/32.f, 1/16.f, 1/8.f, 2/8.f, 3/8.f, 4/8.f, 5/8.f, 6/8.f, 7/8.f, 1,
                                  1.25f, 1.5f, 1.75f, 2, 2.25f, 2.5f, 2.75f, 3, 3.25f, 3.5f};
    int ws = 10; SystemParametersInfoA(SPI_GETMOUSESPEED, 0, &ws, 0);
    return spd[ws >= 1 && ws <= 20 ? ws : 10] * (float)g_menusens;
}
static void menu_mouse(LONG *d) {
    if (g_menusens <= 0 || *(int *)0x76d3e8 == 0x270f) { g_mfx = g_mfy = 0; return; }
    int W = *(int *)0x5b1998, H = *(int *)0x4e045c;   /* screen pixels; menus span the 4:3 (or 16:9) box */
    if (W <= 0 || H <= 0) return;
    int vw = g_menu43 ? (W * 3 > H * 4 ? H * 4 / 3 : W) : (W * 9 > H * 16 ? H * 16 / 9 : W);
    float k = menu_speed();
    /* per axis: the box is vw x H pixels for 640 x 480 units (uneven when menu43=0 stretches menus to 16:9) */
    float fx = d[0] * k * 640.0f / vw + g_mfx, fy = d[1] * k * 480.0f / H + g_mfy;
    d[0] = (LONG)fx; d[1] = (LONG)fy;   /* truncate toward 0, keep the rest */
    g_mfx = fx - d[0]; g_mfy = fy - d[1];
}
/* In-match menu (Esc / the START menu when a match begins, open while scene+0x2340cf4 == 1): it has no
   cursor. 0x49dd11 turns this frame's mouse offset into scene+0x2343293 (y) / +0x2343297 (-x), times the
   aim sensitivity ((s*0.02)^2+1)*0.5, s = [0x4df008]; then any frame over -50/+50 on either axis set
   "up" (+0x234330b) / "down" (+0x234330f). Built for ~30 fps and 400 dpi mice: at 120 fps with a modern
   mouse a gentle slide passes it frame after frame and races through the items, sideways too.
   0x49ddcb now calls this instead: vertical travel is added up and each item takes about one item
   spacing (H/12 pixels) of movement at desktop pointer speed. Aiming uses other paths (0x49d9ec, 0x4885f0). */
static float g_navacc;
static DWORD g_navtick;
static void __cdecl menu_nav(BYTE *scene) {
    DWORD now = GetTickCount();
    if (now - g_navtick > 250) g_navacc = 0;   /* menu just (re)opened */
    g_navtick = now;
    int s = *(int *)0x4df008, H = *(int *)0x4e045c;
    float f = ((s * 0.02f) * (s * 0.02f) + 1) * 0.5f, y = *(float *)(scene + 0x2343293) / f;   /* raw counts */
    if (*(int *)0x4df000) y = -y;   /* undo "invert mouse": the menu follows the hand */
    if (y * g_navacc < 0) g_navacc = 0;   /* changed direction */
    g_navacc += y;
    float step = (H > 0 ? H : 480) / 12.0f / menu_speed();
    if (g_navacc <= -step) { *(int *)(scene + 0x234330b) = 1; g_navacc += step; }
    else if (g_navacc >= step) { *(int *)(scene + 0x234330f) = 1; g_navacc -= step; }}
/* Windows-side mouse buttons after alt-tab. The DInput mouse is exclusive (it hides the buttons from
   Windows) and the game re-Acquires it every frame (0x4012e0), so a button held while switching away
   could be left "down" for the rest of Windows. On deactivation the mouse is unacquired at once and a
   low-level hook (installed then, so it runs before DInput's) tracks the real buttons while the game is
   in the background; a button Windows still reports down after it was really released gets an up. */
static BYTE g_dibtn;                 /* buttons in the last foreground DInput read (bit 0 L, 1 R, 2 M) */
static volatile BYTE g_physbtn;      /* real buttons while inactive */
static volatile LONG g_inactive;
static DWORD g_bgthr;
static LRESULT CALLBACK bg_mouse_ll(int n, WPARAM wp, LPARAM lp) {
    if (n == HC_ACTION)
        switch (wp) {
        case WM_LBUTTONDOWN: g_physbtn |= 1; break;   case WM_LBUTTONUP: g_physbtn &= ~1; break;
        case WM_RBUTTONDOWN: g_physbtn |= 2; break;   case WM_RBUTTONUP: g_physbtn &= ~2; break;
        case WM_MBUTTONDOWN: g_physbtn |= 4; break;   case WM_MBUTTONUP: g_physbtn &= ~4; break;
        }
    return CallNextHookEx(NULL, n, wp, lp);
}
static DWORD WINAPI bg_thread(void *arg) {
    static const int vk[3] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON };
    static const DWORD up[3] = { MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP };
    HHOOK hk = NULL; UINT_PTR tm = 0; int stale[3] = { 0 };
    MSG msg;
    PeekMessageA(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);   /* create the queue */
    SetEvent((HANDLE)arg);
    while (GetMessageA(&msg, NULL, 0, 0) > 0) {
        if (msg.message == WM_APP) {          /* deactivated: (re)hook so this hook is called first */
            if (hk) UnhookWindowsHookEx(hk);
            hk = SetWindowsHookExA(WH_MOUSE_LL, bg_mouse_ll, GetModuleHandleA(NULL), 0);
            if (!tm) tm = SetTimer(NULL, 0, 50, NULL);
            stale[0] = stale[1] = stale[2] = 0;
        } else if (msg.message == WM_APP + 1) {   /* activated: no hook while playing */
            if (hk) UnhookWindowsHookEx(hk);
            if (tm) KillTimer(NULL, tm);
            hk = NULL; tm = 0;
        } else if (msg.message == WM_TIMER && g_inactive) {
            for (int i = 0; i < 3; i++) {
                if ((GetAsyncKeyState(vk[i]) & 0x8000) && !(g_physbtn & (1 << i))) {
                    if (++stale[i] == 2) {    /* still down 50 ms after the real release */
                        INPUT in = { 0 };
                        in.type = INPUT_MOUSE; in.mi.dwFlags = up[i];
                        SendInput(1, &in, sizeof in);
                        logf("input: released stuck mouse button %d in Windows", i + 1);
                    }
                } else stale[i] = 0;
            }
        }
        DispatchMessageA(&msg);
    }
    return 0;
}
static void bg_activate(int active) {
    if (!active) {
        IUnknown *dev = *(IUnknown **)0x4d1fa4;     /* IDirectInputDevice (mouse) */
        if (dev) ((HRESULT (__stdcall *)(void *))(*(void ***)dev)[8])(dev);   /* Unacquire */
        g_physbtn = g_dibtn;
        g_inactive = 1;
        if (!g_bgthr) {
            HANDLE ev = CreateEventA(NULL, FALSE, FALSE, NULL);
            CloseHandle(CreateThread(NULL, 0, bg_thread, ev, 0, &g_bgthr));
            WaitForSingleObject(ev, 2000); CloseHandle(ev);
        }
        PostThreadMessageA(g_bgthr, WM_APP, 0, 0);
    } else {
        g_inactive = 0;
        if (g_bgthr) PostThreadMessageA(g_bgthr, WM_APP + 1, 0, 0);
    }
}
static LRESULT CALLBACK main_subproc(HWND w, UINT m, WPARAM wp, LPARAM lp) {
    if (m == WM_ACTIVATEAPP) bg_activate(wp != 0);
    LRESULT r = CallWindowProcA(g_mainproc, w, m, wp, lp);
    if ((m == WM_ACTIVATE && LOWORD(wp) != WA_INACTIVE) || m == WM_SETFOCUS) {
        HWND chat = *(HWND *)0x9dd888;
        if (chat && IsWindow(chat) && GetParent(chat) == w && GetFocus() != chat) SetFocus(chat);
    }
    return r;
}
/* 0x401600(code) is the game's "just pressed" test for a key binding (303 callers: in-match menu, chat,
   actions). Keys latch: true once per press, to the first caller. Mouse buttons (0xfa-0xfc) instead used a
   flag that flips on EVERY call and returned the one-frame click pulse ([0x4ded88+4i], set by the mouse
   read 0x445c60) only when the flag was 0, so with one test per frame (the in-match menu's select) a click
   counted only if it landed on an even frame: about every other click was lost. They now latch like keys. */
static int g_mlatch[3];
static int __cdecl mouse_pressed(int code) {
    int i = code - 0xfa;
    if (!*(int *)(0x4ded88 + i * 4)) { g_mlatch[i] = 0; return 0; }
    if (g_mlatch[i]) return 0;
    g_mlatch[i] = 1;
    return 1;
}
void *g_pressed_cont __asm__("axis_pressed_cont") = (void *)0x401605;
__attribute__((naked)) static void pressed_wrap(void) {   /* 0x401600 entry: "push esi; mov esi,[esp+8]" */
    __asm__ volatile("movl 4(%%esp), %%eax\n\tcmpl $0xfa, %%eax\n\tjb 1f\n\tcmpl $0xfc, %%eax\n\tja 1f\n\t"
                     "pushl %%eax\n\tcall %P0\n\taddl $4, %%esp\n\tret\n"
                     "1:\n\tpushl %%esi\n\tmovl 8(%%esp), %%esi\n\tjmp *axis_pressed_cont" :: "i"(mouse_pressed));
}
static int __cdecl input_read(void) {
    int r = ((int (__cdecl *)(void))0x401730)();
    HWND w = *(HWND *)0x4ded18;
    BYTE *btn = (BYTE *)0x4d1a94;    /* DIMOUSESTATE.rgbButtons */
    if (w && GetForegroundWindow() != w) g_btnmask = 0x0f;
    else {
        g_dibtn = (btn[0] >> 7) | (btn[1] >> 7 << 1) | (btn[2] >> 7 << 2);
        for (int i = 0; i < 4; i++) {
            if (!(btn[i] & 0x80)) g_btnmask &= ~(1 << i);
            else if (g_btnmask & (1 << i)) btn[i] = 0;
        }
    }
    menu_mouse((LONG *)0x4d1a88);   /* DIMOUSESTATE.lX/lY */
    if (w && w != g_subwnd && IsWindow(w)) {
        WNDPROC p = (WNDPROC)GetWindowLongA(w, GWL_WNDPROC);
        if (p != main_subproc) { g_mainproc = p; SetWindowLongA(w, GWL_WNDPROC, (LONG)main_subproc); }
        g_subwnd = w;
    }
    return r;
}
/* The icon left of a name label (0x4922c0, 24 units wide) ends at x - (len/2)*8, but the label text
   (0x402740) starts at x - 4*(len - 5*colour codes): for odd-length names (SIREN) the icon covered half
   the first letter, at any resolution. 0x491c52 now calls this for the text's own half width. */
static int __cdecl label_halfw(const char *s) {
    int len = lstrlenA(s), codes = 0;
    for (int i = 0; i < len; i++)
        if (s[i] == '$' && s[i + 1] == '[' && s[i + 3] == ']' && s[i + 5]) codes++;
    return 4 * (len - 5 * codes);
}
typedef void (__cdecl *SMALLTEXT)(int, int, int, const char *, int);
static void __cdecl pu_text(int x, int y, int font, const char *fmt, int v) {
    if (font == 1) {   /* font 1: glyph widths at 0x4c5558, from ' ' */
        char s[32];
        int lead = 0, vis = 0, sp = 0, w = AXGL_W, h = AXGL_H;   /* "%2d" pads with a space: centre the digits */
        snprintf(s, sizeof s, fmt, v);
        for (const char *c = s; *c; c++) {
            if (*c < 0x20 || *c > 0x7e) continue;
            int cw = ((int *)0x4c5558)[*c - 0x20];
            if (*c == ' ') { if (vis) sp += cw; else lead += cw; }
            else { vis += sp + cw; sp = 0; }
        }
        double sc = g_hud43 && w > 0 && h > 480 ? w / 640.0 : 1.0;   /* the glyph scale in hook_glVertex2i */
        if (vis) x += 11 - (int)((lead + vis / 2.0) * sc + 0.5);
    }
    g_txtx = x; g_txty = y; g_txt = g_hud43;
    ((SMALLTEXT)0x46bb00)(x, y, font, fmt, v);
    g_txt = 0;
}
/* How far the HUD call-site scans below look: up to the top of this thread's stack (the HUD routine's frame is
   always above the hook), at most 64 KB. It used to be a fixed 200 dwords, so any extra frames between the HUD
   code and glVertex2i (e.g. rebuilt game functions that keep their own state on the stack) pushed the call site
   out of reach and the element got the fallback anchor (the "1/8" counter was drawn over the FPS counter). */
static int stack_scan_words(const DWORD *sp) {
    DWORD top = (DWORD)((NT_TIB *)NtCurrentTeb())->StackBase;
    DWORD n = top > (DWORD)sp ? (top - (DWORD)sp) / 4 : 0;
    return n > 16384 ? 16384 : (int)n;
}
__attribute__((noinline)) static void WINAPI hook_glVertex2i(int x, int y) {
    void *ret = __builtin_return_address(0), *site = NULL;
    if (g_txt && (DWORD)ret >= 0x46bb00 && (DWORD)ret < 0x46bcf2) {
        int w = AXGL_W, h = AXGL_H, ay = h - g_txty;
        if (w > 0 && h > 480) {
            x = g_txtx + (int)((x - g_txtx) * (w / 640.0) + 0.5);
            y = ay + (int)((y - ay) * (h / 480.0) + (y >= ay ? 0.5 : -0.5));
        }
        site = (void *)0x493964;    /* the stack scan is unreliable through pu_text: it is the power-up text */
    }
    DWORD *sp = (DWORD *)__builtin_frame_address(0);
    int nscan = stack_scan_words(sp);
    int area = g_area;
    if (site) ;
    else if (area == 1) site = (void *)0x498585;                               /* player markers */
    else if (area == 5) site = (void *)0x4985c9;                               /* lock-on square */
    else if (area == 2 && g_hudpart) site = (void *)0x498659;                  /* rebuilt main HUD: g_hudpart */
    else if (area == 2) {
        /* main HUD: its own vertices by address; for helpers, accept only a return address whose call
           instruction really calls that helper (the routine's uninitialised locals can hold leftovers) */
        static const DWORD helpers[][2] = {{0x46bdc0, 0x46c060}, {0x4922c0, 0x4924cd}, {0x4924d0, 0x4926ed},
                                           {0x46bd60, 0x46bdbd}, {0x46bd00, 0x46bd5d}, {0x46bb00, 0x46bcf2}};
        DWORD r = (DWORD)ret, start = 0;
        if (r >= 0x4926f0 && r < 0x494930) site = (void *)0x498659;
        else {
            for (int i = 0; i < 6; i++) if (r >= helpers[i][0] && r < helpers[i][1]) start = helpers[i][0];
            for (int k = 2; k < nscan && !site; k++) {
                DWORD v = sp[k];
                if (v < 0x4926f5 || v >= 0x494930 || ((BYTE *)v)[-5] != 0xe8) continue;
                if (start && v + *(INT32 *)(v - 4) != start) continue;
                site = (void *)v;
            }
            if (!site) site = (void *)0x498659;
        }
    }
    else if (area >= 6 && area <= 8) site = (void *)0x48a1fc;                  /* auto play overlay (ov_wrap) */
    else if (area == 3) site = (void *)0x495543;                               /* FPS: right */
    else if (area == 4) {                                                      /* "1/4" right, ranking centre */
        DWORD r = (DWORD)ret;
        if (r >= 0x494930 && r < 0x4950a0) site = (void *)r;
        else for (int k = 2; k < nscan && !site; k++) {
            DWORD v = sp[k];
            if (v >= 0x494935 && v < 0x4950a0 && ((BYTE *)v)[-5] == 0xe8) site = (void *)v;
        }
        if (!site) site = (void *)0x494d99;
    }
    else if (g_inhud) site = (void *)0x496281;          /* rest of the 2D pass (chat, menu, frags, messages): centre */
    else for (int k = 2; k < 200; k++) if (sp[k] >= 0x488000 && sp[k] < 0x49a000 && sp[k] != (DWORD)ret) { site = (void *)sp[k]; break; }
    if (g_hudtrace) trace_vertex(ret, site, x, y);
    int w = AXGL_W, h = AXGL_H, a;
    /* markers that follow players (area 1 / 5, sized for 4:3 by marker_begin): their x is the player's
       projected screen pixel, so map it 1:1 to the screen - the HUD ortho (0..w) is stretched over a
       centred 16:9 viewport on wider screens, which pulled markers towards the centre */
    if (g_hud43 && h > 0 && g_mw > 0 && (area == 1 || area == 5)) {
        double X;
        if (g_label) {
            /* name label glyphs (own 640-unit text mode, real width restored by label_text): centre them on
               the player and give them 4:3 proportions (glyphs map ortho 0..w over the viewport) */
            double c = g_vpx + (double)g_labelx * g_vpw / 640.0, s = 640.0 * h / 480.0 / g_vpw;
            X = g_labelpx + (g_vpx + (double)x * g_vpw / w - c) * (s < 1 ? s : 1);
        } else X = x;
        x = (int)((X - g_vpx) * g_mw / g_vpw + (X >= g_vpx ? 0.5 : -0.5));
        real_glVertex2i(x, y);
        return;
    }
    /* top-right corner icons drawn by the main HUD itself (0x494600-0x4948b3: rank-1 star, CTF flags) are
       64x64 fixed pixels at (W-64, top), so they were tiny at high resolutions (and squashed by the centre
       remap below). Size them in 640x480 units like the rest of the HUD (x height/480), anchored to the
       top-right corner of the HUD area, next to the "1/8" rank counter. */
    /* lock-on range circle (homing weapons, 0x492840-0x4929d0): drawn in screen pixels with an H-based radius,
       so it is round as the game draws it - but the HUD ortho (0..w) is stretched over the centred 16:9
       viewport on wider screens, which squeezed it into an oval. Map its x 1:1 to screen pixels. */
    if (g_hud43 && g_inhud && area == 2 && w > 0 && g_vpw > 0 && hud_part_is(area, (DWORD)ret, 0x492840, 0x4929d0, HP_PIXELS)) {
        x = (int)((double)(x - g_vpx) * w / g_vpw + (x >= g_vpx ? 0.5 : -0.5));
        real_glVertex2i(x, y);
        return;
    }
    if (g_hud43 && g_inhud && area == 2 && w > 0 && h > 0 && hud_part_is(area, (DWORD)ret, 0x494600, 0x4948b3, HP_CORNER)) {
        double sw = g_vpx * 2 + g_vpw, bw = sw, k = h / 480.0;
        if (g_hudaspect > 0 && bw > h * g_hudaspect) bw = h * g_hudaspect;
        double X = (sw + bw) / 2 - (w - x) * k;       /* w - x: pixels from the right edge, as the game drew it */
        x = (int)((X - g_vpx) * w / g_vpw + 0.5);
        y = h - (int)((h - y) * k + 0.5);
        real_glVertex2i(x, y);
        return;
    }
    if (g_hud43 && g_inhud && w > 0 && h > 0 &&
        (a = area == 6 ? A_LEFT : area == 7 ? A_RIGHT : area == 8 ? A_CENTER : hud_part_anchor(area, (DWORD)ret, (DWORD)site)) != A_NONE) {
        /* to screen pixels (ortho 0..w over the current viewport), remap, and back */
        double X = g_vpx + (double)x * g_vpw / w;
        int sw = g_vpx * 2 + g_vpw;                   /* the viewport is centred (or full) */
        double bw = sw, k = h / 480.0;                /* HUD area width, pixels per unit */
        if (g_hudaspect > 0 && bw > h * g_hudaspect) bw = h * g_hudaspect;
        if (bw > 640 * k) {                           /* only when the HUD area is wider than 4:3 */
            double bx = (sw - bw) / 2, u = (X - g_vpx) * 640.0 / g_vpw;
            if (a == A_LEFT) X = bx + u * k;
            else if (a == A_RIGHT) X = bx + bw - (640.0 - u) * k;
            else X = sw / 2.0 + (u - 320.0) * k;
            x = (int)((X - g_vpx) * w / g_vpw + (X >= g_vpx ? 0.5 : -0.5));
        }
    }
    real_glVertex2i(x, y);
}

/* ------------------------------------------------------------------ KYRIE parts (AxisGL)
 * A second SERAPHIM set in ARM CENTER with the unused marked textures (SHAPE\GEOLITE\MARK\KYRIE-*, gold
 * markings), unlocked with the original after the last mission. Same stats: each part is a copy of the
 * SERAPHIM record, appended to the catalogue after it is loaded (0x473780: per slot a count and an array of
 * 50 records), with the name "KYRIE\<slot>" (the textures' name; ARM CENTER shows "KYRIE-HEAD" etc.) and its model names prefixed "MARKED\".
 * Models: the Shape.dat lookup (0x466d60) drops the prefix, so the same model is loaded under its own cache
 * name, and right after it is read (0x466120) its sub-mesh textures "Shape\Geolite\..." become
 * "Shape\Geolite\MARK\...". The marked textures have no _COLOR mask, and a missing mask is filled solid red
 * (= all primary colour), so the mask lookup (call at 0x45636e) falls back to the original's mask, which is
 * blank (keeps every pixel) and the same size: the marked parts don't take part colours, like SERAPHIM. */
#define MK_PREFIX "MARKED\\"
static const struct { const char *slot; DWORD cnt, arr, size, models, cap, table, seraph; } mk_slots[] = {
    {"HEAD",    0x13eb000, 0x13c9b30, 0xaa8,  0x448, 8,  0x4ad5f0, 19},
    {"CHEST",   0x140c8bc, 0x13eb004, 0xabc,  0x448, 8,  0x4ad910, 13},
    {"ARM",     0x1447ec0, 0x140c8c0, 0x1300, 0x848, 16, 0x4adc30, 17},
    {"LEG",     0x148646c, 0x1447ec4, 0x13f4, 0x848, 16, 0x4adf50, 19},
    {"BOOSTER", 0x14d1ab0, 0x1486470, 0x1820, 0xa48, 20, 0x4ae270, 15},
};
static void __cdecl mk_catalog(BYTE *self) {
    for (int s = 0; s < 5; s++) {
        int *cnt = (int *)(self + mk_slots[s].cnt), n = *cnt;
        DWORD size = mk_slots[s].size;
        BYTE *src = self + mk_slots[s].arr + mk_slots[s].seraph * size, *dst = self + mk_slots[s].arr + n * size;
        char want[64];
        snprintf(want, sizeof want, "SERAPHIM\\%s", mk_slots[s].slot);
        if (n != (int)mk_slots[s].seraph + 1 || strcmp((char *)src, want)) {   /* not the stock catalogue */
            logf("KYRIE parts: %s not added (count %d, part %u is \"%.40s\")", mk_slots[s].slot, n,
                 mk_slots[s].seraph, (char *)src);
            continue;
        }
        memcpy(dst, src, size);
        memset(dst, 0, 0x40);
        snprintf((char *)dst, 0x40, "KYRIE\\%s", mk_slots[s].slot);
        for (DWORD i = 0; i < mk_slots[s].cap * 2; i++) {   /* models, then the low-detail models */
            char *m = (char *)dst + mk_slots[s].models + i * 0x44;
            size_t len = strnlen(m, 0x40);
            if (!len || !strcmp(m, ".") || len + 7 >= 0x40) continue;
            memmove(m + 7, m, len + 1);
            memcpy(m, MK_PREFIX, 7);
        }
        *cnt = n + 1;
        int *lvl = (int *)(mk_slots[s].table + 15 * 0x28);   /* level 15 (after the last mission): count + 9 */
        if (lvl[0] == 1 && lvl[1] == (int)mk_slots[s].seraph) { lvl[2] = n; lvl[0] = 2; }
        else if (!(lvl[0] == 2 && lvl[2] == n)) logf("KYRIE parts: %s unlock table not as expected", mk_slots[s].slot);
        logf("KYRIE parts: %s added as part %d", mk_slots[s].slot, n);
    }
}
void *g_cat_fn __asm__("axis_cat_fn") = (void *)0x473780;
__attribute__((naked)) static void cat_wrap(void) {   /* replaces "call 0x473780" (thiscall, 1 arg) */
    __asm__ volatile("pushl %%ecx\n\tpushl 8(%%esp)\n\tcall *axis_cat_fn\n\tpopl %%ecx\n\tpushl %%eax\n\tpushl %%ecx\n\t"
                     "call %P0\n\taddl $4, %%esp\n\tpopl %%eax\n\tret $4" :: "i"(mk_catalog));
}

static int g_mk_pending;   /* the model being read was asked for with the MARKED\ prefix */
static void *__cdecl mk_find(const char *name) {   /* replaces "call 0x466d60" (cdecl: Shape.dat entry by name) */
    g_mk_pending = !_strnicmp(name, MK_PREFIX, 7);
    return ((void *(__cdecl *)(const char *))0x466d60)(g_mk_pending ? name + 7 : name);
}
static void __cdecl mk_retex(BYTE *shp) {
    if (!g_mk_pending) return;
    g_mk_pending = 0;
    int n = *(int *)(shp + 0x10);
    BYTE *sub = *(BYTE **)(shp + 0x14);
    for (int i = 0; i < n && sub; i++) {
        char *t = (char *)sub + i * 0x80 + 4;
        size_t len = strnlen(t, 0x40);
        if (_strnicmp(t, "SHAPE\\GEOLITE\\", 14) || !_strnicmp(t + 14, "MARK", 4) || len + 5 >= 0x40) continue;
        memmove(t + 19, t + 14, len - 14 + 1);
        memcpy(t + 14, "MARK\\", 5);
    }
}
void *g_shpread_fn __asm__("axis_shpread_fn") = (void *)0x466120;
__attribute__((naked)) static void shpread_wrap(void) {   /* replaces "call 0x466120" (thiscall, 3 args) */
    __asm__ volatile("pushl %%ecx\n\tpushl 16(%%esp)\n\tpushl 16(%%esp)\n\tpushl 16(%%esp)\n\tcall *axis_shpread_fn\n\t"
                     "popl %%ecx\n\tpushl %%eax\n\tpushl %%ecx\n\tcall %P0\n\taddl $4, %%esp\n\tpopl %%eax\n\tret $12"
                     :: "i"(mk_retex));
}

/* MARK\KYRIE-x_COLOR -> KYRIE-x_COLOR, in the caller's buffer: the mask reader 0x455550 looks the name up again */
static char *__cdecl mk_altmask(char *name) {
    size_t len = strlen(name);
    if (_strnicmp(name, "SHAPE\\GEOLITE\\MARK\\", 19) || len < 6 || _stricmp(name + len - 6, "_COLOR")) return NULL;
    memmove(name + 14, name + 19, len - 19 + 1);
    return name;
}
void *g_texfind_fn __asm__("axis_texfind_fn") = (void *)0x4554c0;
__attribute__((naked)) static void maskfind_wrap(void) {   /* replaces "call 0x4554c0" (thiscall, 1 arg) at 0x45636e */
    __asm__ volatile("pushl %%ecx\n\tpushl 8(%%esp)\n\tcall *axis_texfind_fn\n\tpopl %%ecx\n\ttestl %%eax, %%eax\n\tjns 1f\n\t"
                     "pushl %%ecx\n\tpushl 8(%%esp)\n\tcall %P0\n\taddl $4, %%esp\n\tpopl %%ecx\n\ttestl %%eax, %%eax\n\tjz 2f\n\t"
                     "pushl %%eax\n\tcall *axis_texfind_fn\n\tret $4\n"
                     "2:\n\torl $-1, %%eax\n"
                     "1:\n\tret $4" :: "i"(mk_altmask));
}

static void hook_marked(void) {
    static const struct { DWORD at, from; void *to; } calls[] = {
        {0x45c638, 0x473780, cat_wrap}, {0x460920, 0x473780, cat_wrap}, {0x498dd8, 0x473780, cat_wrap},
        {0x49a54f, 0x473780, cat_wrap},
        {0x466ea9, 0x466d60, mk_find}, {0x466ee0, 0x466d60, mk_find}, {0x4671f6, 0x466d60, mk_find},
        {0x467249, 0x466d60, mk_find},
        {0x466eb8, 0x466120, shpread_wrap}, {0x466eef, 0x466120, shpread_wrap}, {0x467214, 0x466120, shpread_wrap},
        {0x467267, 0x466120, shpread_wrap},
        {0x45636e, 0x4554c0, maskfind_wrap},
    };
    int n = sizeof calls / sizeof calls[0];
    for (int i = 0; i < n; i++) {   /* all or nothing */
        BYTE *p = (BYTE *)calls[i].at;
        if (p[0] != 0xe8 || *(INT32 *)(p + 1) != (INT32)(calls[i].from - (calls[i].at + 5))) {
            logf("KYRIE parts: NOT INSTALLED (unexpected code at %#lx)", calls[i].at);
            return;
        }
    }
    for (int i = 0; i < n; i++) {
        BYTE *p = (BYTE *)calls[i].at;
        DWORD old;
        VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
        *(INT32 *)(p + 1) = (INT32)((BYTE *)calls[i].to - (p + 5));
        VirtualProtect(p, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), p, 5);
    }
    logf("KYRIE parts hooks ok");
}

/* ------------------------------------------------------------------ write watch (debug: [net] watch=1)
 * Hardware data breakpoints on the equipped chest/arm slots (0x4dc764, 0x4dc768): logs the code address
 * and new value of every write, to find what resets a part. */
static DWORD g_mainthread;

static LONG CALLBACK watch_veh(EXCEPTION_POINTERS *ep) {
    if (ep->ExceptionRecord->ExceptionCode != EXCEPTION_SINGLE_STEP) return EXCEPTION_CONTINUE_SEARCH;
    CONTEXT *c = ep->ContextRecord;
    if (!(c->Dr6 & 3)) return EXCEPTION_CONTINUE_SEARCH;
    DWORD *sp = (DWORD *)c->Esp;
    logf("watch: write at eip %08lx (dr6 %lx) chest %d arm %d  stack %08lx %08lx %08lx %08lx", c->Eip, c->Dr6,
         *(int *)0x4dc764, *(int *)0x4dc768, sp[0], sp[1], sp[2], sp[3]);
    c->Dr6 = 0;
    return EXCEPTION_CONTINUE_EXECUTION;
}
static DWORD WINAPI watch_thread(void *arg) {
    Sleep(500);
    HANDLE t = OpenThread(THREAD_ALL_ACCESS, FALSE, g_mainthread);
    if (!t) return 0;
    SuspendThread(t);
    CONTEXT c; memset(&c, 0, sizeof c); c.ContextFlags = CONTEXT_DEBUG_REGISTERS;
    GetThreadContext(t, &c);
    c.Dr0 = 0x4dc764; c.Dr1 = 0x4dc768;
    c.Dr7 = (1 << 0) | (1 << 2) | (1u << 16) | (3u << 18) | (1u << 20) | (3u << 22);   /* L0,L1: write, 4 bytes */
    SetThreadContext(t, &c);
    ResumeThread(t);
    CloseHandle(t);
    logf("watch armed on 0x4dc764 / 0x4dc768");
    return 0;
}

typedef int (WINAPI *GETSYSMETRICS)(int);
static GETSYSMETRICS real_GetSystemMetrics;
static int WINAPI fake_GetSystemMetrics(int i) {
    if (i == SM_CXSCREEN) return g_fakew;
    if (i == SM_CYSCREEN) return g_fakeh;
    return real_GetSystemMetrics(i);
}

/* replace one import of a module (by name, or by ordinal when ord != 0) */
static void *hook_import_ex(HMODULE mod, const char *dll, const char *func, WORD ord, void *repl) {
    BYTE *base = (BYTE *)mod;
    IMAGE_NT_HEADERS *nt = (IMAGE_NT_HEADERS *)(base + ((IMAGE_DOS_HEADER *)base)->e_lfanew);
    IMAGE_DATA_DIRECTORY dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
    if (!dir.VirtualAddress) return NULL;
    for (IMAGE_IMPORT_DESCRIPTOR *d = (IMAGE_IMPORT_DESCRIPTOR *)(base + dir.VirtualAddress); d->Name; d++) {
        if (lstrcmpiA((char *)base + d->Name, dll)) continue;
        IMAGE_THUNK_DATA *names = (IMAGE_THUNK_DATA *)(base + (d->OriginalFirstThunk ? d->OriginalFirstThunk : d->FirstThunk));
        IMAGE_THUNK_DATA *iat = (IMAGE_THUNK_DATA *)(base + d->FirstThunk);
        for (; names->u1.AddressOfData; names++, iat++) {
            if (IMAGE_SNAP_BY_ORDINAL(names->u1.Ordinal)) {
                if (!ord || IMAGE_ORDINAL(names->u1.Ordinal) != ord) continue;
            } else {
                IMAGE_IMPORT_BY_NAME *ibn = (IMAGE_IMPORT_BY_NAME *)(base + names->u1.AddressOfData);
                if (strcmp((char *)ibn->Name, func)) continue;
            }
            DWORD old; void *orig = (void *)iat->u1.Function;
            VirtualProtect(&iat->u1.Function, sizeof(void *), PAGE_READWRITE, &old);
            iat->u1.Function = (ULONG_PTR)repl;
            VirtualProtect(&iat->u1.Function, sizeof(void *), old, &old);
            return orig;
        }
    }
    return NULL;
}

static void *hook_import(HMODULE mod, const char *dll, const char *func, void *repl) {
    return hook_import_ex(mod, dll, func, 0, repl);
}

__declspec(dllexport) int AxisNetVersion(void) { return 2; }

/* RECOMP TEST BUILD ONLY: the widescreen state the rebuilt game functions that carry these fixes need (menu_vertex,
   menu_drawRect, gfx_setProjection2D3D, hud_drawMain; recomp.dll src/wide.h has the same layout), handed over
   when recomp.dll is loaded */
static volatile int g_menufix;   /* menu_vtx / rect_wrap / trans_wrap installed (menu43) */
static const struct {
    int size;
    const volatile int *menuFix, *menu43, *inHud, *hudArea, *cursorOn, *cursorX, *cursorW;
    volatile int *hudPart;
    void (__cdecl *fullScreen)(int on);
} g_wide = { sizeof g_wide, &g_menufix, &g_menu43, &g_inhud, &g_area, &g_cur_on, &g_cur_vx, &g_cur_vw, &g_hudpart, menu_full };

static HMODULE g_recomp;   /* RECOMP TEST BUILD ONLY: recomp.dll, when loaded */

#ifdef AXIS_STANDALONE
/* STANDALONE BUILD (recomp/standalone): this file is compiled into AxisRC.exe, which maps the game's image at
   0x400000 itself; the exe module is AxisRC.exe, so the game image is named by its address, the rebuilt functions
   are in the same exe, and AxisRC.exe switches them in itself once this returns */
void recomp_setWide(const void *wide);
#define GetModuleHandleA_exe() ((HMODULE)0x400000)
BOOL WINAPI axisnet_attach(HINSTANCE inst, DWORD reason, LPVOID reserved) {
    if (reason != DLL_PROCESS_ATTACH) return TRUE;
    (void)inst;
    recomp_setWide(&g_wide);
#else
#define GetModuleHandleA_exe() GetModuleHandleA(NULL)
BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID reserved) {
    if (reason != DLL_PROCESS_ATTACH) return TRUE;
    DisableThreadLibraryCalls(inst);
#endif
#ifndef AXIS_STANDALONE
    { /* RECOMP TEST BUILD ONLY: load rebuilt game functions (recomp.dll) from the game folder if present */
      char rp[MAX_PATH]; GetModuleFileNameA(NULL, rp, MAX_PATH); strcpy(strrchr(rp, '\\') + 1, "recomp.dll");
      HMODULE rm = g_recomp = GetFileAttributesA(rp) != INVALID_FILE_ATTRIBUTES ? LoadLibraryA(rp) : NULL;
      void (*set_wide)(const void *) = rm ? (void (*)(const void *))GetProcAddress(rm, "recomp_setWide") : NULL;
      if (set_wide) set_wide(&g_wide); }
#endif
    /* The game renders at the monitor's real resolution (DESKTOP mode), but with display scaling Windows
       gives a DPI-unaware program a smaller, stretched window, so only part of the picture was visible
       (menus off-centre, top cut off). Declare DPI awareness before the game creates its window. */
    typedef BOOL (WINAPI *SETDPICTX)(HANDLE);
    SETDPICTX setdpi = (SETDPICTX)GetProcAddress(GetModuleHandleA("user32.dll"), "SetProcessDpiAwarenessContext");
    int dpi_ok = setdpi ? setdpi((HANDLE)-4) : 0;  /* DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2 */
    if (!dpi_ok) dpi_ok = SetProcessDPIAware();
    InitializeCriticalSection(&g_logcs); InitializeCriticalSection(&g_pingcs);
    InitializeCriticalSection(&g_reccs); InitializeCriticalSection(&g_vmcs); InitializeCriticalSection(&hub.cs);
    hub.ls = hub.us = INVALID_SOCKET;
    load_config();
    HMODULE exe = GetModuleHandleA_exe();
    real_CoCreateInstance = hook_import(exe, "ole32.dll", "CoCreateInstance", hook_CoCreateInstance);
    real_IcmpSendEcho = hook_import(exe, "ICMP.dll", "IcmpSendEcho", hook_IcmpSendEcho);
    real_connect = hook_import_ex(exe, "WS2_32.dll", "connect", 4, hook_connect);  /* Axis imports Winsock by ordinal */
    int movie = hook_movie(exe);
    hook_marked();
    /* ARM CENTER mech rotation (right-drag, 0x461850): yaw/pitch come from the menu cursor's position relative
       to the centre, (x - W/2) / W * 360 deg and (y - H/2) / (H/2) * 89 deg, but the callers pass the screen
       size in pixels while the cursor is in 640x480 units - above 640x480 the mech could only turn a small
       part of the way (about 59 deg of yaw at 3840 wide). The four uses of W/H there now use 640/480. */
    static int rot_w = 640;
    static const struct { DWORD at; BYTE sig[7], rep[7]; } rot[] = {
        {0x461962, {0x8b,0x84,0x24,0x60,0xb0,0x00,0x00}, {0xb8,0xe0,0x01,0x00,0x00,0x90,0x90}},   /* mov eax,H -> 480 */
        {0x461982, {0x8b,0x84,0x24,0x5c,0xb0,0x00,0x00}, {0xb8,0x80,0x02,0x00,0x00,0x90,0x90}},   /* mov eax,W -> 640 */
        {0x4619bb, {0xda,0xb4,0x24,0x5c,0xb0,0x00,0x00}, {0xda,0x35,0,0,0,0,0x90}},               /* fidiv W -> [rot_w] */
        {0x4619e1, {0x8b,0x84,0x24,0x60,0xb0,0x00,0x00}, {0xb8,0xe0,0x01,0x00,0x00,0x90,0x90}}};  /* mov eax,H -> 480 */
    int rot_ok = 1;
    for (int i = 0; i < 4; i++) if (IsBadReadPtr((void *)rot[i].at, 7) || memcmp((void *)rot[i].at, rot[i].sig, 7)) rot_ok = 0;
    if (rot_ok) {
        for (int i = 0; i < 4; i++) {
            BYTE c[7]; memcpy(c, rot[i].rep, 7);
            if (c[0] == 0xda) *(DWORD *)(c + 2) = (DWORD)&rot_w;
            DWORD old;
            VirtualProtect((void *)rot[i].at, 7, PAGE_EXECUTE_READWRITE, &old);
            memcpy((void *)rot[i].at, c, 7);
            VirtualProtect((void *)rot[i].at, 7, old, &old);
            FlushInstructionCache(GetCurrentProcess(), (void *)rot[i].at, 7);
        }
    }
    logf("ARM CENTER rotation range fix %s", rot_ok ? "ok" : "NOT INSTALLED (unknown exe)");
    if (g_watch) {
        g_mainthread = GetCurrentThreadId();
        AddVectoredExceptionHandler(1, watch_veh);
        CloseHandle(CreateThread(NULL, 0, watch_thread, NULL, 0, NULL));
    }
    if (g_fakew) {
        real_GetSystemMetrics = hook_import(exe, "USER32.dll", "GetSystemMetrics", fake_GetSystemMetrics);
        logf("fakeres %dx%d (%s)", g_fakew, g_fakeh, real_GetSystemMetrics ? "hooked" : "hook FAILED");
    }
    /* menu cursor proportions (AxisGL): the right-hand corners of the cursor sprite -> cursor_vtx */
    static const BYTE sig_cur[] = {0x8d, 0x6e, 0x2f, 0x57, 0x55, 0xe8};   /* 0x429cbe: lea ebp,[esi+2f]; push edi; push ebp; call */
    if (!IsBadReadPtr((void *)0x429cbe, 16) && !memcmp((void *)0x429cbe, sig_cur, sizeof sig_cur)) {
        static const DWORD at[] = {0x429cc3, 0x429cf0};
        for (int i = 0; i < 2; i++) {
            BYTE *p = (BYTE *)at[i];
            if (p[0] != 0xe8 || *(INT32 *)(p + 1) != (INT32)(0x41ef60 - (at[i] + 5))) continue;
            DWORD old;
            VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
            *(INT32 *)(p + 1) = (INT32)((BYTE *)cursor_vtx - (p + 5));
            VirtualProtect(p, 5, old, &old);
            FlushInstructionCache(GetCurrentProcess(), p, 5);
        }
    }
    /* name label icon spacing (AxisGL): replace "len/2*8" at 0x491c52 with label_halfw(name) */
    static const BYTE sig_icon[] = {0x8d,0x7c,0x24,0x38,0x83,0xc9,0xff,0x33,0xc0,0xf2,0xae,0xf7,0xd1,0x49,
                                    0xd1,0xe9,0xc1,0xe1,0x03,0x2b,0xd1};
    BYTE *pi = (BYTE *)0x491c52;
    if (!IsBadReadPtr(pi, sizeof sig_icon) && !memcmp(pi, sig_icon, sizeof sig_icon)) {
        BYTE c[sizeof sig_icon] = {0x52, 0x8d,0x44,0x24,0x3c, 0x50, 0xe8,0,0,0,0, 0x59, 0x5a, 0x2b,0xd0,
                                   0x90,0x90,0x90,0x90,0x90,0x90};   /* push edx; lea eax,[esp+3c]; push eax;
                                   call label_halfw; pop ecx; pop edx; sub edx,eax */
        *(INT32 *)(c + 7) = (INT32)((BYTE *)label_halfw - (pi + 11));
        DWORD old;
        VirtualProtect(pi, sizeof c, PAGE_EXECUTE_READWRITE, &old);
        memcpy(pi, c, sizeof c);
        VirtualProtect(pi, sizeof c, old, &old);
        FlushInstructionCache(GetCurrentProcess(), pi, sizeof c);
    }
    /* in-match menu mouse (AxisGL): 0x49ddcb -> push esi; call menu_nav; pop ecx; jmp 0x49de23 (menusens=0: original) */
    static const BYTE sig_nav[] = {0xd9,0x86,0x93,0x32,0x34,0x02,0xd8,0x1d,0x58,0x95,0x4a,0x00,0xdf,0xe0,0xf6,0xc4,
                                   0x01,0x75,0x13,0xd9,0x86,0x97,0x32,0x34};
    BYTE *pn = (BYTE *)0x49ddcb;
    if (g_menusens > 0 && !IsBadReadPtr(pn, sizeof sig_nav) && !memcmp(pn, sig_nav, sizeof sig_nav)) {
        BYTE c[12] = {0x56, 0xe8,0,0,0,0, 0x59, 0xe9,0,0,0,0};
        *(INT32 *)(c + 2) = (INT32)((BYTE *)menu_nav - (pn + 6));
        *(INT32 *)(c + 8) = (INT32)((BYTE *)0x49de23 - (pn + 12));
        DWORD old;
        VirtualProtect(pn, sizeof c, PAGE_EXECUTE_READWRITE, &old);
        memcpy(pn, c, sizeof c);
        VirtualProtect(pn, sizeof c, old, &old);
        FlushInstructionCache(GetCurrentProcess(), pn, sizeof c);
    }
    /* proportional HUD: AxisGL's layout only (HUD width getter at 0x4685b0, main HUD routine at 0x4926f0) */
    int hud = 0;
    static const BYTE sig_w[] = {0xa1, 0x10, 0xe8, 0xa0, 0x00, 0xc3}, sig_hud[] = {0x81, 0xec, 0x3c, 0x01, 0x00, 0x00};
    if ((g_hud43 || g_hudtrace) && !IsBadReadPtr((void *)0x4685b0, 8) && !memcmp((void *)0x4685b0, sig_w, 6)
        && !memcmp((void *)0x4926f0, sig_hud, 6)) {
        real_glViewport = hook_import(exe, "OPENGL32.dll", "glViewport", hook_glViewport);
        real_glVertex2i = hook_import(exe, "OPENGL32.dll", "glVertex2i", hook_glVertex2i);
        hud = real_glViewport && real_glVertex2i;
        BYTE *pt = (BYTE *)0x49395f;   /* call 0x46bb00 (power-up seconds) -> pu_text */
        if (hud && g_hud43 && pt[0] == 0xe8 && *(INT32 *)(pt + 1) == (INT32)(0x46bb00 - 0x493964)) {
            DWORD old;
            VirtualProtect(pt, 5, PAGE_EXECUTE_READWRITE, &old);
            *(INT32 *)(pt + 1) = (INT32)((BYTE *)pu_text - (pt + 5));
            VirtualProtect(pt, 5, old, &old);
            FlushInstructionCache(GetCurrentProcess(), pt, 5);
        }
        BYTE *pl = (BYTE *)0x491c2d;   /* call 0x44ae10 (player name label) -> label_text */
        if (hud && g_hud43 && pl[0] == 0xe8 && *(INT32 *)(pl + 1) == (INT32)(0x44ae10 - 0x491c32)) {
            DWORD old;
            VirtualProtect(pl, 5, PAGE_EXECUTE_READWRITE, &old);
            *(INT32 *)(pl + 1) = (INT32)((BYTE *)label_text - (pl + 5));
            VirtualProtect(pl, 5, old, &old);
            FlushInstructionCache(GetCurrentProcess(), pl, 5);
        }
        static const struct { DWORD at, target; void *wrap; } calls[] = {
            {0x498580, 0x4913a0, (void *)markers_wrap}, {0x48a19c, 0x4913a0, (void *)markers_wrap},
            {0x498654, 0x4926f0, (void *)mainhud_wrap}, {0x498862, 0x495510, (void *)fps_wrap},
            {0x4986a0, 0x494930, (void *)rank_wrap}, {0x4985c4, 0x491f50, (void *)lockon_wrap},
            /* auto play overlay (ov_wrap) */
            {0x48a1f7, 0x496820, (void *)ov_icon_left}, {0x48a259, 0x44ad60, (void *)ov_text_left},
            {0x48a299, 0x496820, (void *)ov_icon_right}, {0x48a2ff, 0x44ad60, (void *)ov_text_right},
            {0x48a1c0, 0x495190, (void *)ov_message}, {0x48a309, 0x496b80, (void *)ov_name},
            {0x48a318, 0x494930, (void *)ov_rank}};
        for (int i = 0; i < (int)(sizeof calls / sizeof calls[0]) && hud && g_hud43; i++) {
            BYTE *p = (BYTE *)calls[i].at;
            if (p[0] != 0xe8 || *(INT32 *)(p + 1) != (INT32)(calls[i].target - (calls[i].at + 5))) continue;
            DWORD old;
            VirtualProtect(p, 5, PAGE_EXECUTE_READWRITE, &old);
            *(INT32 *)(p + 1) = (INT32)((BYTE *)calls[i].wrap - (p + 5));
            VirtualProtect(p, 5, old, &old);
            FlushInstructionCache(GetCurrentProcess(), p, 5);
        }
        BYTE *pc = (BYTE *)0x48b386;   /* call 0x4982f0 (in-match 2D pass) -> hud_pass_wrap */
        if (hud && pc[0] == 0xe8 && *(INT32 *)(pc + 1) == (INT32)(0x4982f0 - 0x48b38b)) {
            DWORD old;
            VirtualProtect(pc, 5, PAGE_EXECUTE_READWRITE, &old);
            *(INT32 *)(pc + 1) = (INT32)((BYTE *)hud_pass_wrap - (pc + 5));
            VirtualProtect(pc, 5, old, &old);
            FlushInstructionCache(GetCurrentProcess(), pc, 5);
        } else hud = 0;
        static const BYTE sig_d[] = {0xd8, 0x0d, 0x7c, 0xa2, 0x4a, 0x00};   /* 0x46bdda: fmul dword ptr [0x4aa27c] (26.0) */
        if (hud && g_hud43 && !memcmp((void *)0x46bdda, sig_d, 6)) {
            DWORD old, addr = (DWORD)&g_digit_h;
            VirtualProtect((void *)0x46bddc, 4, PAGE_EXECUTE_READWRITE, &old);
            *(DWORD *)0x46bddc = addr;
            VirtualProtect((void *)0x46bddc, 4, old, &old);
            FlushInstructionCache(GetCurrentProcess(), (void *)0x46bdda, 6);
        }
        if (!hud) g_hud43 = g_hudtrace = 0;
    } else g_hud43 = g_hudtrace = 0;
    /* menus 4:3 (AxisGL): menus and other front-end screens are laid out in 640x480 units and drawn after the
       2D projection switch 0x41ef90, whose widefix hook (cave 0x4a8fb4) gives them a centred viewport of
       h*16/9 when the screen is wider than that. With [hud] menu43=1 (default) the box is h*4/3 instead
       ("shl eax,4 / mov ebx,9" -> "shl eax,2 / mov ebx,3"), so on any screen wider than 4:3 the menus keep
       their original proportions, centred, while the 3D behind them (menu backgrounds, ARM CENTER mech) still
       fills the screen. The in-match HUD has its own projection (0x4685f0), but a few things it draws (player
       name labels) switch through 0x41ef90 too; while the HUD pass runs (g_inhud, hud_pass_wrap) the viewport
       hook gives them the old 16:9 box back, otherwise the rest of the HUD was clipped to the 4:3 box when an
       enemy was in view. That needs the viewport hook and the HUD pass wrapper, installed here if the HUD
       hooks above weren't. */
    static const BYTE sig_box[] = {0xc1,0xe0,0x04,0xbb,0x09,0x00,0x00,0x00,0xf7,0xf3,0x8d,0x58,0x08,0x39,0xcb};
    BYTE *phw = (BYTE *)0x48b386;   /* call 0x4982f0 (in-match 2D pass) */
    int inhud_ok = phw[0] == 0xe8 && *(INT32 *)(phw + 1) == (INT32)((BYTE *)hud_pass_wrap - (phw + 5));
    if (g_menu43 && !inhud_ok && phw[0] == 0xe8 && *(INT32 *)(phw + 1) == (INT32)(0x4982f0 - 0x48b38b)) {
        DWORD old;
        VirtualProtect(phw, 5, PAGE_EXECUTE_READWRITE, &old);
        *(INT32 *)(phw + 1) = (INT32)((BYTE *)hud_pass_wrap - (phw + 5));
        VirtualProtect(phw, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), phw, 5);
        inhud_ok = 1;
    }
    if (g_menu43 && inhud_ok && !real_glViewport) real_glViewport = hook_import(exe, "OPENGL32.dll", "glViewport", hook_glViewport);
    if (g_menu43 && (!inhud_ok || !real_glViewport)) { g_menu43 = 0; logf("menus: 4:3 box NOT enabled (HUD pass / viewport hook missing)"); }
    if (g_menu43 && !IsBadReadPtr((void *)0x4a8fbb, sizeof sig_box) && !memcmp((void *)0x4a8fbb, sig_box, sizeof sig_box)) {
        DWORD old;
        VirtualProtect((void *)0x4a8fbb, 8, PAGE_EXECUTE_READWRITE, &old);
        ((BYTE *)0x4a8fbb)[2] = 0x02; ((BYTE *)0x4a8fbb)[4] = 0x03;
        VirtualProtect((void *)0x4a8fbb, 8, old, &old);
        FlushInstructionCache(GetCurrentProcess(), (void *)0x4a8fbb, 8);
        /* full-screen effects keep covering the whole screen (menu_vtx / trans_wrap / rect_wrap) */
        static const BYTE sig_vtx[] = {0xdb,0x44,0x24,0x08,0xd8,0x0d,0x14,0xf0,0x4d,0x00};
        static const BYTE sig_rect[] = {0xa1,0x8c,0xa4,0x9d,0x00,0x8b,0x0d,0x88,0xa4,0x9d,0x00};
        BYTE *pv = (BYTE *)0x41ef60, *pr = (BYTE *)0x427970, *pt = (BYTE *)0x41f903;
        if (!memcmp(pv, sig_vtx, sizeof sig_vtx) && !memcmp(pr, sig_rect, sizeof sig_rect) &&
            pt[0] == 0xe8 && *(INT32 *)(pt + 1) == (INT32)(0x429170 - 0x41f908)) {
            struct { BYTE *at; void *to; BYTE op; } j[] = {{pv, (void *)menu_vtx, 0xe9}, {pr, (void *)rect_wrap, 0xe9},
                                                          {pt, (void *)trans_wrap, 0xe8}};
            for (int i = 0; i < 3; i++) {
                VirtualProtect(j[i].at, 5, PAGE_EXECUTE_READWRITE, &old);
                j[i].at[0] = j[i].op; *(INT32 *)(j[i].at + 1) = (INT32)((BYTE *)j[i].to - (j[i].at + 5));
                VirtualProtect(j[i].at, 5, old, &old);
                FlushInstructionCache(GetCurrentProcess(), j[i].at, 5);
            }
            BYTE *pcur = (BYTE *)0x41fc28;   /* call 0x429bc0 (menu cursor) -> cursor_draw */
            if (pcur[0] == 0xe8 && *(INT32 *)(pcur + 1) == (INT32)(0x429bc0 - 0x41fc2d)) {
                VirtualProtect(pcur, 5, PAGE_EXECUTE_READWRITE, &old);
                *(INT32 *)(pcur + 1) = (INT32)((BYTE *)cursor_draw - (pcur + 5));
                VirtualProtect(pcur, 5, old, &old);
                FlushInstructionCache(GetCurrentProcess(), pcur, 5);
            }
            g_menufix = 1;
            logf("menus: centred 4:3 box, full-screen effects kept full screen");
        } else logf("menus: centred 4:3 box (full-screen effect hooks NOT installed)");
    }
    BYTE *pin = (BYTE *)0x445c69;   /* call 0x401730 (DInput mouse read) -> input_read */
    if (pin[0] == 0xe8 && *(INT32 *)(pin + 1) == (INT32)(0x401730 - 0x445c6e) &&
        (*(BYTE *)0x401730 == 0xe9 || (*(BYTE *)0x401730 == 0xa1 && *(DWORD *)0x401731 == 0x4d1fa4))) {
        DWORD old;
        VirtualProtect(pin, 5, PAGE_EXECUTE_READWRITE, &old);
        *(INT32 *)(pin + 1) = (INT32)((BYTE *)input_read - (pin + 5));
        VirtualProtect(pin, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), pin, 5);
        logf("input: mouse buttons held across alt-tab ignored, chat line refocused");
    }
    if (g_sharptext) hook_sharptext();
    hook_digits();
    static const BYTE sig_clamp[] ={0x81, 0xf9, 0x76, 0x02, 0x00, 0x00, 0x7e, 0x0b};   /* cmp ecx,630; jle */
    BYTE *pcl = (BYTE *)0x445cd8;   /* menu cursor clamp -> cursor_clamp (whole screen) */
    if (!memcmp(pcl, sig_clamp, sizeof sig_clamp) && *(DWORD *)0x445cf4 == 474) {
        DWORD old;
        VirtualProtect(pcl, 6, PAGE_EXECUTE_READWRITE, &old);
        pcl[0] = 0xe9; *(INT32 *)(pcl + 1) = (INT32)((BYTE *)cursor_clamp_wrap - (pcl + 5)); pcl[5] = 0x90;
        VirtualProtect(pcl, 6, old, &old);
        FlushInstructionCache(GetCurrentProcess(), pcl, 6);
        logf("menus: cursor reaches the whole screen");
    }
    static const BYTE sig_pressed[] ={0x56, 0x8b, 0x74, 0x24, 0x08, 0x81, 0xfe, 0xfa, 0x00, 0x00, 0x00};
    BYTE *pjp = (BYTE *)0x401600;   /* "just pressed" test -> pressed_wrap (mouse buttons latch like keys) */
    if (!memcmp(pjp, sig_pressed, sizeof sig_pressed) && *(DWORD *)0x40160e == 0x4d1e80) {
        DWORD old;
        VirtualProtect(pjp, 5, PAGE_EXECUTE_READWRITE, &old);
        pjp[0] = 0xe9; *(INT32 *)(pjp + 1) = (INT32)((BYTE *)pressed_wrap - (pjp + 5));
        VirtualProtect(pjp, 5, old, &old);
        FlushInstructionCache(GetCurrentProcess(), pjp, 5);
        logf("input: mouse clicks in key bindings counted every time");
    }
    logf("proportional HUD %s (max aspect %.3f)", hud && g_hud43 ? "on" : "off", g_hudaspect);
    logf("axisnet 2 loaded in %s mode (%s), hub port %d, game-list port %d, hooks: dplay %s ping %s connect %s movie %s, dpi-aware %s",
         g_local ? "local" : "server", g_local ? "players host in their own game" : g_server, g_hubport, g_mainport,
         real_CoCreateInstance ? "ok" : "MISSING", real_IcmpSendEcho ? "ok" : "MISSING", real_connect ? "ok" : "MISSING",
         movie ? "ok" : "MISSING", dpi_ok ? "yes" : "no");
    if (!real_connect) real_connect = connect;
    if (!real_CoCreateInstance) real_CoCreateInstance = (COCREATE)CoCreateInstance;
    { /* RECOMP TEST BUILD ONLY: with RECOMP_EARLY=1, recomp.dll switches its tested functions in now, after this
         DLL's own patches and before the game's code runs (see recomp.c recomp_hookEarly) */
      int (*early)(void) = g_recomp ? (int (*)(void))GetProcAddress(g_recomp, "recomp_hookEarly") : NULL;
      if (early) logf("recomp: %d rebuilt functions switched in at start-up", early()); }
    return TRUE;
}
