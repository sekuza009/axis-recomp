/* batch 117 */
/* after menutex_setup has replaced the texture set: the font textures the text passes bind (0x9dae1c, 0x76d448,
   0x76d360, 0x9dad90: the ASCII and Korean fonts) must be textures of that set too: the one owning the
   next-reused GL slot */
static int menutex_fonts(int id)
{
	int k = 0;
	while (S32(BUF + 0x400000, 4 + k * 4) != (int)BUF) k++;
	G32(0x9dae1c) = G32(0x76d448) = G32(0x76d360) = G32(0x9dad90) = k * 512 + S32((char *)S32(BUF, 0xcd134), 4);
	return id;
}
/* menutex_setup's texture set and a bindable texture id as the screen's texture, the text passes' globals
   (textpass_setup, its text at BUF + 0x400 unused), random colours and positions */
static void armctabs_setup(void)
{
	textpass_setup();
	G32(0x9db0a4) = menutex_fonts(menutex_setup());
	G32(0x4dc798) = irnd(-1, 3); G32(0x4dcc90) = irnd(-50, 400); G32(0x4dcc94) = irnd(-50, 400);
	fill((void *)0x4dc1d0, 16); fill((void *)0x4dbc58, 16);
	for (int k = 0; k < 3; k++) fill_str((char *)0x7565a4 + k * 0x80, 60, 32, 126);
}
T_PLAIN(armc_412450, 0x412450, armctabs_setup();, 0, 0, 0, 0, 0)
/* the briefing text: a random text (CR LF pairs, double-byte characters) of up to 160 bytes at BUF + 0x10000,
   shown from offset 0..20, the typing position somewhere in it, the end; the timer near its step */
static void typewriter_setup(void)
{
	textpass_setup();
	char *t = BUF + 0x10000; int n = irnd(0, 160), i = 0;   /* longer texts overflow the 4096-call log */
	while (i < n) {
		int k = irnd(0, 9);
		if (k == 0) { t[i++] = '\r'; t[i++] = '\n'; }
		else if (k == 1) { t[i++] = (char)irnd(0xb0, 0xc8); t[i++] = (char)irnd(0xa1, 0xfe); }
		else t[i++] = (char)irnd(32, 126);
	}
	t[i] = 0; t[i + 1] = 0;
	G32(0x9eeba4) = (int)t; G32(0x9ef1ec) = irnd(0, 5) ? irnd(1, 20) : 0;
	G32(0x9ef1f4) = irnd(0, i > 30 ? i - 25 : 5); G32(0x9ef200) = (int)t + i;
	G32(0x9f105c) = irnd(0, 4) ? 0 : 1; G32(0x4d7348) = irnd(0, 4) ? 0 : 1;
	GF(0x9f16b8) = (float)irnd(0, 200) / 100.0f;
	G32(0x9f16a8) = irnd(-50, 400); G32(0x9f16ac) = irnd(-50, 300); G32(0x4d23c8) = irnd(-50, 600); G32(0x4d23cc) = irnd(-50, 400);
	memset((void *)0x9f1064, 0, 0x200); fill_str((char *)0x9f1064, 100, 32, 126);   /* drawn as is when nothing is typed; zeroed: a typing step copies without a terminator */
}
T_PLAIN(skirmish_445520, 0x445520, typewriter_setup();, 0, 0, 0, 0, 0)
/* the message window: menutex_setup's texture as frame and button, a window rectangle, two texts */
static void profmsg_setup(void)
{
	textpass_setup();
	int id = menutex_fonts(menutex_setup());
	G32(0x9db0a4) = id; G32(0x4deb50) = id; G32(0x4deb4c) = id;   /* frame, button, border */
	G32(0x9f8eac) = irnd(-50, 400); G32(0x9f8ea8) = irnd(-50, 300);
	G32(0x9f8f20) = G32(0x9f8eac) + irnd(0, 400); G32(0x9f8f24) = G32(0x9f8ea8) + irnd(0, 300);
	fill((void *)0x9f8eb0, 16);
	fill_str((char *)0x751d24, 60, 32, 126); fill_str((char *)0x7517a4, 30, 32, 126);
}
T_PLAIN(profile_44dc60, 0x44dc60, profmsg_setup();, 0, 0, 0, 0, 0)
/* the custom option: either the preview reloaded first (mappreview_setup) for custom rules (no texture bound: a
   preview that was not found would bind id -1, outside the set), or no reload and a bindable preview texture,
   custom or not */
static void customopt_setup(DWORD idxp, DWORD flag, DWORD px, DWORD py)
{
	textpass_setup();
	if (!irnd(0, 3)) { mappreview_setup(idxp); menutex_fonts(0); G32(0x680cd0) = 1; *(char *)flag = (char)irnd(1, 2); }
	else { G32(0x9da324) = menutex_fonts(menutex_setup()); G32(0x680cd0) = 0; *(char *)flag = irnd(0, 1) ? 0 : (char)irnd(1, 2); }
	G32(px) = irnd(-50, 700); G32(py) = irnd(-50, 400);
}
T_PLAIN(arena_drawCustomOption, 0x40b550, customopt_setup(0x4db548, 0x4db54a, 0x4dbb08, 0x4dbb04);, 0, 0, 0, 0, 0)
T_PLAIN(room_drawCustomOption, 0x43bde0, customopt_setup(0x4df9e8, 0x4df9ea, 0x9dd1c0, 0x9dd1bc);, 0, 0, 0, 0, 0)
