/* batch 169 */
/* the armour centre's part selection with every heavy callee stubbed (callee_stubs: the scene / actor ones are
   thiscall: CS_THIS records the object, CS_POP pops as they do): kinds -1..6, positions inside and outside the
   lists, list counts 0..20 with random part ids, the choices, the exit mode and flags */
static const DWORD g_stubArmcView[] = { 0x41cca0, 1, 0x419000, 1, 0x461540, 1 | CS_POP | CS_THIS, 0x41c510, 0, 0 };
static const DWORD g_stubArmcKind[] = { 0x45e880, 2 | CS_POP | CS_THIS, 0x40f950, 0, 0 };
static const DWORD g_stubArmcTake[] = { 0x41ca50, 2, 0x419000, 1, 0x461250, 14 | CS_POP | CS_THIS, 0x40f870, 1, 0 };
static const DWORD g_stubArmcScreen[] = { 0x41ca50, 2, 0x41cca0, 1, 0x419000, 1, 0x40f870, 1, 0x41b300, 0, 0 };
static const DWORD g_stubArmcExit[] = { 0x40e670, 0, 0x40e930, 0, 0x40e7a0, 0, 0x41e760, 1, 0x457150, 1, 0 };
static void armcsel_setup(void)
{
	G32(0x4dbe48) = irnd(-1, 6);
	G32(0x4dc244) = irnd(0, 20); G32(0x4dc778) = irnd(0, 20);
	for (int i = 0; i < 20; i++) { G32(0x4dc79c + 4 * i) = irnd(0, 40); G32(0x4dcca4 + 4 * i) = irnd(0, 40); }
	G32(0x4dc77c) = irnd(0, 3) ? irnd(0, 19) : irnd(-3, 25);
	for (DWORD a = 0x4dcb18; a <= 0x4dcb2c; a += 4) G32(a) = irnd(0, 40);
	fill((void *)0x4dc760, 0x14); fill((void *)0x9f1818, 4); fill((void *)0x9087b4, 4);
	G32(0x4dc24c) = irnd(0, 4); G32(0x76d410) = irnd(0, 1); G32(0x9da49c) = irnd(0, 2) ? 0x66 : irnd(0x60, 0x70);
	g_a[0] = irnd(-1, 7); g_a[1] = irnd(0, 1);
}
T_PLAIN(armc_40f950, 0x40f950, armcsel_setup(); callee_stubs(g_stubArmcView, 0);, 0, 0, 0, 0, 0)
T_PLAIN(armc_40f870, 0x40f870, armcsel_setup(); callee_stubs(g_stubArmcKind, 0);, 0, g_a[0], 0, 0, 0)
T_PLAIN(armc_40f9e0, 0x40f9e0, armcsel_setup(); callee_stubs(g_stubArmcTake, 0);, 0, 0, 0, 0, 0)
T_PLAIN(armc_drawPartScreen, 0x40f220, armcsel_setup(); callee_stubs(g_stubArmcScreen, 0);, 0, 0, 0, 0, 0)
T_PLAIN(armc_exit, 0x40f0f0, armcsel_setup(); callee_stubs(g_stubArmcExit, 0);, 0, g_a[1], 0, 0, 0)
