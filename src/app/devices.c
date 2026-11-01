/* devices.c: DirectInput's keyboard and mouse (taken while the window is active, let go when it is not) and the
   objects released when the game closes. */
#include "../game.h"
#include "../wide.h"
#include <string.h>

#define DI_ACQUIRE 0x1c
#define DI_UNACQUIRE 0x20

#define g_directInput GAME_VAR(void *, 0x4d1e98)
#define g_keyboard GAME_VAR(void *, 0x4d1fa0)
#define g_mouse GAME_VAR(void *, 0x4d1fa4)
#define g_keyboardActive GAME_VAR(int, 0x4d1fa8)      /* (by use) the window is active: the keyboard may be taken */
#define g_mouseActive GAME_VAR(int, 0x4d1fac)
#define g_mouseTaken GAME_VAR(int, 0x4ad17c)          /* (by use) 0: the mouse is let go instead of taken */

/* 0x4012c0: take the keyboard again */
void (input_reacquireKeyboard)(void)
{
	if (g_keyboard != NULL && g_keyboardActive != 0)
		COM(g_keyboard, DI_ACQUIRE, long)(g_keyboard);
}

/* 0x4012e0: take the mouse again (or let it go while g_mouseTaken is 0); 1 when there is a mouse */
int (input_reacquireMouse)(void)
{
	if (g_mouse == NULL)
		return 0;
	if (g_mouseTaken != 0)
		COM(g_mouse, DI_ACQUIRE, long)(g_mouse);
	else
		COM(g_mouse, DI_UNACQUIRE, long)(g_mouse);
	return 1;
}

/* 0x401460: let the keyboard go and release it */
void (input_releaseKeyboard)(void)
{
	if (g_keyboard != NULL) {
		COM(g_keyboard, DI_UNACQUIRE, long)(g_keyboard);
		COM(g_keyboard, COM_RELEASE, long)(g_keyboard);
		g_keyboard = NULL;
	}
	g_keyboardActive = 0;
}

/* 0x401490: the same for the mouse */
void (input_releaseMouse)(void)
{
	if (g_mouse != NULL) {
		COM(g_mouse, DI_UNACQUIRE, long)(g_mouse);
		COM(g_mouse, COM_RELEASE, long)(g_mouse);
		g_mouse = NULL;
	}
	g_mouseActive = 0;
}

/* 0x4014c0: all of DirectInput released */
void (input_releaseAll)(void)
{
	input_releaseKeyboard();
	input_releaseMouse();
	if (g_directInput != NULL) {
		COM(g_directInput, COM_RELEASE, long)(g_directInput);
		g_directInput = NULL;
	}
}

/* 0x467b70: DirectSound released */
void (sound_releaseDirectSound)(void)
{
	if (g_directSound != NULL) {
		COM(g_directSound, COM_RELEASE, long)(g_directSound);
		g_directSound = NULL;
	}
}

#define DI_GETDEVICESTATE 0x24
#define DIERR_INPUTLOST 0x8007001eL
#define g_keyState ((u8 *)IMG(0x4d1e9c))                    /* the keyboard's 256 key bytes (0x80: held) */

/* the keyboard's state into g_keyState; when the keyboard was lost it is taken again */
static long read_keys(void)
{
	long r = COM(g_keyboard, DI_GETDEVICESTATE, long, u32, void *)(g_keyboard, 0x100, g_keyState);
	if (r == (long)DIERR_INPUTLOST)
		input_reacquireKeyboard();
	return r;
}

/* 0x4014f0 (input_keyHeld): 1 while key (a DIK code) is held */
int (input_keyHeld)(int key)
{
	if (g_keyboardActive == 0)
		return 0;
	if (read_keys() < 0)
		return 0;
	return (g_keyState[key] & 0x80) ? 1 : 0;
}

/* 0x401540 (input_keyHeldChecked): the same, 0 when reading the keyboard did not fully succeed */
int (input_keyHeldChecked)(int key)
{
	if (g_keyboardActive == 0)
		return 0;
	if (read_keys() != 0)
		return 0;
	return g_keyState[key] >> 7;
}

/* 0x401410: DirectInput (version 0x700) made for instance, then the keyboard and mouse for window; 1 when all
   three worked */
int (input_createDirectInput)(void *window, void *instance)
{
	if (DirectInputCreateA(instance, 0x700, &g_directInput, NULL) < 0)
		return 0;
	if (!input_initKeyboard(window))
		return 0;
	return input_createMouse(window) != 0;
}

/* ---- the cursor and the keys through Win32, only while the game's window (if there is one) is in front ---- */
#define GetForegroundWindow() IMPORT(0x4a92fc, void *, void)()
#define GetAsyncKeyState(key) IMPORT(0x4a92f8, u32, int)(key)
#define GetCursorPos(p) IMPORT(0x4a9300, u32, int *)(p)
#define SetCursorPos(x, y) IMPORT(0x4a9304, u32, int, int)(x, y)

