/* axisnet_dp.c: axisnet's network part - the DirectPlay 4 replacement (the DirectPlay and DirectPlayLobby objects
   the game gets from CoCreateInstance), the session hub, LAN discovery, the built-in game list and the ping - kept
   apart from the patch layer so that it builds for other systems too (PORTING.md stage 3). axisnet_recomp.c
   includes it where it stood; on Windows nothing about it changed. */

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
#ifdef AXIS_NATIVE   /* (the native build reads the fixes' settings itself: standalone/platform.c) */
static int g_fakew, g_fakeh;
#else
static int g_hudtrace, g_fakew, g_fakeh, g_hud43 = 1, g_watch, g_menu43 = 1, g_sharptext = 1;
static double g_hudaspect = 16.0 / 9.0;
static double g_menusens = 1.0;
#endif

static char g_logdir[MAX_PATH];   /* (the log's folder: the game folder, or the user folder - AXISNET_USERDIR) */
static void logf(const char *fmt, ...) {
    if (!g_log) return;
    char path[MAX_PATH], line[1024];
    va_list ap; va_start(ap, fmt); vsnprintf(line, sizeof line, fmt, ap); va_end(ap);
    snprintf(path, sizeof path, "%saxisnet.log", g_logdir);
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

#ifdef AXISNET_POSIX   /* (the folder separator in g_dir's paths) */
#define AXNET_SEP '/'
#else
#define AXNET_SEP '\\'
#endif
static void load_config(void) {
    char ini[MAX_PATH], mode[32];
    if (GetEnvironmentVariableA("AXIS_GAME_DIR", g_dir, MAX_PATH - 2)) {  /* (a host's game folder: axis_api.h) */
        size_t n = strlen(g_dir); if (n && g_dir[n - 1] != AXNET_SEP) { g_dir[n] = AXNET_SEP; g_dir[n + 1] = 0; }
    } else {
    GetModuleFileNameA(NULL, g_dir, MAX_PATH);  /* settings and log live next to the game exe */
    char *p = strrchr(g_dir, AXNET_SEP); if (p) p[1] = 0; else g_dir[0] = 0;
    }
    snprintf(ini, sizeof ini, "%saxisnet.ini", g_dir);
    snprintf(g_logdir, sizeof g_logdir, "%s", g_dir);
#ifdef AXISNET_USERDIR   /* (Linux / macOS, the 64-bit build: the user folder - src/plat/posix/files.c - takes the log,
                            and its axisnet.ini, when there is one, is the one read) */
    {
        const char *plat_userDir(void);
        const char *u = plat_userDir();
        if (u && *u) {
            char mine[MAX_PATH];
            snprintf(g_logdir, sizeof g_logdir, "%s/", u);
            snprintf(mine, sizeof mine, "%s/axisnet.ini", u);
            FILE *t = fopen(mine, "r");
            if (t) { fclose(t); snprintf(ini, sizeof ini, "%s", mine); }
        }
    }
#endif
    GetPrivateProfileStringA("net", "mode", "local", mode, sizeof mode, ini);
    g_local = _stricmp(mode, "server") != 0;
    GetPrivateProfileStringA("net", "server", "", g_server, sizeof g_server, ini);
    g_port = GetPrivateProfileIntA("net", "port", 0, ini);
    g_hubport = GetPrivateProfileIntA("net", "hubport", 2300, ini);
    g_discport = GetPrivateProfileIntA("net", "discport", g_hubport + 1, ini);
    g_upnp = GetPrivateProfileIntA("net", "upnp", 1, ini);
    g_log = GetPrivateProfileIntA("net", "log", 0, ini);
#ifndef AXIS_NATIVE
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
#endif
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
#ifdef AXISNET_POSIX   /* (a refused connection is writable here too: its outcome is SO_ERROR's) */
    if (ok) { int err = 0; socklen_t el = sizeof err; ok = !getsockopt(s, SOL_SOCKET, SO_ERROR, &err, &el) && !err; }
#endif
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
    sendto(us, (char *)RELOC(r), sizeof r, 0, (struct sockaddr *)&from, fl);
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
#ifdef AXISNET_POSIX   /* (the port free again at once after a game - its old connections in TIME_WAIT - as on Windows;
                          there SO_REUSEADDR would let another program take the port, so not on Windows) */
    { int reuse = 1; setsockopt(hub.ls, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof reuse); }
#endif
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

#ifdef AXISNET_POSIX   /* (no NATUPnP COM object, no clipboard here: logged; a host can do both) */
static DWORD WINAPI upnp_thread(void *arg) {
    char ips[128];
    local_ips(ips, sizeof ips);
    if (arg) logf("hub: no UPnP on this system - forward TCP %d to this computer (%s) for players outside the LAN", g_hubport, ips);
    return 0;
}
#else
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

#endif   /* (AXISNET_POSIX: UPnP) */

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
        int got = recvfrom(u, (char *)RELOC(b), sizeof b, 0, (struct sockaddr *)&from, &fl);
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
                memset(r + 0x33, 0, 16); lstrcpynA((char *)RELOC(r) + 0x33, d[i].ip, 16);
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
        MSG_CREATE *c = (MSG_CREATE *)RELOC(out); memset(c, 0, sizeof *c);
        c->dwType = DPSYS_CREATEPLAYERORGROUP; c->dwPlayerType = DPPLAYERTYPE_PLAYER;
        c->dpId = m->dpid; c->dwCurrentPlayers = m->cur; n = &c->dpnName; q = (char *)(RELOC(c) + 1);
    } else {
        MSG_DESTROY *d = (MSG_DESTROY *)RELOC(out); memset(d, 0, sizeof *d);
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
    DPCAE el[2] = {{SP_TCPIP, 16, (void *)RELOC(sp)}, {*type, dsize, data}};
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
