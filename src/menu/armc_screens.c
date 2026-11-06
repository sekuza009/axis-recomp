/* armc_screens.c: two of the ARM CENTER's pages: the weapons page (the item slots, the item box and its stats) and
   the colour editor (two colours, hue, saturation and value, for each of the slots at g_armcColours, six floats a slot:
   hue 1, saturation 1, value 1, hue 2, then saturation 2 and value 2 in -1 .. 1) */
#include "../game.h"
#include <string.h>

#define X0 g_armcPageLeft
#define Y0 g_armcPageTop
#define X1 g_armcPanelRight
#define Y1 g_armcPageBottom
#define K(addr) ((const float *)RELOC(addr))
#define g_slot g_armcColourSlot
#define SLOT (g_armcColours + g_slot * 6)
#define glVertex(x, y) menu_vertex(x, y)

static const u32 *const bright = g_armcBright, *const dim = g_armcDim;
#define TEXT(c) set_colour_bits(g_textColour, (c)[0], (c)[1], (c)[2], (c)[3])

/* the box at the bottom right: "<MSG(287, "$[0] ROTATE")> <the name of g_armcSpin (MSG(118, "OFF"))>" (the texture bound) */
static void mode_box(void)
{
	glColor4f(1.0f, 1.0f, 1.0f, 0.7f);
	menu_drawWideButton(X1 - 0xa0, Y1 - 0x20, X1, Y1, 1);
	TEXT(bright);
	char text[50] = { 0 };
	strcpy(text, (const char *)MSG(287, "$[0] ROTATE"));
	strcat(text, (const char *)STR(0x4b035c, " "));
	strcat(text, (const char *)(MSG(118, "OFF") + g_armcSpin * 0x80));
	text_drawBox16(X1 - 0xa0, Y1 - 0x18, X1, text);
}

/* a hue (degrees) turned half way round */
static int turned(int h) { return h >= 0 && h < 180 ? h + 180 : h - 180; }
static long double turned_f(long double h)
{
	return h >= 0 && h < *&k_180f ? fadd_m(h, &k_180f) : fsub_m(h, &k_180f);
}

/* a 0 .. 99 percentage */
static int percent(long double v)
{
	int p = ftol(fmul_m(v, &k_100f));
	return p >= 100 ? 99 : p;
}

/* a -1 .. 1 value as a 0 .. 99 percentage */
static int half_percent(long double v)
{
	int p = ftol(fmul_m(fmul_m(fadd_m(v, &k_1f), &k_100f), &k_0_5f));
	return p >= 100 ? 99 : p;
}

/* a colour line "<label> [<value>]" at y */
static void value_line(int k, int y, int value)
{
	char line[50] = { 0 }, number[50] = { 0 };
	strcpy(line, (const char *)(MSG(493, "HUE") + k * 0x80));
	strcat(line, (const char *)STR(0x4b037c, " ["));
	sprintf(number, (const char *)STR(0x4b0378, "%d]"), value);
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
	int x = ftol(FMUL(pos, k_m168f));
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
	int x = ftol(FMUL(pos, k_m164f));
	glVertex(X1 - x - 0xbd, y);
	glTexCoord2f(0.03125f, 0.8125f);
	glVertex(X1 - x - 0xb5, y);
	glTexCoord2f(0.03125f, 0.875f);
	glVertex(X1 - x - 0xb5, y + 0x10);
	glTexCoord2f(0.0f, 0.875f);
	glVertex(X1 - x - 0xbd, y + 0x10);
}

/* 0x41a280: the colour editor: two boxes (MSG(491, "PRIMARY COLOR") / MSG(492, "SECONDARY COLOR")) of three lines each, the current slot's hue
   (turned half round, as 0 .. 50 by 0.278) and saturation and value (percent; the second colour's from -1 .. 1);
   the six slot buttons (the current one, g_armcColourSlot, bright; the sixth MSG(286, "VIEW $[0] ALL")) with the parts' names beside them
   when g_armcPreview is set; the sliders' tracks, bars and hue markers; two buttons (MSG(115, "$[0] O K"); 3 / 4 under the pointer,
   by armcColour_hitTest, lit) and the box "<MSG(287, "$[0] ROTATE")> <MSG(118, "OFF") name of g_armcSpin>". The original leaves eax to callers
   that ignore it */
