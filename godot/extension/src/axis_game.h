// axis_game.h: AxisGame, the game itself running in Godot. axis.dll (the portable build, PORTABLE=3) is loaded
// in-process and driven frame by frame from _process; its drawing comes back each frame as a command stream
// (axis_api.h's frame callback) and is drawn with AxisReplay's renderer; Godot's keyboard and mouse are its input.
// The game's own window exists but stays hidden (its messages - timers, sockets - still arrive through Godot's
// message loop).
#pragma once
#include "axis_replay.h"
#include <cstdio>
#include <godot_cpp/classes/input_event.hpp>
#include "host_win.h"
#include "axis_audio.h"
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_generator_playback.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>

namespace godot {

class AxisGame : public AxisReplay {
	GDCLASS(AxisGame, AxisReplay)

public:
	bool start(const String &p_game_dir, const String &p_library, bool p_driver = false, bool p_raw_mouse = false);
	bool is_running() const { return running; }
	int get_game_frames() const { return gameFrames; }
	Vector2i get_game_size() const { return Vector2i(lastW, lastH); }
	String get_audio_status();
	String get_input_status();
	String take_frame_events();
	static int s_message(void *user, const char *title, const char *text);   // (the game's message boxes: OS.alert)
	static int s_launch(void *user, const char *program, const char *arguments);   // (AxisGL.exe: the game restarted)
	bool restartRequested = false;
	bool start_recording(const String &p_path);   // the game's drawing to an AXGLREC1 file (main.tscn replays it)
	void stop_recording();
	void set_music_near_end(double s) { musicNearEnd = s; }   // (a check: each track started s seconds before its end)   // (the frame log: game steps that took long, and the frames drawn in them)
	void _process(double p_delta) override;
	void _input(const Ref<InputEvent> &p_event) override;

protected:
	static void _bind_methods();

private:
	AxisFunctions api = {};
	bool running = false;
	int gameFrames = 0;
	int lastW = 0, lastH = 0;
	unsigned char keys[256] = {};
	float moveX = 0, moveY = 0;
	int wheel = 0;
	unsigned buttons = 0;
	Vector2 pointer;
	// (the input log: what came from Godot and went to the game since the last get_input_status)
	int nMotion = 0, nButton = 0;
	double relX = 0, relY = 0, srelX = 0, srelY = 0;
	long sentX = 0, sentY = 0;
	bool rawMouse = false;
	void *hostWindow = nullptr;   // Godot's window (confining the pointer)
	bool confined = false;
	int rawRetaken = 0;
	String frameEvents;
	String keyEvents;
	double musicNearEnd = 0;
	FILE *record = nullptr;
	std::vector<unsigned char> streamHeader;
	int musicLoops = 0;   // (the game's seeks: a track looped)   // (the input log: key events since the last status)
	bool rawSeen = false;
	bool cursorMouse = false;   // the movement as the cursor moves (the original's); else raw counts (--raw-mouse)
	// (a long game step - a loading screen - shown as it draws: RenderingServer.force_draw from the frame callback)
	bool inStep = false;
	uint64_t stepStart = 0, lastShown = 0;
	int shownInStep = 0, framesInStep = 0;   // the raw reader has had events (until then Godot's motion events are used)   // the mouse's movement read as raw input (host_win.c), not from Godot's motion events
	int nRaw = 0;
	static void on_frame(void *user, const unsigned *words, unsigned count, int width, int height);
	// the sound (AxisSound): the buffers mixed here into a generator stream; the music an MP3 player
	AxisMixer mixer;
	AudioStreamPlayer *sfx = nullptr, *music = nullptr;
	Ref<AudioStreamGeneratorPlayback> playback;
	Ref<AudioStreamMP3> musicStream;
	String gameDir;
	double musicSeekTo = 0;
	void feed_audio();
	static const AxisSound k_sound;
	static void *s_create(void *u, const void *f, unsigned b);
	static void *s_duplicate(void *u, void *b);
	static void s_write(void *u, void *b, const void *d, unsigned n);
	static void s_play(void *u, void *b, int loop);
	static void s_volume(void *u, void *b, int v);
	static void s_pan(void *u, void *b, int p);
	static void s_release(void *u, void *b);
	static int m_open(void *u, const char *file);
	static void m_run(void *u, int run);
	static double m_time(void *u);
	static double m_length(void *u);
	static void m_seek(void *u, double s);
	static void m_close(void *u);
	void release_all();
};

} // namespace godot
