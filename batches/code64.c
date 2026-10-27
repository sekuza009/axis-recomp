/* batch 63: the map's play and mission info loaders (lifted/grp10.c) */
#include "lifted/grp10.c"
/* 0x4876b0 (thiscall) map_loadPlayInfoFrom(name): <dir +0x108>\<name>, version 0x1201, skip the first section, then
   the play records (0x24 bytes, read 0x71c at a time into a 64 KB frame) through the descrambling reader: type 0
   the player start (+0x20fab60, angles x10), 1 a multiplayer start (at most 32), 2 an item point (at most 200; the
   item kind remapped by the game options at +0x20f3ac0..) */
static THISCALL DWORD map_loadPlayInfoFrom(char *map, DWORD name) { DWORD v[1] = { name }; return run_lifted(lift_4876b0, (DWORD)map, 1, v); }
/* 0x48b5c0 (thiscall) map_loadMissionInfoFrom(name): version 0x1201, skip two sections, then the actions
   (load_48b460), waypoint lists and triggers */
static THISCALL DWORD map_loadMissionInfoFrom(char *map, DWORD name) { DWORD v[1] = { name }; return run_lifted(lift_48b5c0, (DWORD)map, 1, v); }
