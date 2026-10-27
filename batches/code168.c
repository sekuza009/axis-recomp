/* batch 167 (lifted/grp113.c): receiving DirectPlay messages */
#include "lifted/grp113.c"
/* 0x450bc0 arena_450bc0(from*, to*, flags, data, size*) / 0x450bf0 FUN_00450bf0(from, to, flags, data, size):
   DirectPlay Receive / Send through 0xa0b404 (0 without it) */
LIFT_PLAIN8(arena_450bc0, 450bc0)
LIFT_PLAIN8(FUN_00450bf0, 450bf0)
/* 0x451270 FUN_00451270(msg, to, size): send msg from the local player 0xa0b424; types 2 and 6 guaranteed (flag 1,
   priority 8), type 7 with the given size */
LIFT_PLAIN(FUN_00451270, 451270)
/* 0x451350 net_logMessage(from, text, out): "<name>: <text>" (the sender's name from DirectPlay, "?" text when
   NULL) in a new global block (*out); the error from the name lookup or 0x8007000e */
LIFT_PLAIN(net_logMessage, 451350)
/* 0x451090 arena_451090(msg, size, from): a game packet by type (1..7): 1 a chat line (net_logMessage into
   0x9fd948, flag 0x9fd95c), 2 the host's id (0x9fd94c) and the room reset (0x454130, 0x4515a0), 3..7 a player slot
   (byte +4: 0x9f9840 + 0x410 * slot) claimed or updated with up to 0x40 bytes of its data (+5 size, +9 data) */
LIFT_PLAIN(arena_451090, 451090)
/* 0x450c20 net_sendLocalInfo(sysmsg): DirectPlay system messages: 5 (create player): the host's slot (0x451530),
   and when hosting over TCP/IP the room or arena info sent to the newcomer (by 0xa0b380: 200 room, 201 arena; the
   packets 0xa0b310 / 0xa0b314 or 0xa0b328 / 0xa0b32c, net_send); 3 (destroy player): its slot freed (0x451450,
   FUN_00451270 with 0x9f9420) and the info sent again */
LIFT_PLAIN(net_sendLocalInfo, 450c20)
/* 0x450a60 arena_450a60(): every waiting DirectPlay message: the buffer (a global block of 0x9fd940 bytes) grown when
   too small, system messages (sender 0) to net_sendLocalInfo, a type 7 of more than 0x49 bytes ends the loop, others
   to arena_451090; ends at DPERR_NOMESSAGES / DPERR_GENERIC-like 0x887703e8 or any other failure (size 0) */
LIFT_PLAIN(arena_450a60, 450a60)
/* 0x450bb0 FUN_00450bb0: jump to arena_450a60 */
LIFT_PLAIN(FUN_00450bb0, 450bb0)
