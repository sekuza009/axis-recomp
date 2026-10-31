/* loading.c: the loading screen between the menus and a match: a progress bar under a text, faded in from black and
   out to black. */
#include "../game.h"
#include <string.h>

#define g_loadTimer ((void *)0xa0e948)                /* its own game-time timer */
#define g_loadProgress GAME_VAR(float, 0xa0ea88)
#define g_loadText ((char *)0xa0e988)
#define g_loadTexture GAME_VAR(int, 0xa0e980)         /* the backdrop's texture id */
#define g_loadFade GAME_VAR(float, 0xa0e984)          /* the fade's time, 0 .. 1 s */
#define ONE GAME_VAR(float, 0x4a9424)

/* one frame of a fade: the screen at its progress, under a black quad (alpha 1 - time fading in, time fading out),
   the fade's time advanced */
static void fade_frame(int in)
{
	loading_draw_bits(BITS(g_loadProgress));
	if (in)
		glColor4f(1.0f, 1.0f, 1.0f, fsub_m(fld_m(&ONE), &g_loadFade));
	else
		glColor4f_bits(0x3f800000, 0x3f800000, 0x3f800000, BITS(g_loadFade));
	int h = gfx_getHeight();
	gfx_fillRect(0, 0, gfx_getWidth(), h);
	g_loadFade = fadd_m(timer_getGameTime(g_loadTimer), &g_loadFade);
	gfx_swapBuffers();
}

/* 0x469730 (mode, unused, text): the loading screen. -1: the progress reset, the text set, the backdrop looked up,
   then a fade from black over one second of game time; -2: the progress advanced by the time since the last call,
   the text set, then a fade to black; any other mode: the progress advanced (the text set when 1) and one frame */
void (loading_drawCylinder)(int mode, int unused, const char *text)
{
	(void)unused;
	long double dt = timer_getGameTime(g_loadTimer);
	if (mode == -2) {
		g_loadProgress = fadd_m(dt, &g_loadProgress);
		strcpy(g_loadText, text);
		BITS(g_loadFade) = 0;
		do
			fade_frame(0);
		while (!(g_loadFade >= ONE));
		return;
	}
	if (mode == -1) {
		BITS(g_loadProgress) = 0;
		strcpy(g_loadText, text);
		g_loadTexture = tex_getIdByName(g_textures, (const char *)0x4c533c, 0, 0, 0, 0, 0, 0, 0);
		BITS(g_loadFade) = 0;
		do
			fade_frame(1);
		while (!(g_loadFade >= ONE));
		return;
	}
	g_loadProgress = fadd_m(dt, &g_loadProgress);
	if (mode == 1)
		strcpy(g_loadText, text);
	loading_draw_bits(BITS(g_loadProgress));
	gfx_swapBuffers();
}

#define glTexCoord2f_bits(s, t) IMPORT(0x4a920c, void, u32, u32)(s, t)
#define Vec3_rotateAxis(v, axis, angle) GAME_THISCALL(0x4677c0, void, float *, int, int)(v, axis, angle)   /* angle in tenths of a degree */
#define g_loadGame GAME_VAR(u8 *, 0xa0ea8c)            /* the game being loaded */

/* a point of the cylinder: radius 400 about the z axis at angle (tenths of a degree), at depth z */
static void cylinder_vertex(int angle, u32 z)
{
	u32 v[3] = { 0, 0x43c80000, z };   /* (0, 400, z) */
	Vec3_rotateAxis((float *)v, 0, angle);
	glVertex3fv((const float *)v);
}

/* one line of the loading screen's text at row (16 pixels a row) */
static void info_line(int row, const char *text)
{
	text_drawSized(0x96, row * 16 + 0x46, text, 0x10);
}

/* 0x469320 (progress, as bits): the loading screen: cleared to blue, the backdrop (0xa0e980) on the inside of a
   cylinder of 18 segments, 25133 deep, its texture's v running from the progress to the progress + 10; then in
   yellow the game's title (game modes 1 / 3), zone, play type (both "on receiving" while +0x1f1cb0 is 1), frag and
   time limits, and in grey the status line 0xa0e988 */
