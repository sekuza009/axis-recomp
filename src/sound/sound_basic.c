/* sound_basic.c: a sound is eight DirectSound buffers of the same sample, played in turn so a sound can overlap
   itself; the menu sounds play at the menus' volume; the music player is a DirectShow graph. */
#include "../game.h"
#include <string.h>

#undef dsbuf_play
#undef dsbuf_setVolume
#define DSB_PLAY 0x30
#define DSB_SETVOLUME 0x3c

typedef struct { void *buffers[8]; i32 next; } Sound;   /* +0x20: the buffer to play next */

#define g_soundOn GAME_VAR(int, 0xa0e80c)             /* (by use) 1: sound works */
#define g_menuSounds ((Sound *const *)0x4dd4d4)
#define g_music GAME_VAR(void *, 0xa0e670)            /* the music graph */

/* 0x467d70: play the sound's next buffer; the turn moves on (0 .. 7) */
void (dsbuf_play)(Sound *sound)
{
	if (sound == NULL)
		return;
	void *buffer = sound->buffers[sound->next];
	if (buffer != NULL)
		COM(buffer, DSB_PLAY, long, u32, u32, u32)(buffer, 0, 0, 0);
	if (sound->next < 7)
		sound->next++;
	else
		sound->next = 0;
}

/* 0x467db0: the volume of the buffer to play next */
void (dsbuf_setVolume)(Sound *sound, int volume)
{
	if (sound == NULL)
		return;
	void *buffer = sound->buffers[sound->next];
	if (buffer != NULL)
		COM(buffer, DSB_SETVOLUME, long, int)(buffer, volume);
}

/* 0x41e760: menu sound id at the menus' volume */
void (sound_playMenu)(int id)
{
	if (g_soundOn != 1)
		return;
	dsbuf_setVolume(g_menuSounds[id], g_menuVolume);
	dsbuf_play(g_menuSounds[id]);
}

/* 0x457310: the music graph released, then COM let go */
void (music_shutdown)(void)
{
	if (g_music == NULL)
		return;
	COM(g_music, COM_RELEASE, long)(g_music);
	g_music = NULL;
	CoUninitialize();
}

/* 0x456de0: with sound on (0xa0e80c), v times the volume setting (0x4e0c90) as 0 .. 100 becomes the attenuation
   (0xa0e66c): below 0 -1000, above 100 0, else (p * 5 - 500) * 20 * the factor at 0x4a93ec. Returns what the
   original leaves in eax */
int (FUN_00456de0)(int v)
{
	if (!GAME_VAR(int, 0xa0e80c))
		return 0;
	int p = ftol(fmul_m((long double)GAME_VAR(int, 0x4e0c90) * v, (const float *)0x4a9504));
	if (p < 0) {
		GAME_VAR(int, 0xa0e66c) = -1000;
		return p;
	}
	if (p > 100) {
		GAME_VAR(int, 0xa0e66c) = 0;
		return p;
	}
	int r = ftol(fmul_m((long double)((p * 5 - 500) * 20), (const float *)0x4a93ec));
	GAME_VAR(int, 0xa0e66c) = r;
	return r;
}

/* 0x4572b0: the music segment (0xa0e670) restarted from the start once it has played to its length (0xa0e018, 64
   bits). Returns what the original leaves in eax */
u32 (music_4572b0)(void)
{
	void *segment = GAME_VAR(void *, 0xa0e670);
	if (!segment)
		return 0;
	u32 pos[2];
	COM(segment, 0x20, u32, u32 *)(segment, pos);   /* the play position */
	int hi = (int)pos[1], end_hi = GAME_VAR(int, 0xa0e01c);
	if (hi < end_hi)
		return (u32)hi;
	if (hi == end_hi && pos[0] < GAME_VAR(u32, 0xa0e018))
		return GAME_VAR(u32, 0xa0e018);
	segment = GAME_VAR(void *, 0xa0e670);
	COM(segment, 0x28, u32, u32, u32)(segment, 0, 0);
	segment = GAME_VAR(void *, 0xa0e670);
	return COM(segment, 0x1c, u32, u32)(segment, 1);
}

/* 0x467dd0: the sound's next buffer (of eight, the turn at +0x20) played with a setting (mode 1 or 2: value, within
   +-10000, kept per buffer at +0x44; the mode at +0x24): the value applied (method 0x40), then played. Returns what
   the original leaves in eax: 0 without a sound, 1 for a value out of range, else the next turn (7 when wrapping) */
