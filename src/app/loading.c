/* loading.c: loading: the start-up load (app_startupLoad) and the menus' textures (menu_loadTextures); a match's
   load, one step per frame (game_processLoadingMode: the stages, the host's game packet sent meanwhile); and the
   loading screen between the menus and a match: a scrolling textured cylinder (Iftex/Cylinder) behind the status text
   lines, faded in from black and out to black (no progress bar). */
#include "../game.h"
#include <string.h>

#define g_loadText g_loadStatusText
#define ONE k_1f

/* one frame of a fade: the screen at its scroll (g_loadScroll), under a black quad (alpha 1 - time fading in, time
   fading out), the fade's time advanced */
static void fade_frame(int in)
{
	loading_draw_bits(BITS(g_loadScroll));
	if (in)
		glColor4f(1.0f, 1.0f, 1.0f, FSUB(ONE, g_loadFade));
	else
		glColor4f_bits(0x3f800000, 0x3f800000, 0x3f800000, BITS(g_loadFade));
	int h = gfx_getHeight();
	gfx_fillRect(0, 0, gfx_getWidth(), h);
	g_loadFade = fadd_m(TimeSync_frameTime(g_loadTimer), &g_loadFade);
	gfx_swapBuffers();
}

/* 0x469730 (mode, unused, text): the loading screen, as the log hook (g_logHook)
   while a match loads. -1: the backdrop's scroll (g_loadScroll) reset, the text set, the backdrop looked up, then a
   fade from black over one second of game time; -2: the scroll advanced by the time since the last call, the text
   set, then a fade to black; any other mode: the scroll advanced (the text set when 1) and one frame */
void (loading_drawScreen)(int mode, int unused, const char *text)
{
	(void)unused;
	long double dt = TimeSync_frameTime(g_loadTimer);
	if (mode == -2) {
		g_loadScroll = fadd_m(dt, &g_loadScroll);
		strcpy(g_loadText, text);
		BITS(g_loadFade) = 0;
		do
			fade_frame(0);
		while (!(g_loadFade >= ONE));
		return;
	}
	if (mode == -1) {
		BITS(g_loadScroll) = 0;
		strcpy(g_loadText, text);
		g_loadTexture = tex_getIdByName(g_textures, (const char *)STR(0x4c533c, "Iftex/Cylinder"), 0, 0, 0, 0, 0, 0, 0);
		BITS(g_loadFade) = 0;
		do
			fade_frame(1);
		while (!(g_loadFade >= ONE));
		return;
	}
	g_loadScroll = fadd_m(dt, &g_loadScroll);
	if (mode == 1)
		strcpy(g_loadText, text);
	loading_draw_bits(BITS(g_loadScroll));
	gfx_swapBuffers();
}


/* a point of the cylinder: radius 400 about the z axis at angle (tenths of a degree), at depth z */
static void cylinder_vertex(int angle, u32 z)
{
	u32 v[3] = { 0, 0x43c80000, z };   /* (0, 400, z) */
	Vec3_rotateAxis((float *)RELOC(v), 0, angle);
	glVertex3fv((const float *)RELOC(v));
}

/* one line of the loading screen's text at row (16 pixels a row) */
static void info_line(int row, const char *text)
{
	text_drawSized(0x96, row * 16 + 0x46, text, 0x10);
}

/* 0x469320 (scroll, as bits): the loading screen: cleared to blue, the backdrop (g_loadTexture) on the inside of a
   cylinder of 18 segments, 25133 deep, its texture's v running from the scroll to the scroll + 10; then in
   yellow the game's title (session modes 1 / 3: a network game, replays), zone, play type (both "on receiving" while awaitingHostRound is 1), frag and
   time limits, and in grey the status line g_loadStatusText */
