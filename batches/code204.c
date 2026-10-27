/* batch 203 (lifted/grp162.c): WinMain */
#include "lifted/grp162.c"
/* 0x43f9d0 WinMain(inst, prev, cmd, show) (stdcall): the command line (0x43f160); a running copy's window (by
   class and title) is told to quit and given half a second; the start time (GetSystemTime into 0x9dd878,
   timeGetTime into 0x9dd8e8) and a two-second wait; another copy still running ends it with a message box, as does
   a failed 0x401000; the language (Korean 0x412 / 0x812: 1, else 2, into 0x9dae74, its message string 0x9dd8c8);
   0x43f300; unless 0x76d410 the five checks (0x41e260, 0x43f770, 0x41e6d0 .. 0x41e670) each end it with their
   message (0x41edf0); the running copy told again; app_init(inst, show) (failure: a message box); the screen saver
   off; then the message loop (PeekMessageA / GetMessageA, TranslateMessage while 0x68039c, DispatchMessageA) with
   the frame (0x43f980) and the fade step (FUN_004202d0) until 0x4b2790 is cleared. Returns 1, or 0 on the exits.
   Named game_WinMain (WinMain is the SDK's) */
static DWORD WINAPI game_WinMain(DWORD inst, DWORD prev, DWORD cmd, DWORD show)
{
	DWORD v[4] = { inst, prev, cmd, show };
	return run_lifted(lift_43f9d0, 0, 4, v);
}
