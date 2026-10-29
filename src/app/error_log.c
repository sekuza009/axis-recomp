/* error_log.c: the game's error reporters. Each stamps the message with the local time (and an object's name),
   appends both to ERROR.TXT when logging is on (0xa1efdc), and hands them to the error hook (0x4c57cc);
   sys_errorTerminate and sys_fatalError then run the cleanup hook (0xa1efe8) and exit. */
#include "../game.h"
#include <stdarg.h>

#define GetLocalTime(st) IMPORT(0x4a90f4, void, u16 *)(st)
#define sprintf_game ((int (CDECL *)(char *, const char *, ...))0x49e9dd)
#define vsprintf_game(out, format, args) GAME_CDECL(0x49ed2e, int, char *, const char *, va_list)(out, format, args)
#define fprintf_game ((int (CDECL *)(void *, const char *, ...))0x49f135)
typedef int (CDECL *ErrorHook)(char *stamp, char *text);
typedef void (*Cleanup)(void);

#define fseek(f, offset, whence) GAME_CDECL(0x49e91e, int, void *, int, int)(f, offset, whence)

/* the message reported: flag (0xa1efe0 a message, 0xa1efe4 fatal) set; the time line from timeFormat (with the
   name at object +4 first when there is an object). Returns the error hook's eax */
static int report(u32 flag, const u8 *object, u32 timeFormat, const char *format, va_list args)
{
	u16 st[8];   /* SYSTEMTIME: year, month, weekday, day, hour, minute, second, milliseconds */
	char stamp[0x100], text[0x400];
	GAME_VAR(int, flag) = 1;
	GetLocalTime(st);
	if (object)
		sprintf_game(stamp, (const char *)timeFormat, *(const u32 *)(object + 4), st[0], st[1], st[3], st[4], st[5], st[6], st[7]);
	else
		sprintf_game(stamp, (const char *)timeFormat, st[0], st[1], st[3], st[4], st[5], st[6], st[7]);
	vsprintf_game(text, format, args);
	if (GAME_VAR(int, 0xa1efdc) == 1) {
		void *f = crt_fopen((const char *)0x4c582c, (const char *)0x4c5838);   /* ERROR.TXT, appended */
		if (f) {
			fseek(f, 0, 2);
			fprintf_game(f, (const char *)0x4c5824, stamp, text);
			fprintf_game(f, (const char *)0x4c57d0);
			fclose(f);
		}
	}
	return GAME_VAR(ErrorHook, 0x4c57cc)(stamp, text);
}

/* the cleanup hook, if any, then exit(1) */
static void terminate(void)
{
	Cleanup cleanup = GAME_VAR(Cleanup, 0xa1efe8);
	if (cleanup)
		cleanup();
	GAME_CDECL(0x49edac, void, int)(1);   /* exit */
}

/* 0x46c840 / 0x46c5f0: a message (without / with the object's name) */
int (sys_errorMessageNoName)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int r = report(0xa1efe0, NULL, 0x4c58a0, format, args);
	va_end(args);
	return r;
}
int (sys_errorMessage)(const u8 *object, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	int r = report(0xa1efe0, object, 0x4c583c, format, args);
	va_end(args);
	return r;
}

/* 0x46c950 / 0x46c710: a fatal error (without / with the object's name): reported, then the game ends */
void (sys_errorTerminate)(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	report(0xa1efe4, NULL, 0x4c58c8, format, args);
	va_end(args);
	terminate();
}
void (sys_fatalError)(const u8 *object, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	report(0xa1efe4, object, 0x4c586c, format, args);
	va_end(args);
	terminate();
}
