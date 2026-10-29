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
#define glScalef_bits(x, y, z) IMPORT(0x4a9200, void, u32, u32, u32)(x, y, z)
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
#define menu_onStateChange() GAME_CDECL(0x445e40, void, void)()
#define menu_processKeys() GAME_CDECL(0x4319d0, void, void)()
#define menu_frameBegin() GAME_CDECL(0x41f820, void, void)()
#define menuState100_intro() GAME_CDECL(0x41f540, void, void)()
#define menu_drawVersion() GAME_CDECL(0x41f8d0, void, void)()   /* the title screen (200) */
#define menuState210_frame() GAME_CDECL(0x44f860, void, void)()
#define menuState300_frame() GAME_CDECL(0x443530, void, void)()
#define menuState400_frame() GAME_CDECL(0x40d450, void, void)()
#define menuState500_missionSelect() GAME_CDECL(0x44aa40, void, void)()
#define menuState600_setup() GAME_CDECL(0x427920, void, void)()
#define menuState700_armCenter() GAME_CDECL(0x41e040, void, void)()
#define menuState800_gameRoom() GAME_CDECL(0x43ef70, void, void)()
#define menuState900_skirmishSetup() GAME_CDECL(0x445be0, void, void)()
#define menu_4290d0() GAME_CDECL(0x4290d0, void, void)()   /* the message box */
#define menu_428940(a, b) GAME_CDECL(0x428940, void, int, int)(a, b)
#define menu_drawCursor() GAME_CDECL(0x429bc0, void, void)()
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
#define g_viewAngle GAME_VAR(float, 0x68038c)          /* the 3D view's vertical angle (degrees) */
#define g_viewAspect GAME_VAR(float, 0x4e1870)        /* the 3D view's aspect ratio (gluPerspective), width / height */
#define g_frameTime GAME_VAR(float, 0x4b071c)         /* the last frame's time in 1/60 s (menu_frame; 1 after a stall) */
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
#define profile_41e7a0(code) GAME_CDECL(0x41e7a0, int, int)(code)   /* quit the game with exit code (app/app_quit.c) */
#define PostMessageA(hwnd, msg, w, l) IMPORT(0x4a9328, int, void *, u32, u32, u32)(hwnd, msg, w, l)
#define profile_44bc50() GAME_CDECL(0x44bc50, void, void)()
#define profile_44e640() GAME_CDECL(0x44e640, void, void)()
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
#define armc_411ab0() GAME_CDECL(0x411ab0, void, void)()      /* the screen's state entered from the room */
#define armc_411110() GAME_CDECL(0x411110, void, void)()      /* and from the main menu */
#define arena_launchFromFile() GAME_CDECL(0x410b50, void, void)()
#define armc_40e5d0() GAME_CDECL(0x40e5d0, void, void)()      /* an ARM CENTER session made (menu/armc_items.c) */
#define armc_41b710() GAME_CDECL(0x41b710, void, void)()      /* the 3D view set up (menu/armc_misc.c) */
#define armc_41b400() GAME_CDECL(0x41b400, void, void)()
#define armc_41dcf0() GAME_CDECL(0x41dcf0, void, void)()
#define armc_41dfb0() GAME_CDECL(0x41dfb0, void, void)()      /* the pages' draw passes (menu/armc_misc.c) */
#define armc_41dfe0() GAME_CDECL(0x41dfe0, void, void)()
#define armc_41e010() GAME_CDECL(0x41e010, void, void)()
#define armc_41dab0() GAME_CDECL(0x41dab0, void, void)()
#define armc_exit(confirmed) GAME_CDECL(0x40f0f0, void, int)(confirmed)   /* leave the screen (menu/armc_misc.c) */
#define set_4dc798_40f200() GAME_CDECL(0x40f200, void, void)()   /* to the parts page */
#define set_4dc798_40f320() GAME_CDECL(0x40f320, void, void)()   /* to the third page */
#define armc_drawPartScreen() GAME_CDECL(0x40f220, void, void)()   /* to the weapons page (menu/armc_items.c) */
#define armc_backupColours() GAME_CDECL(0x40f590, void, void)()   /* the colour slot kept for undo (menu/armc_state.c) */
#define armc_40f340(part, dir) GAME_CDECL(0x40f340, u32, u32, int)(part, dir)   /* the part in view stepped (menu/armc_parts.c) */
#define armc_41b750() GAME_CDECL(0x41b750, void, void)()
#define armc_41d280() GAME_CDECL(0x41d280, void, void)()
#define armc_41cf20() GAME_CDECL(0x41cf20, void, void)()
#define armc_41ced0() GAME_CDECL(0x41ced0, void, void)()   /* the undo buffer into colour slots 0 .. 4 (menu/armc_state.c) */
#define FUN_0041ef20(x, y, z) GAME_CDECL(0x41ef20, void, u32, u32, u32)(x, y, z)   /* turned about x, y, z (degrees as float bits; render/gl_helpers.c) */
#define armc_rotateFromCursor(scene, eye, forward, up, part, angle, w, h) \
	GAME_THISCALL(0x461850, void, Scene *, const u32 *, const u32 *, const u32 *, int, int, int, int)(scene, eye, forward, up, part, angle, w, h)
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
#define armc_40f9e0() GAME_CDECL(0x40f9e0, void, void)()   /* the item slots given to the mech (menu/armc_items.c) */
#define armc_40f830(i) GAME_CDECL(0x40f830, int, int)(i)   /* item list entry i is a colour part already in a slot */
#define menu_40e510() GAME_CDECL(0x40e510, void, void)()
#define armc_40e060() GAME_CDECL(0x40e060, void, void)()   /* the part lists made (heads, chests, arms...) */
#define armc_40e1c0() GAME_CDECL(0x40e1c0, void, void)()
#define armc_40e300() GAME_CDECL(0x40e300, void, void)()
#define armc_buildPartLists() GAME_CDECL(0x40da40, void, void)()
#define FUN_004463a0() GAME_CDECL(0x4463a0, u32, void)()   /* the saved mech read (from the profile) */
#define menu_40e6c0() GAME_CDECL(0x40e6c0, void, void)()
#define armc_40de80() GAME_CDECL(0x40de80, void, void)()
#define armc_40dfa0() GAME_CDECL(0x40dfa0, void, void)()
#define armc_40ed20() GAME_CDECL(0x40ed20, void, void)()
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
#define setup_drawKeyBindingRows(key) GAME_CDECL(0x421680, void, int)(key)   /* (by use) the row being bound gets key */
#define setup_controlTabHelper_420c10() GAME_CDECL(0x420c10, void, void)()   /* the default key bindings */
#define music_shutdown() GAME_CDECL(0x457310, void, void)()

