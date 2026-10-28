/* win32.c: small Win32 / multimedia wrappers. */
#include <stdarg.h>
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

/* 0x41edf0: a printf-formatted message box titled "User Message" (the arguments' address kept in 0x4dd0b4 while
   formatting); MessageBox's answer */
int (sys_messageBox)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	GAME_VAR(va_list, 0x4dd0b4) = args;
	vsprintf((char *)0x4dd0d0, format, args);
	GAME_VAR(void *, 0x4dd0b4) = NULL;
	int answer = MessageBoxA(GetActiveWindow(), (const char *)0x4dd0d0, (const char *)0x4b043c, 0);
	va_end(args);
	return answer;
}

/* 0x43f840: the window class registered: a WNDCLASSEXA made from the WNDCLASSA-like record (ten words, no small
   icon); returns the atom (16 bits) */
u32 (app_registerWindowClassEx)(const u32 *cls)
{
	u32 wc[12];
	wc[0] = 0x30;   /* cbSize */
	wc[11] = 0;     /* hIconSm */
	for (int i = 0; i < 10; i++)
		wc[1 + i] = cls[i];
	return IMPORT(0x4a92e8, u32, const u32 *)(wc) & 0xffff;   /* RegisterClassExA */
}
