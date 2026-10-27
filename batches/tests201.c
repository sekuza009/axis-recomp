/* batch 200 */
/* the actors' frame loop: 0..16 actors in use or not, paused or not, the clock's seconds and fraction, dt up to
   1.5 s (the fraction passes 1 now and then); the actor frame and the triggers stubbed */
static const DWORD g_stubActorLoop[] = { 0x4580b0, 2 | CS_POP | CS_THIS, 0x483640, 0 | CS_THIS, 0 };
static void actorloop_setup(void)
{
	callee_stubs(g_stubActorLoop, 0);
	int n = irnd(0, 16);
	S32(BUF, 0x202e8c8) = n;
	for (int i = 0; i < 16; i++) S32(BUF, 0x1cd94b0 + i * 0x8888) = irnd(0, 2);
	S32(BUF, 0x2149308) = irnd(0, 1); S32(BUF, 0x214930c) = irnd(0, 2);
	S32(BUF, 0x20fcd40) = irnd(0, 1000); GF(BUF + 0x20fcd44) = (float)irnd(0, 999) / 1000.0f;
	GF(&g_a[0]) = (float)irnd(0, 1500) / 1000.0f;
}
ST(actor_updateAll, actorloop_setup();, (TC(void, 0x45e0c0, char *, int)(BUF, g_a[0]), 0), (actor_updateAll(BUF, (DWORD)g_a[0]), 0))
/* the test mode: the first frame or a later one, one key down / pressed (or none) through the key stubs, the local
   player 0..15 with its actor 0..15, a weapon slot 0..5 and its settings within the table sizes 1..8, the camera
   0..9 with its views, replaying or not, the marker grid on or off; every drawing / scene call stubbed */
static const DWORD g_stubInState3[] = { 0x45e0c0, 1 | CS_POP | CS_THIS, 0x45e170, 2 | CS_POP | CS_THIS, 0x45e880, 2 | CS_POP | CS_THIS,
	0x45eb20, 13 | CS_POP | CS_THIS, 0x4685f0, 2, 0x4729b0, 9 | CS_POP | CS_THIS, 0x473b10, 2 | CS_POP | CS_THIS,
	0x473c20, 2 | CS_POP | CS_THIS, 0x473d30, 2 | CS_POP | CS_THIS, 0x473e40, 2 | CS_POP | CS_THIS, 0x473f50, 2 | CS_POP | CS_THIS,
	0x474060, 3 | CS_POP | CS_THIS, 0x479a90, 1 | CS_POP | CS_THIS, 0x479af0, 1 | CS_POP | CS_THIS, 0x47d000, 1 | CS_POP | CS_THIS,
	0x47d060, 1 | CS_POP | CS_THIS, 0x4841f0, 2 | CS_POP | CS_THIS, 0x484260, 0 | CS_THIS, 0x485120, 4 | CS_POP | CS_THIS,
	0x485af0, 2 | CS_POP | CS_THIS, 0x487ba0, 1, 0x487bd0, 1, 0x487c80, 1, 0 };
static void instate3_setup(void)
{
	callee_stubs(g_stubInState3, 0);
	static const int keys[] = { 0x10, 0x11, 0x1b, 0x20, 0x25, 0x26, 0x27, 0x28, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x41, 0x44,
		0x45, 0x51, 0x53, 0x57, 0x58, 0x5a, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 1 };
	/* one key held (0x487ba0) and one pressed (0x487bd0), chosen apart: the setting cycles need F1..F6 held with Z / X pressed */
	int held = irnd(0, 4) ? keys[irnd(0, 28)] : -1, pressed = irnd(0, 3) ? keys[irnd(0, 28)] : -1;
	if (!irnd(0, 2)) { held = 0x70 + irnd(0, 5); pressed = irnd(0, 1) ? 0x5a : 0x58; }
	callee_key(0x487ba0, held); callee_key(0x487bd0, pressed);
	S32(BUF, 0x233cc28) = irnd(0, 3) ? irnd(1, 100) : 0;
	int pl = irnd(0, 15), ac = irnd(0, 15);
	S32(BUF, 0x234240d) = pl;
	char *p = BUF + 0x1ecca70 + pl * 0x888, *a = BUF + 0x1755230 + ac * 0x47fd2;
	S32(p, 0x10c) = ac; S32(p, 0x140) = irnd(0, 5);
	for (int k = 0; k < 4; k++) S32(p, 0x28 + 4 * k) = irnd(0, 400);
	static const DWORD cnt[] = { 0x15de6c8, 0x15fff84, 0x163b588, 0x1679b34, 0x16c5178, 0x175522c };
	for (int k = 0; k < 6; k++) S32(BUF, cnt[k]) = irnd(1, 8);
	for (int k = 0; k < 5; k++) S32(a, 0x30c + 4 * k) = irnd(0, 8);
	for (int k = 0; k < 6; k++) S32(a, 0x320 + 4 * k) = irnd(0, S32(BUF, 0x175522c));
	for (int k = 0; k < 8; k++) S32(BUF, 0x16c7f38 + k * 0x2e18) = irnd(0, 1);
	S32(BUF, 0x233cc10) = irnd(0, 9);
	for (int k = 0; k < 10; k++) {
		GF(BUF + 0x233ca30 + 4 * k) = (float)irnd(-900, 900); GF(BUF + 0x233ca58 + 4 * k) = (float)irnd(0, 3600) / 10.0f;
		GF(BUF + 0x233ca80 + 4 * k) = (float)irnd(1, 20000) / 10.0f;
		S32(BUF, 0x233caa8 + 4 * k) = irnd(0, 1); S32(BUF, 0x233cad0 + 4 * k) = irnd(0, 1); S32(BUF, 0x233caf8 + 4 * k) = irnd(0, 1);
	}
	GF(BUF + 0x233ca28) = (float)irnd(-900, 900); GF(BUF + 0x233ca2c) = (float)irnd(-3600, 3600) / 10.0f;
	GF(BUF + 0x44) = (float)irnd(1, 100) / 1000.0f;
	S32(BUF, 0x2340ce0) = irnd(0, 1); S32(BUF, 0x2340cd0) = irnd(0, 5) ? 0 : 1; S32(BUF, 0x1f1664) = irnd(0, 100);
}
ST(match_inputState3, instate3_setup();, TC(DWORD, 0x48a370, char *)(BUF), match_inputState3(BUF))
