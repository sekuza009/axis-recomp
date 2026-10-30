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

/* a light's glow (+0x2a8) over dt: its position (+0x58) projected (by +0x20f3a74, kept at +0x2ac), it grows while
   that is on screen and nothing lies between it and the camera (collision_rayTrace), up to 1, else fades to 0 */
static void object_glow(u8 *s, u8 *obj, float dt)
{
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
		object_glow(s, obj, dt);
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

#define K(address) ((const float *)(address))
#define A(type, offset) GAME_VAR(type, ac + (offset))

static long double root(long double x) { __asm__("fsqrt" : "+t"(x)); return x; }

/* the screen point (the view's width +0x20f3a24 and height +0x20f3a28) of clip x / w and y / w */
static void to_screen(u8 *s, long double qx, long double qy, float *out)
{
	out[0] = f32(fmul_m(fadd_m(qx, K(0x4a9424)) * (long double)GAME_VAR(int, s + 0x20f3a24), K(0x4a942c)));
	out[1] = f32(fmul_m((fld_m(K(0x4a9424)) - qy) * (long double)GAME_VAR(int, s + 0x20f3a28), K(0x4a942c)));
}

/* whether the name tag's width on screen (+0x87c8 .. +0x87d4) is under k (from the width 640 / the screen's) */
static int tag_narrow(u8 *ac, u32 k)
{
	float span = f32(fsub_m(fld_m((const float *)(ac + 0x87d4)), (const float *)(ac + 0x87c8)));
	return fmul_m(fld_m(K(0x4a9510)) / (long double)gfx_getWidth(), K(k)) > span;
}

/* 0x4729b0 (thiscall on the scene): the camera for this frame at pos looking along dir (the last one kept at
   +0x20f3994, its modelview at +0x20f39e0): its modelview (gluLookAt, +0x20f39a0), the view (fov, w / h, near, far:
   +0x20f3a20..), its projection (gluPerspective, +0x20f3a34) and their product (+0x20f3a74). Unless both mode flags
   (+0x2149308 / +0x214930c) are set, every active light (flag 1) glows (object_glow). Every live actor gets its
   screen position and depth (+0x87bc); another than the viewer (+0x202e8d8) that is in view with a clear line of
   sight also gets its name-tag corners (its radius +0x3e8 out), a too-small flag (+0x484), and unless cloaked at the
   local player's rank or above, when the local player faces it (its cosine +0x87e4 against the table 0xa17f38 by
   the local player's heading +4), a timer (+0x87e8) for enemies of a player with a weapon and a tag size (+0x87f0
   3 when the tag is wide); +0x87e0 says it is tagged. Its callers ignore the eax it leaves */
void THISCALL (camera_setupView)(u8 *s, const float *pos, const float *dir, const float *up, float fov, int w, int h, float nr,
                                 float fr, float dt)
{
	float *cam = (float *)(s + 0x20f3970), *mv = (float *)(s + 0x20f39a0), *pr = (float *)(s + 0x20f3a34);
	memcpy(s + 0x20f3994, cam, 12);
	FUN_0047d5a0(s + 0x20f39e0, mv);
	memcpy(cam, pos, 12);
	memcpy(s + 0x20f397c, dir, 12);
	memcpy(s + 0x20f3988, up, 12);
	const float *d = (const float *)(s + 0x20f397c), *u = (const float *)(s + 0x20f3988);
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(cam[0], cam[1], cam[2], (double)fadd_m(fld_m(&d[0]), &cam[0]), (double)fadd_m(fld_m(&d[1]), &cam[1]),
	          (double)fadd_m(fld_m(&d[2]), &cam[2]), u[0], u[1], u[2]);
	glGetFloatv(0xba6, mv);
	glPopMatrix();
	GAME_VAR(float, s + 0x20f3a20) = fov;
	GAME_VAR(int, s + 0x20f3a24) = w;
	GAME_VAR(int, s + 0x20f3a28) = h;
	GAME_VAR(float, s + 0x20f3a2c) = nr;
	GAME_VAR(float, s + 0x20f3a30) = fr;
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(GAME_VAR(float, s + 0x20f3a20), (double)((long double)GAME_VAR(int, s + 0x20f3a24) / GAME_VAR(int, s + 0x20f3a28)),
	               GAME_VAR(float, s + 0x20f3a2c), GAME_VAR(float, s + 0x20f3a30));
	glGetFloatv(0xba7, pr);
	glPopMatrix();
	glMatrixMode(0x1700);
	Mat4_multiply((float *)(s + 0x20f3a74), pr, mv);
	if (!GAME_VAR(int, s + 0x2149308) || !GAME_VAR(int, s + 0x214930c))
		for (int k = 0; k < GAME_VAR(int, s + 0x13c9b24); k++) {
			u8 *obj = s + 0x131ae44 + k * 0x2cc;
			if (GAME_VAR(int, obj + 4) == 1 && (obj[0xc] & 1))
				object_glow(s, obj, dt);
		}
	for (int k = 0; k < GAME_VAR(int, s + 0x202e8c8); k++) {
		u8 *ac = s + 0x1cd93a8 + k * 0x8888;
		if (A(int, 0x14c) != 1)
			continue;
		const float *p = (const float *)(ac + 0x154);
		float e[3], c[4];
		for (int r = 0; r < 3; r++)
			e[r] = f32(fadd_m(fmul_m(fld_m(&mv[8 + r]), &p[2]) + fmul_m(fld_m(&mv[4 + r]), &p[1]) + fmul_m(fld_m(&mv[r]), &p[0]), &mv[12 + r]));
		c[0] = f32(fadd_m(fmul_m(fld_m(&e[1]), &pr[4]) + fmul_m(fld_m(&e[2]), &pr[8]) + fmul_m(fld_m(&e[0]), &pr[0]), &pr[12]));
		for (int r = 1; r < 4; r++)
			c[r] = f32(fadd_m(fmul_m(fld_m(&e[0]), &pr[r]) + fmul_m(fld_m(&e[1]), &pr[4 + r]) + fmul_m(fld_m(&e[2]), &pr[8 + r]), &pr[12 + r]));
		to_screen(s, fdiv_m(fld_m(&c[0]), &c[3]), fdiv_m(fld_m(&c[1]), &c[3]), (float *)(ac + 0x87bc));
		A(float, 0x87c4) = f32(fld_m(&e[2]));
		float nw = f32(-fld_m(&c[3]));
		u8 hit[12];
		if (k == GAME_VAR(int, s + 0x202e8d8) || !(c[0] > nw) || !(c[1] > nw) || !(c[2] > nw) || c[0] >= c[3] || c[1] >= c[3] ||
		    c[2] >= c[3] || collision_rayTrace(s, cam, p, hit)) {
			A(int, 0x87e8) = 0;
			A(int, 0x87e0) = 0;
			continue;
		}
		const float *rad = (const float *)(ac + 0x3e8);
		float q[3] = { f32(fsub_m(fld_m(&e[0]), rad)), f32(fadd_m(fld_m(&e[1]), rad)), e[2] };
		long double c0 = fadd_m(fmul_m(fld_m(&q[2]), &pr[8]) + fmul_m(fld_m(&q[1]), &pr[4]) + fmul_m(fld_m(&q[0]), &pr[0]), &pr[12]);
		long double c1 = fadd_m(fmul_m(fld_m(&q[0]), &pr[1]) + fmul_m(fld_m(&q[2]), &pr[9]) + fmul_m(fld_m(&q[1]), &pr[5]), &pr[13]);
		float c3 = f32(fadd_m(fmul_m(fld_m(&q[0]), &pr[3]) + fmul_m(fld_m(&q[2]), &pr[11]) + fmul_m(fld_m(&q[1]), &pr[7]), &pr[15]));
		to_screen(s, fdiv_m(c0, &c3), fdiv_m(c1, &c3), (float *)(ac + 0x87c8));
		A(float, 0x87d0) = f32(fld_m(&e[2]));
		long double x = fadd_m(fld_m(&e[0]), rad), y = fsub_m(fld_m(&e[1]), rad), z = fld_m(&e[2]);
		float c0f = f32(fadd_m(fmul_m(z, &pr[8]) + fmul_m(y, &pr[4]) + fmul_m(x, &pr[0]), &pr[12]));
		float c1f = f32(fadd_m(fmul_m(x, &pr[1]) + fmul_m(z, &pr[9]) + fmul_m(y, &pr[5]), &pr[13]));
		long double w3 = fadd_m(fmul_m(x, &pr[3]) + fmul_m(z, &pr[11]) + fmul_m(y, &pr[7]), &pr[15]);
		to_screen(s, fld_m(&c0f) / w3, fld_m(&c1f) / w3, (float *)(ac + 0x87d4));
		A(float, 0x87dc) = f32(fld_m(&e[2]));
		A(int, 0x484) = tag_narrow(ac, 0x4a940c);
		u8 *me = s + 0x1cd93a8 + GAME_VAR(int, s + 0x202e8d4) * 0x8888;
		if ((A(u32, 0x3f0) & 0x200) && A(int, 8) >= GAME_VAR(int, me + 8)) {
			A(int, 0x87e8) = 0;
			A(int, 0x87e0) = 1;
			continue;
		}
		long double cosv = -fld_m(&e[2]) / root(fmul_m(fld_m(&e[2]), &e[2]) + fmul_m(fld_m(&e[1]), &e[1]) + fmul_m(fld_m(&e[0]), &e[0]));
		A(float, 0x87e4) = f32(cosv);
		int heading = ftol(fld_m((const float *)(me + 4)));
		if (!(cosv > GAME_VAR(float, 0xa17f38 + ((heading % 3600 + 3600) % 3600) * 4))) {
			A(int, 0x87e8) = 0;
			A(int, 0x87e0) = 1;
			continue;
		}
		int weapon = GAME_VAR(int, me + 0x148);
		if (GAME_VAR(int, s + 0x202e8d4) >= 0 && A(int, 0x118) != GAME_VAR(int, me + 0x118) && weapon >= 0 &&
		    GAME_VAR(float, s + 0x14d48c4 + weapon * 0x2e18) > 0)
			A(float, 0x87e8) = f32(fadd_m(fld_m(&dt), (const float *)(ac + 0x87e8)));
		else
			A(int, 0x87e8) = 0;
		if (!tag_narrow(ac, 0x4a9414))
			A(u32, 0x87f0) = 0x40400000;
		A(int, 0x87e0) = 1;
	}
}
#undef K
#undef A
