/* statics.c: code the compiler made around the game's global objects and classes: each class's run-time type name
   (an ErrorLog record naming it), the start-up constructors of global objects and the registration of their
   destructors with atexit, empty functions, and small setters of globals. */
#include "../game.h"

/* ---- each class's error log: an ErrorLog record (vtable 0x4aa2a0) holding the class's name, built once at start-up;
   the fatal and error messages print it (sys_fatalError(g_logStage, ..)) ---- */
void *(Texture_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logTexture), (const char *)STR(0x4b3e74, "class Texture"), 0); }   /* 0x454fe0 "class Texture" */
void *(TextureManager_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logTextureManager), (const char *)STR(0x4b4134, "class TextureManager"), 0); }   /* 0x456940 "class TextureManager" */
void *(Sound_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logSound), (const char *)STR(0x4b42e0, "Sound"), 0); }   /* 0x456c90 "Sound" */
void *(Console_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logConsole), (const char *)STR(0x4c456c, "class Console"), 0); }   /* 0x460520 "class Console" */
void *(Shape_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logShape), (const char *)STR(0x4c4a40, "class Shape"), 0); }   /* 0x463b30 "class Shape" */
void *(ShapeManager_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logShapeManager), (const char *)STR(0x4c4ca8, "class ShapeManager"), 0); }   /* 0x4669c0 "class ShapeManager" */
void *(Skeleton_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logSkeleton), (const char *)STR(0x4c534c, "class Skeleton"), 0); }   /* 0x469930 "class Skeleton" */
void *(SkeletonManager_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logSkeletonManager), (const char *)STR(0x4c549c, "class SkeletonManager"), 0); }   /* 0x46ae10 "class SkeletonManager" */
void *(BMPRGBFile_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logBMPRGBFile), (const char *)STR(0x4c58f4, "class BMPRGBFile"), 0); }   /* 0x46ccb0 "class BMPRGBFile" */
void *(RealColor_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logRealColor), (const char *)STR(0x4c59c0, "struct RealColor"), 0); }   /* 0x46d270 "struct RealColor" */
void *(PackedColor_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logPackedColor), (const char *)STR(0x4c59d4, "struct PackedColor"), 0); }   /* 0x46da70 "struct PackedColor" */
void *(UnitPartInfo_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logUnitPartInfo), (const char *)STR(0x4c6ffc, "struct UnitPartInfo"), 0); }   /* 0x46f360 "struct UnitPartInfo" */
void *(UnitPoseInfo_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logUnitPoseInfo), (const char *)STR(0x4c7010, "struct UnitPoseInfo"), 0); }   /* 0x46f3c0 "struct UnitPoseInfo" */
void *(Unit_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logUnit), (const char *)STR(0x4c7024, "class Unit"), 0); }   /* 0x46f420 "class Unit" */
void *(Stage_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logStage), (const char *)STR(0x4c73b0, "class Stage"), 0); }   /* 0x46ff20 "class Stage" */
void *(CollisionVolume_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logCollisionVolume), (const char *)STR(0x4c7800, "class CollisionVolume"), 0); }   /* 0x481340 "class CollisionVolume" */
void *(Light_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logLight), (const char *)STR(0x4c7ad4, "class Light"), 0); }   /* 0x483d00 "class Light" */
void *(ViewVolume_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logViewVolume), (const char *)STR(0x4c7b08, "class ViewVolume"), 0); }   /* 0x483f60 "class ViewVolume" */
void *(TimeSync_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logTimeSync), (const char *)STR(0x4c7b70, "class TimeSync"), 0); }   /* 0x4873e0 "class TimeSync" */
void *(Scene_initLog)(void) { return ErrorLog_ctor((void *)OBJ(g_logScene), (const char *)STR(0x4c7d18, "class Scene"), 0); }   /* 0x48b3c0 "class Scene" */

