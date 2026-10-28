/* game.h: the parts of AxisGL.exe the rebuilt code uses by their original address: functions (called through their
   address, see axis.h), globals and imports. Grows as rebuilds need more; a name defined here can still have a
   rebuild of its own elsewhere in src (that file defines it as "void (name)(...)"). */
#ifndef GAME_H
#define GAME_H
#include "axis.h"
#include "scene.h"

/* ---- OpenGL, through the import table ---- */
#define GL_TEXTURE_2D 0x0de1
#define glColor4f(r, g, b, a) IMPORT(0x4a9228, void, float, float, float, float)(r, g, b, a)
/* a colour kept in memory, passed on bit for bit (the original copies the four values without the FPU, which
   would turn a signalling NaN into a quiet one) */
#define glColor4f_stored(c) IMPORT(0x4a9228, void, u32, u32, u32, u32)(((const u32 *)(c))[0], ((const u32 *)(c))[1], \
	((const u32 *)(c))[2], ((const u32 *)(c))[3])
#define glEnable(cap) IMPORT(0x4a9224, void, u32)(cap)
#define GL_FOG 0x0b60
#define GL_DEPTH_BUFFER_BIT 0x0100
#define GL_COLOR_BUFFER_BIT 0x4000
#define glClear(mask) IMPORT(0x4a91e8, void, u32)(mask)
#define glClearDepth(depth) IMPORT(0x4a91dc, void, double)(depth)
/* a clear colour kept in memory (three floats), passed on bit for bit, alpha 1 */
#define glClearColor_stored(c) IMPORT(0x4a91e0, void, u32, u32, u32, u32)((c)[0], (c)[1], (c)[2], 0x3f800000u)
#define GL_QUADS 7
#define GL_LINE_LOOP 2
#define GL_QUAD_STRIP 8
#define glBegin(mode) IMPORT(0x4a921c, void, u32)(mode)
#define glEnd() IMPORT(0x4a9220, void, void)()
#define glTexCoord2f(s, t) IMPORT(0x4a920c, void, float, float)(s, t)
#define glTexCoord2d(s, t) IMPORT(0x4a9208, void, double, double)(s, t)
#define glBindTexture(target, id) IMPORT(0x4a9264, void, u32, u32)(target, id)
#define glVertex2i(x, y) IMPORT(0x4a91f4, void, int, int)(x, y)
#define glDisable(cap) IMPORT(0x4a922c, void, u32)(cap)
#define GL_FOG_DENSITY 0x0b62
#define GL_FOG_START 0x0b63
#define GL_FOG_END 0x0b64
#define GL_FOG_MODE 0x0b65
#define GL_FOG_COLOR 0x0b66
#define GL_FOG_HINT 0x0c54
#define GL_LINEAR 0x2601
#define GL_DONT_CARE 0x1100
#define glFogi(pname, v) IMPORT(0x4a9288, void, u32, int)(pname, v)
#define glFogfv(pname, v) IMPORT(0x4a9284, void, u32, const void *)(pname, v)
/* a float kept in memory, passed on bit for bit */
#define glFogf_stored(pname, v) IMPORT(0x4a9280, void, u32, u32)(pname, v)
#define glHint(target, mode) IMPORT(0x4a924c, void, u32, u32)(target, mode)
#define glPushMatrix() IMPORT(0x4a9204, void, void)()
#define glLoadIdentity() IMPORT(0x4a9218, void, void)()
#define glGetFloatv(pname, out) IMPORT(0x4a9270, void, u32, float *)(pname, out)
#define glLoadMatrixf(m) IMPORT(0x4a926c, void, const float *)(m)
#define glVertex3fv(v) IMPORT(0x4a9290, void, const float *)(v)
/* a point kept in memory (three floats), passed on bit for bit */
#define glVertex3f_stored(v) IMPORT(0x4a9210, void, u32, u32, u32)(((const u32 *)(v))[0], ((const u32 *)(v))[1], ((const u32 *)(v))[2])
/* colours and translations given as float bits (see BITS) */
#define glColor4f_bits(r, g, b, a) IMPORT(0x4a9228, void, u32, u32, u32, u32)(r, g, b, a)
#define glTranslatef_bits(x, y, z) IMPORT(0x4a9214, void, u32, u32, u32)(x, y, z)
/* GLU, through the game's jump to its import */
#define gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz) ((void (STDCALL *)(double, double, double, double, double, double, double, \
	double, double))0x4509d2)(ex, ey, ez, cx, cy, cz, ux, uy, uz)
#define glPopMatrix() IMPORT(0x4a9258, void, void)()
/* a point kept in memory (three floats), passed on bit for bit */
#define glTranslatef_stored(v) IMPORT(0x4a9214, void, u32, u32, u32)(((const u32 *)(v))[0], ((const u32 *)(v))[1], ((const u32 *)(v))[2])
#define glRotatef(angle, x, y, z) IMPORT(0x4a91f8, void, float, float, float, float)(angle, x, y, z)

/* ---- C runtime of the game ---- */
#define sprintf(...) GAME_CDECL(0x49e9dd, int, char *, const char *, ...)(__VA_ARGS__)
#define vsprintf(out, format, args) GAME_CDECL(0x49ed2e, int, char *, const char *, va_list)(out, format, args)

