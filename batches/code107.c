/* batch 106 (lifted/grp52.c) */
#include "lifted/grp52.c"
/* 0x496f20 (thiscall on the scene) hud_496f20(scale): the level's sky, looking along the camera's direction
   (+0x20f397c..; gluLookAt): by mode, the sky sphere's six faces (+0x9ee064; textures +0x9ee068..), the outer / inner
   sky layers scrolling by +0x9ef0a8 / +0x9ef0ac (+0x9eee48; textures +0x9eee4c / +0x9eee50), the six side layers
   (+0x9ef0b0; textures +0x9ef0b4.., heights +0x9ef0d4..) scaled by the camera height, and the animated floor
   (+0x9ef30c; frame textures +0x9ef310.., vertices +0x9ef358..) under linear fog (hud_472900) with texture
   coordinates from the camera position */
static THISCALL DWORD hud_496f20(char *sc, DWORD scale) { DWORD v[1] = { scale }; return run_lifted(lift_496f20, (DWORD)sc, 1, v); }
