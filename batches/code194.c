/* batch 193 (lifted/grp149.c): the objects' frame loop, the followed player's name, the sound table */
#include "lifted/grp149.c"
/* 0x490d40 match_490d40(dt) (thiscall on the scene, ret 4): unless the game is paused (+0x2149308 with +0x214930c ==
   1), every object in use (0x2cc-byte records, flag +0x131ae48, count +0x13c9b24) gets its frame (0x490440, its
   index and dt) */
static THISCALL DWORD match_490d40(char *s, DWORD dt) { DWORD v[1] = { dt }; return run_lifted(lift_490d40, (DWORD)s, 1, v); }
/* 0x496b80 replay_drawFollowedName() (thiscall on the scene): white text at (0x192, 0x280), the followed player's
   name (+0x2340c64, the 0x888-byte player records' names at +0x1eccb08) or the fixed text when there is none */
static THISCALL DWORD replay_drawFollowedName(char *s) { return run_lifted(lift_496b80, (DWORD)s, 0, NULL); }
/* 0x456d10 sound_initSoundTable(file, volume): with sound on (0xa0e80c), the table freed (0x456cd0), the volume set,
   the file opened (an error message when it does not open) and read descrambled (0x46cbe0): index, 0x100-byte
   name, ... until an index < 0, each name loaded (sound_loadWav) into the table 0xa0e02c; 1, or 0 with sound off */
LIFT_PLAIN(sound_initSoundTable, 456d10)
