/* sound_basic.c: a sound is eight DirectSound buffers of the same sample, played in turn so a sound can overlap
   itself; the menu sounds play at the menus' volume; the music player is a DirectShow graph. */
#include "../game.h"
#include <string.h>

#undef sound_playNext
#undef sound_setNextVolume
#define DSB_PLAY 0x30
#define DSB_SETVOLUME 0x3c

typedef struct {
	void *buffers[8];
	i32 next;            /* the buffer to play next */
	i32 panModes[8];     /* per buffer: the last play's mode (1 / 2: with a pan; sound_playPanned) */
	i32 pans[8];         /* and its pan (SetPan) */
} Sound;                 /* 100 bytes */

#define g_menuSounds ((Sound *const *)OBJ(g_menuSoundBuffers))

/* 0x467d70: play the sound's next buffer; the turn moves on (0 .. 7) */
void (sound_playNext)(Sound *sound)
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
void (sound_setNextVolume)(Sound *sound, int volume)
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
	sound_setNextVolume(g_menuSounds[id], g_menuVolume);
	sound_playNext(g_menuSounds[id]);
}

/* 0x457310: the music graph released, then COM let go */
void (music_stop)(void)
{
	if (g_music == NULL)
		return;
	COM(g_music, COM_RELEASE, long)(g_music);
	g_music = NULL;
	CoUninitialize();
}

/* 0x456de0: with sound on (g_soundOn), v times the volume setting (g_soundVolume) as 0 .. 100 becomes the attenuation
   (g_soundBaseVolume): below 0 -1000, above 100 0, else (p * 5 - 500) * 20 * the factor at k_0_1f. Returns what the
   original leaves in eax */
int (sound_setVolume)(int v)
{
	if (!g_soundOn)
		return 0;
	int p = ftol(fmul_m((long double)g_soundVolume * v, k_0_01f_4a9504));
	if (p < 0) {
		g_soundBaseVolume = -1000;
		return p;
	}
	if (p > 100) {
		g_soundBaseVolume = 0;
		return p;
	}
	int r = ftol(fmul_m((long double)((p * 5 - 500) * 20), (const float *)ADDR(k_0_1f)));
	g_soundBaseVolume = r;
	return r;
}

/* 0x4572b0: the music stream (g_music) restarted from the start once it has played to its length (g_musicLength, 64
   bits). Returns what the original leaves in eax */
u32 (music_loopIfEnded)(void)
{
	void *stream = g_music;
	if (!stream)
		return 0;
	u32 pos[2];
	COM(stream, 0x20, u32, u32 *)(stream, pos);   /* the play position */
	int hi = (int)pos[1], end_hi = g_musicEndHigh;
	if (hi < end_hi)
		return (u32)hi;
	if (hi == end_hi && pos[0] < g_musicLength)
		return g_musicLength;
	stream = g_music;
	COM(stream, 0x28, u32, u32, u32)(stream, 0, 0);
	stream = g_music;
	return COM(stream, 0x1c, u32, u32)(stream, 1);
}

/* 0x467dd0: the sound's next buffer (of eight, next) played with a pan (mode 1 or 2: value, within
   +-10000, kept per buffer in pans; the mode in panModes): the pan applied (SetPan), then played. Returns what
   the original leaves in eax: 0 without a sound, 1 for a value out of range, else the next turn (7 when wrapping) */
u32 (sound_playPanned)(u32 *sound, int mode, int value)
{
	if (!sound)
		return 0;
	if (value > 10000 || value < -10000)
		return 1;
	Sound *sd = (Sound *)sound;
	sd->panModes[sd->next] = mode;
	if (mode == 1 || mode == 2)
		sd->pans[sd->next] = value;
	void *buffer = RELOC(sd->buffers[sd->next]);
	COM(buffer, 0x40, u32, u32)(buffer, (u32)sd->pans[sd->next]);   /* SetPan */
	buffer = RELOC(sd->buffers[sd->next]);
	COM(buffer, 0x30, u32, u32, u32, u32)(buffer, 0, 0, 0);   /* Play */
	u32 turn = (u32)sd->next;
	if ((int)turn < 7) {
		sd->next = turn + 1;
		return turn + 1;
	}
	sd->next = 0;
	return turn;
}

