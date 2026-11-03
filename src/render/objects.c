/* objects.c: the stage's map objects (animated scenery), actors and projectiles handed to the view volume, once
   per pass. Each list is walked up to its count, read again after every entry. */
#include "../game.h"
#include <string.h>
#define ST ((Stage *)s)   /* the stage (s in each function) by its fields (src/scene.fields) */

/* 0x490b30 (stage_drawObject): object i, unless it is hidden or has no model, when its bounding sphere (the model's radius
   plus stage->cullMargin) touches the box around stage->cameraPos: queued with its matrix and pose, culled per mesh */
void THISCALL (stage_drawObject)(Stage *stage, int i, void *view)
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

/* 0x490da0 (stage_drawObjects): every active object */
void THISCALL (stage_drawObjects)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->objectCount; i++)
		if (stage->objects[i].active == 1)
			stage_drawObject(stage, i, view);
}

/* 0x45e170 (stage_drawActors): every active actor's parts; pass is handed on (hud_pass gives 0 and 1, the match's view
   -1) */
void THISCALL (stage_drawActors)(Stage *stage, void *view, int pass)
{
	for (int i = 0; i < stage->actorCount; i++)
		if (stage->actors[i].active == 1)
			actor_updateAllParts(stage, i, view, pass);
}

/* 0x479af0 (stage_drawProjectiles): every active projectile */
void THISCALL (stage_drawProjectiles)(Stage *stage, void *view)
{
	for (int i = 0; i < stage->projectileCount; i++)
		if (stage->projectiles[i].active == 1)
			projectile_draw(stage, i, view);
}

#define K(address) ((const float *)RELOC(address))
#define F(type, obj, offset) GAME_VAR(type, (u8 *)RELOC(obj) + (offset))

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
	    !(clip[2] >= clip[3]) && collision_rayTrace(s, ST->cameraPos, p, hit) == 0) {
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
	u8 *obj = (u8 *)&ST->objects[i];
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
	if ((obj[0xc] & 1) && g_items3D == 1) {
		object_glow(s, obj, dt);
		if ((obj[0xc] & 1) && g_items3D == 1 && F(float, obj, 0x2a8) > *K(0x4a93e8)) {
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
			particle_spawn(s, (const void *)RELOC(flare));
		}
	}
	if (obj[0xc] & 8) {
		long double nearest = fld_m(K(0x4aa4a4));
		for (int k = 0; k < ST->actorCount; k++) {
			u8 *a = (u8 *)&ST->actors[k];
			if (F(int, a, 0x14c) != 1)
				continue;
			long double dx = fsub_m(fld_m((const float *)(RELOC(a) + 0x154)), (const float *)(obj + 0x58));
			long double dy = fsub_m(fld_m((const float *)(RELOC(a) + 0x158)), (const float *)(obj + 0x5c));
			long double dz = fsub_m(fld_m((const float *)(RELOC(a) + 0x15c)), (const float *)(obj + 0x60));
			long double d2 = (dz * dz + dy * dy) + dx * dx;
			float d2f = f32(d2);
			if (!(d2 >= nearest))
				nearest = fld_m(&d2f);
		}
		long double r = fmul_m((long double)F(int, obj, 0x10), K(0x4a93f4));
		if (F(float, obj, 0x29c) == 0 || F(float, obj, 0x29c) != F(float, obj, 0x29c)) {
			if (!(nearest >= r * r))
				anim_start(s, i, obj, ADDR(k_0_001f));
		} else if (F(u32, obj, 0x29c) == 0x3f800000 && nearest > r * r)
			anim_start(s, i, obj, ADDR(k_m0_001f));
	} else if (obj[0xc] & 0x10) {
		if (F(float, obj, 0x29c) == 0 || F(float, obj, 0x29c) != F(float, obj, 0x29c)) {
			if (fmul_m((long double)F(int, obj, 0x10), K(0x4a93f4)) > F(float, obj, 0x2c8)) {
				F(float, obj, 0x2c8) = f32(fadd_m(fld_m(&dt), (const float *)(obj + 0x2c8)));
				return;
			}
			F(int, obj, 0x2c8) = 0;
			anim_start(s, i, obj, ADDR(k_0_001f));
		} else if (F(u32, obj, 0x29c) == 0x3f800000)
			anim_start(s, i, obj, ADDR(k_m0_001f));
	}
}
#undef K
#undef F

