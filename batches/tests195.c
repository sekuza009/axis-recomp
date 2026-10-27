/* batch 194 */
/* the game packets: a random 0x100-byte packet at BUF + 0x100 of kind 0..15 (type 0x40, or another type now and
   then), with the bytes each kind uses as player / table indexes, divisors' inputs and string lengths kept where
   the game's senders keep them (player indexes 0..16 and never negative, names terminated, the item index -1..0x7b);
   the scene's state: recording or not, waiting for the start or not, the local player 0..15, the map table sizes
   and the checksums' divisors non-zero, the game mode; every handler stubbed (team lookup 0x463740 -1..4) */
static const DWORD g_stubNetPkt[] = { 0x45dc00, 4 | CS_POP | CS_THIS, 0x45dca0, 1 | CS_POP | CS_THIS, 0x45e810, 2 | CS_POP | CS_THIS,
	0x461ec0, 1 | CS_POP | CS_THIS, 0x462150, 0 | CS_THIS, 0x462b50, 1 | CS_POP | CS_THIS, 0x462bc0, 1 | CS_POP | CS_THIS,
	0x462c30, 3 | CS_POP | CS_THIS, 0x462d30, 2 | CS_POP | CS_THIS, 0x462e30, 2 | CS_POP | CS_THIS, 0x462f30, 0 | CS_THIS,
	0x462f90, 0 | CS_THIS, 0x462fd0, 0 | CS_THIS, 0x463030, 2 | CS_POP | CS_THIS, 0x463740, 1 | CS_POP | CS_THIS, 0x46cc30, 4,
	0x4732f0, 1 | CS_POP | CS_THIS, 0x473940, 2 | CS_POP | CS_THIS, 0x473a10, 2 | CS_POP | CS_THIS, 0x473a80, 2 | CS_POP | CS_THIS,
	0x473b10, 2 | CS_POP | CS_THIS, 0x473c20, 2 | CS_POP | CS_THIS, 0x473d30, 2 | CS_POP | CS_THIS, 0x473e40, 2 | CS_POP | CS_THIS,
	0x473f50, 2 | CS_POP | CS_THIS, 0x474060, 3 | CS_POP | CS_THIS, 0x474390, 1 | CS_POP | CS_THIS, 0x4743b0, 1 | CS_POP | CS_THIS,
	0x4743e0, 1 | CS_POP | CS_THIS, 0x474b50, 8 | CS_POP | CS_THIS, 0x474fd0, 8 | CS_POP | CS_THIS, 0x48ead0, 0 | CS_THIS, 0 };
static void netpkt_setup(void)
{
	callee_stubs(g_stubNetPkt, 0);
	callee_ret(0x463740, (DWORD)irnd(-1, 4));
	S32(BUF, 0x2340d1d) = irnd(0, 3) ? 0 : 1; S32(BUF, 0x2340d08) = irnd(0, 1000);
	S32(BUF, 0x233cc20) = irnd(0, 4) ? 0 : 1;
	S32(BUF, 0x234240d) = irnd(0, 15);
	G32(0x9dad94) = irnd(-1, 8);
	S32(BUF, 0x1f1cb0) = irnd(0, 1); S32(BUF, 0x22f0408) = irnd(0, 60); S32(BUF, 0xbe3000) = irnd(0, 3);
	S32(BUF, 8) = irnd(0, 4) ? 3 : irnd(0, 4); S32(BUF, 0x1f35c4) = irnd(0x11f0, 0x1210); S32(BUF, 4) = irnd(0, 1);
	for (int k = 0; k < 6; k++) S32(BUF, 0x23423e5 + 4 * k) = irnd(1, 4);
	static const DWORD cnt[] = { 0x15de6c8, 0x15fff84, 0x163b588, 0x1679b34, 0x16c5178, 0x175522c };
	for (int k = 0; k < 6; k++) S32(BUF, cnt[k]) = irnd(1, 8);
	S32(BUF, 0x23423b5) = irnd(0, 2); S32(BUF, 0x23423a1) = irnd(0, 1); S32(BUF, 0x2342399) = irnd(0, 1);
	S32(BUF, 0x22e7184) = irnd(0, 1); S32(BUF, 0x2221fb8) = irnd(0, 3); S32(BUF, 0x2221fbc) = irnd(0, 3);
	S32(BUF, 0x2343253) = irnd(0, 1); S32(BUF, 0x22f0400) = irnd(0, 140);
	BYTE *p = (BYTE *)BUF + 0x100;
	for (int k = 0; k < 0x100; k++) p[k] = (BYTE)irnd(0, 255);
	memset(p + 0xf0, 0, 0x10);
	int kind = irnd(0, 15);
	p[1] = (BYTE)kind;
	switch (kind) {
	case 1:
		p[2] = (BYTE)(irnd(0, 1) ? 0 : irnd(0, 0x11));
		for (int k = 3; k <= 6; k++) p[k] = (BYTE)irnd(-1, 15);
		p[0x2b] = (BYTE)irnd(0, 5);
		*(short *)(p + 0x29) = (short)irnd(-1, 0x7b);
		break;
	case 2:
		fill_str((char *)p + 2, 16, 'A', 'z');
		p[0x13] = (BYTE)irnd(-1, 9); p[0x14] = (BYTE)irnd(0, 9); p[0x16] = (BYTE)irnd(0, 16);
		for (int k = 0x17; k <= 0x21; k++) p[k] = (BYTE)irnd(0, 9) ? (BYTE)irnd(0, 1) : (BYTE)irnd(0, 9);   /* within the table sizes, mostly */
		break;
	case 0: {   /* the sender (byte 4 >> 4) in use, its record fresh or not */
		int i = p[4] >> 4;
		S32(BUF, 0x1755230 + i * 0x47fd2) = irnd(0, 3) ? 1 : 0;
		S32(BUF, 0x1ecca70 + i * 0x888 + 0x108) = irnd(0, 1);
		break;
	}
	case 3: case 4: case 5: case 13:
		if (irnd(0, 5)) p[2] = 0x6b;
		break;
	case 6: case 7: case 8: case 9:
		p[2] = (BYTE)irnd(0, 0x11);
		fill_str((char *)p + 3, irnd(0, 3) ? 16 : 0x3a, 'A', 'z');
		break;
	case 10: case 11:
		p[2] = (BYTE)irnd(0, 16);
		fill_str((char *)p + 4, 16, 'A', 'z');
		break;
	case 12:
		p[2] = (BYTE)irnd(0, 0x11);
		*(short *)(p + 3) = (short)irnd(-1, 0x171);
		break;
	}
	g_a[0] = irnd(0, 16); g_a[1] = irnd(0, 9) ? 0x40 : irnd(0, 0x80); g_a[2] = (int)p;
}
ST(net_processGamePacket, netpkt_setup();, (TC(void, 0x48c830, char *, int, int, int)(BUF, g_a[0], g_a[1], g_a[2]), 0),
	(net_processGamePacket(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2]), 0))
