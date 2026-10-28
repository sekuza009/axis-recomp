/* sound_basic.c: a sound is eight DirectSound buffers of the same sample, played in turn so a sound can overlap
   itself; the menu sounds play at the menus' volume; the music player is a DirectShow graph. */
#include "../game.h"

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
