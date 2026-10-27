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
#define glDisable(cap) IMPORT(0x4a922c, void, u32)(cap)

/* ---- C runtime of the game ---- */
#define sprintf(...) GAME_CDECL(0x49e9dd, int, char *, const char *, ...)(__VA_ARGS__)

/* ---- screen ---- */
#define gfx_setProjection2D3D(mode) GAME_CDECL(0x41ef90, void, int)(mode)   /* 1: 3D, 2: the menus' 2D */
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
#define text_drawSized(x, y, s, size) GAME_CDECL(0x44ad60, void, int, int, const char *, int)(x, y, s, size)

/* ---- HUD ---- */
#define hud_4950a0(x0, y0, x1, y1) GAME_CDECL(0x4950a0, void, int, int, int, int)(x0, y0, x1, y1)
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
#define Color4_set(dst, r, g, b, a) GAME_CDECL(0x41f0e0, void, Colour *, float, float, float, float)(dst, r, g, b, a)

/* ---- globals ---- */
typedef struct { float r, g, b, a; } Colour;
#define g_textColours ((Colour *)0xa1f100)          /* the 16 message colours */
#define g_chatLine ((char *)0x9dc92c)               /* the chat line being typed */
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
#define g_profileIntro GAME_VAR(int, 0x9f6838)       /* the profile screen's intro animation runs */
#define g_profileIntroState GAME_VAR(int, 0x9f8e54)  /* 5: finished */
#define g_profileIntroTime GAME_VAR(int, 0x9f8f30)
#define g_profileIntroZoom GAME_VAR(float, 0x9f8f14)
#define g_profileIntroSpeed GAME_VAR(float, 0x9f8e50)
#define g_profilePage GAME_VAR(int, 0x9f8f10)        /* 1 list, 2 info, 3 / 5 name forms, 6 emblem; 4 has no keys */
#define g_keyEnter GAME_VAR(int, 0x9dae70)           /* key bindings: Enter */
#define g_keyEnter2 GAME_VAR(int, 0x6803a0)          /* the second Enter key */
/* the mission-select screen */
#define g_missionShowBackground GAME_VAR(int, 0x9f63b8)
#define g_missionPage GAME_VAR(int, 0x9f62f8)        /* 0 / 1: no keys; 2: no list refresh */
#define g_missionBox ((const int *)0x9f6308)         /* the dialog frame: x0, y0, x1, y1 */
#define g_missionBusy GAME_VAR(int, 0x9f6300)
#define g_missionStarted GAME_VAR(int, 0x9f62e0)
/* exe strings passed to the text passes (the address itself is what the callee gets) */
#define STR_COPYRIGHT ((const char *)0x4b0474)       /* "AXIS by Jamie System Development" */
#define STR_VERSION ((const char *)0x4b0384)         /* "Axis v1.03" */

#endif
