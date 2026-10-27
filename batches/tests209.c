/* batch 208 */
/* the player markers: each of the 16 records in play or not, flags, team, frags, screen point (on and off the
   1024 x 768 screen), short names; the local and followed players, the mode flags, texture ids; the texture set's
   table zero (the bind stub records the null object); every drawing callee stubbed (the label goes through the
   patch DLL's label_text / label_halfw when installed) */
static const DWORD g_stubMarkers[] = { 0x44ad30, 4, 0x44ae10, 5, 0x4566c0, 1 | CS_POP | CS_THIS, 0x463740, 1 | CS_POP | CS_THIS,
	0x4685b0, 0, 0x4685c0, 0, 0x4922c0, 3 | CS_POP | CS_THIS, 0x4924d0, 3 | CS_POP | CS_THIS, 0 };
static void markers_setup(void)
{
	callee_stubs(g_stubMarkers, 0);
	callee_ret(0x4685b0, 1024); callee_ret(0x4685c0, 768); callee_ret(0x463740, irnd(0, 2));
	for (int p = 0; p < 16; p++) {
		char *e = BUF + 0x1ed5250 + p * 0x8888;
		S32(e, -0x8694) = irnd(0, 3) ? 1 : irnd(0, 2); S32(e, 0) = irnd(0, 3) ? 1 : 0;
		S32(e, -0x8308) = irnd(0, 1); S32(e, -0x8304) = irnd(0, 1); S32(e, -0x83f4) = irnd(0, 2);
		S32(e, -0x86c8) = irnd(-1, 2); S32(e, -0x8704) = irnd(0, 15); S32(e, -0x86fc) = irnd(-2, 30);
		S32(e, -0x86d4) = irnd(0, 15); fill_str(e - 0x8748, 12, 'A', 'Z');
		SF(e, -0x24) = (float)irnd(-200, 1200); SF(e, -0x14) = (float)irnd(-200, 1000); SF(e, 0x10) = csu_fr(-100, 300);
		S32(BUF, 0x179d1f6 + p * 0x47fd2) = irnd(0, 1);
		S32(BUF, 0x2342936 + p * 4) = irnd(0, 2);
	}
	S32(BUF, 8) = irnd(0, 4); S32(BUF, 0x234240d) = irnd(-1, 15); S32(BUF, 0x2340c64) = irnd(-1, 15);
	S32(BUF, 0x233c9fc) = irnd(0, 2) ? 0 : 1; S32(BUF, 0x22e7184) = irnd(0, 1); S32(BUF, 0x22e719c) = irnd(0, 2) ? 0 : 1;
	S32(BUF, 0x22e71a0) = irnd(0, 2) ? 0 : 1; S32(BUF, 0x233c9f0) = irnd(0, 1); S32(BUF, 0x23424f2) = irnd(-1, 3);
	S32(BUF, 0xbc06a0) = irnd(0, 0x3ff); S32(BUF, 0xbc06ac) = irnd(0, 0x3ff);
	G32(0xa0e010) = (int)(BUF + 0x1000);
}
ST(hud_drawPlayerMarkers, markers_setup();, TC(DWORD, 0x4913a0, char *)(BUF), hud_drawPlayerMarkers(BUF))
/* the match's input: every key binding its own key code (0x10 + its index), one of them held and one pressed (or
   none) through the stubbed key tests; the scene's state flags (mostly clear), the local player and its record, the
   input flags, the mouse offsets small, the cursor and the menu state; the other callees stubbed (the menu step goes
   through the patch DLL's menu_nav when installed) */
