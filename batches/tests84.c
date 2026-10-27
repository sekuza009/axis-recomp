/* batch 83 */
/* a shape (BUF + 0x500000) of 0..4 parts in the texture set of tex_getIdByName's test (also at 0xa0e010). Binding
   by name: part names are the existing records' (some with a "*" tail), texture i's (new) or unknown ones, the
   suffix empty or short (rarely too long); flags and colours from texalloc_setup */
static void shapebind_setup(void)
{
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	char *tm = BUF, *sh = BUF + 0x500000; int n = irnd(0, 4), cnt = S32(tm, 0xcd128);
	fill(sh, 0x20); S32(sh, 0x10) = n; S32(sh, 0x14) = (int)(sh + 0x100);
	for (int p = 0; p < n; p++) {
		char *pt = sh + 0x100 + p * 0x80; int c = irnd(0, 9);
		fill(pt, 0x80);
		if (c < 6 && cnt) strcpy(pt + 4, tm + 0xc0128 + irnd(0, cnt - 1) * 0x68);
		else if (c < 8) strcpy(pt + 4, tm + 0xc0128 + S32(tm, 0xcd128) * 0x68);
		else strcpy(pt + 4, irnd(0, 1) ? "NOPE" : "");
	}
	if (cnt && irnd(0, 1)) strcat(tm + 0xc0128 + irnd(0, cnt - 1) * 0x68, "*S");
	char *s = sh + 0x80;                            /* not in the image buffer (BUF + 0x114...): a bind decodes over it */
	int k = irnd(0, 9);
	if (k < 4) s[0] = 0; else if (k < 9) strcpy(s, irnd(0, 1) ? "S" : "RED2");
	else { memset(s, 'Q', 64); s[64] = 0; }   /* fatal: too long. Exactly 63 + "*" would overflow tex_allocIdBy's 64-byte copy in the original */
	g_a[0] = (int)s;
}
ST(shape_bindTextureBy, shapebind_setup();,
   (TC(void, 0x466430, char *, int, int, int, int, int, int, int, int)(BUF + 0x500000, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]), 0),
   (shape_bindTextureBy(BUF + 0x500000, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7]), 0))
/* binding a shape's parts: materials of the test manager's slot in the set (textures with a GL slot, which just
   bind unless flagged for reload, or texture i, loaded from its files), or none (-1) */
static void shapetex_setup(void)
{
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	char *tm = BUF, *sh = BUF + 0x500000; int n = irnd(0, 5), k = 0, i = S32(tm, 0xcd128);
	while (S32(BUF + 0x400000, 4 + k * 4) != (int)BUF) k++;
	S32(tm, 0xcd128) = 21;
	fill(sh, 0x20); S32(sh, 0x10) = n; S32(sh, 0x14) = (int)(sh + 0x100);
	for (int p = 0; p < n; p++) {
		char *pt = sh + 0x100 + p * 0x80, *sl = (char *)S32(tm, 0xcd134); int c = irnd(0, 9), t;
		fill(pt, 0x80);
		for (int j = irnd(0, 5); j; j--) sl = (char *)S32(sl, 0xc);       /* a slot of the ring */
		t = c < 6 ? S32(sl, 4) : c < 9 ? i : -1;
		S32(pt, 0x44) = t >= 0 ? k * 512 + t : -irnd(1, 600);
	}
}
ST(FUN_00466650, shapetex_setup();, (TC(void, 0x466650, char *)(BUF + 0x500000), 0), (FUN_00466650(BUF + 0x500000), 0))
