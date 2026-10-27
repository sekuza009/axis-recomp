/* batch 159 (lifted/grp105.c): DirectInput keyboard and mouse, DirectSound release */
#include "lifted/grp105.c"
/* DirectInput: the object 0x4d1e98, the keyboard 0x4d1fa0 (ready flag 0x4d1fa8, key states 0x4d1a98) and the mouse
   0x4d1fa4 (ready flag 0x4d1fac). 0x401310 input_initKeyboard(hwnd) / 0x4013a0 input_4013a0(hwnd): once, create the
   device, its data format (0x4a95f8 / 0x4a9610) and cooperative level (6: non-exclusive background / 5: exclusive
   foreground); the keyboard is acquired and its states cleared; 1 when ready, else 0 */
LIFT_PLAIN(input_initKeyboard, 401310)
LIFT_PLAIN(input_4013a0, 4013a0)
/* 0x401410 input_createDirectInput(hwnd, inst): DirectInputCreateA (version 0x700), then the keyboard and mouse */
LIFT_PLAIN(input_createDirectInput, 401410)
/* 0x4012c0 input_reacquireKeyboard(): Acquire when ready; 0x4012e0 input_reacquireMouse(): Acquire (or Unacquire
   when the game has no mouse capture, 0x4ad17c == 0), 1 if there is a mouse */
LIFT_PLAIN(input_reacquireKeyboard, 4012c0)
LIFT_PLAIN(input_reacquireMouse, 4012e0)
/* 0x401460 input_releaseKeyboard() / 0x401490 wnd_401490(): Unacquire and Release the keyboard / mouse, not ready;
   0x467b70 wnd_467b70(): Release DirectSound 0xa0e804 */
LIFT_PLAIN(input_releaseKeyboard, 401460)
LIFT_PLAIN(wnd_401490, 401490)
LIFT_PLAIN(wnd_467b70, 467b70)
