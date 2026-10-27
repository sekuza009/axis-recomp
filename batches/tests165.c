/* batch 164 */
/* the mission settings keys: menudisp_setup's state with its own bindings (keys or the wheel only, see batch 162)
   and their latches, the settings state, unlock screen and busy flag */
static void missionkeys_setup(void)
{
	menudisp_setup();
	static const DWORD binds[] = { 0x76d48c, 0x9dae70, 0x4e1510, 0x4e0cdc, 0x9dae14, 0x9db974, 0x6803a8, 0x4df9fc, 0x4df90c };
	static const int keys[] = { 0x01, 0x1c, 0xc8, 0xd0, 0x39, 0x0e, 0x1d, 0x38, 0xfd, 0xfe };
	for (int i = 0; i < 9; i++) {
		int k = keys[irnd(0, 9)];
		G32(binds[i]) = k;
		if (k < 0xfa) G32(0x4d1a98 + 4 * k) = irnd(0, 2) ? 0 : 1;
	}
	G32(0x9f62f8) = irnd(-1, 3);
}
static const DWORD g_stubMissionDraw[] = { 0x449a50, 0, 0 };
static const DWORD g_stubSkirmishDraw[] = { 0x4456b0, 0, 0 };
static const DWORD g_stubLocalAddr[] = { 0x454220, 0, 0 };
T_PLAIN(menu_447c30, 0x447c30, missionkeys_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_447b40, 0x447b40, missionkeys_setup();, 0, 0, 0, 0, 0)
T_PLAIN(menu_447c70, 0x447c70, missionkeys_setup();, 0, 0, 0, 0, 0)
T_PLAIN(missionsel_44aa30, 0x44aa30, callee_stubs(g_stubMissionDraw, 0);, 0, 0, 0, 0, 0)
T_PLAIN(skirmish_445bd0, 0x445bd0, callee_stubs(g_stubSkirmishDraw, 0);, 0, 0, 0, 0, 0)
T_PLAIN(jmp_net_getLocalAddress_4532e0, 0x4532e0, callee_stubs(g_stubLocalAddr, 0);, 0, 0, 0, 0, 0)
