/* batch 93 (lifted/grp39.c) */
#include "lifted/grp39.c"
/* (thiscall) hud_drawNameIcon(n, x, y) / hud_drawLeaderIcon(i, x, y) / replay_drawIcon(x, y, i): a 2D icon from a HUD
   texture atlas at a screen position scaled to the window (gfx_getWidth / gfx_getHeight): the name icon n (1..;
   10 per row; texture +0xbc06b0), the leader icon i (texture +0x22f86ac, or the GL texture +0x22f06a8 when +8 is
   set), the replay icon i (8 per row, white; texture +0xbc06b0) */
static THISCALL DWORD hud_drawNameIcon(char *self, DWORD n, DWORD x, DWORD y) { DWORD v[3] = { n, x, y }; return run_lifted(lift_4922c0, (DWORD)self, 3, v); }
static THISCALL DWORD hud_drawLeaderIcon(char *self, DWORD i, DWORD x, DWORD y) { DWORD v[3] = { i, x, y }; return run_lifted(lift_4924d0, (DWORD)self, 3, v); }
static THISCALL DWORD replay_drawIcon(char *self, DWORD x, DWORD y, DWORD i) { DWORD v[3] = { x, y, i }; return run_lifted(lift_496820, (DWORD)self, 3, v); }