/* ---- screen ---- */
#define gfx_setProjection2D3D(mode) GAME_CDECL(0x41ef90, void, int)(mode)   /* 1: 3D, 2: the menus' 2D */
/* a vertex in the menus' 640 x 480 units (the patch DLL replaces this function: kept original) */
#define menu_vertex(x, y) GAME_CDECL(0x41ef60, void, int, int)(x, y)
/* the menus' 3D camera (gluLookAt) for models and the tunnel */
#define gfx_setMenuCamera() GAME_CDECL(0x41f050, void, void)()
/* glRotatef about x, then y, then z (degrees, as float bits) */
#define gfx_rotateXYZ(x, y, z) GAME_CDECL(0x41ef20, void, u32, u32, u32)(x, y, z)
/* the 3D background (menu_tunnel.c) */
#define g_texturesOff GAME_VAR(int, 0x9da494)        /* (by use) set: the menus' 3D background is drawn untextured (left out) */
#define g_tunnelTexture GAME_VAR(int, 0x4e186c)
#define g_flareTextures ((const int *)0x9da470)     /* flare k's texture is g_flareTextures[-k] */
#define g_cageTexture GAME_VAR(int, 0x76d36c)
#define g_pulse GAME_VAR(float, 0x4b06fc)            /* the bands' colour pulse, 0.05 .. 0.95 */
#define g_pulseStep GAME_VAR(float, 0x4b0700)
#define g_flareSizeB GAME_VAR(float, 0x4b0704)       /* flare 3's half-size, 10 .. 48 */
#define g_flareSizeA GAME_VAR(float, 0x4b0708)       /* flare 2's */
#define g_flareStepB GAME_VAR(float, 0x4b070c)
#define g_flareStepA GAME_VAR(float, 0x4b0710)
/* ---- textures ---- */
typedef struct { u32 count; void *managers[1]; } TextureSets;   /* a texture id names managers[id / 512], slot id % 512 */
#define g_textures GAME_VAR(TextureSets *, 0xa0e010)
#define tex_bind(manager, slot) GAME_THISCALL(0x4566c0, void, void *, int)(manager, slot)
#define gfx_getWidth() GAME_CDECL(0x4685b0, int, void)()
#define gfx_getHeight() GAME_CDECL(0x4685c0, int, void)()
#define gfx_fillRect(x0, y0, x1, y1) GAME_CDECL(0x46bd60, void, int, int, int, int)(x0, y0, x1, y1)

/* ---- text ---- */
#define text_setColor(r, g, b, a) GAME_CDECL(0x44ad30, void, float, float, float, float)(r, g, b, a)
#define text_draw5(x, y, s) GAME_CDECL(0x403170, void, int, int, const char *)(x, y, s)
#define text_draw8(x, y, s) GAME_CDECL(0x402620, void, int, int, const char *)(x, y, s)
#define text_draw16(x, y, s) GAME_CDECL(0x4028b0, void, int, int, const char *)(x, y, s)
#define text_draw32(x, y, s) GAME_CDECL(0x402c90, void, int, int, const char *)(x, y, s)
/* the box passes: text centred between x0 and x1 */
#define hud_403210(x0, y, x1, s) GAME_CDECL(0x403210, void, int, int, int, const char *)(x0, y, x1, s)
#define text_draw8b(x0, y, x1, s) GAME_CDECL(0x402740, void, int, int, int, const char *)(x0, y, x1, s)
#define text_drawBox16(x0, y, x1, s) GAME_CDECL(0x4029d0, void, int, int, int, const char *)(x0, y, x1, s)
#define hud_402db0(x0, y, x1, s) GAME_CDECL(0x402db0, void, int, int, int, const char *)(x0, y, x1, s)
#define hud_44ae10(x0, y, x1, s, size) GAME_CDECL(0x44ae10, void, int, int, int, const char *, int)(x0, y, x1, s, size)
#define text_drawSized(x, y, s, size) GAME_CDECL(0x44ad60, void, int, int, const char *, int)(x, y, s, size)

/* ---- HUD ---- */
#define hud_4950a0(x0, y0, x1, y1) GAME_CDECL(0x4950a0, void, int, int, int, int)(x0, y0, x1, y1)
#define hud_46bd00(x0, y0, x1, y1) GAME_CDECL(0x46bd00, void, int, int, int, int)(x0, y0, x1, y1)   /* a rectangle's outline */
/* a team's slot in teamScores (this_get_0x2342381_463780) and which side of the box it is on (FUN_00463740) */
#define scene_teamSlot(scene, team) GAME_THISCALL(0x463780, int, Scene *, int)(scene, team)
#define scene_teamSide(scene, team) GAME_THISCALL(0x463740, int, Scene *, int)(scene, team)   /* the team's slot, given one if new */
#define scene_findTeam(scene, team) GAME_THISCALL(0x463710, int, Scene *, int)(scene, team)   /* the team's slot or -1 */
#define hud_drawNameIcon(scene, emblem, x, y) GAME_THISCALL(0x4922c0, void, Scene *, int, int, int)(scene, emblem, x, y)
#define hud_drawLeaderIcon(scene, player, x, y) GAME_THISCALL(0x4924d0, void, Scene *, int, int, int)(scene, player, x, y)
#define replay_drawIcon(scene, x, y, icon) GAME_THISCALL(0x496820, void, Scene *, int, int, int)(scene, x, y, icon)

/* ---- main loop and match ---- */
#define main_loop() GAME_CDECL(0x420280, void, void)()
#define game_postMatch() GAME_CDECL(0x420100, void, void)()
#define music_4572b0() GAME_CDECL(0x4572b0, void, void)()
#define gfx_swapBuffers() GAME_CDECL(0x4685d0, void, void)()
#define main_462050(scene) GAME_THISCALL(0x462050, int, Scene *)(scene)
#define game_processLoadingMode(scene) GAME_THISCALL(0x468750, int, Scene *)(scene)
#define match_inputState2(scene) GAME_THISCALL(0x48b200, int, Scene *)(scene)
#define match_inputState3(scene) GAME_THISCALL(0x48a370, int, Scene *)(scene)
#define replay_frame(scene) GAME_THISCALL(0x487f00, int, Scene *)(scene)

