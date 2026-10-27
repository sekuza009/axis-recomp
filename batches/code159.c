/* batch 158 (lifted/grp104.c): DirectSound set-up and buffers, the music stream */
#include "lifted/grp104.c"
/* 0x467a50 sound_init(hwnd): DirectSoundCreate into 0xa0e804, cooperative level 2 (priority), the primary buffer
   0xa0e808 set to 44.1 kHz 16-bit stereo and looping silently; 0xa0e80c = 1 and 1, else 0 (DirectSound released
   when the primary buffer does not play) */
LIFT_PLAIN(sound_init, 467a50)
/* a sound: 8 DirectSound buffers (+0, rotated through by +0x20) with a volume or pan kind (+0x24) and value (+0x44)
   per buffer. 0x467d70 dsbuf_play(snd): plays the current buffer and moves to the next; 0x467db0
   dsbuf_setVolume(snd, vol); 0x467dd0 sound_467dd0(snd, kind, value): value in -10000..10000 is stored as the
   current buffer's kind 1 or 2 value, set as its pan, and the buffer played */
LIFT_PLAIN(dsbuf_play, 467d70)
LIFT_PLAIN(dsbuf_setVolume, 467db0)
LIFT_PLAIN(sound_467dd0, 467dd0)
/* the music stream 0xa0e670 (IAMMultiMediaStream). 0x457310 music_shutdown(): releases it, CoUninitialize;
   0x4572b0 music_4572b0(): at the end (GetTime >= the duration 0xa0e018) seeks to 0 and runs it again (loop);
   0x457150 music_play(name): music volume 0x4e0c94 below 50 or no such file: stops; else CoInitialize, a
   multimedia stream (CoCreateInstance), Initialize, an audio stream, OpenFile, run, name into 0xa0e674 and the
   duration into 0xa0e018 */
LIFT_PLAIN(music_shutdown, 457310)
LIFT_PLAIN(music_4572b0, 4572b0)
LIFT_PLAIN(music_play, 457150)