void (loading_draw)(u32 scroll)
{
	glClearColor_bits(0x3f000000, 0x3f000000, 0x3f800000, 0x3f800000);   /* glClearColor(0.5, 0.5, 1, 1) */
	glClearDepth(1.0);
	glClear(0x4100);   /* GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT */
	gfx_setMatchProjection_bits(1, 0x3f800000);   /* gfx_setMatchProjection(1, 1.0) */
	glEnable(GL_TEXTURE_2D);
	int texture = g_loadTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	glColor4f(0.5f, 0.5f, 1.0f, 0.5f);
	float far = f32(fadd_m(fld_m((const float *)&scroll), (const float *)ADDR(k_10f)));   /* scroll + 10 */
	for (int angle = 0, j = 0; angle < 0xfd20; angle += 0xe10, j++) {
		glBegin(GL_QUADS);
		float s0 = f32(fmul_m((long double)j, k_0_0555556f));        /* j / 18 */
		glTexCoord2f_bits(BITS(s0), scroll);
		cylinder_vertex(angle / 18, 0);
		float s1 = f32(fmul_m((long double)(j + 1), k_0_0555556f));
		glTexCoord2f_bits(BITS(s1), scroll);
		cylinder_vertex((angle + 0xe10) / 18, 0);
		glTexCoord2f_bits(BITS(s1), BITS(far));
		cylinder_vertex((angle + 0xe10) / 18, 0xc6c4597c);   /* -25132.74 */
		glTexCoord2f_bits(BITS(s0), BITS(far));
		cylinder_vertex(angle / 18, 0xc6c4597c);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	gfx_setMatchProjection_bits(0, 0x3f800000);
	text_setColor(1.0f, 1.0f, 0.0f, 1.0f);
	char line[0x100];
	int row = 2;
	int mode = *(int *)((*(u8 * *)&g_loadGame) + 8);
	if (mode == 1 || mode == 3) {
		sprintf(line, (const char *)STR(0x4c5330, "TITLE: %s"), g_gameTitle);
		info_line(row, line);
		row = 4;
	}
	if (((Scene *)(*(u8 * *)&g_loadGame))->awaitingHostRound == 1)
		sprintf(line, (const char *)STR(0x4c531c, "ZONE: ON RECEIVING"));
	else
		sprintf(line, (const char *)STR(0x4c5310, "ZONE: %s"), (const char *)(OBJ(g_mapNames) + g_mapIndex * 32));
	info_line(row, line);
	row += 2;
	if (((Scene *)(*(u8 * *)&g_loadGame))->awaitingHostRound == 1)
		sprintf(line, (const char *)STR(0x4c52f8, "PLAY TYPE: ON RECEIVING"));
	else
		sprintf(line, (const char *)STR(0x4c52e8, "PLAY TYPE: %s"), (const char *)(STR(0x4c7030, "DEATH MATCH") + ((Scene *)(*(u8 * *)&g_loadGame))->gameMode * 64));
	info_line(row, line);
	row += 2;
	sprintf(line, (const char *)STR(0x4c52d8, "FRAG LIMIT: %d"), g_fragLimit);
	info_line(row, line);
	row += 2;
	sprintf(line, (const char *)STR(0x4c52c8, "TIME LIMIT: %d"), g_timeLimit);
	info_line(row, line);
	text_setColor(0.5f, 0.5f, 0.5f, 1.0f);
	text_drawSized(0x96, row * 16 + 0x76, (const char *)g_loadStatusText, 0x10);
}

/* ---- the game's start-up load ---- */

/* a texture's id by its name (copied to the stack first, as the original does) */
static int texture_named(const char *name)
{
	char copy[64];
	strcpy(copy, name);
	return tex_getIdByName(g_textures, copy, 0, 0, 0, 0, 0, 0, 0);
}

/* ---- the menus' textures, loaded with the loading screen moved on a step (g_loadStep) between them ---- */
#define T(addr) texture_named((const char *)RELOC(addr))

static void next_step(void)
{
	g_loadStep++;
	frontEnd_drawProgress();
}

/* 0x430ca0: the menus' textures by name: the intro frames ("iftex/m_intro1" .. 4, "m2_intro1" .. 4 into g_introTextures),
   the corner and box screen (g_menuFrameTextures), the main, arena, control and ladder menus' pairs (g_mainMenuTextures / g_arenaMenuTextures /
   g_ctrlMenuTextures / g_ladderMenuTextures), the six spirals (g_spiralTextures), then "gameconnect" (g_gameConnectTexture), "option" (g_buttonTexture, the
   buttons), "mouse" (g_cursorTexture), "cylinder" (g_ringBandTexture), "cylinder_menu" (g_cageTexture), "menu34" (g_menuTunnelTexture, the tunnel)
   and "character" (g_characterTexture); first a step and a wait of 2 */
void (menu_loadTextures)(void)
{
	static const u32 intro[8] = { STR(0x4b25dc, "iftex/m_intro1"), STR(0x4b25cc, "iftex/m_intro2"), STR(0x4b25bc, "iftex/m_intro3"), STR(0x4b25ac, "iftex/m_intro4"), STR(0x4b259c, "iftex/m2_intro1"), STR(0x4b258c, "iftex/m2_intro2"), STR(0x4b257c, "iftex/m2_intro3"), STR(0x4b256c, "iftex/m2_intro4") };
	static const u32 frames[2] = { STR(0x4b2480, "iftex/corner"), STR(0x4b2470, "iftex/boxscreen") };   /* corner, boxscreen */
	static const u32 mainmenu[2] = { STR(0x4b245c, "iftex/mainmenu01"), STR(0x4b2448, "iftex/mainmenu02") }, arenamenu[2] = { STR(0x4b2434, "iftex/arenamenu01"), STR(0x4b2420, "iftex/arenamenu02") };
	static const u32 ctrlmenu[2] = { STR(0x4b23e4, "iftex/ctrlmenu01"), STR(0x4b23d0, "iftex/ctrlmenu02") }, laddermenu[2] = { STR(0x4b240c, "iftex/laddermenu01"), STR(0x4b23f8, "iftex/laddermenu02") };
	static const u32 spiral[6] = { STR(0x4b23c0, "iftex/spiral1"), STR(0x4b23b0, "iftex/spiral2"), STR(0x4b23a0, "iftex/spiral3"), STR(0x4b2390, "iftex/spiral4"), STR(0x4b2380, "iftex/spiral5"), STR(0x4b2370, "iftex/spiral6") };
	next_step();
	timer_waitFrames(2.0);
	for (int k = 0; k < 8; k++) {
		(g_introTextures)[k] = T(intro[k]);
		next_step();
	}
	for (int k = 0; k < 2; k++) {
		(g_menuFrameTextures)[k] = T(frames[k]);
		next_step();
	}
	for (int k = 0; k < 2; k++) {
		(g_mainMenuTextures)[k] = T(mainmenu[k]);
		(g_arenaMenuTextures)[k] = T(arenamenu[k]);
		next_step();
		(g_ctrlMenuTextures)[k] = T(ctrlmenu[k]);
		(g_ladderMenuTextures)[k] = T(laddermenu[k]);
		next_step();
	}
	for (int k = 0; k < 6; k++) {
		(g_spiralTextures)[k] = T(spiral[k]);
		next_step();
	}
	static const struct { u32 name, into; } rest[7] = {
		{ STR(0x4ad574, "iftex/gameconnect"), ADDR(g_gameConnectTexture) }, { STR(0x4b2360, "iftex/option"), ADDR(g_buttonTexture) }, { STR(0x4b2354, "iftex/mouse"), ADDR(g_cursorTexture) }, { STR(0x4b2344, "iftex/cylinder"), ADDR(g_ringBandTexture) },
		{ STR(0x4b2330, "iftex/cylinder_menu"), ADDR(g_cageTexture) }, { STR(0x4b2320, "iftex/menu34"), ADDR(g_menuTunnelTexture) }, { STR(0x4b255c, "iftex/character"), ADDR(g_characterTexture) },
	};
	for (int k = 0; k < 7; k++) {
		GAME_VAR(int, rest[k].into) = T(rest[k].name);
		next_step();
	}
}
#undef T

/* 0x430400: the start-up load: g_unusedStartupTable and the key latches (g_keySeen) cleared, the settings, tables and lists loaded,
   the text area the whole screen, the timer; DirectInput made once (g_directInputMade; failure: a message box, 0); unless
   g_launchedForNetGame the data files checked (failure: the message 0x4b04b0, 0); the sound (g_soundOn: it works; then the menu
   sounds); the pointer at 310, 230, the keys' table; the CD (failure: a message box, 0); the six texture banks (with the
   linear filtering and mipmap settings, g_cfgLinearFilter / g_cfgMipmaps) gathered into g_textureManager (g_textures), the font, four textures by name, the shape and
   skeleton files, the scene (0x2343acb bytes, constructed; 0 if not had) into g_scene, the sound table, the logo;
   then the camera and menu defaults. Returns 1 (0 on a failure) */
int (app_startupLoad)(void *instance)
{
	memset((void *)OBJ(g_unusedStartupTable), 0, 0x400);
	memset((void *)OBJ(g_keySeen), 0, 0x400);
	g_roomConnected = 0;
	net_clearServerSettings();
	reg_readServerSettings();
	math_initMathFunction();
	reg_readLadderSettings();
	mech_setDefault();
	data_loadCharacterProfiles();
	data_loadMapInfo();
	data_loadSkirmishInfo();
	arena_initOptionTexts();
	profile_scanSaves();
	font_initAsciiGrids();
	font_initHangulGrids();
	text_setWrapX(0x280);
	text_setBottom(0x1e0);
	g_textHitBottom = 0;
	timer_init();
	g_convertHangul = 1;
	g_leavingForMatch = 0;
	if (!g_directInputMade) {
		if (!input_createDirectInput(g_mainWindow, instance)) {
			MessageBoxA(g_mainWindow, (const char *)MSG(112, "DIRECT INPUT INIT FAILED"), (const char *)MSG(101, "ERROR"), 0);
			return 0;
		}
		g_directInputMade = 1;
	}
	if (!g_launchedForNetGame) {
		if (!app_checkFile_profeng() || !app_checkFile_profkor() || !app_checkFile_skirmish() || !app_checkFile_axisgame()
		    || !app_checkFile_game()) {
			sys_messageBox((const char *)STR(0x4b04b0, "Run AxisPlay.exe"));
			return 0;
		}
	}
	if (!sound_init(g_mainWindow))
		g_soundOn = 0;
	else {
		g_soundOn = 1;
		sound_loadMenuSounds();
	}
	g_mouseX = 0x136;
	g_mouseY = 0xe6;
	input_initScanCharTable();
	input_clearKeyTable2();
	(*(u32 *)&g_viewAngle) = 0x42340000;   /* 45 */
	if (!cd_findDrive()) {
		MessageBoxA(NULL, (const char *)STR(0x4b2528, "Please insert Axis CD in your CD-ROM ..."), (const char *)STR(0x4b2554, "Warning"), 0);
		return 0;
	}
	const char *dir = (const char *)STR(0x4b1304, ".");
	u32 linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture64x64), dir, 0x28, 0, 0x40, 0x40, linear, mipmaps);
	linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture128x64), dir, 0x28, 0, 0x80, 0x40, linear, mipmaps);
	linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture256x64), dir, 0x28, 0, 0x100, 0x40, linear, mipmaps);
	linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture128x128), dir, 0x28, 0, 0x80, 0x80, linear, mipmaps);
	linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture256x128), dir, 0x50, 0, 0x100, 0x80, linear, mipmaps);
	linear = g_cfgLinearFilter, mipmaps = g_cfgMipmaps;
	tex_initBy((void *)OBJ(g_texture256x256), dir, 0x28, 0, 0x100, 0x100, linear, mipmaps);
	TextureManager_setBanks((void *)ADDR(g_textureManager), (void *)OBJ(g_texture64x64), (void *)OBJ(g_texture128x64), (void *)OBJ(g_texture256x64), (void *)OBJ(g_texture128x128),
	                (void *)OBJ(g_texture256x128), (void *)OBJ(g_texture256x256));
	g_textures = (TextureManager *)ADDR(g_textureManager);
	pen_init((const char *)STR(0x4b2514, "Interface\\PenFont"));
	g_fontAscii = texture_named((const char *)STR(0x4b24c4, "iftex/english8"));
	g_fontAsciiLarge = texture_named((const char *)STR(0x4b24b4, "iftex/english16"));
	g_fontHanCho = texture_named((const char *)STR(0x4b24a4, "iftex/han_cho"));
	g_fontHanJungJong = texture_named((const char *)STR(0x4b2490, "iftex/han_jung_jong"));
	shapeDat_initBy();
	skelDat_initBy();
	void *scene = operator_new(0x2343acb);
	(*(void **)&g_scene) = scene ? Console_ctor(scene) : NULL;
	sound_initSoundTable((const char *)STR(0x4b2504, "Data/Sound.dat"), 0x64);
	char logo[64];
	strcpy(logo, (const char *)STR(0x4b24f0, "iftex/axis_title"));
	(*(u32 *)&g_menuEyeY) = 0;
	(*(u32 *)&g_menuEyeX) = 0;
	(*(u32 *)&g_menuEyeZ) = 0x43fa0000;   /* 500 */
	(*(u32 *)&g_menuCameraLook) = 0;
	(*(u32 *)&g_menuCameraLookY) = 0;
	(*(u32 *)&g_menuCameraLookZ) = 0x43c80000;   /* 400 */
	g_fpsFrameCount = 0;
	g_logoTexture = tex_getIdByName(g_textures, logo, 0, 0, 0, 0, 0, 0, 0);
	set_colour_bits(g_textColour, 0, 0x3f800000, 0, 0x3f800000);
	set_colour_bits(g_clearColour, 0, 0, 0, 0x3f800000);
	int width = g_screenW, height = g_screenH;
	(*(u32 *)&g_menuKeyGuard) = 0x40a00000;   /* 5 */
	g_menuScaleX = f32(fmul_m((long double)width, k_0_0015625f));
	g_screenCentreX = width / 2;
	g_unusedStartupWord1 = 0;
	g_menuScaleY = f32(fmul_m((long double)height, k_0_00208333f));
	g_dialogPending = 0;
	g_screenCentreY = height / 2;
	g_unusedStartupWord2 = 0;
	g_unusedStartupWord3 = 0;
	(*(u32 *)&g_emblemAlpha) = 0x3dcccccd;   /* 0.1 */
	(*(u32 *)&g_emblemAlphaStep) = 0x3ca3d70a;   /* 0.02 */
	(*(u32 *)&g_logoFade) = 0;
	g_cursorFrame = 0;
	(*(u32 *)&g_cursorFrameTime) = 0;
	g_inputLineHidden = 0;
	g_matchMode = 0;
	g_menuVolume = (g_soundVolume * 5 - 0x1f4) * 4;
	g_matchRunning = 0;
	return 1;
}

