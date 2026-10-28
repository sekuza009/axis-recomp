/* armc_misc.c: small pieces of the ARM CENTER screen: its per-mode draw passes, the 3D view's setup, the text
   helpers that follow the language, and re-making the player's actor. */
#include "../game.h"

#define g_armcPreview GAME_VAR(int, 0x4dbc68)         /* (by use) the mech preview is shown */
#define g_armcModeShown GAME_VAR(int, 0x4dc24c)       /* (unclear) 3: the part lists are left as they are */

/* 0x41dfb0: the parts page: the preview, the part lists (armc_40d990, a no-op in the patched game) and, unless the
   interface is hidden (Ctrl+Alt+M), the frame and the stats panel */
void (armc_41dfb0)(void)
{
	if (g_armcPreview != 0)
		armc_41d600();
	if (g_armcModeShown != 3)
		armc_40d990();
	if (g_armcHideInterface == 0) {
		armc_412450();
		armc_drawStatsPanel();
	}
}

/* 0x41dfe0: the colour page (its own preview) */
void (armc_41dfe0)(void)
{
	if (g_armcPreview != 0)
		armc_41d8a0();
	if (g_armcHideInterface == 0) {
		armc_412450();
		armc_419160();
	}
}

/* 0x41e010: the third page */
void (armc_41e010)(void)
{
	if (g_armcPreview != 0)
		armc_41d600();
	if (g_armcHideInterface == 0) {
		armc_412450();
		armc_41a280();
	}
}

/* 0x41b710: the 3D view: projection, white, textures on, the menu camera */
void (armc_41b710)(void)
{
	gfx_setProjection2D3D(1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	gfx_setMenuCamera();
}

/* 0x4125c0: text in the font that suits the language (language 2 uses the small 5-pixel font) */
void (armc_4125c0)(int x, int y, const char *text)
{
	if (g_language == 2)
		text_draw5(x, y, text);
	else
		text_draw8(x, y, text);
}

/* 0x4125f0: the same, right-aligned at x (6 or 8 pixels a character) */
void (armc_drawStatLabel)(int x, int y, const char *text)
{
	int n = 0;
	while (text[n] != '\0')
		n++;
	if (g_language == 2)
		text_draw5(x - n * 6, y, text);
	else
		text_draw8(x - n * 8, y, text);
}

/* 0x45ddc0 (thiscall on the stage): the player's actor made again in its own slot, at the start position */
void THISCALL (armc_45ddc0)(Stage *stage)
{
	struct { i32 slot, zero; u32 pos[3]; i32 zero2, zero3; } spawn;
	int slot = stage->playerActor;
	spawn.pos[0] = g_startPos[0];
	spawn.pos[1] = g_startPos[1];
	spawn.pos[2] = g_startPos[2];
	spawn.slot = slot;
	spawn.zero = 0;
	spawn.zero2 = 0;
	spawn.zero3 = 0;
	match_45dd80(stage, slot, -1, slot, &spawn);
}
