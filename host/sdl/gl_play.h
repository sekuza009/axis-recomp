/* gl_play.h: the game's drawing - each frame's recorded OpenGL calls (standalone/glrec64.c's stream) - played on a real
   OpenGL context (a compatibility / legacy one: the game's own fixed-function GL 1.x calls, one by one, as the original
   made them). gl_play.c. */
#ifndef GL_PLAY_H
#define GL_PLAY_H
#ifdef __cplusplus
extern "C" {
#endif

/* the GL functions found (getProc: SDL_GL_GetProcAddress), the system's GLU ones when it has GLU (getGlu: NULL or a
   lookup in glu32.dll / libGLU / OpenGL.framework; else gl_play.c's own), and the stream's header read
   (axis_stream_header: its plain calls' names, in op order). 0 and the reason in error when something is missing */
int gl_play_init(void *(*getProc)(const char *name), void *(*getGlu)(const char *name), const unsigned char *header,
                 unsigned headerBytes, char *error, int room);
/* one frame: the game's size (width x height) shown in the drawable (drawW x drawH) - the same size 1:1 (DESKTOP), else
   scaled to fit with its shape kept and black around it */
void gl_play_frame(const unsigned *words, unsigned count, int width, int height, int drawW, int drawH);

#ifdef __cplusplus
}
#endif
#endif
