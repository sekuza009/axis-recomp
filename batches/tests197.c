/* batch 196 */
/* the replay viewer: the first frame or a later one, playing or not, a frame time, 0..16 players (in use, followed
   or not), the followed player -1..n-1, a camera 0..9 with its ten views' angles and flags, the map list position,
   the HUD flags and timers, 0..10 marker records (+0xbc06cc, 0x2c bytes); the replay file 0..8 records (time,
   sender, length <= 0x100, packet; scrambled as 0x46cbe0 descrambles it: byte = rol(x ^ 0x59, 1)) with times around
   the current one; the viewer's key bindings distinct, one of them pressed (or none) for both key tests. All
   drawing, the scene's updates and the packet handler stubbed; the timers, float getters, vector rotation and the
   file reader real */
static const DWORD g_stubReplay[] = { 0x401590, 1, 0x401600, 1, 0x44ad30, 4, 0x44ad60, 4, 0x456b50, 0 | CS_THIS, 0x457310, 0,
	0x45dfb0, 1 | CS_POP | CS_THIS, 0x45e0c0, 1 | CS_POP | CS_THIS, 0x45e170, 2 | CS_POP | CS_THIS, 0x461f10, 0 | CS_THIS,
	0x4629c0, 1 | CS_POP | CS_THIS, 0x462ac0, 1 | CS_POP | CS_THIS, 0x4630c0, 2 | CS_POP | CS_THIS, 0x463450, 2,
	0x470a70, 0 | CS_THIS, 0x470ad0, 0 | CS_THIS, 0x471400, 10 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS,
	0x472900, 4 | CS_POP | CS_THIS, 0x4729b0, 9 | CS_POP | CS_THIS, 0x473610, 0 | CS_THIS, 0x479a90, 1 | CS_POP | CS_THIS,
	0x479af0, 1 | CS_POP | CS_THIS, 0x47d000, 1 | CS_POP | CS_THIS, 0x47d060, 1 | CS_POP | CS_THIS, 0x4841f0, 2 | CS_POP | CS_THIS,
	0x484260, 0 | CS_THIS, 0x485120, 4 | CS_POP | CS_THIS, 0x485af0, 2 | CS_POP | CS_THIS, 0x487c80, 1,
	0x48c830, 3 | CS_POP | CS_THIS, 0x48ed90, 1 | CS_POP | CS_THIS, 0x48f970, 1 | CS_POP | CS_THIS, 0x490d40, 1 | CS_POP | CS_THIS,
	0x490da0, 1 | CS_POP | CS_THIS, 0x4913a0, 0 | CS_THIS, 0x494930, 0 | CS_THIS, 0x495190, 0 | CS_THIS,
	0x496820, 3 | CS_POP | CS_THIS, 0x496b80, 0 | CS_THIS, 0x496c20, 0 | CS_THIS, 0x496e40, 1 | CS_POP | CS_THIS,
	0x496f20, 1 | CS_POP | CS_THIS, 0x497d20, 2 | CS_POP | CS_THIS, 0x4685f0, 2, 0 };
static const DWORD g_replayKeys[] = { 0x4deb58, 0x4deb5c, 0x4deb60, 0x4deb64, 0x4deb68, 0x4deb6c, 0x4deb70, 0x4deb78, 0x4dec8c,
	0x4dec90, 0x4def00, 0x4def04, 0x4def08, 0x4def0c, 0x4def10, 0x4def14, 0x4def18, 0x4def1c, 0x4def30, 0x4def34, 0x4def40,
	0x4def44, 0x4def48, 0x4def4c, 0x4defc8, 0x4defcc, 0x4defe0, 0x4defe4, 0x4df8d0, 0x4e0468, 0x5b1da8, 0x67ef24, 0x9dae70, 0 };
