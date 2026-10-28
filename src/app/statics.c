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
void (static_initObject_4e1878)(void) { GAME_VAR(u32, 0x4e1878) = 0x4a956c; GAME_VAR(u32, 0x4e1878 + 4) = 0; }   /* 0x42b130 */
void (static_initObject_5b1db8)(void) { GAME_VAR(u32, 0x5b1db8) = 0x4a956c; GAME_VAR(u32, 0x5b1db8 + 4) = 0; }   /* 0x42b1a0 */
void (static_initObject_680cd8)(void) { GAME_VAR(u32, 0x680cd8) = 0x4a956c; GAME_VAR(u32, 0x680cd8 + 4) = 0; }   /* 0x42b1f0 */
void (static_initObject_76d498)(void) { GAME_VAR(u32, 0x76d498) = 0x4a956c; GAME_VAR(u32, 0x76d498 + 4) = 0; }   /* 0x42b240 */
void (static_initObject_90d1e0)(void) { GAME_VAR(u32, 0x90d1e0) = 0x4a956c; GAME_VAR(u32, 0x90d1e0 + 4) = 0; }   /* 0x42b290 */
void (static_initObject_83a9e0)(void) { GAME_VAR(u32, 0x83a9e0) = 0x4a956c; GAME_VAR(u32, 0x83a9e0 + 4) = 0; }   /* 0x42b2e0 */

/* ---- a global object's destructor registered with atexit (the result of atexit) ---- */
int (static_registerDtor_42b170)(void) { return atexit((void (*)(void))0x42b180); }
int (static_registerDtor_42b1c0)(void) { return atexit((void (*)(void))0x42b1d0); }
int (static_registerDtor_42b210)(void) { return atexit((void (*)(void))0x42b220); }
int (static_registerDtor_42b260)(void) { return atexit((void (*)(void))0x42b270); }
int (static_registerDtor_42b2b0)(void) { return atexit((void (*)(void))0x42b2c0); }
int (static_registerDtor_42b300)(void) { return atexit((void (*)(void))0x42b310); }
int (static_registerDtor_42b370)(void) { return atexit((void (*)(void))0x42b380); }
int (static_registerDtor_455000)(void) { return atexit((void (*)(void))0x455010); }
int (static_registerDtor_456960)(void) { return atexit((void (*)(void))0x456970); }
int (static_registerDtor_456cb0)(void) { return atexit((void (*)(void))0x456cc0); }
int (static_registerDtor_460540)(void) { return atexit((void (*)(void))0x460550); }
int (static_registerDtor_463b50)(void) { return atexit((void (*)(void))0x463b60); }
int (static_registerDtor_4669e0)(void) { return atexit((void (*)(void))0x4669f0); }
int (static_registerDtor_468730)(void) { return atexit((void (*)(void))0x468740); }
int (static_registerDtor_469950)(void) { return atexit((void (*)(void))0x469960); }
int (static_registerDtor_46ae30)(void) { return atexit((void (*)(void))0x46ae40); }
int (static_registerDtor_46ccd0)(void) { return atexit((void (*)(void))0x46cce0); }
int (static_registerDtor_46d290)(void) { return atexit((void (*)(void))0x46d2a0); }
int (static_registerDtor_46da90)(void) { return atexit((void (*)(void))0x46daa0); }
int (static_registerDtor_46f380)(void) { return atexit((void (*)(void))0x46f390); }
int (static_registerDtor_46f3e0)(void) { return atexit((void (*)(void))0x46f3f0); }
int (static_registerDtor_46f440)(void) { return atexit((void (*)(void))0x46f450); }
int (static_registerDtor_46ff40)(void) { return atexit((void (*)(void))0x46ff50); }
int (static_registerDtor_481360)(void) { return atexit((void (*)(void))0x481370); }
int (static_registerDtor_483d20)(void) { return atexit((void (*)(void))0x483d30); }
int (static_registerDtor_483f80)(void) { return atexit((void (*)(void))0x483f90); }
int (static_registerDtor_487400)(void) { return atexit((void (*)(void))0x487410); }
int (static_registerDtor_48b3e0)(void) { return atexit((void (*)(void))0x48b3f0); }

