/* batch 81 */
/* tex_loadColorMask's test manager with 21 texture records (flags 0..3, tint colours, reload flag) and a ring of
   1..6 GL slots owned by distinct textures (texture i among them half the time) */
static void texbind_setup(void)
{
	texmask_setup();
	char *tm = BUF, *slots = BUF + 0xd0000; int i = g_a[0], n = irnd(1, 6), own[6];
	for (int t = 0; t <= 20; t++) {
		char *r = tm + t * 0x68;
		S32(r, 0xc0168) = -1; *(BYTE *)(r + 0xc016c) = (BYTE)irnd(0, 3); fill(r + 0xc016d, 3);
		for (int k = 0; k < 2; k++) {
			GF(r + 0xc0170 + k * 12) = (float)irnd(-4000, 8000) / 10.0f; GF(r + 0xc0174 + k * 12) = unit_rnd(); GF(r + 0xc0178 + k * 12) = unit_rnd();
		}
		S32(r, 0xc018c) = irnd(0, 3) ? 0 : 1;
	}
	for (int k = 0; k < n; k++) {
		int t, dup;
		do { t = k == 0 && irnd(0, 1) ? i : irnd(0, 20); dup = 0; for (int j = 0; j < k; j++) dup |= own[j] == t; } while (dup);
		own[k] = t;
	}
	for (int k = n - 1; k > 0; k--) { int j = irnd(0, k), x = own[k]; own[k] = own[j]; own[j] = x; }
	for (int k = 0; k < n; k++) {
		char *s = slots + k * 0x14;
		S32(s, 0) = k; S32(s, 4) = own[k]; S32(s, 8) = irnd(1, 500);
		S32(s, 0xc) = (int)(slots + (k + 1) % n * 0x14); S32(s, 0x10) = (int)(slots + (k + n - 1) % n * 0x14);
		S32(tm + own[k] * 0x68, 0xc0168) = k;
	}
	S32(tm, 0xcd12c) = (int)slots; S32(tm, 0xcd134) = (int)(slots + irnd(0, n - 1) * 0x14); S32(tm, 0xcd138) = irnd(0, 1000);
	S32(tm, 0xc0120) = irnd(0, 1); S32(tm, 0xc0124) = irnd(0, 1);
}
ST(tex_bind, texbind_setup();, (TC(void, 0x4566c0, char *, int)(BUF, g_a[0]), 0), (tex_bind(BUF, (DWORD)g_a[0]), 0))
