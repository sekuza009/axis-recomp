/* batch 192 */
/* items: rankactors_setup's 16 actors (positions random floats, alive or not) and their count, 0..24 items with
   types -1..0x28, states 0..2, timers and positions, the type table random floats with small sound / weapon
   integers; dt a small float; the message formatting and sound stubbed */
static const DWORD g_stubItems[] = { 0x456ed0, 5, 0x46c5f0, 3, 0x46c710, 3, 0 };
static void items_setup(void)
{
	rankactors_setup(g_stubItems);
	S32(BUF, 0x202e8c8) = irnd(0, 16);
	int n = irnd(0, 24);
	S32(BUF, 0x20fcd38) = n;
	for (int i = 0; i < n; i++) {
		char *it = BUF + 0x20fadf8 + i * 0x28;
		for (int k = 0; k < 10; k++) GF(it + 4 * k) = (float)irnd(-500, 500) / 10.0f;
		S32(it, 0) = irnd(-1, 0x28); S32(it, 0x20) = irnd(0, 2); S32(it, 4) = irnd(0, n - 1); S32(it, 8) = irnd(0, 3);   /* +4: a linked item */
	}
	for (int t = 0; t <= 0x28; t++) {
		char *ty = BUF + 0x20f3ae0 + t * 0x90;
		for (int k = 0; k < 0x24; k++) GF(ty + 4 * k) = (float)irnd(0, 500) / 10.0f;
		for (int k = 0x30; k < 0x48; k += 4) S32(ty, k) = irnd(0, 15);
	}
	/* the actors' positions (+0x1cd94fc, scene-relative) and pickup radii (+0x1cd9790): some at an item */
	for (int i = 0; i < 16; i++) {
		char *a = BUF + i * 0x8888;
		int at = n && irnd(0, 1) ? irnd(0, n - 1) : -1;
		for (int k = 0; k < 3; k++) GF(a + 0x1cd94fc + 4 * k) = at >= 0 ? GF(BUF + 0x20fadf8 + at * 0x28 + 0xc + 4 * k) + (float)irnd(-5, 5) / 10.0f : (float)irnd(-500, 500) / 10.0f;
		GF(a + 0x1cd9790) = (float)irnd(5, 50) / 10.0f;
	}
	GF(&g_a[0]) = (float)irnd(1, 100) / 1000.0f;
}
ST(item_update, items_setup();, (TC(void, 0x48ed90, char *, int)(BUF, g_a[0]), 0), (item_update(BUF, (DWORD)g_a[0]), 0))
