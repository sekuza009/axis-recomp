/* batch 206 */
/* the scene's frame timer (armc_461210 on the scene: the timer at +0xc, the ring +0x48, index +0x70, dt into +0x44) */
static void scenetimer_setup(void)
{
	S32(BUF, 0x10) = irnd(0, 1); S32(BUF, 0x70) = irnd(0, 9);
	for (int i = 0; i < 10; i++) SF(BUF, 0x48 + i * 4) = csu_fr(0, 100);
	SF(BUF, 0x40) = irnd(0, 2) ? csu_fr(1, 10) : csu_fr(-5, 0);
	S32(BUF, 0x1c) = irnd(0, 1); S32(BUF, 0x24) = irnd(0, 1); S32(BUF, 0x34) = irnd(0, 1);
	qpf_setup(); g_mockQpc = (DWORD)irnd(0, 0x7fffffff);
}
/* the match frame: the round flag, the timer, clocks, counters, countdowns around 0, the state 0..3, a pending quit;
   the round start, quit and the three frame parts stubbed (the HUD pass through the patch DLL's wrapper when it is
   installed) */
static const DWORD g_stubMatchState2[] = { 0x457310, 0, 0x4982f0, 0 | CS_THIS, 0x4988e0, 0 | CS_THIS, 0x49d290, 0 | CS_THIS,
	0x49df10, 0, 0 };
static void matchstate2_setup(void)
{
	callee_stubs(g_stubMatchState2, 0);
	scenetimer_setup();
	S32(BUF, 0x233cc28) = irnd(0, 1); SF(BUF, 0x233cc34) = csu_fr(0, 150); S32(BUF, 0x233cc30) = irnd(0, 1000);
	SF(BUF, 0x2340c90) = csu_fr(0, 150); S32(BUF, 0x2340c80) = irnd(0, 5000); S32(BUF, 0x2340c84) = irnd(0, 5000);
	SF(BUF, 0x233cc40) = csu_fr(-50, 300); SF(BUF, 0x2342f02) = csu_fr(-50, 300); SF(BUF, 0x2340d39) = csu_fr(-50, 300);
	S32(BUF, 0x233cc20) = irnd(0, 3); S32(BUF, 0x23432cf) = !irnd(0, 4);
}
ST(match_inputState2, matchstate2_setup();, TC(DWORD, 0x48b200, char *)(BUF), match_inputState2(BUF))
/* the menus' frame: the screen among its handlers, 9999 and others, the music screen, the key block, the launch fade
   near its ends, the dialog and pointer flags, the brightness mode and value, the FPS switch and frame counts; the
   timer real (mocked counter); every handler and drawing call stubbed */
static const DWORD g_stubMenuFrame[] = { 0x40d450, 0, 0x41e040, 0, 0x41f540, 0, 0x41f820, 0, 0x41f8d0, 0, 0x41f970, 0,
	0x427920, 0, 0x428940, 2, 0x4290d0, 0, 0x429bc0, 0, 0x4319d0, 0, 0x43ef70, 0, 0x443530, 0, 0x445be0, 0, 0x445e40, 0,
	0x44aa40, 0, 0x44f860, 0, 0 };
static void menuframe_setup(void)
{
	callee_stubs(g_stubMenuFrame, 0);
	static const int scr[] = { 100, 200, 210, 300, 400, 500, 600, 700, 800, 900, 9999, 0, 250 };
	G32(0x76d3e8) = scr[irnd(0, 12)]; G32(0x67ef0c) = irnd(0, 1) ? G32(0x76d3e8) : 0;
	G32(0x9da49c) = 0x67 + irnd(0, 3); G32(0x9db994) = irnd(0, 1); G32(0x4df900) = !irnd(0, 3);
	GF(0x4dda44) = csu_fr(0, 12000); GF(0x4e1870) = csu_fr(-10, 200); GF(0x4df02c) = csu_fr(0, 100000);
	GF(0x4dda48) = csu_fr(0, 1000); GF(0x4b071c) = csu_fr(0, 100);
	G32(0x68039c) = irnd(0, 1); G32(0x9da3d8) = irnd(0, 640); G32(0x9da3dc) = irnd(0, 480); G32(0x9f6838) = irnd(0, 1);
	G32(0x4e0464) = irnd(0, 3); GF(0x68038c) = csu_fr(-100, 300); G32(0x83a9d4) = irnd(0, 1); G32(0x4dd0b0) = irnd(0, 200);
	qpf_setup(); g_mockQpc = (DWORD)irnd(0, 0x7fffffff);
	double t = (double)irnd(0, 100000) / 10.0;
	*(double *)0x4dd0a0 = t - (double)irnd(0, 30) / 10.0; *(double *)0x4dd0c8 = t - (double)irnd(1, 500) / 1000.0;
}
T_PLAIN(menu_frame, 0x41fa40, menuframe_setup();, 0, 0, 0, 0, 0)
/* the scene's constructor: every constructor and loader stubbed (the CRT's vector constructor too), the parts'
   loads passing or not; the chat macro file missing or 0..40 lines of 0..80 characters */
