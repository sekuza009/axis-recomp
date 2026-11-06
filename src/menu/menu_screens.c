/* menu_screens.c: the frames of single front-end screens. */
#include "../game.h"
#include <string.h>

/* 0x44aa40 (menuState500_skirmish): the skirmish screen: the background, the tunnel (refreshed
   except on page 2), the screen itself; on its pages from 2 on an open dialog draws its frame, else the screen's
   input (two handlers: the briefing and the round's screen) */
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
	if (g_skirmishBriefing)
		skirmish_frameScreen();
	else
		skirmish_frameSettings();
}

/* 0x41f8d0 (menuState200_title): the title screen's frame: after 19 frames of the title the profile screen follows
   (fading in); the background, the emblem and the transition (a call the patch DLL wraps), and the copyright and
   version lines at the bottom (the version right-aligned at 6 units per character) */
void (menuState200_title)(void)
{
	if (g_titleClosing && ++g_titleCloseFrames >= 19) {
		g_screen = 210;
		g_menuKeyGuard = 5.0f;
	}
	menu_drawBackground();
	PATCHED_CALL(0x41f903, void, void)();        /* menu_titleEmblemTransition */
	Color4_set(g_textColour, 1.0f, 1.0f, 1.0f, 1.0f);
	text_draw5(5, 0x1d6, STR_COPYRIGHT);
	text_draw5((0x69 - (int)strlen(STR_VERSION)) * 6, 0x1d6, STR_VERSION);
}
