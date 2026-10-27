/* batch 110 (lifted/grp56.c) */
#include "lifted/grp56.c"
/* 0x476890 (thiscall on the scene) hud_476890(i, vv): draw projectile i (0x12c-byte records at +0x20a99c0: frame,
   active, type, owner, position, ..., timer +0x6c / length +0x70): unless the type is 50 or more it must lie within
   the range +0xa08 of the camera; then by type (bullets, missiles, beams, explosions, shields, trails, ...) as
   billboards cut from the item atlas (textures +0x9ccfd4..; hud_484ca0 / hud_4848e0), transformed triangles
   (ViewVolume_transformObject) or the effect shapes (+0x20f2e74..; ViewVolume_projectObject), sized and faded by
   the timer, smaller for the viewing actor's own (+0x202e8d8). 0x479af0 hud_479af0(vv): every active projectile
   (count +0x20f2da0) */
static THISCALL DWORD hud_476890(char *sc, DWORD i, DWORD vv) { DWORD v[2] = { i, vv }; return run_lifted(lift_476890, (DWORD)sc, 2, v); }
static THISCALL DWORD hud_479af0(char *sc, DWORD vv) { DWORD v[1] = { vv }; return run_lifted(lift_479af0, (DWORD)sc, 1, v); }
