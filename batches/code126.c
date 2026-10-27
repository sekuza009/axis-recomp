/* batch 125 (lifted/grp71.c): the mission-select tunnel and the profile screen */
#include "lifted/grp71.c"
/* 0x448140 missionsel_448140(): the mission-select backdrop: the setup tunnel's layers (setup_423e50) with three
   panels a side (at -40 / 0 / 40, pushed back 550), textures 0x4e0cd0 and 0x76d47c / 0x76d478, the hovered panel's
   glow (0x680398, 0x680ccc) and the pulse / scroll advancing as there */
LIFT_PLAIN(missionsel_448140, 448140)
/* 0x44d720 mainmenu_drawScreen(): the profile screen: frame and the two panels (bright when focused, 0x9f8f10),
   title 0x751a24, four buttons (0x751aa4; the hovered one, profile_44b260, bright; out of focus the focused
   button 0x9f8f10 - 2), the profile list (profile_44ce90) and its scroll arrows, the pilot panel
   (profile_44cf70), the border and "Axis v1.03" */
LIFT_PLAIN(mainmenu_drawScreen, 44d720)