#define K(address) ((const float *)RELOC(address))
#define A(type, offset) GAME_VAR(type, ac + (offset))
#define AC ((Player *)ac)   /* the same by its fields (src/scene.fields) */


/* the screen point (the view's width +0x20f3a24 and height +0x20f3a28) of clip x / w and y / w */
static void to_screen(u8 *s, long double qx, long double qy, float *out)
{
	out[0] = f32(fmul_m(fadd_m(qx, K(0x4a9424)) * (long double)ST->viewWidth, K(0x4a942c)));
	out[1] = f32(fmul_m((fld_m(K(0x4a9424)) - qy) * (long double)ST->viewHeight, K(0x4a942c)));
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
	float *cam = ST->cameraPos, *mv = (float *)(s + 0x20f39a0), *pr = (float *)(s + 0x20f3a34);
	memcpy(s + 0x20f3994, cam, 12);
	Mat4_copy(s + 0x20f39e0, mv);
	memcpy(cam, pos, 12);
	memcpy(ST->viewDir, dir, 12);
	memcpy(ST->viewUp, up, 12);
	const float *d = ST->viewDir, *u = ST->viewUp;
	glPushMatrix();
	glLoadIdentity();
	gluLookAt(cam[0], cam[1], cam[2], (double)fadd_m(fld_m(&d[0]), &cam[0]), (double)fadd_m(fld_m(&d[1]), &cam[1]),
	          (double)fadd_m(fld_m(&d[2]), &cam[2]), u[0], u[1], u[2]);
	glGetFloatv(0xba6, mv);
	glPopMatrix();
	GAME_VAR(float, s + 0x20f3a20) = fov;
	ST->viewWidth = w;
	ST->viewHeight = h;
	GAME_VAR(float, s + 0x20f3a2c) = nr;
	GAME_VAR(float, s + 0x20f3a30) = fr;
	glMatrixMode(0x1701);
	glPushMatrix();
	glLoadIdentity();
	gluPerspective(GAME_VAR(float, s + 0x20f3a20), (double)((long double)ST->viewWidth / ST->viewHeight),
	               GAME_VAR(float, s + 0x20f3a2c), GAME_VAR(float, s + 0x20f3a30));
	glGetFloatv(0xba7, pr);
	glPopMatrix();
	glMatrixMode(0x1700);
	Mat4_multiply((float *)(s + 0x20f3a74), pr, mv);
	if (!GAME_VAR(int, s + 0x2149308) || !GAME_VAR(int, s + 0x214930c))
		for (int k = 0; k < ST->objectCount; k++) {
			u8 *obj = (u8 *)&ST->objects[k];
			if (GAME_VAR(int, obj + 4) == 1 && (obj[0xc] & 1))
				object_glow(s, obj, dt);
		}
	for (int k = 0; k < ST->actorCount; k++) {
		u8 *ac = (u8 *)&ST->actors[k];
		if (AC->state != 1)
			continue;
		const float *p = AC->pos;
		float e[3], c[4];
		for (int r = 0; r < 3; r++)
			e[r] = f32(fadd_m(fmul_m(fld_m(&mv[8 + r]), &p[2]) + fmul_m(fld_m(&mv[4 + r]), &p[1]) + fmul_m(fld_m(&mv[r]), &p[0]), &mv[12 + r]));
		c[0] = f32(fadd_m(fmul_m(fld_m(&e[1]), &pr[4]) + fmul_m(fld_m(&e[2]), &pr[8]) + fmul_m(fld_m(&e[0]), &pr[0]), &pr[12]));
		for (int r = 1; r < 4; r++)
			c[r] = f32(fadd_m(fmul_m(fld_m(&e[0]), &pr[r]) + fmul_m(fld_m(&e[1]), &pr[4 + r]) + fmul_m(fld_m(&e[2]), &pr[8 + r]), &pr[12 + r]));
		to_screen(s, fdiv_m(fld_m(&c[0]), &c[3]), fdiv_m(fld_m(&c[1]), &c[3]), &AC->screenX);
		A(float, 0x87c4) = f32(fld_m(&e[2]));
		float nw = f32(-fld_m(&c[3]));
		u8 hit[12];
		if (k == ST->selectedActor || !(c[0] > nw) || !(c[1] > nw) || !(c[2] > nw) || c[0] >= c[3] || c[1] >= c[3] ||
		    c[2] >= c[3] || collision_rayTrace(s, cam, p, hit)) {
			AC->lockedOn = 0.0f;
			AC->onScreen = 0;
			continue;
		}
		const float *rad = &AC->radius;
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
		AC->detail = tag_narrow(ac, OBJ(k_30f));
		u8 *me = (u8 *)&ST->actors[ST->playerActor];
		Player *act = (Player *)me;
		if ((((u32)AC->timerFlags) & 0x200) && A(int, 8) >= GAME_VAR(int, me + 8)) {
			AC->lockedOn = 0.0f;
			AC->onScreen = 1;
			continue;
		}
		long double cosv = -fld_m(&e[2]) / x87_fsqrt(fmul_m(fld_m(&e[2]), &e[2]) + fmul_m(fld_m(&e[1]), &e[1]) + fmul_m(fld_m(&e[0]), &e[0]));
		A(float, 0x87e4) = f32(cosv);
		int heading = ftol(fld_m((const float *)(me + 4)));
		if (!(cosv > GAME_VAR(float, OBJ(g_cosTable) + ((heading % 3600 + 3600) % 3600) * 4))) {
			AC->lockedOn = 0.0f;
			AC->onScreen = 1;
			continue;
		}
		int weapon = act->actorType;
		if (ST->playerActor >= 0 && AC->team != act->team && weapon >= 0 &&
		    GAME_VAR(float, s + 0x14d48c4 + weapon * 0x2e18) > 0)
			AC->lockedOn = f32(fadd_m(fld_m(&dt), &AC->lockedOn));
		else
			AC->lockedOn = 0.0f;
		if (!tag_narrow(ac, OBJ(k_40f)))
			AC->labelFade = 3.0f;
		AC->onScreen = 1;
	}
}
#undef K
#undef A
#undef AC

