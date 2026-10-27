/* batch 205 */
/* the mission-select frame: its flags, page -1..3 and dialog either way; every callee stubbed */
static const DWORD g_stubMission[] = { 0x428c30, 4, 0x441740, 0, 0x447cb0, 0, 0x448140, 0, 0x44aa20, 0, 0x44aa30, 0, 0 };
static void missionframe_setup(void)
{
	callee_stubs(g_stubMission, 0);
	G32(0x9f63b8) = irnd(0, 1); G32(0x9f62f8) = irnd(-1, 3); G32(0x90d1c4) = irnd(0, 1); G32(0x9f6300) = !irnd(0, 3);
	G32(0x9f62e0) = irnd(0, 1); for (int k = 0; k < 4; k++) G32(0x9f6308 + 4 * k) = irnd(0, 640);
}
T_PLAIN(menuState500_missionSelect, 0x44aa40, missionframe_setup();, 0, 0, 0, 0, 0)
/* the main loop's frame: the screen in a match or not, 0x67ef0c, 0x68039c, the match frame's answer; every callee
   stubbed */
static const DWORD g_stubMainLoop[] = { 0x4012c0, 0, 0x41f970, 0, 0x41fa40, 0, 0x420100, 0, 0x445c60, 0, 0x462050, 0 | CS_THIS, 0 };
static void mainloop_setup(void)
{
	callee_stubs(g_stubMainLoop, 0);
	callee_ret(0x462050, irnd(0, 2));
	G32(0x76d3e8) = irnd(0, 2) ? 9999 : 200; G32(0x67ef0c) = irnd(0, 1) ? 9999 : 0; G32(0x68039c) = irnd(0, 1);
	G32(0x9087b4) = (int)BUF;
}
T_PLAIN(main_loop, 0x420280, mainloop_setup();, 0, 0, 0, 0, 0)
/* the ranking panel: the mode 0..11, team game or not, 0..8 ranked players (indexes 0..15), names short, teams
   -1..1, kills / deaths / seconds, flags and emblem switches, the players in use; the team order and team tests
   stubbed with small answers, the drawing stubbed (the text calls too: the patch DLL watches them) */
static const DWORD g_stubRanking[] = { 0x44ad30, 4, 0x44ad60, 4, 0x44ae10, 5, 0x463740, 1 | CS_POP | CS_THIS,
	0x463780, 1 | CS_POP | CS_THIS, 0x4922c0, 3 | CS_POP | CS_THIS, 0x4924d0, 3 | CS_POP | CS_THIS, 0x4950a0, 4,
	0x496820, 3 | CS_POP | CS_THIS, 0 };
static void hudrank_players(void)
{
	for (int p = 0; p < 16; p++) {
		char *r = BUF + 0x1eccb08 + p * 0x8888;
		fill_str(r, 12, 'A', 'Z');
		S32(r, 0x44) = irnd(0, 15); S32(r, 0x4c) = irnd(-5, 99); S32(r, 0x50) = irnd(-5, 99);
		S32(r, 0x64) = irnd(0, 4000); S32(r, 0x74) = irnd(0, 15); S32(r, 0x80) = irnd(-1, 1);
		S32(r, 0x440) = irnd(0, 1); S32(r, 0x444) = irnd(0, 1);
		S32(BUF, 0x179d1f6 + p * 0x47fd2) = irnd(0, 1);
		G32(0x9f9840 + p * 0x410) = irnd(0, 1);
	}
	for (int k = 0; k < 4; k++) S32(BUF, 0x2221fb8 + 4 * k) = irnd(-5, 200);
	S32(BUF, 0x234240d) = irnd(0, 15);
}
static void hudrank_setup(void)
{
	callee_stubs(g_stubRanking, 0);
	callee_ret(0x463780, irnd(0, 3)); callee_ret(0x463740, irnd(0, 1));
	hudrank_players();
	S32(BUF, 0x22e7180) = irnd(0, 11); S32(BUF, 0x22e7184) = irnd(0, 1); S32(BUF, 8) = irnd(0, 1);
	S32(BUF, 0x233c9f0) = irnd(0, 1); S32(BUF, 0x2342976) = irnd(0, 8);
	for (int k = 0; k < 8; k++) S32(BUF, 0x23428f6 + k * 4) = irnd(0, 15);
}
ST(hud_drawRanking, hudrank_setup();, TC(DWORD, 0x494930, char *)(BUF), hud_drawRanking(BUF))
/* the team score box: the screen size, team scores and the three counters; the screen getters, team tests and
   drawing stubbed */
static const DWORD g_stubTeamBox[] = { 0x44ad30, 4, 0x44ae10, 5, 0x463740, 1 | CS_POP | CS_THIS, 0x463780, 1 | CS_POP | CS_THIS,
	0x4685b0, 0, 0x4685c0, 0, 0x46bd00, 4, 0x46bd60, 4, 0 };
static void teambox_setup(void)
{
	callee_stubs(g_stubTeamBox, 0);
	static const int w[] = { 640, 800, 1024, 1366, 1920 }, h[] = { 480, 600, 768, 720, 1080 };
	int k = irnd(0, 4);
	callee_ret(0x4685b0, w[k]); callee_ret(0x4685c0, h[k]);
	callee_ret(0x463780, irnd(0, 3)); callee_ret(0x463740, irnd(0, 2));
	hudrank_players();
	for (int i = 0; i < 3; i++) S32(BUF, 0x234297e + 4 * i) = irnd(-10, 999);
}
ST(hud_496240, teambox_setup();, TC(DWORD, 0x496240, char *)(BUF), hud_496240(BUF))
