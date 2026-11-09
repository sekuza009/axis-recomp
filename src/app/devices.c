/* devices.c: DirectInput's keyboard and mouse (taken while the window is active, let go when it is not) and the
   objects released when the game closes. */
#include "../game.h"
#include "../plat/plat.h"
#include "../wide.h"
#include "../fixes/fixes.h"
#include <string.h>



/* 0x4012c0: take the keyboard again */
void (input_reacquireKeyboard)(void)
{
	if (g_keyboard != 0 && g_keyboardReady != 0)
		IN_ACQUIRE(AP(void, g_keyboard));
}

/* 0x4012e0: take the mouse again (or let it go while g_mouseTaken is 0); 1 when there is a mouse */
int (input_reacquireMouse)(void)
{
	if (g_mouse == 0)
		return 0;
	if (g_mouseTaken != 0)
		IN_ACQUIRE(AP(void, g_mouse));
	else
		IN_UNACQUIRE(AP(void, g_mouse));
	return 1;
}

/* 0x401460: let the keyboard go and release it */
void (input_releaseKeyboard)(void)
{
	if (g_keyboard != 0) {
		IN_UNACQUIRE(AP(void, g_keyboard));
		IN_RELEASE(AP(void, g_keyboard));
		g_keyboard = AREF(NULL);
	}
	g_keyboardReady = 0;
}

/* 0x401490: the same for the mouse */
void (input_releaseMouse)(void)
{
	if (g_mouse != 0) {
		IN_UNACQUIRE(AP(void, g_mouse));
		IN_RELEASE(AP(void, g_mouse));
		g_mouse = AREF(NULL);
	}
	g_mouseReady = 0;
}

/* 0x4014c0: all of DirectInput released */
void (input_releaseAll)(void)
{
	input_releaseKeyboard();
	input_releaseMouse();
	if (g_directInput != 0) {
		IN_RELEASE(AP(void, g_directInput));
		g_directInput = AREF(NULL);
	}
}

/* 0x467b70: DirectSound released */
void (sound_releaseDirectSound)(void)
{
	if (g_directSound != 0) {
		SND_RELEASE(AP(void, g_directSound));
		g_directSound = AREF(NULL);
	}
}

#define DIERR_INPUTLOST 0x8007001eL

/* the keyboard's state into g_keyState; when the keyboard was lost it is taken again */
static long read_keys(void)
{
	long r = IN_READ(AP(void, g_keyboard), 0x100, g_keyState);
	if ((int)r == (int)DIERR_INPUTLOST)
		input_reacquireKeyboard();
	return r;
}

/* 0x4014f0 (input_keyHeld): 1 while key (a DIK code) is held */
int (input_keyHeld)(int key)
{
	if (g_keyboardReady == 0)
		return 0;
	if (read_keys() < 0)
		return 0;
	return (g_keyState[key] & 0x80) ? 1 : 0;
}

/* 0x401540 (input_keyHeldChecked): the same, 0 when reading the keyboard did not fully succeed */
int (input_keyHeldChecked)(int key)
{
	if (g_keyboardReady == 0)
		return 0;
	if (read_keys() != 0)
		return 0;
	return g_keyState[key] >> 7;
}

/* 0x401410: DirectInput (version 0x700) made for instance, then the keyboard and mouse for window; 1 when all
   three worked */
int (input_createDirectInput)(void *window, void *instance)
{
	if (IN_CREATE(instance, &g_directInput) < 0)
		return 0;
	if (!input_initKeyboard(window))
		return 0;
	return input_createMouse(window) != 0;
}

/* ---- the cursor and the keys through Win32, only while the game's window (if there is one) is in front ---- */
#define GetForegroundWindow() IMPORT_FN(GetForegroundWindow, void *, void)()
#define GetAsyncKeyState(key) IMPORT_FN(GetAsyncKeyState, u32, int)(key)
#define GetCursorPos(p) IMPORT_FN(GetCursorPos, u32, int *)(p)
#define SetCursorPos(x, y) IMPORT_FN(SetCursorPos, u32, int, int)(x, y)

/* 0x401730: the mouse read into the DIMOUSESTATE at g_mouseState (16 bytes: movement x, y, wheel, 4 buttons), once per
   frame; when the input was lost the mouse is taken again and read again. As the installed exe has it (mousefix.py
   replaced the routine with code in the .axnet section's tail): while another window is in front, or the read or
   the re-take fails, the state is cleared instead of left as it was (a button down at an alt-tab stayed "held").
   1: read (or no mouse), 0: cleared */
