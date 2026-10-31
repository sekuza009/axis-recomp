/* armc_misc.c: small pieces of the ARM CENTER screen: its per-mode draw passes, the 3D view's setup, the text
   helpers that follow the language, and re-making the player's actor. */
#include "../game.h"
#include <string.h>

#define g_armcPreview GAME_VAR(int, 0x4dbc68)         /* (by use) the mech preview is shown */
#define g_armcModeShown GAME_VAR(int, 0x4dc24c)       /* (unclear) 3: the part lists are left as they are */
#define g_armcAngle GAME_VAR(float, 0x4dbc04)          /* the preview's turn */
#define g_armcSpin GAME_VAR(int, 0x4dceac)
#define g_armcState GAME_VAR(int, 0x4dc790)           /* (by use) 0 / 1: the screen is not up; 2: the preview camera is kept */
#define g_armcSessionDue GAME_VAR(int, 0x4dc86c)      /* (by use) the "please wait" box was shown: the session is made next */
#define g_armcSessionMade GAME_VAR(int, 0x4dc54c)
#define g_armcZoom GAME_VAR(float, 0x4dcfd8)          /* (by use) 1 when the part in view changes; each frame lowers it until it is below a limit, then -2 */

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
	stage_claimPlayerActor(stage, slot, -1, slot, &spawn);
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

/* ---- the mech preview of the parts and colour pages: a perspective view turned by the preview's angle (spinning
   while 0x4dceac is set), the mech posed by armc_rotateFromCursor for the part in view ---- */
#define g_armcEye ((const u32 *)0xa0e7a8)              /* (by use) the preview camera's position */

static void preview(int posed, int part)   /* posed: the mech posed for part */
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_viewAngle, g_viewAspect, 100.0, 20000.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	float turn = f32(fmul_m(fld_m(&g_armcAngle), (const float *)0x4a93ec));
	gl_rotateXYZ(0, BITS(turn), 0);
	u32 eye[3] = { g_armcEye[0], g_armcEye[1], g_armcEye[2] };
	u32 forward[3] = { 0, 0, 0xbf800000 }, up[3] = { 0, 0x3f800000, 0 };   /* (0, 0, -1), (0, 1, 0), on the stack as the original's */
	if (posed)
		armc_rotateFromCursor(g_scene, eye, forward, up, part, ftol(g_armcAngle), g_screenW, g_screenH);
	if (g_armcSpin) {
		long double angle = fadd_m(fmul_m(fld_m(&g_frameTime), (const float *)0x4a94cc), &g_armcAngle);
		g_armcAngle = angle;
		if (angle >= GAME_VAR(float, 0x4a94c8))
			BITS(g_armcAngle) = 0;
	}
}

/* the part a page's preview poses: on the parts page the part slot in view (none: -1 for the weapons, 5) */
static int part_in_view(void)
{
	return g_armcPartSlot == 5 ? -1 : g_armcPartSlot;
}

/* 0x41d600: the parts page's preview: a part changed (0x4dcc58) is put on the preview mech first (the item slots
   too), a pending colour change (0x4dca98) applied */
void (armc_41d600)(void)
{
	gfx_setProjection2D3D(1);
	if (GAME_VAR(int, 0x4dcc58) == 1) {
		const int *parts = (const int *)0x4dc760;    /* the mech's head, chest, arm, leg, booster */
		switch (g_armcPartSlot) {
		case 0: armc_setHeadIndex(g_scene, parts[0]); break;
		case 1: armc_setChestIndex(g_scene, parts[1]); break;
		case 2: armc_setArmIndex(g_scene, parts[2]); break;
		case 3: armc_setLegIndex(g_scene, parts[3]); break;
		case 4: armc_setBoosterIndex(g_scene, parts[4]); break;
		}
		armc_41b750();
		armc_461540(g_scene, GAME_VAR(int, 0x4dbe48));
		armc_41c510();
		GAME_VAR(int, 0x4dcc58) = 0;
		armc_41d280();
	}
	if (GAME_VAR(int, 0x4dbc80) == 1)
		GAME_VAR(int, 0x4dbc80) = 0;
	if (GAME_VAR(int, 0x4dca98)) {
		armc_41cf20();
		GAME_VAR(int, 0x4dca98) = 0;
	}
	switch (g_armcMode) {
	case 1: preview(1, part_in_view()); break;
	case 2: case 3: preview(1, -1); break;
	default: preview(0, 0); break;
	}
}

