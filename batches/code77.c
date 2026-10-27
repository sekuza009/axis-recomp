/* batch 76 (lifted/grp23.c) */
#include "lifted/grp23.c"
/* 0x464bf0 (thiscall) model_loadFrom(path, mem, memSize): open the file (a failed open is fatal) and load it by its
   extension (after the last '.', not past a '\' or '/'; case-insensitive): "shp" the binary format (shape_read),
   "obj" Wavefront text (model_loadObjFormatFrom), anything else is fatal; then close it */
static THISCALL DWORD model_loadFrom(char *shape, DWORD path, DWORD mem, DWORD size)
{
	DWORD v[3] = { path, mem, size };
	return run_lifted(lift_464bf0, (DWORD)shape, 3, v);
}
