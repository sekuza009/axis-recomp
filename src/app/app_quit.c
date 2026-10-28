/* app_quit.c: leaving the game from the front end. */
#include "../game.h"

#define WM_CLOSE 0x10
#define g_exitCode GAME_VAR(int, 0x4df048)            /* (by use) why the game closed: 1 to start again with new graphics */

/* 0x41e7a0 (profile_41e7a0): close the main window with code (returns PostMessage's result) */
int (profile_41e7a0)(int code)
{
	g_exitCode = code;
	return PostMessageA(g_hWndMain, WM_CLOSE, 0, 0);
}

/* 0x44f850 (profile_44f850): quit */
void (profile_44f850)(void)
{
	profile_41e7a0(0);
}
