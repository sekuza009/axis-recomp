/* batch 60 (lifted/grp8.c) */
#include "lifted/grp8.c"
/* 0x49d150 (thiscall) match_49d150: add the local player's hits/shots/kills since the last call to the totals
   (0x4de72e..) and remember the new values; without a replay running, send the result (match_44aee0) */
static THISCALL DWORD match_49d150(char *scene) { return run_lifted(lift_49d150, (DWORD)scene, 0, NULL); }
/* 0x43f460 chat_createEdit(parent): the chat input box: a font (12 px, charset by language), an edit control,
   its window procedure replaced, focus */
LIFT_PLAIN(chat_createEdit, 43f460)
/* 0x42bee0 reg_readCharacterSettings: player name and character choices from the registry (created with the
   defaults if missing) */
LIFT_PLAIN(reg_readCharacterSettings, 42bee0)
/* 0x4734d0 (thiscall) gfx_saveScreenshot(p): load player p's emblem picture (Save\<name>.BMP, at least 23 x 15)
   into the player record as 24 x 16 RGBA, black = transparent */
static THISCALL DWORD gfx_saveScreenshot(char *scene, DWORD p) { DWORD v[1] = { p }; return run_lifted(lift_4734d0, (DWORD)scene, 1, v); }
/* 0x473780 (thiscall) catalogue_loadComponents(path): the actor component catalogue (version 0x1204): six
   sections of part records (0xaa8 .. 0x2e18 bytes each, at most 50), read through the descrambling reader */
static THISCALL DWORD catalogue_loadComponents(char *scene, DWORD path) { DWORD v[1] = { path }; return run_lifted(lift_473780, (DWORD)scene, 1, v); }
