// main.cpp: AxisSDL - the game (the portable build's 64-bit library, src/axis_api.h) as a program of its own on Windows,
// Linux and macOS: SDL3 for the window, keyboard, mouse and sound, the game's drawing played on a real OpenGL context
// (gl_play.c), its sounds mixed as DirectSound mixes them (axis_audio.cpp) and its music decoded with dr_mp3. Meant to be
// the original game, with the fixes, on every system - the same library (and network) as every other build.
// Command line: [--game-dir <the Axis folder>] [--windowed] [--novsync]. The game folder is otherwise the program's own
// when it holds initdata, else the one above it. Saves and settings: the game folder on Windows, the user folder
// elsewhere (src/plat/posix/files.c).
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>   // (Windows: the program's WinMain, then main)
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "../../src/axis_api.h"
#include "axis_audio.h"
#include "gl_play.h"
#include "launcher.h"
#define DR_MP3_IMPLEMENTATION
#include "../../third_party/dr_libs/dr_mp3.h"

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall SetEnvironmentVariableA(const char *name, const char *value);
#endif

static const int RATE = 44100;
static SDL_Window *g_window;
static AxisMixer g_mixer(RATE);
static std::string g_dir;   // the game folder, with a trailing '/'
static bool g_restart;
static std::vector<std::string> g_args;

// ---- the music: one MP3 at a time, streamed (the game opens, runs, asks the time, seeks back to replay, closes)
static struct {
	drmp3 mp3;
	bool open = false, playing = false;
	double length = 0, pos = 0;   // seconds; pos: the frames read so far, in seconds
	std::vector<float> buf;       // decoded, not yet mixed (the file's rate and channels)
	size_t bufAt = 0;
	double frac = 0;              // (resampling to RATE: the place between two decoded frames)
} M;
static void music_close() {
	if (M.open) drmp3_uninit(&M.mp3);
	M.open = M.playing = false;
	M.buf.clear();
	M.bufAt = 0;
}
static int m_open(void *, const char *file) {
	music_close();
	std::string p = g_dir + file;
	for (char &c : p) if (c == '\\') c = '/';
	if (!drmp3_init_file(&M.mp3, p.c_str(), nullptr)) {
		SDL_Log("music: cannot open %s", p.c_str());
		return 1;
	}
	M.open = true;
	drmp3_uint64 frames = drmp3_get_pcm_frame_count(&M.mp3);
	M.length = M.mp3.sampleRate ? (double)frames / M.mp3.sampleRate : 0;
	drmp3_seek_to_pcm_frame(&M.mp3, 0);
	M.pos = 0;
	return 0;
}
static void m_run(void *, int run) { if (M.open) M.playing = run != 0; }
static double m_time(void *) { return !M.playing ? M.length : M.pos; }   // (finished or stopped: at its end, as the Godot host)
static double m_length(void *) { return M.length; }
static void m_seek(void *, double s) {
	if (!M.open) return;
	drmp3_seek_to_pcm_frame(&M.mp3, (drmp3_uint64)(s * M.mp3.sampleRate));
	M.buf.clear();
	M.bufAt = 0;
	M.pos = s;
	M.playing = true;   // (the game seeks to replay from the start)
}
static void m_close(void *) { music_close(); }
// the music added to out (stereo floats at RATE)
static void music_mix(float *out, int frames) {
	if (!M.open || !M.playing) return;
	const int ch = (int)M.mp3.channels;
	const double step = (double)M.mp3.sampleRate / RATE;
	for (int i = 0; i < frames; i++) {
		while (M.bufAt + 2 * ch > M.buf.size()) {   // (two decoded frames needed: this one and the next)
			std::vector<float> more(4096 * ch);
			drmp3_uint64 got = drmp3_read_pcm_frames_f32(&M.mp3, 4096, more.data());
			if (!got) {
				M.playing = false;   // (the end: the game sees its time at the length and seeks back)
				M.pos = M.length;
				return;
			}
			M.buf.erase(M.buf.begin(), M.buf.begin() + (long)M.bufAt);
			M.bufAt = 0;
			M.buf.insert(M.buf.end(), more.begin(), more.begin() + (long)(got * ch));
		}
		const float *a = &M.buf[M.bufAt], *b = a + ch;
		const float t = (float)M.frac;
		out[2 * i] += a[0] + (b[0] - a[0]) * t;
		out[2 * i + 1] += (ch > 1 ? a[1] + (b[1] - a[1]) * t : a[0] + (b[0] - a[0]) * t);
		M.frac += step;
		while (M.frac >= 1) {
			M.frac -= 1;
			M.bufAt += ch;
			M.pos += 1.0 / M.mp3.sampleRate;
		}
	}
}

