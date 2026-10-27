/* batch 113 */
/* the game object as scene_reset's, scene_resetActors' and match_463480's tests set it up; 0..12 map list entries
   (names up to 60 characters, some flagged); the camera globals random; modes -1..4 */
static void session_setup(void)
{
	scenereset_setup(); actors_setup(); notice_setup();
	fill(BUF + 0x202e8d0, 0x20); fill(BUF + 0x202e8d8, 0x10);
	S32(BUF, 0x22e7184) = irnd(0, 2); fill(BUF + 0x2342381, 20); fill(SCENE + 0x20f3ab8, 0x24);
	int n = irnd(0, 12); G32(0x9eeab8) = n;
	for (int k = 0; k < n; k++) {
		char *r = (char *)0x9dda88 + k * 0x44; fill(r, 0x44);
		fill_str(r, irnd(0, 60), 33, 126); S32(r, 0x40) = irnd(0, 2) ? 1 : irnd(0, 3);
	}
	fill((void *)0xa0e7a8, 0x40);
	fill(BUF, 0x10); fill(BUF + 0x1f1cbc, 0x40 * 12 + 0x10);
	g_a[0] = (int)rnd32(); g_a[1] = irnd(-1, 4);
}
ST(app_requireCd, session_setup();, (TC(void, 0x460cb0, char *, int, int)(BUF, g_a[0], g_a[1]), 0), (app_requireCd(BUF, (DWORD)g_a[0], (DWORD)g_a[1]), 0))