/* ---- input ---- */
#define input_reacquireKeyboard() GAME_CDECL(0x4012c0, void, void)()
#define input_updateMenuCursor() GAME_CDECL(0x445c60, void, void)()
#define input_justPressed(key) GAME_CDECL(0x401600, int, int)(key)

/* ---- menus: the screens' frames and key handlers ---- */
#define menu_frame() GAME_CDECL(0x41fa40, void, void)()
#define menu_enterState() GAME_CDECL(0x41f970, void, void)()
#define menu_drawBackground() GAME_CDECL(0x441740, void, void)()
#define menu_drawFrame(x0, y0, x1, y1) GAME_CDECL(0x428c30, void, int, int, int, int)(x0, y0, x1, y1)
/* textured quads (menu_quads.c): buttons from the bound sheet (lit == 1: the lit cell), whole textures, panel ornaments */
#define menu_drawTexQuad_4282f0(x0, y0, x1, y1, lit) GAME_CDECL(0x4282f0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define profile_4283e0(x0, y0, x1, y1, lit) GAME_CDECL(0x4283e0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexQuad_4284d0(x0, y0, x1, y1, lit) GAME_CDECL(0x4284d0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexQuad_4285c0(x0, y0, x1, y1, lit) GAME_CDECL(0x4285c0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexQuad_4286b0(x0, y0, x1, y1, lit) GAME_CDECL(0x4286b0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexQuad_4287a0(x0, y0, x1, y1, lit) GAME_CDECL(0x4287a0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexturedRect_427a90(x0, y0, x1, y1, tex) GAME_CDECL(0x427a90, void, int, int, int, int, int)(x0, y0, x1, y1, tex)
#define menu_drawTexturedRect_427b60(x0, y0, x1, y1, tex) GAME_CDECL(0x427b60, void, int, int, int, int, int)(x0, y0, x1, y1, tex)
#define menu_drawTexturedRect_428a00(x0, y0, x1, y1) GAME_CDECL(0x428a00, void, int, int, int, int)(x0, y0, x1, y1)
#define menu_drawTexturedRect_428b50(x0, y0, x1) GAME_CDECL(0x428b50, void, int, int, int)(x0, y0, x1)
#define g_menuOrnamentTexture GAME_VAR(int, 0x4deb4c)   /* the panel corner ornaments (texture id, four 128-unit quarters) */
#define menu_431950() GAME_CDECL(0x431950, void, void)()
#define menu_4318b0() GAME_CDECL(0x4318b0, void, void)()
#define menu_44cdd0() GAME_CDECL(0x44cdd0, void, void)()
#define mainmenu_processKeys() GAME_CDECL(0x441e00, void, void)()
#define lobby_processKeys() GAME_CDECL(0x4081f0, void, void)()
#define menu_447c70() GAME_CDECL(0x447c70, void, void)()
#define setup_processTabKeys() GAME_CDECL(0x4230a0, void, void)()
#define armc_processInput() GAME_CDECL(0x410ab0, void, void)()
#define menu_4378e0() GAME_CDECL(0x4378e0, void, void)()
#define menu_4440f0() GAME_CDECL(0x4440f0, void, void)()
#define match_debugHandler() GAME_CDECL(0x42ada0, void, void)()
#define profile_44c600() GAME_CDECL(0x44c600, void, void)()
#define profile_44c850() GAME_CDECL(0x44c850, void, void)()
#define profile_44c8c0() GAME_CDECL(0x44c8c0, void, void)()
#define profile_44ca90() GAME_CDECL(0x44ca90, void, void)()
#define profile_44cc60() GAME_CDECL(0x44cc60, void, void)()
#define missionsel_447cb0() GAME_CDECL(0x447cb0, void, void)()
#define missionsel_448140() GAME_CDECL(0x448140, void, void)()
#define missionsel_44aa20() GAME_CDECL(0x44aa20, void, void)()
#define missionsel_44aa30() GAME_CDECL(0x44aa30, void, void)()
#define sound_playMenu(id) GAME_CDECL(0x41e760, void, int)(id)          /* 0 confirm / back, 2 move */
#define profile_44b600() GAME_CDECL(0x44b600, void, void)()
#define profile_44bc00() GAME_CDECL(0x44bc00, void, void)()
#define profile_deleteFiles() GAME_CDECL(0x44ba60, void, void)()
#define profile_selectAndLoad() GAME_CDECL(0x44b990, void, void)()
#define profile_44b320(x, y) GAME_CDECL(0x44b320, int, int, int)(x, y)  /* the button at (x, y): 0 left, 1 right */
#define profile_44b360(x, y) GAME_CDECL(0x44b360, int, int, int)(x, y)
#define Color4_set(dst, r, g, b, a) GAME_CDECL(0x41f0e0, void, Colour *, float, float, float, float)(dst, r, g, b, a)

/* ---- the in-match 2D pass: the scene's view, its stage's overlay parts, the HUD elements ---- */
#define gfx_setProjectionHud(mode, scale) GAME_CDECL(0x4685f0, void, int, float)(mode, scale)
#define hud_scale() GAME_CDECL(0x468700, float, void)()             /* FUN_00468700: a float setting */
#define hud_456b50(textures) GAME_THISCALL(0x456b50, void, void *)(textures)
#define this_set_4841d0(view) GAME_THISCALL(0x4841d0, void, void *)(view)
#define ViewVolume_captureMatrices(view, a, b) GAME_THISCALL(0x4841f0, void, void *, void *, void *)(view, a, b)
#define ViewVolume_reset(view) GAME_THISCALL(0x484260, void, void *)(view)
/* out = the inverse of m (4 x 4); returns 0 and leaves out untouched when m is singular */
#define Mat4_invert(out, m) GAME_CDECL(0x47d740, int, float *, const float *)(out, m)
/* a shape's shading colours from light factors (seen through inverse, the inverse of the shape's matrix), every part
   into its slice of out; first = 1 (0x466910) */
