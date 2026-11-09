/* platform.c: the Windows side of the native build's fixes (AXIS_NATIVE, src/fixes/settings.h): the settings from
   axisnet.ini, and the window / mouse plumbing the game's code asks for. Ported from the patch layer
   (axisnet_recomp.c: load_config, main_subproc, bg_*, menu_speed), where it reached the game by addresses. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <mmsystem.h>
#include <digitalv.h>
#include <stdlib.h>
#include <string.h>
#include "../src/fixes/settings.h"
#include "../../axisnet/iv32/iv32.h"

Settings g_settings = { 1, 1, 16.0f / 9.0f, 1, 1.0f, 1.0f };

void platform_loadSettings(void)
{
	char ini[MAX_PATH], v[32];
	if (GetEnvironmentVariableA("AXIS_GAME_DIR", ini, MAX_PATH - 16)) {   /* (a host's game folder, axis_api.h) */
		size_t n = strlen(ini);
		if (n && ini[n - 1] != '\\') strcat(ini, "\\");
		strcat(ini, "axisnet.ini");
	} else {
		GetModuleFileNameA(NULL, ini, MAX_PATH);   /* (next to the exe) */
		char *p = strrchr(ini, '\\');
		strcpy(p ? p + 1 : ini, "axisnet.ini");
	}
	g_settings.menu43 = GetPrivateProfileIntA("hud", "menu43", 1, ini);
	g_settings.hudProportional = GetPrivateProfileIntA("hud", "proportional", 1, ini);
	g_settings.sharpText = GetPrivateProfileIntA("hud", "sharptext", 1, ini);
	GetPrivateProfileStringA("hud", "maxaspect", "1.7778", v, sizeof v, ini);
	g_settings.hudMaxAspect = (float)atof(v);
	GetPrivateProfileStringA("input", "menusens", "1", v, sizeof v, ini);
	g_settings.menuSens = (float)atof(v);
	GetPrivateProfileStringA("input", "escmenusens", "1", v, sizeof v, ini);
	g_settings.escMenuSens = (float)atof(v);
}

/* (a host supplying the input - axis_api.h axis_host - says whether its window has the focus: -1 none) */
int g_platformHostFocus = -1;
int platform_isForeground(void *window) { return g_platformHostFocus >= 0 ? g_platformHostFocus : GetForegroundWindow() == (HWND)window; }
unsigned platform_ticks(void) { return GetTickCount(); }

float platform_pointerSpeed(void)
{
	static const float speed[21] = { 0, 1 / 32.f, 1 / 16.f, 1 / 8.f, 2 / 8.f, 3 / 8.f, 4 / 8.f, 5 / 8.f, 6 / 8.f, 7 / 8.f, 1,
	                                 1.25f, 1.5f, 1.75f, 2, 2.25f, 2.5f, 2.75f, 3, 3.25f, 3.5f };
	int s = 10;
	SystemParametersInfoA(SPI_GETMOUSESPEED, 0, &s, 0);
	return speed[s >= 1 && s <= 20 ? s : 10];
}

/* ---- the mouse buttons after alt-tab. The DirectInput mouse is exclusive (it hides the buttons from Windows) and
   the game acquires it again every frame, so a button held while switching away could stay "down" for the rest of
   Windows. On deactivation the mouse is unacquired at once and a low-level hook (installed then, so that it runs
   before DirectInput's) follows the real buttons while the game is in the background; a button Windows still
   reports down after it was really released gets an up. ---- */
static BYTE g_foregroundButtons;     /* the buttons in the last foreground read */
static volatile BYTE g_realButtons;  /* the real buttons while in the background */
static volatile LONG g_background;
static DWORD g_watchThread;
static void **g_mouseDevice, **g_editField;

void platform_mouseButtons(int bits) { g_foregroundButtons = (BYTE)bits; }

