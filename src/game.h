/* game.h: the parts of AxisGL.exe the rebuilt code uses by their original address: functions (called through their
   address, see axis.h), globals and imports. Grows as rebuilds need more; a name defined here can still have a
   rebuild of its own elsewhere in src (that file defines it as "void (name)(...)"). */
#ifndef GAME_H
#define GAME_H
#include "axis.h"
#include "scene.h"
#include "globals.h"
#include "objects.h"   /* the arrays, buffers and records by name (tools/name_objects.py) */
#include "calls.h"     /* game functions by their plain name (tools/plain_calls.py; game.h has the others) */
#ifdef AXIS_DIRECT
#include "data/layout_names.h"   /* (in AxisRC.exe the named globals are members of g_rdata / g_data) */
#endif

/* ---- OpenGL, through the import table ---- */
#define GL_TEXTURE_2D 0x0de1
#define glColor4f(r, g, b, a) IMPORT(0x4a9228, void, float, float, float, float)(r, g, b, a)
/* a colour kept in memory, passed on bit for bit (the original copies the four values without the FPU, which
   would turn a signalling NaN into a quiet one) */
#define glColor4f_stored(c) IMPORT(0x4a9228, void, u32, u32, u32, u32)(((const u32 *)RELOC(c))[0], ((const u32 *)RELOC(c))[1], \
	((const u32 *)(c))[2], ((const u32 *)(c))[3])
#define glEnable(cap) IMPORT(0x4a9224, void, u32)(cap)
#define GL_FOG 0x0b60
#define GL_DEPTH_BUFFER_BIT 0x0100
#define GL_COLOR_BUFFER_BIT 0x4000
#define glClear(mask) IMPORT(0x4a91e8, void, u32)(mask)
#define glClearDepth(depth) IMPORT(0x4a91dc, void, double)(depth)
/* a clear colour kept in memory (three floats), passed on bit for bit, alpha 1 */
#define glClearColor_stored(c) IMPORT(0x4a91e0, void, u32, u32, u32, u32)((c)[0], (c)[1], (c)[2], 0x3f800000u)
#define glClearColor(r, g, b, a) IMPORT(0x4a91e0, void, float, float, float, float)(r, g, b, a)
#define glClearColor_bits(r, g, b, a) IMPORT(0x4a91e0, void, u32, u32, u32, u32)(r, g, b, a)   /* (the floats as their bits) */
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
/* (render/view_volume.c: drawing the queued objects; vectors and colours passed as pointers into memory) */
#define glPolygonMode(face, mode) IMPORT(0x4a91c4, void, u32, u32)(face, mode)
#define glGetBooleanv(pname, out) IMPORT(0x4a9250, void, u32, u8 *)(pname, out)
#define glEnableClientState(array) IMPORT(0x4a9240, void, u32)(array)
#define glDisableClientState(array) IMPORT(0x4a923c, void, u32)(array)
#define glVertexPointer(size, type, stride, p) IMPORT(0x4a9248, void, int, u32, int, const void *)(size, type, stride, p)
#define glColorPointer(size, type, stride, p) IMPORT(0x4a9244, void, int, u32, int, const void *)(size, type, stride, p)
#define glTexCoordPointer(size, type, stride, p) IMPORT(0x4a9234, void, int, u32, int, const void *)(size, type, stride, p)
#define glMultMatrixf(m) IMPORT(0x4a9238, void, const float *)(m)
#define glCullFace(mode) IMPORT(0x4a91d0, void, u32)(mode)
#define glDrawElements(mode, count, type, indices) IMPORT(0x4a92a8, void, u32, int, u32, const void *)(mode, count, type, indices)
#define glPolygonOffset(factor, units) IMPORT(0x4a92a4, void, float, float)(factor, units)
#define glColor4ub(r, g, b, a) IMPORT(0x4a929c, void, u8, u8, u8, u8)(r, g, b, a)
#define glColor3ub(r, g, b) IMPORT(0x4a9298, void, u8, u8, u8)(r, g, b)
#define glColor4ubv(c) IMPORT(0x4a92a0, void, const void *)(c)
#define glTexCoord2fv(v) IMPORT(0x4a927c, void, const void *)(v)
#define glVertex4fv(v) IMPORT(0x4a9294, void, const void *)(v)
#define glTexCoord2f_bits(s, t) IMPORT(0x4a920c, void, u32, u32)(s, t)
/* a point kept in memory (three floats), passed on bit for bit */
#define glVertex3f_stored(v) IMPORT(0x4a9210, void, u32, u32, u32)(((const u32 *)RELOC(v))[0], ((const u32 *)RELOC(v))[1], ((const u32 *)RELOC(v))[2])
/* colours and translations given as float bits (see BITS) */
#define glColor4f_bits(r, g, b, a) IMPORT(0x4a9228, void, u32, u32, u32, u32)(r, g, b, a)
#define glTranslatef_bits(x, y, z) IMPORT(0x4a9214, void, u32, u32, u32)(x, y, z)
#define glScalef_bits(x, y, z) IMPORT(0x4a9200, void, u32, u32, u32)(x, y, z)
/* GLU, through the game's jump to its import */
#define gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz) IMPORT(0x4a904c, void, double, double, double, double, double, double, \
	double, double, double)(ex, ey, ez, cx, cy, cz, ux, uy, uz)
#define glPopMatrix() IMPORT(0x4a9258, void, void)()
/* a point kept in memory (three floats), passed on bit for bit */
#define glTranslatef_stored(v) IMPORT(0x4a9214, void, u32, u32, u32)(((const u32 *)RELOC(v))[0], ((const u32 *)RELOC(v))[1], ((const u32 *)RELOC(v))[2])
#define glRotatef(angle, x, y, z) IMPORT(0x4a91f8, void, float, float, float, float)(angle, x, y, z)

/* ---- C runtime of the game ---- */
#define sprintf(...) GAME_CDECL(0x49e9dd, int, char *, const char *, ...)(__VA_ARGS__)
#define vsprintf(out, format, args) GAME_CDECL(0x49ed2e, int, char *, const char *, va_list)(out, format, args)

/* ---- screen ---- */
#define gfx_setProjection2D3D(mode) GAME_FN(gfx_setProjection2D3D, 0x41ef90, void, int)(mode)   /* 1: 3D, 2: the menus' 2D */
/* a vertex in the menus' 640 x 480 units (the patch DLL replaces this function: kept original) */
#define menu_vertex(x, y) GAME_FN(menu_vertex, 0x41ef60, void, int, int)(x, y)
/* the menus' 3D camera (gluLookAt) for models and the tunnel */
#define gfx_setMenuCamera() GAME_FN(gfx_setMenuCamera, 0x41f050, void, void)()
/* glRotatef about x, then y, then z (degrees, as float bits) */
#define gfx_rotateXYZ(x, y, z) GAME_FN(gl_rotateXYZ, 0x41ef20, void, u32, u32, u32)(x, y, z)
/* the 3D background (menu_tunnel.c) */
#define g_flareTextures ((const int *)(OBJ(g_spiralTextures) + 0x14))     /* flare k's texture is g_flareTextures[-k] */
/* ---- textures ---- */
typedef struct { u32 vtable; void *banks[6]; i32 count; } TextureManager;   /* the game's TextureManager (0x83a5e0): six texture banks (the game's class Texture, one per size: TextureBank); a texture id names banks[id / 512], slot id % 512 */
#define tex_bind(manager, slot) GAME_THISFN(tex_bind, 0x4566c0, void, void *, int)(manager, slot)
#define gfx_getWidth() GAME_FN(gfx_getWidth, 0x4685b0, int, void)()
#define gfx_getHeight() GAME_FN(gfx_getHeight, 0x4685c0, int, void)()
#define gfx_fillRect(x0, y0, x1, y1) GAME_FN(gfx_fillRect, 0x46bd60, void, int, int, int, int)(x0, y0, x1, y1)

/* ---- text ---- */
#define text_setColor(r, g, b, a) GAME_FN(text_setColor, 0x44ad30, void, float, float, float, float)(r, g, b, a)
#define text_draw5(x, y, s) GAME_FN(text_draw5, 0x403170, void, int, int, const char *)(x, y, s)
#define text_draw8(x, y, s) GAME_FN(text_draw8, 0x402620, u32, int, int, const char *)(x, y, s)
#define createArena_hitTest(x, y) GAME_FN(createArena_hitTest, 0x404520, int, int, int)(x, y)   /* the new-arena form: the item under (x, y), -1 none */
#define arenaCreate_hitTest(x, y) GAME_FN(arenaCreate_hitTest, 0x4045a0, int, int, int)(x, y)   /* its "leave?" box: the button under (x, y) */
#define arena_drawCustomOption(map) GAME_FN(arena_drawCustomOption, 0x40b550, u32, int)(map)   /* its map preview (the map passed, unused) */
#define roomSettings_hitTest(x, y) GAME_FN(roomSettings_hitTest, 0x432380, int, int, int)(x, y)   /* the room's settings form: the item under (x, y), -1 none */
#define room_drawCustomOption(map) GAME_FN(room_drawCustomOption, 0x43bde0, u32, int)(map)   /* the room form's map preview (the map passed, unused) */
#define setup_unbindKey(key) GAME_FN(setup_unbindKey, 0x420e50, void, int)(key)   /* the key taken off the other bindings */
#define controls_fillPrimaryKeys() GAME_FN(controls_fillPrimaryKeys, 0x421350, void, void)()
#define game_setGameTypeFlags(stage, mode) GAME_THISFN(game_setGameTypeFlags, 0x4732f0, void, Stage *, int)(stage, mode)
#define sys_fatalError(out, format, value) GAME_FN(sys_fatalError, 0x46c710, void, char *, const char *, int)(out, format, value)   /* (one value) a message, then exit */
#define netq_reset(host) GAME_FN(netq_reset, 0x4a8300, void, int)(host)
#define stage_selectActor(stage, i) GAME_THISFN(stage_selectActor, 0x45dfb0, void, Stage *, int)(stage, i)
#define sound_setVolume(v) GAME_FN(sound_setVolume, 0x456de0, int, int)(v)
#define music_setVolumeSetting(v) GAME_FN(music_setVolumeSetting, 0x457140, void, int)(v)
#define scene_resetScores(scene) GAME_THISFN(scene_resetScores, 0x4620e0, void, Scene *)(scene)
#define events_clear(scene, t) GAME_THISFN(events_clear, 0x4629c0, void, Scene *, float)(scene, t)
/* (app/main_loop.c: the replay's frame) */
#define events_age(scene, dt) GAME_THISFN(events_age, 0x462ac0, void, void *, u32)(scene, dt)
/* (app/main_loop.c: the match's frame) */
#define profile_saveProgress() GAME_FN(profile_saveProgress, 0x447010, u32, void)()
#define stage_deactivateActors(stage) GAME_THISFN(stage_deactivateActors, 0x45e1c0, void, void *)(stage)
#define actor_checkDataLoss(stage, a) GAME_THISFN(actor_checkDataLoss, 0x45ee40, u32, void *, int)(stage, a)   /* 0: the parts' data was changed */
#define scene_saveNames(scene) GAME_THISFN(scene_saveNames, 0x4616e0, void, void *)(scene)
#define scene_restoreNames(scene) GAME_THISFN(scene_restoreNames, 0x461730, void, void *)(scene)
#define chat_matchCheatCode(scene, p, text) GAME_THISFN(chat_matchCheatCode, 0x462650, int, void *, int, const char *)(scene, p, text)
#define chat_macro(scene, text, out) GAME_THISFN(chat_macro, 0x462740, int, void *, const char *, char *)(scene, text, out)
#define msg_playerConnected(scene, p) GAME_THISFN(msg_playerConnected, 0x462b50, void, void *, int)(scene, p)
#define msg_chatLine(scene, p, text, team) GAME_THISFN(msg_chatLine, 0x462c30, void, void *, int, const char *, int)(scene, p, text, team)
#define msg_serverEndsGame(scene) GAME_THISFN(msg_serverEndsGame, 0x462f30, void, void *)(scene)
#define msg_userEndsGame(scene) GAME_THISFN(msg_userEndsGame, 0x462f60, void, void *)(scene)
#define msg_fragLimitReached(scene) GAME_THISFN(msg_fragLimitReached, 0x462f90, void, void *)(scene)
#define msg_timeLimitReached(scene) GAME_THISFN(msg_timeLimitReached, 0x462fd0, void, void *)(scene)
#define msg_cheatUsed(scene, p, code) GAME_THISFN(msg_cheatUsed, 0x463030, void, void *, int, int)(scene, p, code)
#define msg_connectionLost(scene) GAME_THISFN(msg_connectionLost, 0x463390, void, void *)(scene)
#define msg_networkUnstable(scene) GAME_THISFN(msg_networkUnstable, 0x4633c0, void, void *)(scene)
#define msg_dataLoss(scene) GAME_THISFN(msg_dataLoss, 0x4633f0, void, void *)(scene)
#define net_clearAnnouncements(scene) GAME_THISFN(net_clearAnnouncements, 0x463480, void, void *)(scene)
#define net_announcePlayerConnected(scene, p, rec) GAME_THISFN(net_announcePlayerConnected, 0x4634e0, void, void *, int, void *)(scene, p, rec)
#define net_announcePlayerQuit(scene, p) GAME_THISFN(net_announcePlayerQuit, 0x463530, void, void *, int)(scene, p)
#define net_announceChatLine(scene, p, text, team) GAME_THISFN(net_announceChatLine, 0x463550, void, void *, int, const char *, int)(scene, p, text, team)
#define net_announceServerEnd(scene) GAME_THISFN(net_announceServerEnd, 0x463670, void, void *)(scene)
#define net_announceFragLimit(scene) GAME_THISFN(net_announceFragLimit, 0x463690, void, void *)(scene)
#define net_announceTimeLimit(scene) GAME_THISFN(net_announceTimeLimit, 0x4636b0, void, void *)(scene)
#define stage_newRound(stage) GAME_THISFN(stage_newRound, 0x470cb0, void, void *)(stage)
#define stage_setViewDistance(stage, x) GAME_THISFN(stage_setViewDistance, 0x4722e0, void, void *, u32)(stage, x)
#define stage_refillLights(stage) GAME_THISFN(stage_refillLights, 0x472310, void, void *)(stage)
#define playerRecord_loadFlag(stage, p) GAME_THISFN(playerRecord_loadFlag, 0x4734d0, int, void *, int)(stage, p)
#define playerRecord_set(stage, p, name, a, b, c, d, e, f, g, h, i, j, k, l, m) GAME_THISFN(playerRecord_set, 0x474210, void, void *, int, \
	const char *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32)(stage, p, name, a, b, c, d, e, f, g, h, i, j, k, l, m)
#define net_sendPlayerInfo(scene, p) GAME_THISFN(net_sendPlayerInfo, 0x48e0f0, void, void *, int)(scene, p)
#define net_sendPlayerState(scene, p) GAME_THISFN(net_sendPlayerState, 0x48e2c0, void, void *, int)(scene, p)
#define net_sendMatchEvent(scene) GAME_THISFN(net_sendMatchEvent, 0x48e680, void, void *)(scene)
#define net_sendFlagPiece(scene, p) GAME_THISFN(net_sendFlagPiece, 0x48e990, void, void *, int)(scene, p)
#define stage_advanceScenePath(stage, dt) GAME_THISFN(stage_advanceScenePath, 0x48fd50, void, void *, u32)(stage, dt)
#define match_escMenu(scene) GAME_THISFN(match_escMenu, 0x49ca70, void, void *)(scene)
#define crt_fprintf(...) GAME_CDECL(0x49f135, int, void *, const char *, ...)(__VA_ARGS__)
#define net_localSlot() GAME_FN(net_localSlot, 0x4a86f0, int, void)()   /* the local player's slot */
#define netq_clearResends() GAME_FN(netq_clearResends, 0x4a8720, void, void)()
#define actor_setPartColor_bits(stage, p, part, a, b, c, d, e, f) GAME_THISFN(actor_setPartColor, 0x474b50, u32, void *, int, int, u32, u32, u32, \
	u32, u32, u32)(stage, p, part, a, b, c, d, e, f)   /* (the six as a float's bits) */
