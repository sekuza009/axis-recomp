/* error_log.c: the game's error reporters. Each stamps the message with the local time (and an object's name),
   appends both to ERROR.TXT when logging is on (g_errorLogging), and hands them to the error hook (g_errorHook);
   sys_errorTerminate and sys_fatalError then run the cleanup hook (g_errorCleanupHook) and exit. */
#include "../game.h"
#include <stdarg.h>

#define sprintf_game ((int (CDECL *)(char *, const char *, ...))CRT_FN(sprintf))
#define vsprintf_game(out, format, args) CRT_CALL(vsprintf, int, char *, const char *, va_list)(out, format, args)
#define fprintf_game ((int (CDECL *)(void *, const char *, ...))CRT_FN(fprintf))
typedef int (CDECL *ErrorHook)(char *stamp, char *text);

#define fseek(f, offset, whence) CRT_CALL(fseek, int, void *, int, int)(f, offset, whence)

/* the message reported: flag (g_errorReported a message, g_fatalReported fatal) set; the time line from timeFormat (with the
   name at object +4 first when there is an object). Returns the error hook's eax */
static int report(u32 flag, const u8 *object, u32 timeFormat, const char *format, va_list args)
{
	u16 st[8];   /* SYSTEMTIME: year, month, weekday, day, hour, minute, second, milliseconds */
	char stamp[0x100], text[0x400];
	GAME_VAR(int, flag) = 1;
	GetLocalTime(st);
	if (object)
		sprintf_game(stamp, (const char *)RELOC(timeFormat), *(const u32 *)(object + 4), st[0], st[1], st[3], st[4], st[5], st[6], st[7]);
	else
		sprintf_game(stamp, (const char *)RELOC(timeFormat), st[0], st[1], st[3], st[4], st[5], st[6], st[7]);
	vsprintf_game(text, format, args);
	if (g_errorLogging == 1) {
		void *f = crt_fopen((const char *)STR(0x4c582c, "ERROR.TXT"), (const char *)STR(0x4c5838, "at+"));   /* ERROR.TXT, appended */
		if (f) {
			fseek(f, 0, 2);
			fprintf_game(f, (const char *)STR(0x4c5824, "%s\n%s\n"), stamp, text);
			fprintf_game(f, (const char *)STR(0x4c57d0, "-------------------------------------..."));
			fclose(f);
		}
	}
	return g_errorHook(stamp, text);
}

/* the cleanup hook, if any, then exit(1) */
static void terminate(void)
{
	Cleanup cleanup = g_errorCleanupHook;
	if (cleanup)
		cleanup();
	crt_exit(1);   /* exit */
}

/* 0x46c840 / 0x46c5f0: a message (without / with the object's name) */
int (sys_errorMessageNoName)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int r = report(ADDR(g_errorReported), NULL, STR(0x4c58a0, "Error Message at %d/%d/%d/%d:%d:%d(%d)"), format, args);
	va_end(args);
	return r;
}
int (sys_errorMessage)(const u8 *object, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int r = report(ADDR(g_errorReported), object, STR(0x4c583c, "Error in %s - Message at %d/%d/%d/%d:..."), format, args);
	va_end(args);
	return r;
}

/* 0x46c950 / 0x46c710: a fatal error (without / with the object's name): reported, then the game ends */
void (sys_errorTerminate)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	report(ADDR(g_fatalReported), NULL, STR(0x4c58c8, "Error Termination at %d/%d/%d/%d:%d:%..."), format, args);
	va_end(args);
	terminate();
}
void (sys_fatalError)(const u8 *object, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	report(ADDR(g_fatalReported), object, STR(0x4c586c, "Error in %s - Termination at %d/%d/%d..."), format, args);
	va_end(args);
	terminate();
}
