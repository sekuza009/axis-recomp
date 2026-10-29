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
