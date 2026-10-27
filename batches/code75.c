/* batch 74 (lifted/grp21.c) */
#include "lifted/grp21.c"
/* 0x4699d0 (thiscall) skel_loadFrom(path, mem, memSize): open the file (a failed open is fatal) and load it by its
   extension (after the last '.', not past a '\' or '/'; case-insensitive): "ske" the binary format
   (skel_loadFrom_46aa10), "ase" the text format (skel_loadAseFrom), anything else is fatal; then close it */
static THISCALL DWORD skel_loadFrom(char *sk, DWORD path, DWORD mem, DWORD size)
{
	DWORD v[3] = { path, mem, size };
	return run_lifted(lift_4699d0, (DWORD)sk, 3, v);
}
