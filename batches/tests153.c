/* batch 152 */
/* the clock: hudicon_setup's set (fonts bindable too), a score limit or none, team mode or not with scores near the
   limit, the players' scores, a time limit or none with the elapsed time near it, the blink phase */
static void put32u(char *p, int v) { memcpy(p, &v, 4); }
static void clock_hud_setup(void)
{
	textpass_setup();
	hudicon_setup();
	menutex_fonts(0);
	int lim = irnd(0, 3) ? irnd(1, 50) : irnd(-5, 0);
	put32u(BUF + 0x23423ad, lim);
	S32(BUF, 0x22e7184) = irnd(0, 2);
	S32(BUF, 0x2221fbc) = irnd(0, 50); S32(BUF, 0x2221fb8) = irnd(0, 50);
	int np = irnd(0, 8), lead = irnd(0, 7);
	memcpy(BUF + 0x2342976, &np, 4); memcpy(BUF + 0x23428f6, &lead, 4);
	for (int p = 0; p < 8; p++) S32(BUF, 0x1eccb54 + p * 0x8888) = lim > 0 ? irnd(lim - 3, lim + 1) : irnd(0, 50);
	int tl = irnd(0, 3) ? irnd(1, 20) : irnd(-2, 0);
	put32u(BUF + 0x23423b1, tl);
	S32(BUF, 0x22f0408) = tl > 0 ? irnd(tl * 60 - 15, tl * 60 + 5) : irnd(0, 1200);
	SF(BUF, 0x22f040c) = (float)irnd(0, 100) / 100.0f;
}
ST(hud_drawClock, clock_hud_setup();, (TC(void, 0x496610, char *)(BUF), 0), (hud_drawClock(BUF), 0))
