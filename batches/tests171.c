/* batch 170 */
/* the armour centre's states with their callees stubbed (callee_stubs); the key tests (input_justPressed /
   input_isDown) are stubs too (callee_key: one binding pressed, or none), which also keeps the patch DLL's mouse
   latch in 0x401600 out of the tests; every binding a distinct code; the hit test answers a random button; pages
   -1..5, states -1..4, the rotation toggle, the part kind and position, the mouse, the dialog flag, the camera */
static const DWORD g_armcBinds[] = { 0x4e0cd4, 0x4e0cd8, 0x4e0cdc, 0x4e10e4, 0x4e14ec, 0x4e14f0, 0x4e1504, 0x4e1510,
	0x4e1514, 0x4e151c, 0x4e1524, 0x4e1538, 0x76d330, 0x76d48c, 0x9dae14, 0x9db0a0, 0x9db974, 0x6803a8 };
static const DWORD g_stubArmcMouse[] = { 0x40e450, 2, 0x40f0f0, 1, 0x40f220, 0, 0x40f320, 0, 0x40f340, 0, 0x41e760, 1, 0 };
static const DWORD g_stubArmcMainKeys[] = { 0x401600, 1, 0x40f0f0, 1, 0x40f220, 0, 0x40f320, 0, 0x40f340, 0, 0x41e760, 1, 0 };
static const DWORD g_stubArmcPartKeys[] = { 0x401600, 1, 0x40f0f0, 1, 0x40f200, 0, 0x40f320, 0, 0x40f830, 0, 0x40f870, 1,
	0x40f950, 0, 0x40f9e0, 0, 0x41e760, 1, 0 };
static const DWORD g_stubArmcColourKeys[] = { 0x401600, 1, 0x40f0f0, 1, 0x40f200, 0, 0x40f220, 0, 0x40f590, 0, 0x41e760, 1, 0 };
static const DWORD g_stubArmcState[] = { 0x40fb20, 0, 0x40fd30, 0, 0x40ff40, 0, 0x410160, 0, 0 };
static const DWORD g_stubArmcInput[] = { 0x401590, 1, 0x401600, 1, 0x40d840, 0, 0x4101e0, 0, 0x410500, 0, 0x410810, 0,
	0x433360, 0, 0 };
static void armcstate_setup(const DWORD *stubs)
{
	armcsel_setup();
	for (int i = 0; i < 18; i++) G32(g_armcBinds[i]) = 0x10 + i;
	G32(0x4dc798) = irnd(-1, 5); G32(0x4dc790) = irnd(-1, 4); G32(0x4dceac) = irnd(0, 1); G32(0x4dcfd8) = irnd(0, 3);
	G32(0x4dbc6c) = irnd(0, 3); G32(0x4dc4b0) = irnd(0, 3); g_menuDialogOpen = !irnd(0, 4);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480); g_mouseClick1 = irnd(0, 1); g_mouseClick2 = !irnd(0, 3);
	G32(0x4dc24c) = irnd(0, 4); G32(0x76d410) = irnd(0, 1); G32(0x9da49c) = irnd(0, 2) ? 0x67 : 0x66;
	G32(0x4e0468) = irnd(0, 3); G32(0x4e046c) = irnd(0, 3); G32(0x4e0470) = irnd(0, 3);
	fill((void *)0x4e0874, 4); fill((void *)0x4e0c78, 8);
	static const DWORD fl[] = { 0x4df870, 0x4df874, 0x4df878, 0x76d388, 0x76d38c, 0x76d390, 0x4df024, 0x4df028, 0x4df02c,
		0x680378, 0x68037c, 0x680380, 0x76d3f8, 0x76d3fc, 0x76d400, 0x9db090, 0x9db094, 0x9db098 };
	for (int i = 0; i < 18; i++) GF(fl[i]) = (float)irnd(-2000, 2000) / 10.0f;
	GF(0x4e1870) = (float)irnd(0, 100) / 100.0f;
	callee_stubs(stubs, 0);
	callee_key(0x401600, irnd(0, 2) ? 0x10 + irnd(0, 17) : -1);
	callee_key(0x401590, irnd(0, 1) ? 0x10 + irnd(0, 17) : -1);
	callee_ret(0x40e450, (DWORD)irnd(-1, 12));
}
T_PLAIN(armc_40fb20, 0x40fb20, armcstate_setup(g_stubArmcMouse);, 0, 0, 0, 0, 0)
T_PLAIN(armc_4101e0, 0x4101e0, armcstate_setup(g_stubArmcMainKeys);, 0, 0, 0, 0, 0)
T_PLAIN(armc_410500, 0x410500, armcstate_setup(g_stubArmcPartKeys);, 0, 0, 0, 0, 0)
T_PLAIN(armc_410810, 0x410810, armcstate_setup(g_stubArmcColourKeys);, 0, 0, 0, 0, 0)
T_PLAIN(armc_onStateEnter, 0x410190, armcstate_setup(g_stubArmcState);, 0, 0, 0, 0, 0)
T_PLAIN(armc_processInput, 0x410ab0, armcstate_setup(g_stubArmcInput);, 0, 0, 0, 0, 0)
