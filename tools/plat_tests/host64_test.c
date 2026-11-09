/* host64_test.c: the 64-bit build run headless (PORTING.md, stage 6) - a host with no window, no sound and no input: the
   game loaded, started and run for some frames; each frame's drawing (its stream words) counted, a few frames written
   out as a stream file (AXGLREC1: the header, then per frame width, height, word count and the words) to compare with
   the 32-bit build's. Usage: axis64_test <game folder> [frames] [stream file]. Run in WSL by tools/plat_tests/run64.sh. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#define setenv(n, v, o) _putenv_s(n, v)   /* (the C runtime's environment, which the library's getenv reads) */
#endif
#include "../../src/axis_api.h"

#ifdef AXIS_TEST_DLOPEN   /* (the library as a host loads it: libaxis64.so through dlopen - $AXIS_TEST_LIB) */
#include <dlfcn.h>
#define FN(name) static __typeof__(name) *p_##name;
FN(axis_host) FN(axis_stream_header) FN(axis_load) FN(axis_init) FN(axis_running) FN(axis_input) FN(axis_frame)
FN(axis_exit)
static int load_lib(void)
{
	const char *path = getenv("AXIS_TEST_LIB") ? getenv("AXIS_TEST_LIB") : "./libaxis64.so";
	void *lib = dlopen(path, RTLD_NOW | RTLD_LOCAL);
	if (!lib) {
		printf("dlopen(%s): %s\n", path, dlerror());
		return 0;
	}
#define GET(name) if (!(p_##name = (__typeof__(name) *)dlsym(lib, #name))) { printf("%s has no %s\n", path, #name); return 0; }
	GET(axis_host) GET(axis_stream_header) GET(axis_load) GET(axis_init) GET(axis_running) GET(axis_input)
	GET(axis_frame) GET(axis_exit)
	printf("loaded %s\n", path);
	return 1;
}
#define axis_host p_axis_host
#define axis_stream_header p_axis_stream_header
#define axis_load p_axis_load
#define axis_init p_axis_init
#define axis_running p_axis_running
#define axis_input p_axis_input
#define axis_frame p_axis_frame
#define axis_exit p_axis_exit
#endif


static unsigned g_frames, g_words, g_maxWords;
static FILE *g_dump;
static unsigned g_dumpFrames = 600;
static void on_frame(void *user, const unsigned *words, unsigned count, int width, int height)
{
	(void)user;
	g_frames++;
	g_words += count;
	if (count > g_maxWords)
		g_maxWords = count;
	if (g_dump && g_frames <= g_dumpFrames) {
		unsigned head[3] = { (unsigned)width, (unsigned)height, count };
		fwrite(head, 4, 3, g_dump);
		fwrite(words, 4, count, g_dump);
	}
	if (g_frames % 60 == 1)
		printf("frame %u: %ux%u, %u words\n", g_frames, width, height, count);
}
static int on_message(void *user, const char *title, const char *text)
{
	(void)user;
	printf("message box: [%s] %s\n", title, text);
	return 1;
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		fprintf(stderr, "usage: %s <game folder> [frames] [stream file]\n", argv[0]);
		return 2;
	}
#ifdef AXIS_TEST_DLOPEN
	if (!load_lib())
		return 1;
#endif
	setenv("AXIS_GAME_DIR", argv[1], 1);
	int frames = argc > 2 ? atoi(argv[2]) : 300;
	if (argc > 3 && (g_dump = fopen(argv[3], "wb"))) {
		unsigned n = axis_stream_header(NULL, 0);
		unsigned char *h = malloc(n);
		axis_stream_header(h, n);
		fwrite(h, 1, n, g_dump);
		free(h);
	}
	AxisHostConfig c;
	memset(&c, 0, sizeof c);
	c.frame = on_frame;
	c.input = 1;
	c.nogl = 1;
	c.message = on_message;
	c.screen_w = getenv("AXIS_TEST_W") ? atoi(getenv("AXIS_TEST_W")) : 3840;
	c.screen_h = getenv("AXIS_TEST_H") ? atoi(getenv("AXIS_TEST_H")) : 2160;
	axis_host(&c);
	if (!axis_load()) {
		printf("axis_load failed (see standalone64.log)\n");
		return 1;
	}
	unsigned r = axis_init(NULL, NULL, "", 1);
	printf("axis_init: %u\n", r);
	if (!r)
		return 1;
	unsigned char keys[256] = { 0 };
	int i = 0;
	for (; i < frames && axis_running(); i++) {
		axis_input(keys, 0, 0, 0, 0, 320, 240, 1);
		axis_frame();
	}
	printf("%d frames run, %u drawn, %u words (largest frame %u)\n", i, g_frames, g_words, g_maxWords);
	if (g_dump)
		fclose(g_dump);
	return axis_exit(0) == 0 ? 0 : 3;
}