/* 0x401730: the mouse read into the DIMOUSESTATE at 0x4d1a88 (16 bytes: movement x, y, wheel, 4 buttons), once per
   frame; when the input was lost the mouse is taken again and read again. As the installed exe has it (mousefix.py
   replaced the routine with code in the .axnet section's tail): while another window is in front, or the read or
   the re-take fails, the state is cleared instead of left as it was (a button down at an alt-tab stayed "held").
   1: read (or no mouse), 0: cleared */
#define DI_GETDEVICESTATE_MOUSE 0x24
#define DIERR_INPUTLOST_MOUSE 0x8007001e
int (input_readMouse)(void)
{
	void *state = (void *)IMG(0x4d1a88);
	if (g_hWndMain && GetForegroundWindow() != g_hWndMain)
		goto clear;
	if (g_mouse) {
		long r = COM(g_mouse, DI_GETDEVICESTATE_MOUSE, long, u32, void *)(g_mouse, 0x10, state);
		if (r == (long)DIERR_INPUTLOST_MOUSE) {
			if (COM(g_mouse, DI_ACQUIRE, long)(g_mouse) < 0)
				goto clear;
			r = COM(g_mouse, DI_GETDEVICESTATE_MOUSE, long, u32, void *)(g_mouse, 0x10, state);
		}
		if (r < 0)
			goto clear;
	}
	return 1;
clear:
	memset(state, 0, 16);
	return 0;
}

/* 0x445c60: the frame's mouse input. The mouse is taken again and read (input_readMouse; the patch DLL retargets
   this call to its own read around it: buttons after alt-tab, the menu cursor's speed); the pointer moves by the
   read's movement, the wheel gives g_mouseWheel (one notch of 120 = 1, down positive) and 0x4ded70 (turned at all).
   Outside a match (screen 0x270f) the pointer is kept to 0..630 x 0..474, or by the patch DLL's clamp (it replaces the block at 0x445cd8), which lets it
   reach the whole width of a wide screen (wide.h: cursorClampFix). Each button gives its held state (0 / 0x80) and
   a click pulse (OBJ(g_mouseClicked) + i * 4) on the frame it went down (0x9f1704 + i * 4: down last frame). */
void (input_updateMenuCursor)(void)
{
	const int *state = (const int *)IMG(0x4d1a88);   /* DIMOUSESTATE: x, y, wheel, buttons */
	GAME_FN(input_reacquireMouse, 0x4012e0, int, void)();          /* input_reacquireMouse */
	PATCHED_CALL(0x445c69, int, void)();        /* input_readMouse */
	int x = (int)((u32)g_mouseX + (u32)state[0]), y = (int)((u32)g_mouseY + (u32)state[1]), z = state[2];
	g_mouseWheelTurned = 0;
	g_mouseX = x;
	g_mouseY = y;
	if (z != 0)
		g_mouseWheelTurned = 1;
	g_mouseWheel = z / -120;
	if (g_screen != 0x270f) {
		if (*g_wide->cursorClampFix) {
			g_wide->cursorClamp();
		} else {
			if (x > 630)
				g_mouseX = x = 630;
			if (y > 474)
				g_mouseY = y = 474;
			if (x < 0)
				g_mouseX = 0;
			if (y < 0)
				g_mouseY = 0;
		}
	}
	const u8 *buttons = (const u8 *)IMG(0x4d1a94);
	for (int i = 0; i < 3; i++) {
		int held = buttons[i] & 0x80;
		int *pulse = (int *)(OBJ(g_mouseClicked) + i * 4), *was = (int *)(IMG(0x9f1704) + i * 4);
		GAME_VAR(int, OBJ(g_mouseButtonsHeld) + i * 4) = held;
		if (!held) {
			*pulse = 0;
			*was = 0;
		} else if (*was == 0) {
			*pulse = 1;
			*was = 1;
		} else {
			*pulse = 0;
		}
	}
}

/* 0x487c80: the cursor put at (x, y) (screen pixels). Returns what the original leaves in eax: SetCursorPos's
   answer, or the window in front when it isn't the game's */
u32 (input_setCursorPos)(int x, int y)
{
	if (g_hWndMain) {
		void *front = GetForegroundWindow();
		if (g_hWndMain != front)
			return (u32)front;
	}
	return SetCursorPos(x, y);
}

/* 0x487ba0: is the key down now (1 or 0; GetAsyncKeyState's low 16 bits)? */
int (input_asyncKeyDown)(int key)
{
	if (g_hWndMain && GetForegroundWindow() != g_hWndMain)
		return 0;
	return (u16)GetAsyncKeyState(key) != 0;
}

/* 0x487c30: the cursor's position (screen pixels) into 0xae2f18, left as it was while another window is in front;
   returns the point */
int *(input_getCursorPos)(void)
{
	if (!g_hWndMain || GetForegroundWindow() == g_hWndMain) {
		int p[2];
		GetCursorPos(p);
		g_cursorPos = p[0];
		g_cursorPosY = p[1];
	}
	return (int *)ADDR(g_cursorPos);
}

/* 0x487bd0: was the key just pressed (down now, and not already seen down)? The seen flags (0xae2f24 + key * 4) clear
   when the key is up */