/* ---- devices and sound (app/devices.c, sound/sound_basic.c) ---- */
#define g_menuVolume GAME_VAR(int, 0x4dd984)          /* DirectSound volume of the menu sounds: (v * 5 - 500) * 4 of the setting */
#define dsbuf_play(sound) GAME_CDECL(0x467d70, void, void *)(sound)
#define dsbuf_setVolume(sound, volume) GAME_CDECL(0x467db0, void, void *, int)(sound, volume)
#define wnd_401490() GAME_CDECL(0x401490, void, void)()   /* the mouse let go and released */
#define glFinish() IMPORT(0x4a91f0, void, void)()
#define SwapBuffers(hdc) IMPORT(0x4a9028, int, void *)(hdc)
#define g_hdc GAME_VAR(void *, 0xa0e938)
#define CoUninitialize() IMPORT(0x4a93b8, void, void)()

/* ---- front-end screens (menu/menu_states.c) ---- */
#define g_nextScreen GAME_VAR(int, 0x67ef20)          /* (by use) the front-end screen to go to (300 the main menu) */
#define g_progress GAME_VAR(int, 0x9f181c)            /* rounds beaten (missions unlocked) */
#define armc_enter(tunnel) GAME_CDECL(0x441260, void, void *)(tunnel)   /* moves the background tunnel on */
#define menu_drawBackground3D(tunnel) GAME_CDECL(0x429d70, void, void *)(tunnel)
#define mission_4479b0(m) GAME_CDECL(0x4479b0, void, int)(m)
#define mainmenu_4434f0() GAME_CDECL(0x4434f0, void, void)()
#define menu_mainMenu() GAME_CDECL(0x442050, void, void)()
#define mainmenu_442e10() GAME_CDECL(0x442e10, void, void)()
#define menu_drawDimOverlay() GAME_CDECL(0x40ce70, void, void)()
#define skirmish_saveSettings() GAME_CDECL(0x443e20, void, void)()
#define menu_443ea0() GAME_CDECL(0x443ea0, void, void)()
#define skirmish_processKeys() GAME_CDECL(0x443f20, void, void)()
#define menu_444070() GAME_CDECL(0x444070, void, void)()
#define mission_447af0() GAME_CDECL(0x447af0, void, void)()
#define mission_447a50() GAME_CDECL(0x447a50, void, void)()
#define mission_4479d0() GAME_CDECL(0x4479d0, void, void)()
#define FUN_00447960() GAME_CDECL(0x447960, void, void)()
#define menu_447c30() GAME_CDECL(0x447c30, void, void)()
#define menu_447b40() GAME_CDECL(0x447b40, void, void)()

/* ---- DirectPlay calls (net/dplay_calls.c) ---- */
#define CoCreateInstance(clsid, outer, context, iid, out) IMPORT(0x4a93b4, long, const void *, void *, u32, const void *, void **)(clsid, outer, context, iid, out)
#define arena_4549c0() GAME_CDECL(0x4549c0, int, void)()   /* list the sessions through slot 0 .. 3 */
#define arena_454ae0() GAME_CDECL(0x454ae0, int, void)()
#define arena_454bf0() GAME_CDECL(0x454bf0, int, void)()
#define arena_454d00() GAME_CDECL(0x454d00, int, void)()

