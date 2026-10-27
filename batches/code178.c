/* batch 177 (lifted/grp127.c): app_onClose / app_shutdown (leaving the game: the room / arena left, DirectPlay and
   the music shut down) and menuState100_intro (the intro: logo fades, the menu music, then the main menu), with
   their callees stubbed (tools/gentests.py); chat_editSubclass and sound_play3D by hand */
#include "lifted/grp127.c"
LIFT_PLAIN(app_onClose, 434e70)
LIFT_PLAIN(app_shutdown, 4062b0)
LIFT_PLAIN(menuState100_intro, 41f540)
/* 0x440840 chat_editSubclass(hwnd, msg, wparam, lparam) (stdcall, ret 0x10): the chat edit's window proc: Enter
   sends the line, Esc / Tab / arrows handled, the room's timers send their requests, all else to the original
   proc (0x9dd868, CallWindowProcA) */
static LONG WINAPI chat_editSubclass(DWORD w, DWORD m, DWORD wp, DWORD lp)
{
	DWORD v[4] = { w, m, wp, lp };
	return (LONG)run_lifted(lift_440840, 0, 4, v);
}
/* 0x456ed0 sound_play3D(sound, pos, listener, volume, range): with sound on, the sound's pan from the source's
   direction against the listener's ear vector 0xa0e7d8 and its volume from the distance, then played */
LIFT_PLAIN8(sound_play3D, 456ed0)
