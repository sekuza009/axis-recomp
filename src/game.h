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
/* the game's ending movie player, which no rebuild replaces (the patch layer and AxisRC.exe use their own): the test
   build's only call into game code not rebuilt */
#define movie_playEnding(zero, path, width, height) GAME_CDECL(0x46c420, void, int, const char *, int, int)(zero, path, width, height)
#define glColor4f(r, g, b, a) IMPORT_FN(glColor4f, void, float, float, float, float)(r, g, b, a)
/* a colour kept in memory, passed on bit for bit (the original copies the four values without the FPU, which
   would turn a signalling NaN into a quiet one) */
#define glColor4f_stored(c) IMPORT_FN(glColor4f, void, u32, u32, u32, u32)(((const u32 *)RELOC(c))[0], ((const u32 *)RELOC(c))[1], \
	((const u32 *)(c))[2], ((const u32 *)(c))[3])
#define glEnable(cap) IMPORT_FN(glEnable, void, u32)(cap)
#define GL_FOG 0x0b60
#define GL_DEPTH_BUFFER_BIT 0x0100
#define GL_COLOR_BUFFER_BIT 0x4000
#define glClear(mask) IMPORT_FN(glClear, void, u32)(mask)
#define glClearDepth(depth) IMPORT_FN(glClearDepth, void, double)(depth)
/* a clear colour kept in memory (three floats), passed on bit for bit, alpha 1 */
#define glClearColor_stored(c) IMPORT_FN(glClearColor, void, u32, u32, u32, u32)(((const u32 *)(c))[0], ((const u32 *)(c))[1], ((const u32 *)(c))[2], 0x3f800000u)
#define glClearColor(r, g, b, a) IMPORT_FN(glClearColor, void, float, float, float, float)(r, g, b, a)
#define glClearColor_bits(r, g, b, a) IMPORT_FN(glClearColor, void, u32, u32, u32, u32)(r, g, b, a)   /* (the floats as their bits) */
#define GL_QUADS 7
#define GL_LINE_LOOP 2
#define GL_QUAD_STRIP 8
#define glBegin(mode) IMPORT_FN(glBegin, void, u32)(mode)
#define glEnd() IMPORT_FN(glEnd, void, void)()
#define glTexCoord2f(s, t) IMPORT_FN(glTexCoord2f, void, float, float)(s, t)
#define glTexCoord2d(s, t) IMPORT_FN(glTexCoord2d, void, double, double)(s, t)
#define glBindTexture(target, id) IMPORT_FN(glBindTexture, void, u32, u32)(target, id)
#define glVertex2i(x, y) IMPORT_FN(glVertex2i, void, int, int)(x, y)
#ifdef AXIS_NATIVE   /* (the native build remaps the HUD's vertices: fixes/hud.c) */
void fix_hudVertex(int x, int y);
#undef glVertex2i
#define glVertex2i(x, y) fix_hudVertex(x, y)
#endif
#define glDisable(cap) IMPORT_FN(glDisable, void, u32)(cap)
#define GL_FOG_DENSITY 0x0b62
#define GL_FOG_START 0x0b63
#define GL_FOG_END 0x0b64
#define GL_FOG_MODE 0x0b65
#define GL_FOG_COLOR 0x0b66
#define GL_FOG_HINT 0x0c54
#define GL_LINEAR 0x2601
#define GL_DONT_CARE 0x1100
#define glFogi(pname, v) IMPORT_FN(glFogi, void, u32, int)(pname, v)
#define glFogfv(pname, v) IMPORT_FN(glFogfv, void, u32, const void *)(pname, v)
/* a float kept in memory, passed on bit for bit */
#define glFogf_stored(pname, v) IMPORT_FN(glFogf, void, u32, u32)(pname, v)
#define glHint(target, mode) IMPORT_FN(glHint, void, u32, u32)(target, mode)
#define glPushMatrix() IMPORT_FN(glPushMatrix, void, void)()
#define glLoadIdentity() IMPORT_FN(glLoadIdentity, void, void)()
#define glGetFloatv(pname, out) IMPORT_FN(glGetFloatv, void, u32, float *)(pname, out)
#define glLoadMatrixf(m) IMPORT_FN(glLoadMatrixf, void, const float *)(m)
#define glVertex3fv(v) IMPORT_FN(glVertex3fv, void, const float *)(v)
/* (render/view_volume.c: drawing the queued objects; vectors and colours passed as pointers into memory) */
#define glPolygonMode(face, mode) IMPORT_FN(glPolygonMode, void, u32, u32)(face, mode)
#define glGetBooleanv(pname, out) IMPORT_FN(glGetBooleanv, void, u32, u8 *)(pname, out)
#define glEnableClientState(array) IMPORT_FN(glEnableClientState, void, u32)(array)
#define glDisableClientState(array) IMPORT_FN(glDisableClientState, void, u32)(array)
#define glVertexPointer(size, type, stride, p) IMPORT_FN(glVertexPointer, void, int, u32, int, const void *)(size, type, stride, p)
#define glColorPointer(size, type, stride, p) IMPORT_FN(glColorPointer, void, int, u32, int, const void *)(size, type, stride, p)
#define glTexCoordPointer(size, type, stride, p) IMPORT_FN(glTexCoordPointer, void, int, u32, int, const void *)(size, type, stride, p)
#define glMultMatrixf(m) IMPORT_FN(glMultMatrixf, void, const float *)(m)
#define glCullFace(mode) IMPORT_FN(glCullFace, void, u32)(mode)
#define glDrawElements(mode, count, type, indices) IMPORT_FN(glDrawElements, void, u32, int, u32, const void *)(mode, count, type, indices)
#define glPolygonOffset(factor, units) IMPORT_FN(glPolygonOffset, void, float, float)(factor, units)
#define glColor4ub(r, g, b, a) IMPORT_FN(glColor4ub, void, u8, u8, u8, u8)(r, g, b, a)
#define glColor3ub(r, g, b) IMPORT_FN(glColor3ub, void, u8, u8, u8)(r, g, b)
#define glColor4ubv(c) IMPORT_FN(glColor4ubv, void, const void *)(c)
#define glTexCoord2fv(v) IMPORT_FN(glTexCoord2fv, void, const void *)(v)
#define glVertex4fv(v) IMPORT_FN(glVertex4fv, void, const void *)(v)
#define glTexCoord2f_bits(s, t) IMPORT_FN(glTexCoord2f, void, u32, u32)(s, t)
/* a point kept in memory (three floats), passed on bit for bit */
#define glVertex3f_stored(v) IMPORT_FN(glVertex3f, void, u32, u32, u32)(((const u32 *)RELOC(v))[0], ((const u32 *)RELOC(v))[1], ((const u32 *)RELOC(v))[2])
/* colours and translations given as float bits (see BITS) */
#define glColor4f_bits(r, g, b, a) IMPORT_FN(glColor4f, void, u32, u32, u32, u32)(r, g, b, a)
#define glTranslatef_bits(x, y, z) IMPORT_FN(glTranslatef, void, u32, u32, u32)(x, y, z)
#define glScalef_bits(x, y, z) IMPORT_FN(glScalef, void, u32, u32, u32)(x, y, z)
/* GLU, through the game's jump to its import */
#define gluLookAt(ex, ey, ez, cx, cy, cz, ux, uy, uz) IMPORT_FN(gluLookAt, void, double, double, double, double, double, double, \
	double, double, double)(ex, ey, ez, cx, cy, cz, ux, uy, uz)
#define glPopMatrix() IMPORT_FN(glPopMatrix, void, void)()
/* a point kept in memory (three floats), passed on bit for bit */
#define glTranslatef_stored(v) IMPORT_FN(glTranslatef, void, u32, u32, u32)(((const u32 *)RELOC(v))[0], ((const u32 *)RELOC(v))[1], ((const u32 *)RELOC(v))[2])
#define glRotatef(angle, x, y, z) IMPORT_FN(glRotatef, void, float, float, float, float)(angle, x, y, z)

/* ---- C runtime of the game ---- */
#define sprintf(...) CRT_CALL(sprintf, int, char *, const char *, ...)(__VA_ARGS__)
#define vsprintf(out, format, args) CRT_CALL(vsprintf, int, char *, const char *, va_list)(out, format, args)

/* ---- screen ---- */
#define gfx_setProjection2D3D(mode) CALL_FN(gfx_setProjection2D3D, void, int)(mode)   /* 1: 3D, 2: the menus' 2D */
/* a vertex in the menus' 640 x 480 units (the patch DLL replaces this function: kept original) */
#define menu_vertex(x, y) CALL_FN(menu_vertex, void, int, int)(x, y)
/* the menus' 3D camera (gluLookAt) for models and the tunnel */
#define gfx_setMenuCamera() CALL_FN(gfx_setMenuCamera, void, void)()
/* glRotatef about x, then y, then z (degrees, as float bits) */
#define gfx_rotateXYZ(x, y, z) CALL_FN(gl_rotateXYZ, void, u32, u32, u32)(x, y, z)
/* the 3D background (menu_tunnel.c) */
#define g_flareTextures ((const int *)(OBJ(g_spiralTextures) + 0x14))     /* flare k's texture is g_flareTextures[-k] */
/* ---- textures ---- */
typedef void (*Cleanup)(void);   /* a fatal error's clean-up before exit(1) (g_errorCleanupHook) */
typedef struct { u32 vtable; void *banks[6]; i32 count; } TextureManager;   /* the game's TextureManager (0x83a5e0): six texture banks (the game's class Texture, one per size: TextureBank); a texture id names banks[id / 512], slot id % 512 */
#define tex_bind(manager, slot) CALL_THISFN(tex_bind, void, void *, int)(manager, slot)
#define gfx_getWidth() CALL_FN(gfx_getWidth, int, void)()
#define gfx_getHeight() CALL_FN(gfx_getHeight, int, void)()
#define gfx_fillRect(x0, y0, x1, y1) CALL_FN(gfx_fillRect, void, int, int, int, int)(x0, y0, x1, y1)

/* ---- text ---- */
#define text_setColor(r, g, b, a) CALL_FN(text_setColor, void, float, float, float, float)(r, g, b, a)
#define text_draw5(x, y, text) CALL_FN(text_draw5, void, int, int, const char *)(x, y, text)
#define text_draw8(x, y, text) CALL_FN(text_draw8, u32, int, int, const char *)(x, y, text)
#define createArena_hitTest(x, y) CALL_FN(createArena_hitTest, int, int, int)(x, y)   /* the new-arena form: the item under (x, y), -1 none */
#define arenaUpdateNotice_hitTest(x, y) CALL_FN(arenaUpdateNotice_hitTest, int, int, int)(x, y)   /* the program-updated notice (MSG 3 / 4): its button under (x, y) */
#define arena_drawMapPreview(map) CALL_FN(arena_drawMapPreview, u32, int)(map)   /* its map preview (the map passed, unused) */
#define roomSettings_hitTest(x, y) CALL_FN(roomSettings_hitTest, int, int, int)(x, y)   /* the room's settings form: the item under (x, y), -1 none */
#define room_drawMapPreview(map) CALL_FN(room_drawMapPreview, u32, int)(map)   /* the room form's map preview (the map passed, unused) */
#define setup_unbindKey(key) CALL_FN(setup_unbindKey, void, int)(key)   /* the key taken off the other bindings */
#define controls_fillPrimaryKeys() CALL_FN(controls_fillPrimaryKeys, void, void)()
#define game_setGameTypeFlags(scene, mode) CALL_THISFN(game_setGameTypeFlags, void, Stage *, int)(scene, mode)
#define sys_fatalError(log, format, value) CALL_FN(sys_fatalError, void, char *, const char *, int)(log, format, value)   /* (one value) a message, then exit */
#define netq_reset(host) CALL_FN(netq_reset, void, int)(host)
#define stage_setCockpitActor(stage, i) CALL_THISFN(stage_setCockpitActor, void, Stage *, int)(stage, i)
#define sound_setVolume(v) CALL_FN(sound_setVolume, int, int)(v)
#define music_setVolumeSetting(v) CALL_FN(music_setVolumeSetting, void, int)(v)
#define scene_resetScores(scene) CALL_THISFN(scene_resetScores, void, Scene *)(scene)
#define events_clear(scene, time) CALL_THISFN(events_clear, void, Scene *, float)(scene, time)
/* (app/main_loop.c: the replay's frame) */
#define events_age(scene, dt) CALL_THISFN(events_age, void, void *, u32)(scene, dt)
/* (app/main_loop.c: the match's frame) */
#define profile_save() CALL_FN(profile_save, u32, void)()
#define stage_deactivateActors(stage) CALL_THISFN(stage_deactivateActors, void, void *)(stage)
#define actor_checkDataLoss(stage, a) CALL_THISFN(actor_checkDataLoss, u32, void *, int)(stage, a)   /* 0: the parts' data was changed */
#define scene_saveNames(scene) CALL_THISFN(scene_saveNames, void, void *)(scene)
#define scene_restoreNames(scene) CALL_THISFN(scene_restoreNames, void, void *)(scene)
#define chat_matchCheatCode(scene, actor, text) CALL_THISFN(chat_matchCheatCode, int, void *, int, const char *)(scene, actor, text)
#define chat_applyMacro(scene, text, out) CALL_THISFN(chat_applyMacro, int, void *, const char *, char *)(scene, text, out)
#define msg_playerConnected(scene, actor) CALL_THISFN(msg_playerConnected, void, void *, int)(scene, actor)
#define msg_chatLine(scene, actor, text, team) CALL_THISFN(msg_chatLine, void, void *, int, const char *, int)(scene, actor, text, team)
#define msg_serverEndsGame(scene) CALL_THISFN(msg_serverEndsGame, void, void *)(scene)
#define msg_userEndsGame(scene) CALL_THISFN(msg_userEndsGame, void, void *)(scene)
#define msg_fragLimitReached(scene) CALL_THISFN(msg_fragLimitReached, void, void *)(scene)
#define msg_timeLimitReached(scene) CALL_THISFN(msg_timeLimitReached, void, void *)(scene)
#define msg_cheatUsed(scene, actor, cheat) CALL_THISFN(msg_cheatUsed, void, void *, int, int)(scene, actor, cheat)
#define msg_connectionLost(scene) CALL_THISFN(msg_connectionLost, void, void *)(scene)
#define msg_networkUnstable(scene) CALL_THISFN(msg_networkUnstable, void, void *)(scene)
#define msg_dataLoss(scene) CALL_THISFN(msg_dataLoss, void, void *)(scene)
#define net_clearAnnouncements(scene) CALL_THISFN(net_clearAnnouncements, void, void *)(scene)
#define net_announcePlayerConnected(scene, player, text) CALL_THISFN(net_announcePlayerConnected, void, void *, int, void *)(scene, player, text)
#define net_announcePlayerQuit(scene, player) CALL_THISFN(net_announcePlayerQuit, void, void *, int)(scene, player)
#define net_announceChatLine(scene, player, text, team) CALL_THISFN(net_announceChatLine, void, void *, int, const char *, int)(scene, player, text, team)
#define net_announceServerEnd(scene) CALL_THISFN(net_announceServerEnd, void, void *)(scene)
#define net_announceFragLimit(scene) CALL_THISFN(net_announceFragLimit, void, void *)(scene)
#define net_announceTimeLimit(scene) CALL_THISFN(net_announceTimeLimit, void, void *)(scene)
#define stage_newRound(stage) CALL_THISFN(stage_newRound, void, void *)(stage)
#define stage_setCullMargin(stage, vBits) CALL_THISFN(stage_setCullMargin, void, void *, u32)(stage, vBits)
#define stage_refillLights(stage) CALL_THISFN(stage_refillLights, void, void *)(stage)
#define playerRecord_loadFlag(scene, p) CALL_THISFN(playerRecord_loadFlag, int, void *, int)(scene, p)
#define playerRecord_set(stage, p, name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5) CALL_THISFN(playerRecord_set, void, void *, int, \
	const char *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32)(stage, p, name, v, team, head, chest, arm, leg, booster, i0, i1, i2, i3, i4, i5)
#define net_sendPlayerInfo(scene, p) CALL_THISFN(net_sendPlayerInfo, void, void *, int)(scene, p)
#define net_sendPlayerState(scene, p) CALL_THISFN(net_sendPlayerState, void, void *, int)(scene, p)
#define net_sendMatchEvent(scene) CALL_THISFN(net_sendMatchEvent, void, void *)(scene)
#define net_sendFlagPiece(scene, p) CALL_THISFN(net_sendFlagPiece, void, void *, int)(scene, p)
#define stage_advanceScenePath(stage, dtBits) CALL_THISFN(stage_advanceScenePath, void, void *, u32)(stage, dtBits)
#define escMenu_update(scene) CALL_THISFN(escMenu_update, void, void *)(scene)
#define crt_fprintf(...) CRT_CALL(fprintf, int, void *, const char *, ...)(__VA_ARGS__)
#define net_localSlot() CALL_FN(net_localSlot, int, void)()   /* the local player's slot */
#define netq_clearSkipped() CALL_FN(netq_clearSkipped, void, void)()
#define actor_setPartColor_bits(stage, p, part, h1, s1, v1, h2, s2, v2) CALL_THISFN(playerRecord_setPartColour, u32, void *, int, int, u32, u32, u32, \
	u32, u32, u32)(stage, p, part, h1, s1, v1, h2, s2, v2)   /* (the six as a float's bits) */
