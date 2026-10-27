/* batch 59 (lifted/grp7.c): menu frame/overlay drawing (calling the patched projection switch natively), GL window
   and display mode, dat/image file opening, the game timer, the clock check, profile deletion, the character
   settings in the registry and their room users, GL state, texture uploads */
#include "lifted/grp7.c"
/* 0x41b710 armc_41b710: 3D projection, white, texturing, the menu camera */
LIFT_PLAIN(armc_41b710, 41b710)
/* 0x40ce70 menu_drawDimOverlay / 0x43df00 room_43df00: fade a dark rectangle in over the screen */
LIFT_PLAIN(menu_drawDimOverlay, 40ce70)
LIFT_PLAIN(room_43df00, 43df00)
/* 0x428890 menu_428890(x, y): the blinking cursor bar; 0x428c30 menu_drawFrame(x0, y0, x1, y1): a window frame */
LIFT_PLAIN(menu_428890, 428890)
LIFT_PLAIN(menu_drawFrame, 428c30)
/* GL window: 0x468050 glWindow_restoreDisplayMode / 0x467f20 glWindow_setDisplayModeBy(w, h, bpp) /
   0x467e60 glWindow_setupPixelFormat(dc) / 0x468450 glWindow_resize(w, h); errors as message boxes */
LIFT_PLAIN(glWindow_restoreDisplayMode, 468050)
LIFT_PLAIN(glWindow_setDisplayModeBy, 467f20)
LIFT_PLAIN(glWindow_setupPixelFormat, 467e60)
LIFT_PLAIN(glWindow_resize, 468450)
/* 0x46cd00 (thiscall) image_initBy(path): open a 24-bit BMP, read and check its headers, keep width/height */
static THISCALL DWORD image_initBy(char *img, DWORD path) { DWORD v[1] = { path }; return run_lifted(lift_46cd00, (DWORD)img, 1, v); }
/* 0x466c00 shapeDat_initBy / 0x46afe0 skelDat_initBy: open Data\Shape.dat / Data\Skeleton.dat once and read its
   index (count, 0x44-byte entries) */
LIFT_PLAIN(shapeDat_initBy, 466c00)
LIFT_PLAIN(skelDat_initBy, 46afe0)
/* 0x487490 (thiscall) timer_getGameTime: frame time from the performance counter (initialised on first use),
   returned in ST0; 0x461210 (thiscall) armc_461210: its average over the last 10 frames */
static THISCALL long double timer_getGameTime(char *t) { return run_lifted_fp(lift_487490, (DWORD)t, 0, NULL); }
static THISCALL DWORD armc_461210(char *t) { return run_lifted(lift_461210, (DWORD)t, 0, NULL); }
/* 0x43f300 sys_checkClockTampering: compare the system time with the last one seen; a clock set back ends the
   game with a message */
LIFT_PLAIN(sys_checkClockTampering, 43f300)
/* 0x44ba60 profile_deleteFiles: delete the selected profile's files and reload the list */
LIFT_PLAIN(profile_deleteFiles, 44ba60)
/* 0x432400 reg_writeCharacterSettings: player name and character choices into the registry; 0x433640 room_433640 /
   0x43e610 room_43e610: room steps that save them */
LIFT_PLAIN(reg_writeCharacterSettings, 432400)
LIFT_PLAIN(room_433640, 433640)
LIFT_PLAIN(room_43e610, 43e610)
/* 0x42f150 gfx_initGLState(w, h): the GL state for a new window and the projection */
LIFT_PLAIN(gfx_initGLState, 42f150)
/* 0x456520 (thiscall) tex_upload(name, mode): upload the texture object's RGBA image (with mipmaps if wanted);
   0x473610 (thiscall) tex_upload2: copy each changed player colour block into the shared texture and upload it */
static THISCALL DWORD tex_upload(char *tex, DWORD name, DWORD mode) { DWORD v[2] = { name, mode }; return run_lifted(lift_456520, (DWORD)tex, 2, v); }
static THISCALL DWORD tex_upload2(char *scene) { return run_lifted(lift_473610, (DWORD)scene, 0, NULL); }
