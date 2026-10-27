/* batch 62 */
/* an open BMP (VFS_FILE(1), data at 54, up to 40 x 40) and a destination of up to 48 x 48; the block and both
   positions are often partly outside; a short file leaves the row buffer as it was (painted stack) */
static int g_ca[10];                       /* image_copyTo has more arguments than g_a holds */
static void copyto_setup(void)
{
	char *img = BUF + 0x100;
	fill(img, 0x50); S32(img, 4) = (int)VFS_FILE(1); S32(img, 0x12) = 54;
	S32(img, 0x3e) = irnd(0, 40); S32(img, 0x42) = irnd(0, 40);
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = 54 + 40 * 40 * 3;
	fill(d, n); g_vfsData = d; g_vfsSize = (DWORD)(irnd(0, 5) ? n : irnd(0, n));
	g_ca[0] = irnd(1, 48); g_ca[1] = irnd(1, 48); g_ca[2] = irnd(0, 9) ? irnd(3, 4) : irnd(0, 6);
	for (int i = 3; i < 7; i++) g_ca[i] = irnd(-20, 50);
	g_ca[7] = irnd(-10, 60); g_ca[8] = irnd(-10, 60); g_ca[9] = irnd(0, 1);
	fill(BUF + 0x300000, 48 * 48 * 4);
	g_paintStacks = 1;
}
ST(image_copyTo, copyto_setup();,
   (TC(void, 0x46ce80, char *, char *, int, int, int, int, int, int, int, int, int, int)(BUF + 0x100, BUF + 0x300000, g_ca[0], g_ca[1], g_ca[2],
     g_ca[3], g_ca[4], g_ca[5], g_ca[6], g_ca[7], g_ca[8], g_ca[9]), 0),
   (image_copyTo(BUF + 0x100, (DWORD)(BUF + 0x300000), (DWORD)g_ca[0], (DWORD)g_ca[1], (DWORD)g_ca[2], (DWORD)g_ca[3], (DWORD)g_ca[4],
     (DWORD)g_ca[5], (DWORD)g_ca[6], (DWORD)g_ca[7], (DWORD)g_ca[8], (DWORD)g_ca[9]), 0))
/* short names from a small alphabet, so that index lookups hit often */
static void tex_token(char *s) { int n = irnd(1, 3); for (int i = 0; i < n; i++) s[i] = (char)irnd('A', 'D'); s[n] = 0; }
static int tex_cmp(const void *a, const void *b) { return strcmp((const char *)a, (const char *)b); }
/* the manager at BUF + 0x100: directory, format, size; a sorted index of names formatted
   the way the lookup formats them; one file serving as both the BMP and the RAW header (RAW sizes at 6 / 8) */