void (loading_draw)(u32 progress)
{
	IMPORT(0x4a91e0, void, u32, u32, u32, u32)(0x3f000000, 0x3f000000, 0x3f800000, 0x3f800000);   /* glClearColor(0.5, 0.5, 1, 1) */
	glClearDepth(1.0);
	glClear(0x4100);   /* GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT */
	GAME_CDECL(0x4685f0, void, int, u32)(1, 0x3f800000);   /* gfx_setProjectionHud(1, 1.0) */
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0xa0e980);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(0.5f, 0.5f, 1.0f, 0.5f);
	float far = f32(fadd_m(fld_m((const float *)&progress), (const float *)0x4a9418));   /* progress + 10 */
	for (int angle = 0, j = 0; angle < 0xfd20; angle += 0xe10, j++) {
		glBegin(GL_QUADS);
		float s0 = f32(fmul_m((long double)j, (const float *)0x4aa26c));        /* j / 18 */
		glTexCoord2f_bits(BITS(s0), progress);
		cylinder_vertex(angle / 18, 0);
		float s1 = f32(fmul_m((long double)(j + 1), (const float *)0x4aa26c));
		glTexCoord2f_bits(BITS(s1), progress);
		cylinder_vertex((angle + 0xe10) / 18, 0);
		glTexCoord2f_bits(BITS(s1), BITS(far));
		cylinder_vertex((angle + 0xe10) / 18, 0xc6c4597c);   /* -25132.74 */
		glTexCoord2f_bits(BITS(s0), BITS(far));
		cylinder_vertex(angle / 18, 0xc6c4597c);
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	GAME_CDECL(0x4685f0, void, int, u32)(0, 0x3f800000);
	text_setColor(1.0f, 1.0f, 0.0f, 1.0f);
	char line[0x100];
	int row = 2;
	int mode = *(int *)(g_loadGame + 8);
	if (mode == 1 || mode == 3) {
		sprintf(line, (const char *)0x4c5330, (const char *)0x67fb44);   /* "TITLE : %s" */
		info_line(row, line);
		row = 4;
	}
	if (*(int *)(g_loadGame + 0x1f1cb0) == 1)
		sprintf(line, (const char *)0x4c531c);
	else
		sprintf(line, (const char *)0x4c5310, (const char *)(0x907b30 + GAME_VAR(int, 0x9dad94) * 32));   /* "ZONE : %s" */
	info_line(row, line);
	row += 2;
	if (*(int *)(g_loadGame + 0x1f1cb0) == 1)
		sprintf(line, (const char *)0x4c52f8);
	else
		sprintf(line, (const char *)0x4c52e8, (const char *)(0x4c7030 + *(int *)(g_loadGame + 0x22e7180) * 64));   /* "PLAY TYPE : %s" */
	info_line(row, line);
	row += 2;
	sprintf(line, (const char *)0x4c52d8, GAME_VAR(int, 0x4df8e8));   /* "FRAG LIMIT : %d" */
	info_line(row, line);
	row += 2;
	sprintf(line, (const char *)0x4c52c8, GAME_VAR(int, 0x76d408));   /* "TIME LIMIT : %d" */
	info_line(row, line);
	text_setColor(0.5f, 0.5f, 0.5f, 1.0f);
	text_drawSized(0x96, row * 16 + 0x76, (const char *)0xa0e988, 0x10);
}

/* ---- the game's start-up load ---- */
#define g_mainWindow GAME_VAR(void *, 0x4ded18)

/* a texture's id by its name (copied to the stack first, as the original does) */
static int texture_named(const char *name)
{
	char copy[64];
	strcpy(copy, name);
	return tex_getIdByName(g_textures, copy, 0, 0, 0, 0, 0, 0, 0);
}

/* ---- the menus' textures, loaded with the loading screen moved on a step (g_loadStep) between them ---- */
#define g_loadStep GAME_VAR(int, 0x4dda34)
#define T(addr) texture_named((const char *)(addr))

static void next_step(void)
{
	g_loadStep++;
	frontEnd_drawProgress();
}

