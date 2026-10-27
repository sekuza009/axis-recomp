/* batch 102 (lifted/grp48.c) */
#include "lifted/grp48.c"
/* 0x474550 (thiscall on the scene) map_loadActorInfoFrom(name): the map's players and actors from "dir/name" (dir
   +0x108; no file or a version other than 0x1201 is fatal): three blocks skipped (scrambled length, then fseek), a
   fourth value, then the scrambled player count (+0x1cd6fb0) and 0x58-byte player records (+0x1cd6a30), the actor
   count (+0x1cd93a4) and 0x5c-byte actor records (+0x1cd6fb4). Every player but the first gets its part colours from
   its colour scheme (record +4, minus 1; actor_setPartColor with the built-in tables), the game mode's fixed items
   (as actor_setActorTypeItemInfoBy) and is set up from its record (load_4742f0); the player count goes to
   +0x19e1888, the actors after the first are marked active, the clan texture "Stage\<map +0x908>\Clan" is looked up
   (+0x2104fe4) and every player gets two fields set (+0x1561b68 + p * 0x47fd2 + 0x3fc6 / +0x3fce) */
static THISCALL DWORD map_loadActorInfoFrom(char *sc, DWORD name) { DWORD v[1] = { name }; return run_lifted(lift_474550, (DWORD)sc, 1, v); }