/* ---- global objects: the vtable 0x4a956c (Texture) and an empty second field ---- */
void (static_initTex64x64)(void) { g_texture64x64Vtable = VT(Texture); ((TextureBank *)g_texture64x64)->ready = 0; }   /* 0x42b130 */
void (static_initTex128x64)(void) { g_texture128x64Vtable = VT(Texture); ((TextureBank *)g_texture128x64)->ready = 0; }   /* 0x42b1a0 */
void (static_initTex256x64)(void) { g_texture256x64Vtable = VT(Texture); ((TextureBank *)g_texture256x64)->ready = 0; }   /* 0x42b1f0 */
void (static_initTex128x128)(void) { g_texture128x128Vtable = VT(Texture); ((TextureBank *)g_texture128x128)->ready = 0; }   /* 0x42b240 */
void (static_initTex256x128)(void) { g_texture256x128Vtable = VT(Texture); ((TextureBank *)g_texture256x128)->ready = 0; }   /* 0x42b290 */
void (static_initTex256x256)(void) { g_texture256x256Vtable = VT(Texture); ((TextureBank *)g_texture256x256)->ready = 0; }   /* 0x42b2e0 */

/* ---- a global object's destructor registered with atexit (the result of atexit) ---- */
int (static_registerTex64x64Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex64x64)); }
int (static_registerTex128x64Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex128x64)); }
int (static_registerTex256x64Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex256x64)); }
int (static_registerTex128x128Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex128x128)); }
int (static_registerTex256x128Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex256x128)); }
int (static_registerTex256x256Dtor)(void) { return atexit((void (*)(void))FN(static_destroyTex256x256)); }
int (static_registerTextureManagerDtor)(void) { return atexit((void (*)(void))FN(static_endTextureManager)); }
int (static_registerTextureLogDtor)(void) { return atexit((void (*)(void))FN(static_endTextureLog)); }
int (static_registerTextureManagerLogDtor)(void) { return atexit((void (*)(void))FN(static_endTextureManagerLog)); }
int (static_registerSoundLogDtor)(void) { return atexit((void (*)(void))FN(static_endSoundLog)); }
int (static_registerConsoleLogDtor)(void) { return atexit((void (*)(void))FN(static_endConsoleLog)); }
int (static_registerShapeLogDtor)(void) { return atexit((void (*)(void))FN(static_endShapeLog)); }
int (static_registerShapeManagerLogDtor)(void) { return atexit((void (*)(void))FN(static_endShapeManagerLog)); }
int (static_registerTimeSyncDtor)(void) { return atexit((void (*)(void))FN(static_endTimeSync)); }
int (static_registerSkeletonLogDtor)(void) { return atexit((void (*)(void))FN(static_endSkeletonLog)); }
int (static_registerSkeletonManagerLogDtor)(void) { return atexit((void (*)(void))FN(static_endSkeletonManagerLog)); }
int (static_registerBMPRGBFileLogDtor)(void) { return atexit((void (*)(void))FN(static_endBMPRGBFileLog)); }
int (static_registerRealColorLogDtor)(void) { return atexit((void (*)(void))FN(static_endRealColorLog)); }
int (static_registerPackedColorLogDtor)(void) { return atexit((void (*)(void))FN(static_endPackedColorLog)); }
int (static_registerUnitPartInfoLogDtor)(void) { return atexit((void (*)(void))FN(static_endUnitPartInfoLog)); }
int (static_registerUnitPoseInfoLogDtor)(void) { return atexit((void (*)(void))FN(static_endUnitPoseInfoLog)); }
int (static_registerUnitLogDtor)(void) { return atexit((void (*)(void))FN(static_endUnitLog)); }
int (static_registerStageLogDtor)(void) { return atexit((void (*)(void))FN(static_endStageLog)); }
int (static_registerCollisionVolumeLogDtor)(void) { return atexit((void (*)(void))FN(static_endCollisionVolumeLog)); }
int (static_registerLightLogDtor)(void) { return atexit((void (*)(void))FN(static_endLightLog)); }
int (static_registerViewVolumeLogDtor)(void) { return atexit((void (*)(void))FN(static_endViewVolumeLog)); }
int (static_registerTimeSyncLogDtor)(void) { return atexit((void (*)(void))FN(static_endTimeSyncLog)); }
int (static_registerSceneLogDtor)(void) { return atexit((void (*)(void))FN(static_endSceneLog)); }

