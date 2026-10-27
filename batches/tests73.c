/* batch 72 */
/* an actor (0..3) in state 1 mostly, its stat block random, its player (0..3) with a pilot 0..7, part indices 0..3
   and items -1..7 (the item, part and type tables random around the fields read), game mode 0..12 and the
   one-third flag random; stacks painted. Random stats fail the first comparisons: the play test covers the passing
   path (the game runs this check on the local player every 20 s and ends the match with "data loss" on a 0) */
/* call the original from a known stack pointer and return its finished frame (it compares the actor's stat block
   with a local copy at frame + 0x28 + offset, the item count at frame + 0x470): entry esp - 0x88bc (3 SEH pushes,
   the 0x88a0 _chkstk frame, 4 saved registers). Read at once: the frame is below the stack pointer */
static BYTE g_totFrame[0x480];
static BYTE *totals_frame(char *scene, int actor)
{
	DWORD sp;
	__asm__ volatile("movl %%esp, %0
	pushl %2
	movl %1, %%ecx
	movl $0x45ee40, %%eax
	call *%%eax"
	                 : "=m"(sp) : "r"(scene), "r"(actor) : "eax", "ecx", "edx", "memory", "cc");
	memcpy(g_totFrame, (BYTE *)(sp - 8 - 0x88bc), sizeof g_totFrame);
	return g_totFrame;
}
static void tot_fill(char *p, int n)           /* plausible floats (part stats), sometimes random bytes */
{
	if (!irnd(0, 9)) { fill(p, n); return; }
	for (int i = 0; i + 4 <= n; i += 4) SF(p, i) = (float)irnd(0, 20000) / 100.0f;
}
static void totals_setup(void)
{
	int a = irnd(0, 3), p = irnd(0, 3);
	char *ac = BUF + 0x1cd93a8 + a * 0x8888, *pl = BUF + 0x1561b68 + p * 0x47fd2;
	fill(ac, 0x500);
	S32(ac, 0x14c) = irnd(0, 5) ? 1 : irnd(0, 2) * 2; S32(ac, 0x10c) = p;
	fill(pl, 0x340);
	S32(pl, 0x44) = irnd(0, 7);
	for (int k = 0; k < 5; k++) S32(pl, 0x30c + 4 * k) = irnd(0, 3);
	for (int k = 0; k < 6; k++) S32(pl, 0x320 + 4 * k) = irnd(0, 2) ? -1 : irnd(0, 7);
	for (int i = 0; i < 4; i++) {
		tot_fill(BUF + 0x13c9b30 + i * 0xaa8 + 0xa80, 0x40); tot_fill(BUF + 0x13ebab4 + i * 0xabc - 0x20, 0x40);
		tot_fill(BUF + 0x140c8c0 + i * 0x1300 + 0x12e0, 0x20); tot_fill(BUF + 0x1447ec4 + i * 0x13f4 + 0x13d0, 0x24);
		tot_fill(BUF + 0x1486470 + i * 0x1820 + 0x17f0, 0x30);
	}
	for (int i = 0; i < 8; i++) tot_fill(BUF + 0x14d4860 + i * 0x2e18, 0x20);
	S32(BUF, 0x20f3ab8) = irnd(0, 12); S32(BUF, 0x20f3acc) = irnd(0, 1);
	g_a[0] = a; g_paintStacks = 1;
	if (S32(ac, 0x14c) == 1 && irnd(0, 3)) {                /* make it pass, then maybe break one field */
		BYTE *fr = totals_frame(BUF, a);
		memcpy(ac, fr + 0x28, 0x70); S32(ac, 0x68) = S32(fr + 0x28, 0x50); S32(ac, 0x448) = S32(fr, 0x470);
		for (int k = 0; k < 6; k++) S32(ac, 0x128 + 4 * k) = irnd(0, 9) ? -1000 : irnd(-10, 300);
		for (int k = 0; k < 4; k++) SF(ac, 0x3f4 + 4 * k) = irnd(0, 9) ? (float)irnd(0, 3000) / 100.0f : 31.0f;
		S32(ac, 0x4d8) = irnd(0, 1);
		if (irnd(0, 1)) { int k = irnd(0, 0x1b); if (irnd(0, 1)) SF(ac, 4 * k) += 1.0f; else S32(ac, 4 * k) ^= 1 << irnd(0, 31); }
	}
}
static int g_totalsPass;
static DWORD totals_orig(void)
{
	DWORD r = (DWORD)TC(int, 0x45ee40, char *, int)(BUF, g_a[0]);
	g_totalsPass += r == 1 && S32(BUF + 0x1cd93a8 + g_a[0] * 0x8888, 0x14c) == 1;
	return r;
}
ST(armc_computeTotals, totals_setup();, totals_orig(), armc_computeTotals(BUF, (DWORD)g_a[0]))
