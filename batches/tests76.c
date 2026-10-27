/* batch 75 */
/* a generated OBJ file: sometimes a "3DS" comment, 3..8 positions, normals and texture coordinates, then 1..3 parts
   (usemtl with names of one to three "_" pieces), each with 0..3 faces of 3 or 4 corners (indices mostly in range,
   sometimes a "\" continuation line, rarely only 2 corners: fatal); memory allocated or given (sometimes too small:
   fatal); stacks painted */
static char *obj_num(char *p)
{
	int k = irnd(0, 29);
	if (k == 0) return p + sprintf(p, " %d", irnd(-99999, 99999));
	if (k == 1) return p + sprintf(p, " 1e%d", irnd(-40, 40));
	return p + sprintf(p, " %d.%03d", irnd(-50, 50), irnd(0, 999));
}
static void obj_setup(void)
{
	char *f = BUF + 0x200000, *p = f;
	int nv = irnd(3, 8), nn = irnd(3, 8), nt = irnd(3, 8), np = irnd(1, 3), tris = 0;
	if (irnd(0, 1)) p += sprintf(p, "# Exported by an OBJ writer\n");
	for (int i = 0; i < nv; i++) { p += sprintf(p, "v"); for (int k = 0; k < 3; k++) p = obj_num(p); p += sprintf(p, "\n"); }
	for (int i = 0; i < nn; i++) { p += sprintf(p, "vn"); for (int k = 0; k < 3; k++) p = obj_num(p); p += sprintf(p, "\n"); }
	for (int i = 0; i < nt; i++) { p += sprintf(p, "vt"); for (int k = 0; k < 2; k++) p = obj_num(p); p += sprintf(p, "\n"); }
	for (int q = 0; q < np; q++) {
		int pieces = irnd(1, 3);
		p += sprintf(p, "usemtl ");
		for (int k = 0; k < pieces; k++) p += sprintf(p, "%s%c%d", k ? "_" : "", 'a' + irnd(0, 25), irnd(0, 99));
		p += sprintf(p, "\n");
		for (int fc = irnd(0, 3); fc > 0; fc--) {
			int c = irnd(0, 29) ? irnd(3, 4) : 2;
			p += sprintf(p, "f");
			if (!irnd(0, 6)) p += sprintf(p, " \\\n");
			for (int k = 0; k < c; k++) {
				int ok = irnd(0, 19) != 0;
				p += sprintf(p, " %d/%d/%d", ok ? irnd(1, nv) : irnd(0, nv + 2), ok ? irnd(1, nt) : irnd(0, nt + 2), ok ? irnd(1, nn) : irnd(0, nn + 2));
			}
			p += sprintf(p, "\n");
			tris += c == 4 ? 2 : 1;
		}
	}
	/* a "3DS" comment turns on the 3ds Max fix-up, whose loop over a part's vertices never advances: any part with
	   vertices hangs the original, so only files without faces get one */
	if (!tris && irnd(0, 1)) p += sprintf(p, "# Exported by 3DS MAX\n");
	g_vfsData = (BYTE *)f; g_vfsSize = (DWORD)(p - f);
	char *sh = BUF + 0x100; fill(sh, 0x40); S32(sh, 0xc) = 0;
	int need = np * 0x8c + tris * 3 * 12 * 4 + (nv + nn) * 12 + nt * 8 + 0x100;
	g_a[0] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[1] = irnd(0, 5) ? need : irnd(0, need);
	fill(BUF + 0x400000, 0x2000);
	g_paintStacks = 1;
}
ST(model_loadObjFormatFrom, obj_setup();, (TC(void, 0x464db0, char *, int, int, int)(BUF + 0x100, (int)VFS_FILE(0), g_a[0], g_a[1]), 0),
   (model_loadObjFormatFrom(BUF + 0x100, VFS_FILE(0), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
