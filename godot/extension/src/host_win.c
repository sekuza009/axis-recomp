/* host_win.c: the Windows calls AxisGame needs (kept apart from godot-cpp's headers, which windows.h does not mix
   with): the game folder in the environment, axis.dll loaded and its functions found. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "host_win.h"

int host_load(const char *library, const char *game_dir, AxisFunctions *f, char *error, int room)
{
	SetEnvironmentVariableA("AXIS_GAME_DIR", game_dir);   /* (axis.dll's files, settings and logs: the game folder) */
	HMODULE m = LoadLibraryA(library);
	if (!m) {
		wsprintfA(error, "cannot load %s (error %lu)", library, GetLastError());
		return 0;
	}
	struct { void **at; const char *name; } k[] = {
		{ (void **)&f->host, "axis_host" }, { (void **)&f->stream_header, "axis_stream_header" }, { (void **)&f->load, "axis_load" },
		{ (void **)&f->init, "axis_init@16" }, { (void **)&f->frame, "axis_frame" }, { (void **)&f->running, "axis_running" },
		{ (void **)&f->text_input, "axis_textInput" }, { (void **)&f->input, "axis_input" }, { (void **)&f->key, "axis_key" },
		{ (void **)&f->ch, "axis_char" }, { (void **)&f->exit, "axis_exit" }, { (void **)&f->shutdown, "axis_shutdown" },
	};
	for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++)
		if (!(*k[i].at = (void *)GetProcAddress(m, k[i].name))) {
			wsprintfA(error, "%s has no %s", library, k[i].name);
			return 0;
		}
	(void)room;
	return 1;
}

void *host_instance(void) { return GetModuleHandleA(NULL); }

/* ---- the mouse's raw movement (as DirectInput reads it: the device's own counts, no pointer acceleration). A
   message-only window registered for the mouse's raw input; Godot's message loop delivers its WM_INPUT (the same
   thread). Relative devices add their counts; absolute ones (remote desktops, tablets) their change of place ---- */
static HWND g_rawWnd;
static volatile LONG g_rawX, g_rawY, g_rawEvents;
static LONG g_absX = -1, g_absY = -1;
static LRESULT CALLBACK raw_proc(HWND w, UINT m, WPARAM wp, LPARAM lp)
{
	if (m == WM_INPUT) {
		RAWINPUT ri;
		UINT size = sizeof ri;
		if (GetRawInputData((HRAWINPUT)lp, RID_INPUT, &ri, &size, sizeof(RAWINPUTHEADER)) != (UINT)-1 && ri.header.dwType == RIM_TYPEMOUSE) {
			const RAWMOUSE *r = &ri.data.mouse;
			if (r->usFlags & MOUSE_MOVE_ABSOLUTE) {
				const int vw = GetSystemMetrics(r->usFlags & MOUSE_VIRTUAL_DESKTOP ? SM_CXVIRTUALSCREEN : SM_CXSCREEN);
				const int vh = GetSystemMetrics(r->usFlags & MOUSE_VIRTUAL_DESKTOP ? SM_CYVIRTUALSCREEN : SM_CYSCREEN);
				const LONG x = (LONG)((double)r->lLastX * vw / 65535.0), y = (LONG)((double)r->lLastY * vh / 65535.0);
				if (g_absX >= 0) { g_rawX += x - g_absX; g_rawY += y - g_absY; }
				g_absX = x;
				g_absY = y;
			} else {
				g_rawX += r->lLastX;
				g_rawY += r->lLastY;
			}
			g_rawEvents++;
		}
		return DefWindowProcA(w, m, wp, lp);
	}
	return DefWindowProcA(w, m, wp, lp);
}

/* the reader's own thread and message loop: Godot's loop takes the raw input messages of its thread for itself */
static HANDLE g_rawReady;
static DWORD WINAPI raw_thread(void *unused)
{
	(void)unused;
	WNDCLASSA wc = { 0 };
	wc.lpfnWndProc = raw_proc;
	wc.hInstance = GetModuleHandleA(NULL);
	wc.lpszClassName = "AxisRawMouse";
	RegisterClassA(&wc);
	g_rawWnd = CreateWindowA("AxisRawMouse", "", 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wc.hInstance, NULL);
	if (g_rawWnd) {
		RAWINPUTDEVICE d = { 1, 2, RIDEV_INPUTSINK, g_rawWnd };   /* generic desktop, mouse: delivered here even in the background */
		if (!RegisterRawInputDevices(&d, 1, sizeof d)) g_rawWnd = NULL;
	}
	SetEvent(g_rawReady);
	MSG m;
	while (g_rawWnd && GetMessageA(&m, NULL, 0, 0) > 0)
		DispatchMessageA(&m);
	return 0;
}

int host_raw_mouse_start(void)
{
	g_rawReady = CreateEventA(NULL, TRUE, FALSE, NULL);
	HANDLE t = CreateThread(NULL, 0, raw_thread, NULL, 0, NULL);
	if (!t) return 0;
	CloseHandle(t);
	WaitForSingleObject(g_rawReady, 2000);
	return g_rawWnd != NULL;
}

/* the mouse's raw input registered to the reader still (a process has one registration per device kind, and Godot
   registers its window too): 1 if it was, 0 if it had to be taken back */
int host_raw_mouse_keep(void)
{
	RAWINPUTDEVICE list[16];
	UINT n = 16;
	if (GetRegisteredRawInputDevices(list, &n, sizeof list[0]) != (UINT)-1)
		for (UINT i = 0; i < n; i++)
			if (list[i].usUsagePage == 1 && list[i].usUsage == 2 && list[i].hwndTarget == g_rawWnd)
				return 1;
	RAWINPUTDEVICE d = { 1, 2, RIDEV_INPUTSINK, g_rawWnd };
	RegisterRawInputDevices(&d, 1, sizeof d);
	return 0;
}

/* the pointer kept inside the host's window (on: while it has the focus) - the mouse's own capture, as the original's
   exclusive DirectInput mouse kept it; Godot's captured mode is not used (it takes the raw input over, and its motion
   events did not come) */
void host_confine(void *window, int on)
{
	if (!on || !window) {
		ClipCursor(NULL);
		return;
	}
	RECT r;
	GetClientRect((HWND)window, &r);
	POINT a = { r.left, r.top }, b = { r.right, r.bottom };
	ClientToScreen((HWND)window, &a);
	ClientToScreen((HWND)window, &b);
	RECT c = { a.x, a.y, b.x, b.y };
	ClipCursor(&c);
}

/* the movement since the last call (and the number of raw events, for the input log) */
void host_raw_mouse_take(int *dx, int *dy, int *events)
{
	*dx = (int)InterlockedExchange(&g_rawX, 0);
	*dy = (int)InterlockedExchange(&g_rawY, 0);
	*events = (int)InterlockedExchange(&g_rawEvents, 0);
}