// ---- the game's sounds: its buffers in the mixer
static void *s_create(void *, const void *f, unsigned b) { return g_mixer.create(f, b); }
static void *s_duplicate(void *, void *b) { return g_mixer.duplicate((AxisMixer::Voice *)b); }
static void s_write(void *, void *b, const void *d, unsigned n) { g_mixer.write((AxisMixer::Voice *)b, d, n); }
static void s_play(void *, void *b, int loop) { g_mixer.play((AxisMixer::Voice *)b, loop != 0); }
static void s_volume(void *, void *b, int v) { g_mixer.set_volume((AxisMixer::Voice *)b, v); }
static void s_pan(void *, void *b, int p) { g_mixer.set_pan((AxisMixer::Voice *)b, p); }
static void s_release(void *, void *b) { g_mixer.release((AxisMixer::Voice *)b); }
static const AxisSound k_sound = { s_create, s_duplicate, s_write, s_play, s_volume, s_pan, s_release,
	m_open, m_run, m_time, m_length, m_seek, m_close };

// ---- the drawing: each frame's stream played, then shown
static unsigned g_frames;
static void on_frame(void *, const unsigned *words, unsigned count, int width, int height) {
	g_frames++;
	if (getenv("AXISSDL_FRAMELOG") && g_frames % 60 == 1)
		SDL_Log("frame %u: %dx%d, %u words", g_frames, width, height, count);
	int w = 0, h = 0;
	SDL_GetWindowSizeInPixels(g_window, &w, &h);
	gl_play_frame(words, count, width, height, w, h);
	SDL_GL_SwapWindow(g_window);
}

// ---- the game's message boxes and the programs it starts
static int on_message(void *, const char *title, const char *text) {
	SDL_SetWindowRelativeMouseMode(g_window, false);
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title, text, g_window);
	return 1;   // IDOK
}
// "AxisGL.exe": the game itself again, after a graphics change - this program restarts once the game has ended; the
// original's patcher and server tool (Windows) run when they are there
static int on_launch(void *, const char *program, const char *arguments) {
	std::string p = program;
	for (char &c : p) if (c == '\\') c = '/';
	std::string name = p.substr(p.find_last_of('/') == std::string::npos ? 0 : p.find_last_of('/') + 1);
	for (char &c : name) c = (char)tolower((unsigned char)c);
	SDL_Log("the game asks to start %s %s", program, arguments ? arguments : "");
	if (name == "axisgl.exe") {
		g_restart = true;
		return 1;
	}
#ifdef _WIN32
	std::string path = (p.size() > 1 && p[1] == ':') ? p : g_dir + p;
	if (!SDL_GetPathInfo(path.c_str(), nullptr)) return 0;
	std::vector<const char *> argv = { path.c_str() };
	std::string a = arguments ? arguments : "";
	if (!a.empty()) argv.push_back(a.c_str());
	argv.push_back(nullptr);
	SDL_Process *pr = SDL_CreateProcess(argv.data(), false);
	if (pr) SDL_DestroyProcess(pr);
	return pr != nullptr;
#else
	return 0;
#endif
}

