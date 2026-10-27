/* batch 186: game_processGameModeInit / match_escMenu generated (tools/gentests.py, thiscall on the game: ecx =
   BUF, zero apart from what the callees would set), wnd_setCursor and scene_loadPath by hand */
static const DWORD g_gs_49df10[] = { 0x4326f0, 1, 0x44ace0, 0, 0x456de0, 1, 0x457140, 1, 0x45dfb0, 1 | CS_POP, 0x4613a0, 1 | CS_POP, 0x4620e0, 0, 0x4629c0, 1 | CS_POP, 0x4636d0, 0, 0x4685b0, 0, 0x4685c0, 0, 0x46c710, 3, 0x4732f0, 1 | CS_POP, 0x473940, 2 | CS_POP, 0x4743e0, 1 | CS_POP, 0x487490, 0, 0 };
static const DWORD g_gi_49df10[] = { 0x4dc878, 0x4dc87c, 0x4dc880, 0x4dc884, 0x4dc888, 0x4dcf18, 0x4dcf1c, 0x4dcf20, 0x4dcf24, 0x4dcf28, 0x4dcf2c, 0x4de722, 0x4de72a, 0x4ded68, 0x4ded6c, 0x4df8e8, 0x4e0c90, 0x4e0c94, 0x5ae9c4, 0x67ef00, 0x68039c, 0x76d368, 0x76d408, 0x9da3e0, 0x9dad94, 0x9f1818, 0x9fd94c, 0xa1efb8, 0 };
static const DWORD g_gb_49df10[] = { 0x4d0710, 0x4d950c, 0x4dcfe4, 0x4dedd8, 0x9db9ec, 0xa0e778, 0 };
T_PLAIN(game_processGameModeInit, 0x49df10, gen_setup(g_gs_49df10, g_gi_49df10, g_gb_49df10); /* thiscall on the game */, BUF, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_49ca70[] = { 0x44ac90, 3, 0x44ace0, 0, 0x456e50, 2, 0x45dca0, 1 | CS_POP, 0x4613a0, 1 | CS_POP, 0x462150, 0, 0x462850, 0, 0x462d30, 2 | CS_POP, 0x462e30, 2 | CS_POP, 0x463450, 2, 0x4635b0, 3 | CS_POP, 0x463610, 3 | CS_POP, 0x463740, 1 | CS_POP, 0x487cb0, 1 | CS_POP, 0x487ed0, 0, 0x49ca20, 2 | CS_POP, 0x49d150, 0, 0 };
static const DWORD g_gi_49ca70[] = { 0x68039c, 0 };
static const DWORD g_gb_49ca70[] = { 0x4d06f4, 0x9f63e4, 0 };
T_PLAIN(match_escMenu, 0x49ca70, gen_setup(g_gs_49ca70, g_gi_49ca70, g_gb_49ca70); /* thiscall on the game */, BUF, g_a[0], g_a[1], g_a[2], g_a[3])
/* the shutdown (wnd_setCursor): the game object 0x9087b4 kept 0 (its deleting destructor would run on the real
   game), the sounds 0x4dd4d4 .., the cursor; callees stubbed. scene_loadPath(path) (thiscall on the scene): the
   path record at +0x2148ed8 loaded once (+0x2148ee0), the path's name looked up (stubbed), its sound */
static const DWORD g_stubShutdown[] = { 0x42eed0, 4, 0x4014c0, 0, 0x457310, 0, 0x467d60, 1, 0x456cd0, 0, 0x467b70, 0, 0 };
static const DWORD g_stubLoadPath[] = { 0x457080, 2, 0x48b430, 2 | CS_POP | CS_THIS, 0x48b440, 1 | CS_POP | CS_THIS, 0 };
T_PLAIN(wnd_setCursor, 0x4314e0, G32(0x9087b4) = 0; fill((void *)0x4dd4d4, 40); fill((void *)0x76d3ec, 4); fill((void *)0x76d430, 4);
   fill((void *)0x67eefc, 4); callee_stubs(g_stubShutdown, 0);, 0, 0, 0, 0, 0)
ST(scene_loadPath, S32(BUF, 0x2149308) = irnd(0, 1); S32(BUF, 0x2148ee0) = irnd(0, 1); fill_str(BUF + 0x100, 30, 'a', 'z');
   callee_stubs(g_stubLoadPath, (DWORD)irnd(0, 1));,
   TC(DWORD, 0x48fd50, char *, char *)(BUF, BUF + 0x100), scene_loadPath(BUF, (DWORD)(BUF + 0x100)))
