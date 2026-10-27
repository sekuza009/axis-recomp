/* batch 199 (lifted/grp154.c): a script's commands */
#include "lifted/grp154.c"
/* 0x483770 script_processCommandBy(actor, trigger, entry) (thiscall on the scene, ret 0xc): the trigger's script
   (28-byte trigger records at +0xe3b03c, +0 their entry list), its entry (20 bytes: +0xc command count, +0x10 the
   commands): each 0x30-byte command by its type 0..0x1f: triggers on / off / armed, the acting actor's (-1: none;
   0x8888-byte records at +0x1cd93a8) orders, targets, speed and flags, players and objects reset or moved, sounds,
   messages, objects created from formatted names; the scene's handlers stubbed */
static THISCALL DWORD script_processCommandBy(char *s, DWORD actor, DWORD trig, DWORD entry) { DWORD v[3] = { actor, trig, entry }; return run_lifted(lift_483770, (DWORD)s, 3, v); }
#include "lifted/grp155.c"
/* 0x483640 script_processTriggers() (thiscall on the scene): every armed trigger (+0xe3c938 of them, 28-byte records
   at +0xe3b03c: +0 its point / entry list, +4 armed, +8 flags, +0xc time, +0x10 squared radius, +0x14 fired) fires
   on the game time (flag 1: +0x20fcd40 + +0x20fcd44 past its time) or on the player's actor (+0x202e8d4) inside its
   radius (flag 2); then each fired one runs its script (script_processCommandBy, no actor, entry 0), is cleared and
   disarmed, and its "ran" flag (+0xe3c618) set */
static THISCALL DWORD script_processTriggers(char *s) { return run_lifted(lift_483640, (DWORD)s, 0, NULL); }
