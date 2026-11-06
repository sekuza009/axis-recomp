/* items.c: the map's items (power-ups, ammo...) handed to the view volume. */
#include "../game.h"

/* a texel count to a texture coordinate, rounded to a float as the original stores it */
static float texel(int n, float perTexel)
{
	return (float)((long double)n * perTexel);
}

/* 0x48f970 (stage_drawItems): every item that is not taken and lies within stage->cullMargin of the camera on each axis.
   In 3D (g_highDetail, and always for type 34) its type's model at the item's place and turn; otherwise a 300-unit
   billboard with its 32-texel icon from the item atlas (eight a row). Items fading in or out (fade below 1, or NaN)
   are drawn white with alpha 255 * fade; whole billboards take g_white, whole models their own colours. */
void THISCALL (stage_drawItems)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->itemCount; i++) {
		MapItem *item = &stage->items[i];
		int type = item->type;
		if (type < 0 || item->taken == 1)
			continue;
		ItemType *kind = &stage->itemTypes[type];
		float r = stage->cullMargin;
		/* the low sides first, then the high ones; a NaN passes both tests */
		int outside = 0;
		for (int k = 0; k < 3 && !outside; k++)
			outside = (long double)stage->cameraPos[k] - r > item->pos[k];
		for (int k = 0; k < 3 && !outside; k++)
			outside = !((long double)r + stage->cameraPos[k] >= item->pos[k]);
		if (outside)
			continue;

		u8 colour[4];
		if (g_highDetail == 1 || type == 34) {
			const u8 *tint = NULL;
			if (!(item->timer >= 1.0f)) {
				colour[0] = colour[1] = colour[2] = 0xff;
				colour[3] = (u8)ftol((long double)item->timer * 255.0f);
				tint = colour;
			}
			Model *model = kind->model;
			if (model == NULL)
				continue;
			glPushMatrix();
			glTranslatef_stored(item->pos);
			glRotatef((float)((long double)item->angle * 0.1f), 0.0f, 1.0f, 0.0f);
			ViewVolume_queueModel(view, model, 0, NULL, 0, tint, 1, -1, 0);
			glPopMatrix();
		} else {
			if (!(item->timer >= 1.0f)) {
				colour[0] = colour[1] = colour[2] = 0xff;
				colour[3] = (u8)ftol((long double)item->timer * 255.0f);
			} else {
				*(u32 *)colour = g_white;
			}
			float uv0[2] = { texel(type % 8 * 32, 1.0f / 256), texel(type / 8 * 32, 1.0f / 256) };
			float uv1[2] = { uv0[0] + 0.125f, uv0[1] + 0.125f };
			float a[2] = { -150.0f, -150.0f }, b[2] = { 150.0f, 150.0f };
			ViewVolume_addBillboard(view, stage->billboards, uv0, uv1, 150.0f, colour, a, b, item->pos, 2, 1);
		}
	}
}