/* 0x41d8a0: the colour page's preview: item slot 0 emptied first when asked (0x4dbc80). The second page poses the
   item slot being picked (slots 4 / 5 as 6 / 7, the weapon slots as 5; none when that slot's record is empty) */
void (armc_41d8a0)(void)
{
	gfx_setProjection2D3D(1);
	if (GAME_VAR(int, 0x4dbc80) == 1) {
		armc_41ca50(0, 0);
		GAME_VAR(int, 0x4dbc80) = 0;
	}
	int slot;
	switch (g_armcMode) {
	case 1: preview(1, part_in_view()); break;
	case 2:
		slot = GAME_VAR(int, 0x4dbe48);
		if (GAME_VAR(int, 0x4dbe90 + slot * 0x80) == -1)
			preview(1, -1);
		else
			preview(1, slot > 3 ? slot + 2 : 5);
		break;
	case 3: preview(1, -1); break;
	default: preview(0, 0); break;
	}
}


/* 0x41e040: the ARM CENTER's frame: the menus' background (unless entered from the lobby), the entry state, then,
   while the screen is up: only the dialog's frame while one is open; the session made (and the six item slots
   filled) once the "please wait" box has been shown; the preview camera; the page; the box while there is neither a
   preview nor a session. The original leaves eax to callers that ignore it */
void (menuState700_armCenter)(void)
{
	if (GAME_VAR(int, 0x4dc868) && g_armcFrom != 2)
		menu_drawBackground();
	if (g_armcState != 2) {
		if (g_armcFrom == 3)
			armc_411ab0();
		if (g_armcFrom == 1)
			armc_411110();
	}
	arena_launchFromFile();
	int state = g_armcState;
	if (state == 1 || state == 0)
		return;
	if (g_dialogOpen) {
		menu_drawFrame(GAME_VAR(int, 0x4dcc90), GAME_VAR(int, 0x4dcc94), GAME_VAR(int, 0x4dcc98), GAME_VAR(int, 0x4dcc9c));
		return;
	}
	if (g_armcSessionDue && !g_armcSessionMade) {
		static const u32 items[6] = { 0x4dcb20, 0x4dcb24, 0x4dcb28, 0x4dcb2c, 0x4dcb18, 0x4dcb1c };
		armc_40e5d0();
		for (int slot = 0; slot < 6; slot++)
			armc_41ca50(slot, GAME_VAR(int, items[slot]));
		state = g_armcState;
	}
	if (state == 2 && !GAME_VAR(int, 0x4dcf10)) {
		armc_41b300();
		armc_41b710();
		armc_41b400();
	}
	armc_41dcf0();
	switch (g_armcMode) {
	case 1: armc_41dfb0(); break;
	case 2: armc_41dfe0(); break;
	case 3: armc_41e010(); break;
	}
	int box = 1;
	if (g_armcPreview) {
		armc_41dab0();
		box = !g_armcPreview;
	}
	if (box && !g_armcSessionMade) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(100, 200, 540, 280, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);   /* yellow */
		text_drawBox16(105, 220, 535, (const char *)0x7572a4);
		text_drawBox16(105, 244, 535, (const char *)0x757324);
		g_armcSessionDue = 1;
	}
	long double zoom = fsubr_m(fmul_m(fld_m(&g_frameTime), (const float *)0x4a93ec), &g_armcZoom);
	g_armcZoom = zoom;
	if (!(zoom >= GAME_VAR(float, 0x4a94a8)))
		g_armcZoom = -2.0f;
}

#define g_menuEye ((u32 *)0x4df024)                   /* the menu camera: its position (g_armcCamHeight, g_armcCamDistance) */
#define g_menuAt ((u32 *)0x680378)                    /* and the point it looks at */

/* 0x40ee20: entering the ARM CENTER: its music, the parts page with nothing picked, the camera put in front of the
   mech (further back from the room), the dialog box and two colours, the camera's point for the screen, the part
   lists built and the mech read (from the room's session or the profile), a sound; 0x4dcf34 set when the money
   (0x9dd5d8 from the room, 0x9f181c otherwise) went up since last time, the new amount kept and returned */
