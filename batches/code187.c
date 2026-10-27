/* batch 186 (lifted/grp140.c): game_processGameModeInit (a match's start: modes, teams, items, music),
   match_escMenu (the in-match menu's input), wnd_setCursor (in fact the shutdown: the game object deleted, input,
   music and sounds released, the cursor back), scene_loadPath, with their callees stubbed */
#include "lifted/grp140.c"
LIFT_PLAIN(game_processGameModeInit, 49df10)
LIFT_PLAIN(match_escMenu, 49ca70)
LIFT_PLAIN(wnd_setCursor, 4314e0)
/* 0x48fd50 scene_loadPath(path) (thiscall on the scene, ret 4) */
static THISCALL DWORD scene_loadPath(char *scene, DWORD path) { DWORD v[1] = { path }; return run_lifted(lift_48fd50, (DWORD)scene, 1, v); }
