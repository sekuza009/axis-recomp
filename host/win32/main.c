/* host/win32/main.c: AxisHost.exe, the Windows host of axis.dll (PORTING.md stage 5; PORTABLE=3 in
   standalone/build.sh). It holds nothing of the game: it loads axis.dll (from its own folder, the game folder),
   starts the game and runs its frames, pumping the window's messages between them as the original's loop did.
   The Godot branch replaces this with a GDExtension calling the same functions (src/axis_api.h). */
#include <windows.h>
#define AXIS_HOST
#include "../../src/axis_api.h"

/* the command line after the program's name, as the C runtime's start-up hands it to WinMain */
static const char *arguments(void)
{
	const char *cmd = GetCommandLineA();
	if (*cmd == '"') {
		for (cmd++; *cmd && *cmd != '"'; cmd++)
			;
		if (*cmd == '"')
			cmd++;
	} else {
		while ((unsigned char)*cmd > ' ')
			cmd++;
	}
	while (*cmd && (unsigned char)*cmd <= ' ')
		cmd++;
	return cmd;
}

int WINAPI WinMain(HINSTANCE inst, HINSTANCE prev, LPSTR unused, int show)
{
	(void)prev; (void)unused;
	if (!axis_load())
		return 1;
	if (!axis_init(inst, NULL, arguments(), show))
		return axis_exit(0);
	MSG msg;
	while (axis_running()) {
		while (PeekMessageA(&msg, NULL, 0, 0, PM_NOREMOVE) == 1)
			if (GetMessageA(&msg, NULL, 0, 0)) {
				if (axis_textInput())
					TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		axis_frame();
	}
	return axis_exit(1);   /* (the game quit: its code; the host ends) */
}
