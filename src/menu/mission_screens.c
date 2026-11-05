/* mission_screens.c: the mission-select screen (0x9f6308 .. 0x9f6314) for mission g_missionShown: its title, the map's
   preview, the mission record (0x9db99c, 0x5c bytes a mission) and the two buttons */
#include "../game.h"
#include <string.h>
#include "portrait.h"

#define X0 g_missionSelectLeft
#define Y0 g_missionSelectTop
#define X1 (g_missionSelectRect[2])
#define Y1 (g_missionSelectRect[3])
#define K(addr) ((const float *)RELOC(addr))
#define record ((const int *)((OBJ(g_skirmishInfo) + 0x4) + g_missionShown * 0x5c))
#define map_name ((const char *)(OBJ(g_mapNames) + g_missionShown * 0x20))

static void white_text(void)
{
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0x3f800000, 0x3f800000);
}

static void bind(int texture)
{
	tex_bind(g_textures->banks[texture / 512], texture % 512);
}

/* "<label> : <value>" at y: the value a number and its unit, or the text none when it is 0 */
static void value_line(int y, u32 label, int value, u32 none, u32 unit)
{
	char line[128] = { 0 }, number[128] = { 0 };
	strcpy(line, (const char *)RELOC(label));
	strcat(line, (const char *)STR(0x4b2b10, " : "));
	if (!value)
		strcat(line, (const char *)RELOC(none));
	else {
		itoa(value, number, 10);
		strcat(line, number);
		strcat(line, (const char *)RELOC(unit));
	}
	text_draw16(X0 + 0xc4, y, line);
}

/* the screen, hovered the button (0 / 1) or arrow (2 / 3) under the pointer (-1: none, nothing lit) */
static void mission_screen(int hovered)
{
	const u32 *bright = g_missionColourLit, *dim = g_missionColourDim;
	gfx_setProjection2D3D(2);
	glLoadIdentity();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawTexture(X0, Y0, X1, Y1, g_dialogFrameTexture);
	set_colour_bits(g_textColour, bright[0], bright[1], bright[2], bright[3]);
	/* "<n>ST <0x75f1a4>  [ <map> ]" */
	char title[256];
	itoa(g_missionShown + 1, title, 10);
	static const u32 suffix[4] = { STR(0x4b2b20, "ST "), STR(0x4b2b24, "ND "), STR(0x4b2b28, "RD "), STR(0x4b2b2c, "TH ") };
	strcat(title, (const char *)RELOC(suffix[(unsigned)g_missionShown < 3 ? g_missionShown : 3]));
	strcat(title, (const char *)MSG(551, "ROUND"));
	strcat(title, (const char *)STR(0x4b2b18, "  [ "));
	strcat(title, map_name);
	strcat(title, (const char *)STR(0x4b2b14, " ]"));
	text_drawBox16(X0, Y0 + 8, X1, title);
	/* the preview, looked up when asked for: "<g_stageDir><map>/<map>" */
	if (g_missionPreviewDue) {
		char path[128] = { 0 }, name[64];
		strcpy(path, g_stageDir);
		strcat(path, map_name);
		strcat(path, (const char *)STR(0x4ad564, "/"));
		strcat(path, map_name);
		strcpy(name, path);
		g_mapPreviewTexture = tex_getIdByName(g_textures, name, 0, 0, 0, 0, 0, 0, 0);
		g_missionPreviewDue = 0;
	}
	glEnable(GL_TEXTURE_2D);
	bind(g_mapPreviewTexture);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0, 0.0);
	menu_vertex(X0 + 0xd8, Y0 + 0x20);
	glTexCoord2d(1.0, 0.0);
	menu_vertex(X0 + 0x158, Y0 + 0x20);
	glTexCoord2d(1.0, 1.0);
	menu_vertex(X0 + 0x158, Y0 + 0xa0);
	glTexCoord2d(0.0, 1.0);
	menu_vertex(X0 + 0xd8, Y0 + 0xa0);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	menu_drawRect(X0 + 0xd8, Y0 + 0x20, X0 + 0x158, Y0 + 0xa0, 0);
	/* the arrows: back from the first mission, on up to the last unlocked (0x9f181c) and 14 */
	bind(g_buttonTexture);
	glEnable(GL_TEXTURE_2D);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawSmallButton1(X0 + 0x98, Y0 + 0x4c, X0 + 0xd0, Y0 + 0x74, g_missionShown > 0 && hovered == 2);
	menu_drawSmallButton2(X0 + 0x160, Y0 + 0x4c, X0 + 0x198, Y0 + 0x74,
	                        g_missionShown < g_progress && hovered == 3 && g_missionShown < 14);
	white_text();
	/* the kind and the two values */
	char line[128] = { 0 };
	strcpy(line, (const char *)MSG(553, "GAME TYPE"));
	strcat(line, (const char *)STR(0x4b2b10, " : "));
	strcat(line, (const char *)(MSG(471, "DEATH MATCH") + record[0x48 / 4] * 0x80));
	text_draw16(X0 + 0xc4, Y0 + 0xaa, line);
	value_line(Y0 + 0xbc, MSG(554, "OBJECTIVE"), record[0x50 / 4], MSG(453, "UNLIMITED"), MSG(454, "FRAGS"));
	value_line(Y0 + 0xce, MSG(555, "TIME"), record[0x4c / 4], MSG(451, "UNLIMITED"), MSG(452, "MIN"));
	/* the allies (+0x24 of them, faces from +0x28) in red frames */
	if (record[0x24 / 4]) {
		white_text();
		text_drawBox16(X0, Y0 + 0xf2, X1, (const char *)MSG(558, "FRIENDLY"));
		glEnable(GL_TEXTURE_2D);
		bind(g_characterTexture);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		int x0 = 0x146 - record[0x24 / 4] * 0x20;
		for (int i = 0; i < record[0x24 / 4]; i++)
			portrait(record[0x28 / 4 + i], x0 + i * 0x40, Y0 + 0x104, 0x30);
		glDisable(GL_TEXTURE_2D);
		set_colour_bits(g_rectColour, 0x3f800000, 0x3dcccccd, 0x3dcccccd, 0x3f800000);   /* 1, 0.1, 0.1, 1 */
		for (int i = 0; i < record[0x24 / 4]; i++)
			menu_drawRect(x0 + i * 0x40, Y0 + 0x104, x0 + i * 0x40 + 0x30, Y0 + 0x134, 0);
	}
	/* the enemies (+0 of them, faces from +4; outside 0 .. 8 "???") in blue frames */
	text_drawBox16(X0, Y0 + 0x142, X1, (const char *)MSG(559, "ENEMY"));
	glEnable(GL_TEXTURE_2D);
	int x0 = 0x146 - record[0] * 0x20;
	for (int i = 0; i < record[0]; i++) {
		int face = record[1 + i], x = x0 + i * 0x40;
		bind(g_characterTexture);
		glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
		if (face >= 0 && face <= 8)
			portrait(face, x, Y0 + 0x154, 0x30);
		else
			text_drawBox16(x, Y0 + 0x164, x + 0x30, (const char *)STR(0x4b2b0c, "???"));
	}
	glDisable(GL_TEXTURE_2D);
	set_colour_bits(g_rectColour, 0x3dcccccd, 0x3dcccccd, 0x3f800000, 0x3f800000);   /* 0.1, 0.1, 1, 1 */
	for (int i = 0; i < record[0]; i++)
		menu_drawRect(x0 + i * 0x40, Y0 + 0x154, x0 + i * 0x40 + 0x30, Y0 + 0x184, 0);
	for (int k = 0; k < 2; k++) {
		glEnable(GL_TEXTURE_2D);
		bind(g_buttonTexture);
		int lit = hovered == k;
		glColor4f(1.0f, 1.0f, 1.0f, lit ? 1.0f : 0.4f);
		int x = X0 + k * 0x8c;
		menu_drawWideButton(x + 0x96, Y1 - 0x30, x + 0x10e, Y1 - 0x10, 1);
		const u32 *colour = lit ? bright : dim;
		set_colour_bits(g_textColour, colour[0], colour[1], colour[2], colour[3]);
		text_drawBox16(x + 0x96, Y1 - 0x28, x + 0x10e, (const char *)(MSG(561, "$[0] O K") + k * 0x80));
	}
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	menu_drawCornerOrnaments(X0, Y0, X1, Y1);
}

