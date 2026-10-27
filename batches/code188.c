/* batch 187 (lifted/grp141.c, grp142.c: split, they call each other): particles */
#include "lifted/grp141.c"
#include "lifted/grp142.c"
/* the particle system (thiscall: its object, the scene at BUF in the tests): 1000 slots of 0x12c bytes from
   +0x20a99c0 (used flag +4), the next free +0x20f2da4, the highest used +0x20f2da0, a serial +0x20f2da8.
   0x479950 particle_spawn(desc) (ret 4): the first free slot from the next free one on (-1 when full), set up by
   particle_init; returns the slot */
static THISCALL DWORD particle_spawn(char *ps, DWORD desc) { DWORD v[1] = { desc }; return run_lifted(lift_479950, (DWORD)ps, 1, v); }
/* 0x475070 particle_init(slot, desc) (ret 8): the slot from the descriptor (kind +0x30, positions, velocities,
   colours, sizes, life), its matrix (Mat4_invert, real), the sound (sound_play3D) and child particles
   (particle_spawn) */
static THISCALL DWORD particle_init(char *ps, DWORD slot, DWORD desc) { DWORD v[2] = { slot, desc }; return run_lifted(lift_475070, (DWORD)ps, 2, v); }
