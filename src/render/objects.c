/* objects.c: the stage's map objects (animated scenery), actors and projectiles handed to the view volume, once
   per pass. Each list is walked up to its count, read again after every entry. */
#include "../game.h"
#include <string.h>

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

#define K(address) ((const float *)(address))
#define F(type, obj, offset) GAME_VAR(type, (u8 *)(obj) + (offset))

/* an object's animation stopped at its start: time and speed 0, its collision unit put back (space_enableUnit), the
   unit flag cleared */
static void anim_reset(u8 *obj)
{
	F(int, obj, 0x298) = F(int, obj, 0x29c) = 0;
	if (F(void *, obj, 0x28c))
		space_enableUnit(F(void *, obj, 0x28c));
	F(int, obj, 0x290) = 0;
}

/* the animation started (object_setAnimation with its name +0x18 and the speed: +0x14 x k) */
static void anim_start(u8 *scene, int i, u8 *obj, u32 k)
{
	float speed = f32((long double)F(int, obj, 0x14) * *K(k));
	object_setAnimation(scene, i, (const char *)obj + 0x18, *(u32 *)&speed, 1);
}

/* 0x490440 (thiscall on the scene): map object i's frame (0x2cc bytes from +0x131ae44). A running animation (speed
   +0x29c) moves its time (+0x298) on by dt: mode 1 stops below 0 and holds at 1; mode 2 loops (by the game clock,
   +0x20fcd40 / 44); mode 3 stops outside 0 .. 1; the pose is then out of date (+0x2a4). An out-of-date object takes
   its skeleton's pose (skel_applyPose, bone 0) into its matrices (+0xf4 the pose times +0x74, inverses, +0x1f4) and
   its shading (unless flagged 2) and its centre (+0x2bc) again. Shaded twice (+0x288 1) it copies its colours and
   shades the second set. A light (flag 1, with flares on: 0x83a9c8) is projected (+0x2ac ..) and its glow (+0x2a8)
   grows while it is on screen and in plain view of the camera (collision_rayTrace), else fades; while it glows it
   spawns a flare (particle kind 4). A proximity object (flag 8) starts its animation forwards when an actor in play
   comes within its radius (+0x10) or backwards when they all leave; a timed one (flag 0x10) after +0x10 seconds.
   Its caller ignores the eax it leaves */