/* 0x448ac0: the mission settings screen, the button or arrow under the pointer (missionsel_hitTest) lit. The
   original leaves eax to callers that ignore it */
void (missionsel_drawSettingsScreen)(void)
{
	mission_screen(missionsel_hitTest(g_mouseX, g_mouseY));   /* missionsel_hitTest */
}

/* 0x449a50: the same with nothing lit (the pointer is still asked), under a dimmed screen with the message
   MSG(563, "YOU'VE GOT NEW PARTS AND WEAPONS") / MSG(0, "PRESS ENTER OR CLICK MOUSE"). The original leaves eax to callers that ignore it */
void (missionsel_drawScreen)(void)
{
	missionsel_hitTest(g_mouseX, g_mouseY);   /* missionsel_hitTest */
	mission_screen(-1);
	set_colour_bits(g_rectColour, 0, 0, 0, 0x3f000000);
	menu_drawRect(0, 0, 0x280, 0x1e0, 1);
	set_colour_bits(g_rectColour, 0x3e4ccccd, 0x3e4ccccd, 0x3f333333, 0x3f333333);   /* 0.2, 0.2, 0.7, 0.7 */
	menu_drawRect(0x3c, 0xc8, 0x244, 0x122, 1);
	set_colour_bits(g_rectColour, 0, 0x3f800000, 0x3f800000, 0x3f800000);
	menu_drawRect(0x41, 0xcd, 0x23f, 0x11d, 0);
	set_colour_bits(g_textColour, 0x3f800000, 0x3f800000, 0, 0x3f800000);
	text_drawBox16(0x46, 0xdc, 0x23a, (const char *)MSG(563, "YOU'VE GOT NEW PARTS AND WEAPONS"));
	text_drawBox16(0x46, 0xf5, 0x23a, (const char *)MSG(0, "PRESS ENTER OR CLICK MOUSE"));
}

/* 0x44aa20, 0x44aa30: jumps to missionsel_drawSettingsScreen and missionsel_drawScreen (the mission select's states'
   frames; their callers ignore eax) */
void (missionsel_frameSettings)(void) { missionsel_drawSettingsScreen(); }
void (missionsel_frameScreen)(void) { missionsel_drawScreen(); }