static const DWORD g_stubSceneCtor[] = { 0x401290, 4 | CS_POP, 0x45dfb0, 1 | CS_POP | CS_THIS, 0x4617f0, 0 | CS_THIS,
	0x462560, 0 | CS_THIS, 0x462cf0, 0 | CS_THIS, 0x463790, 0 | CS_THIS, 0x4637f0, 0 | CS_THIS, 0x466a20, 0 | CS_THIS,
	0x46ae70, 0 | CS_THIS, 0x46c710, 2, 0x4700a0, 9 | CS_POP | CS_THIS, 0x473780, 1 | CS_POP | CS_THIS, 0x483d60, 0 | CS_THIS,
	0x483fc0, 0 | CS_THIS, 0x484050, 8 | CS_POP | CS_THIS, 0x487430, 0 | CS_THIS, 0x487480, 0 | CS_THIS,
	0x4875d0, 1 | CS_POP | CS_THIS, 0x49fd2d, 5 | CS_POP, 0 };
static char g_chatFile[4096];
static void scenector_setup(void)
{
	callee_stubs(g_stubSceneCtor, 0);
	callee_ret(0x473780, irnd(0, 3) ? 1 : 0); callee_ret(0x4875d0, irnd(0, 3) ? 1 : 0);
	int n = irnd(0, 40), len = 0;
	for (int i = 0; i < n && len < (int)sizeof g_chatFile - 100; i++) {
		int k = irnd(0, 80);
		for (int j = 0; j < k; j++) g_chatFile[len++] = (char)irnd(32, 126);
		if (irnd(0, 1)) g_chatFile[len++] = '\r';
		g_chatFile[len++] = '\n';
	}
	g_vfsData = g_chatFile; g_vfsSize = len; g_vfsOpenFail = !irnd(0, 5);
}
ST(game_loadAllData, scenector_setup();, TC(DWORD, 0x460570, char *)(BUF), game_loadAllData(BUF))
/* the in-match 2D pass: the scene's flags and modes (mostly 0: several overlays need four of them clear), the local and followed players (-1..15) with their records'
   states, the fog colour, countdowns, the FPS switch; every part and overlay stubbed (the five wrapped calls go
   through the patch DLL's wrappers when installed, to the same stubs) */
static const DWORD g_stubHudPass[] = { 0x44ad30, 4, 0x44ad60, 4, 0x456b50, 0, 0x45e170, 2 | CS_POP | CS_THIS, 0x4685b0, 0,
	0x4685c0, 0, 0x4685f0, 2, 0x472900, 4 | CS_POP | CS_THIS, 0x479af0, 1 | CS_POP | CS_THIS, 0x47d060, 1 | CS_POP | CS_THIS,
	0x4841d0, 0 | CS_THIS, 0x4841f0, 2 | CS_POP | CS_THIS, 0x484260, 0 | CS_THIS, 0x485af0, 2 | CS_POP | CS_THIS,
	0x48f970, 1 | CS_POP | CS_THIS, 0x48fde0, 4 | CS_POP, 0x490da0, 1 | CS_POP | CS_THIS, 0x4913a0, 0 | CS_THIS,
	0x491f50, 0 | CS_THIS, 0x4926f0, 0 | CS_THIS, 0x494930, 0 | CS_THIS, 0x495140, 0 | CS_THIS, 0x495190, 0 | CS_THIS,
	0x4953d0, 0 | CS_THIS, 0x495510, 0 | CS_THIS, 0x4955a0, 0 | CS_THIS, 0x495610, 0 | CS_THIS, 0x496240, 0 | CS_THIS,
	0x496610, 0 | CS_THIS, 0x496820, 3 | CS_POP | CS_THIS, 0x496a30, 0 | CS_THIS, 0x496b80, 0 | CS_THIS, 0x496c20, 0 | CS_THIS,
	0x496d10, 0 | CS_THIS, 0x496f20, 1 | CS_POP | CS_THIS, 0x497d20, 2 | CS_POP | CS_THIS, 0 };
static void hudpass_setup(void)
{
	callee_stubs(g_stubHudPass, 0);
	callee_ret(0x4685b0, 1024); callee_ret(0x4685c0, 768);
	static const DWORD flags[] = { 0x233c9e8, 0x233c9d0, 0x233c9fc, 0x23424f2, 0x233cc10, 0xbe170c, 0x2340ce4, 0x2342399,
		0x23423a1, 0x2340cf4, 0x2340cec, 0x234328f, 0x2340d04, 0x2340d35, 0x2340ce8, 0x22e7184, 0x2340d1d, 0xbe16f8 };
	for (unsigned i = 0; i < sizeof flags / sizeof flags[0]; i++) S32(BUF, flags[i]) = irnd(0, 2) ? 0 : irnd(-1, 2);
	S32(BUF, 0x23424f2) = irnd(-12, 3);
	S32(BUF, 0x234240d) = irnd(-1, 15); S32(BUF, 0x2340c64) = irnd(-1, 15); S32(BUF, 0x23428f6) = irnd(0, 15);
	S32(BUF, 0x234243e) = irnd(-1, 15); S32(BUF, 0x1f1664) = irnd(0, 3);
	for (int p = 0; p < 16; p++) S32(BUF, 0x1eccbbc + p * 0x8888) = irnd(0, 2);
	for (int k = 0; k < 3; k++) SF(BUF, 0xbe16fc + 4 * k) = csu_fr(0, 100);
	SF(BUF, 0x22f040c) = csu_fr(0, 100); SF(BUF, 0x233cc40) = csu_fr(-50, 50); SF(BUF, 0x2342f02) = csu_fr(-50, 50);
	SF(BUF, 0x233cc4c) = csu_fr(-50, 50);
	G32(0xa0e010) = (int)(BUF + 0x1000); G32(0x83a9d4) = irnd(0, 1);
}
ST(hud_pass, hudpass_setup();, TC(DWORD, 0x4982f0, char *)(BUF), hud_pass(BUF))
