/* batch 199 */
/* a script: trigger 0..7 pointing at 1..4 entries of 0..8 commands (at BUF + 0x2390000, past the scene's fields),
   each a type 0..0x21 (0x20 / 0x21: none) with arguments kept where the game's scripts keep them: trigger indexes
   0..63, player / actor indexes 0..15, object kinds 0..31, the names short and terminated; the acting actor -1..15
   (its +0x10c player 0..15, +0x8820 -1..1); the scene's path strings short; all handlers stubbed */
static const DWORD g_stubScript[] = { 0x457080, 2, 0x45dca0, 1 | CS_POP | CS_THIS, 0x45de20, 2 | CS_POP | CS_THIS,
	0x45dff0, 3 | CS_POP | CS_THIS, 0x45e880, 2 | CS_POP | CS_THIS, 0x46c710, 3, 0x483ce0, 1 | CS_POP | CS_THIS,
	0x48fc40, 4 | CS_POP | CS_THIS, 0x48fce0, 2 | CS_POP | CS_THIS, 0x490df0, 4 | CS_POP | CS_THIS,
	0x490ee0, 1 | CS_POP | CS_THIS, 0x490f30, 1 | CS_POP | CS_THIS, 0 };
static void script_setup(void)
{
	callee_stubs(g_stubScript, 0);
	char *sd = BUF + 0x2390000;
	int trig = irnd(0, 7), nent = irnd(1, 4);
	S32(BUF, 0xe3b03c + trig * 28) = (int)sd;
	for (int e = 0; e < nent; e++) {
		char *en = sd + e * 20, *cmds = sd + 0x100 + e * 0x400;
		int n = irnd(0, 8);
		S32(en, 0xc) = n; S32(en, 0x10) = (int)cmds;
		for (int c = 0; c < n; c++) {
			char *cm = cmds + c * 0x30;
			int ty = irnd(0, 0x21);
			S32(cm, 0) = ty;
			for (int k = 4; k < 0x30; k += 4) S32(cm, k) = irnd(-1, 15);
			switch (ty) {
			case 0: case 1: case 2: S32(cm, 4) = irnd(0, 63); break;
			case 13: GF(cm + 4) = (float)irnd(0, 1000) / 10.0f; break;
			case 15: case 16: case 22: case 23: S32(cm, 4) = irnd(0, 15); break;
			case 26: S32(cm, 4) = irnd(0, 31); S32(cm, 8) = irnd(0, 31); break;
			case 27: case 29: fill_str(cm + 4, 0x1b, 'a', 'z'); break;
			case 28: fill_str(cm + 8, 0x1b, 'a', 'z'); break;
			}
		}
	}
	for (int i = 0; i < 16; i++) {
		char *a = BUF + 0x1cd93a8 + i * 0x8888;
		S32(a, 0x10c) = irnd(0, 15); S32(a, 0x8820) = irnd(-1, 1); S32(a, 0x68) = irnd(0, 100);
	}
	for (int p = 0; p < 16; p++) for (int k = 0; k < 6; k++) S32(BUF, 0x1561e88 + p * 0x47fd2 + 4 * k) = irnd(0, 3);
	for (int k = 0; k < 32; k++) { S32(BUF, 0x2104fe8 + k * 0x88) = irnd(0, 1); S32(BUF, 0x210850c + k * 0x108) = irnd(0, 1); }
	fill_str(BUF + 8, 12, 'a', 'z'); fill_str(BUF + 0x808, 12, 'a', 'z'); fill_str(BUF + 0x908, 12, 'a', 'z');
	g_a[0] = irnd(-1, 15); g_a[1] = trig; g_a[2] = irnd(0, nent - 1);
}
ST(script_processCommandBy, script_setup();, (TC(void, 0x483770, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
	(script_processCommandBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
/* the triggers: 0..24 records, armed or not, flags 0..3, times around the game time, points and radii near the
   player's actor (-1..15) or not, some fired already; the script run stubbed */
static const DWORD g_stubTriggers[] = { 0x483770, 3 | CS_POP | CS_THIS, 0 };
static void scrtrig_setup(void)
{
	callee_stubs(g_stubTriggers, 0);
	int n = irnd(0, 24), pl = irnd(-1, 15);
	S32(BUF, 0xe3c938) = n; S32(BUF, 0x202e8d4) = pl;
	S32(BUF, 0x20fcd40) = irnd(0, 100); GF(BUF + 0x20fcd44) = (float)irnd(0, 100) / 100.0f;
	for (int i = 0; i < 16; i++) for (int k = 0; k < 3; k++) GF(BUF + 0x1cd94fc + i * 0x8888 + 4 * k) = (float)irnd(-200, 200) / 10.0f;
	for (int i = 0; i < n; i++) {
		char *r = BUF + 0xe3b03c + i * 28, *pt = BUF + 0x2390000 + i * 0x40;
		for (int k = 0; k < 3; k++) GF(pt + 4 * k) = (float)irnd(-200, 200) / 10.0f;
		S32(r, 0) = (int)pt; S32(r, 4) = irnd(0, 3) ? 1 : 0; S32(r, 8) = irnd(0, 3);
		GF(r + 0xc) = (float)irnd(0, 1000) / 10.0f; GF(r + 0x10) = (float)irnd(0, 4000) / 10.0f; S32(r, 0x14) = irnd(0, 3) ? 0 : 1;
	}
}
ST(script_processTriggers, scrtrig_setup();, (TC(void, 0x483640, char *)(BUF), 0), (script_processTriggers(BUF), 0))
