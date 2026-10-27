/* batch 195 (lifted/grp151.c): the loading screen's state machine */
#include "lifted/grp151.c"
/* 0x468750 game_processLoadingMode() (thiscall on the scene): one step of loading per call. On the first call
   (+0x233cc28 == 0) the loading lines are reset (+0x2340c60 lines of 0x100 bytes at +0x233cc60, the title line).
   By the stage (+0x233cc24, 0..8): the replay file's header read (mode 3), the map named (0x9dad94 into 0x907b30;
   an empty name ends it with 0xa0ea94 set), waiting for the players (the network packets drained through the patch
   DLL's 0x4a8350 / 0x4a8450 into net_processGamePacket; Esc / the keys 0x4defc8 / 0x4defcc to stop), the map's
   ground, objects, sky, sounds and actors loaded, then the game started (+0x233cc20 by the game mode +8). Each
   stage adds a line (the next stage depends on the mode); every step then draws the screen (the GL clear, the
   lines). Returns +0x233cc20. The loaders and the drawing are stubbed */
static THISCALL DWORD game_processLoadingMode(char *s) { return run_lifted(lift_468750, (DWORD)s, 0, NULL); }
