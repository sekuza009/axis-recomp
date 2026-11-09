/* movie64.c: the ending movie in the 64-bit build (PORTING.md, stage 6) - initdata/battle.sra, an AVI of Indeo 3 video
   (400 x 300, 20 frames a second) and 8-bit stereo PCM, played by the library for the host: the video decoded with
   FFmpeg's indeo3 decoder (../axisnet/iv32/ffmpeg, unmodified, LGPL 2.1+; the same code the 32-bit build's iv32 hands
   to Windows' MCI), each picture drawn into the frame stream (glrec64_movieFrame: a texture on a quad, the aspect kept)
   and the sound played as one of the host's sound buffers (AxisSound). The game ends right after it (its window's
   close path, src/app/win32.c case 99), so the movie runs over the host's next frames: platform_playMovie starts it,
   the loader's axis_frame shows it and axis_running stays 1 until it has finished or a new press of Esc skips it. */
#if defined(__x86_64__) || defined(__aarch64__)
#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#endif
#include "config.h"
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <malloc.h>
#endif
#include "libavcodec/avcodec.h"
#include "libavcodec/codec_internal.h"
#include "../src/axis_api.h"

typedef uint8_t u8;
typedef uint32_t u32;
void hlog(const char *fmt, ...);   /* host64.c */
unsigned platform_ticks(void);     /* platform64.c */
void glrec64_movieFrame(const u8 *rgb, int w, int h);   /* glrec64.c */
extern const FFCodec ff_indeo3_decoder;

/* ---- the libav runtime the decoder calls (as iv32.c's) */
void av_log(void *avcl, int level, const char *fmt, ...) { (void)avcl; (void)level; (void)fmt; }
void avpriv_request_sample(void *avc, const char *msg, ...) { (void)avc; (void)msg; }
void *av_malloc(size_t size)
{
#ifdef _WIN32
	return _aligned_malloc(size ? size : 1, 64);
#else
	void *p = NULL;
	return posix_memalign(&p, 64, size ? size : 1) ? NULL : p;
#endif
}
void av_freep(void *arg)
{
	void **p = arg;
#ifdef _WIN32
	if (*p) _aligned_free(*p);
#else
	free(*p);
#endif
	*p = NULL;
}
int av_image_check_size(unsigned w, unsigned h, int log_offset, void *log_ctx)
{
	(void)log_offset; (void)log_ctx;
	return w && h && w <= 4096 && h <= 4096 ? 0 : AVERROR(EINVAL);
}
int ff_set_dimensions(AVCodecContext *avctx, int width, int height)
{
	if (av_image_check_size(width, height, 0, NULL) < 0) return AVERROR(EINVAL);
	avctx->width = avctx->coded_width = width;
	avctx->height = avctx->coded_height = height;
	return 0;
}
typedef struct { AVCodecContext avctx; AVFrame frame; u8 *pic; int pic_w, pic_h, have; } Dec;   /* (avctx first) */
int ff_get_buffer(AVCodecContext *avctx, AVFrame *frame, int flags)
{
	Dec *d = (Dec *)avctx;
	int w = avctx->width, h = avctx->height, cw = (w + 3) >> 2, ch = (h + 3) >> 2;
	(void)flags;
	if (!d->pic || d->pic_w != w || d->pic_h != h) {
		free(d->pic);
		d->pic = malloc((size_t)w * h + 2 * (size_t)cw * ch);
		if (!d->pic) return AVERROR(ENOMEM);
		d->pic_w = w, d->pic_h = h;
	}
	frame->data[0] = d->pic, frame->linesize[0] = w;
	frame->data[1] = d->pic + w * h, frame->linesize[1] = cw;
	frame->data[2] = d->pic + w * h + cw * ch, frame->linesize[2] = cw;
	frame->width = w, frame->height = h;
	return 0;
}

