/* win32.c: small Win32 / multimedia wrappers. */
#include "../game.h"

#define MCI_PAUSE 0x809
#define MCI_NOTIFY 1

/* 0x43f580: the current directory into the game's path buffer (0x76d224, 0x105 bytes) */
u32 (GetCurrentDirectoryA_wrap_43f580)(void)
{
	return GetCurrentDirectoryA(0x105, (char *)0x76d224);
}

/* 0x46c580: a message box over the active window (title, text); MessageBox's answer */
int (FUN_0046c580)(const char *title, const char *text)
{
	return MessageBoxA(GetActiveWindow(), text, title, 0);
}

/* 0x46c540: the MCI device (the CD audio) paused, notifying the window kept in its parameters */
u32 (mci_pause)(void)
{
	u32 params[3] = { GAME_VAR(u32, 0xa1efc8), GAME_VAR(u32, 0xa1efcc), GAME_VAR(u32, 0xa1efd0) };
	return mciSendCommandA(GAME_VAR(u32, 0xa1efd8), MCI_PAUSE, MCI_NOTIFY, params);
}
