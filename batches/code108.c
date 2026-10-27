/* batch 107 (lifted/grp53.c) */
#include "lifted/grp53.c"
/* 0x495ed0 (thiscall) hud_495ed0(x, y, w, h): a HUD panel: the rectangle in 640 x 480 units scaled to the window
   (gfx_getWidth / gfx_getHeight), drawn as a textured quad (texture +0xbc06b4, the full image) */
static THISCALL DWORD hud_495ed0(char *self, DWORD x, DWORD y, DWORD w, DWORD h)
{
	DWORD v[4] = { x, y, w, h };
	return run_lifted(lift_495ed0, (DWORD)self, 4, v);
}