#define view_setFov(fovBits) CALL_FN(view_setFov, int, u32)(fovBits)   /* the view angle (0x4c4dec) set, a float's bits */
#define msg_kill(scene, victim, killer) CALL_THISFN(msg_kill, void, void *, int, int)(scene, victim, killer)
#define flag_uploadAtlas(scene) CALL_THISFN(flag_uploadAtlas, void, void *)(scene)
#define item_update(s, dt) CALL_THISFN(item_update, void, void *, u32)(s, dt)
#define stage_updateObjects(s, dt) CALL_THISFN(stage_updateObjects, void, void *, u32)(s, dt)
#define stage_advanceClocks(stage, dt) CALL_THISFN(stage_advanceClocks, void, void *, u32)(stage, dt)
#define collision_moveSphere(stage, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis) CALL_THISFN(collision_moveSphere, int, void *, float, const float *, const float *, u32, u32, float *, float *, float *, float *, u32)(stage, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis)
#define teams_setup(scene) CALL_THISFN(teams_setup, void, Scene *)(scene)
#define armcPartsPage_hitTest(x, y) CALL_FN(armcPartsPage_hitTest, int, int, int)(x, y)   /* the ARM CENTER's item under (x, y), -1 none */
#define quat_fromMatrix(q, m) CALL_THISFN(quat_fromMatrix, void, float *, const float *)(q, m)   /* a rotation matrix to a quaternion */
#define quat_toAxisAngle(out, q) CALL_THISFN(quat_toAxisAngle, void, float *, const float *)(out, q)
#define factor_addFactorBy(pool, record) CALL_THISFN(factor_addFactorBy, void, void *, void *)(pool, record)   /* a 0x2c-byte factor record added */
#define light_computeLayerLightBy(scene, layer, cols, first, r0, c0, r1, c1) CALL_THISFN(light_computeLayerLightBy, void, void *, const void *, u32, int, int, int, int, int)(scene, layer, cols, first, r0, c0, r1, c1)
#define bullet_update(scene, slot, dt_bits) CALL_THISFN(bullet_update, void, void *, int, int)(scene, slot, dt_bits)
#define particle_update(scene, slot, dt) CALL_THISFN(particle_update, void, void *, int, int)(scene, slot, dt)   /* one effect updated */
#define mapObject_frame(scene, i, dt) CALL_THISFN(mapObject_frame, void, void *, int, int)(scene, i, dt)
#define tex_findByName(manager, name) CALL_THISFN(tex_findByName, int, void *, const char *)(manager, name)   /* the item's index by name, < 0 none */
#define crt_fseek(f, offset, origin) CRT_CALL(fseek, int, void *, int, int)(f, offset, origin)
#define crt_strncpy(to, from, n) CRT_CALL(strncpy, char *, char *, const char *, int)(to, from, n)
#define Mat4_copy(d, s) CALL_FN(Mat4_copy, void, void *, const void *)(d, s)   /* a 4 x 4 matrix copied */
#define Mat4_multiply(out, a, b) CALL_FN(Mat4_multiply, void, float *, const float *, const float *)(out, a, b)
#define space_getNextFreeNodePtr(space) CALL_THISFN(space_getNextFreeNodePtr, void *, void *)(space)
#define space_insertTriangle(space, flags, v0, v1, v2, unit, part, i0, i1, i2) CALL_THISFN(space_insertTriangle, u8 *, void *, u32, u32, u32, u32, void *, u32, u32, u32, u32)(space, flags, v0, v1, v2, unit, part, i0, i1, i2)
#define scenePath_openStub(self, a0, a1) CALL_THISFN(scenePath_openStub, void, void *, void *, const void *)(self, a0, a1)   /* (an empty method) */
#define scenePath_advanceStub(self, a) CALL_THISFN(scenePath_advanceStub, int, void *, u32)(self, a)                             /* (answers 0) */
#define sound_playFile(name, volume) CALL_FN(sound_playFile, u32, const char *, int)(name, volume)
#define actor_setupFromParts(scene, a, id, controlledBy, spawn) CALL_THISFN(actor_setupFromParts, void, void *, int, u32, u32, u32)(scene, a, id, controlledBy, spawn)
#define particle_init(system, slot, desc) CALL_THISFN(particle_init, void, void *, int, u32)(system, slot, desc)
#define tex_getIdBy(manager, name, flags, h1, s1, v1, h2, s2, v2) CALL_THISFN(tex_getIdBy, int, void *, u32, u32, u32, u32, u32, u32, u32, u32)(manager, name, flags, h1, s1, v1, h2, s2, v2)
#define playerRecord_setPartColour(scene, p, part, h1, s1, v1, h2, s2, v2) CALL_THISFN(playerRecord_setPartColour, u32, void *, int, int, float, float, float, float, float, float)(scene, p, part, h1, s1, v1, h2, s2, v2)
#define actor_processFrame(scene, i, dt_bits) CALL_THISFN(actor_processFrame, void, void *, int, float)(scene, i, dt_bits)
#define script_processTriggers(scene) CALL_THISFN(script_processTriggers, void, void *)(scene)
#define bullet_init(scene, slot, id, owner, homingTarget, shot, quiet) CALL_THISFN(bullet_init, void, void *, int, u32, u32, u32, u32, u32)(scene, slot, id, owner, homingTarget, shot, quiet)
#define object_initObjectBy(scene, slot, type) CALL_THISFN(object_initObjectBy, void, void *, int, u32)(scene, slot, type)
#define sys_errorMessage(log, format, a, b) CALL_FN(sys_errorMessage, void, char *, const char *, int, int)(log, format, a, b)
#define ObjectList_load(list, shapes, skels, ns, names, nk, knames, lit, factors, tint, mem, size) CALL_THISFN(ObjectList_load, void, void *, void *, void *, u32, void *, u32, void *, u32, u32, u32, void *, u32)(list, shapes, skels, ns, names, nk, knames, lit, factors, tint, mem, size)
#define shape_getByName(cache, name, bind) CALL_THISFN(shape_getByName, u32, void *, const char *, int)(cache, name, bind)
#define sys_fatalErrorN(log, ...) CALL_FN(sys_fatalError, void, char *, const char *, ...)((char *)(log), __VA_ARGS__)   /* (a format and any values) */
#define script_processCommandBy(scene, actorIndex, trig, entry) CALL_THISFN(script_processCommandBy, void, void *, int, int, int)(scene, actorIndex, trig, entry)
#define space_resetPlanes(space) CALL_THISFN(space_resetPlanes, int, void *)(space)
#define space_resetNodes(space) CALL_THISFN(space_resetNodes, int, void *)(space)
#define space_resetUnits(space) CALL_THISFN(space_resetUnits, void, void *)(space)
#define space_resetBlocks(space) CALL_THISFN(space_resetBlocks, int, void *)(space)
#define image_tryOpen(image, path) CALL_THISFN(image_tryOpen, int, void *, const char *)(image, path)   /* a BMP opened */
#define image_copyTo(image, dst, dw, dh, depth, sx, sy, dx, dy, w, h, topDown) CALL_THISFN(image_copyTo, int, void *, void *, int, int, int, int, int, int, int, int, int, int)(image, dst, dw, dh, depth, sx, sy, dx, dy, w, h, topDown)
#define BMPRGBFile_close(self) CALL_THISFN(BMPRGBFile_close, u32, void *)(self)   /* the object's file closed */
#define map_loadWayPointInfoFrom(scene, f) CALL_THISFN(map_loadWayPointInfoFrom, void, void *, void *)(scene, f)
#define map_loadTriggerInfoFrom(scene, f) CALL_THISFN(map_loadTriggerInfoFrom, void, void *, void *)(scene, f)
#define ladder_sendRecord() CALL_FN(ladder_sendRecord, void, void)()   /* g_ladderId put into the Ladder record, which is checked and sent */
#define log_message(a, b, c, ...) CALL_FN(log_message, void, int, int, int, const char *, ...)(a, b, c, __VA_ARGS__)   /* a message to the log hook */
#define map_readCommands(self, f) CALL_THISFN(map_readCommands, u32, void *, void *)(self, f)
#define file_writeScrambled(p, size, count, f) CALL_FN(file_writeScrambled, u32, const void *, u32, u32, void *)(p, size, count, f)   /* fwrite, scrambled */
#define net_sendPacketData(size, data) CALL_FN(net_sendPacketData, u32, int, void *)(size, data)
#define glWindow_setupPixelFormat(dc) CALL_FN(glWindow_setupPixelFormat, int, void *)(dc)
#define glWindow_restoreDisplayMode() CALL_FN(glWindow_restoreDisplayMode, void, void)()
#define tex_loadImage(textures, i) CALL_THISFN(tex_loadImage, void, void *, int)(textures, i)
#define tex_applyTintMask(tex, i) CALL_THISFN(tex_applyTintMask, void, void *, int)(tex, i)
#define tex_upload(textures, id, mode) CALL_THISFN(tex_upload, void, void *, u32, int)(textures, id, mode)
#define glPixelStorei(pname, v) IMPORT_FN(glPixelStorei, void, u32, int)(pname, v)
#define glTexParameterf_bits(target, pname, bits) IMPORT_FN(glTexParameterf, void, u32, u32, u32)(target, pname, bits)   /* (the float as its bits) */
#define glTexImage2D(target, level, format, w, h, border, layout, type, data) IMPORT_FN(glTexImage2D, void, u32, int, int, int, int, int, u32, u32, const void *)(target, level, format, w, h, border, layout, type, data)
#define setupSlider_hitTest(x, y) CALL_FN(setupSlider_hitTest, int, int, int)(x, y)   /* the slider's part under the cursor */
#define actor_loadWeapon(scene, a, slot, variant) CALL_THISFN(actor_loadWeapon, void, void *, int, int, u32)(scene, a, slot, variant)
#define gluBuild2DMipmaps(target, components, w, h, format, type, data) IMPORT_FN(gluBuild2DMipmaps, int, u32, int, int, int, u32, u32, const void *)(target, components, w, h, format, type, data)
#define crt_tolower(c) CRT_CALL(tolower, int, int)(c)
#define shape_read(shape, f, mem, size) CALL_THISFN(shape_read, void, void *, void *, void *, int)(shape, f, mem, size)
#define shape_readObj(shape, f, mem, memSize) CALL_THISFN(shape_readObj, void, void *, void *, void *, int)(shape, f, mem, memSize)
#define skel_loadFromFile(self, f, mem, size) CALL_THISFN(skel_loadFromFile, void, void *, void *, void *, int)(self, f, mem, size)
#define skel_loadAseFrom(sk, f, mem, memSize) CALL_THISFN(skel_loadAseFrom, void, void *, void *, void *, int)(sk, f, mem, memSize)
#define crt_strupr(s) CRT_CALL(strupr, char *, char *)(s)
#define text_findSubstring(text, word, exact) CALL_FN(text_findSubstring, const char *, const char *, const char *, int)(text, word, exact)
#define file_existsf(format) CALL_FN(file_existsf, int, const char *)(format)
#define space_collideAt(space, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	CALL_THISFN(space_collideAt, int, void *, u32, float *, float *, u32, u32, u32, u32, u32, u32, u32, u32)(space, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define image_initBy(image, path) CALL_THISFN(image_initBy, void *, void *, const char *)(image, path)   /* a 24-bit BMP opened */
#define ShapeManager_releaseShapes(models) CALL_THISFN(ShapeManager_releaseShapes, int, void *)(models)   /* the shape cache emptied */
#define SkeletonManager_releaseSkeletons(skels) CALL_THISFN(SkeletonManager_releaseSkeletons, int, void *)(skels)   /* the skeleton cache emptied */
#define path_stripExtension(src, dst) CALL_FN(path_stripExtension, void, const char *, char *)(src, dst)
#define stage_clearMapObjects(stage) CALL_THISFN(stage_clearMapObjects, void, void *)(stage)
#define object_addObjectBy(scene, type) CALL_THISFN(object_addObjectBy, int, void *, const void *)(scene, type)
#define ObjectList_relight(list, factors, tint) CALL_THISFN(ObjectList_relight, void, void *, u32, u32)(list, factors, tint)
#define glTranslatef(x, y, z) IMPORT_FN(glTranslatef, void, float, float, float)(x, y, z)
#define app_parseCommandLine(line) CALL_FN(app_parseCommandLine, void, const char *)(line)
#define app_readLauncherCheck() CALL_FN(app_readLauncherCheck, u32, void)()
#define reg_readStartMode() CALL_FN(reg_readStartMode, u32, void)()
#define editField_readTyping() CALL_FN(editField_readTyping, void, void)()   /* a frame */
#define app_frame() CALL_FN(app_frame, void, void)()   /* the whole frame: the music, the menus' key guard, then app_frameByScreen */
#define app_init(inst, show) CALL_FN(app_init, int, void *, int)(inst, show)
#define space_testSphere(space, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	CALL_THISFN(space_testSphere, int, void *, u32, const float *, const float *, u32, u32, u32, u32, u32, u32, u32, void *, int)(space, r, pos, vel, step, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define array_recordAt(i, base, stride) CALL_FN(array_recordAt, int, int, int, int)(i, base, stride)   /* record i of an array (none when negative) */
#define collisionTri_sweepSphere(rec, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis) \
	CALL_THISFN(collisionTri_sweepSphere, int, void *, float, const float *, const float *, u32, float *, float *, float *, float *, u32)(rec, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis)
#define space_collideBlock(node, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs) \
	CALL_THISFN(space_collideBlock, int, void *, u32, const float *, const float *, u32, float *, u32, u32, u32, u32, u32, u32)(node, r, pos, vel, k, outPos, outVel, outDist, outPlane, axis, subs, nsubs)