#define view_setAngle(v) GAME_FN(view_setAngle, 0x4686e0, int, u32)(v)   /* the view angle (0x4c4dec) set, a float's bits */
#define msg_kill(scene, victim, killer) GAME_THISFN(msg_kill, 0x4630c0, void, void *, int, int)(scene, victim, killer)
#define flag_uploadAtlas(scene) GAME_THISFN(flag_uploadAtlas, 0x473610, void, void *)(scene)
#define item_update(s, dt) GAME_THISFN(item_update, 0x48ed90, void, void *, u32)(s, dt)
#define stage_updateObjects(s, dt) GAME_THISFN(stage_updateObjects, 0x490d40, void, void *, u32)(s, dt)
#define stage_advanceClocks(stage, dt) GAME_THISFN(stage_advanceClocks, 0x496e40, void, void *, u32)(stage, dt)
#define collision_moveActor(stage, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis) GAME_THISFN(collision_moveActor, 0x471400, int, void *, float, const float *, const float *, u32, u32, float *, float *, float *, float *, u32)(stage, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis)
#define teams_setup(scene) GAME_THISFN(teams_setup, 0x4636d0, void, Scene *)(scene)
#define armcMain_hitTest(x, y) GAME_FN(armcMain_hitTest, 0x40e450, int, int, int)(x, y)   /* the ARM CENTER's item under (x, y), -1 none */
#define quat_fromMatrix(q, m) GAME_THISFN(quat_fromMatrix, 0x47d0f0, void, float *, const float *)(q, m)   /* a rotation matrix to a quaternion */
#define quat_toAxisAngle(out, q) GAME_THISFN(quat_toAxisAngle, 0x47d260, void, float *, const float *)(out, q)
#define factor_addFactorBy(pool, record) GAME_THISFN(factor_addFactorBy, 0x483dd0, void, void *, void *)(pool, record)   /* a 0x2c-byte factor record added */
#define light_computeLayerLightBy(scene, layer, verts, a, b, c, rows, cols) GAME_THISFN(light_computeLayerLightBy, 0x472400, void, void *, const void *, u32, int, int, int, int, int)(scene, layer, verts, a, b, c, rows, cols)
#define bullet_update(scene, i, dt) GAME_THISFN(bullet_update, 0x47a2d0, void, void *, int, int)(scene, i, dt)
#define particle_update(scene, i, dt) GAME_THISFN(particle_update, 0x476410, void, void *, int, int)(scene, i, dt)   /* one effect updated */
#define mapObject_frame(scene, i, dt) GAME_THISFN(mapObject_frame, 0x490440, void, void *, int, int)(scene, i, dt)
#define tex_findByName(manager, name) GAME_THISFN(tex_findByName, 0x4554c0, int, void *, const char *)(manager, name)   /* the item's index by name, < 0 none */
#define crt_fseek(f, offset, origin) GAME_CDECL(0x49e91e, int, void *, int, int)(f, offset, origin)
#define crt_strncpy(to, from, n) GAME_CDECL(0x49ea80, char *, char *, const char *, int)(to, from, n)
#define Mat4_copy(d, s) GAME_FN(Mat4_copy, 0x47d5a0, void, void *, const void *)(d, s)   /* a 4 x 4 matrix copied */
#define Mat4_multiply(out, a, b) GAME_FN(Mat4_multiply, 0x47d380, void, float *, const float *, const float *)(out, a, b)
#define space_getNextFreeNodePtr(space) GAME_THISFN(space_getNextFreeNodePtr, 0x4816c0, void *, void *)(space)
#define space_insertTriangle(space, id, v0, v1, v2, unit, part, i0, i1, i2) GAME_THISFN(space_insertTriangle, 0x481eb0, u8 *, void *, u32, u32, u32, u32, void *, u32, u32, u32, u32)(space, id, v0, v1, v2, unit, part, i0, i1, i2)
#define recorder_openStub(self, a0, a1) GAME_THISFN(recorder_openStub, 0x48b430, void, void *, void *, const void *)(self, a0, a1)   /* (an empty method) */
#define recorder_setPathStub(self, a) GAME_THISFN(recorder_setPathStub, 0x48b440, int, void *, u32)(self, a)                             /* (answers 0) */
#define sound_playFile(name, volume) GAME_FN(sound_playFile, 0x457080, u32, const char *, int)(name, volume)
#define actor_setupFromParts(scene, i, x, y, parts) GAME_THISFN(actor_setupFromParts, 0x457330, void, void *, int, u32, u32, u32)(scene, i, x, y, parts)
#define particle_init(system, i, desc) GAME_THISFN(particle_init, 0x475070, void, void *, int, u32)(system, i, desc)
#define tex_allocIdBy(manager, name, a, b, c, d, e, f, g) GAME_THISFN(tex_allocIdBy, 0x4555b0, int, void *, u32, u32, u32, u32, u32, u32, u32, u32)(manager, name, a, b, c, d, e, f, g)
#define actor_setPartColor(scene, p, part, a, b, c, d, e, f) GAME_THISFN(actor_setPartColor, 0x474b50, u32, void *, int, int, float, float, float, float, float, float)(scene, p, part, a, b, c, d, e, f)
#define actor_processFrame(scene, i, dt) GAME_THISFN(actor_processFrame, 0x4580b0, void, void *, int, float)(scene, i, dt)
#define script_processTriggers(scene) GAME_THISFN(script_processTriggers, 0x483640, void, void *)(scene)
#define bullet_init(scene, slot, a1, a2, a3, a4, a5) GAME_THISFN(bullet_init, 0x479b40, void, void *, int, u32, u32, u32, u32, u32)(scene, slot, a1, a2, a3, a4, a5)
#define object_initObjectBy(scene, slot, type) GAME_THISFN(object_initObjectBy, 0x48fee0, void, void *, int, u32)(scene, slot, type)
#define sys_errorMessage(out, format, a, b) GAME_FN(sys_errorMessage, 0x46c5f0, void, char *, const char *, int, int)(out, format, a, b)
#define ObjectList_load(self, a, b, c, d, e, f, g, h, i, j, limit) GAME_THISFN(ObjectList_load, 0x46f4e0, void, void *, void *, void *, u32, void *, u32, void *, u32, u32, u32, void *, u32)(self, a, b, c, d, e, f, g, h, i, j, limit)
#define shape_getByName(cache, name, flag) GAME_THISFN(shape_getByName, 0x466dc0, u32, void *, const char *, int)(cache, name, flag)
#define sys_fatalErrorN(out, ...) GAME_FN(sys_fatalError, 0x46c710, void, char *, const char *, ...)((char *)(out), __VA_ARGS__)   /* (a format and any values) */
#define script_processCommandBy(scene, a, i, b) GAME_THISFN(script_processCommandBy, 0x483770, void, void *, int, int, int)(scene, a, i, b)
#define space_resetPlanes(space) GAME_THISFN(space_resetPlanes, 0x481520, int, void *)(space)
#define space_resetNodes(space) GAME_THISFN(space_resetNodes, 0x481630, int, void *)(space)
#define space_resetUnits(space) GAME_THISFN(space_resetUnits, 0x481760, void, void *)(space)
#define space_resetBlocks(space) GAME_THISFN(space_resetBlocks, 0x481860, int, void *)(space)
#define image_tryOpen(image, path) GAME_THISFN(image_tryOpen, 0x46cdc0, int, void *, const char *)(image, path)   /* a BMP opened */
#define image_copyTo(image, out, w, h, bpp, a, b, c, d, w2, h2, e) GAME_THISFN(image_copyTo, 0x46ce80, int, void *, void *, int, int, int, int, int, int, int, int, int, int)(image, out, w, h, bpp, a, b, c, d, w2, h2, e)
#define BMPRGBFile_close(self) GAME_THISFN(BMPRGBFile_close, 0x46ce50, u32, void *)(self)   /* the object's file closed */
#define map_loadWayPointInfoFrom(scene, f) GAME_THISFN(map_loadWayPointInfoFrom, 0x48b4a0, void, void *, void *)(scene, f)
#define map_loadTriggerInfoFrom(scene, f) GAME_THISFN(map_loadTriggerInfoFrom, 0x48b530, void, void *, void *)(scene, f)
#define room_keepText() GAME_FN(room_keepText, 0x44aee0, void, void)()   /* the room's text kept */
#define log_message(a, b, c, ...) GAME_FN(log_message, 0x470fc0, void, int, int, int, const char *, ...)(a, b, c, __VA_ARGS__)   /* a message to the log hook */
#define map_readCommands(self, f) GAME_THISFN(map_readCommands, 0x48b460, u32, void *, void *)(self, f)
#define file_writeScrambled(p, size, count, f) GAME_FN(file_writeScrambled, 0x46cc30, u32, const void *, u32, u32, void *)(p, size, count, f)   /* fwrite, scrambled */
#define net_sendPacketData(size, data) GAME_FN(net_sendPacketData, 0x4a8360, u32, int, void *)(size, data)
#define glWindow_setupPixelFormat(dc) GAME_FN(glWindow_setupPixelFormat, 0x467e60, int, void *)(dc)
#define glWindow_restoreDisplayMode() GAME_FN(glWindow_restoreDisplayMode, 0x468050, void, void)()
#define tex_loadImage(textures, i) GAME_THISFN(tex_loadImage, 0x455aa0, void, void *, int)(textures, i)
#define tex_applyTintMask(textures, i) GAME_THISFN(tex_applyTintMask, 0x456470, void, void *, int)(textures, i)
#define tex_upload(textures, id, mode) GAME_THISFN(tex_upload, 0x456520, void, void *, u32, int)(textures, id, mode)
#define glPixelStorei(pname, v) IMPORT(0x4a9268, void, u32, int)(pname, v)
#define glTexParameterf_bits(target, pname, bits) IMPORT(0x4a9260, void, u32, u32, u32)(target, pname, bits)   /* (the float as its bits) */
#define glTexImage2D(target, level, format, w, h, border, layout, type, data) IMPORT(0x4a91e4, void, u32, int, int, int, int, int, u32, u32, const void *)(target, level, format, w, h, border, layout, type, data)
#define setupSlider_hitTest(x, y) GAME_FN(setupSlider_hitTest, 0x420730, int, int, int)(x, y)   /* the slider's part under the cursor */
#define actor_updatePart(scene, i, slot, value) GAME_THISFN(actor_updatePart, 0x45e600, void, void *, int, int, u32)(scene, i, slot, value)
#define gluBuild2DMipmaps(target, components, w, h, format, type, data) IMPORT(0x4a9044, int, u32, int, int, int, u32, u32, const void *)(target, components, w, h, format, type, data)
#define crt_tolower(c) GAME_CDECL(0x49fdaf, int, int)(c)
#define shape_read(shape, f, mem, size) GAME_THISFN(shape_read, 0x466120, void, void *, void *, void *, int)(shape, f, mem, size)
#define model_loadObjFormatFrom(shape, f, mem, size) GAME_THISFN(model_loadObjFormatFrom, 0x464db0, void, void *, void *, void *, int)(shape, f, mem, size)
#define skel_loadFromFile(sk, f, mem, size) GAME_THISFN(skel_loadFromFile, 0x46aa10, void, void *, void *, void *, int)(sk, f, mem, size)
#define skel_loadAseFrom(sk, f, mem, size) GAME_THISFN(skel_loadAseFrom, 0x469b90, void, void *, void *, void *, int)(sk, f, mem, size)
#define crt_strupr(s) GAME_CDECL(0x49fab5, char *, char *)(s)
#define text_findWord(text, word, exact) GAME_FN(text_findWord, 0x454d90, const char *, const char *, const char *, int)(text, word, exact)
#define file_existsf(path) GAME_FN(file_existsf, 0x46ca70, int, const char *)(path)
#define space_collideAt(grid, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	GAME_THISFN(space_collideAt, 0x482aa0, int, void *, u32, float *, float *, u32, u32, u32, u32, u32, u32, u32, u32)(grid, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define image_initBy(image, path) GAME_THISFN(image_initBy, 0x46cd00, void *, void *, const char *)(image, path)   /* a 24-bit BMP opened */
#define ShapeManager_releaseModels(models) GAME_THISFN(ShapeManager_releaseModels, 0x467520, int, void *)(models)   /* the shape cache emptied */
#define SkeletonManager_releaseSkeletons(skels) GAME_THISFN(SkeletonManager_releaseSkeletons, 0x46b7f0, int, void *)(skels)   /* the skeleton cache emptied */
#define path_stripExtension(src, dst) GAME_FN(path_stripExtension, 0x46cad0, void, const char *, char *)(src, dst)
#define stage_clearMapObjects(stage) GAME_THISFN(stage_clearMapObjects, 0x490d10, void, void *)(stage)
#define object_addObjectBy(scene, type) GAME_THISFN(object_addObjectBy, 0x490c50, int, void *, const void *)(scene, type)
#define ObjectList_relight(list, factors, lights) GAME_THISFN(ObjectList_relight, 0x46f7a0, void, void *, u32, u32)(list, factors, lights)
#define glTranslatef(x, y, z) IMPORT(0x4a9214, void, float, float, float)(x, y, z)
#define app_parseCommandLine(cmd) GAME_FN(app_parseCommandLine, 0x43f160, void, const char *)(cmd)
#define app_readLauncherCheck() GAME_FN(app_readLauncherCheck, 0x41e260, u32, void)()
#define reg_readStartMode() GAME_FN(reg_readStartMode, 0x43f770, u32, void)()
#define editField_readTyping() GAME_FN(editField_readTyping, 0x43f980, void, void)()   /* a frame */
#define app_frame() GAME_FN(app_frame, 0x4202d0, void, void)()   /* the fade step */
#define app_init(inst, show) GAME_FN(app_init, 0x43fcc0, int, void *, int)(inst, show)
#define space_testSphere(grid, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	GAME_THISFN(space_testSphere, 0x482e30, int, void *, u32, const float *, const float *, u32, u32, u32, u32, u32, u32, u32, void *, int)(grid, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define array_recordAt(i, base, stride) GAME_FN(array_recordAt, 0x46cbc0, int, int, int, int)(i, base, stride)   /* record i of an array (none when negative) */
#define collisionTri_sweepSphere(rec, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis) \
	GAME_THISFN(collisionTri_sweepSphere, 0x47dd90, int, void *, float, const float *, const float *, u32, float *, float *, float *, float *, u32)(rec, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis)
