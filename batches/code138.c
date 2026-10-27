/* batch 137 (lifted/grp83.c): the room's game settings form */
#include "lifted/grp83.c"
/* 0x43bfe0 room_drawGameSettings(): the game settings form (window 0x9dd1b8..): frame, title 0x75a424, a line,
   seven labels (0x75a4a4, 0x80 apart) and their boxes: the game name 0x4df9c8 and the password 0x4df9ee as '*'
   (each hidden while edited: 0x9dd380 / 0x9dd6a8), the map (0x4df9e8, a 0x5ae9d0 name, 0x50 apart; or, custom
   0x4df9ea, set lower), players (0x4df9e9), mode (0x4df9eb, a 0x7669a4 string), two limits (the bytes 0x4df9ec /
   0x4df9ed, hidden while edited: 0x9dd388 / 0x9dd568); unless a field is being edited (0x68039c) or the form is
   locked (0x907b2c) the hovered value (room_432380) gets a shadow and a highlight; three buttons (0x75a8a4, none
   bright while 0x4db508); then the custom option / map preview (room_drawCustomOption) */
LIFT_PLAIN(room_drawGameSettings, 43bfe0)
