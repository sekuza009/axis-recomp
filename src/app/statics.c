/* statics.c: code the compiler made around the game's global objects and classes: each class's run-time type name
   (an ErrorLog record naming it), the start-up constructors of global objects and the registration of their
   destructors with atexit, empty functions, and small setters of globals. */
#include "../game.h"

/* ---- class names: an ErrorLog record (vtable 0x4aa2a0) holding the class name, built once at start-up ---- */
void *(Texture_rtti)(void) { return ErrorLog_ctor((void *)0xa0dff8, (const char *)0x4b3e74, 0); }   /* 0x454fe0 "class Texture" */
void *(TextureManager_rtti)(void) { return ErrorLog_ctor((void *)0xa0e000, (const char *)0x4b4134, 0); }   /* 0x456940 "class TextureManager" */
void *(Sound_rtti)(void) { return ErrorLog_ctor((void *)0xa0e020, (const char *)0x4b42e0, 0); }   /* 0x456c90 "Sound" */
void *(Console_rtti)(void) { return ErrorLog_ctor((void *)0xa0e778, (const char *)0x4c456c, 0); }   /* 0x460520 "class Console" */
void *(Shape_rtti)(void) { return ErrorLog_ctor((void *)0xa0e790, (const char *)0x4c4a40, 0); }   /* 0x463b30 "class Shape" */
void *(ShapeManager_rtti)(void) { return ErrorLog_ctor((void *)0xa0e788, (const char *)0x4c4ca8, 0); }   /* 0x4669c0 "class ShapeManager" */
void *(Skeleton_rtti)(void) { return ErrorLog_ctor((void *)0xa0eaa8, (const char *)0x4c534c, 0); }   /* 0x469930 "class Skeleton" */
void *(SkeletonManager_rtti)(void) { return ErrorLog_ctor((void *)0xa0eaa0, (const char *)0x4c549c, 0); }   /* 0x46ae10 "class SkeletonManager" */
void *(BMPRGBFile_rtti)(void) { return ErrorLog_ctor((void *)0xa1f0f0, (const char *)0x4c58f4, 0); }   /* 0x46ccb0 "class BMPRGBFile" */
void *(RealColor_rtti)(void) { return ErrorLog_ctor((void *)0xa1f290, (const char *)0x4c59c0, 0); }   /* 0x46d270 "struct RealColor" */
void *(PackedColor_rtti)(void) { return ErrorLog_ctor((void *)0xa1f250, (const char *)0x4c59d4, 0); }   /* 0x46da70 "struct PackedColor" */
void *(UnitPartInfo_rtti)(void) { return ErrorLog_ctor((void *)0xae2ea0, (const char *)0x4c6ffc, 0); }   /* 0x46f360 "struct UnitPartInfo" */
void *(UnitPoseInfo_rtti)(void) { return ErrorLog_ctor((void *)0xae2ea8, (const char *)0x4c7010, 0); }   /* 0x46f3c0 "struct UnitPoseInfo" */
void *(Unit_rtti)(void) { return ErrorLog_ctor((void *)0xae2e98, (const char *)0x4c7024, 0); }   /* 0x46f420 "class Unit" */
void *(Stage_rtti)(void) { return ErrorLog_ctor((void *)0xae2eb8, (const char *)0x4c73b0, 0); }   /* 0x46ff20 "class Stage" */
void *(CollisionVolume_rtti)(void) { return ErrorLog_ctor((void *)0xae2ed0, (const char *)0x4c7800, 0); }   /* 0x481340 "class CollisionVolume" */
void *(Light_rtti)(void) { return ErrorLog_ctor((void *)0xae2ee8, (const char *)0x4c7ad4, 0); }   /* 0x483d00 "class Light" */
void *(ViewVolume_rtti)(void) { return ErrorLog_ctor((void *)0xae2ef0, (const char *)0x4c7b08, 0); }   /* 0x483f60 "class ViewVolume" */
void *(TimeSync_rtti)(void) { return ErrorLog_ctor((void *)0xae2f00, (const char *)0x4c7b70, 0); }   /* 0x4873e0 "class TimeSync" */
void *(Scene_rtti)(void) { return ErrorLog_ctor((void *)0xae3328, (const char *)0x4c7d18, 0); }   /* 0x48b3c0 "class Scene" */

