/* batch 84 (lifted/grp30.c) */
#include "lifted/grp30.c"
/* 0x466dc0 (thiscall) shape_getByName(name, bind): the shape cache, as skel_getSkeletonPtrBy (upper-cased name,
   empty or ".x" gives 0, binary tree of 0x4c-byte nodes at +0x118, count +0x120, capacity +0x114), shapes 0x4c bytes
   at +0x11c. A miss loads by format +0x110: 0 "shp" / 1 "obj" files through model_loadFrom, 2 the item of the shape
   dat (shape_findDatEntry, shape_read); then its parts' textures are looked up with the suffix +0x130 and the flags
   and colours +0x230..+0x248 (shape_bindTextureBy). bind == 1 also binds the shape's textures (FUN_00466650) */
static THISCALL DWORD shape_getByName(char *self, DWORD name, DWORD bind)
{
	DWORD v[2] = { name, bind };
	return run_lifted(lift_466dc0, (DWORD)self, 2, v);
}
