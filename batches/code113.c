/* batch 112 (lifted/grp58.c) */
#include "lifted/grp58.c"
/* 0x4680d0 glWindow_wndProc(wnd, msg, w, l) (stdcall, the window class's procedure): WM_CREATE hides the cursor,
   takes the window's DC (0xa0e938), sets its pixel format (glWindow_setupPixelFormat; failure quits) and makes a GL
   context current (0xa0e93c); WM_SIZE resizes the GL view (glWindow_resize); WM_PAINT validates; WM_CLOSE destroys
   the window; WM_DESTROY deletes the context, releases the DC, restores the display mode, shows the cursor and
   quits; anything else goes to DefWindowProcA */
static LRESULT WINAPI glWindow_wndProc(DWORD wnd, DWORD msg, DWORD w, DWORD l)
{
	DWORD v[4] = { wnd, msg, w, l };
	return (LRESULT)run_lifted(lift_4680d0, 0, 4, v);
}
/* 0x468250 glWindow_init(title, w, h, depth, a, fullscreen, parent, b): the game window, once (a second call gives
   a message and 0): the title (0xa0e81c) and the mode kept, the window class registered (failure: message, 0), the
   display mode switched for full screen (glWindow_setDisplayModeBy), the window created (a child of parent, or
   pop-up), shown, focused and the GL state set (glWindow_4684c0); returns the window */
LIFT_PLAIN8(glWindow_init, 468250)
