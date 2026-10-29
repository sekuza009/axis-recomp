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