/* ---- empty functions ---- */
void (nullsub_46b860)(void) { }   /* 0x46b860 */
void (nullsub_46b880)(void) { }   /* 0x46b880 */
void (nullsub_46b8a0)(void) { }   /* 0x46b8a0 */
void (nullsub_46b8c0)(void) { }   /* 0x46b8c0 */
void (nullsub_46b8e0)(void) { }   /* 0x46b8e0 */
void (nullsub_46b900)(void) { }   /* 0x46b900 */
void (nullsub_46b920)(void) { }   /* 0x46b920 */
void (nullsub_46b940)(void) { }   /* 0x46b940 */
void (nullsub_487b70)(void) { }   /* 0x487b70 */
void (nullsub_487b90)(void) { }   /* 0x487b90 */
void (nullsub_48b420)(void) { }   /* 0x48b420 */

/* ---- start-up: one global object made (or a class-name record), its destructor registered (atexit's result) ---- */
int (FUN_0042b120)(void) { static_initObject_4e1878(); return static_registerDtor_42b170(); }   /* 0x42b120 */
int (FUN_0042b190)(void) { static_initObject_5b1db8(); return static_registerDtor_42b1c0(); }   /* 0x42b190 */
int (FUN_0042b1e0)(void) { static_initObject_680cd8(); return static_registerDtor_42b210(); }   /* 0x42b1e0 */
int (FUN_0042b230)(void) { static_initObject_76d498(); return static_registerDtor_42b260(); }   /* 0x42b230 */
int (FUN_0042b280)(void) { static_initObject_90d1e0(); return static_registerDtor_42b2b0(); }   /* 0x42b280 */
int (FUN_0042b2d0)(void) { static_initObject_83a9e0(); return static_registerDtor_42b300(); }   /* 0x42b2d0 */
int (FUN_0042b320)(void) { TextureManager_ctor(); return static_registerDtor_42b370(); }   /* 0x42b320 */
int (FUN_00454fd0)(void) { Texture_rtti(); return static_registerDtor_455000(); }   /* 0x454fd0 */
int (FUN_00456930)(void) { TextureManager_rtti(); return static_registerDtor_456960(); }   /* 0x456930 */
int (FUN_00456c80)(void) { Sound_rtti(); return static_registerDtor_456cb0(); }   /* 0x456c80 */
int (FUN_00460510)(void) { Console_rtti(); return static_registerDtor_460540(); }   /* 0x460510 */
int (FUN_00463b20)(void) { Shape_rtti(); return static_registerDtor_463b50(); }   /* 0x463b20 */
int (FUN_004669b0)(void) { ShapeManager_rtti(); return static_registerDtor_4669e0(); }   /* 0x4669b0 */
int (FUN_00468710)(void) { load_487430_wrap_468720(); return static_registerDtor_468730(); }   /* 0x468710 */
int (FUN_00469920)(void) { Skeleton_rtti(); return static_registerDtor_469950(); }   /* 0x469920 */
int (FUN_0046ae00)(void) { SkeletonManager_rtti(); return static_registerDtor_46ae30(); }   /* 0x46ae00 */
int (FUN_0046cca0)(void) { BMPRGBFile_rtti(); return static_registerDtor_46ccd0(); }   /* 0x46cca0 */
int (FUN_0046d260)(void) { RealColor_rtti(); return static_registerDtor_46d290(); }   /* 0x46d260 */
int (FUN_0046da60)(void) { PackedColor_rtti(); return static_registerDtor_46da90(); }   /* 0x46da60 */
int (FUN_0046f350)(void) { UnitPartInfo_rtti(); return static_registerDtor_46f380(); }   /* 0x46f350 */
int (FUN_0046f3b0)(void) { UnitPoseInfo_rtti(); return static_registerDtor_46f3e0(); }   /* 0x46f3b0 */
int (FUN_0046f410)(void) { Unit_rtti(); return static_registerDtor_46f440(); }   /* 0x46f410 */
int (FUN_0046ff10)(void) { Stage_rtti(); return static_registerDtor_46ff40(); }   /* 0x46ff10 */
int (FUN_00481330)(void) { CollisionVolume_rtti(); return static_registerDtor_481360(); }   /* 0x481330 */
int (FUN_00483cf0)(void) { Light_rtti(); return static_registerDtor_483d20(); }   /* 0x483cf0 */
int (FUN_00483f50)(void) { ViewVolume_rtti(); return static_registerDtor_483f80(); }   /* 0x483f50 */
int (FUN_004873d0)(void) { TimeSync_rtti(); return static_registerDtor_487400(); }   /* 0x4873d0 */
int (FUN_0048b3b0)(void) { Scene_rtti(); return static_registerDtor_48b3e0(); }   /* 0x48b3b0 */

