/* app_quit.c: leaving the game from the front end. */
#include "../game.h"

#define WM_CLOSE 0x10
#define g_exitCode GAME_VAR(int, 0x4df048)            /* (by use) why the game closed: 1 to start again with new graphics */

/* 0x41e7a0 (app_closeWindow): close the main window with code (returns PostMessage's result) */
int (app_closeWindow)(int code)
{
	g_exitCode = code;
	return PostMessageA(g_hWndMain, WM_CLOSE, 0, 0);
}

/* 0x44f850 (app_quitGame): quit */
void (app_quitGame)(void)
{
	app_closeWindow(0);
}