#define space_collideBlock(node, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	GAME_THISFN(space_collideBlock, 0x4804b0, int, void *, u32, const float *, const float *, u32, float *, u32, u32, u32, u32, u32, u32)(node, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define space_itemMeetsBox(item, low, high, margin) GAME_THISFN(space_itemMeetsBox, 0x47fce0, int, void *, const float *, const float *, u32)(item, low, high, margin)   /* the item meets the box (widened) */
#define space_getNextFreeBlockPtrBy(space, low, high) GAME_THISFN(space_getNextFreeBlockPtrBy, 0x4818e0, u8 *, void *, const float *, const float *)(space, low, high)
#define space_freeNode(space, node) GAME_THISFN(space_freeNode, 0x481730, void, void *, void *)(space, node)   /* a node back to the free list */
#define space_freeBlock(space, block) GAME_THISFN(space_freeBlock, 0x481980, void, void *, void *)(space, block)   /* a block back to the free list */
#define space_insertItem(space, block, item, depth) GAME_THISFN(space_insertItem, 0x481ae0, int, void *, void *, void *, int)(space, block, item, depth)
#define angle_wrap(degrees) GAME_FN(angle_wrap, 0x46c100, long double, float)(degrees)   /* an angle wrapped into a turn (in ST0) */
#define shape_setTextureDir(shape, dir, mode, h1, s1, v1, h2, s2, v2) GAME_THISFN(shape_setTextureDir, 0x467580, void, void *, const char *, int, u32, u32, u32, u32, u32, u32)(shape, dir, mode, h1, s1, v1, h2, s2, v2)
#define space_getNextFreePlanePtr(space) GAME_THISFN(space_getNextFreePlanePtr, 0x4815c0, u8 *, void *)(space)
#define collisionTri_setup(plane, id, v0, v1, v2, unit, part, i0, i1, i2) GAME_THISFN(collisionTri_setup, 0x47db60, void, void *, u32, const float *, const float *, const float *, u32, u32, u32, u32, u32)(plane, id, v0, v1, v2, unit, part, i0, i1, i2)   /* the triangle's planes */
#define array_indexOf(record, base, stride) GAME_FN(array_indexOf, 0x46cba0, int, void *, int, int)(record, base, stride)   /* a record's index in its array */
#define stage_triggerActionNone(scene, v) GAME_THISFN(stage_triggerActionNone, 0x483ce0, void, void *, u32)(scene, v)
#define actor_applySpawnRecord(scene, i, record) GAME_THISFN(actor_applySpawnRecord, 0x45de20, int, void *, int, void *)(scene, i, record)
#define camera_setTarget(scene, a, b, c) GAME_THISFN(camera_setTarget, 0x45dff0, void, void *, u32, u32, u32)(scene, a, b, c)
#define script_pushMessage(scene, a, b, c, d) GAME_THISFN(script_pushMessage, 0x48fc40, void, void *, u32, u32, u32, u32)(scene, a, b, c, d)
#define script_runScpFile(scene, name, v) GAME_THISFN(script_runScpFile, 0x48fce0, void, void *, const char *, u32)(scene, name, v)
#define object_setAnimation(scene, i, name, a, b) GAME_THISFN(object_setAnimation, 0x490df0, void, void *, u32, const char *, u32, u32)(scene, i, name, a, b)
#define object_activate(scene, i) GAME_THISFN(object_activate, 0x490ee0, void, void *, u32)(scene, i)
#define object_deactivate(scene, i) GAME_THISFN(object_deactivate, 0x490f30, void, void *, u32)(scene, i)
#define playerRecord_setFromMapPlayer(scene, p, record) GAME_THISFN(playerRecord_setFromMapPlayer, 0x4742f0, void, void *, int, void *)(scene, p, record)   /* a player set up from its map record */
#define skelDat_getItemFileBy(name) GAME_FN(skelDat_getItemFileBy, 0x46b140, void *, const char *)(name)   /* the item's file in the skeleton dat */
#define skel_loadFrom(sk, path, mem, size) GAME_THISFN(skel_loadFrom, 0x4699d0, void, void *, const char *, void *, int)(sk, path, mem, size)
#define shape_findDatEntry(name) GAME_FN(shape_findDatEntry, 0x466d60, void *, const char *)(name)   /* the shape's file in the shape dat */
#define model_loadFrom(shape, path, mem, size) GAME_THISFN(model_loadFrom, 0x464bf0, void, void *, const char *, void *, int)(shape, path, mem, size)
#define shape_bindTextureBy(shape, textures, a, b, c, d, e, f, g) GAME_THISFN(shape_bindTextureBy, 0x466430, void, void *, void *, u32, u32, u32, u32, u32, u32, u32)(shape, textures, a, b, c, d, e, f, g)
#define stage_resetLights(scene) GAME_THISFN(stage_resetLights, 0x4723e0, void, void *)(scene)
#define stage_clearBullets(scene) GAME_THISFN(stage_clearBullets, 0x47cfd0, void, void *)(scene)
#define stage_clearProjectiles(scene) GAME_THISFN(stage_clearProjectiles, 0x479a60, void, void *)(scene)
#define stage_resetMatrixAndPoints(scene) GAME_THISFN(stage_resetMatrixAndPoints, 0x48fe10, void, void *)(scene)
#define stage_clearMessages(scene) GAME_THISFN(stage_clearMessages, 0x48fc30, void, void *)(scene)
#define stage_initSpaceOneCell(scene) GAME_THISFN(stage_initSpaceOneCell, 0x471010, void, void *)(scene)
#define texRecord_init(record, name, id, flags, h1, s1, v1, h2, s2, v2) GAME_THISFN(texRecord_init, 0x454e60, void, void *, const char *, int, u32, u32, u32, u32, u32, u32, u32)(record, name, id, flags, h1, s1, v1, h2, s2, v2)   /* a texture record set up */
#define tex_textureFileExist(tm, name) GAME_THISFN(tex_textureFileExist, 0x4557e0, int, void *, const char *)(tm, name)
#define match_startRound(scene) GAME_THISFN(match_startRound, 0x49df10, void, void *)(scene)
#define scene_averageFrameTime(scene) GAME_THISFN(scene_averageFrameTime, 0x461210, long double, void *)(scene)   /* (answers in ST0) */
#define match_combatInput(scene) GAME_THISFN(match_combatInput, 0x49d290, void, void *)(scene)
#define match_frame(scene) GAME_THISFN(match_frame, 0x4988e0, void, void *)(scene)
#define hud_pass(scene) GAME_THISFN(hud_pass, 0x4982f0, void, void *)(scene)
#define collision_rayTrace(scene, from, to, out) GAME_THISFN(collision_rayTrace, 0x471740, int, void *, const float *, const float *, void *)(scene, from, to, out)   /* 0: nothing in the way */
#define crt_ftell(f) GAME_CDECL(0x49efdd, long, void *)(f)
#define shape_computeBounds(shape) GAME_THISFN(shape_computeBounds, 0x4666d0, void, void *)(shape)
#define FUN_0046c100_bits(bits) GAME_FN(angle_wrap, 0x46c100, long double, u32)(bits)   /* (the angle passed as its bits) */
#define space_buildUnits(space, id, shape, matrix) GAME_THISFN(space_buildUnits, 0x4823c0, u32, void *, int, void *, const float *)(space, id, shape, matrix)
#define space_getNextFreeUnitPtr(space) GAME_THISFN(space_getNextFreeUnitPtr, 0x4817f0, u32 *, void *)(space)
#define space_addUnitPlanes(space, id, unit, part, i0, i1, i2, v0, v1, v2) GAME_THISFN(space_addUnitPlanes, 0x482320, void, void *, u32, void *, u32, u32, u32, u32, const float *, const float *, const float *)(space, id, unit, part, i0, i1, i2, v0, v1, v2)
#define space_transformPoint(out, m, v) GAME_FN(space_transformPoint, 0x482a40, void, float *, const float *, const float *)(out, m, v)   /* a point through a matrix */
#define space_traceBlock(node, p0, p1, hit, dist, subs, nsubs) GAME_THISFN(space_traceBlock, 0x4809f0, int, void *, const float *, const float *, u32, float *, u32, u32)(node, p0, p1, hit, dist, subs, nsubs)
#define Vec3_rotateAxis(v, axis, angle) GAME_THISFN(Vec3_rotateAxis, 0x4677c0, void, float *, int, int)(v, axis, angle)   /* about axis 0 / 1 / 2 by tenths of a degree */
#define factors_addAmbient(self, colour) GAME_THISFN(factors_addAmbient, 0x483e90, void, void *, const void *)(self, colour)
#define factors_addDirectional(self, colour, dir) GAME_THISFN(factors_addDirectional, 0x483ec0, void, void *, const void *, const void *)(self, colour, dir)
#define space_initBy(space, planes, nodes, units, blocks, cells, mem, size) GAME_THISFN(space_initBy, 0x4813e0, void, void *, int, int, int, int, int, void *, int)(space, planes, nodes, units, blocks, cells, mem, size)
#define shape_initBy(self, dir, n, a, extra, mem, size) GAME_THISFN(shape_initBy, 0x466a60, void, void *, const char *, int, u32, int, void *, int)(self, dir, n, a, extra, mem, size)
#define skelSet_setup(self, dir, n, a, extra, mem, size) GAME_THISFN(skelSet_setup, 0x46aeb0, void, void *, const char *, int, u32, int, void *, int)(self, dir, n, a, extra, mem, size)
#define scene_resetActors(scene) GAME_THISFN(scene_resetActors, 0x470a70, void, void *)(scene)
#define scene_reset(scene) GAME_THISFN(scene_reset, 0x470ad0, void, void *)(scene)
#define effect_initShapes(scene) GAME_THISFN(effect_initShapes, 0x48ec20, void, void *)(scene)
#define stage_setFolders(s, a1, a2, a3, a4, a5, a6, a7, a8, a9) GAME_THISFN(stage_setFolders, 0x470de0, void, void *, u32, u32, u32, u32, u32, u32, u32, u32, u32)(s, a1, a2, a3, a4, a5, a6, a7, a8, a9)
#define particle_spawn(scene, record) GAME_THISFN(particle_spawn, 0x479950, void, void *, const void *)(scene, record)
/* (match/weapons.c: a bullet's frame) */
#define sound_play3D(index, pos, listener, side, range) GAME_FN(sound_play3D, 0x456ed0, void, int, const void *, const void *, const void *, u32)(index, pos, listener, side, range)
#define actor_takeDamage(scene, attacker, target, mode, damage, kind, value) GAME_THISFN(actor_takeDamage, 0x460000, void, void *, int, int, int, int, int, int)(scene, attacker, target, mode, damage, kind, value)
#define bullet_free(stage, b) GAME_THISFN(bullet_free, 0x47cf10, void, void *, int)(stage, b)
#define math_segmentSphere(p0, p1, dir, centre, radius, hit, t) GAME_FN(math_segmentSphere, 0x47d9d0, int, const float *, const float *, const float *, const float *, float, float *, float *)(p0, p1, dir, centre, radius, hit, t)   /* 1: the segment meets the sphere */
#define skel_applyPose(sk, out, bone, t) GAME_THISFN(skel_applyPose, 0x46ab30, void, void *, void *, int, u32)(sk, out, bone, t)
/* (match/actor_frame.c: an actor's frame) */
#define actor_updateHead(stage, i) GAME_THISFN(actor_updateHead, 0x45e1f0, void, void *, int)(stage, i)
#define actor_updateBody(stage, i) GAME_THISFN(actor_updateBody, 0x45e2c0, void, void *, int)(stage, i)
#define actor_updateArms(stage, i) GAME_THISFN(actor_updateArms, 0x45e390, void, void *, int)(stage, i)
#define actor_updateLegs(stage, i) GAME_THISFN(actor_updateLegs, 0x45e460, void, void *, int)(stage, i)
#define actor_updateBooster(stage, i) GAME_THISFN(actor_updateBooster, 0x45e530, void, void *, int)(stage, i)
#define actor_prevWeapon(stage, i) GAME_THISFN(actor_prevWeapon, 0x45e910, void, void *, int)(stage, i)   /* the previous weapon */
#define actor_nextWeapon(stage, i) GAME_THISFN(actor_nextWeapon, 0x45e9e0, void, void *, int)(stage, i)   /* the next weapon */
#define actor_clearInput(stage, i) GAME_THISFN(actor_clearInput, 0x45eab0, void, void *, int)(stage, i)   /* the input cleared */
#define actor_pickRandomWeapon(stage, i) GAME_THISFN(actor_pickRandomWeapon, 0x45edb0, void, void *, int)(stage, i)
#define actor_pickPathPoint(stage, i) GAME_THISFN(actor_pickPathPoint, 0x460270, void, void *, int)(stage, i)
#define angle_turn(from, to) GAME_FN(angle_turn, 0x46c140, long double, u32, u32)(from, to)   /* the turn from one angle to another */
#define angle_stepTowards(from, to, t) GAME_FN(angle_stepTowards, 0x46c1c0, long double, u32, u32, u32)(from, to, t)   /* an angle part way */
#define anim_setFrame(part, k, value) GAME_THISFN(anim_setFrame, 0x46f770, void, void *, int, u32)(part, k, value)
#define skel_poseBones(part, m) GAME_THISFN(skel_poseBones, 0x46f8c0, void, void *, void *)(part, m)
#define partList_bindTextures(part) GAME_THISFN(partList_bindTextures, 0x46fed0, void, void *)(part)
#define bullet_spawn(stage, slot, owner, target, rec, n) GAME_THISFN(bullet_spawn, 0x47ce50, int, void *, int, int, int, void *, int)(stage, slot, owner, target, rec, n)
#define collisionTri_traceSegment(rec, p0, p1, hit, t) GAME_THISFN(collisionTri_traceSegment, 0x47fb80, int, void *, const float *, const float *, float *, float *)(rec, p0, p1, hit, t)
#define partList_queue(list, vv, lights, tint, a4, a5, a6) GAME_THISFN(partList_queue, 0x46fd20, int, void *, void *, void *, u8 *, int, u32, u32)(list, vv, lights, tint, a4, a5, a6)
#define tex_getItemFileBy(manager, name) GAME_THISFN(tex_getItemFileBy, 0x455550, void *, void *, const char *)(manager, name)   /* the dat file at the item's data */
#define ptx_initTables() GAME_FN(ptx_initTables, 0x46ea00, void, void)()
#define ptx_open(path, out, bpp, w, h) GAME_FN(ptx_open, 0x46eb00, int, const char *, void *, int *, int *, int *)(path, out, bpp, w, h)
#define ptx_decode(file, out, bpp, w, h) GAME_FN(ptx_decode, 0x46ed80, int, void *, void *, int *, int *, int *)(file, out, bpp, w, h)
#define input_asyncKeyPressed(key) GAME_FN(input_asyncKeyPressed, 0x487bd0, int, int)(key)
#define net_sendGamePacket(scene, kind) GAME_THISFN(net_sendGamePacket, 0x48dbf0, void, void *, int)(scene, kind)
#define net_processGamePacket(scene, from, size, data) GAME_THISFN(net_processGamePacket, 0x48c830, void, void *, int, int, void *)(scene, from, size, data)
#define netq_poll() GAME_FN(netq_poll, 0x4a8350, void, void)()   /* the network's incoming messages gathered */
#define netq_receive(from, size, data) GAME_FN(netq_receive, 0x4a8450, int, int *, int *, void *)(from, size, data)   /* the next message: 0 none, 1 a game packet */
#define net_isClient() GAME_FN(net_isClient, 0x4a86d0, int, void)()   /* online as a client? */
#define netq_online() GAME_FN(netq_online, 0x4a86c0, int, void)()   /* (g_netOnline) */
#define netq_resends() GAME_FN(netq_resends, 0x4a8730, int, void)()
#define map_loadGroundInfoFrom(stage, name) GAME_THISFN(map_loadGroundInfoFrom, 0x48b9d0, int, void *, const char *)(stage, name)
#define map_loadObjectInfoFrom(stage, name, a) GAME_THISFN(map_loadObjectInfoFrom, 0x48b710, void, void *, const char *, int)(stage, name, a)
#define collision_initVolume(stage, x, y, z, cell, depth, a) GAME_THISFN(collision_initVolume, 0x471040, void, void *, u32, u32, u32, u32, int, int)(stage, x, y, z, cell, depth, a)
#define map_loadPlayInfoFrom(stage, name) GAME_THISFN(map_loadPlayInfoFrom, 0x4876b0, void, void *, const char *)(stage, name)
#define map_loadMissionInfoFrom(stage, name) GAME_THISFN(map_loadMissionInfoFrom, 0x48b5c0, void, void *, const char *)(stage, name)
#define map_loadActorInfoFrom(stage, name) GAME_THISFN(map_loadActorInfoFrom, 0x474550, void, void *, const char *)(stage, name)
#define font_penDraw(x, y, a, text) GAME_FN(font_penDraw, 0x46bb00, void, int, int, int, const char *)(x, y, a, text)
#define space_traceNodes(grid, p0, p1, hit, subs, nsubs) GAME_THISFN(space_traceNodes, 0x483060, u32, void *, const float *, const float *, void *, void *, int)(grid, p0, p1, hit, subs, nsubs)
#define match_resetInputState(scene) GAME_THISFN(match_resetInputState, 0x461f10, void, void *)(scene)
#define net_matchOver() GAME_FN(net_matchOver, 0x4a86e0, int, void)()   /* the network says the match is over? */
#define crt_fread(p, size, count, f) GAME_CDECL(0x49e836, u32, void *, u32, u32, void *)(p, size, count, f)
#define Light_read(lights, f) GAME_THISFN(Light_read, 0x483d70, void, void *, void *)(lights, f)   /* the lights read */
#define math_triangleNormal(out, a, b, c) GAME_FN(math_triangleNormal, 0x4679a0, float *, float *, const float *, const float *, const float *)(out, a, b, c)   /* a triangle's normal */
#define ground_computeLighting(scene, layer) GAME_THISFN(ground_computeLighting, 0x4728e0, void, void *, void *)(scene, layer)   /* a layer's light map */
#define stage_buildMeshDrawRecords(scene) GAME_THISFN(stage_buildMeshDrawRecords, 0x497a90, void, void *)(scene)   /* the layer meshes */
#define crt_atof(s) GAME_CDECL(0x49fe7a, double, const char *)(s)
#define axisAngle_combine(out, a, b) GAME_FN(axisAngle_combine, 0x47d320, float *, float *, const float *, const float *)(out, a, b)   /* two rotations combined */
#define Mat4_transpose(out, m) GAME_FN(Mat4_transpose, 0x47d830, void, float *, const float *)(out, m)   /* copied transposed */
#define axisAngle_fromMatrix(out, m) GAME_THISFN(axisAngle_fromMatrix, 0x47d2f0, u32, float *, const float *)(out, m)   /* matrix -> (angle, axis) */
#define input_asyncKeyDown(vk) GAME_FN(input_asyncKeyDown, 0x487ba0, int, int)(vk)
#define input_setCursorPos(x, y) GAME_FN(input_setCursorPos, 0x487c80, void, int, int)(x, y)
#define input_getCursorPos() GAME_FN(input_getCursorPos, 0x487c30, const int *, void)()
#define actor_setInput(stage, a, b, c, d, e, f, g, h, i, j, k, l, m) GAME_THISFN(actor_setInput, 0x45eb20, void, void *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32)(stage, a, b, c, d, e, f, g, h, i, j, k, l, m)   /* the local actor's controls */
#define view_nearPlane() GAME_FN(view_nearPlane, 0x4686f0, float, void)()
#define actor_updateAll(stage, dt) GAME_THISFN(actor_updateAll, 0x45e0c0, void, void *, u32)(stage, dt)
#define bullet_updateAll(stage, dt) GAME_THISFN(bullet_updateAll, 0x47d000, void, void *, u32)(stage, dt)
#define stage_updateEffects(stage, dt) GAME_THISFN(stage_updateEffects, 0x479a90, void, void *, u32)(stage, dt)
#define ViewVolume_addSegment(view, colour, p0, p1, a) GAME_THISFN(ViewVolume_addSegment, 0x485120, void, void *, const void *, const float *, const float *, int)(view, colour, p0, p1, a)   /* a line */
#define setupOptions_hitTest(x, y) GAME_FN(setupOptions_hitTest, 0x4206b0, int, int, int)(x, y)   /* the options dialog's item under (x, y), -1 none */
#define text_draw16(x, y, s) GAME_FN(text_draw16, 0x4028b0, void, int, int, const char *)(x, y, s)
#define text_draw32(x, y, s) GAME_FN(text_draw32, 0x402c90, void, int, int, const char *)(x, y, s)
/* the box passes: text centred between x0 and x1 */
#define text_drawCentred5(x0, y, x1, s) GAME_FN(text_drawCentred5, 0x403210, void, int, int, int, const char *)(x0, y, x1, s)
#define text_draw8b(x0, y, x1, s) GAME_FN(text_draw8b, 0x402740, void, int, int, int, const char *)(x0, y, x1, s)
#define text_drawBox16(x0, y, x1, s) GAME_FN(text_drawBox16, 0x4029d0, u32, int, int, int, const char *)(x0, y, x1, s)
#define text_drawCentred32(x0, y, x1, s) GAME_FN(text_drawCentred32, 0x402db0, void, int, int, int, const char *)(x0, y, x1, s)
#define text_drawCentred(x0, y, x1, s, size) GAME_FN(text_drawCentred, 0x44ae10, void, int, int, int, const char *, int)(x0, y, x1, s, size)
#define text_drawSized(x, y, s, size) GAME_FN(text_drawSized, 0x44ad60, void, int, int, const char *, int)(x, y, s, size)

/* ---- HUD ---- */
#define hud_fillRect(x0, y0, x1, y1) GAME_FN(hud_fillRect, 0x4950a0, void, int, int, int, int)(x0, y0, x1, y1)
#define hud_drawRectOutline(x0, y0, x1, y1) GAME_FN(hud_drawRectOutline, 0x46bd00, void, int, int, int, int)(x0, y0, x1, y1)   /* a rectangle's outline */
/* a team's slot in teamScores (scene_teamIdAt) and which side of the box it is on (scene_teamSide) */
#define scene_teamIdAt(scene, team) GAME_THISFN(scene_teamIdAt, 0x463780, int, Scene *, int)(scene, team)
#define scene_teamSide(scene, team) GAME_THISFN(scene_teamSide, 0x463740, int, void *, int)(scene, team)   /* the team's slot, given one if new */
#define scene_findTeam(scene, team) GAME_THISFN(scene_findTeam, 0x463710, int, Scene *, int)(scene, team)   /* the team's slot or -1 */
#define hud_drawEmblem(scene, emblem, x, y) GAME_THISFN(hud_drawEmblem, 0x4922c0, void, Scene *, int, int, int)(scene, emblem, x, y)
#define hud_drawFlag(scene, player, x, y) GAME_THISFN(hud_drawFlag, 0x4924d0, void, Scene *, int, int, int)(scene, player, x, y)
#define hud_drawIcon(scene, x, y, icon) GAME_THISFN(hud_drawIcon, 0x496820, void, Scene *, int, int, int)(scene, x, y, icon)

/* ---- main loop and match ---- */
#define main_loop() GAME_FN(main_loop, 0x420280, void, void)()
#define game_postMatch() GAME_FN(game_postMatch, 0x420100, void, void)()
#define music_loopIfEnded() GAME_FN(music_loopIfEnded, 0x4572b0, void, void)()
#define gfx_swapBuffers() GAME_FN(gfx_swapBuffers, 0x4685d0, void, void)()
#define match_frameByState(scene) GAME_THISFN(match_frameByState, 0x462050, int, Scene *)(scene)
#define game_processLoadingMode(scene) GAME_THISFN(game_processLoadingMode, 0x468750, int, Scene *)(scene)
#define match_playFrame(scene) GAME_THISFN(match_playFrame, 0x48b200, int, Scene *)(scene)
#define match_freeCamFrame(scene) GAME_THISFN(match_freeCamFrame, 0x48a370, int, Scene *)(scene)
#define replay_frame(scene) GAME_THISFN(replay_frame, 0x487f00, int, Scene *)(scene)

/* ---- input ---- */
#define input_reacquireKeyboard() GAME_FN(input_reacquireKeyboard, 0x4012c0, void, void)()
#define input_updateMouse() GAME_FN(input_updateMouse, 0x445c60, void, void)()
#define input_justPressed(key) GAME_FN(input_justPressed, 0x401600, int, int)(key)
#define app_setDataPaths() GAME_FN(app_setDataPaths, 0x43f5a0, void, void)()
#define data_loadMessages() GAME_FN(data_loadMessages, 0x42b3e0, void, void)()
#define input_initDikCodes() GAME_FN(input_initDikCodes, 0x42fd40, void, void)()
#define cfg_init() GAME_FN(cfg_init, 0x42eca0, void, void)()
#define app_screenSizeForMode() GAME_FN(app_screenSizeForMode, 0x43f640, void, void)()
#define app_registerWindowClassEx(wc) GAME_FN(app_registerWindowClassEx, 0x43f840, int, void *)(wc)   /* the class registered on old Windows */
#define app_startupLoad(inst) GAME_FN(app_startupLoad, 0x430400, int, void *)(inst)
#define app_reportDisplayModeError(code) GAME_FN(app_reportDisplayModeError, 0x42ef30, int, int)(code)   /* a start-up problem reported */
#define app_readCurrentDirectory() GAME_FN(app_readCurrentDirectory, 0x43f580, u32, void)()
#define app_setDisplayMode(w, h, flags, bits) GAME_FN(app_setDisplayMode, 0x42eed0, int, int, int, u32, int)(w, h, flags, bits)   /* the display mode set (src/app/win32.c) */
#define armc_partsPageKeys() GAME_FN(armc_partsPageKeys, 0x4101e0, void, void)()   /* the arm screen's keys, page 1 */
#define armc_weaponsPageKeys() GAME_FN(armc_weaponsPageKeys, 0x410500, void, void)()   /* page 2 */
#define armc_colourPageKeys() GAME_FN(armc_colourPageKeys, 0x410810, void, void)()   /* page 3 */