static const DWORD g_combatKeys[] = { 0x4deb58, 0x4deb5c, 0x4deb60, 0x4deb64, 0x4deb68, 0x4deb6c, 0x4deb70, 0x4deb78,
	0x4dec8c, 0x4dec90, 0x4def00, 0x4def04, 0x4def08, 0x4def0c, 0x4def10, 0x4def14, 0x4def18, 0x4def1c, 0x4def30, 0x4def34,
	0x4def38, 0x4def3c, 0x4def40, 0x4def44, 0x4def48, 0x4def4c, 0x4def50, 0x4def54, 0x4def58, 0x4def5c, 0x4def60, 0x4def64,
	0x4def68, 0x4def6c, 0x4def70, 0x4def74, 0x4def78, 0x4def7c, 0x4def80, 0x4def84, 0x4def88, 0x4def8c, 0x4def90, 0x4def94,
	0x4def98, 0x4def9c, 0x4defa8, 0x4defac, 0x4defb0, 0x4defb4, 0x4defc8, 0x4defcc, 0x4defe0, 0x4defe4, 0x4deff0, 0x4deff4,
	0x4deff8, 0x4deffc, 0x4df8d0, 0x4e0460, 0x4e0468, 0x4e046c, 0x4e0470, 0x4e0874, 0x4e0c78, 0x4e0c7c, 0x4e0c80, 0x4e0c84,
	0x4e0c88, 0x5b1da8, 0x67ef24, 0x6803a0, 0x76d330, 0x9dae14, 0x9dae70, 0x9db0a0, 0x9db974, 0 };
static const DWORD g_stubCombat[] = { 0x401590, 1, 0x401600, 1, 0x461f10, 0 | CS_THIS, 0x463450, 2, 0x4685b0, 0, 0x4685c0, 0, 0 };
static void combat_setup(void)
{
	callee_stubs(g_stubCombat, 0);
	callee_ret(0x4685b0, 1024); callee_ret(0x4685c0, 768);
	int n = 0;
	for (; g_combatKeys[n]; n++) G32(g_combatKeys[n]) = 0x10 + n;
	callee_key(0x401590, irnd(0, 3) ? 0x10 + irnd(0, n - 1) : -1);
	callee_key(0x401600, irnd(0, 3) ? 0x10 + irnd(0, n - 1) : -1);
	S32(BUF, 0x233c9e8) = irnd(0, 5) ? 1 : 0;
	static const DWORD clr[] = { 0x2340d35, 0x2340cf4, 0x233c9fc, 0x2340cf0, 0x2340ce4, 0x2340ce8, 0x23432cf, 8 };
	for (int i = 0; i < 8; i++) S32(BUF, clr[i]) = irnd(0, 3) ? 0 : irnd(1, 2);
	S32(BUF, 0x234240d) = irnd(0, 15); S32(BUF, 0x1eccb48 + S32(BUF, 0x234240d) * 0x8888) = irnd(0, 2) ? 0 : 1;
	S32(BUF, 0x233cc10) = irnd(0, 3); S32(BUF, 0x2340c68) = irnd(0, 3); S32(BUF, 0x2340c6c) = irnd(-1, 3);
	S32(BUF, 0x23424ee) = irnd(-1, 3); S32(BUF, 0x23424f2) = irnd(-1, 3); SF(BUF, 0x2340d39) = csu_fr(-50, 50);
	for (DWORD o = 0x2343257; o <= 0x234331f; o += 4) S32(BUF, o) = irnd(0, 3) ? 0 : 1;
	SF(BUF, 0x2343293) = csu_fr(-3000, 3000); SF(BUF, 0x2343297) = csu_fr(-3000, 3000);
	/* the cursor's y at the screen's middle (768 / 2): the in-match menu's vertical offset stays 0, since the
	   patch DLL's menu_nav adds it to a total it keeps between calls (reset only after 250 ms of real time), which
	   the original's run would leave for the rebuilt one (8 in 400 tests differed in +0x234330b) */
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = 384; G32(0x4ded88) = irnd(-5, 5); G32(0x4ded8c) = irnd(-5, 5);
	G32(0x4df000) = irnd(0, 3); GF(0x4df008) = csu_fr(-100, 100);
}
ST(match_combatInput, combat_setup();, TC(DWORD, 0x49d290, char *)(BUF), match_combatInput(BUF))