/* ---- the game's own network code (net/net_servers.c) ---- */
#define net_ping(ip, timeout) GAME_CDECL(0x4548b0, int, u32, int)(ip, timeout)   /* ICMP echo: the round trip time, 0 when none */
#define inet_addr_wrap_4547c0(address) GAME_CDECL(0x4547c0, u32, const char *)(address)
#define net_454760() GAME_CDECL(0x454760, void, void)()   /* the network threads' handles closed */
#define net_4545b0() GAME_CDECL(0x4545b0, void, void)()   /* ping every listed server */
#define WaitForMultipleObjects(n, handles, all, ms) IMPORT(0x4a917c, u32, u32, void *const *, int, u32)(n, handles, all, ms)
#define ExitThread(code) IMPORT(0x4a9180, void, u32)(code)
#define GetTickCount() IMPORT(0x4a9184, u32, void)()
#define data_loadPilotProfiles() GAME_CDECL(0x42b590, void, void)()
#define FUN_00427a40(x0, y0, x1, y1) GAME_CDECL(0x427a40, void, int, int, int, int)(x0, y0, x1, y1)   /* a line in the menu colour */
#define intro_41e730(frames) GAME_CDECL(0x41e730, void, double)(frames)   /* wait frames 1/60 s (app/timer.c) */
#define intro_41f100() GAME_CDECL(0x41f100, void, void)()   /* the loading picture at the next step (0x4dda34) */
#define intro_4411e0() GAME_CDECL(0x4411e0, void, void)()
#define intro_430bf0() GAME_CDECL(0x430bf0, void, void)()
#define menu_loadIntroTextures() GAME_CDECL(0x430ca0, void, void)()
#define profile_44f850() GAME_CDECL(0x44f850, void, void)()   /* quit (app/app_quit.c) */
#define net_closeAll(mode) GAME_CDECL(0x451600, void, int)(mode)   /* every socket closed before connecting */
#define net_send(kind, socket) GAME_CDECL(0x4521c0, u32, int, int)(kind, socket)   /* a packet (0xc room, 0x14 arena...) to the lobby (100) / game server (0x65) */
#define net_connect(mode) GAME_CDECL(0x451b80, int, int)(mode)   /* 100 the lobby, 0x65 the game server (net/net_tables.c) */
#define net_disconnect() GAME_CDECL(0x451e60, u32, void)()   /* leaving the network (net/net_tables.c) */
#define GetModuleHandleA(name) IMPORT(0x4a915c, void *, const char *)(name)
#define glWindow_resize(w, h) GAME_CDECL(0x468450, int, int, int)(w, h)   /* app/win32.c */
#define timer_getGameTime(timer) GAME_THISCALL(0x487490, long double, void *)(timer)   /* seconds since its last call */
#define loading_draw_bits(progress) GAME_CDECL(0x469320, void, u32)(progress)   /* the loading screen at progress (float bits) */
#define mainmenu_4417f0() GAME_CDECL(0x4417f0, void, void)()   /* every map of the map-select list in */
#define mainmenu_440df0() GAME_CDECL(0x440df0, void, void)()   /* and out */
#define mainmenu_441770() GAME_CDECL(0x441770, void, void)()   /* the map-select dialog's OK */
#define net_452de0(reply) GAME_CDECL(0x452de0, void, void *)(reply)   /* the server's accept reply handled */
#define mission_saveAxisMis(k) GAME_CDECL(0x443af0, u32, int)(k)   /* mission k's block read from axis.mis (load/files.c) */
#define skirmish_443c80() GAME_CDECL(0x443c80, u32, void)()   /* leave the skirmish settings */
#define skirmish_443cd0() GAME_CDECL(0x443cd0, void, void)()   /* the skirmish list's cursor up */
#define skirmish_443d10() GAME_CDECL(0x443d10, void, void)()   /* and down */
#define skirmish_445520() GAME_CDECL(0x445520, void, void)()   /* the briefing typed out (menu/skirmish.c) */
#define skirmish_4017b0(v) GAME_CDECL(0x4017b0, int, int)(v)   /* the text wrap x (0x4ad490) */
#define skirmish_4017c0(v) GAME_CDECL(0x4017c0, int, int)(v)   /* the text's bottom (0x4ad494) */
#define timer_now() GAME_CDECL(0x4301e0, long double, void)()   /* the time in ticks of the shifted performance counter, 80-bit */
#define QueryPerformanceFrequency(out) IMPORT(0x4a913c, int, u64 *)(out)
#define msg_newKing(scene) GAME_THISCALL(0x462150, void, Scene *)(scene)   /* the ranking and its "new king" message */
#define ResetEvent(event) IMPORT(0x4a9168, int, void *)(event)
#define SetEvent(event) IMPORT(0x4a9178, int, void *)(event)

/* ---- objects, Win32, GL helpers (app/objects.c, app/win32.c, render/gl_helpers.c) ---- */
#define gfx_initVertexArrayExt(view) GAME_THISCALL(0x483fd0, int, void *)(view)   /* frees the view's vertex buffer, finds GL_EXT_vertex_array */
#define ViewVolume_dtor(view) GAME_THISCALL(0x483fb0, int, void *)(view)
#define Console_dtor(console) GAME_THISCALL(0x460c40, void, void *)(console)   /* named Console_ctor in symbols.csv */
#define Stage_dtor(stage) GAME_THISCALL(0x46ff70, void, Stage *)(stage)
#define operator_delete(p) GAME_CDECL(0x49ef24, void, void *)(p)
#define operator_new(size) GAME_CDECL(0x49f1aa, void *, u32)(size)
#define GetCurrentDirectoryA(size, out) IMPORT(0x4a9108, u32, u32, char *)(size, out)
#define GetActiveWindow() IMPORT(0x4a9320, void *, void)()
#define MessageBoxA(hwnd, text, title, type) IMPORT(0x4a9324, int, void *, const char *, const char *, u32)(hwnd, text, title, type)
#define mciSendCommandA(device, msg, flags, params) IMPORT(0x4a9368, u32, u32, u32, u32, void *)(device, msg, flags, params)
#define glRotatef_bits(angle, x, y, z) IMPORT(0x4a91f8, void, u32, u32, u32, u32)(angle, x, y, z)
#define arena_editTextField_405010() GAME_CDECL(0x405010, void, void)()
#define armc_freeRing(first) GAME_CDECL(0x441190, void, void *)(first)   /* frees the last ring of the tunnel whose first is *first */
#define game_returnToMenus_41e9d0() GAME_CDECL(0x41e9d0, void, void)()

