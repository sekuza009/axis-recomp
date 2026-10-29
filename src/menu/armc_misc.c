/* armc_misc.c: small pieces of the ARM CENTER screen: its per-mode draw passes, the 3D view's setup, the text
   helpers that follow the language, and re-making the player's actor. */
#include "../game.h"
#include <string.h>

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

/* 0x40de80: the ARM CENTER camera box's corners (each +-700 or 0, as floats) */
void (armc_40de80)(void)
{
	static const struct { u8 offset; signed char sign; } corner[] = {
		{ 0x40, -1 }, { 0x44, 1 }, { 0x48, 1 }, { 0x50, 1 }, { 0x58, 1 }, { 0x60, 1 }, { 0x64, -1 }, { 0x68, 1 },
		{ 0x70, -1 }, { 0x74, -1 }, { 0x78, 1 }, { 0x80, -1 }, { 0x84, 1 }, { 0x88, -1 }, { 0x90, 1 }, { 0x94, 1 },
		{ 0x98, -1 }, { 0xa0, 1 }, { 0xa4, -1 }, { 0xa8, -1 }, { 0xb0, -1 }, { 0xb4, -1 }, { 0xb8, -1 },
		{ 0xc0, 0 }, { 0xc4, 0 }, { 0xc8, 0 }, { 0xd0, 0 }, { 0xd4, 0 } };
	for (unsigned k = 0; k < sizeof corner / sizeof corner[0]; k++)
		GAME_VAR(u32, 0x4dcf00 + corner[k].offset) = corner[k].sign > 0 ? 0x442f0000 : corner[k].sign < 0 ? 0xc42f0000 : 0;
}

/* 0x40dfa0: the six parts' bounding boxes (+-600, 0x58 bytes each from 0x4dc550), their offsets, and the camera's
   limits (200, 600, 2, -2) */
void (armc_40dfa0)(void)
{
	for (u32 p = 0x4dc554; p < 0x4dc764; p += 0x58) {
		static const signed char corner[] = { -1, -1, -1, 0, 1, -1, -1, 0, 1, -1, 1, 0, -1, -1, 1 };
		for (int k = 0; k < 15; k++)
			if (corner[k])
				GAME_VAR(u32, p - 4 + k * 4) = corner[k] > 0 ? 0x44160000 : 0xc4160000;
		GAME_VAR(int, p + 0x3c) = 0;
		GAME_VAR(int, p + 0x40) = 0;
		GAME_VAR(int, p + 0x44) = 0;
		GAME_VAR(int, p + 0x4c) = 0;
	}
	GAME_VAR(u32, 0x4dc5a4) = 0x3e19999a;   /* 0.15 */
	GAME_VAR(u32, 0x4dc5fc) = 0xbeb33333;   /* -0.35 */
	GAME_VAR(u32, 0x4dc654) = 0xbfc00000;   /* -1.5 */
	GAME_VAR(u32, 0x4dc6ac) = 0x3fc00000;   /* 1.5 */
	GAME_VAR(u32, 0x4dc704) = 0xbe3851ec;   /* -0.18 */
	GAME_VAR(u32, 0x4dc75c) = 0x3e3851ec;   /* 0.18 */
	GAME_VAR(u32, 0x4b0704) = 0x43480000;   /* 200 */
	GAME_VAR(u32, 0x4b0708) = 0x44160000;   /* 600 */
	GAME_VAR(u32, 0x4b070c) = 0x40000000;   /* 2 */
	GAME_VAR(u32, 0x4b0710) = 0xc0000000;   /* -2 */
}

/* 0x410190: the ARM CENTER's mouse, on pages 1 .. 4 (0x4dc798) in a state past 1 (0x4dc790) with no dialog open.
   Returns what the original leaves in eax (the value it stopped at, or the page's handler's) */
