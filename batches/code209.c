/* batch 208 (lifted/grp171.c, grp172.c): functions where the patch DLL overwrites a block of code; lift.py
   "%addr=bytes" lifts the patched block too and the lifted code runs whichever is in memory (g_patchOk lists it) */
#include "lifted/grp171.c"
/* 0x4913a0 hud_drawPlayerMarkers() (thiscall on the scene): for each other player in play (+0x1eccbbc == 1 and the
   record's marker flag, stride 0x8888) at its projected screen point: the off-screen arrow and the target box
   (textures from the set 0xa0e010 by +0xbc06ac / +0xbc06a0, quads through glTexCoord2f / glVertex2i), team
   colours (0x463740), the emblem (0x4922c0) and flag (0x4924d0), the shield bar by the frag count and the name
   label (@0x491c2d: 0x44ae10, the patch DLL's label_text) centred by its half width (0x491c52: len / 2 * 8, or
   the patch DLL's label_halfw(name) in its 21-byte block) */
static THISCALL DWORD hud_drawPlayerMarkers(char *s) { return run_lifted(lift_4913a0, (DWORD)s, 0, NULL); }
#include "lifted/grp172.c"
/* 0x49d290 match_combatInput() (thiscall on the scene): the match's input: 0x461f10; unless paused, dead or in a
   menu the key bindings (0x4deb58 .., 0x4def00 .., 0x4e0460 .., tested pressed by 0x401600 / held by 0x401590)
   set the scene's input flags (+0x2343257 .. +0x234331f), weapon and view choices, chat and menu keys; the mouse
   offset (+0x2343293 / +0x2343297) moves the in-match menu's selection (0x49ddcb: the original's own step, or the
   patch DLL's menu_nav in its 12-byte block) */
static THISCALL DWORD match_combatInput(char *s) { return run_lifted(lift_49d290, (DWORD)s, 0, NULL); }