/* ---- menus: the screens' frames and key handlers ---- */
#define menu_frame() GAME_FN(menu_frame, 0x41fa40, void, void)()
#define menu_frameInput() GAME_FN(menu_frameInput, 0x445e40, void, void)()
#define menu_processKeys() GAME_FN(menu_processKeys, 0x4319d0, void, void)()
#define menu_frameBegin() GAME_FN(menu_frameBegin, 0x41f820, void, void)()
#define menuState100_intro() GAME_FN(menuState100_intro, 0x41f540, void, void)()
#define menuState200_title() GAME_FN(menuState200_title, 0x41f8d0, void, void)()   /* the title screen (200) */
#define menuState210_frame() GAME_FN(menuState210_frame, 0x44f860, void, void)()
#define menuState300_frame() GAME_FN(menuState300_frame, 0x443530, void, void)()
#define menuState400_frame() GAME_FN(menuState400_frame, 0x40d450, void, void)()
#define menuState500_missionSelect() GAME_FN(menuState500_missionSelect, 0x44aa40, void, void)()
#define menuState600_setup() GAME_FN(menuState600_setup, 0x427920, void, void)()
#define menuState700_armCenter() GAME_FN(menuState700_armCenter, 0x41e040, void, void)()
#define menuState800_gameRoom() GAME_FN(menuState800_gameRoom, 0x43ef70, void, void)()
#define menuState900_skirmishSetup() GAME_FN(menuState900_skirmishSetup, 0x445be0, void, void)()
#define menu_drawMessageBox() GAME_FN(menu_drawMessageBox, 0x4290d0, void, void)()   /* the message box */
#define menu_drawInputLine(a, b) GAME_FN(menu_drawInputLine, 0x428940, void, int, int)(a, b)
#define menu_drawCursor() GAME_FN(menu_drawCursor, 0x429bc0, void, void)()
#define menu_enterState() GAME_FN(menu_enterState, 0x41f970, void, void)()
#define menu_drawBackground() GAME_FN(menu_drawBackground, 0x441740, void, void)()
#define menu_drawFrame(x0, y0, x1, y1) GAME_FN(menu_drawFrame, 0x428c30, u32, int, int, int, int)(x0, y0, x1, y1)
/* textured quads (menu_quads.c): buttons from the bound sheet (lit == 1: the lit cell), whole textures, panel ornaments */
#define menu_drawWideButton(x0, y0, x1, y1, lit) GAME_FN(menu_drawWideButton, 0x4282f0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define profile_drawButton(x0, y0, x1, y1, lit) GAME_FN(profile_drawButton, 0x4283e0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawSmallButton1(x0, y0, x1, y1, lit) GAME_FN(menu_drawSmallButton1, 0x4284d0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawSmallButton2(x0, y0, x1, y1, lit) GAME_FN(menu_drawSmallButton2, 0x4285c0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawSmallButton3(x0, y0, x1, y1, lit) GAME_FN(menu_drawSmallButton3, 0x4286b0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawSmallButton4(x0, y0, x1, y1, lit) GAME_FN(menu_drawSmallButton4, 0x4287a0, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexture(x0, y0, x1, y1, tex) GAME_FN(menu_drawTexture, 0x427a90, void, int, int, int, int, int)(x0, y0, x1, y1, tex)
#define menu_drawTextureFlipped(x0, y0, x1, y1, tex) GAME_FN(menu_drawTextureFlipped, 0x427b60, void, int, int, int, int, int)(x0, y0, x1, y1, tex)
#define menu_drawCornerOrnaments(x0, y0, x1, y1) GAME_FN(menu_drawCornerOrnaments, 0x428a00, u32, int, int, int, int)(x0, y0, x1, y1)
#define menu_drawTopRightOrnament(x0, y0, x1) GAME_FN(menu_drawTopRightOrnament, 0x428b50, void, int, int, int)(x0, y0, x1)
#define g_menuOrnamentTexture (g_menuFrameTextures[0])   /* the panel corner ornaments (texture id, four 128-unit quarters) */
#define messageBox_keyClose() GAME_FN(messageBox_keyClose, 0x431950, void, void)()
#define menu_keyStartFade() GAME_FN(menu_keyStartFade, 0x4318b0, void, void)()
#define profile_screenKeys() GAME_FN(profile_screenKeys, 0x44cdd0, void, void)()
#define mainmenu_processKeys() GAME_FN(mainmenu_processKeys, 0x441e00, void, void)()
#define lobby_processKeys() GAME_FN(lobby_processKeys, 0x4081f0, void, void)()
#define missionsel_keys() GAME_FN(missionsel_keys, 0x447c70, void, void)()
#define setup_processTabKeys() GAME_FN(setup_processTabKeys, 0x4230a0, void, void)()
#define armc_processInput() GAME_FN(armc_processInput, 0x410ab0, void, void)()
#define room_mouse() GAME_FN(room_mouse, 0x4378e0, void, void)()
#define settingsPage_keys() GAME_FN(settingsPage_keys, 0x4440f0, void, void)()
#define freeCam_keys() GAME_FN(freeCam_keys, 0x42ada0, void, void)()
#define profileList_keys() GAME_FN(profileList_keys, 0x44c600, void, void)()
#define profile_messageKeys() GAME_FN(profile_messageKeys, 0x44c850, void, void)()
#define profile_deleteKeys() GAME_FN(profile_deleteKeys, 0x44c8c0, void, void)()
#define profile_secondDialogKeys() GAME_FN(profile_secondDialogKeys, 0x44ca90, void, void)()
#define profile_emblemKeys() GAME_FN(profile_emblemKeys, 0x44cc60, void, void)()
#define missionsel_camera() GAME_FN(missionsel_camera, 0x447cb0, void, void)()
#define missionsel_drawTunnel() GAME_FN(missionsel_drawTunnel, 0x448140, void, void)()
#define missionsel_frameSettings() GAME_FN(missionsel_frameSettings, 0x44aa20, void, void)()
#define missionsel_frameScreen() GAME_FN(missionsel_frameScreen, 0x44aa30, void, void)()
#define sound_playMenu(id) GAME_FN(sound_playMenu, 0x41e760, u32, int)(id)          /* 0 confirm / back, 2 move */
#define profile_typeNewName() GAME_FN(profile_typeNewName, 0x44b600, u32, void)()
#define profile_resetCamera() GAME_FN(profile_resetCamera, 0x44bc00, void, void)()
#define profile_deleteFiles() GAME_FN(profile_deleteFiles, 0x44ba60, void, void)()
#define profile_selectAndLoad() GAME_FN(profile_selectAndLoad, 0x44b990, void, void)()
#define deleteDialog_hitTest(x, y) GAME_FN(deleteDialog_hitTest, 0x44b320, int, int, int)(x, y)  /* the button at (x, y): 0 left, 1 right */
#define secondDialog_hitTest(x, y) GAME_FN(secondDialog_hitTest, 0x44b360, int, int, int)(x, y)
#define Color4_set(dst, r, g, b, a) GAME_FN(Color4_set, 0x41f0e0, void, Colour *, float, float, float, float)(dst, r, g, b, a)
#define Color4_set_bits(dst, r, g, b, a) GAME_FN(Color4_set, 0x41f0e0, void, void *, u32, u32, u32, u32)(dst, r, g, b, a)   /* (the floats as their bits) */

/* ---- the in-match 2D pass: the scene's view, its stage's overlay parts, the HUD elements ---- */
#define gfx_setProjectionHud(mode, scale) GAME_FN(gfx_setProjectionHud, 0x4685f0, void, int, float)(mode, scale)
#define gfx_setProjectionHud_bits(mode, scale) GAME_FN(gfx_setProjectionHud, 0x4685f0, void, int, u32)(mode, scale)   /* (the scale as its bits) */
#define factors_addPointLight(pool, colour, radius, pos) GAME_THISFN(factors_addPointLight, 0x483f00, int, void *, u32, float, void *)(pool, colour, radius, pos)   /* a light of radius at pos */
#define factors_addPointLight_bits(pool, colour, strength, pos) GAME_THISFN(factors_addPointLight, 0x483f00, int, void *, u32, u32, void *)(pool, colour, strength, pos)   /* (the strength as its bits) */
#define view_farPlane() GAME_FN(view_farPlane, 0x468700, float, void)()             /* view_farPlane: a float setting */
#define tex_clearSetCounters(textures) GAME_THISFN(tex_clearSetCounters, 0x456b50, void, void *)(textures)
#define ViewVolume_clearDrawCounts(view) GAME_THISFN(ViewVolume_clearDrawCounts, 0x4841d0, void, void *)(view)
#define ViewVolume_captureMatrices(view, a, b) GAME_THISFN(ViewVolume_captureMatrices, 0x4841f0, void, void *, void *, void *)(view, a, b)
#define ViewVolume_reset(view) GAME_THISFN(ViewVolume_reset, 0x484260, void, void *)(view)
/* out = the inverse of m (4 x 4); returns 0 and leaves out untouched when m is singular */
#define Mat4_invert(out, m) GAME_FN(Mat4_invert, 0x47d740, int, float *, const float *)(out, m)
#define Mat4_minor(m, out, row, col) GAME_FN(Mat4_minor, 0x47d610, void, const float *, float *, int, int)(m, out, row, col)   /* the 3x3 left without row and col */
#define Mat4_determinant(m) GAME_FN(Mat4_determinant, 0x47d690, long double, const float *)(m)
#define ViewVolume_addTriangle(vv, id, info6, info3, P, M, raw, cull) GAME_THISFN(ViewVolume_addTriangle, 0x4842d0, int, void *, int, const u32 *, const u32 *, const float *, const float *, int, int)(vv, id, info6, info3, P, M, raw, cull)
#define shape_getShadingColorBufferBy(out, first, part, factors, m) GAME_FN(shape_getShadingColorBufferBy, 0x463b80, void, u8 *, int, const void *, const u8 *, const float *)(out, first, part, factors, m)
#define render_depthSortA(e, lo, hi) GAME_FN(render_depthSortA, 0x490f80, void, u32 *, int, int)(e, lo, hi)   /* (transparent triangles) */
#define render_depthSortB(e, lo, hi) GAME_FN(render_depthSortB, 0x491190, void, u32 *, int, int)(e, lo, hi)   /* (billboards) */
/* a shape's shading colours from light factors (seen through inverse, the inverse of the shape's matrix), every part
   into its slice of out; first = 1 (0x466910) */
#define shape_shadeParts(out, first, shape, factors, inverse) GAME_FN(shape_shadingColours, 0x466910, void, u32 *, int, Model *, const LightFactors *, \
	const float *)(out, first, shape, factors, inverse)
/* a shape's colours from point lights: set (first = 1) or added (0), every part into its slice of out (0x466960) */
#define shape_lightParts(out, first, shape, lights) GAME_FN(shape_colourPixels, 0x466960, void, u32 *, int, Model *, const void *)(out, first, shape, lights)
#define stage_drawObject(stage, i, view) GAME_THISFN(stage_drawObject, 0x490b30, void, Stage *, int, void *)(stage, i, view)   /* a map object to the view volume */
/* queue every mesh of model for drawing (see recomp.c): extra, matrix (none: the current modelview), a4, colour (4 bytes,
   or none), cull (1: skip meshes outside a clip plane),
   material (< 0: the mesh's own), a8 */
#define ViewVolume_projectObject(view, model, extra, matrix, a4, colour, cull, material, a8) GAME_THISFN(ViewVolume_projectObject, 0x4853c0, void, void *, \
	void *, u32, const float *, int, const void *, int, int, int)(view, model, extra, matrix, a4, colour, cull, material, a8)
#define render_drawObjects(view, mode, alpha) GAME_THISFN(render_drawObjects, 0x485af0, void, void *, int, float)(view, mode, alpha)
#define sky_draw(stage, scale) GAME_THISFN(sky_draw, 0x496f20, void, Stage *, float)(stage, scale)   /* the sky (render/sky.c) */
#define ground_buildDrawLists(stage, view, scale) GAME_THISFN(ground_buildDrawLists, 0x497d20, void, void *, void *, float)(stage, view, scale)
/* the stage, the scene's own object (scene.fields: Stage) */
#define STAGE(scene) ((Stage *)((u8 *)RELOC(scene) + 0x1f36c8))
#define SCENE_STAGE_AT 0x1f36c8   /* where a scene's stage (its Stage object) starts */
#define SCENE_STAGE(scene) ((Stage *)((u8 *)(scene) + SCENE_STAGE_AT))   /* the same for a runtime scene pointer (no RELOC) */
#define stage_drawObjects(stage, view) GAME_THISFN(stage_drawObjects, 0x490da0, void, Stage *, void *)(stage, view)
#define stage_drawActors(stage, view, pass) GAME_THISFN(stage_drawActors, 0x45e170, void, Stage *, void *, int)(stage, view, pass)
/* actor i's frame of its parts (actor_updateBody / actor_updatePart), with the view volume and pass */
#define actor_drawIntoView(stage, i, view, pass) GAME_THISFN(actor_drawIntoView, 0x45d3e0, void, Stage *, int, void *, int)(stage, i, view, pass)
#define stage_drawBullets(stage, view) GAME_THISFN(stage_drawBullets, 0x47d060, void, void *, void *)(stage, view)
#define stage_drawProjectiles(stage, view) GAME_THISFN(stage_drawProjectiles, 0x479af0, void, Stage *, void *)(stage, view)
/* projectile i drawn (or queued) in the view volume */
/* a camera-facing quad at p into the view volume's billboard list id: corners p + a .. p + b, depth + dz, texture
   coordinates uv0 .. uv1, colour (4 bytes) */
#define viewVolume_addBillboard(view, id, uv0, uv1, dz, colour, a, b, p, extra, flag) GAME_THISFN(viewVolume_addBillboard, 0x484ca0, void, void *, int, const float *, \
	const float *, float, const void *, const float *, const float *, const float *, int, int)(view, id, uv0, uv1, dz, colour, a, b, p, extra, flag)
#define g_highDetail (g_graphicSettings[2])            /* the polygon detail setting (HIGH 1): 1 draws map items as models */
#define projectile_draw(stage, i, view) GAME_THISFN(projectile_draw, 0x476890, void, Stage *, int, void *)(stage, i, view)
#define stage_drawItems(stage, view) GAME_THISFN(stage_drawItems, 0x48f970, void, void *, void *)(stage, view)
#define stage_setFog(stage, colour, start, end, density) GAME_THISFN(stage_setFog, 0x472900, void, Stage *, const void *, u32, u32, u32)(stage, colour, start, end, density)
#define script_notifyObject(stage, x0, y0, x1, y1) GAME_THISFN(script_notifyObject, 0x48fde0, void, void *, int, int, int, int)(stage, x0, y0, x1, y1)
/* scene_followedActor: the match's top player: in team games the best ranked player of the leading team (the local player
   if it has none), else the first ranked */
#define scene_topPlayer(scene) GAME_THISFN(scene_followedActor, 0x4625a0, Player *, Scene *)(scene)
#define hud_drawDigits(x, y, scale, value, digits, flag) GAME_FN(hud_drawDigits, 0x46bdc0, void, int, int, float, int, int, int)(x, y, scale, value, digits, flag)
#define tex_getIdByName(textures, name, a, b, c, d, e, f, g) GAME_THISFN(tex_getIdByName, 0x456be0, int, void *, const char *, int, int, int, int, int, int, int)(textures, name, a, b, c, d, e, f, g)
#define vec_rotate(v, angle) GAME_THISFN(vec_rotate, 0x467700, void, float *, int)(v, angle)   /* turns (x, y) by angle (tenths of a degree) */
#define view_angle() GAME_FN(view_angle, 0x4686d0, float, void)()                          /* view_angle: the float at 0x4c4dec */
#define hud_drawPressFire(scene) GAME_THISFN(hud_drawPressFire, 0x495140, void, Scene *)(scene)
#define hud_drawClock(scene) GAME_THISFN(hud_drawClock, 0x496610, void, Scene *)(scene)
#define hud_drawMatchResult(scene) GAME_THISFN(hud_drawMatchResult, 0x496a30, void, Scene *)(scene)
#define hud_drawWatchedName(scene) GAME_THISFN(hud_drawWatchedName, 0x496b80, void, Scene *)(scene)
#define replay_drawMessage(scene) GAME_THISFN(replay_drawMessage, 0x495190, void, Scene *)(scene)
#define hud_drawChatInput(scene) GAME_THISFN(hud_drawChatInput, 0x4953d0, void, Scene *)(scene)
#define hud_drawTeamScores(scene) GAME_THISFN(hud_drawTeamScores, 0x496240, void, Scene *)(scene)
#define debug_traceStripped(scene) GAME_THISFN(debug_traceStripped, 0x48b420, void, Scene *)(scene)
#define hud_drawHelp(scene) GAME_THISFN(hud_drawHelp, 0x4955a0, void, Scene *)(scene)
#define hud_drawMenuBox(scene, x0, y0, x1, y1) GAME_THISFN(hud_drawMenuBox, 0x495ed0, void, Scene *, int, int, int, int)(scene, x0, y0, x1, y1)   /* a menu box */
#define hud_drawEscMenu(scene) GAME_THISFN(hud_drawEscMenu, 0x495610, void, Scene *)(scene)
#define hud_drawRecordIndicator(scene) GAME_THISFN(hud_drawRecordIndicator, 0x496d10, void, Scene *)(scene)
#define hud_drawCentreNotice(scene) GAME_THISFN(hud_drawCentreNotice, 0x496c20, void, Scene *)(scene)

/* ---- network ---- */
#define net_playerInUse(i) GAME_FN(net_playerInUse, 0x4a8700, int, int)(i)   /* the player table's slot i is taken */

/* ---- globals ---- */
typedef struct { float r, g, b, a; } Colour;
#define input_releaseKeyboard() GAME_FN(input_releaseKeyboard, 0x401460, void, void)()
#define menu_clearInputBuffer(maxLength) GAME_FN(menu_clearInputBuffer, 0x431560, void, int)(maxLength)
#define chat_createEdit(maxLength) GAME_FN(chat_createEdit, 0x43f460, void, int)(maxLength)   /* the hidden EDIT control typing goes to */
#define itoa(value, out, radix) GAME_CDECL(0x49fb53, char *, int, char *, int)(value, out, radix)
#define g_missionProgress (*(int *)(g_campaign + 0x104))   /* the furthest stage reached */
#define g_trig (g_tanTable)            /* 3600 values by tenths of a degree (the ring's radius) */
#define g_showFps (*(int *)&g_cfgSwitches[2])           /* 1: the FPS counter is shown */
#define g_gameModeNames ((const char (*)[64])STR(0x4c7030, "DEATH MATCH"))   /* "DEATH MATCH", "TEAM DEATH MATCH", ... (12) */
/* the title and profile screens */
/* the title emblem (menu_title.c) */
#define g_titleTextures (g_introTextures)     /* eight: the base picture's quarters, then the pulsing layer's */
/* key bindings (key codes), named by their use in the menus */
#define g_keyClick g_dikEnter           /* fire / click: the button under the pointer */
#define g_keyOk g_dikO              /* confirms a page */
#define g_keyCancel g_dikEscape          /* leaves a page */
#define g_keyBack g_dikC
#define g_keyCancel2 g_dikEscape_2
#define g_keyLeft g_dikLeft
#define g_keyRight g_dikRight
#define g_keyUp g_dikUp
#define g_keyDown g_dikDown
#define g_keyToggle g_dikTab          /* switches a two-button dialog's highlight */
#define g_keyLeftShift g_dikLShift       /* the modifier keys (DIK codes 0x2a, 0x36, 0x1d, 0x9d) */
#define g_keyRightShift g_dikRShift
#define g_keyLeftCtrl g_dikLCtrl
#define g_keyRightCtrl g_dikRCtrl
#define input_isDown(key) GAME_FN(input_isDown, 0x401590, int, int)(key)   /* the key (code) is held */
#define g_mouseClick (g_mouseClicked[0])           /* a click this frame (the left button) */
#define g_mouseHeld (g_mouseButtonsHeld[0])        /* (by use) the left button held down */
#define g_hWndMain g_mainWindow
#define KillTimer(hwnd, id) IMPORT(0x4a9330, int, void *, u32)(hwnd, id)
/* a rectangle in menu units in g_rectColour, filled or outlined (the patch DLL replaces it: kept original) */
#define menu_drawRect(x0, y0, x1, y1, filled) GAME_FN(menu_drawRect, 0x427970, u32, int, int, int, int, int)(x0, y0, x1, y1, filled)
/* the room's buttons under (x, y): the index of the button hit, or -1 */
#define leaveDialog_hitTest(x, y) GAME_FN(leaveDialog_hitTest, 0x4321c0, int, int, int)(x, y)
#define popup_hitTest(x, y) GAME_FN(popup_hitTest, 0x432280, int, int, int)(x, y)
#define gameListStop_hitTest(x, y) GAME_FN(gameListStop_hitTest, 0x432340, int, int, int)(x, y)
#define field_editMessage() GAME_FN(field_editMessage, 0x434320, void, void)()   /* open the message field */
#define app_closeWindow(code) GAME_FN(app_closeWindow, 0x41e7a0, int, int)(code)   /* quit the game with exit code (app/app_quit.c) */
#define PostMessageA(hwnd, msg, w, l) IMPORT(0x4a9328, int, void *, u32, u32, u32)(hwnd, msg, w, l)
#define profile_loadSelectedColours() GAME_FN(profile_loadSelectedColours, 0x44bc50, void, void)()
#define profile_drawPilotSelect() GAME_FN(profile_drawPilotSelect, 0x44e640, void, void)()
#define arena_leaveSession() GAME_FN(arena_leaveSession, 0x452fe0, u32, void)()
/* two-button dialogs: the highlighted choice and its marker */
/* the profile screen's pages */
/* the mission-select screen */
#define g_missionBox ((const int *)ADDR(g_missionSelectLeft))         /* the dialog frame: x0, y0, x1, y1 */
/* exe strings passed to the text passes (the address itself is what the callee gets) */
#define STR_COPYRIGHT ((const char *)STR(0x4b0474, "AXIS by Jamie System Development"))
#define STR_2D ((const char *)STR(0x4d03e0, "%2d"))
#define STR_VERSION ((const char *)STR(0x4b0384, "Axis v1.03"))

