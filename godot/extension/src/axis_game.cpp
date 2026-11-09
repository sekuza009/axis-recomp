// axis_game.cpp: see axis_game.h.
#include "axis_game.h"

#include <godot_cpp/classes/audio_stream_generator.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include <vector>

using namespace godot;

namespace {

// a Godot key (physical, by its place on a US layout) -> its DirectInput code (the PC scan code; extended + 0x80)
int dik_of(Key k, KeyLocation where) {
	if (k >= KEY_A && k <= KEY_Z) {
		static const unsigned char letters[26] = { 0x1e, 0x30, 0x2e, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24, 0x25, 0x26, 0x32,
			0x31, 0x18, 0x19, 0x10, 0x13, 0x1f, 0x14, 0x16, 0x2f, 0x11, 0x2d, 0x15, 0x2c };
		return letters[k - KEY_A];
	}
	if (k >= KEY_1 && k <= KEY_9) return 0x02 + (k - KEY_1);
	if (k >= KEY_F1 && k <= KEY_F10) return 0x3b + (k - KEY_F1);
	switch (k) {
	case KEY_0: return 0x0b;
	case KEY_ESCAPE: return 0x01;
	case KEY_MINUS: return 0x0c;
	case KEY_EQUAL: return 0x0d;
	case KEY_BACKSPACE: return 0x0e;
	case KEY_TAB: return 0x0f;
	case KEY_BRACKETLEFT: return 0x1a;
	case KEY_BRACKETRIGHT: return 0x1b;
	case KEY_ENTER: return 0x1c;
	case KEY_KP_ENTER: return 0x9c;
	case KEY_CTRL: return where == KEY_LOCATION_RIGHT ? 0x9d : 0x1d;
	case KEY_SEMICOLON: return 0x27;
	case KEY_APOSTROPHE: return 0x28;
	case KEY_QUOTELEFT: return 0x29;
	case KEY_SHIFT: return where == KEY_LOCATION_RIGHT ? 0x36 : 0x2a;
	case KEY_BACKSLASH: return 0x2b;
	case KEY_COMMA: return 0x33;
	case KEY_PERIOD: return 0x34;
	case KEY_SLASH: return 0x35;
	case KEY_ALT: return where == KEY_LOCATION_RIGHT ? 0xb8 : 0x38;
	case KEY_SPACE: return 0x39;
	case KEY_CAPSLOCK: return 0x3a;
	case KEY_F11: return 0x57;
	case KEY_F12: return 0x58;
	case KEY_HOME: return 0xc7;
	case KEY_UP: return 0xc8;
	case KEY_PAGEUP: return 0xc9;
	case KEY_LEFT: return 0xcb;
	case KEY_RIGHT: return 0xcd;
	case KEY_END: return 0xcf;
	case KEY_DOWN: return 0xd0;
	case KEY_PAGEDOWN: return 0xd1;
	case KEY_INSERT: return 0xd2;
	case KEY_DELETE: return 0xd3;
	default: return -1;
	}
}

// the Windows virtual-key code of the keys a text field acts on (Enter, Esc, Tab, Backspace, the arrows...)
unsigned vk_of(Key k) {
	switch (k) {
	case KEY_ENTER: case KEY_KP_ENTER: return 0x0d;
	case KEY_ESCAPE: return 0x1b;
	case KEY_TAB: return 0x09;
	case KEY_BACKSPACE: return 0x08;
	case KEY_LEFT: return 0x25;
	case KEY_UP: return 0x26;
	case KEY_RIGHT: return 0x27;
	case KEY_DOWN: return 0x28;
	case KEY_HOME: return 0x24;
	case KEY_END: return 0x23;
	case KEY_DELETE: return 0x2e;
	case KEY_SHIFT: return 0x10;
	default: return 0;
	}
}

} // namespace

void AxisGame::_bind_methods() {
	ClassDB::bind_method(D_METHOD("start", "game_dir", "library", "driver"), &AxisGame::start, DEFVAL(false));
	ClassDB::bind_method(D_METHOD("is_running"), &AxisGame::is_running);
	ClassDB::bind_method(D_METHOD("get_game_frames"), &AxisGame::get_game_frames);
	ClassDB::bind_method(D_METHOD("get_game_size"), &AxisGame::get_game_size);
	ClassDB::bind_method(D_METHOD("get_audio_status"), &AxisGame::get_audio_status);
	ClassDB::bind_method(D_METHOD("get_input_status"), &AxisGame::get_input_status);
}

