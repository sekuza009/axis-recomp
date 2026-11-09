/* app_quit.c: leaving the game from the front end. */
#include "../game.h"

#define WM_CLOSE 0x10

/* 0x41e7a0 (app_closeWindow): close the main window with code (returns PostMessage's result) */
int (app_closeWindow)(int code)
{
	g_exitCode = code;
	return PostMessageA(AP(void, g_mainWindow), WM_CLOSE, 0, 0);
}

/* 0x44f850 (app_quitGame): quit */
void (app_quitGame)(void)
{
	app_closeWindow(0);
}