/* ---- DirectPlay (net/dplay_slots.c) ---- */
#define dplay_coInit() GAME_FN(dplay_coInit, 0x453720, int, void)()                     /* 0 when COM is up */
#define dplay_connectionAvailable(kind) GAME_FN(net_connectionAvailable, 0x453a30, int, int)(kind)  /* net_connectionAvailable */
#define dplay_initConnection(kind, address) GAME_FN(dplay_initConnection, 0x453a90, int, int, int)(kind, address)
#define dplay_release() GAME_FN(dplay_release, 0x453920, int, void)()
#define dplay_enumSessions() GAME_FN(dplay_enumSessions, 0x453fd0, int, void)()
#define dplay_hostSession(a1, a2, a3, a4, a5, a6, a7, a8) GAME_FN(dplay_hostSession, 0x453cf0, int, int, int, int, int, int, int, int, int)\
	(a1, a2, a3, a4, a5, a6, a7, a8)
#define dplay_joinSession(a1, a2, a3, a4) GAME_FN(dplay_joinSession, 0x453e60, int, int, int, int, int)(a1, a2, a3, a4)
#define dplay_create() GAME_FN(dplay_create, 0x453790, int, void)()
#define net_resetState() GAME_FN(net_resetState, 0x4509e0, void, void)()
#define dplaySlot0_close() GAME_FN(dplaySlot0_close, 0x4549a0, int, void)()   /* close slot 0 .. 3 */
#define dplaySlot1_close() GAME_FN(dplaySlot1_close, 0x454ac0, int, void)()
#define dplaySlot2_close() GAME_FN(dplaySlot2_close, 0x454bd0, int, void)()
#define dplaySlot3_close() GAME_FN(dplaySlot3_close, 0x454ce0, int, void)()

/* ---- the stage's player records (thiscall on the stage; p: the player) ---- */
#define player_setName(stage, p, name) GAME_THISFN(player_setName, 0x473940, void, void *, int, const char *)(stage, p, name)
#define player_setLevel(stage, p, v) GAME_THISFN(player_setLevel, 0x473a10, void, void *, int, int)(stage, p, v)   /* player_setLevel */
#define player_setTeam(stage, p, team) GAME_THISFN(player_setTeam, 0x473a80, void, void *, int, int)(stage, p, team)
#define actor_setActorTypeHeadInfoBy(stage, p, i) GAME_THISFN(actor_setActorTypeHeadInfoBy, 0x473b10, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeChestInfoBy(stage, p, i) GAME_THISFN(actor_setActorTypeChestInfoBy, 0x473c20, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeArmInfoBy(stage, p, i) GAME_THISFN(actor_setActorTypeArmInfoBy, 0x473d30, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeLegInfoBy(stage, p, i) GAME_THISFN(actor_setActorTypeLegInfoBy, 0x473e40, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeBoosterInfoBy(stage, p, i) GAME_THISFN(actor_setActorTypeBoosterInfoBy, 0x473f50, int, Stage *, int, int)(stage, p, i)
#define actor_setActorTypeItemInfoBy(stage, p, slot, item) GAME_THISFN(actor_setActorTypeItemInfoBy, 0x474060, void, void *, int, int, int)(stage, p, slot, item)
#define player_markUsed(stage, p) GAME_THISFN(playerRecord_markUsed, 0x474390, void, void *, int)(stage, p)   /* playerRecord_markUsed */
/* the ARM CENTER's mech setters (menu/armc_mech.c), thiscall on the scene */
#define mech_setName(scene, name) GAME_THISFN(mech_setName, 0x461320, void, Scene *, const char *)(scene, name)
#define mech_setPilotLevel(scene, v) GAME_THISFN(mech_setPilotLevel, 0x461370, void, Scene *, int)(scene, v)
#define scene_setLocalTeam(scene, team) GAME_THISFN(scene_setLocalTeam, 0x4613a0, void, Scene *, int)(scene, team)
#define escMenu_open(scene, page, item) GAME_THISFN(escMenu_open, 0x49ca20, void, Scene *, int, int)(scene, page, item)   /* the Esc menu opened on page */
#define profile_addMatchScores(scene) GAME_THISFN(profile_addMatchScores, 0x49d150, void, Scene *)(scene)
#define msg_playerChangedTeam(scene, player, team) GAME_THISFN(msg_playerChangedTeam, 0x462e30, void, Scene *, int, int)(scene, player, team)
#define msg_playerJoinedTeam(scene, player, team) GAME_THISFN(msg_playerJoinedTeam, 0x462d30, void, Scene *, int, int)(scene, player, team)
#define net_announceChangedTeam(scene, a, b, text) GAME_THISFN(net_announceChangedTeam, 0x463610, void, Scene *, int, int, const char *)(scene, a, b, text)
#define net_announceJoinedTeam(scene, a, b, text) GAME_THISFN(net_announceJoinedTeam, 0x4635b0, void, Scene *, int, int, const char *)(scene, a, b, text)
#define notice_printCentre(scene, ...) GAME_FN(notice_printCentre, 0x463450, int, Scene *, const char *, ...)(scene, __VA_ARGS__)   /* a HUD notice (a format and its arguments) */
#define chat_textField(x, y, maxLength) GAME_FN(chat_textField, 0x44ac90, void, int, int, int)(x, y, maxLength)   /* the match's text line opened */
#define chat_keepLastLine() GAME_FN(chat_keepLastLine, 0x44ace0, void, void)()
#define replay_closeRecording(scene) GAME_THISFN(replay_closeRecording, 0x487ed0, void, Scene *)(scene)   /* the recording stopped */
#define autoplay_startRecording(scene, name) GAME_THISFN(autoplay_startRecording, 0x487cb0, void, Scene *, const char *)(scene, name)
#define music_playMatch(scene) GAME_THISFN(music_playMatch, 0x462850, void, Scene *)(scene)
#define armc_setHeadIndex(scene, i) GAME_THISFN(armc_setHeadIndex, 0x4613d0, void, Scene *, int)(scene, i)
#define armc_setChestIndex(scene, i) GAME_THISFN(armc_setChestIndex, 0x461410, void, Scene *, int)(scene, i)
#define armc_setArmIndex(scene, i) GAME_THISFN(armc_setArmIndex, 0x461450, void, Scene *, int)(scene, i)
#define armc_setLegIndex(scene, i) GAME_THISFN(armc_setLegIndex, 0x461490, void, Scene *, int)(scene, i)
#define armc_setBoosterIndex(scene, i) GAME_THISFN(armc_setBoosterIndex, 0x4614d0, void, Scene *, int)(scene, i)
#define mech_setItem(scene, slot, item) GAME_THISFN(mech_setItem, 0x461510, void, Scene *, int, int)(scene, slot, item)

/* ---- the ARM CENTER (menu/armc_*.c) ---- */
#define armc_updatePartsPreview() GAME_FN(armc_updatePartsPreview, 0x41d600, void, void)()      /* the mech preview */
#define armc_updateColourPreview() GAME_FN(armc_updateColourPreview, 0x41d8a0, void, void)()      /* the colour page's preview */
#define armc_drawPreviewTunnel() GAME_FN(armc_drawPreviewTunnel, 0x411ab0, void, void)()      /* the screen's state entered from the room */
#define armc_drawTunnel() GAME_FN(armc_drawTunnel, 0x411110, void, void)()      /* and from the main menu */
#define armc_cameraStep() GAME_FN(armc_cameraStep, 0x410b50, void, void)()
#define armc_enterScreen() GAME_FN(armc_enterScreen, 0x40e5d0, void, void)()      /* an ARM CENTER session made (menu/armc_items.c) */
#define armc_setup3DView() GAME_FN(armc_setup3DView, 0x41b710, void, void)()      /* the 3D view set up (menu/armc_misc.c) */
#define armc_drawPanels() GAME_FN(armc_drawPanels, 0x41b400, void, void)()
#define armc_extraItemBonuses() GAME_FN(armc_extraItemBonuses, 0x41dcf0, void, void)()
#define armc_drawPartsPage() GAME_FN(armc_drawPartsPage, 0x41dfb0, void, void)()      /* the pages' draw passes (menu/armc_misc.c) */
#define armc_drawColourPage() GAME_FN(armc_drawColourPage, 0x41dfe0, void, void)()
#define armc_drawThirdPage() GAME_FN(armc_drawThirdPage, 0x41e010, void, void)()
#define armc_drawWeightLine() GAME_FN(armc_drawWeightLine, 0x41dab0, void, void)()
#define armc_exit(confirmed) GAME_FN(armc_exit, 0x40f0f0, u32, int)(confirmed)   /* leave the screen (menu/armc_misc.c) */
#define armc_showPartsPage() GAME_FN(armc_showPartsPage, 0x40f200, void, void)()   /* to the parts page */
#define armc_showColourPage() GAME_FN(armc_showColourPage, 0x40f320, u32, void)()   /* to the third page */
#define armc_openWeaponsPage() GAME_FN(armc_openWeaponsPage, 0x40f220, u32, void)()   /* to the weapons page (menu/armc_items.c) */
#define armc_backupColours() GAME_FN(armc_backupColours, 0x40f590, u32, void)()   /* the colour slot kept for undo (menu/armc_state.c) */
#define armc_stepPart(part, dir) GAME_FN(armc_stepPart, 0x40f340, u32, u32, int)(part, dir)   /* the part in view stepped (menu/armc_parts.c) */
#define armc_drawPartPanels() GAME_FN(armc_drawPartPanels, 0x41b750, void, void)()
#define armc_retintParts() GAME_FN(armc_retintParts, 0x41d280, void, void)()
#define armc_applyColourSlot() GAME_FN(armc_applyColourSlot, 0x41cf20, void, void)()
#define armc_restoreColourUndo() GAME_FN(armc_restoreColourUndo, 0x41ced0, void, void)()   /* the undo buffer into colour slots 0 .. 4 (menu/armc_state.c) */
#define gl_rotateXYZ(x, y, z) GAME_FN(gl_rotateXYZ, 0x41ef20, void, u32, u32, u32)(x, y, z)   /* turned about x, y, z (degrees as float bits; render/gl_helpers.c) */
#define armc_rotateFromCursor(scene, eye, forward, up, part, angle, w, h) \
	GAME_THISFN(armc_rotateFromCursor, 0x461850, void, Scene *, const u32 *, const u32 *, const u32 *, int, int, int, int)(scene, eye, forward, up, part, angle, w, h)
#define armc_resetSeraphimParts() GAME_FN(armc_resetSeraphimParts, 0x40d990, void, void)()      /* the part lists (a no-op in the patched game) */
#define armc_drawModeTabs() GAME_FN(armc_drawModeTabs, 0x412450, void, void)()      /* the screen's frame */
#define armc_drawStatsPanel() GAME_FN(armc_drawStatsPanel, 0x412650, void, void)()
#define armc_drawBuildScreen() GAME_FN(armc_drawBuildScreen, 0x419160, void, void)()
#define armc_drawColourEditor() GAME_FN(armc_drawColourEditor, 0x41a280, void, void)()
#define g_startPos ((const u32 *)ADDR(g_vecOrigin))          /* (by use) where the player's actor starts (three floats) */
/* claim actor slot a for the player and make it theirs (thiscall on the stage; spawn: slot, -, position...) */
#define stage_claimPlayerActor(stage, a, x, y, spawn) GAME_THISFN(stage_claimPlayerActor, 0x45dd80, void, Stage *, int, int, int, void *)(stage, a, x, y, spawn)

#define mech_setAll(scene, name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5) GAME_THISFN(mech_setAll, 0x461250, void, \
	Scene *, const char *, int, int, int, int, int, int, int, int, int, int, int, int, int)(scene, name, v, team, head, chest, arm, leg, \
	booster, i0, i1, i2, i3, i4, i5)
#define stage_remakePlayerActor(stage) GAME_THISFN(stage_remakePlayerActor, 0x45ddc0, void, Stage *)(stage)
#define armc_giveShownActorWeapon(scene, slot) GAME_THISFN(armc_giveShownActorWeapon, 0x461540, void, Scene *, int)(scene, slot)   /* re-equip the preview mech */
#define armc_pickSlot(slot) GAME_FN(armc_pickSlot, 0x40f870, void, int)(slot)
#define armc_showCursorItem() GAME_FN(armc_showCursorItem, 0x40f950, void, void)()
#define armc_takeCursorItem() GAME_FN(armc_takeCursorItem, 0x40f9e0, u32, void)()   /* the item slots given to the mech (menu/armc_items.c) */
#define armc_colourPartEquipped(i) GAME_FN(armc_colourPartEquipped, 0x40f830, int, int)(i)   /* item list entry i is a colour part already in a slot */
#define armc_initCameraPoints() GAME_FN(armc_initCameraPoints, 0x40e510, void, void)()
#define armcMain_layout() GAME_FN(armcMain_layout, 0x40e060, void, void)()   /* the part lists made (heads, chests, arms...) */
#define armcParts_layout() GAME_FN(armcParts_layout, 0x40e1c0, void, void)()
#define armcColour_layout() GAME_FN(armcColour_layout, 0x40e300, void, void)()
#define armc_buildPartLists() GAME_FN(armc_buildPartLists, 0x40da40, void, void)()
#define mech_loadFromProfile() GAME_FN(mech_loadFromProfile, 0x4463a0, u32, void)()   /* the saved mech read (from the profile) */
#define armc_loadSavedMech() GAME_FN(armc_loadSavedMech, 0x40e6c0, void, void)()
#define armc_initCameraBox() GAME_FN(armc_initCameraBox, 0x40de80, void, void)()
#define armc_initPartBoxes() GAME_FN(armc_initPartBoxes, 0x40dfa0, void, void)()
#define armc_syncPartCursors() GAME_FN(armc_syncPartCursors, 0x40ed20, void, void)()
#define armc_viewedPartRecord(item) GAME_FN(armc_viewedPartRecord, 0x41cca0, void, int)(item)   /* the item shown on the preview */
#define armc_weaponSlotRecord(slot, item) GAME_FN(armc_weaponSlotRecord, 0x41ca50, void, int, int)(slot, item)
#define armc_snapshot(which) GAME_FN(armc_snapshot, 0x419000, void, int)(which)
#define armc_drawText(x, y, s) GAME_FN(armc_drawText, 0x4125c0, void, int, int, const char *)(x, y, s)
#define armc_drawStatLabel(x, y, s) GAME_FN(armc_drawStatLabel, 0x4125f0, void, int, int, const char *)(x, y, s)   /* right-aligned at x */
#define armc_readMechStats() GAME_FN(armc_readMechStats, 0x41c510, void, void)()
#define actor_selectWeapon(stage, actor, slot) GAME_THISFN(actor_selectWeapon, 0x45e880, void, Stage *, int, int)(stage, actor, slot)
#define scene_startSession(scene, a, b) GAME_THISFN(scene_startSession, 0x460cb0, void, Scene *, int, int)(scene, a, b)

#define armc_restoreMenuCamera() GAME_FN(armc_restoreMenuCamera, 0x40e670, void, void)()
#define armc_saveSelection() GAME_FN(armc_saveSelection, 0x40e7a0, void, void)()       /* keep the mech, save the progress */
#define armc_sendSelectionToNet() GAME_FN(armc_sendSelectionToNet, 0x40e930, void, void)()
#define armc_easeCamera() GAME_FN(armc_easeCamera, 0x41b300, void, void)()               /* the camera towards the page's target */
#define music_play(path) GAME_FN(music_play, 0x457150, u32, const char *)(path)

/* ---- messages ---- */
#define msg_print(scene, colour, ...) GAME_FN(msg_print, 0x4629f0, void, Scene *, int, const char *, ...)(scene, colour, __VA_ARGS__)   /* a line in the message box (printf) */
#define sound_playVolume(id, volume) GAME_FN(sound_playVolume, 0x456e50, void, int, int)(id, volume)   /* volume 0..100 */

/* ---- the setup screen (menu/setup_keys.c) ---- */
#define menuCamera_setMove(v) GAME_FN(menuCamera_setMove, 0x441250, u32, int)(v)   /* g_menuCameraMove = v */
#define setup_topPageClicks() GAME_FN(setup_topPageClicks, 0x4220c0, void, void)()
#define setup_soundTabClicks() GAME_FN(setup_soundTabClicks, 0x4221d0, void, void)()
#define setup_graphicTabClicks() GAME_FN(setup_graphicTabClicks, 0x422480, void, void)()
#define setup_controlTabClicks() GAME_FN(setup_controlTabClicks, 0x422830, void, void)()
#define setupSound_hitTest(x, y) GAME_FN(setupSound_hitTest, 0x420670, int, int, int)(x, y)   /* the sound tab's control at (x, y) */
#define setupControl_hitTest(x, y) GAME_FN(setupControl_hitTest, 0x4206f0, int, int, int)(x, y)   /* the controls tab's control at (x, y) */
#define setup_sliderClicks() GAME_FN(setup_sliderClicks, 0x4226b0, void, void)()   /* the controls tab's slider follows the pointer */
#define setup_topPageKeys() GAME_FN(setup_topPageKeys, 0x422b70, void, void)()
#define setup_soundTabKeys() GAME_FN(setup_soundTabKeys, 0x422c60, void, void)()
#define setup_graphicTabKeys() GAME_FN(setup_graphicTabKeys, 0x422d20, void, void)()
#define setup_controlTabKeys() GAME_FN(setup_controlTabKeys, 0x422e10, void, void)()
#define setup_selectSoundTab() GAME_FN(setup_selectSoundTab, 0x420ad0, void, void)()
#define setup_selectGraphicTab() GAME_FN(setup_selectGraphicTab, 0x420b40, void, void)()
#define setup_selectControlTab() GAME_FN(setup_selectControlTab, 0x420ba0, void, void)()
#define setup_drawTunnel() GAME_FN(setup_drawTunnel, 0x423e50, void, void)()
#define setup_drawSoundPage() GAME_FN(setup_drawSoundPage, 0x424810, void, void)()
#define setup_drawOptionsDialog() GAME_FN(setup_drawOptionsDialog, 0x425460, void, void)()
#define setup_drawControlsPage() GAME_FN(setup_drawControlsPage, 0x425cd0, void, void)()
#define cfg_readPlayer(f) GAME_FN(cfg_readPlayer, 0x42d7f0, void, void *)(f)          /* axis.cfg's player section read back */
#define cfg_readServer(f) GAME_FN(cfg_readServer, 0x42da70, void, void *)(f)      /* its server section */
#define cfg_readSound(f) GAME_FN(cfg_readSound, 0x42e080, void, void *)(f)             /* its sound section */
#define cfg_readGraphics(f) GAME_FN(cfg_readGraphics, 0x42e240, void, void *)(f)     /* its graphics section */
#define cfg_readKeyBindings(f) GAME_FN(cfg_readKeyBindings, 0x42e730, void, void *)(f)      /* its key bindings */
#define input_setDefaultBindings() GAME_FN(input_setDefaultBindings, 0x42c410, void, void)()     /* the default key bindings */
#define armc_enterParts() GAME_FN(armc_enterParts, 0x40ee20, u32, void)()
#define dplay_join(session, id, name, colour) GAME_FN(dplay_join, 0x453180, int, int, u32, const char *, int)(session, id, name, colour)   /* a join: 500 joined */
#define tunnel_addRing() GAME_FN(tunnel_addRing, 0x441200, TunnelRing *, void)()   /* one more tunnel ring */
#define tunnel_removeLastRing(head) GAME_FN(tunnel_removeLastRing, 0x441190, u32, TunnelRing **)(head)   /* the last ring taken off and freed */
#define crypt_countingKey(p, key) GAME_FN(crypt_countingKey, 0x42b3c0, int, u8 *, u8)(p, key)   /* a 0x4c-byte record decoded (xor key, key + 1, ...) */
#define cfg_writeAxisCfg() GAME_FN(cfg_writeAxisCfg, 0x42d730, u32, void)()
#define setup_bindKey(key) GAME_FN(setup_bindKey, 0x421680, void, int)(key)   /* (by use) the row being bound gets key */
#define setup_defaultBindings() GAME_FN(setup_defaultBindings, 0x420c10, void, void)()   /* the default key bindings */
#define music_shutdown() GAME_FN(music_shutdown, 0x457310, void, void)()

