/* armc_misc.c: small pieces of the ARM CENTER screen: its per-mode draw passes, the 3D view's setup, the text
   helpers that follow the language, and re-making the player's actor. */
#include "../game.h"
#include "../wide.h"
#include <string.h>

#define g_armcAngle GAME_VAR(float, 0x4dbc04)          /* the preview's turn */
#define g_armcSessionDue GAME_VAR(int, 0x4dc86c)      /* (by use) the "please wait" box was shown: the session is made next */

/* 0x41dfb0: the parts page: the preview, the part lists (armc_resetSeraphimParts, a no-op in the patched game) and, unless the
   interface is hidden (Ctrl+Alt+M), the frame and the stats panel */
void (armc_drawPartsPage)(void)
{
	if (g_armcPreview != 0)
		armc_updatePartsPreview();
	if (g_armcFrom != 3)
		armc_resetSeraphimParts();
	if (g_armcHideInterface == 0) {
		armc_drawModeTabs();
		armc_drawStatsPanel();
	}
}

/* 0x41dfe0: the colour page (its own preview) */
void (armc_drawColourPage)(void)
{
	if (g_armcPreview != 0)
		armc_updateColourPreview();
	if (g_armcHideInterface == 0) {
		armc_drawModeTabs();
		armc_drawBuildScreen();
	}
}

/* 0x41e010: the third page */
void (armc_drawThirdPage)(void)
{
	if (g_armcPreview != 0)
		armc_updatePartsPreview();
	if (g_armcHideInterface == 0) {
		armc_drawModeTabs();
		armc_drawColourEditor();
	}
}

/* 0x41b710: the 3D view: projection, white, textures on, the menu camera */
void (armc_setup3DView)(void)
{
	gfx_setProjection2D3D(1);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	gfx_setMenuCamera();
}

/* 0x4125c0: text in the font that suits the language (language 2 uses the small 5-pixel font) */
void (armc_drawText)(int x, int y, const char *text)
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
void THISCALL (stage_remakePlayerActor)(Stage *stage)
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


/* 0x40f0f0: leaving the screen; confirmed: keep the mech (saved with the profile, or sent to the room's players
   when entered from the room). The front end's 3D background and camera are reset and the Netsphere music starts */
void (armc_exit)(int confirmed)
{
	switch (g_armcFrom) {
	case 1:
		armc_restoreMenuCamera();
		g_armcState = 0;
		g_viewAspect = 0.1f;
		if (confirmed)
			armc_saveSelection();
		break;
	case 2:
		g_armcState = 0;
		g_viewAspect = 0.1f;
		g_lobbySubState = 0;
		if (confirmed)
			armc_saveSelection();
		break;
	case 3:
		armc_restoreMenuCamera();
		g_armcState = 0;
		g_viewAspect = 0.1f;
		if (confirmed)
			armc_sendSelectionToNet();
		break;
	}
	g_armcCamHeight = 0.0f;
	g_armcCamDistance = 1600.0f;
	(*(int *)&g_menuCameraLookY) = 0;
	g_menuCameraHeight = 0;
	g_armcLeaving = 1;
	g_flareSizeB = 10.0f;
	g_flareSizeA = 48.0f;
	g_flareStepB = 0.2f;
	g_flareStepA = -0.2f;
	sound_playMenu(4);
	music_play((const char *)STR(0x4b01cc, "music/Netsphere.mp3"));                  /* "music/Netsphere.mp3", the game's own string */
	if (g_startedFromLobby == 1 && g_lobbyReply == 0x66)
		g_lobbyReply = 0x67;
}

/* ---- the mech preview of the parts and colour pages: a perspective view turned by the preview's angle (spinning
   while 0x4dceac is set), the mech posed by armc_rotateFromCursor for the part in view ---- */
#define g_armcEye ((const u32 *)ADDR(g_vecOrigin))              /* (by use) the preview camera's position */