u32 (armc_onStateEnter)(void)
{
	int state = GAME_VAR(int, 0x4dc790);
	if (state == 1 || state == 0)
		return state;
	if (g_dialogOpen)
		return g_dialogOpen;
	u32 page = GAME_VAR(u32, 0x4dc798) - 1;
	switch (page) {
	case 0:
		return armc_40fb20();
	case 1:
		return armc_40fd30();
	case 2:
		return armc_colourScreenInput();
	case 3:
		return GAME_CDECL(0x410160, u32, void)();   /* armc_410160 (its eax) */
	}
	return page;
}

/* 0x419000: catalogue item i's snapshot texture ("Actor/item/<name>/snapshot"; the name 0x80 bytes a slot at
   0x4dbe50) loaded into 0x4dcc70[i]; nothing for a name shorter than 2 letters. 0x4dcc64 cleared either way */
void (armc_snapshot)(int i)
{
	const char *name = (const char *)(0x4dbe50 + i * 0x80);
	if (strlen(name) <= 1) {
		GAME_VAR(int, 0x4dcc64) = 0;
		return;
	}
	char path[0x80], copy[0x40];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)0x4b036c);   /* "Actor/item/" */
	strcat(path, name);
	strcat(path, (const char *)0x4ad564);   /* "/" */
	strcat(path, (const char *)0x4b0360);   /* "snapshot" */
	strcpy(copy, path);
	GAME_VAR(int, 0x4dcc70 + i * 4) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), copy, 0, 0, 0, 0, 0, 0, 0);
	GAME_VAR(int, 0x4dcc64) = 0;
}

/* 0x412450: the three mode tabs across the top (0x4dcc90 / 0x4dcc94, 100 apart): the tab texture (0x9db0a4), the
   chosen one (0x4dc798, 1 .. 3) brighter, then each tab's name (0x7565a4, 0x80 a slot) in its colour (0x4dbc58
   chosen, else 0x4dc1d0). Returns 3 (the original's eax) */
int (armc_412450)(void)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	for (int i = 0; i < 3; i++) {
		glColor4f(1.0f, 1.0f, 1.0f, GAME_VAR(int, 0x4dc798) == i + 1 ? 0.8f : 0.4f);
		int x = GAME_VAR(int, 0x4dcc90), y = GAME_VAR(int, 0x4dcc94);
		menu_drawTexQuad_4282f0(x + i * 100 + 0x10, y - 8, x + i * 100 + 0x70, y + 0x18, 1);
	}
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < 3; i++) {
		const u32 *c = (const u32 *)(GAME_VAR(int, 0x4dc798) == i + 1 ? 0x4dbc58 : 0x4dc1d0);
		set_colour_bits((Colour *)0x76d438, c[0], c[1], c[2], c[3]);
		int x = GAME_VAR(int, 0x4dcc90);
		text_drawBox16(x + i * 100 + 0x10, GAME_VAR(int, 0x4dcc94), x + i * 100 + 0x70, (const char *)(0x7565a4 + i * 0x80));
	}
	return 3;
}

/* 0x40e7a0: the selection kept: the part choices (0x90 bytes from 0x4dc4b8 into 0x4dcfe0), the five colour
   choices (0x4dc760 into 0x4dc878) and six more settings (0x4dcb18 into 0x4dcf18), between two calls of the part
   lists (armc_40d990); the original then checked the choices' ranges, which the patched game jumps over. Then the
   progress saved; returns profile_saveProgress's eax */
u32 (armc_saveSelection)(void)
{
	GAME_CDECL(0x40d990, void, void)();
	memcpy((void *)0x4dcfe0, (const void *)0x4dc4b8, 0x90);
	memcpy((void *)0x4dc878, (const void *)0x4dc760, 5 * 4);
	memcpy((void *)0x4dcf18, (const void *)0x4dcb18, 6 * 4);
	GAME_CDECL(0x40d990, void, void)();
	return GAME_CDECL(0x447010, u32, void)();   /* profile_saveProgress */
}