/* ---- more front end (menu/menu_states.c, menu/edit_fields.c) ---- */
#define g_hChatEdit GAME_VAR(void *, 0x9dd888)        /* the hidden EDIT control typing goes to */
#define GetWindowTextLengthA(hwnd) IMPORT(0x4a92e0, int, void *)(hwnd)
#define GetWindowTextA(hwnd, out, size) IMPORT(0x4a92e4, int, void *, char *, int)(hwnd, out, size)
#define game_returnToMenus_41e8b0() GAME_CDECL(0x41e8b0, void, void)()
#define setup_4230e0() GAME_CDECL(0x4230e0, void, void)()
#define setup_4277c0() GAME_CDECL(0x4277c0, void, void)()
#define setup_423330() GAME_CDECL(0x423330, void, void)()
#define setup_427830() GAME_CDECL(0x427830, void, void)()
#define setup_427880() GAME_CDECL(0x427880, void, void)()
#define setup_4278d0() GAME_CDECL(0x4278d0, void, void)()

/* ---- DirectInput setup (app/devices.c) ---- */
#define DirectInputCreateA(instance, version, out, outer) ((long (STDCALL *)(void *, u32, void *, void *))0x4509c0)(instance, version, out, outer)
#define input_initKeyboard(window) GAME_CDECL(0x401310, int, void *)(window)
#define input_4013a0(window) GAME_CDECL(0x4013a0, int, void *)(window)   /* the mouse */

#define FUN_0045dc00(stage, a, x, y, spawn) GAME_THISCALL(0x45dc00, int, Stage *, int, int, int, void *)(stage, a, x, y, spawn)   /* claim actor slot a */
#define FUN_0045e810(stage, actor, slot) GAME_THISCALL(0x45e810, void, Stage *, int, int)(stage, actor, slot)   /* select a weapon slot */
#define match_4327f0() GAME_CDECL(0x4327f0, void, void)()

/* ---- start-up objects (app/statics.c) ---- */
#define ErrorLog_ctor(self, name, b) GAME_THISCALL(0x46c5a0, void *, void *, const char *, int)(self, name, b)   /* a named record (vtable 0x4aa2a0) */
#define atexit(f) GAME_CDECL(0x49ef9c, int, void (*)(void))(f)

/* ---- small classes (app/classes.c) ---- */
#define fclose(f) GAME_CDECL(0x49e7e0, u32, void *)(f)
#define FUN_004569a0(self) GAME_THISCALL(0x4569a0, int, void *)(self)
#define FUN_00464bb0(self) GAME_THISCALL(0x464bb0, int, void *)(self)
#define load_466a20(self) GAME_THISCALL(0x466a20, int, void *)(self)
#define load_46ae70(self) GAME_THISCALL(0x46ae70, int, void *)(self)
#define load_4813a0(self) GAME_THISCALL(0x4813a0, int, void *)(self)
#define load_487480(self) GAME_THISCALL(0x487480, int, void *)(self)
#define this_set_483d60(self) GAME_THISCALL(0x483d60, int, void *)(self)
#define FUN_004569b0(self) GAME_THISCALL(0x4569b0, int, void *)(self)
#define load_466a30(self) GAME_THISCALL(0x466a30, int, void *)(self)
#define load_46ae80(self) GAME_THISCALL(0x46ae80, int, void *)(self)
#define load_4813b0(self) GAME_THISCALL(0x4813b0, int, void *)(self)
#define FUN_00464bc0(self) GAME_THISCALL(0x464bc0, int, void *)(self)
#define TextureManager_dtor(self) GAME_THISCALL(0x456990, int, void *)(self)
#define Light_dtor(self) GAME_THISCALL(0x483d50, int, void *)(self)
#define CollisionVolume_dtor(self) GAME_THISCALL(0x481390, int, void *)(self)
#define Model_dtor(self) GAME_THISCALL(0x464ba0, int, void *)(self)
#define ShapeManager_dtor(self) GAME_THISCALL(0x466a10, int, void *)(self)
#define SkeletonManager_dtor(self) GAME_THISCALL(0x46ae60, int, void *)(self)
#define TimeSync_dtor(self) GAME_THISCALL(0x487470, void, void *)(self)
#define Scene_dtor(self) GAME_THISCALL(0x48b410, void, void *)(self)
#define BMPRGBFile_ctor(self) GAME_THISCALL(0x46ce60, void, void *)(self)
#define ErrorLog_dtor(self) GAME_THISCALL(0x46c5e0, void, void *)(self)
#define Texture_ctor(self) GAME_THISCALL(0x455030, u32, void *)(self)   /* in fact Texture's destructor */