#define collisionTri_meetsBox(item, low, high, margin) CALL_THISFN(collisionTri_meetsBox, int, void *, const float *, const float *, u32)(item, low, high, margin)   /* the item meets the box (widened) */
#define space_getNextFreeBlockPtrBy(space, low, high) CALL_THISFN(space_getNextFreeBlockPtrBy, u8 *, void *, const float *, const float *)(space, low, high)
#define space_freeNode(space, node) CALL_THISFN(space_freeNode, void, void *, void *)(space, node)   /* a node back to the free list */
#define space_freeBlock(space, node) CALL_THISFN(space_freeBlock, void, void *, void *)(space, node)   /* a block back to the free list */
#define space_insertItem(space, block, item, depth) CALL_THISFN(space_insertItem, int, void *, void *, void *, int)(space, block, item, depth)
#define angle_wrap(degrees) CALL_FN(angle_wrap, long double, float)(degrees)   /* an angle wrapped into a turn (in ST0) */
#define shape_setTextureSuffix(model, folder, flags, h1, s1, v1, h2, s2, v2) CALL_THISFN(shape_setTextureSuffix, void, void *, const char *, int, u32, u32, u32, u32, u32, u32)(model, folder, flags, h1, s1, v1, h2, s2, v2)
#define space_getNextFreePlanePtr(space) CALL_THISFN(space_getNextFreePlanePtr, u8 *, void *)(space)
#define collisionTri_setup(plane, flags, v0, v1, v2, object, part, corner0, corner1, corner2) CALL_THISFN(collisionTri_setup, void, void *, u32, const float *, const float *, const float *, u32, u32, u32, u32, u32)(plane, flags, v0, v1, v2, object, part, corner0, corner1, corner2)   /* the triangle's planes */
#define array_indexOf(record, base, stride) CALL_FN(array_indexOf, int, void *, int, int)(record, base, stride)   /* a record's index in its array */
#define stage_triggerActionNone(scene, a) CALL_THISFN(stage_triggerActionNone, void, void *, u32)(scene, a)
#define actor_applySpawnRecord(scene, a, rec) CALL_THISFN(actor_applySpawnRecord, int, void *, int, void *)(scene, a, rec)
#define script_holdActor(stage, i, mode, value) CALL_THISFN(script_holdActor, void, void *, u32, u32, u32)(stage, i, mode, value)
#define script_pushMessage(stage, speaker, text, colour, unused) CALL_THISFN(script_pushMessage, void, void *, u32, u32, u32, u32)(stage, speaker, text, colour, unused)
#define script_startScenePath(stage, name, mode) CALL_THISFN(script_startScenePath, void, void *, const char *, u32)(stage, name, mode)
#define object_setAnimation(stage, i, name, period, mode) CALL_THISFN(object_setAnimation, void, void *, u32, const char *, u32, u32)(stage, i, name, period, mode)
#define object_activate(stage, i) CALL_THISFN(object_activate, void, void *, u32)(stage, i)
#define object_deactivate(stage, i) CALL_THISFN(object_deactivate, void, void *, u32)(stage, i)
#define playerRecord_setFromMapPlayer(stage, p, rec) CALL_THISFN(playerRecord_setFromMapPlayer, void, void *, int, void *)(stage, p, rec)   /* a player set up from its map record */
#define skelDat_getItemFileBy(name) CALL_FN(skelDat_getItemFileBy, void *, const char *)(name)   /* the item's file in the skeleton dat */
#define skel_loadFrom(sk, path, mem, size) CALL_THISFN(skel_loadFrom, void, void *, const char *, void *, int)(sk, path, mem, size)
#define shapeDat_getItemFileBy(name) CALL_FN(shapeDat_getItemFileBy, void *, const char *)(name)   /* the shape's file in the shape dat */
#define shape_loadFrom(shape, path, mem, size) CALL_THISFN(shape_loadFrom, void, void *, const char *, void *, int)(shape, path, mem, size)
#define shape_bindTextureBy(shape, suffix, flags, h1, s1, v1, h2, s2, v2) CALL_THISFN(shape_bindTextureBy, void, void *, void *, u32, u32, u32, u32, u32, u32, u32)(shape, suffix, flags, h1, s1, v1, h2, s2, v2)
#define stage_resetDynamicLights(stage) CALL_THISFN(stage_resetDynamicLights, void, void *)(stage)
#define stage_clearBullets(stage) CALL_THISFN(stage_clearBullets, void, void *)(stage)
#define stage_clearParticles(stage) CALL_THISFN(stage_clearParticles, void, void *)(stage)
#define stage_resetMatrixAndPoints(stage) CALL_THISFN(stage_resetMatrixAndPoints, void, void *)(stage)
#define stage_clearMessages(scene) CALL_THISFN(stage_clearMessages, void, void *)(scene)
#define stage_initSpaceOneCell(stage) CALL_THISFN(stage_initSpaceOneCell, void, void *)(stage)
#define texRecord_init(record, name, slot, flags, h1, s1, v1, h2, s2, v2) CALL_THISFN(texRecord_init, void, void *, const char *, int, u32, u32, u32, u32, u32, u32, u32)(record, name, slot, flags, h1, s1, v1, h2, s2, v2)   /* a texture record set up */
#define tex_textureFileExist(tm, name) CALL_THISFN(tex_textureFileExist, int, void *, const char *)(tm, name)
#define match_setupOrStartRound(scene) CALL_THISFN(match_setupOrStartRound, void, void *)(scene)
#define scene_averageFrameTime(scene) CALL_THISFN(scene_averageFrameTime, long double, void *)(scene)   /* (answers in ST0) */
#define match_readInput(scene) CALL_THISFN(match_readInput, void, void *)(scene)
#define match_frame(scene) CALL_THISFN(match_frame, void, void *)(scene)
#define match_drawFrame(scene) CALL_THISFN(match_drawFrame, void, void *)(scene)
#define collision_rayTrace(scene, from, p1, hit) CALL_THISFN(collision_rayTrace, int, void *, const float *, const float *, void *)(scene, from, p1, hit)   /* 0: nothing in the way */
#define crt_ftell(f) CRT_CALL(ftell, long, void *)(f)
#define shape_computeBounds(shape) CALL_THISFN(shape_computeBounds, void, void *)(shape)
#define angle_wrap_bits(bits) CALL_FN(angle_wrap, long double, u32)(bits)   /* (the angle passed as its bits) */
#define space_buildUnit(space, id, shape, matrix) CALL_THISFN(space_buildUnit, u32, void *, int, void *, const float *)(space, id, shape, matrix)
#define space_getNextFreeUnitPtr(space) CALL_THISFN(space_getNextFreeUnitPtr, u32 *, void *)(space)
#define space_addUnitTriangle(space, flags, owner, part, i0, i1, i2, v0, v1, v2) CALL_THISFN(space_addUnitTriangle, void, void *, u32, void *, u32, u32, u32, u32, const float *, const float *, const float *)(space, flags, owner, part, i0, i1, i2, v0, v1, v2)
#define space_transformPoint(out, m, p) CALL_FN(space_transformPoint, void, float *, const float *, const float *)(out, m, p)   /* a point through a matrix */
#define space_traceBlock(block, from, to, hit, dist, subs, nsubs) CALL_THISFN(space_traceBlock, int, void *, const float *, const float *, u32, float *, u32, u32)(block, from, to, hit, dist, subs, nsubs)
#define Vec3_rotateAxis(v, axis, angle) CALL_THISFN(Vec3_rotateAxis, void, float *, int, int)(v, axis, angle)   /* about axis 0 / 1 / 2 by tenths of a degree */
#define factors_addAmbient(pool, colour) CALL_THISFN(factors_addAmbient, void, void *, const void *)(pool, colour)
#define factors_addDirectional(pool, colour, dir) CALL_THISFN(factors_addDirectional, void, void *, const void *, const void *)(pool, colour, dir)
#define space_initBy(space, planes, nodes, units, blocks, cells, mem, size) CALL_THISFN(space_initBy, void, void *, int, int, int, int, int, void *, int)(space, planes, nodes, units, blocks, cells, mem, size)
#define ShapeManager_initBy(self, dir, n, source, extra, mem, size) CALL_THISFN(ShapeManager_initBy, void, void *, const char *, int, u32, int, void *, int)(self, dir, n, source, extra, mem, size)
#define SkeletonManager_initBy(self, dir, n, source, extra, mem, size) CALL_THISFN(SkeletonManager_initBy, void, void *, const char *, int, u32, int, void *, int)(self, dir, n, source, extra, mem, size)
#define stage_resetActors(stage) CALL_THISFN(stage_resetActors, void, void *)(stage)
#define stage_reset(scene) CALL_THISFN(stage_reset, void, void *)(scene)
#define effect_initShapes(scene) CALL_THISFN(effect_initShapes, void, void *)(scene)
#define stage_setFolders(self, stageDir, mapDir, textureDir, shapeDir, skeletonDir, actorDir, bulletDir, effectDir, sceneDir) CALL_THISFN(stage_setFolders, void, void *, u32, u32, u32, u32, u32, u32, u32, u32, u32)(self, stageDir, mapDir, textureDir, shapeDir, skeletonDir, actorDir, bulletDir, effectDir, sceneDir)
#define particle_spawn(scene, desc) CALL_THISFN(particle_spawn, void, void *, const void *)(scene, desc)
/* (match/weapons.c: a bullet's frame) */
#define sound_play3D(index, pos, listener, side, range) CALL_FN(sound_play3D, void, int, const void *, const void *, const void *, u32)(index, pos, listener, side, range)
#define actor_takeDamage(scene, attacker, target, mode, damage, shotMode, weapon) CALL_THISFN(actor_takeDamage, void, void *, int, int, int, int, int, int)(scene, attacker, target, mode, damage, shotMode, weapon)
#define bullet_free(stage, b) CALL_THISFN(bullet_free, void, void *, int)(stage, b)
#define math_segmentSphere(p0, p1, dir, ctr, radius, hit, t_out) CALL_FN(math_segmentSphere, int, const float *, const float *, const float *, const float *, float, float *, float *)(p0, p1, dir, ctr, radius, hit, t_out)   /* 1: the segment meets the sphere */
#define skel_getBoneMatrix(sk, out, bone, t) CALL_THISFN(skel_getBoneMatrix, void, void *, void *, int, u32)(sk, out, bone, t)
/* (match/actor_frame.c: an actor's frame) */
#define actor_loadHead(scene, a) CALL_THISFN(actor_loadHead, void, void *, int)(scene, a)
#define actor_loadChest(scene, a) CALL_THISFN(actor_loadChest, void, void *, int)(scene, a)
#define actor_loadArms(scene, a) CALL_THISFN(actor_loadArms, void, void *, int)(scene, a)
#define actor_loadLegs(scene, a) CALL_THISFN(actor_loadLegs, void, void *, int)(scene, a)
#define actor_loadBooster(scene, a) CALL_THISFN(actor_loadBooster, void, void *, int)(scene, a)
#define actor_prevWeapon(stage, i) CALL_THISFN(actor_prevWeapon, void, void *, int)(stage, i)   /* the previous weapon */
#define actor_nextWeapon(stage, i) CALL_THISFN(actor_nextWeapon, void, void *, int)(stage, i)   /* the next weapon */
#define actor_clearInput(stage, i) CALL_THISFN(actor_clearInput, void, void *, int)(stage, i)   /* the input cleared */
#define actor_pickRandomWeapon(stage, i) CALL_THISFN(actor_pickRandomWeapon, void, void *, int)(stage, i)
#define actor_pickPathPoint(scene, p) CALL_THISFN(actor_pickPathPoint, void, void *, int)(scene, p)
#define angle_turn(from, b) CALL_FN(angle_turn, long double, u32, u32)(from, b)   /* the turn from one angle to another */
#define angle_stepTowards(from, b, t) CALL_FN(angle_stepTowards, long double, u32, u32, u32)(from, b, t)   /* an angle part way */
#define anim_setTime(anim, i, scale) CALL_THISFN(anim_setTime, void, void *, int, u32)(anim, i, scale)
#define ObjectList_poseBones(pose, base) CALL_THISFN(ObjectList_poseBones, void, void *, void *)(pose, base)
#define ObjectList_bindTextures(list) CALL_THISFN(ObjectList_bindTextures, void, void *)(list)
#define bullet_spawn(stage, slot, owner, homingTarget, shot, quiet) CALL_THISFN(bullet_spawn, int, void *, int, int, int, void *, int)(stage, slot, owner, homingTarget, shot, quiet)
#define collisionTri_traceSegment(rec, p0, p1, hit, dist) CALL_THISFN(collisionTri_traceSegment, int, void *, const float *, const float *, float *, float *)(rec, p0, p1, hit, dist)
#define ObjectList_queue(list, view, factors, tint, cull, material, extraMatrix) CALL_THISFN(ObjectList_queue, int, void *, void *, void *, u8 *, int, u32, u32)(list, view, factors, tint, cull, material, extraMatrix)
#define tex_getItemFileBy(bank, name) CALL_THISFN(tex_getItemFileBy, void *, void *, const char *)(bank, name)   /* the dat file at the item's data */
#define ptx_initTables() CALL_FN(ptx_initTables, void, void)()
#define ptx_decodeFile(path, out, fmt, width, height) CALL_FN(ptx_decodeFile, int, const char *, void *, int *, int *, int *)(path, out, fmt, width, height)
#define ptx_decode(file, out, fmt, width, height) CALL_FN(ptx_decode, int, void *, void *, int *, int *, int *)(file, out, fmt, width, height)
#define input_asyncKeyPressed(key) CALL_FN(input_asyncKeyPressed, int, int)(key)
#define net_sendGamePacket(scene, kind) CALL_THISFN(net_sendGamePacket, void, void *, int)(scene, kind)
#define net_processGamePacket(scene, from, size, pkt) CALL_THISFN(net_processGamePacket, void, void *, int, int, void *)(scene, from, size, pkt)
#define netq_poll() CALL_FN(netq_poll, void, void)()   /* the network's incoming messages gathered */
#define netq_receive(from, size, data) CALL_FN(netq_receive, int, int *, int *, void *)(from, size, data)   /* the next message: 0 none, 1 a game packet */
#define net_hasSlot() CALL_FN(net_hasSlot, int, void)()   /* the local player has its slot (g_slotTakenFlag: the host from the reset, a joining machine on message 6); packets are sent only then */
#define netq_online() CALL_FN(netq_online, int, void)()   /* (g_netOnline) */
#define netq_skippedCount() CALL_FN(netq_skippedCount, int, void)()
#define map_loadGroundInfoFrom(stage, name) CALL_THISFN(map_loadGroundInfoFrom, int, void *, const char *)(stage, name)
#define map_loadObjectInfoFrom(scene, name, mode) CALL_THISFN(map_loadObjectInfoFrom, void, void *, const char *, int)(scene, name, mode)
#define collision_initVolume(stage, size_z, size_x, size_y, margin, splitCount, depth) CALL_THISFN(collision_initVolume, void, void *, u32, u32, u32, u32, int, int)(stage, size_z, size_x, size_y, margin, splitCount, depth)
#define map_loadPlayInfoFrom(scene, name) CALL_THISFN(map_loadPlayInfoFrom, void, void *, const char *)(scene, name)
#define map_loadMissionInfoFrom(scene, name) CALL_THISFN(map_loadMissionInfoFrom, void, void *, const char *)(scene, name)
#define map_loadActorInfoFrom(scene, name) CALL_THISFN(map_loadActorInfoFrom, void, void *, const char *)(scene, name)
#define font_penDraw(x, y, font, format) CALL_FN(font_penDraw, void, int, int, int, const char *)(x, y, font, format)
#define space_traceCells(space, p0, p1, hit, subs, nsubs) CALL_THISFN(space_traceCells, u32, void *, const float *, const float *, void *, void *, int)(space, p0, p1, hit, subs, nsubs)
#define match_resetInputState(scene) CALL_THISFN(match_resetInputState, void, void *)(scene)
#define net_hostGone() CALL_FN(net_hostGone, int, void)()   /* the network says the match is over? */
#define crt_fread(p, size, count, f) CRT_CALL(fread, u32, void *, u32, u32, void *)(p, size, count, f)
#define LightFactors_read(lights, f) CALL_THISFN(LightFactors_read, void, void *, void *)(lights, f)   /* the lights read */
#define math_triangleNormal(out, p1, p0, p2) CALL_FN(math_triangleNormal, float *, float *, const float *, const float *, const float *)(out, p1, p0, p2)   /* a triangle's normal */
#define ground_computeLighting(scene, layer) CALL_THISFN(ground_computeLighting, void, void *, void *)(scene, layer)   /* a layer's light map */
#define ground_buildLayerModels(stage) CALL_THISFN(ground_buildLayerModels, void, void *)(stage)   /* the layer meshes */
#define crt_atof(s) CRT_CALL(atof, double, const char *)(s)
#define axisAngle_combine(out, a, b) CALL_FN(axisAngle_combine, float *, float *, const float *, const float *)(out, a, b)   /* two rotations combined */
#define Mat4_transpose(out, s) CALL_FN(Mat4_transpose, void, float *, const float *)(out, s)   /* copied transposed */
#define axisAngle_fromMatrix(out, m) CALL_THISFN(axisAngle_fromMatrix, u32, float *, const float *)(out, m)   /* matrix -> (angle, axis) */
#define input_asyncKeyDown(key) CALL_FN(input_asyncKeyDown, int, int)(key)
#define input_setCursorPos(x, y) CALL_FN(input_setCursorPos, void, int, int)(x, y)
#define input_getCursorPos() CALL_FN(input_getCursorPos, const int *, void)()
#define actor_setInput(stage, i, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11) CALL_THISFN(actor_setInput, void, void *, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32, u32)(stage, i, v0, v1, v2, v3, v4, v5, v6, v7, v8, v9, v10, v11)   /* the local actor's controls */
#define view_nearPlane() CALL_FN(view_nearPlane, float, void)()
#define stage_updateActorsAndTriggers(stage, dt) CALL_THISFN(stage_updateActorsAndTriggers, void, void *, u32)(stage, dt)
#define bullet_updateAll(stage, dt) CALL_THISFN(bullet_updateAll, void, void *, u32)(stage, dt)
#define stage_updateParticles(stage, dt) CALL_THISFN(stage_updateParticles, void, void *, u32)(stage, dt)
#define ViewVolume_addSegment(view, colour, p, q, flag) CALL_THISFN(ViewVolume_addSegment, void, void *, const void *, const float *, const float *, int)(view, colour, p, q, flag)   /* a line in a packed colour */
#define setupGraphic_hitTest(x, y) CALL_FN(setupGraphic_hitTest, int, int, int)(x, y)   /* the graphics page's item under (x, y), -1 none */
#define text_draw16(x, y, text) CALL_FN(text_draw16, void, int, int, const char *)(x, y, text)
#define text_draw32(x, y, text) CALL_FN(text_draw32, void, int, int, const char *)(x, y, text)
/* the box passes: text centred between x0 and x1 */
#define text_drawCentred5(x0, y, x1, text) CALL_FN(text_drawCentred5, void, int, int, int, const char *)(x0, y, x1, text)
#define text_drawCentred8(x0, y, x1, text) CALL_FN(text_drawCentred8, void, int, int, int, const char *)(x0, y, x1, text)
#define text_drawCentredLines16(x0, y, x1, text) CALL_FN(text_drawCentredLines16, u32, int, int, int, const char *)(x0, y, x1, text)
#define text_drawCentredLines32(x0, y, x1, text) CALL_FN(text_drawCentredLines32, void, int, int, int, const char *)(x0, y, x1, text)
#define text_drawCentred(x0, y, x1, text, size) CALL_FN(text_drawCentred, void, int, int, int, const char *, int)(x0, y, x1, text, size)
#define text_drawSized(x, y, text, size) CALL_FN(text_drawSized, void, int, int, const char *, int)(x, y, text, size)

/* ---- HUD ---- */
#define hud_fillRect(x0, y0, x1, y1) CALL_FN(hud_fillRect, void, int, int, int, int)(x0, y0, x1, y1)
#define hud_drawRectOutline(x0, y0, x1, y1) CALL_FN(hud_drawRectOutline, void, int, int, int, int)(x0, y0, x1, y1)   /* a rectangle's outline */
/* a team's slot in teamScores (scene_teamIdAt) and which side of the box it is on (scene_claimTeamSlot) */
#define scene_teamIdAt(scene, team) CALL_THISFN(scene_teamIdAt, int, Scene *, int)(scene, team)
#define scene_claimTeamSlot(scene, team) CALL_THISFN(scene_claimTeamSlot, int, void *, int)(scene, team)   /* the team's slot, given one if new */
#define scene_findTeam(scene, team) CALL_THISFN(scene_findTeam, int, Scene *, int)(scene, team)   /* the team's slot or -1 */
#define hud_drawGradeBadge(scene, grade, x, y) CALL_THISFN(hud_drawGradeBadge, void, Scene *, int, int, int)(scene, grade, x, y)
#define hud_drawFlag(scene, player, x, y) CALL_THISFN(hud_drawFlag, void, Scene *, int, int, int)(scene, player, x, y)
#define hud_drawIcon(scene, x, y, icon) CALL_THISFN(hud_drawIcon, void, Scene *, int, int, int)(scene, x, y, icon)

/* ---- main loop and match ---- */
#define app_frameByScreen() CALL_FN(app_frameByScreen, void, void)()
#define game_postMatch() CALL_FN(game_postMatch, void, void)()
#define music_loopIfEnded() CALL_FN(music_loopIfEnded, void, void)()
#define gfx_swapBuffers() CALL_FN(gfx_swapBuffers, void, void)()
#define match_frameByState(scene) CALL_THISFN(match_frameByState, int, Scene *)(scene)
#define game_processLoadingMode(scene) CALL_THISFN(game_processLoadingMode, int, Scene *)(scene)
#define match_playFrame(scene) CALL_THISFN(match_playFrame, int, Scene *)(scene)
#define match_mechTestFrame(scene) CALL_THISFN(match_mechTestFrame, int, Scene *)(scene)
#define replay_frame(scene) CALL_THISFN(replay_frame, int, Scene *)(scene)

/* ---- input ---- */
#define input_reacquireKeyboard() CALL_FN(input_reacquireKeyboard, void, void)()
#define input_updateMouse() CALL_FN(input_updateMouse, void, void)()
#define input_justPressed(key) CALL_FN(input_justPressed, int, int)(key)
#define app_setDataPaths() CALL_FN(app_setDataPaths, void, void)()
#define data_loadMessages() CALL_FN(data_loadMessages, void, void)()
#define input_initDikCodes() CALL_FN(input_initDikCodes, void, void)()
#define cfg_init() CALL_FN(cfg_init, void, void)()
#define app_screenSizeForMode() CALL_FN(app_screenSizeForMode, void, void)()
#define app_registerWindowClassEx(cls) CALL_FN(app_registerWindowClassEx, int, void *)(cls)   /* the class registered on old Windows */
#define app_startupLoad(instance) CALL_FN(app_startupLoad, int, void *)(instance)
#define app_reportDisplayModeError(code) CALL_FN(app_reportDisplayModeError, int, int)(code)   /* a start-up problem reported */
#define app_readCurrentDirectory() CALL_FN(app_readCurrentDirectory, u32, void)()
#define app_setDisplayMode(width, height, flags, bits) CALL_FN(app_setDisplayMode, int, int, int, u32, int)(width, height, flags, bits)   /* the display mode set (src/app/win32.c) */
#define armc_partsPageKeys() CALL_FN(armc_partsPageKeys, void, void)()   /* the arm screen's keys, page 1 */
#define armc_weaponsPageKeys() CALL_FN(armc_weaponsPageKeys, void, void)()   /* page 2 */
#define armc_colourPageKeys() CALL_FN(armc_colourPageKeys, void, void)()   /* page 3 */

