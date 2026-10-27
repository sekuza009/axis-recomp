/* batch 80 */
/* a texture manager (BUF): format 0..2 (rarely 3), dir or none, texture i's name with or without a "*" tail, its
   size mostly the image's. Format 0: a dat index (BUF + 0x200) of the name and, each often, its _ALPHA / _COLOR
   items between decoys, all at offset 0 of the dat file (ptxfile_setup's PTX). Format 2: the same PTX through
   fopen. Format 1: a 24-bit BMP of up to 64 x 64. fopen attempts fail by mask (the first rarely) */
static void texmask_setup(void)
{
	char *tm = BUF;
	int fmt = irnd(0, 19) ? irnd(0, 2) : 3, w, h;
	if (fmt == 1) {
		BYTE *d = (BYTE *)(BUF + 0x200000);
		w = irnd(1, 64); h = irnd(1, 64);
		int row = (w * 3 + 3) & ~3, n = 54 + row * h;
		fill(d, n); memset(d, 0, 54); d[0] = 'B'; d[1] = 'M'; *(DWORD *)(d + 2) = (DWORD)n; *(DWORD *)(d + 10) = 54;
		*(DWORD *)(d + 14) = 40; *(int *)(d + 18) = w; *(int *)(d + 22) = h; *(WORD *)(d + 26) = 1; *(WORD *)(d + 28) = 24;
		g_vfsData = d; g_vfsSize = (DWORD)n;
		if (irnd(0, 2)) { w = irnd(1, 64); h = irnd(1, 64); }        /* the copy clips to the texture's size */
	} else {
		ptxfile_setup();
		BYTE *f = (BYTE *)g_vfsData;
		w = *(short *)(f + 6) * 8; h = *(short *)(f + 8) * 8;
		if (!irnd(0, 19)) w += 8;
	}
	g_vfsOpenFail = 0; g_vfsFailMask = (DWORD)(irnd(0, 29) ? 0 : 1) | (DWORD)irnd(0, 3) << 1;
	fill(tm, 0x200);
	if (irnd(0, 1)) strcpy(tm + 8, "Data\\Tex"); else tm[8] = 0;
	int i = irnd(0, 20);
	char *nm = tm + 0xc0128 + i * 0x68;
	strcpy(nm, irnd(0, 1) ? "TEX1" : "WALL_B2"); if (irnd(0, 2) == 0) strcat(nm, "*7");
	S32(tm, 0xc0114) = fmt; S32(tm, 0xc0118) = w; S32(tm, 0xc011c) = h;
	/* the dat index: decoys and the texture's items, sorted (one more record past the count) */
	char full[0x80], names[8][0x44]; int n = 0;
	{ char base[0x40]; strcpy(base, nm); char *s = strchr(base, '*'); if (s) *s = 0;
	  if (tm[8]) sprintf(full, "%s\\%s", tm + 8, base); else strcpy(full, base); }
	if (irnd(0, 19)) strcpy(names[n++], full);
	if (irnd(0, 1)) sprintf(names[n++], "%s_ALPHA", full);
	if (irnd(0, 1)) sprintf(names[n++], "%s_COLOR", full);
	strcpy(names[n++], "A0"); sprintf(names[n++], "%s_B", full); strcpy(names[n++], "Data\\Tex\\Z");
	for (int a = 0; a < n; a++) for (int b = a + 1; b < n; b++)
		if (strcmp(names[b], names[a]) < 0) { char x[0x44]; strcpy(x, names[a]); strcpy(names[a], names[b]); strcpy(names[b], x); }
	S32(tm, 0x108) = n; S32(tm, 0x10c) = (int)(BUF + 0x200); S32(tm, 0x110) = (int)VFS_FILE(0);
	for (int k = 0; k < n; k++) { strcpy(BUF + 0x200 + k * 0x44, names[k]); S32(BUF + 0x200 + k * 0x44, 0x40) = 0; }
	strcpy(BUF + 0x200 + n * 0x44, "\x7f"); S32(BUF + 0x200 + n * 0x44, 0x40) = 0;
	for (int k = 0; k < 3; k++) fill(tm + 0x114 + k * 0x40000, 0x4000);
	fill((void *)0xa1f238, 4); G32(0xa0e00c) = irnd(0, 1);
	g_a[0] = i;
}
ST(tex_loadColorMask, texmask_setup();, (TC(void, 0x455aa0, char *, int)(BUF, g_a[0]), 0), (tex_loadColorMask(BUF, (DWORD)g_a[0]), 0))
