/* axis_api.h: the game as a library a host drives (PORTING.md stage 4; the portable build, AXIS_PORTABLE).

   The host loads it, starts the game once, then runs frames until it stops:

       if (!axis_load()) return 0;                                     // data, imports, runtime, network layer
       if (!axis_init(instance, NULL, commandLine, show)) return 0;   // start-up checks, window, devices, data
       while (axis_running()) {
           ...the host's own message pump: Windows messages to the game's window (TranslateMessage only while
              axis_textInput() - a text field is open)...
           axis_frame();                                               // one frame of the game
       }
       return axis_exit(1);

   axis_shutdown() asks the game to close (its window's own close path, as the window's close button); when it has,
   axis_running() is 0 and axis_exit() gives the host the game's exit code. The game still creates and owns its
   window (app_init); a later stage gives the host the window and the GL context. */
#ifndef AXIS_API_H
#define AXIS_API_H

/* (PORTABLE=3: the game is axis.dll, AXIS_DLL, and the host AxisHost.exe, AXIS_HOST - host/win32/main.c) */
#if defined(AXIS_DLL)
#define AXIS_API __declspec(dllexport)
#elif defined(AXIS_HOST)
#define AXIS_API __declspec(dllimport)
#else
#define AXIS_API
#endif

/* a host's configuration (before axis_load; optional - without it the game is a Windows program as before) */
typedef struct {
	void *window;   /* the host's window (an HWND): sound plays while it has the focus; 0: the game's own */
	/* each frame's drawing: the stream's words (standalone/glrec.c's format - axis_stream_header() gives the file
	   header that names its calls) and the frame's size; valid during the call. 0: none */
	void (*frame)(void *user, const unsigned *words, unsigned count, int width, int height);
	void *user;
	int input;      /* 1: the host supplies keyboard and mouse (axis_input / axis_key / axis_char) and the game's own
	                   window stays hidden */
} AxisHostConfig;
AXIS_API void axis_host(const AxisHostConfig *config);
/* the stream's header (an AXGLREC1 file's start: its calls' table) into out; its size (out 0 or room too small: only
   the size) */
AXIS_API unsigned axis_stream_header(unsigned char *out, unsigned room);
/* the input for the next frame (with config.input): the keyboard (256 bytes by DirectInput key code - the PC scan
   code, extended keys + 0x80 - bit 7 held), the mouse's movement and wheel since the last call (added up), its
   buttons (bit 0 left, 1 right, 2 middle), the pointer in the game's window (pixels) and whether the host's window
   has the focus */
AXIS_API void axis_input(const unsigned char keys[256], int dx, int dy, int wheel, unsigned buttons, int x, int y, int focused);
/* a key (a Windows virtual-key code) down / up and a typed character, for an open text field (axis_textInput()) */
AXIS_API void axis_key(unsigned vk, int down);
AXIS_API void axis_char(unsigned ch);

/* the library made ready (once, before axis_init): the game's data placed, its imports and C runtime set up, the
   network layer started, the static constructors run. 1, or 0 (the reason in standalone.log / a message box) */
AXIS_API int axis_load(void);
/* the end, after the loop: when the game quit itself (its window closed), its exit code, returned to the host;
   otherwise (axis_init failed, or the host stopped early) the game's exit list is run with code and the process
   ends, as the original's did */
AXIS_API int axis_exit(int code);

/* the start-up (the original WinMain's, src/app/win32.c game_WinMain, up to its loop): 1, or 0 when the game
   would not start (the reason shown in a message box) */
AXIS_API unsigned __attribute__((stdcall)) axis_init(void *instance, void *previous, const char *commandLine, int show);
/* one frame: the text typed into an open text field read, then the game's frame (app_frame); 1 while it runs on */
AXIS_API unsigned axis_frame(void);
/* 1 until the game has stopped */
AXIS_API int axis_running(void);
/* 1 while a text field is open (the host translates key messages into characters then) */
AXIS_API int axis_textInput(void);
/* the game asked to close */
AXIS_API void axis_shutdown(void);

#endif