/* ---- 0x476890: a projectile drawn ---- */

#define K(address) ((const float *)RELOC(address))
#define P(type, offset) GAME_VAR(type, p + (offset))
#define PR ((Projectile *)p)   /* the same by its fields (src/scene.fields) */
#define TEX(k) GAME_VAR(int, s + 0x9ccfd4 + (k) * 4)   /* the effect textures */

static u8 clamp255(int a) { return a < 0 ? 0 : a > 255 ? 255 : (u8)a; }

/* a camera-facing quad (viewVolume_addBillboard): texture corners uv (two pairs), offsets ab (two pairs), its colour +0x78 */
static void quad(void *vv, int tex, const float *uv, float dz, u8 *p, const float *ab, const float *at, int kind)
{
	viewVolume_addBillboard(vv, tex, uv, uv + 2, dz, p + 0x78, ab, ab + 2, at, kind, 1);
}

/* offsets +-h, each corner rounded */
static void square(float *ab, long double h)
{
	ab[0] = ab[1] = (float)-h;
	ab[2] = ab[3] = (float)h;
}

/* one of the effect shapes about the projectile's matrix (+0x2c) */
static void shape(void *vv, u8 *p, void *model, const void *colour, int cull)
{
	ViewVolume_projectObject(vv, model, 0, PR->matrix, 0, colour, cull, -1, 0);
}

static const float k_glowUV[4] = { 0.5f, 0.125f, 0.625f, 0.25f }, k_coreUV[4] = { 0.875f, 0.125f, 1.0f, 0.25f };

/* the glow: faded by a squared (a = 1 - t), +-big, or +-small for the viewing actor's own (+0x202e8d8) */
static void glow(u8 *s, u8 *p, void *vv, long double a, float big, float small)
{
	float ab[4];
	P(u8, 0x7b) = clamp255(ftol(fmul_m(a * a, K(0x4aa264))));   /* 128 */
	square(ab, PR->owner == ST->selectedActor ? small : big);
	quad(vv, TEX(0), k_glowUV, 0, p, ab, PR->pos, 2);
}

/* the glow sized by the projectile's radius (+0x80) plus add, halved for the viewing actor's own */
static void sized_glow(u8 *s, u8 *p, void *vv, long double a, const float *add)
{
	float ab[4];
	P(u8, 0x7b) = clamp255(ftol(fmul_m(a * a, K(0x4aa264))));
	long double size = fadd_m(fld_m(&PR->baseSize), add);
	square(ab, size);
	if (PR->owner == ST->selectedActor) {
		ab[0] = f32(fmul_m(fld_m(&ab[0]), K(0x4a942c)));
		ab[1] = f32(fmul_m(fld_m(&ab[1]), K(0x4a942c)));
		ab[2] = ab[3] = (float)fmul_m(size, K(0x4a942c));
	}
	quad(vv, TEX(0), k_glowUV, 0, p, ab, PR->pos, 2);
}

