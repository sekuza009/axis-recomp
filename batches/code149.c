/* batch 148 (lifted/grp94.c): the intro set-up */
#include "lifted/grp94.c"
/* 0x430bf0 intro_430bf0(): clear 0xc00 bytes at 0x67ef38, then the intro tables one by one (intro_430ab0,
   intro_42f2b0, intro_42f500, intro_42f690, intro_42f8e0, intro_430bd0), each followed by a loading-screen frame
   (intro_41f100, progress 0x4dda34 + 1) and, but for the last, a wait of 2.0 (intro_41e730) */
LIFT_PLAIN(intro_430bf0, 430bf0)
