/* batch 142 (lifted/grp88.c): two more screen dispatchers */
#include "lifted/grp88.c"
/* 0x44f810 profile_44f810(): the pilot-select dialog (profile_44e640), its colours refreshed first when asked
   (0x9f8d68: profile_44bc50), or only its frame while a message is open */
LIFT_PLAIN(profile_44f810, 44f810)
/* 0x43ede0 room_43ede0(): the ranking page: a pending request (0x9dd350) for sort column 0x9dd1d0 sends packet
   0x15 / 0x65 (code 0x25 / 0x23 / 0x26 and the first rank of page 0x9dd6ac, stored as in room_43d060) and starts
   waiting (0x9dd6b8, blink 1000), column 3 just clears it; the room tunnel (room_4388e0); then, in room modes
   other than 0 / 1 (0x9dce48) and outside sub-state 99 (0x9dd834): with a message open only the ranking frame
   (and a request when it closes), else while waiting an answer (0x76d40c) fills the list (room_435770) and keeps
   the column and page (0x9dd300, 0x9dd1b4), the blink counts down (by 0x4b071c * 0x4ad498, from 1000 again below
   0); the ranking table (room_43d060) */
LIFT_PLAIN(room_43ede0, 43ede0)