/* a bright core (+-h, faded by (1 - t) squared) under the glow (faded the same, rounded) */
static void core(u8 *s, u8 *p, void *vv, const float *t, float h, float big, float small)
{
	float ab[4];
	long double a = fsub_m(fld_m(K(0x4a9424)), t);
	float a_rounded = (float)a;
	P(u8, 0x7b) = clamp255(ftol(fmul_m(a * a, K(0x4a9744))));   /* 255 */
	square(ab, h);
	quad(vv, TEX(0), k_coreUV, 0, p, ab, PR->pos, 2);
	glow(s, p, vv, fld_m(&a_rounded), big, small);
}

/* a flare: the core sized by the fade squared times the radius plus 200 (dz 200), then the radius glow */
static void flare(u8 *s, u8 *p, void *vv, float *t)
{
	float ab[4];
	long double a = fsub_m(fld_m(K(0x4a9424)), t);
	float a_rounded = (float)a;
	long double a2 = a * a;
	P(u8, 0x7b) = clamp255(ftol(fmul_m(a2, K(0x4aa260))));   /* 256 */
	*t = f32(fadd_m(fld_m(&PR->baseSize), K(0x4a93f0)));   /* (the original reuses t's slot) */
	square(ab, fmul_m(a2, t));
	quad(vv, TEX(0), k_coreUV, 200.0f, p, ab, PR->pos, 2);
	sized_glow(s, p, vv, fld_m(&a_rounded), K(0x4a93d0));
}

/* a bolt: one of 8 frames by t on the strip at 0.9375, risen 100 t, +-100 (or the radius + 100), then the radius
   glow (+2) */
static void bolt(u8 *s, u8 *p, void *vv, const float *t, int sized)
{
	float uv[4], ab[4], at[3];
	int n = ftol(fmul_m(fld_m(t), K(0x4a94cc)));
	if (n > 7)
		n = 7;
	uv[0] = f32(fmul_m((long double)(n << 4), K(0x4a957c)));
	uv[1] = 0.9375f;
	uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4a958c)));
	uv[3] = 1.0f;
	P(u8, 0x7b) = 0xff;
	memcpy(at, PR->pos, 12);
	at[1] = f32(fadd_m(fmul_m(fld_m(t), K(0x4a93f4)), &at[1]));
	if (sized)
		square(ab, fadd_m(fld_m(&PR->baseSize), K(0x4a93f4)));
	else
		square(ab, 100.0f);
	quad(vv, TEX(0), uv, 100.0f, p, ab, at, 2);
	sized_glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), t), K(0x4a93fc));
}

/* one of 16 frames (4 x 4, a quarter of the texture each) by t */
static void frame16(float *uv, const float *t)
{
	int n = ftol(fmul_m(fld_m(t), K(0x4aa43c)));
	if (n > 15)
		n = 15;
	uv[0] = f32(fmul_m((long double)((n % 4) << 6), K(0x4a957c)));
	uv[1] = f32(fmul_m((long double)((n / 4) << 6), K(0x4a957c)));
	uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4a941c)));
	uv[3] = f32(fadd_m(fld_m(&uv[1]), K(0x4a941c)));
}

/* one of 16 frames (8 x 2 from the fourth row) by t, turned by the projectile's index (i % 4) */
static void frame16_turned(float *uv, const float *t, int i)
{
	int n = ftol(fmul_m(fld_m(t), K(0x4aa43c)));
	if (n > 15)
		n = 15;
	long double u = fmul_m((long double)((n % 8) << 5), K(0x4a957c));
	float v = f32(fmul_m((long double)((n / 8 + 3) << 5), K(0x4a957c)));
	float u1 = f32(fadd_m(u, K(0x4aa274))), v1 = f32(fadd_m(fld_m(&v), K(0x4aa274)));
	switch (i % 4) {
	case 0: uv[0] = (float)u; uv[1] = v; uv[2] = u1; uv[3] = v1; break;
	case 1: uv[0] = (float)u; uv[1] = v1; uv[2] = u1; uv[3] = v; break;
	case 2: uv[0] = u1; uv[1] = v1; uv[2] = (float)u; uv[3] = v; break;
	case 3: uv[0] = u1; uv[1] = v; uv[2] = (float)u; uv[3] = v1; break;
	}
}