/* ---- global objects: the vtable 0x4a956c (Texture) and an empty second field ---- */
void (static_initTex64x64)(void) { g_staticTex64x64 = 0x4a956c; GAME_VAR(u32, 0x4e1878 + 4) = 0; }   /* 0x42b130 */
void (static_initTex128x64)(void) { g_staticTex128x64 = 0x4a956c; GAME_VAR(u32, 0x5b1db8 + 4) = 0; }   /* 0x42b1a0 */
void (static_initTex256x64)(void) { g_staticTex256x64 = 0x4a956c; GAME_VAR(u32, 0x680cd8 + 4) = 0; }   /* 0x42b1f0 */
void (static_initTex128x128)(void) { g_staticTex128x128 = 0x4a956c; GAME_VAR(u32, 0x76d498 + 4) = 0; }   /* 0x42b240 */
void (static_initTex256x128)(void) { g_staticTex256x128 = 0x4a956c; GAME_VAR(u32, 0x90d1e0 + 4) = 0; }   /* 0x42b290 */
void (static_initTex256x256)(void) { g_staticTex256x256 = 0x4a956c; GAME_VAR(u32, 0x83a9e0 + 4) = 0; }   /* 0x42b2e0 */

/* ---- a global object's destructor registered with atexit (the result of atexit) ---- */
int (static_registerTex64x64Dtor)(void) { return atexit((void (*)(void))0x42b180); }
int (static_registerTex128x64Dtor)(void) { return atexit((void (*)(void))0x42b1d0); }
int (static_registerTex256x64Dtor)(void) { return atexit((void (*)(void))0x42b220); }
int (static_registerTex128x128Dtor)(void) { return atexit((void (*)(void))0x42b270); }
int (static_registerTex256x128Dtor)(void) { return atexit((void (*)(void))0x42b2c0); }
int (static_registerTex256x256Dtor)(void) { return atexit((void (*)(void))0x42b310); }
int (static_registerTextureManagerDtor)(void) { return atexit((void (*)(void))0x42b380); }
int (static_registerTextureRttiDtor)(void) { return atexit((void (*)(void))0x455010); }
int (static_registerTextureManagerRttiDtor)(void) { return atexit((void (*)(void))0x456970); }
int (static_registerSoundRttiDtor)(void) { return atexit((void (*)(void))0x456cc0); }
int (static_registerConsoleRttiDtor)(void) { return atexit((void (*)(void))0x460550); }
int (static_registerShapeRttiDtor)(void) { return atexit((void (*)(void))0x463b60); }
int (static_registerShapeManagerRttiDtor)(void) { return atexit((void (*)(void))0x4669f0); }
int (static_registerTimeSyncDtor)(void) { return atexit((void (*)(void))0x468740); }
int (static_registerSkeletonRttiDtor)(void) { return atexit((void (*)(void))0x469960); }
int (static_registerSkeletonManagerRttiDtor)(void) { return atexit((void (*)(void))0x46ae40); }
int (static_registerBMPRGBFileRttiDtor)(void) { return atexit((void (*)(void))0x46cce0); }
int (static_registerRealColorRttiDtor)(void) { return atexit((void (*)(void))0x46d2a0); }
int (static_registerPackedColorRttiDtor)(void) { return atexit((void (*)(void))0x46daa0); }
int (static_registerUnitPartInfoRttiDtor)(void) { return atexit((void (*)(void))0x46f390); }
int (static_registerUnitPoseInfoRttiDtor)(void) { return atexit((void (*)(void))0x46f3f0); }
int (static_registerUnitRttiDtor)(void) { return atexit((void (*)(void))0x46f450); }
int (static_registerStageRttiDtor)(void) { return atexit((void (*)(void))0x46ff50); }
int (static_registerCollisionVolumeRttiDtor)(void) { return atexit((void (*)(void))0x481370); }
int (static_registerLightRttiDtor)(void) { return atexit((void (*)(void))0x483d30); }
int (static_registerViewVolumeRttiDtor)(void) { return atexit((void (*)(void))0x483f90); }
int (static_registerTimeSyncRttiDtor)(void) { return atexit((void (*)(void))0x487410); }
int (static_registerSceneRttiDtor)(void) { return atexit((void (*)(void))0x48b3f0); }

/* ---- empty functions ---- */
void (static_emptyCtorSkelData1)(void) { }   /* 0x46b860 */
void (static_emptyCtorSkelData2)(void) { }   /* 0x46b880 */
void (static_emptyCtorSkelData3)(void) { }   /* 0x46b8a0 */
void (static_emptyCtorSkelData4)(void) { }   /* 0x46b8c0 */
void (static_emptyCtorSkelData5)(void) { }   /* 0x46b8e0 */
void (static_emptyCtorSkelData6)(void) { }   /* 0x46b900 */
void (static_emptyCtorSkelData7)(void) { }   /* 0x46b920 */
void (static_emptyCtorSkelData8)(void) { }   /* 0x46b940 */
void (static_emptyCtorTimeSync1)(void) { }   /* 0x487b70 */
void (static_emptyCtorTimeSync2)(void) { }   /* 0x487b90 */
void (debug_traceStripped)(void) { }   /* 0x48b420 */

