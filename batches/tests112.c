/* batch 111 */
/* the ground file (second VFS content "G1.gnd", built at BUF + 0x2200000, scrambled after the version): random sky
   modes, 0..3 lights of types 0..2, 0..3 layers of 1..12 x 1..12 cells (grey heights mostly), a full 256-row height
   map each (a short read would leave stack in the buffer). Every texture name the function may ask for is in the
   texture manager's dat index (moved to BUF + 0xd8000: a bound texture's pixels land in the manager's image buffer,
   where texpath_index keeps it), format 0, no dir; load_497a90's mesh fields as meshes_setup's */
static void ground_scramble(BYTE *p, int n) { for (int i = 0; i < n; i++) { BYTE c = p[i]; p[i] = (BYTE)(((c >> 1) | (c << 7)) ^ 0x59); } }
static void groundfile_setup(void)
{
	static const char *one[] = { "SphereFloor", "SphereCeiling", "SphereEast", "SphereSouth", "SphereWest", "SphereNorth",
	                             "SkyInnerLayer", "SkyOuterLayer" };
	char dir[16], names[48][64]; int nn = 0;
	strcpy(dir, irnd(0, 1) ? "Map1" : "Stage03");
	for (int k = 0; k < 8; k++) sprintf(names[nn++], "%s/%s", dir, one[k]);
	for (int k = 0; k <= 6; k++) sprintf(names[nn++], "%s/SideLayer%d", dir, k);
	for (int k = 0; k <= 16; k++) sprintf(names[nn++], "%s/FloorAni%02d", dir, k);
	for (int k = 0; k <= 3; k++) sprintf(names[nn++], "%s/Ground%dMap", dir, k);
	/* the texture set and its index (all names, upper-cased, '/' -> '\', sorted, one sometimes missing) */
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	S32(BUF, 0xc0114) = 0; BUF[8] = 0; S32(BUF, 0xcd130) = irnd(0, 30);
	char up[48][64]; int miss = irnd(0, 9) ? -1 : irnd(0, nn - 1), m = 0;
	for (int k = 0; k < nn; k++) {
		if (k == miss) continue;
		strcpy(up[m], names[k]);
		for (char *c = up[m]; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
		m++;
	}
	for (int a = 0; a < m; a++) for (int b = a + 1; b < m; b++)
		if (strcmp(up[b], up[a]) < 0) { char x[64]; strcpy(x, up[a]); strcpy(up[a], up[b]); strcpy(up[b], x); }
	char *ix = BUF + 0xd8000;
	for (int k = 0; k < m; k++) { memset(ix + k * 0x44, 0, 0x44); strcpy(ix + k * 0x44, up[k]); }
	strcpy(ix + m * 0x44, "\x7f");
	S32(BUF, 0x108) = m; S32(BUF, 0x10c) = (int)ix;
	/* load_497a90's buffers */
	meshes_setup();
	/* the file */
	BYTE *d = (BYTE *)(BUF + 0x2200000); int len = 4, nl = irnd(0, 3);
	*(DWORD *)d = irnd(0, 29) ? 0x1201 : 0x1200;
	for (int b = 0; b < 4; b++) { int n = irnd(0, 16); *(int *)(d + len) = n; len += 4; fill(d + len, n); len += n; }
	memset(d + len, 0, 0x100); strcpy((char *)d + len, dir); len += 0x100;
	SF(d, len) = (float)irnd(100, 5000); len += 4;
	int nlight = irnd(0, 3);                                 /* load_483d70: two counts, the records, one more dword */
	*(int *)(d + len) = nlight; *(int *)(d + len + 4) = irnd(0, 3); len += 8;
	for (int k = 0; k < nlight; k++) {
		BYTE *f = d + len; fill(f, 0x2c);
		for (int a = 0; a < 0x2c; a += 4) SF(f, a) = (float)irnd(-1200, 1200) / 10.0f;
		*(int *)(f + 8) = irnd(0, 2);                       /* the light type (layerlight_setup's +0x9cd008) */
		len += 0x2c;
	}
	*(int *)(d + len) = irnd(0, 1); len += 4;
	for (int k = 0; k < 13; k++) { SF(d, len) = (float)irnd(0, 1000) / 1000.0f; len += 4; }   /* clear colour, fog */
	S32(d, len - 12) = irnd(0, 0xffffff);                    /* the fog colour (+0x9ee058) */
	*(int *)(d + len) = irnd(0, 2); len += 4; *(int *)(d + len) = irnd(0, 2); len += 4;     /* sphere, sky */
	*(int *)(d + len) = irnd(0, 3); len += 4; *(int *)(d + len) = irnd(0, 3); len += 4;     /* side, floor */
	for (int k = 0; k < 15; k++) { SF(d, len) = (float)irnd(0, 1000) / 1000.0f; len += 4; } /* ground colours */
	*(int *)(d + len) = nl; len += 4;
	for (int l = 0; l < nl; l++) {
		BYTE *h = d + len; int rows = irnd(1, 12), cols = irnd(1, 12);
		for (int a = 0; a < 0x20c; a += 4) SF(h, a) = (float)irnd(1, 1000) / 10.0f;
		*(int *)h = irnd(0, 1); *(int *)(h + 0x1c) = rows; *(int *)(h + 0x20) = cols; *(int *)(h + 0x30) = irnd(0, 1);
		len += 0x20c;
		BYTE *px = d + len;
		for (int r = 0; r < 256; r++) for (int c = 0; c < 256; c++) {
			BYTE *q = px + r * 0x300 + c * 3;
			if (r <= rows + 1 && c <= cols + 1) { BYTE v = (BYTE)irnd(0, 255); q[0] = v; q[1] = irnd(0, 9) ? v : (BYTE)irnd(0, 255); q[2] = v; }
			else q[0] = q[1] = q[2] = 0;
		}
		len += 0x30000;
	}
	ground_scramble(d + 4, len - 4);
	g_vfsAltName = "G1.gnd"; g_vfsAltData = d; g_vfsAltSize = (DWORD)len;
	g_vfsOpenFail = 0; g_vfsFailMask = !irnd(0, 29);
	strcpy(BUF + 0x87ff00, "G1.gnd");
	fill(BUF + 0xdc0240, 4); fill(BUF + 0x9ee030, 0x40);
	g_a[0] = (int)(BUF + 0x87ff00);
	g_paintStacks = 1;
}
static int g_groundDone;
static DWORD groundfile_orig(void) { TC(int, 0x48b9d0, char *, char *)(BUF, (char *)g_a[0]); g_groundDone++; return 1; }
ST(map_loadGroundInfoFrom, groundfile_setup();, groundfile_orig(), map_loadGroundInfoFrom(BUF, (DWORD)g_a[0]))
