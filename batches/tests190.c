/* batch 189 */
/* a particle's frame: particles_setup's system, the slot's record random floats (its clock +0x74 ahead of or behind
   its life +0x70, a kind and count +4 / +8 as small integers), a second argument as a small value or a float; the
   free (0x4799f0), spawn and matrix helper stubbed (thiscall) */
static const DWORD g_stubPartFrame[] = { 0x471740, 3 | CS_POP | CS_THIS, 0x479950, 1 | CS_POP | CS_THIS, 0x4799f0, 1 | CS_POP | CS_THIS, 0 };
static void partframe_setup(void)
{
	particles_setup(g_stubPartFrame);
	int slot = irnd(0, 999);
	char *r = BUF + 0x20a99c0 + slot * 0x12c;
	for (int k = 0; k < 0x12c / 4; k++) GF(r + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(r, 4) = irnd(0, 3); S32(r, 8) = irnd(0, 200); S32(r, 0x14) = irnd(0, 50); S32(r, 0x18) = irnd(0, 50);
	GF(r + 0x70) = irnd(0, 9) ? (float)irnd(1, 500) / 10.0f : 0.0f; GF(BUF + 0x20a9a34 + slot * 0x12c) = (float)irnd(0, 600) / 10.0f;
	S32(r, 0x28) = 0;
	g_a[0] = slot; g_a[1] = irnd(0, 1) ? irnd(0, 10) : (int)0x3d4ccccd;
}
ST(match_476410, partframe_setup();, (TC(void, 0x476410, char *, int, int)(BUF, g_a[0], g_a[1]), 0),
   (match_476410(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
/* an object's frame: the record random floats (its mode 0..4 at +0x2a0, the active flag +0x29c..), dt a small float,
   the object index 0..63; the helpers stubbed (thiscall ones with CS_THIS), the matrix maths real */
static const DWORD g_stubObjFrame[] = { 0x466910, 5, 0x46ab30, 3 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS,
	0x479950, 1 | CS_POP | CS_THIS, 0x480480, 0, 0x490df0, 4 | CS_POP | CS_THIS, 0 };
static void objframe_setup(void)
{
	int i = irnd(0, 63);
	char *r = BUF + 0x131ae44 + i * 0x2cc;
	for (int k = 0; k < 0x2cc / 4; k++) GF(r + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(r, 0x2a0) = irnd(0, 4); if (!irnd(0, 4)) GF(r + 0x29c) = 0.0f;
	GF(BUF + 0x131b0e0 + i * 0x2cc) = irnd(0, 4) ? 1.0f : 0.0f;
	/* +0x27c its skeleton (bone count +0x18, a scale +0x28), +0x280 / +0x284 the pose copied from / to (count dwords) */
	S32(r, 0x27c) = (int)(BUF + 0x300); S32(BUF, 0x318) = irnd(0, 16); GF(BUF + 0x328) = (float)irnd(1, 100) / 10.0f;
	fill(BUF + 0x400, 0x40); S32(r, 0x280) = (int)(BUF + 0x400); S32(r, 0x284) = (int)(BUF + 0x500);
	g_a[0] = i; GF(&g_a[1]) = (float)irnd(1, 100) / 1000.0f;
	callee_stubs(g_stubObjFrame, (DWORD)irnd(0, 1));
}
ST(actor_render, objframe_setup();, (TC(void, 0x490440, char *, int, int)(BUF, g_a[0], g_a[1]), 0),
   (actor_render(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