#define DIERR_INPUTLOST_MOUSE 0x8007001e
int (input_readMouse)(void)
{
	void *state = AP(void, OBJ(g_mouseState));
	if (g_mainWindow && AV(GetForegroundWindow()) != g_mainWindow)
		goto clear;
	if (g_mouse) {
		long r = IN_READ(AP(void, g_mouse), 0x10, state);
		if ((int)r == (int)DIERR_INPUTLOST_MOUSE) {
			if (IN_ACQUIRE(AP(void, g_mouse)) < 0)
				goto clear;
			r = IN_READ(AP(void, g_mouse), 0x10, state);
		}
		if (r < 0)
			goto clear;
	}
	return 1;
clear:
	memset(state, 0, 16);
	return 0;
}

/* 0x445c60: the frame's mouse input, on every screen. The mouse is taken again and read (input_readMouse; the patch DLL retargets
   this call to its own read around it: buttons after alt-tab, the menu cursor's speed); the pointer moves by the
   read's movement, the wheel gives g_mouseWheel (one notch of 120 = 1, down positive) and g_mouseWheelTurned (turned at all).
   Outside a match (screen 0x270f) the pointer is kept to 0..630 x 0..474, or by the patch DLL's clamp (it replaces the block at 0x445cd8), which lets it
   reach the whole width of a wide screen (wide.h: cursorClampFix). Each button gives its held state (0 / 0x80) and
   a click pulse (OBJ(g_mouseClicked) + i * 4) on the frame it went down (OBJ(g_mouseWasDown) + i * 4: down last frame). */
void (input_updateMouse)(void)
{
	const int *state = g_mouseState;   /* DIMOUSESTATE: x, y, wheel, buttons */
	input_reacquireMouse();          /* input_reacquireMouse */
#ifdef AXIS_NATIVE
	fix_readMouse();                 /* input_readMouse, buttons after alt-tab, the menu pointer's speed (fixes/input.c) */
#else
	SITE_CALL(0x445c69, input_readMouse, int, void)();        /* input_readMouse */
#endif
	int x = (int)((u32)g_mouseX + (u32)state[0]), y = (int)((u32)g_mouseY + (u32)state[1]), z = state[2];
	g_mouseWheelTurned = 0;
	g_mouseX = x;
	g_mouseY = y;
	if (z != 0)
		g_mouseWheelTurned = 1;
	g_mouseWheel = z / -120;
	if (g_screen != 0x270f) {
#ifdef AXIS_NATIVE
		fix_cursorClamp();   /* the whole width of a wide screen (fixes/input.c) */
	}
#else
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
#endif

	const u8 *buttons = AP(const u8, (ADDR_AT(g_mouseState, 3)));
	for (int i = 0; i < 3; i++) {
		int held = buttons[i] & 0x80;
		int *pulse = AP(int, (OBJ(g_mouseClicked) + i * 4)), *was = AP(int, (OBJ(g_mouseWasDown) + i * 4));
		g_mouseButtonsHeld[i] = held;
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
	if (g_mainWindow) {
		void *front = GetForegroundWindow();
		if (g_mainWindow != AV(front))
			return AV(front);
	}
	return SetCursorPos(x, y);
}

/* 0x487ba0: is the key down now (1 or 0; GetAsyncKeyState's low 16 bits)? */
int (input_asyncKeyDown)(int key)
{
	if (g_mainWindow && AV(GetForegroundWindow()) != g_mainWindow)
		return 0;
	return (u16)GetAsyncKeyState(key) != 0;
}

/* 0x487c30: the cursor's position (screen pixels) into g_cursorX, left as it was while another window is in front;
   returns the point */
int *(input_getCursorPos)(void)
{
	if (!g_mainWindow || AV(GetForegroundWindow()) == g_mainWindow) {
		int p[2];
		GetCursorPos(p);
		g_cursorX = p[0];
		g_cursorPosY = p[1];
	}
	return AP(int, ADDR(g_cursorX));
}

/* 0x487bd0: was the key just pressed (down now, and not already seen down)? The seen flags (g_asyncKeySeen + key * 4) clear
   when the key is up */
int (input_asyncKeyPressed)(int key)
{
	if (g_mainWindow && AV(GetForegroundWindow()) != g_mainWindow)
		return 0;
	int *seen = AP(int, (OBJ(g_asyncKeySeen) + key * 4));
	if (!(u16)GetAsyncKeyState(key))
		*seen = 0;
	if (*seen)
		return 0;
	if (!(u16)GetAsyncKeyState(key))
		return 0;
	*seen = 1;
	return 1;
}

/* 0x401590: is the key bound to an action down? 0xfa .. 0xfc the mouse buttons (as their state), 0xfd /
   0xfe the wheel turned up / down this frame (the game's key names WHEEL-UP / WHEEL-DOWN), anything else a key held
   (1 or 0) */
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
	return input_keyHeldChecked(key) != 0;   /* input_keyHeldChecked: held */
}

