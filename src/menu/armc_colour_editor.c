/* armc_colour_editor.c: the ARM CENTER's colour editor: two colours (hue, saturation, value) for each of the slots
   (0x4dc4b8, six floats a slot: hue 1, saturation 1, value 1, hue 2, then saturation 2 and value 2 in -1 .. 1) */
#include "../game.h"
#include <string.h>

#define X0 GAME_VAR(int, 0x4dcc90)
#define Y0 GAME_VAR(int, 0x4dcc94)
#define X1 GAME_VAR(int, 0x4dcc98)
#define Y1 GAME_VAR(int, 0x4dcc9c)
#define K(addr) ((const float *)(addr))
#define g_slot GAME_VAR(int, 0x4dc4b0)
#define SLOT ((const float *)0x4dc4b8 + g_slot * 6)
#define glVertex(x, y) menu_vertex(x, y)

static const u32 *const bright = (const u32 *)0x4dbc58, *const dim = (const u32 *)0x4dc1d0;
#define TEXT(c) set_colour_bits((Colour *)0x76d438, (c)[0], (c)[1], (c)[2], (c)[3])

/* a hue (degrees) turned half way round */
static int turned(int h) { return h >= 0 && h < 180 ? h + 180 : h - 180; }
static long double turned_f(long double h)
{
	return h >= 0 && h < *K(0x4a945c) ? fadd_m(h, K(0x4a945c)) : fsub_m(h, K(0x4a945c));
}

/* a 0 .. 99 percentage */
static int percent(long double v)
{
	int p = ftol(fmul_m(v, K(0x4a93f4)));
	return p >= 100 ? 99 : p;
}

/* a -1 .. 1 value as a 0 .. 99 percentage */
static int half_percent(long double v)
{
	int p = ftol(fmul_m(fmul_m(fadd_m(v, K(0x4a9424)), K(0x4a93f4)), K(0x4a942c)));
	return p >= 100 ? 99 : p;
}

/* a colour line "<label> [<value>]" at y */
static void value_line(int k, int y, int value)
{
	char line[50] = { 0 }, number[50] = { 0 };
	strcpy(line, (const char *)(0x75d4a4 + k * 0x80));
	strcat(line, (const char *)0x4b037c);   /* " [" */
	sprintf(number, (const char *)0x4b0378, value);   /* "%d]" */
	strcat(line, number);
	text_draw8(X1 - 0xc0, y, line);
}

/* a slider's track from texture row t0 .. t1 at y .. y1 */
static void track(float t0, float t1, int y, int y1)
{
	glTexCoord2f(0.0f, t0);
	glVertex(X1 - 0xbc, y);
	glTexCoord2f(1.0f, t0);
	glVertex(X1 - 0x10, y);
	glTexCoord2f(1.0f, t1);
	glVertex(X1 - 0x10, y1);
	glTexCoord2f(0.0f, t1);
	glVertex(X1 - 0xbc, y1);
}

/* a saturation / value slider's bar, filled to pos (0 .. 1) from the left at y */
static void bar(float pos, int y)
{
	glTexCoord2f(0.0f, 0.9375f);
	glVertex(X1 - 0xba, y);
	glTexCoord2f(pos, 0.9375f);
	int x = ftol(fmul_m(fld_m(&pos), K(0x4a948c)));
	glVertex(X1 - x - 0xba, y);
	glTexCoord2f(pos, 1.0f);
	glVertex(X1 - x - 0xba, y + 0x10);
	glTexCoord2f(0.0f, 1.0f);
	glVertex(X1 - 0xba, y + 0x10);
}

/* a hue slider's marker at pos (0 .. 1) at y */
static void marker(float pos, int y)
{
	glTexCoord2f(0.0f, 0.8125f);
	int x = ftol(fmul_m(fld_m(&pos), K(0x4a9484)));
	glVertex(X1 - x - 0xbd, y);
	glTexCoord2f(0.03125f, 0.8125f);
	glVertex(X1 - x - 0xb5, y);
	glTexCoord2f(0.03125f, 0.875f);
	glVertex(X1 - x - 0xb5, y + 0x10);
	glTexCoord2f(0.0f, 0.875f);
	glVertex(X1 - x - 0xbd, y + 0x10);
}

/* 0x41a280: the colour editor: two boxes (0x75d3a4 / 0x75d424) of three lines each, the current slot's hue
   (turned half round, as 0 .. 50 by 0.278) and saturation and value (percent; the second colour's from -1 .. 1);
   the six slot buttons (the current one, 0x4dc4b0, bright; the sixth 0x756d24) with the parts' names beside them
   when 0x4dbc68 is set; the sliders' tracks, bars and hue markers; two buttons (0x7517a4; 3 / 4 under the pointer,
   by armc_40e4d0, lit) and the box "<0x756da4> <0x751924 name of 0x4dceac>". The original leaves eax to callers
   that ignore it */
