/* posix_system_test.c: plat/posix/system.c checked on Linux (run in WSL by tools/plat_tests/run_posix.sh), called as
   the game calls them: through the "_plat_<name>" symbols, stdcall on 32-bit. */
#define AXIS_PORTABLE 1
#include "../../src/plat/posix/system.c"
#include <stdio.h>

static int fails;
static void check(int ok, const char *what)
{
	printf("%s  %s\n", ok ? "PASS" : "FAIL", what);
	if (!ok)
		fails++;
}
static char g_lastTitle[64], g_lastText[128], g_lastProgram[64], g_lastArgs[64];
static int host_message(void *user, const char *title, const char *text)
{
	(void)user;
	snprintf(g_lastTitle, sizeof g_lastTitle, "%s", title);
	snprintf(g_lastText, sizeof g_lastText, "%s", text);
	return 1;
}
static int host_launch(void *user, const char *program, const char *args)
{
	(void)user;
	snprintf(g_lastProgram, sizeof g_lastProgram, "%s", program);
	snprintf(g_lastArgs, sizeof g_lastArgs, "%s", args);
	return !strcmp(program, "AxisGL.exe");
}

/* the game's view of them: the symbols by name, its calling convention */
extern int WINAPI game_MessageBoxA(void *, const char *, const char *, uint32_t) __asm__("_plat_MessageBoxA");
extern void *WINAPI game_ShellExecuteA(void *, const char *, const char *, const char *, const char *, int) __asm__("_plat_ShellExecuteA");
extern int WINAPI game_GetSystemMetrics(int) __asm__("_plat_GetSystemMetrics");
extern int WINAPI game_GetDeviceCaps(void *, int) __asm__("_plat_GetDeviceCaps");
extern uint16_t WINAPI game_GetSystemDefaultLangID(void) __asm__("_plat_GetSystemDefaultLangID");
extern uint32_t WINAPI game_GetVersion(void) __asm__("_plat_GetVersion");
extern int WINAPI game_MultiByteToWideChar(uint32_t, uint32_t, const char *, int, uint16_t *, int) __asm__("_plat_MultiByteToWideChar");
extern int WINAPI game_ShowCursor(int) __asm__("_plat_ShowCursor");

int main(void)
{
	check(game_MessageBoxA(NULL, "text", "title", 0) == 1, "MessageBoxA without a host: printed, IDOK");
	g_platHostMessage = host_message;
	g_platHostLaunch = host_launch;
	check(game_MessageBoxA(NULL, "Cannot find Server list.", "Warning", 0) == 1 && !strcmp(g_lastTitle, "Warning") &&
	      !strcmp(g_lastText, "Cannot find Server list."), "MessageBoxA with a host: the host's box (title, text)");
	check((uintptr_t)game_ShellExecuteA(NULL, "open", "AxisGL.exe", NULL, NULL, 10) == 42 && !strcmp(g_lastProgram, "AxisGL.exe"),
	      "ShellExecuteA(AxisGL.exe): the host restarts the game, 42 (done)");
	check((uintptr_t)game_ShellExecuteA(NULL, "open", "axispatch.exe", "nstower", NULL, 10) == 2 && !strcmp(g_lastArgs, "nstower"),
	      "ShellExecuteA(axispatch.exe nstower): the host declines, 2");
	g_platScreenW = 2560;
	g_platScreenH = 1440;
	check(game_GetSystemMetrics(0) == 2560 && game_GetSystemMetrics(1) == 1440, "GetSystemMetrics: the host's screen 2560x1440");
	check(game_GetDeviceCaps(NULL, 8) == 2560 && game_GetDeviceCaps(NULL, 10) == 1440 && game_GetDeviceCaps(NULL, 12) == 32,
	      "GetDeviceCaps: HORZRES, VERTRES, 32 bits");
	unsetenv("LC_ALL");   /* (a machine's own settings, which come first, out of the way) */
	unsetenv("LC_MESSAGES");
	setenv("LANG", "ko_KR.UTF-8", 1);
	check(game_GetSystemDefaultLangID() == 0x412, "LANG=ko_KR.UTF-8: Korean (0x412)");
	setenv("LANG", "en_GB.UTF-8", 1);
	check(game_GetSystemDefaultLangID() == 0x409, "LANG=en_GB.UTF-8: English (0x409)");
	setenv("LC_ALL", "ko_KR", 1);
	check(game_GetSystemDefaultLangID() == 0x412, "LC_ALL=ko_KR over LANG: Korean");
	check(game_GetVersion() == 0x23f00206 && game_GetVersion() < 0x80000000, "GetVersion: 6.2 build 9200 (NT), as Windows gives the game");
	uint16_t w[16];
	check(game_MultiByteToWideChar(0, 0, "music/a.mp3", -1, w, 16) == 12 && w[0] == 'm' && w[11] == 0,
	      "MultiByteToWideChar(music/a.mp3): 12 wide characters with the end");
	check(game_ShowCursor(0) == -1 && game_ShowCursor(1) == 0, "ShowCursor counts as Windows' does");
	printf("%s: %d failed\n", fails ? "FAILED" : "ALL PASSED", fails);
	return fails != 0;
}
