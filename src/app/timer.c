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

/* 0x487490 (thiscall on a frame timer): the frame time in seconds. On first use the counter's frequency (+0xc) and
   start (+0x14) are read (a fatal message if either fails) and the longest frame (+0x34) set to 1/15 s unless
   positive. Each call counts the frame (+8), takes the counter's rise (+0x1c) and adds it up (+0x24); once that
   passes a second the frames per second go to +0x2c (0 if the sum is not positive) and the count and sum restart.
   The frame time (+0x30) is the rise over the frequency, at most +0x34; returned as stored */
long double THISCALL (timer_getGameTime)(u8 *t)
{
#define FIELD(type, offset) GAME_VAR(type, t + (offset))
#define QueryPerformanceCounter(out) IMPORT(0x4a9140, int, u64 *)(out)
#define fatal() GAME_CDECL(0x46c710, void, char *, const char *)((char *)0xae2f00, (const char *)0x4c7b80)
	if (FIELD(int, 4) == 0) {
		if (!QueryPerformanceFrequency(&FIELD(u64, 0xc)))
			fatal();
		if (!QueryPerformanceCounter(&FIELD(u64, 0x14)))
			fatal();
		if (!(FIELD(float, 0x34) > 0))
			FIELD(u32, 0x34) = 0x3d888889;   /* 1/15 */
		FIELD(int, 4) = 1;
	}
	FIELD(int, 8)++;
	u64 now;
	QueryPerformanceCounter(&now);
	int64_t rise = (int64_t)(now - FIELD(u64, 0x14));
	FIELD(int64_t, 0x1c) = rise;
	FIELD(u64, 0x14) = now;
	FIELD(int64_t, 0x24) += rise;
	int64_t sum = FIELD(int64_t, 0x24), freq = FIELD(int64_t, 0xc);
	if (sum > freq) {
		if (sum > 0)
			FIELD(float, 0x2c) = (float)((long double)freq * FIELD(int, 8) / (long double)sum);
		else
			FIELD(int, 0x2c) = 0;
		FIELD(u32, 0x24) = 0;   /* (the low half only, then the high half below) */
		FIELD(int, 8) = 0;
		FIELD(u32, 0x28) = 0;
	}
	long double dt = (long double)rise / (long double)freq;
	FIELD(float, 0x30) = (float)dt;
	if (dt > FIELD(float, 0x34))
		FIELD(u32, 0x30) = FIELD(u32, 0x34);
	return FIELD(float, 0x30);
#undef FIELD
#undef QueryPerformanceCounter
#undef fatal
}

/* 0x461210 (thiscall on a frame timer): the frame's time (timer_getGameTime of the timer at +0xc) kept in a ring of
   ten (+0x48, next at +0x70), their average (the sum times 0x4a955c, 0.1) in +0x44; the average is also left on the
   FPU stack, as the original leaves it (its callers pop it) */
long double THISCALL (armc_461210)(u8 *t)
{
#define FIELD(type, offset) GAME_VAR(type, t + (offset))
	long double now = timer_getGameTime(t + 0xc);
	FIELD(float, 0x48 + FIELD(int, 0x70) * 4) = (float)now;
	FIELD(int, 0x70) = (FIELD(int, 0x70) + 1) % 10;
	long double sum = GAME_VAR(float, 0x4a93e8);   /* 0 */
	for (int i = 0; i < 10; i++)
		sum += FIELD(float, 0x48 + i * 4);
	sum *= GAME_VAR(float, 0x4a955c);
	FIELD(float, 0x44) = (float)sum;
	return sum;
#undef FIELD
}
