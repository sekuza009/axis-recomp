/* batch 171 */
/* small functions with every callee stubbed (callee_stubs, the key test in key mode over the bindings' codes, the
   others answering 0 / a random value); their flags random, counts small, DirectInput a fake object or none */
static const DWORD g_stubConnUp[] = { 0x4509e0, 0, 0x453790, 0, 0x453920, 0, 0 };
static const DWORD g_stubInputOff[] = { 0x401460, 0, 0x401490, 0, 0 };
static const DWORD g_stubJoin[] = { 0x453e60, 4, 0 };
static const DWORD g_stubHost[] = { 0x453cf0, 8, 0 };
static const DWORD g_stubSound[] = { 0x41e760, 1, 0 };
static const DWORD g_stubKeyClose[] = { 0x401600, 1, 0x41e7a0, 1, 0 };
static const DWORD g_stubKeyClose2[] = { 0x401600, 1, 0x41e760, 1, 0 };
static const DWORD g_stubTypeOn[] = { 0x401460, 0, 0x431560, 1, 0x43f460, 1, 0 };
static const DWORD g_stubTypeOff[] = { 0x401310, 1, 0x431590, 0, 0 };
static const DWORD g_stubRoomClose[] = { 0x41e760, 1, 0x432280, 2, 0 };
static void small_setup(const DWORD *stubs)
{
	G32(0x4e0cdc) = 0x21; G32(0x4e1510) = 0x22;
	G32(0x907b2c) = irnd(0, 1); G32(0x9dd850) = irnd(0, 1); G32(0x9dd6c4) = irnd(0, 1); g_menuDialogOpen = !irnd(0, 3);
	G32(0xa0d7a4) = irnd(0, 1); G32(0xa0d7a8) = irnd(0, 1);
	G32(0x4d1e98) = irnd(0, 2) ? (int)fakecom_new(0, 0x30, g_nargsDinput, 0) : 0;
	G32(0x67ef00) = irnd(-1, 16); fill((void *)0x4d7350, 0x100); fill((void *)0x4d7408, 0x14);
	G32(0x9dd928) = irnd(-1, 10);
	for (int i = 0; i < 10; i++) G32(0x9ddac8 + 0x44 * i) = irnd(0, 3) ? 0 : 1;
	fill((void *)0x9eeab4, 8); fill((void *)0x9db994, 4);
	fill((void *)0x9f63e4, 0x400); fill_str((char *)0x9dc92c, irnd(0, 1) ? 0 : 40, 32, 126);
	fill((void *)0x9f67e8, 4); fill((void *)0x68039c, 4); fill((void *)0x9f63c4, 8);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480); g_mouseClick1 = irnd(0, 1);
	for (int i = 0; i < 8; i++) g_a[i] = irnd(0, 3) ? irnd(0, 600) : irnd(-5, 0x7fff);
	callee_stubs(stubs, (DWORD)irnd(0, 1));
	callee_key(0x401600, irnd(0, 2) ? 0x21 + irnd(0, 1) : -1);
	callee_ret(0x432280, (DWORD)irnd(-1, 2));
}
T_PLAIN(arena_453770, 0x453770, small_setup(g_stubConnUp);, 0, 0, 0, 0, 0)
T_PLAIN(wnd_4014c0, 0x4014c0, small_setup(g_stubInputOff);, 0, 0, 0, 0, 0)
ST(arena_4549e0, small_setup(g_stubHost);,
   ((DWORD (__cdecl *)(int, int, int, int, int, int, int, int))0x4549e0)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   arena_4549e0(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]))
ST(arena_454b00, small_setup(g_stubHost);,
   ((DWORD (__cdecl *)(int, int, int, int, int, int, int, int))0x454b00)(g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   arena_454b00(0, 0, 0, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]))
T_PLAIN(arena_454a20, 0x454a20, small_setup(g_stubJoin);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(arena_454b40, 0x454b40, small_setup(g_stubJoin);, 0, g_a[0], g_a[1], g_a[2], g_a[3])
T_PLAIN(room_403530, 0x403530, small_setup(g_stubSound);, 0, 0, 0, 0, 0)
T_PLAIN(room_4034e0, 0x4034e0, small_setup(g_stubSound);, 0, 0, 0, 0, 0)
T_PLAIN(lobbyJoin_keys, 0x407970, small_setup(g_stubKeyClose);, 0, 0, 0, 0, 0)
T_PLAIN(menu_436940, 0x436940, small_setup(g_stubKeyClose);, 0, 0, 0, 0, 0)
T_PLAIN(lobby_keysBack, 0x4080c0, small_setup(g_stubKeyClose);, 0, 0, 0, 0, 0)
T_PLAIN(menu_4370e0, 0x4370e0, small_setup(g_stubKeyClose2);, 0, 0, 0, 0, 0)
T_PLAIN(match_44ac90, 0x44ac90, small_setup(g_stubTypeOn);, 0, g_a[0], g_a[1], g_a[2], 0)
T_PLAIN(match_44ace0, 0x44ace0, small_setup(g_stubTypeOff);, 0, 0, 0, 0, 0)
T_PLAIN(mainmenu_441770, 0x441770, small_setup(g_stubSound);, 0, 0, 0, 0, 0)
T_PLAIN(room_435ce0, 0x435ce0, small_setup(g_stubRoomClose);, 0, 0, 0, 0, 0)