/* ---- start-up pieces called by the start-up pairs (app/statics.c) ---- */
#define BMPRGBFile_rtti() GAME_CDECL(0x46ccb0, void *, void)()
#define CollisionVolume_rtti() GAME_CDECL(0x481340, void *, void)()
#define Console_rtti() GAME_CDECL(0x460520, void *, void)()
#define Light_rtti() GAME_CDECL(0x483d00, void *, void)()
#define PackedColor_rtti() GAME_CDECL(0x46da70, void *, void)()
#define RealColor_rtti() GAME_CDECL(0x46d270, void *, void)()
#define Scene_rtti() GAME_CDECL(0x48b3c0, void *, void)()
#define ShapeManager_rtti() GAME_CDECL(0x4669c0, void *, void)()
#define Shape_rtti() GAME_CDECL(0x463b30, void *, void)()
#define SkeletonManager_rtti() GAME_CDECL(0x46ae10, void *, void)()
#define Skeleton_rtti() GAME_CDECL(0x469930, void *, void)()
#define Sound_rtti() GAME_CDECL(0x456c90, void *, void)()
#define Stage_rtti() GAME_CDECL(0x46ff20, void *, void)()
#define TextureManager_ctor() GAME_CDECL(0x42b330, int, void)()
#define TextureManager_rtti() GAME_CDECL(0x456940, void *, void)()
#define Texture_rtti() GAME_CDECL(0x454fe0, void *, void)()
#define TimeSync_rtti() GAME_CDECL(0x4873e0, void *, void)()
#define UnitPartInfo_rtti() GAME_CDECL(0x46f360, void *, void)()
#define UnitPoseInfo_rtti() GAME_CDECL(0x46f3c0, void *, void)()
#define Unit_rtti() GAME_CDECL(0x46f420, void *, void)()
#define ViewVolume_rtti() GAME_CDECL(0x483f60, void *, void)()
#define load_487430_wrap_468720() GAME_CDECL(0x468720, void, void)()
#define static_initObject_4e1878() GAME_CDECL(0x42b130, void, void)()
#define static_initObject_5b1db8() GAME_CDECL(0x42b1a0, void, void)()
#define static_initObject_680cd8() GAME_CDECL(0x42b1f0, void, void)()
#define static_initObject_76d498() GAME_CDECL(0x42b240, void, void)()
#define static_initObject_83a9e0() GAME_CDECL(0x42b2e0, void, void)()
#define static_initObject_90d1e0() GAME_CDECL(0x42b290, void, void)()
#define static_registerDtor_42b170() GAME_CDECL(0x42b170, int, void)()
#define static_registerDtor_42b1c0() GAME_CDECL(0x42b1c0, int, void)()
#define static_registerDtor_42b210() GAME_CDECL(0x42b210, int, void)()
#define static_registerDtor_42b260() GAME_CDECL(0x42b260, int, void)()
#define static_registerDtor_42b2b0() GAME_CDECL(0x42b2b0, int, void)()
#define static_registerDtor_42b300() GAME_CDECL(0x42b300, int, void)()
#define static_registerDtor_42b370() GAME_CDECL(0x42b370, int, void)()
#define static_registerDtor_455000() GAME_CDECL(0x455000, int, void)()
#define static_registerDtor_456960() GAME_CDECL(0x456960, int, void)()
#define static_registerDtor_456cb0() GAME_CDECL(0x456cb0, int, void)()
#define static_registerDtor_460540() GAME_CDECL(0x460540, int, void)()
#define static_registerDtor_463b50() GAME_CDECL(0x463b50, int, void)()
#define static_registerDtor_4669e0() GAME_CDECL(0x4669e0, int, void)()
#define static_registerDtor_468730() GAME_CDECL(0x468730, int, void)()
#define static_registerDtor_469950() GAME_CDECL(0x469950, int, void)()
#define static_registerDtor_46ae30() GAME_CDECL(0x46ae30, int, void)()
#define static_registerDtor_46ccd0() GAME_CDECL(0x46ccd0, int, void)()
#define static_registerDtor_46d290() GAME_CDECL(0x46d290, int, void)()
#define static_registerDtor_46da90() GAME_CDECL(0x46da90, int, void)()
#define static_registerDtor_46f380() GAME_CDECL(0x46f380, int, void)()
#define static_registerDtor_46f3e0() GAME_CDECL(0x46f3e0, int, void)()
#define static_registerDtor_46f440() GAME_CDECL(0x46f440, int, void)()
#define static_registerDtor_46ff40() GAME_CDECL(0x46ff40, int, void)()
#define static_registerDtor_481360() GAME_CDECL(0x481360, int, void)()
#define static_registerDtor_483d20() GAME_CDECL(0x483d20, int, void)()
#define static_registerDtor_483f80() GAME_CDECL(0x483f80, int, void)()
#define static_registerDtor_487400() GAME_CDECL(0x487400, int, void)()
#define static_registerDtor_48b3e0() GAME_CDECL(0x48b3e0, int, void)()

/* ---- small pieces (app/small.c) ---- */
#define set_colour_bits(c, r, g, b, a) GAME_CDECL(0x41f0e0, void, Colour *, u32, u32, u32, u32)(c, r, g, b, a)   /* Color4_set with float bits */
#define set4ints(a, b, c, d, out) GAME_CDECL(0x42eeb0, void, int, int, int, int, int *)(a, b, c, d, out)
#define FUN_00441120(head) GAME_CDECL(0x441120, u32, void *)(head)   /* a ring added to the background tunnel */
#define FUN_00473470(stage, p) GAME_THISCALL(0x473470, void, Stage *, int)(stage, p)   /* player p's colour grid cleared */
#define actor_deactivate(stage, i) GAME_THISCALL(0x45dca0, void, Stage *, int)(stage, i)
#define FUN_00469980(self) GAME_THISCALL(0x469980, void, void *)(self)
#define FUN_0046f480(self) GAME_THISCALL(0x46f480, void, void *)(self)
#define FUN_0046f4b0(self) GAME_THISCALL(0x46f4b0, int, void *)(self)
#define cfg_44ac50(s) GAME_CDECL(0x44ac50, int, const char *)(s)