/* ---- start-up: one global object made (or a class-name record), its destructor registered (atexit's result) ---- */
int (static_startTex64x64)(void) { static_initTex64x64(); return static_registerTex64x64Dtor(); }   /* 0x42b120 */
int (static_startTex128x64)(void) { static_initTex128x64(); return static_registerTex128x64Dtor(); }   /* 0x42b190 */
int (static_startTex256x64)(void) { static_initTex256x64(); return static_registerTex256x64Dtor(); }   /* 0x42b1e0 */
int (static_startTex128x128)(void) { static_initTex128x128(); return static_registerTex128x128Dtor(); }   /* 0x42b230 */
int (static_startTex256x128)(void) { static_initTex256x128(); return static_registerTex256x128Dtor(); }   /* 0x42b280 */
int (static_startTex256x256)(void) { static_initTex256x256(); return static_registerTex256x256Dtor(); }   /* 0x42b2d0 */
int (static_startTextureManager)(void) { TextureManager_ctor(); return static_registerTextureManagerDtor(); }   /* 0x42b320 */
int (static_startTextureRtti)(void) { Texture_rtti(); return static_registerTextureRttiDtor(); }   /* 0x454fd0 */
int (static_startTextureManagerRtti)(void) { TextureManager_rtti(); return static_registerTextureManagerRttiDtor(); }   /* 0x456930 */
int (static_startSoundRtti)(void) { Sound_rtti(); return static_registerSoundRttiDtor(); }   /* 0x456c80 */
int (static_startConsoleRtti)(void) { Console_rtti(); return static_registerConsoleRttiDtor(); }   /* 0x460510 */
int (static_startShapeRtti)(void) { Shape_rtti(); return static_registerShapeRttiDtor(); }   /* 0x463b20 */
int (static_startShapeManagerRtti)(void) { ShapeManager_rtti(); return static_registerShapeManagerRttiDtor(); }   /* 0x4669b0 */
int (static_startTimeSync)(void) { static_initTimeSync(); return static_registerTimeSyncDtor(); }   /* 0x468710 */
int (static_startSkeletonRtti)(void) { Skeleton_rtti(); return static_registerSkeletonRttiDtor(); }   /* 0x469920 */
int (static_startSkeletonManagerRtti)(void) { SkeletonManager_rtti(); return static_registerSkeletonManagerRttiDtor(); }   /* 0x46ae00 */
int (static_startBMPRGBFileRtti)(void) { BMPRGBFile_rtti(); return static_registerBMPRGBFileRttiDtor(); }   /* 0x46cca0 */
int (static_startRealColorRtti)(void) { RealColor_rtti(); return static_registerRealColorRttiDtor(); }   /* 0x46d260 */
int (static_startPackedColorRtti)(void) { PackedColor_rtti(); return static_registerPackedColorRttiDtor(); }   /* 0x46da60 */
int (static_startUnitPartInfoRtti)(void) { UnitPartInfo_rtti(); return static_registerUnitPartInfoRttiDtor(); }   /* 0x46f350 */
int (static_startUnitPoseInfoRtti)(void) { UnitPoseInfo_rtti(); return static_registerUnitPoseInfoRttiDtor(); }   /* 0x46f3b0 */
int (static_startUnitRtti)(void) { Unit_rtti(); return static_registerUnitRttiDtor(); }   /* 0x46f410 */
int (static_startStageRtti)(void) { Stage_rtti(); return static_registerStageRttiDtor(); }   /* 0x46ff10 */
int (static_startCollisionVolumeRtti)(void) { CollisionVolume_rtti(); return static_registerCollisionVolumeRttiDtor(); }   /* 0x481330 */
int (static_startLightRtti)(void) { Light_rtti(); return static_registerLightRttiDtor(); }   /* 0x483cf0 */
int (static_startViewVolumeRtti)(void) { ViewVolume_rtti(); return static_registerViewVolumeRttiDtor(); }   /* 0x483f50 */
int (static_startTimeSyncRtti)(void) { TimeSync_rtti(); return static_registerTimeSyncRttiDtor(); }   /* 0x4873d0 */
int (static_startSceneRtti)(void) { Scene_rtti(); return static_registerSceneRttiDtor(); }   /* 0x48b3b0 */

