/* armc_colours.c: the ARM CENTER's colour sliders, dragged with the pointer. Each colour slot holds two colours of
   three values (hue, then chroma and value); a slider's position is the pointer's x from the slider's left edge
   (0x4dcc98, less 184 units), 0.00625 per unit, so 0 .. 1 across 160 units. Dragging marks the mech's colours as
   changed (0x4dca98). */
#include "../game.h"

#define g_armcColours ((float *)IMG(0x4dc4b8))       /* six values per slot */

static long double slider_pos(void)
{
	return (long double)(g_mouseX - g_armcSliderLeft + 0xb8) * 0.00625f;
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

/* ---- the preview mech tinted: the local player's five part shapes (in its stride-0x47fd2 record) take colour
   slots' six values (shape_setTint) ---- */
static const u32 part_shapes[5] = { 0x1755568, 0x175d4b4, 0x1765400, 0x177504c, 0x1784c98 };

static void tint_part(int part, int slot)
{
	const u32 *c = (const u32 *)g_armcColours + slot * 6;
	Scene *scene = g_scene;
	shape_setTint((u8 *)scene + part_shapes[part] + scene->localPlayer * 0x47fd2, c[0], c[1], c[2], c[3], c[4], c[5]);
}

/* 0x41cf20: the colour slot being edited applied to its part; slot 5 (all) puts the undo buffer back first and
   tints every part with it */
void (armc_applyColourSlot)(void)
{
	int slot = g_armcColourSlot;
	if (slot < 0 || slot > 5)
		return;
	if (slot < 5) {
		tint_part(slot, slot);
		return;
	}
	armc_restoreColourUndo();
	for (int part = 0; part < 5; part++)
		tint_part(part, g_armcColourSlot);
}

/* 0x41d280: after a change (0x4dd074) every part takes its own slot's colours; then the part in view is tinted
   again with its slot */
void (armc_retintParts)(void)
{
	if (g_colourChanged) {
		for (int part = 0; part < 5; part++)
			tint_part(part, part);
		g_colourChanged = 0;
	}
	int slot = g_armcPartSlot;
	if (slot >= 0 && slot <= 4)
		tint_part(slot, slot);
}
