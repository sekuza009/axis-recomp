/* batch 189 (lifted/grp145.c): a particle's frame and an object's */
#include "lifted/grp145.c"
/* 0x476410 match_476410(slot, a2) (thiscall on the particle system, ret 8): the slot (0x12c bytes from +0x20a99c0)
   aged (+0x6c from the clock against its life +0x70: freed at the end, 0x4799f0), moved, slowed, faded and turned
   by its kind; trail particles spawned (particle_spawn); callees stubbed */
static THISCALL DWORD match_476410(char *ps, DWORD slot, DWORD a2) { DWORD v[2] = { slot, a2 }; return run_lifted(lift_476410, (DWORD)ps, 2, v); }
/* 0x490440 actor_render(i, dt) (thiscall on the scene, ret 8): object i's record (0x2cc bytes from +0x131ae44):
   its animation time advanced by dt and its speed, by mode (+0x2a0: once, loop, back and forth) wrapped or
   stopped, the pose applied (skel_applyPose), its matrices built (Mat4_multiply / Mat4_invert, real), the unit
   enabled in the space, effects spawned; callees stubbed */
static THISCALL DWORD actor_render(char *s, DWORD i, DWORD dt) { DWORD v[2] = { i, dt }; return run_lifted(lift_490440, (DWORD)s, 2, v); }