/* YUV 4:1:0 to RGB: BT.601 limited range, the chroma interpolated from its quarter-size grid (iv32.c's) */
static u8 clip8(int v) { return v < 0 ? 0 : v > 255 ? 255 : (u8)v; }
typedef struct { int i0, i1, w1; } Tap;
static void taps(Tap *t, int n, int cn)
{
	for (int x = 0; x < n; x++) {
		int p = (x * 2 - 3) * 32, i = p < 0 ? -1 : p >> 8, f = p - i * 256;
		if (i < 0) i = 0, f = 0;
		if (i >= cn - 1) i = cn - 1, f = 0;
		t[x].i0 = i, t[x].i1 = i + (i < cn - 1), t[x].w1 = f;
	}
}
static void to_rgb(const AVFrame *fr, int w, int h, u8 *out)
{
	int cw = (w + 3) >> 2, ch = (h + 3) >> 2;
	Tap *tx = malloc(sizeof *tx * w), *ty = malloc(sizeof *ty * h);
	int *cu = malloc(sizeof *cu * cw * 2), *cv = cu ? cu + cw : NULL;
	if (tx && ty && cu) {
		taps(tx, w, cw);
		taps(ty, h, ch);
		for (int y = 0; y < h; y++) {
			const u8 *Y = fr->data[0] + y * fr->linesize[0];
			const u8 *U0 = fr->data[1] + ty[y].i0 * fr->linesize[1], *U1 = fr->data[1] + ty[y].i1 * fr->linesize[1];
			const u8 *V0 = fr->data[2] + ty[y].i0 * fr->linesize[2], *V1 = fr->data[2] + ty[y].i1 * fr->linesize[2];
			int wy = ty[y].w1;
			u8 *o = out + (size_t)y * w * 3;
			for (int i = 0; i < cw; i++) {
				cu[i] = U0[i] * (256 - wy) + U1[i] * wy;
				cv[i] = V0[i] * (256 - wy) + V1[i] * wy;
			}
			for (int x = 0; x < w; x++, o += 3) {
				int wx = tx[x].w1;
				int u = ((cu[tx[x].i0] * (256 - wx) + cu[tx[x].i1] * wx + (1 << 15)) >> 16) - 128;
				int v = ((cv[tx[x].i0] * (256 - wx) + cv[tx[x].i1] * wx + (1 << 15)) >> 16) - 128;
				int c = (Y[x] - 16) * 298 + 128;
				o[0] = clip8((c + 516 * u) >> 8);
				o[1] = clip8((c - 100 * u - 208 * v) >> 8);
				o[2] = clip8((c + 409 * v) >> 8);
			}
		}
	}
	free(tx), free(ty), free(cu);
}

/* ---- the movie */
typedef struct { u32 at, size; } Chunk;
static struct {
	int on;
	u8 *file;
	size_t fileSize;
	Chunk *frames;
	int nframes, next;
	u32 rate, scale;   /* frames a second: rate / scale */
	int w, h;
	Dec *dec;
	u8 *rgb;
	unsigned start;
	int escUp;
	const AxisSound *snd;
	void *user, *buffer;
	unsigned audioMs;
} M;

static u32 rd32(const u8 *p) { return (u32)p[0] | (u32)p[1] << 8 | (u32)p[2] << 16 | (u32)p[3] << 24; }
#define FCC(p, s) (memcmp((p), (s), 4) == 0)

/* the chunks of a list (from..to): the headers (strh / strf: which stream is the video, its rate and size, the
   sound's format), the video's frames indexed, the sound's samples appended to pcm */
typedef struct { int video, audio, stream; u8 wfx[18]; u8 *pcm; size_t pcmLen, pcmCap; int nf, cap; } Scan;
static void scan(Scan *s, size_t from, size_t to)
{
	size_t p = from;
	while (p + 8 <= to) {
		const u8 *c = M.file + p;
		u32 n = rd32(c + 4);
		size_t body = p + 8, end = body + n;
		if (end > to)
			end = to;
		if (FCC(c, "LIST") || FCC(c, "RIFF")) {
			if (body + 4 <= end)
				scan(s, body + 4, end);
		} else if (FCC(c, "strh") && n >= 48) {
			s->stream++;
			if (FCC(c + 8, "vids") && s->video < 0) {
				s->video = s->stream - 1;
				M.scale = rd32(c + 8 + 20);
				M.rate = rd32(c + 8 + 24);
			} else if (FCC(c + 8, "auds") && s->audio < 0)
				s->audio = s->stream - 1;
		} else if (FCC(c, "strf")) {
			if (s->stream - 1 == s->video && n >= 40) {
				M.w = (int)rd32(c + 8 + 4);
				M.h = abs((int)rd32(c + 8 + 8));
			} else if (s->stream - 1 == s->audio && n >= 16) {
				memset(s->wfx, 0, sizeof s->wfx);
				memcpy(s->wfx, c + 8, n < 18 ? n : 18);
			}
		} else if (c[0] >= '0' && c[0] <= '9' && c[1] >= '0' && c[1] <= '9') {
			int k = (c[0] - '0') * 10 + (c[1] - '0');
			if (k == s->video && (c[2] == 'd')) {
				if (s->nf == s->cap) {
					s->cap = s->cap ? s->cap * 2 : 4096;
					M.frames = realloc(M.frames, sizeof *M.frames * s->cap);
				}
				M.frames[s->nf].at = (u32)body;
				M.frames[s->nf].size = (u32)(end - body);
				s->nf++;
			} else if (k == s->audio && c[2] == 'w') {
				size_t len = end - body;
				if (s->pcmLen + len > s->pcmCap) {
					s->pcmCap = (s->pcmLen + len) * 2;
					s->pcm = realloc(s->pcm, s->pcmCap);
				}
				memcpy(s->pcm + s->pcmLen, M.file + body, len);
				s->pcmLen += len;
			}
		}
		p = body + n + (n & 1);
	}
}