/* ---- menus: the screens' frames and key handlers ---- */
#define menu_frame() CALL_FN(menu_frame, void, void)()
#define menu_processMouse() CALL_FN(menu_processMouse, void, void)()
#define menu_processKeys() CALL_FN(menu_processKeys, void, void)()
#define menu_frameBegin() CALL_FN(menu_frameBegin, void, void)()
#define menuState100_intro() CALL_FN(menuState100_intro, void, void)()
#define menuState200_title() CALL_FN(menuState200_title, void, void)()   /* the title screen (200) */
#define menuState210_frame() CALL_FN(menuState210_frame, void, void)()
#define menuState300_frame() CALL_FN(menuState300_frame, void, void)()
#define menuState400_frame() CALL_FN(menuState400_frame, void, void)()
#define menuState500_skirmish() CALL_FN(menuState500_skirmish, void, void)()
#define menuState600_setup() CALL_FN(menuState600_setup, void, void)()
#define menuState700_armCenter() CALL_FN(menuState700_armCenter, void, void)()
#define menuState800_gameRoom() CALL_FN(menuState800_gameRoom, void, void)()
#define menuState900_missions() CALL_FN(menuState900_missions, void, void)()
#define menu_drawMessageBox() CALL_FN(menu_drawMessageBox, void, void)()   /* the message box */
#define menu_drawInputLine(x, y) CALL_FN(menu_drawInputLine, void, int, int)(x, y)
#define menu_drawCursor() CALL_FN(menu_drawCursor, void, void)()
#define menu_enterState() CALL_FN(menu_enterState, void, void)()
#define menu_drawBackground() CALL_FN(menu_drawBackground, void, void)()
#define menu_drawFrameOpening(x0, y0, x1, y1) CALL_FN(menu_drawFrameOpening, u32, int, int, int, int)(x0, y0, x1, y1)
/* textured quads (menu_quads.c): buttons from the bound sheet (lit == 1: the lit cell), whole textures, panel ornaments */
#define menu_drawWideButton(x0, y0, x1, y1, lit) CALL_FN(menu_drawWideButton, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawLargeButton(x0, y0, x1, y1, lit) CALL_FN(menu_drawLargeButton, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawLeftArrow(x0, y0, x1, y1, lit) CALL_FN(menu_drawLeftArrow, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawRightArrow(x0, y0, x1, y1, lit) CALL_FN(menu_drawRightArrow, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawUpArrow(x0, y0, x1, y1, lit) CALL_FN(menu_drawUpArrow, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawDownArrow(x0, y0, x1, y1, lit) CALL_FN(menu_drawDownArrow, void, int, int, int, int, int)(x0, y0, x1, y1, lit)
#define menu_drawTexture(x0, y0, x1, y1, texture) CALL_FN(menu_drawTexture, void, int, int, int, int, int)(x0, y0, x1, y1, texture)
#define menu_drawTextureFlipped(x0, y0, x1, y1, texture) CALL_FN(menu_drawTextureFlipped, void, int, int, int, int, int)(x0, y0, x1, y1, texture)
#define menu_drawCornerOrnaments(x0, y0, x1, y1) CALL_FN(menu_drawCornerOrnaments, u32, int, int, int, int)(x0, y0, x1, y1)
#define menu_drawTopRightOrnament(x0, y0, x1) CALL_FN(menu_drawTopRightOrnament, void, int, int, int)(x0, y0, x1)
#define g_menuOrnamentTexture (g_menuFrameTextures[0])   /* the panel corner ornaments (texture id, four 128-unit quarters) */
#define messageBox_keyClose() CALL_FN(messageBox_keyClose, void, void)()
#define title_keyDismiss() CALL_FN(title_keyDismiss, void, void)()
#define profile_screenKeys() CALL_FN(profile_screenKeys, void, void)()
#define mainmenu_processKeys() CALL_FN(mainmenu_processKeys, void, void)()
#define lobby_processKeys() CALL_FN(lobby_processKeys, void, void)()
#define skirmish_keys() CALL_FN(skirmish_keys, void, void)()
#define setup_processTabKeys() CALL_FN(setup_processTabKeys, void, void)()
#define armc_processInput() CALL_FN(armc_processInput, void, void)()
#define room_keysByState() CALL_FN(room_keysByState, void, void)()
#define missions_pageKeys() CALL_FN(missions_pageKeys, void, void)()
#define freeCam_keys() CALL_FN(freeCam_keys, void, void)()
#define profileList_keys() CALL_FN(profileList_keys, void, void)()
#define profile_messageKeys() CALL_FN(profile_messageKeys, void, void)()
#define profile_deleteKeys() CALL_FN(profile_deleteKeys, void, void)()
#define profile_logOutKeys() CALL_FN(profile_logOutKeys, void, void)()
#define pilotSelect_keys() CALL_FN(pilotSelect_keys, void, void)()
#define skirmish_camera() CALL_FN(skirmish_camera, void, void)()
#define skirmish_drawTunnel() CALL_FN(skirmish_drawTunnel, void, void)()
#define skirmish_frameRoundScreen() CALL_FN(skirmish_frameRoundScreen, void, void)()
#define skirmish_frameNewPartsNotice() CALL_FN(skirmish_frameNewPartsNotice, void, void)()
#define sound_playMenu(id) CALL_FN(sound_playMenu, u32, int)(id)          /* 0 confirm / back, 2 move */
#define profile_typeNewName() CALL_FN(profile_typeNewName, u32, void)()
#define profile_quitGame() CALL_FN(profile_quitGame, void, void)()
#define profile_deleteChosen() CALL_FN(profile_deleteChosen, void, void)()
#define profile_create() CALL_FN(profile_create, void, void)()
#define deleteDialog_hitTest(x, y) CALL_FN(deleteDialog_hitTest, int, int, int)(x, y)  /* the button at (x, y): 0 left, 1 right */
#define logOutDialog_hitTest(x, y) CALL_FN(logOutDialog_hitTest, int, int, int)(x, y)
#define Color4_set(dst, r, g, b, a) CALL_FN(Color4_set, void, Colour *, float, float, float, float)(dst, r, g, b, a)
#define Color4_set_bits(dst, r, g, b, a) CALL_FN(Color4_set, void, void *, u32, u32, u32, u32)(dst, r, g, b, a)   /* (the floats as their bits) */

/* ---- the in-match 2D pass: the scene's view, its stage's overlay parts, the HUD elements ---- */
#define gfx_setMatchProjection(mode, scale) CALL_FN(gfx_setMatchProjection, void, int, float)(mode, scale)
#define gfx_setMatchProjection_bits(mode, scale) CALL_FN(gfx_setMatchProjection, void, int, u32)(mode, scale)   /* (the scale as its bits) */
#define factors_addPointLight(pool, colour, radius, pos) CALL_THISFN(factors_addPointLight, int, void *, u32, float, void *)(pool, colour, radius, pos)   /* a light of radius at pos */
#define factors_addPointLight_bits(pool, colour, strength, pos) CALL_THISFN(factors_addPointLight, int, void *, u32, u32, void *)(pool, colour, strength, pos)   /* (the strength as its bits) */
#define view_farPlane() CALL_FN(view_farPlane, float, void)()             /* view_farPlane: a float setting */
#define tex_clearSetCounters(textures) CALL_THISFN(tex_clearSetCounters, void, void *)(textures)
#define ViewVolume_clearDrawCounts(view) CALL_THISFN(ViewVolume_clearDrawCounts, void, void *)(view)
#define ViewVolume_captureMatrices(view, projection, modelview) CALL_THISFN(ViewVolume_captureMatrices, void, void *, void *, void *)(view, projection, modelview)
#define ViewVolume_reset(view) CALL_THISFN(ViewVolume_reset, void, void *)(view)
/* out = the inverse of m (4 x 4); returns 0 and leaves out untouched when m is singular */
#define Mat4_invert(out, m) CALL_FN(Mat4_invert, int, float *, const float *)(out, m)
#define Mat4_minor(m, out, row, col) CALL_FN(Mat4_minor, void, const float *, float *, int, int)(m, out, row, col)   /* the 3x3 left without row and col */
#define Mat4_determinant(m) CALL_FN(Mat4_determinant, long double, const float *)(m)
#define ViewVolume_addTriangle(vv, id, info6, info3, P, M, raw, cull) CALL_THISFN(ViewVolume_addTriangle, int, void *, int, const u32 *, const u32 *, const float *, const float *, int, int)(vv, id, info6, info3, P, M, raw, cull)
#define shape_getShadingColorBufferBy(out, first, part, factors, m) CALL_FN(shape_getShadingColorBufferBy, void, void *, int, const void *, const void *, const float *)(out, first, part, factors, m)
#define render_depthSortTriangles(e, lo, hi) CALL_FN(render_depthSortTriangles, void, u32 *, int, int)(e, lo, hi)   /* (transparent triangles) */
#define render_depthSortBillboards(e, lo, hi) CALL_FN(render_depthSortBillboards, void, u32 *, int, int)(e, lo, hi)   /* (billboards) */
/* a shape's shading colours from light factors (seen through inverse, the inverse of the shape's matrix), every part
   into its slice of out; first = 1 (0x466910) */
#define shape_shadingColours(out, first, shape, factors, inverse) CALL_FN(shape_shadingColours, void, u32 *, int, Shape *, const LightFactors *, \
	const float *)(out, first, shape, factors, inverse)
/* one RGBA tint colour set (first = 1) or added (0) on every part's colours, in its slice of out (0x466960) */
#define shape_addColour(px, mode, shape, colour) CALL_FN(shape_addColour, void, u32 *, int, Shape *, const void *)(px, mode, shape, colour)
#define stage_drawObject(stage, i, view) CALL_THISFN(stage_drawObject, void, Stage *, int, void *)(stage, i, view)   /* a map object to the view volume */
/* queue every mesh of model for drawing (see recomp.c): extra, matrix (none: the current modelview), a4, colour (4 bytes,
   or none), cull (1: skip meshes outside a clip plane),
   material (< 0: the mesh's own), a8 */
#define ViewVolume_queueModel(view, model, extra, matrix, factors, colour, cull, material, extraMatrix) CALL_THISFN(ViewVolume_queueModel, void, void *, \
	void *, u32, const float *, int, const void *, int, int, int)(view, model, extra, matrix, factors, colour, cull, material, extraMatrix)
#define ViewVolume_draw(view, mode, alpha) CALL_THISFN(ViewVolume_draw, void, void *, int, float)(view, mode, alpha)
#define sky_draw(stage, scale) CALL_THISFN(sky_draw, void, Stage *, float)(stage, scale)   /* the sky (render/sky.c) */
#define ground_buildDrawLists(stage, view, scale) CALL_THISFN(ground_buildDrawLists, void, void *, void *, float)(stage, view, scale)
/* the stage, the scene's own object (scene.fields: Stage) */
#define STAGE(scene) ((Stage *)((u8 *)RELOC(scene) + 0x1f36c8))
#define SCENE_STAGE_AT 0x1f36c8   /* where a scene's stage (its Stage object) starts */
#define SCENE_STAGE(scene) ((Stage *)((u8 *)(scene) + SCENE_STAGE_AT))   /* the same for a runtime scene pointer (no RELOC) */
#define stage_drawObjects(stage, view) CALL_THISFN(stage_drawObjects, void, Stage *, void *)(stage, view)
#define stage_drawActors(stage, view, pass) CALL_THISFN(stage_drawActors, void, Stage *, void *, int)(stage, view, pass)
/* actor i's frame of its parts (actor_loadChest / actor_loadWeapon), with the view volume and pass */
#define actor_drawIntoView(stage, a, view, draw) CALL_THISFN(actor_drawIntoView, void, Stage *, int, void *, int)(stage, a, view, draw)
#define stage_drawBullets(stage, view) CALL_THISFN(stage_drawBullets, void, void *, void *)(stage, view)
#define stage_drawParticles(stage, view) CALL_THISFN(stage_drawParticles, void, Stage *, void *)(stage, view)
/* particle i drawn (or queued) in the view volume */
/* a camera-facing quad at p into the view volume's billboard list id: corners p + a .. p + b, depth + dz, texture
   coordinates uv0 .. uv1, colour (4 bytes) */
#define ViewVolume_addBillboard(view, id, uv0, uv1, dz, colour, A, B, p, extra, flag) CALL_THISFN(ViewVolume_addBillboard, void, void *, int, const float *, \
	const float *, float, const void *, const float *, const float *, const float *, int, int)(view, id, uv0, uv1, dz, colour, A, B, p, extra, flag)
#define g_highDetail (g_graphicSettings[2])            /* the polygon detail setting (HIGH 1): 1 draws map items as models */
#define particle_draw(stage, i, view) CALL_THISFN(particle_draw, void, Stage *, int, void *)(stage, i, view)
#define stage_drawItems(stage, view) CALL_THISFN(stage_drawItems, void, void *, void *)(stage, view)
#define stage_setFog(stage, colour, start, end, density) CALL_THISFN(stage_setFog, void, Stage *, const void *, u32, u32, u32)(stage, colour, start, end, density)
#define script_notifyObject(stage, a, b, c, d) CALL_THISFN(script_notifyObject, void, void *, int, int, int, int)(stage, a, b, c, d)
/* scene_topPlayer: the match's top player: in team games the best ranked player of the leading team (the local player
   if it has none), else the first ranked */
#define scene_topPlayer(scene) CALL_THISFN(scene_topPlayer, Actor *, Scene *)(scene)
#define hud_drawDigits(x, y, scale, value, count, padded) CALL_FN(hud_drawDigits, void, int, int, float, int, int, int)(x, y, scale, value, count, padded)
#define tex_getIdByName(manager, name, flags, h1, s1, v1, h2, s2, v2) CALL_THISFN(tex_getIdByName, int, void *, const char *, int, int, int, int, int, int, int)(manager, name, flags, h1, s1, v1, h2, s2, v2)
#define vec_rotate(v, angle) CALL_THISFN(vec_rotate, void, float *, int)(v, angle)   /* turns (x, y) by angle (tenths of a degree) */
#define view_fov() CALL_FN(view_fov, float, void)()                          /* the field of view (g_viewFov, 0x4c4dec) */
#define hud_drawPressFire(scene) CALL_THISFN(hud_drawPressFire, void, Scene *)(scene)
#define hud_drawMatchCounters(scene) CALL_THISFN(hud_drawMatchCounters, void, Scene *)(scene)
#define hud_drawMatchResult(scene) CALL_THISFN(hud_drawMatchResult, void, Scene *)(scene)
#define hud_drawWatchedName(scene) CALL_THISFN(hud_drawWatchedName, void, Scene *)(scene)
#define hud_drawMessageBox(scene) CALL_THISFN(hud_drawMessageBox, void, Scene *)(scene)
#define hud_drawChatInput(scene) CALL_THISFN(hud_drawChatInput, void, Scene *)(scene)
#define hud_drawTeamScores(scene) CALL_THISFN(hud_drawTeamScores, void, Scene *)(scene)
#define shared_emptyFunction(scene) CALL_THISFN(shared_emptyFunction, void, Scene *)(scene)
#define hud_drawHelp(scene) CALL_THISFN(hud_drawHelp, void, Scene *)(scene)
#define hud_drawMenuBox(scene, x0, y0, x1, y1) CALL_THISFN(hud_drawMenuBox, void, Scene *, int, int, int, int)(scene, x0, y0, x1, y1)   /* a menu box */
#define hud_drawEscMenu(scene) CALL_THISFN(hud_drawEscMenu, void, Scene *)(scene)
#define hud_drawRecordIndicator(scene) CALL_THISFN(hud_drawRecordIndicator, void, Scene *)(scene)
#define hud_drawCentreNotice(scene) CALL_THISFN(hud_drawCentreNotice, void, Scene *)(scene)

/* ---- network ---- */
#define net_playerInUse(i) CALL_FN(net_playerInUse, int, int)(i)   /* the player table's slot i is taken */