/* ---- devices and sound (app/devices.c, sound/sound_basic.c) ---- */
#define dsbuf_play(sound) GAME_FN(dsbuf_play, 0x467d70, u32, void *)(sound)
#define dsbuf_setVolume(sound, volume) GAME_FN(dsbuf_setVolume, 0x467db0, void, void *, int)(sound, volume)
#define sound_playNextBuffer(sound, mode, value) GAME_FN(sound_playNextBuffer, 0x467dd0, u32, void *, int, int)(sound, mode, value)   /* played with a pan (mode 1 / 2) */
#define input_releaseMouse() GAME_FN(input_releaseMouse, 0x401490, void, void)()   /* the mouse let go and released */
#define glFinish() IMPORT(0x4a91f0, void, void)()
#define SwapBuffers(hdc) IMPORT(0x4a9028, int, void *)(hdc)
#define CoUninitialize() IMPORT(0x4a93b8, void, void)()

/* ---- front-end screens (menu/menu_states.c) ---- */
#define g_progress (*(int *)(g_campaign + 0x104))            /* rounds beaten (missions unlocked) */
#define menuTunnel_advance(tunnel) GAME_FN(menuTunnel_advance, 0x441260, void, void *)(tunnel)   /* moves the background tunnel on */
#define menu_drawBackground3D(tunnel) GAME_FN(menu_drawBackground3D, 0x429d70, void, void *)(tunnel)
#define mission_chosen(m) GAME_FN(mission_chosen, 0x4479b0, u32, int)(m)
#define mainmenu_drawReplaySelect() GAME_FN(mainmenu_drawReplaySelect, 0x4434f0, void, void)()
#define replaySelect_drawNames() GAME_FN(replaySelect_drawNames, 0x442d10, u32, void)()   /* the replay selection dialog's list */
#define menu_mainMenu() GAME_FN(menu_mainMenu, 0x442050, void, void)()
#define replaySelect_drawDialog() GAME_FN(replaySelect_drawDialog, 0x442e10, void, void)()
#define menu_drawDimOverlay() GAME_FN(menu_drawDimOverlay, 0x40ce70, u32, void)()
#define skirmish_clicks() GAME_FN(skirmish_clicks, 0x443e20, void, void)()
#define skirmish_settingsArrowClick() GAME_FN(skirmish_settingsArrowClick, 0x443ea0, void, void)()
#define skirmish_processKeys() GAME_FN(skirmish_processKeys, 0x443f20, void, void)()
#define skirmish_settingsKeys() GAME_FN(skirmish_settingsKeys, 0x444070, void, void)()
#define briefing_clickClose() GAME_FN(briefing_clickClose, 0x447af0, void, void)()
#define missionsel_clicks() GAME_FN(missionsel_clicks, 0x447a50, void, void)()
#define mission_choose() GAME_FN(mission_choose, 0x4479d0, u32, void)()
#define missionSettings_leave() GAME_FN(missionSettings_leave, 0x447960, u32, void)()
#define briefing_keys() GAME_FN(briefing_keys, 0x447c30, void, void)()
#define missionList_keys() GAME_FN(missionList_keys, 0x447b40, void, void)()

/* ---- DirectPlay calls (net/dplay_calls.c) ---- */
#define CoCreateInstance(clsid, outer, context, iid, out) IMPORT(0x4a93b4, long, const void *, void *, u32, const void *, void **)(clsid, outer, context, iid, out)
#define dplaySlot0_enum() GAME_FN(dplaySlot0_enum, 0x4549c0, int, void)()   /* list the sessions through slot 0 .. 3 */
#define dplaySlot1_enum() GAME_FN(dplaySlot1_enum, 0x454ae0, int, void)()
#define dplaySlot2_enum() GAME_FN(dplaySlot2_enum, 0x454bf0, int, void)()
#define dplaySlot3_enum() GAME_FN(dplaySlot3_enum, 0x454d00, int, void)()

/* ---- the game's own network code (net/net_servers.c) ---- */
#define net_ping(ip, timeout) GAME_FN(net_ping, 0x4548b0, int, u32, int)(ip, timeout)   /* ICMP echo: the round trip time, 0 when none */
#define net_inetAddr(address) GAME_FN(net_inetAddr, 0x4547c0, u32, const char *)(address)
#define net_closeThreadHandles() GAME_FN(net_closeThreadHandles, 0x454760, void, void)()   /* the network threads' handles closed */
#define net_pingAllServers() GAME_FN(net_pingAllServers, 0x4545b0, void, void)()   /* ping every listed server */
#define WaitForMultipleObjects(n, handles, all, ms) IMPORT(0x4a917c, u32, u32, void *const *, int, u32)(n, handles, all, ms)
#define ExitThread(code) IMPORT(0x4a9180, void, u32)(code)
#define GetTickCount() IMPORT(0x4a9184, u32, void)()
#define data_loadPilotProfiles() GAME_FN(data_loadPilotProfiles, 0x42b590, void, void)()
#define menu_drawLine(x0, y0, x1, y1) GAME_FN(menu_drawLine, 0x427a40, void, int, int, int, int)(x0, y0, x1, y1)   /* a line in the menu colour */
#define timer_waitFrames(frames) GAME_FN(timer_waitFrames, 0x41e730, void, double)(frames)   /* wait frames 1/60 s (app/timer.c) */
#define frontEnd_drawProgress() GAME_FN(frontEnd_drawProgress, 0x41f100, u32, void)()   /* the loading picture at the next step (0x4dda34) */
#define tunnel_rebuild() GAME_FN(tunnel_rebuild, 0x4411e0, void, void)()
#define frontEnd_startUp() GAME_FN(frontEnd_startUp, 0x430bf0, void, void)()
#define menu_loadTextures() GAME_FN(menu_loadTextures, 0x430ca0, void, void)()
#define app_quitGame() GAME_FN(app_quitGame, 0x44f850, void, void)()   /* quit (app/app_quit.c) */
#define net_closeAll(mode) GAME_FN(net_closeAll, 0x451600, void, int)(mode)   /* every socket closed before connecting */
#define net_send(kind, socket) GAME_FN(net_send, 0x4521c0, u32, int, int)(kind, socket)   /* a packet (0xc room, 0x14 arena...) to the lobby (100) / game server (0x65) */
#define net_connect(mode) GAME_FN(net_connect, 0x451b80, int, int)(mode)   /* 100 the lobby, 0x65 the game server (net/net_tables.c) */
#define net_disconnect() GAME_FN(net_disconnect, 0x451e60, u32, void)()   /* leaving the network (net/net_tables.c) */
#define GetModuleHandleA(name) IMPORT(0x4a915c, void *, const char *)(name)
#define glWindow_resize(w, h) GAME_FN(glWindow_resize, 0x468450, int, int, int)(w, h)   /* app/win32.c */
#define TimeSync_frameTime(timer) GAME_THISFN(TimeSync_frameTime, 0x487490, long double, void *)(timer)   /* seconds since its last call */
#define loading_draw_bits(progress) GAME_FN(loading_draw, 0x469320, void, u32)(progress)   /* the loading screen at progress (float bits) */
#define replaySelect_allIn() GAME_FN(replaySelect_allIn, 0x4417f0, void, void)()   /* every map of the replay selection list in */
#define replaySelect_toggle(i) GAME_FN(replaySelect_toggle, 0x4417c0, void, int)(i)   /* map i of the replay selection list in or out */
#define replaySelect_hitTest(x, y) GAME_FN(replaySelect_hitTest, 0x440b70, int, int, int)(x, y)   /* the replay selection control at (x, y), -1: none */
#define mapList_hitTest(x, y) GAME_FN(mapList_hitTest, 0x4033e0, int, int, int)(x, y)   /* the arena map list's control at (x, y) */
#define mapList_toggle(i) GAME_FN(mapList_toggle, 0x403560, void, int)(i)     /* the arena list: map i in or out */
#define mapList_stepGameType(i) GAME_FN(mapList_stepGameType, 0x403590, void, int)(i)     /* map i's game type stepped */
#define mapList_chooseNone() GAME_FN(mapList_chooseNone, 0x403530, u32, void)()      /* no map chosen */
#define mapList_chooseAll() GAME_FN(mapList_chooseAll, 0x4034e0, u32, void)()      /* every map chosen */
#define mapList_ok() GAME_FN(mapList_ok, 0x403640, u32, void)()      /* the list kept */
#define replaySelect_allOut() GAME_FN(replaySelect_allOut, 0x440df0, void, void)()   /* and out */
#define replaySelect_ok() GAME_FN(replaySelect_ok, 0x441770, void, void)()   /* the replay selection dialog's OK */
#define net_addPlayerRecord(reply) GAME_FN(net_addPlayerRecord, 0x452de0, void, void *)(reply)   /* the server's accept reply handled */
#define mission_loadBriefing(k) GAME_FN(mission_loadBriefing, 0x443af0, u32, int)(k)   /* mission k's block read from axis.mis (load/files.c) */
#define skirmishSettings_leave() GAME_FN(skirmishSettings_leave, 0x443c80, u32, void)()   /* leave the skirmish settings */
#define skirmish_cursorUp() GAME_FN(skirmish_cursorUp, 0x443cd0, void, void)()   /* the skirmish list's cursor up */
#define skirmish_cursorDown() GAME_FN(skirmish_cursorDown, 0x443d10, void, void)()   /* and down */
#define briefing_typeOut() GAME_FN(briefing_typeOut, 0x445520, void, void)()   /* the briefing typed out (menu/skirmish.c) */
#define text_setWrapX(v) GAME_FN(text_setWrapX, 0x4017b0, int, int)(v)   /* the text wrap x (0x4ad490) */
#define text_setBottom(v) GAME_FN(text_setBottom, 0x4017c0, int, int)(v)   /* the text's bottom (0x4ad494) */
#define timer_now() GAME_FN(timer_now, 0x4301e0, long double, void)()   /* the time in ticks of the shifted performance counter, 80-bit */
#define QueryPerformanceFrequency(out) IMPORT(0x4a913c, int, u64 *)(out)
#define scene_updateRanking(scene) GAME_THISFN(scene_updateRanking, 0x462150, void, void *)(scene)   /* the ranking and its "new king" message */
#define ResetEvent(event) IMPORT(0x4a9168, int, void *)(event)
#define SetEvent(event) IMPORT(0x4a9178, int, void *)(event)

/* ---- objects, Win32, GL helpers (app/objects.c, app/win32.c, render/gl_helpers.c) ---- */
#define gfx_initVertexArrayExt(view) GAME_THISFN(gfx_initVertexArrayExt, 0x483fd0, int, void *)(view)   /* frees the view's vertex buffer, finds GL_EXT_vertex_array */
#define ViewVolume_dtor(view) GAME_THISFN(ViewVolume_dtor, 0x483fb0, int, void *)(view)
#define Console_dtor(console) GAME_THISFN(Console_dtor, 0x460c40, void, void *)(console)
#define Stage_dtor(stage) GAME_THISFN(Stage_dtor, 0x46ff70, void, Stage *)(stage)
#define operator_delete(p) GAME_CDECL(0x49ef24, void, void *)(p)
#define operator_new(size) GAME_CDECL(0x49f1aa, void *, u32)(size)
#define GetCurrentDirectoryA(size, out) IMPORT(0x4a9108, u32, u32, char *)(size, out)
#define GetActiveWindow() IMPORT(0x4a9320, void *, void)()
#define MessageBoxA(hwnd, text, title, type) IMPORT(0x4a9324, int, void *, const char *, const char *, u32)(hwnd, text, title, type)
#define sys_messageBox(text) GAME_FN(sys_messageBox, 0x41edf0, int, const char *)(text)   /* (a format, then its arguments) */
/* the start-up loaders (app_startupLoad's) */
#define net_clearServerSettings() GAME_FN(net_clearServerSettings, 0x4515d0, void, void)()
#define reg_readServerSettings() GAME_FN(reg_readServerSettings, 0x42bde0, int, void)()
#define math_initMathFunction() GAME_FN(math_initMathFunction, 0x46c270, int, void)()
#define reg_readCharacterSettings() GAME_FN(reg_readCharacterSettings, 0x42bee0, void, void)()
#define mech_setEmpty() GAME_FN(mech_setEmpty, 0x430390, void, void)()
#define data_loadMapInfo() GAME_FN(data_loadMapInfo, 0x42b830, u32, void)()
#define data_loadSkirmishInfo() GAME_FN(data_loadSkirmishInfo, 0x42ba40, u32, void)()
#define arena_initOptionTexts() GAME_FN(arena_initOptionTexts, 0x42bc00, void, void)()
#define profile_scanSaves() GAME_FN(profile_scanSaves, 0x4460d0, void, void)()
#define font_initMenuGrids() GAME_FN(font_initMenuGrids, 0x42f940, void, void)()
#define font_initHudGrids() GAME_FN(font_initHudGrids, 0x42fb40, void, void)()
#define timer_init() GAME_FN(timer_init, 0x4302d0, void, void)()
#define input_createDirectInput(window, instance) GAME_FN(input_createDirectInput, 0x401410, int, void *, void *)(window, instance)
#define app_checkFile_profeng() GAME_FN(app_checkFile_profeng, 0x41e6d0, u32, void)()
#define app_checkFile_profkor() GAME_FN(app_checkFile_profkor, 0x41e550, u32, void)()
#define app_checkFile_skirmish() GAME_FN(app_checkFile_skirmish, 0x41e5b0, u32, void)()
#define app_checkFile_axisgame() GAME_FN(app_checkFile_axisgame, 0x41e610, u32, void)()
#define app_checkFile_game() GAME_FN(app_checkFile_game, 0x41e670, u32, void)()
#define sound_init(hwnd) GAME_FN(sound_init, 0x467a50, int, void *)(hwnd)
#define sound_loadMenuSounds() GAME_FN(sound_loadMenuSounds, 0x42bd40, u32, void)()
#define input_initVkTable() GAME_FN(input_initVkTable, 0x431680, void, void)()
#define input_clearKeyTable2() GAME_FN(input_clearKeyTable2, 0x401780, void, void)()
#define cd_findDrive() GAME_FN(cd_findDrive, 0x401000, u32, void)()
#define tex_initBy(tm, dir, slots, fmt, w, h, a, b) GAME_THISFN(tex_initBy, 0x455080, u32, void *, const char *, int, int, int, int, u32, u32)(tm, dir, slots, fmt, w, h, a, b)
#define TextureManager_setBanks(t, a, b, c, d, e, f) GAME_THISFN(TextureManager_setBanks, 0x4569d0, u32, void *, void *, void *, void *, void *, void *, void *)(t, a, b, c, d, e, f)
#define pen_init(name) GAME_FN(pen_init, 0x46b950, int, const char *)(name)
#define shapeDat_initBy() GAME_FN(shapeDat_initBy, 0x466c00, u32, void)()
#define skelDat_initBy() GAME_FN(skelDat_initBy, 0x46afe0, u32, void)()
#define Game_ctor(scene) GAME_THISFN(Game_ctor, 0x460570, void *, void *)(scene)   /* the scene's constructor */
#define sound_initSoundTable(file, volume) GAME_FN(sound_initSoundTable, 0x456d10, int, const char *, int)(file, volume)
#define mciSendCommandA(device, msg, flags, params) IMPORT(0x4a9368, u32, u32, u32, u32, void *)(device, msg, flags, params)
#define glRotatef_bits(angle, x, y, z) IMPORT(0x4a91f8, void, u32, u32, u32, u32)(angle, x, y, z)
#define arena_editMessage() GAME_FN(arena_editMessage, 0x405010, void, void)()
#define armc_freeRing(first) GAME_FN(tunnel_removeLastRing, 0x441190, void, void *)(first)   /* frees the last ring of the tunnel whose first is *first */
#define game_returnToScreen400() GAME_FN(game_returnToScreen400, 0x41e9d0, void, void)()

/* ---- more front end (menu/menu_states.c, menu/edit_fields.c) ---- */
#define GetWindowTextLengthA(hwnd) IMPORT(0x4a92e0, int, void *)(hwnd)
#define GetWindowTextA(hwnd, out, size) IMPORT(0x4a92e4, int, void *, char *, int)(hwnd, out, size)
#define game_returnToMainMenu() GAME_FN(game_returnToMainMenu, 0x41e8b0, void, void)()
#define net_sendChat(text) GAME_FN(net_sendChat, 0x4512c0, int, const char *)(text)   /* a chat line sent */
#define input_resetKeys() GAME_FN(input_resetKeys, 0x431590, void, void)()
#define menuCamera_forward() GAME_FN(menuCamera_forward, 0x42aa30, void, void)()   /* the free camera forward */
#define menuCamera_back() GAME_FN(menuCamera_back, 0x42aad0, void, void)()   /* and back */
#define net_sendMessage(players, id, a) GAME_FN(net_sendMessage, 0x451270, void, void *, u32, int)(players, id, a)
#define setup_camera() GAME_FN(setup_camera, 0x4230e0, void, void)()
#define setup_easePanel() GAME_FN(setup_easePanel, 0x4277c0, void, void)()
#define setup_drawMenu() GAME_FN(setup_drawMenu, 0x423330, void, void)()
#define setup_frameSoundPage() GAME_FN(setup_frameSoundPage, 0x427830, void, void)()
#define setup_frameOptionsPage() GAME_FN(setup_frameOptionsPage, 0x427880, void, void)()
#define setup_frameControlsPage() GAME_FN(setup_frameControlsPage, 0x4278d0, void, void)()

/* ---- DirectInput setup (app/devices.c) ---- */
#define DirectInputCreateA(instance, version, out, outer) IMPORT(0x4a9018, long, void *, u32, void *, void *)(instance, version, out, outer)
#define input_initKeyboard(window) GAME_FN(input_initKeyboard, 0x401310, int, void *)(window)
#define input_createMouse(window) GAME_FN(input_createMouse, 0x4013a0, int, void *)(window)   /* the mouse */

#define stage_setupActorSlot(stage, a, x, y, spawn) GAME_THISFN(stage_setupActorSlot, 0x45dc00, int, Stage *, int, int, int, void *)(stage, a, x, y, spawn)   /* claim actor slot a */
#define actor_setWeaponSlot(stage, actor, slot) GAME_THISFN(actor_setWeaponSlot, 0x45e810, void, void *, int, int)(stage, actor, slot)   /* select a weapon slot */
#define profile_checkAndSendRecord() GAME_FN(profile_checkAndSendRecord, 0x4327f0, void, void)()