/* ---- batch: front-end records, objects, video tables ---- */
#define FUN_00451450() GAME_CDECL(0x451450, u8, void)()   /* a free network player slot claimed (0xff: none) */
#define arena_4514a0(slot, id) GAME_CDECL(0x4514a0, void, u32, int)(slot, id)   /* player slot taken by id */
#define space_disableUnit(unit) GAME_THISCALL(0x480460, void, void *)(unit)
#define space_enableUnit(unit) GAME_THISCALL(0x480480, void, void *)(unit)
#define FUN_00456820(self, m) GAME_THISCALL(0x456820, void, void *, int)(self, m)   /* material m marked changed */
#define profile_44b7a0() GAME_CDECL(0x44b7a0, void, void)()
#define ptx_46e320() GAME_CDECL(0x46e320, void, void)()
#define ptx_initTable_46efd0() GAME_CDECL(0x46efd0, void, void)()
#define ptx_46e2b0(q) GAME_CDECL(0x46e2b0, void, int)(q)
#define ptx_46e7c0() GAME_CDECL(0x46e7c0, void, void)()
#define ptx_46e9b0(q) GAME_CDECL(0x46e9b0, void, int)(q)
#define ptx_error(...) ((int (CDECL *)(int, const char *, ...))0x46e260)(__VA_ARGS__)   /* app/ptx_decode.c */
#define ptx_crtlError(...) ((int (CDECL *)(int, const char *, ...))0x46e1e0)(__VA_ARGS__)
#define set_a61708_46f090(p) GAME_CDECL(0x46f090, void, const u8 *)(p)   /* the bit reader started at p */
#define ptx_internal_46f0b0(block) GAME_CDECL(0x46f0b0, int, int *)(block)   /* one block's coefficients; the bit position */
#define ptx_decodeBlock_46e380(in, out) GAME_CDECL(0x46e380, void, const int *, u8 *)(in, out)
#define ptx_internal_46e830(y, dst, n) GAME_CDECL(0x46e830, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_internal_46e8e0(y, dst, n) GAME_CDECL(0x46e8e0, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_internal_46ea30(src, dst, w, h, bpp) GAME_CDECL(0x46ea30, void, const u8 *, u8 *, int, int, int)(src, dst, w, h, bpp)

#define room_431c00() GAME_CDECL(0x431c00, void, void)()
#define room_431b70() GAME_CDECL(0x431b70, void, void)()
#define tex_recolourMaterial(set, m, h1, c1, v1, h2, c2, v2) GAME_THISCALL(0x456860, void, void *, int, u32, u32, u32, u32, u32, u32)(set, m, h1, c1, v1, h2, c2, v2)
#define FUN_00464a70(px, mode, part, colour) GAME_CDECL(0x464a70, void, u8 *, int, const u32 *, const u8 *)(px, mode, part, colour)   /* a colour added to a part's RGBA pixels */
#define load_480440(slot) GAME_THISCALL(0x480440, void, int *)(slot)
#define shape_466560(shape) GAME_THISCALL(0x466560, void, void *)(shape)
#define shape_4665c0(shape, h1, c1, v1, h2, c2, v2) GAME_THISCALL(0x4665c0, void, void *, u32, u32, u32, u32, u32, u32)(shape, h1, c1, v1, h2, c2, v2)

#define crt_free(p) GAME_CDECL(0x49ee81, u32, void *)(p)
#define crt_fopen(name, mode) GAME_CDECL(0x49e9ca, void *, const char *, const char *)(name, mode)
#define crt_fwrite(p, size, count, f) GAME_CDECL(0x49f58a, u32, const void *, u32, u32, void *)(p, size, count, f)
#define crt_rand() GAME_CDECL(0x49f92c, int, void)()
#define save_cryptRecord(rec, key) GAME_CDECL(0x445ee0, void, u8 *, u8)(rec, key)   /* a 0x3ac-byte profile record scrambled (menu/profile_misc.c) */
#define match_4464b0() GAME_CDECL(0x4464b0, void, void)()   /* the current profile's record gathered (0x9f1718) */
#define profile_445f40(p, key) GAME_CDECL(0x445f40, void, u8 *, u8)(p, key)   /* a 0x80-byte record unscrambled */
#define fread_scrambled(p, size, count, f) GAME_CDECL(0x46cbe0, u32, void *, u32, u32, void *)(p, size, count, f)   /* fread, each byte unscrambled (rotated left, xor 0x59) */
#define hud_47ca70(stage, i, view) GAME_THISCALL(0x47ca70, void, Stage *, int, void *)(stage, i, view)   /* bullet i's trail drawn */
#define hud_48b450(self, a, b, c, d) GAME_THISCALL(0x48b450, void, void *, int, int, int, int)(self, a, b, c, d)
#define FUN_00467d60(p) GAME_CDECL(0x467d60, u32, void *)(p)   /* p deleted (0 for none) */

#define g_menuState GAME_VAR(int, 0x76d3e8)          /* the front end's screen (300 the main menu) */
#define arena_4065e0() GAME_CDECL(0x4065e0, void, void)()   /* the session list sorted */

/* ---- the projection switch and the menus' 2D (menu_2d.c) ---- */
#define GL_LINES 1
#define GL_DEPTH_TEST 0x0b71
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define glViewport(x, y, w, h) IMPORT(0x4a91d4, void, int, int, int, int)(x, y, w, h)
#define glMatrixMode(mode) IMPORT(0x4a91fc, void, u32)(mode)
#define gluPerspective(angle, aspect, zNear, zFar) ((void (STDCALL *)(double, double, double, double))0x4509c6)(angle, aspect, zNear, zFar)
#define gluOrtho2D(left, right, bottom, top) ((void (STDCALL *)(double, double, double, double))0x4509cc)(left, right, bottom, top)

