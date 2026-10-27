/* batch 200 (lifted/grp156.c): the actors' frame loop */
#include "lifted/grp156.c"
/* 0x45e0c0 actor_updateAll(dt) (thiscall on the scene, ret 4): unless paused (+0x2149308 with +0x214930c == 1),
   each actor in use (+0x1cd94b0 == 1, +0x202e8c8 of them) gets its frame (actor_processFrame(i, dt)), the triggers
   run (script_processTriggers), and the game clock (+0x20fcd40 whole seconds, +0x20fcd44 the fraction) moves on */
static THISCALL DWORD actor_updateAll(char *s, DWORD dt) { DWORD v[1] = { dt }; return run_lifted(lift_45e0c0, (DWORD)s, 1, v); }
#include "lifted/grp157.c"
/* 0x48a370 match_inputState3() (thiscall on the scene): the free camera / test mode. On its first frame the ten
   cameras reset and the cursor centred; then the keys (movement W/A/S/D/Q/E, speed, camera 1..6, zoom, the F1..F6
   setting cycles with shift, Esc) set the scene's input flags, the cursor's offset moves the view, the local
   player's (+0x234240d) settings step through their tables (0x473b10.. on the scene's 0x1f36c8 part, bounded by
   the table sizes +0x15de6c8 ...), the camera vectors are rotated into place and set (0x4729b0), the frame runs
   unless replaying (actor_updateAll, bullets, particles), the scene is drawn (optionally a 100 x 150 grid of
   markers). Returns 3 after Esc, else 0. Callees stubbed except the screen / cursor / timer getters and the
   vector rotation */
static THISCALL DWORD match_inputState3(char *s) { return run_lifted(lift_48a370, (DWORD)s, 0, NULL); }