/* ---- start-up objects (app/statics.c) ---- */
#define ErrorLog_ctor(self, name, b) GAME_THISFN(ErrorLog_ctor, 0x46c5a0, void *, void *, const char *, int)(self, name, b)   /* a named record (vtable 0x4aa2a0) */
#define atexit(f) GAME_CDECL(0x49ef9c, int, void (*)(void))(f)

/* ---- small classes (app/classes.c) ---- */
#define fclose(f) GAME_CDECL(0x49e7e0, u32, void *)(f)
#define arena_loadSettings(path) GAME_FN(arena_loadSettings, 0x40d4e0, int, const char *)(path)   /* an arena settings file; 0 if missing */
#define str_dropLast(s) GAME_FN(str_dropLast, 0x44ac70, int, char *)(s)   /* s cut to its last character (app/small.c) */
#define TextureManager_clear(self) GAME_THISFN(TextureManager_clear, 0x4569a0, int, void *)(self)
#define Model_clear(self) GAME_THISFN(Model_clear, 0x464bb0, int, void *)(self)
#define ShapeManager_clear(self) GAME_THISFN(ShapeManager_clear, 0x466a20, int, void *)(self)
#define SkeletonManager_clear(self) GAME_THISFN(SkeletonManager_clear, 0x46ae70, int, void *)(self)
#define CollisionVolume_clear(self) GAME_THISFN(CollisionVolume_clear, 0x4813a0, int, void *)(self)
#define TimeSync_clear(self) GAME_THISFN(TimeSync_clear, 0x487480, int, void *)(self)
#define Light_clearCounts(self) GAME_THISFN(Light_clearCounts, 0x483d60, int, void *)(self)
#define TextureManager_reset(self) GAME_THISFN(TextureManager_reset, 0x4569b0, int, void *)(self)
#define ShapeManager_release(self) GAME_THISFN(ShapeManager_release, 0x466a30, int, void *)(self)
#define SkeletonManager_release(self) GAME_THISFN(SkeletonManager_release, 0x46ae80, int, void *)(self)
#define CollisionVolume_release(self) GAME_THISFN(CollisionVolume_release, 0x4813b0, int, void *)(self)
#define Model_release(self) GAME_THISFN(Model_release, 0x464bc0, int, void *)(self)
#define TextureManager_dtor(self) GAME_THISFN(TextureManager_dtor, 0x456990, int, void *)(self)
#define Light_dtor(self) GAME_THISFN(Light_dtor, 0x483d50, int, void *)(self)
#define CollisionVolume_dtor(self) GAME_THISFN(CollisionVolume_dtor, 0x481390, int, void *)(self)
#define Model_dtor(self) GAME_THISFN(Model_dtor, 0x464ba0, int, void *)(self)
#define ShapeManager_dtor(self) GAME_THISFN(ShapeManager_dtor, 0x466a10, int, void *)(self)
#define SkeletonManager_dtor(self) GAME_THISFN(SkeletonManager_dtor, 0x46ae60, int, void *)(self)
#define TimeSync_dtor(self) GAME_THISFN(TimeSync_dtor, 0x487470, void, void *)(self)
#define Scene_dtor(self) GAME_THISFN(Scene_dtor, 0x48b410, void, void *)(self)
#define BMPRGBFile_dtor(self) GAME_THISFN(BMPRGBFile_dtor, 0x46ce60, void, void *)(self)
#define ErrorLog_dtor(self) GAME_THISFN(ErrorLog_dtor, 0x46c5e0, void, void *)(self)
#define Texture_dtor(self) GAME_THISFN(Texture_dtor, 0x455030, u32, void *)(self)   /* in fact Texture's destructor */

/* ---- start-up pieces called by the start-up pairs (app/statics.c) ---- */
#define BMPRGBFile_initLog() GAME_FN(BMPRGBFile_initLog, 0x46ccb0, void *, void)()
#define CollisionVolume_initLog() GAME_FN(CollisionVolume_initLog, 0x481340, void *, void)()
#define Console_initLog() GAME_FN(Console_initLog, 0x460520, void *, void)()
#define Light_initLog() GAME_FN(Light_initLog, 0x483d00, void *, void)()
#define PackedColor_initLog() GAME_FN(PackedColor_initLog, 0x46da70, void *, void)()
#define RealColor_initLog() GAME_FN(RealColor_initLog, 0x46d270, void *, void)()
#define Scene_initLog() GAME_FN(Scene_initLog, 0x48b3c0, void *, void)()
#define ShapeManager_initLog() GAME_FN(ShapeManager_initLog, 0x4669c0, void *, void)()
#define Shape_initLog() GAME_FN(Shape_initLog, 0x463b30, void *, void)()
#define SkeletonManager_initLog() GAME_FN(SkeletonManager_initLog, 0x46ae10, void *, void)()
#define Skeleton_initLog() GAME_FN(Skeleton_initLog, 0x469930, void *, void)()
#define Sound_initLog() GAME_FN(Sound_initLog, 0x456c90, void *, void)()
#define Stage_initLog() GAME_FN(Stage_initLog, 0x46ff20, void *, void)()
#define TextureManager_ctor() GAME_FN(TextureManager_ctor, 0x42b330, int, void)()
#define TextureManager_initLog() GAME_FN(TextureManager_initLog, 0x456940, void *, void)()
#define Texture_initLog() GAME_FN(Texture_initLog, 0x454fe0, void *, void)()
#define TimeSync_initLog() GAME_FN(TimeSync_initLog, 0x4873e0, void *, void)()
#define UnitPartInfo_initLog() GAME_FN(UnitPartInfo_initLog, 0x46f360, void *, void)()
#define UnitPoseInfo_initLog() GAME_FN(UnitPoseInfo_initLog, 0x46f3c0, void *, void)()
#define Unit_initLog() GAME_FN(Unit_initLog, 0x46f420, void *, void)()
#define ViewVolume_initLog() GAME_FN(ViewVolume_initLog, 0x483f60, void *, void)()
#define static_initTimeSync() GAME_FN(static_initTimeSync, 0x468720, void, void)()
#define static_initTex64x64() GAME_FN(static_initTex64x64, 0x42b130, void, void)()
#define static_initTex128x64() GAME_FN(static_initTex128x64, 0x42b1a0, void, void)()
#define static_initTex256x64() GAME_FN(static_initTex256x64, 0x42b1f0, void, void)()
#define static_initTex128x128() GAME_FN(static_initTex128x128, 0x42b240, void, void)()
#define static_initTex256x256() GAME_FN(static_initTex256x256, 0x42b2e0, void, void)()
#define static_initTex256x128() GAME_FN(static_initTex256x128, 0x42b290, void, void)()
#define static_registerTex64x64Dtor() GAME_FN(static_registerTex64x64Dtor, 0x42b170, int, void)()
#define static_registerTex128x64Dtor() GAME_FN(static_registerTex128x64Dtor, 0x42b1c0, int, void)()
#define static_registerTex256x64Dtor() GAME_FN(static_registerTex256x64Dtor, 0x42b210, int, void)()
#define static_registerTex128x128Dtor() GAME_FN(static_registerTex128x128Dtor, 0x42b260, int, void)()
#define static_registerTex256x128Dtor() GAME_FN(static_registerTex256x128Dtor, 0x42b2b0, int, void)()
#define static_registerTex256x256Dtor() GAME_FN(static_registerTex256x256Dtor, 0x42b300, int, void)()
#define static_registerTextureManagerDtor() GAME_FN(static_registerTextureManagerDtor, 0x42b370, int, void)()
#define static_registerTextureLogDtor() GAME_FN(static_registerTextureLogDtor, 0x455000, int, void)()
#define static_registerTextureManagerLogDtor() GAME_FN(static_registerTextureManagerLogDtor, 0x456960, int, void)()
#define static_registerSoundLogDtor() GAME_FN(static_registerSoundLogDtor, 0x456cb0, int, void)()
#define static_registerConsoleLogDtor() GAME_FN(static_registerConsoleLogDtor, 0x460540, int, void)()
#define static_registerShapeLogDtor() GAME_FN(static_registerShapeLogDtor, 0x463b50, int, void)()
#define static_registerShapeManagerLogDtor() GAME_FN(static_registerShapeManagerLogDtor, 0x4669e0, int, void)()
#define static_registerTimeSyncDtor() GAME_FN(static_registerTimeSyncDtor, 0x468730, int, void)()
#define static_registerSkeletonLogDtor() GAME_FN(static_registerSkeletonLogDtor, 0x469950, int, void)()
#define static_registerSkeletonManagerLogDtor() GAME_FN(static_registerSkeletonManagerLogDtor, 0x46ae30, int, void)()
#define static_registerBMPRGBFileLogDtor() GAME_FN(static_registerBMPRGBFileLogDtor, 0x46ccd0, int, void)()
#define static_registerRealColorLogDtor() GAME_FN(static_registerRealColorLogDtor, 0x46d290, int, void)()
#define static_registerPackedColorLogDtor() GAME_FN(static_registerPackedColorLogDtor, 0x46da90, int, void)()
#define static_registerUnitPartInfoLogDtor() GAME_FN(static_registerUnitPartInfoLogDtor, 0x46f380, int, void)()
#define static_registerUnitPoseInfoLogDtor() GAME_FN(static_registerUnitPoseInfoLogDtor, 0x46f3e0, int, void)()
#define static_registerUnitLogDtor() GAME_FN(static_registerUnitLogDtor, 0x46f440, int, void)()
#define static_registerStageLogDtor() GAME_FN(static_registerStageLogDtor, 0x46ff40, int, void)()
#define static_registerCollisionVolumeLogDtor() GAME_FN(static_registerCollisionVolumeLogDtor, 0x481360, int, void)()
#define static_registerLightLogDtor() GAME_FN(static_registerLightLogDtor, 0x483d20, int, void)()
#define static_registerViewVolumeLogDtor() GAME_FN(static_registerViewVolumeLogDtor, 0x483f80, int, void)()
#define static_registerTimeSyncLogDtor() GAME_FN(static_registerTimeSyncLogDtor, 0x487400, int, void)()
#define static_registerSceneLogDtor() GAME_FN(static_registerSceneLogDtor, 0x48b3e0, int, void)()

/* ---- small pieces (app/small.c) ---- */
#define set_colour_bits(c, r, g, b, a) GAME_FN(Color4_set, 0x41f0e0, void, Colour *, u32, u32, u32, u32)(c, r, g, b, a)   /* Color4_set with float bits */
#define set4ints(a, b, c, d, out) GAME_FN(set4ints, 0x42eeb0, void, int, int, int, int, int *)(a, b, c, d, out)
#define tunnel_appendRing(head) GAME_FN(tunnel_appendRing, 0x441120, u32, void *)(head)   /* a ring added to the background tunnel */
#define playerRecord_resetColourGrid(stage, p) GAME_THISFN(playerRecord_resetColourGrid, 0x473470, void, Stage *, int)(stage, p)   /* player p's colour grid cleared */
#define actor_deactivate(stage, i) GAME_THISFN(actor_deactivate, 0x45dca0, void, void *, int)(stage, i)
#define Skeleton_clear(self) GAME_THISFN(Skeleton_clear, 0x469980, void, void *)(self)
#define partList_clear(self) GAME_THISFN(partList_clear, 0x46f480, void, void *)(self)
#define partList_release(self) GAME_THISFN(partList_release, 0x46f4b0, int, void *)(self)
#define str_length(s) GAME_FN(str_length, 0x44ac50, int, const char *)(s)

/* ---- batch: front-end records, objects, video tables ---- */
#define net_claimPlayerSlot() GAME_FN(net_claimPlayerSlot, 0x451450, u8, void)()   /* a free network player slot claimed (0xff: none) */
#define net_takePlayerSlot(slot, id) GAME_FN(net_takePlayerSlot, 0x4514a0, void, u32, int)(slot, id)   /* player slot taken by id */
#define space_disableUnit(unit) GAME_THISFN(space_disableUnit, 0x480460, void, void *)(unit)
#define space_enableUnit(unit) GAME_THISFN(space_enableUnit, 0x480480, void, void *)(unit)
#define tex_markMaterialChanged(self, m) GAME_THISFN(tex_markMaterialChanged, 0x456820, void, void *, int)(self, m)   /* material m marked changed */
#define profile_resetPreview() GAME_FN(profile_resetPreview, 0x44b7a0, u32, void)()
#define ptx_initClampTable() GAME_FN(ptx_initClampTable, 0x46e320, void, void)()
#define ptx_initYCbCrTables() GAME_FN(ptx_initYCbCrTables, 0x46efd0, void, void)()
#define ptx_initDequantTables(q) GAME_FN(ptx_initDequantTables, 0x46e2b0, void, int)(q)
#define ptx_initColourTables() GAME_FN(ptx_initColourTables, 0x46e7c0, void, void)()
#define ptx_initQuantTables(q) GAME_FN(ptx_initQuantTables, 0x46e9b0, void, int)(q)
#define ptx_error(...) ((int (CDECL *)(int, const char *, ...))FN_ADDR(ptx_error, 0x46e260))(__VA_ARGS__)   /* app/ptx_decode.c */
#define ptx_crtlError(...) ((int (CDECL *)(int, const char *, ...))FN_ADDR(ptx_crtlError, 0x46e1e0))(__VA_ARGS__)
#define ptx_startBitReader(p) GAME_FN(ptx_startBitReader, 0x46f090, void, const u8 *)(p)   /* the bit reader started at p */
#define ptx_readBlock(block) GAME_FN(ptx_readBlock, 0x46f0b0, int, int *)(block)   /* one block's coefficients; the bit position */
#define ptx_inverseDct(in, out) GAME_FN(ptx_inverseDct, 0x46e380, void, const int *, u8 *)(in, out)
#define ptx_toRgb(y, dst, n) GAME_FN(ptx_toRgb, 0x46e830, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_toRgba(y, dst, n) GAME_FN(ptx_toRgba, 0x46e8e0, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_layoutBlocks(src, dst, w, h, bpp) GAME_FN(ptx_layoutBlocks, 0x46ea30, void, const u8 *, u8 *, int, int, int)(src, dst, w, h, bpp)

#define popup_layout() GAME_FN(popup_layout, 0x431c00, void, void)()
#define loginDialog_layout() GAME_FN(loginDialog_layout, 0x431b70, void, void)()
#define tex_recolourMaterial(set, m, h1, c1, v1, h2, c2, v2) GAME_THISFN(tex_recolourMaterial, 0x456860, void, void *, int, u32, u32, u32, u32, u32, u32)(set, m, h1, c1, v1, h2, c2, v2)
#define image_addColour(px, mode, part, colour) GAME_FN(image_addColour, 0x464a70, void, u8 *, int, const u32 *, const u8 *)(px, mode, part, colour)   /* a colour added to a part's RGBA pixels */
#define spaceSlot_clear(slot) GAME_THISFN(spaceSlot_clear, 0x480440, void, int *)(slot)
#define shape_markMaterialsChanged(shape) GAME_THISFN(shape_markMaterialsChanged, 0x466560, void, void *)(shape)
#define shape_recolourMaterials(shape, h1, c1, v1, h2, c2, v2) GAME_THISFN(shape_recolourMaterials, 0x4665c0, void, void *, u32, u32, u32, u32, u32, u32)(shape, h1, c1, v1, h2, c2, v2)

#define crt_free(p) GAME_CDECL(0x49ee81, u32, void *)(p)
#define crt_fopen(name, mode) GAME_CDECL(0x49e9ca, void *, const char *, const char *)(name, mode)
#define crt_fwrite(p, size, count, f) GAME_CDECL(0x49f58a, u32, const void *, u32, u32, void *)(p, size, count, f)
#define crt_rand() GAME_CDECL(0x49f92c, int, void)()
#define save_cryptRecord(rec, key) GAME_FN(save_cryptRecord, 0x445ee0, void, u8 *, u8)(rec, key)
#define crypt_record104(rec, key) GAME_FN(crypt_record104, 0x445f10, void, u8 *, u8)(rec, key)   /* a 0x104-byte record (un)scrambled */
#define profile_writeCleared(count) GAME_FN(profile_writeCleared, 0x445f70, u32, int)(count)
#define profile_readHeader() GAME_FN(profile_readHeader, 0x4474a0, u32, void)()   /* a 0x3ac-byte profile record scrambled (menu/profile_misc.c) */
#define mech_storeToProfile() GAME_FN(mech_storeToProfile, 0x4464b0, void, void)()   /* the current profile's record gathered (0x9f1718) */
#define crypt_record80(p, key) GAME_FN(crypt_record80, 0x445f40, void, u8 *, u8)(p, key)   /* a 0x80-byte record unscrambled */
#define fread_scrambled(p, size, count, f) GAME_FN(file_readScrambled, 0x46cbe0, u32, void *, u32, u32, void *)(p, size, count, f)   /* fread, each byte unscrambled (rotated left, xor 0x59) */
#define bullet_drawTrail(stage, i, view) GAME_THISFN(bullet_drawTrail, 0x47ca70, void, Stage *, int, void *)(stage, i, view)   /* bullet i's trail drawn */
#define recorder_noteStub(self, a, b, c, d) GAME_THISFN(recorder_noteStub, 0x48b450, void, void *, int, int, int, int)(self, a, b, c, d)
#define mem_free(p) GAME_FN(mem_free, 0x467d60, u32, void *)(p)   /* p deleted (0 for none) */

#define g_menuState g_screen   /* the front end's screen (300 the main menu) */
#define sessionList_sort() GAME_FN(sessionList_sort, 0x4065e0, void, void)()   /* the session list sorted */

/* ---- the projection switch and the menus' 2D (menu_2d.c) ---- */
#define GL_LINES 1
#define GL_DEPTH_TEST 0x0b71
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define glViewport(x, y, w, h) IMPORT(0x4a91d4, void, int, int, int, int)(x, y, w, h)
#define glMatrixMode(mode) IMPORT(0x4a91fc, void, u32)(mode)
#define gluPerspective(angle, aspect, zNear, zFar) ((void (STDCALL *)(double, double, double, double))*(const u32 *)STR(0x4a9048, "j\300\n"))(angle, aspect, zNear, zFar)
#define gluOrtho2D(left, right, bottom, top) ((void (STDCALL *)(double, double, double, double))*(const u32 *)STR(0x4a9050, "|\300\n"))(left, right, bottom, top)

/* ---- small methods and resets (app/small.c, app/classes.c, match/actor_slots.c, load/space_pools.c, render/rotations.c) ---- */
#define path_normalize(path) GAME_FN(path_normalize, 0x46cb60, char *, char *)(path)   /* upper-cased in place, '/' -> '\' */
#define stage_setTextureFolder(self, folder) GAME_THISFN(stage_setTextureFolder, 0x470f80, char *, void *, const char *)(self, folder)
#define TimeSync_ctor(self) GAME_THISFN(TimeSync_ctor, 0x487430, void *, void *)(self)
#define Skeleton_release(self) GAME_THISFN(Skeleton_release, 0x4699a0, int, void *)(self)   /* a skeleton released */
#define stage_clearFrags(stage) GAME_THISFN(stage_clearFrags, 0x45df90, void, Stage *)(stage)
#define stage_resetPlayerRecords(stage) GAME_THISFN(stage_resetPlayerRecords, 0x474480, void, Stage *)(stage)   /* the 16 player records reset */
#define stage_clearActorSlots(stage) GAME_THISFN(stage_clearActorSlots, 0x45e070, void, Stage *)(stage)
#define actor_resetSlot(stage, i) GAME_THISFN(actor_resetSlot, 0x4743e0, void, void *, int)(stage, i)
#define collisionPlane_clear(self) GAME_THISFN(collisionPlane_clear, 0x47db50, int, void *)(self)   /* a collision plane cleared */
#define spaceNode_clear(self) GAME_THISFN(spaceNode_clear, 0x480430, int, void *)(self)   /* a node */
#define spaceBlock_clear(self) GAME_THISFN(spaceBlock_clear, 0x4804a0, int, void *)(self)   /* a block */
#define quat_fromAxisAngle(q, rotation) GAME_THISFN(quat_fromAxisAngle, 0x47d0b0, void, float *, const float *)(q, rotation)
#define Mat4_fromQuat(m, q) GAME_FN(Mat4_fromQuat, 0x47d8a0, void, float *, const float *)(m, q)   /* quaternion -> matrix */