void (armc_drawColourEditor)(void)
{
	int hovered = ((int)armcColour_hitTest(g_mouseX, g_mouseY));   /* armcColour_hitTest */
	for (int box = 0; box < 2; box++) {
		set_colour_bits(g_rectColour, 0x3dcccccd, 0x3e4ccccd, 0x3f000000, 0x3f000000);   /* 0.1, 0.2, 0.5, 0.5 */
		menu_drawRect(X1 - 200, Y0 + 0x30 + box * 0xb0, X1, Y0 + 0xd0 + box * 0xb0, 1);
	}
	TEXT(bright);
	text_drawCentred8(X1 - 200, Y0 + 0x34, X1, (const char *)MSG(491, "PRIMARY COLOR"));
	text_drawCentred8(X1 - 200, Y0 + 0xe4, X1, (const char *)MSG(492, "SECONDARY COLOR"));
	for (int k = 0; k < 3; k++) {
		int y = Y0 + k * 0x30;
		int v1 = k == 0 ? ftol(fmul_m((long double)turned(ftol(fld_m(&SLOT[0]))), &k_0_2777778f))
		                : percent(fld_m(&SLOT[k]));
		value_line(k, y + 0x46, v1);
		int v2 = k == 0 ? ftol(fmul_m((long double)turned(ftol(fld_m(&SLOT[3]))), &k_0_2777778f))
		                : half_percent(fld_m(&SLOT[3 + k]));
		value_line(k, y + 0xf6, v2);
	}
	/* the slots */
	glEnable(GL_TEXTURE_2D);
	int texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
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
			text_drawBox16(X0 + 0x10, Y0 + 0x13d, X0 + 0xb0, (const char *)MSG(286, "VIEW $[0] ALL"));
		else
			text_draw8(X0 + 0x18, Y0 + k * 0x30 + 0x44, (const char *)(MSG(281, "$[0] HEAD") + k * 0x80));
	}
	if (g_armcPreview) {
		static const u32 names[5] = { OBJ(g_headPanelName), OBJ(g_chestPanelName), OBJ(g_armPanelName), OBJ(g_legPanelName), OBJ(g_boosterPanelName) };
		TEXT(bright);
		for (int k = 0; k < 5; k++)
			text_draw8(X0 + 0x28, Y0 + 0x54 + k * 0x30, (const char *)RELOC(names[k]));
	}
	/* the sliders' tracks: the hue's rainbow, saturation and value plain */
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
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
			pos1 = f32(fmul_m(h1, &k_0_002777778f));
			pos2 = f32(fmul_m(h2, &k_0_002777778f));
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
			marker(pos1, Y0 + 0x5a);
			marker(pos2, Y0 + 0x10a);
		} else {
			pos1 = SLOT[k];
			pos2 = f32(fmul_m(FADD(SLOT[3 + k], k_1f), &k_0_5f));
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
		text_drawBox16(X0 + k * 0x64 + 0x10, Y1 - 0x18, X0 + k * 0x64 + 0x70, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
	}
	glEnable(GL_TEXTURE_2D);
	texture = g_buttonTexture;
	tex_bind(g_textures->banks[texture / 512], texture % 512);
	mode_box();
}

/* ---- the weapons page ---- */
#define SLOT_NAME(k) ((const char *)OBJ(g_partRecords) + (k) * 0x80)
#define PART ((const PartInfo *)OBJ(g_viewedPart))   /* the part looked at (armc_viewedPartRecord) */

static void bind_texture(int texture)
{
	tex_bind(g_textures->banks[texture / 512], texture % 512);
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
		strcat(text, (const char *)RELOC(unit));
	armc_drawTextRight(x, y, text);
}

static void stat_float(int x, int y, float value, u32 format, u32 unit)
{
	char text[50] = { 0 };
	sprintf(text, (const char *)RELOC(format), (double)value);   /* "%.0f" / "%.1f" */
	strcat(text, (const char *)RELOC(unit));
	armc_drawTextRight(x, y, text);
}

/* 0x419160: the weapons page: two buttons (MSG(115, "$[0] O K"); 3 / 4 under the pointer, by armcWeaponsPage_hitTest, lit), the six part
   slots (the chosen one, g_armcSlot, bright), a new snapshot of it when asked (g_armcChanged), each slot's picture
   (texture OBJ(g_slotTextures) + 4 k, when it has a name, g_partRecords) and label (MSG(291, "HAND-W1($[0] 1)")) with its name (or MSG(319, "EMPTY SLOT")); the part
   box: its picture (g_armcBuildTexture), name (0x4dc150) and type (MSG(711, "HV-PISTOL"), by g_weaponListTable / g_extraListTable of g_armcCursor), or
   MSG(320, "REMOVE WEAPON") without one; its arrows either side of it (0xc / 0xd lit); the mode box; the stats panel: nothing chosen (0x4dc190 = -1: MSG(319, "EMPTY SLOT")), a part type only
   (g_viewedPartAmmoType = -1: MSG(771, "SPECIAL WEAPON") and its kind MSG(745, "GRAVITY CONTROLLER")), or the 16 stats under their labels (MSG(301, "SLOT TYPE")), the sixth with
   the pilot's (g_selectedCharacter) skill bonus. The original leaves eax to callers that ignore it */