// ---- input: SDL's scancodes as DirectInput's key codes (the PC's scan codes; extended keys + 0x80)
static int dik_of(SDL_Scancode s) {
	if (s >= SDL_SCANCODE_A && s <= SDL_SCANCODE_Z) {
		static const unsigned char letters[26] = { 0x1e, 0x30, 0x2e, 0x20, 0x12, 0x21, 0x22, 0x23, 0x17, 0x24, 0x25, 0x26, 0x32,
			0x31, 0x18, 0x19, 0x10, 0x13, 0x1f, 0x14, 0x16, 0x2f, 0x11, 0x2d, 0x15, 0x2c };
		return letters[s - SDL_SCANCODE_A];
	}
	if (s >= SDL_SCANCODE_1 && s <= SDL_SCANCODE_9) return 0x02 + (s - SDL_SCANCODE_1);
	if (s >= SDL_SCANCODE_F1 && s <= SDL_SCANCODE_F10) return 0x3b + (s - SDL_SCANCODE_F1);
	switch (s) {
	case SDL_SCANCODE_0: return 0x0b;
	case SDL_SCANCODE_RETURN: return 0x1c;
	case SDL_SCANCODE_ESCAPE: return 0x01;
	case SDL_SCANCODE_BACKSPACE: return 0x0e;
	case SDL_SCANCODE_TAB: return 0x0f;
	case SDL_SCANCODE_SPACE: return 0x39;
	case SDL_SCANCODE_MINUS: return 0x0c;
	case SDL_SCANCODE_EQUALS: return 0x0d;
	case SDL_SCANCODE_LEFTBRACKET: return 0x1a;
	case SDL_SCANCODE_RIGHTBRACKET: return 0x1b;
	case SDL_SCANCODE_BACKSLASH: return 0x2b;
	case SDL_SCANCODE_SEMICOLON: return 0x27;
	case SDL_SCANCODE_APOSTROPHE: return 0x28;
	case SDL_SCANCODE_GRAVE: return 0x29;
	case SDL_SCANCODE_COMMA: return 0x33;
	case SDL_SCANCODE_PERIOD: return 0x34;
	case SDL_SCANCODE_SLASH: return 0x35;
	case SDL_SCANCODE_CAPSLOCK: return 0x3a;
	case SDL_SCANCODE_F11: return 0x57;
	case SDL_SCANCODE_F12: return 0x58;
	case SDL_SCANCODE_PRINTSCREEN: return 0xb7;
	case SDL_SCANCODE_SCROLLLOCK: return 0x46;
	case SDL_SCANCODE_PAUSE: return 0xc5;
	case SDL_SCANCODE_INSERT: return 0xd2;
	case SDL_SCANCODE_HOME: return 0xc7;
	case SDL_SCANCODE_PAGEUP: return 0xc9;
	case SDL_SCANCODE_DELETE: return 0xd3;
	case SDL_SCANCODE_END: return 0xcf;
	case SDL_SCANCODE_PAGEDOWN: return 0xd1;
	case SDL_SCANCODE_RIGHT: return 0xcd;
	case SDL_SCANCODE_LEFT: return 0xcb;
	case SDL_SCANCODE_DOWN: return 0xd0;
	case SDL_SCANCODE_UP: return 0xc8;
	case SDL_SCANCODE_NUMLOCKCLEAR: return 0x45;
	case SDL_SCANCODE_KP_DIVIDE: return 0xb5;
	case SDL_SCANCODE_KP_MULTIPLY: return 0x37;
	case SDL_SCANCODE_KP_MINUS: return 0x4a;
	case SDL_SCANCODE_KP_PLUS: return 0x4e;
	case SDL_SCANCODE_KP_ENTER: return 0x9c;
	case SDL_SCANCODE_KP_1: return 0x4f;
	case SDL_SCANCODE_KP_2: return 0x50;
	case SDL_SCANCODE_KP_3: return 0x51;
	case SDL_SCANCODE_KP_4: return 0x4b;
	case SDL_SCANCODE_KP_5: return 0x4c;
	case SDL_SCANCODE_KP_6: return 0x4d;
	case SDL_SCANCODE_KP_7: return 0x47;
	case SDL_SCANCODE_KP_8: return 0x48;
	case SDL_SCANCODE_KP_9: return 0x49;
	case SDL_SCANCODE_KP_0: return 0x52;
	case SDL_SCANCODE_KP_PERIOD: return 0x53;
	case SDL_SCANCODE_NONUSBACKSLASH: return 0x56;
	case SDL_SCANCODE_APPLICATION: return 0xdd;
	case SDL_SCANCODE_LCTRL: return 0x1d;
	case SDL_SCANCODE_LSHIFT: return 0x2a;
	case SDL_SCANCODE_LALT: return 0x38;
	case SDL_SCANCODE_LGUI: return 0xdb;
	case SDL_SCANCODE_RCTRL: return 0x9d;
	case SDL_SCANCODE_RSHIFT: return 0x36;
	case SDL_SCANCODE_RALT: return 0xb8;
	case SDL_SCANCODE_RGUI: return 0xdc;
	default: return -1;
	}
}
// a key as a Windows virtual key, for an open text field (its editing keys, letters and digits)
static unsigned vk_of(SDL_Keycode k) {
	switch (k) {
	case SDLK_BACKSPACE: return 0x08;
	case SDLK_TAB: return 0x09;
	case SDLK_RETURN: case SDLK_KP_ENTER: return 0x0d;
	case SDLK_ESCAPE: return 0x1b;
	case SDLK_END: return 0x23;
	case SDLK_HOME: return 0x24;
	case SDLK_LEFT: return 0x25;
	case SDLK_UP: return 0x26;
	case SDLK_RIGHT: return 0x27;
	case SDLK_DOWN: return 0x28;
	case SDLK_DELETE: return 0x2e;
	default: break;
	}
	if (k >= 'a' && k <= 'z') return (unsigned)(k - 'a' + 'A');
	if (k >= '0' && k <= '9') return (unsigned)k;
	return 0;
}