/* ---- (render/shape_colours.c, app/small.c, menu/menu_records.c callers) ---- */
#define shape_setTint(model, h1, c1, v1, h2, c2, v2) GAME_THISFN(shape_setTint, 0x467660, void, void *, u32, u32, u32, u32, u32, u32)(model, h1, c1, v1, h2, c2, v2)
#define model_clearTint(model) GAME_THISFN(model_clearTint, 0x4675f0, void, void *)(model)   /* the model's shapes' own colours back */
#define script_reset(stage) GAME_THISFN(script_reset, 0x48fca0, int, Stage *)(stage)
#define briefing_hitTest(x, y) GAME_FN(briefing_hitTest, 0x443910, int, int, int)(x, y)   /* which skirmish settings arrow is at (x, y) */
#define undo_push() GAME_FN(undo_push, 0x443d80, u32, void)()   /* skirmish settings: the pending step pushed */
#define undo_pop() GAME_FN(undo_pop, 0x443de0, u32, void)()   /* one step undone */

/* ---- the lobby's and room's screens (menu/lobby_states.c) ---- */
#define arena_copyProfile() GAME_FN(arena_copyProfile, 0x404930, void, void)()   /* the player's record from the profile */
#define mapList_layout() GAME_FN(mapList_layout, 0x403300, void, void)()   /* the map list laid out */
#define lobby_drawArenaTitle() GAME_FN(lobby_drawArenaTitle, 0x404980, void, void)()
#define mapList_init() GAME_FN(mapList_init, 0x403420, void, void)()   /* the map on/off list reset */
#define room_loadSettingsRecord() GAME_FN(room_loadSettingsRecord, 0x433700, void, void)()   /* the room settings copied */

/* ---- the PTX video decoder (app/ptx_decode.c) ---- */
#define ptx_readBits(out, n) GAME_FN(ptx_readBits, 0x46f230, int, int *, int)(out, n)   /* the next n bits of the stream */
#define ptx_readDcDiff(out) GAME_FN(ptx_readDcDiff, 0x46f190, void, int *)(out)   /* a DC difference */
#define ptx_readAcSymbol(out, run) GAME_FN(ptx_readAcSymbol, 0x46f2a0, void, int *, int *)(out, run)   /* an AC symbol */

/* ---- (net/net_sessions.c, render/rotations.c) ---- */
#define record_swap(a, b) GAME_FN(record_swap, 0x4065a0, void, void *, void *)(a, b)   /* two session records swapped */
#define Vec3_normalize(v) GAME_THISFN(Vec3_normalize, 0x467760, long double, float *)(v)   /* returns the length, unrounded */

/* ---- (load/lists.c, render/shape_colours.c, net/net_tables.c, match/map_objects.c, menu/lobby_states.c) ---- */
#define crt_malloc(size) GAME_CDECL(0x49eeb0, void *, u32)(size)
#define net_clearServers() GAME_FN(net_clearServers, 0x454690, void, void)()                  /* the server table cleared */
#define net_resolveHost(host) GAME_FN(net_resolveHost, 0x4547d0, int, const char *)(host)   /* 1: resolved (into 0xa0d320) */
#define net_freeBuffers() GAME_FN(net_freeBuffers, 0x4519b0, u32, void)()
#define net_clearServerList() GAME_FN(net_clearServerList, 0x452e60, void, void)()   /* the game list table cleared */
#define net_receiveLobbyReply() GAME_FN(net_receiveLobbyReply, 0x452a30, void, void)()   /* the list of games received */
#define net_receiveGameServerReply() GAME_FN(net_receiveGameServerReply, 0x452bd0, void, void)()   /* the server list received */
#define net_receiveServerReply() GAME_FN(net_receiveServerReply, 0x452d70, void, void)()   /* the player list received */
#define net_clearRoomList() GAME_FN(net_clearRoomList, 0x452e80, void, void)()   /* the server table cleared */
#define net_clearPlayerList() GAME_FN(net_clearPlayerList, 0x452ea0, void, void)()   /* the player list cleared */
#define jmp_net_getLocalAddress() GAME_FN(jmp_net_getLocalAddress, 0x4532e0, int, void)()   /* this machine's address (0xa0b43c) */
#define crt_strtok(s, delimiters) GAME_CDECL(0x49ec3b, char *, char *, const char *)(s, delimiters)   /* the game's CRT strtok */
#define crt_atoi(s) GAME_CDECL(0x49ec09, int, const char *)(s)
#define tunnelRing_build(node, value) GAME_FN(tunnelRing_build, 0x440e20, u32, void *, int)(node, value)
#define tex_tintHsv(c, dh, ds, dv) GAME_THISFN(tex_tintHsv, 0x46d950, void, float *, u32, u32, u32)(c, dh, ds, dv)
#define skel_getSkeletonPtrBy(cache, name) GAME_THISFN(skel_getSkeletonPtrBy, 0x46b1a0, void *, void *, u32)(cache, name)
#define mech_unpackFromRecord() GAME_FN(mech_unpackFromRecord, 0x40ddb0, void, void)()   /* the mech unpacked */

/* ---- (render/tex_colours.c) ---- */
#define tex_rgbToHsv(r, g, b, h, s, v) GAME_FN(tex_rgbToHsv, 0x46def0, void, u32, u32, u32, float *, float *, float *)(r, g, b, h, s, v)   /* RGB -> HSV (r, g, b as float bits) */
#define color_hsvToRgb(h, s, v, r, g, b) GAME_FN(color_hsvToRgb, 0x46e050, void, u32, u32, u32, float *, float *, float *)(h, s, v, r, g, b)   /* (h, s, v as float bits) */
#define tex_tintRgba(rgba, dh, ds, dv) GAME_THISFN(tex_tintRgba, 0x46de20, int, u8 *, u32, u32, u32)(rgba, dh, ds, dv)   /* an RGBA byte colour tinted */

/* ---- (net/net_sessions.c) ---- */
#define net_sessionCount() GAME_FN(net_sessionCount, 0x4532a0, int, void)()   /* the session list's count */
#define net_sessionValue(i) GAME_FN(net_sessionValue, 0x4532b0, int, int)(i)   /* session i's record */

#define room_copyJoinedSettings() GAME_FN(room_copyJoinedSettings, 0x432be0, void, void)()   /* the joined game's settings into the room screen */
#define room_takeReceivedSettings() GAME_FN(room_takeReceivedSettings, 0x432db0, void, void)()   /* a received game's settings into the room */
#define field_editGameName() GAME_FN(field_editGameName, 0x433b00, u32, void)()   /* the game's name opened for typing */
#define field_editGamePassword() GAME_FN(field_editGamePassword, 0x433bb0, u32, void)()   /* the game's password opened for typing */
#define chat_closeEdit() GAME_FN(chat_closeEdit, 0x433c70, void, void)()   /* the chat edit control closed, the line taken */
#define login_send() GAME_FN(login_send, 0x434490, void, void)()   /* the login sent */
#define loginForm_openField(k) GAME_FN(loginForm_openField, 0x433e60, int, int)(k)   /* the login form's field k opened for typing */
#define room_drawTunnel() GAME_FN(room_drawTunnel, 0x4388e0, void, void)()   /* the game room's tunnel */
#define room_mergeReceivedSessions() GAME_FN(room_mergeReceivedSessions, 0x434ff0, void, void)()   /* the list of games asked for again */
#define gameList_draw() GAME_FN(gameList_draw, 0x43adc0, void, void)()   /* the game room's list of games drawn */
#define room_joinSession(i) GAME_FN(room_joinSession, 0x434dd0, u32, int)(i)   /* game i of the list joined */
#define gameList_hitTest(x, y) GAME_FN(gameList_hitTest, 0x432300, int, int, int)(x, y)   /* the game list's control at (x, y) */
#define room_startChat() GAME_FN(room_startChat, 0x434da0, void, void)()   /* the selected game joined */
#define gameList_open() GAME_FN(gameList_open, 0x434d00, int, void)()    /* the search asked for: 1 sent */
#define createDialog_hitTest(x, y) GAME_FN(createDialog_hitTest, 0x432200, int, int, int)(x, y)   /* the create-game dialog's button at (x, y) */
#define room_openDialog4d() GAME_FN(room_openDialog4d, 0x4338c0, u32, void)()
#define dplay_host(name, player, map, a, b, c, d, corp) GAME_FN(dplay_host, 0x453090, int, const void *, const char *, int, int, int, int, int, int)(name, player, map, a, b, c, d, corp)   /* the arena hosted: 0 failed */
#define net_asyncSelect(hwnd, socket) GAME_FN(net_asyncSelect, 0x452170, int, void *, int)(hwnd, socket)
#define lobby_keepArenaSettings() GAME_FN(lobby_keepArenaSettings, 0x405140, u32, void)()   /* the arena's settings kept (0x4db528 into 0x4ded20) */
#define room_keepSettings() GAME_FN(room_keepSettings, 0x433640, u32, void)()    /* the room's settings kept (0x4df9c8 into 0x5b1b30) */
#define arena_drawTunnel() GAME_FN(arena_drawTunnel, 0x4091b0, void, void)()   /* the arena's tunnel */
#define dplay_listSessions() GAME_FN(dplay_listSessions, 0x453260, u32, void)()   /* DirectPlay's session list polled */
#define arenaList_rebuild() GAME_FN(arenaList_rebuild, 0x406810, void, void)()
#define arena_mergeReceivedSessions() GAME_FN(arena_mergeReceivedSessions, 0x406640, void, void)()   /* the list of games asked for again */
#define arena_drawGameList() GAME_FN(arena_drawGameList, 0x40a070, void, void)()   /* the arena's list of games drawn */
#define arena_joinListed(i) GAME_FN(arena_joinListed, 0x406200, u32, int)(i)   /* game i joined (99999: the one typed) */
#define arena_joinSession(i) GAME_FN(arena_joinSession, 0x405690, u32, int)(i)   /* session i joined */
#define sys_checkClockTampering() GAME_FN(sys_checkClockTampering, 0x43f300, void, void)()
#define glWindow_init(title, w, h, bits, depth, full, hwnd, flag) GAME_FN(glWindow_init, 0x468250, void, const char *, int, int, int, int, int, void *, int)(title, w, h, bits, depth, full, hwnd, flag)
#define map_fileExists(map) GAME_FN(map_fileExists, 0x41e7c0, int, int)(map)   /* the map's files loaded: 0 failed */
#define pilotRecord_syncCopies() GAME_FN(pilotRecord_syncCopies, 0x41e390, void, void)()
#define scene_setTextureFolder(scene, map) GAME_THISFN(scene_setTextureFolder, 0x461ec0, void, Scene *, const char *)(scene, map)
#define actor_levelFromValue(points) GAME_FN(actor_levelFromValue, 0x4326f0, int, int)(points)   /* the level (1 ..) the points reach */
#define net_receiveAll() GAME_FN(net_receiveAll, 0x450a60, u32, void)()
#define net_getLocalAddress() GAME_FN(net_getLocalAddress, 0x454220, int, void)()   /* this machine's address as text (0xa0b43c) */
#define missionsel_drawSettingsScreen() GAME_FN(missionsel_drawSettingsScreen, 0x448ac0, void, void)()
#define missionsel_drawScreen() GAME_FN(missionsel_drawScreen, 0x449a50, void, void)()
#define missionList_draw() GAME_FN(missionList_draw, 0x444f40, void, void)()
#define missionBriefing_draw() GAME_FN(missionBriefing_draw, 0x4456b0, void, void)()
#define arenaNameDialog_hitTest(x, y) GAME_FN(arenaNameDialog_hitTest, 0x404460, int, int, int)(x, y)   /* the arena name dialog's control at (x, y) */
#define arena_openSession(kind, host) GAME_FN(arena_openSession, 0x452ec0, int, u32, const char *)(kind, host)   /* a DirectPlay slot opened */
#define lobby_openConnection() GAME_FN(lobby_openConnection, 0x4060f0, int, void)()   /* the lobby server connection opened: 1 done */
#define arenaGameList_hitTest(x, y) GAME_FN(arenaGameList_hitTest, 0x4044a0, int, int, int)(x, y)   /* the arena lobby's button under (x, y), -1 none */
#define arena_chatLine() GAME_FN(arena_chatLine, 0x405200, void, void)()   /* the arena screen's chat line opened */
#define arena_editTitle() GAME_FN(arena_editTitle, 0x405230, void, void)()   /* the arena title's edit field opened */
#define menu_showMessage(i) GAME_FN(menu_showMessage, 0x41ee40, u32, int)(i)   /* message i in the message box */
#define reg_writeCharacterSettings() GAME_FN(reg_writeCharacterSettings, 0x432400, u32, void)()

/* ---- the screens' set-ups (menu/screen_enter.c): rectangle builders and resets ---- */
#define arena_clearSessionEntry() GAME_FN(arena_clearSessionEntry, 0x4045e0, void, void)()
#define lobbyTop_layout() GAME_FN(lobbyTop_layout, 0x403f30, void, void)()
#define arenaNameDialog_layout() GAME_FN(arenaNameDialog_layout, 0x403f80, void, void)()
#define arenaGameList_layout() GAME_FN(arenaGameList_layout, 0x404010, void, void)()
#define arenaDialogBox_layout() GAME_FN(arenaDialogBox_layout, 0x404120, void, void)()
#define arenaOptions_layout() GAME_FN(arenaOptions_layout, 0x404190, void, void)()
#define arenaCreate_layout() GAME_FN(arenaCreate_layout, 0x404150, void, void)()
#define setupSound_layout() GAME_FN(setupSound_layout, 0x420300, void, void)()
#define setupOptions_layout() GAME_FN(setupOptions_layout, 0x420480, void, void)()
#define setupControl_layout() GAME_FN(setupControl_layout, 0x420510, void, void)()
#define roomLogin_layout() GAME_FN(roomLogin_layout, 0x431ae0, void, void)()
#define account_layout() GAME_FN(account_layout, 0x431c50, void, void)()
#define gameList_layout() GAME_FN(gameList_layout, 0x431ce0, void, void)()
#define gameListStop_layout() GAME_FN(gameListStop_layout, 0x431db0, void, void)()
#define roomSettings_layout() GAME_FN(roomSettings_layout, 0x431de0, void, void)()
#define ranking_layout() GAME_FN(ranking_layout, 0x432040, void, void)()
#define leaveDialog_layout() GAME_FN(leaveDialog_layout, 0x431aa0, void, void)()

#define viewVolume_addQuad(view, texture, uv0, uv1, colour, points, kind, flag) GAME_THISFN(viewVolume_addQuad, 0x4848e0, void, void *, int, const u32 *, const u32 *, const u32 *, const float *, u32, int)(view, texture, uv0, uv1, colour, points, kind, flag)   /* a textured quad into the view volume */

#define net_findFreeSession() GAME_FN(net_findFreeSession, 0x454110, int, void)()   /* the first free session slot, or -1 */

#define Mat4_transformPoint(out, m, p) GAME_FN(Mat4_transformPoint, 0x484860, void, float *, const float *, const float *)(out, m, p)

/* ---- (app/devices.c, net/net_tables.c, app/small.c, render/object_list.c, menu/armc_misc.c) ---- */
#define dplay_send(from, to, flags, data, size) GAME_FN(dplay_send, 0x450bf0, int, u32, u32, u32, const void *, u32)(from, to, flags, data, size)   /* a DirectPlay message sent */
#define space_setBy(space, lo, hi, nx, ny, nz, a, b, depth) GAME_THISFN(space_setBy, 0x4819b0, u32, void *, void *, void *, int, int, int, int, int, int)(space, lo, hi, nx, ny, nz, a, b, depth)
#define shape_bindPartTextures(shape) GAME_THISFN(shape_bindPartTextures, 0x466650, u32, void *)(shape)   /* a shape's textures bound */
#define armc_mainPageClicks() GAME_FN(armc_mainPageClicks, 0x40fb20, u32, void)()
#define armc_partScreenClicks() GAME_FN(armc_partScreenClicks, 0x40fd30, u32, void)()
#define armc_colourScreenInput() GAME_FN(armc_colourScreenInput, 0x40ff40, u32, void)()

#define Mat4_fromAxisAngle(m, rotation) GAME_FN(Mat4_fromAxisAngle, 0x47d9a0, void, float *, const float *)(m, rotation)   /* (angle, axis) -> matrix */

/* the DirectPlay slot functions by connection kind (src/net/dplay_slots.c) */
#define dplay_slotHost(kind, a1, a2, a3, a4, a5, a6, a7, a8) 	GAME_CDECL(((const u32[4]){ FN_ADDR(dplaySlot0_host, 0x4549e0), FN_ADDR(dplaySlot1_host, 0x454b00), FN_ADDR(dplaySlot2_host, 0x454c10), FN_ADDR(dplaySlot3_host, 0x454d20) })[kind], int, int, int, int, int, int, int, int, int)(a1, a2, a3, a4, a5, a6, a7, a8)
#define dplay_slotJoin(kind, a1, a2, a3, a4) 	GAME_CDECL(((const u32[4]){ FN_ADDR(dplaySlot0_join, 0x454a20), FN_ADDR(dplaySlot1_join, 0x454b40), FN_ADDR(dplaySlot2_join, 0x454c50), FN_ADDR(dplaySlot3_join, 0x454d60) })[kind], int, int, int, int, int)(a1, a2, a3, a4)

/* the error reporters (src/app/error_log.c): a message, or a fatal one that ends the game */
#define sys_errorTerminate(...) GAME_FN(sys_errorTerminate, 0x46c950, void, const char *, ...)(__VA_ARGS__)

/* a menu button's outline as menu_pointInPolygon takes it on the stack: the edge count, then the corners' xs and ys */
typedef struct { int n, x[5], y[5]; } Outline;
#define point_in_outline(x, y, outline) GAME_FN(menu_pointInPolygon, 0x41eea0, int, int, int, Outline)(x, y, outline)   /* menu_pointInPolygon */

/* the Korean text passes (text/text_codes.c): the lead glyphs, and the vowel and tail glyphs, at 13 and 31 units */
#define text_hanCho(x, y, s) GAME_FN(text_hanCho, 0x401870, void, int, int, const char *)(x, y, s)
#define text_hanJungJong(x, y, s) GAME_FN(text_hanJungJong, 0x401aa0, void, int, int, const char *)(x, y, s)
#define text_hanCho32(x, y, s) GAME_FN(text_drawHangul31, 0x401ce0, void, int, int, const char *)(x, y, s)
#define text_hanJungJong32(x, y, s) GAME_FN(text_drawHangul31b, 0x401e70, void, int, int, const char *)(x, y, s)

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
