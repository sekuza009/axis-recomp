/* avimovie.c: the game's movies read and decoded (avimovie.h) - an AVI reader and FFmpeg's indeo3 decoder
   (../axisnet/iv32/ffmpeg, unmodified, LGPL 2.1+; the same code the 32-bit build's iv32 hands to Windows' MCI), with the
   few libav runtime functions it calls and the YUV 4:1:0 to RGB conversion of iv32.c. Plain C, any platform. Build with
   -DHAVE_AV_CONFIG_H -I../axisnet/iv32/ffmpeg and link ffmpeg's libavcodec/indeo3.c and hpeldsp.c. */
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
#include "avimovie.h"

typedef uint8_t u8;
typedef uint32_t u32;
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
typedef struct { AVCodecContext avctx; AVFrame frame; u8 *pic; int pic_w, pic_h; } Dec;   /* (avctx first) */
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
struct AviMovie {
	AviMovieInfo info;
	u8 *file;
	size_t fileSize;
	Chunk *frames;
	int next, cap;
	int video, audio, stream;
	u8 wfx[18];
	u8 *pcm;
	size_t pcmLen, pcmCap;
	Dec *dec;
	u8 *rgb;
};

static u32 rd32(const u8 *p) { return (u32)p[0] | (u32)p[1] << 8 | (u32)p[2] << 16 | (u32)p[3] << 24; }
#define FCC(p, s) (memcmp((p), (s), 4) == 0)

/* the chunks of a list (from..to): the headers (strh / strf: which stream is the video, its rate and size, the
   sound's format), the video's frames indexed, the sound's samples appended */
static void scan(AviMovie *m, size_t from, size_t to)
{
	size_t p = from;
	while (p + 8 <= to) {
		const u8 *c = m->file + p;
		u32 n = rd32(c + 4);
		size_t body = p + 8, end = body + n;
		if (end > to)
			end = to;
		if (FCC(c, "LIST") || FCC(c, "RIFF")) {
			if (body + 4 <= end)
				scan(m, body + 4, end);
		} else if (FCC(c, "strh") && n >= 48) {
			m->stream++;
			if (FCC(c + 8, "vids") && m->video < 0) {
				m->video = m->stream - 1;
				m->info.scale = rd32(c + 8 + 20);
				m->info.rate = rd32(c + 8 + 24);
			} else if (FCC(c + 8, "auds") && m->audio < 0)
				m->audio = m->stream - 1;
		} else if (FCC(c, "strf")) {
			if (m->stream - 1 == m->video && n >= 40) {
				m->info.width = (int)rd32(c + 8 + 4);
				m->info.height = abs((int)rd32(c + 8 + 8));
			} else if (m->stream - 1 == m->audio && n >= 16) {
				memset(m->wfx, 0, sizeof m->wfx);
				memcpy(m->wfx, c + 8, n < 18 ? n : 18);
			}
		} else if (c[0] >= '0' && c[0] <= '9' && c[1] >= '0' && c[1] <= '9') {
			int k = (c[0] - '0') * 10 + (c[1] - '0');
			if (k == m->video && c[2] == 'd') {
				if (m->info.frames == m->cap) {
					m->cap = m->cap ? m->cap * 2 : 4096;
					m->frames = realloc(m->frames, sizeof *m->frames * m->cap);
				}
				m->frames[m->info.frames].at = (u32)body;
				m->frames[m->info.frames].size = (u32)(end - body);
				m->info.frames++;
			} else if (k == m->audio && c[2] == 'w') {
				size_t len = end - body;
				if (m->pcmLen + len > m->pcmCap) {
					m->pcmCap = (m->pcmLen + len) * 2;
					m->pcm = realloc(m->pcm, m->pcmCap);
				}
				memcpy(m->pcm + m->pcmLen, m->file + body, len);
				m->pcmLen += len;
			}
		}
		p = body + n + (n & 1);
	}
}

void avimovie_close(AviMovie *m)
{
	if (!m)
		return;
	if (m->dec) {
		if (m->dec->avctx.priv_data)
			ff_indeo3_decoder.close(&m->dec->avctx);
		free(m->dec->avctx.priv_data);
		free(m->dec->pic);
		free(m->dec);
	}
	free(m->frames);
	free(m->file);
	free(m->pcm);
	free(m->rgb);
	free(m);
}

AviMovie *avimovie_open(const char *path)
{
	FILE *f = fopen(path, "rb");
	if (!f)
		return NULL;
	AviMovie *m = calloc(1, sizeof *m);
	if (!m) {
		fclose(f);
		return NULL;
	}
	m->video = m->audio = -1;
	fseek(f, 0, SEEK_END);
	long size = ftell(f);
	fseek(f, 0, SEEK_SET);
	m->fileSize = size > 0 ? (size_t)size : 0;
	m->file = malloc(m->fileSize ? m->fileSize : 1);
	int ok = m->file && fread(m->file, 1, m->fileSize, f) == m->fileSize;
	fclose(f);
	if (!ok || m->fileSize < 12 || !FCC(m->file, "RIFF") || !FCC(m->file + 8, "AVI "))
		goto bad;
	scan(m, 12, m->fileSize);
	AviMovieInfo *i = &m->info;
	if (!i->frames || i->width <= 0 || i->height <= 0 || !i->rate || !i->scale)
		goto bad;
	m->dec = calloc(1, sizeof *m->dec);
	if (!m->dec)
		goto bad;
	m->dec->avctx.width = m->dec->avctx.coded_width = i->width;
	m->dec->avctx.height = m->dec->avctx.coded_height = i->height;
	m->dec->avctx.priv_data = calloc(1, ff_indeo3_decoder.priv_data_size);
	if (!m->dec->avctx.priv_data || ff_indeo3_decoder.init(&m->dec->avctx) < 0) {
		free(m->dec->avctx.priv_data);
		m->dec->avctx.priv_data = NULL;
		goto bad;
	}
	m->rgb = calloc((size_t)i->width * i->height, 3);
	if (!m->rgb)
		goto bad;
	if (m->pcmLen && rd32(m->wfx) != 0) {
		i->pcm = m->pcm;
		i->pcmBytes = m->pcmLen;
		i->waveFormat = m->wfx;
	}
	return m;
bad:
	avimovie_close(m);
	return NULL;
}

const AviMovieInfo *avimovie_info(const AviMovie *m) { return &m->info; }
int avimovie_next(const AviMovie *m) { return m->next; }
const uint8_t *avimovie_rgb(const AviMovie *m) { return m->rgb; }

int avimovie_decode_to(AviMovie *m, int due)
{
	if (due > m->info.frames)
		due = m->info.frames;
	int fresh = 0;
	while (m->next < due) {
		const Chunk *c = &m->frames[m->next++];
		if (!c->size)
			continue;
		AVPacket pkt = { 0 };
		int got = 0;
		pkt.data = m->file + c->at;
		pkt.size = (int)c->size;
		if (ff_indeo3_decoder.cb.decode(&m->dec->avctx, &m->dec->frame, &got, &pkt) >= 0 && got)
			fresh = 1;
	}
	if (fresh)
		to_rgb(&m->dec->frame, m->info.width, m->info.height, m->rgb);
	return fresh;
}
