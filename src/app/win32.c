/* win32.c: the game's Win32 side: the program (game_WinMain, app_init) and its window procedures, the GL window and
   the display mode, the text fields' hidden EDIT control, message boxes, the ending movie's MCI device and the
   current directory. */
#include <stdarg.h>
#include <string.h>
#include "../game.h"
#include "../plat/plat.h"
#include "../fixes/fixes.h"
#include "../wide.h"

#define MCI_PAUSE 0x809
#define MCI_NOTIFY 1

/* 0x43f580: the current directory (GetCurrentDirectoryA, 0x105 bytes) read into 0x76d224, which lies
   inside g_messages' storage (g_messages + 0x1f400, message line 1000); nothing reads it from there (this push is the
   only access to 0x76d224 in the original). Returns GetCurrentDirectoryA's answer */
u32 (app_readCurrentDirectory)(void)
{
	return FILE_CURRENT_DIRECTORY(0x105, AP(char, (OBJ(g_messages) + 0x1f400)));
}

/* 0x46c580: a message box over the active window (title, text); MessageBox's answer */
int (sys_messageBoxOverActive)(const char *title, const char *text)
{
	return MessageBoxA(GetActiveWindow(), text, title, 0);
}

/* 0x46c540: the ending movie's MCI device (g_mciDevice, the "AVIVideo" device movie_playEnding opened)
   sent MCI_PAUSE with MCI_NOTIFY and a parameter block copied from the one movie_playEnding gave MCI_PLAY
   (g_mciCallback, g_mciFrom, g_mciTo); mciSendCommandA's answer. Only caller: movie_playEnding, when Esc
   (GetAsyncKeyState 0x1b) cuts the movie short, just before MCI_CLOSE */
u32 (movie_pauseEnding)(void)
{
	u32 params[3] = { g_mciCallback, g_mciFrom, g_mciTo };
	return mciSendCommandA(g_mciDevice, MCI_PAUSE, MCI_NOTIFY, params);
}

/* 0x41edf0: a printf-formatted message box titled "User Message" (the arguments' address kept in g_messageBoxArgs while
   formatting); MessageBox's answer */
int (sys_messageBox)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
#ifdef AXIS_64   /* (a 64-bit va_list is no address: none kept) */
	vsprintf(g_messageBoxText, format, args);
#else
	g_messageBoxArgs = args;
	vsprintf(g_messageBoxText, format, args);
	ASET(g_messageBoxArgs, NULL);
#endif
	int answer = MessageBoxA(GetActiveWindow(), g_messageBoxText, AP(const char, STR(0x4b043c, "User Message ^_^;")), 0);
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
	return RegisterClassExA(wc) & 0xffff;   /* RegisterClassExA */
}

/* 0x468450: the GL window resized to width x height (g_glWidth, g_glHeight): the viewport set and, in full screen
   (g_glFullScreen), the display mode changed to match (glWindow_setDisplayModeBy; failing that, a message and 0). The cached state
   g_matchProjMode is reset; returns 1 */
int (glWindow_resize)(int width, int height)
{
	g_glWidth = width;
	g_glHeight = height;
	glViewport(0, 0, width, height);   /* glViewport */
	if (g_glFullScreen == 1 &&
	    !glWindow_setDisplayModeBy(g_glWidth, g_glHeight, 0)) {
		sys_errorMessageNoName(AP(const char, STR(0x4c500c, "glWindow screen resolution change fai...")));   /* sys_errorMessageNoName */
		return 0;
	}
	g_matchProjMode = -1;
	return 1;
}


/* 0x468250: the game's GL window made, once (a second call: a message and NULL), with title, width x height and
   colour / depth bits (g_glWidth, g_glHeight, g_glColourBits, g_glDepthBits) kept. Without a given window (window and
   dc NULL): its class registered (glWindow_wndProc, the icon named as the title, arrow cursor), the display mode
   switched in full screen (failing that, a message and windowed), a pop-up window of that size made, shown and
   focused; otherwise the given window and its DC (g_glWindowDc) taken and resized. Then the GL state (gfx_resetState);
   returns the window */
void *(glWindow_init)(const char *title, int width, int height, int colourBits, int depthBits, int fullscreen,
                      void *window, void *dc)
{
	if (g_glWindowMade == 1) {
		sys_errorMessageNoName(AP(const char, STR(0x4c4fd8, "glWindow duplicate initialization - g...")));   /* sys_errorMessageNoName */
		return NULL;
	}
	strcpy(g_glTitle, title);
	g_glColourBits = colourBits;
	g_glDepthBits = depthBits;
	g_glFullScreen = fullscreen;
	g_glWidth = width;
	g_glHeight = height;
	if (window == NULL && dc == NULL) {
		u32 wc[10];   /* WNDCLASSA */
		wc[0] = 0;                 /* style */
		wc[1] = FN(glWindow_wndProc);
		wc[2] = 0;
		wc[3] = 0;
		wc[4] = AV(GetModuleHandleA(NULL));
		wc[5] = AV(LoadIconA(GetModuleHandleA(NULL), g_glTitle));   /* LoadIconA */
		wc[6] = AV(LoadCursorA(NULL, 0x7f00));                               /* LoadCursorA(IDC_ARROW) */
		wc[7] = 6;                 /* COLOR_WINDOW + 1 */
		wc[8] = AV(g_glTitle);    /* menu name */
		wc[9] = AV(g_glTitle);    /* class name */
		if (!(RegisterClassA(wc))) {                                               /* RegisterClassA */
			sys_errorMessageNoName(AP(const char, STR(0x4c4fa4, "glWindow RegisterClass() failed - glW...")));
			return NULL;
		}
		if (g_glFullScreen == 1 &&
		    !glWindow_setDisplayModeBy(g_glWidth, g_glHeight, g_glColourBits)) {
			sys_errorMessageNoName(AP(const char, STR(0x4c4f50, "glWindow full screen mode failed, win...")));   /* glWindow_setDisplayModeBy failed */
			g_glFullScreen = 0;
		}
		g_glWindow = AREF(IMPORT_FN(CreateWindowExA, void *, u32, const char *, const char *, u32, int, int, int, int, void *, void *, void *, void *)(
			0, g_glTitle, g_glTitle, 0x86000000, 0, 0, g_glWidth, g_glHeight, NULL, NULL,
			GetModuleHandleA(NULL), NULL));                                                             /* CreateWindowExA: WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN */
		if (g_glWindow == 0) {
			sys_errorMessageNoName(AP(const char, STR(0x4c4f14, "glWindow window handle initializing f...")));
			return NULL;
		}
		ShowWindow(AP(void, g_glWindow), 10);   /* ShowWindow(SW_SHOWDEFAULT) */
		UpdateWindow(AP(void, g_glWindow));            /* UpdateWindow */
		SetFocus(AP(void, g_glWindow));         /* SetFocus */
		g_glWindowMade = 1;
	} else {
		g_glWindow = AREF(window);
		g_glWindowDc = AREF(dc);   /* the GL window's DC (g_glWindowDc below) */
		glWindow_resize(width, height);
	}
	gfx_resetState();   /* gfx_resetState */
	g_matchProjMode = -1;
	return AP(void, g_glWindow);
}

