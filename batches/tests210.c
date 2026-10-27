/* batch 209 */
/* an actor's frame: actor 0..15 of player 0..7, every actor field the function reads given a value by its use
   (floats -50..50, ints 0..3), the player's part indexes 0..3 and items -1..3, the scene's actor counts and local /
   followed actors, dt 0.001..0.1 s; every callee stubbed except the three that return in ST0 (Vec3_normalize, the angle steps actor_46c140 /
   actor_46c1c0); stacks painted */
static const DWORD g_stubActorFrame[] = { 0x4326f0, 1, 0x456e50, 2, 0x456ed0, 0, 0x45dca0, 1 | CS_POP | CS_THIS,
	0x45e1f0, 1 | CS_POP | CS_THIS, 0x45e2c0, 1 | CS_POP | CS_THIS, 0x45e390, 1 | CS_POP | CS_THIS, 0x45e460, 1 | CS_POP | CS_THIS,
	0x45e530, 1 | CS_POP | CS_THIS, 0x45e600, 3 | CS_POP | CS_THIS, 0x45e810, 2 | CS_POP | CS_THIS, 0x45e880, 2 | CS_POP | CS_THIS,
	0x45e910, 1 | CS_POP | CS_THIS, 0x45e9e0, 1 | CS_POP | CS_THIS, 0x45eab0, 1 | CS_POP | CS_THIS, 0x45edb0, 1 | CS_POP | CS_THIS,
	0x460000, 6 | CS_POP | CS_THIS, 0x460270, 1 | CS_POP | CS_THIS, 0x4677c0, 2 | CS_POP | CS_THIS, 0x46ab30, 3 | CS_POP | CS_THIS,
	0x46cbc0, 3, 0x46f770, 2 | CS_POP | CS_THIS, 0x46f8c0, 1 | CS_POP | CS_THIS, 0x46fed0, 0,
	0x471400, 10 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS, 0x473450, 2, 0x473780, 1 | CS_POP | CS_THIS,
	0x479950, 1 | CS_POP | CS_THIS, 0x47ce50, 5 | CS_POP | CS_THIS, 0x47cf10, 1 | CS_POP | CS_THIS, 0x47d380, 3, 0x47d740, 2,
	0x47d9d0, 7, 0x483770, 3 | CS_POP | CS_THIS, 0 };
static const DWORD g_afActF[] = { 0xc, 0x1c, 0x38, 0x3c, 0x40, 0x44, 0x48, 0x4c, 0x50, 0x54, 0x6c, 0x7c, 0x80, 0x8c, 0x100, 0x120,
	0x124, 0x150, 0x154, 0x158, 0x15c, 0x160, 0x164, 0x168, 0x16c, 0x170, 0x174, 0x178, 0x17c, 0x180, 0x184, 0x188, 0x18c, 0x190,
	0x194, 0x198, 0x19c, 0x1a0, 0x1a4, 0x1a8, 0x1ac, 0x1b0, 0x1b4, 0x1b8, 0x1c0, 0x1c4, 0x1c8, 0x1cc, 0x1d0, 0x1d4, 0x1d8, 0x1dc,
	0x1e0, 0x1e4, 0x1f4, 0x378, 0x37c, 0x380, 0x384, 0x388, 0x38c, 0x390, 0x394, 0x398, 0x39c, 0x3a0, 0x3e8, 0x3f4, 0x3f8, 0x3fc,
	0x400, 0x464, 0x468, 0x490, 0x494, 0x4a4, 0x4a8, 0x4ac, 0x4b0, 0x4ec, 0x534, 0x540, 0x544, 0x548, 0x87f0, 0x8804, 0x8824,
	0x8828, 0x882c, 0x8830, 0x8834, 0x8844, 0x8854, 0x8858, 0x885c, 0x8860, 0x8864, 0x886c, 0x8874, 0x8878, 0x887c, 0x8884, 0 };
