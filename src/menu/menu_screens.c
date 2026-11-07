/* menu_screens.c: the frames of single front-end screens. */
#include "../game.h"
#include <string.h>

/* 0x44aa40: the skirmish screen (500): the background (g_skirmishShowBackground), the tunnel (skirmish_drawTunnel)
   unless the camera has arrived (g_skirmishState 2), the camera (skirmish_camera); once arrived (state past 1): the
   dialog frame while it opens (g_skirmishBox), nothing once the screen has been left (g_skirmishLeft), else the
   new-parts notice (g_skirmishNewPartsNotice: skirmish_frameNewPartsNotice) or the round's settings (skirmish_frameRoundScreen) */
void (menuState500_skirmish)(void)
{
	if (g_skirmishShowBackground)
		menu_drawBackground();
	if (g_skirmishState != 2)
		skirmish_drawTunnel();
	skirmish_camera();
	if (g_skirmishState == 1 || g_skirmishState == 0)
		return;
	if (g_frameOpening) {
		menu_drawFrame(g_skirmishBox[0], g_skirmishBox[1], g_skirmishBox[2], g_skirmishBox[3]);
		return;
	}
	if (g_skirmishLeft)
		return;
	if (g_skirmishNewPartsNotice)
		skirmish_frameNewPartsNotice();
	else
		skirmish_frameRoundScreen();
}

/* 0x41f8d0: the title screen's frame: 19 frames after the title was dismissed (g_titleClosing, counted in
   g_titleCloseFrames) the profile screen (210) follows, with a key delay of 5; the background, the emblem and logo
   (menu_titleEmblemTransition, a call the patch DLL wraps), and the copyright and version lines at the bottom (the
   version right-aligned at 6 units per character) */
void (menuState200_title)(void)
{
	if (g_titleClosing && ++g_titleCloseFrames >= 19) {
		g_screen = 210;
		g_menuKeyGuard = 5.0f;
	}
	menu_drawBackground();
	SITE_CALL(0x41f903, menu_titleEmblemTransition, void, void)();        /* menu_titleEmblemTransition */
	Color4_set(g_textColour, 1.0f, 1.0f, 1.0f, 1.0f);
	text_draw5(5, 0x1d6, STR_COPYRIGHT);
	text_draw5((0x69 - (int)strlen(STR_VERSION)) * 6, 0x1d6, STR_VERSION);
}
