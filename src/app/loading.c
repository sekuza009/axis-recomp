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
