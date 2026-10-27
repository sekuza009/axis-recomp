/* batch 203 */
/* WinMain: a running copy found now and then, the language among Korean (both ids) and others, the checks mostly
   passing (each fails one time in eight), 0x76d410 either way, app_init passing or not; the message loop answers by
   random bits with GetMessageA's result and the TranslateMessage flag either way, and its flag is cleared after
   1..40 peeks; every callee stubbed */
static const DWORD g_stubWinMain[] = { 0x401000, 0, 0x41e260, 0, 0x41e550, 0, 0x41e5b0, 0, 0x41e610, 0, 0x41e670, 0,
	0x41e6d0, 0, 0x41edf0, 1, 0x4202d0, 0, 0x43f160, 1, 0x43f300, 0, 0x43f770, 0, 0x43f980, 0, 0x43fcc0, 2, 0 };
static void winmain_setup(void)
{
	callee_stubs(g_stubWinMain, 0);
	static const DWORD chk[] = { 0x401000, 0x41e260, 0x41e550, 0x41e5b0, 0x41e610, 0x41e670, 0x41e6d0, 0x43f770, 0x43fcc0 };
	for (int i = 0; i < 9; i++) callee_ret(chk[i], irnd(0, 7) ? 1 : 0);
	static const DWORD lang[] = { 0x412, 0x812, 0x409, 0x411, 0x407 };
	g_mockFindWnd = irnd(0, 5) ? 0 : 0x20020; g_mockLangId = lang[irnd(0, 4)];
	g_mockPeekBits = (DWORD)irnd(0, 0xffff) | (DWORD)irnd(0, 0xffff) << 16; g_mockPeekQuit = irnd(1, 40);
	g_mockGetMsgRet = irnd(0, 3) ? 1 : 0; g_mockMsgId = irnd(0, 0x400);
	G32(0x76d410) = irnd(0, 1); G32(0x68039c) = irnd(0, 1);
	fill_str(BUF + 0x100, 20, 'a', 'z');
	g_a[0] = 0x400000; g_a[1] = 0; g_a[2] = (int)(BUF + 0x100); g_a[3] = irnd(0, 10);
}
ST(game_WinMain, winmain_setup();, ((DWORD (WINAPI *)(DWORD, DWORD, DWORD, DWORD))0x43f9d0)(g_a[0], g_a[1], g_a[2], g_a[3]),
	game_WinMain(g_a[0], g_a[1], g_a[2], g_a[3]))
