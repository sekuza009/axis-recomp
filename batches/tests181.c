/* batch 180: generated tests (tools/gentests.py, gen_setup from batch 172) plus two by hand */
static const DWORD g_gs_441740[] = { 0x41ef90, 1, 0x429d70, 1, 0x441260, 1, 0 };
static const DWORD g_gi_441740[] = { 0x67fb3c, 0 };
static const DWORD g_gb_441740[] = { 0 };
T_PLAIN(menu_drawBackground, 0x441740, gen_setup(g_gs_441740, g_gi_441740, g_gb_441740);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_454940[] = { 0x453720, 0, 0x453a30, 1, 0x453a90, 2, 0x4549a0, 0, 0 };
static const DWORD g_gi_454940[] = { 0xa0d7a4, 0 };
static const DWORD g_gb_454940[] = { 0 };
T_PLAIN(arena_454940, 0x454940, gen_setup(g_gs_454940, g_gi_454940, g_gb_454940);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_454a50[] = { 0x453720, 0, 0x453a30, 1, 0x453a90, 2, 0x454ac0, 0, 0 };
static const DWORD g_gi_454a50[] = { 0xa0d7a8, 0 };
static const DWORD g_gb_454a50[] = { 0 };
T_PLAIN(arena_454a50, 0x454a50, gen_setup(g_gs_454a50, g_gi_454a50, g_gb_454a50);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_454b70[] = { 0x453720, 0, 0x453a30, 1, 0x453a90, 2, 0x454bd0, 0, 0 };
static const DWORD g_gi_454b70[] = { 0xa0d7ac, 0 };
static const DWORD g_gb_454b70[] = { 0 };
T_PLAIN(arena_454b70, 0x454b70, gen_setup(g_gs_454b70, g_gi_454b70, g_gb_454b70);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_454c80[] = { 0x453720, 0, 0x453a30, 1, 0x453a90, 2, 0x454ce0, 0, 0 };
static const DWORD g_gi_454c80[] = { 0xa0d7b0, 0 };
static const DWORD g_gb_454c80[] = { 0 };
T_PLAIN(arena_454c80, 0x454c80, gen_setup(g_gs_454c80, g_gi_454c80, g_gb_454c80);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
static const DWORD g_gs_435c20[] = { 0x41e760, 1, 0x432240, 2, 0x433d30, 0, 0x433e60, 1, 0x434640, 0, 0x4346c0, 0, 0 };
static const DWORD g_gi_435c20[] = { 0x4ded68, 0x4ded6c, 0x4ded88, 0x4ded8c, 0 };
static const DWORD g_gb_435c20[] = { 0 };
T_PLAIN(room_435c20, 0x435c20, gen_setup(g_gs_435c20, g_gi_435c20, g_gb_435c20);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
/* match_4620e0 (thiscall on the scene): the 16 player records' scores cleared (and their team slots in team games,
   +8 == 1), then the actor reset (0x45df90 on the actor table +0x1f36c8) and the ranking (msg_newKing), both
   stubbed and thiscall; arena_453090: by connection kind 0xa0b418 (0..3, others) host through that kind's slot
   (8 arguments passed on) */
static const DWORD g_stubResetScores[] = { 0x45df90, 0 | CS_THIS, 0x462150, 0 | CS_THIS, 0 };
static const DWORD g_stubHostKind[] = { 0x4549e0, 8, 0x454b00, 8, 0x454c10, 8, 0x454d20, 8, 0 };
T_PLAIN(match_4620e0, 0x4620e0, for (int i = 0; i < 16; i++) fill(BUF + 0x1eccb40 + i * 0x8888, 0x50); S32(BUF, 8) = irnd(0, 2);
   callee_stubs(g_stubResetScores, 0);, BUF, 0, 0, 0, 0)
ST(arena_453090, G32(0xa0b418) = irnd(0, 9) ? irnd(0, 3) : irnd(-1, 6); for (int i = 0; i < 8; i++) g_a[i] = irnd(-5, 1000);
   callee_stubs(g_stubHostKind, (DWORD)irnd(0, 1));,
   ((DWORD (__cdecl *)(int, int, int, int, int, int, int, int))0x453090)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   arena_453090(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]))
