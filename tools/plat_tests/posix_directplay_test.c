/* posix_directplay_test.c: axisnet's DirectPlay on Linux (plat/posix/directplay.c), end to end: two processes on
   loopback as two players - the host creates a session (axisnet's hub starts) and a player, the client finds the
   session, joins, creates its player and sends a message; the host sees the join (DPSYS_CREATEPLAYERORGROUP) and the
   message and answers; the client sees the host's player and the answer. Both use the objects as the game does (from
   CoCreateInstance, the connection from the lobby's CreateAddress). Run in WSL by tools/plat_tests/run_posix.sh. */
#define AXIS_PORTABLE 1
#include "../../src/plat/posix/directplay.c"
#include <sys/wait.h>

static int fails;
static void check(int ok, const char *who, const char *what)
{
	printf("%s  [%s] %s\n", ok ? "PASS" : "FAIL", who, what);
	fflush(stdout);
	if (!ok)
		fails++;
}

extern HRESULT WINAPI game_CoCreateInstance(REFCLSID, void *, DWORD, REFIID, void **) __asm__("_plat_CoCreateInstance");
static const GUID k_iid = { 0 };
static const GUID k_app = { 0x12345678, 0x1234, 0x1234, { 1, 2, 3, 4, 5, 6, 7, 8 } };

static DP *make(const char *who, const char *target)
{
	DP *dp = NULL;
	Lobby *lobby = NULL;
	check(game_CoCreateInstance(&CLSID_DirectPlay_, NULL, 1, &k_iid, (void **)&dp) == S_OK && dp, who, "CoCreateInstance(CLSID_DirectPlay)");
	check(game_CoCreateInstance(&CLSID_DirectPlayLobby_, NULL, 1, &k_iid, (void **)&lobby) == S_OK && lobby, who, "CoCreateInstance(CLSID_DirectPlayLobby)");
	BYTE blob[256];
	DWORD size = sizeof blob;
	check(LB_CreateAddress(lobby, &SP_TCPIP, &DPAID_INet_, (void *)target, (DWORD)strlen(target), blob, &size) == DP_OK, who, "lobby CreateAddress (TCP/IP)");
	check(DP_InitializeConnection(dp, blob, 0) == DP_OK, who, "InitializeConnection");
	return dp;
}

static DPSD2 g_found;
static char g_foundName[NAMELEN];
static int g_foundCount;
static BOOL WINAPI on_session(const DPSD2 *sd, DWORD *timeout, DWORD flags, void *ctx)
{
	(void)timeout; (void)ctx;
	if (flags & DPESC_TIMEDOUT || !sd)
		return FALSE;
	if (!g_foundCount++) {
		g_found = *sd;
		snprintf(g_foundName, sizeof g_foundName, "%s", sd->lpszSessionNameA ? sd->lpszSessionNameA : "");
		g_found.lpszSessionNameA = g_foundName;
	}
	return TRUE;
}
static int g_sawHost;
static BOOL WINAPI on_player(DWORD id, DWORD type, const DPNAME_ *name, DWORD flags, void *ctx)
{
	(void)id; (void)type; (void)flags; (void)ctx;
	if (name && name->lpszShortNameA && !strcmp(name->lpszShortNameA, "Host"))
		g_sawHost = 1;
	return TRUE;
}