/* ---- globals ---- */
typedef struct { float r, g, b, a; } Colour;   /* an RGBA colour, four floats (Color4_set / set_colour_bits; g_textColour, g_messageColours ..) */
#define input_releaseKeyboard() CALL_FN(input_releaseKeyboard, void, void)()
#define menu_clearInputBuffer(max) CALL_FN(menu_clearInputBuffer, void, int)(max)
#define editField_createEdit(chars) CALL_FN(editField_createEdit, void, int)(chars)   /* the hidden EDIT control typing goes to */
#define itoa(value, out, radix) CRT_CALL(itoa, char *, int, char *, int)(value, out, radix)
#define g_missionProgress (*(int *)(g_pilotSave + 0x104))   /* the furthest stage reached */
#define g_trig (g_tanTable)            /* 3600 values by tenths of a degree (the ring's focal length and radius) */
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
#define input_isDown(key) CALL_FN(input_isDown, int, int)(key)   /* the key (code) is held */
#define g_mouseClick (g_mouseClicked[0])           /* a click this frame (the left button) */
#define g_mouseHeld (g_mouseButtonsHeld[0])        /* the left button held down (0x80; input_updateMouse) */
#define KillTimer(hwnd, id) IMPORT_FN(KillTimer, int, void *, u32)(hwnd, id)
/* a rectangle in menu units in g_rectColour, filled or outlined (the patch DLL replaces it: kept original) */
#define menu_drawRect(x0, y0, x1, y1, filled) CALL_FN(menu_drawRect, u32, int, int, int, int, int)(x0, y0, x1, y1, filled)
/* the room's buttons under (x, y): the index of the button hit, or -1 */
#define updateNotice_hitTest(x, y) CALL_FN(updateNotice_hitTest, int, int, int)(x, y)
#define newIdConfirm_hitTest(x, y) CALL_FN(newIdConfirm_hitTest, int, int, int)(x, y)
#define gameListJoinBox_hitTest(x, y) CALL_FN(gameListJoinBox_hitTest, int, int, int)(x, y)
#define room_editJoinPassword() CALL_FN(room_editJoinPassword, void, void)()   /* the join password field opened */
#define app_closeWindow(code) CALL_FN(app_closeWindow, int, int)(code)   /* quit the game with exit code (app/app_quit.c) */
#define PostMessageA(hwnd, msg, w, l) IMPORT_FN(PostMessageA, int, void *, u32, u32, u32)(hwnd, msg, w, l)
#define pilotSelect_loadStats() CALL_FN(pilotSelect_loadStats, void, void)()
#define profile_drawPilotSelect() CALL_FN(profile_drawPilotSelect, void, void)()
#define dplay_leaveSession() CALL_FN(dplay_leaveSession, u32, void)()
/* two-button dialogs: the highlighted choice and its marker */
/* the profile screen's pages */
/* the skirmish screen (screen 500) */
#define g_skirmishBox ((const int *)ADDR(g_skirmishRectLeft))         /* the dialog frame: x0, y0, x1, y1 */
/* exe strings passed to the text passes (the address itself is what the callee gets) */
#define STR_COPYRIGHT ((const char *)STR(0x4b0474, "AXIS by Jamie System Development"))
#define STR_2D ((const char *)STR(0x4d03e0, "%2d"))
#define STR_VERSION ((const char *)STR(0x4b0384, "Axis v1.03"))

/* ---- DirectPlay (net/dplay_slots.c) ---- */
#define dplay_init() CALL_FN(dplay_init, int, void)()                     /* 0 when COM is up */
#define dplay_connectionAvailable(kind) CALL_FN(net_connectionAvailable, int, int)(kind)  /* net_connectionAvailable */
#define dplay_initConnection(kind, address) CALL_FN(dplay_initConnection, int, int, int)(kind, address)
#define dplay_release() CALL_FN(dplay_release, int, void)()
#define dplay_enumSessions() CALL_FN(dplay_enumSessions, int, void)()
#define dplay_hostSession(session, player, user1, maxPlayers, user2, hi, lo, data) CALL_FN(dplay_hostSession, int, int, int, int, int, int, int, int, int)\
	(session, player, user1, maxPlayers, user2, hi, lo, data)
#define dplay_joinSession(guid, player, data, gameMode) CALL_FN(dplay_joinSession, int, int, int, int, int)(guid, player, data, gameMode)
#define dplay_create() CALL_FN(dplay_create, int, void)()
#define net_resetState() CALL_FN(net_resetState, void, void)()
#define dplaySlot0_close() CALL_FN(dplaySlot0_close, int, void)()   /* close slot 0 .. 3 */
#define dplaySlot1_close() CALL_FN(dplaySlot1_close, int, void)()
#define dplaySlot2_close() CALL_FN(dplaySlot2_close, int, void)()
#define dplaySlot3_close() CALL_FN(dplaySlot3_close, int, void)()

/* ---- the stage's player records (thiscall on the stage; p: the player) ---- */
#define player_setName(stage, p, name) CALL_THISFN(player_setName, void, void *, int, const char *)(stage, p, name)
#define player_setCharacter(stage, p, v) CALL_THISFN(player_setCharacter, void, void *, int, int)(stage, p, v)   /* player_setCharacter */
#define player_setTeam(stage, p, team) CALL_THISFN(player_setTeam, void, void *, int, int)(stage, p, team)
#define actor_setActorTypeHeadInfoBy(stage, p, type) CALL_THISFN(actor_setActorTypeHeadInfoBy, int, Stage *, int, int)(stage, p, type)
#define actor_setActorTypeChestInfoBy(stage, p, type) CALL_THISFN(actor_setActorTypeChestInfoBy, int, Stage *, int, int)(stage, p, type)
#define actor_setActorTypeArmInfoBy(stage, p, type) CALL_THISFN(actor_setActorTypeArmInfoBy, int, Stage *, int, int)(stage, p, type)
#define actor_setActorTypeLegInfoBy(stage, p, type) CALL_THISFN(actor_setActorTypeLegInfoBy, int, Stage *, int, int)(stage, p, type)
#define actor_setActorTypeBoosterInfoBy(stage, p, type) CALL_THISFN(actor_setActorTypeBoosterInfoBy, int, Stage *, int, int)(stage, p, type)
#define actor_setActorTypeItemInfoBy(stage, p, slot, item) CALL_THISFN(actor_setActorTypeItemInfoBy, void, void *, int, int, int)(stage, p, slot, item)
#define playerRecord_markUsed(stage, p) CALL_THISFN(playerRecord_markUsed, void, void *, int)(stage, p)   /* playerRecord_markUsed */
/* the ARM CENTER's mech setters (menu/armc_mech.c), thiscall on the scene */
#define mech_setName(scene, name) CALL_THISFN(mech_setName, void, Scene *, const char *)(scene, name)
#define mech_setCharacter(scene, character) CALL_THISFN(mech_setCharacter, void, Scene *, int)(scene, character)
#define scene_setLocalTeam(scene, team) CALL_THISFN(scene_setLocalTeam, void, Scene *, int)(scene, team)
#define escMenu_open(scene, page, item) CALL_THISFN(escMenu_open, void, Scene *, int, int)(scene, page, item)   /* the Esc menu opened on page */
#define ladder_addMatchScores(scene) CALL_THISFN(ladder_addMatchScores, void, Scene *)(scene)
#define msg_playerChangedTeam(scene, player, team) CALL_THISFN(msg_playerChangedTeam, void, Scene *, int, int)(scene, player, team)
#define msg_playerJoinedTeam(scene, player, team) CALL_THISFN(msg_playerJoinedTeam, void, Scene *, int, int)(scene, player, team)
#define net_announceChangedTeam(scene, player, team, text) CALL_THISFN(net_announceChangedTeam, void, Scene *, int, int, const char *)(scene, player, team, text)
#define net_announceJoinedTeam(scene, player, team, text) CALL_THISFN(net_announceJoinedTeam, void, Scene *, int, int, const char *)(scene, player, team, text)
#define notice_printCentre(scene, ...) CALL_FN(notice_printCentre, int, Scene *, const char *, ...)(scene, __VA_ARGS__)   /* a HUD notice (a format and its arguments) */
#define match_openTextField(x, y, maxLength) CALL_FN(match_openTextField, void, int, int, int)(x, y, maxLength)   /* the match's text line opened */
#define match_endTyping() CALL_FN(match_endTyping, void, void)()
#define replay_closeRecording(scene) CALL_THISFN(replay_closeRecording, void, Scene *)(scene)   /* the recording stopped */
#define replay_startRecording(scene, name) CALL_THISFN(replay_startRecording, void, Scene *, const char *)(scene, name)
#define music_playMatch(stage) CALL_THISFN(music_playMatch, void, Scene *)(stage)
#define mech_setHeadIndex(scene, index) CALL_THISFN(mech_setHeadIndex, void, Scene *, int)(scene, index)
#define mech_setChestIndex(scene, index) CALL_THISFN(mech_setChestIndex, void, Scene *, int)(scene, index)
#define mech_setArmIndex(scene, index) CALL_THISFN(mech_setArmIndex, void, Scene *, int)(scene, index)
#define mech_setLegIndex(scene, index) CALL_THISFN(mech_setLegIndex, void, Scene *, int)(scene, index)
#define mech_setBoosterIndex(scene, index) CALL_THISFN(mech_setBoosterIndex, void, Scene *, int)(scene, index)
#define mech_setItem(scene, slot, item) CALL_THISFN(mech_setItem, void, Scene *, int, int)(scene, slot, item)

/* ---- the ARM CENTER (menu/armc_*.c) ---- */
#define armc_updatePartsPreview() CALL_FN(armc_updatePartsPreview, void, void)()      /* the mech preview */
#define armc_updateWeaponsPreview() CALL_FN(armc_updateWeaponsPreview, void, void)()      /* the weapons page's preview */
#define armc_drawRoomTunnel() CALL_FN(armc_drawRoomTunnel, void, void)()      /* the tunnel behind ARM CENTER opened from the game room (g_armcFrom 3) */
#define armc_drawTunnel() CALL_FN(armc_drawTunnel, void, void)()      /* the one when opened from the main menu (g_armcFrom 1) */
#define armc_cameraStep() CALL_FN(armc_cameraStep, void, void)()
#define armc_makeSession() CALL_FN(armc_makeSession, void, void)()      /* an ARM CENTER session made (menu/armc_items.c) */
#define armc_setup3DView() CALL_FN(armc_setup3DView, void, void)()      /* the 3D view set up (menu/armc_misc.c) */
#define armc_drawPanels() CALL_FN(armc_drawPanels, void, void)()
#define armc_applyExtraItemBonuses() CALL_FN(armc_applyExtraItemBonuses, void, void)()
#define armc_drawPartsPage() CALL_FN(armc_drawPartsPage, void, void)()      /* the pages' draw passes (menu/armc_misc.c) */
#define armc_drawWeaponsPage() CALL_FN(armc_drawWeaponsPage, void, void)()
#define armc_drawColourPage() CALL_FN(armc_drawColourPage, void, void)()
#define armc_drawWeightLine() CALL_FN(armc_drawWeightLine, void, void)()
#define armc_exit(confirmed) CALL_FN(armc_exit, u32, int)(confirmed)   /* leave the screen (menu/armc_misc.c) */
#define armc_showPartsPage() CALL_FN(armc_showPartsPage, void, void)()   /* to the parts page */
#define armc_showColourPage() CALL_FN(armc_showColourPage, u32, void)()   /* to the colour page */
#define armc_openWeaponsPage() CALL_FN(armc_openWeaponsPage, u32, void)()   /* to the weapons page (menu/armc_items.c) */
#define armc_seedAllColourSlot() CALL_FN(armc_seedAllColourSlot, u32, void)()   /* colour slot 5 (VIEW ALL) seeded from slot 1 (menu/armc_state.c) */
#define armc_stepPart(part, dir) CALL_FN(armc_stepPart, u32, u32, int)(part, dir)   /* the part in view stepped (menu/armc_parts.c) */
#define armc_readPartPanels() CALL_FN(armc_readPartPanels, void, void)()
#define armc_retintParts() CALL_FN(armc_retintParts, void, void)()
#define armc_applyColourSlot() CALL_FN(armc_applyColourSlot, void, void)()
#define armc_spreadAllColourSlot() CALL_FN(armc_spreadAllColourSlot, void, void)()   /* colour slot 5 (VIEW ALL) copied into slots 0 .. 4 (menu/armc_state.c) */
#define gl_rotateXYZ(x, y, z) CALL_FN(gl_rotateXYZ, void, u32, u32, u32)(x, y, z)   /* turned about x, y, z (degrees as float bits; render/gl_helpers.c) */
#define armc_drawPreview3D(scene, eye, forward, up, part, angle, w, h) \
	CALL_THISFN(armc_drawPreview3D, void, Scene *, const u32 *, const u32 *, const u32 *, int, int, int, int)(scene, eye, forward, up, part, angle, w, h)
#define armc_resetSeraphimParts() CALL_FN(armc_resetSeraphimParts, void, void)()      /* the part lists (a no-op in the patched game) */
#define armc_drawModeTabs() CALL_FN(armc_drawModeTabs, void, void)()      /* the screen's frame */
#define armc_drawPartsScreen() CALL_FN(armc_drawPartsScreen, void, void)()
#define armc_drawWeaponsScreen() CALL_FN(armc_drawWeaponsScreen, void, void)()
#define armc_drawColourEditor() CALL_FN(armc_drawColourEditor, void, void)()
/* claim actor slot a for the player and make it theirs (thiscall on the stage; spawn: slot, -, position...) */
#define stage_claimPlayerActor(stage, a, id, controlledBy, spawn) CALL_THISFN(stage_claimPlayerActor, void, Stage *, int, int, int, void *)(stage, a, id, controlledBy, spawn)

#define mech_setAll(scene, name, character, team, head, chest, arm, leg, booster, item0, item1, item2, item3, item4, item5) CALL_THISFN(mech_setAll, void, \
	Scene *, const char *, int, int, int, int, int, int, int, int, int, int, int, int, int)(scene, name, character, team, head, chest, arm, leg, \
	booster, item0, item1, item2, item3, item4, item5)
#define stage_remakePlayerActor(stage) CALL_THISFN(stage_remakePlayerActor, void, Stage *)(stage)
#define armc_giveShownActorWeapon(scene, slot) CALL_THISFN(armc_giveShownActorWeapon, void, Scene *, int)(scene, slot)   /* re-equip the preview mech */
#define armc_pickSlot(slot) CALL_FN(armc_pickSlot, void, int)(slot)
#define armc_showCursorItem() CALL_FN(armc_showCursorItem, void, void)()
#define armc_takeCursorItem() CALL_FN(armc_takeCursorItem, u32, void)()   /* the item slots given to the mech (menu/armc_items.c) */
#define armc_extraItemEquipped(i) CALL_FN(armc_extraItemEquipped, int, int)(i)   /* item list entry i is a colour part already in a slot */
#define armc_initCameraPoints() CALL_FN(armc_initCameraPoints, void, void)()
#define armcPartsPage_layout() CALL_FN(armcPartsPage_layout, void, void)()   /* the parts page's button rectangles (g_armcPartsPageRects) laid out */
#define armcWeaponsPage_layout() CALL_FN(armcWeaponsPage_layout, void, void)()
#define armcColour_layout() CALL_FN(armcColour_layout, void, void)()
#define armc_buildPartLists() CALL_FN(armc_buildPartLists, void, void)()
#define mech_loadFromProfile() CALL_FN(mech_loadFromProfile, u32, void)()   /* the saved mech read (from the profile) */
#define armc_loadSavedMech() CALL_FN(armc_loadSavedMech, void, void)()
#define armc_initCameraBox() CALL_FN(armc_initCameraBox, void, void)()
#define armc_initPanels() CALL_FN(armc_initPanels, void, void)()
#define armc_syncPartCursors() CALL_FN(armc_syncPartCursors, void, void)()
#define armc_viewedPartRecord(idx) CALL_FN(armc_viewedPartRecord, void, int)(idx)   /* the item shown on the preview */
#define armc_itemSlotRecord(slot, idx) CALL_FN(armc_itemSlotRecord, void, int, int)(slot, idx)
#define armc_loadSnapshotTexture(which) CALL_FN(armc_loadSnapshotTexture, void, int)(which)
#define armc_drawText(x, y, text) CALL_FN(armc_drawText, void, int, int, const char *)(x, y, text)
#define armc_drawTextRight(x, y, text) CALL_FN(armc_drawTextRight, void, int, int, const char *)(x, y, text)   /* right-aligned at x */
#define armc_readMechStats() CALL_FN(armc_readMechStats, void, void)()
#define actor_selectWeapon(stage, actor, slot) CALL_THISFN(actor_selectWeapon, void, Stage *, int, int)(stage, actor, slot)
#define scene_startSession(scene, client, mode) CALL_THISFN(scene_startSession, void, Scene *, int, int)(scene, client, mode)

#define armc_snapCameraToPoint0() CALL_FN(armc_snapCameraToPoint0, void, void)()
#define armc_saveSelection() CALL_FN(armc_saveSelection, void, void)()       /* keep the mech, save the progress */
#define armc_sendSelectionToNet() CALL_FN(armc_sendSelectionToNet, void, void)()
#define armc_easeCamera() CALL_FN(armc_easeCamera, void, void)()               /* the camera towards the page's target */
#define music_play(name) CALL_FN(music_play, u32, const char *)(name)

/* ---- messages ---- */
#define msg_print(scene, colour, ...) CALL_FN(msg_print, void, Scene *, int, const char *, ...)(scene, colour, __VA_ARGS__)   /* a line in the message box (printf) */
#define sound_playVolume(index, volume) CALL_FN(sound_playVolume, void, int, int)(index, volume)   /* volume 0..100 */