/* 0x461850: the preview's 3D pass. The camera at eye looking along forward (camera_setupView, as the match's view);
   while the right button is held the cursor turns the mech: its offset from the screen's centre (w x h) is kept
   (+0x2343293 y, +0x2343297 x) and the heading becomes x / w * 3600 less the preview's angle. The actor's pitch is
   y / (h / 2) * 89 degrees. The mech is posed (actor_processFrame), lit by one light from the view direction, and
   its eight part lists queued: with no part chosen (part < 0) all under that light, else the chosen one white and
   the rest a dim violet, unlit; then drawn. The cursor is in 640 x 480 units while w and h are screen pixels, so
   above 640 x 480 the mech turned only part of the way; the patch DLL's fix (wide.h: rotFix; its four changes at
   0x461962, 0x461982, 0x4619bb, 0x4619e1) uses 640 x 480 there. (The original's SEH frame, for unwinding the local
   light set, is not reproduced.) */
void THISCALL (armc_rotateFromCursor)(Scene *scene, const u32 *eye, const u32 *forward, const u32 *up, int part, int angle,
                                      int w, int h)
{
	static const u32 lists[8] = { 0x554, 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };   /* (in the actor) */
	u8 *s = (u8 *)scene, *stage = s + 0x1f36c8, *vv = s + 0x74;
	u32 light[0xb00c / 4];   /* a Light: vtable, 0x400 entries of 0x2c bytes, two counts */
	for (int i = 0; i < 0x400; i++)
		GAME_THISFN(ResourceSet_trivialCtor, 0x45fff0, void *, void *)((u8 *)RELOC(light) + 4 + i * 0x2c);
	light[0] = VT(Light, 0x4aa248);
	Light_clearCounts(light);
	u8 white[4] = { 0xff, 0xff, 0xff, 0xff }, dim[4] = { 0xf0, 0xc0, 0xc0, 0x60 };
	frameTimer_average(scene);
	u32 x44 = GAME_VAR(u32, s + 0x44);
	float far = view_farPlane(), near = view_nearPlane(), fov = game_clock();
	GAME_THISFN(camera_setupView, 0x4729b0, void, void *, const u32 *, const u32 *, const u32 *, u32, int, int, u32, u32, u32)(stage, eye, forward, up,
	                                                                                                       BITS(fov), w, h, BITS(near), BITS(far), x44);   /* camera_setupView */
	ViewVolume_captureMatrices(vv, 0, s + 0x22e7068);
	ViewVolume_reset(vv);
	int fix = *g_wide->rotFix, W = fix ? 640 : w, H = fix ? 480 : h;
	if (g_mouse2Down) {   /* the right button held */
		GAME_VAR(int, s + 0x234325b) = g_mouseY;
		GAME_VAR(int, s + 0x2343257) = g_mouseX;
		int dy = GAME_VAR(int, s + 0x234325b) - H / 2, dx = GAME_VAR(int, s + 0x2343257) - W / 2;
		GAME_VAR(float, s + 0x2343293) = (float)dy;
		long double x = (long double)dx;
		GAME_VAR(float, s + 0x2343297) = (float)x;
		long double turn = x / W * k_3600f;   /* 3600 */
		GAME_VAR(float, s + 0x2342409) = (float)(turn - (long double)((angle % 3600 + 3600) % 3600));
	}
	int a = GAME_VAR(int, s + 0x234240d);
	u8 *actor = s + 0x1ecca70 + a * 0x8888;
	GAME_VAR(float, actor + 0x18c) = (float)fmul_m(fld_m((const float *)(s + 0x2343293)) / (long double)(H / 2),
	                                               (const float *)ADDR(k_890f));   /* 890: tenths of a degree */
	GAME_VAR(u32, actor + 0x190) = GAME_VAR(u32, s + 0x2342409);
	actor_processFrame(stage, GAME_VAR(int, s + 0x234240d), GAME_VAR(float, s + 0x3c));
	Light_clearCounts(light);
	u32 dir[3] = { forward[0], forward[1], forward[2] };
	Vec3_normalize((float *)RELOC(dir));
	factors_addPoint(light, (const void *)IMG(0xa1f23c), dir);
	for (int k = 0; k < 8; k++) {
		u8 *list = s + 0x1ecca70 + GAME_VAR(int, s + 0x234240d) * 0x8888 + lists[k];
		if (part < 0)
			partList_queue(list, vv, light, NULL, 1, (u32)-1, 0);
		else
			partList_queue(list, vv, NULL, k == part ? white : dim, 1, (u32)-1, 0);
	}
	render_drawObjects(vv, 0, 0.0f);
	Light_dtor(light);
}

