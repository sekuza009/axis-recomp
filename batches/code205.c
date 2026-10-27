/* batch 204 (lifted/grp163.c): the game's start-up load */
#include "lifted/grp163.c"
/* 0x430400 app_checkCdAndLoad(inst): key tables 0x4d1688 / 0x4d1a98 cleared; the loaders (0x4515d0 .. 0x42fb40),
   the 640 x 480 cursor range, 0x4302d0; the CD check once (0x401410 with the main window; failure: a message box
   and 0); unless 0x76d410 the five checks (0x41e6d0 .. 0x41e670) each end it with their message; the window's
   GL state (0x467a50 -> 0xa0e80c, then 0x42bd40); the cursor at 310, 230; 0x431680, 0x401780; 0x401000 (failure: a
   message box and 0); the six texture sets built (0x455080 at 0x4e1878 .. 0x83a9e0, sizes from 0x83a9cc /
   0x83a9d0) and gathered (0x4569d0 at 0x83a5e0 -> 0xa0e010); the font (0x46b950); four textures by name
   (0x456be0); 0x466c00, 0x46afe0; the scene (operator new 0x2343acb, constructed by 0x460570 -> 0x9087b4, 0 if the
   allocation failed); 0x456d10; a fifth texture; the camera and menu defaults (two 0x41f0e0 vectors, the fade 5,
   the screen centre from 0x5b1998 / 0x4e045c, 0x4dd984 from 0x4e0c90). SEH frame emulated. Returns 1, or 0 */
LIFT_PLAIN(app_checkCdAndLoad, 430400)
