// axis_audio.h: the game's sound buffers mixed as DirectSound mixes them (src/axis_api.h AxisSound) - PCM samples
// (8 or 16 bit, mono or stereo, any rate) played once or looping, a volume in hundredths of a decibel and a pan
// (DirectSound's law: the far side attenuated), resampled to the output rate and summed. No Godot dependency:
// AxisGame feeds the mix to a Godot AudioStreamGenerator.
#pragma once
#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>

class AxisMixer {
public:
	struct Samples { std::vector<float> l, r; double rate = 44100; };
	struct Voice {
		std::shared_ptr<Samples> s;
		int channels = 1, bits = 16;
		bool playing = false, loop = false;
		double pos = 0;
		float gainL = 1, gainR = 1, volume = 1, panL = 1, panR = 1;
	};
	explicit AxisMixer(double outRate = 44100) : rate(outRate) {}
	~AxisMixer();
	Voice *create(const void *waveFormat, unsigned bytes);
	Voice *duplicate(Voice *v);
	void write(Voice *v, const void *data, unsigned bytes);
	void play(Voice *v, bool loop);
	void set_volume(Voice *v, int hundredthsOfDb);
	void set_pan(Voice *v, int pan);
	void release(Voice *v);
	// frames of stereo float output, interleaved L R
	void mix(float *out, int frames);
	int playing_count() const;
	float peak = 0;   // the largest output sample since it was last read (AxisGame's audio status)

private:
	double rate;
	std::unordered_set<Voice *> voices;
	static void gains(Voice *v);
};
