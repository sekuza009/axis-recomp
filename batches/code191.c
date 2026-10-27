/* batch 190 (lifted/grp146.c): a bullet's frame */
#include "lifted/grp146.c"
/* 0x47a2d0 bullet_update(slot, dt) (thiscall on the scene, ret 8): bullet slot's flight (0x4e8 bytes from
   +0x202ef34): moved by its weapon's speed (the weapon record at +0x14d1ab4), aged, its homing towards its target,
   its trail particles, its hits found against the actors (math_segmentSphere and FUN_0047d9a0, real) and applied
   (bullet_playImpactSound, the damage: stubbed), its explosion; the hit sounds */
static THISCALL DWORD bullet_update(char *s, DWORD slot, DWORD dt) { DWORD v[2] = { slot, dt }; return run_lifted(lift_47a2d0, (DWORD)s, 2, v); }
