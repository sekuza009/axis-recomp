// axis_audio.cpp: see axis_audio.h.
#include "axis_audio.h"

#include <cmath>
#include <cstring>

AxisMixer::~AxisMixer() {
	for (Voice *v : voices) delete v;
}

AxisMixer::Voice *AxisMixer::create(const void *waveFormat, unsigned bytes) {
	(void)bytes;
	// WAVEFORMATEX: format tag, channels, samples per second, bytes per second, block align, bits per sample
	uint16_t tag, channels, bits;
	uint32_t samplesPerSec;
	memcpy(&tag, waveFormat, 2);
	memcpy(&channels, (const char *)waveFormat + 2, 2);
	memcpy(&samplesPerSec, (const char *)waveFormat + 4, 4);
	memcpy(&bits, (const char *)waveFormat + 14, 2);
	if (tag != 1 || (bits != 8 && bits != 16) || channels < 1 || channels > 2) return nullptr;   // (PCM only)
	Voice *v = new Voice;
	v->s = std::make_shared<Samples>();
	v->s->rate = samplesPerSec ? samplesPerSec : 22050;
	v->channels = channels;
	v->bits = bits;
	voices.insert(v);
	return v;
}

AxisMixer::Voice *AxisMixer::duplicate(Voice *src) {
	if (!src) return nullptr;
	Voice *v = new Voice;
	v->s = src->s;   // (the same samples; its own play state, volume and pan)
	v->channels = src->channels;
	v->bits = src->bits;
	voices.insert(v);
	return v;
}

void AxisMixer::write(Voice *v, const void *data, unsigned bytes) {
	if (!v) return;
	const int frameBytes = v->channels * v->bits / 8;
	const size_t n = frameBytes ? bytes / frameBytes : 0;
	Samples &s = *v->s;
	s.l.resize(n);
	s.r.resize(n);
	const uint8_t *p = (const uint8_t *)data;
	for (size_t i = 0; i < n; i++) {
		float c[2];
		for (int k = 0; k < v->channels; k++) {
			const uint8_t *e = p + i * frameBytes + k * (v->bits / 8);
			if (v->bits == 8) c[k] = ((int)e[0] - 128) / 128.0f;
			else { int16_t x; memcpy(&x, e, 2); c[k] = x / 32768.0f; }
		}
		s.l[i] = c[0];
		s.r[i] = v->channels == 2 ? c[1] : c[0];
	}
}

// DirectSound: Play on a playing buffer only changes its looping; a stopped one starts from the beginning
void AxisMixer::play(Voice *v, bool loop) {
	if (!v) return;
	if (!v->playing) {
		v->pos = 0;
		v->playing = true;
	}
	v->loop = loop;
}

void AxisMixer::gains(Voice *v) {
	v->gainL = v->volume * v->panL;
	v->gainR = v->volume * v->panR;
}

void AxisMixer::set_volume(Voice *v, int cb) {
	if (!v) return;
	if (cb > 0) cb = 0;
	v->volume = cb <= -10000 ? 0.0f : (float)std::pow(10.0, cb / 2000.0);
	gains(v);
}

// DirectSound's pan: the other side attenuated by |pan| hundredths of a decibel
void AxisMixer::set_pan(Voice *v, int pan) {
	if (!v) return;
	if (pan > 10000) pan = 10000;
	if (pan < -10000) pan = -10000;
	v->panL = pan > 0 ? (pan >= 10000 ? 0.0f : (float)std::pow(10.0, -pan / 2000.0)) : 1.0f;
	v->panR = pan < 0 ? (pan <= -10000 ? 0.0f : (float)std::pow(10.0, pan / 2000.0)) : 1.0f;
	gains(v);
}

void AxisMixer::release(Voice *v) {
	if (!v) return;
	voices.erase(v);
	delete v;
}

void AxisMixer::mix(float *out, int frames) {
	memset(out, 0, sizeof(float) * 2 * frames);
	for (Voice *v : voices) {
		if (!v->playing) continue;
		const Samples &s = *v->s;
		const size_t n = s.l.size();
		if (!n) { v->playing = false; continue; }
		const double step = s.rate / rate;
		for (int f = 0; f < frames; f++) {
			if (v->pos >= (double)n) {
				if (v->loop) v->pos = std::fmod(v->pos, (double)n);
				else { v->playing = false; v->pos = 0; break; }
			}
			const size_t i = (size_t)v->pos;
			const float t = (float)(v->pos - (double)i);
			const size_t j = i + 1 < n ? i + 1 : (v->loop ? 0 : i);
			out[2 * f] += (s.l[i] + (s.l[j] - s.l[i]) * t) * v->gainL;
			out[2 * f + 1] += (s.r[i] + (s.r[j] - s.r[i]) * t) * v->gainR;
			v->pos += step;
		}
	}
	for (int k = 0; k < 2 * frames; k++) {   // (DirectSound clips the mix)
		const float a = out[k] < 0 ? -out[k] : out[k];
		if (a > peak) peak = a;
		if (out[k] > 1) out[k] = 1;
		else if (out[k] < -1) out[k] = -1;
	}
}

int AxisMixer::playing_count() const {
	int n = 0;
	for (Voice *v : voices) n += v->playing;
	return n;
}
