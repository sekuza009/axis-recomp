/* batch 165 (lifted/grp111.c): profile screen dialogs and mouse handlers */
#include "lifted/grp111.c"
/* 0x44b600 profile_44b600(): start typing a profile name: keyboard released, input cleared, the edit box at the
   name field (0x9f8ea8 + 0x38, 0x9f8eac + 0x24), page 2, a dialog open, the edit window created */
LIFT_PLAIN(profile_44b600, 44b600)
/* 0x44b670 profile_44b670() / 0x44b6e0 profile_44b6e0(): open the delete (page 3, box at 0x9f8f0c / 0x9f8f1c) or
   load (page 5, box at 0x9f683c / 0x9f6834) confirmation: menu sound 0, a dialog open, its pop-in animation */
LIFT_PLAIN(profile_44b670, 44b670)
LIFT_PLAIN(profile_44b6e0, 44b6e0)
/* the profile pages' mouse (a left click on the page's buttons, a right click back to page 1):
   0x44c390 profile_44c390(): delete confirmation (0x44b320): yes deletes (profile_deleteFiles), no;
   0x44c400 profile_44c400(): load confirmation (0x44b360): yes loads (profile_44bc00), no;
   0x44c480 profile_44c480(): the profile list (0x44b3e0, 11 buttons): a profile row selects it (sound 2), load
   (profile_selectAndLoad), back */
LIFT_PLAIN(profile_44c390, 44c390)
LIFT_PLAIN(profile_44c400, 44c400)
LIFT_PLAIN(profile_44c480, 44c480)