#define shape_shadeParts(out, first, shape, factors, inverse) GAME_CDECL(0x466910, void, u32 *, int, Model *, const LightFactors *, \
	const float *)(out, first, shape, factors, inverse)
/* a shape's colours from point lights: set (first = 1) or added (0), every part into its slice of out (0x466960) */
#define shape_lightParts(out, first, shape, lights) GAME_CDECL(0x466960, void, u32 *, int, Model *, const void *)(out, first, shape, lights)
#define hud_490b30(stage, i, view) GAME_THISCALL(0x490b30, void, Stage *, int, void *)(stage, i, view)   /* a map object to the view volume */
/* queue every mesh of model for drawing (see recomp.c): extra, matrix (none: the current modelview), a4, colour (4 bytes,
   or none), cull (1: skip meshes outside a clip plane),
   material (< 0: the mesh's own), a8 */
#define ViewVolume_projectObject(view, model, extra, matrix, a4, colour, cull, material, a8) GAME_THISCALL(0x4853c0, void, void *, \
	void *, u32, const float *, int, const void *, int, int, int)(view, model, extra, matrix, a4, colour, cull, material, a8)
#define render_drawObjects(view, mode, alpha) GAME_THISCALL(0x485af0, void, void *, int, float)(view, mode, alpha)
#define hud_496f20(stage, scale) GAME_THISCALL(0x496f20, void, Stage *, float)(stage, scale)   /* the sky (render/sky.c) */
#define render_processRenderingBy(stage, view, scale) GAME_THISCALL(0x497d20, void, void *, void *, float)(stage, view, scale)
/* the stage, the scene's own object (scene.fields: Stage) */
#define STAGE(scene) ((Stage *)((u8 *)(scene) + 0x1f36c8))
#define hud_490da0(stage, view) GAME_THISCALL(0x490da0, void, Stage *, void *)(stage, view)
#define hud_45e170(stage, view, pass) GAME_THISCALL(0x45e170, void, Stage *, void *, int)(stage, view, pass)
/* actor i's frame of its parts (actor_updateBody / actor_updatePart), with the view volume and pass */
#define actor_updateAllParts(stage, i, view, pass) GAME_THISCALL(0x45d3e0, void, Stage *, int, void *, int)(stage, i, view, pass)
#define hud_47d060(stage, view) GAME_THISCALL(0x47d060, void, void *, void *)(stage, view)
#define hud_479af0(stage, view) GAME_THISCALL(0x479af0, void, Stage *, void *)(stage, view)
/* projectile i drawn (or queued) in the view volume */
/* a camera-facing quad at p into the view volume's billboard list id: corners p + a .. p + b, depth + dz, texture
   coordinates uv0 .. uv1, colour (4 bytes) */
#define hud_484ca0(view, id, uv0, uv1, dz, colour, a, b, p, extra, flag) GAME_THISCALL(0x484ca0, void, void *, int, const float *, \
	const float *, float, const void *, const float *, const float *, const float *, int, int)(view, id, uv0, uv1, dz, colour, a, b, p, extra, flag)
#define g_items3D GAME_VAR(int, 0x83a9c8)            /* (unclear) a graphics setting: 1 draws map items as models */
#define g_white GAME_VAR(u32, 0xa1f23c)              /* four bytes 0xff: an opaque white colour */
#define hud_476890(stage, i, view) GAME_THISCALL(0x476890, void, Stage *, int, void *)(stage, i, view)
#define hud_48f970(stage, view) GAME_THISCALL(0x48f970, void, void *, void *)(stage, view)
#define hud_472900(stage, colour, start, end, density) GAME_THISCALL(0x472900, void, Stage *, const void *, u32, u32, u32)(stage, colour, start, end, density)
#define hud_48fde0(stage, x0, y0, x1, y1) GAME_THISCALL(0x48fde0, void, void *, int, int, int, int)(stage, x0, y0, x1, y1)
/* FUN_004625a0: the match's top player: in team games the best ranked player of the leading team (the local player
   if it has none), else the first ranked */