static const DWORD g_afActI[] = { 0x10, 0x20, 0x28, 0x2c, 0x30, 0x34, 0x58, 0x5c, 0x60, 0x74, 0x84, 0x88, 0x90, 0x94, 0x98, 0xdc,
	0xe4, 0xe8, 0xfc, 0x104, 0x110, 0x118, 0x11c, 0x128, 0x12c, 0x130, 0x134, 0x138, 0x13c, 0x140, 0x144, 0x14c, 0x1bc, 0x1e8,
	0x1ec, 0x1f0, 0x1fc, 0x2a0, 0x360, 0x374, 0x3a4, 0x3a8, 0x3f0, 0x448, 0x44c, 0x450, 0x454, 0x458, 0x46c, 0x470, 0x474, 0x478,
	0x47c, 0x480, 0x484, 0x488, 0x48c, 0x498, 0x49c, 0x4a0, 0x4b4, 0x4b8, 0x4c0, 0x4cc, 0x4d0, 0x4d4, 0x4d8, 0x4dc, 0x4e0, 0x4f4,
	0x54c, 0x550, 0x554, 0xd54, 0xd68, 0x1554, 0x1568, 0x2524, 0x2538, 0x34f4, 0x3508, 0x40dc, 0x587c, 0x701c, 0x87f4, 0x87f8,
	0x87fc, 0x8800, 0x8808, 0x8810, 0x8814, 0x8818, 0x881c, 0x8820, 0x884c, 0x8868, 0x8870, 0x8880, 0 };
static const DWORD g_afPlI[] = { 0xc, 0x10, 0x1c, 0x2c, 0x34, 0x3c, 0x294, 0x2d8, 0x330, 0x2dc8, 0 };
static const DWORD g_afScI[] = { 0xa24, 0x1cd9484, 0x1cd948c, 0x1cd94c0, 0x1cd9504, 0x1ce1b94, 0x202e8dc, 0x202e8e8, 0x202e8ec,
	0x202e8f0, 0x202e8f4, 0x202ea80, 0x202ec10, 0x202ef30, 0x202ef40, 0x20a99b4, 0x20f3970, 0x20f397c, 0x20f3ab4, 0x20f3abc,
	0x20f3ac0, 0x20f3ad4, 0x20f3ad8, 0x20fcd48, 0x20fce4c, 0 };
