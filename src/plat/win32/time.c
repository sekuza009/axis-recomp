/* plat/win32/time.c: plat.h's time for Windows (portable build only): each the call the original makes (plat.h's
   master definitions, expanded here - through the game's import slots, so the loader's layers still apply). */
#include "../../game.h"
#ifdef AXIS_PORTABLE
#undef AXIS_PORTABLE   /* (plat.h's master definitions: the original's calls) */
#include "../plat.h"
#define AXIS_PORTABLE

int plat_timeCounter(void *count) { return TIME_COUNTER(count); }
int plat_timeFrequency(void *frequency) { return TIME_FREQUENCY(frequency); }
u32 plat_timeMs(void) { return TIME_MS(); }
u32 plat_timeTicks(void) { return TIME_TICKS(); }
void plat_sleep(u32 ms) { TIME_SLEEP(ms); }
void plat_timeLocal(void *st) { TIME_LOCAL(st); }
void plat_timeUTC(void *st) { TIME_UTC(st); }
#endif
