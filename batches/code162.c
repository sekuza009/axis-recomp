/* batch 161 (lifted/grp107.c): keyboard state, menu sounds, settings screens leaving */
#include "lifted/grp107.c"
/* the keyboard's state (GetDeviceState, 256 bytes into 0x4d1e9c) when ready (0x4d1fa8): 0x401540 load_401540(key):
   bit 7 of the key's byte, 0 on a failure (input lost: reacquire); 0x4014f0 load_4014f0(key): the same as 0 / 1 */
LIFT_PLAIN(load_401540, 401540)
LIFT_PLAIN(load_4014f0, 4014f0)
/* 0x401590 input_isDown(code): the mouse buttons 0xfa..0xfc (0x4ded94..), wheel down / up 0xfd / 0xfe (0x4ded7c < 0 /
   > 0), else the key */
LIFT_PLAIN(input_isDown, 401590)
/* 0x41e760 sound_playMenu(i): with sound (0xa0e80c == 1) the menu sound i (0x4dd4d4) at the sound volume 0x4dd984 */
LIFT_PLAIN(sound_playMenu, 41e760)
/* 0x443c80 skirmish_443c80() / 0x447960 FUN_00447960(): leave the skirmish / mission settings (state 0x9ef1f0 /
   0x9f62f8 = 0), the camera back (0x4e1870, 0x4df028 / 0x4df02c, 0x68037c / 0x680380), menu sound 4 and the saved
   camera (skirmish_447910) */
LIFT_PLAIN(skirmish_443c80, 443c80)
LIFT_PLAIN(FUN_00447960, 447960)
/* 0x4479b0 mission_4479b0(m): the mission m chosen (0x9f6328, 0x9f63b0 = 1), menu sound 2 */
LIFT_PLAIN(mission_4479b0, 4479b0)
