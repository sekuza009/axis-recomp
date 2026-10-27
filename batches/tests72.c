/* batch 71 */
/* shade_setup's shape and factor pool; the parts also get ViewVolume_projectObject's mesh fields (vv_setup's view
   volume); an object list (BUF + 0x50000) of up to 3 entries (shape or none, colour buffers, invertible matrices),
   frames for hud_46fd20; pixel lights (BUF + 0x40000) or none; stacks painted (a singular matrix leaves the inverse
   unwritten) */
static int g_ol[6];
static void objlist_setup(void)
{
	vv_setup(); shade_setup();
	for (int p = 0; p < 3; p++) { char *pt = BUF + 0x200 + p * 0x80; S32(pt, 0x44) = irnd(-1, 30); S32(pt, 0x60) = irnd(-1, 3); }
	S32(BUF + 0x100, 0x18) = irnd(0, 36);
	char *L = BUF + 0x50000; int n = irnd(0, 9) ? irnd(1, 3) : irnd(-1, 0);
	fill(L, 0x40); S32(L, 0x10) = n; S32(L, 0x14) = (int)(L + 0x100);
	S32(L, 0x1c) = irnd(0, 5) ? irnd(1, 3) : 0; S32(L, 0x20) = (int)(L + 0x80); S32(L, 0x24) = irnd(0, 1);
	S32(L, 0x80) = irnd(0, 5) ? 1 : 0; S32(L, 0x84) = irnd(0, 5) ? 1 : 0; S32(L, 0x2c) = irnd(0, 3) ? 1 : irnd(0, 2) * 2;
	for (int k = 0; k < 3; k++) {
		char *e = L + 0x100 + k * 100; fill(e, 100);
		S32(e, 0) = irnd(0, 5) ? (int)(BUF + 0x100) : 0; S32(e, 8) = (int)(BUF + 0x30000 + k * 0x400);
		rotmat(e + 0xc); for (int i = 12; i < 15; i++) SF(e + 0xc, 4 * i) = (float)irnd(-300, 300) / 100.0f; SF(e + 0xc, 60) = 1.0f;
		fill(BUF + 0x30000 + k * 0x400, 0x100);
	}
	S32(BUF + 0x10000, 0xb00c) = irnd(0, 3) ? 1 : 0;
	fill(BUF + 0x40000, 0x100);
	g_ol[0] = irnd(0, 3) ? (int)(BUF + 0x10000) : 0; g_ol[1] = irnd(0, 2) ? 0 : (int)(BUF + 0x40000);
	g_ol[2] = irnd(0, 1) ? 1 : irnd(0, 2); g_ol[3] = irnd(0, 2) ? -1 : irnd(0, 40); g_ol[4] = 11;
	g_paintStacks = 1;
}
ST(data_46f7a0, objlist_setup();, (TC(void, 0x46f7a0, char *, int, int)(BUF + 0x50000, g_ol[0], g_ol[1]), 0),
   (data_46f7a0(BUF + 0x50000, (DWORD)g_ol[0], (DWORD)g_ol[1]), 0))
ST(hud_46fd20, objlist_setup();,
   TC(int, 0x46fd20, char *, char *, int, int, int, int, int)(BUF + 0x50000, BUF + 0x100000, g_ol[0], g_ol[1], g_ol[2], g_ol[3], g_ol[4]),
   hud_46fd20(BUF + 0x50000, (DWORD)(BUF + 0x100000), (DWORD)g_ol[0], (DWORD)g_ol[1], (DWORD)g_ol[2], (DWORD)g_ol[3], (DWORD)g_ol[4]))
