/* batch 71 (lifted/grp18.c) */
#include "lifted/grp18.c"
/* 0x46f7a0 (thiscall) data_46f7a0(factors, pixelLights): relight an object list's entries (count +0x10, 100 bytes
   apart from +0x14: shape, -, colour buffer, matrix): with neither, the colours (shape +0x18 dwords) are cleared;
   factors through the inverted matrix (FUN_00466910), pixel lights (FUN_00466960) on top or alone */
static THISCALL DWORD data_46f7a0(char *list, DWORD fac, DWORD px) { DWORD v[2] = { fac, px }; return run_lifted(lift_46f7a0, (DWORD)list, 2, v); }
/* 0x46fd20 (thiscall) hud_46fd20(vv, factors, pixelLights, a, b, c): if the list has frames (+0x1c, the current one
   +0x20[+0x24] set) and entries: each entry is lit as in data_46f7a0 when the list is pre-lit (+0x2c == 1; factors
   only when their pool's +0xb00c is 1) and then projected with its own colours, else projected with the lights
   passed on (ViewVolume_projectObject). Returns 1 if it ran, else 0 */
static THISCALL DWORD hud_46fd20(char *list, DWORD vv, DWORD fac, DWORD px, DWORD a, DWORD b, DWORD c)
{
	DWORD v[6] = { vv, fac, px, a, b, c };
	return run_lifted(lift_46fd20, (DWORD)list, 6, v);
}
