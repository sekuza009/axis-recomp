/* batch 83 (lifted/grp29.c) */
#include "lifted/grp29.c"
/* 0x466430 (thiscall) shape_bindTextureBy(suffix, flags, 6 floats): for each of the shape's parts (count +0x10,
   0x80 bytes at +0x14, texture name +4): append "*" suffix to the name when the suffix is not empty (a result over
   63 characters is fatal), then look the texture up in the global set (0xa0e010, tex_getIdByName) into +0x44 */
static THISCALL DWORD shape_bindTextureBy(char *shape, DWORD sfx, DWORD flags, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f)
{
	DWORD v[8] = { sfx, flags, a, b, c, d, e, f };
	return run_lifted(lift_466430, (DWORD)shape, 8, v);
}
/* 0x466650 (thiscall) FUN_00466650(): with GL_TEXTURE_2D enabled, bind every part's texture (+0x44 >= 0: set
   index / 512, texture % 512) */
static THISCALL DWORD FUN_00466650(char *shape) { return run_lifted(lift_466650, (DWORD)shape, 0, NULL); }
