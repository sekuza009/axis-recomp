/* batch 113 (lifted/grp59.c) */
#include "lifted/grp59.c"
/* 0x460cb0 (thiscall on the game) app_requireCd(a, mode): misnamed (the CD check is only its first step; the no-CD
   build's cd_findDrive always finds one): start a session of mode (+8; a kept at +4): counters cleared, in mode 3
   the names of the map list entries flagged +0x40 (0x9dda88, 0x44-byte records, count 0x9eeab8) copied to
   +0x1f1cbc (0x40 each, count +0x1f35bc); actors and scene reset; mode 2 also clears the armour cache, the view box
   and sets the game type flags for type 0; the camera from 0xa0e7a8.. (direction negated), the HUD mode +0x233cc20
   (2 -> 3, 3 -> 1, else 2) and its defaults, the match state (match_4636d0), the notices (match_463480) and the
   lobby slots (+0x234240d -1 in modes 1 and 3) */
static THISCALL DWORD app_requireCd(char *g, DWORD a, DWORD mode) { DWORD v[2] = { a, mode }; return run_lifted(lift_460cb0, (DWORD)g, 2, v); }
