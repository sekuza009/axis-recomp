/* hud_message_box.c: the message box at the top of the screen (matches and replays): one waiting message of up to
   four lines, or else the last events, fading out with scene->msgFade. */
#include "../game.h"
#include <string.h>

/* the colours of the event lines by their type */
static void event_setColour(u32 type, float alpha)
{
	switch (type) {
	case 0: text_setColor(0.0f, 1.0f, 0.0f, alpha); break;     /* green */
	case 1: text_setColor(1.0f, 1.0f, 1.0f, alpha); break;     /* white */
	case 2: text_setColor(0.0f, 0.0f, 1.0f, alpha); break;     /* blue */
	case 3: text_setColor(1.0f, 0.0f, 0.0f, alpha); break;     /* red */
	case 4:
	case 5: text_setColor(1.0f, 1.0f, 0.0f, alpha); break;     /* yellow */
	}                                                           /* others keep the current colour */
}

/* 0x495190: the message box (drawn by the HUD in matches and replays) */
void THISCALL (hud_drawMessageBox)(Scene *scene)
{
	char line[256];
	float alpha;
	if (scene->msgFade >= 1.0f)
		alpha = 1.0f;
	else if (scene->msgFade >= 0.0f)
		alpha = scene->msgFade;
	else
		alpha = 0.0f;                                           /* NaN too */
	glColor4f(0.0f, 0.0f, 0.0f, alpha * 0.5f);
	hud_fillRect(0x1c, 0x24, 0x264, 0x6c);

	if (scene->msgRead < scene->msgWrite) {
		/* the next waiting message: four lines of its text block */
		MessageSlot *msg = &scene->msgRing[scene->msgRead & 31];
		int y, offset = 0;
		for (y = 0x28; y < 0x68; y += 0x10, offset += 0x41) {
			if (msg->colour < 16) {
				Colour *c = &g_textColours[msg->colour];
				text_setColor(c->r, c->g, c->b, alpha);
			} else {
				text_setColor(1.0f, 1.0f, 1.0f, 0.0f);
			}
			strcpy(line, &scene->msgText[msg->text][offset]);
			text_drawSized(0x20, y, line, 8);
		}
		return;
	}
	/* no message: the events still shown, one per line */
	for (u32 i = scene->eventFirst; i < scene->eventCount; i++) {
		EventLine *event = &scene->events[i % 5];
		event_setColour(event->type, alpha);
		text_drawSized(0x20, (int)((i - scene->eventFirst) * 0x10 + 0x28), event->text, 8);
	}
}
