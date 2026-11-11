/* draw_tags.h: what the drawing is, told to the 64-bit build's recorder (standalone/glrec64.c) for the Godot remaster:
   a tag op in the stream before the drawing it names, and once per view volume drawn the camera (its projection and
   view matrices), once per frame the stage's lights. The world is queued into the view volume by kind (the sky, the ground, map objects, actors ...) and
   drawn by material, so each queued record keeps the kind it was queued under (view_volume.c) and the draw tags each
   one. Only the 64-bit build (AXIS_64): elsewhere these are nothing, the game's code as it was. */
#pragma once

enum {
	DRAWTAG_OTHER = 0,       /* menus, loading screens, anything untagged */
	DRAWTAG_SKY = 1,         /* the sky sphere and its cloud layers (sky_draw) */
	DRAWTAG_GROUND = 2,      /* the map's ground layers (ground_buildDrawLists) */
	DRAWTAG_OBJECT = 3,      /* the map's objects: its buildings and scenery (stage_drawObjects) */
	DRAWTAG_ACTOR = 4,       /* the mechs (stage_drawActors, pass 0) */
	DRAWTAG_ACTOR_VIEW = 5,  /* the actors' pass over a cleared depth buffer (stage_drawActors, pass 1) */
	DRAWTAG_BULLET = 6,      /* bullets and their trails (stage_drawBullets) */
	DRAWTAG_PARTICLE = 7,    /* particles: explosions, smoke, sparks (stage_drawParticles) */
	DRAWTAG_ITEM = 8,        /* the items: power-ups, ammunition (stage_drawItems) */
	DRAWTAG_MARKER = 9,      /* debug markers (the map's lights, the mech test's grid) */
	DRAWTAG_HUD = 10,        /* the in-match HUD and overlays, after the 3D scene */
};

#ifdef AXIS_64
extern int g_drawSource;                                       /* the kind records are queued under now */
void glrec64_tag(int kind);                                    /* a tag op (when it changes) */
void glrec64_camera(const float *projection, const float *view);
void glrec64_lights(int pool, const void *records, int count);   /* a light pool's records in use (Factor, 0x2c bytes) */
void draw_particleGlows(Stage *stage);
void glrec64_depthMask(int on);   /* depth writes on / off (the game never sets them: view_volume.c's billboards) */   /* (objects.c) pool 3: a glow at each booster puff, muzzle flash and shot in flight */
#define DRAW_SOURCE(k) (g_drawSource = (k))
/* the stage's light pools, once per frame before the world: 0 the map's (from the map file), 1 the dynamic ones (the
   actors' glow, the particles that give light: refilled each frame), 2 the actors' own (ambient and from above) */
#define DRAW_LIGHTS(st) (glrec64_lights(0, (st)->mapLights.records, (st)->mapLights.count), \
                         glrec64_lights(1, (st)->dynamicLights.records, (st)->dynamicLights.count), \
                         glrec64_lights(2, (st)->actorLights.records, (st)->actorLights.count), \
                         draw_particleGlows(st))
#define DRAW_TAG(k) glrec64_tag(k)
#define DRAW_CAMERA(p, v) glrec64_camera(p, v)
#define DRAW_DEPTHMASK(on) glrec64_depthMask(on)
#else
#define DRAW_SOURCE(k) ((void)0)
#define DRAW_TAG(k) ((void)0)
#define DRAW_CAMERA(p, v) ((void)0)
#define DRAW_LIGHTS(st) ((void)0)
#define DRAW_DEPTHMASK(on) ((void)0)
#endif