static void replay_setup(void)
{
	callee_stubs(g_stubReplay, 0);
	int nk = 0;
	for (const DWORD *k = g_replayKeys; *k; k++) G32(*k) = 0x10 + nk++;
	int key = irnd(0, 2) ? 0x10 + irnd(0, nk - 1) : -1;
	callee_key(0x401600, irnd(0, 1) ? key : -1); callee_key(0x401590, irnd(0, 1) ? key : -1);
	G32(0x4ded88) = irnd(0, 4) ? 0 : 1; G32(0x4ded8c) = irnd(0, 4) ? 0 : 1;
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480); G32(0x4df000) = irnd(0, 1); G32(0x4df008) = irnd(1, 20);
	G32(0x9eeac0) = irnd(0, 1); G32(0x4b2a7c) = irnd(0, 1); G32(0xa1efb8) = irnd(0, 0x10000);
	S32(BUF, 0x233cc28) = irnd(0, 3) ? irnd(1, 100) : 0;
	GF(BUF + 0x44) = (float)irnd(1, 100) / 1000.0f;
	S32(BUF, 0x2340ce0) = irnd(0, 3) ? 0 : 1;
	int n = irnd(0, 16);
	S32(BUF, 0x2221f90) = n;
	for (int i = 0; i < 16; i++) {
		char *p = BUF + 0x1eccb08 + i * 0x888;
		S32(p, 0x40) = irnd(0, 2); S32(p, 0x70) = irnd(0, 2); S32(p, 0x80) = irnd(-1, 1);
		for (int k = 0xbc; k < 0xd0; k += 4) GF(p + k) = (float)irnd(-1000, 1000) / 10.0f;
		GF(p + 0x350) = (float)irnd(0, 3600) / 10.0f;
		S32(BUF, 0x1ed52d8 + i * 0x8888) = irnd(0, 1); S32(BUF, 0x1ed52d8 - 0x83a8 + i * 0x8888) = irnd(0, 15);
	}
	S32(BUF, 0x2340c64) = irnd(-1, n - 1);
	S32(BUF, 0x2340c70) = irnd(0, 1); S32(BUF, 0x2340c68) = irnd(0, 1); S32(BUF, 0x2340c6c) = irnd(0, 1);
	S32(BUF, 0x233cc10) = irnd(0, 9);
	for (int k = 0; k < 10; k++) {
		GF(BUF + 0x233ca30 + 4 * k) = (float)irnd(-900, 900); GF(BUF + 0x233ca58 + 4 * k) = (float)irnd(0, 3600) / 10.0f;
		GF(BUF + 0x233ca80 + 4 * k) = (float)irnd(1, 500) / 10.0f;
		S32(BUF, 0x233caa8 + 4 * k) = irnd(0, 1); S32(BUF, 0x233cad0 + 4 * k) = irnd(0, 1); S32(BUF, 0x233caf8 + 4 * k) = irnd(0, 1);
	}
	for (int k = 0; k < 5; k++) GF(BUF + 0x22ee228 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	GF(BUF + 0x233ca28) = (float)irnd(-900, 900); GF(BUF + 0x233ca2c) = (float)irnd(-3600, 3600) / 10.0f;
	S32(BUF, 0x1f35bc) = irnd(0, 5); S32(BUF, 0x1f35c0) = irnd(0, 5);
	GF(BUF + 0x233cc38) = (float)irnd(0, 200) / 10.0f; GF(BUF + 0x233cc3c) = (float)irnd(0, 200) / 10.0f;
	GF(BUF + 0x233cc40) = (float)irnd(-10, 50) / 10.0f; GF(BUF + 0x2342f02) = (float)irnd(-10, 50) / 10.0f;
	GF(BUF + 0x2342425) = irnd(0, 2) ? (float)irnd(-10, 50) / 10.0f : (float)irnd(1, 100) / 1000.0f;   /* some run out this frame */ GF(BUF + 0x2340d39) = (float)irnd(-10, 50) / 10.0f;
	GF(BUF + 0x233cc34) = (float)irnd(0, 20) / 10.0f; S32(BUF, 0x233cc30) = irnd(0, 5000);
	S32(BUF, 0x23432ab) = irnd(0, 1); S32(BUF, 0x23432af) = irnd(0, 1); S32(BUF, 0x2343283) = irnd(0, 1);
	S32(BUF, 0x234328b) = irnd(0, 1); S32(BUF, 0x234328f) = irnd(0, 1); S32(BUF, 0x233c9fc) = irnd(0, 2);
	S32(BUF, 0x2340ce4) = irnd(0, 1); S32(BUF, 0x2340ce8) = irnd(0, 1); S32(BUF, 0x2340cd4) = irnd(0, 1);
	S32(BUF, 0xbe170c) = irnd(0, 1); GF(BUF + 0x22f040c) = (float)irnd(0, 100) / 10.0f; S32(BUF, 0x1f1664) = irnd(0, 100);
	int nm = irnd(0, 10);
	S32(BUF, 0xbcb6c8) = nm;
	for (int i = 0; i < nm; i++) {
		char *r = BUF + 0xbc06cc + i * 0x2c;
		S32(r, 0) = irnd(0, 2);
		for (int k = 4; k < 0x2c; k += 4) GF(r + k) = (float)irnd(-1000, 1000) / 10.0f;
	}
	/* the replay file */
	float now = (float)irnd(0, 1000) / 10.0f;
	GF(BUF + 0x2340d2d) = now; GF(BUF + 0x2340d29) = now + (float)irnd(-20, 5) / 10.0f;
	S32(BUF, 0x2340d25) = 0;
	BYTE *d = (BYTE *)BUF + 0x10000;
	int nr = irnd(0, 8), pos = 0;
	float t = GF(BUF + 0x2340d29);
	for (int i = 0; i < nr; i++) {
		t += (float)irnd(0, 10) / 10.0f;
		int len = irnd(0, 0x100);
		GF(d + pos) = t; S32(d, pos + 4) = irnd(0, 16); S32(d, pos + 8) = len; pos += 12;
		for (int k = 0; k < len; k++) d[pos + k] = (BYTE)irnd(0, 255);
		pos += len;
	}
	if (irnd(0, 3)) { GF(d + pos) = t + 100.0f; S32(d, pos + 4) = 0; S32(d, pos + 8) = 0; pos += 12; }   /* a record in the future: the reading stops before the file's end (always whole: a record cut after its time leaves the length to the stack) */
	for (int k = 0; k < pos; k++) { BYTE x = d[k]; d[k] = (BYTE)((x >> 1 | x << 7) ^ 0x59); }
	g_vfsData = d; g_vfsSize = (DWORD)pos;
	S32(BUF, 0x2340d08) = (int)VFS_FILE(0);
}
ST(replay_frame, replay_setup();, TC(DWORD, 0x487f00, char *)(BUF), replay_frame(BUF))