/* ---- the game's constant colours: packed (four bytes r, g, b, a) and real (four floats, as bits) ---- */
void (colour_initPackedBlue)(void) { u8 *c = (u8 *)0xa1f200; c[0] = 0; c[1] = 0; c[2] = 0xff; c[3] = 0xff; }   /* 0x46dbf0 */
void (colour_initPackedGrey)(void) { u8 *c = (u8 *)0xa1f204; c[0] = 0x7f; c[1] = 0x7f; c[2] = 0x7f; c[3] = 0xff; }   /* 0x46db30 */
void (colour_initPackedYellow)(void) { u8 *c = (u8 *)0xa1f208; c[0] = 0xff; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dc20 */
void (colour_initPackedClear)(void) { u8 *c = (u8 *)0xa1f220; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46dad0 */
void (colour_initPackedRed)(void) { u8 *c = (u8 *)0xa1f238; c[0] = 0xff; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db90 */
void (colour_initPackedWhite)(void) { u8 *c = (u8 *)0xa1f23c; c[0] = 0xff; c[1] = 0xff; c[2] = 0xff; c[3] = 0xff; }   /* 0x46db60 */
void (colour_initPackedBlack)(void) { u8 *c = (u8 *)0xa1f278; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db00 */
void (colour_initPackedGreen)(void) { u8 *c = (u8 *)0xa1f2ec; c[0] = 0; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dbc0 */
void (colour_initRealClear)(void) { u32 *c = (u32 *)0xa1f210; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46d2d0 */
void (colour_initRealBlue)(void) { u32 *c = (u32 *)0xa1f228; c[0] = 0; c[1] = 0; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d450 */
void (colour_initRealWhite)(void) { u32 *c = (u32 *)0xa1f240; c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d390 */
void (colour_initRealGreen)(void) { u32 *c = (u32 *)0xa1f258; c[0] = 0; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d410 */
void (colour_initRealRed)(void) { u32 *c = (u32 *)0xa1f268; c[0] = 0x3f800000u; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d3d0 */
void (colour_initRealBlack)(void) { u32 *c = (u32 *)0xa1f280; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d310 */
void (colour_initRealYellow)(void) { u32 *c = (u32 *)0xa1f2d8; c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d490 */
void (colour_initRealGrey)(void) { u32 *c = (u32 *)0xa1f2f0; c[0] = 0x3f000000u; c[1] = 0x3f000000u; c[2] = 0x3f000000u; c[3] = 0x3f800000u; }   /* 0x46d350 */

/* ---- a global object's destructor, run once (the guard byte's bit 0 set first): ErrorLog_dtor of the object ---- */
#define GUARDED_DTOR(name, guard, obj) \
	void (name)(void) \
	{ \
		if (!(GAME_VAR(u8, guard) & 1)) { \
			GAME_VAR(u8, guard) |= 1; \
			ErrorLog_dtor((void *)(obj)); \
		} \
	}
GUARDED_DTOR(static_endTextureRtti, 0xa0e009, 0xa0dff8)
GUARDED_DTOR(static_endTextureManagerRtti, 0xa0e008, 0xa0e000)
GUARDED_DTOR(static_endConsoleRtti, 0xa0e780, 0xa0e778)
GUARDED_DTOR(static_endShapeRtti, 0xa0e798, 0xa0e790)
GUARDED_DTOR(static_endShapeManagerRtti, 0xa0e799, 0xa0e788)
GUARDED_DTOR(static_endSkeletonRtti, 0xa0eab0, 0xa0eaa8)
GUARDED_DTOR(static_endSkeletonManagerRtti, 0xa0eab1, 0xa0eaa0)
GUARDED_DTOR(static_endBMPRGBFileRtti, 0xa1f0f8, 0xa1f0f0)
GUARDED_DTOR(static_endRealColorRtti, 0xa1f2e8, 0xa1f290)
GUARDED_DTOR(static_endPackedColorRtti, 0xa1f2e9, 0xa1f250)
GUARDED_DTOR(static_endUnitPartInfoRtti, 0xae2eb2, 0xae2ea0)
GUARDED_DTOR(static_endUnitPoseInfoRtti, 0xae2eb1, 0xae2ea8)
GUARDED_DTOR(static_endUnitRtti, 0xae2eb0, 0xae2e98)
GUARDED_DTOR(static_endStageRtti, 0xae2ec0, 0xae2eb8)
GUARDED_DTOR(static_endCollisionVolumeRtti, 0xae2ed8, 0xae2ed0)
GUARDED_DTOR(static_endLightRtti, 0xae2ee0, 0xae2ee8)
GUARDED_DTOR(static_endViewVolumeRtti, 0xae2ef8, 0xae2ef0)
GUARDED_DTOR(static_endTimeSyncRtti, 0xae2f08, 0xae2f00)
GUARDED_DTOR(static_endSceneRtti, 0xae3330, 0xae3328)
#undef GUARDED_DTOR
