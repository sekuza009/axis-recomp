/* batch 202 (lifted/grp161.c): the fade step after a menu frame and the match's per-state frame */
#include "lifted/grp161.c"
/* 0x4202d0 FUN_004202d0(): a menu frame's end: 0x4572b0, then the fade 0x9da434 steps down by 0x4b071c while above
   its limit 0x4a93e8, then 0x420280 by tail call */
LIFT_PLAIN(FUN_004202d0, 4202d0)
/* 0x462050 main_462050() (thiscall on the scene): the match's frame by input state +0x233cc20 (1..4: 0x468750,
   0x48b200, match_inputState3, 0x487f00), each returning the next state; after states 2 (when +0x233c9e8 == 1),
   3 and 4 the frame is presented (0x4685d0). Returns the state */
static THISCALL DWORD main_462050(char *s) { return run_lifted(lift_462050, (DWORD)s, 0, NULL); }
