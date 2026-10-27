/* batch 123 */
/* the options dialog: dlgwin_setup's window at 0x4dddd0, its labels, the six value tables (filled at run time in
   the game: here two short entries each) and settings 0..1, a resolution 0..7, the cursor sometimes on a value */
static void options_setup(void)
{
	dlgwin_setup(0x4dddd0);
	fill((void *)0x4de048, 16); fill((void *)0x4ddae0, 16);
	fill_str((char *)0x7538a4, 20, 32, 126);
	for (int k = 0; k < 7; k++) fill_str((char *)0x753924 + k * 0x80, 12, 32, 126);
	for (int k = 0; k < 2; k++) fill_str((char *)0x753ca4 + k * 0x80, 12, 32, 126);
	static const DWORD tab[] = { 0x4ddbbc, 0x4dda64, 0x4ddc84, 0x4de058, 0x4ddc20, 0x4ddaf0 };
	for (int t = 0; t < 6; t++) {
		for (int k = 0; k < 2; k++) fill_str((char *)tab[t] + k * 0x32, 12, 32, 126);
		G32(0x4ddba4 + t * 4) = irnd(0, 1);
	}
	G32(0x4ddba0) = irnd(0, 7);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x4dddd0) + irnd(0xe0, 0x160); G32(0x4ded6c) = G32(0x4dddd4) + 0x40 + irnd(0, 6) * 0x28 + irnd(0, 12); }
}
T_PLAIN(setup_425460, 0x425460, options_setup();, 0, 0, 0, 0, 0)
