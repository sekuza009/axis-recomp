// axis_game.h: AxisGame, the game itself running in Godot. axis.dll (the portable build, PORTABLE=3) is loaded
// in-process and driven frame by frame from _process; its drawing comes back each frame as a command stream
// (axis_api.h's frame callback) and is drawn with AxisReplay's renderer; Godot's keyboard and mouse are its input.
// The game's own window exists but stays hidden (its messages - timers, sockets - still arrive through Godot's
// message loop).
#pragma once
#include "axis_replay.h"
#include <godot_cpp/classes/input_event.hpp>
#include "host_win.h"

namespace godot {

class AxisGame : public AxisReplay {
	GDCLASS(AxisGame, AxisReplay)

public:
	bool start(const String &p_game_dir, const String &p_library);
	bool is_running() const { return running; }
	int get_game_frames() const { return gameFrames; }
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
	static void on_frame(void *user, const unsigned *words, unsigned count, int width, int height);
	void release_all();
};

} // namespace godot
