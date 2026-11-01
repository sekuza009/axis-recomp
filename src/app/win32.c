/* win32.c: small Win32 / multimedia wrappers. */
#include <stdarg.h>
#include <string.h>
#include "../game.h"

#define MCI_PAUSE 0x809
#define MCI_NOTIFY 1

/* 0x43f580: the current directory into the game's path buffer (0x76d224, 0x105 bytes) */
u32 (app_readCurrentDirectory)(void)
{
	return GetCurrentDirectoryA(0x105, (char *)(OBJ(g_messages) + 0x1f400));
}

/* 0x46c580: a message box over the active window (title, text); MessageBox's answer */
int (sys_messageBoxOverActive)(const char *title, const char *text)
{
	return MessageBoxA(GetActiveWindow(), text, title, 0);
}

/* 0x46c540: the MCI device (the CD audio) paused, notifying the window kept in its parameters */
u32 (mci_pause)(void)
{
	u32 params[3] = { g_mciCallback, g_mciFrom, g_mciTo };
	return mciSendCommandA(g_mciDevice, MCI_PAUSE, MCI_NOTIFY, params);
}

/* 0x41edf0: a printf-formatted message box titled "User Message" (the arguments' address kept in 0x4dd0b4 while
   formatting); MessageBox's answer */
int (sys_messageBox)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	g_messageBoxArgs = args;
	vsprintf((char *)IMG(0x4dd0d0), format, args);
	(*(void **)&g_messageBoxArgs) = NULL;
	int answer = MessageBoxA(GetActiveWindow(), (const char *)IMG(0x4dd0d0), (const char *)STR(0x4b043c, "User Message ^_^;"), 0);
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
	g_glWidth = width;
	g_glHeight = height;
	IMPORT(0x4a91d4, void, int, int, int, int)(0, 0, width, height);   /* glViewport */
	if (g_fullScreen == 1 &&
	    !GAME_FN(glWindow_setDisplayModeBy, 0x467f20, int, int, int, int)(g_glWidth, g_glHeight, 0)) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c500c, "glWindow screen resolution change fai..."));   /* sys_errorMessageNoName */
		return 0;
	}
	g_glCachedState = -1;
	return 1;
}

#define g_glWindowMade GAME_VAR(int, 0xa0e930)        /* the window exists (it is made once) */
#define g_glWindow GAME_VAR(void *, 0xa0e934)
#define g_glTitle ((char *)IMG(0xa0e81c))                   /* also the window class's, icon's and menu's name */

/* 0x468250: the game's GL window made, once (a second call: a message and NULL), with title, width x height and
   colour / depth bits (0xa0e810, 0xa0e928, 0xa0e818, 0xa0e924) kept. Without a given window (window and other
   NULL): its class registered (glWindow_wndProc, the icon named as the title, arrow cursor), the display mode
   switched in full screen (failing that, a message and windowed), a pop-up window of that size made, shown and
   focused; otherwise the given window (and other, 0xa0e938) taken and resized. Then the GL state (gfx_resetState);
   returns the window */
void *(glWindow_init)(const char *title, int width, int height, int colourBits, int depthBits, int fullscreen,
                      void *window, void *other)
{
	if (g_glWindowMade == 1) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4fd8, "glWindow duplicate initialization - g..."));   /* sys_errorMessageNoName */
		return NULL;
	}
	strcpy(g_glTitle, title);
	g_glColourBits = colourBits;
	(*(int *)&g_glDepthBits) = depthBits;
	g_fullScreen = fullscreen;
	g_glWidth = width;
	g_glHeight = height;
	if (window == NULL && other == NULL) {
		u32 wc[10];   /* WNDCLASSA */
		wc[0] = 0;                 /* style */
		wc[1] = FN_ADDR(glWindow_wndProc, 0x4680d0);
		wc[2] = 0;
		wc[3] = 0;
		wc[4] = (u32)GetModuleHandleA(NULL);
		wc[5] = (u32)IMPORT(0x4a92c4, void *, void *, const char *)(GetModuleHandleA(NULL), g_glTitle);   /* LoadIconA */
		wc[6] = (u32)IMPORT(0x4a933c, void *, void *, u32)(NULL, 0x7f00);                               /* LoadCursorA(IDC_ARROW) */
		wc[7] = 6;                 /* COLOR_WINDOW + 1 */
		wc[8] = (u32)g_glTitle;    /* menu name */
		wc[9] = (u32)g_glTitle;    /* class name */
		if (!(IMPORT(0x4a92b8, u16, const u32 *)(wc))) {                                               /* RegisterClassA */
			GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4fa4, "glWindow RegisterClass() failed - glW..."));
			return NULL;
		}
		if (g_fullScreen == 1 &&
		    !GAME_FN(glWindow_setDisplayModeBy, 0x467f20, int, int, int, int)(g_glWidth, g_glHeight, g_glColourBits)) {
			GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4f50, "glWindow full screen mode failed, win..."));   /* glWindow_setDisplayModeBy failed */
			g_fullScreen = 0;
		}
		g_glWindow = IMPORT(0x4a9350, void *, u32, const char *, const char *, u32, int, int, int, int, void *, void *, void *, void *)(
			0, g_glTitle, g_glTitle, 0x86000000, 0, 0, g_glWidth, g_glHeight, NULL, NULL,
			GetModuleHandleA(NULL), NULL);                                                             /* CreateWindowExA: WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN */
		if (g_glWindow == NULL) {
			GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4f14, "glWindow window handle initializing f..."));
			return NULL;
		}
		IMPORT(0x4a92bc, int, void *, int)(g_glWindow, 10);   /* ShowWindow(SW_SHOWDEFAULT) */
		IMPORT(0x4a92c0, int, void *)(g_glWindow);            /* UpdateWindow */
		IMPORT(0x4a935c, void *, void *)(g_glWindow);         /* SetFocus */
		g_glWindowMade = 1;
	} else {
		g_glWindow = window;
		g_hdc = other;   /* the GL window's DC (g_hdc below) */
		glWindow_resize(width, height);
	}
	GAME_FN(gfx_resetState, 0x4684c0, void, void)();   /* gfx_resetState */
	g_glCachedState = -1;
	return g_glWindow;
}

