/* batch 74 */
/* a binary skeleton (skel_loadFrom_46aa10's test file) or an ASE file (skel_loadAseFrom's), named .ske / .ase in any
   case, or with another, no or a misleading extension ("a.ske\b"); the open sometimes fails */
static void skelfile_setup(void)
{
	static const char *names[] = { "Data\\Skel\\mech.ske", "Data\\Skel\\MECH.SKE", "x.SkE", "Data/anim.ase", "ANIM.ASE", "y.aSe",
	                               "Data\\Skel\\mech.sk", "Data\\noext", "a.ske\\b", "a.ase/b", "Data\\x.skel", ".ase", "z.txt", "" };
	int k = irnd(0, 13), ase = strstr(names[k], "as") || strstr(names[k], "AS") || strstr(names[k], "aS");
	if (ase) { ase_setup(); g_a[0] = irnd(0, 1) ? (int)(BUF + 0x400000) : 0; } else anim_setup();
	strcpy(BUF + 0x300, names[k]);
	g_vfsOpenFail = !irnd(0, 9);
}
ST(skel_loadFrom, skelfile_setup();, (TC(void, 0x4699d0, char *, char *, int, int)(BUF + 0x100, BUF + 0x300, g_a[0], g_a[1]), 0),
   (skel_loadFrom(BUF + 0x100, (DWORD)(BUF + 0x300), (DWORD)g_a[0], (DWORD)g_a[1]), 0))
