/* batch 111 (lifted/grp57.c) */
#include "lifted/grp57.c"
/* 0x48b9d0 (thiscall on the scene) map_loadGroundInfoFrom(name): the map's ground from "dir/name" (dir +0x108; no
   file or a version other than 0x1201 is fatal), all scrambled after the version: four blocks skipped, the map's
   directory name (0x100 bytes), the view range (+0xa08), the lights (load_483d70 into +0x9ccffc), clear colour
   and fog (+0x9ee030..+0x9ee060), the sky sphere / sky layer / side layer / animated floor modes (+0x9ee064,
   +0x9eee48, +0x9ef0b0, +0x9ef30c) whose textures are then looked up by name ("<dir>/SphereFloor", ...,
   "SkyInnerLayer", "SideLayer1..6", "FloorAni01..16"), ground colours (+0x9ef904..), and the layers (count
   +0xdc0a74; 0x20c-byte records from +0xdc0244): each with its texture "<dir>/Ground<i>Map" and a 256 x 256 RGB
   height map (grey pixels are heights, others 0), from which its arrays are built in the 4,000,000-byte pool at
   +0x9ef940 (used +0xdc0240; overflow is fatal): heights, flat-cell flags, vertices, normals (FUN_004679a0, sign by
   +0), light map (load_4728e0), texture coordinates, index and primitive buffers; finally the layer meshes
   (load_497a90). Returns 1 */
static THISCALL DWORD map_loadGroundInfoFrom(char *sc, DWORD name) { DWORD v[1] = { name }; return run_lifted(lift_48b9d0, (DWORD)sc, 1, v); }
