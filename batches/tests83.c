/* batch 82 */
/* tex_bind's test manager: texture i (the one its files describe) is the next free record (count = i), the records
   before it have short names (tex_token, one sometimes texture i's). The name asked for is texture i's or an
   existing one, as stored or in lower case, or empty; flags and colours mostly a record's own (one changed half
   the time); bound at once below a random limit */
static void texalloc_setup(void)
{
	texbind_setup();
	char *tm = BUF; int i = g_a[0];
	char *nm = tm + 0xc0128 + i * 0x68, want[0x40];
	strcpy(want, nm);
	for (int t = 0; t < i; t++) tex_token(tm + 0xc0128 + t * 0x68);
	if (i && !irnd(0, 9)) strcpy(tm + 0xc0128 + irnd(0, i - 1) * 0x68, want);
	S32(tm, 0xcd128) = i; S32(tm, 0xcd130) = irnd(0, 30);
	if (S32(tm, 0xc0114) == 3) S32(tm, 0xc0114) = 0;     /* tex_textureFileExist prints another format as %s and crashes */
	int c = irnd(0, 9), src = -1;
	char *q = BUF + 0x400100;                       /* outside the manager's image buffers */
	if (c < 5) strcpy(q, want);
	else if (c < 8 && i) { src = irnd(0, i - 1); strcpy(q, tm + 0xc0128 + src * 0x68); }
	else if (c == 8) q[0] = 0;
	else strcpy(q, "NOPE");                          /* in no index: no file */
	if (irnd(0, 1)) for (char *p = q; *p; p++) if (*p >= 'A' && *p <= 'Z') *p += 0x20;
	g_a[0] = (int)q;
	char *r = tm + (src >= 0 ? src : irnd(0, 20)) * 0x68;
	g_a[1] = S32(r, 0xc016c);
	for (int k = 0; k < 6; k++) g_a[2 + k] = S32(r, 0xc0170 + k * 4);
	if (irnd(0, 1)) { int k = irnd(1, 7); if (k == 1) g_a[1] = irnd(0, 3); else GF(&g_a[k]) = (float)irnd(-500, 500) / 100.0f; }
}
ST(tex_allocIdBy, texalloc_setup();,
   TC(int, 0x4555b0, char *, int, int, int, int, int, int, int, int)(BUF, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   tex_allocIdBy(BUF, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7]))
/* the six managers' slots (BUF + 0x400000): the test manager in one of them, the others empty */
static void texset_setup(void)
{
	texalloc_setup();
	char *set = BUF + 0x400000; int k = irnd(0, 5);
	fill(set, 4);
	for (int j = 0; j < 6; j++) S32(set, 4 + j * 4) = j == k ? (int)BUF : 0;
}
ST(tex_getIdByName, texset_setup();,
   TC(int, 0x456be0, char *, int, int, int, int, int, int, int, int)(BUF + 0x400000, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6], g_a[7]),
   tex_getIdByName(BUF + 0x400000, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6], (DWORD)g_a[7]))