void AxisGame::on_frame(void *user, const unsigned *words, unsigned count, int width, int height) {
	AxisGame *g = static_cast<AxisGame *>(user);
	g->emu.run_words(words, count, width, height);
	g->submit(width, height);
	g->lastW = width;
	g->lastH = height;
	g->gameFrames++;
}

// ---- the sound: the game's buffers into the mixer, its music into an MP3 player ----
const AxisSound AxisGame::k_sound = { &AxisGame::s_create, &AxisGame::s_duplicate, &AxisGame::s_write, &AxisGame::s_play,
	&AxisGame::s_volume, &AxisGame::s_pan, &AxisGame::s_release, &AxisGame::m_open, &AxisGame::m_run, &AxisGame::m_time,
	&AxisGame::m_length, &AxisGame::m_seek, &AxisGame::m_close };
void *AxisGame::s_create(void *u, const void *f, unsigned b) { return static_cast<AxisGame *>(u)->mixer.create(f, b); }
void *AxisGame::s_duplicate(void *u, void *b) { return static_cast<AxisGame *>(u)->mixer.duplicate((AxisMixer::Voice *)b); }
void AxisGame::s_write(void *u, void *b, const void *d, unsigned n) { static_cast<AxisGame *>(u)->mixer.write((AxisMixer::Voice *)b, d, n); }
void AxisGame::s_play(void *u, void *b, int loop) { static_cast<AxisGame *>(u)->mixer.play((AxisMixer::Voice *)b, loop != 0); }
void AxisGame::s_volume(void *u, void *b, int v) { static_cast<AxisGame *>(u)->mixer.set_volume((AxisMixer::Voice *)b, v); }
void AxisGame::s_pan(void *u, void *b, int p) { static_cast<AxisGame *>(u)->mixer.set_pan((AxisMixer::Voice *)b, p); }
void AxisGame::s_release(void *u, void *b) { static_cast<AxisGame *>(u)->mixer.release((AxisMixer::Voice *)b); }
int AxisGame::m_open(void *u, const char *file) {
	AxisGame *g = static_cast<AxisGame *>(u);
	const String path = g->gameDir.path_join(String(file).replace("\\", "/"));
	const PackedByteArray data = FileAccess::get_file_as_bytes(path);
	if (data.is_empty()) return 1;
	g->musicStream.instantiate();
	g->musicStream->set_data(data);
	g->music->set_stream(g->musicStream);
	g->musicSeekTo = 0;
	return 0;
}
void AxisGame::m_run(void *u, int run) {
	AxisGame *g = static_cast<AxisGame *>(u);
	if (!g->musicStream.is_valid()) return;
	if (run) { if (!g->music->is_playing()) g->music->play((float)g->musicSeekTo); }
	else g->music->stop();
}
double AxisGame::m_time(void *u) {
	AxisGame *g = static_cast<AxisGame *>(u);
	if (!g->music->is_playing()) return g->musicStream.is_valid() ? g->musicStream->get_length() : 0;   // (finished: at its end)
	return g->music->get_playback_position();
}
double AxisGame::m_length(void *u) {
	AxisGame *g = static_cast<AxisGame *>(u);
	return g->musicStream.is_valid() ? g->musicStream->get_length() : 0;
}
void AxisGame::m_seek(void *u, double s) {
	AxisGame *g = static_cast<AxisGame *>(u);
	g->musicSeekTo = s;
	if (g->musicStream.is_valid()) g->music->play((float)s);   // (the game seeks to replay from the start)
}
void AxisGame::m_close(void *u) {
	AxisGame *g = static_cast<AxisGame *>(u);
	g->music->stop();
	g->music->set_stream(Ref<AudioStream>());
	g->musicStream.unref();
}