u32 (sound_467dd0)(u32 *sound, int mode, int value)
{
	if (!sound)
		return 0;
	if (value > 10000 || value < -10000)
		return 1;
	u32 *modes = sound + 9, *values = sound + 0x11;
	modes[sound[8]] = (u32)mode;
	if (mode == 1 || mode == 2)
		values[sound[8]] = (u32)value;
	void *buffer = (void *)sound[sound[8]];
	COM(buffer, 0x40, u32, u32)(buffer, values[sound[8]]);
	buffer = (void *)sound[sound[8]];
	COM(buffer, 0x30, u32, u32, u32, u32)(buffer, 0, 0, 0);   /* Play */
	u32 turn = sound[8];
	if ((int)turn < 7) {
		sound[8] = turn + 1;
		return turn + 1;
	}
	sound[8] = 0;
	return turn;
}

/* 0x42bd40: the ten menu sounds loaded (0x467b90; their names from 0x4b1644 down to 0x4b1564) into 0x4dd4d4 ..
   0x4dd4f8. Returns the last one */
u32 (sound_loadMenuSounds)(void)
{
	static const u32 names[10] = { 0x4b1644, 0x4b1628, 0x4b1610, 0x4b15f4, 0x4b15dc, 0x4b15c4, 0x4b15b0, 0x4b1598,
	                               0x4b1580, 0x4b1564 };
	u32 r = 0;
	for (int k = 0; k < 10; k++)
		GAME_VAR(u32, 0x4dd4d4 + k * 4) = r = GAME_CDECL(0x467b90, u32, const char *)((const char *)names[k]);
	return r;
}

/* 0x457080: a sound file played once (with sound on): loaded under its name (0x467b90), at volume 0 .. 100 of the
   sound setting (below 0: silent at -1000, above 100: the setting's attenuation), then the buffer released. Returns
   what the original leaves in eax */
u32 (sound_playFile)(const char *name, int volume)
{
	if (!GAME_VAR(int, 0xa0e80c))
		return 0;
	char copy[0x104];
	strcpy(copy, name);
	void *sound = GAME_CDECL(0x467b90, void *, const char *)(copy);
	if (!sound)
		return 0;
	int attenuation;
	if (volume < 0)
		attenuation = -1000;
	else if (volume > 100)
		attenuation = GAME_VAR(int, 0xa0e66c);
	else
		attenuation = ftol(fmul_m((long double)volume, (const float *)0x4a9504) * (GAME_VAR(int, 0xa0e66c) + 10000)) - 10000;
	GAME_CDECL(0x467db0, void, void *, int)(sound, attenuation);   /* dsbuf_setVolume */
	GAME_CDECL(0x467d70, void, void *)(sound);                     /* dsbuf_play */
	return GAME_CDECL(0x467d60, u32, void *)(sound);               /* FUN_00467d60 */
}

/* 0x456d10: the sound table loaded (with sound on): the old one released (0x456cd0), the volume set, then from the
   scrambled file: records of an index and a 256-byte sound name, each sound loaded into the table at 0xa0e02c,
   until a negative index. A missing file is a fatal error. Returns 1 (0 with sound off) */
int (sound_initSoundTable)(const char *file, int volume)
{
	if (!GAME_VAR(int, 0xa0e80c))
		return 0;
	GAME_CDECL(0x456cd0, void, void)();   /* FUN_00456cd0 */
	GAME_CDECL(0x456de0, int, int)(volume);   /* FUN_00456de0 */
	void *f = crt_fopen(file, (const char *)0x4ad170);
	if (!f)
		GAME_CDECL(0x46c710, void, void *, const char *, const char *)((void *)0xa0e020, (const char *)0x4b42e8, file);   /* sys_fatalError */
	int index;
	char name[0x100];
	fread_scrambled(&index, 4, 1, f);
	while (index >= 0) {
		fread_scrambled(name, 1, 0x100, f);
		u32 sound = GAME_CDECL(0x467b90, u32, const char *)(name);
		GAME_VAR(u32, 0xa0e02c + index * 4) = sound;
		fread_scrambled(&index, 4, 1, f);
	}
	fclose(f);
	return 1;
}

/* 0x456e50: sound `index` played at volume 0..100 (with sound on and the sound loaded): below 0 silent (-1000),
   above 100 the base volume (0xa0e66c), otherwise volume * 0x4a9504 * (base + 10000) - 10000. Returns the play's
   eax, or what the original leaves when there is nothing to play */
