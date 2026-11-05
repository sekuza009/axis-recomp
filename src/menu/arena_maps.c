/* arena_maps.c: the arena's map list: per map whether it is in the rotation and its game type (0 .. 13), edited on
   a working copy (g_mapChoices) and kept on OK (g_mapChoicesKept). Maps 22 .. 24 can never be chosen. */
#include "../game.h"
#include <string.h>

#define g_mapChoices ((MapChoice *)g_mapChoiceTable)          /* (objects.h: 1024 of them) */
#define g_mapChoicesKept ((MapChoice *)g_mapChoiceKeptTable)

/* the maps that are never offered */
static void clear_unused(void)
{
	g_mapChoices[22].chosen = 0;
	g_mapChoices[23].chosen = 0;
	g_mapChoices[24].chosen = 0;
}

/* 0x403490: start editing from the kept list */
void (mapList_startEdit)(void)
{
	int n = g_arenaMapCount;
	for (int i = 0; i < n; i++) {
		g_mapChoices[i].chosen = g_mapChoicesKept[i].chosen;
		g_mapChoices[i].type = g_mapChoicesKept[i].type;
	}
	clear_unused();
	g_mapListOpen = 1;
}

/* 0x4034e0: choose every map */
void (mapList_chooseAll)(void)
{
	sound_playMenu(0);
	for (int i = 0; i < g_arenaMapCount; i++)
		g_mapChoices[i].chosen = 1;
	clear_unused();
}

/* 0x403530: choose none (types back to 0) */
void (mapList_chooseNone)(void)
{
	sound_playMenu(0);
	for (int i = 0; i < g_arenaMapCount; i++) {
		g_mapChoices[i].chosen = 0;
		g_mapChoices[i].type = 0;
	}
}

/* 0x403560: map i in or out */
void (mapList_toggle)(int i)
{
	g_mapChoices[i].chosen = 1 - g_mapChoices[i].chosen;
	if (i >= 22 && i <= 24)
		g_mapChoices[i].chosen = 0;
}

/* 0x403590: map i's game type one on (0 .. 13, round), or one back while a Shift or Ctrl key is held */
void (mapList_stepGameType)(int i)
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
void (mapList_ok)(void)
{
	int i = 0;
	if (g_arenaMapCount <= 0)
		return;
	while (g_mapChoices[i].chosen != 1)
		if (++i >= g_arenaMapCount)
			return;
	sound_playMenu(0);
	clear_unused();
	for (i = 0; i < g_arenaMapCount; i++) {
		g_mapChoicesKept[i].chosen = g_mapChoices[i].chosen;
		g_mapChoicesKept[i].type = g_mapChoices[i].type;
	}
	g_mapListOpen = 0;
	g_mapListKept = 1;
}

/* 0x4050a0: the lobby player's name, sex and corporation kept as axis.cfg's (g_cfgPlayerName ..) and the configuration written */
void (arena_savePlayerSettings)(void)
{
	g_playerSex = g_arenaSex;
	const char *name = g_arenaPlayerName;
	char *kept = g_cfgPlayerName;
	int i = 0;
	do
		kept[i] = name[i];
	while (name[i++] != '\0');
	g_playerCorporation = g_arenaCorporation;
	cfg_writeAxisCfg();
}

/* a map choice moved one on (dir > 0) or back, round the g_arenaMapCount maps, skipping 22 .. 24; nothing while the
   lock byte is set; the change flagged (0x680cd0) */
static void map_step(int dir, u32 lock, u32 choice)
{
	signed char *c = (signed char *)RELOC(choice);
	if (*(char *)RELOC(lock))
		return;
	if (dir > 0) {
		if (++*c == 0x16)
			*c = 0x19;
		if (*c >= g_arenaMapCount)
			*c = 0;
	} else {
		if (--*c < 0)
			*c = (signed char)((*(char *)&g_arenaMapCount) - 1);
		if (*c == 0x18)
			*c = 0x15;
	}
	g_mapPreviewChanged = 1;
}

/* 0x4068d0, 0x4356f0: the arena's and the room's map choice */
void (arena_stepMap)(int dir) { map_step(dir, ADDR(g_newArenaKind), ADDR(g_newArenaMap)); }
void (room_stepMap)(int dir) { map_step(dir, ADDR(g_roomCustom), ADDR(g_roomMap)); }

/* ---- the map list's drawing ---- */
#define cyan_text(a) set_colour_bits(g_textColour, 0, 0x3f800000, 0x3f800000, a)

/* a map's cell from x0 to x1 in the row at y: on a red bar (yellow text) when the map is chosen */
static void map_cell(int map, int x0, int x1, int y)
{
	if (g_mapChoices[map].chosen) {
		set_colour_bits(g_rectColour, 0x3f800000, 0, 0x3f000000, 0x3f000000);   /* 1, 0, 0.5, 0.5 */
		menu_drawRect(x0, y, x1, y + 0x14, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	} else
		cyan_text(0x3f4ccccd);
}

/* a row of two buttons at y (labels 0x80 apart from label), lit while the pointer (hovered) is on first + k */
static void map_buttons(int hovered, int first, int y, int label)
{
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		int texture = g_buttonTexture;
		tex_bind(g_textures->banks[texture / 512], texture % 512);
		int x = 0xaa + k * 0xa0;
		if (hovered == first + k) {
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
		} else {
			glColor4f(1.0f, 1.0f, 1.0f, 0.4f);
			set_colour_bits(g_textColour, 0x3e99999a, 0x3f333333, 0x3f333333, 0x3f800000);   /* 0.3, 0.7, 0.7, 1 */
		}
		menu_drawWideButton(x, y, x + 0x8c, y + 0x20, 1);
		text_drawBox16(x, y + 8, x + 0x8c, (const char *)(RELOC(label) + k * 0x80));
	}
}