/* smoke (texture 5, the row v0..v1): ten puffs along the projectile's backward direction (its matrix's rows by the
   world's 0xa0e7c8 * -50, scaled by +0x1c), each 1.1 times the last and farther out, fading by +0x20 */
static void smoke(u8 *s, u8 *p, void *vv, int i, float v0, float v1)
{
	int tex = TEX(5), phase = i % 8;
	long double gx = fmul_m(fld_m((&g_vecUnitZXyz[0])), K(0x4a9558)), gy = fmul_m(fld_m((&g_vecUnitZXyz[1])), K(0x4a9558)),
	            gz = fmul_m(fld_m((&g_vecUnitZXyz[2])), K(0x4a9558));
	float v[3], at[3], uv[4], ab[4];
	v[0] = f32((fmul_m(gz, &PR->matrix[8]) + fmul_m(gy, &PR->matrix[4])) + fmul_m(gx, &PR->matrix[0]));
	v[1] = f32((fmul_m(gz, &PR->matrix[9]) + fmul_m(gy, &PR->matrix[5])) + fmul_m(gx, &PR->matrix[1]));
	long double v2 = (fmul_m(gz, &PR->matrix[10]) + fmul_m(gy, &PR->matrix[6])) + fmul_m(gx, &PR->matrix[2]);
	long double h = fld_m(&PR->target[0]);
	v[0] = f32(fmul_m(h, &v[0]));
	v[1] = f32(fmul_m(h, &v[1]));
	v[2] = f32(v2 * h);
	long double size = x87_fsqrt((fmul_m(fld_m(&v[0]), &v[0]) + fmul_m(fld_m(&v[2]), &v[2])) + fmul_m(fld_m(&v[1]), &v[1]));
	float last = (float)size;
	for (int k = 0; k < 3; k++)
		at[k] = f32(fadd_m(fld_m(&v[k]), &PR->pos[k]));
	for (int k = 0; k < 10; k++) {
		uv[0] = f32(fmul_m((long double)(((k + phase) % 8) << 5), K(0x4a957c)));
		uv[1] = v0;
		uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4aa274)));
		uv[3] = v1;
		P(u8, 0x7b) = (u8)ftol(fmul_m(fmul_m(fsubr_m(fmul_m((long double)k, K(0x4a955c)), K(0x4a9424)), &PR->target[1]), K(0x4a9744)));
		square(ab, size);
		quad(vv, tex, uv, 0, p, ab, at, 2);
		for (int j = 0; j < 3; j++)
			v[j] = f32(fmul_m(fld_m(&v[j]), K(0x4aa438)));   /* 1.1 */
		size = fmul_m(fld_m(&last), K(0x4aa438));
		last = (float)size;
		long double d0 = fmul_m(fld_m(&v[0]), K(0x4a94fc));   /* 0.3 */
		float d1 = f32(fmul_m(fld_m(&v[1]), K(0x4a94fc))), d2 = f32(fmul_m(fld_m(&v[2]), K(0x4a94fc)));
		at[0] = f32(fadd_m(d0, &at[0]));
		at[1] = f32(fadd_m(fld_m(&d1), &at[1]));
		at[2] = f32(fadd_m(fld_m(&at[2]), &d2));
	}
}

/* 0x476890 (thiscall on the scene): projectile i (0x12c-byte records from +0x20a99c0: frame +0, type +8, owner
   +0xc, position +0x10, matrix +0x2c, timer +0x6c of +0x70, colour +0x78 with its alpha +0x7b, radius +0x80).
   Below type 50 it must lie in the box of +0xa08 about the camera (+0x20f3970). By type: billboards from the effect
   textures (+0x9ccfd4..) by the fraction t of the timer gone, the effect shapes (+0x20f2e74..; the owner's part
   shapes for debris), a trail (types 40-49: triangles through ViewVolume_transformObject) or a quad (type 50) */
