/* batch 99 (lifted/grp45.c) */
#include "lifted/grp45.c"
/* 0x452620 net_recv(): the network state machine's receive step, by state 0xa0b300: 10 / 0x12 a 4-byte answer on the
   lobby / server socket (1 disconnect: 0x67, 0 accepted: 0x66, 3 refused; into 0xa0b370 / 0xa0b374), 0xe / 0xf a
   0x10b-byte server reply (its first byte a status into 0xa0b378 / 0xa0b37c), 0xd / 0x13 / 0x15 the reply readers
   (net_452a30 / net_452bd0 / net_452d70), 0x1a clear the room table (net_452ea0), 0x1d a 0x22-byte chat line
   (0xa052c0; non-empty sets 0xa0b354); each read waits up to 3 s (timeout: status 0x29 / 0x28) and most end the
   state (0) */
LIFT_PLAIN(net_recv, 452620)