#define GetDeviceCaps(dc, index) IMPORT_FN(GetDeviceCaps, int, void *, int)(dc, index)
#define g_glDc g_glWindowDc

/* a DEVMODEA asking for width x height (and bits). (The original fills only these fields and leaves the
   rest as the stack had it; here it is zeroed.) */
static void display_mode(DevModeA *mode, int width, int height, int bits, u32 fields)
{
	memset(mode, 0, sizeof *mode);
	mode->dmSize = sizeof *mode;
	mode->dmFields = fields;   /* (0x1c0000: DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT) */
	mode->dmBitsPerPel = bits;
	mode->dmPelsWidth = width;
	mode->dmPelsHeight = height;
}

/* 0x468050: the desktop's mode put back after a switch (failing that, a message and 0); 1 */
int (glWindow_restoreDisplayMode)(void)
{
	if (g_modeChanged != 1)
		return 1;
	DevModeA mode;
	display_mode(&mode, g_desktopW, g_desktopH, g_desktopBits, 0x1c0000);
	if (ChangeDisplaySettingsA(&mode, 0)) {
		sys_errorMessageNoName(AP(const char, STR(0x4c4ed4, "glWindow ChangeDisplaySettings() fail...")));   /* sys_errorMessageNoName */
		return 0;
	}
	g_modeChanged = 0;
	return 1;
}

/* 0x467f20: the display switched to width x height (bits: any when 0): the window's DC taken when there is none,
   the desktop's mode kept before the first switch; 1 when the screen is already in that mode or the switch worked
   (then g_modeChanged is set), else a message and 0 */
int (glWindow_setDisplayModeBy)(int width, int height, int bits)
{
	void *dc = AP(void, g_glDc);
	if (!dc)
		dc = AP(void, g_glDc = AREF(GetDC(GetActiveWindow())));   /* GetDC */
	if (!g_modeChanged) {
		g_desktopW = GetDeviceCaps(dc, 8);       /* HORZRES */
		g_desktopH = GetDeviceCaps(AP(void, g_glDc), 10);  /* VERTRES */
		g_desktopBits = GetDeviceCaps(AP(void, g_glDc), 12);   /* BITSPIXEL */
		dc = AP(void, g_glDc);
	}
	if (GetDeviceCaps(dc, 8) == width && GetDeviceCaps(AP(void, g_glDc), 10) == height &&
	    (!bits || GetDeviceCaps(AP(void, g_glDc), 12) == bits))
		return 1;
	DevModeA mode;
	display_mode(&mode, width, height, bits, bits ? 0x1c0000 : 0x180000);
	if (ChangeDisplaySettingsA(&mode, 0)) {
		sys_errorMessageNoName(AP(const char, STR(0x4c4e94, "glWindow ChangeDisplaySettings() fail...")));
		return 0;
	}
	g_modeChanged = 1;
	return 1;
}

/* 0x42eed0 (the display mode set; with the exe patch's cave at 0x4a8e54 done here): the desktop's own size
   (g_desktopWidth x g_desktopHeight) is not switched to: a mode changed before (flag g_displayModeChanged) is left by
   ChangeDisplaySettingsA(NULL), else nothing (0). Any other size is remembered (g_otherModeWidth / g_otherModeHeight, the flag set)
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
	DevModeA mode;
	display_mode(&mode, width, height, 32, 0x1c0000);
	mode.dmColor = 0x800;   /* (as the original leaves it) */
	return ChangeDisplaySettingsA(&mode, flags);
}

/* 0x4314e0: the game shut down: the object at g_scene deleted (it stays set), the screen restored (app_setDisplayMode with
   the desktop's size), the arrow cursor back, input_releaseAll, the music stopped, the ten sounds at g_menuSoundBuffers released,
   the sound table released (sound_freeAll) and DirectSound ended (sound_releaseDirectSound, whose eax it returns) */
u32 (app_shutdown)(void)
{
	void *object = AGET(void, g_scene);
	if (object)
		GAME_THISCALL(*AP(u32, *(u32 *)object), void, void *, int)(object, 1);   /* scalar deleting destructor */
	app_setDisplayMode(g_desktopWidth, g_desktopHeight, 0, g_desktopDepth);
	SetCursor(LoadCursorA(NULL, 0x7f00));   /* SetCursor(LoadCursorA(IDC_ARROW)) */
	input_releaseAll();
	music_stop();
	for (u32 p = OBJ(g_menuSoundBuffers); p < OBJ(g_menuSoundBuffers) + 10 * 4; p += 4)
		mem_free(AP(void, GAME_VAR(APTR(void), p)));
	sound_freeAll();
	return sound_releaseDirectSound();
}

/* Windows' PIXELFORMATDESCRIPTOR */
typedef struct {
	u16 size, version;
	u32 flags;                  /* 0x21: PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL; 0x80 PFD_NEED_PALETTE */
	u8 pixelType, colorBits;
	u8 colorAndAccum[13];       /* cRedBits .. cAccumAlphaBits */
	u8 depthBits, stencilBits, auxBuffers, layerType, reserved;
	u32 layerMask, visibleMask, damageMask;
} PixelFormat;
_Static_assert(sizeof(PixelFormat) == 0x28, "PixelFormat");
#define ChoosePixelFormat(dc, pfd) IMPORT_FN(ChoosePixelFormat, int, void *, const void *)(dc, pfd)
#define SetPixelFormat(dc, format, pfd) IMPORT_FN(SetPixelFormat, int, void *, int, const void *)(dc, format, pfd)

