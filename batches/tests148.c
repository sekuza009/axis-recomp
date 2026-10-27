/* batch 147 */
/* the menu textures: texset_setup's manager at BUF with a dat index (BUF + 0xd8000, as groundfile_setup's) of all
   31 names (upper-cased, '/' -> '\', sorted; one sometimes left out: fatal), format 0, a random bind limit; the
   loading screen's picture bindable, its progress starting at 0 or 1; the wait's frame counter as intro_41e730's test sets it */
static void introtex_setup(void)
{
	static const char *nm[] = { "iftex/gameconnect", "iftex/menu34", "iftex/cylinder_menu", "iftex/cylinder", "iftex/mouse",
		"iftex/option", "iftex/spiral6", "iftex/spiral5", "iftex/spiral4", "iftex/spiral3", "iftex/spiral2", "iftex/spiral1",
		"iftex/ctrlmenu02", "iftex/ctrlmenu01", "iftex/laddermenu02", "iftex/laddermenu01", "iftex/arenamenu02",
		"iftex/arenamenu01", "iftex/mainmenu02", "iftex/mainmenu01", "iftex/boxscreen", "iftex/corner", "iftex/character",
		"iftex/m2_intro4", "iftex/m2_intro3", "iftex/m2_intro2", "iftex/m2_intro1", "iftex/m_intro4", "iftex/m_intro3",
		"iftex/m_intro2", "iftex/m_intro1" };
	enum { NNAMES = sizeof nm / sizeof nm[0] };
	texset_setup();
	G32(0xa0e010) = (int)(BUF + 0x400000);
	S32(BUF, 0xc0114) = 0; BUF[8] = 0; S32(BUF, 0xcd130) = irnd(0, 40);
	char up[NNAMES][64]; int miss = irnd(0, 9) ? -1 : irnd(0, NNAMES - 1), m = 0;
	for (int k = 0; k < NNAMES; k++) {
		if (k == miss) continue;
		strcpy(up[m], nm[k]);
		for (char *c = up[m]; *c; c++) { if (*c >= 'a' && *c <= 'z') *c -= 0x20; else if (*c == '/') *c = '\\'; }
		m++;
	}
	for (int a = 0; a < m; a++) for (int b = a + 1; b < m; b++)
		if (strcmp(up[b], up[a]) < 0) { char x[64]; strcpy(x, up[a]); strcpy(up[a], up[b]); strcpy(up[b], x); }
	char *ix = BUF + 0xd8000;
	for (int k = 0; k < m; k++) { memset(ix + k * 0x44, 0, 0x44); strcpy(ix + k * 0x44, up[k]); }
	strcpy(ix + m * 0x44, "\x7f");
	S32(BUF, 0x108) = m; S32(BUF, 0x10c) = (int)ix;
	menutex_fonts(0);
	G32(0x76d3f0) = G32(0x9dae1c);
	G32(0x4dda34) = irnd(0, 1);   /* 13 loading-screen frames of 16 columns a step: from 0, as the game */ fill((void *)0x76d350, 16); G32(0x76d480) = 0xdc0;
	g_frames = irnd(0, 3) ? irnd(-2, 400) / 3.0 : irnd(0, 100000);
	g_vfsOpenFail = 0;
}
T_PLAIN(menu_loadIntroTextures, 0x430ca0, introtex_setup();, 0, 0, 0, 0, 0)