/* 0x42bd40: the ten menu sounds loaded (sound_loadWav; their names from 0x4b1644 down to 0x4b1564) into 0x4dd4d4 ..
   0x4dd4f8. Returns the last one */
u32 (sound_loadMenuSounds)(void)
{
	static const u32 names[10] = { STR(0x4b1644, "sound/if_menu_select.wav"), STR(0x4b1628, "sound/if_menu_cancel.wav"), STR(0x4b1610, "sound/if_menu_move.wav"), STR(0x4b15f4, "sound/if_tunnel_select.wav"), STR(0x4b15dc, "sound/if_tunnel_in.wav"), STR(0x4b15c4, "sound/if_tunnel_out.wav"), STR(0x4b15b0, "sound/if_error.wav"), STR(0x4b1598, "sound/if_negative.wav"),
	                               STR(0x4b1580, "sound/if_arm_equip.wav"), STR(0x4b1564, "sound/if_arm_equipslide.wav") };
	u32 r = 0;
	for (int k = 0; k < 10; k++)
		g_menuSoundBuffers[k] = r = sound_loadWav((const char *)RELOC(names[k]));
	return r;
}

/* 0x457080: a sound file played once (with sound on): loaded under its name (sound_loadWav), at volume 0 .. 100 of the
   sound setting (below 0: silent at -1000, above 100: the setting's attenuation), then the sound's record freed (mem_free; its DirectSound buffer is not released). Returns
   what the original leaves in eax */
u32 (sound_playFile)(const char *name, int volume)
{
	if (!g_soundOn)
		return 0;
	char copy[0x104];
	strcpy(copy, name);
	void *sound = GAME_FN(sound_loadWav, 0x467b90, void *, const char *)(copy);
	if (!sound)
		return 0;
	int attenuation;
	if (volume < 0)
		attenuation = -1000;
	else if (volume > 100)
		attenuation = g_soundBaseVolume;
	else
		attenuation = ftol(fmul_m((long double)volume, k_0_01f_4a9504) * (g_soundBaseVolume + 10000)) - 10000;
	GAME_FN(sound_setNextVolume, 0x467db0, void, void *, int)(sound, attenuation);   /* sound_setNextVolume */
	GAME_FN(sound_playNext, 0x467d70, void, void *)(sound);                     /* sound_playNext */
	return mem_free(sound);
}

/* 0x456d10: the sound table loaded (with sound on): the old one released (sound_freeAll), the volume set, then from the
   scrambled file: records of an index and a 256-byte sound name, each sound loaded into the table at g_soundTable,
   until a negative index. A missing file is a fatal error. Returns 1 (0 with sound off) */
int (sound_initSoundTable)(const char *file, int volume)
{
	if (!g_soundOn)
		return 0;
	sound_freeAll();   /* sound_freeAll */
	sound_setVolume(volume);   /* sound_setVolume */
	void *f = crt_fopen(file, (const char *)STR(0x4ad170, "rb"));
	if (!f)
		sys_fatalErrorN((void *)OBJ(g_logSound), (const char *)STR(0x4b42e8, "can't open file %s - initSoundTable()"), file);   /* sys_fatalError */
	int index;
	char name[0x100];
	fread_scrambled(&index, 4, 1, f);
	while (index >= 0) {
		fread_scrambled(name, 1, 0x100, f);
		u32 sound = sound_loadWav(name);
		g_soundTable[index] = sound;
		fread_scrambled(&index, 4, 1, f);
	}
	fclose(f);
	return 1;
}

/* 0x456e50: sound `index` played at volume 0..100 (with sound on and the sound loaded): below 0 silent (-1000),
   above 100 the base volume (g_soundBaseVolume), otherwise volume * k_0_01f_4a9504 * (base + 10000) - 10000. Returns the play's
   eax, or what the original leaves when there is nothing to play */