/* 0x4038e0: the map list over a dimmed screen: two column heads (0x75d924, 0x75d9a4), up to 10 rows from g_mapTop
   (22 .. 24 left out): the number, the name (0x907b30, 0x20 apart) and the game type's name (0x4db8d8, 20 apart),
   the row under the pointer (by mapList_hitTest) highlighted; the scroll arrows (0x14 / 0x15) and two rows of buttons
   (MSG(506, "$[0] DEFAULT") from 0x16, MSG(504, "$[0] O K") from 0x18). The original leaves eax to callers that ignore it */
void (mapList_draw)(void)
{
	int hovered = mapList_hitTest(g_mouseX, g_mouseY);
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3e99999a);   /* 0.3 */
	menu_drawRect(0, 0, 0x280, 0x1e0, 1);
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3f333333);   /* 0.7 */
	menu_drawRect(0x8c, 0x28, 0x1f4, 0x1b8, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f4ccccd);
	menu_drawRect(0x90, 0x2c, 0x1f0, 0x1b4, 0);
	cyan_text(0x3f800000);
	text_draw8(0xc8, 0x32, (const char *)MSG(502, "MAP"));
	cyan_text(0x3f800000);
	text_draw8(0x168, 0x32, (const char *)MSG(503, "TYPE"));
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f4ccccd);
	menu_drawLine(0x96, 0x4b, 0x1ea, 0x4b);
	for (int i = 0; i < g_arenaMapCount && i < 10; i++) {
		int y = 0x57 + i * 0x18;
		if (hovered == i) {
			set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f4ccccd, 0x3ecccccd);   /* 0.1, 0.2, 0.8, 0.4 */
			menu_drawRect(0x96, y, 0x1a4, y + 0x14, 1);
		}
		int map = g_mapTop + i;
		if (map >= 22 && map <= 24)
			continue;
		char number[20] = { 0 };
		itoa(map + 1, number, 10);
		map_cell(g_mapTop + i, 0x96, 0x154, y);
		text_draw8(0xb4 - (int)strlen(number) * 8, y + 3, number);
		text_draw8(0xbe, y + 3, (const char *)(OBJ(g_mapNames) + (g_mapTop + i) * 0x20));
		map_cell(g_mapTop + i, 0x168, 0x1a4, y);
		text_draw8(0x17c, y + 3, (const char *)(OBJ(g_gameTypeNames) + g_mapChoices[g_mapTop + i].type * 20));
	}
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f4ccccd);
	menu_drawLine(0x96, 0x14f, 0x1ea, 0x14f);
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton3(0x1c2, 0x96, 0x1e0, 0xca, hovered == 0x14);
	menu_drawSmallButton4(0x1c2, 0xdc, 0x1e0, 0x110, hovered != 0x14 && hovered == 0x15);
	map_buttons(hovered, 0x16, 0x15e, MSG(506, "$[0] DEFAULT"));
	map_buttons(hovered, 0x18, 0x186, MSG(504, "$[0] O K"));
}
#undef cyan_text

/* 0x4036c0: the map list's mouse: a click (the blink clock restarted) on a row's map (0 .. 9) or game type (10 ..
   19), the arrows (20 / 21: one row up / down), none, every map, OK, or close (25); in mode 2 (0x4dbb3c) holding an
   arrow scrolls once the clock reaches 5 (0x4a93d0), restarting it. The original leaves eax to callers that ignore
   it */
void (mapList_mouse)(void)
{
	const float *repeat = (const float *)ADDR(k_5f);
	if (g_mouseClick) {
		g_cursorBlink = 0.0f;
		int on = mapList_hitTest(g_mouseX, g_mouseY);
		if (on >= 0 && on < 10)
			mapList_toggle(g_mapTop + on);
		else if (on >= 10 && on < 20)
			mapList_stepGameType(g_mapTop + on - 10);
		else if (on == 20) {
			sound_playMenu(2);
			if (g_mapTop > 0)
				g_mapTop--;
		} else if (on == 21) {
			sound_playMenu(2);
			if (g_mapTop + 10 < g_arenaMapCount)
				g_mapTop++;
		} else if (on == 22)
			mapList_chooseNone();
		else if (on == 23)
			mapList_chooseAll();
		else if (on == 24)
			mapList_ok();
		else if (on == 25) {
			sound_playMenu(0);
			g_mapListOpen = 0;
		}
	}
	if (!g_mouseHeld || g_arenaLobbyMode != 2)
		return;
	int on = mapList_hitTest(g_mouseX, g_mouseY);
	if (on == 20 && g_cursorBlink >= *repeat) {
		if (g_mapTop > 0)
			g_mapTop--;
		g_cursorBlink = 0.0f;
	} else if (on == 21 && g_cursorBlink >= *repeat) {
		if (g_mapTop + 10 < g_arenaMapCount) {
			g_cursorBlink = 0.0f;
			g_mapTop++;
		} else
			g_cursorBlink = 0.0f;
	}
}