/* 0x430ca0: the menus' textures by name: the intro frames ("iftex/m_intro1" .. 4, "m2_intro1" .. 4 into 0x9dad6c),
   the corner and box screen (0x4deb4c), the main, arena, control and ladder menus' pairs (0x76d478 / 0x4df040 /
   0x5b1978 / 0x4df904), the six spirals (0x9da45c), then "gameconnect" (0x4df450), "option" (0x9db0a4, the
   buttons), "mouse" (0x4e152c), "cylinder" (0x4e186c), "cylinder_menu" (0x76d36c), "menu34" (0x4e0cd0, the tunnel)
   and "character" (0x4dfa00); first a step and a wait of 2 */
void (menu_loadIntroTextures)(void)
{
	static const u32 intro[8] = { 0x4b25dc, 0x4b25cc, 0x4b25bc, 0x4b25ac, 0x4b259c, 0x4b258c, 0x4b257c, 0x4b256c };
	static const u32 frames[2] = { 0x4b2480, 0x4b2470 };   /* corner, boxscreen */
	static const u32 mainmenu[2] = { 0x4b245c, 0x4b2448 }, arenamenu[2] = { 0x4b2434, 0x4b2420 };
	static const u32 ctrlmenu[2] = { 0x4b23e4, 0x4b23d0 }, laddermenu[2] = { 0x4b240c, 0x4b23f8 };
	static const u32 spiral[6] = { 0x4b23c0, 0x4b23b0, 0x4b23a0, 0x4b2390, 0x4b2380, 0x4b2370 };
	next_step();
	timer_waitFrames(2.0);
	for (int k = 0; k < 8; k++) {
		((int *)0x9dad6c)[k] = T(intro[k]);
		next_step();
	}
	for (int k = 0; k < 2; k++) {
		((int *)0x4deb4c)[k] = T(frames[k]);
		next_step();
	}
	for (int k = 0; k < 2; k++) {
		((int *)0x76d478)[k] = T(mainmenu[k]);
		((int *)0x4df040)[k] = T(arenamenu[k]);
		next_step();
		((int *)0x5b1978)[k] = T(ctrlmenu[k]);
		((int *)0x4df904)[k] = T(laddermenu[k]);
		next_step();
	}
	for (int k = 0; k < 6; k++) {
		((int *)0x9da45c)[k] = T(spiral[k]);
		next_step();
	}
	static const struct { u32 name, into; } rest[7] = {
		{ 0x4ad574, 0x4df450 }, { 0x4b2360, 0x9db0a4 }, { 0x4b2354, 0x4e152c }, { 0x4b2344, 0x4e186c },
		{ 0x4b2330, 0x76d36c }, { 0x4b2320, 0x4e0cd0 }, { 0x4b255c, 0x4dfa00 },
	};
	for (int k = 0; k < 7; k++) {
		GAME_VAR(int, rest[k].into) = T(rest[k].name);
		next_step();
	}
}
#undef T

/* 0x430400: the start-up load: the key tables (0x4d1688, 0x4d1a98) cleared, the settings, tables and lists loaded,
   the text area the whole screen, the timer; DirectInput made once (0x9dbf0c; failure: a message box, 0); unless
   0x76d410 the data files checked (failure: the message 0x4b04b0, 0); the sound (0xa0e80c: it works; then the menu
   sounds); the pointer at 310, 230, the keys' table; the CD (failure: a message box, 0); the six texture sets (the
   sizes 0x83a9cc / 0x83a9d0) gathered into 0x83a5e0 (g_textures), the font, four textures by name, the shape and
   skeleton files, the scene (0x2343acb bytes, constructed; 0 if not had) into 0x9087b4, the sound table, the logo;
   then the camera and menu defaults. Returns 1 (0 on a failure) */