void (armc_41a280)(void)
{
	int hovered = GAME_CDECL(0x40e4d0, int, int, int)(GAME_VAR(int, 0x4ded68), GAME_VAR(int, 0x4ded6c));   /* armc_40e4d0 */
	for (int box = 0; box < 2; box++) {
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
		menu_drawRect(X1 - 200, Y0 + 0x30 + box * 0xb0, X1, Y0 + 0xd0 + box * 0xb0, 1);
	}
	TEXT(bright);
	text_draw8b(X1 - 200, Y0 + 0x34, X1, (const char *)0x75d3a4);
	text_draw8b(X1 - 200, Y0 + 0xe4, X1, (const char *)0x75d424);
	for (int k = 0; k < 3; k++) {
		int y = Y0 + k * 0x30;
		int v1 = k == 0 ? ftol(fmul_m((long double)turned(ftol(fld_m(&SLOT[0]))), K(0x4a9490)))
		                : percent(fld_m(&SLOT[k]));
		value_line(k, y + 0x46, v1);
		int v2 = k == 0 ? ftol(fmul_m((long double)turned(ftol(fld_m(&SLOT[3]))), K(0x4a9490)))
		                : half_percent(fld_m(&SLOT[3 + k]));
		value_line(k, y + 0xf6, v2);
	}
	/* the slots */
	glEnable(GL_TEXTURE_2D);
	int texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 6; k++) {
		glColor4f(1.0f, 1.0f, 1.0f, g_slot == k ? 0.8f : 0.4f);
		profile_4283e0(X0 + 0x10, Y0 + k * 0x30 + 0x40, X0 + 0xb0, Y0 + k * 0x30 + 0x6c, 1);
	}
	for (int k = 0; k < 6; k++) {
		if (g_slot == k)
			TEXT(bright);
		else
			TEXT(dim);
		if (k == 5)
			text_drawBox16(X0 + 0x10, Y0 + 0x13d, X0 + 0xb0, (const char *)0x756d24);
		else
			text_draw8(X0 + 0x18, Y0 + k * 0x30 + 0x44, (const char *)(0x756aa4 + k * 0x80));
	}
	if (GAME_VAR(int, 0x4dbc68)) {
		static const u32 names[5] = { 0x4dceb8, 0x4dbc08, 0x4dc250, 0x4dc1e8, 0x4dce40 };
		TEXT(bright);
		for (int k = 0; k < 5; k++)
			text_draw8(X0 + 0x28, Y0 + 0x54 + k * 0x30, (const char *)names[k]);
	}
	/* the sliders' tracks: the hue's rainbow, saturation and value plain */
	glEnable(GL_TEXTURE_2D);
	texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	for (int k = 0; k < 3; k++)
		if (k == 0) {
			track(0.125f, 0.25f, Y0 + 0x53, Y0 + 0x73);
			track(0.125f, 0.25f, Y0 + 0x103, Y0 + 0x123);
		} else {
			track(0.875f, 0.9375f, Y0 + k * 0x30 + 0x5a, Y0 + k * 0x30 + 0x6a);
			track(0.875f, 0.9375f, Y0 + k * 0x30 + 0x10a, Y0 + k * 0x30 + 0x11a);
		}
	glEnd();
	/* their positions */
	glBegin(GL_QUADS);
	for (int k = 0; k < 3; k++) {
		float pos1, pos2;
		if (k == 0) {
			long double h1 = turned_f(fld_m(&SLOT[0]));
			long double h2 = turned_f(fld_m(&SLOT[3]));
			pos1 = f32(fmul_m(h1, K(0x4a9488)));
			pos2 = f32(fmul_m(h2, K(0x4a9488)));
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			marker(pos1, Y0 + 0x5a);
			marker(pos2, Y0 + 0x10a);
		} else {
			pos1 = SLOT[k];
			pos2 = f32(fmul_m(fadd_m(fld_m(&SLOT[3 + k]), K(0x4a9424)), K(0x4a942c)));
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			bar(pos1, Y0 + k * 0x30 + 0x5a);
			bar(pos2, Y0 + k * 0x30 + 0x10a);
		}
	}
	glEnd();
	for (int k = 0; k < 2; k++) {
		glColor4f(1.0f, 1.0f, 1.0f, hovered == k + 3 ? 0.8f : 0.4f);
		menu_drawTexQuad_4282f0(X0 + k * 0x64 + 0x10, Y1 - 0x20, X0 + k * 0x64 + 0x70, Y1, 1);
	}
	for (int k = 0; k < 2; k++) {
		if (hovered == k + 3)
			TEXT(bright);
		else
			TEXT(dim);
		text_drawBox16(X0 + k * 0x64 + 0x10, Y1 - 0x18, X0 + k * 0x64 + 0x70, (const char *)(0x7517a4 + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	texture = GAME_VAR(int, 0x9db0a4);
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	menu_drawTexQuad_4282f0(X1 - 0xa0, Y1 - 0x20, X1, Y1, 1);
	TEXT(bright);
	char text[50] = { 0 };
	strcpy(text, (const char *)0x756da4);
	strcat(text, (const char *)0x4b035c);   /* " " */
	strcat(text, (const char *)(0x751924 + GAME_VAR(int, 0x4dceac) * 0x80));
	text_drawBox16(X1 - 0xa0, Y1 - 0x18, X1, text);
}
