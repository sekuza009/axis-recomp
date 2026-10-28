/* devices.c: DirectInput's keyboard and mouse (taken while the window is active, let go when it is not) and the
   objects released when the game closes. */
#include "../game.h"

#define DI_ACQUIRE 0x1c
#define DI_UNACQUIRE 0x20

#define g_directInput GAME_VAR(void *, 0x4d1e98)
#define g_keyboard GAME_VAR(void *, 0x4d1fa0)
#define g_mouse GAME_VAR(void *, 0x4d1fa4)
#define g_keyboardActive GAME_VAR(int, 0x4d1fa8)      /* (by use) the window is active: the keyboard may be taken */
#define g_mouseActive GAME_VAR(int, 0x4d1fac)
#define g_mouseTaken GAME_VAR(int, 0x4ad17c)          /* (by use) 0: the mouse is let go instead of taken */
#define g_directSound GAME_VAR(void *, 0xa0e804)

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
void (wnd_401490)(void)
{
	if (g_mouse != NULL) {
		COM(g_mouse, DI_UNACQUIRE, long)(g_mouse);
		COM(g_mouse, COM_RELEASE, long)(g_mouse);
		g_mouse = NULL;
	}
	g_mouseActive = 0;
}

/* 0x4014c0: all of DirectInput released */
void (wnd_4014c0)(void)
{
	input_releaseKeyboard();
	wnd_401490();
	if (g_directInput != NULL) {
		COM(g_directInput, COM_RELEASE, long)(g_directInput);
		g_directInput = NULL;
	}
}

/* 0x467b70: DirectSound released */
void (wnd_467b70)(void)
{
	if (g_directSound != NULL) {
		COM(g_directSound, COM_RELEASE, long)(g_directSound);
		g_directSound = NULL;
	}
}

#define DI_GETDEVICESTATE 0x24
#define DIERR_INPUTLOST 0x8007001eL
#define g_keyState ((u8 *)0x4d1e9c)                    /* the keyboard's 256 key bytes (0x80: held) */

/* the keyboard's state into g_keyState; when the keyboard was lost it is taken again */
static long read_keys(void)
{
	long r = COM(g_keyboard, DI_GETDEVICESTATE, long, u32, void *)(g_keyboard, 0x100, g_keyState);
	if (r == (long)DIERR_INPUTLOST)
		input_reacquireKeyboard();
	return r;
}

/* 0x4014f0 (load_4014f0): 1 while key (a DIK code) is held */
int (load_4014f0)(int key)
{
	if (g_keyboardActive == 0)
		return 0;
	if (read_keys() < 0)
		return 0;
	return (g_keyState[key] & 0x80) ? 1 : 0;
}

/* 0x401540 (load_401540): the same, 0 when reading the keyboard did not fully succeed */
int (load_401540)(int key)
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
	return input_4013a0(window) != 0;
}