int (input_asyncKeyPressed)(int key)
{
	if (g_hWndMain && GetForegroundWindow() != g_hWndMain)
		return 0;
	int *seen = (int *)(IMG(0xae2f24) + key * 4);
	if (!(u16)GetAsyncKeyState(key))
		*seen = 0;
	if (*seen)
		return 0;
	if (!(u16)GetAsyncKeyState(key))
		return 0;
	*seen = 1;
	return 1;
}

/* 0x401590: is the key bound to an action down? 0xfa .. 0xfc the mouse buttons (as their state), 0xfd / 0xfe the
   wheel turned down / up this frame, anything else a key held (1 or 0) */
int (input_isDown)(int key)
{
	switch (key) {
	case 0xfa:
		return g_mouseHeld;
	case 0xfb:
		return g_mouse2Down;
	case 0xfc:
		return g_mouse3Down;
	case 0xfd:
		return g_mouseWheel < 0;
	case 0xfe:
		return g_mouseWheel > 0;
	}
	return GAME_FN(input_keyHeldChecked, 0x401540, int, int)(key) != 0;   /* input_keyHeldChecked: held */
}

/* 0x401600: was the key bound to an action just pressed (true once per press)? A key latches in 0x4d1a98 + key * 4
   until it is seen released; the wheel (0xfd down) latches in 0x4d1e8c; 0xfe is the wheel turned up. The mouse
   buttons (0xfa .. 0xfc) answer the frame's click pulse (OBJ(g_mouseClicked) + i * 4) only when their flag (0x4d1e80 + i * 4),
   which flips on every call, was 0 - so with one test per frame about every other click was lost. The patch DLL
   (wide.h: pressedFix) makes the buttons latch like keys instead; with it installed they are its answer. */
int (input_justPressed)(int key)
{
	if (key >= 0xfa && key <= 0xfc) {
		if (*g_wide->pressedFix)
			return g_wide->mousePressed(key);
		int *flag = (int *)((OBJ(g_keySeen) + 0x3e8) + (key - 0xfa) * 4);
		if (*flag) {
			*flag = 0;
			return 0;
		}
		*flag = 1;
		return GAME_VAR(int, OBJ(g_mouseClicked) + (key - 0xfa) * 4);
	}
	if (key == 0xfd) {
		int *latch = (int *)(OBJ(g_keySeen) + 0x3f4);
		if (g_mouseWheel >= 0) {
			*latch = 0;
			return 0;
		}
		if (*latch)
			return 0;
		*latch = 1;
		return 1;
	}
	if (key == 0xfe)
		return g_mouseWheel > 0;
	int *seen = (int *)(OBJ(g_keySeen) + key * 4);
	if (!GAME_FN(input_keyHeld, 0x4014f0, int, int)(key))   /* input_keyHeld */
		*seen = 0;
	if (*seen)
		return 0;
	if (!GAME_FN(input_keyHeldChecked, 0x401540, int, int)(key))   /* input_keyHeldChecked */
		return 0;
	*seen = 1;
	return 1;
}

/* 0x4013a0: the DirectInput mouse made (once): the device (GUID_SysMouse at 0x4a9698), its data format (c_dfDIMouse,
   0x4a9610) and its cooperative level for the window (exclusive, foreground). 1 when ready, 0 on a failure */
int (input_createMouse)(void *window)
{
	if (g_mouseActive)
		return 1;
	void *dinput = g_directInput;
	if (COM(dinput, 0x0c, int, const void *, void **, void *)(dinput, (const void *)IMG(0x4a9698), &g_mouse, NULL) < 0)
		return 0;
	if (COM(g_mouse, 0x2c, int, const void *)(g_mouse, (const void *)IMG(0x4a9610)) < 0)
		return 0;
	if (COM(g_mouse, 0x34, int, void *, u32)(g_mouse, window, 5) < 0)
		return 0;
	g_mouseActive = 1;
	return 1;
}

/* 0x401310: the DirectInput keyboard made (once): the device (GUID_SysKeyboard, 0x4a9688), its data format
   (c_dfDIKeyboard, 0x4a95f8), its cooperative level for the window (non-exclusive, foreground), acquired, the key
   state (0x4d1a98) cleared. 1 when ready, 0 on a failure */
int (input_initKeyboard)(void *window)
{
	if (g_keyboardActive)
		return 1;
	void *dinput = g_directInput;
	if (COM(dinput, 0x0c, int, const void *, void **, void *)(dinput, (const void *)IMG(0x4a9688), &g_keyboard, NULL) < 0)
		return 0;
	if (COM(g_keyboard, 0x2c, int, const void *)(g_keyboard, (const void *)IMG(0x4a95f8)) < 0)
		return 0;
	if (COM(g_keyboard, 0x34, int, void *, u32)(g_keyboard, window, 6) < 0)
		return 0;
	COM(g_keyboard, DI_ACQUIRE, int)(g_keyboard);   /* (its result not checked) */
	memset((void *)OBJ(g_keySeen), 0, 0x400);
	g_keyboardActive = 1;
	return 1;
}
