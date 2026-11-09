// axis_movie.cpp: AxisMovie (axis_movie.h).
#include "axis_movie.h"
#include <godot_cpp/core/class_db.hpp>
#include <string.h>
#include "../../../standalone/avimovie.h"

using namespace godot;

AxisMovie::~AxisMovie() { close(); }

bool AxisMovie::open(const String &p_path) {
	close();
	movie = avimovie_open(p_path.utf8().get_data());
	return movie != nullptr;
}

void AxisMovie::close() {
	avimovie_close(movie);
	movie = nullptr;
}

int AxisMovie::get_width() const { return movie ? avimovie_info(movie)->width : 0; }
int AxisMovie::get_height() const { return movie ? avimovie_info(movie)->height : 0; }
int AxisMovie::get_frame_count() const { return movie ? avimovie_info(movie)->frames : 0; }
double AxisMovie::get_fps() const {
	if (!movie)
		return 0;
	const AviMovieInfo *i = avimovie_info(movie);
	return i->scale ? (double)i->rate / i->scale : 0;
}
bool AxisMovie::decode_to(int p_due) { return movie && avimovie_decode_to(movie, p_due); }
int AxisMovie::get_next_frame() const { return movie ? avimovie_next(movie) : 0; }

Ref<Image> AxisMovie::get_image() const {
	if (!movie)
		return Ref<Image>();
	const AviMovieInfo *i = avimovie_info(movie);
	PackedByteArray px;
	px.resize((int64_t)i->width * i->height * 3);
	memcpy(px.ptrw(), avimovie_rgb(movie), (size_t)px.size());
	return Image::create_from_data(i->width, i->height, false, Image::FORMAT_RGB8, px);
}

PackedByteArray AxisMovie::get_audio() const {
	PackedByteArray a;
	if (!movie || !avimovie_info(movie)->pcm)
		return a;
	const AviMovieInfo *i = avimovie_info(movie);
	a.resize((int64_t)i->pcmBytes);
	memcpy(a.ptrw(), i->pcm, i->pcmBytes);
	const uint8_t *w = i->waveFormat;
	if ((w[14] | w[15] << 8) == 8) {   // (8-bit PCM is unsigned in a WAV file, signed in Godot's AudioStreamWAV)
		uint8_t *p = a.ptrw();
		for (size_t k = 0; k < i->pcmBytes; k++)
			p[k] ^= 0x80;
	}
	return a;
}
static int wfx_field(const AviMovie *m, int at, int bytes) {
	if (!m || !avimovie_info(m)->waveFormat)
		return 0;
	const uint8_t *w = avimovie_info(m)->waveFormat + at;
	return bytes == 2 ? w[0] | w[1] << 8 : (int)(w[0] | w[1] << 8 | w[2] << 16 | (uint32_t)w[3] << 24);
}
int AxisMovie::get_audio_channels() const { return wfx_field(movie, 2, 2); }
int AxisMovie::get_audio_rate() const { return wfx_field(movie, 4, 4); }
int AxisMovie::get_audio_bits() const { return wfx_field(movie, 14, 2); }

void AxisMovie::_bind_methods() {
	ClassDB::bind_method(D_METHOD("open", "path"), &AxisMovie::open);
	ClassDB::bind_method(D_METHOD("close"), &AxisMovie::close);
	ClassDB::bind_method(D_METHOD("get_width"), &AxisMovie::get_width);
	ClassDB::bind_method(D_METHOD("get_height"), &AxisMovie::get_height);
	ClassDB::bind_method(D_METHOD("get_frame_count"), &AxisMovie::get_frame_count);
	ClassDB::bind_method(D_METHOD("get_fps"), &AxisMovie::get_fps);
	ClassDB::bind_method(D_METHOD("decode_to", "due"), &AxisMovie::decode_to);
	ClassDB::bind_method(D_METHOD("get_next_frame"), &AxisMovie::get_next_frame);
	ClassDB::bind_method(D_METHOD("get_image"), &AxisMovie::get_image);
	ClassDB::bind_method(D_METHOD("get_audio"), &AxisMovie::get_audio);
	ClassDB::bind_method(D_METHOD("get_audio_rate"), &AxisMovie::get_audio_rate);
	ClassDB::bind_method(D_METHOD("get_audio_channels"), &AxisMovie::get_audio_channels);
	ClassDB::bind_method(D_METHOD("get_audio_bits"), &AxisMovie::get_audio_bits);
}
