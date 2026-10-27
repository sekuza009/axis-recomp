/* batch 155 (lifted/grp101.c): the in-match Esc menu */
#include "lifted/grp101.c"
/* 0x495610 (thiscall on the game) hud_drawEscMenu(): the in-match menu, fading in over its first 0.25 s (+0x2340c9c),
   by page (+0x2340cf8, 0..4): the title and the rows the mode allows (START / SPECTATOR for players without a slot
   +0x234243e, TEAM CHANGE in team games +0x22e7184, RECORD / STOP RECORD by +0x2340d1d, RETRY / EXIT ...), each on a
   panel (hud_495ed0) with its text (hud_44ae10, patched: native), the selected row +0x2340cfc bright; the other
   pages ask for confirmation, show the record name 0x9dc92c or the stage 0x9dad94 / progress 0x9f181c */
static THISCALL DWORD hud_drawEscMenu(char *game) { return run_lifted(lift_495610, (DWORD)game, 0, NULL); }