/* ---- empty functions ---- */
/* ten empty start-up initialisers (each a bare "ret", run once from crt_start's initialiser table): the eight at
   0x46b860 .. 0x46b940 follow the skeleton data code (skelDat_), the two at 0x487b70 / 0x487b90 the item / play info
   loaders; an empty body names no object, so they are named by address */
void (static_emptyInit_46b860)(void) { }   /* 0x46b860 */
void (static_emptyInit_46b880)(void) { }   /* 0x46b880 */
void (static_emptyInit_46b8a0)(void) { }   /* 0x46b8a0 */
void (static_emptyInit_46b8c0)(void) { }   /* 0x46b8c0 */
void (static_emptyInit_46b8e0)(void) { }   /* 0x46b8e0 */
void (static_emptyInit_46b900)(void) { }   /* 0x46b900 */
void (static_emptyInit_46b920)(void) { }   /* 0x46b920 */
void (static_emptyInit_46b940)(void) { }   /* 0x46b940 */
void (static_emptyInit_487b70)(void) { }   /* 0x487b70 */
void (static_emptyInit_487b90)(void) { }   /* 0x487b90 */
/* 0x48b420: an empty function ("ret") shared by every empty function of the game (identical code folded): called
   as a cdecl one-argument trace (net_processGamePacket pushes the packet and pops 4), as an empty thiscall method
   (Scene_ctor, stage_build, script_reset with &stage->scenePath, match_drawFrame) and with no arguments from the menus' key
   / click handlers (lobby_topPageClicks, lobbyTop_keys, armc_processInput, menuState100_intro, setup_topPageClicks /
   Keys, room_leave, roomLogin_clicks / keys, mainmenu_clicks / processKeys) */
void (shared_emptyFunction)(void) { }   /* 0x48b420 */

