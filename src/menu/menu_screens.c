/* menu_screens.c: the frames of single front-end screens. */
#include "../game.h"
#include <string.h>

/* 0x44aa40 (menuState500_missionSelect): the mission-select screen: the background, the mission list (refreshed
   except on page 2), the screen itself; on its pages from 2 on an open dialog draws its frame, else the screen's
   input (two handlers: before and after a mission is started) */
void (menuState500_missionSelect)(void)
{
	if (g_missionShowBackground)
		menu_drawBackground();
	if (g_missionPage != 2)
		missionsel_448140();
	missionsel_447cb0();
	if (g_missionPage == 1 || g_missionPage == 0)
		return;
	if (g_dialogOpen) {
		menu_drawFrame(g_missionBox[0], g_missionBox[1], g_missionBox[2], g_missionBox[3]);
		return;
	}
	if (g_missionBusy)
		return;
	if (g_missionStarted)
		missionsel_44aa30();
	else
		missionsel_44aa20();
}

/* 0x41f8d0 (menu_drawVersion): the title screen's frame: after 19 frames of the title the profile screen follows
   (fading in); the background, the emblem and the transition (a call the patch DLL wraps), and the copyright and
   version lines at the bottom (the version right-aligned at 6 units per character) */
void (menu_drawVersion)(void)
{
	if (g_titleShown && ++g_titleFrames >= 19) {
		g_screen = 210;
		g_menuFade = 5.0f;
	}
	menu_drawBackground();
	PATCHED_CALL(0x41f903, void, void)();        /* menu_titleEmblemTransition */
	Color4_set(g_textColour, 1.0f, 1.0f, 1.0f, 1.0f);
	text_draw5(5, 0x1d6, STR_COPYRIGHT);
	text_draw5((0x69 - (int)strlen(STR_VERSION)) * 6, 0x1d6, STR_VERSION);
}