/* ---- the setup screen (menu/setup_keys.c) ---- */
#define menuCamera_setMove(v) CALL_FN(menuCamera_setMove, u32, int)(v)   /* g_menuCameraMove = v */
#define setup_topPageClicks() CALL_FN(setup_topPageClicks, void, void)()
#define setup_soundTabClicks() CALL_FN(setup_soundTabClicks, void, void)()
#define setup_graphicTabClicks() CALL_FN(setup_graphicTabClicks, void, void)()
#define setup_controlTabClicks() CALL_FN(setup_controlTabClicks, void, void)()
#define setupSound_hitTest(x, y) CALL_FN(setupSound_hitTest, int, int, int)(x, y)   /* the sound tab's control at (x, y) */
#define setupControl_hitTest(x, y) CALL_FN(setupControl_hitTest, int, int, int)(x, y)   /* the controls tab's control at (x, y) */
#define setup_sliderClicks() CALL_FN(setup_sliderClicks, void, void)()   /* the controls tab's slider follows the pointer */
#define setup_topPageKeys() CALL_FN(setup_topPageKeys, void, void)()
#define setup_soundTabKeys() CALL_FN(setup_soundTabKeys, void, void)()
#define setup_graphicTabKeys() CALL_FN(setup_graphicTabKeys, void, void)()
#define setup_controlTabKeys() CALL_FN(setup_controlTabKeys, void, void)()
#define setup_selectSoundTab() CALL_FN(setup_selectSoundTab, void, void)()
#define setup_selectGraphicTab() CALL_FN(setup_selectGraphicTab, void, void)()
#define setup_selectControlTab() CALL_FN(setup_selectControlTab, void, void)()
#define setup_drawTunnel() CALL_FN(setup_drawTunnel, void, void)()
#define setup_drawSoundPage() CALL_FN(setup_drawSoundPage, void, void)()
#define setup_drawGraphicPage() CALL_FN(setup_drawGraphicPage, void, void)()
#define setup_drawControlsPage() CALL_FN(setup_drawControlsPage, void, void)()
#define cfg_readPlayer(f) CALL_FN(cfg_readPlayer, void, void *)(f)          /* axis.cfg's player section read back */
#define cfg_readServer(f) CALL_FN(cfg_readServer, void, void *)(f)      /* its server section */
#define cfg_readSound(f) CALL_FN(cfg_readSound, void, void *)(f)             /* its sound section */
#define cfg_readGraphics(f) CALL_FN(cfg_readGraphics, void, void *)(f)     /* its graphics section */
#define cfg_readKeyBindings(f) CALL_FN(cfg_readKeyBindings, void, void *)(f)      /* its key bindings */
#define input_setDefaultBindings() CALL_FN(input_setDefaultBindings, void, void)()     /* the default key bindings */
#define armc_open() CALL_FN(armc_open, u32, void)()
#define dplay_join(session, guid, player, data) CALL_FN(dplay_join, int, int, u32, const char *, int)(session, guid, player, data)   /* a join: 500 joined */
#define tunnel_addRing() CALL_FN(tunnel_addRing, TunnelRing *, void)()   /* one more tunnel ring */
#define tunnel_removeLastRing(head) CALL_FN(tunnel_removeLastRing, u32, TunnelRing **)(head)   /* the last ring taken off and freed */
#define crypt_record4c(p, key) CALL_FN(crypt_record4c, int, u8 *, u8)(p, key)   /* a 0x4c-byte record decoded (xor key, key + 1, ...) */
#define cfg_writeAxisCfg() CALL_FN(cfg_writeAxisCfg, u32, void)()
#define setup_bindKey(key) CALL_FN(setup_bindKey, void, int)(key)   /* the row being bound gets key (a key, mouse button or wheel code) */
#define setup_defaultBindings() CALL_FN(setup_defaultBindings, void, void)()   /* the default key bindings */
#define music_stop() CALL_FN(music_stop, void, void)()

/* ---- devices and sound (app/devices.c, sound/sound_basic.c) ---- */
#define sound_playNext(sound) CALL_FN(sound_playNext, u32, void *)(sound)
#define sound_setNextVolume(sound, volume) CALL_FN(sound_setNextVolume, void, void *, int)(sound, volume)
#define sound_playPanned(sound, mode, value) CALL_FN(sound_playPanned, u32, void *, int, int)(sound, mode, value)   /* played with a pan (mode 1 / 2) */
#define input_releaseMouse() CALL_FN(input_releaseMouse, void, void)()   /* the mouse let go and released */
#define glFinish() IMPORT_FN(glFinish, void, void)()
#define SwapBuffers(hdc) IMPORT_FN(SwapBuffers, int, void *)(hdc)
#define CoUninitialize() IMPORT_FN(CoUninitialize, void, void)()

/* ---- front-end screens (menu/menu_states.c) ---- */
#define g_progress (*(int *)(g_pilotSave + 0x104))            /* rounds beaten (missions unlocked) */
#define menuTunnel_advance(ring) CALL_FN(menuTunnel_advance, void, void *)(ring)   /* moves the background tunnel on */
#define menu_drawBackground3D(first) CALL_FN(menu_drawBackground3D, void, void *)(first)
#define skirmish_roundChosen(round) CALL_FN(skirmish_roundChosen, u32, int)(round)
#define mainmenu_drawReplaySelect() CALL_FN(mainmenu_drawReplaySelect, void, void)()
#define replaySelect_drawNames() CALL_FN(replaySelect_drawNames, u32, void)()   /* the replay selection dialog's list */
#define mainmenu_drawMenu() CALL_FN(mainmenu_drawMenu, void, void)()
#define replaySelect_drawDialog() CALL_FN(replaySelect_drawDialog, void, void)()
#define menu_drawWhiteFade() CALL_FN(menu_drawWhiteFade, u32, void)()
#define missions_listClicks() CALL_FN(missions_listClicks, void, void)()
#define missions_briefingClicks() CALL_FN(missions_briefingClicks, void, void)()
#define missions_listKeys() CALL_FN(missions_listKeys, void, void)()
#define missions_briefingKeys() CALL_FN(missions_briefingKeys, void, void)()
#define newPartsNotice_clickClose() CALL_FN(newPartsNotice_clickClose, void, void)()
#define skirmish_clicks() CALL_FN(skirmish_clicks, void, void)()
#define skirmish_startRound() CALL_FN(skirmish_startRound, u32, void)()
#define skirmish_leave() CALL_FN(skirmish_leave, u32, void)()
#define newPartsNotice_keys() CALL_FN(newPartsNotice_keys, void, void)()
#define skirmish_roundKeys() CALL_FN(skirmish_roundKeys, void, void)()

/* ---- DirectPlay calls (net/dplay_calls.c) ---- */
#define CoCreateInstance(clsid, outer, context, iid, out) IMPORT_FN(CoCreateInstance, long, const void *, void *, u32, const void *, void **)(clsid, outer, context, iid, out)
#define dplaySlot0_enum() CALL_FN(dplaySlot0_enum, int, void)()   /* list the sessions through slot 0 .. 3 */
#define dplaySlot1_enum() CALL_FN(dplaySlot1_enum, int, void)()
#define dplaySlot2_enum() CALL_FN(dplaySlot2_enum, int, void)()
#define dplaySlot3_enum() CALL_FN(dplaySlot3_enum, int, void)()

/* ---- the game's own network code (net/net_servers.c) ---- */
#define net_ping(ip, timeout) CALL_FN(net_ping, int, u32, int)(ip, timeout)   /* ICMP echo: the round trip time, 0 when none */
#define net_inetAddr(text) CALL_FN(net_inetAddr, u32, const char *)(text)
#define net_closeThreadHandles() CALL_FN(net_closeThreadHandles, void, void)()   /* the network threads' handles closed */
#define net_pingAllServers() CALL_FN(net_pingAllServers, void, void)()   /* ping every listed server */
#define WaitForMultipleObjects(n, handles, all, ms) IMPORT_FN(WaitForMultipleObjects, u32, u32, void *const *, int, u32)(n, handles, all, ms)
#define ExitThread(code) IMPORT_FN(ExitThread, void, u32)(code)
#define GetTickCount() IMPORT_FN(GetTickCount, u32, void)()
#define data_loadCharacterProfiles() CALL_FN(data_loadCharacterProfiles, void, void)()
#define menu_drawLine(x0, y0, x1, y1) CALL_FN(menu_drawLine, void, int, int, int, int)(x0, y0, x1, y1)   /* a line in the menu colour */
#define timer_waitFrames(frames) CALL_FN(timer_waitFrames, void, double)(frames)   /* wait frames 1/60 s (app/timer.c) */
#define frontEnd_drawProgress() CALL_FN(frontEnd_drawProgress, u32, void)()   /* the loading picture at the next step (0x4dda34) */
#define tunnel_restart() CALL_FN(tunnel_restart, void, void)()
#define frontEnd_startUp() CALL_FN(frontEnd_startUp, void, void)()
#define menu_loadTextures() CALL_FN(menu_loadTextures, void, void)()
#define app_quitGame() CALL_FN(app_quitGame, void, void)()   /* quit (app/app_quit.c) */
#define net_resetConnection(kind) CALL_FN(net_resetConnection, void, int)(kind)   /* every socket closed before connecting */
#define net_send(kind, socket) CALL_FN(net_send, u32, int, int)(kind, socket)   /* a packet (0xc room, 0x14 arena...) to the lobby (100) / game server (0x65) */
#define net_connect(mode) CALL_FN(net_connect, int, int)(mode)   /* 100 the lobby, 0x65 the game server (net/network.c) */
#define net_disconnect() CALL_FN(net_disconnect, u32, void)()   /* leaving the network (net/network.c) */
#define GetModuleHandleA(name) IMPORT_FN(GetModuleHandleA, void *, const char *)(name)
#define glWindow_resize(width, height) CALL_FN(glWindow_resize, int, int, int)(width, height)   /* app/win32.c */
#define TimeSync_frameTime(timer) CALL_THISFN(TimeSync_frameTime, long double, void *)(timer)   /* seconds since its last call */
#define loading_draw_bits(scroll) CALL_FN(loading_draw, void, u32)(scroll)   /* the loading screen at scroll (float bits) */
#define replaySelect_allIn() CALL_FN(replaySelect_allIn, void, void)()   /* every replay file of the replay selection list in (FileEntry.picked) */
#define replaySelect_toggle(i) CALL_FN(replaySelect_toggle, void, int)(i)   /* replay file i of the replay selection list in or out (FileEntry.picked) */
#define replaySelect_hitTest(x, y) CALL_FN(replaySelect_hitTest, int, int, int)(x, y)   /* the replay selection control at (x, y), -1: none */
#define mapList_hitTest(x, y) CALL_FN(mapList_hitTest, int, int, int)(x, y)   /* the arena map list's control at (x, y) */
#define mapList_toggle(i) CALL_FN(mapList_toggle, void, int)(i)     /* the arena list: map i in or out */
#define mapList_stepGameType(i) CALL_FN(mapList_stepGameType, void, int)(i)     /* map i's game type stepped */
#define mapList_setDefault() CALL_FN(mapList_setDefault, u32, void)()      /* no map chosen */
#define mapList_chooseAll() CALL_FN(mapList_chooseAll, u32, void)()      /* every map chosen */
#define mapList_ok() CALL_FN(mapList_ok, u32, void)()      /* the list kept */
#define replaySelect_allOut() CALL_FN(replaySelect_allOut, void, void)()   /* and out */
#define replaySelect_ok() CALL_FN(replaySelect_ok, void, void)()   /* the replay selection dialog's OK */
#define net_addPlayerRecord(rec) CALL_FN(net_addPlayerRecord, void, void *)(rec)   /* the server's accept reply handled */
#define mission_loadBriefing(k) CALL_FN(mission_loadBriefing, u32, int)(k)   /* mission k's block read from axis.mis (load/files.c) */
#define missions_leave() CALL_FN(missions_leave, u32, void)()   /* leave the mission list (screen 900) */
#define missions_cursorUp() CALL_FN(missions_cursorUp, void, void)()   /* the mission list's cursor up */
#define missions_cursorDown() CALL_FN(missions_cursorDown, void, void)()   /* and down */
#define briefing_typeOut() CALL_FN(briefing_typeOut, void, void)()   /* the briefing typed out (menu/mission_list.c) */
#define text_setWrapX(v) CALL_FN(text_setWrapX, int, int)(v)   /* the text wrap x (g_textWrapX) */
#define text_setBottom(v) CALL_FN(text_setBottom, int, int)(v)   /* the text's bottom (g_textBottom) */
#define timer_now() CALL_FN(timer_now, long double, void)()   /* the time in ticks of the shifted performance counter, 80-bit */
#define QueryPerformanceFrequency(out) IMPORT_FN(QueryPerformanceFrequency, int, u64 *)(out)
#define scene_updateRanking(scene) CALL_THISFN(scene_updateRanking, void, void *)(scene)   /* the ranking and its "new king" message */
#define ResetEvent(event) IMPORT_FN(ResetEvent, int, void *)(event)
#define SetEvent(event) IMPORT_FN(SetEvent, int, void *)(event)

/* ---- objects, Win32, GL helpers (app/destructors.c, app/win32.c, render/gl_helpers.c) ---- */
#define ViewVolume_release(view) CALL_THISFN(ViewVolume_release, int, void *)(view)   /* the view volume's release: its owned block freed, its lists cleared (ViewVolume_clear), GL_EXT_vertex_array looked up again */
#define ViewVolume_dtor(view) CALL_THISFN(ViewVolume_dtor, int, void *)(view)
#define Console_dtor(console) CALL_THISFN(Console_dtor, void, void *)(console)
#define Stage_dtor(stage) CALL_THISFN(Stage_dtor, void, Stage *)(stage)
#define operator_delete(p) CRT_CALL(operator_delete, void, void *)(p)
#define operator_new(size) CRT_CALL(operator_new, void *, u32)(size)
#define GetCurrentDirectoryA(size, out) IMPORT_FN(GetCurrentDirectoryA, u32, u32, char *)(size, out)
#define GetActiveWindow() IMPORT_FN(GetActiveWindow, void *, void)()
#define MessageBoxA(hwnd, text, title, type) IMPORT_FN(MessageBoxA, int, void *, const char *, const char *, u32)(hwnd, text, title, type)
#define sys_messageBox(format) CALL_FN(sys_messageBox, int, const char *)(format)   /* (a format, then its arguments) */
/* the start-up loaders (app_startupLoad's) */
#define net_clearServerSettings() CALL_FN(net_clearServerSettings, void, void)()
#define reg_readServerSettings() CALL_FN(reg_readServerSettings, int, void)()
#define math_initMathFunction() CALL_FN(math_initMathFunction, int, void)()
#define reg_readLadderSettings() CALL_FN(reg_readLadderSettings, void, void)()
#define mech_setDefault() CALL_FN(mech_setDefault, void, void)()
#define data_loadMapInfo() CALL_FN(data_loadMapInfo, u32, void)()
#define data_loadSkirmishInfo() CALL_FN(data_loadSkirmishInfo, u32, void)()
#define arena_initOptionTexts() CALL_FN(arena_initOptionTexts, void, void)()
#define profile_scanSaves() CALL_FN(profile_scanSaves, void, void)()
#define font_initAsciiGrids() CALL_FN(font_initAsciiGrids, void, void)()
#define font_initHangulGrids() CALL_FN(font_initHangulGrids, void, void)()
#define timer_init() CALL_FN(timer_init, void, void)()
#define input_createDirectInput(window, instance) CALL_FN(input_createDirectInput, int, void *, void *)(window, instance)
#define app_checkFile_profeng() CALL_FN(app_checkFile_profeng, u32, void)()
#define app_checkFile_profkor() CALL_FN(app_checkFile_profkor, u32, void)()
#define app_checkFile_skirmish() CALL_FN(app_checkFile_skirmish, u32, void)()
#define app_checkFile_axisgame() CALL_FN(app_checkFile_axisgame, u32, void)()
#define app_checkFile_game() CALL_FN(app_checkFile_game, u32, void)()
#define sound_init(hwnd) CALL_FN(sound_init, int, void *)(hwnd)
#define sound_loadMenuSounds() CALL_FN(sound_loadMenuSounds, u32, void)()
#define input_initScanCharTable() CALL_FN(input_initScanCharTable, void, void)()
#define input_clearKeyTable2() CALL_FN(input_clearKeyTable2, void, void)()
#define cd_findDrive() CALL_FN(cd_findDrive, u32, void)()
#define tex_initBy(tm, dir, slots, format, w, h, linear, mipmaps) CALL_THISFN(tex_initBy, u32, void *, const char *, int, int, int, int, u32, u32)(tm, dir, slots, format, w, h, linear, mipmaps)
#define TextureManager_setBanks(manager, bank64x64, bank128x64, bank256x64, bank128x128, bank256x128, bank256x256) CALL_THISFN(TextureManager_setBanks, u32, void *, void *, void *, void *, void *, void *, void *)(manager, bank64x64, bank128x64, bank256x64, bank128x128, bank256x128, bank256x256)
#define pen_init(name) CALL_FN(pen_init, int, const char *)(name)
#define shapeDat_initBy() CALL_FN(shapeDat_initBy, u32, void)()
#define skelDat_initBy() CALL_FN(skelDat_initBy, u32, void)()
#define Console_ctor(scene) CALL_THISFN(Console_ctor, void *, void *)(scene)   /* the scene's constructor */
#define sound_initSoundTable(file, volume) CALL_FN(sound_initSoundTable, int, const char *, int)(file, volume)
#define mciSendCommandA(device, msg, flags, params) IMPORT_FN(mciSendCommandA, u32, u32, u32, u32, void *)(device, msg, flags, params)
#define glRotatef_bits(angle, x, y, z) IMPORT_FN(glRotatef, void, u32, u32, u32, u32)(angle, x, y, z)
#define arena_editJoinPassword() CALL_FN(arena_editJoinPassword, void, void)()
#define armc_freeRing(first) CALL_FN(tunnel_removeLastRing, void, void *)(first)   /* frees the last ring of the tunnel whose first is *first */
#define game_returnToArenaLobby() CALL_FN(game_returnToArenaLobby, void, void)()

/* ---- more front end (menu/menu_states.c, menu/edit_fields.c) ---- */
#define GetWindowTextLengthA(hwnd) IMPORT_FN(GetWindowTextLengthA, int, void *)(hwnd)
#define GetWindowTextA(hwnd, out, size) IMPORT_FN(GetWindowTextA, int, void *, char *, int)(hwnd, out, size)
#define game_returnToMainMenu() CALL_FN(game_returnToMainMenu, void, void)()
#define net_sendChat(text) CALL_FN(net_sendChat, int, const char *)(text)   /* a chat line sent */
#define input_resetKeys() CALL_FN(input_resetKeys, void, void)()
#define freeCam_stepLeft() CALL_FN(freeCam_stepLeft, void, void)()   /* the free camera stepped sideways (left) */
#define freeCam_stepRight() CALL_FN(freeCam_stepRight, void, void)()   /* and right */
#define net_sendMessage(message, to, size) CALL_FN(net_sendMessage, void, void *, u32, int)(message, to, size)
#define setup_camera() CALL_FN(setup_camera, void, void)()
#define setup_easePanel() CALL_FN(setup_easePanel, void, void)()
#define setup_drawMenu() CALL_FN(setup_drawMenu, void, void)()
#define setup_frameSoundPage() CALL_FN(setup_frameSoundPage, void, void)()
#define setup_frameGraphicPage() CALL_FN(setup_frameGraphicPage, void, void)()
#define setup_frameControlsPage() CALL_FN(setup_frameControlsPage, void, void)()

/* ---- DirectInput setup (app/devices.c) ---- */
#define DirectInputCreateA(instance, version, out, outer) IMPORT_FN(DirectInputCreateA, long, void *, u32, void *, void *)(instance, version, out, outer)
#define input_initKeyboard(window) CALL_FN(input_initKeyboard, int, void *)(window)
#define input_createMouse(window) CALL_FN(input_createMouse, int, void *)(window)   /* the mouse */