static LRESULT CALLBACK real_buttons(int n, WPARAM wp, LPARAM lp)
{
	if (n == HC_ACTION)
		switch (wp) {
		case WM_LBUTTONDOWN: g_realButtons |= 1; break;
		case WM_LBUTTONUP: g_realButtons &= ~1; break;
		case WM_RBUTTONDOWN: g_realButtons |= 2; break;
		case WM_RBUTTONUP: g_realButtons &= ~2; break;
		case WM_MBUTTONDOWN: g_realButtons |= 4; break;
		case WM_MBUTTONUP: g_realButtons &= ~4; break;
		}
	return CallNextHookEx(NULL, n, wp, lp);
}

static DWORD WINAPI watch_buttons(void *ready)
{
	static const int vk[3] = { VK_LBUTTON, VK_RBUTTON, VK_MBUTTON };
	static const DWORD up[3] = { MOUSEEVENTF_LEFTUP, MOUSEEVENTF_RIGHTUP, MOUSEEVENTF_MIDDLEUP };
	HHOOK hook = NULL;
	UINT_PTR timer = 0;
	int stale[3] = { 0 };
	MSG msg;
	PeekMessageA(&msg, NULL, WM_USER, WM_USER, PM_NOREMOVE);   /* (the thread's message queue) */
	SetEvent((HANDLE)ready);
	while (GetMessageA(&msg, NULL, 0, 0) > 0) {
		if (msg.message == WM_APP) {              /* deactivated: hooked again, so that this hook runs first */
			if (hook) UnhookWindowsHookEx(hook);
			hook = SetWindowsHookExA(WH_MOUSE_LL, real_buttons, GetModuleHandleA(NULL), 0);
			if (!timer) timer = SetTimer(NULL, 0, 50, NULL);
			stale[0] = stale[1] = stale[2] = 0;
		} else if (msg.message == WM_APP + 1) {   /* activated: no hook while playing */
			if (hook) UnhookWindowsHookEx(hook);
			if (timer) KillTimer(NULL, timer);
			hook = NULL;
			timer = 0;
		} else if (msg.message == WM_TIMER && g_background) {
			for (int i = 0; i < 3; i++) {
				if ((GetAsyncKeyState(vk[i]) & 0x8000) && !(g_realButtons & (1 << i))) {
					if (++stale[i] == 2) {   /* still down 50 ms after the real release */
						INPUT in = { 0 };
						in.type = INPUT_MOUSE;
						in.mi.dwFlags = up[i];
						SendInput(1, &in, sizeof in);
					}
				} else
					stale[i] = 0;
			}
		}
		DispatchMessageA(&msg);
	}
	return 0;
}

static void activated(int active)
{
	if (g_platformHostFocus >= 0)   /* (a host supplies the input and owns the focus: no devices to let go) */
		return;
	if (!active) {
		void *dev = g_mouseDevice ? *g_mouseDevice : NULL;   /* (an IDirectInputDevice) */
		if (dev)
			((HRESULT (__stdcall *)(void *))(*(void ***)dev)[8])(dev);   /* IDirectInputDevice::Unacquire */
		g_realButtons = g_foregroundButtons;
		g_background = 1;
		if (!g_watchThread) {
			HANDLE ready = CreateEventA(NULL, FALSE, FALSE, NULL);
			CloseHandle(CreateThread(NULL, 0, watch_buttons, ready, 0, &g_watchThread));
			WaitForSingleObject(ready, 2000);
			CloseHandle(ready);
		}
		PostThreadMessageA(g_watchThread, WM_APP, 0, 0);
	} else {
		g_background = 0;
		if (g_watchThread)
			PostThreadMessageA(g_watchThread, WM_APP + 1, 0, 0);
	}
}

/* ---- the game window: activation as above; on activation or focus the text field's hidden EDIT control (g_hEditField, a
   child of the window, which exists while any text field is typed in: names, passwords, chat ..) gets the focus back - otherwise typing went nowhere after alt-tab ---- */
static HWND g_watched;
static WNDPROC g_gameProc;