String AxisGame::get_input_status() {
	const char *modes[] = { "visible", "hidden", "captured", "confined", "confined_hidden" };
	const int mode = (int)Input::get_singleton()->get_mouse_mode();
	String s = String("mouse mode ") + (mode >= 0 && mode < 5 ? modes[mode] : "?") + ", focused " + (get_window() && get_window()->has_focus() ? "yes" : "no") +
		", motion events " + String::num_int64(nMotion) + " (relative " + String::num(relX, 1) + ", " + String::num(relY, 1) +
		"; screen relative " + String::num(srelX, 1) + ", " + String::num(srelY, 1) + "), sent to the game " + String::num_int64(sentX) +
		", " + String::num_int64(sentY) + (rawMouse ? String(" (raw input, ") + String::num_int64(nRaw) + " raw events, taken back " + String::num_int64(rawRetaken) + "x)" : String(" (Godot's motion events)")) + "; button events " + String::num_int64(nButton) + ", buttons now " + String::num_int64(buttons);
	nMotion = nButton = nRaw = 0;
	relX = relY = srelX = srelY = 0;
	sentX = sentY = 0;
	return s;
}

String AxisGame::get_audio_status() {
	String s = String("sounds playing ") + String::num_int64(mixer.playing_count()) + ", peak " + String::num(mixer.peak, 3);
	mixer.peak = 0;
	if (musicStream.is_valid())
		s += String(", music ") + (music->is_playing() ? "playing " : "stopped ") + String::num(music->get_playback_position(), 1) + " / " + String::num(musicStream->get_length(), 1) + " s";
	else
		s += ", no music";
	return s;
}

void AxisGame::feed_audio() {
	if (!playback.is_valid()) return;
	const int n = playback->get_frames_available();
	if (n <= 0) return;
	std::vector<float> buf((size_t)n * 2);
	mixer.mix(buf.data(), n);
	PackedVector2Array frames;
	frames.resize(n);
	Vector2 *w = frames.ptrw();
	for (int i = 0; i < n; i++) w[i] = Vector2(buf[2 * i], buf[2 * i + 1]);
	playback->push_buffer(frames);
}

bool AxisGame::start(const String &p_game_dir, const String &p_library, bool p_driver) {
	gameDir = p_game_dir;
	{	// the players: the sounds' mix (44.1 kHz, as the game's primary buffer) and the music
		Ref<AudioStreamGenerator> gen;
		gen.instantiate();
		gen->set_mix_rate(44100);
		gen->set_buffer_length(0.1f);
		sfx = memnew(AudioStreamPlayer);
		sfx->set_stream(gen);
		add_child(sfx);
		sfx->play();
		playback = sfx->get_stream_playback();
		music = memnew(AudioStreamPlayer);
		add_child(music);
	}
	const String lib = ProjectSettings::get_singleton()->globalize_path(p_library);
	char error[512] = "";
	if (!host_load(lib.utf8().get_data(), p_game_dir.utf8().get_data(), &api, error, sizeof error)) {
		status = String("AxisGame: ") + error;
		UtilityFunctions::printerr(status);
		return false;
	}
	// the stream's header: which call each op is
	std::vector<unsigned char> header(api.stream_header(nullptr, 0));
	api.stream_header(header.data(), (unsigned)header.size());
	std::string err;
	if (!emu.load_header(header.data(), header.size(), err)) {
		status = String("AxisGame: ") + err.c_str();
		return false;
	}
	loaded = true;   // (AxisReplay's renderer: frames come from the game, not a file)
	AxisHostConfig config = {};
	config.window = (void *)(intptr_t)DisplayServer::get_singleton()->window_get_native_handle(DisplayServer::WINDOW_HANDLE, 0);
	config.frame = &AxisGame::on_frame;
	config.user = this;
	config.input = 1;
	config.nogl = p_driver ? 0 : 1;   // (no OpenGL: the game's calls only recorded, its queries answered in software)
	config.sound = &k_sound;           // (the sound and music through Godot: no DirectSound / DirectShow)
	api.host(&config);
	if (!api.load()) { status = "AxisGame: axis_load failed (standalone.log in the game folder)"; return false; }
	if (!api.init(host_instance(), nullptr, "", 1)) {
		status = "AxisGame: the game did not start (axis_init)";
		api.exit(0);
		return false;
	}
	running = true;
	status = String("AxisGame: running from ") + p_game_dir;
	UtilityFunctions::print(status);
	hostWindow = config.window;
	// the mouse as the original has it: hidden, kept in the window, its movement read raw (not Godot's captured mode)
	Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_HIDDEN);
	rawMouse = host_raw_mouse_start() != 0;
	return true;
}

