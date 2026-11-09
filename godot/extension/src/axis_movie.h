// axis_movie.h: AxisMovie - one of the game's movies (initdata/interface.sra, battle.sra) read and decoded for the
// launcher's cinematics (project/launcher_movie.gd), with the library's reader and Indeo 3 decoder
// (standalone/avimovie.c, FFmpeg's indeo3).
#pragma once
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

struct AviMovie;

namespace godot {

class AxisMovie : public RefCounted {
	GDCLASS(AxisMovie, RefCounted)

public:
	~AxisMovie();
	bool open(const String &p_path);
	void close();
	int get_width() const;
	int get_height() const;
	int get_frame_count() const;
	double get_fps() const;
	// the frames before 'due' decoded, in order: true when the picture changed
	bool decode_to(int p_due);
	int get_next_frame() const;
	Ref<Image> get_image() const;   // the picture (RGB8)
	// the sound (PCM; 8-bit samples made signed, as AudioStreamWAV takes them), and its format; empty when there is none
	PackedByteArray get_audio() const;
	int get_audio_rate() const;
	int get_audio_channels() const;
	int get_audio_bits() const;

protected:
	static void _bind_methods();

private:
	AviMovie *movie = nullptr;
};

} // namespace godot
