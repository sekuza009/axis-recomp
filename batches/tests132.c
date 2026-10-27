/* batch 131 */
/* each dispatcher's screens as their own tests set them up, a message open now and then (dlgwin_setup's
   0x90d1c4), the modes and tabs that choose the dialog */
static void mapselect2_setup(void) { mapselect_setup(); G32(0x90d1c4) = irnd(0, 3) ? 0 : 1; }
T_PLAIN(mainmenu_4434f0, 0x4434f0, mapselect2_setup();, 0, 0, 0, 0, 0)
static void arenaplayer_setup(void)
{
	tunnels_setup(); arenaname_setup();          /* the dialog rebuilds the texture set: the tunnel's slots from the new one */
	G32(0x4e0cd0) = G32(0x9db0a4); for (DWORD a = 0x4df03c; a <= 0x4df04c; a += 4) G32(a) = G32(0x9db0a4);
	G32(0x4dbb3c) = irnd(0, 3); G32(0x4db51c) = irnd(0, 3) ? irnd(0, 4) : 5; G32(0x90d1c4) = irnd(0, 3) ? 0 : 1;
}
T_PLAIN(lobbyPlayer_draw, 0x40cf80, arenaplayer_setup();, 0, 0, 0, 0, 0)
static void setupdlg_setup(int sound)
{
	if (sound) sound_setup(); else options_setup();
	setuptunnel_setup();                       /* rebuilds the texture set: the dialog's textures from the new one */
	G32(0x9db0a4) = G32(0x4e0cd0); G32(0x4deb50) = G32(0x4e0cd0); G32(0x4deb4c) = G32(0x4e0cd0);
	G32(0x4ddac8) = irnd(0, 3) ? irnd(0, 0x300) : 0x29a; G32(0x90d1c4) = irnd(0, 3) ? 0 : 1;
}
T_PLAIN(setup_427830, 0x427830, setupdlg_setup(1);, 0, 0, 0, 0, 0)
T_PLAIN(setup_427880, 0x427880, setupdlg_setup(0);, 0, 0, 0, 0, 0)
/* the profile screen with a dialog: profscreen_setup and the dialog's window (profdlg_setup), the glide on or off
   with a target and time left */
static void profglide_setup(DWORD xo, DWORD yo, DWORD xe, DWORD ye)
{
	profscreen_setup();
	profdlg_setup(xo, yo, xe, ye);             /* rebuilds the texture set: the panel's portrait from the new one */
	G32(0x4dfa00) = G32(0x9db0a4);
	for (DWORD s = 0x751ca4; s <= 0x751e24; s += 0x80) ((char *)s)[irnd(0, 10)] = 0;   /* short texts: the call log */
	((char *)0x7517a4)[irnd(0, 8)] = 0; ((char *)0x751824)[irnd(0, 8)] = 0;
	G32(0x76d42c) = irnd(0, 1); G32(0x67ef34) = irnd(0, 640); G32(0x67fb38) = irnd(0, 480);
	GF(0x680bc0) = (float)irnd(-10, 100) / 10.0f; G32(0x90d1c4) = irnd(0, 3) ? 0 : 1;
}
T_PLAIN(profile_44f5f0, 0x44f5f0, profglide_setup(0x9f8f1c, 0x9f8f0c, 0x9f8f2c, 0x9f8f28);, 0, 0, 0, 0, 0)
T_PLAIN(profile_44f740, 0x44f740, profglide_setup(0x9f6834, 0x9f683c, 0x9f93bc, 0x9f93c0);, 0, 0, 0, 0, 0)