#define GS ((Scene *)g)   /* the same by its fields (src/scene.fields) */
#undef STAGE   /* (game.h's gives a Stage *; here the byte pointer) */
#define STAGE(g) ((u8 *)SCENE_STAGE(g))

/* the next stage: its line added to the loading screen (loadLines, loadLineCount) */
static void next_stage(u8 *g, int stage, u32 line)
{
	GS->loadStage = stage;
	strcpy(GS->loadLines[GS->loadLineCount++], (const char *)RELOC(line));
}

/* a game mode (+8) with no next stage: a fatal message */
static void no_next(u8 *g)
{
	sys_fatalErrorN((char *)OBJ(g_logConsole), (const char *)STR(0x4c5060, "next submode not defined(W%d:P%d:S%d)..."), GS->sessionMode, GS->matchState,
	                                                             GS->loadStage);
}

/* the host of a network game (mode 1, local player 0) that holds its slot (net_hasSlot) sends its game packet
   (net_sendGamePacket) while it loads */
static void keep_alive(u8 *g)
{
	if (GS->sessionMode == 1 && GS->localPlayer == 0 && net_hasSlot() == 1)
		net_sendGamePacket(g, GS->localPlayer);
}

/* the map's file name (mapName with .bfd) */
static char *bfd_name(u8 *g, char *out)
{
	sprintf(out, (const char *)STR(0x4c5190, "%s.bfd"), GS->mapName);
	return out;
}

