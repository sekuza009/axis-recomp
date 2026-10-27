/* batch 212 (lifted/grp177.c): native until now, not changed in memory by the patch DLL (it wraps calls to them) */
#include "lifted/grp177.c"
/* 0x491f50 hud_drawLockOn() (thiscall on the scene): for each other player in play with a lock timer
   (+0x2222148, per player) the lock-on square at its screen point, the timer scaling it (textures from the set
   0xa0e010 by +0xbc06a0, quads through glTexCoord2f / glVertex2i) */
static THISCALL DWORD hud_drawLockOn(char *s) { return run_lifted(lift_491f50, (DWORD)s, 0, NULL); }
/* 0x429170 menu_titleEmblemTransition(): the title emblem (faded in by 0x4e0458 while 0x4df01c) and the zooming
   transition between menus (0x4de1d8 .. 0x4de1ec, textures 0x9dad6c .. 0x9dad88), through menu_vertex */
LIFT_PLAIN(menu_titleEmblemTransition, 429170)
/* 0x495510 hud_drawFps() (thiscall on the scene): the FPS icon (0x496820) and "%4.1f" of +0x38 (text_drawSized) */
static THISCALL DWORD hud_drawFps(char *s) { return run_lifted(lift_495510, (DWORD)s, 0, NULL); }
/* 0x4953d0 hud_4953d0() (thiscall on the scene): the chat line box: in chat modes 1 / 2 (+0x2340d35) the box
   (hud_4950a0) and the line typed (0x9dc92c), with a "_" cursor blinking by +0x233cc34 */
static THISCALL DWORD hud_4953d0(char *s) { return run_lifted(lift_4953d0, (DWORD)s, 0, NULL); }
/* 0x495190 replay_drawMessage() (thiscall on the scene): the message box (fading by +0x233cc40): the next message
   of the ring at +0x233c318 (32 x 20 bytes, read +0x233c59c / written +0x233c598) in its colour (0xa1f100 table)
   as four 0x41-byte lines of its text block (+0x22fbbd8, 0x108 each), else the last five events of the ring at
   +0x23429ce (0x108 each, coloured by their type 0..5) */
static THISCALL DWORD replay_drawMessage(char *s) { return run_lifted(lift_495190, (DWORD)s, 0, NULL); }
