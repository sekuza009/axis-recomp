/* arena_maps.c: the arena's map list: per map whether it is in the rotation and its game type (0 .. 13), edited on
   a working copy (g_mapChoices) and kept on OK (g_mapChoicesKept). Maps 22 .. 24 can never be chosen. */
#include "../game.h"

typedef struct { i32 chosen; i32 type; } MapChoice;
#define g_mapCount GAME_VAR(int, 0x67ef00)
#define g_mapChoices ((MapChoice *)0x4d7358)
#define g_mapChoicesKept ((MapChoice *)0x4d9508)
#define g_mapListOpen GAME_VAR(int, 0x4db508)         /* (by use) 1 while the list is being edited */
#define g_mapListKept GAME_VAR(int, 0x4d94fc)         /* (by use) set once a list has been kept */

/* the maps that are never offered */
static void clear_unused(void)
{
	g_mapChoices[22].chosen = 0;
	g_mapChoices[23].chosen = 0;
	g_mapChoices[24].chosen = 0;
}

/* 0x403490: start editing from the kept list */
void (room_403490)(void)
{
	int n = g_mapCount;
	for (int i = 0; i < n; i++) {
		g_mapChoices[i].chosen = g_mapChoicesKept[i].chosen;
		g_mapChoices[i].type = g_mapChoicesKept[i].type;
	}
	clear_unused();
	g_mapListOpen = 1;
}

/* 0x4034e0: choose every map */
void (room_4034e0)(void)
{
	sound_playMenu(0);
	for (int i = 0; i < g_mapCount; i++)
		g_mapChoices[i].chosen = 1;
	clear_unused();
}

/* 0x403530: choose none (types back to 0) */
void (room_403530)(void)
{
	sound_playMenu(0);
	for (int i = 0; i < g_mapCount; i++) {
		g_mapChoices[i].chosen = 0;
		g_mapChoices[i].type = 0;
	}
}

/* 0x403560: map i in or out */
void (room_403560)(int i)
{
	g_mapChoices[i].chosen = 1 - g_mapChoices[i].chosen;
	if (i >= 22 && i <= 24)
		g_mapChoices[i].chosen = 0;
}

/* 0x403590: map i's game type one on (0 .. 13, round), or one back while a Shift or Ctrl key is held */
void (room_403590)(int i)
{
	if (input_isDown(g_keyLeftShift) || input_isDown(g_keyRightShift) || input_isDown(g_keyLeftCtrl)
	    || input_isDown(g_keyRightCtrl)) {
		if (--g_mapChoices[i].type < 0)
			g_mapChoices[i].type = 13;
	} else {
		if (++g_mapChoices[i].type > 13)
			g_mapChoices[i].type = 0;
	}
	if (i >= 22 && i <= 24)
		g_mapChoices[i].type = 0;
}

/* 0x403640: OK: keep the list, if at least one map is chosen (otherwise nothing happens) */
void (room_403640)(void)
{
	int i = 0;
	if (g_mapCount <= 0)
		return;
	while (g_mapChoices[i].chosen != 1)
		if (++i >= g_mapCount)
			return;
	sound_playMenu(0);
	clear_unused();
	for (i = 0; i < g_mapCount; i++) {
		g_mapChoicesKept[i].chosen = g_mapChoices[i].chosen;
		g_mapChoicesKept[i].type = g_mapChoices[i].type;
	}
	g_mapListOpen = 0;
	g_mapListKept = 1;
}

/* 0x4050a0 (FUN_004050a0): the arena's name and two settings kept (0x4dedb0 ..) and the configuration written */
void (FUN_004050a0)(void)
{
	GAME_VAR(int, 0x4dedd4) = GAME_VAR(int, 0x4db584);
	const char *name = (const char *)0x4db560;
	char *kept = (char *)0x4dedb0;
	int i = 0;
	do
		kept[i] = name[i];
	while (name[i++] != '\0');
	GAME_VAR(int, 0x4dedd0) = GAME_VAR(int, 0x4db580);
	cfg_loadAxisCfg();
}