void THISCALL (projectile_draw)(u8 *s, int i, void *vv)
{
	u8 *p = (u8 *)&ST->projectiles[i];
	const float *at = PR->pos, *cam = ST->cameraPos, *range = &ST->cullMargin;
	int type = PR->kind;
	float uv[4], ab[4], t;
	if (type < 50) {
		for (int k = 0; k < 3; k++)
			if (fsub_m(fld_m(&cam[k]), range) > at[k])
				return;
		for (int k = 0; k < 3; k++)
			if (!(fadd_m(fld_m(range), &cam[k]) >= at[k]))
				return;
	}
	if (PR->life > 0)
		t = f32(fdiv_m(fld_m(&PR->drawAge), &PR->life));
	else
		t = 0;
	switch (type) {
	case 0: {   /* one of 8 frames by the frame count, growing and fading */
		uv[0] = f32(fmul_m((long double)((PR->id % 8) << 5), K(0x4a957c)));
		uv[1] = 0;
		uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4aa274)));
		uv[3] = 0.125f;
		int a = ftol(fmul_m(fsub_m(fld_m(K(0x4a9424)), &t), K(0x4a9744)));
		P(u8, 0x7b) = (u8)(a > 0xff ? 0xff : a);
		square(ab, fmul_m(fadd_m(fld_m(&t), K(0x4a9424)), K(0x4a93f4)));
		quad(vv, TEX(0), uv, 100.0f, p, ab, at, 2);
		return;
	}
	case 1:
	case 8: {   /* one of 8 frames by t; 1 rising 300 a second, 8 on the second strip (its own texture with an owner) */
		int n = ftol(fmul_m(fld_m(&t), K(0x4a94cc)));
		if (n > 7)
			n = 7;
		int tex = type == 8 && PR->owner != 0 ? TEX(4) : TEX(0);
		float pos[3];
		uv[0] = f32(fmul_m((long double)(n << 5), K(0x4a957c)));
		uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4aa274)));
		memcpy(pos, at, 12);
		if (type == 1) {
			uv[1] = 0;
			uv[3] = 0.125f;
			pos[1] = f32(fadd_m(fmul_m(fld_m(&PR->drawAge), K(0x4aa440)), &pos[1]));
		} else {
			uv[1] = 0.625f;
			uv[3] = 0.75f;
		}
		square(ab, 300.0f);
		quad(vv, tex, uv, 300.0f, p, ab, type == 1 ? pos : at, 2);
		return;
	}
	case 2:
		if (!(PR->drawAge >= *K(0x4a9420)))
			glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), 600.0f, 300.0f);
		frame16_turned(uv, &t, i);
		square(ab, 300.0f);
		quad(vv, TEX(0), uv, 300.0f, p, ab, at, 2);
		return;
	case 3:
		if (!(PR->drawAge >= *K(0x4a9420)))
			glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), 1600.0f, 800.0f);
		frame16(uv, &t);
		square(ab, 800.0f);
		quad(vv, TEX(2), uv, 800.0f, p, ab, at, 2);
		return;
	case 4:   /* a marker the owner's colour index shows through */
		ab[0] = ab[1] = (float)-fld_m(&PR->target[0]);
		ab[2] = ab[3] = (float)fld_m(&PR->target[0]);
		P(u8, 0x7b) = P(u8, 0xc);
		uv[0] = uv[1] = 0.75f;
		uv[2] = uv[3] = 1.0f;
		quad(vv, TEX(0), uv, 0, p, ab, at, 3);
		return;
	case 5:
		smoke(s, p, vv, i, 0, 0.125f);
		return;
	case 6:
		smoke(s, p, vv, i, 0.125f, 0.25f);
		return;
	case 7:
		smoke(s, p, vv, i, 0.25f, 0.375f);
		return;
	case 9: {   /* debris: one of the owner's part shapes (the part by i % 5) */
		static const u32 k_parts[4] = { 0x1561ea0, 0x1569dec, 0x1571d38, 0x1581984 };
		int part = i % 5;
		u8 *cache = s + (part >= 0 && part < 4 ? k_parts[part] : 0x15915d0) + PR->owner * 0x47fd2;
		shape(vv, p, GAME_VAR(u8 *, cache + 0x11c) + i % GAME_VAR(int, cache + 0x120) * 0x4c, 0, 1);
		return;
	}
	case 10:
	case 11:
	case 18:
		shape(vv, p, GAME_VAR(void *, s + (type == 10 ? 0x20f2e74 : type == 11 ? 0x20f2e7c : 0x20f2e80)), 0, 1);
		glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), 600.0f, 300.0f);
		return;
	case 12:
		core(s, p, vv, &t, 50.0f, 200.0f, 100.0f);
		return;
	case 13:
	case 14:
		core(s, p, vv, &t, 100.0f, 600.0f, 300.0f);
		return;
	case 15:
	case 16: {   /* a glow and a rising flame (8 frames on the strip at 0.9375) */
		glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), 600.0f, 300.0f);
		int n = ftol(fmul_m(fld_m(&t), K(0x4a94cc)));
		if (n > 7)
			n = 7;
		float pos[3];
		memcpy(pos, at, 12);
		uv[0] = f32(fmul_m((long double)(n << 4), K(0x4a957c)));
		uv[1] = 0.9375f;
		uv[2] = f32(fadd_m(fld_m(&uv[0]), K(0x4a958c)));
		uv[3] = 1.0f;
		pos[1] = f32(fadd_m(fmul_m(fld_m(&PR->drawAge), K(0x4a93f4)), &pos[1]));
		square(ab, 100.0f);
		quad(vv, TEX(0), uv, 0, p, ab, pos, 2);
		return;
	}
	case 20:
	case 21:
		if (PR->owner != ST->selectedActor)
			shape(vv, p, GAME_VAR(void *, s + (type == 20 ? 0x20f2e78 : 0x20f2e84)), p + 0x78, 0);
		return;
	case 22:
		if (PR->owner == 1)
			return;
		square(ab, fadd_m(fld_m(&PR->baseSize), K(0x4a93f4)));
		uv[0] = 0.875f;
		uv[1] = 0.25f;
		uv[2] = 1.0f;
		uv[3] = 0.375f;
		quad(vv, TEX(0), uv, 0, p, ab, at, 2);
		return;
	case 24: {
		long double a = fsub_m(fld_m(K(0x4a9424)), &t);
		P(u8, 0x7b) = clamp255(ftol(fmul_m(a * a, K(0x4aa260))));
		shape(vv, p, GAME_VAR(void *, s + 0x20f2e88), p + 0x78, 0);
		return;
	}
	case 25:
		if (PR->owner == 1)
			return;
		shape(vv, p, GAME_VAR(void *, s + 0x20f2e8c), 0, 1);
		square(ab, 500.0f);
		quad(vv, TEX(0), k_glowUV, 0, p, ab, at, 2);
		return;
	case 26:
		if (PR->owner == 1)
			return;
		shape(vv, p, GAME_VAR(void *, s + 0x20f2e90), 0, 1);
		sized_glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), K(0x4a9450));
		return;
	case 30:
		bolt(s, p, vv, &t, 0);
		return;
	case 31:
	case 39:
		bolt(s, p, vv, &t, 1);
		return;
	case 32:
	case 33:
	case 34:
	case 37:
	case 38:
		flare(s, p, vv, &t);
		return;
	case 35:   /* an explosion: 16 frames, the radius + 2000, then the radius glow (+4000) */
		frame16(uv, &t);
		P(u8, 0x7b) = 0xff;
		square(ab, fadd_m(fld_m(&PR->baseSize), K(0x4a9554)));
		quad(vv, TEX(2), uv, 2000.0f, p, ab, at, 2);
		sized_glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), K(0x4aa434));
		return;
	case 36:
		frame16_turned(uv, &t, i);
		P(u8, 0x7b) = 0xff;
		square(ab, 1000.0f);
		quad(vv, TEX(0), uv, 1000.0f, p, ab, at, 2);
		sized_glow(s, p, vv, fsub_m(fld_m(K(0x4a9424)), &t), K(0x4a9554));
		return;
	case 40: case 41: case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: {
		/* a trail's triangle (texture 8), its three colours fading over its last second */
		int tex = TEX(8);
		if (PR->drawAge > 1.0f)
			P(u8, 0xd7) = P(u8, 0xdb) = P(u8, 0xdf) = clamp255(ftol(fmul_m(fsub_m(fld_m(K(0x4a93fc)), &PR->drawAge), K(0x4aa260))));
		ViewVolume_transformObject(vv, tex, (const u32 *)(p + 0xb4), (const u32 *)(p + 0xd4), &PR->fade,
		                           (*(const float * *)&PR->matrixFrom), 1, 1);
		return;
	}
	case 50:
		viewVolume_addQuad(vv, P(int, 0xe4), (const u32 *)(p + 0xe8), (const u32 *)(p + 0xf0), (const u32 *)(p + 0xf8), (const float *)(p + 0xfc), 2, 1);
		return;
	}
}
#undef K
#undef P
#undef PR
#undef TEX
