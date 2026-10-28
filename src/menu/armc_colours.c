/* armc_colours.c: the ARM CENTER's colour sliders, dragged with the pointer. Each colour slot holds two colours of
   three values (hue, then chroma and value); a slider's position is the pointer's x from the slider's left edge
   (0x4dcc98, less 184 units), 0.00625 per unit, so 0 .. 1 across 160 units. Dragging marks the mech's colours as
   changed (0x4dca98). */
#include "../game.h"

#define g_armcColours ((float *)0x4dc4b8)       /* six values per slot */
#define g_sliderLeft GAME_VAR(int, 0x4dcc98)
#define g_coloursChanged GAME_VAR(int, 0x4dca98)

static long double slider_pos(void)
{
	return (long double)(g_mouseX - g_sliderLeft + 0xb8) * 0.00625f;
}

/* a hue: 0 .. 360 degrees (clamped to 359, not 360), stored shifted by half a turn into -180 .. 180, then back into
   0 .. 360 when negative */
static void slider_hue(float *hue)
{
	long double v = slider_pos() * 360.0f;
	*hue = (float)v;
	if (!(v < 360.0f))
		*hue = 359.0f;
	v = (long double)*hue - 180.0f;
	*hue = (float)v;
	g_coloursChanged = 1;
	if (v < 0)
		*hue = (float)(v + 360.0f);
}

/* 0x40f5d0, 0x40f670, 0x40f6b0: the first colour's hue, chroma and value (0 .. 1) */
void (armc_dragPrimaryHue)(void) { slider_hue(&g_armcColours[g_armcColourSlot * 6]); }

void (armc_dragPrimaryChroma)(void)
{
	g_coloursChanged = 1;
	g_armcColours[g_armcColourSlot * 6 + 1] = (float)slider_pos();
}

void (armc_dragPrimaryValue)(void)
{
	g_coloursChanged = 1;
	g_armcColours[g_armcColourSlot * 6 + 2] = (float)slider_pos();
}

/* 0x40f6f0, 0x40f790, 0x40f7e0: the second colour's: its chroma and value run -1 .. 1 */
void (armc_dragSecondaryHue)(void) { slider_hue(&g_armcColours[g_armcColourSlot * 6 + 3]); }

void (armc_dragSecondaryChroma)(void)
{
	long double v = slider_pos();
	g_coloursChanged = 1;
	g_armcColours[g_armcColourSlot * 6 + 4] = (float)(v + v - 1.0f);
}

void (armc_dragSecondaryValue)(void)
{
	long double v = slider_pos();
	g_coloursChanged = 1;
	g_armcColours[g_armcColourSlot * 6 + 5] = (float)(v + v - 1.0f);
}