static void actorframe_setup(void)
{
	callee_stubs(g_stubActorFrame, 0);
	int a = irnd(0, 15), p = irnd(0, 7);
	char *ac = BUF + 0x1cd93a8 + a * 0x8888, *pl = BUF + 0x1561b68 + p * 0x47fd2;
	for (int k = 0; g_afActF[k]; k++) SF(ac, g_afActF[k]) = csu_fr(-5000, 5000);
	for (int k = 0; g_afActI[k]; k++) S32(ac, g_afActI[k]) = irnd(0, 3);
	S32(ac, 0x10c) = p;
	for (int k = 0; g_afPlI[k]; k++) S32(pl, g_afPlI[k]) = irnd(0, 3);
	for (int k = 0; k < 5; k++) S32(pl, 0x30c + 4 * k) = irnd(0, 3);
	for (int k = 0; k < 6; k++) S32(pl, 0x320 + 4 * k) = irnd(-1, 3);
	SF(pl, 0x2e08) = csu_fr(-5000, 5000);
	/* the actor's path (+0x87f8: -1 none, else a trigger record (28 bytes at +0xe3b03c) whose first field points to 20-byte
	   points, +0x87fc the current one) */
	S32(ac, 0x87f8) = irnd(-1, 3);
	for (int k = 0; k < 4; k++) S32(BUF, 0xe3b03c + k * 28) = (int)(BUF + 0x23a7000 + k * 0x400);
	for (int j = 0; j < 0x1000; j += 4) SF(BUF + 0x23a7000, j) = csu_fr(-5000, 5000);
	/* the body and weapon models (+0xd54, +0x1554, +0x2524, +0x34f4; +0x40dc, +0x587c, +0x701c) keep their matrices' address
	   at +0x14: 4 KB of floats each in free scratch (BUF + 0x23a0000) */
	static const DWORD models[] = { 0xd54, 0x1554, 0x2524, 0x34f4, 0x40dc, 0x587c, 0x701c };
	for (int k = 0; k < 7; k++) {
		char *mx = BUF + 0x23a0000 + k * 0x1000;
		for (int j = 0; j < 0x1000; j += 4) SF(mx, j) = csu_fr(-500, 500);
		S32(ac, models[k] + 0x14) = (int)mx;
	}
	for (int k = 0; g_afScI[k]; k++) S32(BUF, g_afScI[k]) = irnd(0, 3);
	for (int k = 0; k < 6; k++) SF(BUF, 0x9ef904 + 4 * k) = csu_fr(-5000, 5000);
	S32(BUF, 0x202e8c8) = irnd(0, 16); S32(BUF, 0x202e8d4) = irnd(0, 3) ? a : irnd(-1, 15); S32(BUF, 0x202e8d8) = irnd(-1, 15);
	/* -1 sentinels, flag words with high bits (bit 9 of +0x3f0 and of the player's +0x294), the local actor's team
	   slot, floats now and then far out (thresholds past +-50) */
	S32(ac, 0x8820) = irnd(-1, 3); S32(ac, 0x881c) = irnd(-1, 3); S32(ac, 0x87f4) = irnd(-1, 3);
	S32(ac, 0x3f0) = irnd(0, 0xffff); S32(pl, 0x294) = irnd(0, 0xffff); S32(ac, 0x4c0) = irnd(-1, 3);
	/* the fields compared with constants past 3: the weapon slot 0..5, the fire state 0..4 (4 fires), the effect state
	   0..6 (a jump table; 7 and up: none), +0x490 as 1.0f */
	S32(ac, 0x140) = irnd(0, 6); S32(ac, 0x4d0) = irnd(0, 5); S32(ac, 0x54c) = irnd(0, 8); if (irnd(0, 1)) SF(ac, 0x490) = 1.0f;
	/* the five weapon slots: flags +0x1f8 / +0x1fc (stride 0x20), the item +0x360 (-1: none), the weapon models' object
	   pointer at +0x20 (to a zero dword); other actors' and players' flag words with high bits too */
	for (int k = 0; k < 5; k++) {
		S32(ac, 0x1f8 + k * 0x20) = irnd(0, 2) ? 1 : 0; S32(ac, 0x1fc + k * 0x20) = irnd(0, 2) ? 1 : 0; S32(ac, 0x360 + k * 4) = irnd(-1, 3);
	}
	for (int k = 0; k < 7; k++) S32(ac, models[k] + 0x20) = (int)(BUF + 0x23a8000);
	for (int k = 0; k < 16; k++) if (k != a) S32(BUF, 0x1cd9798 + k * 0x8888) = irnd(0, 0xffff);
	for (int k = 0; k < 8; k++) if (k != p) { S32(BUF, 0x1561b68 + k * 0x47fd2 + 0x294) = irnd(0, 0xffff); S32(BUF, 0x1561b68 + k * 0x47fd2 + 0x2d8) = irnd(0, 0xffff); }
	S32(pl, 0x2d8) = irnd(0, 0xffff);
	S32(ac, 0x128) = irnd(-3, 3); S32(BUF, 0x202e8dc) = irnd(-1, 15);   /* +0x128 <= 0 leads into the death effects */
	/* the other actors' state (+0x14c, 1 = in play) and +0x884c, positions near; the slot items' records (+0x202ef34,
	   stride 0x4e8: +4 == 1 in use) */
	for (int k = 0; k < 16; k++) if (k != a) {
		char *o = BUF + 0x1cd93a8 + k * 0x8888;
		S32(o, 0x14c) = irnd(0, 2); S32(o, 0x884c) = irnd(0, 2) ? 0 : 1;
		for (int j = 0; j < 9; j++) SF(o, 0x154 + 4 * j) = csu_fr(-5000, 5000);
	}
	for (int j = -1; j < 4; j++) S32(BUF, 0x202ef38 + j * 0x4e8) = irnd(0, 1);
	for (int k = 0; k < 16; k++) S32(BUF, 0x1cd94b8 + k * 0x8888) = irnd(0, 1) ? S32(BUF, 0x202e8d4) : irnd(-1, 15);
	for (int k = 0; k < 4; k++) { int o = g_afActF[irnd(0, 99)]; SF(ac, o) = csu_fr(-500000, 500000); }
	g_a[0] = a; GF(&g_a[1]) = (float)irnd(1, 100) / 1000.0f;
	g_paintStacks = 1;
}
ST(actor_processFrame, actorframe_setup();, (TC(void, 0x4580b0, char *, int, int)(BUF, g_a[0], g_a[1]), 0),
	(actor_processFrame(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