/* 0x467e60: the GL window's pixel format chosen and set: double-buffered (flags 0x21) RGBA with g_glColourBits colour and
   g_glDepthBits depth bits. A message and 0 when there is none, it needs a palette, or it cannot be set; 1 when set.
   (The original fills only these fields and leaves the rest of the descriptor as the stack had it; here it is
   zeroed.) */
int (glWindow_setupPixelFormat)(void *dc)
{
	PixelFormat pfd_, *pfd = &pfd_;
	memset(pfd, 0, sizeof *pfd);
	pfd->size = sizeof *pfd;
	pfd->version = 1;
	pfd->flags = 0x21;   /* PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL */
	pfd->colorBits = (*(u8 *)&g_glColourBits);
	pfd->depthBits = (*(u8 *)&g_glDepthBits);
	int format = ChoosePixelFormat(dc, pfd);
	if (!format) {
		sys_errorMessageNoName(AP(const char, STR(0x4c4e5c, "glWindow ChoosePixelFormat failed - s...")));   /* sys_errorMessageNoName */
		return 0;
	}
	if (pfd->flags & 0x80) {   /* PFD_NEED_PALETTE */
		sys_errorMessageNoName(AP(const char, STR(0x4c4e30, "glWindow needs palette - setupPixelFo...")));
		return 0;
	}
	if (!SetPixelFormat(dc, format, pfd)) {
		sys_errorMessageNoName(AP(const char, STR(0x4c4df8, "glWindow SetPixelFormat() failed - se...")));
		return 0;
	}
	return 1;
}

/* 0x42f000: the window's pixel format from the game's descriptor (0x4b1020), filled in the first time (flag bit 1 of
   g_pixelFormatFilled): (video depth g_videoDepth + 1) * 16 colour bits, 16 depth bits, the rest zero. 1 when set; 0 when there
   is none, it needs a palette, or it cannot be set */
int (gfx_setPixelFormat)(void *dc)
{
	PixelFormat *pfd = AP(PixelFormat, STR(0x4b1020, "("));
	if (!(g_pixelFormatFilled & 1)) {
		g_pixelFormatFilled |= 1;
		pfd->colorBits = (u8)(((*(u8 *)&g_videoDepth) + 1) << 4);
		memset(pfd->colorAndAccum, 0, sizeof pfd->colorAndAccum);
		pfd->depthBits = 0x10;
		memset((u8 *)pfd + offsetof(PixelFormat, stencilBits), 0, sizeof *pfd - offsetof(PixelFormat, stencilBits));
	}
	int format = ChoosePixelFormat(dc, pfd);
	if (!format || (pfd->flags & 0x80))
		return 0;
	return SetPixelFormat(dc, format, pfd) != 0;
}

#define SendMessageA(hwnd, msg, w, l) IMPORT_FN(SendMessageA, int, void *, u32, u32, u32)(hwnd, msg, w, l)

/* 0x43f460: the hidden EDIT control that every text field types into (names, passwords, numbers,
   addresses, the e-mail, chat), `chars` letters wide (g_editFieldLength): a 12-pixel Fixedsys font (0x4b29b0,
   g_inputFont) and an edit control (g_hEditField, id 0xca, style 0x40000400, not visible) on the main window at the
   field's caret (g_inputLineX - 5, g_inputLineY + 0x21), subclassed by editField_editProc (the old procedure in
   g_editOldProc), focused, holding the typed line (g_inputLine) with the caret at its end. Returns the last
   SendMessageA's eax (EM_SETSEL) */
int (editField_createEdit)(int chars)
{
	struct { int height, width, escapement, orientation, weight; u8 italic, underline, strikeOut, charSet, outPrecision,
	         clipPrecision, quality, pitchAndFamily; char face[32]; } font;   /* LOGFONTA */
	memset(&font, 0, sizeof font);
	font.height = -12;
	font.charSet = 1;   /* DEFAULT_CHARSET */
	strcpy(font.face, AP(const char, STR(0x4b29b0, "Fixedsys")));
	g_editFieldLength = chars;
	g_inputFont = AREF(CreateFontIndirectA(&font));   /* CreateFontIndirectA */
	void *edit = IMPORT_FN(CreateWindowExA, void *, u32, const char *, const char *, u32, int, int, int, int, void *, u32, void *, void *)(
		0, AP(const char, STR(0x4b29a8, "EDIT")), NULL, 0x40000400, g_inputLineX - 5, g_inputLineY + 0x21,
		chars * 8, 0x18, AP(void, g_mainWindow), 0xca, AP(void, g_hInstance), NULL);   /* CreateWindowExA("EDIT") */
	g_hEditField = AREF(edit);
	if (edit) {
		SendMessageA(edit, 0x30, (*(u32 *)&g_inputFont), 0);   /* WM_SETFONT */
		edit = AP(void, g_hEditField);
	}
	g_editOldProc = SetWindowLongA(edit, -4, FN(editField_editProc));   /* SetWindowLongA(GWL_WNDPROC) */
	SetFocus(AP(void, g_hEditField));   /* SetFocus */
	u32 length = strlen(g_inputLine);
	SendMessageA(AP(void, g_hEditField), 0xc, 0, OBJ(g_inputLine));   /* WM_SETTEXT */
	return SendMessageA(AP(void, g_hEditField), 0xb1, length, length);   /* EM_SETSEL */
}

/* ---- the start-up ---- */
#define GetSystemMetrics(index) IMPORT_FN(GetSystemMetrics, int, int)(index)
#define GetVersion() IMPORT_FN(GetVersion, u32, void)()

/* the files the game checks for (each failing: "Run AxisPlay.exe" and 0) */
static int files_present(void)
{
	if (!app_checkFile_profeng() || !app_checkFile_profkor() || !app_checkFile_skirmish() ||
	    !app_checkFile_axisgame() || !app_checkFile_game()) {
		sys_messageBox(AP(const char, STR(0x4b04b0, "Run AxisPlay.exe")));
		return 0;
	}
	return 1;
}

