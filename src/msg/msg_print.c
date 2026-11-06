/* msg_print.c: the event list, the last five lines of the match's messages (a ring in the scene). */
#include <stdarg.h>
#include "../game.h"

/* 0x4629f0 (msg_print): a new line in colour, printf-formatted; the oldest line drops out when the ring is full,
   and the message box comes up (msgFade 5). Returns the new count / 5: what the original leaves in eax, and the
   message functions built on it pass it on */
unsigned (msg_print)(Scene *scene, int colour, const char *format, ...)
{
	va_list args;
	va_start(args, format);
	scene->events[scene->eventCount % 5].type = colour;
	vsprintf(scene->events[scene->eventCount % 5].text, format, args);
	BITS(scene->events[scene->eventCount % 5].timeLeft) = BITS(scene->eventTime);
	scene->eventCount++;
	if (scene->eventCount % 5 == scene->eventFirst % 5)
		scene->eventFirst++;
	scene->msgFade = 5.0f;
	va_end(args);
	return scene->eventCount / 5;
}
