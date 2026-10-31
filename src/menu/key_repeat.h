/* key_repeat.h: the menu lists' held-key repeat (up / down share one wait each, cleared when the screen opens) */
#ifndef KEY_REPEAT_H
#define KEY_REPEAT_H

#define g_repeatUp GAME_VAR(float, 0x76d37c)       /* frames until a held up / down key steps again */
#define g_repeatDown GAME_VAR(float, 0x680bb4)

/* a held key: the first press steps at once and waits 4 frames, then it steps whenever the wait runs out (the text
   cursor's blink restarting each frame). 1 when the key is held */
static int key_repeat(int key, float *wait, void (*step)(void))
{
	if (input_isDown(key) == 0)
		BITS(*wait) = 0;
	if (input_isDown(key) != 1)
		return 0;
	g_cursorBlink = 0;
	if (*wait > k_0f) {
		*wait = fsub_m(fld_m(wait), &g_frameTime);
		return 1;
	}
	*wait = 4.0f;
	step();
	return 1;
}

#endif