/* ---- small methods and resets (app/small.c, app/classes.c, match/actor_slots.c, load/space_pools.c, render/rotations.c) ---- */
#define FUN_0046cb60(path) GAME_CDECL(0x46cb60, char *, char *)(path)   /* upper-cased in place, '/' -> '\' */
#define FUN_00470f80(self, folder) GAME_THISCALL(0x470f80, char *, void *, const char *)(self, folder)
#define TimeSync_ctor(self) GAME_THISCALL(0x487430, void *, void *)(self)
#define FUN_004699a0(self) GAME_THISCALL(0x4699a0, int, void *)(self)   /* a skeleton released */
#define FUN_0045df90(stage) GAME_THISCALL(0x45df90, void, Stage *)(stage)
#define load_474480(stage) GAME_THISCALL(0x474480, void, Stage *)(stage)   /* the 16 player records reset */
#define FUN_0045e070(stage) GAME_THISCALL(0x45e070, void, Stage *)(stage)
#define actor_resetSlot(stage, i) GAME_THISCALL(0x4743e0, void, Stage *, int)(stage, i)
#define load_47db50(self) GAME_THISCALL(0x47db50, int, void *)(self)   /* a collision plane cleared */
#define load_480430(self) GAME_THISCALL(0x480430, int, void *)(self)   /* a node */
#define load_4804a0(self) GAME_THISCALL(0x4804a0, int, void *)(self)   /* a block */
#define FUN_0047d0b0(q, rotation) GAME_THISCALL(0x47d0b0, void, float *, const float *)(q, rotation)
#define FUN_0047d8a0(m, q) GAME_CDECL(0x47d8a0, void, float *, const float *)(m, q)   /* quaternion -> matrix */

/* ---- (render/shape_colours.c, app/small.c, menu/menu_records.c callers) ---- */
#define shape_setTint(model, h1, c1, v1, h2, c2, v2) GAME_THISCALL(0x467660, void, void *, u32, u32, u32, u32, u32, u32)(model, h1, c1, v1, h2, c2, v2)
#define shape_4675f0(model) GAME_THISCALL(0x4675f0, void, void *)(model)   /* the model's shapes' own colours back */
#define script_reset(stage) GAME_THISCALL(0x48fca0, int, Stage *)(stage)
#define skirmish_443910(x, y) GAME_CDECL(0x443910, int, int, int)(x, y)   /* which skirmish settings arrow is at (x, y) */
#define FUN_00443d80() GAME_CDECL(0x443d80, void, void)()   /* skirmish settings: the pending step pushed */
#define FUN_00443de0() GAME_CDECL(0x443de0, void, void)()   /* one step undone */

/* ---- the lobby's and room's screens (menu/lobby_states.c) ---- */
#define lobby_404930() GAME_CDECL(0x404930, void, void)()   /* the player's record from the profile */
#define room_403300() GAME_CDECL(0x403300, void, void)()   /* the map list laid out */
#define lobby_drawArenaTitle() GAME_CDECL(0x404980, void, void)()
#define room_403420() GAME_CDECL(0x403420, void, void)()   /* the map on/off list reset */
#define room_433700() GAME_CDECL(0x433700, void, void)()   /* the room settings copied */

/* ---- the PTX video decoder (app/ptx_decode.c) ---- */
#define ptx_46f230(out, n) GAME_CDECL(0x46f230, int, int *, int)(out, n)   /* the next n bits of the stream */
#define ptx_internal_46f190(out) GAME_CDECL(0x46f190, void, int *)(out)   /* a DC difference */
#define ptx_internal_46f2a0(out, run) GAME_CDECL(0x46f2a0, void, int *, int *)(out, run)   /* an AC symbol */

/* ---- (net/net_sessions.c, render/rotations.c) ---- */
#define arena_4065a0(a, b) GAME_CDECL(0x4065a0, void, void *, void *)(a, b)   /* two session records swapped */
#define Vec3_normalize(v) GAME_THISCALL(0x467760, long double, float *)(v)   /* returns the length, unrounded */

/* ---- (load/lists.c, render/shape_colours.c, net/net_tables.c, match/map_objects.c, menu/lobby_states.c) ---- */
#define crt_malloc(size) GAME_CDECL(0x49eeb0, void *, u32)(size)
#define crt_strtok(s, delimiters) GAME_CDECL(0x49ec3b, char *, char *, const char *)(s, delimiters)   /* the game's CRT strtok */
#define crt_atoi(s) GAME_CDECL(0x49ec09, int, const char *)(s)
#define FUN_00440e20(node, value) GAME_CDECL(0x440e20, u32, void *, int)(node, value)
#define tex_tintHsv(c, dh, ds, dv) GAME_THISCALL(0x46d950, void, float *, u32, u32, u32)(c, dh, ds, dv)
#define skel_getSkeletonPtrBy(cache, name) GAME_THISCALL(0x46b1a0, void *, void *, u32)(cache, name)
#define FUN_0040ddb0() GAME_CDECL(0x40ddb0, void, void)()   /* the mech unpacked */

/* ---- (render/tex_colours.c) ---- */
#define tex_46def0(r, g, b, h, s, v) GAME_CDECL(0x46def0, void, u32, u32, u32, float *, float *, float *)(r, g, b, h, s, v)   /* RGB -> HSV (r, g, b as float bits) */
#define color_hsvToRgb(h, s, v, r, g, b) GAME_CDECL(0x46e050, void, u32, u32, u32, float *, float *, float *)(h, s, v, r, g, b)   /* (h, s, v as float bits) */
#define tex_46de20(rgba, dh, ds, dv) GAME_THISCALL(0x46de20, int, u8 *, u32, u32, u32)(rgba, dh, ds, dv)   /* an RGBA byte colour tinted */

