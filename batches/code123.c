/* batch 122 (lifted/grp68.c): the room login dialog and the pilot stats panel */
#include "lifted/grp68.c"
/* 0x4392c0 room_4392c0(): the room login dialog (only its frame while a message is open): title 0x7583a4 and its
   line, two labelled dark boxes (0x758424), the name 0x9dd1d8 and the password 0x9dd1f6 as '*' (each hidden while
   edited: 0x9dd830 / 0x9dd38c), three buttons (0x758524; none bright while connecting, 0x9dd838, which shows a box
   with two lines 0x74f6a4 / 0x74f724), the confirmation box (0x9dd850) and the border */
LIFT_PLAIN(room_4392c0, 4392c0)
/* 0x44cf70 profile_44cf70(): the selected profile's pilot panel (with profiles, 0x9f9008): the pilot (0x9f688c of
   the selected profile 0x9f8d74, into 0x9f8d6c), 13 labels (0x75e824), the portrait (texture 0x4dfa00, cell
   pilot % 3, pilot / 3 of 86 texels) in a yellow frame, name (0x9f9040, 0x4c apart), title (+0x10), class (+0x20, a
   0x75eea4 string), level (+0x24), nine stats (+0x28..) right-aligned, and nine bars easing (by 0x4b071c / 10)
   from 0x9f8d34 to 0x9f8ec0; dimmed when the panel is not focused (0x9f8f10) */
LIFT_PLAIN(profile_44cf70, 44cf70)
