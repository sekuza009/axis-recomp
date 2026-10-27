/* batch 206 (lifted/grp167.c .. grp170.c): functions whose call sites the patch DLL retargets; those calls are lifted
   with lift.py "@site" (the target read from the live instruction) and the rel32 bytes listed in g_patchOk */
#include "lifted/grp167.c"
/* 0x48b200 match_inputState2() (thiscall on the scene): the match's frame: the round start (0x49df10) until
   +0x233cc28, the frame timer (armc_461210 -> dt at +0x44), the clocks (+0x233cc34 / +0x233cc30 whole seconds,
   +0x2340c90 with the per-second rates +0x2340c88 / +0x2340c8c from the counters +0x2340c80 / +0x2340c84), three
   countdowns (+0x233cc40, +0x2342f02, +0x2340d39); the combat input (match_combatInput), the game mode
   (game_processGameMode), in state 2 the HUD pass (hud_pass: @0x48b386, the patch DLL's hud_pass_wrap); a pending
   quit (+0x23432cf) ends it (0x457310, 0), else the state +0x233cc20 */
static THISCALL DWORD match_inputState2(char *s) { return run_lifted(lift_48b200, (DWORD)s, 0, NULL); }
#include "lifted/grp168.c"
/* 0x41fa40 menu_frame(): the menus' frame: the cursor blink 0x4dda44, the screen's music (0x41f970), the keys
   (0x445e40, menu_processKeys) unless 0x9da49c is 0x68 / 0x69; on screen 300 the launch fade (0x4e1870, 0x4df02c,
   0x4dda48) into a match (9999); 0x41f820; the screen's frame by 0x76d3e8 (100 .. 900); a dialog (0x4290d0); the
   pointer (0x428940) while 0x68039c; GL resets, the menu cursor (@0x41fc28: 0x429bc0, the patch DLL's
   cursor_draw), glFinish, SwapBuffers; the brightness step 0x68038c by 0x4e0464; the frame time (timer_now): the FPS
   every second (0x83a9d4), the frame's dt 0x4b071c (at most 1) */
LIFT_PLAIN(menu_frame, 41fa40)
#include "lifted/grp169.c"
/* 0x460570 game_loadAllData() (thiscall: the scene's constructor): the timers, every member array built (0x401290 /
   the CRT's vector constructor 0x49fd2d), vtables set, the parts loaded (0x4700a0 with nine names; @0x460920:
   0x473780, the patch DLL's cat_wrap; 0x4875d0; failure: 0x46c710 to the log), the ten camera presets, 0x45dfb0,
   the HUD defaults, up to 30 chat macros (63 characters each) read from a text file by fgets with their line ends
   cut, 0x4617f0. SEH frame emulated. Returns the scene */
static THISCALL DWORD game_loadAllData(char *s) { return run_lifted(lift_460570, (DWORD)s, 0, NULL); }
#include "lifted/grp170.c"
/* 0x4982f0 hud_pass() (thiscall on the scene): the in-match 2D pass: GL state, the fog colour from +0xbe16f8 ..,
   clears, the HUD projection (0x4685f0), the scene parts drawn in order (0x4841f0 .., 0x496f20 / 0x497d20 with
   0x468700's scale), the overlays by the scene's flags and the local player's record: the player markers
   (@0x498580: 0x4913a0), the lock-on (@0x4985c4: 0x491f50), the main HUD (@0x498654: 0x4926f0), the ranking
   (@0x4986a0: 0x494930), messages, clock, team box, FPS (@0x498862: 0x495510) and the rest; the patch DLL wraps
   the five @ calls (markers_wrap .. fps_wrap) */
static THISCALL DWORD hud_pass(char *s) { return run_lifted(lift_4982f0, (DWORD)s, 0, NULL); }
