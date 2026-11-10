// glplay_check.cpp: gl_play.c checked against the original - a recorded session (standalone/glrec.c's AXIS_GLREC_DUMP
// file: the header, then per frame its width, height, word count and words) played on a real OpenGL context with
// gl_play, frame by frame, and the frames the original's own images were saved of (AXIS_GLREC_DUMP_SHOTS: glrec_<n>_frame
// <N>.ppm, read from its back buffer) compared pixel by pixel with the replay's. Drawn, as the game draws, into a window's
// back buffer of the frame's size - borderless at y = -1, as the game's window (a framebuffer object lays samples a hair
// differently). Usage: glplay_check <file.glrec> <frame>=<image.ppm> ...
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>
#include "gl_play.h"

static void *gl_proc(const char *name) { return (void *)SDL_GL_GetProcAddress(name); }
static SDL_SharedObject *g_glu;
static void *glu_proc(const char *name) { return g_glu ? (void *)SDL_LoadFunction(g_glu, name) : nullptr; }

static bool read_ppm(const char *path, int &w, int &h, std::vector<unsigned char> &rgb) {
	FILE *f = fopen(path, "rb");
	if (!f) return false;
	int maxv = 0;
	if (fscanf(f, "P6 %d %d %d", &w, &h, &maxv) != 3) { fclose(f); return false; }
	fgetc(f);
	rgb.resize((size_t)w * h * 3);
	const bool ok = fread(rgb.data(), 1, rgb.size(), f) == rgb.size();
	fclose(f);
	return ok;
}

int main(int argc, char **argv) {
	if (argc < 3) {
		fprintf(stderr, "usage: glplay_check <file.glrec> <frame>=<image.ppm> ...\n");
		return 2;
	}
	std::map<unsigned, std::string> shots;
	for (int i = 2; i < argc; i++) {
		const char *eq = strchr(argv[i], '=');
		if (eq) shots[(unsigned)atoi(argv[i])] = eq + 1;
	}
	FILE *f = fopen(argv[1], "rb");
	if (!f) { fprintf(stderr, "cannot open %s\n", argv[1]); return 2; }
	std::vector<unsigned char> header(12);
	if (fread(header.data(), 1, 12, f) != 12) return 2;
	unsigned n;
	memcpy(&n, header.data() + 8, 4);
	for (unsigned i = 0; i < n; i++) {   // (the plain calls' table: words, name length, name)
		unsigned wl[2];
		if (fread(wl, 4, 2, f) != 2) return 2;
		const size_t at = header.size();
		header.resize(at + 8 + wl[1]);
		memcpy(header.data() + at, wl, 8);
		if (fread(header.data() + at + 8, 1, wl[1], f) != wl[1]) return 2;
	}
	unsigned fw, fh, cnt;   // (the first frame's size: the window's)
	long first = ftell(f);
	if (fread(&fw, 4, 1, f) != 1 || fread(&fh, 4, 1, f) != 1) return 2;
	fseek(f, first, SEEK_SET);
	SDL_Init(SDL_INIT_VIDEO);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_Window *win = SDL_CreateWindow("glplay_check", (int)fw, (int)fh, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
	SDL_SetWindowPosition(win, 0, -1);
	SDL_GLContext gl = SDL_GL_CreateContext(win);
	SDL_GL_SetSwapInterval(0);
#if defined(_WIN32)
	if (!getenv("GLPLAY_NOGLU")) g_glu = SDL_LoadObject("glu32.dll");   // (GLPLAY_NOGLU: gl_play.c's own GLU)
#endif
	char error[256] = "";
	if (!gl || !gl_play_init(gl_proc, glu_proc, header.data(), (unsigned)header.size(), error, sizeof error)) {
		fprintf(stderr, "gl_play_init: %s %s\n", error, SDL_GetError());
		return 2;
	}
	auto readPixels = (void (*)(int, int, int, int, unsigned, unsigned, void *))SDL_GL_GetProcAddress("glReadPixels");
	auto readBuffer = (void (*)(unsigned))SDL_GL_GetProcAddress("glReadBuffer");
	std::vector<unsigned> words;
	unsigned frame = 0;
	int fails = 0;
	while (fread(&fw, 4, 1, f) == 1 && fread(&fh, 4, 1, f) == 1 && fread(&cnt, 4, 1, f) == 1) {
		words.resize(cnt);
		if (fread(words.data(), 4, cnt, f) != cnt) break;
		frame++;
		gl_play_frame(words.data(), cnt, (int)fw, (int)fh, (int)fw, (int)fh);
		auto s = shots.find(frame);
		if (s != shots.end()) {
			int w, h;
			std::vector<unsigned char> want, got((size_t)fw * fh * 4);
			readBuffer(0x0405);   // GL_BACK
			readPixels(0, 0, (int)fw, (int)fh, 0x1908, 0x1401, got.data());
			if (!read_ppm(s->second.c_str(), w, h, want) || w != (int)fw || h != (int)fh) {
				printf("frame %u: cannot read %s (or another size)\n", frame, s->second.c_str());
				fails++;
			} else {
				size_t same = 0, close = 0, total = (size_t)w * h;
				int worst = 0;
				for (int y = 0; y < h; y++)
					for (int x = 0; x < w; x++) {
						const unsigned char *a = &want[((size_t)y * w + x) * 3], *b = &got[((size_t)(h - 1 - y) * w + x) * 4];
						int d = 0;
						for (int c = 0; c < 3; c++) d = abs(a[c] - b[c]) > d ? abs(a[c] - b[c]) : d;
						if (!d) same++;
						if (d <= 8) close++;
						if (d > worst) worst = d;
					}
				printf("frame %u: %.3f%% of the pixels identical, %.3f%% within 8 levels, largest difference %d\n", frame,
				       100.0 * same / total, 100.0 * close / total, worst);
				if (getenv("GLPLAY_SAVE")) {   // (the replay's image beside the original's: <image>.replay.ppm)
					FILE *o = fopen((s->second + ".replay.ppm").c_str(), "wb");
					if (o) {
						fprintf(o, "P6\n%d %d\n255\n", w, h);
						for (int y = h - 1; y >= 0; y--)
							for (int x = 0; x < w; x++) fwrite(&got[((size_t)y * w + x) * 4], 1, 3, o);
						fclose(o);
					}
				}
			}
		}
		SDL_GL_SwapWindow(win);
		SDL_PumpEvents();
	}
	printf("%u frames played\n", frame);
	SDL_Quit();
	return fails;
}