void (armc_drawWeaponsScreen)(void)
{
	int hovered = ((int)armcWeaponsPage_hitTest(g_mouseX, g_mouseY));   /* armcWeaponsPage_hitTest */
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
		text_drawBox16(x + 0x10, Y1 - 0x18, x + 0x70, (const char *)(MSG(115, "$[0] O K") + k * 0x80));
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
			bind_texture(g_slotTextures[k]);
			picture(X0 + 0x40, Y0 + k * 0x3f + 0x2a, X0 + 0x9c, Y0 + k * 0x3f + 0x4e);
		}
	for (int k = 0; k < 6; k++) {
		TEXT(bright);
		text_draw8(X0 + 0x14, Y0 + k * 0x3f + 0x19, (const char *)(MSG(291, "HAND-W1($[0] 1)") + k * 0x80));
		TEXT(yellow);
		if (strlen(SLOT_NAME(k)) <= 1)
			text_drawCentred8(X0 + 0x10, Y0 + k * 0x3f + 0x36, X0 + 0xa0, (const char *)MSG(319, "EMPTY SLOT"));
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
	if (strlen((const char *)OBJ(g_viewedPart)) <= 1) {
		TEXT(yellow);
		text_drawCentred8(x, y + 0x142, x + 0xa0, (const char *)MSG(320, "REMOVE WEAPON"));
	} else {
		glEnable(GL_TEXTURE_2D);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		bind_texture(g_armcBuildTexture);
		picture(x + 0x10, y + 0x11c, x + 0x90, y + 0x158);
		TEXT(white);
		armc_drawText(x + 5, y + 0x158, (const char *)OBJ(g_viewedPart));
		int part = g_armcCursor;
		int type = g_armcSlot > 3 ? (g_extraListTable)[part] : (g_weaponListTable)[part];
		TEXT(white);
		armc_drawText(x + 5, y + 0x16a, (const char *)(MSG(711, "HV-PISTOL") + type * 0x80));
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
	if (PART->slotType == -1) {
		TEXT(yellow);
		text_drawBox16(x, y + 0x40, x + 0xc8, (const char *)MSG(319, "EMPTY SLOT"));
		return;
	}
	if (PART->ammoType == -1) {
		TEXT(yellow);
		text_draw8(x + 8, y + 0x10, (const char *)MSG(771, "SPECIAL WEAPON"));
		TEXT(white);
		armc_drawText(x + 8, y + 0x28, (const char *)(MSG(745, "GRAVITY CONTROLLER") + PART->ammoPerShot * 0x80));
		return;
	}
	TEXT(bright);
	TEXT(white);
	for (int k = 0; k < 16; k++)
		armc_drawText(x + 8, y + 8 + k * 0x10, (const char *)(MSG(301, "SLOT TYPE") + k * 0x80));
	set_colour_bits(g_textColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	int vx = x + 0xc0;
	char text[50] = { 0 };
	strcpy(text, (const char *)(MSG(321, "HAND") + PART->slotType * 0x80));
	armc_drawTextRight(vx, y + 8, text);
	char kind[50] = { 0 };
	strcpy(kind, (const char *)(MSG(323, "30mm") + PART->ammoType * 0x80));
	armc_drawTextRight(vx, y + 0x18, kind);
	stat_int(vx, y + 0x28, PART->ammoPerShot, MSG(756, "cell"));
	stat_int(vx, y + 0x38, PART->burst, MSG(758, "Round"));
	char name[50] = { 0 };
	strcpy(name, (const char *)(MSG(327, "IMPACT") + PART->damageType * 0x80));
	armc_drawTextRight(vx, y + 0x48, name);
	/* the sixth with the pilot's skill (of the part's kind) in percent of it as a bonus */
	char value[50] = { 0 }, bonus[16];
	itoa(PART->damage, value, 10);
	static const u8 skill[5] = { 0, 0, 1, 2, 3 };   /* the profile's stat by kind; above 3 the last */
	int kind_of = (unsigned)PART->ammoType <= 3 ? PART->ammoType : 4;
	long double b = fmul_m((long double)g_characterProfiles[g_selectedCharacter].stats[skill[kind_of]], (const float *)ADDR(k_0_01f));
	b *= (long double)PART->damage;
	if (b >= k_0f)
		sprintf(bonus, (const char *)STR(0x4b02f0, " +%d"), ftol(b));
	else
		sprintf(bonus, (const char *)STR(0x4b02f8, " %d"), ftol(b));
	strcat(value, bonus);
	armc_drawTextRight(vx, y + 0x58, value);
	stat_float(vx, y + 0x68, PART->range, STR(0x4b0354, "%.0f"), MSG(751, "m"));
	stat_float(vx, y + 0x78, PART->speed, STR(0x4b0354, "%.0f"), MSG(759, "m/s"));
	stat_float(vx, y + 0x88, PART->spread, STR(0x4b0334, "%.1f"), MSG(752, "'"));
	stat_float(vx, y + 0x98, PART->hitRange, STR(0x4b0334, "%.1f"), MSG(751, "m"));
	stat_float(vx, y + 0xa8, PART->splashRadius, STR(0x4b0334, "%.1f"), MSG(751, "m"));
	stat_int(vx, y + 0xb8, PART->splashBorderDamage, 0);
	stat_float(vx, y + 0xc8, PART->cycleTime, STR(0x4b0354, "%.0f"), MSG(754, "ms"));
	stat_float(vx, y + 0xd8, PART->guidance, STR(0x4b0334, "%.1f"), MSG(752, "'"));
	stat_float(vx, y + 0xe8, PART->targetingTime, STR(0x4b0334, "%.1f"), MSG(754, "ms"));
	stat_float(vx, y + 0xf8, PART->weight, STR(0x4b0334, "%.1f"), MSG(755, "t"));
}
#undef STAT
#undef SLOT_NAME