#define ChangeDisplaySettingsA(mode, flags) IMPORT(0x4a9314, int, void *, u32)(mode, flags)
#define GetDeviceCaps(dc, index) IMPORT(0x4a9034, int, void *, int)(dc, index)
#define g_modeChanged GAME_VAR(int, 0xa0e940)          /* the display mode was switched (to be put back) */
#define g_glDc GAME_VAR(void *, 0xa0e938)
#define g_desktopW GAME_VAR(int, 0xa0e92c)             /* the desktop's mode before the switch */
#define g_desktopH GAME_VAR(int, 0xa0e814)
#define g_desktopBits GAME_VAR(int, 0xa0e91c)

/* a DEVMODEA asking for width x height (and bits). (The original fills only these fields and leaves the
   rest as the stack had it; here it is zeroed.) */
static void display_mode(u8 *mode, int width, int height, int bits, u32 fields)
{
	memset(mode, 0, 0x94);
	*(u16 *)(mode + 0x24) = 0x94;                         /* dmSize */
	*(u32 *)(mode + 0x28) = fields;   /* 0x1c0000: DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT */
	*(u32 *)(mode + 0x68) = bits;
	*(u32 *)(mode + 0x6c) = width;
	*(u32 *)(mode + 0x70) = height;
}

/* 0x468050: the desktop's mode put back after a switch (failing that, a message and 0); 1 */
int (glWindow_restoreDisplayMode)(void)
{
	if (g_modeChanged != 1)
		return 1;
	u8 mode[0x94];
	display_mode(mode, g_desktopW, g_desktopH, g_desktopBits, 0x1c0000);
	if (ChangeDisplaySettingsA(mode, 0)) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4ed4, "glWindow ChangeDisplaySettings() fail..."));   /* sys_errorMessageNoName */
		return 0;
	}
	g_modeChanged = 0;
	return 1;
}

/* 0x467f20: the display switched to width x height (bits: any when 0): the window's DC taken when there is none,
   the desktop's mode kept before the first switch; 1 when the screen is already in that mode or the switch worked
   (then 0xa0e940 is set), else a message and 0 */
int (glWindow_setDisplayModeBy)(int width, int height, int bits)
{
	void *dc = g_glDc;
	if (!dc)
		dc = g_glDc = IMPORT(0x4a9318, void *, void *)(GetActiveWindow());   /* GetDC */
	if (!g_modeChanged) {
		g_desktopW = GetDeviceCaps(dc, 8);       /* HORZRES */
		g_desktopH = GetDeviceCaps(g_glDc, 10);  /* VERTRES */
		g_desktopBits = GetDeviceCaps(g_glDc, 12);   /* BITSPIXEL */
		dc = g_glDc;
	}
	if (GetDeviceCaps(dc, 8) == width && GetDeviceCaps(g_glDc, 10) == height &&
	    (!bits || GetDeviceCaps(g_glDc, 12) == bits))
		return 1;
	u8 mode[0x94];
	display_mode(mode, width, height, bits, bits ? 0x1c0000 : 0x180000);
	if (ChangeDisplaySettingsA(mode, 0)) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4e94, "glWindow ChangeDisplaySettings() fail..."));
		return 0;
	}
	g_modeChanged = 1;
	return 1;
}

/* 0x42eed0 (by use the display mode set; with the exe patch's cave at 0x4a8e54 done here): the desktop's own size
   (0x67eefc x 0x76d430) is not switched to: a mode changed before (flag 0xb12a80) is left by
   ChangeDisplaySettingsA(NULL), else nothing (0). Any other size is remembered (0xb12a84 / 0xb12a88, the flag set)
   and set with 32 bits (the patch's choice, whatever bits asks), with ChangeDisplaySettingsA's flags. Returns its
   answer. (The original's DEVMODE also has its word at 0x3c, dmColor, at 0x800.) */
int (app_setDisplayMode)(int width, int height, u32 flags, int bits)
{
	(void)bits;
	if (width == g_desktopWidth && height == g_desktopHeight) {
		if (!g_displayModeChanged)
			return 0;
		g_displayModeChanged = 0;
		return ChangeDisplaySettingsA(NULL, 0);
	}
	g_otherModeWidth = width;
	g_otherModeHeight = height;
	g_displayModeChanged = 1;
	u8 mode[0x94];
	display_mode(mode, width, height, 32, 0x1c0000);
	*(u16 *)(mode + 0x3c) = 0x800;
	return ChangeDisplaySettingsA(mode, flags);
}

/* 0x4314e0: the game shut down: the object at 0x9087b4 deleted (it stays set), the screen restored (0x42eed0 with
   the desktop's size), the arrow cursor back, 0x4014c0, the music stopped, the ten sounds at 0x4dd4d4 released,
   the sound table released (0x456cd0) and DirectSound ended (0x467b70, whose eax it returns) */