void THISCALL (actor_render)(u8 *s, int i, float dt)
{
	u8 *obj = s + 0x131ae44 + i * 0x2cc;
	if (!(F(float, obj, 0x29c) == 0 || F(float, obj, 0x29c) != F(float, obj, 0x29c))) {   /* (fcom: a NaN counts as equal) */
		float t = f32(fadd_m(fmul_m(fld_m(&dt), (const float *)(obj + 0x29c)), (const float *)(obj + 0x298)));
		F(float, obj, 0x298) = t;
		switch (F(int, obj, 0x2a0)) {
		case 1:
			if (!(t >= *K(0x4a93e8)))
				anim_reset(obj);
			else if (t > *K(0x4a9424)) {
				F(u32, obj, 0x298) = 0x3f800000;
				F(int, obj, 0x29c) = 0;
			}
			break;
		case 2: {
			long double per = fld_m(K(0x4a9424)) / *(const float *)(obj + 0x29c);
			int now = ftol(fmul_m(fadd_m((long double)F(int, s, 0x20fcd40), (const float *)(s + 0x20fcd44)), K(0x4a94bc)));
			int r = now % ftol(fmul_m(per, K(0x4a94bc)));
			F(float, obj, 0x298) = f32(fmul_m((long double)r, K(0x4a9480)) / per);
			break;
		}
		case 3:
			if (!(t >= *K(0x4a93e8)) || t > *K(0x4a9424))
				anim_reset(obj);
			break;
		}
		F(int, obj, 0x2a4) = 1;
	}
	if (F(int, obj, 0x2a4) == 1) {
		skel_applyPose(F(void *, obj, 0x294), obj + 0x174, 0, F(u32, obj, 0x298));
		float *m = (float *)(obj + 0xf4);
		Mat4_multiply(m, (const float *)(obj + 0x74), (const float *)(obj + 0x174));
		Mat4_invert((float *)(obj + 0x134), m);
		Mat4_invert((float *)(obj + 0x1b4), (const float *)(obj + 0x174));
		Mat4_multiply((float *)(obj + 0x1f4), m, (const float *)(obj + 0xb4));
		Mat4_invert((float *)(obj + 0x234), (const float *)(obj + 0x1f4));
		if (!(obj[0xc] & 2))
			shape_shadeParts(F(u32 *, obj, 0x280), 1, (Model *)F(u8 *, obj, 0x27c), (const LightFactors *)(s + 0x9ccffc),
			                 (const float *)(obj + 0x134));
		F(int, obj, 0x2a4) = 0;
		const float *c = (const float *)(F(u8 *, obj, 0x27c) + 0x20);
		float *out = (float *)(obj + 0x2bc);
		out[0] = f32(fadd_m(fmul_m(fld_m(&m[8]), &c[2]) + fmul_m(fld_m(&m[4]), &c[1]) + fmul_m(fld_m(&m[0]), &c[0]), &m[12]));
		for (int r = 1; r < 3; r++)
			out[r] = f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &c[2]) + fmul_m(fld_m(&m[r]), &c[0]) + fmul_m(fld_m(&m[4 + r]), &c[1]), &m[12 + r]));
	}
	if (F(int, obj, 0x288) == 1 && !(obj[0xc] & 2)) {
		memcpy(F(void *, obj, 0x284), F(void *, obj, 0x280), F(int, F(u8 *, obj, 0x27c), 0x18) * 4);
		shape_shadeParts(F(u32 *, obj, 0x284), 0, (Model *)F(u8 *, obj, 0x27c), (const LightFactors *)(s + 0x9d8010),
		                 (const float *)(obj + 0x134));
	}
	if ((obj[0xc] & 1) && GAME_VAR(int, 0x83a9c8) == 1) {
		const float *p = (const float *)(obj + 0x58), *m = (const float *)(s + 0x20f3a74);
		float *clip = (float *)(obj + 0x2ac);
		clip[0] = f32(fadd_m(fmul_m(fld_m(&m[8]), &p[2]) + fmul_m(fld_m(&m[4]), &p[1]) + fmul_m(fld_m(&m[0]), &p[0]), &m[12]));
		for (int r = 1; r < 4; r++)
			clip[r] = f32(fadd_m(fmul_m(fld_m(&m[8 + r]), &p[2]) + fmul_m(fld_m(&m[r]), &p[0]) + fmul_m(fld_m(&m[4 + r]), &p[1]), &m[12 + r]));
		float nw = f32(-fld_m(&clip[3]));
		u8 hit[12];
		if (clip[0] > nw && clip[1] > nw && clip[2] > nw && !(clip[0] >= clip[3]) && !(clip[1] >= clip[3]) &&
		    !(clip[2] >= clip[3]) && collision_rayTrace(s, (const float *)(s + 0x20f3970), p, hit) == 0) {
			long double g = fadd_m(fmul_m(fld_m(&dt), K(0x4a947c)), (const float *)(obj + 0x2a8));
			F(float, obj, 0x2a8) = f32(g);
			if (g > *K(0x4a9424))
				F(u32, obj, 0x2a8) = 0x3f800000;
		} else {
			long double g = fld_m((const float *)(obj + 0x2a8)) - fmul_m(fld_m(&dt), K(0x4a947c));
			F(float, obj, 0x2a8) = f32(g);
			if (!(g >= *K(0x4a93e8)))
				F(int, obj, 0x2a8) = 0;
		}
		if ((obj[0xc] & 1) && GAME_VAR(int, 0x83a9c8) == 1 && F(float, obj, 0x2a8) > *K(0x4a93e8)) {
			volatile u32 flare[13];   /* (its eighth dword is never set, as in the original) */
			flare[0] = 4;
			flare[1] = ftol(fmul_m(fld_m((const float *)(obj + 0x2a8)), K(0x4a9744)));
			flare[2] = F(u32, obj, 0x58);
			flare[3] = F(u32, obj, 0x5c);
			flare[4] = F(u32, obj, 0x60);
			flare[5] = F(u32, obj, 0x274);
			flare[6] = F(u32, obj, 0x278);
			for (int k = 8; k < 13; k++)
				flare[k] = 0;
			particle_spawn(s, (const void *)flare);
		}
	}
	if (obj[0xc] & 8) {
		long double nearest = fld_m(K(0x4aa4a4));
		for (int k = 0; k < GAME_VAR(int, s + 0x202e8c8); k++) {
			u8 *a = s + 0x1cd93a8 + k * 0x8888;
			if (F(int, a, 0x14c) != 1)
				continue;
			long double dx = fsub_m(fld_m((const float *)(a + 0x154)), (const float *)(obj + 0x58));
			long double dy = fsub_m(fld_m((const float *)(a + 0x158)), (const float *)(obj + 0x5c));
			long double dz = fsub_m(fld_m((const float *)(a + 0x15c)), (const float *)(obj + 0x60));
			long double d2 = (dz * dz + dy * dy) + dx * dx;
			float d2f = f32(d2);
			if (!(d2 >= nearest))
				nearest = fld_m(&d2f);
		}
		long double r = fmul_m((long double)F(int, obj, 0x10), K(0x4a93f4));
		if (F(float, obj, 0x29c) == 0 || F(float, obj, 0x29c) != F(float, obj, 0x29c)) {
			if (!(nearest >= r * r))
				anim_start(s, i, obj, 0x4a9480);
		} else if (F(u32, obj, 0x29c) == 0x3f800000 && nearest > r * r)
			anim_start(s, i, obj, 0x4aa4a0);
	} else if (obj[0xc] & 0x10) {
		if (F(float, obj, 0x29c) == 0 || F(float, obj, 0x29c) != F(float, obj, 0x29c)) {
			if (fmul_m((long double)F(int, obj, 0x10), K(0x4a93f4)) > F(float, obj, 0x2c8)) {
				F(float, obj, 0x2c8) = f32(fadd_m(fld_m(&dt), (const float *)(obj + 0x2c8)));
				return;
			}
			F(int, obj, 0x2c8) = 0;
			anim_start(s, i, obj, 0x4a9480);
		} else if (F(u32, obj, 0x29c) == 0x3f800000)
			anim_start(s, i, obj, 0x4aa4a0);
	}
}
#undef K
#undef F
