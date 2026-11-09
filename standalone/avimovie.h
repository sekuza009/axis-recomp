/* avimovie.h: the game's movies (initdata/interface.sra, battle.sra: AVI files of Indeo 3 video and PCM sound) read and
   decoded - standalone/avimovie.c, used by the 64-bit build's ending movie (movie64.c) and by the Godot launcher's
   cinematics (godot/extension/src/axis_movie.cpp). */
#ifndef AVIMOVIE_H
#define AVIMOVIE_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef struct AviMovie AviMovie;
typedef struct {
	int width, height;   /* the pictures */
	int frames;          /* the video's frames */
	unsigned rate, scale;   /* frames a second: rate / scale */
	const uint8_t *pcm;  /* the sound (NULL: none) - its bytes, as the file has them */
	size_t pcmBytes;
	const uint8_t *waveFormat;   /* its WAVEFORMATEX (18 bytes: format, channels, rate, bytes a second, block, bits) */
} AviMovieInfo;

/* the file read whole and its streams found; NULL when it is missing or not such a movie */
AviMovie *avimovie_open(const char *path);
const AviMovieInfo *avimovie_info(const AviMovie *m);
/* the frames up to (not including) frame 'due' decoded, in order (each Indeo 3 frame builds on the last): 1 when the
   picture changed */
int avimovie_decode_to(AviMovie *m, int due);
int avimovie_next(const AviMovie *m);   /* the next frame to decode */
const uint8_t *avimovie_rgb(const AviMovie *m);   /* the picture: RGB, 3 bytes a pixel, top row first */
void avimovie_close(AviMovie *m);

#ifdef __cplusplus
}
#endif
#endif