static void texexist_setup(void)
{
	static const int sz[3] = { 64, 128, 256 };
	char *tm = BUF + 0x100;
	fill(tm, 0x200); fill(tm + 0xc0100, 0x40);
	if (irnd(0, 1)) tm[8] = 0; else fill_str(tm + 8, 12, 'A', 'Z');
	S32(tm, 0xc0114) = irnd(0, 2);   /* another format is fatal with the number printed as %s (the original crashes) */
	int w = sz[irnd(0, 2)], h = sz[irnd(0, 2)];
	S32(tm, 0xc0118) = w; S32(tm, 0xc011c) = h;
	int n = irnd(0, 8); char *items = BUF + 0x10000;
	fill(items, 8 * 0x44);
	for (int i = 0; i < n; i++) {
		char t[8]; tex_token(t);
		if (tm[8]) sprintf(items + i * 0x44, (const char *)0x4b3fdc, tm + 8, t); else sprintf(items + i * 0x44, (const char *)0x4b3fd8, t);
	}
	qsort(items, (size_t)n, 0x44, tex_cmp);
	S32(tm, 0x108) = n; S32(tm, 0x10c) = (int)items;
	tex_token(BUF + 0x300); if (!irnd(0, 3)) strcat(BUF + 0x300, ".BMP");
	BYTE *d = (BYTE *)(BUF + 0x200000);
	fill(d, 0x80); d[0] = 'B'; d[1] = 'M'; *(DWORD *)(d + 10) = 54;
	*(short *)(d + 6) = (short)(irnd(0, 3) ? w / 8 : irnd(0, 40)); *(short *)(d + 8) = (short)(irnd(0, 3) ? h / 8 : irnd(0, 40));
	*(int *)(d + 18) = irnd(0, 3) ? w : irnd(0, 300); *(int *)(d + 22) = irnd(0, 3) ? h : irnd(0, 300);
	*(WORD *)(d + 28) = 24; *(DWORD *)(d + 30) = 0;
	g_vfsData = d; g_vfsSize = 0x80; g_vfsOpenFail = !irnd(0, 5);
	g_paintStacks = 1;
}
ST(tex_textureFileExist, texexist_setup();, TC(DWORD, 0x4557e0, char *, char *)(BUF + 0x100, BUF + 0x300), tex_textureFileExist(BUF + 0x100, (DWORD)(BUF + 0x300)))
/* a directory argument: none, the empty string the code compares with, or a path with lower case and slashes */
static DWORD dir_arg(void)
{
	int k = irnd(0, 3);
	if (k == 0) return 0;
	if (k == 1) return 0x4b1304;
	fill_str(BUF + 0x380, 30, '/', 'z');
	return (DWORD)(BUF + 0x380);
}
/* a manager (maybe already initialised: fatal), the dat index file (count 0..10, entries), slot counts mostly
   small, sometimes over the 0x200 limit; a stale count at +0x108 for a file that does not open */
static void texinit_setup(void)
{
	static const int sz[4] = { 64, 128, 256, 32 };
	char *tm = BUF + 0x100;
	fill(tm, 0x200); fill(tm + 0xc0100, 0x40); fill(tm + 0xcd120, 0x30);
	S32(tm, 4) = irnd(0, 9) ? 0 : 1; S32(tm, 0x108) = irnd(0, 5);
	g_a[0] = (int)dir_arg();
	g_a[1] = irnd(0, 9) ? irnd(0, 40) : irnd(0x1fe, 0x203);
	g_a[2] = irnd(0, 3) ? 0 : irnd(1, 2);
	g_a[3] = sz[irnd(0, 3)]; g_a[4] = sz[irnd(0, 3)]; g_a[5] = irnd(0, 1000); g_a[6] = irnd(0, 1000);
	BYTE *d = (BYTE *)(BUF + 0x200000); int n = irnd(0, 10);
	*(int *)d = n; fill(d + 4, n * 0x44);
	g_vfsData = d; g_vfsSize = (DWORD)(4 + n * 0x44); g_vfsOpenFail = !irnd(0, 8);
}
ST(tex_initBy, texinit_setup();,
   (TC(void, 0x455080, char *, int, int, int, int, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5], g_a[6]), 0),
   (tex_initBy(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5], (DWORD)g_a[6]), 0))
/* a data-memory object (not owning memory), n entries, extra bytes, memory given (sometimes too small) or allocated */
static void datamem_setup(void)
{
	fill(BUF + 0x100, 0x260); S32(BUF + 0x100, 0xc) = 0;
	g_a[0] = (int)dir_arg(); g_a[1] = irnd(0, 20); g_a[2] = irnd(0, 1000); g_a[3] = irnd(0, 0x400);
	g_a[4] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[5] = irnd(0, 4) ? 0x40000 : irnd(0, 0x800);
}
ST(shape_initBy, datamem_setup();,
   (TC(void, 0x466a60, char *, int, int, int, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5]), 0),
   (shape_initBy(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5]), 0))
ST(skel_loadFrom_46aeb0, datamem_setup();,
   (TC(void, 0x46aeb0, char *, int, int, int, int, int, int)(BUF + 0x100, g_a[0], g_a[1], g_a[2], g_a[3], g_a[4], g_a[5]), 0),
   (skel_loadFrom_46aeb0(BUF + 0x100, (DWORD)g_a[0], (DWORD)g_a[1], (DWORD)g_a[2], (DWORD)g_a[3], (DWORD)g_a[4], (DWORD)g_a[5]), 0))
