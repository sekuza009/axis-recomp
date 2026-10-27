/* batch 153 */
/* HUD text: the game at BUF, hudicon_setup's set with the fonts bindable */
static void hudtext_setup(void)
{
	textpass_setup();
	hudicon_setup();
	menutex_fonts(0);
}
T_PLAIN(hud_drawPressFire, 0x495140, hudtext_setup();, 0, 0, 0, 0, 0)
/* the countdown anywhere in -1..5 (whole values now and then), the message */
static void readystart_setup(void)
{
	hudtext_setup();
	SF(BUF, 0x233cc4c) = irnd(0, 3) ? (float)irnd(-10, 50) / 10.0f : (float)irnd(-1, 5);
	fill_str(BUF + 0x2342f06, 30, 32, 126);
}
ST(hud_drawReadyStart, readystart_setup();, (TC(void, 0x496c20, char *)(BUF), 0), (hud_drawReadyStart(BUF), 0))
/* the recording time 0..3600 s (fractions decide the blink), the file name */
static void recind_setup(void)
{
	hudtext_setup();
	float t = (float)irnd(0, 36000) / 10.0f; memcpy(BUF + 0x2340d29, &t, 4);
	fill_str(BUF + 0x2340d0c, 20, 32, 126);
}
ST(hud_drawRecordIndicator, recind_setup();, (TC(void, 0x496d10, char *)(BUF), 0), (hud_drawRecordIndicator(BUF), 0))
/* not a team game (see below), the teams' slots and the winner id (FUN_00463740's test values), follow_setup's top player,
   every record's flag and name */
static void matchresult_setup(void)
{
	hudtext_setup();
	follow_setup();
	if (S32(BUF, 0x22e7184) == 1) S32(BUF, 0x22e7184) = 2;   /* the team branch draws through the patched gfx_fillRect, whose patch code calls a null pointer while the tests run */
	for (int k = 0; k < 5; k++) S32(BUF, 0x2342381 + k * 4) = irnd(-3, 8);
	int w = irnd(-2, 9); memcpy(BUF + 0x23423bd, &w, 4);
	for (int a = 0; a < 16; a++) { char *r = BUF + 0x1ecca70 + a * 0x8888; S32(r, 0x14c) = irnd(0, 1); fill_str(r + 0x98, 16, 32, 126); }
}
ST(hud_drawMatchResult, matchresult_setup();, (TC(void, 0x496a30, char *)(BUF), 0), (hud_drawMatchResult(BUF), 0))
