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

#define g_armcCamHeight GAME_VAR(float, 0x4df028)     /* the preview camera's height */
#define g_armcCamDistance GAME_VAR(float, 0x4df02c)   /* and distance (1600 at rest) */
#define g_armcFrom GAME_VAR(int, 0x4dc24c)            /* where the screen was entered from: 1, 2 the lobby, 3 the room */

/* 0x40f0f0: leaving the screen; confirmed: keep the mech (saved with the profile, or sent to the room's players
   when entered from the room). The front end's 3D background and camera are reset and the Netsphere music starts */
void (armc_exit)(int confirmed)
{
	switch (g_armcFrom) {
	case 1:
		armc_40e670();
		GAME_VAR(int, 0x4dc790) = 0;
		g_viewAspect = 0.1f;
		if (confirmed)
			armc_saveSelection();
		break;
	case 2:
		GAME_VAR(int, 0x4dc790) = 0;
		g_viewAspect = 0.1f;
		g_lobbySubState = 0;
		if (confirmed)
			armc_saveSelection();
		break;
	case 3:
		armc_40e670();
		GAME_VAR(int, 0x4dc790) = 0;
		g_viewAspect = 0.1f;
		if (confirmed)
			armc_sendSelectionToNet();
		break;
	}
	g_armcCamHeight = 0.0f;
	g_armcCamDistance = 1600.0f;
	GAME_VAR(int, 0x68037c) = 0;
	GAME_VAR(int, 0x680380) = 0;
	GAME_VAR(int, 0x4dcf10) = 1;
	g_flareSizeB = 10.0f;
	g_flareSizeA = 48.0f;
	g_flareStepB = 0.2f;
	g_flareStepA = -0.2f;
	sound_playMenu(4);
	music_play((const char *)0x4b01cc);                  /* "music/Netsphere.mp3", the game's own string */
	if (GAME_VAR(int, 0x76d410) == 1 && GAME_VAR(int, 0x9da49c) == 0x66)
		GAME_VAR(int, 0x9da49c) = 0x67;
}

/* v moved a tenth of the way to target per time unit */
static void approach(float *v, float target)
{
	*v = (float)(((long double)target - *v) * g_frameTime * 0.1f + *v);
}

/* 0x41b300: the preview camera eases towards the part being edited (on the parts and colour pages, by their part
   slot: head, chest, arm, leg, booster, weapons) or the weapons (on the weapons page) */
void (armc_41b300)(void)
{
	static const float height[6] = { 500.0f, 100.0f, -200.0f, -400.0f, -200.0f, 550.0f };
	static const float distance[6] = { 1300.0f, 1300.0f, 1500.0f, 1300.0f, 1500.0f, 1300.0f };
	int part;
	if (g_armcMode == 1)
		part = g_armcPartSlot;
	else if (g_armcMode == 3)
		part = g_armcColourSlot;
	else if (g_armcMode == 2)
		part = 5;
	else
		return;
	if ((unsigned)part > 5)
		return;
	approach(&g_armcCamHeight, height[part]);
	approach(&g_armcCamDistance, distance[part]);
}

/* 0x45dd80 (thiscall on the stage): actor slot a claimed (FUN_0045dc00) and made the player's, with weapon slot 0 */
void THISCALL (match_45dd80)(Stage *stage, int a, int x, int y, void *spawn)
{
	FUN_0045dc00(stage, a, x, y, spawn);
	stage->playerActor = a;
	FUN_0045e810(stage, a, 0);
}

/* 0x410160: a right click leaves the ARM CENTER's page, the menu camera put back */
void (armc_410160)(void)
{
	if (GAME_VAR(int, 0x4ded8c)) {
		armc_40e670();
		GAME_VAR(int, 0x4dc790) = 0;
		BITS(g_viewAspect) = 0;
	}
}