// the game folder: --game-dir, else this program's folder when it holds initdata, else the one above it
static std::string game_folder() {
	for (size_t i = 0; i + 1 < g_args.size(); i++)
		if (g_args[i] == "--game-dir") {
			std::string d = g_args[i + 1];
			for (char &c : d) if (c == '\\') c = '/';
			if (!d.empty() && d.back() != '/') d += '/';
			return d;
		}
	std::string here = SDL_GetBasePath() ? SDL_GetBasePath() : "./";
	for (char &c : here) if (c == '\\') c = '/';
	if (!here.empty() && here.back() != '/') here += '/';
	if (SDL_GetPathInfo((here + "initdata").c_str(), nullptr)) return here;
	std::string up = here.substr(0, here.size() - 1);
	size_t cut = up.find_last_of('/');
	return cut == std::string::npos ? here : up.substr(0, cut + 1);
}
static bool has_arg(const char *a) {
	for (const std::string &s : g_args) if (s == a) return true;
	return false;
}
static void *gl_proc(const char *name) { return (void *)SDL_GL_GetProcAddress(name); }
static SDL_SharedObject *g_glu;
static void *glu_proc(const char *name) { return g_glu ? (void *)SDL_LoadFunction(g_glu, name) : nullptr; }

int main(int argc, char **argv) {
	for (int i = 1; i < argc; i++) g_args.push_back(argv[i]);
	SDL_SetHint(SDL_HINT_MOUSE_RELATIVE_SYSTEM_SCALE, "1");   // (the pointer's speed as Windows moves it: what the original's DirectInput reported)
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS)) {
		fprintf(stderr, "AxisSDL: SDL_Init: %s\n", SDL_GetError());
		return 1;
	}
	g_dir = game_folder();
	SDL_Log("the game folder: %s", g_dir.c_str());
#ifdef _WIN32
	SetEnvironmentVariableA("AXIS_GAME_DIR", g_dir.c_str());
#else
	setenv("AXIS_GAME_DIR", g_dir.c_str(), 1);