static LRESULT CALLBACK game_window(HWND w, UINT m, WPARAM wp, LPARAM lp)
{
	if (m == WM_ACTIVATEAPP)
		activated(wp != 0);
	LRESULT r = CallWindowProcA(g_gameProc, w, m, wp, lp);
	if ((m == WM_ACTIVATE && LOWORD(wp) != WA_INACTIVE) || m == WM_SETFOCUS) {
		HWND edit = g_editField ? (HWND)*g_editField : NULL;
		if (edit && IsWindow(edit) && GetParent(edit) == w && GetFocus() != edit)
			SetFocus(edit);
	}
	return r;
}

void platform_watchWindow(void *window, void **editField, void **mouseDevice)
{
	HWND w = (HWND)window;
	g_editField = editField;
	g_mouseDevice = mouseDevice;
	if (!w || w == g_watched || !IsWindow(w))
		return;
	WNDPROC p = (WNDPROC)GetWindowLongA(w, GWL_WNDPROC);
	if (p != game_window) {
		g_gameProc = p;
		SetWindowLongA(w, GWL_WNDPROC, (LONG)game_window);
	}
	g_watched = w;
}

/* ---- the bound 2D texture's filters (pixel-sharp text): glTexParameteri / glGetTexParameteriv, which the game does
   not import ---- */
typedef void (WINAPI *TEXPARAMI)(unsigned, unsigned, int);
typedef void (WINAPI *GETTEXPARAMIV)(unsigned, unsigned, int *);
/* (looked up at first use unless already set: glrec.c, the drawing recorder, puts its own in front) */
TEXPARAMI g_texParameteri;
GETTEXPARAMIV g_getTexParameteriv;

int platform_texNearest(int saved[2])
{
	if (!g_texParameteri || !g_getTexParameteriv) {
		HMODULE gl = GetModuleHandleA("opengl32.dll");
		g_texParameteri = gl ? (TEXPARAMI)GetProcAddress(gl, "glTexParameteri") : NULL;
		g_getTexParameteriv = gl ? (GETTEXPARAMIV)GetProcAddress(gl, "glGetTexParameteriv") : NULL;
		if (!g_texParameteri || !g_getTexParameteriv) {
			g_texParameteri = NULL;
			return 0;
		}
	}
	g_getTexParameteriv(0x0de1, 0x2800, &saved[0]);   /* GL_TEXTURE_2D: GL_TEXTURE_MAG_FILTER */
	g_getTexParameteriv(0x0de1, 0x2801, &saved[1]);   /* GL_TEXTURE_MIN_FILTER */
	g_texParameteri(0x0de1, 0x2800, 0x2600);          /* GL_NEAREST */
	g_texParameteri(0x0de1, 0x2801, 0x2600);
	return 1;
}

void platform_texRestore(const int saved[2])
{
	g_texParameteri(0x0de1, 0x2800, saved[0]);
	g_texParameteri(0x0de1, 0x2801, saved[1]);
}

/* ---- the ending movie (after the last mission): played in a black full-screen window, centred with its aspect kept,
   Esc to skip, the window's messages handled while it plays. The game's own routine left the MCI window's style
   unset, ignored errors and busy-waited without handling messages after the game window was already gone, which
   crashed or hung the game; and the movies are Indeo 3, which Windows no longer decodes (iv32 adds a decoder). ---- */
static LRESULT CALLBACK movie_window(HWND w, UINT m, WPARAM wp, LPARAM lp)
{
	if (m == WM_SETCURSOR) {
		SetCursor(NULL);
		return TRUE;
	}
	return DefWindowProcA(w, m, wp, lp);
}

