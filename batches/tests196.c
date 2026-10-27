/* batch 195 */
/* the loading steps: the first call or a later one, any stage 0..9 (9: none), a game mode 0..4, up to 12 lines
   already, the local player 0..3 (0: maybe the host), the players' names and the map file name short strings, a
   map index 0..7 with its name empty now and then; the network receive stubbed to "nothing" (a constant answer
   would loop forever), the host flag, the player count (0x4a8730) and the key tests random; every loader, the
   message box (0x46c710) and the drawing stubbed */
static const DWORD g_stubLoadMode[] = { 0x401600, 1, 0x456be0, 8 | CS_POP | CS_THIS, 0x457310, 0, 0x461ec0, 1 | CS_POP | CS_THIS,
	0x462850, 0 | CS_THIS, 0x4685f0, 2, 0x46bb00, 4, 0x46c710, 2, 0x46cbe0, 4, 0x470ad0, 0 | CS_THIS, 0x470fc0, 4,
	0x471040, 6 | CS_POP | CS_THIS, 0x4732f0, 1 | CS_POP | CS_THIS, 0x474550, 1 | CS_POP | CS_THIS, 0x4841f0, 2 | CS_POP | CS_THIS,
	0x484260, 0 | CS_THIS, 0x485af0, 2 | CS_POP | CS_THIS, 0x4876b0, 1 | CS_POP | CS_THIS, 0x487bd0, 1, 0x48b5c0, 1 | CS_POP | CS_THIS,
	0x48b710, 2 | CS_POP | CS_THIS, 0x48b9d0, 1 | CS_POP | CS_THIS, 0x48c830, 3 | CS_POP | CS_THIS, 0x48dbf0, 1 | CS_POP | CS_THIS,
	0x4a8350, 0, 0x4a8450, 3, 0x4a86d0, 0, 0x4a8730, 0, 0 };
static void loadmode_setup(void)
{
	callee_stubs(g_stubLoadMode, 0);
	callee_ret(0x4a86d0, (DWORD)irnd(0, 1)); callee_ret(0x4a8730, (DWORD)irnd(0x70, 0x90));
	callee_ret(0x487bd0, (DWORD)irnd(0, 1)); callee_ret(0x401600, (DWORD)irnd(0, 1)); callee_ret(0x48b9d0, (DWORD)irnd(0, 1));
	callee_ret(0x456be0, (DWORD)irnd(0, 1000));
	S32(BUF, 0x233cc28) = irnd(0, 2) ? irnd(1, 50) : 0;
	S32(BUF, 0x233cc24) = irnd(0, 9);
	S32(BUF, 0x2340c60) = irnd(0, 12);
	S32(BUF, 8) = irnd(0, 4);
	S32(BUF, 0x234240d) = irnd(0, 3) ? 0 : irnd(1, 3);
	S32(BUF, 0x1f35c0) = irnd(0, 7);
	for (int i = 0; i < 8; i++) fill_str(BUF + 0x1f1cbc + i * 0x40, 12, 'a', 'z');
	fill_str(BUF + 0x1f35c8, 12, 'a', 'z');
	S32(BUF, 0x1f1cb0) = irnd(0, 1); S32(BUF, 0xbe3000) = irnd(0, 7); S32(BUF, 0x233cc20) = irnd(0, 4);
	S32(BUF, 0x1f1664) = irnd(0, 100); S32(BUF, 0x2340c7c) = irnd(0, 100); S32(BUF, 0x2340d08) = irnd(0, 100);
	int map = irnd(0, 7);
	G32(0x9dad94) = map;
	*(char *)(0x907b30 + map * 32) = irnd(0, 4) ? 'm' : 0;
	G32(0x4defc8) = irnd(0, 255); G32(0x4defcc) = irnd(0, 255); G32(0x4df00c) = irnd(0, 9);
	G32(0xa0e010) = irnd(0, 1000); G32(0x76d368) = irnd(0, 15);
}
ST(game_processLoadingMode, loadmode_setup();, TC(DWORD, 0x468750, char *)(BUF), game_processLoadingMode(BUF))
