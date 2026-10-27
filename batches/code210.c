/* batch 209 (lifted/grp173.c): an actor's frame */
#include "lifted/grp173.c"
/* 0x4580b0 actor_processFrame(i, dt) (thiscall on the scene, ret 8; 21 KB): actor i (+0x1cd93a8, stride 0x8888) of
   player +0x10c (+0x1561b68, stride 0x47fd2) with its parts (head .. booster tables by the player's +0x30c ..
   +0x31c) and items: death (0x45dca0) once its armour is gone, the local player's view (0x45eab0), the movement,
   boost, jump and turning by the input flags and dt, the weapons' heat, reload and fire (bullets 0x460000, effects
   0x471400 / 0x471740), the parts' animation (0x45e1f0 .. 0x45e530), lock-on (0x473450), the camera vectors
   (0x46f770 / 0x46f8c0, Vec3_normalize, fpatan for the heading), sounds (0x46c140 ..), the scripts (0x483770),
   the KYRIE parts' lookup (@0x45c638: 0x473780, the patch DLL's cat_wrap) */
static THISCALL DWORD actor_processFrame(char *s, DWORD i, DWORD dt) { DWORD v[2] = { i, dt }; return run_lifted(lift_4580b0, (DWORD)s, 2, v); }