static int host(void)
{
	DP *dp = make("host", "");
	DPSD2 sd;
	memset(&sd, 0, sizeof sd);
	sd.dwSize = sizeof sd;
	sd.dwMaxPlayers = 8;
	sd.guidApplication = k_app;
	sd.lpszSessionNameA = "Linux test game";
	check(DP_Open(dp, &sd, DPOPEN_CREATE) == DP_OK, "host", "Open(DPOPEN_CREATE): the session hosted, the hub running");
	DPNAME_ name = { sizeof name, 0, "Host", "Host player" };
	DWORD me = 0;
	check(DP_CreatePlayer(dp, &me, &name, NULL, NULL, 0, 0) == DP_OK && me, "host", "CreatePlayer(Host)");
	int joined = 0, hello = 0;
	DWORD client = 0;
	for (DWORD t0 = GetTickCount(); GetTickCount() - t0 < 15000 && !(joined && hello);) {
		BYTE buf[512];
		DWORD from = 0, to = 0, size = sizeof buf;
		if (DP_Receive(dp, &from, &to, 0, buf, &size) != DP_OK) {
			Sleep(20);
			continue;
		}
		if (from == DPID_SYSMSG) {
			MSG_CREATE *m = (MSG_CREATE *)buf;
			if (m->dwType == DPSYS_CREATEPLAYERORGROUP && m->dpnName.lpszShortNameA && !strcmp(m->dpnName.lpszShortNameA, "Client")) {
				joined = 1;
				client = m->dpId;
			}
		} else if (size == 18 && !memcmp(buf, "hello from client", 18)) {
			hello = 1;
			DP_Send(dp, me, from, 0, "welcome", 8);
		}
	}
	check(joined, "host", "the client's player joined (DPSYS_CREATEPLAYERORGROUP, \"Client\")");
	check(hello && client, "host", "its message arrived; the answer sent");
	Sleep(1500);   /* (the client reads the answer) */
	DP_Close(dp);
	return fails;
}

static int client(void)
{
	Sleep(1500);   /* (the host is up) */
	DP *dp = make("client", "127.0.0.1");
	DPSD2 sd;
	memset(&sd, 0, sizeof sd);
	sd.dwSize = sizeof sd;
	sd.guidApplication = k_app;
	check(DP_EnumSessions(dp, &sd, 1000, on_session, NULL, 0) == DP_OK && g_foundCount >= 1 && !strcmp(g_foundName, "Linux test game"),
	      "client", "EnumSessions at 127.0.0.1: \"Linux test game\"");
	check(DP_Open(dp, &g_found, DPOPEN_JOIN) == DP_OK, "client", "Open(DPOPEN_JOIN)");
	DPNAME_ name = { sizeof name, 0, "Client", "Client player" };
	DWORD me = 0;
	check(DP_CreatePlayer(dp, &me, &name, NULL, NULL, 0, 0) == DP_OK && me, "client", "CreatePlayer(Client)");
	Sleep(300);
	DP_EnumPlayers(dp, NULL, on_player, NULL, 0);
	check(g_sawHost, "client", "EnumPlayers: the host's player is there");
	check(DP_Send(dp, me, DPID_ALLPLAYERS, 0, "hello from client", 18) == DP_OK, "client", "Send to everyone");
	int welcome = 0;
	for (DWORD t0 = GetTickCount(); GetTickCount() - t0 < 8000 && !welcome;) {
		BYTE buf[512];
		DWORD from = 0, to = 0, size = sizeof buf;
		if (DP_Receive(dp, &from, &to, 0, buf, &size) != DP_OK) {
			Sleep(20);
			continue;
		}
		if (from != DPID_SYSMSG && size == 8 && !memcmp(buf, "welcome", 8))
			welcome = 1;
	}
	check(welcome, "client", "the host's answer arrived");
	DP_Close(dp);
	return fails;
}

int main(void)
{
	system("rm -rf /tmp/axdp && mkdir -p /tmp/axdp");
	FILE *f = fopen("/tmp/axdp/axisnet.ini", "w");
	fputs("[net]\nmode=local\nhubport=23810\nupnp=0\nlog=1\n", f);
	fclose(f);
	setenv("AXIS_SETTINGS", "/tmp/axdp/registry.txt", 1);
	if (chdir("/tmp/axdp") != 0)
		return 2;
	pid_t pid = fork();
	if (pid == 0)
		return host();
	int r = client(), status = 0;
	waitpid(pid, &status, 0);
	int hostFails = WIFEXITED(status) ? WEXITSTATUS(status) : 99;
	printf("---- axisnet.log:\n");
	fflush(stdout);
	system("cat /tmp/axdp/axisnet.log | cut -c1-140 | head -40");
	printf("%s: client %d failed, host %d failed\n", r || hostFails ? "FAILED" : "ALL PASSED", r, hostFails);
	return r || hostFails;
}