/* ---- start-up: one global object made (or a class's error log), its destructor registered (atexit's result) ---- */
int (static_startTex64x64)(void) { static_initTex64x64(); return static_registerTex64x64Dtor(); }   /* 0x42b120 */
int (static_startTex128x64)(void) { static_initTex128x64(); return static_registerTex128x64Dtor(); }   /* 0x42b190 */
int (static_startTex256x64)(void) { static_initTex256x64(); return static_registerTex256x64Dtor(); }   /* 0x42b1e0 */
int (static_startTex128x128)(void) { static_initTex128x128(); return static_registerTex128x128Dtor(); }   /* 0x42b230 */
int (static_startTex256x128)(void) { static_initTex256x128(); return static_registerTex256x128Dtor(); }   /* 0x42b280 */
int (static_startTex256x256)(void) { static_initTex256x256(); return static_registerTex256x256Dtor(); }   /* 0x42b2d0 */
int (static_startTextureManager)(void) { TextureManager_ctor(); return static_registerTextureManagerDtor(); }   /* 0x42b320 */
int (static_startTextureLog)(void) { Texture_initLog(); return static_registerTextureLogDtor(); }   /* 0x454fd0 */
int (static_startTextureManagerLog)(void) { TextureManager_initLog(); return static_registerTextureManagerLogDtor(); }   /* 0x456930 */
int (static_startSoundLog)(void) { Sound_initLog(); return static_registerSoundLogDtor(); }   /* 0x456c80 */
int (static_startConsoleLog)(void) { Console_initLog(); return static_registerConsoleLogDtor(); }   /* 0x460510 */
int (static_startShapeLog)(void) { Shape_initLog(); return static_registerShapeLogDtor(); }   /* 0x463b20 */
int (static_startShapeManagerLog)(void) { ShapeManager_initLog(); return static_registerShapeManagerLogDtor(); }   /* 0x4669b0 */
int (static_startTimeSync)(void) { static_initTimeSync(); return static_registerTimeSyncDtor(); }   /* 0x468710 */
int (static_startSkeletonLog)(void) { Skeleton_initLog(); return static_registerSkeletonLogDtor(); }   /* 0x469920 */
int (static_startSkeletonManagerLog)(void) { SkeletonManager_initLog(); return static_registerSkeletonManagerLogDtor(); }   /* 0x46ae00 */
int (static_startBMPRGBFileLog)(void) { BMPRGBFile_initLog(); return static_registerBMPRGBFileLogDtor(); }   /* 0x46cca0 */
int (static_startRealColorLog)(void) { RealColor_initLog(); return static_registerRealColorLogDtor(); }   /* 0x46d260 */
int (static_startPackedColorLog)(void) { PackedColor_initLog(); return static_registerPackedColorLogDtor(); }   /* 0x46da60 */
int (static_startUnitPartInfoLog)(void) { UnitPartInfo_initLog(); return static_registerUnitPartInfoLogDtor(); }   /* 0x46f350 */
int (static_startUnitPoseInfoLog)(void) { UnitPoseInfo_initLog(); return static_registerUnitPoseInfoLogDtor(); }   /* 0x46f3b0 */
int (static_startUnitLog)(void) { Unit_initLog(); return static_registerUnitLogDtor(); }   /* 0x46f410 */
int (static_startStageLog)(void) { Stage_initLog(); return static_registerStageLogDtor(); }   /* 0x46ff10 */
int (static_startCollisionVolumeLog)(void) { CollisionVolume_initLog(); return static_registerCollisionVolumeLogDtor(); }   /* 0x481330 */
int (static_startLightLog)(void) { Light_initLog(); return static_registerLightLogDtor(); }   /* 0x483cf0 */
int (static_startViewVolumeLog)(void) { ViewVolume_initLog(); return static_registerViewVolumeLogDtor(); }   /* 0x483f50 */
int (static_startTimeSyncLog)(void) { TimeSync_initLog(); return static_registerTimeSyncLogDtor(); }   /* 0x4873d0 */
int (static_startSceneLog)(void) { Scene_initLog(); return static_registerSceneLogDtor(); }   /* 0x48b3b0 */