u32 (wnd_setCursor)(void)
{
	void *object = (*(void **)&g_scene);
	if (object)
		GAME_THISCALL(**(u32 **)object, void, void *, int)(object, 1);   /* scalar deleting destructor */
	app_setDisplayMode(g_desktopWidth, g_desktopHeight, 0, g_desktopDepth);
	IMPORT(0x4a9340, void *, void *)(IMPORT(0x4a933c, void *, void *, u32)(NULL, 0x7f00));   /* SetCursor(LoadCursorA(IDC_ARROW)) */
	GAME_FN(input_releaseAll, 0x4014c0, void, void)();
	music_shutdown();
	for (u32 p = IMG(0x4dd4d4); p < IMG(0x4dd4fc); p += 4)
		mem_free(GAME_VAR(void *, p));
	GAME_FN(sound_freeAll, 0x456cd0, void, void)();
	return GAME_FN(sound_releaseDirectSound, 0x467b70, u32, void)();
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
	pfd[9] = (*(u8 *)&g_glColourBits);     /* cColorBits */
	pfd[0x17] = g_glDepthBits;  /* cDepthBits */
	int format = ChoosePixelFormat(dc, pfd);
	if (!format) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4e5c, "glWindow ChoosePixelFormat failed - s..."));   /* sys_errorMessageNoName */
		return 0;
	}
	if (pfd[4] & 0x80) {   /* PFD_NEED_PALETTE */
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)STR(0x4c4e30, "glWindow needs palette - setupPixelFo..."));
		return 0;
	}
	if (!SetPixelFormat(dc, format, pfd)) {
		GAME_FN(sys_errorMessageNoName, 0x46c840, int, const char *)((const char *)IMG(0x4c4df8));
		return 0;
	}
	return 1;
}

/* 0x42f000: the window's pixel format from the game's descriptor (0x4b1020), filled in the first time (flag bit 1 of
   0x9dbefc): (video depth 0x83a9c4 + 1) * 16 colour bits, 16 depth bits, the rest zero. 1 when set; 0 when there
   is none, it needs a palette, or it cannot be set */