#define stage_setupActorSlot(scene, i, id, controlledBy, spawn) CALL_THISFN(stage_setupActorSlot, int, Stage *, int, int, int, void *)(scene, i, id, controlledBy, spawn)   /* claim actor slot a */
#define actor_setWeaponSlot(stage, actor, slot) CALL_THISFN(actor_setWeaponSlot, void, void *, int, int)(stage, actor, slot)   /* select a weapon slot */
#define ladder_checkAndSendRecord() CALL_FN(ladder_checkAndSendRecord, void, void)()

/* ---- start-up objects (app/statics.c) ---- */
#define ErrorLog_ctor(self, name, cleanupHook) CALL_THISFN(ErrorLog_ctor, void *, void *, const char *, Cleanup)(self, name, cleanupHook)   /* a named record (vtable 0x4aa2a0) */
#define atexit(f) CRT_CALL(atexit, int, void (*)(void))(f)

/* ---- small classes (app/classes.c) ---- */
#define fclose(f) CRT_CALL(fclose, u32, void *)(f)
#define arena_loadSettings(path) CALL_FN(arena_loadSettings, int, const char *)(path)   /* an arena settings file; 0 if missing */
#define str_dropLast(s) CALL_FN(str_dropLast, int, char *)(s)   /* s without its last character; its old length (app/small.c) */
#define TextureManager_clear(self) CALL_THISFN(TextureManager_clear, int, void *)(self)
#define Shape_clear(self) CALL_THISFN(Shape_clear, int, void *)(self)
#define ShapeManager_clear(self) CALL_THISFN(ShapeManager_clear, int, void *)(self)
#define SkeletonManager_clear(self) CALL_THISFN(SkeletonManager_clear, int, void *)(self)
#define CollisionVolume_clear(self) CALL_THISFN(CollisionVolume_clear, int, void *)(self)
#define TimeSync_clear(self) CALL_THISFN(TimeSync_clear, int, void *)(self)
#define Light_clearCounts(self) CALL_THISFN(Light_clearCounts, int, void *)(self)
#define TextureManager_reset(self) CALL_THISFN(TextureManager_reset, int, void *)(self)
#define ShapeManager_release(self) CALL_THISFN(ShapeManager_release, int, void *)(self)
#define SkeletonManager_release(self) CALL_THISFN(SkeletonManager_release, int, void *)(self)
#define CollisionVolume_release(self) CALL_THISFN(CollisionVolume_release, int, void *)(self)
#define Shape_release(self) CALL_THISFN(Shape_release, int, void *)(self)
#define TextureManager_dtor(self) CALL_THISFN(TextureManager_dtor, int, void *)(self)
#define Light_dtor(self) CALL_THISFN(Light_dtor, int, void *)(self)
#define CollisionVolume_dtor(self) CALL_THISFN(CollisionVolume_dtor, int, void *)(self)
#define Shape_dtor(self) CALL_THISFN(Shape_dtor, int, void *)(self)
#define ShapeManager_dtor(self) CALL_THISFN(ShapeManager_dtor, int, void *)(self)
#define SkeletonManager_dtor(self) CALL_THISFN(SkeletonManager_dtor, int, void *)(self)
#define TimeSync_dtor(self) CALL_THISFN(TimeSync_dtor, void, void *)(self)
#define Scene_dtor(self) CALL_THISFN(Scene_dtor, void, void *)(self)
#define BMPRGBFile_dtor(self) CALL_THISFN(BMPRGBFile_dtor, void, void *)(self)
#define ErrorLog_dtor(self) CALL_THISFN(ErrorLog_dtor, void, void *)(self)
#define Texture_dtor(self) CALL_THISFN(Texture_dtor, u32, void *)(self)   /* in fact Texture's destructor */

/* ---- start-up pieces called by the start-up pairs (app/statics.c) ---- */
#define BMPRGBFile_initLog() CALL_FN(BMPRGBFile_initLog, void *, void)()
#define CollisionVolume_initLog() CALL_FN(CollisionVolume_initLog, void *, void)()
#define Console_initLog() CALL_FN(Console_initLog, void *, void)()
#define Light_initLog() CALL_FN(Light_initLog, void *, void)()
#define PackedColor_initLog() CALL_FN(PackedColor_initLog, void *, void)()
#define RealColor_initLog() CALL_FN(RealColor_initLog, void *, void)()
#define Scene_initLog() CALL_FN(Scene_initLog, void *, void)()
#define ShapeManager_initLog() CALL_FN(ShapeManager_initLog, void *, void)()
#define Shape_initLog() CALL_FN(Shape_initLog, void *, void)()
#define SkeletonManager_initLog() CALL_FN(SkeletonManager_initLog, void *, void)()
#define Skeleton_initLog() CALL_FN(Skeleton_initLog, void *, void)()
#define Sound_initLog() CALL_FN(Sound_initLog, void *, void)()
#define Stage_initLog() CALL_FN(Stage_initLog, void *, void)()
#define TextureManager_ctor() CALL_FN(TextureManager_ctor, int, void)()
#define TextureManager_initLog() CALL_FN(TextureManager_initLog, void *, void)()
#define Texture_initLog() CALL_FN(Texture_initLog, void *, void)()
#define TimeSync_initLog() CALL_FN(TimeSync_initLog, void *, void)()
#define UnitPartInfo_initLog() CALL_FN(UnitPartInfo_initLog, void *, void)()
#define UnitPoseInfo_initLog() CALL_FN(UnitPoseInfo_initLog, void *, void)()
#define Unit_initLog() CALL_FN(Unit_initLog, void *, void)()
#define ViewVolume_initLog() CALL_FN(ViewVolume_initLog, void *, void)()
#define static_initTimeSync() CALL_FN(static_initTimeSync, void, void)()
#define static_initTex64x64() CALL_FN(static_initTex64x64, void, void)()
#define static_initTex128x64() CALL_FN(static_initTex128x64, void, void)()
#define static_initTex256x64() CALL_FN(static_initTex256x64, void, void)()
#define static_initTex128x128() CALL_FN(static_initTex128x128, void, void)()
#define static_initTex256x256() CALL_FN(static_initTex256x256, void, void)()
#define static_initTex256x128() CALL_FN(static_initTex256x128, void, void)()
#define static_registerTex64x64Dtor() CALL_FN(static_registerTex64x64Dtor, int, void)()
#define static_registerTex128x64Dtor() CALL_FN(static_registerTex128x64Dtor, int, void)()
#define static_registerTex256x64Dtor() CALL_FN(static_registerTex256x64Dtor, int, void)()
#define static_registerTex128x128Dtor() CALL_FN(static_registerTex128x128Dtor, int, void)()
#define static_registerTex256x128Dtor() CALL_FN(static_registerTex256x128Dtor, int, void)()
#define static_registerTex256x256Dtor() CALL_FN(static_registerTex256x256Dtor, int, void)()
#define static_registerTextureManagerDtor() CALL_FN(static_registerTextureManagerDtor, int, void)()
#define static_registerTextureLogDtor() CALL_FN(static_registerTextureLogDtor, int, void)()
#define static_registerTextureManagerLogDtor() CALL_FN(static_registerTextureManagerLogDtor, int, void)()
#define static_registerSoundLogDtor() CALL_FN(static_registerSoundLogDtor, int, void)()
#define static_registerConsoleLogDtor() CALL_FN(static_registerConsoleLogDtor, int, void)()
#define static_registerShapeLogDtor() CALL_FN(static_registerShapeLogDtor, int, void)()
#define static_registerShapeManagerLogDtor() CALL_FN(static_registerShapeManagerLogDtor, int, void)()
#define static_registerTimeSyncDtor() CALL_FN(static_registerTimeSyncDtor, int, void)()
#define static_registerSkeletonLogDtor() CALL_FN(static_registerSkeletonLogDtor, int, void)()
#define static_registerSkeletonManagerLogDtor() CALL_FN(static_registerSkeletonManagerLogDtor, int, void)()
#define static_registerBMPRGBFileLogDtor() CALL_FN(static_registerBMPRGBFileLogDtor, int, void)()
#define static_registerRealColorLogDtor() CALL_FN(static_registerRealColorLogDtor, int, void)()
#define static_registerPackedColorLogDtor() CALL_FN(static_registerPackedColorLogDtor, int, void)()
#define static_registerUnitPartInfoLogDtor() CALL_FN(static_registerUnitPartInfoLogDtor, int, void)()
#define static_registerUnitPoseInfoLogDtor() CALL_FN(static_registerUnitPoseInfoLogDtor, int, void)()
#define static_registerUnitLogDtor() CALL_FN(static_registerUnitLogDtor, int, void)()
#define static_registerStageLogDtor() CALL_FN(static_registerStageLogDtor, int, void)()
#define static_registerCollisionVolumeLogDtor() CALL_FN(static_registerCollisionVolumeLogDtor, int, void)()
#define static_registerLightLogDtor() CALL_FN(static_registerLightLogDtor, int, void)()
#define static_registerViewVolumeLogDtor() CALL_FN(static_registerViewVolumeLogDtor, int, void)()
#define static_registerTimeSyncLogDtor() CALL_FN(static_registerTimeSyncLogDtor, int, void)()
#define static_registerSceneLogDtor() CALL_FN(static_registerSceneLogDtor, int, void)()

/* ---- small pieces (app/small.c) ---- */
#define set_colour_bits(c, r, g, b, a) CALL_FN(Color4_set, void, Colour *, u32, u32, u32, u32)(c, r, g, b, a)   /* Color4_set with float bits */
#define rect_set(a, b, c, d, out) CALL_FN(rect_set, void, int, int, int, int, int *)(a, b, c, d, out)
#define tunnel_appendRing(head) CALL_FN(tunnel_appendRing, u32, void *)(head)   /* a ring added to the background tunnel */
#define playerRecord_resetFlag(stage, p) CALL_THISFN(playerRecord_resetFlag, void, Stage *, int)(stage, p)   /* player p's colour grid cleared */
#define actor_deactivate(stage, i) CALL_THISFN(actor_deactivate, void, void *, int)(stage, i)
#define Skeleton_clear(self) CALL_THISFN(Skeleton_clear, void, void *)(self)
#define ObjectList_clear(self) CALL_THISFN(ObjectList_clear, void, void *)(self)
#define ObjectList_release(self) CALL_THISFN(ObjectList_release, int, void *)(self)
#define str_length(s) CALL_FN(str_length, int, const char *)(s)

/* ---- batch: front-end records, objects, video tables ---- */
#define net_claimPlayerSlot() CALL_FN(net_claimPlayerSlot, u8, void)()   /* a free network player slot claimed (0xff: none) */
#define net_takePlayerSlot(slot, id) CALL_FN(net_takePlayerSlot, void, u32, int)(slot, id)   /* player slot taken by id */
#define space_disableUnit(unit) CALL_THISFN(space_disableUnit, void, void *)(unit)
#define space_enableUnit(unit) CALL_THISFN(space_enableUnit, void, void *)(unit)
#define tex_markMaterialChanged(self, m) CALL_THISFN(tex_markMaterialChanged, void, void *, int)(self, m)   /* material m marked changed */
#define profile_resetStatBars() CALL_FN(profile_resetStatBars, u32, void)()
#define ptx_initClampTable() CALL_FN(ptx_initClampTable, void, void)()
#define ptx_initYCbCrTables() CALL_FN(ptx_initYCbCrTables, void, void)()
#define ptx_initFdctDivisors(q) CALL_FN(ptx_initFdctDivisors, void, int)(q)
#define ptx_initColourTables() CALL_FN(ptx_initColourTables, void, void)()
#define ptx_initDequantTables(q) CALL_FN(ptx_initDequantTables, void, int)(q)
#define ptx_error(...) ((int (CDECL *)(int, const char *, ...))FN(ptx_error))(__VA_ARGS__)   /* app/ptx_decode.c */
#define ptx_crtlError(...) ((int (CDECL *)(int, const char *, ...))FN(ptx_crtlError))(__VA_ARGS__)
#define ptx_startBitReader(data) CALL_FN(ptx_startBitReader, void, const u8 *)(data)   /* the bit reader started at data */
#define ptx_readBlock(block) CALL_FN(ptx_readBlock, int, int *)(block)   /* one block's coefficients; the bit position */
#define ptx_inverseDct(in, out) CALL_FN(ptx_inverseDct, void, const int *, u8 *)(in, out)
#define ptx_toRgb(y, dst, n) CALL_FN(ptx_toRgb, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_toRgba(y, dst, n) CALL_FN(ptx_toRgba, void, const u8 *, u8 *, unsigned)(y, dst, n)
#define ptx_layoutBlocks(src, dst, w, h, bpp) CALL_FN(ptx_layoutBlocks, void, const u8 *, u8 *, int, int, int)(src, dst, w, h, bpp)

#define newIdConfirm_layout() CALL_FN(newIdConfirm_layout, void, void)()
#define newIdForm_layout() CALL_FN(newIdForm_layout, void, void)()
#define tex_setMaterialTint(bank, m, h1, s1, v1, h2, s2, v2) CALL_THISFN(tex_setMaterialTint, void, void *, int, u32, u32, u32, u32, u32, u32)(bank, m, h1, s1, v1, h2, s2, v2)
#define part_addColour(px, mode, img, colour) CALL_FN(part_addColour, void, u8 *, int, const u32 *, const u8 *)(px, mode, img, colour)   /* a colour added to a part's RGBA pixels */
#define spaceSlot_clear(slot) CALL_THISFN(spaceSlot_clear, void, int *)(slot)
#define shape_markMaterialsChanged(shape) CALL_THISFN(shape_markMaterialsChanged, void, void *)(shape)
#define shape_setMaterialTints(shape, h1, s1, v1, h2, s2, v2) CALL_THISFN(shape_setMaterialTints, void, void *, u32, u32, u32, u32, u32, u32)(shape, h1, s1, v1, h2, s2, v2)

#define crt_free(p) CRT_CALL(free, u32, void *)(p)
#define crt_fopen(name, mode) CRT_CALL(fopen, void *, const char *, const char *)(name, mode)
#define crt_fwrite(p, size, count, f) CRT_CALL(fwrite, u32, const void *, u32, u32, void *)(p, size, count, f)
#define crt_rand() CRT_CALL(rand, int, void)()
#define save_cryptRecord(rec, key) CALL_FN(save_cryptRecord, void, u8 *, u8)(rec, key)
#define crypt_record104(rec, key) CALL_FN(crypt_record104, void, u8 *, u8)(rec, key)   /* a 0x104-byte record (un)scrambled */
#define profile_writeCleared(count) CALL_FN(profile_writeCleared, u32, int)(count)
#define profile_readHeader() CALL_FN(profile_readHeader, u32, void)()   /* a 0x3ac-byte profile record scrambled (menu/profile_misc.c) */
#define mech_storeToProfile() CALL_FN(mech_storeToProfile, void, void)()   /* the current profile's record gathered (0x9f1718) */
#define crypt_record80(p, key) CALL_FN(crypt_record80, void, u8 *, u8)(p, key)   /* a 0x80-byte record unscrambled */
#define fread_scrambled(p, size, count, f) CALL_FN(file_readScrambled, u32, void *, u32, u32, void *)(p, size, count, f)   /* fread, each byte unscrambled (xor 0x59, then rotated left by 1) */
#define bullet_drawTrail(stage, b, view) CALL_THISFN(bullet_drawTrail, void, Stage *, int, void *)(stage, b, view)   /* bullet i's trail drawn */
#define scenePath_notifyStub(self, a0, a1, a2, a3) CALL_THISFN(scenePath_notifyStub, void, void *, int, int, int, int)(self, a0, a1, a2, a3)
#define mem_free(p) CALL_FN(mem_free, u32, void *)(p)   /* p deleted (0 for none) */

#define g_menuState g_screen   /* the front end's screen (300 the main menu) */
#define sessionList_sort() CALL_FN(sessionList_sort, void, void)()   /* the session list sorted */

/* ---- the projection switch and the menus' 2D (menu_2d.c) ---- */
#define GL_LINES 1
#define GL_DEPTH_TEST 0x0b71
#define GL_MODELVIEW 0x1700
#define GL_PROJECTION 0x1701
#define glViewport(x, y, w, h) IMPORT_FN(glViewport, void, int, int, int, int)(x, y, w, h)
#ifdef AXIS_NATIVE   /* (the native build keeps the viewport: fixes/screen.c) */
void fix_glViewport(int x, int y, int w, int h);
#undef glViewport
#define glViewport(x, y, w, h) fix_glViewport(x, y, w, h)
#endif
#define glMatrixMode(mode) IMPORT_FN(glMatrixMode, void, u32)(mode)
#define gluPerspective(angle, aspect, zNear, zFar) ((void (STDCALL *)(double, double, double, double))*(const u32 *)STR(0x4a9048, "j\300\n"))(angle, aspect, zNear, zFar)
#define gluOrtho2D(left, right, bottom, top) ((void (STDCALL *)(double, double, double, double))*(const u32 *)STR(0x4a9050, "|\300\n"))(left, right, bottom, top)

/* ---- small methods and resets (app/small.c, app/classes.c, match/actor_slots.c, collision/collision_space.c, render/rotations.c) ---- */
#define path_normalize(path) CALL_FN(path_normalize, char *, char *)(path)   /* upper-cased in place, '/' -> '\' */
#define stage_setName(self, folder) CALL_THISFN(stage_setName, char *, void *, const char *)(self, folder)
#define TimeSync_ctor(self) CALL_THISFN(TimeSync_ctor, void *, void *)(self)
#define Skeleton_release(self) CALL_THISFN(Skeleton_release, int, void *)(self)   /* a skeleton released */
#define stage_clearFrags(stage) CALL_THISFN(stage_clearFrags, void, Stage *)(stage)
#define stage_resetPlayerRecords(stage) CALL_THISFN(stage_resetPlayerRecords, void, Stage *)(stage)   /* the 16 player records reset */
#define stage_clearActorSlots(stage) CALL_THISFN(stage_clearActorSlots, void, Stage *)(stage)
#define actor_resetSlot(stage, i) CALL_THISFN(actor_resetSlot, void, void *, int)(stage, i)
#define collisionPlane_clear(self) CALL_THISFN(collisionPlane_clear, int, void *)(self)   /* a collision plane cleared */
#define spaceNode_clear(self) CALL_THISFN(spaceNode_clear, int, void *)(self)   /* a node */
#define spaceBlock_clear(self) CALL_THISFN(spaceBlock_clear, int, void *)(self)   /* a block */
#define quat_fromAxisAngle(q, rotation) CALL_THISFN(quat_fromAxisAngle, void, float *, const float *)(q, rotation)
#define Mat4_fromQuat(m, q) CALL_FN(Mat4_fromQuat, void, float *, const float *)(m, q)   /* quaternion -> matrix */

