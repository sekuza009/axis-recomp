/* batch 179 */
/* the scene's 16 actor / player records at BUF (stride 0x8888; the scratch area is zero between tests): teams -1..3,
   frags and deaths, active / alive flags, the player link and slot, flags; the player table's used flags
   (0x9f9840, 0x410 per slot) and levels (0x9f9068, 0x4c per player); the mode; the callees stubbed (the team test
   0x463740 and 0x473a80 are thiscall on the scene) */
static const DWORD g_stubNewKing[] = { 0x456e50, 2, 0x463450, 2, 0x463740, 1 | CS_POP | CS_THIS, 0x473a80, 2 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubImpact[] = { 0x456e50, 2, 0 };
static void rankactors_setup(const DWORD *stubs)
{
	for (int i = 0; i < 16; i++) {
		char *a = BUF + i * 0x8888;
		S32(a, 0x1eccb88) = irnd(-1, 3); S32(a, 0x1eccb54) = irnd(0, 30); S32(a, 0x1eccb58) = irnd(0, 30);
		S32(a, 0x1cd94f4) = irnd(0, 3) ? 1 : 0; S32(a, 0x1ce1bb4) = !irnd(0, 3); S32(a, 0x1cd94b0) = irnd(0, 1);
		S32(a, 0x1cd94bc) = irnd(0, 15); S32(a, 0x1cd9798) = irnd(0, 0xffff);
		S32(a, 0x1cd94d0) = irnd(0, 500); S32(a, 0x1cd94d4) = irnd(0, 500);
		G32(0x9f9840 + i * 0x410) = irnd(0, 1);
	}
	fill((void *)0x9f9068, 16 * 0x4c);
	for (int i = 0; i < 16 * 19; i++) G32(0x9f9068 + 4 * i) = irnd(0, 100);
	S32(BUF, 0x202e8d4) = irnd(0, 15);
	G32(0x9dae74) = irnd(0, 3);
	S32(BUF, 0x22e7184) = irnd(0, 1); S32(BUF, 0x22e7180) = irnd(0, 7);
	g_a[0] = irnd(0, 15); g_a[1] = irnd(0, 15); g_a[2] = irnd(0, 300); g_a[3] = irnd(0, 10);
	g_a[4] = irnd(0, 1000); g_a[5] = irnd(0, 1000);
	callee_stubs(stubs, (DWORD)irnd(0, 1));
}
T_PLAIN(msg_newKing, 0x462150, rankactors_setup(g_stubNewKing);, BUF, 0, 0, 0, 0)
ST(bullet_playImpactSound, rankactors_setup(g_stubImpact);,
   (TC(void, 0x460000, char *, int, int, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5]), 0),
   (bullet_playImpactSound(BUF, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5]), 0))
