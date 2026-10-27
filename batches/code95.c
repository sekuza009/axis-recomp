/* batch 94 (lifted/grp40.c) */
#include "lifted/grp40.c"
/* 0x4875d0 (thiscall on the scene) map_loadItemInfoFrom(path): the map's item types. The file must open and be
   version 0x1201 (else fatal); a scrambled count (+0x20f3adc) and that many 0x90-byte records (+0x20f3ae0) follow;
   each record with a non-empty name (+0) gets its shape (name +0x4c) from the cache at +0x19e188c, bound, into +0x8c
   (else 0). Returns 1 */
static THISCALL DWORD map_loadItemInfoFrom(char *scene, DWORD path) { DWORD v[1] = { path }; return run_lifted(lift_4875d0, (DWORD)scene, 1, v); }
