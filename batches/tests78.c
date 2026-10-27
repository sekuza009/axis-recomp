/* batch 77 */
/* the skeleton cache (BUF + 0x1000): a tree of 0..9 names from a pool (the input often one of them, in another case
   or with '/'), capacity mostly above the count (sometimes full or 0), format 0..2, a dir or none, data
   memory or none; a miss loads skel_loadFrom_46aa10's (ske, dat) or skel_loadAseFrom's (ase) test file. The dat
   index holds the pool names sorted (one sometimes left out), every item at offset 0 of the VFS file */
static void skelcache_setup(char *self)
{
	static const char *pool[] = { "MECH", "mech_a", "Bone/Walk", "RUN", "run2", "Jump", "IDLE2", "a", "zz", "Arm\\L", "Z9", "_x" };
	enum { NP = 12 };
	char *nodes = BUF + 0x2000, *sk = BUF + 0x3000, up[NP][0x40];
	for (int i = 0; i < NP; i++) {
		strcpy(up[i], pool[i]);
		for (char *c = up[i]; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
	}
	int fmt = irnd(0, 2);                          /* not 3: the "invalid file format(%s)" error passes the number as %s and crashes */
	if (fmt == 1) ase_setup(); else anim_setup();
	g_mockMallocFail = 0;
	fill(self, 0x130);
	if (irnd(0, 1)) strcpy(self + 0x10, "Data\\Skel"); else self[0x10] = 0;
	int cnt = irnd(0, 9), used[NP] = { 0 }, n = 0;
	fill(nodes, 12 * 0x4c);
	for (int i = 0; i < cnt; i++) {
		int k = irnd(0, NP - 1);
		if (used[k]) continue;
		used[k] = 1;
		char *e = nodes + n * 0x4c;
		strcpy(e, up[k]); S32(e, 0x40) = n; S32(e, 0x44) = 0; S32(e, 0x48) = 0;
		for (char *p = nodes; n; ) {                         /* link it below the root */
			int r = strcmp(e, p), off = r < 0 ? 0x44 : 0x48;
			if (!S32(p, off)) { S32(p, off) = (int)e; break; }
			p = (char *)S32(p, off);
		}
		n++;
	}
	S32(self, 0x110) = fmt; S32(self, 0x118) = (int)nodes; S32(self, 0x11c) = (int)sk; S32(self, 0x120) = n;
	S32(self, 0x114) = irnd(0, 19) ? (irnd(0, 9) ? n + irnd(1, 3) : n) : 0;
	fill(sk, 12 * 0x24);
	for (int i = 0; i < 12; i++) S32(sk + i * 0x24, 0xc) = 0;
	if (irnd(0, 1)) { S32(self, 0x128) = (int)(BUF + 0x400000); S32(self, 0x124) = 0x40000; S32(self, 0x12c) = irnd(0, 3) * 0x100; }
	else S32(self, 0x128) = 0;
	fill(BUF + 0x400000, 0x1000);
	/* the dat index: the pool names sorted, one sometimes left out, and the extra entry read at [count] */
	char *t = BUF + 0x10000; int m = 0, skip = irnd(0, 1) ? irnd(0, NP - 1) : -1;
	char srt[NP][0x40]; memcpy(srt, up, sizeof srt);
	for (int i = 0; i < NP; i++) for (int j = i + 1; j < NP; j++)
		if (strcmp(srt[j], srt[i]) < 0) { char x[0x40]; strcpy(x, srt[i]); strcpy(srt[i], srt[j]); strcpy(srt[j], x); }
	for (int i = 0; i < NP; i++) {
		if (skip >= 0 && !strcmp(srt[i], up[skip])) continue;
		strcpy(t + m * 0x44, srt[i]); S32(t + m * 0x44, 0x40) = 0; m++;
	}
	strcpy(t + m * 0x44, "\x7f\x7f"); S32(t + m * 0x44, 0x40) = 0;
	G32(0xa0eab4) = m; G32(0xa0eab8) = (int)t; G32(0xa0eabc) = (int)VFS_FILE(0);
	/* the name: a pool one (as written, upper-cased, or a tree one), an empty one, one starting with '.', or random */
	char *nm = BUF + 0x300; int c = irnd(0, 9);
	if (c < 6) strcpy(nm, pool[irnd(0, NP - 1)]);
	else if (c < 8 && n) strcpy(nm, nodes + irnd(0, n - 1) * 0x4c);
	else if (c == 8) strcpy(nm, irnd(0, 1) ? "" : ".ske");
	else fill_str(nm, 20, 33, 126);
	g_a[0] = (int)nm;
}
ST(skel_getSkeletonPtrBy, skelcache_setup(BUF + 0x1000);, TC(int, 0x46b1a0, char *, char *)(BUF + 0x1000, (char *)g_a[0]),
   skel_getSkeletonPtrBy(BUF + 0x1000, (DWORD)g_a[0]))