u32 (menu_enterMenus)(void)
{
	g_armcHideInterface = 0;
	GAME_VAR(int, 0x4dbe48) = 0;
	armc_initCameraPoints();
	music_play((const char *)0x4b01b0);
	g_armcPartSlot = 5;
	GAME_VAR(int, 0x4dce38) = 5;
	g_armcColourSlot = 5;
	int fromRoom = g_armcFrom == 3;
	g_armcMode = 1;
	GAME_VAR(int, 0x4dc788) = 0;
	g_menuEye[0] = 0;
	g_menuEye[1] = 0;
	u32 distance = fromRoom ? GAME_VAR(u32, 0x4a9458) : GAME_VAR(u32, 0x4a9454);   /* -1550, -450 */
	g_menuAt[0] = 0;
	g_menuAt[1] = 0;
	g_menuEye[2] = distance;
	g_menuAt[2] = fromRoom ? 0xc4ce4000 : 0xc4098000;                                /* -1650, -550 */
	GAME_VAR(int, 0x4dcc90) = 10;
	GAME_VAR(int, 0x4dcc94) = 10;
	GAME_VAR(int, 0x4dcc98) = 0x276;
	GAME_VAR(int, 0x4dcc9c) = 0x1d6;
	static const u32 colourA[4] = { 0, 0x3f800000, 0x3f800000, 0x3f800000 }, colourB[4] = { 0, 0x3f19999a, 0x3f19999a, 0x3f800000 };
	for (int i = 0; i < 4; i++) {
		GAME_VAR(u32, 0x4dbc58 + i * 4) = colourA[i];
		GAME_VAR(u32, 0x4dc1d0 + i * 4) = colourB[i];
	}
	GAME_VAR(int, 0x4dcf34) = 0;
	u32 *point = (u32 *)0x4df870, *pointAt = (u32 *)0x76d388;   /* the ARM CENTER's camera point */
	point[0] = 0;
	point[1] = 0;
	pointAt[0] = 0;
	pointAt[1] = 0;
	if (fromRoom) {
		point[2] = 0xc47a0000;    /* -1000 */
		pointAt[2] = 0xc4898000;  /* -1100 */
		if (GAME_VAR(int, 0x9dd5d8) > GAME_VAR(int, 0x4dc4b4))
			GAME_VAR(int, 0x4dcf34) = 1;
	} else {
		point[2] = 0x42c80000;    /* 100 */
		pointAt[2] = 0;
		if (GAME_VAR(int, 0x9f181c) > GAME_VAR(int, 0x4dc1e0))
			GAME_VAR(int, 0x4dcf34) = 1;
	}
	u32 *home = (u32 *)0x9db090, *homeAt = (u32 *)0x76d3f8;
	home[2] = distance;
	home[0] = 0;
	home[1] = 0;
	homeAt[0] = 0;
	homeAt[1] = 0;
	homeAt[2] = g_menuAt[2];
	g_armcState = 1;
	g_screen = 700;
	g_lastScreen = 700;
	g_nextScreen = 700;
	armc_40e060();
	armc_40e1c0();
	armc_40e300();
	armc_buildPartLists();
	GAME_VAR(int, 0x4dc868) = 1;
	g_armcSpin = 1;
	GAME_VAR(int, 0x4dcc58) = 1;
	g_armcPreview = 0;
	g_armcSessionDue = 0;
	g_armcSessionMade = 0;
	GAME_VAR(int, 0x4dcf10) = 0;
	GAME_VAR(int, 0x4dbc00) = 0;
	BITS(g_armcAngle) = 0;
	g_armcZoom = 1.0f;
	if (g_armcFrom == 3)
		mech_unpackFromRecord();
	else
		mech_loadFromProfile();
	armc_loadSavedMech();
	armc_40de80();
	armc_40dfa0();
	armc_40ed20();
	sound_playMenu(4);
	if (g_armcFrom == 3) {
		int money = GAME_VAR(int, 0x9dd5d8);
		if (money > GAME_VAR(int, 0x4dc4b4))
			GAME_VAR(int, 0x4dc4b4) = money;
		return money;
	}
	int money = GAME_VAR(int, 0x9f181c);
	if (money > GAME_VAR(int, 0x4dc1e0))
		GAME_VAR(int, 0x4dc1e0) = money;
	return money;
}

/* ---- the five spinning part panels behind the mech (panels 1 .. 5 of the records at 0x4dc550) ---- */
typedef struct {
	u32 corners[4][4];   /* x, y, z (and a pad) */
	u32 x;               /* the panel's x offset */
	u32 pad[3];
	float angle;         /* its turn about y, kept within -360 .. 360 */
	float speed;
} Panel;                 /* 0x58 bytes */
#define g_panels ((Panel *)0x4dc550)
#define g_panelSize2 GAME_VAR(float, 0x4b0708)   /* panels 2 and 3 breathe: a half width growing by its rate, */
#define g_panelSize3 GAME_VAR(float, 0x4b0704)   /* which turns to shrinking (-2 a frame) at 600 and back (2) at 200 */
#define g_panelRate2 GAME_VAR(float, 0x4b0710)
#define g_panelRate3 GAME_VAR(float, 0x4b070c)
#define F(addr) ((const float *)(addr))

