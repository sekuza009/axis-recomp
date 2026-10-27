/* batch 135 */
/* the ranking window: dlgwin_setup's window at 0x9dced8, every texture it binds from that set (the rank icons
   from 0x76d448), pages 0..20, sort columns -1..4, a list or none, 0..10 rows (an empty name ends them), some
   with one-character values, levels 1..60, small floats ("%8.1f" / "%3.2f" go into a 20-byte
   buffer) and counts, loading or not, short texts */
static void put32(char *p, DWORD v) { memcpy(p, &v, 4); }
static void ranking_setup(void)
{
	dlgwin_setup(0x9dced8);
	G32(0x76d448) = G32(0x9db0a4);
	fill((void *)0x9dcec0, 16); fill((void *)0x9dd338, 16);
	G32(0x9dd6ac) = irnd(0, 20); G32(0x9dd1d0) = irnd(-1, 4); G32(0x9dd3b0) = irnd(0, 4) ? 1 : 0;
	G32(0x9dd6b8) = irnd(0, 3) ? 0 : 1; GF(0x4dba80) = (float)irnd(0, 100000) / 100.0f;
	for (DWORD s = 0x75aba4; s <= 0x75b1a4; s += 0x80) fill_str((char *)s, 8, 32, 126);
	int n = irnd(0, 10), tiny = !irnd(0, 3);
	for (int k = 0; k < 10; k++) {
		char *r = (char *)0x9dcef0 + k * 0x44;
		fill(r, 0x44);
		put32(r, (DWORD)(tiny ? irnd(1, 9) : irnd(1, 999)));
		if (k < n) { fill_str(r + 4, tiny ? 1 : 6, 33, 126); if (!r[4]) r[4] = 'A'; } else r[4] = 0;
		int lim = tiny ? 9 : 9999;
		put32(r + 4 + 0x1e, (DWORD)irnd(-lim, lim)); put32(r + 4 + 0x26, (DWORD)irnd(-lim, lim));
		put32(r + 4 + 0x2a, (DWORD)irnd(-lim, lim)); put32(r + 4 + 0x32, (DWORD)irnd(1, 60));
		float a = (float)irnd(-lim * 100, lim * 100) / 10.0f, b = (float)irnd(-lim * 10, lim * 10) / 100.0f;
		memcpy(r + 4 + 0x2e, &b, 4); memcpy(r + 4 + 0x36, &a, 4);
	}
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9dced8) + irnd(0x7d, 0x2e0); G32(0x4ded6c) = G32(0x9dcee4) - irnd(0x10, 0x30); }
}
T_PLAIN(room_43d060, 0x43d060, ranking_setup();, 0, 0, 0, 0, 0)