#define scene_topPlayer(scene) GAME_THISCALL(0x4625a0, Player *, Scene *)(scene)
#define hud_drawDigits(x, y, scale, value, digits, flag) GAME_CDECL(0x46bdc0, void, int, int, float, int, int, int)(x, y, scale, value, digits, flag)
#define tex_getIdByName(textures, name, a, b, c, d, e, f, g) GAME_THISCALL(0x456be0, int, void *, const char *, int, int, int, int, int, int, int)(textures, name, a, b, c, d, e, f, g)
#define vec_rotate(v, angle) GAME_THISCALL(0x467700, void, float *, int)(v, angle)   /* turns (x, y) by angle (tenths of a degree) */
#define game_clock() GAME_CDECL(0x4686d0, float, void)()                          /* FUN_004686d0: the float at 0x4c4dec */
#define hud_drawPressFire(scene) GAME_THISCALL(0x495140, void, Scene *)(scene)
#define hud_drawClock(scene) GAME_THISCALL(0x496610, void, Scene *)(scene)
#define hud_drawMatchResult(scene) GAME_THISCALL(0x496a30, void, Scene *)(scene)
#define replay_drawFollowedName(scene) GAME_THISCALL(0x496b80, void, Scene *)(scene)
#define replay_drawMessage(scene) GAME_THISCALL(0x495190, void, Scene *)(scene)
#define hud_4953d0(scene) GAME_THISCALL(0x4953d0, void, Scene *)(scene)
#define hud_496240(scene) GAME_THISCALL(0x496240, void, Scene *)(scene)
#define nullsub_48b420(scene) GAME_THISCALL(0x48b420, void, Scene *)(scene)
#define hud_4955a0(scene) GAME_THISCALL(0x4955a0, void, Scene *)(scene)
#define hud_495ed0(scene, x0, y0, x1, y1) GAME_THISCALL(0x495ed0, void, Scene *, int, int, int, int)(scene, x0, y0, x1, y1)   /* a menu box */
#define hud_drawEscMenu(scene) GAME_THISCALL(0x495610, void, Scene *)(scene)
#define hud_drawRecordIndicator(scene) GAME_THISCALL(0x496d10, void, Scene *)(scene)
#define hud_drawReadyStart(scene) GAME_THISCALL(0x496c20, void, Scene *)(scene)

/* ---- network ---- */
#define net_playerInUse(i) GAME_CDECL(0x4a8700, int, int)(i)   /* FUN_004a8700: the player table's slot i is taken */

/* ---- globals ---- */
typedef struct { float r, g, b, a; } Colour;
#define g_textColours ((Colour *)0xa1f100)          /* the 16 message colours */
#define g_chatLine ((char *)0x9dc92c)               /* the chat line being typed */
#define g_chatCaretX GAME_VAR(int, 0x9da3d8)          /* where the line being typed is drawn (menu units) */
#define g_chatCaretY GAME_VAR(int, 0x9da3dc)
#define g_chatLength GAME_VAR(int, 0x9dbf10)          /* characters in g_chatLine */
#define g_chatFieldFlag GAME_VAR(int, 0x4e1868)       /* (unclear) set for the short fields (passwords, rules), clear for names */
#define input_releaseKeyboard() GAME_CDECL(0x401460, void, void)()
#define menu_clearInputBuffer(maxLength) GAME_CDECL(0x431560, void, int)(maxLength)
#define chat_createEdit(maxLength) GAME_CDECL(0x43f460, void, int)(maxLength)   /* the hidden EDIT control typing goes to */
#define itoa(value, out, radix) GAME_CDECL(0x49fb53, char *, int, char *, int)(value, out, radix)
#define g_missionStage GAME_VAR(int, 0x9dad94)      /* the mission stage being played */
#define g_missionProgress GAME_VAR(int, 0x9f181c)   /* the furthest stage reached */
#define g_trig ((const float *)0xa146f8)            /* 3600 values by tenths of a degree (the ring's radius) */
#define g_showFps GAME_VAR(int, 0x83a9d4)           /* 1: the FPS counter is shown */
#define g_gameModeNames ((const char (*)[64])0x4c7030)   /* "DEATH MATCH", "TEAM DEATH MATCH", ... (12) */
#define g_scene GAME_VAR(Scene *, 0x9087b4)          /* the scene object (0 outside a match) */
#define g_screen GAME_VAR(int, 0x76d3e8)             /* the front end's screen: 100 intro, 200 title, 210 profile, 300 main menu, 400 lobby,
                                                         500 missions, 600 setup, 700 armour, 800 game room, 900 skirmish, 9999 in a match */
