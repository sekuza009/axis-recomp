// host_win.h: axis.dll's API as function pointers (src/axis_api.h), loaded by host_win.c.
#pragma once
#ifdef __cplusplus
extern "C" {
#endif

typedef struct {   /* (as src/axis_api.h's) */
	void *(*create)(void *user, const void *waveFormat, unsigned bytes);
	void *(*duplicate)(void *user, void *buffer);
	void (*write)(void *user, void *buffer, const void *data, unsigned bytes);
	void (*play)(void *user, void *buffer, int loop);
	void (*volume)(void *user, void *buffer, int hundredthsOfDb);
	void (*pan)(void *user, void *buffer, int pan);
	void (*release)(void *user, void *buffer);
	int (*music_open)(void *user, const char *file);
	void (*music_run)(void *user, int run);
	double (*music_time)(void *user);
	double (*music_length)(void *user);
	void (*music_seek)(void *user, double seconds);
	void (*music_close)(void *user);
} AxisSound;

typedef struct {
	void *window;
	void (*frame)(void *user, const unsigned *words, unsigned count, int width, int height);
	void *user;
	int input;
	int nogl;
	const AxisSound *sound;
	int (*message)(void *user, const char *title, const char *text);
	int (*launch)(void *user, const char *program, const char *arguments);
	int screen_w, screen_h;
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
int host_raw_mouse_start(void);                          /* the mouse's raw movement (as DirectInput reads it) */
void host_raw_mouse_take(int *dx, int *dy, int *events);
void host_confine(void *window, int on);
int host_key_down(int vk);                                  /* a key held now (GetAsyncKeyState) */
void host_cursor_delta(void *window, int *dx, int *dy);   /* the cursor's movement, then re-centred (as the original's DirectInput) */
int host_raw_mouse_keep(void);                            /* the raw mouse taken back if Godot re-registered it */                  /* the pointer kept in the window (ClipCursor) */

#ifdef __cplusplus
}
#endif
