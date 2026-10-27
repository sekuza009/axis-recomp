/* batch 155 */
/* the Esc menu: the game at BUF, hudtext_setup's set with hudpanel_setup's panel textures, the fade 0..0.5 s, pages
   -1..5, modes 0..3, a slot or none, team game or not, the selection 0..4, recording or not, the record name, the
   stage and progress */
static void escmenu_setup(void)
{
	hudtext_setup();
	S32(BUF, 0xbc06b4) = S32(BUF, 0xbc06b0);
	float f = (float)irnd(0, 50) / 100.0f; memcpy(BUF + 0x2340c9c, &f, 4);
	int v;
	v = irnd(0, 9) ? irnd(0, 4) : irnd(-1, 5); memcpy(BUF + 0x2340cf8, &v, 4);
	S32(BUF, 8) = irnd(0, 3);
	v = irnd(0, 2) ? irnd(0, 7) : -1; memcpy(BUF + 0x234243e, &v, 4);
	S32(BUF, 0x22e7184) = irnd(0, 2);
	v = irnd(-1, 4); memcpy(BUF + 0x2340cfc, &v, 4);
	v = irnd(0, 1); memcpy(BUF + 0x2340d1d, &v, 4);
	v = irnd(0, 9); memcpy(BUF + 0x23423a9, &v, 4);
	fill_str((char *)0x9dc92c, 20, 32, 126); G32(0x9dad94) = irnd(0, 15); G32(0x9f181c) = irnd(0, 20);
}
ST(hud_drawEscMenu, escmenu_setup();, (TC(void, 0x495610, char *)(BUF), 0), (hud_drawEscMenu(BUF), 0))
