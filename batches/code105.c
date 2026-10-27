/* batch 104 (lifted/grp50.c) */
#include "lifted/grp50.c"
/* 0x48f970 (thiscall on the scene) hud_48f970(vv): draw the map's items (count +0x20fcd38, 0x28-byte entries from
   +0x20fadf8: type, position, angle, taken flag, fade) that are not taken and lie within the range +0xa08 of the
   camera (+0x20f3970..): in 3D mode (0x83a9c8 == 1, and always for type 34) the type's shape (+0x20f3ae0 + type *
   0x90, +0x8c) projected at the item's place and turn (ViewVolume_projectObject; faded items with a white colour of
   alpha 255 * fade), else a 300-unit billboard cut from the item atlas (8 icons per row, 32 px each) through the
   billboard object (+0x9ccff8, hud_484ca0) */
static THISCALL DWORD hud_48f970(char *sc, DWORD vv) { DWORD v[1] = { vv }; return run_lifted(lift_48f970, (DWORD)sc, 1, v); }
