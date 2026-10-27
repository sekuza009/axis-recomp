/* batch 85 (lifted/grp31.c) */
#include "lifted/grp31.c"
/* 0x48fee0 (thiscall) object_initObjectBy(i, type): set up map object i (0x2cc bytes at +0x131ae44) from a 0xb0-byte
   object type record (shape name, three ints +0x40, sub-dir +0x4c, position +0x8c, rotation +0x98, +0xa4, +0xa8,
   +0xac). The type's name joins the scene's list (+0x130b440, 0x40 each, count +0x131ae40; 1000 is fatal) unless it
   is there; the object gets the next serial (+0x13c9b2c), the path "dir\sub\name" when +0x4c is set, its matrices
   (translation x rotation, inverse, two more pairs), its shape (shape_getByName at +0xe3c93c, bound), two element
   ranges of the shape's size from the pool at +0xf30dc8 (count +0x13016c8; past 1000000 is fatal), its shape centre
   through the matrix, and, unless +0x13016cc, its shading colours (FUN_00466910 with the factors at +0x9ccffc) */
static THISCALL DWORD object_initObjectBy(char *scene, DWORD i, DWORD type)
{
	DWORD v[2] = { i, type };
	return run_lifted(lift_48fee0, (DWORD)scene, 2, v);
}