static void preview(int posed, int part)   /* posed: the mech posed for part */
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(g_viewAngle, g_viewAspect, 100.0, 20000.0);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_MODELVIEW);
	float turn = f32(fmul_m(fld_m(&g_armcAngle), (const float *)ADDR(k_tenthsToDegrees)));
	gl_rotateXYZ(0, BITS(turn), 0);
	u32 eye[3] = { g_armcEye[0], g_armcEye[1], g_armcEye[2] };
	u32 forward[3] = { 0, 0, 0xbf800000 }, up[3] = { 0, 0x3f800000, 0 };   /* (0, 0, -1), (0, 1, 0), on the stack as the original's */
	if (posed)
		armc_rotateFromCursor(g_scene, eye, forward, up, part, ftol(g_armcAngle), g_screenW, g_screenH);
	if (g_armcSpin) {
		long double angle = fadd_m(fmul_m(fld_m(&g_frameTime), (const float *)IMG(0x4a94cc)), &g_armcAngle);
		g_armcAngle = angle;
		if (angle >= k_3600f)
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
void (armc_updatePartsPreview)(void)
{
	gfx_setProjection2D3D(1);
	if (g_mechChanged == 1) {
		const int *parts = (const int *)IMG(0x4dc760);    /* the mech's head, chest, arm, leg, booster */
		switch (g_armcPartSlot) {
		case 0: armc_setHeadIndex(g_scene, parts[0]); break;
		case 1: armc_setChestIndex(g_scene, parts[1]); break;
		case 2: armc_setArmIndex(g_scene, parts[2]); break;
		case 3: armc_setLegIndex(g_scene, parts[3]); break;
		case 4: armc_setBoosterIndex(g_scene, parts[4]); break;
		}
		armc_drawPartPanels();
		armc_giveShownActorWeapon(g_scene, g_armcSlot);
		armc_readMechStats();
		g_mechChanged = 0;
		armc_retintParts();
	}
	if (g_emptyItemSlot0 == 1)
		g_emptyItemSlot0 = 0;
	if (g_coloursChanged) {
		armc_applyColourSlot();
		g_coloursChanged = 0;
	}
	switch (g_armcMode) {
	case 1: preview(1, part_in_view()); break;
	case 2: case 3: preview(1, -1); break;
	default: preview(0, 0); break;
	}
}

/* 0x41d8a0: the colour page's preview: item slot 0 emptied first when asked (0x4dbc80). The second page poses the
   item slot being picked (slots 4 / 5 as 6 / 7, the weapon slots as 5; none when that slot's record is empty) */
void (armc_updateColourPreview)(void)
{
	gfx_setProjection2D3D(1);
	if (g_emptyItemSlot0 == 1) {
		armc_weaponSlotRecord(0, 0);
		g_emptyItemSlot0 = 0;
	}
	int slot;
	switch (g_armcMode) {
	case 1: preview(1, part_in_view()); break;
	case 2:
		slot = g_armcSlot;
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
	if (g_armcEntered && g_armcFrom != 2)
		menu_drawBackground();
	if (g_armcState != 2) {
		if (g_armcFrom == 3)
			armc_drawPreviewTunnel();
		if (g_armcFrom == 1)
			armc_drawTunnel();
	}
	arena_launchFromFile();
	int state = g_armcState;
	if (state == 1 || state == 0)
		return;
	if (g_dialogOpen) {
		menu_drawFrame(g_armcStatsPanelLeft, g_armcStatsPanelTop, g_armcSliderLeft, g_armcStatsPanelBottom);
		return;
	}
	if (g_armcSessionDue && !g_armcSessionMade) {
		static const u32 items[6] = { ADDR(g_mechItem2), ADDR(g_mechItem3), ADDR(g_mechItem4), ADDR(g_mechItem5), ADDR(g_itemSlot4), ADDR(g_itemSlot5) };
		armc_enterScreen();
		for (int slot = 0; slot < 6; slot++)
			armc_weaponSlotRecord(slot, GAME_VAR(int, items[slot]));
		state = g_armcState;
	}
	if (state == 2 && !g_armcLeaving) {
		armc_easeCamera();
		armc_setup3DView();
		armc_drawPanels();
	}
	armc_extraItemBonuses();
	switch (g_armcMode) {
	case 1: armc_drawPartsPage(); break;
	case 2: armc_drawColourPage(); break;
	case 3: armc_drawThirdPage(); break;
	}
	int box = 1;
	if (g_armcPreview) {
		armc_drawWeightLine();
		box = !g_armcPreview;
	}
	if (box && !g_armcSessionMade) {
		set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);
		menu_drawRect(100, 200, 540, 280, 1);
		set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);   /* yellow */
		text_drawBox16(105, 220, 535, (const char *)MSG(297, "LOADING MECHANIC DATA.."));
		text_drawBox16(105, 244, 535, (const char *)MSG(298, "PLEASE WAIT"));
		g_armcSessionDue = 1;
	}
	long double zoom = fsubr_m(fmul_m(fld_m(&g_frameTime), (const float *)ADDR(k_tenthsToDegrees)), &g_armcZoom);
	g_armcZoom = zoom;
	if (!(zoom >= k_m2f))
		g_armcZoom = -2.0f;
}

