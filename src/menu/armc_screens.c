/* armc_screens.c: two of the ARM CENTER's screens: the build screen (the part slots, the part box and its stats) and
   the colour editor (two colours, hue, saturation and value, for each of the slots at 0x4dc4b8, six floats a slot:
   hue 1, saturation 1, value 1, hue 2, then saturation 2 and value 2 in -1 .. 1) */
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

/* the box at the bottom right: "<0x756da4> <the name of 0x4dceac (0x751924)>" (the texture bound) */
static void mode_box(void)
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	menu_drawWideButton(X1 - 0xa0, Y1 - 0x20, X1, Y1, 1);
	TEXT(bright);
	char text[50] = { 0 };
	strcpy(text, (const char *)0x756da4);
	strcat(text, (const char *)0x4b035c);   /* " " */
	strcat(text, (const char *)(0x751924 + g_armcSpin * 0x80));
	text_drawBox16(X1 - 0xa0, Y1 - 0x18, X1, text);
}

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
   by armcColour_hitTest, lit) and the box "<0x756da4> <0x751924 name of 0x4dceac>". The original leaves eax to callers
   that ignore it */
void (armc_drawColourEditor)(void)
{
	int hovered = GAME_CDECL(0x40e4d0, int, int, int)(g_mouseX, g_mouseY);   /* armcColour_hitTest */
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
	int texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 6; k++) {
		glColor4f(1.0f, 1.0f, 1.0f, g_slot == k ? 0.8f : 0.4f);
		profile_drawButton(X0 + 0x10, Y0 + k * 0x30 + 0x40, X0 + 0xb0, Y0 + k * 0x30 + 0x6c, 1);
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
	if (g_armcPreview) {
		static const u32 names[5] = { 0x4dceb8, 0x4dbc08, 0x4dc250, 0x4dc1e8, 0x4dce40 };
		TEXT(bright);
		for (int k = 0; k < 5; k++)
			text_draw8(X0 + 0x28, Y0 + 0x54 + k * 0x30, (const char *)names[k]);
	}
	/* the sliders' tracks: the hue's rainbow, saturation and value plain */
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
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
		menu_drawWideButton(X0 + k * 0x64 + 0x10, Y1 - 0x20, X0 + k * 0x64 + 0x70, Y1, 1);
	}
	for (int k = 0; k < 2; k++) {
		if (hovered == k + 3)
			TEXT(bright);
		else
			TEXT(dim);
		text_drawBox16(X0 + k * 0x64 + 0x10, Y1 - 0x18, X0 + k * 0x64 + 0x70, (const char *)(0x7517a4 + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
	tex_bind(g_textures->managers[texture / 512], texture % 512);
	mode_box();
}

/* ---- the build screen ---- */
#define SLOT_NAME(k) ((const char *)0x4dbe50 + (k) * 0x80)
#define STAT(type, offset) GAME_VAR(type, 0x4dc190 + (offset))

static void bind_texture(int texture)
{
	tex_bind(g_textures->managers[texture / 512], texture % 512);
}

/* a texture's whole quad on (x0, y0) .. (x1, y1) */
static void picture(int x0, int y0, int x1, int y1)
{
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex(x0, y0);
	glTexCoord2f(1.0f, 0.0f);
	glVertex(x1, y0);
	glTexCoord2f(1.0f, 1.0f);
	glVertex(x1, y1);
	glTexCoord2f(0.0f, 1.0f);
	glVertex(x0, y1);
	glEnd();
}

/* a stat line's value, right-aligned at x: a number with its unit (none: no unit) */
static void stat_int(int x, int y, int value, u32 unit)
{
	char text[50] = { 0 };
	itoa(value, text, 10);
	if (unit)
		strcat(text, (const char *)unit);
	armc_drawStatLabel(x, y, text);
}

static void stat_float(int x, int y, float value, u32 format, u32 unit)
{
	char text[50] = { 0 };
	sprintf(text, (const char *)format, (double)value);   /* "%.0f" / "%.1f" */
	strcat(text, (const char *)unit);
	armc_drawStatLabel(x, y, text);
}

/* 0x419160: the build screen: two buttons (0x7517a4; 3 / 4 under the pointer, by armcParts_hitTest, lit), the six part
   slots (the chosen one, 0x4dbe48, bright), a new snapshot of it when asked (0x4dcc64), each slot's picture
   (texture 0x4dcc70 + 4 k, when it has a name, 0x4dbe50) and label (0x756fa4) with its name (or 0x757da4); the part
   box: its picture (0x4dcc88), name (0x4dc150) and type (0x7641a4, by 0x4dc79c / 0x4dcca4 of 0x4dc77c), or
   0x757e24 without one; its arrows either side of it (0xc / 0xd lit); the mode box; the stats panel: nothing chosen (0x4dc190 = -1: 0x757da4), a part type only
   (0x4dc194 = -1: 0x765fa4 and its kind 0x7652a4), or the 16 stats under their labels (0x7574a4), the sixth with
   the pilot's (0x9f1818) skill bonus. The original leaves eax to callers that ignore it */
void (armc_drawBuildScreen)(void)
{
	int hovered = GAME_CDECL(0x40e490, int, int, int)(g_mouseX, g_mouseY);   /* armcParts_hitTest */
	static const u32 yellow[4] = { 0x3f800000, 0x3f800000, 0, 0x3f800000 };
	static const u32 white[4] = { 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000 };
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		bind_texture(g_buttonTexture);
		int lit = hovered == k + 3, x = X0 + k * 0x64;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		menu_drawWideButton(x + 0x10, Y1 - 0x20, x + 0x70, Y1, 1);
		if (lit)
			TEXT(bright);
		else
			TEXT(dim);
		text_drawBox16(x + 0x10, Y1 - 0x18, x + 0x70, (const char *)(0x7517a4 + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	bind_texture(g_buttonTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 6; k++) {
		glColor4f(1.0f, 1.0f, 1.0f, g_armcSlot == k ? 1.0f : 0.4f);
		menu_drawWideButton(X0 + 0x10, Y0 + k * 0x3f + 0x28, X0 + 0xa0, Y0 + k * 0x3f + 0x54, 1);
	}
	if (g_armcChanged)
		armc_snapshot(g_armcSlot);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	for (int k = 0; k < 6; k++)
		if (strlen(SLOT_NAME(k)) > 1) {
			bind_texture(GAME_VAR(int, 0x4dcc70 + k * 4));
			picture(X0 + 0x40, Y0 + k * 0x3f + 0x2a, X0 + 0x9c, Y0 + k * 0x3f + 0x4e);
		}
	for (int k = 0; k < 6; k++) {
		TEXT(bright);
		text_draw8(X0 + 0x14, Y0 + k * 0x3f + 0x19, (const char *)(0x756fa4 + k * 0x80));
		TEXT(yellow);
		if (strlen(SLOT_NAME(k)) <= 1)
			text_draw8b(X0 + 0x10, Y0 + k * 0x3f + 0x36, X0 + 0xa0, (const char *)0x757da4);
		else
			text_draw5(X0 + 0x18, Y0 + k * 0x3f + 0x2d, SLOT_NAME(k));
	}
	/* the part box */
	int x = X1 - 0xc2, y = Y0 + 0x28;
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3f333333);   /* 0.7 */
	menu_drawRect(x, y + 0x118, x + 0xa0, y + 0x17c, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(x, y + 0x118, x + 0xa0, y + 0x17c, 0);
	if (strlen((const char *)0x4dc150) <= 1) {
		TEXT(yellow);
		text_draw8b(x, y + 0x142, x + 0xa0, (const char *)0x757e24);
	} else {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		bind_texture(g_armcBuildTexture);
		picture(x + 0x10, y + 0x11c, x + 0x90, y + 0x158);
		TEXT(white);
		armc_drawText(x + 5, y + 0x158, (const char *)0x4dc150);
		int part = g_armcCursor;
		int type = g_armcSlot > 3 ? ((const int *)0x4dcca4)[part] : ((const int *)0x4dc79c)[part];
		TEXT(white);
		armc_drawText(x + 5, y + 0x16a, (const char *)(0x7641a4 + type * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	bind_texture(g_buttonTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(x - 0x28, y + 0x13a, x, y + 0x15a, hovered == 0xc);
	menu_drawSmallButton2(x + 0xa0, y + 0x13a, x + 0xc8, y + 0x15a, hovered != 0xc && hovered == 0xd);
	mode_box();
	/* the stats panel */
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f333333);   /* 0.1, 0.2, 0.5, 0.7 */
	menu_drawRect(x, y, x + 0xc8, y + 0x10e, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(x + 4, y + 4, x + 0xc4, y + 0x10a, 0);
	if (STAT(int, 0) == -1) {
		TEXT(yellow);
		text_drawBox16(x, y + 0x40, x + 0xc8, (const char *)0x757da4);
		return;
	}
	if (STAT(int, 4) == -1) {
		TEXT(yellow);
		text_draw8(x + 8, y + 0x10, (const char *)0x765fa4);
		TEXT(white);
		armc_drawText(x + 8, y + 0x28, (const char *)(0x7652a4 + STAT(int, 8) * 0x80));
		return;
	}
	TEXT(bright);
	TEXT(white);
	for (int k = 0; k < 16; k++)
		armc_drawText(x + 8, y + 8 + k * 0x10, (const char *)(0x7574a4 + k * 0x80));
	set_colour_bits((Colour *)0x76d438, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	int vx = x + 0xc0;
	char text[50] = { 0 };
	strcpy(text, (const char *)(0x757ea4 + STAT(int, 0) * 0x80));
	armc_drawStatLabel(vx, y + 8, text);
	char kind[50] = { 0 };
	strcpy(kind, (const char *)(0x757fa4 + STAT(int, 4) * 0x80));
	armc_drawStatLabel(vx, y + 0x18, kind);
	stat_int(vx, y + 0x28, STAT(int, 8), 0x765824);
	stat_int(vx, y + 0x38, STAT(int, 0xc), 0x765924);
	char name[50] = { 0 };
	strcpy(name, (const char *)(0x7581a4 + STAT(int, 0x10) * 0x80));
	armc_drawStatLabel(vx, y + 0x48, name);
	/* the sixth with the pilot's skill (of the part's kind) in percent of it as a bonus */
	char value[50] = { 0 }, bonus[16];
	itoa(STAT(int, 0x14), value, 10);
	static const u32 skill[5] = { 0x9f9068, 0x9f9068, 0x9f906c, 0x9f9070, 0x9f9074 };   /* by kind; above 3 the last */
	int kind_of = (unsigned)STAT(int, 4) <= 3 ? STAT(int, 4) : 4;
	long double b = fmul_m((long double)*(const int *)(skill[kind_of] + g_armcValue * 0x4c), (const float *)0x4a9420);
	b *= (long double)STAT(int, 0x14);
	if (b >= *(const float *)0x4a93e8)
		sprintf(bonus, (const char *)0x4b02f0, ftol(b));   /* " +%d" */
	else
		sprintf(bonus, (const char *)0x4b02f8, ftol(b));   /* " %d" */
	strcat(value, bonus);
	armc_drawStatLabel(vx, y + 0x58, value);
	stat_float(vx, y + 0x68, STAT(float, 0x18), 0x4b0354, 0x7655a4);
	stat_float(vx, y + 0x78, STAT(float, 0x1c), 0x4b0354, 0x7659a4);
	stat_float(vx, y + 0x88, STAT(float, 0x20), 0x4b0334, 0x765624);
	stat_float(vx, y + 0x98, STAT(float, 0x24), 0x4b0334, 0x7655a4);
	stat_float(vx, y + 0xa8, STAT(float, 0x28), 0x4b0334, 0x7655a4);
	stat_int(vx, y + 0xb8, STAT(int, 0x2c), 0);
	stat_float(vx, y + 0xc8, STAT(float, 0x30), 0x4b0354, 0x765724);
	stat_float(vx, y + 0xd8, STAT(float, 0x34), 0x4b0334, 0x765624);
	stat_float(vx, y + 0xe8, STAT(float, 0x38), 0x4b0334, 0x765724);
	stat_float(vx, y + 0xf8, STAT(float, 0x3c), 0x4b0334, 0x7657a4);
}
#undef STAT
#undef SLOT_NAME
