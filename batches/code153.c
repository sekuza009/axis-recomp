/* batch 152 (lifted/grp98.c): the HUD clock */
#include "lifted/grp98.c"
/* 0x496610 (thiscall on the game) hud_drawClock(): with a score limit (+0x23423ad) the points still needed (team
   mode +0x22e7184 == 1: the better of +0x2221fbc / +0x2221fb8, else the leading player's +0x1eccb54 of record
   +0x23428f6 when there are any, +0x2342976), blinking red at 1 (by +0x22f040c), "%d" right-aligned with its icon
   (replay_drawIcon 1); with a time limit (+0x23423b1 minutes) the time left (against +0x22f0408 seconds) as
   "%02d:%02d", blinking red under 11 s, with icon 2. Text through text_drawSized (patched: native) */
static THISCALL DWORD hud_drawClock(char *game) { return run_lifted(lift_496610, (DWORD)game, 0, NULL); }