/* ---- (net/net_sessions.c) ---- */
#define arena_4532a0() GAME_CDECL(0x4532a0, int, void)()   /* the session list's count */
#define arena_4532b0(i) GAME_CDECL(0x4532b0, int, int)(i)   /* session i's record */

#define room_432be0() GAME_CDECL(0x432be0, void, void)()   /* the joined game's settings into the room screen */

/* ---- the screens' set-ups (menu/screen_enter.c): rectangle builders and resets ---- */
#define arena_4045e0() GAME_CDECL(0x4045e0, void, void)()
#define arena_403f30() GAME_CDECL(0x403f30, void, void)()
#define arena_403f80() GAME_CDECL(0x403f80, void, void)()
#define arena_404010() GAME_CDECL(0x404010, void, void)()
#define arena_404120() GAME_CDECL(0x404120, void, void)()
#define arena_404190() GAME_CDECL(0x404190, void, void)()
#define arena_404150() GAME_CDECL(0x404150, void, void)()
#define setup_420300() GAME_CDECL(0x420300, void, void)()
#define setup_420480() GAME_CDECL(0x420480, void, void)()
#define setup_420510() GAME_CDECL(0x420510, void, void)()
#define room_431ae0() GAME_CDECL(0x431ae0, void, void)()
#define room_431c50() GAME_CDECL(0x431c50, void, void)()
#define room_431ce0() GAME_CDECL(0x431ce0, void, void)()
#define room_431db0() GAME_CDECL(0x431db0, void, void)()
#define room_431de0() GAME_CDECL(0x431de0, void, void)()
#define room_432040() GAME_CDECL(0x432040, void, void)()
#define room_431aa0() GAME_CDECL(0x431aa0, void, void)()

#define hud_4848e0(view, texture, uv0, uv1, colour, points, kind, flag) GAME_THISCALL(0x4848e0, void, void *, int, const u32 *, const u32 *, const u32 *, const float *, u32, int)(view, texture, uv0, uv1, colour, points, kind, flag)   /* a textured quad into the view volume */

#define FUN_00454110() GAME_CDECL(0x454110, int, void)()   /* the first free session slot, or -1 */

#define Mat4_transformPoint(out, m, p) GAME_CDECL(0x484860, void, float *, const float *, const float *)(out, m, p)

/* ---- (app/devices.c, net/net_tables.c, app/small.c, render/object_list.c, menu/armc_misc.c) ---- */
#define FUN_00450bf0(from, to, flags, data, size) GAME_CDECL(0x450bf0, int, u32, u32, u32, const void *, u32)(from, to, flags, data, size)   /* a DirectPlay message sent */
#define space_setBy(space, lo, hi, nx, ny, nz, a, b, depth) GAME_THISCALL(0x4819b0, u32, void *, void *, void *, int, int, int, int, int, int)(space, lo, hi, nx, ny, nz, a, b, depth)
#define FUN_00466650(shape) GAME_THISCALL(0x466650, u32, void *)(shape)   /* a shape's textures bound */
#define armc_40fb20() GAME_CDECL(0x40fb20, u32, void)()
#define armc_40fd30() GAME_CDECL(0x40fd30, u32, void)()
#define armc_colourScreenInput() GAME_CDECL(0x40ff40, u32, void)()

#define FUN_0047d9a0(m, rotation) GAME_CDECL(0x47d9a0, void, float *, const float *)(m, rotation)   /* (angle, axis) -> matrix */

/* the DirectPlay slot functions by connection kind (src/net/dplay_slots.c) */
#define dplay_slotHost(kind, a1, a2, a3, a4, a5, a6, a7, a8) 	GAME_CDECL(((const u32[4]){ 0x4549e0, 0x454b00, 0x454c10, 0x454d20 })[kind], int, int, int, int, int, int, int, int, int)(a1, a2, a3, a4, a5, a6, a7, a8)
#define dplay_slotJoin(kind, a1, a2, a3, a4) 	GAME_CDECL(((const u32[4]){ 0x454a20, 0x454b40, 0x454c50, 0x454d60 })[kind], int, int, int, int, int)(a1, a2, a3, a4)

/* the error reporters (src/app/error_log.c): a message, or a fatal one that ends the game */
#define sys_errorTerminate(...) GAME_CDECL(0x46c950, void, const char *, ...)(__VA_ARGS__)

/* a menu button's outline as FUN_0041eea0 takes it on the stack: the edge count, then the corners' xs and ys */
typedef struct { int n, x[5], y[5]; } Outline;
#define point_in_outline(x, y, outline) GAME_CDECL(0x41eea0, int, int, int, Outline)(x, y, outline)   /* FUN_0041eea0 */

/* the Korean text passes (text/text_codes.c): the lead glyphs, and the vowel and tail glyphs, at 13 and 31 units */
#define text_hanCho(x, y, s) GAME_CDECL(0x401870, void, int, int, const char *)(x, y, s)
#define text_hanJungJong(x, y, s) GAME_CDECL(0x401aa0, void, int, int, const char *)(x, y, s)
#define text_hanCho32(x, y, s) GAME_CDECL(0x401ce0, void, int, int, const char *)(x, y, s)
#define text_hanJungJong32(x, y, s) GAME_CDECL(0x401e70, void, int, int, const char *)(x, y, s)

/* strcmp as the original inlines it: -1 / 0 / 1, the bytes compared unsigned */
static inline int str_order(const char *a, const char *b)
{
	for (;; a++, b++) {
		if (*a != *b)
			return (u8)*a < (u8)*b ? -1 : 1;
		if (*a == '\0')
			return 0;
	}
}

#endif