/* ---- the game's constant colours: packed (four bytes r, g, b, a) and real (four floats, as bits) ---- */
void (FUN_0046dbf0)(void) { u8 *c = (u8 *)0xa1f200; c[0] = 0; c[1] = 0; c[2] = 0xff; c[3] = 0xff; }   /* 0x46dbf0 */
void (FUN_0046db30)(void) { u8 *c = (u8 *)0xa1f204; c[0] = 0x7f; c[1] = 0x7f; c[2] = 0x7f; c[3] = 0xff; }   /* 0x46db30 */
void (FUN_0046dc20)(void) { u8 *c = (u8 *)0xa1f208; c[0] = 0xff; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dc20 */
void (FUN_0046dad0)(void) { u8 *c = (u8 *)0xa1f220; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46dad0 */
void (FUN_0046db90)(void) { u8 *c = (u8 *)0xa1f238; c[0] = 0xff; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db90 */
void (FUN_0046db60)(void) { u8 *c = (u8 *)0xa1f23c; c[0] = 0xff; c[1] = 0xff; c[2] = 0xff; c[3] = 0xff; }   /* 0x46db60 */
void (FUN_0046db00)(void) { u8 *c = (u8 *)0xa1f278; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0xff; }   /* 0x46db00 */
void (FUN_0046dbc0)(void) { u8 *c = (u8 *)0xa1f2ec; c[0] = 0; c[1] = 0xff; c[2] = 0; c[3] = 0xff; }   /* 0x46dbc0 */
void (FUN_0046d2d0)(void) { u32 *c = (u32 *)0xa1f210; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0; }   /* 0x46d2d0 */
void (FUN_0046d450)(void) { u32 *c = (u32 *)0xa1f228; c[0] = 0; c[1] = 0; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d450 */
void (FUN_0046d390)(void) { u32 *c = (u32 *)0xa1f240; c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0x3f800000u; c[3] = 0x3f800000u; }   /* 0x46d390 */
void (FUN_0046d410)(void) { u32 *c = (u32 *)0xa1f258; c[0] = 0; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d410 */
void (FUN_0046d3d0)(void) { u32 *c = (u32 *)0xa1f268; c[0] = 0x3f800000u; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d3d0 */
void (FUN_0046d310)(void) { u32 *c = (u32 *)0xa1f280; c[0] = 0; c[1] = 0; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d310 */
void (FUN_0046d490)(void) { u32 *c = (u32 *)0xa1f2d8; c[0] = 0x3f800000u; c[1] = 0x3f800000u; c[2] = 0; c[3] = 0x3f800000u; }   /* 0x46d490 */
void (FUN_0046d350)(void) { u32 *c = (u32 *)0xa1f2f0; c[0] = 0x3f000000u; c[1] = 0x3f000000u; c[2] = 0x3f000000u; c[3] = 0x3f800000u; }   /* 0x46d350 */
