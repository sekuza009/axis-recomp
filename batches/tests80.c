/* batch 79 */
/* a generated PTX file in the VFS. Random data could run a block's coefficient index past 64 and smash the
   original's stack, so the test installs complete prefix codes (the DC tables overlap: table 0 has 12 categories,
   table 1 starts at its 13th entry; the AC tables are 8-bit codes) and encodes valid blocks with them: a DC
   category with its bits, then (run, size) pairs, zero runs of 16, and an end-of-block unless the block is full */
static BYTE *g_bw; static int g_bp;
static void bits_put(DWORD v, int n)
{
	for (int k = n - 1; k >= 0; k--, g_bp++)
		if (v >> k & 1) g_bw[g_bp >> 3] |= (BYTE)(0x80 >> (g_bp & 7)); else g_bw[g_bp >> 3] &= (BYTE)~(0x80 >> (g_bp & 7));
}
static void ptxfile_setup(void)
{
	int *dc = (int *)0x4c5af0, perm[256];
	for (int i = 0; i < 12; i++) perm[i] = i;
	for (int i = 11; i > 0; i--) { int j = irnd(0, i), x = perm[i]; perm[i] = perm[j]; perm[j] = x; }
	for (int i = 0; i < 12; i++) { int c = perm[i]; dc[i * 2] = c < 4 ? 3 : 4; dc[i * 2 + 1] = c < 4 ? c : c + 4; }   /* 000..011, 1000..1111 */
	for (int i = 0; i < 16; i++) perm[i] = i;
	for (int i = 15; i > 0; i--) { int j = irnd(0, i), x = perm[i]; perm[i] = perm[j]; perm[j] = x; }
	for (int i = 0; i < 16; i++) { dc[24 + i * 2] = 4; dc[24 + i * 2 + 1] = perm[i]; }
	for (int t = 0; t < 2; t++) {
		int *ac = (int *)(0x4c5bb0 + t * 0x800);
		for (int i = 0; i < 256; i++) perm[i] = i;
		for (int i = 255; i > 0; i--) { int j = irnd(0, i), x = perm[i]; perm[i] = perm[j]; perm[j] = x; }
		for (int i = 0; i < 256; i++) { ac[i * 2] = 8; ac[i * 2 + 1] = perm[i]; }
	}
	BYTE *f = (BYTE *)(BUF + 0x200000);
	int w8 = irnd(0, 19) ? irnd(1, 8) : 0, h8 = irnd(1, 8), type = irnd(0, 19) ? 0x81 + irnd(0, 1) : irnd(0, 0x100);
	memcpy(f, "PTX", 4);
	*(short *)(f + 4) = irnd(0, 29) ? 0x100 : (short)irnd(0, 0x200); *(short *)(f + 6) = (short)w8; *(short *)(f + 8) = (short)h8;
	*(short *)(f + 10) = (short)type; *(short *)(f + 12) = (short)(irnd(0, 4) ? irnd(1, 300) : 100); *(short *)(f + 14) = 0;
	if (!irnd(0, 29)) f[irnd(0, 3)] ^= 1;
	g_bw = f + 16; int off = 0;
	int planes = type == 0x82 ? 4 : 3, blocks = (w8 * 8 * h8 * 8 + 63) >> 6, dense = irnd(0, 30);
	for (int p = 0; p < planes; p++) {
		int t = p == 1 || p == 2, *d = (int *)(0x4c5af0 + t * 96), *ac = (int *)(0x4c5bb0 + t * 0x800);
		g_bp = off * 8;
		for (int b = 0; b < blocks; b++) {
			int c = irnd(0, irnd(0, 3) ? 6 : 11);
			bits_put((DWORD)d[c * 2 + 1], d[c * 2]); bits_put((DWORD)irnd(0, 0x7fff), c);
			int k = 1;
			while (k < 64) {
				if (!irnd(0, dense)) { bits_put((DWORD)ac[1], 8); break; }        /* end of block */
				if (k + 15 < 64 && !irnd(0, 15)) { bits_put((DWORD)ac[0xf0 * 2 + 1], 8); k += 16; continue; }
				int run = irnd(0, irnd(0, 3) ? 2 : 15); if (k + run > 63) run = 63 - k;
				int size = irnd(1, irnd(0, 3) ? 6 : 10), s = run << 4 | size;
				bits_put((DWORD)ac[s * 2 + 1], 8); bits_put((DWORD)irnd(0, 0x7fff), size);
				k += run + 1;
			}
		}
		off = (g_bp + 7) >> 3;
	}
	g_vfsData = f; g_vfsSize = 16 + (DWORD)off + (DWORD)irnd(0, 64); g_vfsOpenFail = !irnd(0, 29);
	fill(f + 16 + off, 64);
	strcpy(BUF + 0x300, irnd(0, 1) ? "Data\\Movie\\a.ptx" : "b.ptx");
	fill(BUF + 0x100, 12); fill(BUF + 0x10000, 0x4000);
}
ST(ptx_open, ptxfile_setup();,
   (CD(void, 0x46eb00, char *, char *, char *, char *, char *)(BUF + 0x300, BUF + 0x10000, BUF + 0x100, BUF + 0x104, BUF + 0x108), 0),
   (ptx_open(0, 0, 0, (DWORD)(BUF + 0x300), (DWORD)(BUF + 0x10000), (DWORD)(BUF + 0x100), (DWORD)(BUF + 0x104), (DWORD)(BUF + 0x108), 0, 0, 0), 0))
ST(ptx_decode, ptxfile_setup(); g_vfsOpenFail = 0;,
   (CD(void, 0x46ed80, int, char *, char *, char *, char *)((int)VFS_FILE(0), BUF + 0x10000, BUF + 0x100, BUF + 0x104, BUF + 0x108), 0),
   (ptx_decode(0, 0, 0, (DWORD)VFS_FILE(0), (DWORD)(BUF + 0x10000), (DWORD)(BUF + 0x100), (DWORD)(BUF + 0x104), (DWORD)(BUF + 0x108), 0, 0, 0), 0))
