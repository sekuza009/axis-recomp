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
