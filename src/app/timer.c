/* timer.c: the game's clock: the performance counter, shifted right until its frequency is at most 2 MHz (so the
   counter's low 32 bits are enough between two frames), and a wait on it. */
#include "../game.h"

#define TIMER_MAX_FREQUENCY k_2000000
#define ONE k_1
#define FRAME_RATE k_60        /* 60: timer_now's seconds to 1/60 s frames */

/* 0x4302d0: the frequency (a message box when there is none), halved until it is at most 2 MHz, the shift count
   kept; the time's state (0x9db980, two doubles) cleared and the tick length 1 / f */
void (timer_init)(void)
{
	u64 f;
	if (!QueryPerformanceFrequency(&f))
		sys_messageBox((const char *)STR(0x4b24d4, "No hardware timer available"));
	g_timerFrequency = f;
	int shift = 0;
	g_timerShift = 0;
	while ((u32)(f >> 32) || (long double)(u32)f > TIMER_MAX_FREQUENCY) {
		f >>= 1;
		shift++;
	}
	g_timerShift = shift;
	for (int i = 0; i < 4; i++)
		GAME_VAR(u32, OBJ(g_timerClocks) + i * 4) = 0;
	g_timerTick = ONE / (long double)(u32)f;
}

/* 0x41e730: busy-wait until `frames` 1/60 s have passed */
void (timer_waitFrames)(double frames)
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
#define g_time g_clockNow
	u32 counter[2];
	IMPORT(0x4a9140, int, u32 *)(counter);   /* QueryPerformanceCounter */
	int shift = g_timerShift;
	g_timerHigh = counter[1];
	g_perfCounter = counter[0];
	u32 count = counter[1] << ((32 - shift) & 31) | counter[0] >> (shift & 31);   /* (x86 shift counts, mod 32) */
	if (g_timerFirstCall) {
		long double t = g_time;
		g_lastCount = count;
		g_timerFirstCall = 0;
		return t;
	}
	u32 last = g_lastCount;
	if (count <= last && last - count < 0x10000000) {
		long double t = g_time;
		g_lastCount = count;
		return t;
	}
	g_lastCount = count;
	long double t = (long double)(count - last) * g_timerTick + g_time;
	g_time = (double)t;
	long double before = g_lastTime;
	if (t == before || t != t || before != before) {   /* (fcom: equal or unordered) */
		if (++g_timerRepeatCount > 100000) {
			t += k_1;
			g_time = (double)t;
			g_timerRepeatCount = 0;
		}
	} else
		g_timerRepeatCount = 0;
	g_lastTime = (double)t;
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
	TimeSync *ts = (TimeSync *)t;
#define QueryPerformanceCounter(out) IMPORT(0x4a9140, int, u64 *)(out)
#define fatal() sys_fatalErrorN((char *)OBJ(g_logTimeSync), (const char *)STR(0x4c7b80, "invalid system time"))
	if (ts->started == 0) {
		if (!QueryPerformanceFrequency(&ts->frequency))
			fatal();
		if (!QueryPerformanceCounter(&ts->lastCount))
			fatal();
		if (!(ts->maxFrame > 0))
			BITS(ts->maxFrame) = 0x3d888889;   /* 1/15 */
		ts->started = 1;
	}
	ts->frames++;
	u64 now;
	QueryPerformanceCounter(&now);
	int64_t rise = (int64_t)(now - ts->lastCount);
	ts->rise = rise;
	ts->lastCount = now;
	ts->riseSum += rise;
	int64_t sum = ts->riseSum, freq = (int64_t)ts->frequency;
	if (sum > freq) {
		if (sum > 0)
			ts->fps = (float)((long double)freq * ts->frames / (long double)sum);
		else
			(*(int *)&ts->fps) = 0;
		((u32 *)&ts->riseSum)[0] = 0;   /* (the low half only, then the high half below) */
		ts->frames = 0;
		((u32 *)&ts->riseSum)[1] = 0;
	}
	long double dt = (long double)rise / (long double)freq;
	ts->frameTime = (float)dt;
	if (dt > ts->maxFrame)
		BITS(ts->frameTime) = BITS(ts->maxFrame);
	return ts->frameTime;
#undef QueryPerformanceCounter
#undef fatal
}

/* 0x461210 (thiscall on a frame timer): the frame's time (timer_getGameTime of the timer at +0xc) kept in a ring of
   ten (+0x48, next at +0x70), their average (the sum times 0x4a955c, 0.1) in +0x44; the average is also left on the
   FPU stack, as the original leaves it (its callers pop it) */
long double THISCALL (frameTimer_average)(u8 *t)
{
	Scene *sc = (Scene *)t;
	long double now = timer_getGameTime(t + 0xc);
	sc->frameTimes[sc->frameTimeNext] = (float)now;
	sc->frameTimeNext = (sc->frameTimeNext + 1) % 10;
	long double sum = k_0f;   /* 0 */
	for (int i = 0; i < 10; i++)
		sum += sc->frameTimes[i];
	sum *= k_tenth;
	sc->frameTime = (float)sum;
	return sum;
}
