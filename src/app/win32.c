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

#define g_glWindowMade GAME_VAR(int, 0xa0e930)        /* the window exists (it is made once) */
#define g_glWindow GAME_VAR(void *, 0xa0e934)
#define g_glTitle ((char *)0xa0e81c)                   /* also the window class's, icon's and menu's name */

/* 0x468250: the game's GL window made, once (a second call: a message and NULL), with title, width x height and
   colour / depth bits (0xa0e810, 0xa0e928, 0xa0e818, 0xa0e924) kept. Without a given window (window and other
   NULL): its class registered (glWindow_wndProc, the icon named as the title, arrow cursor), the display mode
   switched in full screen (failing that, a message and windowed), a pop-up window of that size made, shown and
   focused; otherwise the given window (and other, 0xa0e938) taken and resized. Then the GL state (glWindow_4684c0);
   returns the window */
void *(glWindow_init)(const char *title, int width, int height, int colourBits, int depthBits, int fullscreen,
                      void *window, void *other)
{
	if (g_glWindowMade == 1) {
		GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4fd8);   /* sys_errorMessageNoName */
		return NULL;
	}
	strcpy(g_glTitle, title);
	GAME_VAR(int, 0xa0e818) = colourBits;
	GAME_VAR(int, 0xa0e924) = depthBits;
	GAME_VAR(int, 0xa0e920) = fullscreen;
	GAME_VAR(int, 0xa0e810) = width;
	GAME_VAR(int, 0xa0e928) = height;
	if (window == NULL && other == NULL) {
		u32 wc[10];   /* WNDCLASSA */
		wc[0] = 0;                 /* style */
		wc[1] = 0x4680d0;          /* glWindow_wndProc */
		wc[2] = 0;
		wc[3] = 0;
		wc[4] = (u32)GetModuleHandleA(NULL);
		wc[5] = (u32)IMPORT(0x4a92c4, void *, void *, const char *)(GetModuleHandleA(NULL), g_glTitle);   /* LoadIconA */
		wc[6] = (u32)IMPORT(0x4a933c, void *, void *, u32)(NULL, 0x7f00);                               /* LoadCursorA(IDC_ARROW) */
		wc[7] = 6;                 /* COLOR_WINDOW + 1 */
		wc[8] = (u32)g_glTitle;    /* menu name */
		wc[9] = (u32)g_glTitle;    /* class name */
		if (!(IMPORT(0x4a92b8, u16, const u32 *)(wc))) {                                               /* RegisterClassA */
			GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4fa4);
			return NULL;
		}
		if (GAME_VAR(int, 0xa0e920) == 1 &&
		    !GAME_CDECL(0x467f20, int, int, int, int)(GAME_VAR(int, 0xa0e810), GAME_VAR(int, 0xa0e928), GAME_VAR(int, 0xa0e818))) {
			GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4f50);   /* glWindow_setDisplayModeBy failed */
			GAME_VAR(int, 0xa0e920) = 0;
		}
		g_glWindow = IMPORT(0x4a9350, void *, u32, const char *, const char *, u32, int, int, int, int, void *, void *, void *, void *)(
			0, g_glTitle, g_glTitle, 0x86000000, 0, 0, GAME_VAR(int, 0xa0e810), GAME_VAR(int, 0xa0e928), NULL, NULL,
			GetModuleHandleA(NULL), NULL);                                                             /* CreateWindowExA: WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN */
		if (g_glWindow == NULL) {
			GAME_CDECL(0x46c840, int, const char *)((const char *)0x4c4f14);
			return NULL;
		}
		IMPORT(0x4a92bc, int, void *, int)(g_glWindow, 10);   /* ShowWindow(SW_SHOWDEFAULT) */
		IMPORT(0x4a92c0, int, void *)(g_glWindow);            /* UpdateWindow */
		IMPORT(0x4a935c, void *, void *)(g_glWindow);         /* SetFocus */
		g_glWindowMade = 1;
	} else {
		g_glWindow = window;
		GAME_VAR(void *, 0xa0e938) = other;
		glWindow_resize(width, height);
	}
	GAME_CDECL(0x4684c0, void, void)();   /* glWindow_4684c0 */
	GAME_VAR(int, 0x4c4de8) = -1;
	return g_glWindow;
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

#define SendMessageA(hwnd, msg, w, l) IMPORT(0x4a92ec, int, void *, u32, u32, u32)(hwnd, msg, w, l)

/* 0x43f460: the chat input box, `chars` letters wide (0x76d418): a 12-pixel font (face 0x4b29b0, 0x9dd8e4) and an
   edit control (0x9dd888) on the main window at the chat line (0x9da3d8 - 5, 0x9da3dc + 0x21), subclassed by
   0x440840 (the old procedure in 0x9dd868), focused, holding the typed line (0x9dc92c) with the caret at its end.
   Returns the last SendMessageA's eax */
int (chat_createEdit)(int chars)
{
	struct { int height, width, escapement, orientation, weight; u8 italic, underline, strikeOut, charSet, outPrecision,
	         clipPrecision, quality, pitchAndFamily; char face[32]; } font;   /* LOGFONTA */
	memset(&font, 0, sizeof font);
	font.height = -12;
	font.charSet = 1;   /* DEFAULT_CHARSET */
	strcpy(font.face, (const char *)0x4b29b0);
	GAME_VAR(int, 0x76d418) = chars;
	GAME_VAR(void *, 0x9dd8e4) = IMPORT(0x4a9038, void *, const void *)(&font);   /* CreateFontIndirectA */
	void *edit = IMPORT(0x4a9350, void *, u32, const char *, const char *, u32, int, int, int, int, void *, u32, void *, void *)(
		0, (const char *)0x4b29a8, NULL, 0x40000400, GAME_VAR(int, 0x9da3d8) - 5, GAME_VAR(int, 0x9da3dc) + 0x21,
		chars * 8, 0x18, GAME_VAR(void *, 0x4ded18), 0xca, GAME_VAR(void *, 0x67ef18), NULL);   /* CreateWindowExA("EDIT") */
	GAME_VAR(void *, 0x9dd888) = edit;
	if (edit) {
		SendMessageA(edit, 0x30, GAME_VAR(u32, 0x9dd8e4), 0);   /* WM_SETFONT */
		edit = GAME_VAR(void *, 0x9dd888);
	}
	GAME_VAR(u32, 0x9dd868) = IMPORT(0x4a9354, u32, void *, int, u32)(edit, -4, 0x440840);   /* SetWindowLongA(GWL_WNDPROC) */
	IMPORT(0x4a935c, void *, void *)(GAME_VAR(void *, 0x9dd888));   /* SetFocus */
	u32 length = strlen((const char *)0x9dc92c);
	SendMessageA(GAME_VAR(void *, 0x9dd888), 0xc, 0, 0x9dc92c);   /* WM_SETTEXT */
	return SendMessageA(GAME_VAR(void *, 0x9dd888), 0xb1, length, length);   /* EM_SETSEL */
}