int (app_checkCdAndLoad)(void *instance)
{
	memset((void *)0x4d1688, 0, 0x400);
	memset((void *)0x4d1a98, 0, 0x400);
	GAME_VAR(int, 0x9dd84c) = 0;
	app_4515d0();
	reg_readServerSettings();
	math_initMathFunction();
	reg_readCharacterSettings();
	app_430390();
	data_loadPilotProfiles();
	data_loadMapInfo();
	data_loadSkirmishInfo();
	arena_42bc00();
	profile_scanSaves();
	app_42f940();
	hud_42fb40();
	skirmish_4017b0(0x280);
	skirmish_4017c0(0x1e0);
	GAME_VAR(int, 0x4d7348) = 0;
	timer_init();
	GAME_VAR(int, 0x4d23d0) = 1;
	GAME_VAR(int, 0x67ef14) = 0;
	if (!GAME_VAR(int, 0x9dbf0c)) {
		if (!input_createDirectInput(g_mainWindow, instance)) {
			MessageBoxA(g_mainWindow, (const char *)0x751624, (const char *)0x7510a4, 0);
			return 0;
		}
		GAME_VAR(int, 0x9dbf0c) = 1;
	}
	if (!GAME_VAR(int, 0x76d410)) {
		if (!app_checkFile_profeng() || !app_checkFile_profkor() || !app_checkFile_skirmish() || !app_checkFile_axisgame()
		    || !app_checkFile_game()) {
			sys_messageBox((const char *)0x4b04b0);
			return 0;
		}
	}
	if (!sound_init(g_mainWindow))
		GAME_VAR(int, 0xa0e80c) = 0;
	else {
		GAME_VAR(int, 0xa0e80c) = 1;
		sound_loadMenuSounds();
	}
	GAME_VAR(int, 0x4ded68) = 0x136;
	GAME_VAR(int, 0x4ded6c) = 0xe6;
	input_initVkTable();
	app_401780();
	GAME_VAR(u32, 0x68038c) = 0x42340000;   /* 45 */
	if (!cd_findDrive()) {
		MessageBoxA(NULL, (const char *)0x4b2528, (const char *)0x4b2554, 0);
		return 0;
	}
	const char *dir = (const char *)0x4b1304;
	u32 w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x4e1878, dir, 0x28, 0, 0x40, 0x40, w, h);
	w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x5b1db8, dir, 0x28, 0, 0x80, 0x40, w, h);
	w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x680cd8, dir, 0x28, 0, 0x100, 0x40, w, h);
	w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x76d498, dir, 0x28, 0, 0x80, 0x80, w, h);
	w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x90d1e0, dir, 0x50, 0, 0x100, 0x80, w, h);
	w = GAME_VAR(u32, 0x83a9cc), h = GAME_VAR(u32, 0x83a9d0);
	tex_initBy((void *)0x83a9e0, dir, 0x28, 0, 0x100, 0x100, w, h);
	texSmall_initBy((void *)0x83a5e0, (void *)0x4e1878, (void *)0x5b1db8, (void *)0x680cd8, (void *)0x76d498,
	                (void *)0x90d1e0, (void *)0x83a9e0);
	g_textures = (TextureSets *)0x83a5e0;
	pen_init((const char *)0x4b2514);
	GAME_VAR(int, 0x76d448) = texture_named((const char *)0x4b24c4);
	GAME_VAR(int, 0x9dad90) = texture_named((const char *)0x4b24b4);
	GAME_VAR(int, 0x9dae1c) = texture_named((const char *)0x4b24a4);
	GAME_VAR(int, 0x76d360) = texture_named((const char *)0x4b2490);
	shapeDat_initBy();
	skelDat_initBy();
	void *scene = operator_new(0x2343acb);
	GAME_VAR(void *, 0x9087b4) = scene ? game_loadAllData(scene) : NULL;
	sound_initSoundTable((const char *)0x4b2504, 0x64);
	char logo[64];
	strcpy(logo, (const char *)0x4b24f0);
	GAME_VAR(u32, 0x4df028) = 0;
	GAME_VAR(u32, 0x4df024) = 0;
	GAME_VAR(u32, 0x4df02c) = 0x43fa0000;   /* 500 */
	GAME_VAR(u32, 0x680378) = 0;
	GAME_VAR(u32, 0x68037c) = 0;
	GAME_VAR(u32, 0x680380) = 0x43c80000;   /* 400 */
	GAME_VAR(int, 0x4dd0b0) = 0;
	GAME_VAR(int, 0x76d3f0) = tex_getIdByName(g_textures, logo, 0, 0, 0, 0, 0, 0, 0);
	set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0, 0x3f800000);
	set_colour_bits((Colour *)0x76d350, 0, 0, 0, 0x3f800000);
	int width = GAME_VAR(int, 0x5b1998), height = GAME_VAR(int, 0x4e045c);
	GAME_VAR(u32, 0x9da434) = 0x40a00000;   /* 5 */
	GAME_VAR(float, 0x680bac) = f32(fmul_m((long double)width, (const float *)0x4a9578));
	GAME_VAR(int, 0x4e1520) = width / 2;
	GAME_VAR(int, 0x76d474) = 0;
	GAME_VAR(float, 0x4df014) = f32(fmul_m((long double)height, (const float *)0x4a9574));
	GAME_VAR(int, 0x4df900) = 0;
	GAME_VAR(int, 0x680394) = height / 2;
	GAME_VAR(u32, 0x4dd96c) = 0;
	GAME_VAR(int, 0x4dd0b8) = 0;
	GAME_VAR(u32, 0x4de1e0) = 0x3dcccccd;   /* 0.1 */
	GAME_VAR(u32, 0x4de1d8) = 0x3ca3d70a;   /* 0.02 */
	GAME_VAR(u32, 0x4de1e8) = 0;
	GAME_VAR(int, 0x4df03c) = 0;
	GAME_VAR(u32, 0x4df910) = 0;
	GAME_VAR(int, 0x4e1868) = 0;
	GAME_VAR(int, 0x5ae9c4) = 0;
	GAME_VAR(int, 0x4dd984) = (GAME_VAR(int, 0x4e0c90) * 5 - 0x1f4) * 4;
	GAME_VAR(int, 0x5b1dac) = 0;
	return 1;
}