/* 0x401600: was the key bound to an action just pressed (true once per press)? A key latches in g_keySeen + key * 4
   until it is seen released; the wheel turned up (0xfd, WHEEL-UP) latches in 0x4d1e8c; 0xfe is the wheel turned down (WHEEL-DOWN). The mouse
   buttons (0xfa .. 0xfc) answer the frame's click pulse (OBJ(g_mouseClicked) + i * 4) only when their flag (0x4d1e80 + i * 4),
   which flips on every call, was 0 - so with one test per frame about every other click was lost. The patch DLL
   (wide.h: pressedFix) makes the buttons latch like keys instead; with it installed they are its answer. */
int (input_justPressed)(int key)
{
	if (key >= 0xfa && key <= 0xfc) {
#ifdef AXIS_NATIVE
		return fix_mousePressed(key);   /* they latch like keys (fixes/input.c) */
#else
		if (*g_wide->pressedFix)
			return g_wide->mousePressed(key);
		int *flag = (int *)((ADDR_AT(g_keySeen, 250)) + (key - 0xfa) * 4);
		if (*flag) {
			*flag = 0;
			return 0;
		}
		*flag = 1;
		return g_mouseClicked[key - 0xfa];
#endif
	}
	if (key == 0xfd) {
		int *latch = AP(int, (ADDR_AT(g_keySeen, 253)));
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
	int *seen = AP(int, (OBJ(g_keySeen) + key * 4));
	if (!input_keyHeld(key))   /* input_keyHeld */
		*seen = 0;
	if (*seen)
		return 0;
	if (!input_keyHeldChecked(key))   /* input_keyHeldChecked */
		return 0;
	*seen = 1;
	return 1;
}

/* 0x4013a0: the DirectInput mouse made (once): the device (GUID_SysMouse at k_GUID_SysMouse), its data format (c_dfDIMouse,
   k_c_dfDIMouse) and its cooperative level for the window (exclusive, foreground). 1 when ready, 0 on a failure */
int (input_createMouse)(void *window)
{
	if (g_mouseReady)
		return 1;
	void *dinput = AP(void, g_directInput);
	if (IN_CREATE_MOUSE(dinput, &g_mouse) < 0)
		return 0;
	if (IN_SET_MOUSE_FORMAT(AP(void, g_mouse)) < 0)
		return 0;
	if (IN_SET_WINDOW(AP(void, g_mouse), window, 5) < 0)
		return 0;
	g_mouseReady = 1;
	return 1;
}

/* 0x401310: the DirectInput keyboard made (once): the device (GUID_SysKeyboard, k_GUID_SysKeyboard), its data format
   (c_dfDIKeyboard, k_c_dfDIKeyboard), its cooperative level for the window (non-exclusive, foreground), acquired, the key
   state (g_keySeen) cleared. 1 when ready, 0 on a failure */
int (input_initKeyboard)(void *window)
{
	if (g_keyboardReady)
		return 1;
	void *dinput = AP(void, g_directInput);
	if (IN_CREATE_KEYBOARD(dinput, &g_keyboard) < 0)
		return 0;
	if (IN_SET_KEYBOARD_FORMAT(AP(void, g_keyboard)) < 0)
		return 0;
	if (IN_SET_WINDOW(AP(void, g_keyboard), window, 6) < 0)
		return 0;
	IN_ACQUIRE(AP(void, g_keyboard));   /* (its result not checked) */
	memset(AP(void, OBJ(g_keySeen)), 0, 0x400);
	g_keyboardReady = 1;
	return 1;
}
