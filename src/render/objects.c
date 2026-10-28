/* objects.c: the map's objects (animated scenery) handed to the view volume for drawing. */
#include "../game.h"

/* 0x490b30 (hud_490b30): object i, unless it is hidden or has no model, when its bounding sphere (the model's radius
   plus scene->cullMargin) touches the box around scene->cameraPos: queued with its matrix and pose, culled per mesh */
void THISCALL (hud_490b30)(Scene *scene, int i, void *view)
{
	MapObject *o = &scene->objects[i];
	if (o->flags & 2)
		return;
	Model *model = o->model;
	if (model == NULL)
		return;
	float r = (float)((long double)model->radius + scene->cullMargin);
	/* the low sides first, then the high ones; a NaN passes both tests */
	for (int k = 0; k < 3; k++)
		if ((long double)scene->cameraPos[k] - r > o->pos[k])
			return;
	for (int k = 0; k < 3; k++)
		if (!((long double)r + scene->cameraPos[k] >= o->pos[k]))
			return;
	ViewVolume_projectObject(view, model, o->poseSide == 0 ? o->poseFrom : o->poseTo, o->matrix, 0, 0, 1, -1, 0);
}

/* 0x490da0 (hud_490da0): every active object (the count read again after each one) */
void THISCALL (hud_490da0)(Scene *scene, void *view)
{
	for (int i = 0; i < scene->objectCount; i++)
		if (scene->objects[i].active == 1)
			hud_490b30(scene, i, view);
}
