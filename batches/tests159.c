/* batch 158 */
static LONG ds_res(void) { return irnd(0, 4) ? 0 : irnd(0, 1) ? (LONG)0x80004005 : (LONG)0x88780078; }
/* sound_init: DirectSoundCreate giving a fake DirectSound or failing, each step succeeding or not (the buffer
   description and the format hashed) */
static void dsinit_setup(void)
{
	FakeCom *ds = (FakeCom *)fakecom_new(2, 3, g_nargsDsound, 0), *pb = (FakeCom *)fakecom_new(3, 4, g_nargsDsbuf, 0);
	ds->ret[6] = ds_res(); ds->ret[3] = ds_res(); ds->outarg[3] = 2; ds->val[3] = (DWORD)pb; ds->harg[3] = 1; ds->hlen[3] = 0x24;
	pb->ret[14] = ds_res(); pb->harg[14] = 1; pb->hlen[14] = 0x12; pb->ret[12] = ds_res();
	g_mockDsObj = irnd(0, 5) ? (DWORD)ds : 0;
	G32(0xa0e804) = 0; G32(0xa0e808) = 0; G32(0xa0e80c) = 0;
	g_a[0] = irnd(0, 0xffff);
}
/* a sound at BUF + 0x100 (or none): 8 fake buffers (some missing, the current one present when need), the current
   index, kinds and values; a volume or pan anywhere around -10000..10000 */
static void dsbuf_setup(int need)
{
	char *snd = BUF + 0x100;
	fill(snd, 0x64);
	for (int i = 0; i < 8; i++) {
		FakeCom *b = (FakeCom *)fakecom_new(4 + i, 4 + (DWORD)i, g_nargsDsbuf, ds_res());
		S32(snd, i * 4) = irnd(0, 3) ? (int)b : 0;
	}
	S32(snd, 0x20) = irnd(0, 7);
	if (need) S32(snd, S32(snd, 0x20) * 4) = (int)&g_fakeCom[4 + S32(snd, 0x20)];
	g_a[0] = irnd(0, 4); g_a[1] = irnd(0, 3) ? irnd(-10000, 10000) : irnd(-20000, 20000);
	g_a[2] = irnd(0, 7) ? (int)snd : 0;
}
/* the music stream: a fake IAMMultiMediaStream or none, its time against the duration */
static void music_setup(void)
{
	FakeCom *m = (FakeCom *)fakecom_new(12, 0x20, g_nargsAmms, 0);
	G32(0xa0e670) = irnd(0, 3) ? (int)m : 0;
	m->fn[8] = fc_out64; m->val[8] = (DWORD)irnd(0, 100); m->val2[8] = (DWORD)irnd(0, 2);
	G32(0xa0e018) = irnd(0, 100); G32(0xa0e01c) = irnd(0, 2);
}
/* music_play: the music volume, the file there or not, CoCreateInstance giving the stream or failing, each step
   succeeding or not; the wide file name passed to OpenFile hashed */
static void musicplay_setup(void)
{
	music_setup();
	vfs_content(0, 0); g_vfsOpenFail = !irnd(0, 4);
	G32(0x4e0c94) = irnd(0, 3) ? irnd(50, 100) : irnd(0, 49);
	FakeCom *m = &g_fakeCom[13];
	fakecom_new(13, 0x21, g_nargsAmms, 0);
	m->ret[12] = ds_res(); m->ret[15] = ds_res(); m->ret[16] = ds_res(); m->fn[9] = fc_out64;
	m->val[9] = (DWORD)irnd(0, 1000); m->val2[9] = (DWORD)irnd(0, 3); m->ret[9] = 0;
	fill_str(BUF + 0x1c0, 40, 'a', 'z');
	m->harg[16] = 1; m->hlen[16] = (WORD)(2 * (strlen(BUF + 0x1c0) + 1));
	g_mockCoClsid[0] = 0x4aaf10; g_mockCoObj[0] = irnd(0, 4) ? (DWORD)m : 0;
	fill((void *)0xa0e674, 0x40);
}
T_PLAIN(sound_init, 0x467a50, dsinit_setup();, 0, g_a[0], 0, 0, 0)
T_PLAIN(dsbuf_play, 0x467d70, dsbuf_setup(0);, 0, g_a[2], 0, 0, 0)
T_PLAIN(dsbuf_setVolume, 0x467db0, dsbuf_setup(0);, 0, g_a[2], g_a[1], 0, 0)
T_PLAIN(sound_467dd0, 0x467dd0, dsbuf_setup(1);, 0, g_a[2], g_a[0], g_a[1], 0)
T_PLAIN(music_shutdown, 0x457310, music_setup();, 0, 0, 0, 0, 0)
T_PLAIN(music_4572b0, 0x4572b0, music_setup();, 0, 0, 0, 0, 0)
T_PLAIN(music_play, 0x457150, musicplay_setup();, 0, BUF + 0x1c0, 0, 0, 0)