void AxisGame::release_all() {
	memset(keys, 0, sizeof keys);
	buttons = 0;
}

void AxisGame::_input(const Ref<InputEvent> &p_event) {
	if (!running) return;
	Ref<InputEventKey> k = p_event;
	if (k.is_valid()) {
		const int dik = dik_of(k->get_physical_keycode(), k->get_location());
		if (dik >= 0) keys[dik] = k->is_pressed() ? 0x80 : 0;
		if (api.text_input()) {   // (a text field: its keys and characters as Windows would send them)
			const unsigned vk = vk_of(k->get_keycode());
			if (vk) api.key(vk, k->is_pressed());
			if (k->is_pressed() && k->get_unicode() >= 32) api.ch((unsigned)k->get_unicode());
			if (k->is_pressed() && k->get_keycode() == KEY_BACKSPACE) api.ch(8);
		}
		return;
	}
	Ref<InputEventMouseMotion> m = p_event;
	if (m.is_valid()) {
		const Vector2 r = m->get_screen_relative();
		nMotion++;
		relX += m->get_relative().x; relY += m->get_relative().y;
		srelX += r.x; srelY += r.y;
		moveX += r.x;
		moveY += r.y;
		pointer = m->get_position();
		return;
	}
	Ref<InputEventMouseButton> b = p_event;
	if (b.is_valid()) {
		const MouseButton i = b->get_button_index();
		nButton++;
		if (i == MOUSE_BUTTON_WHEEL_UP && b->is_pressed()) wheel += 120;
		else if (i == MOUSE_BUTTON_WHEEL_DOWN && b->is_pressed()) wheel -= 120;
		else {
			const unsigned bit = i == MOUSE_BUTTON_LEFT ? 1 : i == MOUSE_BUTTON_RIGHT ? 2 : i == MOUSE_BUTTON_MIDDLE ? 4 : 0;
			if (b->is_pressed()) buttons |= bit; else buttons &= ~bit;

		}
	}
}

void AxisGame::_process(double p_delta) {
	(void)p_delta;
	if (!running) return;
	const bool focused = get_window() && get_window()->has_focus();
	if (!focused) release_all();
	if (focused != confined) {   // (the pointer kept in the window while it has the focus, free otherwise)
		host_confine(hostWindow, focused);
		confined = focused;
	} else if (focused && gameFrames % 60 == 0)
		host_confine(hostWindow, 1);   // (again now and then: a resize or another program may have let it go)
	int dx = (int)moveX, dy = (int)moveY;
	moveX -= dx;
	moveY -= dy;
	if (rawMouse && !host_raw_mouse_keep()) rawRetaken++;
	if (rawMouse) {   // (raw counts instead of Godot's motion events, once the reader has had any)
		int rx, ry, n;
		host_raw_mouse_take(&rx, &ry, &n);
		if (n) rawSeen = true;
		if (rawSeen) {
			dx = rx;
			dy = ry;
		}
		nRaw += n;
	}
	if (focused) { sentX += dx; sentY += dy; }
	// the pointer in the game window's pixels (the view is the window, stretched)
	const Vector2 vs = get_viewport()->get_visible_rect().size;
	const int px = lastW > 0 && vs.x > 0 ? (int)(pointer.x * lastW / vs.x) : (int)pointer.x;
	const int py = lastH > 0 && vs.y > 0 ? (int)(pointer.y * lastH / vs.y) : (int)pointer.y;
	api.input(keys, focused ? dx : 0, focused ? dy : 0, focused ? wheel : 0, buttons, px, py, focused);
	wheel = 0;
	api.frame();
	feed_audio();
	if (!api.running()) {
		running = false;
		const int code = api.exit(1);
		UtilityFunctions::print("AxisGame: the game quit (code ", code, ")");
		host_confine(hostWindow, 0);
		Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
		get_tree()->quit(code);
	}
}
