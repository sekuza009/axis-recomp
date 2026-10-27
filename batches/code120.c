/* batch 119 (lifted/grp65.c): the loading screen and two dialogs */
#include "lifted/grp65.c"
/* 0x41f100 intro_41f100(): the loading screen: clear to 0x76d350, the loading picture (texture 0x76d3f0) in the
   middle, the progress bar (0x4dda34 * 16 one-unit columns in three colour ramps: red to blue, green to blue, red
   to yellow), glFinish and SwapBuffers on 0x76d480 */
LIFT_PLAIN(intro_41f100, 41f100)
/* 0x4399c0 room_4399c0(): the server login dialog (only its frame while a message is open): title 0x7588a4, four
   labelled lines (0x758924, 0x80 apart) with underlines, the values (name 0x9dd1d8, the two password fields
   0x9dd1f6 / 0x9dd202 as '*', 0x9dd20e), each hidden while its field is being edited (0x9dd348 / 0x9dd3f8 /
   0x9dd564 / 0x9dd6cc with 0x68039c), two buttons (the one under the cursor bright) and the border */
LIFT_PLAIN(room_4399c0, 4399c0)
/* 0x409bc0 arena_409bc0(): the arena name dialog: frame, a cyan box, title 0x751fa4, two labels and the name
   0x4db560 (hidden while edited, 0x68039c); without a message (0x4dbbd0) the label under the cursor gets a shadow
   and a highlight; three buttons (0x7521a4, 0x80 apart), the border */
LIFT_PLAIN(arena_409bc0, 409bc0)