#define g_lastScreen GAME_VAR(int, 0x67ef0c)         /* the screen whose music / state was set up last */
#define g_paused GAME_VAR(int, 0x68039c)             /* (unclear) input off: the window is inactive or a text box has the keys */
#define g_keysBlocked GAME_VAR(int, 0x680370)        /* (unclear) the menus ignore their keys while set */
#define g_menuFade GAME_VAR(float, 0x9da434)          /* the menus' fade-in: the keys wait for it to reach 0 */
#define g_frameTime GAME_VAR(float, 0x4b071c)         /* the last frame's time, seconds */
#define g_dialogPending GAME_VAR(int, 0x4df900)      /* a message box is up: it takes the keys */
#define g_dialogOpen GAME_VAR(int, 0x90d1c4)         /* a dialog of the current screen is open */
#define g_textColour ((Colour *)0x76d438)            /* the menus' text colour */
#define g_textCharWidth GAME_VAR(int, 0x4d23d8)      /* units per character of the font being drawn */
#define g_fontHanCho GAME_VAR(int, 0x9dae1c)         /* font textures (ids): Hangul initial consonants */
#define g_fontHanJungJong GAME_VAR(int, 0x76d360)    /* Hangul vowels and finals */
#define g_fontAscii GAME_VAR(int, 0x76d448)          /* ASCII, 5- and 8-unit fonts */
#define g_fontAsciiLarge GAME_VAR(int, 0x9dad90)     /* ASCII, 16- and 32-unit fonts */
/* the title and profile screens */
#define g_titleShown GAME_VAR(int, 0x4df01c)
#define g_titleFrames GAME_VAR(int, 0x4e0458)        /* frames the title has been shown */
/* the title emblem (menu_title.c) */
#define g_titleTextures ((const int *)0x9dad6c)     /* eight: the base picture's quarters, then the pulsing layer's */
#define g_titleSpread ((const int *)0x4b065c)       /* by g_titleFrames: how far the quarters have moved apart (0 .. 512) */
#define g_emblemAlpha GAME_VAR(float, 0x4de1e0)      /* the pulsing layer's alpha (0.2 .. 0.9) */
#define g_emblemPulse GAME_VAR(float, 0x4de1d8)      /* its change per time unit (+-0.018) */
#define g_logoFade GAME_VAR(float, 0x4de1e8)         /* the logo fading in, 0 .. 1 */
#define g_logoFadeLate GAME_VAR(float, 0x4de1ec)     /* (unclear) a faster fade from 0.2, not read here */
#define g_logoTexture GAME_VAR(int, 0x76d3f0)
#define g_profileIntro GAME_VAR(int, 0x9f6838)       /* the profile screen's intro animation runs */
#define g_profileIntroState GAME_VAR(int, 0x9f8e54)  /* 5: finished */
#define g_profileIntroTime GAME_VAR(int, 0x9f8f30)
#define g_profileIntroZoom GAME_VAR(float, 0x9f8f14)
#define g_profileIntroSpeed GAME_VAR(float, 0x9f8e50)
#define g_profilePage GAME_VAR(int, 0x9f8f10)        /* 1 list, 2 info, 3 / 5 name forms, 6 emblem; 4 has no keys */
/* key bindings (key codes), named by their use in the menus */
#define g_keyClick GAME_VAR(int, 0x9dae70)           /* fire / click: the button under the pointer */
#define g_keyOk GAME_VAR(int, 0x4e1510)              /* confirms a page */
#define g_keyCancel GAME_VAR(int, 0x6803a0)          /* leaves a page */
#define g_keyBack GAME_VAR(int, 0x4e0cdc)
#define g_keyCancel2 GAME_VAR(int, 0x76d48c)
#define g_keyLeft GAME_VAR(int, 0x9dae14)
#define g_keyRight GAME_VAR(int, 0x9db974)
#define g_keyUp GAME_VAR(int, 0x9db0a0)
#define g_keyDown GAME_VAR(int, 0x76d330)
#define g_keyToggle GAME_VAR(int, 0x680390)          /* switches a two-button dialog's highlight */
#define g_keyLeftShift GAME_VAR(int, 0x67ef24)       /* the modifier keys (DIK codes 0x2a, 0x36, 0x1d, 0x9d) */
#define g_keyRightShift GAME_VAR(int, 0x9db0ac)
#define g_keyLeftCtrl GAME_VAR(int, 0x6803a8)
#define g_keyRightCtrl GAME_VAR(int, 0x9dad8c)
#define input_isDown(key) GAME_CDECL(0x401590, int, int)(key)   /* the key (code) is held */
#define g_mouseX GAME_VAR(int, 0x4ded68)             /* the pointer, 640 x 480 units */
#define g_mouseY GAME_VAR(int, 0x4ded6c)
#define g_mouseClick GAME_VAR(int, 0x4ded88)         /* a click this frame */
#define g_localPlayer GAME_VAR(int, 0x76d41c)        /* (by use) the local player's index in the room's lists */
#define g_hWndMain GAME_VAR(void *, 0x4ded18)
#define g_screenW GAME_VAR(int, 0x5b1998)
#define g_screenH GAME_VAR(int, 0x4e045c)
#define KillTimer(hwnd, id) IMPORT(0x4a9330, int, void *, u32)(hwnd, id)
/* a rectangle in menu units in g_rectColour, filled or outlined (the patch DLL replaces it: kept original) */
#define menu_drawRect(x0, y0, x1, y1, filled) GAME_CDECL(0x427970, void, int, int, int, int, int)(x0, y0, x1, y1, filled)
#define g_rectColour ((Colour *)0x9da480)
/* the room's buttons under (x, y): the index of the button hit, or -1 */
#define room_4321c0(x, y) GAME_CDECL(0x4321c0, int, int, int)(x, y)
#define room_432280(x, y) GAME_CDECL(0x432280, int, int, int)(x, y)
#define room_432340(x, y) GAME_CDECL(0x432340, int, int, int)(x, y)
#define room_434320() GAME_CDECL(0x434320, void, void)()   /* open the message field */
#define profile_41e7a0(message) GAME_CDECL(0x41e7a0, void, int)(message)   /* (unclear) posts a front-end message */
#define arena_452fe0() GAME_CDECL(0x452fe0, void, void)()
#define g_cursorBlink GAME_VAR(float, 0x4dda44)      /* the text cursor's blink clock */
#define g_cursorFrame GAME_VAR(int, 0x4df03c)        /* the mouse pointer's animation frame, 0..14 */
#define g_cursorFrameTime GAME_VAR(float, 0x4df910)  /* frame time collected towards the next frame (5 units) */
#define g_cursorTexture GAME_VAR(int, 0x4e152c)      /* the pointer's sprite sheet (texture id) */
/* two-button dialogs: the highlighted choice and its marker */
#define g_dialogChoice GAME_VAR(int, 0x74de1c)       /* 0 the left button, 1 the right one */
#define g_highlightShown GAME_VAR(int, 0x76d42c)
#define g_highlightSize GAME_VAR(float, 0x680bc0)
#define g_highlightAlpha GAME_VAR(float, 0x9da4a4)
#define g_highlightX GAME_VAR(int, 0x67ef34)
#define g_highlightY GAME_VAR(int, 0x67fb38)
/* the profile screen's pages */
#define g_profileMessage GAME_VAR(int, 0x9f8f34)     /* page 2 shows a message */
#define g_profileDialogX GAME_VAR(int, 0x9f8f1c)     /* page 3's dialog frame */
#define g_profileDialogY GAME_VAR(int, 0x9f8f0c)
#define g_profileDialog2X GAME_VAR(int, 0x9f6834)    /* page 5's dialog frame */
#define g_profileDialog2Y GAME_VAR(int, 0x9f683c)
#define g_emblemCursor GAME_VAR(int, 0x9f8d30)       /* page 6: 0..8, row by row */
#define g_emblemMoved GAME_VAR(int, 0x9f8d68)
#define g_profile9f8ee4 GAME_VAR(int, 0x9f8ee4)      /* (unclear) cleared when the emblem cursor moves */
#define g_profile9f6828 GAME_VAR(int, 0x9f6828)      /* (unclear) the same */
/* the mission-select screen */
#define g_missionShowBackground GAME_VAR(int, 0x9f63b8)
#define g_missionPage GAME_VAR(int, 0x9f62f8)        /* 0 / 1: no keys; 2: no list refresh */
#define g_missionBox ((const int *)0x9f6308)         /* the dialog frame: x0, y0, x1, y1 */
#define g_missionBusy GAME_VAR(int, 0x9f6300)
#define g_missionStarted GAME_VAR(int, 0x9f62e0)
/* exe strings passed to the text passes (the address itself is what the callee gets) */
#define STR_COPYRIGHT ((const char *)0x4b0474)       /* "AXIS by Jamie System Development" */
#define STR_2D ((const char *)0x4d03e0)              /* "%2d" */
#define STR_VERSION ((const char *)0x4b0384)         /* "Axis v1.03" */