#define g_menuEye ((u32 *)ADDR(g_menuCameraPos))                   /* the menu camera: its position (g_armcCamHeight, g_armcCamDistance) */
#define g_menuAt ((u32 *)ADDR(g_menuCameraLook))                    /* and the point it looks at */

/* 0x40ee20: entering the ARM CENTER: its music, the parts page with nothing picked, the camera put in front of the
   mech (further back from the room), the dialog box and two colours, the camera's point for the screen, the part
   lists built and the mech read (from the room's session or the profile), a sound; g_progressWentUp set when the level
   (0x9dd5d8 from the room, 0x9f181c otherwise) went up since last time (new parts to show), the new value kept and returned */
u32 (menu_enterMenus)(void)
{
	g_armcHideInterface = 0;
	g_armcSlot = 0;
	armc_initCameraPoints();
	music_play((const char *)STR(0x4b01b0, "music/Heart of Giants.mp3"));
	g_armcPartSlot = 5;
	g_unusedArmcWord3 = 5;
	g_armcColourSlot = 5;
	int fromRoom = g_armcFrom == 3;
	g_armcMode = 1;
	g_armcUnusedFlag = 0;
	g_menuEye[0] = 0;
	g_menuEye[1] = 0;
	u32 distance = fromRoom ? k_armcDistanceRoom : k_armcDistance;   /* -1550, -450 */
	g_menuAt[0] = 0;
	g_menuAt[1] = 0;
	g_menuEye[2] = distance;
	g_menuAt[2] = fromRoom ? 0xc4ce4000 : 0xc4098000;                                /* -1650, -550 */
	g_armcStatsPanelLeft = 10;
	g_armcStatsPanelTop = 10;
	g_armcSliderLeft = 0x276;
	g_armcStatsPanelBottom = 0x1d6;
	static const u32 colourA[4] = { 0, 0x3f800000, 0x3f800000, 0x3f800000 }, colourB[4] = { 0, 0x3f19999a, 0x3f19999a, 0x3f800000 };
	for (int i = 0; i < 4; i++) {
		GAME_VAR(u32, 0x4dbc58 + i * 4) = colourA[i];
		GAME_VAR(u32, 0x4dc1d0 + i * 4) = colourB[i];
	}
	g_progressWentUp = 0;
	u32 *point = (u32 *)ADDR(g_camPoint0X), *pointAt = (u32 *)ADDR(g_camAim0X);   /* the ARM CENTER's camera point */
	point[0] = 0;
	point[1] = 0;
	pointAt[0] = 0;
	pointAt[1] = 0;
	if (fromRoom) {
		point[2] = 0xc47a0000;    /* -1000 */
		pointAt[2] = 0xc4898000;  /* -1100 */
		if (g_pilotLevel > g_bestLevelNet)
			g_progressWentUp = 1;
	} else {
		point[2] = 0x42c80000;    /* 100 */
		pointAt[2] = 0;
		if (g_progress > g_bestProgressSolo)
			g_progressWentUp = 1;
	}
	u32 *home = (u32 *)ADDR(g_menuCameraX), *homeAt = (u32 *)ADDR(g_menuLookAtX);
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
	armcMain_layout();
	armcParts_layout();
	armcColour_layout();
	armc_buildPartLists();
	g_armcEntered = 1;
	g_armcSpin = 1;
	g_mechChanged = 1;
	g_armcPreview = 0;
	g_armcSessionDue = 0;
	g_armcSessionMade = 0;
	g_armcLeaving = 0;
	g_unusedArmcWord4 = 0;
	BITS(g_armcAngle) = 0;
	g_armcZoom = 1.0f;
	if (g_armcFrom == 3)
		mech_unpackFromRecord();
	else
		mech_loadFromProfile();
	armc_loadSavedMech();
	armc_initCameraBox();
	armc_initPartBoxes();
	armc_syncPartCursors();
	sound_playMenu(4);
	if (g_armcFrom == 3) {
		int money = g_pilotLevel;
		if (money > g_bestLevelNet)
			g_bestLevelNet = money;
		return money;
	}
	int money = g_progress;
	if (money > g_bestProgressSolo)
		g_bestProgressSolo = money;
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
#define g_panels ((Panel *)IMG(0x4dc550))
#define g_panelSize2 GAME_VAR(float, 0x4b0708)   /* panels 2 and 3 breathe: a half width growing by its rate, */
#define g_panelSize3 GAME_VAR(float, 0x4b0704)   /* which turns to shrinking (-2 a frame) at 600 and back (2) at 200 */
#define g_panelRate2 GAME_VAR(float, 0x4b0710)
#define g_panelRate3 GAME_VAR(float, 0x4b070c)
#define F(addr) ((const float *)RELOC(addr))

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
void (armc_drawPanels)(void)
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
		glTranslatef_bits(p->x, BITS(y), g_armcPanelDepth);
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
void (armc_easeCamera)(void)
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
void (armc_rightClickLeave)(void)
{
	if (g_keyEnter) {
		armc_restoreMenuCamera();
		g_armcState = 0;
		BITS(g_viewAspect) = 0;
	}
}

/* 0x40de80: the ARM CENTER camera box's corners (each +-700 or 0, as floats) */
void (armc_initCameraBox)(void)
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
void (armc_initPartBoxes)(void)
{
	for (u32 p = IMG(0x4dc554); p < IMG(0x4dc764); p += 0x58) {
		static const signed char corner[] = { -1, -1, -1, 0, 1, -1, -1, 0, 1, -1, 1, 0, -1, -1, 1 };
		for (int k = 0; k < 15; k++)
			if (corner[k])
				GAME_VAR(u32, p - 4 + k * 4) = corner[k] > 0 ? 0x44160000 : 0xc4160000;
		GAME_VAR(int, p + 0x3c) = 0;
		GAME_VAR(int, p + 0x40) = 0;
		GAME_VAR(int, p + 0x44) = 0;
		GAME_VAR(int, p + 0x4c) = 0;
	}
	g_partBox0Offset = 0x3e19999a;   /* 0.15 */
	g_partBox1Offset = 0xbeb33333;   /* -0.35 */
	g_partBox2Offset = 0xbfc00000;   /* -1.5 */
	g_partBox3Offset = 0x3fc00000;   /* 1.5 */
	g_partBox4Offset = 0xbe3851ec;   /* -0.18 */
	g_partBox5Offset = 0x3e3851ec;   /* 0.18 */
	(*(u32 *)&g_panelSize3) = 0x43480000;   /* 200 */
	(*(u32 *)&g_panelSize2) = 0x44160000;   /* 600 */
	(*(u32 *)&g_panelRate3) = 0x40000000;   /* 2 */
	(*(u32 *)&g_panelRate2) = 0xc0000000;   /* -2 */
}

/* 0x410190: the ARM CENTER's mouse, on pages 1 .. 4 (0x4dc798) in a state past 1 (0x4dc790) with no dialog open.
   Returns what the original leaves in eax (the value it stopped at, or the page's handler's) */
u32 (armc_onStateEnter)(void)
{
	int state = g_armcState;
	if (state == 1 || state == 0)
		return state;
	if (g_dialogOpen)
		return g_dialogOpen;
	u32 page = (*(u32 *)&g_armcMode) - 1;
	switch (page) {
	case 0:
		return armc_mainPageClicks();
	case 1:
		return armc_partScreenClicks();
	case 2:
		return armc_colourScreenInput();
	case 3:
		return GAME_FN(armc_rightClickLeave, 0x410160, u32, void)();   /* armc_rightClickLeave (its eax) */
	}
	return page;
}

/* 0x419000: catalogue item i's snapshot texture ("Actor/item/<name>/snapshot"; the name 0x80 bytes a slot at
   0x4dbe50) loaded into 0x4dcc70[i]; nothing for a name shorter than 2 letters. 0x4dcc64 cleared either way */
void (armc_snapshot)(int i)
{
	const char *name = (const char *)(IMG(0x4dbe50) + i * 0x80);
	if (strlen(name) <= 1) {
		g_armcChanged = 0;
		return;
	}
	char path[0x80], copy[0x40];
	memset(path, 0, sizeof path);
	strcpy(path, (const char *)STR(0x4b036c, "Actor/item/"));
	strcat(path, name);
	strcat(path, (const char *)STR(0x4ad564, "/"));
	strcat(path, (const char *)STR(0x4b0360, "snapshot"));
	strcpy(copy, path);
	GAME_VAR(int, 0x4dcc70 + i * 4) = tex_getIdByName((*(void **)&g_textures), copy, 0, 0, 0, 0, 0, 0, 0);
	g_armcChanged = 0;
}

/* 0x41dab0: the armour screen's weight line at y (0x4dcc94): the label 0x7573a4 right-aligned at 0x27c (8 units a
   character in mode 1, 0x9dae74, else 14); below it the total weight (the ten parts' weights summed into 0x4dc78c)
   in red when above the most the legs carry (0x4dcb0c), else green, then "/most" in white, both as "%.0f" and
   right-aligned at 0x27e. The original leaves eax to callers that ignore it */
void (armc_drawWeightLine)(void)
{
	static const u32 weights[10] = { IMG(0x4dc14c), IMG(0x4dc0cc), IMG(0x4dc04c), IMG(0x4dbfcc), IMG(0x4dbf4c), IMG(0x4dbecc), ADDR(g_boosterWeight), ADDR(g_legsWeight), ADDR(g_armsWeight), ADDR(g_headWeight) };
	int y = g_armcStatsPanelTop;
	struct { char total[20]; char most[20]; } s;   /* (in this order on the original's stack) */
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	int length = (int)strlen((const char *)MSG(299, "WEIGHT"));
	text_draw16(0x27c - length * (g_language == 1 ? 8 : 14), y, (const char *)MSG(299, "WEIGHT"));
	long double sum = fld_m((const float *)RELOC(weights[0]));
	for (int k = 1; k < 10; k++)
		sum = fadd_m(sum, (const float *)RELOC(weights[k]));
	g_totalWeight = f32(sum);
	memset(s.most, 0, sizeof s.most);
	strcpy(s.most, (const char *)STR(0x4ad564, "/"));
	sprintf(s.total, (const char *)STR(0x4b0354, "%.0f"), (double)g_legsMaxWeight);
	strcat(s.most, s.total);
	memset(s.total, 0, sizeof s.total);
	sprintf(s.total, (const char *)STR(0x4b0354, "%.0f"), (double)g_totalWeight);
	if (g_totalWeight > g_legsMaxWeight)
		set_colour_bits(g_textColour, 0x3f800000, 0, 0, 0x3f800000);
	else
		set_colour_bits(g_textColour, 0, 0x3f800000, 0, 0x3f800000);
	text_draw16(0x27e - ((int)strlen(s.total) + (int)strlen(s.most)) * 14, y + 0x10, s.total);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
	text_draw16(0x27e - (int)strlen(s.most) * 14, y + 0x10, s.most);
}

/* 0x412450: the three mode tabs across the top (0x4dcc90 / 0x4dcc94, 100 apart): the tab texture (0x9db0a4), the
   chosen one (0x4dc798, 1 .. 3) brighter, then each tab's name (0x7565a4, 0x80 a slot) in its colour (0x4dbc58
   chosen, else 0x4dc1d0). Returns 3 (the original's eax) */
int (armc_drawModeTabs)(void)
{
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	int texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	for (int i = 0; i < 3; i++) {
		glColor4f(1.0f, 1.0f, 1.0f, g_armcMode == i + 1 ? 0.8f : 0.4f);
		int x = g_armcStatsPanelLeft, y = g_armcStatsPanelTop;
		menu_drawWideButton(x + i * 100 + 0x10, y - 8, x + i * 100 + 0x70, y + 0x18, 1);
	}
	glDisable(GL_TEXTURE_2D);
	for (int i = 0; i < 3; i++) {
		const u32 *c = (const u32 *)(g_armcMode == i + 1 ? IMG(0x4dbc58) : IMG(0x4dc1d0));
		set_colour_bits(g_textColour, c[0], c[1], c[2], c[3]);
		int x = g_armcStatsPanelLeft;
		text_drawBox16(x + i * 100 + 0x10, g_armcStatsPanelTop, x + i * 100 + 0x70, (const char *)(MSG(271, "$[0] PARTS") + i * 0x80));
	}
	return 3;
}

/* 0x40e7a0: the selection kept: the part choices (0x90 bytes from 0x4dc4b8 into 0x4dcfe0), the five colour
   choices (0x4dc760 into 0x4dc878) and six more settings (0x4dcb18 into 0x4dcf18), between two calls of the part
   lists (armc_resetSeraphimParts); the original then checked the choices' ranges, which the patched game jumps over. Then the
   progress saved; returns profile_saveProgress's eax */
u32 (armc_saveSelection)(void)
{
	armc_resetSeraphimParts();
	memcpy((void *)OBJ(g_savedColourChoices), (const void *)IMG(0x4dc4b8), 0x90);
	memcpy((void *)ADDR(g_savedMechParts), (const void *)IMG(0x4dc760), 5 * 4);
	memcpy((void *)ADDR(g_savedMechWeapons), (const void *)ADDR(g_itemSlot4), 6 * 4);
	armc_resetSeraphimParts();
	return GAME_FN(profile_saveProgress, 0x447010, u32, void)();   /* profile_saveProgress */
}

/* 0x40e930: the selection sent to the others in the room: the colour choices (0x90 bytes from 0x4dc4b8, through the
   FPU: a signalling NaN arrives quiet) kept (0x4dcfe0) and in the room's copy (0x9dd603); the part lists
   (armc_resetSeraphimParts) unless 0x9dd5d8 is 0x14; the parts (0x4dc760) and six settings (0x4dcb18) kept as in
   armc_saveSelection (the range checks jumped over again); their low bytes into the room's copy (0x9dd5f8: the five
   parts, then settings 4 / 5, then 0 .. 3); then the packet at 0xa0b340: the name (0x9dd570), those 11 bytes from
   +0x1e, the colours from +0x29; sent as kind 0x1b to the game server (0x65). The original returns net_send's eax
   to a caller that ignores it */
void (armc_sendSelectionToNet)(void)
{
	for (int i = 0; i < 0x24; i++) {
		float v = f32(fld_m((const float *)IMG(0x4dc4b8) + i));
		((float *)OBJ(g_savedColourChoices))[i] = v;
		((float *)IMG(0x9dd603))[i] = v;
	}
	if (g_pilotLevel != 0x14)
		armc_resetSeraphimParts();
	memcpy((void *)ADDR(g_savedMechParts), (const void *)IMG(0x4dc760), 5 * 4);
	memcpy((void *)ADDR(g_savedMechWeapons), (const void *)ADDR(g_itemSlot4), 6 * 4);
	u8 *room = (u8 *)IMG(0x9dd5f8);
	const int *parts = (const int *)ADDR(g_savedMechParts), *settings = (const int *)ADDR(g_savedMechWeapons);
	for (int i = 0; i < 4; i++)
		room[7 + i] = (u8)settings[2 + i];
	room[5] = (u8)g_itemSlot4;
	room[6] = (u8)g_itemSlot5;
	for (int i = 0; i < 5; i++)
		room[i] = (u8)parts[i];
	u8 *packet = g_netSelectionPacket;
	strcpy((char *)packet, g_joinedTitleName);
	memcpy(packet + 0x1e, room, 11);
	memcpy(packet + 0x29, (const void *)IMG(0x9dd603), 0x90);
	net_send(0x1b, 0x65);
}

/* 0x40fb20: the armour centre's main page clicked (armcMain_hitTest's buttons 1 .. 16): 1 / 2 the part and colour pages
   (armc_40f220 / 40f320, unless already there), 3 / 4 the part screen's two sides (armc_40f0f0), 6 .. 11 the mech
   view 0 .. 5 (0x4dbc6c; its zoom 0x4dcfd8 back to 1), 14 / 15 the view's two turns (armc_stepPart; not in view 5),
   16 the rotation toggle (0x4dceac). Each with its sound. Returns what the original leaves in eax */
u32 (armc_mainPageClicks)(void)
{
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_FN(armcMain_hitTest, 0x40e450, u32, int, int)(g_mouseX, g_mouseY);   /* armcMain_hitTest */
	int view = g_armcPartSlot;
	switch (button) {
	case 1:
		if (g_armcMode == 2)
			return 2;
		sound_playMenu(2);
		return GAME_FN(armc_drawPartScreen, 0x40f220, u32, void)();
	case 2:
		if (g_armcMode == 3)
			return 1;
		sound_playMenu(2);
		return GAME_FN(armc_showColourPage, 0x40f320, u32, void)();
	case 3: case 4:
		sound_playMenu(0);
		return GAME_FN(armc_exit, 0x40f0f0, u32, int)(button == 3);
	case 6: case 7: case 8: case 9: case 10: case 11:
		if (view == (int)button - 6)
			return button == 7 || button == 11 ? button - 1 : button - 6;
		{
			u32 r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(2);
			g_armcPartSlot = button - 6;
			g_armcZoom = 1.0f;
			return r;
		}
	case 14: case 15:
		if (view == 5)
			return button - 1;
		sound_playMenu(8);
		return GAME_FN(armc_stepPart, 0x40f340, u32, int, int)(g_armcPartSlot, button == 14 ? 1 : 2);
	case 16:
		sound_playMenu(2);
		view = g_armcSpin;
		g_armcSpin = 1 - view;
		return view;
	}
	return button - 1;
}

/* 0x40ff40: the colour page clicked (armcColour_hitTest's buttons 0 .. 17): 0 .. 2 the part screen, main and colour pages
   (armc_40f200 / 40f220 / 40f320, unless already there), 3 / 4 the two sides (armc_40f0f0), 5 .. 10 the colour slot
   0 .. 5 (0x4dc4b0; slot 5 also armc_40f590), 11 .. 16 the slider and swatch buttons (armc_40f5d0 .. 40f7e0), 17 the
   rotation toggle. Returns what the original leaves in eax */
u32 (armc_colourScreenInput)(void)
{
	if (!g_mouseClick)
		return 0;
	u32 button = GAME_FN(armcColour_hitTest, 0x40e4d0, u32, int, int)(g_mouseX, g_mouseY);   /* armcColour_hitTest */
	static const u32 page[3] = { FN_ADDR(armc_showPartsPage, 0x40f200), FN_ADDR(armc_drawPartScreen, 0x40f220), FN_ADDR(armc_showColourPage, 0x40f320) };
	static const u32 control[6] = { FN_ADDR(armc_dragPrimaryHue, 0x40f5d0), FN_ADDR(armc_dragPrimaryChroma, 0x40f670), FN_ADDR(armc_dragPrimaryValue, 0x40f6b0), FN_ADDR(armc_dragSecondaryHue, 0x40f6f0), FN_ADDR(armc_dragSecondaryChroma, 0x40f790), FN_ADDR(armc_dragSecondaryValue, 0x40f7e0) };
	u32 r;
	switch (button) {
	case 0: case 1: case 2:
		if ((*(u32 *)&g_armcMode) == button + 1)
			return button == 1 ? 2 : button;
		sound_playMenu(2);
		return GAME_CDECL(page[button], u32, void)();
	case 3: case 4:
		sound_playMenu(2);
		return GAME_FN(armc_exit, 0x40f0f0, u32, int)(button == 3);
	case 5: case 6: case 7: case 8: case 9: case 10:
		if ((*(u32 *)&g_armcColourSlot) == button - 5)
			return button - 5;
		r = GAME_FN(sound_playMenu, 0x41e760, u32, int)(2);
		(*(u32 *)&g_armcColourSlot) = button - 5;
		return button == 10 ? GAME_FN(armc_backupColours, 0x40f590, u32, void)() : r;
	case 11: case 12: case 13: case 14: case 15: case 16:
		return GAME_CDECL(control[button - 11], u32, void)();
	case 17:
		sound_playMenu(2);
		r = (*(u32 *)&g_armcSpin);
		(*(u32 *)&g_armcSpin) = 1 - r;
		return r;
	}
	return button;
}