void platform_playMovie(void *owner, const char *file, int w, int h)
{
	(void)w;
	(void)h;
	char path[MAX_PATH];
	if (!GetFullPathNameA(file, sizeof path, path, NULL))
		lstrcpynA(path, file, sizeof path);
	iv32_install();
	/* MCIAVI scales the rectangles it is given by the display scaling (DESKTOPHORZRES / HORZRES) */
	HDC screen = GetDC(NULL);
	int physW = GetDeviceCaps(screen, DESKTOPHORZRES), logW = GetDeviceCaps(screen, HORZRES);
	ReleaseDC(NULL, screen);
	if (physW <= 0 || logW <= 0)
		physW = logW = 1;
	int sw = GetSystemMetrics(SM_CXSCREEN), sh = GetSystemMetrics(SM_CYSCREEN);
	WNDCLASSA wc = { 0 };
	wc.lpfnWndProc = movie_window;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.hbrBackground = GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "AxisMovie";
	RegisterClassA(&wc);
	HWND win = CreateWindowExA(WS_EX_TOPMOST, wc.lpszClassName, "Axis", WS_POPUP | WS_VISIBLE, 0, 0, sw, sh, (HWND)owner,
	                           NULL, wc.hInstance, NULL);
	MCI_DGV_OPEN_PARMSA open = { 0 };
	open.lpstrDeviceType = "AVIVideo";
	open.lpstrElementName = path;
	MCIERROR e = win ? mciSendCommandA(0, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD_PTR)&open) : MCIERR_INTERNAL;
	if (e) {
		if (win)
			DestroyWindow(win);
		UnregisterClassA(wc.lpszClassName, wc.hInstance);
		return;
	}
	MCIDEVICEID dev = open.wDeviceID;
	MCI_DGV_RECT_PARMS source = { 0 };   /* (MCI rectangles: x, y, width, height) */
	int vw = 4, vh = 3;
	if (!mciSendCommandA(dev, MCI_WHERE, MCI_DGV_WHERE_SOURCE, (DWORD_PTR)&source) && source.rc.right > 0 && source.rc.bottom > 0) {
		vw = source.rc.right;
		vh = source.rc.bottom;
	}
	int dw = sw, dh = sw * vh / vw;
	if (dh > sh) {
		dh = sh;
		dw = sh * vw / vh;
	}
	MCI_DGV_WINDOW_PARMSA window = { 0 };
	window.hWnd = win;
	mciSendCommandA(dev, MCI_WINDOW, MCI_DGV_WINDOW_HWND, (DWORD_PTR)&window);
	MCI_DGV_PUT_PARMS put = { 0 };
	put.rc.left = MulDiv((sw - dw) / 2, logW, physW);
	put.rc.top = MulDiv((sh - dh) / 2, logW, physW);
	put.rc.right = MulDiv(dw, logW, physW);
	put.rc.bottom = MulDiv(dh, logW, physW);
	mciSendCommandA(dev, MCI_PUT, MCI_DGV_PUT_DESTINATION | MCI_DGV_RECT, (DWORD_PTR)&put);
	SetForegroundWindow(win);
	MCI_DGV_PLAY_PARMS play = { 0 };
	e = mciSendCommandA(dev, MCI_PLAY, 0, (DWORD_PTR)&play);
	DWORD start = GetTickCount();
	int quit = 0, played = 0;
	WPARAM quitCode = 0;
	while (!e) {
		MSG msg;
		while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				quit = 1;
				quitCode = msg.wParam;
				continue;
			}
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
		if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
			break;
		MCI_STATUS_PARMS status = { 0 };
		status.dwItem = MCI_STATUS_MODE;
		if (mciSendCommandA(dev, MCI_STATUS, MCI_STATUS_ITEM, (DWORD_PTR)&status))
			break;
		if (status.dwReturn == MCI_MODE_PLAY)
			played = 1;
		else if (status.dwReturn != MCI_MODE_SEEK && (played || GetTickCount() - start > 3000))
			break;
		Sleep(15);
	}
	mciSendCommandA(dev, MCI_CLOSE, 0, 0);
	DestroyWindow(win);
	UnregisterClassA(wc.lpszClassName, wc.hInstance);
	if (quit)
		PostQuitMessage((int)quitCode);
}
