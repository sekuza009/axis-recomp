/* batch 160 (lifted/grp106.c): loading a WAV sound */
#include "lifted/grp106.c"
/* 0x467b90 sound_loadWav(name): reads the 44-byte WAV header and the data (CreateFile / ReadFile), a static
   buffer of that size and format (CreateSoundBuffer, "SoundBuffer create error" box and NULL on a failure), the
   data copied in (Lock / Unlock), then the sound (100 bytes): 7 duplicates of the buffer, index and kinds 0;
   NULL when the file does not open */
LIFT_PLAIN(sound_loadWav, 467b90)
