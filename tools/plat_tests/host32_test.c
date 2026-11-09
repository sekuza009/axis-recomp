/* host32_test.c: the 32-bit build (axis.dll, PORTABLE=3) run headless as host64_test.c runs the 64-bit one - to compare their
   streams. Built and run on Windows: tools/plat_tests/run32.sh. (host64_test.c:) the 64-bit build run headless (PORTING.md, stage 6) - a host with no window, no sound and no input: the
   game loaded, started and run for some frames; each frame's drawing (its stream words) counted, a few frames written
   out as a stream file (AXGLREC1: the header, then per frame width, height, word count and the words) to compare with
   the 32-bit build's. Usage: axis64_test <game folder> [frames] [stream file]. Run in WSL by tools/plat_tests/run64.sh. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define setenv(n, v, o) SetEnvironmentVariableA(n, v)
#define AXIS_HOST 1
#include "../../src/axis_api.h"

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
	c.screen_w = 1920;
	c.screen_h = 1080;
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
