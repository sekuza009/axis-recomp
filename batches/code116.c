/* batch 115 (lifted/grp61.c) */
#include "lifted/grp61.c"
/* 0x4700a0 (thiscall on the scene) item_initTextures(nine names): misnamed: the scene's whole start-up. The names
   kept (load_470de0); the space object at +0xa10 sized into its own memory +0xb04 (space_initBy); the ten textures
   "<name 3>\00".."\09" (+0x9ccfd4, the last two with flags 1); the lights reset (this_set_483d60, load_483e90 with
   the colour 0xa1f23c, load_4723e0, a grey ambient, load_483ec0); fog and sky cleared, the sky-sphere directions
   (+0x9ee080, 6 faces of 7 x 7), the sky layer and side directions, the floor grid (+0x9ef350, 11 x 11), the ground
   bounds (+-100000) and layer count; the mesh headers; the shape caches and skeleton pools (the scene's at +0xe3c93c
   / +0x13016d0, five per player, the effect cache +0x19e188c and its skeletons) laid out in their own memory; the
   effect shapes (effect_initTextures) and the item textures (damage map, booster, shield: +0x20f2f3c..); two
   item matrices; a GL texture name +0x20fcfe0 and a 128 x 64 image of 0xa1f220; the game type flags for type 0;
   actors and scene reset; +4 = 1 */
static THISCALL DWORD item_initTextures(char *sc, DWORD a, DWORD b, DWORD c, DWORD d, DWORD e, DWORD f, DWORD g, DWORD h, DWORD i)
{
	DWORD v[9] = { a, b, c, d, e, f, g, h, i };
	return run_lifted(lift_4700a0, (DWORD)sc, 9, v);
}