u32 (sound_playVolume)(int index, int volume)
{
	u32 on = (*(u32 *)&g_soundOn);
	if (!on)
		return 0;
	void *sound = GAME_VAR(void *, OBJ(g_soundTable) + index * 4);
	if (!sound)
		return on;
	int level;
	if (volume < 0)
		level = -1000;
	else if (volume > 100)
		level = g_soundBaseVolume;
	else
		level = ftol(fmul_m((long double)volume, k_0_01f_4a9504) * (long double)(g_soundBaseVolume + 10000)) - 10000;
	GAME_FN(sound_setNextVolume, 0x467db0, void, void *, int)(sound, level);   /* sound_setNextVolume */
	return GAME_FN(sound_playNext, 0x467d70, u32, void *)(GAME_VAR(void *, OBJ(g_soundTable) + index * 4));   /* sound_playNext */
}

/* 0x456ed0: sound index played at pos as heard from listener (side: the listener's right, the listener's up at
   g_vecUnitY) within range (a float): fading from the base volume (g_soundBaseVolume) at the listener to silence at range,
   and panned by the side of the listener it is on (k_1500f_4a9700, or k_m1500f with g_stereoReverse set, as the pan's scale).
   Nothing out of range or with sound off. The callers ignore the eax it leaves */
void (sound_play3D)(int index, const float *pos, const float *listener, const float *side, float range)
{
	if (!g_soundOn || !GAME_VAR(void *, OBJ(g_soundTable) + index * 4))
		return;
	const float *up = g_vecUnitY;
	float d[3], v[3], c[3];
	for (int k = 0; k < 3; k++)
		d[k] = f32(fsub_m(fld_m(pos + k), listener + k));
	memcpy(v, d, sizeof v);
	long double length = Vec3_normalize(v);
	float distance = f32(length);
	if (!(length < (long double)range) && !__builtin_isnan(length) && !__builtin_isnan(range))
		return;
	if (!(range > 0.0f))
		return;
	int base = g_soundBaseVolume + 10000;
	int volume = ftol(fsubr_m(FDIV(distance, range), (const float *)ADDR(k_1f)) * (long double)base) - 10000;
	if (volume > 0)
		volume = 0;
	c[0] = f32(FMUL(d[1], up[2]) - FMUL(d[2], up[1]));
	c[1] = f32(FMUL(d[2], up[0]) - FMUL(up[2], d[0]));
	c[2] = f32(FMUL(up[1], d[0]) - FMUL(d[1], up[0]));
	Vec3_normalize(c);
	long double across = FMUL(c[1], side[1]) + FMUL(c[2], side[2]);
	across = across + FMUL(c[0], side[0]);
	int pan = ftol(fmul_m(across, (const float *)(g_stereoReverse ? ADDR(k_m1500f) : ADDR(k_1500f_4a9700))));
	GAME_FN(sound_setNextVolume, 0x467db0, void, void *, int)(GAME_VAR(void *, OBJ(g_soundTable) + index * 4), volume);   /* sound_setNextVolume */
	sound_playPanned(GAME_VAR(void *, OBJ(g_soundTable) + index * 4) /* g_soundTable[index] */, (pan > 0) + 1, pan);
}

#define DS_CREATESOUNDBUFFER 0x0c
#define DS_DUPLICATESOUNDBUFFER 0x14
#define DSB_LOCK 0x2c
#define DSB_UNLOCK 0x4c
#undef CreateFileA
#define CreateFileA(name, access, share, security, how, attributes, tmpl) \
	IMPORT(0x4a91b4, void *, const char *, u32, u32, void *, u32, u32, void *)(name, access, share, security, how, attributes, tmpl)
#define ReadFile(file, out, size, done, overlapped) IMPORT(0x4a9068, int, void *, void *, u32, u32 *, void *)(file, out, size, done, overlapped)
#undef CloseHandle
#define CloseHandle(handle) IMPORT(0x4a91b0, int, void *)(handle)

/* the buffer's format and description as the original lays them out on its stack: the description starts where
   the format's cbSize would be (so that reads as the description's size, 0x24) */
typedef struct __attribute__((packed)) {
	u16 formatTag, channels;
	u32 samplesPerSec, avgBytesPerSec;
	u16 blockAlign, bitsPerSample;
	u32 size, flags, bufferBytes, reserved;   /* DSBUFFERDESC */
	void *format;
	u8 algorithm3D[16];
} WaveDesc;