/* a square of half width size: corners (-s, s), (s, s), (s, -s), (-s, -s) in x, z */
static void panel_resize(Panel *p, float *size)
{
	long double s = -fld_m(size);
	*(float *)&p->corners[0][0] = s;
	*(float *)&p->corners[2][2] = s;
	*(float *)&p->corners[3][0] = s;
	*(float *)&p->corners[3][2] = s;
	p->corners[0][2] = BITS(*size);
	p->corners[1][0] = BITS(*size);
	p->corners[1][2] = BITS(*size);
	p->corners[2][0] = BITS(*size);
}

/* 0x41b400: the panels drawn: each under the menu camera scaled 0.8, its texture (0x9da470 - k * 4), at height
   k * 5 + 0x4dcfc4 + 1 - 105 and depth 0x4dcfc8, turned by its angle; the angle advances by its speed. Then
   panels 2 / 3 breathe */
void (armc_41b400)(void)
{
	glEnable(GL_TEXTURE_2D);
	for (int k = 1; k < 6; k++) {
		gfx_setMenuCamera();
		glScalef_bits(0x3f4ccccd, 0x3f4ccccd, 0x3f4ccccd);   /* 0.8 */
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		int texture = GAME_VAR(int, 0x9da470 - k * 4);
		tex_bind(g_textures->managers[texture / 512], texture % 512);
		Panel *p = &g_panels[k];
		if (k == 2)
			panel_resize(p, &g_panelSize2);
		else if (k == 3)
			panel_resize(p, &g_panelSize3);
		float y = f32(fsub_m(fadd_m(fadd_m(fmul_m((long double)k, F(0x4a93d0)), F(0x4dcfc4)), F(0x4a9424)), F(0x4a94b4)));
		glTranslatef_bits(p->x, BITS(y), GAME_VAR(u32, 0x4dcfc8));
		glPushMatrix();
		gl_rotateXYZ(0, BITS(p->angle), 0);
		glBegin(GL_QUADS);
		static const float uv[4][2] = { { 0, 1 }, { 1, 1 }, { 1, 0 }, { 0, 0 } };
		for (int c = 0; c < 4; c++) {
			glTexCoord2f(uv[c][0], uv[c][1]);
			glVertex3f_stored(p->corners[c]);
		}
		glEnd();
		glPopMatrix();
		long double angle = fadd_m(fmul_m(fld_m(&g_frameTime), &p->speed), &p->angle);
		float stored = f32(angle);
		p->angle = stored;
		if (angle > *F(0x4a9460)) {
			BITS(p->angle) = 0xc3b40000;   /* -360 */
			stored = -360.0f;
		}
		if (!(stored >= *F(0x4a94b0)))
			BITS(p->angle) = 0x43b40000;   /* 360 */
	}
	long double size = fadd_m(fld_m(&g_panelRate3), &g_panelSize3);
	float stored = f32(size);
	g_panelSize3 = stored;
	if (size >= *F(0x4a94ac))
		g_panelRate3 = fmul_m(fld_m(&g_frameTime), F(0x4a94a8));
	if (!(stored > *F(0x4a93f0)))   /* the stored size (panel 2 below compares the sum itself) */
		g_panelRate3 = (long double)g_frameTime + g_frameTime;
	size = fadd_m(fld_m(&g_panelRate2), &g_panelSize2);
	g_panelSize2 = size;
	if (size >= *F(0x4a94ac))
		g_panelRate2 = fmul_m(fld_m(&g_frameTime), F(0x4a94a8));
	if (!(size > *F(0x4a93f0)))
		g_panelRate2 = (long double)g_frameTime + g_frameTime;
}
#undef F

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