#endif
	// the launcher first (launcher.cpp, AxisPlay.exe's rewrite) - Play Game goes on to the game; --play skips it (the
	// game's own restart after a graphics change, as the original started AxisGL.exe itself)
	if (!has_arg("--play") && !launcher_run(g_dir)) {
		SDL_Quit();
		return 0;
	}
	// the window: borderless over the whole screen (the game's DESKTOP size is the screen's, 1:1), or a window
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// (not SDL's fullscreen: a borderless window one row taller than the screen, from y = -1 - as the original's fix
	// made its window, so the driver keeps it an ordinary window - instant Alt-Tab - and the game, which draws that one
	// row more, is shown 1:1)
	const bool windowed = has_arg("--windowed");
	SDL_Rect screen = { 0, 0, 1280, 720 };
	SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &screen);
	SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY | (windowed ? SDL_WINDOW_RESIZABLE : SDL_WINDOW_BORDERLESS);
	g_window = SDL_CreateWindow("Axis", windowed ? 1280 : screen.w, windowed ? 720 : screen.h + 1, flags);
	if (g_window && !windowed)
		SDL_SetWindowPosition(g_window, screen.x, screen.y - 1);
	if (!g_window) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Axis", SDL_GetError(), nullptr);
		return 1;
	}
	SDL_GLContext gl = SDL_GL_CreateContext(g_window);
	if (!gl) {
		std::string e = std::string("OpenGL: ") + SDL_GetError();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Axis", e.c_str(), g_window);
		return 1;
	}
	SDL_GL_SetSwapInterval(has_arg("--novsync") ? 0 : 1);
	SDL_Log("OpenGL: %s / %s", (const char *)((const unsigned char *(*)(unsigned))SDL_GL_GetProcAddress("glGetString"))(0x1f01),
	        (const char *)((const unsigned char *(*)(unsigned))SDL_GL_GetProcAddress("glGetString"))(0x1f02));
	// the system's GLU (Windows' glu32, as the original used; libGLU; macOS's OpenGL framework), else gl_play.c's
#if defined(_WIN32)
	g_glu = SDL_LoadObject("glu32.dll");
#elif defined(__APPLE__)
	g_glu = SDL_LoadObject("/System/Library/Frameworks/OpenGL.framework/OpenGL");
#else
	g_glu = SDL_LoadObject("libGLU.so.1");
#endif
	std::vector<unsigned char> header(axis_stream_header(nullptr, 0));
	axis_stream_header(header.data(), (unsigned)header.size());
	char error[256] = "";
	if (!gl_play_init(gl_proc, glu_proc, header.data(), (unsigned)header.size(), error, sizeof error)) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Axis", error, g_window);
		return 1;
	}
	// the sound: the mix and the music into one stream
	SDL_AudioSpec spec = { SDL_AUDIO_F32, 2, RATE };
	SDL_AudioStream *audio = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec, nullptr, nullptr);
	if (audio) SDL_ResumeAudioStreamDevice(audio);
	else SDL_Log("no sound: %s", SDL_GetError());

	int sw = 0, sh = 0;
	SDL_GetWindowSizeInPixels(g_window, &sw, &sh);
	AxisHostConfig c = {};