#define G(type, offset) GAME_VAR(type, g + (offset))
#define STAGE(g) ((g) + 0x1f36c8)

/* the next stage: its line added to the loading screen (+0x233cc60, 0x100 a line, +0x2340c60 of them) */
static void next_stage(u8 *g, int stage, u32 line)
{
	G(int, 0x233cc24) = stage;
	strcpy((char *)g + 0x233cc60 + G(int, 0x2340c60)++ * 0x100, (const char *)line);
}

/* a game mode (+8) with no next stage: a fatal message */
static void no_next(u8 *g)
{
	GAME_CDECL(0x46c710, void, char *, const char *, int, int, int)((char *)0xa0e778, (const char *)0x4c5060, G(int, 8), G(int, 0x233cc20),
	                                                             G(int, 0x233cc24));
}

/* a network client (mode 1, local player 0) that is online keeps the host told it is still loading */
static void keep_alive(u8 *g)
{
	if (G(int, 8) == 1 && G(int, 0x234240d) == 0 && FUN_004a86d0() == 1)
		net_sendGamePacket(g, G(int, 0x234240d));
}

/* the map's file name (+0x1f35c8 with .bfd) */
static char *bfd_name(u8 *g, char *out)
{
	sprintf(out, (const char *)0x4c5190, (const char *)g + 0x1f35c8);
	return out;
}

/* 0x468750 (thiscall on the game object): one step of loading per call. The first (+0x233cc28 0) resets the
   loading lines to the title. By the stage (+0x233cc24): 0 the replay file's header (mode 3: version 0x1201, the
   map, the players' names, the type), the scene reset; 1 the map named (0x9dad94 into 0x907b30: none ends it, 0xa0ea94
   set); 2 waiting for the stage's play information (the network drained into net_processGamePacket; a timeout
   +0x2342395 against K 0x4a93d0, too many players or the stop keys 0x4defc8 / 0x4defcc stop it); 3 the ground; 4 the
   objects; 5 the collision volume; 6 the crosshair and the play information; 7 the mission and (mode 0) the actors; 8
   the game started (+0x233cc20 by the mode). Each stage adds a line (the next depends on the mode +8); every step but
   the last draws the screen. Returns +0x233cc20, or 0 once Esc or the stop is seen or the map has no name */
