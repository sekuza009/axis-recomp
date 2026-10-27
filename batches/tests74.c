/* batch 73 */
/* a generated ASE file: the scene block (frame speed and ticks per frame never 0: the original divides by them),
   then up to 4 GEOMOBJECTs with names, parents (an earlier bone, none, or rarely a missing one: fatal), node
   transforms and animation tracks (TCB or Bezier position keys, TCB rotation keys, 0..4 each) with plain or odd
   numbers; memory allocated or given (sometimes too small: fatal) */
static char *ase_num(char *p, int lo, int hi)
{
	int k = irnd(0, 19);
	if (k == 0) return p + sprintf(p, " %d", irnd(-99999, 99999));
	if (k == 1) return p + sprintf(p, " 1e%d", irnd(-40, 40));
	return p + sprintf(p, " %d.%04d", irnd(lo, hi), irnd(0, 9999));
}
static void ase_setup(void)
{
	char *f = BUF + 0x200000, *p = f; int nb = irnd(0, 4);
	p += sprintf(p, "*3DSMAX_ASCIIEXPORT\t200\n*SCENE {\n\t*SCENE_LASTFRAME %d\n\t*SCENE_FRAMESPEED %d\n\t*SCENE_TICKSPERFRAME %d\n}\n",
	             irnd(0, 200), irnd(1, 60), irnd(1, 4) * 80);
	for (int b = 0; b < nb; b++) {
		p += sprintf(p, "*GEOMOBJECT {\n\t*NODE_NAME \"bone%d\"\n", b);
		int par = irnd(0, 2) ? irnd(-1, b - 1) : (irnd(0, 9) ? -1 : 7);
		if (par >= 0) p += sprintf(p, "\t*NODE_PARENT \"bone%d\"\n", par);
		p += sprintf(p, "\t*NODE_TM {\n\t\t*NODE_NAME \"bone%d\"\n\t\t*TM_POS", b); p = ase_num(p, -50, 50); p = ase_num(p, -50, 50); p = ase_num(p, -50, 50);
		p += sprintf(p, "\n\t\t*TM_ROTAXIS"); p = ase_num(p, -1, 0); p = ase_num(p, -1, 0); p = ase_num(p, 0, 1);
		p += sprintf(p, "\n\t\t*TM_ROTANGLE"); p = ase_num(p, -3, 3); p += sprintf(p, "\n\t}\n\t*TM_ANIMATION {\n");
		int np = irnd(0, 4), nr = irnd(0, 4), bez = irnd(0, 1), t = 0;
		if (np || irnd(0, 1)) {
			p += sprintf(p, "\t\t*CONTROL_POS_TRACK {\n\t\t\t*%s {\n", bez ? "CONTROL_POS_BEZIER" : "CONTROL_POS_TCB");
			for (int k = 0; k < np; k++) {
				t += irnd(0, 3) * 160; p += sprintf(p, "\t\t\t\t*%s %d", bez ? "CONTROL_BEZIER_POS_KEY" : "CONTROL_TCB_POS_KEY", t);
				for (int i = 0; i < 3; i++) p = ase_num(p, -50, 50);
				p += sprintf(p, "\n");
			}
			p += sprintf(p, "\t\t\t}\n\t\t}\n");
		}
		if (nr || irnd(0, 1)) {
			t = 0; p += sprintf(p, "\t\t*CONTROL_ROT_TRACK {\n\t\t\t*CONTROL_ROT_TCB {\n");
			for (int k = 0; k < nr; k++) {
				t += irnd(0, 3) * 160; p += sprintf(p, "\t\t\t\t*CONTROL_TCB_ROT_KEY %d", t);
				for (int i = 0; i < 3; i++) p = ase_num(p, -1, 1);
				p = ase_num(p, -3, 3); p += sprintf(p, "\n");
			}
			p += sprintf(p, "\t\t\t}\n\t\t}\n");
		}
		p += sprintf(p, "\t}\n}\n");
	}
	g_vfsData = (BYTE *)f; g_vfsSize = (DWORD)(p - f);
	char *sk = BUF + 0x100; fill(sk, 0x40); S32(sk, 0xc) = 0;
	int need = nb * 0x70 + 4 * nb * (0x20 + 0x28);
	g_a[0] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; g_a[1] = irnd(0, 5) ? need + 0x100 : irnd(0, need);
	fill(BUF + 0x400000, 0x1000);
	g_paintStacks = 1;                         /* a singular parent matrix: Mat4_invert leaves the inverse unwritten (stack) */
}
ST(skel_loadAseFrom, ase_setup();, (TC(void, 0x469b90, char *, int, int, int)(BUF + 0x100, (int)VFS_FILE(0), g_a[0], g_a[1]), 0),
   (skel_loadAseFrom(BUF + 0x100, VFS_FILE(0), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
