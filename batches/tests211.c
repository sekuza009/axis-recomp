/* batch 210 */
/* the game mode's frame: every scene field the function reads given a value by its use (floats -50..50, ints 0..3),
   the 16 player records' fields 0..3 (names short), the globals it reads 0..3; every callee stubbed except the
   four that return in ST0 (Vec3_normalize, the 0x4c4dec.. float getters); the log file mocked */
static const DWORD g_stubGameMode[] = {
	0x447010, 0, 0x44ac90, 3, 0x44ace0, 0, 0x456e50, 0, 0x457310, 0, 0x45dd80, 4 | CS_POP | CS_THIS, 0x45de20, 2 |
	CS_POP | CS_THIS, 0x45df90, 0, 0x45dfb0, 1 | CS_POP | CS_THIS, 0x45e0c0, 1 | CS_POP | CS_THIS, 0x45e1c0, 0,
	0x45eb20, 13 | CS_POP | CS_THIS, 0x45ee40, 1 | CS_POP | CS_THIS, 0x4613a0, 1 | CS_POP | CS_THIS, 0x4616e0, 0,
	0x461730, 0, 0x4620e0, 0, 0x462150, 0, 0x4625a0, 0, 0x462650, 2 | CS_POP | CS_THIS, 0x462740, 2 | CS_POP | CS_THIS,
	0x462850, 0, 0x4629c0, 1 | CS_POP | CS_THIS, 0x462ac0, 1 | CS_POP | CS_THIS, 0x462b50, 1 | CS_POP | CS_THIS,
	0x462c30, 3 | CS_POP | CS_THIS, 0x462d30, 2 | CS_POP | CS_THIS, 0x462f30, 0, 0x462f60, 0, 0x462f90, 0, 0x462fd0, 0,
	0x463030, 2 | CS_POP | CS_THIS, 0x4630c0, 2 | CS_POP | CS_THIS, 0x463390, 0, 0x4633c0, 0, 0x4633f0, 0, 0x463450, 1,
	0x463480, 0, 0x4634e0, 2 | CS_POP | CS_THIS, 0x463530, 1 | CS_POP | CS_THIS, 0x463550, 3 | CS_POP | CS_THIS,
	0x4635b0, 3 | CS_POP | CS_THIS, 0x463670, 0, 0x463690, 0, 0x4636b0, 0, 0x4636d0, 0, 0x463710, 1 | CS_POP | CS_THIS,
	0x463740, 1 | CS_POP | CS_THIS, 0x463780, 1 | CS_POP | CS_THIS, 0x4677c0, 2 | CS_POP | CS_THIS, 0x4685b0, 0,
	0x4685c0, 0, 0x4686e0, 0, 0x470cb0, 0, 0x471400, 10 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS, 0x4722e0, 1
	| CS_POP | CS_THIS, 0x472310, 0, 0x4729b0, 9 | CS_POP | CS_THIS, 0x4732f0, 1 | CS_POP | CS_THIS, 0x4734d0, 1 |
	CS_POP | CS_THIS, 0x473610, 0, 0x473780, 1 | CS_POP | CS_THIS, 0x473940, 2 | CS_POP | CS_THIS, 0x474210, 15 |
	CS_POP | CS_THIS, 0x4743e0, 1 | CS_POP | CS_THIS, 0x474b50, 8 | CS_POP | CS_THIS, 0x479a90, 1 | CS_POP | CS_THIS,
	0x47cfd0, 0, 0x47d000, 1 | CS_POP | CS_THIS, 0x487ed0, 0, 0x48b430, 2 | CS_POP | CS_THIS, 0x48c830, 3 | CS_POP |
	CS_THIS, 0x48dbf0, 1 | CS_POP | CS_THIS, 0x48e0f0, 1 | CS_POP | CS_THIS, 0x48e2c0, 1 | CS_POP | CS_THIS, 0x48e680,
	0, 0x48e990, 1 | CS_POP | CS_THIS, 0x48ed90, 1 | CS_POP | CS_THIS, 0x48fd50, 1 | CS_POP | CS_THIS, 0x490d40, 1 |
	CS_POP | CS_THIS, 0x496e40, 1 | CS_POP | CS_THIS, 0x49ca20, 2 | CS_POP | CS_THIS, 0x49ca70, 0, 0x49d150, 0, 0 };
