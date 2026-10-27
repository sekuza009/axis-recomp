/* batch 212 */
/* the lock-on squares: each of the 16 players in play or not, its lock timer around 0, screen point on and off
   the screen; the local player; the bind and screen size stubbed */
static const DWORD g_stubLockOn[] = { 0x4566c0, 1 | CS_POP | CS_THIS, 0x4685b0, 0, 0x4685c0, 0, 0 };
static void lockon_setup(void)
{
	callee_stubs(g_stubLockOn, 0); callee_ret(0x4685b0, 1024); callee_ret(0x4685c0, 768);
	for (int p = 0; p < 16; p++) {
		char *e = BUF + 0x1ed5250 + p * 0x8888;
		S32(e, -0x8694) = irnd(0, 3) ? 1 : irnd(0, 2); S32(e, 0) = irnd(0, 3) ? 1 : 0;
		SF(e, 0xc) = csu_fr(-100, 300); SF(e, -0x24) = (float)irnd(-200, 1200); SF(e, -0x20) = (float)irnd(-200, 1000);
		SF(BUF, 0x2222148 + p * 4) = csu_fr(-100, 300);
	}
	S32(BUF, 0x234240d) = irnd(-1, 15); S32(BUF, 0xbc06a0) = irnd(0, 0x3ff);
	G32(0xa0e010) = (int)(BUF + 0x1000);
}
ST(hud_drawLockOn, lockon_setup();, TC(DWORD, 0x491f50, char *)(BUF), hud_drawLockOn(BUF))
/* the emblem / transition: title on or off with its counter, the transition state and timers, texture ids, dt;
   the projection, vertex helper and bind stubbed */
static const DWORD g_stubEmblem[] = { 0x41ef60, 2, 0x41ef90, 1, 0x4566c0, 1 | CS_POP | CS_THIS, 0 };
static void transition_setup(void)
{
	callee_stubs(g_stubEmblem, 0);
	G32(0xa0e010) = (int)(BUF + 0x1000);
	for (DWORD a = 0x9dad6c; a <= 0x9dad88; a += 4) G32(a) = irnd(0, 0x7ff);
	G32(0x4df01c) = irnd(0, 1); G32(0x4e0458) = irnd(0, 20); G32(0x76d3f0) = irnd(0, 0x7ff);
	GF(0x4b071c) = csu_fr(0, 200);
	GF(0x4de1d8) = csu_fr(-50, 300); GF(0x4de1e0) = csu_fr(-50, 300); GF(0x4de1e8) = csu_fr(-50, 300);
	if (irnd(0, 1)) G32(0x4de1ec) = irnd(0, 3); else GF(0x4de1ec) = csu_fr(-50, 300);   /* used as int and float */
}
T_PLAIN(menu_titleEmblemTransition, 0x429170, transition_setup();, 0, 0, 0, 0, 0)
/* the FPS counter: any rate; the icon, colour and text stubbed */
static const DWORD g_stubFps[] = { 0x44ad30, 4, 0x44ad60, 4, 0x496820, 3 | CS_POP | CS_THIS, 0 };
static void fps_setup(void) { callee_stubs(g_stubFps, 0); SF(BUF, 0x38) = csu_fr(0, 30000); }
ST(hud_drawFps, fps_setup();, TC(DWORD, 0x495510, char *)(BUF), hud_drawFps(BUF))
/* the chat line: modes -1..3, the blink timer, a typed line of 0..40 characters; the box, colour and text stubbed */
static const DWORD g_stubChatBox[] = { 0x44ad30, 4, 0x44ad60, 4, 0x4950a0, 4, 0 };
static void chatbox_setup(void)
{
	callee_stubs(g_stubChatBox, 0);
	S32(BUF, 0x2340d35) = irnd(-1, 3); SF(BUF, 0x233cc34) = csu_fr(0, 100);
	fill_str((char *)0x9dc92c, 40, 32, 126);
}
ST(hud_4953d0, chatbox_setup();, TC(DWORD, 0x4953d0, char *)(BUF), hud_4953d0(BUF))
/* the replay message box: the fade -1..3 s, the message ring's read / write indexes (equal or not, past 32), its
   entries' text block 0..7 and colour 0..20, the text blocks (four short lines each), the event ring's indexes and
   entries (type 0..6, a short text); the box, colour and text stubbed */
static const DWORD g_stubReplayMsg[] = { 0x44ad30, 4, 0x44ad60, 4, 0x4950a0, 4, 0 };
static void replaymsg_setup(void)
{
	callee_stubs(g_stubReplayMsg, 0);
	SF(BUF, 0x233cc40) = csu_fr(-100, 300);
	int r = irnd(0, 60); S32(BUF, 0x233c59c) = r; S32(BUF, 0x233c598) = r + irnd(-1, 2);
	for (int k = 0; k < 32; k++) { char *m = BUF + 0x233c318 + k * 20; S32(m, 4) = irnd(0, 7); S32(m, 8) = irnd(0, 20); }
	for (int k = 0; k < 8; k++) for (int l = 0; l < 4; l++) fill_str(BUF + 0x22fbbd8 + k * 0x108 + l * 0x41, 30, 32, 126);
	int e = irnd(0, 20); S32(BUF, 0x2342efa) = e; S32(BUF, 0x2342ef6) = e + irnd(0, 6);
	for (int k = 0; k < 5; k++) { char *v = BUF + 0x23429ce + k * 0x108; S32(v, 0) = irnd(0, 6); fill_str(v + 4, 40, 32, 126); }
}
ST(replay_drawMessage, replaymsg_setup();, TC(DWORD, 0x495190, char *)(BUF), replay_drawMessage(BUF))
