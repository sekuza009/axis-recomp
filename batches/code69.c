/* batch 68 (lifted/grp15.c) */
#include "lifted/grp15.c"
/* 0x471040 (thiscall) collision_initVolume(sizeZ, sizeX, sizeY, margin, perBlock, depth): set up the level grid
   (scene +0xa10, space_setBy) over the level bounds (+0x9ef904 / +0x9ef910) with extent / size cells per axis; if
   +0x9ef30c, two triangles of the bottom face; every floor (+4 == 0) / ceiling (1) terrain layer's cells as two
   triangles each (the winding flipped for ceilings, vertices +0x3c, rows +0x18, columns +0x1c); every active object
   (+0x131ae48, 0x2cc apart, count +0x13c9b24; not flagged 4 at +8) as a unit of its shape (+0x278) through its matrix
   (+0xf0), stored at +0x288. Progress messages through FUN_00470fc0 */
static THISCALL DWORD collision_initVolume(char *scene, DWORD sz, DWORD sx, DWORD sy, DWORD mg, DWORD per, DWORD depth)
{
	DWORD v[6] = { sz, sx, sy, mg, per, depth };
	return run_lifted(lift_471040, (DWORD)scene, 6, v);
}
