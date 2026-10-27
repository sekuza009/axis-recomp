/* batch 149 (lifted/grp95.c): the console's destructor */
#include "lifted/grp95.c"
/* 0x460c40 (thiscall) Console_ctor(): misnamed: the console's destructor: an SEH frame, the vtable 0x4aa238, then
   the members in reverse: the stage at +0x1f36c8 (Stage_dtor), the view volume at +0x74 (ViewVolume_dtor), the
   time sync at +0xc (TimeSync_dtor) */
static THISCALL DWORD Console_ctor(char *self) { return run_lifted(lift_460c40, (DWORD)self, 0, NULL); }
/* 0x460c20 (thiscall) Console_deletingDtor(flags): the destructor, then delete when flags bit 0; returns this */
static THISCALL DWORD Console_deletingDtor(char *self, DWORD flags) { DWORD v[1] = { flags }; return run_lifted(lift_460c20, (DWORD)self, 1, v); }
