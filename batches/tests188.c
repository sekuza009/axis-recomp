/* batch 187 */
/* particles: the system at BUF (thiscall), its 1000 slots' used flags random (some runs of free ones), the next
   free and highest used slot (sometimes full: 1000), the serial; a descriptor at BUF + 0x100 (kind 0..2 at
   +0x30, floats elsewhere, its matrix / vector pointers into BUF); the listener / camera vectors; the other one of the
   pair stubbed (thiscall), the 3D sound stubbed */
static const DWORD g_stubPartInit[] = { 0x475070, 2 | CS_POP | CS_THIS, 0 };
static const DWORD g_stubPartSpawn[] = { 0x456ed0, 5, 0x479950, 1 | CS_POP | CS_THIS, 0 };
static void particles_setup(const DWORD *stubs)
{
	int hi = irnd(-1, 999);
	for (int i = 0; i <= hi && i < 1000; i++) S32(BUF, 0x20a99c4 + i * 0x12c) = irnd(0, 3) ? 1 : 0;
	S32(BUF, 0x20f2da0) = hi; S32(BUF, 0x20f2da4) = irnd(0, 9) ? irnd(0, hi + 1) : 1000; S32(BUF, 0x20f2da8) = irnd(0, 100000);
	char *d = BUF + 0x100;
	for (int k = 0; k < 0x30; k++) GF(d + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(d, 0x30) = irnd(0, 2);
	/* +0x20 a matrix or none, +0x24 / +0x28 vectors: pointers into BUF (the rest values, +0x58 / +0x64 inline vectors) */
	S32(d, 0x20) = irnd(0, 2) ? (int)(BUF + 0x200) : 0; S32(d, 0x24) = (int)(BUF + 0x240); S32(d, 0x28) = (int)(BUF + 0x250);
	for (int k = 0; k < 0x30; k++) GF(BUF + 0x200 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(BUF, 0x230) = 0;
	for (int k = 0; k < 3; k++) GF(0xa0e7a8 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	for (int k = 0; k < 3; k++) G32(0xa0e7b8 + 4 * k) = irnd(0, 3);
	G32(0xa1efb8) = irnd(0, 0x2000); G32(0xa1f23c) = irnd(0, 3);
	g_a[0] = irnd(0, 999);
	callee_stubs(stubs, (DWORD)irnd(0, 999));
}
ST(particle_spawn, particles_setup(g_stubPartInit);, TC(DWORD, 0x479950, char *, char *)(BUF, BUF + 0x100),
   particle_spawn(BUF, (DWORD)(BUF + 0x100)))
ST(particle_init, particles_setup(g_stubPartSpawn);, (TC(void, 0x475070, char *, int, char *)(BUF, g_a[0], BUF + 0x100), 0),
   (particle_init(BUF, (DWORD)g_a[0], (DWORD)(BUF + 0x100)), 0))
