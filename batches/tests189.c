/* batch 188 */
/* bullets: the scene at BUF (thiscall); the 400 slots' used flags random, the next free / highest used slot (sometimes
   all in use), the serial; a shot at BUF + 0x100 (weapon -1..7 at +4, floats elsewhere); an owner actor 0..15 and
   ids; the weapon records and owner actors zero apart from random floats; bullet_init stubbed for bullet_spawn, the
   sounds, particles and actor helpers stubbed for bullet_init (thiscall ones with CS_THIS) */
static const DWORD g_stubBulletInit[] = { 0x479b40, 6 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubBulletSpawn[] = { 0x456e50, 2, 0x456ed0, 5, 0x4677c0, 2 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS,
	0x479950, 1 | CS_POP | CS_THIS, 0 };
static void bullets_setup(const DWORD *stubs)
{
	int hi = irnd(-1, 399);
	for (int i = 0; i <= hi && i < 400; i++) S32(BUF, 0x202ef38 + i * 0x4e8) = irnd(0, 3) ? 1 : 0;
	S32(BUF, 0x20a99b4) = hi; S32(BUF, 0x20a99b8) = irnd(0, 9) ? irnd(0, hi + 1) : 400; S32(BUF, 0x20a99bc) = irnd(0, 100000);
	char *d = BUF + 0x100;
	for (int k = 0; k < 0x20; k++) GF(d + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(d, 4) = irnd(0, 9) ? irnd(0, 7) : -1;
	for (int i = 0; i < 16; i++) for (int k = 0; k < 8; k++) GF(BUF + 0x1cd93a8 + i * 0x8888 + 0x2e00 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	g_a[0] = irnd(0, 399); g_a[1] = irnd(-1, 50); g_a[2] = irnd(0, 15); g_a[3] = irnd(0, 3); g_a[4] = (int)d; g_a[5] = irnd(-1, 15);
	callee_stubs(stubs, (DWORD)irnd(0, 399));
}
ST(bullet_spawn, bullets_setup(g_stubBulletInit);, TC(DWORD, 0x47ce50, char *, int, int, int, char *, int)(BUF, g_a[1], g_a[2], g_a[3], (char *)g_a[4], g_a[5]),
   bullet_spawn(BUF, (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5]))
ST(bullet_init, bullets_setup(g_stubBulletSpawn);, (TC(void, 0x479b40, char *, int, int, int, int, char *, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3], (char *)g_a[4], g_a[5]), 0),
   (bullet_init(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5]), 0))
