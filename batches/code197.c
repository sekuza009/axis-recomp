/* batch 196 (lifted/grp152.c): the replay viewer's frame */
#include "lifted/grp152.c"
/* 0x487f00 replay_frame() (thiscall on the scene; 9.3 KB: functions.csv had its second part, from 0x4885a0, as
   "hud_cycleF11Mode"): on the first frame (+0x233cc28 == 0) the cameras reset from the start view; then the frame
   time, the viewer's keys (camera 0..9, follow a player / the next / a random one, pause, speed, the HUD toggles),
   the free camera moved, the replay file (+0x2340d08) read up to the current time (+0x2340d2d): records of time,
   sender, length and packet (scrambled, 0x46cbe0) handed to net_processGamePacket; at its end the next map or back
   to the menu (returns 0 early); otherwise the scene's frame (objects, bullets, particles, items), the followed
   player's camera, the scene drawn and the HUD texts. Returns 1, or 4 when the viewer quits. Callees stubbed except
   the timers, the float getters, the vector rotation and the file reader */
static THISCALL DWORD replay_frame(char *s) { return run_lifted(lift_487f00, (DWORD)s, 0, NULL); }