/* 0x468750 (thiscall on the game object): one step of loading per call. The first (stateFrames 0) resets the
   loading lines to the title. By the stage (loadStage): 0 the replay file's header (mode 3: version 0x1201, the
   map, the players' names, the type), the stage reset (stage_reset); 1 the map named (g_mapIndex into g_mapNames: none ends it, g_mapMissing
   set); 2 waiting for the stage's play information (the network drained into net_processGamePacket; a timeout
   lostTime against K k_5f, 0x80 or more packets out of turn (netq_skippedCount) or the game menu keys (g_keyGameMenu)
   stop it); 3 the ground; 4 the objects; 5 the collision volume; 6 the crosshair and the play information; 7 the
   mission and (mode 0) the actors; 8 the game started (matchState by the mode). Each stage adds a line (the next
   depends on the mode +8); every step but the last draws the screen. Returns matchState, or 0 once Esc or the stop is
   seen or the map has no name */
u32 THISCALL (game_processLoadingMode)(u8 *g)
{
	char name[0x100], path[0x100];
	if (GS->stateFrames == 0) {
		(*(u8 * *)&g_loadGame) = g;
		g_loadStatusText[0] = 0;
		GS->loadLineCount = 1;
		strcpy(GS->loadLines[0], (const char *)STR(0x4c52b0, "START LOADING PROCESS"));
		GS->loadStage = 0;
		GS->unused233cc2c = 0;
	}
	int stop = input_asyncKeyPressed(0x1b) != 0;
	int mode;
	switch (GS->loadStage) {
	case 0:
		keep_alive(g);
		music_stop();
		if (GS->sessionMode == 3) {
			sprintf(path, (const char *)STR(0x4c52a4, "AutoPlay/%s"), GS->replayFiles[GS->replayIndex]);
			void *f = GS->replayFile = crt_fopen(path, (const char *)STR(0x4ad170, "rb"));
			if (!f)
				sys_fatalError((char *)OBJ(g_logConsole), (const char *)STR(0x4c5278, "can't open file %s - processAutoPlayM..."), (int)path);
			fread_scrambled(&GS->replayVersion, 4, 1, GS->replayFile);
			if (GS->replayVersion != 0x1201)
				sys_fatalError((char *)OBJ(g_logConsole), (const char *)STR(0x4c5234, "incorrect file version, remove the fi..."), (int)path);
			fread_scrambled((void *)ADDR(g_matchMode), 4, 1, GS->replayFile);
			fread_scrambled((void *)ADDR(g_mapIndex), 4, 1, GS->replayFile);
			fread_scrambled((void *)OBJ(g_gameTitle), 1, 0x20, GS->replayFile);
			fread_scrambled((void *)ADDR(g_mapRotation), 4, 1, GS->replayFile);
			fread_scrambled((void *)ADDR(g_chosenGameMode), 4, 1, GS->replayFile);
			fread_scrambled((void *)ADDR(g_fragLimit), 4, 1, GS->replayFile);
			fread_scrambled((void *)ADDR(g_timeLimit), 4, 1, GS->replayFile);
			game_setGameTypeFlags((Stage *)STAGE(g), g_chosenGameMode);
		}
		(*(u32 *)&g_logHook) = FN(loading_drawScreen);
		log_message((int)STAGE(g), -1, 0, (const char *)STR(0x4c521c, ".start loading process"));
		stage_reset(STAGE(g));
		mode = GS->sessionMode;
		if (mode == 3)
			next_stage(g, 1, STR(0x4c520c, ".LOAD AUTO PLAY"));   /* .LOAD AUTO PLAY */
		else if (mode >= 0 && mode <= 2)
			next_stage(g, 2, STR(0x4c51e4, ".INIT PLAY INFO"));   /* .INIT PLAY INFO */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 1: {
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c51f4, ".load auto-play file"));
		g_mapMissing = 0;
		const char *map = g_mapNames + g_mapIndex * 0x20;
		if (!map[0]) {
			g_mapMissing = 1;
			return 0;
		}
		scene_setMapName((Scene *)g, map);
		mode = GS->sessionMode;
		if (mode >= 0 && mode <= 3)
			next_stage(g, mode == 2 ? 6 : 2, STR(0x4c51e4, ".INIT PLAY INFO"));   /* .INIT PLAY INFO */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	}
	case 2:
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c51c0, ".receiving stage play information"));
		keep_alive(g);
		if (GS->awaitingHostRound == 0) {
			scene_setMapName((Scene *)g, g_mapNames + g_mapIndex * 0x20);
			mode = GS->sessionMode;
			if (mode == 0 || mode == 1 || mode == 3)
				next_stage(g, 3, STR(0x4c51b0, ".LOAD GROUND"));   /* .LOAD GROUND */
			else
				no_next(g);
			GS->unused233cc2c = 0;
			break;
		}
		{
			int from, size;
			u8 data[0x230];   /* (the original's buffer runs on into its path and name buffers) */
			int r;
			netq_poll();
			while ((r = netq_receive(&from, &size, data)) != 0) {
				if (r == 1)
					net_processGamePacket(g, from, size, data);
				GS->packetsReceived++;
				netq_poll();
			}
		}
		if (net_hasSlot() == 0) {
			long double t = FADD(GS->frameTime, GS->lostTime);
			GS->lostTime = f32(t);
			if (t > k_5f)
				stop = 1;
		}
		if (netq_skippedCount() >= 0x80)
			stop = 1;
		if (input_justPressed(g_keyGameMenu) || input_justPressed(g_keyGameMenu2))
			stop = 1;
		break;
	case 3:
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c5198, ".load zone information"));
		keep_alive(g);
		if (!map_loadGroundInfoFrom(STAGE(g), bfd_name(g, path)))
			sys_fatalErrorN((char *)OBJ(g_logConsole), (const char *)STR(0x4c4598, "file damaged!"));
		if (g_mapIndex != GS->mapNumber)
			sys_fatalErrorN((char *)OBJ(g_logConsole), (const char *)STR(0x4c4598, "file damaged!"));
		mode = GS->sessionMode;
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 4, STR(0x4c5180, ".LOAD OBJECT"));   /* .LOAD OBJECT */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 4:
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c5164, ".load obstacle information"));
		keep_alive(g);
		map_loadObjectInfoFrom(STAGE(g), bfd_name(g, path), 0);
		mode = GS->sessionMode;
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 5, STR(0x4c514c, ".SET COLLISION VOLUME"));   /* .SET COLLISION VOLUME */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 5:
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c512c, ".analyze collision information"));
		keep_alive(g);
		collision_initVolume(STAGE(g), 0x469c4000, 0x469c4000, 0x469c4000, 0x43fa0000, 0x10, 3);   /* cells of 20000 each way, margin 500, split at 16 items, depth 3 */
		mode = GS->sessionMode;
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 6, STR(0x4c511c, ".LOAD PLAY INFO"));   /* .LOAD PLAY INFO */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 6:
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c5104, ".analyze battle field"));
		keep_alive(g);
		sprintf(name, (const char *)STR(0x4c50e4, "Texture/Crosshair/Crosshair%d"), g_crosshairSetting);
		GS->crosshairTexture = tex_getIdByName((*(void **)&g_textures), name, 0, 0, 0, 0, 0, 0, 0);
		map_loadPlayInfoFrom(STAGE(g), bfd_name(g, path));
		mode = GS->sessionMode;
		if (mode >= 0 && mode <= 3)
			next_stage(g, mode <= 1 ? 7 : 8, STR(0x4c50a0, "END LOADING PROCESS"));   /* END LOADING PROCESS */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 7:
		keep_alive(g);
		log_message((int)STAGE(g), 1, 0, (const char *)STR(0x4c50c4, ".transmit mission objectives"));
		map_loadMissionInfoFrom(STAGE(g), bfd_name(g, path));
		if (GS->sessionMode == 0) {
			log_message((int)STAGE(g), 0, 0, (const char *)STR(0x4c50b4, "load actor info"));
			map_loadActorInfoFrom(STAGE(g), bfd_name(g, path));
		}
		mode = GS->sessionMode;
		if (mode >= 0 && mode <= 3)
			next_stage(g, 8, STR(0x4c50a0, "END LOADING PROCESS"));   /* END LOADING PROCESS */
		else
			no_next(g);
		GS->unused233cc2c = 0;
		break;
	case 8:
		log_message((int)STAGE(g), -2, 0, (const char *)STR(0x4c5048, ".end loading process"));
		keep_alive(g);
		music_playMatch((Scene *)g);
		GS->matchDrawing = 1;
		mode = GS->sessionMode;
		if (mode >= 0 && mode <= 3)
			GS->matchState = mode <= 1 ? 2 : mode == 2 ? 3 : 4;
		else
			no_next(g);
		GS->stateFrames = 0;
		(*(int *)&g_logHook) = 0;
		return ((u32)GS->matchState);
	}
	GS->stateFrames++;
	glClearColor_stored(((const u32[]){ 0, 0, 0 }));
	glClearDepth(1.0);
	glClear(0x4100);
	gfx_setMatchProjection(1, 1.0f);
	ViewVolume_captureMatrices((u8 *)&GS->view, 0, (u8 *)GS->modelview);
	ViewVolume_reset((u8 *)&GS->view);
	ViewVolume_draw((u8 *)&GS->view, GS->renderMode, 0.0f);
	gfx_setMatchProjection(0, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0, y = 8; k < GS->loadLineCount; k += 2, y += 16)   /* (every other line from the second, as the original steps) */
		font_penDraw(0x10, y, 0, GS->loadLines[k + 1]);
	return stop == 1 ? 0 : ((u32)GS->matchState);
}
#undef GS
#undef STAGE