/* 0x45dd80 (thiscall on the stage): actor slot a claimed (stage_setupActorSlot) and made the player's, with weapon slot 0 */
void THISCALL (stage_claimPlayerActor)(Stage *stage, int a, int x, int y, void *spawn)
{
	stage_setupActorSlot(stage, a, x, y, spawn);
	stage->playerActor = a;
	actor_setWeaponSlot(stage, a, 0);
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

/* 0x41dab0: the armour screen's weight line at y (0x4dcc94): the label 0x7573a4 right-aligned at 0x27c (8 units a
   character in mode 1, 0x9dae74, else 14); below it the total weight (the ten parts' weights summed into 0x4dc78c)
   in red when above the most the legs carry (0x4dcb0c), else green, then "/most" in white, both as "%.0f" and
   right-aligned at 0x27e. The original leaves eax to callers that ignore it */
void (armc_41dab0)(void)
{
	static const u32 weights[10] = { 0x4dc14c, 0x4dc0cc, 0x4dc04c, 0x4dbfcc, 0x4dbf4c, 0x4dbecc, 0x4dcea0, 0x4dc240, 0x4dc2a4, 0x4dcf0c };
	int y = GAME_VAR(int, 0x4dcc94);
	struct { char total[20]; char most[20]; } s;   /* (in this order on the original's stack) */
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	int length = (int)strlen((const char *)0x7573a4);
	text_draw16(0x27c - length * (GAME_VAR(int, 0x9dae74) == 1 ? 8 : 14), y, (const char *)0x7573a4);
	long double sum = fld_m((const float *)weights[0]);
	for (int k = 1; k < 10; k++)
		sum = fadd_m(sum, (const float *)weights[k]);
	GAME_VAR(float, 0x4dc78c) = f32(sum);
	memset(s.most, 0, sizeof s.most);
	strcpy(s.most, (const char *)0x4ad564);   /* "/" */
	sprintf(s.total, (const char *)0x4b0354, (double)GAME_VAR(float, 0x4dcb0c));   /* "%.0f" */
	strcat(s.most, s.total);
	memset(s.total, 0, sizeof s.total);
	sprintf(s.total, (const char *)0x4b0354, (double)GAME_VAR(float, 0x4dc78c));
	if (GAME_VAR(float, 0x4dc78c) > GAME_VAR(float, 0x4dcb0c))
		set_colour_bits((Colour *)0x76d438, 0x3f800000, 0, 0, 0x3f800000);
	else
		set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0, 0x3f800000);
	text_draw16(0x27e - ((int)strlen(s.total) + (int)strlen(s.most)) * 14, y + 0x10, s.total);
	set_colour_bits((Colour *)0x76d438, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_draw16(0x27e - (int)strlen(s.most) * 14, y + 0x10, s.most);
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

/* 0x40e930: the selection sent to the others in the room: the colour choices (0x90 bytes from 0x4dc4b8, through the
   FPU: a signalling NaN arrives quiet) kept (0x4dcfe0) and in the room's copy (0x9dd603); the part lists
   (armc_40d990) unless 0x9dd5d8 is 0x14; the parts (0x4dc760) and six settings (0x4dcb18) kept as in
   armc_saveSelection (the range checks jumped over again); their low bytes into the room's copy (0x9dd5f8: the five
   parts, then settings 4 / 5, then 0 .. 3); then the packet at 0xa0b340: the name (0x9dd570), those 11 bytes from
   +0x1e, the colours from +0x29; sent as kind 0x1b to the game server (0x65). The original returns net_send's eax
   to a caller that ignores it */
void (armc_sendSelectionToNet)(void)
{
	for (int i = 0; i < 0x24; i++) {
		float v = f32(fld_m((const float *)0x4dc4b8 + i));
		((float *)0x4dcfe0)[i] = v;
		((float *)0x9dd603)[i] = v;
	}
	if (GAME_VAR(int, 0x9dd5d8) != 0x14)
		armc_40d990();
	memcpy((void *)0x4dc878, (const void *)0x4dc760, 5 * 4);
	memcpy((void *)0x4dcf18, (const void *)0x4dcb18, 6 * 4);
	u8 *room = (u8 *)0x9dd5f8;
	const int *parts = (const int *)0x4dc878, *settings = (const int *)0x4dcf18;
	for (int i = 0; i < 4; i++)
		room[7 + i] = (u8)settings[2 + i];
	room[5] = (u8)GAME_VAR(int, 0x4dcb18);
	room[6] = (u8)GAME_VAR(int, 0x4dcb1c);
	for (int i = 0; i < 5; i++)
		room[i] = (u8)parts[i];
	u8 *packet = GAME_VAR(u8 *, 0xa0b340);
	strcpy((char *)packet, (const char *)0x9dd570);
	memcpy(packet + 0x1e, room, 11);
	memcpy(packet + 0x29, (const void *)0x9dd603, 0x90);
	net_send(0x1b, 0x65);
}

/* 0x40fb20: the armour centre's main page clicked (armc_40e450's buttons 1 .. 16): 1 / 2 the part and colour pages
   (armc_40f220 / 40f320, unless already there), 3 / 4 the part screen's two sides (armc_40f0f0), 6 .. 11 the mech
   view 0 .. 5 (0x4dbc6c; its zoom 0x4dcfd8 back to 1), 14 / 15 the view's two turns (armc_40f340; not in view 5),
   16 the rotation toggle (0x4dceac). Each with its sound. Returns what the original leaves in eax */
u32 (armc_40fb20)(void)
{
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	u32 button = GAME_CDECL(0x40e450, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* armc_40e450 */
	int view = GAME_VAR(int, 0x4dbc6c);
	switch (button) {
	case 1:
		if (GAME_VAR(int, 0x4dc798) == 2)
			return 2;
		sound_playMenu(2);
		return GAME_CDECL(0x40f220, u32, void)();
	case 2:
		if (GAME_VAR(int, 0x4dc798) == 3)
			return 1;
		sound_playMenu(2);
		return GAME_CDECL(0x40f320, u32, void)();
	case 3: case 4:
		sound_playMenu(0);
		return GAME_CDECL(0x40f0f0, u32, int)(button == 3);
	case 6: case 7: case 8: case 9: case 10: case 11:
		if (view == (int)button - 6)
			return button == 7 || button == 11 ? button - 1 : button - 6;
		{
			u32 r = GAME_CDECL(0x41e760, u32, int)(2);
			GAME_VAR(int, 0x4dbc6c) = button - 6;
			GAME_VAR(float, 0x4dcfd8) = 1.0f;
			return r;
		}
	case 14: case 15:
		if (view == 5)
			return button - 1;
		sound_playMenu(8);
		return GAME_CDECL(0x40f340, u32, int, int)(GAME_VAR(int, 0x4dbc6c), button == 14 ? 1 : 2);
	case 16:
		sound_playMenu(2);
		view = GAME_VAR(int, 0x4dceac);
		GAME_VAR(int, 0x4dceac) = 1 - view;
		return view;
	}
	return button - 1;
}

/* 0x40ff40: the colour page clicked (armc_40e4d0's buttons 0 .. 17): 0 .. 2 the part screen, main and colour pages
   (armc_40f200 / 40f220 / 40f320, unless already there), 3 / 4 the two sides (armc_40f0f0), 5 .. 10 the colour slot
   0 .. 5 (0x4dc4b0; slot 5 also armc_40f590), 11 .. 16 the slider and swatch buttons (armc_40f5d0 .. 40f7e0), 17 the
   rotation toggle. Returns what the original leaves in eax */
u32 (armc_colourScreenInput)(void)
{
	if (!GAME_VAR(int, 0x4ded88))
		return 0;
	u32 button = GAME_CDECL(0x40e4d0, u32, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* armc_40e4d0 */
	static const u32 page[3] = { 0x40f200, 0x40f220, 0x40f320 };
	static const u32 control[6] = { 0x40f5d0, 0x40f670, 0x40f6b0, 0x40f6f0, 0x40f790, 0x40f7e0 };
	u32 r;
	switch (button) {
	case 0: case 1: case 2:
		if (GAME_VAR(u32, 0x4dc798) == button + 1)
			return button == 1 ? 2 : button;
		sound_playMenu(2);
		return GAME_CDECL(page[button], u32, void)();
	case 3: case 4:
		sound_playMenu(2);
		return GAME_CDECL(0x40f0f0, u32, int)(button == 3);
	case 5: case 6: case 7: case 8: case 9: case 10:
		if (GAME_VAR(u32, 0x4dc4b0) == button - 5)
			return button - 5;
		r = GAME_CDECL(0x41e760, u32, int)(2);
		GAME_VAR(u32, 0x4dc4b0) = button - 5;
		return button == 10 ? GAME_CDECL(0x40f590, u32, void)() : r;
	case 11: case 12: case 13: case 14: case 15: case 16:
		return GAME_CDECL(control[button - 11], u32, void)();
	case 17:
		sound_playMenu(2);
		r = GAME_VAR(u32, 0x4dceac);
		GAME_VAR(u32, 0x4dceac) = 1 - r;
		return r;
	}
	return button;
}