/* 0x43fcc0: the game started (inst, show): outside the lobby (g_launchedForNetGame) the files checked; a 640 x 480 default; the
   directory, data paths and messages; the process made DPI aware when user32 has SetProcessDPIAware (the exe
   patch's cave at 0x4a8e20); the desktop's size, DC and depth (g_desktopWidth, g_desktopHeight, g_windowDC, g_desktopDepth); the
   default keys and axis.cfg, app_screenSizeForMode, the display mode set (32 bits) and its answer reported (app_reportDisplayModeError); the
   files checked again. The window class "AXIS" (WndProc game_wndProc; app_registerWindowClassEx where GetVersion says
   so, else RegisterClassA; kept at g_windowClass), the window at (0, -1), the screen's size with one more row (the
   patch's cave at 0x4a8f50), three timers, shown. Then the CD and the data (failing: the desktop's mode back, 0);
   screen 100, the cursor hidden, the clock check. Returns 1, or 0 on any failure */
int (app_init)(void *inst, int show)
{
	if (!g_launchedForNetGame && !files_present())
		return 0;
	g_screenW = 640;
	g_screenH = 480;
	app_readCurrentDirectory();
	app_setDataPaths();
	data_loadMessages();
	void *user32 = GetModuleHandleA(AP(const char, STR(0x4ac820, "user32.dll")));
	if (user32) {
		void (STDCALL *dpi_aware)(void) = GetProcAddress(user32, AP(const char, STR(0x4ac82c, "SetProcessDPIAware")));   /* GetProcAddress */
		if (dpi_aware)
			dpi_aware();
	}
	g_unusedInitWord = 0;
	g_desktopWidth = GetSystemMetrics(0);   /* SM_CXSCREEN */
	g_desktopHeight = GetSystemMetrics(1);
	void *dc = GetDC(NULL);   /* GetDC */
	g_windowDC = AREF(dc);
	g_desktopDepth = GetDeviceCaps(dc, 12);   /* BITSPIXEL */
	input_initDikCodes();
	cfg_init();
	app_screenSizeForMode();
	app_reportDisplayModeError(app_setDisplayMode(g_screenW, g_screenH, 4, (g_videoDepth + 1) * 16));   /* CDS_FULLSCREEN */
	if (!g_launchedForNetGame && !files_present())
		return 0;

	struct { u32 style; u32 proc; int cls_extra, wnd_extra; APTR(void) inst; APTR(void) icon; APTR(void) cursor; APTR(void) brush;
	         APTR(const char) menu; APTR(const char) name; } wc;
	wc.style = 0;
	wc.proc = FN(game_wndProc);   /* WndProc */
	wc.cls_extra = wc.wnd_extra = 0;
	wc.inst = AREF(inst);
	wc.icon = AREF(LoadIconA(inst, NULL));   /* LoadIconA */
	wc.cursor = AREF(LoadCursorA(NULL, 0x7f00));   /* LoadCursorA(IDC_ARROW) */
	wc.brush = AREF(GetStockObject(4));   /* GetStockObject(BLACK_BRUSH) */
	wc.menu = wc.name = AREF(AP(const char, STR(0x4b0714, "AXIS")));
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
	} else if (!(u16)IMPORT_FN(RegisterClassA, u32, void *)(&wc))   /* RegisterClassA */
		return 0;

	memcpy(AP(void, OBJ(g_windowClass)), &wc, sizeof wc);
	g_mainWindow = AREF(IMPORT_FN(CreateWindowExA, void *, u32, const char *, const char *, u32, int, int, int, int, void *, void *, void *, void *)
		(0, AP(const char, STR(0x4b0714, "AXIS")), AP(const char, STR(0x4b2874, "AXIS")), 0x86000000, 0, -1, g_screenW, g_screenH + 1, NULL, NULL, inst, NULL));   /* CreateWindowExA: WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN */
	if (!g_mainWindow)
		return 0;
	g_hInstance = AREF(inst);
	g_showCmd = show;
	static const u32 timers[3][2] = { { 0x29a, 60000 }, { 0x115c, 30000 }, { 0x309, 60000 } };
	for (int k = 0; k < 3; k++)
		SetTimer(AP(void, g_mainWindow), timers[k][0], timers[k][1], NULL);   /* SetTimer */
	ShowWindow(AP(void, g_mainWindow), show);   /* ShowWindow */
	UpdateWindow(AP(void, g_mainWindow));   /* UpdateWindow */
	if (!app_startupLoad(inst)) {
		app_setDisplayMode(g_desktopWidth, g_desktopHeight, 0, g_desktopDepth);
		return 0;
	}
	g_menuState = 100;
	ShowCursor(0);   /* ShowCursor */
	g_clockCheckQuits = 1;
	sys_checkClockTampering();
	return 1;
}
#undef GetSystemMetrics
#undef GetVersion

/* 0x4680d0: the GL window's messages. Created: the cursor hidden, its DC (g_glWindowDc) given a pixel format (failing, the
   game quits) and a GL context (g_glWindowContext) made current. Painted: begun and ended. Resized: the view resized. Closed:
   destroyed. Destroyed: the context and DC let go, the display mode restored, the cursor shown, the game quits. The
   rest go to DefWindowProcA */
