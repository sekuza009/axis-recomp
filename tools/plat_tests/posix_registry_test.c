/* posix_registry_test.c: plat/posix/registry.c checked on Linux (run in WSL by tools/plat_tests/run_posix.sh), with
   the game's own sequences (src/app/small.c): the first start (Character created), a restart (read back), the
   launcher's modes and the server list missing, as on a system without the launcher. */
#define AXIS_PORTABLE 1
#include "../../src/plat/posix/registry.c"
#include <stdio.h>

static int fails;
static void check(int ok, const char *what)
{
	printf("%s  %s\n", ok ? "PASS" : "FAIL", what);
	if (!ok)
		fails++;
}
static void restart(void)   /* (the game started again: only the file remains) */
{
	for (int i = 0; i < g_keyCount; i++) {
		for (int j = 0; j < g_keys[i].count; j++)
			free(g_keys[i].values[j].data);
		free(g_keys[i].values);
	}
	free(g_keys);
	g_keys = NULL;
	g_keyCount = g_loaded = 0;
	memset(g_open, 0, sizeof g_open);
}

#define HKCU 0x80000001u
#define CHARACTER "SOFTWARE\\AxisArena\\Character"

int main(void)
{
	system("rm -rf /tmp/axreg");
	setenv("AXIS_SETTINGS", "/tmp/axreg/sub/registry.txt", 1);
	uint32_t key = 0xdeadbeef, disp = 77, type = 0, size, value;
	char name[0x1e] = "AxisPlayer", game[0x20] = "Axis Ladder Game", buf[0x400];

	/* reg_readServerSettings without the key (no launcher wrote it) */
	check(plat_regOpen(HKCU, "SOFTWARE\\AxisArena\\SelectServer", &key) == 2 && key == 0xdeadbeef,
	      "open a missing key: 2, *key left as it was");
	check(plat_regClose(key) == 6, "close that unset handle: 6 (the game closes it anyway)");

	/* reg_readLadderSettings, first start: the key made, the defaults written */
	check(plat_regCreate(HKCU, CHARACTER, &key, &disp) == 0 && disp == 1, "create Character: new (1)");
	check(plat_regSet(key, "Name", 1, name, 0x1e) == 0, "set Name, REG_SZ of 0x1e bytes (padding included)");
	plat_regSet(key, "GameName", 1, game, 0x20);
	const char *choices[6] = { "Map", "PlayerNum", "FlagLimit", "TimeLimit", "Customize", "GameType" };
	uint32_t defaults[6] = { 0, 8, 10, 10, 0, 0 };
	for (int i = 0; i < 6; i++)
		plat_regSet(key, choices[i], 4, &defaults[i], 4);
	check(plat_regClose(key) == 0, "close: 0");

	restart();
	check(plat_regCreate(HKCU, CHARACTER, &key, &disp) == 0 && disp == 2, "after a restart: create Character finds it (2)");
	memset(buf, 0x55, sizeof buf);
	size = 0x1e;
	check(plat_regQuery(key, "Name", &type, buf, &size) == 0 && type == 1 && size == 0x1e && !memcmp(buf, name, 0x1e),
	      "read Name back: type 1, 0x1e bytes, as written");
	size = 4;
	check(plat_regQuery(key, "name", &type, buf, &size) == 234 && size == 0x1e, "read it into 4 bytes: 234, size 0x1e given back");
	size = 4;
	check(plat_regQuery(key, "TimeLimit", &type, &value, &size) == 0 && type == 4 && value == 10, "read TimeLimit: DWORD 10");
	size = 4;
	check(plat_regQuery(key, "Nope", &type, &value, &size) == 2, "read a missing value: 2");
	value = 21;
	plat_regSet(key, "MAP", 4, &value, 4);   /* (another case: the same value) */
	size = 4;
	check(plat_regQuery(key, "map", &type, &value, &size) == 0 && value == 21, "set MAP, read map: 21 (names without regard to case)");
	plat_regClose(key);
	check(plat_regOpen(HKCU, "software\\AXISARENA\\character", &key) == 0, "open software\\AXISARENA\\character: found");
	plat_regClose(key);

	/* reg_write (StartMode / EndMode) under Launcher, which only the launcher creates */
	key = 0x1234;
	check(plat_regOpen(HKCU, "SOFTWARE\\AxisArena\\Launcher", &key) == 2 && key == 0x1234, "open Launcher (none here): 2");

	restart();
	FILE *f = fopen("/tmp/axreg/sub/registry.txt", "r");
	check(f != NULL, "the settings file is at $AXIS_SETTINGS (folders made)");
	if (f) {
		char line[512];
		printf("      ---- the file:\n");
		while (fgets(line, sizeof line, f))
			printf("      %s", line);
		fclose(f);
	}
	check(plat_regOpen(HKCU, CHARACTER, &key) == 0, "after another restart: Character opens");
	size = 4;
	check(plat_regQuery(key, "Map", &type, &value, &size) == 0 && value == 21, "  and Map is still 21");

	printf("%s: %d failed\n", fails ? "FAILED" : "ALL PASSED", fails);
	return fails != 0;
}