/* ---- DirectPlay (net/dplay_slots.c) ---- */
#define g_dplaySlots ((int *)0xa0d7a4)               /* four connection slots: 1 while open */
#define dplay_coInit() GAME_CDECL(0x453720, int, void)()                     /* 0 when COM is up */
#define dplay_connectionAvailable(kind) GAME_CDECL(0x453a30, int, int)(kind)  /* arena_453a30 */
#define dplay_initConnection(kind, address) GAME_CDECL(0x453a90, int, int, int)(kind, address)
#define dplay_release() GAME_CDECL(0x453920, int, void)()
#define dplay_enumSessions() GAME_CDECL(0x453fd0, int, void)()
#define dplay_hostSession(a1, a2, a3, a4, a5, a6, a7, a8) GAME_CDECL(0x453cf0, int, int, int, int, int, int, int, int, int)\
	(a1, a2, a3, a4, a5, a6, a7, a8)
#define dplay_joinSession(a1, a2, a3, a4) GAME_CDECL(0x453e60, int, int, int, int, int)(a1, a2, a3, a4)
#define dplay_create() GAME_CDECL(0x453790, int, void)()
#define arena_4509e0() GAME_CDECL(0x4509e0, void, void)()
#define arena_4549a0() GAME_CDECL(0x4549a0, int, void)()   /* close slot 0 .. 3 */
#define arena_454ac0() GAME_CDECL(0x454ac0, int, void)()
#define arena_454bd0() GAME_CDECL(0x454bd0, int, void)()
#define arena_454ce0() GAME_CDECL(0x454ce0, int, void)()

/* ---- the stage's player records (thiscall on the stage; p: the player) ---- */
#define player_setName(stage, p, name) GAME_THISCALL(0x473940, void, Stage *, int, const char *)(stage, p, name)
#define player_setValue(stage, p, v) GAME_THISCALL(0x473a10, void, Stage *, int, int)(stage, p, v)   /* FUN_00473a10 */
#define player_setTeam(stage, p, team) GAME_THISCALL(0x473a80, void, Stage *, int, int)(stage, p, team)
#define actor_setActorTypeHeadInfoBy(stage, p, i) GAME_THISCALL(0x473b10, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeChestInfoBy(stage, p, i) GAME_THISCALL(0x473c20, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeArmInfoBy(stage, p, i) GAME_THISCALL(0x473d30, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeLegInfoBy(stage, p, i) GAME_THISCALL(0x473e40, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeBoosterInfoBy(stage, p, i) GAME_THISCALL(0x473f50, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeItemInfoBy(stage, p, slot, item) GAME_THISCALL(0x474060, void, Stage *, int, int, int)(stage, p, slot, item)
#define player_markUsed(stage, p) GAME_THISCALL(0x474390, void, Stage *, int)(stage, p)   /* FUN_00474390 */
/* the ARM CENTER's mech setters (menu/armc_mech.c), thiscall on the scene */
#define armc_461320(scene, name) GAME_THISCALL(0x461320, void, Scene *, const char *)(scene, name)
#define armc_461370(scene, v) GAME_THISCALL(0x461370, void, Scene *, int)(scene, v)
#define match_4613a0(scene, team) GAME_THISCALL(0x4613a0, void, Scene *, int)(scene, team)
#define armc_setHeadIndex(scene, i) GAME_THISCALL(0x4613d0, void, Scene *, int)(scene, i)
#define armc_setChestIndex(scene, i) GAME_THISCALL(0x461410, void, Scene *, int)(scene, i)
#define armc_setArmIndex(scene, i) GAME_THISCALL(0x461450, void, Scene *, int)(scene, i)
#define armc_setLegIndex(scene, i) GAME_THISCALL(0x461490, void, Scene *, int)(scene, i)
#define armc_setBoosterIndex(scene, i) GAME_THISCALL(0x4614d0, void, Scene *, int)(scene, i)
#define armc_461510(scene, slot, item) GAME_THISCALL(0x461510, void, Scene *, int, int)(scene, slot, item)