int (gfx_setPixelFormat)(void *dc)
{
	u8 *pfd = (u8 *)STR(0x4b1020, "(");
	if (!(g_pixelFormatFilled & 1)) {
		g_pixelFormatFilled |= 1;
		pfd[9] = (u8)(((*(u8 *)&g_videoDepth) + 1) << 4);   /* cColorBits */
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
	strcpy(font.face, (const char *)STR(0x4b29b0, "Fixedsys"));
	g_chatEditLength = chars;
	g_inputFont = IMPORT(0x4a9038, void *, const void *)(&font);   /* CreateFontIndirectA */
	void *edit = IMPORT(0x4a9350, void *, u32, const char *, const char *, u32, int, int, int, int, void *, u32, void *, void *)(
		0, (const char *)STR(0x4b29a8, "EDIT"), NULL, 0x40000400, g_chatCaretX - 5, g_chatCaretY + 0x21,
		chars * 8, 0x18, g_mainWindow, 0xca, g_hInstance, NULL);   /* CreateWindowExA("EDIT") */
	g_hChatEdit = edit;
	if (edit) {
		SendMessageA(edit, 0x30, (*(u32 *)&g_inputFont), 0);   /* WM_SETFONT */
		edit = g_hChatEdit;
	}
	g_editOldProc = IMPORT(0x4a9354, u32, void *, int, u32)(edit, -4, FN_ADDR(chat_editSubclass, 0x440840));   /* SetWindowLongA(GWL_WNDPROC) */
	IMPORT(0x4a935c, void *, void *)(g_hChatEdit);   /* SetFocus */
	u32 length = strlen(g_chatLine);
	SendMessageA(g_hChatEdit, 0xc, 0, OBJ(g_chatLine));   /* WM_SETTEXT */
	return SendMessageA(g_hChatEdit, 0xb1, length, length);   /* EM_SETSEL */
}

/* ---- the start-up ---- */
#define GetSystemMetrics(index) IMPORT(0x4a9358, int, int)(index)
#define GetVersion() IMPORT(0x4a90fc, u32, void)()

/* the files the game checks for (each failing: "Run AxisPlay.exe" and 0) */
static int files_present(void)
{
	if (!app_checkFile_profeng() || !app_checkFile_profkor() || !app_checkFile_skirmish() ||
	    !app_checkFile_axisgame() || !app_checkFile_game()) {
		sys_messageBox((const char *)STR(0x4b04b0, "Run AxisPlay.exe"));
		return 0;
	}
	return 1;
}

/* 0x43fcc0: the game started (inst, show): outside the lobby (0x76d410) the files checked; a 640 x 480 default; the
   directory, data paths and messages; the process made DPI aware when user32 has SetProcessDPIAware (the exe
   patch's cave at 0x4a8e20); the desktop's size, DC and depth (0x67eefc, 0x76d430, 0x76d480, 0x76d3ec); the
   default keys and axis.cfg, 0x43f640, the display mode set (32 bits) and its answer reported (app_reportStartupProblem); the
   files checked again. The window class "AXIS" (WndProc 0x440070; app_registerWindowClassEx where GetVersion says
   so, else RegisterClassA; kept at 0x4e0ca8), the window at (0, -1), the screen's size with one more row (the
   patch's cave at 0x4a8f50), three timers, shown. Then the CD and the data (failing: the desktop's mode back, 0);
   screen 100, the cursor hidden, the clock check. Returns 1, or 0 on any failure */
int (app_init)(void *inst, int show)
{
	if (!g_startedFromLobby && !files_present())
		return 0;
	g_screenW = 640;
	g_screenH = 480;
	app_readCurrentDirectory();
	app_setDataPaths();
	data_loadMessages();
	void *user32 = GetModuleHandleA((const char *)STR(0x4ac820, "user32.dll"));
	if (user32) {
		void (STDCALL *dpi_aware)(void) = IMPORT(0x4a907c, void *, void *, const char *)(user32, (const char *)STR(0x4ac82c, "SetProcessDPIAware"));   /* GetProcAddress */
		if (dpi_aware)
			dpi_aware();
	}
	g_unusedInitWord = 0;
	g_desktopWidth = GetSystemMetrics(0);   /* SM_CXSCREEN */
	g_desktopHeight = GetSystemMetrics(1);
	void *dc = IMPORT(0x4a9318, void *, void *)(NULL);   /* GetDC */
	g_desktopDC = dc;
	g_desktopDepth = GetDeviceCaps(dc, 12);   /* BITSPIXEL */
	input_setDefaultKeyBindings();
	cfg_writeDefaultAxisCfg();
	app_screenSizeForMode();
	app_reportStartupProblem(app_setDisplayMode(g_screenW, g_screenH, 4, (g_videoDepth + 1) * 16));   /* CDS_FULLSCREEN */
	if (!g_startedFromLobby && !files_present())
		return 0;

	struct { u32 style; u32 proc; int cls_extra, wnd_extra; void *inst, *icon, *cursor, *brush; const char *menu, *name; } wc;
	wc.style = 0;
	wc.proc = FN_ADDR(game_wndProc, 0x440070);   /* WndProc */
	wc.cls_extra = wc.wnd_extra = 0;
	wc.inst = inst;
	wc.icon = IMPORT(0x4a92c4, void *, void *, const char *)(inst, NULL);   /* LoadIconA */
	wc.cursor = IMPORT(0x4a933c, void *, void *, u32)(NULL, 0x7f00);   /* LoadCursorA(IDC_ARROW) */
	wc.brush = IMPORT(0x4a903c, void *, int)(4);   /* GetStockObject(BLACK_BRUSH) */
	wc.menu = wc.name = (const char *)IMG(0x4b0714);
	int extended;   /* (GetVersion asked up to three times, as the original does) */
	if (GetVersion() < 0x80000000)
		extended = 0;
	else if (GetVersion() < 0x80000000)
		extended = 1;
	else
		extended = (u8)GetVersion() >= 4;
	if (extended) {
		if (!app_registerWindowClassEx(&wc))
			return 0;
	} else if (!(u16)IMPORT(0x4a92b8, u32, void *)(&wc))   /* RegisterClassA */
		return 0;

	memcpy((void *)IMG(0x4e0ca8), &wc, sizeof wc);
	g_hWndMain = IMPORT(0x4a9350, void *, u32, const char *, const char *, u32, int, int, int, int, void *, void *, void *, void *)
		(0, (const char *)IMG(0x4b0714), (const char *)STR(0x4b2874, "AXIS"), 0x86000000, 0, -1, g_screenW, g_screenH + 1, NULL, NULL, inst, NULL);   /* CreateWindowExA: WS_POPUP | WS_VISIBLE | WS_SYSMENU */
	if (!g_hWndMain)
		return 0;
	g_hInstance = inst;
	g_showCmd = show;
	static const u32 timers[3][2] = { { 0x29a, 60000 }, { 0x115c, 30000 }, { 0x309, 60000 } };
	for (int k = 0; k < 3; k++)
		IMPORT(0x4a9334, u32, void *, u32, u32, void *)(g_hWndMain, timers[k][0], timers[k][1], NULL);   /* SetTimer */
	IMPORT(0x4a92bc, int, void *, int)(g_hWndMain, show);   /* ShowWindow */
	IMPORT(0x4a92c0, int, void *)(g_hWndMain);   /* UpdateWindow */
	if (!app_checkCdAndLoad(inst)) {
		app_setDisplayMode(g_desktopWidth, g_desktopHeight, 0, g_desktopDepth);
		return 0;
	}
	g_menuState = 100;
	IMPORT(0x4a92c8, int, int)(0);   /* ShowCursor */
	g_clockCheckClosed = 1;
	sys_checkClockTampering();
	return 1;
}
#undef GetSystemMetrics
#undef GetVersion

/* 0x4680d0: the GL window's messages. Created: the cursor hidden, its DC (0xa0e938) given a pixel format (failing, the
   game quits) and a GL context (0xa0e93c) made current. Painted: begun and ended. Resized: the view resized. Closed:
   destroyed. Destroyed: the context and DC let go, the display mode restored, the cursor shown, the game quits. The
   rest go to DefWindowProcA */
long STDCALL (glWindow_wndProc)(void *wnd, u32 msg, u32 w, u32 l)
{
#define g_dc GAME_VAR(void *, 0xa0e938)
#define g_context GAME_VAR(void *, 0xa0e93c)
#define ShowCursor(show) IMPORT(0x4a92c8, int, int)(show)
#define PostQuitMessage(code) IMPORT(0x4a932c, void, int)(code)
	u32 rect[4], paint[0x10];
	switch (msg) {
	case 1:   /* WM_CREATE */
		ShowCursor(0);
		g_dc = IMPORT(0x4a9318, void *, void *)(wnd);   /* GetDC */
		if (!glWindow_setupPixelFormat(g_dc))
			PostQuitMessage(0);
		g_context = IMPORT(0x4a9230, void *, void *)(g_dc);   /* wglCreateContext */
		IMPORT(0x4a9254, int, void *, void *)(g_dc, g_context);   /* wglMakeCurrent */
		IMPORT(0x4a9310, int, void *, u32 *)(wnd, rect);   /* GetClientRect */
		return 0;
	case 0xf:   /* WM_PAINT */
		IMPORT(0x4a9308, void *, void *, u32 *)(wnd, paint);   /* BeginPaint */
		IMPORT(0x4a92dc, int, void *, u32 *)(wnd, paint);   /* EndPaint */
		return 0;
	case 0x10:   /* WM_CLOSE */
		IMPORT(0x4a9344, int, void *)(wnd);   /* DestroyWindow */
		return 0;
	case 5:   /* WM_SIZE */
		glWindow_resize(l & 0xffff, l >> 16);
		return 0;
	case 2:   /* WM_DESTROY */
		if (g_context)
			IMPORT(0x4a9274, int, void *)(g_context);   /* wglDeleteContext */
		if (g_dc)
			IMPORT(0x4a931c, int, void *, void *)(wnd, g_dc);   /* ReleaseDC */
		g_context = 0;
		g_dc = 0;
		glWindow_restoreDisplayMode();
		ShowCursor(1);
		PostQuitMessage(0);
		return 0;
	}
	return IMPORT(0x4a92f4, long, void *, u32, u32, u32)(wnd, msg, w, l);   /* DefWindowProcA */
#undef g_dc
#undef g_context
#undef ShowCursor
#undef PostQuitMessage
}

#define CallWindowProcA(proc, wnd, msg, w, l) IMPORT(0x4a930c, long, u32, u32, u32, u32, u32)(proc, wnd, msg, w, l)

/* the chat line closed by a key: its text kept (Enter) or dropped, the edit destroyed, the main window focused again
   and the line closed (chat_closeLine, sent or not) */
static void chat_close(void *edit, int sent)
{
	if (sent)
		SendMessageA(edit, 0xd, 0x80, OBJ(g_chatLine));   /* WM_GETTEXT */
	SendMessageA(edit, 0xc, 0, 0);                 /* WM_SETTEXT "" */
	IMPORT(0x4a9344, int, void *)(g_hChatEdit);   /* DestroyWindow */
	IMPORT(0x4a935c, void *, void *)(g_mainWindow);   /* SetFocus */
	GAME_FN(chat_closeLine, 0x431600, u32, int)(sent);   /* chat_closeLine */
	g_chatLineDone = 1;
}

/* 0x440840: the chat edit's window procedure (set by chat_createEdit). Keys: Enter, once the open delay (0x9da434)
   is not over 0x4a93e8, takes the line and sends it (the fade 0x9dc428 20); Esc drops it; Tab in the room
   (0x76d3e8 0x320) closes it (sent) and sets the fade by Shift (10 held, else 20); Home and Left are swallowed (0).
   Timers: 0x29a, in the lobby (0x4dbbf4 2), and 0x115c, when connected (0x9dd84c), send their keep-alives (0x17 to
   the lobby, 0x18 to the game server). Everything not swallowed goes on to the edit's own procedure (0x9dd868) */
long STDCALL (chat_editSubclass)(void *wnd, u32 msg, u32 w, u32 l)
{
	if (msg == 0x100) {   /* WM_KEYDOWN */
		switch (w) {
		case 0xd:   /* Enter */
			if (!(g_menuFade > k_0f)) {
				chat_close(wnd, 1);
				g_fieldTabKey = 0x14;
			}
			break;
		case 0x1b:   /* Esc */
			chat_close(wnd, 0);
			break;
		case 9:   /* Tab */
			if (g_menuState == 0x320) {
				IMPORT(0x4a9344, int, void *)(g_hChatEdit);   /* DestroyWindow */
				IMPORT(0x4a935c, void *, void *)(g_mainWindow);   /* SetFocus */
				GAME_FN(chat_closeLine, 0x431600, u32, int)(1);   /* chat_closeLine */
				g_fieldTabKey = 0x14;
				g_chatLineDone = 1;
				g_fieldTabKey = IMPORT(0x4a9338, short, int)(0x10) < 0 ? 10 : 20;   /* GetKeyState(VK_SHIFT) */
			}
			break;
		case 0x24: case 0x25:   /* Home, Left */
			return 0;
		}
	} else if (msg == 0x113) {   /* WM_TIMER */
		if (w == 0x29a) {
			if (g_arenaLobbyState == 2)
				net_send(0x17, 100);
		} else if (w == 0x115c && g_roomConnected)
			net_send(0x18, 0x65);
	}
	return CallWindowProcA(g_editOldProc, (u32)wnd, msg, w, l);
}

/* 0x43f9d0: the program. The launch file read (arena_readLaunchFile); a running launcher (window class 0x4b2834)
   told to quit, then half a second; the start time (GetSystemTime into 0x9dd878, timeGetTime 0x9dd8e8) and two
   seconds. A game already running (an "AXIS" window), or no CD (cd_findDrive), ends it with a message box. The
   language by the system's (Korean 0x412 / 0x812: 1 and the message 0x4b2794, else 2 and 0x4b27e4, at 0x9dae74 /
   0x9dd8c8); the clock check; outside the lobby (0x76d410) the launcher, start mode and file checks, each failing
   with its message. The launcher told to quit again, app_init (failing: a message box), the screen saver off, then
   the message loop (TranslateMessage while 0x68039c) with a frame (0x43f980) and the fade step after each round of
   messages, until 0x4b2790 is cleared. Returns 1, or 0 on the exits. (Named game_WinMain: WinMain is the SDK's) */
u32 STDCALL (game_WinMain)(void *inst, void *prev, const char *cmd, int show)
{
#define FindWindowA(cls, name) IMPORT(0x4a92cc, void *, const char *, const char *)(cls, name)
#define Sleep(ms) IMPORT(0x4a9110, void, u32)(ms)
	arena_readLaunchFile(cmd);
	void *launcher = FindWindowA((const char *)STR(0x4b2834, "#32770"), (const char *)STR(0x4b2854, "\364\270\315\366\361\375\340\362\312\245\341\334\320\357"));
	if (launcher) {
		PostMessageA(launcher, 0x12, 0, 0);   /* WM_QUIT */
		Sleep(500);
	}
	IMPORT(0x4a910c, void, void *)((void *)OBJ(g_clockLastTime));              /* GetSystemTime */
	g_startTicks = IMPORT(0x4a9364, u32, void)();       /* timeGetTime */
	Sleep(2000);
	if (FindWindowA((const char *)IMG(0x4b0714), NULL)) {
		MessageBoxA(NULL, (const char *)STR(0x4b2a00, "This application is already run!!"), (const char *)STR(0x4b2554, "Warning"), 0);
		return 0;
	}
	if (!cd_findDrive()) {
		MessageBoxA(NULL, (const char *)STR(0x4b2528, "Please insert Axis CD in your CD-ROM ..."), (const char *)STR(0x4b2554, "Warning"), 0);
		return 0;
	}
	u16 language = IMPORT(0x4a9100, u16, void)();   /* GetSystemDefaultLangID */
	g_languageId = language;
	if (language == 0x412 || language == 0x812) {
		g_language = 1;
		(*(u32 *)&g_launchMessage) = STR(0x4b2794, "Axisplay.exe \310\255\300\317\300\314 \300\337\270\370\265\307\276\372\275\300\264\317\264\331");
	} else {
		g_language = 2;
		(*(u32 *)&g_launchMessage) = STR(0x4b27e4, "Axisplay.exe has been expired");
	}
	sys_checkClockTampering();
	if (!g_startedFromLobby) {
		if (!app_checkLauncherRunning()) {
			sys_messageBox(g_launchMessage);
			return 0;
		}
		if (!reg_readStartMode()) {
			sys_messageBox((const char *)STR(0x4b04b0, "Run AxisPlay.exe"));
			return 0;
		}
		if (!files_present())
			return 0;
	}
	launcher = FindWindowA((const char *)STR(0x4b2834, "#32770"), (const char *)STR(0x4b2854, "\364\270\315\366\361\375\340\362\312\245\341\334\320\357"));
	if (launcher)
		PostMessageA(launcher, 0x12, 0, 0);
	if (!app_init(inst, show)) {
		MessageBoxA(g_hWndMain, (const char *)STR(0x4b29ec, "Windows Init Faild"), (const char *)STR(0x4b141c, "ERROR"), 0);
		return 0;
	}
	g_gameRunning = 1;
	IMPORT(0x4a92d0, int, u32, u32, void *, u32)(0x61, 1, NULL, 0);   /* SystemParametersInfoA(SPI_SETSCREENSAVERRUNNING) */
	u32 msg[7];   /* MSG */
	while (g_gameRunning) {
		while (IMPORT(0x4a92d4, int, void *, void *, u32, u32, u32)(msg, NULL, 0, 0, 0) == 1)   /* PeekMessageA */
			if (IMPORT(0x4a92d8, int, void *, void *, u32, u32)(msg, NULL, 0, 0)) {   /* GetMessageA */
				if (g_paused)
					IMPORT(0x4a9348, int, const void *)(msg);   /* TranslateMessage */
				IMPORT(0x4a934c, long, const void *)(msg);       /* DispatchMessageA */
			}
		editField_readTyping();
		app_frame();
	}
	return 1;
#undef FindWindowA
#undef Sleep
}

/* 0x440070: the game window's messages (its class's procedure; the patch DLL subclasses it, see axisnet's input_read).
   Returns 1 for the messages it takes (0 where noted), DefWindowProcA's answer for the rest.
   - WM_CREATE: the window's DC (g_desktopDC) given a pixel format (failing: the game quits) and a GL context
     (0x9087b8); the GL state for the client size; the pointer at the menus' centre.
   - WM_SIZE: the 3D view for the client size (gfx_setup3DView).
     As the installed exe has both (widefix.py: wrappers at 0x4a8f6a / 0x4a8f87, called from 0x440116 / 0x440186):
     the client is one pixel taller than the game's height (the window starts at y -1, so the driver keeps it
     composited), so that height is taken back to the game's, and the menus' projection switch sets its viewport
     again next time (g_projMode -1).
   - WM_PAINT: begun and ended. WM_CLOSE: the DC let go, the arena session left, the network closed, the three
     network timers stopped, the cursor put back, the window destroyed.
   - WM_DESTROY: the screen saver back on, the DC and the chat line let go, the cursor shown, the game quits; then,
     by the exit mode (0x4df048): 0 the start mode 0 and the data files spoilt (and 0x4b2790 cleared), 1 the start
     mode 1 and AxisGL.exe started again, 2 / 3 the start mode 0, the files spoilt and axispatch.exe ("nstower") /
     DServer.exe started, 99 the files spoilt and the ending movie; the process ends.
   - WM_ACTIVATEAPP: the activation kept (0x9dd864). As the installed exe has it (cursorfix.py, through 0x44037c ->
     0x4a8ec1): the Windows cursor hidden while active and shown while not (counted down / up until it is), and the
     window restored when the game comes back (borderless); then (widefix.py's handler at 0x4a8ecb) a display mode
     the game had set (0xb12a80) is given up while it is in the background (the window minimised) and set again
     (0xb12a84 x 0xb12a88) when it comes back.
   - WM_SYSCOMMAND: moving, sizing, maximising, the screen saver, closing, the task list, the keyboard menu and
     minimising are swallowed (0); SC_RESTORE goes to DefWindowProcA (cursorfix.py changed 0x44050c: the game
     swallowed it), though as the command 0xf120 itself, not as WM_SYSCOMMAND; anything else 1.
   - WM_TIMER: 0x29a in the arena's lobby a keep-alive (net_send 0x17), 0x115c in a room another (0x18); 0x378 the
     arena's session search: the sessions listed; after 30 tries the join gives up, else a session found ends it
     (none: try again next time); either way the timer stops and the room closes (app_onClose) or the arena's join
     is answered (app_shutdown).
   - 0x40a, 0x40c (the game server's and the lobby's sockets): closed, both sockets closed and the menus back at
     the main menu (0), unless in a match; else the reply read and the connection's step and search result
     taken from it. */
long STDCALL (game_wndProc)(void *wnd, u32 msg, u32 w, u32 l)
{
#define g_glContext GAME_VAR(void *, 0x9087b8)
#define g_exitMode GAME_VAR(int, 0x4df048)
#define ShowCursor(show) IMPORT(0x4a92c8, int, int)(show)
#define PostQuitMessage(code) IMPORT(0x4a932c, void, int)(code)
#define ShowWindow(wnd, how) IMPORT(0x4a92bc, int, void *, int)(wnd, how)
#define DestroyWindow(wnd) IMPORT(0x4a9344, int, void *)(wnd)
#define ReleaseDC(wnd, dc) IMPORT(0x4a931c, int, void *, void *)(wnd, dc)
#define GetClientRect(wnd, rect) IMPORT(0x4a9310, int, void *, int *)(wnd, rect)
#define ExitProcess(code) IMPORT(0x4a90f8, void, u32)(code)
#define ShellExecuteA(wnd, verb, file, args, dir, show) \
	IMPORT(0x4a92b0, void *, void *, const char *, const char *, const char *, const char *, int)(wnd, verb, file, args, dir, show)
#define GAME_HEIGHT(h) ((h) - 1 == g_screenH ? (h) - 1 : (h))   /* widefix.py: the client's extra row taken back */
	u16 now[8];
	int rect[4];
	u32 paint[0x10];
	IMPORT(0x4a90f4, void, u16 *)(now);   /* GetLocalTime (unused) */
	switch (msg) {
	case 1:   /* WM_CREATE */
		g_desktopDC = IMPORT(0x4a9318, void *, void *)(wnd);   /* GetDC */
		if (!GAME_FN(gfx_setPixelFormat, 0x42f000, int, void *)(g_desktopDC)) {   /* gfx_setPixelFormat */
			PostQuitMessage(0);
			return 1;
		}
		g_glContext = IMPORT(0x4a9230, void *, void *)(g_desktopDC);   /* wglCreateContext */
		IMPORT(0x4a9254, int, void *, void *)(g_desktopDC, g_glContext);   /* wglMakeCurrent */
		GetClientRect(wnd, rect);
		g_projMode = -1;
		GAME_FN(gfx_initGLState, 0x42f150, u32, int, int)(rect[2], GAME_HEIGHT(rect[3]));   /* gfx_initGLState */
		g_mouseX = 0x140;
		g_mouseY = 0xf0;
		g_mouseWheelTurned = 0;
		return 1;
	case 0xf:   /* WM_PAINT */
		IMPORT(0x4a9308, void *, void *, u32 *)(wnd, paint);   /* BeginPaint */
		IMPORT(0x4a92dc, int, void *, u32 *)(wnd, paint);   /* EndPaint */
		return 1;
	case 5:   /* WM_SIZE */
		GetClientRect(wnd, rect);
		g_projMode = -1;
		GAME_FN(gfx_setup3DView, 0x42f0f0, u32, int, int)(rect[2], GAME_HEIGHT(rect[3]));   /* gfx_setup3DView */
		return 1;
	case 0x10:   /* WM_CLOSE */
		if (g_desktopDC)
			ReleaseDC(wnd, g_desktopDC);
		g_glContext = NULL;
		g_desktopDC = NULL;
		g_lobbyPending = 1;
		arena_leaveSession();
		net_disconnect();
		KillTimer(g_hWndMain, 0x29a);
		KillTimer(g_hWndMain, 0x115c);
		KillTimer(g_hWndMain, 0x309);
		g_lobbyPending = 1;
		GAME_FN(wnd_setCursor, 0x4314e0, u32, void)();   /* wnd_setCursor */
		DestroyWindow(wnd);
		return 1;
	case 2:   /* WM_DESTROY */
		IMPORT(0x4a92d0, int, u32, u32, void *, u32)(0x61, 0, NULL, 0);   /* SystemParametersInfoA: SPI_SETSCREENSAVERRUNNING off */
		if (g_desktopDC)
			ReleaseDC(wnd, g_desktopDC);
		if (g_hChatEdit)
			DestroyWindow(g_hChatEdit);
		ShowCursor(1);
		PostQuitMessage(0);
		switch (g_exitMode) {
		case 0:
			GAME_FN(reg_writeStartMode, 0x43f7f0, u32, u32)(0);   /* reg_writeStartMode */
			GAME_FN(app_deleteDataFiles, 0x43f8b0, u32, void)();   /* app_deleteDataFiles */
			g_gameRunning = 0;
			ExitProcess(0);
			return 0;
		case 1:
			GAME_FN(reg_writeStartMode, 0x43f7f0, u32, u32)(1);
			ShellExecuteA(NULL, (const char *)STR(0x4b2a5c, "open"), (const char *)STR(0x4b2a64, "AxisGL.exe"), NULL, NULL, 10);
			ExitProcess(0);
			return 0;
		case 2:
			GAME_FN(reg_writeStartMode, 0x43f7f0, u32, u32)(0);
			GAME_FN(app_deleteDataFiles, 0x43f8b0, u32, void)();
			ShellExecuteA(NULL, (const char *)STR(0x4b2a5c, "open"), (const char *)STR(0x4b2a44, "axispatch.exe"), (const char *)STR(0x4b2a54, "nstower"), NULL, 10);
			ExitProcess(0);
			return 0;
		case 3:
			GAME_FN(reg_writeStartMode, 0x43f7f0, u32, u32)(0);
			GAME_FN(app_deleteDataFiles, 0x43f8b0, u32, void)();
			ShellExecuteA(NULL, (const char *)STR(0x4b2a5c, "open"), (const char *)STR(0x4b2a38, "DServer.exe"), (const char *)STR(0x4b13ec, "1"), NULL, 10);
			ExitProcess(0);
			return 0;
		case 99:
			GAME_FN(app_deleteDataFiles, 0x43f8b0, u32, void)();
			GAME_CDECL(0x46c420, void, int, const char *, int, int)(0, (const char *)STR(0x4b2a24, "initdata/battle.sra"), g_desktopWidth, g_desktopHeight);   /* movie_playEnding: initdata\battle.sra */
			ExitProcess(0);
		}
		ExitProcess(0);
		return 0;
	case 0x1c: {   /* WM_ACTIVATEAPP */
		g_unusedLastWParam = w;
		if (w) {
			while (ShowCursor(0) >= 0)
				;
			if (!g_displayModeChanged)
				ShowWindow(g_hWndMain, 9);   /* SW_RESTORE */
			if (g_displayModeLeft) {
				g_displayModeLeft = 0;
				app_setDisplayMode(g_otherModeWidth, g_otherModeHeight, 4, 0x20);
				ShowWindow(g_hWndMain, 9);
			}
		} else {
			while (ShowCursor(1) < 0)
				;
			if (g_displayModeChanged) {
				ShowWindow(g_hWndMain, 7);   /* SW_SHOWMINNOACTIVE */
				IMPORT(0x4a9314, int, void *, u32)(NULL, 0);   /* ChangeDisplaySettingsA: the desktop's mode back */
				g_displayModeChanged = 0;
				g_displayModeLeft = 1;
			}
		}
		return 1;
	}
	case 0x112: {   /* WM_SYSCOMMAND */
		u32 command = w & 0xfff0;
		if (command == 0xf120)   /* SC_RESTORE: DefWindowProcA, with the command where the message goes (cursorfix.py's
		                            jump arrives with the command in eax, which the call passes as the message) */
			return IMPORT(0x4a92f4, long, void *, u32, u32, u32)(wnd, command, w, l);
		if (command == 0xf130 || command == 0xf040 || command == 0xf050 || command == 0xf170 || command == 0xf060 ||
		    command == 0xf030 || command == 0xf020 || command == 0xf140)
			return 0;
		return 1;
	}
	case 0x113:   /* WM_TIMER */
		if (w == 0x29a) {
			if (g_arenaLobbyState == 2)
				net_send(0x17, 100);
		} else if (w == 0x378) {
			dplay_listSessions();
			if (++g_arenaSearchTicks > 30) {
				g_arenaJoinWaiting = 1;
			} else {
				g_receivedSession = (const u8 *)net_sessionValue(0);
				if (!g_receivedSession)
					return 1;
				g_arenaJoinPending = 1;
			}
			KillTimer(wnd, 0x378);
			if (g_screen == 800)
				GAME_FN(app_onClose, 0x434e70, u32, void)();   /* app_onClose */
			else
				GAME_FN(app_shutdown, 0x4062b0, void, void)();   /* app_shutdown */
		} else if (w == 0x115c) {
			if (g_roomConnected)
				net_send(0x18, 0x65);
		}
		return 1;
	case 0x40a:   /* the game server's socket */
		if ((u16)l == 0x20) {   /* FD_CLOSE */
			GAME_FN(net_closeSockets, 0x4520e0, u32, void)();   /* net_closeSockets */
			if (g_screen != 0x270f)
				GAME_FN(menu_returnToMain, 0x41edc0, void, void)();   /* menu_returnToMain */
			return 0;
		}
		GAME_FN(net_recv, 0x452620, void, void)();   /* net_recv */
		switch (g_lobbyStatus) {
		case 0x29: g_connectStep = 4; break;
		case 0x66: g_connectStep = 1; break;
		case 0x67: g_connectStep = 3; break;
		default: g_connectStep = 0; break;
		}
		switch (g_serverConnectionState) {
		case 0x29: g_serverAnswerIn = 1; g_searchResult = 4; break;
		case 0xca: g_serverAnswerIn = 1; g_searchResult = 1; break;
		case 0xcb: g_serverAnswerIn = 1; g_searchResult = 3; break;
		}
		return 1;
	case 0x40c:   /* the lobby's socket */
		if ((u16)l == 0x20) {
			GAME_FN(net_closeSockets, 0x4520e0, u32, void)();
			if (g_screen != 0x270f)
				GAME_FN(menu_returnToMainFromRoom, 0x41ed70, void, void)();   /* menu_returnToMainFromRoom */
			return 0;
		}
		GAME_FN(net_recv, 0x452620, void, void)();
		switch (g_gameServerStatus) {
		case 0x28: g_connectStep = 4; break;
		case 0x66: g_connectStep = 1; break;
		case 0x67: g_connectStep = 3; break;
		default: g_connectStep = 0; break;
		}
		switch (g_gameServerState) {
		case 0x28: g_roomSearchAnswerIn = 1; g_searchResult = 4; break;
		case 0xca: g_roomSearchAnswerIn = 1; g_searchResult = 1; break;
		case 0xcb: g_roomSearchAnswerIn = 1; g_searchResult = 3; break;
		}
		if (g_playerListRefused)
			g_roomListWaiting = 1;
		if (g_netNoticeIn)
			g_accountNotice = 1;
		return 1;
	}
	return IMPORT(0x4a92f4, long, void *, u32, u32, u32)(wnd, msg, w, l);   /* DefWindowProcA */
#undef g_glContext
#undef g_exitMode
#undef ShowCursor
#undef PostQuitMessage
#undef ShowWindow
#undef DestroyWindow
#undef ReleaseDC
#undef GetClientRect
#undef ExitProcess
#undef ShellExecuteA
#undef GAME_HEIGHT
}
