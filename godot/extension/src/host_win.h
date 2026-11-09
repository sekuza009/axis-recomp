// host_win.h: axis.dll's API as function pointers (src/axis_api.h), loaded by host_win.c.
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	void *window;
	void (*frame)(void *user, const unsigned *words, unsigned count, int width, int height);
	void *user;
	int input;
	int nogl;
} AxisHostConfig;   /* (as src/axis_api.h's) */

typedef struct {
	void (*host)(const AxisHostConfig *config);
	unsigned (*stream_header)(unsigned char *out, unsigned room);
	int (*load)(void);
	unsigned (__attribute__((stdcall)) *init)(void *instance, void *previous, const char *commandLine, int show);
	unsigned (*frame)(void);
	int (*running)(void);
	int (*text_input)(void);
	void (*input)(const unsigned char keys[256], int dx, int dy, int wheel, unsigned buttons, int x, int y, int focused);
	void (*key)(unsigned vk, int down);
	void (*ch)(unsigned ch);
	int (*exit)(int code);
	void (*shutdown)(void);
} AxisFunctions;

int host_load(const char *library, const char *game_dir, AxisFunctions *f, char *error, int room);
void *host_instance(void);

#ifdef __cplusplus
}
#endif