long STDCALL (glWindow_wndProc)(void *wnd, u32 msg, u32 w, u32 l)
{
#define g_dc g_glWindowDc
#undef PostQuitMessage
#define PostQuitMessage(code) IMPORT_FN(PostQuitMessage, void, int)(code)
	u32 rect[4], paint[0x10];
	switch (msg) {
	case 1:   /* WM_CREATE */
		ShowCursor(0);
		g_dc = AREF(GetDC(wnd));   /* GetDC */
		if (!glWindow_setupPixelFormat(AP(void, g_dc)))
			PostQuitMessage(0);
		g_glWindowContext = AREF(wglCreateContext(AP(void, g_dc)));   /* wglCreateContext */
		wglMakeCurrent(AP(void, g_dc), AP(void, g_glWindowContext));   /* wglMakeCurrent */
		IMPORT_FN(GetClientRect, int, void *, u32 *)(wnd, rect);   /* GetClientRect */
		return 0;
	case 0xf:   /* WM_PAINT */
		BeginPaint(wnd, paint);   /* BeginPaint */
		EndPaint(wnd, paint);   /* EndPaint */
		return 0;
	case 0x10:   /* WM_CLOSE */
		DestroyWindow(wnd);   /* DestroyWindow */
		return 0;
	case 5:   /* WM_SIZE */
		glWindow_resize(l & 0xffff, l >> 16);
		return 0;
	case 2:   /* WM_DESTROY */
		if (g_glWindowContext)
			wglDeleteContext(AP(void, g_glWindowContext));   /* wglDeleteContext */
		if (g_dc)
			ReleaseDC(wnd, AP(void, g_dc));   /* ReleaseDC */
		g_glWindowContext = 0;
		g_dc = 0;
		glWindow_restoreDisplayMode();
		ShowCursor(1);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProcA(wnd, msg, w, l);   /* DefWindowProcA */
#undef g_dc
#undef g_glWindowContext
#undef PostQuitMessage
}

#define CallWindowProcA(proc, wnd, msg, w, l) IMPORT_FN(CallWindowProcA, long, u32, u32, u32, u32, u32)(proc, wnd, msg, w, l)

/* the text field's line closed by a key: its text kept (Enter) or dropped, the edit destroyed, the main window focused again
   and the line closed (menu_closeInputLine, sent or not) */
static void edit_close(void *edit, int sent)
{
	if (sent)
		SendMessageA(edit, 0xd, 0x80, OBJ(g_inputLine));   /* WM_GETTEXT */
	SendMessageA(edit, 0xc, 0, 0);                 /* WM_SETTEXT "" */
	DestroyWindow(AP(void, g_hEditField));   /* DestroyWindow */
	SetFocus(AP(void, g_mainWindow));   /* SetFocus */
	menu_closeInputLine(sent);   /* menu_closeInputLine */
	g_editLineDone = 1;
}

/* 0x440840: the text fields' hidden edit's window procedure (set by editField_createEdit). Keys: Enter, once the open delay (g_menuKeyGuard)
   is not over k_0f, takes the line and sends it (g_fieldStep 20: the next field); Esc drops it; Tab in the room
   (g_screen 0x320) closes it (sent) and steps by Shift (g_fieldStep 10 back when held, else 20); Home and Left are swallowed (0).
   Timers: 0x29a, in the lobby (g_hostingState 2), and 0x115c, when connected (g_roomConnected), send their keep-alives (0x17 to
   the lobby, 0x18 to the game server). Everything not swallowed goes on to the edit's own procedure (g_editOldProc) */
long STDCALL (editField_editProc)(void *wnd, u32 msg, u32 w, u32 l)
{
	if (msg == 0x100) {   /* WM_KEYDOWN */
		switch (w) {
		case 0xd:   /* Enter */
			if (!(g_menuKeyGuard > k_0f)) {
				edit_close(wnd, 1);
				g_fieldStep = 0x14;
			}
			break;
		case 0x1b:   /* Esc */
			edit_close(wnd, 0);
			break;
		case 9:   /* Tab */
			if (g_menuState == 0x320) {
				DestroyWindow(AP(void, g_hEditField));   /* DestroyWindow */
				SetFocus(AP(void, g_mainWindow));   /* SetFocus */
				menu_closeInputLine(1);   /* menu_closeInputLine */
				g_fieldStep = 0x14;
				g_editLineDone = 1;
				g_fieldStep = GetKeyState(0x10) < 0 ? 10 : 20;   /* GetKeyState(VK_SHIFT) */
			}
			break;
		case 0x24: case 0x25:   /* Home, Left */
			return 0;
		}
	} else if (msg == 0x113) {   /* WM_TIMER */
		if (w == 0x29a) {
			if (g_hostingState == 2)
				net_send(0x17, 100);
		} else if (w == 0x115c && g_roomConnected)
			net_send(0x18, 0x65);
	}
	return CallWindowProcA(g_editOldProc, AV(wnd), msg, w, l);
}

/* 0x43f9d0: the program. The launch file read (app_parseCommandLine); a running launcher (window class 0x4b2834)
   told to quit, then half a second; the start time (GetSystemTime into g_clockLastTime, timeGetTime g_startTicks) and two
   seconds. A game already running (an "AXIS" window), or no CD (cd_findDrive), ends it with a message box. The
   language by the system's (Korean 0x412 / 0x812: 1 and the message 0x4b2794, else 2 and 0x4b27e4, at g_language /
   g_launchMessage); the clock check; outside the lobby (g_launchedForNetGame) the launcher, start mode and file checks, each failing
   with its message. The launcher told to quit again, app_init (failing: a message box), the screen saver off, then
   the message loop (TranslateMessage while g_textFieldOpen) with the typed text read (editField_readTyping) and a frame (app_frame)
   after each round of messages, until g_gameRunning is cleared. Returns 1, or 0 on the exits. (Named game_WinMain: WinMain is the
   SDK's) */
#ifdef AXIS_PORTABLE
/* (the portable build: this is axis_init, the start-up only - the host runs the frames, see the end of this file
   and src/axis_api.h) */
#include "../axis_api.h"
#define game_WinMain axis_init
#endif
u32 STDCALL (game_WinMain)(void *inst, void *prev, const char *cmd, int show)
{
#define FindWindowA(cls, name) IMPORT_FN(FindWindowA, void *, const char *, const char *)(cls, name)
	app_parseCommandLine(cmd);
	void *launcher = FindWindowA(AP(const char, STR(0x4b2834, "#32770")), AP(const char, STR(0x4b2854, "\364\270\315\366\361\375\340\362\312\245\341\334\320\357")));
	if (launcher) {
		PostMessageA(launcher, 0x12, 0, 0);   /* WM_QUIT */
		TIME_SLEEP(500);
	}
	TIME_UTC(AP(void, OBJ(g_clockLastTime)));              /* GetSystemTime */
	g_startTicks = TIME_MS();       /* timeGetTime */
	TIME_SLEEP(2000);
	if (FindWindowA(AP(const char, STR(0x4b0714, "AXIS")), NULL)) {
		MessageBoxA(NULL, AP(const char, STR(0x4b2a00, "This application is already run!!")), AP(const char, STR(0x4b2554, "Warning")), 0);
		return 0;
	}
	if (!cd_findDrive()) {
		MessageBoxA(NULL, AP(const char, STR(0x4b2528, "Please insert Axis CD in your CD-ROM ...")), AP(const char, STR(0x4b2554, "Warning")), 0);
		return 0;
	}
	u16 language = GetSystemDefaultLangID();   /* GetSystemDefaultLangID */
	g_languageId = language;
	if (language == 0x412 || language == 0x812) {
		g_language = 1;
		(*(u32 *)&g_launchMessage) = STR(0x4b2794, "Axisplay.exe \310\255\300\317\300\314 \300\337\270\370\265\307\276\372\275\300\264\317\264\331");
	} else {
		g_language = 2;
		(*(u32 *)&g_launchMessage) = STR(0x4b27e4, "Axisplay.exe has been expired");
	}
	sys_checkClockTampering();
	if (!g_launchedForNetGame) {
		if (!app_readLauncherCheck()) {
			sys_messageBox(AP(const char, g_launchMessage));
			return 0;
		}
		if (!reg_readStartMode()) {
			sys_messageBox(AP(const char, STR(0x4b04b0, "Run AxisPlay.exe")));
			return 0;
		}
		if (!files_present())
			return 0;
	}
	launcher = FindWindowA(AP(const char, STR(0x4b2834, "#32770")), AP(const char, STR(0x4b2854, "\364\270\315\366\361\375\340\362\312\245\341\334\320\357")));
	if (launcher)
		PostMessageA(launcher, 0x12, 0, 0);
	if (!app_init(inst, show)) {
		MessageBoxA(AP(void, g_mainWindow), AP(const char, STR(0x4b29ec, "Windows Init Faild")), AP(const char, STR(0x4b141c, "ERROR")), 0);
		return 0;
	}
	g_gameRunning = 1;
	SystemParametersInfoA(0x61, 1, NULL, 0);   /* SystemParametersInfoA(SPI_SETSCREENSAVERRUNNING) */
#ifdef AXIS_PORTABLE
	return 1;   /* (the host's loop: axis_running / axis_frame) */
#else
	u32 msg[7];   /* MSG */
	while (g_gameRunning) {
		while (PeekMessageA(msg, NULL, 0, 0, 0) == 1)   /* PeekMessageA */
			if (GetMessageA(msg, NULL, 0, 0)) {   /* GetMessageA */
				if (g_textFieldOpen)
					TranslateMessage(msg);   /* TranslateMessage */
				DispatchMessageA(msg);       /* DispatchMessageA */
			}
		editField_readTyping();
		app_frame();
	}
	return 1;
#endif
#undef FindWindowA
}
#undef game_WinMain

/* 0x440070: the game window's messages (its class's procedure; the patch DLL subclasses it, see axisnet's input_read).
   Returns 1 for the messages it takes (0 where noted), DefWindowProcA's answer for the rest.
   - WM_CREATE: the window's DC (g_windowDC) given a pixel format (failing: the game quits) and a GL context
     (g_glContext); the GL state for the client size; the pointer at the menus' centre.
   - WM_SIZE: the 3D view for the client size (gfx_setup3DView).
     As the installed exe has both (widefix.py: wrappers at 0x4a8f6a / 0x4a8f87, called from 0x440116 / 0x440186):
     the client is one pixel taller than the game's height (the window starts at y -1, so the driver keeps it
     composited), so that height is taken back to the game's, and the menus' projection switch sets its viewport
     again next time (g_projMode -1).
   - WM_PAINT: begun and ended. WM_CLOSE: the DC let go, the arena session left, the network closed, the three
     network timers stopped, the cursor put back, the window destroyed.
   - WM_DESTROY: the screen saver back on, the DC and the text fields' EDIT control (g_hEditField) let go, the cursor shown, the game quits; then,
     by the exit mode (g_exitCode): 0 the start mode 0 and the launcher's marks invalidated (app_invalidateLauncherMarks; and g_gameRunning cleared), 1 the start
     mode 1 and AxisGL.exe started again, 2 / 3 the start mode 0, the marks invalidated and axispatch.exe ("nstower") /
     DServer.exe started, 99 the marks invalidated and the ending movie; the process ends.
   - WM_ACTIVATEAPP: the activation kept (g_unusedActive). As the installed exe has it (cursorfix.py, through 0x44037c ->
     0x4a8ec1): the Windows cursor hidden while active and shown while not (counted down / up until it is), and the
     window restored when the game comes back (borderless); then (widefix.py's handler at 0x4a8ecb) a display mode
     the game had set (g_displayModeChanged) is given up while it is in the background (the window minimised) and set again
     (g_otherModeWidth x g_otherModeHeight) when it comes back.
   - WM_SYSCOMMAND: moving, sizing, maximising, the screen saver, closing, the task list, the keyboard menu and
     minimising are swallowed (0); SC_RESTORE goes to DefWindowProcA (cursorfix.py changed 0x44050c: the game
     swallowed it), though as the command 0xf120 itself, not as WM_SYSCOMMAND; anything else 1.
   - WM_TIMER: 0x29a in the arena's lobby a keep-alive (net_send 0x17), 0x115c in a room another (0x18); 0x378 the
     arena's session search: the sessions listed; after 30 tries the join gives up, else a session found ends it
     (none: try again next time); either way the timer stops and the room closes (room_joinAnswer) or the arena's join
     is answered (arena_joinAnswer).
   - 0x40a, 0x40c (the lobby's and the game server's sockets): closed, both sockets closed and the menus back at
     the main menu (0), unless in a match; else the reply read and the connection's step and search result
     taken from it. */
long STDCALL (game_wndProc)(void *wnd, u32 msg, u32 w, u32 l)
{
#define g_exitMode g_exitCode
#undef PostQuitMessage
#define PostQuitMessage(code) IMPORT_FN(PostQuitMessage, void, int)(code)
#undef GetClientRect
#define GetClientRect(wnd, rect) IMPORT_FN(GetClientRect, int, void *, int *)(wnd, rect)
#ifdef AXIS_PORTABLE
/* (the portable build: quitting hands back to the host - the frames stop, axis_exit gives the host the code; each
   ExitProcess here is followed by the procedure's return, which now runs. See the end of this file) */
void axis_ended(u32 code);
#define ExitProcess(code) axis_ended(code)
#else
#define ExitProcess(code) IMPORT_FN(ExitProcess, void, u32)(code)
#endif
#undef ShellExecuteA
#define ShellExecuteA(wnd, verb, file, args, dir, show) \
	IMPORT_FN(ShellExecuteA, void *, void *, const char *, const char *, const char *, const char *, int)(wnd, verb, file, args, dir, show)
#define GAME_HEIGHT(h) ((h) - 1 == g_screenH ? (h) - 1 : (h))   /* widefix.py: the client's extra row taken back */
	u16 now[8];
	int rect[4];
	u32 paint[0x10];
	TIME_LOCAL(now);   /* GetLocalTime (unused) */
	switch (msg) {
	case 1:   /* WM_CREATE */
		g_windowDC = AREF(GetDC(wnd));   /* GetDC */
		if (!gfx_setPixelFormat(AP(void, g_windowDC))) {   /* gfx_setPixelFormat */
			PostQuitMessage(0);
			return 1;
		}
		g_glContext = AREF(wglCreateContext(AP(void, g_windowDC)));   /* wglCreateContext */
		wglMakeCurrent(AP(void, g_windowDC), AP(void, g_glContext));   /* wglMakeCurrent */
		GetClientRect(wnd, rect);
		g_projMode = -1;
		gfx_initGLState(rect[2], GAME_HEIGHT(rect[3]));   /* gfx_initGLState */
		g_mouseX = 0x140;
		g_mouseY = 0xf0;
		g_mouseWheelTurned = 0;
		return 1;
	case 0xf:   /* WM_PAINT */
		BeginPaint(wnd, paint);   /* BeginPaint */
		EndPaint(wnd, paint);   /* EndPaint */
		return 1;
	case 5:   /* WM_SIZE */
		GetClientRect(wnd, rect);
		g_projMode = -1;
		gfx_setup3DView(rect[2], GAME_HEIGHT(rect[3]));   /* gfx_setup3DView */
		return 1;
	case 0x10:   /* WM_CLOSE */
		if (g_windowDC)
			ReleaseDC(wnd, AP(void, g_windowDC));
		g_glContext = AREF(NULL);
		g_windowDC = AREF(NULL);
		g_lobbyReportsOff = 1;
		dplay_leaveSession();
		net_disconnect();
		KillTimer(AP(void, g_mainWindow), 0x29a);
		KillTimer(AP(void, g_mainWindow), 0x115c);
		KillTimer(AP(void, g_mainWindow), 0x309);
		g_lobbyReportsOff = 1;
		app_shutdown();   /* app_shutdown */
		DestroyWindow(wnd);
		return 1;
	case 2:   /* WM_DESTROY */
		SystemParametersInfoA(0x61, 0, NULL, 0);   /* SystemParametersInfoA: SPI_SETSCREENSAVERRUNNING off */
		if (g_windowDC)
			ReleaseDC(wnd, AP(void, g_windowDC));
		if (g_hEditField)
			DestroyWindow(AP(void, g_hEditField));
		ShowCursor(1);
		PostQuitMessage(0);
		switch (g_exitMode) {
		case 0:
			reg_writeStartMode(0);   /* reg_writeStartMode */
			app_invalidateLauncherMarks();   /* app_invalidateLauncherMarks */
			g_gameRunning = 0;
			ExitProcess(0);
			return 0;
		case 1:
			reg_writeStartMode(1);
			ShellExecuteA(NULL, AP(const char, STR(0x4b2a5c, "open")), AP(const char, STR(0x4b2a64, "AxisGL.exe")), NULL, NULL, 10);
			ExitProcess(0);
			return 0;
		case 2:
			reg_writeStartMode(0);
			app_invalidateLauncherMarks();
			ShellExecuteA(NULL, AP(const char, STR(0x4b2a5c, "open")), AP(const char, STR(0x4b2a44, "axispatch.exe")), AP(const char, STR(0x4b2a54, "nstower")), NULL, 10);
			ExitProcess(0);
			return 0;
		case 3:
			reg_writeStartMode(0);
			app_invalidateLauncherMarks();
			ShellExecuteA(NULL, AP(const char, STR(0x4b2a5c, "open")), AP(const char, STR(0x4b2a38, "DServer.exe")), AP(const char, STR(0x4b13ec, "1")), NULL, 10);
			ExitProcess(0);
			return 0;
		case 99:
			app_invalidateLauncherMarks();
#ifdef AXIS_NATIVE
			platform_playMovie(NULL, AP(const char, STR(0x4b2a24, "initdata/battle.sra")), g_desktopWidth, g_desktopHeight);   /* movie_playEnding's replacement (standalone/platform.c) */
#elif defined(AXIS_DIRECT)
			if (g_wide->playEnding)   /* (AxisRC.exe: the patch layer's player, which replaces movie_playEnding) */
				g_wide->playEnding(NULL, AP(const char, STR(0x4b2a24, "initdata/battle.sra")), g_desktopWidth, g_desktopHeight);
#else
			movie_playEnding(0, AP(const char, STR(0x4b2a24, "initdata/battle.sra")), g_desktopWidth, g_desktopHeight);
#endif
			ExitProcess(0);
		}
		ExitProcess(0);
		return 0;
	case 0x1c: {   /* WM_ACTIVATEAPP */
		g_unusedActive = w;
		if (w) {
			while (ShowCursor(0) >= 0)
				;
			if (!g_displayModeChanged)
				ShowWindow(AP(void, g_mainWindow), 9);   /* SW_RESTORE */
			if (g_displayModeLeft) {
				g_displayModeLeft = 0;
				app_setDisplayMode(g_otherModeWidth, g_otherModeHeight, 4, 0x20);
				ShowWindow(AP(void, g_mainWindow), 9);
			}
		} else {
			while (ShowCursor(1) < 0)
				;
			if (g_displayModeChanged) {
				ShowWindow(AP(void, g_mainWindow), 7);   /* SW_SHOWMINNOACTIVE */
				ChangeDisplaySettingsA(NULL, 0);   /* ChangeDisplaySettingsA: the desktop's mode back */
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
			return DefWindowProcA(wnd, command, w, l);
		if (command == 0xf130 || command == 0xf040 || command == 0xf050 || command == 0xf170 || command == 0xf060 ||
		    command == 0xf030 || command == 0xf020 || command == 0xf140)
			return 0;
		return 1;
	}
	case 0x113:   /* WM_TIMER */
		if (w == 0x29a) {
			if (g_hostingState == 2)
				net_send(0x17, 100);
		} else if (w == 0x378) {
			dplay_listSessions();
			if (++g_joinPollTicks > 30) {
				g_joinTimedOut = 1;
			} else {
				g_receivedSession = AREF(AP(const u8, net_getSession(0)));
				if (!g_receivedSession)
					return 1;
				g_sessionFound = 1;
			}
			KillTimer(wnd, 0x378);
			if (g_screen == 800)
				room_joinAnswer();   /* room_joinAnswer */
			else
				arena_joinAnswer();   /* arena_joinAnswer */
		} else if (w == 0x115c) {
			if (g_roomConnected)
				net_send(0x18, 0x65);
		}
		return 1;
	case 0x40a:   /* the lobby's socket (net_asyncSelect 100: g_lobbySocket) */
		if ((u16)l == 0x20) {   /* FD_CLOSE */
			net_closeSockets();   /* net_closeSockets */
			if (g_screen != 0x270f)
				menu_returnToArenaLobbyViaMain();   /* menu_returnToArenaLobbyViaMain */
			return 0;
		}
		net_recv();   /* net_recv */
		switch (g_lobbyStatus) {
		case 0x29: g_hostAnswer = 4; break;
		case 0x66: g_hostAnswer = 1; break;
		case 0x67: g_hostAnswer = 3; break;
		default: g_hostAnswer = 0; break;
		}
		switch (g_lobbyListAnswer) {
		case 0x29: g_serverAnswerIn = 1; g_searchResult = 4; break;
		case 0xca: g_serverAnswerIn = 1; g_searchResult = 1; break;
		case 0xcb: g_serverAnswerIn = 1; g_searchResult = 3; break;
		}
		return 1;
	case 0x40c:   /* the game server's socket (net_asyncSelect 101: g_gameServerSocket) */
		if ((u16)l == 0x20) {
			net_closeSockets();
			if (g_screen != 0x270f)
				menu_returnToMainFromRoom();   /* menu_returnToMainFromRoom */
			return 0;
		}
		net_recv();
		switch (g_gameServerStatus) {
		case 0x28: g_hostAnswer = 4; break;
		case 0x66: g_hostAnswer = 1; break;
		case 0x67: g_hostAnswer = 3; break;
		default: g_hostAnswer = 0; break;
		}
		switch (g_roomListAnswer) {
		case 0x28: g_roomSearchAnswerIn = 1; g_searchResult = 4; break;
		case 0xca: g_roomSearchAnswerIn = 1; g_searchResult = 1; break;
		case 0xcb: g_roomSearchAnswerIn = 1; g_searchResult = 3; break;
		}
		if (g_playerListDone)
			g_rankingListIn = 1;
		if (g_rankReplyIn)
			g_accountRankDue = 1;
		return 1;
	}
	return DefWindowProcA(wnd, msg, w, l);   /* DefWindowProcA */
#undef g_glContext
#undef g_exitMode
#undef PostQuitMessage
#undef GetClientRect
#undef ExitProcess
#undef ShellExecuteA
#undef GAME_HEIGHT
}

#ifdef AXIS_PORTABLE
/* ---- the host's side (src/axis_api.h): the original loop's body, one round per call ---- */
unsigned axis_frame(void)
{
	if (!g_gameRunning)   /* (stopped - the window may be gone: no frame, as the original's loop ran none) */
		return 0;
	/* (the x87 control word the game's maths needs - 53-bit precision, standalone/main.c - for the frame; a host may
	   run with its own) */
#if defined(__i386__) || defined(__x86_64__)
	unsigned short was, cw = 0x027f;
	__asm__ volatile("fnstcw %0" : "=m"(was));
	__asm__ volatile("fldcw %0" : : "m"(cw));
#define CW_RESTORE() __asm__ volatile("fldcw %0" : : "m"(was))
#else   /* (no x87: arm64's doubles are the 53 bits already) */
#define CW_RESTORE() ((void)0)
#endif
	PLAT_PUMP();   /* (a host without the window: its posted messages, timers and socket events, as the loop's messages) */
	if (!g_gameRunning) {   /* (a message ended the game) */
		CW_RESTORE();
		return 0;
	}
	editField_readTyping();
	app_frame();
	CW_RESTORE();
#undef CW_RESTORE
	return g_gameRunning != 0;
}
/* a key and a typed character for the open text field (its hidden EDIT control, as Windows would send them) */
void axis_key(unsigned vk, int down)
{
	if (g_textFieldOpen && g_hEditField)
		SendMessageA(AP(void, g_hEditField), down ? 0x100 : 0x101, vk, 0);   /* WM_KEYDOWN / WM_KEYUP */
}
void axis_char(unsigned ch)
{
	if (g_textFieldOpen && g_hEditField)
		SendMessageA(AP(void, g_hEditField), 0x102, ch, 0);   /* WM_CHAR */
}
int axis_running(void) { return g_gameRunning != 0; }
/* the game quitting (its window destroyed: the original ended the process there, without its exit list) */
static int g_ended;
static u32 g_endCode;
void axis_ended(u32 code)
{
	if (!g_ended) {
		g_ended = 1;
		g_endCode = code;
	}
	g_gameRunning = 0;
}
/* 1 (and the code) once the game has quit that way (standalone/portable.c axis_exit) */
int axis_hasEnded(u32 *code)
{
	*code = g_endCode;
	return g_ended;
}
int axis_textInput(void) { return g_textFieldOpen != 0; }
void axis_shutdown(void)
{
	if (g_mainWindow)
		PostMessageA(AP(void, g_mainWindow), 0x10, 0, 0);   /* WM_CLOSE: the window's own close path */
}
#endif