/* ---- (render/shape_colours.c, app/small.c, menu/menu_misc.c callers) ---- */
#define shape_setTint(model, h1, s1, v1, h2, s2, v2) CALL_THISFN(shape_setTint, void, void *, u32, u32, u32, u32, u32, u32)(model, h1, s1, v1, h2, s2, v2)
#define shape_clearTint(model) CALL_THISFN(shape_clearTint, void, void *)(model)   /* the model's shapes' own colours back */
#define script_reset(stage) CALL_THISFN(script_reset, int, Stage *)(stage)
#define briefing_hitTest(x, y) CALL_FN(briefing_hitTest, int, int, int)(x, y)   /* which button of the mission screen's (900) briefing is at (x, y) */
#define briefing_nextPage() CALL_FN(briefing_nextPage, u32, void)()   /* the briefing's next page */
#define briefing_prevPage() CALL_FN(briefing_prevPage, u32, void)()   /* the briefing's page before */

/* ---- the lobby's and room's screens (menu/lobby_states.c) ---- */
#define arena_loadPlayerSettings() CALL_FN(arena_loadPlayerSettings, void, void)()   /* the player's record from the profile */
#define mapList_layout() CALL_FN(mapList_layout, void, void)()   /* the map list laid out */
#define lobby_loadArenaSettings() CALL_FN(lobby_loadArenaSettings, void, void)()
#define mapList_init() CALL_FN(mapList_init, void, void)()   /* the map on/off list reset */
#define room_loadSettingsRecord() CALL_FN(room_loadSettingsRecord, void, void)()   /* the room settings copied */

/* ---- the PTX video decoder (app/ptx_decode.c) ---- */
#define ptx_readBits(out, n) CALL_FN(ptx_readBits, int, int *, int)(out, n)   /* the next n bits of the stream */
#define ptx_readDcDiff(out) CALL_FN(ptx_readDcDiff, void, int *)(out)   /* a DC difference */
#define ptx_readAcSymbol(out, run) CALL_FN(ptx_readAcSymbol, void, int *, int *)(out, run)   /* an AC symbol */

/* ---- (net/net_sessions.c, render/rotations.c) ---- */
#define sessionList_swap(a, b) CALL_FN(sessionList_swap, void, SessionEntry *, SessionEntry *)(a, b)   /* two session records swapped */
#define Vec3_normalize(v) CALL_THISFN(Vec3_normalize, long double, float *)(v)   /* returns the length, unrounded */

/* ---- (load/lists.c, render/shape_colours.c, net/network.c, match/map_objects.c, menu/lobby_states.c) ---- */
#define crt_malloc(size) CRT_CALL(malloc, void *, u32)(size)
#define net_clearServers() CALL_FN(net_clearServers, void, void)()                  /* the server table cleared */
#define net_resolveHost(host) CALL_FN(net_resolveHost, int, const char *)(host)   /* 1: resolved (into 0xa0d320) */
#define net_freeBuffers() CALL_FN(net_freeBuffers, u32, void)()
#define net_clearServerList() CALL_FN(net_clearServerList, void, void)()   /* the lobby's arena (server) list cleared (g_serverList: ArenaRecord, request 13) */
#define net_receiveLobbyReply() CALL_FN(net_receiveLobbyReply, void, void)()   /* the list of games received */
#define net_receiveGameServerReply() CALL_FN(net_receiveGameServerReply, void, void)()   /* a game server reply: a room for the room list, its end, or a refusal */
#define net_receivePlayerListReply() CALL_FN(net_receivePlayerListReply, void, void)()   /* the player list received */
#define net_clearRoomList() CALL_FN(net_clearRoomList, void, void)()   /* the game server's room list cleared (g_roomList: RoomRecord, request 19) */
#define net_clearPlayerList() CALL_FN(net_clearPlayerList, void, void)()   /* the player list cleared */
#define jmp_net_getLocalAddress() CALL_FN(jmp_net_getLocalAddress, int, void)()   /* this machine's address (0xa0b43c) */
#define crt_strtok(s, delimiters) CRT_CALL(strtok, char *, char *, const char *)(s, delimiters)   /* the game's CRT strtok */
#define crt_atoi(s) CRT_CALL(atoi, int, const char *)(s)
#define tunnelRing_build(node, index) CALL_FN(tunnelRing_build, u32, void *, int)(node, index)
#define tex_tintHsv(rgb, dh, ds, dv) CALL_THISFN(tex_tintHsv, void, float *, u32, u32, u32)(rgb, dh, ds, dv)
#define skel_getSkeletonPtrBy(cache, name) CALL_THISFN(skel_getSkeletonPtrBy, void *, void *, u32)(cache, name)
#define mech_unpackFromRecord() CALL_FN(mech_unpackFromRecord, void, void)()   /* the mech unpacked */

/* ---- (render/tex_colours.c) ---- */
#define color_rgbToHsv(r, g, b, h, s, v) CALL_FN(color_rgbToHsv, void, u32, u32, u32, float *, float *, float *)(r, g, b, h, s, v)   /* RGB -> HSV (r, g, b as float bits) */
#define color_hsvToRgb(hue, sat, val, r, g, b) CALL_FN(color_hsvToRgb, void, u32, u32, u32, float *, float *, float *)(hue, sat, val, r, g, b)   /* (h, s, v as float bits) */
#define tex_tintRgba(rgba, dh, ds, dv) CALL_THISFN(tex_tintRgba, int, u8 *, u32, u32, u32)(rgba, dh, ds, dv)   /* an RGBA byte colour tinted */

/* ---- (net/net_sessions.c) ---- */
#define net_sessionCount() CALL_FN(net_sessionCount, int, void)()   /* the session list's count */
#define net_getSession(i) CALL_FN(net_getSession, int, int)(i)   /* session i's record */

#define room_copyAccountRecord() CALL_FN(room_copyAccountRecord, void, void)()   /* the joined game's settings into the room screen */
#define login_takeAccountRecord() CALL_FN(login_takeAccountRecord, void, void)()   /* the login's account record (g_profileReply) taken: ID, e-mail, mech, colours, pilot stats, the Ladder record */
#define roomLogin_editId() CALL_FN(roomLogin_editId, u32, void)()   /* the Ladder login's ID opened for typing */
#define roomLogin_editPassword() CALL_FN(roomLogin_editPassword, u32, void)()   /* the Ladder login's password opened for typing */
#define roomLogin_endTyping() CALL_FN(roomLogin_endTyping, void, void)()   /* the Ladder login's hidden EDIT control closed, its line taken into the ID or password */
#define login_send() CALL_FN(login_send, void, void)()   /* the login sent */
#define newIdForm_openField(k) CALL_FN(newIdForm_openField, int, int)(k)   /* the new-ID form's field k opened for typing */
#define room_drawTunnel() CALL_FN(room_drawTunnel, void, void)()   /* the game room's tunnel */
#define room_mergeReceivedSessions() CALL_FN(room_mergeReceivedSessions, void, void)()   /* the pinged rooms' new games (g_roomList) merged into g_sessionList */
#define gameList_draw() CALL_FN(gameList_draw, void, void)()   /* the game room's list of games drawn */
#define room_joinListed(i) CALL_FN(room_joinListed, u32, int)(i)   /* game i of the list joined */
#define gameList_hitTest(x, y) CALL_FN(gameList_hitTest, int, int, int)(x, y)   /* the game list's control at (x, y) */
#define room_askJoinPassword() CALL_FN(room_askJoinPassword, void, void)()   /* a locked game's join password asked for (the join is room_joinListed) */
#define gameList_refresh() CALL_FN(gameList_refresh, int, void)()    /* the search asked for: 1 sent */
#define roomLogin_hitTest(x, y) CALL_FN(roomLogin_hitTest, int, int, int)(x, y)   /* the Ladder login dialog's button at (x, y) */
#define room_openNewIdForm() CALL_FN(room_openNewIdForm, u32, void)()
#define dplay_host(session, player, user1, maxPlayers, user2, hi, lo, data) CALL_FN(dplay_host, int, const void *, const char *, int, int, int, int, int, int)(session, player, user1, maxPlayers, user2, hi, lo, data)   /* the arena hosted: 0 failed */
#define net_asyncSelect(wnd, which) CALL_FN(net_asyncSelect, int, void *, int)(wnd, which)
#define lobby_keepArenaSettings() CALL_FN(lobby_keepArenaSettings, u32, void)()   /* the arena's settings kept (0x4db528 into 0x4ded20) */
#define room_keepSettings() CALL_FN(room_keepSettings, u32, void)()    /* the room's settings kept (0x4df9c8 into 0x5b1b30) */
#define arena_drawTunnel() CALL_FN(arena_drawTunnel, void, void)()   /* the arena's tunnel */
#define dplay_listSessions() CALL_FN(dplay_listSessions, u32, void)()   /* DirectPlay's session list polled */
#define arenaList_rebuild() CALL_FN(arenaList_rebuild, void, void)()
#define arena_mergeReceivedSessions() CALL_FN(arena_mergeReceivedSessions, void, void)()   /* the pinged arena servers' new games (g_serverList) merged into g_sessionList */
#define arena_drawGameList() CALL_FN(arena_drawGameList, void, void)()   /* the arena's list of games drawn */
#define arena_joinListed(i) CALL_FN(arena_joinListed, u32, int)(i)   /* game i joined (99999: the one typed) */
#define arena_joinSession(session) CALL_FN(arena_joinSession, u32, int)(session)   /* session i joined */
#define sys_checkClockTampering() CALL_FN(sys_checkClockTampering, void, void)()
#define glWindow_init(title, width, height, colourBits, depthBits, fullscreen, window, dc) CALL_FN(glWindow_init, void, const char *, int, int, int, int, int, void *, int)(title, width, height, colourBits, depthBits, fullscreen, window, dc)
#define map_fileExists(map) CALL_FN(map_fileExists, int, int)(map)   /* the map's files loaded: 0 failed */
#define pilotRecord_syncCopies() CALL_FN(pilotRecord_syncCopies, void, void)()
#define scene_setMapName(scene, folder) CALL_THISFN(scene_setMapName, void, Scene *, const char *)(scene, folder)
#define level_fromPoints(points) CALL_FN(level_fromPoints, int, int)(points)   /* the level (1 ..) the points reach */
#define net_receiveAll() CALL_FN(net_receiveAll, u32, void)()
#define net_getLocalAddress() CALL_FN(net_getLocalAddress, int, void)()   /* this machine's address as text (0xa0b43c) */
#define skirmish_drawRoundScreen() CALL_FN(skirmish_drawRoundScreen, void, void)()
#define skirmish_drawNewPartsNotice() CALL_FN(skirmish_drawNewPartsNotice, void, void)()
#define missionList_draw() CALL_FN(missionList_draw, void, void)()
#define missionBriefing_draw() CALL_FN(missionBriefing_draw, void, void)()
#define playerSetup_hitTest(x, y) CALL_FN(playerSetup_hitTest, int, int, int)(x, y)   /* the SETUP PLAYER dialog's control at (x, y) */
#define dplay_openConnection(kind, host) CALL_FN(dplay_openConnection, int, u32, const char *)(kind, host)   /* a DirectPlay slot opened */
#define lobby_openConnection() CALL_FN(lobby_openConnection, int, void)()   /* the lobby server connection opened: 1 done */
#define arenaGameList_hitTest(x, y) CALL_FN(arenaGameList_hitTest, int, int, int)(x, y)   /* the arena lobby's button under (x, y), -1 none */
#define arena_askJoinPassword() CALL_FN(arena_askJoinPassword, void, void)()   /* the arena join password asked for when the picked game is locked (arena_editJoinPassword) */
#define arena_editAddress() CALL_FN(arena_editAddress, void, void)()   /* the IP address field opened (a game joined by address) */
#define menu_showMessage(i) CALL_FN(menu_showMessage, u32, int)(i)   /* message i in the message box */
#define reg_writeLadderSettings() CALL_FN(reg_writeLadderSettings, u32, void)()

/* ---- the screens' set-ups (menu/screen_enter.c): rectangle builders and resets ---- */
#define arena_clearSessionEntry() CALL_FN(arena_clearSessionEntry, void, void)()
#define lobbyTop_layout() CALL_FN(lobbyTop_layout, void, void)()
#define playerSetup_layout() CALL_FN(playerSetup_layout, void, void)()
#define arenaGameList_layout() CALL_FN(arenaGameList_layout, void, void)()
#define arenaDialogBox_layout() CALL_FN(arenaDialogBox_layout, void, void)()
#define createArena_layout() CALL_FN(createArena_layout, void, void)()
#define arenaUpdateNotice_layout() CALL_FN(arenaUpdateNotice_layout, void, void)()
#define setupSound_layout() CALL_FN(setupSound_layout, void, void)()
#define setupGraphic_layout() CALL_FN(setupGraphic_layout, void, void)()
#define setupControl_layout() CALL_FN(setupControl_layout, void, void)()
#define roomLogin_layout() CALL_FN(roomLogin_layout, void, void)()
#define account_layout() CALL_FN(account_layout, void, void)()
#define gameList_layout() CALL_FN(gameList_layout, void, void)()
#define gameListJoinBox_layout() CALL_FN(gameListJoinBox_layout, void, void)()
#define roomSettings_layout() CALL_FN(roomSettings_layout, void, void)()
#define ranking_layout() CALL_FN(ranking_layout, void, void)()
#define updateNotice_layout() CALL_FN(updateNotice_layout, void, void)()

#define ViewVolume_addQuad(view, texture, uv0, uv1, colour, points, extra, flag) CALL_THISFN(ViewVolume_addQuad, void, void *, int, const u32 *, const u32 *, const u32 *, const float *, u32, int)(view, texture, uv0, uv1, colour, points, extra, flag)   /* a textured quad into the view volume */

#define net_findFreeSession() CALL_FN(net_findFreeSession, int, void)()   /* the first free session slot, or -1 */

#define Mat4_transformPoint(out, m, p) CALL_FN(Mat4_transformPoint, void, float *, const float *, const float *)(out, m, p)

/* ---- (app/devices.c, net/network.c, app/small.c, render/object_list.c, menu/armc_misc.c) ---- */
#define dplay_send(from, to, flags, data, size) CALL_FN(dplay_send, int, u32, u32, u32, const void *, u32)(from, to, flags, data, size)   /* a DirectPlay message sent */
#define space_setBy(space, mn, mx, cz, cx, cy, margin, splitCount, depth) CALL_THISFN(space_setBy, u32, void *, void *, void *, int, int, int, int, int, int)(space, mn, mx, cz, cx, cy, margin, splitCount, depth)
#define shape_bindPartTextures(shape) CALL_THISFN(shape_bindPartTextures, u32, void *)(shape)   /* a shape's textures bound */
#define armc_partsPageClicks() CALL_FN(armc_partsPageClicks, u32, void)()
#define armc_weaponsPageClicks() CALL_FN(armc_weaponsPageClicks, u32, void)()
#define armc_colourPageClicks() CALL_FN(armc_colourPageClicks, u32, void)()

#define Mat4_fromAxisAngle(m, rotation) CALL_FN(Mat4_fromAxisAngle, void, float *, const float *)(m, rotation)   /* (angle, axis) -> matrix */

/* the DirectPlay slot functions by connection kind (src/net/dplay_slots.c) */
#define dplay_slotHost(kind, session, player, user1, maxPlayers, user2, hi, lo, data) 	GAME_CDECL(((const u32[4]){ FN(dplaySlot0_host), FN(dplaySlot1_host), FN(dplaySlot2_host), FN(dplaySlot3_host) })[kind], int, int, int, int, int, int, int, int, int)(session, player, user1, maxPlayers, user2, hi, lo, data)
#define dplay_slotJoin(kind, guid, player, data, gameMode) 	GAME_CDECL(((const u32[4]){ FN(dplaySlot0_join), FN(dplaySlot1_join), FN(dplaySlot2_join), FN(dplaySlot3_join) })[kind], int, int, int, int, int)(guid, player, data, gameMode)

/* the error reporters (src/app/error_log.c): a message, or a fatal one that ends the game */
#define sys_errorTerminate(...) CALL_FN(sys_errorTerminate, void, const char *, ...)(__VA_ARGS__)

/* a menu button's outline as menu_pointInPolygon takes it on the stack: the edge count, then the corners' xs and ys */
typedef struct { int n, x[5], y[5]; } Outline;   /* a MenuOutline (scene.fields) as point_in_outline takes it by value: the
   same 0x2c bytes, not packed (aligned loads, as the original) */
#define point_in_outline(x, y, outline) CALL_FN(menu_pointInPolygon, int, int, int, Outline)(x, y, outline)   /* menu_pointInPolygon */

/* the Korean text passes (text/text_passes.c): the lead glyphs, and the vowel and tail glyphs, at 13 and 31 units */
#define text_hangul13Pass(x, y, s) CALL_FN(text_hangul13Pass, void, int, int, const char *)(x, y, s)
#define text_hangul13LayeredPass(x, y, s) CALL_FN(text_hangul13LayeredPass, void, int, int, const char *)(x, y, s)
#define text_hangul31Pass(x, y, s) CALL_FN(text_hangul31Pass, void, int, int, const char *)(x, y, s)
#define text_hangul31LayeredPass(x, y, s) CALL_FN(text_hangul31LayeredPass, void, int, int, const char *)(x, y, s)

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
