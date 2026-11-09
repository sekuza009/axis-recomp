/* host_win.c: the Windows calls AxisGame needs (kept apart from godot-cpp's headers, which windows.h does not mix
   with): the game folder in the environment, axis.dll loaded and its functions found. */
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include "host_win.h"

int host_load(const char *library, const char *game_dir, AxisFunctions *f, char *error, int room)
{
	SetEnvironmentVariableA("AXIS_GAME_DIR", game_dir);   /* (axis.dll's files, settings and logs: the game folder) */
	HMODULE m = LoadLibraryA(library);
	if (!m) {
		wsprintfA(error, "cannot load %s (error %lu)", library, GetLastError());
		return 0;
	}
	struct { void **at; const char *name; } k[] = {
		{ (void **)&f->host, "axis_host" }, { (void **)&f->stream_header, "axis_stream_header" }, { (void **)&f->load, "axis_load" },
		{ (void **)&f->init, "axis_init@16" }, { (void **)&f->frame, "axis_frame" }, { (void **)&f->running, "axis_running" },
		{ (void **)&f->text_input, "axis_textInput" }, { (void **)&f->input, "axis_input" }, { (void **)&f->key, "axis_key" },
		{ (void **)&f->ch, "axis_char" }, { (void **)&f->exit, "axis_exit" }, { (void **)&f->shutdown, "axis_shutdown" },
	};
	for (unsigned i = 0; i < sizeof k / sizeof k[0]; i++)
		if (!(*k[i].at = (void *)GetProcAddress(m, k[i].name))) {
			wsprintfA(error, "%s has no %s", library, k[i].name);
			return 0;
		}
	(void)room;
	return 1;
}

void *host_instance(void) { return GetModuleHandleA(NULL); }
