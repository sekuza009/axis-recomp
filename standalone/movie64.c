/* movie64.c: the ending movie in the 64-bit build (PORTING.md, stage 6) - initdata/battle.sra, an AVI of Indeo 3 video
   (400 x 300, 20 frames a second) and 8-bit stereo PCM, played by the library for the host: read and decoded by
   avimovie.c (FFmpeg's indeo3 decoder), each picture drawn into the frame stream (glrec64_movieFrame: a texture on a
   quad, the aspect kept) and the sound played as one of the host's sound buffers (AxisSound). The game ends right
   after it (its window's close path, src/app/win32.c case 99), so the movie runs over the host's next frames:
   platform_playMovie starts it, the loader's axis_frame shows it and axis_running stays 1 until it has finished or a
   new press of Esc skips it. */
#if defined(__x86_64__) || defined(__aarch64__)
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "../src/axis_api.h"
#include "avimovie.h"

typedef uint8_t u8;
typedef uint32_t u32;
void hlog(const char *fmt, ...);   /* host64.c */
unsigned platform_ticks(void);     /* platform64.c */
void glrec64_movieFrame(const u8 *rgb, int w, int h);   /* glrec64.c */

static struct {
	AviMovie *movie;
	const AviMovieInfo *info;
	unsigned start, audioMs;
	int escUp;
	const AxisSound *snd;
	void *user, *buffer;
} M;

static u32 rd32(const u8 *p) { return (u32)p[0] | (u32)p[1] << 8 | (u32)p[2] << 16 | (u32)p[3] << 24; }

static void movie_end(int why)
{
	hlog("ending movie: ended (%s) after %u ms, %d of %d frames\n", why == 1 ? "Esc" : "finished",
	     platform_ticks() - M.start, avimovie_next(M.movie), M.info->frames);
	if (M.buffer && M.snd && M.snd->release)
		M.snd->release(M.user, M.buffer);
	avimovie_close(M.movie);
	memset(&M, 0, sizeof M);
}

int movie64_start(const char *path, const void *sound, void *user)
{
	const AxisSound *snd = sound;
	if (M.movie)
		return 1;
	memset(&M, 0, sizeof M);
	M.movie = avimovie_open(path);
	if (!M.movie) {
		hlog("ending movie: %s missing or not readable\n", path);
		return 0;
	}
	M.info = avimovie_info(M.movie);
	M.snd = snd;
	M.user = user;
	if (snd && M.info->pcm) {   /* (the sound: one buffer, played once) */
		if (snd->music_run)
			snd->music_run(user, 0);
		M.buffer = snd->create(user, M.info->waveFormat, (unsigned)M.info->pcmBytes);
		if (M.buffer) {
			snd->write(user, M.buffer, M.info->pcm, (unsigned)M.info->pcmBytes);
			snd->volume(user, M.buffer, 0);
			snd->play(user, M.buffer, 0);
			u32 bytesPerSec = rd32(M.info->waveFormat + 8);
			M.audioMs = bytesPerSec ? (unsigned)(M.info->pcmBytes * 1000 / bytesPerSec) : 0;
		}
	}
	M.start = platform_ticks();
	hlog("ending movie: %s - %dx%d, %d frames at %u/%u a second, sound %u ms (%s)\n", path, M.info->width,
	     M.info->height, M.info->frames, M.info->rate, M.info->scale, M.audioMs, M.buffer ? "playing" : "none");
	return 1;
}

int movie64_active(void) { return M.movie != NULL; }

/* one host frame of the movie: the frames due by now decoded, the newest drawn; Esc (pressed during the movie) or the
   end stops it */
void movie64_frame(const u8 keys[256])
{
	if (!M.movie)
		return;
	unsigned t = platform_ticks() - M.start;
	if (keys[0x01] & 0x80) {
		if (M.escUp) {
			movie_end(1);
			return;
		}
	} else
		M.escUp = 1;
	int due = (int)((unsigned long long)t * M.info->rate / (1000ull * M.info->scale)) + 1;
	int fresh = avimovie_decode_to(M.movie, due);
	glrec64_movieFrame(fresh ? avimovie_rgb(M.movie) : NULL, M.info->width, M.info->height);
	unsigned length = (unsigned)((unsigned long long)M.info->frames * 1000 * M.info->scale / M.info->rate);
	if (avimovie_next(M.movie) >= M.info->frames && t >= length && t >= M.audioMs)
		movie_end(2);
}
#endif
