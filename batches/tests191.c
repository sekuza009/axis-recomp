/* batch 190 */
/* a bullet's frame: rankactors_setup's 16 actors (with random positions and radii), the bullet slot's record random
   floats with its integers in range (in use, weapon 0..7, owner -1..15, target -1..15, kind 0..9), its flags byte
   (+0x6c points at it), the weapon records random floats; dt a small float; the damage, sounds, particles and
   target clean-up stubbed (thiscall ones with CS_THIS), the collision maths real */
static const DWORD g_stubBulletFrame[] = { 0x456e50, 2, 0x456ed0, 5, 0x460000, 6 | CS_POP | CS_THIS, 0x471740, 3 | CS_POP | CS_THIS,
	0x479950, 1 | CS_POP | CS_THIS, 0x47cf10, 1 | CS_POP | CS_THIS, 0 };
static void bulletframe_setup(void)
{
	rankactors_setup(g_stubBulletFrame);
	for (int i = 0; i < 16; i++) for (int k = 0; k < 16; k++) GF(BUF + 0x1cd93a8 + i * 0x8888 + 0x2e00 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	int slot = irnd(0, 399);
	char *b = BUF + 0x202ef34 + slot * 0x4e8;
	for (int k = 0; k < 0x4e8 / 4; k++) GF(b + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	S32(b, 4) = 1; S32(b, 8) = irnd(0, 7); S32(b, 0xb8) = irnd(-1, 15); S32(b, 0xbc) = irnd(0, 9);
	S32(b, 0xc0) = irnd(-1, 15); S32(b, 0xd0) = irnd(-1, 15); S32(b, 0) = irnd(0, 1000);
	S32(b, 0xc) = irnd(0, 15); S32(b, 0xb4) = irnd(-1, 15); S32(b, 0x4e4) = irnd(0, 10);   /* owner actor, a second actor, the trail count (20 entries from +0x494) */
	*(BYTE *)(BUF + 0x600) = (BYTE)irnd(0, 255); S32(b, 0x6c) = (int)(BUF + 0x600);
	for (int w = 0; w < 8; w++) for (int k = 0; k < 0x80; k++) GF(BUF + 0x14d1ab4 + w * 0x2e18 + 4 * k) = (float)irnd(-1000, 1000) / 10.0f;
	G32(0x83a9c8) = irnd(0, 1);
	g_a[0] = slot; GF(&g_a[1]) = (float)irnd(1, 100) / 1000.0f;
}
ST(bullet_update, bulletframe_setup();, (TC(void, 0x47a2d0, char *, int, int)(BUF, g_a[0], g_a[1]), 0),
   (bullet_update(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
