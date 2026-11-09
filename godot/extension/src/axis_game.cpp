// axis_game.cpp: see axis_game.h.
#include "axis_game.h"

#include <godot_cpp/classes/display_server.hpp>
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
}

void AxisGame::on_frame(void *user, const unsigned *words, unsigned count, int width, int height) {
	AxisGame *g = static_cast<AxisGame *>(user);
	g->emu.run_words(words, count, width, height);
	g->submit(width, height);
	g->lastW = width;
	g->lastH = height;
	g->gameFrames++;
}

bool AxisGame::start(const String &p_game_dir, const String &p_library, bool p_driver) {
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
	Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
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
		moveX += r.x;
		moveY += r.y;
		pointer = m->get_position();
		return;
	}
	Ref<InputEventMouseButton> b = p_event;
	if (b.is_valid()) {
		const MouseButton i = b->get_button_index();
		if (i == MOUSE_BUTTON_WHEEL_UP && b->is_pressed()) wheel += 120;
		else if (i == MOUSE_BUTTON_WHEEL_DOWN && b->is_pressed()) wheel -= 120;
		else {
			const unsigned bit = i == MOUSE_BUTTON_LEFT ? 1 : i == MOUSE_BUTTON_RIGHT ? 2 : i == MOUSE_BUTTON_MIDDLE ? 4 : 0;
			if (b->is_pressed()) buttons |= bit; else buttons &= ~bit;
			if (b->is_pressed() && Input::get_singleton()->get_mouse_mode() != Input::MOUSE_MODE_CAPTURED)
				Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);   // (clicked back into the game)
		}
	}
}

void AxisGame::_process(double p_delta) {
	(void)p_delta;
	if (!running) return;
	const bool focused = get_window() && get_window()->has_focus();
	if (!focused) release_all();
	const int dx = (int)moveX, dy = (int)moveY;
	moveX -= dx;
	moveY -= dy;
	// the pointer in the game window's pixels (the view is the window, stretched)
	const Vector2 vs = get_viewport()->get_visible_rect().size;
	const int px = lastW > 0 && vs.x > 0 ? (int)(pointer.x * lastW / vs.x) : (int)pointer.x;
	const int py = lastH > 0 && vs.y > 0 ? (int)(pointer.y * lastH / vs.y) : (int)pointer.y;
	api.input(keys, focused ? dx : 0, focused ? dy : 0, focused ? wheel : 0, buttons, px, py, focused);
	wheel = 0;
	api.frame();
	if (!api.running()) {
		running = false;
		const int code = api.exit(1);
		UtilityFunctions::print("AxisGame: the game quit (code ", code, ")");
		Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_VISIBLE);
		get_tree()->quit(code);
	}
}