static void movie_end(int why)
{
	hlog("ending movie: ended (%s) after %u ms, %d of %d frames\n", why == 1 ? "Esc" : why == 2 ? "finished" : "failed",
	     platform_ticks() - M.start, M.next, M.nframes);
	if (M.buffer && M.snd && M.snd->release)
		M.snd->release(M.user, M.buffer);
	if (M.dec) {
		ff_indeo3_decoder.close(&M.dec->avctx);
		free(M.dec->avctx.priv_data);
		free(M.dec->pic);
		free(M.dec);
	}
	free(M.frames);
	free(M.file);
	free(M.rgb);
	memset(&M, 0, sizeof M);
}

int movie64_start(const char *path, const void *sound, void *user)
{
	const AxisSound *snd = sound;
	if (M.on)
		return 1;
	memset(&M, 0, sizeof M);
	FILE *f = fopen(path, "rb");
	if (!f) {
		hlog("ending movie: %s not found\n", path);
		return 0;
	}
	fseek(f, 0, SEEK_END);
	M.fileSize = (size_t)ftell(f);
	fseek(f, 0, SEEK_SET);
	M.file = malloc(M.fileSize ? M.fileSize : 1);
	if (!M.file || fread(M.file, 1, M.fileSize, f) != M.fileSize) {
		fclose(f);
		free(M.file);
		M.file = NULL;
		return 0;
	}
	fclose(f);
	Scan s = { -1, -1, 0, { 0 }, NULL, 0, 0, 0, 0 };
	if (M.fileSize < 12 || !FCC(M.file, "RIFF") || !FCC(M.file + 8, "AVI "))
		goto bad;
	scan(&s, 12, M.fileSize);
	M.nframes = s.nf;
	if (!M.nframes || M.w <= 0 || M.h <= 0 || !M.rate || !M.scale)
		goto bad;
	M.dec = calloc(1, sizeof *M.dec);
	M.dec->avctx.width = M.dec->avctx.coded_width = M.w;
	M.dec->avctx.height = M.dec->avctx.coded_height = M.h;
	M.dec->avctx.priv_data = calloc(1, ff_indeo3_decoder.priv_data_size);
	if (!M.dec->avctx.priv_data || ff_indeo3_decoder.init(&M.dec->avctx) < 0)
		goto bad;
	M.rgb = calloc((size_t)M.w * M.h, 3);
	M.snd = snd;
	M.user = user;
	if (snd && s.pcmLen && rd32(s.wfx) != 0) {   /* (the sound: one buffer, played once) */
		if (snd->music_run)
			snd->music_run(user, 0);
		M.buffer = snd->create(user, s.wfx, (unsigned)s.pcmLen);
		if (M.buffer) {
			snd->write(user, M.buffer, s.pcm, (unsigned)s.pcmLen);
			snd->volume(user, M.buffer, 0);
			snd->play(user, M.buffer, 0);
			u32 bytesPerSec = rd32(s.wfx + 8);
			M.audioMs = bytesPerSec ? (unsigned)(s.pcmLen * 1000 / bytesPerSec) : 0;
		}
	}
	free(s.pcm);
	M.on = 1;
	M.start = platform_ticks();
	hlog("ending movie: %s - %dx%d, %d frames at %u/%u a second, sound %u ms (%s)\n", path, M.w, M.h, M.nframes, M.rate,
	     M.scale, M.audioMs, M.buffer ? "playing" : "none");
	return 1;
bad:
	free(s.pcm);
	hlog("ending movie: %s could not be read\n", path);
	movie_end(0);
	return 0;
}

int movie64_active(void) { return M.on; }

/* one host frame of the movie: the frames due by now decoded (each, in order: Indeo 3 frames build on the last), the
   newest drawn; Esc (pressed during the movie) or the end stops it */
void movie64_frame(const u8 keys[256])
{
	if (!M.on)
		return;
	unsigned t = platform_ticks() - M.start;
	if (keys[0x01] & 0x80) {
		if (M.escUp) {
			movie_end(1);
			return;
		}
	} else
		M.escUp = 1;
	int due = (int)((unsigned long long)t * M.rate / (1000ull * M.scale)) + 1;
	if (due > M.nframes)
		due = M.nframes;
	int fresh = 0;
	while (M.next < due) {
		const Chunk *c = &M.frames[M.next++];
		if (c->size) {
			AVPacket pkt = { 0 };
			int got = 0;
			pkt.data = M.file + c->at;
			pkt.size = (int)c->size;
			if (ff_indeo3_decoder.cb.decode(&M.dec->avctx, &M.dec->frame, &got, &pkt) >= 0 && got)
				M.dec->have = fresh = 1;
		}
	}
	if (fresh)
		to_rgb(&M.dec->frame, M.w, M.h, M.rgb);
	glrec64_movieFrame(fresh ? M.rgb : NULL, M.w, M.h);
	unsigned length = (unsigned)((unsigned long long)M.nframes * 1000 * M.scale / M.rate);
	if (M.next >= M.nframes && t >= length && t >= M.audioMs)
		movie_end(2);
}
#endif