u32 THISCALL (game_processLoadingMode)(u8 *g)
{
	char name[0x100], path[0x100];
	if (G(int, 0x233cc28) == 0) {
		GAME_VAR(u8 *, 0xa0ea8c) = g;
		GAME_VAR(u8, 0xa0e988) = 0;
		G(int, 0x2340c60) = 1;
		strcpy((char *)g + 0x233cc60, (const char *)0x4c52b0);
		G(int, 0x233cc24) = 0;
		G(int, 0x233cc2c) = 0;
	}
	int stop = input_asyncKeyPressed(0x1b) != 0;
	int mode;
	switch (G(int, 0x233cc24)) {
	case 0:
		keep_alive(g);
		music_shutdown();
		if (G(int, 8) == 3) {
			sprintf(path, (const char *)0x4c52a4, (const char *)g + 0x1f1cbc + G(int, 0x1f35c0) * 0x40);
			void *f = G(void *, 0x2340d08) = crt_fopen(path, (const char *)0x4ad170);
			if (!f)
				sys_fatalError((char *)0xa0e778, (const char *)0x4c5278, (int)path);
			fread_scrambled(g + 0x1f35c4, 4, 1, G(void *, 0x2340d08));
			if (G(int, 0x1f35c4) != 0x1201)
				sys_fatalError((char *)0xa0e778, (const char *)0x4c5234, (int)path);
			fread_scrambled((void *)0x5ae9c4, 4, 1, G(void *, 0x2340d08));
			fread_scrambled((void *)0x9dad94, 4, 1, G(void *, 0x2340d08));
			fread_scrambled((void *)0x67fb44, 1, 0x20, G(void *, 0x2340d08));
			fread_scrambled((void *)0x9da3e0, 4, 1, G(void *, 0x2340d08));
			fread_scrambled((void *)0x76d368, 4, 1, G(void *, 0x2340d08));
			fread_scrambled((void *)0x4df8e8, 4, 1, G(void *, 0x2340d08));
			fread_scrambled((void *)0x76d408, 4, 1, G(void *, 0x2340d08));
			game_setGameTypeFlags((Stage *)STAGE(g), GAME_VAR(int, 0x76d368));
		}
		GAME_VAR(u32, 0xae2ec8) = 0x469730;
		log_message((int)STAGE(g), -1, 0, (const char *)0x4c521c);
		scene_reset(STAGE(g));
		mode = G(int, 8);
		if (mode == 3)
			next_stage(g, 1, 0x4c520c);   /* .LOAD AUTO PLAY */
		else if (mode >= 0 && mode <= 2)
			next_stage(g, 2, 0x4c51e4);   /* .INIT PLAY INFO */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 1: {
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c51f4);
		GAME_VAR(int, 0xa0ea94) = 0;
		const char *map = (const char *)0x907b30 + GAME_VAR(int, 0x9dad94) * 0x20;
		if (!map[0]) {
			GAME_VAR(int, 0xa0ea94) = 1;
			return 0;
		}
		scene_setTextureFolder((Scene *)g, map);
		mode = G(int, 8);
		if (mode >= 0 && mode <= 3)
			next_stage(g, mode == 2 ? 6 : 2, 0x4c51e4);   /* .INIT PLAY INFO */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	}
	case 2:
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c51c0);
		keep_alive(g);
		if (G(int, 0x1f1cb0) == 0) {
			scene_setTextureFolder((Scene *)g, (const char *)0x907b30 + GAME_VAR(int, 0x9dad94) * 0x20);
			mode = G(int, 8);
			if (mode == 0 || mode == 1 || mode == 3)
				next_stage(g, 3, 0x4c51b0);   /* .LOAD GROUND */
			else
				no_next(g);
			G(int, 0x233cc2c) = 0;
			break;
		}
		{
			int from, size;
			u8 data[0x230];   /* (the original's buffer runs on into its path and name buffers) */
			int r;
			FUN_004a8350();
			while ((r = FUN_004a8450(&from, &size, data)) != 0) {
				if (r == 1)
					net_processGamePacket(g, from, size, data);
				G(int, 0x2340c7c)++;
				FUN_004a8350();
			}
		}
		if (FUN_004a86d0() == 0) {
			long double t = fadd_m(fld_m((const float *)(g + 0x44)), (const float *)(g + 0x2342395));
			G(float, 0x2342395) = f32(t);
			if (t > *(const float *)0x4a93d0)
				stop = 1;
		}
		if (FUN_004a8730() >= 0x80)
			stop = 1;
		if (input_justPressed(GAME_VAR(int, 0x4defc8)) || input_justPressed(GAME_VAR(int, 0x4defcc)))
			stop = 1;
		break;
	case 3:
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c5198);
		keep_alive(g);
		if (!map_loadGroundInfoFrom(STAGE(g), bfd_name(g, path)))
			GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa0e778, (const char *)0x4c4598);
		if (GAME_VAR(int, 0x9dad94) != G(int, 0xbe3000))
			GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xa0e778, (const char *)0x4c4598);
		mode = G(int, 8);
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 4, 0x4c5180);   /* .LOAD OBJECT */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 4:
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c5164);
		keep_alive(g);
		map_loadObjectInfoFrom(STAGE(g), bfd_name(g, path), 0);
		mode = G(int, 8);
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 5, 0x4c514c);   /* .SET COLLISION VOLUME */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 5:
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c512c);
		keep_alive(g);
		collision_initVolume(STAGE(g), 0x469c4000, 0x469c4000, 0x469c4000, 0x43fa0000, 0x10, 3);   /* 20000 cubed, cells of 500 */
		mode = G(int, 8);
		if (mode == 0 || mode == 1 || mode == 3)
			next_stage(g, 6, 0x4c511c);   /* .LOAD PLAY INFO */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 6:
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c5104);
		keep_alive(g);
		sprintf(name, (const char *)0x4c50e4, GAME_VAR(int, 0x4df00c));
		G(int, 0x233c9f8) = tex_getIdByName(GAME_VAR(void *, 0xa0e010), name, 0, 0, 0, 0, 0, 0, 0);
		map_loadPlayInfoFrom(STAGE(g), bfd_name(g, path));
		mode = G(int, 8);
		if (mode >= 0 && mode <= 3)
			next_stage(g, mode <= 1 ? 7 : 8, 0x4c50a0);   /* END LOADING PROCESS */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 7:
		keep_alive(g);
		log_message((int)STAGE(g), 1, 0, (const char *)0x4c50c4);
		map_loadMissionInfoFrom(STAGE(g), bfd_name(g, path));
		if (G(int, 8) == 0) {
			log_message((int)STAGE(g), 0, 0, (const char *)0x4c50b4);
			map_loadActorInfoFrom(STAGE(g), bfd_name(g, path));
		}
		mode = G(int, 8);
		if (mode >= 0 && mode <= 3)
			next_stage(g, 8, 0x4c50a0);   /* END LOADING PROCESS */
		else
			no_next(g);
		G(int, 0x233cc2c) = 0;
		break;
	case 8:
		log_message((int)STAGE(g), -2, 0, (const char *)0x4c5048);
		keep_alive(g);
		music_playMatch((Scene *)g);
		G(int, 0x233c9e8) = 1;
		mode = G(int, 8);
		if (mode >= 0 && mode <= 3)
			G(int, 0x233cc20) = mode <= 1 ? 2 : mode == 2 ? 3 : 4;
		else
			no_next(g);
		G(int, 0x233cc28) = 0;
		GAME_VAR(int, 0xae2ec8) = 0;
		return G(u32, 0x233cc20);
	}
	G(int, 0x233cc28)++;
	glClearColor_stored(((const u32[]){ 0, 0, 0 }));
	glClearDepth(1.0);
	glClear(0x4100);
	gfx_setProjectionHud(1, 1.0f);
	ViewVolume_captureMatrices(g + 0x74, 0, g + 0x22e7068);
	ViewVolume_reset(g + 0x74);
	render_drawObjects(g + 0x74, G(int, 0x1f1664), 0.0f);
	gfx_setProjectionHud(0, 1.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0, y = 8; k < G(int, 0x2340c60); k += 2, y += 16)   /* (every other line from the second, as the original steps) */
		font_penDraw(0x10, y, 0, (const char *)g + 0x233cc60 + (k + 1) * 0x100);
	return stop == 1 ? 0 : G(u32, 0x233cc20);
}
#undef G
#undef STAGE