u32 (sound_playVolume)(int index, int volume)
{
	u32 on = GAME_VAR(u32, 0xa0e80c);
	if (!on)
		return 0;
	void *sound = GAME_VAR(void *, 0xa0e02c + index * 4);
	if (!sound)
		return on;
	int level;
	if (volume < 0)
		level = -1000;
	else if (volume > 100)
		level = GAME_VAR(int, 0xa0e66c);
	else
		level = ftol(fmul_m((long double)volume, (const float *)0x4a9504) * (long double)(GAME_VAR(int, 0xa0e66c) + 10000)) - 10000;
	GAME_CDECL(0x467db0, void, void *, int)(sound, level);   /* dsbuf_setVolume */
	return GAME_CDECL(0x467d70, u32, void *)(GAME_VAR(void *, 0xa0e02c + index * 4));   /* dsbuf_play */
}

/* 0x467a50: DirectSound started on window hwnd (0xa0e804, priority level) with its primary buffer (0xa0e808) set to
   44.1 kHz 16-bit stereo and playing (looped); sound on (0xa0e80c). 1, or 0 when any step fails (DirectSound
   released again when the buffer will not play) */
int (sound_init)(void *hwnd)
{
	if (((int (STDCALL *)(void *, void **, void *))0x4a82e6)(NULL, (void **)0xa0e804, NULL))   /* DirectSoundCreate */
		return 0;
	void *ds = GAME_VAR(void *, 0xa0e804);
	if (COM(ds, 0x18, int, void *, u32)(ds, hwnd, 2))   /* SetCooperativeLevel(DSSCL_PRIORITY) */
		return 0;
	struct { u16 format, channels; u32 rate, bytesPerSecond; u16 blockAlign, bits, extra; } wave;   /* WAVEFORMATEX */
	struct { u32 size, flags, bytes, reserved; void *format; u8 algorithm[16]; } desc;              /* DSBUFFERDESC */
	memset(&desc, 0, sizeof desc);
	desc.size = 0x24;
	desc.flags = 1;   /* DSBCAPS_PRIMARYBUFFER */
	wave.format = 1;  /* PCM */
	wave.channels = 2;
	wave.rate = 44100;
	wave.bytesPerSecond = 0x2b110;
	wave.blockAlign = 4;
	wave.bits = 16;
	wave.extra = 0;
	ds = GAME_VAR(void *, 0xa0e804);
	if (COM(ds, 0xc, int, void *, void **, void *)(ds, &desc, (void **)0xa0e808, NULL))   /* CreateSoundBuffer */
		return 0;
	void *primary = GAME_VAR(void *, 0xa0e808);
	COM(primary, 0x38, int, void *)(primary, &wave);   /* SetFormat */
	primary = GAME_VAR(void *, 0xa0e808);
	if (COM(primary, 0x30, int, u32, u32, u32)(primary, 0, 0, 1)) {   /* Play, looping */
		ds = GAME_VAR(void *, 0xa0e804);
		COM(ds, COM_RELEASE, u32)(ds);
		GAME_VAR(void *, 0xa0e804) = NULL;
		return 0;
	}
	GAME_VAR(int, 0xa0e80c) = 1;
	return 1;
}

/* 0x462850 (thiscall on the stage): the match music by the map's kind (+0xbe3004), picked with the random table
   (0xa106f8) at the counter 0xa1efb8: 1 one of four (the counter before it moves on), 2 always "darkness", 3 and 4
   one of three (the counter after). Returns music_play's eax, or kind - 1 for another kind */
u32 THISCALL (music_playMatch)(u8 *stage)
{
	static const u32 kind1[4] = { 0x4b496c, 0x4b4a6c, 0x4b4b6c, 0x4b4c6c };   /* trance soul, Dark Core, Mean street, Thrill Seeker */
	static const u32 kind3[3] = { 0x4b4d6c, 0x4b4e6c, 0x4b506c };             /* Forgotten, desert wind, ashes of past */
	static const u32 kind4[3] = { 0x4b516c, 0x4b536c, 0x4b546c };             /* Speed of Light, Fierce battle, Valhalla */
	const u32 *random = (const u32 *)0xa106f8;
	u32 kind = *(u32 *)(stage + 0xbe3004) - 1;
	u32 n;
	switch (kind) {
	case 0:
		n = GAME_VAR(u32, 0xa1efb8)++;
		return GAME_CDECL(0x457150, u32, const char *)((const char *)kind1[random[n & 0xfff] & 3]);   /* music_play */
	case 1:
		GAME_VAR(u32, 0xa1efb8)++;
		return GAME_CDECL(0x457150, u32, const char *)((const char *)0x4b4f6c);   /* darkness */
	case 2:
	case 3:
		n = ++GAME_VAR(u32, 0xa1efb8);
		return GAME_CDECL(0x457150, u32, const char *)((const char *)(kind == 2 ? kind3 : kind4)[random[n & 0xfff] % 3]);
	}
	return kind;
}
