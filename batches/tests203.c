/* batch 202 */
/* the fade at, below or above its limit; both callees stubbed */
static const DWORD g_stubFade[] = { 0x4572b0, 0, 0x420280, 0, 0 };
static void fadestep_setup(void)
{
	callee_stubs(g_stubFade, 0);
	float lim = GF(0x4a93e8); int k = irnd(0, 3);
	GF(0x9da434) = k == 0 ? lim : k == 1 ? lim - 1.0f : lim + (float)irnd(1, 100) / 10.0f;
}
T_PLAIN(FUN_004202d0, 0x4202d0, fadestep_setup();, 0, 0, 0, 0, 0)
/* the match's state -1..6 (four handled by the table), the presenting flag, each state handler stubbed returning
   its own next state 0..5 */
static const DWORD g_stubMatchFrame[] = { 0x468750, 0 | CS_THIS, 0x48b200, 0 | CS_THIS, 0x48a370, 0 | CS_THIS,
	0x487f00, 0 | CS_THIS, 0x4685d0, 0, 0 };
static void matchframe_setup(void)
{
	callee_stubs(g_stubMatchFrame, 0);
	callee_ret(0x468750, irnd(0, 5)); callee_ret(0x48b200, irnd(0, 5)); callee_ret(0x48a370, irnd(0, 5));
	callee_ret(0x487f00, irnd(0, 5));
	S32(BUF, 0x233cc20) = irnd(-1, 6); S32(BUF, 0x233c9e8) = irnd(0, 2);
}
ST(main_462050, matchframe_setup();, TC(DWORD, 0x462050, char *)(BUF), main_462050(BUF))
