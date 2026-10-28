/* objects.c: the stage's map objects (animated scenery), actors and projectiles handed to the view volume, once
   per pass. Each list is walked up to its count, read again after every entry. */
#include "../game.h"

/* 0x490b30 (hud_490b30): object i, unless it is hidden or has no model, when its bounding sphere (the model's radius
   plus stage->cullMargin) touches the box around stage->cameraPos: queued with its matrix and pose, culled per mesh */
void THISCALL (hud_490b30)(Stage *stage, int i, void *view)
{
	MapObject *o = &stage->objects[i];
	if (o->flags & 2)
		return;
	Model *model = o->model;
	if (model == NULL)
		return;
	float r = f32((long double)model->radius + stage->cullMargin);
	/* the low sides first, then the high ones; a NaN passes both tests */
	for (int k = 0; k < 3; k++)
		if ((long double)stage->cameraPos[k] - r > o->pos[k])
			return;
	for (int k = 0; k < 3; k++)
		if (!((long double)r + stage->cameraPos[k] >= o->pos[k]))
			return;
	ViewVolume_projectObject(view, model, o->poseSide == 0 ? o->poseFrom : o->poseTo, o->matrix, 0, NULL, 1, -1, 0);
}

/* 0x490da0 (hud_490da0): every active object */
void THISCALL (hud_490da0)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->objectCount; i++)
		if (stage->objects[i].active == 1)
			hud_490b30(stage, i, view);
}

/* 0x45e170 (hud_45e170): every active actor's parts; pass is handed on (hud_pass gives 0 and 1, the match's view
   -1) */
void THISCALL (hud_45e170)(Stage *stage, void *view, int pass)
{
	for (int i = 0; i < stage->actorCount; i++)
		if (stage->actors[i].active == 1)
			actor_updateAllParts(stage, i, view, pass);
}

/* 0x479af0 (hud_479af0): every active projectile */
void THISCALL (hud_479af0)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->projectileCount; i++)
		if (stage->projectiles[i].active == 1)
			hud_476890(stage, i, view);
}
