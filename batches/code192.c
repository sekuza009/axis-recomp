/* batch 191 (lifted/grp147.c): the bullets' and particles' frame loops */
#include "lifted/grp147.c"
/* 0x47d000 bullet_updateAll(dt) / 0x479a90 match_479a90(dt) (thiscall on the scene, ret 4): unless the game is paused
   (+0x2149308 with +0x214930c == 1), every bullet / particle slot in use up to the highest one (bullet_update /
   match_476410) */
static THISCALL DWORD bullet_updateAll(char *s, DWORD dt) { DWORD v[1] = { dt }; return run_lifted(lift_47d000, (DWORD)s, 1, v); }
static THISCALL DWORD match_479a90(char *s, DWORD dt) { DWORD v[1] = { dt }; return run_lifted(lift_479a90, (DWORD)s, 1, v); }
