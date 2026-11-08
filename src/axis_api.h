/* axis_api.h: the game as a library a host drives (PORTING.md stage 4; the portable build, AXIS_PORTABLE).

   The host starts the game once, then runs frames until it stops:

       if (!axis_init(instance, NULL, commandLine, show)) return 0;   // start-up checks, window, devices, data
       while (axis_running()) {
           ...the host's own message pump: Windows messages to the game's window (TranslateMessage only while
              axis_textInput() - a text field is open)...
           axis_frame();                                               // one frame of the game
       }

   axis_shutdown() asks the game to close (its window's own close path, as the window's close button: the game
   then ends the process itself - handing the exit back to the host is stage 5). The game still creates and owns its
   window (app_init); a later stage gives the host the window and the GL context. */
#ifndef AXIS_API_H
#define AXIS_API_H

/* the start-up (the original WinMain's, src/app/win32.c game_WinMain, up to its loop): 1, or 0 when the game
   would not start (the reason shown in a message box) */
unsigned __attribute__((stdcall)) axis_init(void *instance, void *previous, const char *commandLine, int show);
/* one frame: the text typed into an open text field read, then the game's frame (app_frame); 1 while it runs on */
unsigned axis_frame(void);
/* 1 until the game has stopped */
int axis_running(void);
/* 1 while a text field is open (the host translates key messages into characters then) */
int axis_textInput(void);
/* the game asked to close */
void axis_shutdown(void);

#endif