static const DWORD g_gmF[] = {
	0x44, 0x1f4164, 0xbe2fcc, 0xbe2fd0, 0xbe2fd4, 0xbe2fd8, 0xbe2fdc, 0xbe2fe0, 0x22ee234, 0x22ee238, 0x233ca04,
	0x233ca08, 0x233ca0c, 0x233ca28, 0x233ca2c, 0x233cc14, 0x233cc18, 0x233cc1c, 0x233cc38, 0x233cc3c, 0x233cc48,
	0x233cc4c, 0x233cc50, 0x233cc54, 0x233cc58, 0x233cc5c, 0x2340c74, 0x2340c94, 0x2340d29, 0x2342395, 0x234239d,
	0x23423a5, 0x23423b9, 0x23423c1, 0x2342405, 0x2342425, 0x2343293, 0x2343297, 0 };
static const DWORD g_gmI[] = {
	0x1f1ca8, 0x1f1cac, 0x1f1cb4, 0x1f1cb8, 0x1f36c8, 0x1eca67c, 0x1ecca6c, 0x1eccb58, 0x1eccb78, 0x1eccb80, 0x1eccbcc,
	0x1ed52d8, 0x2221f90, 0x2221fb0, 0x2221fb4, 0x22e7184, 0x22e719c, 0x22e71a0, 0x22ee228, 0x22ee4bc, 0x22ee4e4,
	0x22f0400, 0x22f0408, 0x22f040c, 0x22f0410, 0x22f0414, 0x233c9e8, 0x233c9ec, 0x233c9f0, 0x233c9fc, 0x233ca10,
	0x233ca1c, 0x233ca20, 0x233ca24, 0x233cb20, 0x233cc10, 0x233cc20, 0x233cc28, 0x233cc40, 0x2340c64, 0x2340c68,
	0x2340c6c, 0x2340c78, 0x2340c7c, 0x2340c80, 0x2340c84, 0x2340ce0, 0x2340cec, 0x2340cf0, 0x2340cf4, 0x2340d00,
	0x2340d04, 0x2340d1d, 0x2340d35, 0x2340d39, 0x2342399, 0x23423a1, 0x23423a9, 0x23423ad, 0x23423b1, 0x23423b5,
	0x23423bd, 0x23423c5, 0x23423fd, 0x2342401, 0x234240d, 0x2342411, 0x2342415, 0x2342419, 0x234241d, 0x2342421,
	0x2342429, 0x234243a, 0x234243e, 0x2342442, 0x2342446, 0x234244a, 0x234244e, 0x2342452, 0x2342456, 0x234245a,
	0x234245e, 0x2342462, 0x2342466, 0x234246a, 0x234246e, 0x2342472, 0x23424a2, 0x23424ee, 0x23424f2, 0x23428f6,
	0x2342976, 0x234297a, 0x234297e, 0x2342982, 0x234300a, 0x2343106, 0x234325f, 0x2343263, 0x2343267, 0x234326b,
	0x234326f, 0x2343273, 0x2343277, 0x234327b, 0x234327f, 0x2343283, 0x2343287, 0x234328b, 0x234328f, 0x23432cb,
	0x23432cf, 0x23432eb, 0x23432ef, 0x23432fb, 0x23432ff, 0x2343303, 0x2343307, 0x234331b, 0x234331f, 0 };
static const DWORD g_gmG[] = {
	0x4d05a4, 0x4de72a, 0x4df8e8, 0x68039c, 0x76d368, 0x76d408, 0x76d410, 0x9da3e0, 0x9dad94, 0x9f181c, 0x9f67ec,
	0x9f67f0, 0x9f67f4, 0x9f67f8, 0xa0e7e8, 0xa0e7ec, 0xa0e7f0, 0xa1efb8, 0 };
