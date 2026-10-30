/* timer.c: the game's clock: the performance counter, shifted right until its frequency is at most 2 MHz (so the
   counter's low 32 bits are enough between two frames), and a wait on it. */
#include "../game.h"

#define g_timerFrequency GAME_VAR(u64, 0x4df030)     /* QueryPerformanceFrequency's result */
#define g_timerShift GAME_VAR(int, 0x67ef1c)         /* how far the counter is shifted right */
#define g_timerTick GAME_VAR(double, 0x4ded58)       /* seconds per (shifted) tick */
#define TIMER_MAX_FREQUENCY GAME_VAR(double, 0x4a9580)
#define ONE GAME_VAR(double, 0x4a94e0)
#define FRAME_RATE GAME_VAR(double, 0x4a94d0)        /* 60: timer_now's seconds to 1/60 s frames */

/* 0x4302d0: the frequency (a message box when there is none), halved until it is at most 2 MHz, the shift count
   kept; the time's state (0x9db980, two doubles) cleared and the tick length 1 / f */
void (timer_init)(void)
{
	u64 f;
	if (!QueryPerformanceFrequency(&f))
		GAME_CDECL(0x41edf0, int, const char *)((const char *)0x4b24d4);   /* sys_messageBox */
	g_timerFrequency = f;
	int shift = 0;
	g_timerShift = 0;
	while ((u32)(f >> 32) || (long double)(u32)f > TIMER_MAX_FREQUENCY) {
		f >>= 1;
		shift++;
	}
	g_timerShift = shift;
	for (int i = 0; i < 4; i++)
		GAME_VAR(u32, 0x9db980 + i * 4) = 0;
	g_timerTick = ONE / (long double)(u32)f;
}

/* 0x41e730: busy-wait until `frames` 1/60 s have passed */
void (intro_41e730)(double frames)
{
	volatile double start = timer_now();
	while (!((timer_now() - start) * FRAME_RATE >= frames))
		;
}

/* 0x4301e0: the time in seconds (0x9db980, a double; the value returned unrounded): the performance counter
   (QueryPerformanceCounter, kept at 0x5ae9c8) shifted right by 0x67ef1c into 32 bits, its rise since the last
   reading (0x9dbf08) times the seconds per count (0x4ded58) added. The first call (0x4b1048) only takes the
   reading; a reading a little below the last (less than 0x10000000) adds nothing. A time that stays equal to the
   one before (0x9db988) 100000 calls in a row is moved on by 0x4a94e0 */
long double (timer_now)(void)
{
#define g_time GAME_VAR(double, 0x9db980)
#define g_lastCount GAME_VAR(u32, 0x9dbf08)
	u32 counter[2];
	IMPORT(0x4a9140, int, u32 *)(counter);   /* QueryPerformanceCounter */
	int shift = GAME_VAR(int, 0x67ef1c);
	GAME_VAR(u32, 0x5ae9cc) = counter[1];
	GAME_VAR(u32, 0x5ae9c8) = counter[0];
	u32 count = counter[1] << ((32 - shift) & 31) | counter[0] >> (shift & 31);   /* (x86 shift counts, mod 32) */
	if (GAME_VAR(int, 0x4b1048)) {
		long double t = g_time;
		g_lastCount = count;
		GAME_VAR(int, 0x4b1048) = 0;
		return t;
	}
	u32 last = g_lastCount;
	if (count <= last && last - count < 0x10000000) {
		long double t = g_time;
		g_lastCount = count;
		return t;
	}
	g_lastCount = count;
	long double t = (long double)(count - last) * GAME_VAR(double, 0x4ded58) + g_time;
	g_time = (double)t;
	long double before = GAME_VAR(double, 0x9db988);
	if (t == before || t != t || before != before) {   /* (fcom: equal or unordered) */
		if (++GAME_VAR(int, 0x9dbf00) > 100000) {
			t += GAME_VAR(double, 0x4a94e0);
			g_time = (double)t;
			GAME_VAR(int, 0x9dbf00) = 0;
		}
	} else
		GAME_VAR(int, 0x9dbf00) = 0;
	GAME_VAR(double, 0x9db988) = (double)t;
	return t;
#undef g_time
#undef g_lastCount
}