/* a .wav file's 44-byte header (RIFF, its "fmt " chunk, the "data" chunk's head) */
typedef struct {
	u32 riff, riffSize, wave, fmt, fmtSize;
	u16 formatTag, channels;
	u32 samplesPerSec, avgBytesPerSec;
	u16 blockAlign, bitsPerSample;
	u32 data, dataSize;
} WavHeader;
_Static_assert(sizeof(WavHeader) == 0x2c, "WavHeader");

/* 0x467b90: a sound from a PCM .wav file (its 44-byte header, then the data): a static buffer of the data's size and
   format (DSBCAPS 0xe2), the data copied in, then the 8 buffers all duplicates of it. NULL when the file does not
   open or the buffer is not made ("SoundBuffer create error") */
Sound *(sound_loadWav)(const char *name)
{
	void *file = CreateFileA(name, 0x80000000, 1, NULL, 3, 0x80, NULL);   /* GENERIC_READ, share read, OPEN_EXISTING */
	if (file == (void *)-1)
		return NULL;
	WavHeader header;
	u32 done;
	ReadFile(file, &header, sizeof header, &done, NULL);
	WaveDesc desc;
	memset(&desc, 0, sizeof desc);
	desc.formatTag = 1;
	desc.channels = header.channels;
	desc.samplesPerSec = header.samplesPerSec;
	desc.blockAlign = header.blockAlign;
	desc.avgBytesPerSec = desc.blockAlign * desc.samplesPerSec;
	desc.bitsPerSample = header.bitsPerSample;
	u32 size = header.dataSize;
	desc.size = 0x24;
	desc.flags = 0xe2;
	desc.bufferBytes = size;
	desc.format = &desc;
	u8 *data = operator_new(size);
	Sound *sound = operator_new(100);
	ReadFile(file, data, size, &done, NULL);
	CloseHandle(file);
	void *ds = g_directSound;
	if (COM(ds, DS_CREATESOUNDBUFFER, long, void *, void **, void *)(ds, &desc.size, &sound->buffers[0], NULL)) {
		MessageBoxA(NULL, (const char *)STR(0x4c4dc4, "SoundBuffer create error"), (const char *)STR(0x4c4de0, "Error"), 0);
		return NULL;
	}
	void *buffer = sound->buffers[0], *locked;
	COM(buffer, DSB_LOCK, long, u32, u32, void **, u32 *, void **, u32 *, u32)(buffer, 0, size, &locked, &size, NULL, NULL, 0);
	memcpy(locked, data, size);
	COM(buffer, DSB_UNLOCK, long, void *, u32, void *, u32)(buffer, locked, size, NULL, 0);
	sound->next = 0;
	for (int i = 0; i < 8; i++) {
		sound->panModes[i] = 0;
		sound->pans[i] = 0;
	}
	for (int i = 0; i < 8; i++) {
		ds = g_directSound;
		COM(ds, DS_DUPLICATESOUNDBUFFER, long, void *, void **)(ds, sound->buffers[0], &sound->buffers[i]);
	}
	operator_delete(data);
	return sound;
}

/* 0x467a50: DirectSound started on window hwnd (g_directSound, priority level) with its primary buffer (g_primarySoundBuffer) set to
   44.1 kHz 16-bit stereo and playing (looped); sound on (g_soundOn). 1, or 0 when any step fails (DirectSound
   released again when the buffer will not play) */
int (sound_init)(void *hwnd)
{
	if (IMPORT(0x4a9020, int, void *, void **, void *)(NULL, (void **)ADDR(g_directSound), NULL))   /* DirectSoundCreate */
		return 0;
	void *ds = g_directSound;
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
	ds = g_directSound;
	if (COM(ds, 0xc, int, void *, void **, void *)(ds, &desc, (void **)ADDR(g_primarySoundBuffer), NULL))   /* CreateSoundBuffer */
		return 0;
	void *primary = g_primarySoundBuffer;
	COM(primary, 0x38, int, void *)(primary, &wave);   /* SetFormat */
	primary = g_primarySoundBuffer;
	if (COM(primary, 0x30, int, u32, u32, u32)(primary, 0, 0, 1)) {   /* Play, looping */
		ds = g_directSound;
		COM(ds, COM_RELEASE, u32)(ds);
		g_directSound = NULL;
		return 0;
	}
	g_soundOn = 1;
	return 1;
}