static void gamemode_setup(void)
{
	callee_stubs(g_stubGameMode, 0);
	/* the stubs answer -1..3 each (their answers pick branches and small indexes), but the leader's record */
	for (int k = 0; g_stubGameMode[k]; k += 2) callee_ret(g_stubGameMode[k], (DWORD)irnd(-1, 3));
	callee_ret(0x4625a0, (DWORD)(BUF + 0x1ecca70 + irnd(0, 15) * 0x8888));   /* the leader's player record */
	for (int k = 0; g_gmF[k]; k++) SF(BUF, g_gmF[k]) = csu_fr(-5000, 5000);
	for (int k = 0; g_gmI[k]; k++) S32(BUF, g_gmI[k]) = irnd(0, 3);
	for (int k = 0; g_gmG[k]; k++) G32(g_gmG[k]) = irnd(0, 3);
	for (int p = 0; p < 16; p++) {
		char *r = BUF + 0x1ecca70 + p * 0x8888;
		for (int o = 0xd8; o < 0x570; o += 4) S32(r, o) = irnd(0, 3);
		fill_str(r + 0x98, 12, 'A', 'Z');
		S32(r, 0x118) = irnd(0, 2);   /* the team: an index into the log's three team names */
		/* the records are actor-shaped: their models keep a matrices' address at +0x14 (as actor_processFrame's) */
		static const DWORD models[] = { 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };
		for (int k = 0; k < 7; k++) S32(r, models[k] + 0x14) = (int)(BUF + 0x23a0000 + k * 0x1000);
	}
	S32(BUF, 0x234240d) = irnd(-1, 15); S32(BUF, 0x2340c64) = irnd(-1, 15); S32(BUF, 0x2342976) = irnd(0, 16);
	for (int k = 0; k < 16; k++) { S32(BUF, 0x23428f6 + 4 * k) = irnd(0, 15); S32(BUF, 0x2342936 + 4 * k) = irnd(0, 15); }
	/* +0x2343106 is waited for (0x48e680 called until it is set): it is compared with 0 or 1 (edi): 2..3 here, the stub cannot set it */
	S32(BUF, 0x2343106) = irnd(2, 3);
	/* the game mode 0..11 (odd: team games), 0x9dad94 around 14, the players' +0x179d1fe around 0x180 */
	G32(0x76d368) = irnd(0, 11); G32(0x9dad94) = irnd(10, 18);
	/* the camera modes' tables (by +0x233cc10 / +0x23424f2): positions +0x233cb20 / +0x233cb48 / +0x233cb70, flags
	   +0x233cb98 / +0x233cbc0 / +0x233cbe8 */
	for (int k = -1; k < 10; k++) {
		for (int t = 0; t < 3; t++) SF(BUF, 0x233cb20 + t * 0x28 + 4 * k) = csu_fr(-5000, 5000);
		for (int t = 0; t < 3; t++) S32(BUF, 0x233cb98 + t * 0x28 + 4 * k) = irnd(0, 1);
	}
	S32(BUF, 0x233cc10) = irnd(0, 9); S32(BUF, 0x23424f2) = irnd(-1, 9);
	S32(BUF, 4) = irnd(0, 3); S32(BUF, 8) = irnd(0, 3);   /* small offsets (the field scan missed them) */
	if (irnd(0, 3)) fill_str((char *)0x9f63e4, 16, 'a', 'z'); else G32(0x9f63e4) = 0;   /* the chat line typed */
	/* the network state read through the small getters (0x4a86d0 / 0x4a86e0 / 0x4a86f0): online or not, the slot
	   number 0..15; the local player -1 (not joined yet) a quarter of the time */
	G32(0x9f9838) = irnd(0, 1); G32(0x9fd94c) = irnd(0, 2); *(BYTE *)0x9fd954 = (BYTE)irnd(0, 15);
	if (!irnd(0, 3)) S32(BUF, 0x234240d) = -1;
	for (int p = 0; p < 16; p++) S32(BUF, 0x179d1fe + p * 0x47fd2) = irnd(0, 1) ? 0x180 : irnd(0x170, 0x190);
	for (int j = 0; j < 0x7000; j += 4) SF(BUF + 0x23a0000, j) = csu_fr(-500, 500);
	g_vfsOpenFail = irnd(0, 1);
	g_paintStacks = 1;
}
ST(game_processGameMode, gamemode_setup();, TC(DWORD, 0x4988e0, char *)(BUF), game_processGameMode(BUF))
