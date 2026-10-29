/* win32.c: small Win32 / multimedia wrappers. */
#include <stdarg.h>
#include <string.h>
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

/* 0x468450: the GL window resized to width x height (0xa0e810, 0xa0e928): the viewport set and, in full screen
   (0xa0e920), the display mode changed to match (0x467f20; failing that, a message and 0). The cached state
   0x4c4de8 is reset; returns 1 */
int (glWindow_resize)(int width, int height)
{
	GAME_VAR(int, 0xa0e810) = width;
	GAME_VAR(int, 0xa0e928) = height;
	IMPORT(0x4a91d4, void, int, int, int, int)(0, 0, width, height);   /* glViewport */
	if (GAME_VAR(int, 0xa0e920) == 1 &&
	    !GAME_CDECL(0x467f20, int, int, int, int)(GAME_VAR(int, 0xa0e810), GAME_VAR(int, 0xa0e928), 0)) {
		GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c500c);   /* sys_errorMessageNoName */
		return 0;
	}
	GAME_VAR(int, 0x4c4de8) = -1;
	return 1;
}

/* 0x4314e0: the game shut down: the object at 0x9087b4 deleted (it stays set), the screen restored (0x42eed0 with
   the desktop's size), the arrow cursor back, 0x4014c0, the music stopped, the ten sounds at 0x4dd4d4 released,
   the sound table released (0x456cd0) and DirectSound ended (0x467b70, whose eax it returns) */
u32 (wnd_setCursor)(void)
{
	void *object = GAME_VAR(void *, 0x9087b4);
	if (object)
		GAME_THISCALL(**(u32 **)object, void, void *, int)(object, 1);   /* scalar deleting destructor */
	GAME_CDECL(0x42eed0, void, int, int, int, int)(GAME_VAR(int, 0x67eefc), GAME_VAR(int, 0x76d430), 0, GAME_VAR(int, 0x76d3ec));
	IMPORT(0x4a9340, void *, void *)(IMPORT(0x4a933c, void *, void *, u32)(NULL, 0x7f00));   /* SetCursor(LoadCursorA(IDC_ARROW)) */
	GAME_CDECL(0x4014c0, void, void)();
	music_shutdown();
	for (u32 p = 0x4dd4d4; p < 0x4dd4fc; p += 4)
		FUN_00467d60(GAME_VAR(void *, p));
	GAME_CDECL(0x456cd0, void, void)();
	return GAME_CDECL(0x467b70, u32, void)();
}

#define ChoosePixelFormat(dc, pfd) IMPORT(0x4a902c, int, void *, const void *)(dc, pfd)
#define SetPixelFormat(dc, format, pfd) IMPORT(0x4a9030, int, void *, int, const void *)(dc, format, pfd)

/* 0x467e60: the GL window's pixel format chosen and set: double-buffered (flags 0x21) RGBA with 0xa0e818 colour and
   0xa0e924 depth bits. A message and 0 when there is none, it needs a palette, or it cannot be set; 1 when set.
   (The original fills only these fields and leaves the rest of the descriptor as the stack had it; here it is
   zeroed.) */
int (glWindow_setupPixelFormat)(void *dc)
{
	u8 pfd[0x28];   /* PIXELFORMATDESCRIPTOR */
	memset(pfd, 0, sizeof pfd);
	*(u16 *)pfd = 0x28;                  /* nSize */
	*(u16 *)(pfd + 2) = 1;               /* nVersion */
	*(u32 *)(pfd + 4) = 0x21;            /* PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL */
	pfd[9] = GAME_VAR(u8, 0xa0e818);     /* cColorBits */
	pfd[0x17] = GAME_VAR(u8, 0xa0e924);  /* cDepthBits */
	int format = ChoosePixelFormat(dc, pfd);
	if (!format) {
		GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4e5c);   /* sys_errorMessageNoName */
		return 0;
	}
	if (pfd[4] & 0x80) {   /* PFD_NEED_PALETTE */
		GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4e30);
		return 0;
	}
	if (!SetPixelFormat(dc, format, pfd)) {
		GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4df8);
		return 0;
	}
	return 1;
}

/* 0x42f000: the window's pixel format from the game's descriptor (0x4b1020), filled in the first time (flag bit 1 of
   0x9dbefc): (video depth 0x83a9c4 + 1) * 16 colour bits, 16 depth bits, the rest zero. 1 when set; 0 when there
   is none, it needs a palette, or it cannot be set */
int (gfx_setPixelFormat)(void *dc)
{
	u8 *pfd = (u8 *)0x4b1020;
	if (!(GAME_VAR(u8, 0x9dbefc) & 1)) {
		GAME_VAR(u8, 0x9dbefc) |= 1;
		pfd[9] = (u8)((GAME_VAR(u8, 0x83a9c4) + 1) << 4);   /* cColorBits */
		memset(pfd + 0xa, 0, 0x17 - 0xa);
		pfd[0x17] = 0x10;                                    /* cDepthBits */
		memset(pfd + 0x18, 0, 0x28 - 0x18);
	}
	int format = ChoosePixelFormat(dc, pfd);
	if (!format || (pfd[4] & 0x80))
		return 0;
	return SetPixelFormat(dc, format, pfd) != 0;
}