/* 0x462850 (thiscall on the scene): the match music by the map's kind (musicKind, from the ground file), picked with the random table
   (g_randTable) at the counter g_randPos: 1 one of four (the counter before it moves on), 2 always "darkness", 3 and 4
   one of three (the counter after). Returns music_play's eax, or kind - 1 for another kind */
u32 THISCALL (music_playMatch)(Scene *scene)
{
	static const u32 kind1[4] = { STR(0x4b496c, "Music/trance soul.mp3"), STR(0x4b4a6c, "Music/Dark Core.mp3"), STR(0x4b4b6c, "Music/Mean street.mp3"), STR(0x4b4c6c, "Music/Thrill Seeker.mp3") };   /* trance soul, Dark Core, Mean street, Thrill Seeker */
	static const u32 kind3[3] = { STR(0x4b4d6c, "Music/Forgotten.mp3"), STR(0x4b4e6c, "Music/desert wind.mp3"), STR(0x4b506c, "Music/ashes of past.mp3") };             /* Forgotten, desert wind, ashes of past */
	static const u32 kind4[3] = { STR(0x4b516c, "Music/Speed of Light.mp3"), STR(0x4b536c, "Music/Fierce battle.mp3"), STR(0x4b546c, "Music/Valhalla.mp3") };             /* Speed of Light, Fierce battle, Valhalla */
	const u32 *random = (const u32 *)OBJ(g_randTable);
	u32 kind = (u32)scene->musicKind - 1;
	u32 n;
	switch (kind) {
	case 0:
		n = g_randPos++;
		return music_play((const char *)RELOC(kind1[random[n & 0xfff] & 3]));   /* music_play */
	case 1:
		g_randPos++;
		return music_play((const char *)STR(0x4b4f6c, "Music/darkness.mp3"));   /* darkness */
	case 2:
	case 3:
		n = ++g_randPos;
		return music_play((const char *)(RELOC(kind) == 2 ? kind3 : kind4)[random[n & 0xfff] % 3]);
	}
	return kind;
}

/* 0x457150: the music file `name` played through DirectShow's multimedia stream (CoCreateInstance of k_CLSID_AMMultiMediaStream;
   Initialize for reading, the default audio renderer added, the file opened, run), the stream kept in g_music, its
   duration in g_musicLength and the name in g_musicFile. The music volume (g_musicVolume) below 50 or no such file: the music
   stopped and 1. Any failing step: 0 (the stream let go of nothing). Otherwise 1 */
int (music_play)(const char *name)
{
	if (g_musicVolume < 50) {
		music_stop();
		return 1;
	}
	if (g_music)
		music_stop();
	if (!file_existsf(name)) {   /* the file exists */
		if (g_music)
			music_stop();
		return 1;
	}
	void *stream;
	unsigned short wname[0x104];
	CoInitialize(NULL);   /* CoInitialize */
	if (CoCreateInstance((const void *)OBJ(k_CLSID_AMMultiMediaStream), NULL, 1,
			(const void *)OBJ(k_IID_IAMMultiMediaStream), &stream))   /* CoCreateInstance(CLSID_AMMultiMediaStream, IID_IAMMultiMediaStream) */
		return 0;
	MultiByteToWideChar(0, 0, name, -1, wname, 0x104);   /* MultiByteToWideChar */
	if (COM(stream, 0x30, long, u32, u32, void *)(stream, 0, 1, NULL))   /* Initialize(read, no graph thread) */
		return 0;
	if (COM(stream, 0x3c, long, void *, const void *, u32, void *)(stream, NULL, (const void *)OBJ(k_MSPID_PrimaryAudio), 1, NULL))
		return 0;   /* AddMediaStream(primary audio, default renderer) */
	if (COM(stream, 0x40, long, const void *, u32)(stream, wname, 0))   /* OpenFile */
		return 0;
	g_music = stream;
	COM(stream, 0x1c, long, u32)(stream, 1);   /* SetState(run) */
	strcpy(g_musicFile, name);
	COM(g_music, 0x24, long, void *)(g_music, (void *)ADDR(g_musicLength));   /* GetDuration */
	return 1;
}