/* ---- the ARM CENTER (menu/armc_*.c) ---- */
#define g_armcHideInterface GAME_VAR(int, 0x4dd078)  /* Ctrl+Alt+M: the screen without its interface */
#define g_language GAME_VAR(int, 0x9dae74)           /* 2: the small font for labels */
#define armc_41d600() GAME_CDECL(0x41d600, void, void)()      /* the mech preview */
#define armc_41d8a0() GAME_CDECL(0x41d8a0, void, void)()      /* the colour page's preview */
#define armc_40d990() GAME_CDECL(0x40d990, void, void)()      /* the part lists (a no-op in the patched game) */
#define armc_412450() GAME_CDECL(0x412450, void, void)()      /* the screen's frame */
#define armc_drawStatsPanel() GAME_CDECL(0x412650, void, void)()
#define armc_419160() GAME_CDECL(0x419160, void, void)()
#define armc_41a280() GAME_CDECL(0x41a280, void, void)()
#define g_startPos ((const u32 *)0xa0e7a8)          /* (by use) where the player's actor starts (three floats) */
/* claim actor slot a for the player and make it theirs (thiscall on the stage; spawn: slot, -, position...) */
#define match_45dd80(stage, a, x, y, spawn) GAME_THISCALL(0x45dd80, void, Stage *, int, int, int, void *)(stage, a, x, y, spawn)

#define armc_461250(scene, name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5) GAME_THISCALL(0x461250, void, \
	Scene *, const char *, int, int, int, int, int, int, int, int, int, int, int, int, int)(scene, name, v, team, head, chest, arm, leg, \
	booster, i0, i1, i2, i3, i4, i5)
#define armc_45ddc0(stage) GAME_THISCALL(0x45ddc0, void, Stage *)(stage)
#define armc_461540(scene, slot) GAME_THISCALL(0x461540, void, Scene *, int)(scene, slot)   /* re-equip the preview mech */
#define armc_40f870(slot) GAME_CDECL(0x40f870, void, int)(slot)
#define armc_40f950() GAME_CDECL(0x40f950, void, void)()
#define armc_41cca0(item) GAME_CDECL(0x41cca0, void, int)(item)   /* the item shown on the preview */
#define armc_41ca50(slot, item) GAME_CDECL(0x41ca50, void, int, int)(slot, item)
#define armc_snapshot(which) GAME_CDECL(0x419000, void, int)(which)
#define armc_41c510() GAME_CDECL(0x41c510, void, void)()
#define actor_selectWeapon(stage, actor, slot) GAME_THISCALL(0x45e880, void, Stage *, int, int)(stage, actor, slot)
#define app_requireCd(scene, a, b) GAME_THISCALL(0x460cb0, void, Scene *, int, int)(scene, a, b)

#define g_armcMode GAME_VAR(int, 0x4dc798)           /* the ARM CENTER's page: 1 the parts, 2 the weapons, 3 the colours, 4 ... */
#define g_armcPartSlot GAME_VAR(int, 0x4dbc6c)       /* 0 head, 1 chest, 2 arm, 3 leg, 4 booster, 5 weapons */
#define g_armcColourSlot GAME_VAR(int, 0x4dc4b0)     /* the colour slot being edited */
#define g_lobbySubState GAME_VAR(int, 0x4db51c)      /* the lobby's page: 5 the top menu, 0 player setup, 1 join, 2 create */
#define armc_40e670() GAME_CDECL(0x40e670, void, void)()
#define armc_saveSelection() GAME_CDECL(0x40e7a0, void, void)()       /* keep the mech, save the progress */
#define armc_sendSelectionToNet() GAME_CDECL(0x40e930, void, void)()
#define armc_41b300() GAME_CDECL(0x41b300, void, void)()               /* the camera towards the page's target */
#define music_play(path) GAME_CDECL(0x457150, void, const char *)(path)

/* ---- messages ---- */
#define msg_print(scene, colour, ...) GAME_CDECL(0x4629f0, void, Scene *, int, const char *, ...)(scene, colour, __VA_ARGS__)   /* a line in the message box (printf) */
#define sound_playVolume(id, volume) GAME_CDECL(0x456e50, void, int, int)(id, volume)   /* volume 0..100 */

/* ---- the setup screen (menu/setup_keys.c) ---- */
#define g_setupTab GAME_VAR(int, 0x4ddac8)           /* 0 sound, 1 graphics, 2 controls, 0x29a the top page */
#define set_680370_441250(v) GAME_CDECL(0x441250, void, int)(v)   /* g_keysBlocked = v */
#define setup_drawTopPage() GAME_CDECL(0x4220c0, void, void)()
#define setup_drawSoundTab() GAME_CDECL(0x4221d0, void, void)()
#define setup_drawGraphicTab() GAME_CDECL(0x422480, void, void)()
#define setup_drawControlTab() GAME_CDECL(0x422830, void, void)()
#define setup_topPageKeys() GAME_CDECL(0x422b70, void, void)()
#define setup_soundTabKeys() GAME_CDECL(0x422c60, void, void)()
#define setup_graphicTabKeys() GAME_CDECL(0x422d20, void, void)()
#define setup_controlTabKeys() GAME_CDECL(0x422e10, void, void)()
#define setup_selectSoundTab() GAME_CDECL(0x420ad0, void, void)()
#define setup_selectGraphicTab() GAME_CDECL(0x420b40, void, void)()
#define setup_selectControlTab() GAME_CDECL(0x420ba0, void, void)()
#define setup_423e50() GAME_CDECL(0x423e50, void, void)()
#define setup_424810() GAME_CDECL(0x424810, void, void)()
#define setup_425460() GAME_CDECL(0x425460, void, void)()
#define setup_crosshairScreen() GAME_CDECL(0x425cd0, void, void)()
#define cfg_loadAxisCfg() GAME_CDECL(0x42d730, void, void)()
#define music_shutdown() GAME_CDECL(0x457310, void, void)()

#endif
