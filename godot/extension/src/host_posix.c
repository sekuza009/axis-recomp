/* host_posix.c: host_win.h's calls on Linux / macOS - the game folder in the environment, libaxis64.so loaded with
   dlopen and its functions found. The mouse needs nothing here: AxisGame uses Godot's captured mode there (its motion
   events are the mouse's relative movement), so the Windows raw-input reader, the cursor re-centring and the confining
   are empty; Godot's key events are trusted as they come. */
#ifndef _WIN32
#define _POSIX_C_SOURCE 200809L
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

#include "host_win.h"

int host_load(const char *library, const char *game_dir, AxisFunctions *f, char *error, int room)
{
	setenv("AXIS_GAME_DIR", game_dir, 1);   /* (the library's files, settings and logs: the game folder) */
	/* (kept mapped to the process's end: its exit handlers run after Godot has let go of it - unmapped, quitting
	   crashed in the exit handlers on Linux) */
	void *m = dlopen(library, RTLD_NOW | RTLD_LOCAL | RTLD_NODELETE);
	if (!m) {
		snprintf(error, (size_t)room, "cannot load %s (%s)", library, dlerror());
		return 0;
	}
	struct { void **at; const char *name; } k[] = {
		{ (void **)&f->host, "axis_host" }, { (void **)&f->stream_header, "axis_stream_header" }, { (void **)&f->load, "axis_load" },
		{ (void **)&f->init, "axis_init" }, { (void **)&f->frame, "axis_frame" }, { (void **)&f->running, "axis_running" },
		{ (void **)&f->text_input, "axis_textInput" }, { (void **)&f->input, "axis_input" }, { (void **)&f->key, "axis_key" },
		{ (void **)&f->ch, "axis_char" }, { (void **)&f->exit, "axis_exit" }, { (void **)&f->shutdown, "axis_shutdown" },
	};
	for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++)
		if (!(*k[i].at = dlsym(m, k[i].name))) {
			snprintf(error, (size_t)room, "%s has no %s", library, k[i].name);
			return 0;
		}
	return 1;
}

void *host_instance(void) { return NULL; }
int host_raw_mouse_start(void) { return 0; }
int host_raw_mouse_keep(void) { return 1; }
void host_raw_mouse_take(int *dx, int *dy, int *events) { *dx = *dy = *events = 0; }
void host_confine(void *window, int on) { (void)window; (void)on; }
void host_cursor_delta(void *window, int *dx, int *dy) { (void)window; (void)dx; (void)dy; }   /* (Godot's movement kept) */
int host_key_down(int vk) { (void)vk; return 1; }
#endif
