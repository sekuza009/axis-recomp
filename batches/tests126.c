/* batch 125 */
/* the mission-select backdrop: the setup tunnel's values and textures, its own two textures, the hover glow */
static void missionbg_setup(void)
{
	setuptunnel_setup();
	G32(0x76d47c) = G32(0x4e0cd0); G32(0x76d478) = G32(0x4e0cd0); G32(0x76d480) = irnd(0, 1) ? 0xdc0 : 0;
	G32(0x680398) = irnd(0, 1); GF(0x680ccc) = (float)irnd(0, 400) / 10.0f; GF(0x4df454) = irnd(0, 1) ? 1.0f : -1.0f;
}
T_PLAIN(missionsel_448140, 0x448140, missionbg_setup();, 0, 0, 0, 0, 0)
/* the profile screen: pilotpanel_setup's panel and proflist_setup's list (positions shared), every text short (the
   screen draws the list, the panel, four buttons and labels: about ten logged calls a character), the window
   0x9f8e48..0x9f8ea4, focus 0..3, the cursor sometimes on a button */
static void profscreen_setup(void)
{
	pilotpanel_setup();
	int n = irnd(0, 20); G32(0x9f9008) = n; G32(0x9f8c4c) = irnd(0, 7); G32(0x9f8d74) = irnd(0, n > 0 ? n - 1 : 0);
	for (int k = 0; k < 28; k++) fill_str((char *)0x9f684c + k * 0x48, 6, 32, 126);
	for (int k = 0; k < 28; k++) S32((char *)0x9f684c + k * 0x48, 0x40) = irnd(0, 8);
	for (int k = 0; k < 13; k++) fill_str((char *)0x75e824 + k * 0x80, 5, 32, 126);
	for (int p = 0; p < 9; p++) { char *r = (char *)0x9f9040 + p * 0x4c; fill_str(r, 6, 32, 126); fill_str(r + 0x10, 6, 32, 126); }
	fill_str((char *)0x751a24, 12, 32, 126);
	for (int k = 0; k < 4; k++) fill_str((char *)0x751aa4 + k * 0x80, 8, 32, 126);
	G32(0x9f8ea0) = G32(0x9f8e48) + irnd(300, 600); G32(0x9f8ea4) = G32(0x9f8e4c) + irnd(200, 450);
	G32(0x9f8f10) = irnd(0, 3); fill((void *)0x9f8d58, 16);
	G32(0x4deb50) = G32(0x9db0a4); G32(0x4deb4c) = G32(0x9db0a4);
	G32(0x4ded68) = irnd(0, 640); G32(0x4ded6c) = irnd(0, 480);
	if (irnd(0, 1)) { G32(0x4ded68) = G32(0x9f8e48) + 0x28 + irnd(0, 3) * 0x72 + irnd(0, 0x60); G32(0x4ded6c) = G32(0x9f8ea4) - irnd(0x10, 0x30); }
}
T_PLAIN(mainmenu_drawScreen, 0x44d720, profscreen_setup();, 0, 0, 0, 0, 0)