#ifdef _WIN32
	c.window = SDL_GetPointerProperty(SDL_GetWindowProperties(g_window), SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
#endif
	c.frame = on_frame;
	c.input = 1;
	c.nogl = 1;   // (the library records; the drawing is played here)
	c.sound = &k_sound;
	c.message = on_message;
	c.launch = on_launch;
	{   // (the screen's size for DESKTOP: the display's - the game adds its one row; windowed, the window shows it scaled)
		const SDL_DisplayMode *dm = SDL_GetDesktopDisplayMode(SDL_GetDisplayForWindow(g_window));
		if (dm) { sw = (int)lround(dm->w * dm->pixel_density); sh = (int)lround(dm->h * dm->pixel_density); }
	}
	c.screen_w = sw;
	c.screen_h = sh;
	axis_host(&c);
	if (!axis_load()) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Axis", "The game library could not start (standalone64.log).", g_window);
		return 1;
	}
	if (!axis_init(nullptr, nullptr, "", 1)) return axis_exit(0);

	unsigned char keys[256] = {};
	float dx = 0, dy = 0;
	int wheel = 0;
	unsigned buttons = 0;
	bool focused = true, texting = false;
	SDL_SetWindowRelativeMouseMode(g_window, true);
	std::vector<float> mix;
	while (axis_running()) {
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			switch (e.type) {
			case SDL_EVENT_QUIT: axis_shutdown(); break;
			case SDL_EVENT_WINDOW_FOCUS_GAINED: focused = true; SDL_SetWindowRelativeMouseMode(g_window, true); break;
			case SDL_EVENT_WINDOW_FOCUS_LOST:
				focused = false;
				memset(keys, 0, sizeof keys);
				buttons = 0;
				SDL_SetWindowRelativeMouseMode(g_window, false);
				break;
			case SDL_EVENT_KEY_DOWN: case SDL_EVENT_KEY_UP: {
				const int d = dik_of(e.key.scancode);
				if (d >= 0) keys[d] = e.key.down ? 0x80 : 0;
				if (texting) {
					const unsigned vk = vk_of(e.key.key);
					if (vk) axis_key(vk, e.key.down);
					if (e.key.down && e.key.key == SDLK_BACKSPACE) axis_char(8);
				}
				break;
			}
			case SDL_EVENT_TEXT_INPUT:
				if (texting)
					for (const unsigned char *s = (const unsigned char *)e.text.text; *s;) {   // (UTF-8 -> the characters)
						unsigned cp = *s++;
						if (cp >= 0xc0) {
							int more = cp >= 0xf0 ? 3 : cp >= 0xe0 ? 2 : 1;
							cp &= 0x3f >> more;
							while (more-- && (*s & 0xc0) == 0x80) cp = (cp << 6) | (*s++ & 0x3f);
						}
						if (cp >= 32 && cp < 256) axis_char(cp);
					}
				break;
			case SDL_EVENT_MOUSE_MOTION: dx += e.motion.xrel; dy += e.motion.yrel; break;
			case SDL_EVENT_MOUSE_WHEEL: wheel += (int)lround(e.wheel.y * 120); break;
			case SDL_EVENT_MOUSE_BUTTON_DOWN: case SDL_EVENT_MOUSE_BUTTON_UP: {
				const unsigned bit = e.button.button == SDL_BUTTON_LEFT ? 1 : e.button.button == SDL_BUTTON_RIGHT ? 2 :
				                     e.button.button == SDL_BUTTON_MIDDLE ? 4 : 0;
				if (e.button.down) buttons |= bit; else buttons &= ~bit;
				break;
			}
			default: break;
			}
		}
		const bool wantText = axis_textInput() != 0;   // (a text field open: typed characters too)
		if (wantText != texting) {
			texting = wantText;
			if (texting) SDL_StartTextInput(g_window); else SDL_StopTextInput(g_window);
		}
		const int ix = (int)dx, iy = (int)dy;
		dx -= ix;
		dy -= iy;
		axis_input(keys, focused ? ix : 0, focused ? iy : 0, focused ? wheel : 0, buttons, sw / 2, sh / 2, focused);
		wheel = 0;
		axis_frame();
		if (audio) {   // (the sound kept about 60 ms ahead)
			const int queued = SDL_GetAudioStreamQueued(audio) / (int)(2 * sizeof(float));
			const int want = RATE * 60 / 1000 - queued;
			if (want > 0) {
				mix.assign((size_t)want * 2, 0.0f);
				g_mixer.mix(mix.data(), want);
				music_mix(mix.data(), want);
				SDL_PutAudioStreamData(audio, mix.data(), want * (int)(2 * sizeof(float)));
			}
		}
	}
	const int code = axis_exit(1);
	music_close();
	if (audio) SDL_DestroyAudioStream(audio);
	SDL_GL_DestroyContext(gl);
	SDL_DestroyWindow(g_window);
	if (g_restart) {   // (a graphics change: this program again, with its arguments - straight into the game)
		std::vector<const char *> av = { argv[0] };
		if (!has_arg("--play")) av.push_back("--play");
		for (const std::string &s : g_args) av.push_back(s.c_str());
		av.push_back(nullptr);
		SDL_Process *p = SDL_CreateProcess(av.data(), false);
		if (p) SDL_DestroyProcess(p);
	}
	SDL_Quit();
	return code;
}
