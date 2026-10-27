/* batch 77 (lifted/grp24.c) */
#include "lifted/grp24.c"
/* 0x46b1a0 (thiscall) skel_getSkeletonPtrBy(name): the skeleton cache. The name is upper-cased with '/' -> '\'
   (an empty one or one starting with '.' gives 0); it is looked up in the binary tree of 0x4c-byte nodes at +0x118
   (name, skeleton index +0x40, left +0x44 / right +0x48, unsigned byte order), count +0x120, capacity +0x114 (0 is
   fatal). A hit returns skeleton +0x11c + index * 0x24; a miss adds a node (overflow is fatal) and loads the
   skeleton by format +0x110: 0 "ske" / 1 "ase" files ("dir\name.ext" with dir +0x10, or "name.ext") through
   skel_loadFrom, 2 the item from the skeleton dat file (skelDat_getItemFileBy), anything else fatal; with data
   memory (+0x128 base, +0x124 size, +0x12c used) the skeleton's size is added to the used part */
static THISCALL DWORD skel_getSkeletonPtrBy(char *self, DWORD name)
{
	DWORD v[1] = { name };
	return run_lifted(lift_46b1a0, (DWORD)self, 1, v);
}