/* ---- the game's constant colours: packed (four bytes r, g, b, a) and real (four floats, as bits) ---- */
void (colour_initPackedBlue)(void) { u8 *c = g_packedBlue; c[0] = 0; c[1] = 0; c[2] = 0xff; c[3] = 0xff; }   /* 0x46dbf0 */
void (colour_initPackedGrey)(void) { u8 *c = g_packedGrey; c[0] = 0x7f; c[1] = 0x7f; c[2] = 0x7f; c[3] = 0xff; }   /* 0x46db30 */
void (colour_initPackedYellow)(void) { u8 *c = g_packedYellow; c[0] = 0xff; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dc20 */
void (colour_initPackedClear)(void) { u8 *c = (u8 *)ADDR(g_defaultColour); c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46dad0 */
void (colour_initPackedRed)(void) { u8 *c = (u8 *)ADDR(g_packedRed); c[0] = 0xff; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db90 */
void (colour_initPackedWhite)(void) { u8 *c = g_packedWhite; c[0] = 0xff; c[1] = 0xff; c[2] = 0xff; c[3] = 0xff; }   /* 0x46db60 */
void (colour_initPackedBlack)(void) { u8 *c = (u8 *)ADDR(g_unlit); c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db00 */
void (colour_initPackedGreen)(void) { u8 *c = g_packedGreen; c[0] = 0; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dbc0 */
void (colour_initRealClear)(void) { u32 *c = (u32 *)OBJ(g_realClear); c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46d2d0 */
void (colour_initRealBlue)(void) { u32 *c = (u32 *)OBJ(g_realBlue); c[0] = 0; c[1] = 0; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d450 */
void (colour_initRealWhite)(void) { u32 *c = (u32 *)OBJ(g_realWhite); c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d390 */
void (colour_initRealGreen)(void) { u32 *c = (u32 *)OBJ(g_realGreen); c[0] = 0; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d410 */
void (colour_initRealRed)(void) { u32 *c = (u32 *)OBJ(g_realRed); c[0] = 0x3f800000u; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d3d0 */
void (colour_initRealBlack)(void) { u32 *c = (u32 *)OBJ(g_realBlack); c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d310 */
void (colour_initRealYellow)(void) { u32 *c = (u32 *)OBJ(g_realYellow); c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d490 */
void (colour_initRealGrey)(void) { u32 *c = (u32 *)OBJ(g_realGrey); c[0] = 0x3f000000u; c[1] = 0x3f000000u; c[2] = 0x3f000000u; c[3] = 0x3f800000u; }   /* 0x46d350 */

/* ---- a global object's destructor, run once (the guard byte's bit 0 set first): ErrorLog_dtor of the object ---- */
#define GUARDED_DTOR(name, guard, obj) \
	void (name)(void) \
	{ \
		if (!(GAME_VAR(u8, guard) & 1)) { \
			GAME_VAR(u8, guard) |= 1; \
			ErrorLog_dtor((void *)(obj)); \
		} \
	}
GUARDED_DTOR(static_endTextureLog, 0xa0e009, OBJ(g_logTexture))
GUARDED_DTOR(static_endTextureManagerLog, 0xa0e008, OBJ(g_logTextureManager))
GUARDED_DTOR(static_endConsoleLog, 0xa0e780, OBJ(g_logConsole))
GUARDED_DTOR(static_endShapeLog, 0xa0e798, OBJ(g_logShape))
GUARDED_DTOR(static_endShapeManagerLog, 0xa0e799, OBJ(g_logShapeManager))
GUARDED_DTOR(static_endSkeletonLog, 0xa0eab0, OBJ(g_logSkeleton))
GUARDED_DTOR(static_endSkeletonManagerLog, 0xa0eab1, OBJ(g_logSkeletonManager))
GUARDED_DTOR(static_endBMPRGBFileLog, 0xa1f0f8, OBJ(g_logBMPRGBFile))
GUARDED_DTOR(static_endRealColorLog, 0xa1f2e8, OBJ(g_logRealColor))
GUARDED_DTOR(static_endPackedColorLog, 0xa1f2e9, OBJ(g_logPackedColor))
GUARDED_DTOR(static_endUnitPartInfoLog, 0xae2eb2, OBJ(g_logUnitPartInfo))
GUARDED_DTOR(static_endUnitPoseInfoLog, 0xae2eb1, OBJ(g_logUnitPoseInfo))
GUARDED_DTOR(static_endUnitLog, 0xae2eb0, OBJ(g_logUnit))
GUARDED_DTOR(static_endStageLog, 0xae2ec0, OBJ(g_logStage))
GUARDED_DTOR(static_endCollisionVolumeLog, 0xae2ed8, OBJ(g_logCollisionVolume))
GUARDED_DTOR(static_endLightLog, 0xae2ee0, OBJ(g_logLight))
GUARDED_DTOR(static_endViewVolumeLog, 0xae2ef8, OBJ(g_logViewVolume))
GUARDED_DTOR(static_endTimeSyncLog, 0xae2f08, OBJ(g_logTimeSync))
GUARDED_DTOR(static_endSceneLog, 0xae3330, OBJ(g_logScene))
#undef GUARDED_DTOR
