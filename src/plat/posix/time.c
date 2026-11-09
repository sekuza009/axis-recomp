/* plat/posix/time.c: plat.h's time for Linux, macOS and the like (portable build only; not built on Windows): the
   counter in nanoseconds of the monotonic clock (frequency 10^9 - the game clock shifts it down to its 2 MHz, as it
   does Windows' counter), milliseconds of the same clock, sleeping, and the date as Windows' SYSTEMTIME fields. */
#if defined(AXIS_PORTABLE) && !defined(_WIN32)
#define _POSIX_C_SOURCE 200809L
#include <stdint.h>
#include <string.h>
#include <time.h>

static uint64_t now_ns(void)
{
	struct timespec t;
	clock_gettime(CLOCK_MONOTONIC, &t);
	return (uint64_t)t.tv_sec * 1000000000u + (uint64_t)t.tv_nsec;
}

int plat_timeCounter(void *count)
{
	uint64_t n = now_ns();
	memcpy(count, &n, 8);
	return 1;
}
int plat_timeFrequency(void *frequency)
{
	uint64_t f = 1000000000u;
	memcpy(frequency, &f, 8);
	return 1;
}
uint32_t plat_timeMs(void) { return (uint32_t)(now_ns() / 1000000u); }
uint32_t plat_timeTicks(void) { return (uint32_t)(now_ns() / 1000000u); }
void plat_sleep(uint32_t ms)
{
	struct timespec t = { (time_t)(ms / 1000), (long)(ms % 1000) * 1000000L };
	while (nanosleep(&t, &t) != 0)
		;
}

/* SYSTEMTIME: year, month (1-12), weekday (0 = Sunday), day, hour, minute, second, milliseconds */
static void system_time(void *out, int local)
{
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	struct tm m;
	time_t s = t.tv_sec;
	if (local)
		localtime_r(&s, &m);
	else
		gmtime_r(&s, &m);
	uint16_t st[8] = { (uint16_t)(m.tm_year + 1900), (uint16_t)(m.tm_mon + 1), (uint16_t)m.tm_wday, (uint16_t)m.tm_mday,
	                   (uint16_t)m.tm_hour, (uint16_t)m.tm_min, (uint16_t)m.tm_sec, (uint16_t)(t.tv_nsec / 1000000) };
	memcpy(out, st, sizeof st);
}
void plat_timeLocal(void *st) { system_time(st, 1); }
void plat_timeUTC(void *st) { system_time(st, 0); }
#endif
