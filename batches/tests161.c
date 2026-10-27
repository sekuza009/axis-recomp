/* batch 160 */
/* a WAV file at BUF + 0x2000 (or none): the standard 44-byte header (channels, rate, bits) and 0..2000 bytes of
   data, its size field sometimes larger than the file; DirectSound with CreateSoundBuffer / DuplicateSoundBuffer
   giving a fake buffer or failing, the buffer's Lock pointing at BUF + 0x8000 */
static void wav_setup(void)
{
	BYTE *f = (BYTE *)BUF + 0x2000;
	int n = irnd(0, 2000), ch = irnd(1, 2), bits = irnd(0, 1) ? 16 : 8, rate = irnd(0, 2) ? 22050 : irnd(8000, 48000);
	fill(f, 0x2c + n);
	memcpy(f, "RIFF", 4); S32(f, 4) = 36 + n; memcpy(f + 8, "WAVEfmt ", 8); S32(f, 0x10) = 16;
	*(WORD *)(f + 0x14) = 1; *(WORD *)(f + 0x16) = (WORD)ch; S32(f, 0x18) = rate; S32(f, 0x1c) = rate * ch * bits / 8;
	*(WORD *)(f + 0x20) = (WORD)(ch * bits / 8); *(WORD *)(f + 0x22) = (WORD)bits; memcpy(f + 0x24, "data", 4);
	S32(f, 0x28) = irnd(0, 5) ? n : n + irnd(1, 100);
	g_mockFile = irnd(0, 7) ? f : NULL; g_mockFileLen = 0x2c + n;
	FakeCom *ds = (FakeCom *)fakecom_new(0, 3, g_nargsDsound, 0), *sb = (FakeCom *)fakecom_new(1, 4, g_nargsDsbuf, 0);
	ds->ret[3] = irnd(0, 5) ? 0 : (LONG)0x88780078; ds->outarg[3] = 2; ds->val[3] = (DWORD)sb;
	ds->ret[5] = irnd(0, 5) ? 0 : (LONG)0x80004005; ds->outarg[5] = 2; ds->val[5] = (DWORD)sb;
	sb->fn[11] = fc_lock; sb->val[11] = (DWORD)(BUF + 0x8000); sb->fn[19] = fc_unlock;
	G32(0xa0e804) = (int)ds;
	fill_str(BUF + 0x1c0, 30, 'a', 'z');
}
T_PLAIN(sound_loadWav, 0x467b90, wav_setup();, 0, BUF + 0x1c0, 0, 0, 0)
